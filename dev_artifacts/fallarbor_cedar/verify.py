"""Verify the pixel-preserving Wurrentest experiment and render indexed assets."""
from pathlib import Path
from collections import Counter
import json
import struct
from PIL import Image, ImageDraw
from refine import ROOF, DOOR, tile, remap_pixels

ROOT = Path(__file__).resolve().parents[2]
REPORT = Path(__file__).resolve().parent
SOURCE = ROOT / 'data/tilesets/secondary/fallarbor'
DEST = ROOT / 'data/tilesets/secondary/fallarbor_cedar'
BACKUP = REPORT / 'before'
PRIMARY = ROOT / 'data/tilesets/primary/general'

def words(path):
    data = path.read_bytes()
    return list(struct.unpack('<' + 'H' * (len(data) // 2), data))

def palette(path):
    return [tuple(map(int, line.split())) for line in path.read_text().splitlines()[3:19]]

def render(secondary, blocks):
    sheets = [Image.open(PRIMARY / 'tiles.png'), Image.open(secondary / 'tiles.png')]
    metatiles = [words(PRIMARY / 'metatiles.bin'), words(secondary / 'metatiles.bin')]
    palettes = [palette((PRIMARY if i < 6 else secondary) / f'palettes/{i:02}.pal') for i in range(13)]
    output = Image.new('RGB', (80, 64))
    for pos, block in enumerate(blocks):
        mid = block & 1023
        entries = metatiles[mid >= 512][mid % 512 * 8:(mid % 512 + 1) * 8]
        for offset, entry in enumerate(entries):
            tid = entry & 1023
            sheet = sheets[tid >= 512]
            cols = sheet.width // 8
            local = tid % 512
            x0, y0 = local % cols * 8, local // cols * 8
            tile = sheet.crop((x0, y0, x0 + 8, y0 + 8))
            if entry & 1024:
                tile = tile.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
            if entry & 2048:
                tile = tile.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
            for y in range(8):
                for x in range(8):
                    index = tile.getpixel((x, y)) % 16
                    if index:
                        output.putpixel((pos % 5 * 16 + offset % 2 * 8 + x,
                                         pos // 5 * 16 + offset % 4 // 2 * 8 + y), palettes[entry >> 12][index])
    return output

for saved in (BACKUP / 'secondary').rglob('*'):
    if saved.is_file():
        relative = saved.relative_to(BACKUP / 'secondary')
        assert (SOURCE / relative).read_bytes() == saved.read_bytes(), f'Original changed: {relative}'
        if relative not in (Path('palettes/07.pal'), Path('tiles.png'), Path('metatiles.bin')):
            assert (DEST / relative).read_bytes() == saved.read_bytes(), f'Unexpected copy change: {relative}'
oldpal = palette(SOURCE / 'palettes/07.pal')
newpal = palette(DEST / 'palettes/07.pal')
assert len(newpal) == 16
for index in (0, 9, 10, 15):
    assert newpal[index] == oldpal[index], f'Transparency, glass or ground colour changed: {index}'
for name in ('map.bin', 'border.bin'):
    assert (ROOT / 'data/layouts/wurrentest' / name).read_bytes() == (BACKUP / name).read_bytes()
for name in ('fallarbor_light_roof.png', 'fallarbor_dark_roof.png'):
    assert (ROOT / 'graphics/door_anims' / name).read_bytes() == (BACKUP / name).read_bytes()
before_layouts = json.loads((BACKUP / 'registration/data/layouts/layouts.json').read_text())
after_layouts = json.loads((ROOT / 'data/layouts/layouts.json').read_text())
expected = json.loads(json.dumps(before_layouts))
layout = next(x for x in expected['layouts'] if x['id'] == 'LAYOUT_WURRENTEST')
assert layout['secondary_tileset'] == 'gTileset_Fallarbor'
layout['secondary_tileset'] = 'gTileset_FallarborCedar'
assert expected == after_layouts, 'Another layout was changed'
assert not any(x['secondary_tileset'] == 'gTileset_FallarborCedar' for x in after_layouts['layouts'] if x['id'] != 'LAYOUT_WURRENTEST')
met = words(DEST / 'metatiles.bin')
blocks = words(ROOT / 'data/layouts/wurrentest/map.bin')
assert len(blocks) == 20
targets = {x & 1023 for x in blocks}
original_met = words(SOURCE / 'metatiles.bin')
assert len(met) == len(original_met), 'No new metatiles permitted'
original_sheet = Image.open(SOURCE / 'tiles.png')
new_sheet = Image.open(DEST / 'tiles.png')
assert new_sheet.mode == original_sheet.mode == 'P' and new_sheet.size == original_sheet.size
roles = {}
for position, block in enumerate(blocks):
    for off in range(8):
        address = ((block & 1023) - 512) * 8 + off
        if original_met[address] >> 12 != 7:
            continue
        x = position % 5 * 16 + off % 2 * 8
        y = position // 5 * 16 + off % 4 // 2 * 8
        role = 'roof' if y < 40 else ('door' if 32 <= x < 48 else 'facade')
        if role == 'facade' and original_met[address] & 1023 in (0x2AC, 0x2BC):
            role = 'window_top' if original_met[address] & 1023 == 0x2AC else 'window_bottom'
        assert address not in roles or roles[address] == role
        roles[address] = role
allocated = set()
original_refs = {e & 1023 for e in original_met + words(PRIMARY / 'metatiles.bin')}
for address, (old, new) in enumerate(zip(original_met, met)):
    if address not in roles:
        assert old == new, 'An unrelated metatile changed'
        continue
    assert old & 0xFC00 == new & 0xFC00, 'Palette or flip flags changed'
    slot = (new & 1023) - 512
    assert 0 < slot < 504 and slot + 512 not in original_refs
    assert not any(tile(original_sheet, slot).get_flattened_data())
    original_pixels = list(tile(original_sheet, (old & 1023) - 512).get_flattened_data())
    new_pixels = list(tile(new_sheet, slot).get_flattened_data())
    assert new_pixels == remap_pixels(original_pixels, roles[address]), 'Pixel shape/pattern changed'
    assert [i == 0 for i in original_pixels] == [i == 0 for i in new_pixels]
    allocated.add(slot)
for slot in range(original_sheet.width * original_sheet.height // 64):
    if slot not in allocated:
        assert list(tile(original_sheet, slot).get_flattened_data()) == list(tile(new_sheet, slot).get_flattened_data())
assert len(allocated) == 26 and max(new_sheet.get_flattened_data()) < 16
other_affected = sorted({512+i//8 for i, e in enumerate(met) if e>>12 == 7 and (512+i//8) not in targets})
print('Other metatiles using palette 7 in the COPY:', ', '.join(hex(x) for x in other_affected))
print('Secondary palette usage:', dict(Counter(e >> 12 for e in met)))
before = render(SOURCE, blocks)
after = render(DEST, blocks)
before.save(REPORT / 'building_before.png')
after.save(REPORT / 'building_after.png')
after.resize((640, 512), Image.Resampling.NEAREST).save(REPORT / 'preview.png')
comparison = Image.new('RGB', (1016, 430), (242, 240, 235))
draw = ImageDraw.Draw(comparison)
for i, (title, im) in enumerate([('Original orange roof', before), ('Cedar roof + golden wood + matching door', after)]):
    draw.text((12+i*504, 8), title, fill=(30, 30, 35))
    comparison.paste(im.resize((480, 384), Image.Resampling.NEAREST), (12+i*504, 32))
comparison.save(REPORT / 'comparison.png')
revision = REPORT / 'refined'
previous = Image.open(revision / 'before/building_after.png')
revised_comparison = Image.new('RGB', (1016, 430), (242, 240, 235))
draw = ImageDraw.Draw(revised_comparison)
for i, (title, im) in enumerate([('First pass', previous), ('Refined wood + orange accents + yellow knob', after)]):
    draw.text((12+i*504, 8), title, fill=(30, 30, 35))
    revised_comparison.paste(im.resize((480, 384), Image.Resampling.NEAREST), (12+i*504, 32))
revised_comparison.save(revision / 'comparison.png')
# All eight animation quadrants use the same palette 7 as the static door.
animation = Image.open(ROOT / 'graphics/door_anims/fallarbor_cedar.png')
assert animation.mode == 'P' and animation.size == (16, 96)
assert max(animation.get_flattened_data()) < 16
original_animation = Image.open(ROOT / 'graphics/door_anims/fallarbor_light_roof.png')
for y in range(96):
    mapping = ROOF if y % 32 < 8 else DOOR
    for x in range(16):
        old = original_animation.getpixel((x, y))
        assert animation.getpixel((x, y)) == mapping.get(old, old)
rgb = Image.new('RGB', animation.size)
rgb.putdata([newpal[index] for index in animation.get_flattened_data()])
rgb.resize((128, 768), Image.Resampling.NEAREST).save(REPORT / 'door_animation_preview.png')
door_source = (ROOT / 'src/field_door.c').read_text()
assert 'sDoorAnimPalettes_FallarborLightRoof[] = {7, 7, 7, 7, 7, 7, 7, 7}' in door_source
for door in ('LightRoof', 'DarkRoof', 'BattleTent'):
    assert any('METATILE_Fallarbor_Door_'+door in line and '&gTileset_FallarborCedar' in line for line in door_source.splitlines())
assert any('METATILE_Fallarbor_Door_LightRoof' in line and '&gTileset_FallarborCedar' in line and 'sDoorAnimTiles_FallarborCedar,' in line for line in door_source.splitlines())
print('PASS: original tileset/animations unchanged; 26 unused tile slots remapped; pixels/flags/behaviour preserved; no new palettes/metatiles; matching animation copy.')

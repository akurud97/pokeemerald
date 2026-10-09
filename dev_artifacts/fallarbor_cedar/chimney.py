"""Add the chimney variant to the existing wood palette, preserving saved map edits."""
from pathlib import Path
import json
import shutil
import struct
import sys
from PIL import Image, ImageDraw
from refine import ROOF, tile

ROOT = Path(__file__).resolve().parents[2]
REPORT = Path(__file__).resolve().parent / 'chimney'
SOURCE = ROOT / 'data/tilesets/secondary/fallarbor'
DEST = ROOT / 'data/tilesets/secondary/fallarbor_cedar'
PRIMARY = ROOT / 'data/tilesets/primary/general'
TARGETS = {0x320, 0x321, 0x328, 0x329}
# Existing window/glass colours give the chimney a metallic blue-grey finish.
# Index 14 is the roof shadow showing beneath the chimney.
CHIMNEY = {1: 10, 2: 7, 3: 8, 4: 12, 5: 5, 6: 6, 7: 12, 8: 12, 14: 12}
ROOF_TILES = {0x2AF, 0x2BF}

def words(path):
    data = path.read_bytes()
    return list(struct.unpack('<' + 'H' * (len(data) // 2), data))

def palette(path):
    return [tuple(map(int, l.split())) for l in path.read_text().splitlines()[3:19]]

def render(secondary, blocks, width, sheet=None, entries=None, palette_overrides=None):
    sheets = [Image.open(PRIMARY / 'tiles.png'), sheet if sheet is not None else Image.open(secondary / 'tiles.png')]
    mets = [words(PRIMARY / 'metatiles.bin'), entries if entries is not None else words(secondary / 'metatiles.bin')]
    pals = [palette((PRIMARY if i < 6 else secondary) / f'palettes/{i:02}.pal') for i in range(13)]
    if palette_overrides:
        for number, colours in palette_overrides.items():
            pals[number] = colours
    output = Image.new('RGB', (width * 16, len(blocks) // width * 16))
    for pos, block in enumerate(blocks):
        mid = block & 1023
        for off, e in enumerate(mets[mid >= 512][mid % 512 * 8:(mid % 512 + 1) * 8]):
            tid = e & 1023
            im = tile(sheets[tid >= 512], tid % 512)
            if e & 1024:
                im = im.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
            if e & 2048:
                im = im.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
            for y in range(8):
                for x in range(8):
                    index = im.getpixel((x, y)) % 16
                    if index:
                        output.putpixel((pos % width * 16 + off % 2 * 8 + x,
                                         pos // width * 16 + off % 4 // 2 * 8 + y), pals[e >> 12][index])
    return output

def prepare():
    layout = next(l for l in json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts'] if l['id'] == 'LAYOUT_WURRENTEST')
    assert layout['secondary_tileset'] == 'gTileset_FallarborCedar'
    blocks = words(ROOT / layout['blockdata_filepath'])
    assert len(blocks) == layout['width'] * layout['height']
    assert TARGETS <= {b & 1023 for b in blocks}
    entries = words(DEST / 'metatiles.bin')
    original = words(SOURCE / 'metatiles.bin')
    oldsheet = Image.open(DEST / 'tiles.png')
    source_sheet = Image.open(SOURCE / 'tiles.png')
    sheet = oldsheet.copy()
    references = {e & 1023 for e in entries + words(PRIMARY / 'metatiles.bin')}
    free = [i for i in range(1, min(504, oldsheet.width * oldsheet.height // 64))
            if i + 512 not in references and not any(tile(oldsheet, i).get_flattened_data())]
    allocated = {}
    for mid in sorted(TARGETS):
        start = (mid - 512) * 8
        assert entries[start:start+8] == original[start:start+8], 'Chimney metatile has unexpected edits'
        for off in range(8):
            e = entries[start+off]
            if e >> 12 != 7:
                continue
            tid = e & 1023
            mapping = ROOF if tid in ROOF_TILES else CHIMNEY
            pixels = [mapping.get(i, i) for i in tile(source_sheet, tid-512).get_flattened_data()]
            key = (tid, 'roof' if tid in ROOF_TILES else 'chimney')
            if key not in allocated:
                # Reuse a remapped roof tile from the preceding pass if identical.
                matching = next((i for i in range(1, oldsheet.width * oldsheet.height // 64)
                                 if list(tile(oldsheet, i).get_flattened_data()) == pixels), None)
                if matching is None:
                    assert free, 'No safe unused tile slots'
                    matching = free.pop(0)
                    im = tile(source_sheet, tid-512)
                    im.putdata(pixels)
                    sheet.paste(im, (matching % 16 * 8, matching // 16 * 8))
                allocated[key] = matching + 512
            entries[start+off] = (e & 0xFC00) | allocated[key]
    before = render(DEST, blocks, layout['width'])
    after = render(DEST, blocks, layout['width'], sheet, entries)
    return layout, blocks, oldsheet, sheet, entries, allocated, before, after

def main():
    layout, blocks, oldsheet, sheet, entries, allocated, before, after = prepare()
    if sys.argv[1:] == ['--preview']:
        after.resize((512, 640), Image.Resampling.NEAREST).save('/private/tmp/wurrentest_chimney_candidate.png')
        print('Preview only; no project assets changed.')
        return
    assert not sys.argv[1:]
    assert not REPORT.exists(), 'Never overwrite an existing backup'
    REPORT.mkdir()
    backup = REPORT / 'before'
    shutil.copytree(DEST, backup / 'secondary')
    for path in ['data/layouts/wurrentest/map.bin', 'data/layouts/wurrentest/border.bin', 'data/layouts/layouts.json', 'graphics/door_anims/fallarbor_cedar.png']:
        target = backup / path
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / path, target)
    previous_entries = words(DEST / 'metatiles.bin')
    slots = {new-512 for new in allocated.values()
             if list(tile(oldsheet, new-512).get_flattened_data()) != list(tile(sheet, new-512).get_flattened_data())}
    for slot in range(oldsheet.width * oldsheet.height // 64):
        if slot not in slots:
            assert list(tile(oldsheet, slot).get_flattened_data()) == list(tile(sheet, slot).get_flattened_data())
        else:
            assert not any(tile(oldsheet, slot).get_flattened_data())
    assert sheet.mode == oldsheet.mode == 'P' and sheet.size == oldsheet.size
    assert max(sheet.get_flattened_data()) < 16
    for address, (old, new) in enumerate(zip(previous_entries, entries)):
        assert old == new or address // 8 + 512 in TARGETS
        assert old & 0xFC00 == new & 0xFC00
    sheet.save(DEST / 'tiles.png', optimize=False)
    (DEST / 'metatiles.bin').write_bytes(struct.pack('<' + 'H'*len(entries), *entries))
    before.save(REPORT / 'building_before.png')
    after.save(REPORT / 'building_after.png')
    after.resize((512, 640), Image.Resampling.NEAREST).save(REPORT / 'preview.png')
    original = render(SOURCE, blocks, layout['width'])
    comparison = Image.new('RGB', (812, 536), (242, 240, 235))
    draw = ImageDraw.Draw(comparison)
    for i, (title, im) in enumerate([('Original orange + chimney', original), ('Wood palette + blue-grey chimney', after)]):
        draw.text((12+i*400, 8), title, fill=(30, 30, 35))
        comparison.paste(im.resize((384, 480), Image.Resampling.NEAREST), (12+i*400, 32))
    comparison.save(REPORT / 'comparison.png')
    for saved in (backup / 'secondary').rglob('*'):
        if saved.is_file():
            rel = saved.relative_to(backup / 'secondary')
            if rel not in (Path('tiles.png'), Path('metatiles.bin')):
                assert saved.read_bytes() == (DEST / rel).read_bytes()
    for path in ['data/layouts/wurrentest/map.bin', 'data/layouts/wurrentest/border.bin', 'data/layouts/layouts.json', 'graphics/door_anims/fallarbor_cedar.png']:
        assert (ROOT / path).read_bytes() == (backup / path).read_bytes()
    source_backup = REPORT.parent / 'before/secondary'
    for saved in source_backup.rglob('*'):
        if saved.is_file():
            assert saved.read_bytes() == (SOURCE / saved.relative_to(source_backup)).read_bytes()
    for (tid, role), new in allocated.items():
        old_pixels = tile(Image.open(SOURCE / 'tiles.png'), tid-512).get_flattened_data()
        new_pixels = tile(sheet, new-512).get_flattened_data()
        mapping = ROOF if role == 'roof' else CHIMNEY
        assert list(new_pixels) == [mapping.get(i, i) for i in old_pixels]
    print('PASS: only four chimney metatiles remapped; pixel positions/flip flags/palettes/map/behaviour/door animation preserved.')
    print('Existing blank tile slots filled:', sorted(slots), '; no new palette or metatile slots.')

if __name__ == '__main__':
    main()

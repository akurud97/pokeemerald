"""Create and verify the Tiakitest teal/grey building with untouched wood pixels."""
from pathlib import Path
from collections import Counter
import importlib.util
import json
import shutil
import struct
import sys
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / 'data/tilesets/secondary/dewford'
DEST = ROOT / 'data/tilesets/secondary/dewford_teal'
PRIMARY = ROOT / 'data/tilesets/primary/general'
REPORT = Path(__file__).resolve().parent
BACKUP = REPORT / 'before'
spec = importlib.util.spec_from_file_location('native_render', ROOT / 'dev_artifacts/fallarbor_cedar/chimney.py')
helper = importlib.util.module_from_spec(spec)
sys.path.insert(0,str(ROOT / 'dev_artifacts/fallarbor_cedar'))
spec.loader.exec_module(helper)
words, palette, render = helper.words, helper.palette, helper.render
SAND_TILES = {0x108, 0x118}
REGISTRATION = ['src/data/tilesets/graphics.h', 'src/data/tilesets/metatiles.h',
                'src/data/tilesets/headers.h', 'include/tilesets.h', 'src/field_door.c',
                'data/layouts/layouts.json']

def prepare():
    assert not DEST.exists() and not BACKUP.exists(), 'Do not overwrite an existing copy or backup'
    original = words(SOURCE / 'metatiles.bin')
    pm = words(PRIMARY / 'metatiles.bin')
    assert not any(e >> 12 in (6,11) for e in original+pm), 'Palette slots 6/11 are not unused'
    layouts = json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']
    layout = next(l for l in layouts if l['id'] == 'LAYOUT_TIAKITEST')
    assert layout['primary_tileset'] == 'gTileset_General' and layout['secondary_tileset'] == 'gTileset_Dewford'
    assert layout['width'] == 5 and layout['height'] == 4
    blocks = words(ROOT / layout['blockdata_filepath'])
    targets = {b & 1023 for b in blocks}
    assert len(blocks) == 20 and all(mid >= 512 for mid in targets)
    BACKUP.mkdir(parents=True)
    shutil.copytree(SOURCE, BACKUP / 'secondary')
    shutil.copytree(PRIMARY, BACKUP / 'primary')
    shutil.copytree(SOURCE, DEST)
    for path in REGISTRATION + [layout['blockdata_filepath'],layout['border_filepath'],
                                'graphics/door_anims/dewford.png']:
        target = BACKUP / path
        target.parent.mkdir(parents=True,exist_ok=True)
        shutil.copy2(ROOT/path,target)
    door_dest = ROOT / 'graphics/door_anims/dewford_teal.png'
    assert not door_dest.exists()
    shutil.copy2(ROOT / 'graphics/door_anims/dewford.png',door_dest)
    entries = original.copy()
    for mid in targets:
        for off in range(8):
            address = (mid-512)*8+off
            e = original[address]
            tid, oldpal = e & 1023, e >> 12
            if tid == 0 or tid in SAND_TILES:
                continue
            assert oldpal in (0,5)
            entries[address] = (e & 0x0FFF) | (6 if oldpal == 0 else 11) << 12
    (DEST / 'metatiles.bin').write_bytes(struct.pack('<'+'H'*len(entries),*entries))
    print('Created DewfordTeal copy; palettes 6 and 11 are free. No new tile or metatile slots.')

def verify():
    for name, current in [('secondary',SOURCE),('primary',PRIMARY)]:
        for saved in (BACKUP/name).rglob('*'):
            if saved.is_file():
                assert saved.read_bytes() == (current/saved.relative_to(BACKUP/name)).read_bytes(), f'Original {name} changed'
    for saved in (BACKUP/'secondary').rglob('*'):
        if saved.is_file():
            rel = saved.relative_to(BACKUP/'secondary')
            if rel not in (Path('metatiles.bin'),Path('palettes/06.pal'),Path('palettes/11.pal')):
                assert saved.read_bytes() == (DEST/rel).read_bytes(), f'Unexpected asset change: {rel}'
    before_layouts = json.loads((BACKUP / 'data/layouts/layouts.json').read_text())
    after_layouts = json.loads((ROOT / 'data/layouts/layouts.json').read_text())
    layout = next(l for l in before_layouts['layouts'] if l['id'] == 'LAYOUT_TIAKITEST')
    layout['secondary_tileset'] = 'gTileset_DewfordTeal'
    assert before_layouts == after_layouts, 'An unrelated layout changed'
    assert [l['id'] for l in after_layouts['layouts'] if l['secondary_tileset'] == 'gTileset_DewfordTeal'] == ['LAYOUT_TIAKITEST']
    blocks = words(ROOT / layout['blockdata_filepath'])
    for path in [layout['blockdata_filepath'],layout['border_filepath']]:
        assert (ROOT/path).read_bytes() == (BACKUP/path).read_bytes()
    original = words(SOURCE/'metatiles.bin')
    entries = words(DEST/'metatiles.bin')
    assert len(entries) == len(original)
    targets = {b & 1023 for b in blocks}
    for address,(old,new) in enumerate(zip(original,entries)):
        assert old & 0x0FFF == new & 0x0FFF, 'Tile ID/flip flags changed'
        assert old == new or address//8+512 in targets
        if old != new:
            assert new >> 12 == (6 if old >> 12 == 0 else 11)
        if old & 1023 in SAND_TILES:
            assert old == new
    wood = palette(PRIMARY/'palettes/05.pal')
    facade = palette(DEST/'palettes/11.pal')
    assert facade[11:16] == wood[11:16], 'Wood shades changed'
    assert facade[9:11] == wood[9:11], 'Window glass changed'
    assert len(facade) == len(palette(DEST/'palettes/06.pal')) == 16
    door = ROOT/'graphics/door_anims/dewford_teal.png'
    assert door.read_bytes() == (ROOT/'graphics/door_anims/dewford.png').read_bytes()
    assert (ROOT/'graphics/door_anims/dewford.png').read_bytes() == (BACKUP/'graphics/door_anims/dewford.png').read_bytes()
    field_door = (ROOT/'src/field_door.c').read_text()
    assert 'sDoorAnimPalettes_DewfordTeal[] = {6, 6, 11, 11, 11, 11, 11, 11}' in field_door
    assert any('METATILE_Dewford_Door,' in l and '&gTileset_DewfordTeal' in l and 'sDoorAnimTiles_DewfordTeal' in l for l in field_door.splitlines())
    before, after = render(SOURCE,blocks,5), render(DEST,blocks,5)
    before.save(REPORT/'building_before.png')
    after.save(REPORT/'building_after.png')
    after.resize((640,512),Image.Resampling.NEAREST).save(REPORT/'preview.png')
    comparison = Image.new('RGB',(1016,430),(242,240,235))
    draw = ImageDraw.Draw(comparison)
    for i,(label,im) in enumerate([('Original Dewford building',before),('Teal roof + light grey + original wood',after)]):
        draw.text((12+i*504,8),label,fill=(30,30,35))
        comparison.paste(im.resize((480,384),Image.Resampling.NEAREST),(12+i*504,32))
    comparison.save(REPORT/'comparison.png')
    animation = Image.open(door)
    rgb = Image.new('RGB',animation.size)
    roof = palette(DEST/'palettes/06.pal')
    for y in range(animation.height):
        pal = roof if y%32 < 8 else facade
        for x in range(animation.width):
            # Original PNG carries two 16-colour banks; 4bpp uses the low nibble.
            rgb.putpixel((x,y),pal[animation.getpixel((x,y)) % 16])
    rgb.resize((128,768),Image.Resampling.NEAREST).save(REPORT/'door_animation_preview.png')
    print('PASS: originals, pixels, tile IDs, flips, attributes, sand, glass/wood colours and map preserved; only Tiakitest switched; copied door animation matches.')
    print('Palette references in clone:',dict(Counter(e >> 12 for e in entries)))

if __name__ == '__main__':
    if sys.argv[1:] == ['--prepare']:
        prepare()
    elif sys.argv[1:] == ['--verify']:
        verify()
    else:
        raise SystemExit('Use --prepare once or --verify after registration/palette edits.')

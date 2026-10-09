"""Apply the approved palette-3 grey chimney preview, preserving all other assets."""
from pathlib import Path
from collections import defaultdict
import json
import shutil
import struct
from PIL import Image, ImageChops, ImageDraw
from chimney import render, words, TARGETS, ROOF_TILES
from copper import COPPER
from refine import tile

ROOT = Path(__file__).resolve().parents[2]
DEST = ROOT / 'data/tilesets/secondary/fallarbor_cedar'
SOURCE = ROOT / 'data/tilesets/secondary/fallarbor'
PRIMARY = ROOT / 'data/tilesets/primary/general'
REPORT = Path(__file__).resolve().parent / 'grey'
GREY = {1: 2, 2: 3, 3: 4, 4: 8, 5: 5, 6: 8, 7: 8, 8: 8, 9: 5, 10: 3, 14: 8}

def main():
    assert not REPORT.exists(), 'Never overwrite a revision backup'
    layout = next(l for l in json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts'] if l['id'] == 'LAYOUT_WURRENTEST')
    assert layout['primary_tileset'] == 'gTileset_General'
    assert layout['secondary_tileset'] == 'gTileset_FallarborCedar'
    blocks = words(ROOT / layout['blockdata_filepath'])
    assert layout['width'] == 4 and layout['height'] == 5 and len(blocks) == 20
    original = words(SOURCE / 'metatiles.bin')
    previous = words(DEST / 'metatiles.bin')
    entries = previous.copy()
    oldsheet = Image.open(DEST / 'tiles.png')
    source = Image.open(SOURCE / 'tiles.png')
    sheet = oldsheet.copy()
    refs = defaultdict(set)
    for address, e in enumerate(previous):
        refs[e & 1023].add(address // 8 + 512)
    changed = {}
    for mid in sorted(TARGETS):
        for off in range(8):
            address = (mid - 512)*8 + off
            old = previous[address]
            tid = original[address] & 1023
            if old >> 12 != 7 or tid in ROOF_TILES:
                continue
            local = (old & 1023)-512
            assert not any(tile(source, local).get_flattened_data()), 'Do not edit original nonblank art'
            assert refs[old & 1023] <= TARGETS, 'Chimney graphics are shared elsewhere'
            original_pixels = list(tile(source, tid-512).get_flattened_data())
            current_pixels = list(tile(oldsheet, local).get_flattened_data())
            assert current_pixels == [COPPER.get(i, i) for i in original_pixels], 'Unexpected edits to bronze chimney'
            values = [GREY.get(i, i) for i in original_pixels]
            assert local not in changed or changed[local] == values
            changed[local] = values
            assert [i == 0 for i in original_pixels] == [i == 0 for i in values]
            im = tile(source, tid-512)
            im.putdata(values)
            sheet.paste(im, (local % 16 * 8, local // 16 * 8))
            entries[address] = (old & 0x0FFF) | 3 << 12
    assert len(changed) == 10
    assert len(entries) == len(previous)
    assert max(sheet.get_flattened_data()) < 16
    assert sheet.mode == oldsheet.mode == 'P' and sheet.size == oldsheet.size
    for slot in range(sheet.width * sheet.height // 64):
        if slot not in changed:
            assert list(tile(sheet, slot).get_flattened_data()) == list(tile(oldsheet, slot).get_flattened_data())
    for address, (old, new) in enumerate(zip(previous, entries)):
        assert old & 0x0FFF == new & 0x0FFF, 'Tile IDs/flip flags changed'
        assert old == new or address // 8 + 512 in TARGETS
    before = render(DEST, blocks, layout['width'])
    after = render(DEST, blocks, layout['width'], sheet, entries)
    box = ImageChops.difference(before, after).getbbox()
    assert box and box[0] >= 32 and box[3] <= 32, 'An area outside the chimney changed'
    REPORT.mkdir()
    shutil.copytree(DEST, REPORT / 'before/secondary')
    preserved = ['data/layouts/wurrentest/map.bin', 'data/layouts/wurrentest/border.bin', 'data/layouts/layouts.json', 'graphics/door_anims/fallarbor_cedar.png', 'data/tilesets/primary/general/palettes/03.pal']
    for path in preserved:
        target = REPORT / 'before' / path
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / path, target)
    sheet.save(DEST / 'tiles.png', optimize=False)
    (DEST / 'metatiles.bin').write_bytes(struct.pack('<'+'H'*len(entries), *entries))
    for saved in (REPORT / 'before/secondary').rglob('*'):
        if saved.is_file():
            rel = saved.relative_to(REPORT / 'before/secondary')
            if rel not in (Path('tiles.png'), Path('metatiles.bin')):
                assert saved.read_bytes() == (DEST / rel).read_bytes()
    for path in preserved:
        assert (ROOT/path).read_bytes() == (REPORT/'before'/path).read_bytes()
    before.save(REPORT / 'building_before.png')
    after.save(REPORT / 'building_after.png')
    after.resize((512,640), Image.Resampling.NEAREST).save(REPORT / 'preview.png')
    comparison = Image.new('RGB', (812,536), (242,240,235))
    draw = ImageDraw.Draw(comparison)
    for i,(label,im) in enumerate([('Bronze chimney',before),('Grey metal - existing palette 3',after)]):
        draw.text((12+i*400,8),label,fill=(30,30,35))
        comparison.paste(im.resize((384,480),Image.Resampling.NEAREST),(12+i*400,32))
    comparison.save(REPORT / 'comparison.png')
    print('PASS: 10 generated chimney tiles remapped to existing palette 3; no new tiles/metatiles/palettes; only chimney pixels changed.')
    print('Map, primary/shared palettes, roof/facade/windows and door animation untouched. Bronze version backed up.')

if __name__ == '__main__':
    main()

"""Warm-copper chimney colour swap; leave the shared palette and windows untouched."""
from pathlib import Path
from collections import defaultdict
import shutil
import struct
import json
import sys
from PIL import Image, ImageDraw
from chimney import render, words, TARGETS, ROOF_TILES, CHIMNEY
from refine import tile

ROOT = Path(__file__).resolve().parents[2]
DEST = ROOT / 'data/tilesets/secondary/fallarbor_cedar'
SOURCE = ROOT / 'data/tilesets/secondary/fallarbor'
PRIMARY = ROOT / 'data/tilesets/primary/general'
REPORT = Path(__file__).resolve().parent / 'copper'
COPPER = {1: 1, 2: 7, 3: 8, 4: 12, 5: 8, 6: 11, 7: 12, 8: 12, 9: 4, 10: 2, 14: 12}

def main():
    layout = next(l for l in json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts'] if l['id'] == 'LAYOUT_WURRENTEST')
    assert layout['secondary_tileset'] == 'gTileset_FallarborCedar'
    blocks = words(ROOT / layout['blockdata_filepath'])
    oldsheet = Image.open(DEST / 'tiles.png')
    source = Image.open(SOURCE / 'tiles.png')
    sheet = oldsheet.copy()
    previous = words(DEST / 'metatiles.bin')
    entries = previous.copy()
    original = words(SOURCE / 'metatiles.bin')
    refs = defaultdict(set)
    for i, e in enumerate(entries):
        refs[e & 1023].add(512 + i//8)
    allrefs = set(refs) | {e & 1023 for e in words(PRIMARY / 'metatiles.bin')}
    free = [i for i in range(1, min(504, oldsheet.width * oldsheet.height // 64))
            if i+512 not in allrefs and not any(tile(oldsheet, i).get_flattened_data())]
    changed = {}
    allocations = {}
    for mid in sorted(TARGETS):
        for off in range(8):
            address = (mid-512)*8+off
            old = entries[address]
            if old >> 12 != 7:
                continue
            tid = original[address] & 1023
            if tid in ROOF_TILES:
                continue
            pixels = list(tile(source, tid-512).get_flattened_data())
            current = list(tile(oldsheet, (old & 1023)-512).get_flattened_data())
            assert current == [CHIMNEY.get(i, i) for i in pixels], 'Unexpected user edits to chimney pixels'
            local = (old & 1023)-512
            # Only modify the generated chimney copies. Original nonblank art stays untouched.
            if any(tile(source, local).get_flattened_data()) or not refs[old & 1023] <= TARGETS:
                if tid not in allocations:
                    assert free
                    allocations[tid] = free.pop(0)
                local = allocations[tid]
                entries[address] = (old & 0xFC00) | (512+local)
            values = [COPPER.get(i, i) for i in pixels]
            assert local not in changed or changed[local] == values
            changed[local] = values
            im = tile(source, tid-512)
            im.putdata(values)
            sheet.paste(im, (local % 16 * 8, local // 16 * 8))
            assert [i == 0 for i in pixels] == [i == 0 for i in values]
            assert not any(i in (9, 10) for i in values), 'Blue remains in chimney'
    before = render(DEST, blocks, layout['width'])
    after = render(DEST, blocks, layout['width'], sheet, entries)
    if sys.argv[1:] == ['--preview']:
        after.resize((512,640), Image.Resampling.NEAREST).save('/private/tmp/wurrentest_copper_candidate.png')
        return
    assert not sys.argv[1:] and not REPORT.exists(), 'Never overwrite an existing backup'
    REPORT.mkdir()
    shutil.copytree(DEST, REPORT / 'before/secondary')
    preserved = ['data/layouts/wurrentest/map.bin', 'data/layouts/wurrentest/border.bin', 'data/layouts/layouts.json', 'graphics/door_anims/fallarbor_cedar.png']
    for path in preserved:
        target = REPORT / 'before' / path
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / path, target)
    for slot in range(oldsheet.width*oldsheet.height//64):
        if slot not in changed:
            assert list(tile(oldsheet, slot).get_flattened_data()) == list(tile(sheet, slot).get_flattened_data())
        else:
            assert not any(tile(source, slot).get_flattened_data()), 'Original nonblank tile changed'
    assert max(sheet.get_flattened_data()) < 16
    assert sheet.mode == 'P' and sheet.size == oldsheet.size
    sheet.save(DEST / 'tiles.png', optimize=False)
    (DEST / 'metatiles.bin').write_bytes(struct.pack('<'+'H'*len(entries), *entries))
    for saved in (REPORT / 'before/secondary').rglob('*'):
        if saved.is_file():
            rel = saved.relative_to(REPORT / 'before/secondary')
            if rel not in (Path('tiles.png'), Path('metatiles.bin')):
                assert saved.read_bytes() == (DEST / rel).read_bytes()
    for path in preserved:
        assert (ROOT/path).read_bytes() == (REPORT/'before'/path).read_bytes()
    for a, b in zip(previous, entries):
        assert a & 0xFC00 == b & 0xFC00
    before.save(REPORT / 'building_before.png')
    after.save(REPORT / 'building_after.png')
    after.resize((512,640), Image.Resampling.NEAREST).save(REPORT / 'preview.png')
    comparison = Image.new('RGB', (812,536), (242,240,235))
    draw = ImageDraw.Draw(comparison)
    for i,(label,im) in enumerate([('Previous blue-grey chimney',before),('Bronze / copper chimney',after)]):
        draw.text((12+i*400,8),label,fill=(30,30,35))
        comparison.paste(im.resize((384,480),Image.Resampling.NEAREST),(12+i*400,32))
    comparison.save(REPORT / 'comparison.png')
    print('PASS: chimney-only index swap; window/roof/facade/palette/map/door assets preserved. New blank tile slots:', sorted(allocations.values()))

if __name__ == '__main__':
    main()

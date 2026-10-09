"""Remap five individual 8x8 ground-edge tiles, preserving transparent overlays."""
from pathlib import Path
from collections import Counter
import json
import shutil
import struct
from PIL import Image, ImageDraw
from chimney import words, render, palette
from refine import tile
from straw_ground import REMAP, SHADES

ROOT = Path(__file__).resolve().parents[2]
DEST = ROOT / 'data/tilesets/secondary/fallarbor_cedar'
PRIMARY = ROOT / 'data/tilesets/primary/general'
SOURCE = ROOT / 'data/tilesets/secondary/fallarbor'
REPORT = Path(__file__).resolve().parent / 'straw_edges'
TARGET_TILES = {0x363, 0x364, 0x365, 0x373, 0x375}

def main():
    assert not REPORT.exists(), 'Never overwrite an existing backup'
    original = words(DEST / 'metatiles.bin')
    primary_met = words(PRIMARY / 'metatiles.bin')
    assert not any(e & 1023 in TARGET_TILES for e in primary_met)
    entries = original.copy()
    oldsheet = Image.open(DEST / 'tiles.png')
    assert oldsheet.mode == 'P' and oldsheet.width == 128
    sheet = oldsheet.copy()
    pal8 = palette(DEST / 'palettes/08.pal')
    assert all(pal8[i] == rgb for i, rgb in SHADES.items())
    refs = {e & 1023 for e in primary_met + original}
    free = [i for i in range(1, min(504, oldsheet.width * oldsheet.height // 64))
            if i+512 not in refs and not any(tile(oldsheet, i).get_flattened_data())]
    assert len(free) >= len(TARGET_TILES)
    copied = {}
    for tid in sorted(TARGET_TILES):
        im = tile(oldsheet, tid-512)
        values = list(im.get_flattened_data())
        assert set(values) <= {0, 10, 11, 12}
        remapped = [REMAP.get(i, i) for i in values]
        assert [i == 0 for i in values] == [i == 0 for i in remapped]
        local = free.pop(0)
        im.putdata(remapped)
        sheet.paste(im, (local % 16 * 8, local // 16 * 8))
        copied[tid] = local+512
    addresses = set()
    for address, e in enumerate(original):
        tid = e & 1023
        if tid in TARGET_TILES:
            assert e >> 12 == 11, 'Target edge is also used with another palette'
            entries[address] = (e & 0x0C00) | copied[tid] | 8 << 12
            addresses.add(address)
    assert {original[i] & 1023 for i in addresses} == TARGET_TILES
    layouts = json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']
    layout = next(l for l in layouts if l['name'] == 'WurrenTown_Layout')
    assert layout['primary_tileset'] == 'gTileset_General' and layout['secondary_tileset'] == 'gTileset_FallarborCedar'
    blocks = words(ROOT / layout['blockdata_filepath'])
    crop = [blocks[(1+y)*layout['width']+7+x] for y in range(11) for x in range(14)]
    before = render(DEST, crop, 14, oldsheet, original)
    after = render(DEST, crop, 14, sheet, entries)
    REPORT.mkdir()
    backup = REPORT / 'before'
    shutil.copytree(DEST, backup / 'secondary')
    preserved = ['data/layouts/layouts.json', 'graphics/door_anims/fallarbor_cedar.png']
    for l in layouts:
        if l['secondary_tileset'] == 'gTileset_FallarborCedar':
            preserved += [l['blockdata_filepath'], l['border_filepath']]
    for path in preserved:
        target = backup / path
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / path, target)
    sheet.save(DEST / 'tiles.png', optimize=False)
    (DEST / 'metatiles.bin').write_bytes(struct.pack('<'+'H'*len(entries), *entries))
    assert len(entries) == len(original) and sheet.mode == 'P' and sheet.size == oldsheet.size
    allocated = {tid-512 for tid in copied.values()}
    for i in range(oldsheet.width * oldsheet.height // 64):
        if i not in allocated:
            assert list(tile(oldsheet, i).get_flattened_data()) == list(tile(sheet, i).get_flattened_data())
        else:
            assert not any(tile(oldsheet, i).get_flattened_data())
    for i,(old,new) in enumerate(zip(original,entries)):
        assert old == new or i in addresses
        assert old & 0x0C00 == new & 0x0C00
        assert i not in addresses or new >> 12 == 8
    for oldtid,newtid in copied.items():
        old = list(tile(oldsheet, oldtid-512).get_flattened_data())
        new = list(tile(sheet, newtid-512).get_flattened_data())
        assert new == [REMAP.get(i, i) for i in old]
        assert [i == 0 for i in old] == [i == 0 for i in new]
    for saved in (backup/'secondary').rglob('*'):
        if saved.is_file():
            rel = saved.relative_to(backup/'secondary')
            if rel not in (Path('tiles.png'),Path('metatiles.bin')):
                assert saved.read_bytes() == (DEST/rel).read_bytes()
    for path in preserved:
        assert (ROOT/path).read_bytes() == (backup/path).read_bytes()
    before.save(REPORT/'map_before.png')
    after.save(REPORT/'map_after.png')
    after.resize((896,704),Image.Resampling.NEAREST).save(REPORT/'preview.png')
    comparison = Image.new('RGB',(1832,756),(242,240,235))
    draw = ImageDraw.Draw(comparison)
    for i,(label,im) in enumerate([('Straw ground with original grey edges',before),('Matching straw edge overlays',after)]):
        draw.text((12+i*916,8),label,fill=(30,30,35))
        comparison.paste(im.resize((896,704),Image.Resampling.NEAREST),(12+i*916,32))
    comparison.save(REPORT/'comparison.png')
    print('Copied global 8x8 tile IDs:', {hex(k):hex(v) for k,v in copied.items()})
    print('References updated:',len(addresses),'in',len({512+i//8 for i in addresses}),'metatiles')
    print('PASS: exact pixel-index swap; transparent masks, flips, layers, palettes, behaviours, maps, original graphics and door animation preserved.')

if __name__ == '__main__':
    main()

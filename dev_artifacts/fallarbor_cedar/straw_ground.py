"""Isolate the ash ground's three shades in spare palette-8 entries."""
from pathlib import Path
from collections import Counter
import json
import shutil
import struct
import sys
from PIL import Image, ImageDraw
from chimney import render, words, palette
from refine import tile

ROOT = Path(__file__).resolve().parents[2]
DEST = ROOT / 'data/tilesets/secondary/fallarbor_cedar'
PRIMARY = ROOT / 'data/tilesets/primary/general'
SOURCE = ROOT / 'data/tilesets/secondary/fallarbor'
REPORT = Path(__file__).resolve().parent / 'straw_ground'
SHADES = {5: (200, 184, 128), 6: (224, 208, 160), 7: (168, 152, 96)}
REMAP = {11: 5, 10: 6, 12: 7}

def prepare():
    original = words(DEST / 'metatiles.bin')
    entries = original.copy()
    oldsheet = Image.open(DEST / 'tiles.png')
    assert oldsheet.mode == 'P' and oldsheet.width == 128
    sheet = oldsheet.copy()
    primary_sheet = Image.open(PRIMARY / 'tiles.png')
    primary_met = words(PRIMARY / 'metatiles.bin')
    used8 = set()
    for e in primary_met + original:
        if e >> 12 == 8:
            tid = e & 1023
            used8.update(tile(primary_sheet if tid < 512 else oldsheet, tid % 512).get_flattened_data())
    assert not set(SHADES) & used8, 'Requested palette entries are already used'
    oldpal = palette(DEST / 'palettes/08.pal')
    newpal = oldpal.copy()
    for index, colour in SHADES.items():
        newpal[index] = colour
    ground = tile(oldsheet, 0x210-512)
    assert Counter(ground.get_flattened_data()) == Counter({11: 52, 10: 8, 12: 4})
    refs = {e & 1023 for e in primary_met + original}
    free = [i for i in range(1, min(504, sheet.width * sheet.height // 64))
            if i+512 not in refs and not any(tile(oldsheet, i).get_flattened_data())]
    assert free, 'No safe blank tile slots'
    slot = free[0]
    remapped = ground.copy()
    remapped.putdata([REMAP[i] for i in ground.get_flattened_data()])
    sheet.paste(remapped, (slot % 16 * 8, slot // 16 * 8))
    addresses = [i for i, e in enumerate(original) if (e & 1023) == 0x210 and e >> 12 == 11]
    assert addresses and all((0x218-512)*8+i in addresses for i in range(4))
    for address in addresses:
        entries[address] = (original[address] & 0x0C00) | (512+slot) | 8 << 12
    return original, entries, oldsheet, sheet, oldpal, newpal, slot, addresses

def preview(original, entries, oldsheet, sheet, oldpal, newpal, output):
    layouts = json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']
    layout = next(l for l in layouts if l['name'] == 'WurrenTown_Layout')
    assert layout['primary_tileset'] == 'gTileset_General' and layout['secondary_tileset'] == 'gTileset_FallarborCedar'
    blocks = words(ROOT / layout['blockdata_filepath'])
    x0, y0, width, height = 7, 1, 14, 11
    crop = [blocks[(y0+y)*layout['width']+x0+x] for y in range(height) for x in range(width)]
    before = render(DEST, crop, width, oldsheet, original, {8: oldpal})
    after = render(DEST, crop, width, sheet, entries, {8: newpal})
    after.resize((896,704), Image.Resampling.NEAREST).save(output)
    return before, after

def main():
    original, entries, oldsheet, sheet, oldpal, newpal, slot, addresses = prepare()
    if sys.argv[1:] == ['--preview']:
        preview(original, entries, oldsheet, sheet, oldpal, newpal, '/private/tmp/wurrentest_straw_ground_candidate.png')
        print('Preview only:',len(addresses),'bare-ground references; one blank tile slot',slot)
        return
    assert not sys.argv[1:] and not REPORT.exists(), 'Never overwrite an existing backup'
    REPORT.mkdir()
    backup = REPORT / 'before'
    shutil.copytree(DEST, backup / 'secondary')
    layouts = json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']
    preserved = ['data/layouts/layouts.json', 'graphics/door_anims/fallarbor_cedar.png']
    for layout in layouts:
        if layout['secondary_tileset'] == 'gTileset_FallarborCedar':
            preserved += [layout['blockdata_filepath'], layout['border_filepath']]
    for path in preserved:
        target = backup / path
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / path, target)
    # Palette 8 is changed separately with apply_patch after this guarded binary conversion.
    sheet.save(DEST / 'tiles.png', optimize=False)
    (DEST / 'metatiles.bin').write_bytes(struct.pack('<'+'H'*len(entries), *entries))
    assert len(entries) == len(original) and sheet.size == oldsheet.size
    for i in range(sheet.width * sheet.height // 64):
        if i != slot:
            assert list(tile(sheet,i).get_flattened_data()) == list(tile(oldsheet,i).get_flattened_data())
    for i,(old,new) in enumerate(zip(original,entries)):
        assert old & 0x0C00 == new & 0x0C00
        assert old == new or i in addresses
    for path in preserved:
        assert (ROOT/path).read_bytes() == (backup/path).read_bytes()
    before, after = preview(original, entries, oldsheet, sheet, oldpal, newpal, REPORT/'preview.png')
    before.save(REPORT/'map_before.png')
    after.save(REPORT/'map_after.png')
    comparison = Image.new('RGB',(1832,756),(242,240,235))
    draw = ImageDraw.Draw(comparison)
    for i,(label,im) in enumerate([('Original ashy ground',before),('Sun-dried straw - isolated palette-8 shades',after)]):
        draw.text((12+i*916,8),label,fill=(30,30,35))
        comparison.paste(im.resize((896,704),Image.Resampling.NEAREST),(12+i*916,32))
    comparison.save(REPORT/'comparison.png')
    print('Ground tile local slot:',slot,'; references updated:',len(addresses),'; metatiles:',len({512+i//8 for i in addresses}))
    print('PASS: original pixels preserved, no metatile slots added, map blocks/attributes/doors unchanged.')

if __name__ == '__main__':
    main()

"""Separate colour roles without moving pixels or editing original assets."""
from pathlib import Path
import shutil
import struct
import sys
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
DEST = ROOT / 'data/tilesets/secondary/fallarbor_cedar'
REPORT = Path(__file__).resolve().parent / 'refined'
PRIMARY = ROOT / 'data/tilesets/primary/general'

ROOF = {5: 8, 6: 11, 7: 12, 8: 12, 11: 7, 12: 8, 13: 11, 14: 12}
FACADE = {5: 8, 6: 11, 7: 12, 8: 12, 11: 14, 12: 13, 13: 13, 14: 4}
WINDOW = {5: 5, 6: 5, 7: 6, 8: 12, 11: 14, 12: 13, 13: 13, 14: 4}
DOOR = {5: 8, 6: 11, 7: 12, 8: 12, 11: 14, 12: 14, 13: 13, 14: 4}

def remap_pixels(pixels, role):
    values = []
    for position, index in enumerate(pixels):
        mapping = {'roof': ROOF, 'facade': FACADE, 'door': DOOR,
                   'window_top': WINDOW if position // 8 >= 5 else FACADE,
                   'window_bottom': WINDOW}[role]
        values.append(mapping.get(index, index))
    return values

def words(path):
    data = path.read_bytes()
    return list(struct.unpack('<' + 'H' * (len(data) // 2), data))

def tile(sheet, index):
    return sheet.crop((index % 16 * 8, index // 16 * 8, index % 16 * 8 + 8, index // 16 * 8 + 8))

def main():
    rebuilding = sys.argv[1:] == ['--rebuild-from-snapshot']
    if not rebuilding:
        assert not REPORT.exists(), 'Never overwrite an existing revision backup'
        assert not (ROOT / 'graphics/door_anims/fallarbor_cedar.png').exists()
        REPORT.mkdir()
        shutil.copytree(DEST, REPORT / 'before/secondary')
        for name in ('building_after.png', 'preview.png', 'comparison.png', 'door_animation_preview.png'):
            shutil.copy2(REPORT.parent / name, REPORT / 'before' / name)
        shutil.copy2(ROOT / 'src/field_door.c', REPORT / 'before/field_door.c')
    snapshot = REPORT / 'before/secondary'
    oldsheet = Image.open(snapshot / 'tiles.png')
    assert oldsheet.mode == 'P' and oldsheet.width == 128
    sheet = oldsheet.copy()
    original = words(snapshot / 'metatiles.bin')
    entries = original.copy()
    references = {e & 1023 for e in original + words(PRIMARY / 'metatiles.bin')}
    free = [i for i in range(1, min(504, sheet.width * sheet.height // 64))
            if i + 512 not in references and not any(tile(oldsheet, i).get_flattened_data())]
    blocks = words(ROOT / 'data/layouts/wurrentest/map.bin')
    allocated = {}
    changed_entries = {}
    for position, block in enumerate(blocks):
        mid = block & 1023
        assert mid >= 512
        for off in range(8):
            address = (mid - 512) * 8 + off
            entry = original[address]
            if entry >> 12 != 7:
                continue
            x = position % 5 * 16 + off % 2 * 8
            y = position // 5 * 16 + off % 4 // 2 * 8
            role = 'roof' if y < 40 else ('door' if 32 <= x < 48 else 'facade')
            if role == 'facade' and entry & 1023 in (0x2AC, 0x2BC):
                role = 'window_top' if entry & 1023 == 0x2AC else 'window_bottom'
            key = (entry & 1023, role)
            if key not in allocated:
                assert entry & 1023 >= 512
                remapped = tile(oldsheet, (entry & 1023) - 512)
                remapped.putdata(remap_pixels(remapped.get_flattened_data(), role))
                assert free, 'No safe unused tile slots left'
                local = free.pop(0)
                sheet.paste(remapped, (local % 16 * 8, local // 16 * 8))
                allocated[key] = local + 512
            replacement = (entry & 0xFC00) | allocated[key]
            assert address not in changed_entries or changed_entries[address] == replacement
            changed_entries[address] = replacement
            entries[address] = replacement
    # Recolouring changes indices only; transparency and all original used tiles stay intact.
    for (oldtid, role), newtid in allocated.items():
        old = tile(oldsheet, oldtid - 512)
        new = tile(sheet, newtid - 512)
        assert [i == 0 for i in old.get_flattened_data()] == [i == 0 for i in new.get_flattened_data()]
    used_slots = {tid - 512 for tid in allocated.values()}
    for i in range(sheet.width * sheet.height // 64):
        if i not in used_slots:
            assert list(tile(sheet, i).get_flattened_data()) == list(tile(oldsheet, i).get_flattened_data())
    assert max(sheet.get_flattened_data()) < 16
    sheet.save(DEST / 'tiles.png', optimize=False)
    (DEST / 'metatiles.bin').write_bytes(struct.pack('<' + 'H' * len(entries), *entries))
    animation = Image.open(ROOT / 'graphics/door_anims/fallarbor_light_roof.png').copy()
    for y in range(animation.height):
        mapping = ROOF if y % 32 < 8 else DOOR
        for x in range(animation.width):
            index = animation.getpixel((x, y))
            animation.putpixel((x, y), mapping.get(index, index))
    animation.save(ROOT / 'graphics/door_anims/fallarbor_cedar.png', optimize=False)
    print('Allocated existing unused tile slots:', sorted(used_slots))
    print('No new palette slots, metatile slots, or sheet dimensions needed.')

if __name__ == '__main__':
    main()

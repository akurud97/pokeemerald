"""Read-only audit of runtime callbacks, copied frames, dynamic slots and doors."""
from pathlib import Path
import re
from PIL import Image

root = Path(__file__).resolve().parents[2]
headers = (root / 'src/data/tilesets/headers.h').read_text()
doors = (root / 'src/field_door.c').read_text()
callbacks = (root / 'src/tileset_anims.c').read_text()
pairs = [
    ('Dewford', 'DewfordTeal', 'dewford', 'dewford_teal', [(170, 176)]),
    ('Mauville', 'MauvilleBrick', 'mauville', 'mauville_brick', [(96, 160)]),
    ('Slateport', 'SlateportCharcoal', 'slateport', 'slateport_charcoal', [(224, 228)]),
    ('Lavaridge', 'LavaridgeForest', 'lavaridge', 'lavaridge_forest', [(160, 164), (288, 296)]),
    ('Petalburg', 'PetalburgLavender', 'petalburg', 'petalburg_lavender', []),
    ('Mossdeep', 'MossdeepOrange', 'mossdeep', 'mossdeep_orange', []),
    ('Fallarbor', 'FallarborCedar', 'fallarbor', 'fallarbor_cedar', []),
]

def callback(name):
    block = re.search(r'const struct Tileset gTileset_' + name + r'\s*=\s*\{(.*?)\};', headers, re.S)
    assert block, name
    return re.search(r'\.callback\s*=\s*(\w+)', block[1])[1]

def door_ids(name):
    return set(re.findall(r'\{(\w+)\s*,\s*&gTileset_' + name + r'\s*,', doors))

def tile(image, index):
    columns = image.width // 8
    x, y = index % columns * 8, index // columns * 8
    return image.crop((x, y, x + 8, y + 8)).tobytes()

for source, copy, source_folder, copy_folder, ranges in pairs:
    assert callback(source) == callback(copy), copy
    assert door_ids(source) <= door_ids(copy), copy + ': missing original door registrations'
    src = root / 'data/tilesets/secondary' / source_folder
    dst = root / 'data/tilesets/secondary' / copy_folder
    frames = list((src / 'anim').rglob('*.png')) if (src / 'anim').exists() else []
    for file in frames:
        assert file.read_bytes() == (dst / file.relative_to(src)).read_bytes(), str(file)
    source_image = Image.open(src / 'tiles.png')
    copy_image = Image.open(dst / 'tiles.png')
    assert source_image.mode == copy_image.mode == 'P'
    for start, end in ranges:
        for index in range(start, end):
            assert tile(source_image, index) == tile(copy_image, index), f'{copy}: animated slot {index}'
    if not ranges:
        init = re.search(r'void ' + callback(copy) + r'\(void\)\s*\{(.*?)\}', callbacks, re.S)
        assert 'sSecondaryTilesetAnimCallback = NULL' in init[1], copy
    print(f'{copy}: callback, {len(frames)} copied frames, dynamic slots and doors OK')

assert callback('Castula') == 'InitTilesetAnim_Castula'
for file in re.findall(r'INCGFX_U16\("(data/tilesets/secondary/castula/anim/[^"]+)"', callbacks):
    assert (root / file).is_file(), file
assert door_ids('Castula'), 'Castula custom doors missing'
for file, current in [('headers.h', 'src/data/tilesets/headers.h'),
                      ('tileset_anims.c', 'src/tileset_anims.c'),
                      ('field_door.c', 'src/field_door.c')]:
    assert (root / 'dev_artifacts/tileset_animation_audit/before' / file).read_bytes() == (root / current).read_bytes()
print('PASS: runtime assets intact; no game-source changes during this fix')

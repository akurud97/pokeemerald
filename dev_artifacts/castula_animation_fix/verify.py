"""Read-only regression checks for Castula's fountain-only animation fix."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]
BACKUP = Path(__file__).resolve().parent / 'before'
before = (BACKUP / 'src/tileset_anims.c').read_text()
after = (ROOT / 'src/tileset_anims.c').read_text()

def function(text, name):
    match = re.search(r'(?:static )?void ' + name + r'\([^;]*?\)\n\{.*?\n\}', text, re.S)
    assert match, name
    return match[0]

# No changed assets/maps, palettes, doors or tileset headers. Removed C bindings
# don't delete the old water PNGs; they're recoverable in the backup as well.
for relative in ['data/tilesets/secondary/castula', 'data/layouts/CastulaCity',
                 'data/layouts/Route112', 'data/layouts/HyadesRoute8']:
    saved_folder = BACKUP / relative
    if not saved_folder.exists(): continue
    for saved in saved_folder.rglob('*'):
        if saved.is_file():
            assert saved.read_bytes() == (ROOT / saved.relative_to(BACKUP)).read_bytes(), str(saved)
for relative in ['src/field_door.c', 'src/data/tilesets/headers.h', 'data/layouts/layouts.json']:
    assert (ROOT / relative).read_bytes() == (BACKUP / relative).read_bytes(), relative
for saved in (BACKUP / 'data/layouts').rglob('*.bin'):
    assert saved.read_bytes() == (ROOT / saved.relative_to(BACKUP)).read_bytes(), str(saved)

assert 'QueueAnimTiles_Castula_WindyWater' not in after
assert 'sTilesetAnims_Castula_WindyWater' not in after
callback = function(after, 'TilesetAnim_Castula')
assert 'if (timer % 8 == 0)' in callback
assert re.findall(r'QueueAnimTiles_\w+\([^;]+\);', callback) == ['QueueAnimTiles_Castula_Fountain(timer / 8);']
for name in ['InitTilesetAnim_Castula', 'QueueAnimTiles_Castula_Fountain',
             'TilesetAnim_Rustboro', 'QueueAnimTiles_Rustboro_WindyWater', 'QueueAnimTiles_Rustboro_Fountain']:
    assert function(before, name) == function(after, name), name

# Reconstruct the exact allowed C edits; catch any unintended global changes.
expected = before.replace('static void QueueAnimTiles_Castula_WindyWater(u16, u8);\n', '')
start = expected.index('static const u16 sTilesetAnims_Castula_WindyWater_Frame0[]')
end = expected.index('static const u16 sTilesetAnims_Castula_Fountain_Frame0[]', start)
expected = expected[:start] + expected[end:]
expected = expected.replace(function(before, 'TilesetAnim_Castula'), callback)
expected = expected.replace(function(before, 'QueueAnimTiles_Castula_WindyWater') + '\n\n', '')
assert expected == after, 'Unrelated runtime code changed'
print('PASS: Castula buildings never receive water writes; fountain callback/timing unchanged')
print('PASS: all assets/maps/door registrations preserved; original Rustboro and all other runtime code unchanged')

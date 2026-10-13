"""Guarded one-shot import; run from the repository root."""
from pathlib import Path
from PIL import Image
import json
import shutil
import struct

root = Path(__file__).resolve().parents[2]
out = Path(__file__).resolve().parent
src = root / 'data/tilesets/secondary/mauville'
dst = root / 'data/tilesets/secondary/wurren'
assert not (out / 'before').exists(), 'Already imported; do not rerun.'
old_m = (dst / 'metatiles.bin').read_bytes()
old_a = (dst / 'metatile_attributes.bin').read_bytes()
source_m = (src / 'metatiles.bin').read_bytes()
source_a = (src / 'metatile_attributes.bin').read_bytes()
mapping = {0x204: 0x253, 0x205: 0x254}
tile_mapping = {0x24D: 0x24B, 0x25D: 0x24C}
metatiles = list(struct.iter_unpack('<8H', old_m))
used_tiles = {v & 0x3FF for mt in metatiles for v in mt}
assert used_tiles.isdisjoint(tile_mapping.values())
for target, duplicate in [(0x253, 0x250), (0x254, 0x252)]:
    assert metatiles[target - 512] == metatiles[duplicate - 512]
    assert old_a[(target-512)*2:(target-511)*2] == old_a[(duplicate-512)*2:(duplicate-511)*2]
layouts = json.loads((root / 'data/layouts/layouts.json').read_text())['layouts']
for layout in layouts:
    if layout.get('secondary_tileset') == 'gTileset_Wurren':
        assert layout['primary_tileset'] == 'gTileset_General'
        for key in ['blockdata_filepath', 'border_filepath']:
            assert {v[0] & 0x3FF for v in struct.iter_unpack('<H', (root / layout[key]).read_bytes())}.isdisjoint(mapping.values())

def box(tile):
    i = tile - 512
    return (i % 16 * 8, i // 16 * 8, i % 16 * 8 + 8, i // 16 * 8 + 8)

source_image = Image.open(src / 'tiles.png')
image = Image.open(dst / 'tiles.png')
old_image = image.copy()
assert source_image.mode == image.mode == 'P'
for source, target in tile_mapping.items():
    image.paste(source_image.crop(box(source)), box(target))
new_m, new_a = bytearray(old_m), bytearray(old_a)
for source, target in mapping.items():
    values = struct.unpack_from('<8H', source_m, (source - 512) * 16)
    remapped = [(v & ~0x3FF) | tile_mapping.get(v & 0x3FF, v & 0x3FF) for v in values]
    struct.pack_into('<8H', new_m, (target - 512) * 16, *remapped)
    new_a[(target-512)*2:(target-511)*2] = source_a[(source-512)*2:(source-511)*2]
    assert struct.unpack_from('<H', new_a, (target-512)*2)[0] == 7

# All other metatiles, attributes and referenced graphics stay intact.
for i, mt in enumerate(metatiles):
    if i + 512 not in mapping.values():
        assert new_m[i*16:(i+1)*16] == old_m[i*16:(i+1)*16]
        assert new_a[i*2:(i+1)*2] == old_a[i*2:(i+1)*2]
for i in range(512, 512 + image.width * image.height // 64):
    if i not in tile_mapping.values():
        assert old_image.crop(box(i)).tobytes() == image.crop(box(i)).tobytes()

def render(data, mt_id, tiles):
    result = Image.new('RGBA', (16, 16))
    palette = [tuple(map(int, line.split())) for line in (root / 'data/tilesets/primary/general/palettes/02.pal').read_text().splitlines()[3:19]]
    for n, value in enumerate(struct.unpack_from('<8H', data, (mt_id-512)*16)):
        if value == 0:
            continue
        assert value >> 12 == 2
        tile = tiles.crop(box(value & 0x3FF))
        pixels = list(tile.get_flattened_data())
        rgba = Image.new('RGBA', (8, 8))
        rgba.putdata([palette[p] + (255 if p else 0,) for p in pixels])
        if value & 0x400:
            rgba = rgba.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
        if value & 0x800:
            rgba = rgba.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
        result.alpha_composite(rgba, ((n % 4 % 2)*8, (n % 4 // 2)*8))
    return result

preview = Image.new('RGBA', (32, 32))
for i, (source, target) in enumerate(mapping.items()):
    a, b = render(source_m, source, source_image), render(new_m, target, image)
    assert a.tobytes() == b.tobytes()
    preview.paste(a, (i*16, 0))
    preview.paste(b, (i*16, 16))
(out / 'before').mkdir()
for name in ['tiles.png', 'metatiles.bin', 'metatile_attributes.bin']:
    shutil.copy2(dst / name, out / 'before' / name)
image.save(dst / 'tiles.png', bits=4, optimize=True)
(dst / 'metatiles.bin').write_bytes(new_m)
(dst / 'metatile_attributes.bin').write_bytes(new_a)
assert Image.open(dst / 'tiles.png').tobytes() == image.tobytes()
preview.resize((256, 256), Image.Resampling.NEAREST).save(out / 'comparison.png')
(out / 'manifest.json').write_text(json.dumps({
    'metatiles': {hex(k): hex(v) for k, v in mapping.items()},
    'tiles': {hex(k): hex(v) for k, v in tile_mapping.items()},
    'attribute': '0x0007 (MB_SHORT_GRASS, normal layer)',
    'palette': 'General primary palette 2',
    'animations': 'No tileset animation; existing FLDEFF_SHORT_GRASS is selected by behaviour.',
    'replaced_duplicates': {'0x253': '0x250', '0x254': '0x252'},
}, indent=2) + '\n')
print('PASS: imported 0x204 -> 0x253 and 0x205 -> 0x254; pixel, attribute and preservation checks passed.')

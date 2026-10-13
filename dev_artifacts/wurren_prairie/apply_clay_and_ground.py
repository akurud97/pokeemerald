"""Apply approved clay road and replace matching bottom-layer ground."""
from pathlib import Path
from PIL import Image
import struct

root = Path(__file__).resolve().parents[2]
out = Path(__file__).resolve().parent
p = root / 'data/tilesets/secondary/wurren'
old_m = (p / 'metatiles.bin').read_bytes()
m = bytearray(old_m)
attrs = (p / 'metatile_attributes.bin').read_bytes()
image = Image.open(p / 'tiles.png')
old_image = image.copy()
palette_path = p / 'palettes/08.pal'
old_palette = palette_path.read_text()
palette = old_palette.splitlines()
targets = {0x2E8, 0x2E9, 0x2EA, 0x2F0, 0x2F1, 0x2F2, 0x2F8, 0x2F9, 0x2FA}
graphics = dict(zip([0x2C4, 0x2C5, 0x2C6, 0x2D4, 0x2D5, 0x2D6], [0x210, 0x21A, 0x21D, 0x21E, 0x226, 0x227]))
entries = list(struct.iter_unpack('<8H', old_m))
used = {v & 1023 for mt in entries for v in mt}
assert used.isdisjoint(graphics.values()), 'Destination graphic slots are occupied.'

def box(t):
    i = t - 512
    return (i % 16*8, i // 16*8, i % 16*8+8, i // 16*8+8)

# Palette entries 9-11 are unreferenced by all current Wurren graphics.
for mt in entries:
    for v in mt:
        if v >> 12 == 8:
            assert v & 1023 >= 512
            assert set(image.crop(box(v & 1023)).get_flattened_data()).isdisjoint({9, 10, 11})
for i, colour in zip([9, 10, 11], [(216, 184, 152), (192, 160, 128), (168, 136, 104)]):
    palette[i+3] = ' '.join(map(str, colour))
for source, dest in graphics.items():
    tile = image.crop(box(source))
    tile.putdata([{1:9, 2:10, 3:11}.get(v, v) for v in tile.get_flattened_data()])
    image.paste(tile, box(dest))

ground = entries[0x218-512][:4]
replacement = entries[0x254-512][:4]
assert ground == (0x8259,) * 4
assert replacement == (0x724B, 0x724B, 0x724C, 0x724C)
ground_changes = []
quadrants = 0
for index, entry in enumerate(entries):
    mt = index + 512
    values = list(entry)
    if mt != 0x218:
        for n in range(4):
            # Preserve the existing quadrant's flips on the replacement graphic.
            if values[n] & 0xF3FF == 0x8259:
                values[n] = replacement[n] | (values[n] & 0xC00)
                quadrants += 1
        if tuple(values[:4]) != entry[:4]: ground_changes.append(mt)
    if mt in targets:
        for n in range(4, 8):
            v = values[n]
            assert v >> 12 == 8 and (v & 1023) in graphics
            values[n] = (v & ~1023) | graphics[v & 1023]
    struct.pack_into('<8H', m, index*16, *values)

# Verify the exact scope before writing: behaviours, nonmatching bottom
# quadrants and every foreground outside the nine road metatiles stay intact.
for index, entry in enumerate(entries):
    mt = index + 512
    new = struct.unpack_from('<8H', m, index*16)
    if mt not in targets: assert new[4:] == entry[4:]
    for n in range(4):
        if mt == 0x218 or entry[n] & 0xF3FF != 0x8259: assert new[n] == entry[n]
for t in range(512, 960):
    if t not in graphics.values(): assert image.crop(box(t)).tobytes() == old_image.crop(box(t)).tobytes()
for i in range(16):
    if i not in [9, 10, 11]: assert palette[i+3] == old_palette.splitlines()[i+3]

image.save(p / 'tiles.png', bits=4, optimize=True)
(p / 'metatiles.bin').write_bytes(m)
palette_path.write_text('\n'.join(palette) + '\n')
assert Image.open(p / 'tiles.png').tobytes() == image.tobytes()
assert (p / 'metatile_attributes.bin').read_bytes() == attrs

# Render the applied assets using the preview renderer, without regenerating
# the earlier mockups or adding any proposed colour overrides.
preview_source = (out / 'patch_mockups.py').read_text().split('font = ImageFont.truetype')[0]
scope = {'__file__': str(out / 'patch_mockups.py')}
exec(compile(preview_source, 'preview_renderer', 'exec'), scope)
context = Image.new('RGB', (192, 128))
for y in range(8):
    for x in range(12):
        mt = scope['map_ids'][(y+6)*scope['layout']['width']+x+9]
        context.paste(scope['render'](mt, None), (x*16, y*16))
context.resize((768, 512), Image.Resampling.NEAREST).save(out / 'applied_clay_road.png')
print(f'PASS: weathered-clay road applied to 9 metatiles; golden ground replaced in {len(ground_changes)} metatiles ({quadrants} quadrants).')
print('PASS: 0x218, behaviours, unrelated foregrounds, existing graphic pixels and used palette colours preserved.')

"""Render proposed palette remaps without modifying game assets."""
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont
import struct

root = Path(__file__).resolve().parents[2]
out = Path(__file__).resolve().parent
dst = root / 'data/tilesets/secondary/wurren'
tiles = Image.open(dst / 'tiles.png')
data = (dst / 'metatiles.bin').read_bytes()
variants = [
    ('A - Golden wheat', 7, [1, 2, 3, 4], 'Warm gold with deeper ochre shadows'),
    ('B - Dry prairie', 8, [6, 5, 7, 8], 'Muted straw with olive-brown shadows'),
]
font_path = Path('C:/Windows/Fonts/segoeui.ttf')
font = ImageFont.truetype(str(font_path), 22)
small = ImageFont.truetype(str(font_path), 16)
sheet = Image.new('RGB', (840, 420), '#f4f0e5')
draw = ImageDraw.Draw(sheet)
draw.text((24, 12), 'Wurren shortgrass - palette mockups', font=font, fill='#373124')
for column, (name, palette_id, indices, caption) in enumerate(variants):
    palette = [tuple(map(int, line.split())) for line in (dst / 'palettes' / f'{palette_id:02}.pal').read_text().splitlines()[3:19]]
    remap = dict(zip([12, 13, 14, 15], indices))
    samples = []
    for mt_id in [0x253, 0x254]:
        sample = Image.new('RGB', (16, 16))
        for n, value in enumerate(struct.unpack_from('<8H', data, (mt_id-512)*16)[:4]):
            i = (value & 1023) - 512
            tile = tiles.crop((i%16*8, i//16*8, i%16*8+8, i//16*8+8))
            rgb = Image.new('RGB', (8, 8))
            rgb.putdata([palette[remap[p]] for p in tile.get_flattened_data()])
            if value & 0x400: rgb = rgb.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
            if value & 0x800: rgb = rgb.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
            sample.paste(rgb, (n%2*8,n//2*8))
        samples.append(sample)
    patch = Image.new('RGB', (96, 64))
    for y in range(4):
        for x in range(6): patch.paste(samples[(x+y)%2],(x*16,y*16))
    patch.save(out / f'option_{name[0].lower()}_native.png')
    x = 24 + column*416
    draw.text((x, 55), name, font=font, fill='#373124')
    draw.text((x, 87), f'Existing palette {palette_id} - no palette edits', font=small, fill='#665e4d')
    sheet.paste(patch.resize((384,256), Image.Resampling.NEAREST),(x,120))
    draw.text((x, 385), caption, font=small, fill='#665e4d')
sheet.save(out / 'options.png')
print('Created two mockups using existing palettes 7 and 8. Game assets untouched.')

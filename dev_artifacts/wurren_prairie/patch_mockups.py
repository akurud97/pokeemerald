"""Explore Wurren's 3x3 patch around 0x2F1 without asset edits."""
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont
import json
import struct

root = Path(__file__).resolve().parents[2]
out = Path(__file__).resolve().parent
secondary = root / 'data/tilesets/secondary/wurren'
primary = root / 'data/tilesets/primary/general'
images = [Image.open(primary / 'tiles.png'), Image.open(secondary / 'tiles.png')]
mts = [list(struct.iter_unpack('<8H', (p / 'metatiles.bin').read_bytes())) for p in [primary, secondary]]
palettes = [[tuple(map(int, l.split())) for l in ((primary if i < 6 else secondary) / 'palettes' / f'{i:02}.pal').read_text().splitlines()[3:19]] for i in range(13)]
targets = [0x2E8, 0x2E9, 0x2EA, 0x2F0, 0x2F1, 0x2F2, 0x2F8, 0x2F9, 0x2FA]
variants = [
    ('Current', None, 'Original peach-straw patch'),
    ('A - Golden wheat', [palettes[7][i] for i in [1, 2, 3]], 'Existing palette 7; matches golden shortgrass'),
    ('B - Olive grass', [palettes[6][i] for i in [1, 2, 3]], 'Existing palette 6; fresh green highlights'),
    ('C - Dusty sage', [(208, 216, 160), (168, 184, 120), (128, 152, 88)], 'Custom colours in unused palette 8 entries'),
]
layout = next(l for l in json.loads((root / 'data/layouts/layouts.json').read_text())['layouts'] if l['name'] == 'WurrenTown_Layout')
map_ids = [v[0] & 1023 for v in struct.iter_unpack('<H', (root / layout['blockdata_filepath']).read_bytes())]

def render(mt, ramp):
    result = Image.new('RGB', (16, 16), palettes[0][0])
    for n, value in enumerate(mts[mt >= 512][mt - (512 if mt >= 512 else 0)]):
        tile_id, pal = value & 1023, value >> 12
        image = images[tile_id >= 512]
        tile_id -= 512 if tile_id >= 512 else 0
        columns = image.width // 8
        tile = image.crop((tile_id % columns * 8, tile_id // columns * 8, tile_id % columns * 8 + 8, tile_id // columns * 8 + 8))
        rgba = Image.new('RGBA', (8, 8))
        pixels = []
        for index in tile.get_flattened_data():
            colour = palettes[pal][index]
            if ramp and mt in targets and n >= 4 and pal == 8 and index in [1, 2, 3]:
                colour = ramp[index - 1]
            pixels.append(colour + (0 if n >= 4 and index == 0 else 255,))
        rgba.putdata(pixels)
        if value & 0x400: rgba = rgba.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
        if value & 0x800: rgba = rgba.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
        result.paste(rgba, ((n % 4 % 2)*8, (n % 4 // 2)*8), rgba)
    return result

font = ImageFont.truetype('C:/Windows/Fonts/segoeui.ttf', 23)
small = ImageFont.truetype('C:/Windows/Fonts/segoeui.ttf', 16)
sheet = Image.new('RGB', (1040, 800), '#f4f0e5')
draw = ImageDraw.Draw(sheet)
draw.text((24, 12), 'Wurren 0x2F1 and surrounding tiles - colour studies', font=font, fill='#373124')
for v, (title, ramp, caption) in enumerate(variants):
    x, y = 24 + (v % 2)*512, 56 + (v // 2)*368
    draw.text((x,y),title,font=font,fill='#373124')
    draw.text((x,y+32),caption,font=small,fill='#665e4d')
    patch = Image.new('RGB',(48,48))
    for i, mt in enumerate(targets): patch.paste(render(mt,ramp),(i%3*16,i//3*16))
    context = Image.new('RGB',(192,128))
    for yy in range(8):
        for xx in range(12):
            mt = map_ids[(yy+6)*layout['width']+xx+9]
            context.paste(render(mt,ramp),(xx*16,yy*16))
    sheet.paste(context.resize((384,256),Image.Resampling.NEAREST),(x,y+65))
    sheet.paste(patch.resize((96,96),Image.Resampling.NEAREST),(x+392,y+65))
    draw.text((x+394,y+170),'3 x 3',font=small,fill='#665e4d')
    draw.text((x,y+329),'Actual WurrenTown map excerpt',font=small,fill='#665e4d')
    context.save(out / f'patch_{v}_context.png')
sheet.save(out / 'patch_options.png')
print('Created current + three recolour mockups; game assets unchanged.')

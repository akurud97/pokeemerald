"""Render a warmer tall-grass proposal without changing game assets."""
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont
import json
import struct

out = Path(__file__).resolve().parent
base = (out / 'patch_mockups.py').read_text().split('font = ImageFont.truetype')[0]
base = base.replace('if ramp and mt in targets and n >= 4 and pal == 8 and index in [1, 2, 3]:', 'if ramp and pal == 6 and index in [1, 2, 3, 4]:')
scope = {'__file__': str(out / 'patch_mockups.py')}
exec(compile(base, 'grass_preview_renderer', 'exec'), scope)
layout = next(l for l in json.loads((scope['root'] / 'data/layouts/layouts.json').read_text())['layouts'] if l['name'] == 'CraterCanyon_Layout')
ids = [v[0] & 1023 for v in struct.iter_unpack('<H', (scope['root'] / layout['blockdata_filepath']).read_bytes())]
ramp = [(208,216,144), (168,184,104), (120,144,64), (64,80,32)]
sheet = Image.new('RGB', (1200, 476), '#f4f0e5')
draw = ImageDraw.Draw(sheet)
font = ImageFont.truetype('C:/Windows/Fonts/segoeui.ttf', 23)
small = ImageFont.truetype('C:/Windows/Fonts/segoeui.ttf', 17)
for column, (title, colours) in enumerate([('Current tall grass', None), ('Warmer olive / straw-green', ramp)]):
    context = Image.new('RGB', (384,256))
    for y in range(16):
        for x in range(24):
            mt = ids[(y+12)*layout['width']+x+15]
            context.paste(scope['render'](mt, colours), (x*16,y*16))
    x = 16 + column*592
    draw.text((x,12), title, font=font, fill='#373124')
    sheet.paste(context.resize((576,384), Image.Resampling.NEAREST), (x,52))
    context.save(out / f'olive_grass_{column}_native.png')
draw.text((16,448), 'Preview only: grass warms slightly; terrain, trees, buildings and water retain their current colours.', font=small, fill='#665e4d')
sheet.save(out / 'olive_grass_comparison.png')
print('Created current vs olive tall-grass preview. Game assets unchanged.')

"""Preview muted terrain colours for Wurren 0x279; no asset edits."""
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

out = Path(__file__).resolve().parent
base = (out / 'patch_mockups.py').read_text().split('font = ImageFont.truetype')[0]
# Override colours only on the selected terrain, using its original pixel ramp.
base = base.replace("if ramp and mt in targets and n >= 4 and pal == 8 and index in [1, 2, 3]:", "if ramp and mt == 0x279 and n < 4 and pal == 3 and index in [10, 11, 12, 13]:")
base = base.replace('colour = ramp[index - 1]', 'colour = ramp[index - 10]')
scope = {'__file__': str(out / 'patch_mockups.py')}
exec(compile(base, 'terrain_renderer', 'exec'), scope)
variants = [
    ('Current', None, 'Original pink-brown terrain'),
    ('A - Dusty tan', [(216,192,168),(184,160,136),(152,128,112),(128,104,88)], 'Custom ramp; muted tan, closest to the original'),
    ('B - Subdued ochre', [(216,192,152),(184,160,120),(152,128,88),(128,104,64)], 'Custom ramp; warmer golden-brown undertone'),
    ('C - Existing sand', [scope['palettes'][6][i] for i in [5,6,7,8]], 'Existing palette 6; yellower with deeper contrast'),
]
font = ImageFont.truetype('C:/Windows/Fonts/segoeui.ttf', 23)
small = ImageFont.truetype('C:/Windows/Fonts/segoeui.ttf', 16)
sheet = Image.new('RGB', (1040,800), '#f4f0e5')
draw = ImageDraw.Draw(sheet)
draw.text((24,12), 'Wurren 0x279 - less pink, more dusty earth', font=font, fill='#373124')
for v, (title,ramp,caption) in enumerate(variants):
    x,y=24+(v%2)*512,56+(v//2)*368
    draw.text((x,y),title,font=font,fill='#373124')
    draw.text((x,y+32),caption,font=small,fill='#665e4d')
    tile=scope['render'](0x279,ramp)
    patch=Image.new('RGB',(48,48))
    for yy in range(3):
        for xx in range(3):patch.paste(tile,(xx*16,yy*16))
    context=Image.new('RGB',(192,128))
    for yy in range(8):
        for xx in range(12):
            mt=scope['map_ids'][(yy+3)*scope['layout']['width']+xx]
            context.paste(scope['render'](mt,ramp),(xx*16,yy*16))
    sheet.paste(context.resize((384,256),Image.Resampling.NEAREST),(x,y+65))
    sheet.paste(patch.resize((96,96),Image.Resampling.NEAREST),(x+392,y+65))
    draw.text((x+394,y+170),'0x279',font=small,fill='#665e4d')
    draw.text((x,y+329),'Map preview: only 0x279 recoloured',font=small,fill='#665e4d')
    tile.save(out / f'terrain_279_{v}_native.png')
sheet.save(out / 'terrain_279_options.png')
print('Created original plus three mockups. Game assets unchanged.')

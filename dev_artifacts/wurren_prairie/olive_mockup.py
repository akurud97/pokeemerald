"""Preview a custom olive-straw ramp; leave game assets unchanged."""
from pathlib import Path
from PIL import Image, ImageDraw, ImageFont

out = Path(__file__).resolve().parent
original = Image.open(out / 'option_b_native.png').convert('RGB')
old = [(224, 208, 160), (200, 184, 128), (168, 152, 96), (136, 120, 72)]
# GBA-representable RGB colours, with restrained green and golden highlights.
new = [(216, 216, 144), (184, 192, 112), (144, 160, 80), (112, 128, 56)]
remap = dict(zip(old, new))
olive = Image.new('RGB', original.size)
olive.putdata([remap[p] for p in original.get_flattened_data()])
olive.save(out / 'option_c_native.png')
sheet = Image.new('RGB', (840, 420), '#f4f0e5')
draw = ImageDraw.Draw(sheet)
font = ImageFont.truetype('C:/Windows/Fonts/segoeui.ttf', 22)
small = ImageFont.truetype('C:/Windows/Fonts/segoeui.ttf', 16)
draw.text((24, 12), 'Wurren shortgrass - a little more olive', font=font, fill='#373124')
for x, patch, title, detail, caption in [
    (24, original, 'B - Dry prairie', 'Previous mockup: existing palette 8', 'Muted straw with brown-olive shadows'),
    (440, olive, 'C - Olive prairie', 'Proposed custom palette colours', 'Greener olive shadows, pale straw highlights'),
]:
    draw.text((x,55),title,font=font,fill='#373124')
    draw.text((x,87),detail,font=small,fill='#665e4d')
    sheet.paste(patch.resize((384,256),Image.Resampling.NEAREST),(x,120))
    draw.text((x,385),caption,font=small,fill='#665e4d')
sheet.save(out / 'olive_comparison.png')
print('Olive mockup created; no game assets changed.')

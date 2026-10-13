"""Use the existing preview renderer for dirt-road colour studies."""
from pathlib import Path

path = Path(__file__).resolve().parent / 'patch_mockups.py'
source = path.read_text()
start = source.index('variants = [')
end = source.index('\nlayout = ', start)
source = source[:start] + '''variants = [
    ('A - Sandy ochre', [(224, 200, 144), (200, 176, 112), (176, 152, 88)], 'Custom ramp; dusty gold with softer speckles'),
    ('B - Packed earth', [(192, 168, 128), (168, 144, 104), (144, 120, 80)], 'Custom ramp; warm brown worn dirt'),
    ('C - Weathered clay', [(216, 184, 152), (192, 160, 128), (168, 136, 104)], 'Custom ramp; soft terracotta-brown'),
    ('D - Dry limestone', [(208, 200, 168), (184, 176, 144), (160, 152, 120)], 'Custom ramp; pale grey-beige dirt'),
]''' + source[end:]
source = source.replace('Wurren 0x2F1 and surrounding tiles - colour studies', 'Wurren dirt road - softer, earthier colour studies')
source = source.replace("f'patch_{v}_context.png'", "f'road_{v}_context.png'")
source = source.replace("'patch_options.png'", "'road_options.png'")
source = source.replace('Created current + three recolour mockups;', 'Created four dirt-road mockups;')
exec(compile(source, str(path), 'exec'))

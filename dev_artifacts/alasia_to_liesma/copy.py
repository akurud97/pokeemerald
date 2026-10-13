"""One-shot Alasia 0x201 import using the verified tile-copy workflow."""
from pathlib import Path

root = Path(__file__).resolve().parents[2]
source = (root / 'dev_artifacts/castulatest_to_liesma/copy.py').read_text()
changes = [
    ('Copy the three selected Castulatest metatiles, preserving current edits.',
     'Copy Alasia metatile 0x201, preserving current edits.'),
    ('secondary/castula', 'secondary/alasia'),
    ("blocks = r.words(ROOT / 'data/layouts/castulatest/map.bin')", 'blocks = [0x201]'),
    ('assert len(blocks) == 3 and ids == [0x37E, 0x386, 0x38E]', 'assert ids == [0x201]'),
    ('== {0, 2}', '== {2, 5}'),
    ('(128,384)', '(128,128)'),
    ("'primary_palettes': [0,2]", "'primary_palettes': [2,5]"),
]
for old, new in changes:
    assert old in source, old
    source = source.replace(old, new)
exec(compile(source, str(Path(__file__).resolve()), 'exec'))

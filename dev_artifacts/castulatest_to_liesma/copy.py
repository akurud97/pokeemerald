"""Copy the three selected Castulatest metatiles, preserving current edits."""
from pathlib import Path
import importlib.util
import json
import shutil
import re
from PIL import Image

ROOT = Path(__file__).resolve().parents[2]
REPORT = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('renderlib', ROOT / 'dev_artifacts/liesma/build.py')
r = importlib.util.module_from_spec(spec)
spec.loader.exec_module(r)
src = ROOT / 'data/tilesets/secondary/castula'
dst = ROOT / 'data/tilesets/secondary/liesma'
blocks = r.words(ROOT / 'data/layouts/castulatest/map.bin')
ids = sorted({b & 1023 for b in blocks})
assert len(blocks) == 3 and ids == [0x37E, 0x386, 0x38E]
assert not (REPORT / 'before').exists(), 'Never overwrite backup or rerun import'
sm, sa = r.words(src / 'metatiles.bin'), r.words(src / 'metatile_attributes.bin')
dm, da = r.words(dst / 'metatiles.bin'), r.words(dst / 'metatile_attributes.bin')
old_dm, old_da = dm[:], da[:]
sheet, source = Image.open(dst / 'tiles.png').copy(), Image.open(src / 'tiles.png')
old_pixels = sheet.tobytes()
entries = [e for mid in ids for e in sm[(mid-512)*8:(mid-512)*8+8]]
assert {e >> 12 for e in entries} == {0, 2}, 'Unexpected palette requirements'
layouts = json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']
used_mids = set()
for layout in layouts:
    if layout['secondary_tileset'] == 'gTileset_Liesma':
        assert layout['primary_tileset'] == 'gTileset_General'
        for key in ['blockdata_filepath', 'border_filepath']:
            used_mids.update(b & 1023 for b in r.words(ROOT / layout[key]))
free_mids = [mid for mid in range(0x201, 0x400)
             if mid not in used_mids and not any(dm[(mid-512)*8:(mid-512)*8+8]) and da[mid-512] == 0]
reserved = set(range(0x2DA, 0x2E0)) | set(range(0x3F8, 0x400))
used_tiles = {e & 1023 for e in dm} | reserved
free_tiles = [tid for tid in range(0x200, 0x3F8)
              if tid not in used_tiles and not any(r.tile(sheet, tid-512).tobytes())]
lookup = {r.tile(sheet, tid-512).tobytes(): tid for tid in range(0x200, 0x3F8) if tid not in reserved}
allocated, mapping = [], {}
for mid in ids:
    target = free_mids.pop(0)
    mapped = []
    for e in sm[(mid-512)*8:(mid-512)*8+8]:
        tid = e & 1023
        if tid >= 512:
            pixels = r.tile(source, tid-512)
            key = pixels.tobytes()
            if key not in lookup:
                new_tid = free_tiles.pop(0)
                sheet.paste(pixels, ((new_tid-512)%16*8, (new_tid-512)//16*8))
                lookup[key] = new_tid
                allocated.append(new_tid)
            e = (e & 0xFC00) | lookup[key]
        mapped.append(e)
    dm[(target-512)*8:(target-512)*8+8] = mapped
    da[target-512] = sa[mid-512]
    mapping[mid] = target
after_blocks = [(b & ~1023) | mapping[b & 1023] for b in blocks]
before = r.render(src, blocks, 1)
# Save exact working-tree versions, including the user's existing edits.
files = ['data/tilesets/secondary/liesma/tiles.png', 'data/tilesets/secondary/liesma/metatiles.bin',
         'data/tilesets/secondary/liesma/metatile_attributes.bin', 'src/data/tilesets/graphics.h']
for relative in files:
    backup = REPORT / 'before' / relative
    backup.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(ROOT / relative, backup)
sheet.save(dst / 'tiles.png', bits=4)
r.save_words(dst / 'metatiles.bin', dm)
r.save_words(dst / 'metatile_attributes.bin', da)
graphics = ROOT / 'src/data/tilesets/graphics.h'
text = graphics.read_text()
match = re.search(r'(gTilesetTiles_Liesma\[\].*?-num_tiles )(\d+)', text)
assert match
count = max(int(match[2]), max(allocated, default=512)-511)
if count != int(match[2]):
    text = text[:match.start(2)] + str(count) + text[match.end(2):]
    graphics.write_text(text)
after = r.render(dst, after_blocks, 1)
assert before.tobytes() == after.tobytes(), 'Rendered copy differs'
for i in range(512):
    if i+512 not in mapping.values():
        assert dm[i*8:i*8+8] == old_dm[i*8:i*8+8] and da[i] == old_da[i]
saved = Image.open(dst / 'tiles.png')
for tid in range(512, 1024):
    if tid not in allocated:
        start = (tid-512)//16*8*128 + (tid-512)%16*8
        for y in range(8):
            assert saved.tobytes()[start+y*128:start+y*128+8] == old_pixels[start+y*128:start+y*128+8]
before.resize((128,384), Image.Resampling.NEAREST).save(REPORT / 'source.png')
after.resize((128,384), Image.Resampling.NEAREST).save(REPORT / 'liesma.png')
manifest = {'metatile_mapping': {f'{k:03X}': f'{v:03X}' for k,v in mapping.items()},
            'allocated_graphic_tiles': [f'{v:03X}' for v in allocated], 'compiled_tiles': count,
            'primary_palettes': [0,2], 'render_identical': True}
(REPORT / 'manifest.json').write_text(json.dumps(manifest, indent=2)+'\n')
print(json.dumps(manifest, indent=2))

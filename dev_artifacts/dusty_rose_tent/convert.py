"""Recolour native tent pixels with General palette 3; never edit palettes."""
from pathlib import Path
from collections import Counter
import importlib.util
import json
import shutil
import sys
import re
import hashlib
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
REPORT = Path(__file__).resolve().parent
BEFORE = REPORT / 'before'
spec = importlib.util.spec_from_file_location('liesma_render', ROOT / 'dev_artifacts/liesma/build.py')
renderlib = importlib.util.module_from_spec(spec)
spec.loader.exec_module(renderlib)
words, save_words, tile, render = renderlib.words, renderlib.save_words, renderlib.tile, renderlib.render
FOLDERS = ['castula', 'fallarbor_cedar', 'liesma']
# Grey indices 6/7 in palette 3 are green. Use its dark plum neutrals instead.
# Transparent index 0 remains 0; four warm shades become the rose ramp 9..12.
LUT = [0, 1, 2, 3, 4, 5, 14, 8, 8, 9, 10, 9, 10, 11, 12, 15]
EXTRA_WURREN = [0x353, 0x354, 0x355, 0x35B, 0x35C, 0x35D]

def folder(name, saved=False):
    if saved and name == 'fallarbor_rose_tent': name = 'fallarbor_cedar'
    return (BEFORE if saved else ROOT) / 'data/tilesets/secondary' / name

def state():
    return json.loads((REPORT / 'manifest.json').read_text())

def save_state(data):
    # Generated audit data, not hand-edited project source.
    (REPORT / 'manifest.json').write_text(json.dumps(data, indent=2) + '\n')

def snapshot():
    assert not BEFORE.exists(), 'Do not overwrite a backup'
    layouts = json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']
    for relative in ['data/tilesets/primary/general'] + ['data/tilesets/secondary/' + f for f in FOLDERS]:
        shutil.copytree(ROOT / relative, BEFORE / relative)
    for l in layouts:
        if l['secondary_tileset'] not in ['gTileset_Castula', 'gTileset_FallarborCedar', 'gTileset_Liesma']:
            continue
        for key in ['blockdata_filepath', 'border_filepath']:
            p = Path(l[key]); dst = BEFORE / p; dst.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(ROOT / p, dst)
        name = Path(l['blockdata_filepath']).parent.name
        if (ROOT / 'data/maps' / name).exists():
            shutil.copytree(ROOT / 'data/maps' / name, BEFORE / 'data/maps' / name)
    for relative in ['data/layouts/layouts.json', 'src/field_door.c', 'src/tileset_anims.c',
                     'src/data/tilesets/headers.h', 'src/data/tilesets/graphics.h',
                     'porymap_scripts/tileset_animation/project_tileset_copies.js']:
        dst = BEFORE / relative; dst.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / relative, dst)
    shutil.copytree(ROOT / 'graphics/door_anims', BEFORE / 'graphics/door_anims')

class Allocator:
    def __init__(self, name):
        self.name = name
        self.sheet = Image.open(folder(name) / 'tiles.png').copy()
        self.ms = words(folder(name) / 'metatiles.bin')
        refs = {e & 1023 for e in self.ms}
        reserved = set(range(0x3F8, 0x400))
        if name == 'castula': reserved.update(range(0x3C0, 0x3C4))
        if name == 'liesma': reserved.update(range(0x2DA, 0x2E0))
        self.free = [i + 512 for i in range(min(504, self.sheet.width * self.sheet.height // 64))
                     if i + 512 not in refs and i + 512 not in reserved and not any(tile(self.sheet, i).tobytes())]
        self.lookup = {}
        self.added = []

    def allocate(self, pixels):
        key = pixels.tobytes()
        if not any(key): return 0
        if key not in self.lookup:
            assert self.free, self.name + ': no blank unreferenced graphic tiles left'
            tid = self.free.pop(0)
            self.sheet.paste(pixels, ((tid - 512) % 16 * 8, (tid - 512) // 16 * 8))
            self.lookup[key] = tid
            self.added.append(tid)
        return self.lookup[key]

    def save(self):
        self.sheet.save(folder(self.name) / 'tiles.png', bits=4)
        save_words(folder(self.name) / 'metatiles.bin', self.ms)

def recolour():
    snapshot()
    manifest = {'palette': 3, 'lut': LUT, 'aligned': False, 'tilesets': {}}
    for name, mapname, oldpals in [('castula', 'castulatest', {5, 11}),
                                  ('fallarbor_cedar', 'wurrentest', {1})]:
        alloc = Allocator(name)
        original = words(folder(name, True) / 'metatiles.bin')
        source = Image.open(folder(name, True) / 'tiles.png')
        blocks = words(BEFORE / f'data/layouts/{mapname}/map.bin')
        mids = sorted({b & 1023 for b in blocks if b & 1023 >= 512})
        tids = {e & 1023 for mid in mids for e in original[(mid-512)*8+4:(mid-512)*8+8]
                if e >> 12 in oldpals and e & 1023 >= 512}
        changed = []
        # Also handle extension pieces which reuse these exact tent graphics.
        # Clone the graphics, so original assets/references with other palettes stay intact.
        for addr, e in enumerate(original):
            if addr % 8 < 4 or e >> 12 not in oldpals or e & 1023 not in tids:
                continue
            pixels = tile(source, (e & 1023) - 512)
            pixels.putdata([LUT[v] for v in pixels.get_flattened_data()])
            alloc.ms[addr] = 0x3000 | (e & 0xC00) | alloc.allocate(pixels)
            changed.append(addr)
        assert changed
        alloc.save()
        manifest['tilesets'][name] = {'changed_addresses': changed, 'allocated_tiles': alloc.added,
                                      'test_metatiles': mids}

    # Import Castula's larger/aligned template, leaving both city maps and the
    # existing pink/cream house test unchanged. Use Liesma's primary plaza floor.
    alloc = Allocator('liesma')
    source = Image.open(folder('castula') / 'tiles.png')
    cms = words(folder('castula') / 'metatiles.bin')
    attrs = words(folder('liesma') / 'metatile_attributes.bin')
    cattrs = words(folder('castula') / 'metatile_attributes.bin')
    ids = manifest['tilesets']['castula']['test_metatiles']
    primary = words(ROOT / 'data/tilesets/primary/general/metatiles.bin')
    plaza = primary[0x170 * 8:0x170 * 8 + 4]
    candidates = [mid for mid in range(0x352, 0x400)
                  if not any(alloc.ms[(mid-512)*8:(mid-512)*8+8]) and attrs[mid-512] == 0]
    assert len(candidates) >= len(ids)
    lookup = {}
    for mid in ids:
        target = candidates.pop(0)
        mapped = list(plaza)
        for e in cms[(mid-512)*8+4:(mid-512)*8+8]:
            if e & 1023 >= 512:
                tid = alloc.allocate(tile(source, (e & 1023) - 512))
                mapped.append((e & 0xFC00) | tid)
            else:
                mapped.append(e)
        alloc.ms[(target-512)*8:(target-512)*8+8] = mapped
        attrs[target-512] = cattrs[mid-512]
        lookup[mid] = target
    alloc.save()
    save_words(folder('liesma') / 'metatile_attributes.bin', attrs)
    manifest['tilesets']['liesma'] = {'metatile_mapping': {f'{k:03X}': v for k,v in lookup.items()},
                                    'allocated_tiles': alloc.added,
                                    'compiled_tiles': max(252, max(alloc.added) - 511)}
    blocks = words(ROOT / 'data/layouts/castulatest/map.bin')
    manifest['liesma_template'] = [lookup[b & 1023] for b in blocks]
    save_state(manifest)
    previews()
    print(json.dumps(manifest, indent=2))

def align():
    """Run only after the user approves reusing EXTRA_WURREN slots."""
    manifest = state()
    assert not manifest['aligned']
    dest = folder('fallarbor_rose_tent')
    assert not dest.exists(), 'Never overwrite a tileset copy'
    shutil.copytree(folder('fallarbor_cedar'), dest)
    alloc = Allocator('fallarbor_rose_tent')
    original = list(alloc.ms)
    source_blocks = words(BEFORE / 'data/layouts/wurrentest/map.bin')
    assert len(source_blocks) == 36 and source_blocks[30:] == [0] * 6
    layouts = json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']
    for l in layouts:
        if l['secondary_tileset'] != 'gTileset_FallarborCedar': continue
        for key in ['blockdata_filepath', 'border_filepath']:
            assert not ({v & 1023 for v in words(ROOT / l[key])} & set(EXTRA_WURREN))
    ground = [0x8259] * 4
    candidates = sorted({b & 1023 for b in source_blocks if b & 1023 >= 512}) + EXTRA_WURREN
    attrs = words(dest / 'metatile_attributes.bin')
    lookup, output = {}, []
    for y in range(6):
        for x in range(6):
            bg = ground
            fg = []
            for q in range(4):
                sy = y * 2 + q // 2 - 1
                if 0 <= sy < 10:
                    mid = source_blocks[(sy//2)*6+x] & 1023
                    fg.append(original[(mid-512)*8+4+(sy%2)*2+q%2])
                else: fg.append(0)
            key = tuple(bg + fg)
            if key not in lookup:
                assert candidates, 'Not enough approved metatile slots'
                mid = candidates.pop(0)
                lookup[key] = mid
                alloc.ms[(mid-512)*8:(mid-512)*8+8] = key
                attrs[mid-512] = 0
            output.append((source_blocks[y*6+x] & 0xFC00) | lookup[key])
    alloc.save()
    save_words(dest / 'metatile_attributes.bin', attrs)
    save_words(ROOT / 'data/layouts/wurrentest/map.bin', output)
    manifest['aligned'] = True
    manifest['aligned_folder'] = 'fallarbor_rose_tent'
    manifest['tilesets']['fallarbor_rose_tent'] = manifest['tilesets']['fallarbor_cedar'].copy()
    manifest['aligned_metatiles'] = list(lookup.values())
    manifest['wurren_template'] = output
    save_state(manifest)
    previews()
    print('Aligned Wurren 8 pixels lower:', len(lookup), 'metatiles')

def foreground(name, blocks, saved=False, tint=False):
    f = folder(name, saved)
    ms = words(f / 'metatiles.bin')
    sheet = Image.open(f / 'tiles.png')
    pal = renderlib.palette(ROOT / 'data/tilesets/primary/general/palettes/03.pal')
    out = Image.new('RGBA', (96, 96), (0,0,0,0))
    for pos, block in enumerate(blocks):
        if block & 1023 < 512: continue
        for q, e in enumerate(ms[((block&1023)-512)*8+4:((block&1023)-512)*8+8]):
            tid = e & 1023
            if not tid: continue
            t = tile(sheet, tid-512)
            if e & 0x400: t = t.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
            if e & 0x800: t = t.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
            for yy in range(8):
                for xx in range(8):
                    v = t.getpixel((xx,yy))
                    if tint: v = LUT[v]
                    if v: out.putpixel((pos%6*16+q%2*8+xx, pos//6*16+q//2*8+yy), (*pal[v],255))
    return out

def previews():
    manifest = state()
    for name, mapname in [('castula','castulatest'), (manifest.get('aligned_folder','fallarbor_cedar'),'wurrentest')]:
        blocks = words(ROOT / f'data/layouts/{mapname}/map.bin')
        render(folder(name), blocks, 6).resize((576,576), Image.Resampling.NEAREST).save(REPORT / (name + '_preview.png'))
    render(folder('liesma'), manifest['liesma_template'], 6).resize((576,576), Image.Resampling.NEAREST).save(REPORT / 'liesma_preview.png')
    for name, blocks in [('castula', words(ROOT / 'data/layouts/castulatest/map.bin')),
                         (manifest.get('aligned_folder','fallarbor_cedar'), words(ROOT / 'data/layouts/wurrentest/map.bin')),
                         ('liesma', manifest['liesma_template'])]:
        foreground(name, blocks).resize((576,576),Image.Resampling.NEAREST).save(REPORT / (name + '_building.png'))

def registration_patch():
    manifest = state()
    assert manifest['aligned']
    for relative in ['src/data/tilesets/metatiles.h', 'include/tilesets.h']:
        target = BEFORE / relative
        assert not target.exists()
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / relative, target)
    edits = {}
    for relative, pattern in [
        ('src/data/tilesets/headers.h', r'const struct Tileset gTileset_FallarborCedar =\n\{.*?\n\};'),
        ('src/data/tilesets/graphics.h', r'const u32 gTilesetTiles_FallarborCedar\[\].*?const u16 gTilesetPalettes_FallarborCedar\[\]\[16\] =\n\{.*?\n\};'),
        ('src/data/tilesets/metatiles.h', r'const u16 gMetatiles_FallarborCedar\[\].*?\nconst u16 gMetatileAttributes_FallarborCedar\[\].*?;'),
    ]:
        old = (ROOT / relative).read_text()
        match = re.search(pattern, old, re.S)
        assert match, relative
        block = match[0]
        copy = block.replace('FallarborCedar', 'FallarborRoseTent').replace('fallarbor_cedar/', 'fallarbor_rose_tent/')
        new = old.replace(block, block + '\n\n' + copy, 1)
        if relative.endswith('graphics.h'):
            anchor = '"-num_tiles 252 -Wnum_tiles"'
            assert new.count(anchor) == 1
            new = new.replace(anchor, '"-num_tiles 275 -Wnum_tiles"')
        edits[relative] = (old, new)
    relative = 'include/tilesets.h'
    old = (ROOT / relative).read_text()
    anchor = 'extern const struct Tileset gTileset_FallarborCedar;'
    edits[relative] = (old, old.replace(anchor, anchor + '\nextern const struct Tileset gTileset_FallarborRoseTent;',1))
    relative = 'src/field_door.c'
    old = (ROOT / relative).read_text()
    rows = [r for r in old.splitlines() if '&gTileset_FallarborCedar,' in r]
    assert len(rows) == 3
    anchor = '\n'.join(rows)
    copy = anchor.replace('&gTileset_FallarborCedar,', '&gTileset_FallarborRoseTent,')
    edits[relative] = (old, old.replace(anchor, anchor+'\n'+copy,1))
    relative = 'porymap_scripts/tileset_animation/project_tileset_copies.js'
    old = (ROOT / relative).read_text()
    anchor = '    { source: "gTileset_Fallarbor", copy: "gTileset_FallarborCedar", folder: "fallarbor_cedar/anim" },'
    copy = anchor.replace('FallarborCedar', 'FallarborRoseTent').replace('fallarbor_cedar/', 'fallarbor_rose_tent/')
    edits[relative] = (old, old.replace(anchor, anchor+'\n'+copy,1))
    relative = 'data/layouts/layouts.json'
    old = (ROOT / relative).read_text()
    block = re.search(r'\{\s*"id": "LAYOUT_WURRENTEST",.*?\}', old, re.S)[0]
    copy = block.replace('gTileset_FallarborCedar', 'gTileset_FallarborRoseTent')
    assert copy != block
    edits[relative] = (old, old.replace(block,copy,1))
    patch = ['*** Begin Patch']
    manifest['registration_hashes'] = {}
    for relative, (old, new) in edits.items():
        assert new != old
        assert old == (BEFORE / relative).read_text(), 'Registration changed during operation'
        # Trim unchanged leading/trailing lines for small targeted hunks.
        a,b = old.splitlines(), new.splitlines()
        first = 0
        while first < len(a) and first < len(b) and a[first] == b[first]: first += 1
        last_a,last_b = len(a),len(b)
        while last_a > first and last_b > first and a[last_a-1] == b[last_b-1]: last_a-=1;last_b-=1
        start=max(0,first-2); end_a=min(len(a),last_a+2);end_b=min(len(b),last_b+2)
        patch += ['*** Update File: '+str(ROOT/relative),'@@']
        patch += [' '+line for line in a[start:first]]
        patch += ['-'+line for line in a[first:last_a]]
        patch += ['+'+line for line in b[first:last_b]]
        patch += [' '+line for line in a[last_a:end_a]]
        manifest['registration_hashes'][relative] = hashlib.sha256(new.encode()).hexdigest()
    patch.append('*** End Patch')
    save_state(manifest)
    print(json.dumps('\n'.join(patch)))

def verify():
    manifest = state()
    for saved in (BEFORE / 'data/tilesets/primary/general').rglob('*'):
        if saved.is_file(): assert saved.read_bytes() == (ROOT / saved.relative_to(BEFORE)).read_bytes()
    for name in FOLDERS + (['fallarbor_rose_tent'] if manifest['aligned'] else []):
        f = folder(name)
        for saved in (folder(name,True) / 'palettes').glob('*.pal'):
            assert saved.read_bytes() == (f / 'palettes' / saved.name).read_bytes(), 'Palette changed'
        for saved in (folder(name,True) / 'anim').rglob('*'):
            if saved.is_file(): assert saved.read_bytes() == (f / 'anim' / saved.relative_to(folder(name,True) / 'anim')).read_bytes()
        original = Image.open(folder(name,True) / 'tiles.png')
        current = Image.open(f / 'tiles.png')
        added = set(manifest['tilesets'][name]['allocated_tiles'])
        for i in range(original.width*original.height//64):
            if i+512 not in added: assert tile(original,i).tobytes() == tile(current,i).tobytes(), (name,hex(i+512))
            else: assert not any(tile(original,i).tobytes()), 'Occupied tile overwritten'
        assert current.mode == 'P' and current.size == original.size
        for mid in range(len(words(f/'metatile_attributes.bin'))):
            old = words(folder(name,True)/'metatiles.bin')[mid*8:mid*8+8]
            new = words(f/'metatiles.bin')[mid*8:mid*8+8]
            if name == 'liesma': allowed = mid+512 in manifest['tilesets'][name]['metatile_mapping'].values()
            else:
                allowed = any(a//8 == mid for a in manifest['tilesets'][name]['changed_addresses'])
                if name == 'fallarbor_rose_tent' and manifest['aligned']: allowed |= mid+512 in manifest['aligned_metatiles']
            if not allowed: assert old == new, (name,'unrelated metatile',hex(mid+512))
    for relative in ['src/tileset_anims.c']:
        assert (BEFORE/relative).read_bytes() == (ROOT/relative).read_bytes(), relative
    for relative, expected in manifest.get('registration_hashes',{}).items():
        assert hashlib.sha256((ROOT/relative).read_bytes()).hexdigest() == expected, relative
    for saved in (BEFORE/'graphics/door_anims').rglob('*'):
        if saved.is_file(): assert saved.read_bytes() == (ROOT/saved.relative_to(BEFORE)).read_bytes()
    for saved in (BEFORE/'data/layouts').rglob('*.bin'):
        if manifest['aligned'] and saved == BEFORE/'data/layouts/wurrentest/map.bin': continue
        assert saved.read_bytes() == (ROOT/saved.relative_to(BEFORE)).read_bytes(), saved
    cb = words(ROOT/'data/layouts/castulatest/map.bin')
    assert foreground('castula', cb).tobytes() == foreground('liesma',manifest['liesma_template']).tobytes(), 'Liesma building differs'
    if manifest['aligned']:
        wb = words(ROOT/'data/layouts/wurrentest/map.bin')
        old_blocks = words(BEFORE/'data/layouts/wurrentest/map.bin')
        # Rebuild expected tinted foreground from backup, then shift by exactly 8.
        original = foreground('fallarbor_cedar',old_blocks,True,tint=True)
        shifted = Image.new('RGBA',(96,96),(0,0,0,0));shifted.paste(original,(0,8))
        assert foreground('fallarbor_rose_tent',wb).tobytes() == shifted.tobytes(), 'Wurren shift is not pixel-exact'
        assert all((a&0xFC00)==(b&0xFC00) for a,b in zip(wb,old_blocks)), 'Map collision/elevation bits changed'
    print('PASS: original graphics, General, all palettes, animations, doors and unrelated maps preserved')
    print('PASS: Castula and Liesma building pixels/colours identical; Wurren alignment verified' if manifest['aligned'] else 'PASS: Castula and Liesma building pixels/colours identical; Wurren alignment pending')

if __name__ == '__main__':
    {'recolour': recolour, 'align': align, 'verify': verify, 'previews': previews,
     'registration-patch': registration_patch}[sys.argv[1]]()

"""Switch the saved rose tent experiment to General's existing blue palette 0."""
from pathlib import Path
import importlib.util
import json
import shutil
import sys
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
REPORT = Path(__file__).resolve().parent
BEFORE = REPORT / 'before'
ROSE = ROOT / 'dev_artifacts/dusty_rose_tent'
spec = importlib.util.spec_from_file_location('native_render', ROOT / 'dev_artifacts/liesma/build.py')
native = importlib.util.module_from_spec(spec)
spec.loader.exec_module(native)
words, save_words, tile, render = native.words, native.save_words, native.tile, native.render
FOLDERS = ['castula', 'fallarbor_cedar', 'fallarbor_rose_tent', 'liesma']
# Reverse the rose index remap, then apply the blue ramp. The two dark outline
# shades merged in rose both become index 7: palette 0's index 8 is BEIGE.
LUT = [0, 1, 2, 3, 4, 5, 6, 7, 7, 9, 12, 13, 14, 13, 6, 15]
ROSE_INDICES = {0, 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 14}
REGISTRATIONS = ['data/layouts/layouts.json', 'src/field_door.c', 'src/tileset_anims.c',
                 'src/data/tilesets/graphics.h', 'src/data/tilesets/headers.h',
                 'src/data/tilesets/metatiles.h', 'include/tilesets.h',
                 'porymap_scripts/tileset_animation/project_tileset_copies.js']

def folder(name, saved=False):
    return (BEFORE if saved else ROOT) / 'data/tilesets/secondary' / name

def backup():
    assert not BEFORE.exists(), 'Never overwrite an earlier backup'
    for name in FOLDERS:
        shutil.copytree(folder(name), folder(name,True))
    shutil.copytree(native.PRIMARY, BEFORE / 'data/tilesets/primary/general')
    shutil.copytree(ROOT / 'graphics/door_anims', BEFORE / 'graphics/door_anims')
    layouts = json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']
    for l in layouts:
        if l['secondary_tileset'] not in ['gTileset_Castula', 'gTileset_FallarborCedar',
                                         'gTileset_FallarborRoseTent', 'gTileset_Liesma']:
            continue
        for key in ['blockdata_filepath', 'border_filepath']:
            p = Path(l[key]); dst = BEFORE / p
            dst.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(ROOT / p, dst)
        name = Path(l['blockdata_filepath']).parent.name
        p = ROOT / 'data/maps' / name
        if p.exists(): shutil.copytree(p, BEFORE / 'data/maps' / name)
    for relative in REGISTRATIONS:
        dst = BEFORE / relative
        dst.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / relative, dst)
    shutil.copy2(ROSE / 'manifest.json', BEFORE / 'rose_manifest.json')

def convert():
    rose = json.loads((ROSE / 'manifest.json').read_text())
    assert rose['aligned']
    # Validate all assets before making any change. A colour edit by the user
    # outside this experiment must not be silently reinterpreted.
    for name in FOLDERS:
        tids = set(rose['tilesets'][name]['allocated_tiles'])
        im = Image.open(folder(name) / 'tiles.png')
        ms = words(folder(name) / 'metatiles.bin')
        refs = [e for e in ms if e & 1023 in tids]
        assert refs and all(e >> 12 == 3 for e in refs), (name, 'unexpected palette reference')
        assert all(set(tile(im,tid-512).get_flattened_data()) <= ROSE_INDICES for tid in tids), (name,'unexpected colour index')
    backup()
    manifest = {'palette': 0, 'lut': LUT, 'tilesets': {},
                'liesma_template': rose['liesma_template'], 'wurren_template': rose['wurren_template']}
    for name in FOLDERS:
        tids = set(rose['tilesets'][name]['allocated_tiles'])
        im = Image.open(folder(name) / 'tiles.png').copy()
        ms = words(folder(name) / 'metatiles.bin')
        for tid in tids:
            pixels = tile(im, tid-512)
            pixels.putdata([LUT[v] for v in pixels.get_flattened_data()])
            im.paste(pixels, ((tid-512)%16*8, (tid-512)//16*8))
        addresses = [i for i,e in enumerate(ms) if e & 1023 in tids]
        for i in addresses: ms[i] &= 0x0FFF
        im.save(folder(name) / 'tiles.png', bits=4)
        save_words(folder(name) / 'metatiles.bin', ms)
        manifest['tilesets'][name] = {'tiles': sorted(tids), 'addresses': addresses}
    (REPORT/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    previews()
    verify()

def foreground(name, blocks):
    ms = words(folder(name)/'metatiles.bin')
    im = Image.open(folder(name)/'tiles.png')
    pals = [native.palette((native.PRIMARY if p<6 else folder(name))/f'palettes/{p:02}.pal') for p in range(13)]
    out = Image.new('RGBA',(96,96),(0,0,0,0))
    for pos, block in enumerate(blocks):
        mid = block & 1023
        if mid < 512: continue
        for q,e in enumerate(ms[(mid-512)*8+4:(mid-512)*8+8]):
            tid = e & 1023
            if not tid: continue
            assert tid >= 512
            pixels = tile(im,tid-512)
            if e & 0x400: pixels = pixels.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
            if e & 0x800: pixels = pixels.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
            for y in range(8):
                for x in range(8):
                    idx = pixels.getpixel((x,y))
                    if idx: out.putpixel((pos%6*16+q%2*8+x,pos//6*16+q//2*8+y),(*pals[e>>12][idx],255))
    return out

def previews():
    manifest = json.loads((REPORT/'manifest.json').read_text())
    cb = words(ROOT/'data/layouts/castulatest/map.bin')
    wb = words(ROOT/'data/layouts/wurrentest/map.bin')
    variants = [('castula','Castula',cb), ('fallarbor_rose_tent','Wurren (aligned)',wb),
                ('liesma','Liesma',manifest['liesma_template'])]
    preview = Image.new('RGB',(960,370),(235,231,222));draw = ImageDraw.Draw(preview)
    for i,(name,label,blocks) in enumerate(variants):
        building = foreground(name,blocks)
        building.resize((576,576),Image.Resampling.NEAREST).save(REPORT/(name+'_building.png'))
        render(folder(name),blocks,6).resize((576,576),Image.Resampling.NEAREST).save(REPORT/(name+'_preview.png'))
        building = building.resize((288,288),Image.Resampling.NEAREST)
        preview.paste(building,(i*320+16,50),building)
        draw.text((i*320+16,20),label,fill=(60,48,58))
    preview.save(REPORT/'comparison.png')

def verify():
    manifest = json.loads((REPORT/'manifest.json').read_text())
    for name,data in manifest['tilesets'].items():
        src,dest = folder(name,True),folder(name)
        old_ms,new_ms = words(src/'metatiles.bin'),words(dest/'metatiles.bin')
        old_im,new_im = Image.open(src/'tiles.png'),Image.open(dest/'tiles.png')
        assert old_im.size == new_im.size and new_im.mode == 'P'
        for i,(a,b) in enumerate(zip(old_ms,new_ms)):
            assert b == (a&0xFFF if i in data['addresses'] else a), (name,'unexpected reference edit',i)
        for i in range(old_im.width*old_im.height//64):
            before = tile(old_im,i).tobytes()
            after = tile(new_im,i).tobytes()
            expected = bytes(LUT[v] for v in before) if i+512 in data['tiles'] else before
            assert after == expected,(name,'unexpected pixel edit',hex(i+512))
            assert [v!=0 for v in before] == [v!=0 for v in after], 'Transparency changed'
        for saved in src.rglob('*'):
            if not saved.is_file() or saved.relative_to(src).as_posix() in ['tiles.png','metatiles.bin']: continue
            assert saved.read_bytes() == (dest/saved.relative_to(src)).read_bytes(),saved
    for relative in REGISTRATIONS:
        assert (BEFORE/relative).read_bytes() == (ROOT/relative).read_bytes(),relative
    for relative in ['data/tilesets/primary/general','data/layouts','data/maps','graphics/door_anims']:
        for saved in (BEFORE/relative).rglob('*'):
            if saved.is_file(): assert saved.read_bytes() == (ROOT/saved.relative_to(BEFORE)).read_bytes(),saved
    cb = words(ROOT/'data/layouts/castulatest/map.bin')
    assert foreground('castula',cb).tobytes() == foreground('liesma',manifest['liesma_template']).tobytes()
    print('PASS: only the existing tent graphics and their palette references changed')
    print('PASS: no new palettes/tiles/metatiles; all layouts, alignment, behaviours, animations and doors preserved')
    print('PASS: Castula and Liesma foreground colours/pixels match exactly')

if __name__ == '__main__':
    {'convert':convert,'verify':verify,'previews':previews}[sys.argv[1]]()

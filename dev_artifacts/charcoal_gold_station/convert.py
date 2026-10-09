"""Native charcoal station / selective gold trim, using untouched General pal 5."""
from pathlib import Path
from collections import defaultdict
import importlib.util
import json
import shutil
import sys
import hashlib
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
REPORT = Path(__file__).resolve().parent
BEFORE = REPORT / 'before'
ROSE = ROOT / 'dev_artifacts/dusty_rose_tent'
BLUE = ROOT / 'dev_artifacts/blue_tent'
spec = importlib.util.spec_from_file_location('blue_station', BLUE / 'convert.py')
blue = importlib.util.module_from_spec(spec)
spec.loader.exec_module(blue)
native = blue.native
words, save_words, tile, render = blue.words, blue.save_words, blue.tile, blue.render
FOLDERS = blue.FOLDERS
REGISTRATIONS = blue.REGISTRATIONS
ROOF = {11:5, 12:6, 13:7, 14:8}
BODY = {11:1, 12:2, 13:4, 14:5}
BULB = {11:2, 12:6, 13:7, 14:7}

def folder(name, saved=False):
    return (BEFORE if saved else ROOT) / 'data/tilesets/secondary' / name

def recover_originals():
    """Recover original grey/outline indices which earlier palette swaps merged."""
    rose = json.loads((ROSE/'manifest.json').read_text())
    blue_manifest = json.loads((BLUE/'manifest.json').read_text())
    by_blue_pixels = {}
    for name in ['castula', 'fallarbor_cedar']:
        original_folder = ROSE/'before/data/tilesets/secondary'/name
        original_ms = words(original_folder/'metatiles.bin')
        original_sheet = Image.open(original_folder/'tiles.png')
        current_ms = words(folder(name)/'metatiles.bin')
        current_sheet = Image.open(folder(name)/'tiles.png')
        for address in rose['tilesets'][name]['changed_addresses']:
            old_tid = original_ms[address] & 1023
            current_tid = current_ms[address] & 1023
            original = tile(original_sheet, old_tid-512)
            key = tile(current_sheet,current_tid-512).tobytes()
            if key in by_blue_pixels: assert by_blue_pixels[key].tobytes() == original.tobytes()
            by_blue_pixels[key] = original
    originals = {}
    for name in FOLDERS:
        im = Image.open(folder(name)/'tiles.png')
        originals[name] = {}
        for tid in blue_manifest['tilesets'][name]['tiles']:
            key = tile(im,tid-512).tobytes()
            assert key in by_blue_pixels, (name,hex(tid),'user graphics changed')
            originals[name][tid] = by_blue_pixels[key].copy()
    return originals

def templates():
    rose = json.loads((ROSE/'manifest.json').read_text())
    return {
        'castula': (words(ROOT/'data/layouts/castulatest/map.bin'),0),
        'fallarbor_cedar': (words(ROSE/'before/data/layouts/wurrentest/map.bin'),8),
        'fallarbor_rose_tent': (words(ROOT/'data/layouts/wurrentest/map.bin'),0),
        'liesma': (rose['liesma_template'],0),
    }

def recoloured(original, role, position=None, flips=0):
    out = original.copy()
    ramp = BULB if role == 'bulb' else ROOF if role == 'roof' else BODY
    values = []
    for y in range(8):
        for x in range(8):
            idx = original.getpixel((x,y))
            value = ramp.get(idx,idx)
            if position is not None and idx in (11,12,13,14):
                gx = position[0] + (7-x if flips&0x400 else x)
                gy = position[1] + (7-y if flips&0x800 else y)
                lintel = 32 <= gx < 64 and gy in (54,55)
                window_border = 32 <= gx < 64 and gy in (56,63)
                jamb = gx in (30,65) and 56 <= gy < 80
                if lintel or window_border or jamb: value = idx
            values.append(value)
    out.putdata(values)
    return out

def make_plan(originals):
    template = templates()
    # Classify each ORIGINAL indexed tile, using the aligned Castula template.
    cms = words(folder('castula')/'metatiles.bin')
    bulb_pixels = tile(Image.open(ROSE/'before/data/tilesets/secondary/castula/tiles.png'),0x386-512).tobytes()
    roles = {}
    for pos,block in enumerate(template['castula'][0]):
        mid = block&1023
        for q,e in enumerate(cms[(mid-512)*8+4:(mid-512)*8+8]):
            tid = e&1023
            if tid not in originals['castula']: continue
            pixels = originals['castula'][tid].tobytes()
            y = pos//6*16+q//2*8
            role = 'bulb' if pixels == bulb_pixels else 'roof' if y<56 else 'body'
            assert pixels not in roles or roles[pixels] == role
            roles[pixels] = role
    plan = {}
    for name in FOLDERS:
        ms = words(folder(name)/'metatiles.bin')
        im = Image.open(folder(name)/'tiles.png').copy()
        target_tids = set(originals[name])
        addresses = [i for i,e in enumerate(ms) if e&1023 in target_tids]
        assert addresses and all(ms[i]>>12 == 0 for i in addresses), 'Unexpected current palette'
        refs = {e&1023 for e in ms}
        reserved = set(range(0x3F8,0x400))
        if name=='castula': reserved.update(range(0x3C0,0x3C4))
        if name=='liesma': reserved.update(range(0x2DA,0x2E0))
        free = [i+512 for i in range(min(504,im.width*im.height//64))
                if i+512 not in refs and i+512 not in reserved and not any(tile(im,i).tobytes())]
        pixels_by_tid = {}
        lookup = {}
        for tid,original in originals[name].items():
            pixels = recoloured(original,roles[original.tobytes()])
            pixels_by_tid[tid] = pixels
            lookup.setdefault(pixels.tobytes(),tid)
        # The usual grey version applies to every alias of an existing tent tile.
        output_ms = list(ms)
        for address in addresses: output_ms[address] = (ms[address]&0xFFF)|0x5000
        added = []
        placements = {}
        for pos,block in enumerate(template[name][0]):
            mid = block&1023
            if mid<512: continue
            for q in range(4):
                address = (mid-512)*8+4+q
                entry = ms[address]
                tid = entry&1023
                if tid not in originals[name]: continue
                original = originals[name][tid]
                xy = (pos%6*16+q%2*8,pos//6*16+q//2*8+template[name][1])
                pixels = recoloured(original,roles[original.tobytes()],xy,entry&0xC00)
                key = pixels.tobytes()
                if key not in lookup:
                    assert free, name+': no free graphics slots'
                    allocated = free.pop(0)
                    lookup[key] = allocated
                    pixels_by_tid[allocated] = pixels
                    added.append(allocated)
                # A repeated metatile must have the same appearance at all its
                # placements; otherwise it needs a user-approved metatile slot.
                expected = 0x5000|(entry&0xC00)|lookup[key]
                if address in placements: assert placements[address] == expected
                placements[address] = expected
                output_ms[address] = expected
        for tid,pixels in pixels_by_tid.items():
            im.paste(pixels,((tid-512)%16*8,(tid-512)//16*8))
        plan[name] = {'sheet':im, 'metatiles':output_ms, 'added':added, 'addresses':addresses,
                      'originals':originals[name], 'modified_tiles':sorted(pixels_by_tid),
                      'tile_pixels':{str(tid):list(p.tobytes()) for tid,p in pixels_by_tid.items()}}
    return plan

def backup():
    assert not BEFORE.exists(),'Never overwrite a backup'
    for name in FOLDERS: shutil.copytree(folder(name),folder(name,True))
    for relative in ['data/tilesets/primary/general','graphics/door_anims']:
        shutil.copytree(ROOT/relative,BEFORE/relative)
    layouts = json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts']
    for layout in layouts:
        if layout['secondary_tileset'] not in ['gTileset_Castula','gTileset_FallarborCedar','gTileset_FallarborRoseTent','gTileset_Liesma']: continue
        for key in ['blockdata_filepath','border_filepath']:
            p=Path(layout[key]); dst=BEFORE/p;dst.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(ROOT/p,dst)
        p=Path('data/maps')/Path(layout['blockdata_filepath']).parent.name
        if (ROOT/p).exists(): shutil.copytree(ROOT/p,BEFORE/p)
    for relative in REGISTRATIONS:
        dst=BEFORE/relative;dst.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(ROOT/relative,dst)
    shutil.copy2(BLUE/'manifest.json',BEFORE/'blue_manifest.json')

def convert():
    originals = recover_originals()
    plan = make_plan(originals)
    backup()
    manifest = {'palette':5,'tilesets':{},'liesma_template':templates()['liesma'][0]}
    for name,data in plan.items():
        data['sheet'].save(folder(name)/'tiles.png',bits=4)
        save_words(folder(name)/'metatiles.bin',data['metatiles'])
        manifest['tilesets'][name]={k:data[k] for k in ['added','addresses','modified_tiles','tile_pixels']}
        print(name,'extra graphic tiles:',len(data['added']))
    manifest['liesma_compiled_tiles']=max(275,max(plan['liesma']['modified_tiles'])-511)
    (REPORT/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    previews()

def previews():
    building_templates = templates()
    canvas = Image.new('RGB',(960,370),(235,231,222));draw=ImageDraw.Draw(canvas)
    for i,(name,label) in enumerate([('castula','Castula'),('fallarbor_rose_tent','Wurren (aligned)'),('liesma','Liesma')]):
        blocks = building_templates[name][0]
        building = blue.foreground(name,blocks)
        building.resize((576,576),Image.Resampling.NEAREST).save(REPORT/(name+'_building.png'))
        render(folder(name),blocks,6).resize((576,576),Image.Resampling.NEAREST).save(REPORT/(name+'_preview.png'))
        small=building.resize((288,288),Image.Resampling.NEAREST);canvas.paste(small,(320*i+16,50),small)
        draw.text((320*i+16,20),label,fill=(60,48,58))
    canvas.save(REPORT/'comparison.png')

def graphics_patch():
    manifest=json.loads((REPORT/'manifest.json').read_text())
    old=(ROOT/'src/data/tilesets/graphics.h').read_text()
    anchor='const u32 gTilesetTiles_Liesma[] = INCGFX_U32("data/tilesets/secondary/liesma/tiles.png", ".4bpp.fastSmol", "-num_tiles 275 -Wnum_tiles");'
    assert old.count(anchor)==1
    new=anchor.replace('275',str(manifest['liesma_compiled_tiles']))
    expected=old.replace(anchor,new)
    manifest['graphics_hash']=hashlib.sha256(expected.encode()).hexdigest()
    (REPORT/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    print(json.dumps('*** Begin Patch\n*** Update File: '+str(ROOT/'src/data/tilesets/graphics.h')+'\n@@\n-'+anchor+'\n+'+new+'\n*** End Patch'))

def verify():
    manifest=json.loads((REPORT/'manifest.json').read_text())
    for name,data in manifest['tilesets'].items():
        src,dest=folder(name,True),folder(name)
        old_ms,new_ms=words(src/'metatiles.bin'),words(dest/'metatiles.bin')
        a,b=Image.open(src/'tiles.png'),Image.open(dest/'tiles.png')
        assert a.size==b.size and b.mode=='P'
        assert len(old_ms)==len(new_ms)
        for i,(old,new) in enumerate(zip(old_ms,new_ms)):
            if i not in data['addresses']: assert old==new,(name,'unrelated metatile')
            else: assert new>>12==5 and old&0xC00==new&0xC00,(name,'flip/palette mismatch')
        for i in range(a.width*a.height//64):
            old,new=tile(a,i).tobytes(),tile(b,i).tobytes()
            if i+512 in data['modified_tiles']:
                assert new==bytes(data['tile_pixels'][str(i+512)])
                if i+512 in data['added']: assert not any(old),'Occupied graphic overwritten'
                else: assert [v!=0 for v in old]==[v!=0 for v in new],'Transparency changed'
            else: assert old==new,(name,'unrelated graphic',hex(i+512))
        for saved in src.rglob('*'):
            if saved.is_file() and saved.relative_to(src).as_posix() not in ['tiles.png','metatiles.bin']:
                assert saved.read_bytes()==(dest/saved.relative_to(src)).read_bytes(),saved
    for relative in REGISTRATIONS:
        if relative=='src/data/tilesets/graphics.h':
            assert hashlib.sha256((ROOT/relative).read_bytes()).hexdigest()==manifest['graphics_hash']
        else: assert (ROOT/relative).read_bytes()==(BEFORE/relative).read_bytes(),relative
    for relative in ['data/tilesets/primary/general','data/layouts','data/maps','graphics/door_anims']:
        for saved in (BEFORE/relative).rglob('*'):
            if saved.is_file(): assert saved.read_bytes()==(ROOT/saved.relative_to(BEFORE)).read_bytes(),saved
    cb=templates()['castula'][0];lb=templates()['liesma'][0]
    assert blue.foreground('castula',cb).tobytes()==blue.foreground('liesma',lb).tobytes()
    print('PASS: same charcoal/gold building colours in Castula and Liesma')
    print('PASS: no palette or metatile slots added; all maps, alignment, behaviours, flips and animations preserved')
    print('PASS: only station graphics/references and Liesma compiled tile count changed')

if __name__=='__main__':
    {'convert':convert,'verify':verify,'previews':previews,'graphics-patch':graphics_patch}[sys.argv[1]]()

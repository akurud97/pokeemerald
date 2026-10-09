"""Match Mintaka's door to its existing charcoal roof, including all door frames."""
from pathlib import Path
import importlib.util
import json
import shutil
import sys
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
REPORT=Path(__file__).resolve().parent
BEFORE=REPORT/'before'
TILESET=Path('data/tilesets/secondary/slateport_charcoal')
ANIMATION=Path('graphics/door_anims/slateport_charcoal_one_palette.png')
TILES=[0x329,0x334,0x33B,0x348,0x34F,0x358]
LUT={13:7,14:8}
spec=importlib.util.spec_from_file_location('native','dev_artifacts/liesma/build.py')
native=importlib.util.module_from_spec(spec);spec.loader.exec_module(native)

def convert():
    assert not BEFORE.exists(),'Never overwrite a backup'
    ms=native.words(ROOT/TILESET/'metatiles.bin')
    expected={0x329:(0x2D4,2),0x334:(0x2D4,3),
              0x33B:(0x2DC,0),0x348:(0x2DC,1),0x34F:(0x2DC,2),0x358:(0x2DC,3)}
    for tid in TILES:
        refs=[(i//8+512,i%8,e>>12) for i,e in enumerate(ms) if e&1023==tid]
        assert refs==[(*expected[tid],10)],(hex(tid),'unexpected shared graphic',refs)
    layout=json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts']
    test=next(l for l in layout if l['id']=='LAYOUT_MINTAKATEST')
    assert test['secondary_tileset']=='gTileset_SlateportCharcoal'
    shutil.copytree(ROOT/TILESET,BEFORE/TILESET)
    shutil.copytree(ROOT/'data/tilesets/primary/general',BEFORE/'data/tilesets/primary/general')
    for relative in [ANIMATION,Path('src/field_door.c'),Path('src/tileset_anims.c'),Path('data/layouts/layouts.json')]:
        dst=BEFORE/relative;dst.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(ROOT/relative,dst)
    for name in ['mintakatest','MintakaCity']:
        for base in ['data/maps','data/layouts']:
            shutil.copytree(ROOT/base/name,BEFORE/base/name)
    im=Image.open(ROOT/TILESET/'tiles.png').copy()
    for tid in TILES:
        pixels=native.tile(im,tid-512)
        pixels.putdata([LUT.get(v,v) for v in pixels.get_flattened_data()])
        im.paste(pixels,((tid-512)%16*8,(tid-512)//16*8))
    im.save(ROOT/TILESET/'tiles.png',bits=4)
    anim=Image.open(ROOT/ANIMATION).copy()
    anim.putdata([LUT.get(v%16,v%16) for v in anim.get_flattened_data()])
    anim.save(ROOT/ANIMATION,bits=4)
    previews()
    verify()

def previews():
    blocks=native.words(ROOT/'data/layouts/mintakatest/map.bin')
    native.render(ROOT/TILESET,blocks,5).resize((640,512),Image.Resampling.NEAREST).save(REPORT/'preview.png')
    anim=Image.open(ROOT/ANIMATION)
    palette=native.palette(ROOT/TILESET/'palettes/10.pal')
    anim.putpalette([channel for rgb in palette for channel in rgb])
    anim.convert('RGB').resize((128,768),Image.Resampling.NEAREST).save(REPORT/'door_frames.png')

def verify():
    old=Image.open(BEFORE/TILESET/'tiles.png');new=Image.open(ROOT/TILESET/'tiles.png')
    assert old.size==new.size and new.mode=='P'
    for i in range(old.width*old.height//64):
        a,b=native.tile(old,i).tobytes(),native.tile(new,i).tobytes()
        expected=bytes(LUT.get(v,v) for v in a) if i+512 in TILES else a
        assert b==expected,('unexpected tile edit',hex(i+512))
        assert [v!=0 for v in a]==[v!=0 for v in b]
    a,b=Image.open(BEFORE/ANIMATION),Image.open(ROOT/ANIMATION)
    assert a.size==b.size==(16,96) and b.mode=='P'
    assert bytes(v%16 for v in b.get_flattened_data())==bytes(LUT.get(v%16,v%16) for v in a.get_flattened_data())
    for relative in [TILESET,Path('data/tilesets/primary/general'),Path('data/maps'),Path('data/layouts')]:
        for saved in (BEFORE/relative).rglob('*'):
            if not saved.is_file() or saved==BEFORE/TILESET/'tiles.png':continue
            assert saved.read_bytes()==(ROOT/saved.relative_to(BEFORE)).read_bytes(),saved
    for relative in ['src/field_door.c','src/tileset_anims.c']:
        assert (BEFORE/relative).read_bytes()==(ROOT/relative).read_bytes()
    print('PASS: only six closed-door tiles and the matching custom animation recoloured')
    print('PASS: blue window, knob, facade, roof, all palettes, maps, behaviours, animations and registrations preserved')

if __name__=='__main__':
    {'convert':convert,'verify':verify,'previews':previews}[sys.argv[1]]()

"""Lighten only the original door's brown regions, not its dark detailing."""
from pathlib import Path
import importlib.util
import shutil
import sys
from PIL import Image

ROOT=Path(__file__).resolve().parents[2]
REPORT=Path(__file__).resolve().parent
BEFORE=REPORT/'before'
spec=importlib.util.spec_from_file_location('black_door',ROOT/'dev_artifacts/mintaka_black_door/convert.py')
black=importlib.util.module_from_spec(spec);spec.loader.exec_module(black)
ORIGINAL=black.BEFORE
native=black.native
LUT={13:6,14:15}

def convert():
    assert not BEFORE.exists(),'Never overwrite a backup'
    black.verify()
    # Preserve the current black version separately from its earlier brown backup.
    for saved in ORIGINAL.rglob('*'):
        if saved.is_file():
            relative=saved.relative_to(ORIGINAL);dest=BEFORE/relative
            dest.parent.mkdir(parents=True,exist_ok=True)
            shutil.copy2(ROOT/relative,dest)
    original=Image.open(ORIGINAL/black.TILESET/'tiles.png')
    current=Image.open(ROOT/black.TILESET/'tiles.png').copy()
    for tid in black.TILES:
        source=native.tile(original,tid-512)
        pixels=native.tile(current,tid-512)
        pixels.putdata([LUT.get(a,b) for a,b in zip(source.get_flattened_data(),pixels.get_flattened_data())])
        current.paste(pixels,((tid-512)%16*8,(tid-512)//16*8))
    current.save(ROOT/black.TILESET/'tiles.png',bits=4)
    source=Image.open(ORIGINAL/black.ANIMATION)
    current=Image.open(ROOT/black.ANIMATION).copy()
    current.putdata([LUT.get(a%16,b%16) for a,b in zip(source.get_flattened_data(),current.get_flattened_data())])
    current.save(ROOT/black.ANIMATION,bits=4)
    black.REPORT=REPORT
    black.previews()
    verify()

def verify():
    original=Image.open(ORIGINAL/black.TILESET/'tiles.png')
    before=Image.open(BEFORE/black.TILESET/'tiles.png')
    after=Image.open(ROOT/black.TILESET/'tiles.png')
    assert before.size==after.size and after.mode=='P'
    for i in range(before.width*before.height//64):
        old,new=native.tile(before,i).tobytes(),native.tile(after,i).tobytes()
        if i+512 in black.TILES:
            source=native.tile(original,i).tobytes()
            expected=bytes(LUT.get(a,b) for a,b in zip(source,old))
        else:expected=old
        assert new==expected,('unexpected tile change',hex(i+512))
        assert [v!=0 for v in old]==[v!=0 for v in new]
    original=Image.open(ORIGINAL/black.ANIMATION)
    old,new=Image.open(BEFORE/black.ANIMATION),Image.open(ROOT/black.ANIMATION)
    assert old.size==new.size==(16,96)
    assert bytes(v%16 for v in new.get_flattened_data())==bytes(LUT.get(a%16,b%16) for a,b in zip(original.get_flattened_data(),old.get_flattened_data()))
    changed={black.TILESET/'tiles.png',black.ANIMATION}
    for saved in BEFORE.rglob('*'):
        if saved.is_file():
            relative=saved.relative_to(BEFORE)
            if relative not in changed:assert saved.read_bytes()==(ROOT/relative).read_bytes(),relative
    print('PASS: door fill lifted to palette 10 index 15 (56,64,80), highlights to index 6 (96,104,120)')
    print('PASS: dark details, blue glass, knob, roof, facade, all palettes, maps and registrations preserved')
    print('PASS: all opening/closing frames use the same lighter door shades')

if __name__=='__main__':
    {'convert':convert,'verify':verify}[sys.argv[1]]()

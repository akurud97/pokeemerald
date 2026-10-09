"""Match metatile 0x229's transparent patch to the straw ground."""
from pathlib import Path
import shutil
import struct
import json
from PIL import Image, ImageDraw
from chimney import words, render, palette
from refine import tile

ROOT = Path(__file__).resolve().parents[2]
DEST = ROOT / 'data/tilesets/secondary/fallarbor_cedar'
PRIMARY = ROOT / 'data/tilesets/primary/general'
REPORT = Path(__file__).resolve().parent / 'straw_patch'
MID = 0x229
SOURCE_TILES = [0x24B, 0x24C, 0x25B, 0x25C]
REMAP = {0: 0, 3: 6, 11: 5, 4: 7, 13: 8}
DARK = (136, 120, 72)

def main():
    assert not REPORT.exists(), 'Never overwrite an existing backup'
    original = words(DEST / 'metatiles.bin')
    entries = original.copy()
    pm = words(PRIMARY / 'metatiles.bin')
    oldsheet = Image.open(DEST / 'tiles.png')
    ps = Image.open(PRIMARY / 'tiles.png')
    assert oldsheet.mode == 'P' and oldsheet.width == 128
    sheet = oldsheet.copy()
    used8 = set()
    for e in pm+original:
        tid = e & 1023
        if e >> 12 == 8:
            used8.update(tile(ps if tid < 512 else oldsheet, tid % 512).get_flattened_data())
    assert 8 not in used8, 'The requested spare shade is already used'
    oldpal = palette(DEST / 'palettes/08.pal')
    newpal = oldpal.copy()
    newpal[8] = DARK
    refs = {e & 1023 for e in pm+original}
    free = [i for i in range(1,min(504,oldsheet.width*oldsheet.height//64))
            if i+512 not in refs and not any(tile(oldsheet,i).get_flattened_data())]
    assert len(free) >= 4
    copied = {}
    addresses = {(MID-512)*8+off for off in range(4,8)}
    for off,tid in zip(range(4,8),SOURCE_TILES):
        address = (MID-512)*8+off
        old = original[address]
        assert old & 1023 == tid and old >> 12 == 11
        assert [i for i,e in enumerate(original) if e&1023 == tid] == [address]
        im = tile(oldsheet,tid-512)
        values = list(im.get_flattened_data())
        assert set(values) <= set(REMAP)
        remapped = [REMAP[i] for i in values]
        assert [i == 0 for i in values] == [i == 0 for i in remapped]
        local = free.pop(0)
        copied[tid] = local+512
        im.putdata(remapped)
        sheet.paste(im,(local%16*8,local//16*8))
        entries[address] = (old & 0x0C00) | (local+512) | 8 << 12
    before = render(DEST,[MID],1,oldsheet,original,{8:oldpal})
    after = render(DEST,[MID],1,sheet,entries,{8:newpal})
    REPORT.mkdir()
    backup = REPORT/'before'
    shutil.copytree(DEST,backup/'secondary')
    layouts = json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts']
    preserved = ['data/layouts/layouts.json','graphics/door_anims/fallarbor_cedar.png']
    for l in layouts:
        if l['secondary_tileset'] == 'gTileset_FallarborCedar':
            preserved += [l['blockdata_filepath'],l['border_filepath']]
    for path in preserved:
        target = backup/path
        target.parent.mkdir(parents=True,exist_ok=True)
        shutil.copy2(ROOT/path,target)
    # Palette entry 8 is edited via apply_patch after this guarded binary edit.
    sheet.save(DEST/'tiles.png',optimize=False)
    (DEST/'metatiles.bin').write_bytes(struct.pack('<'+'H'*len(entries),*entries))
    allocated = {i-512 for i in copied.values()}
    for slot in range(sheet.width*sheet.height//64):
        if slot not in allocated:
            assert list(tile(sheet,slot).get_flattened_data()) == list(tile(oldsheet,slot).get_flattened_data())
        else:
            assert not any(tile(oldsheet,slot).get_flattened_data())
    for i,(old,new) in enumerate(zip(original,entries)):
        assert old == new or i in addresses
        assert old & 0x0C00 == new & 0x0C00
    assert sheet.mode == 'P' and sheet.size == oldsheet.size and max(sheet.get_flattened_data()) < 16
    assert len(entries) == len(original)
    for saved in (backup/'secondary').rglob('*'):
        if saved.is_file():
            rel = saved.relative_to(backup/'secondary')
            if rel not in (Path('tiles.png'),Path('metatiles.bin')):
                assert saved.read_bytes() == (DEST/rel).read_bytes()
    for path in preserved:
        assert (ROOT/path).read_bytes() == (backup/path).read_bytes()
    before.save(REPORT/'patch_before.png')
    after.save(REPORT/'patch_after.png')
    after.resize((256,256),Image.Resampling.NEAREST).save(REPORT/'preview.png')
    comparison = Image.new('RGB',(536,300),(242,240,235))
    draw = ImageDraw.Draw(comparison)
    for i,(label,im) in enumerate([('Previous grey patch',before),('Matching straw patch',after)]):
        draw.text((8+i*268,8),label,fill=(30,30,35))
        comparison.paste(im.resize((256,256),Image.Resampling.NEAREST),(8+i*268,32))
    comparison.save(REPORT/'comparison.png')
    print('Copied 8x8 tile IDs:',{hex(k):hex(v) for k,v in copied.items()})
    print('PASS: only 0x229 top layer changed; original pixels, transparency, flips, bottom layer, behaviour, maps and doors preserved.')

if __name__ == '__main__':
    main()

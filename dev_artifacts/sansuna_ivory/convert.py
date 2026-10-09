"""Ivory adobe house / teal Sootopolis door on the existing Sansuna test map."""
from pathlib import Path
import importlib.util
import json
import shutil
import struct
import sys
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
REPORT = Path(__file__).resolve().parent
BACKUP = REPORT / 'before'
SOURCE = ROOT / 'data/tilesets/secondary/lavaridge'
DEST = ROOT / 'data/tilesets/secondary/lavaridge_ivory'
PRIMARY = ROOT / 'data/tilesets/primary/general'
spec = importlib.util.spec_from_file_location('native_liesma', ROOT / 'dev_artifacts/liesma/build.py')
native = importlib.util.module_from_spec(spec)
spec.loader.exec_module(native)
words, palette, render = native.words, native.palette, native.render
REGISTRATIONS = ['data/layouts/layouts.json', 'src/data/tilesets/graphics.h',
                 'src/data/tilesets/metatiles.h', 'src/data/tilesets/headers.h',
                 'include/tilesets.h', 'src/field_door.c', 'include/constants/metatile_labels.h',
                 'porymap_scripts/tileset_animation/project_tileset_copies.js']
COLOURS = [
    (115,197,164), (248,248,232), (240,232,208), (232,224,200),
    (208,192,160), (160,144,120), (120,104,88), (80,72,64),
    (41,49,90), (0,0,0), (0,0,0), (64,176,160),
    (40,144,136), (24,112,112), (16,80,88), (0,0,0),
]

def prepare():
    assert not BACKUP.exists() and not DEST.exists(), 'Do not overwrite an existing copy or backup'
    layouts = json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']
    layout = next(l for l in layouts if l['id'] == 'LAYOUT_SANSUNATEST')
    assert layout['secondary_tileset'] == 'gTileset_Lavaridge' and layout['primary_tileset'] == 'gTileset_General'
    assert (layout['width'],layout['height']) == (3,4)
    blocks = words(ROOT / layout['blockdata_filepath'])
    ids = [b & 1023 for b in blocks]
    assert ids == [0x3D3,0x3D4,0x3D5,0x3DB,0x3DC,0x3DD,0x3E3,0x3E4,0x3E5,0x3EB,0x3EC,0x3ED]
    source_entries = words(SOURCE / 'metatiles.bin')
    uses = {i+512 for i in range(512) if any(e >> 12 == 12 for e in source_entries[i*8:i*8+8])}
    assert uses == set(ids) | {0x3F0,0x3F1,0x3F2,0x3F3,0x3F8,0x3F9,0x3FA,0x3FB}, 'Palette12 used by unrelated metatiles'
    BACKUP.mkdir()
    shutil.copytree(SOURCE, BACKUP / 'secondary')
    shutil.copytree(PRIMARY, BACKUP / 'primary')
    shutil.copytree(ROOT / 'data/maps/sansunatest', BACKUP / 'data/maps/sansunatest')
    shutil.copytree(ROOT / 'data/layouts/sansunatest', BACKUP / 'data/layouts/sansunatest')
    for relative in REGISTRATIONS + ['graphics/door_anims/sootopolis.png']:
        target = BACKUP / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / relative, target)
    shutil.copytree(SOURCE, DEST)
    # Only the imported door gains animated-door behaviour; preserve its upper
    # attribute flags and every map block/collision/elevation value.
    attrs = words(DEST / 'metatile_attributes.bin')
    assert attrs[0x3EC-512] == 0
    attrs[0x3EC-512] = (attrs[0x3EC-512] & 0xFE00) | 0x69
    (DEST / 'metatile_attributes.bin').write_bytes(struct.pack('<512H', *attrs))
    door_dest = ROOT / 'graphics/door_anims/lavaridge_ivory_sootopolis.png'
    assert not door_dest.exists()
    shutil.copy2(ROOT / 'graphics/door_anims/sootopolis.png', door_dest)
    match_door_corner()
    chunks = {}
    def update(relative, old, new):
        assert (ROOT / relative).read_text().count(old) == 1, (relative, old)
        chunks.setdefault('*** Update File: ' + str(ROOT / relative), []).extend(
            ['@@'] + ['-' + row for row in old.splitlines()] + ['+' + row for row in new.splitlines()])
    def after(relative, anchor, extra): update(relative, anchor, anchor + '\n' + extra)
    pal_path = 'data/tilesets/secondary/lavaridge_ivory/palettes/12.pal'
    pal_text = 'JASC-PAL\n0100\n16\n' + '\n'.join(' '.join(map(str,c)) for c in COLOURS) + '\n'
    update(pal_path, (ROOT / pal_path).read_text(), pal_text)
    chunk = '\n'.join('    ' + row for row in json.dumps(layout, indent=2).splitlines())
    update('data/layouts/layouts.json', chunk, chunk.replace('gTileset_Lavaridge', 'gTileset_LavaridgeIvory'))
    after('include/tilesets.h', 'extern const struct Tileset gTileset_LavaridgeForest;', 'extern const struct Tileset gTileset_LavaridgeIvory;')
    after('src/data/tilesets/metatiles.h', 'const u16 gMetatileAttributes_LavaridgeForest[] = INCBIN_U16("data/tilesets/secondary/lavaridge_forest/metatile_attributes.bin");',
          '\nconst u16 gMetatiles_LavaridgeIvory[] = INCBIN_U16("data/tilesets/secondary/lavaridge_ivory/metatiles.bin");\nconst u16 gMetatileAttributes_LavaridgeIvory[] = INCBIN_U16("data/tilesets/secondary/lavaridge_ivory/metatile_attributes.bin");')
    anchor = 'const u32 gTilesetTiles_LavaridgeForest[] = INCGFX_U32("data/tilesets/secondary/lavaridge_forest/tiles.png", ".4bpp.fastSmol", "-num_tiles 450 -Wnum_tiles");'
    pal_lines = '\n'.join(f'    INCGFX_U16("data/tilesets/secondary/lavaridge_ivory/palettes/{n:02}.pal", ".gbapal"),' for n in range(16))
    after('src/data/tilesets/graphics.h', anchor,
          '\nconst u32 gTilesetTiles_LavaridgeIvory[] = INCGFX_U32("data/tilesets/secondary/lavaridge_ivory/tiles.png", ".4bpp.fastSmol", "-num_tiles 450 -Wnum_tiles");\n\nconst u16 gTilesetPalettes_LavaridgeIvory[][16] =\n{\n' + pal_lines + '\n};')
    after('src/data/tilesets/headers.h', '    .tiles = gTilesetTiles_LavaridgeForest,\n    .palettes = gTilesetPalettes_LavaridgeForest,\n    .metatiles = gMetatiles_LavaridgeForest,\n    .metatileAttributes = gMetatileAttributes_LavaridgeForest,\n    .callback = InitTilesetAnim_Lavaridge,\n};',
          '\nconst struct Tileset gTileset_LavaridgeIvory =\n{\n    .isCompressed = TRUE,\n    .isSecondary = TRUE,\n    .tiles = gTilesetTiles_LavaridgeIvory,\n    .palettes = gTilesetPalettes_LavaridgeIvory,\n    .metatiles = gMetatiles_LavaridgeIvory,\n    .metatileAttributes = gMetatileAttributes_LavaridgeIvory,\n    .callback = InitTilesetAnim_Lavaridge,\n};')
    after('porymap_scripts/tileset_animation/project_tileset_copies.js',
          '    { source: "gTileset_Lavaridge", copy: "gTileset_LavaridgeForest", folder: "lavaridge_forest/anim" },',
          '    { source: "gTileset_Lavaridge", copy: "gTileset_LavaridgeIvory", folder: "lavaridge_ivory/anim" },')
    after('include/constants/metatile_labels.h', '#define METATILE_LavaridgeForest_Door  0x3AA',
          '\n// gTileset_LavaridgeIvory\n#define METATILE_LavaridgeIvory_Door 0x3EC')
    after('src/field_door.c', 'static const u8 sDoorAnimTiles_Sootopolis[] = INCGFX_U8("graphics/door_anims/sootopolis.png", ".4bpp");',
          'static const u8 sDoorAnimTiles_LavaridgeIvory[] = INCGFX_U8("graphics/door_anims/lavaridge_ivory_sootopolis.png", ".4bpp");')
    after('src/field_door.c', 'static const u8 sDoorAnimPalettes_Sootopolis[] = {6, 6, 6, 6, 6, 6, 6, 6};',
          'static const u8 sDoorAnimPalettes_LavaridgeIvory[] = {12, 12, 12, 12, 12, 12, 12, 12};')
    after('src/field_door.c', '    {METATILE_Sootopolis_Door,                              &gTileset_Sootopolis, DOOR_SOUND_NORMAL,  1, sDoorAnimTiles_Sootopolis, sDoorAnimPalettes_Sootopolis},',
          '    {METATILE_LavaridgeIvory_Door, &gTileset_LavaridgeIvory, DOOR_SOUND_NORMAL, 1, sDoorAnimTiles_LavaridgeIvory, sDoorAnimPalettes_LavaridgeIvory},')
    patch = ['*** Begin Patch']
    for header, content in chunks.items(): patch += [header] + content
    patch.append('*** End Patch')
    print(json.dumps({'patch':'\n'.join(patch)}))

def verify():
    for source_name, current in [('secondary', SOURCE), ('primary', PRIMARY)]:
        for saved in (BACKUP / source_name).rglob('*'):
            if saved.is_file(): assert saved.read_bytes() == (current / saved.relative_to(BACKUP / source_name)).read_bytes(), str(saved)
    for saved in (BACKUP / 'secondary').rglob('*'):
        if saved.is_file():
            relative = saved.relative_to(BACKUP / 'secondary')
            if relative not in (Path('palettes/12.pal'), Path('metatile_attributes.bin')):
                assert saved.read_bytes() == (DEST / relative).read_bytes(), 'Unexpected change: ' + str(relative)
    old_layouts = json.loads((BACKUP / 'data/layouts/layouts.json').read_text())
    expected = json.loads(json.dumps(old_layouts))
    layout = next(l for l in expected['layouts'] if l['id'] == 'LAYOUT_SANSUNATEST')
    layout['secondary_tileset'] = 'gTileset_LavaridgeIvory'
    assert expected == json.loads((ROOT / 'data/layouts/layouts.json').read_text()), 'Other layouts changed'
    for saved in (BACKUP / 'data/layouts/sansunatest').rglob('*'):
        if saved.is_file(): assert saved.read_bytes() == (ROOT / saved.relative_to(BACKUP)).read_bytes(), 'Map blocks or border changed'
    assert (BACKUP / 'data/maps/sansunatest/map.json').read_bytes() == (ROOT / 'data/maps/sansunatest/map.json').read_bytes()
    original_attrs = words(BACKUP / 'secondary/metatile_attributes.bin')
    current_attrs = words(DEST / 'metatile_attributes.bin')
    assert [(i+512,a,b) for i,(a,b) in enumerate(zip(original_attrs,current_attrs)) if a!=b] == [(0x3EC,0,0x69)]
    assert palette(DEST / 'palettes/12.pal') == COLOURS
    door = ROOT / 'graphics/door_anims/lavaridge_ivory_sootopolis.png'
    assert (BACKUP / 'graphics/door_anims/sootopolis.png').read_bytes() == (ROOT / 'graphics/door_anims/sootopolis.png').read_bytes()
    original_door, copied_door = Image.open(BACKUP / 'graphics/door_anims/sootopolis.png'), Image.open(door)
    assert original_door.mode == copied_door.mode == 'P' and original_door.size == copied_door.size
    for y in range(copied_door.height):
        for x in range(copied_door.width):
            old = original_door.getpixel((x,y)) % 16
            expected = 7 if x == 15 and y % 32 == 12 else old
            assert copied_door.getpixel((x,y)) % 16 == expected, 'Unexpected copied frame pixel change'
    blocks = words(ROOT / layout['blockdata_filepath'])
    before, after_im = render(SOURCE, blocks, 3), render(DEST, blocks, 3)
    before.save(REPORT / 'building_before.png')
    after_im.save(REPORT / 'building_after.png')
    after_im.resize((480,640), Image.Resampling.NEAREST).save(REPORT / 'preview.png')
    im = Image.open(door)
    rgb = Image.new('RGB', im.size)
    for y in range(im.height):
        for x in range(im.width): rgb.putpixel((x,y),COLOURS[im.getpixel((x,y))%16])
    # Every opening frame retains the exact static door surround and lintel.
    for frame in range(3):
        assert rgb.crop((0,frame*32,16,frame*32+13)).tobytes() == after_im.crop((16,32,32,45)).tobytes(), 'Sootopolis animation surround does not match building'
    rgb.resize((128,768), Image.Resampling.NEAREST).save(REPORT / 'door_animation_preview.png')
    field_door = (ROOT / 'src/field_door.c').read_text()
    assert 'METATILE_LavaridgeIvory_Door, &gTileset_LavaridgeIvory, DOOR_SOUND_NORMAL, 1, sDoorAnimTiles_LavaridgeIvory, sDoorAnimPalettes_LavaridgeIvory' in field_door
    assert 'sDoorAnimPalettes_LavaridgeIvory[] = {12, 12, 12, 12, 12, 12, 12, 12}' in field_door
    print('PASS: original assets unchanged; map blocks/collisions/border/dimensions preserved; palette12 only; no new tile/metatile slots; steam/lava callback and editor registration retained; independent matching Sootopolis door copy')

def match_door_corner():
    # The imported closed door has one darker lintel corner than the original
    # Sootopolis animation. Match it in the copy, never the original asset.
    door = Image.open(BACKUP / 'graphics/door_anims/sootopolis.png').copy()
    for frame in range(3):
        assert door.getpixel((15,frame*32+12)) % 16 == 6
        door.putpixel((15,frame*32+12),7)
    door.save(ROOT / 'graphics/door_anims/lavaridge_ivory_sootopolis.png', bits=4)

if __name__ == '__main__':
    if sys.argv[1:] == ['--prepare']: prepare()
    elif sys.argv[1:] == ['--verify']: verify()
    elif sys.argv[1:] == ['--match-door-corner']: match_door_corner()
    else: raise SystemExit('Use --prepare once or --verify')

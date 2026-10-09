"""Pack the two saved Liesma maps and Lilycove test house, without editing originals."""
from pathlib import Path
from collections import Counter
import json
import shutil
import struct
import sys
from PIL import Image, ImageDraw

ROOT = Path(__file__).resolve().parents[2]
REPORT = Path(__file__).resolve().parent
BACKUP = REPORT / 'before'
DEST = ROOT / 'data/tilesets/secondary/liesma'
PRIMARY = ROOT / 'data/tilesets/primary/general'
SOURCES = [('LiesmaCityNorth', 'battle_frontier_outside_east'),
           ('LiesmaCitySouth', 'battle_frontier_outside_west'),
           ('liesmatest', 'lilycove')]
REGISTRATIONS = ['data/layouts/layouts.json', 'data/maps/map_groups.json',
                 'src/data/tilesets/headers.h', 'src/data/tilesets/graphics.h',
                 'src/data/tilesets/metatiles.h', 'include/tilesets.h',
                 'include/tileset_anims.h', 'include/constants/metatile_labels.h',
                 'src/tileset_anims.c', 'src/field_door.c', 'data/event_scripts.s',
                 'porymap_scripts/tileset_animation/project_tileset_copies.js']

def words(path):
    data = path.read_bytes()
    return list(struct.unpack('<' + 'H' * (len(data) // 2), data))

def save_words(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(struct.pack('<' + 'H' * len(data), *data))

def palette(path):
    return [tuple(map(int, row.split())) for row in path.read_text().splitlines()[3:19]]

def tile(sheet, local_id):
    columns = sheet.width // 8
    x, y = local_id % columns * 8, local_id // columns * 8
    im = sheet.crop((x, y, x + 8, y + 8))
    im.putdata([i % 16 for i in im.get_flattened_data()])
    return im

def render(folder, blocks, width):
    sheets = [Image.open(PRIMARY / 'tiles.png'), Image.open(folder / 'tiles.png')]
    metatiles = [words(PRIMARY / 'metatiles.bin'), words(folder / 'metatiles.bin')]
    pals = [palette((PRIMARY if i < 6 else folder) / f'palettes/{i:02}.pal') for i in range(13)]
    out = Image.new('RGB', (width * 16, len(blocks) // width * 16))
    for pos, block in enumerate(blocks):
        mid = block & 1023
        entries = metatiles[mid >= 512][mid % 512 * 8:mid % 512 * 8 + 8]
        for off, entry in enumerate(entries):
            tid = entry & 1023
            im = tile(sheets[tid >= 512], tid % 512)
            if entry & 1024: im = im.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
            if entry & 2048: im = im.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
            for y in range(8):
                for x in range(8):
                    idx = im.getpixel((x, y))
                    if idx:
                        out.putpixel((pos % width * 16 + off % 2 * 8 + x,
                                      pos // width * 16 + off % 4 // 2 * 8 + y), pals[entry >> 12][idx])
    return out

def add_file(patch, relative, content):
    patch.extend(['*** Add File: ' + str(ROOT / relative)] + ['+' + row for row in content.splitlines()])

def insert_after(patch, relative, anchor, content):
    text = (ROOT / relative).read_text()
    assert text.count(anchor) == 1, (relative, anchor)
    patch.extend(['*** Update File: ' + str(ROOT / relative), '@@'] +
                 [' ' + row for row in anchor.splitlines()] + ['+' + row for row in content.splitlines()])

def prepare():
    assert not BACKUP.exists() and not DEST.exists(), 'Never overwrite a previous build/backup'
    layouts_data = json.loads((ROOT / 'data/layouts/layouts.json').read_text())
    layouts = layouts_data['layouts']
    source_layouts = {name: next(l for l in layouts if l['blockdata_filepath'] == f'data/layouts/{name}/map.bin') for name, _ in SOURCES}
    for name, folder in SOURCES:
        l = source_layouts[name]
        assert l['primary_tileset'] == 'gTileset_General'
        assert l['secondary_tileset'] == 'gTileset_' + {'lilycove': 'Lilycove', 'battle_frontier_outside_east': 'BattleFrontierOutsideEast', 'battle_frontier_outside_west': 'BattleFrontierOutsideWest'}[folder]
        if name != 'liesmatest':
            assert not (ROOT / f'data/maps/{name}2').exists()
            assert not (ROOT / f'data/layouts/{name}2').exists()
    assert source_layouts['liesmatest']['width'] == 6 and source_layouts['liesmatest']['height'] == 5
    BACKUP.mkdir()
    for name, folder in SOURCES:
        shutil.copytree(ROOT / f'data/maps/{name}', BACKUP / f'data/maps/{name}')
        shutil.copytree(ROOT / f'data/layouts/{name}', BACKUP / f'data/layouts/{name}')
        shutil.copytree(ROOT / f'data/tilesets/secondary/{folder}', BACKUP / f'data/tilesets/secondary/{folder}')
    shutil.copytree(PRIMARY, BACKUP / 'data/tilesets/primary/general')
    for relative in REGISTRATIONS + ['graphics/door_anims/lilycove_wooden.png']:
        target = BACKUP / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / relative, target)

    DEST.mkdir(parents=True)
    # Keep the common flag's six VRAM slots; static graphics never occupy them.
    east = ROOT / 'data/tilesets/secondary/battle_frontier_outside_east'
    west = ROOT / 'data/tilesets/secondary/battle_frontier_outside_west'
    shutil.copytree(east / 'anim', DEST / 'anim')
    for file in (east / 'anim').rglob('*.png'):
        assert file.read_bytes() == (west / 'anim' / file.relative_to(east / 'anim')).read_bytes()
    sheet = Image.new('P', (128, 256), 0)
    sheet.putpalette(Image.open(east / 'tiles.png').getpalette())
    for i in range(218, 224):
        a, b = tile(Image.open(east / 'tiles.png'), i), tile(Image.open(west / 'tiles.png'), i)
        assert a.tobytes() == b.tobytes()
        sheet.paste(a, (i % 16 * 8, i // 16 * 8))
    tile_lookup = {bytes(64): 512}
    next_tile = 1
    def allocate_tile(pixels):
        nonlocal next_tile
        key = pixels.tobytes()
        if key not in tile_lookup:
            while 218 <= next_tile < 224: next_tile += 1
            assert next_tile < 504, 'No room for graphics'
            sheet.paste(pixels, (next_tile % 16 * 8, next_tile // 16 * 8))
            tile_lookup[key] = 512 + next_tile
            next_tile += 1
        return tile_lookup[key]

    entries = [0] * 4096
    attrs = [0] * 512
    met_lookup = {(tuple([0] * 8), 0): 512}
    next_mid = 513
    mappings = {}
    before_blocks = {}
    after_blocks = {}
    house = {}
    primary_entries = words(PRIMARY / 'metatiles.bin')
    assert all(e & 1023 < 512 for e in primary_entries), 'Primary references secondary graphics'
    # Preserve the used secondary palettes; reserve 7/8 for the new house.
    shutil.copytree(east / 'palettes', DEST / 'palettes')
    shutil.copy2(west / 'palettes/11.pal', DEST / 'palettes/11.pal')
    patch = ['*** Begin Patch']
    roof = palette(PRIMARY / 'palettes/05.pal')
    roof[2:9] = [(224,224,232), (192,192,208), (152,152,168), (128,128,144), (96,96,112), (64,72,88), (40,48,64)]
    roof[11:15] = [(248, 208, 216), (240, 160, 184), (224, 112, 152), (184, 72, 112)]
    facade = palette(PRIMARY / 'palettes/05.pal')
    facade[1:5] = [(248, 240, 216), (240, 224, 192), (216, 192, 152), (184, 160, 128)]
    facade[5:9] = [(128, 128, 136), (96, 96, 112), (64, 72, 88), (40, 48, 64)]
    facade[11:15] = [(248, 232, 192), (232, 208, 160), (208, 176, 128), (184, 144, 96)]
    facade[8], facade[15] = palette(PRIMARY / 'palettes/05.pal')[13:15]
    for number, colours in [(7, roof), (8, facade)]:
        content = 'JASC-PAL\n0100\n16\n' + '\n'.join(' '.join(map(str, rgb)) for rgb in colours) + '\n'
        current = (DEST / f'palettes/{number:02}.pal').read_text()
        patch.extend(['*** Update File: ' + str(DEST / f'palettes/{number:02}.pal'), '@@'] +
                     ['-' + row for row in current.splitlines()] + ['+' + row for row in content.splitlines()])

    for name, folder in SOURCES:
        l = source_layouts[name]
        src = ROOT / 'data/tilesets/secondary' / folder
        sm, sa = words(src / 'metatiles.bin'), words(src / 'metatile_attributes.bin')
        source_sheet = Image.open(src / 'tiles.png')
        blocks = words(ROOT / l['blockdata_filepath'])
        border = words(ROOT / l['border_filepath'])
        ids = sorted({v & 1023 for v in blocks + border if v & 1023 >= 512})
        mapping = {}
        if name == 'liesmatest':
            roles = {}
            for pos, block in enumerate(blocks):
                mid = block & 1023
                if mid < 512: continue
                role = 'roof' if pos // l['width'] < 3 else 'facade'
                assert mid not in roles or roles[mid] == role
                roles[mid] = role
        for mid in ids:
            mapped = []
            for off, e in enumerate(sm[(mid - 512) * 8:(mid - 512) * 8 + 8]):
                tid, pal = e & 1023, e >> 12
                if tid >= 512:
                    if name != 'liesmatest' and 730 <= tid < 736:
                        new_tid = tid
                    else:
                        new_tid = allocate_tile(tile(source_sheet, tid - 512))
                else:
                    new_tid = tid
                if name != 'liesmatest':
                    assert pal not in (7, 8), 'House would overwrite a city palette'
                    if pal == 11:
                        assert not any(tile(source_sheet if tid >= 512 else Image.open(PRIMARY / 'tiles.png'), tid % 512).tobytes()), 'Unexpected visible West palette 11'
                elif pal == 5 and mid != 0x28E:
                    pal = 7 if roles[mid] == 'roof' or (mid in {0x286, 0x2A3, 0x2AF, 0x2A5, 0x2A6} and off % 4 < 2) else 8
                mapped.append((e & 0xC00) | pal << 12 | new_tid)
            # Door graphics registrations are keyed to metatile, so no ambiguity
            # is allowed if appearance happens to coincide with a non-door.
            key = (tuple(mapped), sa[mid - 512])
            if key not in met_lookup:
                assert next_mid < 1024
                met_lookup[key] = next_mid
                entries[(next_mid - 512) * 8:(next_mid - 512) * 8 + 8] = mapped
                attrs[next_mid - 512] = sa[mid - 512]
                next_mid += 1
            mapping[mid] = met_lookup[key]
        mappings[name] = mapping
        remap = lambda items: [(v & 0xFC00) | mapping.get(v & 1023, v & 1023) for v in items]
        before_blocks[name], after_blocks[name] = blocks, remap(blocks)
        new_name = name if name == 'liesmatest' else name + '2'
        save_words(ROOT / f'data/layouts/{new_name}/map.bin', remap(blocks))
        save_words(ROOT / f'data/layouts/{new_name}/border.bin', remap(border))
        if name == 'liesmatest':
            house = {f'{mid:03X}': target for mid, target in mapping.items()}

    compiled_tiles = max(next_tile, 224)
    sheet.save(DEST / 'tiles.png', bits=4)
    save_words(DEST / 'metatiles.bin', entries)
    save_words(DEST / 'metatile_attributes.bin', attrs)
    door_dest = ROOT / 'graphics/door_anims/liesma_wooden.png'
    assert not door_dest.exists()
    shutil.copy2(ROOT / 'graphics/door_anims/lilycove_wooden.png', door_dest)

    # New maps are appended so existing map IDs remain stable. Only their mutual
    # North/South links are redirected; the original game world is untouched.
    new_layouts = []
    for name, _ in SOURCES[:2]:
        new_name = name + '2'
        map_data = json.loads((ROOT / f'data/maps/{name}/map.json').read_text())
        map_data['id'] += '2'
        map_data['name'] = new_name
        map_data['layout'] = source_layouts[name]['id'] + '2'
        for connection in map_data['connections'] or []:
            if connection['map'] in ['MAP_LIESMA_CITY_NORTH', 'MAP_LIESMA_CITY_SOUTH']:
                connection['map'] += '2'
        add_file(patch, f'data/maps/{new_name}/map.json', json.dumps(map_data, indent=2) + '\n')
        add_file(patch, f'data/maps/{new_name}/scripts.pory', f'raw `\n{new_name}_MapScripts::\n\t.byte 0\n`\n')
        add_file(patch, f'data/maps/{new_name}/scripts.inc', f'{new_name}_MapScripts::\n\t.byte 0\n')
        nl = dict(source_layouts[name])
        nl.update(id=nl['id'] + '2', name=new_name + '_Layout', secondary_tileset='gTileset_Liesma',
                  border_filepath=f'data/layouts/{new_name}/border.bin', blockdata_filepath=f'data/layouts/{new_name}/map.bin')
        new_layouts.append(nl)
    insert_after(patch, 'data/event_scripts.s', '\t.include "data/maps/liesmatest/scripts.inc"',
                 '\n\t.include "data/maps/LiesmaCityNorth2/scripts.inc"\n\n\t.include "data/maps/LiesmaCitySouth2/scripts.inc"')
    # Minimal JSON patches preserve formatting and unrelated entries.
    test_layout = source_layouts['liesmatest']
    old_chunk = json.dumps(test_layout, indent=2).splitlines()
    old_chunk = ['    ' + row for row in old_chunk]
    new_test = dict(test_layout, secondary_tileset='gTileset_Liesma')
    new_chunk = ['    ' + row for row in json.dumps(new_test, indent=2).splitlines()]
    new_chunk[-1] += ','
    for i, nl in enumerate(new_layouts):
        chunk = ['    ' + row for row in json.dumps(nl, indent=2).splitlines()]
        if i < len(new_layouts) - 1: chunk[-1] += ','
        new_chunk += chunk
    patch.extend(['*** Update File: ' + str(ROOT / 'data/layouts/layouts.json'), '@@'] +
                 ['-' + row for row in old_chunk] + ['+' + row for row in new_chunk])
    groups = json.loads((ROOT / 'data/maps/map_groups.json').read_text())
    last = groups['gMapGroup_testingstage'][-1]
    patch.extend(['*** Update File: ' + str(ROOT / 'data/maps/map_groups.json'), '@@',
                  '-    "' + last + '"', '+    "' + last + '",',
                  '+    "LiesmaCityNorth2",', '+    "LiesmaCitySouth2"'])
    palette_lines = '\n'.join(f'    INCGFX_U16("data/tilesets/secondary/liesma/palettes/{n:02}.pal", ".gbapal"),' for n in range(16))
    insert_after(patch, 'src/data/tilesets/graphics.h',
                 'const u32 gTilesetTiles_BattleFrontierOutsideWest[] = INCGFX_U32("data/tilesets/secondary/battle_frontier_outside_west/tiles.png", ".4bpp.fastSmol", "-num_tiles 508 -Wnum_tiles");',
                 f'\nconst u32 gTilesetTiles_Liesma[] = INCGFX_U32("data/tilesets/secondary/liesma/tiles.png", ".4bpp.fastSmol", "-num_tiles {compiled_tiles} -Wnum_tiles");\n\nconst u16 gTilesetPalettes_Liesma[][16] =\n{{\n{palette_lines}\n}};')
    insert_after(patch, 'src/data/tilesets/metatiles.h',
                 'const u16 gMetatiles_BattleFrontierOutsideWest[] = INCBIN_U16("data/tilesets/secondary/battle_frontier_outside_west/metatiles.bin");',
                 '\nconst u16 gMetatiles_Liesma[] = INCBIN_U16("data/tilesets/secondary/liesma/metatiles.bin");\nconst u16 gMetatileAttributes_Liesma[] = INCBIN_U16("data/tilesets/secondary/liesma/metatile_attributes.bin");')
    insert_after(patch, 'include/tilesets.h', 'extern const struct Tileset gTileset_Lilycove;', 'extern const struct Tileset gTileset_Liesma;')
    insert_after(patch, 'src/data/tilesets/headers.h',
                 '    .callback = InitTilesetAnim_BattleFrontierOutsideEast,\n};',
                 '\nconst struct Tileset gTileset_Liesma =\n{\n    .isCompressed = TRUE,\n    .isSecondary = TRUE,\n    .tiles = gTilesetTiles_Liesma,\n    .palettes = gTilesetPalettes_Liesma,\n    .metatiles = gMetatiles_Liesma,\n    .metatileAttributes = gMetatileAttributes_Liesma,\n    .callback = InitTilesetAnim_Liesma,\n};')
    insert_after(patch, 'include/tileset_anims.h', 'void InitTilesetAnim_BattleFrontierOutsideEast(void);', 'void InitTilesetAnim_Liesma(void);')
    insert_after(patch, 'src/tileset_anims.c', 'static void TilesetAnim_BattleFrontierOutsideEast(u16);', 'static void TilesetAnim_Liesma(u16);')
    frame_lines = '\n'.join(f'static const u16 sTilesetAnims_Liesma_Flag_Frame{i}[] = INCGFX_U16("data/tilesets/secondary/liesma/anim/flag/{i}.png", ".4bpp");' for i in range(4))
    insert_after(patch, 'src/tileset_anims.c',
                 'const u16 gTilesetAnims_BattleFrontierOutsideEast_Flag_Frame3[] = INCGFX_U16("data/tilesets/secondary/battle_frontier_outside_east/anim/flag/3.png", ".4bpp");',
                 '\n' + frame_lines + '\n\nstatic const u16 *const sTilesetAnims_Liesma_Flag[] = {\n    sTilesetAnims_Liesma_Flag_Frame0,\n    sTilesetAnims_Liesma_Flag_Frame1,\n    sTilesetAnims_Liesma_Flag_Frame2,\n    sTilesetAnims_Liesma_Flag_Frame3\n};')
    insert_after(patch, 'src/tileset_anims.c',
                 '    sSecondaryTilesetAnimCallback = TilesetAnim_BattleFrontierOutsideEast;\n}',
                 '\nvoid InitTilesetAnim_Liesma(void)\n{\n    sSecondaryTilesetAnimCounter = 0;\n    sSecondaryTilesetAnimCounterMax = sPrimaryTilesetAnimCounterMax;\n    sSecondaryTilesetAnimCallback = TilesetAnim_Liesma;\n}\n\nstatic void TilesetAnim_Liesma(u16 timer)\n{\n    if (timer % 8 == 0)\n    {\n        u16 frame = (timer / 8) % ARRAY_COUNT(sTilesetAnims_Liesma_Flag);\n        AppendTilesetAnimToBuffer(sTilesetAnims_Liesma_Flag[frame],\n            (u16 *)(BG_VRAM + TILE_OFFSET_4BPP(NUM_TILES_IN_PRIMARY + 218)), 6 * TILE_SIZE_4BPP);\n    }\n}')
    insert_after(patch, 'porymap_scripts/tileset_animation/project_tileset_copies.js',
                 '    { source: "gTileset_Rustboro", copy: "gTileset_Castula", folder: "castula/anim" },',
                 '    { source: "gTileset_BattleFrontierOutsideWest", copy: "gTileset_Liesma", folder: "liesma/anim" },')
    insert_after(patch, 'src/field_door.c',
                 'static const u8 sDoorAnimTiles_LilycoveWooden[] = INCGFX_U8("graphics/door_anims/lilycove_wooden.png", ".4bpp");',
                 'static const u8 sDoorAnimTiles_LiesmaWooden[] = INCGFX_U8("graphics/door_anims/liesma_wooden.png", ".4bpp");')
    insert_after(patch, 'src/field_door.c', 'static const u8 sDoorAnimPalettes_LilycoveWooden[] = {5, 5, 5, 5, 5, 5, 5, 5};',
                 'static const u8 sDoorAnimPalettes_LiesmaWooden[] = {7, 7, 8, 8, 5, 5, 5, 5};')
    city_doors = [('BattleDome', 0x28A, 'sDoorAnimTiles_BattleDome', 'sDoorAnimPalettes_BattleDome', 'DOOR_SOUND_SLIDING'),
                  ('Frontier', 0x3FC, 'sDoorAnimTiles_BattleFrontier', 'sDoorAnimPalettes_BattleFrontier', 'DOOR_SOUND_NORMAL')]
    labels = []
    door_rows = []
    for label, old_id, graphics, pals, sound in city_doors:
        target = mappings['LiesmaCitySouth'][old_id]
        labels.append(f'#define METATILE_Liesma_Door_{label} 0x{target:03X}')
        door_rows.append(f'    {{METATILE_Liesma_Door_{label}, &gTileset_Liesma, {sound}, 1, {graphics}, {pals}}},')
    target = mappings['liesmatest'][0x28E]
    labels.append(f'#define METATILE_Liesma_Door_Wooden 0x{target:03X}')
    door_rows.append('    {METATILE_Liesma_Door_Wooden, &gTileset_Liesma, DOOR_SOUND_NORMAL, 1, sDoorAnimTiles_LiesmaWooden, sDoorAnimPalettes_LiesmaWooden},')
    insert_after(patch, 'include/constants/metatile_labels.h', '#define METATILE_Lilycove_Door_Wooden      0x28E', '\n' + '\n'.join(labels))
    insert_after(patch, 'src/field_door.c', 'static const struct DoorGraphics sDoorAnimGraphicsTable[] =\n{\n#if !IS_FRLG', '\n'.join(door_rows))
    manifest = dict(compiled_tiles=compiled_tiles, unique_graphics=len(tile_lookup) + 6,
                    used_metatiles=next_mid - 512, house=house,
                    mappings={name: {f'{old:03X}': new for old, new in mapping.items()} for name, mapping in mappings.items()},
                    source_layouts=source_layouts, free_palettes=[6, 11])
    add_file(patch, 'dev_artifacts/liesma/manifest.json', json.dumps(manifest, indent=2) + '\n')
    # apply_patch requires one file operation containing all hunks per file.
    grouped = {}
    current = None
    for line in patch[1:]:
        if line.startswith(('*** Add File: ', '*** Update File: ')):
            current = line
            grouped.setdefault(current, [])
        else:
            grouped[current].append(line)
    output_patch = ['*** Begin Patch']
    for header, body in grouped.items(): output_patch += [header] + body
    output_patch.append('*** End Patch')
    print(json.dumps(dict(patch='\n'.join(output_patch), compiled_tiles=compiled_tiles, used_metatiles=next_mid - 512)))

def verify():
    manifest = json.loads((REPORT / 'manifest.json').read_text())
    layouts = json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']
    original_layouts = json.loads((BACKUP / 'data/layouts/layouts.json').read_text())['layouts']
    original_groups = json.loads((BACKUP / 'data/maps/map_groups.json').read_text())
    groups = json.loads((ROOT / 'data/maps/map_groups.json').read_text())
    expected_groups = json.loads(json.dumps(original_groups))
    expected_groups['gMapGroup_testingstage'] += ['LiesmaCityNorth2', 'LiesmaCitySouth2']
    assert groups == expected_groups, 'Existing map IDs/order changed'
    for saved in (BACKUP / 'data/tilesets').rglob('*'):
        if saved.is_file():
            assert saved.read_bytes() == (ROOT / saved.relative_to(BACKUP)).read_bytes(), str(saved)
    mets, attrs = words(DEST / 'metatiles.bin'), words(DEST / 'metatile_attributes.bin')
    assert len(mets) == 4096 and len(attrs) == 512
    assert all((e & 1023) < 512 + manifest['compiled_tiles'] for e in mets)
    assert manifest['compiled_tiles'] <= 504 and manifest['used_metatiles'] <= 512
    for name, folder in SOURCES:
        original_layout = next(l for l in original_layouts if l['blockdata_filepath'] == f'data/layouts/{name}/map.bin')
        original_blocks = words(BACKUP / original_layout['blockdata_filepath'])
        new_name = name if name == 'liesmatest' else name + '2'
        new_layout = next(l for l in layouts if l['blockdata_filepath'] == f'data/layouts/{new_name}/map.bin')
        assert new_layout['secondary_tileset'] == 'gTileset_Liesma'
        assert (new_layout['width'], new_layout['height']) == (original_layout['width'], original_layout['height'])
        mapping = {int(old, 16): new for old, new in manifest['mappings'][name].items()}
        source_entries = words(BACKUP / f'data/tilesets/secondary/{folder}/metatiles.bin')
        source_attrs = words(BACKUP / f'data/tilesets/secondary/{folder}/metatile_attributes.bin')
        source_sheet = Image.open(BACKUP / f'data/tilesets/secondary/{folder}/tiles.png')
        sheet = Image.open(DEST / 'tiles.png')
        for old, new in mapping.items():
            assert source_attrs[old - 512] == attrs[new - 512], 'Metatile behaviour/attributes changed'
            for before, after in zip(source_entries[(old-512)*8:(old-512)*8+8], mets[(new-512)*8:(new-512)*8+8]):
                assert before & 0xC00 == after & 0xC00, 'Flip flags changed'
                old_tid, new_tid = before & 1023, after & 1023
                if old_tid < 512: assert old_tid == new_tid
                else: assert tile(source_sheet, old_tid - 512).tobytes() == tile(sheet, new_tid - 512).tobytes()
        for key in ['blockdata_filepath', 'border_filepath']:
            before = words(BACKUP / original_layout[key])
            after = words(ROOT / new_layout[key])
            assert len(before) == len(after)
            assert all(a & 0xFC00 == b & 0xFC00 for a, b in zip(before, after)), 'Collision/elevation changed'
            assert after == [(v & 0xFC00) | mapping.get(v & 1023, v & 1023) for v in before]
        old_render = render(BACKUP / f'data/tilesets/secondary/{folder}', original_blocks, original_layout['width'])
        new_render = render(DEST, words(ROOT / new_layout['blockdata_filepath']), new_layout['width'])
        old_render.save(REPORT / f'{name}_before.png')
        new_render.save(REPORT / f'{new_name}_after.png')
        if name != 'liesmatest':
            assert old_render.tobytes() == new_render.tobytes(), name + ': appearance changed'
            assert next(l for l in layouts if l['id'] == original_layout['id']) == original_layout
            for saved in (BACKUP / f'data/layouts/{name}').rglob('*'):
                if saved.is_file(): assert saved.read_bytes() == (ROOT / saved.relative_to(BACKUP)).read_bytes()
            assert (BACKUP / f'data/maps/{name}/map.json').read_bytes() == (ROOT / f'data/maps/{name}/map.json').read_bytes()
            original_map = json.loads((ROOT / f'data/maps/{name}/map.json').read_text())
            new_map = json.loads((ROOT / f'data/maps/{new_name}/map.json').read_text())
            expected = json.loads(json.dumps(original_map))
            expected.update(id=expected['id']+'2', name=new_name, layout=original_layout['id']+'2')
            for conn in expected['connections'] or []:
                if conn['map'] in ['MAP_LIESMA_CITY_NORTH', 'MAP_LIESMA_CITY_SOUTH']: conn['map'] += '2'
            assert new_map == expected, 'New map events/connections changed unexpectedly'
            print(name + ': exact RGB appearance, pixels, attributes, collisions, dimensions and original map preserved')
        else:
            new_render.resize((768, 640), Image.Resampling.NEAREST).save(REPORT / 'house_preview.png')
            print('House: pixels, attributes, wood door and glass preserved; new roof/facade palettes')
    for i in range(4):
        assert (DEST / f'anim/flag/{i}.png').read_bytes() == (BACKUP / f'data/tilesets/secondary/battle_frontier_outside_east/anim/flag/{i}.png').read_bytes()
    original_door = Image.open(BACKUP / 'graphics/door_anims/lilycove_wooden.png')
    # PNGs store only the three opening frames. The closed frame is the map
    # itself (the engine's -1 offset), not the first PNG frame.
    door = Image.open(ROOT / 'graphics/door_anims/liesma_wooden.png')
    assert door.size == original_door.size and door.mode == original_door.mode == 'P'
    door_rgb = Image.new('RGB', door.size)
    for y in range(door.height):
        pal_path = DEST / ('palettes/07.pal' if y % 32 < 8 else 'palettes/08.pal') if y % 32 < 16 else PRIMARY / 'palettes/05.pal'
        pal = palette(pal_path)
        for x in range(door.width):
            idx = door.getpixel((x, y)) % 16
            old_idx = original_door.getpixel((x, y)) % 16
            expected = {13: 8, 14: 15}.get(old_idx, old_idx) if 8 <= y % 32 < 16 else old_idx
            assert idx == expected, 'Unexpected door pixel change'
            if 8 <= y % 32 < 16 and old_idx in (13, 14):
                assert pal[idx] == palette(PRIMARY / 'palettes/05.pal')[old_idx], 'Moving door wood colour changed'
            if idx: door_rgb.putpixel((x, y), pal[idx])
    door_rgb.resize((128, 768), Image.Resampling.NEAREST).save(REPORT / 'door_animation_preview.png')
    test_blocks = words(ROOT / 'data/layouts/liesmatest/map.bin')
    house_render = render(DEST, test_blocks, 6)
    for frame in range(3):
        assert door_rgb.crop((0, frame*32, 16, frame*32+8)).tobytes() == house_render.crop((16,48,32,56)).tobytes(), 'Door animation roof strip mismatches house'
    for number in (9, 10):
        assert palette(DEST / 'palettes/08.pal')[number] == palette(PRIMARY / 'palettes/05.pal')[number], 'House window glass changed'
    print(f"PASS: {manifest['used_metatiles']}/512 metatiles, {manifest['compiled_tiles']}/504 compiled tiles; flags and copied door intact")

def refine_door():
    manifest = json.loads((REPORT / 'manifest.json').read_text())
    entries = words(DEST / 'metatiles.bin')
    for source in [0x286, 0x2A3, 0x2AF, 0x2A5, 0x2A6]:
        mid = manifest['house'][f'{source:03X}']
        for off in range(8):
            address = (mid-512)*8 + off
            if off % 4 < 2 and entries[address] >> 12 == 8:
                entries[address] = (entries[address] & 0xFFF) | 7 << 12
    # Facade indices 8/15 aren't used by any static house pixels; they preserve
    # the two wood shades that swing up into the facade during the animation.
    sheet = Image.open(DEST / 'tiles.png')
    for mid in manifest['house'].values():
        for e in entries[(mid-512)*8:(mid-512)*8+8]:
            if e >> 12 == 8:
                assert not ({8, 15} & set(tile(sheet, (e&1023)-512).get_flattened_data()))
    save_words(DEST / 'metatiles.bin', entries)
    door = Image.open(BACKUP / 'graphics/door_anims/lilycove_wooden.png').copy()
    for y in range(door.height):
        for x in range(door.width):
            old = door.getpixel((x,y)) % 16
            if 8 <= y % 32 < 16:
                door.putpixel((x,y), {13: 8, 14: 15}.get(old, old))
    door.save(ROOT / 'graphics/door_anims/liesma_wooden.png', bits=4)
    print('Refined roof/facade transition and independent door opening frames')

if __name__ == '__main__':
    if sys.argv[1:] == ['--prepare']: prepare()
    elif sys.argv[1:] == ['--verify']: verify()
    elif sys.argv[1:] == ['--refine-door']: refine_door()
    else: raise SystemExit('Use --prepare once, then --verify')

"""Rename custom tilesets to city names, without altering any asset or map pixels."""
from pathlib import Path
import difflib
import hashlib
import json
import re
import shutil
import sys

ROOT=Path(__file__).resolve().parents[2]
REPORT=Path(__file__).resolve().parent
BEFORE=REPORT/'before'
RENAMES=[
    ('PetalburgLavender','Alasia','petalburg_lavender','alasia'),
    ('MauvilleBrick','Inquill','mauville_brick','inquill'),
    ('SlateportCharcoal','Mintaka','slateport_charcoal','mintaka'),
    ('MossdeepOrange','Uuba','mossdeep_orange','uuba'),
    ('LavaridgeForest','Acamar','lavaridge_forest','acamar'),
    ('LavaridgeIvory','Sansuna','lavaridge_ivory','sansuna'),
    ('FallarborCedar','Wurren','fallarbor_cedar','wurren'),
    ('FallarborRoseTent','WurrenStation','fallarbor_rose_tent','wurren_station'),
    ('DewfordTeal','Tiaki','dewford_teal','tiaki'),
]
TEXT_FILES=[
    'src/data/tilesets/headers.h','src/data/tilesets/graphics.h',
    'src/data/tilesets/metatiles.h','include/tilesets.h',
    'include/constants/metatile_labels.h','src/field_door.c',
    'data/layouts/layouts.json',
    'porymap_scripts/tileset_animation/project_tileset_copies.js',
    'dev_artifacts/tileset_animation_audit/verify.mjs',
]
UNTOUCHED_FILES=['src/tileset_anims.c','include/tileset_anims.h',
                 'data/maps/map_groups.json','porymap.user.cfg',
                 'porymap_scripts/tileset_animation/animations_pokeemerald.js']

def hash_file(path):return hashlib.sha256(path.read_bytes()).hexdigest()

def transform(text):
    for old,new,oldfolder,newfolder in RENAMES:
        text=text.replace(old,new).replace(oldfolder+'/',newfolder+'/')
    return text

def prepare():
    assert not BEFORE.exists(),'Never overwrite a backup'
    headers=(ROOT/TEXT_FILES[0]).read_text()
    layouts=json.loads((ROOT/'data/layouts/layouts.json').read_text())['layouts']
    for old,new,oldfolder,newfolder in RENAMES:
        src=ROOT/'data/tilesets/secondary'/oldfolder
        dest=ROOT/'data/tilesets/secondary'/newfolder
        assert src.is_dir() and not dest.exists(),(src,dest)
        assert 'const struct Tileset gTileset_'+old+' =' in headers
        assert 'const struct Tileset gTileset_'+new+' =' not in headers
    BEFORE.mkdir()
    manifest={'renames':RENAMES,'asset_hashes':{},'original_asset_hashes':{},
              'door_hashes':{},'map_hashes':{},'expected_text_hashes':{},'layouts':[]}
    oldfolders={r[2] for r in RENAMES}
    for old,new,oldfolder,newfolder in RENAMES:
        relative=Path('data/tilesets/secondary')/oldfolder
        shutil.copytree(ROOT/relative,BEFORE/relative)
        manifest['asset_hashes'][oldfolder]={str(p.relative_to(ROOT/relative)):hash_file(p)
                                          for p in (ROOT/relative).rglob('*') if p.is_file()}
    # Hash originals and other custom sets (Castula/Liesma) to prove they are untouched.
    for base in ['data/tilesets/primary','data/tilesets/secondary']:
        for p in (ROOT/base).rglob('*'):
            if not p.is_file():continue
            relative=p.relative_to(ROOT)
            if base.endswith('secondary') and relative.parts[3] in oldfolders:continue
            manifest['original_asset_hashes'][str(relative)]=hash_file(p)
    shutil.copytree(ROOT/'graphics/door_anims',BEFORE/'graphics/door_anims')
    manifest['door_hashes']={str(p.relative_to(ROOT)):hash_file(p)
                            for p in (ROOT/'graphics/door_anims').rglob('*') if p.is_file()}
    symbols={'gTileset_'+r[0] for r in RENAMES}
    for l in layouts:
        if l['secondary_tileset'] not in symbols:continue
        manifest['layouts'].append({'name':l['name'],'before':l['secondary_tileset'],
                                    'after':transform(l['secondary_tileset'])})
        for k in ['blockdata_filepath','border_filepath']:
            relative=Path(l[k]);dest=BEFORE/relative
            dest.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(ROOT/relative,dest)
            manifest['map_hashes'][str(relative)]=hash_file(ROOT/relative)
        relative=Path('data/maps')/Path(l['blockdata_filepath']).parent.name
        if (ROOT/relative).exists():shutil.copytree(ROOT/relative,BEFORE/relative)
    for relative in TEXT_FILES+UNTOUCHED_FILES:
        dest=BEFORE/relative;dest.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(ROOT/relative,dest)
    patch=['*** Begin Patch']
    for relative in TEXT_FILES:
        old=(ROOT/relative).read_text();new=transform(old)
        assert old!=new,relative
        manifest['expected_text_hashes'][relative]=hashlib.sha256(new.encode()).hexdigest()
        diff=list(difflib.unified_diff(old.splitlines(),new.splitlines(),lineterm=''))
        patch += ['*** Update File: '+str(ROOT/relative)]+['@@' if row.startswith('@@') else row for row in diff[2:]]
    patch.append('*** End Patch')
    (REPORT/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    print(json.dumps('\n'.join(patch)))

def patch_only():
    patch=['*** Begin Patch']
    for relative in TEXT_FILES:
        old=(BEFORE/relative).read_text()
        assert (ROOT/relative).read_text()==old,'Files changed after preparation: '+relative
        diff=list(difflib.unified_diff(old.splitlines(),transform(old).splitlines(),lineterm=''))
        patch += ['*** Update File: '+str(ROOT/relative)]+['@@' if row.startswith('@@') else row for row in diff[2:]]
    patch.append('*** End Patch')
    print(json.dumps('\n'.join(patch)))

def move_assets():
    manifest=json.loads((REPORT/'manifest.json').read_text())
    for relative,expected in manifest['expected_text_hashes'].items():
        assert hash_file(ROOT/relative)==expected,('Apply the text patch first',relative)
    for old,new,oldfolder,newfolder in RENAMES:
        source=ROOT/'data/tilesets/secondary'/oldfolder
        dest=ROOT/'data/tilesets/secondary'/newfolder
        assert source.is_dir() and not dest.exists(),(source,dest)
        for relative,expected in manifest['asset_hashes'][oldfolder].items():
            assert hash_file(source/relative)==expected,('Asset changed since backup',relative)
    for old,new,oldfolder,newfolder in RENAMES:
        (ROOT/'data/tilesets/secondary'/oldfolder).rename(ROOT/'data/tilesets/secondary'/newfolder)
        print(old,'→',new)
    verify()

def verify():
    manifest=json.loads((REPORT/'manifest.json').read_text())
    for old,new,oldfolder,newfolder in RENAMES:
        assert not (ROOT/'data/tilesets/secondary'/oldfolder).exists()
        dest=ROOT/'data/tilesets/secondary'/newfolder
        actual={str(p.relative_to(dest)):hash_file(p) for p in dest.rglob('*') if p.is_file()}
        assert actual==manifest['asset_hashes'][oldfolder],new+' assets changed'
    for group in ['original_asset_hashes','door_hashes','map_hashes']:
        for relative,expected in manifest[group].items():assert hash_file(ROOT/relative)==expected,relative
    for relative,expected in manifest['expected_text_hashes'].items():
        assert hash_file(ROOT/relative)==expected,relative
        assert (ROOT/relative).read_text()==transform((BEFORE/relative).read_text()),relative
    for relative in UNTOUCHED_FILES:
        assert (ROOT/relative).read_bytes()==(BEFORE/relative).read_bytes(),relative
    oldlayouts=json.loads((BEFORE/'data/layouts/layouts.json').read_text())
    current=json.loads((ROOT/'data/layouts/layouts.json').read_text())
    for l in oldlayouts['layouts']:l['secondary_tileset']=transform(l['secondary_tileset'])
    assert oldlayouts==current,'Unexpected map/layout change'
    known=set(re.findall(r'const struct Tileset (gTileset_\w+) =',(ROOT/'src/data/tilesets/headers.h').read_text()))
    for layout in current['layouts']:
        for key in ['primary_tileset','secondary_tileset']:
            assert layout[key]=='0' or layout[key] in known,(layout['id'],layout[key])
    for saved in (BEFORE/'data/maps').rglob('*'):
        if saved.is_file():assert saved.read_bytes()==(ROOT/saved.relative_to(BEFORE)).read_bytes(),saved
    print('PASS: nine tilesets renamed; '+str(len(manifest['layouts']))+' layouts updated')
    print('PASS: every graphics/palette/metatile/animation file is byte-identical')
    print('PASS: originals, city-named Castula/Liesma, doors, maps, collisions and runtime animations unchanged')

if __name__=='__main__':
    {'prepare':prepare,'patch':patch_only,'move-assets':move_assets,'verify':verify}[sys.argv[1]]()

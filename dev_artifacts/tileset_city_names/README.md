# City-based tileset names

These are renames only. Every graphics, palette, metatile, attribute, and animation
file is byte-for-byte unchanged. All 22 dependent layouts keep their existing
dimensions, block/border data, collisions, elevation, events, connections and IDs.

| Previous custom name | Current name | Current secondary folder |
| --- | --- | --- |
| PetalburgLavender | Alasia | alasia |
| MauvilleBrick | Inquill | inquill |
| SlateportCharcoal | Mintaka | mintaka |
| MossdeepOrange | Uuba | uuba |
| LavaridgeForest | Acamar | acamar |
| LavaridgeIvory | Sansuna | sansuna |
| FallarborCedar | Wurren | wurren |
| FallarborRoseTent | WurrenStation | wurren_station |
| DewfordTeal | Tiaki | tiaki |

Names in C/Porymap are `gTileset_Alasia`, `gTileset_Inquill`, etc. Their graphics,
palette and metatile symbols and folder references have matching city names.
Castula and Liesma already had city names and were left unchanged. Original
Petalburg, Mauville, Slateport, Mossdeep, Lavaridge, Fallarbor, Dewford and all
other original game tilesets are untouched.

Wurren and WurrenStation remain separate: WurrenTown and its surrounding maps
use Wurren; `wurrentest` uses WurrenStation with its aligned station pieces.
No maps have been switched between these two variants.

Door-table tileset pointers and custom C identifiers are updated, but the actual
door PNG filenames/pixels are deliberately unchanged. Shared original animation
callbacks remain shared; frame locations, intervals and ranges are unchanged.
The project-local Porymap registry and its live loader verifier use the new names,
including Tiaki's flag and Castula's fountain-only restriction.

## Backups and verification

`before/` contains all nine pre-rename tilesets, affected map/layout copies,
door files and source registrations. `manifest.json` records old/new names,
the 22 layout changes, and asset hashes. Prior experiment snapshots/manifests
and one-shot conversion scripts retain their historical names for provenance;
do not rerun those converters against the renamed live folders. Use the mapping
above when locating today's assets.

```sh
python3 dev_artifacts/tileset_city_names/rename.py verify
node dev_artifacts/tileset_animation_audit/verify.mjs
```

Reopen/reload the Porymap project so its tileset list and cached map selections
pick up the new names. No compatibility aliases or duplicate old-name tilesets
are left in the active project.

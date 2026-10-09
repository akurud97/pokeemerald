# Tileset animation audit — 2026-10-07

The Tiaki flag was not removed or changed in the game data. Metatiles `0x349`
and `0x34A` in DewfordTeal match Dewford exactly and reference all six flag tiles
(`0x2AA–0x2AF`). The callback and all four copied flag frames are intact.
The missing component was a registration for the copied tileset name in the
Porymap animation plugin.

| Copy | Runtime audit | Porymap registration fixed |
| --- | --- | --- |
| DewfordTeal | Flag callback, frames, slots and doors intact | Flag |
| MauvilleBrick | Callback, frames, slots and doors intact | Flowers |
| SlateportCharcoal | Callback, frames, slots and doors intact | Balloons |
| LavaridgeForest | Callback, steam frames, steam/lava slots and doors intact | Steam and shared cave lava |
| PetalburgLavender | Matches original (no secondary animation loop); doors intact | No secondary loop to register |
| MossdeepOrange | Matches original (no secondary animation loop); doors intact | No secondary loop to register |
| FallarborCedar | Matches original (no secondary animation loop); doors intact | No secondary loop to register |
| Castula | Custom callback/frame assets and door registrations present | Fountain only; reused building slots excluded |

A local plugin copy now contains the extra registrations. The shared plugin,
game source, frame PNGs, palettes and metatiles were not modified by this fix.
The original user config and relevant game source files are backed up in `before/`.

Validation passed:

- The actual Porymap plugin loader expanded all registrations without errors.
- Five animated copies cover 122 animated tiles and load 36 frame paths, including
  shared Lavaridge lava frames. All paths exist and have valid dimensions.
- Original vanilla editor definitions and plugin settings are unchanged.
- Seven recoloured copies retain their original callback and all original doors;
  copied PNG frames and pixels in dynamic tile slots match the originals.
- DewfordTeal's two flag metatiles retain all six registered animated tiles.
- Porymap successfully loaded the project-local script on TiakiTown with
  animations enabled. Two successive UI screenshots show the flag changing
  frames; no map edits were made during that check.

Run with Node and Python/Pillow:

```
node dev_artifacts/tileset_animation_audit/verify.mjs
python3 dev_artifacts/tileset_animation_audit/verify_assets.py
```

No ROM rebuild is needed for this editor-only fix. Future copy procedure is in
`porymap_scripts/tileset_animation/PROJECT_NOTES.md`.

Follow-up correction: the initial Castula registration inherited too much.
Rustboro's former windy-water range now contains Castula buildings. Both the
editor and game callback are restricted to the fountain; see
`dev_artifacts/castula_animation_fix/README.md`. The original audit counts above
describe the initial audit, not the corrected/current registry.

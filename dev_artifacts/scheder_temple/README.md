# Scheder indigo-and-sandstone temple

The temple displayed by `schedartest` now uses a dedicated secondary tileset,
`gTileset_Scheder`, cloned from Lilycove so the original Lilycove assets remain
unchanged. The installed colours reconstruct the selected “softened
indigo/sandstone” balanced-round mockup with indexed, hardware-safe colours.

Implementation:

- `schedartest` alone was switched from `gTileset_Lilycove` to
  `gTileset_Scheder`.
- 33 existing temple graphics were re-indexed in place. No pixel shapes were
  removed or redrawn.
- 208 existing palette-8 metatile references to those graphics were switched
  to Scheder palette 10. This also covers matching alternate temple pieces in
  the cloned set, not only the pieces visible on the test map.
- Scheder palette 10 contains the new indigo roof, sandstone/ivory wall, cedar
  trim, blue-grey foundation, and neutral stair ramps. Other palettes retain
  their Lilycove bytes.
- No graphic or metatile was appended. The cloned set remains at its source
  dimensions: 512 metatiles, 512 attributes, and a 128x360 indexed sheet.
- Lilycove's runtime callback is safe to reuse because
  `InitTilesetAnim_Lilycove` has no continuous secondary animation. The
  Lilycove normal, wooden, department-store, and Safari Zone door registrations
  were duplicated for the new tileset pointer.

`preview.png` is a native installed render; `preview_3x.png` is the same render
scaled with nearest-neighbour sampling. `manifest.json` records the affected
IDs and installed hashes. `analyze_layers.py` is a read-only region/graphics
audit helper and does not edit game data.

Verification completed: the tilesheet and palette convert with `gbagfx`, the
layout JSON parses, the project tileset-animation audit passes, and a full ROM
build succeeds when invoked with the installed devkitARM path
(`/opt/devkitpro/devkitARM`). No emulator playtest was performed.

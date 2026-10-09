# Sansuna ivory / teal adobe test

Only `sansunatest` (3×4) is switched to `gTileset_LavaridgeIvory`, a full copy of
the current Lavaridge secondary tileset. The original Lavaridge, General,
LavaridgeForest, SansunaCity and all other layouts are unchanged.

No free palette slots existed. Palette 12 is used exclusively by this adobe
building's 12 test metatiles and eight related border/edge variants, so the copy
recolours that existing palette: a single warm-ivory body with brown/taupe
shadows and a four-shade turquoise/teal door. No additional palette, metatile
or graphic-tile slots are required. Pixel geometry and tile flip flags are
unchanged. Related edge variants take on the same colours inside this copy.

Door metatile `0x3EC` now has animated-door behaviour `0x69` and a registration
using palette 12 for all eight quadrants. The animation is a separate Sootopolis
copy at `graphics/door_anims/lavaridge_ivory_sootopolis.png`; only one shadow
pixel per frame is adjusted to match the imported lintel corner. All moving-door
pixels are retained, and the original Sootopolis frames are untouched. No warp
destination is added to the empty test map.

The clone keeps Lavaridge's unchanged lava/steam callback and copies its
animation directory. It also has a project-local Porymap animation registration,
including the shared Cave lava frames. Animated VRAM tile ranges are untouched.
Compiled tile count remains 450.

`before/` holds the original map/layout files, complete primary/secondary assets,
original Sootopolis door and registration-source snapshots. To undo this test,
switch only sansunatest's secondary tileset back to `gTileset_Lavaridge`; its
original tile IDs, map blocks, collision/elevation bits and border were never
changed. Avoid restoring full registration snapshots over later changes.

`preview.png` and `door_animation_preview.png` are native palette renders.
`convert.py --verify` checks preservation, the door's static surround across
all opening frames, behaviour, registration and the palette. The guarded
`--prepare` mode is one-shot construction, not a restore command.

Native preservation/door checks, the Porymap animation-loader audit and
`make -j4` passed. The ROM built successfully; no emulator playtest was performed.

# Inquill warm brick roof test

The `inquilltest` layout in map group `testingstage` uses a new secondary
tileset, `gTileset_MauvilleBrick`, under `data/tilesets/secondary/mauville_brick`.
The original Mauville tileset remains untouched. Only this test layout was
switched; choose `gTileset_Mauville` in Porymap to restore its green roof.

The map is 5x4 metatiles, entirely occupied by the building. Its 14 metatiles are
`0x388`, `0x389`, `0x38A`, `0x38B`, `0x38C`, `0x390`, `0x391`, `0x392`,
`0x393`, `0x394`, `0x398`, `0x399`, `0x3A0`, `0x3A1`.

Palette 12 was unused in the source tileset. It now copies palette 6, with
only the roof greens at entries 1..4 changed to warm brick red:

- 248 192 160
- 248 152 120
- 224 104 80
- 184 80 64

The roof was subsequently lightened to better match the warm brick mockup.
`palette_12_dark_brick.pal` preserves the initial darker palette. The older
`comparison.png` and `preview.png` still show that first version; see
`light_brick_comparison.png` and `light_brick_preview.png` for the active colours.

Only these metatiles' palette-6 references are redirected to palette 12.
The yellow/cream facade, blue door and window, outlines and grass are preserved.
All secondary slots 6..12 are now used in the clone; none remains wholly unused.
Original palette 6 remains intact for other objects.

No indexed tile pixels, metatile behaviors, flips or map blocks were changed.
The clone retains Mauville's animation callback and the compiled count of 503
tiles, leaving the usual eight door-animation VRAM tiles free.

The Verdanturf door at `0x3A1` retains the original animation PNG and has a
separate palette array for this clone: 12,12,5,5,5,5,5,5. The clone's other
Mauville doors are also registered with their original graphics and palettes.
No original animation graphics or palette arrays were edited.

The PNG previews are rendered from the actual saved indexed assets, not game
captures. The ROM build completed successfully. `metatiles_before.bin`,
`palette_12_before.pal` and `map_before.bin`
preserve the original relevant data. The unchanged source tileset is also
available for restoring the copy. No warp destination or emulator playtest was
added; the test map currently has no warp events.

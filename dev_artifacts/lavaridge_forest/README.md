# Acumar forest-green / reddish-brown-door test

The active version keeps the initial forest-green roof and tries a richer
reddish-brown door. See `reddish_brown/` for the active preview and the preceding
palette backup. PNGs directly in this directory show the initial walnut-brown
version; `sage/` and `forest_warm_door/` retain the intermediate experiments.

Only the `acumartest` layout now uses `gTileset_LavaridgeForest`, backed by
`data/tilesets/secondary/lavaridge_forest`. The house is copied entirely from
General into the secondary tileset. All original General and Lavaridge PNGs,
palettes, metatiles and behavior attributes are unchanged.

The building and its animation use palette 12: 15 opaque colours and transparent
index 0. It has four forest-green roof shades, a two-shade reddish-brown door,
cream walls and blue glass. To fit one palette, two similar cream highlights
share a shade, and the blue glass shading is simplified. Pixel layout and
transparent masks are preserved. Grass still uses unchanged primary palette 2.

The nine occupied slots authorised by the user are 0x368,0x369,0x370..0x376.
Five already-blank, behavior-free slots complete the fourteen metatile copies:
0x354,0x36F,0x3A5,0x3AA,0x3AB. Blank 0x200 is deliberately left intact.

| Original primary metatile | Copied secondary metatile |
| --- | --- |
| 0x008 | 0x354 |
| 0x009 | 0x368 |
| 0x00A | 0x369 |
| 0x00B | 0x36F |
| 0x010 | 0x370 |
| 0x011 | 0x371 |
| 0x012 | 0x372 |
| 0x013 | 0x373 |
| 0x018 | 0x374 |
| 0x019 | 0x375 |
| 0x01A | 0x376 |
| 0x020 | 0x3A5 |
| 0x021 (door) | 0x3AA |
| 0x022 | 0x3AB |

The 5x4 map uses these copied IDs in place of its original primary IDs. Every
block's collision/elevation bits, every copied behavior attribute, all tile
flips and the existing border data are preserved.

Twenty-seven indexed tile copies occupy previously blank, unreferenced local
slots 1,11,27,37,43,59,75,78,84,86,87,88,91,93,94,97,98,99,100,101,104,107,
109,116,117,120,121. All existing nonblank tile pixels remain intact. Copies
stay below compiled tile count 450, and avoid lava slots 160..163, steam slots
288..295, and the door-animation VRAM area 504..511.

Door 0x3AA is registered under `METATILE_LavaridgeForest_Door` with a separate
indexed animation, `graphics/door_anims/lavaridge_forest.png`; all eight
quadrants use palette 12. The original General door animation is unchanged.

Other metatiles using palette 12 inside this copy also take on the new colours,
as authorised. Maps using original Lavaridge retain their original appearance.
Only the nine authorised occupied definitions and five blank definitions were
replaced inside the copy; the original source definitions remain recoverable.

`before/secondary/` preserves the complete original Lavaridge assets.
`before/map.bin` and `before/general_door.png` preserve the test placement and
source animation. To undo the test, restore `before/map.bin` to
`data/layouts/acumartest/map.bin` AND switch the layout back to
`gTileset_Lavaridge`. Merely switching the secondary tileset is insufficient
because the test now uses replacement secondary metatile IDs.

The PNG previews are actual saved-asset renders, not emulator screenshots.
The ROM build completed successfully. All 15 opaque palette colours remain
distinct at GBA colour precision.
No new warp destination or emulator playtest is added; the map has no warps.

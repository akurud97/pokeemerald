# Uuba tangerine roof test

Only the `uubatest` layout in `testingstage` now uses the separate secondary
tileset `gTileset_MossdeepOrange`, backed by
`data/tilesets/secondary/mossdeep_orange`. Original Mossdeep and General assets
remain intact.

This changes only two entries in palette 9, with no new palette slot:

- 13: 189 82 82 -> 248 152 88 (bright tangerine)
- 14: 131 57 65 -> 192 96 56 (orange/copper shadow)

The roof and facade share palette 9, but the facade does not use these two red
entries. The door itself uses unchanged primary palette 1. The validation found
1044 changed roof pixels and verified that every facade and door pixel stays
identical. All indexed PNGs, metatile definitions, behavior attributes and map
blocks remain byte-identical to their originals.

The Mossdeep door at 0x2A1 is registered for this new tileset with its unchanged
animation PNG and palette array 9,9,1,1,1,1,1,1. Its roof automatically receives
the copied tileset's new palette-9 colours. The original animation is not
edited. The clone's Space Center door registration remains on palette 8.

Other metatiles referencing the same two red entries will also change inside
this copy, as authorised. Potentially affected metatiles outside the test
building are: 0x291,0x296,0x298,0x29A,0x29B,0x29C,0x29D,0x29E,0x29F,0x2A6,
0x2A7,0x2AF,0x354,0x35D,0x35E,0x363,0x364,0x365,0x366,0x370,0x380.
Original maps still using `gTileset_Mossdeep` are unaffected.

`before/secondary/` contains the complete original Mossdeep asset folder.
`before/map.bin` and `before/mossdeep_door.png` preserve the map and door PNG.
To restore the test map's original colours, select `gTileset_Mossdeep` as its
secondary tileset; no map-block restoration is needed because none changed.

PNG previews are rendered from the actual saved indexed assets and palettes,
not emulator screenshots. The ROM build completed successfully.
No warp destination or emulator playtest is added;
the test map has no warp events.

# One-palette Mintaka building test

`mintakatest` still uses `gTileset_SlateportCharcoal`. The building itself now
uses only palette 10: 15 opaque colours plus transparent index 0. The grass
continues to use the existing General palette 2; it needs no new building slot.

The walls are more neutral white. Several near-identical roof/trim greys share
entries, and the door's two close blue glass shades share one entry. The brown
door retains its two shades. Pixel placement, transparent masks and flip flags
are preserved, though some colour distinctions are deliberately merged.

Palette 6 was restored to the original Slateport palette. It is no longer
needed by this building, but it is NOT globally unused: other metatiles in the
copied tileset still reference it. Objects using palette 10 elsewhere in this
copy can look different because its slots now contain the combined palette.
Original Slateport and General assets remain untouched.

Twenty-seven remapped tile copies use previously blank/unreferenced local
slots 82,83,95,106,111,115,122,127,143,174,175,188,189,202,203,269,297,308,
315,328,335,344,370,371,375,381,393. No previously nonblank tile is overwritten.
Balloon animation slots 224..227 and door slots 504..511 are excluded. The
compiled count remains 504. Test-map placement, collision/elevation bits and
all behavior attributes are unchanged from the two-palette version.

The active animation is a new indexed file:
`graphics/door_anims/slateport_charcoal_one_palette.png`. All eight animation
quadrants now use palette 10. The original Slateport animation and the previous
two-palette `slateport_charcoal.png` both remain intact.

`before/secondary/` contains the complete pre-change two-palette tileset.
`before/map.bin` and `before/slateport_charcoal.png` preserve its map and
animation. To revert to that version, restore the copied tileset assets and
change `sDoorAnimTiles_SlateportCharcoal` back to `slateport_charcoal.png` and
`sDoorAnimPalettes_SlateportCharcoal` back to `{6,6,10,10,10,10,10,10}`.
No map restoration is necessary unless its placement subsequently changes.

The palette was later moved from slot 6 to slot 10 without changing any colours
or indexed pixels. `slot_10/before/` preserves the complete previous slot-6
version and its map and animation. The PNG previews remain visually accurate;
they show the same colours regardless of the palette-slot number.

The PNG previews are actual saved-asset renders, not emulator screenshots.
The ROM build completed successfully, and all 15 opaque colours remain distinct
after conversion to GBA colour precision.
No warp destination or emulator playtest is added by this change.

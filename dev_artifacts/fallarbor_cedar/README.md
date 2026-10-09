# Wurrentest cedar building experiment

## Sun-dried straw ground

Metatile 0x229's patch now matches the straw ground. Its four top-layer 8x8
tiles (original IDs 0x24B, 0x24C, 0x25B, 0x25C) are copied into unused slots
and remapped to palette 8. Existing straw shades 5–7 are reused, plus the
previously unused entry 8 for the dark shade (136,120,72). Transparent pixel
placement, layer positions, flips and the four bottom-layer ground quadrants
are unchanged. No new palette or metatile slot is needed; original graphics
remain available. `straw_patch/before` preserves the preceding complete
tileset and affected map/layout/door assets. Native before/after previews are
in `straw_patch/comparison.png`; `straw_patch.py` checks pixel preservation.
Copies are global tile IDs 0x26F, 0x271, 0x272 and 0x273 (secondary-local
111, 113, 114 and 115). Verification passed and `make -j4` rebuilt the ROM
successfully. No emulator play-test was performed.

The five individual 8x8 edge graphics 0x363, 0x364, 0x365, 0x373 and 0x375 now
have matching straw-coloured copies. These are TILE IDs, not metatile IDs.
All 42 references in 17 existing metatiles switch to palette 8 and the copies;
layer positions, horizontal/vertical flips and every transparent pixel remain
unchanged, so the terrain beneath the overlays retains its original colours.
No additional palette entries or metatile slots were needed. The original edge
graphics remain available, and `straw_edges/before` backs up the preceding
tileset plus all affected map/layout/door files. `straw_edges/preview.png` and
`comparison.png` show the updated native map rendering.

Global tile-copy mapping: 0x363→0x25A, 0x364→0x25E, 0x365→0x25F,
0x373→0x264, 0x375→0x26E. This fills previously unused secondary-local slots
90, 94, 95, 100 and 110. `straw_edges.py` performs exact preservation checks.
Those checks passed and `make -j4` successfully rebuilt the ROM with the edge
changes. No emulator play-test was performed.

The ash ground from metatile 0x218 now uses palette 8's previously unused
entries 5–7. The straw base is (200,184,128), light specks (224,208,160), and
dark specks (168,152,96), all exactly aligned with GBA's 5-bit channels.
Existing palette-8 entries and every other palette remain unchanged.

The original ground graphic (tile 0x210) is preserved. A remapped copy occupies
previously unused secondary-local tile 89 (global tile 0x259). Every reference
to that exact bare-ground tile with palette 11 now uses the copy and palette 8,
including ground under layered objects. Only ground is recoloured: composite
object pixels, rocks, paths, roofs, trees, buildings and door animations are
not colour-swapped. Other mixed terrain/edge artwork with embedded old-colour
pixels is deliberately left intact to avoid mistaking object colours for ground.

`straw_ground/before` backs up the complete preceding tileset, layout JSON,
all three affected maps/borders, and cedar door animation. The affected layouts
are WurrenTown, HyadesRoute12 and wurrentest; none of their blockdata is edited.
`straw_ground/preview.png` and `comparison.png` show an exact native WurrenTown
crop, not an AI mockup. `straw_ground.py` performs the guarded conversion and
creates the backup; palette changes are made separately via apply_patch.

489 ground-quadrant references in 139 existing metatile definitions were
updated. Verification passed: only the one formerly blank graphics slot and
three unused palette entries changed, and all map/layout/attribute/door assets
are preserved. `make -j4` successfully rebuilt the ROM. Native rendering was
checked against the preview; no emulator play-test was performed.

## Current chimney variant

The active chimney is grey metal using existing General primary palette 3.
Only chimney quadrants in metatiles 0x320, 0x321, 0x328 and 0x329 switch to
palette 3; their roof quadrants remain palette 7. Neither palette is edited.
Ten already-generated chimney tiles are remapped in place; no new graphics,
metatile or palette slots are required. All original nonblank tiles, tile IDs,
flip flags, transparency, map blocks, layout, roof/facade/window pixels and door
animation are preserved. The darkest existing palette-3 shade has a slight
purple tint, which the user agreed to try in game.

`grey/before` backs up the complete bronze tileset and relevant map/layout,
door animation and primary palette 3. `grey/preview.png` and
`grey/comparison.png` show the current exact indexed rendering. `grey.py`
performed pixel/asset preservation checks. The result exactly matches the
approved native preview, and `make -j4` successfully rebuilt the ROM. Appearance
is not emulator-tested.

## Earlier bronze and blue chimney variants

The previous chimney was bronze/copper rather than blue-grey. `copper/before`
backs up the full previous blue version and current map/layout/door assets.
`copper/preview.png` and `copper/comparison.png` show that bronze version.
The change recolours only generated chimney graphics, reusing palette 7 as-is;
blue window glass, wood roof, facade, knob and door animation are unchanged.
One unused tile slot was needed to avoid overwriting an original nonblank tile.
The earlier blue chimney experiment remains recorded below for reference.

The user replaced Wurrentest with a 4x5 chimney building. Their saved map blocks,
layout dimensions, and border remain untouched. Metatiles 0x320, 0x321, 0x328,
and 0x329 now use colour-remapped chimney and roof tile copies. Palette 7 itself
is unchanged; the chimney uses its existing blue-grey, blue-green, and light
bronze/wood-neutral shades. No additional palette or metatile slots were used.

`chimney/before` backs up the complete refined tileset and the user's new map,
border, layout JSON, and current door animation. `chimney/preview.png` and
`chimney/comparison.png` show the actual current indexed assets. `chimney.py`
performed exact pixel-index remapping and preservation checks. The historical
`verify.py` and `refine.py` target the earlier 5x4 layout and should not be run
against this new saved map. The previous building's metatiles and door animation
remain as they were; only the four chimney metatile references and newly filled
blank graphics slots were changed.

Nine existing unused graphics slots (60–63, 72–74, 78, and 79) were filled;
matching previously remapped roof tiles were reused. Preservation checks passed
and `make -j4` successfully rebuilt the ROM for this 4x5 chimney version.

## Earlier 5x4 building and backups

Wurrentest uses the registered `gTileset_FallarborCedar` secondary tileset in
`data/tilesets/secondary/fallarbor_cedar`. All other maps keep their existing tilesets.

Palette 7 contains a weathered-brown roof, golden timber facade, matching wood
door, orange window accents, yellow knob, and blue-grey window frames. Blue
glass colours (9 and 10), ground colour (15), and transparent index (0) remain
unchanged. No extra palette or metatile slots were needed. The refined version
uses 26 existing unused blank 8x8 tile slots to separate shared colour roles.
Every pixel remains in its original place; only its palette index changes.
Metatile flip flags and counts, attributes, map blocks, and collision bits are
unchanged. All previously nonblank tiles remain untouched.

Door 0x2A5 uses the new `graphics/door_anims/fallarbor_cedar.png` animation copy
with palette 7. Its pixel indices are remapped by the same roof/door rules as
the static tiles. No original animation PNG was edited. The other original
Fallarbor door registrations remain available in the copy.

`before/secondary` is a complete original Fallarbor snapshot. `before` also
contains map/border blocks, the original door PNGs, and registration-file
snapshots. Do not restore entire registration files blindly; they may include
later user work. Reverting just the Wurrentest layout to `gTileset_Fallarbor`
restores the original appearance immediately.

All secondary palette slots 6–12 were already referenced, but the existing
building palette 7 was sufficient. Other palette-7 objects in this COPY are
affected and may need separate remapping before use. Original Fallarbor maps
remain unaffected. `refined/before` saves the complete first-pass copy,
previews, and door-registration source. `refined/comparison.png` compares that
first pass to the refined version. The unused tile slots are 10, 11, 12, 14,
15, 27, 28, 31, 34, 35, 36, 37, 40, 41, 42, 43, 44, 47, 50, 51, 52, 53,
56, 57, 58, and 59 (secondary-local indices).

`preview.png`, `comparison.png`, and `door_animation_preview.png` render the
actual indexed assets, not AI-generated mockups. `verify.py` checks preservation
and generates these previews using Pillow.

Verification passed, and `make -j4` successfully rebuilt `pokeemerald.gba`.
The appearance and door animation have not been play-tested in an emulator.

The 16-colour fit merges a few close window-frame grey shades and knob
highlights, but preserves their spatial patterns, transparency, and outlines.

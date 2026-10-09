# Lavender roof, grey facade, coral accents

The active facade has subsequently been switched to cream for comparison.
`palette_12_grey.pal` preserves this test's grey version. Only entries 1..4
in palette 12 changed; the indexed door animation automatically uses the new
colours. The images in this folder still show the grey test; the cream preview
is in `../cream_building/`.

Implemented in `gTileset_PetalburgLavender`, which is already selected by the
`alasiatest` layout in map group `testingstage`. Reload the project in Porymap
to see the saved assets. Original Petalburg assets are not modified.

Building rectangle: x=2..7, y=1..5, inclusive. These 22 metatiles are recoloured:
`0x20C`, `0x20D`, `0x20E`, `0x20F`, `0x214`, `0x215`, `0x216`, `0x217`,
`0x21E`, `0x21F`, `0x226`, `0x227`, `0x22C`, `0x22D`, `0x234`, `0x235`,
`0x241`, `0x242`, `0x243`, `0x249`, `0x24A`, `0x24B`.

- Roof reuses palette 7's existing lavender entries 11..14. Three entries
  unused by the first house (1..3) now preserve the rooftop fixture's silver.
- Palette 12, the last unused secondary slot, supplies grey walls and coral
  door/window accents. Other secondary slots 6..11 remain in use.
- 31 remapped tile copies occupy local tile slots 159..189. The original
  first 159 tiles remain intact; the compiled tile count is now 190.
- The earlier lavender/coral house's metatiles and visible colours are preserved.
- A separate `graphics/door_anims/birchs_lab_lavender.png` animation is registered
  for this clone's door at `0x249`, with the grey header above it at `0x241`.
  The original Birch's Lab animation remains intact.
- Map blocks, collision/elevation and metatile behavior attributes are unchanged.

All seven secondary palette slots (6..12) are now used. Future recolours may
still share palettes, but there is no completely unused secondary slot left.

`comparison.png`, `house_after.png` and `map_after.png` are previews rendered
from the actual saved indexed tiles, metatiles and palettes, not game captures.
The ROM builds successfully; no emulator playtest or new warp destination was
added. The existing test map has no warp events.

`before/` preserves the pre-change clone's tile PNG, metatiles, attributes,
palettes and the user's newly placed map. It does not back up the source code.
To undo only this second test, restore the clone assets from that snapshot,
restore its compiled tile count to 159, and switch this clone's Birch's Lab
door registration back to the original animation and palette array. Keep the
current map placement unless you also want to restore `before/map.bin`.

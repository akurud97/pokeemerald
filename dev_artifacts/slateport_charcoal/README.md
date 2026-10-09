# Mintaka charcoal / cool-white / walnut test

The active version now uses one building palette, slot 10, with a more neutral
white facade. Palette 6 is restored to the source Slateport colours. See
`one_palette/README.md` for that revision and its complete two-palette backup.
The details and images below describe the earlier two-palette version.

Only the `mintakatest` layout now uses `gTileset_SlateportCharcoal`, backed by
`data/tilesets/secondary/slateport_charcoal`. The source Slateport and General
tilesets remain untouched.

As requested, this copy replaces palette slots 6 and 10:

- Palette 6: charcoal roof, with multiple grey shades preserving the roof pattern.
- Palette 10: mostly-white facade with subtle blue-grey shadows, brown door,
  blue glass and the shared dark outlines.

Both slots were referenced by other metatiles in the source tileset. Those
objects can therefore look different inside this copy; their original versions
on maps still using `gTileset_Slateport` are unchanged. No claim is made that
the slots were unused. All secondary slots 6..12 remain allocated.

The building covers the full 5x4 test map. Its existing secondary metatiles are
`0x2C0`, `0x2C1`, `0x2C2`, `0x2C8`, `0x2C9`, `0x2CA`, `0x2D0`, `0x2D1`,
`0x2D2`, `0x2D4` and door `0x2DC`. Shared primary wall metatiles were copied
into this secondary tileset so the General palette need not change:

- `0x013` -> `0x396`
- `0x020` -> `0x397`
- `0x022` -> `0x398`

Only those replacements change the test map's block IDs; collision/elevation
bits and behavior attributes remain identical. Fifteen indexed tile copies use
previously blank, unreferenced local slots 1,15,16,17,31,34,35,47,51,63,64,67,
68,80,81. Every pre-existing nonblank tile remains intact. No primary graphics
were edited. Balloon animation slots 224..227 and door VRAM slots 504..511
are left alone. The compiled tile count stays 504.

`graphics/door_anims/slateport_charcoal.png` is a separate copy of the Slateport
door animation with the brown colour indices remapped. It uses palette 6 for
the first two quadrants and palette 10 for the remaining six. Original door
graphics and palette arrays remain intact. The copy's Battle Tent door retains
its original animation registration.

The complete original Slateport asset directory, the original test map blocks,
and the original door PNG are saved in `before/`. To undo the test, restore
`before/map.bin` to `data/layouts/mintakatest/map.bin` AND select
`gTileset_Slateport` in the layout. Switching tilesets alone is insufficient
because the bottom-wall copies at 0x396..0x398 only exist in this new tileset.

PNG previews are rendered from the actual indexed assets and palettes; they
are not emulator screenshots. The ROM build completed successfully.
No warp destination or emulator playtest was
added. The test map currently has no warp events.

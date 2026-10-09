# Petalburg lavender/coral colour test

The second test adds a lavender/grey/coral lab building. See
`grey_building/README.md` for its changes and backup. The original house's
colours remain available; the details below describe the first test.

The `alasiatest` layout in the `testingstage` map group now uses
`gTileset_PetalburgLavender`, backed by
`data/tilesets/secondary/petalburg_lavender`.

The original Petalburg tileset remains intact. To restore the original test-map
colours, select `gTileset_Petalburg` as this map's secondary tileset in Porymap.
No map blocks or metatile behavior attributes were changed.

House rectangle: x=2..6, y=1..4, inclusive. Its 14 metatiles are:
`0x26C`, `0x26D`, `0x26E`, `0x274`, `0x275`, `0x276`, `0x27C`,
`0x27D`, `0x27E`, `0x27F`, `0x284`, `0x286`, `0x287`, `0x28F`.

Only these metatiles' palette references were changed:

- Roof: original palette 10 copied into formerly unused palette 7. Entries
  11..14 supply the selected lavender highlights and shadows.
- Front: original palette 9 copied into formerly unused palette 11. Entries
  12..14 supply coral trim and door highlights and shadows.

All 8x8 graphics and flip flags remain identical. The new tileset keeps the
original palettes 9 and 10 for other objects. Other metatiles retain their
original palette references. Palette slots 7 and 11 were unused by the source
Petalburg metatiles before this change.

The Oldale door animation for `0x287` is registered for the new tileset and uses
palette 7 for its two roof quadrants and palette 11 for the remaining quadrants.
The original Littleroot and Birch's Lab door animations are also registered for
the clone with their original palettes. The test map currently has no warp
events; no new destination was assigned.

`comparison.png` and `map_before.png` / `map_after.png` are rendered from the
actual indexed tile graphics, metatile definitions, map data, and palettes.
The validation checked that all pixels outside the house rectangle render
identically and that tile references and behavior attributes are preserved.

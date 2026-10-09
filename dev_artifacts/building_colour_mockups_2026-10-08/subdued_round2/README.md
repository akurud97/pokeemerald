# Subdued building colour mockups — round 2

Generated October 8, 2026 as visual-direction mockups only. No game tilesets,
palettes, graphics, metatiles, maps, or source files were changed.

Each sheet presents three variants from left to right:

- Hotel: weathered copper-brown; dusty wine/taupe; existing Ever Grande pale
  stone/slate. Ever Grande palette 12 was blank and unreferenced in the current
  metatile data, so the first two are possible custom-palette directions.
- Hydrology lab: stormy teal; mineral blue-grey; moss/rust industrial.
  BattleFrontierOutsideWest palettes 7, 8, and 10 were unreferenced by its
  current metatile data, so these are possible replacement-palette directions.
- Temple: aged cedar; weathered sage; muted plum-brown. Lilycove palettes 10
  and 11 were unreferenced by its current metatile data, so these are possible
  custom-palette directions.
- Haunted house: weathered timber; dusty blue/mauve; faded salmon/soot. These
  use existing Inquill colour families because every normal secondary palette
  from 6 through 12 currently has references.
- Chateau: dusty lavender-grey; weathered blue-green; aubergine-brown. Liesma
  palette 6 was unreferenced by its current metatile data.
- Shopping mall: smoke blue/champagne; sea-glass/concrete; burgundy/graphite.
  Liesma palette 6 was unreferenced by its current metatile data.

The audit above only checked current palette references in each tileset's
metatile data. Re-audit all dependent maps, borders, animations, reserved engine
palettes, and current files before implementing or overwriting any palette.
Image-generation output is not indexed or pixel-exact; rebuild a selected look
from the original sprite and verified hardware palette values.

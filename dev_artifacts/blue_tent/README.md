# Blue tent (historical version)

The current live station is charcoal/gold. See
`../charcoal_gold_station/README.md` for its conversion and blue-version backup.

Replaces the dusty-rose tent experiment with the blue mockup's colour scheme.
All tent foreground pieces now use the unchanged shared **General palette 0**:
blue ramp indices 9, 12, 13, 14, plus pale blue-grey frame colours and white bulbs.
The darker outline becomes index 7 instead of palette 0's beige index 8.

Updated Castula, FallarborCedar (WurrenTown), FallarborRoseTent (aligned wurrentest),
and Liesma. The internal name FallarborRoseTent is retained to avoid changing map
selections; that tileset's tent is now blue. No new tileset copy was made.

All placements, tile IDs, flips, transparency, metatile behaviours, collision and
elevation, palettes, and runtime/editor animations are unchanged. The enlarged
door remains non-animated, as before. Liesma's tent still occupies 0x352–0x375;
the placement grids in ../dusty_rose_tent/README.md remain valid.

`before/` contains the full dusty-rose versions of all four tilesets, General,
affected map/layout files, door graphics, and registrations. This is separate
from the earlier pre-rose backups. `comparison.png` and individual previews are
native renders of the current indexed pixels, not AI mockups.

Verification:

```sh
python3 dev_artifacts/blue_tent/convert.py verify
node dev_artifacts/tileset_animation_audit/verify.mjs
```

Do not rerun `convert`: it refuses to overwrite this backup. The earlier rose
conversion verifier describes that historical version, not this newer blue one.

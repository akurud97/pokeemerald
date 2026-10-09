# Charcoal / gold station — current version

Replaces the blue experiment on Castula, FallarborCedar (WurrenTown),
FallarborRoseTent (aligned wurrentest), and Liesma. Names, map selections,
placements, collision/elevation, tile flips and metatile behaviours are unchanged.

All station foreground pieces use **General primary palette 5**, unchanged.
The roof is charcoal; posts and side walls are cool silver-grey. White roof bulbs
retain their original geometry. Gold is restricted to a small entrance lintel,
window-surround bands, and narrow vertical jambs. Original indexed graphics from
the pre-rose backup supply the dark outline shade lost in earlier recolours.

The existing 23 cloned graphics tiles per tileset were recoloured in place.
Three additional formerly blank, unreferenced graphics slots per tileset hold
selective gold variants; no new metatile or palette slots are needed. Liesma's
compiled tile count is 278 instead of 275 so these graphics are loaded in game.
Animation ranges and door VRAM are untouched. Runtime/editor animation code and
door PNGs/registrations are preserved. These enlarged station templates remain
non-animated doors, as they were before; no warps are added.

Liesma station IDs remain `0x352–0x375`. Placement grids in the earlier
`../dusty_rose_tent/README.md` still apply. FallarborRoseTent retains its historical
name, but the station in that tileset now uses charcoal/gold.

`before/` backs up the complete blue versions of the four tilesets, General,
affected maps/layouts, door graphics and registrations. Earlier blue/rose backups
are unchanged. `comparison.png` and individual previews are actual native renders
of indexed game graphics, not AI images.

Checks:

```sh
python3 dev_artifacts/charcoal_gold_station/convert.py verify
node dev_artifacts/tileset_animation_audit/verify.mjs
```

Do not rerun the conversion over an existing backup. The earlier blue/rose
verifiers describe historical versions; use this verifier for the current assets.

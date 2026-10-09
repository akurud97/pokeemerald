# Softer sage roof revision

This is a historical revision. The active version has reverted to the first
forest-green roof and original door brown; see the parent README.

`acumartest` continues to use the same `gTileset_LavaridgeForest` copy and
palette 12. Only its four roof shades (entries 7..10) are changed:

- 7: 208 224 176
- 8: 176 200 144
- 9: 144 176 120
- 10: 112 144 96

The door's two brown shades were also changed to colours sampled from the sage
mockup: entry 14 is 165 116 68 and entry 15 is 131 90 51. They are warmer and
more golden than the previous browns. `before_door_palette.pal` preserves the
sage-roof version before this door change. No extra palette slot is used.

The cream facade, glass, indexed graphics, metatile definitions, behaviors and
map placement remain unchanged. The separate door animation already uses
palette 12 and automatically receives both the sage roof and updated browns;
its PNG and registration require no edits.

`before/secondary/` preserves the complete previous forest-green copy;
`before/map.bin` and `before/door.png` preserve its map and animation. Restore
`before/secondary/palettes/12.pal` as the copy's palette 12 to return to forest.
Original General and Lavaridge remain untouched.

Previews are rendered from the actual saved indexed assets, not game captures.
The ROM rebuild completed successfully with both the sage roof and updated
brown door. All 15 opaque colours remain distinct at GBA precision.

# Forest roof with the sage mockup's brown door

This is a historical experiment. The active version now uses the first forest
test's original door browns again. `palette_12_before_original_door.pal` preserves
this warm-brown experiment; restore it to the copy's palette 12 to try it again.

The active `acumartest` building still uses `gTileset_LavaridgeForest` and only
palette 12. Roof entries 7..10 are restored to the original forest version:
184 232 144; 136 200 104; 88 168 80; 40 120 72.

Door entries 14..15 stay at the warmer sage-mockup browns:
165 116 68; 131 90 51. Every other palette entry is unchanged. The facade,
indexed graphics, metatile definitions, map placement and behaviors do not
change. All eight door-animation quadrants already use palette 12, so the
animation automatically receives the restored green roof and keeps the browns.

`palette_12_sage_before.pal` preserves the preceding sage-and-warm-brown version.
Restore it as the copy's `palettes/12.pal` to return to that combination.
Original General and Lavaridge assets remain untouched.

`preview.png` is rendered from the actual saved assets, not an emulator capture.
The ROM rebuilt successfully. Validation confirmed that the forest roof matches
the original forest colours and every facade/door pixel remains unchanged.

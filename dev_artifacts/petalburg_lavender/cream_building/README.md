# Cream front test

The lab building on `alasiatest` now uses warm cream walls, with its lavender
roof and coral door/window accents preserved. This changes only palette 12
entries 1..4 in `data/tilesets/secondary/petalburg_lavender/palettes/12.pal`:

1. Highlight: 248 240 216
2. Light: 224 208 184
3. Midtone: 200 176 152
4. Shadow: 168 144 128

No new palette slots, tile edits, map placement changes or animation graphics
were needed. The existing copied door animation reads palette 12 automatically.
Original Petalburg graphics and the first lavender house are unchanged.

The previous grey palette is saved at `../grey_building/palette_12_grey.pal`.
Restore it as the clone's `palettes/12.pal` to switch back to grey.

`house_after.png` and `map_after.png` are rendered asset previews, not game
screenshots. Reload Porymap and load the rebuilt ROM to see the cream version.

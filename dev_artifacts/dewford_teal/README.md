# Tiakitest teal/grey building

Tiakitest uses the registered secondary tileset `gTileset_DewfordTeal`, copied
from the user's current Dewford tileset into `data/tilesets/secondary/dewford_teal`.
No other layout is switched, and original Dewford and General primary assets
are untouched.

Two unused palette slots were available and are used without replacing any
existing tile colours: slot 6 for the teal roof, slot 11 for the light-grey
facade. Door and support-beam wood colours (indices 11–14) are exactly the
original General palette-5 gold/tan wood shades. The original window-glass
colours are also preserved. Roof/facade palette references change only in the
building's existing metatiles from the 5x4 Tiakitest map. No new tile or metatile
slots, pixel-index changes, or shade merges are needed. Tile IDs, flip flags,
metatile behaviours, collision/elevation bits, map blocks and dimensions remain
unchanged. The underlying sand quads stay on original primary palette 5.

Door 0x225 uses a separate copied PNG, `graphics/door_anims/dewford_teal.png`,
with palette array `{6,6,11,11,11,11,11,11}`. Its pixel data is byte-identical to
the original animation, but the independent copy is safe to edit later. The
source PNG's upper bank uses indices above 15; the preview and engine's 4bpp
conversion correctly use their low nibble. Original animations are not edited.
The original Battle Tower door is also registered for the clone using its
unchanged graphics and palette 9.

The clone retains the Dewford flag callback and compiled tile count 503. No new
tiles occupy the flag animation range (secondary-local 170–175) or door-animation
VRAM range (504–511).

`before/secondary` and `before/primary` are complete source snapshots. `before`
also includes map/border blocks, original door PNG, layout JSON and registration
source snapshots. Avoid restoring full registration snapshots blindly over
later user changes. Switching only Tiakitest back to `gTileset_Dewford` restores
its old colours immediately.

`preview.png`, `comparison.png` and `door_animation_preview.png` are native
indexed renders, not AI mockups. Run `convert.py --verify` with Pillow to verify
preservation and refresh previews. `--prepare` is guarded and should not be run
again. Verification passed before and after a successful `make -j4` ROM build;
appearance has not been tested in an emulator.

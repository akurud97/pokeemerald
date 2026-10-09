# Castula building / inherited water-animation collision

Castula's imported buildings occupy graphic tiles `0x280–0x29F`, which were the
animated windy-water slots in Rustboro. All nonblank tiles in that range now
contain building art and all used references are on building palette 12.
No legitimate water metatiles still use that range. Restoring Rustboro's entire
editor registration made the collision visible in Porymap; Castula's runtime
callback also retained the conflicting writes.

The fix removes **only Castula's windy-water animation**, in both the game
callback and project-local editor definition. Castula is now explicitly
fountain-only rather than assuming all animations from its donor still apply.
The fountain retains its original two frames, eight-tick interval and four tile
slots `0x3C0–0x3C3` (metatiles `0x339` / `0x341`). Primary General water,
original Rustboro, all other copies, and door animations are unchanged.

No map blocks, metatiles, PNGs, palettes, door registrations or tileset headers
were changed. Old water PNGs remain on disk; only their Castula C bindings and
callback calls were removed. `before/` backs up the source and editor settings,
complete Castula assets and blocks/borders for all layouts using Castula.

Checks:

```
python3 dev_artifacts/castula_animation_fix/verify.py
node dev_artifacts/tileset_animation_audit/verify.mjs
```

The editor loader test asserts that Castula animates only `0x3C0–0x3C3` and
never any building tile in `0x280–0x29F`. It also checks fountain references and
all earlier tileset registrations. Reload Porymap's project/scripts to clear
old water overlays and cached definitions; restarting the app also works.

Both regression checks and `make -j4` passed. The ROM build completed; the fix
has not been visually playtested in an emulator.

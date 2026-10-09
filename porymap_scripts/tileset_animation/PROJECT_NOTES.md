# Project tileset animations

This is a project-local copy of the existing GriffinRichards/Porymap-Animation
plugin. The original shared plugin at `/Users/andrewbecker/Porymap-Animation` is
unchanged. Only the Emerald animation data imports our additional registrations
from `project_tileset_copies.js`; original definitions and settings are preserved.

When copying a tileset, also:

1. Copy its `anim/` assets, preserving frame names and indexed pixels.
2. Retain the original C animation callback if the animated tiles and frames are
   unchanged. If changing the animated frames, provide a callback/arrays that
   reference the new assets instead of silently sharing the original frames.
3. Preserve the callback's animated tile ranges; don't reuse them for static tiles.
4. Copy all original door-table registrations for the new tileset pointer, and
   register any custom/recoloured door separately.
5. Add the new tileset name and animation folder to `project_tileset_copies.js`.
   Porymap's plugin does not discover copied names from the game callbacks.
   For edited/repacked donor tilesets, check the actual contents of every
   animation range. Use `animationStarts` to whitelist only animations still
   applicable, and restrict the C callback accordingly (Castula is fountain-only).
6. Reload Porymap's project/scripts and verify the animations on the map.

Porymap is configured to load this folder's `animation.js` in `porymap.user.cfg`.

Custom copies now use city names: Alasia, Inquill, Mintaka, Uuba, Acamar, Sansuna,
Wurren, WurrenStation, Tiaki, Castula and Liesma. The first nine replace the old
colour/donor names; see `dev_artifacts/tileset_city_names/README.md` for the mapping.
WurrenStation is the aligned test variant, separate from WurrenTown's Wurren set.
Historical experiment scripts/backups still use their original names; the active
animation registry and `verify.mjs` use the current city names.

If the editor still has the old script cached, restart Porymap. Alternatively,
use Options → Custom Scripts to replace the old shared script with this one;
don't enable both animation scripts simultaneously.

Checks: `dev_artifacts/tileset_animation_audit/verify.mjs` exercises the actual
editor data loader, and `verify_assets.py` audits runtime callbacks, frame copies,
animated tile slots and door registrations. Both are read-only.

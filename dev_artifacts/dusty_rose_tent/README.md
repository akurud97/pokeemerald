# Dusty rose / brown tent

Historical version: the live station is now charcoal/gold. See
`../charcoal_gold_station/README.md` for the current conversion and backup.
The placement grids below still apply.

The native building pixels use the unchanged **General primary palette 3**.
No primary or secondary palette files were modified. Transparency, tile flips,
bulbs, patterned roof, and doorway geometry are preserved; some dark neutral
shades are merged to fit the existing palette without introducing its greens.

## Where to look

- `castulatest`: existing Castula tent recoloured in place. CastulaCity's matching
  tent pieces also use the recoloured graphics; map placement is unchanged.
- `wurrentest`: now uses `gTileset_FallarborRoseTent`, a full copy of the already
  modified FallarborCedar tileset. Its foreground is shifted down exactly 8 pixels
  into the empty sixth row. The six explicitly approved unused smaller-tent
  slots `0x353–0x355` and `0x35B–0x35D` are reused in this copy only.
- WurrenTown still uses FallarborCedar: same new dusty-rose colours, original
  footprint. Its building/sign/map placement was deliberately not shifted.
- Liesma: new 6×6 building template in `0x352–0x375`. Existing city copies and
  `liesmatest` are unchanged; the latter still contains the pink/cream house.
  The new tent uses the city's shared primary plaza ground (`0x170`) underneath.

## Liesma placement (left to right, top to bottom)

```text
352 353 354 355 356 357
358 359 35A 35B 35C 35D
35E 35F 360 361 362 363
364 365 366 367 368 369
36A 36B 36C 36D 36E 36F
370 371 372 373 374 375
```

## Aligned Wurren placement

Use the new **FallarborRoseTent** tileset for this arrangement, not FallarborCedar.

```text
380 381 382 382 383 384
388 389 38A 38B 38C 390
391 392 393 394 398 399
39A 39B 39C 39C 3A0 3A1
3A2 3A3 3A4 3A4 353 354
355 355 35B 35B 35C 35D
```

## Animation / backups

These enlarged templates had no animated-door behaviour or door registration;
none was invented, and no warp destinations were added. Original door PNGs and
runtime animation code are unchanged. The new Fallarbor copy preserves the source
callback and all three existing door-table entries. Porymap registration is also
included. Castula's fountain-only restriction and Liesma's flag remain intact.

`before/` contains complete pre-edit tilesets, General, affected map/layout copies,
door images, runtime code, and registrations. `manifest.json` records allocated
graphics, edited metatile addresses, new templates, and expected registration
hashes. All new graphics occupy previously blank, unreferenced, non-animated slots.

Checks:

```sh
python3 dev_artifacts/dusty_rose_tent/convert.py verify
node dev_artifacts/tileset_animation_audit/verify.mjs
```

The conversion commands are deliberately non-idempotent: never rerun recolour or
align over an existing backup/output. Reload Porymap after saving any open edits
to pick up the new tileset and external graphics changes.

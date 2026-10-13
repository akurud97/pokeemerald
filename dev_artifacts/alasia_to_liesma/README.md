# Alasia 0x201 copied to Liesma

Alasia metatile `0x201` is now available in Liesma at `0x37A`.
It uses General primary palettes 2 (ground) and 5 (foreground), with no
palette changes. Four copied graphics occupy `0x31E–0x321`; the compiled
Liesma graphic count increased from 286 to 290.

Both layers, flips and attribute `0x1000` are preserved. The source and
destination renders match exactly, and all existing graphics and metatiles
are preserved. No maps were changed. Animation graphic slots were excluded
from allocation.

`before/` stores the working-tree versions before this import, including
existing user edits. Do not restore whole files over later changes.
`manifest.json`, `source.png` and `liesma.png` record the result. The guarded
one-shot `copy.py` reuses the earlier import workflow and must not be rerun.

Asset verification passed. ROM compilation was not run for this import.

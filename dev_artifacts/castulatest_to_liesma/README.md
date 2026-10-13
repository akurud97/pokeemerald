# Castulatest tiles copied to Liesma

Copied the three metatiles selected in the current 1×3 Castulatest layout:

| Castula | Liesma |
| --- | --- |
| 0x37E | 0x376 |
| 0x386 | 0x377 |
| 0x38E | 0x378 |

These use General primary palettes 0 and 2; no palette files were changed.
Both layers, tile flips and metatile attributes are preserved. Eight new
8×8 graphics occupy 0x316–0x31D, and Liesma's compiled tile count increased
from 278 to 286. Existing graphics were reused where identical.

The source and destination renders are pixel-identical. Existing metatiles,
graphics, maps and palette files are preserved, including the user's current
uncommitted edits. Metatile 0x200 remains the original blank slot. Flag and
door animation graphic slots were excluded from allocation.

`before/` contains the exact working-tree versions of the touched assets before
this import. Do not restore whole files over subsequent edits. `manifest.json`
records allocations, and `source.png` / `liesma.png` show the copied strip.
`copy.py` is a guarded one-shot import, not a command to rerun.

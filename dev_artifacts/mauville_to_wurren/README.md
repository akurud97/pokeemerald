# Mauville short grass imported to Wurren

| Mauville source | Wurren destination |
| --- | --- |
| `0x204` | `0x253` |
| `0x205` | `0x254` |

Wurren already has all 512 secondary metatile entries. The destination slots
were unused in every Wurren layout and border and duplicated `0x250` and
`0x252`, respectively. Those original entries remain available.

Copied graphics `0x24D` and `0x25D` occupy previously unreferenced Wurren
graphics slots `0x24B` and `0x24C`. Indexed pixels, both layers, flips and full
attributes are preserved. Both imports have attribute `0x0007`, selecting
`MB_SHORT_GRASS` and the existing animated `FLDEFF_SHORT_GRASS` movement
effect. Neither source references Mauville's animated flower graphics
(`0x260–0x29F`), so no tileset animation callback or frame copy is needed.

Both imports use General primary palette 2. Their used colours (indices
12–15) match the donor palette. All Wurren layouts use General; no palettes
or maps were changed.

Validation: source and destination renders match pixel for pixel; every
other metatile, attribute and indexed graphic is unchanged. PNG round-trip
checks passed. `comparison.png` shows Mauville above Wurren. ROM compilation
and in-game testing were not performed; WSL is unavailable in this session.

`before/` contains the Wurren assets before this import. `manifest.json`
records the mapping. `copy.py` is a guarded one-shot script and must not be
rerun after import.

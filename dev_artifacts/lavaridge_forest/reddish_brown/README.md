# Reddish-brown door trial

The active `acumartest` house keeps its forest-green roof and uses richer,
copper/mahogany browns for the door. Only palette 12 entries 14 and 15 changed:

- 14: 184 112 64 -> 192 104 80
- 15: 128 72 40 -> 144 72 48

The existing door animation automatically uses these same colours. No extra
palette slot, tile edits, animation PNG edits, map changes or behavior changes
are needed. Original General and Lavaridge assets remain untouched.

`palette_12_before.pal` preserves the previous forest-green/original-brown
combination. Restore it as the copy's `palettes/12.pal` to revert this trial.
`preview.png` is rendered from the saved indexed assets, not a game screenshot.
The ROM rebuild completed successfully. Validation confirmed that only the
two door shades changed and that the roof, facade and glass stay identical.

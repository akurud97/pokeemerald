# Dynamic connection objects

Adapted from tustin2121's Dynamic In-Connection Clones implementation:
https://github.com/tustin2121/pokeemerald/commit/ba40f2a6ce77b847ec542fde022ae665bf679f1b

The expansion base already supports FRLG clone templates, so this integration
uses that existing structure and OBJ_KIND_CLONE value. It automatically appends
nearby connected-map objects to the saved template array and includes that tail
in camera spawning. Sprite and light setup resolve the original template before
reading movement, species, or light parameters, because those fields share storage
with clone metadata.

No map edits or object-template/save-layout changes are required. Continue restores
current-map scripts and rebuilds the generated tail without resetting saved NPC
positions. Only cardinal connections are scanned; dive/emerge are excluded.
Existing clone targets are deduplicated, and generated clones do not recursively
clone other clones. Current-map templates take priority at the 64-template limit.
The engine's existing 16 simultaneously active object slots remain in effect.

Run the map audit and focused production-C checks from WSL:

```sh
python3 dev_artifacts/dynamic_clones/verify.py
```

The checks compile the actual loader functions extracted from the modified source
against a small host shim. They cover cardinal coordinate transforms, offsets,
sparse IDs, source-template resolution, duplicate exclusion, saved current-map
positions, capacity guards, dive connections, and maps without connections.
They do not replace an emulator check of walking across a connection and
saving/reloading near it.

## Verification

- Production C checks and map audit passed: the maximum is 43 templates after
  adding nearby connection objects; no audited map exceeds 64.
- Full ROM build passed using ARM GCC 14.2.1 in an isolated Linux copy, with the
  project's existing compiled scripts. The result is `pokeemerald.gba` in the
  project root (SHA-256
  `4c884ae105b8660c3bf36002c3ba9a568e34a13eb9f2025e263e2aaadfa2941c`).
- Linked memory: EWRAM 226760 bytes, IWRAM 28392 bytes, ROM 29015764 bytes.
- Route110's script-local challenge biker alias was renamed to
  `LOCALID_ROUTE110_CHALLENGE_BIKER` in both source and compiled scripts to avoid
  colliding with the compatibility macro. Its value remains 21.
- No emulator boundary/save-load check was performed.

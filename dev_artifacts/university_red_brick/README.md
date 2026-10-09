# Red-brick university implementation

This task applies the chosen red-brick/cream/navy university direction to the
three variants in `castulatest`, `evergrandetest`, and `evergrandetest2`.

The final installed pass restores the original detailed pixel art and applies a
purpose-built low-contrast cream/peach/navy palette. It keeps the ornament,
window shading, and brick layout while assigning the original light, middle,
and shadow indices to closer values, avoiding the harsh contrast of earlier
index-remapping passes.

It edits the original university graphics/metatiles in the existing Castula and
Ever Grande tilesets. Test maps use their original IDs, all earlier clone
allocations were reclaimed, and maps sharing those university pieces receive
the final appearance as intended.

Palette strategy:

- Castula palette 7 was freed by moving its only four unique graphics/five
  metatiles to the similar palette 8. Palette 7 now holds the university.
- Ever Grande palette 12 was blank/unreferenced and now holds the identical
  university palette.
- Broadly shared Castula palette 11 and Ever Grande palette 6 were restored to
  their original bytes, so unrelated users are not recoloured.
- One repeating upper-wing fill tile in each tileset swaps its two existing
  indices into the close cream pair. Its complete pixel pattern is preserved.

Safety:

- `before/` is the untouched pre-task state. Subsequent `before_*` folders
  preserve every installed iteration, including the simplified and preliminary
  palette passes.
- Final tilesheet dimensions and metatile/attribute counts match `before/`;
  no university clone space remains allocated.
- Target graphics do not overlap Castula's live fountain range `0x3C0–0x3C3`,
  Ever Grande's flower range `0x2E0–0x2FF`, or door-reserved `0x3F0+` space.

Commands, from the repository root:

```sh
/Users/andrewbecker/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3 dev_artifacts/university_red_brick/build.py audit
/Users/andrewbecker/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3 dev_artifacts/university_red_brick/build.py preview
/Users/andrewbecker/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3 dev_artifacts/university_red_brick/build.py apply
/Users/andrewbecker/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3 dev_artifacts/university_red_brick/build.py retune-low-key
/Users/andrewbecker/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3 dev_artifacts/university_red_brick/build.py simplify-in-place
/Users/andrewbecker/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3 dev_artifacts/university_red_brick/build.py final-palette-pass
/Users/andrewbecker/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3 dev_artifacts/university_red_brick/build.py isolate-final-palette
/Users/andrewbecker/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3 dev_artifacts/university_red_brick/build.py verify
```

The mutation modes are one-shot operations guarded by their respective backup
directories. They document provenance and must not be rerun on the installed
state.

Historical scripts using old donor/colour names are not involved and should
not be rerun for this task.

# Building/tileset work — continuation handoff

Updated October 8, 2026. This is the current-state handoff for the long building
recolouring chat, not a complete history of all pokeemerald development.

## Scope and user preferences

Workspace: `/Users/andrewbecker/pokeemerald`.

We are customising buildings and terrain for the user's region, usually first
making colour mockups, then implementing the chosen look on a small map in map
group `testingstage`. The user often subsequently applies the custom tileset to
the real city. Preserve original sprite geometry/pixels when implementing;
AI mockups are colour inspiration, not pixel-exact replacement assets.

Important working rules:

- Duplicate original tilesets before experimenting. Keep backups of changes.
- Prefer existing colours and a single palette when feasible. If more palette,
  graphics, or metatile space is needed, audit it and ask before overwriting
  occupied slots. A slot unused on one test map is not necessarily unused
  elsewhere: check every map/border using the tileset and animation ranges.
- Match static doors and their opening animations. Copy/recolour a custom door
  animation instead of damaging a shared original. Preserve window glass,
  handles, outlines, and moving-frame detail.
- Copy continuous animation assets AND game callback bindings AND Porymap
  registrations. Donor animations are valid only where their target slots still
  contain the intended animated graphics; repacked tilesets need a range audit.
- The repo has extensive unrelated user changes. Do not reset, clean, commit,
  or overwrite those. Restore individual relevant assets, not entire old shared
  registration files over later work.
- Use `apply_patch` for source/text edits. Indexed/binary game assets are edited
  through task scripts. For requested AI image mockups, use the imagegen skill.

There is no pending implementation request at this handoff. The last asset work
was the lighter Mintaka door followed by renaming our custom tilesets.

## Current names and looks

All live custom secondary folders are under `data/tilesets/secondary/`.
C/Porymap symbols are `gTileset_<Current name>`.

| Current name / folder | Previous custom name | Test map | Current look / notes |
| --- | --- | --- | --- |
| Alasia / `alasia` | PetalburgLavender | `alasiatest` | Lavender roof, warm coral door/window trim; cream-front lab variant, custom doors. |
| Inquill / `inquill` | MauvilleBrick | `inquilltest` | Lightened warm brick-red roof; original facade retained. |
| Mintaka / `mintaka` | SlateportCharcoal | `mintakatest` | Charcoal roof, white/cool facade, lighter grey-black door; one palette, slot 10. Original slot 6 restored. |
| Uuba / `uuba` | MossdeepOrange | `uubatest` | Orange roof, original facade; modified existing palette 9. |
| Acamar / `acamar` | LavaridgeForest | `acumartest` | Forest-green roof, reddish-brown door, palette 12; primary house duplicated into secondary. Test name really is `acumar`, city is Acamar. |
| Sansuna / `sansuna` | LavaridgeIvory | `sansunatest` | Ivory adobe-like building, teal door, palette 12; independent Sootopolis-derived door animation. |
| Wurren / `wurren` | FallarborCedar | See below | Rustic cedar/brown house, brown door, orange window awning, yellow knob; grey chimney variant; sun-dried-straw ground and blended edges/patch. Also charcoal/gold station. |
| WurrenStation / `wurren_station` | FallarborRoseTent | `wurrentest` | Separate Wurren copy with the station shifted down 8 pixels to align with Castula; now charcoal/gold, despite historical RoseTent name. |
| Tiaki / `tiaki` | DewfordTeal | `tiakitest` | Teal roof, neutral facade, wooden support beams/door; flag animation retained. |
| Castula / `castula` | Already city-named | `castulatest` | Existing city tiles plus charcoal/gold station. Continuous secondary animation is fountain-only. |
| Liesma / `liesma` | Already city-named | `liesmatest` | Consolidated city set; pink-roof/cream double-tier house, wooden door; charcoal/gold station also available. |

The first nine were renamed in the latest work. All palette, PNG, metatile,
attribute, and animation files remained byte-for-byte identical during renaming.
Updated C symbols, include declarations, layouts, door-table references, custom
door identifiers, two custom metatile-label namespaces, and Porymap registry.
Original game tilesets were not renamed or modified by that operation.

Current dependent layouts:

- Alasia: Alasiaville, HyadesRoute1, alasiatest.
- Inquill: InquillTown, inquilltest.
- Mintaka: MintakaCity, mintakatest.
- Uuba: UubaCity, HyadesRoute5, uubatest.
- Acamar: AcamarJunction, acumartest.
- Sansuna: SansunaCity, sansunatest.
- Wurren: WurrenTown, HyadesRoute11, HyadesRoute12, CraterCanyon.
- WurrenStation: wurrentest only. It is intentionally NOT the WurrenTown set.
- Tiaki: TiakiTown, HyadesRoute13, tiakitest.
- Castula: CastulaCity, HyadesRoute8, castulatest.
- Liesma: LiesmaCityNorth2, LiesmaCitySouth2, liesmatest.

Door PNG filenames retain historical donor names deliberately. Examples:
`graphics/door_anims/slateport_charcoal_one_palette.png`, `dewford_teal.png`,
`lavaridge_forest.png`, `lavaridge_ivory_sootopolis.png`, `liesma_wooden.png`.
The active C pointers use the new tileset names.

## Latest Mintaka door

The first black door was too dark for the user. Current version uses existing
palette 10 index 15 `(56,64,80)` for main fill and index 6 `(96,104,120)` for
frame/highlights. Original brown index 13 becomes 6, original 14 becomes 15,
ONLY at the original brown pixels. Other dark details, glass and knob remain.
All three opening frames match. No palette values or additional slots changed.

Static door metatiles: upper `0x2D4`, lower `0x2DC`. Custom animation file:
`graphics/door_anims/slateport_charcoal_one_palette.png` (16x96 indexed).
MintakaCity's matching doors share these updated graphics.

`dev_artifacts/mintaka_grey_black_door/before/` preserves the too-dark black;
`dev_artifacts/mintaka_black_door/before/` preserves the earlier brown version.

## Train station — current charcoal/gold version

The enlarged Battle Tent building is being repurposed as a train station.
User tried dusty rose, then blue, then chose charcoal/gold: standout but subdued.
Current station art exists in Castula, Wurren, WurrenStation and Liesma.

- All station foreground uses existing **General primary palette 5**, unchanged.
- Charcoal roof, cool silver-grey body, white bulbs; selective gold entrance
  lintel/window bands/narrow jambs. Native recolour retains original pixel shapes.
- 23 graphics tiles were already cloned per variant; the latest pass added three
  blank/unreferenced graphics slots per variant for selective gold details.
- No new palette slots or metatiles in the latest colour pass. Liesma's compiled
  graphics count is now **278**, not the older README's initial 252.
- Castula test is 6x6. Wurren's original station was 8px higher; user approved
  reusing unused small-tent metatiles `0x353–0x355` and `0x35B–0x35D` in the
  separate WurrenStation copy to make a 6x6 aligned test.
- WurrenTown keeps its original station footprint and original Wurren selection;
  it has matching colours but is not switched to the aligned test variant.
- Liesma station occupies `0x352–0x375` (36 row-major metatiles, 6x6). It has not
  been placed over city buildings. `liesmatest` still previews the pink house.
- These enlarged station doors have no animated-door registrations/behaviours
  or test warps. Do not attach the unrelated narrow original tent door animation
  to the wide entrance. No destinations were invented.

See `dev_artifacts/charcoal_gold_station/` for current native previews and
backups of the blue stage; earlier blue/rose backups are also retained.

## Liesma consolidation

Original LiesmaCityNorth/South used BattleFrontierOutsideEast/West. We packed
only referenced metatiles/graphics/palettes, borders, and required animations
into new secondary `Liesma`, adding the Lilycove-derived 6x5 double-tier house.

User explicitly chose **separate copies, existing world connections untouched**:

- `LiesmaCityNorth2` (65x40) and `LiesmaCitySouth2` (67x48), appended to testingstage
  without shifting existing map IDs. Their mutual connection targets each other.
- Original city maps remain unchanged. Surrounding routes still connect to the
  originals; new copies retain outgoing links to those original routes.
- Original collisions/elevation/events and appearance were preserved by remapping.
- Pink/cream house occupies `0x33D–0x351`; roof palette 7, facade 8, wooden door
  primary 5. Own `liesma_wooden.png`, palette array `{7,7,8,8,5,5,5,5}`.
- After station additions, metatiles above `0x375` are still available according
  to the last allocation. Palettes 6 and 11 were free in the original pack
  (11 only blank references), and subsequent station uses primary 5. Re-audit
  current files before allocating, since the user may have edited them.
- Flag graphics `0x2DA–0x2DF` (global tile IDs) are reserved for animation.
  Dedicated Liesma C callback uses copied frames at original eight-tick timing.
- Original-city/source snapshots and old-to-new ID map are in
  `dev_artifacts/liesma/before/` and `manifest.json`.

## Wurren house/terrain details

Rustic house palette 7 retained orange awning and yellow knob in the refined
native version. Chimney was tried in copper then changed to grey using existing
primary palette 3 via cloned graphics, not another custom palette.

Sun-dried-straw ground uses palette 8. Ground metatile `0x218` and matching
references were updated. User's edge IDs `0x363,0x364,0x365,0x373,0x375` were
**raw graphics tile IDs, not metatiles**; their foreground tiles were cloned and
recoloured, preserving transparency/flips. Ground patch metatile `0x229` had
foreground graphics `0x24B,0x24C,0x25B,0x25C`, also cloned to blend with straw.
Related task records/backups live in `dev_artifacts/fallarbor_cedar/`.

## University red-brick variants

The final low-contrast cream/peach/soft-brick/navy university scheme is installed
in `castulatest`, `evergrandetest`, and `evergrandetest2`. The user clarified
that test maps only present the buildings and that future building edits may
overwrite existing assets. Prefer in-place edits over clones unless a later
request explicitly requires isolation.

- The final pass overwrites the original university graphics/metatiles in the
  existing Castula and Ever Grande tilesets; no new tileset was created.
- Earlier clone allocations (`0x3A8–0x3C6` Castula metatiles; `0x360–0x390`
  Ever Grande metatiles and `0x3B0–0x3DB` graphics) were fully reclaimed. Test
  maps again use their original metatile IDs, and final sheet/metatile counts
  match the pre-task snapshots.
- Shared map users now receive the final university appearance. This includes
  the relevant original IDs in CastulaCity, FortreeCity, RustboroPark, and
  CastulaPark; this is intentional under the clarified instruction.
- The original detailed artwork is restored: no ornament, window shading, or
  brick pixels were deleted. The original light/mid/shadow roles now use close
  warm values, which reduces contrast without flattening the design. Only the
  repeating upper-wing fill swaps its two existing indices into the cream ramp.
- The final colours are isolated to Castula palette 7 and Ever Grande palette
  12. To free Castula 7, its only four unique graphics/five metatiles were moved
  to the similar palette 8. Shared Castula 11 and Ever Grande 6 are restored to
  their original bytes, avoiding unrelated recolours.
- Target graphics avoid Castula fountain `0x3C0–0x3C3`, Ever Grande flowers
  `0x2E0–0x2FF`, and door-reserved `0x3F0+` graphics.
- Backups: `before/` is pre-task; the successive `before_low_key/`,
  `before_simplified_in_place/`, `before_final_palette_pass/`, and
  `before_isolated_palette/` folders preserve every installed iteration.

Task-specific audit/apply/verify tooling, exact allocation manifest, reference
images, native previews, and full before snapshots are in
`dev_artifacts/university_red_brick/`. The animation audit passes. Both edited
tilesheets and the Ever Grande palette convert successfully with `gbagfx`.
The full `make -j4` attempt on October 8, 2026 was blocked only because this
shell lacks the `arm-none-eabi-*` compiler toolchain; no emulator playtest was
performed.

## Inquill coral-and-stone house

The 5x4 house shown in `inquilltest` now uses the requested coral upper siding,
dark coral/charcoal middle panels, blue-grey stone base, gold columns, and coral
door. The user explicitly authorized direct edits to existing tilesets and said
insurance copies are no longer needed at this stage.

- No new tileset, metatile, graphic slot, or palette was created; no backup was
  made for this pass.
- Twenty-three original house graphics were re-indexed without changing pixel
  shapes. All palette-7 references to them were switched to existing palette 12,
  covering 42 house-piece metatiles so alternate pieces stay consistent.
- Existing palette 12 was unchanged. Other palette-7 graphics/metatiles were
  untouched.
- Edited graphics avoid Inquill/Mauville flower animation `0x260–0x29F`.
- `dev_artifacts/inquill_house/` contains the installed native preview, an ID
  manifest, and implementation notes (but deliberately no backup payload).
- `gbagfx` conversion and the project animation audit pass; no emulator playtest
  was performed.

## Scheder indigo-and-sandstone temple

The temple shown in `schedartest` now uses the new `gTileset_Scheder`, cloned
from Lilycove at the user's request. Only `schedartest` was switched; the
original Lilycove tileset and its existing map users remain untouched.

- The selected look is the balanced-round “softened indigo/sandstone” mockup:
  slate-indigo patterned roofs, ivory/sandstone walls, restrained cedar trim,
  blue-grey foundation, and neutral stairs.
- Thirty-three existing graphics were re-indexed and 208 palette-8 references
  to those graphics were moved to the clone's custom palette 10. Pixel shapes,
  metatile IDs, collision/behavior attributes, and map block data were preserved.
- No new graphic or metatile slots were consumed. Scheder remains a full
  512-metatile/512-attribute clone with the original 128x360 sheet dimensions.
- Scheder reuses Lilycove's callback; it has no live continuous secondary
  animation, so no project Porymap animation registration was added. All four
  Lilycove door registrations were duplicated for the Scheder pointer.
- Native previews, affected IDs, hashes, and the read-only layer audit helper
  are in `dev_artifacts/scheder_temple/`.
- `gbagfx` conversion, layout JSON parsing, the project animation audit, and a
  full ROM build all pass. In Codex shells where `DEVKITARM` is not inherited,
  build with `make DEVKITARM=/opt/devkitpro/devkitARM -j4`. No emulator
  playtest was performed.

## Critical animation fix — do not undo

Castula's imported building graphics occupy global `0x280–0x29F`, which were
Rustboro windy-water animation slots. Blindly inheriting Rustboro animations
caused water to appear over buildings in both editor/runtime.

We removed **only Castula's windy-water animation** from C bindings/callback and
its Porymap registration. Castula must remain **fountain-only**, global
`0x3C0–0x3C3`, two frames/eight-tick interval; fountain metatiles `0x339/0x341`.
Original Rustboro, General water, and all other sets are unchanged. Old unused
water PNGs remain on disk. Backup: `dev_artifacts/castula_animation_fix/before/`.

Project-local Porymap plugin:

- `porymap.user.cfg` loads
  `/Users/andrewbecker/pokeemerald/porymap_scripts/tileset_animation/animation.js`.
- Shared `/Users/andrewbecker/Porymap-Animation` is untouched.
- `project_tileset_copies.js` registers current city-named copies, including
  Tiaki flag, Inquill flowers, Mintaka balloons, Acamar/Sansuna steam/lava,
  Castula fountain-only, Liesma flag. Alasia/Uuba/Wurren variants have no
  continuous secondary animation to add; door animations are separate.
- Tiaki flag metatiles `0x349–0x34A` target global tiles `0x2AA–0x2AF`.
  Four original flag frames were copied unchanged; editor registration repaired.
- Full rules: `porymap_scripts/tileset_animation/PROJECT_NOTES.md`.

Reopen/reload Porymap after renamed sets or animation registry edits. Do not
enable shared and project-local plugins simultaneously or save stale selections.

## Backups, scripts, verification, and caveats

`dev_artifacts/` began October 5 with the lavender/coral test. Per-task folders
contain notes, indexed renders, before snapshots, scripts, manifests and build
logs. They are development records, not game runtime inputs. Other older repo
notes exist (e.g. `docs/music_imports.md`); no complete all-project diary exists.

**Historical task READMEs/converters deliberately retain old donor names.**
Do not rerun them blindly after renaming; adapt their paths/expectations first.
Many snapshot-based verifiers correctly fail once later intentional edits have
changed their baseline. One-shot prepare/conversion modes are not restore tools.
The Liesma README's initial free-space figures also predate station additions.

Newest rename mapping/backups:
`dev_artifacts/tileset_city_names/README.md`, `manifest.json`, `before/`.
At completion, native asset/hash checks, editor-animation loader checks and
`make -j4` all passed. No emulator visual/playtest was performed by the agent.

Useful current checks (read-only except ordinary build outputs):

```sh
# Run from /Users/andrewbecker/pokeemerald.
/Users/andrewbecker/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/bin/python3 dev_artifacts/tileset_city_names/rename.py verify
/Users/andrewbecker/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/bin/node dev_artifacts/tileset_animation_audit/verify.mjs
make -j4
```

The rename verifier checks its completion baseline; future intentional/user
edits may require reviewing differences, not restoring them to make it pass.
Last successful build log: `dev_artifacts/tileset_city_names/build.log`.
Pre-existing build warnings were not part of this task.

For native rendering, helpers in `dev_artifacts/liesma/build.py` include `words`,
`save_words`, `palette`, `tile`, `render`. Render uses General plus secondary;
does not simulate continuous animation VRAM. PNGs are indexed, hardware indices
modulo 16; preserve index-0 transparency. Metatile IDs are mapword low 10 bits;
preserve upper collision/elevation bits. Tile references include flips and
palette bits. Typical primary/secondary graphics split is 512+512; normal door
VRAM reserves global `0x3F8–0x3FF` (wide size-2 doors can reserve `0x3F0–0x3FF`).
Do not assume blank graphics or unused metatile capacity is safe without auditing.

New chat should read this handoff, animation PROJECT_NOTES, and the relevant
task's README/script, then inspect current assets before implementing the next
request. No Git commit was made as part of these tasks.

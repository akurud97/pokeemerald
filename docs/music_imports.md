# Music import notes

Before registering a newly imported MIDI, run:

```sh
python3 tools/sanitize_music_midi.py --write sound/songs/midi/mus_name.mid
```

This is especially important for MIDI files converted from Nintendo DS
sequences. Those files can contain controller 33 or 39 events for fine
modulation or volume. `mid2agb` interprets both controller numbers as M4A
`PRIO` commands. High generated priorities can occupy all five DirectSound
channels and make Pokémon cries or sound effects play inconsistently.

After building, a quick verification is:

```sh
rg "PRIO" sound/songs/midi/mus_name.s
```

Normally an imported background track should not generate any track-level
`PRIO` commands. If priorities are intentionally required, keep them below
`CRY_PRIORITY_NORMAL` (currently 10 in `include/constants/sound.h`).

`tools/stage_selected_donor_music.py` runs the sanitizer automatically for its
staged imports. Other manual and PoryDAW imports still need the command above.

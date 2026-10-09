# Mintaka grey-black door — current version

The main door fill is lifted from palette 10's index 8 (40,48,64) to its existing
index 15 (56,64,80); the frame/highlights use index 6 (96,104,120), instead of
index 7 (72,80,96). Only pixels which originally used the brown door shades are
changed. This keeps the original dark detailing, blue window and bright knob.
All three animation frames receive the same change.

No new colours or palette/tile/metatile slots. Roof, facade, maps, behaviours,
collision and animation registrations are untouched. MintakaCity's matching
house doors share the same updated graphics.

`before/` preserves the darker black version. The earlier brown version remains
in `../mintaka_black_door/before/`. Native previews: `preview.png`, `door_frames.png`.

```sh
python3 dev_artifacts/mintaka_grey_black_door/convert.py verify
```

Do not rerun conversion over an existing backup.

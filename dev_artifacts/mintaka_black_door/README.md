# Mintaka charcoal door

Historical darker version: see `../mintaka_grey_black_door/README.md` for the
current lighter grey-black door. Both backups remain available.

Mintakatest uses SlateportCharcoal. Its door's two brown indices are remapped to
the existing roof shades in palette 10: index 13 → 7 (72,80,96), index 14 → 8
(40,48,64). The six unique closed-door tiles and all three opening/closing frames
in `graphics/door_anims/slateport_charcoal_one_palette.png` use the same remap.
The blue window, bright knob, pixel geometry, roof and white facade are untouched.

No palette, graphic or metatile slots are added. MintakaCity uses these same
house pieces, so its matching doors also become charcoal. Neither map is edited.
Original Slateport assets and other door animations are untouched.

`before/` backs up the full modified tileset, General, the custom door PNG,
Mintakatest/MintakaCity maps and layouts, and relevant registrations/runtime code.
`preview.png` and `door_frames.png` are native indexed-graphics renders.

```sh
python3 dev_artifacts/mintaka_black_door/convert.py verify
```

Do not rerun conversion over an existing backup.

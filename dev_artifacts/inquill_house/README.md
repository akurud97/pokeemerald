# Inquill coral-and-stone house

The house displayed by `inquilltest` was edited directly in the existing
Inquill tileset, per the user's instruction. No new tileset, metatiles, graphics
slots, palettes, or insurance backup were created.

Implementation:

- 23 existing house graphics were re-indexed without changing their pixel
  shapes.
- Every palette-7 reference to those graphics was switched to Inquill palette
  12, covering 42 existing house-piece metatiles. This keeps alternate pieces
  consistent, not only the 14 metatiles visible in `inquilltest`.
- The upper band uses a restrained coral ramp; the tall middle panels use dark
  coral with charcoal/navy beams; the lower wall uses darker blue-grey stone;
  existing gold columns and the coral door remain intact.
- Palette 12 itself was already present and was not modified.
- Mauville/Inquill flower animation graphics `0x260–0x29F` are disjoint from
  the edited graphics and remain unchanged.

`preview.png` is a native tileset render of the installed test map.
`manifest.json` records the edited graphic/metatile IDs and contains no backup
payload.

Verification completed: graphics and palette convert with `gbagfx`, tileset
capacity remains 510 metatiles and a 128x256 sheet, and the project animation
audit passes.

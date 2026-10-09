"""One-off layer audit for the schedartest temple.

This reports the visible Lilycove graphic/index pairs in named screen regions.
It does not edit project assets.
"""
from collections import Counter
import json
from pathlib import Path
import struct

from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
layout = next(
    item for item in json.loads((ROOT / "data/layouts/layouts.json").read_text())["layouts"]
    if item["name"] == "schedartest_Layout"
)


def words(path: Path):
    data = path.read_bytes()
    return struct.unpack("<" + "H" * (len(data) // 2), data)


blocks = words(ROOT / layout["blockdata_filepath"])
primary_metatiles = words(ROOT / "data/tilesets/primary/general/metatiles.bin")
secondary_metatiles = words(ROOT / "data/tilesets/secondary/lilycove/metatiles.bin")
primary_sheet = Image.open(ROOT / "data/tilesets/primary/general/tiles.png")
secondary_sheet = Image.open(ROOT / "data/tilesets/secondary/lilycove/tiles.png")
visible = [[None] * (layout["width"] * 16) for _ in range(layout["height"] * 16)]

for position, block in enumerate(blocks):
    metatile = block & 0x3FF
    if metatile < 0x200:
        entries = primary_metatiles[metatile * 8:metatile * 8 + 8]
    else:
        offset = (metatile - 0x200) * 8
        entries = secondary_metatiles[offset:offset + 8]
    for entry_offset, entry in enumerate(entries):
        graphic = entry & 0x3FF
        sheet = primary_sheet if graphic < 0x200 else secondary_sheet
        local = graphic if graphic < 0x200 else graphic - 0x200
        columns = sheet.width // 8
        tile = sheet.crop((
            local % columns * 8,
            local // columns * 8,
            (local % columns + 1) * 8,
            (local // columns + 1) * 8,
        ))
        if entry & 0x400:
            tile = tile.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
        if entry & 0x800:
            tile = tile.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
        x_base = position % layout["width"] * 16 + entry_offset % 2 * 8
        y_base = position // layout["width"] * 16 + (entry_offset % 4) // 2 * 8
        for y in range(8):
            for x in range(8):
                index = tile.getpixel((x, y)) % 16
                if index:
                    visible[y_base + y][x_base + x] = (graphic, index, entry >> 12)


regions = {
    "top_roof_field": (40, 16, 120, 48),
    "side_roofs": (0, 40, 160, 72),
    "upper_facade": (40, 48, 120, 72),
    "middle_band": (0, 72, 160, 88),
    "centre_vent": (56, 72, 104, 88),
    "lower_facade": (0, 88, 160, 104),
    "foundation": (0, 104, 160, 112),
    "entry_floor": (56, 88, 104, 120),
    "stairs": (56, 112, 104, 144),
}

for name, (left, top, right, bottom) in regions.items():
    pairs = Counter(
        visible[y][x]
        for y in range(top, bottom)
        for x in range(left, right)
        if visible[y][x] is not None and visible[y][x][2] == 8
    )
    graphics = Counter()
    indices = Counter()
    for (graphic, index, _palette), count in pairs.items():
        graphics[graphic] += count
        indices[index] += count
    print(name)
    print("  graphics:", " ".join(f"{graphic:03X}:{count}" for graphic, count in graphics.most_common()))
    print("  indices:", " ".join(f"{index:X}:{count}" for index, count in indices.most_common()))

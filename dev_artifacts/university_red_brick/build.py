"""Install the red-brick university variants into existing tilesets only.

Modes:
  audit    Read-only allocation/usage report.
  preview  Render the proposed test maps without changing game assets.
  apply    Back up current assets, then install the clones and render previews.
  verify   Verify the installed assets against the apply manifest.

Historical note: this script is tied to the current city-named Castula and
EverGrande tilesets. Do not repoint it at older donor-named copies.
"""
from __future__ import annotations

from collections import Counter, defaultdict
from hashlib import sha256
import json
from pathlib import Path
import shutil
import struct
import sys

from PIL import Image


ROOT = Path(__file__).resolve().parents[2]
REPORT = Path(__file__).resolve().parent
BACKUP = REPORT / "before"
LOW_KEY_BACKUP = REPORT / "before_low_key"
SIMPLIFIED_BACKUP = REPORT / "before_simplified_in_place"
FINAL_PALETTE_BACKUP = REPORT / "before_final_palette_pass"
ISOLATED_PALETTE_BACKUP = REPORT / "before_isolated_palette"
PREVIEW = REPORT / "preview"
MANIFEST = REPORT / "manifest.json"
PRIMARY = ROOT / "data/tilesets/primary/general"

CONFIG = {
    "castula": {
        "tileset": "gTileset_Castula",
        "folder": ROOT / "data/tilesets/secondary/castula",
        "maps": ["castulatest"],
        "source_palette": 11,
    },
    "ever_grande": {
        "tileset": "gTileset_EverGrande",
        "folder": ROOT / "data/tilesets/secondary/ever_grande",
        "maps": ["evergrandetest", "evergrandetest2"],
        "source_palette": 6,
    },
}

GAME_FILES = [
    "data/tilesets/secondary/castula/tiles.png",
    "data/tilesets/secondary/castula/metatiles.bin",
    "data/tilesets/secondary/castula/metatile_attributes.bin",
    "data/tilesets/secondary/castula/palettes/07.pal",
    "data/tilesets/secondary/castula/palettes/11.pal",
    "data/tilesets/secondary/ever_grande/tiles.png",
    "data/tilesets/secondary/ever_grande/metatiles.bin",
    "data/tilesets/secondary/ever_grande/metatile_attributes.bin",
    "data/tilesets/secondary/ever_grande/palettes/06.pal",
    "data/tilesets/secondary/ever_grande/palettes/12.pal",
    "data/layouts/castulatest/map.bin",
    "data/layouts/evergrandetest/map.bin",
    "data/layouts/evergrandetest2/map.bin",
]

REFERENCE_FILES = {
    "chosen_colour_mockup.png": Path("/var/folders/_f/r_hscyld5q1g5dfdvvs9d4_h0000gn/T/codex-clipboard-32c6a736-751b-4d6c-a4cf-39d637df8aaf.png"),
    "castulatest_original.png": Path("/var/folders/_f/r_hscyld5q1g5dfdvvs9d4_h0000gn/T/codex-clipboard-2885d019-6b64-4f4d-a698-f77ce98365d4.png"),
    "evergrandetest_original.png": Path("/var/folders/_f/r_hscyld5q1g5dfdvvs9d4_h0000gn/T/codex-clipboard-1ddc3239-0c70-4094-a95d-375365bee2ec.png"),
    "evergrandetest2_original.png": Path("/var/folders/_f/r_hscyld5q1g5dfdvvs9d4_h0000gn/T/codex-clipboard-0ad26150-f98d-4f21-b58f-ab830df4699c.png"),
    "chosen_low_key_mockup.png": Path("/var/folders/_f/r_hscyld5q1g5dfdvvs9d4_h0000gn/T/codex-clipboard-19b52eab-31c9-499d-b0ac-bf4065d7066f.png"),
}

# Both source palettes have the same index semantics. Castula palette 12 is
# already live and supplies the shared target colours, so only pixels in cloned
# graphics are re-indexed; Castula's existing palette and users remain intact.
INDEX_MAP = {
    0: 0,   # transparent
    1: 7,   # white highlight -> cool ivory
    2: 3,   # light facade -> sandstone
    3: 5,   # middle facade -> warm brick
    4: 8,   # facade shadow -> terracotta
    5: 7,   # trim highlight -> cool ivory
    6: 9,   # trim middle -> slate blue
    7: 14,  # trim shadow -> navy
    8: 13,  # deepest outline -> near-black maroon
    9: 1,   # glass highlight
    10: 2,  # glass middle
    11: 7,  # pale stone highlight
    12: 7,  # lower-facade highlight -> cool ivory
    13: 3,  # lower-facade body -> quiet sandstone/peach
    14: 5,  # lower-facade shadow -> warm brick
    15: 0,
}

# Final palette-only direction. Entries retain the source university palette's
# original light/mid/shadow roles, with two close warm ramps and the original
# restrained blue/navy structure.
FINAL_UNIVERSITY_PALETTE = [
    (115, 197, 164),
    (255, 250, 238),
    (251, 210, 180),
    (240, 184, 151),
    (216, 151, 118),
    (139, 148, 164),
    (98, 115, 148),
    (65, 74, 106),
    (41, 49, 90),
    (213, 222, 238),
    (139, 180, 213),
    (255, 242, 211),
    (247, 222, 181),
    (238, 190, 158),
    (216, 151, 118),
    (115, 197, 164),
]

CASTULA_RESERVED_GRAPHICS = (
    set(range(0x280, 0x2A0))  # historical windy-water VRAM range; static now
    | set(range(0x3C0, 0x3C4))  # live fountain animation
    | set(range(0x3F0, 0x400))  # wide/normal door VRAM reservation
)


def words(path: Path) -> list[int]:
    data = path.read_bytes()
    return list(struct.unpack("<" + "H" * (len(data) // 2), data))


def save_words(path: Path, data: list[int]) -> None:
    path.write_bytes(struct.pack("<" + "H" * len(data), *data))


def palette(path: Path) -> list[tuple[int, int, int]]:
    rows = path.read_text().replace("\r", "").splitlines()[3:19]
    assert len(rows) == 16, path
    return [tuple(map(int, row.split())) for row in rows]


def palette_text(colors: list[tuple[int, int, int]]) -> str:
    assert len(colors) == 16
    return "JASC-PAL\n0100\n16\n" + "\n".join(
        " ".join(map(str, color)) for color in colors
    ) + "\n"


def digest(path: Path) -> str:
    return sha256(path.read_bytes()).hexdigest()


def tile(sheet: Image.Image, global_id: int) -> Image.Image:
    local_id = global_id - 0x200
    assert local_id >= 0
    cols = sheet.width // 8
    x = local_id % cols * 8
    y = local_id // cols * 8
    assert y + 8 <= sheet.height, (hex(global_id), sheet.size)
    out = sheet.crop((x, y, x + 8, y + 8))
    out.putdata([v % 16 for v in out.getdata()])
    return out


def paste_tile(sheet: Image.Image, global_id: int, value: Image.Image) -> None:
    local_id = global_id - 0x200
    cols = sheet.width // 8
    sheet.paste(value, (local_id % cols * 8, local_id // cols * 8))


def blank_graphics(sheet: Image.Image, metatiles: list[int]) -> list[int]:
    referenced = {entry & 0x3FF for entry in metatiles}
    count = sheet.width // 8 * (sheet.height // 8)
    result = []
    for local_id in range(count):
        global_id = 0x200 + local_id
        if global_id in referenced:
            continue
        if set(tile(sheet, global_id).getdata()) == {0}:
            result.append(global_id)
    return result


def layouts() -> list[dict]:
    return json.loads((ROOT / "data/layouts/layouts.json").read_text())["layouts"]


def layout_for(map_name: str) -> dict:
    path = f"data/layouts/{map_name}/map.bin"
    return next(item for item in layouts() if item["blockdata_filepath"] == path)


def target_metatiles(cfg: dict, metatiles: list[int]) -> list[int]:
    ids = set()
    for name in cfg["maps"]:
        ids.update(value & 0x3FF for value in words(ROOT / f"data/layouts/{name}/map.bin"))
    return sorted(
        mid for mid in ids
        if mid >= 0x200
        and any((entry >> 12) == cfg["source_palette"]
                for entry in metatiles[(mid - 0x200) * 8:(mid - 0x200) * 8 + 8])
    )


def target_graphics(cfg: dict, metatiles: list[int], mids: list[int]) -> list[int]:
    result = set()
    for mid in mids:
        for entry in metatiles[(mid - 0x200) * 8:(mid - 0x200) * 8 + 8]:
            if (entry >> 12) == cfg["source_palette"]:
                result.add(entry & 0x3FF)
    return sorted(result)


def allocate(folder_name: str, cfg: dict, sheet: Image.Image,
             metatiles: list[int]) -> dict:
    mids = target_metatiles(cfg, metatiles)
    graphics = target_graphics(cfg, metatiles, mids)
    next_mid = 0x200 + len(metatiles) // 8
    assert next_mid + len(mids) <= 0x400
    mid_map = dict(zip(mids, range(next_mid, next_mid + len(mids))))

    if folder_name == "castula":
        candidates = [value for value in blank_graphics(sheet, metatiles)
                      if value not in CASTULA_RESERVED_GRAPHICS and value < 0x3F0]
        assert len(candidates) >= len(graphics)
        destinations = candidates[:len(graphics)]
    else:
        start = 0x200 + sheet.width // 8 * (sheet.height // 8)
        assert start == 0x3B0, hex(start)
        destinations = list(range(start, start + len(graphics)))
        assert destinations[-1] < 0x3F0
    graphic_map = dict(zip(graphics, destinations))
    return {
        "source_metatiles": mids,
        "source_graphics": graphics,
        "metatile_map": mid_map,
        "graphic_map": graphic_map,
    }


def proposed() -> dict:
    result = {}
    target_palette = (CONFIG["castula"]["folder"] / "palettes/12.pal").read_bytes()
    for folder_name, cfg in CONFIG.items():
        folder = cfg["folder"]
        source_sheet = Image.open(folder / "tiles.png")
        metatiles = words(folder / "metatiles.bin")
        attrs = words(folder / "metatile_attributes.bin")
        assert len(metatiles) % 8 == 0
        assert len(attrs) == len(metatiles) // 8
        allocation = allocate(folder_name, cfg, source_sheet, metatiles)

        highest = max(allocation["graphic_map"].values())
        rows = (highest - 0x200 + 16) // 16
        if rows * 8 > source_sheet.height:
            sheet = Image.new("P", (source_sheet.width, rows * 8), 0)
            sheet.putpalette(source_sheet.getpalette())
            sheet.paste(source_sheet, (0, 0))
        else:
            sheet = source_sheet.copy()

        for source, destination in allocation["graphic_map"].items():
            original = tile(source_sheet, source)
            recoloured = original.copy()
            recoloured.putdata([INDEX_MAP[value % 16] for value in original.getdata()])
            paste_tile(sheet, destination, recoloured)

        new_metatiles = list(metatiles)
        new_attrs = list(attrs)
        for source in allocation["source_metatiles"]:
            new_entries = []
            entries = metatiles[(source - 0x200) * 8:(source - 0x200) * 8 + 8]
            for entry in entries:
                if (entry >> 12) == cfg["source_palette"]:
                    old_graphic = entry & 0x3FF
                    assert old_graphic in allocation["graphic_map"]
                    entry = ((entry & 0x0C00)
                             | allocation["graphic_map"][old_graphic]
                             | (12 << 12))
                new_entries.append(entry)
            new_metatiles.extend(new_entries)
            new_attrs.append(attrs[source - 0x200])

        maps = {}
        for name in cfg["maps"]:
            current = words(ROOT / f"data/layouts/{name}/map.bin")
            changed = []
            for value in current:
                mid = value & 0x3FF
                changed.append((value & ~0x3FF) | allocation["metatile_map"].get(mid, mid))
            maps[name] = changed

        result[folder_name] = {
            "allocation": allocation,
            "sheet": sheet,
            "metatiles": new_metatiles,
            "attrs": new_attrs,
            "maps": maps,
            "palette12": target_palette,
        }
    return result


def render(folder: Path, blocks: list[int], width: int, sheet: Image.Image,
           metatiles: list[int], target_palette12: bytes) -> Image.Image:
    primary_sheet = Image.open(PRIMARY / "tiles.png")
    primary_metatiles = words(PRIMARY / "metatiles.bin")
    secondary_palettes = {i: palette(folder / f"palettes/{i:02}.pal") for i in range(6, 13)}
    rows = target_palette12.decode().replace("\r", "").splitlines()[3:19]
    secondary_palettes[12] = [tuple(map(int, row.split())) for row in rows]
    palettes = {
        **{i: palette(PRIMARY / f"palettes/{i:02}.pal") for i in range(6)},
        **secondary_palettes,
    }
    height = len(blocks) // width
    output = Image.new("RGB", (width * 16, height * 16))
    for pos, block in enumerate(blocks):
        mid = block & 0x3FF
        if mid < 0x200:
            entries = primary_metatiles[mid * 8:mid * 8 + 8]
        else:
            entries = metatiles[(mid - 0x200) * 8:(mid - 0x200) * 8 + 8]
        for offset, entry in enumerate(entries):
            tid = entry & 0x3FF
            if tid < 0x200:
                cols = primary_sheet.width // 8
                graphic = primary_sheet.crop(((tid % cols) * 8, (tid // cols) * 8,
                                              (tid % cols + 1) * 8, (tid // cols + 1) * 8))
            else:
                graphic = tile(sheet, tid)
            graphic.putdata([value % 16 for value in graphic.getdata()])
            if entry & 0x400:
                graphic = graphic.transpose(Image.Transpose.FLIP_LEFT_RIGHT)
            if entry & 0x800:
                graphic = graphic.transpose(Image.Transpose.FLIP_TOP_BOTTOM)
            xbase = pos % width * 16 + offset % 2 * 8
            ybase = pos // width * 16 + (offset % 4) // 2 * 8
            pal = palettes[entry >> 12]
            for y in range(8):
                for x in range(8):
                    index = graphic.getpixel((x, y)) % 16
                    if index:
                        output.putpixel((xbase + x, ybase + y), pal[index])
    return output


def render_proposed(data: dict, destination: Path) -> None:
    destination.mkdir(parents=True, exist_ok=True)
    for folder_name, cfg in CONFIG.items():
        item = data[folder_name]
        for name in cfg["maps"]:
            layout = layout_for(name)
            image = render(cfg["folder"], item["maps"][name], layout["width"],
                           item["sheet"], item["metatiles"], item["palette12"])
            image.resize((image.width * 3, image.height * 3), Image.Resampling.NEAREST).save(
                destination / f"{name}_after.png"
            )


def render_installed(destination: Path) -> None:
    destination.mkdir(parents=True, exist_ok=True)
    for cfg in CONFIG.values():
        folder = cfg["folder"]
        sheet = Image.open(folder / "tiles.png")
        metatiles = words(folder / "metatiles.bin")
        palette12 = (folder / "palettes/12.pal").read_bytes()
        for name in cfg["maps"]:
            layout = layout_for(name)
            blocks = words(ROOT / f"data/layouts/{name}/map.bin")
            image = render(folder, blocks, layout["width"], sheet, metatiles,
                           palette12)
            image.resize((image.width * 3, image.height * 3), Image.Resampling.NEAREST).save(
                destination / f"{name}_after.png"
            )


def audit() -> None:
    data = proposed()
    all_layouts = layouts()
    for folder_name, cfg in CONFIG.items():
        item = data[folder_name]
        allocation = item["allocation"]
        print(f"{folder_name}: {len(allocation['source_metatiles'])} metatiles -> "
              f"{min(allocation['metatile_map'].values()):03X}-"
              f"{max(allocation['metatile_map'].values()):03X}")
        print("  graphics:", " ".join(
            f"{source:03X}->{destination:03X}"
            for source, destination in allocation["graphic_map"].items()
        ))
        used_elsewhere = defaultdict(list)
        targets = set(allocation["source_metatiles"])
        for layout in all_layouts:
            if layout["secondary_tileset"] != cfg["tileset"]:
                continue
            ids = set()
            for key in ("blockdata_filepath", "border_filepath"):
                ids.update(value & 0x3FF for value in words(ROOT / layout[key]))
            if targets & ids and layout["name"] not in {layout_for(name)["name"] for name in cfg["maps"]}:
                used_elsewhere[layout["name"]] = sorted(targets & ids)
        print("  original metatiles also used by layouts preserved unchanged:")
        for name, ids in used_elsewhere.items():
            print("   ", name, " ".join(f"{value:03X}" for value in ids))


def apply() -> None:
    assert not BACKUP.exists(), "Backup already exists; refusing to overwrite or re-apply"
    data = proposed()
    before_hashes = {relative: digest(ROOT / relative) for relative in GAME_FILES}
    for relative in GAME_FILES:
        target = BACKUP / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / relative, target)
    references = REPORT / "references"
    references.mkdir(parents=True, exist_ok=True)
    for name, source in REFERENCE_FILES.items():
        assert source.exists(), source
        shutil.copy2(source, references / name)

    castula_palette12 = CONFIG["castula"]["folder"] / "palettes/12.pal"
    shutil.copy2(castula_palette12, CONFIG["ever_grande"]["folder"] / "palettes/12.pal")
    for folder_name, cfg in CONFIG.items():
        item = data[folder_name]
        item["sheet"].save(cfg["folder"] / "tiles.png")
        save_words(cfg["folder"] / "metatiles.bin", item["metatiles"])
        save_words(cfg["folder"] / "metatile_attributes.bin", item["attrs"])
        for name, values in item["maps"].items():
            save_words(ROOT / f"data/layouts/{name}/map.bin", values)

    after_hashes = {relative: digest(ROOT / relative) for relative in GAME_FILES}
    manifest = {
        "before_sha256": before_hashes,
        "after_sha256": after_hashes,
        "index_map": {str(k): v for k, v in INDEX_MAP.items()},
        "allocations": {
            folder: {
                "source_metatiles": [f"0x{x:03X}" for x in item["allocation"]["source_metatiles"]],
                "metatile_map": {f"0x{k:03X}": f"0x{v:03X}" for k, v in item["allocation"]["metatile_map"].items()},
                "graphic_map": {f"0x{k:03X}": f"0x{v:03X}" for k, v in item["allocation"]["graphic_map"].items()},
            }
            for folder, item in data.items()
        },
    }
    MANIFEST.write_text(json.dumps(manifest, indent=2) + "\n")
    render_proposed(data, PREVIEW)
    verify()


def retune_low_key() -> None:
    """Retune the already-allocated clones without consuming more space."""
    assert BACKUP.exists(), "Original before snapshot is missing"
    assert MANIFEST.exists(), "No allocation manifest"
    assert not LOW_KEY_BACKUP.exists(), "Low-key backup exists; refusing to re-apply"
    verify()

    manifest = json.loads(MANIFEST.read_text())
    for folder_name, cfg in CONFIG.items():
        relative = Path("data/tilesets/secondary") / folder_name / "tiles.png"
        snapshot = LOW_KEY_BACKUP / relative
        snapshot.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / relative, snapshot)

        original_sheet = Image.open(BACKUP / relative)
        installed_sheet = Image.open(ROOT / relative).copy()
        graphic_map = manifest["allocations"][folder_name]["graphic_map"]
        for source_hex, destination_hex in graphic_map.items():
            original = tile(original_sheet, int(source_hex, 16))
            recoloured = original.copy()
            recoloured.putdata([INDEX_MAP[value % 16] for value in original.getdata()])
            paste_tile(installed_sheet, int(destination_hex, 16), recoloured)
        installed_sheet.save(ROOT / relative)

    shutil.copy2(MANIFEST, LOW_KEY_BACKUP / "manifest_before_low_key.json")
    low_key_reference = REFERENCE_FILES["chosen_low_key_mockup.png"]
    assert low_key_reference.exists(), low_key_reference
    references = REPORT / "references"
    references.mkdir(parents=True, exist_ok=True)
    shutil.copy2(low_key_reference, references / "chosen_low_key_mockup.png")

    manifest["index_map"] = {str(k): v for k, v in INDEX_MAP.items()}
    manifest["after_sha256"] = {
        relative: digest(ROOT / relative) for relative in GAME_FILES
    }
    manifest.setdefault("iterations", []).append({
        "name": "low_key_retune",
        "backup": "before_low_key",
        "note": "Reused the existing cloned slots; no new graphics or metatiles allocated.",
    })
    MANIFEST.write_text(json.dumps(manifest, indent=2) + "\n")
    render_installed(PREVIEW)
    verify()


def simplify_in_place() -> None:
    """Replace the original building assets and remove the temporary clones."""
    assert BACKUP.exists(), "Original before snapshot is missing"
    assert MANIFEST.exists(), "No allocation manifest"
    assert not SIMPLIFIED_BACKUP.exists(), "Simplified-pass backup exists; refusing to re-apply"
    verify()

    manifest = json.loads(MANIFEST.read_text())
    for relative in GAME_FILES:
        snapshot = SIMPLIFIED_BACKUP / relative
        snapshot.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / relative, snapshot)
    shutil.copy2(MANIFEST, SIMPLIFIED_BACKUP / "manifest_before_simplified_in_place.json")

    ever_original = Image.open(BACKUP / "data/tilesets/secondary/ever_grande/tiles.png")
    quiet_patterns = {
        "wing_fill": tile(ever_original, 0x289).tobytes(),
        "centre_fill": tile(ever_original, 0x28B).tobytes(),
        "wall_ornament": tile(ever_original, 0x2B1).tobytes(),
    }

    for folder_name, cfg in CONFIG.items():
        relative_folder = Path("data/tilesets/secondary") / folder_name
        folder = ROOT / relative_folder
        original_folder = BACKUP / relative_folder
        allocation = manifest["allocations"][folder_name]

        original_sheet = Image.open(original_folder / "tiles.png")
        current_sheet = Image.open(folder / "tiles.png")
        sheet = current_sheet.crop((0, 0, original_sheet.width, original_sheet.height))

        # Castula's first pass used scattered blank slots in its fixed-size sheet.
        # Restore every one before installing the final in-place graphics.
        for destination_hex in allocation["graphic_map"].values():
            destination = int(destination_hex, 16)
            if destination - 0x200 < original_sheet.width // 8 * (original_sheet.height // 8):
                paste_tile(sheet, destination, tile(original_sheet, destination))

        for source_hex in allocation["graphic_map"].keys():
            source = int(source_hex, 16)
            original = tile(original_sheet, source)
            values = list(original.getdata())
            recoloured = [INDEX_MAP[value % 16] for value in values]
            raw = original.tobytes()
            if raw == quiet_patterns["wing_fill"]:
                recoloured = [0 if value % 16 == 0 else 7 for value in values]
            elif raw == quiet_patterns["centre_fill"]:
                recoloured = []
                for y in range(8):
                    for x in range(8):
                        value = original.getpixel((x, y)) % 16
                        keep_dash = ((y == 1 and x in (2, 3))
                                     or (y == 5 and x in (5, 6)))
                        recoloured.append(0 if value == 0 else (5 if value == 3 and keep_dash else 3))
            elif raw == quiet_patterns["wall_ornament"]:
                recoloured = [0 if value % 16 == 0 else 3 for value in values]
            output = original.copy()
            output.putdata(recoloured)
            paste_tile(sheet, source, output)

        current_metatiles = words(folder / "metatiles.bin")
        original_metatiles = words(original_folder / "metatiles.bin")
        metatiles = list(current_metatiles[:len(original_metatiles)])
        for source_hex in allocation["metatile_map"].keys():
            source = int(source_hex, 16)
            start = (source - 0x200) * 8
            for offset, entry in enumerate(metatiles[start:start + 8]):
                if entry >> 12 == cfg["source_palette"]:
                    metatiles[start + offset] = (entry & 0x0FFF) | (12 << 12)

        original_attrs = words(original_folder / "metatile_attributes.bin")
        attrs = words(folder / "metatile_attributes.bin")[:len(original_attrs)]

        inverse_metatiles = {
            int(destination, 16): int(source, 16)
            for source, destination in allocation["metatile_map"].items()
        }
        maps = {}
        for name in cfg["maps"]:
            current = words(ROOT / f"data/layouts/{name}/map.bin")
            maps[name] = [
                (value & ~0x3FF) | inverse_metatiles.get(value & 0x3FF, value & 0x3FF)
                for value in current
            ]

        sheet.save(folder / "tiles.png")
        save_words(folder / "metatiles.bin", metatiles)
        save_words(folder / "metatile_attributes.bin", list(attrs))
        for name, values in maps.items():
            save_words(ROOT / f"data/layouts/{name}/map.bin", values)

    manifest["installed_mode"] = "in_place"
    manifest["after_sha256"] = {
        relative: digest(ROOT / relative) for relative in GAME_FILES
    }
    manifest.setdefault("iterations", []).append({
        "name": "simplified_in_place",
        "backup": "before_simplified_in_place",
        "note": "Restored the test maps to original IDs, overwrote the original building assets, and reclaimed every clone allocation.",
    })
    manifest["quiet_tile_edits"] = {
        "wing_fill": "flat cool ivory",
        "centre_fill": "reduced each 3x2 brick to a 2x1 dash",
        "wall_ornament": "flat sandstone/peach",
    }
    MANIFEST.write_text(json.dumps(manifest, indent=2) + "\n")
    render_installed(PREVIEW)
    verify()


def final_palette_pass() -> None:
    """Restore original pixel art and apply the final mockup-matched palettes."""
    assert BACKUP.exists(), "Original before snapshot is missing"
    assert MANIFEST.exists(), "No allocation manifest"
    assert not FINAL_PALETTE_BACKUP.exists(), "Final-pass backup exists; refusing to re-apply"
    verify()

    manifest = json.loads(MANIFEST.read_text())
    for relative in GAME_FILES:
        snapshot = FINAL_PALETTE_BACKUP / relative
        snapshot.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / relative, snapshot)
    shutil.copy2(MANIFEST, FINAL_PALETTE_BACKUP / "manifest_before_final_palette_pass.json")

    # Restore all graphics, metatiles, attributes, test-map IDs, and Ever Grande's
    # formerly blank palette 12 from the untouched pre-task snapshot.
    for relative in GAME_FILES:
        original = BACKUP / relative
        if original.exists():
            shutil.copy2(original, ROOT / relative)

    # Keep the complete original upper-wing pixel pattern, but move its two
    # colours into the palette's close cream pair. No pixels are added/removed.
    for folder_name, graphic_id in (("castula", 0x331), ("ever_grande", 0x289)):
        path = ROOT / "data/tilesets/secondary" / folder_name / "tiles.png"
        sheet = Image.open(path).copy()
        original = tile(sheet, graphic_id)
        remapped = original.copy()
        remapped.putdata([
            11 if value % 16 == 2 else 12 if value % 16 == 11 else value % 16
            for value in original.getdata()
        ])
        paste_tile(sheet, graphic_id, remapped)
        sheet.save(path)

    final_palette = palette_text(FINAL_UNIVERSITY_PALETTE)
    (ROOT / "data/tilesets/secondary/castula/palettes/11.pal").write_text(final_palette)
    (ROOT / "data/tilesets/secondary/ever_grande/palettes/06.pal").write_text(final_palette)

    manifest["installed_mode"] = "original_assets_with_custom_palette"
    manifest["after_sha256"] = {
        relative: digest(ROOT / relative) for relative in GAME_FILES
    }
    manifest.setdefault("iterations", []).append({
        "name": "final_palette_pass",
        "backup": "before_final_palette_pass",
        "note": "Restored original pixel art/metatiles and applied matched source palettes; only the upper-wing fill swaps its existing two indices into the cream ramp.",
    })
    manifest["final_palette"] = [list(color) for color in FINAL_UNIVERSITY_PALETTE]
    manifest["final_graphic_index_swaps"] = {
        "castula_0x331": {"2": 11, "11": 12},
        "ever_grande_0x289": {"2": 11, "11": 12},
    }
    MANIFEST.write_text(json.dumps(manifest, indent=2) + "\n")
    render_installed(PREVIEW)
    verify()


def isolate_final_palette() -> None:
    """Move final colours to dedicated slots without touching unrelated users."""
    assert FINAL_PALETTE_BACKUP.exists(), "Final palette-pass backup is missing"
    assert MANIFEST.exists(), "No allocation manifest"
    assert not ISOLATED_PALETTE_BACKUP.exists(), "Isolated-palette backup exists; refusing to re-apply"
    verify()

    manifest = json.loads(MANIFEST.read_text())
    for relative in GAME_FILES:
        snapshot = ISOLATED_PALETTE_BACKUP / relative
        snapshot.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(ROOT / relative, snapshot)
    shutil.copy2(MANIFEST, ISOLATED_PALETTE_BACKUP / "manifest_before_isolated_palette.json")

    # Restore the broadly shared original source palettes. The preceding stage's
    # snapshot captured them immediately before they were customized.
    for relative in (
        "data/tilesets/secondary/castula/palettes/11.pal",
        "data/tilesets/secondary/ever_grande/palettes/06.pal",
    ):
        shutil.copy2(FINAL_PALETTE_BACKUP / relative, ROOT / relative)

    castula = CONFIG["castula"]["folder"]
    castula_sheet = Image.open(castula / "tiles.png").copy()
    castula_metatiles = words(castula / "metatiles.bin")

    # Palette 7 had only four unique graphics and five metatiles. Move them to
    # the very similar palette 8, freeing 7 for the university without clones.
    palette7_graphics = {
        entry & 0x3FF for entry in castula_metatiles if entry >> 12 == 7
    }
    for graphic in palette7_graphics:
        assert not any(
            (entry & 0x3FF) == graphic and entry >> 12 != 7
            for entry in castula_metatiles
        ), f"Palette-7 graphic {graphic:03X} is shared"
        original = tile(castula_sheet, graphic)
        moved = original.copy()
        remap = {2: 3, 3: 4, 4: 5, 6: 2}
        moved.putdata([remap.get(value % 16, value % 16) for value in original.getdata()])
        paste_tile(castula_sheet, graphic, moved)
    for index, entry in enumerate(castula_metatiles):
        if entry >> 12 == 7:
            castula_metatiles[index] = (entry & 0x0FFF) | (8 << 12)

    for source_hex in manifest["allocations"]["castula"]["metatile_map"].keys():
        source = int(source_hex, 16)
        start = (source - 0x200) * 8
        for offset, entry in enumerate(castula_metatiles[start:start + 8]):
            if entry >> 12 == 11:
                castula_metatiles[start + offset] = (entry & 0x0FFF) | (7 << 12)
    castula_sheet.save(castula / "tiles.png")
    save_words(castula / "metatiles.bin", castula_metatiles)

    ever = CONFIG["ever_grande"]["folder"]
    ever_metatiles = words(ever / "metatiles.bin")
    for source_hex in manifest["allocations"]["ever_grande"]["metatile_map"].keys():
        source = int(source_hex, 16)
        start = (source - 0x200) * 8
        for offset, entry in enumerate(ever_metatiles[start:start + 8]):
            if entry >> 12 == 6:
                ever_metatiles[start + offset] = (entry & 0x0FFF) | (12 << 12)
    save_words(ever / "metatiles.bin", ever_metatiles)

    final_palette = palette_text(FINAL_UNIVERSITY_PALETTE)
    (castula / "palettes/07.pal").write_text(final_palette)
    (ever / "palettes/12.pal").write_text(final_palette)

    manifest["installed_mode"] = "in_place_with_isolated_palettes"
    manifest["after_sha256"] = {
        relative: digest(ROOT / relative) for relative in GAME_FILES
    }
    manifest.setdefault("iterations", []).append({
        "name": "isolated_final_palette",
        "backup": "before_isolated_palette",
        "note": "Moved Castula's four palette-7 graphics to palette 8; final university uses Castula 7 and previously empty Ever Grande 12. Shared palettes 11/6 restored.",
    })
    manifest["final_palette_slots"] = {"castula": 7, "ever_grande": 12}
    manifest["castula_palette7_migration"] = {
        "destination_palette": 8,
        "graphics": [f"0x{value:03X}" for value in sorted(palette7_graphics)],
        "index_map": {"2": 3, "3": 4, "4": 5, "6": 2},
    }
    MANIFEST.write_text(json.dumps(manifest, indent=2) + "\n")
    render_installed(PREVIEW)
    verify()


def verify() -> None:
    assert MANIFEST.exists(), "No apply manifest"
    manifest = json.loads(MANIFEST.read_text())
    for relative, expected in manifest["after_sha256"].items():
        actual = digest(ROOT / relative)
        assert actual == expected, (relative, expected, actual)
    mode = manifest.get("installed_mode")
    if mode == "in_place_with_isolated_palettes":
        assert (CONFIG["castula"]["folder"] / "palettes/07.pal").read_bytes() == (
            CONFIG["ever_grande"]["folder"] / "palettes/12.pal"
        ).read_bytes()
        assert (CONFIG["castula"]["folder"] / "palettes/11.pal").read_bytes() == (
            CONFIG["ever_grande"]["folder"] / "palettes/06.pal"
        ).read_bytes()
    elif mode == "original_assets_with_custom_palette":
        assert (CONFIG["castula"]["folder"] / "palettes/11.pal").read_bytes() == (
            CONFIG["ever_grande"]["folder"] / "palettes/06.pal"
        ).read_bytes()
    else:
        assert (CONFIG["castula"]["folder"] / "palettes/12.pal").read_bytes() == (
            CONFIG["ever_grande"]["folder"] / "palettes/12.pal"
        ).read_bytes()
    print("University assets match the recorded installed state.")


def main() -> None:
    mode = sys.argv[1] if len(sys.argv) > 1 else "audit"
    if mode == "audit":
        audit()
    elif mode == "preview":
        render_proposed(proposed(), PREVIEW)
        print(PREVIEW)
    elif mode == "apply":
        apply()
    elif mode == "retune-low-key":
        retune_low_key()
    elif mode == "simplify-in-place":
        simplify_in_place()
    elif mode == "final-palette-pass":
        final_palette_pass()
    elif mode == "isolate-final-palette":
        isolate_final_palette()
    elif mode == "verify":
        verify()
    else:
        raise SystemExit(f"Unknown mode: {mode}")


if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Stage a dependency-minimal set of songs from the aichiya music branch.

This deliberately writes only to a staging directory.  The generated files can
then be reviewed and copied into the project as a mechanical asset import.
"""

from __future__ import annotations

import argparse
import re
import shutil
import subprocess
from pathlib import Path

from sanitize_music_midi import sanitize_midi_file


SONGS = [
    ("mus_bw_dreamyard", "-E -R5 -G_bw_main_3 -V093"),
    ("mus_bw_icirrus", "-E -R5 -G_bw_main_1 -V064"),
    ("mus_bw_lacunosa", "-E -R5 -G_bw_main_2 -V090"),
    ("mus_bw_nacrene", "-E -R5 -G_bw_main_3 -V070"),
    ("mus_bw_route10", "-E -R5 -G_bw_main_1 -V094"),
    ("mus_bw_route12_autumn", "-E -R5 -G_bw_main_2 -V071"),
    ("mus_bw_route12_winter", "-E -R5 -G_bw_main_2 -V071"),
    ("mus_bw_route2_summer", "-E -R5 -G_bw_main_2 -V082"),
    ("mus_dp_eterna_forest", "-E -R0 -G_dppt_main -V088"),
    ("mus_dp_floaroma_day", "-E -R0 -G_dppt_main -V110"),
    ("mus_dp_route201_day", "-E -R0 -G_dppt_main -V127"),
    ("mus_dp_route203_day", "-E -R0 -G_dppt_main -V100"),
    ("mus_dp_route205_day", "-E -R0 -G_dppt_main -V086"),
    ("mus_dp_route209_day", "-E -R0 -G_dppt_main -V086"),
    ("mus_dp_route210_day", "-E -R0 -G_dppt_main -V080"),
    ("mus_dp_route216_night", "-E -R0 -G_dppt_main -V100"),
    ("mus_dp_solaceon_day", "-E -R0 -G_dppt_main -V110"),
    ("mus_dp_sunyshore_night", "-E -R0 -G_dppt_main -V090"),
    ("mus_hg_b_hall", "-E -R0 -G_hgss_main -V080"),
    ("mus_hg_cianwood", "-E -R0 -G_hgss_main -V073"),
    ("mus_hg_route34", "-E -R0 -G_hgss_main -V092"),
    ("mus_hg_route47", "-E -R0 -G_hgss_main -V073"),
    ("mus_hg_vs_lugia", "-E -R0 -G_hgss_main -V102"),
    ("mus_hg_vs_ho_oh", "-E -R0 -G_hgss_main -V079"),
    ("mus_hg_ho_oh_appears", "-E -R0 -G_hgss_main -V108"),
    ("mus_hg_lugia_appears", "-E -R0 -G_hgss_main -V092"),
    ("mus_hg_vermilion", "-E -R0 -G_hgss_main -V062"),
]

MAIN_BANKS = ("dppt_main", "hgss_main", "bw_main_1", "bw_main_2", "bw_main_3")
DUMMY_VOICE = "voice_square_1 60, 0, 0, 2, 0, 0, 15, 0"


def uncomment_code(line: str) -> str:
    """Return active assembler text, with an inline @ comment removed."""
    return line.split("@", 1)[0].rstrip()


def symbols_in_voice(text: str) -> tuple[set[str], set[str], set[str]]:
    groups = set(re.findall(r"\bvoicegroup_[A-Za-z0-9_]+", text))
    tables = set(re.findall(r"\bkeysplit_[A-Za-z0-9_]+", text))
    samples = set(re.findall(r"\bDirectSoundWaveData_[A-Za-z0-9_]+", text))
    return groups, tables, samples


def active_voice_lines(path: Path) -> list[str]:
    result = []
    for raw in path.read_text().splitlines():
        code = uncomment_code(raw).strip()
        if re.match(r"voice_(?!group\b)", code):
            result.append(code)
    return result


def defined_groups(root: Path) -> set[str]:
    found = set()
    for path in (root / "sound/voicegroups").rglob("*.inc"):
        for raw in path.read_text(errors="ignore").splitlines():
            code = uncomment_code(raw).strip()
            match = re.match(r"voice_group\s+([A-Za-z0-9_]+)", code)
            if match:
                found.add("voicegroup_" + match.group(1))
    return found


def defined_tables(path: Path) -> set[str]:
    found = set()
    for raw in path.read_text(errors="ignore").splitlines():
        code = uncomment_code(raw).strip()
        match = re.match(r"keysplit\s+([A-Za-z0-9_]+)\s*,", code)
        if match:
            found.add("keysplit_" + match.group(1))
    return found


def direct_sound_blocks(path: Path) -> dict[str, tuple[str, str]]:
    lines = path.read_text(errors="ignore").splitlines()
    blocks: dict[str, tuple[str, str]] = {}
    for index, raw in enumerate(lines):
        match = re.match(r"(DirectSoundWaveData_[A-Za-z0-9_]+)::", raw.strip())
        if not match:
            continue
        label = match.group(1)
        incbin = ""
        for following in lines[index + 1:index + 5]:
            inc_match = re.search(r'\.incbin\s+"([^"]+)"', following)
            if inc_match:
                incbin = inc_match.group(1)
                break
        if incbin:
            blocks[label] = (incbin, f'\t.align 2\n{label}::\n\t.incbin "{incbin}"\n')
    return blocks


def table_blocks(path: Path) -> dict[str, str]:
    lines = path.read_text(errors="ignore").splitlines()
    starts = []
    for index, raw in enumerate(lines):
        code = uncomment_code(raw).strip()
        match = re.match(r"keysplit\s+([A-Za-z0-9_]+)\s*,", code)
        if match:
            starts.append((index, "keysplit_" + match.group(1)))
    blocks = {}
    for pos, (start, name) in enumerate(starts):
        end = starts[pos + 1][0] if pos + 1 < len(starts) else len(lines)
        block_lines = lines[start:end]
        while block_lines and not block_lines[-1].strip():
            block_lines.pop()
        blocks[name] = "\n".join(block_lines) + "\n"
    return blocks


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--project", type=Path, required=True)
    parser.add_argument("--donor", type=Path, required=True)
    parser.add_argument("--stage", type=Path, required=True)
    args = parser.parse_args()
    project = args.project.resolve()
    donor = args.donor.resolve()
    stage = args.stage.resolve()
    if stage.exists():
        shutil.rmtree(stage)
    stage.mkdir(parents=True)

    mid2agb = project / "tools/mid2agb/mid2agb"
    used: dict[str, set[int]] = {name: set() for name in MAIN_BANKS}
    midi_out = stage / "sound/songs/midi"
    midi_out.mkdir(parents=True)
    converted = stage / "converted"
    converted.mkdir()
    for song, options in SONGS:
        source = donor / f"sound/songs/midi/{song}.mid"
        if not source.exists():
            raise SystemExit(f"missing MIDI: {source}")
        target = midi_out / source.name
        shutil.copy2(source, target)
        sanitize_midi_file(target, write=True)
        temp_midi = converted / source.name
        shutil.copy2(target, temp_midi)
        subprocess.run([str(mid2agb), str(temp_midi), *options.split()], check=True)
        assembly = temp_midi.with_suffix(".s").read_text()
        bank_match = re.search(r"-G_([A-Za-z0-9_]+)", options)
        assert bank_match
        bank = bank_match.group(1)
        used[bank].update(int(value) for value in re.findall(r"VOICE\s*,\s*(\d+)", assembly))

    # Index active donor voice groups in include order. Every voice entry is a
    # fixed-size structure, so this also lets us faithfully resolve old banks
    # that intentionally ran into the next included group.
    include_paths = []
    for raw in (donor / "sound/voice_groups.inc").read_text().splitlines():
        match = re.match(r'\s*\.include\s+"([^"]+)"', uncomment_code(raw))
        if match and match.group(1).startswith("sound/voicegroups/"):
            include_paths.append(match.group(1))
    group_file: dict[str, str] = {}
    group_start: dict[str, int] = {}
    flat_entries: list[str] = []
    for rel in include_paths:
        path = donor / rel
        if not path.exists():
            continue
        entries = active_voice_lines(path)
        labels = []
        for raw in path.read_text(errors="ignore").splitlines():
            match = re.match(r"voice_group\s+([A-Za-z0-9_]+)", uncomment_code(raw).strip())
            if match:
                labels.append("voicegroup_" + match.group(1))
        if labels:
            # Files in this donor define one group apiece in practice. The
            # first label points at the first voice entry in that file.
            for label in labels:
                group_file[label] = rel
                group_start[label] = len(flat_entries)
        flat_entries.extend(entries)

    imported_groups = stage / "sound/voicegroups"
    imported_groups.mkdir(parents=True)
    generated_main_lines: dict[str, list[str]] = {}
    for bank in MAIN_BANKS:
        label = "voicegroup_" + bank
        if label not in group_start:
            raise SystemExit(f"donor bank not indexed: {bank}")
        start = group_start[label]
        rows = [f"voice_group {bank}  @ normalized 128-entry selective import"]
        chosen = []
        for slot in range(128):
            if slot in used[bank]:
                try:
                    voice = flat_entries[start + slot]
                except IndexError as exc:
                    raise SystemExit(f"{bank} slot {slot} falls outside donor data") from exc
                chosen.append(voice)
            else:
                voice = DUMMY_VOICE
            rows.append(f"\t{voice:<100} @ {slot:03d}")
        generated_main_lines[bank] = chosen
        (imported_groups / f"{bank}.inc").write_text("\n".join(rows) + "\n")

    current_groups = defined_groups(project)
    pending_groups: set[str] = set()
    needed_tables: set[str] = set()
    needed_samples: set[str] = set()
    for lines in generated_main_lines.values():
        for line in lines:
            groups, tables, samples = symbols_in_voice(line)
            pending_groups |= groups
            needed_tables |= tables
            needed_samples |= samples

    copied_group_files: set[str] = set()
    seen_groups: set[str] = set()
    while pending_groups:
        group = pending_groups.pop()
        if group in seen_groups or group in current_groups:
            continue
        seen_groups.add(group)
        rel = group_file.get(group)
        if rel is None:
            raise SystemExit(f"missing donor voice group definition: {group}")
        copied_group_files.add(rel)
        source = donor / rel
        for line in active_voice_lines(source):
            groups, tables, samples = symbols_in_voice(line)
            pending_groups |= groups
            needed_tables |= tables
            needed_samples |= samples

    for rel in sorted(copied_group_files):
        source = donor / rel
        target = stage / rel
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, target)

    current_table_names = defined_tables(project / "sound/keysplit_tables.inc")
    donor_tables = table_blocks(donor / "sound/keysplit_tables.inc")
    missing_tables = sorted(needed_tables - current_table_names)
    unknown_tables = [name for name in missing_tables if name not in donor_tables]
    if unknown_tables:
        raise SystemExit("missing keysplit tables: " + ", ".join(unknown_tables))
    imported_dir = stage / "sound/imported_music"
    imported_dir.mkdir(parents=True)
    (imported_dir / "keysplit_tables.inc").write_text(
        "@ Selective DPPt/HGSS/BW music import.\n\n"
        + "\n".join(donor_tables[name] for name in missing_tables)
    )

    current_direct = direct_sound_blocks(project / "sound/direct_sound_data.inc")
    donor_direct = direct_sound_blocks(donor / "sound/direct_sound_data.inc")
    missing_samples = sorted(needed_samples - set(current_direct))
    unknown_samples = [name for name in missing_samples if name not in donor_direct]
    if unknown_samples:
        raise SystemExit("missing direct sound labels: " + ", ".join(unknown_samples))
    (imported_dir / "direct_sound_data.inc").write_text(
        "@ Selective DPPt/HGSS/BW music import.\n\n"
        + "\n".join(donor_direct[name][1] for name in missing_samples)
    )
    copied_wavs = set()
    for label in missing_samples:
        incbin = donor_direct[label][0]
        if not incbin.endswith(".bin"):
            raise SystemExit(f"unexpected sample path for {label}: {incbin}")
        wav_rel = incbin[:-4] + ".wav"
        source = donor / wav_rel
        if not source.exists():
            raise SystemExit(f"missing WAV for {label}: {source}")
        target = stage / wav_rel
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, target)
        copied_wavs.add(wav_rel)

    voice_include_lines = [
        '@ Selective DPPt/HGSS/BW music import.',
        *[f'.include "sound/voicegroups/{bank}.inc"' for bank in MAIN_BANKS],
        *[f'.include "{rel}"' for rel in sorted(copied_group_files)],
    ]
    (imported_dir / "voice_groups.inc").write_text("\n".join(voice_include_lines) + "\n")
    (imported_dir / "manifest.txt").write_text(
        f"songs={len(SONGS)}\n"
        f"voice_group_files={len(copied_group_files) + len(MAIN_BANKS)}\n"
        f"keysplit_tables={len(missing_tables)}\n"
        f"direct_sound_samples={len(missing_samples)}\n"
        + "\n".join(f"{bank}_slots={','.join(map(str, sorted(slots)))}" for bank, slots in used.items())
        + "\n"
    )
    print((imported_dir / "manifest.txt").read_text(), end="")


if __name__ == "__main__":
    main()

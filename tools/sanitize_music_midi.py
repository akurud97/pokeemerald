#!/usr/bin/env python3
"""Remove MIDI controllers that mid2agb mistakes for track priorities.

Nintendo DS sequence-to-MIDI exports commonly contain controller 33 and 39
(fine modulation/volume data).  mid2agb treats both controllers as M4A PRIO
commands.  Values above the engine's normal cry priority can then prevent
Pokemon cries and sound effects from obtaining one of the five DirectSound
channels.

This tool removes only those controller events and carries their delta time to
the next event, so notes, tempo, instruments, and playback timing are retained.
"""

from __future__ import annotations

import argparse
import struct
from pathlib import Path


PRIORITY_CONTROLLERS = {33, 39}


def read_vlq(data: bytes, pos: int) -> tuple[int, int]:
    value = 0
    for _ in range(4):
        if pos >= len(data):
            raise ValueError("truncated variable-length quantity")
        byte = data[pos]
        pos += 1
        value = (value << 7) | (byte & 0x7F)
        if not byte & 0x80:
            return value, pos
    raise ValueError("invalid variable-length quantity")


def encode_vlq(value: int) -> bytes:
    if value < 0 or value > 0x0FFFFFFF:
        raise ValueError(f"delta time outside MIDI range: {value}")
    encoded = [value & 0x7F]
    value >>= 7
    while value:
        encoded.append(0x80 | (value & 0x7F))
        value >>= 7
    return bytes(reversed(encoded))


def sanitize_track(track: bytes) -> tuple[bytes, int]:
    output = bytearray()
    pos = 0
    running_status: int | None = None
    carried_delta = 0
    removed = 0

    while pos < len(track):
        delta, pos = read_vlq(track, pos)
        if pos >= len(track):
            raise ValueError("track ends after delta time")

        first = track[pos]
        if first & 0x80:
            status = first
            pos += 1
        elif running_status is not None:
            status = running_status
        else:
            raise ValueError("data byte without running status")

        if 0x80 <= status <= 0xEF:
            running_status = status
            data_size = 1 if status & 0xF0 in (0xC0, 0xD0) else 2
            end = pos + data_size
            if end > len(track):
                raise ValueError("truncated channel event")
            event_data = track[pos:end]
            pos = end

            if status & 0xF0 == 0xB0 and event_data[0] in PRIORITY_CONTROLLERS:
                carried_delta += delta
                removed += 1
                continue

            # Emit an explicit status for every channel event.  This keeps the
            # stream valid even when a removed event established running status.
            event = bytes((status,)) + event_data
        elif status == 0xFF:
            if pos >= len(track):
                raise ValueError("truncated meta event")
            meta_type = track[pos]
            pos += 1
            length, pos = read_vlq(track, pos)
            end = pos + length
            if end > len(track):
                raise ValueError("truncated meta-event payload")
            event = bytes((status, meta_type)) + encode_vlq(length) + track[pos:end]
            pos = end
        elif status in (0xF0, 0xF7):
            length, pos = read_vlq(track, pos)
            end = pos + length
            if end > len(track):
                raise ValueError("truncated SysEx payload")
            event = bytes((status,)) + encode_vlq(length) + track[pos:end]
            pos = end
        else:
            raise ValueError(f"unsupported MIDI status 0x{status:02X}")

        output.extend(encode_vlq(delta + carried_delta))
        output.extend(event)
        carried_delta = 0

    if carried_delta:
        raise ValueError("removed priority controller occurs after the final event")
    return bytes(output), removed


def sanitize_midi(data: bytes) -> tuple[bytes, int]:
    if len(data) < 14 or data[:4] != b"MThd":
        raise ValueError("not a Standard MIDI file")

    output = bytearray()
    pos = 0
    removed_total = 0
    while pos < len(data):
        if pos + 8 > len(data):
            raise ValueError("truncated MIDI chunk header")
        chunk_type = data[pos:pos + 4]
        chunk_size = struct.unpack(">I", data[pos + 4:pos + 8])[0]
        start = pos + 8
        end = start + chunk_size
        if end > len(data):
            raise ValueError("truncated MIDI chunk")
        payload = data[start:end]
        if chunk_type == b"MTrk":
            payload, removed = sanitize_track(payload)
            removed_total += removed
        output.extend(chunk_type)
        output.extend(struct.pack(">I", len(payload)))
        output.extend(payload)
        pos = end
    return bytes(output), removed_total


def sanitize_midi_file(path: Path, write: bool = False) -> int:
    original = path.read_bytes()
    sanitized, removed = sanitize_midi(original)
    if write and removed:
        path.write_bytes(sanitized)
    return removed


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Remove CC33/CC39 events that mid2agb converts to unsafe PRIO commands."
    )
    parser.add_argument("paths", nargs="+", type=Path, help="MIDI files to inspect")
    parser.add_argument("--write", action="store_true", help="replace affected MIDI files")
    args = parser.parse_args()

    total = 0
    for path in args.paths:
        removed = sanitize_midi_file(path, write=args.write)
        total += removed
        action = "removed" if args.write else "found"
        print(f"{path}: {action} {removed} unsafe controller event(s)")
    print(f"Total: {total}")


if __name__ == "__main__":
    main()

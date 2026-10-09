#!/usr/bin/env python3
"""Extract the unique Pokemon Pinball RSE samples from the supplied Emerald SF2.

The SoundFont was ripped and assembled by MezmerKaiser. Please retain that
credit when distributing music or assets made with these samples.
"""

from __future__ import annotations

import argparse
import math
import struct
from pathlib import Path


# sample index, output stem, loops, unity key, additional tuning in cents
SAMPLES = (
    (186, "pinball_rse_clavinet_low", True, 43, 0),
    (187, "pinball_rse_clavinet_mid", True, 55, 0),
    (188, "pinball_rse_clavinet_high", True, 80, 0),
    (189, "pinball_rse_clavinet_highest", True, 109, 13),
    (195, "pinball_rse_closed_cymbal", False, 42, 0),
    (196, "pinball_rse_open_cymbal", False, 46, 0),
    (198, "pinball_rse_muted_triangle", False, 80, 0),
    (199, "pinball_rse_triangle", False, 81, 0),
    (200, "pinball_rse_closed_hihat", False, 44, 0),
    (201, "pinball_rse_sine", True, 60, 0),
    (202, "pinball_rse_bongo", False, 60, 0),
    (204, "pinball_rse_japanese_percussion_3", False, 77, 0),
    (205, "pinball_rse_japanese_percussion_4", False, 60, 0),
    (207, "pinball_rse_japanese_percussion_1", False, 76, 0),
    (224, "pinball_rse_clarinet", True, 62, -20),
    (226, "pinball_rse_muted_staccato_trumpet", True, 72, 0),
    (227, "pinball_rse_nylon_guitar", True, 70, 0),
    (229, "pinball_rse_whistle", True, 51, 0),
    (230, "pinball_rse_picked_bass", True, 70, 0),
    (231, "pinball_rse_rock_organ", True, 61, 0),
    (232, "pinball_rse_vibraphone", True, 73, 0),
    (233, "pinball_rse_bubbles", False, 60, 0),
    (243, "pinball_rse_bike_bell", False, 60, 0),
    (246, "pinball_rse_shamisen", True, 58, 0),
    (247, "pinball_rse_slap_bass", True, 48, 0),
    (259, "pinball_rse_snare", False, 40, 0),
    (260, "pinball_rse_japanese_percussion_bell", False, 84, 0),
    (267, "pinball_rse_xylophone", True, 63, 0),
    (268, "pinball_rse_saxophone", True, 65, 0),
    (270, "pinball_rse_deep_piano", True, 31, 0),
    (271, "pinball_rse_contrabass", True, 55, 0),
    (272, "pinball_rse_drawbar_organ", True, 58, 0),
    (874, "pinball_rse_oriental_flute", True, 60, 0),
    (875, "pinball_rse_clarinet_relooped", True, 72, 0),
    (876, "pinball_rse_oboe_relooped", True, 60, 0),
    (877, "pinball_rse_voice_aahs_relooped", True, 60, 0),
    (878, "pinball_rse_distortion_guitar_relooped", True, 60, 0),
    (879, "pinball_rse_gamelan_relooped", True, 60, 0),
    (880, "pinball_rse_electric_piano_relooped", True, 60, 0),
)


def get_chunk(data: bytes, tag: bytes) -> bytes:
    offset = data.find(tag)
    if offset < 0:
        raise ValueError(f"SoundFont is missing its {tag.decode()} chunk")
    size = struct.unpack_from("<I", data, offset + 4)[0]
    return data[offset + 8 : offset + 8 + size]


def riff_chunk(tag: bytes, payload: bytes) -> bytes:
    padding = b"\0" if len(payload) & 1 else b""
    return tag + struct.pack("<I", len(payload)) + payload + padding


def make_wave(
    pcm: bytes,
    source_rate: int,
    unity_key: int,
    tuning_cents: int,
    loop_start: int,
    loop_end_exclusive: int,
    loops: bool,
) -> bytes:
    # Normalize the tuning to middle C, matching the existing pokeemerald WAVs.
    effective_rate = source_rate * math.pow(
        2.0, (60.0 - unity_key) / 12.0 + tuning_cents / 1200.0
    )
    wav_rate = max(1, int(effective_rate))
    agb_pitch = max(1, int(effective_rate * 1024.0))

    fmt = struct.pack("<HHIIHH", 1, 1, wav_rate, wav_rate, 1, 8)
    sample_period = max(1, int(round(1_000_000_000.0 / effective_rate)))
    smpl = struct.pack("<9I", 0, 0, sample_period, 60, 0, 0, 0, int(loops), 0)

    if loops:
        # SoundFont loop ends are exclusive; WAV smpl loop ends are inclusive.
        loop_start = min(max(loop_start, 0), len(pcm) - 1)
        loop_end = min(max(loop_end_exclusive - 1, loop_start), len(pcm) - 1)
        smpl += struct.pack("<6I", 0, 0, loop_start, loop_end, 0, 0)
    else:
        loop_end = len(pcm) - 1

    chunks = b"".join(
        (
            riff_chunk(b"fmt ", fmt),
            riff_chunk(b"smpl", smpl),
            riff_chunk(b"agbp", struct.pack("<I", agb_pitch)),
            riff_chunk(b"agbl", struct.pack("<I", loop_end)),
            riff_chunk(b"data", pcm),
        )
    )
    return b"RIFF" + struct.pack("<I", len(chunks) + 4) + b"WAVE" + chunks


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("soundfont", type=Path)
    parser.add_argument("output_dir", type=Path)
    args = parser.parse_args()

    sf2 = args.soundfont.read_bytes()
    if sf2[:4] != b"RIFF" or sf2[8:12] != b"sfbk":
        raise ValueError(f"Not a SoundFont: {args.soundfont}")

    sample_pool = get_chunk(sf2, b"smpl")
    headers = get_chunk(sf2, b"shdr")
    args.output_dir.mkdir(parents=True, exist_ok=True)

    for sample_index, stem, loops, unity_key, extra_tuning in SAMPLES:
        offset = sample_index * 46
        header = headers[offset : offset + 46]
        if len(header) != 46:
            raise ValueError(f"Missing SoundFont sample index {sample_index}")

        start, end, loop_start, loop_end, rate, _key, correction, _link, _type = (
            struct.unpack_from("<IIIIIBbHH", header, 20)
        )
        frame_count = end - start
        values = struct.unpack_from(f"<{frame_count}h", sample_pool, start * 2)
        # SF2 PCM is signed 16-bit; GBA DirectSound source WAVs are unsigned 8-bit.
        pcm = bytes((((value >> 8) + 128) & 0xFF) for value in values)

        wave = make_wave(
            pcm,
            rate,
            unity_key,
            correction + extra_tuning,
            loop_start - start,
            loop_end - start,
            loops,
        )
        (args.output_dir / f"{stem}.wav").write_bytes(wave)

    print(f"Imported {len(SAMPLES)} unique Pinball RSE samples.")


if __name__ == "__main__":
    main()

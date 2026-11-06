# Tone Rebellion — static decompilation workspace

## Play the remake

The C11 remake built from this analysis lives in [ToneRebellion_Remake/](ToneRebellion_Remake/README.md). Windows builds are on the [releases page](https://github.com/Fadoli/Tone-Rebellion-Remastered/releases) and the browser version is at [fadoli.github.io/Tone-Rebellion-Remastered](https://fadoli.github.io/Tone-Rebellion-Remastered/). Both need your own copy of *Tone Rebellion* (installed folder, CD or `.iso`); no game data is distributed here. A tag `v*` builds and publishes both ([release workflow](.github/workflows/release.yml)).

## Target and method

Static analysis of `C:\Program Files\Tone\FLOAT.EXE` (x86 PE, version 1.16F) with Ghidra 12.1.4 through REA. The binary, the COB archives and the Ghidra projects are immutable references; the original game is never run.

Observed facts, interpretations and unknowns are kept apart. Names and types reconstructed by Ghidra are provisional. The method and the instructions for picking the work up are in [AGENTS.md](AGENTS.md).

## Local data

The extracted corpus is under `C:\git\ToneRebellion_Raw\original_content`; the unpacked ISO is under `C:\toneIso`. The 483 COB members are indexed in [archive_index.jsonl](archive_index.jsonl). Do not search for or download the corpus online.

## Coverage

The inventory has 2,410 procedures: 1,507 decompiled bodies, 780 thunks and 123 externals. Details and limits: [evidence/manifest.md](evidence/manifest.md), [unknowns.md](unknowns.md).

## Navigation

- [FUNCTION_GUIDE.md](FUNCTION_GUIDE.md) — function index with links to the detailed evidence.
- [behavior_map.md](behavior_map.md) and [behavior/](behavior/) — flows and behaviour by area (notes kept in French, the analysis language).
- [functions/](functions/) — Ghidra pseudocode and metadata.
- [data_catalog.md](data_catalog.md), [cob_archives.md](cob_archives.md) — formats and resources.
- [ToneRebellion_Remake/README.md](ToneRebellion_Remake/README.md) — remake: play, build, tests, releases.
- [ToneRebellion_Remake/TODO.md](ToneRebellion_Remake/TODO.md) — next remake tasks.
- [ToneRebellion_Remake/docs/differences-from-original.md](ToneRebellion_Remake/docs/differences-from-original.md) — where the remake knowingly differs from the original game (network pause, save and load, Escape shortcut, end screen, saves).

# FLOAT.EXE decompilation workspace

Static analysis of `FLOAT.EXE` (x86 PE, version 1.16F), the executable of *Tone Rebellion*, done with Ghidra through REA. The binary, the COB archives and the Ghidra projects are read-only references; the original game is never run. The [remake](../ToneRebellion_Remake/README.md) is built from these notes.

The notes keep apart what Ghidra shows, what is interpreted from it, and what is still unknown. Names such as `FUN_...`, and all reconstructed types, are provisional; the pseudocode is decompiler output, not the original source. Working rules: [AGENTS.md](../AGENTS.md).

## Coverage

The inventory has 2,410 procedures: 1,507 decompiled bodies, 780 thunks and 123 externals. Counts and limits: [evidence/manifest.md](evidence/manifest.md), [unknowns.md](unknowns.md).

## Map

| Path | Content |
|---|---|
| [FUNCTION_GUIDE.md](FUNCTION_GUIDE.md) | Function index, with links to the evidence |
| [behavior_map.md](behavior_map.md), [behavior/](behavior/) | Game behaviour by area: flows, rules, formats (in French, the analysis language) |
| [functions/](functions/), [index.jsonl](index.jsonl) | Ghidra pseudocode and one metadata entry per procedure |
| [data_catalog.md](data_catalog.md) | Data files and their parsers |
| [cob_archives.md](cob_archives.md), [archive_index.jsonl](archive_index.jsonl) | `TONE00/01.COB` archives and their 483 members |
| [audio_inventory.md](audio_inventory.md) | Sounds and music |
| [remake_spec.md](remake_spec.md), [world_start_distribution.md](world_start_distribution.md) | Specification notes for the remake |
| [evidence/](evidence/), [unknowns.md](unknowns.md) | Coverage counts, open questions |

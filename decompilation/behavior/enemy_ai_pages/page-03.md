# Enemy AI and autonomous unit behavior

## Next evidence to chase

- Resolve the relationship between per-unit category, owning tribe, and planet/island fields; `FUN_0042219e` and candidate filters use several independent records.
- Trace all writers/readers of the per-player tables consulted by `FUN_00420991` and the state/target fields written by `FUN_0042219e`.
- Trace readers of location timer `+0x45a` and resolve the source-level meanings of mode-2 location fields and per-island counters used by Spore site conversion.
- Trace attack/`atteff`/`attxy` consumers, damage/death transitions, and spell creation from the floater update and effect manager.
- Trace regular-unit attached task records and the shared flag-`0x10` auto-engage helper through the record and flag writers.
- Trace the remaining Leviathan site-to-unit production/replenishment chain from converted location type 4.
- Trace the difficulty global `DAT_004bf11c` and world field `+0x2cc30` readers beyond the currently identified damage, recruiter-preference, and score paths.

---

# Enemy AI and autonomous unit behavior

## Evidence limits

The focused pass used the existing Ghidra 12.1.4 static analysis of `FLOAT.EXE`, PE x86 SHA-256 `bb229d7f09c88caf4dc1825c00b957961c22c201cf1a8dd8139bf6f4599ff28c`. Whole-program indexing records 2,410 recognized procedures and 2,209 defined strings; this does not prove that every code region, indirect call, or undefined/packed string was recovered. No runtime observation was performed. `Float.pdb` is referenced in PE metadata, but its availability/load state is unknown; no original names or types are inferred from a PDB.

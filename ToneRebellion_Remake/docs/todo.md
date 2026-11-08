# Remaining work

Port only behaviour established by the binary and the local data. Evidence: `decompilation/behavior/` and [FUNCTION_GUIDE.md](../../decompilation/FUNCTION_GUIDE.md); overall state and kept gaps: [roadmap](roadmap.md); remake choices: [differences from the original game](differences-from-original.md). Finished work is not listed here (see the reviews and the git history).

## To do

- Check in game: contamination of a class-1 marker by a Spore, hover over the trait triggers (none is reachable in the fixtures).
- Local clean-up (ignored by git): copies `ToneRebellion_Remake_sdl - Copie*.exe`, `ToneRebellion_Remake*.zip`, `../hs_err_pid*.log`, `mci_debug.log`.

## Not ported

- Texts: background `DAT_004c2b08`.
- Network: `FUN_00465793` category 3, subtype 4 (one resource added to an island, pending count decremented). No sender of that packet was found (REA 2026-11-05).

## Minor gaps

- Approximate site clean-up.

## Open REA questions

None. The 2026-11-04 pass closed the previous ones ([floater states](../../decompilation/behavior/floater-states.md)): CONSTR guards already ported, no producer of state 10, no `x` prefix, callers, bodies, `IWLocInfo` class and message 0x47 established.

## Out of scope

HallStk mode and the names of genres 0x2c; exact native multiplayer (DirectPlay, chat); other `nevada` commands (keyboard rotation and zoom, task keys `U`/`F`: [tasks](../../decompilation/behavior/island-tasks.md)).

# Remaining work

Port only behaviour established by the binary and the local data. Evidence: `../behavior/` and [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md); overall state and kept gaps: [roadmap](ROADMAP.md); remake choices: [differences from the original game](docs/differences-from-original.md). Finished work is not listed here (see the reviews and the git history).

## To do

- Building move: the source is cleared at the placement; the original sets `+0x58 = 3` and clears it 8 to 16 ticks later (`FUN_0045343b`, `FUN_00450a71`). The port cannot keep that delay while the Hall search would see two Halls ([analysis](../behavior/island-ground-object-interaction.md)).
- Check in game: Repair through the repair list up to full health (fixture `repair`: button and list checked), contamination of a class-1 marker by a Spore, the full victory sequence (solo and network; in a network game `F11` sends command 0x15), hover over the trait triggers (none is reachable in the fixtures).
- Local clean-up (ignored by git): copies `ToneRebellion_Remake_sdl - Copie*.exe`, `ToneRebellion_Remake*.zip`, `../hs_err_pid*.log`, `mci_debug.log`.

## Not ported

- Tasks: AI branch for workers in danger (`DAT_005eebd4`, states 6/7), second caller of `FUN_004239e9` (state 0x13, sub-case 0x14), task types 6, 0x11 and 0xd of the "urgent" list.
- Texts: genre 3 `FEAT%02d` (keys missing from the data, table `DAT_005eebf8` not modelled), pool texts `POOLINFECT`/`SUPPLY_%d`; background `DAT_004c2b08`.
- Network: direct placement `FUN_00465793` (category 3, subtype 4), only through the relay `FUN_00412eac`.

## Minor gaps

- Wrapped `IWTextInfo` text placed at y = 0x10 (original (10, 6)).
- Badge 0x1e (Leviathan) and the owner-4 `spl11` veil never drawn: `DAT_0061fa2e` has no known writer.
- Approximate site clean-up.

## Open REA questions

None. The 2026-11-04 pass closed the previous ones ([floater states](../behavior/floater-states.md)): CONSTR guards already ported, no producer of state 10, no `x` prefix, callers, bodies, `IWLocInfo` class and message 0x47 established.

## Out of scope

HallStk mode and the names of genres 0x2c; exact native multiplayer (DirectPlay, chat); `intro.avi`; `nevada` commands (keyboard rotation and zoom).

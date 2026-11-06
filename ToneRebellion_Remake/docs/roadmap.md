# Roadmap

State on 2026-11-05. Remaining work: [TODO](todo.md); ported features: [implemented.md](implemented.md); remake choices that differ from the original: [differences from the original game](differences-from-original.md); evidence: `decompilation/behavior/` and [FUNCTION_GUIDE.md](../../decompilation/FUNCTION_GUIDE.md).

## Status

- Decompilation: `decompilation/index.jsonl` covers 2410 procedures (1493 internal, 780 thunks, 123 external, 14 runtime); 1507 decompiled, 903 excluded with a reason. The inventory is closed; remaining REA work is targeted, not a sweep, and no REA question is open.
- Remake: ~47 k lines of C11 (`src/`), 27 CTest entries (C unit tests and `tests/test_docs_integrity.mjs`), plus `tests/e2e/island_e2e.ps1` and `tests/e2e/fixture_e2e.ps1` (generated static games, never the player's saves).

## Done

- **Game loop**: manual movement, building orders (`BC_*`, adoption `FUN_0042219e`), tasks (CONSTR, CHARGE, Obtain, SUPPLY, UpgSpread, Upgrade, Repair through the repair list, Hall type 4), return of subtypes 4 and 8 after an action, recruiter with its fallback birth island.
- **Opponents**: Leviathan AI (contamination, defence, production, attacks, retaliation `FUN_00421d82`); the original has no planner for opposing tribes.
- **End of game**: seal victory (sequence states 2..7, also in network games), defeat when no floater is left, end screen with score cards ([end of game](../../decompilation/behavior/end-game.md)).
- **Saving**: remake saves that survive `GameSession` changes (field table), original saves with their score counters, tribe choice when several tribes were played.
- **Interface**: panel parity, fonts, world map, FLTINFO badges (state badge and spell shimmer included), pause (island and map frozen, eye closed), starting buildings already built, title screen stars and credits, move button frames while a building is held, repair button pulse.
- **Audio**: volume and pan by distance, producer, island and collapse sounds.
- **Web and SDL**: web port done in 8 steps (1 portable `RenderSurface`, 2 `platform_*` services, 3 SDL3 adapter, 4 Emscripten target, 5 user data, 6 `IDBFS` saves, 7 browser audio, 8 single-player web build); CD image (`.iso`) import.
- **Network**: lockstep TCP play checked SDL to SDL; pause, game speed, save, loading a saved game and reconnection after a lost connection or a restart of the game in network play, build check in `HELLO` (remake extensions).
- **Checks**: static fixtures (`TONE_REBELLION_E2E_FIXTURE`: badges, enemy_hall, spell, obtain, dying, victory, messages, return, repair) with `TONE_REBELLION_SAVE_DIR`; `tests/e2e/fixture_e2e.ps1` and `tests/e2e/island_e2e.ps1` ([validation](build-and-validation.md)).

## Kept gaps

- Bridge crossing: the `+0x3c` order is kept in `handoff_resume_action`; it resumes on the same tick as the original, with no observable difference.
- Building move: the old site fades out over 8 to 16 ticks as in the original (`FUN_00450a71`), but its game state is cleared at the placement so the Hall is never found twice.
- CONSTR: the port keeps action 4 where the original carries action 5 (`FA_Build`), with no observed effect.
- Clipboard: filled with every owned training building by default (`game_session_clip_auto_register`); the remake options switch to the original (only the selected one).
- Every remake choice visible to the player (network pause, save and load, Escape shortcut, end screen click, repair button, paused load, tribe choice) is listed in [differences from the original game](differences-from-original.md).

Out of scope and open points: [TODO](todo.md).

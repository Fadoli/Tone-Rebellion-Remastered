# Differences from the original game

This page lists every behaviour of the remake that knowingly differs from `FLOAT.EXE` 1.16F, so a player or a reviewer can tell remake choices from ported behaviour. Everything else aims at the original behaviour; the evidence for it is in `../behavior/` and [FUNCTION_GUIDE.md](../../FUNCTION_GUIDE.md). Gaps that are not choices (behaviour not ported yet) are listed in the [TODO](../TODO.md).

## Network play

| Topic | Original | Remake |
|---|---|---|
| Transport | DirectPlay sessions, native channels and turn rate. | Own TCP records (port 28610 by default) and lockstep turns of one tick (50 ms); see [multiplayer](../../behavior/multiplayer.md). No chat, no reconnection. |
| Lobby entry | DirectPlay property sheet (`FUN_0044c2b9`). | "Multijoueur" title button (`M`), the remake setup screen, `H`/`J` on the title, or `--host` / `--join address`. |
| Tribes | One player per tribe. | Several players may share a tribe (co-operation). |
| Pause | Refused in a network game (`FUN_004578df`, `DAT_004befe0 != 0`). | The pause zone of the options panel pauses every machine on the same turn (`GAME_COMMAND_SET_NETWORK_PAUSE`); turns keep flowing so the resume can arrive. Any player can pause or resume. |
| Save | Refused in a network game. | The Save zone and `F5` save a local copy of the shared session; turns go on while the Save screen is open. Loaded outside a network game, such a save continues as a solo game. |
| Load | Refused in a network game. | The host loads: `L` in the lobby, or the Load zone of the options panel during a game (guests cannot). A pick during a game sends every machine back to the lobby. The file goes to each guest (`NET_RECORD_SAVE_DATA`, 2 KB chunks); every machine applies the same bytes and acknowledges; the lobby becomes the tribe choice below; the start waits for every acknowledgement. |
| Debug end sequence | Key `W` with the debug flag `DAT_004c2b74` sends world command 0x15. | `F11` in a network game sends the same command (`GAME_COMMAND_START_END_SEQUENCE`). |
| End screen cards | `ENDGNONP` cards drawn in a network game. | Same; the remake draws them from the scores taken when the screen opens. |

## Saving and loading

| Topic | Original | Remake |
|---|---|---|
| Save format | 0x80-byte header and four engine streams (`FUN_0045749a` / `FUN_004576c7`). | Same header, then a remake body: the `GameSession` field table and the raw session. A later build copies the fields by name, so a save survives added, removed or resized fields ([build and validation](build-and-validation.md)). Original saves are still read. |
| Save location | Game directory. | A `saves` directory next to the executable (or `TONE_REBELLION_SAVE_DIR`); the game directory is never written. |
| Loaded game | Resumes running. | Opens paused, with the options panel open; the player resumes from the pause zone. |
| Several played tribes | No such case (one local tribe). | Loading a game where two or more tribes were played (more than the starting Hall, a building order, or a queued task) opens the New Game screen as a tribe choice: unplayed tribes drawn black and not selectable, world size and difficulty locked; NEWGAME continues as the picked tribe. |

## Keyboard and mouse

| Topic | Original | Remake |
|---|---|---|
| Escape on the island or the world map | No effect. | Opens or closes the options panel (save, load, pause, quit, music, sound). It first puts back a held building, or disarms an armed spell or order. The island returns to the map through `GOTOMAP`. |
| End screen | A click on the player card, the story text or a card leaves to the title (`SetState(0)`); nothing skips the scroll. | A click skips the text scroll and the card reveal; Escape leaves to the title and ends the game. |
| Save screen | No known entry key. | `F5` on the map or the island. |
| Shift + right click | Not a merge shortcut. | Orders the selected floater to merge. |
| Test aids | None. | `F6` producer, `F7` remove the tribe's floaters, `F8` building for the next tribe, `F9` training building, `F11` end screen preview (solo); `C`, `H`, `R` only with `TONE_REBELLION_E2E_STATE`. |

## Interface

| Topic | Original | Remake |
|---|---|---|
| Repair button | Shown on every eligible site; damage is checked at the click (`FUN_00452b67`). | Shown only on an own damaged building, or one already in the repair list. Its pulse while active is ported (`FUN_00442d60`). |
| Clipboard | Fills with the selected training building (`FUN_00438120`). | Fills with every owned training building (`game_session_clip_auto_register`); removing that call in `island_view_render.inc` restores the original. |
| Credits text | Font not set by the code. | SMFONT, default pen; the star field uses its own random state. |

## Simulation

| Topic | Original | Remake |
|---|---|---|
| Building move | The source site is cleared 8 to 16 ticks after the placement (`FUN_00450a71`). | Cleared at once: the delay would show two Halls to the Hall search. |
| CONSTR action | Workers carry action 5 (`FA_Build`). | Action 4, with no observed effect. |
| Birth site | Picked on events and kept between them (`FUN_0045e6d3`). | Searched again every tick; same result while the markers do not change. |

## Platforms

| Topic | Original | Remake |
|---|---|---|
| Systems | Windows 9x, DirectX. | Win32 and SDL3 builds, and a browser build (Emscripten). |
| Browser data | — | The page asks for the game folder or the CD image (`.iso`, ISO 9660, read by slices); files stay in the browser storage. |

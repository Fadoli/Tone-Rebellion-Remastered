# Differences from the original game

This page lists every behaviour of the remake that knowingly differs from `FLOAT.EXE` 1.16F, so a player or a reviewer can tell remake choices from ported behaviour. Everything else aims at the original behaviour; the evidence for it is in `../behavior/` and [FUNCTION_GUIDE.md](../../FUNCTION_GUIDE.md). Gaps that are not choices (behaviour not ported yet) are listed in the [TODO](../TODO.md).

## Network play

| Topic | Original | Remake |
|---|---|---|
| Transport | DirectPlay sessions, native channels and turn rate. | Own TCP records (port 28610 by default) and lockstep turns of one tick (50 ms); see [multiplayer](../../behavior/multiplayer.md). No chat. A slow player makes the others wait (with an "En attente de" message) instead of being dropped. |
| Lost connection | The player leaves the session. | The player's slot is kept for 2 minutes while the game goes on; its machine reconnects by itself and receives the current session (`NET_RECORD_REJOIN`, `NET_RECORD_RESYNC`); a player who restarted the game gets the slot back by joining again with the same name. Both sides must run the same build (session layout tag in `HELLO`). A link silent for 15 s counts as lost. After 2 minutes the tribe hands its glyphs back, as when a player leaves. |
| Lobby entry | DirectPlay property sheet (`FUN_0044c2b9`). | "Multijoueur" title button (`M`), the remake setup screen, `H`/`J` on the title, or `--host` / `--join address`. |
| Tribes | One player per tribe. | Several players may share a tribe (co-operation). |
| Pause | Refused in a network game (`FUN_004578df`, `DAT_004befe0 != 0`). | The pause zone of the options panel pauses every machine on the same turn (`GAME_COMMAND_SET_NETWORK_PAUSE`); turns keep flowing so the resume can arrive. Any player can pause or resume. |
| Save | Refused in a network game. | The Save zone and `F5` save a local copy of the shared session; turns go on while the Save screen is open. Loaded outside a network game, such a save continues as a solo game. |
| Load | Refused in a network game. | The host loads: `L` in the lobby, or the Load zone of the options panel during a game (guests cannot). A pick during a game sends every machine back to the lobby. The file goes to each guest (`NET_RECORD_SAVE_DATA`, 2 KB chunks); every machine applies the same bytes and acknowledges; the lobby becomes the tribe choice below; the start waits for every acknowledgement. |
| Game speed | Keys `8`/`9` (and numpad `-`/`+`) allowed only with `multispeed` in `FLOAT.CFG`; a network game starts at speed 2 (`GAMEENV +0x130`), plus catch-up ticks `DAT_004bf114`. | Always allowed; any player changes the speed for every machine on the same turn (`GAME_COMMAND_SET_NETWORK_SPEED`, 1..3 ticks per turn). A network game starts at speed 1. |
| Debug end sequence | Key `W` with the debug flag `DAT_004c2b74` sends world command 0x15. | `F11` in a network game sends the same command (`GAME_COMMAND_START_END_SEQUENCE`). |
| End screen cards | `ENDGNONP` cards drawn in a network game. | Same; the remake draws them from the scores taken when the screen opens. |

## Saving and loading

| Topic | Original | Remake |
|---|---|---|
| Save format | 0x80-byte header and four engine streams (`FUN_0045749a` / `FUN_004576c7`). | Same header, then a remake body: the `GameSession` field table and the raw session. A later build copies the fields by name, so a save survives added, removed or resized fields ([build and validation](build-and-validation.md)). Original saves are still read. |
| Save location | Game directory. | A `saves` directory next to the executable (or `TONE_REBELLION_SAVE_DIR`); the game directory is never written. |
| Loaded game | Resumes running. | Opens paused by default, with the options panel open; the player resumes from the pause zone. The remake options can turn this off. |
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
| Remake options | — | F2 on the island or the world map, or the left claw of the options panel (Escape), opens a panel for the remake's own settings: display rate, scaling, game speed, music, sound effects, whether a loaded game starts paused, and whether the clipboard is filled with every training building (remake) or only the selected one (original). Arrows or clicks change them; `video.cfg` (`loadpaused`, `clipall`) and `audio.cfg` keep them. |
| Window scaling | Fixed 640x480 display mode. | The 640x480 picture fills a window: whole multiples with bars, fill (nearest pixel), fill (smooth), or fill (sharp bilinear: nearest-pixel scale by the largest whole factor, then a linear stretch, so pixels stay crisp and evenly sized with soft edges). F12, the window menu or the remake options change it; `video.cfg` keeps it (`scale`). |
| Display rate | The island and the world map are drawn once per 20 frames/s game frame, with 1 to 3 simulation ticks each (game speed), so motion steps by up to 3 ticks per picture. | The game frame still runs at 20 frames/s, but the picture is painted at 20, 40, 60 (default) or 120 Hz: units, shots, spell effects and the world-map orbits are blended between the last two game frames, one frame (50 ms) behind. 20 Hz paints as the original. Shift+F12, the window menu or the remake options change it; `video.cfg` keeps it (`fps`). Sprite frames stay the original ones. |
| Browser data | — | The page asks for the game folder or the CD image (`.iso`, ISO 9660, read by slices); files stay in the browser storage. |

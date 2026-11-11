# Differences from the original game

This page lists every behaviour of the remake that knowingly differs from `FLOAT.EXE` 1.16F, so a player or a reviewer can tell remake choices from ported behaviour. Everything else aims at the original behaviour; the evidence for it is in `decompilation/behavior/` and [FUNCTION_GUIDE.md](../../decompilation/FUNCTION_GUIDE.md). Gaps that are not choices (behaviour not ported yet) are listed in the [TODO](todo.md).

## Network play

| Topic | Original | Remake |
|---|---|---|
| Transport | DirectPlay sessions, native channels and turn rate. | Own TCP records (port 28610 by default) and lockstep turns of one tick (50 ms); see [multiplayer](../../decompilation/behavior/multiplayer.md). No chat. A slow player makes the others wait (with an "En attente de" message) instead of being dropped. |
| Lost connection | The player leaves the session. | The player's slot is kept for 2 minutes while the game goes on; its machine reconnects by itself and receives the current session (`NET_RECORD_REJOIN`, `NET_RECORD_RESYNC`); a player who restarted the game gets the slot back by joining again with the same name. Both sides must run the same build (session layout tag in `HELLO`). A link silent for 15 s counts as lost. After 2 minutes the tribe hands its glyphs back, as when a player leaves. |
| Lobby entry | DirectPlay property sheet (`FUN_0044c2b9`). | "Partie en ligne" title button (`M`): player name, then "Creer partie" (port to listen on) or "Entrer partie" (list of hosts joined before, address and port). `H`/`J` on the title, or `--host` / `--join address`. |
| Server list | None (DirectPlay enumerates sessions). | Every address tried is kept in `saves\servers.cfg` (16 at most, most recent first, labelled with the host's name once its lobby answers); Delete forgets one. The list is ready for public entries from a future lobby server (`src/core/net_server_list.h`); none exists yet. |
| Tribes | One player per tribe. | Several players may share a tribe (co-operation). |
| Pause | Refused in a network game (`FUN_004578df`, `DAT_004befe0 != 0`). | The pause zone of the options panel pauses every machine on the same turn (`GAME_COMMAND_SET_NETWORK_PAUSE`); turns keep flowing so the resume can arrive. Any player can pause or resume. |
| Save | Refused in a network game. | The Save zone, `Shift+F5` and the `F5` quicksave save a local copy of the shared session; turns go on while the Save screen is open. Loaded outside a network game, such a save continues as a solo game. |
| Load | Refused in a network game. | The host loads: `L` in the lobby, or the Load zone of the options panel during a game (guests cannot). A pick during a game sends every machine back to the lobby. The file goes to each guest (`NET_RECORD_SAVE_DATA`, 2 KB chunks); every machine applies the same bytes and acknowledges; the lobby becomes the tribe choice below; the start waits for every acknowledgement. |
| Game speed | Keys `8`/`9` (and numpad `-`/`+`) allowed only with `multispeed` in `FLOAT.CFG`; a network game starts at speed 2 (`GAMEENV +0x130`), plus catch-up ticks `DAT_004bf114`. | Always allowed; any player changes the speed for every machine on the same turn (`GAME_COMMAND_SET_NETWORK_SPEED`, 1..3 ticks per turn). A network game starts at speed 1. |
| Debug end sequence | Key `W` with the debug flag `DAT_004c2b74` sends world command 0x15. | Debug builds only (`TONE_REBELLION_DEBUG_KEYS`): `F11` in a network game sends the same command (`GAME_COMMAND_START_END_SEQUENCE`). |
| End screen cards | `ENDGNONP` cards drawn in a network game. | Same; the remake draws them from the scores taken when the screen opens. |

## Saving and loading

| Topic | Original | Remake |
|---|---|---|
| Save format | 0x80-byte header and four engine streams (`FUN_0045749a` / `FUN_004576c7`). | Same header, then a remake body: the `GameSession` field table and the raw session. A later build copies the fields by name, so a save survives added, removed, resized or renamed fields and changes of meaning ([build and validation](build-and-validation.md)). Original saves are still read. |
| Save location | Game directory. | A `saves` directory next to the executable (or `TONE_REBELLION_SAVE_DIR`); the game directory is never written. |
| Loaded game | Resumes running. | Opens paused by default, with the options panel open; the player resumes from the pause zone. The remake options can turn this off. |
| Several played tribes | No such case (one local tribe). | Loading a game where two or more tribes were played (more than the starting Hall, a building order, or a queued task) opens the New Game screen as a tribe choice: unplayed tribes drawn black and not selectable, world size and difficulty locked; NEWGAME continues as the picked tribe. |

## Keyboard and mouse

| Topic | Original | Remake |
|---|---|---|
| Escape on the island or the world map | No effect. | Opens or closes the options panel (save, load, pause, quit, music, sound). It first puts back a held building, or disarms an armed spell or order. The island returns to the map through `GOTOMAP`. |
| Intro movie | `intro.avi` (state 6, DirectShow `FUN_00449b80`) only through the title's `I` key with `nevada` in `FLOAT.CFG`; the end of playback returns to the title. | "Intro" title button (lower left) and `I` without `nevada`; the remake decodes the Cinepak video itself (`src/data/cinepak.c`). A click or a key ends it early; the title music stops for it and resumes after. Desktop only: the browser build has neither the button nor the key. |
| Remake buttons | None. | Remake-only buttons reuse the TITSCRN button art: the background and the letters are cut from the four title buttons at run time (`remake_buttons.inc`). When a language's captions need letters the originals lack (only A C D E G H I L N O P Q R T U V exist), all of that language's buttons draw their captions in the game font on the same art instead. |
| Languages | French only (texts from the data files). | The remake's own texts (options, multiplayer screens, buttons, alerts, notices, window titles, dialogs) exist in French, English, German, Italian and Spanish (`src/core/remake_text.def`). The language follows the system unless the options' Language row picks one (`video.cfg` `lang`); F2 opens the options on the title screen too. The game's own texts are not translated. |
| End screen | A click on the player card, the story text or a card leaves to the title (`SetState(0)`); nothing skips the scroll. | A click skips the text scroll and the card reveal; Escape leaves to the title and ends the game. |
| Pause key | The options panel's pause zone pauses (`FUN_004578df`); these notes record no keyboard pause key. | The keyboard `Pause` key pauses or resumes the game on the island and the world map, whatever panel is open (network games: the same shared pause as the pause zone). It cannot be bound to a shortcut. |
| Save screen | No known entry key. | `Shift+F5` on the map or the island (`F5` when quicksave is turned off). |
| Shift + right click | Not a merge shortcut. | Orders the selected floater to merge. |
| Test aids | None. | Debug builds only (CMake option `TONE_REBELLION_DEBUG_KEYS`, on for `CMAKE_BUILD_TYPE=Debug`; release builds ignore these keys): `Ctrl+F6` producer, `Ctrl+F7` remove the tribe's floaters, `Ctrl+F8` building for the next tribe, `Ctrl+F9` training building (bare keys only in e2e runs with `TONE_REBELLION_E2E_TEST_AIDS`), `F11` end screen preview (solo); `C`, `H`, `R` only with `TONE_REBELLION_E2E_STATE`. |

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
| Systems | Windows 9x, DirectX. | SDL3 build (Windows; the Win32/GDI build was dropped on 2026-11-06) and a browser build (Emscripten) whose picture fills the page at the screen's pixel density. |
| Island scrolling | Arrow keys (160 px) and the wheel (128 px) jump the view. | Smooth scrolling glides those jumps (about 160 ms); edge scrolling moves the view while the pointer is at the left or right edge of the window (900 px/s). Smooth scrolling is off by default, edge scrolling on; both are set in the remake options. |
| Keyboard shortcuts | None for the island controls. | Keys for the island buttons, the Hall commands, the building controls and the spells (defaults: M map, P panic, R realms, T tasks, G/I/K/B/D Hall pages, V move, O on/off, U upgrade, F repair, L obtain, A/S/Z/X/Q orders, 1..7 spells). A key replays a click on the control, so it does nothing when the control is not shown. Rebound in the remake options, kept in `keys.cfg`; off by default (remake options). |
| Alerts | Island messages only for the island in view. | Attacks on the tribe's units or buildings, a lost building, and Leviathan units appearing where the tribe is present are listed at the top right on other islands and the map; Space jumps to the newest one. Off by default (remake options). |
| Random island captions | The island view shows a random `gamey.txt` CRYPTIC0..20 caption from time to time (`FUN_00435f4d`). | Off by default; the remake options turn them back on (`video.cfg` `cryptic`). The Leviathan's `LEVIBRK` + `BOND<n>` caption is kept. |
| Quicksave and autosave | — | `F5` writes `quick.sav`, `F9` loads it, `Shift+F9` loads `auto.sav`, written every 2, 5 (default), 10, 15 or 30 minutes of play. Loading is solo only. Both can be turned off. |
| Repeated sound effects | A sound triggered again while it plays restarts its one DirectSound buffer (`FUN_0045afb9`, `FUN_0045b3a7`). | Overlapping sounds (default on, `video.cfg` `sfxoverlap`): each trigger plays on its own voice over the copies still playing (32 voices, the one closest to its end is replaced when all are busy). Off restarts the sound like the original. |
| Remake options | — | F2 on the island or the world map, or the left claw of the options panel (Escape), opens a panel for the remake's own settings: display rate, scaling, game speed, music, sound effects, overlapping sounds, smooth and edge scrolling, alerts, random captions, shortcuts (and their keys), quicksave, autosave, whether a loaded game starts paused, and whether the clipboard is filled with every training building (remake) or only the selected one (original). The rows sit in collapsible sections (Display, Sound, Game, Controls, Saves; `video.cfg` `optfolds`) in a list that scrolls with the wheel, the scrollbar or the arrows. Arrows or clicks change them; `video.cfg` (`loadpaused`, `clipall`) and `audio.cfg` keep them. |
| Window scaling | Fixed 640x480 display mode. | The 640x480 picture fills a window, in whole multiples with bars or filling the window, through a filter run on the GPU (OpenGL 3.3, WebGL 2 in the browser): nearest pixel, bilinear, sharp bilinear (default), bicubic (Catmull-Rom), Lanczos 3, or the pixel-art filters xBR, HQx (2x..4x by the window size) and ScaleFX, from the libretro GLSL shaders (see the [third-party notes](../README.md#third-party-code)). A filter whose shaders do not compile or whose framebuffers are refused is not offered; without OpenGL the SDL renderer shows nearest or bilinear only. F12 cycles the filters this machine can run, Ctrl+F12 the scaling; the remake options list both; `video.cfg` keeps them (`scale`, `filter`). |
| Linked unit on another island | Clicking it in IWLocInfo selects it; the island view shows only its own units. | The view opens that unit's island, centred on it, with the building kept as the location. |
| Widescreen island | The island view is the 640x320 top of the 640x480 screen; the camera never leaves the player's explored extent (`island+0x408/+0x40c`, `FUN_00435ea7`), which the IWLilMap bars hide. | Option "Island max. aspect ratio" (Display section, `video.cfg` `widescreen`: 0 = 4:3, the original and default; 2 = 16:10; 1 = 16:9; 3 = 21:9; 4 = no limit). Above 4:3, the frame is as wide as the window's shape allows up to that ratio (640..768, 854, 1120 or 2560 x 480, the island art's full width; following window resizes; whole multiples in integer scaling; a wider window gets bars) and the island view alone fills it; the lower panel and every other screen keep their 640x480 picture, centred. The scroll keeps its meaning (world x under panel x 0, view centre `+0x140`, so effect volume and pan are unchanged) and is clamped so the wider view stays in the explored extent; where that extent is narrower than the view, the view is centred on it and the rest shows only the darkened island art, without sites or units. Units and sites in the extra width can be clicked, edge scrolling uses the frame's edges, and the IWLilMap lines frame the wider view. The sides next to the lower panel hold empty boxes framed with the panel's own border (ISLETMP's right-edge profile) and take no clicks. |
| Display rate | The island and the world map are drawn once per 20 frames/s game frame, with 1 to 3 simulation ticks each (game speed), so motion steps by up to 3 ticks per picture. | The game frame still runs at 20 frames/s, but the picture is painted at 20, 40, 60 (default) or 120 Hz: units, shots, spell effects and the world-map orbits are blended between the last two game frames, one frame (50 ms) behind. 20 Hz paints as the original. Shift+F12 or the remake options change it; `video.cfg` keeps it (`fps`). The loop sleeps until the next game frame or paint is due; an optional vertical sync (OpenGL, remake options, `vsync`) makes each swap wait for the monitor. Sprite frames stay the original ones. |
| Browser data | — | The page asks for the game folder or the CD image (`.iso` or `.img`, ISO 9660 with 2048 or raw 2352-byte sectors, read by slices); files stay in the browser storage. |

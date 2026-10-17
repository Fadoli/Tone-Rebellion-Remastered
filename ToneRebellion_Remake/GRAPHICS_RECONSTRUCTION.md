# Original menu graphics reconstruction

## Evidence-backed asset path

The remake reads original assets from `C:\Program Files\Tone\TONE01.COB` in read-only mode. The new-game palette is `data\newgame.pal`; the title screen palette is `data\titscrn.pal`. The asset names and their roles are also present in the local `shapes.txt`: `NEWBACK`, `TITSCRN`, `NEWBUTT`, `GLYPHS`, `NGREALMS`, `BIGFLOAT`, and `LEVIDIFF`.

The SHP decoder follows the Ghidra decompilation of `FUN_00404770` at `0x404770` and its unclipped fast path `FUN_00404b74` at `0x404b74`. Observed frame records have an 8-byte frame-directory entry, an offset-relative frame record, signed drawing bounds, and a byte RLE stream. In the RLE stream, a zero token ends a row, an even nonzero token repeats the next palette index, an odd nonzero token copies that many literal palette indices, and token `1` skips a count from the next byte before continuing at the following token. These are observations from Ghidra's pseudocode, not recovered original source.

The 768-byte palettes contain 256 RGB triples whose observed components are in the VGA range 0–63; the renderer scales these to 8-bit RGB. The SHP transparent-run encoding supplies the alpha mask; palette index zero is not assumed to mean transparent.

## Original menu composition used by the remake

- Title art uses frame 0 of `TITSCRN` as the 640×480 background and frames 2, 4, 6, and 8 at the four button panes from `windows.txt`.
- New-game art uses `NEWBACK` frame 0, the full-screen/bottom strip `NEWBUTT` frame 0, then button frames 1, 3, 5, 7, 9, 11, 13, and 15 at the panes in `windows.txt`.
- The selected realm, difficulty illustration, and floater come from `NGREALMS`, `LEVIDIFF`, and `BIGFLOAT`. Their frame choices and placement use calls and constants observed in `FUN_0044ec5d` (`functions/0015_batch_0011.md`), with selected tribe and difficulty state substituting for live game globals.
- `GLYPHS` uses the original sheet and its 20-frame per-tribe grouping. The renderer places its four symbols at `(170,240)`, `(320,90)`, `(470,240)`, and `(320,390)`, matching the x/y address tables at `0x4a24c8` and `0x4a24d8` read by `FUN_0044ec5d`.
- The new-game background renderer draws the three dotted orbital rings found in `FUN_0044ec5d`: 8×10 rectangles around `(320,240)` at radii 150, 170, and 130. Static disassembly shows each base value `-50`, `-30`, or `-70` is offset by 200 before multiplying `sin`/`cos`; the rings use palette index 0. The original adds randomized palette specks to rings through the selected size; the remake uses stable pseudo-random specks on those same rings to avoid repaint flicker. The 20-frame glyph cycle and 17-frame floater cycle are driven by a 33 ms Win32 timer; their frame groupings and original update cadence are observed, while exact global clock phase and floater bobbing are approximated.
- Clicking Begin or pressing Enter from new-game opens a map view using `MAPBACK` frame 0 and `SMISLE`, with `MAINMAP.PAL`. Island angle/range/height/shape records come from the local `data\\worldpos.txt` member. `FUN_00471e66` selects one of three 15-frame SMISLE groups: frame base 0 for an inhabited island, 15 for an uninhabited island, and 30 for the selected homeworld. The remake initializes WORLDPOS entries 0–3 as the four homeworlds, marks the chosen tribe's homeworld with base 30, the other homeworlds with base 0, and remaining islands with base 15. This matches the shipped data layout and handler branch; dynamic ownership after starting a game is not implemented.
- `FUN_00471536` computes map positions as `x = centerX + trunc(cos(angle - phase) * range * 0.129999995 + 0.5)` and `y = centerY - trunc(sin(angle - phase) * range * 0.060000002 + z * 0.060000002 + 0.5)`. `FUN_004701ef` initializes the two scale fields and phase offset. Ghidra's recovered helper bodies at `0x477ab4` and `0x477314` stop after their calls to the floating-point loader; static disassembly of their following bytes shows `FCOS` at `0x477ad2` and `FSIN` at `0x477332`, confirming the trig operations. The code adds `0.5` then calls `__ftol`, which truncates toward zero; the remake follows both operations. It uses initial phase zero and the map center `(320,240)` from the 640×480 world pane. Bridge shimmer is not rendered yet.
- `Esc` returns from the map view to new-game setup; Left/Right changes the selected world size before or after entering the view.

## Scope and remaining fidelity work

The menu and first map view now use original art from the shipped COB. This still does not reproduce every animation phase, mouse-over frame, localized text overlay, sound cue, bridge effect, or all world/game screens. The world map transform is statically reconstructed; the selected homeworld frame variant and bridge effect still need work. A screenshot comparison against the original binary has not been performed; the original binary was not executed during this work.

The 640×480 game surface is letterboxed to preserve its 4:3 aspect ratio in the resizable remake window. Mouse coordinates are transformed through that same logical viewport, so hit testing remains aligned when the window is resized or letterboxed.

The original target identity was checked before analysis: `FLOAT.EXE` SHA-256 remains `bb229d7f09c88caf4dc1825c00b957961c22c201cf1a8dd8139bf6f4599ff28c`. It was only read for the Ghidra static analysis; no original executable or COB archive was changed.

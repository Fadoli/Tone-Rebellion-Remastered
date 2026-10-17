# Tone Rebellion remake

An independent, modern C implementation informed by the static analysis documented in the parent `FLOAT_decompilation` directory. Original game files are read-only reference data; the remake does not launch `FLOAT.EXE` or write to the original installation.

## Current milestone

The current implementation contains a portable C11 reader for the observed COB archive directory, a world-map data model/parser, an SHP RLE decoder, and a Windows menu executable. The COB API opens archives read-only, validates the fixed-width directory and member ranges, lists entries, and reads a selected member into caller-owned memory. The world parser accepts either an extracted `worldpos.txt` or `data\\worldpos.txt` directly from a COB. SDL3 is not installed in this environment, so the current desktop adapter uses built-in Win32/GDI; the core remains separate so the adapter can later be replaced by SDL3.

Build with CMake and a C11 compiler. `remake_inspect_cob <archive.cob>` lists archive entries. Run `remake_inspect_worlds <path-to-WORLDPOS.TXT>` for an extracted table, or `remake_inspect_worlds --cob <archive.cob> data\\worldpos.txt` to read the member without extracting or modifying the archive. On Windows, launch `build/remake_menu.exe`; it reads `C:\\Program Files\\Tone\\TONE01.COB` in read-only mode.

## Build status

Built successfully with CMake 4.3.2 and MinGW GCC 6.3.0, including the Windows GUI target `remake_menu.exe`. The COB lister reads 21 entries from `TONE00.COB` and 462 from `TONE01.COB`. The world parser reads `worldpos.txt` both from the local corpus and directly from `TONE01.COB`; the complete CLI output matches. Counts are `(7, 8)`, `(11, 14)`, and `(15, 22)` for worlds/islands/links. Windows created the menu window; screenshot capture could not be verified because the UI capture channel timed out twice. `FLOAT.EXE` has not been run.

## Menu prototype

The menu reads and renders original title and new-game sprites from `TONE01.COB` using the observed 6-bit palettes and the RLE structure recovered from `FUN_00404770` / `FUN_00404b74`. It uses the panes in local `windows.txt` for title and setup buttons and the new-game shape families referenced by `FUN_0044ec5d`. The setup screen animates the original glyph and floater frame families and shows the three original orbital rings; speck placement is stabilized for redraws. Begin opens a first world-map view rendered with the original `MAPBACK` and `SMISLE` art and `MAINMAP.PAL`. The map's sine/cosine projection and scale factors are reconstructed from static disassembly of the x87 helper code and `WorldWindow` constructor. Detailed evidence and remaining fidelity gaps are in [GRAPHICS_RECONSTRUCTION.md](GRAPHICS_RECONSTRUCTION.md).

The input controls remain remake behavior: choose New Game, cycle world size, select one of four tribes, cycle five difficulty levels, begin the map view, return to setup, or Exit. Keyboard: Enter advances from title to setup and setup to map, N opens setup, Escape backs out one screen, Left/Right change world size, D cycles difficulty, and 1–4 select tribes. The world-size and five-value difficulty cycles match the `FUN_00448e5a` master handler; tribe selection remains a remake interaction because its original message consumer has not been fully traced. Resume and Load are still not connected to savegame handling. The map is a visual first screen only; simulation and map interaction are not implemented. The 640×480 surface stays 4:3 when resized, and mouse hit testing uses the letterboxed viewport.

The directory layout and fixed widths come from static bytes plus the Ghidra COB loader (`FUN_0040ff5b`); C error handling, API shape, and strict validation are remake implementation choices, not recovered source. Offsets are required to increase strictly because that is true of both supplied archives. Member lookup is exact and case-sensitive. No assumptions are made about game-rule meanings beyond the format labels recorded in `FLOAT_decompilation` documentation.

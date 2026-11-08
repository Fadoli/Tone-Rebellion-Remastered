# Tone Rebellion Remastered

A remaster of *Tone Rebellion* (The Logic Factory, 1997), the real-time strategy game of floating islands, tones and the Leviathan, written in portable C11.

This is not a decompilation or a port: the original source is not available, and the code is not decompiler output. The game is rewritten by hand, with a static analysis of the original Windows executable as the reference. It tries to reproduce the original behaviour, and adds what a modern player expects: any window size, upscaling filters, smoother display, comfort options, browser play and a new network layer.

**Status:** playable from the title screen to the end of a game, but not complete. Some behaviours are not ported yet or are approximations; see the [open tasks](ToneRebellion_Remake/docs/todo.md) and the [ported features](ToneRebellion_Remake/docs/implemented.md).

Two parts live here:

- **The remaster** ([ToneRebellion_Remake/](ToneRebellion_Remake/README.md)): a new engine that loads the original game data and reproduces its rules, screens and sounds. It runs on modern Windows and in the browser.
- **The analysis workspace** ([decompilation/](decompilation/README.md)): notes, an index and decompiler pseudocode for `FLOAT.EXE` 1.16F, used as a reference. The remaster is written from these, so every ported behaviour can be traced back to its evidence.

No game data is included. You need your own copy of *Tone Rebellion*: the installed folder, the CD, or a `.iso` image.

## Play

- **Windows:** download `ToneRebellion_Remake-<version>-windows-x64.zip` from the [releases](https://github.com/Fadoli/Tone-Rebellion-Remastered/releases), unzip it and run `ToneRebellion_Remake.exe`. It finds the game in `C:\Program Files\Tone`, on a mounted CD, or as a `.iso` next to the executable. You can also drop the folder or the `.iso` onto the executable.
- **Browser:** [fadoli.github.io/Tone-Rebellion-Remastered](https://fadoli.github.io/Tone-Rebellion-Remastered/). Pick the game folder or the `.iso`; the files stay in your browser and nothing is uploaded.

## What the remake adds

The remake aims at the original behaviour, and every deliberate change can be turned off. All of them are listed in [differences from the original game](ToneRebellion_Remake/docs/differences-from-original.md).

- **Display:** any window size; GPU upscaling filters (sharp bilinear, Lanczos, xBR, HQx, ScaleFX, and others); a display rate of 20 to 120 Hz, blended between the game's 20 Hz frames; optional vsync.
- **Comfort:** smooth and edge scrolling; rebindable keyboard shortcuts for the island controls; alerts with a jump key; quicksave, quickload and autosave. Press `F2` in game to reach these settings.
- **Network:** TCP lockstep play, with pause, game speed, save and load, and reconnection. It does not use DirectPlay.
- **Saves:** loads the original saves too. Saves are written to a `saves` folder, never to the game folder.

## Build

Windows uses an MSYS2 UCRT64 shell with the `gcc`, `cmake`, `ninja` and `sdl3` packages:

```sh
cd ToneRebellion_Remake
cmake -S . -B build/ucrt64 -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build/ucrt64
ctest --test-dir build/ucrt64 --output-on-failure
```

The browser build uses Emscripten: `tools/build_web.sh <SDL3 source directory>`. For tests, e2e scripts and benchmarks, see [build and validation](ToneRebellion_Remake/docs/build-and-validation.md). Pushing a tag `v*` runs the [release workflow](.github/workflows/release.yml), which builds both versions, attaches them to a GitHub release and publishes the browser version.

## How it was made

The original `FLOAT.EXE` (x86 PE, version 1.16F) was studied statically with Ghidra through REA. It was never run or modified. The inventory covers 2,410 procedures: 1,507 decompiled bodies, 780 thunks and 123 externals ([manifest](decompilation/evidence/manifest.md), [unknowns](decompilation/unknowns.md)).

The notes keep three things apart: what Ghidra shows, what we interpret from it, and what is still unknown. Names such as `FUN_...`, and all reconstructed types, are provisional. Working rules for contributors and agents are in [AGENTS.md](AGENTS.md).

## Repository map

| Path | Content |
|---|---|
| [ToneRebellion_Remake/](ToneRebellion_Remake/README.md) | Remake: sources (`src/`), tests, shaders, tools, benchmarks |
| [ToneRebellion_Remake/docs/](ToneRebellion_Remake/docs/) | Remake docs: [ported features](ToneRebellion_Remake/docs/implemented.md), [roadmap](ToneRebellion_Remake/docs/roadmap.md), [open tasks](ToneRebellion_Remake/docs/todo.md), [movement](ToneRebellion_Remake/docs/movement/README.md), UI and rendering notes |
| [decompilation/](decompilation/README.md) | Analysis of `FLOAT.EXE`: function guide, behaviour notes (in French), pseudocode, data formats, COB archives, coverage and unknowns |

## Licence

The remake's code and the documentation are under the [MIT licence](LICENSE.md). The upscaling shaders come from libretro under their own licences; the details are in the [remake README](ToneRebellion_Remake/README.md#third-party-code). *Tone Rebellion* and its data belong to their owners and are not distributed here.

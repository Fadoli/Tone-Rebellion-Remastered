# Tone Rebellion remake

Remaster of *Tone Rebellion* (1997) in C11. It is not a decompilation or a port of the original code: the game is rewritten from a static analysis of the original executable and its data. It aims to reproduce the original game while adding new capabilities: display, comfort, browser and network play. The original executable is a read-only reference and is never run. No game data is included: the remake reads your own copy of the game.

Status: playable, but not complete. What is ported and its limits: [ported features](docs/implemented.md); what remains: [open tasks](docs/todo.md); deliberate changes: [differences from the original game](docs/differences-from-original.md).

## Play

- **Windows:** download `ToneRebellion_Remake-<version>-windows-x64.zip` from the [releases](https://github.com/Fadoli/Tone-Rebellion-Remastered/releases), unzip it and run `ToneRebellion_Remake.exe`. It finds the game in `C:\Program Files\Tone`, on a mounted CD, or as a `.iso` or `.img` placed next to the executable; you can also drop the game folder or the `.iso`/`.img` onto the executable, or pass `--game-dir <folder>` / `--iso <file>`.
- **Browser:** [fadoli.github.io/Tone-Rebellion-Remastered](https://fadoli.github.io/Tone-Rebellion-Remastered/) asks for the game folder or the CD image (`.iso` or `.img`); the files stay in the browser's storage, nothing is uploaded.

Remake keys on the island and the world map: `F2` remake options (display rate, scaling filter, scrolling, alerts, shortcuts and their keys, saves), `Esc` options panel, `F5` quicksave, `F9` quickload, `Shift+F9` autosave, `Space` jump to the newest alert, `8`/`9` game speed, `F12` scaling filter. Everything the remake changes on purpose is listed in [differences from the original game](docs/differences-from-original.md).

## Build and check

Windows, from an MSYS2 UCRT64 shell (packages `mingw-w64-ucrt-x86_64-gcc`, `-cmake`, `-ninja`, `-sdl3`):

```sh
cmake -S . -B build/ucrt64 -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build/ucrt64
ctest --test-dir build/ucrt64 --output-on-failure
```

The build refreshes `ToneRebellion_Remake.exe`, `SDL3.dll` and `libiconv-2.dll` beside this file. The browser build is `tools/build_web.sh <SDL3 source directory>` (Emscripten; output in `web/out/`). Details, the e2e scripts and the benchmarks: [build and validation](docs/build-and-validation.md), [bench/](bench/).

## Releases

Pushing a tag `v*` runs [`.github/workflows/release.yml`](../.github/workflows/release.yml): it builds and tests the Windows game, builds the web version, attaches both zips to a GitHub release and publishes the web version to GitHub Pages ("Run workflow" does the builds and the Pages deployment without a release).

```sh
git tag v0.1.2
git push origin v0.1.2
```

Every player-facing change goes into [CHANGELOG.md](CHANGELOG.md) under the next version (`## <version> - unreleased`); before tagging, date that section. The release text is the install notes plus that section.

## Documentation

- [Menu, map, and island UI](docs/menu-and-island-ui.md)
- [World start and initial simulation](docs/world-start.md)
- [Building rendering](docs/building-rendering.md)
- [Graphics notes by screen](docs/graphics-reconstruction.md)
- [Roadmap](docs/roadmap.md) and [open tasks](docs/todo.md)
- [Ported features and limits](docs/implemented.md)
- [Differences from the original game](docs/differences-from-original.md)
- [Movement traces](docs/movement/README.md)
- [Original behavior and evidence](../decompilation/FUNCTION_GUIDE.md)

## Third-party code

The upscaling filters run on the GPU with libretro GLSL shaders, copied under `shaders/libretro/` with their notices and embedded by `tools/embed_shaders.py` into `src/platform/sdl/sdl_gl_shaders.h`:

- `xbr/`: xBR level 2 (Hyllian), MIT. `xbr-lv2.glsl` is modified: three global initializers became macros for GLSL ES (marked in the file).
- `hqx/`: hq2x/hq3x/hq4x (Maxim Stepin, Cameron Zemek, Jules Blok), LGPL-2.1-or-later, with their lookup images.
- `scalefx/`: ScaleFX (Sp00kyFox), MIT.
- `cubic/catmull-rom.glsl`: MIT; `interpolation/sharp-bilinear.glsl`: public domain.

`shaders/remake/` (nearest/linear copy, Lanczos 3) is the remake's own. The HQx shaders are LGPL: distributing a build requires offering their source (this repository). SDL3 (zlib licence) is linked dynamically on Windows and statically in the browser build.

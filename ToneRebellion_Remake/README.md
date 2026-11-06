# Tone Rebellion remake

Independent C11 remake informed by static analysis and local game data. The original executable is a read-only reference and is not run.

## Build and check

```powershell
cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release
cmake --build build/release --parallel 4
ctest --test-dir build/release --output-on-failure
```

Windows executable beside this file: `ToneRebellion_Remake.exe` (SDL3 build) with `SDL3.dll` and `libiconv-2.dll`; SDL3 is required (the Win32/GDI build was dropped on 2026-11-06). See [build and validation details](docs/build-and-validation.md).

## Documentation

- [Menu, map, and island UI](docs/menu-and-island-ui.md)
- [World start and initial simulation](docs/world-start.md)
- [Building rendering](docs/building-rendering.md)
- [Graphics notes by screen](GRAPHICS_RECONSTRUCTION.md)
- [Roadmap](ROADMAP.md) and [open tasks](TODO.md)
- [Ported features and limits](docs/implemented.md)
- [Differences from the original game](docs/differences-from-original.md) (network pause, save and load, Escape shortcut, end screen, saves)
- [Movement traces](MOVEMENT_REVERSE_ENGINEERING.md)
- [Original behavior and evidence](../FUNCTION_GUIDE.md)

## Third-party code

The upscaling filters run on the GPU with libretro GLSL shaders, copied under `shaders/libretro/` with their notices and embedded by `tools/embed_shaders.py` into `src/platform/sdl/sdl_gl_shaders.h`:

- `xbr/`: xBR level 2 (Hyllian), MIT. `xbr-lv2.glsl` is modified: three global initializers became macros for GLSL ES (marked in the file).
- `hqx/`: hq2x/hq3x/hq4x (Maxim Stepin, Cameron Zemek, Jules Blok), LGPL-2.1-or-later, with their lookup images.
- `scalefx/`: ScaleFX (Sp00kyFox), MIT.
- `cubic/catmull-rom.glsl`: MIT; `interpolation/sharp-bilinear.glsl`: public domain.

`shaders/remake/` (nearest/linear copy, Lanczos 3) is the remake's own. The HQx shaders are LGPL: distributing a build requires offering their source (this repository).

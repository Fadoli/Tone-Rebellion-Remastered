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

The upscaling filters include ports of third-party code, each file keeping its notice:

- `src/render/upscale_xbr.c`: xBR (Hyllian), adapted from FFmpeg `libavfilter/vf_xbr.c`, LGPL-2.1-or-later.
- `src/render/upscale_hqx.c`: hq2x/hq3x/hq4x (Maxim Stepin), adapted from grom358/hqx, LGPL-2.1-or-later.
- `src/render/upscale_scalefx.c`: ScaleFX (Sp00kyFox), from the libretro slang-shaders preset, MIT.

The two LGPL files are linked statically into the executable; distributing a build therefore requires offering their source (this repository) so they can be relinked.


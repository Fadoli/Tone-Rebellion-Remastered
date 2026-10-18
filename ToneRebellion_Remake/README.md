# Tone Rebellion remake

Independent C11 remake informed by static analysis and local game data. The original executable is a read-only reference and is not run.

## Build and check

```powershell
cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release
cmake --build build/release --parallel 4
ctest --test-dir build/release --output-on-failure
```

Windows executable: `ToneRebellion_Remake.exe` beside this file. See [build and validation details](docs/build-and-validation.md).

## Documentation

- [Menu, map, and island UI](docs/menu-and-island-ui.md)
- [World start and initial simulation](docs/world-start.md)
- [Building rendering](docs/building-rendering.md)
- [Graphics notes by screen](GRAPHICS_RECONSTRUCTION.md)
- [Open tasks](TODO.md)
- [Ported features and limits](docs/implemented.md)
- [Movement traces](MOVEMENT_REVERSE_ENGINEERING.md)
- [Original behavior and evidence](../FUNCTION_GUIDE.md)

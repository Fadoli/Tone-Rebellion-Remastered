# Remake agent instructions

- Implement the remake in portable modern C; the current project target is C11.
- Keep core game rules independent from windowing, rendering, audio, and operating-system APIs.
- Use SDL3 for the platform adapter when the renderer/input layer is added; do not put SDL headers or types in `src/core`.
- Treat `C:\Program Files\Tone\FLOAT.EXE`, `TONE00.COB`, `TONE01.COB`, and any existing Ghidra project as immutable. Never execute the original game.
- Use `C:\git\ToneRebellion_Raw\original_content` as the local reference corpus. The user asked to avoid GitHub; do not use GitHub or download the corpus again.
- Ground behavior claims in the Ghidra evidence and/or local data files; label interpretations and unknowns separately.
- Preserve original record ordering and IDs when loading game data. Reject malformed inputs with explicit errors.
- Do not claim gameplay parity from parser checks. Compare the remake with independently supplied runtime captures if they become available.
- Keep build output under `build/`; do not add generated binaries or CMake state to source documentation.

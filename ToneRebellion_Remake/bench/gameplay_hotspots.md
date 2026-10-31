# Gameplay frame cost and hotspots

## Harness

`ToneRebellion_Remake.exe --bench` (`src/platform/win32/menu_app_sections/bench.inc`)
starts a fixed session (world 0, tribe 0, difficulty 0, constant seed), opens
the start island, runs `--bench-warmup` simulation ticks (300), then
`--bench-frames` frames (600) back to back: `run_ui_frame` (sim), the back
buffer composition (`render_back_buffer`) and the window present
(`present_back_buffer`, split out of `paint_window`). Music is stopped; sound
effects still play. Report: `bench_report.txt` next to the executable, or
`--bench-out FILE`. Neither the resume save nor any other save is written.

Scenarios (`--bench-scenario`), the "fake environment":

- `idle`: the plain start (16 floaters).
- `crowd`: the player's idle starting workers copied onto the island up to 96
  (108 floaters).
- `battle`: `crowd` plus 24 workers of each other tribe on the same island
  (180 floaters).

`--bench-paced` waits for the game's 50 ms frame clock instead of running
flat out. `--bench-screen title|newgame|map` measures another screen over
the same session; `--bench-dump FILE` writes the last composed frame as a
640x480 BMP (used to compare renderers pixel for pixel). `--bench-profile` adds a sampling profiler: a thread suspends the
main thread about every 2 ms and stores its EBP-chain call stack. Use a build
with frame pointers and less inlining, then resolve the samples:

```
cmake -S . -B build/bench -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF "-DCMAKE_C_FLAGS_RELEASE=-O2 -DNDEBUG -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-inline-functions -fno-inline-small-functions -fno-inline-functions-called-once"
cmake --build build/bench --target remake_menu
build/bench/remake_menu.exe --bench --bench-profile --bench-scenario battle --bench-frames 2000 --bench-out prof.txt
nm -n build/bench/remake_menu.exe > syms.txt
node bench/hotspots.js prof.txt syms.txt [all|sim|render|present] [top]
```

The `build/bench` post-build step also copies its executable over the root
`ToneRebellion_Remake.exe`; rebuild `build` (or copy `build/remake_menu.exe`)
afterwards.

## Before (2026-10-31, Ryzen 5 5600X, 1024x781 client, `-O3` build)

| scenario | frame ms (mean) | sim | render | present | one core at 20 fps |
|---|---|---|---|---|---|
| idle | 6.34 | 0.06 | 1.13 | 5.14 | 12.2 % |
| crowd | 9.13 | 0.03 | 3.86 | 5.25 | 18.2 % |
| battle | 11.4 | 0.04 | 6.1 | 5.3 | 23 % |

Task Manager divides by 12 logical CPUs, so this showed as 1-2 % for the
process. The simulation was negligible (under 1 % of the samples); nearly all
of the time was in GDI system calls:

- Present, 46 % of battle samples: `StretchBlt` in `HALFTONE` mode filters
  640x480 up to the client size on the CPU, about 5.2 ms per frame.
- Sprite blits, about 40 %: each `draw_sprite*` cost `SelectObject` +
  `AlphaBlend` (+ `GetObject` and a temporary DIB when scaled or hazed).
- Mini-map dots, 13 %: a brush, `FillRect` and `DeleteObject` per dot.

## Changes

- `present_back_buffer` scales with `COLORONCOLOR` (nearest pixel) instead
  of `HALFTONE`: the enlarged frame is sharp instead of smoothed.
- `soft_blit_frame` / `soft_fill_rect` (`sprite_primitives.inc`) write the
  back buffer DIB directly for `draw_sprite`, `draw_sprite_region`,
  `draw_sprite_scaled[_plain]`, `fill_rect` and `lilmap_fill`, with the same
  premultiplied source-over and nearest sampling as the GDI path. Frame bits
  are cached per bitmap in `SpriteFrame`. The back buffer clip is mirrored
  from `SaveDC`/`RestoreDC`/`IntersectClipRect` wrappers (`menu_app.c`); a
  region clip (feature reveal stipples) keeps the GDI path.
- `GdiSetBatchLimit(1)` at startup: `GdiFlush` is a system call even with an
  empty batch, and one per sprite cost 59 % of the samples in a first version.
- Per-column source table and 32-bit division in the scaled blit (a 64-bit
  division per pixel), mini-map slot colours resolved once per island palette instead
  of a 256-entry palette search per dot pixel.

Every `--bench-dump` frame (idle, crowd and battle island, world map, title,
new game) is identical, alpha included, to a build with the software path
disabled.

## After

| scenario | frame ms (mean) | sim | render | present | one core at 20 fps |
|---|---|---|---|---|---|
| idle | 0.79 | 0.04 | 0.58 | 0.16 | 1.6 % |
| crowd | 0.92 | 0.03 | 0.72 | 0.17 | 1.8 % |
| battle | 1.05 | 0.04 | 0.84 | 0.17 | 2.1 % |

Remaining battle samples: `soft_blit_frame` 52 % (pixel work), `StretchBlt`
15 %, `soft_fill_rect` 9 % (mostly the full-screen black fill under the
island background and template), `SaveDC`/`RestoreDC` 6 %. The first idle
frame still spends about 17 ms in `waveOutOpen` (first sound effect).

Not done: dropping the full-screen `fill_rect` needs checking that the
background and template frames have no transparent pixels.

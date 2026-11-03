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
flat out. `--bench-screen title|newgame|map|load` measures another screen over
the same session; `--bench-client WxH` sets the window client size;
`--bench-dump FILE` writes the last composed frame as a
640x480 BMP (used to compare renderers pixel for pixel); `--bench-dump-set DIR`
writes the 34 parity frames as `DIR/NAME.bmp` from one hidden process; `--bench-panel N`
(island panel mode) and `--bench-construct` (IWConstruct open, first column
hovered) fix more UI for those dumps. `--bench-profile` adds a sampling profiler: a thread suspends the
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
  of `HALFTONE`. A non-integer nearest scale gives uneven pixel sizes (the
  mini-map dots show it): F12 or the window menu switches between fill
  sharp (default), whole multiples of 640x480 with black bars, and fill
  smoothed (`HALFTONE`) (`logical_viewport`, `savesideo.cfg`).
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

## RenderSurface (2026-10-31)

Step 1 of the Web port ([ROADMAP.md](../ROADMAP.md)): every renderer draws into a
`RenderSurface` (`src/render/render_surface.c`); sprite frames are plain
pixel arrays and the region clips of the stipple reveals are per-pixel
masks. GDI only presents the back buffer.

Parity: 38 `--bench-dump` frames (idle, crowd, battle at warmup 40, 300 and
1500; panels 1..7; IWConstruct; title, new game, map, load) are byte
identical to the previous build. Those states never reach the mask clip or
the site shimmer, so a scratch harness (not kept) also compared
`RenderSurface` with GDI on a 32-bit DIB: 20 000 random cases of clip
rectangle plus optional `ExtSelectClipRgn` mask with `AlphaBlend` (plain and
nearest-prescaled), `FillRect`, `FrameRect`, `Rectangle` (pen, null brush),
`SetPixel` and `SetPixel(GetPixel)` gave no difference.
Notes from it: GDI fills and pixels store alpha 0; `GetPixel` outside the
clip returns `CLR_INVALID`, which `SetPixel` writes as black.

Same machine, 1024x781 client, 2000 frames, mean ms:

| scenario | frame before | frame after | render before | render after |
|---|---|---|---|---|
| idle | 0.73 | 0.63 | 0.53 | 0.42 |
| crowd | 0.79 | 0.68 | 0.60 | 0.48 |
| battle | 0.89 | 0.77 | 0.70 | 0.57 |

Tried and dropped: a first version with one blend loop (mask and transform
tested per pixel) and a 16 KB column table on the stack rendered battle in
0.77 ms, slower than before. The kept blit copies unscaled spans without a
table, splits the plain loop from the masked/transformed one, and keeps the
table at 2 KB (no stack probe).

## SDL3 shell and 64-bit build (2026-10-31)

`remake_sdl` (MSYS2 UCRT64, GCC 16.2, SDL3 3.4.18, 64-bit) renders the
same `RenderSurface` and presents it through a streaming texture. The 34
`--bench-dump-set` frames are byte identical across the 32-bit MinGW.org
build, the 64-bit Win32 build and `remake_sdl`.

Two 32/64-bit differences came up first, both fixed:

- Load screen: the original game's saves sit in the UAC VirtualStore
  (`%LOCALAPPDATA%VirtualStoreProgram FilesTone`). Windows redirects
  reads there only for 32-bit processes without a manifest; the slot scan
  now looks there itself.
- New-game orbit dots: 32-bit x87 kept `angle` in extended precision, so
  `(int)(cos(angle) * 150)` gave 75 instead of 74 at some steps (one pixel).
  `-fexcess-precision=standard` did not change GCC 6.3's result;
  `-msse2 -mfpmath=sse` on 32-bit GCC builds did.

Battle, 1024x781 client, mean ms (one run each):

| shell | frames | frame | render | present |
|---|---|---|---|---|
| Win32 64-bit | 2000 flat out | 0.90 | 0.53 | 0.31 |
| SDL3 | 2000 flat out | 2.56 | 0.63 | 1.87 (p95 frame 11.6) |
| SDL3 | 200 at 20 Hz | 1.51 | 0.77 | 0.67 |

Flat out, `SDL_RenderPresent` stalls on the GPU queue; at the game's 20 Hz
the SDL shell costs 3.0 % of a core against about 1.8 % for GDI. Untried:
rendering straight into `SDL_LockTexture` memory to skip the 1.2 MB upload
copy.

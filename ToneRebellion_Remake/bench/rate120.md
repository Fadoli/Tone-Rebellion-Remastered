# Frame cost at a 120 Hz display rate (2026-11-06)

The first two tables are the polled loop; the last section is after the pacing fix.

## Harness

`ToneRebellion_Remake.exe --bench --bench-rate 120` (`src/platform/win32/menu_app_sections/bench.inc`,
`bench_rate_run`) runs the real loop for `--bench-seconds` (8 here): the 20 Hz game frame
(`run_ui_frame`, simulation) whenever the frame clock is due, and a paint (`render_back_buffer`,
the 640x480 software composition with the positions blended by `render_interp.inc`, then
`sdl_present`, the OpenGL filter passes and `SDL_GL_SwapWindow`) on every game frame and whenever
the paint clock is due in between, polled at twice the rate as `SDL_AppIterate` does.
`--bench-filter N` picks the filter, `--bench-client WxH` the window size, `--bench-gpu-sync`
adds `glFinish` after each present, so "present" then includes the GPU's work.
`process_cpu_pct_of_one_core` is `GetProcessTimes` over the wall time (every thread: main loop,
SDL audio, the GL driver).

`node bench/rate120.js [seconds] [rate] [--gpu-sync]` runs the matrix below (scenarios
`idle` 16 floaters and `battle` 180 floaters, six filters, two window sizes) with saves and
settings in a temporary folder, and prints the tables.

Machine: Ryzen 5 5600X, Radeon RX 6800, Windows 10, 1920x1080 desktop; `-O2` UCRT64 build.

## Results

Rate 120 Hz, 8 s per run.

| client | scenario | filter | paints/s | game frames/s | CPU % of one core | sim ms (mean) | render ms (mean / p95) | present ms (mean / p95) | paint interval ms (p95 / max) |
|---|---|---|---|---|---|---|---|---|---|
| 1280x960 | idle | nearest | 119.70 | 19.99 | 14.45 | 0.02 | 0.35 / 0.45 | 0.18 / 0.39 | 9.27 / 17.75 |
| 1280x960 | idle | sharp bilinear | 119.84 | 19.99 | 12.50 | 0.02 | 0.34 / 0.41 | 0.17 / 0.39 | 9.29 / 17.80 |
| 1280x960 | idle | Lanczos 3 | 119.86 | 20.00 | 14.84 | 0.02 | 0.36 / 0.45 | 0.18 / 0.40 | 9.27 / 18.65 |
| 1280x960 | idle | xBR | 119.87 | 20.00 | 12.69 | 0.02 | 0.35 / 0.44 | 0.18 / 0.42 | 9.26 / 19.36 |
| 1280x960 | idle | HQx | 119.85 | 20.00 | 15.23 | 0.02 | 0.34 / 0.41 | 0.18 / 0.39 | 9.22 / 19.52 |
| 1280x960 | idle | ScaleFX | 119.57 | 19.99 | 12.49 | 0.02 | 0.34 / 0.40 | 0.20 / 0.42 | 9.23 / 22.54 |
| 1280x960 | battle | nearest | 119.72 | 19.99 | 12.50 | 0.03 | 0.50 / 0.58 | 0.17 / 0.37 | 9.48 / 18.46 |
| 1280x960 | battle | sharp bilinear | 119.84 | 19.99 | 12.89 | 0.03 | 0.49 / 0.56 | 0.16 / 0.36 | 9.36 / 16.32 |
| 1280x960 | battle | Lanczos 3 | 119.57 | 19.99 | 14.84 | 0.03 | 0.50 / 0.58 | 0.17 / 0.39 | 9.61 / 18.33 |
| 1280x960 | battle | xBR | 119.45 | 19.99 | 14.06 | 0.03 | 0.50 / 0.60 | 0.17 / 0.38 | 9.39 / 18.13 |
| 1280x960 | battle | HQx | 119.34 | 19.99 | 16.21 | 0.03 | 0.52 / 0.64 | 0.19 / 0.41 | 9.49 / 19.42 |
| 1280x960 | battle | ScaleFX | 119.35 | 20.00 | 14.84 | 0.03 | 0.49 / 0.56 | 0.19 / 0.40 | 9.40 / 23.45 |
| 1024x768 | idle | nearest | 119.87 | 20.00 | 15.04 | 0.02 | 0.34 / 0.40 | 0.17 / 0.39 | 9.22 / 16.70 |
| 1024x768 | idle | sharp bilinear | 119.99 | 20.00 | 19.33 | 0.02 | 0.34 / 0.40 | 0.17 / 0.40 | 9.27 / 16.37 |
| 1024x768 | idle | Lanczos 3 | 119.82 | 19.99 | 17.18 | 0.02 | 0.35 / 0.40 | 0.17 / 0.40 | 9.21 / 17.57 |
| 1024x768 | idle | xBR | 119.82 | 19.99 | 12.88 | 0.02 | 0.35 / 0.41 | 0.17 / 0.42 | 9.33 / 15.77 |
| 1024x768 | idle | HQx | 119.86 | 20.00 | 16.79 | 0.02 | 0.35 / 0.42 | 0.18 / 0.43 | 9.27 / 16.97 |
| 1024x768 | idle | ScaleFX | 119.72 | 20.00 | 13.28 | 0.02 | 0.36 / 0.47 | 0.20 / 0.46 | 9.33 / 22.42 |
| 1024x768 | battle | nearest | 119.61 | 20.00 | 16.99 | 0.03 | 0.49 / 0.56 | 0.17 / 0.35 | 9.38 / 16.86 |
| 1024x768 | battle | sharp bilinear | 119.62 | 20.00 | 17.19 | 0.03 | 0.49 / 0.58 | 0.17 / 0.37 | 9.41 / 16.04 |
| 1024x768 | battle | Lanczos 3 | 119.73 | 20.00 | 13.87 | 0.03 | 0.49 / 0.56 | 0.17 / 0.36 | 9.41 / 17.46 |
| 1024x768 | battle | xBR | 119.32 | 19.99 | 14.45 | 0.03 | 0.49 / 0.57 | 0.19 / 0.36 | 9.40 / 30.10 |
| 1024x768 | battle | HQx | 118.81 | 19.99 | 17.57 | 0.03 | 0.49 / 0.57 | 0.19 / 0.36 | 9.49 / 17.30 |
| 1024x768 | battle | ScaleFX | 119.31 | 19.99 | 11.52 | 0.03 | 0.50 / 0.57 | 0.19 / 0.37 | 9.36 / 19.95 |

Rate 120 Hz, 8 s per run, glFinish after each present.

| client | scenario | filter | paints/s | game frames/s | CPU % of one core | sim ms (mean) | render ms (mean / p95) | present ms (mean / p95) | paint interval ms (p95 / max) |
|---|---|---|---|---|---|---|---|---|---|
| 1280x960 | idle | nearest | 119.70 | 19.99 | 13.86 | 0.02 | 0.36 / 0.48 | 0.59 / 0.81 | 9.66 / 18.41 |
| 1280x960 | idle | sharp bilinear | 119.98 | 20.00 | 14.84 | 0.02 | 0.34 / 0.40 | 0.56 / 0.77 | 9.48 / 16.26 |
| 1280x960 | idle | Lanczos 3 | 116.70 | 19.99 | 15.81 | 0.02 | 0.34 / 0.40 | 1.23 / 1.50 | 10.19 / 17.55 |
| 1280x960 | idle | xBR | 119.83 | 19.99 | 22.84 | 0.02 | 0.34 / 0.40 | 0.90 / 1.14 | 9.86 / 17.96 |
| 1280x960 | idle | HQx | 119.81 | 19.99 | 21.86 | 0.02 | 0.34 / 0.41 | 0.72 / 0.96 | 9.68 / 17.98 |
| 1280x960 | idle | ScaleFX | 118.23 | 20.00 | 10.74 | 0.02 | 0.34 / 0.41 | 1.14 / 1.40 | 10.07 / 22.47 |
| 1280x960 | battle | nearest | 119.96 | 19.99 | 22.26 | 0.03 | 0.49 / 0.56 | 0.55 / 0.76 | 9.63 / 16.10 |
| 1280x960 | battle | sharp bilinear | 119.71 | 19.99 | 21.67 | 0.03 | 0.53 / 0.74 | 0.59 / 0.83 | 9.91 / 17.59 |
| 1280x960 | battle | Lanczos 3 | 118.84 | 19.99 | 18.16 | 0.03 | 0.49 / 0.57 | 1.22 / 1.46 | 10.30 / 18.21 |
| 1280x960 | battle | xBR | 119.69 | 19.99 | 19.72 | 0.03 | 0.49 / 0.58 | 0.90 / 1.13 | 10.04 / 18.78 |
| 1280x960 | battle | HQx | 119.73 | 20.00 | 18.36 | 0.03 | 0.49 / 0.57 | 0.73 / 0.96 | 9.81 / 19.26 |
| 1280x960 | battle | ScaleFX | 117.45 | 19.99 | 19.52 | 0.03 | 0.49 / 0.56 | 1.14 / 1.41 | 10.21 / 23.15 |
| 1024x768 | idle | nearest | 119.74 | 20.00 | 13.28 | 0.02 | 0.34 / 0.40 | 0.53 / 0.75 | 9.49 / 16.69 |
| 1024x768 | idle | sharp bilinear | 119.59 | 19.99 | 13.08 | 0.02 | 0.33 / 0.39 | 0.54 / 0.77 | 9.47 / 16.78 |
| 1024x768 | idle | Lanczos 3 | 119.71 | 19.99 | 8.79 | 0.02 | 0.36 / 0.52 | 1.00 / 1.27 | 10.05 / 17.42 |
| 1024x768 | idle | xBR | 119.82 | 19.99 | 16.20 | 0.02 | 0.34 / 0.39 | 0.76 / 1.00 | 9.72 / 17.44 |
| 1024x768 | idle | HQx | 119.96 | 19.99 | 15.23 | 0.02 | 0.34 / 0.40 | 0.69 / 0.92 | 9.63 / 16.55 |
| 1024x768 | idle | ScaleFX | 118.56 | 19.99 | 15.62 | 0.02 | 0.34 / 0.39 | 1.11 / 1.32 | 10.03 / 21.93 |
| 1024x768 | battle | nearest | 119.94 | 19.99 | 18.35 | 0.03 | 0.49 / 0.57 | 0.54 / 0.76 | 9.64 / 15.88 |
| 1024x768 | battle | sharp bilinear | 119.82 | 19.99 | 13.28 | 0.03 | 0.48 / 0.56 | 0.54 / 0.74 | 9.66 / 16.90 |
| 1024x768 | battle | Lanczos 3 | 118.60 | 20.00 | 12.30 | 0.03 | 0.48 / 0.57 | 0.96 / 1.16 | 10.04 / 17.46 |
| 1024x768 | battle | xBR | 119.83 | 19.99 | 20.31 | 0.03 | 0.53 / 0.78 | 0.77 / 1.01 | 10.02 / 16.34 |
| 1024x768 | battle | HQx | 119.83 | 19.99 | 15.62 | 0.03 | 0.48 / 0.56 | 0.70 / 0.91 | 9.79 / 16.96 |
| 1024x768 | battle | ScaleFX | 117.22 | 20.00 | 15.04 | 0.03 | 0.50 / 0.57 | 1.11 / 1.34 | 10.21 / 20.41 |

## Findings

- Every case holds the 120 Hz target (117-120 paints/s) with the game frame at 20/s.
- CPU per paint is about 0.5-0.7 ms on the main thread: composition 0.35 ms (idle) to 0.50 ms
  (battle), submit and swap about 0.2 ms. The simulation is negligible (0.02-0.03 ms per game
  frame). The process uses 11-23 % of one core; the spread between runs of the same work is
  mostly the polling loop, the audio thread and the driver, not the filters.
- GPU time per paint (with `glFinish`, minus the unsynced present): nearest and sharp bilinear
  about 0.4 ms, HQx 0.5 ms, xBR 0.6-0.7 ms, Lanczos 3 and ScaleFX 0.8-1.0 ms. Lanczos 3 (our
  36-tap one-pass shader) costs as much as ScaleFX's five passes; a separable two-pass version
  would cut it.
- Pacing is the weak point, not cost: the paint interval should be 8.33 ms but its p95 is
  9.2-9.6 ms and isolated intervals reach 16-30 ms. Paints are checked on a 4.2 ms poll
  (`SDL_HINT_MAIN_CALLBACK_RATE` 240), so each one can land up to one poll late, and the swap
  has no vsync (`SDL_GL_SetSwapInterval(0)`), so a late paint can also tear. Sleeping until the
  next due paint (and an optional vsync matched to the monitor) would even this out.

## After the pacing fix

`ui_wait_for_next_deadline` (`window_proc.inc`) now sleeps (`SDL_DelayPrecise`) until the
earliest deadline: the next game frame, the next paint while blending, or at once while the view
glides, at most 2 ms so input and network keep flowing; SDL only caps the loop at 1000
iterations/s. The bench loop uses the same function. A vsync setting (remake options,
`video.cfg` `vsync`) can also make the swap wait for the monitor; off by default and not
measured here.

Rate 120 Hz, 6 s per run.

| client | scenario | filter | paints/s | game frames/s | CPU % of one core | sim ms (mean) | render ms (mean / p95) | present ms (mean / p95) | paint interval ms (p95 / max) |
|---|---|---|---|---|---|---|---|---|---|
| 1280x960 | idle | nearest | 120.15 | 20.16 | 9.63 | 0.03 | 0.40 / 0.67 | 0.20 / 0.43 | 8.99 / 13.93 |
| 1280x960 | idle | sharp bilinear | 120.16 | 20.16 | 4.69 | 0.02 | 0.36 / 0.41 | 0.19 / 0.42 | 8.95 / 14.37 |
| 1280x960 | idle | Lanczos 3 | 120.15 | 20.16 | 5.99 | 0.02 | 0.36 / 0.42 | 0.19 / 0.42 | 8.91 / 14.63 |
| 1280x960 | idle | xBR | 120.15 | 20.16 | 5.99 | 0.02 | 0.36 / 0.41 | 0.19 / 0.43 | 8.98 / 14.16 |
| 1280x960 | idle | HQx | 120.16 | 20.16 | 9.89 | 0.02 | 0.35 / 0.40 | 0.20 / 0.47 | 8.97 / 13.65 |
| 1280x960 | idle | ScaleFX | 119.99 | 20.16 | 8.33 | 0.02 | 0.36 / 0.42 | 0.21 / 0.44 | 8.97 / 19.37 |
| 1280x960 | battle | nearest | 120.14 | 20.16 | 7.81 | 0.03 | 0.51 / 0.58 | 0.18 / 0.41 | 9.01 / 13.96 |
| 1280x960 | battle | sharp bilinear | 120.15 | 20.16 | 5.99 | 0.03 | 0.52 / 0.59 | 0.18 / 0.41 | 9.02 / 14.08 |
| 1280x960 | battle | Lanczos 3 | 120.14 | 20.16 | 9.89 | 0.03 | 0.51 / 0.58 | 0.19 / 0.43 | 9.00 / 13.41 |
| 1280x960 | battle | xBR | 120.14 | 20.16 | 9.37 | 0.03 | 0.56 / 0.79 | 0.22 / 0.44 | 9.01 / 14.02 |
| 1280x960 | battle | HQx | 120.15 | 20.16 | 11.20 | 0.03 | 0.52 / 0.59 | 0.21 / 0.42 | 9.01 / 14.15 |
| 1280x960 | battle | ScaleFX | 119.97 | 20.16 | 15.62 | 0.03 | 0.51 / 0.58 | 0.21 / 0.44 | 9.01 / 18.38 |
| 1024x768 | idle | nearest | 120.14 | 20.16 | 7.81 | 0.02 | 0.36 / 0.40 | 0.20 / 0.44 | 8.98 / 12.21 |
| 1024x768 | idle | sharp bilinear | 120.15 | 20.16 | 8.59 | 0.02 | 0.36 / 0.41 | 0.18 / 0.42 | 8.98 / 12.34 |
| 1024x768 | idle | Lanczos 3 | 120.15 | 20.16 | 6.77 | 0.02 | 0.35 / 0.41 | 0.19 / 0.43 | 8.91 / 13.50 |
| 1024x768 | idle | xBR | 120.14 | 20.16 | 8.59 | 0.02 | 0.36 / 0.42 | 0.18 / 0.42 | 8.96 / 12.82 |
| 1024x768 | idle | HQx | 120.15 | 20.16 | 9.11 | 0.02 | 0.35 / 0.42 | 0.21 / 0.44 | 9.01 / 12.29 |
| 1024x768 | idle | ScaleFX | 119.99 | 20.16 | 8.33 | 0.02 | 0.36 / 0.42 | 0.21 / 0.44 | 8.95 / 17.42 |
| 1024x768 | battle | nearest | 120.15 | 20.16 | 12.50 | 0.04 | 0.55 / 0.89 | 0.19 / 0.43 | 9.00 / 11.92 |
| 1024x768 | battle | sharp bilinear | 120.15 | 20.16 | 13.28 | 0.03 | 0.51 / 0.58 | 0.19 / 0.42 | 9.02 / 12.26 |
| 1024x768 | battle | Lanczos 3 | 120.15 | 20.16 | 11.98 | 0.03 | 0.53 / 0.60 | 0.18 / 0.42 | 9.02 / 13.32 |
| 1024x768 | battle | xBR | 120.14 | 20.16 | 9.63 | 0.03 | 0.51 / 0.57 | 0.18 / 0.41 | 9.01 / 11.87 |
| 1024x768 | battle | HQx | 120.15 | 20.16 | 7.29 | 0.03 | 0.52 / 0.57 | 0.20 / 0.43 | 9.00 / 13.30 |
| 1024x768 | battle | ScaleFX | 119.99 | 20.16 | 9.11 | 0.03 | 0.52 / 0.59 | 0.20 / 0.43 | 9.02 / 17.47 |

- Every case is at 120 paints/s; the paint interval p95 went from 9.2-9.6 ms to about 9.0 ms
  (mean 8.33 ms) and the worst gap from 16-30 ms to 12-19 ms.
- CPU fell to about 5-13 % of one core (the loop sleeps instead of polling at 240/s).
- What is left: about 0.7 ms of jitter around 8.33 ms, and rare 12-19 ms gaps (largest with
  ScaleFX, the heaviest GPU filter), outside the loop's control without vsync.


# Sprite source DC reuse

Run `node bench/sprite-dc-reuse.js [iterations]` on Windows. It times the Win32 `CreateCompatibleDC`/`DeleteDC` pair plus bitmap selection used by the previous sprite path, against repeated bitmap selection on one reusable DC. Five-run medians; it excludes `AlphaBlend` and whole-frame rendering.

Latest run: 100,000 operations, churn 1,084.63 ms, reuse 311.10 ms (3.49× for DC lifecycle). The renderer now shares one source DC across sprite blits and releases it on window teardown. Each blit restores the previous bitmap, so asset lifetime and pixels are unchanged. This benchmark does not quantify total app CPU reduction.

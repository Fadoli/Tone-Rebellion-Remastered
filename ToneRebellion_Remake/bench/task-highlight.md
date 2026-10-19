# Task highlight cost

Run `node bench/task-highlight.js [frames]`. The repeated-row benchmark uses 2,275 exact palette pixels (175×13), compares rebuilding the exact map for every row with reusing one map, and reports five-run medians. It is an algorithm microbenchmark, not whole-app CPU usage.

Latest run (Node.js 26.5.0, 120 rows): rebuild 2.41 ms; reuse 1.40 ms; 1.7× faster for this part of the work (about 8 μs saved per row). The older nearest-color scan took 8.41 ms for 12 rows. The quantized lookup still mismatched 515/4,096 deterministic arbitrary RGB samples, so it remains rejected.

The renderer builds the 255-entry exact RGB-to-index map once when loading the island palette. Row highlighting reuses it. Non-palette colors now use a 512-slot exact-color memo for the nearest palette result; cache collisions recompute the original RGB distance scan, and rebuilding the palette clears the memo. Pixel writes go directly to the persistent DIB.

The updated fallback benchmark models 2,275 highlight pixels containing 16 repeated non-palette colors, 120 rows per run. Latest Node.js 26.5.0 median: 131.18 ms without memoization, 0.72 ms with memoization (181× for that fallback work). Both paths produced the same checksum. This synthetic workload demonstrates the repeated-color case only; it does not measure the actual scene or whole-app CPU. `FUN_004459e6` paints the visible original task rows (REA `ev_fe6bd972740d099ab62aab1ef94df71e686f886cba296a0ba805cba982259d2f`), but the binary analysis does not establish repaint cadence or invalidation. The remake still needs a runtime CPU profile to quantify total savings.

## Retained and rejected

- Retained: palette map reuse; output is unchanged for exact palette pixels and fallback is unchanged for other pixels.
- Retained: exact memoization of repeated nearest-color fallback inputs; collisions are resolved by recomputation, preserving the prior search result.
- Rejected: 5-bit-per-channel nearest-color table; it changes colors. A redraw cache remains unsafe without invalidation for animated island pixels visible through transparent panel areas and for animated task previews.

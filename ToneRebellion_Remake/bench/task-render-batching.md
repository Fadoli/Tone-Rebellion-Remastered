# Tasks GDI batching

The task list previously flushed GDI once before each visible row label. The remake now draws row sprites first, flushes once, then writes all row labels to the DIB. The selected-row remap also no longer performs a second flush after its direct memory writes.

Run `node bench/task-render-batching.js`. A Win32 DIB benchmark with 7 rows, 3 alpha blits per row and identical full-buffer checksums measured 529.70 ms with per-row flushes versus 512.75 ms batched (3,000 frames; 1.03×). GDI flushes fell from 21,000 to 3,000. This synthetic measurement isolates GDI batching; it does not measure the remake's whole-frame CPU or establish original repaint cadence.

The original `FUN_004459e6` loop scales with visible rows. Static call graph analysis does not reveal how often the panel is repainted. See [the task REA notes](../../behavior/island-tasks.md).

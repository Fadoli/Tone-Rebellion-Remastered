# Selected task row transform

The selected task row applies the same haze lookup and opaque RGB conversion to every highlighted pixel. The renderer now precomputes the 256 possible output colors when it loads the island palette; the live pixel loop only looks up the palette index and writes the cached color.

Run `node bench/task-highlight-transform.js [iterations]`. It compares the previous per-pixel transform with the 256-entry lookup over a 175×13 row and checksums both outputs. On Node.js 26.5.0, 3,000 iterations measured 54.66 ms before and 13.91 ms after (3.93× for this isolated transform; outputs matched). The saving is about 13.6 μs per selected row, so this does not explain or establish a whole-frame CPU reduction.

This isolates the transform after palette-index lookup; it does not measure palette matching, GDI work, the full panel, or whole-game CPU. A runtime profile is still needed to identify the dominant cost.

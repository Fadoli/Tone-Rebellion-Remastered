# Task text pixel writes

The Tasks renderer draws bitmap-font glyphs with one GDI `SetPixelV` call per lit pixel. The new path flushes pending GDI work once per label and writes the same 1-bit glyph mask directly to the persistent top-down 32-bit DIB. It keeps the existing byte-to-glyph fallback, clipping, color and pixel placement.

Windows run (500 iterations of one representative label): 1,264.565 ms for `SetPixelV`, 2.176 ms for direct DIB writes (581.12×); both paths touched 1,088,000 pixels and produced identical buffers. Run `node bench/task-text-blit.js [path-to-bench_task_text.exe] [iterations]` to repeat. It measures only text rasterization, not whole-frame CPU use.

The core test checks exact glyph pixels, clipping at both horizontal edges, and an invalid target stride.

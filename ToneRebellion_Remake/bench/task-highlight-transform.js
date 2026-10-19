'use strict';

const { performance } = require('node:perf_hooks');

const WIDTH = 175;
const HEIGHT = 13;
const ROW_PIXELS = WIDTH * HEIGHT;
const ITERATIONS = Number(process.argv[2] || 5000);
const palette = new Uint32Array(256);
const haze = new Uint8Array(256);
const sourceIndexes = new Uint8Array(ROW_PIXELS);
const outputLut = new Uint32Array(256);

for (let i = 0; i < 256; i += 1) {
  palette[i] = (((i * 73) & 255) << 16) |
    (((i * 151) & 255) << 8) | ((i * 199) & 255);
  haze[i] = (i * 37 + 11) & 255;
}
for (let i = 0; i < 256; i += 1)
  outputLut[i] = 0xff000000 | palette[haze[i]];
for (let i = 0; i < ROW_PIXELS; i += 1) sourceIndexes[i] = (i * 67) & 255;

function run(precomputed) {
  let checksum = 2166136261;
  const start = performance.now();
  for (let iteration = 0; iteration < ITERATIONS; iteration += 1) {
    for (let pixel = 0; pixel < ROW_PIXELS; pixel += 1) {
      const index = sourceIndexes[pixel];
      const color = precomputed
        ? outputLut[index]
        : (0xff000000 | palette[haze[index]]);
      checksum = Math.imul(checksum ^ color, 16777619) >>> 0;
    }
  }
  return { ms: performance.now() - start, checksum };
}

const baseline = run(false);
const cached = run(true);
if (baseline.checksum !== cached.checksum) {
  throw new Error('precomputed highlight colors differ from per-pixel transform');
}
process.stdout.write(`pixels_per_row=${ROW_PIXELS} iterations=${ITERATIONS} ` +
  `per_pixel_ms=${baseline.ms.toFixed(2)} lookup_ms=${cached.ms.toFixed(2)} ` +
  `speedup=${(baseline.ms / cached.ms).toFixed(2)}x ` +
  `checksum_equal=yes\n`);

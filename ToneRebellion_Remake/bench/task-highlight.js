const { performance } = require('node:perf_hooks');

const palette = new Uint32Array(256);
for (let i = 0; i < 255; i += 1) {
  palette[i] = (((i * 73) & 255) << 16) |
    (((i * 151) & 255) << 8) | ((i * 199) & 255);
}
palette[255] = palette[17];

const pixels = new Uint32Array(175 * 13);
for (let i = 0; i < pixels.length; i += 1) pixels[i] = palette[(i * 67) % 255];
const samples = pixels.length;

function nearest(rgb) {
  const r = (rgb >>> 16) & 255;
  const g = (rgb >>> 8) & 255;
  const b = rgb & 255;
  let bestDistance = Infinity;
  let bestIndex = 0;
  for (let i = 0; i < 255; i += 1) {
    const dr = r - ((palette[i] >>> 16) & 255);
    const dg = g - ((palette[i] >>> 8) & 255);
    const db = b - (palette[i] & 255);
    const distance = dr * dr + dg * dg + db * db;
    if (distance < bestDistance) {
      bestDistance = distance;
      bestIndex = i;
      if (distance === 0) break;
    }
  }
  return bestIndex;
}

function buildExact() {
  const exact = new Map();
  for (let i = 0; i < 255; i += 1) {
    if (!exact.has(palette[i])) exact.set(palette[i], i);
  }
  return exact;
}

function runLookup(rebuildEachRow, iterations) {
  let checksum = 0;
  const cachedLookup = rebuildEachRow ? null : buildExact();
  const start = performance.now();
  for (let iteration = 0; iteration < iterations; iteration += 1) {
    const rowLookup = rebuildEachRow ? buildExact() : cachedLookup;
    for (let i = 0; i < pixels.length; i += 1) checksum += rowLookup.get(pixels[i]);
  }
  return { ms: performance.now() - start, checksum };
}

function runNearest(iterations) {
  let checksum = 0;
  const start = performance.now();
  for (let iteration = 0; iteration < iterations; iteration += 1) {
    for (let i = 0; i < pixels.length; i += 1) checksum += nearest(pixels[i]);
  }
  return { ms: performance.now() - start, checksum };
}

function buildQuantizedLut() {
  const lut = new Uint8Array(32 * 32 * 32);
  for (let r = 0; r < 32; r += 1) {
    for (let g = 0; g < 32; g += 1) {
      for (let b = 0; b < 32; b += 1) {
        lut[(r << 10) | (g << 5) | b] =
          nearest((((r << 3) | 4) << 16) | (((g << 3) | 4) << 8) | ((b << 3) | 4));
      }
    }
  }
  return lut;
}

/* A selected row can contain arbitrary island colors beneath transparent
   highlight pixels. Model a fixed pool of repeated non-palette colors and
   compare the original full scan with the remake's 512-slot exact memo. */
const fallbackColors = new Uint32Array(175 * 13);
const repeatedColors = [
  0x000000, 0xffffff, 0x1856ae, 0x68aeff,
  0x7bed74, 0xee5fda, 0xffca44, 0x3ddaf8,
  0x5a6b7c, 0x344455, 0x102030, 0x90a0b0,
  0x243c60, 0x476185, 0x738395, 0xc0d0e0,
];
for (let i = 0; i < fallbackColors.length; i += 1) {
  fallbackColors[i] = repeatedColors[(i * 13 + (i >>> 3)) % repeatedColors.length];
}

function nearestColor(rgb) {
  const r = (rgb >>> 16) & 255;
  const g = (rgb >>> 8) & 255;
  const b = rgb & 255;
  let bestDistance = Infinity;
  let bestIndex = 0;
  for (let i = 0; i < 255; i += 1) {
    const dr = r - ((palette[i] >>> 16) & 255);
    const dg = g - ((palette[i] >>> 8) & 255);
    const db = b - (palette[i] & 255);
    const distance = dr * dr + dg * dg + db * db;
    if (distance < bestDistance) {
      bestDistance = distance;
      bestIndex = i;
    }
  }
  return bestIndex;
}

function nearestCached(rgb, cacheKeys, cacheIndexes, cacheUsed) {
  const slot = Math.imul(rgb, 2654435761) >>> 23;
  if (cacheUsed[slot] && cacheKeys[slot] === rgb) return cacheIndexes[slot];
  const index = nearestColor(rgb);
  cacheKeys[slot] = rgb;
  cacheIndexes[slot] = index;
  cacheUsed[slot] = 1;
  return index;
}

function runFallback(useCache, iterations) {
  let checksum = 0;
  const cacheKeys = new Uint32Array(512);
  const cacheIndexes = new Uint8Array(512);
  const cacheUsed = new Uint8Array(512);
  const start = performance.now();
  for (let iteration = 0; iteration < iterations; iteration += 1) {
    for (let i = 0; i < fallbackColors.length; i += 1) {
      checksum += useCache
        ? nearestCached(fallbackColors[i], cacheKeys, cacheIndexes, cacheUsed)
        : nearestColor(fallbackColors[i]);
    }
  }
  return { ms: performance.now() - start, checksum };
}

const quantized = buildQuantizedLut();
let quantizedMismatches = 0;
for (let i = 0; i < 255; i += 1) {
  const rgb = palette[i];
  const key = ((((rgb >>> 16) & 255) >>> 3) << 10) |
    ((((rgb >>> 8) & 255) >>> 3) << 5) | ((rgb & 255) >>> 3);
  if (quantized[key] !== nearest(rgb)) quantizedMismatches += 1;
}
let randomState = 0x6d2b79f5;
for (let i = 0; i < 4096; i += 1) {
  randomState = Math.imul(randomState ^ (randomState >>> 15), randomState | 1);
  randomState ^= randomState + Math.imul(randomState ^ (randomState >>> 7), randomState | 61);
  const rgb = (randomState ^ (randomState >>> 14)) & 0xffffff;
  const key = ((((rgb >>> 16) & 255) >>> 3) << 10) |
    ((((rgb >>> 8) & 255) >>> 3) << 5) | ((rgb & 255) >>> 3);
  if (quantized[key] !== nearest(rgb)) quantizedMismatches += 1;
}

const iterations = Number(process.argv[2] || 120);
const rebuildingRuns = [];
const cachedRuns = [];
for (let runIndex = 0; runIndex < 5; runIndex += 1) {
  rebuildingRuns.push(runLookup(true, iterations));
  cachedRuns.push(runLookup(false, iterations));
}
rebuildingRuns.sort((a, b) => a.ms - b.ms);
cachedRuns.sort((a, b) => a.ms - b.ms);
if (rebuildingRuns[2].checksum !== cachedRuns[2].checksum) {
  throw new Error('cached lookup differs from per-row lookup');
}

const priorNearest = runNearest(Math.max(1, Math.floor(iterations / 10)));
const uncachedRuns = [];
const memoizedRuns = [];
for (let runIndex = 0; runIndex < 5; runIndex += 1) {
  uncachedRuns.push(runFallback(false, iterations));
  memoizedRuns.push(runFallback(true, iterations));
}
uncachedRuns.sort((a, b) => a.ms - b.ms);
memoizedRuns.sort((a, b) => a.ms - b.ms);
if (uncachedRuns[2].checksum !== memoizedRuns[2].checksum) {
  throw new Error('memoized nearest palette lookup changed output');
}
process.stdout.write(`rows=${samples} iterations=${iterations} ` +
  `lookup_rebuilt_per_row_ms=${rebuildingRuns[2].ms.toFixed(2)} ` +
  `lookup_reused_ms=${cachedRuns[2].ms.toFixed(2)} ` +
  `reuse_speedup=${(rebuildingRuns[2].ms / cachedRuns[2].ms).toFixed(1)}x ` +
  `prior_nearest_scan_ms_per_${Math.max(1, Math.floor(iterations / 10))}_rows=${priorNearest.ms.toFixed(2)} ` +
  `quantized_mismatches=${quantizedMismatches} ` +
  `fallback_pixels=${fallbackColors.length} repeated_fallback_colors=${repeatedColors.length} ` +
  `fallback_uncached_ms=${uncachedRuns[2].ms.toFixed(2)} ` +
  `fallback_memoized_ms=${memoizedRuns[2].ms.toFixed(2)} ` +
  `fallback_speedup=${(uncachedRuns[2].ms / memoizedRuns[2].ms).toFixed(1)}x\n`);

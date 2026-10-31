// Summarises a `--bench --bench-profile` report.
// Usage: node bench/hotspots.js <bench_report.txt> <nm -n output> [phase] [top]
// The nm listing must come from the executable that produced the report:
//   nm -n build/bench/remake_menu.exe > syms.txt
'use strict';
const fs = require('node:fs');

const [reportPath, symbolPath, phaseFilter = 'all', topArg = '25'] =
  process.argv.slice(2);
if (!reportPath || !symbolPath) {
  console.error('usage: node bench/hotspots.js <report> <nm-output> [phase] [top]');
  process.exit(1);
}
const top = Number(topArg);

// Text symbols sorted by address, for nearest-below lookups.
const symbolAddresses = [];
const symbolNames = [];
for (const line of fs.readFileSync(symbolPath, 'utf8').split(/\r?\n/)) {
  const match = /^([0-9a-f]+) [tT] _?(.+)$/.exec(line);
  if (!match) continue;
  symbolAddresses.push(parseInt(match[1], 16));
  symbolNames.push(match[2]);
}

function ownSymbol(address) {
  let low = 0;
  let high = symbolAddresses.length - 1;
  let found = -1;
  while (low <= high) {
    const middle = (low + high) >> 1;
    if (symbolAddresses[middle] <= address) {
      found = middle;
      low = middle + 1;
    } else {
      high = middle - 1;
    }
  }
  return found < 0 ? '?' : symbolNames[found];
}

const lines = fs.readFileSync(reportPath, 'utf8').split(/\r?\n/);
let imageBase = 0x400000;
const header = [];
const resolved = new Map();
function label(frame) {
  let name = resolved.get(frame);
  if (name !== undefined) return name;
  if (frame[0] === '@') name = ownSymbol(imageBase + parseInt(frame.slice(1), 16));
  else name = frame.replace(/\+[0-9a-f]+$/, '');
  resolved.set(frame, name);
  return name;
}

const phaseCounts = new Map();
const self = new Map();
const attributed = new Map();
const inclusive = new Map();
const callerPairs = new Map();
let total = 0;
function bump(map, key) {
  map.set(key, (map.get(key) || 0) + 1);
}

for (const line of lines) {
  if (line.startsWith('image_base ')) {
    imageBase = parseInt(line.slice(11), 16);
    continue;
  }
  if (!line.startsWith('s ')) {
    if (line.length !== 0) header.push(line);
    continue;
  }
  const parts = line.split(' ');
  const phase = parts[1];
  bump(phaseCounts, phase);
  if (phaseFilter !== 'all' && phase !== phaseFilter) continue;
  ++total;
  const frames = parts.slice(2);
  bump(self, label(frames[0]));
  // First frame inside the game executable: the code that asked for the work.
  let ownIndex = -1;
  for (let i = 0; i < frames.length; ++i) {
    if (frames[i][0] === '@') {
      ownIndex = i;
      break;
    }
  }
  if (ownIndex >= 0) {
    const owner = label(frames[ownIndex]);
    const leaf = ownIndex === 0 ? '(own code)' : label(frames[0]);
    bump(attributed, owner);
    bump(callerPairs, `${owner} -> ${leaf}`);
  } else {
    bump(attributed, '(no game frame)');
  }
  const seen = new Set();
  for (const frame of frames) {
    if (frame[0] !== '@') continue;
    const name = label(frame);
    if (seen.has(name)) continue;
    seen.add(name);
    bump(inclusive, name);
  }
}

function print(title, map) {
  const rows = [...map].sort((a, b) => b[1] - a[1]).slice(0, top);
  console.log(`\n## ${title}`);
  for (const [name, count] of rows)
    console.log(`${(100 * count / total).toFixed(1).padStart(6)}%  ${name}`);
}

for (const line of header) console.log(line);
console.log(`\nsamples by phase: ${[...phaseCounts].map(([p, c]) => `${p} ${c}`).join(', ')}`);
console.log(`phase filter: ${phaseFilter} (${total} samples)`);
print('self (leaf frame)', self);
print('attributed (innermost game function, system time included)', attributed);
print('game function -> leaf', callerPairs);
print('inclusive (game functions on the stack)', inclusive);

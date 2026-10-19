'use strict';

const { execFileSync } = require('node:child_process');
const { mkdtempSync, rmSync } = require('node:fs');
const { tmpdir } = require('node:os');
const { join } = require('node:path');

const root = __dirname;
const temp = mkdtempSync(join(tmpdir(), 'tone-task-render-'));
const exe = join(temp, 'task-render-batching.exe');
try {
  execFileSync('C:\\MinGW\\bin\\gcc.exe', [
    join(root, 'task-render-batching.c'), '-O2', '-o', exe,
    '-lgdi32', '-lmsimg32',
  ], { stdio: 'inherit' });
  process.stdout.write(execFileSync(exe, [], { encoding: 'utf8' }));
} finally {
  rmSync(temp, { recursive: true, force: true });
}

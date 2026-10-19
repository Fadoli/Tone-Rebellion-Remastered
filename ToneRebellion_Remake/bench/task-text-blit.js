const { spawnSync } = require('node:child_process');
const { resolve } = require('node:path');

const exe = resolve(process.argv[2] || 'build/release/bench_task_text.exe');
const iterations = process.argv[3] || '500';
const result = spawnSync(exe, [iterations], { encoding: 'utf8' });
if (result.error) throw result.error;
if (result.status !== 0) {
  process.stderr.write(result.stderr || result.stdout);
  process.exit(result.status || 1);
}
process.stdout.write(result.stdout);

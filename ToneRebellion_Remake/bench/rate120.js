// Runs ToneRebellion_Remake.exe --bench --bench-rate over scenarios, filters
// and window sizes, and prints a Markdown table (bench/rate120.md).
//   node bench/rate120.js [seconds] [rate] [--gpu-sync]
'use strict';
const { execFileSync } = require('node:child_process');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');

const root = path.join(__dirname, '..');
const exe = path.join(root, 'ToneRebellion_Remake.exe');
const seconds = Number(process.argv[2] || 8);
const rate = Number(process.argv[3] || 120);
const gpuSync = process.argv.includes('--gpu-sync');
const filters = [[0, 'nearest'], [2, 'sharp bilinear'], [4, 'Lanczos 3'],
    [5, 'xBR'], [6, 'HQx'], [7, 'ScaleFX']];
const scenarios = ['idle', 'battle'];
const clients = ['1280x960', '1024x768'];

// Saves and settings in a throwaway folder (no player data touched).
const saves = fs.mkdtempSync(path.join(os.tmpdir(), 'tone-bench-'));
fs.writeFileSync(path.join(saves, 'audio.cfg'), '0 0 0 0\n');
const out = path.join(saves, 'report.txt');

function parse(text) {
    const r = {};
    for (const line of text.split(/\r?\n/)) {
        const t = line.trim().split(/\s+/);
        if (t.length < 2) continue;
        if (t.length > 2 && t[1] === 'count') {
            const o = {};
            for (let i = 1; i + 1 < t.length; i += 2) o[t[i]] = Number(t[i + 1]);
            r[t[0]] = o;
        } else {
            r[t[0]] = t.slice(1).join(' ');
        }
    }
    return r;
}

const rows = [];
for (const client of clients) {
    for (const scenario of scenarios) {
        for (const [filter, name] of filters) {
            const args = ['--bench', '--bench-scenario', scenario, '--bench-rate', String(rate),
                '--bench-seconds', String(seconds), '--bench-filter', String(filter),
                '--bench-client', client, '--bench-out', out];
            if (gpuSync) args.push('--bench-gpu-sync');
            execFileSync(exe, args, { cwd: root, env: { ...process.env, TONE_REBELLION_SAVE_DIR: saves } });
            const r = parse(fs.readFileSync(out, 'utf8'));
            rows.push({ client, scenario, name, r });
            process.stderr.write(`${client} ${scenario} ${name}: ${r.paints_per_s} paints/s\n`);
        }
    }
}

const f = (x) => (x === undefined || Number.isNaN(x) ? '-' : x.toFixed(2));
console.log(`Rate ${rate} Hz, ${seconds} s per run${gpuSync ? ', glFinish after each present' : ''}.\n`);
console.log('| client | scenario | filter | paints/s | game frames/s | CPU % of one core | sim ms (mean) | render ms (mean / p95) | present ms (mean / p95) | paint interval ms (p95 / max) |');
console.log('|---|---|---|---|---|---|---|---|---|---|');
for (const { client, scenario, name, r } of rows) {
    console.log(`| ${client} | ${scenario} | ${name} | ${f(Number(r.paints_per_s))} | ${f(Number(r.game_frames_per_s))} | ${f(Number(r.process_cpu_pct_of_one_core))} | ${f(r.sim.mean_ms)} | ${f(r.render.mean_ms)} / ${f(r.render.p95_ms)} | ${f(r.present.mean_ms)} / ${f(r.present.p95_ms)} | ${f(r.paint_interval.p95_ms)} / ${f(r.paint_interval.max_ms)} |`);
}

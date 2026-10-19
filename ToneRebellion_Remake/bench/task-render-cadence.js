const ticksPerSecond = Number(process.argv[2] || 30);
const seconds = Number(process.argv[3] || 60);
const redrawDivisor = 6;
const previousRedrawDivisor = 3;

if (!Number.isInteger(ticksPerSecond) || ticksPerSecond < 1 ||
    !Number.isInteger(seconds) || seconds < 1) {
  throw new Error('usage: node bench/task-render-cadence.js [ticksPerSecond] [seconds]');
}

let taskPaints = 0;
let previousTaskPaints = 0;
for (let tick = 1; tick <= ticksPerSecond * seconds; ++tick) {
  if (tick % redrawDivisor === 0) ++taskPaints;
  if (tick % previousRedrawDivisor === 0) ++previousTaskPaints;
}

const regularPaints = ticksPerSecond * seconds;
process.stdout.write(JSON.stringify({
  ticks: regularPaints,
  regularPaints,
  previousTaskPaints,
  taskPaints,
  reductionFromPreviousPercent: (1 - taskPaints / previousTaskPaints) * 100,
  reductionPercent: (1 - taskPaints / regularPaints) * 100,
  redrawDivisor,
  note: 'Scheduled paint-count comparison only; excludes input-triggered paints and does not measure CPU time.',
}) + '\n');

# Task panel repaint cadence experiment (rejected)

Run `node bench/task-render-cadence.js [ticksPerSecond] [seconds]`. At 30 simulation ticks/s over 60 seconds, a six-tick schedule requests 300 paints versus 1,800 at every tick. This count model suggested fewer paints, but the optimization was rejected: each `WM_PAINT` redraws the entire island, so gating invalidation also reduced all world animation and made the game appear to run at 5 Hz whenever Tasks was selected. The application now invalidates on every 33 ms game tick in every island-panel mode.

**Original binary:** `FUN_004459e6` renders the visible task rows and their labels/progress (REA `ev_fe6bd972…`). Static analysis did not establish its caller cadence or task-specific invalidation. A timer call has unresolved purpose (`ev_8e3b3209…`), so it is not treated as task-panel evidence.

**Remake policy:** the 33 ms timer advances simulation and requests a full-window repaint. A future task-only redraw optimization must avoid suppressing the island's repaint cadence.

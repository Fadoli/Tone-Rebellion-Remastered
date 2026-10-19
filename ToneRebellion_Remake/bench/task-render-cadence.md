# Task panel repaint cadence

Run `node bench/task-render-cadence.js [ticksPerSecond] [seconds]`. The remake advances simulation at 30 ticks/s and redraws the full screen on each tick, including while Tasks is open: 30 Hz. Over 60 seconds this is 1,800 timer-requested paints, versus 600 at the previous 10 Hz Tasks cadence. The script counts scheduled paints; it does not measure wall-clock CPU or additional input-triggered repaint requests.

**Original binary:** `FUN_004459e6` returns unless both panel flags are set and then iterates visible rows only (REA `ev_de6da60ad170dce608c62cd139ae11567db47c54a3214cea6503a31d13ecb928`). Its cadence is unknown; an xref does not resolve to a caller, so static analysis does not establish task-specific invalidation or a permanent rendering loop (`ev_3c0d1448c85b43140bc4ee2af73c66737365e5acf3790c726bbe3997a2c18fa7`, `ev_8b6a2ab6c368a4af25570fa84d41e98d13e6521356b6434d47f5ac9d4b0b1652`).

**Choice and limit:** Tasks no longer suppresses timer-driven paints. The screen refreshes at the same 30 Hz cadence as the simulation.

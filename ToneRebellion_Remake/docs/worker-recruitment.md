# Automatic worker recruitment

The remake now ports the automatic subtype-0 worker path from `FUN_0045eaa7`.
It advances once per island simulation tick. The native gate requires net
maintenance surplus `+0x40 > 4`, worker subtype count below half gross
maintenance capacity `+0x3c`, and an available class-1 spawn marker. The
per-player timer at `+0x8c` increments while those conditions hold; when it is
greater than 300 and a marker remains available, `FUN_004532e2` creates one
worker, then the timer resets. Gross capacity is stored separately from net
surplus so the population threshold follows the native formula.

Gross capacity is `(int)(sqrt(S) * 20.0)`, `S` = sum over islands of the
class-1 count returned by `FUN_00462285`. `FUN_00477599` is the CRT `pow`
(`fyl2x` path); the caller pushes `0.5` then the sum, so it computes `S^0.5`,
not a constant 10. The earlier "0.5 x 20.0 = 10" reading took the wrong stack
slot. Net budget is `capacity - min(spend, capacity)`.

The source selects a visible class-1 location on the currently selected
island, nearest its Hall anchor. The remake has no live selected-island state
per player, so it uses the player's starting Hall island and the nearest
visible class-1 marker there. New workers use the player's starting worker
stats, occupy a reusable slot in the native 256-entry floater table, receive
the native `0x801` runtime flags, and enter the existing body/legs animation
renderer.

Creation event `FUN_00416a9a(0, site)` resolves `fltbirth` for ordinary tribes.
Local `effects.txt` declares it `SoundOnly`, and `sound.txt` maps it to
`data\fltbirth.wav`. The remake queues that sound through its existing Win32
audio adapter. The birth event has no sprite sequence of its own. The visible
animation is the tribe site's PROD cycle: `FUN_004532e2` sets site flag 2,
clears `+0x42`, links the floater at site `+0x2e` and holds it with `0x801`.
The class-1 tick runs 100 ticks, then releases the worker at `(x, y - 0x28)`
(`FUN_00450a71` cases 0/1, `decompilation/functions/0015_batch_0011/details-04-02.md`).
The remake follows this through `leviathan_spawned_floater`.

Birth visual (static reading of conserved pseudocode; REA session closed):
the world floater loop `FUN_00435f4d` skips any floater with `+0x1c & 1`
(`ev_9466be6d877d3a7686cb6bcf7838301774c412a8e560a476b938307aac8b32ad`, `decompilation/functions/0012_batch_0008/details-06-02.md`), so the held
newborn is not drawn as a floater. `FUN_0040bf98` gives class-1 items 0/5 the
POOL shape `DAT_004a4b70`, which has no PROD row in `bldinf.txt`. The class-1
site drawer `FUN_0040b09a` (dispatched through thunk `0x401780` from
`FUN_0040d5bf`; `ev_c454d7fb5d524fdd5ec56d6a1fef42e234a6ed8e81d3e14ffb9b0592edacc8a7`)
draws the white birth: for items outside 6..9 with flag 2, frame 0 of the
linked floater's body and legs at `(x, y - 0x28)`, unmirrored, through the
`FUN_004106dd(1, level)` white table. While `+0x42 < 17` `FUN_004109a6`
recolors only the ground under the silhouette (level `+0x42 / 2`); then
`FUN_00404c3b`/`FUN_00404c5a` draw the sprite through the table at level
`(100 - +0x42) / 2`, clamped 0..7, so it stays white and fades to its colors
before release. The remake now skips held floaters (bit 0x001) in the island
loop, which also removes the duplicate held Leviathan, and draws this birth in
`draw_island_worker_birth`. Interpretation: frame 0 of the remake's tribe body
and legs sheets equals native shape frame 0.

Evidence: `FUN_0045eaa7` (`ev_d0241191e19be6e3ec7ab4c4a16172c22e772b518c82aeef201ad3125475226d`),
`FUN_004532e2` (`ev_f568b5a3b8f15baa665610518ba92d8599e54715db51c26ef29d327af6893104`),
and `FUN_00466fe4` (`ev_0ca802ac15043c61c073f6d68546619fc924a4ba10fd4d9f04e203668dc62ed7`).
Detailed pseudocode is in `decompilation/functions/0017_batch_0013/details-01-02.md`,
`decompilation/functions/0015_batch_0011/details-05-02.md`, and
`decompilation/functions/0017_batch_0013/details-06-01.md`.

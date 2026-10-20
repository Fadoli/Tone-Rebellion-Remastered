# Automatic worker recruitment

The remake now ports the automatic subtype-0 worker path from `FUN_0045eaa7`.
It advances once per island simulation tick. The native gate requires net
maintenance surplus `+0x40 > 4`, worker subtype count below half gross
maintenance capacity `+0x3c`, and an available class-1 spawn marker. The
per-player timer at `+0x8c` increments while those conditions hold; when it is
greater than 300 and a marker remains available, `FUN_004532e2` creates one
worker, then the timer resets. Gross capacity is stored separately from net
surplus so the population threshold follows the native formula.

Gross capacity is 10 per accessible class-1 Tone pool: `FUN_0045e6d3`
converts the pool count by 0.5, then multiplies by the native 20.0 constant.

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
audio adapter. The worker appears at the class-1 marker and immediately uses
the normal animated body and walking legs; the native birth event itself has
no separate sprite sequence.

Evidence: `FUN_0045eaa7` (`ev_d0241191e19be6e3ec7ab4c4a16172c22e772b518c82aeef201ad3125475226d`),
`FUN_004532e2` (`ev_f568b5a3b8f15baa665610518ba92d8599e54715db51c26ef29d327af6893104`),
and `FUN_00466fe4` (`ev_0ca802ac15043c61c073f6d68546619fc924a4ba10fd4d9f04e203668dc62ed7`).
Detailed pseudocode is in `../functions/0017_batch_0013/details-01-02.md`,
`../functions/0015_batch_0011/details-05-02.md`, and
`../functions/0017_batch_0013/details-06-01.md`.

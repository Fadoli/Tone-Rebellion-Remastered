# Floater movement primitives: REA evidence and port

This note records observed selection/input/movement procedures and separates them
from behavior still needing class/state checks. Ghidra pseudocode is a decompiler
reconstruction, not recovered source; field names and inferred types remain
provisional. The user has clarified that workers cannot receive direct orders:
selecting them only shows stats, while soldiers and mages are orderable. The
remake now routes mode `0x13` to state 9 for selected floaters with nonzero
subtype. That subtype mapping is an implementation gate following the user's
constraint; the original allowlist and `FA_Cast` interaction remain unresolved.


Detailed sections below. The headings are kept here to preserve the old anchor links.

## Input and destination path
[Full section](input.md#input-and-destination-path)

### `0x4c` coordinate order and its receiver
[Full section](coordinate-orders.md#0x4c-coordinate-order-and-its-receiver)

## Interaction cursor lifecycle
[Full section](speed.md#interaction-cursor-lifecycle)

## Unit tick and speed source
[Full section](speed.md#unit-tick-and-speed-source)

## Tick, state machine, target and arrival detail
[Full section](tick.md#tick-state-machine-target-and-arrival-detail)

### Update sequence
[Full section](tick.md#update-sequence)

### Destination resolution and step size
[Full section](step-kernel.md#destination-resolution-and-step-size)

### Target source and facing adjustment
[Full section](step-kernel.md#target-source-and-facing-adjustment)

### `FA_Move`: local target approach and arrival
[Full section](local-orders.md#fa_move-local-target-approach-and-arrival)

### `FA_DefendFlt`: reach target, select a nearby unit, then approach it
[Full section](local-orders.md#fa_defendflt-reach-target-select-a-nearby-unit-then-approach-it)

### Autonomous order selection and execution
[Full section](autonomous-orders.md#autonomous-order-selection-and-execution)

### `FA_Wander` destination generation and repeated movement
[Full section](autonomous-orders.md#fa_wander-destination-generation-and-repeated-movement)

### Attack orders: approach then stationary combat state
[Full section](local-orders.md#attack-orders-approach-then-stationary-combat-state)

### Training and recharge orders: travel to a location record
[Full section](travel-orders.md#training-and-recharge-orders-travel-to-a-location-record)

### `FA_ObtainObject`: assigned location or owner candidate
[Full section](travel-orders.md#fa_obtainobject-assigned-location-or-owner-candidate)

### Cross-island handoff through state `0x11`
[Full section](travel-orders.md#cross-island-handoff-through-state-0x11)

### `FA_Deliver`: site search, island handoff and local approach
[Full section](site-orders.md#fa_deliver-site-search-island-handoff-and-local-approach)

### `FA_Repair`: candidate site then local approach
[Full section](site-orders.md#fa_repair-candidate-site-then-local-approach)

### `FA_Build`: three local route states
[Full section](site-orders.md#fa_build-three-local-route-states)

### `FA_Cast` (`0x13`): target resolution without locomotion
[Full section](special-orders.md#fa_cast-0x13-target-resolution-without-locomotion)

### `FA_MergeWith` (`0x14`): approach, then idle/roam state
[Full section](special-orders.md#fa_mergewith-0x14-approach-then-idleroam-state)

### Orders without a local consumer branch
[Full section](order-edge-cases.md#orders-without-a-local-consumer-branch)

### Facing and rendered anchor
[Full section](order-edge-cases.md#facing-and-rendered-anchor)

## Current port and limits
[Full section](port.md#current-port-and-limits)

## Order 9 from the Hall move context
[Full section](hall-context.md#order-9-from-the-hall-move-context)

## Direct movement/combat audit (pseudocode re-read by the main agent)

Evidence: `FUN_00422d27` `ev_dce3014d` and assembly `ev_12c6e0e8`, `FUN_004672a6` `ev_11cfa067` (Chebyshev distance), `FUN_00420217` `ev_6ccca76e`, `FUN_004204bc` `ev_2016a3eb`, `FUN_0041e569` `ev_8578fcc7`, `FUN_0042520e` `ev_124b4bd8`, `FUN_00425296` `ev_436a1ff2`.

- Fixed: the reduced speed near the target is `distance / 4` truncated (`CDQ/AND 3/ADD/SAR 2` at `0x422f8c`), not rounded up; a zero step falls back to `tick & 1`. `floater_motion.c` and its test now follow the native.
- Fixed: the expiry of floater flag `0x100` (cast shield at level 0/1, and `0x1100` at level 2) was missing. `FUN_0041e569` (tail) increments the counter `+0x24`; beyond 2000 (`FUN_00425296(0x100)`) the flag drops; with `0x1000`, beyond 0xdac (3500) both drop. Ported in `game_session_tick_floater_cast_pulse`.
- Confirmed matching: per-axis bounded movement steps, subtype 0 speed doubling per owner, +1 for sites 0x2c/0x2d/0x2e, states 8/9/0xe at speed 1 near the target (radius 100), `FUN_00425296` table (8 -> 40, 0x2000 -> 45), death timer, `FUN_00420217` damage roll (three draws bounded to 10, owner/0x8/0x100 guard) and `FUN_004204bc` application (death when HP < 1).
- Not diffed line by line: the x87 hit-percentage computation of `FUN_00420217` (the decompiler loses it; the port reconstructs it), the action cases 6/7/8/9 of `FUN_0041e569`, and the functions `FUN_00420721`, `FUN_00423068`, `FUN_004200d2`, `FUN_00420188`, `FUN_00415fc6`. Not verified in game.

### Hit chance of `FUN_00420217` (assembly re-read, `ev_d4bb6e22`; constants `ev_15f172be`, jump table `ev_d7687baa`, `__ftol` `ev_7430d34a`)

`FUN_004533a8` (towers) calls `FUN_00420217(pad row +0x0a, -1, owner)`; `FUN_004200d2` (floater strike) calls it with the attacker's power, its realm (`FUN_0042003c`) and its owner. Fixed in `game_session_combat.c`:
- The difficulty term is a double: difficulty 0 -> `p/4` (floor 1), 1 and 2 -> `p/2` (floor 2), 3 and 4 -> `2p/3` (floor 3); the port used integer divisions and treated 2 as 3+.
- The "different realm" correction multiplies the difficulty term (not the raw power): `(0/limit - 0.5) * term`, sign inverted when the attacker realm > 1 (the globals `DAT_00618e4c/50` are 0 at load).
- The percentage `(int)(60*score/14) + 10` uses `__ftol`, which TRUNCATES (`OR AH,0xc` at `0x472c7b`); the port rounded to nearest.
- Tower path (`realm = -1`): the attacker realm becomes the target's, so there is no realm term; the port applied a term derived from the subtype.
- Defense: subtypes 0 and 9 have zero defense (the port added the levels for subtype 0); a subtype 9 takes the attacker's realm.
The globals `DAT_00618e4c/50` each have 3 references outside this computation (`0x438b9b/0x438e45`, `0x438bbb/0x438f9e`), not analysed. Not verified in game.

### Attack power: a single function (`FUN_0041fde6`, `ev_6840e960`; loader `FUN_004633a7`, `ev_8709314a`)

`FUN_004200d2` (floater attack) and `FUN_00420188` (site attack, `ev_18b2df90`) call the same `FUN_0041fde6`. The loader writes the six integers of each row at offsets `+0` (range), `+2` (realm), `+6` (HP), `+8` (max attack points, compared with the charge counter in `FUN_0041e569` case 1), `+0xa` (attack strength), `+0xc` (speed). The base of `FUN_0041fde6` is therefore the attack strength (`+0xa`), not the max attack points (`+8`). The port used `max_attack_points` for sites; fixed: a single `floater_attack_power` function with base `attack_strength` (category 4 or loaded nonzero subtype), +3 if the linked source has flag `0x8000`, +1 for the player's glyph bits `0x01/0x40/0x400` on a `0x2c/0x2d/0x2e` source, then level × 3 plus a 1/22 share (category 4) or level × 2. The glyph term was missing from the floater path. Not verified in game.

### RNG and approach radius (assembly re-read: `FUN_00467260` `ev_ea4dec92`, `FUN_00474b80` `ev_85045540`, `FUN_00474b90` `ev_c71d7459`; `FUN_00420721` `ev_fd5a4201`, `FUN_00423068` `ev_f59cd438`)

- Fixed: `FUN_00467260` loads the seed `[0x4a4b78]`, copies it into the CRT seed, performs one step of the MSVC LCG and WRITES the 15-bit result back to `[0x4a4b78]`. The next draw therefore restarts from the previous 15-bit output, not from the 32-bit state. `tone_rng.c` kept the full state (sequence 41, 18467, 6334 for seed 1); it now follows the native (41, 172, 600). All draws after the first change, hence also generated worlds, tower targets and music; the tests `test_tone_rng` and `test_game_music` were updated. The initial seed written by the native into `[0x4a4b78]` is not identified.
- Fixed: the approach radius of `FUN_0041e569` case 0xe/0xf comes from `FUN_00420721` (row range, `×5/4` truncated to 16 bits with glyph bit `0x04` and a linked source); 10 by default.
- Not ported (found by direct reading of `FUN_00423068`): the rejection of an order when the arrival point falls outside the owner's `[min, max]` (`return 0` -> `FUN_00421ec1(-1)`), state 8 storing a relative random offset `(rand(200)-100, rand(200)-100)` with no `y` bound, and the approach offsets `±0x4a/0x4c` from `FUN_0045575c` for states 3/4.

### Weighted selections and target search (`FUN_0041e28e` `ev_17c3c46d`, `FUN_00420a55` `ev_54951b3e`, `FUN_00420635` `ev_ccde6e44`, `FUN_00420991` `ev_1f975170`; haiku/general agent for the first pass, all facts below re-read)

- Fixed: `FUN_0041e28e` computes `weight_i = sum / d_i`, normalised to 1000, then integer CUMULATIVE thresholds `threshold_i = ftol(threshold_{i-1} + weight_i)` (`__ftol` truncates), and forces the last threshold to 1000 so that a draw always picks a candidate. The port rounded to nearest (action9) or did not accumulate at all (delivery, separate copy) and could return -1. A single function `game_session_pick_inverse_distance` now serves the four uses.
- Fixed: `FUN_00420a55` case 4 filters on the distance of the target point (< 90, zero allowed) but collects and weights the distance from the searching floater to the site (`FUN_00420635`); the port used the target point for both.
- Fixed: `FUN_004208eb` has no special case for a protected category-4 floater; the port always returned that floater.
- Not ported, observed: `FUN_00420991` tests an island table `DAT_0061fa2e[island] >= 0x65` (inverts the category-4 rule for category-4 sources); table zero at load, writer unknown.
- Not ported, reported by agent (not re-read): order effects (`FUN_004211bb`) for actions 2/0x11 (recharge), 0xb/0xc (object drop before charge), 0xd ("carried object" branch -> state 4), delivery sub-steps (action 4), action 5 stored as 4, `FUN_00466533` cancellation after attack; and in `FUN_0041e569` the end block (subtype 8 -> order to the Hall, subtype 4 -> building record), the melee flags `0x10`/`0x40` (never written by the port; `FUN_00422d27` blocks the step if `+0x1c & 0x411`), state 8 (exit via `FUN_004208eb`), the 1/8 cadence of state 9, the `FUN_00416a9a(5)` calls at state 0x15.

### Defense (state 8), melee (flags 0x10/0x40) and stationary strikes (re-read: `FUN_00423068` `ev_78129691`/asm `ev_f59cd438`, `FUN_00422d27` `ev_dce3014d`, `FUN_0041e569` `ev_8578fcc7`, `FUN_004211bb` `ev_3477c421`)

- Fixed: in state 8 the native stores in `+0x28/+0x2a` an offset `(rand(200)-100, rand(200)-100)` drawn once at planning (x then y, plan rejected if x is outside `[min, max]` with min = 0 by default) and `FUN_00422d27` adds the protected floater's position (`DAT_006137c8/ca`) at each step. The port drew a position around the defender itself at every tick (never following). Now: offset fixed at planning (`follow_offset_x/y`), destination = protected + offset clamped to x 0..0x9ff, y 0x28..0x122; replan only on arrival without a candidate.
- Fixed: states 6 and 7 (strikes) are stationary in the native (`FUN_00422d27` not called); the port chased the target.
- Fixed: melee. On arrival in state 0xf (outside action 0x14) of a floater without a ranged attack (`FUN_00420721` returns 0), the target receives `0x10`, the attacker `0x40`. A floater with `0x10` does not step (`+0x1c & 0x411`, only 0x10 retained here) as long as a floater on the island targets it with `0x40`. The port never wrote these flags.
- Not verified in game. Bits `0x01` and `0x400` of the same blocking mask (`FUN_00422d27` not called) are not ported.

### Charge orders and order end (re-read: `FUN_004211bb` `ev_3477c421`)

- Fixed: orders 0xb/0xc call `FUN_00425084` before planning the charge state: the carried object is dropped or credited first (`game_session_order_floater_to_charge_site`).
- Fixed: the end of an automatic order (`FUN_00421ec1(-1)` + `FUN_00466533`) clears the flag group `0x65`, not only `0x04` (`game_session_advance_category4_autonomous_order`).
- Still not ported: actions 2/0x11 (no emitter in the port), the "object already carried" branch of action 0xd, delivery sub-steps, return to the Hall of subtypes 4/8 as a common block, rejection of an order outside the owner's range, step blocking by `0x01`/`0x400`.

### Recharge producer (state 2): `FUN_0042219e`, linked-floater branch (re-read: `ev_7b65b088`, `FUN_0045ddb8` `ev_95bce0a0`, `FUN_0045de20` `ev_72655553`, `FUN_0045dd3c` `ev_e33131f1`, `FUN_00420f28` `ev_309dc553`)

No emitter of action 2 in the port (the receiver `delivery.c`, `recharge_order`, exists). Native, for a non-category-4 floater with a linked building (`+0xc != -1`), without flag `0x10` (otherwise `FUN_00421d82`):
1. if this floater is the building's "current" floater (`record+0x4c == index`) and does not have flag `0x20`, order `0xc` to the building (island/site of the record), then end;
2. otherwise, if it is already in state 2 with flag `0x01` (on arrival), it stays;
3. otherwise compute the needs: max HP `FUN_00420f28` (pad row `+6`, level formula, +1 subtype 0 with glyph bit `0x10`, ×5/4 with glyph bit and source `0x2c/0x2d/0x2e`) and max charge (pad row `+8`). Thresholds: `maxHP` and `max charge`, or their third if `FUN_0045de20() == 0` (i.e. order 9 to the source cell on the source island, within 0x14), or 1 and `HP/3` for non-initial orders 6, 7, 8/9. Heal (`+0x44 = 0`) if `HP < threshold` and `maxHP <= HP + building stock+0x2a` (`FUN_0045dd3c`, the 0x1000 glyph test there is unreachable: three simultaneous equalities on the same identifier); otherwise recharge (`+0x44 = 1`) if `charge < threshold` and `max charge <= charge + stock+0x2a`. Order 2 to the building (`+0x30/+0x42` = island/site, `+0x44` = 0/1);
4. otherwise copy the order of the building's record (6 to 9), except action `0x13`.
Arrival (case 1 of `FUN_0041e569`): flag 1 then 10 wait ticks, then each cycle consumes 1 point of `stock+0x2a` (`FUN_0045ddb8(1)`, ×4/3 never active) for +1 HP (`+0x44 == 0`) or +1 charge; stops when nothing is due or stock runs out. Not ported: depends on the building-record model (`record+0x4c`, island/site of the record) which does not exist in the port.

### Out-of-range rejection (`FUN_00423068`, `ev_f59cd438` lines `0x4235e2..0x423611`)
Fixed for the approach states 0xf/0x10: if the x of the arrival point is outside the owner's `[min, max]` (0 and 0x9ff by default, category 4 free), the order is cancelled as `FUN_00421ec1(-1)` (flags `0x65` cleared, return to wandering) instead of being followed. The other states (3/4 delivery, 9 coordinate) do not check this bound yet.

### Task table (re-read: `FUN_004662b7` `ev_1a99fa08`, `FUN_00422031` `ev_bd805382`; agent review for the rest)

- Fixed: the duplicate detection of `FUN_004662b7` (types 5 and 0xd) compares only player, island `+0xa`, site `+0xe` and type; the port also compared `+0xc` and the object (`+0x12`), so it accepted two rows for the same site.
- Fixed: `FUN_00422031` case 0x12 tests the carried word (`in_ECX[6]` = `+0x18`), not the subtype: a worker carrying Build Tone is eligible, otherwise an accessible Build Tone source is required. The port excluded subtype 1.
- Rework 2026-11-01 (see [worker allocation](../../../decompilation/behavior/island-tasks.md#répartition-des-ouvriers-refonte-2026-11-01)): types 6/0x11 added to the "urgent" test, invented guards (caps 20/10/SUPPLY, cost reservation, single finisher) and the island restriction on resource deliveries removed. Remaining: detaching an object row during an exchange (`FUN_00466533(old)`) not ported, `reclaim_orphaned_task_claim` kept as a guard.

### Economy (re-read: `FUN_004526de` `ev_16ab810c`; agent review for the rest)
- Fixed: a building's accessibility compares the pad's maintenance cost with the player's `+0x40` (`DAT_006191f8`, capacity minus maintenance = `source_maintenance_budget`), not the raw capacity `+0x3c`. Placement (`game_session_buildings.c`) and worker assignment (`game_session_delivery.c`) fixed; tests updated (`construction.inc`).
- Fixed: the end of a `0x100` step on an owner-4 site goes through the Leviathan recomputation like `FUN_00453a5f`.
- Remaining gaps reported (agent, not re-read): cadence of markers 6-9 guarded by `DAT_0061f8d8` (never written), strategic Leviathan-subtype branch (`DAT_0061f998` etc.), two distinct difficulty globals (`DAT_004bf11c` bounded, `DAT_00618e48`), birth fallback to the home island `+0x13c4`, defeat lock `+0x90` of `FUN_0045eaa7`, early return of `FUN_004528ca` if `FUN_0045ee26` fails for 0x2c-0x32, type-7 destruction event.

### Economy globals without a direct writer (xrefs re-read: `ev_a2281049` `0x61f8d8`, `ev_bff2cd49` `0x61f998`, `ev_87d7d29c` `0x618e48`, `ev_34709f82` `0x4bf11c`)
- `DAT_0061f8d8` (cadence guard of markers 6-9) and `DAT_0061f998` (strategic Leviathan-subtype branch) each have only one direct reference, a read (`0x451407`, `0x45198e`). Their writers are therefore indirect (block-indexed writes) and unresolved; the port keeps the `+0x32` cadence and the partial subtype selection.
- `DAT_004bf11c` (difficulty bounded 0..4 used by attack power, the Leviathan spawn threshold and `FUN_0041e569`) and `DAT_00618e48` (unbounded difficulty used by `FUN_00450a71` case 5 and the Leviathan bonus) have 11 and 14 direct read-only references; their identity remains unproven, the port uses a single value.

### Recruitment (`FUN_0045eaa7`, re-read: `ev_427930b7`)
Matches `game_session_tick_floater_recruitment`: the player's floater count, capacity `+0x3c`, budget `+0x40 > 4`, workers (subtype 0) `< capacity / 2`, timer `+0x8c` incremented then birth (`FUN_004532e2`) when `> 300`, with the birth marker `+0x13ce != -1`. Only the defeat lock `+0x90` (event 0xb or `FUN_00460072`) has no equivalent in the port; end-of-game detection belongs to the end-of-game screen under development.

### Task row choice order
Resolved 2026-11-01: the port takes the first eligible row in slot order and re-evaluates a busy worker once every ten ticks, like `FUN_0042219e`; see [worker allocation](../../../decompilation/behavior/island-tasks.md#répartition-des-ouvriers-refonte-2026-11-01).

### Subtype 8 return to the Hall (end block of `FUN_0041e569`, `ev_8578fcc7`)
Ported approximately: as soon as a subtype-8 floater goes from a nonzero state to state 0 (finished state) outside action `0x13` and outside action 9 (already toward the Hall), it receives the coordinate order to its Hall (`game_session_order_floater_home`), like the native `in_ECX[0xf] = 9`. The detector uses the tracking field `previous_movement_state`. Not ported: subtype 4 (order from the building record `DAT_006192b0`, nonexistent in the port) and the global guard `DAT_006191b4`. Not verified in game.

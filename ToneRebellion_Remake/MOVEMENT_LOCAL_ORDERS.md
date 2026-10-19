### `FA_Move`: local target approach and arrival

Action 1 (`FA_Move`) is case `0` of `FUN_004211bb`'s `order - 1` switch. When
its destination island is current (or unspecified), it sets runtime state 1,
copies task target `+0x42` to floater target `+0x32`, and sets progress
`+0x46` to `-1`. If the assigned island is remote, the shared pre-switch path
delegates to `FUN_004210a9`, which selects the local handoff site and changes
to state `0x11` (hexadecimal 17, the transit state documented below). No
continuous coordinates are integrated across islands.

Local state 1 passes the common movement gate. `FUN_00422d27` uses the normal
unit speed and resolves `+0x32` through the current island's location table;
`FUN_00423068` applies the location/state-specific anchor offset and bounds
checks before storing the pixel destination. The coordinate kernel then
advances the floater by clamped per-axis steps. When both current coordinates
equal that destination, the state handler completes state 1. A special
category-4/subtype-9 branch may also change the target location's raw fields
and call two helpers on arrival; the evidence does not identify this branch
as a general player move effect. Evidence: action consumer and island route
`ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
state tick/arrival `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
destination resolution and coordinate step
`ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
handoff `ev_dd046f002c50d0d9e841af455f3dd8fc8b70d1b11f430f2fa5c0185edc5f5121`,
and action labels `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.

### `FA_DefendFlt`: reach target, select a nearby unit, then approach it

Action 8 (`FA_DefendFlt`) is case `7`. At progress 0, the consumer enters
state `8`, copies task target `+0x42` to `+0x32`, clears flag `0x004`, and sets
progress to 1. State 8 is a follow approach with a moving offset, not direct
arrival at the target floater: `FUN_00423068` stores a random `[-100,99]` X/Y
offset, and each `FUN_00422d27` step adds the target floater's current
coordinates before applying the world-bound clamps. The same stored offset is
therefore carried along as the target moves. Effective speed changes to 1
when the two floaters' direct Chebyshev distance is below 100, regardless of
their distance from the offset waypoint. Later category/site modifiers can
still adjust that base value. The state handler can finish early
when `FUN_004208eb` finds a qualifying candidate; otherwise exact arrival at
the translated waypoint completes state 8.

While progress is 1, `FUN_004208eb` scans the current-island entity list in
order. It returns the first candidate accepted by `FUN_00420991` whose
`FUN_00420600(candidate, target)` result is below `0xfa`; it does not rank all
qualifying candidates. A match becomes target `+0x32`, changes runtime state
to `0x0f`, sets flag `0x004`, and advances progress to 2. No match resets
progress to 0 for a later retry. State `0x0f` then moves toward that entity's
current position with its state-specific anchor and stopping-radius rule.
On completion, the next consumer pass changes to state 6 and resets progress
to `-1`; state 6 no longer runs the common movement kernel. This establishes
two sequential approach phases, but not the complete combat/defense behavior
or the semantic unit classes selected by the eligibility guard. Evidence:
order consumer `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
candidate scan `ev_45e476a70f900a1cdcdfaa0a6d82ee5f2025db59a6f6005a7451f7eb7ef707e2`,
eligibility guard `ev_2b7c3a4d07a47624e5bda9eda2a57d60b965635fa529ab925962c1b77d88b010`,
state handling `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
and target resolution `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`.


Autonomous order selection and wandering are documented in [autonomous floater orders](MOVEMENT_AUTONOMOUS_ORDERS.md).

### Attack orders: approach then stationary combat state

`FUN_0042219e` can issue action 6 (`FA_AttackFlt`) or action 7
(`FA_AttackLoc`) from its candidate-selection branches. The consumer
`FUN_004211bb` turns each order into an approach state before entering its
combat state:

| Order | Initial consumer branch | Approach | Follow-up state |
|---|---|---|---|
| `6` (`FA_AttackFlt`) | Requires target index `+0x42 != -1`; calls `FUN_00425084`, sets state `0x0f`, copies target index to `+0x32`, clears counter `+0x30`, sets flag `0x004`, progress `1`. Missing target cancels the task link. | State `0x0f` resolves the target record's current coordinates and steps toward its combat-side offset; arrival uses the state radius handler. | On the next idle consumption, progress `1` changes state to `6` and progress to `-1`. State `6` is excluded from both movement and order reevaluation while active. |
| `7` (`FA_AttackLoc`) | Calls `FUN_00425084`, sets state `0x10`, copies location index `+0x42` to `+0x32`, clears counter `+0x30`, progress `1`. | State `0x10` resolves the island location at `+0x32` and moves toward its coordinate; arrival uses the state radius handler. | On the next idle consumption, progress `1` changes state to `7` and progress to `-1`. State `7` is excluded from movement and order reevaluation while active. |

The runtime states `6/7` therefore mean the approach has ended; they are not
additional travel targets. For `FA_AttackFlt`, the arrival-side code can set
flag `0x10` on the referenced entity record and `0x40` on the floater. The
exact attack cadence and the conditions that later replace or cancel these
orders remain separate from the movement path. Evidence:
order selection `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`,
order consumption `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
movement/arrival `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
and target resolution/step `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`.

For the moving approach states, the radius test is centered on the stored
approach point, not necessarily on the target entity's center. In state
`0x0f`, `FUN_00423068` normally stores an X point 43 units onto the floater's
side of its target, while the arrival handler compares current coordinates
with that stored point using the default or stat-derived radius. The resulting
radius therefore cannot be read as the maximum distance from the target
center. `FA_MergeWith` is the specific exception: it suppresses the entity
offset and forces radius zero, so the current step must land exactly on the
resolved target point (subject to the documented stale-target check ordering).
State `0x10` uses the same side-offset rule for a location target, with its
arrival radius measured around that stored location approach point. Evidence:
destination resolver `ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f`,
step and arrival handler `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
and coordinate kernel `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`.


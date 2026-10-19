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

### Autonomous order selection and execution

`FUN_0042219e` chooses/revises orders; `FUN_004211bb` consumes an order
already stored on the unit. They are separate from the coordinate step.
Evidence for the two procedures:
`ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea` and
`ev_0e9d3fbfa8df7eb8f372d0b17bc92593ddd6fc2eb7cebe7c043ca611798b4abd`.
The reevaluator returns for runtime states 6/7 and while global guard
`DAT_006191b4` is nonzero. In the regular-unit path, when flag `0x10` is clear
and the action is `FA_Nothing` or `FA_Wander`, it can scan at most 64 records
at `DAT_006183bc`. It filters active records by owner/type, excludes the
already attached record, and calls `FUN_0041e454` and `FUN_00422031` before
comparing record class/level values. It attaches a qualifying record through
`FUN_00421ec1`; if none qualifies, a unit with no attached record can receive
`FA_Wander` (`14`) with its home island as the target. Candidate field
semantics and all eligibility thresholds are not fully named. Evidence:
`ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`.

`FUN_00421ec1` is the task-link transition. Passing `-1` decrements the old
record's claimant count, clears its reference, action and runtime state; a
valid index increments the new record's count, copies its action and target
fields into the floater, clears progress/state, and releases an old attached
record when the link changes. This is the observed bridge between the task
table and an order executor, not a coordinate assignment by itself. Evidence:
`ev_c2d3e74dd2e94c30ca9de18f1387bb8d44d32daf432cd179e9d1b8dfc693b4dc`.

### `FA_Wander` destination generation and repeated movement

The periodic reevaluator can assign `FA_Wander` (`14`) with the tribe's home
island as its target when no task record is selected. The local executor in
`FUN_004211bb`, switch case `0x0d` (`action - 1`), sets runtime state `0x0e`,
sets the state timer at `+0x34` to 60, and sets progress `+0x46` to `-1`. Its
branch does not write the movement destination pair itself. The executor's
common tail calls `FUN_00423068` whenever runtime state `+0x2c` is nonzero, so
the newly entered state resolves a coordinate destination immediately.

This fallback is reachable for the initial unlinked units. `FUN_0041e4e4`
resets a newly allocated floater's flags `+0x1c` and action `+0x3c` to zero and
its task link `+0x38` to `-1`; `FUN_00466fe4` uses that reset when allocating
the starting floaters created by `FUN_0046466f`. On a state-zero tick,
`FUN_0042219e` performs the regular-unit task scan and, when the order remains
`FA_Nothing`, assigns `FA_Wander` and an island target. This grounds the
remake's initial idle-wander path, while the task-slot eligibility and
selection rules remain outside the port. Evidence: reset
`ev_a5f6ff6cbb1d9a1b23aa8807337444803e3415de869ec691acf503f150bb3523`,
allocation `ev_0ca802ac15043c61c073f6d68546619fc924a4ba10fd4d9f04e203668dc62ed7`,
initial creation `ev_ac313cb8cc73f9c102676395cd14cb97b5b1f9355d074df1e6656ce028d2d36f`,
and reevaluation `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`.

For state `0x0e`, `FUN_00423068` starts from the floater's current X/Y. It reads
the floater category's horizontal limits from the current-island record at
`DAT_005ec620 + category * 8 + islandIndex * 0x29e8`; the lower limit is used only
when positive and the upper only when below `0x9ff`, otherwise they default to
`0` and `0x9ff`. Category 4 skips those table reads and keeps the defaults. Before
adding randomness, the X center is clamped first to at least `minX + 100`, then
to at most `maxX - 100`. Two calls to `FUN_00467260(200)` then add offsets in
`[-100,99]` to that X center and the current Y. Y is clamped to
`0x28..0x122`. State `0x0e` takes the no-location-record path, which adds no
extra sprite/stance offset. The resolver accepts the candidate only if final X
is inclusively within the raw limits, then stores the pair at `+0x28/+0x2a`;
facing is updated from the candidate's horizontal direction. The center clamps
do not establish that every random candidate is in range when the two 100-unit
margins overlap; the final bounds check decides acceptance. Coordinate units
and the table limits' gameplay meaning are not fully named. The evidence does
not establish a uniform distribution, nor that a newly generated coordinate
must differ from the previous one. Evidence: resolver
`ev_d4cd7abeebb8995fafaa9f6766fac6764547a0f499b94fe2e51d82cc3411373a`.

If the final X check fails, the helper returns 0 without writing either
destination coordinate. On the `FA_Wander` dispatch path, `FUN_004211bb`'s
common tail checks this return value and cancels the task link through
`FUN_00421ec1(-1)`. Thus an out-of-bounds random X does not keep an older
destination as an active route: the coordinate fields may remain stale, but
that dispatch clears the action/state and does not retry a new random point in
the same call. The ordinary state-`0x0f`/
`0x10` arrival handler uses the same resolver-failure return to cancel its
order. Evidence: destination resolver
`ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f`, order
consumer `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
and state arrival handler
`ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`.

State `0x0e` is allowed through the common movement gate in `FUN_0041e569`.
`FUN_00422d27` consumes the stored `+0x28/+0x2a` destination and uses base step
magnitude 1 for this state before other speed/effect modifiers. The timer at
`+0x34` counts down only when the coordinate step reports exact arrival; this
state does not use the radius test documented for states `0x0f/0x10`. When the
timer expires, generic completion clears runtime state but retains the action;
the next idle dispatch can enter the executor branch again, whose common tail
resolves another destination. The reevaluator's home-island value is still an
island/task target, while the coordinate destination is generated separately
by `FUN_00423068`. Evidence:
`ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`,
`ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
`ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
and `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`.

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


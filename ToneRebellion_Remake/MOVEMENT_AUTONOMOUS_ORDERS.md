# Autonomous floater orders

## Autonomous order selection and execution

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


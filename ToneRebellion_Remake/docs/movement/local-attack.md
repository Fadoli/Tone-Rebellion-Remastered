# Movement Local Orders

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

# Enemy AI and autonomous unit behavior

## Control domain and Leviathan category

### `vspore` behavior in detail
### `vspore` behavior in detail

The Spore is not an ordinary attacker. Its active `floater.txt` row gives it 4 hit points and zero attack points/strength. Its dedicated controller branch never issues `AttackFlt` or `AttackLoc`; it searches for an island location to convert, then removes the Spore as part of a successful conversion. **Gameplay interpretation supplied by the user:** Vspores act as enemy building constructors. A successful contamination can turn a basin slot into a new enemy source, or contaminate a building slot so the enemy can build a building there. This meaning comes from the user's gameplay observation; the binary analysis below establishes the selection/conversion mechanics, but does not yet map raw record values to “basin” versus “building slot.”

1. **Reevaluation cadence.** In `FUN_0041e569`, a floater in runtime state 0 runs the reevaluator every update; other states run it when `(DAT_00618e44 + floaterIndex) % 10 == 0`. The world loop iterates each live floater. This is the observed scheduling gate; the counter-to-seconds conversion is still unknown. Evidence `ev_ff0149927c5527e42ad97c0ccb0ecff046537edadb26eb9fecf60e1403b49d28`, `ev_e5317b46de61b404289fc8556d81824a35484a01520435d6ee10035e913c95e0`.
2. **Site search.** `FUN_00420d97` supplies the Spore's current island to `FUN_00420a55`. Mode 2 scans that island's location records and accepts a record if its `+0x04` field equals 1 or 0, and either its `+0x14` field is -1, or both its `+0x10` and `+0x24` fields equal 1. These are raw record offsets; their source-level names are not established. The controller asks for the value-1 and value-0 candidate sets separately. Evidence `ev_2d5d4353c4c551b2a2466b6ea1e94e34b62fe0ef86797db366eca77c4a38fb4f`, `ev_a866192475a173af42b9578146770a81c2566ffbebf76d51ae9e9aed96d266d9`.
3. **Target preference.** Each set is scored by `FUN_00420635`, which calls the Chebyshev-distance helper (`max(abs(dx), abs(dy))`). The selector keeps the ten lowest-scoring eligible records; `FUN_0041e28e` then makes a weighted random choice using inverse-score weights, so nearer records get greater probability without always choosing only the nearest. By default the value-0 target is used. A value-1 target replaces it when the per-island `DAT_0061f9d4` counter is positive and either `DAT_0061f9b6` is zero, the value-0 set is empty, or `FUN_00467260(4)` returns zero. The counters' game meanings remain unknown. Evidence `ev_8abb08fe878eeb4b95b90b95aa69f3315b673dc32d5016dbd3cf3274f4ac8493`, `ev_d6e45300f5ee5de4ed13ebfa3da2e5198981b6af36bc072d956c795033a50243`, `ev_2f27ef00567b68d5a8d3ffd44f86f6a060dead0acebb0b98c93fd7e2b36b128b`, `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`.
4. **Order persistence and conversion.** With a selected location, the Spore cancels its old order (`FUN_00421ec1`) and writes `FA_Move` (1), the current island, the selected location index, and progress 0. While that target's `+0x14` field remains -1, the reevaluator returns early and preserves the move order. The action executor enters runtime state 1; the floater update then checks the indexed location record. When the arrival/result path runs, if that record has `+0x04` equal to 0 or 1 and `+0x10` equal to 0 or 1, the controller checks flag `0x200` in the location's `+0x1c` flags. If clear, it changes the location's `+0x14` field to 4, clears flag bit 1, triggers `FUN_00453a5f`, and removes the Spore with `FUN_00467101`. The binary therefore confirms a location conversion to category/type 4. The gameplay meaning supplied by the user identifies the converted sites as either basin slots that become new enemy sources or building slots for enemy construction. The mapping between those two target kinds and the raw `+0x04`/`+0x10` values remains unverified. If flag `0x200` is set, it applies damage equal to the Spore's current HP, killing it instead of converting the location. Evidence `ev_ff0149927c5527e42ad97c0ccb0ecff046537edadb26eb9fecf60e1403b49d28`, `ev_0e9d3fbfa8df7eb8f372d0b17bc92593ddd6fc2eb7cebe7c043ca611798b4abd`, `ev_2a1c3b1da3138e27e5625c59da85fe4e4c611b4d336273c83c488795cc55c6b7`, `ev_6745ea13e551cd4bc25dc59c623fb7adf0a818c613fdb948c7f4b034a74cac52`.
5. **No-target decay.** If both searches return no candidate, the controller clears the current order. Whenever `(DAT_00618e44 & 0x7f) == 0`, it subtracts 1 HP with `FUN_004204bc(1, -1)`. The `-1` source means this damage is not attributed to a player in that helper. At 4 HP, four such no-target damage events are enough to trigger the normal death flag/removal path, absent other effects. This is an event-count statement, not a real-time lifespan estimate. Evidence `ev_6745ea13e551cd4bc25dc59c623fb7adf0a818c613fdb948c7f4b034a74cac52`, `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`.

For category 4 subtype IDs 10–17, the reevaluator acts only when flag `0x10` is clear and the existing action is `FA_Wander` (14) or `FA_Nothing` (0). It scans current-island candidate records with `FUN_00420991`, retains a candidate whose score from `FUN_00420600` is below 150, or below 3000 when flag `0x80` is set, and asks candidate mode 3 for another target under that bound. If a scanned candidate exists and `FUN_00467260(3)` returns 0, the mode-3 target is discarded. The direct candidate is then issued as action 6 (`AttackFlt`); otherwise the mode-3 result is issued as action 7 (`AttackLoc`). Both writes set the target island to the floater's current island. With flag `0x10` set, this branch delegates to `FUN_00421d82`, a distinct same-island auto-engage path. These action labels are established by the action table; candidate classes and the precise tactical intent of the score thresholds remain partly unresolved. Evidence `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`, `ev_0e9d3fbfa8df7eb8f372d0b17bc92593ddd6fc2eb7cebe7c043ca611798b4abd`.

`FUN_00460460` recalculates per-island counts for location records whose type field is 4, counts existing Leviathan floaters other than subtype 9, and writes interval-like values at `+0x45a` in those island location records. That `+0x45a` value is a location-record timer, not a floater field. The function is called around category-4 floater creation/removal and can recalculate every island. `FUN_00460989` consumes the island summary/countdown and, on its timer path, sets flag `0x80` on a selected number of existing non-Spore Leviathans; that flag widens their reevaluation threshold from 150 to 3000. This connects Spore-created type-4 locations to Leviathan population/balance logic. The user's observation further clarifies the resulting gameplay: a contaminated basin slot can become a new enemy source, while a contaminated building slot supports enemy building construction. The exact timer purpose, which type-4 sites feed which production/building path, and the full spawn/production chain are not recovered from static analysis. Evidence `ev_f6fad36a24d0df23600189218f8f97cf25c8ae1078856cf1f0526c0fd092aedd`, `ev_51318b865289347ea016897f2f58125ee6479e16683f3d13844fb280a52d10df`.

The four regular tribes and Leviathan entity setup feed into the same world simulation architecture. New-game command `FUN_004121b7` handles player add/remove, alliance/team bits, world size, difficulty, and game start. On game start it calls `FUN_004637fc(worldSize, difficulty, ...)`, which stores the difficulty at world-object offset `+0x2cc30`, initializes island data, and seeds starting locations/floaters. It also calls `FUN_0046466f` and `FUN_00464b9e` for tribe setup. Difficulty's other known consumers include damage/death chance, recruiter staffing preferences, and score contribution; those are discussed below and are not evidence of a separate enemy-AI subsystem.

---

# Enemy AI and autonomous unit behavior

## Candidate selection

`FUN_00420a55` scans the current island's location records. Its `param_2` selects one of five filters (0–4); qualifying candidates are scored by `FUN_00420635`, at most ten are retained, and `FUN_0041e28e` selects the returned candidate. `FUN_00420d97` is a wrapper that supplies the floater's current island. Evidence `ev_76a4661cb67067b44054706649c3ff1f80a7e9eec7116d8c36177f340ab15b36`, `ev_0a150ef6299ccee55e14aeab45e2de16381b5142b4063cda099503d87e818883`; details in [the function notes](../../functions/0010_batch_0006.md#fun_00420a55--0x420a55).

Observed filters include:

- Mode 0: calls a candidate/eligibility helper using the requested value and candidate record.
- Mode 1: admits every scanned record to the scoring step.
- Mode 2: checks candidate fields against a requested owner/value and status fields.
- Mode 3: requires owner field at record offset `+0x04` to be 0, excludes class 4 at `+0x14`, limits the type/item field at `+0x10` to `0x25 < value < 0x35` while excluding `0x2a`, then requires the score to be below the supplied threshold.
- Mode 4: requires the field at record offset `+0x14` to equal 4, a measured distance below `0x5a`, the field at `+0x10` below `0x16`, and no bits from mask `0x90` in the flags at `+0x1c`.

In `FUN_0042219e`, some callers use modes 2, 3, or 4 with additional context. The Leviathan branch writes action 6 or 7 (AttackFlt or AttackLoc); other call paths use these modes for different branches. Candidate field semantics and target priorities remain partly unresolved, so the order labels do not justify more specific tactical names such as "raid" or "retreat".

Another `FUN_0042219e` path consults a 64-record table at `DAT_006183bc`. It checks active records whose owner field matches the unit, excludes the record already attached to the unit, and calls `FUN_0041e454` and `FUN_00422031` before accepting a record. The selection compares record classes and numeric values, with different inequalities depending on the unit's current values. It then passes the selected record index to `FUN_00421ec1`; if no task is selected, a unit without an attached task can be assigned `FA_Wander` (14) and the owner's home island. The record-field meanings and selection values are still partly opaque.

`FUN_00420991` is another candidate guard used by the reevaluator. It rejects the current object and candidates whose flags match mask `0x809`; for class 4 it consults a level threshold table, while other classes pass only under same-class or per-player table conditions. This is evidence of class/level eligibility, but not enough to name a soldier/mage allowlist or an attack rule. Evidence `ev_b758701979d34e447f00b2067f67d58c0c58d9b8c28b444e24dfd4a160713da5`.

---

# Enemy AI and autonomous unit behavior

## Staffing and production assignment

`FUN_00460072` is a separate per-tribe assignment routine. For pending feature bits it visits islands and assigns two eligible staff slots per matching feature using bounded random selection. It then walks item IDs 5 through `0x21`; for each outstanding desired count it picks an eligible unassigned slot, writes the item ID to the slot's `+0x44c` field, and decrements the desired count. Eligibility checks fields `+0x42c`, `+0x43c`, and `+0x44c`; zero status at `+0x438` is initialized to 1. Evidence `ev_1d0bd9feec2d7550ea50129522ad783374e97af92bb6dd9bebd24510c185aedf`; detailed pseudocode in [the function note](../../functions/0017_batch_0013.md#fun_00460072--0x460072).

This proves automatic staffing/type assignment. The routine's trigger and its relationship to a computer-controlled tribe remain unresolved; it should not yet be treated as CPU-only strategy.

---

# Enemy AI and autonomous unit behavior

## Combat-related data is not combat policy

The local game data and parsers expose combat inputs:

- `floater.txt` has 45 records with drawing ID, attack range, attack realm, hit points, maximum attack points, strength, and speed (`FUN_004633a7`; [data catalog](../../data_catalog.md)). These values bound what unit types can do, not which target an opponent chooses.
- `fltinf.txt` is parsed into records with fields named `hover`, `pickup`, `carry`, `attack`, `atteff`, `graspxy`, and `attxy` (`FUN_00454d1f`; [data catalog](../../data_catalog.md)). These establish attack-related animation/effect/position metadata; the numeric field meanings and their use by a target-selection routine remain incomplete.
- `spells.txt` supplies spell title, level, magic cost, cry cost, and text (`FUN_00463563`). `effects.txt` defines effect records, including effect types such as bullet, lightning, impact, cast, and sound-only. These prove spell/effect resources and costs exist, not that a CPU routine selects or casts them autonomously.

The `FA_*` table anchors written order IDs, while the separate `BC_*` strings remain command/control vocabulary and do not establish AI behavior. Seeing `FA_AttackFlt` or `FA_AttackLoc` establishes the issued order label; target priority and behavioral intent still depend on the candidate checks and order executor.

---

# Enemy AI and autonomous unit behavior

## Reimplementation guidance

Port the verified autonomous-unit mechanisms as simulation behavior with source-derived state transitions:

1. Preserve the per-unit order, state, island, target, and progress fields as separate fields; do not collapse them into one "AI state" until their independent writes are traced.
2. Keep candidate filters separate by mode and preserve the scan order, score function, ten-candidate cap, and chooser semantics once `FUN_0041e28e` is fully understood.
3. Make the reevaluation cadence follow the observed per-unit update; keep time scaling configurable until the game's tick/frame conversion is resolved.
4. Model regular tribe floaters and `FT_Leviathan` through their shared update loop, with category-specific order branches kept separate; do not merge Leviathan's population/replenishment logic into an individual floater's order state.
5. Preserve random-call order when porting any branch that uses `FUN_00467260`; it shares the game's LCG and affects deterministic initialization/behavior.

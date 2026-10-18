# Enemy AI and autonomous unit behavior

## Scope and conclusion

This is a static analysis of `FLOAT.EXE` 1.16F with Ghidra 12.1.4. The game was not executed. Ghidra pseudocode is a reconstruction, and field names below are descriptions of access patterns rather than recovered source names.

Scope here is autonomous control of hostile units across the four tribes and the Leviathan on the world map, rather than a separate empire-level opponent planner. The executable updates active floaters through one shared simulation loop; per-unit order reevaluation and order execution are the core control points. Leviathan has its own recognized category and special branches. The action-label table is now recovered; candidate target semantics, attack/cast policy, and tick-to-seconds cadence remain incomplete.

| Question | Status | What the evidence supports |
|---|---|---|
| Does one loop update the units across planets? | Answered | The world simulation walks a 256-slot active floater table and updates each live record; the floater stores its current island separately. |
| How are candidate targets chosen? | Partially answered | Five candidate filters, a score helper, a ten-entry shortlist, and a final chooser are visible. Leviathan writes Move, AttackFlt, and AttackLoc orders; target-type meanings and priority rules remain incomplete. |
| Where is per-unit control? | Answered | `FUN_0042219e` reevaluates an individual floater's orders and `FUN_004211bb` advances them; both run from `FUN_0041e569` inside `FUN_00466ce2`. |
| What is special about Leviathan units? | Answered for order reevaluation | The binary names `FT_Leviathan`; category 4 has IDs 9–17. ID 9 (`vspore`) is handled separately. IDs 10–17 share a second reevaluation branch, despite using eight different unit data/animation records. |
| Is mode 4 an attack selector? | Unresolved | Mode 4 selects nearby class/type-eligible objects. The caller context does not prove that it is attack selection. |
| What does the difficulty setting affect? | Partially answered | It is stored during world construction and also feeds a damage/death probability path, recruiter staffing preferences, and the score formula. The exact per-unit balance effect still needs to be isolated. |
| What is the update rate in seconds? | Unresolved | The routines are reached from the simulation update, but frame/timer conversion to a real-time interval is not proven here. |

## Update and decision flow

1. `FUN_0041c46f` is the application loop. Its documented call sequence includes `FUN_00466ce2` (`[main loop notes](../functions/0004_main_loop.md)`, Evidence `ev_a3a1136454b116409a3a18908d27e23488bf809cdcb8d28b4d4d0805f05688e3`).
2. `FUN_00466ce2` performs world updates, drains queued world actions through `FUN_00466221`, then iterates active floater records and calls `FUN_0041e569`. The iteration is bounded by a 256-slot table and the active count. It also calls the Hall/task update helper four times and advances timers and simulation counters. Evidence `ev_b51f2311ff9bd9ad209f0663ea00bfe330e7ff0eff117e8a273292d3112a4e0e`; details in [the function note](../functions/0017_batch_0013.md#fun_00466ce2--0x466ce2).
3. `FUN_0041e569` is the per-floater update. It calls both `FUN_004211bb` and `FUN_0042219e` among movement, animation, task, and state helpers. It handles movement states `0x0e/0x0f` through the coordinate step routine `FUN_00422d27`; the step advances each axis toward a target and reports arrival only when both coordinates match. Evidence `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`, `ev_0a3a5baa3dd85e9e4d8e576461b4c0ac5dde6dd1cb0ba6135191f046f1f98a93`.
4. `FUN_004211bb` consumes an existing order. It branches on the action field at `+0x3c` and progress/state fields, calls destination/candidate helpers, advances unit state, sets target fields, or cancels an order through `FUN_00421ec1`. It is an order executor, distinct from the action chooser in the reevaluator. Evidence `ev_0e9d3fbfa8df7eb8f372d0b17bc92593ddd6fc2eb7cebe7c043ca611798b4abd`; details in [the function note](../functions/0010_batch_0006.md#fun_004211bb--0x4211bb).
5. `FUN_0042219e` reevaluates a unit's order and conditions. It returns immediately for runtime states 6 or 7 and while the global guard `DAT_006191b4` is nonzero. Otherwise it has category/subtype branches that search candidates, compare scores and unit thresholds, and write action, island, target, and progress fields. For Leviathan it writes `FA_Move`, `FA_AttackFlt`, or `FA_AttackLoc`; regular-unit branches include `FA_AttackFlt`, `FA_Train`, `FA_Recharge`, and `FA_Wander`. Evidence `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`; details in [the function note](../functions/0010_batch_0006.md#fun_0042219e--0x42219e).

These calls locate the verified unit-level decision logic: it is interleaved with each floater update, rather than being an independently scheduled per-player routine. The resolved direct-caller query for `FUN_0042219e` returned no entries (Evidence `ev_2d79f304365a3c8484b4cf08c48a252a5a1bef7bc030214046ea9ada686a468e`); its known link comes from the update function's thunk call. Indirect dispatch and callbacks may contain more behavior than the resolved graph exposes.

## Four-tribe unit behavior

The reevaluator has distinct branches for category-4 Leviathan and the regular tribe floaters, with further special handling keyed by subtype, task-reference field, current order, runtime state, and flags. The regular-unit behavior visible in `FUN_0042219e` is not one universal “enemy order” policy:

- Some active per-island/category condition in `DAT_005eebd4` makes eligible units scan candidate records through `FUN_00420991`, select the lowest `FUN_00420600` score, and issue `FA_AttackFlt` (6). If the current action is already 6, that branch returns without replacing its target. The selector scans candidates associated with the floater's current island.
- Outside that condition, an existing attack order may be canceled, and runtime state 4 suppresses further reevaluation for that call. Units with an attached record reference (`+0x38`) call `FUN_0041e454` and can return early if the record is still active. Otherwise the controller checks up to 64 task records in `DAT_006183bc`, applies owner/class/level comparisons, and either assigns a task record with `FUN_00421ec1` or falls back to `FA_Wander` (14) at the tribe's home island.
- A unit with a non-null reference to its current object/task record may be matched to the current selected record (`FUN_004207f2`). Flag `0x10` routes it through `FUN_00421d82`; another branch assigns `FA_Train` (12) under a `0x20` gate. The same area compares unit values with thresholds returned by helpers and may assign `FA_Recharge` (2). Field identities and threshold units are not fully established, so these are described as record/state responses rather than named morale or resource policies.
- Flag `0x10` also routes the non-spore Leviathan subtype path through `FUN_00421d82`, which selects a same-island eligible peer/candidate and writes `FA_AttackFlt` (6). This shared helper appears to implement a reactive engage order, but its exact trigger semantics still need field-level tracing.

This describes logic common to the global unit controller and its observed regular-unit branches. It does not establish that every regular floater is autonomous at all times: player orders, persistent task records, runtime states, and global pause/guard conditions can all control whether reevaluation changes a unit's order. Main reevaluator evidence: `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`.

## Control domain and Leviathan category

The floaters are not partitioned into separate AI and player update engines in the observed world tick. `FUN_00466ce2` iterates live entries in the global 256-slot floater table and calls the same `FUN_0041e569` update for each; that record carries its current island separately. This is the verified cross-planet control path for autonomous and commanded units alike. The reevaluator then branches on the unit's category/subtype and existing state.

Leviathan's code-facing category is `FT_Leviathan`. `FUN_00462a87` accepts categories 0–4, applies a separate cap to category 4, and calls the floater allocator. `FUN_00466fe4` clamps category-4 subtype IDs to 9–17; other categories clamp to 0–8. The allocator stores those values in the first two 32-bit floater fields, which are the category and subtype tested by the reevaluator. Evidence `ev_c974d07fcb30c38e1877ded7ce0c55f3836351c174b39ab3d49ad7e07cf39d1a`, `ev_fd05027dd8dfa2720031c58c1dfbd4ddc7a335d8b87ce01675e83b1b460a7991`.

### Leviathan subtype table

The local `floater.txt` has nine active records in the Leviathan block. This order aligns with subtype IDs 9–17: the allocator clamps to that range, and the name display indexes `xSpores` with `(subtype - 9) * 2 + variant`; the names parser loads exactly 18 entries. Thus the record/name-to-ID mapping is strongly supported, though the data format itself does not spell out numeric IDs on each row. `FUN_00464242` separately maps category 4 into a contiguous type-info range beginning at index 27. The reevaluator does not branch separately for IDs 10–17.

| Category-4 subtype | Data item / display names | Active combat stats (`range, realm, hp, max attack, strength, speed`) | Per-unit AI distinction in `FUN_0042219e` |
|---:|---|---|---|
| 9 | `vspore` / Spores, Spores | `0, 0, 4, 0, 0, 1` | Dedicated branch; mode-2 selection, action 1 (Move), periodic damage fallback if no target. |
| 10 | `vpc` / Rakalingus, Broontilingus | `0, 0, 16, 10, 4, 2` | Shared IDs 10–17 branch. |
| 11 | `vpr` / Zeeth, Keth | `130, 0, 11, 10, 4, 2` | Shared IDs 10–17 branch. |
| 12 | `vsc` / Drack, Nadrack | `0, 1, 13, 10, 3, 3` | Shared IDs 10–17 branch. |
| 13 | `vsr` / Guêpe du Tone, Sasp | `140, 1, 8, 10, 3, 3` | Shared IDs 10–17 branch. |
| 14 | `vec` / Ronth, Varnth | `0, 2, 14, 10, 5, 4` | Shared IDs 10–17 branch. |
| 15 | `ver` / Metha, Koalint | `150, 2, 9, 10, 4, 3` | Shared IDs 10–17 branch. |
| 16 | `vnc` / Zwacker, Zwaup | `0, 3, 15, 10, 3, 3` | Shared IDs 10–17 branch. |
| 17 | `vnr` / Shandi, Flindex | `160, 3, 10, 10, 5, 2` | Shared IDs 10–17 branch. |

The stat column is the active six-value record in `floater.txt`; `fltinf.txt` supplies separate hover/attack-animation data and should not be conflated with AI priority. The names are two alternatives indexed per subtype by the display routine. The data rows distinguish attack ranges/realms and strength/speed, while the observed order reevaluator keeps all eight non-spore subtypes in the same branch. Local source evidence: `C:\git\ToneRebellion_Raw\original_content\floater.txt`, `fltinf.txt`, `names.txt`; parser `FUN_0041d70d` evidence `ev_d6c275efa826bd914507bd53c4c3f4d979737f6bb54430df661e8609724bd78d`.

### Action IDs and the Leviathan decision branch

The strings `FA_Nothing` through `FA_Ascend` are contiguous at addresses `0x49d0b8` through `0x49d208` in 0x10-byte steps. UI/debug procedures `FUN_0044338b` and `FUN_00435f4d` form the label address as `FA_Nothing + action*0x10` for the floater field at `+0x3c`; they separately use `+0x2c` for the current runtime state. Therefore these are action/order IDs, not runtime-state IDs. String inventory evidence `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`; label use in `FUN_0044338b` evidence `ev_5f9c5a49a60617354d8ad7505c83964ab1f03b05faeb5ac50e17dde56b5c584a`.

| ID | Action label | ID | Action label |
|---:|---|---:|---|
| 0 | `FA_Nothing` | 11 | `FA_Enlist` |
| 1 | `FA_Move` | 12 | `FA_Train` |
| 2 | `FA_Recharge` | 13 | `FA_ObtainObject` |
| 3 | `FA_Fetch` | 14 | `FA_Wander` |
| 4 | `FA_Deliver` | 15 | `FA_ChaseFlt` |
| 5 | `FA_Build` | 16 | `FA_ChaseLoc` |
| 6 | `FA_AttackFlt` | 17 | `FA_UseBridge` |
| 7 | `FA_AttackLoc` | 18 | `FA_Repair` |
| 8 | `FA_DefendFlt` | 19 | `FA_Cast` |
| 9 | `FA_DefendArea` | 20 | `FA_MergeWith` |
| 10 | `FA_Wait` | 21 | `FA_Ascend` |

`FUN_0042219e` returns before reevaluation for runtime states 6 or 7, and while global guard `DAT_006191b4` is active. For a category-4 subtype 9 floater, it asks candidate mode 2 for values 1 and 0. If a candidate is selected under the separate per-island counter/RNG condition, it cancels the prior order and writes action 1 (`Move`) with the selected target. If there is no target, it calls the damage helper with argument 1 when `(DAT_00618e44 & 0x7f) == 0`; this is a periodic fallback keyed to a global simulation counter. The two mode values and counter tables are observed; their semantic meaning is not fully decoded.

For category 4 subtype IDs 10–17, the reevaluator acts only when flag `0x10` is clear and the existing action is `FA_Wander` (14) or `FA_Nothing` (0). It scans current-island candidate records with `FUN_00420991`, retains a candidate whose score from `FUN_00420600` is below 150, or below 3000 when flag `0x80` is set, and asks candidate mode 3 for another target under that bound. If a scanned candidate exists and `FUN_00467260(3)` returns 0, the mode-3 target is discarded. The direct candidate is then issued as action 6 (`AttackFlt`); otherwise the mode-3 result is issued as action 7 (`AttackLoc`). Both writes set the target island to the floater's current island. With flag `0x10` set, this branch delegates to `FUN_00421d82`, a distinct same-island auto-engage path. These action labels are established by the action table; candidate classes and the precise tactical intent of the score thresholds remain partly unresolved. Evidence `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`, `ev_0e9d3fbfa8df7eb8f372d0b17bc92593ddd6fc2eb7cebe7c043ca611798b4abd`.

`FUN_00460460` maintains per-island counters for records with category/field value 4 and updates a related value on selected Leviathan records, including different timing when a record is in state 5. It is called during Leviathan creation/removal and when all-island recalculation is requested, so this is population/balance management around Leviathan units in addition to their per-unit orders. The exact meaning of each counter is not recovered. Evidence `ev_ad1aa5bd37eab79a04b547da8da8b4a555823e2af399386e8059d2bf990be2bf`.

The four regular tribes and Leviathan entity setup feed into the same world simulation architecture. New-game command `FUN_004121b7` handles player add/remove, alliance/team bits, world size, difficulty, and game start. On game start it calls `FUN_004637fc(worldSize, difficulty, ...)`, which stores the difficulty at world-object offset `+0x2cc30`, initializes island data, and seeds starting locations/floaters. It also calls `FUN_0046466f` and `FUN_00464b9e` for tribe setup. Difficulty's other known consumers include damage/death chance, recruiter staffing preferences, and score contribution; those are discussed below and are not evidence of a separate enemy-AI subsystem.

## Candidate selection

`FUN_00420a55` scans the current island's location records. Its `param_2` selects one of five filters (0–4); qualifying candidates are scored by `FUN_00420635`, at most ten are retained, and `FUN_0041e28e` selects the returned candidate. `FUN_00420d97` is a wrapper that supplies the floater's current island. Evidence `ev_76a4661cb67067b44054706649c3ff1f80a7e9eec7116d8c36177f340ab15b36`, `ev_0a150ef6299ccee55e14aeab45e2de16381b5142b4063cda099503d87e818883`; details in [the function notes](../functions/0010_batch_0006.md#fun_00420a55--0x420a55).

Observed filters include:

- Mode 0: calls a candidate/eligibility helper using the requested value and candidate record.
- Mode 1: admits every scanned record to the scoring step.
- Mode 2: checks candidate fields against a requested owner/value and status fields.
- Mode 3: requires owner field at record offset `+0x04` to be 0, excludes class 4 at `+0x14`, limits the type/item field at `+0x10` to `0x25 < value < 0x35` while excluding `0x2a`, then requires the score to be below the supplied threshold.
- Mode 4: requires the field at record offset `+0x14` to equal 4, a measured distance below `0x5a`, the field at `+0x10` below `0x16`, and no bits from mask `0x90` in the flags at `+0x1c`.

In `FUN_0042219e`, some callers use modes 2, 3, or 4 with additional context. The Leviathan branch writes action 6 or 7 (AttackFlt or AttackLoc); other call paths use these modes for different branches. Candidate field semantics and target priorities remain partly unresolved, so the order labels do not justify more specific tactical names such as "raid" or "retreat".

Another `FUN_0042219e` path consults a 64-record table at `DAT_006183bc`. It checks active records whose owner field matches the unit, excludes the record already attached to the unit, and calls `FUN_0041e454` and `FUN_00422031` before accepting a record. The selection compares record classes and numeric values, with different inequalities depending on the unit's current values. It then passes the selected record index to `FUN_00421ec1`; if no task is selected, a unit without an attached task can be assigned `FA_Wander` (14) and the owner's home island. The record-field meanings and selection values are still partly opaque.

`FUN_00420991` is another candidate guard used by the reevaluator. It rejects the current object and candidates whose flags match mask `0x809`; for class 4 it consults a level threshold table, while other classes pass only under same-class or per-player table conditions. This is evidence of class/level eligibility, but not enough to name a soldier/mage allowlist or an attack rule. Evidence `ev_b758701979d34e447f00b2067f67d58c0c58d9b8c28b444e24dfd4a160713da5`.

## Staffing and production assignment

`FUN_00460072` is a separate per-tribe assignment routine. For pending feature bits it visits islands and assigns two eligible staff slots per matching feature using bounded random selection. It then walks item IDs 5 through `0x21`; for each outstanding desired count it picks an eligible unassigned slot, writes the item ID to the slot's `+0x44c` field, and decrements the desired count. Eligibility checks fields `+0x42c`, `+0x43c`, and `+0x44c`; zero status at `+0x438` is initialized to 1. Evidence `ev_1d0bd9feec2d7550ea50129522ad783374e97af92bb6dd9bebd24510c185aedf`; detailed pseudocode in [the function note](../functions/0017_batch_0013.md#fun_00460072--0x460072).

This proves automatic staffing/type assignment. The routine's trigger and its relationship to a computer-controlled tribe remain unresolved; it should not yet be treated as CPU-only strategy.

## Combat-related data is not combat policy

The local game data and parsers expose combat inputs:

- `floater.txt` has 45 records with drawing ID, attack range, attack realm, hit points, maximum attack points, strength, and speed (`FUN_004633a7`; [data catalog](../data_catalog.md)). These values bound what unit types can do, not which target an opponent chooses.
- `fltinf.txt` is parsed into records with fields named `hover`, `pickup`, `carry`, `attack`, `atteff`, `graspxy`, and `attxy` (`FUN_00454d1f`; [data catalog](../data_catalog.md)). These establish attack-related animation/effect/position metadata; the numeric field meanings and their use by a target-selection routine remain incomplete.
- `spells.txt` supplies spell title, level, magic cost, cry cost, and text (`FUN_00463563`). `effects.txt` defines effect records, including effect types such as bullet, lightning, impact, cast, and sound-only. These prove spell/effect resources and costs exist, not that a CPU routine selects or casts them autonomously.

The `FA_*` table anchors written order IDs, while the separate `BC_*` strings remain command/control vocabulary and do not establish AI behavior. Seeing `FA_AttackFlt` or `FA_AttackLoc` establishes the issued order label; target priority and behavioral intent still depend on the candidate checks and order executor.

## Reimplementation guidance

Port the verified autonomous-unit mechanisms as simulation behavior with source-derived state transitions:

1. Preserve the per-unit order, state, island, target, and progress fields as separate fields; do not collapse them into one "AI state" until their independent writes are traced.
2. Keep candidate filters separate by mode and preserve the scan order, score function, ten-candidate cap, and chooser semantics once `FUN_0041e28e` is fully understood.
3. Make the reevaluation cadence follow the observed per-unit update; keep time scaling configurable until the game's tick/frame conversion is resolved.
4. Model regular tribe floaters and `FT_Leviathan` through their shared update loop, with category-specific order branches kept separate; do not merge Leviathan's population/replenishment logic into an individual floater's order state.
5. Preserve random-call order when porting any branch that uses `FUN_00467260`; it shares the game's LCG and affects deterministic initialization/behavior.

## Next evidence to chase

- Resolve the relationship between per-unit category, owning tribe, and planet/island fields; `FUN_0042219e` and candidate filters use several independent records.
- Trace all writers/readers of the per-player tables consulted by `FUN_00420991` and the state/target fields written by `FUN_0042219e`.
- Resolve candidate mode-2 argument meanings, candidate record semantics, and the counters governing subtype 9's Spore movement/damage fallback.
- Trace attack/`atteff`/`attxy` consumers, damage/death transitions, and spell creation from the floater update and effect manager.
- Trace regular-unit attached task records and the shared flag-`0x10` auto-engage helper through the record and flag writers.
- Trace `FUN_00460460`'s per-island category-4 counters and connect them to Leviathan spawn/replenishment behavior.
- Trace the difficulty global `DAT_004bf11c` and world field `+0x2cc30` readers beyond the currently identified damage, recruiter-preference, and score paths.

## Evidence limits

The focused pass used the existing Ghidra 12.1.4 static analysis of `FLOAT.EXE`, PE x86 SHA-256 `bb229d7f09c88caf4dc1825c00b957961c22c201cf1a8dd8139bf6f4599ff28c`. Whole-program indexing records 2,410 recognized procedures and 2,209 defined strings; this does not prove that every code region, indirect call, or undefined/packed string was recovered. No runtime observation was performed. `Float.pdb` is referenced in PE metadata, but its availability/load state is unknown; no original names or types are inferred from a PDB.

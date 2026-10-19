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

---

# Enemy AI and autonomous unit behavior

## Update and decision flow

1. `FUN_0041c46f` is the application loop. Its documented call sequence includes `FUN_00466ce2` (`[main loop notes](../../functions/0004_main_loop.md)`, Evidence `ev_a3a1136454b116409a3a18908d27e23488bf809cdcb8d28b4d4d0805f05688e3`).
2. `FUN_00466ce2` performs world updates, drains queued world actions through `FUN_00466221`, then iterates active floater records and calls `FUN_0041e569`. The iteration is bounded by a 256-slot table and the active count. It also calls the Hall/task update helper four times and advances timers and simulation counters. Evidence `ev_b51f2311ff9bd9ad209f0663ea00bfe330e7ff0eff117e8a273292d3112a4e0e`; details in [the function note](../../functions/0017_batch_0013.md#fun_00466ce2--0x466ce2).
3. `FUN_0041e569` is the per-floater update. It calls both `FUN_004211bb` and `FUN_0042219e` among movement, animation, task, and state helpers. Runtime state `0x0e` uses the exact-arrival result from `FUN_00422d27` to decrement a timer. Runtime states `0x0f`/`0x10` run a state-specific movement step and finish inside a Chebyshev radius (10 by default; a nonzero `FUN_00420721` result replaces it, except order `0x14` forces zero). The coordinate kernel itself reports arrival only when both coordinates match. Evidence `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`, `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`.
4. `FUN_004211bb` consumes an existing order. It branches on the action field at `+0x3c` and progress/state fields, calls destination/candidate helpers, advances unit state, sets target fields, or cancels an order through `FUN_00421ec1`. It is an order executor, distinct from the action chooser in the reevaluator. Evidence `ev_0e9d3fbfa8df7eb8f372d0b17bc92593ddd6fc2eb7cebe7c043ca611798b4abd`; details in [the function note](../../functions/0010_batch_0006.md#fun_004211bb--0x4211bb).
5. `FUN_0042219e` reevaluates a unit's order and conditions. It returns immediately for runtime states 6 or 7 and while the global guard `DAT_006191b4` is nonzero. Otherwise it has category/subtype branches that search candidates, compare scores and unit thresholds, and write action, island, target, and progress fields. For Leviathan it writes `FA_Move`, `FA_AttackFlt`, or `FA_AttackLoc`; regular-unit branches include `FA_AttackFlt`, `FA_Train`, `FA_Recharge`, and `FA_Wander`. Evidence `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`; details in [the function note](../../functions/0010_batch_0006.md#fun_0042219e--0x42219e).

These calls locate the verified unit-level decision logic: it is interleaved with each floater update, rather than being an independently scheduled per-player routine. The resolved direct-caller query for `FUN_0042219e` returned no entries (Evidence `ev_2d79f304365a3c8484b4cf08c48a252a5a1bef7bc030214046ea9ada686a468e`); its known link comes from the update function's thunk call. Indirect dispatch and callbacks may contain more behavior than the resolved graph exposes.

---

# Enemy AI and autonomous unit behavior

## Four-tribe unit behavior

The reevaluator has distinct branches for category-4 Leviathan and the regular tribe floaters, with further special handling keyed by subtype, task-reference field, current order, runtime state, and flags. The regular-unit behavior visible in `FUN_0042219e` is not one universal “enemy order” policy:

- Some active per-island/category condition in `DAT_005eebd4` makes eligible units scan candidate records through `FUN_00420991`, select the lowest `FUN_00420600` score, and issue `FA_AttackFlt` (6). If the current action is already 6, that branch returns without replacing its target. The selector scans candidates associated with the floater's current island.
- Outside that condition, an existing attack order may be canceled, and runtime state 4 suppresses further reevaluation for that call. Units with an attached record reference (`+0x38`) call `FUN_0041e454` and can return early if the record is still active. Otherwise the controller checks up to 64 task records in `DAT_006183bc`, applies owner/class/level comparisons, and either assigns a task record with `FUN_00421ec1` or falls back to `FA_Wander` (14) at the tribe's home island.
- A unit with a non-null reference to its current object/task record may be matched to the current selected record (`FUN_004207f2`). Flag `0x10` routes it through `FUN_00421d82`; another branch assigns `FA_Train` (12) under a `0x20` gate. The same area compares unit values with thresholds returned by helpers and may assign `FA_Recharge` (2). Field identities and threshold units are not fully established, so these are described as record/state responses rather than named morale or resource policies.
- Flag `0x10` also routes the non-spore Leviathan subtype path through `FUN_00421d82`, which selects a same-island eligible peer/candidate and writes `FA_AttackFlt` (6). This shared helper appears to implement a reactive engage order, but its exact trigger semantics still need field-level tracing.

This describes logic common to the global unit controller and its observed regular-unit branches. It does not establish that every regular floater is autonomous at all times: player orders, persistent task records, runtime states, and global pause/guard conditions can all control whether reevaluation changes a unit's order. Main reevaluator evidence: `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`.

### Wander motion

When `FUN_004211bb` dispatches `FA_Wander`, it enters runtime state `0x0e`, loads timer `+0x34 = 60`, sets progress `+0x46 = -1`, then reaches a common tail that calls `FUN_00423068` for nonzero runtime states. For state `0x0e`, that helper draws X and Y offsets with two calls to `FUN_00467260(200)`, shifts each by `-100`, clamps candidate Y to `0x28..0x122`, and writes the destination pair at `+0x28/+0x2a` if candidate X passes horizontal bounds. The no-location-record path for this state adds no extra sprite/stance offset. It also sets facing from candidate X relative to current X. The movement consumer `FUN_00422d27` uses this pair with base step magnitude 1 in state `0x0e`; the timer advances on exact coordinate arrival, and expiry leaves the action available for another dispatch. The evidence does not establish a uniform distribution or guarantee that a repeated draw changes the coordinate. See [the movement analysis](../../ToneRebellion_Remake/MOVEMENT_REVERSE_ENGINEERING.md#fa_wander-destination-generation-and-repeated-movement). Evidence: `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`, `ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f`, `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`.

---

# Enemy AI and autonomous unit behavior

## Control domain and Leviathan category

### Leviathan subtype table
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

---

# Enemy AI and autonomous unit behavior

## Control domain and Leviathan category

### Action IDs and the Leviathan decision branch
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

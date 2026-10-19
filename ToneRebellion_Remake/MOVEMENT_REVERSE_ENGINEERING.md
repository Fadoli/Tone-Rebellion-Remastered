# Floater movement primitives: REA evidence and port

This note records observed selection/input/movement procedures and separates them
from behavior still needing class/state checks. Ghidra pseudocode is a decompiler
reconstruction, not recovered source; field names and inferred types remain
provisional. The user has clarified that workers cannot receive direct orders:
selecting them only shows stats, while soldiers and mages are orderable. The
remake source and current executable do not expose player-facing worker orders.
Worker selection remains informational, and soldiers/mages should only become
orderable after their original class/state gates are verified.

## Input and destination path

| FLOAT.EXE procedure | REA evidence | Observation |
|---|---|---|
| `FUN_0042eba0` (`0x42eba0`) | `ev_65e41f9afa35457a4a0cb35010dd615e0a62eb7384057e13a9aea3fb6ea6465b` | Maps Win32 left/right button-down messages `0x201`/`0x204` to input queue types 2/4. |
| `FUN_00469f56` (`0x469f56`) | `ev_584be7e8cdd9be7c4fd1a0432ef83685f37123ab5a4622037dde65bf4a47704e` | Input code 2 dispatches island event 6 with pointer coordinates; input code 4 dispatches island event 7. The preceding input-queue function maps Win32 left/right button-down to these codes. |
| `FUN_00435826` (`0x435826`) | `ev_5fabac375596d1e1457b7649fb698b76bf3f96b23dab00f021e899fcd4d2c1f2` | Hit-tests a floater and island locations. A floater hit emits message `0x3f`; its empty-ground coordinate branch emits message `0x4c` only while UI state bit `0x4` at `+0x178` is active. A location hit follows separate site/location message branches. |
| `FUN_00420991` (`0x420991`) | `ev_b758701979d34e447f00b2067f67d58c0c58d9b8c28b444e24dfd4a160713da5` | The autonomous task selector calls this candidate guard before ranking candidates. It rejects the current object and records with flag mask `0x809`; for object class 4 it uses a level threshold table at `DAT_0061fa2e`, and for other classes it allows the same class or requires the per-player class value at `DAT_00619290` to be zero. This supports a source class filter but does not identify the table's runtime values as a soldier/mage allowlist. |
| `FUN_00435826` (`0x435826`) | `ev_29719d9690c28e9b3bb41c88f5ff96ce6cc8f4ad226b062deb47d6a23217879c` | Revalidated click handler: a floater hit emits selection message `0x3f`. The `0x4c` destination order is a separate empty-ground path gated by UI state bit `0x4`; it is not issued by selecting a floater. |
| `FUN_0043530b` (`0x43530b`) | `ev_5e3fc63f4718af2e8a051c86de5109504655264091ec1257449307a1b02b0952` | Decodes the UI action modes raised by `FUN_00435826`: mode `0x13` sets interaction bit `0x4` and cursor/action id `0x0f` (the only mode in this set that enables the empty-ground `0x4c` path); `0x10` and `0x12` both set bit `0x2` but choose cursor/action ids `3` and `5`; `0x11` sets bit `0x1` and cursor/action id `0x0d` or `0x0b` depending on the two stored targets. This maps the interaction state, but the class-table initialization and recipient guard remain unknown, so it is not enough to enable soldier/mage movement yet. |
| `FUN_0042970c` (`0x42970c`) | `ev_bcb9a925483956dd92de831e72742c3a6510dbd9a56729b017c9c5223fe5c3a5` | Routes a message according to context field `+0x48`: direct dispatch through `FUN_0046c402`, secondary dispatch through `FUN_0046c1b4`, or a local queue through `FUN_0046c3bc`. |
| `FUN_0046c402` (`0x46c402`) | `ev_5d7372e111e8a989a1bad601deacda8478942b76678d4c0f95271ab98899581f` | Calls the active-context handler indirectly from callback slots in records with stride `0x130`. Static call references do not resolve the effective handler or its recipient-class guard. |
| `DAT_00619290` (table read by `FUN_00435826`) | `ev_e6487dc3406aa2d64a6c44227d93003cc5658ee6fb0b6adabc68947b37f039b5`, `ev_e1cf3e5b13ea9e894e109f983d575d93db9494440640c431beeb4115c47f87d1`, `ev_6a58e77526590a24419b4c84ad1ffdeac127494982b6d9aa3a42c30eb9bacc33` | Instruction evidence confirms comparisons against `DAT_00619290 + type*4 + player*0x14a0` while choosing modes `0x10`–`0x13`. These are reads/comparisons; they do not establish table initialization or the semantic class allowlist. |
| `FUN_0041e3eb` (`0x41e3eb`) | `ev_99ac9bec204079134afb4ec773ba173dab2b1a1a87ae06d72f28cad8c8cbfff9` | Packs each map coordinate as `(coordinate + 5) / 10`, with X in the high byte and Y in the low byte. |
| `FUN_0041e427` (`0x41e427`) | `ev_0c9a83fe313044ec813605a6f5e71760fcbcf78e0fff164432184e30593c562d` | Expands those bytes to pixel coordinates by multiplying each by 10. |

## Interaction cursor lifecycle

The cursor is a 17-slot state machine, not a one-off glyph image. `FUN_0041c181`
loads slots 0..16 from the resource IDs in `DAT_0049c950`; `FUN_0042dd47`
chooses the requested slot when its handle exists, otherwise falls back to slot
0, then calls `SetCursor`. `FUN_0043530b` assigns slot 9 for mode 1, slots
3/5/15 for modes `0x10`/`0x12`/`0x13`, and slot 13 or 11 for mode `0x11`
depending on whether an item or glyph is armed. Evidence:
`ev_c726a273b363fd7769f6b98bb6a0fb90f454b1cc5c2da0d264a1175c0aaaca75`,
`ev_f390428e4e2b22a6ce9a9f425844123e7a120340e823e19cc9c45619ebb90e9a`,
`ev_b65156eb13978511b7f06cdb3fee86e7c2c4a37bf3cac67ad0f0badb2f999a68`.

`FUN_0042fa0f` messages `0x42` and `0x43` arm an inventory item or glyph and
enter mode `0x11`; message `0x40` commits a target, restores slot 0 and clears
both armed IDs. Evidence: `ev_a8230350584e54954217dfeda123b6cf8d9dc6ca7211fff2385661c22cdab6ba`
and the `FUN_0042fa0f` dossier in `functions/0012_batch_0008.md`.

Live REA inspection of the shipped `C:\Program Files\Tone\FLOAT.EXE` confirmed
the table bytes at `0x49c950` (Evidence
`ev_870a794f1785a5ab6a4e135cf0a026a2068b803ccd42730199dce261f9631b74`):
slots 0..16 map to resource IDs `84, 75, 76, 77, 78, 79, 7a, 7b, 7c, 7d,
7e, 7f, 74, 80, 81, 82, 83` (hex). The remake now loads the complete table,
uses slot 11 while an inventory item or glyph is armed, and returns to source
slot 0 immediately after the target click or a screen change. `WM_SETCURSOR`
also reapplies the state so Windows cannot leave a stale custom cursor visible.
The other source modes (slots 3, 5, 9, 13, 15 and data-driven 0x15..0x1c) are
not yet raised by remake actions, so they remain available but inactive.

## Unit tick and speed source

| FLOAT.EXE procedure | REA evidence | Observation |
|---|---|---|
| `FUN_00422d27` (`0x422d27`) | `ev_0a3a5baa3dd85e9e4d8e576461b4c0ac5dde6dd1cb0ba6135191f046f1f98a93` | Computes a destination and effective step, clamps each axis independently, reduces the step near the target using Chebyshev distance, and advances current coordinates. The target is reported reached only when both coordinates match. |
| `FUN_0041e569` (`0x41e569`) | `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a` | Runtime states `0x0f` and `0x10` compare Chebyshev distance against a 10-pixel default stopping radius; `FUN_00420721` can supply a unit-specific radius. State `0x0e` instead uses the coordinate step's exact-arrival result to decrement its timer. |
| `FUN_00423068` (`0x423068`) | `ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f` | Updates the object's draw anchor/offset based on target and state, sets flag bit `0x002` when the target is to the left and clears it when to the right, then checks horizontal bounds. This routine is not evidence of terrain pathfinding. |
| `FUN_0042704b` (`0x42704b`) | `ev_d21d92e7afdc377fecc4fce5fecca40c344273a5e036a4c507b40f99ab2e04b1` | Reads flag bit `0x002`; for the left-facing case negates the horizontal body/leg draw scale, producing a horizontal sprite mirror. |
| `FUN_00464242` (`0x464242`) | `ev_1559f3b44eb1bd728c2c2077c916a6ba549ae4c8310f49d5fc23ec8de61ff7cc` | Resolves a tribe/unit-class record in the runtime floater-stat table. |
| `FUN_004633a7` (`0x4633a7`) | `ev_fe7a5335c367485201a317db133bb5029b49d97a3d6cbffc7fd3926406f911ec` | Parses 45 rows with seven fields into 14-byte records; the seventh field is stored at record offset `+0x0c`. |
| `FUN_0046466f` (`0x46466f`) | `ev_fff46798e5d5d511dba4e67c4659afc2916bd8e719ba56ae3da3806f38ff09fe` | Creates four starting instances per player with unit class 0. |
| `FUN_004211bb` (`0x4211bb`) | `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957` | Consumes the floater order. Case `0x13` (`FA_MergeWith`, order ID `0x14`) first sets state `0x0f` and copies target `+0x42`; after arrival it selects state `0x0e` for subtype 8, otherwise `0x15`. This is autonomous task execution, not a proven player click handler. |
| `FUN_0042219e` (`0x42219e`) | `ev_d9f9f466dec9c616930d5fb954437b6cb9c603d687390540a4d8c90cdc2c0eea`; earlier dossiers `ev_04a74bd124249ab097279236e8788fcf661bc6047d7c113aea28ae262bafc6e5`, `ev_787dc785055d52728b1408fa372d280fa57be569a05f32883f94a4022cbce846` | Fresh full-function dossier covers body `0x42219e–0x422d26` (2,953 bytes). It returns early for object state 6/7 and while `DAT_006191b4` is nonzero. One class-4 branch distinguishes subtype 9; another, when flag `0x10` is clear and order field is 0 or `0x0e`, scans up to 64 records at `DAT_006183bc`, checks active/type/subtype values, calls `FUN_0041e454` and `FUN_00422031`, compares task values against object level and measured distance, and writes task state/target fields. Other branches select states 6/7/`0x0e` for owned-site or other object conditions. The body confirms conditional task scheduling and destination updates, not random roaming; the semantic meaning and source population of every task record and state still need tracing before porting these assignments. |
| `FUN_00420d97` / `FUN_00420a55` | `ev_0a150ef6299ccee55e14aeab45e2de16381b5142b4063cda099503d87e818883`; `ev_76a4661cb67067b44054706649c3ff1f80a7e9eec7116d8c36177f340ab15b36` | `FUN_00420d97` delegates to `FUN_00420a55` for the current island. Its mode 4 candidate filter requires object owner/class field 4, distance below `0x5a`, type below `0x16`, and flags masked by `0x90` clear; it retains up to 10 candidates, then delegates final selection to `FUN_0041e28e`. This identifies one source selector used by movement/task code, not a general order rule for all units. |
| `FUN_004210a9` (`0x4210a9`) | `ev_dd046f002c50d0d9e841af455f3dd8fc8b70d1b11f430f2fa5c0185edc5f5121` | Chooses a current-island handoff location and enters runtime state `0x11` with the departure slot and target island; the mover later makes a timed discrete position/island change. |
| `FUN_00420721` (`0x420721`) | `ev_234f0678b3bbd27430c793e465dfd5095240536d821d1821e23bb5b1acb00e41` | Supplies the optional arrival radius used by states `0x0f`/`0x10`. Its lookup is gated by category/subtype and the floater's `+0x22` value; a linked-site and table-bit condition can scale a positive stat value by integer `5/4`. |
| `FUN_0045da80` (`0x45da80`) | `ev_0f9c0e1151dca8d181ee42ea559e71d3987676f2680c797f76c97d5b25bbba36` | Checks action-specific conditions and an eligible unit, then stores order `0x13` (`FA_Cast`) plus three raw parameters and zeroed progress; deducts two player resource fields after finding the unit. The cast state resolves a destination but does not integrate current coordinates. |
| `FUN_004527ee` (`0x4527ee`) | `ev_1b65d37c5f980508939852c08a13046d03c79fce26bff8abdd695e5f8134eea6` | Calls `FUN_004528ca` to initialize the placed item only after `FUN_00452794` accepts the site/item; on success it sets a runtime flag and emits event 2. The exact full transition from `FA_Build` to this validator still needs to be connected. |

The local original `floater.txt` defines the final field as speed. Each tribe's
`*work` row has speed 3. This agrees with the runtime access at `+0x0c` in
`FUN_00422d27` through `FUN_00464242`; this is only the worker movement
parameter, not evidence that the player can issue worker move orders.

The remake's session tick now passes each floater's state, subtype, category
modifier and already-resolved near-target/site conditions through
`floater_motion_effective_speed` before calling the coordinate kernel. Initial
workers start in state 0; category modifiers and conditional overrides remain
zero until their runtime sources are modeled. The session still lacks the
source order/state machine and target resolver, so this wires the observed
speed rules into the existing simulation without establishing a player-issued
move path.

## Tick, state machine, target and arrival detail

The following separates the per-world update, per-floater order controller,
order executor and coordinate step. Offsets are raw accesses seen in the
decompiler; they are not recovered source declarations. Evidence for the
function bodies is in `functions/0010_batch_0006.md` and
`functions/0017_batch_0013.md`.

### Update sequence

`FUN_00466ce2` iterates active floater records from the fixed 256-slot table
and invokes `FUN_0041e569` for each live record. The latter calculates the
record index using a `0x4c` stride. Evidence:
`ev_b51f2311ff9bd9ad209f0663ea00bfe330e7ff0eff117e8a273292d3112a4e0e` and
`ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`.
Within that update:

1. `FUN_0042219e` reevaluates the order when runtime state `+0x2c` is zero, or
   when `(DAT_00618e44 + floater_index) % 10 == 0` for another state.
2. If state `+0x2c` is zero and action/order `+0x3c` is nonzero,
   `FUN_004211bb` consumes that action and may set the next runtime state,
   target fields and progress fields.
3. The common movement call to `FUN_00422d27` is enabled only when state is
   not `0`, `6`, `7`, `0x0f` or `0x10`, and no flag from mask `0x411` is set.
4. The state-specific switch then handles arrival and action completion. State
   `0x0e` uses the common movement result and decrements its timer only when
   the step routine reports exact arrival. States `0x0f` and `0x10` use the
   radius-based state-specific arrival handler. Both are excluded from the
   common movement call, so each can make at most one state-specific movement
   step in that update.

The return from `FUN_00422d27` means both current coordinates equal its
resolved destination exactly. Runtime states `0x0f` and `0x10` can finish at
a wider radius: they compare Chebyshev distance against 10 by default, use
zero when action/order is `0x14`, and let a nonzero result from `FUN_00420721`
replace the default. The special `0x14` action is `FA_MergeWith`. Reaching
that radius finishes those states even when the coordinate kernel did not
return exact equality. When state `0x0f` finishes with no unit-specific radius
and action/order other than `0x14`, the update also sets bit `0x10` on the
referenced island record and bit `0x40` on the floater flags. State `0x0e`
uses exact coordinate arrival to count down its state timer instead. The
semantic names for these bits remain unresolved. Evidence:
`ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`.

`FUN_00420721` explains when the optional radius replaces 10. It returns zero
unless `FUN_004207c2` returns zero; that guard allows category 4, or a
nonzero subtype when the floater's short at `+0x22` is positive. Otherwise it
reads the first short from `FUN_00464242(category, subtype)`. The local
`floater.txt` header identifies that column as attack range, so states
`0x0f`/`0x10` can stop at the unit's data-defined attack range instead of the
default radius 10. If `FUN_004207f2` resolves a linked site (`+0x0c != -1`)
and bit `0x4` is set in the table dword addressed from
`DAT_00619242 + category * 0x14a0`, a positive attack range is changed to
integer `floor(range * 5 / 4)`. The semantic meaning of that table bit remains
unestablished. Evidence:
`ev_234f0678b3bbd27430c793e465dfd5095240536d821d1821e23bb5b1acb00e41`,
`ev_601b55f72156209d4f5c1ae6f9060918a71e3fc3423c72c12074227bdb69a5c6`,
`ev_400be7fc416e3e48c58ebeae7f1497639f909f0569891b58d5b3cba579bbab2a`.

### Destination resolution and step size

`FUN_00422d27` starts with the signed-short pair at floater offsets `+0x28`
and `+0x2a` as a pixel destination. It resolves special runtime states before
choosing the effective step:

| Runtime state | Target/step handling observed |
|---|---|
| `8` | Adds an island-location offset selected through the record at `+0x32`; clamps X to `0..0x9ff` and Y to `0x28..0x122`. If `FUN_00420600` for that location returns below 100, uses step 1 for this update. It also sets or clears facing flag `0x002` according to whether the resolved X target lies left of current X. |
| `9` | Decodes the packed coordinate at `+0x32` with `FUN_0041e427` (each byte expands to a multiple of 10), then uses step 1 when `FUN_004672a6` between current and decoded target is below 100. |
| `0x0e` | Forces step 1. |
| Other states | Loads the base speed from stat record `FUN_00464242(category, subtype) + 0x0c`. |

After that state-specific choice, a subtype-0 unit doubles its step when the
per-category value at `DAT_00618f5a` is positive. If `FUN_004207f2` reports
the relevant current-site condition, the code also checks the owner's bits at
`DAT_00619242` against current site item IDs `0x2c`, `0x2d` and `0x2e`; the
matching cases add one to the step. The exact gameplay meaning of those
modifiers is not established here.

The remake now exposes this selection as `floater_motion_effective_speed` in
`src/core/floater_motion.c`. Its caller must resolve the raw stat speed and the
state-8/9 distance predicate, category modifier, and owner/site bonus first;
the helper deliberately does not guess those world-state inputs. The existing
`game_session_tick_floater_moves` path still supplies a direct destination and
base speed, so this state-aware helper is groundwork for the autonomous tick,
not a claim that task assignment or destination resolution has been ported.
Evidence: `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`.

The kernel measures Chebyshev distance `max(abs(dx), abs(dy))`. If that value
is less than four times the selected step, it reduces the step to
`distance / 4` using integer division. If this becomes zero, the global tick's
low bit selects a zero- or one-pixel step. It then clamps X and Y deltas
independently to `[-step, +step]`, updates both coordinates, and reports exact
arrival only if both match the target. This is axis-clamped motion rather than
a normalized vector step. The examined code does not establish terrain
pathfinding or obstacle avoidance. Evidence:
`ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
`ev_99ac9bec204079134afb4ec773ba173dab2b1a1a87ae06d72f28cad8c8cbfff9`,
`ev_0c9a83fe313044ec813605a6f5e71760fcbcf78e0fff164432184e30593c562d`.

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
progress to 1. State 8 resolves the indexed runtime entity's current
coordinates and moves toward it. Its state handler can finish early when
`FUN_004208eb` finds a qualifying candidate; otherwise exact coordinate
arrival also completes state 8.

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

### `FA_Wander` execution and retained destination

The periodic reevaluator can assign `FA_Wander` (`14`) with the tribe's home
island as its target when no task record is selected. The local executor in
`FUN_004211bb`, switch case `0x0d` (`action - 1`), sets runtime state `0x0e`,
sets the state timer at `+0x34` to 60, and sets progress `+0x46` to `-1`. This
branch does not write the movement destination pair at `+0x28/+0x2a` or choose
a location record.

State `0x0e` is allowed through the common movement gate in `FUN_0041e569`.
`FUN_00422d27` uses the existing `+0x28/+0x2a` pair as its destination and
uses base step magnitude 1 for this state before range/effect modifiers. The
timer at `+0x34` counts down only when the coordinate step reports exact
arrival; this state does not use the radius test documented for states
`0x0f/0x10`. Thus the evidence proves how the wander action enters a moving
state and which stored coordinates that state uses, but not where a fresh
wander destination is chosen. In particular, the consumer alone does not
support implementing random target selection. The reevaluator's fallback
home-island value is an island/task target, not by itself proof of a
coordinate destination. When the timer expires, generic completion clears the
runtime state but retains the action; the next idle dispatch can enter the
same executor branch again, still without a new coordinate write. Evidence:
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

### Training and recharge orders: travel to a location record

For these orders, `FUN_004211bb` first compares the task's target-island field
`+0x40` with the floater's current island `+0x0e`. If they differ, it passes
the target to `FUN_004210a9` and clears the task link if that call returns 0.
The following local-state transitions occur when the target island is already
current (or unspecified):

| Order | Order consumer writes | Movement and arrival behavior |
|---|---|---|
| `2` (`FA_Recharge`) | Switch case `1` sets runtime state `2`, copies target index `+0x42` to `+0x32`, copies parameter `+0x44` to `+0x30`, and sets progress to `-1`. | State `2` passes the common movement gate. The coordinate step resolves `+0x32` as an island location record and approaches its derived destination. When the exact step result reports arrival, the state handler sets flag bit `0x001`, waits through its counter, and then adjusts one of two raw floater fields subject to stat limits and helper results. It clears the flag and finishes when those conditions say no further adjustment applies. |
| `17` (`FA_UseBridge`) | Switch case `0x10` is grouped with case `1` and performs the same state-2 target/parameter writes as `FA_Recharge`. | Uses the same state-2 movement and arrival handler. The action label does not by itself establish which bridge object or animation is involved. |
| `11` (`FA_Enlist`) | Switch case `0x0a` shares the direct transition with case `0x0b`: set runtime state to the action ID, copy `+0x42` to `+0x32`, `+0x44` to `+0x30`, reset timer `+0x34`, and set progress to `-1`. | State `11` resolves the target as a location record. On exact arrival, the handler checks `FUN_00450385` and `FUN_0045c772`; if both allow it, it calls `FUN_0045c470` and starts its counter. |
| `12` (`FA_Train`) | Switch case `0x0b` performs the same direct target/parameter/state writes as case `0x0a`. | State `12` resolves `+0x32` through the island-location table. On exact arrival, the handler calls `FUN_0045c797` if `FUN_00450385` and `FUN_0045c772` allow it, then advances its counter. |

The location record provides the approach coordinates; these consumers do not
assign a fresh pixel destination directly. Both routes can therefore be
reconstructed through local arrival, but the source-level meanings of the
extra parameter and the adjusted fields remain unresolved. I keep “recharge”
and “train” as action-table labels; the movement evidence alone does not
establish what the fields changed on site represent. Evidence: order and
cross-island consumption `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
state handling `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
location destination resolution `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
and action labels `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.

### `FA_ObtainObject`: assigned location or owner candidate

Action 13 (`FA_ObtainObject`) is switch case `0x0c` in `FUN_004211bb`. The
consumer first compares raw floater field `+0x18` with the action parameter
`+0x44`. If equal, it searches candidate mode 2 for the owner; a local result
enters state `4` with the returned location index in `+0x32` and the parameter
in `+0x30`. If no candidate exists, it delegates to the owner's home island
through `FUN_004210a9`. Otherwise, on the assigned island `+0x40`, it enters
runtime state `13` (`0x0d`), copies assigned location `+0x42` to target `+0x32`,
copies parameter `+0x44` to `+0x30`, and sets progress to `1`. A remote assigned
island is handled by the same cross-island helper.

State `13` is not the special runtime state `0x13` (19 decimal), so its
coordinate step uses the ordinary location-record route. `FUN_00423068`
resolves target record `+0x32` and applies the state-`0x0d` body/leg offset;
`FUN_00422d27` then moves current coordinates toward the stored pixel target.
The state handler maps runtime state `13` to case `0x0c`: it reads a result
through `FUN_004502dc`, cancels the order when that result is zero, and on
arrival calls `FUN_00452a15` for results in the range `5..33` before completing
the state. This confirms local travel and a post-arrival action path, but does
not by itself establish the object's identity or the full meaning of the
parameter/result fields. Evidence: action consumer
`ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
state handling `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
coordinate destination and step `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
result lookup `ev_8d591588cea4abce308dbbd5f69e34b5c6431010d387034afe228dee1b3385a8`,
and action labels `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.

### Cross-island handoff through state `0x11`

`FUN_004210a9(target_island)` is the shared island-handoff helper used by
several order branches. A target of `-1` or the current island succeeds
without changing state. Otherwise it scans the current island's location
records for eligible records with raw class `+0x04 == 2` and flag bit `0x001`
set. It immediately prefers the first record whose `+0x36` equals the target
island; failing that, it keeps the nearest eligible record by the same
Chebyshev-distance score, provided the score is below 6000. If none qualifies,
it returns 0. On success it sets runtime state `0x11`, stores the departure
record index in `+0x32` and the target island in `+0x30`.

State `0x11` then moves normally to the selected departure record. Its handler
waits for the common coordinate step to report exact arrival; if the departure
record's flag bit `0x001` is clear, the state ends. If the bit is set, a timer
starts. At timer 60 the update checks for an active matching location on the
target island and chooses a 200- or 500-tick wait, then adds 120. At timer 120
it places the floater at that destination-island record; if the record is
missing or inactive, it selects the nearest eligible class-2 record within
distance 8000 of an order-dependent reference point. It writes the floater's
position to that record's `(x, y - 30)`, synchronizes the stored destination
pair, and changes the floater's current-island field to the target island.
The countdown then continues to 60 before the state completes. These are tick
counts, not verified seconds. The code therefore shows a walk to a local
handoff site, a timed wait, a discrete position/island change, and a second
wait; it does not show continuous motion between islands. Evidence:
handoff selector `ev_dd046f002c50d0d9e841af455f3dd8fc8b70d1b11f430f2fa5c0185edc5f5121`,
per-floater transition `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
destination-island lookup `ev_c50cc6e829d1545a0ff5b6cadf8d1248dabad2086db613e1f1ba72423d27b6fb`,
and coordinate step `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`.

### `FA_Deliver`: site search, island handoff and local approach

Action 4 (`FA_Deliver`) is switch case `3` in `FUN_004211bb`. Its task fields
remain raw here: destination island `+0x40`, destination/location value
`+0x42`, parameter `+0x44`, and progress `+0x46`. Depending on progress and
the parameter range, the consumer selects a local location or asks
`FUN_004210a9` to hand off to another island:

| Branch | Selected movement state and destination |
|---|---|
| Progress is `2` | If parameter `+0x44` is outside `5..33`, clear the task link. Otherwise request candidate mode 2 for the floater's owner; on a local candidate, enter state `4`, put its location index in `+0x32`, and set progress `-1`. If no candidate exists, delegate to the owner's home island. |
| Progress is `1` | If raw floater field `+0x18` is zero, reset progress to `0` for a parameter outside `5..33`, or to `-1` for one in range. Otherwise advance progress to `2`. No destination is written in this branch. |
| Raw floater field `+0x18` equals parameter `+0x44` | If already on destination island `+0x40`, enter state `4`, copy destination location `+0x42` to `+0x32`, copy `+0x44` to `+0x30`, and set progress `1`. If remote, delegate to that island. |
| Parameter `+0x44` is outside `5..33` | `FUN_00420dbd` selects an island/location pair for that parameter. A local result enters state `3` with the returned location in `+0x32`, parameter in `+0x30`, and timer `+0x34` reset. A remote result is passed to `FUN_004210a9`; no result clears the task link. |
| Parameter `+0x44` is within `5..33` | Candidate mode 3 selects a local location and enters state `3` with that index in `+0x32`, parameter in `+0x30`, and timer reset. If no local candidate exists, delegate to the home island. |

States `3` and `4` are not excluded by the state-value part of the common
movement gate; when flag mask `0x411` is clear, they resolve `+0x32` through
the current island's location table. They travel using the normal class speed
and location-derived destination; no cross-island coordinate interpolation is
shown here. State `3`'s arrival handler runs its timed
location interaction. State `4` completes on the exact step-arrival result
and calls `FUN_004527ee(+0x30, owner)` when the selected location's raw field
`+0x04` is zero. That validator initializes an item only if its own
preconditions pass; this connects the delivery order to a location-side
completion attempt without identifying the delivered object's semantics.

`FA_Fetch` is action ID 3, but `FUN_004211bb`'s order-minus-one switch has no
case `2` in the retained pseudocode. It has no order-specific local target or
runtime-state write here; the shared cross-island delegation before the
switch may still run. The missing local transition should not be filled in by
analogy with `FA_Deliver`. Evidence: action consumption and island handoff
`ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
state handling `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
location approach `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
and location validator `ev_ff5099639bbdcb8c257ae4e8f690ea98f0ebdf4321753ff832e66ba4dc11d800`.

### `FA_Repair`: candidate site then local approach

Action 18 (`FA_Repair`) is switch case `0x11` in `FUN_004211bb`. If raw floater
field `+0x18` is `1`, the order uses its assigned island/location fields:
when the current island matches `+0x40`, it enters state `4`, copies location
`+0x42` to target `+0x32`, and stores `1` at `+0x30`; otherwise it delegates
to `FUN_004210a9(+0x40)`.

For other `+0x18` values, it calls `FUN_00420dbd(1)` to obtain an island and
location pair. No pair cancels the task link. A local pair enters state `3`
with its location index at `+0x32`, `1` at `+0x30`, and timer `+0x34` reset
to zero; a remote pair is handed to `FUN_004210a9(island)`, with task
cancellation if that call returns zero. Once the floater is at the selected
island, states `3/4` use the same location-record movement and arrival paths
described for `FA_Deliver`: state `3` runs its timed arrival interaction,
while state `4` calls the placement validator on exact arrival when raw
location field `+0x04` is zero. The order label is “Repair”, but these paths
alone do not identify the repaired object or the fields changed at the site.
Evidence: order consumer `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
state handling `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
candidate lookup and movement `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
and placement validation `ev_ff5099639bbdcb8c257ae4e8f690ea98f0ebdf4321753ff832e66ba4dc11d800`.

### `FA_Build`: three local route states

Action 5 (`FA_Build`) is switch case `4` in `FUN_004211bb`. The consumer first
loads the requested location from island `+0x40`, location `+0x42`, then checks
the item parameter `+0x44` with `FUN_004526de`. A failed item check terminates
the task. Otherwise it selects among three routes:

| Condition | Local route | Arrival behavior |
|---|---|---|
| Target location raw field `+0x04` is zero and `FUN_00452794(+0x44, owner)` accepts it | On the target island, enter state `5`, target the requested location through `+0x32`, store item parameter `+0x44` at `+0x30`, and set progress `-1`. If remote, hand off through `FUN_004210a9(+0x40)`. | State `5` uses the location-derived movement destination. On exact arrival it ends the state and calls `FUN_004527ee(+0x30, owner)` when location field `+0x04` is zero. |
| Raw floater field `+0x18` is `1` | On the target island, enter state `4`, target location `+0x42`, and store `1` at `+0x30`; if remote, delegate to `FUN_004210a9(+0x40)`. | State `4` uses the same location approach and arrival validator described above. |
| Neither prior condition applies | `FUN_00420dbd(1)` selects an island/location pair. No result terminates the order. A local result enters state `3`, stores its location at `+0x32`, stores `1` at `+0x30`, and resets timer `+0x34`; a remote result is handed off to the selected island. | State `3` uses the location-derived destination and its timed arrival interaction, rather than the state-4/5 placement call. |

The action table labels ID `5` `FA_Build`; the selection branches show that
the order can travel to a fallback site through state `3` or `4` before its
placement attempt. States `4/5` invoke the placement validator only on exact
arrival and when the raw location field is zero; the validator's own item/site
checks can still reject placement. Evidence: order and route
`ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
movement/arrival `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
location resolution `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
item checks `ev_e884123140e558d8678b40fa79da6539532f8441ffe895daabdad5787c8afff7`,
placement `ev_ff5099639bbdcb8c257ae4e8f690ea98f0ebdf4321753ff832e66ba4dc11d800`,
and action labels `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.

### `FA_Cast` (`0x13`): target resolution without locomotion

The action table labels order ID `0x13` (`19`) `FA_Cast`. The event consumer
calls `FUN_0045da80` for selected action values `0x15..0x1c`; that routine
chooses an eligible floater, clears its old task, writes order `0x13`, stores
three raw parameters and zeroed progress, and deducts two player resource
fields. The parameter values remain raw; the action ID itself is independently
identified by the `FA_*` table.

Because `FUN_004211bb` switches on `order - 1`, FA_Cast is case `0x12`, not
case `0x13`. This branch sets runtime state to the order value (`0x13`), copies
task `+0x42` to floater target `+0x32`, copies task `+0x44` to action object
`+0x30`, clears flag `0x200`, and sets progress to `-1`.

The apparent state value `0x13` does not execute the ordinary coordinate
integrator. `FUN_00422d27` delegates that state to `FUN_0042361d`, which checks
the action-object index against `0..0x16` and reads target-mode bits from
`DAT_0049d218[actionObject]`:

| Action-object bit | Destination selection in `FUN_0042361d` |
|---:|---|
| `0x02` | Use coordinates from the runtime object/task record indexed by floater `+0x32`. |
| `0x01` | Use coordinates from the current island's location record indexed by floater `+0x32`. |
| `0x04` | Replace the selected target with a random point within `[-100,99]` on each axis of the floater's current position, then clamp X to `30..2530` and Y to `40..290`. |

The helper updates facing from the selected X coordinate and writes the
destination pair `+0x28/+0x2a` only when its horizontal bounds check succeeds.
It does not update current position. Since the state-`0x13` branch of the
coordinate routine returns this helper result directly, the observed order
refreshes/validates a destination but performs no walking step in this state.
The flags may be combined; bit `0x04`'s random point overrides either record
target when set.

The state handler maps runtime state `0x13` to case `0x12`. It reads a result
from `FUN_004502dc` (raw object `+0x24` only when object `+0x10` equals 1);
zero cancels the task. If destination resolution succeeded, it calls
`FUN_00425084`, copies results in `5..33` into raw floater field `+0x18`,
invokes `FUN_00452a15`, then completes the state. This is a target-selection
and cast-action path, not a supported construction trip. Evidence: order
producer `ev_0f9c0e1151dca8d181ee42ea559e71d3987676f2680c797f76c97d5b25bbba36`,
consumer `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
action labels `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`,
target-mode resolver `ev_41f4dd45d8d838311bb4a2a6ec7147c053d632116535881470c2630ec795f60f`,
state-13 dispatch `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
arrival handler `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
and result/action cleanup `ev_8d591588cea4abce308dbbd5f69e34b5c6431010d387034afe228dee1b3385a8`,
`ev_e2908a2ae8af51fad1abf37e192dc5cf25142c2b8ab72ef3ca34fe1019d57031`.

### `FA_MergeWith` (`0x14`): approach, then idle/roam state

Order ID `0x14` (`20`) is `FA_MergeWith` and reaches switch case `0x13` in
`FUN_004211bb`. With progress zero, the consumer sets state `0x0f`, copies
target index `+0x42` to `+0x32`, clears parameter `+0x30`, and advances progress
to 1. State `0x0f` approaches the indexed runtime object using its current
coordinates and the combat-side anchor offset. Unlike ordinary state-`0x0f`
orders, FA_MergeWith uses a zero stopping radius; the handler's `<=` comparison
therefore requires exact coordinate equality.

After that approach ends and the task is consumed again, subtype 8 enters state
`0x0e`; other subtypes enter state `0x15`. State `0x0e` selects a random point
around the current position and moves with step 1 until exact arrival, then
counts down its 60-tick timer. State `0x15` resolves to the current position,
so it does not create another travel target. These are the observed follow-up
states; their relationship to merge completion is not inferred beyond the
transition itself. Evidence: order consumption and state writes
`ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
arrival and radius handling
`ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
destination selection and step behavior
`ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
and action labels `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.

### Orders without a local consumer branch

The retained `FUN_004211bb` switch has no explicit arms for `action - 1` values
2, 9, `0x0e`, `0x0f`, or `0x14`. These correspond to `FA_Fetch` (3),
`FA_Wait` (10), `FA_ChaseFlt` (15), `FA_ChaseLoc` (16), and `FA_Ascend` (21).
`FA_Fetch`'s missing local transition is noted with `FA_Deliver` above. For the
other four, the action labels alone do not establish whether another routine
consumes them, whether they are legacy values, or what movement they request;
do not infer their routes from similarly named actions. Assignment itself can
be data-driven: `FUN_00421ec1(task_index)` copies the slot's action field
`DAT_006183cc[task_index]` into the floater, and `FUN_0042219e` can attach a
validated slot without switching on that action value. Therefore an action
may be assigned even though `FUN_004211bb` has no matching local executor arm.
The current evidence does not identify another consumer for those missing
values or show that any of them produces a movement state. Evidence: task-link
copy `ev_c2d3e74dd2e94c30ca9de18f1387bb8d44d32daf432cd179e9d1b8dfc693b4dc`,
reevaluation/attachment `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`,
and order consumer `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`.

Address cross-references to the task action table base `DAT_006183cc` resolve
to four functions: `FUN_00421ec1` copies the selected slot action into the
floater order field; `FUN_00422031` validates a slot for attachment; and
`FUN_0042fa0f`/`FUN_004455d1` search or enumerate slots for the Tasks UI. The
validator has explicit handling for actions 4, 5, 11 and 18; the list builder
excludes action `0x0b`. These inspected bodies show reads/filtering at these
sites, not an alternate movement executor or a writer that maps the missing
actions to states. This makes the attachment boundary explicit: assignment is
possible, execution of the four absent local cases remains unproven.

The tick keeps action and runtime state separate. When the floater is idle,
`FUN_0041e569` passes its copied action field to `FUN_004211bb`; that consumer's
`action - 1` switch lacks the cases for Wait/Chase/Ascend. The later state
dispatch is keyed by runtime state `+0x2c`, where movement handlers for states
`0x0e` and `0x0f` do exist. No inspected branch connects the missing action IDs
10/15/16/21 to those states. The equal-looking numeric values therefore cannot
be used to infer a route. Evidence: table cross-references
`ev_da7542c8d20a92a354e31176edb14fccd1ee1f3fac24ff7f7cfd1464503b3b49`,
slot validation `ev_bd805382bd750a65076a58742501849e1bdeb29a87bc0717a5bac1e0307b1077`,
Tasks-list filtering `ev_25d048fc082b5ed144709e4886b7748e44943fd30f5e02a0e06addfc60beaec9`,
message/task lookup `ev_ed75141a79f1bac30a4ad39dcad68e710e351330bcd3044aa3cb304ef2a796b2`,
tick/state dispatch `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
and action consumer `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`.

A read of the loaded image at `DAT_006183bc` returned 0x500 initialized zero
bytes, the full 64-record span at stride `0x14`; the `.data` segment is marked
initialized. Typed incoming references to the action field `+0x10` contain a
read and address-only references, with no typed write at that exact address.
This rules out a prefilled task catalog in the inspected image bytes, but it
does not identify runtime population: a computed destination, bulk copy, or
unobserved indirect writer may not appear as an exact typed reference. Evidence:
image bytes `ev_bc254ddb3b5d4bfc3b423aa3c2a839a6aa1f4f771807016000e59944447f751e`,
segment initialization `ev_254928ccff2cf0ec576eeddf8c2bba7d672a4d24c5d348d39bb0e17288171961`,
and field references `ev_50a5fda0ff82969f755c9db1bc3df1f158c35f1c08640ce4cc393b308f55d113`.

The remaining source probe is to trace task-slot population through computed
or bulk writes and initialization phases; direct field xrefs and initialized
image bytes do not resolve that producer.

### Facing and rendered anchor

`FUN_00423068` adjusts the draw anchor and offsets for the current state, uses
flag `0x002` to select facing, and checks horizontal bounds before accepting
the adjusted anchor. `FUN_0042704b` reads that flag and mirrors the body/leg
draw scale when it is set. The state-specific anchor adjustments use different
targets (site, packed coordinate, island offsets, or local offsets); they are
not evidence of pathfinding. The remake ports the facing mirror but not the
full state-dependent anchor adjustment. Evidence:
`ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f`,
`ev_d21d92e7afdc377fecc4fce5fecca40c344273a5e036a4c507b40f99ab2e04b1`.

## Current port and limits

The player-facing `game_session_order_floater_move` helper and worker
cargo/order model have been removed. The generic movement kernel remains as a
simulation primitive; only source-assigned destinations should reach it. A
floater hit emits selection message `0x3f`; a destination order `0x4c` comes
from the distinct UI destination mode and is routed through an indirect
callback. The actual recipient gate remains unresolved. The autonomous
candidate guard `FUN_00420991` applies class, flags, and level-table tests, but
does not by itself prove which class numbers correspond to soldier/mage or
which direct orders each accepts. Source evidence establishes that the cast
action path assigns order `0x13` to an eligible unit and that the floater tick
consumes such task state; complete autonomous routes and idle-unit destination
rules remain TODOs. Soldier/mage direct orders remain disabled
until their original callback guard and table initialization are confirmed.

The REA pseudocode establishes that `FUN_00435826` chooses UI action modes
`0x10`–`0x13` using the player/type table at `DAT_00619290`, and that UI bit
`0x4` gates emission of move message `0x4c`. The table comparisons are observed
in Ghidra instructions, but its initialization and the meaning of its values
remain unresolved; it must not yet be called a soldier/mage allowlist. The `0x4c`
message then uses the `+0x48` message-routing mode and an indirect active-context
callback. The callback's recipient-class guard, obstacle/terrain collision, and
full unit-state transitions are still unproven. Trace the table owner and
callback handler before implementing player controls. Worker selection remains
inspection-only as specified by the user; no worker move
command is exposed in the remake. The confirmed producer `FUN_0045da80` writes
`FA_Cast` (`0x13`); it is not evidence of a construction assignment. `FA_Build`
has a traced consumer and site validator, but its producer and the transitions
connecting assignment, travel and placement are not yet fully reconstructed.
Do not model idle workers as random walkers: recover their
source-selected destinations and stop/arrival conditions first.

The current remake also records left/right facing from the destination direction and
uses horizontally mirrored body and leg sheets while facing left. This follows
the flag producer in `FUN_00423068` and the renderer in `FUN_0042704b`; flipped
32-bit DIB sheets are cached when the island's art is loaded. This only ports
the facing/mirror behavior: the original anchor adjustment and state-specific
render offsets in `FUN_00423068` are not fully reproduced by the current island
view, which draws a smaller subset of unit states.

## Order 9 from the Hall move context

`FUN_0044003d` hit-tests six `IWLocInfo` slots: left-click selects an occupied
slot (`0x3f`), or emits `0x32` only when the selected record's `+0x18` is not
`-1`. Right-click emits `0x4d(owner)` for a non-local owner, then always
`0x3d(1)`. These are message observations, not proven movement effects; no
evidence links the `IWMove` control to this callback. The remake's four-worker
roster selection is the supported subset; no move command is exposed.
Evidence: `ev_dfa9260d630c5590f535d54281a0b8f2c2767e3ca99d4a00ffdd596b3104b7eb`.

`FUN_0045f4f5` starts the move context after its eligibility checks; it does
not issue order 9. `FUN_0045f5c5` ends the context: for target item `0x2a`,
a different target plus successful `FUN_0046562b(owner, 8)` writes order 9
into a floater task slot. Dropping on the same object takes a position-adjustment
path. Evidence: `ev_6c942de9a792a73d84fdfda4bddbe5dc35196c59fa13110da77051c6b3595d63`,
`ev_d98532f21ef6f26838f03f508eb96bbceb47d6dbbc1a3a7678ffbfca8c9c8bf3`,
`ev_b8ac2fd034c03491f78284865a603e7dda1ce800bc85e544b13add76dde36154`.

`FUN_0045f5c5` can place action ID 9 into a floater task slot after the Hall
move context ends: the selected target must be item `0x2a`, differ from the
source object, and pass `FUN_0046562b(owner, 8)`. The action-label table calls
ID 9 `FA_DefendArea`; this is an observed label, not proof of the full gameplay
meaning of the Hall control.

When the floater is idle, `FUN_004211bb` consumes that action in switch case 8
(`action - 1`) and advances progress at `+0x46` through these observed stages:

| Progress before the branch | Runtime state and target writes | Result/next branch |
|---:|---|---|
| `0` | Set state `9`, copy packed target `+0x42` into `+0x32`, clear flag `0x004`, set progress `1`. | The per-floater tick can move toward the decoded packed coordinate while in state 9. |
| `1` | Call `FUN_00420829` on the packed target. It scans the current-island candidate list in order, applies `FUN_00420991`, and returns the first eligible candidate whose Chebyshev distance from the decoded target is below 250. | On hit, set state `0x0f`, store that candidate index in `+0x32`, set flag `0x004`, progress `2`. |
| `1`, no nearby candidate | Call `FUN_00420d97(4, packed_target)`. Mode 4 decodes the target and selects among current-island locations that pass its type/flag checks and lie within distance 90. The selector ranks eligible sites and chooses from at most ten using `FUN_0041e28e`. | On hit, set state `0x10`, store the selected location index in `+0x32`, progress `3`. If no site qualifies, reset progress to `0` so the search can be retried. |
| `2` | Set state `6`, retain the original target index, set progress to `1`. | The subsequent state-6 handler runs; movement is gated off for states 6/7. |
| `3` | Set state `7`, retain the selected location index, set progress to `1`. | The subsequent state-7 handler runs; movement is gated off for states 6/7. |

Thus the coordinate travel phase and the candidate/site follow-up are separate.
State `9` uses the packed target; the later states `0x0f`/`0x10` and `6`/`7`
are source-observed transitions, but their final gameplay effect is not fully
established by this path. `FUN_00420829` returns the first qualifying candidate
in scan order, whereas fallback mode 4 performs score-based selection. This
Hall action does not establish that the ordinary island click `0x4c` assigns
the same action. Evidence:
`ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
`ev_92d9bb1718fe3eeebfe376dbac88ead112d0c4f1f89113bc3a4cc866df7dbf24`,
`ev_2b7c3a4d07a47624e5bda9eda2a57d60b965635fa529ab925962c1b77d88b010`,
`ev_0a150ef6299ccee55e14aeab45e2de16381b5142b4063cda099503d87e818883`,
`ev_76a4661cb67067b44054706649c3ff1f80a7e9eec7116d8c36177f340ab15b36`,
`ev_f359bbf9ea4d68be9d7184310b58199071b1e8115a49a149ab72415feb7659db`,
`ev_667d311b6cd4f6b516c22975cd0e46ce337aa32ce5fe70c0d2ddd040239feb55`,
and action-label evidence `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.
`FUN_0042219e` is not this consumer; its subtype-9 branch concerns a type-4
floater.

`FUN_0042fa0f` maps the `IWMove`/`IWHallMove` names to `IWTextInfo` message
`0x3039` with parameters `(5,1)`. Separately, the `IWLocInfo` callback
`FUN_00441d3e` handles event 6: after its guards, it sends message `0x48`
when the move-context field is zero, otherwise `0x4a`. `FUN_0042970c` routes
that message according to context field `+0x48`. Independently,
`FUN_00465793` routes event category 3 subtypes 5/6 through thunks to
`FUN_0045f4f5`/`FUN_0045f5c5`. The evidence does not connect the `0x48`
dispatch to a type-3/subtype-5 event, nor establish that event 6 originates
from the `IWMove` window. The selection/commit UI route remains unknown.
Evidence:
`ev_66dacbd51cf6785b063a74bf329239127645ce19926b671235f30adca57b2aea`,
`ev_0e2ae16cc91e4a0449490e69d05f4c816b864c449ede69614ee500146eee0178`,
`ev_721b02ae62d9e81fff934679f3d0f672a102544ced812b19041e4d27311fc4f1`,
`ev_bcb9a925483956dd92de831e72742c3a6510dbd9a56729b017c9c5223fe5c3a5`,
`ev_90fc7b398e8cc430ee898f0371c196e285bf0f21c5cd78aa04fcdd060294d4ce`,
`ev_560d29325f0c28f11d75fd2ff0fe5274983745b3f9f1033098d16fb61c40a5e0`,
`ev_77f09bcf65be7f4df49ff369b2957df1474ade7c97d5617e72fa5148d5de9daf`,
`ev_1f480a49add06ef2e880e52e23d9c4de797b5916cf878e1c456d1852e5004238`,
`ev_72dddc006c4e1e255f9d20a50da596f1d4c1e470e033ced969a4b8d9fb1f9e80`,
`ev_2cea27d9cb11506662c6b3865f086398830c1271ba3439dd01827cb3b8737048`.

The four Hall rows in local `original_content/pad.txt` give base cost
`(15,0,15)`; `game_session_location_move_costs` applies the observed
`+0x4a + 1` multiplier to a runtime location's raw `+0x4a` field. Target
selection and the UI trigger are not ported yet. Cost evidence:
`ev_166ec7236cb49a5bd45dcbc859b69f029d1132243f92ee2e155015d72a50dedd`,
`ev_f92b05e1bac76d2be3a91b76e6eb420474e1d04db600d49cc8d4a55edf30587d`.

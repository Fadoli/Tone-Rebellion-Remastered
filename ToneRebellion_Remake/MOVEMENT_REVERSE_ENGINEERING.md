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

## Unit tick and speed source

| FLOAT.EXE procedure | REA evidence | Observation |
|---|---|---|
| `FUN_00422d27` (`0x422d27`) | `ev_0a3a5baa3dd85e9e4d8e576461b4c0ac5dde6dd1cb0ba6135191f046f1f98a93` | Computes a destination and effective step, clamps each axis independently, reduces the step near the target using Chebyshev distance, and advances current coordinates. The target is reported reached only when both coordinates match. |
| `FUN_0041e569` (`0x41e569`) | `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a` | In states `0x0e` and `0x0f`, computes the Chebyshev distance to the target and uses a 10-pixel default stopping radius. `FUN_00420721` can supply a unit-specific radius under other state/stat conditions. |
| `FUN_00423068` (`0x423068`) | `ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f` | Updates the object's draw anchor/offset based on target and state, sets flag bit `0x002` when the target is to the left and clears it when to the right, then checks horizontal bounds. This routine is not evidence of terrain pathfinding. |
| `FUN_0042704b` (`0x42704b`) | `ev_d21d92e7afdc377fecc4fce5fecca40c344273a5e036a4c507b40f99ab2e04b1` | Reads flag bit `0x002`; for the left-facing case negates the horizontal body/leg draw scale, producing a horizontal sprite mirror. |
| `FUN_00464242` (`0x464242`) | `ev_1559f3b44eb1bd728c2c2077c916a6ba549ae4c8310f49d5fc23ec8de61ff7cc` | Resolves a tribe/unit-class record in the runtime floater-stat table. |
| `FUN_004633a7` (`0x4633a7`) | `ev_fe7a5335c367485201a317db133bb5029b49d97a3d6cbffc7fd3926406f911ec` | Parses 45 rows with seven fields into 14-byte records; the seventh field is stored at record offset `+0x0c`. |
| `FUN_0046466f` (`0x46466f`) | `ev_fff46798e5d5d511dba4e67c4659afc2916bd8e719ba56ae3da3806f38ff09fe` | Creates four starting instances per player with unit class 0. |
| `FUN_004211bb` (`0x4211bb`) | `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957` | Consumes the order stored in a floater record. The order case `0x13` uses its stored site and advances its state/progress fields; this is part of autonomous task execution, not a player click handler. |
| `FUN_0042219e` (`0x42219e`) | `ev_d9f9f466dec9c616930d5fb954437b6cb9c603d687390540a4d8c90cdc2c0eea`; earlier dossiers `ev_04a74bd124249ab097279236e8788fcf661bc6047d7c113aea28ae262bafc6e5`, `ev_787dc785055d52728b1408fa372d280fa57be569a05f32883f94a4022cbce846` | Fresh full-function dossier covers body `0x42219e–0x422d26` (2,953 bytes). It returns early for object state 6/7 and while `DAT_006191b4` is nonzero. One class-4 branch distinguishes subtype 9; another, when flag `0x10` is clear and order field is 0 or `0x0e`, scans up to 64 records at `DAT_006183bc`, checks active/type/subtype values, calls `FUN_0041e454` and `FUN_00422031`, compares task values against object level and measured distance, and writes task state/target fields. Other branches select states 6/7/`0x0e` for owned-site or other object conditions. The body confirms conditional task scheduling and destination updates, not random roaming; the semantic meaning and source population of every task record and state still need tracing before porting these assignments. |
| `FUN_00420d97` / `FUN_00420a55` | `ev_0a150ef6299ccee55e14aeab45e2de16381b5142b4063cda099503d87e818883`; `ev_76a4661cb67067b44054706649c3ff1f80a7e9eec7116d8c36177f340ab15b36` | `FUN_00420d97` delegates to `FUN_00420a55` for the current island. Its mode 4 candidate filter requires object owner/class field 4, distance below `0x5a`, type below `0x16`, and flags masked by `0x90` clear; it retains up to 10 candidates, then delegates final selection to `FUN_0041e28e`. This identifies one source selector used by movement/task code, not a general order rule for all units. |
| `FUN_0045da80` (`0x45da80`) | `ev_0f9c0e1151dca8d181ee42ea559e71d3987676f2680c797f76c97d5b25bbba36` | Checks construction resources and an eligible unit, then stores order `0x13` plus item/site/progress data in that unit and deducts two player resource fields. |
| `FUN_004527ee` (`0x4527ee`) | `ev_1b65d37c5f980508939852c08a13046d03c79fce26bff8abdd695e5f8134eea6` | Calls `FUN_004528ca` to initialize the placed item only after `FUN_00452794` accepts the site/item; on success it sets a runtime flag and emits event 2. The exact full transition from order `0x13` to this validator still needs to be connected. |

The local original `floater.txt` defines the final field as speed. Each tribe's
`*work` row has speed 3. This agrees with the runtime access at `+0x0c` in
`FUN_00422d27` through `FUN_00464242`; this is only the worker movement
parameter, not evidence that the player can issue worker move orders.

## Current port and limits

The player-facing `game_session_order_floater_move` helper and worker
cargo/order model have been removed. The generic movement kernel remains as a
simulation primitive; only source-assigned destinations should reach it. A
floater hit emits selection message `0x3f`; a destination order `0x4c` comes
from the distinct UI destination mode and is routed through an indirect
callback. The actual recipient gate remains unresolved. The autonomous
candidate guard `FUN_00420991` applies class, flags, and level-table tests, but
does not by itself prove which class numbers correspond to soldier/mage or
which direct orders each accepts. Source evidence establishes that build
selection assigns order `0x13` to an eligible unit and that the floater tick
consumes such task state; the complete route, arrival transition, and idle-unit
destination rules remain TODOs. Soldier/mage direct orders remain disabled
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
command is exposed in the remake. Construction has a proven order assignment
path (`FUN_0045da80`), task consumer
(`FUN_004211bb`), periodic task dispatcher (`FUN_0042219e`) and site validator
(`FUN_004527ee`), but the state transitions connecting them are not yet fully
reconstructed. Do not model idle workers as random walkers: recover their
source-selected destinations and stop/arrival conditions first.

The current remake also records left/right facing from the destination direction and
uses horizontally mirrored body and leg sheets while facing left. This follows
the flag producer in `FUN_00423068` and the renderer in `FUN_0042704b`; flipped
32-bit DIB sheets are cached when the island's art is loaded. This only ports
the facing/mirror behavior: the original anchor adjustment and state-specific
render offsets in `FUN_00423068` are not fully reproduced by the current island
view, which draws a smaller subset of unit states.

## Order 9 from the Hall move context

`FUN_0045f4f5` starts the move context after its eligibility checks; it does
not issue order 9. `FUN_0045f5c5` ends the context: for target item `0x2a`,
a different target plus successful `FUN_0046562b(owner, 8)` writes order 9
into a floater task slot. Dropping on the same object takes a position-adjustment
path. Evidence: `ev_6c942de9a792a73d84fdfda4bddbe5dc35196c59fa13110da77051c6b3595d63`,
`ev_d98532f21ef6f26838f03f508eb96bbceb47d6dbbc1a3a7678ffbfca8c9c8bf3`,
`ev_b8ac2fd034c03491f78284865a603e7dda1ce800bc85e544b13add76dde36154`.

`FUN_004211bb` consumes order 9 under state 0 (case 8). It first searches
within Chebyshev distance 250; if no candidate qualifies, it searches within 90,
filters candidates, and applies weighted random selection to the top ten. It
then advances through states 15/16 to 6/7. Evidence:
`ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
`ev_92d9bb1718fe3eeebfe376dbac88ead112d0c4f1f89113bc3a4cc866df7dbf24`,
`ev_2b7c3a4d07a47624e5bda9eda2a57d60b965635fa529ab925962c1b77d88b010`,
`ev_0a150ef6299ccee55e14aeab45e2de16381b5142b4063cda099503d87e818883`,
`ev_76a4661cb67067b44054706649c3ff1f80a7e9eec7116d8c36177f340ab15b36`,
`ev_f359bbf9ea4d68be9d7184310b58199071b1e8115a49a149ab72415feb7659db`,
`ev_667d311b6cd4f6b516c22975cd0e46ce337aa32ce5fe70c0d2ddd040239feb55`.
`FUN_0042219e` is not this consumer; its subtype-9 check concerns a type-4 floater.

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

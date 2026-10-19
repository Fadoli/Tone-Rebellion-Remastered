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
initialized. The adjacent scan bound `DAT_006188bc` is also zero in the loaded
image; its sole direct reference is a read in `FUN_0042fa0f`, where it bounds
the active-task search. Typed incoming references to the action field `+0x10`
contain a read and address-only references, with no typed write at that exact
address.
The live base xrefs cover 19 sites in seven procedures: `FUN_00421ec1`,
`FUN_00422031`, `FUN_0042219e`, `FUN_0042fa0f`, `FUN_00432c74`,
`FUN_00445145` and `FUN_004455d1`. Review of their retained bodies found one
table write:
`FUN_00421ec1` increments/decrements a slot's short at `+0x04` (the claimant
count); it reads the other slot fields and copies the action, island, target
and parameter to the floater. The validator and reevaluator filter slots, the
Tasks UI searches/enumerates them, and `FUN_00432c74` formats nonempty entries
in a diagnostic task list. Their retained bodies show reads/address formation,
not population writes. This rules out a prefilled task catalog in the
inspected image bytes, but it does not identify runtime population: a computed
destination, bulk copy, or unobserved indirect writer may not appear as an
exact typed reference. Evidence:
image bytes `ev_bc254ddb3b5d4bfc3b423aa3c2a839a6aa1f4f771807016000e59944447f751e`,
segment initialization `ev_254928ccff2cf0ec576eeddf8c2bba7d672a4d24c5d348d39bb0e17288171961`,
field references `ev_50a5fda0ff82969f755c9db1bc3df1f158c35f1c08640ce4cc393b308f55d113`,
table-base xrefs `ev_17822ce9cd33c62cee9df591f32253f607cdd2842d06f0999b06c5d99173784a`,
scan-bound bytes `ev_1a41179b501410302facf114f1b939f69b226dbf2b96f46746236674007b5b1e`,
scan-bound xref `ev_2386230a22ea08ca9dee702742e0ada6673f3308dff7cb2224d379efb8d5efdc`,
task-link update `ev_c2d3e74dd2e94c30ca9de18f1387bb8d44d32daf432cd179e9d1b8dfc693b4dc`,
validator `ev_9d5d129cd6bb5e1095f8136fbde959c47360ad898c94d3104c63add6dcda3bc7`,
reevaluator `ev_d9f9f466dec9c616930d5fb954437b6cb9c603d687390540a4d8c90cdc2c0eea`,
Tasks UI `ev_25d048fc082b5ed144709e4886b7748e44943fd30f5e02a0e06addfc60beaec9`,
task-list formatter `ev_a0e3498f3ed8eb4104bd4b63541e89783f53f63203d538d435ff69c00c824209`,
and its typed references `ev_9771e1e273408598010b44e9c8a1a5d1e69b98d70114d34de4e8eda7fe6fa8cf`.

The remaining source probe is to inspect references and stores across the full
64-slot range `[0x6183bc, 0x6188bc)`, including computed/bulk writes, then trace
initialization of the observed count at `DAT_006188bc`. Exact field xrefs and
initialized image bytes alone do not resolve that producer.

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


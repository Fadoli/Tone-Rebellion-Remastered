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


Orders without a local consumer branch and facing/render details are in [the focused edge-case note](MOVEMENT_ORDER_EDGE_CASES.md).

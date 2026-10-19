# Site destination orders

### `FA_Build`: three local route states

Action 5 (`FA_Build`) is switch case `4` in `FUN_004211bb`. The consumer first
loads the requested location from island `+0x40`, location `+0x42`, then checks
the item parameter `+0x44` with `FUN_004526de`. A failed item check terminates
the task. Otherwise it selects among three routes:

There is also an upstream task-eligibility gate. During autonomous selection,
`FUN_0042219e` calls `FUN_00422031` before accepting a task record. For a
record whose action field `+0x10` is 5, the gate rejects it if the record's
parameter `+0x12` fails `FUN_004526de`. If the floater's raw `+0x18` field is
not 1 and `FUN_00452794(parameter, unit)` rejects the parameter, the gate asks
`FUN_00420dbd(1)` for an available island/site pair and accepts the task only
if that search returns one. When `+0x18` is 1, or the direct item/site check
succeeds, this gate does not require that fallback search.
This connects site availability to whether an autonomous build task is
assigned, before the route selection below; the meanings of floater `+0x18`
and task-record population remain unresolved. At field level, `FUN_004526de`
checks owner/state fields, an owner bit in the floater byte at `+0x22`, and the
comparison between an owner-table short and the selected item record's `+0x0c`.
`FUN_00452794` adds a comparison between the floater short at `+0x28` and the
selected item record's `+0x04`. The gameplay meanings of these table values
and shorts are not established. Evidence: task validator
`ev_9d5d129cd6bb5e1095f8136fbde959c47360ad898c94d3104c63add6dcda3bc7`,
item guard `ev_362f18c1c5d6399f0ca1abb08a88f3f9516320b6a45fd5724a68079716b6da56`,
site validator `ev_e884123140e558d8678b40fa79da6539532f8441ffe895daabdad5787c8afff7`,
item-record lookup `ev_f92b05e1bac76d2be3a91b76e6eb420474e1d04db600d49cc8d4a55edf30587d`,
floater short lookup `ev_83275ff82da670ce74e3ad4a2dfd317b20b7b0f0fd6513a33a0d43be184c89d9`,
reevaluator `ev_d9f9f466dec9c616930d5fb954437b6cb9c603d687390540a4d8c90cdc2c0eea`,
and action labels `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.

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

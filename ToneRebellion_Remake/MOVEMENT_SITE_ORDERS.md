# Site destination orders

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

State `3` has two distinct exact-arrival branches, so arrival does not always
end the route immediately. If the target location's raw `+0x10` equals
`0x2a`, its `+0x18` is not `-1`, or floater flag bit 0 is set, arrival sets
floater flag bit 0 and starts timer `+0x34` at 1. The timer increments up to
`0x14`; on the following update the code may copy raw parameter `+0x30` into
floater field `+0x18` and call `FUN_00452eac`, subject to the location's raw
owner `+4` being zero and `FUN_00452c31` accepting the parameter. It clears flag bit 0
and completes state `3` after that timed branch. In the alternate branch,
arrival increments the timer and asks `FUN_00452e4d(parameter, timer)`; a
positive result takes the `FUN_00425084`/`FUN_00452eac` path and completes,
while a zero result calls `FUN_00452ceb(parameter, owner)` and completes only
if that also returns zero. These are raw state transitions and helper gates;
the evidence does not name their gameplay effects. Evidence: state handler
`ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a` and
order parameters `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`.

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


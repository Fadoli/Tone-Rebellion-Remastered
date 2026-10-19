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

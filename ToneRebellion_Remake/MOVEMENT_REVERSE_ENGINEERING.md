# Floater movement primitives: REA evidence and port

This note records observed selection/input/movement procedures and separates them
from behavior still needing class/state checks. Ghidra pseudocode is a decompiler
reconstruction, not recovered source; field names and inferred types remain
provisional. The user has clarified that workers cannot receive direct orders:
selecting them only shows stats, while soldiers and mages are orderable. The
remake now routes mode `0x13` to state 9 for selected floaters with nonzero
subtype. That subtype mapping is an implementation gate following the user's
constraint; the original allowlist and `FA_Cast` interaction remain unresolved.


Sections détaillées ci-dessous. Les titres sont repris ici pour conserver les anciens liens d’ancrage.

## Input and destination path
[Section complète](MOVEMENT_INPUT.md#input-and-destination-path)

### `0x4c` coordinate order and its receiver
[Section complète](MOVEMENT_COORDINATE_ORDERS.md#0x4c-coordinate-order-and-its-receiver)

## Interaction cursor lifecycle
[Section complète](MOVEMENT_SPEED.md#interaction-cursor-lifecycle)

## Unit tick and speed source
[Section complète](MOVEMENT_SPEED.md#unit-tick-and-speed-source)

## Tick, state machine, target and arrival detail
[Section complète](MOVEMENT_TICK.md#tick-state-machine-target-and-arrival-detail)

### Update sequence
[Section complète](MOVEMENT_TICK.md#update-sequence)

### Destination resolution and step size
[Section complète](MOVEMENT_TICK.md#destination-resolution-and-step-size)

### Target source and facing adjustment
[Section complète](MOVEMENT_TICK.md#target-source-and-facing-adjustment)

### `FA_Move`: local target approach and arrival
[Section complète](MOVEMENT_LOCAL_ORDERS.md#fa_move-local-target-approach-and-arrival)

### `FA_DefendFlt`: reach target, select a nearby unit, then approach it
[Section complète](MOVEMENT_LOCAL_ORDERS.md#fa_defendflt-reach-target-select-a-nearby-unit-then-approach-it)

### Autonomous order selection and execution
[Section complète](MOVEMENT_LOCAL_ORDERS.md#autonomous-order-selection-and-execution)

### `FA_Wander` destination generation and repeated movement
[Section complète](MOVEMENT_LOCAL_ORDERS.md#fa_wander-destination-generation-and-repeated-movement)

### Attack orders: approach then stationary combat state
[Section complète](MOVEMENT_LOCAL_ORDERS.md#attack-orders-approach-then-stationary-combat-state)

### Training and recharge orders: travel to a location record
[Section complète](MOVEMENT_TRAVEL_ORDERS.md#training-and-recharge-orders-travel-to-a-location-record)

### `FA_ObtainObject`: assigned location or owner candidate
[Section complète](MOVEMENT_TRAVEL_ORDERS.md#fa_obtainobject-assigned-location-or-owner-candidate)

### Cross-island handoff through state `0x11`
[Section complète](MOVEMENT_TRAVEL_ORDERS.md#cross-island-handoff-through-state-0x11)

### `FA_Deliver`: site search, island handoff and local approach
[Section complète](MOVEMENT_SITE_ORDERS.md#fa_deliver-site-search-island-handoff-and-local-approach)

### `FA_Repair`: candidate site then local approach
[Section complète](MOVEMENT_SITE_ORDERS.md#fa_repair-candidate-site-then-local-approach)

### `FA_Build`: three local route states
[Section complète](MOVEMENT_SITE_ORDERS.md#fa_build-three-local-route-states)

### `FA_Cast` (`0x13`): target resolution without locomotion
[Section complète](MOVEMENT_SPECIAL_ORDERS.md#fa_cast-0x13-target-resolution-without-locomotion)

### `FA_MergeWith` (`0x14`): approach, then idle/roam state
[Section complète](MOVEMENT_SPECIAL_ORDERS.md#fa_mergewith-0x14-approach-then-idleroam-state)

### Orders without a local consumer branch
[Section complète](MOVEMENT_SPECIAL_ORDERS.md#orders-without-a-local-consumer-branch)

### Facing and rendered anchor
[Section complète](MOVEMENT_SPECIAL_ORDERS.md#facing-and-rendered-anchor)

## Current port and limits
[Section complète](MOVEMENT_PORT.md#current-port-and-limits)

## Order 9 from the Hall move context
[Section complète](MOVEMENT_PORT.md#order-9-from-the-hall-move-context)

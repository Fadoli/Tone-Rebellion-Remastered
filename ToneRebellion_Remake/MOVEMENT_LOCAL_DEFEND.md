# Movement Local Orders

### `FA_DefendFlt`: reach target, select a nearby unit, then approach it

Action 8 (`FA_DefendFlt`) is case `7`. At progress 0, the consumer enters
state `8`, copies task target `+0x42` to `+0x32`, clears flag `0x004`, and sets
progress to 1. State 8 is a follow approach with a moving offset, not direct
arrival at the target floater: `FUN_00423068` stores a random `[-100,99]` X/Y
offset, and each `FUN_00422d27` step adds the target floater's current
coordinates before applying the world-bound clamps. The same stored offset is
therefore carried along as the target moves. Effective speed changes to 1
when the two floaters' direct Chebyshev distance is below 100, regardless of
their distance from the offset waypoint. Later category/site modifiers can
still adjust that base value. The state handler can finish early
when `FUN_004208eb` finds a qualifying candidate; otherwise exact arrival at
the translated waypoint completes state 8.

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

The remake now exposes this route through `game_session_order_floater_to_defend`.
It carries the random offset with the live target, clamps the translated point
to the island bounds, polls for a qualifying candidate during the route, and
uses the existing state-`0x0f` combat approach after a match. This simulation
entry point is not connected to a UI or AI task producer yet.


Autonomous order selection and wandering are documented in [autonomous floater orders](MOVEMENT_AUTONOMOUS_ORDERS.md).

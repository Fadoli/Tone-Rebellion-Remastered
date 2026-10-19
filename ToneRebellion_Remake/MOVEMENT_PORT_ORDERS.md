# Floater movement port

## Coordinate orders and combat approaches

The generic movement kernel remains the simulation primitive. A floater hit
emits selection message `0x3f`; destination mode `0x13` emits order `0x4c`.
The remake now applies that coordinate order in state 9 to a selected
non-worker and uses right-click as its local input adapter. The binary receiver
checks the selected-location/link pair but does not test subtype; matching
subtype nonzero to orderable soldiers/mages follows the user's constraint and
is an implementation gate, not an observed binary class rule. The autonomous
candidate guard `FUN_00420991` applies class, flags, and level-table tests, but
does not by itself prove which class numbers correspond to soldier/mage or
which direct orders each accepts. Source evidence establishes that the cast
action path assigns order `0x13` to an eligible unit and that the floater tick
consumes such task state. The remake ports the `FA_Wander` coordinate/timer
cycle for its unlinked initial floaters, but it does not yet model the source
task-candidate scan that decides whether another task should replace wandering.
The UI mode table remains unresolved. The remake models the linked-record
transfer while idle and at the source's 10-tick reevaluation cadence while
moving. After action 9 reaches its packed point, the port scans same-island
floaters in insertion order, applies the `FUN_00420991` class/flag policy where
modeled, then falls back to eligible class-4 sites owned by player 4. Category-4
source targeting starts at level 0, matching the 15 zero-valued loaded-image
entries, so the initial branch seeks non-category-4 floaters. No direct writer
was found; indirect runtime updates remain possible. Other category-pair rules
still depend on `DAT_00619290`. Both unit and site approaches use the source's 43-unit
side-offset, then enter state 6 or 7. The bridge
now preserves the source order while the tick action is `FA_Cast` (`0x13`);
the remake does not yet produce that action itself.

The state-9 route now resolves its packed coordinate to a random waypoint with
the source's bounded offsets and global X/Y limits. Its step falls to 1 when
the floater is within 100 coordinate units of the decoded anchor, independently
of the randomized waypoint. Entity/site approaches check their previously
resolved destination against a 10-unit radius before refreshing the live target;
their radius can use the floater's catalog attack range when `FUN_00420721`'s
category/subtype/charge guard permits it. The linked-site 5/4 radius modifier
remains unmodeled because its table bit and runtime link source are unresolved.

The REA pseudocode establishes that `FUN_00435826` chooses UI action modes
`0x10`–`0x13` using the player/type table at `DAT_00619290`, and that UI bit
`0x4` gates emission of move message `0x4c`. The table comparisons are observed
in Ghidra instructions, but its initialization and the meaning of its values
remain unresolved; it must not yet be called a soldier/mage allowlist. The `0x4c`
message then uses the `+0x48` message-routing mode and an indirect active-context
callback. The receiver's linked-record guard is confirmed; its subtype gate is
not. Obstacle/terrain collision and the full source unit-state/tick transition
remain unproven. Worker selection remains inspection-only as specified by the
user; the remake rejects subtype 0 orders. The confirmed producer
`FUN_0045da80` writes
`FA_Cast` (`0x13`); it is not evidence of a construction assignment. `FA_Build`
has a traced consumer and site validator, but its producer and the transitions
connecting assignment, travel and placement are not yet fully reconstructed.
The core tick now gives unlinked initial floaters the `FA_Wander` fallback:
it generates a state-`0x0e` destination, advances with the shared kernel, waits
for exact arrival while counting down the 60-tick timer, then selects another
point. `GameRuntimeIsland` carries the source's category/island X-bound slots;
they currently retain the source sentinel defaults `0..0x9ff` because their
runtime table is not initialized from available remake inputs. Thus the route
cycle is implemented, while nondefault island/category X limits and the
source task-candidate eligibility scan remain unmodeled.

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
consumes such task state. The remake ports the `FA_Wander` moving-target
cycle for its unlinked initial floaters. Task assignment can now replace an
unlinked state-`0x0e` wander, as the source keeps polling the selector while
idle. Charge and delivery events share an ascending task-slot scan;
construction now joins that same catalog-backed scan in the floater tick, after
completed construction tasks are consumed; other source task categories remain
outside the candidate scan. REA `FUN_0042219e`
(`ev_305d6316ab1fe840f1866d8b882e4afe4dde714f9d235d819d3de9cc6111381c`)
scans all 64 source task slots and stops at the first eligible row.
The scan now also honors the source priority gates for modeled candidate types:
an owner's priority-3 row suppresses its non-special lower-priority rows, and
priority 1/2 rows use the source's assignment-count caps (999 for priority 1,
1998 for priority 2 when the floater has no current task). Charge and artifact
delivery rows use the special-task capacity rule. Special types and task
categories not handled by the remake remain outside this partial port; the
special-task classifier follows `FUN_0041e454`
(`ev_c6ecb8c8345cf4e91b0838202f18dbe0194ed92f17eb8ef9cab3711cf22fdf4`).
The UI mode table remains unresolved. The remake models the linked-record
transfer while idle and at the source's 10-tick reevaluation cadence while
moving. After action 9 reaches its packed point, the port scans same-island
floaters in insertion order, applies the `FUN_00420991` class/flag policy where
modeled, then falls back to sites with `+0x14 == 4`, item ID below `0x16`, and
flags `0x90` clear. `FUN_00420a55` uses that predicate and a 90-unit radius
(REA `ev_8cbbb89cf96f8cec18ab31fded50c934c328575c25039ff87bdd77fcf45866ed`). Category-4
source targeting starts at level 0, matching the 15 zero-valued loaded-image
entries, so the initial branch seeks non-category-4 floaters. No direct writer
was found; indirect runtime updates remain possible. Other category-pair rules
still depend on `DAT_00619290`. Both unit and site approaches use the source's 43-unit
side-offset, then enter state 6 or 7. The bridge
now preserves the source order while the tick action is `FA_Cast` (`0x13`);
the remake also retains a newer coordinate order through cast cleanup so the
next poll can apply it. This follows `FUN_0042219e` (REA
`ev_7b65b0885c0f8b591c2f99765a10875a29d00118a7a606dd55e5e6d165f65a7d`). The
remake does not yet produce the general cast action itself.

The simulation also accepts `FA_MergeWith` (`0x14`) through
`game_session_order_floater_to_merge`: it follows the target to exact contact
using state `0x0f`. Subtype 8 then wanders for 60 ticks and returns to its
owner's Hall. Other subtypes enter state `0x15`, become subtype 8 at tick 25,
and return to the Hall at tick 50. An artifact carried in raw floater `+0x18`
is dropped at the nearest free neutral location as a `PIT_Object`, or added to
the owner's inventory if no location is free. The `join6` visual is not
modeled. This order entry point is not wired to a user input or
autonomous task producer yet. The transitions follow
`FUN_004211bb` (REA `ev_3477c4218f2065db070d4efae8de369bbea8abee71d9fdd735ccbdd92f6b39ba`).

`FA_DefendFlt` (`8`) is also available through
`game_session_order_floater_to_defend`. Its state-8 movement picks a fresh
bounded random step around the defender while target selection scans within
250 units of the separately retained protected floater. A qualifying target
enters state `0x0f` for one tick, then state 6 tracks its live position while
the defender continues scanning around its ally. In the remake, right-clicking
a friendly floater issues this order;
Shift+right-click issues `FA_MergeWith` against that floater. The tick stages
follow `FUN_0041e569`, random movement follows `FUN_00423068`, and target lookup
follows `FUN_004208eb` (REA `ev_ad87da66a016a70974e90562a87b7eca6a6dc530c460c334775e5c1c0d4fe4cb`,
`ev_d4cd7abeebb8995fafaa9f6766fac6764547a0f499b94fe2e51d82cc3411373a`,
`ev_45e476a70f900a1cdcdfaa0a6d82ee5f2025db59a6f6005a7451f7eb7ef707e2`).
These are local input bindings because the original action-mode producer remains unresolved.
The AI task producer remains unconnected; the candidate search uses the
currently modeled `FUN_00420991` policy. REA confirms that `FUN_0042219e`
creates only category-4 combat orders 6/7 directly; its other-floater branch
copies the action from an already linked task row. No direct action-8 or
`0x14` assignment appears in that selector, so automatic defend/merge needs a
source task producer before it can be added (`ev_3df3eba13464779dbcdf8e83195441a5db92f8e9250be6ab8931faee3bb973c1`).

The state-9 route recomputes a random waypoint around its packed anchor on
every tick, with the source's bounded offsets and global X/Y limits.
`FA_DefendArea` now rechecks
for a target on every floater tick, including while moving or attacking, and
switches from the approach state to combat on the next tick. This follows the
state-9 branch of `FUN_0041e569`; the source performs `FUN_00420829` first and
falls back to `FUN_00420d97(4, anchor)` when no floater qualifies (REA
`ev_ad87da66a016a70974e90562a87b7eca6a6dc530c460c334775e5c1c0d4fe4cb`,
`ev_92d9bb1718fe3eeebfe376dbac88ead112d0c4f1f89113bc3a4cc866df7dbf24`,
`ev_0a150ef6299ccee55e14aeab45e2de16381b5142b4063cda099503d87e818883`).
Its step falls to 1 when the floater is within 100 coordinate units of the
decoded anchor, independently of the randomized waypoint. Entity/site
approaches check their previously resolved destination against a 10-unit
radius before refreshing the live target; their radius can use the floater's
catalog attack range when `FUN_00420721`'s category/subtype/charge guard
permits it. The linked-site 5/4 radius modifier remains unmodeled because its
table bit and runtime link source are unresolved.

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
Construction assignments now include remote target islands when an active
bridge route exists: carried Build Tone takes the target handoff directly,
while unladen workers collect first and continue to the target after pickup.
This follows the task eligibility/resource-island lookup in `FUN_00422031`
(`ev_9a8d6a7277585c3a1994ac6bdbbb0ca25b7140f4652c73a8dda17be12efc08e9`) and
`FUN_00420dbd` (`ev_7cf0de2bd4c81e6a748d36e82f9d5a47422b50d01af262b242d6c368caf87b41`).
Construction task selection now also skips pads larger than the target site's
recorded construction size, matching the placement gate and preventing a
worker from servicing an impossible task. REA's type-5 candidate path also
checks `FUN_004526de` (`ev_6ec35a83b3432018558a8d150e6258a94ee23e6a0d9200b3823fa53515caf7d3`)
and `FUN_00452794` (`ev_9eeb6de943efeb051e3413594d0496a04189ce9f94f71c5de389e5842dad08eb`)
for pad ownership, visibility, unlock level, and available Build Tone; the
remake still lacks the runtime unlock-level value (`DAT_006191f8`), so that
part of the native guard remains open.
The core tick gives unlinked initial floaters the `FA_Wander` fallback. In
state `0x0e`, the source recomputes a random destination on every update while
the Chebyshev distance is greater than 10; the remake now follows that moving
target and returns to idle inside the 10-unit radius. Subtype-8
`FA_MergeWith` uses a distinct exact-arrival roam with a fresh waypoint and a
second movement step while the merge order remains active. REA evidence:
`FUN_0041e569`
(`ev_b1d53f56383b1729239625bd9eb3200c49f52a03f3f46f72248bae5dba7b3ff5`),
`FUN_00423068` (`ev_0bef8e9452793f90d69b3ceb2975b020701db734683ad5e5c462e973813c68c4`),
and Chebyshev distance `FUN_004672a6`
(`ev_da1d99f15185527c3722e602f17a45b4674ddf8f83b6fe0c3aebe92d7aa97de6`).
`game_session_initialize_start_players` now initializes the starting island's
player-specific X bounds from the already-computed `GamePlayerStart.view_left`
and `view_right`. This matches `FUN_0046466f`
(`ev_757e8855fb92a0ab71c7d795ef92ce7542cdb16c017524307cf04e7299f6e6c9`),
which stores the Hall-centered window consumed by `FUN_00423068` and
`FUN_00420a55`. Other island/player bounds still keep the `0..0x9ff` defaults
until travel updates them; non-starting-island bounds and the source
task-candidate eligibility scan remain unmodeled.

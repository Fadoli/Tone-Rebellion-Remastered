## Current port and limits

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

The current remake also records left/right facing from the destination direction and
uses horizontally mirrored body and leg sheets while facing left. This follows
the flag producer in `FUN_00423068` and the renderer in `FUN_0042704b`; flipped
32-bit DIB sheets are cached when the island's art is loaded. This only ports
the facing/mirror behavior: the original anchor adjustment and state-specific
render offsets in `FUN_00423068` are not fully reproduced by the current island
view, which draws a smaller subset of unit states.

## Order 9 from the Hall move context

`FUN_0044003d` hit-tests six `IWLocInfo` slots: left-click selects an occupied
slot (`0x3f`), or emits `0x32` only when the selected record's `+0x18` is not
`-1`. Right-click emits `0x4d(owner)` for a non-local owner, then always
`0x3d(1,1)`. The `0x3d` arm in `FUN_0042fa0f` passes `DAT_005c37e4[1]`, message
`0x35` and the click parameters `(1,1)` to `FUN_0046c371`. That wrapper rejects
a negative active-state index (`+0x29f2`); otherwise it indexes the object
array at `+4 + recipient_index * 0x0c` and invokes that object's vtable slot
`+4`, passing a value formed from the active-state index and message `0x35`,
followed by `(1,1)`. The `ISLEVIEW` pointer is fetched by name from the window
object registry through `FUN_0046c4a5`; that helper can also return the
registry slot separately, while `FUN_0046c371` consumes its first argument as
such a slot. In this call, therefore, `DAT_005c37e4[1]` is used as a recipient
index, not passed as the recipient object pointer. Its runtime value, the
registered object's class, vtable and method body remain unresolved, so this
path cannot yet be identified as a floater movement command. The next static
probe is to trace initialization/writes to `DAT_005c37e4[1]`, then resolve that
slot's object and vtable method. This path is distinct
from map-ground message `0x4c`, whose callback and recipient guard are
unresolved independently. The remake's four-worker roster selection is the
supported subset; no move command is exposed. Evidence:
`ev_dfa9260d630c5590f535d54281a0b8f2c2767e3ca99d4a00ffdd596b3104b7eb`,
`ev_6ac7cc6650dc8a0e9b412c055606948d1c6dbbdd3e6c6df0a7fcc1551764419e`,
`ev_f8a09cad809f94f6483fa8f6623537024026f2d86fdd3f36b90ed39dbda0bd65`,
`ev_ed92b375145a0b030776f82d115ccc237230777746be74169b6aac305580d646`,
and named-window lookup `ev_8ca518262f6e9da0f51b7f516b986760a38b2cc4962b4ea5adf47c2f5b350e01`.

`FUN_0045f4f5` starts the move context after its eligibility checks; it does
not issue order 9. `FUN_0045f5c5` ends the context: for target item `0x2a`,
a different target plus successful `FUN_0046562b(owner, 8)` writes order 9
into a floater task slot. Dropping on the same object takes a position-adjustment
path. Evidence: `ev_6c942de9a792a73d84fdfda4bddbe5dc35196c59fa13110da77051c6b3595d63`,
`ev_d98532f21ef6f26838f03f508eb96bbceb47d6dbbc1a3a7678ffbfca8c9c8bf3`,
`ev_b8ac2fd034c03491f78284865a603e7dda1ce800bc85e544b13add76dde36154`.

`FUN_0045f5c5` can place action ID 9 into a floater task slot after the Hall
move context ends: the selected target must be item `0x2a`, differ from the
source object, and pass `FUN_0046562b(owner, 8)`. The action-label table calls
ID 9 `FA_DefendArea`; this is an observed label, not proof of the full gameplay
meaning of the Hall control.

When the floater is idle, `FUN_004211bb` consumes that action in switch case 8
(`action - 1`) and advances progress at `+0x46` through these observed stages:

| Progress before the branch | Runtime state and target writes | Result/next branch |
|---:|---|---|
| `0` | Set state `9`, copy packed target `+0x42` into `+0x32`, clear flag `0x004`, set progress `1`. | The per-floater tick can move toward the decoded packed coordinate while in state 9. |
| `1` | Call `FUN_00420829` on the packed target. It scans the current-island candidate list in order, applies `FUN_00420991`, and returns the first eligible candidate whose Chebyshev distance from the decoded target is below 250. | On hit, set state `0x0f`, store that candidate index in `+0x32`, set flag `0x004`, progress `2`. |
| `1`, no nearby candidate | Call `FUN_00420d97(4, packed_target)`. Mode 4 decodes the target and selects current-island class-4 sites owned by player 4, with item ID below `0x16`, flags `0x90` clear, and distance below 90. The selector retains at most ten nearest sites and chooses among them with inverse-distance weights via `FUN_0041e28e`. | On hit, set state `0x10`, store the selected location index in `+0x32`, progress `3`. If no site qualifies, reset progress to `0` so the search can be retried. |
| `2` | Set state `6`, retain the original target index, set progress to `1`. | The subsequent state-6 handler runs; movement is gated off for states 6/7. |
| `3` | Set state `7`, retain the selected location index, set progress to `1`. | The subsequent state-7 handler runs; movement is gated off for states 6/7. |

Thus the coordinate travel phase and the candidate/site follow-up are separate.
State `9` uses the packed target; the later states `0x0f`/`0x10` and `6`/`7`
are source-observed transitions, but their final gameplay effect is not fully
established by this path. `FUN_00420829` returns the first qualifying candidate
in scan order, whereas fallback mode 4 performs score-based selection. This
Hall action does not establish that the ordinary island click `0x4c` assigns
the same action. Evidence:
`ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
`ev_92d9bb1718fe3eeebfe376dbac88ead112d0c4f1f89113bc3a4cc866df7dbf24`,
`ev_2b7c3a4d07a47624e5bda9eda2a57d60b965635fa529ab925962c1b77d88b010`,
`ev_0a150ef6299ccee55e14aeab45e2de16381b5142b4063cda099503d87e818883`,
`ev_76a4661cb67067b44054706649c3ff1f80a7e9eec7116d8c36177f340ab15b36`,
`ev_f359bbf9ea4d68be9d7184310b58199071b1e8115a49a149ab72415feb7659db`,
`ev_667d311b6cd4f6b516c22975cd0e46ce337aa32ce5fe70c0d2ddd040239feb55`,
and action-label evidence `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.
`FUN_0042219e` is not this consumer; its subtype-9 branch concerns a type-4
floater.

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

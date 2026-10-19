## Tick, state machine, target and arrival detail

The following separates the per-world update, per-floater order controller,
order executor and coordinate step. Offsets are raw accesses seen in the
decompiler; they are not recovered source declarations. Evidence for the
function bodies is in `functions/0010_batch_0006.md` and
`functions/0017_batch_0013.md`.

### Update sequence

`FUN_00466ce2` iterates active floater records from the fixed 256-slot table
and invokes `FUN_0041e569` for each live record. The latter calculates the
record index using a `0x4c` stride. Evidence:
`ev_b51f2311ff9bd9ad209f0663ea00bfe330e7ff0eff117e8a273292d3112a4e0e` and
`ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`.
Within that update:

1. `FUN_0042219e` reevaluates the order when runtime state `+0x2c` is zero, or
   when `(DAT_00618e44 + floater_index) % 10 == 0` for another state.
2. If state `+0x2c` is zero and action/order `+0x3c` is nonzero,
   `FUN_004211bb` consumes that action and may set the next runtime state,
   target fields and progress fields.
3. The common movement call to `FUN_00422d27` is enabled only when state is
   not `0`, `6`, `7`, `0x0f` or `0x10`, and no flag from mask `0x411` is set.
4. The state-specific switch then handles arrival and action completion. State
   `0x0e` uses the common movement result and decrements its timer only when
   the step routine reports exact arrival. States `0x0f` and `0x10` use the
   radius-based state-specific arrival handler. Both are excluded from the
   common movement call, so each can make at most one state-specific movement
   step in that update.

The return from `FUN_00422d27` means both current coordinates equal its
resolved destination exactly. Runtime states `0x0f` and `0x10` can finish at
a wider radius: they compare Chebyshev distance against 10 by default, use
zero when action/order is `0x14`, and let a nonzero result from `FUN_00420721`
replace the default. The special `0x14` action is `FA_MergeWith`. Reaching
that radius finishes those states even when the coordinate kernel did not
return exact equality. When state `0x0f` finishes with no unit-specific radius
and action/order other than `0x14`, the update also sets bit `0x10` on the
referenced island record and bit `0x40` on the floater flags. State `0x0e`
uses exact coordinate arrival to count down its state timer instead. The
semantic names for these bits remain unresolved. Evidence:
`ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`.

`FUN_00420721` explains when the optional radius replaces 10. It returns zero
unless `FUN_004207c2` returns zero; that guard allows category 4, or a
nonzero subtype when the floater's short at `+0x22` is positive. Otherwise it
reads the first short from `FUN_00464242(category, subtype)`. The local
`floater.txt` header identifies that column as attack range, so states
`0x0f`/`0x10` can stop at the unit's data-defined attack range instead of the
default radius 10. If `FUN_004207f2` resolves a linked site (`+0x0c != -1`)
and bit `0x4` is set in the table dword addressed from
`DAT_00619242 + category * 0x14a0`, a positive attack range is changed to
integer `floor(range * 5 / 4)`. The semantic meaning of that table bit remains
unestablished. Evidence:
`ev_234f0678b3bbd27430c793e465dfd5095240536d821d1821e23bb5b1acb00e41`,
`ev_601b55f72156209d4f5c1ae6f9060918a71e3fc3423c72c12074227bdb69a5c6`,
`ev_400be7fc416e3e48c58ebeae7f1497639f909f0569891b58d5b3cba579bbab2a`.

The four initial workers use categories 0–3, subtype 0 and charge `+0x22 = 0`,
so this guard returns no stat radius for them; their state-`0x0f`/`0x10`
arrival radius remains 10 unless their action is `0x14`. Evidence:
`ev_ac313cb8cc73f9c102676395cd14cb97b5b1f9355d074df1e6656ce028d2d36f`,
`ev_0ca802ac15043c61c073f6d68546619fc924a4ba10fd4d9f04e203668dc62ed7`.

### Destination resolution and step size

`FUN_00422d27` starts with the signed-short pair at floater offsets `+0x28`
and `+0x2a` as a pixel destination. It resolves special runtime states before
choosing the effective step:

| Runtime state | Target/step handling observed |
|---|---|
| `8` | Adds the live X/Y of the target floater at `+0x32` to the stored `+0x28/+0x2a` offset, then clamps X to `0..0x9ff` and Y to `0x28..0x122`. If `FUN_00420600` reports Chebyshev distance below 100 between the two floaters, selects base step 1 before later modifiers. It also sets or clears facing flag `0x002` from the resolved X target. |
| `9` | Decodes the packed coordinate at `+0x32` with `FUN_0041e427` (each byte expands to a multiple of 10), then selects base step 1 when `FUN_004672a6` between current and decoded target is below 100. |
| `0x0e` | Selects base step 1. |
| Other states | Loads the base speed from stat record `FUN_00464242(category, subtype) + 0x0c`. |

State `9` uses two related but distinct targets. `FUN_00423068` expands the
packed coordinate and generates a randomized waypoint around it, storing that
waypoint in `+0x28/+0x2a`; `FUN_00422d27` advances toward this stored pair.
However, the base-step-1 near-target override compares the floater's current
coordinates to the expanded packed coordinate itself, using strict Chebyshev
distance `< 100`. The random waypoint does not participate in that speed
predicate. A floater can therefore switch to step 1 while still approaching
the waypoint, or retain its stat speed near the waypoint if it lies outside
the 100-unit box around the packed anchor. Evidence: destination generation
`ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f`,
coordinate step `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
and Chebyshev helper `ev_d6e45300f5ee5de4ed13ebfa3da2e5198981b6af36bc072d956c795033a50243`.

After that state-specific choice, a subtype-0 unit doubles its step when the
per-category value at `DAT_00618f5a` is positive. If `FUN_004207f2` reports
the relevant current-site condition, the code also checks the owner's bits at
`DAT_00619242` against current site item IDs `0x2c`, `0x2d` and `0x2e`; the
matching cases add one to the step. The exact gameplay meaning of those
modifiers is not established here.

The remake now exposes this selection as `floater_motion_effective_speed` in
`src/core/floater_motion.c`. Its caller must resolve the raw stat speed and the
state-8/9 distance predicate, category modifier, and owner/site bonus first;
the helper deliberately does not guess those world-state inputs. The existing
`game_session_tick_floater_moves` path still supplies a direct destination and
base speed, so this state-aware helper is groundwork for the autonomous tick,
not a claim that task assignment or destination resolution has been ported.
Evidence: `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`.

The kernel measures Chebyshev distance `max(abs(dx), abs(dy))`. If that value
is less than four times the selected step, it reduces the step to
`distance / 4` using integer division. If this becomes zero, the global tick's
low bit selects a zero- or one-pixel step. It then clamps X and Y deltas
independently to `[-step, +step]`, updates both coordinates, and reports exact
arrival only if both match the target. This is axis-clamped motion rather than
a normalized vector step. The examined code does not establish terrain
pathfinding or obstacle avoidance. Evidence:
`ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
`ev_99ac9bec204079134afb4ec773ba173dab2b1a1a87ae06d72f28cad8c8cbfff9`,
`ev_0c9a83fe313044ec813605a6f5e71760fcbcf78e0fff164432184e30593c562d`.

The low-bit fallback only applies after a positive step has been reduced by
the near-target division. If the selected effective speed is already zero,
then `distance < 4 * step` is false for every nonzero distance, the kernel
leaves `step` at zero, applies zero deltas on both axes, and reports no
arrival. There is no general minimum-speed fallback: a zero-speed floater
stalls until its speed context changes. The remake's coordinate kernel
preserves this distinction, so callers must not silently replace a missing or
zero stat with speed 1. This follows directly from the same step procedure and
does not depend on an additional runtime assumption.

### Target source and facing adjustment

`FUN_00423068` resolves the next pixel pair from the runtime state and target
index. The main coordinate sources observed in its switch-like conditions are:

| Runtime state / family | Coordinate source before anchor adjustment |
|---|---|
| `6` or `0x0f` | Current coordinates of the floater indexed by `+0x32`; these are live entity coordinates, so an approach can track a moving target. |
| `0x10` | Coordinates from the current island's location record indexed by `+0x32`. |
| `0x0e` | Current floater coordinates plus two bounded offsets in `[-100,99]`; Y is then clamped to `0x28..0x122`. |
| `9` | The packed target at `+0x32` is expanded by `FUN_0041e427`, then the same two bounded offsets are applied. |
| `0x15` | The floater's current coordinates; this branch does not introduce a new travel point. |

Other ordinary states select a location record from the current island. State
`8` follows a separate special case that draws two offsets around coordinate
origin rather than using selected location coordinates. `FUN_00423068` stores
that pair in `+0x28/+0x2a`; on every state-8 step, `FUN_00422d27` adds the
target floater's current coordinates from `+0x32` before clamping the effective
destination. The saved pair is not replaced by this translated coordinate, so
the same offset follows a moving target. The state-8 step-1 predicate compares
the two entities directly and is independent of that offset waypoint. For
entity-target states `6`/`0x0f` and location-approach state `0x10`, the helper
compares target X with current X, sets/clears facing flag `0x002`, and places
the approach point 43 coordinate units on the floater's side of the target. In
the entity-target path only, order `FA_MergeWith` (`0x14`) suppresses this
offset and permits exact-coordinate approach. If target X equals current X,
the helper leaves the facing flag unchanged but keeps its default 43-unit
offset, placing the approach point to the left of the target.
Location targets can receive other adjustments based on their raw
class/type/flags, sprite metrics, and helper results; those conditions remain
field-based rather than named terrain or collision rules. A final horizontal-bounds check controls whether
`+0x28/+0x2a` are written. This is target resolution and visual/body spacing,
not evidence of obstacle avoidance or continuous cross-island movement.
In particular, `FA_Move`'s runtime state `1` does not use the 43-unit
side-offset branch: its initial target is the location record's X/Y, and the
resolver adds offsets only when raw location `+0x10 == 0x2a` or `+0x18 != -1`.
Under that guard it requests offset mode 6 from `FUN_00450197`; otherwise the
offset pair stays zero. The final X-bounds check still gates storing the
destination. Thus the 43-unit approach geometry applies to entity states
`6`/`0x0f` and location state `0x10`, not to all orders that travel to a place.
One vertical adjustment is table-driven: `FUN_0040ad94(parameter)` returns
zero outside parameter IDs `5..33`, otherwise reads one of 29 shorts from
`DAT_0049acbe`. The location resolver subtracts this value from destination Y
in state `0x0d`, in state `4` for raw location class 2, and for raw location
item IDs 0 or 1. The short table's gameplay meaning is not established, so it
remains a raw anchor correction rather than a named height or terrain rule.
Evidence: `ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f`,
with state consumers in
`ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a` and
`ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`;
offset lookup `ev_2051246410a63d4b65ce11be1e28fceb301af46227914716355c6e0125d2722c`;
parameter-to-short lookup `ev_4586db16c58a3a23f362dc453333b4eb5755cdcdae4773f387b9a5f6b954977a`.

States `0x0f` and `0x10` do not use the common movement call in the floater
tick. Their state handler first compares Chebyshev distance against its
arrival radius; only while outside that radius does it resolve the destination
again with `FUN_00423068` and perform one `FUN_00422d27` step. For `0x0f`,
that refresh reads the target floater's current coordinates, so the approach
tracks a moving entity and can end without exact coordinate equality. For
`0x10`, the refresh reads the indexed island-location record. The arrival test
uses the previously stored destination; when it is already inside the radius,
the state completes before refreshing the target or taking a step. **Consequence
of this ordering:** if a target floater moved since its coordinates were last
resolved, the approach can complete while the floater is within radius of that
old point, without checking the target's new position on that update. If the
old point is outside the radius, the handler resolves the target's current
position and attempts one step. This consequence follows from the observed
branch ordering; it is not a separately named source rule. This is a
state-specific approach rule, not general pathfinding. Evidence:
`ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
`ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f`,
`ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`.


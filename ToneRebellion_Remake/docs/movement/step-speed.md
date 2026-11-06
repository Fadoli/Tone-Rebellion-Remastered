# Movement step kernel

## Destination resolution and step size

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
`(distance + 3) / 4`, rounding up. If this becomes zero, the global tick's low
bit selects a zero- or one-pixel step; for a positive remaining distance the
rounded step is at least one. It then clamps X and Y deltas independently to
`[-step, +step]`, updates both coordinates, and reports exact arrival only if
both match the target. This is axis-clamped motion rather than a normalized
vector step. The examined code does not establish terrain pathfinding or
obstacle avoidance. Evidence:
`ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
`ev_99ac9bec204079134afb4ec773ba173dab2b1a1a87ae06d72f28cad8c8cbfff9`,
`ev_0c9a83fe313044ec813605a6f5e71760fcbcf78e0fff164432184e30593c562d`.

If the selected effective speed is already zero, then `distance < 4 * step` is
false for every nonzero distance, the kernel leaves `step` at zero, applies
zero deltas on both axes, and reports no arrival. There is no general
minimum-speed fallback: a zero-speed floater stalls until its speed context
changes. The remake's coordinate kernel preserves this distinction, so callers
must not silently replace a missing or zero stat with speed 1. The port returns
early when already at the destination; the native low-bit fallback in that
case cannot change either coordinate.

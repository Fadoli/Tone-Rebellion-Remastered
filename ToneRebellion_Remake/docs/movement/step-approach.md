# Movement step kernel

## Target refresh and approach

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

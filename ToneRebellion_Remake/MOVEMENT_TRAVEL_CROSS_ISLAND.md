# Movement Travel Orders

### Cross-island handoff through state `0x11`

`FUN_004210a9(target_island)` is the shared island-handoff helper used by
several order branches. A target of `-1` or the current island succeeds
without changing state. Otherwise it scans the current island's location
records for eligible records with raw class `+0x04 == 2` and flag bit `0x001`
set. It immediately prefers the first record whose `+0x36` equals the target
island; failing that, it keeps the nearest eligible record by the same
Chebyshev-distance score, provided the score is below 6000. If none qualifies,
it returns 0. On success it sets runtime state `0x11`, stores the departure
record index in `+0x32` and the target island in `+0x30`.

State `0x11` then moves normally to the selected departure record. Its handler
waits for the common coordinate step to report exact arrival; if the departure
record's flag bit `0x001` is clear, the state ends. If the bit is set, a timer
starts. At timer 60 the update checks for an active matching location on the
target island and chooses a 200- or 500-tick wait, then adds 120. At timer 120
it places the floater at that destination-island record; if the record is
missing or inactive, it selects the nearest eligible class-2 record within
distance 8000 of an order-dependent reference point. It writes the floater's
position to that record's `(x, y - 30)`, synchronizes the stored destination
pair, and changes the floater's current-island field to the target island.
That fallback reference is selected from the still-stored action and target:
orders 6 and 8 use the current coordinates of the floater indexed by `+0x42`;
order 9 decodes the packed coordinate there; other orders use the target
island's location record at `+0x42`, except order `0x0e`, which retains the
literal reference `(0x500, 0xa0)`. The fallback scan then considers only
records whose raw class is 2, whose active flag bit 0 is set, and for which
`FUN_00420ed9` succeeds, keeping a record only when its Chebyshev distance is
strictly below the current best (initially 8000). Thus a missing arrival pad
does not mean “nearest to the floater's departure point” uniformly; the
reference depends on which order led into the handoff. Evidence: the state
handler `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`
and target-coordinate resolver `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`.
The preferred-pad check is also repeated across the transfer: at timer 60 the
lookup scans the target island for the first raw class-2 record whose `+0x36`
endpoint equals the source island, then the caller rejects it if flag bit 0
is clear. At timer 120 it repeats that same lookup and active-bit check before
using the record. If the second lookup no longer qualifies, the distance-based
fallback runs. This revalidation means the chosen arrival record is not
guaranteed to be the same record found before the wait. The lookup helper
itself does not filter on the active bit; that check belongs to the state
handler. Evidence: `FUN_00466c08` lookup
`ev_c50cc6e829d1545a0ff5b6cadf8d1248dabad2086db613e1f1ba72423d27b6fb` and
state handler `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`.
The countdown then continues to 60 before the state completes. These are tick
counts, not verified seconds. The code therefore shows a walk to a local
handoff site, a timed wait, a discrete position/island change, and a second
wait; it does not show continuous motion between islands. Evidence:
handoff selector `ev_dd046f002c50d0d9e841af455f3dd8fc8b70d1b11f430f2fa5c0185edc5f5121`,
per-floater transition `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
destination-island lookup `ev_c50cc6e829d1545a0ff5b6cadf8d1248dabad2086db613e1f1ba72423d27b6fb`,
and coordinate step `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`.

## Remake port

The coordinate-order API now accepts a destination island different from the
floater's current island. It selects a departure marker using the same
endpoint-first, nearest-within-6000 rule, walks there, waits 60 ticks, then
waits 200 ticks when the reciprocal marker is active or 500 when it is not.
At timer 120 it rechecks the reciprocal marker and otherwise chooses the
nearest active class-2 marker within 8000 of the packed destination coordinate.
The floater appears at `(marker.x, marker.y - 30)`, updates island access and
horizontal bounds on first entry, waits until timer 60, and resumes its
coordinate order on the destination island. `FUN_00466b09`'s event emission is
not modeled yet. This port is grounded by REA Evidence
`ev_c4c31ca182a9de59d1857dd8692b44bb5c634fa49bf26b159390ca12c1670270`
(`FUN_004210a9`), `ev_8578fcc7430b99a9d136eb0b2ff8e2854d7c283d39d2eccf477e4abff89249b4`
(`FUN_0041e569`), `ev_a1320147f184399943ce271ba0fbcd2f683878803bd3fc1f71e6ef7ebee5330b`
(`FUN_00466c08`), `ev_91561184d908c1ab3ed34a431eaf16bd34ca04cc463b048c991fbb44863afe98`
(`FUN_00420ed9`), and `ev_4846081c4f2118a55d5a3f04ab48748e6d7988dd57dd442b30ef90fdefcf6b3f`
(`FUN_00466b09`).

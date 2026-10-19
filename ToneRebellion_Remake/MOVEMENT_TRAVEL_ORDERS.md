### Training and recharge orders: travel to a location record

For these orders, `FUN_004211bb` first compares the task's target-island field
`+0x40` with the floater's current island `+0x0e`. If they differ, it passes
the target to `FUN_004210a9` and clears the task link if that call returns 0.
The following local-state transitions occur when the target island is already
current (or unspecified):

| Order | Order consumer writes | Movement and arrival behavior |
|---|---|---|
| `2` (`FA_Recharge`) | Switch case `1` sets runtime state `2`, copies target index `+0x42` to `+0x32`, copies parameter `+0x44` to `+0x30`, and sets progress to `-1`. | State `2` passes the common movement gate. The coordinate step resolves `+0x32` as an island location record and approaches its derived destination. When the exact step result reports arrival, the state handler sets flag bit `0x001`, waits through its counter, and then adjusts one of two raw floater fields subject to stat limits and helper results. It clears the flag and finishes when those conditions say no further adjustment applies. |
| `17` (`FA_UseBridge`) | Switch case `0x10` is grouped with case `1` and performs the same state-2 target/parameter writes as `FA_Recharge`. | Uses the same state-2 movement and arrival handler. The action label does not by itself establish which bridge object or animation is involved. |
| `11` (`FA_Enlist`) | Switch case `0x0a` shares the direct transition with case `0x0b`: set runtime state to the action ID, copy `+0x42` to `+0x32`, `+0x44` to `+0x30`, reset timer `+0x34`, and set progress to `-1`. | State `11` resolves the target as a location record. On exact arrival, the handler checks `FUN_00450385` and `FUN_0045c772`; if both allow it, it calls `FUN_0045c470` and starts its counter. |
| `12` (`FA_Train`) | Switch case `0x0b` performs the same direct target/parameter/state writes as case `0x0a`. | State `12` resolves `+0x32` through the island-location table. On exact arrival, the handler calls `FUN_0045c797` if `FUN_00450385` and `FUN_0045c772` allow it, then advances its counter. |

The location record provides the approach coordinates; these consumers do not
assign a fresh pixel destination directly. Both routes can therefore be
reconstructed through local arrival, but the source-level meanings of the
extra parameter and the adjusted fields remain unresolved. I keep “recharge”
and “train” as action-table labels; the movement evidence alone does not
establish what the fields changed on site represent. Evidence: order and
cross-island consumption `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
state handling `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
location destination resolution `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
and action labels `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.

### `FA_ObtainObject`: assigned location or owner candidate

Action 13 (`FA_ObtainObject`) is switch case `0x0c` in `FUN_004211bb`. The
consumer first compares raw floater field `+0x18` with the action parameter
`+0x44`. If equal, it searches candidate mode 2 for the owner; a local result
enters state `4` with the returned location index in `+0x32` and the parameter
in `+0x30`. If no candidate exists, it delegates to the owner's home island
through `FUN_004210a9`. Otherwise, on the assigned island `+0x40`, it enters
runtime state `13` (`0x0d`), copies assigned location `+0x42` to target `+0x32`,
copies parameter `+0x44` to `+0x30`, and sets progress to `1`. A remote assigned
island is handled by the same cross-island helper.

State `13` is not the special runtime state `0x13` (19 decimal), so its
coordinate step uses the ordinary location-record route. `FUN_00423068`
resolves target record `+0x32`; in state `0x0d`, it adjusts the raw location
coordinates to `X = locationX - visualMetric[+0x4a]` and
`Y = locationY - visualMetric[+0x4c] - FUN_0040ad94(parameter[+0x30])`.
The two visual metrics are shorts read from the resolved visual record, not
named dimensions in the available pseudocode. `FUN_0040ad94` contributes zero
for parameter IDs outside `5..33` and otherwise returns a short from
`DAT_0049acbe`; the table's semantic meaning remains unknown. After the
resolver's final X-bounds gate, `FUN_00422d27` moves current coordinates toward
the stored pixel target. Evidence: resolver `ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f`;
table helper `ev_4586db16c58a3a23f362dc453333b4eb5755cdcdae4773f387b9a5f6b954977a`.
The state handler maps runtime state `13` to case `0x0c`: it reads a result
through `FUN_004502dc`, cancels the order when that result is zero, and on
arrival calls `FUN_00452a15` for results in the range `5..33` before completing
the state. This confirms local travel and a post-arrival action path, but does
not by itself establish the object's identity or the full meaning of the
parameter/result fields. Evidence: action consumer
`ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
state handling `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
coordinate destination and step `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
result lookup `ev_8d591588cea4abce308dbbd5f69e34b5c6431010d387034afe228dee1b3385a8`,
and action labels `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.

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


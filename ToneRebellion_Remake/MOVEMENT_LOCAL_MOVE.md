# Movement Local Orders

### `FA_Move`: local target approach and arrival

Action 1 (`FA_Move`) is case `0` of `FUN_004211bb`'s `order - 1` switch. When
its destination island is current (or unspecified), it sets runtime state 1,
copies task target `+0x42` to floater target `+0x32`, and sets progress
`+0x46` to `-1`. If the assigned island is remote, the shared pre-switch path
delegates to `FUN_004210a9`, which selects the local handoff site and changes
to state `0x11` (hexadecimal 17, the transit state documented below). No
continuous coordinates are integrated across islands.

Local state 1 passes the common movement gate. `FUN_00422d27` uses the normal
unit speed and resolves `+0x32` through the current island's location table;
`FUN_00423068` applies the location/state-specific anchor offset and bounds
checks before storing the pixel destination. The coordinate kernel then
advances the floater by clamped per-axis steps. When both current coordinates
equal that destination, the state handler completes state 1. A special
category-4/subtype-9 branch may also change the target location's raw fields
and call two helpers on arrival; the evidence does not identify this branch
as a general player move effect. Evidence: action consumer and island route
`ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
state tick/arrival `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
destination resolution and coordinate step
`ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
handoff `ev_dd046f002c50d0d9e841af455f3dd8fc8b70d1b11f430f2fa5c0185edc5f5121`,
and action labels `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.

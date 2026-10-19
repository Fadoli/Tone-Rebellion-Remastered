# Movement Travel Orders

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

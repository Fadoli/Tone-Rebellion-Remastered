# Site destination orders

### `FA_Repair`: candidate site then local approach

Action 18 (`FA_Repair`) is switch case `0x11` in `FUN_004211bb`. If raw floater
field `+0x18` is `1`, the order uses its assigned island/location fields:
when the current island matches `+0x40`, it enters state `4`, copies location
`+0x42` to target `+0x32`, and stores `1` at `+0x30`; otherwise it delegates
to `FUN_004210a9(+0x40)`.

For other `+0x18` values, it calls `FUN_00420dbd(1)` to obtain an island and
location pair. No pair cancels the task link. A local pair enters state `3`
with its location index at `+0x32`, `1` at `+0x30`, and timer `+0x34` reset
to zero; a remote pair is handed to `FUN_004210a9(island)`, with task
cancellation if that call returns zero. Once the floater is at the selected
island, states `3/4` use the same location-record movement and arrival paths
described for `FA_Deliver`: state `3` runs its timed arrival interaction,
while state `4` calls the placement validator on exact arrival when raw
location field `+0x04` is zero. The order label is “Repair”, but these paths
alone do not identify the repaired object or the fields changed at the site.
Evidence: order consumer `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
state handling `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
candidate lookup and movement `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
and placement validation `ev_ff5099639bbdcb8c257ae4e8f690ea98f0ebdf4321753ff832e66ba4dc11d800`.

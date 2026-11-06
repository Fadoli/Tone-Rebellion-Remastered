# Movement Travel Orders

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

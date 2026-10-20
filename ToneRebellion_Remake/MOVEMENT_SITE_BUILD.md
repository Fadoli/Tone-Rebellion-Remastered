# Site destination orders

### `FA_Build`: three local route states

Action 5 (`FA_Build`) is switch case `4` in `FUN_004211bb`. The consumer first
loads the requested location from island `+0x40`, location `+0x42`, then checks
the item parameter `+0x44` with `FUN_004526de`. A failed item check terminates
the task. Otherwise it selects among three routes:

There is also an upstream task-eligibility gate. During autonomous selection,
`FUN_0042219e` calls `FUN_00422031` before accepting a task record. For a
record whose action field `+0x10` is 5, the gate rejects it if the record's
parameter `+0x12` fails `FUN_004526de`. If the floater's raw `+0x18` field is
not 1 and `FUN_00452794(parameter, unit)` rejects the parameter, the gate asks
`FUN_00420dbd(1)` for an available island/site pair and accepts the task only
if that search returns one. When `+0x18` is 1, or the direct item/site check
succeeds, this gate does not require that fallback search.
This connects site availability to whether an autonomous build task is
assigned, before the route selection below; the meanings of floater `+0x18`
and task-record population remain unresolved. At field level, `FUN_004526de`
checks owner/state fields, an owner bit in the floater byte at `+0x22`, and the
comparison between an owner-table short and the selected item record's `+0x0c`.
`FUN_00452794` adds a comparison between the floater short at `+0x28` and the
selected item record's `+0x04`. The gameplay meanings of these table values
and shorts are not established. Evidence: task validator
`ev_9d5d129cd6bb5e1095f8136fbde959c47360ad898c94d3104c63add6dcda3bc7`,
item guard `ev_362f18c1c5d6399f0ca1abb08a88f3f9516320b6a45fd5724a68079716b6da56`,
site validator `ev_e884123140e558d8678b40fa79da6539532f8441ffe895daabdad5787c8afff7`,
item-record lookup `ev_f92b05e1bac76d2be3a91b76e6eb420474e1d04db600d49cc8d4a55edf30587d`,
floater short lookup `ev_83275ff82da670ce74e3ad4a2dfd317b20b7b0f0fd6513a33a0d43be184c89d9`,
reevaluator `ev_d9f9f466dec9c616930d5fb954437b6cb9c603d687390540a4d8c90cdc2c0eea`,
and action labels `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.

| Condition | Local route | Arrival behavior |
|---|---|---|
| Target location raw field `+0x04` is zero and `FUN_00452794(+0x44, owner)` accepts it | On the target island, enter state `5`, target the requested location through `+0x32`, store item parameter `+0x44` at `+0x30`, and set progress `-1`. If remote, hand off through `FUN_004210a9(+0x40)`. | State `5` uses the location-derived movement destination. On exact arrival it ends the state and calls `FUN_004527ee(+0x30, owner)` when location field `+0x04` is zero. |
| Raw floater field `+0x18` is `1` | On the target island, enter state `4`, target location `+0x42`, and store `1` at `+0x30`; if remote, delegate to `FUN_004210a9(+0x40)`. | State `4` uses the same location approach and arrival validator described above. |
| Neither prior condition applies | `FUN_00420dbd(1)` selects an island/location pair. No result terminates the order. A local result enters state `3`, stores its location at `+0x32`, stores `1` at `+0x30`, and resets timer `+0x34`; a remote result is handed off to the selected island. | State `3` uses the location-derived destination and its timed arrival interaction, rather than the state-4/5 placement call. |

The action table labels ID `5` `FA_Build`; the selection branches show that
the order can travel to a fallback site through state `3` or `4` before its
placement attempt. States `4/5` invoke the placement validator only on exact
arrival and when the raw location field is zero; the validator's own item/site
checks can still reject placement. Evidence: order and route
`ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
movement/arrival `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
location resolution `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
item checks `ev_e884123140e558d8678b40fa79da6539532f8441ffe895daabdad5787c8afff7`,
placement `ev_ff5099639bbdcb8c257ae4e8f690ea98f0ebdf4321753ff832e66ba4dc11d800`,
and action labels `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.

The deferred `CONSTR` path must preserve the same empty-site states as
`FUN_004526de`: raw location ID `0` or `1`, with owner `-1` and the player's
visibility bit. The port previously canceled tasks and rejected Build Tone
deposits when the raw ID was `1`, even though candidate validation and final
placement accept that state. This affected bridge-linked placeholder sites
(`+0x24` carries their link data), so valid tasks could be released early or
fail to accumulate their cost. Assignment, deposit and completion now retain
both states; regressions cover a full Build Tone delivery and placement on a
state-`1` site with the requesting player's owner and runtime PAD ID.

### Placement record initialization

`FUN_004527ee` validates placement, calls `FUN_004528ca(item, owner)`, sets
flag `0x10`, then recalculates active state. The initializer writes the base
item ID to `+0x10`, player to `+0x14`, clears stocks `+0x28/+0x2a/+0x2c`, charge
field `+0x30`, and capacity `+0x4a`, sets `+0x32=1`, computes `+0x34`, and
assigns source slots `+0x18` for item IDs `0x2c..0x32`. It resets `+0x24` for
players 0–3, sets flags to `0x410` while preserving unrelated bits, and clears
`+0x3a..+0x49` with sentinel `+0x3e=-1`. It clears byte `+0x22` only for
owner 4 on class 0. Thus the constructor itself does not lose the player link
or a player's visibility mask. The later active-state transition can call
`FUN_0045e6d3`, which invokes `FUN_00462285` and recomputes visibility; the
final mask may therefore differ from its pre-placement value. Evidence:
`FUN_004528ca` `ev_a2bd552345a413d2155b98f6187184743ceeb32673ec2c4ebbb9ad875608d2f5`,
`FUN_00452fcb` `ev_7878b698c2ea5b2c87d52eb74899740d2d7101fa3967df458c97364cd85384e3`,
`FUN_004527ee` `ev_197f1ce65ee9546d036cd9bf75c5d7d80316473f55be2b625ca5f33d7fca2ba7`,
`FUN_00453a5f` `ev_56bf6ecfc372646d2d3fcb0362849d666eecd98bf6f5480bb3a0c2f77daedff4`,
`FUN_0045e6d3` `ev_0c10f06b048d94a70ea80142f675a05667a0928aeeeecc98e63ace03f8c270ba`,
and `FUN_00462285` `ev_2bc12365640ce9ddd66153682500e969e470f032e5fe6ce35467ce853b14e16b`.

The remake keeps the owner-specific PAD lookup ID (`base + 16 * owner`) in its
runtime `record_value_10` for catalog and rendering access. Native gameplay
predicates use the base ID at `+0x10` and owner at `+0x14`; the port now
normalizes IDs for source-tier cycling, CHARGE, cast-button eligibility,
category-4 site selection, and island Leviathan eligibility. The last check
previously treated player 0's `0x2c..0x2e` sources differently from the same
buildings owned by players 1–3. This fixes owner-variant IDs being rejected or
misclassified by base-ID rules. The latter check corresponds to the raw-ID
comparisons in `FUN_00460460` (`ev_194649b25df937615aa9cd8470539820d14a39966f5c66e6a2fbdf766465741a`).
Evidence: constructor forwarding
`ev_a571ddb810f57eb82ddb7110d751957927677498282088ff2bc3d5256611b345`,
per-player Hall creation
`ev_55301289f72a4d35e1d0ef2859453ebcf85ca880fd8ceb9c84776069998170d2`,
source-record allocation
`ev_058601a76da294207645bc296e6ea0e0cabf80b9850402c8da50ec5476a85f10`, and
PAD lookup
`ev_dd62728c87ff6b7e3489db5cf25557b77c8d7290e3eae8806cf999267576755a`.

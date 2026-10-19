# Hall move context

## Hall event routing and cost

When the floater is idle, `FUN_004211bb` consumes that action in switch case 8
(`action - 1`) and advances progress at `+0x46` through these observed stages:

| Progress before the branch | Runtime state and target writes | Result/next branch |
|---:|---|---|
| `0` | Set state `9`, copy packed target `+0x42` into `+0x32`, clear flag `0x004`, set progress `1`. | The per-floater tick can move toward the decoded packed coordinate while in state 9. |
| `1` | Call `FUN_00420829` on the packed target. It scans the current-island candidate list in order, applies `FUN_00420991`, and returns the first eligible candidate whose Chebyshev distance from the decoded target is below 250. | On hit, set state `0x0f`, store that candidate index in `+0x32`, set flag `0x004`, progress `2`. |
| `1`, no nearby candidate | Call `FUN_00420d97(4, packed_target)`. Mode 4 decodes the target and selects current-island class-4 sites owned by player 4, with item ID below `0x16`, flags `0x90` clear, and distance below 90. The selector retains at most ten nearest sites and chooses among them with inverse-distance weights via `FUN_0041e28e`. | On hit, set state `0x10`, store the selected location index in `+0x32`, progress `3`. If no site qualifies, reset progress to `0` so the search can be retried. |
| `2` | Set state `6`, retain the original target index, set progress to `1`. | The subsequent state-6 handler runs; movement is gated off for states 6/7. |
| `3` | Set state `7`, retain the selected location index, set progress to `1`. | The subsequent state-7 handler runs; movement is gated off for states 6/7. |

Thus the coordinate travel phase and the candidate/site follow-up are separate.
State `9` uses the packed target; the later states `0x0f`/`0x10` and `6`/`7`
are source-observed transitions, but their final gameplay effect is not fully
established by this path. `FUN_00420829` returns the first qualifying candidate
in scan order, whereas fallback mode 4 performs score-based selection. This
Hall action does not establish that the ordinary island click `0x4c` assigns
the same action. Evidence:
`ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
`ev_92d9bb1718fe3eeebfe376dbac88ead112d0c4f1f89113bc3a4cc866df7dbf24`,
`ev_2b7c3a4d07a47624e5bda9eda2a57d60b965635fa529ab925962c1b77d88b010`,
`ev_0a150ef6299ccee55e14aeab45e2de16381b5142b4063cda099503d87e818883`,
`ev_76a4661cb67067b44054706649c3ff1f80a7e9eec7116d8c36177f340ab15b36`,
`ev_f359bbf9ea4d68be9d7184310b58199071b1e8115a49a149ab72415feb7659db`,
`ev_667d311b6cd4f6b516c22975cd0e46ce337aa32ce5fe70c0d2ddd040239feb55`,
and action-label evidence `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.
`FUN_0042219e` is not this consumer; its subtype-9 branch concerns a type-4
floater.

`FUN_0042fa0f` maps the `IWMove`/`IWHallMove` names to `IWTextInfo` message
`0x3039` with parameters `(5,1)`. Separately, the `IWLocInfo` callback
`FUN_00441d3e` handles event 6: after its guards, it sends message `0x48`
when the move-context field is zero, otherwise `0x4a`. `FUN_0042970c` routes
that message according to context field `+0x48`. Independently,
`FUN_00465793` routes event category 3 subtypes 5/6 through thunks to
`FUN_0045f4f5`/`FUN_0045f5c5`. The evidence does not connect the `0x48`
dispatch to a type-3/subtype-5 event, nor establish that event 6 originates
from the `IWMove` window. The selection/commit UI route remains unknown.
Evidence:
`ev_66dacbd51cf6785b063a74bf329239127645ce19926b671235f30adca57b2aea`,
`ev_0e2ae16cc91e4a0449490e69d05f4c816b864c449ede69614ee500146eee0178`,
`ev_721b02ae62d9e81fff934679f3d0f672a102544ced812b19041e4d27311fc4f1`,
`ev_bcb9a925483956dd92de831e72742c3a6510dbd9a56729b017c9c5223fe5c3a5`,
`ev_90fc7b398e8cc430ee898f0371c196e285bf0f21c5cd78aa04fcdd060294d4ce`,
`ev_560d29325f0c28f11d75fd2ff0fe5274983745b3f9f1033098d16fb61c40a5e0`,
`ev_77f09bcf65be7f4df49ff369b2957df1474ade7c97d5617e72fa5148d5de9daf`,
`ev_1f480a49add06ef2e880e52e23d9c4de797b5916cf878e1c456d1852e5004238`,
`ev_72dddc006c4e1e255f9d20a50da596f1d4c1e470e033ced969a4b8d9fb1f9e80`,
`ev_2cea27d9cb11506662c6b3865f086398830c1271ba3439dd01827cb3b8737048`.

The four Hall rows in local `original_content/pad.txt` give base cost
`(15,0,15)`; `game_session_location_move_costs` applies the observed
`+0x4a + 1` multiplier to a runtime location's raw `+0x4a` field. Target
selection and the UI trigger are not ported yet. Cost evidence:
`ev_166ec7236cb49a5bd45dcbc859b69f029d1132243f92ee2e155015d72a50dedd`,
`ev_f92b05e1bac76d2be3a91b76e6eb420474e1d04db600d49cc8d4a55edf30587d`.

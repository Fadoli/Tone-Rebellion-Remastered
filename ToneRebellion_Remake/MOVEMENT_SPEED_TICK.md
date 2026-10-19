# Cursor and tick cadence

## Unit tick and speed source

| FLOAT.EXE procedure | REA evidence | Observation |
|---|---|---|
| `FUN_00422d27` (`0x422d27`) | `ev_0a3a5baa3dd85e9e4d8e576461b4c0ac5dde6dd1cb0ba6135191f046f1f98a93`; `ev_9ca29c0257a8de26b95a7f677b5ae2615957275141bb3639860ad55fe9a79d36` | Computes a destination and effective step, clamps each axis independently, reduces the step near the target using Chebyshev distance, and advances current coordinates. State 9 uses its packed anchor for the `<100` speed override; exact arrival requires both coordinates to match. |
| `FUN_0041e569` (`0x41e569`) | `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a` | Runtime states `0x0f` and `0x10` compare Chebyshev distance against a 10-pixel default stopping radius; `FUN_00420721` can supply a unit-specific radius. State `0x0e` instead uses the coordinate step's exact-arrival result to decrement its timer. |
| `FUN_00423068` (`0x423068`) | `ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f`; `ev_7102e609b67bea60b3c71e6b5989807367a825dc8dd5c9bce6b76a17fe83298f` | Resolves per-state destinations. State 9 expands the packed anchor, clamps its X center using global/category bounds, adds two bounded random offsets, clamps Y, and rejects final X outside the raw limits. This routine is not evidence of terrain pathfinding. |
| `FUN_0042704b` (`0x42704b`) | `ev_d21d92e7afdc377fecc4fce5fecca40c344273a5e036a4c507b40f99ab2e04b1` | Reads flag bit `0x002`; for the left-facing case negates the horizontal body/leg draw scale, producing a horizontal sprite mirror. |
| `FUN_00464242` (`0x464242`) | `ev_1559f3b44eb1bd728c2c2077c916a6ba549ae4c8310f49d5fc23ec8de61ff7cc` | Resolves a tribe/unit-class record in the runtime floater-stat table. |
| `FUN_004633a7` (`0x4633a7`) | `ev_fe7a5335c367485201a317db133bb5029b49d97a3d6cbffc7fd3926406f911ec` | Parses 45 rows with seven fields into 14-byte records; the seventh field is stored at record offset `+0x0c`. |
| `FUN_0046466f` (`0x46466f`) | `ev_fff46798e5d5d511dba4e67c4659afc2916bd8e719ba56ae3da3806f38ff09fe` | Creates four starting instances per player with unit class 0. |

The local original `floater.txt` defines the final field as speed. Each tribe's
`*work` row has speed 3. This agrees with the runtime access at `+0x0c` in
`FUN_00422d27` through `FUN_00464242`; this is only the worker movement
parameter, not evidence that the player can issue worker move orders.

The remake's session tick passes each floater's state, subtype, category
modifier and already-resolved near-target/site conditions through
`floater_motion_effective_speed` before calling the coordinate kernel. Initial
workers are constructed in state 0, then the first session tick enters the
implemented idle `FA_Wander` fallback (state `0x0e`). Category modifiers and
conditional site/target overrides remain zero until their runtime sources are
modeled. Other source order/state handlers and their target resolver are still
outside this tick path; this does not establish a player-issued move path.


## Related order callers

See [order selection and transition evidence](MOVEMENT_SPEED_ORDERS.md).

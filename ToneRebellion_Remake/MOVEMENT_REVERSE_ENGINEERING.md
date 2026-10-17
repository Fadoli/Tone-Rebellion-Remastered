# Floater movement primitives: REA evidence and port

This note records observed selection/input/movement procedures and separates them
from behavior still needing class/state checks. Ghidra pseudocode is a decompiler
reconstruction, not recovered source; field names and inferred types remain
provisional. The user has clarified that workers cannot receive direct orders:
selecting them only shows stats, while soldiers and mages are orderable. The
remake source and current executable do not expose player-facing worker orders.
Worker selection remains informational, and soldiers/mages should only become
orderable after their original class/state gates are verified.

## Input and destination path

| FLOAT.EXE procedure | REA evidence | Observation |
|---|---|---|
| `FUN_0042eba0` (`0x42eba0`) | `ev_65e41f9afa35457a4a0cb35010dd615e0a62eb7384057e13a9aea3fb6ea6465b` | Maps Win32 left/right button-down messages `0x201`/`0x204` to input queue types 2/4. |
| `FUN_00469f56` (`0x469f56`) | `ev_584be7e8cdd9be7c4fd1a0432ef83685f37123ab5a4622037dde65bf4a47704e` | Input code 2 dispatches island event 6 with pointer coordinates; input code 4 dispatches island event 7. The preceding input-queue function maps Win32 left/right button-down to these codes. |
| `FUN_00435826` (`0x435826`) | `ev_3f593fb36183818f4bc023cacb24c8be650508ce87f0ae8d590a2a24ae89a51b` | Hit-tests a floater and island locations. A floater hit emits message `0x3f`; its empty-ground coordinate branch calls `FUN_0041e3eb` and emits message `0x4c`. A location hit follows separate site/location message branches. |
| `FUN_0041e3eb` (`0x41e3eb`) | `ev_99ac9bec204079134afb4ec773ba173dab2b1a1a87ae06d72f28cad8c8cbfff9` | Packs each map coordinate as `(coordinate + 5) / 10`, with X in the high byte and Y in the low byte. |
| `FUN_0041e427` (`0x41e427`) | `ev_0c9a83fe313044ec813605a6f5e71760fcbcf78e0fff164432184e30593c562d` | Expands those bytes to pixel coordinates by multiplying each by 10. |

## Unit tick and speed source

| FLOAT.EXE procedure | REA evidence | Observation |
|---|---|---|
| `FUN_00422d27` (`0x422d27`) | `ev_0a3a5baa3dd85e9e4d8e576461b4c0ac5dde6dd1cb0ba6135191f046f1f98a93` | Computes a destination and effective step, clamps each axis independently, reduces the step near the target using Chebyshev distance, and advances current coordinates. The target is reported reached only when both coordinates match. |
| `FUN_0041e569` (`0x41e569`) | `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a` | In states `0x0e` and `0x0f`, computes the Chebyshev distance to the target and uses a 10-pixel default stopping radius. `FUN_00420721` can supply a unit-specific radius under other state/stat conditions. |
| `FUN_00423068` (`0x423068`) | `ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f` | Updates the object's draw anchor/offset based on target and state, sets flag bit `0x002` when the target is to the left and clears it when to the right, then checks horizontal bounds. This routine is not evidence of terrain pathfinding. |
| `FUN_0042704b` (`0x42704b`) | `ev_d21d92e7afdc377fecc4fce5fecca40c344273a5e036a4c507b40f99ab2e04b1` | Reads flag bit `0x002`; for the left-facing case negates the horizontal body/leg draw scale, producing a horizontal sprite mirror. |
| `FUN_00464242` (`0x464242`) | `ev_1559f3b44eb1bd728c2c2077c916a6ba549ae4c8310f49d5fc23ec8de61ff7cc` | Resolves a tribe/unit-class record in the runtime floater-stat table. |
| `FUN_004633a7` (`0x4633a7`) | `ev_fe7a5335c367485201a317db133bb5029b49d97a3d6cbffc7fd3926406f911ec` | Parses 45 rows with seven fields into 14-byte records; the seventh field is stored at record offset `+0x0c`. |
| `FUN_0046466f` (`0x46466f`) | `ev_fff46798e5d5d511dba4e67c4659afc2916bd8e719ba56ae3da3806f38ff09fe` | Creates four starting instances per player with unit class 0. |

The local original `floater.txt` defines the final field as speed. Each tribe's
`*work` row has speed 3. This agrees with the runtime access at `+0x0c` in
`FUN_00422d27` through `FUN_00464242`; this is only the worker movement
parameter, not evidence that the player can issue worker move orders.

## Current port and limits

The former `game_session_order_floater_move_from_click` player-facing helper
and worker cargo/order model have been removed. The generic movement kernel
remains as a simulation primitive; do not connect it to player input until the
original recipient and class/state gates are traced. Autonomous worker
navigation and soldier/mage orders remain TODOs, not implemented behavior.

The REA pseudocode does not yet establish obstacle/terrain collision, full
unit-state transitions, or the complete recipient behavior and class/state gate
for message `0x4c`. Trace those before implementing player controls. Also trace
the original worker task loop: construction clicks should create orders that
workers execute autonomously, and taskless workers navigate peacefully.

The current remake also records left/right facing from the destination direction and
uses horizontally mirrored body and leg sheets while facing left. This follows
the flag producer in `FUN_00423068` and the renderer in `FUN_0042704b`; flipped
32-bit DIB sheets are cached when the island's art is loaded. This only ports
the facing/mirror behavior: the original anchor adjustment and state-specific
render offsets in `FUN_00423068` are not fully reproduced by the current island
view, which draws a smaller subset of unit states.

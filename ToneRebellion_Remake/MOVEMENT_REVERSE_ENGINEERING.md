# Initial floater movement: REA evidence and port

This note records the binary observations behind the remake's first user-issued
floater movement order. Ghidra pseudocode is a decompiler reconstruction, not
recovered source; field names and inferred types remain provisional.

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
| `FUN_00464242` (`0x464242`) | `ev_1559f3b44eb1bd728c2c2077c916a6ba549ae4c8310f49d5fc23ec8de61ff7cc` | Resolves a tribe/unit-class record in the runtime floater-stat table. |
| `FUN_004633a7` (`0x4633a7`) | `ev_fe7a5335c367485201a317db133bb5029b49d97a3d6cbffc7fd3926406f911ec` | Parses 45 rows with seven fields into 14-byte records; the seventh field is stored at record offset `+0x0c`. |
| `FUN_0046466f` (`0x46466f`) | `ev_fff46798e5d5d511dba4e67c4659afc2916bd8e719ba56ae3da3806f38ff09fe` | Creates four starting instances per player with unit class 0. |

The local original `floater.txt` defines the final field as speed. Each tribe's
`*work` row has speed 3. This agrees with the runtime access at `+0x0c` in
`FUN_00422d27` through `FUN_00464242`; it is the source for the initial worker
speed used by the remake.

## Current port and limits

`game_session_order_floater_move_from_click` mirrors the packed 10-pixel
coordinates and uses the source-derived speed of initial workers. In the
remake, left-click selects a floater and right-button-down on empty island
terrain sets its destination. The island timer advances the same coordinate
step kernel and the renderer uses the updated position.

The REA pseudocode does not yet establish obstacle/terrain collision, full
unit-state transitions, or the complete recipient behavior for message `0x4c`.
The remake therefore currently permits direct movement across the island view
and does not claim collision or movement-state parity. Initial workers are
covered; other unit classes need their live unit-class records and action paths.

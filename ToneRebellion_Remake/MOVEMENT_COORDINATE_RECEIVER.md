# Coordinate destination orders

## 0x4c receiver and remake path

### `0x4c` coordinate order and its receiver

REA reinspection connects the empty-ground click to the receiver fields. Under
UI bit `0x4`, `FUN_00435826` packs the clicked world coordinate with
`FUN_0041e3eb` and emits message `0x4c`. `FUN_0042fa0f` turns that into a
16-byte type-1 packet: mode at word 2, selected island-location index at word
4, current island at word 5, and the packed coordinate at word 6. The packet
is copied into the command queue without rewriting those payload words.

In `FUN_00465793`, mode `0x13` requires a valid selected location and a
non-null linked record from `FUN_00450385`; it calls `FUN_0045d8b2` with the
current island and packed coordinate. That setter writes island to linked
record `+0x28`, state 9 to `+0x2c`, the packed coordinate to `+0x30`, and zero
to `+0x32`. Mode `0x11` uses the same coordinate setter but writes state 7.
Modes `0x10`/`0x12` take a separate setter path: `FUN_0045d867` reads word 6
as an index into the global `0x4c`-stride unit table and writes states 6/8.
They must not be treated as packed-coordinate destinations.

The remake now exposes state-9 coordinate orders through
`game_session_order_floater_to_coordinate`: it applies the source's nearest-10
packing and replaces the idle wander route. The UI adapter uses right-click on
the island while an eligible non-worker is selected. The non-worker check
follows the user's class constraint and the remake's subtype field; the binary
receiver itself has no subtype test, and the UI allowlist table's meaning is
still unknown.

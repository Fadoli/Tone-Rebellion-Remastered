# Floater movement port

## Idle routes and facing

The current remake also records left/right facing from the destination direction and
uses horizontally mirrored body and leg sheets while facing left. This follows
the flag producer in `FUN_00423068` and the renderer in `FUN_0042704b`; flipped
32-bit DIB sheets are cached when the island's art is loaded. This only ports
the facing/mirror behavior: the original anchor adjustment and state-specific
render offsets in `FUN_00423068` are not fully reproduced by the current island
view, which draws a smaller subset of unit states.


The Hall move context analysis is in [its focused note](MOVEMENT_HALL_CONTEXT.md),
which links to shorter input, state-9 and event pages.
Attack timing and the current damage port are summarized in
[the floater combat note](MOVEMENT_COMBAT.md).

# Movement order edge cases

## Facing and rendered anchor

### Facing and rendered anchor

`FUN_00423068` adjusts the draw anchor and offsets for the current state, uses
flag `0x002` to select facing, and checks horizontal bounds before accepting
the adjusted anchor. `FUN_0042704b` reads that flag and mirrors the body/leg
draw scale when it is set. The state-specific anchor adjustments use different
targets (site, packed coordinate, island offsets, or local offsets); they are
not evidence of pathfinding. The remake ports the facing mirror but not the
full state-dependent anchor adjustment. Evidence:
`ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f`,
`ev_d21d92e7afdc377fecc4fce5fecca40c344273a5e036a4c507b40f99ab2e04b1`.

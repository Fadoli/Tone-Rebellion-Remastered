# Movement step kernel

## Coordinate sources

### Target source and facing adjustment

`FUN_00423068` resolves the next pixel pair from the runtime state and target
index. The main coordinate sources observed in its switch-like conditions are:

| Runtime state / family | Coordinate source before anchor adjustment |
|---|---|
| `6` or `0x0f` | Current coordinates of the floater indexed by `+0x32`; these are live entity coordinates, so an approach can track a moving target. |
| `0x10` | Coordinates from the current island's location record indexed by `+0x32`. |
| `0x0e` | Current floater coordinates plus two bounded offsets in `[-100,99]`; Y is then clamped to `0x28..0x122`. |
| `9` | The packed target at `+0x32` is expanded by `FUN_0041e427`, then the same two bounded offsets are applied. |
| `0x15` | The floater's current coordinates; this branch does not introduce a new travel point. |

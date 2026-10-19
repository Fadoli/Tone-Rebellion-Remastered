# Floater movement primitives: REA evidence and port

This note records observed selection/input/movement procedures and separates them
from behavior still needing class/state checks. Ghidra pseudocode is a decompiler
reconstruction, not recovered source; field names and inferred types remain
provisional. The user has clarified that workers cannot receive direct orders:
selecting them only shows stats, while soldiers and mages are orderable. The
remake now routes mode `0x13` to state 9 for selected floaters with nonzero
subtype. That subtype mapping is an implementation gate following the user's
constraint; the original allowlist and `FA_Cast` interaction remain unresolved.

## Evidence table

- [Input, selection and candidate filtering](MOVEMENT_INPUT_UI.md)
- [Order receiver and destination encoding](MOVEMENT_INPUT_RECEIVER.md)

# Hall move context

## Hall input and move context

## Order 9 from the Hall move context

`FUN_0044003d` hit-tests six `IWLocInfo` slots: left-click selects an occupied
slot (`0x3f`), or emits `0x32` only when the selected record's `+0x18` is not
`-1`. Right-click emits `0x4d(owner)` for a non-local owner, then always
`0x3d(1,1)`. The `0x3d` arm in `FUN_0042fa0f` passes `DAT_005c37e4[1]`, message
`0x35` and the click parameters `(1,1)` to `FUN_0046c371`. That wrapper rejects
a negative active-state index (`+0x29f2`); otherwise it indexes the object
array at `+4 + recipient_index * 0x0c` and invokes that object's vtable slot
`+4`, passing a value formed from the active-state index and message `0x35`,
followed by `(1,1)`. The `ISLEVIEW` pointer is fetched by name from the window
object registry through `FUN_0046c4a5`; that helper can also return the
registry slot separately, while `FUN_0046c371` consumes its first argument as
such a slot. In this call, therefore, `DAT_005c37e4[1]` is used as a recipient
index, not passed as the recipient object pointer. Its runtime value, the
registered object's class, vtable and method body remain unresolved, so this
path cannot yet be identified as a floater movement command. The next static
probe is to trace initialization/writes to `DAT_005c37e4[1]`, then resolve that
slot's object and vtable method. This path is distinct
from map-ground message `0x4c`, whose callback and recipient guard are
unresolved independently. The remake's four-worker roster selection is the
supported subset; no move command is exposed. Evidence:
`ev_dfa9260d630c5590f535d54281a0b8f2c2767e3ca99d4a00ffdd596b3104b7eb`,
`ev_6ac7cc6650dc8a0e9b412c055606948d1c6dbbdd3e6c6df0a7fcc1551764419e`,
`ev_f8a09cad809f94f6483fa8f6623537024026f2d86fdd3f36b90ed39dbda0bd65`,
`ev_ed92b375145a0b030776f82d115ccc237230777746be74169b6aac305580d646`,
and named-window lookup `ev_8ca518262f6e9da0f51b7f516b986760a38b2cc4962b4ea5adf47c2f5b350e01`.

`FUN_0045f4f5` starts the move context after its eligibility checks; it does
not issue order 9. `FUN_0045f5c5` ends the context: for target item `0x2a`,
a different target plus successful `FUN_0046562b(owner, 8)` writes order 9
into a floater task slot. Dropping on the same object takes a position-adjustment
path. Evidence: `ev_6c942de9a792a73d84fdfda4bddbe5dc35196c59fa13110da77051c6b3595d63`,
`ev_d98532f21ef6f26838f03f508eb96bbceb47d6dbbc1a3a7678ffbfca8c9c8bf3`,
`ev_b8ac2fd034c03491f78284865a603e7dda1ce800bc85e544b13add76dde36154`.

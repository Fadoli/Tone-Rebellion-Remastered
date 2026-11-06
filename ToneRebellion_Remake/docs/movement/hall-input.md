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

## Floater click selects its source building

Observation (REA): the `0x3f` case in `FUN_0042fa0f` only stores the floater
pointer (`this+0x170`) and calls `FUN_0042f8f7`. That calls `FUN_004207f2`
(floater `+0x0c` short, `-1` = none, to the 100-byte per-owner source row
`0x6192b0 + idx*100 + owner*0x14a0`) then `FUN_0045c3bb` (row `+0` island,
`+2` location) and `FUN_0042f755`, which stores the location index only when
the island is the viewed one. Without a link the current location is kept.
`decompilation/behavior/island-ground-object-interaction.md` records `FUN_0045c470` as the
writer of floater `+0x0c` (production attach). Interpretation: the remake's
`source_link_0c` + `charge_source_island/location` are that link, used by
`select_floater_source_building`. Initial units keep `-1`, so they select
no building (the Hall default applies, as `FUN_0042f303(0)` does). UI: `FUN_0042f8f7`
hides `IWTextInfo` and shows `IWFltInfo` (windows.txt pane 456,328..631,395,
TEMPHOLE frame 2) while `FUN_0042f755` leaves `IWLocInfo` (192,368..447,471) and
`IWLocControl` on the building, so the remake draws the floater in the
`IWFltInfo` pane and the building in `IWLocInfo`. Full read of `FUN_0042fa0f`
(msgs 1..0x65 except lines 800-914), `FUN_0045302a`, `FUN_0045d5ba`,
`FUN_00450070`, `FUN_0044338b`: the selection path never tests the unit's
subtype (`+0x04`, only the WORKER/AWAKE label); the building command list
depends on the location kind/owner only. The unit *type* only picks order
message `0x10` vs `0x12` via `DAT_00619290[type]` (type 4 forces `0x10`).
Unknown: writer/initial values of `DAT_00619290`, `FUN_0042fa0f` msgs
`>= 0xbbb`, the mode-0/1/2 route from `FUN_0042970c` to `FUN_0042fa0f`
(order gating only, not selection). Evidence: `ev_4ee89808…f533`,
`ev_a86c918e…a43b`, `ev_ad688265…b875`, `ev_982ef225…ae`, `ev_015453b4…e754`,
`ev_05caf6fb…f491`, earlier:

Second pass (REA, `FUN_0042fa0f` msgs `>= 0xbbb` now read): `0x401b8b` is `JMP
0x42fa0f`, registered only as handler 3 of the object at `0x62a780` via
`FUN_0041c46f`/`FUN_0046cbe0` (`this+id*0x130+0x206c`); `view+0x48` is a
per-window type set by the `FUN_0046cd22` parser (not a global mode), and the
active state index in island play stays unresolved. Msg `0x44` re-shows
`+0x16c` (`FUN_0042f755`) when `p2 == 0`; msg `5` clears `+0x170` for a
released unit. `FUN_0044338b` hides the panel for a dying unit (flag `0x8` at
`+0x1c`, timer `+0x24 >= 40`) and keeps the building: the remake now ignores
inactive selected floaters in the info panel. `DAT_00619290` has only read
sites (`FUN_00420991`, `FUN_00435826`), so its writer is unresolved: order
gating only. Evidence: `ev_40f42b3c…`, `ev_e17ea091…`, `ev_9c3f52d5…`.

Third pass (REA, `FUN_0042fa0f` fully read): orders (msgs `0x40`, `0x41/0x4c`,
`0x4a`) clear only the state words `+0x17e`/`+0x178`/`+0x174`; neither the
selected building (`+0x16c`) nor the selected unit (`+0x170`) is cleared, as in
the remake's right-click orders. `FUN_00467101` (release) does not touch
`+0x16c/+0x170` directly. `DAT_00619290[type]` (`0x6191b8+0xd8`) is written
only by `FUN_00465793` class 3 subcode 10 (toggle 0/1 of dword
`owner*0x14a0 + 0xd8 + idx*4`, `which != 0` selects `+0xe8`; pumped by
`FUN_00466221`); read by `FUN_00420991`/`FUN_00435826` (nonzero picks `0x12`/`0x13`
over `0x10`/`0x11`). Interpretation, joined with the remake's diplomacy port
(`game_session_toggle_diplomacy`, `native_save.c`: `DAT_00619290` = Diplomacy
"policy" flags, set = friend, all zero at start; `DAT_006192a0` = message
recipients; the sender is the diplomacy panel via `FUN_0043e399` hit zones;
the `game_diplomacy.h` field-7 comment is the reverse and should not be
trusted): `idx` is the other player id (4 = Leviathan), flag 0 = enemy. The
remake already uses it in `game_session_action9.c` (`FUN_00420991`). `FUN_00420991` accepts a target only
when the flag is 0, and `FUN_00435826` picks `0x10` (state 2, mode 3, attack
floater) for flag 0 or type 4, else `0x12` (mode 5, defend floater), via
`FUN_0043530b`. These order modes need a selected, staffed own building
(`+0x16c`, `+0x18 != -1`), i.e. the building-order buttons, not a direct
soldier order. Island-view state: `SetState(3)` is enqueued only at
`FUN_00470fe7` (from the WorldWin handler `FUN_004702d9`, gated on
`DAT_006191b4`/`FUN_0047117d`), not an island-specific entry; `FUN_0044a0bb`
passes a non-literal state. `FUN_0042dd47` only sets the cursor; none of
`FUN_00425084/0045c51b/00421ec1/004206b2/00418921` touches `+0x16c..+0x17e`. `ev_2979cbdd…b1e8`, `ev_4ba95749…7405`,
`ev_9dfe8ccb…18c`, `ev_21af0363…b6f`. Unknown: owner check, other-island view.

`FUN_0045f4f5` starts the move context after its eligibility checks; it does
not issue order 9. `FUN_0045f5c5` ends the context: for target item `0x2a`,
a different target plus successful `FUN_0046562b(owner, 8)` writes order 9
into a floater task slot. Dropping on the same object takes a position-adjustment
path. Evidence: `ev_6c942de9a792a73d84fdfda4bddbe5dc35196c59fa13110da77051c6b3595d63`,
`ev_d98532f21ef6f26838f03f508eb96bbceb47d6dbbc1a3a7678ffbfca8c9c8bf3`,
`ev_b8ac2fd034c03491f78284865a603e7dda1ce800bc85e544b13add76dde36154`.

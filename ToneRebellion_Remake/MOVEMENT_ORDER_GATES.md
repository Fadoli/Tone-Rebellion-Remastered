# Movement order edge cases

## Unconsumed order actions and gates

## Orders without a local consumer branch

The retained `FUN_004211bb` switch has no explicit arms for `action - 1` values
2, 9, `0x0e`, `0x0f`, or `0x14`. These correspond to `FA_Fetch` (3),
`FA_Wait` (10), `FA_ChaseFlt` (15), `FA_ChaseLoc` (16), and `FA_Ascend` (21).
`FA_Fetch`'s missing local transition is noted with `FA_Deliver` above. For the
other four, the action labels alone do not establish whether another routine
consumes them, whether they are legacy values, or what movement they request;
do not infer their routes from similarly named actions. Assignment itself can
be data-driven: `FUN_00421ec1(task_index)` copies the slot's action field
`DAT_006183cc[task_index]` into the floater, and `FUN_0042219e` can attach a
validated slot without switching on that action value. Therefore an action
may be assigned even though `FUN_004211bb` has no matching local executor arm.
The current evidence does not identify another consumer for those missing
values or show that any of them produces a movement state. Evidence: task-link
copy `ev_c2d3e74dd2e94c30ca9de18f1387bb8d44d32daf432cd179e9d1b8dfc693b4dc`,
reevaluation/attachment `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`,
and order consumer `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`.

Address cross-references to the task action table base `DAT_006183cc` resolve
to four functions: `FUN_00421ec1` copies the selected slot action into the
floater order field; `FUN_00422031` validates a slot for attachment; and
`FUN_0042fa0f`/`FUN_004455d1` search or enumerate slots for the Tasks UI. The
validator has explicit handling for actions 4, 5, 11 and 18; the list builder
excludes action `0x0b`. These inspected bodies show reads/filtering at these
sites, not an alternate movement executor or a writer that maps the missing
actions to states. This makes the attachment boundary explicit: assignment is
possible, execution of the four absent local cases remains unproven.

The tick keeps action and runtime state separate. When the floater is idle,
`FUN_0041e569` passes its copied action field to `FUN_004211bb`; that consumer's
`action - 1` switch lacks the cases for Wait/Chase/Ascend. The later state
dispatch is keyed by runtime state `+0x2c`, where movement handlers for states
`0x0e` and `0x0f` do exist. No inspected branch connects the missing action IDs
10/15/16/21 to those states. The equal-looking numeric values therefore cannot
be used to infer a route. Evidence: table cross-references
`ev_da7542c8d20a92a354e31176edb14fccd1ee1f3fac24ff7f7cfd1464503b3b49`,
slot validation `ev_bd805382bd750a65076a58742501849e1bdeb29a87bc0717a5bac1e0307b1077`,
Tasks-list filtering `ev_25d048fc082b5ed144709e4886b7748e44943fd30f5e02a0e06addfc60beaec9`,
message/task lookup `ev_ed75141a79f1bac30a4ad39dcad68e710e351330bcd3044aa3cb304ef2a796b2`,
tick/state dispatch `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`,
and action consumer `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`.

## Building group orders and the spell-caster hall

Observation: `FUN_0045d5ba` lists the order buttons 0x10..0x13 and recall 0xf
only for items 0x2c..0x2e; items 0x2f/0x30 get spell buttons 0x15..0x1c
(`ev_03503d5f`). The right-click path has no item test: `FUN_00435826` needs an
owned `+0x16c` site with `+0x18 != -1` (`ev_9fac3ab3`), `FUN_0042fa0f` msg 0x65
sub 0x10..0x13 calls `FUN_0043530b`, and `FUN_00465793` only needs
`FUN_00450385` (staff row present). Port: `game_session_building_takes_orders`
(owner + staff record) gates right-click orders and the command, so spell
casters of a 0x2f hall take move/attack orders; the buttons keep the
0x2c..0x2e rule.

## More evidence

See [task table state](MOVEMENT_ORDER_TABLE_STATE.md).

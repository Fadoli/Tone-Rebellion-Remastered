# Autonomous floater orders

## Order selection and task links

## Autonomous order selection and execution

`FUN_0042219e` chooses/revises orders; `FUN_004211bb` consumes an order
already stored on the unit. They are separate from the coordinate step.
Evidence for the two procedures:
`ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea` and
`ev_0e9d3fbfa8df7eb8f372d0b17bc92593ddd6fc2eb7cebe7c043ca611798b4abd`.
The reevaluator returns for runtime states 6/7 and while global guard
`DAT_006191b4` is nonzero. In the regular-unit path, when flag `0x10` is clear
and the action is `FA_Nothing` or `FA_Wander`, it can scan at most 64 records
at `DAT_006183bc`. It filters active records by owner/type, excludes the
already attached record, and calls `FUN_0041e454` and `FUN_00422031` before
comparing record class/level values. It attaches a qualifying record through
`FUN_00421ec1`; if none qualifies, a unit with no attached record can receive
`FA_Wander` (`14`) with its home island as the target. Candidate field
semantics and all eligibility thresholds are not fully named. Evidence:
`ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`.

`FUN_00421ec1` is the task-link transition. Passing `-1` decrements the old
record's claimant count, clears its reference, action and runtime state; a
valid index increments the new record's count, copies its action and target
fields into the floater, clears progress/state, and releases an old attached
record when the link changes. This is the observed bridge between the task
table and an order executor, not a coordinate assignment by itself. Evidence:
`ev_c2d3e74dd2e94c30ca9de18f1387bb8d44d32daf432cd179e9d1b8dfc693b4dc`.

The `FUN_0042219e` candidate path can also copy the selected floater-slot row's
action and target fields onto the current floater when they differ and the
current action is not `FA_Cast` (`0x13`). This permits propagation of actions
`FA_DefendFlt` (`8`) and `FA_MergeWith` (`0x14`), but does not establish where
those source-row actions originate. `DAT_006192b0` is the per-player floater
slot table (100-byte row stride, `0x14a0`-byte owner block); its initial
zero-filled view has no file backing, and the bounded xref scan found no direct
initializer. Indirect runtime writers through stored row pointers remain
unresolved. Evidence: row addressing `ev_2fdd1471c0f1e4e94fb325e5ea31ed049251a46dc4e4043563d8198c30f75343`,
action propagation `ev_27e2b21a8d1a587093fbddfca18e4174abd0ae50b8b815dfecd888332208e06c`,
initial bytes `ev_1f710a017953658c0f8446971ee541ad29071c83cb4af3e1011c24566158afd9`,
xrefs `ev_48a648f49f66d098aeac13af25721f64d6cc6f8a6bfa9dfb8e60f95d56a3e46c`,
and pointer registration `ev_c983e5176a1c900c3cc49a086fbf2b4d22bc8ccb7549dcd1cc17b2b7fee345e9`.

The port assigns the modeled delivery, construction, charge and repair rows
through the shared task scan. An otherwise idle regular floater whose current
island or stored target differs from its Hall's island now takes `FA_Wander`
(`0x0e`) toward home, then resumes local wandering after the bridge handoff.
The full native candidate table and action propagation remain unresolved.

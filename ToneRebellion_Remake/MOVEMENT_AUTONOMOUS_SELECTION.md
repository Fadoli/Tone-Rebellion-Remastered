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

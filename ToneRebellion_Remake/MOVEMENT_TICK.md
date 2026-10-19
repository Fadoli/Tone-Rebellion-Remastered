## Tick, state machine, target and arrival detail

The following separates the per-world update, per-floater order controller,
order executor and coordinate step. Offsets are raw accesses seen in the
decompiler; they are not recovered source declarations. Evidence for the
function bodies is in `functions/0010_batch_0006.md` and
`functions/0017_batch_0013.md`.

### Update sequence

`FUN_00466ce2` iterates active floater records from the fixed 256-slot table
and invokes `FUN_0041e569` for each live record. The latter calculates the
record index using a `0x4c` stride. Evidence:
`ev_b51f2311ff9bd9ad209f0663ea00bfe330e7ff0eff117e8a273292d3112a4e0e` and
`ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`.
Within that update:

1. `FUN_0042219e` reevaluates the order when runtime state `+0x2c` is zero, or
   when `(DAT_00618e44 + floater_index) % 10 == 0` for another state.
2. If state `+0x2c` is zero and action/order `+0x3c` is nonzero,
   `FUN_004211bb` consumes that action and may set the next runtime state,
   target fields and progress fields.
3. The common movement call to `FUN_00422d27` is enabled only when state is
   not `0`, `6`, `7`, `0x0f` or `0x10`, and no flag from mask `0x411` is set.
4. The state-specific switch then handles arrival and action completion. State
   `0x0e` uses the common movement result and decrements its timer only when
   the step routine reports exact arrival. States `0x0f` and `0x10` use the
   radius-based state-specific arrival handler. Both are excluded from the
   common movement call, so each can make at most one state-specific movement
   step in that update.

The return from `FUN_00422d27` means both current coordinates equal its
resolved destination exactly. Runtime states `0x0f` and `0x10` can finish at
a wider radius: they compare Chebyshev distance against 10 by default, use
zero when action/order is `0x14`, and let a nonzero result from `FUN_00420721`
replace the default. The special `0x14` action is `FA_MergeWith`. Reaching
that radius finishes those states even when the coordinate kernel did not
return exact equality. When state `0x0f` finishes with no unit-specific radius
and action/order other than `0x14`, the update also sets bit `0x10` on the
referenced island record and bit `0x40` on the floater flags. State `0x0e`
uses exact coordinate arrival to count down its state timer instead. The
semantic names for these bits remain unresolved. Evidence:
`ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`.

`FUN_00420721` explains when the optional radius replaces 10. It returns zero
unless `FUN_004207c2` returns zero; that guard allows category 4, or a
nonzero subtype when the floater's short at `+0x22` is positive. Otherwise it
reads the first short from `FUN_00464242(category, subtype)`. The local
`floater.txt` header identifies that column as attack range, so states
`0x0f`/`0x10` can stop at the unit's data-defined attack range instead of the
default radius 10. If `FUN_004207f2` resolves a linked site (`+0x0c != -1`)
and bit `0x4` is set in the table dword addressed from
`DAT_00619242 + category * 0x14a0`, a positive attack range is changed to
integer `floor(range * 5 / 4)`. The semantic meaning of that table bit remains
unestablished. Evidence:
`ev_234f0678b3bbd27430c793e465dfd5095240536d821d1821e23bb5b1acb00e41`,
`ev_601b55f72156209d4f5c1ae6f9060918a71e3fc3423c72c12074227bdb69a5c6`,
`ev_400be7fc416e3e48c58ebeae7f1497639f909f0569891b58d5b3cba579bbab2a`.

The four initial workers use categories 0–3, subtype 0 and charge `+0x22 = 0`,
so this guard returns no stat radius for them; their state-`0x0f`/`0x10`
arrival radius remains 10 unless their action is `0x14`. Evidence:
`ev_ac313cb8cc73f9c102676395cd14cb97b5b1f9355d074df1e6656ce028d2d36f`,
`ev_0ca802ac15043c61c073f6d68546619fc924a4ba10fd4d9f04e203668dc62ed7`.


Destination resolution, per-axis stepping, target-source rules and facing are documented in [the movement step kernel](MOVEMENT_STEP_KERNEL.md).

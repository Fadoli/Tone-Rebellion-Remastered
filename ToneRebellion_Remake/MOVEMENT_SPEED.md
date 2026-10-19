# Cursor and tick cadence

## Interaction cursor lifecycle

The cursor is a 17-slot state machine, not a one-off glyph image. `FUN_0041c181`
loads slots 0..16 from the resource IDs in `DAT_0049c950`; `FUN_0042dd47`
chooses the requested slot when its handle exists, otherwise falls back to slot
0, then calls `SetCursor`. `FUN_0043530b` assigns slot 9 for mode 1, slots
3/5/15 for modes `0x10`/`0x12`/`0x13`, and slot 13 or 11 for mode `0x11`
depending on whether an item or glyph is armed. Evidence:
`ev_c726a273b363fd7769f6b98bb6a0fb90f454b1cc5c2da0d264a1175c0aaaca75`,
`ev_f390428e4e2b22a6ce9a9f425844123e7a120340e823e19cc9c45619ebb90e9a`,
`ev_b65156eb13978511b7f06cdb3fee86e7c2c4a37bf3cac67ad0f0badb2f999a68`.

`FUN_0042fa0f` messages `0x42` and `0x43` arm an inventory item or glyph and
enter mode `0x11`; message `0x40` commits a target, restores slot 0 and clears
both armed IDs. Evidence: `ev_a8230350584e54954217dfeda123b6cf8d9dc6ca7211fff2385661c22cdab6ba`
and the `FUN_0042fa0f` dossier in `functions/0012_batch_0008.md`.

Live REA inspection of the shipped `C:\Program Files\Tone\FLOAT.EXE` confirmed
the table bytes at `0x49c950` (Evidence
`ev_870a794f1785a5ab6a4e135cf0a026a2068b803ccd42730199dce261f9631b74`):
slots 0..16 map to resource IDs `84, 75, 76, 77, 78, 79, 7a, 7b, 7c, 7d,
7e, 7f, 74, 80, 81, 82, 83` (hex). The remake now loads the complete table,
uses slot 11 while an inventory item or glyph is armed, and returns to source
slot 0 immediately after the target click or a screen change. `WM_SETCURSOR`
also reapplies the state so Windows cannot leave a stale custom cursor visible.
The other source modes (slots 3, 5, 9, 13, 15 and data-driven 0x15..0x1c) are
not yet raised by remake actions, so they remain available but inactive.

## Unit tick and speed source

| FLOAT.EXE procedure | REA evidence | Observation |
|---|---|---|
| `FUN_00422d27` (`0x422d27`) | `ev_0a3a5baa3dd85e9e4d8e576461b4c0ac5dde6dd1cb0ba6135191f046f1f98a93`; `ev_9ca29c0257a8de26b95a7f677b5ae2615957275141bb3639860ad55fe9a79d36` | Computes a destination and effective step, clamps each axis independently, reduces the step near the target using Chebyshev distance, and advances current coordinates. State 9 uses its packed anchor for the `<100` speed override; exact arrival requires both coordinates to match. |
| `FUN_0041e569` (`0x41e569`) | `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a` | Runtime states `0x0f` and `0x10` compare Chebyshev distance against a 10-pixel default stopping radius; `FUN_00420721` can supply a unit-specific radius. State `0x0e` instead uses the coordinate step's exact-arrival result to decrement its timer. |
| `FUN_00423068` (`0x423068`) | `ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f`; `ev_7102e609b67bea60b3c71e6b5989807367a825dc8dd5c9bce6b76a17fe83298f` | Resolves per-state destinations. State 9 expands the packed anchor, clamps its X center using global/category bounds, adds two bounded random offsets, clamps Y, and rejects final X outside the raw limits. This routine is not evidence of terrain pathfinding. |
| `FUN_0042704b` (`0x42704b`) | `ev_d21d92e7afdc377fecc4fce5fecca40c344273a5e036a4c507b40f99ab2e04b1` | Reads flag bit `0x002`; for the left-facing case negates the horizontal body/leg draw scale, producing a horizontal sprite mirror. |
| `FUN_00464242` (`0x464242`) | `ev_1559f3b44eb1bd728c2c2077c916a6ba549ae4c8310f49d5fc23ec8de61ff7cc` | Resolves a tribe/unit-class record in the runtime floater-stat table. |
| `FUN_004633a7` (`0x4633a7`) | `ev_fe7a5335c367485201a317db133bb5029b49d97a3d6cbffc7fd3926406f911ec` | Parses 45 rows with seven fields into 14-byte records; the seventh field is stored at record offset `+0x0c`. |
| `FUN_0046466f` (`0x46466f`) | `ev_fff46798e5d5d511dba4e67c4659afc2916bd8e719ba56ae3da3806f38ff09fe` | Creates four starting instances per player with unit class 0. |
| `FUN_004211bb` (`0x4211bb`) | `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957` | Consumes the floater order. Case `0x13` (`FA_MergeWith`, order ID `0x14`) first sets state `0x0f` and copies target `+0x42`; after arrival it selects state `0x0e` for subtype 8, otherwise `0x15`. This is autonomous task execution, not a proven player click handler. |
| `FUN_0042219e` (`0x42219e`) | `ev_d9f9f466dec9c616930d5fb954437b6cb9c603d687390540a4d8c90cdc2c0eea`; earlier dossiers `ev_04a74bd124249ab097279236e8788fcf661bc6047d7c113aea28ae262bafc6e5`, `ev_787dc785055d52728b1408fa372d280fa57be569a05f32883f94a4022cbce846` | Fresh full-function dossier covers body `0x42219e–0x422d26` (2,953 bytes). It returns early for object state 6/7 and while `DAT_006191b4` is nonzero. One class-4 branch distinguishes subtype 9; another, when flag `0x10` is clear and order field is 0 or `0x0e`, scans up to 64 records at `DAT_006183bc`, checks active/type/subtype values, calls `FUN_0041e454` and `FUN_00422031`, compares task values against object level and measured distance, and writes task state/target fields. Other branches select states 6/7/`0x0e` for owned-site or other object conditions. The body confirms conditional task scheduling and destination updates, not random roaming; the semantic meaning and source population of every task record and state still need tracing before porting these assignments. |
| `FUN_00420d97` / `FUN_00420a55` | `ev_0a150ef6299ccee55e14aeab45e2de16381b5142b4063cda099503d87e818883`; `ev_76a4661cb67067b44054706649c3ff1f80a7e9eec7116d8c36177f340ab15b36` | `FUN_00420d97` delegates to `FUN_00420a55` for the current island. Its mode 4 candidate filter requires object owner/class field 4, distance below `0x5a`, type below `0x16`, and flags masked by `0x90` clear; it retains up to 10 candidates, then delegates final selection to `FUN_0041e28e`. This identifies one source selector used by movement/task code, not a general order rule for all units. |
| `FUN_004210a9` (`0x4210a9`) | `ev_dd046f002c50d0d9e841af455f3dd8fc8b70d1b11f430f2fa5c0185edc5f5121` | Chooses a current-island handoff location and enters runtime state `0x11` with the departure slot and target island; the mover later makes a timed discrete position/island change. |
| `FUN_00420721` (`0x420721`) | `ev_234f0678b3bbd27430c793e465dfd5095240536d821d1821e23bb5b1acb00e41` | Supplies the optional arrival radius used by states `0x0f`/`0x10`. Its lookup is gated by category/subtype and the floater's `+0x22` value; a linked-site and table-bit condition can scale a positive stat value by integer `5/4`. |
| `FUN_0045da80` (`0x45da80`) | `ev_0f9c0e1151dca8d181ee42ea559e71d3987676f2680c797f76c97d5b25bbba36` | Checks action-specific conditions and an eligible unit, then stores order `0x13` (`FA_Cast`) plus three raw parameters and zeroed progress; deducts two player resource fields after finding the unit. The cast state resolves a destination but does not integrate current coordinates. |
| `FUN_004527ee` (`0x4527ee`) | `ev_1b65d37c5f980508939852c08a13046d03c79fce26bff8abdd695e5f8134eea6` | Calls `FUN_004528ca` to initialize the placed item only after `FUN_00452794` accepts the site/item; on success it sets a runtime flag and emits event 2. The exact full transition from `FA_Build` to this validator still needs to be connected. |

The local original `floater.txt` defines the final field as speed. Each tribe's
`*work` row has speed 3. This agrees with the runtime access at `+0x0c` in
`FUN_00422d27` through `FUN_00464242`; this is only the worker movement
parameter, not evidence that the player can issue worker move orders.

The remake's session tick passes each floater's state, subtype, category
modifier and already-resolved near-target/site conditions through
`floater_motion_effective_speed` before calling the coordinate kernel. Initial
workers are constructed in state 0, then the first session tick enters the
implemented idle `FA_Wander` fallback (state `0x0e`). Category modifiers and
conditional site/target overrides remain zero until their runtime sources are
modeled. Other source order/state handlers and their target resolver are still
outside this tick path; this does not establish a player-issued move path.


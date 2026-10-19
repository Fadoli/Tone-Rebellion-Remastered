# Floater movement primitives: REA evidence and port

## Order receiver and destination encoding

| FLOAT.EXE procedure | REA evidence | Observation |
|---|---|---|
| `FUN_00465793` (`0x465793`) | `ev_b625919fbba21cb67016167d2d318c548f89e6fc5ec6620530ee862c32f1153f` | For type-1 mode `0x13`, requires a selected location index other than `-1` and a non-null record from `FUN_00450385`; then calls `FUN_0045d8b2` with the current island and packed destination. This receiver has no explicit subtype/class test. |
| `FUN_0045d8b2` (`0x45d8b2`) | `ev_48e296b74e9cc988efac53eea393dc2d694c98d8b5139997953e8da5429d7721` | Stores current island at linked record `+0x28`, state 9 for mode `0x13` at `+0x2c`, packed coordinate at `+0x30`, and zero at `+0x32`. |
| `FUN_0042219e` (`0x42219e`) | `ev_83d2c58354af7da0f0eac81274ce4acc13b27060e77eb7d82b4ed0f74897a266` | Resolves the linked 100-byte record through `FUN_004207f2`; when its movement fields differ from the tick record and the current task is not `FA_Cast` (`0x13`), copies linked `+0x2c/+0x28/+0x30/+0x32` into tick `+0x3c/+0x40/+0x42/+0x44` and clears progress `+0x46`. |
| `FUN_004211bb` (`0x4211bb`) | `ev_9cf6e091e5052554584128e5f6d9e26420d03c257fa83061e471eda1b608d689` | Task action 9's first phase selects movement state 9, copies the packed coordinate target into tick `+0x32`, clears flag `0x004`, and advances progress to 1. After arrival, later phases try unit/location follow-up targets. |
| `FUN_0042970c` (`0x42970c`) | `ev_bcb9a925483956dd92de831e72742c3a6510dbd9a56729b017c9c5223fe5c3a5` | Routes a message according to context field `+0x48`: direct dispatch through `FUN_0046c402`, secondary dispatch through `FUN_0046c1b4`, or a local queue through `FUN_0046c3bc`. |
| `FUN_0046c402` (`0x46c402`) | `ev_5d7372e111e8a989a1bad601deacda8478942b76678d4c0f95271ab98899581f` | Calls the active-context handler indirectly from callback slots in records with stride `0x130`. Static call references do not resolve the effective handler or its recipient-class guard. |
| `DAT_00619290` (table read by `FUN_00435826`) | `ev_e6487dc3406aa2d64a6c44227d93003cc5658ee6fb0b6adabc68947b37f039b5`, `ev_e1cf3e5b13ea9e894e109f983d575d93db9494440640c431beeb4115c47f87d1`, `ev_6a58e77526590a24419b4c84ad1ffdeac127494982b6d9aa3a42c30eb9bacc33` | Instruction evidence confirms comparisons against `DAT_00619290 + type*4 + player*0x14a0` while choosing modes `0x10`–`0x13`. These are reads/comparisons; they do not establish table initialization or the semantic class allowlist. |
| `FUN_0041e3eb` (`0x41e3eb`) | `ev_99ac9bec204079134afb4ec773ba173dab2b1a1a87ae06d72f28cad8c8cbfff9` | Packs each map coordinate as `(coordinate + 5) / 10`, with X in the high byte and Y in the low byte. |
| `FUN_0041e427` (`0x41e427`) | `ev_0c9a83fe313044ec813605a6f5e71760fcbcf78e0fff164432184e30593c562d`; `ev_5bc6478909567c79eb3b9145b0a1d0e2dbe24db42a6a863032f43beb4b2d1461` | Expands those bytes to pixel coordinates by multiplying each by 10. |

# Movement Travel Orders

### Training and recharge orders: travel to a location record

For these orders, `FUN_004211bb` first compares the task's target-island field
`+0x40` with the floater's current island `+0x0e`. If they differ, it passes
the target to `FUN_004210a9` and clears the task link if that call returns 0.
The following local-state transitions occur when the target island is already
current (or unspecified):

| Order | Order consumer writes | Movement and arrival behavior |
|---|---|---|
| `2` (`FA_Recharge`) | The regular-floater branch in `FUN_0042219e` can select this order after comparing the floater's two current values with thresholds from its attached task record. It writes the record's island/site into `+0x40/+0x42` and the selected dimension into `+0x44`. `FUN_004211bb` sets runtime state `2`, copies `+0x42` to `+0x32`, copies `+0x44` to `+0x30`, and sets progress to `-1`. | The movement helper consumes the already stored destination pair `+0x28/+0x2a`; it does not resolve `+0x32` to a location in this state. On arrival, the handler checks the target Hall/source, performs the source-specific wait/retry, and may consume the requested resource. For Hall/source records, `FUN_00452c31` checks requested stock or inventory and `FUN_00452eac` debits it. Other linked producers use `FUN_00452e4d`'s `+0x36` retry tick and `FUN_00452ceb` availability check before the same debit. The route still lacks an evidenced destination writer. |
| `17` (`FA_UseBridge`) | Switch case `0x10` is grouped with case `1` and performs the same state-2 writes as `FA_Recharge`. | Uses the same state-2 movement and arrival handler. The action label does not by itself establish which bridge object or animation is involved; its destination writer is also unknown. |
| `11` (`FA_Enlist`) | Switch case `0x0a` shares the direct transition with case `0x0b`: set runtime state to the action ID, copy `+0x42` to `+0x32`, `+0x44` to `+0x30`, reset timer `+0x34`, and set progress to `-1`. | State `11` resolves the target as a location record. On exact arrival, the handler checks `FUN_00450385` and `FUN_0045c772`; if both allow it, it calls `FUN_0045c470` and starts its counter. |
| `12` (`FA_Train`) | Switch case `0x0b` performs the same direct target/parameter/state writes as case `0x0a`. | State `12` resolves `+0x32` through the island-location table. On exact arrival, the handler calls `FUN_0045c797` if `FUN_00450385` and `FUN_0045c772` allow it, then advances its counter. |

`FUN_00422d27` consumes `+0x28/+0x2a` directly for state 2 without reading
`+0x32`. The remake now ports the state-2 arrival consumer: Hall/source waiting,
producer retry via `+0x36`, carried-artifact drop, and requested-resource debit.
The AI can produce `FA_Recharge`, but the port still cannot start its route
until the writer of that coordinate pair is established. The raw `+0x20/+0x22`
updates and extra parameter semantics remain unresolved. “Recharge” and “train”
remain action-table labels. Evidence:
AI selection `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`,
order/cross-island consumption
`ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`,
state handling `ev_65d84bdd9fce74857981724f25ee33467f26c00a24acba921c8139e1a122ccda`,
Hall/source availability and debit `ev_5a0471841e28e1e0c4403918c700d2132239a49d2aa7fc4f4f06dd84f78fb7a0`,
`ev_bf2ec011afe579c598c1f57feca9b80c83515881336566e4cee78b69ee690ca7`,
producer retry `ev_40379ff22d87a9658901c7307389da5f012fecd75baea490d2f78fab5095de26`,
and source availability `ev_636f5bb2277cb3418b09d0152d37b9c7b176bb6da1310e3794613756a3979c67`,
movement destination pair `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`,
artifact drop `ev_c90fab99fa7691b34572e2c9eba925751fbdf77b63a570c51574e19c416b7e0b`,
and action labels `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f`.

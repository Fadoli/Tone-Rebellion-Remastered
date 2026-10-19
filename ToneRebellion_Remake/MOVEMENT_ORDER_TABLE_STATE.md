# Movement order edge cases

## Runtime table state and remaining probe

A read of the loaded image at `DAT_006183bc` returned 0x500 initialized zero
bytes, the full 64-record span at stride `0x14`; the `.data` segment is marked
initialized. The adjacent scan bound `DAT_006188bc` is also zero in the loaded
image; its sole direct reference is a read in `FUN_0042fa0f`, where it bounds
the active-task search. Typed incoming references to the action field `+0x10`
contain a read and address-only references, with no typed write at that exact
address.
The live base xrefs cover 19 sites in seven procedures: `FUN_00421ec1`,
`FUN_00422031`, `FUN_0042219e`, `FUN_0042fa0f`, `FUN_00432c74`,
`FUN_00445145` and `FUN_004455d1`. Review of their retained bodies found one
table write:
`FUN_00421ec1` increments/decrements a slot's short at `+0x04` (the claimant
count); it reads the other slot fields and copies the action, island, target
and parameter to the floater. The validator and reevaluator filter slots, the
Tasks UI searches/enumerates them, and `FUN_00432c74` formats nonempty entries
in a diagnostic task list. Their retained bodies show reads/address formation,
not population writes. This rules out a prefilled task catalog in the
inspected image bytes, but it does not identify runtime population: a computed
destination, bulk copy, or unobserved indirect writer may not appear as an
exact typed reference. Evidence:
image bytes `ev_bc254ddb3b5d4bfc3b423aa3c2a839a6aa1f4f771807016000e59944447f751e`,
segment initialization `ev_254928ccff2cf0ec576eeddf8c2bba7d672a4d24c5d348d39bb0e17288171961`,
field references `ev_50a5fda0ff82969f755c9db1bc3df1f158c35f1c08640ce4cc393b308f55d113`,
table-base xrefs `ev_17822ce9cd33c62cee9df591f32253f607cdd2842d06f0999b06c5d99173784a`,
scan-bound bytes `ev_1a41179b501410302facf114f1b939f69b226dbf2b96f46746236674007b5b1e`,
scan-bound xref `ev_2386230a22ea08ca9dee702742e0ada6673f3308dff7cb2224d379efb8d5efdc`,
task-link update `ev_c2d3e74dd2e94c30ca9de18f1387bb8d44d32daf432cd179e9d1b8dfc693b4dc`,
validator `ev_9d5d129cd6bb5e1095f8136fbde959c47360ad898c94d3104c63add6dcda3bc7`,
reevaluator `ev_d9f9f466dec9c616930d5fb954437b6cb9c603d687390540a4d8c90cdc2c0eea`,
Tasks UI `ev_25d048fc082b5ed144709e4886b7748e44943fd30f5e02a0e06addfc60beaec9`,
task-list formatter `ev_a0e3498f3ed8eb4104bd4b63541e89783f53f63203d538d435ff69c00c824209`,
and its typed references `ev_9771e1e273408598010b44e9c8a1a5d1e69b98d70114d34de4e8eda7fe6fa8cf`.

The remaining source probe is to inspect references and stores across the full
64-slot range `[0x6183bc, 0x6188bc)`, including computed/bulk writes, then trace
initialization of the observed count at `DAT_006188bc`. Exact field xrefs and
initialized image bytes alone do not resolve that producer.

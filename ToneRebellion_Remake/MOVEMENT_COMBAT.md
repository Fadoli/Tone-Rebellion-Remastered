# Floater combat

`game_session_combat.c` contains attack-state timing, hit and damage
calculation, and bounded IMPACT lifetime. `floater_effect_catalog.c` reads the
four realm frame ranges from `effects.txt`.

`floater_attack_power` now applies the category-4 level modifier to the
already accumulated base plus `3 * level`: `power += high_nibble * power / 22`.
Other categories add `2 * level`. `FUN_0041fde6` reads attack strength from the
record at `+0x0a` only when `FUN_004207c2` permits it. A linked source adds 3
when its runtime `+0x1c` flag `0x8000` is set; the port now applies that bonus
using the validated CHARGE source link. The separate `DAT_00619242` building
bonus remains zero in the loaded image. Evidence: `ev_6840e9603bc69a881626d117d21f164c420fe3d7683a6a3499a6803031c91b48`,
`ev_8709314ab4e61c06f9a65200e76f6f026e25e31061938ae192a13265aff6d4b9`,
`ev_42b992f36684f6ab483de7e785ad784edf29aff2675858dcc62fb8c794f6d1fb`,
`ev_bfd788316e3cf96fdb381d544548f14e253126f1a73497c331e2b6205d127b3a`,
`ev_c98a873c8773837cea12a521e802a6556ff976490acd69ff8f2b312c6614ebde`,
`ev_688e3c557e73c5f5a27b0204c6cc3bacef1295f767b3d6df8d94ae7d46b5ec76`,
`ev_c79e46f68f2729047653a05bfccc5dc9ce9869b8d1147b497ed2968453e377ad` and
`ev_73016003aef798231cd1dea33fd1a54a9df2068d3bc944b6b9aa123970934d03`.

On a successful state-6/7 hit, the session reserves one of 32 modeled effect
slots. The hit's damage selects an IMPACT level as `damage / 2`, capped at 3.
The effect advances on odd `source_tick` values and finishes after the loaded
frame span plus one completion update. Effects advance before floater states,
so an attack can leave state 6/7 on the same island tick that its slot is freed.
The parity mapping from `source_tick` to `DAT_00618e44` is an implementation
assumption; no visual effect rendering is included.

## Evidence and limits

`ev_7c484994c613ee44ac210f2e95fa7410266eef0e29269805eab05b5e1821f0d2`
shows `effects.txt` type and realm names plus one-based `LEVELFRAMES` bounds.
`ev_dcd89dd94c9093c5c61f660b46d6d92f3190ef730556ca722959e3483a05d97a`
shows IMPACT instance update and release; `ev_efbe102809736dcd702537792a130764df8124b9abf49bcc646627bb5ad2ad78`
shows animation stepping and completion after passing the descriptor end.
`ev_7497f8cfda4628b468bd57b65b1452e9cf6a0f34bb89155a303ececb306b8e7f`
confirms the IMPACT completion flag. `ev_8b35fe2aa3036a409894d98a435a4b61d341be0005e4db65a406bdd1e047a1ce`
updates active effects before the floater loop in island update
`ev_30ebdbae3fea9c425e667386d450d79579fcde7a1d8aee5d218f1a6ffd472942`.

The session tracks attack effects only, so unrelated visuals do not consume its
modeled 32-slot capacity. Site/research modifiers, kill/death event dispatch,
combat statistics, native notification delivery and visual playback remain open.
These limits do not establish gameplay parity.

The `FA_DefendArea` site fallback now selects records with raw `+0x14 == 4`,
item ID below `0x16`, and flags `0x90` clear, matching `FUN_00420a55`. Site
damage now checks renderer class 0/1, matching `FUN_00450847`; it had been
mistakenly checking the record owner. REA evidence:
`ev_8cbbb89cf96f8cec18ab31fded50c934c328575c25039ff87bdd77fcf45866ed` and
`ev_b8ac599ba63894f58bcb0c088216c59d5562ada7e6c69f06ca6af85ad1fe1648`.
For non-item-5 destruction, the port now clears runtime `+0x48` and recomputes
the affected site's active bit. When that bit changes, it refreshes the
Leviathan island summary for raw `+0x14 == 4`, or player maintenance budgets
otherwise, following `FUN_00453a5f` and its callbacks. The source also appends
type 7 with a packed island/site index to a separate 32-entry engine queue; no
model-side consumer is established, so that notification remains outside the
gameplay state. Evidence: `ev_3b605ab12575d2aa283244d68c1b83314a3c4768bef5b1518df472cf0d5d96a`,
`ev_56bf6ecfc372646d2d3fcb0362849d666eecd98bf6f5480bb3a0c2f77daedff4`,
`ev_194649b25df937615aa9cd8470539820d14a39966f5c66e6a2fbdf766465741a`,
`ev_0c10f06b048d94a70ea80142f675a05667a0928aeeeecc98e63ace03f8c270ba` and
`ev_40e57a701dcdfcc8c86be5c2642b1ceba5aee4bcfc77fe9923616cbdf99e14a9`.

The runtime keeps owner-specific PAD lookup IDs, but `FUN_00450817` filters
base item IDs `0x17..0x24` before site damage. Attack and area-cast filters now
normalize the ID first, so player slots 1–3 receive the same building immunity
as slot 0. Regression coverage is in
`test_site_damage_filters_player_variant_building_ids`. REA confirms the
native predicate reads `+0x10` directly (`ev_a8441ac6c243be3c67999d9793a76b3cd00d9a3644a10d660bf6e4febfd324d7`);
Ghidra found no direct callers for this small helper, so its consumer identity
remains inferred from the existing call-path reconstruction.

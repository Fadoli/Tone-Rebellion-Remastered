# Floater combat

`game_session_combat.c` sequences attack-state timing. Damage rolls are in
`game_session_combat_damage.c`; the bounded IMPACT lifetime is isolated in
`game_session_combat_effects.c`. `floater_effect_catalog.c` reads the four
realm frame ranges from `effects.txt`.

`floater_attack_power` now applies the category-4 level modifier to the
already accumulated base plus `3 * level`: `power += high_nibble * power / 22`.
Other categories add `2 * level`. `FUN_0041fde6` reads attack strength from the
record at `+0x0a` only when `FUN_004207c2` permits it; linked-site bonuses are
still not represented. Evidence: `ev_6840e9603bc69a881626d117d21f164c420fe3d7683a6a3499a6803031c91b48`,
`ev_8709314ab4e61c06f9a65200e76f6f026e25e31061938ae192a13265aff6d4b9`,
`ev_42b992f36684f6ab483de7e785ad784edf29aff2675858dcc62fb8c794f6d1fb`,
`ev_bfd788316e3cf96fdb381d544548f14e253126f1a73497c331e2b6205d127b3a`,
`ev_c98a873c8773837cea12a521e802a6556ff976490acd69ff8f2b312c6614ebde`.

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
combat statistics, site-destruction callbacks and visual playback remain open.
These limits do not establish gameplay parity.

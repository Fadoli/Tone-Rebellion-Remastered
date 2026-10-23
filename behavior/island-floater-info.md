# Panneau d'info de floater (`IWFltInfo`, type 33)

Source: REA relu (sous-agent haiku). Evidence: `ev_611f078c…` (dispatcher `FUN_0046cd22`, classe `IWFloaterInfo`), `ev_5f37bb5d…` (`FUN_00443298`), `ev_34df2fae…` (`FUN_0044331d`, seul `0x350b` traité: `this+0x70` = objet sélectionné), `ev_995b04cc…` (paint `FUN_0044338b`, pseudocode dans `functions/0014_batch_0010/details-02-02.md`).

## Observations Ghidra
- Pane 456,328..631,395, `TEMPHOLE` cadre 2, sans focus souris ni entrée. Le paint ne dessine rien (et joue le son 0x32/0x44) si la sélection est vide ou la garde (`+0x1c & 8`, `+0x24`) échoue; aucune jauge, uniquement du texte « a/b ».
- Sprite d'unité à (125, 38) (`FUN_0042704b`). Floater (hors type 4): nom de tribu + `WORKER`/`AWAKE` centré y=3, `HITS` y=23, `STRENGTH` y=33. Spore (type 4): nom `xSpores` y=3, `LEVEL` y=23, `HITS` 33, `STRENGTH` 43. Branche site/bâtiment: nom `BLDNAME` y=3, `LEVEL` y=18, ligne (4,28), `CHARGE` y=38, `HITS` 48, `STRENGTH` 58. Débogage (`DAT_004c2bb0`): noms `FA_*` et `object=%d`.

## Port
Le remake dessine déjà ce panneau dans `render_island_view` (branches floater et spore, voir `island_view_render.inc`), sans l'étiquette `IWFltInfo`; la branche bâtiment est couverte par `IWLocInfo`. Une revue ligne à ligne des positions y ci-dessus contre ce code n'a pas été faite ici.

## Inconnues
Police/palette (`FUN_004289c0`), fond exact (`DAT_004c2b08`), cadence de rafraîchissement, slots de vtable 0/3/4/6/7, libellés `DAT_004a0cd8/0d38`.

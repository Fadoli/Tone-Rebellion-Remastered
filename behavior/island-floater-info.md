# Panneau d'info de floater (`IWFltInfo`, type 33)

Source: REA relu (sous-agent haiku). Evidence: `ev_611f078c…` (dispatcher `FUN_0046cd22`, classe `IWFloaterInfo`), `ev_5f37bb5d…` (`FUN_00443298`), `ev_34df2fae…` (`FUN_0044331d`, seul `0x350b` traité: `this+0x70` = objet sélectionné), `ev_995b04cc…` (paint `FUN_0044338b`, pseudocode dans `functions/0014_batch_0010/details-02-02.md`).

## Observations Ghidra
- Pane 456,328..631,395, `TEMPHOLE` cadre 2, sans focus souris ni entrée. Le paint ne dessine rien (et joue le son 0x32/0x44) si la sélection est vide ou la garde (`+0x1c & 8`, `+0x24`) échoue; aucune jauge, uniquement du texte « a/b ».
- Sprite d'unité à (125, 38) (`FUN_0042704b`). Floater (hors type 4): nom de tribu + `WORKER`/`AWAKE` centré y=3, `HITS` y=23, `STRENGTH` y=33. Spore (type 4): nom `xSpores` y=3, `LEVEL` y=23, `HITS` 33, `STRENGTH` 43. Branche site/bâtiment: nom `BLDNAME` y=3, `LEVEL` y=18, ligne (4,28), `CHARGE` y=38, `HITS` 48, `STRENGTH` 58. Débogage (`DAT_004c2bb0`): noms `FA_*` et `object=%d`.

## Port
Le remake dessine déjà ce panneau dans `render_island_view` (branches floater et spore, voir `island_view_render.inc`), sans l'étiquette `IWFltInfo`; la branche bâtiment est couverte par `IWLocInfo`. Une revue ligne à ligne des positions y ci-dessus contre ce code n'a pas été faite ici.

## Inconnues
Police/palette (`FUN_004289c0`), fond exact (`DAT_004c2b08`), cadence de rafraîchissement, slots de vtable 0/3/4/6/7, libellés `DAT_004a0cd8/0d38`.

## Sélection de floater : boutons, panneau, ordres (revue REA, sous-agent, non relue)

Observations (`FUN_0042fa0f` cas 0x3f `ev_ed75141a…`, `FUN_0042f8f7` `ev_aa63a0e6…`, `FUN_0044331d` `ev_76b7ca47…`, `FUN_0044338b` `ev_347b34f6…`, `FUN_00435826` `ev_52232fe9…`) :
- Un clic floater pose `+0x170`, ouvre `IWTextInfo`/`IWFltInfo` et ne change pas le mode des boutons `IWLocControl`/`BC_*` : la liste d'options suit le lieu sélectionné (`+0x16c`, `FUN_0042f755` → `FUN_0045302a`). `FUN_0042f8f7` ne remplace `+0x16c` que par la ligne source (`rec+0x18`) du floater. Aucun test de propriétaire sur ce chemin : un floater étranger ou Leviathan atteint `IWFltInfo` (le port concorde : `select_floater_source_building`).
- Branche masquée du panneau : `FUN_00425296(8)` = 40 (constante; 0x100→2000, 0x1000→3500, 0x2000→45, autre→20; `ev_436a1ff2…`). `FUN_0041e569` incrémente `rec+0x24` par tick quand le bit 0x8 est posé, puis au-delà de 40 efface 0x8 et libère le floater (`FUN_00467101`, `ev_ff014992…`) : le panneau n'est masqué qu'au dernier tick avant retrait, rien de durable à porter.
- Ordres vers un floater : voir [ordres](island-ground-object-interaction.md) (aucun test du propriétaire cible dans le pipeline lu).
Interprétation : `rec+0` du tableau de floaters (stride 0x4c) joue le rôle de propriétaire (4 = Leviathan).

## Disposition des lignes (revue REA, sous-agent, non relue)

Observations (`FUN_0044338b` `ev_347b34f6…`) : le test « lieu » est `FUN_004207f2` = lieu lié au floater (`rec+0xc != -1`), pas le lieu sélectionné. Floater lié : `BLDNAME` centré y=3, `LEVEL` (niveau+1) y=18, `EXP` y=28 (`rec+8`; plafond `DAT_004a424a[L+3·sous-type]` si niveau < 2, mélangé à `DAT_004a4282` par `DAT_004bf11c`, 0 dans l'image; « n/d » si d ≥ 1), `CHARGE` y=38, `HITS` y=48, `STRENGTH` y=58, x=4. Floater non lié : disposition déjà portée (y 3/23/33, spore 3/23/33/43). Sprite à (largeur−50, hauteur/2+5), échelle 1,0. Lignes `FA_*`/`object=%d` seulement si `DAT_004c2bb0` (0 statiquement). Pas de retour à la ligne ni de découpe.
Port : disposition liée portée (`island_view_render.inc`, lignes à x = 4 depuis le 2026-11-02), nom de bâtiment via `island_panel_info_construction_task_indices`, confirmé (REA 2026-11-02: `FUN_004207f2` → ligne source B → site `FUN_0045c3bb(B)`; clé `BLDNAME` + `(site+0x10 - 0x25) + site+0x14 * 16` passée à `FUN_00429e69(index, 1)`; `ev_80317dba…`, `ev_6da55aaa…`, `ev_baf9ee69…`), plafond EXP limité aux sous-types 0..5, mélangé par la difficulté (`DAT_004bf11c` = difficulté 0..4, non nulle hors image: `((4-D)·DAT_004a424a[i] + D·DAT_004a4282[i])/4`, même formule que le test de promotion de `FUN_0045cd75`; REA 2026-11-02). Inconnues : police/palette, textes localisés, formules `FUN_0041fde6`/`FUN_00420f28` complètes.

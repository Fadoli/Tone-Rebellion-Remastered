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
- Changement de mode (REA haiku 2026-11-03, `ev_379f1f88…`, `ev_aa63a0e6…`): `FUN_0042f303` masque toujours `IWFltInfo` (avec tous les panneaux) sans effacer `+0x170`; `IWTextInfo` revient en modes 0, 3..7. Seul `FUN_0042f8f7` rouvre `IWFltInfo`; les cas 0xb..0xe de `FUN_0042fa0f` effacent `+0x170` avant `FUN_0042f303(4/5/7/6)`. Port: `floater_info_pane_open` (compteur de sélection `g_floater_select_serial`).
- Ordres vers un floater : voir [ordres](island-ground-object-interaction.md) (aucun test du propriétaire cible dans le pipeline lu).
Interprétation : `rec+0` du tableau de floaters (stride 0x4c) joue le rôle de propriétaire (4 = Leviathan).

## Disposition des lignes (revue REA, sous-agent, non relue)

Observations (`FUN_0044338b` `ev_347b34f6…`) : le test « lieu » est `FUN_004207f2` = lieu lié au floater (`rec+0xc != -1`), pas le lieu sélectionné. Floater lié : `BLDNAME` centré y=3, `LEVEL` (niveau+1) y=18, `EXP` y=28 (`rec+8`; plafond `DAT_004a424a[L+3·sous-type]` si niveau < 2, mélangé à `DAT_004a4282` par `DAT_004bf11c`, 0 dans l'image; « n/d » si d ≥ 1), `CHARGE` y=38, `HITS` y=48, `STRENGTH` y=58, x=4. Floater non lié : disposition déjà portée (y 3/23/33, spore 3/23/33/43). Sprite à (largeur−50, hauteur/2+5), échelle 1,0. Lignes `FA_*`/`object=%d` seulement si `DAT_004c2bb0` (0 statiquement). Pas de retour à la ligne ni de découpe.
Port : disposition liée portée (`island_view_render.inc`, lignes à x = 4 depuis le 2026-11-02), nom de bâtiment via `island_panel_info_construction_task_indices`, confirmé (REA 2026-11-02: `FUN_004207f2` → ligne source B → site `FUN_0045c3bb(B)`; clé `BLDNAME` + `(site+0x10 - 0x25) + site+0x14 * 16` passée à `FUN_00429e69(index, 1)`; `ev_80317dba…`, `ev_6da55aaa…`, `ev_baf9ee69…`), plafond EXP limité aux sous-types 0..5, mélangé par la difficulté (`DAT_004bf11c` = difficulté 0..4, non nulle hors image: `((4-D)·DAT_004a424a[i] + D·DAT_004a4282[i])/4`, même formule que le test de promotion de `FUN_0045cd75`; REA 2026-11-02). Inconnues : police/palette, textes localisés, formules `FUN_0041fde6`/`FUN_00420f28` complètes.

### Badges FLTINFO du monde (REA haiku 2026-11-02, `ev_fe27bac4…`, `ev_7b370fcc…`, `ev_1559f3b4…`)

Observation: `FUN_0042704b` (`param_5 = 1`, `(+0x1c & 0x808) == 0`, forme de corps présente) dessine trois badges sur la même ordonnée `minY` de la boîte du corps (`FUN_00405e11`), x_r = `maxX` si tourné (+0x1c & 2), sinon `minX - 8`:
- royaume (`DAT_005c37f4`): frame 0x16 + `FUN_0042003c(sous-type)`, colonne royaume (+2) de la ligne `FUN_00464242(type, sous-type)` (`type*9 + sous-type`, ou `sous-type + 0x1b` pour le type 4), décalée de +1/-1 par les drapeaux 0x10000/0x20000 du site source lié. Aucune garde de type: les Léviathans l'ont.
- santé (`DAT_005c37f8`): frame 0x15 - min(10, 10*PV/max), x = x_r + 2 pour les sous-types 0 et 8, sinon + (tourné ? 0 : 5); Léviathans compris.
- charge (`DAT_005c37fc`): type != 4 et sous-type >= 1, x = x_r + (tourné ? 5 : 0).
Port: le badge de royaume prenait la tribu (`type_index`) et refusait le type 4; il lit maintenant `game_session_floater_realm` (même calcul que le combat). Le badge de santé reçoit le sous-type (les sous-types 10..17 des Léviathans ne sont plus refusés). Même correction dans le panneau du floater sélectionné, qui décalait le royaume par le lieu sélectionné au lieu du site source. Le panneau dessine aussi maintenant le badge de charge (barre bleue), comme le monde; il manquait.

### Mort d'un floater (REA haiku 2026-11-03, `ev_5cc7f5cc…`, `ev_8beff744…`, `ev_7f3d6aca…`, `ev_2016a3eb…`)

Observation: `FUN_004204bc` pose le drapeau 0x8 (+0x1c), remet le compteur +0x24 à 0 et appelle `FUN_00416a9a(1, rec)` (`levdeath` ou `fltdeath`); `FUN_0041e569` incrémente le compteur et retire le floater après 40 ticks. `FUN_0042704b` ne dessine corps et jambes que si le compteur est < 20, puis, pour chacun, `FUN_0041137c`: des cellules de la forme `die` (`data\die.shp`) tous les 24 px depuis 12 px à l'intérieur de la boîte opaque de la frame (miroir: seul x de base inversé), k = 0 puis +5 par cellule, frame `(compteur - 8 + (k & 7)) / 2` (troncature C) dessinée si 0..10, blit RLE simple. Pas de fondu ni de remappage; badges FLTINFO masqués par `(+0x1c & 0x808) != 0`; le floater mourant reste cliquable (`FUN_00435581` ne teste que le bit 0x1).
Port: `draw_floater_death_cells` (`island_view_render.inc`) pour les floaters de tribu et les Léviathans; badges masqués. Fixture `dying` (`TONE_REBELLION_E2E_FIXTURE=dying`) pour observer la séquence.

### Barre rose des Léviathans et échelle des jauges (REA haiku 2026-11-03, `ev_c1b3c0b4…`, `ev_c98a873c…`, `ev_b35f6adb…`)

Observation: `FUN_0042704b` dessine, sous la même garde que la jauge de charge (`DAT_005c37fc`) mais pour le type 4 de sous-type 10..17, une jauge rose: frame FLTINFO `0x2a - min(10, n)` avec n = quartet haut de `+0x0a` (rang d'attaque, `FUN_0041ff56`), si n > 0, à la place de la jauge bleue (x = x_r + (tourné ? 5 : 0)). Les trois jauges utilisent `DAT_00494158` = 11.0: santé `0x15 - min(10, __ftol(11·PV/max))` (PV négatifs ramenés à 0), charge `10 - min(10, __ftol(11·charge/max))`, rose `0x2a - min(10, n)`.
Port: `island_leviathan_rank_badge_layout`; facteur 11 pour santé et charge (avant: 10); la jauge de charge n'a plus de garde de propriétaire (le natif n'en a pas, et toutes les tribus commencent alliées).

### Alliances au départ (REA haiku 2026-11-03, `ev_ca19bd63…`)

`FUN_0046466f` met à 1 chaque entrée de `DAT_00619290` (+0xd8, politique: 1 = ami) et de `DAT_006192a0` (+0xe8, destinataires) pour chaque joueur et chaque tribu 0..3, soi compris: toutes les tribus commencent alliées. `FUN_00465793` sous-code 10 les bascule. Port: `game_session.c` initialise `diplomacy_policy_mask` et `message_recipient_mask` à 0x0f (avant: seule l'entrée de soi).

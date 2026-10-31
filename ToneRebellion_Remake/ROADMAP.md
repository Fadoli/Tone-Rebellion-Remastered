# Feuille de route

État au 2026-10-27. Détail des items dans le [backlog](TODO_BACKLOG_INDEX.md); portage acquis dans [implemented.md](docs/implemented.md).

## Constat

- Décompilation : `index.jsonl` couvre 2410 procédures (1493 internes, 780 thunks, 123 externes, 14 runtime); 1507 décompilées, 903 exclues avec motif. L'inventaire est clos; le travail REA restant est ciblé (questions ouvertes ci-dessous), pas un balayage.
- Remake : ~36 k lignes C11, 27 tests unitaires + `tests/e2e/island_e2e.ps1`. Backlog : 31 items cochés, 26 ouverts (Interface 13, Tâches 7, Mouvement 4, Autres 4).
- Le rendu et l'interface de l'île sont avancés; la boucle de jeu ne l'est pas : ordres de bâtiment, déplacement manuel, IA adverse et condition de fin restent partiels. Une partie solo complète n'est pas encore jouable.

## Phase 0 — Hygiène (immédiat)

1. Valider le diff en cours (sélection floater/bâtiment `IWFltInfo`/`IWLocInfo`, `MOVEMENT_HALL_INPUT.md`).
2. Corriger le commentaire du champ 7 de `game_diplomacy.h` (sens inversé selon `MOVEMENT_HALL_INPUT.md`).
3. Ménage local hors dépôt : copies `ToneRebellion_Remake - Copie*.exe`, zips, `hs_err_pid*.log`, `mci_debug.log`.

## Phase 1 — Boucle de jeu jouable

Ordre choisi : chaque étape débloque la suivante.

1. **Déplacement manuel** (`TODO_MOVEMENT` l.9) : chemin `FUN_0043530b(0x13)` → `FUN_00435826` (pas de 10, msg `0x4c`) → `FUN_0042fa0f`. Prérequis de tous les ordres.
2. **Ordres de bâtiment** (`TODO_INTERFACE` l.22, l.27) : enregistrement d'ordre dans le bâtiment + adoption par les floaters liés; finir `BC_*` restants (champs `B+0x28..`), `Recall`. Le filtrage ami/ennemi par `DAT_00619290` est établi.
3. **Tâches restantes** : `Obtain` (tâche `0xd`, état 13), `SUPPLY`/`UPGSPREAD` (table genre 0/1 de `FUN_0045fcbe`), Hall type 4, gardes type 5 ↔ `FA_Build`, transition native vers `REPAIR`, cas de `FUN_00450385`.
4. **Producteur de `PIT_Object`** : contexte des appels à `FUN_004503bd` (TODO_OTHER l.4, TODO_TASKS l.8).

## Phase 2 — Adversaires

1. Tick IA `FUN_00460989` et `FUN_00460460` (portés partiellement, `TODO_TASKS` l.7) : décompiler/lire en entier, porter la prise de décision.
2. Leviathan : contamination et défense ont des tests; relier à l'IA et aux ordres d'attaque de la phase 1.
3. Effet monde du clic glyphe : sens de `DAT_004befe0`, ordre `0x13` (TODO_OTHER l.5).

## Phase 3 — Fin de partie

- Déclencheur natif de l'état 7 (branche de l'écran de fin, `TODO_INTERFACE` l.24) : condition de victoire/défaite.
- Sauvegarde/chargement : presse-papiers, mode Sauvegarde de l'écran de chargement, aller-retour `native_save` après les nouveaux champs d'ordre.

## Phase 4 — Parité d'interface

Items à faible risque, parallélisables : polices (`bigfont` des étiquettes), ordre de dessin du cadre de construction et couleurs, commerce/diplomatie (ordre ombrage/emblèmes, couleur de légende), modes d'inventaire et messages `0x3039`/`0x42`, `IWFltInfo` (x 4, `BLDNAME`, `DAT_004bf11c`), reste de la carte du monde, options `float.cfg`.

## Phase 5 — Audio

Volume/pan par distance, bullets et impacts des producteurs (`FUN_00450a71`, table d'attaque à lire), sons d'île.

## Transverse — Vérification

Plusieurs items sont « portés, non vérifiés en jeu » (ordre des panneaux Hall, sélection floater, panneau inférieur droit, `IWMove`). Étendre `island_e2e.ps1` pour couvrir chacun, puis cocher.

## Questions REA ouvertes

À trancher par sous-agent avant le port concerné :

- Boucle de distribution souris des panneaux Hall; index d'état actif en vue île; route mode 0/1/2 `FUN_0042970c` → `FUN_0042fa0f`.
- Expéditeur du paquet de clic Repair, `FUN_00429f3a`, `FUN_00452b67`, attache automatique (`FUN_0041e569`).
- Paquet natif de `IWMove`.

## Audit REA du 2026-10-27

Corrigés (preuve en commentaire dans le code) : bilan d'attaque appliqué à l'attaquant (`FUN_004200d2`/`FUN_00420188`, ECX = attaquant à `0x41ec64`) et dégâts de site débloqués; FA_Cast hors portée avance vers sa cible, destination résolue une seule fois, fin via drapeau 0x200 et +5 en `+0x08` (`FUN_0042383d`); morts Spore via `FUN_004204bc` (garde 0x8, son, compteurs).

Écarts confirmés, non corrigés :

- Royaume de combat statique : `FUN_0042003c` applique ±1 selon les drapeaux 0x10000/0x20000 du bâtiment lié et prend la ligne du sous-type 0 pour un attaquant non chargé (`ev_d094e67f`, `ev_7eebf882`).
- Hall de départ : le port préfère un pad typé; `FUN_0046466f` prend le site classe 0 vide le plus proche (`ev_3cb7946b`).
- Source de recharge Build Tone : priorité Hall absente de `FUN_00420a55`/`FUN_00420dbd` (`game_session_delivery.c` `construction_refill_source`).
- Sélection d'un floater lié à un bâtiment d'une autre île : `FUN_0042f8f7` le sélectionne, le port l'ignore (`ev_aa63a0e6`).
- Alerte/latch de recrutement `+0x90` de `FUN_0045eaa7` absents (`ev_427930b7`).

Doutes à trancher : sites « hidden pad » exclus du hit-test (commit `4452b0a`, sans preuve), gardes CONSTR supplémentaires (`payload_12`, taille, réservation), `renderer_class != 0` refusant une tâche CONSTR, cas 1..0xd et 0x10..0x14 de `FUN_0041e569` non relus.

## Hors périmètre pour l'instant

Multijoueur (transport du commerce, cartes `ENDGNONP`), `intro.avi` et commandes `nevada` (rotation/zoom clavier).

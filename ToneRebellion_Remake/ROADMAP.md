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
2. ~~**Ordres de bâtiment**~~ (`TODO_INTERFACE` l.22, l.27) : fait — enregistrement `B+0x28..0x32`, `BC_*` (Attack/Defend/Recall/TrnStk), clic droit filtré par `DAT_00619290`, adoption `FUN_0042219e` (genre 0 compris), routage interîles par pont, lien gardé à la traversée. Reste: vérification en jeu de l'interîles.
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

Porté : volume/pan par distance (`FUN_0045b24d`), bullets/impacts des producteurs (items Léviathan 0x0a..0x15, seuls appelants de `FUN_00416342`), sons d'île `FEATnn`. Reste : `CRUMBLE` (émetteur de `FUN_0042fa0f` 5/7 inconnu) et phases SPECIAL de `FUN_0041760b`.

## Phase 6 — Portage Web (dernière priorité)

Seulement après les phases 1 à 5. Surface de rendu portable, adaptateur SDL3, cible Emscripten, données fournies par l'utilisateur. Plan : [TODO_WEB.md](TODO_WEB.md).

## Transverse — Vérification

Plusieurs items sont « portés, non vérifiés en jeu » (ordre des panneaux Hall, sélection floater, panneau inférieur droit, `IWMove`). Étendre `island_e2e.ps1` pour couvrir chacun, puis cocher.

## Questions REA ouvertes

À trancher par sous-agent avant le port concerné :

- Boucle de distribution souris des panneaux Hall; index d'état actif en vue île; route mode 0/1/2 `FUN_0042970c` → `FUN_0042fa0f`.
- Expéditeur du paquet de clic Repair, `FUN_00429f3a`, `FUN_00452b67`, attache automatique (`FUN_0041e569`).
- Paquet natif de `IWMove`.

## Audit REA du 2026-10-27

Corrigés (preuve en commentaire dans le code) : bilan d'attaque appliqué à l'attaquant (`FUN_004200d2`/`FUN_00420188`, ECX = attaquant à `0x41ec64`) et dégâts de site débloqués; FA_Cast hors portée avance vers sa cible, destination résolue une seule fois, fin via drapeau 0x200 et +5 en `+0x08` (`FUN_0042383d`); morts Spore via `FUN_004204bc` (garde 0x8, son, compteurs). Ensuite : l'entraînement (`FUN_0045cd75`) rafraîchit portée, royaume, vitesse, force et PV depuis la ligne du nouveau sous-type (une unité à distance entraînée gardait la portée 0 de l'ouvrier et immobilisait sa cible comme en mêlée); royaume de combat via `FUN_0042003c` (±1 selon 0x10000/0x20000 du bâtiment lié, ligne du sous-type 0 pour un attaquant non chargé).

Contrôle des guerriers (REA, `FUN_00435826`, `FUN_0042f8f7`, `FUN_0042fa0f` 3001..3003) : la sélection d'un floater prend son bâtiment sur toute île (panneau mode 3); un raccourci sélectionne son bâtiment sans changer l'île affichée; le clic droit (`param_3 = événement 7`) avec un bâtiment d'entraînement possédé sélectionné écrit l'ordre du bâtiment (genres 6/8 floater, 7 site ennemi, 9 sol) adopté par tout le groupe; l'ordre garde l'île de la cible; le clic sur le sol revient au Hall par défaut; la traversée d'un pont accorde l'accès à l'île (`FUN_00466b09` à l'étape 0x3c).

Combat des soldats (REA `FUN_004633a7`, `FUN_004211bb`, `FUN_0042219e`, `FUN_00421d82`, `FUN_0041e569` case 8; simulation avec `floater.txt`/`fltinf.txt`) : la charge d'entraînement vient de la ligne +8 (points d'attaque max, colonne 5) et non de la force; DefendArea (action 9) n'avance d'étape qu'à la fin de l'état courant (les défenseurs ne frappaient jamais); le point de l'état 9 est tiré une fois et l'état s'arrête dès qu'un ennemi est près de l'ancre (tous les 8 ticks); l'ordre du bâtiment est recopié sauf pendant une frappe (état 6/7, pas l'action), y compris sur un floater qui attaque ou défend une zone; un floater tenu en mêlée riposte (`FUN_00421d82`, soldats et Léviathans). Un soldat lié sous un tiers de ses PV (ou à court de charge en combat) rentre se soigner / recharger dans son bâtiment sur le stock +0x2a (action 2, état 2 : `FUN_0042219e`, `FUN_004211bb` case 1, `FUN_0041e569` case 1, `FUN_0045ddb8`), puis reprend l'ordre du bâtiment.

Écarts confirmés, non corrigés :


- Contre-attaque des Léviathans tenus en mêlée (`FUN_0042219e` -> `FUN_00421d82`, flag 0x10) absente.
- Tirage `FUN_00467260(3)` de `FUN_0042219e` fait dès qu'une cible floater existe; le port ne tire qu'avec une cible lieu aussi (séquence RNG décalée).
- Traversée de pont : le port force l'action 9 au départ et l'état 9 à l'arrivée; le natif garde l'action et finit en état 0 (`FUN_004210a9`, cas 0x10).
- Presse-papiers : enregistrement automatique de tous les bâtiments d'entraînement (natif : seulement le bâtiment sélectionné).
- `IWFltInfo` affiché seulement en modes général/lieu (natif : tout mode après 0x3f); masquage d'un floater mourant (0x8, timer >= 40) non testé au rendu.

- Hall de départ : le port préfère un pad typé; `FUN_0046466f` prend le site classe 0 vide le plus proche (`ev_3cb7946b`).
- Source de recharge Build Tone : priorité Hall absente de `FUN_00420a55`/`FUN_00420dbd` (`game_session_delivery.c` `construction_refill_source`).
- Sélection d'un floater lié à un bâtiment d'une autre île : `FUN_0042f8f7` le sélectionne, le port l'ignore (`ev_aa63a0e6`).
- Alerte/latch de recrutement `+0x90` de `FUN_0045eaa7` absents (`ev_427930b7`).

Doutes à trancher : sites « hidden pad » exclus du hit-test (commit `4452b0a`, sans preuve), gardes CONSTR supplémentaires (`payload_12`, taille, réservation), `renderer_class != 0` refusant une tâche CONSTR, cas 1..0xd et 0x10..0x14 de `FUN_0041e569` non relus.

## Hors périmètre pour l'instant

Multijoueur natif exact (canaux DirectPlay, chat, cartes `ENDGNONP`; lobby, coopération et synchronisation par tours du remake portés, voir [multijoueur](../behavior/multiplayer.md)), `intro.avi` et commandes `nevada` (rotation/zoom clavier).

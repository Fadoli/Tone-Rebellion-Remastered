# Floater movement primitives: REA evidence and port

This note records observed selection/input/movement procedures and separates them
from behavior still needing class/state checks. Ghidra pseudocode is a decompiler
reconstruction, not recovered source; field names and inferred types remain
provisional. The user has clarified that workers cannot receive direct orders:
selecting them only shows stats, while soldiers and mages are orderable. The
remake now routes mode `0x13` to state 9 for selected floaters with nonzero
subtype. That subtype mapping is an implementation gate following the user's
constraint; the original allowlist and `FA_Cast` interaction remain unresolved.


Sections détaillées ci-dessous. Les titres sont repris ici pour conserver les anciens liens d’ancrage.

## Input and destination path
[Section complète](MOVEMENT_INPUT.md#input-and-destination-path)

### `0x4c` coordinate order and its receiver
[Section complète](MOVEMENT_COORDINATE_ORDERS.md#0x4c-coordinate-order-and-its-receiver)

## Interaction cursor lifecycle
[Section complète](MOVEMENT_SPEED.md#interaction-cursor-lifecycle)

## Unit tick and speed source
[Section complète](MOVEMENT_SPEED.md#unit-tick-and-speed-source)

## Tick, state machine, target and arrival detail
[Section complète](MOVEMENT_TICK.md#tick-state-machine-target-and-arrival-detail)

### Update sequence
[Section complète](MOVEMENT_TICK.md#update-sequence)

### Destination resolution and step size
[Section complète](MOVEMENT_STEP_KERNEL.md#destination-resolution-and-step-size)

### Target source and facing adjustment
[Section complète](MOVEMENT_STEP_KERNEL.md#target-source-and-facing-adjustment)

### `FA_Move`: local target approach and arrival
[Section complète](MOVEMENT_LOCAL_ORDERS.md#fa_move-local-target-approach-and-arrival)

### `FA_DefendFlt`: reach target, select a nearby unit, then approach it
[Section complète](MOVEMENT_LOCAL_ORDERS.md#fa_defendflt-reach-target-select-a-nearby-unit-then-approach-it)

### Autonomous order selection and execution
[Section complète](MOVEMENT_AUTONOMOUS_ORDERS.md#autonomous-order-selection-and-execution)

### `FA_Wander` destination generation and repeated movement
[Section complète](MOVEMENT_AUTONOMOUS_ORDERS.md#fa_wander-destination-generation-and-repeated-movement)

### Attack orders: approach then stationary combat state
[Section complète](MOVEMENT_LOCAL_ORDERS.md#attack-orders-approach-then-stationary-combat-state)

### Training and recharge orders: travel to a location record
[Section complète](MOVEMENT_TRAVEL_ORDERS.md#training-and-recharge-orders-travel-to-a-location-record)

### `FA_ObtainObject`: assigned location or owner candidate
[Section complète](MOVEMENT_TRAVEL_ORDERS.md#fa_obtainobject-assigned-location-or-owner-candidate)

### Cross-island handoff through state `0x11`
[Section complète](MOVEMENT_TRAVEL_ORDERS.md#cross-island-handoff-through-state-0x11)

### `FA_Deliver`: site search, island handoff and local approach
[Section complète](MOVEMENT_SITE_ORDERS.md#fa_deliver-site-search-island-handoff-and-local-approach)

### `FA_Repair`: candidate site then local approach
[Section complète](MOVEMENT_SITE_ORDERS.md#fa_repair-candidate-site-then-local-approach)

### `FA_Build`: three local route states
[Section complète](MOVEMENT_SITE_ORDERS.md#fa_build-three-local-route-states)

### `FA_Cast` (`0x13`): target resolution without locomotion
[Section complète](MOVEMENT_SPECIAL_ORDERS.md#fa_cast-0x13-target-resolution-without-locomotion)

### `FA_MergeWith` (`0x14`): approach, then idle/roam state
[Section complète](MOVEMENT_SPECIAL_ORDERS.md#fa_mergewith-0x14-approach-then-idleroam-state)

### Orders without a local consumer branch
[Section complète](MOVEMENT_ORDER_EDGE_CASES.md#orders-without-a-local-consumer-branch)

### Facing and rendered anchor
[Section complète](MOVEMENT_ORDER_EDGE_CASES.md#facing-and-rendered-anchor)

## Current port and limits
[Section complète](MOVEMENT_PORT.md#current-port-and-limits)

## Order 9 from the Hall move context
[Section complète](MOVEMENT_HALL_CONTEXT.md#order-9-from-the-hall-move-context)

## Audit direct mouvement/combat (pseudocode relu par l'agent principal)

Evidence: `FUN_00422d27` `ev_dce3014d` et assembleur `ev_12c6e0e8`, `FUN_004672a6` `ev_11cfa067` (distance de Tchebychev), `FUN_00420217` `ev_6ccca76e`, `FUN_004204bc` `ev_2016a3eb`, `FUN_0041e569` `ev_8578fcc7`, `FUN_0042520e` `ev_124b4bd8`, `FUN_00425296` `ev_436a1ff2`.

- Corrigé: la vitesse réduite près de la cible est `distance / 4` tronqué (`CDQ/AND 3/ADD/SAR 2` à `0x422f8c`), pas arrondie vers le haut; un pas nul retombe sur `tick & 1`. `floater_motion.c` et son test suivent désormais le natif.
- Corrigé: l'expiration du drapeau floater `0x100` (bouclier du cast niveau 0/1 et `0x1100` au niveau 2) manquait. `FUN_0041e569` (queue) incrémente le compteur `+0x24`; au-delà de 2000 (`FUN_00425296(0x100)`) le drapeau tombe; avec `0x1000`, au-delà de 0xdac (3500) les deux tombent. Porté dans `game_session_tick_floater_cast_pulse`.
- Confirmé conforme: étapes de déplacement par axe borné, doublement de vitesse du sous-type 0 par propriétaire, +1 des sites 0x2c/0x2d/0x2e, états 8/9/0xe à vitesse 1 près de la cible (rayon 100), table `FUN_00425296` (8 -> 40, 0x2000 -> 45), minuterie de mort, tirage de dégâts de `FUN_00420217` (trois tirages bornés à 10, garde propriétaire/0x8/0x100) et application de `FUN_004204bc` (mort quand PV < 1).
- Non rediffé ligne à ligne: le calcul x87 du pourcentage de touche de `FUN_00420217` (le décompilateur le perd; le port le reconstruit), les cases d'actions 6/7/8/9 de `FUN_0041e569` et les fonctions `FUN_00420721`, `FUN_00423068`, `FUN_004200d2`, `FUN_00420188`, `FUN_00415fc6`. Non vérifié en jeu.

### Hit chance de `FUN_00420217` (assembleur relu, `ev_d4bb6e22`; constantes `ev_15f172be`, table de saut `ev_d7687baa`, `__ftol` `ev_7430d34a`)

`FUN_004533a8` (tours) appelle `FUN_00420217(ligne pad +0x0a, -1, propriétaire)`; `FUN_004200d2` (frappe de floater) l'appelle avec la puissance de l'attaquant, son royaume (`FUN_0042003c`) et son propriétaire. Corrigé dans `game_session_combat.c`:
- Le terme de difficulté est un double: difficulté 0 -> `p/4` (plancher 1), 1 et 2 -> `p/2` (plancher 2), 3 et 4 -> `2p/3` (plancher 3); le port utilisait des divisions entières et traitait 2 comme 3+.
- La correction « royaume différent » multiplie le terme de difficulté (pas la puissance brute): `(0/limite - 0.5) * terme`, signe inversé quand le royaume attaquant > 1 (les globales `DAT_00618e4c/50` valent 0 au chargement).
- Le pourcentage `(int)(60*score/14) + 10` utilise `__ftol` qui TRONQUE (`OR AH,0xc` à `0x472c7b`); le port arrondissait au plus proche.
- Voie des tours (`royaume = -1`): le royaume attaquant devient celui de la cible, donc aucun terme de royaume; le port appliquait un terme dérivé du sous-type.
- Défense: sous-types 0 et 9 ont une défense nulle (le port ajoutait les niveaux pour le sous-type 0); un sous-type 9 prend le royaume de l'attaquant.
Les globales `DAT_00618e4c/50` ont 3 références chacune hors de ce calcul (`0x438b9b/0x438e45`, `0x438bbb/0x438f9e`), non analysées. Non vérifié en jeu.

### Puissance d'attaque: une seule fonction (`FUN_0041fde6`, `ev_6840e960`; chargeur `FUN_004633a7`, `ev_8709314a`)

`FUN_004200d2` (attaque de floater) et `FUN_00420188` (attaque de site, `ev_18b2df90`) appellent la même `FUN_0041fde6`. Le chargeur écrit les six entiers de chaque ligne aux décalages `+0` (portée), `+2` (royaume), `+6` (PV), `+8` (points d'attaque max, comparés au compteur de charge dans `FUN_0041e569` cas 1), `+0xa` (force d'attaque), `+0xc` (vitesse). La base de `FUN_0041fde6` est donc la force d'attaque (`+0xa`), pas les points d'attaque max (`+8`). Le port utilisait `max_attack_points` pour les sites; corrigé: une seule fonction `floater_attack_power` avec la base `attack_strength` (catégorie 4 ou sous-type non nul chargé), +3 si la source liée a le drapeau `0x8000`, +1 pour les bits de glyphe `0x01/0x40/0x400` du joueur sur une source `0x2c/0x2d/0x2e`, puis niveau × 3 plus part de 1/22 (catégorie 4) ou niveau × 2. Le terme de glyphe était absent de la voie floater. Non vérifié en jeu.

### RNG et rayon d'approche (assembleur relu: `FUN_00467260` `ev_ea4dec92`, `FUN_00474b80` `ev_85045540`, `FUN_00474b90` `ev_c71d7459`; `FUN_00420721` `ev_fd5a4201`, `FUN_00423068` `ev_f59cd438`)

- Corrigé: `FUN_00467260` charge la graine `[0x4a4b78]`, la copie dans la graine CRT, fait un pas du LCG MSVC et RÉÉCRIT le résultat sur 15 bits dans `[0x4a4b78]`. Le tirage suivant repart donc de la sortie 15 bits précédente, pas de l'état 32 bits. `tone_rng.c` gardait l'état complet (suite 41, 18467, 6334 pour la graine 1); elle suit désormais le natif (41, 172, 600). Tous les tirages après le premier changent, donc aussi mondes générés, cibles de tours et musiques; les tests `test_tone_rng` et `test_game_music` ont été mis à jour. La graine initiale écrite par le natif dans `[0x4a4b78]` n'est pas identifiée.
- Corrigé: le rayon d'approche de `FUN_0041e569` cas 0xe/0xf vient de `FUN_00420721` (portée de la ligne, `×5/4` tronqué en 16 bits avec le bit de glyphe `0x04` et une source liée); 10 par défaut.
- Non porté (relevé par lecture directe de `FUN_00423068`): le rejet d'un ordre quand le point d'arrivée tombe hors de `[min, max]` du propriétaire (`return 0` -> `FUN_00421ec1(-1)`), l'état 8 qui stocke un décalage aléatoire relatif `(rand(200)-100, rand(200)-100)` sans borne de `y`, et les décalages d'approche `±0x4a/0x4c` issus de `FUN_0045575c` pour les états 3/4.

### Sélections pondérées et recherche de cible (`FUN_0041e28e` `ev_17c3c46d`, `FUN_00420a55` `ev_54951b3e`, `FUN_00420635` `ev_ccde6e44`, `FUN_00420991` `ev_1f975170`; agent haiku/général pour le premier tri, tous les faits ci-dessous relus)

- Corrigé: `FUN_0041e28e` calcule `poids_i = somme / d_i`, normalisés à 1000, puis des seuils CUMULÉS entiers `seuil_i = ftol(seuil_{i-1} + poids_i)` (`__ftol` tronque), et force le dernier seuil à 1000 pour qu'un tirage choisisse toujours un candidat. Le port arrondissait au plus proche (action9) ou n'accumulait pas du tout (livraison, copie distincte) et pouvait renvoyer -1. Une seule fonction `game_session_pick_inverse_distance` sert maintenant aux quatre usages.
- Corrigé: `FUN_00420a55` cas 4 filtre par la distance du point cible (< 90, zéro permis) mais collecte et pondère la distance du floater chercheur au site (`FUN_00420635`); le port utilisait le point cible pour les deux.
- Corrigé: `FUN_004208eb` n'a pas de cas particulier pour un floater protégé de catégorie 4; le port renvoyait toujours ce floater.
- Non porté, constaté: `FUN_00420991` teste une table d'île `DAT_0061fa2e[île] >= 0x65` (inverse la règle catégorie-4 pour les sources de catégorie 4); table nulle au chargement, écrivain inconnu.
- Non porté, rapporté par agent (non relu): effets d'ordres (`FUN_004211bb`) pour les actions 2/0x11 (recharge), 0xb/0xc (dépôt d'objet avant charge), 0xd (branche « objet porté » -> état 4), sous-étapes de livraison (action 4), action 5 stockée comme 4, annulation `FUN_00466533` après attaque; et dans `FUN_0041e569` le bloc de fin (sous-type 8 -> ordre vers le Hall, sous-type 4 -> enregistrement du bâtiment), les drapeaux de mêlée `0x10`/`0x40` (jamais écrits par le port; `FUN_00422d27` bloque le pas si `+0x1c & 0x411`), l'état 8 (sortie via `FUN_004208eb`), la cadence 1/8 de l'état 9, les appels `FUN_00416a9a(5)` à l'état 0x15.

### Défense (état 8), mêlée (drapeaux 0x10/0x40) et frappes immobiles (relus: `FUN_00423068` `ev_78129691`/asm `ev_f59cd438`, `FUN_00422d27` `ev_dce3014d`, `FUN_0041e569` `ev_8578fcc7`, `FUN_004211bb` `ev_3477c421`)

- Corrigé: en état 8 le natif stocke dans `+0x28/+0x2a` un décalage `(rand(200)-100, rand(200)-100)` tiré une fois au plan (x puis y, plan rejeté si x hors de `[min, max]` avec min = 0 par défaut) et `FUN_00422d27` ajoute chaque pas la position du floater protégé (`DAT_006137c8/ca`). Le port tirait une position autour du défenseur lui-même à chaque tick (jamais de suivi). Désormais: décalage fixé au plan (`follow_offset_x/y`), destination = protégé + décalage borné à x 0..0x9ff, y 0x28..0x122; replan seulement à l'arrivée sans candidat.
- Corrigé: les états 6 et 7 (frappes) sont immobiles dans le natif (`FUN_00422d27` non appelée); le port poursuivait la cible.
- Corrigé: mêlée. À l'arrivée en état 0xf (hors action 0x14) d'un floater sans attaque à distance (`FUN_00420721` renvoie 0), la cible reçoit `0x10`, l'attaquant `0x40`. Un floater avec `0x10` ne fait pas de pas (`+0x1c & 0x411`, ici 0x10 seul retenu) tant qu'un floater de l'île le cible avec `0x40`. Le port n'écrivait jamais ces drapeaux.
- Non vérifié en jeu. Les bits `0x01` et `0x400` du même masque de blocage (`FUN_00422d27` non appelée) ne sont pas portés.

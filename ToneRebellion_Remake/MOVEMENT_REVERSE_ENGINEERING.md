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

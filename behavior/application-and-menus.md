# Application, menus et donnees

Cette page est un index; le détail est réparti en pages thématiques pour limiter la taille de navigation.

## Pilotage du jeu

- [Pilotage du jeu](application_and_menus_pages/page-01.md)

## Son et musique

- [Son et musique](application_and_menus_pages/page-01.md)

## Écran « nouvelle partie » et texte cintré

- [Écran « nouvelle partie » et texte cintré](application_and_menus_pages/page-01.md)

## Chargement de données, archives, monde et rendu

- [Chargement de données, archives, monde et rendu](application_and_menus_pages/page-02.md)

## Revue de l'écran Nouvelle partie (REA, `FUN_0044e9c7`, `FUN_0044ebea`, `FUN_0044e4f8`, `FUN_0044ec5d`; ev_3b86c0b1…, ev_b4501114…, ev_4970330f…)

Observation: la fenêtre (état 1: `+0x74 = 0xbf`, `DAT_0049f538 = -1`, blocs de `newgame.txt` par `FUN_0044e77f`) route les clics par cercles (`FUN_0044e4f8`): quatre tribus (rayon < 50) -> messages 60..63, centre (320,240): `d² < 100` -> 4 (difficulté, message 55), `d² < 200` -> 5 (taille du monde, message 53),
ces deux zones seulement si `DAT_004befe0 == 0` ou (`DAT_004befe0 != 0` et `DAT_004befec == DAT_004befe8`). Défaut: la tribu sélectionnée est la plus petite `i` dont le bit est posé dans `DAT_005e1730[DAT_004befec]`, sinon -1 (pas de panneau de tribu). Sprite de difficulté `levidiff`
(`DAT_004bf11c`) en (320,240); légende de survol à `y = 0x1ae` depuis `DAT_005e4c30`. Touches natives (cas 5: Home, flèches, haut/bas) agissent sur `+0x74` et sont gardées par `DAT_004c2b74` (`nevada`, inerte). Début de partie: message 52 (`BEGINGAME`) vers MASTER; graine `DAT_0049c9b0`
(aléatoire `FUN_00467260(2) << 1` si négative et `DAT_004c2b9c != 0`), mode solo 1; lien 52 -> `FUN_004121b7` cas 9 non vérifié.
Port: messages 52/53/55/60-63 et cercles des tribus (`tribe_icon_at`) conformes; zones centrales non gardées (équivalent en solo, `DAT_004befe0 == 0`); défauts monde 0, difficulté 0, tribu 0 (le natif prend la première tribu possédée, tous bits à posséder inconnus); raccourcis du port (flèches, `D`, `1`..`4`) sans équivalent natif en solo
(extras d'ergonomie); pas de graine aléatoire (monde fixe). Inconnues: rôle de `DAT_004c2b74`/`DAT_004befe0/e8/ec`, valeurs initiales de `DAT_004bf11c`/`DAT_005e1730`, chemin de clic des panneaux de pied.

Tribus possédées au démarrage (REA, ev_2fadf347…, ev_3dd5daf1…, ev_8d6976fc…, ev_b006252a…): `DAT_004bf0f0[0..3]` et `DAT_005e1730[0..3]` valent 0 dans l'image; `FUN_00448e5a` cas 1 copie `0x4bf0f0 -> 0x5e1730` (4 entrées) et aucun écrivain direct de `0x4bf0f0` n'est trouvé
(les écritures passent par le même type de messages/commandes que `DAT_004bf110`, non vus statiquement). Les messages 60..63 (`FUN_00448e5a` cas 0x3c..0x3f) n'alternent aucun bit: ils posent `DAT_004bf100[befec] = i` et envoient le message 6; le dessin ignore `0x4bf100`.
Message 53 fait cycler `DAT_004bf118` (0..2) puis envoie 7; message 55 cycle `DAT_004bf11c` (0..4) puis 8; message 52 envoie 9 seulement si tous les masques `befe4` sont non nuls. Avec des zéros, la tribu par défaut du dessin est -1 (aucun panneau);
le « défaut tribu 0 » du port est un choix du port, non une observation native. Inconnu: comment `0x5e1730` devient non nul en solo.

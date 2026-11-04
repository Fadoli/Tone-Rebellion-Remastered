# Multijoueur (DirectPlay, lobby, transport et synchronisation)

Source: REA statique sur `FLOAT.EXE` (Ghidra, aucune exécution), trois sous-agents haiku; ECX vérifié à l'assembleur aux sites cités. Evidence IDs (préfixes): `ev_5d525afa`, `ev_4ecf4428`, `ev_dc2683ef`, `ev_942674`, `ev_2a8abf`, `ev_7dafbeac`, `ev_a94628c9`, `ev_407c43b3`, `ev_e76bb0bc`, `ev_8b91ebeb`, `ev_b3126f57`, `ev_54c0ae3b`, `ev_4be6368`, `ev_6f7dd1e6`, `ev_e2e16cc25be5`, `ev_f9766eff3e03`, `ev_96e30c7a`, `ev_0b3cd8f3fb26`, `ev_1143a3a4`, `ev_8e521b0585d1`, `ev_add94e1e200`, `ev_0123adaea3de`, `ev_814508f2b1dc`, `ev_374a5bda4d8c`, `ev_bbdf10287a1e`, `ev_c1868c923bd8`, `ev_1f76cc3b`, `ev_1a99fa08`, `ev_242a6f46`, `ev_ff1cb528`.

## Session DirectPlay (observation)

- Imports réseau: `DPLAYX.DLL` `DirectPlayCreate` (`FUN_0044ab7a`) et `DirectPlayEnumerateA` (`FUN_0044aa7e`, fournisseurs de service). Pas de `DirectPlayLobby`, pas de Winsock trouvé (table d'import non énumérée en entier). `CoCreateInstance` ne sert qu'à DirectShow (`intro.avi`).
- Interface `DAT_005e1770` (QI de `DAT_005e1ef0`); appels COM avec l'interface poussée en premier argument. Décalages: `+0x18` CreatePlayer, `+0x34` EnumSessions (`FUN_0044aed8`, GUID d'application `0x494688`), `+0x60` Open (drapeau 1 = rejoindre `FUN_0044afcc`, 2 = créer `FUN_0044acd8`, au plus 8 joueurs), `+0x64` Receive, `+0x68` Send. Noms déduits des arguments et des chaînes d'erreur voisines, `dplay.h` non consulté.
- Interface de connexion: `FUN_0044c2b9`, `PropertySheetA` de 5 pages (gabarits 0x81, 0x6c, 0x82, 0x83, 0x84), clé `HKLM\Software\The Logic Factory\Tone R…`; chaînes « Héberger / Rejoindre une session (3/4) ». Ce n'est pas un écran de `windows.txt` (états 0..8 seulement). Appelants des fonctions DirectPlay: procédures de pages non résolues.
- `float.cfg` `network` → `DAT_004c2b88 = 1`, lu seulement par `FUN_0041c1d6`: avec ce mot-clé le jeu ouvre la feuille de propriétés puis pose `DAT_004befe0 = 1`; sinon `DAT_004befe4 = 1` (solo). `net_name` est copié dans `DAT_0049c9b8` sans lecteur trouvé.

## Table des joueurs `0x4befe0` (observation, ECX de `FUN_004121b7`)

`+0` drapeau multijoueur (`DAT_004befe0`), `+4` nombre de joueurs, `+8` indice de l'hôte, `+0xc` indice local, `+0x10 + k·0x40` noms, `+0x110 + 4k` masques de tribus, `+0x120 + 4k` DPID (`DAT_004bf100`), `+0x138` taille de monde, `+0x13c` difficulté, `+0x140` partie lancée. Écrivains de `+8/+0xc/+0x10` non décompilés.

## Transport (observation)

- File unique `FUN_004133f2(canal, type, données, longueur, drapeaux, instant)`: 32 entrées de 0x60 octets (`+0` occupée, `+4` canal, `+8` instant d'exécution, `+0xc` longueur + 4, `+0x10` type, `+0x14` données). Mise en file locale si solo, si local = hôte ou si `drapeaux & 6`; envoi réseau si multijoueur et `!(drapeaux & 6)` par `FUN_00412d70`: en-tête de 12 octets (canal, instant, type) + données (≤ 0x53), destinataire `DPID[hôte]` pour un invité, tous (0) pour l'hôte. Les invités ne parlent qu'à l'hôte; l'hôte reçoit, met en file et rediffuse.
- Instant d'exécution: solo `maintenant + période`; réseau, prochain multiple de la période (`+0x1278`) plus un compteur de créneau. Défilement `FUN_00413344`: premier enregistrement du canal dont l'instant ≤ tick courant `+0x1274`.
- Canaux: 1 commandes de jeu (`FUN_00414081`, 18 sites; vidé par `FUN_00466221`: type 1 → `FUN_00465793`, 2 → `FUN_004672ef`); 2 lobby/session (`FUN_004140dd`; vidé par `FUN_00413e8a` → `FUN_004121b7`); 3 texte (`FUN_0041412d`, multijoueur seulement); 4 contrôle de cadence (`FUN_00414106`, lu par `FUN_00413675`).
- Réception: `FUN_00412eac` boucle sur Receive et remet chaque paquet en file avec son instant.

## Lobby et début de partie (observation)

- L'écran Nouvelle partie (état 1) sert de lobby: `FUN_0044ec5d` liste les joueurs; taille du monde et difficulté (messages 53/55 → types 7/8) seulement chez l'hôte (`befec == befe8`); un clic de tribu (60..63) envoie le type 6 pour le joueur local (bascule de bit refusée si un autre joueur la tient).
- `FUN_004121b7`: 1 ajout de joueur, 2 retrait (si l'hôte part: retour au solo, seul écrivain de `DAT_004befe0 = 0`), 4 indice local, 5/6 réservation de tribu, 7/8 réglages, 9 début, 10/11 réglages divers, 12 remise à zéro.
- BEGINGAME (52): si tous les masques de tribus sont non nuls, l'hôte envoie le type 9 dont la seule charge est `FUN_0041be72()` (dword bas de `QueryPerformanceCounter`); le cas 9 en fait la graine du tirage `DAT_004a4b78` (`FUN_00467260`) sur chaque machine, puis `FUN_004637fc(monde, difficulté, …)`. Monde, difficulté et tribus sont donc déjà connus de tous avant le type 9.

## Synchronisation en jeu (observation et interprétation)

- Observation: les commandes passent par le canal 1 avec un instant futur commun; l'exécution est gardée par le tick, pas par une attente par joueur. Canal 4: type 1 période, 2 créneau validé par l'hôte (`FUN_00413088`: l'hôte n'avance que si chaque invité a annoncé plus de 0x1f), 3 arrivée d'un pair, 5 accusé, 6 progression d'un invité (tous les 5 créneaux). `FUN_00413b68` (invité) pose `DAT_004bf114 = retard >> 2` pour rattraper (appels de tick supplémentaires par image).
- Interprétation: pas de jeu verrouillé à tour strict mais un ordonnancement de commandes à instant différé, cadencé par l'hôte; la simulation est déterministe à partir de la graine du type 9.

## Inconnues

Procédures des pages de la feuille de propriétés et callbacks EnumSessions; écrivains de l'indice hôte/local et des noms; types précis des commandes du canal 1; `FUN_00412c1d` (cas 3); sens des cas 10/11; flags de session 0x44; débordement possible d'une entrée de file (> 76 octets) sur le chemin local (inférence statique).

## Port

Le remake ne peut pas utiliser DirectPlay; il transporte ses propres enregistrements en TCP non bloquant (`menu_app_sections/net_session.inc`, port 28610), avec un en-tête de 4 octets. Entrée: bouton « Multijoueur » du titre (touche `M`), écran propre au remake (`menu_app_sections/net_setup_screen.inc`: nom, adresse, port, Héberger/Rejoindre, valeurs gardées dans `saves/network.cfg`; un échec de connexion ou un Échap du lobby y ramène), raccourcis `H`/`J` du titre, ou `--host` / `--join adresse` (`--port`, `--name`, prioritaires sur le fichier). La feuille DirectPlay native (`FUN_0044c2b9`) n'est pas reproduite.

- **Lobby** (`src/core/net_lobby.c`, sans API système): l'écran Nouvelle partie devient le lobby (liste en haut au centre, géométrie de `FUN_0044ec5d` non portée); réglages réservés à l'hôte; début = graine (compteur de performance de l'hôte), monde, difficulté, tribu par emplacement; types 1/6/9 repris des numéros natifs. **Coopération (extension du remake):** plusieurs joueurs peuvent choisir la même tribu et la jouer ensemble; un invité prend d'abord la première tribu libre.
- **Commandes** (`src/core/game_command.c`): les 23 mutateurs de session appelés par l'interface (ordres de bâtiment, tâches, commerce, diplomatie, sorts, glyphes, inventaire, déplacement de bâtiment, stocks…) passent par `issue_command`; en solo la commande s'applique tout de suite, en réseau elle part vers l'hôte et l'appelant reçoit le résultat prédit sur une copie de l'état.
- **Tours** (`src/core/net_lockstep.c`): un tour par tick (50 ms); l'hôte regroupe les commandes reçues pendant le tick t dans le paquet du tour t + délai et le diffuse avec l'empreinte FNV-1a de l'état qu'il vient de terminer (hors configuration et presse-papiers). Le délai suit l'aller-retour mesuré (PING/PONG chaque seconde): 1 + ⌈RTT/2 / 50 ms⌉ tours, borné à 1..10 (équivalent de la période envoyée par l'hôte, canal 4 type 1 → `+0x1278`); un délai qui grandit émet les tours sautés vides, un délai qui diminue retient les commandes, aucun tour ne manque. Personne ne simule un tour sans son paquet; l'hôte s'arrête si un invité a 14 tours de retard (équivalent de `FUN_00413088`); un invité qui tient plus de délai + 1 tours d'avance (une image tombée juste avant un paquet a calé) fait 2 ou 3 ticks par image jusqu'à revenir à un tour de l'hôte (`DAT_004bf114`); le délai voyage dans chaque paquet. Les sockets signalent leurs données au fil de l'eau (`WSAAsyncSelect`) au lieu d'attendre la minuterie de 50 ms, qui ajoutait jusqu'à deux images à chaque aller-retour. Une empreinte différente arrête la partie avec « Désynchronisation au tour N ». La simulation tourne sur tous les écrans (carte comprise) avec l'horloge de session; le tirage de musique utilise un générateur local; vitesse, pause, sauvegarde/chargement (comme `FUN_004578df`, gardé par `DAT_004befe0 == 0`) et aides de test F5..F9 sont inactifs en réseau. Départ d'un invité: sa tribu reste inactive, l'hôte continue; perte de l'hôte: l'invité continue seul.
- **Vérifié** avec deux instances sur 127.0.0.1 (script e2e local, touches de test `C`/`H` actives seulement avec `TONE_REBELLION_E2E_STATE`): coopération sur la tribu 1, 380 ticks sans désynchronisation, une commande émise par l'invité puis par les deux à la fois appliquée au même tick des deux côtés, l'hôte poursuit après le départ de l'invité. Latence mesurée en local (127.0.0.1): aller-retour 0..4 ms, délai 1..2 tours, commande appliquée 1 à 2 ticks après son émission (62..94 ms), hôte et invité au même tick; 20 ticks/s mesurés en solo, chez l'hôte et chez l'invité. Même essai avec deux instances `remake_sdl` (tribus distinctes, départ par le bouton NEWGAME de l'hôte): commandes de l'invité puis des deux appliquées au même tick, 728 ticks sans désynchronisation, aller-retour 9..10 ms, délai 2 tours.
- **Tolérance au retard (2026-11-04):** l'hôte prend au plus 14 tours (700 ms) d'avance sur l'invité le plus lent puis attend; l'invité attend ses paquets; après 1 s d'attente chaque joueur voit « En attente de <nom> », et le retardataire rattrape à 2–3 ticks par image. Une erreur de socket, une fermeture TCP ou 15 s sans rien recevoir coupent la connexion, qui passe alors par la reconnexion ci-dessous. Avant ce correctif, un tampon d'envoi plein (lien lent, fenêtre figée, envoi de sauvegarde) coupait le joueur et un envoi partiel cassait le flux: chaque pair a maintenant une file d'envoi (1 Mo) vidée à chaque image, et `TCP_NODELAY` évite l'attente de Nagle sur les petits paquets. **Vérifié:** invité puis hôte suspendus 8 s chacun: pas de coupure, message d'attente des deux côtés, reprise sans désynchronisation.
- **Écarts et restes:** format et cadence propres au remake (pas les canaux natifs); chat (canal 3) absent; `location_move_*` est global à la session (deux joueurs ne peuvent pas déplacer un bâtiment en même temps); reconnexion propre au remake (ci-dessous).

## Pause et sauvegarde en réseau (extension du remake, 2026-11-04)

L'original refuse Sauvegarder, Charger et la pause en réseau (`FUN_004578df`, `DAT_004befe0 != 0`). Le remake, à la demande de l'utilisateur, permet deux de ces actions :
- **Pause :** la zone pause du panneau d'options, ou Échap puis la zone, envoie `GAME_COMMAND_SET_NETWORK_PAUSE`. La commande pose `GameSession.network_paused` au même tour sur chaque machine. Les tours continuent de s'échanger, pour que la reprise puisse arriver, mais `net_run_frame` ne simule plus le monde et l'horloge d'animation s'arrête. N'importe quel joueur peut mettre en pause ou reprendre.
- **Sauvegarde :** la zone Sauvegarder et `F5` ouvrent l'écran de sauvegarde. Le fichier est une copie locale de la session commune, et les tours continuent pendant que cet écran est ouvert. Recharger cette sauvegarde hors réseau la reprend en solo (`multiplayer_session` et `network_paused` remis à 0). Charger reste fermé en réseau.

**Vérifié :** deux instances sur 127.0.0.1, port 28777, dossiers de sauvegarde temporaires.
- L'hôte met en pause : les deux machines restent figées au même tour, l'horloge d'animation arrêtée et l'empreinte identique.
- L'invité reprend : les deux repartent ensemble.
- `F5` côté invité : les tours et l'empreinte restent identiques chez les deux pendant l'écran de sauvegarde.
- Aucune désynchronisation. `resume.gam` est écrit des deux côtés en quittant.

## Reconnexion (extension du remake, 2026-11-05)

L'original n'a pas de reconnexion (DirectPlay). Dans le remake :
- **Hôte :** un joueur coupé garde son slot 120 s (`g_net_reserved`). La partie continue sans lui, sa tribu reste inactive, et le port d'écoute reste ouvert pendant la partie (les nouveaux joueurs sont refusés). Passé ce délai, sa tribu rend ses glyphes et objets (`GAME_COMMAND_HAND_BACK_PLAYER`, comme `FUN_004121b7` cas 2).
- **Invité :** il retente une connexion toutes les 2 s pendant 120 s, puis envoie `NET_RECORD_REJOIN` (0x47 : slot, nom). Pendant ce temps son monde est figé. S'il échoue, il continue en solo.
- **Resynchronisation :** l'hôte envoie la `GameSession` telle qu'au début de son tour courant (`NET_RECORD_RESYNC` 0x48, morceaux de 2 Ko), puis les paquets de tour déjà faits, et remet l'invité dans le lockstep à ce tour. L'invité garde ses octets locaux (avant `random_state` et le presse-papiers, hors empreinte). Même version requise : la taille de `GameSession` doit être identique.
- **Silence :** 15 s sans rien recevoir compte comme une coupure (l'hôte envoie un ping par seconde, l'invité répond et acquitte chaque tour).

**Vérifié** (deux instances, 127.0.0.1) :
- Invité suspendu 20 s : l'hôte le coupe à 15 s et continue ; à la reprise, l'invité revient en moins d'1 s, avec la même empreinte, sans désynchronisation, et ses commandes passent.
- Hôte suspendu 20 s : l'invité revient seul à la reprise.
- Invité tué : son slot est libéré après 120 s (« G a quitte la partie »).

## Vitesse de jeu en réseau (extension du remake, 2026-11-04)

Observation (REA, ev_f30649de, ev_61f0589e, ev_0123adae, ev_02d74de1): la boucle `FUN_0041c46f` appelle `FUN_00413e8a` `DAT_004bf110 + DAT_004bf114` fois par image, sans test d'écran. Les touches `8`/`9` (pavé `-`/`+`) sont traitées par `FUN_0046a5b7`, appelée par la pompe `FUN_00469f56` pour tous les états (carte et île), bornées 1..3. `DAT_004bf110` = `GAMEENV(0x4befe0)+0x130`, posé à 2 en réseau aux cas 9 et 0xc de `FUN_004121b7`. `DAT_004bf114` n'est écrit que par `FUN_00413b68` en réseau: ticks de rattrapage (retard >> 2 au-delà de 4 périodes, 0 sous 2 périodes). Interprétation: pas de rattrapage en solo.

Remake: `8`/`9` envoient `GAME_COMMAND_SET_NETWORK_SPEED`, qui pose `GameSession.network_speed` au même tour partout; chaque tour simule ce nombre de ticks. Écarts: pas de garde `multispeed`, départ à 1 (pas 2), pas de `DAT_004bf114` (le rattrapage du remake rejoue des tours, `net_lockstep_frame_ticks`). En solo la vitesse s'applique aussi sur la carte du monde.

**Vérifié:** deux instances; vitesse 3 côté invité puis 2 côté hôte: 3 puis 2 ticks par tour sur les deux machines, aucune désynchronisation.

## Reprendre une partie sauvegardée en réseau (extension du remake, 2026-11-04)

- **Chargement par l'hôte :** dans le lobby, la touche `L` ouvre l'écran Charger, qui accepte une sauvegarde du remake ou d'origine. En cours de partie, la zone Charger du panneau d'options fait de même pour l'hôte seul (fermée aux invités). Le choix renvoie toutes les machines au lobby (`NET_RECORD_LOBBY_RETURN` 0x46, `net_back_to_lobby`) avant l'envoi du fichier ; un retour sans choix ramène l'hôte à la partie.
- **Envoi aux invités :** le fichier part à chaque invité (`NET_RECORD_SAVE_DATA` 0x44 : type, taille, décalage, puis jusqu'à 2 Ko). L'hôte envoie 4 tranches par invité et par sondage, pour ne pas remplir les sockets non bloquantes ; un invité qui arrive plus tard reçoit le fichier depuis le début.
- **Application :** chaque machine applique les mêmes octets (`net_load_apply`) et confirme (`NET_RECORD_SAVE_ACK` 0x45).
- **Lobby :** il devient le choix de tribu d'une partie chargée, comme en solo (tribus non jouées en noir). Taille du monde et difficulté sont celles de la sauvegarde ; l'hôte refuse toute tribu non jouée.
- **Lancement :** il attend la confirmation de chaque invité et une tribu jouée pour chacun. Chaque machine réapplique alors le fichier et joue sa tribu de lobby (`net_load_start`), avec `multiplayer_session` à 1.

**Vérifié :** deux instances, port 28778, dossiers temporaires. La sauvegarde vient de la fixture `badges` avec F8 (tribus 0 et 1 jouées) et est placée dans l'emplacement 0 de l'hôte.
- Après `L` et le clic sur l'emplacement 0, le choix des deux machines vaut `0b11`.
- L'invité joue la tribu 1, l'hôte la tribu 0. Après le lancement, les deux voient le bâtiment ajouté par F8 (`active_mask` 2), au même tour, sans désynchronisation.
- Même essai depuis une partie réseau en cours (port 28780) : Charger de l'hôte dans le panneau, emplacement 0. Les deux machines reviennent au lobby, qui propose les tribus 0 et 1 ; la partie relancée a la même empreinte sur les deux au tick 146, avec `active_mask` 2.

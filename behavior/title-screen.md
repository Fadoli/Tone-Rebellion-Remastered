# Démarrage et écran titre

Revue REA statique (FLOAT.EXE, sans exécution; ev_dd38b933…, ev_b39328dc…, ev_afe5c885…, ev_48031058…).

## Observations

- `FUN_0041c46f` (entrée de la boucle principale): si `DAT_004c2b98 != 0`, affiche `data\logo.gif` avec
  `data\logo.pal` (fondu de palette); enregistre les gestionnaires (`FUN_0046cbe0` ids 0,1,2,3,7,8),
  choisit l'état `FUN_0046c640(0,1)` si `DAT_004befe4 == 1`, sinon `(8,1)`; demande la piste `start`
  (`FUN_0045aba9`) avant la boucle de messages `FUN_0042ef17`.
- Titre (`FUN_004489c0`, message 1): palette `data\titscrn.pal`, piste `ambi1` en boucle
  (`FUN_0045b8d1`, `FUN_0045aafd`, indicateur `DAT_004a1470`); aucune animation par image. Les boutons
  viennent de `windows.txt` (état 0): RESUME frame 2 (262,269-377,332), NEWGAME frame 4 (99,337-240,399),
  LOADGAME frame 6 (402,337-540,399), EXITAPP frame 8 (255,407-375,469); RESUME → MASTER 2001,
  NEWGAME → WINMGR 5, LOADGAME → WINMGR 1 4, EXITAPP → WINMGR 2. Le gestionnaire du message `0x7d1`
  (RESUME) charge `resume_gam` si `DAT_004befe0 == 0`. La création du titre teste un en-tête de 0x80
  octets de reprise (`FUN_00457490`) avant d'afficher RESUME.
- `intro.avi` (chaîne `0x4a17d0`) est lue par `FUN_00449b80` (DirectShow: `RenderFile`, `Video Renderer`,
  `ShowCursor(0)`), appelée par la fenêtre `FUN_0044a0bb` au message 1; le message `0x32` suit la fin de
  lecture et fait avancer l'état (`FUN_0046c1b4(1, …)`). L'appelant de `FUN_0044a0bb` n'est pas tracé.

## Port et écarts

Concordent: pistes `start` et `ambi1`, art `TITSCRN`, positions et frames des boutons.
Absents du port: logo conditionnel, vidéo `intro.avi`, indicateur `DAT_004a1470`.
Possible écart non tranché: le port dessine RESUME sans sauvegarde valide (le clic est refusé par
`g_resume_available`), alors que le jeu teste l'en-tête de reprise à la création du titre; la lecture
de `FUN_0046c3bc(…, 2, …)` comme « cacher » n'est pas prouvée pour ces trois boutons, donc le rendu du
port n'a pas été modifié. Inconnues: cible des messages WINMGR 1, 2 et 5, image de survol natives,
raccourcis clavier, mode « attract » (aucun minuteur trouvé).

## Complément: machine d'états et démarrage (REA, ev_3cb8d6d4…, ev_f30649de…, ev_3fff1ad2…, ev_481eb776…)

Corrections: l'état 8 n'est pas l'intro. États de `windows.txt`: 0 = titre (`BACKGRND`, `TITSCRN`, RESUME,
NEWGAME, LOADGAME, EXITAPP), 1 = nouvelle partie, 2 = carte (`MAPBKG`, `WORLDVIEW`), 3 = île, 4/5 =
chargement (`LOADTMP`, `LOADSAVE`), 6 = `INTROMOVIE` (`intro.avi`), 7 = écran de victoire, 8 = fond du
titre seul. `FUN_0046c640(état, drapeau)` change d'état (message 1 = entrée, 2 = sortie); la file `WINMGR`
(`FUN_0046c1b4`, vidée par `FUN_0046b752` à chaque image) transporte: type 1 = changer d'état, 2 = quitter,
3 = revenir à l'état précédent, 4 = curseur/focus, 5 = commande (nouvelle partie). Boutons: NEWGAME
(message 5) lance la commande qui met l'état 1 en file, LOADGAME (1, 4) passe à l'état 4, EXITAPP (2)
quitte, RESUME (2001, MASTER) charge `resume_gam` ou passe à l'état 2.
Démarrage par défaut: `DAT_004befe4` vaut 1 sauf mode réseau (`FUN_0041c1d6`), donc `FUN_0046c640(0, 1)`:
titre directement; le logo n'apparaît que si `float.cfg` contient le mot `logo` (`FUN_0041d19d` met
`DAT_004c2b98 = 1`); aucun enregistrement n'envoie l'état 6: l'intro n'est pas sur le chemin par défaut
(entrée de l'état 6 non tracée). `DAT_004befe0` est un drapeau réseau, pas un drapeau de reprise.
Port: démarrage direct sur le titre (concorde). RESUME: `FUN_004489c0` envoie le message 2 à RESUME quand
l'en-tête de `resume_gam` est invalide; pour la classe de bouton générique (`FUN_004293c6`) le message 2
met `+0x3c` et `+0x38` à 0 et `FUN_0042a55d` ne dessine plus: le bouton est caché. Le port ne dessine donc
plus RESUME sans sauvegarde valide (`g_resume_available`). Reste: logo seulement avec `logo` dans la
configuration (non porté, désactivé par défaut), entrée de l'intro (état 6), classe du bouton RESUME non
vérifiée.

## Correction et logo de démarrage (REA, ev_987c0acd…, ev_0ccae20c…, ev_8521b214…, ev_b3bada15…, ev_8ffb51a6…)

Correction: le `FLOAT.CFG` installé (`C:\Program Files\Tone\FLOAT.CFG`, comme celui de `THING1`) contient le mot-clé `logo`
(avec `draw_method 2`, `frame_limit 20`, `sound_on`, `easyunlock`, `temphole`): le logo est donc affiché par défaut avec la
configuration fournie, contrairement à ma note précédente. `FUN_0041d19d` reconnaît (sans `intro`): `draw_method`,
`nevada`, `frame_limit`, `sound_on`, `net_name`, `quiet_click`, `no_template`, `network`, `alloc_test`, `gamma`, `logo`,
`partners`, `easyplot`, `easyunlock`, `hdmusic`, `temphole`, `holecolor`, `simplesound`, `blomster`, `multispeed`,
`island`, `medley`, `runback`.
Séquence (`FUN_0041c46f`): ouverture de `data\logo.gif` (GIF87a 640 x 480, 256 couleurs, LZW, image unique) et de
`data\logo.pal` (768 octets, valeurs 6 bits); palette mise à noir (`FUN_00410765`); décodage du GIF directement sur la
surface (rect 0,0 - 640 x 480, sans recentrage); fondu d'entrée de 65 pas de 4 (`palette * (256 - pas) >> 8`, de noir à la
palette); initialisation du reste du jeu (le « maintien » vaut le temps de cette initialisation); fondu de sortie de 65
pas; puis l'état titre (0, 1) et seulement ensuite la piste `start` (avant la boucle de messages). Aucun délai ni
lecture d'entrée dans la boucle: le logo n'est pas interruptible. L'intro (`intro.avi`, état 6) n'est atteinte que par
la commande de débogage 0x49 de `FUN_0046a5b7`, conditionnée par la clé `nevada` (absente du `FLOAT.CFG` fourni).
Port: écran `SCREEN_LOGO` si `FLOAT.CFG` contient `logo` (`logo_splash.inc`): décodeur GIF vérifié identique à PIL sur
`LOGO.GIF`, palette 6 bits convertie en 8 bits (sans le gamma natif non décodé), fondu d'entrée de 24 tics (~0,8 s), maintien
de 30 tics, fondu de sortie de 24 tics (cadence choisie par le port: l'original n'a pas de délai), entrées ignorées pendant
le logo, piste `start` lancée à la fin. Non porté: intro `intro.avi` (hors chemin par défaut), gamma de `FUN_00477599`.

## Options de `float.cfg` et valeurs par défaut (REA, ev_4be6368b…, ev_75778593…, ev_64e2e6f4…, ev_a917be91…)

Le `FLOAT.CFG` installé ne contient que `draw_method 2`, `frame_limit 20`, `logo`, `sound_on`, `easyunlock`, `temphole`.
Les valeurs initiales de `.data` comptent pour les clés absentes: `easyplot` (`DAT_0049c99c`), `quiet_click` (`DAT_0049c994`) et
`no_template` (`DAT_0049c998`) valent 1 par défaut et `FUN_0041d19d` les met à 0 seulement si le mot-clé est présent;
`DAT_0049c9b4` (draw_method) vaut 1 par défaut, `DAT_004c2b84` 0, `DAT_004c2ba0` (`easyunlock`) et `DAT_004c2bac` (`temphole`) 0.
Effets observés: `quiet_click` actif par défaut = le clic `button` joue (`FUN_004293c6`), comme dans le port; `sound_on` est remis à
0 par `FUN_0041d64e` quand la clé de registre ou la valeur `cdrom` manque (sauf `hdmusic`), et déclenche l'invite DXSOUND ou le
contrôle du CD (`FUN_0041c1d6`, `FUN_0041d8e1`); `easyplot` actif (valeur 1) tire au hasard (`FUN_00467260(count - 1)`) l'île dans
`FUN_004637fc` (initialisation du monde), le mot-clé la rend séquentielle (nom inversé, interprétation); `easyunlock` n'a qu'un lecteur
(`FUN_0042fa0f`, `0x430dc1`): une règle de candidat sur l'emplacement `DAT_005ec640 + site*0x60 + île*0x29e8` pour un monde précis
(effet exact inconnu, pas une porte d'accès d'île); `no_template` n'a pas de lecteur; `draw_method` est lu par `FUN_0042c0fa`
(table de modes non déterminée); les 19 lecteurs de `temphole` ne sont pas résolus.
Port: aucune de ces clés n'est lue (seul `logo`); le port code `quiet_click` actif, `temphole` actif, sans invite de son ni
contrôle du CD. À tracer: les lecteurs de `temphole`, la branche `easyunlock` de `FUN_0042fa0f` (par plage d'adresses) et le
tirage aléatoire de `FUN_004637fc` face à la génération des liens du monde du port.

### `easyunlock` et `easyplot` (REA, ev_1887a43e…, ev_255bb9b4…, ev_8999983f…)

`easyunlock` (actif dans le `FLOAT.CFG` installé): au clic de carte avec un objet armé (`FUN_0042fa0f`, message `0x40`, assembleur
`0x430dc1`), si `(objet - 6) >> 1` égale l'identifiant de l'île (champ `+0x29e0` de l'enregistrement d'île, la forme `6 + 2 * id + côté`
du code de paire), le site du paquet est réécrit: un site central de type 4 devient `site + 1`; un site de classe 3 dont `+0x4a` diffère du
côté `(objet - 6) & 1` devient `site - 1` (côté 0) ou `site + 1` (côté 1); pas de test de distance. C'est une aide au placement des
paires de la fonctionnalité d'île, pas une porte d'accès. Port: cette réécriture est appliquée au clic quand `FLOAT.CFG` contient
`easyunlock` (`window_interaction.inc`, avec `leviathan_marker_shape_id` pour l'identifiant d'île, supposé égal à `+0x29e0`; le contrôle
d'occupation natif sur le site cliqué avant la réécriture n'est pas reproduit).
`easyplot` (valeur 1 par défaut): `FUN_004637fc` place les sites de paire (codes `2 * id + côté`, `+ 6`) sur une île tirée au hasard parmi
`0..nombre-2` (jusqu'à trouver un site libre); le mot-clé les place dans l'ordre (paire k sur l'île k / 2); la dernière île n'en reçoit
pas. Les ponts viennent de `worldpos.txt` (listes explicites par taille de monde), pas du hasard. Port: le placement des sites de paire
suit le fichier de l'île, non ce tirage (écart non traité).

Précision `easyplot`: le cœur du port implémente déjà les deux règles (`randomize_class0_assignment` dans `game_session_layout.c`:
tirage de l'île par `tone_rng_bounded(count - 1)` ou ordre `ordinal / 2`, code d'objet `6 + 2 * forme + côté`), mais la plateforme fixait
l'ordre séquentiel. Comme `DAT_0049c99c` vaut 1 par défaut et que le `FLOAT.CFG` installé n'a pas le mot-clé `easyplot`, le jeu d'origine
tire les îles au hasard. Port: `load_game_session_for_selected_world` utilise maintenant le tirage aléatoire sauf si `FLOAT.CFG` contient
`easyplot`, avec repli sur l'ordre séquentiel si le tirage ne trouve pas assez d'emplacements libres (erreur du cœur). Non vérifié en jeu.

### `temphole` et `sound_on` (REA, ev_1d37a903…, ev_fc8b7b13…, ev_777da343…)

`temphole`: 17 lecteurs de dessin (listes d'icônes et de texte `islewin2.cpp`, construction `iwconstr.cpp`, Hall `iwhall.cpp`:
inventaire, diplomatie, commerce; `iwloc.cpp`; tâches `iwtask.cpp`; listes de débogage `iwdebug.cpp`) dessinent la forme `TEMPHOLE`
(mot `+0x1c`, frame `+0x1e`) quand l'option vaut 1, sinon remplissent le rectangle avec l'octet `holecolor` (`DAT_004c2b08`); la touche de
débogage `0x48` de `FUN_0046a5b7` la bascule (conditionnée par `nevada`). Le port utilise toujours `TEMPHOLE`: conforme au fichier installé.
`sound_on`: `FUN_0041d64e` remet l'option à 0 si, sans `hdmusic`, la clé `HKLM\Software\The Logic Factory\Tone Rebellion\111` ou sa valeur
`cdrom` manque. Avec 0, seules les recherches de son des effets `SOUND` (`FUN_004153b8`) et un appel par image (`0x45a3f1`, non analysé)
sont sautés, ainsi que l'invite DXSOUND et le contrôle du CD; la musique (`FUN_0045aba9`, `FUN_0045aafd`) ne lit pas l'option et son chemin
dépend de `hdmusic` (racine `data\` si actif, sinon `<cdrom>\thing2\`). Port: lecture inconditionnelle des sons et de la musique depuis
`THING2`, cohérente avec une installation où la clé `cdrom` existe. Non vérifié: valeur initiale de `DAT_004c2b80`, contenu de la racine
quand la valeur manque.

### Cadence de simulation native (REA, ev_1fb6c035…, ev_dcceac71…, ev_987c0acd…, ev_842c63eb…, ev_9a10d438…)

Observation: le compteur de ticks global `DAT_00618e44` n'est écrit que par `FUN_00413e8a` (`+0x1274` de l'objet à `0x617BD0`), appelée
dans la boucle principale `FUN_0041c46f` `DAT_004bf110 + DAT_004bf114` fois par image (`for (i = 0; i < …; ++i)`); en solo, pas
d'accumulateur de temps. Le limiteur de la boucle attend `QPC_fréquence / frame_limit` (`DAT_004c2b60`, 0 par défaut donc sans
limite si la clé manque; 20 dans le `FLOAT.CFG` installé: période d'image 50 ms), puis `DAT_004c2b64++`. Les touches `8`/`9` et
pavé numérique ± (`FUN_0046a5b7`, porte `DAT_004befe0 == 0` ou `multispeed`) bornent `DAT_004bf110` de 1 à 3 par `FUN_004140dd`
(`FUN_004133f2`, simple mise en file). `DAT_004bf114` n'est écrit qu'en réseau (`FUN_00413b68`).
Précision: `0x4bf100` est un tableau d'identifiants de joueurs (`DAT_004befe4` entrées, indice local `DAT_004befec`), `DAT_004bf110`
= élément 4, pas une table de vitesse; l'objet à `0x4bf128` n'a que des décalages positifs. Recherches complètes sans écrivain: octets
`10 F1 4B 00` (3 lectures), `00 F1 4B 00` (11 lectures), `B9 ?? ?? 4B 00`, `FUN_004121b7`, `FUN_00413675`. Restent non décodés ~40
accès `0x4bf0xx` (dont `FUN_0042fa0f`, `FUN_00419a6b`, `FUN_0045749a`, `FUN_004489c0`, `FUN_0044ec5d`, `FUN_0046ae19`).
Seconde passe: octets `04/08/0C F1 4B 00`, `F8/E0/D0/C0 F0 4B 00` 0 occurrence; `F0 F0 4B 00` 9 occurrences, toutes lectures ou copie
vers `0x5e1730` (indices < 4); les 5 fonctions « non décodées » n'ont aucune référence à `0x4bf0f0/100/110`. Apply du type 2 de
`FUN_004133f2` et `0x401d75` non décodés. Question close comme non résoluble statiquement sans ces deux corps.
RÉSOLU (3e passe, ev_8c1a4a9e…, asm 0x4126b1): `DAT_004bf110` = `GAMEENV(0x4befe0)+0x130`, écrit par `FUN_004121b7` cas 0xb
(valeur = charge utile; touches 8/9 envoient ±1 borné 1..3 par `FUN_004140dd`/`FUN_004133f2` type 2, consommé par `FUN_00413e8a`).
Valeur initiale posée aux cas 9 (début de partie, envoyé par `FUN_00448e5a` cas 0x34) et 0xc: 1, ou 2 si `DAT_004befe0 != 0`
(réseau). Solo: N = 1, soit 1 tick par image de 50 ms (20/s). Minuteur du port passé de 33 à 50 ms (logo en ticks réduits).


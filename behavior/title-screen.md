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


### `draw_method` et `multispeed` (REA, ev_2f74d0d0, ev_350fca36, ev_fbabbb86, ev_5c792cde, ev_e9e94c75)

Observation: `FUN_0041d19d` fixe `DAT_0049c9b4 = atoi(valeur)` (lu par `FUN_0041c1d6` seulement) puis `FUN_0042c608(mode)` choisit la
présentation: 0 VidFront, 1 VidBack, 2 SysToVidFront (blit mémoire système vers primaire, sans flip), 3 SysToVidBack, 4 Bitmap (GDI
`BitBlt` SRCCOPY depuis le DIB 8 bpp). Modes 0..3: DirectDraw plein écran exclusif 640x480x8; aucun redimensionnement, alpha, voile ni
transformation de couleur dans ces routines. Le `FLOAT.CFG` installé (`draw_method 2`) n'a donc aucun effet visible à reproduire au-delà
du plein écran 640x480 (le port fenêtré GDI correspond au mode 4). `multispeed` (`DAT_004c2bb4`) ne sert qu'à autoriser les touches de
vitesse en réseau; en solo elles sont toujours actives. `nevada` (`DAT_004c2b74`, ~67 lecteurs) garde des touches de débogage.
Inconnues: `DAT_004c2b6c`, `DAT_004c2bb8`, surface écrite par le moteur (système ou DIB).

`easyunlock` précisé (REA, `FUN_0042fa0f` cas 0x40, seul lecteur de `DAT_004c2ba0`, aucune écriture d'état): la vérification d'occupation porte sur le site cliqué avant réécriture; la réécriture
de colonne est faite si `(objet-6)/2 == B` de l'île: site `+0x10 == 4` -> colonne +1 et le site suivant devient le site testé; puis si ce site testé est de classe 3 et `+0x4a != (objet-6)&1`
colonne -1 (côté 0) ou +1 (côté 1). Le second test voit donc le site déjà décalé (décalage net +2 ou 0). Porté tel quel. Aucun écrivain de l'état 3 trouvé (recherche d'immédiats: 0 résultat).

**Correction écran de chargement (signalé par l'utilisateur, vérifié en jeu):** `loadsav0.shp` (`LOADSAVE`, états 4/5) était coloré avec `titscrn.pal` (couleurs fausses, bleu/violet); `titscrn.pal` ne correspond pas à cette planche. Le port la colore maintenant avec `data\game.pal` (cadre rouge et cyan identique à l'interface d'île, hypothèse d'après la couleur et l'absence de `loadsave.pal`). Non établi par REA: la palette que charge le gestionnaire d'état 4/5 (à vérifier), le rôle du bloc 480×160 en haut à gauche du cadre 0 (zone d'aperçu supposée) et le texte des emplacements (non porté).

## Écran Charger / Sauvegarder (REA, ev_94820aeb…, ev_b63492db…, ev_0db3da95…, ev_d05a39a8…, ev_239c2c8d…, ev_9dfe71a3…)
Observation: les états 4 et 5 ne sont pas enregistrés par `FUN_0041c46f`; ils sont atteints par une requête `FUN_0046c1b4(4, 1, 0)` et on en sort par `FUN_0046c1b4(3, 0, 0)`. `FUN_00458162` (message de la fenêtre `LoadSaveWindow`, type 14, ctor `FUN_004580fc`) charge **`data\game.pal`** au message 1 (palette confirmée) puis scanne `00.sav`..`07.sav` (`FUN_00458371`: attributs, date du fichier, en-tête de 0x80 octets valide si `"1.16"` et dword `+0x7c == 0x378b8`). Paint `FUN_0045858a`: `LOADTMP` cadre 0 = gabarit 640×480; huit cellules = cadres 1..8 de `LOADSAV0.SHP` (300×99) à x = 13 / 326 et y = 36 + 111·ligne (slot = ligne + 4·colonne); slot valide: date (`ctime`) à (2,2), `SURPFLOW %d` (en-tête `+0x68`) à (0x69, 0x0e), `POPSTR %d` (`+0x6c`) à (0xe8, 0x28), `WORKSTR` (`+0x70`) à (0xe8, 0x32), icônes de tone et dessin d'aperçu 210×90 (hors port); titre `LSTITLE` à (317, 0), cadre `clamp(tribu, 0..7)` (+4 en mode chargement, `DAT_0062d172 == 4`). Clic (message 6): `y < 35` retour; sinon slot = `(y−28)/112 + 4·(x/320)`; chargement si l'en-tête est valide (`FUN_004576c7`), sauvegarde sinon au mode 5 (`FUN_0045749a`), puis retour à l'état 3; Échap/message 7 = retour.
Correction du port: `loadsav0.shp` est coloriée par `game.pal` (au lieu de `titscrn.pal`); l'ancien rendu superposait le cadre 1 (une cellule 300×99) plein écran à l'origine. **Port:** huit cellules, dates, résumé d'en-tête (surplus, population, ouvriers) et titre; vérifié en jeu avec les huit sauvegardes d'origine présentes. Non porté: icônes de tone, aperçu 210×90, cadre `ENDGAME` par niveau (palette `endgame.pal` à confirmer), pourcentage `WORKSTR`, le mode Sauvegarde (état 5) et le chargement d'une sauvegarde d'origine (sérialisation des quatre flux `FUN_00412d0a/467be5/418a17/46ea1c`). Le répertoire des sauvegardes est le répertoire courant du processus natif (relatif); le port lit `C:\Program Files\Tone`.

**Emblème de niveau (port, vérifié en jeu):** chaque cellule valide dessine `ENDGAME` cadre `clamp(en-tête+0x78, 0..4)` en (−6, −6), colorié avec `game.pal` (palette active native supposée); les huit sauvegardes d'origine montrent des tailles différentes (58×58 à 108×106), donc des niveaux différents. Le titre `LSTITLE` utilise le cadre `4 + tribu` en mode Chargement. Conséquence pour le score de fin (`behavior/end-game.md`): `DAT_004bf11c` (niveau L du score) et `DAT_004bf118` sont ceux que `FUN_0045749a`/`FUN_004576c7` écrivent/relisent dans l'en-tête (`+0x78`, `+0x74`): leur valeur vient donc du chargement d'une sauvegarde (aucun écrivain par adresse directe), et vaut 0 pour une nouvelle partie du remake.

**Port (suite, vérifié en jeu):** pseudocode relu (`functions/0016_batch_0012/details-02-03.md`, `ev_2b0b2608…`): le rectangle de découpe commence à la cellule (x 13/326, y 36 + 111·ligne) et toutes les positions lui sont relatives. Portés: icône `bildtone` cadre 24 à (141, 40), `tonecrys` et `magctone` cadre 4 à (141, 70) et (141, 97), valeurs (shorts d'en-tête `+0x30/+0x32/+0x34`) à x 153, y 34/63/90, et `WORKSTR` « %s %d (%d%%) » (pourcentage = ouvriers·100/population, tronqué; le natif divise en virgule flottante, valeurs affichées 67–80 % sur les huit sauvegardes). Non porté: l'aperçu `FUN_0040bf98` de l'enregistrement de site (en-tête `+0x08`) à (210, 90) et le sprite de floater de la tribu (`FUN_0042704b`, enregistrement `+0x14`) à (250, 17, ou 14 pour la tribu 3), échelle 1,0.

**Port (sprite de floater):** chaque cellule valide dessine le floater de la tribu (enregistrement `+0x14` = en-tête `+0x1c`, quatre tribus) à (250, 17) (14 pour la tribu 3) avec les feuilles de corps et de jambes (`pbod/plegs`, `sbod/slegs`, `mbod/mlegs`, `lbod/llegs`) coloriées avec `game.pal`, cadre 0 des deux (pose au repos approximée). Vérifié en jeu: floaters de couleurs différentes selon la tribu de chaque sauvegarde. Non porté: l'aperçu de site `FUN_0040bf98` à (210, 90), le mode Sauvegarde (état 5) et la désérialisation pour charger une sauvegarde d'origine.

## Sauvegarde et chargement du remake (demande utilisateur, vérifié en jeu)
Le format natif (`FUN_0045749a`/`FUN_004576c7`: en-tête de 0x80 octets puis quatre sérialisations du moteur) n'est pas reproduit; le remake écrit son propre format dans un dossier `saves` à côté de l'exécutable (le dossier du jeu d'origine n'est jamais écrit, `AGENTS.md`): en-tête de 0x80 octets de même disposition que le natif (`"1.16F"`, tribu `+0x1c`, stocks `+0x30/0x32/0x34`, surplus `+0x68`, population `+0x6c`, ouvriers `+0x70`, clé `0x378b8` `+0x7c`) suivi d'un corps `TRRM` (version 1, taille de `GameSession`, monde, difficulté, tribu, île, vitesse, ticks) puis de la `GameSession` brute (314 ko, sans pointeurs). L'écran Charger/Sauvegarder (état 4/5) affiche les sauvegardes du remake (`00.sav`..`07.sav`) et, pour un emplacement sans sauvegarde du remake, la sauvegarde d'origine du même numéro (listée, non chargeable: message explicite). Clic (même géométrie que `FUN_00458162`): mode Sauvegarde = écrit l'emplacement puis revient à l'écran d'origine; mode Chargement = restaure la partie (île si elle était ouverte, sinon carte du monde). `F5` (raccourci du port, point d'entrée natif non établi) ouvre l'écran Sauvegarder depuis la carte ou l'île; `Échap` revient. À la fermeture de la fenêtre pendant une partie, `saves\resume.gam` est écrit et le bouton REPRENDRE (visible si ce fichier est valide) le recharge. Vérifié: sauvegarde 00 depuis l'île, écran Charger montrant le nouvel emplacement (date, surplus, pop, ouvriers, tribu) puis restauration sur l'île depuis le titre. Non vérifié: reprise automatique à la fermeture, sauvegardes sur la carte du monde, restauration de l'état du Hall panel et de la musique (réinitialisée).

## Points d'entrée natifs de Sauvegarder/Charger (REA, ev_7bf6d43f…, ev_21a7e71a…, ev_47ed5e28…, ev_34bb1bdc…, ev_bed05c4d…)
Observation: `FUN_004578df` (fenêtre à machine à phases 0x88 et minuterie, probablement `SHADE`, `WINTYPE 13`, `OPENPANE 0 0 639 99`, états 2 et 3 de `windows.txt`: le panneau d'options qui descend du haut de la carte et de l'île) envoie `SetState(5)` (Sauvegarder) ou `SetState(4)` (Charger) au clic (message 6, `DAT_004befe0 == 0`); zones de la table `DAT_004a33f0`: idx 0 = (102,40)–(197,91) Sauvegarder, idx 1 = (93,8)–(200,50) Charger (recouvrement: l'indice le plus bas gagne), idx 2..5 = réglages; un clic à y = 0 ou y > 97 referme le panneau. Le bouton `LOADGAME` du titre (`1 4 0` vers `WINMGR`) mène aussi à l'état 4. Touches de débogage (portée `DAT_004c2b74`, solo): `S` écrit `quick.sav` (`FUN_0045749a`), `R` le relit (`FUN_004576c7`), `1..4` changent d'état. `DAT_0062d172` n'a aucun écrivain trouvé (lectures seulement).
Conséquence: le port n'a pas le panneau d'options coulissant (`SHADE`: réglages, Sauvegarder, Charger) qui est le point d'entrée natif du mode Sauvegarde; `F5` en tient lieu. **Non porté:** ce panneau (géométrie, réglages idx 2..5 et animation d'ouverture non tracés).

## Panneau d'options coulissant `SlideWindow` / `SHADE` (REA, ev_cc0af90d…, ev_77000b26…, ev_47ed5e28…, ev_f7c159bf…, ev_6e79da7c…, ev_82cf0300…)
Observation: classe `SlideWindow` (`WINTYPE 13`, ctor `FUN_004578b7`, vtable `0x4946f8`, message `FUN_004578df`, **paint `0x457f15`** non enregistré par Ghidra, désassemblé linéairement: plage `0x457f15–0x4580f9`). Phases 0 fermé, 1 ouverture, 2 ouvert, 3 fermeture; hauteur 99 px; minuterie 50 ms: ouverture par pas de 15 px (ralentie dans les 50 derniers px: `rem·15/50 + 1`), fermeture 15 px par tick. Ouverture au clic sur la rangée du haut (pane 0 0 639 0), fermeture au clic à y = 0 ou y > 97. Table `DAT_004a33f0` (premier rectangle gagnant): 0 Sauvegarder (102,40)–(197,91) → `SetState(5)`, 1 Charger (93,8)–(200,50) → `SetState(4)`, 2 pause (285,1)–(359,56) (bascule `DAT_004bf124`, interprété comme pause: la boucle principale ne tourne que s'il est nul), 3 (271,45)–(339,100) écrit `resume.gam` puis `SetState(0)`, 4 musique (394,3)–(452,51), 5 son (401,47)–(447,96); curseurs: x ∈ [450, 580], valeur = clamp(x − 456, 0, 100), musique pour y ∈ [11, 31], son pour y ∈ [57, 77] (`FUN_004595cc`: atténuation logarithmique). Dessin (`SLIDWIN0.SHP`, 11 cadres; décalage d = pos − 99): cadre 0 (640×100) en (0, d); cadre 7 en (292, d+6) si pause; musique: cadre 8 en (414, d+7) si coupée, sinon curseur cadre 10 en (456 + volume, d+13); son: cadre 9 en (415, d+63) si coupé, sinon cadre 10 en (456 + volume, d+59); survol: cadre (index + 1) à (xmin, ymin + d). Aucun texte dans le paint.
**Port (`slide_panel.inc`, vérifié en jeu):** panneau coloré avec `game.pal` (même planche que l'écran Charger), animation, six zones, pause (le jeu s'arrête et le cadre 7 s'affiche), musique et son (désactivation + volume MCI `setaudio` pour la musique; le son est coupé quand désactivé ou volume 0, sans atténuation fine: `PlaySound` n'a pas de volume), Sauvegarder (écran état 5, `F5` conservé), Charger (état 4, retour au jeu à `Échap`), Quitter (écrit `saves\resume.gam` puis le titre; « Reprendre partie » le recharge). Écarts: volumes initiaux (100) supposés; pas de glisser sur les curseurs (le natif ne traite que la pression); l'ouverture se fait aussi sur la carte du monde.

**Vérifications complémentaires en jeu (sauvegarde/reprise):** `F5` depuis la carte du monde puis clic sur l'emplacement 5 écrit `saves\05.sav` (314 296 octets); la fermeture de la fenêtre (`CloseMainWindow`) écrit `saves\resume.gam`; après redémarrage, « Reprendre partie » (visible grâce à ce fichier) restaure la carte du monde. Reste non vérifié: reprise depuis une île ouverte après fermeture, sons coupés pendant la lecture d'un effet, volume initial natif.

**Port (aperçu de site, vérifié en jeu):** `FUN_0040bf98(rect, enregistrement en-tête+0x08, 0xd2, 0x5a, 1, 0x10000, -1)` dessine le site enregistré (ici le Hall) en (210, 90) dans la cellule, ancré par le bas. Le remake écrit l'identifiant d'objet du Hall dans l'en-tête (`+0x18`, propriétaire `+0x1c`) et dessine l'objet à échelle 1,0 sans la rampe de placement (drapeau `0x010`, qui ne s'applique qu'à cette échelle et décalait l'image) avec découpe à la cellule. Le dessin n'apparaît que lorsque l'image du bâtiment est chargée (une partie est en cours); depuis le titre, sans partie lancée, la cellule reste sans aperçu. Les sauvegardes d'origine n'ont pas d'aperçu (enregistrement natif non décodé).

**Port (curseurs de volume, demande utilisateur, vérifié en jeu):** la courbe est celle de `FUN_004595cc` (ev_aad84961…): atténuation en centièmes de dB = `ftol(1000 · log2(v / 100))`, bornée à [−10 000, 0], `v = 0` = silence. Musique: gain d'amplitude `10^(atténuation/2000)` appliqué au niveau MCI (`setaudio tone_music volume to 0..1000`) à chaque réglage et à chaque nouveau morceau. Effets: `PlaySound` n'a pas de volume, donc les effets WAV en mémoire sont copiés et leurs échantillons PCM (8 ou 16 bits) multipliés par le même gain avant lecture (anneau de huit tampons; volume 0 ou son coupé = pas de lecture; volume 100 = lecture directe). Le curseur suit le glisser (appui sur la bande du curseur puis déplacement, capture de la souris, valeur = x − 456 bornée à 0..100); le natif ne traite que la pression, le glisser est un choix du port. Les bascules et volumes sont enregistrés dans `saves\audio.cfg` (choix du port) et relus au démarrage. Vérifié: glisser du curseur musique jusqu'à x = 480 (valeur 24) et du curseur effets jusqu'à x = 470 (valeur 14): les curseurs se déplacent et `audio.cfg` contient `1 24 1 14`. Non mesuré: le niveau sonore réel (aucune capture audio); le volume initial natif (100 supposé).

**Correction volume de la musique (signalé par l'utilisateur, confirmé « ça marche »):** MCI `waveaudio` ne reconnaît pas `setaudio volume` (erreur 261, mesuré avec un programme d'essai sur `ACT1.WAV`), donc le volume de la musique n'avait aucun effet; la musique est maintenant ouverte en `mpegvideo` (DirectShow, `setaudio … volume to 0..1000` accepté, `status … volume` rend 1000) et rejouée en boucle par `play tone_music from 0`. Les effets, eux, étaient déjà mis à l'échelle en mémoire (essai hors ligne: crête 41 → 12 → 1 pour les volumes 100/50/14). Rappel: la musique n'est trouvée que si `TONE_REBELLION_THING2` désigne le dossier `THING2` (ou s'il est voisin de l'exécutable).

**Couleur par tribu (signalé par l'utilisateur, vérifié en jeu):** `FUN_0044964f` formate `slidwin%d.shp`, `loadsav%d.shp`, `isletmp%d.shp`, `mainbut%d.shp`, `thall%d.shp`, `temphol%d.shp`, `scarrow%d.shp` avec le joueur actif (`DAT_0049f538`; `-1` = joueur courant): chaque tribu a ses propres planches colorées (`SLIDWIN0..3.SHP`, `LOADSAV0..3.SHP` existent). Le port chargeait toujours `slidwin0`/`loadsav0` (rouge). Il charge maintenant les planches de la tribu sélectionnée (`g_menu.selected_tribe`), rechargées au changement de tribu: panneau d'options coulissant et écran Charger/Sauvegarder passent de rouge (tribu 0) à bleu pour une autre tribu. Les cadres du bas de l'île suivaient déjà la tribu (`isletmp%d` etc.). Vérifié en jeu pour les quatre tribus (or, rouge, bleu, vert, chacune assortie à l'interface d'île); `LSTITLE` et `ENDGAME` n'existent qu'en un exemplaire.

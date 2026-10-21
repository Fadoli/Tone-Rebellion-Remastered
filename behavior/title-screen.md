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

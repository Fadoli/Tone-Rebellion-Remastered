# Application, menus et donnees

## Pilotage du jeu

| Adresse / fonction Ghidra | Rôle étayé et observations | Pseudocode |
|---|---|---|
| `0x478460` `entry` | **Interprétation :** amorçage runtime C. Prépare le processus, appelle `GetStartupInfoA`, `GetModuleHandleA`, `GetCommandLineA`, puis une thunk ciblant `0x41d8e1`. | [entry/runtime](../../functions/0001_entry_runtime.md) |
| `0x41d8e1` `FUN_0041d8e1` | Démarrage applicatif. Journalise `1.16F`, traite la ligne de commande et référence `gamey.txt`, `newtext.txt`, `bldtxt.txt`, `bldname.txt`, `plotobj.txt`, `tonehelp.txt`, `names.txt`; appelle initialisation fenêtre et boucle. | [application main](../../functions/0002_application_main.md) |
| `0x41c1d6` `FUN_0041c1d6` | Enregistre `Float Class`, crée `Tonus Rebellious`, interroge la fréquence timer; référence le chemin conditionnel `sound.txt`/`DXSOUND`. | [window init](../../functions/0003_window_init.md) |
| `0x41c46f` `FUN_0041c46f` | Initialise ressources puis boucle principale; référence logo, `windows.txt`, `effects.txt`, `fltinf.txt`, `bldinf.txt`, pompe de messages, update, présentation et fermeture. | [main loop](../../functions/0004_main_loop.md) |
| `0x46cd22` `FUN_0046cd22` | Lit `windows.txt` et crée/enregistre des fenêtres et outils (`GameWindow`, `WorldWindow`, `LoadSaveWindow`, `IWTasks`, `IWTrade`, etc.); référence `shapes.txt`, `data\\bgoutfnt.fnt`. | [window manager init](../../functions/0018_batch_0014.md#fun_0046cd22--0x46cd22) |
| `0x42ef17` `FUN_0042ef17` | Pompe les messages Win32, distingue `WM_QUIT`, clavier et événements envoyés à la file interne. | [message dispatch](../../functions/0012_batch_0008.md#fun_0042ef17--0x42ef17) |
| `0x42eba0` `FUN_0042eba0` | Ajoute souris/clavier à une file interne bornée à huit éléments. | [input queue](../../functions/0012_batch_0008.md#fun_0042eba0--0x42eba0) |
| `0x469f56` `FUN_00469f56` | Retire et distribue les événements aux fenêtres/objets; certains destinataires passent par dispatch indirect. | [window events](../../functions/0018_batch_0014.md#fun_00469f56--0x469f56) |
| `0x466ce2` `FUN_00466ce2` | Parcourt collections d’objets et temporisateurs au cours d’une mise à jour; plusieurs champs restent sémantiquement inconnus. | [update](../../functions/0017_batch_0013.md#fun_00466ce2--0x466ce2) |
| `0x41e569` `FUN_0041e569` | Tick d’un floater, appelé par `FUN_00466ce2` pour chaque entrée active. L’état `0x0e` décrémente son minuteur seulement après l’arrivée exacte signalée par `FUN_00422d27`. Les états `0x0f`/`0x10` comparent la distance de Chebyshev à un rayon de 10 par défaut; une portée d’attaque non nulle renvoyée par `FUN_00420721` le remplace, sauf pour l’ordre `0x14` qui force le rayon à zéro. | [floater update](../../functions/0010_batch_0006.md#fun_0041e569--0x41e569) |
| `0x422d27` `FUN_00422d27` | Calcule un pas vers la destination d’un floater, borne séparément les deltas x/y, réduit la vitesse près de la cible et utilise le bit bas du tick si le pas réduit devient nul. Les choix de destination, vitesse effective et collisions sont calculés/filtrés ailleurs. | [movement step](../../functions/0010_batch_0006.md#fun_00422d27--0x422d27) |
| `0x435581` `FUN_00435581` | Hit-test d’île : ajoute le décalage horizontal monde à x, parcourt la liste active de floaters et accepte une distance de Chebyshev strictement inférieure à `0x14` (20); sinon teste les locations avec des largeurs/états variables. | [island hit tests](../../functions/0012_batch_0008.md#fun_00435581--0x435581) |
| `0x435826` `FUN_00435826` | Gestionnaire de sélection appelé pour les clics gauche/droit (messages 6/7 dans `FUN_004337d9`). Appelle le hit-test séparément pour les locations et floaters; émet `0x3f` pour un floater, `0x32` pour une location et traite des actions contextuelles selon boutons/état. L’interprétation complète des commandes résultantes et du déplacement reste partielle. | [island click selection](../../functions/0012_batch_0008.md#fun_00435826--0x435826) |
| `0x43530b` `FUN_0043530b` | Traduit les modes d'interaction en états UI. `0x13` active le bit `+0x178 & 4` qui autorise ensuite le clic de destination `0x4c`; `0x10`/`0x12` activent le bit 2 avec les curseurs 3/5, et `0x11` le bit 1 avec le curseur 0xd ou 0xb. Cela identifie le mode de commande qui précède le déplacement, mais pas les unités autorisées; le garde de classe reste à établir. Evidence REA `ev_5e3fc63f4718af2e8a051c86de5109504655264091ec1257449307a1b02b0952`. |
| `0x420991` `FUN_00420991` | Filtre un candidat à une tâche autonome selon son identité, ses flags, sa classe et, pour l'objet de classe 4, un seuil de niveau. Il ne suffit pas à identifier les classes numériques soldat/mage ni le garde d'une commande directe; la table `DAT_00619290` reste à suivre jusqu'à son initialisation. Evidence `ev_b758701979d34e447f00b2067f67d58c0c58d9b8c28b444e24dfd4a160713da5`. |
| `0x42cc24` `FUN_0042cc24` | Présente l’image par appels de rendu indirects et GDI (`GetDC`, `ReleaseDC`, `BitBlt`); chemins d’erreur de flip/blit visibles. | [presentation](../../functions/0011_batch_0007.md#fun_0042cc24--0x42cc24) |
| `0x41bdae` `FUN_0041bdae` | Callback Win32 : fermeture et activation/désactivation; délègue les autres messages à `DefWindowProcA`. | [window procedure](../../functions/0010_batch_0006.md#fun_0041bdae--0x41bdae) |
| `0x41cf86` `FUN_0041cf86` | Demande la fermeture : journalise `Posting Quit Message`, appelle `PostQuitMessage`, modifie un état global. | [quit request](../../functions/0010_batch_0006.md#fun_0041cf86--0x41cf86) |

---

# Application, menus et donnees

## Son et musique

| Adresse / fonction Ghidra | Rôle étayé et observations | Pseudocode |
|---|---|---|
| `0x459e84` `FUN_00459e84` | Initialise DirectSound et les buffers de musique et d’effets. Charge `data\\format.wav` et `data\\fxformat.wav` comme formats, puis crée un buffer de musique et un buffer par effet. | [DirectSound init](../../functions/0016_batch_0012.md#fun_00459e84--0x459e84) |
| `0x41c46f` `FUN_0041c46f` | À l'initialisation de la boucle principale, demande `start` une fois (`FUN_0045aba9("start",0,0)`), puis prépare un `act1` ou `act2` choisi par le LCG. Le gestionnaire titre demande séparément `ambi1`. | Evidence REA `ev_0d3b5c438336d08cdbf8ba34c9184bb675cb602578f322bf0196680746a282f0` |
| `0x4293c6` `FUN_004293c6` | Pour les clics de contrôle (cas 6/7), demande `button` via `FUN_0045b20c` si le flag de son `DAT_0049c994` est activé. | Evidence REA `ev_72f39fb60094b2431b9019ac015228fb1081f7d6650bc3eaca66812a4c2dfb74` |
| `0x416a9a` `FUN_00416a9a` | Transforme les événements monde en instances d'effet : 2 choisit `fltbuild`/`levbuild` selon le type d'entité, 3 choisit `bridge`. L'activation d'un pont observée dans `FUN_004669bd` appelle le cas 3. Les noms sont passés au système d'effets; cela établit le déclencheur logique, pas une capture runtime de lecture audio. | Evidence REA `ev_7bb81f291a259a90f39323a69a51aca642dbb8d1163a9c7ef8c3299fab5a5344` |
| `0x45aafd` `FUN_0045aafd` | Enregistre le nom de piste et deux paramètres sur l’objet sonore, puis demande le démarrage via `FUN_0045b8ac` selon son quatrième argument. | [tune request](../../functions/0016_batch_0012.md#fun_0045aafd--0x45aafd) |
| `0x4489c0` `FUN_004489c0` | Pour la commande de l’écran titre, demande la piste `ambi1`; cette piste est déclarée dans `sound.txt` comme `ambient1.wav`. | [title and menu](../../functions/0014_batch_0010.md#fun_004489c0--0x4489c0) |
| `0x4576c7` `FUN_004576c7` | Après chargement d’une sauvegarde, construit `tribe%d` depuis l’index de tribu et demande cette piste si elle n’est pas déjà active. | [load-game music](../../functions/0016_batch_0012.md#fun_004576c7--0x4576c7) |
| `0x4702d9` `FUN_004702d9` | Le gestionnaire WORLDWIN charge/initialise les formes des îles puis met à `1` les 15 flags `DAT_00632370[0..14]` qui autorisent le premier changement musical de chaque realm. | Evidence REA `ev_4c1dd2d0f68629c299d1f971bce9fe5b0e14df00a073635622fce0482d43f0b3` |
| `0x470fe7` `FUN_00470fe7` | À la première entrée permise dans un realm, demande `levi` pour ID 14, `tribe%d` si l'ID égale la tribu, `act%d` pour les autres IDs 0–3, sinon appelle la sélection aléatoire; consomme ensuite le flag de ce realm. | Evidence REA `ev_c8c3fa40d02cbbb84756413780634e899191374ea15d52a888ba5ea5c044f084` |
| `0x46ff6f` `FUN_0046ff6f` | Sélectionne une entrée parmi la piste de tribu deux fois, l'acte de la tribu, `act1`–`act4`, `ambi1` et `ambi2`; en mode solo, retire le dernier index choisi du prochain tirage. | Evidence REA `ev_940528e0543fcfbd809a77f2700e26661dd502963e607f4873bc6666a4c1716d` |
| `0x45b8d1` `FUN_0045b8d1` | Compare le nom demandé à l’index de piste active, sans sensibilité à la casse. | [active-tune check](../../functions/0016_batch_0012.md#fun_0045b8d1--0x45b8d1) |

Les noms d'effets et de pistes sont observés dans le code et `sound.txt`. Les 16 entrées `tune` correspondent toutes aux WAV de `C:\toneIso\THING2`, y compris l'inversion des noms d'acte (`act1` → `act4.wav`, ..., `act4` → `act1.wav`). Les effets WAV comme `button`, `fltbuild`, `levbuild` et `bridge` sont déclarés dans `sound.txt`; les effets concernés sont membres de `TONE01.COB`. Le remake joue `start` une fois au lancement, `ambi1` dans les menus/cartes, puis applique les transitions de realm de `FUN_00470fe7` une fois par realm, y compris les pistes `act`, `levi` et la liste aléatoire. Il joue `button` au clic. Les effets de construction ne sont pas joués : l'original émet `fltbuild`/`levbuild` après validation de l'objet par une voie différée, encore incomplète dans le remake. `FUN_004669bd` déclenche le type d'effet `bridge` via `FUN_00416a9a(3, ...)` lors de l'activation d'un lien; ce déclencheur n'est pas encore raccordé au remake.

---

# Application, menus et donnees

## Écran « nouvelle partie » et texte cintré

| Adresse / fonction Ghidra | Rôle étayé et observations | Pseudocode |
|---|---|---|
| `0x44e77f` `FUN_0044e77f` | Charge les blocs descriptifs de `newgame.txt` : lit jusqu’à `ENDTEXT`, concatène les lignes et mémorise leurs offsets; limites visibles : huit blocs, 4096 octets. | [text loader](../../functions/0015_batch_0011.md#fun_0044e77f--0x44e77f) |
| `0x44e9c7` `FUN_0044e9c7` | Gestionnaire d’état/événement de la fenêtre New Game; charge les textes et transforme hit-tests en commandes/états. | [New Game handler](../../functions/0015_batch_0011.md#fun_0044e9c7--0x44e9c7) |
| `0x44e4f8` `FUN_0044e4f8` | Hit-test des quatre emblèmes (`0..3`) et de deux zones autour de `(320,240)`; sinon renvoie `-1`. | [hit test](../../functions/0015_batch_0011.md#fun_0044e4f8--0x44e4f8) |
| `0x44ebea` `FUN_0044ebea` | Convertit `0..3` en une commande indexée, et `4`/`5` en deux autres commandes. | [input mapping](../../functions/0015_batch_0011.md#fun_0044ebea--0x44ebea) |
| `0x44ec5d` `FUN_0044ec5d` | Dessine le menu; références `EXITNEWGAME`, `WORLDSIZE`, `TRIBE0..3`, `DIFFICULTY`, `BEGINGAME` et ressources `newback`, `glyphs`, `levidiff`, `ngrealms`, `bigfloat`; dessine les descriptions. | [New Game paint](../../functions/0015_batch_0011.md#fun_0044ec5d--0x44ec5d) |
| `0x44e613` `FUN_0044e613` | Callback de géométrie des lignes : avance `y` de `3 + hauteur_police`, calcule un bord via `40000-(y-240)^2`, choisit les limites gauche/droite. Assertion visible `ABS(lasty-240)<=NEWGAMERADIUS`. | [curved line callback](../../functions/0015_batch_0011.md#fun_0044e613--0x44e613) |
| `0x428baa` `FUN_00428baa` | Enveloppe les mots selon la largeur retournée par le callback et justifie les espaces pour remplir la ligne. | [wrap and justify](../../functions/0011_batch_0007.md#fun_00428baa--0x428baa) |
| `0x4289a7` `FUN_004289a7` | Helper de mesure/layout utilisé avant le placement; wrapper vers un appel indirect. L’ancrage vertical complet reste indéterminé. | [text layout helper](../../functions/0011_batch_0007.md#fun_004289a7--0x4289a7) |
| `0x448e5a` `FUN_00448e5a` | Initialisation/interactions de la fenêtre New Game; référence `data\\newgame.hzt` et appelle le hit-test. | [New Game setup](../../functions/0014_batch_0010.md#fun_00448e5a--0x448e5a) |

**Conséquence pour le remake :** le cintrage du texte est étayé par `0x44e613` et son utilisation par le justificateur `0x428baa`. L’ancrage vertical choisi côté remake reste approximatif, voir `../ToneRebellion_Remake/GRAPHICS_RECONSTRUCTION.md`.

# Carte des fonctions d’origine — rôles observés dans Ghidra

Index de lecture des pseudocodes : adresse dans `FLOAT.EXE`, rôle déduit du corps analysé, observations qui motivent ce rôle et dossier contenant le pseudocode complet.

## Comment lire les rôles

- **Observé** décrit les opérations visibles dans Ghidra : appels, chaînes, conditions, données lues/écrites.
- **Interprétation** nomme le comportement probable, pas un nom source retrouvé.
- Les noms `FUN_...` sont automatiques. Aucun `Float.pdb` n’étant disponible, les signatures et types reconstruits ne sont pas garantis d’être ceux du source.
- Adresses virtuelles avec base d’image `0x400000`. Evidence IDs et limites sont dans chaque page source.

## Pilotage du jeu

| Adresse / fonction Ghidra | Rôle étayé et observations | Pseudocode |
|---|---|---|
| `0x478460` `entry` | **Interprétation :** amorçage runtime C. Prépare le processus, appelle `GetStartupInfoA`, `GetModuleHandleA`, `GetCommandLineA`, puis une thunk ciblant `0x41d8e1`. | [entry/runtime](functions/0001_entry_runtime.md) |
| `0x41d8e1` `FUN_0041d8e1` | Démarrage applicatif. Journalise `1.16F`, traite la ligne de commande et référence `gamey.txt`, `newtext.txt`, `bldtxt.txt`, `bldname.txt`, `plotobj.txt`, `tonehelp.txt`, `names.txt`; appelle initialisation fenêtre et boucle. | [application main](functions/0002_application_main.md) |
| `0x41c1d6` `FUN_0041c1d6` | Enregistre `Float Class`, crée `Tonus Rebellious`, interroge la fréquence timer; référence le chemin conditionnel `sound.txt`/`DXSOUND`. | [window init](functions/0003_window_init.md) |
| `0x41c46f` `FUN_0041c46f` | Initialise ressources puis boucle principale; référence logo, `windows.txt`, `effects.txt`, `fltinf.txt`, `bldinf.txt`, pompe de messages, update, présentation et fermeture. | [main loop](functions/0004_main_loop.md) |
| `0x46cd22` `FUN_0046cd22` | Lit `windows.txt` et crée/enregistre des fenêtres et outils (`GameWindow`, `WorldWindow`, `LoadSaveWindow`, `IWTasks`, `IWTrade`, etc.); référence `shapes.txt`, `data\\bgoutfnt.fnt`. | [window manager init](functions/0018_batch_0014.md#fun_0046cd22--0x46cd22) |
| `0x42ef17` `FUN_0042ef17` | Pompe les messages Win32, distingue `WM_QUIT`, clavier et événements envoyés à la file interne. | [message dispatch](functions/0012_batch_0008.md#fun_0042ef17--0x42ef17) |
| `0x42eba0` `FUN_0042eba0` | Ajoute souris/clavier à une file interne bornée à huit éléments. | [input queue](functions/0012_batch_0008.md#fun_0042eba0--0x42eba0) |
| `0x469f56` `FUN_00469f56` | Retire et distribue les événements aux fenêtres/objets; certains destinataires passent par dispatch indirect. | [window events](functions/0018_batch_0014.md#fun_00469f56--0x469f56) |
| `0x466ce2` `FUN_00466ce2` | Parcourt collections d’objets et temporisateurs au cours d’une mise à jour; plusieurs champs restent sémantiquement inconnus. | [update](functions/0017_batch_0013.md#fun_00466ce2--0x466ce2) |
| `0x42cc24` `FUN_0042cc24` | Présente l’image par appels de rendu indirects et GDI (`GetDC`, `ReleaseDC`, `BitBlt`); chemins d’erreur de flip/blit visibles. | [presentation](functions/0011_batch_0007.md#fun_0042cc24--0x42cc24) |
| `0x41bdae` `FUN_0041bdae` | Callback Win32 : fermeture et activation/désactivation; délègue les autres messages à `DefWindowProcA`. | [window procedure](functions/0010_batch_0006.md#fun_0041bdae--0x41bdae) |
| `0x41cf86` `FUN_0041cf86` | Demande la fermeture : journalise `Posting Quit Message`, appelle `PostQuitMessage`, modifie un état global. | [quit request](functions/0010_batch_0006.md#fun_0041cf86--0x41cf86) |

## Écran « nouvelle partie » et texte cintré

| Adresse / fonction Ghidra | Rôle étayé et observations | Pseudocode |
|---|---|---|
| `0x44e77f` `FUN_0044e77f` | Charge les blocs descriptifs de `newgame.txt` : lit jusqu’à `ENDTEXT`, concatène les lignes et mémorise leurs offsets; limites visibles : huit blocs, 4096 octets. | [text loader](functions/0015_batch_0011.md#fun_0044e77f--0x44e77f) |
| `0x44e9c7` `FUN_0044e9c7` | Gestionnaire d’état/événement de la fenêtre New Game; charge les textes et transforme hit-tests en commandes/états. | [New Game handler](functions/0015_batch_0011.md#fun_0044e9c7--0x44e9c7) |
| `0x44e4f8` `FUN_0044e4f8` | Hit-test des quatre emblèmes (`0..3`) et de deux zones autour de `(320,240)`; sinon renvoie `-1`. | [hit test](functions/0015_batch_0011.md#fun_0044e4f8--0x44e4f8) |
| `0x44ebea` `FUN_0044ebea` | Convertit `0..3` en une commande indexée, et `4`/`5` en deux autres commandes. | [input mapping](functions/0015_batch_0011.md#fun_0044ebea--0x44ebea) |
| `0x44ec5d` `FUN_0044ec5d` | Dessine le menu; références `EXITNEWGAME`, `WORLDSIZE`, `TRIBE0..3`, `DIFFICULTY`, `BEGINGAME` et ressources `newback`, `glyphs`, `levidiff`, `ngrealms`, `bigfloat`; dessine les descriptions. | [New Game paint](functions/0015_batch_0011.md#fun_0044ec5d--0x44ec5d) |
| `0x44e613` `FUN_0044e613` | Callback de géométrie des lignes : avance `y` de `3 + hauteur_police`, calcule un bord via `40000-(y-240)^2`, choisit les limites gauche/droite. Assertion visible `ABS(lasty-240)<=NEWGAMERADIUS`. | [curved line callback](functions/0015_batch_0011.md#fun_0044e613--0x44e613) |
| `0x428baa` `FUN_00428baa` | Enveloppe les mots selon la largeur retournée par le callback et justifie les espaces pour remplir la ligne. | [wrap and justify](functions/0011_batch_0007.md#fun_00428baa--0x428baa) |
| `0x4289a7` `FUN_004289a7` | Helper de mesure/layout utilisé avant le placement; wrapper vers un appel indirect. L’ancrage vertical complet reste indéterminé. | [text layout helper](functions/0011_batch_0007.md#fun_004289a7--0x4289a7) |
| `0x448e5a` `FUN_00448e5a` | Initialisation/interactions de la fenêtre New Game; référence `data\\newgame.hzt` et appelle le hit-test. | [New Game setup](functions/0014_batch_0010.md#fun_00448e5a--0x448e5a) |

**Conséquence pour le remake :** le cintrage du texte est étayé par `0x44e613` et son utilisation par le justificateur `0x428baa`. L’ancrage vertical choisi côté remake reste approximatif, voir `ToneRebellion_Remake/GRAPHICS_RECONSTRUCTION.md`.

## Chargement de données, archives, monde et rendu

| Adresse / fonction Ghidra | Rôle étayé et observations | Pseudocode |
|---|---|---|
| `0x40ff5b` `FUN_0040ff5b` | Ouvre une archive COB, lit son index et enregistre ses métadonnées; limites visibles : cinq archives, 500 entrées. | [COB loader](functions/0008_batch_0004.md#fun_0040ff5b--0x40ff5b), [format](cob_archives.md) |
| `0x410105` `FUN_00410105` | Référence `cob.cfg` et appelle le chargeur d’archives. | [COB config loader](functions/0008_batch_0004.md#fun_00410105--0x410105) |
| `0x4153b8` `FUN_004153b8` | Parse les records `EFFECT` de `effects.txt` (plafond observé : 96). | [effects parser](functions/0009_batch_0005.md#fun_004153b8--0x4153b8), [catalogue](data_catalog.md) |
| `0x454d1f` `FUN_00454d1f` | Parse `fltinf.txt`, jusqu’à 64 entrées; tags `hover`, `pickup`, `carry`, `attack`, etc. | [floater parser](functions/0016_batch_0012.md#fun_00454d1f--0x454d1f), [catalogue](data_catalog.md) |
| `0x455833` `FUN_00455833` | Parse les records de `bldinf.txt` (`ITEM`, `SHAPE`, `BASE`, `CHUG`, `GLYP`, `INCI`, `CONS`, `PROD`, `OCCU`, `BARG`, `END`). | [building parser](functions/0016_batch_0012.md#fun_00455833--0x455833), [catalogue](data_catalog.md) |
| `0x461b3b` `FUN_00461b3b` | Lit/valide les emplacements d’île dans `ISLANDnn.TXT` : `NUM_LOCATIONS`, cinq champs, limite 100, tags `pad`, `tone`, `smpad`, `bridge`, `levhub`, etc. Les comparaisons Ghidra mappent `pad` et les pads de taille à la classe 0, `tone` à la classe 1, `bridge` à la classe 2 et les types spéciaux/feature à la classe 3. L'octet chaîne à `0x4a4c10` est confirmé comme `pad` par la lecture mémoire `ev_346f0482a3c7a5c0cd1c1c4320ec28be7e3b278647786754331652a5a8e798c3`. | [island parser](functions/0017_batch_0013.md#fun_00461b3b--0x461b3b), [catalogue](data_catalog.md) |
| `0x461859` `FUN_00461859` | Après chargement des records d'une île, copie ses paramètres de monde, initialise les états de records via `FUN_004500c4`, trie les liens d'îles puis associe les extrémités aux records de classe 2. Les liaisons excédentaires font retomber des records de classe 2 à la classe 0; aucun changement en classe 1 n'est visible dans le pseudocode. | [island state / bridge matching](functions/0017_batch_0013.md#fun_00461859--0x461859) |
| `0x410510` `FUN_00410510` | Construit des tables de couleur HZT : deux blocs de `0x700` octets, chacun donne 8 niveaux de 256 entrées; préserve l’indice transparent 255. | [haze tables](functions/0008_batch_0004.md#fun_00410510--0x410510), [catalogue](data_catalog.md) |
| `0x472013` `FUN_00472013` | Hit-test de carte : parcourt les îles en ordre inverse du dessin, compare le point à leurs bornes et renvoie l’objet île ou `NULL`. | [world hit test](functions/0018_batch_0014.md#fun_00472013--0x472013) |
| `0x405e11` `FUN_00405e11` | Décode des runs SHP et calcule/écrête leurs bornes opaques. **Interprétation :** primitive de rendu partagée; ne détermine pas à elle seule le type métier du sprite. | [SHP row/bounds](functions/0006_batch_0002.md#fun_00405e11--0x405e11) |
| `0x40ab42` `FUN_0040ab42` | Routine de dessin de formes de construction : vérifie un masque d’affichage, calcule une image selon le temps et la position, puis dessine la forme sélectionnée. Référence `blddraw.cpp` dans les chaînes de débogage embarquées (indice, pas preuve de source disponible). | [building shape draw](functions/0007_batch_0003.md#fun_0040ab42--0x40ab42) |

## Portée

Index fonctionnel sélectionné, et non affirmation que les 2 410 procédures ont toutes une sémantique résolue. L’inventaire technique est dans [index.jsonl](index.jsonl), les corps dans [functions/](functions/) et les exclusions/limites dans [unknowns.md](unknowns.md). Ajouter les rôles à mesure que consommateurs et call-sites sont confirmés; conserver l’adresse et le nom Ghidra pour la traçabilité.

## Démarrage d'une partie et placement initial

| Adresse / fonction Ghidra | Rôle étayé et observations | Pseudocode |
|---|---|---|
| `0x4121b7` `FUN_004121b7` | Dispatch des commandes de jeu. Les types `7` et `8` enregistrent respectivement taille du monde et difficulté; le type `9` démarre la partie et appelle `FUN_004637fc`, puis ouvre `WORLDVIEW`. Les valeurs sont des indices/configurations brutes; leur libellé de difficulté n'est pas déduit ici. | [command dispatcher](functions/0009_batch_0005.md#fun_004121b7--0x4121b7) |
| `0x4637fc` `FUN_004637fc` | Initialise l'état du monde : valide la taille et la difficulté, choisit les tables de monde, charge chaque `ISLANDnn.TXT` via `FUN_00461b3b`, initialise les tableaux, appelle le placement initial `FUN_0046466f` et une seconde phase `FUN_00464b9e`, puis attribue des états aux ponts et répartit des liens/objets dans les emplacements libres. Les valeurs de plusieurs champs d'état et la seconde phase ne sont pas entièrement interprétées. | [world initialization](functions/0017_batch_0013.md#fun_004637fc--0x4637fc) |
| `0x461b3b` `FUN_00461b3b` | Lit `ISLANDnn.TXT` en ordre de source. Chaque ligne devient un record de 0x60 octets : x/y, classe d'affichage et champs particuliers. Les classes 0/1/2/3 sont des classes internes observées, pas des noms métier universels. | [island parser](functions/0017_batch_0013.md#fun_00461b3b--0x461b3b) |
| `0x46466f` `FUN_0046466f` | Pour quatre slots, choisit l'île (en mode normal, slot 0–3), sélectionne un record de classe 1 selon son ordinal, puis cherche dans cette île le premier record de classe 0 et de champ `+0x10 == 0` à distance minimale `max(|dx|, |dy|)` du marqueur. Les égalités gardent le premier record de l'ordre source. Calcule ensuite une fenêtre horizontale autour de ce site. Le pseudocode appelle aussi des routines de création d'entité et quatre créations de « floater »; leurs effets complets ne sont pas portés par la sélection décrite ici. | [four-player initial placement](functions/0017_batch_0013.md#fun_0046466f--0x46466f) |
| `0x4672a6` `FUN_004672a6` | Retourne `max(abs(x1-x2), abs(y1-y2))`, la métrique employée pour départager les sites. | [location distance](functions/0017_batch_0013.md#fun_004672a6--0x4672a6) |
| `0x462a87` `FUN_00462a87` | Crée/initialise un objet dans l'état du monde pour un type et une position fournis; valide le type jusqu'à 4 et lance des traitements de post-création. Le type `0x2a` passé par le placement initial est conservé comme valeur observée; son nom métier n'est pas affirmé ici. | [world object creation](functions/0017_batch_0013.md#fun_00462a87--0x462a87) |

**Port dans le remake :** `ToneRebellion_Remake/src/core/game_start.c` reproduit uniquement la sélection des îles, marqueurs, sites proches et bornes de vue de `FUN_0046466f`. Les créations d'objets/unités et la seconde phase de génération restent à porter après résolution de leurs états.

**Validation avec les données :** `tone` est le tag de classe 1 utilisé comme marqueur dans `FUN_0046466f`. Les fichiers `ISLAND00.TXT` à `ISLAND03.TXT` contiennent chacun quatre records `tone`; le test du corpus confirme que les quatre affectations et leurs sites voisins se résolvent avec les règles transcrites.

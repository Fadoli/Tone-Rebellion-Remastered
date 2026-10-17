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
| `0x42704b` `FUN_0042704b` | Rendu de floater observé dans `fltdraw.cpp` : sélectionne les fiches de forme, anime et dessine séparément les jambes et le corps, applique des états comme portée/transport et des marqueurs d'état. Les descriptions de dessin viennent de `shapeinf.txt`; le pseudocode ne garantit pas les noms de variables reconstruits. | [floater draw](functions/0011_batch_0007.md#fun_0042704b--0x42704b) |
| `0x455833` `FUN_00455833` | Parse les records de `bldinf.txt` (`ITEM`, `SHAPE`, `BASE`, `CHUG`, `GLYP`, `INCI`, `CONS`, `PROD`, `OCCU`, `BARG`, `END`). | [building parser](functions/0016_batch_0012.md#fun_00455833--0x455833), [catalogue](data_catalog.md) |
| `0x461b3b` `FUN_00461b3b` | Lit/valide les emplacements d’île dans `ISLANDnn.TXT` : `NUM_LOCATIONS`, cinq champs, limite 100, tags `pad`, `tone`, `smpad`, `bridge`, `levhub`, etc. Les comparaisons Ghidra mappent `pad` et les pads de taille à la classe 0, `tone` à la classe 1, `bridge` à la classe 2 et les types spéciaux/feature à la classe 3. L'octet chaîne à `0x4a4c10` est confirmé comme `pad` par la lecture mémoire `ev_346f0482a3c7a5c0cd1c1c4320ec28be7e3b278647786754331652a5a8e798c3`. | [island parser](functions/0017_batch_0013.md#fun_00461b3b--0x461b3b), [catalogue](data_catalog.md) |
| `0x461859` `FUN_00461859` | Après chargement des records d'une île, copie ses paramètres de monde, réinitialise les états via `FUN_004500c4`, rassemble les ponts incidents et les records de classe 2, trie les listes avec `FUN_00461768`/`FUN_00461831`, puis affecte à chaque record l'indice de l'île à l'autre extrémité du pont correspondant. Si des records de classe 2 restent sans pont, ils sont ramenés à la classe 0. Aucun changement en classe 1 n'est visible dans le corps. | [island state / bridge matching](functions/0017_batch_0013.md#fun_00461859--0x461859) |
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
| `0x4637fc` `FUN_004637fc` | Initialise l'état du monde : valide taille/difficulté, charge les tables d'îles, appelle `FUN_0046466f` puis `FUN_00464b9e`, met l'état `2` sur les records de classe 2, et distribue ensuite des valeurs/liens sur certains records de classe 0 libres. Les champs de cette dernière distribution restent à identifier. | [world initialization](functions/0017_batch_0013.md#fun_004637fc--0x4637fc) |
| `0x464b9e` `FUN_00464b9e` | Parcourt jusqu'aux cinq premiers marqueurs `tone` par île; choisit premier/dernier selon l'index sur les quatre premières, ajoute l'autre extrémité si le bit 0 du mode est actif, puis tire un marqueur sur les îles suivantes. Choisit un item 6–9 avec `FUN_004535e4` et appelle `FUN_00452859` avec propriétaire `4`. | [distribution des entités de départ](world_start_distribution.md) |
| `0x4535e4` `FUN_004535e4` | Forme les IDs 6–9 candidats depuis deux tables indexées par shape ID; préfère les IDs absents de l'île puis choisit via `FUN_00467260`. L'île comparée à `DAT_006136b0 - 1` autorise les quatre IDs; son initialisation runtime n'est pas identifiée. | [choix de l'item](world_start_distribution.md) |
| `0x452859` `FUN_00452859` | Valide l'item avec `FUN_00452656`, l'écrit via `FUN_004528ca` et déclenche des mises à jour. | [création sur marqueur](world_start_distribution.md) |
| `0x4528ca` `FUN_004528ca` | Écrit l'ID d'item en `+0x10`, le propriétaire en `+0x14`, initialise des champs et drapeaux de l'enregistrement. | [écriture et effets observés](world_start_distribution.md) |
| `0x461b3b` `FUN_00461b3b` | Lit `ISLANDnn.TXT` en ordre de source. Chaque ligne devient un record de 0x60 octets : x/y, classe d'affichage et champs particuliers. Les classes 0/1/2/3 sont des classes internes observées, pas des noms métier universels. | [island parser](functions/0017_batch_0013.md#fun_00461b3b--0x461b3b) |
| `0x4500c4` `FUN_004500c4` | Initialise le record runtime : propriétaire `+0x14=-1`, remet `+0x10` à zéro sauf pour la classe 3, et efface/initialise plusieurs champs et drapeaux. Ce reset précède les choix de départ via `FUN_00461859`. | [état runtime des records](functions/0015_batch_0011.md#fun_004500c4--0x4500c4) |
| `0x46466f` `FUN_0046466f` | Pour quatre slots, choisit l'île (en mode normal, slot 0–3), sélectionne un record de classe 1 (`tone`) selon son ordinal, puis cherche dans cette île le premier record de classe 0 et de champ `+0x10 == 0` à distance minimale `max(|dx|, |dy|)` du marqueur. Ce champ a déjà été remis à zéro par `FUN_004500c4`. Les égalités gardent le premier record de l'ordre source. Calcule une fenêtre horizontale autour du site, crée l'item de construction `0x2a` sur ce site et appelle quatre fois `FUN_00462a87` au point du marqueur. | [four-player initial placement](functions/0017_batch_0013.md#fun_0046466f--0x46466f) |
| `0x4672a6` `FUN_004672a6` | Retourne `max(abs(x1-x2), abs(y1-y2))`, la métrique employée pour départager les sites. | [location distance](functions/0017_batch_0013.md#fun_004672a6--0x4672a6) |
| `0x4641de` `FUN_004641de` | Résout un record du catalogue `pad.txt`. Si le premier paramètre est un joueur 0–3, il ajoute `16 × joueur` à l'ID d'item de base; sinon il emploie l'ID directement. | [player-specific pad record](functions/0017_batch_0013.md#fun_004641de--0x4641de) |
| `0x462a87` `FUN_00462a87` | Crée/initialise un objet floater dans l'état du monde pour un type et une position fournis; valide le premier paramètre entre 0 et 4 et lance des traitements de post-création. `FUN_0046466f` l'appelle quatre fois par slot avec le type-index du slot et les coordonnées du marqueur `tone`. | [world object creation](functions/0017_batch_0013.md#fun_00462a87--0x462a87) |
| `0x452859` `FUN_00452859` | Initialise un pad de l'ID demandé pour un joueur. Au démarrage, `FUN_0046466f` passe `0x2a`; le record 42 de `pad.txt` est `p-hall` avec l'identifiant de texte `GREATHALL`. Le helper `FUN_004641de` sélectionne le bloc de 16 items correspondant au joueur. | [pad creation](functions/0015_batch_0011.md#fun_00452859--0x452859), [catalogue](data_catalog.md) |
| `0x467260` `FUN_00467260` | Produit un nombre pseudo-aléatoire borné : si la borne vaut zéro, la remplace par `0x7fff`; multiplie le tirage 15 bits par la borne, divise par `32768.0f`, puis tronque vers zéro avec `__ftol`. | [bounded random](functions/0017_batch_0013.md#fun_00467260--0x467260) |
| `0x474b80` `FUN_00474b80` | Stocke la graine fournie dans le global `DAT_004a6340`, consommé par le générateur suivant. | [random seed setter](functions/0019_batch_0015.md#fun_00474b80--0x474b80) |
| `0x474b90` `FUN_00474b90` | Met à jour `DAT_004a6340 = seed * 0x343fd + 0x269ec3` en arithmétique 32 bits et retourne les bits 16–30; c'est le LCG 15 bits consommé par `FUN_00467260`. | [15-bit LCG](functions/0019_batch_0015.md#fun_00474b90--0x474b90) |
| `0x461768` `FUN_00461768` | Comparateur des liens de ponts utilisé par le tri dans `FUN_00461859`. À partir de deux records de pont, sélectionne leur extrémité non partagée, lit les angles correspondants dans la table de positions du monde (`0x5ebd78`, index monde à pas `0xb4`, entrée à pas `0xc`), puis retourne la différence convertie en entier par `__ftol`. **Interprétation :** trie les îles voisines autour de l'île courante par angle. Le pseudocode Ghidra seul est faux/incomplet (`__ftol(); return;`); le rôle est récupéré de l'assemblage observé. | [bridge comparator and assembly](functions/0017_batch_0013.md#fun_00461768--0x461768) |
| `0x461831` `FUN_00461831` | Comparateur des records de classe 2 pour le tri dans `FUN_00461859` : renvoie la différence entre le premier `short` (coordonnée X dans ce contexte) des deux records pointés, donc ordre croissant sur X. | [class-2 location comparator](functions/0017_batch_0013.md#fun_00461831--0x461831) |
| `0x4777a0` `FUN_004777a0` | Utilitaire générique de tri appelé deux fois par `FUN_00461859`, avec des éléments de quatre octets et un comparateur fourni; l'algorithme de tri lui-même n'est pas interprété ici. | [sort helper](functions/0018_batch_0014.md#fun_004777a0--0x4777a0) |

**Port dans le remake :** `game_start.c` reproduit les starts/pads/floaters et les choix de marqueurs/items; `game_session.c` construit l'état runtime mutable, y compris les IDs de halls par joueur (`0x2a + 16 × joueur`) après `FUN_004641de`, l'appariement classe 2/ponts, et les deux boucles d'affectation classe 0 de `FUN_004637fc`. Le bouton New Game transmet cet état à la vue d'île Win32; celle-ci dessine les quatre halls depuis leurs SHP dédiés, avec les plages `BASE` du `bldinf.txt` et la règle modulo de `FUN_0040aaeb`. Le rendu des autres bâtiments/unités et les boucles de simulation restent à faire.

**Validation avec les données :** `tone` est le tag de classe 1 utilisé comme marqueur dans `FUN_0046466f`. Les fichiers `ISLAND00.TXT` à `ISLAND03.TXT` contiennent chacun quatre records `tone`; le test du corpus confirme que les quatre affectations et leurs sites voisins se résolvent avec les règles transcrites. Le post-traitement `FUN_00461859` associe séparément les liens du monde aux emplacements de classe 2; il n'est pas la source des marqueurs `tone`.

**Port RNG :** `ToneRebellion_Remake/src/core/tone_rng.c` retranscrit la transition de `FUN_00474b90` et l'échelle de `FUN_00467260`. La constante flottante à `0x494798` est `32768.0f` (octets `00 00 00 47`). Le test `tone_rng_unit` vérifie la séquence pour une graine connue et la conversion bornée; le menu Win32 utilise désormais le même helper 15 bits au lieu d'une copie locale.

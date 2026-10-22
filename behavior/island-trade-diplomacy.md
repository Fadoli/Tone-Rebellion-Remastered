# Trade, diplomatie et événements

## Trade

- **Observé :** grille de neuf valeurs, trois colonnes × trois lignes; clic gauche/droit ajuste de 10, bornes 0–1000. `TradeZERO` efface; `TradeDOIT` envoie des messages catégorie 3/type `0xb` aux destinataires non nuls puis efface l’offre.
- **Observé :** le dispatch type `0xb` prend les Hall source/cible depuis deux contextes joueur distincts; chaque quantité négative devient zéro et est bornée au stock signé du Hall source avant débit/crédit. Preuves : `ev_133e7da95213ee9e2afef5850bfdb622a53cde1a82d5ad9676b6717fd33abff2`, `ev_90fc7b398e8cc430ee898f0371c196e285bf0f21c5cd78aa04fcdd060294d4ce`, `ev_593f8a710f1ed28f08907d6644367309eb942d46a247531b989779fa3525c71f`.
- **Port :** `TradeDOIT` crée les demandes; le tick local les passe au helper récepteur puis les retire après application. Un transfert est borné au stock signé disponible du Hall source. Les demandes dont un Hall n’est pas résolu restent en tête de file.
- **Preuves UI :** `ev_3b5f4720935dc2a46a88ff1fbfea436d9ef271c9dc1729588ff092dad9112b44`, `ev_ce422c3de4f4cbea0f4a05e91a4bceeed3f8bd5614b6c565a9389730931e5f1c`.

## Diplomatie

- **Observé :** `IWDiplomacy` émet catégorie 3/sous-type 10 pour la cible non locale. Le dispatch inverse les mots correspondants dans les groupes joueur `+0xe8` ou `+0xd8`. Les états d’affichage utilisent les frames 21–23 de `DIPLOMA.SHP`; clés de texte et libellés visibles semblent inversés selon le code.
- **Port :** zones, choix d’état et outbox sont portés; bannières seulement pour les ouvriers initiaux, sans animation ni transport réseau.
- **Preuves :** `ev_83310289d91202d60603bd9f80ef78479a48b64c570e61ce5afd111af27eccb0`, `ev_b31952fff609b555e9e8c59eecea0d388c46aab20464cc9ff7bdc3ea7e0b5f`, `ev_bf0c6364cbdd6d347934dbdf3ecc156f6f17460cd80f9a1b49567d39fdcfcfb2`.

## PANIC et tâches

- **PANIC :** état et limites dans [l'analyse des panneaux](island-panels.md).
- La projection Tasks et les handlers de priorité/annulation sont documentés dans [island-tasks.md](island-tasks.md); producteurs et cycle de vie restent ouverts.

Pseudocodes : [batch 0008](../functions/0012_batch_0008.md), [batch 0013](../functions/0017_batch_0013.md).

## Revue du panneau Commerce (REA, ev_28319f95…, ev_4296c2a3…, ev_71fb8180…, ev_4c15db51…, ev_c2399ce6…)

Concordances: icônes de ressource (bildtone, tonecrys, magctone, frame 4) en `(30, 52 + 24 r)`, montants en
`(40 + 38 c + (28 - w) / 2, 44 + 24 r)`, hit-test de la fonction `FUN_0043ec78` (x 40..154, y 37..109, cellule
`(x - 40) / 33` par `(y - 37) / 19`, pas de dessin 38 x 24: le natif a aussi cette discordance), pas de 10 borné à
0..1000, `TradeZERO` (message 4010, remise à zéro des 9 valeurs) et `TradeDOIT` (4011, un paquet catégorie 3 type 0xb par
colonne non nulle puis remise à zéro), colonnes = les trois autres joueurs sans le joueur local.
Corrigé: une offre nulle s'affiche `-` (chaîne `0x4a03fc`) et une offre non nulle `%d`; la légende du bouton survolé
(`TRZERO` « Annuler », `TRDOIT` « Transférer » de `gamey.txt`) est dessinée en (156, 50) d'`IWTrade`.
Écarts restants non portés: emblèmes d'en-tête de colonne (`FUN_00428191`, `55 + 38 c`, y 12), rectangles de ligne
(`FUN_004109a6`, x 40..190), remise à zéro des offres à l'ouverture du panneau (message 1, inférence: le port les garde
dans l'économie du joueur), refus du port quand la file de requêtes est pleine (le natif ne vérifie pas), couleur du
texte, correspondance frame/état des boutons.

## Revue du panneau Diplomatie (REA, ev_00fb36d4…, ev_78050b04…, ev_a944025b…, ev_bebb5d8e…, ev_263f1f3f…)

Observation: `FUN_0043e5aa` dessine dans la pane `IWDiplomacy` (192, 368)-(447, 471); tous les assistants de dessin
du natif ajoutent l'origine de la pane à leurs arguments et l'appelant retranche cette origine des coordonnées absolues
des emblèmes et des actions: positions finales en coordonnées de fenêtre: emblèmes de groupe `7c` en (264, 378),
(301, 386), (325, 379); cadre de destinataire 23 et état de politique 21/22 en x = 220 / 300 / 380 et y = 426 (colonnes 0
et 2) ou 436 (colonne 1); bannière locale en (319, 378), bannières des autres joueurs en (238 / 318 / 398, 441 ou
451); légende (`TRDIPHI` si le destinataire est survolé, sinon `TRCOMHI`) en (334, 375). Pour la ligne de politique
survolée, la dernière frame du groupe (+6) se superpose à la frame de base au lieu de la remplacer. Les frames
`7c + 1..5` sont des variantes animées (compteur de trois tics, 0..4) conditionnées par `DAT_006192a0[joueur][cible]`
(sens inconnu).
Corrigé: le port soustrayait l'origine de la pane aux positions absolues puis dessinait en coordonnées de fenêtre
(`draw_sprite` n'ajoute pas l'origine): emblèmes, cadres 21/22/23 et surbrillance tombaient décalés de (-192, -368),
en haut à gauche de l'écran. Les positions sont maintenant absolues (`action_y = haut + H - (colonne 1 ? 20 : 30) -
15`) et la surbrillance de politique se superpose à l'emblème de base.
Écarts restants non portés: variantes animées `7c + 1..5` et le tableau `DAT_006192a0`, descripteur de bannière natif
(`FUN_00464242(classe, 0)` via `FUN_0042704b`, sous-couche) face au floater vivant du port, police et couleur de la
légende (objet de police natif, non décodé), fond statique par défaut (remplissage indice 0 quand `DAT_004c2bac == 0`),
nombre de frames de `diploma.shp` non vérifié.

### Variante animée de l'emblème de Diplomatie (REA, ev_78050b04…; inférence)

Les zones de survol du port (`game_diplomacy_hit_test`: x `0x10a..0x127`, `0x139..0x149`, `0x15b..0x178`, y 399..`0x1b1`) sont déjà en
coordonnées de fenêtre, comme les positions d'emblèmes corrigées plus haut. L'emblème de base du groupe `7c` passe à
`7c + 1 + anim` quand `B = DAT_006192a0[local][cible]` est non nul (anim = 0..4, un pas tous les trois dessins). Les deux
tableaux `DAT_00619290` (A, politique, frame 21/22) et `DAT_006192a0` (B) sont distants de 0x10, comme les deux groupes
`+0xd8`/`+0xe8` que `FUN_00465793` (catégorie 3, sous-type 10) inverse: B est donc très probablement le drapeau de
destinataire de message, que le port garde dans `message_recipient_mask`. Port: variante `7c + 1 + (ticks / 3) % 5`
quand le destinataire est actif (inférence; cadence en tics d'animation et non en dessins). Non vérifié: sens de B par
une lecture directe de son écrivain, aspect des frames 1..5.

### Bannière de joueur (REA, ev_0e714c8f…, ev_c4ef7e00…, ev_581135505f9a…)

Observation: `FUN_00428191(surface, classe, sous-type 0, 0, x, y, 8)` construit un descripteur de 0x4c octets à partir
de la classe (tribu) et du sous-type seulement (`+0` classe, `+4` sous-type, le reste non écrit), lit l'enregistrement
`FUN_00464242(classe, 0)` (index `9 * classe`, 14 octets) puis `FUN_0045575c` (entrée de 0x54 octets: image de sous-couche
`[0]`, image du corps `[1]`, frames `[2]..[5]`, diviseur `[6]`) et dessine par `FUN_0042704b` mode 8 à
`(x, y)` sans décalage: sous-couche d'abord (si `[0] != -1`, frame `[2]`), puis corps (frame `[4] + (octet +0x14 /
[6]) % ([5] - [4] + 1)`). Aucun floater vivant n'intervient.
Port: un joueur sans floater actif affiche maintenant la pose de travailleur de sa tribu (frame 0 des jambes et du corps
de `g_initial_floater_legs/bodies[tribu]`, non retourné) au lieu de rien. Inférence: ces feuilles correspondent à
l'enregistrement de classe natif. Non établi: octet `+0x14`, source de la police de la légende (objet de police
`FUN_0042de0d` non résolu; noms `smfont` et `bgfont` en `0x4a0308`), couleur native de la légende.

Passe Commerce (REA, `FUN_0043edac` dessin, `FUN_0043eab5` messages, `FUN_0043ec78` clic; ev_116199be…, ev_016c96cc…, ev_58dd79bd…): remise à zéro à l'ouverture
(`memset(panel+0x74, 0, 0x12)` au message 1): portée. Texte des montants et légende en indice de palette 6 (objet `DAT_005c2870`): déjà couvert par `panel_text_color`.
Emblèmes d'en-tête: `FUN_00428191` en `(55+38c, 12)`, c = 0..2, classe `c` ou `c+1` si `c >= DAT_0049f538`; rectangles de ligne
`x 40..190, y 37+24r, h 14` (blit de forme remappé `FUN_004109a6`, `FUN_004106dd(1,0)`). Ces deux éléments restent absents du port (sprite/frame de bannière
non résolus). Clic: `x 40..154`, `y 37..109`, colonne `(x-40)/33`, ligne `(y-37)/19`, pas ±10, 0..1000. À vérifier: orientation ligne/colonne du
validateur (natif par colonne cible, port par ligne ressource).

Emblèmes et fonds du Commerce (REA, ev_e0739526, ev_825b6d33, ev_0d5900a6): `FUN_00428191` construit un objet de 0x4c octets (classe, sous-type) et dessine via
`FUN_0042704b(surface, obj, x, y, 0, mode 8, 0x10000, 0)`; mode 8 = blit RLE transparent coupé, sans voile, origine absolue. Enregistrement
`FUN_00464242(classe, sous)` = `0x5ebfa0 + (classe*9+sous)*14`, index d'info de forme `+4`, entrée de 0x54 octets (`FUN_0045575c`): trame du corps =
`[4] + (obj+0x14 / [6]) % ([5]-[4]+1)`, sous-couche `[2] + nibble bas de surface+0xa` borné [2..3]. Fichier de bannière non résolu (aucun nom dans les chaînes; pas de
SHP de tribu dans le corpus), animation par tick non observée. Fonds de ligne: forme `FUN_0040e864(panel+0x1c)` trame `panel+0x1e` (écrivain non trouvé);
`FUN_004109a6` applique `table[pixel]` sous un masque (`FUN_004106dd(1,0)` = table de voile niveau 0 `0x4b20f0`, remplie à l'exécution), source non lue: les fonds sont un
assombrissement du fond de fenêtre, pas des pixels de forme. Rectangle d'en-tête `x 40+38c..68+38c, y 22..102` = ombrage statique (pas de survol). Non porté:
tant que l'index de forme de bannière manque, les emblèmes ne peuvent pas être fidèles; l'ombrage des lignes/colonnes est portable via la LUT de voile existante.

Port (interprétation): la « bannière » de `FUN_00428191` est la pose du travailleur de la tribu (même helper que la Diplomatie, sous-type 0); le Commerce
l'affiche désormais à `(55+38c, 12)` relatif au panneau, tribu `c` ou `c+1` à partir du joueur local. Hypothèse: origine relative au panneau (non confirmée par un
argument de site d'appel); fonds de ligne ombrés non portés.

Origine de l'emblème (REA, ev_9fabd444f0c1b2d2, ev_e60ae5e3389e533e): l'appel de `FUN_0043edac` à `0x43eeee` pousse `x = 0x37 + 0x26*i`, `y = 0xc` bruts, sans `this+0xc/+0x10`;
`FUN_00428191`/`FUN_0042704b` les transmettent sans origine de surface (surface globale `DAT_005c30a0`, 640x480). Même traitement brut pour l'icône de ligne `(30, 52+24r)`
et les montants, que le port place déjà relativement au panneau (revue visuelle antérieure: l'origine du panneau est ajoutée par l'enveloppe de fenêtre, cf. Diplomatie où l'appelant
passe des coordonnées moins l'origine). Conclusion retenue: pane-relatif, comme les autres éléments de la même fonction; le rapport « absolu » du sous-agent n'est pas retenu
(contradit la Diplomatie). Reste non confirmé par un tracé de `FUN_00404770` / `FUN_0042704b`.

Origine, suite (REA, ev_5935c354…, ev_4d46b37e…, ev_e60ae5e3…): `FUN_0042d28f` renvoie `&DAT_005c30a0` et n'y écrit que `+4 = 639`, `+8 = 479` (étendues plein écran);
`FUN_00404770` ajoute `surface+4/+8` à x,y puis borne contre `+4..+0x10`, ce qui est incompatible avec une origine nulle: la mise en page de la structure (ou le typage du
décompilateur) reste non résolue. Aucun positionneur d'origine par fenêtre trouvé. Décision inchangée: emblème pane-relatif comme les autres éléments, à contrôler visuellement.

# Inventory et glyphes

## Inventory

- **Observé :** `FUN_0043d45c` envoie l’ID survolé (`-1` hors grille) à `IWTextInfo`; `FUN_00439673` résout `BRIDGE%02d` (ID 5) ou `PLOT%02d` (6–33). `FUN_0043d59b` rafraîchit les compteurs sans toucher la page `+0xec`; `FUN_0043d6a3` utilise la page brute, donc une page devenue hors plage reste vide. `InvCycle` revient alors à zéro. Le clic d’un item visible émet `0x42`; un clic carte émet une requête catégorie 0/type 4. Preuves : `ev_9fc07a22727b951aa803d665ceb9d49be1f2cf511265359011b5b1a9c21be232`, `ev_45fa9501196d329d11ea55b4b6cd052663e870a194f980cb444488b0704663af`, `ev_b54bbd72eab69e7ed428a76f96a43019b3f9d5d401ea65b04fcd1d0f6285d9aa`, `ev_b6f830a22cb40d4fddda3ad559c0a6aaecf6caae982f1a6027434aa2a0f0d62e`, `ev_44c84c02349f96e801edd8d158e98219890eac2e7f94382728cb39bb6a58e816`, `ev_1f4c9fb7164cf7098c41401790393896464ff57491fc99b2d87cefa2ada748d0`.
- **Port :** textes locaux de `plotobj.txt`, survol, sélection, curseur et requête sont modélisés. `game_session_dispatch_inventory_result` reproduit la transaction de `FUN_00465793` catégorie 3/sous-type 4 : compteur positif, appel du récepteur, débit d’un item seulement si le récepteur accepte. La logique état 0 de `FUN_004503bd` crée un `PIT_Object` avec l’ID 5–33 dans un emplacement vide; cette opération existe aussi dans le dépôt d’un floater, mais son raccord à l’événement de résultat reste à établir. Le producteur d’événement et les autres états d’acquisition ne sont pas reliés au callback générique. Evidence résultat `ev_e38a48fb829ba881832e1d6b3585a4996be1470e7e04eadd00714c5f5f3e5f8f`, récepteur `ev_9e94c79685ecafec1c2df530eb6878eb46dad04b14d2e5355d54c3eca58f0f5e`.

## Glyphes

- **Observé :** `IWGlyphs` consomme les clics vides; seul un index valide émet `0x43` et arme le mode `0x11`. Le clic carte émet la requête catégorie 3/type 3; le consommateur cherche un acteur actif du joueur avec `+4=8`. `FUN_00462a87` vérifie le masque, l’absence d’un type 8, puis la garde `DAT_004befe0` ou un tirage LCG borné par le nombre de glyphes acquis. Le flag est posé sous une garde au démarrage puis remis à zéro lors d’un chemin de retrait; son sens reste inconnu. `+0x42` stocke des coordonnées compactées, pas le glyphe.
- **Port :** le clic valide parcourt les floaters dans l’ordre des slots et donne l’ordre `0x13` / sort `0x16` au premier acteur actif du joueur de sous-type 8. Il reproduit aussi le reset `FUN_00421ec1(-1)` avant le nouvel ordre : libération de la tâche liée, annulation conditionnelle d’une ancienne tâche de collecte, remise à zéro de l’état source et des bits d’ordre. Le dispatch n’exclut pas les acteurs déjà en animation de mort, car la recherche native `FUN_0046562b` ne filtre que les slots occupés, le joueur et le sous-type. L’effet monde propre à chaque glyphe reste à confirmer au-delà de l’ordre de cast. Preuves REA complémentaires : reset `ev_d925a619c1f64dc2bee612e35ae4c4e6defe955e87556d2e69d4b672e153ac76`, recherche `ev_39fd4b8d6e11c67ab5a5bd8ac8c93917443b3f4faf02bf9b323101e6d08db56f`.
- **Preuves :** `ev_8ca64092de3b786050ffad150abf2dd04b82ef777d65f1cab09f8f07936c5419`, `ev_b65156eb13978511b7f06cdb3fee86e7c2c4a37bf3cac67ad0f0badb2f999a68`, `ev_a8230350584e54954217dfeda123b6cf8d9dc6ca7211fff2385661c22cdab6ba`, `ev_352feb8e600eceb96c53f7813bd012e104389976cd0dc42358a78b6a0fcddd24`, `ev_dc8178f27dfbe5ae5eb96c11000ab02fb34bf426d8d5bfa2b5e0e778095f46d4`, `ev_b6c592d2020a3b072f7d397ada43d048a75789229d848e76ffadec2a536491cf`, `ev_78147898fdd67751ac4b9dc7f61c638b16c2a36dd616080db86817b146a0965a`, `ev_50b787cc3ab559f485e8b24562694aeeedfcc5940b0eab8001073461b3f42942`.

Les notes détaillées historiques sont dans [island-panels.md](island-panels.md); pseudocode ciblé : [batch 0013](../functions/0013_batch_0009.md) et [batch 0014](../functions/0018_batch_0014.md).

## Revue du panneau Inventaire (REA, ev_7105b54d…, ev_7c8f58f0…, ev_089a56b9…, ev_512d3ead…, ev_f7e67d60…)

Concordances: page de 10 (5 × 2), cellule `(droite-gauche)/5` × `((bas-haut)-24)/2` à partir de `haut+24`,
centrage des bornes opaques, compteur affiché seulement quand il dépasse 1 en `(x+7, y-21)`, contours de
survol (indice de palette 1) et d'objet armé (indice 4, prioritaire) dessinés avant l'icône, comptes par
joueur (`DAT_006191fc + id*2 + DAT_0049f538*0x14a0`), pas de remise à zéro de la page par le rafraîchissement.
Corrigé: format du compteur `"(%d)"` (chaîne `0x4a020c`, avec parenthèses); ordonnée du texte `NOART` =
`(bas-haut)/2 - 6` sans terme de hauteur de police.
Écarts non portés: les messages natifs `0x3039` (texte d'information, clé `BRIDGE%02d` si id < 6 sinon
`PLOT%02d` avec id - 6, dessiné en (10, 6)) et `0x42` (objet armé) vers le répartiteur; le port garde un
retrait de 8 px pour tous les textes d'`IWTextInfo` (métriques de retour à la ligne natives non résolues,
l'ancrage (10, 6) n'est établi que pour ce mode); hit-test sans bornes de colonne ou de ligne dans le natif
(artefacts en bord droit et bas, le port renvoie -1); règle de visibilité d'`InvCycle` (hypothèse: seulement
au-delà d'une page) et remise à zéro de la page au clic (introuvable côté natif).
Inconnues: couleurs (compteur, `NOART`, indices de palette), décalage de cadre appliqué par `FUN_00404770`,
égalité de `DAT_0049f538` et du joueur du Hall, touche clavier.

### InvCycle, texte d'IWTextInfo et message 0x42 (REA, ev_3593eda8…, ev_68eb428b…, ev_20a8dd58…, ev_ff703ed6…, ev_614c66b1…)

Observation: `InvCycle` envoie le message 69 (`0x45`) à `IWInventory`; `FUN_0043d285` fait
`page = page + 1` si `(page + 1) * 10 < nombre`, sinon `page = 0`, puis marque le panneau à redessiner;
le rafraîchissement `FUN_0043d59b` envoie `InvCycle` message 1 (montrer) au passage à 11 objets ou plus et
message 2 (cacher) au retour à 10 ou moins, uniquement aux transitions (compte initial -1). La règle de
`game_inventory_next_page` du port est équivalente. Clés de texte: objet 5 → `BRIDGE00`, objets 6..33 →
`PLOT00..27` (déjà celles du port).
`IWTextInfo` (pane 456 328 631 395, 175 x 67): `FUN_00439673` passe (10, 6) au renvoi à la ligne
`FUN_00428baa`, mais le rappel `FUN_0043954d` impose x = 6, borne droite 173 (largeur 167), ordonnée
`y + 1 + hauteur de ligne` et pas de ligne = hauteur de police + 1, sans limite de lignes; couleur = indice
de palette 6. Les modes NEWGAME, LEVNAME et 5 sont centrés (`x = (droite-gauche-w)/2`, `y = (bas-haut)/2 - 10`),
le mode 4 (niveau) écrit des lignes simples en (10, 2) et (10, 11). Message `0x42`: `FUN_0042fa0f` mémorise
l'objet armé (`DAT_0049e9c4`) et le curseur (`FUN_0043530b(0x11)`); le clic n'envoie jamais -1, seul le
message 2 d'`IWInventory` désarme.
Port: retrait 6 et largeur `pane - 8` pour le texte d'`IWTextInfo`. Non porté: pas de ligne natif (`+1`, le
renvoi partagé du port garde `+2` car ses autres appelants ont leurs propres rappels natifs), ordonnée
de la première ligne (`y + 1 + h` non résolue face au décalage de cadre), modes centrés et mode 4.

### Géométrie exacte du texte d'`IWTextInfo` (REA, ev_4fa53e73…, ev_ff703ed6…, ev_7517af5a…, ev_c4271bbf…)

Observation: `FUN_00428baa(ctx, x, y, texte, 0, rappel)` appelle le rappel avant chaque ligne avec `(x, y)` et dessine
la ligne aux sorties; l'argument `(10, 6)` est écrasé. `FUN_0043954d` sort `x = 6`, borne droite 173 (largeur
167) et `y_sortie = y + 1 + h` (h = hauteur de la police courante, `[police+8]`); le décalage s'accumule, donc la
ligne k a son sommet en `6 + (k + 1) * (h + 1)` (pas de ligne `h + 1`). Les mots se mesurent par somme des
avances de glyphes, coupure gloutonne au dernier espace qui tient, aucune limite de lignes; `y` est le haut
de la rangée de glyphes. Avec `bgoutfnt.fnt` (hauteur 13 à l'octet 8; liaison à `DAT_005c30b8` inférée): lignes
aux ordonnées 20, 34, 48… Modes simples: NEWGAME, LEVNAME et le mode 5 sont centrés sans rappel
(`x = (droite-gauche-w)/2`, `y = (bas-haut)/2 - 10`); le mode niveau dessine en (10, 2) et (10, 11).
Port: `hall_support_render.inc` utilise maintenant x = 6, largeur 167, première ligne à `haut + 6 + h + 1` et pas
`h + 1` via `draw_wrapped_bitmap_label_pitch`; le renvoi partagé des autres écrans garde `h + 2`. Non porté: les
modes centrés et niveau; liaison de `DAT_005c30b8` à `bgoutfnt.fnt` non tracée.

Contexte des appels à `FUN_004503bd` (REA, ev_377d36e5, ev_f5fa2b6f, ev_b1d53f56, ev_053a6cdd, ev_dccd5da0, ev_b943bfaa): 8 appels via le thunk `0x402347`, dans quatre fonctions:
`FUN_0041e569` (phase livraison, objet porté, quantité 1, joueur `*rec`; 0x41ea31/0x41ea8f/0x41eaf3), `FUN_00425084` (dépôt dans un emplacement libre, 0x425157, sinon compteur d'attente),
`FUN_00465793` sous-type 4 (0x465cde, débit seulement si l'appel renvoie non nul) et `FUN_004672ef` cas 1 (0x4673f0.., +50 aux compteurs `+0x28/+0x2a/+0x2c`, sans bits ni glyphe).
Bits de progression (état `+0x10 == 3`): si `action - (2*DAT_005eebf8[île*0x14f4] + 6) == record+0x4a` alors `record+0x1c |= 1` et `slot+0x4a |= 1<<indice` (indice 0/1: les deux objets
`2X+6` et `2X+7`); quand `slot+0x4a & 3 == 3` dans ce même appel: `slot+0x1c |= 1`, `DAT_005eebe4[île*0xa7a] = 1`, **`DAT_00619242[joueur*0x14a0] |= 1<<île` (glyphe attribué)** et évènement monde 4.
`FUN_004672ef` cas 0x11 met `slot+0x4a |= 3` sans glyphe. Inconnues: ECX réel des appels de `FUN_00465793`/`FUN_004672ef`, sens de `DAT_005eebf8/e8/e4`, si le site de livraison est le Hall.
Interprétation: un glyphe est attribué quand les deux objets consécutifs `2X+6` et `2X+7` ont été livrés au site de l'île.

Correction et tables (REA, ev_655c26af asm, ev_ba8f92a6, ev_916926256, ev_8878395b): Ghidra met les pas à l'échelle faussement; l'assembleur donne un bloc par île `IB = 0x5ec218 + I*0x29e8`
avec `word IB+0x29e0` (`DAT_005eebf8`, identifiant de paire B, 0..13), `word IB+0x29d0` (`DAT_005eebe8`, indice X du site de glyphe), `dword IB+0x29cc` (`DAT_005eebe4`, drapeau « glyphe obtenu »).
Branche `FUN_004503bd` état 3 (0x4506d6..0x450794): `I = word[rec+8]`, `d = action - (2B+6)` doit valoir `word[rec+0x4a]`; alors `rec+0x1c |= 1`, `S = IB + X*0x60 + 0x428`, `S.word+0x4a |= 1<<d`; si `& 3 == 3`:
`S+0x1c |= 1`, `IB+0x29cc = 1`, `word 0x619242 + P*0x14a0 |= 1<<I` (bit de l'île `I`, pas de `B`), évènement 4. `FUN_00460072` (aucun appelant résolu) installe les ordres: `S+0x24 = 2B+6` puis `2B+7`
(`B < 0xe`). Interprétation: le glyphe d'une île s'obtient en livrant les objets `2B+6` et `2B+7` au site `X` de cette île. Inconnues: valeurs initiales de B/X, écrivain de l'état 3, valeur initiale de `rec+0x4a`.

Rapprochement avec le port: le bit du joueur est `1 << île` (île 0..13) et le port indexe les glyphes de 0 à `GAME_GLYPH_COUNT - 1`: l'indice de glyphe du port correspond donc à l'indice d'île natif (interprétation).
`game_session_acquire_glyph(session, joueur, glyphe)` n'a aucun appelant hors tests; l'attribution en jeu (livraison `2B+6`/`2B+7` au site `X`) reste à brancher quand B et X seront connus (probablement lus des données d'île).

Rectification (REA ev_bbd3d552, ev_ee737bfe, ev_46f600af + lecture du port): `DAT_00619242` est le masque « fonctionnalité spéciale » par joueur, déjà porté
(`special_feature_island_mask`, `credit_floater_delivery`); ce n'est pas le masque des glyphes du panneau (`glyph_mask`), dont l'écrivain natif reste à établir (la phrase « glyphe attribué »
plus haut est à lire ainsi). Origine des données: B = 4e champ (forme) de `WORLDPOS.TXT` par monde et île (= `leviathan_marker_shape_id` du port), X = indice de l'enregistrement
`feature` de `ISLANDnn.TXT` (nn = B). Les deux sont lus de fichiers, non calculés.

Rectification 2 (REA, ev_303065b9…, ev_2ea57c14…, ev_ba8f92a6…): `DAT_00619242[joueur*0x14a0]` EST le masque lu par le panneau Glyphes (`FUN_0043dee3`, bit k -> frame k+1; 0 -> TEMPHOLE/NOKNOW)
et porte aussi d'autres drapeaux (0x4..0x2000 lus par `FUN_0041fde6`, `FUN_00420721`, `FUN_00420f28`, `FUN_00422d27`, `FUN_0045d9c1`, `FUN_0045dd3c`, `FUN_00440567`). Seul écrivain: `FUN_004503bd`
(14 sites octets décodés), bit = indice d'île. La rectification précédente est à ignorer; le port maintient `glyph_mask` et `special_feature_island_mask` ensemble.

État 3 (REA, ev_49f6c42a…, ev_169fcebf…, ev_fb2899df…, ev_2d44d75f…): dans `FUN_004503bd`, `rec` n'est pas le site mais l'**objet par joueur** (`0x6191b8 + P*0x14a0`, `P = param_3`; `rec+8` = île, `rec+0x8a` = masque d'îles parcouru par `FUN_00460072`); le site est `S = IB + X*0x60 + 0x428`.
Transitions d'état de `rec+0x10`: 0 -> 1 dans `FUN_004503bd` (action 1 ou 4 < action < 0x22: `rec+0x24 = action`, `rec+0x14 = P` si -1); cas 1 sans transition; cas 2 (action 5: `rec+0x2c`, drapeau 4, `rec+0x40 = 0`) sans transition;
cas 3 n'écrit jamais `rec+0x10`. Les transitions 1 -> 2 -> 3 ne sont pas dans cette fonction; aucune écriture immédiate de 3 dans `.text` (0 résultat pour `C7 ?? 10 03 00 00 00`); seule candidate pour l'état 2: `0x463c96` (immédiat 2 dans `FUN_004637fc`, registre de base non décodé).
`FUN_00460072` pose l'état du site à 1 et `S+0x24 = 2B+6+côté` (le côté est dans le code, pas dans `+0x4a`). Appelants de `FUN_004503bd`: aucun résolu (appel indirect). Inconnues: écrivain de `rec+0x10 == 2/3` (probablement non immédiat), écrivain de `rec+0x4a`.

Écriture de l'état 2 (REA, ev_0ad75c66…, ev_c42e6e1b…): `FUN_004637fc` à `0x463c96` fait `mov dword [site+0x10], 2` pour **tous les sites de classe 2** (`site+4 == 2`) de chaque île au démarrage du monde (boucle `k < word[île+0x29a8]`), sans transition; l'écriture à `0x464136`
pose 1 (`+4 == 0`, `+0x14 == -1`, `+0x10 == 0`, `+0x24 = pair[k]+6`). Donc l'état 2 est un état initial des sites de classe 2, pas une étape de progression du joueur. Aucun incrément mémoire ni immédiat vers 3 (motifs `FF ?? 10`, `83 40 10 01`, `C7 ?? 10 03`, `B8 03…`: 0 résultat); les trois `83 ?? 10 01`
(`0x41eb58`, `0x450a9f`, `0x44066f`) et les `89 ?? 10` (store registre) restent à décoder. Rectifie la phrase « aucune écriture de 2 » plus haut: seul 3 reste sans écrivain trouvé.

État 3 résolu (REA, ev_af836582…, ev_342b57c4…, ev_a9362b0f…, ev_3fc8feca…): le chargeur d'île `FUN_00461b3b` (`0x461fed`: `mov [edx+0x10], eax`, `eax = [ebp-0xe4]`) écrit `+0x10 = 3` pour les enregistrements de type `feattrig` (chaîne `0x4a4c5c`; classe `[ebp-0x9c] = 3`),
`4` pour `feature` (`0x4a4c54`) et `0x16` pour `levhub` (`0x4a4c44`), sur le site `IB + 0x428 + k*0x60`. Les sites « paire » (`feattrig`, classe 3, `+0x10 = 3`) reçoivent donc leur état 3 **du fichier `ISLANDnn.TXT` au chargement**, sans transition de jeu;
cela correspond au port (`renderer_class == 3 && record_value_10 == 3` pour la paire, `== 4` pour le site central `feature`). Il n'y a donc pas d'écrivain d'exécution à chercher. Les trois `83 ?? 10 01` sont des `cmp`. Restent inconnus les appelants de `FUN_00461b3b`/`FUN_004528ca`/`FUN_00462a87` (indirects).

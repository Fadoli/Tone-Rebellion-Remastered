# Taches et construction

**Garde-fou du remake :** avant d'afficher les rangées, la vue recalcule son offset maximal à partir du nombre courant de tâches. Si des tâches disparaissent alors que la liste est défilée, l'affichage revient à la dernière page valide. Le binaire montre le défilement borné, mais cette mise à jour après retrait asynchrone n'est pas établie séparément.

- **Tasks — observation Ghidra / port.** `FUN_00465793` applique les sous-types 13–15 comme priorité 1–3; sous-type 12 annule le slot si l’identité (joueur, payload +0xa, action, payload +0x12) correspond. `FUN_00466533` met le propriétaire du site de type 5 à -1 quand son statut vaut 0 ou 1. Le port vérifie les bornes; l’annulation nettoie aussi le lien de demande de réserve modélisé par joueur. Les références de floaters et autres tables de `FUN_0045fb6f` restent hors modèle. Evidence `ev_90fc7b398e8cc430ee898f0371c196e285bf0f21c5cd78aa04fcdd060294d4ce`, `ev_773b697a9733f2af54299261e5decab66b31c9e02a7c738831cb7827c01b06d6`, `ev_60c18846051d1c9de7f9c0bb3864f2011570ff4b4dc637ff583c252cc3261ec3`, `ev_fe6bd972740d099ab62aab1ef94df71e686f886cba296a0ba805cba982259d2f`.

- `FUN_004459e6` traite `CONSTR` (5) et `REPAIR` (`0x12`) avec la cible `+0x0a` = île et `+0x0e` = emplacement. `CONSTR` compare le mot runtime `+0x28` au coût `pad.txt +0x04` résolu par `FUN_004641de(joueur,payload+0x12)`; `REPAIR` compare `+0x34` à `FUN_00450978`. Les deux rendent `TASKICON` frame 9 (70×7, inset 2), ratio plafonné à 1. Le remake porte les deux jauges; il ne produit pas encore les tâches de construction et la valeur REPAIR reste initialisée faute de simulation. `FUN_00450978` ajoute runtime `+0x4a × 5` au 7e entier de `pad.txt`, stocké au record `+0x0e` par `FUN_0046303b`. **Interprétation du modèle :** cet entier est nommé `hit_points`; le sens de la formule reste à confirmer. Evidences `ev_fe6bd972740d099ab62aab1ef94df71e686f886cba296a0ba805cba982259d2f`, `ev_f92b05e1bac76d2be3a91b76e6eb420474e1d04db600d49cc8d4a55edf30587d`, `ev_c050c8da1c727f3840e46ba700e9d2c54ff80d0a24c9a1e397b5340b16c95f7e`, `ev_f43c86a4fb902537253e5af3631a3875fbaf57fbb356887e3d1e995894c6114b`, `ev_c376abd7d000e38d788e4baf135389849cfd5bead8b071e126a93ae114385825`, `ev_1e9e2b997d11c89a045e32925f3af8bee4aefadf27400aad1545da2b7eb86f8f`.

Le cœur expose aussi ces valeurs par île/emplacement sans exiger un slot REPAIR actif. Le remake dessine et consomme `BC_Repair`, mais ne déclenche pas de réparation tant que son dispatcher virtuel et le producteur de tâche `0x12` ne sont pas reliés; voir [la note du contrôle Repair](island-repair-control.md).

- **Producteur `REPAIR` — recherche bornée, sans producteur confirmé.** Les xrefs montrent quatre appels au thunk d’allocation `FUN_004662b7`; les call-sites décompilés correspondent à une requête type `0xb`, deux chemins type `4`, et au dispatcher `FUN_00465793`. Dans ce dispatcher, la branche catégorie 0 alloue le paquet reçu; la branche catégorie 3/sous-type 3 écrit l’action `0x13`. Aucun de ces pseudocodes n’établit la production d’une action `0x12`. Le prochain point de recherche est la construction des paquets d’entrée de `FUN_00465793`, en particulier leur catégorie 0. Evidence `ev_94ae6309765462f4b0754b9d82b62f90adcc275c1c5d7989b0bc32ffb24eb706`, `ev_1db56eabc3b5e97f374c5e64d2fb1a2bc2beab55a5ceba3f76b1b4d5e0eb14bd`, `ev_8dc22cee77c45869eec774b96c98814c0171a67168ce8264bff2bf19d0b115cb`, `ev_e1e66e59162f5b559a5511e6f90a9594a62333770e5d6672bae0ece372467037`, `ev_567770ed791b088a16c09fe59341074d8dd8e4f89bbe009d96603024f13a68f7`.

- **Observation Ghidra :** la tâche dont le slot égale `+0xf4` remappe le framebuffer sous le masque du panneau `TEMPHOLE` sur une bande de 13 px commençant 3 px avant la rangée; la table vient de `FUN_004106dd(1,1)`. **Port :** le remake applique sa LUT HZT blanche niveau 1 à cette bande, géométrie couverte par test. Evidences `ev_fe6bd972740d099ab62aab1ef94df71e686f886cba296a0ba805cba982259d2f`, `ev_92b1f53b9bea0cdd105ea797aafe454686d75cb0ff17e10a6e793201a87751da`, `ev_5dee659e6ca6ce0decafdf17f8c960d7218ffeb39dac103e234aace22ceea725`.

- **Rafraîchissement — observation Ghidra :** `FUN_004459e6` peint seulement les rangées visibles, mais la cadence de son appel reste inconnue; callers incomplets (`ev_5f40796…`, `ev_379a565…`). **Politique du remake :** la simulation et le rendu complet sont à 30 Hz, y compris avec Tasks ouvert; voir [compte des peintures](../ToneRebellion_Remake/bench/task-render-cadence.md).

- **Détail d’artefact Tasks — observation et port.** `FUN_004469d6` mappe les IDs 5–33 des tâches type 4/0xd vers les cadres `TRIGGERS` 0–28, puis place l’image avec les coordonnées de `FUN_004119ba` (`ev_af646caa747aeb02c1e96bdd6b32f50f4f6ca5d96ccacac948648818fb9f8bc4`, `ev_393ddd67e73634646c721faf8d924123cca267f4086a6f25c7175d044c47f343`). `archive_index.jsonl` et `shapes.txt` identifient cette feuille comme `data\\alltrigs.shp` (`TONE01.COB`, membre 3). Le remake affiche maintenant le cadre correspondant dans `IWTaskInfo`; mapping et position sont testés dans `test_island_panel_info`. Les règles de progression/traitement de la tâche restent hors de ce port.

- **Aperçu de cible Tasks — observation Ghidra :** `FUN_004469d6` atteint l’aperçu commun pour les types 4/`0xd`, puis appelle `FUN_0040bf98` à `pane-local (largeur−30, hauteur−10)`, échelle `0x8000`, seulement si le dword runtime cible `+4` vaut 0 (Evidence `ev_af646caa747aeb02c1e96bdd6b32f50f4f6ca5d96ccacac948648818fb9f8bc4`). La branche type 5 dessine son aperçu séparément et quitte. **Interprétation de port :** l’offset correspond à `GameRuntimeLocation.owner_id` d’après l’implantation du record et ses initialisations; le remake garde donc la même sélection de branche. Types, propriétaire et position sont testés; l’animation source complète n’est pas reproduite.

- **SUPPLY/UPGRADE — limite vérifiée :** le caller passe à `FUN_00450385` un pointeur de slot; `FUN_004455d1` confirme des slots espacés de `0x14`, tandis que le helper lit `+0x14/+0x18`. Ces valeurs dépassent la ligne, leur sens n’est pas établi; ne pas les mapper au `GameSession`. Branches identifiées, port en attente (Evidence `ev_adf213374270c0df1da49c26400e5f91c67256a8478ec81e5473415a6b68e11d`, `ev_bc320115f0f140331cab5bd3c6af1bb19d2505748d9aa0d0e1ae63d7addc020b`, helper `ev_b003c4e2130a4f653012f553ad5cdf8222b961d4c5b48c785fd40fdd3404ada2`).

- La création instantanée d'un bâtiment par le chemin de placement actuel est une approximation à remplacer. `FUN_0045da80` attribue `FA_Cast` (`0x13`), pas une construction; `FUN_004211bb` consomme les ordres, `FUN_0041e569` exécute les états et `FUN_004527ee` valide une création sur site, mais le lien entre `FA_Build` et ce validateur n'est pas raccordé. Les transitions complètes d'aller-arrivée et les champs exacts de coût/stock restent à établir. `FUN_0042219e` montre une logique périodique de tâches; les trajectoires des ouvriers inoccupés ne sont pas encore établies. Le mode 2 de `FUN_0045eaa7` déclenche une requête de remplissage, mais son affectation et son trajet restent à reconstruire. Stocks initiaux, capacités et coûts restent incomplets.

## Revue du peintre `FUN_004459e6` (REA, ev_6e4ef728…, ev_4917da8e…)

Concordances: pas de ligne 13, icône x=25, libellé x=45, icône ressource x=135 (y+7),
icône secondaire x=150, jauge x=170 (frame 9, 70x7, marge 2), surbrillance y-3 sur
13 px, formule de la première ligne `(H - visibles*13)/2`.
Corrigé: la jauge remplit `ftol(66 * ratio)` avec `__ftol` (`0x472c6c`) en mode troncature
(contrôle x87 « chop »), pas à l'arrondi au plus proche: 3/4 donne 49 px, non 50;
`island_panel_info_task_gauge_fill` et `island_panel_info_stock_gauge_fill` tronquent
désormais (un attendu de test passe de 18 à 17, non exécuté ici).
Écarts restants: le compteur `[%d]` à x=5 de chaque ligne (valeur `task+4`) n'est pas
dessiné; les types non cartographiés sont dessinés avec le nom `FA_*` brut au lieu d'être
omis; libellés `UPGRADE`, `UPGSPREAD`, `SUPPLY` (icônes 2/2/5-6) absents; jauges natives
pour CONSTR, REPAIR, STOCK, UPGRADE et SUPPLY quand la valeur vaut autre chose que -1 (le
port filtre CONSTR par taille/disponibilité); fraction négative non tracée; sélection
sans repli sur la première ligne dans le natif (non revérifié).
Inconnues: couleur de texte, défilement (`6000/6001`), `FUN_004469d6` (NOTASKS).

### Compteur `[%d]` et lignes UPGRADE/UPGSPREAD/SUPPLY (REA, ev_b62a7744…, ev_00eb9608…, ev_b81bb819…)

Observation: `FUN_004662b7` écrit l'enregistrement de tâche (0x14 octets): `+0` actif, `+4`
= 0, `+6` priorité = 1, `+8` joueur, `+0x10` type, `+0xa/+0xc/+0xe/+0x12` charges.
Seul `FUN_00421ec1` (méthode floater, `+0x38` = index de tâche attachée) modifie ce
compteur: +1 à l'attache, -1 au détachement. Inférence forte: `task+4` = nombre de
floaters attachés à la tâche. Port: `[n]` est dessiné en x=5 sur chaque ligne avec n =
floaters dont `linked_task_slot` désigne la tâche (le champ `assigned_floater_count`
de `GamePendingEvent` n'a pas d'écrivain dans le port, donc on compte à l'affichage).
Type 4 du peintre, dans l'ordre: REPAIR (sous-type 1 et `FUN_0045ff3f`), UPGSPREAD
(sous-type 1 et `FUN_0045ff6d`, icône 2, numérateur `FUN_0045fcbe+8`, dénominateur 10),
puis selon `FUN_00450385`: nul → STOCK (item 0x2a, icône 3, secondaire 7) ou DARTIFACT
(sous-type 5..0x21, icône 4); non nul → icône secondaire `(+0x10 == 0x2f) + 5`, puis
SUPPLY (`FUN_0045c9fe == 0` ou sous-type != 1: icône 3, dénominateur `FUN_0045cd27`,
numérateur `+0x2a` ou `+0x2c`) ou UPGRADE (`FUN_0045c9fe != 0` et sous-type 1: icône
2, numérateur `+0x28`, dénominateur 20). Clés `gamey.txt`: CONSTR, REPAIR, UPGRADE,
SUPPLY, UPGSPREAD. Le port génère UPGRADE (`game_session_toggle_staff_upgrade_request`)
mais le sous-type 1 est partagé avec d'autres tâches, et aucune tâche SUPPLY ou UPGSPREAD
n'existe dans le port. Non porté: ces lignes (prédicats `FUN_0045ff3f/6d`, `FUN_0045c9fe`
non décompilés; `island_panel_info_task_row` ne reçoit ni l'item du site ni son sous-type).

### Prédicats des lignes de tâches (REA, ev_dfe2cb4b…, ev_6cd3f421…, ev_c3ae4d74…) et ligne UPGRADE portée

Observation: `FUN_0045fcbe(île, site, genre)` cherche dans une table de 16 entrées (5 shorts,
`this+0x13dc`: île, site, genre, tâche, compteur) la première entrée active; `FUN_0045ff3f` teste
le genre 0 (REPAIR) et `FUN_0045ff6d` le genre 1 (UPGSPREAD, compteur `+8` sur 10, terminé à 10
livraisons de ressource 1 sur un bloc de type 0x28). `FUN_0045c9fe` vaut `bloc+0x4e != -1`
(requête UPGRADE en cours); `FUN_0045c9b5` crée cette requête (porte `FUN_0045c89b` non
décodée) et `FUN_0045cd27` donne `50 + 25*(bloc+0x4a)`. Création: paquet catégorie 1 sous-type
2 (bascule UPGRADE), catégorie 1 sous-type 3 (bascule REPAIR), catégorie 2 sous-type 0x14
(bascule UPGSPREAD).
Port: la ligne UPGRADE (tâche action 4, `payload_12 == 1`, site dans `payload_0a/0e`) est
maintenant dessinée: libellé `UPGRADE` (`gamey.txt`), icône 2, icône secondaire
`(item == 0x2f) + 5`, icône bildtone et jauge `stock[0] / 20` tronquée. Avant, ces tâches
étaient écartées car `island_panel_info_task_row(4, 1)` n'a pas de ligne. Non porté: SUPPLY,
UPGSPREAD et la table d'entrées de genre 0/1 (aucune création ni progression dans le port;
la progression REPAIR par `+0x34` n'est pas portée non plus), l'association exacte des
boutons `BC_*` aux paquets, la porte `FUN_0045c89b`.

### Commandes de bâtiment `BC_*`, porte UPGRADE et entrées REPAIR/UPGSPREAD (REA, ev_eb5d3a74…, ev_872c7ebd…, ev_dd032f8d…)

Observation: dans `windows.txt`, chaque `BC_*` (OnOff, Move, Upgrade, Repair, Obtain, TrnStkC/M,
HallStkB/C/M, UpgSpread, Spell1..8) envoie `SENDMESSAGE 101 0 0` à `MASTER`; `IWMove`/`IWHallMove`
envoient `0 0 0`. `FUN_00440567` enregistre ces contrôles par `FUN_0046c3bc(nom, 0x0b, 0, 0)`;
le clic passe par `FUN_004293c6` (cas 6/7) puis `FUN_0042970c`/`FUN_0046c402`, qui appelle le
rappel de la fenêtre active. Le message est identique pour tous: la catégorie et le sous-type
du paquet (par ex. bascule UPGRADE = catégorie 1 sous-type 2) sont choisis dans le rappel côté
MASTER (table d'exécution, non résolue). La correspondance bouton → paquet n'est donc pas
établie par cette trace.
`FUN_0045c89b` (porte de la requête UPGRADE): type du bloc `0x2c..0x2f` (T = type - 0x2c),
niveau L = `+0x4a + 1` ≤ `{2,2,1,2}[T]`, N = nombre d'îles où l'entier par propriétaire de
`DAT_005eebc4` est non nul, vrai si `seuil[L + 3T] <= N` avec les tables de seuils par
`DAT_006136b2` (0 / 1 / autre): le port les reproduit (`staff_upgrade_eligible`), à ces écarts
près: il exige propriétaire = joueur et classe 0 (absents du natif), utilise l'item de base, et
rejette `world >= 3` alors que le natif range `>= 2` ensemble; `FUN_0045c9b5` ne fait que créer
la requête (le port peut aussi l'annuler).
`FUN_00452bc5(p)` (porte UPGSPREAD): bloc de type `0x28`, propriétaire 0..3, bit p de `+0x22`,
drapeau `0x800<<p` absent; `FUN_0045fe62` crée l'entrée de genre 1 (île, site, 1, tâche, 0);
`FUN_0045fd91` crée celle de genre 0 (REPAIR) sans contrôle de type. Le port n'a pas cette
table.

### Message 101 et commandes `BC_*` dans `FUN_0042fa0f` (REA, ev_ed75141a…, ev_e0b600c3…, ev_882b587e…)

Observation: pour le message `0x65`, `param_2` est `p1`, pas l'enregistrement du contrôle (les
enregistrements sont passés pour les messages 5/6). Cas de `p1` (lignes de la fonction
extraite): 0, 2, 3 construisent un paquet de 16 octets (type 1, sous-type = `p1`, joueur
`DAT_0049f538`, site sélectionné, valeur `FUN_0045035a()`), envoyé par `FUN_00414081(1, buf,
0x10)`: lecture « OnOff » (sous-type 0), « bascule UPGRADE » (2), « bascule REPAIR » (3),
déduite des valeurs de sous-type; 4 relance le message `0x39`; 5 et 6 (porte
`FUN_00450385 != 0`) et 7..9 émettent `FUN_004354a2(3, 2, …, p1-5 ou p1-7)`; `0xb..0xe` n'ont
qu'un effet d'interface (sélection de `BC_HallStk*`); `0xf` émet un paquet de sous-type 0xf
(porte `FUN_00450385`); `0x10..0x13` lancent l'action locale `FUN_0043530b`; `0x14` envoie le
paquet type 2 sous-type 0x14 (bascule UPGSPREAD, sans porte); `0x15..0x1c` choisissent par
`DAT_004a2898[FUN_00450070(site, p1)]` entre un paquet de sort (sous-type = `p1`) et l'action
locale `FUN_0043530b`.
Contradiction non résolue: `windows.txt` donne `SENDMESSAGE 101 0 0` à tous les `BC_*` (donc
`p1 = 0` partout), ce qui enverrait chaque clic au cas 0 (OnOff). Soit le rappel MASTER de
`IWLocInfo` n'est pas `FUN_0042fa0f`, soit `p1` est réécrit à l'exécution (introuvable dans
`FUN_00440567` et `FUN_0046cd22`). Le tableau bouton → paquet reste donc non établi.
Port: routes présentes pour OnOff (`game_session_queue_onoff_action`), bascule UPGRADE
(`game_session_toggle_staff_upgrade_request`) et sorts (`game_session_queue_cast_action`);
REPAIR est une tâche locale type 0x12 et non un paquet; aucune route pour UPGSPREAD, Obtain,
Move (paquets), TrnStk ni pile de Hall (dessin et survol seulement).

### Résolution: `SendParam1` des `BC_*` et visibilité (REA, ev_0c440708…, ev_444f22b6…, ev_ad688265…)

Observation: `windows.txt` précise que le `SendParam1` des boutons de bâtiment est réglé par la
fonction maître de l'île. `FUN_0042f150` (`islemast.cpp`, exécutée quand `DAT_0049e9bc == 1`)
parcourt la table de 29 noms à `0x49e700` (pas 0x14), retrouve chaque contrôle par
`FUN_0046c4a5` et écrit son index dans `+0x64`; le `p1 = 0` du fichier est donc remplacé une
fois à l'initialisation. Ce qui lève la contradiction de la section précédente. Indices:
OnOff 0, Move 1, Upgrade 2, Repair 3, Obtain 4, TrnStkC 5, TrnStkM 6, HallStkB/C/M 7..9,
GenInfo 10, Storage 11, Knowledge 12, Trade 13, Diplomacy 14, Recall 15, AttackFlt 16,
AttackLoc 17, DefendFlt 18, DefendArea 19, UpgSpread 20, Spell1..8 = 21..28. Correction: les
cas `0xb..0xe` de `FUN_0042fa0f` sont Storage/Knowledge/Trade/Diplomacy (interface seule) et
`0x10..0x13` sont AttackFlt/AttackLoc/DefendFlt/DefendArea; HallStk vaut 7..9.
Visibilité: `FUN_0042f9c5` cache les 29 contrôles, `FUN_0042f755(site, drapeau)` montre ceux de
la liste construite par `FUN_0045302a(joueur, liste, &compte)` (pour les sorts, il envoie
d'abord `msg 0xc` avec `FUN_00450070 << 1`). Liste par bâtiment B (`+4 == 0`, type T, propriétaire
O, emplacement `+0x18`, sous-type S): T == 1 et 4 < S < 0x22 → Obtain; T >= 0x25 et != 0x2a →
Repair (tout propriétaire, sans test de points de vie); T == 0x28 et O != joueur et drapeau
`0x1000 << joueur` absent → UpgSpread; O == joueur et T 0x25..0x27 → OnOff; O == joueur et T ==
0x2a → indices 7..14; O == joueur avec emplacement != -1: toujours TrnStkC (5) et Upgrade (2),
types 0x2c..0x2e + Attack/Defend/Recall (16..19, 15), types 0x2f et 0x30 + TrnStkM (6) et les
sorts 21..28. Move n'est jamais produit par ces fonctions.
Comparaison avec le port: OnOff concorde; Repair diffère (le port exige propriétaire, points
de vie < max et inclut 0x2a, le natif non); Upgrade diffère (le port limite à `0x2a` et
`0x2c..0x30`, le natif donne Upgrade à tout bâtiment possédé avec emplacement, la porte de type
passant par `FUN_0045c3bb`); UpgSpread, Obtain, Move, TrnStk, Recall, Attack/Defend n'ont pas de
règle de visibilité dans le port. Réserves: `FUN_0045c3bb`, le drapeau `0x1000<<P` face à
`0x800<<p` de `FUN_00452bc5`, l'appelant de `FUN_0042f303`. Je n'ai pas modifié les règles du port
(elles reposent sur d'autres traces: tâches REPAIR et requêtes UPGRADE) avant de les recouper.

### Activation et dessin des boutons `BC_*` (REA, ev_141bcbe0…, ev_85c2d07b…, ev_7e307bdf…, ev_b3d14921…)

Observation: `FUN_004293c6` (bouton générique) n'a pas de code de dessin: message 1 montre
(`+0x34 = +0x38 = +0x3c = 1`), 2 cache, 3 active (`+0x38`), 4 désactive, 6/7 clic (sans
test de `+0x38`), 8/9 survol ou pression (cadre `+0x34 = 3/2` seulement si `+0x3c`, `+0x38` et
`+0x44`), `0xc` fixe le cadre de base `+0x1e`. `FUN_0042a55d` dessine seulement si `+0x34` et
`+0x3c`, cadre = `+0x1e + +0x72`, puis remet `+0x34` à 0; elle ne lit jamais `+0x38`.
`FUN_00442799` (appelants non résolus, liaison à un contrôle précis non établie) active quand
l'objet a un emplacement et que `FUN_0045c89b` est vrai, avance le compteur d'animation `+0x72`
aux ticks impairs si une requête UPGRADE est en cours, sinon le remet à 0. `FUN_0045f337` est un
test de candidat de tâche, pas une activation de bouton (inférence).
Conclusion: aucun état « visible mais grisé » n'est décodé; le modèle visible/caché du port est
juste. Les règles de visibilité du port ne sont pas la liste native: Repair exige propriétaire et
points de vie sous le maximum (reprend le test de clic de `FUN_00442c21`, qui vérifie joueur 0..3,
item 0x25..0x34 et `+0x34 < maximum`), alors que la liste de `FUN_0045302a` montre Repair pour
tout bâtiment `T >= 0x25` hors `0x2a`; Upgrade exige l'item 0x2a ou `0x2c..0x30`, alors que
`FUN_0045c89b` n'accepte que `0x2c..0x2f` et que la liste donne Upgrade à tout bâtiment possédé
avec emplacement. Le port approxime donc « bouton montré » par « action possible ». Non changé:
les règles du port, faute de preuve de l'écran natif; l'écart est consigné ici.
Inconnues: contrôle rafraîchi par `FUN_00442799`, valeurs de cadre de base (`+0x1e`) des boutons
hors sorts, signification de `L+0x70`, refresh propre à Repair.

### Boutons de bâtiment sans route dans le port (REA, ev_b9bc79db…, ev_1f76cc3b…, ev_0bfe4a9d…, ev_349b14e0…)

Observation: `FUN_004354a2` empile un paquet de 16 octets (mots: catégorie, joueur `DAT_0049f538`, sous-type,
île, emplacement, deux charges). `TrnStkC`/`TrnStkM` (`p1` 5/6, porte `FUN_00450385`) envoient la catégorie 3,
sous-type 2, avec le bâtiment; le consommateur bascule un drapeau par bâtiment d'entraînement en
`+0x58` (cristal) ou `+0x5c` (magique) du bloc propriétaire (`+0x2d098 + emplacement*100`). `HallStkB/C/M`
(`p1` 7..9) envoient la même catégorie sans bâtiment: `FUN_0045f755` fait cycler (mod 3, valeur -1 = suivant) le
mode de pile de la ressource 0/1/2 à `+0x13d0 + 2*ressource` dans l'objet joueur (même base `0x6191b8 +
joueur*0x14a0` que la table `+0x13dc`): c'est le cycle de modes déjà modélisé par joueur dans le port
(`game_session_cycle_resource_stock_mode`). `Obtain` (`p1` 4) renvoie le message `0x39` puis `FUN_0042f303(0)`;
`0x39` envoie un paquet de catégorie 0, type 0xd (13), site et sous-type d'objet, que `FUN_004662b7` range comme
tâche de type 0xd (dédoublonnée: un second ordre identique l'annule); le port a l'ordre de ramassage par clic
droit (`game_session_order_floater_to_ground_object`) mais pas ce bouton. `Attack`/`Defend` (`p1` 0x10..0x13)
règlent seulement le curseur (`FUN_0043530b`); le clic de carte suivant (message `0x40`) envoie un paquet de
catégorie 1 (sous-type = mode) que `FUN_0045d867` (cibles floater, genres 6 attaque et 8 défense) et `FUN_0045d8b2`
(cibles de lieu, genres 7 et 9) transforment en ordre en attente; `Recall` (`p1` 0xf) passe par `FUN_0045dcf4`
(genre 9, île du bâtiment), même genre que `DefendArea`.
Port: pas de drapeaux d'entraînement (`TrnStk`), pas de `Recall`, pas de bouton `Obtain`, pas de `UpgSpread`,
`defend_target_floater` jamais affecté. Non résolu: sens des modes de pile 0/1/2 et lecteurs de `+0x13d0`, `+0x58` et
`+0x5c`, exécuteur de la tâche 0xd, table de cibles à pas 0x4c, ambiguïté du genre 9 (Recall et DefendArea).

### Couleur des lignes de tâche (REA, ev_956729d2…, ev_24aea2d9…, ev_3a54fb09…, ev_e1a8ee2b…)

Observation: dans `FUN_004459e6`, la couleur du texte ne dépend que de la priorité `task+6`: priorité 2 écrit l'indice 5
(`FUN_0042dd0f(5)`) dans l'objet `smfont`, priorité 3 l'indice 2, les autres gardent l'indice 6; chaque ligne finit par
`FUN_0042dd0f(6)`. L'ordre est: icône, jauge (couleur 0 passée en argument), couleur de priorité, libellé (x = 45) puis
compteur `[n]` (x = 5), restauration. Ni la sélection, ni un manque de ressources, ni le nombre de floaters ne changent
la couleur. `FUN_0042dd0f(n)` renvoie `DAT_0049e140[n]` (identité de 0 à 6). La surbrillance de la ligne (`FUN_004109a6`) se
déclenche sur `pane+0xf4 == tâche` et remappe les pixels non transparents du cadre par la table `FUN_004106dd(1,1)`
(valeurs non lues). Palette `ISLAND00.PAL` (6 bits): indice 2 (63, 63, 35), 5 (48, 37, 16), 6 (42, 29, 14) (conversion x4
non localisée côté port).
Port: libellé et compteur d'une ligne prennent `g_island_palette[5]` (priorité 2), `[2]` (priorité 3) ou `[6]`.

Précision (relecture du code du port): la surbrillance de la ligne sélectionnée est déjà le remappage de `FUN_004106dd(1, 1)`
(banque « haze » 1, niveau 1), calculé par `island_haze_remap` pour chaque indice de palette dans
`rebuild_island_palette_lookup`; la mention « valeurs non lues » ci-dessus décrit seulement ma lecture du binaire.

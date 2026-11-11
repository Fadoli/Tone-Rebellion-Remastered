# Taches et construction

**Garde-fou du remake :** avant d'afficher les rangées, la vue recalcule son offset maximal à partir du nombre courant de tâches. Si des tâches disparaissent alors que la liste est défilée, l'affichage revient à la dernière page valide. Le binaire montre le défilement borné, mais cette mise à jour après retrait asynchrone n'est pas établie séparément.

- **Tasks — observation Ghidra / port.** `FUN_00465793` applique les sous-types 13–15 comme priorité 1–3; sous-type 12 annule le slot si l’identité (joueur, payload +0xa, action, payload +0x12) correspond. `FUN_00466533` met le propriétaire du site de type 5 à -1 quand son statut vaut 0 ou 1. Le port vérifie les bornes; l’annulation nettoie aussi le lien de demande de réserve modélisé par joueur. Les références de floaters et autres tables de `FUN_0045fb6f` restent hors modèle. Evidence `ev_90fc7b398e8cc430ee898f0371c196e285bf0f21c5cd78aa04fcdd060294d4ce`, `ev_773b697a9733f2af54299261e5decab66b31c9e02a7c738831cb7827c01b06d6`, `ev_60c18846051d1c9de7f9c0bb3864f2011570ff4b4dc637ff583c252cc3261ec3`, `ev_fe6bd972740d099ab62aab1ef94df71e686f886cba296a0ba805cba982259d2f`.

- `FUN_004459e6` traite `CONSTR` (5) et `REPAIR` (`0x12`) avec la cible `+0x0a` = île et `+0x0e` = emplacement. `CONSTR` compare le mot runtime `+0x28` au coût `pad.txt +0x04` résolu par `FUN_004641de(joueur,payload+0x12)`; `REPAIR` compare `+0x34` à `FUN_00450978`. Les deux rendent `TASKICON` frame 9 (70×7, inset 2), ratio plafonné à 1. Le remake porte les deux jauges; il ne produit pas encore les tâches de construction et la valeur REPAIR reste initialisée faute de simulation. `FUN_00450978` ajoute runtime `+0x4a × 5` au 7e entier de `pad.txt`, stocké au record `+0x0e` par `FUN_0046303b`. **Interprétation du modèle :** cet entier est nommé `hit_points`; le sens de la formule reste à confirmer. Evidences `ev_fe6bd972740d099ab62aab1ef94df71e686f886cba296a0ba805cba982259d2f`, `ev_f92b05e1bac76d2be3a91b76e6eb420474e1d04db600d49cc8d4a55edf30587d`, `ev_c050c8da1c727f3840e46ba700e9d2c54ff80d0a24c9a1e397b5340b16c95f7e`, `ev_f43c86a4fb902537253e5af3631a3875fbaf57fbb356887e3d1e995894c6114b`, `ev_c376abd7d000e38d788e4baf135389849cfd5bead8b071e126a93ae114385825`, `ev_1e9e2b997d11c89a045e32925f3af8bee4aefadf27400aad1545da2b7eb86f8f`.

Le cœur expose aussi ces valeurs par île/emplacement sans exiger un slot REPAIR actif. Le remake dessine et consomme `BC_Repair`, mais ne déclenche pas de réparation tant que son dispatcher virtuel et le producteur de tâche `0x12` ne sont pas reliés; voir [la note du contrôle Repair](island-repair-control.md).

- **Producteur `REPAIR` — recherche bornée, sans producteur confirmé.** Les xrefs montrent quatre appels au thunk d’allocation `FUN_004662b7`; les call-sites décompilés correspondent à une requête type `0xb`, deux chemins type `4`, et au dispatcher `FUN_00465793`. Dans ce dispatcher, la branche catégorie 0 alloue le paquet reçu; la branche catégorie 3/sous-type 3 écrit l’action `0x13`. Aucun de ces pseudocodes n’établit la production d’une action `0x12`. Le prochain point de recherche est la construction des paquets d’entrée de `FUN_00465793`, en particulier leur catégorie 0. Evidence `ev_94ae6309765462f4b0754b9d82b62f90adcc275c1c5d7989b0bc32ffb24eb706`, `ev_1db56eabc3b5e97f374c5e64d2fb1a2bc2beab55a5ceba3f76b1b4d5e0eb14bd`, `ev_8dc22cee77c45869eec774b96c98814c0171a67168ce8264bff2bf19d0b115cb`, `ev_e1e66e59162f5b559a5511e6f90a9594a62333770e5d6672bae0ece372467037`, `ev_567770ed791b088a16c09fe59341074d8dd8e4f89bbe009d96603024f13a68f7`.

- **Observation Ghidra :** la tâche dont le slot égale `+0xf4` remappe le framebuffer sous le masque du panneau `TEMPHOLE` sur une bande de 13 px commençant 3 px avant la rangée; la table vient de `FUN_004106dd(1,1)`. **Port :** le remake applique sa LUT HZT blanche niveau 1 à cette bande, géométrie couverte par test. Evidences `ev_fe6bd972740d099ab62aab1ef94df71e686f886cba296a0ba805cba982259d2f`, `ev_92b1f53b9bea0cdd105ea797aafe454686d75cb0ff17e10a6e793201a87751da`, `ev_5dee659e6ca6ce0decafdf17f8c960d7218ffeb39dac103e234aace22ceea725`.

- **Rafraîchissement — observation Ghidra :** `FUN_004459e6` peint seulement les rangées visibles, mais la cadence de son appel reste inconnue; callers incomplets (`ev_5f40796…`, `ev_379a565…`). **Politique du remake :** la simulation et le rendu complet sont à 30 Hz, y compris avec Tasks ouvert.

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

### Ligne SUPPLY portée

Observation (pseudocode stocké de `FUN_004459e6`; asm `FUN_00440567` 0x440881/0x4409e6):
l'ECX de `FUN_0045cd27` est le bloc staff de `FUN_00450385`, dont `+0/+2` désignent le
bâtiment lui-même (`FUN_0045c325`): la capacité est 50 + 25*(`+0x4a` du bâtiment).
Port: les tâches type 4, payload 2/3, sur un site à bloc staff (`+0x18 != -1`) sont
dessinées en SUPPLY (`gamey.txt`), icône 3, secondaire `(item == 0x2f) + 5`,
tonecrys/magctone et jauge `+0x2a`/`+0x2c` sur cette capacité (avant: STOCK sans jauge).
SUPPLY pour payload 1 sans UPGRADE en cours (`FUN_0045c9fe == 0`, lien `+0x4e == -1`, `ev_639bf60d…`, REA haiku 2026-10-31, non relue) : porté dans le rendu Tasks (branche magie `+0x2c`, magctone, sous-type != 2); le port ne produit pas ce cas (une tâche sous-type 1 garde son lien), donc il ne sert qu'aux sauvegardes natives ou liens perdus. Producteurs type 4 (`FUN_004666c9`, appelants `0x45c9b5` UPGRADE, `0x45cc17` SUPPLY 2/3 par tick `FUN_0045cd75`, `0x45fd91` REPAIR genre 0, `0x45fe62` UPGSPREAD genre 1) et table `FUN_0045fcbe` (16 entrées de 10 octets: propriétaire, île, genre, slot -1 = vide) lus; le port encode le slot en +1 (0 = vide) et ne porte pas l'entrée genre 0.

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
rejetait `world >= 3` alors que le natif range `>= 2` ensemble (aligné le 2026-11-03: table 2 pour tout monde >= 2); `FUN_0045c9b5` ne fait que créer
la requête (le port peut aussi l'annuler).
Revue 2026-11-11 (REA haiku): `DAT_006136b2` = index 0-based du monde choisi, écrit par
`FUN_004637fc` @0x46387a (`[this+0x2749a]`, base 0x5ec218, arg du cas 9 de `FUN_004121b7`;
le même appel fixe `DAT_006136b0` = nombre d'îles de ce monde lu dans `worldpos.txt`) et par
le chargement `FUN_00467be5` @0x467cb0 (ev_56bd97e2…, ev_89b3f037…, ev_4c58c950…): le port
(`config.world_index`) est conforme. Le drapeau compté (`île+0x29ac+slot*4`) vaut 1 au départ
(`FUN_0046466f`), à la première acquisition (`FUN_00466b09`: message cat. 2/9, pont construit,
arrivée d'une unité état 17), 0 seulement à la mise en place du monde (`FUN_00461859`); aucun
effacement en jeu (ev_1f516589…, ev_b1567869…). `FUN_00442799` masque aussi le bouton si
`FUN_00450385` ne trouve pas l'entrée de personnel (`+0x18 == -1`). Seuls écarts restants du
port: propriétaire = joueur local, classe 0, site « établi » (`(+0x1c & 0xb0) == 0`) et
L ≥ 1; en réseau, `shared_bridge_player_mask` peut accorder des îles en plus (ajout remake).
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
Port (état du 2026-10-21, périmé : `TrnStk`, `Recall`, `Obtain`, `UpgSpread` et `HallStk` sont portés depuis): pas de drapeaux d'entraînement (`TrnStk`), pas de `Recall`, pas de bouton `Obtain`, pas de `UpgSpread`,
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

## Panneau Tâches : lignes UPGSPREAD / SUPPLY (REA, sous-agent haiku, non relue)

Evidence rapportées: ev_956729d2…, ev_0383c7a8…, ev_1bf61b01…, ev_a78bedd3…, ev_9bd33459…, ev_0289c266…, ev_639bf60d…, ev_7cbbb9a2…, ev_ab7739c5… (IDs tronqués par le sous-agent).
Dispatch de `FUN_004459e6` (première correspondance): type 5 CONSTR (icône 0); type 0x12 REPAIR (icône 1); type 4 sous 1 avec `FUN_0045ff3f` REPAIR; type 4 sous 1 avec `FUN_0045ff6d` UPGSPREAD (icône 2, jauge = compteur de l'entrée genre 1 / 10, table `panneau+0x13dc`, 16 entrées de 5 shorts [île, site, genre, tâche, compteur]); type 4 autre: `FUN_00450385()==0` STOCK/DARTIFACT, sinon UPGRADE (`FUN_0045c9fe` et sous 1: icône 2, `+0x28`/20) ou SUPPLY (icône 3, `+0x2a` si sous 2 sinon `+0x2c`, dénominateur `50+25*(FUN_0045c3bb()+0x4a)`, icône tonecrys/magctone); type 0xd OARTIFACT. Gabarit: libellé x=45, compteur `[n]` x=5, icône x=25, jauge x=170 70x7, dessinée si numérateur != -1.
Corrections: `FUN_00450385` ne prend aucun argument (lit l'objet appelant); le compteur `[%d]` est bien dessiné. Inconnues: `FUN_0045c3bb`, `FUN_004641de`, comportement à dénominateur 0, entrée UPGSPREAD nulle. Non porté: la table genre 0/1 de `FUN_0045fcbe` n'est pas modélisée.

### Résolution de `p1` des `BC_*` (REA, ev_16d4374a…, ev_611f078c…, ev_ed75141a…, ev_acb06186…, ev_ae0e78b3…)

Observation: le `SENDMESSAGE 101 0 0` de `windows.txt` est un espace réservé. `FUN_0042f150` (islemast) parcourt la table de 29 noms `0x49e700` (pas 0x14) et écrit `+0x64 = index` dans chaque contrôle; `p1` est donc l'index: 0 OnOff, 1 Move, 2 Upgrade, 3 Repair, 4 Obtain, 5 TrnStkC, 6 TrnStkM, 7-9 HallStkB/C/M, 10-14 GenInfo/Storage/Knowledge/Trade/Diplomacy, 15 Recall, 16 AttackFlt, 17 AttackLoc, 18 DefendFlt, 19 DefendArea, 20 UpgSpread, 21-28 Spell1-8. Le rappel MASTER est supposé `FUN_0042fa0f` (non vérifié). Cela valide la section précédente (cas de `p1`) et lève la contradiction.
Boutons → paquet (16 octets: `[0]` cat, `[2]` joueur, `[4]` sous-type): OnOff cat 1/0; Upgrade cat 1/2; Repair cat 1/3; Obtain via msg `0x39` (cat 0, type 0xd, propriétaire = joueur); TrnStkC/M `FUN_004354a2(3,2,…,p1-5)` si `FUN_00450385 != 0`; HallStk `FUN_004354a2(3,2,0,0,p1-7)`; Recall cat 1/0xf (porte `FUN_00450385`); UpgSpread cat 2/0x14 sans porte. Attack/Defend (16-19): aucun paquet au clic, `FUN_0043530b(p1)` règle le mode de curseur (`+0x174`), le paquet sort du clic carte suivant (msg `0x40`, non revérifié). Move (1): aucun cas dans le commutateur.
Visibilité: `FUN_0045302a` (Obtain, Repair, UpgSpread, OnOff, HallStk…) puis `FUN_0045d5ba` ajoute TrnStkC (5), Upgrade (2), et selon `FUN_0045c3bb` 0x2c..0x2e Recall et Attack/Defend (15-19), 0x2f/0x30 TrnStkM et sorts. Correction: Attack/Defend/Recall viennent de `FUN_0045d5ba`, pas de `FUN_0045302a`. Limite: le récepteur ECX de ces prédicats (enregistrement du site vs objet fenêtre) et `FUN_0045c3bb` ne sont pas établis.

### Consommateurs des paquets `BC_*` et visibilité par genre (REA, ev_9dfe8ccb…, ev_1f76cc3b…, ev_05eacc0a…, ev_eb5b6cab…, ev_349b14e0…, ev_592a62cd…, ev_833a2d0d…, ev_0bfe4a9d…)
Observation: `FUN_00465793` (récepteur des paquets de 16 octets; appelant non résolu) écrit dans l'enregistrement de bâtiment B (`0x6192b0 + joueur·0x14a0 + slot·100`): Recall (cat 1/0xf) `FUN_0045dcf4`: `+0x28` île, `+0x2c = 9`, `+0x30`, `+0x32 = 0`; Attack/Defend floater (cat 1/0x10, 0x12) `FUN_0045d867`: `+0x28` = champ de la table `0x6137c6 + id·0x4c`, `+0x2c` = 6/8, `+0x30` = id; Attack/Defend lieu (0x11, 0x13) `FUN_0045d8b2`: `+0x2c` = 7/9; TrnStkC/M (cat 3/2, `w6 != 0`): bascule `B+0x58` (cristal) ou `B+0x5c` (magie), sans test de genre; HallStk (cat 3/2, `w6 == 0`): `FUN_0045f755` fait tourner le mode `+0x13d0 + res·2` modulo 3; UpgSpread (cat 2/0x14): `FUN_0045fe62` crée l'entrée de genre 1 de la table d'ordres du joueur (5 shorts). Clic carte (msg `0x40`, `DAT_005c3804` = 16..19): cat 1 avec île du site, `FUN_0045035a(S)`, cible (`p2`,`p3`).
Visibilité (`FUN_0045302a` + `FUN_0045d5ba`; kind = `S+0x10`, possédé et slot != -1): TrnStkC et Upgrade pour tout genre; Repair si kind > 0x24 et != 0x2a; OnOff 0x25..0x27; HallStk 0x2a (propriétaire seul); Recall et Attack/Defend 0x2c..0x2e; TrnStkM et sorts 0x2f/0x30; UpgSpread kind 0x28 d'un autre propriétaire (0..3) sans le bit `0x1000<<joueur`; Obtain kind 1 avec `4 < +0x24 < 0x22`; Move jamais.
Limites (ECX de `FUN_0045d867/d8b2/dcf4` = B, résolu: voir [ordres de bâtiment](island-ground-object-interaction.md#ordres-de-bâtiment-copie-native-et-traversée)): `FUN_0045ffe2`, `FUN_00452e2b`, noms des genres 0x2c..0x30, correspondance `S[0]/S[1]` et `S+8` non établis. **Non porté:** ces boutons n'ont d'effet que par les consommateurs de ces champs (entraînement, adoption d'ordres par les floaters), qui ne sont pas modélisés; ajouter les boutons sans eux produirait des contrôles sans effet.

**Port (BC_DefendArea, premier bouton de bâtiment à ordre):** enregistrement d'ordre par bâtiment (`building_order_genre/island/coordinate`, équivalents `rec+0x2c/+0x28/+0x30`), écrit par `game_session_set_building_defend_area` (genre 9, coordonnée empaquetée `(v+5)/10`) pour un site possédé et construit de base `0x2c..0x2e` (règle R5); les floaters liés (`source_link_0c`) l'adoptent via l'ordre de coordonnée existant lorsque le leur diffère (sondage idle ou tous les 10 ticks, comme `FUN_0042219e`; l'enregistrement n'est jamais effacé). UI: `BC_DefendArea` (`TRAINB` cadre 0, pane 453,438..507,471) visible sous la règle R5, un clic arme le mode 19, le clic suivant sur la carte (y < 320) écrit l'ordre, Échap désarme. Écarts: curseur et texte d'aide du mode armé non portés; l'adoption interîles passe par le transfert existant du port; Recall (`+0x30 = FUN_00452e2b()` inconnu), Attack/Defend floater/lieu et TrnStk restent non portés.

**Port (suite):** l'enregistrement d'ordre porte maintenant les genres 6 (`BC_AttackFlt`), 7 (`BC_AttackLoc`), 8 (`BC_DefendFlt`) et 9 (`BC_DefendArea`), tous sur `TRAINB` (cadres 6/8/2/0, panes de `windows.txt`). Le clic arme le genre; le clic carte suivant choisit la cible (floater sous le pointeur pour 6 et 8, site pour 7, coordonnée pour 9) et écrit l'enregistrement via `game_session_set_building_order`. Adoption (`game_session_adopt_building_attack_order`, reprend les états d'approche/frappe/défense déjà portés): 6 = action 6, état `0x0f`; 7 = action 7, état `0x10`; 8 = action 8 (défense). Limites: les floaters déjà en état de frappe (6/7), en action 9 ou en lancer ne sont pas réaffectés; cibles limitées à l'île du floater lié; pas de test de camp pour le genre 6 (le natif copie sans test de valeur); non testé en jeu.

### Recall, TrnStk et UpgSpread: consommateurs (REA, ev_b3261569…, ev_2788be00…, ev_80f4a220…, ev_49f2dd3e…, ev_9320c33f…, ev_dd032f8d…, ev_815d66a9…)
Observation: `FUN_00452e2b` (receveur = enregistrement de site) renvoie `FUN_0041e3eb(x, y)`, la position empaquetée `((x+5)/10 << 8) | ((y+5)/10)`; `FUN_0045dcf4` écrit donc pour Recall: `+0x28` = île, `+0x2c = 9`, `+0x30` = tuile du bâtiment lui-même. **Port:** `BC_Recall` (`TRAINB` cadre 4, pane 527,413..572,471) agit aussitôt: genre 9 à la position du bâtiment (`game_session_set_building_order`). Correction: `FUN_0042fa0f` n'utilise pas `FUN_00452e2b`.
TrnStk: `FUN_00465793` cat 3 sous-type 2 bascule `B+0x58` (cristal) / `B+0x5c` (magie) sans test de genre; aucun lecteur de ces drapeaux trouvé (`FUN_00453958` lit les mots du site, non ceux de `B`); sous-types 3/4 de cat 3 créent une tâche `+0x3c = 0x13`, `+0x44 = 0x16` et consomment un compteur `+0x2cfe4 + kind·2`, types produits inconnus. UpgSpread: `FUN_0045fe62` crée l'entrée (île, site, genre 1, tâche, 0); `FUN_004503bd` (cat 3 sous-type 4 sur un site `0x28`) incrémente `entry+8`; à 10, `site+0x1c |= 0x800<<p`, retrait de l'entrée (`FUN_0045ffe2`) et `FUN_0045e6d3` (totaux joueur); aucun niveau +1 observé. Inconnu: lecteurs de `B+0x58/0x5c`, receveur de `FUN_0045fcbe` dans `FUN_004503bd`. **Non porté:** TrnStk (aucun effet établi) et UpgSpread (dépend de livraisons de ressource 1 vers un bloc `0x28`, hors modèle).

**Correction TrnStk (REA, ev_0ea31843…, ev_9df67b83…, ev_c9dc2648…, ev_6038bcbe…):** « aucun lecteur de `B+0x58/0x5c` » est remplacé par `FUN_004421f1` (méthode des contrôles `IWStock`, `IWLoc.cpp`): pour `BC_TrnStkC` (`'C'`) / `BC_TrnStkM` (`'M'`) elle lit le dword `B+0x58` / `B+0x5c` et écrit le mot `ctrl+0x72` (0/1, état du contrôle, `NSTATES 2`); pour un site `0x2a` le même mécanisme cycle les modes `HallStk` (`+0x13d0`-famille, `% 3`). Aucun autre lecteur trouvé: l'effet sur la production reste inconnu. `FA_Train` (état 12) ne dépend pas de ces drapeaux: il débite le pool `E+0x2a` du site (-10, porte `FUN_0045c772`, `FUN_0045c797`) sans créer d'unité. `FUN_00453958` lit `+0x58` du site appelant, pas de `B`.
**Port:** `training_stock_crystal/magic` sur la localisation, `game_session_toggle_training_stock`; `BC_TrnStkC/M` (`THBUTT`, pane de `windows.txt`, cadre = `SHAPEFRAME` + état, survol `HILITEFRAME` 4) offerts pour un site possédé construit `0x2c..0x32` (M seulement `0x2f/0x30`), un clic bascule. Effet de production non porté (inconnu).

### UpgSpread: boucle de livraison (REA, ev_755e1288…, ev_a294ffae…, ev_fd456498…, ev_ff014992…)
Observation: la livraison d'un objet (`FUN_0041e569` état 3, `FUN_004503bd(objet, 1, propriétaire)`) incrémente le compteur de l'entrée de genre 1 lorsque `kind == 1` et que le site vaut `0x28` (`pad.txt`: `p-extend`, TONEXTEND, extension de portée de ton; interprétation d'après l'ordre du fichier); à 10, `site+0x1c |= 0x800<<p`, retrait de l'entrée, recomptage des totaux. Les tâches `UPGSPREAD` sont créées par `FUN_004666c9(site, 1, P)` (paquet cat 0, type 4, sous-type 1). Le paquet cat 3 sous-type 4 vient de l'interface (`FUN_0042fa0f`, `FUN_004337d9`), non de l'arrivée. Inconnus: origine de l'objet de type 1 livré, lecteurs du bit `0x800<<p`, receveur ECX de `FUN_004503bd` (disposition floater ou site), effet visible de l'achèvement. **Non porté.**

### UpgSpread: création, attache, livraison et drapeau (REA, ev_6a5be0da…, ev_37e88f6a…, ev_38a6790b…, ev_7bb88115…, ev_838db8e1…, ev_336bbb75…, ev_9a8d6a72…, ev_3d7ba623…)
Observation: seule `FUN_0045fe62` (appelée par `FUN_00465793`, cat 2 sous-type 0x14) crée l'entrée de genre 1 puis `FUN_004666c9(site, 1, joueur)`; le paquet (4, 1) n'est pas propre à UPGSPREAD (`FUN_0045c9b5` crée la requête UPGRADE, `FUN_0045fd91` une entrée de genre 0). Garde `FUN_00452bc5`: site `0x28`, propriétaire 0..3 (autre que le joueur), bit `1<<p` de `+0x22`, bit `0x800<<p` de `+0x1c` absent. Attache `FUN_0042219e`/`FUN_00422031` cas 4: le floater ne porte pas déjà l'objet et l'objet 1 a une source. Ramassage (`FUN_0041e569` cas 2): objet 1 = stock `+0x28` d'un enregistrement de genre `0x2a` (Hall) du propriétaire; dépôt cas 3 `FUN_004503bd(objet, 1, propriétaire)` incrémente le compteur de l'entrée; à 10: `site+0x1c |= 0x800<<p`, retrait de l'entrée et annulation de la tâche, `FUN_0045e6d3`.
Interprétation: UPGSPREAD fait livrer 10 unités de la ressource 1 (ton de construction) d'un Hall vers un bloc `0x28` voisin; le bit achevé ne sert, parmi les fonctions lues, que de porte (`FUN_00452bc5`): aucun effet de portée ou de niveau observé. Inconnus: écrivain de l'objet `+0x30` d'un ordre UPGSPREAD, receveur ECX de `FUN_004503bd`, lien kind `0x28` ↔ `p-extend`. **Non porté:** sans effet de jeu observable au-delà de la disparition du bouton et de la ligne de tâche, le modèle de livraison (obtention et dépôt par floater de ton de construction) n'a pas été ajouté.

**Vérification en jeu (aide de test du port `F9` : place le premier bâtiment d'entraînement `0x2c..0x2e` qui tient sur un site libre de l'île):** après placement, le panneau du bâtiment affiche les cinq boutons d'ordre (`TRAINB`: DefendFlt, DefendArea, Recall, AttackFlt, AttackLoc), les boutons `TrnStkC/M` (`THBUTT`) et le point `bildicon` du presse-papiers (premier emplacement). Un clic sur `BC_DefendArea` arme le bouton (halo), un clic carte l'écrit puis le désarme; un clic sur `TrnStkC` change son cadre. Non observé: effet sur des floaters (aucun floater lié au bâtiment de test), cadre exact du groupe actif du presse-papiers.

**Port (UpgSpread):** `BC_UpgSpread` (`UPGRADE` art, pane 246,400..270,425, `NSTATES 13`, `HILITEFRAME 13`) est offert (`game_session_upgspread_available`, règle R3/`FUN_00452bc5`) sur un bloc de base `0x28` d'une autre tribu dont le bit `1<<p` de `+0x22` est posé et le bit `0x800<<p` de `+0x1c` absent. Un clic (`game_session_toggle_upgspread`) crée ou annule l'entrée: une tâche (type 4, sous-type 1, objet 1) comme la requête UPGRADE, retenue par `spread_task_plus1[joueur]`; le bouton défile ses 13 cadres tant que l'entrée existe. Les floaters libres l'exécutent par le chemin de livraison générique (objet 1 pris dans le stock de Hall, déposé sur le bloc); chaque dépôt incrémente `spread_count` (plafond de travailleurs assignés à 10), au dixième `source_flags |= 0x800 << p`, retrait de la tâche. La ligne de tâche est `UPGSPREAD` (icône 2, jauge compteur/10). Aide de test du port `F8` (donne un bloc `0x28` à la tribu suivante, visible par le joueur). Vérifié en jeu: le bouton apparaît sur le bloc étranger, s'anime après le clic puis disparaît dans les 40 s (compatible avec l'achèvement; compteur et ligne de tâche non observés directement). Effet de l'achèvement au-delà de la porte: aucun observé (voir REA).

**Vérification en jeu de l'adoption (aide de test `F9` qui lie aussi deux floaters inactifs au bâtiment placé):** après `BC_DefendArea` puis un clic carte à droite, les deux floaters liés quittent les abords du bâtiment et se placent côte à côte sur la ligne du point demandé (à environ 300 px de celui-ci, la cible se trouvant au-dessus de l'eau), puis restent immobiles entre deux captures espacées de 9 s. Compatible avec l'adoption de l'ordre genre 9; l'arrêt court de la cible n'est pas expliqué (rayon d'arrêt ou obstacle non étudiés).

### Entraînement: réserve `+0x2a/+0x2c` et tâche SUPPLY (REA, ev_90928339…, ev_a34a7d43…, ev_ced5022c…, ev_12285d63…, ev_ba8f92a6…, ev_1dccc8de…)
Observation: `FUN_0045c772` teste `+0x2a > 9`; `FUN_0045c797` retire 10 (plancher 0). `FUN_0045cd75` lit les dwords `B+0x58` (canal 2, tous les sites d'entraînement, réserve `+0x2a`, lien `+0x52`) et `B+0x5c` (canal 3, seulement type `0x2f`, réserve `+0x2c`, lien `+0x54`): drapeau posé, lien libre et réserve < `FUN_0045cd27` = `50 + 25*(+0x4a)` → `FUN_0045cc17` crée la tâche type 4 sous-type = canal (`FUN_004666c9`), seulement si la réserve est < 100; drapeau effacé ou seuil atteint → annulation. `FUN_004503bd` codes 1/2/3 ajoutent le montant aux réserves `+0x28/+0x2a/+0x2c`, sans plafond vu. `FUN_004672ef` cas 1 donne +50 aux trois réserves quand un champ d'enregistrement est 0; l'événement déclencheur n'est pas résolu.
Interprétation: `TrnStkC/M` sont des interrupteurs « garder approvisionné »; sous-type 2 = `tonecrys`, 3 = `magctone` (libellés de `FUN_004459e6`).
Observation (désassemblage objdump de FLOAT.EXE, pas d'Evidence ID: session REA fermée): `FUN_0045ee26` (allocation de ligne B, 0x45ef71) appelle `FUN_0045c3fe`: liens `+0x4c/+0x4e/+0x50/+0x52/+0x54 = -1`, `+0x58 = 1`, `+0x5c = (site+0x10 == 0x2f)`; les deux interrupteurs sont donc actifs par défaut. Le test du canal 3 de `FUN_0045cd75` est `cmp [site+0x10],0x2f` (0x45d350), soit 0x2f seul. `FUN_0045fb6f`, appelé seulement par `FUN_00465793` (0x46608b, annulation joueur), efface le lien `+0x52`/`+0x54` et remet `+0x58`/`+0x5c` à 0; l'annulation du tick (`FUN_0045cc17` → `FUN_00466732` → `FUN_00466533`) ne passe pas par lui et garde l'interrupteur.
Dessin (objdump): `FUN_004421f1` met l'état `ctrl+0x72 = (B+0x58/0x5c != 0)`, puis `FUN_0042a55d` dessine THBUTT `SHAPEFRAME + état` (0 = bol vide, 1 = bol avec flèche) et `HILITEFRAME` au décalage `ctrl+0x6c/+0x6e` dans la surface du pane; ce décalage est interprété comme les 5e/6e nombres de `PANE` (TrnStkC `-4 0`; lien parseur non trouvé, aucune chaîne `PANE` dans l'exe). Le pane de TrnStkC (192..243) recouvre TrnStkM (215..247).
Port: défaut posé à l'allocation (`game_session_buildings.c`), coupure sur annulation joueur (`game_command.c`); garde remake: un site sans lien réadopte sa tâche SUPPLY vivante (chargement de sauvegarde native, liens non restaurés).
Port: `update_training_supply` (animation) tient une tâche type 4, objet 2/3, liée par `source_task_slot[1/2]`; les floaters libres la servent par le chemin de livraison générique (source = pile du Hall) et chaque dépôt ajoute 1 à `resource_stock[1/2]`; plafond de travailleurs `réserve + affectés < seuil`. Le lien est effacé à l'annulation (`game_session_dispatch_task_command`). Écarts/inconnues: le +50 initial n'est pas porté (déclencheur inconnu), donc une salle d'entraînement démarre à 0 et n'est approvisionnée qu'une fois l'interrupteur posé; codes d'objet exacts, appelants (thunks) et plafond de livraison non établis; non testé en jeu.

## Relecture de la liste Tâches (REA, sous-agent, non relue)

Observations (`FUN_004459e6` `ev_956729d2…`, `FUN_004469d6` `ev_7e8f7068…`, jauge `FUN_004118df` `ev_fa0f3371…`) : pas de 13 px, `y0 = (H − 13·visibles)/2`; bande de sélection (voile `FUN_004106dd(1,1)`, de la gauche à `droite−13`, sans repli sur la ligne 0); icône principale `taskicon` en (25, y) (CONSTR 0, REPAIR 1, UPGRADE/UPGSPREAD 2, SUPPLY/STOCK 3, artefacts 4), secondaire en (150, y) (STOCK 7; UPGRADE/SUPPLY 5, 6 si objet 0x2f), icône de ressource en (135, y+7), jauge trame 9 en (170, y) 70×7 (remplit ftol(66·ratio)), compteur `[%d]` en (5, y) = `task+4`, nom en (45, y), couleurs de priorité 1→6, 2→5, 3→2; liste vide: `NOTASKS` centré y=50; pas d'en-tête. Panneau d'info : titre (10,43) TNORM/THIGH/TEXCL, aperçu de bâtiment (W−30, H−10), `BLDCONST`/`DELIVER`/`RETRIEVE` centrés y=5. Le port (`hall_panel_render.inc`) suit déjà ces positions, couleurs, icônes et le compteur; non revérifié ligne à ligne ici : hauteur de la bande, coordonnées de `FUN_004119ba` (icônes de l'info), grille `bildicon` du panneau d'info.

## Fin d'une tâche DARTIFACT

Observation (`FUN_004211bb`, `ev_96f90fdc…`): quand l'étape `+0x46` vaut -1 (cargaison remise), un ordre type 4 d'objet 5..0x21 pose `local_10 = local_8 = 1`, puis `FUN_00421ec1(-1)` et `FUN_00466533(slot)`: la tâche est supprimée. Port: `finish_delivery_order` (`game_session_delivery.c`) envoie la commande 12 sur le slot après une livraison d'artefact réussie (avant: seul le compteur était décrémenté, la tâche restait active sans cargaison).

## Répartition des ouvriers (refonte 2026-11-01)

Observation (pseudocode conservé: `FUN_0042219e` `ev_787dc785…`, `FUN_00422031` `ev_9d5d129c…`, `FUN_00421ec1` `ev_c2d3e74d…`, `FUN_0041e454` `ev_516df530…`, `FUN_004211bb` `ev_96f90fdc…`, `FUN_0041e569` `ev_6c3ec9c5…`, `FUN_00466533`, `FUN_00452794` `ev_e8841231…`):
- Cadence: `FUN_0041e569` appelle `FUN_0042219e` à chaque mise à jour si l'état `+0x2c` vaut 0, sinon quand `(tick + index) % 10 == 0`. Retour immédiat pour les états 6/7 et 4 (dépôt), et pour une tâche courante urgente.
- Choix: première ligne (ordre des 64 emplacements) du joueur qui passe `FUN_00422031` puis la règle de compte. `FUN_00422031` n'a ni test d'île ni plafond: type 4 exige une source du code sauf cargaison identique ou artefact; type 5 exige `FUN_004526de` et, sauf Build Tone porté ou pad complet (`FUN_00452794`: stock `+0x28` ≥ coût), une source de Build Tone; 0xb le sous-type 0; 0x12 Build Tone porté ou une source.
- Exécution: l'ouvrier reste attaché. À chaque retour à l'état 0, `FUN_004211bb` planifie l'étape suivante. Livraison type 4 (cas 3): étape `+0x46` 0 = aller chercher/déposer, 1 après dépôt (cargaison vide → 0, boucle; refusée → 2 → détachement). CONSTR (cas 4): `FUN_004526de` faux → détachement et suppression de la ligne; pad complet → état 5; Build Tone porté → dépôt; sinon source. Les traversées (`FUN_004210a9`) replanifient à l'arrivée. La ligne n'est libérée que par annulation (`FUN_00466533` détache tous ses ouvriers) ou rééquilibrage.

Port (`game_session_delivery.c`): `assign_resource_tasks` suit cette cadence, ces exclusions et cette sélection; `attach_task`/`detach_task` = `FUN_00421ec1`; `plan_task_leg` = cas 3/4 de `FUN_004211bb` pour les codes 1..3 et CONSTR, appelé quand l'ouvrier attaché revient à l'état 0 (y compris après pont, reprise `handoff_resume_state == 0`). Supprimés: fenêtre d'engagement de 300 ticks, réévaluation à chaque tick, plafonds par ligne (CONSTR `stock + affectés < coût`, UPGRADE 20, UPGSPREAD 10, SUPPLY), finisseur unique, restriction des livraisons à l'île de la ligne, libération après chaque livraison. Le champ `task_step` reste 32 bits pour garder la disposition des sauvegardes du remake.

Interprétation / gardes du port conservées: une traversée commencée (état 0x11, minuteur ≠ 0) n'est pas interrompue (le port déplace le floater à un instant fixe); seules les lignes 4, 5, 0xb, 0xd et 0x12 ont un exécuteur; charge, ramassage, artefacts et réparation gardent leur routage à l'affectation (artefact: toute île accessible depuis la passe suivante). Le surplus de Build Tone livré pendant qu'un autre ouvrier achève le pad est un effet natif attendu, non corrigé. Non vérifié en jeu; suite ctest (26/26) et test de documentation passent après adaptation des tests aux règles natives (attache sans trajet immédiat, second ouvrier CONSTR admis, Build Tone en vol conservé dans les cargaisons).

## Ouvriers en traversée et lignes sur une autre île (passe 2026-11-01)

Observation (REA, sous-agents haiku 5.5; `FUN_004211bb` `ev_3477c421…`/asm `ev_a5c09b06…`, `FUN_004210a9` `ev_c4c31ca1…`, `FUN_00420dbd` `ev_1bc6136e…`, `FUN_0041e569` `ev_8578fcc7…`, `FUN_0042219e` `ev_7b65b088…`, `FUN_00421ec1` asm `ev_6260bda2…`, `FUN_00466533` asm `ev_bebe94c4…`, `FUN_00420669` `ev_98619c7d…`, `FUN_00420e94` `ev_31165ecc…`/`ev_385adb02…`, `FUN_0045f5c5` `ev_d98532f2…`/`ev_f7b22af7…`):
- `FUN_004210a9` n'écrit que `+0x2c = 0x11`, `+0x30` (île visée), `+0x32` (pont de départ): `+0x3c`, `+0x40`, `+0x44`, `+0x46` restent ceux de la tâche. Le cas 3/4 de `FUN_004211bb` n'écrit jamais `+0x46` dans une branche qui traverse; échec de `FUN_004210a9` → `FUN_00421ec1(-1)`.
- À t = 0x78, l'état 0x11 écrit `+0x0e = +0x30`: une île visée non adjacente est atteinte en un saut (attente 500 au lieu de 200, arrivée sur le pont actif le plus proche < 8000).
- Rien n'exclut l'état 0x11 de `FUN_0042219e` (comparaisons 6, 7, 4 seulement); `FUN_00421ec1` et `FUN_00466533` → `FUN_00420669` remettent `+0x2c = 0` sans toucher `+0x34` ni la position: une réaffectation ou une suppression de ligne interrompt la traversée sur place.
- Artefact (code 5..0x21, cas 3): source = `FUN_00420e94(3, code)`, dépôt du joueur (`+0x10 == 0x2a` ou `+0x18 != -1`) sur l'île courante avec inventaire > 0; sinon traversée vers l'île `+0x13c8` du bloc joueur. Seul écrivain de `+0x13c8/+0x13ca`: `FUN_0045f5c5`, pour un item `0x2a` (interprétation: île et site du Hall; appelant non résolu).

Port: les livraisons d'artefact (routées) acceptent maintenant une ligne sur une autre île (traversée vers la source, puis vers l'île de la ligne cargaison en main, ou directement si l'ouvrier la porte déjà). Avant, `assign_delivery_task_for_floater` exigeait l'île de l'ouvrier; comme le planificateur s'arrête à la première ligne admise, une telle ligne bloquait l'ouvrier pour toutes les lignes suivantes à chaque réévaluation. Garde du port: si une affectation routée échoue (le natif ne peut pas échouer), le balayage continue aux lignes suivantes. Import de sauvegarde native: un ouvrier lié en état 0x11 reprend en replanification (`handoff_resume_state` 0) au lieu des reprises routées 3/4. Source d'artefact: `refill_source` (île courante puis îles accessibles); avec le Hall comme seul dépôt d'inventaire du port (`+0x18` laissé à -1), l'île choisie est celle du Hall, comme le natif. Écart conservé: une traversée commencée n'est pas interrompue (voir plus haut). Corrigé aussi (`game_session_travel.c`): après le passage sur l'île d'arrivée (t = 120), le port revalidait l'index du pont de départ contre les enregistrements de l'île d'arrivée; si celle-ci en avait moins, la traversée était annulée et la tâche perdue à l'arrivée. Le natif ne lit `+0x32` qu'au départ; le port ne le vérifie plus que pour un minuteur ≤ 60. Vérification: harnais hors dépôt sur données réelles (monde 0, pont 0→4 puis 4→6): chantiers sur île voisine et à deux sauts menés à terme; artefact livré sur l'autre île. Tests (`worker_scheduler.inc`, `test_native_save.c`): chantier distant mené à terme, tâche conservée pendant la traversée puis replanifiée, retour chercher à la source, île non adjacente atteinte en un saut, artefact livré sur l'autre île, ligne routée injoignable sans blocage, annulation pendant traversée, import de sauvegarde en état 0x11. ctest 26/26. Non vérifié en jeu.

Changement de tâche à la replanification (passe 2026-11-02; REA haiku 5.5, `FUN_0042219e` `ev_ddd07c90…`/`ev_55875c8f…`, `FUN_00422031` `ev_e73eeaac…`, `FUN_0041e454` `ev_f173d374…`, `FUN_0041e569` `ev_21801…`, `FUN_00421ec1` `ev_b81bb819…`; pseudocode, ECX non vérifié en assembleur):
- Observation: un ouvrier lié à une ligne non urgente ne la quitte que si (a) une autre ligne, première dans l'ordre des slots, passe `FUN_00422031` puis la règle de compte/classe (déjà portée), ou (b) l'île est en danger (`DAT_005eebd4`, branche attaque, action 6). La ligne courante n'est jamais revalidée ni re-choisie; sans candidate, il la garde. `FUN_0042219e` précède `FUN_004211bb` dans la même mise à jour; la replanification (état 0) n'ajoute aucun autre motif. `FUN_00421ec1` garde la cargaison `+0x18`.
- Port: mêmes règles, aucun écart trouvé. Risque propre au port: un compte `assigned_floater_count` qui fuit déclencherait la règle de compte sans raison. Tests ajoutés: ligne locale ajoutée pendant la marche vers le pont sans prendre l'ouvrier (0 < 1 − 1 faux) jusqu'à l'arrivée; deux ouvriers sur deux chantiers (un par île) gardent chacun leur ligne pendant tous les allers-retours et traversées, compte = ouvriers liés à chaque tick, jusqu'à la fin d'une ligne. ctest 26/26.

## Île en danger et lignes 6, 0xd, 0x11 (REA haiku 2026-11-05)

- **Drapeau de danger :** `DAT_005eebd4` = `IB + 0x29bc + type*4` (île `IB = 0x5ec218 + île*0x29e8`). Écrivains (`ev_0e85aed9…`, `ev_44f750b4…`) :
  - types 0..3 : bascule par `FUN_00465793` catégorie 3 sous-type 0 (`0x465ae2`, bouton PANIC), remise à zéro par `FUN_00461859`, lecture/écriture de sauvegarde par `FUN_00462c55` ;
  - type 4 (`+0x29cc`) : c'est le drapeau « glyphe obtenu » (`FUN_004503bd`, `FUN_004672ef` cas 0x11, effacé par `FUN_00460072`).
- **Qui lit le drapeau :** `FUN_0042219e` ne le lit que pour un floater de type ≠ 4, sans lien (`+0x0c == -1`), de sous-type ≠ 8 et hors actions 6/7. Les branches Léviathan reviennent avant la lecture (assembleur `0x4221b3..0x422556`). Le Léviathan ne réagit donc jamais à `+0x29cc`.
- **Candidats :** `FUN_00420991` accepte toujours un floater de type 4 ; pour les autres types, il faut que la politique `0x619290` soit nulle. Les candidats sont des floaters de l'île (`0x618fb4`), pas des sites. `FUN_00439fdf` fait clignoter le bouton tant que le drapeau du joueur est posé.
- **Rendu du bouton PANIC** (REA haiku 2026-11-05, `ev_322de486…`, `ev_611f078c…`, `ev_e067c411…`) :
  - `FUN_00439fdf` est le slot 2 de la classe `IWPanic` (WINTYPE 45, constructeur `FUN_00439f30`, `+0x70 = 8`, `+0x72 = 1`). La boucle `FUN_0046ae19` l'appelle à chaque passe d'affichage.
  - Drapeau posé : il copie la frame `mainbutt` `+0x70` à l'origine du panneau, sans frame de base ni de survol, puis avance la frame d'un pas. Le sens s'inverse à 13 et à 8, d'où la suite 8, 9 … 13, 12 … 9.
  - Drapeau nul : `+0x70 = 8`, `+0x72 = 1`, puis le dessin normal `FUN_0042a00b`.
  - Port : `island_panic_pulse_step`, un pas par trame de 50 ms. Avant, le port gardait la frame de survol fixe.
  - Vérifié en jeu (fixture `badges`) : frames 8 à 13 en aller-retour, retour à 8 quand le mode est coupé.
- **Port :** déjà couvert par PANIC (`game_session_apply_panic_orders`, `source_event_state`). Le port choisit le candidat le plus proche ; le natif prend le plus petit `FUN_00420600`.
- **Lignes de tâche :** `FUN_004662b7` (64 lignes de 0x14 octets à `0x6183bc`) n'est appelé que par `FUN_0045cd75` (type 0xb), `FUN_0045eaa7` et `FUN_004666c9` (type 4), et `FUN_00465793`, qui relaie les paquets de catégorie 0 (`ev_8318be3d…`).
- **Paquets de catégorie 0 :** types 5, 0xd et 4 (`FUN_0042fa0f`), 0x12 (touche `F`) et 0x11 (touche `U` sur un pont : traversée vers l'île `+0x36`). Les cas `F`/`U` de `FUN_004337d9` exigent `DAT_004c2b74`, que seul le mot `nevada` de `float.cfg` pose (`FUN_0041d19d`, `0x41d285`). Ce sont des touches de débogage, hors périmètre.
- **Aucun créateur de ligne de type 6.**
- **`FUN_004239e9` :** son seul appelant est `FUN_0041760b`, par le thunk `0x4017ee`. Le « sous-cas 0x14 » est le sort de kind 0x14 : il relance `FUN_0042219e` sur chaque floater de type 4 de l'île (ECX = le floater, `0x424f4d`). Le port le fait par le minuteur Léviathan.


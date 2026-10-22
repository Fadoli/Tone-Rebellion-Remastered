# Interaction des objets posés sur l'île

## Ce que prouve le binaire

`IWLocInfo` ne transforme pas la sélection d'un objet au sol en ramassage.
Son action 6 demande au départ de saisir le site sélectionné, mais le prédicat
`FUN_0045f337(site, NULL)` exige que la source soit un emplacement du joueur
portant un ID de bâtiment `0x25..0x34` (sauf `0x28`), avec les gardes de flags,
Hall et ressources de la fonction. Un `PIT_Object` (`item=1`) échoue donc comme
source de cette action.

La seconde forme du prédicat accepte un site cible de classe 0, libre
(`owner=-1`) et visible par le joueur. Si son item vaut 1, le sélecteur de
forme `+0x24` doit être compris entre 5 et 33. `FUN_0045302a` place également
ces sites dans la liste des cibles. Le site `item=1` est donc une cible
d'interaction établie; cette preuve ne dit pas que son objet est ramassé.

## Séquence grab/place observée

1. `FUN_00441d3e`, événement `IWLocInfo` 6, vérifie l'action et l'état
   `mbHaveGrabbed`. Si aucun objet n'est tenu, elle valide le site sélectionné
   avec `FUN_0045f337(site, NULL)` puis envoie `0x48`; si un objet est déjà tenu,
   elle envoie `0x4a` (`ev_d72eed96013f16e8cecbd5772c71935e76feec78b9df2e8af58ccce46c4ada4e`).
2. `FUN_0042fa0f` convertit `0x48` en événement catégorie 3/sous-type 5 et
   `0x4a` en catégorie 3/sous-type 6. `FUN_00465793` route ces événements vers
   `FUN_0045f4f5` et `FUN_0045f5c5` (`ev_6ac7cc6650dc8a0e9b412c055606948d1c6dbbdd3e6c6df0a7fcc1551764419e`,
   `ev_90fc7b398e8cc430ee898f0371c196e285bf0f21c5cd78aa04fcdd060294d4ce`).
3. Le sous-type 5 revalide la source, débite les trois coûts calculés par
   `FUN_0045f2a1`, mémorise l'île et le site d'origine (`+0x13ba/+0x13bc`),
   puis active l'état tenu (`+0x13c0=1`)
   (`ev_598cfe2b014b15e607c8b41ac943b5dd6af4e3db3c818406a1653591e00c406a`).
4. Le sous-type 6 valide la cible avec `FUN_0045343b`. L'assemblage de
   `FUN_0045f5c5` confirme que le pointeur cible est passé dans `ECX` et que le
   site source mémorisé est l'argument. Quand la cible est un
   site libre de type 0 ou 1, cette routine écrit sur la cible l'ID et le
   propriétaire de l'objet tenu via `FUN_004528ca`, puis copie d'autres champs
   du site source. Une pose réussie efface `+0x13c0`; un retour sur le site
   d'origine restitue les coûts (`ev_29c00108fecaae10e34c3acd2f038be290b324679da3c2aa13b3a70825e8b4ae`,
   `ev_ded193af75b4663591b54cea28c51d70b7d2a0d987a2d7b891ee6f7cacdc8963`,
   `ev_46b3b31c81eecb2bc50884c4458f57e4c8020d7001de0c3ae0260c3a1b1d9185`).

Le helper de pose copie les champs vers la cible; son corps ne vide pas le site
source. `FUN_004533fb` effectue cependant un nettoyage séparé quand le site a
un lien source `+0x18`: il libère ses tâches et son handle de staff, puis pose
`+0x58=1`, `+0x46=0` et recalcule le bit actif. Le nettoyage de l'ancien site
dans le remake efface maintenant aussi `source_value_46` avant de le laisser vide.
Le nettoyage natif des champs
`+0x10` et du propriétaire n'est pas encore relié avec certitude à cette
séquence; le port vide le site après le transfert et applique maintenant les
l'annulation des tâches modélisées qui ciblent l'ancienne coordonnée et le
détachement de leurs floaters avant le transfert. Cette extension réutilise le
chemin observé `FUN_00460029` → `FUN_00466533` lors d'une libération de site;
le raccord natif précis dans la transaction grab/place reste à confirmer.
Cette action ne crédite pas
l'inventaire 5–33 et ne prouve toujours pas la collecte du `PIT_Object`.
Evidence REA: `ev_de65e9f21841907f069d4ed90a03330dab6bbc6699fe274eb7fe0e4a9d51a574`,
`ev_133c7d24c9acca9d04969a9c2f27278f1521f10657d9e7d195fb107668d3cab8` et
`ev_f91211a8053408a98cbff1cb291dedf16e59bec13ee8ae9dcf11dbb80c34eaa4`.

## Inconnue restante

Le parseur `fltinf.txt` lit le bloc `pickup` dans `FUN_00454d1f`, mais aucun
consommateur n'est encore relié à un contact floater–`PIT_Object`. Le producteur
de l'événement catégorie 3/sous-type 4 qui crédite l'inventaire reste aussi
inconnu. Il faut établir cette transition et l'éventuelle mutation du record
`item=1` avant de porter le ramassage.

## Autre chemin : clic carte depuis Inventory

Ce chemin ne correspond pas au « grab » de `IWLocInfo`. Dans
`FUN_0042fa0f`, l'action carte `0x40`, si `DAT_0049e9c4` contient un sélecteur
d'objet et que le joueur n'est pas dans l'état qui bloque l'action, construit
une commande catégorie 0/type 4 associant ce sélecteur au point de carte cliqué.
La commande est ajoutée à la file locale; la branche efface ensuite le
sélecteur et ferme le mode Inventory (`ev_6ac7cc6650dc8a0e9b412c055606948d1c6dbbdd3e6c6df0a7fcc1551764419e`).
Le hit-test carte et l'émission de `0x40` sont dans `FUN_00435826`
(`ev_9fac3ab32e724258b184a4abd7ffd102c61b15164169cc041ae03f1859b5bb49`).

Au tick, le dispatcher envoie les commandes catégorie 0 à `FUN_004662b7`, qui
les range dans des slots de tâches de 0x14 octets
(`ev_63d9efb5bce1c51e26da896805829764236e9140de5f842cda6ad015f1c8ad1b`,
`ev_db281f9a7a1fbb3e9bd29b7389912081c306195183d45c11b3bae8830ccff761`).
`FUN_00422031` traite aussi un cas de tâche 4 avec un sélecteur dans la plage
5–33, mais le chaînage observé ne démontre pas que cette tâche crée l'objet sur
le site, débite l'inventaire ou enlève un `PIT_Object` déjà présent
(`ev_9d5d129cd6bb5e1095f8136fbde959c47360ad898c94d3104c63add6dcda3bc7`).
Cette branche documente donc une requête de placement depuis Inventory; elle
n'établit pas une interaction de collecte d'un objet posé.

Evidences complémentaires : les références entrantes de `FUN_0045f337` montrent
les call-sites UI et les transactions grab/place, sans call-site de tick
floater (`ev_0fb01505c0a7e326de1d7e85aa13d4df42a1c47415115b384c04cc90f31f9a6d`).
Cette couverture n'exclut pas un autre mécanisme qui lirait directement les
records de site.

Le consommateur runtime d'état 13 (`FUN_0041e569`, `ev_a22f1c921d2325494e512998fc999d7e222d5c45422f7d52c6d808b30b8feccd`) lit `+0x24` seulement quand la cible est un `PIT_Object` (`ev_8d591588cea4abce308dbbd5f69e34b5c6431010d387034afe228dee1b3385a8`). À l'arrivée, il repose l'artefact déjà porté via `FUN_00425084`, prend l'ID 5–33 et retire le site via `FUN_00452a15`; cette fonction vide le cargo même si ce n'est pas un artefact (`ev_c90fab99fa7691b34572e2c9eba925751fbdf77b63a570c51574e19c416b7e0b`). Sans PIT_Object, il annule la liaison avec `FUN_00421ec1(-1)`, qui décrémente le compteur assigné, libère le slot et efface l'ordre courant (`ev_c2d3e74dd2e94c30ca9de18f1387bb8d44d32daf432cd179e9d1b8dfc693b4dc`). Le remake porte ce consommateur; le producteur de l'état 13 n'est toujours pas identifié.

REA n'a pas établi de bouton dédié de ramassage dans l'interface native. Le gestionnaire de carte `FUN_00435826` sélectionne les emplacements et émet les événements d'action carte; le dispatcher `FUN_0042fa0f` transforme `0x40` en commande de carte ordinaire. Le producteur exact de l'action floater `0x0d` vers un `PIT_Object` reste inconnu : l'ordre clic droit du remake demeure une inférence du consommateur d'état 13, pas une séquence native démontrée.

Le remake n'ajoute donc plus de bouton `RAMASSER` à `IWLocControl`. Lorsqu'un floater porte un objet 5–33, il est affiché dans sa main avec l'icône de l'inventaire, conformément au chemin de rendu natif `FUN_0042704b` qui traite les cargos de cette plage (`ev_e237e172a682f09a34d6fa8f9a34f10489cf0ed25de76eb181a60037ef0e2a00`). Le texte natif `object=%d` dans `IWLocInfo` est activé uniquement par l'option `blomster` de `float.cfg` (`ev_015497334495c0d3c77ccdd63a1bb6d797ca6c813252a8b2a431b4e55a0069d1`, `ev_597538638680fa517492934c3df24ed9cf08214ec26dc930cd117afad07b751c`); c'est un affichage de diagnostic, pas une UI joueur prouvée. Les ouvriers initiaux ont un sous-type 0; l'ordre remake les accepte également. REA n'a trouvé ni store littéral `+0x3c = 0x0d` dans les sections initialisées (`ev_b281788d244cc7683d3ca8dda679e5e8bf1796e7a1a259776e534d8d4bd1d503`), ni caller métier résolu pour le getter `FUN_004502dc`; les stores indirects restent hors de cette recherche.

Le rendu de sélection du remake a été corrigé séparément : la sélection d'un `PIT_Object` (runtime type 1, classe 0, propriétaire -1, objet 5–33) passe désormais avant le panneau du floater conservé. Elle affiche l'icône de l'objet et son texte d'inventaire dans `IWLocInfo`; la sélection native de cibles 5–33 est observée dans `FUN_0045302a` (`ev_11ae9b199167de7f63009a806860da707448a67daead1d9059621173b4fb6477`). Ce panneau descriptif est un rendu du remake, sans prétendre qu'il existe sous cette forme dans le jeu d'origine.

À la fin d'un état 13 réussi, `FUN_0041e569` renvoie aussi un floater subtype 8 vers le Hall lorsque l'ordre n'est pas `FA_Cast` et que le garde global natif est ouvert. Le remake reprend ce retour Hall via le trajet coordonnée déjà porté; son tick n'avance que lorsque la simulation est active. Evidence : `ev_a22f1c921d2325494e512998fc999d7e222d5c45422f7d52c6d808b30b8feccd`.

## Vue IWLocInfo après sélection (état du port)

Observation (REA, ev_c7c37d99, ev_af5ecc43, ev_d6b45c8f, ev_2c439ff0):
`FUN_00440567` (paint `mpLocInfo`) envoie les sites `P+4==0`, `P+0x10` ∈ {0,1}
à `FUN_00441aae`. Pour `PIT_Object` (`P+0x10==1`), garde `4 < P+0x24 < 0x22`,
puis une seule image: sprite `triggers` (alltrigs.shp), frame `P+0x24-5`,
centrée dans le panneau par `FUN_004119ba` (`(W-largeur)/2 - origine`), sans
échelle, sans texte, sans bouton. Le propriétaire (`+0x14`) n'est pas lu ici.
`FUN_0044338b` est le détail d'unité (WORKER/AWAKE, HITS, STRENGTH, CHARGE;
gamey.txt: Ouvrier, Le Sage, Coups, Puissance, Niveau, Charge) et ne sert pas
aux objets au sol; la note précédente de cette section l'avait supposé à tort.
Le port dessine donc seulement la frame centrée (l'ancien libellé inventé
« OBJET AU SOL » et la description sont retirés).
`FUN_0042704b` lit l'ID d'objet en `+0x18` (frame `id-5`, feuille `DAT_0049acb4`)
pour les sprites d'unité; le chemin site utilise `+0x24`. Les deux champs
coexistent; sémantique de `+0x24` (sous-ID ou compte) inconnue.
Inconnues: appelants de `FUN_00440567`/`FUN_00441d3e` (dispatch non résolu),
fond exact (`DAT_004c2b08`; le port garde `g_temp_hole_art` frame 1), sémantique
du clic (`FUN_00441d3e` cas 6).

## Textes du détail d'unité (port aligné)

Observation (ev_347b34f6, ev_76cadb79, ev_8518ba3d, ev_fe68d74a): la ligne de
nom de `FUN_0044338b` est `"%s %s"` du slot tribu (`0x49cfc8`, pas 12) et du
libellé `WORKER`/`AWAKE`. Les chaînes `xTark`… ne sont que l'image initiale:
`FUN_0041d70d` les remplace au démarrage par les lignes de `names.txt` (5 tribus,
5 pluriels, 15 îles, 18 bêtes dont le tableau xSpores). Libellés via `FUN_00429ebe`
(gamey.txt, non mis en majuscules): Ouvrier, Le Sage, Niveau, Coups, Puissance,
Charge. Le port affiche maintenant « Tark Ouvrier », `Coups a/b`, `Puissance n`,
`Charge a/b` et les noms de bêtes de `names.txt`, au lieu des littéraux anglais.
Interprétation: contenu des slots à l'exécution déduit du parseur, non observé en
mémoire. Inconnues: police/couleur natives, `DAT_004c2bb0`.

## Revue du panneau Hall (FUN_00440567)

Observation (ev_671a14319b2fe7be486009e7ab2ec75a402dc35e1dc4794f78145e9aa95e9233,
ev_fccc3ec3…): lignes bildtone/tonecrys/magctone (icônes et montants), SURPFLOW
(5,4), POPSTR (0xb6,0x29) et WORKSTR (0xb6,0x33) concordent avec le port. Corrigé:
WORKSTR n'a pas de garde `total>0`; le résumé exige `P+0x10==0x2a`. Non porté:
grille `ACTICON` (bit i de l'ushort joueur `+0x4a`, i < `DAT_006136b0`),
`bldgage`, icônes de queue, variante `P+0x18 != -1` (bildicon/taskicon/slots).
Inconnues: formule du pourcentage WORKSTR (ST0 hors pseudocode), identité de
`DAT_006191f8` (+0) face à `source_maintenance_budget` (+0x3c), couleur du texte,
appelant `0x40234c`.

### ACTICON du Hall (port)

Observation (ev_e47de0c0a7aca99494439a76c645dfcf775a893feb46fc262066f51d9a30f44e,
ev_2ea57c14…): `DAT_00619242 + P+0x14*0x14a0` est le mot global de bits dont
l'unique écriture est `FUN_004503bd`; ce n'est pas le champ joueur `+0x4a`
(`P+0x4a` est un palier de mise en page). La boucle dessine `ACTICON` (acticon.shp,
`shapes.txt`) frame i pour chaque bit i actif, i < `DAT_006136b0`, curseur (220,1),
x += 10, retour à x=220/y += 10 après i=2,5,8,11 (x=225 pour i=11).
Port: le masque est `special_feature_island_mask` (bits = index d'île). Hypothèse:
`DAT_006136b0` = nombre d'îles (aucun écrivain statique, valeur initiale 0).
Inconnues: nombre de frames d'acticon.shp, survol/infobulle (aucun dans le corps).

### Variante non-résumé du Hall (P+0x18 != -1) — port partiel

Observation (ev_671a14319b…, ev_9bd33459…, ev_7cbbb9a2…, ev_b5f6de1a…, asm
0x440862-0x440878): après le test `P+0x18`, le jeu dessine: corps du bâtiment
(`FUN_0040bf98`, x=base+0x1e/0x14/0xa selon `P+0x4a`, y=90, items 0x2c..0x2f);
jauge `bldgage` (frame 0, (base-18,0), 36x8, marge 2, fraction `+0x34`/`FUN_00450978`,
sauf item 0x2a ou propriétaire 4); rangée `bildicon` (frame clamp(owner+4,4,7), N
icônes, x0=base-40, y=5, pas 8, 5 par ligne; N = short `+0x60` de
`0x6192b0+slot*100+owner*0x14a0`); `tonecrys` frame 4 (11,17) + jauge `taskicon`
6x55 (8,20), fraction `+0x2a`/(50+25*L) ; item 0x2f: `magctone` frame 4 (38,17) +
jauge (35,20) et deux barres 3x55 (15,20)/(42,20); icônes ACTICON de queue; six
icônes de slots (`in_ECX+0x78`, table `0x6137b8`, `FUN_0042704b`); onze contrôles BC_*.
Port: `bldgage`, `tonecrys`/`magctone` (icônes seules), icônes ACTICON de queue
(0x2c..0x2f, 0x2a). Interprétations: ACTICON dessiné si le bit est actif avec x
avancé seulement sur icône dessinée; jauge `bldgage` horizontale, remplie de
gauche à droite avec `game_session_repair_location_values`.
Non porté: rangée `bildicon` (N non relié à un champ du port, trace de
`FUN_00450385` ouverte), jauges `taskicon` (capacité = niveau de l'enregistrement
staff `FUN_0045cd27`, orientation inconnue), barres 3x55, six slots, contrôles BC_*,
placement natif du corps (le port garde son ancrage existant (un commentaire du code dit l'avoir calé sur une référence; non revérifié ici)).

### Tracé `bildicon` et slots (pas de port)

Observation (ev_3755627b…, ev_0f4bd30d…, ev_aa2efe38…, ev_af74df8d…, ev_ff014992…):
`FUN_00450385` renvoie `0x6192b0 + slot*100 + owner*0x14a0` (0 si `+0x18 == -1`);
ce bloc de 100 octets est l'objet « source » initialisé par `FUN_004528ca` et dont
`FUN_0045c470` range les huit liens floater (`+4..+0x12`), le compte `+0x24` et le
dernier id `+0x4c`: ils correspondent à `charge_floater_slots`, `charge_floater_count`
et `charge_recent_floater` du port. `+0x60` (octets 96..97) reste dans le bloc,
mais aucun écrivain n'a été trouvé (accès par pointeur calculé). La table
`0x6137b8` est le tableau des floaters (pas 0x4c).
Interprétation: la rangée `bildicon` compte probablement quelque chose lié aux
liens floater; les six slots sont probablement des ids de floaters liés au site.
Inconnues: écrivains de `+0x60`, écrivain de `in_ECX+0x78` (offset générique
partagé avec d'autres objets liste), 48 vs 52 enregistrements par propriétaire.
Raison de l'absence de port: sans écrivain ni lecteur établi, tout dessin de
`bildicon` ou des slots serait une supposition de données.

### Correction du tracé `+0x60` et `+0x78` (REA, port de `bildicon`)

Observation (ev_a4a51711, ev_b504a93b, ev_4712553c, ev_e7593de8, ev_baeadee8):
le short `R+0x60` est le numéro d'instance 0..9 attribué par `FUN_0045ee26` aux
rangées source de même item (0x2c..0x32), 0 si aucune place; il n'est écrit ailleurs
dans aucune des fonctions listées (recherche de stores word complète, dword/octet
non cherchés). Il correspond à `source_category_slot_60` du port. La rangée
`bildicon` boucle `i < R+0x60`: le port la dessine (frame clamp(owner+4,4,7),
x0=W/2-40, y=5, pas 8, 5 par ligne). L'ancienne note « aucun écrivain » est
dépassée. Interprétation: le sens « numérotation » vient de shapes.txt.
Les six slots (`this+0x78`): seul `FUN_0044034e` les écrit, à chaque dessin
(appelé via le thunk 0x402103 depuis `FUN_00440567`, pas par le message 14000):
valeurs `R.word[4+j*2]` (liens floater) filtrées par type via `FUN_0045d7e8`,
slots 0..2 type 0, 3..4 type 1, 5 type 2, -1 si vide. Non porté: le prédicat
de `FUN_0045d7e8` et le type (nibble bas de `floater+0xA`) ne sont pas reliés au
modèle floater du port.

### Six slots du Hall (port)

Observation (ev_ec3eeb90…, ev_62062fe1…, ev_d3dc2d7b…, ev_bfd78831…, ev_671a1431…):
`FUN_0045d7e8(R, prev, kind)` renvoie le premier lien `j > prev` (8 liens
`R+4..+0x12`, -1 = vide) dont le floater a `(+0x0a & 0xf) == kind`.
`FUN_0044034e` remplit, à chaque dessin, `this+0x78` (6 shorts, -1 initial): kind 0
→ slots 0.., kind 1 → 3.., kind 2 → 5.., sans plafond par kind (une 6e écriture
dépasse le tableau). `FUN_00440567` dessine chaque floater présent par
`FUN_0042704b` aux offsets de panneau X={230,230,230,195,195,160},
Y={21,55,89,35,72,55} (item 0x2f: X={220,-,-,220,-,170}, Y={28,-,-,82,-,55}, 999 =
masqué par le port), surbrillance si le floater est la sélection.
Port: `draw_building_slot_floaters` (corps + jambes comme le panneau unité), kind =
`attack_level_flags & 0xf` (déjà utilisé de même par la logique d'effectif du
port). Non porté: surbrillance du floater sélectionné, sprites des types >= 4,
écrivains natifs de `+0x0a`. Interprétation: kind = niveau d'unité.

### Jauges taskicon et barres du Hall (REA, port partiel)

Observation (asm 0x440aee-0x440b2a, ev_1b288a5409cf…, ev_5202cf39…, ev_13fb39e1…):
la jauge TASKICON appelle `FUN_004118df` avec frame 8, (x,20), 6x55, marge 2,
direction 1: verticale, remplie par le bas, le reste du haut peint en indice
palette 0; géométrie intérieure x+2..x+4 (largeur 2 px selon les arguments, non
recoupée visuellement) par y+22..y+73 (51 px). Fraction = stock/capacité bornée à
[0,1], capacité de `FUN_0045cd27` = 50 + 25*L, L = short `+0x4a` de l'entrée
location (`0x5ec640 + R[1]*0x60 + R[0]*0x29e8`). `bldgage`: horizontale (dir 0),
remplie de gauche à droite, reste peint en indice 0. Barres 3x55 (x=15 et 42, y=20,
`FUN_0041179e`, dir 1, segment seul): contour indice 1 et intérieur couleur 4, ou 2
si `A > P+0x2a` / `B > P+0x2c`, avec `A = short 0x6188e4 + s*0x2c`,
`B = FUN_0045d9c1(s)`, `s = this+0x74`, ignorées si `s < 0`.
Port: jauges TASKICON pour `tonecrys` (8,20) et `magctone` (35,20, item 0x2f) avec
L = `source_capacity_4a` (interprétation); `bldgage` aligné sur l'orientation.
Non porté: barres 3x55 (table `0x6188e4/0x6188e2`, écrivains et sens inconnus;
`s = this+0x74` fixé par le message 14000), contrôles `BC_*`, surbrillance de slot.
Inconnues: relation exacte `R[0]`/`R[1]` ↔ île/location (supposée), sens de L.

### Barres 3x55 du Hall: table `0x6188c0` (REA, pas de port)

Observation (ev_1c2dcfc3…, ev_7b0f7fe9…, ev_be9d2da9…, ev_9c67aecb…, ev_ad242f26…,
ev_bd2212f2…): les barres lisent un enregistrement de pas `0x2c` à `0x6188c0`:
`+0x20` niveau (affiché `LEVEL n+1`), `+0x22` = B (étiquette « magctone »),
`+0x24` = A (étiquette « tonecrys »), `+0x28` pointeur d'image. `FUN_0045da2a`
refuse quand `site+0x2c < B` ou `site+0x2a < A`: A et B sont des coûts en
cristal/magic-tone comparés aux stocks du site (interprétation: coûts, confiance
moyenne). L'index `s` = octet de `0x4a2863 + monde*8 + (type-0x15)` (type 0x15..0x1c),
ligne de catalogue 0..21, via `FUN_00450070`. La table est vide dans l'image
(BSS): écrivain, source (pad.txt ou autre) et expéditeur du message 14000 vers
`IWLocInfo` non identifiés; `this+0x74` est réutilisé de façon incohérente
(index, pointeur, compte). Aucun champ du port ne correspond (pas de rangée
`s`); la correspondance avec `building_tone_cost`/`maintenance_tone_cost` reste
une hypothèse. Pas de port tant que l'écrivain n'est pas trouvé.

### Correction: la table `0x6188c0` est `spells.txt` (REA)

Observation (ev_0e751e17…, ev_6b705a6f…, ev_04e755bc…, ev_71318e69…, ev_4ee89808…,
ev_1e292500…): `FUN_0041C46F` appelle `FUN_004642A3` (ECX = `0x5EC218`), qui charge
`pad.txt`, `floater.txt` puis `spells.txt` par `FUN_00463563`; celle-ci écrit
`this+0x2C6A8 + i*0x2C` (i < 0x20), soit `0x6188C0`. Disposition de la rangée:
`+0x00` nom (32 octets), `+0x20` = `Level` - 1, `+0x22` = `MagCost`, `+0x24` =
`CryCost`, `+0x28` = texte jusqu'à `END`. Le corpus `spells.txt` compte 22 sorts
(ex.: rang 0 « Guérison du Dojo », niveau 1, MagCost 9, CryCost 7). L'indice `s`
de `FUN_00450070` est l'octet `DAT_004A2863[monde*8 + type]` (type 0x15..0x1c),
sans décalage `-0x15` (corrige la note précédente). Les barres 3x55 comparent donc
le coût CryCost (A) et MagCost (B, x2/3 si le drapeau 0x100 du propriétaire) du
sort `s` aux stocks `+0x2a`/`+0x2c` du site; le message 14000 est envoyé par
`FUN_0042FA0F` (cas 0x47) à `IWHallMove`/`IWMove`, pas à `IWLocInfo`.
Non porté: l'état « sort armé » (`this+0x74`) qui détermine `s` n'est pas établi
côté `IWLocInfo` (le panneau l'initialise à 0, d'autres usages l'interprètent
comme pointeur); le port charge déjà les coûts de sorts pour `FA_Cast`.

### Barres de coût de sort du Hall (REA, port avec interprétation)

Observation (ev_55234054, ev_8212125a, ev_bbb1cdc9, ev_469da8cd, ev_0b9148a5):
`FUN_0044003d` (message 0x350d) et `FUN_00440567` (paint) sont deux emplacements
de la même table virtuelle `PTR_LAB_00494458` et partagent le mot `this+0x74`
(initialisé à -1). `FUN_0042fa0f` envoie 0x350d à `IWLocInfo` dans deux branches:
code 6 (valeur -1, si la cible est IWMove/IWHallMove ou un objet de type 0x65) et
code 7 (objet de type 0x65, id de sort 0x15..0x1c, valeur `FUN_00450070` =
`DAT_004a2863[monde*8 + id]`, ligne de `spells.txt`). Le paint dessine les barres
seulement pour l'item 0x2f et `+0x74 >= 0`. L'index est `monde*8 + id` (corrige la
note « -0x15 » plus haut). Les événements 6/7 (survol, sortie, clic) n'ont pas été
retrouvés. Interprétation: aperçu du coût au survol de `BC_Spell1..8`.
Port: `g_hovered_spell_kind` (mis à jour au mouvement de souris, 0x2f seulement),
`game_session_cast_kind_costs` (MagCost/CryCost de `spells.txt`), deux barres 3x55
(x=15 CryCost vs stock `+0x2a`, x=42 MagCost x2/3 si masque 0x100 vs `+0x2c`)
sur 50+25*L, contour indice 1, intérieur indice 4 (2 si coût > stock). Limites:
déclencheur par survol non prouvé, valeur périmée possible au changement de
sélection sans mouvement de souris, L = `source_capacity_4a` supposé.

### Codes 6 et 7 de `FUN_0042fa0f` (REA, déclencheur non tranché)

Observation (ev_b0dfec4e…, ev_120f8b9e…, ev_9fb07007…, ev_d53afc0c…): `FUN_0042fa0f`
est l'entrée 3 de la table enregistrée par `FUN_0041c46f`; `param_1` est un code de
commande de la table, pas un événement souris (`switch(param_1-1)`, codes 6 et 7 =
cas 5 et 6); `param_2` est un enregistrement de contrôle (nom `+0x20`, type
`+0x60`, id de sort `+0x64`). Aucun appel interne ne passe 6 ou 7; leur expéditeur
(`FUN_0046c371` via l'objet de la table, `FUN_004337d9` clavier, `FUN_004293c6`)
n'est pas résolu. Le gestionnaire de glyphes (`FUN_0043dcae`) utilise ses propres
codes (1 = sortie, 6 = déplacement testé, 10 = pression): pas de numérotation
commune démontrée.
Conclusion: rien ne prouve un survol; le port garde l'aperçu de coût au survol de
`BC_SpellN` comme interprétation non vérifiée, au même titre qu'un déclenchement
à l'armement (clic) du sort resterait possible.

### Correction: messages 6/7 = sortie/entrée de survol (REA)

Observation (ev_1d8a9f0b…, ev_ad5951f4…, ev_7b2ad6ef…, ev_e64eb410…): `FUN_0046be81`
est le test de survol: sur déplacement souris sans capture, le contrôle précédemment
survolé reçoit les codes 10 puis 8 et le gestionnaire de groupe (`FUN_0042fa0f`,
entrée 3) reçoit le message 6 (ancien contrôle); le nouveau contrôle reçoit le code 9
et le gestionnaire de groupe le message 7 (nouveau contrôle). Les contrôles sans
`+0x40 == 1`, `+0x38 == 1` ou hors de leur rectangle ne sont pas candidats. Dans
`FUN_0042fa0f`, message 7 sur un contrôle de type `0x65` avec id de sort 0x15..0x1c
envoie à `IWLocInfo` le message 0x350d avec la ligne de sort; message 6 envoie -1.
Les « codes 6/7 » de la section précédente sont ces messages de groupe, pas les codes
de contrôle (6 = bouton enfoncé, 7 = bouton relâché, 8 = survol quitté, 9 = survol
entré, 10 = déplacement avec x,y). Le survol de `BC_SpellN` fixe donc bien `+0x74`
et la sortie du survol le remet à -1: le déclencheur du port est confirmé.
Non vérifié: que les enregistrements `BC_Spell` portent `+0x60 == 0x65`, `+0x40 == 1`
et `+0x38 == 1` (données de contrôle, pas d'observation d'exécution).

### Surbrillance des slots du Hall (REA, pas de port)

Observation (ev_5cc7f5cc, ev_cbd81c59, ev_f8e0a7fb, ev_d9ffc20e, ev_671a1431):
dans `FUN_0042704b`, `param_8 == 1` (ou `entity[0xe] == DAT_005e16ec`) charge la
table de remappage `FUN_004106dd(1,1)` (256 octets copiés dans `DAT_0049a610`) et
met `local_38 = 1`; sur la branche mise à l'échelle, `FUN_00405265` passe alors par
`FUN_00404c5a` au lieu de `FUN_00404770`: même sprite, même position, pixels
dessinés à travers la palette remappée (transparent = indice 0xFF). Pas d'anneau ni
de changement de frame. Les crochets d'angle dépendent de `DAT_005dc668`, pas de
`param_8`. Dans `FUN_00440567`, la surbrillance d'un slot vaut
`*(DAT_005dc64c+0x170) == &0x6137b8[id]` (le floater sélectionné); le port a
`g_selected_floater` pour cela.
Non porté: les couleurs dépendent du contenu de `DAT_004b20f0` (non lu) et le port
dessine des bitmaps alpha sans palette indexée; `FUN_00404c5a` n'est pas décompilée
(l'usage de `DAT_0049a610` est déduit des xrefs). Un contour ou une teinte inventés
ne seraient pas observés. Inconnue: le test `entity[0xe] == DAT_005e16ec`.

### Borne de la grille ACTICON: `DAT_006136b0` = nombre d'îles (REA)

Observation (ev_13ff3710…, ev_b603ce7e…, ev_8c970a17…, ev_f808c6cd…, ev_d266ae75…): le champ
est écrit seulement par base calculée (`0x5EC218 + 0x27498`): `FUN_004637fc`
(initialisation du monde, `tworld.cpp`) y range `DAT_005ebf98[taille du monde]` (0..3),
`FUN_00467be5` le sauvegarde/recharge et `FUN_00462f1d` le remet à zéro. Les
lecteurs (`FUN_0045eaa7`, `FUN_0045388f`, `FUN_0045f121`) bouclent `i < compte` sur des
enregistrements d'île de `0x29e8` octets.
Inférence (confiance moyenne): c'est le nombre d'îles du monde actif, ce que suppose le
port (`g_game_session.island_count`). La valeur 15 n'est pas lisible statiquement (tables
`DAT_005ebf98/005ebd68` nulles dans l'image, remplies à l'exécution).

## Tâche 0xd (Obtain) et ordres Attack/Defend (REA, ev_639001c8…, ev_7b696e7a…, ev_8753775e…, ev_534c32c0…, ev_17f694ec…)

Observation: `FUN_004662b7` range le paquet (mots: catégorie, joueur, type, site, île, emplacement de bâtiment,
sous-type) dans la table de 64 entrées; `entry+4` est le compteur d'attachés, incrémenté et décrémenté par
`FUN_00421ec1` (qui copie type, île, bâtiment et paramètre dans le floater: `+0x38` index de tâche, `+0x3c`
type, `+0x40` île, `+0x42` emplacement, `+0x44` mot 7). Personne ne balaie la table pour le type 0xd; l'automate
de floater `FUN_004211bb` (`switch(type-1)`, type 0xd = cas 0xc) passe à l'état 13 avec `+0x32` = emplacement ou,
si le floater porte déjà l'objet voulu (`+0x18 == mot 7`), à l'état 4 vers une cible trouvée par
`FUN_00420e94(2, joueur)`. Le site d'attache (`FUN_0041e569`?) n'est pas décompilé. `FUN_00466533` efface
l'entrée et `FUN_00420669` détache les floaters. Les ordres `Attack`/`Defend` (`FUN_0045d867`: `+0x28` = mot
`floater+0xe` de la table `0x6137b8`, `+0x2c` = 6 ou 8, `+0x30` = id; `FUN_0045d8b2`: lieux, genres 7 et 9) écrivent
dans l'objet session `0x5ec218`; aucun lecteur des genres 6..9 n'a été trouvé.
Interprétation: le ramassage natif ressemble à un pool de tâches pour floaters libres plutôt qu'à l'ordre à un
floater choisi du port (`game_session_order_floater_to_ground_object`, action 0xd, état 13), dont l'état 13 et
l'annulation (commande 12, `cancel_ground_pickup_order`) correspondent à l'automate natif. Non porté: attache
automatique, ordres `Attack`/`Defend`/`Recall`. Inconnues: appelant d'attache, `FUN_0045dcf4`, lecteurs des
genres 6..9, porte `FUN_00450385`.

### Attache automatique et ordres en attente (REA, ev_7b65b0885c0f…, ev_16b5390f45dc…, ev_bd805382bd75…, ev_349b14e0b6a5…, ev_dce3014d7fa8…)

Observation: la table des tâches natives (64 entrées de 0x14 octets, base `0x6183bc`) est parcourue par le
sondage `FUN_0042219e` (appelé par `FUN_0041e569` et `FUN_004239e9`) pour un floater libre de classe != 4, sans
lien de charge (`+0xc == -1`), de sous-type != 8, hors ordre de type 4/6/7 en cours, avec `DAT_006191b4 == 0`. Un
candidat doit être actif, du même propriétaire, différent de l'entrée courante, accepté par `FUN_00422031` (cas 4, 5,
0xb et 0x12; le type 0xd n'a pas de cas et passe) et par `FUN_0041e454` (classe 1 pour les types 6, 0xd, 0xb, 0x11 et
le type 4 de charge 5..33). Choix: première entrée valide dans l'ordre d'index pour la classe 1 (cap: compteur
`+4 < 1`, une seule attache à la fois pour 0xd, pas de distance); les autres classes utilisent le rang `+6`.
`FUN_00421ec1` copie genre, île, site et charge dans le floater (`+0x3c/+0x40/+0x42/+0x44`) et appelle
`FUN_00466533` si l'ancienne entrée était de type 0xd ou 4. Les ordres en attente 6..9 (`+0x28/+0x2c/+0x30` du
floater, écrits par `FUN_0045d867/d8b2/dcf4`) sont lus par `FUN_00422d27` (genre 8: cible floater, genre 9: lieu,
arrivée à moins de 100) et `FUN_0045de20`; le sondage n'attribue rien aux genres 6 et 7; la branche physique du genre 6
(attaque) n'a pas été trouvée.
Port: le ramassage est une commande à un floater choisi, sans table de 64 entrées, sans compteur `+4`, sans
admission `FUN_00422031` ni classe `FUN_0041e454`, sans attache automatique, sans effacement `FUN_00466533`. À porter pour
la tâche 0xd: création par le bouton `Obtain` (paquet type 0xd), attache automatique du premier floater libre
(compteur < 1), état 13 déjà modélisé, détachement et effacement à la fin.

### Ordres Attack/Defend/Recall: enregistrement de bâtiment et adoption (REA, ev_242a6f46…, ev_8520758d…, ev_7b65b088…, ev_3477c421…, ev_8578fcc7…)

Observation: `FUN_0045d867`, `FUN_0045d8b2` et `FUN_0045dcf4` n'écrivent pas dans le floater cible mais (inférence forte) dans
l'enregistrement source de 100 octets du bâtiment sélectionné (`&0x6192b0 + emplacement * 100 + joueur * 0x14a0`): `+0x28` île,
`+0x2c` genre (6 attaque floater, 7 attaque lieu, 8 défense floater, 9 défense de zone ou rappel), `+0x30` cible. Le sondage
`FUN_0042219e` fait adopter cet ordre à chaque floater de classe différente de 4 dont le lien de charge (`+0xc`) désigne
l'emplacement et dont l'état n'est pas `0x13` (`+0x2c` → `+0x3c`, `+0x28` → `+0x40`, `+0x30` → `+0x42`); les genres 6 et 7 sont
exclus de l'attribution automatique. Comportement par genre (automate `FUN_004211bb`, `FUN_0041e569`): 6 approche (`0xf`) puis frappe
périodique du floater cible (`6`, `FUN_004200d2`); 7 déplacement lointain (`0x10`) puis frappe du bâtiment (`7`, `FUN_00420188`); 8 suivi du
floater protégé (`8`, `FUN_00422d27`, arrivée à moins de 100) avec bascule en `0xf` puis `6` si un ennemi est trouvé
(`FUN_004208eb`); 9 déplacement vers le site (`9`, `FUN_0041e427`, `FUN_004672a6` < 100) puis recherche d'ennemi au site
(`FUN_00420829`) ou relance (tenue de zone). Un floater de sous-type 8 sans ordre retourne au genre 9 à son domicile.
Port: genres 6/7 (auto-attribution), 8 (`defend_target_floater`) et 9 (`game_session_advance_action9`, partiel: pas de tenue de
zone ni de relance) existent par floater; absents: l'enregistrement d'ordre du bâtiment et l'adoption par lien de charge, les boutons
`Attack*`/`Defend*`/`Recall`, et l'écriture des ordres joueur par le paquet de catégorie 1. Inconnues: ECX exact des écrivains, cible de
`Recall` (`FUN_00452e2b`), effets de `FUN_00415fc6`, double rôle de `+0x32`.

### Ordres des boutons de bâtiment: attaque, défense, rappel (REA, ev_e29c42ec, ev_0b6984d3, ev_08044150, ev_55875c8f, ev_2788be00, ev_fca9efc0)

Observation: l'ordre est écrit dans l'enregistrement source du bâtiment (`+0x28` cible, `+0x2c` genre, `+0x30` id/cellule, `+0x32` 0).
`FUN_0045d867` (flotteur ciblé): genre 6 attaque, 8 défense (mode 0x12). `FUN_0045d8b2` (site/zone): genre 7 AttackLoc, 9 DefendArea
(mode 0x13). `FUN_0045dcf4` (Recall, sans curseur): genre 9 vers la cellule `((x+5)/10)<<8 | (y+5)/10` du bâtiment (`FUN_0041e3eb`).
Curseurs (`FUN_0043530b`): 0x10 AttackFlt, 0x11 AttackLoc (0xd, ou 0xb si site sélectionné), 0x12 DefendFlt (5), 0x13 DefendArea (0xf);
mode 0xf sans armement. Adoption (`FUN_0042219e`): un flotteur dont le lien `+0xc` désigne le bâtiment et dont l'état n'est pas 0x13 copie
`+0x2c/+0x28/+0x30/+0x32` vers `+0x3c/+0x40/+0x42/+0x44`. États (`FUN_004211bb`): 6 approche (0xf) puis frappe (6); 7 déplacement (0x10)
puis frappe bâtiment (7); 8 suit la cible puis cherche un ennemi (`FUN_004208eb`); 9 va au site, attaque l'ennemi du site
(`FUN_00420829`/`FUN_00420d97`) sinon retourne; 0xd Obtain -> 0xe (minuterie 0x3c).
Inconnues: qui écrit le lien `+0xc` d'un flotteur vers un bâtiment; `FUN_0045d5ba` (visibilité des boutons du propriétaire); branche
classe 4 de `FUN_0042219e`; sens exact de `+0x28` de `FUN_0045dcf4`. TrnStk, UpgSpread et Obtain non revérifiés. Non porté.

Suite (REA, ev_f90d1eb1…, ev_aaf759e7…, ev_e3322fcb…, ev_ab48501a…): le lien `+0xc` n'est écrit ni par `FUN_0042219e`, `FUN_00421ec1`
ni `FUN_004207f2`; il l'est par l'automate `FUN_004211bb` (charge `+0x44` = emplacement du bâtiment, objet porté `+0x18`, 1 ou 0 à la
libération). `FUN_00421ec1(-1)` (détachement) ne le remet pas à 0. Interprétation (confiance moyenne): le lien est posé quand un flotteur
prend un ordre, pas à la naissance (non trouvée). Le test « classe 4 » est `*(int*)rec == 4` sur `+0` (propriétaire), sans usage du lien.
Visibilité (`FUN_0045302a` puis `FUN_0045d5ba`, liste construite sans condition; 5 en tête, 2 en fin): type de site 0x2c..0x2e ajoute
0x10..0x13 et 0xf; 0x2f/0x30 ajoutent 6 et 0x15..0x1c; Obtain (4) pour type 1 sous-type 5..0x21 sans test de propriétaire; Repair (3)
pour type > 0x24 sauf 0x2a; liste du propriétaire seulement si emplacement `+0x18 != -1`. Obtain: ordre 0xd = si l'objet porté vaut
`+0x44` chercher un emplacement de type 2 (action 4), sinon aller vers l'île `+0x40` (action 0xd, `+0x46 = 1`); la minuterie 0x3c
appartient à l'ordre 0xe. Inconnues: naissance de `+0xc`, `FUN_00420e94`, `FUN_004210a9`, `FUN_00425084`, `FUN_004502dc`, `FUN_00452a15`,
`FUN_00466533`; pas de table de stride 0x13 vs 0x4c à clarifier.

Passe Obtain (REA, ev_935e70f7, ev_7864c1e4, ev_b112d391, ev_de447f6b, ev_4be246fe, ev_49f6c42a, ev_282d6ab2): stride de la table de
flotteurs confirmé à 0x4c octets (`IDIV 0x4c` dans `FUN_0041e569`; le `*0x13` de Ghidra compte des dwords). `FUN_00420e94` délègue à
`FUN_004626f8` (balayage de 0x29a8 enregistrements de 0x30 octets, type 0..3, meilleur par distance). `FUN_004210a9` choisit dans la
table joueur `0x5ec640 + joueur*0x29e8` (entrées de 0x60) l'entrée `+4 == 2` avec `+0x1c & 1` (préférence `+0x36 == paramètre`, sinon
la plus proche) et pose action 0x11, `+0x32` = indice. `FUN_00425084` (objet porté 5..0x21): dépose dans une entrée libre du joueur
(`+4 == 0`, `+0x14 == -1`, `+0x10 == 0`), sinon incrémente le compteur d'attente `DAT_006191fc[joueur*0x14a0 + objet*2]`.
`FUN_004502dc` renvoie `+0x24` si l'état `+0x10 == 1`. `FUN_00452a15` remet l'enregistrement à zéro (pas la naissance).
Interprétations: type 2 = emplacement prêt; l'objet 5..0x21 est un identifiant d'inventaire. Inconnues: bâtiment dont vient le stock,
fin de tâche, naissance des flotteurs (aucun `rep stosd` de 0x13 dwords; ~150 références à `0x6137b8` non lues). Non porté.

Naissance et lien (REA, passe 3): création des flotteurs toujours introuvée (les accès `ECX+0x275a0` n'apparaissent pas dans les xrefs
absolus). `FUN_00467101(idx)` est la libération (assert `num < MAX_FLOATERS`, `*rec = -1`, compteur à `0x6183b8` décrémenté). `FUN_0045c470(idx)`
rattache un flotteur à un emplacement de personnel du bâtiment (8 emplacements `+4..+0x12`, compte `+0x24 < 8`) puis écrit
`rec+0xc = FUN_0045c325()` = indice de l'enregistrement bâtiment `(ptr-0x6192b0-tribu*0x14a0)/100`; appelée via `FUN_0041e569` états
0xa/0xb (production). Donc `+0xc` = indice du bâtiment, posé au rattachement (cohérent avec l'adoption de `FUN_0042219e`).
`FUN_00416a9a(0, rec)` met en file l'évènement « naissance » (sons `levbirth`/`fltbirth`). Piste suivante: appelants de la liste d'île
`DAT_00618fb4` (0x4355f3, 0x435648, 0x43870b, 0x4517c2, 0x451e62, 0x45eb89, 0x45f67e).

Création des flotteurs (REA, ev_4dd79568, ev_05ced3dc, ev_c7ef5dde, ev_c21b24fd): `FUN_00466fe4(type, sous-type)` est l'allocateur
(objet monde `0x5ec218`, garde compteur `+0x2c1a0 < 0x100`, premier enregistrement `*rec == -1`; sous-type borné [9,0x11] pour le type 4,
sinon [0,8]); écrit `+0` type, `+4` sous-type, `+8` 0, `+0x14`, `+0x20`, `+0x22`; n'écrit ni `+0xc`, `+0xe`, `+0x2c`, `+0x38`, `+0x3c`
ni `+0x1c`. Enveloppe `FUN_00462a87(type, ?, x, y)` (assert type 0..4; type 4 limité à 0x80 vivants): écrit `+0xe` île, `+0x10/+0x28` x,
`+0x12/+0x2a` y. Appelants: `FUN_004532e2` (naissance par un bâtiment: ensuite `FUN_00416a9a(0, …)`, `owner+0x5c` = indice, `rec+0x1c |= 0x801`),
`FUN_0046466f` (initialisation d'île, types 0..3 par emplacement), `FUN_00464e4d` (début de partie, type 4, sous-type `rand(8)+10`),
`FUN_004672ef` cas 0 (5 apparitions, y = rand(300)) et 0x14. Valeur initiale de `+0xc`: non écrite, inconnue (ne pas supposer 0).
Inconnue: appel 0x42ff6e dans `FUN_0042fa0f`; appelants de `FUN_004532e2`/`FUN_004672ef`.

Population de départ native (REA, ev_3cb7946b30cb, ev_424bed26fa19, ev_649d4571fe34): `FUN_0046466f` boucle `k = 0..3` (joueur `k`, ou
`base + (k&1)` en mode 1) et appelle 4 fois `FUN_00462a87(k, 0, x_île, y_île)` : 16 apparitions, types 0..3 dans l'ordre, sous-type 0, sans
décalage aléatoire, à l'île choisie (mode 0: 1re île active pour `k` pair, 4e pour `k` impair; salle = île `+2 == 0 && +8 == 0` la plus proche).
Léviathans (`FUN_00464e4d`, état 2, tick 40): un `FUN_00462a87(4, rand(8)+10, …)` par flotteur de type < 4 dont le propriétaire est `cur-1` et le
sous-type != 8 (jusqu'à 16), sur l'île non spéciale de `cur`; plafond 0x80 vivants. Le remake (`game_start.c`, 4 par joueur,
`GAME_START_FLOATERS_PER_PLAYER`) est compatible pour le compte; placement et ordre d'indices (type 0 puis 1..3, 4 chacun) non revérifiés.
Inconnues: paramètres réels (appelants des thunks `0x4013d4`, `0x4023fb`), propriétaire à l'appel de `FUN_00462a87`, drapeaux `DAT_006191f8`.

Comparaison remake (lecture de `game_session_animation.c`): le remake ne crée de léviathan que par le générateur de sites (`spawn_leviathan_floater`, modèle de
`FUN_00450a71`, seuil de difficulté); aucun équivalent de la création de départ de `FUN_00464e4d` (état 2, tick 40: un type 4 de sous-type
`rand(8)+10` par flotteur de type < 4 dont le propriétaire est `cur-1`). Rôle exact de cette machine (séquence d'ouverture? état 2 -> 3 à
tick 1000) non établi; non porté.

Machine `FUN_00464e4d` (REA, ev_e22cb8ca…, ev_cffabb90…, ev_83def11e…, ev_a3043bb8…): séquence scriptée à ticks fixes, pas un mode de débogage.
États 0 et 6 inactifs; 0 -> 1 par `FUN_00466ce2` quand le premier dword de l'enregistrement du joueur courant (`this+0x2d030 + DAT_0049f538*0x14a0`)
est non nul; état 1 attend le tick 100 puis 3; état 2 (aucune transition entrante trouvée): tick 0 `FUN_004655b2(0xb)`, tick 0x28 apparition des
léviathans (placés à la position du 1er enregistrement qualifiant, minuterie 0x14), tick 1000 -> 3; état 3 fondu (`FUN_00410765`), tick 100 `FUN_0046c1b4(1,2,0)`,
puis 4 (tick 350) ou 5 (tick 1299) selon `local_c`; état 5 tick 100/160 `FUN_0046c1b4(1,7|0,0)` et `DAT_004bf120 = 0`, tick 200 -> 6.
Appelée seulement par la boucle principale (`DAT_004bf120 != 0 && DAT_004bf124 == 0`). Monde: `FUN_004637fc` n'est appelée que par `FUN_004121b7` cas 9
(`FUN_004637fc(this+0x138, this+0x13c, DAT_004c2b9c != 0, DAT_0049c9b0)`), qui est le même cas qui pose `DAT_004bf110` (voir cadence).
`FUN_00462a87` depuis `FUN_0046466f`: ECX = enregistrement joueur `S(p)`, donc propriétaire = `p` (joueur), `k` est le type.
Inconnues: écrivain de l'état 2 et du dword `+0x2d030`; variante `local_c` du mode solo; commande 9 envoyée par le menu non vérifiée. Léviathans de
départ non portés tant que l'état 2 n'est pas établi comme atteint en jeu normal.

État 2 (REA, ev_489f6ae9…, ev_e6404a40…, ev_79d1691e…, ev_42a7b18b…): état = `0x6191B4`, tick = `0x6191B6`, dword joueur = `0x619248`. Écrivains de l'état:
`FUN_004637fc` (0, init), `FUN_00466ce2` (0 -> 1 si dword != 0), `FUN_00464e4d` (1 -> 3, 2 -> 3, 3 -> 4/5, 4 -> 5, 5 -> 6; n'écrit jamais 2),
`FUN_004672ef` cas 0x15 (3), `FUN_00467BE5` (chargement de sauvegarde) et `FUN_00460460` @0x4606B6 (**seul écrivain de 2**, garde: état 0, dernier
joueur traité, aucun enregistrement d'unité de type 0x17..0x24). `FUN_00460460` est le décompte par île des flotteurs de type 4, appelé par `FUN_00462a87`
après une apparition de type 4. Interprétation: la séquence de léviathans de départ de l'état 2 se déclenche à la première apparition de léviathan, pas depuis le
menu. Le dword `0x619248` n'est remis à 0 que par `FUN_0046466f` et ne devient non nul que par chargement de flux (aucun écrivain direct).
Inconnu: si `FUN_00460460` s'exécute dans une partie solo normale (aucun appelant direct résolu). Non porté.

Atteignabilité de l'état 2 (REA, passe finale): `FUN_00460460` (thunk `0x401226`) est appelée par `FUN_00453a5f`, `FUN_00462a87` (type 4), `FUN_00464b9e` (arg -1) et
`FUN_00466c8b`. Garde de l'écriture de 2: état 0, île traitée = dernière, aucun enregistrement de type 0x17..0x24 dans son tableau (`île+0x428`, entrées de 0x60).
`FUN_00464b9e` pose justement ces types (`c + 0x17`, état 4, `+0x45c = 30000`) dans la dernière île avant d'appeler `FUN_00460460(-1)`: la garde est donc fausse
après l'initialisation. Interprétation: en partie normale l'état 2 (léviathans de départ) n'est pas atteint; ce serait un reste de séquence d'ouverture ou
de mode non utilisé. Non porté, aucune action nécessaire. Inconnu: ordre exact des chemins de haut niveau vers les 4 thunks.

Adoption précise (REA, ev_21a176c7…, ev_80a249b2…, ev_7b696e7a…, ev_560ab863…, ev_f90d1eb1…): `FUN_0042219e` (tick de flotteur si action 0 ou `tick % 10 == 0`) sort si l'action `+0x2c` vaut 6 ou 7 ou si `DAT_006191b4 != 0`. Le bloc « enregistrement » ne tourne que pour propriétaire (`+0x00`) différent de 4 et lien `+0xc != -1`:
`rec = 0x6192b0 + lien*100 + propriétaire*0x14a0`. Drapeau `+0x1c & 0x10` -> `FUN_00421d82` et fin. Si `rec+0x4c == indice du flotteur`: état != 0xc et pas de drapeau `0x20` -> détache, état 0xc, `+0x40 = rec+0`, `+0x42 = rec+2` (copie sautée). Sinon, état 2 avec drapeau 1: sauté; sinon un test de distance peut poser l'état 2 (`+0x44 = 0/1`).
La copie a lieu si l'état n'est pas `0x13` et que l'un de état/`+0x40`/`+0x42`/`+0x44` diffère de `rec+0x2c/+0x28/+0x30/+0x32` (pas de test `rec+0x2c != 0`; un 0 copié devient l'état 0xe). Copie: `FUN_00421ec1(-1)`, `état = rec+0x2c`, `+0x40 = rec+0x28`, `+0x42 = rec+0x30`, `+0x44 = rec+0x32`, `+0x46 = 0`; le lien n'est pas écrit.
La fonction n'efface jamais `rec+0x2c`: l'ordre est réappliqué à chaque passage. Propriétaire 4 (léviathan): sous-type 9 -> état 1 vers l'île `+0x0e`; autres sous-types: état 6 (bâtiment le plus proche `< 150`, ou `< 3000` avec drapeau `0x80`) ou 7; aucune copie. États 6/7 approche puis frappe, 8 suit, 9 site, 0xc dépôt, 0xd Obtain -> 0xe (minuterie `+0x34 = 0x3c`).
Correction: les drapeaux sont en `+0x1c`, pas `+0x18`. Inconnues: écrivains de `rec+0x4c` et `rec+0x2c` (Recall non relu), `DAT_006191b4` hors partie normale (l'état 6 de `FUN_00464e4d` bloquerait l'adoption globale), espace d'indices flotteur/bâtiment.

Écrivains de l'ordre et état du monde (REA, ev_e9e981a4…, ev_c9ba49c0…, ev_eb5b6cab…, ev_349b14e0…, ev_592a62cd…, ev_4e786cad…, ev_c01195f2…, ev_424bed26…, ev_a34a7d43…): `rec+0x2c` est remis à 0 par `FUN_004500c4` (remise à zéro; efface aussi `+0x28/+0x30/+0x32`, pas `+0x4c`) et `FUN_004528ca` (initialisation: `+0x2c/+0x28/+0x30 = 0`, `+0x32 = 1`);
écrit 9 par `FUN_0045dcf4` (Recall, `+0x28/+0x30/+0x32 = 0`), 6 ou 8 par `FUN_0045d867`, 7 ou 9 par `FUN_0045d8b2` (sans appelant direct). Aucun écrivain « annuler » trouvé: seules les remises à zéro ci-dessus. `rec+0x4c` (flotteur lié): `0xffff` par `FUN_0045c82f` (détachement) et `FUN_0045c3fe` (initialisation d'enregistrement),
indice d'emplacement par `FUN_0045c470` (rattachement, écrit aussi `flotteur+0xc`) et `FUN_0045cd75` (choix du candidat à 0x45d14d). `DAT_006191b4`: écrit seulement par `FUN_00460460` (2, garde état 0) et `FUN_004672ef` cas 0x15 (3); la machine `FUN_00464e4d` ne tourne qu'hors états 0 et 6 et y passe via `in_ECX+0x2cf9c`; l'état 6 n'est pas atteignable depuis 0 par la machine seule.
Conclusion: l'adoption (`FUN_0042219e`, bloquée dès que l'état != 0) fonctionne en partie normale tant qu'aucun évènement du cas 0x15 ni chargement de sauvegarde ne s'exécute (non prouvé); un ordre de bâtiment persiste jusqu'à remise à zéro de l'enregistrement. Inconnues: appelants de `FUN_0045d867/8b2`, données du cas 0x15, lecteurs bruts non décodés.

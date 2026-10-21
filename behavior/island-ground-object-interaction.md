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

# Inconnues et limites

## Économie et flotteurs travailleurs

- Le remake conserve un ledger interne de trois ressources attaché au hall et un code de sortie `PROD` observé. Les commandes prototypes de worker (clic droit, collecte, retour `D`, raccourcis `B/C/M`) ont été retirées du source et de l'exécutable courant. La sélection worker doit seulement montrer ses stats (XP/PV); seuls soldats et mages reçoivent les ordres autorisés par le code d'origine. Le clic de construction doit créer un ordre différé exécuté par des workers autonomes; les travailleurs inoccupés naviguent paisiblement. Les panneaux, règles et chemins exacts sont encore à tracer; voir [`ToneRebellion_Remake/TODO.md`](../ToneRebellion_Remake/TODO.md).
- Observé dans Ghidra : `FUN_0043edac` affiche les trois compteurs de sa fenêtre; `FUN_004459e6` lit trois valeurs dans le record du hall à `+0x28/+0x2a/+0x2c` et compare les ressources avec une formule basée sur `+0x4a`. L'interprétation de cette formule comme capacité n'est pas confirmée. Dans `FUN_0044338b`, `CHARGE` lit le short `+0x22` du record sélectionné et la valeur `+8` obtenue via `FUN_00464242(objet+0, objet+4)`. Cette dernière adresse indexe la table parsée de `floater.txt`, mais les pseudocodes inspectés ne nomment pas les champs objet `+0/+4`; `FUN_004500c4` remet `+0x22` à zéro au reset, alors que `FUN_004528ca` ne l'écrit que sous une condition précise. Ne pas encore afficher ce ratio dans le remake.
- À résoudre depuis le binaire : les gates d'entrée par classe d'unité; panneaux sélection unité/bâtiment et hit regions de la barre basse; création, sélection et exécution autonome des ordres de construction; navigation paisible des workers sans tâche; activation du bit `PROD` `0x002`; affectation des requêtes différées catégorie 4; stock initial/capacité/rendements/coûts. Pistes REA : suivre les écritures +0x28/+0x2a/+0x2c, les états dans `FUN_0041e569`, les événements `FUN_00465793`, le routage UI et les opérations sur les tone fields.
- Liste courte : [`ToneRebellion_Remake/TODO.md`](../ToneRebellion_Remake/TODO.md).

---

# Inconnues et limites

## À traiter

- Le contrôleur d'ordres au niveau des floaters est localisé : `FUN_004211bb` exécute les ordres, `FUN_0042219e` les réévalue, et `FUN_00420a55` sélectionne des candidats. La table `FA_*` et les branches Leviathan 9–17 sont désormais documentées dans [enemy AI](../behavior/enemy-ai.md). L'utilisateur confirme le rôle gameplay constructeur des Vspore : ils contaminent des emplacements de bassin (nouvelle source ennemie) ou de bâtiment (construction ennemie). À tracer encore dans le binaire : quel sous-type brut d'emplacement distingue ces issues et comment la production de sources et la construction des bâtiments se déroulent ensuite. Restent aussi à résoudre les priorités et sémantiques des autres candidats, les conditions et règles de la stratégie globale CPU, la sélection autonome de sorts, et l'effet exact de `DIFFICULTY` sur les ordres.
- Aucune fonction interne candidate ne reste en attente dans l’index pour le profil analysé. Le résultat couvre les 2 410 procédures observées par Ghidra, sans garantir que Ghidra ait reconnu toute région de code possible du binaire.
- Les 780 thunks sont indexées comme wrappers exclus du lot interne ; leur cible Ghidra est conservée lorsqu’elle est disponible.
- Les 123 fonctions externes sont indexées comme imports sans corps décompilable.
- Des helpers et bibliothèques du runtime peuvent subsister parmi les 1 493 procédures `internal`. Les 14 procédures classées `runtime` sont celles du chemin d’entrée C et de ses helpers directs identifiés à partir des appels/pseudocodes observés ; cette frontière est une classification analytique.

---

# Inconnues et limites

## Limites observées

- Aucun fichier `Float.pdb` n’est disponible pour cette analyse (information fournie par l’utilisateur). Une éventuelle référence au nom `Float.pdb` dans les informations de débogage PE n’établit pas que le fichier lui-même soit présent. Les noms d’origine et types source peuvent manquer.
- L’inventaire de chaînes couvre les objets de données définis par Ghidra ; les données non définies ou empaquetées peuvent ne pas apparaître.
- Les pseudocodes Ghidra sont des reconstructions non compilables et non équivalentes au source d’origine.
- La session Ghidra active est temporaire/éphémère. La fermer supprimerait son projet temporaire et son état d’annotation ; conserver la session pendant les travaux.
- Le call-site direct du parseur de `shapeinf.txt` n’est pas encore localisé. `FUN_0042704b` (`fltdraw.cpp`) consomme bien des descripteurs en mémoire pour choisir les formes et intervalles de frames du corps et des jambes, mais le lien entre ce descripteur et les directives du fichier reste à vérifier. Le remake n’utilise donc que les cadres de travailleur de base explicitement listés dans le fichier local; ses états de mouvement/transport/attaque ne sont pas encore portés.
- Le remake dispose d’un écran de surface initial : il charge panorama, palette, octets HZT et sites ordonnés de `ISLANDnn`; `island_haze.c` reproduit les deux tables 8×256 de `FUN_00410510`, mais leur application aux sprites attend les niveaux de brume par objet. Les sites non résolus restent des marqueurs de diagnostic. Les 16 unités flottantes sont dessinées avec les SHP de leurs tribus et leur cycle de vol de base. La sélection d'un ouvrier de départ affiche maintenant le panneau `IWLocInfo` dérivé de `FUN_0044338b` (HITS 3/3, STRENGTH 0, WORKER); les autres classes et panneaux/actions de bâtiment restent à porter. Les contrôles directs de worker ont été retirés. Les ordres soldats/mages, la construction différée et l'autonomie des workers doivent encore être suivis dans le binaire; les workers sans tâche doivent naviguer paisiblement. Les états avancés, effets, autres sprites et simulation restent à reconstruire. L’interface est Win32/GDI; SDL3 reste à faire. Les consommateurs de `WORLDSIZE`, `DIFFICULTY` et `TRIBE0..3` restent à tracer.
- Le noyau de déplacement et le chemin de souris ont été partiellement observés : `FUN_0041e3eb` quantifie une destination sur une grille de 10 px; `FUN_00422d27` effectue un pas, et les états `0x0e/0x0f` passent par les fonctions de déplacement. `FUN_00435581` fait le hit-test des floaters; `FUN_00435826`, via `FUN_004337d9`, émet le message de sélection `0x3f`. Ces procédures prouvent des primitives de sélection/déplacement et un chemin d'ordre, mais pas que la classe initiale `*work` puisse recevoir des ordres. Les commandes de worker et raccourcis prototype ne sont plus exposés par le remake. Le filtrage classe/état, les panneaux de sélection unité/bâtiment et les zones interactives réelles doivent être établis depuis les handlers du binaire. Le cycle d'attribution de tâches/idle autonome et la construction différée doivent être reconstruits avant d'activer ce gameplay; voir [`ToneRebellion_Remake/TODO.md`](../ToneRebellion_Remake/TODO.md).

---

# Inconnues et limites

## Premières observations revalidées

- Ghidra nomme la fonction à `0x478460` `entry`. Son corps prépare le démarrage du processus, puis appelle `thunk_FUN_0041d8e1` à `0x402149`, dont la cible observée est `0x41d8e1`. Interprétation : démarrage runtime C probable.
- `0x41d8e1` journalise la chaîne de version `1.16F`, lit notamment `gamey.txt`, `newtext.txt`, `bldtxt.txt`, `bldname.txt`, `plotobj.txt`, `tonehelp.txt` et `names.txt`, puis appelle l’initialisation fenêtre et la boucle de traitement.
- `0x41c1d6` observe l’enregistrement de la classe `Float Class`, la création d’une fenêtre `Tonus Rebellious`, une requête de fréquence de performance, et un chemin conditionnel lié à `sound.txt` / `DXSOUND`.
- `0x41c46f` contient une boucle de traitement, des appels d’initialisation/affichage, et des chaînes telles que `data\\logo.gif`, `data\\logo.pal`, `windows.txt`, `effects.txt`, `fltinf.txt` et `bldinf.txt`. Les call-sites de ces trois derniers fichiers sont maintenant reliés à leurs parseurs dans `data_catalog.md`.
- Ces observations proviennent des pseudocodes et chaînes référencées dans les Evidence IDs du manifeste ; aucune exécution n’a été observée.

---

# Inconnues et limites

## Procédures sans pseudocode interne

- Les 780 thunks ont un corps de transfert, mais sont exclues du lot des corps internes; la cible Ghidra est conservée quand elle est résolue.
- Les 123 procédures externes sont des imports sans corps fourni par le binaire.
- Aucun résultat interne n’a été marqué `no_body` ou `decompile_failed` dans les 1 507 procédures internes/runtime traitées.

---

# Inconnues et limites

## Inconnues comportementales après la première cartographie

### Ressources et ouvriers (suivi 2026-10-17)

- `FUN_0045eaa7` observe les trois modes de réserve et crée/annule des demandes différées de catégorie 4 quand un stock est sous le seuil source. `tonehelp.txt` en précise les trois modes d'interface. `FUN_004503bd` modifie les stocks du hall aux offsets +0x28/+0x2a/+0x2c et apparaît dans les transitions du tick floater `FUN_0041e569`. L'affectation de demande → worker → site de prélèvement → dépôt reste à reconstruire.
- `FUN_0045f755` fait cycler les modes bruts du hall 0–2; le mode 2 déclenche les demandes de remplissage dans `FUN_0045eaa7`. `FUN_00465793` traite un événement de sous-type 4 en ajoutant une unité au stock et en décrémentant son compteur d'attente. L'étape exacte de ramassage/transport qui crée cet événement n'est pas encore rattachée.
- Acquisition d'un site `PIT_Object` (`item=1`) : le chemin `IWLocInfo` grab/place est maintenant documenté dans [`behavior/island-ground-object-interaction.md`](../behavior/island-ground-object-interaction.md). Il exclut item 1 comme source d'un grab manuel mais l'accepte comme cible libre. Un clic carte depuis Inventory émet séparément une commande différée catégorie 0/type 4 avec le sélecteur actif (`ev_6ac7cc6650dc8a0e9b412c055606948d1c6dbbdd3e6c6df0a7fcc1551764419e`); son effet final ne prouve ni placement effectif ni collecte d'un item 1. Le tag `pickup` de `fltinf.txt` est lu par `FUN_00454d1f` (`ev_6ccf11adf4100a01f329d47d35c0c8bd1d7e5c6fcff4d70ee2a0c846e156a876`); son consommateur pour une collecte automatique n'est pas identifié. Le producteur de catégorie 3/sous-type 4 et la mutation du record item 1 après contact restent à tracer.
- `FUN_00450a71` atteste que la fin d'un `PROD` pour item `0x25/0x27/0x26` écrit le code de sortie 1/2/3 à runtime `+0x24`; les IDs catalogue sont P-BLDTON/P-MAGTON/P-CRYTON dans cet ordre. Ne pas en déduire le contrôle joueur, le transport ni le stockage: ils exigent le traçage des consommateurs et événements. Les contrôles clavier de stock et les ordres manuels du remake sont non validés.
- Restent inconnus : classe-gates de sélection/ordre, panneaux UI et barre basse, modèle de tâches/idle worker, ordre de construction et son exécution, activation de `PROD` `0x002`, flux des workers automatiques, quantité/cadence, capacité du hall, stocks initiaux et coût débité. Le seuil `hall[+0x4a] * 50 + 150` est observé dans la demande automatique et ne doit pas être renommé capacité sans preuve supplémentaire.
- Suivi court et prochaines étapes : [`TODO.md`](../ToneRebellion_Remake/TODO.md).

- Rendu d’île partiel : `FUN_0040bf98` dessine maintenant `BASE`/`CHUG`/`GLYP`/`INCI`/`CONS`/`PROD`/`OCCU`/`BARG`. Pour POOL, cette fonction superpose le CHUG animé sur son BASE statique; le remake reproduit désormais cet ordre (BASE frame 1 puis CHUG frames 2–40 de `bldinf.txt`). `FUN_00450a71` met à jour `+0x3a` et `+0x3c` selon la classe et les flags ; `FUN_004528ca` initialise `flags=0x410`, `+0x32=1`, et `FUN_004500c4` remet les champs animés à zéro. Le bit `0x001` n’est pas activé par le prototype faute de simulation de construction, donc CHUG classe 0 reste au début du segment et GLYP reste inactif jusqu’à activation. `INCI`/`CONS`/`PROD` sont rendus depuis leurs compteurs par site, qui restent à zéro tant que leurs transitions gameplay ne sont pas portées. Le frame BARG utilise la formule d’assembleur `FISTP((last-first+2) * double(objet+0x50))`; la sémantique gameplay et l’auteur du champ `+0x50` restent inconnus, le remake préserve ce champ à zéro. Le timer UI de 33 ms reste une approximation de la cadence source. `FUN_0040ab42` est associé à `PADS` et calcule tick/(vitesse + objet[+0x0c]) puis ajoute x modulo 23 ; `FUN_00461b3b` renseigne le sous-type de taille du site à cet offset. Un item occupant un record masque le cercle `PAD.SHP` même si son SHP est indisponible. Les deux pistes d’animation POOL des IDs runtime 0 et 5 ainsi que leur mapping CHUG sont portés ; la cadence murale exacte reste approximative. Le remake reproduit désormais aussi le gel visuel ID 0 de `FUN_0040bf98` à partir du masque de visibilité `+0x22`, et `FUN_0046466f` initialise le bit des marqueurs de départ. Les événements de découverte ultérieurs qui actualisent ce masque restent à porter. Les effets secondaires/particules de `PROD` restent à porter ; voir le README du remake et `data_catalog.md`.

# Inconnues et limites

## À traiter

- Aucune fonction interne candidate ne reste en attente dans l’index pour le profil analysé. Le résultat couvre les 2 410 procédures observées par Ghidra, sans garantir que Ghidra ait reconnu toute région de code possible du binaire.
- Les 780 thunks sont indexées comme wrappers exclus du lot interne ; leur cible Ghidra est conservée lorsqu’elle est disponible.
- Les 123 fonctions externes sont indexées comme imports sans corps décompilable.
- Des helpers et bibliothèques du runtime peuvent subsister parmi les 1 493 procédures `internal`. Les 14 procédures classées `runtime` sont celles du chemin d’entrée C et de ses helpers directs identifiés à partir des appels/pseudocodes observés ; cette frontière est une classification analytique.

## Limites observées

- Aucun fichier `Float.pdb` n’est disponible pour cette analyse (information fournie par l’utilisateur). Une éventuelle référence au nom `Float.pdb` dans les informations de débogage PE n’établit pas que le fichier lui-même soit présent. Les noms d’origine et types source peuvent manquer.
- L’inventaire de chaînes couvre les objets de données définis par Ghidra ; les données non définies ou empaquetées peuvent ne pas apparaître.
- Les pseudocodes Ghidra sont des reconstructions non compilables et non équivalentes au source d’origine.
- La session Ghidra active est temporaire/éphémère. La fermer supprimerait son projet temporaire et son état d’annotation ; conserver la session pendant les travaux.
- Le consommateur de `shapeinf.txt` n’est pas encore localisé. Le fichier existe dans le corpus local et ses directives `shape`, `frame` et `offset` sont visibles, mais une recherche de chaîne Ghidra n’a pas établi son call-site.
- Le premier prototype du remake couvre le modèle de données et le chargement des mondes. SDL3 est choisi pour la couche plateforme, mais l’adaptateur n’est pas encore implémenté. Les gestionnaires des commandes d’écran `WORLDSIZE`, `DIFFICULTY` et `TRIBE0..3`, puis leur liaison à l’initialisation de partie, restent à tracer ; suivre `remake_spec.md`.

## Premières observations revalidées

- Ghidra nomme la fonction à `0x478460` `entry`. Son corps prépare le démarrage du processus, puis appelle `thunk_FUN_0041d8e1` à `0x402149`, dont la cible observée est `0x41d8e1`. Interprétation : démarrage runtime C probable.
- `0x41d8e1` journalise la chaîne de version `1.16F`, lit notamment `gamey.txt`, `newtext.txt`, `bldtxt.txt`, `bldname.txt`, `plotobj.txt`, `tonehelp.txt` et `names.txt`, puis appelle l’initialisation fenêtre et la boucle de traitement.
- `0x41c1d6` observe l’enregistrement de la classe `Float Class`, la création d’une fenêtre `Tonus Rebellious`, une requête de fréquence de performance, et un chemin conditionnel lié à `sound.txt` / `DXSOUND`.
- `0x41c46f` contient une boucle de traitement, des appels d’initialisation/affichage, et des chaînes telles que `data\\logo.gif`, `data\\logo.pal`, `windows.txt`, `effects.txt`, `fltinf.txt` et `bldinf.txt`. Les call-sites de ces trois derniers fichiers sont maintenant reliés à leurs parseurs dans `data_catalog.md`.
- Ces observations proviennent des pseudocodes et chaînes référencées dans les Evidence IDs du manifeste ; aucune exécution n’a été observée.

## Procédures sans pseudocode interne

- Les 780 thunks ont un corps de transfert, mais sont exclues du lot des corps internes; la cible Ghidra est conservée quand elle est résolue.
- Les 123 procédures externes sont des imports sans corps fourni par le binaire.
- Aucun résultat interne n’a été marqué `no_body` ou `decompile_failed` dans les 1 507 procédures internes/runtime traitées.

## Inconnues comportementales après la première cartographie

- Les formats du lecteur commun, de `float.cfg`, `names.txt`, des tags d’effets/formes et des tables de `worldpos.txt` sont partiellement établis dans `data_catalog.md`. Les COB et le corpus extrait sont disponibles localement et vérifiés par membre ; la sémantique de nombreux champs reste inconnue.
- Les chemins `effects.txt`, `fltinf.txt` et `bldinf.txt` sont reliés aux parseurs par les références d’instruction et appels Ghidra de `FUN_0041c46f` : respectivement `FUN_004153b8`, `FUN_00454d1f` et `FUN_00455833`. Cette liaison de flux ne résout pas encore la signification métier des champs numériques.
- `FUN_0041bdae` reçoit le callback de fenêtre via le stub `0x4020d6`; son pseudocode explicite seulement certains messages Windows. Les autres sont délégués à `DefWindowProcA` dans le pseudocode disponible.
- La file d’événements interne est limitée à huit enregistrements observés. Ses conventions sont lisibles pour certains messages Win32, mais les destinataires finaux des actions passent souvent par dispatch virtuel/indirect.
- `FUN_00466ce2` et d’autres helpers de boucle parcourent de grands états indexés et appellent des pointeurs de fonctions. Les identités métier des objets parcourus restent inconnues.
- `FUN_0042cc24` combine des appels de surface indirects et GDI `BitBlt`; l’identité exacte des interfaces de présentation n’est pas établie par les noms reconstruits seuls.
- Le chemin audio demeure à suivre au-delà des références `sound.txt` et `DXSOUND`.
- La liste priorisée des prochaines analyses figure dans `behavior_map.md`.

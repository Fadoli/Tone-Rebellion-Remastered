# Tone Rebellion — dossier de décompilation statique

## Cible et identité

- Fichier : `C:\Program Files\Tone\FLOAT.EXE`
- Binaire : exécutable Windows PE x86 32 bits, version installée 1.16F.
- Format / architecture : PE Windows, x86 32 bits
- Fournisseur actif : Ghidra 12.1.4 via REA (`rea-agents` 6.5.0)
- Ghidra : `C:\ghidra_12.1.4_PUBLIC`
- Java : `C:\Program Files\Java\jdk-24` (24.0.1)
- Mode : import temporaire Ghidra, cible source immuable ; aucun lancement de `FLOAT.EXE`.
- PDB : aucun fichier `Float.pdb` n’est disponible pour cette analyse (information fournie par l’utilisateur). Le nom peut apparaître dans les informations de débogage PE sans qu’un fichier PDB accompagne le binaire. Les noms automatiques et types reconstruits ne sont pas des noms/types source garantis.

## Corpus de données local

- Archives du jeu, à côté du binaire : `C:\Program Files\Tone\TONE00.COB` (156 212 octets) et `C:\Program Files\Tone\TONE01.COB` (26 927 860 octets).
- `C:\Program Files\Tone\COB.CFG` référence `tone00.cob` et `tone01.cob`.
- Les fichiers extraits sont disponibles dans `C:\git\ToneRebellion_Raw\original_content`. Les 483 entrées des archives sont indexées par nom, taille et chemin vers le membre correspondant du corpus local.
- Une copie décompressée équivalente de l’ISO est également présente dans `C:\toneIso` (notamment `C:\toneIso\THING2` pour les pistes audio). Pour poursuivre l’analyse des ressources livrées, préférer ce corpus local et les COB installés ; ne pas interroger GitHub.
- Voir [cob_archives.md](cob_archives.md) pour le format observé et les éléments Ghidra, et [archive_index.jsonl](archive_index.jsonl) pour le détail des membres.
- Pour la suite, utiliser ces chemins locaux. L’utilisateur a demandé d’éviter GitHub ; ne pas chercher ni télécharger le corpus sur GitHub.

## Méthode

L’analyse reste statique. On conserve le fournisseur, la version, le profil d’analyse et les Evidence IDs REA. L’inventaire complet des procédures distingue fonctions internes, thunks, fonctions externes et code de démarrage/runtime lorsque l’évidence le permet. Chaque fonction interne avec un corps analysable est décompilée par lots. Pour chaque procédure, l’index consigne l’adresse, le nom actuel, la classification, l’état, les appels directs, les chaînes référencées, une référence Evidence et les limites.

Les faits observés par Ghidra sont séparés des interprétations. Une absence de chaîne ou de symbole dans les inventaires Ghidra ne prouve pas son absence des octets du fichier. Les références d’évidence doivent permettre de retrouver les détails sans recopier de réponses tronquées.

## Résumé initial

L’analyse statique des 2 410 procédures de l’inventaire est terminée pour cette cible et ce profil Ghidra. Ghidra a décompilé 1 493 fonctions internes et 14 fonctions du chemin de démarrage/runtime C, soit les 1 507 fonctions internes candidates. Les 780 thunks et 123 externes sont indexées avec leurs motifs d’exclusion. `binary_overview` a relevé 2 209 chaînes Ghidra définies, une base d’image `0x400000` et sept segments. Les fonctions applicatives principales inspectées sont `0x41d8e1`, `0x41c1d6` et `0x41c46f`.

Les pistes `0x478460` (démarrage runtime), `0x41d8e1` (entrée application), `0x41c1d6` (initialisation fenêtre) et `0x41c46f` ont été revalidées dans les pseudocodes et chaînes Ghidra. Leur interprétation reste explicitement signalée comme telle dans `unknowns.md`.

## Fichiers

- `index.jsonl` : une ligne JSON par procédure, générée depuis l’inventaire Ghidra puis enrichie avec les résultats de décompilation.
- `functions/` : pages Markdown numérotées contenant le pseudocode Ghidra et les métadonnées des fonctions internes.
- `unknowns.md` : fonctions externes, thunks, fonctions sans corps, décompilations échouées, fonctions ignorées et limitations avec leurs raisons.
- `behavior_map.md` : première carte statique du démarrage, du gestionnaire de fenêtre, de la file d’événements, de la mise à jour et du rendu.
- `FUNCTION_GUIDE.md` : index fonctionnel par adresse pour les routines d’origine déjà reliées à un comportement observable (démarrage, boucle, menus, texte cintré, parseurs, carte et rendu), avec liens vers les pseudocodes Ghidra et séparation des faits/interprétations.
- `data_catalog.md` : formats de fichiers d’entrée reconstitués à partir des parseurs et chaînes Ghidra, avec degrés de certitude.
- `remake_spec.md` : premier modèle de données, frontière d’architecture et vertical slice proposé pour le remake.
- `ToneRebellion_Remake/` : début d’implémentation C11 du modèle de monde et du lecteur de `worldpos.txt`, compilé puis exécuté sur le fichier local `WORLDPOS.TXT`.
- `ToneRebellion_Remake/src/data/cob_archive.*` : lecteur en lecture seule de la table d’archives COB ; le lecteur de monde accepte maintenant directement le membre `data\\worldpos.txt` de `TONE01.COB`.
- `ToneRebellion_Remake/src/platform/win32/menu_app.c` : prototype de menu interactif Windows, construit et démarré depuis le remake, avec carte du monde, sélection taille/difficulté/tribus et contrôles souris/clavier ; la simulation de partie reste à porter.
- `cob_archives.md` et `archive_index.jsonl` : format/chargement des archives locales et inventaire avec comparaison des 483 membres extraits.
- `evidence/manifest.md` : Evidence IDs, paramètres du profil, couverture et pagination des demandes REA.
- `AGENTS.md` : consignes persistantes pour Codex et les agents de code qui poursuivront l’analyse.

## État d’avancement

Le dossier est initialisé, la cible validée et les 2 410 procédures figurent dans `index.jsonl`. État courant pour le profil Ghidra conservé : 1 507 pseudocodes obtenus (1 493 internes et 14 runtime), 780 thunks et 123 externes exclus avec motif explicite ; aucune fonction interne candidate n’est en attente ou déclarée non décompilable. L’audit documentaire retrouve les 1 507 sections pseudocode avec des blocs complets dans les pages paginées. Les thunks et imports sont indexés, mais ne sont pas des corps de fonctions internes à transcrire.

La cartographie fonctionnelle relie maintenant les principaux rôles aux adresses des fonctions d’origine, avec les dossiers de pseudocode comme preuves. Voir `FUNCTION_GUIDE.md` pour l’index par fonction, et `behavior_map.md` pour le chemin d’exécution et les Evidence IDs.

Pour le démarrage du monde, ces documents décrivent maintenant le rôle des fonctions d'origine par étape : `FUN_004637fc` construit l'état global d'une nouvelle partie, `FUN_00461b3b` parse et classe les emplacements (`tone` → classe 1), `FUN_00461859` initialise les états d'île et associe les ponts aux emplacements de classe 2, `FUN_0046466f` choisit le marqueur/site et les créations initiales, puis `FUN_00464b9e` choisit les marqueurs et items de realm 6–9. `FUN_004535e4`, `FUN_00452859` et `FUN_004528ca` couvrent le choix d'item, sa validation et son écriture. Les fonctions `FUN_00461768` et `FUN_00461831` sont les comparateurs passés au tri des ponts/emplacements. Voir [FUNCTION_GUIDE.md](FUNCTION_GUIDE.md) et [world_start_distribution.md](world_start_distribution.md); constats et interprétations y sont séparés.

Le cœur portable contient aussi le RNG partagé observé dans `FUN_00474b90`/`FUN_00467260` : le LCG 32 bits puis sa sortie 15 bits, avec la mise à l'échelle bornée du binaire. `game_session.c` assemble maintenant une première structure d'état mutable : reset des records (`FUN_004500c4`), starts/pads/floaters (`FUN_0046466f`), items de marqueur (`FUN_00464b9e`), états de classe 2 et affectations de classe 0 (`FUN_004637fc`). Le test du corpus initialise le petit monde à partir des vrais `WORLDPOS.TXT` et `ISLANDnn.TXT`. La session n'est pas encore reliée à l'interface Win32. Voir `ToneRebellion_Remake/src/core/game_session.c`, `world_start_distribution.md` et les tests.

Une première analyse des parseurs confirme la grammaire du lecteur de textes à clés (`END` par entrée, `ENDTEXT` par fichier), la structure clé/valeur de `float.cfg`, la lecture séquentielle de `names.txt`, plusieurs familles de tags pour les effets/formes et des tables monde dans `worldpos.txt`. Les données sont maintenant disponibles dans le corpus local et leur présence dans les COB est vérifiée ; voir `data_catalog.md` et `cob_archives.md`.

Les références d’instruction de l’initialisation relient maintenant `effects.txt` au parseur `FUN_004153b8`, `fltinf.txt` à `FUN_00454d1f` et `bldinf.txt` à `FUN_00455833`. La suite consiste à suivre les champs de ces parseurs dans leurs consommateurs et à comparer les structures reconstruites aux fichiers locaux, sans présenter les interprétations comme des faits source.

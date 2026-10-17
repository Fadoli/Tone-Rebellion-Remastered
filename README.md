# Tone Rebellion — dossier de décompilation statique

## Cible et identité

- Fichier : `C:\Program Files\Tone\FLOAT.EXE`
- SHA-256 attendu et observé : `bb229d7f09c88caf4dc1825c00b957961c22c201cf1a8dd8139bf6f4599ff28c`
- Format / architecture : PE Windows, x86 32 bits
- Fournisseur actif : Ghidra 12.1.4 via REA (`rea-agents` 6.5.0)
- Ghidra : `C:\ghidra_12.1.4_PUBLIC`
- Java : `C:\Program Files\Java\jdk-24` (24.0.1)
- Mode : import temporaire Ghidra, cible source immuable ; aucun lancement de `FLOAT.EXE`.
- PDB : aucun fichier `Float.pdb` n’est disponible pour cette analyse (information fournie par l’utilisateur). Le nom peut apparaître dans les informations de débogage PE sans qu’un fichier PDB accompagne le binaire. Les noms automatiques et types reconstruits ne sont pas des noms/types source garantis.

## Corpus de données local

- Archives du jeu, à côté du binaire : `C:\Program Files\Tone\TONE00.COB` (156 212 octets, SHA-256 `362257b33c4d6b6e3c95208f6e45a1734aeadc2d21898a7f1055476c521bae5b`) et `C:\Program Files\Tone\TONE01.COB` (26 927 860 octets, SHA-256 `ba15e43c3d5b9156594a6fab166c76749c5953dfecc39ffaa568271f7100a64f`).
- `C:\Program Files\Tone\COB.CFG` référence `tone00.cob` et `tone01.cob`.
- Les fichiers extraits sont disponibles dans `C:\git\ToneRebellion_Raw\original_content`. Les 483 membres des archives correspondent tous par nom, taille et SHA-256 aux fichiers du corpus local.
- Voir [cob_archives.md](cob_archives.md) pour le format observé et les éléments Ghidra, et [archive_index.jsonl](archive_index.jsonl) pour le détail des membres.
- Pour la suite, utiliser ces chemins locaux. L’utilisateur a demandé d’éviter GitHub ; ne pas chercher ni télécharger le corpus sur GitHub.

## Méthode

L’analyse reste statique. On conserve l’identité SHA-256, le fournisseur, la version, le profil d’analyse et les Evidence IDs REA. L’inventaire complet des procédures distingue fonctions internes, thunks, fonctions externes et code de démarrage/runtime lorsque l’évidence le permet. Chaque fonction interne avec un corps analysable est décompilée par lots. Pour chaque procédure, l’index consigne l’adresse, le nom actuel, la classification, l’état, les appels directs, les chaînes référencées, une référence Evidence et les limites.

Les faits observés par Ghidra sont séparés des interprétations. Une absence de chaîne ou de symbole dans les inventaires Ghidra ne prouve pas son absence des octets du fichier. Les références d’évidence doivent permettre de retrouver les détails sans recopier de réponses tronquées.

## Résumé initial

L’analyse statique des 2 410 procédures de l’inventaire est terminée pour cette cible et ce profil Ghidra. Ghidra a décompilé 1 493 fonctions internes et 14 fonctions du chemin de démarrage/runtime C, soit les 1 507 fonctions internes candidates. Les 780 thunks et 123 externes sont indexées avec leurs motifs d’exclusion. `binary_overview` a relevé 2 209 chaînes Ghidra définies, une base d’image `0x400000` et sept segments. Les fonctions applicatives principales inspectées sont `0x41d8e1`, `0x41c1d6` et `0x41c46f`.

Les pistes `0x478460` (démarrage runtime), `0x41d8e1` (entrée application), `0x41c1d6` (initialisation fenêtre) et `0x41c46f` ont été revalidées dans les pseudocodes et chaînes Ghidra. Leur interprétation reste explicitement signalée comme telle dans `unknowns.md`.

## Fichiers

- `index.jsonl` : une ligne JSON par procédure, générée depuis l’inventaire Ghidra puis enrichie avec les résultats de décompilation.
- `functions/` : pages Markdown numérotées contenant le pseudocode Ghidra et les métadonnées des fonctions internes.
- `unknowns.md` : fonctions externes, thunks, fonctions sans corps, décompilations échouées, fonctions ignorées et limitations avec leurs raisons.
- `behavior_map.md` : première carte statique du démarrage, du gestionnaire de fenêtre, de la file d’événements, de la mise à jour et du rendu.
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

La première cartographie de comportement relie maintenant l’entrée applicative, la création de fenêtre, l’initialisation des ressources/fenêtres, la file d’événements Win32, la boucle de mise à jour et la présentation graphique. Voir `behavior_map.md` pour les Evidence IDs et les prochaines pistes.

Une première analyse des parseurs confirme la grammaire du lecteur de textes à clés (`END` par entrée, `ENDTEXT` par fichier), la structure clé/valeur de `float.cfg`, la lecture séquentielle de `names.txt`, plusieurs familles de tags pour les effets/formes et des tables monde dans `worldpos.txt`. Les données sont maintenant disponibles dans le corpus local et leur présence dans les COB est vérifiée ; voir `data_catalog.md` et `cob_archives.md`.

Les références d’instruction de l’initialisation relient maintenant `effects.txt` au parseur `FUN_004153b8`, `fltinf.txt` à `FUN_00454d1f` et `bldinf.txt` à `FUN_00455833`. La suite consiste à suivre les champs de ces parseurs dans leurs consommateurs et à comparer les structures reconstruites aux fichiers locaux, sans présenter les interprétations comme des faits source.

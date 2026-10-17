# Consignes pour les agents de code

## Mission

Contribuer à la décompilation statique de `C:\Program Files\Tone\FLOAT.EXE` en suivant le README et l’index de ce dossier. Le binaire original et les archives `TONE00.COB` / `TONE01.COB` sont en lecture seule : ne jamais les exécuter, renommer, modifier ou écrire à côté. Le corpus extrait est disponible dans `C:\git\ToneRebellion_Raw\original_content`, et une copie locale décompressée équivalente de l'ISO se trouve dans `C:\toneIso` (les pistes musicales sont sous `C:\toneIso\THING2`). Utiliser ces sources locales et éviter GitHub ou tout accès réseau pour rechercher le contenu. Ne jamais ouvrir, modifier, écraser ou supprimer un projet Ghidra existant. Réutiliser la session REA/Ghidra active et son analyse stable ; ne pas relancer une analyse identique.

## Preuve et prudence

- Éviter les métadonnées de vérification d’octets dans les fichiers générés.
- Aucun fichier compagnon `Float.pdb` n’est disponible pour cette analyse. Une référence à ce nom dans les métadonnées PE ne signifie pas qu’un PDB est présent ; ne pas présenter l’état Ghidra « inconnu » comme preuve d’un fichier disponible.
- Utiliser les outils REA/Ghidra disponibles, la pagination et les Evidence IDs. Ne pas traiter une sortie tronquée comme complète ; demander une vue/page plus petite ou lire l’évidence conservée.
- Distinguer observation Ghidra, interprétation et inconnue. Le pseudocode est généré par décompilateur, pas le code source d’origine. Les identifiants `FUN_...`, signatures, types et noms de variables sont reconstruits ou automatiques sauf preuve contraire.
- Une chaîne est une chaîne définie par Ghidra ; une absence de résultat n’établit pas l’absence d’octets correspondants.
- Ne pas exécuter le programme ni invoquer de débogueur, d’instrumentation ou d’observation runtime. L’objectif est uniquement statique.

## Analyse REA et documentation

- Pour toute nouvelle analyse REA, déléguer la lecture ciblée des preuves à un sous-agent `gpt-6-luna`, effort `medium`. Lui demander un résultat bref avec Evidence IDs, faits directs et inconnues; garder la coordination et les échanges au minimum. Ne pas déléguer les modifications du remake sans besoin explicite.
- Garder la documentation concise : ne répéter ni pseudocode ni faits déjà consignés. Ajouter les observations, Evidence IDs, interprétations et limites nécessaires à la décision; mettre le détail de fonction dans `functions/` et résumer les ports dans le guide et le TODO.

## Inventaire et décompilation

- Conserver une entrée `index.jsonl` par procédure, avec adresse, nom actuel, classification (`internal`, `thunk`, `external`, `runtime` ou `unknown`), état, appels directs, chaînes référencées, Evidence ID(s), limites et motif si non décompilée.
- Distinguer le code runtime de démarrage du code applicatif avec des indices documentés ; ne pas classer uniquement par adresse ou nom.
- Décompiler les fonctions internes ayant un corps analysable par lots reproductibles. Suivre les comptes d’inventaire, éligibles, terminées, échouées et restantes dans `evidence/manifest.md`.
- Mettre les pseudocodes dans des fichiers Markdown paginés sous `functions/`, avec une plage d’adresses stable et une ligne/titre par fonction. Garder pour chaque fonction nom/adresse, appels directs, chaînes, Evidence ID et limitations.
- Toute fonction externe, thunk, sans corps, indéterminée, non décompilable ou ignorée doit rester dans l’index avec une raison dans `unknowns.md`.
- Mettre à jour les fichiers de façon cohérente : pas de compte « terminé » avant vérification de l’index complet et de chaque page.
- Pour l’analyse de comportement, compléter `behavior_map.md` avec les liens de flux d’appels et séparer les observations Ghidra des interprétations.
- Pour les données externes, compléter `data_catalog.md` seulement à partir de routines de lecture/chaînes observées ; signaler comme hypothèse toute association fichier→parseur qui n’est pas confirmée par les arguments ou références au call-site.
- Pour les membres des COB, consulter `cob_archives.md` et `archive_index.jsonl`. L’index consigne nom, offset, longueur et chemin local pour les 483 membres.

## Conventions de performance et de changements

- Préférer les opérations intégrées comme `node:test` et `assert` lorsqu’un besoin de test existe. Ne pas ajouter ni lancer des tests sans demande explicite.
- Pour du code de traitement volumineux, limiter les allocations temporaires, préférer une `Map` aux recherches répétées par `[].find()`, et éviter `Object.keys()`/`Object.values()` ; parcourir avec `for...in` lorsque cela convient.
- Si une tâche porte sur la performance, documenter les constats et benchmarks dans un sous-dossier `bench/` avec les fichiers `.md` et `.js`, y compris les pistes essayées puis écartées parce qu’elles régressaient.
- Ne pas introduire de scripts ou dépendances nécessaires à l’exécution de la cible. Les scripts de génération du dossier, s’ils deviennent nécessaires, ne doivent lire que les données Evidence et écrire dans ce dossier.

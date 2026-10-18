# Tone Rebellion — dossier de décompilation statique

## Cible et méthode

Analyse statique de `C:\Program Files\Tone\FLOAT.EXE` (PE x86, version 1.16F), avec Ghidra 12.1.4 via REA. Le binaire, les COB et les projets Ghidra sont des références immuables; le jeu original n’est jamais exécuté.

Les faits observés, interprétations et inconnues restent séparés. Les noms et types reconstruits par Ghidra sont provisoires. La méthode et les consignes de reprise sont dans [AGENTS.md](AGENTS.md).

## Données locales

Le corpus extrait est sous `C:\git\ToneRebellion_Raw\original_content`; l’ISO décompressée est sous `C:\toneIso`. Les 483 membres COB sont indexés dans [archive_index.jsonl](archive_index.jsonl). Ne pas rechercher ou télécharger le corpus en ligne.

## Couverture

L’inventaire comprend 2 410 procédures : 1 507 corps décompilés, 780 thunks et 123 externes. Détails et limites : [evidence/manifest.md](evidence/manifest.md), [unknowns.md](unknowns.md).

## Navigation

- [FUNCTION_GUIDE.md](FUNCTION_GUIDE.md) — index des fonctions avec liens vers leurs preuves détaillées.
- [behavior_map.md](behavior_map.md) et [behavior/](behavior/) — flux et comportements par domaine.
- [functions/](functions/) — pseudocode et métadonnées Ghidra.
- [data_catalog.md](data_catalog.md), [cob_archives.md](cob_archives.md) — formats et ressources.
- [ToneRebellion_Remake/README.md](ToneRebellion_Remake/README.md) — état du remake, compilation et tests.
- [ToneRebellion_Remake/TODO.md](ToneRebellion_Remake/TODO.md) — prochaines tâches du remake.

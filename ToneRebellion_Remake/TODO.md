# Gameplay todo

Porter uniquement les comportements établis par le binaire et les données locales. Preuves et détails : `../behavior/`, [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md); état d'ensemble : [feuille de route](ROADMAP.md); portage acquis : [implemented.md](docs/implemented.md).

## Domaines

- [Interface](TODO_INTERFACE.md)
- [Mouvement](TODO_MOVEMENT.md)
- [Tâches et interactions](TODO_TASKS.md)
- [Autres systèmes](TODO_OTHER.md)
- [Portage Web (WASM)](TODO_WEB.md)

Les entrées faites ne gardent qu'un titre et le lien vers leur revue; le détail est dans la revue ou l'historique git.

## Limites connues

- Tâches : branche IA des ouvriers en danger (`DAT_005eebd4`, états 6/7), second appelant de `FUN_004239e9` (état 0x13, sous-cas 0x14) et types de tâche 6, 0x11 et 0xd de la liste « urgente » non portés.
- Textes : genre 3 `FEAT%02d` (clés absentes des données, table `DAT_005eebf8` non modélisée), textes de gisement `POOLINFECT`/`SUPPLY_%d` non portés; texte enveloppé d'`IWTextInfo` posé à y = 0x10 (natif (10, 6)); fond `DAT_004c2b08` non porté.
- Badges : 0x1e (Léviathan) jamais affiché, `DAT_0061fa2e` sans écrivain connu; préfixe `x` et badges des monstres non établis.
- Mouvement : préférence de classe 1 nulle comme dans l'image chargée (aucun écrivain trouvé); état runtime 10 (compteur `+0x34`) sans producteur connu, le port n'y entre jamais.
- Interface : nettoyage de site approximatif; fusion Maj+clic droit = raccourci du remake; mode HallStk et noms des genres 0x2c hors périmètre.
- Réseau : pose directe `FUN_00465793` (catégorie 3, sous-type 4) seulement par le relais `FUN_00412eac`, non portée.
- Inconnus REA : appelants de `FUN_0045d867`/`FUN_0045d8b2`/`FUN_0045ccce`/`FUN_0045dcf4`, corps de `FUN_004207f2`/`FUN_004509da`/`FUN_0042383d`, classe d'`IWLocInfo`, récepteur du message 0x47 de survol.

# Gameplay todo

Tout comportement doit être retrouvé dans le binaire d'origine avant son implémentation. Consigner la fonction et l'évidence Ghidra/REA; distinguer observations, interprétations et inconnues. Ne pas inventer de règles ou d'interactions. FLOAT.EXE et le projet Ghidra restent en lecture seule.

## À faire

- [ ] **Sélection et panneaux UI :** la sélection d'un ouvrier sert à consulter ses statistiques, sans lui donner d'ordre. Confirmer dans le code les classes de soldats/mages qui acceptent des ordres; reconstruire les panneaux d'unités, bâtiments et la barre du bas depuis leurs handlers et données d'origine.
- [ ] **Construction différée :** un choix dans l'UI doit créer l'ordre source, pas poser immédiatement le bâtiment. Retracer sa file, l'unité ouvrière éligible, les coûts/ressources, le déplacement, l'arrivée et la création au site avant de porter le cycle complet.
- [ ] **Ouvriers autonomes et économie :** reconstruire les tâches et destinations choisies par le jeu pour les ouvriers sans tâche, ainsi que le stockage au Grand Hall, collecte, livraison, stocks, coûts et activation des producteurs. Pas de promenade ou d'économie simulée au hasard.
- [ ] **Commandes et barre inférieure :** identifier chaque zone et son handler d'origine; rendre interactives uniquement les actions attestées par un message et un effet source.
- [ ] **Audio de jeu :** rattacher chaque effet sonore aux événements et fonctions qui le déclenchent dans le jeu.

## Réalisé

- [x] Accès à la carte du monde et surbrillance des îles selon le masque de session observé.
- [x] Sons de menu, son de démarrage et sélection de musique de royaume.
- [x] Groupes initiaux d'ouvriers des quatre tribus et rattachement au Grand Hall.
- [x] Primitives de déplacement, registre interne de ressources et sorties de producteurs portés sans revendiquer la parité de gameplay.
- [x] Commandes prototypes directes d'ouvriers retirées; le panneau des ouvriers initiaux lit leurs PV/force depuis leur état (`WORKER`, `HITS 3/3`, `STRENGTH 0`). XP n'est pas ajouté car le panneau source ne l'affiche pas.
- [x] Niveau de bâtiment sélectionné porté depuis le nibble `+0x0a` décodé par `FUN_0041ff2e` et affiché par `FUN_0044338b`.
- [x] Début du traçage du clic de construction: `FUN_0043acea` envoie `0x34` puis `0x33`; la file de catégorie 1 aboutit à `FUN_00465793` et réserve un enregistrement différé via `FUN_004662b7`.
- [x] Build et 14 tests CTest existants vérifiés; l'exécutable livré a été reconstruit depuis le build.

## Références de suivi

- [MOVEMENT_REVERSE_ENGINEERING.md](MOVEMENT_REVERSE_ENGINEERING.md) — sélection, déplacement et cycle autonome des ouvriers.
- [../FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md) — fonctions d'origine, flux et références d'évidence.
- [README.md](README.md) — état du prototype et vérifications disponibles.

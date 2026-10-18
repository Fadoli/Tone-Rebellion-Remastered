# Fonctionnalités déjà portées

Résumé compact de l'implémentation actuelle. Les détails et limites par domaine se trouvent dans les notes liées depuis [FUNCTION_GUIDE.md](../../FUNCTION_GUIDE.md). La présence d'un rendu ne prouve pas la parité gameplay.

- **Démarrage et monde :** lecture du monde, création des îles, Halls, quatre groupes initiaux d'ouvriers et distribution initiale des tons.
- **Interface de l'île :** barre d'île et commandes Hall; panneau d'informations, inventaire, glyphes, diplomatie, commerce, tâches, constructions et roster initial.
- **Interactions :** survol/sélection Inventory, activation d'un glyphe possédé, commandes de priorité/annulation Tasks, requête `BC_OnOff` (sans effet bit modélisé), demande de construction différée, réserve Hall, diplomatie et transferts commerce locaux.
- **Simulation portée :** stocks Hall initiaux, `POPSTR`, cycle `PROD` des IDs 0x25–0x27, overlays `TOGREALM` et bit brut émis par `PANIC`.
- **Rendu :** carte/îles, objets de construction, couches/features, stocks Hall (`POPSTR`/`WORKSTR` depuis les floaters modélisés), badges initiaux, fenêtres Tasks et icônes de diplomatie pour les unités initiales.
- **Audio :** sons de menu et choix de musique du royaume.

Limites principales : consommateurs/transport de plusieurs requêtes, acquisition d'objets, producteurs de tâches `CONSTR`, simulation `REPAIR`, déplacement de floatteurs et champs runtime des badges restent ouverts dans [TODO](../TODO.md).

# Fonctionnalités déjà portées

Résumé compact de l'implémentation actuelle. Les détails et limites par domaine se trouvent dans les notes liées depuis [FUNCTION_GUIDE.md](../../FUNCTION_GUIDE.md). La présence d'un rendu ne prouve pas la parité gameplay.

- **Démarrage et monde :** lecture du monde, création des îles, Halls, quatre groupes initiaux d'ouvriers et distribution initiale des tons.
- **Interface de l'île :** barre d'île et commandes Hall; panneau d'informations, inventaire, glyphes, diplomatie, commerce, tâches, constructions et roster initial.
- **Interactions :** survol/sélection Inventory, activation d'un glyphe possédé, commandes de priorité/annulation Tasks, bascule `BC_OnOff` (`0x400`, garde du budget d'entretien et libération des slots 1–3 à l'arrêt), demande de construction différée, réserve Hall, diplomatie et transferts commerce locaux. `IWLocInfo` expose maintenant un contrôle grab/place : une structure du joueur peut être saisie, puis posée sur un site libre visible ou un `PIT_Object` admissible; le coût de déplacement est débité au départ et remboursé à l'annulation.
- **Simulation portée :** stocks Hall initiaux, `POPSTR`, cycle `PROD` des IDs 0x25–0x27, cycle `REPAIR` (livraison de Build Tone, soin après 40 ticks, réapprovisionnement après un soin partiel et débit des deux stocks), démarrage CONS/PROD d'un pont via livraison de code 5 et accès à l'île voisine pour la faction qui l'a lancé, overlays `TOGREALM` et bit brut émis par `PANIC`.
- **Rendu :** carte/îles, objets de construction, couches/features, stocks Hall (`POPSTR`/`WORKSTR` depuis les floaters modélisés), badges initiaux, fenêtres Tasks et icônes de diplomatie pour les unités initiales.
- **Audio :** sons de menu et choix de musique du royaume.

Limites principales : le grab/place applique une approximation de déplacement; les nettoyages indirects des sous-types 5/6 ne sont pas tous reconstruits. Le ramassage d'un `PIT_Object` vers Inventory reste inconnu. Les consommateurs/transport de plusieurs requêtes, producteurs de tâches `CONSTR`, transition native vers `REPAIR`, déplacement de floatteurs et champs runtime des badges restent ouverts dans [TODO](../TODO.md).

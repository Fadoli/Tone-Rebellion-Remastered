# Gameplay todo

Porter uniquement les comportements établis par le binaire et les données locales. Les preuves, détails de fonctions et limites sont dans [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md).

## À faire

- [ ] Tracer le clic sur `IWMove`/`IWHallMove` : gestionnaire, gardes, coûts et événement de validation.
- [ ] Identifier le callback et la garde de classe des ordres directs avant d'exposer les commandes soldat/mage.
- [ ] Finir les panneaux d'unités/bâtiments : mapper les champs de `CHARGE` et tracer chaque action avant d'ajouter des boutons. Le roster actuel ne couvre que les quatre ouvriers initiaux.
- [ ] Relier la sélection initiale au Hall, mapper le badge charge/état et identifier les consommateurs de l'état `PANIC`.
- [ ] Relier les événements d'acquisition aux compteurs d'inventaire et au masque de glyphes; compléter le retour à la ligne et la bannière Diplomatie.
- [ ] Remplacer le placement immédiat par la construction différée source : coûts, sélection d'unité, ordre, trajet et achèvement.
- [ ] Reconstituer le cycle des tâches, collecte, livraison, stocks et état idle des ouvriers.
- [ ] Ajouter des tests source-backed pour les gardes refusées, commandes, construction différée et interactions de panneaux.
- [ ] Relier les effets sonores aux événements qui les déclenchent.
- [ ] Vérifier visuellement l'ordre de superposition et les hit-tests des panneaux Hall.

## Réalisé

- [x] Carte du monde, îles et quatre groupes initiaux d'ouvriers rattachés aux Halls.
- [x] Rendu initial de l'île, objets, construction, inventaire, glyphes, diplomatie et commerce.
- [x] Roster des quatre ouvriers initiaux : ancres et hit-test `IWLocInfo` testés; le clic conserve le Hall sélectionné.
- [x] Commandes de barre d'île, badges santé/royaume et descriptions de survol actuellement portées.
- [x] Sons de menu et sélection de musique du royaume.
- [x] Build du 18/10/2026 : CTest 19/19; `windows.txt` 100 descripteurs; corpus 15 îles/871 lignes; COB 210 feuilles/4821 frames. SHA-256 build/exécutable : `C16D21934D7CD2980D986758F1AF446A23304B887E1B6FE1B1DB45F60965AC2F`.

## Références

- [MOVEMENT_REVERSE_ENGINEERING.md](MOVEMENT_REVERSE_ENGINEERING.md) — sélection, mouvement et tâches autonomes.
- [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md) — observations, Evidence IDs et inconnues.
- [README.md](README.md) — état du prototype et commandes de vérification.

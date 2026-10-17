# Gameplay todo

Porter uniquement les comportements établis par le binaire et les données locales. Les preuves, détails de fonctions et limites sont dans [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md).

## À faire

- [ ] Relier le clic type 34 sur `IWMove`/`IWHallMove` à l'état UI qui produit `0x4c`; établir gardes, coût et validation avant de porter l'ordre.
- [ ] Identifier le callback et la garde de classe des ordres directs avant d'exposer les commandes soldat/mage.
- [ ] Finir les panneaux d'unités/bâtiments : mapper les champs de `CHARGE` et tracer chaque action avant d'ajouter des boutons. Le roster actuel ne couvre que les quatre ouvriers initiaux.
- [ ] Établir l'état initial et les consommateurs visuels de `TOGREALM`; relier la sélection initiale au Hall, mapper le badge charge/état et identifier les consommateurs de `PANIC`.
- [ ] Tracer l'initialisation/écriture de `DAT_006191f8` et la formule de `% WORKSTR` avant d'afficher surplus et ouvriers.
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
- [x] Compteurs des trois stocks du Hall dessinés aux ancres `IWLocInfo` observées; soldes initiaux non établis.
- [x] `POPSTR` compte les floaters actifs modélisés du joueur; ce sont les quatre unités initiales.
- [x] Commandes de barre d'île, badges santé/royaume et descriptions de survol actuellement portées.
- [x] Sons de menu et sélection de musique du royaume.
- [x] Build du 18/10/2026 : CTest 19/19; `windows.txt` 100 descripteurs; corpus 15 îles/871 lignes; COB 210 feuilles/4821 frames. Exécutable livré : 266731 octets, SHA-256 `33BB841717395EB03151992B1F4954AAC0C0BCBF6CA9BD6154DAA4E6BCE686CC`.

## Références

- [MOVEMENT_REVERSE_ENGINEERING.md](MOVEMENT_REVERSE_ENGINEERING.md) — sélection, mouvement et tâches autonomes.
- [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md) — observations, Evidence IDs et inconnues.
- [README.md](README.md) — état du prototype et commandes de vérification.

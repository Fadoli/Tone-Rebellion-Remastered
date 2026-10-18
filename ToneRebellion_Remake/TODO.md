# Gameplay todo

Porter uniquement les comportements établis par le binaire et les données locales. Les preuves, détails de fonctions et limites sont dans [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md).

## À faire

- [ ] Tracer le consommateur de l'ordre 9 issu du type 34, son événement 7 et les montants de coût absents de `DAT_005eac08`; `0x4c` est un chemin distinct.
- [ ] Identifier le callback et la garde de classe des ordres directs avant d'exposer les commandes soldat/mage.
- [ ] Finir les panneaux d'unités/bâtiments : mapper les champs de `CHARGE` et tracer chaque action avant d'ajouter des boutons. Le roster actuel ne couvre que les quatre ouvriers initiaux.
- [ ] Compléter les badges état/charge de `TOGREALM` et identifier les consommateurs de `PANIC`. Royaume et santé sont rendus pour les quatre ouvriers initiaux.
- [ ] Tracer l'initialisation/écriture de `DAT_006191f8` et la formule de `% WORKSTR` avant d'afficher surplus et ouvriers.
- [ ] Relier les tâches aux compteurs Inventory; établir le producteur des deux bits Hall qui déclenchent l'acquisition Glyphes avant de porter ce chemin.
- [ ] Remplacer le placement immédiat par la construction différée source : coûts, sélection d'unité, ordre, trajet et achèvement.
- [ ] Tracer l’activation du bit Hall `+0x1c & 1` avant les demandes de réserve mode 2; relier le type 4 à l’affectation, collecte, livraison et au cycle idle.
- [ ] Ajouter des tests source-backed pour les gardes refusées, commandes, construction différée et interactions de panneaux.
- [ ] Relier les effets sonores aux événements qui les déclenchent.
- [ ] Vérifier visuellement l'ordre de superposition et les hit-tests des panneaux Hall.

## Réalisé

- [x] Carte du monde, îles et quatre groupes initiaux d'ouvriers rattachés aux Halls.
- [x] Rendu initial de l'île, objets, construction, inventaire, glyphes, diplomatie et commerce.
- [x] Roster des quatre ouvriers initiaux : ancres et hit-test `IWLocInfo` testés; le clic conserve le Hall sélectionné.
- [x] Stocks initiaux du Hall (50/0/0), dessin des trois compteurs aux ancres `IWLocInfo` observées.
- [x] `POPSTR` compte les floaters actifs modélisés du joueur; ce sont les quatre unités initiales.
- [x] Commandes de barre d'île, badges santé/royaume et descriptions de survol actuellement portées.
- [x] Sons de menu et sélection de musique du royaume.
- [x] Icônes des quatre joueurs dans la bannière Diplomatie à partir des ouvriers initiaux et des ancres source; animation et autres états en attente.
- [x] Panneaux Tasks / effets : paires `SCROLL.SHP` rattachées à `IWTasks` (mode 2) et `IWEffList` (mode 8 debug) selon le dispatch source; défilement et données des tâches restent à porter.
- [x] `TOGREALM` inverse ses trois flags; royaume (`FLTINFO` 22–25) et santé (`0x15−maxHP`) sont rendus pour les ouvriers initiaux. Les autres badges attendent leurs champs runtime.
- [x] Build du 18/10/2026 : CTest 19/19 et mise en page des 8 paragraphes depuis les COB; exécutable 270291 octets, SHA-256 `7C3657D2FEC9B7CF73686F117A2A26FCAC3B4C6D2E8A5F221E9C3D2239FAA3A5`.

## Références

- [MOVEMENT_REVERSE_ENGINEERING.md](MOVEMENT_REVERSE_ENGINEERING.md) — sélection, mouvement et tâches autonomes.
- [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md) — observations, Evidence IDs et inconnues.
- [README.md](README.md) — état du prototype et commandes de vérification.

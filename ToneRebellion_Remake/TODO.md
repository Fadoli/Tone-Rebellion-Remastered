# Gameplay todo

Porter uniquement les comportements établis par le binaire et les données locales. Les preuves, détails de fonctions et limites sont dans [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md).

## À faire

- [ ] Tracer le consommateur de l'ordre 9 issu du type 34, son événement 7 et les montants de coût absents de `DAT_005eac08`; `0x4c` est un chemin distinct.
- [ ] Identifier le callback et la garde de classe des ordres directs avant d'exposer les commandes soldat/mage.
- [ ] Finir les panneaux d'unités/bâtiments : l'écriture de `+0x22` est établie pour les floaters, mais pas les clés stats du Hall/site; tracer chaque action avant d'ajouter des boutons. Le roster actuel ne couvre que les quatre ouvriers initiaux.
- [ ] Mapper les champs runtime nécessaires aux badges état/charge; établir le sens visuel ou gameplay du mot d'île basculé par `PANIC`. L'événement et son écriture XOR sont identifiés, mais pas l'effet du mot.
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
- [x] Panneaux Tasks / effets : paires `SCROLL.SHP` et survol `MOUSEFOCUS` portés pour `IWTasks`/`IWEffList`; données des tâches restent à porter. `InvCycle` utilise aussi son frame de survol.
- [x] Inventory : la fiche `IWTextInfo` suit l'ID sélectionné après la fin du survol; couvert par `test_island_panel_info`.
- [x] `TOGREALM` inverse ses trois flags; royaume (`FLTINFO` 22–25) et santé (`0x15−maxHP`) sont rendus pour les ouvriers initiaux. Les autres badges attendent leurs champs runtime.
- [x] `PANIC` émet l'événement local type 3/sous-type 0 et le dispatch bascule le bit 0 du mot d'île par joueur; la sémantique reste inconnue.
- [x] Texte New Game : 13 rangées source, largeur 12/13 et interligne 1 px; les huit paragraphes COB passent les bornes et dégagent emblèmes/pied de page.
- [x] Build du 18/10/2026 : CTest 19/19; exécutable 271467 octets, SHA-256 `F97102FA18FC278EAEE24A0AA59D05488AB42F549C5ADB3C7683BC832EBE9903`.

## Références

- [MOVEMENT_REVERSE_ENGINEERING.md](MOVEMENT_REVERSE_ENGINEERING.md) — sélection, mouvement et tâches autonomes.
- [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md) — observations, Evidence IDs et inconnues.
- [README.md](README.md) — état du prototype et commandes de vérification.

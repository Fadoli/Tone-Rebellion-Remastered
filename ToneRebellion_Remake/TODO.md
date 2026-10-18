# Gameplay todo

Porter uniquement les comportements établis par le binaire et les données locales. Les preuves, détails de fonctions et limites sont dans [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md).

## À faire

- [ ] Tracer le consommateur de l'ordre 9 issu du type 34, son événement 7 et les montants de coût absents de `DAT_005eac08`; `0x4c` est un chemin distinct.
- [ ] Identifier l’initialisation/producteur des records Tasks `DAT_006183bc` (pas 0x14); le filtre/panneau est connu, mais ni l’état initial ni le flux complet ne le sont.
- [ ] Identifier le callback et la garde de classe des ordres directs avant d'exposer les commandes soldat/mage.
- [ ] Finir les panneaux d'unités/bâtiments : l'écriture de `+0x22` est établie pour les floaters, mais pas les clés stats du Hall/site; tracer chaque action avant d'ajouter des boutons. Le roster actuel ne couvre que les quatre ouvriers initiaux.
- [ ] Mapper les champs runtime nécessaires aux badges état/charge; établir le sens visuel ou gameplay du mot d'île basculé par `PANIC`. L'événement et son écriture XOR sont identifiés, mais pas l'effet du mot.
- [ ] Tracer l'initialisation/écriture de `DAT_006191f8` et la formule de `% WORKSTR` avant d'afficher surplus et ouvriers.
- [ ] Relier les tâches aux compteurs Inventory; retrouver le contexte exact des appels à `FUN_004503bd` qui alimentent les deux bits de progression et attribuent un glyphe. Les call-sites existent, mais ne prouvent pas une arrivée au Hall.
- [ ] Finir le clic carte après sélection d'un glyphe : son paquet type 3 est observé, mais les gardes de destination, le consommateur et l'effet restent inconnus.
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
- [x] Panneaux Tasks / effets : cadres `SCROLL.SHP`, survol `MOUSEFOCUS`, `NOTASKS`; les clics Tasks sont consommés et le pas borné est testé. `InvCycle` utilise aussi son frame de survol.
- [x] Clic d'un glyphe possédé : mémorise l'index et arme le curseur source du mode `0x11`; le clic carte et son effet restent en attente des gardes/consommateur.
- [x] Inventory : la fiche `IWTextInfo` suit l'ID sélectionné après la fin du survol; couvert par `test_island_panel_info`.
- [x] `TOGREALM` inverse ses trois flags; royaume (`FLTINFO` 22–25) et santé (`0x15−maxHP`) sont rendus pour les ouvriers initiaux. Les autres badges attendent leurs champs runtime.
- [x] `PANIC` émet l'événement local type 3/sous-type 0 et le dispatch bascule le bit 0 du mot d'île par joueur; la sémantique reste inconnue.
- [x] Texte New Game : hauteur source 13 px sans réduction verticale; largeur ramenée à 11/13 et interligne `+1` comme compromis de traduction (la source avance de `+3`); huit paragraphes testés dans la zone utile.
- [x] Vérification Release courante : CTest 19/19; exécutable 274466 octets, SHA-256 `989A3085AD56A55C2DB20C961B4E8247FF740CDC350C58BCA887989221F9A992`.
- [ ] Alimenter et rendre les records Tasks actifs avant d’activer le défilement visible; producteur et état initial non identifiés.

## Références

- [MOVEMENT_REVERSE_ENGINEERING.md](MOVEMENT_REVERSE_ENGINEERING.md) — sélection, mouvement et tâches autonomes.
- [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md) — observations, Evidence IDs et inconnues.
- [README.md](README.md) — état du prototype et commandes de vérification.

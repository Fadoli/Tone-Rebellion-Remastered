# Gameplay todo

Porter uniquement les comportements établis par le binaire et les données locales. Les preuves, détails de fonctions et limites sont dans [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md).

## À faire

- [ ] Tracer le consommateur de l'ordre 9 issu du type 34, son événement 7 et les montants de coût absents de `DAT_005eac08`; `0x4c` est un chemin distinct.
- [ ] Relier les producteurs d’événements Tasks et tracer leur libération; `FUN_004637fc` initialise les 64 indicateurs actifs, `FUN_004662b7` alloue les slots et `FUN_00466533` en libère.
- [ ] Identifier le callback et la garde de classe des ordres directs avant d'exposer les commandes soldat/mage.
- [ ] Finir les panneaux d'unités/bâtiments : l'écriture de `+0x22` est établie pour les floaters, mais pas les clés stats du Hall/site; tracer chaque action avant d'ajouter des boutons. Le roster actuel ne couvre que les quatre ouvriers initiaux.
- [ ] Mapper les champs runtime nécessaires aux badges état/charge; établir le sens visuel ou gameplay du mot d'île basculé par `PANIC`. L'événement et son écriture XOR sont identifiés, mais pas l'effet du mot.
- [ ] Tracer l'initialisation/écriture de `DAT_006191f8` et la formule de `% WORKSTR` avant d'afficher surplus et ouvriers.
- [ ] Relier les tâches aux compteurs Inventory; retrouver le contexte exact des appels à `FUN_004503bd` qui alimentent les deux bits de progression et attribuent un glyphe. Les call-sites existent, mais ne prouvent pas une arrivée au Hall.
- [ ] Finir le clic carte après sélection d'un glyphe : son paquet type 3 est observé, mais les gardes de destination, le consommateur et l'effet restent inconnus.
- [ ] Remplacer le placement immédiat par la construction différée source : coûts, sélection d'unité, ordre, trajet et achèvement.
- [ ] Tracer l’activation du bit Hall `+0x1c & 1`; la création/annulation source des demandes mode 2/type 4 est portée, mais affectation, collecte, livraison et cycle idle restent ouverts.
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
- [x] Tasks : lignes et défilement portés pour actions 5, 0x12, 4 (items 5–33) et 0xd; clic sélectionne le slot, le panneau détail affiche priorité et catégorie/titre de transfert. Clic sur `IWTaskOptions` modifie la priorité ou libère le slot après garde d'identité. Autres libellés, icônes de détail et surbrillance restent incomplets. Effets : cadres `SCROLL.SHP`; défilement borné testé. `InvCycle` utilise aussi son frame de survol.
- [x] `IWTaskOptions` : boutons dessinés depuis `PRIOR.SHP` aux panes de `windows.txt`, avec survol et routage source de leurs commandes.
- [x] Réserves Hall : au tick, demande type 4 créée/retirée selon mode, stock, bit Hall et lien de slot observés; annulation utilisateur nettoie le lien modélisé. Les demandes liées sont rendues comme `STOCK` avec les deux cadres TASKICON et l’icône ressource.
- [x] Clic d'un glyphe possédé : mémorise l'index et arme le curseur source du mode `0x11`; le clic carte et son effet restent en attente des gardes/consommateur.
- [x] Inventory : la fiche `IWTextInfo` suit l'ID sélectionné après la fin du survol; couvert par `test_island_panel_info`.
- [x] `TOGREALM` inverse ses trois flags; royaume (`FLTINFO` 22–25) et santé (`0x15−maxHP`) sont rendus pour les ouvriers initiaux. Les autres badges attendent leurs champs runtime.
- [x] `PANIC` émet l'événement local type 3/sous-type 0 et le dispatch bascule le bit 0 du mot d'île par joueur; la sémantique reste inconnue.
- [x] Texte New Game : hauteur source 13 px sans réduction verticale; largeur ramenée à 11/13 et interligne `+1` comme compromis de traduction (la source avance de `+3`); huit paragraphes testés dans la zone utile.
- [x] Vérification Release courante : CTest 19/19; `windows.txt` 100 descripteurs; COB 210 spritesheets/4821 images; exécutable 297238 octets, SHA-256 `E9A8C7A35F2E6A39531A557DA5D95172676F28E383A0993AFF1885524F27BDE4`.
- [ ] Compléter `IWTaskInfo` (quantité/jauge et détails action 5/0x12; aperçu Hall incomplet); porter les liens de flotteurs et autres tables annulées; mapper les autres actions, leurs producteurs runtime et leur libération.

## Références

- [MOVEMENT_REVERSE_ENGINEERING.md](MOVEMENT_REVERSE_ENGINEERING.md) — sélection, mouvement et tâches autonomes.
- [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md) — observations, Evidence IDs et inconnues.
- [README.md](README.md) — état du prototype et commandes de vérification.

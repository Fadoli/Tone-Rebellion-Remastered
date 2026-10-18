# Gameplay todo

Porter uniquement les comportements établis par le binaire et les données locales. Les preuves, détails de fonctions et limites sont dans [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md).

## À faire

- [ ] Relier l'activation de déplacement au dispatcher : `FUN_00441d3e` (`IWLocInfo`) envoie `0x48` via `FUN_0042970c`, tandis que `FUN_00465793` route les sous-types 5/6 vers début/fin; aucune preuve ne relie ces chemins ni n'attribue l'événement à la fenêtre `IWMove`. Le coût est porté/testé; la sélection de destination reste à établir.
- [ ] Relier les producteurs d’événements Tasks et tracer leur libération; `FUN_004637fc` initialise les 64 indicateurs actifs, `FUN_004662b7` alloue les slots et `FUN_00466533` en libère.
- [ ] Identifier le callback et la garde de classe des ordres directs avant d'exposer les commandes soldat/mage.
- [ ] Finir les panneaux d'unités/bâtiments : l'écriture de `+0x22` est établie pour les floaters, mais pas les clés stats du Hall/site; tracer chaque action avant d'ajouter des boutons. Le roster actuel ne couvre que les quatre ouvriers initiaux.
- [ ] Mapper les champs runtime nécessaires aux badges état/charge; établir le sens visuel ou gameplay du mot d'île basculé par `PANIC`. L'événement et son écriture XOR sont identifiés, mais pas l'effet du mot.
- [ ] Tracer l'initialisation/écriture de `DAT_006191f8` et la formule de `% WORKSTR` avant d'afficher surplus et ouvriers.
- [ ] Relier les tâches aux compteurs Inventory; retrouver le contexte exact des appels à `FUN_004503bd` qui alimentent les deux bits de progression et attribuent un glyphe. Les call-sites existent, mais ne prouvent pas une arrivée au Hall.
- [ ] Relier `FUN_00452c31`/`FUN_00452eac` aux transitions de floaters : gardes (+0x18 inclus) et débit local sont portés; l’index +0x18 runtime n’est pas prouvé égal à `IslandData.location_index` (tables 100 vs 0x60, sans alias trouvé). Affectation, choix source/destination, trajet et crédit au Hall restent à établir.
- [ ] Finir le clic carte après sélection d'un glyphe : sur `ISLEVIEW`, le routage direct atteint le callback état 3 `FUN_0042fa0f`, qui met à jour le mode/curseur pour `0x65/0x11` et `/0x13`. Tracer l'effet monde et la sélection résultante avant de simuler une acquisition.
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
- [x] Tasks : lignes/défilement des actions 5, 0x12, 4 et 0xd; clic sélectionne le slot et affiche priorité. `IWTaskInfo` montre `BLDCONST`, l’aperçu statique et les détails de transfert; les icônes d’artefacts IDs 5–33 utilisent `TRIGGERS` frames 0–28. Jauges CONSTR/STOCK/REPAIR portées. Les coordonnées `+0x0a/+0x0e` sont résolues île/emplacement. Le cycle `PROD` des IDs 0x25–0x27 est modélisé; producteur de tâches `CONSTR` et simulation `REPAIR` restent absents. `IWTaskOptions` change la priorité ou libère le slot après garde d'identité.
- [x] `IWTaskInfo` rend l'objet runtime cible des actions type 4/`0xd` à demi-échelle en `pane-local (largeur−30, hauteur−10)` lorsque `owner_id==0`; `CONSTR` garde son aperçu séparé. Ces gardes et la position sont testées; l’animation temporelle exacte n’est pas reproduite.
- [x] `IWTaskOptions` : boutons dessinés depuis `PRIOR.SHP` aux panes de `windows.txt`, avec survol et routage source de leurs commandes.
- [x] Réserves Hall : au tick, demande type 4 créée/retirée selon mode, stock, bit Hall et lien de slot observés; annulation utilisateur nettoie le lien modélisé. Les demandes liées sont rendues comme `STOCK` avec les deux cadres TASKICON et l’icône ressource.
- [x] Clic d'un glyphe possédé : mémorise l'index et arme le curseur source du mode `0x11`; les clics vides dans la pane Glyphes sont consommés sans tomber dans la carte.
- [x] Vérifications courantes : CTest 20/20 (dont intégrité documentaire si Node.js est disponible); `windows.txt` 100 descripteurs; COB 210 feuilles/4821 images; ressources locales des panneaux validées.
- [x] Inventory : le survol pilote `IWTextInfo` sans sélectionner; le clic sélectionne l'item visible (`0x42`). Tests ciblés couvrent les deux états.
- [x] `TOGREALM` inverse ses trois flags; royaume (`FLTINFO` 22–25) et santé (`0x15−maxHP`) sont rendus pour les ouvriers initiaux. Les autres badges attendent leurs champs runtime.
- [x] `PANIC` émet l'événement local type 3/sous-type 0 et le dispatch bascule le bit 0 du mot d'île par joueur; la sémantique reste inconnue.
- [x] Texte New Game : hauteur source 13 px sans réduction verticale; largeur ramenée à 11/13 et interligne `+1` comme compromis de traduction (la source avance de `+3`); huit paragraphes testés dans la zone utile.
- [ ] Établir la signification des lectures `+0x14/+0x18` hors de la ligne de tâche dans `FUN_00450385` avant `SUPPLY`/`UPGRADE`; poursuivre ensuite liens de flotteurs, producteurs runtime et libérations de slots.

## Références

- [MOVEMENT_REVERSE_ENGINEERING.md](MOVEMENT_REVERSE_ENGINEERING.md) — sélection, mouvement et tâches autonomes.
- [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md) — observations, Evidence IDs et inconnues.
- [README.md](README.md) — état du prototype et commandes de vérification.

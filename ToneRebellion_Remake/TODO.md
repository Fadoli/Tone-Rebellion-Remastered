# Gameplay todo

Porter uniquement les comportements établis par le binaire et les données locales. Les preuves, détails de fonctions et limites sont dans [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md).

## À faire

- [x] **Performance — rendu Tasks/texte/sprites :** glyphes écrits directement dans le DIB ([benchmark](bench/task-text-blit.md)); DC source GDI partagé ([bench](bench/sprite-dc-reuse.md)); palette, fallback et transformée de surbrillance réutilisés ([surbrillance](bench/task-highlight.md), [transformée](bench/task-highlight-transform.md)); libellés groupés après les blits ([batching](bench/task-render-batching.md)); l'écran complet est rendu à 30 Hz, y compris quand Tasks est ouvert ([cadence](bench/task-render-cadence.md)).
- [x] **Priorité interface — survol Repair/On-Off :** dessiner le cadre normal puis le cadre d'effet; l'ordre des frames est couvert par `test_window_catalog`.
- [x] **Priorité interface — visibilité On/Off :** limité aux sites de classe 0 avec types `0x25..0x27` appartenant au joueur actif; rendu, survol et clic suivent ce garde. Couvert dans `test_island_panel_info`; voir [preuves et limite du chemin secondaire](../behavior/island-onoff-control.md).
- [x] **Priorité interface — bouton Repair :** cadre normal conservé sous le survol; visibilité et hit-test limités aux IDs de bâtiment réparables appartenant au joueur et à `current < maximum`. Le calcul des PV existait déjà; le contrôle visuel est testé dans `test_island_panel_info`.
- [x] **Priorité interface — file Tasks :** la liste, le défilement et la sélection prennent le joueur actif même sans Hall sélectionné. Test du choix de contexte dans `test_island_panel_info`.
- [x] **Priorité interface — panneau Construction :** `IWLocControl` recouvrait le bas de `IWConstructInfo`, les deux partageant x=456..631. Son rendu est maintenant supprimé pendant l'ouverture modale de la construction; tests de la garde et des bornes des deux fenêtres ajoutés.
- [ ] **Priorité interface — panneau inférieur droit noir :** le détail vide avant survol est conforme à la source (`IWConstructInfo` démarre sans item); vérifier visuellement qu'un item survolé remplit bien le panneau avant de modifier le rendu. Voir [preuves construction](../behavior/island-construction.md) et [rendu île](docs/graphics/island-rendering.md).
- [ ] Compléter les ordres de déplacement : le mode `0x13` et le transfert lié→tick sont portés; restent la cadence de réévaluation, la suppression `FA_Cast`, les phases de défense après arrivée et le mapping subtype→soldat/mage, qui demeure inféré de la contrainte utilisateur. Voir [observations de déplacement](../behavior/island-units-and-movement.md) et [la trace du paquet `0x4c`](MOVEMENT_REVERSE_ENGINEERING.md#0x4c-coordinate-order-and-its-receiver).
- [ ] Relier les producteurs `CONSTR`/`REPAIR` et autres types à la simulation. Producteur `REPAIR` non établi; suivre les paquets catégorie 0 vers `FUN_00465793` (quatre call-sites de l’allocateur examinés : requête `0xb`, deux chemins type 4 et dispatcher). Allocation/libération des 64 slots (`FUN_004662b7`/`FUN_00466533`) est identifiée; achèvement des autres types reste à tracer. Voir [tâches](../behavior/island-tasks.md).
- [ ] Finir `CHARGE` des floaters dans `IWLocInfo` : le modèle conserve le lien `+0x0c` et compteur `+0x22` initiaux, et l'affichage suit la garde du lien; il reste à porter les écrivains du lien via les ordres, puis les transitions d'état qui incrémentent/décrémentent. Voir [panneaux de lieu](../behavior/island-units-and-movement.md).
- [ ] Identifier la méthode virtuelle concrète de `IWRepair` et son lien aux événements 6/7; `BC_Repair` affiche/réserve le clic mais aucun producteur de tâche `REPAIR` (`0x12`) ni effet du message 101 n'est établi. Voir [contrôle Repair](../behavior/island-repair-control.md).
- [ ] Finir `BC_OnOff`: le tick applique désormais OFF (`+0x1c & 0x400` effacé) et la visibilité tient compte du décalage d'ID par tribu. ON exige maintenance ≤ budget; l'initialisation de `owner.+0x6191f8` et les effets secondaires (recalcul du bit `0x001`, références de tâches liées) restent à porter. Voir [contrôle On/Off](../behavior/island-onoff-control.md).
- [ ] Relier les transitions de tâches aux changements Inventory : le champ IDs 5–33 est identifié; le producteur et la destination de la requête de résultat, ainsi que l'effet du helper, restent à établir.
- [ ] Tracer l'acquisition des sites `PIT_Object` (`item=1`) avant d'ajouter un pickup : l'action manuelle grab/place exige un bâtiment joueur comme source et traite item 1 uniquement comme cible. Le lien du tag `fltinf.txt`/`pickup` à une collecte automatique, le producteur de catégorie 3/sous-type 4 et la mutation du site source restent inconnus. Voir [analyse](../behavior/island-ground-object-interaction.md).
- [ ] Retrouver le contexte exact des appels à `FUN_004503bd` qui alimentent les deux bits de progression et attribuent un glyphe; les call-sites ne prouvent pas une arrivée au Hall.
- [ ] Relier `FUN_00452c31`/`FUN_00452eac` aux transitions de floaters : gardes (+0x18 inclus) et débit local sont portés; l’index +0x18 runtime n’est pas prouvé égal à `IslandData.location_index` (tables 100 vs 0x60, sans alias trouvé). Affectation, choix source/destination, trajet et crédit au Hall restent à établir.
- [ ] Finir l'effet monde du clic glyphe : la promotion après allocation et son tirage borné sont tracés; `tone_rng` porte déjà la formule. Il reste à établir le sens de `DAT_004befe0`, l'état/allocation des acteurs et l'ordre `0x13`. Voir [glyphes](../behavior/island-inventory-glyphs.md).
- [ ] Porter la sélection/validation/attache IA des slots type 5, puis établir son lien à `FA_Build`; coûts, trajet et achèvement restent requis avant d'activer la pose différée. `FA_Cast` (`0x13`), produit par `FUN_0045da80`, est une action distincte. La recherche `FUN_0042219e` et le validateur `FUN_00422031` sont maintenant identifiés (`FUNCTION_GUIDE.md`); le mapping paquet→slot (priorité 1, champs et déduplication) est porté et testé. Voir [construction](../behavior/island-construction.md).
- [ ] Tracer l’activation du bit Hall `+0x1c & 1`; la création/annulation source des demandes mode 2/type 4 est portée, mais affectation, collecte, livraison et cycle idle restent ouverts.
- [ ] Ajouter des tests source-backed pour les gardes refusées, commandes, construction différée et interactions de panneaux.
- [ ] Relier les effets sonores aux événements qui les déclenchent.
- [ ] Vérifier visuellement l'ordre de superposition et les hit-tests des panneaux Hall.
- [ ] Raccorder le commerce au transport réseau si le remake ajoute le multijoueur; le transfert local type `0xb` est maintenant consommé par le tick et testé bout en bout.
- [ ] Établir la signification des lectures `+0x14/+0x18` hors de la ligne de tâche dans `FUN_00450385` avant `SUPPLY`/`UPGRADE`; poursuivre ensuite liens de floatteurs, producteurs runtime et libérations de slots.

## Avancement

Les éléments déjà portés et leurs limites sont résumés dans [fonctionnalités réalisées](docs/implemented.md). Les pseudocodes et preuves restent référencés dans [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md).

## Références

- [MOVEMENT_REVERSE_ENGINEERING.md](MOVEMENT_REVERSE_ENGINEERING.md) — sélection, mouvement et tâches autonomes.
- [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md) — observations, Evidence IDs et inconnues.
- [README.md](README.md) — état du prototype et commandes de vérification.

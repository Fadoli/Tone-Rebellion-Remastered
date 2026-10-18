# Gameplay todo

Porter uniquement les comportements établis par le binaire et les données locales. Les preuves, détails de fonctions et limites sont dans [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md).

## À faire

- [ ] **Priorité interface — boutons On/Off :** survol ajouté en deuxième passe au-dessus du cadre normal. Il reste à établir les types autorisés avant de masquer le bouton pour certains bâtiments; le dispatch `FUN_00453bf6` prouve un garde de maintenance pour l’activation, pas la règle de visibilité. Voir [On/Off](../behavior/island-onoff-control.md).
- [x] **Priorité interface — bouton Repair :** cadre normal conservé sous le survol; visibilité et hit-test limités aux IDs de bâtiment réparables appartenant au joueur et à `current < maximum`. Le calcul des PV existait déjà; le contrôle visuel est testé dans `test_island_panel_info`.
- [x] **Priorité interface — file Tasks :** la liste, le défilement et la sélection prennent le joueur actif même sans Hall sélectionné. Test du choix de contexte dans `test_island_panel_info`.
- [ ] **Priorité interface — bandeau inférieur :** la file Tasks est désormais liée au joueur actif; la zone noire droite reste à diagnostiquer. `ISLETMP` charge déjà la variante du joueur en 640×160 à y=320. Le rendu ne reconstruit pas encore toute la hiérarchie des fenêtres; comparer les panneaux visibles et leurs frames avant d’ajouter du remplissage. Voir [rendu île](docs/graphics/island-rendering.md).
- [ ] Compléter les clics de déplacement : le callback exact de `ISLEVIEW` pour `0x3d(1,1)` reste inconnu; établir aussi le mode dispatcher au clic `0x32`, le lien de `0x48` et la correspondance des IDs runtime avec le roster. Voir [observations de déplacement](../behavior/island-units-and-movement.md).
- [ ] Relier les producteurs `CONSTR`/`REPAIR` et autres types à la simulation. Producteur `REPAIR` non établi; suivre les paquets catégorie 0 vers `FUN_00465793` (quatre call-sites de l’allocateur examinés : requête `0xb`, deux chemins type 4 et dispatcher). Allocation/libération des 64 slots (`FUN_004662b7`/`FUN_00466533`) est identifiée; achèvement des autres types reste à tracer. Voir [tâches](../behavior/island-tasks.md).
- [ ] Identifier le callback et la garde de classe des ordres directs avant d'exposer les commandes soldat/mage.
- [ ] Porter `CHARGE` des sites dans `IWLocInfo` : `floater.txt` et le champ stats `+8` sont maintenant tracés, mais la clé brute sélectionnée (`+0`, `+4`) et le mutable `+0x22` ne sont pas mappés au modèle de site. Le roster ne couvre encore que les quatre ouvriers initiaux. Voir [panneaux de lieu](../behavior/island-units-and-movement.md).
- [ ] Identifier la méthode virtuelle concrète de `IWRepair` et son lien aux événements 6/7; `BC_Repair` affiche/réserve le clic mais aucun producteur de tâche `REPAIR` (`0x12`) ni effet du message 101 n'est établi. Voir [contrôle Repair](../behavior/island-repair-control.md).
- [ ] Finir `BC_OnOff`: l'icône et la requête sont portées; établir le garde `owner.+0x6191f8`, les callbacks après transition et les tâches liées à `+0x4e/+0x52/+0x54` avant de modifier le bit `+0x1c & 0x400`. Voir [contrôle On/Off](../behavior/island-onoff-control.md).
- [ ] Relier les transitions de tâches aux changements Inventory : le champ IDs 5–33 est identifié; le producteur et la destination de la requête de résultat, ainsi que l'effet du helper, restent à établir.
- [ ] Retrouver le contexte exact des appels à `FUN_004503bd` qui alimentent les deux bits de progression et attribuent un glyphe; les call-sites ne prouvent pas une arrivée au Hall.
- [ ] Relier `FUN_00452c31`/`FUN_00452eac` aux transitions de floaters : gardes (+0x18 inclus) et débit local sont portés; l’index +0x18 runtime n’est pas prouvé égal à `IslandData.location_index` (tables 100 vs 0x60, sans alias trouvé). Affectation, choix source/destination, trajet et crédit au Hall restent à établir.
- [ ] Finir l'effet monde du clic glyphe : la promotion après allocation et son tirage borné sont tracés; `tone_rng` porte déjà la formule. Il reste à établir le sens de `DAT_004befe0`, l'état/allocation des acteurs et l'ordre `0x13`. Voir [glyphes](../behavior/island-inventory-glyphs.md).
- [ ] Relier le slot Tasks type 5 créé au tick à son consommateur puis à l'ordre `0x13`; établir coûts, unité, trajet et achèvement avant d'activer la pose locale. Le mapping paquet→slot (priorité 1, champs et déduplication) est maintenant porté et testé; aucun effet site n'est appliqué. Voir [construction](../behavior/island-construction.md).
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

# TODO — Interface

- [x] **Priorité interface — survol Repair/On-Off :** dessiner le cadre normal puis le cadre d'effet; l'ordre des frames est couvert par `test_window_catalog`.
- [x] **Priorité interface — visibilité On/Off :** limité aux sites de classe 0 avec types `0x25..0x27` appartenant au joueur actif; rendu, survol et clic suivent ce garde. Couvert dans `test_island_panel_info`; voir [preuves et limite du chemin secondaire](../behavior/island-onoff-control.md).
- [x] **Priorité interface — bouton Repair :** cadre normal conservé sous le survol; visibilité et hit-test limités aux IDs de bâtiment réparables appartenant au joueur et à `current < maximum`. Le calcul des PV existait déjà; le contrôle visuel est testé dans `test_island_panel_info`.
- [x] **Priorité interface — file Tasks :** la liste, le défilement et la sélection prennent le joueur actif même sans Hall sélectionné. Test du choix de contexte dans `test_island_panel_info`.
- [x] **Priorité interface — panneau Construction :** `IWLocControl` recouvrait le bas de `IWConstructInfo`, les deux partageant x=456..631. Son rendu est maintenant supprimé pendant l'ouverture modale de la construction; tests de la garde et des bornes des deux fenêtres ajoutés.
- [ ] **Priorité interface — panneau inférieur droit noir :** le détail vide avant survol est conforme à la source (`IWConstructInfo` démarre sans item); vérifier visuellement qu'un item survolé remplit bien le panneau avant de modifier le rendu. Voir [preuves construction](../behavior/island-construction.md) et [rendu île](docs/graphics/island-rendering.md).
- [ ] Vérifier visuellement l'ordre de superposition et les hit-tests des panneaux Hall.

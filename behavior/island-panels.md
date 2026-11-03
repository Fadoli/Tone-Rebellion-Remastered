# Notes détaillées historiques — panneaux

Cette page est un index; le détail est réparti en pages thématiques pour limiter la taille de navigation.

## Mise à jour du texte de survol Inventory

- [Mise à jour du texte de survol Inventory](island_panels_pages/page-01.md)

## Frontières des événements Inventory et Glyphes

- [Frontières des événements Inventory et Glyphes](island_panels_pages/page-01.md)

## Tableau de transfert Trade

- [Tableau de transfert Trade](island_panels_pages/page-01.md)

## Panneau Diplomatie

- [Panneau Diplomatie](island_panels_pages/page-01.md)

## Fenêtres île : empilement et modes (revue REA, sous-agent, non relue)

Observations (`windows.txt` état 3; `FUN_0042f303` `ev_379f1f88…`; `FUN_0042fa0f`; `FUN_004293c6` `ev_0cec1d4c…`) : panneau gauche x 192–447 (IWTasks, IWTrade, IWDiplomacy, IWLocInfo, IWConstruct, IWInventory, IWGlyphs, de même rectangle; IWEffList/IWSFXList; IWLilMap 192,328–447,359); panneau droit x 456–631 (IWTaskInfo/IWFltInfo/IWTextInfo 328–395; IWTaskOptions/IWLocControl/IWTextInfo2 396–471; IWConstructInfo 328–471). Chaque mode de `FUN_0042f303` masque d'abord 16 fenêtres puis montre : 0 et 3 LocInfo+LocControl+TextInfo, 1 Construct+ConstructInfo, 2 Tasks+TaskOptions+TaskInfo, 4 TextInfo+LocControl+Inventory, 5 …+Glyphs, 6 …+Diplomacy, 7 …+Trade, 8 EffList+SFXList. Les fenêtres affichées simultanément ne se recouvrent pas; seuls les boutons `BC_*` et ceux d'`IWRealm` chevauchent les panneaux. Les boutons Hall (message 0x65 codes 0xb→4, 0xc→5, 0xd→7, 0xe→6) fixent le mode sans bascule; `TASKLIST` (0x7d5) bascule 2/0; message 0x44 avec bâtiment sélectionné passe par `FUN_0042f755`. `IWTextInfo2`, `IWFltInfo`, `IWConstructInfo` ne sont montrées par aucun mode (source inconnue).
Inconnues : boucle de distribution souris et ordre z (aucun appelant résolu), consommateur de `+0x34`, correspondance bouton→code, codes 0xf/0x10–0x1c. Le port (modes sans bascule pour les boutons Hall, bascule Tasks, fermeture de la construction à l'ouverture d'un autre panneau) concorde avec ces observations.

Ordre de survol (REA haiku 2026-11-03, `ev_1d8a9f0b…`, `ev_366ff9fe…`, `ev_712c1cc0…`, `ev_ad5951f4…`): `FUN_0046be81` ne parcourt que les emplacements de contrôles de la fenêtre active (`[ECX+0x29f2]`, tableau `+0x1f44`, pas 0x130) à rebours, de 73 à 0, et s'arrête au premier contrôle (`+0x40 == 1`, `+0x38 == 1`, point dans `+0xc..+0x18`): le plus haut emplacement gagne; l'id survolé va dans `[+0x1f3c]` (0x46c0ed). Les clics (`FUN_00469f56` cas 2/4 → `FUN_0046c25d`) parcourent le même ordre sans test de position et s'arrêtent au premier gestionnaire (vtable +4) qui consomme. Le port teste déjà les volets dans l'ordre inverse des descripteurs avec premier gagnant (`window_catalog_hit_test`), ce qui concorde si l'ordre des emplacements suit `windows.txt` (création `FUN_0046c7df`, interprétation). Bornes (`ev_29b411f5…`, `ev_f87fbf45…`): les quatre bords sont inclus (`JG`/`JL` signés, point en mots étendus), et `FUN_0046cd22` range les valeurs PANE de `windows.txt` sans ajustement; port aligné le 2026-11-03 (`window_catalog_hit_test`).

Distribution souris (REA, sous-agent, non relue) : `DAT_0062c6bc` (identifiant de la fenêtre au focus souris, -1 = aucun) n'a qu'un écrivain trouvé, la remise à -1 dans la boucle principale `FUN_0041c46f` (`ev_26533cae…`, sur `DAT_004c2b70`); les 26 autres références sont des lectures (`ev_25e7336e…`). `FUN_004293c6` ne transmet les messages 6/7 que si l'identifiant de l'objet égale ce focus. L'affectation du focus (donc l'ordre z / premier ou dernier recouvrement) n'est pas lisible statiquement: écriture indirecte probable (`FUN_0046c4a5`/`FUN_0046be81` non lues). Aucun port possible de l'ordre z natif; le port garde son ordre de test local.

Sélection par défaut et raccourcis (décision du port, revue REA du mode 0 de `FUN_0042f303`, `ev_379f1f88…`) : le mode 0 montre `IWLocInfo`/`IWLocControl`/`IWTextInfo` et rafraîchit la sélection sur l'enregistrement d'accueil du joueur (`DAT_0061a580/82`) quelle que soit l'île: sans autre sélection le Hall reste donc sélectionné partout (le port: `hall_default_selected`, `effective_info_location`). `CLIPSEL`/`CLIPBD` ne font pas partie des 16 fenêtres masquées par `FUN_0042f303`: la bande de raccourcis est visible dans tous les modes. Le port inscrit en plus chaque bâtiment d'entraînement possédé dans la bande (groupe actif d'abord) et un clic sur un emplacement change d'île si besoin. Clic sur la vue île avec le panneau Tâches ouvert : le natif ne masque que les fenêtres du panneau, pas `ISLEVIEW`; le port traite le clic (pont conservé, sinon retour au mode 0).

Sites mystiques (classe 3, REA haiku 2026-11-03, `ev_fd65e30c…` `FUN_00435581`, `ev_e0431074…` `FUN_0040bf98`, `ev_20a8dd58…` `FUN_00439673`, `ev_8518ba3d…` `FUN_00429ebe`): aucun effet de survol propre. Le test de survol ne lit pas la classe; le peintre de site ne reçoit pas l'indice survolé. Panneaux: `FUN_00441b36` affiche `MYSTLOC` (porté); `FUN_00439673` cherche `FEAT_%02d` (indice < 14), clé absente de `gamey.txt` et de tout le corpus, et `FUN_00429ebe` rend NULL: rien n'est dessiné. Correction (REA haiku 2026-11-03, `ev_b7679b0e…` `FUN_00435f4d`): le site survolé `+0x17a` scintille (`FUN_00411478`, x ± 0x17, y ± 0x17) s'il est un déclencheur de trait (`+4 == 3`, `+0x10 == 3`), quel que soit le mode; un objet armé (`DAT_0049e9c4 != -1`) dessine son cadre `TRIGGERS` (objet − 5) à la souris + (10, 0). Port: fin de la vue d'île dans `render_island_view`; non vu en jeu (aucun déclencheur atteignable dans les fixtures). Inconnu: récepteur du message 0x47 de survol.

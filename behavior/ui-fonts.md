# Polices et couleur du texte de l'interface

Revue REA statique (ev_53d66012…, ev_70fb3a4e…, ev_8d56945f…, ev_10224cb4…, ev_032a30a4…, ev_a28e4243…, ev_4f78cc75…).

## Observations

- Trois polices `.fnt` de format identique (en-tête `1.`, 226 glyphes, hauteur à l'octet 8): `bigfont.fnt`
  (objet `DAT_005c2870`, hauteur 11), `smfont.fnt` (`DAT_005c30b8`, hauteur 8) et `bgoutfnt.fnt` (objet `0x4c2f30`,
  hauteur 13; chargée par `FUN_0046cd22`). `FUN_0042c0fa` charge `bigfont` et `smfont`; `FUN_00428800` est le
  constructeur d'objet de police (colour = -1, table identité `DAT_004c2dc0`).
- `FUN_0042de0d` renvoie toujours `&DAT_005c30b8` (`smfont`), `FUN_0042de03` renvoie `&DAT_005c2870` (`bigfont`): pas
  de variable d'état par fenêtre; le choix est fait par l'appelant (19 appelants du thunk `smfont` `0x4014c9`, 18
  du thunk `bigfont` `0x401c30`).
- Valeurs de pixel des glyphes: `smfont` et `bigfont` utilisent 243 (encre) et 255 (transparent); `bgoutfnt` utilise 1
  (encre), 0 (fond) et 255. `FUN_004289ec` remplace toute valeur non transparente par le champ couleur de l'objet quand
  il vaut autre chose que -1; `FUN_0042da69` écrit l'indice de palette 6 (`DAT_0049e140[6]`) dans les champs couleur
  de `smfont` et `bigfont`. Texte de panneau = police `smfont`, indice de palette 6.
- Légende de la Diplomatie (`FUN_0043e5aa`): `smfont`, indice 6, en `(W/2 + 15, 7)`. `IWTextInfo` et la
  description d'`IWConstructInfo` mesurent leur hauteur de ligne par `FUN_0042de0d`, donc `smfont`: h = 8, pas de ligne 9,
  première ligne à `6 + 9`. Correction: les sections précédentes de `island-inventory-glyphs.md` et
  `island-construction.md` calculaient h = 13 (`bgoutfnt`), ce qui était faux.
- Couleur de `bgoutfnt` (champ de l'objet `0x4c2f38`): écrivains non résolus.

## Port

`g_small_font` (`data\smfont.fnt` de TONE01.COB), `draw_small_label`, `measure_small_text`, `draw_wrapped_small_label`;
`bitmap_font_render_pixels` traite maintenant comme encre toute valeur différente de 0 et 255. Appliqué à `IWTextInfo`,
à la légende de la Diplomatie et à la description d'`IWConstructInfo` (indice de palette 6, h = 8). Les autres textes
(libellés de tâches, compteurs, panneau Hall…) gardent `bgoutfnt` et leurs couleurs: la police native de chacun
n'est pas établie.
Non porté: police et couleur des autres libellés (lecture des appelants des thunks `0x4014c9` et `0x401c30`),
couleur du champ de `bgoutfnt`, `bigfont`.

## Appelants des accesseurs de police (REA, ev_f69f439b…, ev_0992754b…)

`smfont` (thunk `0x4014c9`): panneau de score de fin (`0x419a6b`, `0x41a8df`, `0x41b0d7`), étiquettes de carte d'île
(`0x435f4d`), `IWTextInfo` (`0x439673`), coût de construction (`0x43b369`, nombre `%d` en `(0x25, 0x2d)`), compteurs de
l'inventaire (`0x43d6a3`: `(%d)`; `NOART` en `bigfont`), légende de Diplomatie (`0x43e5aa`), commerce (`0x43edac`),
détail de bâtiment du Hall (`0x440567`: `SURPFLOW`, `POPSTR`, `WORKSTR`), détail d'unité (`0x44338b`: nom, `LEVEL`, `HITS`,
`STRENGTH`, `CHARGE`), liste de tâches (`0x4459e6`: libellés et `[%d]`, couleurs de ligne 5 ou 2 selon l'état),
détail de tâche (`0x4469d6`), liste de sauvegardes (`0x45858a`). `bigfont` seule (`0x401c30`): étiquettes de lieu
(`0x441b36`), sélecteur de mode de tâche (`0x446620`), écran de nouvelle partie (`0x44ec5d`), en-tête de royaume de la
carte (`0x4711e2`), débogage. La couleur par défaut est l'indice 6 (écrit par `FUN_0042dd0f(6)` après chaque
changement).
Port: les libellés des panneaux Hall, tâches, commerce, inventaire, diplomatie, détail d'unité et construction (fichiers
`hall_panel_render.inc`, `island_item_render.inc`, `island_view_render.inc`) passent à `smfont`, indice de palette 6
(macros dans `menu_app.c`); les textes avec renvoi partagé, la nouvelle partie, le texte d'aide du menu et la carte
gardent `bgoutfnt`. Non porté: couleurs de ligne 5 et 2 des tâches, `bigfont` des étiquettes de lieu et de
`NOART`, géométrie verticale recalculée sur la hauteur 8 (certains centrages utilisent encore la hauteur 13).

Mise à jour: `bigfont.fnt` (`dataigfont.fnt` de TONE01.COB, hauteur 11) est chargée (`g_big_font`, `measure_big_text`, `draw_big_label`)
et sert au texte `NOART` du panneau Inventaire (palette 6), seul usage de `bigfont` dans un panneau déjà confirmé par `FUN_0043d6a3`.
Les autres usages de `bigfont` (étiquettes de lieu, écran de nouvelle partie, en-tête de royaume) ne sont pas établis comme police dessinée.

Correctif (relecture indépendante des changements): la macro `draw_bitmap_label` des fichiers Hall/île ne passe plus tout en palette 6;
elle n'y remplace que les couleurs par défaut choisies à la main (`panel_text_color`), les autres (statuts, avertissements, marqueurs)
sont conservées. `bigfont` est facultative (repli sur `smfont` pour `NOART`). Autres correctifs: garde de `player_slot` dans le panneau
Diplomatie, bornes et cas `code == next_code` du décodeur GIF, indicateur de relâchement du clic de carte remis à zéro au clic suivant.

## Correctif couleur: les emplacements de stylo sont des correspondances RGB (relecture des notes `functions/`)

Observation (pseudocode en cache `functions/0011_batch_0007/details-05-01.md`, `functions/0012_batch_0008/details-01-01.md`, `functions/0008_batch_0004/details-02-01.md`; ev_fcb5b3b0…, ev_4b05090f…; pas de nouvelle lecture Ghidra, session REA fermée): `FUN_0042da69` appelle `FUN_0042bfa9` après chaque changement de palette. Celle-ci recalcule `DAT_0049e140[1..6]` = indice de palette le plus proche (`FUN_0041081b`: distance RGB 6 bits au carré, indices 0..254, premier minimum) des cibles stockées à `0x49e148`. Lues dans la section `.data` du fichier (valeurs initiales, non vérifiées à l'exécution): 1 = (63,63,63), 2 = (63,0,0), 3 = (0,63,0), 4 = (0,0,63), 5 = (63,63,0), 6 = (50,50,50). Gamma `_DAT_0049e13c` initial = 1.0.
Interprétation: le texte par défaut (emplacement 6) est le gris le plus proche de (50,50,50), pas l'indice 6 littéral de `island*.pal` ((42,29,14), brun) — cause du texte rougeâtre. Emplacements 2 et 5 (lignes de tâches) = rouge et jaune les plus proches.
Port: `native_text_color` (`sprite_primitives.inc`) remplace `palette[6]`/`[2]`/`[5]` pour le texte. Non vérifié: appelants de `end_game_screen.inc:144` (indice passé tel quel), écrivains éventuels de `0x49e148` à l'exécution.

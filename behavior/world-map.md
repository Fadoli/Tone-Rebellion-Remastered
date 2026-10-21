# Acces aux iles depuis la carte

## Accès aux îles depuis la carte

| Adresse / fonction Ghidra | Rôle étayé et observations | Pseudocode |
|---|---|---|
| `0x46466f` `FUN_0046466f` | Pour chacun des quatre slots joueur, choisit l'île de départ puis met à `1` le dword runtime à `île + 0x29ac + slot*4`. | [initial world setup](../functions/0017_batch_0013.md#fun_0046466f--0x46466f) |
| `0x47117d` `FUN_0047117d` | Parcourt les quatre slots et renvoie vrai si le masque actif `DAT_004bf0f0[DAT_004befec]` contient le bit du slot **et** si le dword runtime correspondant à `île + 0x29ac + slot*4` est non nul. | [island entry gate](../functions/0018_batch_0014.md#fun_0047117d--0x47117d) |
| `0x471e66` `FUN_00471e66` | Dessine les îles de la carte. Pour le groupe `SMISLE` de chaque île, l'offset de frame vaut `+15` si `FUN_0047117d` refuse l'accès, `+0` si l'île est accessible, et `+30` si elle est accessible et sélectionnée. Le même chemin dessine les liens actifs via `FUN_00471b74`; `FUN_004718eb` ne crée ces entrées d'affichage que si le flag runtime du lien est non nul. Le message WORLDWIN `0x4f` met tous ces flags à 1 si le bit `0x100` est absent, et à 0 s'il est présent (`FUN_004702d9`). | Evidence REA `ev_6e36780f41a531e2dfc3f54e7397ffdf4c784b39baff3f6e88954fe4f89de3a8` |
| `0x4669bd` `FUN_004669bd` | Pour un record de classe 2, active le lien WORLDPOS correspondant si les deux extrémités concordent, marque les deux records, puis acquiert l'île voisine pour le propriétaire valide via `FUN_00466b09`. Enfin, `FUN_00466c8b` recalcule les budgets joueurs et l'état des deux îles. `FUN_004672ef` l'appelle dans ses variantes 4 (tous les ponts de l'île) et 0x0c (un record). Le producteur de ces commandes reste à tracer. | Evidence REA `ev_b30589ad8e8dc4fd8f9e7c50be1117bbafa5e3808f994368fd7124a2c0d4ddc4`, `ev_0903519668327e8ca19f3cc31aa3a2ec5afed820badae8241d6d43bf213c3710` |
| `0x4711e2` `FUN_004711e2` | N'affiche le nom de l'île sélectionnée qu'après validation par `FUN_0047117d`; les noms ne sont donc pas révélés pour une île inaccessible. | Evidence REA `ev_e419f0590f1605f2f6c422dab09e4d4e72cfadd4a4dff7155135229a20dc1503` |
| `0x470fe7` `FUN_00470fe7` | Le handler vérifie que l'index d'île mémorisé n'est pas `-1`, que `DAT_006191b4` vaut zéro et que `FUN_0047117d` autorise l'accès avant d'enregistrer l'île et de poursuivre la transition. Nouvelle décompilation REA: `ev_02516916c2e3f63c0fd2a31ed7afee723f4e749127822fce467772757d83069e`. | [world map island transition](../functions/0018_batch_0014.md#fun_00470fe7--0x470fe7) |
| `0x466b09` `FUN_00466b09` | À la première acquisition, met à `1` le dword d'accès du propriétaire, recalcule sa visibilité et enfile deux dwords (`0x0c`, short issu de la table de l'île) via `FUN_004655b2`. Le consommateur de cette file opaque n'est pas identifié; ne pas la confondre avec le cas `0x0c` de `FUN_004672ef`. | Evidence REA `ev_0d9cf2611cf5255de9afc73347a543c4f867aba75af9e735573bb3d07b931a74`, `ev_40e57a701dcdfcc8c86be5c2642b1ceba5aee4bcfc77fe9923616cbdf99e14a9`; [pseudocode](../functions/0017_batch_0013.md#fun_00466b09--0x466b09) |

**Port remake :** `GameRuntimeIsland.access_mask` représente les quatre dwords observés; `FUN_0046466f` est reproduite en ajoutant le bit de chaque slot à son île de départ. L'ouverture depuis la carte teste le bit de la tribu sélectionnée, pour le modèle mono-joueur actuel. `game_session_world_map_frame_offset` reprend les trois groupes de frames observés (`+15` inaccessible, `+0` accessible, `+30` accessible et survolée) et le rendu du nom est masqué pour une île inaccessible. La carte tourne et se repeint sans entrée utilisateur via son timer 33 ms; le même tick recalcule le survol sous un curseur immobile. Un lien de carte n'est rendu que si son flag runtime est actif, si les deux îles ont un marqueur de pont de classe 2 apparié réciproquement à ce lien par `FUN_00461859`, et si les deux records portent le bit de construction observé à `+0x1c` dans `FUN_004669bd`. `game_session_mark_bridge_constructed` modèle cette mise à jour appariée, l'accès et la visibilité du propriétaire, puis recalcule les budgets joueurs et l'état Leviathan des deux îles comme `FUN_00466c8b`. La file opaque `[0x0c, short]` de `FUN_004655b2` reste non modélisée, faute de consommateur identifié; elle est distincte du dispatcher `FUN_004672ef`. Le producteur de la commande d'achèvement du pont reste à raccorder; un edge WORLDPOS possible ou actif ne suffit donc pas à afficher un pont construit. Les particules du pont sont animées de façon déterministe par tick, sans consommer le RNG gameplay. Le masque actif multi-joueur et la mise à jour d'accès après conquête restent à porter. Le graphe statique des ponts n'est pas en soi une autorisation d'entrée.

**Validation avec les données :** `tone` est le tag de classe 1 utilisé comme marqueur dans `FUN_0046466f`. Les fichiers `ISLAND00.TXT` à `ISLAND03.TXT` contiennent chacun quatre records `tone`; le test du corpus confirme que les quatre affectations et leurs sites voisins se résolvent avec les règles transcrites. Le post-traitement `FUN_00461859` associe séparément les liens du monde aux emplacements de classe 2; il n'est pas la source des marqueurs `tone`.

**Port RNG :** `ToneRebellion_Remake/src/core/tone_rng.c` retranscrit la transition de `FUN_00474b90` et l'échelle de `FUN_00467260`. La constante flottante à `0x494798` est `32768.0f` (octets `00 00 00 47`). Le test `tone_rng_unit` vérifie la séquence pour une graine connue et la conversion bornée; le menu Win32 utilise désormais le même helper 15 bits au lieu d'une copie locale.

## Revue de la carte du monde (REA, ev_beac7117…, ev_1f14e1d2…, ev_0068c343…, ev_0b2dd322…)

Observation: le peintre est `FUN_00471e66` (boucle sur les enregistrements d'île/pont dans l'ordre
des enregistrements; décalage de frame +15 inaccessible, +0 accessible, +30 accessible et
`this+0x76`), appelé depuis `FUN_004711e2` (nom). `this+0x76` n'est écrit que par `FUN_00470f67`
(message de déplacement de souris, test `FUN_00472013` sur le rectangle `DAT_006323b0 + id*0x10`
rempli par `FUN_00405e11`, île du dessus d'abord, -1 sans île) et remis à -1 par `FUN_004701ef`:
c'est l'île survolée, non persistante. Le nom (`xTarzus`, table `0x4a4870`, centré x, y = 0x3c)
n'est dessiné que pour cette île, si accessible et `DAT_006191b4 == 0`. Le clic (`FUN_004702d9`
cas 6 puis `FUN_00470fe7`) entre directement dans l'île survolée accessible
(`DAT_0049f53c = île`, `FUN_0046c1b4(1, 3, 0)`): un seul clic, pas d'étape de sélection.
Port: le nom ne se rabat plus sur l'île « sélectionnée », un clic sur une île survolée
l'ouvre (`open_island_view` vérifie l'accès) et le texte « CLICK AN ISLAND TO SELECT… » écrit par
le port (absent des chaînes de l'exécutable) est retiré. Entrée au clavier inchangée
(commodité du port). Non vérifié: bouton enfoncé ou relâché pour le cas 6, sens de
`DAT_006191b4`/`DAT_0062c6bc`, positions (`FUN_00471536`, formule orbitale du port), ordre de
dessin ponts/îles (ordre des enregistrements), étiquette de débogage `%d` (touche 'N'), le
re-test de survol à chaque tick du port (non vu dans le natif).

### Positions, ponts et message de clic (REA, ev_b56fc9b6…, ev_425a59e3…, ev_b9ab52f4…, ev_23872f34…)

Observation: `FUN_004718eb` reconstruit les enregistrements: d'abord une entrée de type 0 par île,
puis une de type 1 par lien actif; `FUN_00471e66` les dessine dans cet ordre, donc les ponts passent
par-dessus les îles. Position: `phase = (DAT_00618e44 mod 1440) * 0.017453277 / 4 + acc`, `a = θ - phase`
(θ float de l'île `+0x29d4`, rayon `+0x29d8`, hauteur `+0x29dc`), `X = cos(a) * r * 0.13`, `Y = sin(a) *
r * 0.06`, `Z = z * 0.06`, `x = cx + trunc(X + 0.5)`, `y = cy - trunc(Y + Z + 0.5)` (troncature x87
« chop »); `acc` (radians) avance de ±6° par message 302 quand l'animation tourne (bit 0 = marche,
bit 1 = sens, déplacés par les messages 300/301, pas par ceux-ci). Le pont est un nuage d'étincelles
le long du segment A-B (10 points par pas, jitter RNG, palette de 8 indices); chaque point appelle le
RNG de jeu 11 fois. Souris: l'événement 2 de la pompe (`WM_LBUTTONDOWN`) devient le message 6;
le relâchement (événements 3, 5, 7) n'est jamais transmis: le clic d'île est donc le bouton
gauche enfoncé.
Port: la forme de la formule concorde (échelles 0.13/0.06, phase 0.25°/tick mod 1440, troncature). Corrigé:
ponts dessinés après les îles; clic de carte sur `WM_LBUTTONDOWN` (le relâchement suivant est ignoré).
Écarts restants: terme `acc` (cadence de 302 inconnue), unité de θ (radians dans le natif, degrés
dans le port, conversion du chargeur introuvable), centre `cx/cy` (`this+0x784/786`) codé 320/240,
flottants 32 bits x87 contre double, RNG de jeu non consommé par la peinture (choix du port).

### Rotation, angle et centre (REA, ev_9c2912b8…, ev_12722ce8…, ev_ebaac76f…, ev_5f770dc6…)

Observation: la carte ne tourne pas « par défaut » par le terme `acc`: `this+0x788` vaut 0 à l'initialisation
(`FUN_004701ef`); la phase de base `(DAT_00618e44 mod 1440) * 0.017453277 / 4` avance en permanence.
Les messages 300/301 (flèche gauche/droite, `FUN_004702d9` cas 5) basculent le bit de marche et le sens, 303
est l'espace, flèche haut/bas règlent `this+0x70` (zoom); le message 302 posté à l'initialisation par
`FUN_0046b928` (période 0) est renvoyé à chaque passage de `FUN_0046bacf` et ajoute ±6° à `acc` seulement si le
bit de marche est levé. Aucun contrôle de `windows.txt` n'envoie 300/301/302. Angle: `worldpos.txt`
(degrés), converti en radians au chargement par `FUN_004642a3` (`* 0.017453277`), copié par `FUN_00461859`
dans l'île (`+0x29d4/d8/dc`): le port garde les degrés et convertit, ce qui est équivalent (la note
« conversion introuvable » plus haut est obsolète). Centre: `FUN_00470259` écrit `cx = (+0x14 - +0xc) / 2` et
`cy = (+0x18 - +0x10) / 2 + 15` (+15 pour dégager le nom), soit 319 et 254 pour la pane 0 0 639 479.
Port: centre passé de (320, 240) à (319, 254) (même convention de pane inclusive que les panneaux
d'île). Non porté: la rotation au clavier (le port utilise flèche gauche/droite pour changer de monde),
le zoom, la cadence réelle de 302 (producteur de `FUN_0046bacf` indirect), le rectangle exact
`this+0xc..0x18`.

### Rotation clavier, zoom et échelle des îles (REA, ev_9c2912b8…, ev_4f9cb8ec…, ev_78bb7097…, ev_86fc6dd6…, ev_b3bada15…)

Observation: le message 302 est mis en file avec une période 0 et est donc délivré une fois par appel de la pompe
`FUN_00469f56`, elle-même limitée par la boucle principale à `frame_limit` images par seconde (`DAT_004c2b60`, clé
`frame_limit` de `float.cfg`, 20 dans `THING1\FLOAT.CFG`). Les touches flèche gauche/droite (300/301), espace (303) et
haut/bas (zoom `+0x70` par pas de 0x1000, de 0x1000 à 0x11000) sont toutes conditionnées par `DAT_004c2b74`, que
seule la clé `nevada` de `float.cfg` met à 1: rotation et zoom au clavier sont donc inertes dans la configuration
fournie (fonctions de débogage), et ne sont pas à porter. `this+0x70` est l'échelle (16.16) des sprites des îles
d'index 4 et plus (`FUN_00471e66`); les îles 0 à 3 sont à l'échelle 1,0. Valeur initiale `0xc000` (75 %), écrite par
`FUN_00470259` (rapport de la section précédente).
Port: les îles d'index 4 et plus sont dessinées à l'échelle `0xc000` (`draw_sprite_scaled`), les zones de survol et de
clic restent à la taille native (bornes de `FUN_00405e11`). Inférence: la mise à l'échelle du blit natif applique le
même décalage de cadre que `draw_sprite_scaled`. Non vérifié à l'écran.

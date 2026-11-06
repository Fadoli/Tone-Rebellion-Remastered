# Budget de Tone du joueur

## Champ observé

Le panneau de diagnostic `FUN_00432c74` affiche `Tone: %d; Unused: %d` avec les dwords du record joueur aux offsets `+0x3c` et `+0x40` (`ev_a4dab9a9a897285f4f52a82dfde5629d13ae9e723a9f1ab6be1472817ab50011`; chaîne `ev_fb36d079d91b3175730d19a2325ab9d899abe1773f42bad775e3548b6aa18cc1`). L'arithmétique observée place les records joueurs à partir de `DAT_006191b8`, avec un pas `0x14a0`. Les offsets sont descriptifs, pas des noms d'origine. `+0x3c` vaut `(int)(sqrt(S) × 20.0)` où `S` est la somme des comptes de régions (voir correction ci-dessous).

## Calcul et modifications observés

`FUN_0045e6d3` est le seul écrivain identifié du champ joueur `+0x40` dans les corps examinés (`ev_40029ca226cb3025b370307705f49a00c27de614f0bce2bbaee8d6771a69c66c`). Il recalcule, pour un joueur demandé ou tous les joueurs (`param_1 == -1`), les contributions de chaque région et en fait une somme provisoire. Cette somme n'est pas la valeur finale de `+0x3c` : l'appel suivant à `FUN_00477599` la remplace par `10`.

**Correction (octets de FLOAT.EXE lus statiquement).** Le site d'appel `0x45e87f` est : `push 0x3fe00000; push 0; fild [eax+0x3c]; sub esp,8; fstp qword [esp]; call 0x477599; add esp,16; fmul qword [0x494780]; call __ftol`. Le `0.5` est donc poussé en premier (adresse haute) et la somme `S` en dernier. À l'entrée du wrapper, `[ESP+4]` = `S` et `[ESP+0xc]` = `0.5`. `FUN_00477599` contient le corps de la fonction CRT `pow` (`fyl2x`, test du mot de contrôle `0x27f`, branches NaN/inf) : c'est `pow(S, 0.5)` = `sqrt(S)`. Le résultat est multiplié par `20.0` (octets `00 00 00 00 00 00 34 40` à `0x494780`) puis tronqué par `__ftol`. L'ancienne lecture « `0.5 × 20.0 = 10` constant » était fausse (mauvais emplacement de pile). Contrainte indépendante : `+0x40 ≤ +0x3c`, donc un surplus de 16 observé en jeu exclut un plafond fixe de 10. `S` = somme des retours de `FUN_00462285` par île (nombre de sites classe 1 atteints, ou 10 si le champ joueur lu à `DAT_0061a654` est non nul). Interprétation : surplus initial 16 avec 4 ouvriers = `20 − 4` pour `S = 1`; non vérifié contre la valeur initiale réelle de `S` par monde.

Après cette écriture, la routine accumule les coûts des sites de classe 1 actifs, applique `coût × 17 / 20` si le bit `0x2000` du masque joueur est posé, ajoute le coût d'entretien des floaters de `FUN_0046562b(joueur, -1)`, plafonne cette somme à `+0x3c`, puis écrit :

```text
joueur.+0x40 = cap - min(dépenses calculées, cap)   # cap = +0x3c = (int)(sqrt(S)*20)
```

Le champ `+0x40` reçoit donc un remplacement complet lors du recalcul; aucun incrément/décrément direct du champ n'a été trouvé. La somme provisoire des régions n'influe pas sur le surplus dans le chemin observé, car elle est remplacée par 10 avant le calcul des dépenses. Les sites actifs, le masque de remise et les floaters peuvent changer le résultat indirectement. Le détail antérieur de la boucle reste utile pour ses accès région/site, mais son interprétation du total doit suivre cette correction.

## Lecteurs et déclencheurs

- `FUN_0045eaa7` lit `+0x40` comme seuil strict `> 4`, comparé aussi à la moitié de `+0x3c` (10 après le recalcul décrit ci-dessus), avant d'incrémenter le délai de demande de recruteur. Il ne modifie pas ces champs (`ev_d0241191e19be6e3ec7ab4c4a16172c22e772b518c82aeef201ad3125475226d`).
- `FUN_00432c74` lit les deux champs pour le texte de diagnostic; `FUN_00432b41` ne fait que sélectionner les messages « Tone cheat on/off » et n'écrit pas ce champ (`ev_eed8d36196f5e4a0135fe473cddbac4417754f26c0e2b0bf1707ffa212042bdc`). L'effet de ces messages seuls sur le budget n'est pas établi.
- Des changements d'activité de site appellent le recalcul `FUN_0045e6d3`; les notes [On/Off](island-onoff-control.md) consignent les branches observées. `FUN_004503bd` écrit aussi à l'offset `+0x40`, mais sur son record runtime d'objet Hall, de taille/contexte différent : ce n'est pas le champ budget du record joueur (`ev_4021833f01ea8cc7d3246c1f20291de57002d6bcb3a77b46a31138e8159b824c`).

Les références résolues au thunk de recalcul (`ev_e67d65ed33f5f275c0208aa2c8a14f0f29802235f4fba16bd75fe9bfb2582366`) donnent six appels directs examinés :

| Routine appelante | Événement qui lance le recalcul |
|---|---|
| `FUN_004503bd` | Après que le compteur local atteint 10, pose un bit `0x800 << param_3`, puis recalcule le joueur (`ev_5a45080167bb4fc859960ef437cd9f91a72e3ae258e14c2fc7d8d0de4df57687`). |
| `FUN_00453a5f` | Après changement du bit d'activité `+0x1c & 1`; appelle une routine distincte pour le propriétaire 4 (`ev_ed13893701a30da1a7dcca0f3b1e7ad88481ba168e841e628a874e0e0de09d11`). |
| `FUN_00462a87` | Après allocation et association d'un floater à l'île et au joueur, si le joueur n'est pas 4 (`ev_352feb8e600eceb96c53f7813bd012e104389976cd0dc42358a78b6a0fcddd24`). |
| `FUN_0046466f` | Pendant l'initialisation, après affectation de masques de visibilité; `param_1 == -1` recalcule tous les joueurs (`ev_79653791ae9981b3933636638f6be8a288fc707abda8b644c27a1d95327dd4`). |
| `FUN_00466c8b` | À l'appel, recalcule quatre fois le même joueur, puis appelle `FUN_00460460` (`ev_3b3bb651e4b1b353e7ecd34655ac9c44df84db809773c1c1e72cd654c836ebb2`). Le motif de quatre appels est observé; son besoin fonctionnel n'est pas déterminé. |
| `FUN_004672ef`, cas 10 | Après avoir éventuellement posé un bit de visibilité sur un site de classe 1, recalcule le joueur concerné (`ev_172a608b3e973e5da3943a31a5e23bd1bda5867c1da669038f74a156ca719da1`). |

Ces appels rafraîchissent `+0x40`; ils ne l'incrémentent pas eux-mêmes. Les coûts de sites actifs, les floaters comptés et le masque `0x2000` sont les entrées identifiées du calcul; la somme d'accessibilité des régions est écrasée par le chemin x87 décrit plus haut.

## Portée et incertitudes

La recherche de références Ghidra au début du tableau joueur (`DAT_006191b8`) a trouvé les points de code examinés dans `ev_f502c20a0313baa2845322d37062fb4be3c013ba1fbcc8fdea9938a22`; parmi leurs pseudocodes examinés, `FUN_0045e6d3` contient l'écriture joueur à `+0x40`. L'analyse ne prouve pas l'absence d'écrivains par alias, pointeur transmis ou référence indirecte non résolue. Le graphe des callers de l'entrée `0x45e6d3` est vide, mais les références au thunk `0x40102d` donnent les six sites listés ci-dessus. La portée est donc celle des références Ghidra résolues et des corps examinés, sans affirmation sur les appels indirects absents. Aucun comportement runtime n'a été observé.

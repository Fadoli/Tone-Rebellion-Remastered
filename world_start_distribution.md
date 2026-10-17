# Distribution des entités de départ — fonctions d’origine

Cette page relie la phase portée depuis `FUN_00464b9e` à ses helpers Ghidra. Les pseudocodes complets sont conservés dans `functions/0017_batch_0013.md`. Les descriptions distinguent les observations de Ghidra des interprétations; noms automatiques et types ne sont pas des déclarations source garanties.

## Chaîne de fonctions observée

| Fonction | Observation Ghidra | Rôle fonctionnel retenu |
|---|---|---|
| `FUN_004637fc` (`0x4637fc`) | Charge le monde et les îles, initialise plusieurs tableaux, puis appelle `FUN_0046466f` et `FUN_00464b9e`. | Orchestration du démarrage d'une partie. |
| `FUN_00461b3b` (`0x461b3b`) | Parse les lignes d'île; classe à `+4`, index d'île à `+8`, sous-type à `+0xC`, variante/état à `+0x10`; le tag `tone` devient classe 1. | Produit les enregistrements marqueurs consommés par la distribution. |
| `FUN_004500c4` (`0x4500c4`) | Initialise chaque record : propriétaire `+0x14 = -1`; met `+0x10` à zéro sauf la classe 3; efface/initialise plusieurs champs et drapeaux. | Convertit les records parsés en états runtime avant le choix des marqueurs et sites. |
| `FUN_00461859` (`0x461859`) | Appelle cette initialisation pour chaque record; collecte les liens incidents et records de classe 2, trie les liens par angle du voisin et les records par X; les records excédentaires passent en classe 0; les autres reçoivent l'index du voisin à `+0x36`. | Associe les emplacements de pont des fichiers d'île aux liens du monde et déclassifie les marqueurs de pont sans lien correspondant. |
| `FUN_00464b9e` (`0x464b9e`) | Parcourt au plus cinq records de classe 1 par île, choisit un ou deux marqueurs selon mode/indice, choisit un item via `FUN_004535e4`, puis appelle `FUN_00452859` avec propriétaire 4. Termine par `FUN_00460460(-1)`. | Sélectionne et initialise les items associés aux marqueurs. |
| `FUN_004535e4` (`0x4535e4`) | Utilise l'index d'île, le shape ID et les items déjà présents; deux tables de shorts restreignent les candidats aux IDs 6–9. Les candidats absents sont prioritaires; sinon tous les candidats permis sont réutilisés. | Choisit un ID d'item de table avec équilibrage local et le RNG du jeu. |
| `FUN_00452859` (`0x452859`) | Valide par `FUN_00452656`, écrit par `FUN_004528ca`, puis appelle des mises à jour d'état. | Crée l'item sur le record sélectionné si admissible. |
| `FUN_00452656` (`0x452656`) | Pour un ID non nul, classe 0 compare une valeur de `FUN_004641de` au champ de limite `+0xC`; classe 1 accepte. | Contrôle d'admissibilité lié à la classe du record. |
| `FUN_004528ca` (`0x4528ca`) | Écrit l'ID à `+0x10`, propriétaire à `+0x14`, initialise plusieurs champs et drapeaux, puis appelle des mises à jour. | Écriture en place de l'item et initialisation associée. |
| `FUN_004641de` (`0x4641de`) | Pour un joueur 0–3, ajoute `0x10 × joueur` à l'ID d'item de base avant de résoudre l'entrée `pad.txt`. | Résout les quatre halls initiaux : `0x2a`, `0x3a`, `0x4a`, `0x5a` correspondent aux entrées joueur 0–3. |
| `FUN_00467260` / `FUN_00474b90` | LCG 32 bits puis sortie 15 bits; `random15 * bound / 32768.0f`, conversion entière vers zéro. | Générateur pseudo-aléatoire partagé utilisé par la sélection. |

## Règles de `FUN_00464b9e`

- Une première boucle écrit `0x17`, `0x18`, `0x19` dans la liste d'emplacements indexée par la globale `DAT_006136b0`, propriétaire `4`, valeur `30000`. La ligne est tirée au hasard et le code recommence tant que classe et champ `+0x10` sont à zéro. Les champs du prédicat ne changent pas après cette écriture : le pseudocode/assemblage ne garantit donc pas trois lignes distinctes. Cette sous-phase n'est pas incluse au port actuel, car l'initialisation runtime de la globale et le rôle des IDs restent à relier.
- `FUN_00461859` appelle `FUN_004500c4` pour chaque record avant les placements : `+0x10` des classes 0/1/2 est remis à zéro, tandis que la classe 3 conserve la valeur parsée; le propriétaire `+0x14` devient `-1`. Le choix d'ID 6–9 ne doit pas compter les variantes brutes des lignes d'île pour les classes 0/1/2.
- Toujours dans `FUN_00461859`, les records de classe 2 sont triés par coordonnée X ascendante et les ponts incidents par angle de l'île voisine. Chaque record excédentaire est rétrogradé en classe 0; les records restants sont appariés un à un aux voisins triés et l'index du voisin est écrit dans le record runtime. Le comparateur de pont lit l'angle de l'autre extrémité (`FUN_00461768`). Le remake conserve ce voisin dans `GameRuntimeLocation.bridge_neighbor_island`; un index `-1` signifie qu'aucune association n'a été observée pour ce record.
- Dans la phase principale, `mode & 1` ajoute un deuxième marqueur aux quatre premières îles si plus d'un marqueur est disponible.
- Sur les quatre premières îles, le marqueur principal est le dernier de classe 1 aux indices pairs et le premier aux indices impairs. En mode alternatif, le second choisi est l'autre extrémité.
- Pour les îles à partir de l'index 4, un ordinal aléatoire est tiré parmi les cinq premiers marqueurs de classe 1.
- Les ajouts sont appliqués l'un après l'autre. Un ID posé sur un marqueur est donc visible dans les comptages effectués pour les marqueurs suivants de la même île.
- `FUN_004535e4` compare l'index d'île à `DAT_006136b0 - 1` pour autoriser les quatre IDs candidats. L'écriture initialisant cette globale n'est pas encore établie; le port expose donc l'indice d'accueil comme paramètre explicite au lieu d'inventer sa valeur.

## Tables utilisées par `FUN_004535e4`

Deux tables de 16 shorts à `0x4a28c8` et `0x4a28e8`, indexées par shape ID (0–15) :

```text
table A: 0, 1, -1, -1, 3, 2, 0, 2, 1, 1, 3, 3, 1, 2, -1, 0
table B: -1, 2, 3, 1, 3, 1, 0, 2, 0, 0, 2, 3, 0, -1, 0, 0
```

Les `-1` sont omis. Les autres valeurs 0–3 deviennent les IDs d'item 6–9. Pour une île ordinaire, un ID autorisé absent du champ record `+0x10` est préféré. Si tous les IDs autorisés existent déjà, le tirage revient à l'ensemble autorisé. Le rôle métier précis des catégories encodées par les IDs 6–9 n'est pas établi par cette fonction seule.

## Port C et limites

`ToneRebellion_Remake/src/core/game_start.c` fournit `game_start_distribute_tones`. Il prend les îles parsées, les shape IDs de la table monde, l'indice d'île d'accueil, le mode et l'état `ToneRng`; il retourne une liste ordonnée `(île, record, item ID, propriétaire)` sans muter les données source. Le comptage conserve les valeurs brutes de classe 3 et les placements précédents; les classes 0/1/2 ont été réinitialisées par `FUN_004500c4`. `game_start_tones_unit` couvre ces règles et les choix de marqueurs.

`ToneRebellion_Remake/src/core/game_session.c` rassemble une première structure mutable de partie. Il initialise les records comme `FUN_004500c4`, applique les pads/floaters issus de `game_start_assign_locations`, résout le hall runtime de chaque joueur comme `0x2a + 16 × joueur` via `FUN_004641de`, applique les placements de marqueur, met l'état `2` aux records de classe 2, puis reproduit les deux boucles classe 0 de `FUN_004637fc` : un site par entrée de pont avec valeur `+0x24 = 5`, puis deux sites par île sauf la dernière avec valeurs `6 + shape_id * 2` et `+1`. La vue Win32 dessine les halls avec les SHP listés dans `shapes.txt` et plages `BASE` du `bldinf.txt`, en utilisant la règle modulo de `FUN_0040aaeb`. `randomize_class0_assignment` expose le branchement de `DAT_0049c99c` sans lui donner de nom métier. Le test `test_island_corpus.exe` vérifie aussi l'initialisation d'un monde depuis le vrai `WORLDPOS.TXT` et les `ISLANDnn.TXT` locaux.

Les effets secondaires précis de `FUN_004528ca`, le recalcul de `FUN_00460460`, la première sous-phase `0x17`–`0x19`, l'initialisation de `DAT_006136b0` et les autres détails de simulation restent à analyser.

## Evidence REA

- `FUN_004500c4`: `ev_26fff5bcd9af63e50fab3f0e6120b8c6d139365c85a25a07557269008ee279a9`.
- `FUN_00461859`: `ev_60cc3b805a032ead183ce15cfa0965bb14b5d6c84b45414f6d11fbbb2eaca75b`; comparateur `FUN_00461768`: `ev_0e30ee9ad5fb8589ee58fce47a3a6e4ab0c72e76ca39b0836ffc9a6344f61862`.
- `FUN_00464b9e`: pseudocode `ev_af395cb5dc0ed1efd405d0c4880d5843648c434a49f9d811e53dccc4b1268377`; assemblage `ev_038b2943f7d5a4740ab39be3abfaf601533a2b50ae7c2135f46dd1eea6cbeaf5`.
- `FUN_004535e4`: `ev_9c1455ba552ca8516634a6b8919d421f5f1ab12d0184e0cbf893965eef0b22ba`.
- `FUN_00452859`: `ev_ebe214a1825dc422a3162a86d7bbb782029538e17a763d5d78e571c6fee5822d`.
- `FUN_00452656`: `ev_7a10ac57d0a8f9d1c6d94bfdba0ff8f19388f4df1e6f899c1c0e677dc4e4a147`.
- `FUN_004528ca`: `ev_48b4bcba9562b96d86e08e3898333b2848f2054141dcd10e2ad9becb516044e3`.
- `FUN_004641de`: `ev_f92b05e1bac76d2be3a91b76e6eb420474e1d04db600d49cc8d4a55edf30587d`.
- Tables à `0x4a28c8` / `0x4a28e8`: `ev_614008e78140c166d35cb4e7093dbfb71b9bca6ea7b05059d629a6c9d6a74f51` / `ev_75517bd4bd63d8f7b901ff08a88d5103b4ac6340e48e2a9556989d5651f72040`.

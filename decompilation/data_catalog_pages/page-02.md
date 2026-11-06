# Catalogue statique des fichiers et formats

## Correspondance des enregistrements Leviathan

Le bloc Leviathan actif de `floater.txt` contient neuf lignes ordonnées de `vspore` à `vnr`. L’allocateur `FUN_00466fe4` borne la catégorie 4 aux sous-types 9–17. Le parseur de `names.txt` charge 18 noms dans `xSpores`; l’affichage `FUN_0044338b` indexe deux noms par sous-type avec `(subtype - 9) * 2`, ce qui lie les neuf lignes aux IDs 9–17 et leurs paires de noms. Pour `vspore`, `FUN_0042219e` sélectionne un enregistrement-location de l’île; son chemin runtime peut changer son type `+0x14` en 4, déclencher un effet et supprimer le floater. `FUN_00460460` recompte ensuite les sites de type 4 par île et écrit des intervalles dans leurs champs `+0x45a`. **Observation gameplay de l’utilisateur :** les Vspore sont des constructeurs ennemis. Ils peuvent contaminer un emplacement de bassin pour produire une nouvelle source d’ennemis ou contaminer un emplacement de bâtiment afin d’y construire des bâtiments ennemis. Le binaire établit la sélection et conversion des emplacements, mais la correspondance entre ces deux fonctions et les valeurs brutes des champs d’emplacement reste à tracer. Les valeurs de stats par unité et le croisement avec les branches AI sont dans [l’analyse enemy AI](../behavior/enemy-ai.md#leviathan-subtype-table). Sources locales : `C:\git\ToneRebellion_Raw\original_content\floater.txt`, `names.txt`; preuves de l’allocateur `ev_fd05027dd8dfa2720031c58c1dfbd4ddc7a335d8b87ce01675e83b1b460a7991`, du parseur de noms `ev_d6c275efa826bd914507bd53c4c3f4d979737f6bb54430df661e8609724bd78d` et de l’affichage `ev_5f9c5a49a60617354d8ad7505c83964ab1f03b05faeb5ac50e17dde56b5c584a`.

---

# Catalogue statique des fichiers et formats

## Détails importants du parseur de texte

`FUN_00429c4b` appelle `FUN_0040f5b3(buffer, 1)` pour les en-têtes et les lignes de contenu. Si un identifiant n’est pas suivi par une ligne commençant par `END`, la lecture continue à ajouter des lignes. Le marqueur de fichier `ENDTEXT` est comparé sur 7 caractères. Le texte agrégé et l’identifiant sont enregistrés par `FUN_00429d5c`.

`FUN_0042f150` effectue ensuite des recherches de chaînes par clé ; il cherche 29 noms de contrôles/fenêtres `BC_OnOff...` dans une table de fenêtres, puis vérifie 21 chaînes générées. Plusieurs correspondances renvoient vers `gamey.txt`; cette fonction établit un lien fonctionnel entre les objets de fenêtres et les textes chargés, mais pas une correspondance exhaustive entre chaque clé et chaque fichier.

---

# Catalogue statique des fichiers et formats

## Schéma partiel des enregistrements d’effets

Le parseur `FUN_004153b8` accepte jusqu’à 96 records `EFFECT`. Les chaînes et branches Ghidra établissent les champs suivants sans reconstruire la structure mémoire complète :

| Tag | Arguments/formes visibles | Traitement observé |
|---|---|---|
| `EFFECT` | deux tokens (`%s %s`) | Débute un record et y stocke son nom ; initialise des champs de type/vitesse/son à des valeurs par défaut. |
| `TYPE` | une valeur texte | Enum : `ONESHOT=0`, `BULLET=1`, `LIGHTNING=2`, `IMPACT=3`, `CAST=4`, `SPECIAL=5`, `SOUNDONLY=6`. |
| `REALM` | une valeur texte | Enum : `PHY=0`, `SUP=1`, `ETH=2`, `NAT=3`. |
| `SHAPE` | un identifiant texte | Recherche l’identifiant dans la table de formes ; journalise/échoue si absent. |
| `SPEED` | un entier (`%s %d`) | Converti puis stocké dans un champ 16 bits. |
| `SOUND` | un identifiant texte | Lorsque l’audio est activé, recherche l’identifiant sonore et le stocke ; échec si absent. |
| `LEVELFRAMES` | nombre suivi de paires entières, format observé `"%s %d %d,%d %d,%d %d,%d %d,%d"` | Exige au moins quatre conversions et limite le nombre de segments à 4. Stocke les bornes des segments avec ajustement `-1`. |
| `CHAIN` | identifiant texte | Conservé en attente puis résolu via un helper après le parsing des records. |

Le parseur initialise certains indices à `0xffff` quand ils restent absents. Les enregistrements sont délimités par l’apparition du prochain `EFFECT`, selon le traitement des lignes visible dans le pseudocode. L’appartenance de cette entrée au fichier `effects.txt` reste une attribution à confirmer au call-site.

Une lecture de données Ghidra à `0x49be80` a révélé les chaînes `TYPE`, `CAST`, `PHY`, `SUP`, `ETH` et `NAT`, qui n’étaient pas toutes définies comme chaînes individuelles dans l’inventaire initial. Evidence : `ev_7dfb26f9c9ef233774c5281b8d6c98964c45d378c4dabe0e36f189713717924f`.

---

# Catalogue statique des fichiers et formats

## Records de shape-info

`FUN_00455833` lit un mot de commande par ligne puis valide les arguments selon le format `FUN_00472f10`. Les motifs ci-dessous sont les formats observés dans les branches du parseur, avec le premier token représentant le tag. Les noms de champs métier ne sont pas récupérés : les nombres/chaînes restent des positions.

| Tag | Format d’arguments Ghidra | Observations |
|---|---|---|
| `ITEM` | `%s` | Incrémente le compteur d’items et initialise le bloc courant. |
| `SHAPE` | `%s %s` | Associe une paire de chaînes au bloc courant. |
| `BASE` | `%s %d %d %d` | Enregistre une ligne numérique liée aux bases ; le parseur vérifie au moins 3 conversions. |
| `CHUG` | `%s %d %d %d %c` | Enregistre une ligne de 3 entiers et un caractère. |
| `GLYP` | `%s %d %d` | Enregistre deux valeurs numériques. |
| `INCI` | `%s %d %d %d %c %d` | Enregistre trois valeurs, un caractère et un entier. |
| `CONS` | `%s %d %d %d %c %d %d,%d` | Enregistre plusieurs valeurs numériques, un caractère et une paire finale. |
| `PROD` | `%s %d %d %d %c %d %d %d,%d %s` | Enregistre valeurs, caractère, paire et chaîne finale ; le parseur demande au moins 9 conversions. |
| `OCCU` | `%s %d %d %d,%d` | Enregistre deux entiers suivis d’une paire. |
| `BARG` | `%s %d %d` | Enregistre deux valeurs numériques. |
| `END` | `%s` | Tag de fin reconnu par les chaînes et les branches du parseur. |

Les limites nommées dans le code couvrent `MAX_BLDSHP_ITEMS`, `MAX_BARG_ANM`, `MAX_BASE_ANM`, `MAX_CHUG_ANM`, `MAX_CONS_ANM`, `MAX_GLYP_ANM`, `MAX_INCI_ANM`, `MAX_OCCU_ANM` et `MAX_PROD_ANM`. Les valeurs numériques de ces constantes ne sont pas établies par ces chaînes.

`FUN_00454d1f` traite séparément une table plafonnée à 64 entrées (`0x3f` avant insertion) et des identifiants tels que `hover`, `pickup`, `carry`, `attack`, `atteff`, `graspxy`, `attxy`. Cela paraît décrire des actions/animations de flotteurs, mais les champs ne sont pas renommés dans Ghidra et cette sémantique reste une interprétation.

Une lecture de données à `0x4a2e10` a confirmé les tags et formats `ITEM` à `BARG`, ainsi que les limites textuelles ci-dessus. Evidence : `ev_8e3daac3c7a9e37924fe5cacc8805796a6855ceafdb5cb3ae47e518811831864`.

---

# Catalogue statique des fichiers et formats

## Sources Ghidra

- [Démarrage et fichiers de texte](../functions/0002_application_main.md), `ev_4447fdd9631929efaeb1d177248260afbbd55aec3775ce0996e1f9b427cb4e7f`.
- [Lecteur de texte à clés](../functions/0011_batch_0007.md#fun_00429c4b--0x429c4b), `ev_b04b7d1efd83a3e7d49ab7ce32bdae2bdc89bee29051ec02d0a1f76ab342b224` ; [stockage partagé](../functions/0011_batch_0007.md#fun_00429d5c--0x429d5c), `ev_fe2d04de71105903ee26e44b7d85f686a4b05bf73a5a407f1e66a1fe0450cfef`.
- [Lecteur commun](../functions/0008_batch_0004.md#fun_0040f419--0x40f419), `ev_f2aaf6dc9f43acefcf3cfa30722df6d60c3f30d302c321fa1ac8258d2174a0a7` ; [lignes/commentaires](../functions/0008_batch_0004.md#fun_0040f5b3--0x40f5b3), `ev_9a43dae9087123005e9f536b7788da9b702d57a3b6b013e2b713164b23dab33f`.
- [Configuration](../functions/0010_batch_0006.md#fun_0041d19d--0x41d19d), `ev_a4d00f397b10ddd5f9e8450e88d33825e40a624c6b54a2e49736d00567ca318c` ; [registre](../functions/0010_batch_0006.md#fun_0041d64e--0x41d64e), `ev_187d22e0d18c68faf0861e12bda0956428befb83a667937aa0ced1976eed0ea5` ; [noms](../functions/0010_batch_0006.md#fun_0041d70d--0x41d70d), `ev_b765d704b9b04a47f1cc07ea19409dcd140e8aadd2232363e5685731bec68576`.
- [Lookup de texte/fenêtre](../functions/0012_batch_0008.md#fun_0042f150--0x42f150), `ev_fd688883d1298751b7b836f120b2f943abe1617bc91b1afc0b81c8323578cacf`.
- [Fenêtres et formes](../functions/0018_batch_0014.md#fun_0046cd22--0x46cd22), `ev_fbdcb9f3b27de341d258e85d68d67d6f9dbe6fb0971f77f99f80d7c8484fa98c`.
- [Effets](../functions/0009_batch_0005.md#fun_004153b8--0x4153b8), `ev_a2f6dd8fe47f403c98165ec901d7fc9dac3fe46367845bddaa51759bdfbdbec6`.
- [Shape-info, première passe](../functions/0016_batch_0012.md#fun_00454d1f--0x454d1f), `ev_6ccf11adf4100a01f329d47d35c0c8bd1d7e5c6fcff4d70ee2a0c846e156a876` ; [records SHAPE](../functions/0016_batch_0012.md#fun_00455833--0x455833), `ev_5d60033e6cc433f212a51343e2761e910c21c813cc1727a5c0375a566c73d999`.
- [Tables monde](../functions/0017_batch_0013.md#fun_004642a3--0x4642a3), `ev_561df3c3edee5a21c16764f7b95d5fa1e14e3a19d3ca83157c30bd51568c31c9`.
- [Sentinelle `END`](../evidence/manifest.md), `read_bytes` Evidence `ev_d64c24d6ebe5f8bcb691202a6d7fad642a6264e07b2bc78e83ce1c39bc21ec8f`.

---

# Catalogue statique des fichiers et formats

## Suite de l’analyse

1. Relier les clés de `float.cfg` aux branches d’initialisation et aux effets observables statiquement, sans traiter les noms d’options comme une preuve de comportement runtime.
2. Déterminer les rôles des champs numériques de `fltinf.txt` et `bldinf.txt` à partir des usages en aval et des tables d’objets qui les consomment.
3. Étudier les parseurs de `pad.txt`, `floater.txt`, `spells.txt`, `windows.txt` et `shapeinf.txt`, puis rattacher chaque format au call-site exact. Comparer les formats reconstruits aux fichiers présents localement.

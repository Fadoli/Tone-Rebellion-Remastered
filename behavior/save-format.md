# Format de sauvegarde natif (`NN.SAV`)

Sources: pseudocode `FUN_0045749a` (écriture), `FUN_004576c7` (lecture), `FUN_00412d0a`, `FUN_00467be5`, `FUN_00418a17`, `FUN_0046ea1c`, `FUN_00462c55`, `FUN_00453d36`, `FUN_00460334`, `FUN_00460c83`, `FUN_004252fa` (`functions/`, Evidence ID dans chaque entrée). Échantillons: 8 sauvegardes réelles, dont 6 de 149 806 octets (15 îles) et 2 de 98 382 octets (7 îles).

Emplacement: Windows redirige `C:\Program Files\Tone\*.SAV` vers `%LOCALAPPDATA%\VirtualStore\Program Files\Tone\`. Les fichiers du vrai dossier font 1 octet (placeholders de l'ISO); les vraies sauvegardes ne sont visibles que par un processus virtualisé (le remake l'est) ou par ce chemin.

## Observation: tout est brut, petit-boutiste, sans compression
Les primitives d'E/S sont `FUN_0040fd80` (écrit N octets), `FUN_0040fc15` (lit N octets), `FUN_0040fdab`/`FUN_004199c0` (un dword). Le fichier est donc un vidage d'enregistrements, dans l'ordre d'appel de `FUN_0045749a`:

| Offset | Taille | Contenu |
|---|---|---|
| 0x00 | 0x80 | En-tête: `"1.16E"` (le jeu écrit `"1.16F"` d'après `0x4a3470`; les échantillons portent `E`), `+0x1c` tribu, `+0x30/32/34` stocks, `+0x68` surplus, `+0x6c` pop, `+0x70` ouvriers, `+0x74/+0x78` `DAT_004bf118/1c`, `+0x7c = 0x378b8` (`FUN_00457490`) |
| 0x80 | 12 | `DAT_0062d174`, `DAT_0049f538` (tribu courante), `DAT_0049f53c` |
| 0x8c | 0x148 | flux 1 (`FUN_00412d0a`): bloc `DAT_004befe0` |
| | 60 | flux 2 (`FUN_00467be5`): 15 dwords, d'où `[monde+0x27498]` = nombre d'îles (mot bas du premier dword) |
| | 0x500, 0x100, 0x100, 0x1e×3 | blobs `+0x2c1a4`, `+0x2749c`, `+0x2cc40`, `+0x2cd42/60/7e` |
| | par île | `FUN_00462c55`: 4 dwords (`+0x29a8` nombre de sites, `+0x29cc`, `+0x29d0`, `+0x29e0`) puis 8 + 0x400 + 0x20 + 0x10 + 0x10 + 0xc octets, puis `n` × 0x60 octets (`FUN_00453d36`: enregistrements de site) |
| | 4 × 0x14a0 | enregistrements joueur (`FUN_00460334`) |
| | 0x1614 | bloc global (`FUN_00460c83`) |
| | 0x100 × 0x4c | tableau des floaters (`FUN_004252fa`) |
| | 4 + 0x280 | flux 3 (`FUN_00418a17`): dword `+0x1482` puis 0x280 octets `+0x1202` |
| fin | variable | flux 4 (`FUN_0046ea1c`): objets 1..0x299 de la table `0x...+n*0xc`, sérialiseur virtuel `vtable+0x10`; 48 octets sur les échantillons |

## Vérification (statique, sur les échantillons)
En parcourant ce plan avec les compteurs lus dans le fichier (îles = mot bas du premier dword du flux 2, sites par île = short à l'en-tête d'île), le curseur après le flux 3 laisse exactement 48 octets pour le flux 4 sur 00/01/03: 15 îles / 871 sites (149 806 octets) et 7 îles / 429 sites (98 382 octets). Cohérent avec les tailles réelles; cela valide le cadrage, pas la signification des champs.

## Inconnues
- Contenu des blobs (0x500, 0x100, 0x400, …), du flux 1 et des 48 octets du flux 4 (classe d'objet et champs non tracés).
- `09.sav` (`"1.16F"`, 49 282 octets, 0 île d'après ce cadrage) n'a pas le même plan: probablement une sauvegarde d'un autre mode; non analysée.
- Correspondance champ à champ avec `GameSession` (le remake modélise déjà les offsets des enregistrements 0x60 et 0x4c, mais pas les blobs).

## Port: chargement natif (première tranche)
`ToneRebellion_Remake/src/core/native_save.c`: les 8 échantillons passent `native_save_parse` (monde déduit du nombre d'îles: 7, 11 ou 15; tribu = dword `0x84`). Le troisième dword (`0x88`, `DAT_0049f53c`) vaut 0..14 selon la sauvegarde: ce n'est pas la difficulté. L'écran Charger construit une session neuve pour ce monde et cette tribu, puis `native_save_apply` y superpose:
- **sites (0x60)**: `+0x08/0x0a/0x10/0x14/0x18/0x1c/0x22/0x24`, stocks du Hall (`+0x28/2a/2c`), `+0x30..+0x4a`. L'identifiant `+0x10` est converti en identifiant propre au joueur (+16·joueur), comme `game_session_base_item_id`. Les Halls des joueurs sont retrouvés par balayage.
- **floaters (0x4c)**: propriétaire (`+0`, -1 = libre), sous-type, île, position, graine d'animation, ressource portée, drapeaux, compteur de charge, minuterie. Les points de vie ne sont pas décodés: ils reprennent le maximum du catalogue.
**Non porté (état perdu au chargement):** lien bâtiment/tâche/ordre des floaters (ils repartent en errance), enregistrements joueur 0x14a0 (dont les 48 lignes source de 100 octets), bloc global 0x1614, tâches et événements en attente, blobs du flux 2, flux 1, flux 4. Non vérifié en jeu (l'exécutable en cours d'exécution bloquait l'édition de liens).

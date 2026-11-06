# Carte comportementale statique — première passe

## Création d'une partie et placements initiaux

### Observations Ghidra

- Le dispatch `FUN_004121b7` reçoit les commandes de configuration : type `7` stocke l'indice de taille du monde et type `8` stocke la difficulté. Le type `9` marque la partie démarrée, calcule deux paramètres de génération, appelle `FUN_004637fc` puis ouvre `WORLDVIEW`.
- `FUN_004637fc` sélectionne une table parmi les mondes chargés par `FUN_004642a3`, charge les îles via `FUN_00461b3b`/`FUN_00461859`, réinitialise plusieurs tableaux et appelle `FUN_0046466f` puis `FUN_00464b9e`. Ensuite, les records de classe 2 reçoivent la valeur d'état `2`; la routine distribue aussi des valeurs/liaisons dans des records de classe 0 encore libres. Les noms métier de plusieurs champs et de cette dernière distribution restent inconnus.
- `FUN_00461859`, exécutée après parsing d'une île, copie les trois paramètres de monde associés à l'île, réinitialise plusieurs états de caméra/record via `FUN_004500c4`, rassemble les ponts du monde incidents à cette île et les records de classe 2, puis trie les deux listes avant leur association. Les records de classe 2 excédentaires sont ramenés à la classe 0. Le tri des ponts utilise `FUN_00461768`; le tri des emplacements utilise `FUN_00461831`.
- `FUN_004500c4` met le propriétaire du record à `-1`, efface de nombreux champs runtime, et remet le champ `+0x10` à zéro sauf pour la classe 3. Ceci explique pourquoi les variantes parsées des classes 0/1/2 ne doivent pas être traitées comme des items déjà placés par `FUN_004535e4`.
- `FUN_00461768` compare deux ponts incidents : il trouve pour chacun l'extrémité autre que celle partagée avec l'autre pont, lit les angles de ces extrémités dans la table monde `0x5ebd78`, soustrait les angles et convertit le résultat flottant en entier via `__ftol`. **Interprétation :** ceci ordonne les voisins autour de l'île par angle; la comparaison ne normalise pas explicitement le passage de l'angle zéro.
- `FUN_00461831` compare le premier `short` de deux records de localisation pointés; dans ce contexte les records sont de classe 2 et le champ est leur coordonnée X. Il les trie donc par X croissant.
- `FUN_00467260` obtient le prochain entier 15 bits auprès de `FUN_00474b90`, multiplie par la borne entière, divise par `32768.0f` (constante lue à `0x494798`, octets `00 00 00 47`) et convertit vers zéro par `__ftol`. **Port correspondant :** `ToneRebellion_Remake/src/core/tone_rng.c`; le même générateur alimente maintenant les effets aléatoires du menu.
- `FUN_0046466f` traite quatre slots de joueur. En mode sans bit 0, chaque slot choisit l'île du même indice; les slots pairs marquent le premier record de classe 1 (`tone`) et les slots impairs le quatrième. Le mode alternatif choisit `alternate_island + (slot & 1)` et un ordinal `slot / 2 + 1`.
- `FUN_00464b9e` choisit jusqu'aux cinq premiers marqueurs `tone` de chaque île. Pour les indices 0–3, le principal alterne dernier/premier selon la parité; le bit 0 du mode ajoute l'autre extrémité. Les îles suivantes tirent un marqueur au hasard. `FUN_004535e4` choisit un ID 6–9 selon deux tables indexées par shape ID et les items déjà présents; `FUN_00452859` valide puis `FUN_004528ca` écrit l'ID et le propriétaire. La globale `DAT_006136b0` fixe l'île d'accueil spéciale, mais sa valeur runtime demeure à résoudre. Détails: [distribution des entités de départ](../world_start_distribution.md).
- `FUN_00461b3b` compare `pad` à `0x4a4c10` et le classe 0; `tone` à `0x4a4c2c` et le classe 1. Les octets lus par REA à `0x4a4c00` donnent la suite `%d %d %d %s %d\0\0pad\0smpad\0...tone\0\0bridge\0...` (Evidence `ev_346f0482a3c7a5c0cd1c1c4320ec28be7e3b278647786754331652a5a8e798c3`). Ainsi les quatre premiers fichiers du petit monde, qui ont chacun quatre entrées `tone`, fournissent les marqueurs de classe 1 attendus par `FUN_0046466f`.
- À partir du marqueur, `FUN_0046466f` choisit le premier record de classe 0 avec le champ au décalage `+0x10` égal à zéro à distance minimale. `FUN_004672a6` définit cette distance comme `max(abs(dx), abs(dy))`. L'ordre des lignes tranche les égalités. Le code calcule ensuite les bords de caméra horizontaux, crée le pad d'ID `0x2a` à cet emplacement, puis appelle quatre fois `FUN_00462a87` avec le type-index du joueur et la position du marqueur.
- `FUN_00462a87` valide un type-index floater (`0..4`), instancie un objet et initialise sa position/état. `FUN_00452859(0x2a, slot)` crée le pad correspondant; l'ID de ligne 42 dans `pad.txt` décrit `p-hall`/`GREATHALL`, et `FUN_004641de` sélectionne le bloc de 16 items de chaque joueur.

### Portée dans le remake

`ToneRebellion_Remake/src/core/game_start.c` reproduit les sélections d'îles/sites, la règle de distance, le hall `0x2a`, les quatre floaters et les marqueurs/items 6–9. `game_session.c` applique ces résultats à un état runtime mutable, marque les records classe 2 et porte les deux boucles classe 0 de `FUN_004637fc`. Cette initialisation de cœur n'est pas encore branchée à la fenêtre Win32; les interactions/simulation et la sous-phase des IDs `0x17`–`0x19` restent à porter.

---

# Carte comportementale statique — première passe

## Évidence et dossiers sources

| Sujet | Adresse(s) | Evidence ID(s) | Dossier |
|---|---|---|---|
| Entrée applicative | `0x41d8e1` | `ev_4447fdd9631929efaeb1d177248260afbbd55aec3775ce0996e1f9b427cb4e7f` | [application main](../functions/0002_application_main.md) |
| Création de fenêtre | `0x41c1d6` | `ev_b6c592d2020a3b072f7d397ada43d048a75789229d848e76ffadec2a536491cf` | [window init](../functions/0003_window_init.md) |
| Boucle principale | `0x41c46f` | `ev_a3a1136454b116409a3a18908d27e23488bf809cdcb8d28b4d4d0805f05688e3` | [main loop](../functions/0004_main_loop.md) |
| Fenêtres et formes | `0x46cd22` | `ev_fbdcb9f3b27de341d258e85d68d67d6f9dbe6fb0971f77f99f80d7c8484fa98c` | [window manager initialization](../functions/0018_batch_0014.md#fun_0046cd22--0x46cd22) |
| Callback Win32 et fermeture | `0x4020d6 → 0x41bdae → 0x41cf86` | `ev_f59847072eb309e1dd70ee6e13ae354930572914ab05c815aa8a8bd2d573198c`; `ev_4c453f8245e9d1316205dd4285ed187d01ba61dc33a4d464394dc61400095283`; `ev_a96a976ad9c33472b4ef2263c63b0eb7fc71e68f3c288de3c2d861de035fa03b` | [window procedure](../functions/0010_batch_0006.md#fun_0041bdae--0x41bdae), [quit request](../functions/0010_batch_0006.md#fun_0041cf86--0x41cf86) |
| Pump de messages | `0x41be0f`, `0x42ef17` | `ev_29ad09d456ae628d3158564a8c1dab7a234851e959fde7b086429c419b386514`; `ev_84932651de367bf515bdf073e6673f51992e52b524f7c4d9a416ce8b8a101e83` | [message processing](../functions/0010_batch_0006.md#fun_0041be0f--0x41be0f), [loop dispatch](../functions/0012_batch_0008.md#fun_0042ef17--0x42ef17) |
| File d’événements | `0x42eba0`, `0x42ee48`, `0x469f56` | `ev_4539fa61c9afdfc26f53f63f89c1eeee1db31de6684e55bec209ac2cf5d040ee`; `ev_b1eef3a6b252c5fa1733dbfcf82a66aff0128de7f09b851e71e222f58035aff9`; `ev_3b7d1c7373d2274d945cf5579c6d5b74b907c2a1517b6587e6a2c23a92bec22e` | [input queue](../functions/0012_batch_0008.md#fun_0042eba0--0x42eba0), [window events](../functions/0018_batch_0014.md#fun_00469f56--0x469f56) |
| Update et rendu | `0x466ce2`, `0x42cc24`, `0x46bdee` | `ev_b51f2311ff9bd9ad209f0663ea00bfe330e7ff0eff117e8a273292d3112a4e0e`; `ev_29e8acc9ef214546bdb7036b2cbf1e88ffe8105275d37ccc324960fffcdd8da8`; `ev_fa0207968e95f1464cc1c397bc1d8b28d8ffed8238efbbe7a0daf79f16598254` | [update loop](../functions/0017_batch_0013.md#fun_00466ce2--0x466ce2), [graphics presentation](../functions/0011_batch_0007.md#fun_0042cc24--0x42cc24), [window callback fanout](../functions/0018_batch_0014.md#fun_0046bdee--0x46bdee) |
| New game and world setup | `0x4121b7`, `0x4637fc`, `0x461859`, `0x46466f`, `0x4672a6`, `0x462a87`, `0x452859` | `ev_436ec675045ff47701ee7511eba972fb3eac9f707eccb9322fefc66d4be20300`; `ev_96a46390b086f06a56b3c395f6e1a9de7ba2c2a1c30396c7ca72c63944a1039e`; `ev_60cc3b805a032ead183ce15cfa0965bb14b5d6c84b45414f6d11fbbb2eaca75b`; `ev_ac313cb8cc73f9c102676395cd14cb97b5b1f9355d074df1e6656ce028d2d36f`; `ev_d6e45300f5ee5de4ed13ebfa3da2e5198981b6af36bc072d956c795033a50243`; `ev_352feb8e600eceb96c53f7813bd012e104389976cd0dc42358a78b6a0fcddd24`; `ev_a571ddb810f57eb82ddb7110d751957927677498282088ff2bc3d5256611b345` | [function guide](../FUNCTION_GUIDE.md#démarrage-dune-partie-et-placement-initial), [command dispatcher](../functions/0009_batch_0005.md#fun_004121b7--0x4121b7), [world setup pseudocode](../functions/0017_batch_0013.md#fun_004637fc--0x4637fc) |
| Association des ponts d'une île | `0x461859`, `0x461768`, `0x461831`, `0x4777a0`, `0x472c6c` | `ev_60cc3b805a032ead183ce15cfa0965bb14b5d6c84b45414f6d11fbbb2eaca75b`; `ev_0e30ee9ad5fb8589ee58fce47a3a6e4ab0c72e76ca39b0836ffc9a6344f61862`; `ev_b2c053a4bd63d8f7ce191f425358685b35f763313fce9b221df727eef5c30a41`; `ev_a0793f5d9552f14a7accb48cbf992564af87d834ce8fe8c91da7a4cfbdd76ad1` | [bridge matching and comparators](../FUNCTION_GUIDE.md#démarrage-dune-partie-et-placement-initial), [bridge setup](../functions/0017_batch_0013.md#fun_00461859--0x461859) |

---

# Carte comportementale statique — première passe

## Prochaines pistes

1. Comparer les parsers aux fichiers présents dans `C:\git\ToneRebellion_Raw\original_content`; les formats de `worldpos.txt`, `pad.txt`, `floater.txt` et `spells.txt` sont maintenant rattachés aux appels/parseurs dans `remake_spec.md`.
2. Relier les codes de la file d’événements aux gestionnaires de fenêtres/classe qui les consomment, y compris les appels indirects.
3. Cartographier les objets manipulés par `FUN_00413e8a` / `FUN_00466ce2` et distinguer simulation, animation, audio et rafraîchissement d’interface.
4. Poursuivre l’initialisation audio à partir du test `sound.txt`/`DXSOUND` et des interfaces appelées conditionnellement.

---

# Carte comportementale statique — première passe

## Limites

- Aucun fichier `Float.pdb` n’est disponible ; les noms de méthodes et structures restent principalement automatiques.
- Les fichiers de données sont disponibles dans le corpus local et les 483 membres des COB concordent avec leurs copies extraites. Plusieurs tables sont décrites dans `data_catalog.md` et `remake_spec.md`; d’autres parsers et relations aux écrans restent à analyser.
- Les appels virtuels/indirects, les variables globales et les appels calculés peuvent cacher des relations non montrées dans le graphe direct.
- Les données locales sont désormais analysées pour `worldpos.txt`, `pad.txt`, `floater.txt` et `spells.txt`; leurs limites connues et le premier vertical slice du remake figurent dans `remake_spec.md`.
- Aucune exécution du programme n’a été faite ; cette carte décrit le flux statique observé dans Ghidra.

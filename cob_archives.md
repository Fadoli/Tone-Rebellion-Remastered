# Archives de données COB

## Sources locales et intégrité

Les archives se trouvent à côté de la cible, sous `C:\Program Files\Tone\` :

| Fichier | Taille | SHA-256 | Membres |
|---|---:|---|---:|
| `TONE00.COB` | 156 212 octets | `362257b33c4d6b6e3c95208f6e45a1734aeadc2d21898a7f1055476c521bae5b` | 21 |
| `TONE01.COB` | 26 927 860 octets | `ba15e43c3d5b9156594a6fab166c76749c5953dfecc39ffaa568271f7100a64f` | 462 |

`C:\Program Files\Tone\COB.CFG` contient les deux noms `tone00.cob` et `tone01.cob`, chacun sur sa ligne. Les membres extraits sont présents dans `C:\git\ToneRebellion_Raw\original_content`. Une comparaison locale de chaque membre a vérifié le nom, la longueur et le SHA-256 : 21/21 pour `TONE00.COB`, 462/462 pour `TONE01.COB`, soit 483 correspondances et aucun écart. Le détail reproductible est consigné ligne par ligne dans [archive_index.jsonl](archive_index.jsonl).

Les fichiers originaux ont été lus pour calculer leurs empreintes et analyser leurs tables ; ils n’ont pas été modifiés ni exécutés. Le corpus local fourni est la source de travail. Conformément à la demande, ne pas utiliser GitHub ni télécharger à nouveau les fichiers.

## Structure observée sur disque

L’inspection statique des octets des deux archives montre la disposition suivante :

1. Un entier little-endian de 4 octets indiquant le nombre de membres (`21` ou `462`).
2. Une table de `count × 50` octets contenant les noms de membres, encodés en chaînes terminées par NUL et complétées dans le champ fixe.
3. Une table de `count × 4` octets d’offsets little-endian, un offset par nom.
4. Les contenus des membres dans l’ordre des offsets. La longueur d’un membre est la différence avec l’offset suivant ; le dernier se termine à la fin de l’archive.

La fin des deux tables et le début de la zone de données sont à l’offset `0x472` dans `TONE00.COB` et `0x6178` dans `TONE01.COB`. Les offsets observés sont croissants, dans les limites des fichiers, et la dernière entrée de chaque archive s’achève à sa fin. Les premiers membres sont `bldinf.txt` et `data\\acast.shp`; les derniers sont `windows.txt` et `data\\worldpos.txt`, respectivement.

Cette description provient de la lecture des octets et de la concordance de tous les contenus extraits. Le pseudocode Ghidra confirme indépendamment les champs de table utilisés par le chargeur.

## Code de chargement observé dans Ghidra

- `FUN_00410105` lit `cob.cfg` et parcourt ses lignes. Evidence `ev_3d928c3e3c20204be08e14067bfa575cbc3d1a9fe24a546b56dfe0d283c1483b`.
- `FUN_0040ff5b` ouvre les archives indiquées, lit le compteur, puis réserve/lit `count × 50` octets de noms et `count × 4` octets d’offsets. Le code vérifie un maximum de 5 archives et un maximum total de 500 membres. Evidence `ev_78147898fdd67751ac4b9dc7f61c638b16c2a36dd616080db86817b146a0965a`.
- `cob.cfg` est ouvert via le helper `FUN_00474b00`, dont le chemin passe par `FUN_00474a10` en mode `0x40`. Evidence `ev_dbed377a96c46e7249eb471314289a7bc5e14e413dae2d53c986f75f10265626`.
- `FUN_00474190` est un helper de lecture de fichier du runtime ; son pseudocode n’est pas à lui seul une preuve de format COB. Evidence `ev_87da4088d973d81a945f8e3e9d68ea79ba722b3a0ebeefcfa1504b0232847a05`.
- La chaîne `cob.cfg` est référencée depuis `0x410113`; l’appel correspondant entre dans `FUN_00410105`. Ces liens et pseudocodes sont conservés dans le manifeste et l’index de procédures.

## Inventaire et prochaines analyses

`archive_index.jsonl` contient une entrée par membre : archive et empreinte de l’archive, index, nom, offset, longueur, empreinte du contenu, chemin extrait local, empreinte extraite et résultat de comparaison. Les fichiers du corpus peuvent donc servir directement à lire les formats texte et inspecter les assets, tout en gardant la provenance vers les octets archivés.

La correspondance du conteneur avec le corpus extrait ne donne pas automatiquement la grammaire des formats. Rattacher chaque fichier à son chargeur/parseur à l’aide des appels et références Ghidra. `shapeinf.txt`, par exemple, est présent localement et expose les directives `shape`, `frame` et `offset`, mais le call-site qui le consomme reste à identifier. Les associations et interprétations documentées figurent dans [data_catalog.md](data_catalog.md).

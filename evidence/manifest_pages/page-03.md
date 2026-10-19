# Registre d’évidence REA

| Opération | Evidence ID | Résumé | Couverture / remarque |
|---|---|---|---|
| `procedure_pseudo_code` | `ev_d72eed96013f16e8cecbd5772c71935e76feec78b9df2e8af58ccce46c4ada4e` | `FUN_00441d3e` | L'événement 6 d'IWLocInfo valide une source avant `0x48`, ou envoie `0x4a` si un grab est actif. |
| `procedure_references` | `ev_0fb01505c0a7e326de1d7e85aa13d4df42a1c47415115b384c04cc90f31f9a6d` | thunk `FUN_0045f337` | Six appels résolus depuis les handlers d'île/IWLocInfo et les chemins grab/place; couverture directe des références entrantes. |
| `procedure_pseudo_code` | `ev_29c00108fecaae10e34c3acd2f038be290b324679da3c2aa13b3a70825e8b4ae` | `FUN_0045f5c5` | Fin du grab : valide le site destination, gère la pose au Hall/retour à l'origine et efface l'état actif en cas de succès. |
| `procedure_assembly` | `ev_ded193af75b4663591b54cea28c51d70b7d2a0d987a2d7b891ee6f7cacdc8963` | `FUN_0045f5c5` | Confirme les conventions du helper de pose : cible en `ECX`, site source mémorisé en argument. |
| `procedure_pseudo_code` | `ev_46b3b31c81eecb2bc50884c4458f57e4c8020d7001de0c3ae0260c3a1b1d9185` | `FUN_0045343b` | Un site cible libre de type 0 ou 1 reçoit l'ID/propriétaire et plusieurs champs de la source. |
| `analyze_function` | `ev_5d60033e6cc433f212a51343e2761e910c21c813cc1727a5c0375a566c73d999` | `FUN_00455833` | Parseur de records `SHAPE` et données associées. |
| `analyze_function` | `ev_561df3c3edee5a21c16764f7b95d5fa1e14e3a19d3ca83157c30bd51568c31c9` | `FUN_004642a3` | Parseur de tables monde/îles/positions et appels aux helpers `pad`, `floater`, `spells`. |
| `analyze_function` | `ev_ac313cb8cc73f9c102676395cd14cb97b5b1f9355d074df1e6656ce028d2d36f` | `FUN_0046466f` | Initialisation de quatre slots, sélection du marqueur/site de départ et appels pour créer le pad `0x2a` et quatre floaters; voir `FUNCTION_GUIDE.md` pour les limites d'interprétation. |
| `analyze_function` | `ev_60cc3b805a032ead183ce15cfa0965bb14b5d6c84b45414f6d11fbbb2eaca75b` | `FUN_00461859` | Post-traitement des records d'île : réinitialisation d'états, collecte et tri des ponts incidents et des records de classe 2, association des extrémités, déclassement des records sans pont correspondant. |
| `analyze_function` | `ev_26fff5bcd9af63e50fab3f0e6120b8c6d139365c85a25a07557269008ee279a9` | `FUN_004500c4` | Initialisation runtime des records : champ `+0x14=-1`, reset de `+0x10` sauf classe 3, effacement de champs/drapeaux. |
| `analyze_function` | `ev_0e30ee9ad5fb8589ee58fce47a3a6e4ab0c72e76ca39b0836ffc9a6344f61862` | `FUN_00461768` | L'assemblage montre le comparateur de ponts omis par le pseudocode : extrémités non partagées, angles de la table monde, soustraction flottante et conversion `__ftol`. |
| `analyze_function` | `ev_b2c053a4bd63d8f7ce191f425358685b35f763313fce9b221df727eef5c30a41` | `FUN_00461831` | Comparateur des pointeurs de records de classe 2 par différence du premier champ `short` (X dans le contexte appelant). |
| `analyze_function` | `ev_a0793f5d9552f14a7accb48cbf992564af87d834ce8fe8c91da7a4cfbdd76ad1` | `__ftol`, `0x472c6c` | Routine runtime Visual Studio : conversion x87 float vers entier avec troncature vers zéro. |
| `analyze_function` | `ev_dc8178f27dfbe5ae5eb96c11000ab02fb34bf426d8d5bfa2b5e0e778095f46d4` | `FUN_00467260` | Génération d'un entier pseudo-aléatoire borné : tirage LCG 15 bits, multiplication par la borne, division x87 par `32768.0f`, conversion entière. |
| `analyze_function` | `ev_54b38f5f410aea6f9412be424aca11a8988ac2385749300cc5e9178ac5d354ad` | `FUN_00474b80` | Écrit la graine du LCG dans `DAT_004a6340`. |
| `analyze_function` | `ev_5937c55f338b7b8770bc542cfe382c4755b4fb232b3d306e6a536037c7fbd98c` | `FUN_00474b90` | Mise à jour 32 bits de la graine et retour des bits 16–30 (`state * 0x343fd + 0x269ec3`). |
| `read_bytes` | `ev_4791eda48b1dd3df52587e7ec577452e548d62501c2802c49c34a2cbeebf2c38` | `0x494798` | Les quatre octets `00 00 00 47` représentent le flottant IEEE-754 `32768.0f`, utilisé par `FUN_00467260`. |
| `analyze_function` | `ev_af395cb5dc0ed1efd405d0c4880d5843648c434a49f9d811e53dccc4b1268377` | `FUN_00464b9e` | Attribution additionnelle de lieux via parcours de tables et choix conditionnels/aléatoires. |
| `analyze_function` | `ev_038b2943f7d5a4740ab39be3abfaf601533a2b50ae7c2135f46dd1eea6cbeaf5` | `FUN_00464b9e`, assemblage | Confirme les limites du parcours, le choix des marqueurs et les paramètres passés aux helpers. |
| `analyze_function` | `ev_9c1455ba552ca8516634a6b8919d421f5f1ab12d0184e0cbf893965eef0b22ba` | `FUN_004535e4` | Choix des IDs 6–9 selon les tables shape/realm et les items déjà présents dans l'île. |
| `analyze_function` | `ev_ebe214a1825dc422a3162a86d7bbb782029538e17a763d5d78e571c6fee5822d` | `FUN_00452859` | Validation, mutation via `FUN_004528ca` puis effets secondaires d'objet. |
| `analyze_function` | `ev_7a10ac57d0a8f9d1c6d94bfdba0ff8f19388f4df1e6f899c1c0e677dc4e4a147` | `FUN_00452656` | Admissibilité d'un item selon le paramètre et la classe/limite du record. |
| `analyze_function` | `ev_48b4bcba9562b96d86e08e3898333b2848f2054141dcd10e2ad9becb516044e3` | `FUN_004528ca` | Champs d'enregistrement écrits et drapeaux initialisés à la création. |
| `read_bytes` | `ev_614008e78140c166d35cb4e7093dbfb71b9bca6ea7b05059d629a6c9d6a74f51` | `0x4a28c8` | 16 entrées `int16` de la première table de realm, indexée par shape ID. |
| `read_bytes` | `ev_75517bd4bd63d8f7b901ff08a88d5103b4ac6340e48e2a9556989d5651f72040` | `0x4a28e8` | 16 entrées `int16` de la seconde table de realm, indexée par shape ID. |
| `analyze_function` | `ev_a3a1136454b116409a3a18908d27e23488bf809cdcb8d28b4d4d0805f05688e3` | `FUN_0041c46f` | Références Ghidra relient les chaînes `effects.txt`, `fltinf.txt`, `bldinf.txt` aux appels respectifs vers `FUN_004153b8`, `FUN_00454d1f` et `FUN_00455833` ; call-sites `0x41c669`, `0x41c6aa`, `0x41c6b9`. |
| `read_bytes` | `ev_d64c24d6ebe5f8bcb691202a6d7fad642a6264e07b2bc78e83ce1c39bc21ec8f` | `0x49de40` | Lecture de 16 octets ; `END\0` observé à l’adresse référencée par le parseur de textes. |
| `read_bytes` | `ev_7dfb26f9c9ef233774c5281b8d6c98964c45d378c4dabe0e36f189713717924f` | `0x49be80` | Lecture de 0x140 octets ; a permis de confirmer le tag `TYPE`, `CAST` et les valeurs de `REALM`. |
| `read_bytes` | `ev_8e3daac3c7a9e37924fe5cacc8805796a6855ceafdb5cb3ae47e518811831864` | `0x4a2e10` | Lecture de 0x350 octets ; confirmation des tags et formats `shapeinf.cpp`, `ITEM` à `BARG`, et des noms de limites. |
| `search_strings` / références croisées | `ev_3d928c3e3c20204be08e14067bfa575cbc3d1a9fe24a546b56dfe0d283c1483b` | `FUN_00410105`, `0x410105` | Chargeur de `cob.cfg` : lecture des lignes de configuration et appel du traitement d’une archive par ligne. |
| `analyze_function` | `ev_78147898fdd67751ac4b9dc7f61c638b16c2a36dd616080db86817b146a0965a` | `FUN_0040ff5b`, `0x40ff5b` | Chargement des archives COB : compteur, table de noms de 50 octets, table d’offsets de 4 octets et plafonds de capacité. |
| `analyze_function` | `ev_dbed377a96c46e7249eb471314289a7bc5e14e413dae2d53c986f75f10265626` | `FUN_00474b00`, `0x474b00` | Helper appelé pour ouvrir/lire le fichier de configuration COB. |
| `analyze_function` | `ev_87da4088d973d81a945f8e3e9d68ea79ba722b3a0ebeefcfa1504b0232847a05` | `FUN_00474190`, `0x474190` | Helper de lecture fichier du runtime, noté pour le contexte du chargement ; aucune sémantique COB spécifique ne lui est attribuée. |
| `analyze_function` | `ev_15c8370778d014104c360b1fc45e6174add31e7ce2b771b4a2f6eba9473c9fc0` | `FUN_00440567` | Formule d'affichage `WORKSTR` et lecture `DAT_006191f8`. |
| `analyze_function` | `ev_73b7a5d00a820cccc744dfd2168d1f0704c9ce37dda703814c69df8fc9be7ca5` | `FUN_0046562b` | Comptage par premier dword de catégorie/type et filtre sur le second dword. |
| `inspect_native_instruction` | `ev_20c6e74d9bf368220195a9f1340f0eb4feaa54a95c1d25b61a49ebad099863ab` | `FUN_00440567` | Calcule `count(+4==0) * 100.0 / count(tous)` puis convertit vers l'entier affiché. |
| `xrefs` / `read_bytes` | `ev_35dd32f9b0d9fd7b10dddf106f9517fe0eb352d969838552bc284f20e0c80c71`, `ev_785c735c398b2b79aed64f722b3b9dc00fbd787d8f894a5c1679744c01aad41c` | `DAT_006191f8` | Xrefs examinés en lecture; cinq slots échantillonnés nuls sur disque. |

---

# Registre d’évidence REA

| Opération | Evidence ID | Résumé | Couverture / remarque |
|---|---|---|---|
| `analyze_function` | `ev_0ca802ac15043c61c073f6d68546619fc924a4ba10fd4d9f04e203668dc62ed7` | `FUN_00466fe4` | L'allocateur écrit les deux premiers dwords depuis ses paramètres type/sous-type; bornes de catégories et sous-types. |

---

# Registre d’évidence REA

## Sources locales de données du jeu

- Les archives `TONE00.COB` et `TONE01.COB` sont à côté de `FLOAT.EXE`; structure statique et inventaire : [cob_archives.md](../../cob_archives.md).
- Les 483 membres ont chacun un enregistrement avec offset, longueur et chemin local dans `../archive_index.jsonl`.
- Le clone local `C:\git\ToneRebellion_Raw\original_content` est la copie de travail des contenus extraits. Éviter GitHub, conformément à la demande de l’utilisateur.

---

# Registre d’évidence REA

## Profil d’analyse

- Fournisseur : Ghidra 12.1.4
- Aucun fichier `Float.pdb` disponible pour cette analyse, selon la précision de l’utilisateur. Toute référence PE au nom du PDB est un chemin/nom déclaré dans les métadonnées, pas la preuve de disponibilité du fichier.
- Progression finale : 2 410 procédures inventoriées ; 1 493 internes et 14 runtime décompilées ; 780 thunks et 123 externes exclus avec motif ; 0 fonction interne en attente ou en échec de décompilation dans cette passe.
- Les Evidence IDs individuels sont référencés par adresse dans `index.jsonl`; les pages pseudocode sont `functions/0001_entry_runtime.md` à `functions/0023_batch_0019.md`.

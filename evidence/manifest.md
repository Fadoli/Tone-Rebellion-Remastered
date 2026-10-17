# Registre d’évidence REA

| Opération | Evidence ID | Résumé | Couverture / remarque |
|---|---|---|---|
| `binary_overview` | `ev_78e02fea36715ea8de479afd53ecbe956f7050cb8cea229addc1a460097c39f3` | 2 410 procédures, 2 209 chaînes, image base `0x400000`, 7 segments | Observation Ghidra 12.1.4 via workflow REA. |
| `list_procedures` | `ev_c01b8c54dcc2f60207f2b1d086a7768d14adb866a6a07f142f3c1ef365c344ac` | 2 410 procédures | Evidence complète récupérée du registre REA ; index initialisé depuis cette réponse. |
| `analyze_function` | `ev_4ea4348ef088ca577694ef3daa25d523ab017af07ee682c3223e064798ca5191` | `entry`, `0x478460` | Pseudocode, appels et références associés. |
| `analyze_function` | `ev_4447fdd9631929efaeb1d177248260afbbd55aec3775ce0996e1f9b427cb4e7f` | `FUN_0041d8e1` | Pseudocode, appels et chaînes associés. |
| `analyze_function` | `ev_b6c592d2020a3b072f7d397ada43d048a75789229d848e76ffadec2a536491cf` | `FUN_0041c1d6` | Pseudocode, appels et chaînes associés. |
| `analyze_function` | `ev_a3a1136454b116409a3a18908d27e23488bf809cdcb8d28b4d4d0805f05688e3` | `FUN_0041c46f` | Pseudocode, appels et chaînes associés. |
| `analyze_function` | `ev_5e71afc99fd4ab5273b4c07b5dc6e556212856d3462a715fb6a2569b19ce1407` | `FUN_0040bf98` | Réponse dossier dépassait le budget MCP ; pseudocode complet récupéré via `inspect_analysis_view`, Evidence de projection `ev_b27af7c4aa7fe81484bab129b8d52fbeac54c332a8df1d60fb47c7d01c7eb5ab`, 19 350 unités UTF-16. |
| `analyze_function` | `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a` | `FUN_0041e569` | Pseudocode complet obtenu par pagination de la projection conservée, 20 237 unités UTF-16. |
| `analyze_function` | `ev_6ac7cc6650dc8a0e9b412c055606948d1c6dbbdd3e6c6df0a7fcc1551764419e` | `FUN_0042fa0f` | Réponse paginée du registre Evidence ; pseudocode complet (31 897 unités UTF-16). |
| `analyze_function` | `ev_0d862ab7ac54cca2b239537d84431bd5a758100fdc0d68f7cc958f8f31cdbdf6` | `FUN_004337d9` | Réponse paginée du registre Evidence ; pseudocode complet (23 161 unités UTF-16). |
| `analyze_function` | `ev_2c01d69c5cc4626ed22aa4e310f991bfd5bbd1180eefe950c3ecf47a1b8658eb` | `FUN_00450a71` | Réponse paginée du registre Evidence ; pseudocode complet (28 097 unités UTF-16). |
| `analyze_function` | `ev_fbdcb9f3b27de341d258e85d68d67d6f9dbe6fb0971f77f99f80d7c8484fa98c` | `FUN_0046cd22` | Réponse paginée du registre Evidence ; pseudocode complet (24 375 unités UTF-16). |
| `analyze_function` | `ev_c337653463ee8c6cfd8d1c96e1f5ff733f7cb2d54228801312a9c893827bc0cb` | `FUN_0047a7c0` | Réponse paginée du registre Evidence ; pseudocode complet (21 335 unités UTF-16). |
| `inspect_native_instruction` | `ev_f59847072eb309e1dd70ee6e13ae354930572914ab05c815aa8a8bd2d573198c` | `0x4020d6` | Instruction `JMP 0x41bdae`; cible confirmée comme procédure indexée `FUN_0041bdae`. |
| `analyze_function` | `ev_fa0207968e95f1464cc1c397bc1d8b28d8ffed8238efbbe7a0daf79f16598254` | `FUN_0046bdee` | Dossier relu pour la cartographie de la boucle principale ; appels, pseudocode et limites conservés dans la page de fonction. |
| `analyze_function` | `ev_29e8acc9ef214546bdb7036b2cbf1e88ffe8105275d37ccc324960fffcdd8da8` | `FUN_0042cc24` | Dossier du chemin de rendu relu pour distinguer les appels de surface/GDI et les chaînes d’erreur. |
| `analyze_function` | `ev_a96a976ad9c33472b4ef2263c63b0eb7fc71e68f3c288de3c2d861de035fa03b` | `FUN_0041cf86` | Dossier de fermeture appelé par le callback WM_DESTROY : journalisation, `PostQuitMessage` et mise à jour d’un état global. |
| `analyze_function` | `ev_b04b7d1efd83a3e7d49ab7ce32bdae2bdc89bee29051ec02d0a1f76ab342b224` | `FUN_00429c4b` | Parseur de blocs de texte à clés ; chaîne `ENDTEXT` et arrêt des valeurs par préfixe `END`. |
| `analyze_function` | `ev_fe2d04de71105903ee26e44b7d85f686a4b05bf73a5a407f1e66a1fe0450cfef` | `FUN_00429d5c` | Stockage partagé de texte et bornes de tampon/table observées. |
| `analyze_function` | `ev_f2aaf6dc9f43acefcf3cfa30722df6d60c3f30d302c321fa1ac8258d2174a0a7` | `FUN_0040f419` | Chargement du fichier vers un tampon de taille bornée. |
| `analyze_function` | `ev_9a43dae9087123005e9f536b7788da9b702d57a3b6b013e2b713164b23dab33f` | `FUN_0040f5b3` | Lecture des lignes, filtrage des lignes vides/commentaires. |
| `analyze_function` | `ev_a4d00f397b10ddd5f9e8450e88d33825e40a624c6b54a2e49736d00567ca318c` | `FUN_0041d19d` | Parseur de clés/valeurs pour `float.cfg`. |
| `analyze_function` | `ev_187d22e0d18c68faf0861e12bda0956428befb83a667937aa0ced1976eed0ea5` | `FUN_0041d64e` | Lecture de la valeur `cdrom` depuis la branche de registre Tone Rebellion. |
| `analyze_function` | `ev_b765d704b9b04a47f1cc07ea19409dcd140e8aadd2232363e5685731bec68576` | `FUN_0041d70d` | Lecture séquentielle de groupes de noms de tailles fixes. |
| `analyze_function` | `ev_fd688883d1298751b7b836f120b2f943abe1617bc91b1afc0b81c8323578cacf` | `FUN_0042f150` | Recherche de types de fenêtre et chaînes localisées, dont le diagnostic `gamey.txt`. |
| `analyze_function` | `ev_a2f6dd8fe47f403c98165ec901d7fc9dac3fe46367845bddaa51759bdfbdbec6` | `FUN_004153b8` | Parseur d’enregistrements de données d’effets. |
| `analyze_function` | `ev_6ccf11adf4100a01f329d47d35c0c8bd1d7e5c6fcff4d70ee2a0c846e156a876` | `FUN_00454d1f` | Parseur shape-info avec tags d’animation/interaction. |
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

## Sources locales de données du jeu

- Les archives `TONE00.COB` et `TONE01.COB` sont à côté de `FLOAT.EXE`; structure statique et inventaire : [cob_archives.md](../cob_archives.md).
- Les 483 membres ont chacun un enregistrement avec offset, longueur et chemin local dans `../archive_index.jsonl`.
- Le clone local `C:\git\ToneRebellion_Raw\original_content` est la copie de travail des contenus extraits. Éviter GitHub, conformément à la demande de l’utilisateur.

## Profil d’analyse

- Fournisseur : Ghidra 12.1.4
- Aucun fichier `Float.pdb` disponible pour cette analyse, selon la précision de l’utilisateur. Toute référence PE au nom du PDB est un chemin/nom déclaré dans les métadonnées, pas la preuve de disponibilité du fichier.
- Progression finale : 2 410 procédures inventoriées ; 1 493 internes et 14 runtime décompilées ; 780 thunks et 123 externes exclus avec motif ; 0 fonction interne en attente ou en échec de décompilation dans cette passe.
- Les Evidence IDs individuels sont référencés par adresse dans `index.jsonl`; les pages pseudocode sont `functions/0001_entry_runtime.md` à `functions/0023_batch_0019.md`.

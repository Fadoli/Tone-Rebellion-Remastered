# Registre d’évidence REA

| Opération | Evidence ID | Résumé | Couverture / remarque |
|---|---|---|---|
| `xrefs` | `ev_da7542c8d20a92a354e31176edb14fccd1ee1f3fac24ff7f7cfd1464503b3b49` | `DAT_006183cc`, table d’action des tâches | Quatre références directes vers le champ d’action des slots. |
| `procedure_pseudo_code` | `ev_bd805382bd750a65076a58742501849e1bdeb29a87bc0717a5bac1e0307b1077` | `FUN_00422031` | Validation d’un slot de tâche; seules certaines valeurs d’action ont des gardes explicites. |
| `procedure_pseudo_code` | `ev_25d048fc082b5ed144709e4886b7748e44943fd30f5e02a0e06addfc60beaec9` | `FUN_004455d1` | Énumération des slots visibles dans Tasks; filtre l’action `0x0b`. |
| `procedure_pseudo_code` | `ev_ed75141a79f1bac30a4ad39dcad68e710e351330bcd3044aa3cb304ef2a796b2` | `FUN_0042fa0f` | Recherche d’un slot actif par l’interface Tasks. |
| `read_bytes` | `ev_bc254ddb3b5d4bfc3b423aa3c2a839a6aa1f4f771807016000e59944447f751e` | `DAT_006183bc..0x6188bc` | 0x500 octets lus dans l’image chargée; tous nuls. |
| `list_segments` | `ev_254928ccff2cf0ec576eeddf8c2bba7d672a4d24c5d348d39bb0e17288171961` | Segment `.data` | Ghidra marque le segment contenant les slots comme initialisé. |
| `inspect_native_instruction` | `ev_50a5fda0ff82969f755c9db1bc3df1f158c35f1c08640ce4cc393b308f55d113` | `DAT_006183cc` | Références typées entrantes : aucune écriture directe observée sur le champ. |
| `analyze_function` | `ev_6ac7cc6650dc8a0e9b412c055606948d1c6dbbdd3e6c6df0a7fcc1551764419e` | `FUN_0042fa0f` | Réponse paginée du registre Evidence ; pseudocode complet (31 897 unités UTF-16). |
| `procedure_pseudo_code` | `ev_9fac3ab32e724258b184a4abd7ffd102c61b15164169cc041ae03f1859b5bb49` | `FUN_00435826` | Hit-test carte; chemin qui émet `0x40` avec le sélecteur Inventory actif. |
| `analyze_function` | `ev_63d9efb5bce1c51e26da896805829764236e9140de5f842cda6ad015f1c8ad1b` | `FUN_00466221` | Dépile les commandes locales et transmet les paquets catégorie 0 à `FUN_004662b7`. |
| `procedure_pseudo_code` | `ev_db281f9a7a1fbb3e9bd29b7389912081c306195183d45c11b3bae8830ccff761` | `FUN_004662b7` | Stocke les paquets catégorie 0 dans une table de 64 slots de tâches différées. |
| `analyze_function` | `ev_9d5d129cd6bb5e1095f8136fbde959c47360ad898c94d3104c63add6dcda3bc7` | `FUN_00422031` | Cas de validation des tâches de type 4; l'effet monde final n'est pas établi. |
| `procedure_pseudo_code` | `ev_dfa9260d630c5590f535d54281a0b8f2c2767e3ca99d4a00ffdd596b3104b7eb` | `FUN_0044003d`, `0x44003d` | Émission de `0x32` selon le slot sélectionné et `+0x18`. |
| `procedure_pseudo_code` | `ev_196d5ce18818030f061f610add4e421b67b51a08a81cfe4b30f91fd722d4a4dc` | `FUN_0042970c`, `0x42970c` | Routage selon mode 0/1/2 du dispatch. |
| `procedure_pseudo_code` | `ev_1a06455495cb08c19a3e95bb1bd8abb4f5f2df731cdd09e809cc8c2a78f504f9` | `FUN_0041c46f`, `0x41c46f` | Inscription du callback au slot 3; état initial choisi 0 ou 8. |
| `procedure_pseudo_code` | `ev_a8230350584e54954217dfeda123b6cf8d9dc6ca7211fff2385661c22cdab6ba` | `FUN_0042fa0f`, `0x42fa0f` | Traitement partagé du message `0x32` après le switch. |
| `procedure_pseudo_code` | `ev_94eb91d39af9704767219d6df99b523c4408544d37cebde8472793c068780572` | `FUN_0046c402`, `0x46c402` | Appel indirect du callback au slot actif. |
| `procedure_pseudo_code` | `ev_e485a0839f32ca445383d2eab74cff5f5c3744ea6dbfc9bfc1b3c00a0edaa26a` | `FUN_0046c640`, `0x46c640` | Écriture de l'index actif du dispatch. |
| `procedure_pseudo_code` | `ev_adba0f04ecf4c24995e49e0f36cf9efcfa8397a704bdfbe072742e0e43adab60` | `FUN_0046cbe0`, `0x46cbe0` | Inscription d'un callback dans la table à pas `0x130`. |
| `procedure_pseudo_code` | `ev_313d0ccc3d43b5ed7e5d13b4b18d8ceca9606e76b6650bf123b770a1b8afe5f1` | `FUN_0046c1b4`, `0x46c1b4` | Dispatch du chemin secondaire du mode 1. |
| `procedure_pseudo_code` | `ev_9b2f8d28b701a828ee0fa8c8a2a7b9ed1ac5edc678f92d8c58589e8d2a034487` | `FUN_0046c3bc`, `0x46c3bc` | Passage du mode 2 par la file locale. |
| `procedure_pseudo_code` | `ev_ed92b375145a0b030776f82d115ccc237230777746be74169b6aac305580d646` | `FUN_0046c371`, `0x46c371` | Dispatch indirect du callback/handler. |
| `procedure_pseudo_code` | `ev_45c01a5996eb93f262ba6c323b4204385b379cf618c015fe98b5915f6ba131f4` | `FUN_0044003d`, `0x44003d` | Références entrantes : seul entrant code résolu est une thunk; appelant fonctionnel non établi. |
| `procedure_pseudo_code` | `ev_402be0529a7ef91e812f2d71112211850a8109145326f5a6fb277d1fc8fe21ca` | `FUN_00469cce`, `0x469cce` | Initialisation de l'index actif à -1. |
| `procedure_pseudo_code` | `ev_21bbfcb1cfb92364a864a26226f542128edeaed0b08030bf8e4652aab1e6e24f` | `FUN_0046b752`, `0x46b752` | Une entrée de file peut modifier l'état actif via `FUN_0046c640`; lien au clic inconnu. |
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

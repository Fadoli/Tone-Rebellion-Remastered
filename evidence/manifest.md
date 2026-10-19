# Registre d’évidence REA

| Opération | Evidence ID | Résumé | Couverture / remarque |
|---|---|---|---|
| `binary_overview` | `ev_78e02fea36715ea8de479afd53ecbe956f7050cb8cea229addc1a460097c39f3` | 2 410 procédures, 2 209 chaînes, image base `0x400000`, 7 segments | Observation Ghidra 12.1.4 via workflow REA. |
| `list_procedures` | `ev_c01b8c54dcc2f60207f2b1d086a7768d14adb866a6a07f142f3c1ef365c344ac` | 2 410 procédures | Evidence complète récupérée du registre REA ; index initialisé depuis cette réponse. |
| `analyze_function` | `ev_4ea4348ef088ca577694ef3daa25d523ab017af07ee682c3223e064798ca5191` | `entry`, `0x478460` | Pseudocode, appels et références associés. |
| `procedure_callers` | `ev_2d79f304365a3c8484b4cf08c48a252a5a1bef7bc030214046ea9ada686a468e` | `FUN_0042219e`, `0x42219e` | Aucun appelant direct résolu ; appels calculés/indirects restent hors de cette relation Ghidra. |
| `analyze_function` | `ev_b51f2311ff9bd9ad209f0663ea00bfe330e7ff0eff117e8a273292d3112a4e0e` | `FUN_00466ce2`, `0x466ce2` | Tick de simulation : actions monde, parcours des floaters actifs, compteurs et temporisateurs. |
| `analyze_function` | `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957` | `FUN_004211bb`, `0x4211bb` | Consommateur d'ordres : branches d'état, recherche de cibles, progression et annulation. |
| `analyze_function` | `ev_787dc785055d52728b1408fa372d280fa57be569a05f32883f94a4022cbce846` | `FUN_0042219e`, `0x42219e` | Réévaluation de l'ordre et sélection de cible selon classe, état, distance et tâches disponibles. |
| `analyze_function` | `ev_76a4661cb67067b44054706649c3ff1f80a7e9eec7116d8c36177f340ab15b36` | `FUN_00420a55`, `0x420a55` | Cinq filtres de candidats, scoring, shortlist de dix éléments et sélection finale. |
| `analyze_function` | `ev_0a150ef6299ccee55e14aeab45e2de16381b5142b4063cda099503d87e818883` | `FUN_00420d97`, `0x420d97` | Wrapper de recherche qui fournit l'île courante du floater. |
| `analyze_function` | `ev_b758701979d34e447f00b2067f67d58c0c58d9b8c28b444e24dfd4a160713da5` | `FUN_00420991`, `0x420991` | Garde candidat : état/flags, classe et seuils liés au niveau. |
| `analyze_function` | `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f` | `FUN_00422d27`, `0x422d27` | Avancement spatial par pas borné jusqu'à destination. |
| `analyze_function` | `ev_1d0bd9feec2d7550ea50129522ad783374e97af92bb6dd9bebd24510c185aedf` | `FUN_00460072`, `0x460072` | Affectation aléatoire de slots admissibles aux demandes de type d'unité et aux îles/features. |
| `list_strings` | `ev_189665af46e3e7c1c67975389c462c48387e5c25127ebe9509729510bd2e66b7` | Chaînes définies, dont `FA_AttackFlt`, `FA_AttackLoc`, `FA_Cast`, `BC_AttackFlt`, `BC_AttackLoc`, `BC_Spell1`–`BC_Spell8` | Inventaire initial ; les adresses et l’indexation action/libellé sont confirmées par les preuves ci-dessous. |
| `procedure_pseudo_code` | `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea` | `FUN_0042219e`, `0x42219e` | Nouvelle analyse : branches Leviathan 9 et 10–17, réévaluation des ordres/cibles des floaters réguliers. |
| `procedure_pseudo_code` | `ev_0e9d3fbfa8df7eb8f372d0b17bc92593ddd6fc2eb7cebe7c043ca611798b4abd` | `FUN_004211bb`, `0x4211bb` | Nouvelle analyse de l’exécution des ordres numériques et des transitions d’état des unités. |
| `procedure_pseudo_code` | `ev_5f9c5a49a60617354d8ad7505c83964ab1f03b05faeb5ac50e17dde56b5c584a` | `FUN_0044338b`, `0x44338b` | Affiche les libellés d’action et d’état runtime en indexant séparément la table `FA_*`. |
| `procedure_pseudo_code` | `ev_2e9357b21e13aa63c74213b43d59e68fd72a88c0668e7a529e193fa19960063e` | `FUN_00435f4d`, `0x435f4d` | Confirme indépendamment les champs floater `+0x3c` (action) et `+0x2c` (état runtime). |
| `search_strings` | `ev_ca6209d841056d1b69884f43a204d17713c19c2756570da82baaec770609aa1f` | `FA_*`, 22 libellés | Les chaînes et adresses forment une table contiguë avec un pas de 0x10 octets, IDs 0–21. |
| `procedure_pseudo_code` | `ev_fd05027dd8dfa2720031c58c1dfbd4ddc7a335d8b87ce01675e83b1b460a7991` | `FUN_00466fe4`, `0x466fe4` | L’allocateur limite la catégorie 4 aux sous-types 9–17 et les autres catégories à 0–8. |
| `procedure_pseudo_code` | `ev_d6c275efa826bd914507bd53c4c3f4d979737f6bb54430df661e8609724bd78d` | `FUN_0041d70d`, `0x41d70d` | Charge exactement 18 noms `xSpores`, indexés par paires de sous-type pour l’affichage. |
| `procedure_pseudo_code` | `ev_2d5d4353c4c551b2a2466b6ea1e94e34b62fe0ef86797db366eca77c4a38fb4f` | `FUN_00420a55`, `0x420a55` | Filtre mode 2 et sélection d'emplacements sur l'île courante. |
| `procedure_pseudo_code` | `ev_2f27ef00567b68d5a8d3ffd44f86f6a060dead0acebb0b98c93fd7e2b36b128b` | `FUN_0041e28e`, `0x41e28e` | Choix aléatoire pondéré par les scores parmi les candidats. |
| `procedure_pseudo_code` | `ev_8abb08fe878eeb4b95b90b95aa69f3315b673dc32d5016dbd3cf3274f4ac8493` | `FUN_00420635`, `0x420635` | Score de cible basé sur le helper de distance. |
| `procedure_pseudo_code` | `ev_ff0149927c5527e42ad97c0ccb0ecff046537edadb26eb9fecf60e1403b49d28` | `FUN_0041e569`, `0x41e569` | Cadence de reevaluation et conversion de l'emplacement cible par le Spore. |
| `procedure_pseudo_code` | `ev_6745ea13e551cd4bc25dc59c623fb7adf0a818c613fdb948c7f4b034a74cac52` | `FUN_004204bc`, `0x4204bc` | Application de dégâts, flag de mort et attribution de la source éventuelle. |
| `procedure_pseudo_code` | `ev_f6fad36a24d0df23600189218f8f97cf25c8ae1078856cf1f0526c0fd092aedd` | `FUN_00460460`, `0x460460` | Comptes par île pour les sites de type 4; écritures de temporisateur dans les records d'emplacement (`+0x45a`). |
| `procedure_pseudo_code` | `ev_51318b865289347ea016897f2f58125ee6479e16683f3d13844fb280a52d10df` | `FUN_00460989`, `0x460989` | Consomme les comptes/compteurs insulaires et pose le flag `0x80` sur certains floaters Leviathan non-Spore. |
| `analyze_function` | `ev_0a3a5baa3dd85e9e4d8e576461b4c0ac5dde6dd1cb0ba6135191f046f1f98a93` | `FUN_00422d27`, `0x422d27` | Mouvement vers une destination et condition d'arrivée sur les deux axes. |
| `analyze_function` | `ev_4447fdd9631929efaeb1d177248260afbbd55aec3775ce0996e1f9b427cb4e7f` | `FUN_0041d8e1` | Pseudocode, appels et chaînes associés. |
| `analyze_function` | `ev_b6c592d2020a3b072f7d397ada43d048a75789229d848e76ffadec2a536491cf` | `FUN_0041c1d6` | Pseudocode, appels et chaînes associés. |
| `analyze_function` | `ev_a3a1136454b116409a3a18908d27e23488bf809cdcb8d28b4d4d0805f05688e3` | `FUN_0041c46f` | Pseudocode, appels et chaînes associés. |
| `analyze_function` | `ev_5e71afc99fd4ab5273b4c07b5dc6e556212856d3462a715fb6a2569b19ce1407` | `FUN_0040bf98` | Réponse dossier dépassait le budget MCP ; pseudocode complet récupéré via `inspect_analysis_view`, Evidence de projection `ev_b27af7c4aa7fe81484bab129b8d52fbeac54c332a8df1d60fb47c7d01c7eb5ab`, 19 350 unités UTF-16. |
| `analyze_function` | `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a` | `FUN_0041e569` | Pseudocode complet obtenu par pagination de la projection conservée, 20 237 unités UTF-16. |
| `analyze_function` | `ev_234f0678b3bbd27430c793e465dfd5095240536d821d1821e23bb5b1acb00e41` | `FUN_00420721`, `0x420721` | Rayon d'arrivée optionnel : garde catégorie/sous-type, lecture de la portée d'attaque dans la table de stats et modulation entière conditionnelle par `5/4`. |
| `analyze_function` | `ev_601b55f72156209d4f5c1ae6f9060918a71e3fc3423c72c12074227bdb69a5c6` | `FUN_004207c2`, `0x4207c2` | Garde du rayon optionnel : catégorie 4, ou sous-type non nul avec champ floater `+0x22` positif. |
| `analyze_function` | `ev_400be7fc416e3e48c58ebeae7f1497639f909f0569891b58d5b3cba579bbab2a` | `FUN_004207f2`, `0x4207f2` | Retourne le pointeur de site courant si le lien floater `+0x0c` diffère de `-1`. |
| `analyze_function` | `ev_0f1bf5caca4a6c5c244c4a2b8bee6e591fc8367f9b451a0694329a19e3378011` | `FUN_0045c3bb`, `0x45c3bb` | Résout le pointeur de lieu/site à partir des champs d'indice et d'île du floater. |
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
| `analyze_function` | `ev_0ca802ac15043c61c073f6d68546619fc924a4ba10fd4d9f04e203668dc62ed7` | `FUN_00466fe4` | L'allocateur écrit les deux premiers dwords depuis ses paramètres type/sous-type; bornes de catégories et sous-types. |

## Sources locales de données du jeu

- Les archives `TONE00.COB` et `TONE01.COB` sont à côté de `FLOAT.EXE`; structure statique et inventaire : [cob_archives.md](../cob_archives.md).
- Les 483 membres ont chacun un enregistrement avec offset, longueur et chemin local dans `../archive_index.jsonl`.
- Le clone local `C:\git\ToneRebellion_Raw\original_content` est la copie de travail des contenus extraits. Éviter GitHub, conformément à la demande de l’utilisateur.

## Profil d’analyse

- Fournisseur : Ghidra 12.1.4
- Aucun fichier `Float.pdb` disponible pour cette analyse, selon la précision de l’utilisateur. Toute référence PE au nom du PDB est un chemin/nom déclaré dans les métadonnées, pas la preuve de disponibilité du fichier.
- Progression finale : 2 410 procédures inventoriées ; 1 493 internes et 14 runtime décompilées ; 780 thunks et 123 externes exclus avec motif ; 0 fonction interne en attente ou en échec de décompilation dans cette passe.
- Les Evidence IDs individuels sont référencés par adresse dans `index.jsonl`; les pages pseudocode sont `functions/0001_entry_runtime.md` à `functions/0023_batch_0019.md`.

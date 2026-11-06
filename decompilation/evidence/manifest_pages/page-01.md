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
| `analyze_function` | `ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f` | `FUN_00423068`, `0x423068` | Ajustement d'ancre/orientation et résolution de destination selon l'état; en état `0x0e`, tirage autour de la position courante et écriture sous garde de limites X. |
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

# Feuille de route

État au 2026-11-02. Détail des items dans le [backlog](TODO_BACKLOG_INDEX.md); portage acquis dans [implemented.md](docs/implemented.md).

## Constat

- Décompilation : `index.jsonl` couvre 2410 procédures (1493 internes, 780 thunks, 123 externes, 14 runtime); 1507 décompilées, 903 exclues avec motif. L'inventaire est clos; le travail REA restant est ciblé (questions ouvertes ci-dessous), pas un balayage.
- Remake : ~44 k lignes C11 (`src/`), 27 programmes de test C + `tests/test_docs_integrity.mjs` + `tests/e2e/island_e2e.ps1` et `tests/e2e/fixture_e2e.ps1` (parties statiques générées, jamais les sauvegardes du joueur). Backlog (2026-11-03) : 71 items cochés, 1 ouvert (délai d'effacement du site source au déplacement de bâtiment, écart volontaire).
- Boucle de jeu : déplacement manuel, ordres de bâtiment, tâches (CONSTR, CHARGE, Obtain, SUPPLY, UpgSpread, Upgrade, Repair, Hall type 4), IA Léviathan et victoire par les sceaux sont portés. Restent des règles sans preuve native (voir Phase 1) et la vérification en jeu.

## Phase 0 — Hygiène (immédiat)

1. ~~Valider le diff en cours~~ : fait (arbre propre).
2. ~~Commentaire du champ 7 de `game_diplomacy.h`~~ : corrigé le 2026-11-02 (`+0xd8` = politique `DAT_00619290`, `+0xe8` = destinataires `DAT_006192a0`).
3. Ménage local (ignoré par git) : copies `ToneRebellion_Remake_sdl - Copie*.exe`, `ToneRebellion_Remake*.zip`, `../hs_err_pid*.log`, `mci_debug.log`.

## Phase 1 — Boucle de jeu jouable

1. ~~**Déplacement manuel**~~ (`TODO_MOVEMENT` l.9) : porté (`FUN_0043530b(0x13)` → `FUN_00435826` → `FUN_0042fa0f`, transfert inter-îles, défense/fusion au clic droit). Origine des ordres recopiés par `FUN_0042219e` établie : l'enregistrement du bâtiment (voir point 2).
2. ~~**Ordres de bâtiment**~~ (`TODO_INTERFACE` l.22, l.27) : fait — enregistrement `B+0x28..0x32`, `BC_*` (Attack/Defend/Recall/TrnStk), clic droit filtré par `DAT_00619290`, adoption `FUN_0042219e` (genre 0 compris), routage interîles par pont, lien gardé à la traversée. Reste: vérification en jeu de l'interîles.
3. ~~**Tâches**~~ : portées et testées — Obtain (tâche `0xd`, attache automatique comprise, traversée de pont), SUPPLY (stocks `TrnStkC/M`), UpgSpread (vérifié en jeu), Upgrade, Repair, Hall type 4, répartition des ouvriers (refonte `FUN_0042219e`/`FUN_00422031`/`FUN_004211bb` du 2026-11-01).
4. **Fidélité des tâches** (règles du port sans preuve native, à trancher par REA) :
   - Hall type 4 : dix candidats (`FUN_00420a55`) et attente de 20 ticks (`FUN_0041e569` états 3/4) confirmés par REA le 2026-11-02. Garde d'attente de l'état 3 et garde de classe `site+4` alignées (`TODO_MOVEMENT` l.17).
   - Repair : chemin natif établi (REA sonnet 2026-11-02, `behavior/island-repair-control.md`): le bouton bascule le bâtiment dans une liste de réparation de la tribu et crée une tâche type 4 sous-type 1; chaque Build Tone livré donne +1 PV jusqu'au maximum. `FA_Repair`/état 0x12 sont vestigiaux. Port aligné le 2026-11-02: `BC_Repair` émet `GAME_COMMAND_TOGGLE_REPAIR` (liste par site `repair_task_plus1`, ligne type 4 Build Tone), chaque unité livrée donne +1 PV et retire l'entrée au maximum; les sauvegardes d'origine rechargent la liste (`PLAYER_SITE_LIST`). Le chemin tâche 0x12 / soin à 40 ticks n'est plus émis par l'interface (code conservé pour les anciennes sauvegardes du remake). Non vérifié en jeu.
   - Type 5 ↔ `FA_Build` établi (action 5, état 5 → `FUN_004527ee`); le port garde l'action 4. Cas de `FUN_00450385` = états `FA_Enlist`/`FA_Train` (portés); le mot de mode `+0x13d0` est écrit par `FUN_0045f755` (porté).
5. **Producteur de `PIT_Object`** : les 8 appels de `FUN_004503bd` sont résolus (livraison, dépôt `FUN_00425084`, messages `FUN_00465793`/`FUN_004672ef`) et suivis par le port. La pose directe (`FUN_00465793` catégorie 3 / sous-type 4) n'a pas de constructeur local, seulement le relais réseau `FUN_00412eac`; traitée comme inutilisée (`TODO_OTHER` l.4).

## Phase 2 — Adversaires

1. ~~Tick IA `FUN_00460989` et `FUN_00460460`~~ : relus en entier et portés le 2026-10-28 (`TODO_TASKS` l.7). Il n'existe pas de planificateur de tribu adverse : l'adversaire solo est le Léviathan (Spores qui contaminent sites et marqueurs, marqueurs qui produisent, unités 10..17 qui attaquent floaters et bâtiments, vagues `0x80` élargissant la portée à 3000). Reste : garde `DAT_006191b4` (fin de partie, phase 3).
2. Leviathan : contamination, défense, production et attaques autonomes (`FA_AttackFlt`/`FA_AttackLoc`, riposte `FUN_00421d82`) sont reliés; une Spore peut maintenant contaminer un marqueur classe 1 et étendre la production. À vérifier en jeu.
3. Clic glyphe : `DAT_004befe0` = drapeau multijoueur; promotion du lanceur sous-type 8 à la naissance (`FUN_00462a87`) portée; ordre `0x13` déjà porté (TODO_OTHER l.5).

## Phase 3 — Fin de partie

- Déclencheur natif de l'état 7 : porté (destruction des sceaux `PIT_LeviShield` de la dernière île → séquence `FUN_00464e4d` L = 0, voir `behavior/end-game.md`). Évènements et jumelage de l'état 2, fondus des états 3 et 5 portés (2026-11-02). Reste : chemin multijoueur 0x15, vérification en jeu, relecture REA de `0x4239e9`/`0x46a92a`.
- Sauvegarde/chargement : fonctionne. Sauvegarde du remake = copie brute de `GameSession` (presse-papiers et champs d'ordre compris), mode Sauvegarde (état 5) de l'écran Charger/Sauvegarder porté. Les sauvegardes d'origine se chargent par `native_save_parse`/`native_save_apply` (sites, sources et ordres de bâtiment `+0x28..0x30`, stocks `+0x58/+0x5c`, tâches, floaters). Limites : une sauvegarde du remake est refusée dès que `sizeof(GameSession)` change (aucune migration) et dépend de l'ABI (32/64 bits); le presse-papiers natif n'est pas relu des sauvegardes d'origine.

## Phase 4 — Parité d'interface

Faite (2026-11-03) : polices, construction, commerce, diplomatie, inventaire, `IWFltInfo`, carte du monde (survol au seul mouvement de souris), options `float.cfg`, bords inclusifs des contrôles, badges FLTINFO (royaume par ligne fltinf, Léviathans, charge), mort des floaters (`die.shp`), zone de clic des bâtiments.

## Phase 5 — Audio

Porté : volume/pan par distance (`FUN_0045b24d`), bullets/impacts des producteurs (items Léviathan 0x0a..0x15, seuls appelants de `FUN_00416342`), sons d'île `FEATnn`, `CRUMBLE` (émetteur `FUN_00450847`, message 7 → `FUN_0042fa0f` 5 → évènement monde 7, île vue seulement). Animation d'application des sorts (`FUN_0041760b`) portée : l'effet du sort tombe à la fin de l'animation. Dessins `KILLBEAS`/`FAROBT` et miroir portés, lancer vérifié en jeu (fixture `spell`).

## Phase 6 — Portage Web (dernière priorité)

Plan : [TODO_WEB.md](TODO_WEB.md). Déjà fait : surface `RenderSurface`, services `platform_*`, shell `remake_sdl` (rendu, audio, curseurs `FLOAT.EXE`, sockets TCP), chemins UTF-8, build Web jouable (`tools/build_web.sh`, `web/shell.html` : wasm 1,37 Mo, dossier du jeu copié dans `IDBFS`, sauvegardes/options synchronisées après écriture, export/import, audio SDL3 repris au premier geste). Parité audio SDL/Win32 vérifiée dans le code (écoute facultative); multijoueur Web réglé par la build mono-joueur (relais possible sur demande). Partie réseau SDL↔SDL vérifiée en jeu (deux tribus, commandes au même tick, 728 ticks sans désynchronisation).

## Transverse — Vérification

Fixtures statiques (`TONE_REBELLION_E2E_FIXTURE` : badges, enemy_hall, spell, obtain, dying, victory, messages) et `TONE_REBELLION_SAVE_DIR` : `fixture_e2e.ps1` (20 contrôles) et `island_e2e.ps1` (21 contrôles, 1 ignoré) tournent sans toucher aux sauvegardes du joueur; voir `docs/build-and-validation.md`.

## Questions REA ouvertes

À trancher par sous-agent avant le port concerné :

- ~~Boucle de distribution souris~~: résolue le 2026-11-03 (`FUN_0046be81` survol, `FUN_0046c25d` clics, à rebours, premier gagnant, bords inclus). Résolus aussi (REA haiku 2026-11-03, `ev_3cb8d6d4…`, `ev_e0b600c3…`, `ev_4ed56393…`): l'index actif `+0x29f2` est l'état de jeu, seul écrivain `FUN_0046c640` (message 2 à l'ancien gestionnaire, 1 au nouveau, puis `FUN_0046be81`); les gestionnaires sont enregistrés par état (`FUN_0046cbe0`), `FUN_0042fa0f` est celui de l'état 3. `FUN_0042970c` est l'envoi de message à trois modes selon `+0x48`: 0 appel direct du gestionnaire de l'état courant (`FUN_0046c402`), 1 mise en file (`FUN_0046c1b4`, vidée par `FUN_0046b752`), 2 envoi par nom de fenêtre (`FUN_0046c3bc`); il n'appelle pas `FUN_0042fa0f` directement.
- ~~Expéditeur du paquet de clic Repair~~: établi le 2026-11-02 (catégorie 1 code 3, liste de réparation de la tribu, `behavior/island-repair-control.md`).
- ~~Paquet natif de `IWMove`~~: établi le 2026-11-02 (catégorie 3, sous-type 5 saisie `FUN_0045f4f5`, 6 pose `FUN_0045f5c5`, via `FUN_004354a2`; voir `behavior/island-ground-object-interaction.md`, « Paquets du déplacement »).

## Audit REA du 2026-10-27

Corrigés (preuve en commentaire dans le code) : bilan d'attaque appliqué à l'attaquant (`FUN_004200d2`/`FUN_00420188`, ECX = attaquant à `0x41ec64`) et dégâts de site débloqués; FA_Cast hors portée avance vers sa cible, destination résolue une seule fois, fin via drapeau 0x200 et +5 en `+0x08` (`FUN_0042383d`); morts Spore via `FUN_004204bc` (garde 0x8, son, compteurs). Ensuite : l'entraînement (`FUN_0045cd75`) rafraîchit portée, royaume, vitesse, force et PV depuis la ligne du nouveau sous-type (une unité à distance entraînée gardait la portée 0 de l'ouvrier et immobilisait sa cible comme en mêlée); royaume de combat via `FUN_0042003c` (±1 selon 0x10000/0x20000 du bâtiment lié, ligne du sous-type 0 pour un attaquant non chargé).

Contrôle des guerriers (REA, `FUN_00435826`, `FUN_0042f8f7`, `FUN_0042fa0f` 3001..3003) : la sélection d'un floater prend son bâtiment sur toute île (panneau mode 3); un raccourci sélectionne son bâtiment sans changer l'île affichée; le clic droit (`param_3 = événement 7`) avec un bâtiment d'entraînement possédé sélectionné écrit l'ordre du bâtiment (genres 6/8 floater, 7 site ennemi, 9 sol) adopté par tout le groupe; l'ordre garde l'île de la cible; le clic sur le sol revient au Hall par défaut; la traversée d'un pont accorde l'accès à l'île (`FUN_00466b09` à l'étape 0x3c).

Combat des soldats (REA `FUN_004633a7`, `FUN_004211bb`, `FUN_0042219e`, `FUN_00421d82`, `FUN_0041e569` case 8; simulation avec `floater.txt`/`fltinf.txt`) : la charge d'entraînement vient de la ligne +8 (points d'attaque max, colonne 5) et non de la force; DefendArea (action 9) n'avance d'étape qu'à la fin de l'état courant (les défenseurs ne frappaient jamais); le point de l'état 9 est tiré une fois et l'état s'arrête dès qu'un ennemi est près de l'ancre (tous les 8 ticks); l'ordre du bâtiment est recopié sauf pendant une frappe (état 6/7, pas l'action), y compris sur un floater qui attaque ou défend une zone; un floater tenu en mêlée riposte (`FUN_00421d82`, soldats et Léviathans). Un soldat lié sous un tiers de ses PV (ou à court de charge en combat) rentre se soigner / recharger dans son bâtiment sur le stock +0x2a (action 2, état 2 : `FUN_0042219e`, `FUN_004211bb` case 1, `FUN_0041e569` case 1, `FUN_0045ddb8`), puis reprend l'ordre du bâtiment.

Corrigés le 2026-10-31 (REA `ev_7393f2a9`, `ev_9994f35e`, `ev_3cb7946b`, `ev_1bc6136e`, `ev_427930b7`) : tirage `FUN_00467260(3)` dès qu'une cible floater existe (0x42244c); Hall de départ = premier site classe 0 type 0 au Chebyshev strictement minimal, sans préférence de pad; recharge Build Tone sans priorité Hall (le Hall n'est qu'un candidat de `FUN_00452ceb` tiré par `FUN_0041e28e`; la « priorité » était un ajout du port); latch `+0x90` (plus de floater ou `+0x3c < 1`) qui arrête le recruteur et rend la défaite définitive; sortie de pont d'un sous-type 8 sur l'action 9 (0x41f935..0x41f958). Déjà portés, lignes périmées retirées : riposte `FUN_00421d82` des Léviathans tenus, sélection inter-îles `FUN_0042f8f7`.

Écarts confirmés, non corrigés :

- Traversée de pont (écart de représentation, gardé le 2026-11-03) : le port range l'ordre `+0x3c` dans `handoff_resume_action` et écrit l'action 9 pendant la traversée; le natif laisse `+0x3c` intact (`FUN_004210a9` n'écrit que `+0x2c/+0x30/+0x32`), finit en état 0 (0x41f928) et `FUN_004211bb` relance `+0x3c` au tick suivant (`+0x2c == 0 && +0x3c != 0`). Même ordre repris des deux côtés; seul le tick d'attente natif diffère. REA haiku `ev_0e9d3fbf…`, `ev_494492d3…`. Le bloc 0x41f9ba..0x41fa7b n'est pas lié aux ponts : fin d'action d'un floater de sous-type 4 (hors `FA_Cast` sauf drapeau 0x200, qu'il efface) → action 9 vers le site de son bâtiment `+0x0c` (`FUN_0045c3bb`, `ev_99c5ba25…`); porté le 2026-11-03 à côté du bloc sous-type 8 (0x41f935, Hall).
- Latch `+0x90` : corrigé le 2026-11-02 — en multijoueur (`multiplayer_session`, `DAT_004befe0`) le port ne verrouille plus et saute seulement le recruteur; `0x401d9d` = `FUN_00460072`, portée (`game_session_hand_back_player_holdings`: glyphes et objets d'inventaire remis sur des sites; `ev_3de14804…`, `ev_5cabff24…`, asm `ev_160fda2c…`). Écart: le port s'arrête quand aucun site n'est libre, le natif boucle sans fin. Le départ d'un joueur en cours de partie (`FUN_004121b7` cas 2) l'appelle aussi, via la commande synchronisée `GAME_COMMAND_HAND_BACK_PLAYER` mise en file par l'hôte, sauf si un autre joueur partage la tribu. Évènement 0xb (texte/son via 0x4013c0) non résolu.
- Presse-papiers : enregistrement automatique de tous les bâtiments d'entraînement (natif : seulement le bâtiment sélectionné).
- `IWFltInfo` affiché seulement en modes général/lieu (natif : tout mode après 0x3f); mort d'un floater dessinée comme `FUN_0042704b` le 2026-11-03 (cellules `die.shp`, corps masqué dès le tick 20, fixture `dying`). Après `FUN_0042f8f7` le mode vaut toujours 0 ou 3: l'écart ne se voit qu'en changeant de mode avec un floater sélectionné.

Doutes à trancher : sites « hidden pad » exclus du hit-test: prouvé le 2026-11-03 (garde de `FUN_00435581`: `+4 != 0`, bit joueur de `+0x22` ou `+0x10 != 0`, `ev_1e045b59…`); gardes CONSTR supplémentaires (`payload_12`, taille, réservation), `renderer_class != 0` refusant une tâche CONSTR, cas 1..0xd et 0x10..0x14 de `FUN_0041e569` non relus.

## Hors périmètre pour l'instant

Multijoueur natif exact (canaux DirectPlay, chat, cartes `ENDGNONP`; lobby, coopération et synchronisation par tours du remake portés, voir [multijoueur](../behavior/multiplayer.md)), `intro.avi` et commandes `nevada` (rotation/zoom clavier).

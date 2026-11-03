# Feuille de route

État au 2026-11-03. Reste à faire et limites connues : [TODO](TODO.md); portage acquis : [implemented.md](docs/implemented.md); preuves : `../behavior/` et [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md).

## Constat

- Décompilation : `index.jsonl` couvre 2410 procédures (1493 internes, 780 thunks, 123 externes, 14 runtime); 1507 décompilées, 903 exclues avec motif. L'inventaire est clos; le travail REA restant est ciblé (questions ouvertes ci-dessous), pas un balayage.
- Remake : ~44 k lignes C11 (`src/`), 27 programmes de test C + `tests/test_docs_integrity.mjs` + `tests/e2e/island_e2e.ps1` et `tests/e2e/fixture_e2e.ps1` (parties statiques générées, jamais les sauvegardes du joueur). Backlog (2026-11-03) : 71 items cochés, 1 ouvert (délai d'effacement du site source au déplacement de bâtiment, écart volontaire).

## Fait

- **Boucle de jeu** : déplacement manuel, ordres de bâtiment (`BC_*`, adoption `FUN_0042219e`), tâches (CONSTR, CHARGE, Obtain, SUPPLY, UpgSpread, Upgrade, Repair par liste de réparation, Hall type 4), retour des sous-types 4 et 8 en fin d'action.
- **Adversaires** : IA Léviathan (contamination, défense, production, attaques, riposte `FUN_00421d82`); pas de planificateur de tribu adverse dans le natif.
- **Fin de partie** : victoire par les sceaux (états 2..7), défaite « plus de floaters », écran de fin ([fin de partie](../behavior/end-game.md)).
- **Sauvegarde** : sauvegardes du remake et du jeu d'origine; une partie chargée ou reprise s'ouvre en pause, panneau d'options ouvert (choix du remake).
- **Interface** : parité des panneaux, polices, carte du monde, badges FLTINFO (dont badge d'état et scintillement des sorts), pause (île et carte figées, œil fermé), bâtiments de départ déjà construits.
- **Audio** : volume/pan par distance, sons de producteurs, d'île et d'écroulement.
- **Web et SDL** : [TODO_WEB.md](TODO_WEB.md) (toutes les étapes faites; build Web mono-joueur); partie réseau SDL↔SDL vérifiée en jeu.
- **Vérification** : fixtures statiques (`TONE_REBELLION_E2E_FIXTURE` : badges, enemy_hall, spell, obtain, dying, victory, messages, return) avec `TONE_REBELLION_SAVE_DIR`; `tests/e2e/fixture_e2e.ps1` et `tests/e2e/island_e2e.ps1` ([validation](docs/build-and-validation.md)).

## Reste

- Vérifier en jeu : Repair par liste, Léviathan (contamination de marqueur classe 1), séquence de victoire complète, survol des déclencheurs de trait (aucun atteignable dans les fixtures).
- Fin de partie : chemin multijoueur 0x15; relecture REA de `0x4239e9`/`0x46a92a`.
- Doutes REA : gardes CONSTR supplémentaires (`payload_12`, taille, réservation), `renderer_class != 0` refusant une tâche CONSTR, cas 1..0xd et 0x10..0x14 de `FUN_0041e569` non relus.
- Latch `+0x90` : évènement 0xb (texte/son via 0x4013c0) non résolu; le port s'arrête quand aucun site n'est libre (le natif boucle).
- Sauvegardes : celle du remake est refusée dès que `sizeof(GameSession)` change (pas de migration, dépend de l'ABI); le presse-papiers natif n'est pas relu des sauvegardes d'origine.
- Ménage local (ignoré par git) : copies `ToneRebellion_Remake_sdl - Copie*.exe`, `ToneRebellion_Remake*.zip`, `../hs_err_pid*.log`, `mci_debug.log`.

## Écarts gardés

- Traversée de pont : l'ordre `+0x3c` est rangé dans `handoff_resume_action`; reprise au même tick que le natif, sans écart observable.
- Déplacement de bâtiment : la source est effacée à la pose (natif : 8 à 16 ticks plus tard, `FUN_00450a71`); le délai dupliquerait le Hall dans la recherche du port.
- CONSTR : le port garde l'action 4 là où le natif porte l'action 5 (`FA_Build`), sans effet observé.
- Presse-papiers : rempli avec tous les bâtiments d'entraînement possédés (`game_session_clip_auto_register`); natif : seulement le bâtiment sélectionné. Retirer l'appel dans `island_view_render.inc` rend le comportement natif.
- Chargement en pause : choix du remake, `FUN_004576c7` ne pause pas.

## Hors périmètre

Multijoueur natif exact (canaux DirectPlay, chat, cartes `ENDGNONP`; le lobby, la coopération et la synchronisation par tours du remake sont portés, voir [multijoueur](../behavior/multiplayer.md)), `intro.avi` et commandes `nevada` (rotation/zoom clavier).

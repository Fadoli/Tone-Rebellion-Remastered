# Feuille de route

État au 2026-11-03. Reste à faire : [TODO](TODO.md); portage acquis : [implemented.md](docs/implemented.md); preuves : `../behavior/` et [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md).

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
- **Web et SDL** : portage Web fait en 8 étapes (1 surface portable `RenderSurface`, 2 services `platform_*`, 3 adaptateur SDL3, 4 cible Emscripten, 5 données utilisateur, 6 sauvegardes `IDBFS`, 7 audio navigateur, 8 build Web mono-joueur); partie réseau SDL↔SDL vérifiée en jeu.
- **Vérification** : fixtures statiques (`TONE_REBELLION_E2E_FIXTURE` : badges, enemy_hall, spell, obtain, dying, victory, messages, return) avec `TONE_REBELLION_SAVE_DIR`; `tests/e2e/fixture_e2e.ps1` et `tests/e2e/island_e2e.ps1` ([validation](docs/build-and-validation.md)).

## Écarts gardés

- Traversée de pont : l'ordre `+0x3c` est rangé dans `handoff_resume_action`; reprise au même tick que le natif, sans écart observable.
- Déplacement de bâtiment : la source est effacée à la pose (natif : 8 à 16 ticks plus tard, `FUN_00450a71`); le délai dupliquerait le Hall dans la recherche du port.
- CONSTR : le port garde l'action 4 là où le natif porte l'action 5 (`FA_Build`), sans effet observé.
- Presse-papiers : rempli avec tous les bâtiments d'entraînement possédés (`game_session_clip_auto_register`); natif : seulement le bâtiment sélectionné. Retirer l'appel dans `island_view_render.inc` rend le comportement natif.
- Chargement en pause : choix du remake, `FUN_004576c7` ne pause pas.

Hors périmètre et questions ouvertes : [TODO](TODO.md).

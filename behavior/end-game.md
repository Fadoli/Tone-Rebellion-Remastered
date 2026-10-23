# Écran de fin (état de menu 7)

Source: REA relu sur `FLOAT.EXE` (session rouverte avec accord utilisateur), sous-agent haiku. Evidence IDs: `ev_7cbf1350`, `ev_0d28fc54`, `ev_aadb178a` (vtables), `ev_987c0acd`, `ev_d54f1364`, `ev_526258f5` (enregistrement des états), `ev_181f9c08` (`FUN_0041b0d7`), `ev_7cd28ec2` (`0x45f849`, calcul du score), `ev_ae97542c`, `ev_8eaa374d`.

**Attention :** l'état de floater 7 (`order_progress == 3`, défense) n'a aucun rapport avec l'état de menu 7; une note précédente les avait confondus.

## Observations Ghidra
- Gestionnaire d'état 7 = `FUN_0044954d` (enregistré par `FUN_0046cbe0(7, …)` en `0x41c46f`); il n'agit que sur le message 1: charge `data\endgame.pal`, diffuse le message 1 aux fenêtres. Aucun son/musique, aucune entrée.
- Fenêtres: `STATBKG` (`ENDTEMP` cadre 0 plein écran), type 36 `EndGamePlayer` (paint `0x419a6b`), 37 `EndGameNonPlayer` (`0x41a8df`, trois cartes, joueur = index parmi les non-spectateurs), 38 `EndGameText` (`0x41b0d7`).
- `ENDGTEXT`: charge `endgame.txt` (enregistrements de 40 caractères, arrêt à `ENDSTORY`, lignes `*` vidées), défilement continu: pour 5 < tick < 500 la ligne i est centrée à y = 150 − (tick−5) + 16·i; compteur `DAT_004c2994` (+1 par peinture, ramené à `0x1f5` au-delà de 6000).
- `ENDGPLAYER`: planning de révélation par tick (250/300/350/400/425/450/500), clés `POINTS`, `IVISIT`, `GLYPHS`, `SHADSTR`, `FLOTTRIB`, `FLOTLOSS`, `TROFTHE`; score = somme de compteurs du joueur (`0x45f849`), grade min(9, total·10/1200).

## Port
`SCREEN_END_GAME` (`end_game_screen.inc`): fond `ENDTEMP` + palette `endgame.pal` et défilement de l'histoire. Police `BIGFONT` supposée, lignes dessinées seulement entièrement dans le cadre, fond `endgame.shp` cadre 0 de `ENDGTEXT` omis. Accès par F11 (aperçu du port), Échap pour quitter.

## Inconnues
Déclencheur natif de l'état 7 (aucun appelant trouvé de `FUN_0046c640(7)`), victoire/défaite, entrée pour quitter, musique, police/couleur du texte, cartes `ENDGPLAYER`/`ENDGNONP` (positions listées dans le rapport, valeurs lues dans les enregistrements `DAT_006191b8 + p·0x14a0`), `gamey.txt` non vérifié.

## Liste de dessin ENDGPLAYER / ENDGNONP (REA, ev_20fa7a7f…, ev_6f3b8544…, ev_7cd28ec2…; helpers `ev_48707155…`, `ev_6b8ef8ab…`, `ev_7c8ca8e4…`, `ev_c66b7542…`)
Observation, `FUN_00419a6b` (tests `tick >` stricts; surface locale = écran): >250 cadre `min(DAT_004bf118+5,7)` (31,20); >300 cadre `clamp(DAT_004bf11c,0,4)` (483,19); >350 cadre `35+joueur` (22,187) puis cadres `19+c` pour chaque bit c de `rec+0x8a`; >400 cadre 8 (439,188); >500 cadre `clamp(grade+9,9,18)` (239,141) et figure `FUN_00428191` (410×175). Textes (format → position): >250 `%d IVISIT:` y 131 et `%d POINTS` y 141, centrés sur 204; >300 `LSTREN[L+1]:` y 131 centré sur 1071; >350 `%d GLYPHS:` (266) + points (276); >400 `%d SHADSTR` (454,167), points (454,177) et quatre valeurs `%d` à y 236 (x 458/506/551/593); >425 `%d <tribu> FLOTTRIB` (454,258); >450 `%d <tribu> FLOTLOSS` (454,283) et `-points` (458,293); >500 nom du joueur (y 158), `TROFTHE`+tribu (172), `%d POINTS: RANK[grade]` (288), le tout centré sur 320.
Observation, `FUN_0041a8df` (carte NONP, sans tick, `p = idx`): cadre `clamp(grade+9,9,18)` à (−16,−19); nom `%s: %s` (10,2); `%d POINTS: RANK` (10,12); GLYPHS (10,122); SHADSTR (70,122); compteur de tribu (140,52/62/72); pertes (140,85/95/105).
Textes (`newtext.txt`): POINTS « Points », GLYPHS « Glyphes », SHADSTR « Créatures vaincues », FLOTTRIB « dans la tribu », FLOTLOSS « ont été perdus », TROFTHE « Tribu des », IVISIT « Iles visitées ».
Score (`0x45f849`): V = îles visitées, G = glyphes (bits 0..13), T = floaters de la tribu (≤100), F = pertes (`rec+0x1498`), L = niveau (0..4); p4 = 50·L, p3 = 100·V/14, p5 = 200·G/14, p7 = min(T,100), p8 = 500·F/280, p9..12 = S_k·W/200 (W = {420,300,480,600} tourné), total = p3+p4+p5+p7+p9..12 − p8 (≥0), grade = min(9, total·10/1200).
Incohérences/inconnues: récepteur ECX de `0x45f849`/`0x45f0cd`/`0x46562b` non établi; asset `DAT_0049c684` (écrivain introuvable; `endgame.shp` supposé); police et couleurs (`DAT_0049e140`); SHADSTR somme 8 shorts (joueur) contre 4 (carte).
**Port:** seuls l'emblème (35+joueur), les surcouches de glyphes, le cadre 8 et la ligne de glyphes sont dessinés; le reste attend ces inconnues.

## Déclencheur et sortie (REA, ev_0f5760d1…, ev_8089c623…, ev_584be7e8…, ev_f9dc4c11…, ev_6ac0d305…)
**Correction:** « aucun appelant de `FUN_0046c640(7)` » était incomplet. L'état 7 passe par la file de requêtes de fenêtres (`FUN_0046c1b4`, op 1 = SetState, vidée par `FUN_0046b752`); seuls `FUN_0041c46f`, `0x46b752` et `0x46c7b5` appellent `FUN_0046c640` directement.
Observation: deux enfilages `op 1, p2 = 7`: (a) `FUN_00464e4d` en `0x465505`, gardé par le mot `[rec+0x2cf9e] == 100` (le même test à `0xa0` enfile `SetState(0)`); (b) `FUN_0046a5b7` en `0x46a957`, gardé par `DAT_004c2b74 != 0` (porte de débogage) et `DAT_004befe0 == 0`. Aucun chemin de sortie par Échap/clic trouvé hors de ce `SetState(0)` à 160.
Interprétation: (a) est le déclencheur de jeu probable (compteur à 100), (b) une route de débogage. Inconnu: sens du mot `+0x2cf9e`, victoire/défaite, joueur observateur, touche de (b), musique, écrivains de `DAT_004bf118/11c`, récepteurs ECX du score. Le port garde donc F11/Échap comme aperçu.

## Récepteurs et entrées du score (REA, ev_55c28969…, ev_71770f5c…, ev_68aa402b…, ev_3d94d7af…, ev_34709f82…)
**Correction:** `FUN_00419a6b` et `FUN_0041a8df` n'appellent pas `0x45f849/0x45f0cd/0x46562b` directement (thunks `0x401217/0x402153/0x4019b5`). Observation: score en `0x419b2c`: `ECX = 0x6191b8 + DAT_0049f538·0x14a0` (joueur courant, non borné); carte `0x41aa78`: `ECX = 0x6191b8 + word[this+0x70]·0x14a0` (non borné pour le score, borné pour les autres appels); glyphes `FUN_0045f0cd` : ECX = enregistrement joueur; `FUN_0046562b` : ECX = objet constant `0x5EC218` + indice joueur en argument.
`DAT_004bf118` (4 lectures) et `DAT_004bf11c` (11 lectures dont le score `0x45f8b7`): aucune écriture par adresse directe trouvée; source des valeurs inconnue (ni « monde » ni `LSTREN` établis). Écrivains des courts `rec+0x147e..0x1498` et de `DAT_004befe0/ec/f0` non déterminés (écritures par pointeur, balayage d'octets nécessaire).
Conséquence: le score/rang/pertes ne peut pas être calculé fidèlement dans le port (compteurs d'évènements et niveau `L` sans source); non porté.

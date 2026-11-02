# Animation d'application des sorts (`FUN_0041760b`)

Observations Ghidra (REA sonnet/haiku 2026-11-02; `ev_821b6030…`, `ev_9605cef5…` `FUN_0041760b`; `ev_f5840e71…` `FUN_0041660b`; `ev_b26b69b4…` `FUN_00415063`; `ev_82a3e4f3…` `FUN_0041521a`; `ev_c398cf5f…`/`ev_00f81dc4…` `FUN_0041511b`; `ev_e6de5e26…` chargeur `FUN_004153b8`; `ev_b5cbda29…` `FUN_004239e9`; `ev_8cb30928…` `FUN_004181a6`; `ev_c9c2c66f…` `FUN_004182c8`).

- Création: `FUN_0042383d` appelle `FUN_0041660b` au 10e tick de FA_Cast. Instance de 0x14 octets sur les 32 emplacements partagés, à la position du lanceur, frame = première frame du niveau 0. Sprite de départ: `PSPELL`/`SSPELL`/`MSPELL`/`LSPELL`, ou `FLTARMOR` (1, 0x11), `FASTPROD` (2, 0xe, 0x15), `SACRIF` (7, 0x12), `KILLBEAS` (0xa), `DESTSUPP` (0x10), `ASCEND` (0x16). Le drapeau 2 (cible = site) est posé sauf pour 8 et le groupe sans cible 2, 7, 0xe, 0x11, 0x12, 0x14, 0x15.
- Pas d'image: une frame par tick impair. Une passe de N frames se termine au N-ième tick impair, et `FUN_0041760b` change de phase dans le même appel.
- Phase 0x100: une passe du sprite de départ. Ensuite:
  - 2, 0xe, 0x11, 0x14, 0x15 et 0x16 appliquent le sort (aucun trajet).
  - 7 et 0x12 jouent `BLASTWB` sur place (17 frames), puis appliquent.
  - Les autres sorts passent au trajet 0x200.
- Phase 0x200 (trajet): la position avance à chaque tick de SPEED vers la cible (`FUN_00414fbf`) et s'arrête quand la distance est inférieure à 6.
  - Sprite: `UPGRADE` (SPEED 8) par défaut, `FREEZELB` (15) pour 1, `LOCPROT` (5) pour 5, `BUILDTON` (5) pour 6, `HYPERHEAL` (20) pour 9.
  - Sans ligne SPEED, le chargeur met 5.
- Phase 0x400 (sprite de fin), puis `FUN_004239e9` applique le sort; c'est son seul appelant.
  - Sprites: `REPAIR` 0, `FLTARMOR` 1, `STOCKUP` 3, `BLDARMOR` 4, `LOCPROT` 5, `BUILDTON` 6, `HYPERHEAL` 9, `REVPLOT` 0xb, `FASTFLT` 0xc, `FREEZESC` 0xd/0x13, `BLASTWB` 0xf.
  - 5, 6 et 9 jouent leur second niveau LEVELFRAMES.
  - 0x13 joue `FREEZESC` à rebours.
- Cas particuliers:
  - 8: après la passe de départ, un compteur avance à chaque tick; le sort est appliqué à 0x44 et l'instance libérée à 0x7a.
  - 0xa: le premier appel tire trois `-rand(30)` (`FUN_00467260`); le sort s'applique quand les trois compteurs, avancés de 1 par tick, dépassent 75.
  - 0x10: pas de passe de départ. Il part en trajet (frames 0..3, SPEED 5), puis joue les frames 14..17 et applique.
- `FUN_004239e9` exige que le lanceur soit toujours en FA_Cast (+0x2c == 0x13) avec le drapeau 0x200 à zéro.
- Son: une seule fois, au premier tick, avec le `SOUND` du sprite de départ. Les sprites des phases suivantes ne sonnent pas.

Port: `game_session_schedule_cast_effect_step` / `game_session_tick_cast_effects` (`game_session_combat.c`) et `game_session_cast_effect_visual` (`game_session_build_events.c`), avec 23 visuels chargés par `island_assets.inc`.

Dessin (`FUN_004182c8`, REA haiku 2026-11-02, `ev_3d2e004f…`):
- Cas général: frame [3] en ([5], [6]), miroir si bit 0 de [8] (lanceur tourné à gauche).
- `KILLBEAS`: trois sprites à x = flotteur cible [1] − 5 + 5k, compteurs [5], [6], [3]. Pour c ≤ 63: y = cible − 320 + 5c, frame (c non signé mod 13) + 13 quand le bit k de [2] est nul. Pour 64..73: y = cible, frame c − 38. Pas de miroir.
- `FAROBT`: sur le site cible, compteur c = [5]:
  - 3..23: frame 0, y − 80, masque `FUN_00410bd2` niveau c/3.
  - 24..53: frame 0, y − 128 + 2c.
  - 54..67: frames 1..7, y − 20.
  - 68..97: frame 7, y + 116 − 2c.
  - 98..121: frame 7, y − 80, niveau 8 − (c − 98)/3.
  - À c = 0x44, [2] = site +0x24; l'objet (`FUN_0040adb5`, TRIGGERS frame sel − 5) est dessiné 20 plus bas avec le même niveau.

Limites et interprétations:
- `FUN_0040adb5` (`ev_2500d2d1…`): les sélecteurs 1..3 lisent `DAT_0049aca8..acb0`, qui valent 0xffff dans l'image (`ev_d189bd05…`); aucun écrivain n'a été trouvé, seulement trois lecteurs (`FUN_0040adb5`, `FUN_0040bf98`, `FUN_0040d48c`). Aucune valeur 2 ou 3 de site +0x24 n'est connue. Le port ne dessine rien pour ces sélecteurs.
- `KILLBEAS` (`ev_4615c5ce…`, `ev_8072182a…`): [2] = 0 à la création; au premier appel, `FUN_0041760b` tire [2] = `FUN_00467260(8)` avant les trois `-rand(30)` ([5], [6], [3]).
- Les plages de `FUN_00467260(8)` et `FUN_00467260(30)` sont reprises de `tone_rng_bounded`.

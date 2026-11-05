# États runtime des floaters

Passe REA statique du 2026-11-04 (sous-agents haiku 5.5, sans exécution). Elle clôt les questions ouvertes du [TODO](../ToneRebellion_Remake/TODO.md) sur `FUN_0041e569`, les gardes CONSTR, l'état 10, `FUN_0042704b` et les appelants des ordres de bâtiment.

## Table de `FUN_0041e569`

Observation (`ev_89fd8492…` assembleur, `ev_56cebbc9…` table, `ev_8578fcc7…` pseudocode) : `MOV ECX,[rec+0x2c]; SUB ECX,1; CMP 0x14; JA 0x41f918; JMP [idx*4+0x41fd03]`. Le champ d'état est le dword `+0x2c`; la table compte 21 entrées. `FUN_00466ce2` appelle la routine pour chaque floater du tableau `0x6137b8` (base monde `0x5ec218 + 0x275a0`, pas `0x4c`); il n'existe pas d'autre appelant ni de pointeur vers la routine (`ev_5088a0e4…`).

| État | Cible | Rôle (interprétation du pseudocode) |
|---|---|---|
| 1 | 0x41eb0e | type 4 sous-type 9 seulement : pose `slot+0x14 = 4`, `FUN_00453a5f`, `FUN_00467101` |
| 2 | 0x41f042 | séjour : compteur `+0x34` jusqu'à 10, pas vers le site |
| 3 | 0x41eea4 | retrait : seuil 0x14, `FUN_00452c31`/`FUN_00452eac` |
| 4 | 0x41e975 | dépôt : seuil 0x14, `FUN_004503bd(+0x18, 1, joueur)` |
| 5 | 0x41f629 | construction : `FUN_004527ee(+0x30, joueur)` |
| 6, 7 | 0x41ebbc | charge (voir [charge](floater-charge.md)) |
| 8 | 0x41f209 | fin quand `FUN_004208eb(site, +0x32) != -1` |
| 9 | 0x41ed15 | tous les 8 ticks : `FUN_00420829`, sinon `FUN_00420d97(4)` |
| 10 | 0x41f8eb | minuterie : `+0x34` décrémenté, fin sous 1 |
| 11, 12 | 0x41f66c, 0x41f6f5 | `FUN_00450385` + `FUN_0045c772` / `FUN_0045c797`, puis `FUN_0045c470(site)` |
| 13 | 0x41f77e | Obtain : `FUN_004502dc`, objet 5..0x21 en `+0x18`, `FUN_00452a15` |
| 14 | 0x41e93d | minuterie gardée, fin sous 1 |
| 15, 16 | 0x41ed86 | coût `FUN_00420721` contre distance `FUN_004672a6`; type 0xf : bit 0x10 du site |
| 17 | 0x41f23d | attente 0x3c puis 0x78, choix de l'emplacement le plus proche |
| 18 | 0x41f89b | réparation : `+0x34` jusqu'à 0x27, `FUN_004509da(1)` |
| 19 | 0x41f8db | sort : fin = retour de `FUN_0042383d` |
| 20 | 0x41f918 | cible par défaut, sans effet |
| 21 | 0x41f7ea | 1 : `FUN_00416a9a(5)`; 0x19 : type 4 `FUN_00467101`, sinon sous-type 8; 0x32 : fin |

Le remake a déjà une branche pour chacun de ces états. L'état 20 reste sans effet.

## État 10 : aucun producteur

Les écritures littérales de 0xa dans `+0x2c` ont été cherchées sous toutes les formes (dword, word et octet; disp8, disp32 et SIB; adresse absolue `0x6137e4`) : aucune occurrence (`ev_85864224…`, `ev_e5130f89…`, `ev_b4b63482…`, `ev_a65be9d6…`). Toutes les écritures de `+0x2c` par registre ont été lues, une fonction propriétaire à la fois :
- `FUN_004211bb` écrit 1..9, 0xe, 0xf, 0x10 et 0x15, et recopie `+0x3c` seulement quand il vaut 11, 12, 13 ou 19 (`ev_3477c421…`).
- Le seul compteur qui atteint 10 est celui de `FUN_00450a71`. Il porte sur un enregistrement de site (table `0x5ec640`, pas de `0x60`), pas sur un floater.
- La copie de `FUN_0045343b` va d'un site à un autre.

**Conclusion :** aucun floater n'entre dans l'état 10. La branche du remake (`game_session_tick_timed_movement_state`) reproduit donc un chemin mort; elle reste en place parce qu'elle ne coûte rien.

## Gardes CONSTR

La seule branche de `FUN_00422031` pour le type 5 (`ev_bd805382…`, `ev_7b65b088…`) procède ainsi :
1. Elle refuse la tâche si `FUN_004526de(payload, joueur)` échoue. Cette fonction teste que le propriétaire `+0x14` du site vaut -1 ou le joueur, que l'item `+0x10` vaut 0 ou 1, que le bit du joueur est posé dans `+0x22`, et que l'entretien du PAD (`+0x0c`) ne dépasse pas le niveau du joueur.
2. Elle accepte si l'ouvrier porte du Build Tone (`+0x18 == 1`), ou si `FUN_00452794` constate que le stock de Build Tone du site couvre le coût `+0x04`.
3. Sinon, elle accepte seulement si `FUN_00420dbd` trouve une source de Build Tone.

Il n'y a ni test de taille, ni réservation, ni test de classe de site. `FUN_004459e6` ne fait que l'affichage. `worker_admitted_to_task` et `game_session_build_target_available` portent déjà ces tests, la question est close.

## `FUN_0042704b` : préfixe et voiles

- **Pas de préfixe `x` :** la fonction n'en emploie aucun. Le seul 0x78 est un plafond du short `+0x34`, et la seule chaîne de format est `%02d`, qui forme le nom de forme des objets 5..0x21 portés (`ev_5cc7f5cc…`). Le nom `xSpores` du panneau vient du texte, pas de ce dessin.
- **Badges et jauges :** ceux qui sont portés concordent avec le binaire ([info floater](island-floater-info.md)). Les jauges, toutes plafonnées à 10, se calculent ainsi :
  - santé : `10 * max(+0x20, 0) / FUN_00420f28(rec)` ;
  - charge : `10 * max(+0x22, 0) / FUN_00464242(...)+8` ;
  - rang : `10 * max(FUN_0041ff56, 0) / 11.0`.
- **Voile `spl11` du propriétaire 4 :** il est lu dans `DAT_0061fa2e[rec+0x0e]` (île, si l'indice est dans 0..14), la même valeur que le badge 0x1e au-delà de 100. Le voile se dessine quand cette valeur est dans 1..0x15, avec la frame `(0x16 - v) / 2`. Le tableau n'ayant aucun écrivain connu, le voile ne se dessine jamais, comme le badge 0x1e. Il n'est pas porté.
  - **Passe du 2026-11-05 (REA haiku) :** le tableau est un mot signé par île (15 entrées), lu en absolu par `FUN_00420991` (`0x4209e7`) et `FUN_0042704b` (`0x42776b`). La recherche d'octets `2e fa 61 00` ne trouve que ces deux lectures (`ev_d0a047ec…`), et les octets du fichier valent zéro (`ev_ad9230d6…`). Aucune adresse `0x61xxxx` n'est poussée comme destination de copie, et aucun `rep stos/movs` n'a de destination constante dans la zone.
  - **Conclusion :** le tableau reste à zéro. Le remake, qui ne dessine ni le badge ni le voile, a donc le même rendu que l'original ; ce n'est pas un écart. Seule limite : une copie de bloc à destination calculée n'est pas exclue.
- **Argument `param_5` :** il vaut 1 pour tous les appelants sauf `FUN_00428191`, qui passe 0 et supprime donc badges, barres et voile. `FUN_00405265` est le blitter avec mise à l'échelle et rotation (utilisé pour le miroir); `FUN_00410bd2` est le blitter RLE tramé, mode 8 opaque pour tous les appelants.

## Message 0x47 et `IWLocInfo`

- **Classe d'`IWLocInfo` :** la fabrique de fenêtres `FUN_0046cd22` traite le WINTYPE 27 (0x1b) par `new(0x84)` et le constructeur `FUN_0043ffc2`. Celui-ci pose la vtable `0x494458`, dont l'entrée 1 (gestionnaire de messages) est `FUN_0044003d`. Ce gestionnaire traite les messages 1, 2, 6, 7, 10, 0x350b et 0x350d et passe les autres à la base `FUN_004293c6` (messages 1..12). Il n'a pas de cas 0x47.
- **Émetteur :** la vue d'île `ISLEVIEW` (WINTYPE 10, vtable `0x4942a8`, gestionnaire `FUN_004337d9`) envoie `0x47(site survolé +0x17a, 0)` quand ce site change. Le site envoyé est un indice, -1 quand aucun site n'est survolé. Le message part par `FUN_0042970c` vers MASTER, c'est-à-dire le gestionnaire de l'état courant du WINMGR (`0x62a780 + 0x206c + état*0x130`). Pour l'état 3, `FUN_0041c46f` y enregistre `FUN_0042fa0f` (thunk `0x401b8b`).
- **Cas 0x47 de `FUN_0042fa0f`** (table `0x431d30`, entrée 20, `0x43142e`) : si un bâtiment est saisi (`0x61a578 + joueur*0x14a0` non nul), il envoie le message 14000 (`0x36b0`) à `IWHallMove` puis à `IWMove`, avec le site `0x5ec640 + i*0x60` survolé ou NULL.
- **`IWMove`/`IWHallMove`** (WINTYPE 34, `FUN_00441caf`, gestionnaire `FUN_00441d3e`) : le message 14000 range le site en `+0x74` et pose `+0x34 = 1`.
- **Dessin de `FUN_00441e8b`** (`ev_8c7540d8…`, `ev_a14c5876…`) : il dessine les frames de THBUTT suivantes, sans texte :
  - 5, toujours ;
  - 8, quand le contrôle a le focus souris ;
  - pendant une saisie, si `DAT_00630a3e < 0x140` (souris dans la vue d'île) ou si le contrôle a le focus : 7, par la table de remappage `FUN_00404c5a`, quand `FUN_0045f337` accepte le site `+0x74` ; sinon 6, croix rouge.

**Port :** le remake dessine ces frames 5, 6, 7 et 8. La frame 7 est dessinée sans remappage. `game_session_location_move_target_ok` porte le test de `FUN_0045f337`. L'indication anglaise que le remake avait inventée est retirée. Vérifié en jeu sur la fixture `badges` (bâtiment posé avec F6) : croix rouge sur le ciel, anneau sur un site libre.

## Appelants et corps restants

- **Appelants des ordres de bâtiment :** `FUN_0045d867`, `FUN_0045d8b2` et `FUN_0045dcf4` ne sont appelés que par `FUN_00465793`, via leurs thunks (`0x4012f3`, `0x4024e1`, `0x40249b`). `FUN_0045ccce` ne l'est que par `FUN_0045343b` (déplacement de bâtiment, via `0x4019d3`). Aucun pointeur de données ne vise ces fonctions (`ev_3d4e22b6…`, `ev_31758278…`, `ev_9b494953…`, `ev_30f93ceb…`).
- **`FUN_004207f2` :** renvoie l'enregistrement de bâtiment `0x6192b0 + joueur*0x14a0 + (+0x0c)*100`, ou NULL si `+0x0c == -1` (`ev_4ba95749…`).
- **`FUN_004509da(p)` :** décrémente les stocks `+0x28`/`+0x2a` sans descendre sous 0, ajoute `p` à `+0x34` et plafonne par `FUN_00450978` (`ev_ee4284d8…`). Le remake fait de même.
- **`FUN_0042383d` :** tant que le sort est en cours, il avance le lanceur vers sa cible quand celle-ci est à portée. Quand le sort est fini (bit 0x200), il ajoute 5 à `+0x08` (`ev_0c23a222…`). Le remake fait de même.

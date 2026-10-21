# Audio du jeu

## Source vérifiée

Le dossier `C:\toneIso\THING2` est la copie locale décompressée de la partie audio du disque. Il contient 16 fichiers WAV et une vidéo `INTRO.AVI`. Les 16 fichiers WAV correspondent exactement aux 16 déclarations `tune` de `C:\git\ToneRebellion_Raw\original_content\sound.txt`.

Propriétés observées dans les en-têtes RIFF/WAVE : PCM (format code 1), stéréo, 22 050 Hz, 8 bits par échantillon. La taille combinée des WAV est de 246 029 578 octets. Aucun média n'a été copié ni modifié.

## Correspondance des pistes

Les identifiants et noms de fichiers viennent des lignes `tune` de `sound.txt`; les appels de fonctions sont des observations Ghidra. Cette correspondance ne décrit pas à elle seule toutes les transitions temporelles du jeu.

| Identifiant `sound.txt` | Fichier `THING2` | Usage observé dans FLOAT.EXE |
|---|---|---|
| `tribe0` | `PROTECT.WAV` | Piste de la tribu 0 après chargement / transition d'île |
| `tribe1` | `SEEKERS.WAV` | Piste de la tribu 1 |
| `tribe2` | `MYSTICS.WAV` | Piste de la tribu 2 |
| `tribe3` | `LIFEGIVE.WAV` | Piste de la tribu 3 |
| `act1` | `ACT4.WAV` | Piste d'acte 1 (correspondance explicitement inversée dans `sound.txt`) |
| `act2` | `ACT3.WAV` | Piste d'acte 2 |
| `act3` | `ACT2.WAV` | Piste d'acte 3 |
| `act4` | `ACT1.WAV` | Piste d'acte 4 |
| `start` | `START.WAV` | Demandée une fois au lancement de la boucle principale par `FUN_0041c46f` (`0x41c46f`); le titre demande ensuite `ambi1` |
| `ambi1` | `AMBIENT1.WAV` | Demandée par `FUN_004489c0` pour l'écran titre |
| `ambi2` | `AMBIENT2.WAV` | Déclarée; appel/transition exacte à préciser |
| `ambi3` | `AMBIENT3.WAV` | Déclarée; appel/transition exacte à préciser |
| `ambi4` | `AMBIENT4.WAV` | Déclarée; appel/transition exacte à préciser |
| `levi` | `LEVIATAN.WAV` | Demandée par `FUN_00470fe7` dans le cas Leviathan |
| `winend` | `WINNER.WAV` | Déclarée; déclenchement exact à préciser |
| `loosend` | `LOSEND.WAV` | Déclarée; déclenchement exact à préciser |

`FUN_004576c7` demande `tribe%d` après chargement d'une sauvegarde. `FUN_004702d9` arme les 15 flags d'entrée musicale; `FUN_00470fe7` consomme le flag de l'ID de realm et choisit `tribe%d`, `act%d`, `levi`, ou, pour les autres realms, tire une valeur LCG et n'appelle `FUN_0046ff6f` que si son bit 0 vaut 1. Cette dernière sélectionne parmi neuf entrées et évite de répéter l'index précédent. `FUN_004337d9` construit les chemins `island%02d` depuis le même ID de forme stocké par `WORLDPOS.TXT`; le remake utilise ce `shape_id` comme ID du realm pour la transition. `FUN_00459e84` initialise DirectSound et ses buffers.

## État de l'intégration du remake

Le prototype ouvre `ambi1` dans les menus/cartes puis, à la première entrée d'un realm, applique la table de `FUN_00470fe7` à partir du `shape_id` de `WORLDPOS.TXT`. Il consomme aussi le tirage de gate des realms ordinaires : une valeur paire conserve la piste active sans changement, une valeur impaire consomme ensuite `FUN_0046ff6f`. Le masque des 15 transitions est conservé pendant la session et le LCG partagé continue après les tirages de génération actuellement modélisés. Les tirages de démarrage absents du modèle restent une limite de séquence exacte. Le lecteur WinMM MCI boucle les pistes et résout `THING2` dans cet ordre : variable d'environnement `TONE_REBELLION_THING2`, dossier `THING2` adjacent à l'exécutable, puis `C:\toneIso\THING2`. La source d'origine utilise DirectSound.

## Effets sonores

`sound.txt` déclare séparément les effets (par exemple `button`, `fltbuild`, `levbuild` et `bridge`) sous `data\\*.wav`. Les effets proviennent de membres de `TONE01.COB`, pas des 16 pistes musicales de `THING2`. `FUN_004293c6` demande l'effet `button` lors d'un clic UI quand le son est activé. `FUN_00416a9a` associe l'événement 2 à `fltbuild` ou `levbuild` selon le propriétaire de l'objet (`param_2[5] == 4` choisit `levbuild`); `FUN_004527ee` n'émet cet événement qu'après validation du site et application réussies (Evidence `ev_28a2577cfeedddf9d6610a6cfc350a5cb84a992fdc89a98a2b03ac6e86e27d72`, `ev_ff5099639bbdcb8c257ae4e8f690ea98f0ebdf4321753ff832e66ba4dc11d800`). L'événement 3 de `FUN_00416a9a` crée une instance d'effet `bridge` (`ev_7bb81f291a259a90f39323a69a51aca642dbb8d1163a9c7ef8c3299fab5a5344`); `FUN_004669bd` l'émet lorsqu'il active le lien entre deux records pont appariés (`ev_b30589ad8e8dc4fd8f9e7c50be1117bbafa5e3808f994368fd7124a2c0d4ddc4`). Le remake charge maintenant `BUTTON.WAV`, `FLTBUILD.WAV`, `LEVBUILD.WAV` et `BRIDGE.WAV`. La simulation met les événements 2/3 en file au succès d'une construction ou à la première activation du lien; l'adaptateur les joue dans l'ordre, avec `LEVBUILD` réservé au propriétaire 4.

L'événement 0 de `FUN_00416a9a` choisit `fltbirth` ou `levbirth`; `FUN_004532e2` l'émet lors de la création des floaters Leviathan par leurs bâtiments (`ev_0f4988bf277009e5657d38ce4b4a560f2ccc81ed14bd42320088bd505b19dd5d`, `ev_7463fd4a8f96b3891fabce4a95247d93d5ef025e8e922fd07737e6ae21c36cf9`). Le remake charge maintenant aussi `data\\levbirth.wav` de `TONE01.COB` et choisit le son de naissance à partir du propriétaire de l'événement.

## Effets sonores des sorts (REA, port partiel)

Observation (ev_ad61fbe1…, ev_4e6ad21d…, ev_8072182a…, ev_0c23a222…): la fonction de lecture est
`FUN_0045afb9(index, volume, pan)` (saute le redémarrage si le son joue déjà, sauf
`fltdeath`/`levdeath`). Les sons d'effets viennent de données: `FUN_004153b8` parse
`effects.txt` (stride 0x30, `SOUND` résolu par `FUN_0045b34c` en `+0x28`); le seul
appel par chaîne littérale est `button` (`FUN_004293c6`). Une instance d'effet joue son
`SOUND` à son premier tick (`FUN_004181a6`, `+0x08` de l'instance = `DAT_0049f53c`, qui multiplie aussi le pas d'île `0x29e8` dans `FUN_0042fa0f`: l'île affichée; volume et
pan selon la distance à l'écran, `FUN_0045b24d`). `FUN_0042383d` lance
`FUN_0041660b` au compteur 10 d'un FA_Cast; l'effet vaut: kinds 1 et 17 FLTARMOR,
2/14/21 FASTPROD, 7/18 SACRIF, 10 KILLBEAS, 16 DESTSUPP, 22 ASCEND, autres kinds
l'effet par tribu PSPELL/SSPELL/MSPELL/LSPELL (même nom pour le `SOUND`).
Port: `GAME_SESSION_AUDIO_CAST` mis en file au dixième tick de cast
(`game_session_cast_sound_id`), joué quand l'île du lanceur est l'île affichée, volume et pan
constants. Non porté: atténuation et pan par distance, les autres effets
(bullets, impacts, realms, îles, blowup/crumble, upgrade, repair, stockup,
buildton…: les noms apparaissent seulement comme références d'effet, aucun site de
lecture résolu), règle « ne pas redémarrer un son en cours » (PlaySound remplace).
Inconnues: le mapping des lignes de `spells.txt` aux kinds (supposé identique à
`game_session_cast_kind_for_action`), `DAT_0049f53c`/`DAT_0062d172`.

### Événements d'effets sonores restants (REA, pas de port)

Observation (ev_89e5ca34…, ev_9320c33f…, ev_f6f67f5b…, ev_c57eb490…, ev_734ec2ad…):
trois allocateurs créent des instances d'effet: `FUN_0041660b` (casts, porté),
`FUN_00416a9a` (événements monde 0..12) et `FUN_00416342` (bullets et impacts,
appelé depuis `FUN_00450a71`, non décompilée). Événements de `FUN_00416a9a`:
0 naissance (`FLTBIRTH`/`LEVBIRTH`, `FUN_004532e2`), 1 mort (`FUN_004204bc`),
2 construction (`FUN_004527ee`, `FUN_00452859`), 3 pont (`FUN_004669bd`) — déjà
portés —, 4 fonctionnalité d'île (`FEATnn`, `FUN_004503bd`), 5 `JOIN6` (sans SOUND),
7 `CRUMBLE` (appel depuis `FUN_0042fa0f`, déclencheur non résolu), 9 curseur/carte
(flag 0x80, `FUN_0043b9af`, `FUN_0043bebe`). Les effets `SoundOnly` d'`effects.txt` sont
les huit précédents plus `FEAT00..FEAT13` (tarzus, crystal, cephean, pangir, dreenbog,
onsama, palomon, tonal, core, frenza, lethe, mymus, morfid, norasten). Le nom
`FEAT%02d` prend son indice dans `DAT_005eebf8[(short)record+8 * 0x14f4]`, table
nulle dans l'image (remplie à l'exécution, écrivains non décodés); `record+8` joue
aussi le rôle de propriétaire: le son ne sort que si `record+8 == DAT_0049f53c` et
`DAT_0062d172 == 3`. Aucun effet `blowup`, `bullet`, `upgrade` ou `repair` n'est un
événement ou `SoundOnly`: `upgrade`, `repair`, `stockup`, `buildton`… sont des phases
de la même instance de cast (`FUN_0041760b`, indicateurs 0x100/0x200/0x400 et
parité `DAT_00618e44`, condition de pose non résolue).
Raison de l'absence de port: l'indice `FEATnn`, le déclencheur de `CRUMBLE`, les
conditions de phase des effets de cast et `FUN_00450a71` (bullets/impacts) ne sont
pas établis; associer les îles à `FEAT` par ordre de noms serait une supposition.

Correction (REA, ev_734ec2ad…, ev_9320c33f…): `DAT_0049f53c` est l'île vue (index
multiplié par `0x29e8`, le pas d'île, dans `FUN_0042fa0f`), pas le joueur; le champ
`+0x08` d'une instance est l'île (`+0x0e` du lanceur, `in_ECX[2]` dans `FUN_00450a71`). Le port
compare donc l'île du lanceur à `g_menu.selected_map_island` sur l'écran île, et
non plus la tribu. Le nom `FEATnn` prend son indice dans la table par île
`DAT_005eebf8` (pas `0x14f4`, clef `record+8` = île): son contenu reste inconnu.
Bullets/impacts (`FUN_00450a71` = tick des items producteurs/défenses,
`FUN_00416342`): impact `PHYIMP/SUPIMP/ETHIMP/NATIMP` choisi par `item & 3`, sons
`PREALM/SREALM/EREALM/NREALM`; bullets via l'enregistrement d'attaque `+0x0e`
(table atteff non lue), 13 effets BULLET tous avec SOUND; tir à `+0x42 == rec+4`
(30 par défaut). Non porté: le remake ne modélise pas ces bullets d'item.

### `CRUMBLE` et appelants de `FUN_00416a9a` (REA, pas de port)

Observation (ev_ed75141a…, ev_da0c5175…): `CRUMBLE` (événement 7) est lancé depuis le
cas `param_1 == 5` de `FUN_0042fa0f`, sous-code `param_2 == 7`: `param_3` contient
l'île (`>> 16`) et l'index de site (`& 0xffff`), l'enregistrement est
`0x5ec640 + site*0x60 + île*0x29e8`, et le son ne part que si l'île est l'île
affichée. Le sous-code 8 sélectionne un site, le sous-code 1 efface un curseur.
Appelants complets de l'allocateur: événement 0 `FUN_004532e2`, 1 `FUN_004204bc`, 2
`FUN_004527ee` et `FUN_00452859`, 3 `FUN_004669bd`, 4 `FUN_004503bd`, 5 `FUN_0041e569`
(état 0x14, `JOIN6`), 7 `FUN_0042fa0f`, 9 `FUN_0043b9af` et `FUN_0043bebe`; aucun
appel littéral ne passe 6, 8, 10, 11 ou 12.
Interprétation non prouvée: commande de l'île vue (peut-être l'affichage d'un site
détruit). Le port destruit un bâtiment à la fin du compteur létal
(`game_session_animation.c`, événement monde 8), mais la correspondance avec la
commande native 5/7 n'est pas établie (l'émetteur de `(5, 7, paquet)` est inconnu), donc
aucun son n'est branché.

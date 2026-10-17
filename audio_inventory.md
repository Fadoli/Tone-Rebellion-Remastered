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

`FUN_004576c7` demande `tribe%d` après chargement d'une sauvegarde. `FUN_004702d9` arme les 15 flags d'entrée musicale; `FUN_00470fe7` consomme le flag de l'ID de realm et choisit `tribe%d`, `act%d`, `levi`, ou délègue à `FUN_0046ff6f`. Cette dernière sélectionne parmi neuf entrées, en évitant de répéter l'index précédent. `FUN_004337d9` construit les chemins `island%02d` depuis le même ID de forme stocké par `WORLDPOS.TXT`; le remake utilise ce `shape_id` comme ID du realm pour la transition. `FUN_00459e84` initialise DirectSound et ses buffers.

## État de l'intégration du remake

Le prototype ouvre `ambi1` dans les menus/cartes puis, à la première entrée d'un realm, applique la table de `FUN_00470fe7` à partir du `shape_id` de `WORLDPOS.TXT`. Il conserve le masque des 15 transitions consommées pendant la session et utilise le LCG partagé après les tirages de génération actuellement modélisés pour la liste aléatoire de `FUN_0046ff6f`. Les tirages de démarrage absents du modèle restent une limite de séquence exacte. Le lecteur WinMM MCI boucle les pistes et résout `THING2` dans cet ordre : variable d'environnement `TONE_REBELLION_THING2`, dossier `THING2` adjacent à l'exécutable, puis `C:\toneIso\THING2`. La source d'origine utilise DirectSound.

## Effets sonores

`sound.txt` déclare séparément les effets (par exemple `button`, `fltbuild`, `levbuild` et `bridge`) sous `data\\*.wav`. Les WAV d'effets observés, dont `data\\button.wav`, sont des membres de `TONE01.COB`; ils ne font pas partie des 16 pistes musicales de `THING2`. `FUN_004293c6` demande l'effet `button` lors d'un clic UI quand le son est activé. `FUN_00416a9a` crée les événements `fltbuild`/`levbuild` et les associe à la construction d'une unité, et `FUN_004527ee` appelle cet événement après validation de l'objet. Le remake joue `BUTTON.WAV` sur clic; les effets d'événement gameplay ne sont pas encore intégrés.

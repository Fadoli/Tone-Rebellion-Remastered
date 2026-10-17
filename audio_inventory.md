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

`sound.txt` déclare séparément les effets (par exemple `button`, `fltbuild`, `levbuild` et `bridge`) sous `data\\*.wav`. Les effets proviennent de membres de `TONE01.COB`, pas des 16 pistes musicales de `THING2`. `FUN_004293c6` demande l'effet `button` lors d'un clic UI quand le son est activé. `FUN_00416a9a` associe l'événement 2 à `fltbuild` ou `levbuild` selon le propriétaire de l'objet (`param_2[5] == 4` choisit `levbuild`); `FUN_004527ee` n'émet cet événement qu'après validation du site et application réussies (Evidence `ev_28a2577cfeedddf9d6610a6cfc350a5cb84a992fdc89a98a2b03ac6e86e27d72`, `ev_ff5099639bbdcb8c257ae4e8f690ea98f0ebdf4321753ff832e66ba4dc11d800`). L'événement 3 de `FUN_00416a9a` crée une instance d'effet `bridge` (`ev_7bb81f291a259a90f39323a69a51aca642dbb8d1163a9c7ef8c3299fab5a5344`); `FUN_004669bd` l'émet lorsqu'il active le lien entre deux records pont appariés (`ev_b30589ad8e8dc4fd8f9e7c50be1117bbafa5e3808f994368fd7124a2c0d4ddc4`). Le remake charge maintenant `BUTTON.WAV`, `FLTBUILD.WAV` et `LEVBUILD.WAV`; le placement sélectionne l'effet selon `owner_id` comme dans `FUN_00416a9a`. Les propriétaires joueur 0–3 utilisent `FLTBUILD`; `LEVBUILD` est prêt pour le propriétaire 4, mais l'UI actuelle n'expose pas encore cette faction. Le clic accepté est encore traité comme achèvement immédiat, donc le son n'a pas le timing différé de la simulation originale. L'effet `bridge` n'est pas encore déclenché car les commandes de progression/activation du pont ne sont pas raccordées au gameplay du remake.

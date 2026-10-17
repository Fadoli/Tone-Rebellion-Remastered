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
| `start` | `START.WAV` | Déclarée; appel/transition exacte à préciser |
| `ambi1` | `AMBIENT1.WAV` | Demandée par `FUN_004489c0` pour l'écran titre |
| `ambi2` | `AMBIENT2.WAV` | Déclarée; appel/transition exacte à préciser |
| `ambi3` | `AMBIENT3.WAV` | Déclarée; appel/transition exacte à préciser |
| `ambi4` | `AMBIENT4.WAV` | Déclarée; appel/transition exacte à préciser |
| `levi` | `LEVIATAN.WAV` | Demandée par `FUN_00470fe7` dans le cas Leviathan |
| `winend` | `WINNER.WAV` | Déclarée; déclenchement exact à préciser |
| `loosend` | `LOSEND.WAV` | Déclarée; déclenchement exact à préciser |

`FUN_004576c7` demande `tribe%d` après chargement d'une sauvegarde. `FUN_00470fe7` demande selon le contexte `tribe%d`, `act%d` ou `levi` lors d'une transition d'île. `FUN_00459e84` initialise DirectSound et ses buffers. Les pistes sont donc maintenant disponibles pour le remake; l'équivalence du streaming/bouclage et les transitions restent à implémenter.

## État de l'intégration du remake

Le prototype ouvre actuellement le thème `ambi1` à l'écran titre et le conserve dans les écrans de configuration/carte; à l'entrée d'une île, il passe à `tribe%d` selon la tribu sélectionnée. Il utilise WinMM MCI en boucle et résout `THING2` dans cet ordre : variable d'environnement `TONE_REBELLION_THING2`, dossier `THING2` adjacent à l'exécutable, puis `C:\toneIso\THING2`. Ce choix est une adaptation au remake; la source d'origine utilise DirectSound. Les branches `act%d`/`levi` de `FUN_00470fe7` ne sont pas encore reproduites, car le type/realm musical de l'île n'est pas dans le modèle runtime.

## Effets sonores

`sound.txt` déclare les identifiants d'effets dans une section distincte, tandis que les fichiers WAV d'effets sont présents dans le corpus local `original_content` et/ou les archives de ressources. Ils ne sont pas interchangeables avec les 16 pistes musicales de `THING2`. Le remake ne joue actuellement que `BUTTON.WAV` sur clic.

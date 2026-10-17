# Gameplay todo

## Règle de travail

Reconstituer chaque comportement depuis le binaire d'origine (pseudocode Ghidra/REA, appels, états et données locales) avant de le coder. Pour chaque fonctionnalité, noter la fonction source et l'évidence; distinguer observation, interprétation et inconnue. Ne pas inventer de règles, de raccourcis ou d'interactions. Le binaire d'origine et le projet Ghidra restent en lecture seule.

## Fait

- [x] Restreindre l'accès à la carte du monde et la surbrillance des îles au masque de session observé.
- [x] Ajouter les sons de menu, le son de démarrage et le choix de musique de royaume; les effets sonores de gameplay restent incomplets.
- [x] Créer les groupes initiaux de travailleurs des quatre tribus et leur association initiale au Grand Hall.
- [x] Porter les primitives de déplacement observées, le registre interne de ressources et les sorties de producteurs, sans prétendre que leurs règles de gameplay sont complètes.
- [x] Retirer du code source les commandes prototypes de travailleurs (clic droit, collecte, retour au Hall et raccourcis B/C/M), reconstruire l'exécutable livré et vérifier qu'il correspond au build.
- [x] Construire le projet et vérifier les 14 tests CTest existants.
- [x] Tracer partiellement le clic de construction : `FUN_0043acea` envoie `0x34` puis `0x33`; la commande passe par la file de catégorie 1, dont le tick appelle `FUN_00465793`, puis `FUN_004662b7` réserve un record différé.

## À faire — suivre les preuves d'origine

- [ ] **Sélection et ordres d'unités :** tracer le routage d'entrée, les états et les vérifications de classe (`FUN_004337d9`, `FUN_00435826`, réception de `0x3f`/`0x4c`). La sélection d'un ouvrier affiche uniquement ses vraies stats; seuls soldats et mages reçoivent les ordres que le code d'origine autorise. Vérifier chaque ordre séparément avant de l'activer.
- [x] **Panneau d'ouvrier initial :** restaurer le panneau `IWLocInfo` depuis `FUN_0044338b` avec `WORKER`, `HITS 3/3` et `STRENGTH 0`, valeurs dérivées de `FUN_00466fe4`, `FUN_00420f28`, `FUN_0041fde6` et des lignes `*work` de `floater.txt`.
- [ ] **Panneaux contextuels restants :** porter les variantes pour unités entraînées et bâtiments depuis `FUN_0044338b`; déterminer les champs par classe. Retrouver les autres actions de bâtiment et les zones interactives de la barre du bas par leurs handlers; garder inertes les zones non prouvées.
- [ ] **Construction différée :** retrouver le consommateur des records réservés par `FUN_004662b7`, ses transitions et le chemin qui mobilise les travailleurs. Valider l'exécution et le coût dans le binaire, puis remplacer le placement instantané du prototype par le flux source complet.
- [ ] **Travailleurs autonomes :** tracer l'attribution des tâches, le déplacement paisible des travailleurs inoccupés, l'exécution des constructions et les transitions d'état depuis le tick d'origine. Ne pas traiter la classe `*work` comme directement commandable sans preuve.
- [ ] **Ressources et bâtiments :** retrouver les stocks initiaux, limites, coûts, débit du Grand Hall, collecte/livraison et activation des producteurs dans leurs fonctions d'origine; connecter les éléments déjà portés uniquement lorsque le flux complet est vérifié.
- [ ] **Audio et interface :** tracer et implémenter les effets sonores de gameplay ainsi que les interactions restantes de l'interface depuis leurs appels d'origine.

## Limites connues

- `FUN_00435826` émet un message de déplacement dans un état UI donné, mais les preuves actuelles ne déterminent ni les classes acceptées ni le comportement complet du destinataire.
- `FUN_0044338b` identifie le champ `HITS` (+0x20 actuel, `FUN_00420f28` maximum); sa branche worker de classe 0 n'affiche pas de ligne `LEVEL`. Le panneau du remake ne couvre que les ouvriers initiaux, sans simulation de dégâts ou d'XP.
- Le chemin de construction du prototype place encore immédiatement un bâtiment; il ne devient pas fidèle avant la reconstruction du flux d'ordre différé.
- Les stocks du Hall, les coûts, l'activation des producteurs, l'IA de travailleurs et certaines transitions de bâtiment restent incomplets ou non résolus.

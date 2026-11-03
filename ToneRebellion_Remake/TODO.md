# Reste à faire

Porter uniquement les comportements établis par le binaire et les données locales. Preuves : `../behavior/` et [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md); état d'ensemble et écarts gardés : [feuille de route](ROADMAP.md). Ce qui est fait n'est pas listé ici (voir les revues et l'historique git).

## À faire

- Déplacement de bâtiment : la source est effacée à la pose; le natif la passe en `+0x58 = 3` et l'efface 8 à 16 ticks plus tard (`FUN_0045343b`, `FUN_00450a71`). Le port ne peut pas garder ce délai tant que la recherche du Hall verrait deux Halls ([analyse](../behavior/island-ground-object-interaction.md)).
- Vérifier en jeu : Repair par liste de réparation, contamination d'un marqueur classe 1 par une Spore, séquence de victoire complète, survol des déclencheurs de trait (aucun n'est atteignable dans les fixtures).
- Fin de partie : chemin multijoueur 0x15; relire `0x4239e9` et `0x46a92a` avec REA.
- Latch `+0x90` : évènement 0xb (texte/son via 0x4013c0) non résolu; le port s'arrête quand aucun site n'est libre, le natif boucle.
- Sauvegardes : celle du remake est refusée dès que `sizeof(GameSession)` change (pas de migration, dépend de l'ABI); le presse-papiers natif n'est pas relu des sauvegardes d'origine.
- Web : la page n'accepte pas un fichier `.iso` (dossier seulement).
- Ménage local (ignoré par git) : copies `ToneRebellion_Remake_sdl - Copie*.exe`, `ToneRebellion_Remake*.zip`, `../hs_err_pid*.log`, `mci_debug.log`.

## Non porté

- Tâches : branche IA des ouvriers en danger (`DAT_005eebd4`, états 6/7), second appelant de `FUN_004239e9` (état 0x13, sous-cas 0x14), types de tâche 6, 0x11 et 0xd de la liste « urgente ».
- Textes : genre 3 `FEAT%02d` (clés absentes des données, table `DAT_005eebf8` non modélisée), textes de gisement `POOLINFECT`/`SUPPLY_%d`; fond `DAT_004c2b08`.
- Réseau : pose directe `FUN_00465793` (catégorie 3, sous-type 4), seulement par le relais `FUN_00412eac`.

## Écarts mineurs

- Texte enveloppé d'`IWTextInfo` posé à y = 0x10 (natif (10, 6)).
- Badge 0x1e (Léviathan) jamais affiché : `DAT_0061fa2e` sans écrivain connu.
- Nettoyage de site approximatif; fusion Maj+clic droit = raccourci du remake.

## Questions REA ouvertes

- Gardes CONSTR supplémentaires (`payload_12`, taille, réservation), `renderer_class != 0` refusant une tâche CONSTR, cas 1..0xd et 0x10..0x14 de `FUN_0041e569`.
- État runtime 10 (compteur `+0x34`) : producteur inconnu, le port n'y entre jamais; préférence de classe 1 nulle (aucun écrivain trouvé).
- Préfixe `x` et badges des monstres dans `FUN_0042704b`.
- Appelants de `FUN_0045d867`/`FUN_0045d8b2`/`FUN_0045ccce`/`FUN_0045dcf4`; corps de `FUN_004207f2`/`FUN_004509da`/`FUN_0042383d`; classe d'`IWLocInfo`; récepteur du message 0x47 de survol.

## Hors périmètre

Mode HallStk et noms des genres 0x2c; multijoueur natif exact (DirectPlay, chat, cartes `ENDGNONP`); `intro.avi`; commandes `nevada` (rotation/zoom clavier).

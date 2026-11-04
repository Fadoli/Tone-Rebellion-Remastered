# Reste à faire

Porter uniquement les comportements établis par le binaire et les données locales. Preuves : `../behavior/` et [FUNCTION_GUIDE.md](../FUNCTION_GUIDE.md); état d'ensemble et écarts gardés : [feuille de route](ROADMAP.md). Ce qui est fait n'est pas listé ici (voir les revues et l'historique git).

## À faire

- Déplacement de bâtiment : la source est effacée à la pose; le natif la passe en `+0x58 = 3` et l'efface 8 à 16 ticks plus tard (`FUN_0045343b`, `FUN_00450a71`). Le port ne peut pas garder ce délai tant que la recherche du Hall verrait deux Halls ([analyse](../behavior/island-ground-object-interaction.md)).
- Vérifier en jeu : Repair par liste de réparation jusqu'aux PV pleins (fixture `repair` : bouton et liste vérifiés), contamination d'un marqueur classe 1 par une Spore, séquence de victoire complète (en solo et en réseau, F11 réseau = commande 0x15), survol des déclencheurs de trait (aucun n'est atteignable dans les fixtures).
- Ménage local (ignoré par git) : copies `ToneRebellion_Remake_sdl - Copie*.exe`, `ToneRebellion_Remake*.zip`, `../hs_err_pid*.log`, `mci_debug.log`.

## Non porté

- Tâches : branche IA des ouvriers en danger (`DAT_005eebd4`, états 6/7), second appelant de `FUN_004239e9` (état 0x13, sous-cas 0x14), types de tâche 6, 0x11 et 0xd de la liste « urgente ».
- Textes : genre 3 `FEAT%02d` (clés absentes des données, table `DAT_005eebf8` non modélisée), textes de gisement `POOLINFECT`/`SUPPLY_%d`; fond `DAT_004c2b08`.
- Réseau : pose directe `FUN_00465793` (catégorie 3, sous-type 4), seulement par le relais `FUN_00412eac`.

## Écarts mineurs

- Texte enveloppé d'`IWTextInfo` posé à y = 0x10 (natif (10, 6)).
- Badge 0x1e (Léviathan) et voile `spl11` du propriétaire 4 jamais affichés : `DAT_0061fa2e` sans écrivain connu.
- Nettoyage de site approximatif; fusion Maj+clic droit = raccourci du remake.

## Questions REA ouvertes

Aucune. La passe du 2026-11-04 a clos les précédentes ([états des floaters](../behavior/floater-states.md)) : gardes CONSTR déjà portées, aucun producteur de l'état 10, pas de préfixe `x`, appelants, corps, classe d'`IWLocInfo` et message 0x47 établis.

## Hors périmètre

Mode HallStk et noms des genres 0x2c; multijoueur natif exact (DirectPlay, chat, cartes `ENDGNONP`); `intro.avi`; commandes `nevada` (rotation/zoom clavier).

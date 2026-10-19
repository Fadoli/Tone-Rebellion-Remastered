# TODO — Autres systèmes

- [x] **Performance — rendu Tasks/texte/sprites :** glyphes écrits directement dans le DIB ([benchmark](bench/task-text-blit.md)); DC source GDI partagé ([bench](bench/sprite-dc-reuse.md)); palette, fallback et transformée de surbrillance réutilisés ([surbrillance](bench/task-highlight.md), [transformée](bench/task-highlight-transform.md)); libellés groupés après les blits ([batching](bench/task-render-batching.md)); l'écran complet est rendu à 30 Hz, y compris quand Tasks est ouvert ([cadence](bench/task-render-cadence.md)).
- [ ] Retrouver le contexte exact des appels à `FUN_004503bd` qui alimentent les deux bits de progression et attribuent un glyphe; les call-sites ne prouvent pas une arrivée au Hall.
- [ ] Finir l'effet monde du clic glyphe : la promotion après allocation et son tirage borné sont tracés; `tone_rng` porte déjà la formule. Il reste à établir le sens de `DAT_004befe0`, l'état/allocation des acteurs et l'ordre `0x13`. Voir [glyphes](../behavior/island-inventory-glyphs.md).
- [ ] Relier les effets sonores aux événements qui les déclenchent.
- [ ] Raccorder le commerce au transport réseau si le remake ajoute le multijoueur; le transfert local type `0xb` est maintenant consommé par le tick et testé bout en bout.

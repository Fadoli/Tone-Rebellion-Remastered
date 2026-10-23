# Presse-papiers de l'île (CLIPSEL1-3, CLIPBD1-3)

Source: REA relu (sous-agent haiku). Evidence: `ev_611f078c…` (dispatcher `FUN_0046cd22`), `ev_6a3225ac…` (`FUN_0046fe40`), `ev_16ba98df…` (`FUN_004390b8`), `ev_32348803…`, `ev_52267ba9…` (vtables `0x4947a0`, `0x494338`), `ev_e8312465…` (`FUN_0043913c`), `ev_bbf728c7…`.

## Observations Ghidra
- `CLIPSEL1-3` = type 48 `ClipSelector` (classe de base seule: aucun gestionnaire propre, paint générique `FUN_0042a27f`, cadre `SHAPEFRAME` de `CLIP`). `CLIPBD1-3` = type 5 `IsleClipBd`: message 1 fixe l'index d'emplacement (`obj+0x70` = caractère à `obj+0x26` − '1'), message 7 efface l'emplacement si `obj+4 == DAT_0062c6bc`.
- Paint `FUN_004391ab`: fond `bildicon`; si l'emplacement est non nul, boucle `*(short*)(slot+0x60)` fois, icône en grille (pas 5 px, 5 par ligne, départ (1,1)), niveau = clamp(`*(int*)(cur+0x14)`, 0..3).
- MASTER (`FUN_0042fa0f`, d'après les notes de fonction, non relu): messages 3001..3003 = sélection de l'emplacement idx (met à jour les panneaux d'info par `FUN_0042f755`); 7001..7003 = groupe actif `DAT_005e16a8` (0..2) puis diffusion de 0xb.
- Données: 9 emplacements `DAT_005e16b0[group*3 + slot]` (message « slot<TOTALCLIPS »), chaque pointeur dans la table par tribu `DAT_006192b0 + DAT_0049f538*0x14a0`, enregistrements de 100 octets.

## Interprétation / inconnues
Interprétation: 3 groupes × 3 emplacements de sélections mémorisées de la tribu. Inconnu: contenu d'un emplacement (type d'enregistrement 100 octets), `FUN_0045c3bb`, `FUN_0040fdab`, appelant de `FUN_004393ab` (création de groupe), correspondance PANE→position. **Non porté:** le modèle de sélection du remake ne peut pas représenter ces groupes tant que le contenu n'est pas établi.

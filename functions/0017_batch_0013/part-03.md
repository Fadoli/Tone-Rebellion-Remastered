# 0017_batch_0013 — détails (3/6)

## FUN_00460989 — 0x460989

- Classification : internal
- Corps : `0x460989–0x460bfa`
- État : pseudocode obtenu
- Evidence : `ev_4ef2e45917071656edd3ac413473549e461a40720460162b2c1dfc0fc0841f9e`
- Note de portée : le chemin insulaire utilise les compteurs et son compte à rebours pour sélectionner des floaters catégorie 4 dont le sous-type n'est pas 9, puis leur pose le flag `0x80`. La reevaluation Leviathan interprète ce flag en portant le seuil de sélection de 150 à 3000. Cette routine ne crée directement ni Spore ni nouveau floater ; la chaîne de production reste à tracer. Evidence de la relecture `ev_51318b865289347ea016897f2f58125ee6479e16683f3d13844fb280a52d10df`.
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013c0` — `thunk_FUN_004655b2`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x40186b` — `thunk_FUN_004656d6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00460989(void)

{
  int iVar1;
  int in_ECX;
  undefined4 local_28;
  uint local_24;
  int *local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  do {
    if ((int)(uint)DAT_006136b0 <= local_8) {
      local_24 = DAT_00618e44 / 6000;
      if (DAT_00618e44 % 6000 == 0) {
        local_28 = 10;
        local_24 = DAT_00618e44 / 6000 - 1;
        if ((int)local_24 < 8) {
          local_24 = thunk_FUN_004655b2(&local_28);
        }
      }
      return local_24;
    }
    if (*(short *)(in_ECX + 0x15f6 + local_8 * 2) != 0) {
      *(short *)(in_ECX + 0x15f6 + local_8 * 2) = *(short *)(in_ECX + 0x15f6 + local_8 * 2) + -1;
      if (*(short *)(in_ECX + 0x15f6 + local_8 * 2) < 2) {
        *(undefined2 *)(in_ECX + 0x15f6 + local_8 * 2) = 0x834;
      }
      else if ((0x32 < *(short *)(in_ECX + 0x15f6 + local_8 * 2)) &&
              (*(short *)(in_ECX + 0x15f6 + local_8 * 2) < 100)) {
        *(undefined2 *)(in_ECX + 0x15f6 + local_8 * 2) = 0;
      }
    }
    if (*(int *)(in_ECX + 0x14e8 + local_8 * 4) == 0) {
      if (*(int *)(in_ECX + 0x1524 + local_8 * 4) < 0) {
        iVar1 = thunk_FUN_00467260(0x960);
        *(int *)(in_ECX + 0x1524 + local_8 * 4) = iVar1 + 0x4b0;
      }
      else if (*(int *)(in_ECX + 0x1524 + local_8 * 4) == 0) {
        local_c = (int)(local_8 + (local_8 >> 0x1f & 3U)) >> 2;
        if (DAT_00618e48 < local_c) {
          local_c = DAT_00618e48;
        }
        local_10 = (local_c + 2 + DAT_00618e48) / 2;
        iVar1 = thunk_FUN_00467260(local_10);
        local_10 = local_10 + iVar1;
        local_14 = thunk_FUN_004656d6(local_8,0xfffffffe);
        local_1c = 0;
        for (local_18 = 0; local_18 < local_14; local_18 = local_18 + 1) {
          iVar1 = (short)(&DAT_00618fb4)[local_18] * 0x4c;
          local_20 = &DAT_006137b8 + (short)(&DAT_00618fb4)[local_18] * 0x13;
          if ((*local_20 == 4) && (*(int *)(&DAT_006137bc + iVar1) != 9)) {
            *(uint *)(&DAT_006137d4 + iVar1) = *(uint *)(&DAT_006137d4 + iVar1) | 0x80;
            local_1c = local_1c + 1;
            if (local_10 <= local_1c) break;
          }
        }
        *(undefined4 *)(in_ECX + 0x1524 + local_8 * 4) = 0xffffffff;
      }
      else if (2 < *(short *)(in_ECX + 0x15ba + local_8 * 2)) {
        *(int *)(in_ECX + 0x1524 + local_8 * 4) = *(int *)(in_ECX + 0x1524 + local_8 * 4) + -1;
      }
    }
    local_8 = local_8 + 1;
  } while( true );
}
```

---

## FUN_00460bfb — 0x460bfb

- Classification : internal
- Corps : `0x460bfb–0x460c47`
- État : pseudocode obtenu
- Evidence : `ev_2951f194f1eca70246fa44005ad5a29291a364e89c6f9ea5bee149973012b846`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00460bfb(short param_1,short param_2)

{
  int in_ECX;
  
  if ((param_1 == 0xe) && (param_2 == *(short *)(in_ECX + 0x14a8 + *(short *)(in_ECX + 0x14a6) * 2))
     ) {
    *(short *)(in_ECX + 0x14a6) = *(short *)(in_ECX + 0x14a6) + 1;
  }
  return;
}
```

---

## FUN_00460c48 — 0x460c48

- Classification : internal
- Corps : `0x460c48–0x460c82`
- État : pseudocode obtenu
- Evidence : `ev_3a7d623c6538068a574d6728b3f7410eff06846c08cf7c487d993699cf2160a5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00460c48(short param_1)

{
  int in_ECX;
  
  if (param_1 < 0) {
    param_1 = 0;
  }
  if (0xf < param_1) {
    param_1 = 0xf;
  }
  *(undefined2 *)(in_ECX + 0x15f6 + param_1 * 2) = 0x16;
  return;
}
```

---

## FUN_00460c83 — 0x460c83

- Classification : internal
- Corps : `0x460c83–0x460d38`
- État : pseudocode obtenu
- Evidence : `ev_a24c81f8a2f97b41143b5d688d38b94924834128b61b556cd6e4d6cc30f17a50`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401875` — `thunk_FUN_0040fc15`
- `0x401ad7` — `thunk_FUN_004603ea`
- `0x401c03` — `thunk_FUN_0046044d`
- `0x401cee` — `thunk_FUN_0040fd80`
- `0x478410` — `FUN_00478410`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00460c83(undefined4 param_1,int param_2)

{
  undefined4 *extraout_ECX;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_1624 [1408];
  undefined4 uStack_24;
  undefined4 *puStack_20;
  undefined4 uStack_1c;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491c12;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  FUN_00478410();
  uStack_1c = 0x460cb8;
  thunk_FUN_004603ea();
  local_8 = 0;
  if (param_2 == 0) {
    puVar2 = extraout_ECX;
    puVar3 = local_1624;
    for (iVar1 = 0x585; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    uStack_1c = 0x1614;
    puStack_20 = local_1624;
    uStack_24 = 0x460d15;
    thunk_FUN_0040fd80();
  }
  else {
    uStack_1c = 0x1614;
    puStack_20 = local_1624;
    uStack_24 = 0x460cd9;
    thunk_FUN_0040fc15();
    puVar2 = local_1624;
    puVar3 = extraout_ECX;
    for (iVar1 = 0x585; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  local_8 = 0xffffffff;
  uStack_1c = 0x460d27;
  thunk_FUN_0046044d();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

## FUN_004616f0 — 0x4616f0

- Classification : internal
- Corps : `0x4616f0–0x46175c`
- État : pseudocode obtenu
- Evidence : `ev_8a6be8d3eed1ab2a2493f4535904f2fc10e013e5d1ebb1bd02197cb0e587122f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402121` — `thunk_FUN_00459370`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004616f0(void)

{
  int in_ECX;
  
  thunk_FUN_00459370(in_ECX + 0x428,0x60,100,thunk_FUN_004500b6);
  *(undefined2 *)(in_ECX + 0x29a8) = 0;
  *(undefined4 *)(in_ECX + 0x29d4) = 0;
  *(undefined4 *)(in_ECX + 0x29dc) = 0;
  *(undefined4 *)(in_ECX + 0x29d8) = 0;
  return in_ECX;
}
```

---

## FUN_0046175d — 0x46175d

- Classification : internal
- Corps : `0x46175d–0x461767`
- État : pseudocode obtenu
- Evidence : `ev_b0bf8f76a5dc2d9ea6b5d238dbf28d4b632afdba787594c65f4dea9836131cff`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046175d(void)

{
  return;
}
```

---

## FUN_00461768 — 0x461768

- Classification : internal
- Corps : `0x461768–0x461830`
- État : pseudocode obtenu
- Evidence : `ev_6b6df8f9f7b52b34cb95a21a218a438f3767531b1c116fb67e756157a3666c24`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472c6c` — `__ftol`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00461768(void)

{
  __ftol();
  return;
}
```

### Complément établi par l'assemblage

- Evidence REA : `ev_0e30ee9ad5fb8589ee58fce47a3a6e4ab0c72e76ca39b0836ffc9a6344f61862` (analyse fraîche du corps et de l'assemblage `0x461768–0x461830`).
- Le corps reçoit deux pointeurs vers des enregistrements de pont. Pour chacun, il choisit l'extrémité qui n'est pas partagée par les deux ponts, puis charge son angle dans la table à `0x5ebd78` (index de monde à pas `0xb4`, index d'île à pas `0xc`).
- Il calcule `angle_A - angle_B`, puis appelle `__ftol` à `0x472c6c`. Ce helper convertit le flottant x87 en entier avec arrondi vers zéro (modification temporaire du mode d'arrondi suivie de `FISTP`).
- **Interprétation dans le contexte appelant :** comparateur passé au tri des ponts dans `FUN_00461859`, ce qui ordonne les voisins autour de l'île courante par angle. Le corps ne normalise pas explicitement la différence autour de la discontinuité angulaire.
- Le pseudocode enregistré par Ghidra est incomplet et ne reflète pas ces opérations; conserver l'assemblage comme base de cette description plutôt que de traiter `void(void)` comme une signature réelle.

---

## FUN_00461831 — 0x461831

- Classification : internal
- Corps : `0x461831–0x461858`
- État : pseudocode obtenu
- Evidence : `ev_01e84e3b7c0e0b4de4d333b8326aa958815bc2f20f2ae9cc89898cf36ff2d001`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00461831(undefined4 *param_1,undefined4 *param_2)

{
  return (int)*(short *)*param_1 - (int)*(short *)*param_2;
}
```

### Rôle dans l'appelant

- Evidence REA : `ev_b2c053a4bd63d8f7ce191f425358685b35f763313fce9b221df727eef5c30a41`.
- `FUN_00461859` passe ce comparateur à `FUN_004777a0` pour trier les pointeurs vers ses records de classe 2. Le `short` à l'adresse pointée est le premier champ du record (X dans le contexte d'île); le tri est donc croissant sur X.

---

## FUN_00461859 — 0x461859

- Classification : internal
- Corps : `0x461859–0x461b3a`
- État : pseudocode obtenu
- Evidence : `ev_60cc3b805a032ead183ce15cfa0965bb14b5d6c84b45414f6d11fbbb2eaca75b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011e0` — `thunk_FUN_004500c4`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4777a0` — `FUN_004777a0`

### Chaînes référencées

- `0x4a4b80` — "curbridge<bridgecount"
- `0x4a4b98` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
void FUN_00461859(void)

{
  undefined4 *puVar1;
  int in_ECX;
  int aiStackY_2003c [10];
  int aiStackY_20014 [32751];
  int local_3c [4];
  short local_2c;
  int local_28;
  int local_24;
  short local_20;
  int local_1c;
  short local_18;
  int local_14 [4];
  
  puVar1 = (undefined4 *)
           (&DAT_005ebd78 + ((in_ECX + -0x5ec218) / 0x29e8) * 0xc + DAT_006136b2 * 0xb4);
  *(undefined4 *)(in_ECX + 0x29d4) = *puVar1;
  *(undefined4 *)(in_ECX + 0x29d8) = puVar1[1];
  *(undefined4 *)(in_ECX + 0x29dc) = puVar1[2];
  for (local_24 = 0; local_24 < 4; local_24 = local_24 + 1) {
    *(undefined2 *)(in_ECX + local_24 * 2) = 0;
    *(undefined4 *)(in_ECX + 0x408 + local_24 * 8) = 0;
    *(undefined4 *)(in_ECX + 0x40c + local_24 * 8) = 0x27f;
    *(undefined4 *)(in_ECX + 0x29ac + local_24 * 4) = 0;
    *(undefined4 *)(in_ECX + 0x29bc + local_24 * 4) = 0;
  }
  for (local_24 = 0; local_24 < *(short *)(in_ECX + 0x29a8); local_24 = local_24 + 1) {
    thunk_FUN_004500c4();
  }
  local_2c = 0;
  local_18 = (short)((in_ECX + -0x5ec218) / 0x29e8);
  for (local_24 = 0; local_24 < (int)(uint)DAT_006137b4; local_24 = local_24 + 1) {
    if ((*(short *)(&DAT_006136b8 + local_24 * 8) == local_18) ||
       (*(short *)(&DAT_006136ba + local_24 * 8) == local_18)) {
      local_3c[local_2c] = (int)(&DAT_006136b4 + local_24 * 2);
      local_2c = local_2c + 1;
    }
  }
  local_20 = 0;
  for (local_24 = 0; local_24 < *(short *)(in_ECX + 0x29a8); local_24 = local_24 + 1) {
    if (*(int *)(in_ECX + 0x42c + local_24 * 0x60) == 2) {
      local_14[local_20] = in_ECX + 0x428 + local_24 * 0x60;
      local_20 = local_20 + 1;
    }
  }
  FUN_004777a0(local_3c,(int)local_2c,4,&LAB_004019dd);
  FUN_004777a0(local_14,(int)local_20,4,&LAB_004015f5);
  local_1c = 0;
  local_28 = 0;
  for (local_24 = 0; local_24 < local_20; local_24 = local_24 + 1) {
    if ((local_24 == 0) || (local_20 - local_1c <= (int)local_2c)) {
      if (local_2c <= local_28) {
        thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4b98,0xcb,s_curbridge<bridgecount_004a4b80)
        ;
      }
      if (*(short *)(local_3c[local_28] + 4) == local_18) {
        *(undefined2 *)(local_14[local_24] + 0x36) = *(undefined2 *)(local_3c[local_28] + 6);
      }
      else {
        *(undefined2 *)(local_14[local_24] + 0x36) = *(undefined2 *)(local_3c[local_28] + 4);
      }
      local_28 = local_28 + 1;
    }
    else {
      *(undefined4 *)(local_14[local_24] + 4) = 0;
      local_1c = local_1c + 1;
    }
  }
  *(undefined4 *)(in_ECX + 0x29cc) = 0;
  return;
}
```

---

## FUN_00461b3b — 0x461b3b

- Classification : internal
- Corps : `0x461b3b–0x462093`
- État : pseudocode obtenu
- Evidence : `ev_3b7162466a7231d687838b72eb5276518cedf5f25744ad18bf65773722a5e009`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401154` — `thunk_FUN_00414b91`
- `0x40149c` — `thunk_FUN_00414bc2`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472ca0` — `FUN_00472ca0`
- `0x472f10` — `FUN_00472f10`
- `0x4774f0` — `_strcmp`

### Chaînes référencées

- `0x4a4bb0` — "data\\ISLAND%02d.TXT"
- `0x4a4bc4` — "%s %d"
- `0x4a4bcc` — "numlocs <= MAX_ISLAND_LOCS"
- `0x4a4be8` — "C:\\float\\src\\tworld.cpp"
- `0x4a4c00` — "%d %d %d %s %d"
- `0x4a4c14` — "smpad"
- `0x4a4c1c` — "mdpad"
- `0x4a4c24` — "lgpad"
- `0x4a4c34` — "bridge"
- `0x4a4c3c` — "special"
- `0x4a4c44` — "levhub"
- `0x4a4c4c` — "levshld"
- `0x4a4c54` — "feature"
- `0x4a4c5c` — "feattrig"
- `0x4a4c68` — "FALSE"
- `0x4a4c70` — "C:\\float\\src\\tworld.cpp"
- `0x4a4c88` — "mNumLocs < MAX_ISLAND_LOCS"
- `0x4a4ca4` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_00461b3b(undefined2 param_1)

{
  undefined2 *puVar1;
  int iVar2;
  undefined4 uVar3;
  int in_ECX;
  uint local_e8;
  undefined4 local_e0;
  undefined2 local_dc [2];
  undefined2 local_d8 [2];
  undefined1 local_d4 [4];
  int local_d0 [4];
  short local_c0;
  char local_bc [24];
  int local_a4;
  undefined4 local_a0;
  undefined1 local_9c [100];
  undefined1 local_38 [52];
  
  *(undefined2 *)(in_ECX + 0x29e0) =
       *(undefined2 *)(&DAT_005eaba8 + ((in_ECX + -0x5ec218) / 0x29e8) * 2 + DAT_006136b2 * 0x1e);
  FUN_00472ca0(local_38,s_data_ISLAND_02d_TXT_004a4bb0,(int)*(short *)(in_ECX + 0x29e0));
  iVar2 = thunk_FUN_0040f419(local_38,&DAT_004b28f0,20000);
  if (iVar2 == 0) {
    *(undefined2 *)(in_ECX + 0x29a8) = 0;
    thunk_FUN_0040f5b3(local_9c,0);
    FUN_00472f10(local_9c,s__s__d_004a4bc4,local_38,&local_a4);
    if (100 < local_a4) {
      thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4be8,0xf1,
                         s_numlocs_<__MAX_ISLAND_LOCS_004a4bcc);
    }
    for (local_c0 = 0; local_c0 < local_a4; local_c0 = local_c0 + 1) {
      thunk_FUN_0040f5b3(local_9c,0);
      iVar2 = FUN_00472f10(local_9c,s__d__d__d__s__d_004a4c00,local_d4,local_d8,local_dc,local_bc,
                           local_d0);
      if (iVar2 != 5) {
        return 0;
      }
      local_e8 = 0;
      local_e0 = 0;
      iVar2 = _strcmp(local_bc,&DAT_004a4c10);
      if (iVar2 == 0) {
        local_a0 = 0;
        local_e8 = (uint)(local_d0[0] == 1);
      }
      else {
        iVar2 = _strcmp(local_bc,s_smpad_004a4c14);
        if (iVar2 == 0) {
          local_a0 = 0;
          local_e8 = (uint)(local_d0[0] == 1);
        }
        else {
          iVar2 = _strcmp(local_bc,s_mdpad_004a4c1c);
          if (iVar2 == 0) {
            local_a0 = 0;
            local_e0 = 1;
            local_e8 = (uint)(local_d0[0] == 1);
          }
          else {
            iVar2 = _strcmp(local_bc,s_lgpad_004a4c24);
            if (iVar2 == 0) {
              local_a0 = 0;
              local_e0 = 2;
              local_e8 = (uint)(local_d0[0] == 1);
            }
            else {
              iVar2 = _strcmp(local_bc,&DAT_004a4c2c);
              if (iVar2 == 0) {
                local_a0 = 1;
              }
              else {
                iVar2 = _strcmp(local_bc,s_bridge_004a4c34);
                if (iVar2 == 0) {
                  local_a0 = 2;
                }
                else {
                  iVar2 = _strcmp(local_bc,s_special_004a4c3c);
                  if (iVar2 == 0) {
                    local_a0 = 3;
                  }
                  else {
                    iVar2 = _strcmp(local_bc,s_levhub_004a4c44);
                    if (iVar2 == 0) {
                      local_a0 = 3;
                      local_e8 = 0x16;
                    }
                    else {
                      iVar2 = _strcmp(local_bc,s_levshld_004a4c4c);
                      if (iVar2 == 0) {
                        local_a0 = 0;
                      }
                      else {
                        iVar2 = _strcmp(local_bc,s_feature_004a4c54);
                        if (iVar2 == 0) {
                          local_a0 = 3;
                          local_e8 = 4;
                        }
                        else {
                          iVar2 = _strcmp(local_bc,s_feattrig_004a4c5c);
                          if (iVar2 != 0) {
                            thunk_FUN_00414b91(s_C__float_src_tworld_cpp_004a4c70,0x13d,
                                               s_FALSE_004a4c68,local_bc);
                            return 0;
                          }
                          local_a0 = 3;
                          local_e8 = 3;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (99 < *(short *)(in_ECX + 0x29a8)) {
        thunk_FUN_00414bc2(s_C__float_src_tworld_cpp_004a4ca4,0x141,
                           s_mNumLocs_<_MAX_ISLAND_LOCS_004a4c88,(int)*(short *)(in_ECX + 0x29e0));
      }
      puVar1 = (undefined2 *)(in_ECX + 0x428 + *(short *)(in_ECX + 0x29a8) * 0x60);
      *(short *)(in_ECX + 0x29a8) = *(short *)(in_ECX + 0x29a8) + 1;
      *(undefined4 *)(puVar1 + 2) = local_a0;
      *puVar1 = local_d8[0];
      puVar1[1] = local_dc[0];
      puVar1[4] = param_1;
      *(uint *)(puVar1 + 8) = local_e8;
      *(undefined4 *)(puVar1 + 6) = local_e0;
      switch(local_a0) {
      case 0:
        break;
      case 1:
        puVar1[0x10] = 0x14;
        break;
      case 2:
        puVar1[0x1b] = (undefined2)local_d0[0];
        break;
      case 3:
        if (*(int *)(puVar1 + 8) == 3) {
          puVar1[0x25] = (undefined2)local_d0[0];
        }
        else if (*(int *)(puVar1 + 8) == 4) {
          *(short *)(in_ECX + 0x29d0) = local_c0;
        }
      }
    }
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}
```

---

## FUN_004620a4 — 0x4620a4

- Classification : internal
- Corps : `0x4620a4–0x46210f`
- État : pseudocode obtenu
- Evidence : `ev_ab8c3b536bfc7f9d9c2578cc3e5fd6fdb1a0674eff1670eda940aff59a36de3c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004620a4(int param_1,int param_2)

{
  int in_ECX;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (*(short *)(in_ECX + param_1 * 2) <= local_8) {
      return 0;
    }
    if ((*(int *)(in_ECX + 8 + param_1 * 0x100 + local_8 * 8) <= param_2) &&
       (param_2 <= *(int *)(in_ECX + param_1 * 0x100 + 0xc + local_8 * 8))) break;
    local_8 = local_8 + 1;
  }
  return 1;
}
```

---

## FUN_00462110 — 0x462110

- Classification : internal
- Corps : `0x462110–0x46226b`
- État : pseudocode obtenu
- Evidence : `ev_bb7bfd638dab1623b8d3eb908028998e40ef60175b2b6fea8a8f73134068fccf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a4cbc` — "numspans < MAX_TONE_SPANS"
- `0x4a4cd8` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
void FUN_00462110(int param_1,int param_2,int param_3)

{
  int in_ECX;
  int iVar1;
  int *local_10;
  int local_8;
  
  iVar1 = (int)*(short *)(in_ECX + param_1 * 2);
  if (0x1f < iVar1) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4cd8,0x178,s_numspans_<_MAX_TONE_SPANS_004a4cbc
                      );
  }
  if (param_2 < 0) {
    param_2 = 0;
  }
  if (0x9ff < param_3) {
    param_3 = 0x9ff;
  }
  local_8 = iVar1;
  if (0 < iVar1) {
    local_10 = (int *)(in_ECX + 8 + param_1 * 0x100);
    for (local_8 = 0; local_8 < iVar1; local_8 = local_8 + 1) {
      if ((param_2 < *local_10) && (*local_10 <= param_3)) {
        *local_10 = param_2;
        if (local_10[1] < param_3) {
          local_10[1] = param_3;
        }
        break;
      }
      if ((local_10[1] < param_3) && (param_2 <= local_10[1])) {
        local_10[1] = param_3;
        if (param_2 < *local_10) {
          *local_10 = param_2;
        }
        break;
      }
      local_10 = local_10 + 2;
    }
  }
  if (local_8 == iVar1) {
    *(int *)(in_ECX + 8 + param_1 * 0x100 + iVar1 * 8) = param_2;
    *(int *)(in_ECX + param_1 * 0x100 + 0xc + iVar1 * 8) = param_3;
    *(short *)(in_ECX + param_1 * 2) = *(short *)(in_ECX + param_1 * 2) + 1;
  }
  return;
}
```

---

## FUN_0046226c — 0x46226c

- Classification : internal
- Corps : `0x46226c–0x462284`
- État : pseudocode obtenu
- Evidence : `ev_3905b02543f0b0144a753b7cb0c664db2865ddb18518f6f3986f90ac7a4b59d9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046226c(int param_1)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + param_1 * 2) = 0;
  return;
}
```

---

## FUN_00462285 — 0x462285

- Classification : internal
- Corps : `0x462285–0x4626f7`
- État : pseudocode obtenu
- Evidence : `ev_d21db672f076fafb487f3df6b6c2223688f295be4f07b4dfb7d9645fa381068c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014f6` — `thunk_FUN_00462110`
- `0x401992` — `thunk_FUN_004539e9`
- `0x401aa0` — `thunk_FUN_004620a4`
- `0x401bef` — `thunk_FUN_00453cf5`
- `0x401c71` — `thunk_FUN_0046226c`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401ff0` — `thunk_FUN_00453958`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a4cf0` — "tribe > FT_None && tribe < FT_NumTypes"
- `0x4a4d18` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
int FUN_00462285(int param_1)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int in_ECX;
  uint uVar4;
  int local_88;
  int local_84;
  short *local_80;
  byte local_78;
  byte local_74 [100];
  int local_10;
  int local_c;
  int local_8;
  
  if ((param_1 < 0) || (4 < param_1)) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4d18,0x1a7,
                       s_tribe_>_FT_None____tribe_<_FT_Nu_004a4cf0);
  }
  local_88 = 0;
  local_10 = param_1;
  uVar4 = 1 << ((byte)param_1 & 0x1f);
  _memset(local_74,0,100);
  thunk_FUN_0046226c(local_10);
  bVar2 = true;
  while (local_78 = (byte)uVar4, bVar2) {
    bVar2 = false;
    local_80 = (short *)(in_ECX + 0x428);
    for (local_84 = 0; local_84 < *(short *)(in_ECX + 0x29a8); local_84 = local_84 + 1) {
      if (*(int *)(local_80 + 10) != 4) {
        if (*(int *)(&DAT_0061a654 + local_10 * 0x14a0) == 0) {
          if (local_74[local_84] == 0) {
            if (*(int *)(local_80 + 2) == 1) {
              if ((((int)(char)local_80[0x11] & uVar4) != 0) ||
                 (iVar3 = thunk_FUN_004620a4(local_10,(int)*local_80), iVar3 != 0)) {
                local_74[local_84] = local_78;
                thunk_FUN_00462110(local_10,*local_80 + -0x96,*local_80 + 0x96);
                local_88 = local_88 + 1;
              }
            }
            else if (*(int *)(local_80 + 2) == 2) {
              if ((*(uint *)(local_80 + 0xe) & 1) != 0) {
                local_74[local_84] = local_78;
                thunk_FUN_00462110(local_10,*local_80 + -100,*local_80 + 100);
              }
            }
            else if (((*(int *)(local_80 + 2) == 0) &&
                     (iVar3 = thunk_FUN_00453cf5(param_1), iVar3 != 0)) &&
                    ((*(int *)(local_80 + 8) == 0x28 &&
                     ((iVar3 = thunk_FUN_00453958(), iVar3 != 0 &&
                      (iVar3 = thunk_FUN_004620a4(local_10,(int)*local_80), iVar3 != 0)))))) {
              local_74[local_84] = local_78;
              thunk_FUN_00462110(local_10,*local_80 + -300,*local_80 + 300);
            }
            if (local_74[local_84] != 0) {
              bVar2 = true;
            }
          }
        }
        else {
          local_74[local_84] = local_78;
        }
      }
      local_80 = local_80 + 0x30;
    }
  }
  local_80 = (short *)(in_ECX + 0x428);
  for (local_84 = 0; local_84 < *(short *)(in_ECX + 0x29a8); local_84 = local_84 + 1) {
    if ((((local_74[local_84] == 0) && (*(int *)(local_80 + 2) == 0)) &&
        (*(int *)(local_80 + 10) != 4)) &&
       (iVar3 = thunk_FUN_004620a4(local_10,(int)*local_80), iVar3 != 0)) {
      local_74[local_84] = local_78;
    }
    local_80 = local_80 + 0x30;
  }
  if (*(int *)(&DAT_0061a654 + local_10 * 0x14a0) != 0) {
    thunk_FUN_00462110(local_10,0,0xa00);
    local_88 = 10;
  }
  local_80 = (short *)(in_ECX + 0x428);
  for (local_84 = 0; local_84 < *(short *)(in_ECX + 0x29a8); local_84 = local_84 + 1) {
    *(byte *)((int)local_80 + 0x22) = *(byte *)((int)local_80 + 0x22) & ~local_78;
    *(byte *)((int)local_80 + 0x22) = *(byte *)((int)local_80 + 0x22) | local_74[local_84];
    thunk_FUN_004539e9();
    local_80 = (short *)((int)local_80 + 0x60);
  }
  local_c = *(int *)(in_ECX + 0x408 + local_10 * 8);
  local_8 = *(int *)(in_ECX + 0x40c + local_10 * 8);
  for (local_84 = 0; local_84 < *(short *)(in_ECX + local_10 * 2); local_84 = local_84 + 1) {
    iVar3 = in_ECX + 8 + local_10 * 0x100;
    iVar1 = *(int *)(iVar3 + local_84 * 8);
    iVar3 = *(int *)(iVar3 + 4 + local_84 * 8);
    if (iVar1 + -100 < local_c) {
      local_c = iVar1 + -100;
    }
    if (local_8 < iVar3 + 100) {
      local_8 = iVar3 + 100;
    }
  }
  if (local_c < 0) {
    local_c = 0;
  }
  if (0x9ff < local_8) {
    local_8 = 0x9ff;
  }
  *(int *)(in_ECX + 0x408 + local_10 * 8) = local_c;
  *(int *)(in_ECX + 0x40c + local_10 * 8) = local_8;
  return local_88;
}
```

---

## FUN_004626f8 — 0x4626f8

- Classification : internal
- Corps : `0x4626f8–0x4628fc`
- État : pseudocode obtenu
- Evidence : `ev_ceec68ebd92188172b554b5516640e2fa7b5db846231f2264f38376bdc7d3acd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40173a` — `thunk_FUN_004672a6`
- `0x401a69` — `thunk_FUN_00452ceb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4
FUN_004626f8(undefined4 param_1,short param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  short *psVar1;
  int iVar2;
  int in_ECX;
  uint local_34;
  uint local_30;
  uint local_20;
  short *local_1c;
  int local_18;
  int local_14;
  short *local_10;
  int local_c;
  short local_8;
  
  local_8 = -1;
  local_14 = 0;
  if ((param_3 < 0) || (3 < param_3)) {
    local_10 = (short *)0x0;
    local_c = 0x9ff;
    psVar1 = (short *)(in_ECX + 0x428);
  }
  else {
    local_10 = *(short **)(in_ECX + 0x408 + param_3 * 8);
    local_c = *(int *)(in_ECX + 0x40c + param_3 * 8);
    psVar1 = local_10;
  }
  local_1c = (short *)(in_ECX + 0x428);
  for (local_18 = 0; local_18 < *(short *)(in_ECX + 0x29a8); local_18 = local_18 + 1) {
    if (((int)local_10 <= (int)*local_1c) && (*local_1c <= local_c)) {
      local_20 = 0;
      switch(param_1) {
      case 0:
        local_20 = (uint)(*(int *)(local_1c + 2) == (int)param_2);
        break;
      case 1:
        if ((*(int *)(local_1c + 2) == 0) && (*(int *)(local_1c + 8) == (int)param_2)) {
          local_30 = 1;
        }
        else {
          local_30 = 0;
        }
        local_20 = local_30;
        break;
      case 2:
        if (((*(int *)(local_1c + 2) == 0) && (*(int *)(local_1c + 10) == (int)param_2)) &&
           ((*(int *)(local_1c + 8) == 0x2a || (local_1c[0xc] != -1)))) {
          local_20 = 1;
        }
        break;
      case 3:
        if ((param_2 < 5) || (0x21 < param_2)) {
          local_20 = thunk_FUN_00452ceb((int)param_2,param_3);
        }
        else {
          if ((*(int *)(local_1c + 10) == param_3) &&
             (((*(int *)(local_1c + 8) == 0x2a || (local_1c[0xc] != -1)) &&
              (0 < *(short *)(&DAT_006191fc + param_2 * 2 + param_3 * 0x14a0))))) {
            local_34 = 1;
          }
          else {
            local_34 = 0;
          }
          local_20 = local_34;
        }
      }
      if ((local_20 != 0) &&
         ((iVar2 = thunk_FUN_004672a6((int)*local_1c,(int)local_1c[1],param_4,param_5),
          local_8 == -1 || (iVar2 < local_14)))) {
        local_8 = (short)local_18;
        local_14 = iVar2;
      }
    }
    psVar1 = local_1c + 0x30;
    local_1c = psVar1;
  }
  return CONCAT22((short)((uint)psVar1 >> 0x10),local_8);
}
```

---

## FUN_0046290d — 0x46290d

- Classification : internal
- Corps : `0x46290d–0x462a86`
- État : pseudocode obtenu
- Evidence : `ev_17007ffebe96d72cd52cb293a42776a6f5d9225353c509d624a7118731d03beb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f32` — `thunk_FUN_00450a71`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046290d(void)

{
  int in_ECX;
  undefined4 local_c;
  undefined4 local_8;
  
  for (local_c = 0; local_c < *(short *)(in_ECX + 0x29a8); local_c = local_c + 1) {
    thunk_FUN_00450a71();
  }
  while (6.28318 <= *(float *)(in_ECX + 0x29d4)) {
    *(float *)(in_ECX + 0x29d4) = *(float *)(in_ECX + 0x29d4) - 6.28318;
  }
  while (*(float *)(in_ECX + 0x29d4) < 0.0) {
    *(float *)(in_ECX + 0x29d4) = *(float *)(in_ECX + 0x29d4) + 6.28318;
  }
  local_8 = -1;
  if ((DAT_006191b4 == 3) && (99 < DAT_006191b6)) {
    local_8 = DAT_006191b6 + -100;
  }
  else if ((DAT_006191b4 == 4) && (DAT_006191b6 < 0x3c)) {
    local_8 = DAT_006191b6 + 200;
  }
  if (local_8 != -1) {
    if (*(int *)(DAT_0049f538 * 0x14a0 + 0x619248) == 0) {
      local_8 = -(local_8 / 0x46);
    }
    else {
      local_8 = (local_8 / 0x46) / 3;
    }
    if (local_8 < -0x14) {
      local_8 = -0x14;
    }
    if (0x14 < local_8) {
      local_8 = 0x14;
    }
    if (200 < *(int *)(in_ECX + 0x29d8)) {
      *(int *)(in_ECX + 0x29d8) = *(int *)(in_ECX + 0x29d8) + local_8;
    }
  }
  return;
}
```

---


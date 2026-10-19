# 0017_batch_0013 — détails (1/3)

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

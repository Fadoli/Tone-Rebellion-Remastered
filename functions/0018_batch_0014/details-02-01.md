# 0018_batch_0014 — détails (1/3)

## FUN_0046b928 — 0x46b928

- Classification : internal
- Corps : `0x46b928–0x46ba3a`
- État : pseudocode obtenu
- Evidence : `ev_03ce20faddd08eab7d86a563c258a4587ad7041d25c8a7cc761e628052c6caea`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a568c` — "mNumContinuousRequests != MAX_CONTINUOUS_UPDATES"
- `0x4a56c0` — "C:\\float\\src\\winman.cpp"

### Pseudocode Ghidra

```c
void FUN_0046b928(undefined4 param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int in_ECX;
  short local_8;
  
  if (*(short *)(in_ECX + 0x2e7c) == 0x10) {
    thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a56c0,0x414,
                       s_mNumContinuousRequests____MAX_CO_004a568c);
  }
  local_8 = 0;
  while( true ) {
    if (0xf < local_8) {
      return;
    }
    if (*(int *)(in_ECX + 0x2cfc + local_8 * 0x18) == 0) break;
    local_8 = local_8 + 1;
  }
  *(undefined4 *)(in_ECX + 0x2cfc + local_8 * 0x18) = param_1;
  *(undefined2 *)(in_ECX + 0x2d00 + local_8 * 0x18) = param_2;
  *(undefined4 *)(in_ECX + 0x2d04 + local_8 * 0x18) = param_3;
  *(undefined4 *)(in_ECX + 0x2d08 + local_8 * 0x18) = param_4;
  *(undefined4 *)(in_ECX + 0x2d0c + local_8 * 0x18) = param_5;
  *(undefined4 *)(in_ECX + 0x2d10 + local_8 * 0x18) = param_5;
  *(short *)(in_ECX + 0x2e7c) = *(short *)(in_ECX + 0x2e7c) + 1;
  return;
}
```

---

---

## FUN_0046ba3b — 0x46ba3b

- Classification : internal
- Corps : `0x46ba3b–0x46bace`
- État : pseudocode obtenu
- Evidence : `ev_71a0a79a04153617d44768e05d375b6e769b9ccfdfe26b3bcd213a0ca005447b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046ba3b(int param_1,short param_2)

{
  int in_ECX;
  undefined2 local_8;
  
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    if ((*(int *)(in_ECX + 0x2cfc + local_8 * 0x18) == param_1) &&
       ((param_2 == -1 || (*(short *)(in_ECX + 0x2d00 + local_8 * 0x18) == param_2)))) {
      *(undefined4 *)(in_ECX + 0x2cfc + local_8 * 0x18) = 0;
      *(short *)(in_ECX + 0x2e7c) = *(short *)(in_ECX + 0x2e7c) + -1;
    }
  }
  return;
}
```

---

---

## FUN_0046bacf — 0x46bacf

- Classification : internal
- Corps : `0x46bacf–0x46bb7e`
- État : pseudocode obtenu
- Evidence : `ev_dfaa232786df3cd74e66be03909ede115369effe979cb90003367954999b44e5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046bacf(void)

{
  int *piVar1;
  int in_ECX;
  short local_10;
  short local_c;
  
  local_c = *(short *)(in_ECX + 0x2e7c);
  local_10 = 0;
  while ((local_10 < 0x10 && (0 < local_c))) {
    piVar1 = (int *)(in_ECX + 0x2cfc + local_10 * 0x18);
    if (*piVar1 != 0) {
      if (piVar1[5] == 0) {
        thunk_FUN_0046c371(*piVar1,CONCAT22((short)((uint)piVar1 >> 0x10),(short)piVar1[1]),
                           piVar1[2],piVar1[3]);
        piVar1[5] = piVar1[5] + piVar1[4];
      }
      local_c = local_c + -1;
    }
    local_10 = local_10 + 1;
  }
  return;
}
```

---

---

## FUN_0046bb7f — 0x46bb7f

- Classification : internal
- Corps : `0x46bb7f–0x46bc7d`
- État : pseudocode obtenu
- Evidence : `ev_7ad60d15a072cfa0d11f2d033f16ad5cc597681dadcd6d5ddeec2be3772273d9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a56d8` — "mNumMsgOnChange != MAX_MSG_ON_CHANGE"
- `0x4a5700` — "C:\\float\\src\\winman.cpp"

### Pseudocode Ghidra

```c
void FUN_0046bb7f(undefined4 param_1,undefined4 param_2,undefined2 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  int in_ECX;
  short local_8;
  
  if (*(short *)(in_ECX + 0x2fc0) == 0x10) {
    thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5700,0x47b,
                       s_mNumMsgOnChange____MAX_MSG_ON_CH_004a56d8);
  }
  local_8 = 0;
  while( true ) {
    if (0xf < local_8) {
      return;
    }
    if (*(int *)(in_ECX + 0x2e80 + local_8 * 0x14) == 0) break;
    local_8 = local_8 + 1;
  }
  *(undefined4 *)(in_ECX + 0x2e80 + local_8 * 0x14) = param_1;
  *(undefined4 *)(in_ECX + 0x2e84 + local_8 * 0x14) = param_2;
  *(undefined2 *)(in_ECX + 0x2e88 + local_8 * 0x14) = param_3;
  *(undefined4 *)(in_ECX + 0x2e8c + local_8 * 0x14) = param_4;
  *(undefined4 *)(in_ECX + 0x2e90 + local_8 * 0x14) = param_5;
  *(short *)(in_ECX + 0x2fc0) = *(short *)(in_ECX + 0x2fc0) + 1;
  return;
}
```

---

---

## FUN_0046bc7e — 0x46bc7e

- Classification : internal
- Corps : `0x46bc7e–0x46bd11`
- État : pseudocode obtenu
- Evidence : `ev_8ca934a96d0348dea10b8c806545c5d48e9e2f4145a6775116683d1dc76c4493`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046bc7e(int param_1,short param_2)

{
  int in_ECX;
  undefined2 local_8;
  
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    if ((*(int *)(in_ECX + 0x2e80 + local_8 * 0x14) == param_1) &&
       ((param_2 == -1 || (*(short *)(in_ECX + 0x2e88 + local_8 * 0x14) == param_2)))) {
      *(undefined4 *)(in_ECX + 0x2e80 + local_8 * 0x14) = 0;
      *(short *)(in_ECX + 0x2fc0) = *(short *)(in_ECX + 0x2fc0) + -1;
    }
  }
  return;
}
```

---

---

## FUN_0046bd12 — 0x46bd12

- Classification : internal
- Corps : `0x46bd12–0x46bded`
- État : pseudocode obtenu
- Evidence : `ev_b80881a3a159b541d5a1ba4763c89806c2f4337b3b938e49c712565c60f1b357`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Removing unreachable block (ram,0x0046bd96) */

void FUN_0046bd12(void)

{
  int in_ECX;
  undefined2 local_18;
  undefined2 local_10;
  
  local_10 = *(short *)(in_ECX + 0x2fc0);
  local_18 = 0;
  while ((local_18 < 0x10 && (0 < local_10))) {
    if (*(int *)(in_ECX + 0x2e80 + local_18 * 0x14) != 0) {
      local_10 = local_10 + -1;
    }
    local_18 = local_18 + 1;
  }
  return;
}
```

---

---

## FUN_0046bdee — 0x46bdee

- Classification : internal
- Corps : `0x46bdee–0x46be80`
- État : pseudocode obtenu
- Evidence : `ev_fa0207968e95f1464cc1c397bc1d8b28d8ffed8238efbbe7a0daf79f16598254`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046bdee(void)

{
  int in_ECX;
  int local_c;
  undefined4 *local_8;
  
  if ((0 < DAT_00618f58) && (*(int *)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130) != 0))
  {
    local_8 = &DAT_00618e58;
    for (local_c = 0; local_c < DAT_00618f58; local_c = local_c + 1) {
      (**(code **)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130))(5,*local_8,local_8[1],0);
      local_8 = local_8 + 2;
    }
  }
  return;
}
```

---

---

## FUN_0046be81 — 0x46be81

- Classification : internal
- Corps : `0x46be81–0x46c17a`
- État : pseudocode obtenu
- Evidence : `ev_babd1c65f3d01ba7689c390b5aa86ccbe61b906550c4f27ec84d56edee8ab87a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x476e20` — `_strncmp`

### Chaînes référencées

- `0x4a5718` — "wnd_index >= 0"
- `0x4a5728` — "C:\\float\\src\\winman.cpp"
- `0x4a5740` — "scroll"

### Pseudocode Ghidra

```c
void FUN_0046be81(void)

{
  short sVar1;
  short sVar2;
  int iVar3;
  bool bVar4;
  int in_ECX;
  short local_20;
  short local_18;
  int local_14;
  
  sVar1 = *(short *)(in_ECX + 0x62bc);
  sVar2 = *(short *)(in_ECX + 0x62be);
  if (-1 < *(short *)(in_ECX + 0x29f2)) {
    local_18 = *(short *)(in_ECX + 8000 + *(short *)(in_ECX + 0x29f2) * 0x130);
    local_20 = 0x49;
    bVar4 = false;
    while ((0 < local_18 && (!bVar4))) {
      if (local_20 < 0) {
        thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5728,0x530,s_wnd_index_>__0_004a5718);
      }
      local_14 = *(int *)(in_ECX + *(short *)(in_ECX + 0x29f2) * 0x130 + 0x1f44 + local_20 * 4);
      if (local_14 != 0) {
        if (((((*(int *)(*(int *)(in_ECX + 4 + local_14 * 0xc) + 0x40) == 1) &&
              (iVar3 = *(int *)(in_ECX + 4 + local_14 * 0xc), (int)sVar1 <= *(int *)(iVar3 + 0x14)))
             && (*(int *)(iVar3 + 0xc) <= (int)sVar1)) &&
            (((int)sVar2 <= *(int *)(iVar3 + 0x18) && (*(int *)(iVar3 + 0x10) <= (int)sVar2)))) &&
           (*(int *)(*(int *)(in_ECX + 4 + local_14 * 0xc) + 0x38) == 1)) {
          bVar4 = true;
          _strncmp((char *)(*(int *)(in_ECX + 4 + local_14 * 0xc) + 0x20),s_scroll_004a5740,6);
        }
        local_18 = local_18 + -1;
      }
      local_20 = local_20 + -1;
    }
    if ((*(int *)(in_ECX + 0x1f3c) != -1) && ((!bVar4 || (local_14 != *(int *)(in_ECX + 0x1f3c)))))
    {
      thunk_FUN_0046c371(*(undefined4 *)(in_ECX + 0x1f3c),10,(int)sVar1,(int)sVar2);
      thunk_FUN_0046c371(*(undefined4 *)(in_ECX + 0x1f3c),8,0,0);
      if (*(int *)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130) != 0) {
        (**(code **)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130))
                  (6,*(undefined4 *)(in_ECX + 4 + *(int *)(in_ECX + 0x1f3c) * 0xc),
                   (int)*(short *)(in_ECX + 0x1f3c),0);
      }
    }
    if (bVar4) {
      if (local_14 != *(int *)(in_ECX + 0x1f3c)) {
        *(int *)(in_ECX + 0x1f3c) = local_14;
        thunk_FUN_0046c371(*(undefined4 *)(in_ECX + 0x1f3c),9,0,0);
        if (*(int *)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130) != 0) {
          (**(code **)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130))
                    (7,*(undefined4 *)(in_ECX + 4 + *(int *)(in_ECX + 0x1f3c) * 0xc),
                     (int)*(short *)(in_ECX + 0x1f3c),0);
        }
      }
    }
    else {
      *(undefined4 *)(in_ECX + 0x1f3c) = 0xffffffff;
    }
  }
  return;
}
```

---

---

## FUN_0046c17b — 0x46c17b

- Classification : internal
- Corps : `0x46c17b–0x46c1b3`
- État : pseudocode obtenu
- Evidence : `ev_bed9cec98fa4ebbd1a1e1942f83b7454afc6dc36246fa62a3bfcad9d59c7567f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0046c17b(void)

{
  int in_ECX;
  undefined4 local_8;
  
  local_8 = 0;
  if (*(int *)(in_ECX + 0x1f3c) != -1) {
    local_8 = *(undefined4 *)(in_ECX + 4 + *(int *)(in_ECX + 0x1f3c) * 0xc);
  }
  return local_8;
}
```

---

---

## FUN_0046c1b4 — 0x46c1b4

- Classification : internal
- Corps : `0x46c1b4–0x46c25c`
- État : pseudocode obtenu
- Evidence : `ev_241803fdaeb978e611e81579680c16ce51af260986fa94b77d75430cc61dad51`
- Note de routage : enregistre le message et ses arguments dans la file de requêtes du gestionnaire; il s'agit du chemin mode 1 de `FUN_0042970c`. Evidence `ev_313d0ccc3d43b5ed7e5d13b4b18d8ceca9606e76b6650bf123b770a1b8afe5f1`.
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a5748` — "mNumRequests!=MAX_WINDOW_REQUESTS"
- `0x4a576c` — "C:\\float\\src\\winman.cpp"

### Pseudocode Ghidra

```c
void FUN_0046c1b4(undefined2 param_1,undefined4 param_2,undefined4 param_3)

{
  int in_ECX;
  
  if (*(short *)(in_ECX + 0x2cf8) == 0x20) {
    thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a576c,0x582,
                       s_mNumRequests__MAX_WINDOW_REQUEST_004a5748);
  }
  *(undefined2 *)(in_ECX + 0x29f8 + *(short *)(in_ECX + 0x2cf8) * 0xc) = param_1;
  *(undefined4 *)(in_ECX + 0x29fc + *(short *)(in_ECX + 0x2cf8) * 0xc) = param_2;
  *(undefined4 *)(in_ECX + 0x2a00 + *(short *)(in_ECX + 0x2cf8) * 0xc) = param_3;
  *(short *)(in_ECX + 0x2cf8) = *(short *)(in_ECX + 0x2cf8) + 1;
  return;
}
```

---

---

## FUN_0046c25d — 0x46c25d

- Classification : internal
- Corps : `0x46c25d–0x46c370`
- État : pseudocode obtenu
- Evidence : `ev_f9974d221df291d4bdd3ef6a0b902ba3139dec986c4afda692ef70b433133d4a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a5784` — "wnd_index >= 0"
- `0x4a5794` — "C:\\float\\src\\winman.cpp"

### Pseudocode Ghidra

```c
void FUN_0046c25d(short param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int in_ECX;
  undefined4 uVar3;
  short local_14;
  short local_10;
  int local_c;
  
  if (-1 < *(short *)(in_ECX + 0x29f2)) {
    local_10 = *(short *)(in_ECX + 8000 + *(short *)(in_ECX + 0x29f2) * 0x130);
    local_14 = 0x49;
    local_c = 0;
    while ((0 < local_10 && (local_c == 0))) {
      if (local_14 < 0) {
        uVar3 = thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5794,0x5b6,
                                   s_wnd_index_>__0_004a5784);
      }
      else {
        uVar3 = 0;
      }
      iVar1 = *(int *)(in_ECX + *(short *)(in_ECX + 0x29f2) * 0x130 + 0x1f44 + local_14 * 4);
      if (iVar1 != 0) {
        local_10 = local_10 + -1;
        piVar2 = *(int **)(in_ECX + 4 + iVar1 * 0xc);
        if ((piVar2[0xe] != 0) || (param_1 == 1)) {
          local_c = (**(code **)(*piVar2 + 4))(param_1,param_2,param_3,uVar3);
        }
      }
      local_14 = local_14 + -1;
    }
  }
  return;
}
```

---

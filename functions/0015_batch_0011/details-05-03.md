# 0015_batch_0011 — détails (3/3)

## FUN_004535e4 — 0x4535e4

- Classification : internal
- Corps : `0x4535e4–0x45388e`
- État : pseudocode obtenu
- Evidence : `ev_31221e7fe9a9d051962a8feae7b513cf35e0906fe9cb40f2fa8885a9c8bde283`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014bf` — `thunk_FUN_00467260`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004535e4(void)

{
  int in_ECX;
  int iVar1;
  short asStackY_1000c [32732];
  int local_4c;
  short local_40;
  short local_3c;
  short local_38 [10];
  undefined *local_24;
  int local_20;
  short local_1c;
  short local_18;
  undefined1 *local_14;
  int local_10;
  short asStack_c [4];
  
  iVar1 = (int)*(short *)(in_ECX + 8);
  local_14 = &DAT_005ec218 + iVar1 * 0x29e8;
  local_10 = (int)(short)(&DAT_005eebf8)[iVar1 * 0x14f4];
  if ((short)(&DAT_005eebf8)[iVar1 * 0x14f4] < 0) {
    local_10 = 0;
  }
  if (0xe < local_10) {
    local_10 = 0xe;
  }
  local_1c = DAT_006136b0 + -1;
  local_38[0] = 0;
  local_38[1] = 0;
  local_38[2] = 0;
  local_38[3] = 0;
  if (*(short *)(in_ECX + 8) == (short)(DAT_006136b0 + -1)) {
    local_38[3] = 1;
    local_38[2] = 1;
    local_38[1] = 1;
    local_38[0] = 1;
  }
  else {
    local_3c = *(short *)(&DAT_004a28c8 + local_10 * 2);
    local_40 = *(short *)(&DAT_004a28e8 + local_10 * 2);
    if (local_3c < -1) {
      local_3c = -1;
    }
    if (3 < local_3c) {
      local_3c = 3;
    }
    if (local_40 < -1) {
      local_40 = -1;
    }
    if (3 < local_40) {
      local_40 = 3;
    }
    if (-1 < local_3c) {
      local_38[local_3c] = 1;
    }
    if (-1 < local_40) {
      local_38[local_40] = 1;
    }
  }
  local_38[4] = 0;
  local_38[5] = 0;
  local_38[6] = 0;
  local_38[7] = 0;
  local_24 = &DAT_005ec640 + iVar1 * 0x29e8;
  for (local_20 = 0; local_20 < (short)(&DAT_005eebc0)[iVar1 * 0x14f4]; local_20 = local_20 + 1) {
    if ((5 < *(int *)(local_24 + 0x10)) && (*(int *)(local_24 + 0x10) < 10)) {
      local_4c = *(int *)(local_24 + 0x10) + -6;
      if (local_4c < 0) {
        local_4c = 0;
      }
      if (3 < local_4c) {
        local_4c = 3;
      }
      local_38[local_4c + 4] = local_38[local_4c + 4] + 1;
    }
    local_24 = local_24 + 0x60;
  }
  local_18 = 0;
  for (local_20 = 0; local_20 < 4; local_20 = local_20 + 1) {
    if (local_38[local_20 + 4] < local_38[local_20]) {
      asStack_c[local_18] = (short)local_20;
      local_18 = local_18 + 1;
    }
  }
  if (local_18 == 0) {
    for (local_20 = 0; local_20 < 4; local_20 = local_20 + 1) {
      if (local_38[local_20] != 0) {
        asStack_c[local_18] = (short)local_20;
        local_18 = local_18 + 1;
      }
    }
  }
  if (local_18 < 1) {
    local_18 = 1;
  }
  if (4 < local_18) {
    local_18 = 4;
  }
  iVar1 = thunk_FUN_00467260((int)local_18);
  return asStack_c[iVar1] + 6;
}
```

---

---

## FUN_0045388f — 0x45388f

- Classification : internal
- Corps : `0x45388f–0x453957`
- État : pseudocode obtenu
- Evidence : `ev_553814d3beb7ec3f9ebdb9102fc26090e4d3cf1dea35923c504e7f6240ac792f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014bf` — `thunk_FUN_00467260`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045388f(void)

{
  int iVar1;
  int in_ECX;
  int local_1c;
  int local_18;
  uint local_14;
  int local_c;
  
  local_14 = 0xc;
  if (DAT_00618e48 == 1) {
    local_14 = 10;
  }
  else if (DAT_00618e48 == 0) {
    local_14 = 6;
  }
  local_18 = (int)((DAT_006136b0 - 1) + ((int)(DAT_006136b0 - 1) >> 0x1f & 3U)) >> 2;
  local_1c = (int)((int)*(short *)(in_ECX + 8) + ((int)*(short *)(in_ECX + 8) >> 0x1f & 3U)) >> 2;
  if (local_18 == 0) {
    local_18 = 1;
    local_1c = 1;
  }
  local_c = local_14 / 2 + (int)((local_14 - local_14 / 2) * local_1c) / local_18;
  if (local_c < 1) {
    local_c = 1;
  }
  if (0xc < local_c) {
    local_c = 0xc;
  }
  iVar1 = thunk_FUN_00467260(local_c);
  return *(undefined4 *)(&DAT_004a2948 + iVar1 * 4);
}
```

---

---

## FUN_00453958 — 0x453958

- Classification : internal
- Corps : `0x453958–0x4539e8`
- État : pseudocode obtenu
- Evidence : `ev_4e9d9f16ef59e1813c25b8fc8c49e2f90f67f2d8723ae7bf25cacaf07607a717`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00453958(void)

{
  int in_ECX;
  undefined4 local_10;
  undefined4 local_8;
  
  if ((((*(uint *)(in_ECX + 0x1c) & 0x90) == 0) &&
      ((((*(uint *)(in_ECX + 0x1c) & 0x400) != 0 || (*(short *)(in_ECX + 0x18) != -1)) ||
       (*(int *)(in_ECX + 4) == 1)))) &&
     ((((*(uint *)(in_ECX + 0x1c) & 0x100) == 0 || (*(short *)(in_ECX + 0x44) < 0x14)) &&
      (*(short *)(in_ECX + 0x58) == 0)))) {
    local_10 = 1;
  }
  else {
    local_10 = 0;
  }
  local_8 = local_10;
  if (*(int *)(in_ECX + 0x10) < 2) {
    local_8 = 0;
  }
  return local_8;
}
```

---

---

## FUN_004539e9 — 0x4539e9

- Classification : internal
- Corps : `0x4539e9–0x453a5e`
- État : pseudocode obtenu
- Evidence : `ev_ebff1d31012dd2ee16d0e674aa0911fd1c2dfed438f43d535755fb935b15d227`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401ff0` — `thunk_FUN_00453958`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004539e9(void)

{
  int iVar1;
  int in_ECX;
  
  if ((((*(int *)(in_ECX + 4) != 2) && (*(int *)(in_ECX + 4) != 3)) &&
      (*(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) & 0xfffffffe,
      *(int *)(in_ECX + 0x14) != -1)) &&
     ((iVar1 = thunk_FUN_00453958(), iVar1 != 0 &&
      ((*(int *)(in_ECX + 0x14) == 4 ||
       (((int)*(char *)(in_ECX + 0x22) & 1 << ((byte)*(undefined4 *)(in_ECX + 0x14) & 0x1f)) != 0)))
      ))) {
    *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 1;
  }
  return;
}
```

---

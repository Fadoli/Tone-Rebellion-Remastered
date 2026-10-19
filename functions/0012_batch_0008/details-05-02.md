# 0012_batch_0008 — détails (2/2)

## FUN_0043530b — 0x43530b

- Classification : internal
- Corps : `0x43530b–0x4354a1`
- État : pseudocode obtenu
- Evidence : `ev_b65156eb13978511b7f06cdb3fee86e7c2c4a37bf3cac67ad0f0badb2f999a68`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40224d` — `thunk_FUN_00450070`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043530b(int param_1)

{
  int iVar1;
  int in_ECX;
  
  *(int *)(in_ECX + 0x174) = param_1;
  *(undefined2 *)(in_ECX + 0x178) = 0;
  if (param_1 == 1) {
    *(undefined2 *)(in_ECX + 0x178) = 1;
    *(undefined2 *)(in_ECX + 0x17e) = 9;
  }
  if (param_1 == 0x11) {
    *(undefined2 *)(in_ECX + 0x178) = 1;
    *(undefined2 *)(in_ECX + 0x17e) = 0xd;
    if ((DAT_0049e9c0 != -1) || (DAT_0049e9c4 != -1)) {
      *(undefined2 *)(in_ECX + 0x17e) = 0xb;
    }
  }
  else if (param_1 == 0x13) {
    *(undefined2 *)(in_ECX + 0x178) = 4;
    *(undefined2 *)(in_ECX + 0x17e) = 0xf;
  }
  else if (param_1 == 0x10) {
    *(undefined2 *)(in_ECX + 0x178) = 2;
    *(undefined2 *)(in_ECX + 0x17e) = 3;
  }
  else if (param_1 == 0x12) {
    *(undefined2 *)(in_ECX + 0x178) = 2;
    *(undefined2 *)(in_ECX + 0x17e) = 5;
  }
  else if (((0x14 < param_1) && (param_1 < 0x1d)) && (*(int *)(in_ECX + 0x16c) != 0)) {
    iVar1 = thunk_FUN_00450070(*(undefined4 *)(in_ECX + 0x16c),param_1);
    *(short *)(in_ECX + 0x178) = (short)(char)(&DAT_004a2898)[iVar1];
    if ((*(short *)(in_ECX + 0x178) == 1) || (*(short *)(in_ECX + 0x178) == 4)) {
      *(undefined2 *)(in_ECX + 0x17e) = 0xb;
    }
    else if (*(short *)(in_ECX + 0x178) == 2) {
      *(undefined2 *)(in_ECX + 0x17e) = 7;
    }
  }
  return;
}
```

---

---

## FUN_004354a2 — 0x4354a2

- Classification : internal
- Corps : `0x4354a2–0x435537`
- État : pseudocode obtenu
- Evidence : `ev_b2285cf0e0e4766d4326255d4e7442bd644268872da28f1a18140867b9945798`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40228e` — `thunk_FUN_00414081`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004354a2(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
                 undefined2 param_5,int param_6,int param_7)

{
  undefined2 local_14;
  undefined2 local_12;
  undefined2 local_10;
  undefined2 local_e;
  undefined2 local_c;
  undefined2 local_a;
  undefined2 local_8;
  undefined2 local_6;
  
  _memset(&local_14,0,0x10);
  local_14 = param_1;
  local_12 = (undefined2)DAT_0049f538;
  local_10 = param_2;
  local_e = (undefined2)param_6;
  if (param_6 == -1) {
    local_e = DAT_0049f53c;
  }
  local_a = (undefined2)param_7;
  if (param_7 == -1) {
    local_a = DAT_0049f53c;
  }
  local_c = param_3;
  local_8 = param_4;
  local_6 = param_5;
  thunk_FUN_00414081(1,&local_14,0x10);
  return;
}
```

---

---

## FUN_00435538 — 0x435538

- Classification : internal
- Corps : `0x435538–0x435580`
- État : pseudocode obtenu
- Evidence : `ev_804d4e9d826e6b0634ab0f56a1d5fbe497a086d78e2c2f128b0dfdb02987a467`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40228e` — `thunk_FUN_00414081`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00435538(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_1c = param_1;
  local_18 = (int)DAT_0049f53c;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  local_8 = param_5;
  thunk_FUN_00414081(2,&local_1c,0x18);
  return;
}
```

---

---

## FUN_00435581 — 0x435581

- Classification : internal
- Corps : `0x435581–0x435825`
- État : pseudocode obtenu
- Evidence : `ev_348f5497af7071783e238a442881827d9f24b812a0a6f4663070125e1d452240`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40173a` — `thunk_FUN_004672a6`
- `0x40186b` — `thunk_FUN_004656d6`
- `0x401d11` — `thunk_FUN_00456a87`
- `0x4021ad` — `thunk_FUN_004641de`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00435581(int param_1,int param_2,int *param_3,int *param_4)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int *piVar4;
  int in_ECX;
  int iVar5;
  undefined2 extraout_var;
  int local_44;
  int local_2c;
  int local_24;
  short *local_20;
  short local_1c;
  short local_14;
  
  param_1 = param_1 + *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
  if ((*param_3 == 0) || (*param_3 == 2)) {
    iVar3 = thunk_FUN_004656d6((int)DAT_0049f53c,0xfffffffe);
    for (local_14 = 0; local_14 < iVar3; local_14 = local_14 + 1) {
      iVar5 = (short)(&DAT_00618fb4)[local_14] * 0x4c;
      if (((*(uint *)(&DAT_006137d4 + iVar5) & 1) == 0) &&
         (iVar5 = thunk_FUN_004672a6(param_1,param_2,(int)*(short *)(&DAT_006137c8 + iVar5),
                                     (int)*(short *)(&DAT_006137ca + iVar5)), iVar5 < 0x14)) {
        *param_3 = 2;
        *param_4 = (int)(short)(&DAT_00618fb4)[local_14];
        return;
      }
    }
  }
  if ((*param_3 == 0) || (*param_3 == 1)) {
    local_20 = (short *)(*(int *)(in_ECX + 0x9c) + 0x428);
    for (local_1c = 0; local_1c < *(short *)(*(int *)(in_ECX + 0x9c) + 0x29a8);
        local_1c = local_1c + 1) {
      if (param_1 - *local_20 < 0) {
        local_44 = -(param_1 - *local_20);
      }
      else {
        local_44 = param_1 - *local_20;
      }
      sVar1 = local_20[1];
      if ((local_44 < 0x65) &&
         (((*(int *)(local_20 + 2) != 0 ||
           (((int)(char)local_20[0x11] & 1 << ((byte)DAT_0049f538 & 0x1f)) != 0)) ||
          (*(int *)(local_20 + 8) != 0)))) {
        sVar2 = DAT_0049f564;
        if (*(int *)(local_20 + 2) == 0) {
          sVar2 = *(short *)(&DAT_0049f560 + *(int *)(local_20 + 6) * 2);
        }
        local_2c = (int)sVar2;
        local_24 = 0;
        if (*(int *)(local_20 + 8) != 0) {
          piVar4 = (int *)thunk_FUN_004641de(*(undefined4 *)(local_20 + 10),
                                             *(undefined4 *)(local_20 + 8));
          iVar3 = thunk_FUN_00456a87(CONCAT22(extraout_var,*(undefined2 *)((int)piVar4 + 0x16)));
          if (iVar3 != 0) {
            local_24 = -(uint)*(byte *)(iVar3 + 2);
          }
          if (*(int *)(local_20 + 2) == 0) {
            local_2c = (int)*(short *)(&DAT_0049f560 + *piVar4 * 2);
          }
        }
        iVar3 = local_2c / 2;
        if (-iVar3 < local_24) {
          local_24 = -iVar3;
        }
        if (((local_44 < local_2c) && (local_24 < param_2 - sVar1)) && (param_2 - sVar1 < iVar3)) {
          *param_3 = 1;
          *param_4 = (int)local_1c;
          return;
        }
      }
      local_20 = local_20 + 0x30;
    }
  }
  *param_3 = 0;
  return;
}
```

---

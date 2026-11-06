# 0021_batch_0017 — détails (2/2)

## FUN_00482b20 — 0x482b20

- Classification : internal
- Corps : `0x482b20–0x482d61`
- État : pseudocode obtenu
- Evidence : `ev_2ec044ec430a79ab7afd1d9cca0895cd598a7706680ab82cdb6019ed3aaad19d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482890` — `FUN_00482890`
- `0x482970` — `__CopyMan`
- `0x4829c0` — `__FillZeroMan`
- `0x4829f0` — `__IsZeroMan`
- `0x482a30` — `FUN_00482a30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00482b20(ushort *param_1,uint *param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  undefined1 local_34 [16];
  uint local_24;
  undefined4 local_20;
  uint local_1c;
  uint local_18;
  int local_14;
  int local_c;
  int local_8;
  
  local_8 = (param_1[5] & 0x7fff) - 0x3fff;
  local_24 = param_1[5] & 0x8000;
  local_1c = *(uint *)(param_1 + 3);
  local_18 = *(uint *)(param_1 + 1);
  local_14 = (uint)*param_1 << 0x10;
  if (local_8 == -0x3fff) {
    local_c = 0;
    iVar1 = __IsZeroMan(&local_1c);
    if (iVar1 == 0) {
      __FillZeroMan(&local_1c);
      local_20 = 2;
    }
    else {
      local_20 = 0;
    }
  }
  else {
    __CopyMan(local_34,&local_1c);
    iVar1 = FUN_00482890(&local_1c,param_3[2]);
    if (iVar1 != 0) {
      local_8 = local_8 + 1;
    }
    if (local_8 < param_3[1] - param_3[2]) {
      __FillZeroMan(&local_1c);
      local_c = 0;
      local_20 = 2;
    }
    else if (param_3[1] < local_8) {
      if (local_8 < *param_3) {
        local_c = local_8 + param_3[5];
        local_1c = local_1c & 0x7fffffff;
        FUN_00482a30(&local_1c,param_3[3]);
        local_20 = 0;
      }
      else {
        __FillZeroMan(&local_1c);
        local_1c = local_1c | 0x80000000;
        FUN_00482a30(&local_1c,param_3[3]);
        local_c = *param_3 + param_3[5];
        local_20 = 1;
      }
    }
    else {
      iVar1 = param_3[1] - local_8;
      __CopyMan(&local_1c,local_34,iVar1);
      FUN_00482a30(&local_1c,iVar1);
      FUN_00482890(&local_1c,param_3[2]);
      FUN_00482a30(&local_1c,param_3[3] + 1);
      local_c = 0;
      local_20 = 2;
    }
  }
  uVar2 = local_1c | local_c << (0x20U - ((char)param_3[3] + '\x01') & 0x1f) |
          -(uint)(local_24 != 0) & 0x80000000;
  if (param_3[4] == 0x40) {
    param_2[1] = uVar2;
    *param_2 = local_18;
  }
  else if (param_3[4] == 0x20) {
    *param_2 = uVar2;
  }
  return local_20;
}
```

---

---

## FUN_00482d70 — 0x482d70

- Classification : internal
- Corps : `0x482d70–0x482d89`
- État : pseudocode obtenu
- Evidence : `ev_8e592cf03619d0a00e544bf04c99c5eba609e043a9261f2e987087469bdbc0af`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482b20` — `FUN_00482b20`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00482d70(undefined4 param_1,undefined4 param_2)

{
  FUN_00482b20(param_1,param_2,&DAT_004a8ac0);
  return;
}
```

---

---

## FUN_00482d90 — 0x482d90

- Classification : internal
- Corps : `0x482d90–0x482da9`
- État : pseudocode obtenu
- Evidence : `ev_39321083f888f68bc39c8b372eea9a1f795fe39fcd9cd9a0888d7fe751a81769`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482b20` — `FUN_00482b20`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00482d90(undefined4 param_1,undefined4 param_2)

{
  FUN_00482b20(param_1,param_2,&DAT_004a8ad8);
  return;
}
```

---

---

## FUN_00482db0 — 0x482db0

- Classification : internal
- Corps : `0x482db0–0x482e6e`
- État : pseudocode obtenu
- Evidence : `ev_e08870dcb8102aeae145b454408dac47bb91a5c30dcc47a4d92bf2096def5ddf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482890` — `FUN_00482890`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_00482db0(ushort *param_1,undefined4 *param_2)

{
  ushort uVar1;
  int iVar2;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  
  local_8 = CONCAT22(local_8._2_2_,param_1[5]) & 0xffff7fff;
  uVar1 = param_1[5];
  local_14 = *(undefined4 *)(param_1 + 3);
  local_10 = *(undefined4 *)(param_1 + 1);
  local_c = (uint)*param_1 << 0x10;
  iVar2 = FUN_00482890(&local_14,0x40);
  if (iVar2 != 0) {
    local_14 = 0x80000000;
    local_8 = (uint)(ushort)((short)local_8 + 1);
  }
  param_2[1] = local_14;
  *param_2 = local_10;
  *(ushort *)(param_2 + 2) = uVar1 & 0x8000 | (ushort)local_8;
  return (local_8 & 0xffff) == 0x7fff;
}
```

---

---

## FUN_00482e70 — 0x482e70

- Classification : internal
- Corps : `0x482e70–0x482ea5`
- État : pseudocode obtenu
- Evidence : `ev_214fe41e57625eab2abfd8e67a5b938e4facfeb506f9593497d860eaba520b19`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482d70` — `FUN_00482d70`
- `0x4853a0` — `FUN_004853a0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00482e70(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_14 [4];
  undefined1 local_10 [12];
  
  FUN_004853a0(local_10,local_14,param_2,0,0,0,0);
  FUN_00482d70(local_10,param_1);
  return;
}
```

---

---

## FUN_00482eb0 — 0x482eb0

- Classification : internal
- Corps : `0x482eb0–0x482ee5`
- État : pseudocode obtenu
- Evidence : `ev_45027a21e31ac21117cb7795b8182ec29006a251595dad77b8d2786f37329899`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482db0` — `FUN_00482db0`
- `0x4853a0` — `FUN_004853a0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00482eb0(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_14 [4];
  undefined1 local_10 [12];
  
  FUN_004853a0(local_10,local_14,param_2,1,0,0,0);
  FUN_00482db0(local_10,param_1);
  return;
}
```

---

---

## FUN_00482ef0 — 0x482ef0

- Classification : internal
- Corps : `0x482ef0–0x482f25`
- État : pseudocode obtenu
- Evidence : `ev_9afd539bb36fc717ab3836b7650f73621973ed3ce287eef90f78e4ddd4468877`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482d90` — `FUN_00482d90`
- `0x4853a0` — `FUN_004853a0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00482ef0(undefined4 param_1,undefined4 param_2)

{
  undefined1 local_14 [4];
  undefined1 local_10 [12];
  
  FUN_004853a0(local_10,local_14,param_2,0,0,0,0);
  FUN_00482d90(local_10,param_1);
  return;
}
```

---

---

## FUN_00482f30 — 0x482f30

- Classification : internal
- Corps : `0x482f30–0x483016`
- État : pseudocode obtenu
- Evidence : `ev_ea358ce1c9f39077a7a2b7b838c549dda545bc18aa1cf2d15e97c2a229a0b5d4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472da0` — `FUN_00472da0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00482f30(char *param_1,int param_2,int param_3)

{
  char cVar1;
  char *pcVar2;
  char *local_c;
  char *local_8;
  
  local_c = *(char **)(param_3 + 0xc);
  *param_1 = '0';
  pcVar2 = param_1;
  for (; local_8 = pcVar2 + 1, 0 < param_2; param_2 = param_2 + -1) {
    if (*local_c == '\0') {
      cVar1 = '0';
    }
    else {
      cVar1 = *local_c;
      local_c = local_c + 1;
    }
    *local_8 = cVar1;
    pcVar2 = local_8;
  }
  *local_8 = '\0';
  if ((-1 < param_2) && (local_8 = pcVar2, '4' < *local_c)) {
    for (; *local_8 == '9'; local_8 = local_8 + -1) {
      *local_8 = '0';
    }
    *local_8 = *local_8 + '\x01';
  }
  if (*param_1 == '1') {
    *(int *)(param_3 + 4) = *(int *)(param_3 + 4) + 1;
  }
  else {
    FUN_00472da0(param_1,param_1 + 1);
  }
  return;
}
```

---

---

## FUN_00483020 — 0x483020

- Classification : internal
- Corps : `0x483020–0x483090`
- État : pseudocode obtenu
- Evidence : `ev_798071827b42b9371f454dc3b7aebcd91b7a12c5a1543e56399c97b0532ff311`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4830a0` — `FUN_004830a0`
- `0x488340` — `FUN_00488340`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_00483020(void)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined2 local_8;
  
  FUN_004830a0(&local_10,&stack0x00000004);
  _DAT_00632890 = FUN_00488340(local_10,local_c,local_8,0x11,0,&DAT_00632868);
  _DAT_00632888 = (int)DAT_0063286a;
  _DAT_0063288c = (int)DAT_00632868;
  _DAT_00632894 = &DAT_0063286c;
  return &DAT_00632888;
}
```

---

---

## FUN_004830a0 — 0x4830a0

- Classification : internal
- Corps : `0x4830a0–0x483201`
- État : pseudocode obtenu
- Evidence : `ev_7b55156b9e00821ffc387ab456c613c04e576c00fb91e82a517bf7af54888ed3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004830a0(uint *param_1,uint *param_2)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  ushort uVar4;
  short local_18;
  uint local_10;
  
  local_10 = 0x80000000;
  iVar3 = (int)(*(ushort *)((int)param_2 + 6) & 0x7ff0) >> 4;
  uVar1 = *(ushort *)((int)param_2 + 6);
  uVar2 = *param_2;
  local_18 = (short)iVar3;
  if (iVar3 == 0) {
    if (((param_2[1] & 0xfffff) == 0) && (uVar2 == 0)) {
      param_1[1] = 0;
      *param_1 = 0;
      *(undefined2 *)(param_1 + 2) = 0;
      return;
    }
    uVar4 = 0x3c01;
    local_10 = 0;
  }
  else if (iVar3 == 0x7ff) {
    uVar4 = 0x7fff;
  }
  else {
    uVar4 = local_18 + 0x3c00;
  }
  param_1[1] = local_10 | (param_2[1] & 0xfffff) << 0xb | uVar2 >> 0x15;
  *param_1 = uVar2 << 0xb;
  while ((param_1[1] & 0x80000000) == 0) {
    param_1[1] = param_1[1] << 1 | (uint)((*param_1 & 0x80000000) != 0);
    *param_1 = *param_1 << 1;
    uVar4 = uVar4 - 1;
  }
  *(ushort *)(param_1 + 2) = uVar1 & 0x8000 | uVar4;
  return;
}
```

---

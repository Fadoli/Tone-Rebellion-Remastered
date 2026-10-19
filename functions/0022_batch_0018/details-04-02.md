# 0022_batch_0018 — détails (2/3)

## FUN_00488200 — 0x488200

- Classification : internal
- Corps : `0x488200–0x48833a`
- État : pseudocode obtenu
- Evidence : `ev_f25b30ba57b4907636525051e54cd18c1a7badd656c80488b6b4f1aa5a7b72a6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x488080` — `___add_12`
- `0x488130` — `___shl_12`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00488200(char *param_1,int param_2,uint *param_3)

{
  short local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  local_14 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    local_10 = *param_3;
    local_c = param_3[1];
    local_8 = param_3[2];
    ___shl_12(param_3);
    ___shl_12(param_3);
    ___add_12(param_3,&local_10);
    ___shl_12(param_3);
    local_10 = (uint)*param_1;
    local_c = 0;
    local_8 = 0;
    ___add_12(param_3,&local_10);
    param_1 = param_1 + 1;
  }
  while (param_3[2] == 0) {
    param_3[2] = param_3[1] >> 0x10;
    param_3[1] = param_3[1] << 0x10 | *param_3 >> 0x10;
    *param_3 = *param_3 << 0x10;
    local_14 = local_14 + -0x10;
  }
  while ((param_3[2] & 0x8000) == 0) {
    ___shl_12(param_3);
    local_14 = local_14 + -1;
  }
  *(short *)((int)param_3 + 10) = local_14;
  return;
}
```

---

---

## FUN_00488340 — 0x488340

- Classification : internal
- Corps : `0x488340–0x488855`
- État : pseudocode obtenu
- Evidence : `ev_da956eda13f984bad08b4180e2f67ec8305fc5293fd06a75c20838d21a4a04d2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472da0` — `FUN_00472da0`
- `0x488080` — `___add_12`
- `0x488130` — `___shl_12`
- `0x488190` — `___shr_12`
- `0x489670` — `FUN_00489670`
- `0x489ac0` — `FUN_00489ac0`

### Chaînes référencées

- `0x4962fc` — "1#QNAN"
- `0x496304` — "1#INF"
- `0x49630c` — "1#IND"
- `0x496314` — "1#SNAN"

### Pseudocode Ghidra

```c
undefined4
FUN_00488340(int param_1,uint param_2,ushort param_3,int param_4,uint param_5,short *param_6)

{
  int iVar1;
  ushort uVar2;
  char *pcVar3;
  uint local_78;
  short local_60;
  undefined4 local_5c;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  undefined1 local_51;
  undefined1 local_50;
  undefined1 local_4f;
  undefined1 local_4e;
  undefined1 local_4d;
  int local_4c;
  int local_48;
  ushort local_44;
  undefined2 uStack_42;
  undefined2 local_40;
  undefined2 uStack_3e;
  undefined2 local_3c;
  undefined2 uStack_3a;
  undefined2 uStack_38;
  undefined2 uStack_36;
  undefined2 uStack_34;
  undefined1 local_32;
  char cStack_31;
  undefined2 uStack_30;
  undefined1 uStack_2e;
  char cStack_2d;
  uint local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  ushort local_10;
  int local_c;
  short *local_8;
  
  _local_40 = CONCAT22(uStack_3e,0x4d);
  local_24 = 0x134312f4;
  local_58 = 0xcc;
  local_57 = 0xcc;
  local_56 = 0xcc;
  local_55 = 0xcc;
  local_54 = 0xcc;
  local_53 = 0xcc;
  local_52 = 0xcc;
  local_51 = 0xcc;
  local_50 = 0xcc;
  local_4f = 0xcc;
  local_4e = 0xfb;
  local_4d = 0x3f;
  local_5c = 1;
  local_28 = param_2;
  local_4c = param_1;
  if ((param_3 & 0x8000) == 0) {
    *(undefined1 *)(param_6 + 1) = 0x20;
  }
  else {
    *(undefined1 *)(param_6 + 1) = 0x2d;
  }
  if ((((param_3 & 0x7fff) == 0) && (param_2 == 0)) && (param_1 == 0)) {
    *param_6 = 0;
    *(undefined1 *)(param_6 + 1) = 0x20;
    *(undefined1 *)((int)param_6 + 3) = 1;
    *(undefined1 *)(param_6 + 2) = 0x30;
    *(undefined1 *)((int)param_6 + 5) = 0;
    local_5c = 1;
  }
  else if ((param_3 & 0x7fff) == 0x7fff) {
    *param_6 = 1;
    if (((param_2 == 0x80000000) && (param_1 == 0)) || ((param_2 & 0x40000000) != 0)) {
      if ((((param_3 & 0x8000) == 0) || (param_2 != 0xc0000000)) || (param_1 != 0)) {
        if ((param_2 == 0x80000000) && (param_1 == 0)) {
          FUN_00472da0(param_6 + 2,"1#INF");
          *(undefined1 *)((int)param_6 + 3) = 5;
        }
        else {
          FUN_00472da0(param_6 + 2,"1#QNAN");
          *(undefined1 *)((int)param_6 + 3) = 6;
        }
      }
      else {
        FUN_00472da0(param_6 + 2,"1#IND");
        *(undefined1 *)((int)param_6 + 3) = 5;
      }
    }
    else {
      FUN_00472da0(param_6 + 2,"1#SNAN");
      *(undefined1 *)((int)param_6 + 3) = 6;
    }
    local_5c = 0;
  }
  else {
    local_10 = param_3 & 0xff;
    uVar2 = (ushort)(byte)(param_2 >> 0x18);
    _local_44 = CONCAT22(uStack_42,uVar2);
    local_c = (param_3 & 0x7fff) * 0x4d10 + (uint)(param_3 >> 8 & 0x7f) * 0x4d + (uint)uVar2 * 0x9a
              + -0x134312f4;
    local_60 = (short)((uint)local_c >> 0x10);
    local_32 = (undefined1)(param_3 & 0x7fff);
    cStack_31 = (char)((param_3 & 0x7fff) >> 8);
    uStack_36 = (undefined2)param_2;
    uStack_34 = (undefined2)(param_2 >> 0x10);
    uStack_3a = (undefined2)param_1;
    uStack_38 = (undefined2)((uint)param_1 >> 0x10);
    local_3c = 0;
    FUN_00489ac0(&local_3c,-(int)local_60,1);
    if (0x3ffe < CONCAT11(cStack_31,local_32)) {
      local_60 = local_60 + 1;
      FUN_00489670(&local_3c,&local_58);
    }
    *param_6 = local_60;
    if (((param_5 & 1) == 0) || (param_4 = param_4 + local_60, 0 < param_4)) {
      if (0x15 < param_4) {
        param_4 = 0x15;
      }
      iVar1 = CONCAT11(cStack_31,local_32) - 0x3ffe;
      uStack_30 = (undefined2)iVar1;
      uStack_2e = (undefined1)((uint)iVar1 >> 0x10);
      cStack_2d = (char)((uint)iVar1 >> 0x18);
      local_32 = 0;
      cStack_31 = '\0';
      for (local_48 = 0; local_48 < 8; local_48 = local_48 + 1) {
        ___shl_12(&local_3c);
      }
      if (cStack_2d < '\0') {
        for (local_78 = -CONCAT13(cStack_2d,CONCAT12(uStack_2e,uStack_30)) & 0xff; 0 < (int)local_78
            ; local_78 = local_78 - 1) {
          ___shr_12(&local_3c);
        }
      }
      local_8 = param_6 + 2;
      for (local_14 = param_4 + 1; 0 < local_14; local_14 = local_14 + -1) {
        local_20 = CONCAT22(uStack_3a,local_3c);
        local_1c = CONCAT22(uStack_36,uStack_38);
        local_18 = CONCAT13(cStack_31,CONCAT12(local_32,uStack_34));
        ___shl_12(&local_3c);
        ___shl_12(&local_3c);
        ___add_12(&local_3c,&local_20);
        ___shl_12(&local_3c);
        *(char *)local_8 = cStack_31 + '0';
        local_8 = (short *)((int)local_8 + 1);
        cStack_31 = '\0';
      }
      pcVar3 = (char *)((int)local_8 + -1);
      local_8 = local_8 + -1;
      if (*pcVar3 < '5') {
        for (; (param_6 + 2 <= local_8 && ((char)*local_8 == '0'));
            local_8 = (short *)((int)local_8 + -1)) {
        }
        if (local_8 < param_6 + 2) {
          *param_6 = 0;
          *(undefined1 *)(param_6 + 1) = 0x20;
          *(undefined1 *)((int)param_6 + 3) = 1;
          *(undefined1 *)(param_6 + 2) = 0x30;
          *(undefined1 *)((int)param_6 + 5) = 0;
          return 1;
        }
      }
      else {
        for (; (param_6 + 2 <= local_8 && ((char)*local_8 == '9'));
            local_8 = (short *)((int)local_8 + -1)) {
          *(char *)local_8 = '0';
        }
        if (local_8 < param_6 + 2) {
          local_8 = (short *)((int)local_8 + 1);
          *param_6 = *param_6 + 1;
        }
        *(char *)local_8 = (char)*local_8 + '\x01';
      }
      *(char *)((int)param_6 + 3) = ((char)local_8 - ((char)param_6 + '\x04')) + '\x01';
      *(undefined1 *)((int)param_6 + *(char *)((int)param_6 + 3) + 4) = 0;
    }
    else {
      *param_6 = 0;
      *(undefined1 *)(param_6 + 1) = 0x20;
      *(undefined1 *)((int)param_6 + 3) = 1;
      *(undefined1 *)(param_6 + 2) = 0x30;
      *(undefined1 *)((int)param_6 + 5) = 0;
      local_5c = 1;
    }
  }
  return local_5c;
}
```

---

---

## FUN_00488860 — 0x488860

- Classification : internal
- Corps : `0x488860–0x48890b`
- État : pseudocode obtenu
- Evidence : `ev_88c9d25497e6820a77bd99bab4a2e91e7fca2a9e15a3e49d8f893d558bf2a566`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4748a0` — `FUN_004748a0`
- `0x475780` — `FUN_00475780`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00488860(void)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  for (local_c = 3; local_c < DAT_00633d00; local_c = local_c + 1) {
    if (*(int *)(DAT_006329bc + local_c * 4) != 0) {
      if ((*(uint *)(*(int *)(DAT_006329bc + local_c * 4) + 0xc) & 0x83) != 0) {
        iVar1 = FUN_004748a0(*(undefined4 *)(DAT_006329bc + local_c * 4));
        if (iVar1 != -1) {
          local_8 = local_8 + 1;
        }
      }
      if (0x13 < local_c) {
        FUN_00475780(*(undefined4 *)(DAT_006329bc + local_c * 4),2);
        *(undefined4 *)(DAT_006329bc + local_c * 4) = 0;
      }
    }
  }
  return local_8;
}
```

---

---

## FUN_00488910 — 0x488910

- Classification : internal
- Corps : `0x488910–0x488963`
- État : pseudocode obtenu
- Evidence : `ev_fa0203bb1e26338038c53c8154451e33f15af074e7ed7090991789986564caf3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4893c0` — `__umatherr`
- `0x4895b0` — `FUN_004895b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00488910(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  float10 fVar1;
  
  if (DAT_004a90f8 == 0) {
    fVar1 = (float10)__umatherr(1,param_1,param_2,param_3,0,0,param_2,param_3,param_4);
  }
  else {
    _DAT_0063251c = 0x21;
    FUN_004895b0(param_4,0xffff);
    fVar1 = (float10)(double)CONCAT44(param_3,param_2);
  }
  return fVar1;
}
```

---

---

## FUN_00488970 — 0x488970

- Classification : internal
- Corps : `0x488970–0x4889d5`
- État : pseudocode obtenu
- Evidence : `ev_1e169c356f9d8bccb6ad663c77b27279473c48e8b4f5915b4e109cad79ac0708`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4893c0` — `__umatherr`
- `0x4895b0` — `FUN_004895b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00488970(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5,undefined4 param_6)

{
  double dVar1;
  float10 fVar2;
  
  dVar1 = (double)CONCAT44(param_3,param_2) + (double)CONCAT44(param_5,param_4);
  if (DAT_004a90f8 == 0) {
    fVar2 = (float10)__umatherr(1,param_1,param_2,param_3,param_4,param_5,dVar1,param_6);
  }
  else {
    _DAT_0063251c = 0x21;
    FUN_004895b0(param_6,0xffff);
    fVar2 = (float10)dVar1;
  }
  return fVar2;
}
```

---

---

## FUN_004889e0 — 0x4889e0

- Classification : internal
- Corps : `0x4889e0–0x488a91`
- État : pseudocode obtenu
- Evidence : `ev_57a4b08383f6a5827127ce8594dc0bed35550d67111defc27037463e56c14c03`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x488b70` — `FUN_00488b70`
- `0x489040` — `FUN_00489040`
- `0x4893c0` — `__umatherr`
- `0x489460` — `__set_errno`
- `0x4894e0` — `FUN_004894e0`
- `0x4895b0` — `FUN_004895b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_004889e0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  float10 fVar2;
  undefined1 local_60 [56];
  uint local_28;
  int local_8;
  
  iVar1 = FUN_00489040(param_1,&param_5,param_7);
  if (iVar1 == 0) {
    local_28 = local_28 & 0xfffffffe;
    FUN_00488b70(local_60,&param_7,param_1,param_2,&param_3,&param_5);
  }
  local_8 = FUN_004894e0(param_1);
  if ((DAT_004a90f8 == 0) && (local_8 != 0)) {
    fVar2 = (float10)__umatherr(local_8,param_2,param_3,param_4,0,0,param_5,param_6,param_7);
  }
  else {
    __set_errno(local_8);
    FUN_004895b0(param_7,0xffff);
    fVar2 = (float10)(double)CONCAT44(param_6,param_5);
  }
  return fVar2;
}
```

---

---

## FUN_00488aa0 — 0x488aa0

- Classification : internal
- Corps : `0x488aa0–0x488b6d`
- État : pseudocode obtenu
- Evidence : `ev_bc77c8fcf4e877d6b003a409c2ffb1a9512a5f55fdad558166e3a7b4b83c4237`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x488b70` — `FUN_00488b70`
- `0x489040` — `FUN_00489040`
- `0x4893c0` — `__umatherr`
- `0x489460` — `__set_errno`
- `0x4894e0` — `FUN_004894e0`
- `0x4895b0` — `FUN_004895b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_00488aa0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                    undefined4 param_9)

{
  int iVar1;
  float10 fVar2;
  undefined1 local_60 [40];
  undefined4 local_38;
  undefined4 local_34;
  uint local_28;
  int local_8;
  
  iVar1 = FUN_00489040(param_1,&param_7,param_9);
  if (iVar1 == 0) {
    local_28 = local_28 & 0xffffffe1 | 3;
    local_38 = param_5;
    local_34 = param_6;
    FUN_00488b70(local_60,&param_9,param_1,param_2,&param_3,&param_7);
  }
  local_8 = FUN_004894e0(param_1);
  if ((DAT_004a90f8 == 0) && (local_8 != 0)) {
    fVar2 = (float10)__umatherr(local_8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_9);
  }
  else {
    __set_errno(local_8);
    FUN_004895b0(param_9,0xffff);
    fVar2 = (float10)(double)CONCAT44(param_8,param_7);
  }
  return fVar2;
}
```

---

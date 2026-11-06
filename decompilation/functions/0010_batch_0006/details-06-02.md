# 0010_batch_0006 — détails (2/2)

## FUN_00420a55 — 0x420a55

- Classification : internal
- Corps : `0x420a55–0x420d82`
- État : pseudocode obtenu
- Evidence : `ev_76a4661cb67067b44054706649c3ff1f80a7e9eec7116d8c36177f340ab15b36`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401401` — `thunk_FUN_0041e427`
- `0x4016c7` — `thunk_FUN_00420ed9`
- `0x4016e0` — `thunk_FUN_00420635`
- `0x40173a` — `thunk_FUN_004672a6`
- `0x401a69` — `thunk_FUN_00452ceb`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x40239c` — `thunk_FUN_0041e28e`

### Chaînes référencées

- `0x49d2b4` — "C:\\float\\src\\floater.cpp"

### Pseudocode Ghidra

```c
undefined2 FUN_00420a55(short param_1,int param_2,short param_3)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  undefined4 *in_ECX;
  int local_84;
  int aiStack_78 [10];
  int local_50;
  short *local_4c;
  int local_48;
  int local_44 [10];
  int local_1c;
  undefined1 *local_18;
  short local_14 [2];
  short local_10 [2];
  int local_c;
  undefined2 local_8;
  
  local_8 = 0xffff;
  local_18 = &DAT_005ec218 + param_1 * 0x29e8;
  local_4c = (short *)(&DAT_005ec640 + param_1 * 0x29e8);
  local_50 = 0;
  local_c = -1;
  if (param_2 == 4) {
    thunk_FUN_0041e427(CONCAT22((short)((uint)local_4c >> 0x10),param_3),local_10,local_14);
  }
  for (local_48 = 0; local_48 < *(short *)(local_18 + 0x29a8); local_48 = local_48 + 1) {
    bVar1 = false;
    switch(param_2) {
    case 0:
      iVar3 = thunk_FUN_00452ceb((int)param_3,*in_ECX);
      if ((iVar3 == 0) || (iVar3 = thunk_FUN_00420ed9(local_4c), iVar3 == 0)) {
        bVar1 = false;
      }
      else {
        bVar1 = true;
      }
      break;
    case 1:
      bVar1 = true;
      break;
    case 2:
      if ((*(int *)(local_4c + 2) == (int)param_3) &&
         ((*(int *)(local_4c + 10) == -1 ||
          ((*(int *)(local_4c + 8) == 1 && (*(int *)(local_4c + 0x12) == 1)))))) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      break;
    case 3:
      if ((((*(int *)(local_4c + 2) == 0) && (*(int *)(local_4c + 10) != 4)) &&
          ((0x24 < *(int *)(local_4c + 8) &&
           ((*(int *)(local_4c + 8) < 0x35 && (*(int *)(local_4c + 8) != 0x2a)))))) &&
         (iVar3 = thunk_FUN_00420635(local_4c), iVar3 < param_3)) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      break;
    case 4:
      if ((((*(int *)(local_4c + 10) == 4) &&
           (iVar3 = thunk_FUN_004672a6((int)local_10[0],(int)local_14[0],(int)*local_4c,
                                       (int)local_4c[1]), iVar3 < 0x5a)) &&
          (*(int *)(local_4c + 8) < 0x16)) && ((*(uint *)(local_4c + 0xe) & 0x90) == 0)) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      break;
    default:
      thunk_FUN_00414b64(s_C__float_src_floater_cpp_0049d2b4,0x666,&DAT_0049d2b0);
    }
    if (bVar1) {
      iVar3 = thunk_FUN_00420635(local_4c);
      if (local_50 < 10) {
        aiStack_78[local_50] = local_48;
        local_44[local_50] = iVar3;
        if ((local_c == -1) || (local_1c < iVar3)) {
          local_c = local_50;
          local_1c = iVar3;
        }
        local_50 = local_50 + 1;
      }
      else if (iVar3 < local_1c) {
        aiStack_78[local_c] = local_48;
        local_44[local_c] = iVar3;
        local_c = -1;
        for (local_84 = 0; local_84 < local_50; local_84 = local_84 + 1) {
          if ((local_c == -1) || (local_1c < local_44[local_84])) {
            local_1c = local_44[local_84];
            local_c = local_84;
          }
        }
      }
    }
    local_4c = local_4c + 0x30;
  }
  if (local_50 != 0) {
    sVar2 = thunk_FUN_0041e28e(local_44,CONCAT22(*(short *)(local_18 + 0x29a8) >> 0xf,
                                                 (undefined2)local_50));
    local_8 = (undefined2)aiStack_78[sVar2];
  }
  return local_8;
}
```

---

---

## FUN_00420d97 — 0x420d97

- Classification : internal
- Corps : `0x420d97–0x420dbc`
- État : pseudocode obtenu
- Evidence : `ev_0a150ef6299ccee55e14aeab45e2de16381b5142b4063cda099503d87e818883`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b72` — `thunk_FUN_00420a55`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00420d97(undefined4 param_1,undefined2 param_2)

{
  int in_ECX;
  
  thunk_FUN_00420a55(*(undefined2 *)(in_ECX + 0xe),param_1,param_2);
  return;
}
```

---

---

## FUN_00420dbd — 0x420dbd

- Classification : internal
- Corps : `0x420dbd–0x420e93`
- État : pseudocode obtenu
- Evidence : `ev_1f18388d9e85610e04df8eb3ddf751eeece0b60f158c1e56fcfdeb44b58385f5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40100f` — `thunk_FUN_00420d97`
- `0x401b72` — `thunk_FUN_00420a55`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00420dbd(undefined2 param_1,undefined2 *param_2,short *param_3)

{
  short sVar1;
  int *in_ECX;
  int local_c;
  undefined1 *local_8;
  
  *param_2 = 0xffff;
  *param_3 = -1;
  sVar1 = thunk_FUN_00420d97(0,param_1);
  if (sVar1 == -1) {
    local_8 = &DAT_005ec218;
    for (local_c = 0; local_c < (int)(uint)DAT_006136b0; local_c = local_c + 1) {
      if (*(int *)(local_8 + *in_ECX * 4 + 0x29ac) != 0) {
        sVar1 = thunk_FUN_00420a55(CONCAT22((short)((uint)*in_ECX >> 0x10),(undefined2)local_c),0,
                                   param_1);
        if (sVar1 != -1) {
          *param_2 = (undefined2)local_c;
          *param_3 = sVar1;
          return;
        }
      }
      local_8 = local_8 + 0x29e8;
    }
  }
  else {
    *param_2 = *(undefined2 *)((int)in_ECX + 0xe);
    *param_3 = sVar1;
  }
  return;
}
```

---

---

## FUN_00420e94 — 0x420e94

- Classification : internal
- Corps : `0x420e94–0x420ed8`
- État : pseudocode obtenu
- Evidence : `ev_2bce5601ef6e25fe752eb078a75b21fc9ec5ddd5ab15cb5d6fcbeae73e1552ca`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40209f` — `thunk_FUN_004626f8`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00420e94(short param_1,undefined2 param_2)

{
  undefined4 *in_ECX;
  
  thunk_FUN_004626f8((int)param_1,CONCAT22(*(short *)(in_ECX + 4) >> 0xf,param_2),*in_ECX,
                     (int)*(short *)(in_ECX + 4),(int)*(short *)((int)in_ECX + 0x12));
  return;
}
```

---

---

## FUN_00420ed9 — 0x420ed9

- Classification : internal
- Corps : `0x420ed9–0x420f27`
- État : pseudocode obtenu
- Evidence : `ev_9a09d268ef3fc99f0b46bf7cfab21e44e2381b01d4da10628389c335f5c1897f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00420ed9(short *param_1)

{
  undefined4 uVar1;
  int *in_ECX;
  
  if (((int)*param_1 < *(int *)(&DAT_005ec620 + *in_ECX * 8 + param_1[4] * 0x29e8)) ||
     (*(int *)((int)(&DAT_005ec620 + *in_ECX * 8 + param_1[4] * 0x29e8) + 4) < (int)*param_1)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}
```

---

---

## FUN_00420f28 — 0x420f28

- Classification : internal
- Corps : `0x420f28–0x4210a8`
- État : pseudocode obtenu
- Evidence : `ev_63ad84d3d0d141fdb043c3a8bc27b373108b9f2ce92bfb42ea0a29510a0bb3b9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018cf` — `thunk_FUN_0041ff2e`
- `0x401933` — `thunk_FUN_00464242`
- `0x401dac` — `thunk_FUN_004207f2`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
short FUN_00420f28(void)

{
  short sVar1;
  ushort uVar2;
  short sVar3;
  int iVar4;
  int *in_ECX;
  short local_8;
  
  if (*in_ECX == 4) {
    iVar4 = thunk_FUN_00464242(*in_ECX,in_ECX[1]);
    sVar1 = *(short *)(iVar4 + 6);
    sVar3 = thunk_FUN_0041ff2e();
    local_8 = (short)(((int)sVar1 * (sVar3 * 7 + 10)) / 10);
  }
  else {
    iVar4 = thunk_FUN_00464242(*in_ECX,in_ECX[1]);
    sVar1 = *(short *)(iVar4 + 6);
    sVar3 = thunk_FUN_0041ff2e();
    local_8 = (short)(((sVar3 + 2) * (int)sVar1) / 2);
    uVar2 = *(ushort *)(&DAT_00619242 + *in_ECX * 0x14a0);
    if (((uVar2 & 0x10) != 0) && (in_ECX[1] == 0)) {
      local_8 = local_8 + 1;
    }
    iVar4 = thunk_FUN_004207f2();
    if (iVar4 != 0) {
      iVar4 = thunk_FUN_0045c3bb();
      if (((uVar2 & 2) == 0) || (*(int *)(iVar4 + 0x10) != 0x2c)) {
        if (((uVar2 & 0x80) == 0) || (*(int *)(iVar4 + 0x10) != 0x2d)) {
          if (((uVar2 & 0x800) != 0) && (*(int *)(iVar4 + 0x10) == 0x2e)) {
            local_8 = (short)((int)((int)(short)(local_8 * 5) +
                                   ((int)(short)(local_8 * 5) >> 0x1f & 3U)) >> 2);
          }
        }
        else {
          local_8 = (short)((int)((int)(short)(local_8 * 5) +
                                 ((int)(short)(local_8 * 5) >> 0x1f & 3U)) >> 2);
        }
      }
      else {
        local_8 = (short)((int)((int)(short)(local_8 * 5) + ((int)(short)(local_8 * 5) >> 0x1f & 3U)
                               ) >> 2);
      }
    }
  }
  return local_8;
}
```

---

---

## FUN_004210a9 — 0x4210a9

- Classification : internal
- Corps : `0x4210a9–0x4211ba`
- État : pseudocode obtenu
- Evidence : `ev_dd046f002c50d0d9e841af455f3dd8fc8b70d1b11f430f2fa5c0185edc5f5121`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4016c7` — `thunk_FUN_00420ed9`
- `0x4016e0` — `thunk_FUN_00420635`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004210a9(int param_1)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int in_ECX;
  int local_18;
  int local_14;
  undefined *local_10;
  int local_c;
  
  if ((param_1 == -1) || (*(short *)(in_ECX + 0xe) == param_1)) {
    uVar2 = 1;
  }
  else {
    sVar1 = *(short *)(in_ECX + 0xe);
    local_18 = -1;
    local_c = 6000;
    local_10 = &DAT_005ec640 + sVar1 * 0x29e8;
    for (local_14 = 0; local_14 < (short)(&DAT_005eebc0)[sVar1 * 0x14f4]; local_14 = local_14 + 1) {
      if ((*(int *)(local_10 + 4) == 2) && ((*(uint *)(local_10 + 0x1c) & 1) != 0)) {
        iVar3 = thunk_FUN_00420ed9(local_10);
        if (iVar3 != 0) {
          if (*(short *)(local_10 + 0x36) == param_1) {
            local_18 = local_14;
            break;
          }
          iVar3 = thunk_FUN_00420635(local_10);
          if (iVar3 < local_c) {
            local_18 = local_14;
            local_c = iVar3;
          }
        }
      }
      local_10 = local_10 + 0x60;
    }
    if (local_18 == -1) {
      uVar2 = 0;
    }
    else {
      *(undefined4 *)(in_ECX + 0x2c) = 0x11;
      *(undefined2 *)(in_ECX + 0x32) = (undefined2)local_18;
      *(undefined2 *)(in_ECX + 0x30) = (undefined2)param_1;
      uVar2 = 1;
    }
  }
  return uVar2;
}
```

---

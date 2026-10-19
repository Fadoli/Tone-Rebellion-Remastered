# 0010_batch_0006 — détails (6/8)

## FUN_00420217 — 0x420217

- Classification : internal
- Corps : `0x420217–0x4204a7`
- État : pseudocode obtenu
- Evidence : `ev_81c67f0c489b8994b0566412ba29d32d2b1fceaccd6896d7874a57229b0ad6a8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010d7` — `thunk_FUN_0042003c`
- `0x4011ea` — `thunk_FUN_0041fde6`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x401d16` — `thunk_FUN_004204bc`
- `0x472c6c` — `__ftol`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00420217(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *in_ECX;
  int local_3c;
  int local_24;
  int local_20;
  
  if (((*in_ECX == -1) || ((in_ECX[7] & 8U) != 0)) || ((in_ECX[7] & 0x100U) != 0)) {
    local_20 = 0;
  }
  else {
    local_20 = 0;
    thunk_FUN_0042003c(in_ECX[1]);
    thunk_FUN_0041fde6();
    local_24 = DAT_004bf11c;
    if (DAT_004bf11c < 0) {
      local_24 = 0;
    }
    if (4 < local_24) {
      local_24 = 4;
    }
    switch(local_24) {
    case 0:
      break;
    case 1:
    case 2:
      break;
    default:
    }
    iVar1 = __ftol();
    iVar2 = thunk_FUN_00467260(100);
    if (iVar2 < iVar1 + 10) {
      local_3c = param_1 + -1;
      if (local_3c < 1) {
        local_3c = 1;
      }
      iVar1 = thunk_FUN_00467260(local_3c);
      iVar2 = thunk_FUN_00467260(local_3c);
      iVar3 = thunk_FUN_00467260(local_3c);
      iVar1 = (iVar1 + iVar2 + 3 + iVar3) / 3;
      local_20 = iVar1;
      if (10 < iVar1) {
        local_20 = 10;
      }
      thunk_FUN_004204bc(CONCAT22((short)((uint)iVar1 >> 0x10),(undefined2)local_20),param_3);
    }
  }
  return local_20;
}
```

---

## FUN_004204bc — 0x4204bc

- Classification : internal
- Corps : `0x4204bc–0x4205ff`
- État : pseudocode obtenu
- Evidence : `ev_c5d4a5104a2028ab42739db13819a1061617290fb0656b911b575d99de0cc674`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013c0` — `thunk_FUN_004655b2`
- `0x401adc` — `thunk_FUN_00416a9a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004204bc(short param_1,int param_2)

{
  int *in_ECX;
  undefined4 local_c;
  int local_8;
  
  if (((in_ECX[7] & 8U) == 0) &&
     (*(short *)(in_ECX + 8) = (short)in_ECX[8] - param_1, (short)in_ECX[8] < 1)) {
    in_ECX[7] = in_ECX[7] | 8;
    in_ECX[9] = 0;
    thunk_FUN_00416a9a(1,in_ECX);
    local_c = 1;
    local_8 = (int)(in_ECX + -0x184dee) / 0x4c;
    thunk_FUN_004655b2(&local_c);
    if ((-1 < param_2) && (param_2 < 4)) {
      if (*in_ECX == 4) {
        *(short *)(&DAT_0061a624 + in_ECX[1] * 2 + param_2 * 0x14a0) =
             *(short *)(&DAT_0061a624 + in_ECX[1] * 2 + param_2 * 0x14a0) + 1;
      }
      else {
        *(short *)(&DAT_0061a648 + *in_ECX * 2 + param_2 * 0x14a0) =
             *(short *)(&DAT_0061a648 + *in_ECX * 2 + param_2 * 0x14a0) + 1;
      }
    }
    if ((-1 < *in_ECX) && (*in_ECX < 4)) {
      *(short *)(&DAT_0061a650 + *in_ECX * 0x14a0) =
           *(short *)(&DAT_0061a650 + *in_ECX * 0x14a0) + 1;
    }
  }
  return;
}
```

---

## FUN_00420600 — 0x420600

- Classification : internal
- Corps : `0x420600–0x420634`
- État : pseudocode obtenu
- Evidence : `ev_85bc423ec5ecdbce06de718adc4fd60bce26aa8f7d568b367b9d8e52caac3298`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40173a` — `thunk_FUN_004672a6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00420600(int param_1)

{
  int in_ECX;
  
  thunk_FUN_004672a6((int)*(short *)(in_ECX + 0x10),(int)*(short *)(in_ECX + 0x12),
                     (int)*(short *)(param_1 + 0x10),(int)*(short *)(param_1 + 0x12));
  return;
}
```

---

## FUN_00420635 — 0x420635

- Classification : internal
- Corps : `0x420635–0x420668`
- État : pseudocode obtenu
- Evidence : `ev_f359bbf9ea4d68be9d7184310b58199071b1e8115a49a149ab72415feb7659db`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40173a` — `thunk_FUN_004672a6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00420635(short *param_1)

{
  int in_ECX;
  
  thunk_FUN_004672a6((int)*(short *)(in_ECX + 0x10),(int)*(short *)(in_ECX + 0x12),(int)*param_1,
                     (int)param_1[1]);
  return;
}
```

---

## FUN_00420669 — 0x420669

- Classification : internal
- Corps : `0x420669–0x4206b1`
- État : pseudocode obtenu
- Evidence : `ev_b7b0099d6f0f4e998eff7774dac933f017be7b8919cf6bcc70057fa6fb3c0474`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40140b` — `thunk_FUN_00416e7d`
- `0x40225c` — `thunk_FUN_00421ec1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00420669(int param_1)

{
  int in_ECX;
  
  if (*(int *)(in_ECX + 0x38) == param_1) {
    if (*(short *)(in_ECX + 0x48) != -1) {
      thunk_FUN_00416e7d(*(undefined2 *)(in_ECX + 0x48));
      *(undefined2 *)(in_ECX + 0x48) = 0xffff;
    }
    thunk_FUN_00421ec1(0xffffffff);
  }
  return;
}
```

---

## FUN_004206b2 — 0x4206b2

- Classification : internal
- Corps : `0x4206b2–0x4206fb`
- État : pseudocode obtenu
- Evidence : `ev_0fa2d1314dadc2b6f43acd0876a73cd309d50445ccfedf7e8bafb07cb057e8fc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4020b3` — `thunk_FUN_00466533`
- `0x40225c` — `thunk_FUN_00421ec1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004206b2(int param_1)

{
  int in_ECX;
  
  if ((*(short *)(in_ECX + 0x32) == param_1) && ((*(uint *)(in_ECX + 0x1c) & 4) != 0)) {
    if (*(int *)(in_ECX + 0x38) != -1) {
      thunk_FUN_00466533(*(undefined4 *)(in_ECX + 0x38));
    }
    thunk_FUN_00421ec1(0xffffffff);
  }
  return;
}
```

---

## FUN_004206fc — 0x4206fc

- Classification : internal
- Corps : `0x4206fc–0x420720`
- État : pseudocode obtenu
- Evidence : `ev_d65a12f5117769a72a31e2a4af19ea210118c464a80d28b268c1820afe5c2eee`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004206fc(short param_1)

{
  int in_ECX;
  
  if (*(short *)(in_ECX + 0x48) == param_1) {
    *(undefined2 *)(in_ECX + 0x48) = 0xffff;
  }
  return;
}
```

---

## FUN_00420721 — 0x420721

- Classification : internal
- Corps : `0x420721–0x4207c1`
- État : pseudocode obtenu
- Evidence : `ev_234f0678b3bbd27430c793e465dfd5095240536d821d1821e23bb5b1acb00e41`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401933` — `thunk_FUN_00464242`
- `0x401dac` — `thunk_FUN_004207f2`
- `0x4023bf` — `thunk_FUN_0045c3bb`
- `0x4024be` — `thunk_FUN_004207c2`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
short FUN_00420721(void)

{
  int iVar1;
  short *psVar2;
  int *in_ECX;
  short local_8;
  
  local_8 = 0;
  iVar1 = thunk_FUN_004207c2();
  if (iVar1 == 0) {
    psVar2 = (short *)thunk_FUN_00464242(*in_ECX,in_ECX[1]);
    local_8 = *psVar2;
    iVar1 = thunk_FUN_004207f2();
    if (iVar1 != 0) {
      thunk_FUN_0045c3bb();
      if (((*(ushort *)(&DAT_00619242 + *in_ECX * 0x14a0) & 4) != 0) && (0 < local_8)) {
        local_8 = (short)((int)((int)(short)(local_8 * 5) + ((int)(short)(local_8 * 5) >> 0x1f & 3U)
                               ) >> 2);
      }
    }
  }
  return local_8;
}
```

---

## FUN_004207c2 — 0x4207c2

- Classification : internal
- Corps : `0x4207c2–0x4207f1`
- État : pseudocode obtenu
- Evidence : `ev_601b55f72156209d4f5c1ae6f9060918a71e3fc3423c72c12074227bdb69a5c6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004207c2(void)

{
  undefined4 uVar1;
  int *in_ECX;
  
  if ((*in_ECX == 4) || ((in_ECX[1] != 0 && (0 < *(short *)((int)in_ECX + 0x22))))) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}
```

---

## FUN_004207f2 — 0x4207f2

- Classification : internal
- Corps : `0x4207f2–0x420828`
- État : pseudocode obtenu
- Evidence : `ev_400be7fc416e3e48c58ebeae7f1497639f909f0569891b58d5b3cba579bbab2a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_004207f2(void)

{
  undefined *puVar1;
  int *in_ECX;
  
  if ((short)in_ECX[3] == -1) {
    puVar1 = (undefined *)0x0;
  }
  else {
    puVar1 = &DAT_006192b0 + (short)in_ECX[3] * 100 + *in_ECX * 0x14a0;
  }
  return puVar1;
}
```

---

## FUN_00420829 — 0x420829

- Classification : internal
- Corps : `0x420829–0x4208ea`
- État : pseudocode obtenu
- Evidence : `ev_92d9bb1718fe3eeebfe376dbac88ead112d0c4f1f89113bc3a4cc866df7dbf24`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401401` — `thunk_FUN_0041e427`
- `0x40173a` — `thunk_FUN_004672a6`
- `0x40186b` — `thunk_FUN_004656d6`
- `0x401d39` — `thunk_FUN_00420991`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined2 FUN_00420829(undefined2 param_1)

{
  int iVar1;
  int iVar2;
  int in_ECX;
  int iVar3;
  int local_14;
  short local_c [2];
  short local_8 [2];
  
  thunk_FUN_0041e427(param_1,local_8,local_c);
  iVar1 = thunk_FUN_004656d6((int)*(short *)(in_ECX + 0xe),0xfffffffe);
  local_14 = 0;
  while( true ) {
    if (iVar1 <= local_14) {
      return 0xffff;
    }
    iVar3 = (short)(&DAT_00618fb4)[local_14] * 0x4c;
    iVar2 = thunk_FUN_00420991(&DAT_006137b8 + (short)(&DAT_00618fb4)[local_14] * 0x13);
    if ((iVar2 != 0) &&
       (iVar2 = thunk_FUN_004672a6((int)*(short *)(&DAT_006137c8 + iVar3),
                                   (int)*(short *)(&DAT_006137ca + iVar3),(int)local_8[0],
                                   (int)local_c[0]), iVar2 < 0xfa)) break;
    local_14 = local_14 + 1;
  }
  return (&DAT_00618fb4)[local_14];
}
```

---

## FUN_004208eb — 0x4208eb

- Classification : internal
- Corps : `0x4208eb–0x420990`
- État : pseudocode obtenu
- Evidence : `ev_45e476a70f900a1cdcdfaa0a6d82ee5f2025db59a6f6005a7451f7eb7ef707e2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40180c` — `thunk_FUN_00420600`
- `0x40186b` — `thunk_FUN_004656d6`
- `0x401d39` — `thunk_FUN_00420991`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined2 FUN_004208eb(short param_1)

{
  int iVar1;
  int iVar2;
  int in_ECX;
  int local_10;
  
  iVar1 = thunk_FUN_004656d6((int)*(short *)(in_ECX + 0xe),0xfffffffe);
  local_10 = 0;
  while( true ) {
    if (iVar1 <= local_10) {
      return 0xffff;
    }
    iVar2 = thunk_FUN_00420991(&DAT_006137b8 + (short)(&DAT_00618fb4)[local_10] * 0x13);
    if ((iVar2 != 0) && (iVar2 = thunk_FUN_00420600(&DAT_006137b8 + param_1 * 0x13), iVar2 < 0xfa))
    break;
    local_10 = local_10 + 1;
  }
  return (&DAT_00618fb4)[local_10];
}
```

---

## FUN_00420991 — 0x420991

- Classification : internal
- Corps : `0x420991–0x420a54`
- État : pseudocode obtenu
- Evidence : `ev_2b7c3a4d07a47624e5bda9eda2a57d60b965635fa529ab925962c1b77d88b010`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_00420991(int *param_1)

{
  int *in_ECX;
  bool bVar1;
  
  bVar1 = false;
  if ((param_1 != in_ECX) && ((param_1[7] & 0x809U) == 0)) {
    if (*in_ECX == 4) {
      if (((*(short *)((int)in_ECX + 0xe) < 0) || (0xe < *(short *)((int)in_ECX + 0xe))) ||
         (*(short *)(&DAT_0061fa2e + *(short *)((int)in_ECX + 0xe) * 2) < 0x65)) {
        bVar1 = *param_1 != 4;
      }
      else {
        bVar1 = *param_1 == 4;
      }
    }
    else if ((*param_1 == 4) || (*(int *)(&DAT_00619290 + *param_1 * 4 + *in_ECX * 0x14a0) == 0)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  return bVar1;
}
```

---

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


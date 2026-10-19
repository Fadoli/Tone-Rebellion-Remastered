# 0010_batch_0006 — détails (1/2)

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

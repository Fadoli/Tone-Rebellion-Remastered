# 0013_batch_0009 — détails (1/5)

## FUN_00439fbd — 0x439fbd

- Classification : internal
- Corps : `0x439fbd–0x439fde`
- État : pseudocode obtenu
- Evidence : `ev_b546f1b6cbdd4a1950dd08f85d93b62b5bde036b0ca554444f295c05e7fd4abb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00439fbd(undefined2 param_1,undefined4 param_2,undefined4 param_3)

{
  thunk_FUN_004293c6(param_1,param_2,param_3);
  return;
}
```

---

## FUN_00439fdf — 0x439fdf

- Classification : internal
- Corps : `0x439fdf–0x43a10d`
- État : pseudocode obtenu
- Evidence : `ev_14aea1c7d10fea00bc9988f18a516b9ce647d415945e0355a4abd7bd468f342d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40146f` — `thunk_FUN_0042d87c`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x40203b` — `thunk_FUN_0042a00b`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- `0x49fde8` — "mainbutt"
- `0x49fdf4` — "shape"
- `0x49fdfc` — "C:\\float\\src\\islewin2.cpp"

### Pseudocode Ghidra

```c
void FUN_00439fdf(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int in_ECX;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    uVar1 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar1;
    if (*(int *)(&DAT_005eebd4 + DAT_0049f538 * 4 + DAT_0049f53c * 0x29e8) == 0) {
      *(undefined2 *)(in_ECX + 0x70) = 8;
      *(undefined2 *)(in_ECX + 0x72) = 1;
      thunk_FUN_0042a00b(param_1);
      *(undefined4 *)(in_ECX + 0x34) = 1;
    }
    else {
      iVar2 = thunk_FUN_0040ec89(s_mainbutt_0049fde8,1);
      if (iVar2 == 0) {
        uVar1 = thunk_FUN_00414b64(s_C__float_src_islewin2_cpp_0049fdfc,0x43b,s_shape_0049fdf4);
      }
      else {
        uVar1 = 0;
      }
      thunk_FUN_00404770(in_ECX + 8,iVar2,(int)*(short *)(in_ECX + 0x70),0,0,uVar1);
      *(short *)(in_ECX + 0x70) = *(short *)(in_ECX + 0x70) + *(short *)(in_ECX + 0x72);
      if (*(short *)(in_ECX + 0x70) == 0xd) {
        *(undefined2 *)(in_ECX + 0x72) = 0xffff;
      }
      else if (*(short *)(in_ECX + 0x70) == 8) {
        *(undefined2 *)(in_ECX + 0x72) = 1;
      }
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,1);
  }
  return;
}
```

---

## FUN_0043a910 — 0x43a910

- Classification : internal
- Corps : `0x43a910–0x43a93d`
- État : pseudocode obtenu
- Evidence : `ev_93ec525904d06a9c2691e6cfa141e9dda01bea0537c243f10ec474581b2c85f7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4023e7` — `thunk_FUN_00438298`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043a910(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00438298();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0043a950 — 0x43a950

- Classification : internal
- Corps : `0x43a950–0x43a97d`
- État : pseudocode obtenu
- Evidence : `ev_8da6ad6bf4d69c0ab470dc1d489709383420af2e05e04974e3bfe5839202c4ad`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401ca8` — `thunk_FUN_00438abc`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043a950(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00438abc();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0043a990 — 0x43a990

- Classification : internal
- Corps : `0x43a990–0x43a9bd`
- État : pseudocode obtenu
- Evidence : `ev_473265cb3dea7190d224a3cf403a4bc6a09d997b1f5ec7c0c7c1110d3eadcffd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402464` — `thunk_FUN_0043910c`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043a990(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0043910c();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0043a9d0 — 0x43a9d0

- Classification : internal
- Corps : `0x43a9d0–0x43a9fd`
- État : pseudocode obtenu
- Evidence : `ev_4049f9ccc431eb61a8d7633c1ce0cefb9a3da53e99a56b57ad8bfcbc1183a477`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401df7` — `thunk_FUN_004395d7`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043a9d0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_004395d7();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0043aa10 — 0x43aa10

- Classification : internal
- Corps : `0x43aa10–0x43aa3d`
- État : pseudocode obtenu
- Evidence : `ev_4114e0adb781d1ab908a544aa756b3c7efc00d0ea7c989b24926528286336a0b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401e33` — `thunk_FUN_00439f84`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043aa10(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00439f84();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0043aa50 — 0x43aa50

- Classification : internal
- Corps : `0x43aa50–0x43aa77`
- État : pseudocode obtenu
- Evidence : `ev_0d75b96bcb6c1b82c4809165f745c81c5ad13f8f29e2e58f2bb25ad876e9b5b8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0043aa50(void)

{
  undefined4 *in_ECX;
  
  thunk_FUN_00429243();
  *in_ECX = &PTR_LAB_00494380;
  *(undefined2 *)((int)in_ECX + 0x72) = 0;
  return in_ECX;
}
```

---

## FUN_0043aa78 — 0x43aa78

- Classification : internal
- Corps : `0x43aa78–0x43aa93`
- État : pseudocode obtenu
- Evidence : `ev_b2230c2b2358473ee9ec092a2e274ca98e2ba3f8e13020a05919ac9fe9083805`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043aa78(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494380;
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_0043aa94 — 0x43aa94

- Classification : internal
- Corps : `0x43aa94–0x43aa9e`
- État : pseudocode obtenu
- Evidence : `ev_e73b9a5a318818ae99407c073fce68619e925a669ea95dd2b888374bd8c2a5f7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043aa94(void)

{
  return;
}
```

---

## FUN_0043aa9f — 0x43aa9f

- Classification : internal
- Corps : `0x43aa9f–0x43ac8c`
- État : pseudocode obtenu
- Evidence : `ev_6911df5e5607f9963149a4f1d5f880269f5e522dd039c54f3b9294f261283f52`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013f7` — `thunk_FUN_0046c402`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401645` — `thunk_FUN_0043acea`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401cb2` — `thunk_FUN_0045f121`
- `0x401ce4` — `thunk_FUN_0043ad79`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49fea0` — "pIWWin"
- `0x49fea8` — "C:\\float\\src\\Iwconstr.cpp"
- `0x49fec4` — "BuildCycle"
- `0x49fed0` — "BuildCycle"

### Pseudocode Ghidra

```c
undefined4 FUN_0043aa9f(short param_1,int param_2,int param_3)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined2 extraout_var;
  
  switch((int)param_1) {
  case 1:
    *(undefined2 *)(in_ECX + 0x74) = 0;
    *(undefined2 *)(in_ECX + 0x72) = 0;
    *(undefined2 *)(in_ECX + 0x76) = 0xffff;
    if (DAT_005dc64c == 0) {
      thunk_FUN_00414b64(s_C__float_src_Iwconstr_cpp_0049fea8,0x59,s_pIWWin_0049fea0);
    }
    if (*(int *)(DAT_005dc64c + 0x16c) != 0) {
      uVar1 = thunk_FUN_0045f121(*(int *)(DAT_005dc64c + 0x16c));
      *(undefined2 *)(in_ECX + 0x74) = uVar1;
      if (4 < *(short *)(in_ECX + 0x74)) {
        thunk_FUN_0046c3bc(s_BuildCycle_0049fec4,1,0,0);
      }
    }
    uVar2 = thunk_FUN_004293c6(param_1,param_2,param_3);
    return uVar2;
  case 2:
    thunk_FUN_0046c3bc(s_BuildCycle_0049fed0,2,0,0);
    uVar2 = thunk_FUN_004293c6(CONCAT22(extraout_var,param_1),param_2,param_3);
    return uVar2;
  default:
    uVar2 = thunk_FUN_004293c6(CONCAT22((short)((uint)(param_1 + -1) >> 0x10),param_1),param_2,
                               param_3);
    return uVar2;
  case 6:
    if ((((*(int *)(in_ECX + 0xc) <= param_2) && (param_2 <= *(int *)(in_ECX + 0x14))) &&
        (*(int *)(in_ECX + 0x10) <= param_3)) &&
       ((param_3 <= *(int *)(in_ECX + 0x18) && (*(int *)(in_ECX + 0x38) != 0)))) {
      thunk_FUN_0043acea(param_2,param_3);
    }
    break;
  case 10:
    thunk_FUN_0043ad79(param_2,param_3);
    break;
  case 0x45:
    *(short *)(in_ECX + 0x72) = *(short *)(in_ECX + 0x72) + 1;
    if ((int)*(short *)(in_ECX + 0x74) <= *(short *)(in_ECX + 0x72) * 4) {
      *(undefined2 *)(in_ECX + 0x72) = 0;
    }
    *(undefined2 *)(in_ECX + 0x76) = 0xffff;
    *(undefined4 *)(in_ECX + 0x34) = 1;
    thunk_FUN_0046c402(0x3c,0xfffffffe,0);
  }
  return 0;
}
```

---

## FUN_0043acea — 0x43acea

- Classification : internal
- Corps : `0x43acea–0x43ad78`
- État : pseudocode obtenu
- Evidence : `ev_df54e8be59f9e45675cb4c41fc2e435a490a7b0cca320ff92fc7a3a4bf1c4aa7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013f7` — `thunk_FUN_0046c402`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49fedc` — "item>=(int)PIT_BuildToneProducer"
- `0x49ff00` — "C:\\float\\src\\Iwconstr.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0043acea(void)

{
  undefined4 uVar1;
  int in_ECX;
  int local_8;
  
  if (*(short *)(in_ECX + 0x70) < 0) {
    uVar1 = 0;
  }
  else {
    local_8 = (int)*(short *)(in_ECX + 0x70);
    if (0x34 < local_8) {
      local_8 = local_8 + DAT_0049f538 * -0x10;
    }
    if (local_8 < 0x25) {
      thunk_FUN_00414b64(s_C__float_src_Iwconstr_cpp_0049ff00,0x9a,
                         s_item>__int_PIT_BuildToneProducer_0049fedc);
    }
    thunk_FUN_0046c402(0x34,local_8,0);
    thunk_FUN_0046c402(0x33,0,0);
    uVar1 = 1;
  }
  return uVar1;
}
```

---

## FUN_0043ad79 — 0x43ad79

- Classification : internal
- Corps : `0x43ad79–0x43aee7`
- État : pseudocode obtenu
- Evidence : `ev_d8631383039a32358c65c9bc1a4848f8d090e8bc6fa25e6bc06fdddb635e056b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013f7` — `thunk_FUN_0046c402`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043ad79(int param_1,int param_2)

{
  int in_ECX;
  int iVar1;
  undefined2 local_14;
  int local_10;
  int local_8;
  
  local_8 = -1;
  if ((((*(int *)(in_ECX + 0xc) <= param_1) && (param_1 <= *(int *)(in_ECX + 0x14))) &&
      (*(int *)(in_ECX + 0x10) + 0x1a <= param_2)) && (param_2 <= *(int *)(in_ECX + 0x18) + -10)) {
    iVar1 = *(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc);
    local_8 = (param_1 - *(int *)(in_ECX + 0xc)) / ((int)(iVar1 + (iVar1 >> 0x1f & 3U)) >> 2);
  }
  if (local_8 != *(short *)(in_ECX + 0x76)) {
    *(undefined2 *)(in_ECX + 0x76) = (undefined2)local_8;
    *(undefined4 *)(in_ECX + 0x34) = 1;
    local_10 = -1;
    if ((-1 < *(short *)(in_ECX + 0x76)) && (*(short *)(in_ECX + 0x76) < 4)) {
      local_10 = (int)*(short *)(in_ECX + 0x76) + *(short *)(in_ECX + 0x72) * 4;
    }
    if (*(short *)(in_ECX + 0x74) <= local_10) {
      local_10 = -1;
    }
    if ((local_10 < 0) || ((int)(uint)*(ushort *)(DAT_0049f538 * 0x14a0 + 0x61928c) <= local_10)) {
      if (-1 < *(short *)(in_ECX + 0x70)) {
        *(undefined2 *)(in_ECX + 0x70) = 0xffff;
        thunk_FUN_0046c402(0x3c,0xfffffffe,0);
      }
    }
    else {
      iVar1 = *(int *)(DAT_0049f538 * 0x14a0 + 0x61924c + local_10 * 4);
      if (*(short *)(in_ECX + 0x70) != iVar1) {
        local_14 = (undefined2)iVar1;
        *(undefined2 *)(in_ECX + 0x70) = local_14;
        thunk_FUN_0046c402(0x3c,iVar1,0);
      }
    }
  }
  return 0;
}
```

---

## FUN_0043aee8 — 0x43aee8

- Classification : internal
- Corps : `0x43aee8–0x43b231`
- État : pseudocode obtenu
- Evidence : `ev_468d444232620fa2d405a489c4af1fe908970562f91bfd4112903f94ea7af30e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401410` — `thunk_FUN_0040d3e1`
- `0x401442` — `thunk_FUN_0041169f`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x4019ec` — `thunk_FUN_00405265`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401cb2` — `thunk_FUN_0045f121`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x4021ad` — `thunk_FUN_004641de`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`

### Chaînes référencées

- `0x49ff1c` — "starti<numitems"
- `0x49ff2c` — "C:\\float\\src\\Iwconstr.cpp"
- `0x49ff48` — "bildtone"
- `0x49ff54` — "shape"
- `0x49ff5c` — "C:\\float\\src\\Iwconstr.cpp"
- `0x49ff78` — "BuildCycle"

### Pseudocode Ghidra

```c
void FUN_0043aee8(void)

{
  short sVar1;
  short sVar2;
  undefined1 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int in_ECX;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int local_2c;
  int local_14;
  int local_10;
  int local_8;
  
  if ((((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) && (DAT_005dc64c != 0)) &&
     ((*(int *)(DAT_005dc64c + 0x16c) != 0 &&
      (iVar6 = *(int *)(DAT_005dc64c + 0x16c), *(int *)(iVar6 + 4) == 0)))) {
    uVar4 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar4;
    if (DAT_004c2bac == 0) {
      thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
    }
    else {
      uVar10 = 0;
      uVar9 = 0;
      iVar5 = (int)*(short *)(in_ECX + 0x1e);
      uVar4 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar4,iVar5,uVar9,uVar10);
    }
    iVar5 = *(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc);
    iVar5 = iVar5 + (iVar5 >> 0x1f & 3U);
    local_10 = (iVar5 >> 2) - (iVar5 >> 0x1f) >> 1;
    iVar5 = *(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10);
    iVar8 = DAT_0049f538 * 0x14a0;
    iVar6 = thunk_FUN_0045f121(iVar6);
    sVar1 = *(short *)(in_ECX + 0x72);
    local_14 = sVar1 * 4;
    if (iVar6 <= local_14) {
      thunk_FUN_00414b64(s_C__float_src_Iwconstr_cpp_0049ff2c,0xef,s_starti<numitems_0049ff1c);
    }
    local_8 = local_14 + 4;
    if (iVar6 < local_14 + 4) {
      local_8 = iVar6;
    }
    for (; local_14 < local_8; local_14 = local_14 + 1) {
      if (local_14 + sVar1 * -4 == (int)*(short *)(in_ECX + 0x76)) {
        uVar3 = thunk_FUN_0042dd0f(1,0,0xffffffff);
        iVar6 = *(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc);
        iVar6 = iVar6 + (iVar6 >> 0x1f & 3U);
        iVar7 = *(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc);
        iVar7 = iVar7 + (iVar7 >> 0x1f & 3U);
        thunk_FUN_0041169f(in_ECX + 8,(local_10 - ((iVar7 >> 2) - (iVar7 >> 0x1f) >> 1)) + 5,0x1a,
                           local_10 + -5 + ((iVar6 >> 2) - (iVar6 >> 0x1f) >> 1),
                           (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + -10,uVar3);
      }
      iVar6 = thunk_FUN_004641de(DAT_0049f538,*(undefined4 *)(iVar8 + 0x61924c + local_14 * 4));
      sVar2 = *(short *)(iVar6 + 4);
      if (-1 < sVar2) {
        thunk_FUN_0040d3e1(in_ECX + 8,DAT_0049f538,*(undefined4 *)(iVar8 + 0x61924c + local_14 * 4),
                           local_10,iVar5 + -0x23,0x8000);
        local_2c = sVar2 + -1;
        if (0x31 < local_2c) {
          local_2c = 0x31;
        }
        iVar6 = thunk_FUN_0040ec89(s_bildtone_0049ff48,1);
        if (iVar6 == 0) {
          uVar4 = thunk_FUN_00414b64(s_C__float_src_Iwconstr_cpp_0049ff5c,0x10e,s_shape_0049ff54);
        }
        else {
          uVar4 = 0;
        }
        thunk_FUN_00405265(in_ECX + 8,iVar6,local_2c,local_10,iVar5 + -0xf,&DAT_004b28f0,0,0x8000,
                           0x8000,0,uVar4);
        iVar6 = *(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc);
        local_10 = local_10 + ((int)(iVar6 + (iVar6 >> 0x1f & 3U)) >> 2);
      }
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,3);
    *(undefined4 *)(in_ECX + 0x34) = 0;
    if (4 < *(short *)(in_ECX + 0x74)) {
      thunk_FUN_0046c3bc(s_BuildCycle_0049ff78,0xb,0,0);
    }
  }
  return;
}
```

---

## FUN_0043b232 — 0x43b232

- Classification : internal
- Corps : `0x43b232–0x43b23e`
- État : pseudocode obtenu
- Evidence : `ev_f310e0557f94d2e629cb2c81ed36adbf3da6522eb1484abdd7e4f283c743b2ea`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043b232(void)

{
  return;
}
```

---

## FUN_0043b23f — 0x43b23f

- Classification : internal
- Corps : `0x43b23f–0x43b24b`
- État : pseudocode obtenu
- Evidence : `ev_ee749647ec227b12ec19f7c092cb12eadfdcbe3b3acffb33200f7f2a5b9a4253`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043b23f(void)

{
  return;
}
```

---

## FUN_0043b24c — 0x43b24c

- Classification : internal
- Corps : `0x43b24c–0x43b29f`
- État : pseudocode obtenu
- Evidence : `ev_959f984e12a2f20e76069c141b827c48f5cac7a2e352dc65853c5ff00fb96cdd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`
- `0x40217b` — `thunk_FUN_0043b2bc`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0043b24c(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491769;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494398;
  thunk_FUN_0043b2bc();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_0043b2a0 — 0x43b2a0

- Classification : internal
- Corps : `0x43b2a0–0x43b2bb`
- État : pseudocode obtenu
- Evidence : `ev_9a4cb3a9e18f2f876e1a8666443def6d3b45bc90474149e166d96d8f9d52579a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043b2a0(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494398;
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_0043b2bc — 0x43b2bc

- Classification : internal
- Corps : `0x43b2bc–0x43b2d0`
- État : pseudocode obtenu
- Evidence : `ev_4e02c868590c7d64e2efd35b60b06987d240c7ad146ebde326243abd87d8e51c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043b2bc(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x70) = 0xffffffff;
  return;
}
```

---

## FUN_0043b2d1 — 0x43b2d1

- Classification : internal
- Corps : `0x43b2d1–0x43b332`
- État : pseudocode obtenu
- Evidence : `ev_9a8b46e251e108cdbd84177b8fd432ad065e222919fa3eeaa4e40d87fb15aa7f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043b2d1(short param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int in_ECX;
  
  if (param_1 == 1) {
    *(undefined4 *)(in_ECX + 0x70) = 0xffffffff;
  }
  else if (param_1 == 0x9a4) {
    *(undefined4 *)(in_ECX + 0x70) = param_2;
    *(undefined4 *)(in_ECX + 0x34) = 1;
    return 1;
  }
  uVar1 = thunk_FUN_004293c6(param_1,param_2,param_3);
  return uVar1;
}
```

---

## FUN_0043b333 — 0x43b333

- Classification : internal
- Corps : `0x43b333–0x43b368`
- État : pseudocode obtenu
- Evidence : `ev_f9380fef749f2c11e622232221f39c93e02bf0cef614fe0dec2ab1e2eb1d7788`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x401712` — `thunk_FUN_004289a7`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043b333(undefined4 param_1,int param_2,undefined4 *param_3,int *param_4,
                 undefined4 *param_5)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = thunk_FUN_0042de0d();
  iVar2 = thunk_FUN_004289a7(uVar1);
  *param_4 = param_2 + 1 + iVar2;
  *param_3 = 6;
  *param_5 = 0xad;
  return;
}
```

---

## FUN_0043b369 — 0x43b369

- Classification : internal
- Corps : `0x43b369–0x43b5b0`
- État : pseudocode obtenu
- Evidence : `ev_c771cda1ee2765b9539df839ec4bf6ad3f68c540a0daa9aa41c293e8f4e0a000`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401410` — `thunk_FUN_0040d3e1`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x4021ad` — `thunk_FUN_004641de`
- `0x4022fc` — `thunk_FUN_00428baa`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49ff8c` — "C:\\float\\src\\Iwconstr.cpp"
- `0x49ffa8` — "bildtone"
- `0x49ffb4` — "shape"
- `0x49ffbc` — "C:\\float\\src\\Iwconstr.cpp"

### Pseudocode Ghidra

```c
void FUN_0043b369(void)

{
  undefined4 uVar1;
  undefined2 extraout_var;
  int in_ECX;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int local_28;
  undefined1 local_24 [12];
  int local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((*(int *)(in_ECX + 0x3c) != 0) && (*(int *)(in_ECX + 0x34) != 0)) {
    uVar1 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar1;
    if (DAT_004c2bac == 0) {
      thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
    }
    else {
      uVar4 = 0;
      uVar3 = 0;
      iVar2 = (int)*(short *)(in_ECX + 0x1e);
      uVar1 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar1,iVar2,uVar3,uVar4);
      uVar5 = 0x44;
      uVar4 = 0;
      uVar3 = 7;
      uVar1 = thunk_FUN_0040e864(CONCAT22(extraout_var,*(undefined2 *)(in_ECX + 0x1c)));
      thunk_FUN_00404770(in_ECX + 8,uVar1,uVar3,uVar4,uVar5);
    }
    if (-1 < *(int *)(in_ECX + 0x70)) {
      local_8 = *(undefined4 *)(in_ECX + 0x70);
      local_c = DAT_0049f538;
      thunk_FUN_0040d3e1(in_ECX + 8,DAT_0049f538,local_8,
                         (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) + -0x37,0x55,0x10000);
      iVar2 = thunk_FUN_004641de(local_c,local_8,0);
      local_18 = thunk_FUN_00429ebe(iVar2 + 0x18);
      local_14 = thunk_FUN_0042de0d();
      if (local_14 == 0) {
        uVar1 = thunk_FUN_00414b64(s_C__float_src_Iwconstr_cpp_0049ff8c,0x17e,&DAT_0049ff84);
      }
      else {
        uVar1 = 0;
      }
      iVar2 = thunk_FUN_004641de(local_c,local_8);
      local_10 = (int)*(short *)(iVar2 + 4);
      if (-1 < local_10) {
        local_28 = local_10 + -1;
        if (0x31 < local_28) {
          local_28 = 0x31;
        }
        iVar2 = thunk_FUN_0040ec89(s_bildtone_0049ffa8,1);
        if (iVar2 == 0) {
          uVar3 = thunk_FUN_00414b64(s_C__float_src_Iwconstr_cpp_0049ffbc,0x186,s_shape_0049ffb4);
        }
        else {
          uVar3 = 0;
        }
        thunk_FUN_00404770(in_ECX + 8,iVar2,local_28,0x2d,0x4b,uVar3,uVar1);
        FUN_00472ca0(local_24,&DAT_0049ffd8,local_10);
        thunk_FUN_004289c0(in_ECX + 8,0x25,0x2d,local_24);
      }
      if (local_18 != 0) {
        thunk_FUN_00428baa(in_ECX + 8,10,0x58,local_18,0,&LAB_0040196a);
      }
    }
    thunk_FUN_0042d38a();
    *(undefined4 *)(in_ECX + 0x34) = 0;
    thunk_FUN_0042d87c(in_ECX + 8,3);
  }
  return;
}
```

---

## FUN_0043b890 — 0x43b890

- Classification : internal
- Corps : `0x43b890–0x43b8bd`
- État : pseudocode obtenu
- Evidence : `ev_a9d61cbbb45a8485b4cdca1265255d688226110707f45569556d927366224273`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4019fb` — `thunk_FUN_0043aa78`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043b890(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0043aa78();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0043b8d0 — 0x43b8d0

- Classification : internal
- Corps : `0x43b8d0–0x43b8fd`
- État : pseudocode obtenu
- Evidence : `ev_49d9ec1374d980f67c9ac7920e089adca201dded45ac1d7d29422199ec0457b5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401703` — `thunk_FUN_0043b2a0`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043b8d0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0043b2a0();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0043b910 — 0x43b910

- Classification : internal
- Corps : `0x43b910–0x43b963`
- État : pseudocode obtenu
- Evidence : `ev_3ef5a4b7ae6476a1508e05bea2f0c0f58a574e12fe20f16c48d15b2ef6d11a9f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401519` — `thunk_FUN_0043b980`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0043b910(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491789;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004943b0;
  thunk_FUN_0043b980();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_0043b964 — 0x43b964

- Classification : internal
- Corps : `0x43b964–0x43b97f`
- État : pseudocode obtenu
- Evidence : `ev_87b7d7a7da87b942d9a09ba53a2d295a6d8bdaa32dcf8c16de09812c767b4a6d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043b964(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004943b0;
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_0043b980 — 0x43b980

- Classification : internal
- Corps : `0x43b980–0x43b9ae`
- État : pseudocode obtenu
- Evidence : `ev_c4d3e88bda12ce0560d5884790ec4b511a5931d80d5022afb5ab68f1911c8526`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043b980(void)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x72) = 0;
  *(undefined2 *)(in_ECX + 0x70) = 0;
  *(undefined2 *)(in_ECX + 0x78) = 0xffff;
  *(undefined2 *)(in_ECX + 0x7a) = 0xffff;
  return;
}
```

---


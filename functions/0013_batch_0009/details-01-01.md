# 0013_batch_0009 — détails (1/3)

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

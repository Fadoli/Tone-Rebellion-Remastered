# 0014_batch_0010 — détails (2/3)

## FUN_00449e3c — 0x449e3c

- Classification : internal
- Corps : `0x449e3c–0x449ee1`
- État : pseudocode obtenu
- Evidence : `ev_1f35c8f94dfa9744ae8f5c1008655007d982199a58f182a97798e4915a9525af`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401956` — `thunk_FUN_00449ee2`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x4a18d8` — "Event code: %x\n"
- `0x4a18e8` — "EC Complete\n"

### Pseudocode Ghidra

```c
undefined4 FUN_00449e3c(void)

{
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  int local_14;
  int *local_10;
  int local_c;
  undefined4 local_8;
  
  local_8 = 0;
  if (DAT_005e1758 == 0) {
    local_8 = 0;
  }
  else {
    local_10 = (int *)0x0;
    (**(code **)*DAT_005e175c)(DAT_005e175c,&DAT_00494848,&local_10);
    local_c = (**(code **)(*local_10 + 0x20))(local_10,&local_14,local_1c,local_18,0);
    if (local_c == 0) {
      thunk_FUN_00414ad0(s_Event_code___x_004a18d8,local_14);
    }
    if (local_14 == 1) {
      thunk_FUN_00414ad0(s_EC_Complete_004a18e8);
      thunk_FUN_00449ee2();
    }
    else {
      local_8 = 1;
    }
    (**(code **)(*local_10 + 8))(local_10);
  }
  return local_8;
}
```

---

---

## FUN_00449ee2 — 0x449ee2

- Classification : internal
- Corps : `0x449ee2–0x449f49`
- État : pseudocode obtenu
- Evidence : `ev_1c0eee3ffee85815e5822304695d7b6df6548168aef66a70847df49e90ef1a75`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x65` — `USER32.DLL::ShowCursor`
- `0x401a46` — `thunk_FUN_0042d9ee`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x4a18f8` — "Stopping movie.\n"

### Pseudocode Ghidra

```c
void FUN_00449ee2(void)

{
  int *local_8;
  
  if (DAT_005e1758 != 0) {
    thunk_FUN_00414ad0(s_Stopping_movie__004a18f8);
    (**(code **)*DAT_005e175c)(DAT_005e175c,&DAT_00494838,&local_8);
    (**(code **)(*local_8 + 0x24))(local_8);
    (**(code **)(*local_8 + 8))(local_8);
    DAT_005e1758 = 0;
    thunk_FUN_0042d9ee();
    ShowCursor(1);
  }
  return;
}
```

---

---

## FUN_0044a040 — 0x44a040

- Classification : internal
- Corps : `0x44a040–0x44a093`
- État : pseudocode obtenu
- Evidence : `ev_6ee347856c86b3c32a98c568072f7e8a2ff32546349d1944e79a4712fc696812`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014ec` — `thunk_FUN_0044a0b0`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0044a040(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491a49;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004945d0;
  thunk_FUN_0044a0b0();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0044a094 — 0x44a094

- Classification : internal
- Corps : `0x44a094–0x44a0af`
- État : pseudocode obtenu
- Evidence : `ev_d72f7b39f7946bf4cc13360e03602c354b4b1f413eb2dd78de92b07f29c261b1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044a094(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004945d0;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_0044a0b0 — 0x44a0b0

- Classification : internal
- Corps : `0x44a0b0–0x44a0ba`
- État : pseudocode obtenu
- Evidence : `ev_47f370566cb49d6c1ca54d447dd4f029e6fb6d53a9a639c0d51985e19d4807a9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044a0b0(void)

{
  return;
}
```

---

---

## FUN_0044a0bb — 0x44a0bb

- Classification : internal
- Corps : `0x44a0bb–0x44a15d`
- État : pseudocode obtenu
- Evidence : `ev_f5c6d5d3ca38d5dae709a9d901f4cfb88ac28e6228c7bd53e9dc5715e4533d98`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`
- `0x4016ef` — `thunk_FUN_00449e3c`
- `0x4017d5` — `thunk_FUN_00449b80`
- `0x401956` — `thunk_FUN_00449ee2`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x4023d3` — `thunk_FUN_0046b928`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0044a0bb(short param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  
  if (param_1 == 1) {
    thunk_FUN_00449b80(in_ECX + 0x70);
    thunk_FUN_0046b928(*(undefined4 *)(in_ECX + 4),0x32,0,0,0);
    *(undefined4 *)(in_ECX + 0x34) = 0;
  }
  else if (param_1 == 6) {
    thunk_FUN_00449ee2();
  }
  else {
    if (param_1 != 0x32) {
      uVar2 = thunk_FUN_004293c6(param_1,param_2,param_3);
      return uVar2;
    }
    iVar1 = thunk_FUN_00449e3c();
    if (iVar1 == 0) {
      thunk_FUN_0046c1b4(1,*(undefined4 *)(in_ECX + 100),*(undefined4 *)(in_ECX + 0x68));
    }
  }
  return 0;
}
```

---

---

## FUN_0044a15e — 0x44a15e

- Classification : internal
- Corps : `0x44a15e–0x44a16a`
- État : pseudocode obtenu
- Evidence : `ev_77cce19bf90c1c57b69b8161552c58abd08c5c3a1adcd15fc3b11005cc1b2237`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044a15e(void)

{
  return;
}
```

---

---

## FUN_0044a1c0 — 0x44a1c0

- Classification : internal
- Corps : `0x44a1c0–0x44a1ed`
- État : pseudocode obtenu
- Evidence : `ev_ecdd205943d8ff380080744f360155bc79ea59674d4ee3987967a7d2976421bf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012d5` — `thunk_FUN_0044a094`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0044a1c0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0044a094();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_0044a200 — 0x44a200

- Classification : internal
- Corps : `0x44a200–0x44a20e`
- État : pseudocode obtenu
- Evidence : `ev_5f7b66fb6ec71f2a3f1c1688124c2eedc60a089b73332603c34b71a0dff61e44`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x44a20f` — `FUN_0044a20f`
- `0x44a21e` — `FUN_0044a21e`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044a200(void)

{
  FUN_0044a20f();
  FUN_0044a21e();
  return;
}
```

---

---

## FUN_0044a20f — 0x44a20f

- Classification : internal
- Corps : `0x44a20f–0x44a21d`
- État : pseudocode obtenu
- Evidence : `ev_72a246fcf9e38e135f0ed945065134fc2b3e322b0ddf9c34816b960dd32b08e9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40191f` — `thunk_FUN_0044a9ce`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044a20f(void)

{
  thunk_FUN_0044a9ce();
  return;
}
```

---

---

## FUN_0044a21e — 0x44a21e

- Classification : internal
- Corps : `0x44a21e–0x44a22f`
- État : pseudocode obtenu
- Evidence : `ev_f38ce0a22e23eafc5c15745a8df3eef3200fc23fd8282141962c3db29c06b8d9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476c60` — `FUN_00476c60`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044a21e(void)

{
  FUN_00476c60(FUN_0044a230);
  return;
}
```

---

---

## FUN_0044a230 — 0x44a230

- Classification : internal
- Corps : `0x44a230–0x44a23e`
- État : pseudocode obtenu
- Evidence : `ev_06976ea7ed5e2d7ccdd06f16855e799537ec05109845cc6934b8646e3f6732ff`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401ca3` — `thunk_FUN_0044aa56`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044a230(void)

{
  thunk_FUN_0044aa56();
  return;
}
```

---

---

## FUN_0044a23f — 0x44a23f

- Classification : internal
- Corps : `0x44a23f–0x44a2c9`
- État : pseudocode obtenu
- Evidence : `ev_dc99a2e582afd0b5253bf5fdbbd11fc49f73daff7c94534d5e33bcb7fd486c56`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4737e0` — `_strncpy`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0044a23f(undefined4 *param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = DAT_005e1f50 * 0x68;
  *(undefined4 *)(&DAT_005e2d60 + iVar1) = *param_1;
  *(undefined4 *)(&DAT_005e2d64 + iVar1) = param_1[1];
  *(undefined4 *)(&DAT_005e2d68 + iVar1) = param_1[2];
  *(undefined4 *)(&DAT_005e2d6c + iVar1) = param_1[3];
  *(undefined4 *)(&DAT_005e2d70 + DAT_005e1f50 * 0x68) = param_3;
  *(undefined4 *)(&DAT_005e2d74 + DAT_005e1f50 * 0x68) = param_4;
  _strncpy(&DAT_005e2d78 + DAT_005e1f50 * 0x68,param_2,0x4e);
  DAT_005e1f50 = DAT_005e1f50 + 1;
  return 1;
}
```

---

---

## FUN_0044a2ca — 0x44a2ca

- Classification : internal
- Corps : `0x44a2ca–0x44a369`
- État : pseudocode obtenu
- Evidence : `ev_77d3496741654f65b462f4f6ac5ebb4b35b60eee35976eeefe29bfbef1ef5c63`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472da0` — `FUN_00472da0`
- `0x4734a0` — `FUN_004734a0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0044a2ca(int param_1,undefined4 param_2,uint param_3)

{
  undefined4 uVar1;
  
  if (DAT_005e3118 == 8) {
    uVar1 = 0;
  }
  else if ((param_3 & 1) == 0) {
    if (param_1 != 0) {
      FUN_004734a0(&DAT_005e1778 + DAT_005e3118 * 0x50,param_1,0x50);
      FUN_00472da0(&DAT_005e2ad8 + DAT_005e3118 * 0x50,*(undefined4 *)(param_1 + 0x30));
      *(undefined **)(&DAT_005e17a8 + DAT_005e3118 * 0x50) = &DAT_005e2ad8 + DAT_005e3118 * 0x50;
      DAT_005e3118 = DAT_005e3118 + 1;
    }
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
```

---

---

## FUN_0044a36a — 0x44a36a

- Classification : internal
- Corps : `0x44a36a–0x44a3c7`
- État : pseudocode obtenu
- Evidence : `ev_83b9660da2c99ca55e9600227c79c2f0577025a67045d68b3487883bb9bd59a2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472da0` — `FUN_00472da0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_0044a36a(undefined4 param_1,undefined4 param_2,int param_3)

{
  bool bVar1;
  
  bVar1 = DAT_005e1768 < 8;
  if (bVar1) {
    FUN_00472da0(&DAT_005e2830 + DAT_005e1768 * 0x54,*(undefined4 *)(param_3 + 8));
    *(undefined4 *)(&DAT_005e2880 + DAT_005e1768 * 0x54) = param_1;
    DAT_005e1768 = DAT_005e1768 + 1;
  }
  return bVar1;
}
```

---

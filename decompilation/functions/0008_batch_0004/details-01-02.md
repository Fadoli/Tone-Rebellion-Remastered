# 0008_batch_0004 — détails (2/3)

## FUN_0040fb33 — 0x40fb33

- Classification : internal
- Corps : `0x40fb33–0x40fb83`
- État : pseudocode obtenu
- Evidence : `ev_1c5591eb84b3cb57917db9fb5f9dd245e27189422959da810a17fd27c46a21fc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40150a` — `thunk_FUN_0040f9af`
- `0x401b9f` — `thunk_FUN_0040fa7f`
- `0x4739b0` — `FUN_004739b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0040fb33(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *in_ECX;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  iVar1 = thunk_FUN_0040fa7f();
  if (-1 < iVar1 + param_1) {
    iVar2 = thunk_FUN_0040f9af();
    if (iVar1 + param_1 < iVar2) {
      local_8 = FUN_004739b0(*in_ECX,param_1,1);
    }
  }
  return local_8;
}
```

---

---

## FUN_0040fb84 — 0x40fb84

- Classification : internal
- Corps : `0x40fb84–0x40fc14`
- État : pseudocode obtenu
- Evidence : `ev_12611b8dae36eb63b8693c36cd2fa718f9ffd610e979b843b49b9591d6254e67`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40150a` — `thunk_FUN_0040f9af`
- `0x401749` — `thunk_FUN_00414c97`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x402176` — `thunk_FUN_00414bf7`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040fb84(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int *in_ECX;
  
  if (*in_ECX == -1) {
    param_1 = 0;
  }
  else {
    iVar2 = thunk_FUN_0040f9af();
    bVar1 = false;
    if (iVar2 < 1) {
      param_1 = 0;
    }
    else {
      if (param_1 == 0) {
        param_1 = thunk_FUN_00414bf7(iVar2);
        if (param_1 == 0) {
          return 0;
        }
        bVar1 = true;
      }
      iVar3 = thunk_FUN_0040fc15(param_1,iVar2);
      if (iVar3 != iVar2) {
        if (bVar1) {
          thunk_FUN_00414c97(param_1);
        }
        param_1 = 0;
      }
    }
  }
  return param_1;
}
```

---

---

## FUN_0040fc15 — 0x40fc15

- Classification : internal
- Corps : `0x40fc15–0x40fc6f`
- État : pseudocode obtenu
- Evidence : `ev_6687075565018f38b98755e584d6391126d5b9d63f931a6c8820a6ec50e43223`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40150a` — `thunk_FUN_0040f9af`
- `0x401b9f` — `thunk_FUN_0040fa7f`
- `0x474190` — `FUN_00474190`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040fc15(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 *in_ECX;
  
  if (in_ECX[0x42] != -1) {
    iVar1 = thunk_FUN_0040fa7f();
    uVar2 = thunk_FUN_0040f9af();
    if (uVar2 < (uint)(iVar1 + param_2)) {
      param_2 = uVar2 - iVar1;
    }
  }
  FUN_00474190(*in_ECX,param_1,param_2);
  return;
}
```

---

---

## FUN_0040fc70 — 0x40fc70

- Classification : internal
- Corps : `0x40fc70–0x40fd7f`
- État : pseudocode obtenu
- Evidence : `ev_2489f3357d076d8dd3550a91f98f0490562e1fedd892ce3fb1dbd2cf59328840`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401875` — `thunk_FUN_0040fc15`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040fc70(int param_1,uint param_2,uint param_3,code *param_4)

{
  uint uVar1;
  int iVar2;
  uint local_18;
  int local_14;
  uint local_c;
  
  local_14 = 0;
  local_c = 0;
  while( true ) {
    if (param_3 - 1 <= local_c) {
      iVar2 = thunk_FUN_0040fc15(param_1,param_2 - local_14);
      if (iVar2 == -1) {
        local_14 = -1;
      }
      else {
        local_14 = local_14 + iVar2;
        (*param_4)(param_3,local_c,param_1);
      }
      return local_14;
    }
    uVar1 = thunk_FUN_0040fc15(param_1,param_2 / param_3);
    if (uVar1 == 0xffffffff) break;
    local_14 = local_14 + uVar1;
    if (uVar1 < param_2 / param_3) {
      for (local_18 = local_c; local_18 < param_3; local_18 = local_18 + 1) {
        (*param_4)(param_3,local_18,0);
      }
      return local_14;
    }
    (*param_4)(param_3,local_c,param_1);
    param_1 = param_1 + uVar1;
    local_c = local_c + 1;
  }
  return -1;
}
```

---

---

## FUN_0040fd80 — 0x40fd80

- Classification : internal
- Corps : `0x40fd80–0x40fdaa`
- État : pseudocode obtenu
- Evidence : `ev_643c7d6ef7ceeceb23f1f32e1f046b2071ec8fb85a53dc0b4c459bc34c5069a2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4745f0` — `FUN_004745f0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0040fd80(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *in_ECX;
  
  uVar1 = FUN_004745f0(*in_ECX,param_1,param_2);
  return uVar1;
}
```

---

---

## FUN_0040fdab — 0x40fdab

- Classification : internal
- Corps : `0x40fdab–0x40fdc8`
- État : pseudocode obtenu
- Evidence : `ev_f392cde64729db8b4734f762228cd7b2bcdb4c5294b69f0ca4e5d64c4775f3c4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401875` — `thunk_FUN_0040fc15`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0040fdab(void)

{
  undefined4 local_8;
  
  thunk_FUN_0040fc15(&local_8,4);
  return local_8;
}
```

---

---

## FUN_0040fdc9 — 0x40fdc9

- Classification : internal
- Corps : `0x40fdc9–0x40fe9e`
- État : pseudocode obtenu
- Evidence : `ev_f9513f5bad1a27316d3bb0d265a57dc41a851de5ee16b1cfbdaeb7e15c8287ee`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40150a` — `thunk_FUN_0040f9af`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401b9f` — `thunk_FUN_0040fa7f`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49b374` — "mFileAccess & O_TEXT"
- `0x49b38c` — "C:\\float\\src\\cfile.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0040fdc9(int param_1)

{
  uint uVar1;
  int *in_ECX;
  undefined4 uVar2;
  uint local_18;
  int local_14;
  char local_c [4];
  undefined4 local_8;
  
  if ((in_ECX[0x41] & 0x4000U) == 0) {
    uVar2 = thunk_FUN_00414b64(s_C__float_src_cfile_cpp_0049b38c,0x288,
                               s_mFileAccess___O_TEXT_0049b374);
  }
  else {
    uVar2 = 0;
  }
  if (*in_ECX == -1) {
    local_8 = 0xffffffff;
  }
  else {
    local_c[0] = '\0';
    local_14 = 0;
    uVar1 = thunk_FUN_0040f9af(uVar2);
    local_18 = thunk_FUN_0040fa7f();
    local_8 = 0xffffffff;
    if (local_18 < uVar1) {
      local_8 = 0;
    }
    while ((local_18 < uVar1 && (local_c[0] != '\n'))) {
      thunk_FUN_0040fc15(local_c,1);
      *(char *)(param_1 + local_14) = local_c[0];
      local_14 = local_14 + 1;
      local_18 = local_18 + 1;
    }
    *(undefined1 *)(param_1 + local_14) = 0;
  }
  return local_8;
}
```

---

---

## FUN_0040fe9f — 0x40fe9f

- Classification : internal
- Corps : `0x40fe9f–0x40ff5a`
- État : pseudocode obtenu
- Evidence : `ev_311162cce4fc52471f26550d0c85983cb52da0cb4fdcfcbbae523ff8e6f6093a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4017e4` — `thunk_FUN_0040fdc9`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040fe9f(char *param_1)

{
  bool bVar1;
  char *local_14;
  int local_8;
  
  local_8 = -1;
  bVar1 = false;
  do {
    if ((bVar1) || (local_8 = thunk_FUN_0040fdc9(param_1), local_8 == -1)) {
      return local_8;
    }
    for (local_14 = param_1; *local_14 != '\0'; local_14 = local_14 + 1) {
      if (((*local_14 != ' ') && (*local_14 != '\t')) && (*local_14 != '\n')) {
        if ((*local_14 == ';') || ((*local_14 == '/' && (local_14[1] == '/')))) {
          *local_14 = '\0';
          break;
        }
        bVar1 = true;
      }
    }
  } while( true );
}
```

---

---

## FUN_0040ff5b — 0x40ff5b

- Classification : internal
- Corps : `0x40ff5b–0x410104`
- État : pseudocode obtenu
- Evidence : `ev_78147898fdd67751ac4b9dc7f61c638b16c2a36dd616080db86817b146a0965a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x4737e0` — `_strncpy`
- `0x473aa0` — `FID_conflict:__open`
- `0x473fe0` — `FUN_00473fe0`
- `0x4740d0` — `FUN_004740d0`
- `0x474190` — `FUN_00474190`

### Chaînes référencées

- `0x49b3a4` — "mNumCobs < MAX_COBS"
- `0x49b3b8` — "C:\\float\\src\\cfile.cpp"
- `0x49b3d0` — "num <= MAX_KERNELS - mNumKernels"
- `0x49b3f4` — "C:\\float\\src\\cfile.cpp"

### Pseudocode Ghidra

```c
void FUN_0040ff5b(char *param_1)

{
  undefined4 uVar1;
  int in_ECX;
  int local_c;
  int local_8;
  
  if (4 < *(int *)(in_ECX + 0x6aa0)) {
    thunk_FUN_00414b64(s_C__float_src_cfile_cpp_0049b3b8,0x2d1,s_mNumCobs_<_MAX_COBS_0049b3a4);
  }
  if (*(int *)(in_ECX + 0x6aa0) < 5) {
    _strncpy((char *)(in_ECX + 0x6990 + *(int *)(in_ECX + 0x6aa0) * 0x32),param_1,0x32);
    local_8 = FID_conflict___open(param_1,0x8000);
    if (local_8 != -1) {
      uVar1 = FUN_004740d0(local_8);
      *(undefined4 *)(in_ECX + 0x6a8c + *(int *)(in_ECX + 0x6aa0) * 4) = uVar1;
      FUN_00474190(local_8,&local_c,4);
      if (500 - *(int *)(in_ECX + 27000) < local_c) {
        uVar1 = thunk_FUN_00414b64(s_C__float_src_cfile_cpp_0049b3f4,0x2e5,
                                   s_num_<__MAX_KERNELS___mNumKernels_0049b3d0);
      }
      else {
        uVar1 = 0;
      }
      if (local_c <= 500 - *(int *)(in_ECX + 27000)) {
        FUN_00474190(local_8,in_ECX + *(int *)(in_ECX + 27000) * 0x32,local_c * 0x32,uVar1);
        FUN_00474190(local_8,in_ECX + 25000 + *(int *)(in_ECX + 27000) * 4,local_c << 2);
        FUN_00473fe0(local_8);
        *(int *)(in_ECX + 27000) = *(int *)(in_ECX + 27000) + local_c;
        *(int *)(in_ECX + 0x697c + *(int *)(in_ECX + 0x6aa0) * 4) = local_c;
        *(int *)(in_ECX + 0x6aa0) = *(int *)(in_ECX + 0x6aa0) + 1;
      }
    }
  }
  return;
}
```

---

---

## FUN_00410105 — 0x410105

- Classification : internal
- Corps : `0x410105–0x410160`
- État : pseudocode obtenu
- Evidence : `ev_3d928c3e3c20204be08e14067bfa575cbc3d1a9fe24a546b56dfe0d283c1483b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40183e` — `thunk_FUN_0040ff5b`
- `0x4748a0` — `FUN_004748a0`
- `0x474980` — `FUN_00474980`
- `0x474b00` — `FUN_00474b00`

### Chaînes référencées

- `0x49b410` — "cob.cfg"

### Pseudocode Ghidra

```c
void FUN_00410105(void)

{
  int iVar1;
  undefined1 local_6c [100];
  int local_8;
  
  local_8 = FUN_00474b00(s_cob_cfg_0049b410,&DAT_0049b40c);
  if (local_8 != 0) {
    while( true ) {
      iVar1 = FUN_00474980(local_8,&DAT_0049b418,local_6c);
      if (iVar1 == -1) break;
      thunk_FUN_0040ff5b(local_6c);
    }
    FUN_004748a0(local_8);
  }
  return;
}
```

---

---

## FUN_004104c0 — 0x4104c0

- Classification : internal
- Corps : `0x4104c0–0x4104d5`
- État : pseudocode obtenu
- Evidence : `ev_dce2fd40b367e433d50e86263a496f516c0e32bf3a463391e18c56033a70558a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a6e` — `thunk_FUN_004104e0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004104c0(void)

{
  undefined4 in_ECX;
  
  thunk_FUN_004104e0();
  return in_ECX;
}
```

---

---

## FUN_004104e0 — 0x4104e0

- Classification : internal
- Corps : `0x4104e0–0x410504`
- État : pseudocode obtenu
- Evidence : `ev_c5ff6b6e803acda84a20fe6cb44898407dc3786576c987c3f3cadfc81db98b63`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004104e0(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 27000) = 0;
  *(undefined4 *)(in_ECX + 0x6aa0) = 0;
  return;
}
```

---

---

## FUN_00410510 — 0x410510

- Classification : internal
- Corps : `0x410510–0x410642`
- État : pseudocode obtenu
- Evidence : `ev_c9d82ee41f603bb4b2372d5aff779397fb5c9fb6ebfcadb02a6c190ae955ecbd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401a28` — `thunk_FUN_0041081b`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00410510(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004914ac;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0040f6f7();
  local_8 = 0;
  iVar1 = thunk_FUN_0040f752(param_1,0x8000);
  if (iVar1 == 0) {
    thunk_FUN_0040fc15(&DAT_004b20f0,0x700);
    iVar1 = thunk_FUN_0041081b(param_2,0,0x404f8000,0,0x404f8000,0,0x404f8000);
    _memset(&DAT_004b27f0,iVar1,0xff);
    DAT_004b28ef = 0xff;
    thunk_FUN_0040fc15(&DAT_004bc530,0x700);
    iVar1 = thunk_FUN_0041081b(param_2,0,0,0,0,0,0);
    _memset(&DAT_004bcc30,iVar1,0xff);
    DAT_004bcd2f = 0xff;
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
  }
  else {
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
  }
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

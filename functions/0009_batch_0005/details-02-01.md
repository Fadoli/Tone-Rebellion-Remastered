# 0009_batch_0005 — détails (1/2)

## FUN_00413e71 — 0x413e71

- Classification : internal
- Corps : `0x413e71–0x413e89`
- État : pseudocode obtenu
- Evidence : `ev_6665339d845a39c0df9c63de864df95a7270fc152a495b9f7f465b96eb26cfc3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00413e71(undefined4 param_1)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x1288) = param_1;
  return;
}
```

---

---

## FUN_00413e8a — 0x413e8a

- Classification : internal
- Corps : `0x413e8a–0x414080`
- État : pseudocode obtenu
- Evidence : `ev_f39fecaa50c8d1e93f75d9965a68335c0693806c5b4f23f578af0ea1c87eba72`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401258` — `thunk_FUN_00467ff6`
- `0x40137f` — `thunk_FUN_00412eac`
- `0x40173f` — `thunk_FUN_00412c1d`
- `0x401b7c` — `thunk_FUN_00413675`
- `0x401c8a` — `thunk_FUN_004121b7`
- `0x401d70` — `thunk_FUN_00413b68`
- `0x401ece` — `thunk_FUN_00413344`
- `0x402036` — `thunk_FUN_00413088`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00413e8a(void)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  uint uVar3;
  bool bVar4;
  int local_18;
  
  *(int *)(in_ECX + 0x1274) = *(int *)(in_ECX + 0x1274) + 1;
  bVar4 = false;
  do {
    if (DAT_004befe0 != 0) {
      uVar3 = *(uint *)(in_ECX + 0x1274) % *(uint *)(in_ECX + 0x1278);
      if ((((uVar3 == 0) && (DAT_004befe0 != 0)) && (DAT_004befec != DAT_004befe8)) ||
         (((DAT_004befe0 != 0 && (DAT_004befec == DAT_004befe8)) &&
          (((uVar3 + (*(uint *)(in_ECX + 0x1278) >> 1)) % *(uint *)(in_ECX + 0x1278) == 0 ||
           (*(uint *)(in_ECX + 0x1278) >> 1 == 0)))))) {
        iVar1 = thunk_FUN_00413088();
        bVar4 = iVar1 == 0;
      }
      if (((DAT_004befe0 != 0) && (DAT_004befec != DAT_004befe8)) &&
         ((uVar3 + (*(uint *)(in_ECX + 0x1278) >> 1)) % *(uint *)(in_ECX + 0x1278) == 0)) {
        iVar1 = *(int *)(in_ECX + 0x127c);
        uVar2 = thunk_FUN_00467ff6();
        *(undefined4 *)(in_ECX + ((iVar1 + 1U) % 0x40) * 0x18 + 0xc88) = uVar2;
      }
      if ((bVar4) && (*(int *)(in_ECX + 0x1288) != 0)) {
        (**(code **)(in_ECX + 0x1288))();
      }
      do {
        iVar1 = thunk_FUN_00412eac();
      } while (iVar1 != 0);
    }
    if (DAT_004c03ec != 0) {
      for (local_18 = 0;
          (local_18 < DAT_004befe4 && (*(int *)(&DAT_004bf100 + local_18 * 4) != DAT_004c03ec));
          local_18 = local_18 + 1) {
      }
      if (local_18 < DAT_004befe4) {
        DAT_004c03ec = 0;
        thunk_FUN_00412c1d(local_18);
      }
    }
    thunk_FUN_00413675();
    while (iVar1 = thunk_FUN_00413344(2,1), iVar1 != 0) {
      thunk_FUN_004121b7(iVar1 + 0x10);
    }
  } while (bVar4);
  thunk_FUN_00413b68();
  return;
}
```

---

---

## FUN_00414081 — 0x414081

- Classification : internal
- Corps : `0x414081–0x4140a7`
- État : pseudocode obtenu
- Evidence : `ev_465bdf887183cc058f4d41f0cbe5887015f76e92ad642eab06c04f4cd7f4dd2b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010be` — `thunk_FUN_004133f2`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414081(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  thunk_FUN_004133f2(1,param_1,param_2,param_3,0,0);
  return;
}
```

---

---

## FUN_004140a8 — 0x4140a8

- Classification : internal
- Corps : `0x4140a8–0x4140dc`
- État : pseudocode obtenu
- Evidence : `ev_e98f3641fd7cda7aa75e415010fc4195f3d8f55faa41609550cbe9e8ebc0edcd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401ece` — `thunk_FUN_00413344`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004140a8(void)

{
  int iVar1;
  undefined4 local_8;
  
  local_8 = 0;
  iVar1 = thunk_FUN_00413344(1,1);
  if (iVar1 != 0) {
    local_8 = iVar1 + 0x10;
  }
  return local_8;
}
```

---

---

## FUN_004140dd — 0x4140dd

- Classification : internal
- Corps : `0x4140dd–0x414105`
- État : pseudocode obtenu
- Evidence : `ev_fbd69623917c7e0b2903282a5b0264d13e2a160687ed32844ea3c9e18aeea58d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010be` — `thunk_FUN_004133f2`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004140dd(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  thunk_FUN_004133f2(2,param_1,param_2,param_3,param_4,0);
  return;
}
```

---

---

## FUN_00414106 — 0x414106

- Classification : internal
- Corps : `0x414106–0x41412c`
- État : pseudocode obtenu
- Evidence : `ev_38a325e63cb8d6e87bc68ddea89b7cb74e43acc6fd77beddd579dff961ab5375`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010be` — `thunk_FUN_004133f2`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414106(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  thunk_FUN_004133f2(4,param_1,param_2,param_3,0,0);
  return;
}
```

---

---

## FUN_0041412d — 0x41412d

- Classification : internal
- Corps : `0x41412d–0x414179`
- État : pseudocode obtenu
- Evidence : `ev_b411f8d81f379c51a46e19223c563873b30f0c309168549822884a0a846caf7e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010be` — `thunk_FUN_004133f2`
- `0x472e90` — `_strlen`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041412d(char *param_1)

{
  undefined4 uVar1;
  size_t sVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (DAT_004befe0 != 0) {
    uVar1 = *(undefined4 *)(&DAT_004bf100 + DAT_004befec * 4);
    uVar4 = 0;
    uVar3 = 0;
    sVar2 = _strlen(param_1);
    thunk_FUN_004133f2(3,uVar1,param_1,sVar2 + 2,uVar3,uVar4);
  }
  return;
}
```

---

---

## FUN_0041417a — 0x41417a

- Classification : internal
- Corps : `0x41417a–0x414246`
- État : pseudocode obtenu
- Evidence : `ev_f7c123b793d6f10b9fa4266672cb4cff3d3dc672111c4653f85ab9ce86f75f96`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401ece` — `thunk_FUN_00413344`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49bb18` — "i<GAMEENV.mNumPlayers"
- `0x49bb30` — "C:\\float\\src\\command.cpp"

### Pseudocode Ghidra

```c
int FUN_0041417a(int *param_1)

{
  int iVar1;
  int local_1c;
  int local_8;
  
  local_8 = 0;
  iVar1 = thunk_FUN_00413344(3,1);
  if (iVar1 != 0) {
    local_8 = iVar1 + 0x14;
    if (param_1 != (int *)0x0) {
      for (local_1c = 0; local_1c < DAT_004befe4; local_1c = local_1c + 1) {
        if (*(int *)(&DAT_004bf100 + local_1c * 4) == *(int *)(iVar1 + 0x10)) {
          *param_1 = local_1c;
          break;
        }
      }
      if (DAT_004befe4 <= local_1c) {
        thunk_FUN_00414b64(s_C__float_src_command_cpp_0049bb30,0x5db,
                           s_i<GAMEENV_mNumPlayers_0049bb18);
      }
    }
  }
  return local_8;
}
```

---

---

## FUN_00414ad0 — 0x414ad0

- Classification : internal
- Corps : `0x414ad0–0x414b63`
- État : pseudocode obtenu
- Evidence : `ev_4293d986c56d7088be300364b5ce15bf3e42ed620b0b363891b2013d54a93fa4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4748a0` — `FUN_004748a0`
- `0x474b00` — `FUN_00474b00`
- `0x474bc0` — `FUN_00474bc0`
- `0x474c70` — `FUN_00474c70`

### Chaînes référencées

- `0x49bc64` — "float.out"
- `0x49bc74` — "float.out"

### Pseudocode Ghidra

```c
void FUN_00414ad0(undefined4 param_1)

{
  if (DAT_004c0b20 == 0) {
    DAT_004c0b1c = FUN_00474b00(s_float_out_0049bc64,&DAT_0049bc60);
  }
  else {
    DAT_004c0b1c = FUN_00474b00(s_float_out_0049bc74,&DAT_0049bc70);
  }
  FUN_00474c70(DAT_004c0b1c,param_1,&stack0x00000008);
  FUN_00474bc0(DAT_004c0b1c,&DAT_0049bc80,0);
  FUN_004748a0(DAT_004c0b1c);
  DAT_004c0b20 = DAT_004c0b20 + 1;
  return;
}
```

---

---

## FUN_00414b64 — 0x414b64

- Classification : internal
- Corps : `0x414b64–0x414b90`
- État : pseudocode obtenu
- Evidence : `ev_22d8c8ae2ad59aa883e597b6d5925cc21b774ac25f7ff52fa27f448f86786de0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018fc` — `thunk_FUN_0041cfac`
- `0x4020a4` — `thunk_FUN_0042c4cf`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x49bc84` — "Assert Failed (%s, Line %d):\n %s\n"

### Pseudocode Ghidra

```c
void FUN_00414b64(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  thunk_FUN_0042c4cf();
  thunk_FUN_00414ad0(s_Assert_Failed___s__Line__d____s_0049bc84,param_1,param_2,param_3);
  thunk_FUN_0041cfac(1);
  return;
}
```

---

---

## FUN_00414b91 — 0x414b91

- Classification : internal
- Corps : `0x414b91–0x414bc1`
- État : pseudocode obtenu
- Evidence : `ev_853688b10eaa42311c40648387a04d0608a7d2c0bebe66cf544818c48cd94f1c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018fc` — `thunk_FUN_0041cfac`
- `0x4020a4` — `thunk_FUN_0042c4cf`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x49bca8` — "Assert Failed (%s, Line %d):\n %s\n \"%s\"\n"

### Pseudocode Ghidra

```c
void FUN_00414b91(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  thunk_FUN_0042c4cf();
  thunk_FUN_00414ad0(s_Assert_Failed___s__Line__d____s___0049bca8,param_1,param_2,param_3,param_4);
  thunk_FUN_0041cfac(1);
  return;
}
```

---

---

## FUN_00414bc2 — 0x414bc2

- Classification : internal
- Corps : `0x414bc2–0x414bf6`
- État : pseudocode obtenu
- Evidence : `ev_c746e452e806e7a03440df743df02739819eba6465bd15d76e89582c561495b7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018fc` — `thunk_FUN_0041cfac`
- `0x4020a4` — `thunk_FUN_0042c4cf`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x49bcd0` — "Assert Failed (%s, Line %d):\n %s\n %d (%x)\n"

### Pseudocode Ghidra

```c
void FUN_00414bc2(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  thunk_FUN_0042c4cf();
  thunk_FUN_00414ad0(s_Assert_Failed___s__Line__d____s___0049bcd0,param_1,param_2,param_3,param_4,
                     param_4);
  thunk_FUN_0041cfac(1);
  return;
}
```

---

---

## FUN_00414bf7 — 0x414bf7

- Classification : internal
- Corps : `0x414bf7–0x414c96`
- État : pseudocode obtenu
- Evidence : `ev_0ab9c6f05f0882c15ccc7827a45a2842469c22f1b8116308dfcc2ecb20e53dac`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b20` — `_memset`
- `0x474d20` — `FUN_00474d20`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00414bf7(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  iVar2 = -1;
  if (DAT_004c0b18 == 0) {
    _memset(&DAT_004c0988,0,400);
    DAT_004c0b18 = 1;
  }
  for (iVar1 = 0;
      (iVar3 = iVar2, iVar1 < 100 && (iVar3 = iVar1, *(int *)(&DAT_004c0988 + iVar1 * 4) != 0));
      iVar1 = iVar1 + 1) {
  }
  uVar4 = FUN_00474d20(param_1,iVar1,iVar3,uVar4);
  if (iVar3 != -1) {
    *(undefined4 *)(&DAT_004c0988 + iVar3 * 4) = uVar4;
    *(undefined4 *)(&DAT_004c07f8 + iVar3 * 4) = param_1;
  }
  return uVar4;
}
```

---

---

## FUN_00414c97 — 0x414c97

- Classification : internal
- Corps : `0x414c97–0x414cfe`
- État : pseudocode obtenu
- Evidence : `ev_1ecde4ec9cf3ab888ef3023f6f6a9a42cccf60446844ae1ca4d5741c7c88f346`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x475760` — `FUN_00475760`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414c97(int param_1)

{
  int local_c;
  int local_8;
  
  local_8 = -1;
  if (param_1 != 0) {
    for (local_c = 0; local_c < 100; local_c = local_c + 1) {
      if (*(int *)(&DAT_004c0988 + local_c * 4) == param_1) {
        local_8 = local_c;
        break;
      }
    }
  }
  FUN_00475760(param_1);
  if (local_8 != -1) {
    *(undefined4 *)(&DAT_004c0988 + local_8 * 4) = 0;
  }
  return;
}
```

---

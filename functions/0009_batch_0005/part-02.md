# 0009_batch_0005 — détails (2/3)

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

## FUN_00414cff — 0x414cff

- Classification : internal
- Corps : `0x414cff–0x414d88`
- État : pseudocode obtenu
- Evidence : `ev_292c126f9d1e9cf39aec739a8bedd0a396b99fa4619478f64b291220f147b90d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00414cff(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int local_c;
  int local_8;
  
  local_8 = -1;
  if (DAT_004c0b18 == 0) {
    _memset(&DAT_004c0988,0,400);
    DAT_004c0b18 = 1;
  }
  local_c = 0;
  do {
    if (99 < local_c) {
LAB_00414d62:
      if (local_8 != -1) {
        *(undefined4 *)(&DAT_004c0988 + local_8 * 4) = param_3;
        *(undefined4 *)(&DAT_004c07f8 + local_8 * 4) = param_2;
      }
      return param_3;
    }
    if (*(int *)(&DAT_004c0988 + local_c * 4) == 0) {
      local_8 = local_c;
      goto LAB_00414d62;
    }
    local_c = local_c + 1;
  } while( true );
}
```

---

## FUN_00414d89 — 0x414d89

- Classification : internal
- Corps : `0x414d89–0x414de4`
- État : pseudocode obtenu
- Evidence : `ev_179eafca94eedad4e62b08a7b61dfcb9553f90dd32284f86b1144b85a3f479d0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414d89(undefined4 param_1,int param_2)

{
  int local_c;
  int local_8;
  
  local_8 = -1;
  if (param_2 != 0) {
    for (local_c = 0; local_c < 100; local_c = local_c + 1) {
      if (*(int *)(&DAT_004c0988 + local_c * 4) == param_2) {
        local_8 = local_c;
        break;
      }
    }
  }
  if (local_8 != -1) {
    *(undefined4 *)(&DAT_004c0988 + local_8 * 4) = 0;
  }
  return;
}
```

---

## FUN_00414de5 — 0x414de5

- Classification : internal
- Corps : `0x414de5–0x414e85`
- État : pseudocode obtenu
- Evidence : `ev_f7d1c93967d8386fe88f260a20c3c5e0a52399d9beeb535a3683fd77d5341454`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x49bcfc` — "HeapCheck:"
- `0x49bd08` — " No mallocs yet"
- `0x49bd18` — " %x,%d"
- `0x49bd20` — " Total: %d"

### Pseudocode Ghidra

```c
void FUN_00414de5(void)

{
  int local_c;
  int local_8;
  
  thunk_FUN_00414ad0(s_HeapCheck__0049bcfc);
  if (DAT_004c0b18 == 0) {
    thunk_FUN_00414ad0(s_No_mallocs_yet_0049bd08);
  }
  else {
    local_8 = 0;
    for (local_c = 0; local_c < 100; local_c = local_c + 1) {
      if (*(int *)(&DAT_004c0988 + local_c * 4) != 0) {
        thunk_FUN_00414ad0(s__x__d_0049bd18,*(undefined4 *)(&DAT_004c0988 + local_c * 4),
                           *(undefined4 *)(&DAT_004c07f8 + local_c * 4));
        local_8 = local_8 + *(int *)(&DAT_004c07f8 + local_c * 4);
      }
    }
    thunk_FUN_00414ad0(s_Total___d_0049bd20,local_8);
  }
  return;
}
```

---

## FUN_00414f80 — 0x414f80

- Classification : internal
- Corps : `0x414f80–0x414f8e`
- État : pseudocode obtenu
- Evidence : `ev_e5f145a5289960c69663909f0358e8244311fb4789da7e773555e1165702836c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x414f8f` — `FUN_00414f8f`
- `0x414f9e` — `FUN_00414f9e`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414f80(void)

{
  FUN_00414f8f();
  FUN_00414f9e();
  return;
}
```

---

## FUN_00414f8f — 0x414f8f

- Classification : internal
- Corps : `0x414f8f–0x414f9d`
- État : pseudocode obtenu
- Evidence : `ev_b33c4713b67c505085d3d127d7879a71497e0a3db73ee7db41e89e4b42cc68cc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401c17` — `thunk_FUN_004152ea`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414f8f(void)

{
  thunk_FUN_004152ea();
  return;
}
```

---

## FUN_00414f9e — 0x414f9e

- Classification : internal
- Corps : `0x414f9e–0x414faf`
- État : pseudocode obtenu
- Evidence : `ev_d222f2942c3e1068dd8b748d37f39029a8b8c2fdeeeeab9443a70d82ee79e3fc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476c60` — `FUN_00476c60`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414f9e(void)

{
  FUN_00476c60(FUN_00414fb0);
  return;
}
```

---

## FUN_00414fb0 — 0x414fb0

- Classification : internal
- Corps : `0x414fb0–0x414fbe`
- État : pseudocode obtenu
- Evidence : `ev_35e0ee6d85b2f77c9949aab6684fa2c3cc55c9b31885627255ba681998dda213`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b4` — `thunk_FUN_004152f8`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414fb0(void)

{
  thunk_FUN_004152f8();
  return;
}
```

---

## FUN_00414fbf — 0x414fbf

- Classification : internal
- Corps : `0x414fbf–0x415062`
- État : pseudocode obtenu
- Evidence : `ev_2225dcaac634d008b70b7c2c05ca964d8ad85415a230aca5f56f1143a85007f7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414fbf(short *param_1,int *param_2,int *param_3)

{
  short sVar1;
  short sVar2;
  
  if ((param_1[8] & 2U) == 0) {
    sVar1 = param_1[1];
    if (param_2 != (int *)0x0) {
      *param_2 = (int)*(short *)(&DAT_006137c8 + sVar1 * 0x4c);
    }
    if (param_3 != (int *)0x0) {
      *param_3 = (int)*(short *)(&DAT_006137ca + sVar1 * 0x4c);
    }
  }
  else {
    sVar1 = *(short *)(&DAT_006137c6 + *param_1 * 0x4c);
    sVar2 = param_1[1];
    if (param_2 != (int *)0x0) {
      *param_2 = (int)*(short *)(&DAT_005ec640 + sVar2 * 0x60 + sVar1 * 0x29e8);
    }
    if (param_3 != (int *)0x0) {
      *param_3 = (int)*(short *)((int)(&DAT_005ec640 + sVar2 * 0x60 + sVar1 * 0x29e8) + 2);
    }
  }
  return;
}
```

---

## FUN_00415063 — 0x415063

- Classification : internal
- Corps : `0x415063–0x41511a`
- État : pseudocode obtenu
- Evidence : `ev_51b2bb858f6899cc3394bba5d8f9a9b78dfc787e365dfded36b405be94608b8f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00415063(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = DAT_00618e44 / 2;
  if (DAT_00618e44 % 2 != 0) {
    *(short *)(param_2 + 6) = *(short *)(param_2 + 6) + 1;
    if (*(short *)(param_1 + 0x1c + *(short *)(param_2 + 4) * 2) < *(short *)(param_2 + 6)) {
      *(ushort *)(param_2 + 0x10) = *(ushort *)(param_2 + 0x10) | 0x20;
    }
    if (*(short *)(param_2 + 6) < *(short *)(param_1 + 0x14 + *(short *)(param_2 + 4) * 2)) {
      *(undefined2 *)(param_2 + 6) = *(undefined2 *)(param_1 + 0x14 + *(short *)(param_2 + 4) * 2);
    }
    uVar1 = (uint)*(short *)(param_1 + 0x1c + *(short *)(param_2 + 4) * 2);
    if ((int)uVar1 < (int)*(short *)(param_2 + 6)) {
      *(undefined2 *)(param_2 + 6) = *(undefined2 *)(param_1 + 0x1c + *(short *)(param_2 + 4) * 2);
      uVar1 = param_2;
    }
  }
  return uVar1;
}
```

---

## FUN_0041511b — 0x41511b

- Classification : internal
- Corps : `0x41511b–0x415219`
- État : pseudocode obtenu
- Evidence : `ev_a15cac1c225306aedb8bc03c1e95425c2b687dbd7017886d1a12843486b61afd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40173a` — `thunk_FUN_004672a6`
- `0x40250e` — `thunk_FUN_00414fbf`
- `0x472c6c` — `__ftol`
- `0x476ce4` — `FUN_00476ce4`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041511b(undefined4 param_1,int param_2,int param_3)

{
  short sVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  int local_18;
  float local_14;
  int local_10;
  float local_c;
  float local_8;
  
  local_c = (float)param_3;
  thunk_FUN_00414fbf(param_2,&local_10,&local_18);
  iVar2 = local_10 - *(short *)(param_2 + 10);
  local_14 = (float)iVar2;
  iVar3 = local_18 - *(short *)(param_2 + 0xc);
  fVar4 = (float10)FUN_00476ce4((double)((float)iVar3 * (float)iVar3 + local_14 * local_14));
  local_8 = (float)fVar4;
  if (local_c <= local_8) {
    sVar1 = __ftol(iVar3,iVar2,local_c / local_8);
    *(short *)(param_2 + 10) = *(short *)(param_2 + 10) + sVar1;
    sVar1 = __ftol();
    *(short *)(param_2 + 0xc) = *(short *)(param_2 + 0xc) + sVar1;
  }
  else {
    *(undefined2 *)(param_2 + 10) = (undefined2)local_10;
    *(undefined2 *)(param_2 + 0xc) = (undefined2)local_18;
  }
  thunk_FUN_004672a6((int)*(short *)(param_2 + 10),(int)*(short *)(param_2 + 0xc),local_10,local_18)
  ;
  return;
}
```

---

## FUN_0041521a — 0x41521a

- Classification : internal
- Corps : `0x41521a–0x4152bc`
- État : pseudocode obtenu
- Evidence : `ev_f8fbbf55cd3ba3901294ef07c0e87a274b1b40db63b5a23d15637973bd160dc0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401fc3` — `thunk_FUN_0041511b`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041521a(int param_1,int param_2)

{
  if (DAT_00618e44 % 2 != 0) {
    *(short *)(param_2 + 6) = *(short *)(param_2 + 6) + 1;
    if (*(short *)(param_2 + 6) < *(short *)(param_1 + 0x14 + *(short *)(param_2 + 4) * 2)) {
      *(undefined2 *)(param_2 + 6) = *(undefined2 *)(param_1 + 0x14 + *(short *)(param_2 + 4) * 2);
    }
    else if (*(short *)(param_1 + 0x1c + *(short *)(param_2 + 4) * 2) < *(short *)(param_2 + 6)) {
      *(undefined2 *)(param_2 + 6) = *(undefined2 *)(param_1 + 0x14 + *(short *)(param_2 + 4) * 2);
    }
  }
  thunk_FUN_0041511b(param_1,param_2,(int)*(short *)(param_1 + 0x24));
  return;
}
```

---

## FUN_004152bd — 0x4152bd

- Classification : internal
- Corps : `0x4152bd–0x4152e9`
- État : pseudocode obtenu
- Evidence : `ev_8b69a2741fd93af7eabf0a30a269d6fdfa617dfbaf866f10da933049bb5ae590`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014bf` — `thunk_FUN_00467260`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004152bd(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  
  *(short *)(param_2 + 6) = *(short *)(param_2 + 6) + 1;
  uVar1 = thunk_FUN_00467260(0x8000);
  *(undefined2 *)(param_2 + 0xc) = uVar1;
  return;
}
```

---

## FUN_004152ea — 0x4152ea

- Classification : internal
- Corps : `0x4152ea–0x4152f7`
- État : pseudocode obtenu
- Evidence : `ev_f947e5cf3c6ebbf23adfdc796210d0aa297b9fcfabe0ef7e94d9d4289bb2d3da`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004152ea(void)

{
  undefined4 in_ECX;
  
  return in_ECX;
}
```

---

## FUN_004152f8 — 0x4152f8

- Classification : internal
- Corps : `0x4152f8–0x415371`
- État : pseudocode obtenu
- Evidence : `ev_9bf3fe992f62378de95ff0c4eefcf67df6199f5b1c75bfea4a496db2b027a332`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x49bde0` — "$$$$ SFX Changed: %s using sound \"%s\""

### Pseudocode Ghidra

```c
void FUN_004152f8(void)

{
  int in_ECX;
  int iVar1;
  int local_8;
  
  for (local_8 = 0; local_8 < *(short *)(in_ECX + 0x1200); local_8 = local_8 + 1) {
    iVar1 = in_ECX + local_8 * 0x30;
    if (((*(ushort *)(iVar1 + 0x2c) & 1) != 0) && (*(short *)(iVar1 + 0x28) != -1)) {
      thunk_FUN_00414ad0(s______SFX_Changed___s_using_sound_0049bde0,iVar1,
                         &DAT_005e8230 + *(short *)(iVar1 + 0x28) * 0x48);
    }
  }
  return;
}
```

---

## FUN_00415372 — 0x415372

- Classification : internal
- Corps : `0x415372–0x4153b7`
- État : pseudocode obtenu
- Evidence : `ev_b87ea303ffb71fef7ea466bedd7ae47caf0d81a2e8d06b4c0b7a645324d95047`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00415372(void)

{
  int in_ECX;
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 0x20; local_8 = local_8 + 1) {
    *(undefined2 *)(in_ECX + 0x1202 + local_8 * 0x14) = 0xffff;
  }
  *(undefined2 *)(in_ECX + 0x1482) = 0;
  return;
}
```

---


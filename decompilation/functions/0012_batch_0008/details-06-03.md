# 0012_batch_0008 — détails (3/3)

## FUN_00436e06 — 0x436e06

- Classification : internal
- Corps : `0x436e06–0x436ea7`
- État : pseudocode obtenu
- Evidence : `ev_ca91ee5621d213bb1283aea55835b7876dd881dcb7645fa8cb769fd436a8acf6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`

### Chaînes référencées

- `0x49fa40` — "len < 60"
- `0x49fa4c` — "C:\\float\\src\\islewin.cpp"

### Pseudocode Ghidra

```c
void FUN_00436e06(char *param_1,undefined2 param_2)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (DAT_005dc6e4 < 10) {
    sVar2 = _strlen(param_1);
    if ((int)sVar2 < 0x3c) {
      uVar4 = 0;
    }
    else {
      uVar4 = thunk_FUN_00414b64(s_C__float_src_islewin_cpp_0049fa4c,0x8c7,s_len_<_60_0049fa40);
    }
    iVar1 = DAT_005dc6e4;
    iVar3 = DAT_005dc6e4 * 0x42;
    FUN_00472da0(&DAT_005dc3b0 + iVar3,param_1,uVar4);
    *(undefined2 *)(&DAT_005dc3ec + iVar3) = param_2;
    (&DAT_005dc3ee)[iVar1 * 0x21] = 0;
    (&DAT_005dc3f0)[iVar1 * 0x21] = (short)sVar2 * 2 + 0x3c;
    DAT_005dc6e4 = DAT_005dc6e4 + 1;
  }
  return;
}
```

---

---

## FUN_00436ea8 — 0x436ea8

- Classification : internal
- Corps : `0x436ea8–0x436f3e`
- État : pseudocode obtenu
- Evidence : `ev_f68fa2c50e5d3cf6aca6b4c50d2780bc557f83fecc6bf824984a279c6ba5e81d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00436ea8(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int local_c;
  
  if ((DAT_005dc6e4 != 0) && (DAT_005dc3ee = DAT_005dc3ee + 1, DAT_005dc3f0 <= DAT_005dc3ee)) {
    for (local_c = 0; local_c < DAT_005dc6e4 + -1; local_c = local_c + 1) {
      puVar2 = (undefined4 *)(&DAT_005dc3b0 + (local_c + 1) * 0x42);
      puVar3 = (undefined4 *)(&DAT_005dc3b0 + local_c * 0x42);
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      *(undefined2 *)puVar3 = *(undefined2 *)puVar2;
    }
    DAT_005dc6e4 = DAT_005dc6e4 + -1;
  }
  return;
}
```

---

---

## FUN_00436f3f — 0x436f3f

- Classification : internal
- Corps : `0x436f3f–0x436f55`
- État : pseudocode obtenu
- Evidence : `ev_a7c698c8cf67c2e5f2c314bf931b91913c7e2438e6eb05f154183f57ba8aec0f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_00436f3f(void)

{
  undefined *puVar1;
  
  if (DAT_005dc6e4 < 1) {
    puVar1 = (undefined *)0x0;
  }
  else {
    puVar1 = &DAT_005dc3b0;
  }
  return puVar1;
}
```

---

---

## FUN_004380e0 — 0x4380e0

- Classification : internal
- Corps : `0x4380e0–0x43810d`
- État : pseudocode obtenu
- Evidence : `ev_382d996567015af78a3031065e5f14582a0794e23b1bdd9037c2bfcf90e88b2e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40177b` — `thunk_FUN_0043370b`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004380e0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0043370b();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_00438120 — 0x438120

- Classification : internal
- Corps : `0x438120–0x4381a1`
- État : pseudocode obtenu
- Evidence : `ev_9db51b636f16705e20a38936c1e741f9f9048cf2d6f93d3bd0a1c771ec59a0a7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00438120(int param_1)

{
  int iVar1;
  int local_c;
  
  for (local_c = 0; local_c < 9; local_c = local_c + 1) {
    if (*(int *)(&DAT_005e16b0 + local_c * 4) == param_1) {
      return;
    }
  }
  local_c = DAT_005e16a8 * 3;
  iVar1 = local_c + 3;
  while( true ) {
    if (iVar1 <= local_c) {
      return;
    }
    if (*(int *)(&DAT_005e16b0 + local_c * 4) == 0) break;
    local_c = local_c + 1;
  }
  *(int *)(&DAT_005e16b0 + local_c * 4) = param_1;
  return;
}
```

---

---

## FUN_004381a2 — 0x4381a2

- Classification : internal
- Corps : `0x4381a2–0x4381e0`
- État : pseudocode obtenu
- Evidence : `ev_5364bbe379e3f0fdba385586dd726957d5a7a88e6cc2b73be9e126a8737fb484`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004381a2(int param_1)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 9; local_8 = local_8 + 1) {
    if (*(int *)(&DAT_005e16b0 + local_8 * 4) == param_1) {
      *(undefined4 *)(&DAT_005e16b0 + local_8 * 4) = 0;
    }
  }
  return;
}
```

---

---

## FUN_004381e1 — 0x4381e1

- Classification : internal
- Corps : `0x4381e1–0x43822a`
- État : pseudocode obtenu
- Evidence : `ev_c9282b52c73cceabf3ff26f5a286032393a232d3c3942c797ce7e6073aeaa4ff`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49fb70` — "slot<TOTALCLIPS"
- `0x49fb80` — "C:\\float\\src\\islewin2.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_004381e1(int param_1)

{
  param_1 = DAT_005e16a8 * 3 + param_1;
  if (8 < param_1) {
    thunk_FUN_00414b64(s_C__float_src_islewin2_cpp_0049fb80,0x75,s_slot<TOTALCLIPS_0049fb70);
  }
  return *(undefined4 *)(&DAT_005e16b0 + param_1 * 4);
}
```

---

---

## FUN_0043822b — 0x43822b

- Classification : internal
- Corps : `0x43822b–0x438278`
- État : pseudocode obtenu
- Evidence : `ev_980a1572db041f1717349e6c785ef1fccdbe524ac79403f0e26889b26942726f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49fb9c` — "slot<TOTALCLIPS"
- `0x49fbac` — "C:\\float\\src\\islewin2.cpp"

### Pseudocode Ghidra

```c
void FUN_0043822b(int param_1)

{
  param_1 = DAT_005e16a8 * 3 + param_1;
  if (8 < param_1) {
    thunk_FUN_00414b64(s_C__float_src_islewin2_cpp_0049fbac,0x7d,s_slot<TOTALCLIPS_0049fb9c);
  }
  *(undefined4 *)(&DAT_005e16b0 + param_1 * 4) = 0;
  return;
}
```

---

---

## FUN_00438279 — 0x438279

- Classification : internal
- Corps : `0x438279–0x438297`
- État : pseudocode obtenu
- Evidence : `ev_4a42b2b5984917cc9078a6bb1c54c92b9671c66557171e14cfe09bb08c75053f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00438279(void)

{
  undefined4 *in_ECX;
  
  thunk_FUN_00429243();
  *in_ECX = &PTR_LAB_004942f0;
  return in_ECX;
}
```

---

---

## FUN_00438298 — 0x438298

- Classification : internal
- Corps : `0x438298–0x4382b3`
- État : pseudocode obtenu
- Evidence : `ev_98e3aa08090f8cd442c9915b4abaf13e191f26c1e92b05a4a3564dff51dccbcd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00438298(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004942f0;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_004382b4 — 0x4382b4

- Classification : internal
- Corps : `0x4382b4–0x4382be`
- État : pseudocode obtenu
- Evidence : `ev_ec0b3b22726c1161d4b1119a381495c784add2b175f6c7b16da80eb5f1017987`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004382b4(void)

{
  return;
}
```

---

---

## FUN_004382bf — 0x4382bf

- Classification : internal
- Corps : `0x4382bf–0x438378`
- État : pseudocode obtenu
- Evidence : `ev_d76d5d142cd6742eda6053d7505f16a91fab0cc698a813d1ac03fba45044c5ac`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40146f` — `thunk_FUN_0042d87c`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401d34` — `thunk_FUN_00438379`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x402022` — `thunk_FUN_00406604`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004382bf(short param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int in_ECX;
  
  if (5 < param_1) {
    if (param_1 < 8) {
      if ((*(int *)(in_ECX + 4) == DAT_0062c6bc) && (*(int *)(in_ECX + 0x38) != 0)) {
        uVar2 = thunk_FUN_00438379(param_1,param_2,param_3);
        return uVar2;
      }
    }
    else if (param_1 == 0x33) {
      uVar2 = thunk_FUN_0042d28f();
      *(undefined4 *)(in_ECX + 8) = uVar2;
      uVar1 = thunk_FUN_0042dd0f(0);
      thunk_FUN_00406604(in_ECX + 8,uVar1);
      thunk_FUN_0042d38a();
      thunk_FUN_0042d87c(in_ECX + 8,1);
      return 1;
    }
  }
  uVar2 = thunk_FUN_004293c6(param_1,param_2,param_3);
  return uVar2;
}
```

---

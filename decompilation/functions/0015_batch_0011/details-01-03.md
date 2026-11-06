# 0015_batch_0011 — détails (3/3)

## FUN_0044bbe0 — 0x44bbe0

- Classification : internal
- Corps : `0x44bbe0–0x44bc81`
- État : pseudocode obtenu
- Evidence : `ev_36d3c7d01449d9a1e262db3a58b7034101b06b1e8caa99b2b055f06220688b3d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a2048` — "NETNumCommands >= 0"
- `0x4a205c` — "C:\\float\\src\\network.cpp"

### Pseudocode Ghidra

```c
undefined * FUN_0044bbe0(void)

{
  short local_c;
  
  local_c = 0;
  while( true ) {
    if (7 < local_c) {
      return (undefined *)0x0;
    }
    if (*(int *)(&DAT_005e30f8 + local_c * 4) != 0) break;
    local_c = local_c + 1;
  }
  *(undefined4 *)(&DAT_005e30f8 + local_c * 4) = 0;
  DAT_005e19f8 = DAT_005e19f8 + -1;
  if (-1 < DAT_005e19f8) {
    return &DAT_005e2020 + local_c * 0x80;
  }
  thunk_FUN_00414b64(s_C__float_src_network_cpp_004a205c,0x4e2,s_NETNumCommands_>__0_004a2048);
  return &DAT_005e2020 + local_c * 0x80;
}
```

---

---

## FUN_0044bc82 — 0x44bc82

- Classification : internal
- Corps : `0x44bc82–0x44bce4`
- État : pseudocode obtenu
- Evidence : `ev_9dee919368a81ff1b0ca77d445a2eb94970e0a6fb8dabc96b973030e4641ac10`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_0044bc82(void)

{
  ushort uVar1;
  undefined *local_8;
  
  local_8 = (undefined *)0x0;
  if (0 < DAT_005e176c) {
    local_8 = &DAT_005e1a90 + DAT_005e30a0 * 0x80;
    DAT_005e176c = DAT_005e176c + -1;
    uVar1 = (ushort)(DAT_005e30a0 + 1 >> 0x1f);
    DAT_005e30a0 = (((ushort)(DAT_005e30a0 + 1) ^ uVar1) - uVar1 & 7 ^ uVar1) - uVar1;
  }
  return local_8;
}
```

---

---

## FUN_0044bce5 — 0x44bce5

- Classification : internal
- Corps : `0x44bce5–0x44bd11`
- État : pseudocode obtenu
- Evidence : `ev_c5da577026982c4dc599d3b5b16e56b860abad043effbd15cef9a4d9067e6497`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0044bce5(void)

{
  undefined4 uVar1;
  int *in_ECX;
  
  if (in_ECX[1] == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = DAT_005e1e94;
    if (*in_ECX == 0) {
      uVar1 = 1;
    }
  }
  return uVar1;
}
```

---

---

## FUN_0044bd12 — 0x44bd12

- Classification : internal
- Corps : `0x44bd12–0x44bd4e`
- État : pseudocode obtenu
- Evidence : `ev_284f74334de9d4acae842f071f094054cf58f258cb7a0b4c863793f892ceaae1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_0044bd12(int param_1)

{
  undefined *puVar1;
  int *in_ECX;
  
  if ((in_ECX[1] == 0) || (*in_ECX == 0)) {
    puVar1 = (undefined *)0x0;
  }
  else if (param_1 < DAT_005e1768) {
    puVar1 = &DAT_005e2830 + param_1 * 0x54;
  }
  else {
    puVar1 = (undefined *)0x0;
  }
  return puVar1;
}
```

---

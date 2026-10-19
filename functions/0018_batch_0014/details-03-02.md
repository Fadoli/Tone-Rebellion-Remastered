# 0018_batch_0014 — détails (2/2)

## FUN_0046ea1c — 0x46ea1c

- Classification : internal
- Corps : `0x46ea1c–0x46ea96`
- État : pseudocode obtenu
- Evidence : `ev_d48f1b898bd1118c0aa954997cc4517887787d33e0a72d095caa0cb2a5bf601e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046ea1c(undefined4 param_1,undefined4 param_2)

{
  int in_ECX;
  undefined2 local_8;
  
  for (local_8 = 1; local_8 < 0x29a; local_8 = local_8 + 1) {
    if ((*(int *)(in_ECX + local_8 * 0xc) != 0) && (*(int *)(in_ECX + 4 + local_8 * 0xc) != 0)) {
      (**(code **)(**(int **)(in_ECX + 4 + local_8 * 0xc) + 0x10))(param_1,param_2);
    }
  }
  return;
}
```

---

---

## FUN_0046fe40 — 0x46fe40

- Classification : internal
- Corps : `0x46fe40–0x46fe5e`
- État : pseudocode obtenu
- Evidence : `ev_9a1a3a438de61cc5b8f9e7fac8cd50093ff70d729cd3655cfe68f825bbe2e6f2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402211` — `thunk_FUN_0042a1a1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0046fe40(void)

{
  undefined4 *in_ECX;
  
  thunk_FUN_0042a1a1();
  *in_ECX = &PTR_LAB_004947a0;
  return in_ECX;
}
```

---

---

## FUN_0046fe70 — 0x46fe70

- Classification : internal
- Corps : `0x46fe70–0x46fe9d`
- État : pseudocode obtenu
- Evidence : `ev_7ca457e37be27cdf371c1b637a9b53e7035260717e76125345f0d769a6f18b22`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401fdc` — `thunk_FUN_0046feb0`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0046fe70(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0046feb0();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_0046feb0 — 0x46feb0

- Classification : internal
- Corps : `0x46feb0–0x46fecb`
- État : pseudocode obtenu
- Evidence : `ev_a3e3a03b599004fa9de90a793e7ba8f693a2ddc2bd2e94b4160d180334586c32`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40200e` — `thunk_FUN_0042a1f5`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046feb0(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004947a0;
  thunk_FUN_0042a1f5();
  return;
}
```

---

---

## FUN_0046fee0 — 0x46fee0

- Classification : internal
- Corps : `0x46fee0–0x46ff6e`
- État : pseudocode obtenu
- Evidence : `ev_a33f146f8e48c8e669f38a10be45c43598481d1896ac8c3b3c41b222c949c3f4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0046fee0(int *param_1,int *param_2)

{
  undefined4 local_8;
  
  local_8 = 0;
  if (*(int *)(*param_1 + 4) == *(int *)(*param_2 + 4)) {
    if (*(float *)(*param_1 + 0x10) <= *(float *)(*param_2 + 0x10)) {
      if (*(float *)(*param_1 + 0x10) < *(float *)(*param_2 + 0x10)) {
        local_8 = 1;
      }
    }
    else {
      local_8 = 0xffffffff;
    }
  }
  else if (*(int *)(*param_1 + 4) == 0) {
    local_8 = 1;
  }
  else {
    local_8 = 0xffffffff;
  }
  return local_8;
}
```

---

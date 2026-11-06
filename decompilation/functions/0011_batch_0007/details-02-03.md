# 0011_batch_0007 — détails (3/3)

## FUN_00429209 — 0x429209

- Classification : internal
- Corps : `0x429209–0x429242`
- État : pseudocode obtenu
- Evidence : `ev_60089f167d8a725ffff636d52f369f93cf4e5222f99edaaa5b4c4871d8488763`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00429209(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if ((((param_1 < *(int *)(param_3 + 4)) || (*(int *)(param_3 + 0xc) < param_1)) ||
      (param_2 < *(int *)(param_3 + 8))) || (*(int *)(param_3 + 0x10) < param_2)) {
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

## FUN_00429243 — 0x429243

- Classification : internal
- Corps : `0x429243–0x429261`
- État : pseudocode obtenu
- Evidence : `ev_e226c86e7af328ab359627b9ff5b4ad9d906efae112a9c39c6287863552c2e2d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010e1` — `thunk_FUN_00429276`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00429243(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494168;
  thunk_FUN_00429276();
  return in_ECX;
}
```

---

---

## FUN_00429262 — 0x429262

- Classification : internal
- Corps : `0x429262–0x429275`
- État : pseudocode obtenu
- Evidence : `ev_7bb6f62c0432fd9ea8756f86ba744c3ada95cdc07a65b17c33e2417cf0025f2a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429262(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494168;
  return;
}
```

---

---

## FUN_00429276 — 0x429276

- Classification : internal
- Corps : `0x429276–0x42930e`
- État : pseudocode obtenu
- Evidence : `ev_314c189323a147e2680822eb0f068dcf8af18d5582e6ec09118a2f285b932b5c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429276(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 4) = 0;
  *(undefined4 *)(in_ECX + 8) = 0;
  *(undefined2 *)(in_ECX + 0x1c) = 0xffff;
  *(undefined2 *)(in_ECX + 0x1e) = 0xffff;
  *(undefined1 *)(in_ECX + 0x20) = 0;
  *(undefined4 *)(in_ECX + 0x38) = 0;
  *(undefined4 *)(in_ECX + 0x3c) = 0;
  *(undefined4 *)(in_ECX + 0x44) = 0;
  *(undefined2 *)(in_ECX + 0x60) = 0;
  *(undefined4 *)(in_ECX + 100) = 0;
  *(undefined4 *)(in_ECX + 0x68) = 0;
  *(undefined2 *)(in_ECX + 0x6c) = 0;
  *(undefined2 *)(in_ECX + 0x6e) = 0;
  *(undefined4 *)(in_ECX + 0x40) = 0;
  *(undefined4 *)(in_ECX + 0x34) = 0;
  return;
}
```

---

---

## FUN_0042930f — 0x42930f

- Classification : internal
- Corps : `0x42930f–0x42932d`
- État : pseudocode obtenu
- Evidence : `ev_70863ade22444382a63117a55fd68b519aaefc1e9000de9099b7252692795c21`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021f3` — `thunk_FUN_0046c7df`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042930f(void)

{
  undefined4 uVar1;
  int in_ECX;
  
  uVar1 = thunk_FUN_0046c7df(in_ECX);
  *(undefined4 *)(in_ECX + 4) = uVar1;
  return;
}
```

---

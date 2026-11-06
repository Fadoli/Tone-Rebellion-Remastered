# 0010_batch_0006 — détails (2/2)

## FUN_0041e454 — 0x41e454

- Classification : internal
- Corps : `0x41e454–0x41e4c2`
- État : pseudocode obtenu
- Evidence : `ev_516df530870cffc769dce043e9a8c1b1b8c1f94b19f0c02801576769f23972ae`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0041e454(int param_1)

{
  undefined4 local_8;
  
  if ((((*(short *)(param_1 + 0x10) == 6) || (*(short *)(param_1 + 0x10) == 0xd)) ||
      ((*(short *)(param_1 + 0x10) == 4 &&
       ((4 < *(short *)(param_1 + 0x12) && (*(short *)(param_1 + 0x12) < 0x22)))))) ||
     ((*(short *)(param_1 + 0x10) == 0xb || (*(short *)(param_1 + 0x10) == 0x11)))) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  return local_8;
}
```

---

---

## FUN_0041e4c3 — 0x41e4c3

- Classification : internal
- Corps : `0x41e4c3–0x41e4d8`
- État : pseudocode obtenu
- Evidence : `ev_909c86d7e5beeb6c56e239a696f6674e0d0a06e79b0b871c7d32ff8eede7db65`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012c1` — `thunk_FUN_0041e4e4`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0041e4c3(void)

{
  undefined4 in_ECX;
  
  thunk_FUN_0041e4e4();
  return in_ECX;
}
```

---

---

## FUN_0041e4d9 — 0x41e4d9

- Classification : internal
- Corps : `0x41e4d9–0x41e4e3`
- État : pseudocode obtenu
- Evidence : `ev_ba02dc42419fe4d9b404370bb4ce877d13fe06c60f8e545e14a97b80b68fc08a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041e4d9(void)

{
  return;
}
```

---

---

## FUN_0041e4e4 — 0x41e4e4

- Classification : internal
- Corps : `0x41e4e4–0x41e568`
- État : pseudocode obtenu
- Evidence : `ev_a5f6ff6cbb1d9a1b23aa8807337444803e3415de869ec691acf503f150bb3523`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041e4e4(void)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x12) = 0;
  *(undefined2 *)(in_ECX + 0x10) = 0;
  *(undefined2 *)(in_ECX + 0x2a) = 0;
  *(undefined2 *)(in_ECX + 0x28) = 0;
  *(undefined2 *)(in_ECX + 8) = 0;
  *(undefined4 *)(in_ECX + 0x18) = 0;
  *(undefined4 *)(in_ECX + 0x1c) = 0;
  *(undefined2 *)(in_ECX + 0xc) = 0xffff;
  *(undefined4 *)(in_ECX + 0x3c) = 0;
  *(undefined4 *)(in_ECX + 0x38) = 0xffffffff;
  *(undefined2 *)(in_ECX + 0x40) = 0xffff;
  *(undefined4 *)(in_ECX + 0x2c) = 0;
  *(undefined2 *)(in_ECX + 0x48) = 0xffff;
  return;
}
```

---

# 0013_batch_0009 — détails (3/3)

## FUN_0043b910 — 0x43b910

- Classification : internal
- Corps : `0x43b910–0x43b963`
- État : pseudocode obtenu
- Evidence : `ev_3ef5a4b7ae6476a1508e05bea2f0c0f58a574e12fe20f16c48d15b2ef6d11a9f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401519` — `thunk_FUN_0043b980`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0043b910(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491789;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004943b0;
  thunk_FUN_0043b980();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0043b964 — 0x43b964

- Classification : internal
- Corps : `0x43b964–0x43b97f`
- État : pseudocode obtenu
- Evidence : `ev_87b7d7a7da87b942d9a09ba53a2d295a6d8bdaa32dcf8c16de09812c767b4a6d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043b964(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004943b0;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_0043b980 — 0x43b980

- Classification : internal
- Corps : `0x43b980–0x43b9ae`
- État : pseudocode obtenu
- Evidence : `ev_c4d3e88bda12ce0560d5884790ec4b511a5931d80d5022afb5ab68f1911c8526`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043b980(void)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x72) = 0;
  *(undefined2 *)(in_ECX + 0x70) = 0;
  *(undefined2 *)(in_ECX + 0x78) = 0xffff;
  *(undefined2 *)(in_ECX + 0x7a) = 0xffff;
  return;
}
```

---

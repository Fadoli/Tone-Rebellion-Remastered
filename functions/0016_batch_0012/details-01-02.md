# 0016_batch_0012 — détails (2/4)

## FUN_004557bc — 0x4557bc

- Classification : internal
- Corps : `0x4557bc–0x455824`
- État : pseudocode obtenu
- Evidence : `ev_7060c372bf104f242ef237949c5b00597b5bd6a4e25337c298ccc2674e7f672c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x48b100` — `__strcmpi`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined2 FUN_004557bc(char *param_1)

{
  int iVar1;
  int in_ECX;
  int local_c;
  
  local_c = 0;
  while( true ) {
    if ((int)(uint)*(ushort *)(in_ECX + 0x1740) <= local_c) {
      return 0xffff;
    }
    iVar1 = __strcmpi((char *)(in_ECX + 0x1500 + local_c * 9),param_1);
    if (iVar1 == 0) break;
    local_c = local_c + 1;
  }
  return (undefined2)local_c;
}
```

---

---

## FUN_00455825 — 0x455825

- Classification : internal
- Corps : `0x455825–0x455832`
- État : pseudocode obtenu
- Evidence : `ev_ad859f781daa935be0ac28f19ae469a0bd081bfd7b19aacc4cf8d516e3139d02`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00455825(void)

{
  undefined4 in_ECX;
  
  return in_ECX;
}
```

---

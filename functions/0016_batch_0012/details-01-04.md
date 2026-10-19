# 0016_batch_0012 — détails (4/4)

## FUN_00456a13 — 0x456a13

- Classification : internal
- Corps : `0x456a13–0x456a6a`
- État : pseudocode obtenu
- Evidence : `ev_fb6d0c4daa51eaf949b8f18e16e038d10f01fe5b1afd5097a071f38cef255a2a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x48b100` — `__strcmpi`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00456a13(char *param_1)

{
  int iVar1;
  int in_ECX;
  uint local_8;
  
  local_8 = 0;
  while( true ) {
    if ((int)*(short *)(in_ECX + 0xa20) <= (int)local_8) {
      return 0xffff;
    }
    iVar1 = __strcmpi(param_1,(char *)(in_ECX + local_8 * 9));
    if (iVar1 == 0) break;
    local_8 = local_8 + 1;
  }
  return local_8 & 0xffff;
}
```

---

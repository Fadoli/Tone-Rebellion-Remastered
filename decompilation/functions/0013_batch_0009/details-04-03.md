# 0013_batch_0009 — détails (3/3)

## FUN_00440451 — 0x440451

- Classification : internal
- Corps : `0x440451–0x440566`
- État : pseudocode obtenu
- Evidence : `ev_9e5f61cf79edd2a0425ee2f8b0f8c237a37b466f2219e936bdc3427204f308c2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00440451(int param_1,int param_2)

{
  int in_ECX;
  undefined *local_2c;
  undefined *local_28;
  int local_20;
  int local_18;
  int local_10;
  
  if ((*(int *)(in_ECX + 0x70) != 0) && (*(short *)(*(int *)(in_ECX + 0x70) + 0x18) != -1)) {
    *(undefined2 *)(in_ECX + 0x76) = 0xffff;
    if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2f) {
      local_28 = &DAT_004a04b8;
    }
    else {
      local_28 = &DAT_004a0498;
    }
    if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2f) {
      local_2c = &DAT_004a04c8;
    }
    else {
      local_2c = &DAT_004a04a8;
    }
    for (local_10 = 0; local_10 < 6; local_10 = local_10 + 1) {
      if (*(short *)(in_ECX + 0x78 + local_10 * 2) != -1) {
        local_18 = (param_1 - *(int *)(in_ECX + 0xc)) - (int)*(short *)(local_28 + local_10 * 2);
        if (local_18 < 0) {
          local_18 = -local_18;
        }
        local_20 = (param_2 - *(int *)(in_ECX + 0x10)) - (int)*(short *)(local_2c + local_10 * 2);
        if (local_20 < 0) {
          local_20 = -local_20;
        }
        if ((local_18 < 0xf) && (local_20 < 0xf)) {
          *(undefined2 *)(in_ECX + 0x76) = (undefined2)local_10;
          return;
        }
      }
    }
  }
  return;
}
```

---

# 0015_batch_0011 — détails (3/3)

## FUN_00452656 — 0x452656

- Classification : internal
- Corps : `0x452656–0x4526dd`
- État : pseudocode obtenu
- Evidence : `ev_a3e1a4c67af78c87a718e3f471c75cfeaca52655210d8a34d98cbcbc754c8672`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40149c` — `thunk_FUN_00414bc2`
- `0x4021ad` — `thunk_FUN_004641de`

### Chaînes référencées

- `0x4a2a24` — "item < NUMPADITEMINFOS"
- `0x4a2a3c` — "C:\\float\\src\\pad.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_00452656(int param_1,undefined4 param_2)

{
  int *piVar1;
  int in_ECX;
  undefined4 uVar2;
  undefined4 local_8;
  
  if (param_1 < 0x65) {
    uVar2 = 0;
  }
  else {
    uVar2 = thunk_FUN_00414bc2(s_C__float_src_pad_cpp_004a2a3c,0x536,
                               s_item_<_NUMPADITEMINFOS_004a2a24,param_1);
  }
  local_8 = 0;
  if (param_1 != 0) {
    if ((*(int *)(in_ECX + 4) == 0) &&
       (piVar1 = (int *)thunk_FUN_004641de(param_2,param_1,uVar2), *piVar1 <= *(int *)(in_ECX + 0xc)
       )) {
      return 1;
    }
    if (*(int *)(in_ECX + 4) == 1) {
      local_8 = 1;
    }
  }
  return local_8;
}
```

---

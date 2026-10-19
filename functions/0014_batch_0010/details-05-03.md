# 0014_batch_0010 — détails (3/3)

## FUN_0044a3c8 — 0x44a3c8

- Classification : internal
- Corps : `0x44a3c8–0x44a55d`
- État : pseudocode obtenu
- Evidence : `ev_18b19c63237afbb0d29d7601800258092c3cc6120d1b2fc1e93bd2b19920b830`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x4734a0` — `FUN_004734a0`

### Chaînes référencées

- `0x4a1960` — "size + 3*sizeof(Dword) < MAX_COMMAND_SIZE"
- `0x4a198c` — "C:\\float\\src\\network.cpp"
- `0x4a19a8` — "i<MAX_BUFFERED_COMMANDS"
- `0x4a19c0` — "C:\\float\\src\\network.cpp"

### Pseudocode Ghidra

```c
undefined4
FUN_0044a3c8(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  short local_10;
  undefined4 local_8;
  
  local_8 = 0;
  if (param_5 == 0) {
    if (DAT_005e19f8 < 8) {
      if (param_3 + 0xcU < 0x80) {
        uVar2 = 0;
      }
      else {
        uVar2 = thunk_FUN_00414b64(s_C__float_src_network_cpp_004a198c,0xfc,
                                   s_size___3_sizeof_Dword__<_MAX_COM_004a1960);
      }
      local_10 = 0;
      while ((local_10 < 8 && (*(int *)(&DAT_005e30f8 + local_10 * 4) != 0))) {
        local_10 = local_10 + 1;
      }
      if (local_10 < 8) {
        iVar1 = local_10 * 0x80;
        *(undefined4 *)(&DAT_005e2020 + iVar1) = param_4;
        *(undefined4 *)(&DAT_005e2024 + iVar1) = param_1;
        *(int *)(&DAT_005e2028 + iVar1) = param_3;
        FUN_004734a0(iVar1 + 0x5e202c,param_2,param_3,0,uVar2);
        local_8 = 1;
        *(undefined4 *)(&DAT_005e30f8 + local_10 * 4) = 1;
        DAT_005e19f8 = DAT_005e19f8 + 1;
      }
      else {
        thunk_FUN_00414b64(s_C__float_src_network_cpp_004a19c0,0x104,
                           s_i<MAX_BUFFERED_COMMANDS_004a19a8);
      }
    }
  }
  else {
    DAT_005e1f58 = param_4;
    DAT_005e1f5c = param_1;
    DAT_005e1f60 = param_3;
    FUN_004734a0(&DAT_005e1f64,param_2,param_3);
    local_8 = 1;
  }
  return local_8;
}
```

---

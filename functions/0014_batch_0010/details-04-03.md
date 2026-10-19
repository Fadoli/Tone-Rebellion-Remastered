# 0014_batch_0010 — détails (3/3)

## FUN_00448d22 — 0x448d22

- Classification : internal
- Corps : `0x448d22–0x448e59`
- État : pseudocode obtenu
- Evidence : `ev_4ec736e5647cf4849a446f97cb8c43fbc1bb893896b2dcd6ce29c86d83d9dde7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401154` — `thunk_FUN_00414b91`
- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x4017f3` — `thunk_FUN_0040fb84`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401d02` — `thunk_FUN_0046cce7`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x40227f` — `thunk_FUN_0046c25d`

### Chaînes référencées

- `0x4a14f0` — "data\\titscrn.pal"
- `0x4a14f0` — "data\\titscrn.pal"
- `0x4a14f0` — "data\\titscrn.pal"
- `0x4a1504` — "status==0"
- `0x4a1510` — "C:\\float\\src\\master.cpp"

### Pseudocode Ghidra

```c
void FUN_00448d22(short param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar2;
  undefined1 local_314 [768];
  char *local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004919ee;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (param_1 == 1) {
    thunk_FUN_0040f6f7();
    local_8 = 0;
    local_14 = s_data_titscrn_pal_004a14f0;
    iVar1 = thunk_FUN_0040f752(s_data_titscrn_pal_004a14f0,0x8000);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = thunk_FUN_00414b91(s_C__float_src_master_cpp_004a1510,0xc1,s_status__0_004a1504,
                                 local_14);
    }
    thunk_FUN_0040fb84(local_314);
    thunk_FUN_0046cce7(local_314);
    thunk_FUN_0040f966(uVar2);
    thunk_FUN_0046c25d(1,0,0,0);
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
  }
  else if (param_1 == 3) {
    thunk_FUN_0046c25d(0xb,0,0,0);
  }
  else if (param_1 == 4) {
    *param_4 = 0;
  }
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

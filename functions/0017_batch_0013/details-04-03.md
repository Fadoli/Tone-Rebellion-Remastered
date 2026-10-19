# 0017_batch_0013 — détails (3/3)

## FUN_004642a3 — 0x4642a3

- Classification : internal
- Corps : `0x4642a3–0x46466e`
- État : pseudocode obtenu
- Evidence : `ev_561df3c3edee5a21c16764f7b95d5fa1e14e3a19d3ca83157c30bd51568c31c9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401046` — `thunk_FUN_0046303b`
- `0x4015cd` — `thunk_FUN_00463563`
- `0x401749` — `thunk_FUN_00414c97`
- `0x40187a` — `thunk_FUN_004633a7`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x402176` — `thunk_FUN_00414bf7`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472f10` — `FUN_00472f10`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a4ff4` — "pad.txt"
- `0x4a4ffc` — "floater.txt"
- `0x4a5008` — "spells.txt"
- `0x4a5014` — "data\\worldpos.txt"
- `0x4a5028` — "FALSE"
- `0x4a5030` — "C:\\float\\src\\tworld.cpp"
- `0x4a504c` — "TW_NumWorlds<=MAX_WORLD_DEFINITIONS"
- `0x4a5070` — "C:\\float\\src\\tworld.cpp"
- `0x4a508c` — "i0 <= MAX_ISLANDS"
- `0x4a50a0` — "C:\\float\\src\\tworld.cpp"
- `0x4a50b8` — "%d %d %d %d"
- `0x4a50c4` — "t == 4"
- `0x4a50cc` — "C:\\float\\src\\tworld.cpp"
- `0x4a50e4` — "%d %d"
- `0x4a50ec` — "i0 < TW_NumIslands[w] && i1 < TW_NumIslands[w]"
- `0x4a511c` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_004642a3(void)

{
  int iVar1;
  undefined4 uVar2;
  int local_94;
  undefined2 local_90 [2];
  undefined4 local_8c;
  undefined1 local_88 [100];
  int local_24;
  int local_20 [4];
  int local_10;
  int local_c;
  undefined4 local_8;
  
  thunk_FUN_0046303b(s_pad_txt_004a4ff4);
  thunk_FUN_004633a7(s_floater_txt_004a4ffc);
  thunk_FUN_00463563(s_spells_txt_004a5008);
  local_8 = thunk_FUN_00414bf7(10000);
  iVar1 = thunk_FUN_0040f419(s_data_worldpos_txt_004a5014,local_8,10000);
  if (iVar1 == 0) {
    _memset(&DAT_005ebd68,0,6);
    _memset(&DAT_005ebf98,0,6);
    thunk_FUN_0040f5b3(local_88,0);
    FUN_00472f10(local_88,&DAT_004a5048,&DAT_005ebd70);
    if (3 < DAT_005ebd70) {
      thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a5070,0x49a,
                         s_TW_NumWorlds<_MAX_WORLD_DEFINITI_004a504c);
    }
    for (local_10 = 0; local_10 < DAT_005ebd70; local_10 = local_10 + 1) {
      thunk_FUN_0040f5b3(local_88,0);
      FUN_00472f10(local_88,&DAT_004a5088,local_20);
      if (0xf < local_20[0]) {
        thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a50a0,0x4a0,s_i0_<__MAX_ISLANDS_004a508c);
      }
      *(undefined2 *)(&DAT_005ebf98 + local_10 * 2) = (undefined2)local_20[0];
      for (local_94 = 0; local_94 < *(short *)(&DAT_005ebf98 + local_10 * 2);
          local_94 = local_94 + 1) {
        thunk_FUN_0040f5b3(local_88,0);
        local_c = FUN_00472f10(local_88,s__d__d__d__d_004a50b8,local_20,&local_24,&local_8c,local_90
                              );
        if (local_c != 4) {
          thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a50cc,0x4a8,s_t____4_004a50c4);
        }
        *(float *)(&DAT_005ebd78 + local_94 * 0xc + local_10 * 0xb4) =
             (float)local_20[0] * 0.017453277;
        *(int *)(&DAT_005ebd7c + local_94 * 0xc + local_10 * 0xb4) = local_24;
        *(undefined4 *)(&DAT_005ebd80 + local_94 * 0xc + local_10 * 0xb4) = local_8c;
        *(undefined2 *)(&DAT_005eaba8 + local_94 * 2 + local_10 * 0x1e) = local_90[0];
      }
      do {
        thunk_FUN_0040f5b3(local_88,0);
        local_c = FUN_00472f10(local_88,s__d__d_004a50e4,local_20,&local_24);
        if (local_c == 2) {
          if ((*(short *)(&DAT_005ebf98 + local_10 * 2) <= local_20[0]) ||
             (*(short *)(&DAT_005ebf98 + local_10 * 2) <= local_24)) {
            thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a511c,0x4b7,
                               s_i0_<_TW_NumIslands[w]_&&_i1_<_TW_004a50ec);
          }
          *(undefined2 *)
           (&DAT_0061fa54 + *(short *)(&DAT_005ebd68 + local_10 * 2) * 8 + local_10 * 0x100) =
               (undefined2)local_20[0];
          *(undefined2 *)
           (&DAT_0061fa56 + *(short *)(&DAT_005ebd68 + local_10 * 2) * 8 + local_10 * 0x100) =
               (undefined2)local_24;
          *(undefined4 *)
           (&DAT_0061fa50 + *(short *)(&DAT_005ebd68 + local_10 * 2) * 8 + local_10 * 0x100) = 0;
          *(short *)(&DAT_005ebd68 + local_10 * 2) = *(short *)(&DAT_005ebd68 + local_10 * 2) + 1;
        }
      } while (local_c == 2);
    }
    thunk_FUN_00414c97(local_8);
    uVar2 = 1;
  }
  else {
    thunk_FUN_00414c97(local_8);
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a5030,0x490,s_FALSE_004a5028);
    uVar2 = 0;
  }
  return uVar2;
}
```

---

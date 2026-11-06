# 0008_batch_0004 — détails (3/3)

## FUN_00410643 — 0x410643

- Classification : internal
- Corps : `0x410643–0x4106dc`
- État : pseudocode obtenu
- Evidence : `ev_7f7b020659ba71437a19e3a43d05a0335ba6895a255049b6cc23800f2990d6ff`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x401eba` — `thunk_FUN_0040f752`

### Chaînes référencées

- `0x49b478` — "data\\imremap.haz"

### Pseudocode Ghidra

```c
void FUN_00410643(void)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004914c2;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (DAT_004bcd30 == 0) {
    thunk_FUN_0040f6f7();
    local_8 = 0;
    thunk_FUN_0040f752(s_data_imremap_haz_0049b478,0x8000);
    thunk_FUN_0040fc15(&DAT_004b1ff0,0x100);
    thunk_FUN_0040f966();
    DAT_004bcd30 = 1;
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
  }
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

---

## FUN_004106dd — 0x4106dd

- Classification : internal
- Corps : `0x4106dd–0x41072e`
- État : pseudocode obtenu
- Evidence : `ev_5dee659e6ca6ce0decafdf17f8c960d7218ffeb39dac103e234aace22ceea725`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49b48c` — "degree >= 0 && degree < NUM_HAZE_DEGREES"
- `0x49b4b8` — "C:\\float\\src\\color.cpp"

### Pseudocode Ghidra

```c
undefined * FUN_004106dd(int param_1,int param_2)

{
  undefined *puVar1;
  
  if ((param_2 < 0) || (7 < param_2)) {
    thunk_FUN_00414b64(s_C__float_src_color_cpp_0049b4b8,0x4c,
                       s_degree_>__0____degree_<_NUM_HAZE_0049b48c);
  }
  if (param_1 == 0) {
    puVar1 = &DAT_004bc530 + param_2 * 0x100;
  }
  else {
    puVar1 = &DAT_004b20f0 + param_2 * 0x100;
  }
  return puVar1;
}
```

---

---

## FUN_0041072f — 0x41072f

- Classification : internal
- Corps : `0x41072f–0x410764`
- État : pseudocode obtenu
- Evidence : `ev_3d36c7e7bdb49320ccc35a7f5cde0e1c8fbfa86e0fafdc603147536e039501f2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49b4d0` — "RemapLoaded"
- `0x49b4dc` — "C:\\float\\src\\color.cpp"

### Pseudocode Ghidra

```c
undefined * FUN_0041072f(void)

{
  if (DAT_004bcd30 == 0) {
    thunk_FUN_00414b64(s_C__float_src_color_cpp_0049b4dc,0x58,s_RemapLoaded_0049b4d0);
  }
  return &DAT_004b1ff0;
}
```

---

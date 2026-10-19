# 0007_batch_0003 — détails (2/2)

## FUN_0040e764 — 0x40e764

- Classification : internal
- Corps : `0x40e764–0x40e816`
- État : pseudocode obtenu
- Evidence : `ev_3333d68ca3c49338aaa833c5cdfd0ad37c2b6d35b51ca53a7686055ecc035761`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014d8` — `thunk_FUN_0040e2e6`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472f10` — `FUN_00472f10`

### Chaînes référencées

- `0x49b108` — "%s %s"

### Pseudocode Ghidra

```c
void FUN_0040e764(undefined4 param_1)

{
  int iVar1;
  int in_ECX;
  undefined1 local_144 [52];
  undefined1 local_110 [52];
  undefined1 local_dc [212];
  int local_8;
  
  thunk_FUN_0040f419(param_1,*(undefined4 *)(in_ECX + 0x2fe0),*(undefined4 *)(in_ECX + 0x2fe4));
  local_8 = 0;
  while (local_8 == 0) {
    iVar1 = thunk_FUN_0040f5b3(local_dc,0);
    if (iVar1 == -1) {
      local_8 = 1;
    }
    else {
      iVar1 = FUN_00472f10(local_dc,s__s__s_0049b108,local_110,local_144);
      if (iVar1 == 2) {
        thunk_FUN_0040e2e6(local_110,local_144);
      }
    }
  }
  return;
}
```

---

---

## FUN_0040e817 — 0x40e817

- Classification : internal
- Corps : `0x40e817–0x40e863`
- État : pseudocode obtenu
- Evidence : `ev_6f90097044220810713729fa84f863b491d518117b24ac4cb23cdedde20e3c43`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014d8` — `thunk_FUN_0040e2e6`
- `0x4017fd` — `thunk_FUN_0040e6a9`
- `0x401acd` — `thunk_FUN_0040ebde`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040e817(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  undefined2 extraout_var;
  
  sVar1 = thunk_FUN_0040ebde(param_1);
  if (sVar1 != -1) {
    thunk_FUN_0040e6a9(CONCAT22(extraout_var,sVar1));
    thunk_FUN_0040e2e6(param_2,param_1);
  }
  return;
}
```

---

---

## FUN_0040e864 — 0x40e864

- Classification : internal
- Corps : `0x40e864–0x40ebdd`
- État : pseudocode obtenu
- Evidence : `ev_f077e763479e8a1e4fa81db5773b2fcd964d477382f91c2d64c9b2e558c712b7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40149c` — `thunk_FUN_00414bc2`
- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x40150a` — `thunk_FUN_0040f9af`
- `0x401717` — `thunk_FUN_0040ecd6`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49b110` — "mActive"
- `0x49b118` — "C:\\float\\src\\cache.cpp"
- `0x49b130` — "handle < MAX_CACHE_ITEMS"
- `0x49b14c` — "C:\\float\\src\\cache.cpp"
- `0x49b164` — "mFilenames[handle][0] != 0"
- `0x49b180` — "C:\\float\\src\\cache.cpp"
- `0x49b198` — "cache_size < mCacheSize"
- `0x49b1b0` — "C:\\float\\src\\cache.cpp"
- `0x49b1c8` — "loadstat == file_size"
- `0x49b1e0` — "C:\\float\\src\\cache.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0040e864(ushort param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int in_ECX;
  uint uVar4;
  undefined4 *unaff_FS_OFFSET;
  int local_12c;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049146c;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (*(int *)(in_ECX + 0x2fe8) == 0) {
    thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049b118,0xd8,s_mActive_0049b110);
  }
  if (0xf9 < param_1) {
    thunk_FUN_00414bc2(s_C__float_src_cache_cpp_0049b14c,0xdc,s_handle_<_MAX_CACHE_ITEMS_0049b130,
                       param_1);
  }
  if (*(char *)(in_ECX + 0x9c4 + (uint)param_1 * 0x1e) == '\0') {
    thunk_FUN_00414bc2(s_C__float_src_cache_cpp_0049b180,0xdd,s_mFilenames_handle__0_____0_0049b164,
                       param_1);
  }
  if (*(int *)(in_ECX + (uint)param_1 * 4) == 0) {
    thunk_FUN_0040f6f7();
    local_8 = 0;
    thunk_FUN_0040f752(in_ECX + 0x9c4 + (uint)param_1 * 0x1e,0x8000);
    iVar1 = thunk_FUN_0040f9af();
    uVar4 = iVar1 + 3U & 0xfffffffc;
    if (*(int *)(in_ECX + 0x2fe4) <= (int)uVar4) {
      thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049b1b0,0xec,s_cache_size_<_mCacheSize_0049b198);
    }
    uVar2 = thunk_FUN_0040ecd6(uVar4);
    *(undefined4 *)(in_ECX + (uint)param_1 * 4) = uVar2;
    *(uint *)(in_ECX + 1000 + (uint)param_1 * 4) = uVar4;
    iVar3 = thunk_FUN_0040fc15(*(undefined4 *)(in_ECX + (uint)param_1 * 4),iVar1);
    if (iVar3 != iVar1) {
      thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049b1e0,0xf2,s_loadstat____file_size_0049b1c8);
    }
    thunk_FUN_0040f966();
    *(ushort *)(in_ECX + 2000 + *(short *)(in_ECX + 0x2fdc) * 2) = param_1;
    *(short *)(in_ECX + 0x2fdc) = *(short *)(in_ECX + 0x2fdc) + 1;
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
  }
  else {
    for (local_12c = 0;
        (local_12c < *(short *)(in_ECX + 0x2fdc) &&
        (*(ushort *)(in_ECX + 2000 + local_12c * 2) != param_1)); local_12c = local_12c + 1) {
    }
    for (; local_12c < *(short *)(in_ECX + 0x2fdc); local_12c = local_12c + 1) {
      *(undefined2 *)(in_ECX + 2000 + local_12c * 2) =
           *(undefined2 *)(in_ECX + 0x7d2 + local_12c * 2);
    }
    *(ushort *)(in_ECX + 0x7ce + *(short *)(in_ECX + 0x2fdc) * 2) = param_1;
  }
  uVar2 = *(undefined4 *)(in_ECX + (uint)param_1 * 4);
  *unaff_FS_OFFSET = local_10;
  return uVar2;
}
```

---

---

## FUN_0040ebde — 0x40ebde

- Classification : internal
- Corps : `0x40ebde–0x40ec88`
- État : pseudocode obtenu
- Evidence : `ev_5348f17d6b4240b4628ed93c279f3ecc465bd40aae0e74feadb5810516109771`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x49b1f8` — "mActive"
- `0x49b200` — "C:\\float\\src\\cache.cpp"

### Pseudocode Ghidra

```c
undefined2 FUN_0040ebde(char *param_1)

{
  int iVar1;
  int in_ECX;
  int local_c;
  
  if (*(int *)(in_ECX + 0x2fe8) == 0) {
    thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049b200,0x114,s_mActive_0049b1f8);
  }
  local_c = 0;
  while( true ) {
    if (*(short *)(in_ECX + 0x2fda) <= local_c) {
      return 0xffff;
    }
    if ((*(char *)(in_ECX + 0x9c4 + local_c * 0x1e) != '\0') &&
       (iVar1 = __strcmpi(param_1,(char *)(in_ECX + 10000 + local_c * 9)), iVar1 == 0)) break;
    local_c = local_c + 1;
  }
  return (undefined2)local_c;
}
```

---

---

## FUN_0040ec89 — 0x40ec89

- Classification : internal
- Corps : `0x40ec89–0x40ecd5`
- État : pseudocode obtenu
- Evidence : `ev_a728302373cf570c2a9376ac9efe4a693d9be4f9f9de2ab9f2ace00f0ad0bde2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401acd` — `thunk_FUN_0040ebde`
- `0x401b4a` — `thunk_FUN_0040e864`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0040ec89(undefined4 param_1,int param_2)

{
  short sVar1;
  undefined4 uVar2;
  undefined2 extraout_var;
  
  sVar1 = thunk_FUN_0040ebde(param_1);
  if ((sVar1 == -1) && (param_2 == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = thunk_FUN_0040e864(CONCAT22(extraout_var,sVar1));
  }
  return uVar2;
}
```

---

---

## FUN_0040ecd6 — 0x40ecd6

- Classification : internal
- Corps : `0x40ecd6–0x40edba`
- État : pseudocode obtenu
- Evidence : `ev_a463bfe633cbe2998a696dc8a7ac3757bfb62ef6fc8ff9aec24c959adfa66774`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011ef` — `thunk_FUN_0040edbb`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49b218` — "num_dumps < mNumItems"
- `0x49b230` — "C:\\float\\src\\cache.cpp"

### Pseudocode Ghidra

```c
int FUN_0040ecd6(int param_1)

{
  int in_ECX;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = 0;
  for (local_14 = 0; local_14 < 0xfa; local_14 = local_14 + 1) {
    local_c = local_c + *(int *)(in_ECX + 1000 + local_14 * 4);
  }
  local_18 = *(int *)(in_ECX + 0x2fe0) + local_c;
  local_10 = *(int *)(in_ECX + 0x2fe4) - local_c;
  local_8 = 0;
  while (local_10 <= param_1) {
    if (*(short *)(in_ECX + 0x2fda) <= local_8) {
      thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049b230,0x147,s_num_dumps_<_mNumItems_0049b218);
    }
    local_10 = local_10 + *(int *)(in_ECX + 1000 + (uint)*(ushort *)(in_ECX + 2000) * 4);
    local_18 = thunk_FUN_0040edbb(*(undefined2 *)(in_ECX + 2000));
    local_8 = local_8 + 1;
  }
  return local_18;
}
```

---

---

## FUN_0040edbb — 0x40edbb

- Classification : internal
- Corps : `0x40edbb–0x40efaf`
- État : pseudocode obtenu
- Evidence : `ev_71bda5f71f78bbc941652791995478d99928454f2945a8165de203f095282c93`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x4734a0` — `FUN_004734a0`

### Chaînes référencées

- `0x49b248` — "handle < MAX_CACHE_ITEMS"
- `0x49b264` — "C:\\float\\src\\cache.cpp"

### Pseudocode Ghidra

```c
int FUN_0040edbb(ushort param_1)

{
  uint uVar1;
  int iVar2;
  int in_ECX;
  int local_14;
  int local_c;
  
  if (0xf9 < param_1) {
    thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049b264,0x158,s_handle_<_MAX_CACHE_ITEMS_0049b248);
  }
  if (*(int *)(in_ECX + (uint)param_1 * 4) == 0) {
    local_c = 0;
  }
  else {
    local_c = 0;
    for (local_14 = 0; local_14 < 0xfa; local_14 = local_14 + 1) {
      local_c = local_c + *(int *)(in_ECX + 1000 + local_14 * 4);
    }
    local_c = *(int *)(in_ECX + 0x2fe0) + local_c;
    uVar1 = *(uint *)(in_ECX + (uint)param_1 * 4);
    iVar2 = *(int *)(in_ECX + 1000 + (uint)param_1 * 4);
    FUN_004734a0(uVar1,uVar1 + iVar2,local_c - (uVar1 + iVar2));
    *(undefined4 *)(in_ECX + (uint)param_1 * 4) = 0;
    *(undefined4 *)(in_ECX + 1000 + (uint)param_1 * 4) = 0;
    for (local_14 = 0; local_14 < 0xfa; local_14 = local_14 + 1) {
      if (uVar1 < *(uint *)(in_ECX + local_14 * 4)) {
        *(int *)(in_ECX + local_14 * 4) = *(int *)(in_ECX + local_14 * 4) - iVar2;
      }
    }
    local_c = local_c - iVar2;
    *(short *)(in_ECX + 0x2fdc) = *(short *)(in_ECX + 0x2fdc) + -1;
    for (local_14 = 0;
        (local_14 < *(short *)(in_ECX + 0x2fdc) &&
        (*(ushort *)(in_ECX + 2000 + local_14 * 2) != param_1)); local_14 = local_14 + 1) {
    }
    for (; local_14 < *(short *)(in_ECX + 0x2fdc); local_14 = local_14 + 1) {
      *(undefined2 *)(in_ECX + 2000 + local_14 * 2) = *(undefined2 *)(in_ECX + 0x7d2 + local_14 * 2)
      ;
    }
  }
  return local_c;
}
```

---

---

## FUN_0040efb0 — 0x40efb0

- Classification : internal
- Corps : `0x40efb0–0x40f009`
- État : pseudocode obtenu
- Evidence : `ev_463de7fea0aef60c1e9c4b7edca71138e01379bf20b67c478003d6431d0ca57e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040efb0(void)

{
  int in_ECX;
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < *(short *)(in_ECX + 0x2fda); local_8 = local_8 + 1) {
    *(undefined4 *)(in_ECX + local_8 * 4) = 0;
    *(undefined4 *)(in_ECX + 1000 + local_8 * 4) = 0;
  }
  *(undefined2 *)(in_ECX + 0x2fdc) = 0;
  return;
}
```

---

---

## FUN_0040f00a — 0x40f00a

- Classification : internal
- Corps : `0x40f00a–0x40f029`
- État : pseudocode obtenu
- Evidence : `ev_f43cfb4ed75589d107b994f5e34841bffd7af2885e8b7847249748f442946557`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401db6` — `thunk_FUN_0040efb0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040f00a(void)

{
  int in_ECX;
  
  thunk_FUN_0040efb0();
  *(undefined4 *)(in_ECX + 0x2fe8) = 0;
  return;
}
```

---

---

## FUN_0040f02a — 0x40f02a

- Classification : internal
- Corps : `0x40f02a–0x40f041`
- État : pseudocode obtenu
- Evidence : `ev_3ed850d44478bccace4dd0a31fc9d5824d67ea50387f0e5c4d5498437f20c002`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040f02a(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x2fe8) = 1;
  return;
}
```

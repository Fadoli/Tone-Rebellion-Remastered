# 0007_batch_0003 — détails (3/3)

## FUN_0040d3e1 — 0x40d3e1

- Classification : internal
- Corps : `0x40d3e1–0x40d43c`
- État : pseudocode obtenu
- Evidence : `ev_e301167e29fb986c482605ac20e6fe87304050877b577a45d4bae3bb39c765d6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011e0` — `thunk_FUN_004500c4`
- `0x401bc7` — `thunk_FUN_004500b6`
- `0x401eab` — `thunk_FUN_0040bf98`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040d3e1(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined1 local_64 [4];
  undefined4 local_60;
  undefined4 local_58;
  int local_54;
  undefined4 local_50;
  
  if (param_3 != 0) {
    thunk_FUN_004500b6();
    local_60 = 0;
    local_58 = 2;
    thunk_FUN_004500c4();
    local_50 = param_2;
    local_54 = param_3;
    thunk_FUN_0040bf98(param_1,local_64,param_4,param_5,0,param_6,0xffffffff);
  }
  return;
}
```

---

## FUN_0040d43d — 0x40d43d

- Classification : internal
- Corps : `0x40d43d–0x40d48b`
- État : pseudocode obtenu
- Evidence : `ev_79cdac17259260ed5b1b1c1b0d6870adb51de716473ddd25881b4d55bb6c284c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401eab` — `thunk_FUN_0040bf98`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040d43d(undefined4 param_1,short *param_2)

{
  thunk_FUN_0040bf98(param_1,param_2,
                     (int)*param_2 - (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2),
                     (int)param_2[1],1,0x10000,0xffffffff);
  return;
}
```

---

## FUN_0040d48c — 0x40d48c

- Classification : internal
- Corps : `0x40d48c–0x40d5be`
- État : pseudocode obtenu
- Evidence : `ev_3ad72473706944ea541d20fd1f68160184e2e6d04630c3508c6de78791d9e315`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401acd` — `thunk_FUN_0040ebde`

### Chaînes référencées

- `0x49adb8` — "solidpad"
- `0x49adcc` — "bildtone"
- `0x49add8` — "tonecrys"
- `0x49ade4` — "magctone"
- `0x49adf0` — "triggers"
- `0x49adfc` — "spl19e"
- `0x49ae04` — "v-infect"
- `0x49ae10` — "crumble"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0040d48c(void)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 0x35; local_8 = local_8 + 1) {
    *(undefined1 **)(&DAT_004a9ee0 + local_8 * 4) = &LAB_00401a5f;
  }
  DAT_004a9fb4 = &LAB_00401780;
  DAT_004a9edc = &LAB_00401bb3;
  DAT_004a9ed8 = &LAB_0040187f;
  _DAT_004a9ee0 = thunk_FUN_0040ab42;
  _DAT_004a9ee4 = &LAB_00401fcd;
  _DAT_004a9ef4 = &LAB_004018ed;
  DAT_0049aca0 = thunk_FUN_0040ebde(s_solidpad_0049adb8);
  DAT_0049aca4 = thunk_FUN_0040ebde(&DAT_0049adc4);
  DAT_0049aca8 = thunk_FUN_0040ebde(s_bildtone_0049adcc);
  DAT_0049acac = thunk_FUN_0040ebde(s_tonecrys_0049add8);
  DAT_0049acb0 = thunk_FUN_0040ebde(s_magctone_0049ade4);
  DAT_0049acb4 = thunk_FUN_0040ebde(s_triggers_0049adf0);
  DAT_0049acb8 = thunk_FUN_0040ebde(s_spl19e_0049adfc);
  DAT_0049acbc = thunk_FUN_0040ebde(s_v_infect_0049ae04);
  DAT_0049acc0 = thunk_FUN_0040ebde(s_crumble_0049ae10);
  DAT_004a9fb8 = 1;
  return;
}
```

---

## FUN_0040d5bf — 0x40d5bf

- Classification : internal
- Corps : `0x40d5bf–0x40d65e`
- État : pseudocode obtenu
- Evidence : `ev_38027bdf8162e8bb8cfe85121e3a9903a286f65fe16a3da5f39af660c1270e99`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40149c` — `thunk_FUN_00414bc2`
- `0x40241e` — `thunk_FUN_0040d48c`

### Chaînes référencées

- `0x49ae1c` — "C:\\float\\src\\blddraw.cpp"

### Pseudocode Ghidra

```c
void FUN_0040d5bf(undefined4 param_1,int param_2)

{
  if (DAT_004a9fb8 == 0) {
    thunk_FUN_0040d48c();
  }
  switch(*(undefined4 *)(param_2 + 4)) {
  case 0:
    (**(code **)(&DAT_004a9ee0 + *(int *)(param_2 + 0x10) * 4))(param_1,param_2);
    break;
  case 1:
    (*DAT_004a9fb4)(param_1,param_2);
    break;
  case 2:
    (*DAT_004a9edc)(param_1,param_2);
    break;
  case 3:
    (*DAT_004a9ed8)(param_1,param_2);
    break;
  default:
    thunk_FUN_00414bc2(s_C__float_src_blddraw_cpp_0049ae1c,0x4f4,&DAT_0049ae18,
                       *(undefined4 *)(param_2 + 4));
  }
  return;
}
```

---

## FUN_0040e160 — 0x40e160

- Classification : internal
- Corps : `0x40e160–0x40e1ac`
- État : pseudocode obtenu
- Evidence : `ev_1a4e22301be9590748ca90a5af169a18cd2d5a144a211f261e0388e272e24561`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040e160(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x2fe0) = 0;
  *(undefined4 *)(in_ECX + 0x2fe4) = 0;
  *(undefined2 *)(in_ECX + 0x2fda) = 0;
  *(undefined2 *)(in_ECX + 0x2fdc) = 0;
  *(undefined4 *)(in_ECX + 0x2fe8) = 1;
  return in_ECX;
}
```

---

## FUN_0040e1ad — 0x40e1ad

- Classification : internal
- Corps : `0x40e1ad–0x40e1bf`
- État : pseudocode obtenu
- Evidence : `ev_4024a6e8a053b2a27e57f91c539bac90883433b40a914a84136c1b3b3388284e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40134d` — `thunk_FUN_0040e2a3`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040e1ad(void)

{
  thunk_FUN_0040e2a3();
  return;
}
```

---

## FUN_0040e1c0 — 0x40e1c0

- Classification : internal
- Corps : `0x40e1c0–0x40e2a2`
- État : pseudocode obtenu
- Evidence : `ev_a32fd68868ac92cfdde5e381c6e5748f74c282394bb53c282aa08cb11803e46c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x402176` — `thunk_FUN_00414bf7`

### Chaînes référencées

- `0x49ae88` — "mBaseptr != NULL"
- `0x49ae9c` — "C:\\float\\src\\cache.cpp"

### Pseudocode Ghidra

```c
void FUN_0040e1c0(int param_1)

{
  undefined4 uVar1;
  int in_ECX;
  uint uVar2;
  int local_8;
  
  uVar2 = param_1 + 3U & 0xfffffffc;
  uVar1 = thunk_FUN_00414bf7(uVar2);
  *(undefined4 *)(in_ECX + 0x2fe0) = uVar1;
  if (*(int *)(in_ECX + 0x2fe0) == 0) {
    thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049ae9c,0x2c,s_mBaseptr____NULL_0049ae88);
  }
  *(uint *)(in_ECX + 0x2fe4) = uVar2;
  *(undefined2 *)(in_ECX + 0x2fda) = 0;
  *(undefined2 *)(in_ECX + 0x2fdc) = 0;
  for (local_8 = 0; local_8 < 0xfa; local_8 = local_8 + 1) {
    *(undefined4 *)(in_ECX + local_8 * 4) = 0;
    *(undefined1 *)(in_ECX + 0x9c4 + local_8 * 0x1e) = 0;
    *(undefined1 *)(in_ECX + 10000 + local_8 * 9) = 0;
    *(undefined4 *)(in_ECX + 1000 + local_8 * 4) = 0;
  }
  return;
}
```

---

## FUN_0040e2a3 — 0x40e2a3

- Classification : internal
- Corps : `0x40e2a3–0x40e2e5`
- État : pseudocode obtenu
- Evidence : `ev_148e275c5664a063702d1e7c429f6079cfd578f44ce9ddb7d4e1cd24ee56da1f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401749` — `thunk_FUN_00414c97`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040e2a3(void)

{
  int in_ECX;
  
  if (*(int *)(in_ECX + 0x2fe0) != 0) {
    thunk_FUN_00414c97(*(undefined4 *)(in_ECX + 0x2fe0));
    *(undefined4 *)(in_ECX + 0x2fe0) = 0;
  }
  *(undefined4 *)(in_ECX + 0x2fe4) = 0;
  return;
}
```

---

## FUN_0040e2e6 — 0x40e2e6

- Classification : internal
- Corps : `0x40e2e6–0x40e510`
- État : pseudocode obtenu
- Evidence : `ev_a4d5c12fdfa9901acc784bd29ad3fb55d379485a8847c8a58bc3059ef0dc89e9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x49aeb4` — "mBaseptr != NULL"
- `0x49aec8` — "C:\\float\\src\\cache.cpp"
- `0x49aee0` — "len > 0"
- `0x49aee8` — "C:\\float\\src\\cache.cpp"
- `0x49af00` — "len < CACHE_FILENAME_LEN"
- `0x49af1c` — "C:\\float\\src\\cache.cpp"
- `0x49af34` — "idlen < CACHE_ID_LEN"
- `0x49af4c` — "C:\\float\\src\\cache.cpp"
- `0x49af64` — "mNumItems < MAX_CACHE_ITEMS"
- `0x49af80` — "C:\\float\\src\\cache.cpp"
- `0x49af98` — "Duplicate cache id: %s"

### Pseudocode Ghidra

```c
uint FUN_0040e2e6(char *param_1,char *param_2)

{
  size_t sVar1;
  size_t sVar2;
  int iVar3;
  int in_ECX;
  undefined4 uVar4;
  undefined4 uVar5;
  uint local_10;
  uint local_8;
  
  if (*(int *)(in_ECX + 0x2fe0) == 0) {
    thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049aec8,0x51,s_mBaseptr____NULL_0049aeb4);
  }
  local_8 = 0xffff;
  sVar1 = _strlen(param_1);
  sVar2 = _strlen(param_2);
  if ((int)sVar1 < 1) {
    thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049aee8,0x58,s_len_>_0_0049aee0);
  }
  if (0x1d < (int)sVar1) {
    thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049af1c,0x59,s_len_<_CACHE_FILENAME_LEN_0049af00);
  }
  if ((int)sVar2 < 9) {
    uVar5 = 0;
  }
  else {
    uVar5 = thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049af4c,0x5a,
                               s_idlen_<_CACHE_ID_LEN_0049af34);
  }
  if (*(short *)(in_ECX + 0x2fda) < 0xfa) {
    uVar4 = 0;
  }
  else {
    uVar4 = thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049af80,0x5b,
                               s_mNumItems_<_MAX_CACHE_ITEMS_0049af64);
  }
  local_10 = 0;
  do {
    if (0xf9 < (int)local_10) {
LAB_0040e499:
      if (local_8 != 0xffff) {
        FUN_00472da0(in_ECX + 0x9c4 + local_8 * 0x1e,param_1,uVar4,uVar5);
        FUN_00472da0(in_ECX + 10000 + local_8 * 9,param_2);
        *(short *)(in_ECX + 0x2fda) = *(short *)(in_ECX + 0x2fda) + 1;
      }
      return local_8;
    }
    if (((*(char *)(in_ECX + 0x9c4 + local_10 * 0x1e) != '\0') &&
        (*(char *)(in_ECX + 10000 + local_10 * 9) != '\0')) &&
       (iVar3 = __strcmpi((char *)(in_ECX + 10000 + local_10 * 9),param_2), iVar3 == 0)) {
      thunk_FUN_00414ad0(s_Duplicate_cache_id___s_0049af98,param_2);
      local_8 = 0xffff;
      goto LAB_0040e499;
    }
    if ((*(char *)(in_ECX + 0x9c4 + local_10 * 0x1e) == '\0') && (local_8 == 0xffff)) {
      local_8 = local_10 & 0xffff;
    }
    local_10 = local_10 + 1;
  } while( true );
}
```

---

## FUN_0040e511 — 0x40e511

- Classification : internal
- Corps : `0x40e511–0x40e6a8`
- État : pseudocode obtenu
- Evidence : `ev_c2646e86ecbe09eb06bfb01032704f9d2614cbaa85c754afe963441f5cd332d1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4017fd` — `thunk_FUN_0040e6a9`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x49afb0` — "mBaseptr != NULL"
- `0x49afc4` — "C:\\float\\src\\cache.cpp"
- `0x49afdc` — "len > 0"
- `0x49afe4` — "C:\\float\\src\\cache.cpp"
- `0x49affc` — "len < CACHE_FILENAME_LEN"
- `0x49b018` — "C:\\float\\src\\cache.cpp"
- `0x49b030` — "mNumItems < MAX_CACHE_ITEMS"
- `0x49b04c` — "C:\\float\\src\\cache.cpp"
- `0x49b064` — "item >=0 && item < MAX_CACHE_ITEMS"
- `0x49b088` — "C:\\float\\src\\cache.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0040e511(ushort param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  int in_ECX;
  undefined2 extraout_var;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if (*(int *)(in_ECX + 0x2fe0) == 0) {
    thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049afc4,0x78,s_mBaseptr____NULL_0049afb0);
  }
  sVar1 = _strlen(param_2);
  if ((int)sVar1 < 1) {
    thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049afe4,0x7c,s_len_>_0_0049afdc);
  }
  if ((int)sVar1 < 0x1e) {
    uVar5 = 0;
  }
  else {
    uVar5 = thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049b018,0x7d,
                               s_len_<_CACHE_FILENAME_LEN_0049affc);
  }
  if (*(short *)(in_ECX + 0x2fda) < 0xfa) {
    uVar4 = 0;
  }
  else {
    uVar4 = thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049b04c,0x7e,
                               s_mNumItems_<_MAX_CACHE_ITEMS_0049b030);
  }
  if (param_1 < 0xfa) {
    uVar3 = 0;
  }
  else {
    uVar3 = thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049b088,0x7f,
                               s_item_>_0____item_<_MAX_CACHE_ITE_0049b064);
  }
  if (*(char *)(in_ECX + 0x9c4 + (uint)param_1 * 0x1e) != '\0') {
    iVar2 = __strcmpi(param_2,(char *)(in_ECX + 0x9c4 + (uint)param_1 * 0x1e));
    if (iVar2 == 0) {
      return 1;
    }
    thunk_FUN_0040e6a9(CONCAT22(extraout_var,param_1));
  }
  FUN_00472da0(in_ECX + 0x9c4 + (uint)param_1 * 0x1e,param_2,uVar3,uVar4,uVar5);
  *(short *)(in_ECX + 0x2fda) = *(short *)(in_ECX + 0x2fda) + 1;
  return 1;
}
```

---

## FUN_0040e6a9 — 0x40e6a9

- Classification : internal
- Corps : `0x40e6a9–0x40e763`
- État : pseudocode obtenu
- Evidence : `ev_3bcc8cbc67ae9f8507c2945563dd81e2bb6132199b93d2b322852773a5ae5138`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011ef` — `thunk_FUN_0040edbb`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49b0a0` — "handle < MAX_CACHE_ITEMS"
- `0x49b0bc` — "C:\\float\\src\\cache.cpp"
- `0x49b0d4` — "mFilenames[handle][0] != 0"
- `0x49b0f0` — "C:\\float\\src\\cache.cpp"

### Pseudocode Ghidra

```c
void FUN_0040e6a9(ushort param_1)

{
  int in_ECX;
  
  if (0xf9 < param_1) {
    thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049b0bc,0x9e,s_handle_<_MAX_CACHE_ITEMS_0049b0a0);
  }
  if (*(char *)(in_ECX + 0x9c4 + (uint)param_1 * 0x1e) == '\0') {
    thunk_FUN_00414b64(s_C__float_src_cache_cpp_0049b0f0,0x9f,s_mFilenames_handle__0_____0_0049b0d4)
    ;
  }
  thunk_FUN_0040edbb(param_1);
  *(undefined1 *)(in_ECX + 0x9c4 + (uint)param_1 * 0x1e) = 0;
  *(short *)(in_ECX + 0x2fda) = *(short *)(in_ECX + 0x2fda) + -1;
  return;
}
```

---

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

# 0007_batch_0003 — détails (1/2)

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

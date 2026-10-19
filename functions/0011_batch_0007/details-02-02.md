# 0011_batch_0007 — détails (2/3)

## FUN_0042822b — 0x42822b

- Classification : internal
- Corps : `0x42822b–0x4282be`
- État : pseudocode obtenu
- Evidence : `ev_b4229d42dd41f3c5fdd3e44835793cad041459a76c6cdcee1c5d7ee52f113714`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40110e` — `thunk_FUN_00426fd0`
- `0x401a87` — `thunk_FUN_0042704b`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49d520` — "C:\\float\\src\\fltdraw.cpp"

### Pseudocode Ghidra

```c
void FUN_0042822b(undefined4 param_1,int param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 == 0) {
    thunk_FUN_00414b64(s_C__float_src_fltdraw_cpp_0049d520,0x1ba,&DAT_0049d51c);
  }
  iVar3 = (int)*(short *)(param_2 + 0x10) - (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
  sVar1 = *(short *)(param_2 + 0x12);
  iVar2 = thunk_FUN_00426fd0(param_2);
  if (iVar3 < 700) {
    thunk_FUN_0042704b(param_1,param_2,iVar3,sVar1 + iVar2,1,8,0x10000,0);
  }
  return;
}
```

---

---

## FUN_004282bf — 0x4282bf

- Classification : internal
- Corps : `0x4282bf–0x4282f8`
- État : pseudocode obtenu
- Evidence : `ev_f5fcae142471f5b2e5662a1f63ab31397c726411a7999a9c16e680c40939692d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004282bf(void)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
    *(undefined1 **)(&DAT_004c2ca0 + local_8 * 4) = &LAB_00401627;
  }
  DAT_004c2cb4 = 1;
  return;
}
```

---

---

## FUN_004282f9 — 0x4282f9

- Classification : internal
- Corps : `0x4282f9–0x428322`
- État : pseudocode obtenu
- Evidence : `ev_7bee3b46f2a506574fd7a2eed72aa88f4ebd83f2e16fe2ef817307a538f16fe8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401abe` — `thunk_FUN_004282bf`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004282f9(undefined4 param_1,int *param_2)

{
  if (DAT_004c2cb4 == 0) {
    thunk_FUN_004282bf();
  }
  (**(code **)(&DAT_004c2ca0 + *param_2 * 4))(param_1,param_2);
  return;
}
```

---

---

## FUN_00428800 — 0x428800

- Classification : internal
- Corps : `0x428800–0x428883`
- État : pseudocode obtenu
- Evidence : `ev_e824abcf343d7768146af3913ccca58952807bea96ec700f01ab05366e006c9f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00428800(void)

{
  undefined4 *in_ECX;
  int local_8;
  
  if (DAT_004c2ec0 == 0) {
    DAT_004c2dbf = 0xff;
    for (local_8 = 0; local_8 < 0x100; local_8 = local_8 + 1) {
      (&DAT_004c2dc0)[local_8] = (undefined1)local_8;
    }
    DAT_004c2ec0 = 1;
  }
  *in_ECX = 0;
  in_ECX[1] = 0;
  in_ECX[2] = 0xffffffff;
  in_ECX[3] = 3;
  in_ECX[4] = 0;
  return in_ECX;
}
```

---

---

## FUN_00428884 — 0x428884

- Classification : internal
- Corps : `0x428884–0x42892c`
- État : pseudocode obtenu
- Evidence : `ev_62d8b921775b33793b4b8683fb72f17353b1cf54d782b26b0a8d3881d5e263d0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x401749` — `thunk_FUN_00414c97`
- `0x4017f3` — `thunk_FUN_0040fb84`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401eba` — `thunk_FUN_0040f752`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00428884(undefined4 param_1)

{
  int iVar1;
  int *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049160c;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (*in_ECX != 0) {
    thunk_FUN_00414c97(*in_ECX);
    *in_ECX = 0;
  }
  thunk_FUN_0040f6f7();
  local_8 = 0;
  thunk_FUN_0040f752(param_1,0x8000);
  iVar1 = thunk_FUN_0040fb84(0);
  *in_ECX = iVar1;
  local_8 = 0xffffffff;
  thunk_FUN_0040f73f();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

---

## FUN_0042892d — 0x42892d

- Classification : internal
- Corps : `0x42892d–0x4289a6`
- État : pseudocode obtenu
- Evidence : `ev_058e7cccfcc8f22bdbb7a363c4b82bc46a45a9cd6d91d8b0bdaa8133bacfbea0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401974` — `thunk_FUN_00408287`
- `0x472e90` — `_strlen`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0042892d(char *param_1,int param_2,int param_3)

{
  size_t sVar1;
  int iVar2;
  undefined4 *in_ECX;
  int local_c;
  int local_8;
  
  if (param_2 == -1) {
    param_2 = 0;
  }
  if (param_3 == -1) {
    sVar1 = _strlen(param_1);
    param_3 = sVar1 - 1;
  }
  local_8 = 0;
  for (local_c = param_2; local_c <= param_3; local_c = local_c + 1) {
    iVar2 = thunk_FUN_00408287(*in_ECX,param_1[local_c]);
    local_8 = local_8 + iVar2;
  }
  return local_8;
}
```

---

---

## FUN_004289a7 — 0x4289a7

- Classification : internal
- Corps : `0x4289a7–0x4289bf`
- État : pseudocode obtenu
- Evidence : `ev_1eb850d08499e460e387a0ce0794bd470f0fc6584b29fe8a329a33e0d2f8eb98`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401523` — `thunk_FUN_00408274`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004289a7(void)

{
  undefined4 *in_ECX;
  
  thunk_FUN_00408274(*in_ECX);
  return;
}
```

---

---

## FUN_004289c0 — 0x4289c0

- Classification : internal
- Corps : `0x4289c0–0x4289eb`
- État : pseudocode obtenu
- Evidence : `ev_b450008741a2d0bbef5d7ca9a9af52a90961e5ef685add7eaf6fb885b4c99290`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401294` — `thunk_FUN_004289ec`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004289c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int in_ECX;
  
  thunk_FUN_004289ec(param_1,param_2,param_3,param_4,*(undefined4 *)(in_ECX + 0x10));
  return;
}
```

---

---

## FUN_004289ec — 0x4289ec

- Classification : internal
- Corps : `0x4289ec–0x428ba9`
- État : pseudocode obtenu
- Evidence : `ev_af4527d762caf118766ab1ee0e25ab1ab9e5c8accc75e7ff253c646edfb319fb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401280` — `thunk_FUN_0040843a`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x401523` — `thunk_FUN_00408274`
- `0x401974` — `thunk_FUN_00408287`
- `0x401e79` — `thunk_FUN_004082a7`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x402234` — `thunk_FUN_0042892d`
- `0x472e90` — `_strlen`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x49d574` — "mShape"
- `0x49d57c` — "C:\\float\\src\\font.cpp"

### Pseudocode Ghidra

```c
void FUN_004289ec(int *param_1,int param_2,int param_3,char *param_4,uint param_5)

{
  size_t sVar1;
  int *in_ECX;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int local_30;
  int local_24 [4];
  int local_14;
  int local_10;
  int local_c;
  undefined *local_8;
  
  if (*in_ECX == 0) {
    thunk_FUN_00414b64(s_C__float_src_font_cpp_0049d57c,0x60,s_mShape_0049d574);
  }
  local_8 = &DAT_004c2dc0;
  if (in_ECX[2] != -1) {
    local_8 = &DAT_004c2cc0;
    _memset(&DAT_004c2cc1,in_ECX[2],0xfe);
  }
  local_10 = thunk_FUN_00408274(*in_ECX);
  if ((param_5 & 1) == 0) {
    local_c = thunk_FUN_0042892d(param_4,0xffffffff,0xffffffff);
  }
  else {
    sVar1 = _strlen(param_4);
    local_c = thunk_FUN_00408287(*in_ECX,0x43);
    local_c = sVar1 * local_c;
  }
  piVar3 = param_1;
  piVar4 = local_24;
  for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar4 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar4 = piVar4 + 1;
  }
  local_24[1] = param_2;
  local_24[2] = param_3;
  local_24[3] = param_2 + local_c;
  local_14 = param_3 + local_10;
  if ((param_5 & 2) != 0) {
    thunk_FUN_00406604(local_24,in_ECX[1]);
  }
  if ((param_5 & 1) == 0) {
    if (*param_4 != '\0') {
      thunk_FUN_0040843a(param_1,param_2,param_3,*in_ECX,param_4,local_8);
    }
  }
  else {
    iVar2 = thunk_FUN_00408287(*in_ECX,0x43);
    local_30 = param_2;
    for (; *param_4 != '\0'; param_4 = param_4 + 1) {
      thunk_FUN_004082a7(param_1,local_30,param_3,*in_ECX,(int)*param_4,local_8);
      local_30 = local_30 + iVar2;
    }
  }
  if ((param_5 & 8) != 0) {
    thunk_FUN_0042d87c(local_24,(char)in_ECX[3]);
  }
  return;
}
```

---

---

## FUN_00428baa — 0x428baa

- Classification : internal
- Corps : `0x428baa–0x428fea`
- État : pseudocode obtenu
- Evidence : `ev_070bb8f7f12c4075d07ababe01d163146f4b42bd9713ada666333c335146cb96`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402234` — `thunk_FUN_0042892d`
- `0x472e90` — `_strlen`
- `0x4737e0` — `_strncpy`
- `0x4773b0` — `FUN_004773b0`

### Chaînes référencées

- `0x49d594` — "num_spaces<MAX_SPACES"
- `0x49d5ac` — "C:\\float\\src\\font.cpp"
- `0x49d5c4` — "num_spaces<MAX_SPACES"
- `0x49d5dc` — "C:\\float\\src\\font.cpp"
- `0x49d5f4` — "endspace>=0"
- `0x49d600` — "C:\\float\\src\\font.cpp"

### Pseudocode Ghidra

```c
void FUN_00428baa(int param_1,int param_2,undefined4 param_3,char *param_4,int param_5,code *param_6
                 )

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_548;
  int local_540;
  int local_53c;
  char *local_534;
  undefined1 local_528 [4];
  undefined4 local_524;
  char local_520 [256];
  int local_420;
  size_t local_41c;
  int local_418;
  int local_414;
  int local_410;
  int aiStack_40c [256];
  int local_c;
  int local_8;
  
  if (((param_6 == (code *)0x0) || (param_4 == (char *)0x0)) || (param_1 == 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    local_410 = param_2;
    local_524 = param_3;
    local_41c = _strlen(param_4);
    local_8 = 0;
    for (local_418 = 0; local_418 < (int)local_41c; local_418 = local_418 + 1) {
      if (param_4[local_418] == ' ') {
        if (0xff < local_8) {
          thunk_FUN_00414b64(s_C__float_src_font_cpp_0049d5ac,0xa9,s_num_spaces<MAX_SPACES_0049d594)
          ;
        }
        aiStack_40c[local_8] = local_418;
        local_8 = local_8 + 1;
      }
    }
    if (0xff < local_8) {
      thunk_FUN_00414b64(s_C__float_src_font_cpp_0049d5dc,0xad,s_num_spaces<MAX_SPACES_0049d5c4);
    }
    aiStack_40c[local_8] = local_418;
    local_8 = local_8 + 1;
    local_c = 0;
    while (local_c < (int)local_41c) {
      (*param_6)(local_410,local_524,&local_410,&local_524,&local_414,local_528);
      iVar4 = local_414 - local_410;
      local_420 = local_8 + -1;
      while (iVar2 = thunk_FUN_0042892d(param_4,local_c,aiStack_40c[local_420] + -1), iVar4 < iVar2)
      {
        local_420 = local_420 + -1;
        if (local_420 < 0) {
          thunk_FUN_00414b64(s_C__float_src_font_cpp_0049d600,0xc0,s_endspace>_0_0049d5f4);
        }
      }
      _strncpy(local_520,param_4 + local_c,aiStack_40c[local_420] - local_c);
      local_520[aiStack_40c[local_420] - local_c] = '\0';
      if (param_5 == 0) {
        thunk_FUN_004289c0(param_1,local_410,local_524,local_520);
      }
      else {
        local_53c = 0;
        for (local_534 = local_520; *local_534 != '\0'; local_534 = local_534 + 1) {
          if (*local_534 == ' ') {
            local_53c = local_53c + 1;
          }
        }
        if (local_53c == 0) {
          local_53c = 1;
        }
        iVar2 = thunk_FUN_0042892d(local_520,0xffffffff,0xffffffff);
        iVar4 = iVar4 - iVar2;
        iVar2 = iVar4 / local_53c;
        local_548 = local_410;
        local_534 = (char *)FUN_004773b0(local_520,&DAT_0049d618);
        local_540 = iVar4 - iVar2 * local_53c;
        while (local_534 != (char *)0x0) {
          iVar4 = thunk_FUN_0042892d(local_534,0xffffffff,0xffffffff);
          iVar3 = thunk_FUN_0042892d(&DAT_0049d61c,0xffffffff,0xffffffff);
          thunk_FUN_004289c0(param_1,local_548,local_524,local_534);
          local_548 = local_548 + iVar4 + iVar3 + iVar2;
          if (local_540 != 0) {
            local_548 = local_548 + 1;
          }
          local_534 = (char *)FUN_004773b0(0,&DAT_0049d620);
          local_540 = local_540 + -1;
        }
      }
      local_c = aiStack_40c[local_420] + 1;
    }
  }
  return;
}
```

---

---

## FUN_004291f0 — 0x4291f0

- Classification : internal
- Corps : `0x4291f0–0x4291f9`
- État : pseudocode obtenu
- Evidence : `ev_3f3f365243a48c6fca5f88c191292e2bb970aaf4fe0a415d4c2355f54b03f72e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4291fa` — `FUN_004291fa`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004291f0(void)

{
  FUN_004291fa();
  return;
}
```

---

---

## FUN_004291fa — 0x4291fa

- Classification : internal
- Corps : `0x4291fa–0x429208`
- État : pseudocode obtenu
- Evidence : `ev_b0f3e5c9726e5319cafea1c2f3c7888fd1fa047d6fcc3b45e611d50797c568af`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4020cc` — `thunk_FUN_00428800`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004291fa(void)

{
  thunk_FUN_00428800();
  return;
}
```

---

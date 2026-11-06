# 0008_batch_0004 — détails (1/3)

## FUN_0040f400 — 0x40f400

- Classification : internal
- Corps : `0x40f400–0x40f409`
- État : pseudocode obtenu
- Evidence : `ev_59292393e219569b483000d57a0b825c1151769d560561abb0f6d038b713c0e3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40f40a` — `FUN_0040f40a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040f400(void)

{
  FUN_0040f40a();
  return;
}
```

---

---

## FUN_0040f40a — 0x40f40a

- Classification : internal
- Corps : `0x40f40a–0x40f418`
- État : pseudocode obtenu
- Evidence : `ev_2e7408f488609c4254a0e4813280a745fc9807b484c57ac5eb1d363ec469ffb4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40142e` — `thunk_FUN_004104c0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040f40a(void)

{
  thunk_FUN_004104c0();
  return;
}
```

---

---

## FUN_0040f419 — 0x40f419

- Classification : internal
- Corps : `0x40f419–0x40f511`
- État : pseudocode obtenu
- Evidence : `ev_f2aaf6dc9f43acefcf3cfa30722df6d60c3f30d302c321fa1ac8258d2174a0a7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x40150a` — `thunk_FUN_0040f9af`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401eba` — `thunk_FUN_0040f752`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040f419(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049148c;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0040f6f7();
  local_8 = 0;
  local_14 = thunk_FUN_0040f752(param_1,0x4000);
  if (local_14 == 0) {
    iVar1 = thunk_FUN_0040f9af();
    if (iVar1 < param_3) {
      iVar1 = thunk_FUN_0040fc15(param_2,iVar1);
      in_ECX[2] = iVar1;
      *in_ECX = param_2;
      in_ECX[1] = *in_ECX;
      *(undefined1 *)(*in_ECX + in_ECX[2]) = 0;
    }
    else {
      local_14 = -1;
    }
  }
  local_8 = 0xffffffff;
  thunk_FUN_0040f73f();
  *unaff_FS_OFFSET = local_10;
  return local_14;
}
```

---

---

## FUN_0040f512 — 0x40f512

- Classification : internal
- Corps : `0x40f512–0x40f5b2`
- État : pseudocode obtenu
- Evidence : `ev_e365a747229874a24a786fc747500af932432feedaa3e6d0d1e473bb99484f11`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4737e0` — `_strncpy`
- `0x4738f0` — `_strchr`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0040f512(char *param_1)

{
  undefined4 uVar1;
  int *in_ECX;
  char *local_8;
  
  if ((*in_ECX == 0) || ((uint)(*in_ECX + in_ECX[2]) <= (uint)in_ECX[1])) {
    uVar1 = 0xffffffff;
  }
  else {
    local_8 = _strchr((char *)in_ECX[1],10);
    if (local_8 == (char *)0x0) {
      local_8 = (char *)(in_ECX[2] - (in_ECX[1] - *in_ECX));
    }
    else {
      local_8 = local_8 + (1 - in_ECX[1]);
    }
    _strncpy(param_1,(char *)in_ECX[1],(size_t)local_8);
    param_1[(int)local_8] = '\0';
    in_ECX[1] = (int)(local_8 + in_ECX[1]);
    uVar1 = 0;
  }
  return uVar1;
}
```

---

---

## FUN_0040f5b3 — 0x40f5b3

- Classification : internal
- Corps : `0x40f5b3–0x40f6f6`
- État : pseudocode obtenu
- Evidence : `ev_9a43dae9087123005e9f536b7788da9b702d57a3b6b013e2b713164b23dab33f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40128a` — `thunk_FUN_0040f512`
- `0x472e90` — `_strlen`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040f5b3(char *param_1,int param_2)

{
  bool bVar1;
  size_t sVar2;
  char *local_18;
  char *local_14;
  int local_8;
  
  local_8 = -1;
  bVar1 = false;
  do {
    do {
      if ((bVar1) || (local_8 = thunk_FUN_0040f512(param_1), local_8 == -1)) {
        if ((bVar1) && (param_2 != 0)) {
          sVar2 = _strlen(param_1);
          for (local_18 = param_1 + (sVar2 - 1); *local_18 < '!'; local_18 = local_18 + -1) {
            *local_18 = '\0';
          }
        }
        return local_8;
      }
      for (local_14 = param_1; *local_14 != '\0'; local_14 = local_14 + 1) {
        if (((*local_14 != ' ') && (*local_14 != '\t')) && (*local_14 != '\n')) {
          if ((*local_14 != ';') && ((*local_14 != '/' || (local_14[1] != '/')))) {
            bVar1 = true;
          }
          break;
        }
      }
    } while (!bVar1);
    for (; *local_14 != '\0'; local_14 = local_14 + 1) {
      if ((*local_14 == ';') || ((*local_14 == '/' && (local_14[1] == '/')))) {
        *local_14 = '\0';
        break;
      }
    }
  } while( true );
}
```

---

---

## FUN_0040f6f7 — 0x40f6f7

- Classification : internal
- Corps : `0x40f6f7–0x40f73e`
- État : pseudocode obtenu
- Evidence : `ev_f100207dddc9e8fd8a5d1c9fdfabf68852e7feef8fd4dbfc01cb4e94c03a1d8a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40154b` — `thunk_FUN_00410105`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0040f6f7(void)

{
  undefined4 *in_ECX;
  
  if (DAT_004b0a94 == 0) {
    thunk_FUN_00410105();
    DAT_004b0a94 = 1;
  }
  *in_ECX = 0xffffffff;
  *(undefined1 *)(in_ECX + 1) = 0;
  in_ECX[0x42] = 0xffffffff;
  return in_ECX;
}
```

---

---

## FUN_0040f73f — 0x40f73f

- Classification : internal
- Corps : `0x40f73f–0x40f751`
- État : pseudocode obtenu
- Evidence : `ev_24054806d828a010a5b6bff5fc59e56849b4ea3d616731a1f02a7fff82398f10`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401d25` — `thunk_FUN_0040f966`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040f73f(void)

{
  thunk_FUN_0040f966();
  return;
}
```

---

---

## FUN_0040f752 — 0x40f752

- Classification : internal
- Corps : `0x40f752–0x40f7a4`
- État : pseudocode obtenu
- Evidence : `ev_a904d7914a07214d5a02d49e6d1e547b3bc233f78d42c9b2ca4127fdd0464f6f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401d25` — `thunk_FUN_0040f966`
- `0x402315` — `thunk_FUN_0040f7c3`
- `0x4737e0` — `_strncpy`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0040f752(char *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int *in_ECX;
  
  if (*in_ECX != -1) {
    thunk_FUN_0040f966();
  }
  _strncpy((char *)(in_ECX + 1),param_1,0x100);
  *(undefined1 *)((int)in_ECX + 0x103) = 0;
  uVar1 = thunk_FUN_0040f7c3(param_2);
  return uVar1;
}
```

---

---

## FUN_0040f7a5 — 0x40f7a5

- Classification : internal
- Corps : `0x40f7a5–0x40f7c2`
- État : pseudocode obtenu
- Evidence : `ev_08c77df3e6e1aabcd299150e114fcdb149f703062dddd6d3933c58733eb22f23`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401eba` — `thunk_FUN_0040f752`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040f7a5(undefined4 param_1)

{
  thunk_FUN_0040f752(param_1,0x8101);
  return;
}
```

---

---

## FUN_0040f7c3 — 0x40f7c3

- Classification : internal
- Corps : `0x40f7c3–0x40f965`
- État : pseudocode obtenu
- Evidence : `ev_067e150ea2e6f0bf6f48a067f0f2a131db44a7553b9821e2f0ac9302c87fe0de`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401d25` — `thunk_FUN_0040f966`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4739b0` — `FUN_004739b0`
- `0x473aa0` — `FID_conflict:__open`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x49b348` — "mFileHandle != -1"
- `0x49b35c` — "C:\\float\\src\\cfile.cpp"

### Pseudocode Ghidra

```c
bool FUN_0040f7c3(uint param_1)

{
  bool bVar1;
  int iVar2;
  int *in_ECX;
  undefined4 uVar3;
  int local_14;
  int local_10;
  int local_c;
  
  if (*in_ECX != -1) {
    thunk_FUN_0040f966();
  }
  if ((param_1 & 0x100) == 0) {
    bVar1 = false;
    in_ECX[0x42] = -1;
    if ((param_1 & 3) == 0) {
      local_10 = 0;
      local_c = 0;
      for (local_14 = 0; local_14 < DAT_004b0968; local_14 = local_14 + 1) {
        if (local_c == *(int *)(&DAT_004b096c + local_10 * 4)) {
          local_10 = local_10 + 1;
          local_c = 0;
        }
        iVar2 = __strcmpi((char *)(in_ECX + 1),&DAT_004a9ff0 + local_14 * 0x32);
        if (iVar2 == 0) {
          in_ECX[0x42] = local_14;
          iVar2 = FID_conflict___open(&DAT_004b0980 + local_10 * 0x32,param_1);
          *in_ECX = iVar2;
          if (*in_ECX == -1) {
            uVar3 = thunk_FUN_00414b64(s_C__float_src_cfile_cpp_0049b35c,0x107,
                                       s_mFileHandle_____1_0049b348);
          }
          else {
            uVar3 = 0;
          }
          FUN_004739b0(*in_ECX,*(undefined4 *)(&DAT_004b0198 + local_14 * 4),0,uVar3);
          bVar1 = true;
          break;
        }
        local_c = local_c + 1;
      }
    }
    if (!bVar1) {
      iVar2 = FID_conflict___open((char *)(in_ECX + 1),param_1);
      *in_ECX = iVar2;
    }
  }
  else {
    param_1 = param_1 | 0x200;
    iVar2 = FID_conflict___open((char *)(in_ECX + 1),param_1,0x180);
    *in_ECX = iVar2;
  }
  in_ECX[0x41] = param_1;
  return *in_ECX == -1;
}
```

---

---

## FUN_0040f966 — 0x40f966

- Classification : internal
- Corps : `0x40f966–0x40f9ae`
- État : pseudocode obtenu
- Evidence : `ev_82e6edc8a611f3ee24068fa4765168ce40feb82dc165a5219c65648f7d815476`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x473fe0` — `FUN_00473fe0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040f966(void)

{
  int iVar1;
  int *in_ECX;
  
  if (*in_ECX == -1) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_00473fe0(*in_ECX);
    if (iVar1 == 0) {
      *in_ECX = -1;
      in_ECX[0x42] = -1;
    }
  }
  return iVar1;
}
```

---

---

## FUN_0040f9af — 0x40f9af

- Classification : internal
- Corps : `0x40f9af–0x40fa7e`
- État : pseudocode obtenu
- Evidence : `ev_7c60fc6bc9ceee3c02f59b06c54a2975170215d597cfa75a64c3a3efc0295f0d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4740d0` — `FUN_004740d0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040f9af(void)

{
  int *in_ECX;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (*in_ECX == -1) {
    local_8 = -1;
  }
  else if (in_ECX[0x42] == -1) {
    local_8 = FUN_004740d0(*in_ECX);
  }
  else {
    local_14 = *(int *)(&DAT_004b019c + in_ECX[0x42] * 4);
    local_c = 0;
    for (local_10 = 0; local_10 < DAT_004b0a90; local_10 = local_10 + 1) {
      local_c = local_c + *(int *)(&DAT_004b096c + local_10 * 4);
      if (in_ECX[0x42] == local_c + -1) {
        local_14 = *(int *)(&DAT_004b0a7c + local_10 * 4);
      }
    }
    local_8 = local_14 - *(int *)(&DAT_004b0198 + in_ECX[0x42] * 4);
  }
  return local_8;
}
```

---

---

## FUN_0040fa7f — 0x40fa7f

- Classification : internal
- Corps : `0x40fa7f–0x40fac7`
- État : pseudocode obtenu
- Evidence : `ev_0b5c0febde603b8f0a96024ded6e6ac9a4eef333c550890914a64ffeaafdf098`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474170` — `FUN_00474170`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040fa7f(void)

{
  undefined4 *in_ECX;
  int local_8;
  
  local_8 = FUN_00474170(*in_ECX);
  if ((local_8 != -1) && (in_ECX[0x42] != -1)) {
    local_8 = local_8 - *(int *)(&DAT_004b0198 + in_ECX[0x42] * 4);
  }
  return local_8;
}
```

---

---

## FUN_0040fac8 — 0x40fac8

- Classification : internal
- Corps : `0x40fac8–0x40fb32`
- État : pseudocode obtenu
- Evidence : `ev_c9055c14dec9e06847683060055f50e2226f0b2fb8bc5c5e8903a686e128228b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40150a` — `thunk_FUN_0040f9af`
- `0x4739b0` — `FUN_004739b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0040fac8(int param_1)

{
  int iVar1;
  undefined4 *in_ECX;
  int local_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  if (-1 < param_1) {
    iVar1 = thunk_FUN_0040f9af();
    if (param_1 < iVar1) {
      local_c = param_1;
      if (in_ECX[0x42] != -1) {
        local_c = *(int *)(&DAT_004b0198 + in_ECX[0x42] * 4) + param_1;
      }
      local_8 = FUN_004739b0(*in_ECX,local_c,0);
    }
  }
  return local_8;
}
```

---

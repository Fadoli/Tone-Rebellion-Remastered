# 0008_batch_0004 — détails (1/2)

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

## FUN_0040fb33 — 0x40fb33

- Classification : internal
- Corps : `0x40fb33–0x40fb83`
- État : pseudocode obtenu
- Evidence : `ev_1c5591eb84b3cb57917db9fb5f9dd245e27189422959da810a17fd27c46a21fc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40150a` — `thunk_FUN_0040f9af`
- `0x401b9f` — `thunk_FUN_0040fa7f`
- `0x4739b0` — `FUN_004739b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0040fb33(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *in_ECX;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  iVar1 = thunk_FUN_0040fa7f();
  if (-1 < iVar1 + param_1) {
    iVar2 = thunk_FUN_0040f9af();
    if (iVar1 + param_1 < iVar2) {
      local_8 = FUN_004739b0(*in_ECX,param_1,1);
    }
  }
  return local_8;
}
```

---

## FUN_0040fb84 — 0x40fb84

- Classification : internal
- Corps : `0x40fb84–0x40fc14`
- État : pseudocode obtenu
- Evidence : `ev_12611b8dae36eb63b8693c36cd2fa718f9ffd610e979b843b49b9591d6254e67`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40150a` — `thunk_FUN_0040f9af`
- `0x401749` — `thunk_FUN_00414c97`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x402176` — `thunk_FUN_00414bf7`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040fb84(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int *in_ECX;
  
  if (*in_ECX == -1) {
    param_1 = 0;
  }
  else {
    iVar2 = thunk_FUN_0040f9af();
    bVar1 = false;
    if (iVar2 < 1) {
      param_1 = 0;
    }
    else {
      if (param_1 == 0) {
        param_1 = thunk_FUN_00414bf7(iVar2);
        if (param_1 == 0) {
          return 0;
        }
        bVar1 = true;
      }
      iVar3 = thunk_FUN_0040fc15(param_1,iVar2);
      if (iVar3 != iVar2) {
        if (bVar1) {
          thunk_FUN_00414c97(param_1);
        }
        param_1 = 0;
      }
    }
  }
  return param_1;
}
```

---

## FUN_0040fc15 — 0x40fc15

- Classification : internal
- Corps : `0x40fc15–0x40fc6f`
- État : pseudocode obtenu
- Evidence : `ev_6687075565018f38b98755e584d6391126d5b9d63f931a6c8820a6ec50e43223`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40150a` — `thunk_FUN_0040f9af`
- `0x401b9f` — `thunk_FUN_0040fa7f`
- `0x474190` — `FUN_00474190`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040fc15(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 *in_ECX;
  
  if (in_ECX[0x42] != -1) {
    iVar1 = thunk_FUN_0040fa7f();
    uVar2 = thunk_FUN_0040f9af();
    if (uVar2 < (uint)(iVar1 + param_2)) {
      param_2 = uVar2 - iVar1;
    }
  }
  FUN_00474190(*in_ECX,param_1,param_2);
  return;
}
```

---

## FUN_0040fc70 — 0x40fc70

- Classification : internal
- Corps : `0x40fc70–0x40fd7f`
- État : pseudocode obtenu
- Evidence : `ev_2489f3357d076d8dd3550a91f98f0490562e1fedd892ce3fb1dbd2cf59328840`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401875` — `thunk_FUN_0040fc15`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040fc70(int param_1,uint param_2,uint param_3,code *param_4)

{
  uint uVar1;
  int iVar2;
  uint local_18;
  int local_14;
  uint local_c;
  
  local_14 = 0;
  local_c = 0;
  while( true ) {
    if (param_3 - 1 <= local_c) {
      iVar2 = thunk_FUN_0040fc15(param_1,param_2 - local_14);
      if (iVar2 == -1) {
        local_14 = -1;
      }
      else {
        local_14 = local_14 + iVar2;
        (*param_4)(param_3,local_c,param_1);
      }
      return local_14;
    }
    uVar1 = thunk_FUN_0040fc15(param_1,param_2 / param_3);
    if (uVar1 == 0xffffffff) break;
    local_14 = local_14 + uVar1;
    if (uVar1 < param_2 / param_3) {
      for (local_18 = local_c; local_18 < param_3; local_18 = local_18 + 1) {
        (*param_4)(param_3,local_18,0);
      }
      return local_14;
    }
    (*param_4)(param_3,local_c,param_1);
    param_1 = param_1 + uVar1;
    local_c = local_c + 1;
  }
  return -1;
}
```

---

## FUN_0040fd80 — 0x40fd80

- Classification : internal
- Corps : `0x40fd80–0x40fdaa`
- État : pseudocode obtenu
- Evidence : `ev_643c7d6ef7ceeceb23f1f32e1f046b2071ec8fb85a53dc0b4c459bc34c5069a2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4745f0` — `FUN_004745f0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0040fd80(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *in_ECX;
  
  uVar1 = FUN_004745f0(*in_ECX,param_1,param_2);
  return uVar1;
}
```

---

## FUN_0040fdab — 0x40fdab

- Classification : internal
- Corps : `0x40fdab–0x40fdc8`
- État : pseudocode obtenu
- Evidence : `ev_f392cde64729db8b4734f762228cd7b2bcdb4c5294b69f0ca4e5d64c4775f3c4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401875` — `thunk_FUN_0040fc15`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0040fdab(void)

{
  undefined4 local_8;
  
  thunk_FUN_0040fc15(&local_8,4);
  return local_8;
}
```

---

## FUN_0040fdc9 — 0x40fdc9

- Classification : internal
- Corps : `0x40fdc9–0x40fe9e`
- État : pseudocode obtenu
- Evidence : `ev_f9513f5bad1a27316d3bb0d265a57dc41a851de5ee16b1cfbdaeb7e15c8287ee`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40150a` — `thunk_FUN_0040f9af`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401b9f` — `thunk_FUN_0040fa7f`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49b374` — "mFileAccess & O_TEXT"
- `0x49b38c` — "C:\\float\\src\\cfile.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0040fdc9(int param_1)

{
  uint uVar1;
  int *in_ECX;
  undefined4 uVar2;
  uint local_18;
  int local_14;
  char local_c [4];
  undefined4 local_8;
  
  if ((in_ECX[0x41] & 0x4000U) == 0) {
    uVar2 = thunk_FUN_00414b64(s_C__float_src_cfile_cpp_0049b38c,0x288,
                               s_mFileAccess___O_TEXT_0049b374);
  }
  else {
    uVar2 = 0;
  }
  if (*in_ECX == -1) {
    local_8 = 0xffffffff;
  }
  else {
    local_c[0] = '\0';
    local_14 = 0;
    uVar1 = thunk_FUN_0040f9af(uVar2);
    local_18 = thunk_FUN_0040fa7f();
    local_8 = 0xffffffff;
    if (local_18 < uVar1) {
      local_8 = 0;
    }
    while ((local_18 < uVar1 && (local_c[0] != '\n'))) {
      thunk_FUN_0040fc15(local_c,1);
      *(char *)(param_1 + local_14) = local_c[0];
      local_14 = local_14 + 1;
      local_18 = local_18 + 1;
    }
    *(undefined1 *)(param_1 + local_14) = 0;
  }
  return local_8;
}
```

---

## FUN_0040fe9f — 0x40fe9f

- Classification : internal
- Corps : `0x40fe9f–0x40ff5a`
- État : pseudocode obtenu
- Evidence : `ev_311162cce4fc52471f26550d0c85983cb52da0cb4fdcfcbbae523ff8e6f6093a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4017e4` — `thunk_FUN_0040fdc9`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040fe9f(char *param_1)

{
  bool bVar1;
  char *local_14;
  int local_8;
  
  local_8 = -1;
  bVar1 = false;
  do {
    if ((bVar1) || (local_8 = thunk_FUN_0040fdc9(param_1), local_8 == -1)) {
      return local_8;
    }
    for (local_14 = param_1; *local_14 != '\0'; local_14 = local_14 + 1) {
      if (((*local_14 != ' ') && (*local_14 != '\t')) && (*local_14 != '\n')) {
        if ((*local_14 == ';') || ((*local_14 == '/' && (local_14[1] == '/')))) {
          *local_14 = '\0';
          break;
        }
        bVar1 = true;
      }
    }
  } while( true );
}
```

---

## FUN_0040ff5b — 0x40ff5b

- Classification : internal
- Corps : `0x40ff5b–0x410104`
- État : pseudocode obtenu
- Evidence : `ev_78147898fdd67751ac4b9dc7f61c638b16c2a36dd616080db86817b146a0965a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x4737e0` — `_strncpy`
- `0x473aa0` — `FID_conflict:__open`
- `0x473fe0` — `FUN_00473fe0`
- `0x4740d0` — `FUN_004740d0`
- `0x474190` — `FUN_00474190`

### Chaînes référencées

- `0x49b3a4` — "mNumCobs < MAX_COBS"
- `0x49b3b8` — "C:\\float\\src\\cfile.cpp"
- `0x49b3d0` — "num <= MAX_KERNELS - mNumKernels"
- `0x49b3f4` — "C:\\float\\src\\cfile.cpp"

### Pseudocode Ghidra

```c
void FUN_0040ff5b(char *param_1)

{
  undefined4 uVar1;
  int in_ECX;
  int local_c;
  int local_8;
  
  if (4 < *(int *)(in_ECX + 0x6aa0)) {
    thunk_FUN_00414b64(s_C__float_src_cfile_cpp_0049b3b8,0x2d1,s_mNumCobs_<_MAX_COBS_0049b3a4);
  }
  if (*(int *)(in_ECX + 0x6aa0) < 5) {
    _strncpy((char *)(in_ECX + 0x6990 + *(int *)(in_ECX + 0x6aa0) * 0x32),param_1,0x32);
    local_8 = FID_conflict___open(param_1,0x8000);
    if (local_8 != -1) {
      uVar1 = FUN_004740d0(local_8);
      *(undefined4 *)(in_ECX + 0x6a8c + *(int *)(in_ECX + 0x6aa0) * 4) = uVar1;
      FUN_00474190(local_8,&local_c,4);
      if (500 - *(int *)(in_ECX + 27000) < local_c) {
        uVar1 = thunk_FUN_00414b64(s_C__float_src_cfile_cpp_0049b3f4,0x2e5,
                                   s_num_<__MAX_KERNELS___mNumKernels_0049b3d0);
      }
      else {
        uVar1 = 0;
      }
      if (local_c <= 500 - *(int *)(in_ECX + 27000)) {
        FUN_00474190(local_8,in_ECX + *(int *)(in_ECX + 27000) * 0x32,local_c * 0x32,uVar1);
        FUN_00474190(local_8,in_ECX + 25000 + *(int *)(in_ECX + 27000) * 4,local_c << 2);
        FUN_00473fe0(local_8);
        *(int *)(in_ECX + 27000) = *(int *)(in_ECX + 27000) + local_c;
        *(int *)(in_ECX + 0x697c + *(int *)(in_ECX + 0x6aa0) * 4) = local_c;
        *(int *)(in_ECX + 0x6aa0) = *(int *)(in_ECX + 0x6aa0) + 1;
      }
    }
  }
  return;
}
```

---

## FUN_00410105 — 0x410105

- Classification : internal
- Corps : `0x410105–0x410160`
- État : pseudocode obtenu
- Evidence : `ev_3d928c3e3c20204be08e14067bfa575cbc3d1a9fe24a546b56dfe0d283c1483b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40183e` — `thunk_FUN_0040ff5b`
- `0x4748a0` — `FUN_004748a0`
- `0x474980` — `FUN_00474980`
- `0x474b00` — `FUN_00474b00`

### Chaînes référencées

- `0x49b410` — "cob.cfg"

### Pseudocode Ghidra

```c
void FUN_00410105(void)

{
  int iVar1;
  undefined1 local_6c [100];
  int local_8;
  
  local_8 = FUN_00474b00(s_cob_cfg_0049b410,&DAT_0049b40c);
  if (local_8 != 0) {
    while( true ) {
      iVar1 = FUN_00474980(local_8,&DAT_0049b418,local_6c);
      if (iVar1 == -1) break;
      thunk_FUN_0040ff5b(local_6c);
    }
    FUN_004748a0(local_8);
  }
  return;
}
```

---

## FUN_004104c0 — 0x4104c0

- Classification : internal
- Corps : `0x4104c0–0x4104d5`
- État : pseudocode obtenu
- Evidence : `ev_dce2fd40b367e433d50e86263a496f516c0e32bf3a463391e18c56033a70558a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a6e` — `thunk_FUN_004104e0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004104c0(void)

{
  undefined4 in_ECX;
  
  thunk_FUN_004104e0();
  return in_ECX;
}
```

---

## FUN_004104e0 — 0x4104e0

- Classification : internal
- Corps : `0x4104e0–0x410504`
- État : pseudocode obtenu
- Evidence : `ev_c5ff6b6e803acda84a20fe6cb44898407dc3786576c987c3f3cadfc81db98b63`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004104e0(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 27000) = 0;
  *(undefined4 *)(in_ECX + 0x6aa0) = 0;
  return;
}
```

---

## FUN_00410510 — 0x410510

- Classification : internal
- Corps : `0x410510–0x410642`
- État : pseudocode obtenu
- Evidence : `ev_c9d82ee41f603bb4b2372d5aff779397fb5c9fb6ebfcadb02a6c190ae955ecbd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401a28` — `thunk_FUN_0041081b`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00410510(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004914ac;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0040f6f7();
  local_8 = 0;
  iVar1 = thunk_FUN_0040f752(param_1,0x8000);
  if (iVar1 == 0) {
    thunk_FUN_0040fc15(&DAT_004b20f0,0x700);
    iVar1 = thunk_FUN_0041081b(param_2,0,0x404f8000,0,0x404f8000,0,0x404f8000);
    _memset(&DAT_004b27f0,iVar1,0xff);
    DAT_004b28ef = 0xff;
    thunk_FUN_0040fc15(&DAT_004bc530,0x700);
    iVar1 = thunk_FUN_0041081b(param_2,0,0,0,0,0,0);
    _memset(&DAT_004bcc30,iVar1,0xff);
    DAT_004bcd2f = 0xff;
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
  }
  else {
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
  }
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

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


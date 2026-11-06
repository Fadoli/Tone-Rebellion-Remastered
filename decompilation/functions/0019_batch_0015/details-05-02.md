# 0019_batch_0015 — détails (2/3)

## FUN_004777a0 — 0x4777a0

- Classification : internal
- Corps : `0x4777a0–0x4779d3`
- État : pseudocode obtenu
- Evidence : `ev_67c26586715584be82c288d4929339e579595b59f0c086c56dd57bdbb9d996f5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4779e0` — `shortsort`
- `0x477a50` — `swap`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004777a0(uint param_1,uint param_2,uint param_3,code *param_4)

{
  int iVar1;
  uint local_110;
  uint auStack_10c [30];
  uint local_94;
  uint auStack_90 [30];
  uint local_18;
  int local_14;
  uint local_10;
  int local_c;
  uint local_8;
  
  if ((param_2 < 2) || (param_3 == 0)) {
    return;
  }
  local_14 = 0;
  local_10 = param_1;
  local_110 = param_1 + param_3 * (param_2 - 1);
LAB_004777de:
  local_8 = (local_110 - local_10) / param_3 + 1;
  if (8 < local_8) {
    local_c = local_10 + (local_8 >> 1) * param_3;
    swap(local_c,local_10,param_3);
    local_18 = local_10;
    local_94 = local_110 + param_3;
LAB_00477852:
    local_18 = local_18 + param_3;
    if (local_18 <= local_110) goto code_r0x00477866;
    goto LAB_00477878;
  }
  shortsort(local_10,local_110,param_3,param_4);
  goto LAB_0047799f;
code_r0x00477866:
  iVar1 = (*param_4)(local_18,local_10);
  if (iVar1 < 1) goto LAB_00477852;
LAB_00477878:
  do {
    local_94 = local_94 - param_3;
    if (local_94 <= local_10) break;
    iVar1 = (*param_4)(local_94,local_10);
  } while (-1 < iVar1);
  if (local_18 <= local_94) {
    swap(local_18,local_94,param_3);
    goto LAB_00477852;
  }
  swap(local_10,local_94,param_3);
  if ((int)((local_94 - 1) - local_10) < (int)(local_110 - local_18)) {
    if (local_18 < local_110) {
      auStack_90[local_14] = local_18;
      auStack_10c[local_14] = local_110;
      local_14 = local_14 + 1;
    }
    if (local_10 + param_3 < local_94) {
      local_110 = local_94 - param_3;
      goto LAB_004777de;
    }
  }
  else {
    if (local_10 + param_3 < local_94) {
      auStack_90[local_14] = local_10;
      auStack_10c[local_14] = local_94 - param_3;
      local_14 = local_14 + 1;
    }
    if (local_18 < local_110) {
      local_10 = local_18;
      goto LAB_004777de;
    }
  }
LAB_0047799f:
  local_14 = local_14 + -1;
  if (local_14 < 0) {
    return;
  }
  local_10 = auStack_90[local_14];
  local_110 = auStack_10c[local_14];
  goto LAB_004777de;
}
```

---

## shortsort — 0x4779e0

- Classification : internal
- Corps : `0x4779e0–0x477a4c`
- État : pseudocode obtenu
- Evidence : `ev_9369c3102b6e153561fb9884a18ee162d4b72e5c1299e0bee10f124ab3a131cc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x477a50` — `swap`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _shortsort
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual
   Studio 2010 Debug */

void __cdecl shortsort(uint param_1,uint param_2,int param_3,code *param_4)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  for (; param_1 < param_2; param_2 = param_2 - param_3) {
    local_c = param_1;
    local_8 = param_1;
    while (local_8 = local_8 + param_3, local_8 <= param_2) {
      iVar1 = (*param_4)(local_8,local_c);
      if (0 < iVar1) {
        local_c = local_8;
      }
    }
    swap(local_c,param_2,param_3);
  }
  return;
}
```

---

## swap — 0x477a50

- Classification : internal
- Corps : `0x477a50–0x477a9d`
- État : pseudocode obtenu
- Evidence : `ev_2950a95b58e8a552dd5aca3e6e2375def2920670446bc26d115446d5daa9c702`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _swap
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual
   Studio 2010 Debug */

void __cdecl swap(undefined1 *param_1,undefined1 *param_2,int param_3)

{
  undefined1 uVar1;
  
  if (param_1 != param_2) {
    while (param_3 != 0) {
      uVar1 = *param_1;
      *param_1 = *param_2;
      param_1 = param_1 + 1;
      *param_2 = uVar1;
      param_2 = param_2 + 1;
      param_3 = param_3 + -1;
    }
  }
  return;
}
```

---

---

## FUN_00477aa0 — 0x477aa0

- Classification : internal
- Corps : `0x477aa0–0x477ab3`
- État : pseudocode obtenu
- Evidence : `ev_862df2ac266faef809a9d3d5198b04ba77d36391f94d0f25eff7961b9be40691`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x477abd` — `FUN_00477abd`
- `0x47f628` — `FUN_0047f628`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00477aa0(void)

{
  float10 in_ST0;
  
  FUN_0047f628((double)in_ST0);
  FUN_00477abd();
  return;
}
```

---

---

## FUN_00477ab4 — 0x477ab4

- Classification : internal
- Corps : `0x477ab4–0x477abc`
- État : pseudocode obtenu
- Evidence : `ev_00953bad2ddc5bda717ba63bea5321752793ad3cc53df37593084248ff91eb41`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x477ab8 to 0x47f5e5 __fload_withFB (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `0x47f5e5` — `__fload_withFB`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00477ab4(void)

{
                    /* WARNING: Subroutine does not return */
  __fload_withFB();
}
```

---

---

## FUN_00477abd — 0x477abd

- Classification : internal
- Corps : `0x477abd–0x477b4d`
- État : pseudocode obtenu
- Evidence : `ev_d9ee78f662f4d549a4460edbd8e684130a45d831555d9c6889384d7cc795f4b7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x477af2 to 0x47f64b __math_exit (external=false, thunk=false, hasNoReturn=false); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.

### Appels directs

- `0x47f557` — `__startOneArgErrorHandling`
- `0x47f5cc` — `FUN_0047f5cc`
- `0x47f64b` — `__math_exit`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ushort FUN_00477abd(int param_1)

{
  ushort uVar1;
  uint in_EAX;
  bool in_ZF;
  ushort in_FPUStatusWord;
  unkbyte10 in_ST0;
  float10 fVar2;
  
  if (in_ZF) {
    if (((in_EAX & 0xfffff) == 0) && (param_1 == 0)) {
      in_FPUStatusWord = 1;
    }
    else {
      in_FPUStatusWord = FUN_0047f5cc();
    }
    if (DAT_00632500 == 0) {
      uVar1 = __startOneArgErrorHandling();
      return uVar1;
    }
  }
  else {
    fVar2 = (float10)fcos(in_ST0);
    if ((in_FPUStatusWord & 0x400) != 0) {
      do {
        fVar2 = fVar2 - ROUND(fVar2 / _DAT_00495e5a) * _DAT_00495e5a;
      } while ((in_FPUStatusWord & 0x400) != 0);
      fcos(fVar2);
    }
    if (DAT_00632500 == 0) {
      uVar1 = __math_exit();
      return uVar1;
    }
  }
  return in_FPUStatusWord;
}
```

---

---

## FUN_00477b50 — 0x477b50

- Classification : internal
- Corps : `0x477b50–0x477b5a`
- État : pseudocode obtenu
- Evidence : `ev_c8a6533ea23e82a84c6d96e49b3c94bc1d0e0b5aeb17d67dee5f450b96949394`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00477b50(int param_1)

{
  return param_1 + -0x20;
}
```

---

---

## FUN_00477b60 — 0x477b60

- Classification : internal
- Corps : `0x477b60–0x477c88`
- État : pseudocode obtenu
- Evidence : `ev_7cd25b1f09406593647ce2d978a535763c1e0eccaf1beca1690a92f67f795dff`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`
- `0x480050` — `FUN_00480050`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00477b60(uint param_1)

{
  int iVar1;
  uint local_14;
  uint local_10;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  undefined4 local_8;
  
  if (DAT_006325e8 == 0) {
    if ((0x60 < (int)param_1) && ((int)param_1 < 0x7b)) {
      param_1 = param_1 - 0x20;
    }
  }
  else {
    if ((int)param_1 < 0x100) {
      if (DAT_004a87f4 < 2) {
        local_14 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 2;
      }
      else {
        local_14 = FUN_0047f2b0(param_1,2);
      }
      if (local_14 == 0) {
        return param_1;
      }
    }
    if ((*(ushort *)(PTR_DAT_004a85e8 + ((int)param_1 >> 8 & 0xffU) * 2) & 0x8000) == 0) {
      local_c = (undefined1)param_1;
      local_b = 0;
      local_8 = 1;
    }
    else {
      local_c = (undefined1)(param_1 >> 8);
      local_b = (undefined1)param_1;
      local_a = 0;
      local_8 = 2;
    }
    iVar1 = FUN_00480050(DAT_006325e8,0x200,&local_c,local_8,&local_10,3,0);
    if (iVar1 != 0) {
      if (iVar1 == 1) {
        param_1 = local_10 & 0xff;
      }
      else {
        param_1 = local_10 & 0xff | (local_10 >> 8 & 0xff) << 8;
      }
    }
  }
  return param_1;
}
```

---

---

## FUN_00477c90 — 0x477c90

- Classification : internal
- Corps : `0x477c90–0x47808c`
- État : pseudocode obtenu
- Evidence : `ev_9bd18987248cf70c13e954ff5fdb2e7102f8c9a38bbb9b18d7cdbe7c80770f01`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `EXTERNAL:0x38` — `KERNEL32.DLL::GetFileType`
- `EXTERNAL:0x42` — `KERNEL32.DLL::FileTimeToSystemTime`
- `EXTERNAL:0x43` — `KERNEL32.DLL::FileTimeToLocalFileTime`
- `EXTERNAL:0x44` — `KERNEL32.DLL::GetFileInformationByHandle`
- `EXTERNAL:0x45` — `KERNEL32.DLL::PeekNamedPipe`
- `0x47cac0` — `__dosmaperr`
- `0x480360` — `FUN_00480360`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00477c90(uint param_1,uint *param_2)

{
  DWORD DVar1;
  BOOL BVar2;
  uint uVar3;
  int iVar4;
  uint local_60 [2];
  undefined4 local_58;
  _FILETIME local_54;
  uint local_4c;
  _BY_HANDLE_FILE_INFORMATION local_48;
  _SYSTEMTIME local_14;
  
  local_58 = 0;
  if ((param_1 < DAT_00633e5c) &&
     (iVar4 = (int)param_1 >> 5,
     (*(byte *)((&DAT_00633d20)[iVar4] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    DVar1 = GetFileType(*(HANDLE *)((&DAT_00633d20)[iVar4] + (param_1 & 0x1f) * 8));
    local_4c = DVar1 & 0xffff7fff;
    if (local_4c == 1) {
      *(undefined2 *)((int)param_2 + 6) = 0;
      *(undefined2 *)(param_2 + 3) = 0;
      *(undefined2 *)((int)param_2 + 10) = 0;
      *(undefined2 *)(param_2 + 1) = 0;
      *(undefined2 *)(param_2 + 2) = 1;
      BVar2 = GetFileInformationByHandle
                        (*(HANDLE *)((&DAT_00633d20)[iVar4] + (param_1 & 0x1f) * 8),&local_48);
      if (BVar2 == 0) {
        DVar1 = GetLastError();
        __dosmaperr(DVar1);
        local_58 = 0xffffffff;
      }
      else {
        if ((local_48.dwFileAttributes & 1) == 0) {
          *(ushort *)((int)param_2 + 6) = *(ushort *)((int)param_2 + 6) | 0x1b6;
        }
        else {
          *(ushort *)((int)param_2 + 6) = *(ushort *)((int)param_2 + 6) | 0x124;
        }
        BVar2 = FileTimeToLocalFileTime(&local_48.ftLastWriteTime,&local_54);
        if ((BVar2 == 0) || (BVar2 = FileTimeToSystemTime(&local_54,&local_14), BVar2 == 0)) {
          local_58 = 0xffffffff;
        }
        else {
          uVar3 = FUN_00480360(local_14.wYear,local_14.wMonth,local_14.wDay,local_14.wHour,
                               local_14.wMinute,local_14.wSecond,0xffffffff);
          param_2[7] = uVar3;
          if ((local_48.ftLastAccessTime.dwLowDateTime == 0) &&
             (local_48.ftLastAccessTime.dwHighDateTime == 0)) {
            param_2[6] = param_2[7];
          }
          else {
            BVar2 = FileTimeToLocalFileTime(&local_48.ftLastAccessTime,&local_54);
            if ((BVar2 == 0) || (BVar2 = FileTimeToSystemTime(&local_54,&local_14), BVar2 == 0)) {
              return 0xffffffff;
            }
            uVar3 = FUN_00480360(local_14.wYear,local_14.wMonth,local_14.wDay,local_14.wHour,
                                 local_14.wMinute,local_14.wSecond,0xffffffff);
            param_2[6] = uVar3;
          }
          if ((local_48.ftCreationTime.dwLowDateTime == 0) &&
             (local_48.ftCreationTime.dwHighDateTime == 0)) {
            param_2[8] = param_2[7];
          }
          else {
            BVar2 = FileTimeToLocalFileTime(&local_48.ftCreationTime,&local_54);
            if ((BVar2 == 0) || (BVar2 = FileTimeToSystemTime(&local_54,&local_14), BVar2 == 0)) {
              return 0xffffffff;
            }
            uVar3 = FUN_00480360(local_14.wYear,local_14.wMonth,local_14.wDay,local_14.wHour,
                                 local_14.wMinute,local_14.wSecond,0xffffffff);
            param_2[8] = uVar3;
          }
          param_2[5] = local_48.nFileSizeLow;
          *(ushort *)((int)param_2 + 6) = *(ushort *)((int)param_2 + 6) | 0x8000;
          *param_2 = 0;
          param_2[4] = 0;
        }
      }
    }
    else if ((local_4c == 2) || (local_4c == 3)) {
      if (local_4c == 2) {
        *(undefined2 *)((int)param_2 + 6) = 0x2000;
      }
      else {
        *(undefined2 *)((int)param_2 + 6) = 0x1000;
      }
      *param_2 = param_1;
      param_2[4] = param_1;
      *(undefined2 *)(param_2 + 2) = 1;
      *(undefined2 *)(param_2 + 1) = 0;
      *(undefined2 *)(param_2 + 3) = 0;
      *(undefined2 *)((int)param_2 + 10) = 0;
      param_2[8] = 0;
      param_2[7] = 0;
      param_2[6] = 0;
      if (local_4c == 2) {
        param_2[5] = 0;
      }
      else {
        BVar2 = PeekNamedPipe(*(HANDLE *)((&DAT_00633d20)[iVar4] + (param_1 & 0x1f) * 8),(LPVOID)0x0
                              ,0,(LPDWORD)0x0,local_60,(LPDWORD)0x0);
        if (BVar2 == 0) {
          param_2[5] = 0;
        }
        else {
          param_2[5] = local_60[0];
        }
      }
    }
    else if (local_4c == 0) {
      _DAT_0063251c = 9;
      local_58 = 0xffffffff;
    }
    else {
      DVar1 = GetLastError();
      __dosmaperr(DVar1);
      local_58 = 0xffffffff;
    }
  }
  else {
    _DAT_0063251c = 9;
    local_58 = 0xffffffff;
  }
  return local_58;
}
```

---

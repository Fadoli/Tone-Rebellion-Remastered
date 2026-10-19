# 0019_batch_0015 — détails (2/3)

## FUN_004739b0 — 0x4739b0

- Classification : internal
- Corps : `0x4739b0–0x473a9d`
- État : pseudocode obtenu
- Evidence : `ev_f455da877ea81f9a059b60ab70c7209ed55c8ce6db6627278c71e8546b03019a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `EXTERNAL:0x36` — `KERNEL32.DLL::SetFilePointer`
- `0x47cac0` — `__dosmaperr`
- `0x47ce00` — `FUN_0047ce00`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

DWORD FUN_004739b0(uint param_1,LONG param_2,DWORD param_3)

{
  DWORD DVar1;
  HANDLE hFile;
  int iVar2;
  ulong local_8;
  
  if ((param_1 < DAT_00633e5c) &&
     (iVar2 = (int)param_1 >> 5,
     (*(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    hFile = (HANDLE)FUN_0047ce00(param_1);
    if (hFile == (HANDLE)0xffffffff) {
      _DAT_0063251c = 9;
      DVar1 = 0xffffffff;
    }
    else {
      DVar1 = SetFilePointer(hFile,param_2,(PLONG)0x0,param_3);
      if (DVar1 == 0xffffffff) {
        local_8 = GetLastError();
      }
      else {
        local_8 = 0;
      }
      if (local_8 == 0) {
        *(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) =
             *(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 0xfd;
      }
      else {
        __dosmaperr(local_8);
        DVar1 = 0xffffffff;
      }
    }
  }
  else {
    _DAT_0063251c = 9;
    DAT_00632520 = 0;
    DVar1 = 0xffffffff;
  }
  return DVar1;
}
```

---

## FID_conflict:__open — 0x473aa0

- Classification : internal
- Corps : `0x473aa0–0x473ade`
- État : pseudocode obtenu
- Evidence : `ev_8e1b0f55fb8def7e85a89bd9f9443dd42465607aa063b7ee68f1fdfcc11c981e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x473ae0` — `FUN_00473ae0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Multiple Matches With Different Base Names
    __open
    __wopen
   
   Library: Visual Studio 2003 Debug */

int __cdecl FID_conflict___open(char *_Filename,int _OpenFlag,...)

{
  int iVar1;
  undefined4 in_stack_0000000c;
  
  iVar1 = FUN_00473ae0(_Filename,_OpenFlag,0x40,in_stack_0000000c,0);
  return iVar1;
}
```

---

---

## FUN_00473ae0 — 0x473ae0

- Classification : internal
- Corps : `0x473ae0–0x473f95`
- État : pseudocode obtenu
- Evidence : `ev_20c95f91cfaee499df411e2d0d7a6ddff65efb66f2d74e86e79aedd5532e5983`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `EXTERNAL:0x37` — `KERNEL32.DLL::CloseHandle`
- `EXTERNAL:0x38` — `KERNEL32.DLL::GetFileType`
- `EXTERNAL:0x39` — `KERNEL32.DLL::CreateFileA`
- `0x4739b0` — `FUN_004739b0`
- `0x473fe0` — `FUN_00473fe0`
- `0x474190` — `FUN_00474190`
- `0x47cac0` — `__dosmaperr`
- `0x47cb50` — `FUN_0047cb50`
- `0x47cc80` — `__set_osfhnd`
- `0x47d2b0` — `FUN_0047d2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_00473ae0(LPCSTR param_1,uint param_2,undefined4 param_3,uint param_4)

{
  DWORD DVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  byte local_3c;
  uint local_38;
  char local_34 [4];
  undefined4 local_30;
  uint local_2c;
  _SECURITY_ATTRIBUTES local_28;
  DWORD local_1c;
  uint local_18;
  uint local_14;
  DWORD local_10;
  DWORD local_c;
  HANDLE local_8;
  
  local_28.nLength = 0xc;
  local_28.lpSecurityDescriptor = (LPVOID)0x0;
  bVar5 = (param_2 & 0x80) == 0;
  if (bVar5) {
    local_3c = 0;
  }
  else {
    local_3c = 0x10;
  }
  local_28.bInheritHandle = (BOOL)bVar5;
  if ((param_2 & 0x8000) == 0) {
    if ((param_2 & 0x4000) == 0) {
      if (DAT_006325a0 != 0x8000) {
        local_3c = local_3c | 0x80;
      }
    }
    else {
      local_3c = local_3c | 0x80;
    }
  }
  uVar4 = param_2 & 3;
  if (uVar4 == 0) {
    local_38 = 0x80000000;
  }
  else if (uVar4 == 1) {
    local_38 = 0x40000000;
  }
  else {
    if (uVar4 != 2) {
      _DAT_0063251c = 0x16;
      DAT_00632520 = 0;
      return 0xffffffff;
    }
    local_38 = 0xc0000000;
  }
  switch(param_3) {
  case 0x10:
    local_c = 0;
    break;
  default:
    _DAT_0063251c = 0x16;
    DAT_00632520 = 0;
    return 0xffffffff;
  case 0x20:
    local_c = 1;
    break;
  case 0x30:
    local_c = 2;
    break;
  case 0x40:
    local_c = 3;
  }
  uVar4 = param_2 & 0x700;
  if (uVar4 < 0x101) {
    if (uVar4 == 0x100) {
      local_1c = 4;
      goto LAB_00473cc9;
    }
    if (uVar4 != 0) {
      _DAT_0063251c = 0x16;
      DAT_00632520 = 0;
      return 0xffffffff;
    }
LAB_00473c80:
    local_1c = 3;
    goto LAB_00473cc9;
  }
  if (uVar4 < 0x301) {
    if (uVar4 == 0x300) {
      local_1c = 2;
      goto LAB_00473cc9;
    }
    if (uVar4 != 0x200) {
      _DAT_0063251c = 0x16;
      DAT_00632520 = 0;
      return 0xffffffff;
    }
LAB_00473c9b:
    local_1c = 5;
  }
  else {
    if (uVar4 < 0x501) {
      if (uVar4 != 0x500) {
        if (uVar4 != 0x400) {
          _DAT_0063251c = 0x16;
          DAT_00632520 = 0;
          return 0xffffffff;
        }
        goto LAB_00473c80;
      }
    }
    else {
      if (uVar4 == 0x600) goto LAB_00473c9b;
      if (uVar4 != 0x700) {
        _DAT_0063251c = 0x16;
        DAT_00632520 = 0;
        return 0xffffffff;
      }
    }
    local_1c = 1;
  }
LAB_00473cc9:
  local_2c = 0x80;
  if ((param_2 & 0x100) != 0) {
    local_14 = param_4;
    local_30 = 0;
    if ((param_4 & ~DAT_00632524 & 0x80) == 0) {
      local_2c = 1;
    }
  }
  if ((param_2 & 0x40) != 0) {
    local_2c = local_2c | 0x4000000;
    local_38 = local_38 | 0x10000;
  }
  if ((param_2 & 0x1000) != 0) {
    local_2c = local_2c | 0x100;
  }
  if ((param_2 & 0x20) == 0) {
    if ((param_2 & 0x10) != 0) {
      local_2c = local_2c | 0x10000000;
    }
  }
  else {
    local_2c = local_2c | 0x8000000;
  }
  local_18 = FUN_0047cb50();
  if (local_18 == 0xffffffff) {
    _DAT_0063251c = 0x18;
    DAT_00632520 = 0;
    local_18 = 0xffffffff;
  }
  else {
    local_8 = CreateFileA(param_1,local_38,local_c,&local_28,local_1c,local_2c,(HANDLE)0x0);
    if (local_8 == (HANDLE)0xffffffff) {
      DVar1 = GetLastError();
      __dosmaperr(DVar1);
      local_18 = 0xffffffff;
    }
    else {
      local_10 = GetFileType(local_8);
      if (local_10 == 0) {
        CloseHandle(local_8);
        DVar1 = GetLastError();
        __dosmaperr(DVar1);
        local_18 = 0xffffffff;
      }
      else {
        if (local_10 == 2) {
          local_3c = local_3c | 0x40;
        }
        else if (local_10 == 3) {
          local_3c = local_3c | 8;
        }
        __set_osfhnd(local_18,(intptr_t)local_8);
        *(byte *)((&DAT_00633d20)[(int)local_18 >> 5] + 4 + (local_18 & 0x1f) * 8) = local_3c | 1;
        if ((((local_3c & 0x48) == 0) && (((int)(char)(local_3c | 1) & 0x80U) != 0)) &&
           ((param_2 & 2) != 0)) {
          iVar2 = FUN_004739b0(local_18,0xffffffff,2);
          if (iVar2 == -1) {
            if (DAT_00632520 != 0x83) {
              FUN_00473fe0(local_18);
              return 0xffffffff;
            }
          }
          else {
            local_34[0] = '\0';
            iVar3 = FUN_00474190(local_18,local_34,1);
            if (((iVar3 == 0) && (local_34[0] == '\x1a')) &&
               (iVar2 = FUN_0047d2b0(local_18,iVar2), iVar2 == -1)) {
              FUN_00473fe0(local_18);
              return 0xffffffff;
            }
            iVar2 = FUN_004739b0(local_18,0,0);
            if (iVar2 == -1) {
              FUN_00473fe0(local_18);
              return 0xffffffff;
            }
          }
        }
        if (((local_3c & 0x48) == 0) && ((param_2 & 8) != 0)) {
          *(byte *)((&DAT_00633d20)[(int)local_18 >> 5] + 4 + (local_18 & 0x1f) * 8) =
               *(byte *)((&DAT_00633d20)[(int)local_18 >> 5] + 4 + (local_18 & 0x1f) * 8) | 0x20;
        }
      }
    }
  }
  return local_18;
}
```

---

---

## FUN_00473fe0 — 0x473fe0

- Classification : internal
- Corps : `0x473fe0–0x4740cc`
- État : pseudocode obtenu
- Evidence : `ev_bf53cdbca46e20aee57077e6b5b25960e5eccf2b83fa8aa52dfec86e4a3ac31f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `EXTERNAL:0x37` — `KERNEL32.DLL::CloseHandle`
- `0x47cac0` — `__dosmaperr`
- `0x47cd30` — `FUN_0047cd30`
- `0x47ce00` — `FUN_0047ce00`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00473fe0(uint param_1)

{
  int iVar1;
  int iVar2;
  HANDLE hObject;
  BOOL BVar3;
  undefined4 uVar4;
  ulong local_8;
  
  if ((DAT_00633e5c <= param_1) ||
     ((*(byte *)((&DAT_00633d20)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) & 1) == 0)) {
    _DAT_0063251c = 9;
    DAT_00632520 = 0;
    return 0xffffffff;
  }
  iVar1 = FUN_0047ce00(param_1);
  if (iVar1 != -1) {
    if ((param_1 == 1) || (param_1 == 2)) {
      iVar1 = FUN_0047ce00(1);
      iVar2 = FUN_0047ce00(2);
      if (iVar1 == iVar2) goto LAB_00474079;
    }
    hObject = (HANDLE)FUN_0047ce00(param_1);
    BVar3 = CloseHandle(hObject);
    if (BVar3 == 0) {
      local_8 = GetLastError();
      goto LAB_0047408b;
    }
  }
LAB_00474079:
  local_8 = 0;
LAB_0047408b:
  FUN_0047cd30(param_1);
  *(undefined1 *)((&DAT_00633d20)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) = 0;
  if (local_8 == 0) {
    uVar4 = 0;
  }
  else {
    __dosmaperr(local_8);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}
```

---

---

## FUN_004740d0 — 0x4740d0

- Classification : internal
- Corps : `0x4740d0–0x47416e`
- État : pseudocode obtenu
- Evidence : `ev_9da57838c0a45f3816cb113fee495166cc4334a8fd721f25cb87b7fec4118aa2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4739b0` — `FUN_004739b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_004740d0(uint param_1)

{
  int iVar1;
  int local_8;
  
  if ((param_1 < DAT_00633e5c) &&
     ((*(byte *)((&DAT_00633d20)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    iVar1 = FUN_004739b0(param_1,0,1);
    if (iVar1 == -1) {
      local_8 = -1;
    }
    else {
      local_8 = FUN_004739b0(param_1,0,2);
      if (iVar1 != local_8) {
        FUN_004739b0(param_1,iVar1,0);
      }
    }
  }
  else {
    _DAT_0063251c = 9;
    DAT_00632520 = 0;
    local_8 = -1;
  }
  return local_8;
}
```

---

---

## FUN_00474170 — 0x474170

- Classification : internal
- Corps : `0x474170–0x474184`
- État : pseudocode obtenu
- Evidence : `ev_84a723ef1a96f0b644fa6b7409879deef6867cd47516148568814d4b4cefc099`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4739b0` — `FUN_004739b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00474170(undefined4 param_1)

{
  FUN_004739b0(param_1,0,1);
  return;
}
```

---

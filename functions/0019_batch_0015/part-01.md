# 0019_batch_0015 — détails (1/6)

## FUN_00473486 — 0x473486

- Classification : internal
- Corps : `0x473486–0x47349d`
- État : pseudocode obtenu
- Evidence : `ev_aeb7594ca7ffb21b0c8a69db0433357ce6ae611eccb12d9b78afc44fbeebbcf5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00473486(void)

{
  undefined4 in_EAX;
  int unaff_EBP;
  
  DAT_004a6338 = *(undefined4 *)(unaff_EBP + 8);
  DAT_004a6334 = in_EAX;
  DAT_004a633c = unaff_EBP;
  return;
}
```

---

## FUN_004734a0 — 0x4734a0

- Classification : internal
- Corps : `0x4734a0–0x4734fa`, `0x4734fc–0x473502`, `0x473510–0x473538`, `0x47353c–0x47355e`, `0x473560–0x473578`, `0x47359c–0x4735e5`, `0x4735f8–0x4735fe`, `0x473600–0x47360a`, `0x47360c–0x47361c`, `0x473620–0x473636`, `0x473638–0x47365d`, `0x473660–0x473668`, `0x47366c–0x47368a`, `0x473698–0x4736b4`, `0x4736b8–0x4736de`, `0x4736e0–0x473710`, `0x473734–0x47377d`, `0x473790–0x473796`, `0x473798–0x4737a4`, `0x4737a8–0x4737ba`, `0x4737bc–0x4737d4`
- État : pseudocode obtenu
- Evidence : `ev_8b161aa603bc9ab42d593121121cec08459a614882e5aac34e270745d5b8937e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_004734a0(undefined4 *param_1,undefined4 *param_2,uint param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if ((param_2 < param_1) && (param_1 < (undefined4 *)(param_3 + (int)param_2))) {
    param_2 = (undefined4 *)((param_3 - 4) + (int)param_2);
    puVar2 = (undefined4 *)((param_3 - 4) + (int)param_1);
    if (((uint)puVar2 & 3) == 0) {
      uVar1 = param_3 >> 2;
      param_3 = param_3 & 3;
      if (7 < uVar1) {
        for (; uVar1 != 0; uVar1 = uVar1 - 1) {
          *puVar2 = *param_2;
          param_2 = param_2 + -1;
          puVar2 = puVar2 + -1;
        }
        switch(param_3) {
        case 0:
          return param_1;
        case 2:
          goto switchD_00473657_caseD_2;
        case 3:
          goto switchD_00473657_caseD_3;
        }
        goto switchD_00473657_caseD_1;
      }
    }
    else {
      switch(param_3) {
      case 0:
        goto switchD_00473657_caseD_0;
      case 1:
        goto switchD_00473657_caseD_1;
      case 2:
        goto switchD_00473657_caseD_2;
      case 3:
        goto switchD_00473657_caseD_3;
      default:
        uVar1 = param_3 - ((uint)puVar2 & 3);
        switch((uint)puVar2 & 3) {
        case 1:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          param_2 = (undefined4 *)((int)param_2 + -1);
          uVar1 = uVar1 >> 2;
          puVar2 = (undefined4 *)((int)puVar2 - 1);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto switchD_00473657_caseD_2;
            case 3:
              goto switchD_00473657_caseD_3;
            }
            goto switchD_00473657_caseD_1;
          }
          break;
        case 2:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
          param_2 = (undefined4 *)((int)param_2 + -2);
          puVar2 = (undefined4 *)((int)puVar2 - 2);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto switchD_00473657_caseD_2;
            case 3:
              goto switchD_00473657_caseD_3;
            }
            goto switchD_00473657_caseD_1;
          }
          break;
        case 3:
          param_3 = uVar1 & 3;
          *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
          *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
          uVar1 = uVar1 >> 2;
          *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
          param_2 = (undefined4 *)((int)param_2 + -3);
          puVar2 = (undefined4 *)((int)puVar2 - 3);
          if (7 < uVar1) {
            for (; uVar1 != 0; uVar1 = uVar1 - 1) {
              *puVar2 = *param_2;
              param_2 = param_2 + -1;
              puVar2 = puVar2 + -1;
            }
            switch(param_3) {
            case 0:
              return param_1;
            case 2:
              goto switchD_00473657_caseD_2;
            case 3:
              goto switchD_00473657_caseD_3;
            }
            goto switchD_00473657_caseD_1;
          }
        }
      }
    }
    switch(uVar1) {
    case 7:
      puVar2[7 - uVar1] = param_2[7 - uVar1];
    case 6:
      puVar2[6 - uVar1] = param_2[6 - uVar1];
    case 5:
      puVar2[5 - uVar1] = param_2[5 - uVar1];
    case 4:
      puVar2[4 - uVar1] = param_2[4 - uVar1];
    case 3:
      puVar2[3 - uVar1] = param_2[3 - uVar1];
    case 2:
      puVar2[2 - uVar1] = param_2[2 - uVar1];
    case 1:
      puVar2[1 - uVar1] = param_2[1 - uVar1];
      param_2 = param_2 + -uVar1;
      puVar2 = puVar2 + -uVar1;
    }
    switch(param_3) {
    case 1:
switchD_00473657_caseD_1:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      return param_1;
    case 2:
switchD_00473657_caseD_2:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
      return param_1;
    case 3:
switchD_00473657_caseD_3:
      *(undefined1 *)((int)puVar2 + 3) = *(undefined1 *)((int)param_2 + 3);
      *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
      *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
      return param_1;
    }
switchD_00473657_caseD_0:
    return param_1;
  }
  puVar2 = param_1;
  if (((uint)param_1 & 3) == 0) {
    uVar1 = param_3 >> 2;
    param_3 = param_3 & 3;
    if (7 < uVar1) {
      for (; uVar1 != 0; uVar1 = uVar1 - 1) {
        *puVar2 = *param_2;
        param_2 = param_2 + 1;
        puVar2 = puVar2 + 1;
      }
      switch(param_3) {
      case 0:
        return param_1;
      case 2:
        goto switchD_004734d5_caseD_2;
      case 3:
        goto switchD_004734d5_caseD_3;
      }
      goto switchD_004734d5_caseD_1;
    }
  }
  else {
    switch(param_3) {
    case 0:
      goto switchD_004734d5_caseD_0;
    case 1:
      goto switchD_004734d5_caseD_1;
    case 2:
      goto switchD_004734d5_caseD_2;
    case 3:
      goto switchD_004734d5_caseD_3;
    default:
      uVar1 = (param_3 - 4) + ((uint)param_1 & 3);
      switch((uint)param_1 & 3) {
      case 1:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 2) = *(undefined1 *)((int)param_2 + 2);
        param_2 = (undefined4 *)((int)param_2 + 3);
        puVar2 = (undefined4 *)((int)param_1 + 3);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto switchD_004734d5_caseD_2;
          case 3:
            goto switchD_004734d5_caseD_3;
          }
          goto switchD_004734d5_caseD_1;
        }
        break;
      case 2:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        uVar1 = uVar1 >> 2;
        *(undefined1 *)((int)param_1 + 1) = *(undefined1 *)((int)param_2 + 1);
        param_2 = (undefined4 *)((int)param_2 + 2);
        puVar2 = (undefined4 *)((int)param_1 + 2);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto switchD_004734d5_caseD_2;
          case 3:
            goto switchD_004734d5_caseD_3;
          }
          goto switchD_004734d5_caseD_1;
        }
        break;
      case 3:
        param_3 = uVar1 & 3;
        *(undefined1 *)param_1 = *(undefined1 *)param_2;
        param_2 = (undefined4 *)((int)param_2 + 1);
        uVar1 = uVar1 >> 2;
        puVar2 = (undefined4 *)((int)param_1 + 1);
        if (7 < uVar1) {
          for (; uVar1 != 0; uVar1 = uVar1 - 1) {
            *puVar2 = *param_2;
            param_2 = param_2 + 1;
            puVar2 = puVar2 + 1;
          }
          switch(param_3) {
          case 0:
            return param_1;
          case 2:
            goto switchD_004734d5_caseD_2;
          case 3:
            goto switchD_004734d5_caseD_3;
          }
          goto switchD_004734d5_caseD_1;
        }
      }
    }
  }
  switch(uVar1) {
  case 7:
    puVar2[uVar1 - 7] = param_2[uVar1 - 7];
  case 6:
    puVar2[uVar1 - 6] = param_2[uVar1 - 6];
  case 5:
    puVar2[uVar1 - 5] = param_2[uVar1 - 5];
  case 4:
    puVar2[uVar1 - 4] = param_2[uVar1 - 4];
  case 3:
    puVar2[uVar1 - 3] = param_2[uVar1 - 3];
  case 2:
    puVar2[uVar1 - 2] = param_2[uVar1 - 2];
  case 1:
    puVar2[uVar1 - 1] = param_2[uVar1 - 1];
    param_2 = param_2 + uVar1;
    puVar2 = puVar2 + uVar1;
  }
  switch(param_3) {
  case 1:
switchD_004734d5_caseD_1:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    return param_1;
  case 2:
switchD_004734d5_caseD_2:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
    return param_1;
  case 3:
switchD_004734d5_caseD_3:
    *(undefined1 *)puVar2 = *(undefined1 *)param_2;
    *(undefined1 *)((int)puVar2 + 1) = *(undefined1 *)((int)param_2 + 1);
    *(undefined1 *)((int)puVar2 + 2) = *(undefined1 *)((int)param_2 + 2);
    return param_1;
  }
switchD_004734d5_caseD_0:
  return param_1;
}
```

---

## _strncpy — 0x4737e0

- Classification : internal
- Corps : `0x4737e0–0x4738dd`
- État : pseudocode obtenu
- Evidence : `ev_41b2e7e3a42619d8a5cca5a8d83b6218db9781c0f80ff872ff413474812b14e9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _strncpy
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl _strncpy(char *_Dest,char *_Source,size_t _Count)

{
  uint uVar1;
  uint uVar2;
  char cVar3;
  uint uVar4;
  uint *puVar5;
  
  if (_Count == 0) {
    return _Dest;
  }
  puVar5 = (uint *)_Dest;
  if (((uint)_Source & 3) != 0) {
    while( true ) {
      uVar4 = *(uint *)_Source;
      _Source = (char *)((int)_Source + 1);
      *(char *)puVar5 = (char)uVar4;
      puVar5 = (uint *)((int)puVar5 + 1);
      _Count = _Count - 1;
      if (_Count == 0) {
        return _Dest;
      }
      if ((char)uVar4 == '\0') break;
      if (((uint)_Source & 3) == 0) {
        uVar4 = _Count >> 2;
        goto joined_r0x0047381e;
      }
    }
    do {
      if (((uint)puVar5 & 3) == 0) {
        uVar4 = _Count >> 2;
        cVar3 = '\0';
        if (uVar4 == 0) goto LAB_0047385b;
        goto LAB_004738c9;
      }
      *(char *)puVar5 = '\0';
      puVar5 = (uint *)((int)puVar5 + 1);
      _Count = _Count - 1;
    } while (_Count != 0);
    return _Dest;
  }
  uVar4 = _Count >> 2;
  if (uVar4 != 0) {
    do {
      uVar1 = *(uint *)_Source;
      uVar2 = *(uint *)_Source;
      _Source = (char *)((int)_Source + 4);
      if (((uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff) & 0x81010100) != 0) {
        if ((char)uVar2 == '\0') {
          *puVar5 = 0;
joined_r0x004738c5:
          while( true ) {
            uVar4 = uVar4 - 1;
            puVar5 = puVar5 + 1;
            if (uVar4 == 0) break;
LAB_004738c9:
            *puVar5 = 0;
          }
          cVar3 = '\0';
          _Count = _Count & 3;
          if (_Count != 0) goto LAB_0047385b;
          return _Dest;
        }
        if ((char)(uVar2 >> 8) == '\0') {
          *puVar5 = uVar2 & 0xff;
          goto joined_r0x004738c5;
        }
        if ((uVar2 & 0xff0000) == 0) {
          *puVar5 = uVar2 & 0xffff;
          goto joined_r0x004738c5;
        }
        if ((uVar2 & 0xff000000) == 0) {
          *puVar5 = uVar2;
          goto joined_r0x004738c5;
        }
      }
      *puVar5 = uVar2;
      puVar5 = puVar5 + 1;
      uVar4 = uVar4 - 1;
joined_r0x0047381e:
    } while (uVar4 != 0);
    _Count = _Count & 3;
    if (_Count == 0) {
      return _Dest;
    }
  }
  do {
    cVar3 = (char)*(uint *)_Source;
    _Source = (char *)((int)_Source + 1);
    *(char *)puVar5 = cVar3;
    puVar5 = (uint *)((int)puVar5 + 1);
    if (cVar3 == '\0') {
      while (_Count = _Count - 1, _Count != 0) {
LAB_0047385b:
        *(char *)puVar5 = cVar3;
        puVar5 = (uint *)((int)puVar5 + 1);
      }
      return _Dest;
    }
    _Count = _Count - 1;
  } while (_Count != 0);
  return _Dest;
}
```

---

## _strchr — 0x4738f0

- Classification : internal
- Corps : `0x4738e0–0x4738e4`, `0x4738f0–0x4739ab`
- État : pseudocode obtenu
- Evidence : `ev_e0db3b989e4bfc8b0ba51ae716b5747533f202ff79dc884ad11bfb0e8d04e74d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _strchr
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

char * __cdecl _strchr(char *_Str,int _Val)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  while (((uint)_Str & 3) != 0) {
    uVar1 = *(uint *)_Str;
    if ((char)uVar1 == (char)_Val) {
      return (char *)(uint *)_Str;
    }
    _Str = (char *)((int)_Str + 1);
    if ((char)uVar1 == '\0') {
      return (char *)0x0;
    }
  }
  while( true ) {
    while( true ) {
      uVar1 = *(uint *)_Str;
      uVar4 = uVar1 ^ CONCAT22(CONCAT11((char)_Val,(char)_Val),CONCAT11((char)_Val,(char)_Val));
      uVar3 = uVar1 ^ 0xffffffff ^ uVar1 + 0x7efefeff;
      puVar5 = (uint *)((int)_Str + 4);
      if (((uVar4 ^ 0xffffffff ^ uVar4 + 0x7efefeff) & 0x81010100) != 0) break;
      _Str = (char *)puVar5;
      if ((uVar3 & 0x81010100) != 0) {
        if ((uVar3 & 0x1010100) != 0) {
          return (char *)0x0;
        }
        if ((uVar1 + 0x7efefeff & 0x80000000) == 0) {
          return (char *)0x0;
        }
      }
    }
    uVar1 = *(uint *)_Str;
    if ((char)uVar1 == (char)_Val) {
      return (char *)(uint *)_Str;
    }
    if ((char)uVar1 == '\0') {
      return (char *)0x0;
    }
    cVar2 = (char)(uVar1 >> 8);
    if (cVar2 == (char)_Val) {
      return (char *)((int)_Str + 1);
    }
    if (cVar2 == '\0') {
      return (char *)0x0;
    }
    cVar2 = (char)(uVar1 >> 0x10);
    if (cVar2 == (char)_Val) {
      return (char *)((int)_Str + 2);
    }
    if (cVar2 == '\0') break;
    cVar2 = (char)(uVar1 >> 0x18);
    if (cVar2 == (char)_Val) {
      return (char *)((int)_Str + 3);
    }
    _Str = (char *)puVar5;
    if (cVar2 == '\0') {
      return (char *)0x0;
    }
  }
  return (char *)0x0;
}
```

---

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

## FUN_00474190 — 0x474190

- Classification : internal
- Corps : `0x474190–0x4745e3`
- État : pseudocode obtenu
- Evidence : `ev_87da4088d973d81a945f8e3e9d68ea79ba722b3a0ebeefcfa1504b0232847a05`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `EXTERNAL:0x3a` — `KERNEL32.DLL::ReadFile`
- `0x4739b0` — `FUN_004739b0`
- `0x47cac0` — `__dosmaperr`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00474190(uint param_1,char *param_2,DWORD param_3)

{
  BOOL BVar1;
  int iVar2;
  char local_20 [4];
  int local_1c;
  char *local_18;
  DWORD local_14;
  char *local_10;
  DWORD local_c;
  char *local_8;
  
  if ((param_1 < DAT_00633e5c) &&
     (iVar2 = (int)param_1 >> 5,
     (*(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    local_1c = 0;
    local_18 = param_2;
    if ((param_3 == 0) || ((*(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 2) != 0))
    {
      local_1c = 0;
    }
    else {
      if (((*(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 0x48) != 0) &&
         (*(char *)((&DAT_00633d20)[iVar2] + 5 + (param_1 & 0x1f) * 8) != '\n')) {
        *param_2 = *(char *)((&DAT_00633d20)[iVar2] + 5 + (param_1 & 0x1f) * 8);
        local_18 = param_2 + 1;
        local_1c = 1;
        param_3 = param_3 - 1;
        *(undefined1 *)((&DAT_00633d20)[iVar2] + 5 + (param_1 & 0x1f) * 8) = 10;
      }
      BVar1 = ReadFile(*(HANDLE *)((&DAT_00633d20)[iVar2] + (param_1 & 0x1f) * 8),local_18,param_3,
                       &local_14,(LPOVERLAPPED)0x0);
      if (BVar1 == 0) {
        local_c = GetLastError();
        if (local_c == 5) {
          _DAT_0063251c = 9;
          local_1c = -1;
          DAT_00632520 = 5;
        }
        else if (local_c == 0x6d) {
          local_1c = 0;
        }
        else {
          __dosmaperr(local_c);
          local_1c = -1;
        }
      }
      else {
        local_1c = local_1c + local_14;
        if (((int)*(char *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 0x80U) != 0) {
          if ((local_14 == 0) || (*param_2 != '\n')) {
            *(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) =
                 *(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 0xfb;
          }
          else {
            *(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) =
                 *(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) | 4;
          }
          local_10 = param_2;
          local_8 = param_2;
          while (local_8 < param_2 + local_1c) {
            if (*local_8 == '\x1a') {
              if ((*(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 0x40) == 0) {
                *(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) =
                     *(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) | 2;
              }
              break;
            }
            if (*local_8 == '\r') {
              if (local_8 < param_2 + local_1c + -1) {
                if (local_8[1] == '\n') {
                  local_8 = local_8 + 2;
                  *local_10 = '\n';
                }
                else {
                  *local_10 = *local_8;
                  local_8 = local_8 + 1;
                }
                local_10 = local_10 + 1;
              }
              else {
                local_8 = local_8 + 1;
                local_c = 0;
                BVar1 = ReadFile(*(HANDLE *)((&DAT_00633d20)[iVar2] + (param_1 & 0x1f) * 8),local_20
                                 ,1,&local_14,(LPOVERLAPPED)0x0);
                if (BVar1 == 0) {
                  local_c = GetLastError();
                }
                if ((local_c == 0) && (local_14 != 0)) {
                  if ((*(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 0x48) == 0) {
                    if ((local_10 == param_2) && (local_20[0] == '\n')) {
                      *local_10 = '\n';
                      local_10 = local_10 + 1;
                    }
                    else {
                      FUN_004739b0(param_1,0xffffffff,1);
                      if (local_20[0] != '\n') {
                        *local_10 = '\r';
                        local_10 = local_10 + 1;
                      }
                    }
                  }
                  else {
                    if (local_20[0] == '\n') {
                      *local_10 = '\n';
                    }
                    else {
                      *local_10 = '\r';
                      *(char *)((&DAT_00633d20)[iVar2] + 5 + (param_1 & 0x1f) * 8) = local_20[0];
                    }
                    local_10 = local_10 + 1;
                  }
                }
                else {
                  *local_10 = '\r';
                  local_10 = local_10 + 1;
                }
              }
            }
            else {
              *local_10 = *local_8;
              local_10 = local_10 + 1;
              local_8 = local_8 + 1;
            }
          }
          local_1c = (int)local_10 - (int)param_2;
        }
      }
    }
  }
  else {
    _DAT_0063251c = 9;
    DAT_00632520 = 0;
    local_1c = -1;
  }
  return local_1c;
}
```

---


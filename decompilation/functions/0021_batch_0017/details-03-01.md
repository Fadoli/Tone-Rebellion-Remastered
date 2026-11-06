# 0021_batch_0017 — détails (1/3)

## FUN_00480e90 — 0x480e90

- Classification : internal
- Corps : `0x480e90–0x480ea4`
- État : pseudocode obtenu
- Evidence : `ev_66f77dafbd4e104d4dc3b0a35ff49ad791889bc5175161c0c54d23451ab216c1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480e90(undefined4 param_1)

{
  FUN_00480f30(param_1,0x10,2);
  return;
}
```

---

---

## FUN_00480eb0 — 0x480eb0

- Classification : internal
- Corps : `0x480eb0–0x480ec4`
- État : pseudocode obtenu
- Evidence : `ev_0c78cfc3eac5642cbaf192bb7595a00dda80985227b1861ee94a1e7fb98713c7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480eb0(undefined4 param_1)

{
  FUN_00480f30(param_1,0,4);
  return;
}
```

---

---

## FUN_00480ed0 — 0x480ed0

- Classification : internal
- Corps : `0x480ed0–0x480ee4`
- État : pseudocode obtenu
- Evidence : `ev_798b827b8f06772862aa5c98451c181209a1e8602344ee6f4b303d2eb8d6aeb1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480ed0(undefined4 param_1)

{
  FUN_00480f30(param_1,0,8);
  return;
}
```

---

## __ismbbkana — 0x480ef0

- Classification : internal
- Corps : `0x480ef0–0x480f2a`
- État : pseudocode obtenu
- Evidence : `ev_3d3e2322bdfa8e5155725ae9d8ad231a9c608de6de5a85bbf642fcd92e05c490`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __ismbbkana
   
   Library: Visual Studio 2003 Debug */

int __cdecl __ismbbkana(uint _C)

{
  int iVar1;
  
  if ((DAT_00632844 == 0x3a4) && (iVar1 = FUN_00480f30(_C,0,3), iVar1 != 0)) {
    return 1;
  }
  return 0;
}
```

---

---

## FUN_00480f30 — 0x480f30

- Classification : internal
- Corps : `0x480f30–0x480f91`
- État : pseudocode obtenu
- Evidence : `ev_27190c6d0456519cde47dcf48df7b47a0fedb58a63306c51b4929b1a9cb68659`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00480f30(uint param_1,uint param_2,byte param_3)

{
  uint local_8;
  
  if (((&DAT_00632741)[param_1 & 0xff] & param_3) == 0) {
    if (param_2 == 0) {
      local_8 = 0;
    }
    else {
      local_8 = *(ushort *)(&DAT_004a85f2 + (param_1 & 0xff) * 2) & param_2;
    }
    if (local_8 == 0) {
      return 0;
    }
  }
  return 1;
}
```

---

---

## FUN_00480fa0 — 0x480fa0

- Classification : internal
- Corps : `0x480fa0–0x4810d0`
- État : pseudocode obtenu
- Evidence : `ev_e5a2f278fe89927816b9bbd23333c8a420d2b28db1fcdb975339ff4c280a49a2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`
- `0x474d40` — `FUN_00474d40`
- `0x475780` — `FUN_00475780`
- `0x478690` — `__amsg_exit`

### Chaînes référencées

- `0x495f00` — "stdenvp.c"
- `0x495f00` — "stdenvp.c"

### Pseudocode Ghidra

```c
void FUN_00480fa0(void)

{
  size_t sVar1;
  int iVar2;
  int *local_10;
  int local_c;
  char *local_8;
  
  local_c = 0;
  for (local_8 = DAT_00632570; *local_8 != '\0'; local_8 = local_8 + sVar1 + 1) {
    if (*local_8 != '=') {
      local_c = local_c + 1;
    }
    sVar1 = _strlen(local_8);
  }
  local_10 = (int *)FUN_00474d40(local_c * 4 + 4,2,"stdenvp.c",0x55);
  DAT_00632544 = local_10;
  if (local_10 == (int *)0x0) {
    __amsg_exit(9);
  }
  for (local_8 = DAT_00632570; *local_8 != '\0'; local_8 = local_8 + sVar1 + 1) {
    sVar1 = _strlen(local_8);
    if (*local_8 != '=') {
      iVar2 = FUN_00474d40(sVar1 + 1,2,"stdenvp.c",0x61);
      *local_10 = iVar2;
      if (*local_10 == 0) {
        __amsg_exit(9);
      }
      FUN_00472da0(*local_10,local_8);
      local_10 = local_10 + 1;
    }
  }
  FUN_00475780(DAT_00632570,2);
  DAT_00632570 = (char *)0x0;
  *local_10 = 0;
  return;
}
```

---

---

## FUN_004810e0 — 0x4810e0

- Classification : internal
- Corps : `0x4810e0–0x4811a6`
- État : pseudocode obtenu
- Evidence : `ev_5098fc51dfc0222223a7b04171a086268c1eb53c8fffad2ee94c4f38a8f8b5b0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x3d` — `KERNEL32.DLL::GetModuleFileNameA`
- `0x474d40` — `FUN_00474d40`
- `0x478690` — `__amsg_exit`
- `0x4811b0` — `FUN_004811b0`

### Chaînes référencées

- `0x495f0c` — "stdargv.c"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004810e0(void)

{
  char *local_18;
  int local_10;
  int local_c;
  int local_8;
  
  GetModuleFileNameA((HMODULE)0x0,&DAT_00632630,0x104);
  DAT_00632554 = &DAT_00632630;
  if (*DAT_00633e6c == '\0') {
    local_18 = &DAT_00632630;
  }
  else {
    local_18 = DAT_00633e6c;
  }
  FUN_004811b0(local_18,0,0,&local_10,&local_8);
  local_c = FUN_00474d40(local_8 + local_10 * 4,2,"stdargv.c",0x75);
  if (local_c == 0) {
    __amsg_exit(8);
  }
  FUN_004811b0(local_18,local_c,local_c + local_10 * 4,&local_10,&local_8);
  _DAT_00632538 = local_10 + -1;
  _DAT_0063253c = local_c;
  return;
}
```

---

---

## FUN_004811b0 — 0x4811b0

- Classification : internal
- Corps : `0x4811b0–0x4815d3`
- État : pseudocode obtenu
- Evidence : `ev_abf5a5f94d7a78d305f31fe63f3b6368dc4f6a64af0636ba6488834f8af7edb3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004811b0(byte *param_1,undefined4 *param_2,byte *param_3,int *param_4,int *param_5)

{
  byte bVar1;
  bool bVar2;
  byte *pbVar3;
  bool bVar4;
  uint local_14;
  byte *local_8;
  
  *param_5 = 0;
  *param_4 = 1;
  local_8 = param_1;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = param_3;
    param_2 = param_2 + 1;
  }
  if (*param_1 == 0x22) {
    while ((pbVar3 = local_8 + 1, *pbVar3 != 0x22 && (*pbVar3 != 0))) {
      if ((((&DAT_00632741)[*pbVar3] & 4) != 0) && (*param_5 = *param_5 + 1, param_3 != (byte *)0x0)
         ) {
        *param_3 = *pbVar3;
        param_3 = param_3 + 1;
        pbVar3 = local_8 + 2;
      }
      local_8 = pbVar3;
      *param_5 = *param_5 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *local_8;
        param_3 = param_3 + 1;
      }
    }
    *param_5 = *param_5 + 1;
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    if (*pbVar3 == 0x22) {
      pbVar3 = local_8 + 2;
    }
  }
  else {
    do {
      *param_5 = *param_5 + 1;
      if (param_3 != (byte *)0x0) {
        *param_3 = *local_8;
        param_3 = param_3 + 1;
      }
      bVar1 = *local_8;
      pbVar3 = local_8 + 1;
      if (((&DAT_00632741)[bVar1] & 4) != 0) {
        *param_5 = *param_5 + 1;
        if (param_3 != (byte *)0x0) {
          *param_3 = local_8[1];
          param_3 = param_3 + 1;
        }
        pbVar3 = local_8 + 2;
      }
      local_8 = pbVar3;
    } while (((bVar1 != 0x20) && (bVar1 != 0)) && (bVar1 != 9));
    if (bVar1 == 0) {
      pbVar3 = local_8 + -1;
    }
    else {
      pbVar3 = local_8;
      if (param_3 != (byte *)0x0) {
        param_3[-1] = 0;
      }
    }
  }
  local_8 = pbVar3;
  bVar2 = false;
  while( true ) {
    if (*local_8 != 0) {
      for (; (*local_8 == 0x20 || (*local_8 == 9)); local_8 = local_8 + 1) {
      }
    }
    if (*local_8 == 0) break;
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = param_3;
      param_2 = param_2 + 1;
    }
    *param_4 = *param_4 + 1;
    while( true ) {
      bVar4 = true;
      local_14 = 0;
      for (; *local_8 == 0x5c; local_8 = local_8 + 1) {
        local_14 = local_14 + 1;
      }
      if (*local_8 == 0x22) {
        if (local_14 % 2 == 0) {
          if (bVar2) {
            bVar4 = local_8[1] == 0x22;
            if (bVar4) {
              local_8 = local_8 + 1;
            }
          }
          else {
            bVar4 = false;
          }
          bVar2 = !bVar2;
        }
        local_14 = local_14 >> 1;
      }
      while (local_14 != 0) {
        if (param_3 != (byte *)0x0) {
          *param_3 = 0x5c;
          param_3 = param_3 + 1;
        }
        *param_5 = *param_5 + 1;
        local_14 = local_14 - 1;
      }
      if ((*local_8 == 0) || ((!bVar2 && ((*local_8 == 0x20 || (*local_8 == 9)))))) break;
      if (bVar4) {
        if (param_3 == (byte *)0x0) {
          if (((&DAT_00632741)[*local_8] & 4) != 0) {
            local_8 = local_8 + 1;
            *param_5 = *param_5 + 1;
          }
        }
        else {
          if (((&DAT_00632741)[*local_8] & 4) != 0) {
            *param_3 = *local_8;
            param_3 = param_3 + 1;
            local_8 = local_8 + 1;
            *param_5 = *param_5 + 1;
          }
          *param_3 = *local_8;
          param_3 = param_3 + 1;
        }
        *param_5 = *param_5 + 1;
      }
      local_8 = local_8 + 1;
    }
    if (param_3 != (byte *)0x0) {
      *param_3 = 0;
      param_3 = param_3 + 1;
    }
    *param_5 = *param_5 + 1;
  }
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = 0;
  }
  *param_4 = *param_4 + 1;
  return;
}
```

---

---

## FUN_004815e0 — 0x4815e0

- Classification : internal
- Corps : `0x4815e0–0x481858`
- État : pseudocode obtenu
- Evidence : `ev_21306ca318f1458b04dd70020076b7b7cc65ce3b6dd4856df24e43cb9fb444b9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x5` — `KERNEL32.DLL::MultiByteToWideChar`
- `EXTERNAL:0x1b` — `KERNEL32.DLL::GetEnvironmentStringsW`
- `EXTERNAL:0x1c` — `KERNEL32.DLL::GetEnvironmentStrings`
- `EXTERNAL:0x1d` — `KERNEL32.DLL::FreeEnvironmentStringsW`
- `EXTERNAL:0x1e` — `KERNEL32.DLL::FreeEnvironmentStringsA`
- `0x472e90` — `_strlen`
- `0x4734a0` — `FUN_004734a0`
- `0x474d40` — `FUN_00474d40`
- `0x475780` — `FUN_00475780`
- `0x488010` — `FUN_00488010`

### Chaînes référencées

- `0x495f18` — "aw_env.c"
- `0x495f18` — "aw_env.c"

### Pseudocode Ghidra

```c
void FUN_004815e0(void)

{
  LPWCH pWVar1;
  int iVar2;
  size_t sVar3;
  LPWSTR pWVar4;
  int iVar5;
  LPWCH local_18;
  LPWCH local_14;
  int local_10;
  LPWCH local_c;
  
  local_18 = (LPWCH)0x0;
  local_10 = 0;
  if (DAT_00632734 == 0) {
    local_18 = GetEnvironmentStringsW();
    if (local_18 == (LPWCH)0x0) {
      local_18 = (LPWCH)GetEnvironmentStrings();
      if (local_18 == (LPWCH)0x0) {
        return;
      }
      DAT_00632734 = 2;
    }
    else {
      DAT_00632734 = 1;
    }
  }
  if (DAT_00632734 == 1) {
    if ((local_18 != (LPWCH)0x0) || (local_18 = GetEnvironmentStringsW(), local_18 != (LPWCH)0x0)) {
      local_14 = local_18;
      pWVar1 = local_14;
      while (local_14 = pWVar1, *local_14 != L'\0') {
        pWVar1 = local_14 + 1;
        if (local_14[1] == L'\0') {
          pWVar1 = local_14 + 2;
        }
      }
      iVar5 = (int)local_14 + (2 - (int)local_18);
      iVar2 = FUN_00474d40(iVar5,2,"aw_env.c",0x57);
      if (iVar2 == 0) {
        FreeEnvironmentStringsW(local_18);
      }
      else {
        FUN_004734a0(iVar2,local_18,iVar5);
        FreeEnvironmentStringsW(local_18);
      }
    }
  }
  else if ((DAT_00632734 == 2) &&
          ((local_18 != (LPWCH)0x0 ||
           (local_18 = (LPWCH)GetEnvironmentStrings(), local_18 != (LPWCH)0x0)))) {
    for (local_c = local_18; (char)*local_c != '\0'; local_c = (LPWCH)((int)local_c + sVar3 + 1)) {
      iVar2 = MultiByteToWideChar(DAT_006325f8,1,(LPCSTR)local_c,-1,(LPWSTR)0x0,0);
      if (iVar2 == 0) {
        return;
      }
      local_10 = local_10 + iVar2;
      sVar3 = _strlen((char *)local_c);
    }
    pWVar4 = (LPWSTR)FUN_00474d40((local_10 + 1) * 2,2,"aw_env.c",0x87);
    if (pWVar4 == (LPWSTR)0x0) {
      FreeEnvironmentStringsA((LPCH)local_18);
    }
    else {
      local_c = local_18;
      local_14 = pWVar4;
      while ((char)*local_c != '\0') {
        iVar2 = MultiByteToWideChar(DAT_006325f8,1,(LPCSTR)local_c,-1,local_14,
                                    (local_10 + 1) - ((int)local_14 - (int)pWVar4 >> 1));
        if (iVar2 == 0) {
          FUN_00475780(pWVar4,2);
          FreeEnvironmentStringsA((LPCH)local_18);
          return;
        }
        sVar3 = _strlen((char *)local_c);
        local_c = (LPWCH)((int)local_c + sVar3 + 1);
        iVar2 = FUN_00488010(local_14);
        local_14 = local_14 + iVar2 + 1;
      }
      *local_14 = L'\0';
      FreeEnvironmentStringsA((LPCH)local_18);
    }
  }
  return;
}
```

---

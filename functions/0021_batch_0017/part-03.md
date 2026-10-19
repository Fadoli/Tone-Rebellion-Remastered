# 0021_batch_0017 — détails (3/5)

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

## FUN_00481860 — 0x481860

- Classification : internal
- Corps : `0x481860–0x481a7b`
- État : pseudocode obtenu
- Evidence : `ev_aac81a6e987c3e253a9652a95ef78444556e677391e7a8cca87622dbed09131c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x7` — `KERNEL32.DLL::WideCharToMultiByte`
- `EXTERNAL:0x1b` — `KERNEL32.DLL::GetEnvironmentStringsW`
- `EXTERNAL:0x1c` — `KERNEL32.DLL::GetEnvironmentStrings`
- `EXTERNAL:0x1d` — `KERNEL32.DLL::FreeEnvironmentStringsW`
- `EXTERNAL:0x1e` — `KERNEL32.DLL::FreeEnvironmentStringsA`
- `0x4734a0` — `FUN_004734a0`
- `0x474d40` — `FUN_00474d40`
- `0x475780` — `FUN_00475780`

### Chaînes référencées

- `0x495f18` — "aw_env.c"
- `0x495f18` — "aw_env.c"

### Pseudocode Ghidra

```c
LPSTR FUN_00481860(void)

{
  char *pcVar1;
  LPWCH pWVar2;
  int iVar3;
  LPSTR pCVar4;
  int cchWideChar;
  LPCH local_1c;
  LPWCH local_18;
  char *local_10;
  LPWCH local_c;
  
  local_18 = (LPWCH)0x0;
  local_1c = (LPCH)0x0;
  if (DAT_00632738 == 0) {
    local_18 = GetEnvironmentStringsW();
    if (local_18 == (LPWCH)0x0) {
      local_1c = GetEnvironmentStrings();
      if (local_1c == (LPCH)0x0) {
        return (LPSTR)0x0;
      }
      DAT_00632738 = 2;
    }
    else {
      DAT_00632738 = 1;
    }
  }
  if (DAT_00632738 == 1) {
    if ((local_18 == (LPWCH)0x0) && (local_18 = GetEnvironmentStringsW(), local_18 == (LPWCH)0x0)) {
      pCVar4 = (LPSTR)0x0;
    }
    else {
      local_c = local_18;
      pWVar2 = local_c;
      while (local_c = pWVar2, *local_c != L'\0') {
        pWVar2 = local_c + 1;
        if (local_c[1] == L'\0') {
          pWVar2 = local_c + 2;
        }
      }
      cchWideChar = ((int)local_c - (int)local_18 >> 1) + 1;
      iVar3 = WideCharToMultiByte(0,0,local_18,cchWideChar,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
      if ((iVar3 == 0) ||
         (local_1c = (LPCH)FUN_00474d40(iVar3,2,"aw_env.c",0xfb), local_1c == (LPSTR)0x0)) {
        FreeEnvironmentStringsW(local_18);
        pCVar4 = (LPSTR)0x0;
      }
      else {
        iVar3 = WideCharToMultiByte(0,0,local_18,cchWideChar,local_1c,iVar3,(LPCSTR)0x0,(LPBOOL)0x0)
        ;
        if (iVar3 == 0) {
          FUN_00475780(local_1c,2);
          local_1c = (LPSTR)0x0;
        }
        FreeEnvironmentStringsW(local_18);
        pCVar4 = local_1c;
      }
    }
  }
  else if (DAT_00632738 == 2) {
    if ((local_1c == (LPCH)0x0) && (local_1c = GetEnvironmentStrings(), local_1c == (LPCH)0x0)) {
      pCVar4 = (LPSTR)0x0;
    }
    else {
      local_10 = local_1c;
      pcVar1 = local_10;
      while (local_10 = pcVar1, *local_10 != '\0') {
        pcVar1 = local_10 + 1;
        if (local_10[1] == '\0') {
          pcVar1 = local_10 + 2;
        }
      }
      pCVar4 = (LPSTR)FUN_00474d40(local_10 + (1 - (int)local_1c),2,"aw_env.c",0x126);
      if (pCVar4 == (LPSTR)0x0) {
        FreeEnvironmentStringsA(local_1c);
        pCVar4 = (LPSTR)0x0;
      }
      else {
        FUN_004734a0(pCVar4,local_1c,local_10 + (1 - (int)local_1c));
        FreeEnvironmentStringsA(local_1c);
      }
    }
  }
  else {
    pCVar4 = (LPSTR)0x0;
  }
  return pCVar4;
}
```

---

## FUN_00481a80 — 0x481a80

- Classification : internal
- Corps : `0x481a80–0x481d54`
- État : pseudocode obtenu
- Evidence : `ev_aa1722ca69bd9e75a0c6e62ac142d82cfdd9ece6a41ecb4e579cbf30efc95268`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x1a` — `KERNEL32.DLL::GetCPInfo`
- `0x481d60` — `getSystemCP`
- `0x481dc0` — `FUN_00481dc0`
- `0x481e40` — `FUN_00481e40`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00481a80(undefined4 param_1)

{
  UINT CodePage;
  undefined4 uVar1;
  BOOL BVar2;
  BYTE *local_2c;
  uint local_28;
  _cpinfo local_24;
  uint local_10;
  byte *local_c;
  uint local_8;
  
  CodePage = getSystemCP(param_1);
  if (CodePage == DAT_00632844) {
    uVar1 = 0;
  }
  else if (CodePage == 0) {
    FUN_00481e40();
    uVar1 = 0;
  }
  else {
    for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
      if (*(UINT *)(&DAT_004a8940 + local_8 * 0x30) == CodePage) {
        for (local_28 = 0; local_28 < 0x101; local_28 = local_28 + 1) {
          (&DAT_00632740)[local_28] = 0;
        }
        for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
          for (local_c = &DAT_004a8950 + local_10 * 8 + local_8 * 0x30;
              (*local_c != 0 && (local_c[1] != 0)); local_c = local_c + 2) {
            for (local_28 = (uint)*local_c; local_28 <= local_c[1]; local_28 = local_28 + 1) {
              (&DAT_00632741)[local_28] = (&DAT_00632741)[local_28] | (&DAT_004a8938)[local_10];
            }
          }
        }
        DAT_00632844 = CodePage;
        DAT_00632848 = FUN_00481dc0(CodePage);
        for (local_10 = 0; local_10 < 6; local_10 = local_10 + 1) {
          *(undefined2 *)(&DAT_00632850 + local_10 * 2) =
               *(undefined2 *)(&DAT_004a8944 + local_10 * 2 + local_8 * 0x30);
        }
        return 0;
      }
    }
    BVar2 = GetCPInfo(CodePage,&local_24);
    if (BVar2 == 1) {
      for (local_28 = 0; local_28 < 0x101; local_28 = local_28 + 1) {
        (&DAT_00632740)[local_28] = 0;
      }
      if (local_24.MaxCharSize < 2) {
        DAT_00632844 = 0;
        DAT_00632848 = 0;
      }
      else {
        for (local_2c = local_24.LeadByte; (*local_2c != 0 && (local_2c[1] != 0));
            local_2c = local_2c + 2) {
          for (local_28 = (uint)*local_2c; local_28 <= local_2c[1]; local_28 = local_28 + 1) {
            (&DAT_00632741)[local_28] = (&DAT_00632741)[local_28] | 4;
          }
        }
        for (local_28 = 1; local_28 < 0xff; local_28 = local_28 + 1) {
          (&DAT_00632741)[local_28] = (&DAT_00632741)[local_28] | 8;
        }
        DAT_00632844 = CodePage;
        DAT_00632848 = FUN_00481dc0(CodePage);
      }
      for (local_10 = 0; local_10 < 6; local_10 = local_10 + 1) {
        *(undefined2 *)(&DAT_00632850 + local_10 * 2) = 0;
      }
      uVar1 = 0;
    }
    else if (DAT_0063285c == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      FUN_00481e40();
      uVar1 = 0;
    }
  }
  return uVar1;
}
```

---

## getSystemCP — 0x481d60

- Classification : internal
- Corps : `0x481d60–0x481db8`
- État : pseudocode obtenu
- Evidence : `ev_3c12f7487552e91a757da612cfcaeba337361f1456c0ef85848b05de5ed03d5a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x18` — `KERNEL32.DLL::GetOEMCP`
- `EXTERNAL:0x19` — `KERNEL32.DLL::GetACP`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _getSystemCP
   
   Library: Visual Studio 2003 Debug */

UINT __cdecl getSystemCP(UINT param_1)

{
  DAT_0063285c = 0;
  if (param_1 == 0xfffffffe) {
    DAT_0063285c = 1;
    param_1 = GetOEMCP();
  }
  else if (param_1 == 0xfffffffd) {
    DAT_0063285c = 1;
    param_1 = GetACP();
  }
  else if (param_1 == 0xfffffffc) {
    DAT_0063285c = 1;
    param_1 = DAT_006325f8;
  }
  return param_1;
}
```

---

## FUN_00481dc0 — 0x481dc0

- Classification : internal
- Corps : `0x481dc0–0x481e0f`
- État : pseudocode obtenu
- Evidence : `ev_e180aaded969ad4181298e7cfdb632c7d254e6cb0f0f58a3f05c657f0fd29272`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00481dc0(undefined4 param_1)

{
  undefined4 uVar1;
  
  switch(param_1) {
  case 0x3a4:
    uVar1 = 0x411;
    break;
  default:
    uVar1 = 0;
    break;
  case 0x3a8:
    uVar1 = 0x804;
    break;
  case 0x3b5:
    uVar1 = 0x412;
    break;
  case 0x3b6:
    uVar1 = 0x404;
  }
  return uVar1;
}
```

---

## FUN_00481e40 — 0x481e40

- Classification : internal
- Corps : `0x481e40–0x481ea9`
- État : pseudocode obtenu
- Evidence : `ev_a5758ee842741d7d203e26b6f404cdc1e2fba820bdecf70fa6c9530155ede576`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00481e40(void)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 0x101; local_8 = local_8 + 1) {
    (&DAT_00632740)[local_8] = 0;
  }
  DAT_00632844 = 0;
  DAT_00632848 = 0;
  for (local_8 = 0; local_8 < 6; local_8 = local_8 + 1) {
    *(undefined2 *)(&DAT_00632850 + local_8 * 2) = 0;
  }
  return;
}
```

---

## FUN_00481eb0 — 0x481eb0

- Classification : internal
- Corps : `0x481eb0–0x481eb9`
- État : pseudocode obtenu
- Evidence : `ev_6d45d883fa76bd3e544ef3f515369859b84ca8604fa9650a4ba2ce1de1f5dd8d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00481eb0(void)

{
  return DAT_00632844;
}
```

---

## FUN_00481ec0 — 0x481ec0

- Classification : internal
- Corps : `0x481ec0–0x481ece`
- État : pseudocode obtenu
- Evidence : `ev_cdba735551ea0d6026442ea6faa3cdfc33a8cf80f15214431f5eb11a21b95c2a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x481a80` — `FUN_00481a80`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00481ec0(void)

{
  FUN_00481a80(0xfffffffd);
  return;
}
```

---

## __FF_MSGBANNER — 0x481ed0

- Classification : internal
- Corps : `0x481ed0–0x481f18`
- État : pseudocode obtenu
- Evidence : `ev_235a5bd9b6f73cb02f57b0599714cd0d0324318ae3115e66d26795f983e0242a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x481f20` — `FUN_00481f20`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __FF_MSGBANNER
   
   Library: Visual Studio 2003 Debug */

void __cdecl __FF_MSGBANNER(void)

{
  if ((DAT_00632578 == 1) || ((DAT_00632578 == 0 && (DAT_004a63d4 == 1)))) {
    FUN_00481f20(0xfc);
    if (DAT_00632860 != (code *)0x0) {
      (*DAT_00632860)();
    }
    FUN_00481f20(0xff);
  }
  return;
}
```

---

## FUN_00481f20 — 0x481f20

- Classification : internal
- Corps : `0x481f20–0x482110`
- État : pseudocode obtenu
- Evidence : `ev_dd0849b98292044b9b00d25c4f148149b15de82e222b70c9704385f8b248c84f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x481f93 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `EXTERNAL:0xa` — `KERNEL32.DLL::GetStdHandle`
- `EXTERNAL:0x3b` — `KERNEL32.DLL::WriteFile`
- `EXTERNAL:0x3d` — `KERNEL32.DLL::GetModuleFileNameA`
- `0x472da0` — `FUN_00472da0`
- `0x472db0` — `FUN_00472db0`
- `0x472e90` — `_strlen`
- `0x4737e0` — `_strncpy`
- `0x47a120` — `FUN_0047a120`
- `0x484240` — `FUN_00484240`

### Chaînes référencées

- `0x495d0c` — "<program name unknown>"
- `0x4961b0` — "Microsoft Visual C++ Runtime Library"
- `0x4961d8` — "Runtime Error!\n\nProgram: "

### Pseudocode Ghidra

```c
void FUN_00481f20(int param_1)

{
  code *pcVar1;
  int iVar2;
  size_t sVar3;
  DWORD DVar4;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  HANDLE local_1b8;
  undefined1 local_1b4 [160];
  CHAR local_114 [260];
  char *local_10;
  uint local_c;
  DWORD local_8;
  
  for (local_c = 0; (local_c < 0x12 && (param_1 != *(int *)(&DAT_004a8a30 + local_c * 8)));
      local_c = local_c + 1) {
  }
  if (param_1 == *(int *)(&DAT_004a8a30 + local_c * 8)) {
    if ((param_1 != 0xfc) &&
       (iVar2 = FUN_0047a120(1,0,0,0,(&PTR_s_R6002___floating_point_not_loade_004a8a34)[local_c * 2]
                            ), iVar2 == 1)) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    if ((DAT_00632578 == 1) || ((DAT_00632578 == 0 && (DAT_004a63d4 == 1)))) {
      if ((DAT_00633d20 == 0) || (*(int *)(DAT_00633d20 + 0x10) == -1)) {
        local_1b8 = GetStdHandle(0xfffffff4);
      }
      else {
        local_1b8 = *(HANDLE *)(DAT_00633d20 + 0x10);
      }
      lpOverlapped = (LPOVERLAPPED)0x0;
      lpNumberOfBytesWritten = &local_8;
      sVar3 = _strlen((&PTR_s_R6002___floating_point_not_loade_004a8a34)[local_c * 2]);
      WriteFile(local_1b8,(&PTR_s_R6002___floating_point_not_loade_004a8a34)[local_c * 2],sVar3,
                lpNumberOfBytesWritten,lpOverlapped);
    }
    else if (param_1 != 0xfc) {
      DVar4 = GetModuleFileNameA((HMODULE)0x0,local_114,0x104);
      if (DVar4 == 0) {
        FUN_00472da0(local_114,"<program name unknown>");
      }
      local_10 = local_114;
      sVar3 = _strlen(local_10);
      if (0x3c < sVar3 + 1) {
        sVar3 = _strlen(local_114);
        local_10 = local_10 + (sVar3 - 0x3b);
        _strncpy(local_10,"...",3);
      }
      FUN_00472da0(local_1b4,"Runtime Error!\n\nProgram: ");
      FUN_00472db0(local_1b4,local_10);
      FUN_00472db0(local_1b4,&DAT_00495c7c);
      FUN_00472db0(local_1b4,(&PTR_s_R6002___floating_point_not_loade_004a8a34)[local_c * 2]);
      FUN_00484240(local_1b4,"Microsoft Visual C++ Runtime Library",0x12010);
    }
  }
  return;
}
```

---

## __GET_RTERRMSG — 0x482120

- Classification : internal
- Corps : `0x482120–0x48216f`
- État : pseudocode obtenu
- Evidence : `ev_bcfa0a30f522e2b0a332acddba6630a50e1879262d6558a2b1842b5e0660bd8f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __GET_RTERRMSG
   
   Library: Visual Studio 2003 Debug */

wchar_t * __cdecl __GET_RTERRMSG(int param_1)

{
  wchar_t *pwVar1;
  uint local_8;
  
  for (local_8 = 0; (local_8 < 0x12 && (param_1 != *(int *)(&DAT_004a8a30 + local_8 * 8)));
      local_8 = local_8 + 1) {
  }
  if (param_1 == *(int *)(&DAT_004a8a30 + local_8 * 8)) {
    pwVar1 = (wchar_t *)(&PTR_s_R6002___floating_point_not_loade_004a8a34)[local_8 * 2];
  }
  else {
    pwVar1 = (wchar_t *)0x0;
  }
  return pwVar1;
}
```

---

## FUN_00482170 — 0x482170

- Classification : internal
- Corps : `0x482170–0x48218e`
- État : pseudocode obtenu
- Evidence : `ev_74e8d568f28cdc971932c1c44dee143004f7c8b6273135ca237f41a4d60280ae`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482560` — `FUN_00482560`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00482170(void)

{
  FUN_00482560();
  return;
}
```

---

## FUN_00482190 — 0x482190

- Classification : internal
- Corps : `0x482190–0x4821af`
- État : pseudocode obtenu
- Evidence : `ev_235de416c2dc2beb8180bbbff878e422ad8221ed97858b13087d0a554171426c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482560` — `FUN_00482560`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00482190(void)

{
  FUN_00482560();
  return;
}
```

---

## FUN_004821b0 — 0x4821b0

- Classification : internal
- Corps : `0x4821b0–0x4821fe`
- État : pseudocode obtenu
- Evidence : `ev_befc470f8d91a44045cba47140808d7f0e46e7a158a318486793cf2bf8d83512`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482280` — `FUN_00482280`
- `0x482400` — `FUN_00482400`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_004821b0(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = FUN_00482280();
  uVar1 = param_1 & param_2 | uVar1 & ~param_2;
  FUN_00482400(uVar1);
  return uVar1;
}
```

---

## __controlfp — 0x482200

- Classification : internal
- Corps : `0x482200–0x482219`
- État : pseudocode obtenu
- Evidence : `ev_fbae25ac6350f6bbd7f50f5c210b209fd36e0f0a645beb1eb04e1c35c8d46ab7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4821b0` — `FUN_004821b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __controlfp
   
   Library: Visual Studio 2003 Debug */

uint __cdecl __controlfp(uint _NewValue,uint _Mask)

{
  uint uVar1;
  
  uVar1 = FUN_004821b0(_NewValue,_Mask & 0xfff7ffff);
  return uVar1;
}
```

---

## FUN_00482220 — 0x482220

- Classification : internal
- Corps : `0x482220–0x482275`
- État : pseudocode obtenu
- Evidence : `ev_c133961885c50b991e211335309677e7c0f0d326d5b0c326987ff151127fdbe3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4786c0` — `__setdefaultprecision`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00482220(void)

{
  int iVar1;
  
  iVar1 = DAT_0063262c;
  __setdefaultprecision();
  if ((iVar1 != 0) && ((**(uint **)(iVar1 + 4) & 0x10008) != 0)) {
    iVar1 = *(int *)(iVar1 + 4);
    *(undefined4 *)(iVar1 + 0x20) = 0;
    *(undefined4 *)(iVar1 + 0x24) = 0xffff;
  }
  return;
}
```

---


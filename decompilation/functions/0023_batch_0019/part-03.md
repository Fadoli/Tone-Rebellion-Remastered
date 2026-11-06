# Lot 0019 — détails des procédures (3/4)



## FUN_0048aa70 — 0x48aa70

- Classification : internal
- Corps : `0x48aa70–0x48ad4f`
- État : pseudocode obtenu
- Evidence : `ev_7baf52f11751cf4aaa5ebf088a83538756b207aac228ff14518cf14d8d058fb4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x31` — `KERNEL32.DLL::SetEnvironmentVariableA`
- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`
- `0x474d40` — `FUN_00474d40`
- `0x4751c0` — `__realloc_dbg`
- `0x475780` — `FUN_00475780`
- `0x48a2b0` — `FUN_0048a2b0`
- `0x48ad50` — `findenv`
- `0x48add0` — `copy_environ`
- `0x48aec0` — `FUN_0048aec0`

### Chaînes référencées

- `0x49645c` — "setenv.c"
- `0x49645c` — "setenv.c"
- `0x49645c` — "setenv.c"
- `0x49645c` — "setenv.c"
- `0x49645c` — "setenv.c"

### Pseudocode Ghidra

```c
undefined4 FUN_0048aa70(char *param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  int *piVar3;
  size_t sVar4;
  LPCSTR lpName;
  bool bVar5;
  undefined4 uVar6;
  char *pcVar7;
  undefined4 uVar8;
  int local_c;
  
  if (((param_1 == (char *)0x0) ||
      (pcVar1 = (char *)FUN_0048aec0(param_1,0x3d), pcVar1 == (char *)0x0)) || (param_1 == pcVar1))
  {
    return 0xffffffff;
  }
  bVar5 = pcVar1[1] == '\0';
  if (DAT_00632544 == DAT_00632548) {
    DAT_00632544 = (int *)copy_environ(DAT_00632544);
  }
  if (DAT_00632544 == (int *)0x0) {
    if ((param_2 == 0) || (DAT_0063254c == (undefined4 *)0x0)) {
      if (bVar5) {
        return 0;
      }
      DAT_00632544 = (int *)FUN_00474d40(4,2,"setenv.c",0x87);
      if (DAT_00632544 == (int *)0x0) {
        return 0xffffffff;
      }
      *DAT_00632544 = 0;
      if (DAT_0063254c == (undefined4 *)0x0) {
        DAT_0063254c = (undefined4 *)FUN_00474d40(4,2,"setenv.c",0x8e);
        if (DAT_0063254c == (undefined4 *)0x0) {
          return 0xffffffff;
        }
        *DAT_0063254c = 0;
      }
    }
    else {
      iVar2 = FUN_0048a2b0();
      if (iVar2 != 0) {
        return 0xffffffff;
      }
    }
  }
  piVar3 = DAT_00632544;
  local_c = findenv(param_1,(int)pcVar1 - (int)param_1);
  if ((local_c < 0) || (*piVar3 == 0)) {
    if (bVar5) {
      return 0;
    }
    if (local_c < 0) {
      local_c = -local_c;
    }
    piVar3 = (int *)__realloc_dbg(piVar3,local_c * 4 + 8,2,"setenv.c",0xce);
    if (piVar3 == (int *)0x0) {
      return 0xffffffff;
    }
    piVar3[local_c] = (int)param_1;
    piVar3[local_c + 1] = 0;
    DAT_00632544 = piVar3;
  }
  else if (bVar5) {
    FUN_00475780(piVar3[local_c],2);
    for (; piVar3[local_c] != 0; local_c = local_c + 1) {
      piVar3[local_c] = piVar3[local_c + 1];
    }
    piVar3 = (int *)__realloc_dbg(piVar3,local_c << 2,2,"setenv.c",0xb9);
    if (piVar3 != (int *)0x0) {
      DAT_00632544 = piVar3;
    }
  }
  else {
    piVar3[local_c] = (int)param_1;
  }
  if (param_2 != 0) {
    uVar8 = 0xe5;
    pcVar7 = "setenv.c";
    uVar6 = 2;
    sVar4 = _strlen(param_1);
    lpName = (LPCSTR)FUN_00474d40(sVar4 + 2,uVar6,pcVar7,uVar8);
    if (lpName != (LPCSTR)0x0) {
      FUN_00472da0(lpName,param_1);
      lpName[(int)pcVar1 - (int)param_1] = '\0';
      SetEnvironmentVariableA
                (lpName,(LPCSTR)(~-(uint)bVar5 & (uint)(lpName + ((int)pcVar1 - (int)param_1) + 1)))
      ;
      FUN_00475780(lpName,2);
    }
  }
  return 0;
}
```

---

## findenv — 0x48ad50

- Classification : internal
- Corps : `0x48ad50–0x48adcb`
- État : pseudocode obtenu
- Evidence : `ev_78b82ba54433ad6b72c149f372c03b90fa3186fc0df46e95b8159dcc7ecf234c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x48a260` — `__mbsnbicoll`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _findenv
   
   Library: Visual Studio 2003 Debug */

int __cdecl findenv(uchar *param_1,size_t param_2)

{
  int iVar1;
  int *local_8;
  
  local_8 = DAT_00632544;
  while( true ) {
    if (*local_8 == 0) {
      return -((int)local_8 - (int)DAT_00632544 >> 2);
    }
    iVar1 = __mbsnbicoll(param_1,(uchar *)*local_8,param_2);
    if ((iVar1 == 0) &&
       ((*(char *)(*local_8 + param_2) == '=' || (*(char *)(*local_8 + param_2) == '\0')))) break;
    local_8 = local_8 + 1;
  }
  return (int)local_8 - (int)DAT_00632544 >> 2;
}
```

---

## copy_environ — 0x48add0

- Classification : internal
- Corps : `0x48add0–0x48aebd`
- État : pseudocode obtenu
- Evidence : `ev_80c2e71b7652f21d93644bd43ed357f17491b2b1c89e1311923e53532a03a0a2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`
- `0x474d40` — `FUN_00474d40`
- `0x478690` — `__amsg_exit`

### Chaînes référencées

- `0x49645c` — "setenv.c"
- `0x49645c` — "setenv.c"

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _copy_environ
   
   Library: Visual Studio 2003 Debug */

int * __cdecl copy_environ(int *param_1)

{
  int *piVar1;
  size_t sVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined4 uVar6;
  int local_14;
  int *local_10;
  int *local_c;
  
  local_14 = 0;
  local_10 = param_1;
  if (param_1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    while (iVar3 = *local_10, local_10 = local_10 + 1, iVar3 != 0) {
      local_14 = local_14 + 1;
    }
    piVar1 = (int *)FUN_00474d40(local_14 * 4 + 4,2,"setenv.c",0x146);
    if (piVar1 == (int *)0x0) {
      __amsg_exit(9);
    }
    local_c = piVar1;
    for (local_10 = param_1; *local_10 != 0; local_10 = local_10 + 1) {
      uVar6 = 0x14f;
      pcVar5 = "setenv.c";
      uVar4 = 2;
      sVar2 = _strlen((char *)*local_10);
      iVar3 = FUN_00474d40(sVar2 + 1,uVar4,pcVar5,uVar6);
      *local_c = iVar3;
      if (*local_c != 0) {
        FUN_00472da0(*local_c,*local_10);
      }
      local_c = local_c + 1;
    }
    *local_c = 0;
  }
  return piVar1;
}
```

---

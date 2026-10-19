# Lot 0019 — détails des procédures (1/4)



## FUN_0048a130 — 0x48a130

- Classification : internal
- Corps : `0x48a130–0x48a190`
- État : pseudocode obtenu
- Evidence : `ev_47519d7ba96cc07267dcb17f5cec5d21fe959a7c64b0db9123b8c4636782172e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0048a130(short *param_1,int param_2)

{
  int local_c;
  short *local_8;
  
  local_c = param_2 + 1;
  for (local_8 = param_1; (local_c = local_c + -1, local_c != 0 && (*local_8 != 0));
      local_8 = local_8 + 1) {
  }
  if ((local_c != 0) && (*local_8 == 0)) {
    param_2 = ((int)local_8 - (int)param_1 >> 1) + 1;
  }
  return param_2;
}
```

---

## FUN_0048a1a0 — 0x48a1a0

- Classification : internal
- Corps : `0x48a1a0–0x48a255`
- État : pseudocode obtenu
- Evidence : `ev_ba7e1a1664107c9407d50eec320be98ed0e6e159dadda353222ff36d6c4282f3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472e90` — `_strlen`
- `0x48a260` — `__mbsnbicoll`
- `0x48a2b0` — `FUN_0048a2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0048a1a0(uchar *param_1)

{
  int iVar1;
  size_t _MaxCount;
  size_t sVar2;
  int *local_c;
  
  local_c = DAT_00632544;
  if ((DAT_00632544 == (int *)0x0) && (DAT_0063254c != 0)) {
    iVar1 = FUN_0048a2b0();
    if (iVar1 != 0) {
      return 0;
    }
    local_c = DAT_00632544;
  }
  DAT_00632544 = local_c;
  if ((local_c != (int *)0x0) && (param_1 != (uchar *)0x0)) {
    _MaxCount = _strlen((char *)param_1);
    for (; *local_c != 0; local_c = local_c + 1) {
      sVar2 = _strlen((char *)*local_c);
      if (((_MaxCount < sVar2) && (*(char *)(*local_c + _MaxCount) == '=')) &&
         (iVar1 = __mbsnbicoll((uchar *)*local_c,param_1,_MaxCount), iVar1 == 0)) {
        return *local_c + 1 + _MaxCount;
      }
    }
  }
  return 0;
}
```

---

## __mbsnbicoll — 0x48a260

- Classification : internal
- Corps : `0x48a260–0x48a2ae`
- État : pseudocode obtenu
- Evidence : `ev_e333d412ed9865f8800713936c5122a9f1a8e1fa2b96a6b0b7a7bc072be42640`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x48a660` — `FUN_0048a660`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __mbsnbicoll
   
   Library: Visual Studio 2003 Debug */

int __cdecl __mbsnbicoll(uchar *_Str1,uchar *_Str2,size_t _MaxCount)

{
  int iVar1;
  
  if (_MaxCount == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = FUN_0048a660(DAT_00632848,1,_Str1,_MaxCount,_Str2,_MaxCount,DAT_00632844);
    if (iVar1 == 0) {
      iVar1 = 0x7fffffff;
    }
    else {
      iVar1 = iVar1 + -2;
    }
  }
  return iVar1;
}
```

---

## FUN_0048a2b0 — 0x48a2b0

- Classification : internal
- Corps : `0x48a2b0–0x48a35d`
- État : pseudocode obtenu
- Evidence : `ev_c9f79160d6493eeb3e6830abd2068971ac3281384d04ce9a49f4575eada13c54`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x7` — `KERNEL32.DLL::WideCharToMultiByte`
- `0x474d40` — `FUN_00474d40`
- `0x48aa70` — `FUN_0048aa70`

### Chaînes référencées

- `0x496404` — "wtombenv.c"

### Pseudocode Ghidra

```c
undefined4 FUN_0048a2b0(void)

{
  int iVar1;
  LPSTR lpMultiByteStr;
  int *local_8;
  
  local_8 = DAT_0063254c;
  while( true ) {
    if (*local_8 == 0) {
      return 0;
    }
    iVar1 = WideCharToMultiByte(1,0,(LPCWSTR)*local_8,-1,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
    if (iVar1 == 0) {
      return 0xffffffff;
    }
    lpMultiByteStr = (LPSTR)FUN_00474d40(iVar1,2,"wtombenv.c",0x3d);
    if (lpMultiByteStr == (LPSTR)0x0) {
      return 0xffffffff;
    }
    iVar1 = WideCharToMultiByte(1,0,(LPCWSTR)*local_8,-1,lpMultiByteStr,iVar1,(LPCSTR)0x0,
                                (LPBOOL)0x0);
    if (iVar1 == 0) break;
    FUN_0048aa70(lpMultiByteStr,0);
    local_8 = local_8 + 1;
  }
  return 0xffffffff;
}
```

---

## FUN_0048a360 — 0x48a360

- Classification : internal
- Corps : `0x48a360–0x48a5f1`
- État : pseudocode obtenu
- Evidence : `ev_509230709d3769c7535261b0bfe619dd9970b6144fbbbbe3639887d6418f8011`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x7` — `KERNEL32.DLL::WideCharToMultiByte`
- `EXTERNAL:0x32` — `KERNEL32.DLL::CompareStringW`
- `EXTERNAL:0x33` — `KERNEL32.DLL::CompareStringA`
- `0x474d40` — `FUN_00474d40`
- `0x475780` — `FUN_00475780`
- `0x48a600` — `FUN_0048a600`

### Chaînes référencées

- `0x496410` — "aw_cmp.c"
- `0x496410` — "aw_cmp.c"

### Pseudocode Ghidra

```c
void FUN_0048a360(LCID param_1,DWORD param_2,PCNZWCH param_3,int param_4,LPCWSTR param_5,int param_6
                 ,UINT param_7)

{
  int iVar1;
  PCNZCH lpMultiByteStr;
  int iVar2;
  int iVar3;
  LPSTR local_8;
  
  if (DAT_006329b4 == 0) {
    iVar1 = CompareStringW(0,0,L"",1,L"",1);
    if (iVar1 == 0) {
      iVar1 = CompareStringA(0,0,"",1,"",1);
      if (iVar1 == 0) {
        return;
      }
      DAT_006329b4 = 2;
    }
    else {
      DAT_006329b4 = 1;
    }
  }
  if (0 < param_4) {
    param_4 = FUN_0048a600(param_3,param_4);
  }
  if (0 < param_6) {
    param_6 = FUN_0048a600(param_5,param_6);
  }
  if ((param_4 != 0) && (param_6 != 0)) {
    if (DAT_006329b4 == 1) {
      CompareStringW(param_1,param_2,param_3,param_4,param_5,param_6);
    }
    else if (DAT_006329b4 == 2) {
      local_8 = (LPSTR)0x0;
      if (param_7 == 0) {
        param_7 = DAT_006325f8;
      }
      iVar1 = WideCharToMultiByte(param_7,0x220,param_3,param_4,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0
                                 );
      if ((iVar1 != 0) &&
         (lpMultiByteStr = (PCNZCH)FUN_00474d40(iVar1,2,"aw_cmp.c",0xc4),
         lpMultiByteStr != (PCNZCH)0x0)) {
        iVar2 = WideCharToMultiByte(param_7,0x220,param_3,param_4,lpMultiByteStr,iVar1,(LPCSTR)0x0,
                                    (LPBOOL)0x0);
        if ((iVar2 == 0) ||
           (((iVar2 = WideCharToMultiByte(param_7,0x220,param_5,param_6,(LPSTR)0x0,0,(LPCSTR)0x0,
                                          (LPBOOL)0x0), iVar2 == 0 ||
             (local_8 = (LPSTR)FUN_00474d40(iVar2,2,"aw_cmp.c",0xd5), local_8 == (LPSTR)0x0)) ||
            (iVar3 = WideCharToMultiByte(param_7,0x220,param_5,param_6,local_8,iVar2,(LPCSTR)0x0,
                                         (LPBOOL)0x0), iVar3 == 0)))) {
          FUN_00475780(lpMultiByteStr,2);
          FUN_00475780(local_8,2);
        }
        else {
          CompareStringA(param_1,param_2,lpMultiByteStr,iVar1,local_8,iVar2);
          FUN_00475780(lpMultiByteStr,2);
          FUN_00475780(local_8,2);
        }
      }
    }
  }
  return;
}
```

---

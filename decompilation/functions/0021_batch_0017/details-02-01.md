# 0021_batch_0017 — détails (1/3)

## FUN_0047fcc0 — 0x47fcc0

- Classification : internal
- Corps : `0x47fcc0–0x47fd3f`
- État : pseudocode obtenu
- Evidence : `ev_20a7505712fcbd0ec48ebdb05bcfa000ec84f76a574e267d55cbfd21846e9807`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x486f70` — `FUN_00486f70`
- `0x487500` — `FUN_00487500`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047fcc0(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  float10 fVar3;
  
  uVar1 = FUN_00487500(param_1,param_2);
  if ((uVar1 & 0x90) == 0) {
    fVar3 = (float10)FUN_00486f70(param_1,param_2);
    if ((double)fVar3 == (double)CONCAT44(param_2,param_1)) {
      fVar3 = (float10)FUN_00486f70((double)CONCAT44(param_2,param_1) / 2.0);
      if ((float10)(double)CONCAT44(param_2,param_1) / (float10)2.0 == fVar3) {
        uVar2 = 2;
      }
      else {
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}
```

---

---

## FUN_0047fd40 — 0x47fd40

- Classification : internal
- Corps : `0x47fd40–0x47ffe6`
- État : pseudocode obtenu
- Evidence : `ev_cdb89862c021e8e994e3720e880d5c7cb172589a2755c5da705b681ec8920634`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x5` — `KERNEL32.DLL::MultiByteToWideChar`
- `EXTERNAL:0x7` — `KERNEL32.DLL::WideCharToMultiByte`
- `EXTERNAL:0x20` — `KERNEL32.DLL::LCMapStringW`
- `EXTERNAL:0x21` — `KERNEL32.DLL::LCMapStringA`
- `0x4737e0` — `_strncpy`
- `0x474d40` — `FUN_00474d40`
- `0x475780` — `FUN_00475780`
- `0x47fff0` — `FUN_0047fff0`

### Chaînes référencées

- `0x495eb0` — "aw_map.c"
- `0x495eb0` — "aw_map.c"

### Pseudocode Ghidra

```c
void FUN_0047fd40(LCID param_1,uint param_2,LPCWSTR param_3,int param_4,LPWSTR param_5,
                 size_t param_6,UINT param_7)

{
  int iVar1;
  LPCSTR lpMultiByteStr;
  int iVar2;
  size_t local_1c;
  char *local_10;
  
  if (DAT_006325d8 == 0) {
    iVar1 = LCMapStringW(0,0x100,L"",1,(LPWSTR)0x0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringA(0,0x100,"",1,(LPSTR)0x0,0);
      if (iVar1 == 0) {
        return;
      }
      DAT_006325d8 = 2;
    }
    else {
      DAT_006325d8 = 1;
    }
  }
  if (0 < param_4) {
    param_4 = FUN_0047fff0(param_3,param_4);
  }
  if (DAT_006325d8 == 1) {
    LCMapStringW(param_1,param_2,param_3,param_4,param_5,param_6);
    return;
  }
  if (DAT_006325d8 != 2) {
    return;
  }
  local_10 = (char *)0x0;
  if (param_7 == 0) {
    param_7 = DAT_006325f8;
  }
  iVar1 = WideCharToMultiByte(param_7,0x220,param_3,param_4,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0);
  if (iVar1 == 0) {
    return;
  }
  lpMultiByteStr = (LPCSTR)FUN_00474d40(iVar1,2,"aw_map.c",0xcc);
  if (lpMultiByteStr == (LPCSTR)0x0) {
    return;
  }
  iVar2 = WideCharToMultiByte(param_7,0x220,param_3,param_4,lpMultiByteStr,iVar1,(LPCSTR)0x0,
                              (LPBOOL)0x0);
  if ((((iVar2 == 0) ||
       (local_1c = LCMapStringA(param_1,param_2,lpMultiByteStr,iVar1,(LPSTR)0x0,0), local_1c == 0))
      || (local_10 = (char *)FUN_00474d40(local_1c,2,"aw_map.c",0xdb), local_10 == (char *)0x0)) ||
     (iVar1 = LCMapStringA(param_1,param_2,lpMultiByteStr,iVar1,local_10,local_1c), iVar1 == 0)) {
LAB_0047ffc5:
    FUN_00475780(lpMultiByteStr,2);
    FUN_00475780(local_10,2);
  }
  else {
    if ((param_2 & 0x400) == 0) {
      if (param_6 == 0) {
        iVar1 = MultiByteToWideChar(param_7,1,local_10,local_1c,(LPWSTR)0x0,0);
      }
      else {
        iVar1 = MultiByteToWideChar(param_7,1,local_10,local_1c,param_5,param_6);
      }
      if (iVar1 == 0) goto LAB_0047ffc5;
    }
    else if (param_6 != 0) {
      if ((int)param_6 < (int)local_1c) {
        local_1c = param_6;
      }
      _strncpy((char *)param_5,local_10,local_1c);
    }
    FUN_00475780(lpMultiByteStr,2);
    FUN_00475780(local_10,2);
  }
  return;
}
```

---

---

## FUN_0047fff0 — 0x47fff0

- Classification : internal
- Corps : `0x47fff0–0x480045`
- État : pseudocode obtenu
- Evidence : `ev_aaf34537eb93e2207f37cc49e0b2010400446df10449969f0ff17b8f910bfaf2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0047fff0(short *param_1,int param_2)

{
  int local_c;
  short *local_8;
  
  local_c = param_2;
  for (local_8 = param_1; (local_c != 0 && (*local_8 != 0)); local_8 = local_8 + 1) {
    local_c = local_c + -1;
  }
  if (*local_8 == 0) {
    param_2 = (int)local_8 - (int)param_1 >> 1;
  }
  return param_2;
}
```

---

---

## FUN_00480050 — 0x480050

- Classification : internal
- Corps : `0x480050–0x480307`
- État : pseudocode obtenu
- Evidence : `ev_4e097a33cf85c0785430c477fcab781a4756f76bf0511b7b53fa2537fae3d994`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x5` — `KERNEL32.DLL::MultiByteToWideChar`
- `EXTERNAL:0x7` — `KERNEL32.DLL::WideCharToMultiByte`
- `EXTERNAL:0x20` — `KERNEL32.DLL::LCMapStringW`
- `EXTERNAL:0x21` — `KERNEL32.DLL::LCMapStringA`
- `0x474d40` — `FUN_00474d40`
- `0x475780` — `FUN_00475780`
- `0x480310` — `FUN_00480310`

### Chaînes référencées

- `0x495eb0` — "aw_map.c"
- `0x495eb0` — "aw_map.c"

### Pseudocode Ghidra

```c
void FUN_00480050(LCID param_1,uint param_2,LPCSTR param_3,int param_4,LPWSTR param_5,int param_6,
                 UINT param_7)

{
  int iVar1;
  LPCWSTR lpWideCharStr;
  int iVar2;
  LPCWSTR local_c;
  
  if (DAT_006325dc == 0) {
    iVar1 = LCMapStringA(0,0x100,"",1,(LPSTR)0x0,0);
    if (iVar1 == 0) {
      iVar1 = LCMapStringW(0,0x100,L"",1,(LPWSTR)0x0,0);
      if (iVar1 == 0) {
        return;
      }
      DAT_006325dc = 1;
    }
    else {
      DAT_006325dc = 2;
    }
  }
  if (0 < param_4) {
    param_4 = FUN_00480310(param_3,param_4);
  }
  if (DAT_006325dc == 2) {
    LCMapStringA(param_1,param_2,param_3,param_4,(LPSTR)param_5,param_6);
    return;
  }
  if (DAT_006325dc != 1) {
    return;
  }
  local_c = (LPCWSTR)0x0;
  if (param_7 == 0) {
    param_7 = DAT_006325f8;
  }
  iVar1 = MultiByteToWideChar(param_7,9,param_3,param_4,(LPWSTR)0x0,0);
  if (iVar1 == 0) {
    return;
  }
  lpWideCharStr = (LPCWSTR)FUN_00474d40(iVar1 << 1,2,"aw_map.c",0x16d);
  if (lpWideCharStr == (LPCWSTR)0x0) {
    return;
  }
  iVar2 = MultiByteToWideChar(param_7,1,param_3,param_4,lpWideCharStr,iVar1);
  if ((iVar2 != 0) &&
     (iVar2 = LCMapStringW(param_1,param_2,lpWideCharStr,iVar1,(LPWSTR)0x0,0), iVar2 != 0)) {
    if ((param_2 & 0x400) == 0) {
      local_c = (LPCWSTR)FUN_00474d40(iVar2 << 1,2,"aw_map.c",0x191);
      if ((local_c == (LPCWSTR)0x0) ||
         (iVar1 = LCMapStringW(param_1,param_2,lpWideCharStr,iVar1,local_c,iVar2), iVar1 == 0))
      goto LAB_004802e6;
      if (param_6 == 0) {
        iVar1 = WideCharToMultiByte(param_7,0x220,local_c,iVar2,(LPSTR)0x0,0,(LPCSTR)0x0,(LPBOOL)0x0
                                   );
      }
      else {
        iVar1 = WideCharToMultiByte(param_7,0x220,local_c,iVar2,(LPSTR)param_5,param_6,(LPCSTR)0x0,
                                    (LPBOOL)0x0);
      }
    }
    else {
      if (param_6 == 0) goto LAB_004802c5;
      if (param_6 < iVar2) goto LAB_004802e6;
      iVar1 = LCMapStringW(param_1,param_2,lpWideCharStr,iVar1,param_5,param_6);
    }
    if (iVar1 != 0) {
LAB_004802c5:
      FUN_00475780(lpWideCharStr,2);
      FUN_00475780(local_c,2);
      return;
    }
  }
LAB_004802e6:
  FUN_00475780(lpWideCharStr,2);
  FUN_00475780(local_c,2);
  return;
}
```

---

---

## FUN_00480310 — 0x480310

- Classification : internal
- Corps : `0x480310–0x48035f`
- État : pseudocode obtenu
- Evidence : `ev_61c81f3986295633a0046a4a17f3457d2102ae7c76bff18d6747418bc36943ad`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00480310(char *param_1,int param_2)

{
  int local_c;
  char *local_8;
  
  local_c = param_2;
  for (local_8 = param_1; (local_c != 0 && (*local_8 != '\0')); local_8 = local_8 + 1) {
    local_c = local_c + -1;
  }
  if (*local_8 == '\0') {
    param_2 = (int)local_8 - (int)param_1;
  }
  return param_2;
}
```

---

---

## FUN_00480360 — 0x480360

- Classification : internal
- Corps : `0x480360–0x48044d`
- État : pseudocode obtenu
- Evidence : `ev_a48ec5acbf9064ff23b65f75324deaf351e29413fc5d7465b3e1e9bf9892586e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4875e0` — `FUN_004875e0`
- `0x487940` — `FUN_00487940`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00480360(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7
                )

{
  uint uVar1;
  int iVar2;
  int local_30;
  undefined1 local_2c [8];
  int local_24;
  int local_1c;
  uint local_18;
  int local_10;
  int local_8;
  
  uVar1 = param_1 - 0x76c;
  if (((int)uVar1 < 0x46) || (0x8a < (int)uVar1)) {
    local_8 = -1;
  }
  else {
    local_30 = param_3 + *(int *)(&DAT_004a8fe4 + param_2 * 4);
    if (((uVar1 & 3) == 0) && (2 < param_2)) {
      local_30 = local_30 + 1;
    }
    local_8 = ((((param_1 + -0x76d >> 2) + -0x11 + local_30 + (param_1 + -0x7b2) * 0x16d) * 0x18 +
               param_4) * 0x3c + param_5) * 0x3c + param_6;
    FUN_004875e0();
    local_8 = local_8 + DAT_004a8ef8;
    local_10 = local_30;
    local_1c = param_2 + -1;
    local_24 = param_4;
    if ((param_7 == 1) ||
       (((param_7 == -1 && (DAT_004a8efc != 0)) &&
        (local_18 = uVar1, iVar2 = FUN_00487940(local_2c), iVar2 != 0)))) {
      local_8 = local_8 + DAT_004a8f00;
    }
  }
  return local_8;
}
```

---

## _asctime — 0x480450

- Classification : internal
- Corps : `0x480450–0x4805c8`
- État : pseudocode obtenu
- Evidence : `ev_d951cce1205691d6e2374f344db58b8cc9e40cff68dac9587f6aa434d4fc36b8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4805d0` — `store_dt`

### Chaînes référencées

- `0x4962b0` — "SunMonTueWedThuFriSat"
- `0x4962c8` — "JanFebMarAprMayJunJulAugSepOctNovDec"

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _asctime
   
   Library: Visual Studio 2003 Debug */

char * __cdecl _asctime(tm *_Tm)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  int local_14;
  char *local_8;
  
  local_8 = &DAT_00632600;
  iVar1 = _Tm->tm_wday;
  iVar2 = _Tm->tm_mon;
  for (local_14 = 0; local_14 < 3; local_14 = local_14 + 1) {
    *local_8 = "SunMonTueWedThuFriSat"[iVar1 * 3 + local_14];
    local_8[4] = "JanFebMarAprMayJunJulAugSepOctNovDec"[iVar2 * 3 + local_14];
    local_8 = local_8 + 1;
  }
  *local_8 = ' ';
  local_8[4] = ' ';
  puVar3 = (undefined1 *)store_dt(local_8 + 5,_Tm->tm_mday);
  *puVar3 = 0x20;
  puVar3 = (undefined1 *)store_dt(puVar3 + 1,_Tm->tm_hour);
  *puVar3 = 0x3a;
  puVar3 = (undefined1 *)store_dt(puVar3 + 1,_Tm->tm_min);
  *puVar3 = 0x3a;
  puVar3 = (undefined1 *)store_dt(puVar3 + 1,_Tm->tm_sec);
  *puVar3 = 0x20;
  uVar4 = store_dt(puVar3 + 1,_Tm->tm_year / 100 + 0x13);
  puVar3 = (undefined1 *)store_dt(uVar4,_Tm->tm_year % 100);
  *puVar3 = 10;
  puVar3[1] = 0;
  return &DAT_00632600;
}
```

---

## store_dt — 0x4805d0

- Classification : internal
- Corps : `0x4805d0–0x48060f`
- État : pseudocode obtenu
- Evidence : `ev_467c13958e8f7e35c05fcfcaf34c63b3294501cf3198f5d86d8f381638cd0492`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _store_dt
   
   Library: Visual Studio 2003 Debug */

char * __cdecl store_dt(char *param_1,int param_2)

{
  *param_1 = (char)(param_2 / 10) + '0';
  param_1[1] = (char)(param_2 % 10) + '0';
  return param_1 + 2;
}
```

---

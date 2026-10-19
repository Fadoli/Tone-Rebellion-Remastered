# 0021_batch_0017 — détails (2/5)

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

## FUN_00480610 — 0x480610

- Classification : internal
- Corps : `0x480610–0x48086f`
- État : pseudocode obtenu
- Evidence : `ev_926e4e01883a7dcac5e191152c2de332e6a8c54a2e1a73936f6035b04a43fb19`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4875e0` — `FUN_004875e0`
- `0x487940` — `FUN_00487940`
- `0x487e40` — `_gmtime`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
tm * FUN_00480610(time_t *param_1)

{
  tm *ptVar1;
  int iVar2;
  int local_8;
  
  if ((int)*param_1 < 0) {
    ptVar1 = (tm *)0x0;
  }
  else {
    FUN_004875e0();
    if (((int)*param_1 < 0x3f481) || (0x7ffc0b7e < (int)*param_1)) {
      ptVar1 = _gmtime(param_1);
      iVar2 = FUN_00487940(ptVar1);
      if (iVar2 == 0) {
        local_8 = ptVar1->tm_sec - DAT_004a8ef8;
      }
      else {
        local_8 = ptVar1->tm_sec - (DAT_004a8ef8 + DAT_004a8f00);
      }
      ptVar1->tm_sec = local_8 % 0x3c;
      if (ptVar1->tm_sec < 0) {
        ptVar1->tm_sec = ptVar1->tm_sec + 0x3c;
        local_8 = local_8 + -0x3c;
      }
      local_8 = ptVar1->tm_min + local_8 / 0x3c;
      ptVar1->tm_min = local_8 % 0x3c;
      if (ptVar1->tm_min < 0) {
        ptVar1->tm_min = ptVar1->tm_min + 0x3c;
        local_8 = local_8 + -0x3c;
      }
      local_8 = ptVar1->tm_hour + local_8 / 0x3c;
      ptVar1->tm_hour = local_8 % 0x18;
      if (ptVar1->tm_hour < 0) {
        ptVar1->tm_hour = ptVar1->tm_hour + 0x18;
        local_8 = local_8 + -0x18;
      }
      local_8 = local_8 / 0x18;
      if (local_8 < 1) {
        if (local_8 < 0) {
          ptVar1->tm_wday = (ptVar1->tm_wday + 7 + local_8) % 7;
          ptVar1->tm_mday = ptVar1->tm_mday + local_8;
          if (ptVar1->tm_mday < 1) {
            ptVar1->tm_mday = ptVar1->tm_mday + 0x1f;
            ptVar1->tm_yday = 0x16c;
            ptVar1->tm_mon = 0xb;
            ptVar1->tm_year = ptVar1->tm_year + -1;
          }
          else {
            ptVar1->tm_yday = ptVar1->tm_yday + local_8;
          }
        }
      }
      else {
        ptVar1->tm_wday = (ptVar1->tm_wday + local_8) % 7;
        ptVar1->tm_mday = ptVar1->tm_mday + local_8;
        ptVar1->tm_yday = ptVar1->tm_yday + local_8;
      }
    }
    else {
      local_8 = (int)*param_1 - DAT_004a8ef8;
      ptVar1 = _gmtime((time_t *)&local_8);
      if ((DAT_004a8efc != 0) && (iVar2 = FUN_00487940(ptVar1), iVar2 != 0)) {
        local_8 = local_8 - DAT_004a8f00;
        ptVar1 = _gmtime((time_t *)&local_8);
        ptVar1->tm_isdst = 1;
      }
    }
  }
  return ptVar1;
}
```

---

## __cintrindisp2 — 0x480870

- Classification : internal
- Corps : `0x480870–0x4808ad`
- État : pseudocode obtenu
- Evidence : `ev_b8abb7f7091e97c95bdef1e3903cb2db430276f3898fbdb30223e14691625475`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f3d7` — `__trandisp2`
- `0x480925` — `FUN_00480925`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __cintrindisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __cintrindisp2(void)

{
  __trandisp2();
  DAT_00632628 = 1;
  FUN_00480925();
  return;
}
```

---

## __cintrindisp1 — 0x4808ae

- Classification : internal
- Corps : `0x4808ae–0x4808e3`
- État : pseudocode obtenu
- Evidence : `ev_0312abacadffb8db2b33c86f00009195d05710608f190f3977bffb3d2c86efd5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f370` — `__trandisp1`
- `0x480925` — `FUN_00480925`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __cintrindisp1
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __cintrindisp1(void)

{
  __trandisp1();
  DAT_00632628 = 1;
  FUN_00480925();
  return;
}
```

---

## __ctrandisp2 — 0x4808e4

- Classification : internal
- Corps : `0x4808e4–0x48091d`
- État : pseudocode obtenu
- Evidence : `ev_4219f0b72a0436a80344486f1af96b1b85e3a38b2f22257e359b6cab0d6848c3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f3d7` — `__trandisp2`
- `0x48091e` — `FUN_0048091e`
- `0x480a81` — `__fload`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __ctrandisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __ctrandisp2(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  __fload(param_1,param_2);
  __fload(param_3,param_4);
  __trandisp2();
  FUN_0048091e();
  return;
}
```

---

## FUN_0048091e — 0x48091e

- Classification : internal
- Corps : `0x48091e–0x480924`
- État : pseudocode obtenu
- Evidence : `ev_eeca05c606d8d34fe9ecaf8aa1d2b04dd415b846e4c7ebb1d4af0e3d908a6016`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048091e(void)

{
  char cVar1;
  int unaff_EBP;
  ushort in_FPUStatusWord;
  float10 in_ST0;
  
  DAT_00632628 = '\0';
  if (DAT_00632500 != 0) {
    DAT_00632628 = 0;
    return;
  }
  _DAT_00632620 = (double)in_ST0;
  cVar1 = *(char *)(unaff_EBP + -0x90);
  if (cVar1 != '\0') {
    if ((cVar1 != -1) && (cVar1 != -2)) {
      if (cVar1 == '\0') {
        DAT_00632628 = 0;
        return;
      }
      *(int *)(unaff_EBP + -0x8e) = (int)cVar1;
      goto LAB_004809f3;
    }
    if (((ulonglong)_DAT_00632620 & 0x7ff0000000000000) == 0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 4;
      in_ST0 = (float10)fscale(in_ST0,(float10)1536.0);
      if (ABS(in_ST0) < (float10)2.2250738585072014e-308) {
        in_ST0 = in_ST0 * (float10)0.0;
      }
      goto LAB_004809f3;
    }
    if ((DAT_00632626 & 0x7ff0) == 0x7ff0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 3;
      in_ST0 = (float10)fscale(in_ST0,(float10)-1536.0);
      if ((float10)1.7976931348623157e+308 < ABS(in_ST0)) {
        in_ST0 = in_ST0 * (float10)INFINITY;
      }
      goto LAB_004809f3;
    }
  }
  if ((*(ushort *)(unaff_EBP + -0xa4) & 0x20) != 0) {
    DAT_00632628 = 0;
    return;
  }
  if ((in_FPUStatusWord & 0x20) == 0) {
    DAT_00632628 = 0;
    return;
  }
  *(undefined4 *)(unaff_EBP + -0x8e) = 8;
LAB_004809f3:
  *(int *)(unaff_EBP + -0x8a) = *(int *)(unaff_EBP + -0x94) + 1;
  if (DAT_00632628 == '\0') {
    *(undefined4 *)(unaff_EBP + -0x86) = *(undefined4 *)(unaff_EBP + 8);
    *(undefined4 *)(unaff_EBP + -0x82) = *(undefined4 *)(unaff_EBP + 0xc);
    if (*(char *)(*(int *)(unaff_EBP + -0x94) + 0xd) != '\x01') {
      *(undefined4 *)(unaff_EBP + -0x7e) = *(undefined4 *)(unaff_EBP + 0x10);
      *(undefined4 *)(unaff_EBP + -0x7a) = *(undefined4 *)(unaff_EBP + 0x14);
    }
  }
  *(double *)(unaff_EBP + -0x76) = (double)in_ST0;
  FUN_00485220((int)*(char *)(*(int *)(unaff_EBP + -0x94) + 0xe),unaff_EBP + -0x8e,unaff_EBP + -0xa4
              );
  return;
}
```

---

## FUN_00480925 — 0x480925

- Classification : internal
- Corps : `0x480925–0x480a54`
- État : pseudocode obtenu
- Evidence : `ev_872cdf0ac487938237b112c5803917f83ca59e65138fec49f59ec4a598bc6d92`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x485220` — `FUN_00485220`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00480925(void)

{
  char cVar1;
  int unaff_EBP;
  ushort in_FPUStatusWord;
  float10 in_ST0;
  
  if (DAT_00632500 != 0) {
    return;
  }
  _DAT_00632620 = (double)in_ST0;
  cVar1 = *(char *)(unaff_EBP + -0x90);
  if (cVar1 != '\0') {
    if ((cVar1 != -1) && (cVar1 != -2)) {
      if (cVar1 == '\0') {
        return;
      }
      *(int *)(unaff_EBP + -0x8e) = (int)cVar1;
      goto LAB_004809f3;
    }
    if (((ulonglong)_DAT_00632620 & 0x7ff0000000000000) == 0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 4;
      in_ST0 = (float10)fscale(in_ST0,(float10)1536.0);
      if (ABS(in_ST0) < (float10)2.2250738585072014e-308) {
        in_ST0 = in_ST0 * (float10)0.0;
      }
      goto LAB_004809f3;
    }
    if ((DAT_00632626 & 0x7ff0) == 0x7ff0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 3;
      in_ST0 = (float10)fscale(in_ST0,(float10)-1536.0);
      if ((float10)1.7976931348623157e+308 < ABS(in_ST0)) {
        in_ST0 = in_ST0 * (float10)INFINITY;
      }
      goto LAB_004809f3;
    }
  }
  if ((*(ushort *)(unaff_EBP + -0xa4) & 0x20) != 0) {
    return;
  }
  if ((in_FPUStatusWord & 0x20) == 0) {
    return;
  }
  *(undefined4 *)(unaff_EBP + -0x8e) = 8;
LAB_004809f3:
  *(int *)(unaff_EBP + -0x8a) = *(int *)(unaff_EBP + -0x94) + 1;
  if (DAT_00632628 == '\0') {
    *(undefined4 *)(unaff_EBP + -0x86) = *(undefined4 *)(unaff_EBP + 8);
    *(undefined4 *)(unaff_EBP + -0x82) = *(undefined4 *)(unaff_EBP + 0xc);
    if (*(char *)(*(int *)(unaff_EBP + -0x94) + 0xd) != '\x01') {
      *(undefined4 *)(unaff_EBP + -0x7e) = *(undefined4 *)(unaff_EBP + 0x10);
      *(undefined4 *)(unaff_EBP + -0x7a) = *(undefined4 *)(unaff_EBP + 0x14);
    }
  }
  *(double *)(unaff_EBP + -0x76) = (double)in_ST0;
  FUN_00485220((int)*(char *)(*(int *)(unaff_EBP + -0x94) + 0xe),unaff_EBP + -0x8e,unaff_EBP + -0xa4
              );
  return;
}
```

---

## __ctrandisp1 — 0x480a55

- Classification : internal
- Corps : `0x480a55–0x480a80`
- État : pseudocode obtenu
- Evidence : `ev_f780d7e9cd6e56148b3ea1a6fdba676b8b4f8fbbf171bf7db569c466102ca370`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f370` — `__trandisp1`
- `0x48091e` — `FUN_0048091e`
- `0x480a81` — `__fload`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __ctrandisp1
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __ctrandisp1(undefined4 param_1,undefined4 param_2)

{
  __fload(param_1,param_2);
  __trandisp1();
  FUN_0048091e();
  return;
}
```

---

## __fload — 0x480a81

- Classification : internal
- Corps : `0x480a81–0x480abc`
- État : pseudocode obtenu
- Evidence : `ev_d7796b0c3977bc52d81535e1acb09551399964e3f72d3fecdb656f17cd60d4c9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __fload
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

float10 __fload(uint param_1,int param_2)

{
  float10 fVar1;
  
  if ((param_2._2_2_ & 0x7ff0) == 0x7ff0) {
    fVar1 = (float10)CONCAT28(param_2._2_2_ | 0x7fff,
                              CONCAT44(param_2 << 0xb | param_1 >> 0x15,param_1));
  }
  else {
    fVar1 = (float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
  }
  return fVar1;
}
```

---

## FUN_00480b85 — 0x480b85

- Classification : internal
- Corps : `0x480b85–0x480b9f`
- État : pseudocode obtenu
- Evidence : `ev_47fbd8d53e54f74147e56ea96af689e3b255ffab951693cc6b62a4bb3582da36`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4733f2` — `__local_unwind2`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480b85(int param_1)

{
  __local_unwind2(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x1c));
  return;
}
```

---

## __XcptFilter — 0x480ba0

- Classification : internal
- Corps : `0x480ba0–0x480d48`
- État : pseudocode obtenu
- Evidence : `ev_94ab6e588a8963c778ea8c0e1169e81bed1a791f70096a7ee390cff3f333da88`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x1f` — `KERNEL32.DLL::UnhandledExceptionFilter`
- `0x480d50` — `xcptlookup`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __XcptFilter
   
   Library: Visual Studio 2003 Debug */

int __cdecl __XcptFilter(ulong _ExceptionNum,_EXCEPTION_POINTERS *_ExceptionPtr)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  int local_14;
  
  piVar4 = (int *)xcptlookup(_ExceptionNum);
  uVar3 = DAT_0063262c;
  if ((piVar4 == (int *)0x0) || (piVar4[2] == 0)) {
    iVar5 = UnhandledExceptionFilter(_ExceptionPtr);
  }
  else if (piVar4[2] == 5) {
    piVar4[2] = 0;
    iVar5 = 1;
  }
  else if (piVar4[2] == 1) {
    iVar5 = -1;
    DAT_0063262c = (_EXCEPTION_POINTERS *)uVar3;
  }
  else {
    pcVar1 = (code *)piVar4[2];
    DAT_0063262c = _ExceptionPtr;
    if (piVar4[1] == 8) {
      for (local_14 = DAT_004a8928; uVar2 = DAT_004a8934, local_14 < DAT_004a8928 + _DAT_004a892c;
          local_14 = local_14 + 1) {
        *(undefined4 *)(local_14 * 0xc + 0x4a88b8) = 0;
      }
      if (*piVar4 == -0x3fffff72) {
        DAT_004a8934 = 0x83;
      }
      else if (*piVar4 == -0x3fffff70) {
        DAT_004a8934 = 0x81;
      }
      else if (*piVar4 == -0x3fffff6f) {
        DAT_004a8934 = 0x84;
      }
      else if (*piVar4 == -0x3fffff6d) {
        DAT_004a8934 = 0x85;
      }
      else if (*piVar4 == -0x3fffff73) {
        DAT_004a8934 = 0x82;
      }
      else if (*piVar4 == -0x3fffff71) {
        DAT_004a8934 = 0x86;
      }
      else if (*piVar4 == -0x3fffff6e) {
        DAT_004a8934 = 0x8a;
      }
      (*pcVar1)(8,DAT_004a8934);
      DAT_004a8934 = uVar2;
    }
    else {
      piVar4[2] = 0;
      (*pcVar1)(piVar4[1]);
    }
    iVar5 = -1;
    DAT_0063262c = (_EXCEPTION_POINTERS *)uVar3;
  }
  return iVar5;
}
```

---

## xcptlookup — 0x480d50

- Classification : internal
- Corps : `0x480d50–0x480daa`
- État : pseudocode obtenu
- Evidence : `ev_95e088a4bde575fc318b260e6e6cd6431cf1e03d27a35c1f69c1e374ddaf3778`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _xcptlookup
   
   Library: Visual Studio 2003 Debug */

int * __cdecl xcptlookup(int param_1)

{
  int *local_8;
  
  local_8 = &DAT_004a88b0;
  do {
    if (*local_8 == param_1) break;
    local_8 = local_8 + 3;
  } while (local_8 < &DAT_004a88b0 + DAT_004a8930 * 3);
  if ((&DAT_004a88b0 + DAT_004a8930 * 3 <= local_8) || (*local_8 != param_1)) {
    local_8 = (int *)0x0;
  }
  return local_8;
}
```

---

## FUN_00480db0 — 0x480db0

- Classification : internal
- Corps : `0x480db0–0x480dc4`
- État : pseudocode obtenu
- Evidence : `ev_b01febd9cf443bf7691751db24ac0af75916dd08c7e450738ec20f9fa4a574d4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480db0(undefined4 param_1)

{
  FUN_00480f30(param_1,0,1);
  return;
}
```

---

## FUN_00480dd0 — 0x480dd0

- Classification : internal
- Corps : `0x480dd0–0x480de4`
- État : pseudocode obtenu
- Evidence : `ev_08ae5d20c5bcbd20378ef83aef3fddf78d501a66add4dd792fabf6194f8c24d3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480dd0(undefined4 param_1)

{
  FUN_00480f30(param_1,0,3);
  return;
}
```

---

## FUN_00480df0 — 0x480df0

- Classification : internal
- Corps : `0x480df0–0x480e04`
- État : pseudocode obtenu
- Evidence : `ev_8d43fc2a33306e97db6791bcd6423c4241a7e5b4d1a046de6163a38d57bc219e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480df0(undefined4 param_1)

{
  FUN_00480f30(param_1,0,2);
  return;
}
```

---

## FUN_00480e10 — 0x480e10

- Classification : internal
- Corps : `0x480e10–0x480e27`
- État : pseudocode obtenu
- Evidence : `ev_fd3d58cfab0750613ca2560e22b0817592418192f48cb1aeace189cf926b4513`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480e10(undefined4 param_1)

{
  FUN_00480f30(param_1,0x107,1);
  return;
}
```

---

## FUN_00480e30 — 0x480e30

- Classification : internal
- Corps : `0x480e30–0x480e47`
- État : pseudocode obtenu
- Evidence : `ev_f90cc4695fd1ec76863ee94725ea916603faf78026ba51e4896b3b197c1c0998`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480e30(undefined4 param_1)

{
  FUN_00480f30(param_1,0x103,1);
  return;
}
```

---

## FUN_00480e50 — 0x480e50

- Classification : internal
- Corps : `0x480e50–0x480e67`
- État : pseudocode obtenu
- Evidence : `ev_0ef373180e7912e34a888102260dbf1e653fa2b9167b8430dfab1b8dc4ce161b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480e50(undefined4 param_1)

{
  FUN_00480f30(param_1,0x117,3);
  return;
}
```

---

## FUN_00480e70 — 0x480e70

- Classification : internal
- Corps : `0x480e70–0x480e87`
- État : pseudocode obtenu
- Evidence : `ev_cab2c0577594b53912b4af0a0772eaf7766063aaa9878ad2a430e55c1a4ed23f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480e70(undefined4 param_1)

{
  FUN_00480f30(param_1,0x157,3);
  return;
}
```

---


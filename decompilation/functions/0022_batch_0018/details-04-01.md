# 0022_batch_0018 — détails (1/3)

## FUN_00487610 — 0x487610

- Classification : internal
- Corps : `0x487610–0x48793b`
- État : pseudocode obtenu
- Evidence : `ev_052073bab5a497224d2620473428a2bafb520e061f1ccd0c96c872d9f5c20a54`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x11` — `KERNEL32.DLL::GetTimeZoneInformation`
- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`
- `0x4737e0` — `_strncpy`
- `0x474d40` — `FUN_00474d40`
- `0x475780` — `FUN_00475780`
- `0x4770b0` — `FUN_004770b0`
- `0x4774f0` — `_strcmp`
- `0x489e50` — `FUN_00489e50`
- `0x48a1a0` — `FUN_0048a1a0`

### Chaînes référencées

- `0x4962f0` — "tzset.c"

### Pseudocode Ghidra

```c
void FUN_00487610(void)

{
  char cVar1;
  char *_Str1;
  DWORD DVar2;
  int iVar3;
  size_t sVar4;
  undefined4 uVar5;
  char *pcVar6;
  undefined4 uVar7;
  char *local_c;
  
  DAT_006328d0 = 0;
  DAT_004a8fa0 = 0xffffffff;
  DAT_004a8f90 = 0xffffffff;
  _Str1 = (char *)FUN_0048a1a0(&DAT_004962f8);
  if (_Str1 == (char *)0x0) {
    DVar2 = GetTimeZoneInformation((LPTIME_ZONE_INFORMATION)&DAT_006328d8);
    if (DVar2 != 0xffffffff) {
      DAT_006328d0 = 1;
      DAT_004a8ef8 = DAT_006328d8 * 0x3c;
      if (DAT_0063291e != 0) {
        DAT_004a8ef8 = DAT_004a8ef8 + DAT_0063292c * 0x3c;
      }
      if ((DAT_00632972 == 0) || (DAT_00632980 == 0)) {
        DAT_004a8efc = 0;
        DAT_004a8f00 = 0;
      }
      else {
        DAT_004a8efc = 1;
        DAT_004a8f00 = (DAT_00632980 - DAT_0063292c) * 0x3c;
      }
      FUN_00489e50(PTR_DAT_004a8f88,&DAT_006328dc,0x40);
      FUN_00489e50(PTR_DAT_004a8f8c,&DAT_00632930,0x40);
      PTR_DAT_004a8f8c[0x3f] = 0;
      PTR_DAT_004a8f88[0x3f] = 0;
    }
  }
  else if ((*_Str1 != '\0') &&
          ((DAT_00632984 == (char *)0x0 || (iVar3 = _strcmp(_Str1,DAT_00632984), iVar3 != 0)))) {
    FUN_00475780(DAT_00632984,2);
    uVar7 = 0xec;
    pcVar6 = "tzset.c";
    uVar5 = 2;
    sVar4 = _strlen(_Str1);
    DAT_00632984 = (char *)FUN_00474d40(sVar4 + 1,uVar5,pcVar6,uVar7);
    if (DAT_00632984 != (char *)0x0) {
      FUN_00472da0(DAT_00632984,_Str1);
      _strncpy(PTR_DAT_004a8f88,_Str1,3);
      PTR_DAT_004a8f88[3] = 0;
      local_c = _Str1 + 3;
      cVar1 = *local_c;
      if (cVar1 == '-') {
        local_c = _Str1 + 4;
      }
      iVar3 = FUN_004770b0(local_c);
      DAT_004a8ef8 = iVar3 * 0xe10;
      for (; (*local_c == '+' || (('/' < *local_c && (*local_c < ':')))); local_c = local_c + 1) {
      }
      if (*local_c == ':') {
        local_c = local_c + 1;
        iVar3 = FUN_004770b0(local_c);
        DAT_004a8ef8 = DAT_004a8ef8 + iVar3 * 0x3c;
        for (; ('/' < *local_c && (*local_c < ':')); local_c = local_c + 1) {
        }
        if (*local_c == ':') {
          local_c = local_c + 1;
          iVar3 = FUN_004770b0(local_c);
          DAT_004a8ef8 = DAT_004a8ef8 + iVar3;
          for (; ('/' < *local_c && (*local_c < ':')); local_c = local_c + 1) {
          }
        }
      }
      if (cVar1 == '-') {
        DAT_004a8ef8 = -DAT_004a8ef8;
      }
      DAT_004a8efc = (int)*local_c;
      if (DAT_004a8efc == 0) {
        *PTR_DAT_004a8f8c = 0;
      }
      else {
        _strncpy(PTR_DAT_004a8f8c,local_c,3);
        PTR_DAT_004a8f8c[3] = 0;
      }
    }
  }
  return;
}
```

---

---

## FUN_00487940 — 0x487940

- Classification : internal
- Corps : `0x487940–0x487c39`
- État : pseudocode obtenu
- Evidence : `ev_93d4e17ed20814a78886f053eafa1a53c8ff0eb6f364fd0d67346d45f5fc4c54`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x487c40` — `FUN_00487c40`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00487940(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_004a8efc == 0) {
    return 0;
  }
  if ((param_1[5] != DAT_004a8f90) || (param_1[5] != DAT_004a8fa0)) {
    if (DAT_006328d0 == 0) {
      FUN_00487c40(1,1,param_1[5],4,1,0,0,2,0,0,0);
      FUN_00487c40(0,1,param_1[5],10,5,0,0,2,0,0,0);
    }
    else {
      if (DAT_00632970 == 0) {
        FUN_00487c40(1,1,param_1[5],DAT_00632972,DAT_00632976,DAT_00632974,0,DAT_00632978,
                     DAT_0063297a,DAT_0063297c,DAT_0063297e);
      }
      else {
        FUN_00487c40(1,0,param_1[5],DAT_00632972,0,0,DAT_00632976,DAT_00632978,DAT_0063297a,
                     DAT_0063297c,DAT_0063297e);
      }
      if (DAT_0063291c == 0) {
        FUN_00487c40(0,1,param_1[5],DAT_0063291e,DAT_00632922,DAT_00632920,0,DAT_00632924,
                     DAT_00632926,DAT_00632928,DAT_0063292a);
      }
      else {
        FUN_00487c40(0,0,param_1[5],DAT_0063291e,0,0,DAT_00632922,DAT_00632924,DAT_00632926,
                     DAT_00632928,DAT_0063292a);
      }
    }
  }
  if (DAT_004a8f94 < DAT_004a8fa4) {
    if ((param_1[7] < DAT_004a8f94) || (DAT_004a8fa4 < param_1[7])) {
      return 0;
    }
    if ((DAT_004a8f94 < param_1[7]) && (param_1[7] < DAT_004a8fa4)) {
      return 1;
    }
  }
  else {
    if ((param_1[7] < DAT_004a8fa4) || (DAT_004a8f94 < param_1[7])) {
      return 1;
    }
    if ((DAT_004a8fa4 < param_1[7]) && (param_1[7] < DAT_004a8f94)) {
      return 0;
    }
  }
  iVar2 = (*param_1 + param_1[1] * 0x3c + param_1[2] * 0xe10) * 1000;
  if (param_1[7] == DAT_004a8f94) {
    if (iVar2 < DAT_004a8f98) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else if (iVar2 < DAT_004a8fa8) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
```

---

---

## FUN_00487c40 — 0x487c40

- Classification : internal
- Corps : `0x487c40–0x487e37`
- État : pseudocode obtenu
- Evidence : `ev_d4ed3d2a2678b333fee4f6deb3b7d8359ca8337bef84b2d6f574ecbdca24f8f8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00487c40(int param_1,int param_2,uint param_3,int param_4,int param_5,int param_6,
                 int param_7,int param_8,int param_9,int param_10,int param_11)

{
  int iVar1;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  
  if (param_2 == 1) {
    if ((param_3 & 3) == 0) {
      local_10 = *(int *)(&DAT_004a8fac + param_4 * 4);
    }
    else {
      local_10 = *(int *)(&DAT_004a8fe4 + param_4 * 4);
    }
    local_10 = local_10 + 1;
    iVar1 = (int)(local_10 + (param_3 - 0x46) * 0x16d + -0xd + ((int)(param_3 - 1) >> 2)) % 7;
    if (iVar1 < param_6) {
      local_c = (param_5 + -1) * 7 + local_10 + (param_6 - iVar1);
    }
    else {
      local_c = param_5 * 7 + local_10 + (param_6 - iVar1);
    }
    if (param_5 == 5) {
      if ((param_3 & 3) == 0) {
        local_14 = *(int *)(&DAT_004a8fb0 + param_4 * 4);
      }
      else {
        local_14 = *(int *)(&DAT_004a8fe8 + param_4 * 4);
      }
      if (local_14 < local_c) {
        local_c = local_c + -7;
      }
    }
  }
  else {
    if ((param_3 & 3) == 0) {
      local_18 = *(int *)(&DAT_004a8fac + param_4 * 4);
    }
    else {
      local_18 = *(int *)(&DAT_004a8fe4 + param_4 * 4);
    }
    local_c = local_18 + param_7;
  }
  if (param_1 == 1) {
    DAT_004a8f94 = local_c;
    DAT_004a8f98 = param_11 + (param_10 + (param_9 + param_8 * 0x3c) * 0x3c) * 1000;
    DAT_004a8f90 = param_3;
  }
  else {
    DAT_004a8fa4 = local_c;
    DAT_004a8fa8 = param_11 + (param_10 + (param_9 + param_8 * 0x3c) * 0x3c) * 1000 +
                   DAT_004a8f00 * 1000;
    if (DAT_004a8fa8 < 0) {
      DAT_004a8fa8 = DAT_004a8fa8 + 86399999;
    }
    else if (86399999 < DAT_004a8fa8) {
      DAT_004a8fa8 = DAT_004a8fa8 + -86399999;
    }
    DAT_004a8fa0 = param_3;
  }
  return;
}
```

---

## _gmtime — 0x487e40

- Classification : internal
- Corps : `0x487e40–0x488000`
- État : pseudocode obtenu
- Evidence : `ev_af80f2a8808bc0ed1b0b3c4cba754eca188029b39f3e3e973c801bbe7d01bdc5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _gmtime
   
   Library: Visual Studio 2003 Debug */

tm * __cdecl _gmtime(time_t *_Time)

{
  bool bVar1;
  tm *ptVar2;
  int iVar3;
  int iVar4;
  int local_18;
  undefined *local_14;
  int local_10;
  
  iVar4 = (int)*_Time;
  bVar1 = false;
  if (iVar4 < 0) {
    ptVar2 = (tm *)0x0;
  }
  else {
    iVar3 = iVar4 % 0x7861f80;
    iVar4 = (iVar4 / 0x7861f80) * 4;
    local_18 = iVar4 + 0x46;
    local_10 = iVar3;
    if (0x1e1337f < iVar3) {
      local_18 = iVar4 + 0x47;
      local_10 = iVar3 + -0x1e13380;
      if (0x1e1337f < local_10) {
        local_18 = iVar4 + 0x48;
        local_10 = iVar3 + -0x3c26700;
        if (local_10 < 0x1e28500) {
          bVar1 = true;
        }
        else {
          local_18 = iVar4 + 0x49;
          local_10 = iVar3 + -0x5a4ec00;
        }
      }
    }
    DAT_006329a4 = local_18;
    DAT_006329ac = local_10 / 0x15180;
    if (bVar1) {
      local_14 = &DAT_004a8fb0;
    }
    else {
      local_14 = &DAT_004a8fe8;
    }
    for (local_18 = 1; *(int *)(local_14 + local_18 * 4) < DAT_006329ac; local_18 = local_18 + 1) {
    }
    DAT_006329a0 = local_18 + -1;
    DAT_0063299c = DAT_006329ac - *(int *)(local_14 + DAT_006329a0 * 4);
    DAT_006329a8 = ((int)*_Time / 0x15180 + 4) % 7;
    DAT_00632998 = (local_10 % 0x15180) / 0xe10;
    iVar4 = (local_10 % 0x15180) % 0xe10;
    DAT_00632994 = iVar4 / 0x3c;
    DAT_00632990 = iVar4 % 0x3c;
    DAT_006329b0 = 0;
    ptVar2 = (tm *)&DAT_00632990;
  }
  return ptVar2;
}
```

---

---

## FUN_00488010 — 0x488010

- Classification : internal
- Corps : `0x488010–0x48803f`
- État : pseudocode obtenu
- Evidence : `ev_0034da0d618489b7097a69f0f926316746519077408779fe01d205ccff19d2a8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00488010(short *param_1)

{
  short sVar1;
  short *local_8;
  
  local_8 = param_1;
  do {
    sVar1 = *local_8;
    local_8 = local_8 + 1;
  } while (sVar1 != 0);
  return ((int)local_8 - (int)param_1 >> 1) + -1;
}
```

---

## ___addl — 0x488040

- Classification : internal
- Corps : `0x488040–0x48807d`
- État : pseudocode obtenu
- Evidence : `ev_3c876cf5a80c8a9b7ce3da958199cf442368dbd6a16625a6b1665923d3fe906c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    ___addl
   
   Library: Visual Studio 2012 Debug */

undefined4 ___addl(uint param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  undefined4 local_c;
  
  local_c = 0;
  uVar1 = param_1 + param_2;
  if ((uVar1 < param_1) || (uVar1 < param_2)) {
    local_c = 1;
  }
  *param_3 = uVar1;
  return local_c;
}
```

---

## ___add_12 — 0x488080

- Classification : internal
- Corps : `0x488080–0x48812c`
- État : pseudocode obtenu
- Evidence : `ev_2211e067d5db381f9d231aef7c49c647cd3d69f2584c6e66506dd63285d70bdd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x488040` — `___addl`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    ___add_12
   
   Library: Visual Studio */

void ___add_12(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = ___addl(*param_1,*param_2,param_1);
  if (iVar1 != 0) {
    iVar1 = ___addl(param_1[1],1,param_1 + 1);
    if (iVar1 != 0) {
      param_1[2] = param_1[2] + 1;
    }
  }
  iVar1 = ___addl(param_1[1],param_2[1],param_1 + 1);
  if (iVar1 != 0) {
    param_1[2] = param_1[2] + 1;
  }
  ___addl(param_1[2],param_2[2],param_1 + 2);
  return;
}
```

---

## ___shl_12 — 0x488130

- Classification : internal
- Corps : `0x488130–0x48818f`
- État : pseudocode obtenu
- Evidence : `ev_41f35742f19c7b5f3a749830ece6a3f2866ff46fa70a8b47bc630857962c7ce4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    ___shl_12
   
   Libraries: Visual Studio 2003, Visual Studio 2005, Visual Studio 2008, Visual Studio 2010 */

void ___shl_12(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  *param_1 = *param_1 << 1;
  param_1[1] = param_1[1] << 1 | (uint)((uVar1 & 0x80000000) != 0);
  param_1[2] = param_1[2] << 1 | (uint)((uVar2 & 0x80000000) != 0);
  return;
}
```

---

## ___shr_12 — 0x488190

- Classification : internal
- Corps : `0x488190–0x4881f2`
- État : pseudocode obtenu
- Evidence : `ev_59ee4d93751f7e8c46c7664d565b6729ee9375ffe666c92631d0aca0bc3bfdfe`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    ___shr_12
   
   Libraries: Visual Studio 2003, Visual Studio 2005, Visual Studio 2008, Visual Studio 2010 */

void ___shr_12(uint *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = param_1[2];
  uVar2 = param_1[1];
  param_1[2] = param_1[2] >> 1;
  param_1[1] = param_1[1] >> 1 | -(uint)((uVar1 & 1) != 0) & 0x80000000;
  *param_1 = *param_1 >> 1 | -(uint)((uVar2 & 1) != 0) & 0x80000000;
  return;
}
```

---

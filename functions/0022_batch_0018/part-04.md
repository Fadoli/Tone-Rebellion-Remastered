# 0022_batch_0018 — détails (4/5)

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

## FUN_00488200 — 0x488200

- Classification : internal
- Corps : `0x488200–0x48833a`
- État : pseudocode obtenu
- Evidence : `ev_f25b30ba57b4907636525051e54cd18c1a7badd656c80488b6b4f1aa5a7b72a6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x488080` — `___add_12`
- `0x488130` — `___shl_12`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00488200(char *param_1,int param_2,uint *param_3)

{
  short local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  
  local_14 = 0x404e;
  *param_3 = 0;
  param_3[1] = 0;
  param_3[2] = 0;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    local_10 = *param_3;
    local_c = param_3[1];
    local_8 = param_3[2];
    ___shl_12(param_3);
    ___shl_12(param_3);
    ___add_12(param_3,&local_10);
    ___shl_12(param_3);
    local_10 = (uint)*param_1;
    local_c = 0;
    local_8 = 0;
    ___add_12(param_3,&local_10);
    param_1 = param_1 + 1;
  }
  while (param_3[2] == 0) {
    param_3[2] = param_3[1] >> 0x10;
    param_3[1] = param_3[1] << 0x10 | *param_3 >> 0x10;
    *param_3 = *param_3 << 0x10;
    local_14 = local_14 + -0x10;
  }
  while ((param_3[2] & 0x8000) == 0) {
    ___shl_12(param_3);
    local_14 = local_14 + -1;
  }
  *(short *)((int)param_3 + 10) = local_14;
  return;
}
```

---

## FUN_00488340 — 0x488340

- Classification : internal
- Corps : `0x488340–0x488855`
- État : pseudocode obtenu
- Evidence : `ev_da956eda13f984bad08b4180e2f67ec8305fc5293fd06a75c20838d21a4a04d2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472da0` — `FUN_00472da0`
- `0x488080` — `___add_12`
- `0x488130` — `___shl_12`
- `0x488190` — `___shr_12`
- `0x489670` — `FUN_00489670`
- `0x489ac0` — `FUN_00489ac0`

### Chaînes référencées

- `0x4962fc` — "1#QNAN"
- `0x496304` — "1#INF"
- `0x49630c` — "1#IND"
- `0x496314` — "1#SNAN"

### Pseudocode Ghidra

```c
undefined4
FUN_00488340(int param_1,uint param_2,ushort param_3,int param_4,uint param_5,short *param_6)

{
  int iVar1;
  ushort uVar2;
  char *pcVar3;
  uint local_78;
  short local_60;
  undefined4 local_5c;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  undefined1 local_51;
  undefined1 local_50;
  undefined1 local_4f;
  undefined1 local_4e;
  undefined1 local_4d;
  int local_4c;
  int local_48;
  ushort local_44;
  undefined2 uStack_42;
  undefined2 local_40;
  undefined2 uStack_3e;
  undefined2 local_3c;
  undefined2 uStack_3a;
  undefined2 uStack_38;
  undefined2 uStack_36;
  undefined2 uStack_34;
  undefined1 local_32;
  char cStack_31;
  undefined2 uStack_30;
  undefined1 uStack_2e;
  char cStack_2d;
  uint local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  ushort local_10;
  int local_c;
  short *local_8;
  
  _local_40 = CONCAT22(uStack_3e,0x4d);
  local_24 = 0x134312f4;
  local_58 = 0xcc;
  local_57 = 0xcc;
  local_56 = 0xcc;
  local_55 = 0xcc;
  local_54 = 0xcc;
  local_53 = 0xcc;
  local_52 = 0xcc;
  local_51 = 0xcc;
  local_50 = 0xcc;
  local_4f = 0xcc;
  local_4e = 0xfb;
  local_4d = 0x3f;
  local_5c = 1;
  local_28 = param_2;
  local_4c = param_1;
  if ((param_3 & 0x8000) == 0) {
    *(undefined1 *)(param_6 + 1) = 0x20;
  }
  else {
    *(undefined1 *)(param_6 + 1) = 0x2d;
  }
  if ((((param_3 & 0x7fff) == 0) && (param_2 == 0)) && (param_1 == 0)) {
    *param_6 = 0;
    *(undefined1 *)(param_6 + 1) = 0x20;
    *(undefined1 *)((int)param_6 + 3) = 1;
    *(undefined1 *)(param_6 + 2) = 0x30;
    *(undefined1 *)((int)param_6 + 5) = 0;
    local_5c = 1;
  }
  else if ((param_3 & 0x7fff) == 0x7fff) {
    *param_6 = 1;
    if (((param_2 == 0x80000000) && (param_1 == 0)) || ((param_2 & 0x40000000) != 0)) {
      if ((((param_3 & 0x8000) == 0) || (param_2 != 0xc0000000)) || (param_1 != 0)) {
        if ((param_2 == 0x80000000) && (param_1 == 0)) {
          FUN_00472da0(param_6 + 2,"1#INF");
          *(undefined1 *)((int)param_6 + 3) = 5;
        }
        else {
          FUN_00472da0(param_6 + 2,"1#QNAN");
          *(undefined1 *)((int)param_6 + 3) = 6;
        }
      }
      else {
        FUN_00472da0(param_6 + 2,"1#IND");
        *(undefined1 *)((int)param_6 + 3) = 5;
      }
    }
    else {
      FUN_00472da0(param_6 + 2,"1#SNAN");
      *(undefined1 *)((int)param_6 + 3) = 6;
    }
    local_5c = 0;
  }
  else {
    local_10 = param_3 & 0xff;
    uVar2 = (ushort)(byte)(param_2 >> 0x18);
    _local_44 = CONCAT22(uStack_42,uVar2);
    local_c = (param_3 & 0x7fff) * 0x4d10 + (uint)(param_3 >> 8 & 0x7f) * 0x4d + (uint)uVar2 * 0x9a
              + -0x134312f4;
    local_60 = (short)((uint)local_c >> 0x10);
    local_32 = (undefined1)(param_3 & 0x7fff);
    cStack_31 = (char)((param_3 & 0x7fff) >> 8);
    uStack_36 = (undefined2)param_2;
    uStack_34 = (undefined2)(param_2 >> 0x10);
    uStack_3a = (undefined2)param_1;
    uStack_38 = (undefined2)((uint)param_1 >> 0x10);
    local_3c = 0;
    FUN_00489ac0(&local_3c,-(int)local_60,1);
    if (0x3ffe < CONCAT11(cStack_31,local_32)) {
      local_60 = local_60 + 1;
      FUN_00489670(&local_3c,&local_58);
    }
    *param_6 = local_60;
    if (((param_5 & 1) == 0) || (param_4 = param_4 + local_60, 0 < param_4)) {
      if (0x15 < param_4) {
        param_4 = 0x15;
      }
      iVar1 = CONCAT11(cStack_31,local_32) - 0x3ffe;
      uStack_30 = (undefined2)iVar1;
      uStack_2e = (undefined1)((uint)iVar1 >> 0x10);
      cStack_2d = (char)((uint)iVar1 >> 0x18);
      local_32 = 0;
      cStack_31 = '\0';
      for (local_48 = 0; local_48 < 8; local_48 = local_48 + 1) {
        ___shl_12(&local_3c);
      }
      if (cStack_2d < '\0') {
        for (local_78 = -CONCAT13(cStack_2d,CONCAT12(uStack_2e,uStack_30)) & 0xff; 0 < (int)local_78
            ; local_78 = local_78 - 1) {
          ___shr_12(&local_3c);
        }
      }
      local_8 = param_6 + 2;
      for (local_14 = param_4 + 1; 0 < local_14; local_14 = local_14 + -1) {
        local_20 = CONCAT22(uStack_3a,local_3c);
        local_1c = CONCAT22(uStack_36,uStack_38);
        local_18 = CONCAT13(cStack_31,CONCAT12(local_32,uStack_34));
        ___shl_12(&local_3c);
        ___shl_12(&local_3c);
        ___add_12(&local_3c,&local_20);
        ___shl_12(&local_3c);
        *(char *)local_8 = cStack_31 + '0';
        local_8 = (short *)((int)local_8 + 1);
        cStack_31 = '\0';
      }
      pcVar3 = (char *)((int)local_8 + -1);
      local_8 = local_8 + -1;
      if (*pcVar3 < '5') {
        for (; (param_6 + 2 <= local_8 && ((char)*local_8 == '0'));
            local_8 = (short *)((int)local_8 + -1)) {
        }
        if (local_8 < param_6 + 2) {
          *param_6 = 0;
          *(undefined1 *)(param_6 + 1) = 0x20;
          *(undefined1 *)((int)param_6 + 3) = 1;
          *(undefined1 *)(param_6 + 2) = 0x30;
          *(undefined1 *)((int)param_6 + 5) = 0;
          return 1;
        }
      }
      else {
        for (; (param_6 + 2 <= local_8 && ((char)*local_8 == '9'));
            local_8 = (short *)((int)local_8 + -1)) {
          *(char *)local_8 = '0';
        }
        if (local_8 < param_6 + 2) {
          local_8 = (short *)((int)local_8 + 1);
          *param_6 = *param_6 + 1;
        }
        *(char *)local_8 = (char)*local_8 + '\x01';
      }
      *(char *)((int)param_6 + 3) = ((char)local_8 - ((char)param_6 + '\x04')) + '\x01';
      *(undefined1 *)((int)param_6 + *(char *)((int)param_6 + 3) + 4) = 0;
    }
    else {
      *param_6 = 0;
      *(undefined1 *)(param_6 + 1) = 0x20;
      *(undefined1 *)((int)param_6 + 3) = 1;
      *(undefined1 *)(param_6 + 2) = 0x30;
      *(undefined1 *)((int)param_6 + 5) = 0;
      local_5c = 1;
    }
  }
  return local_5c;
}
```

---

## FUN_00488860 — 0x488860

- Classification : internal
- Corps : `0x488860–0x48890b`
- État : pseudocode obtenu
- Evidence : `ev_88c9d25497e6820a77bd99bab4a2e91e7fca2a9e15a3e49d8f893d558bf2a566`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4748a0` — `FUN_004748a0`
- `0x475780` — `FUN_00475780`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00488860(void)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  for (local_c = 3; local_c < DAT_00633d00; local_c = local_c + 1) {
    if (*(int *)(DAT_006329bc + local_c * 4) != 0) {
      if ((*(uint *)(*(int *)(DAT_006329bc + local_c * 4) + 0xc) & 0x83) != 0) {
        iVar1 = FUN_004748a0(*(undefined4 *)(DAT_006329bc + local_c * 4));
        if (iVar1 != -1) {
          local_8 = local_8 + 1;
        }
      }
      if (0x13 < local_c) {
        FUN_00475780(*(undefined4 *)(DAT_006329bc + local_c * 4),2);
        *(undefined4 *)(DAT_006329bc + local_c * 4) = 0;
      }
    }
  }
  return local_8;
}
```

---

## FUN_00488910 — 0x488910

- Classification : internal
- Corps : `0x488910–0x488963`
- État : pseudocode obtenu
- Evidence : `ev_fa0203bb1e26338038c53c8154451e33f15af074e7ed7090991789986564caf3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4893c0` — `__umatherr`
- `0x4895b0` — `FUN_004895b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00488910(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  float10 fVar1;
  
  if (DAT_004a90f8 == 0) {
    fVar1 = (float10)__umatherr(1,param_1,param_2,param_3,0,0,param_2,param_3,param_4);
  }
  else {
    _DAT_0063251c = 0x21;
    FUN_004895b0(param_4,0xffff);
    fVar1 = (float10)(double)CONCAT44(param_3,param_2);
  }
  return fVar1;
}
```

---

## FUN_00488970 — 0x488970

- Classification : internal
- Corps : `0x488970–0x4889d5`
- État : pseudocode obtenu
- Evidence : `ev_1e169c356f9d8bccb6ad663c77b27279473c48e8b4f5915b4e109cad79ac0708`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4893c0` — `__umatherr`
- `0x4895b0` — `FUN_004895b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00488970(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5,undefined4 param_6)

{
  double dVar1;
  float10 fVar2;
  
  dVar1 = (double)CONCAT44(param_3,param_2) + (double)CONCAT44(param_5,param_4);
  if (DAT_004a90f8 == 0) {
    fVar2 = (float10)__umatherr(1,param_1,param_2,param_3,param_4,param_5,dVar1,param_6);
  }
  else {
    _DAT_0063251c = 0x21;
    FUN_004895b0(param_6,0xffff);
    fVar2 = (float10)dVar1;
  }
  return fVar2;
}
```

---

## FUN_004889e0 — 0x4889e0

- Classification : internal
- Corps : `0x4889e0–0x488a91`
- État : pseudocode obtenu
- Evidence : `ev_57a4b08383f6a5827127ce8594dc0bed35550d67111defc27037463e56c14c03`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x488b70` — `FUN_00488b70`
- `0x489040` — `FUN_00489040`
- `0x4893c0` — `__umatherr`
- `0x489460` — `__set_errno`
- `0x4894e0` — `FUN_004894e0`
- `0x4895b0` — `FUN_004895b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_004889e0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  float10 fVar2;
  undefined1 local_60 [56];
  uint local_28;
  int local_8;
  
  iVar1 = FUN_00489040(param_1,&param_5,param_7);
  if (iVar1 == 0) {
    local_28 = local_28 & 0xfffffffe;
    FUN_00488b70(local_60,&param_7,param_1,param_2,&param_3,&param_5);
  }
  local_8 = FUN_004894e0(param_1);
  if ((DAT_004a90f8 == 0) && (local_8 != 0)) {
    fVar2 = (float10)__umatherr(local_8,param_2,param_3,param_4,0,0,param_5,param_6,param_7);
  }
  else {
    __set_errno(local_8);
    FUN_004895b0(param_7,0xffff);
    fVar2 = (float10)(double)CONCAT44(param_6,param_5);
  }
  return fVar2;
}
```

---

## FUN_00488aa0 — 0x488aa0

- Classification : internal
- Corps : `0x488aa0–0x488b6d`
- État : pseudocode obtenu
- Evidence : `ev_bc77c8fcf4e877d6b003a409c2ffb1a9512a5f55fdad558166e3a7b4b83c4237`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x488b70` — `FUN_00488b70`
- `0x489040` — `FUN_00489040`
- `0x4893c0` — `__umatherr`
- `0x489460` — `__set_errno`
- `0x4894e0` — `FUN_004894e0`
- `0x4895b0` — `FUN_004895b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_00488aa0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                    undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                    undefined4 param_9)

{
  int iVar1;
  float10 fVar2;
  undefined1 local_60 [40];
  undefined4 local_38;
  undefined4 local_34;
  uint local_28;
  int local_8;
  
  iVar1 = FUN_00489040(param_1,&param_7,param_9);
  if (iVar1 == 0) {
    local_28 = local_28 & 0xffffffe1 | 3;
    local_38 = param_5;
    local_34 = param_6;
    FUN_00488b70(local_60,&param_9,param_1,param_2,&param_3,&param_7);
  }
  local_8 = FUN_004894e0(param_1);
  if ((DAT_004a90f8 == 0) && (local_8 != 0)) {
    fVar2 = (float10)__umatherr(local_8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_9);
  }
  else {
    __set_errno(local_8);
    FUN_004895b0(param_9,0xffff);
    fVar2 = (float10)(double)CONCAT44(param_8,param_7);
  }
  return fVar2;
}
```

---

## FUN_00488b70 — 0x488b70

- Classification : internal
- Corps : `0x488b70–0x489020`
- État : pseudocode obtenu
- Evidence : `ev_01957806b331ca681c47f8f31af97ac907aa1e8e9611c99f1f3a3ca660bf0c73`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x10` — `KERNEL32.DLL::RaiseException`
- `0x489570` — `FUN_00489570`
- `0x489590` — `FUN_00489590`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00488b70(uint *param_1,uint *param_2,uint param_3,uint param_4,uint *param_5,uint *param_6)

{
  uint uVar1;
  DWORD local_8;
  
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  if ((param_3 & 0x10) != 0) {
    local_8 = 0xc000008f;
    param_1[1] = param_1[1] | 1;
  }
  if ((param_3 & 2) != 0) {
    local_8 = 0xc0000093;
    param_1[1] = param_1[1] | 2;
  }
  if ((param_3 & 1) != 0) {
    local_8 = 0xc0000091;
    param_1[1] = param_1[1] | 4;
  }
  if ((param_3 & 4) != 0) {
    local_8 = 0xc000008e;
    param_1[1] = param_1[1] | 8;
  }
  if ((param_3 & 8) != 0) {
    local_8 = 0xc0000090;
    param_1[1] = param_1[1] | 0x10;
  }
  param_1[2] = param_1[2] & 0xffffffef | (uint)((*param_2 & 1) == 0) << 4;
  param_1[2] = param_1[2] & 0xfffffff7 | (uint)((*param_2 & 4) == 0) << 3;
  param_1[2] = param_1[2] & 0xfffffffb | (uint)((*param_2 & 8) == 0) << 2;
  param_1[2] = param_1[2] & 0xfffffffd | (uint)((*param_2 & 0x10) == 0) << 1;
  param_1[2] = param_1[2] & 0xfffffffe | (uint)((*param_2 & 0x20) == 0);
  uVar1 = FUN_00489570();
  if ((uVar1 & 1) != 0) {
    param_1[3] = param_1[3] | 0x10;
  }
  if ((uVar1 & 4) != 0) {
    param_1[3] = param_1[3] | 8;
  }
  if ((uVar1 & 8) != 0) {
    param_1[3] = param_1[3] | 4;
  }
  if ((uVar1 & 0x10) != 0) {
    param_1[3] = param_1[3] | 2;
  }
  if ((uVar1 & 0x20) != 0) {
    param_1[3] = param_1[3] | 1;
  }
  uVar1 = *param_2 & 0xc00;
  if (uVar1 < 0x401) {
    if (uVar1 == 0x400) {
      *param_1 = *param_1 & 0xfffffffc | 1;
    }
    else if (uVar1 == 0) {
      *param_1 = *param_1 & 0xfffffffc;
    }
  }
  else if (uVar1 == 0x800) {
    *param_1 = *param_1 & 0xfffffffc | 2;
  }
  else if (uVar1 == 0xc00) {
    *param_1 = *param_1 | 3;
  }
  uVar1 = *param_2 & 0x300;
  if (uVar1 == 0) {
    *param_1 = *param_1 & 0xffffffe3 | 8;
  }
  else if (uVar1 == 0x200) {
    *param_1 = *param_1 & 0xffffffe3 | 4;
  }
  else if (uVar1 == 0x300) {
    *param_1 = *param_1 & 0xffffffe3;
  }
  *param_1 = *param_1 & 0xfffe001f | (param_4 & 0xfff) << 5;
  param_1[8] = param_1[8] | 1;
  param_1[8] = param_1[8] & 0xffffffe1 | 2;
  param_1[4] = *param_5;
  param_1[5] = param_5[1];
  param_1[0x14] = param_1[0x14] | 1;
  param_1[0x14] = param_1[0x14] & 0xffffffe1 | 2;
  param_1[0x10] = *param_6;
  param_1[0x11] = param_6[1];
  FUN_00489590();
  RaiseException(local_8,0,1,(ULONG_PTR *)&param_1);
  if ((param_1[2] >> 4 & 1) != 0) {
    *param_2 = *param_2 & 0xfffffffe;
  }
  if ((param_1[2] >> 3 & 1) != 0) {
    *param_2 = *param_2 & 0xfffffffb;
  }
  if ((param_1[2] >> 2 & 1) != 0) {
    *param_2 = *param_2 & 0xfffffff7;
  }
  if ((param_1[2] >> 1 & 1) != 0) {
    *param_2 = *param_2 & 0xffffffef;
  }
  if ((param_1[2] & 1) != 0) {
    *param_2 = *param_2 & 0xffffffdf;
  }
  switch(*param_1 & 3) {
  case 0:
    *param_2 = *param_2 & 0xfffff3ff;
    break;
  case 1:
    *param_2 = *param_2 & 0xfffff3ff | 0x400;
    break;
  case 2:
    *param_2 = *param_2 & 0xfffff3ff | 0x800;
    break;
  case 3:
    *param_2 = *param_2 & 0xfffff3ff | 0xc00;
  }
  uVar1 = *param_1 >> 2 & 7;
  if (uVar1 == 0) {
    *param_2 = *param_2 & 0xfffff3ff | 0x300;
  }
  else if (uVar1 == 1) {
    *param_2 = *param_2 & 0xfffff3ff | 0x200;
  }
  else if (uVar1 == 2) {
    *param_2 = *param_2 & 0xfffff3ff;
  }
  *param_6 = param_1[0x10];
  param_6[1] = param_1[0x11];
  return;
}
```

---


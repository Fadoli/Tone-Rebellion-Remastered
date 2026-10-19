# 0022_batch_0018 — détails (1/5)

## FUN_00483790 — 0x483790

- Classification : internal
- Corps : `0x483790–0x4837a9`
- État : pseudocode obtenu
- Evidence : `ev_92e01f3af0bef03b6543ab39290874a8c1419fe9fe69215325dfe335998701b4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47d6e0` — `FUN_0047d6e0`
- `0x488860` — `FUN_00488860`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00483790(void)

{
  FUN_0047d6e0();
  if (DAT_0063255c != '\0') {
    FUN_00488860();
  }
  return;
}
```

---

## FUN_004837b0 — 0x4837b0

- Classification : internal
- Corps : `0x4837b0–0x48384d`
- État : pseudocode obtenu
- Evidence : `ev_232d58019dd2c4e2c077ff5c11140afbfc785bef0920654c98aaf8a1a63c576d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x7` — `KERNEL32.DLL::WideCharToMultiByte`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_004837b0(LPSTR param_1,uint param_2)

{
  int iVar1;
  BOOL local_c [2];
  
  if (param_1 == (LPSTR)0x0) {
    iVar1 = 0;
  }
  else if (DAT_006325e8 == 0) {
    if ((param_2 & 0xffff) < 0x100) {
      *param_1 = (CHAR)param_2;
      iVar1 = 1;
    }
    else {
      _DAT_0063251c = 0x2a;
      iVar1 = -1;
    }
  }
  else {
    local_c[0] = 0;
    iVar1 = WideCharToMultiByte(DAT_006325f8,0x220,(LPCWSTR)&param_2,1,param_1,DAT_004a87f4,
                                (LPCSTR)0x0,local_c);
    if ((iVar1 == 0) || (local_c[0] != 0)) {
      _DAT_0063251c = 0x2a;
      iVar1 = -1;
    }
  }
  return iVar1;
}
```

---

## __aulldiv — 0x483850

- Classification : internal
- Corps : `0x483850–0x4838b7`
- État : pseudocode obtenu
- Evidence : `ev_65e0d2e7d2537d9b78b0d8526e59fc5daf5196d70c71a5b5c32dfdaefb2f521f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __aulldiv
   
   Library: Visual Studio */

undefined8 __aulldiv(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar6;
  
  uVar9 = param_1;
  uVar6 = param_4;
  uVar7 = param_2;
  uVar3 = param_3;
  if (param_4 == 0) {
    uVar3 = param_2 / param_3;
    iVar4 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) /
                 (ulonglong)param_3);
  }
  else {
    do {
      uVar5 = uVar6 >> 1;
      uVar3 = (uint)(CONCAT14((uVar6 & 1) != 0,uVar3) >> 1);
      uVar8 = uVar7 >> 1;
      uVar9 = (uint)(CONCAT14((uVar7 & 1) != 0,uVar9) >> 1);
      uVar6 = uVar5;
      uVar7 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar8,uVar9) / (ulonglong)uVar3;
    iVar4 = (int)uVar1;
    lVar2 = (ulonglong)param_3 * (uVar1 & 0xffffffff);
    uVar3 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar9 = uVar3 + iVar4 * param_4;
    if (((CARRY4(uVar3,iVar4 * param_4)) || (param_2 < uVar9)) ||
       ((param_2 <= uVar9 && (param_1 < (uint)lVar2)))) {
      iVar4 = iVar4 + -1;
    }
    uVar3 = 0;
  }
  return CONCAT44(uVar3,iVar4);
}
```

---

## __aullrem — 0x4838c0

- Classification : internal
- Corps : `0x4838c0–0x483934`
- État : pseudocode obtenu
- Evidence : `ev_658c8172f01dedad5b843dcfb16124b8ee525a4af30c3da2cf29feb5e90bc28b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __aullrem
   
   Library: Visual Studio */

undefined8 __aullrem(uint param_1,uint param_2,uint param_3,uint param_4)

{
  ulonglong uVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  
  uVar4 = param_1;
  uVar9 = param_4;
  uVar10 = param_2;
  uVar3 = param_3;
  if (param_4 == 0) {
    iVar6 = (int)(((ulonglong)param_2 % (ulonglong)param_3 << 0x20 | (ulonglong)param_1) %
                 (ulonglong)param_3);
    iVar7 = 0;
  }
  else {
    do {
      uVar5 = uVar9 >> 1;
      uVar3 = (uint)(CONCAT14((uVar9 & 1) != 0,uVar3) >> 1);
      uVar8 = uVar10 >> 1;
      uVar4 = (uint)(CONCAT14((uVar10 & 1) != 0,uVar4) >> 1);
      uVar9 = uVar5;
      uVar10 = uVar8;
    } while (uVar5 != 0);
    uVar1 = CONCAT44(uVar8,uVar4) / (ulonglong)uVar3;
    uVar3 = (int)uVar1 * param_4;
    lVar2 = (uVar1 & 0xffffffff) * (ulonglong)param_3;
    uVar9 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar4 = (uint)lVar2;
    uVar10 = uVar9 + uVar3;
    if (((CARRY4(uVar9,uVar3)) || (param_2 < uVar10)) || ((param_2 <= uVar10 && (param_1 < uVar4))))
    {
      bVar11 = uVar4 < param_3;
      uVar4 = uVar4 - param_3;
      uVar10 = (uVar10 - param_4) - (uint)bVar11;
    }
    iVar6 = -(uVar4 - param_1);
    iVar7 = -(uint)(uVar4 - param_1 != 0) - ((uVar10 - param_2) - (uint)(uVar4 < param_1));
  }
  return CONCAT44(iVar7,iVar6);
}
```

---

## __itoa — 0x483940

- Classification : internal
- Corps : `0x483940–0x483981`
- État : pseudocode obtenu
- Evidence : `ev_5c7f2d9f5780796df5583b52b86dc86c84ca7144b69042cca26961d14b282cdf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x483990` — `xtoa`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __itoa
   
   Library: Visual Studio 2003 Debug */

char * __cdecl __itoa(int _Value,char *_Dest,int _Radix)

{
  if ((_Radix == 10) && (_Value < 0)) {
    xtoa(_Value,_Dest,10,1);
  }
  else {
    xtoa(_Value,_Dest,_Radix,0);
  }
  return _Dest;
}
```

---

## xtoa — 0x483990

- Classification : internal
- Corps : `0x483990–0x483a51`
- État : pseudocode obtenu
- Evidence : `ev_d61cb42cdabeed295595d052d62563a953a7558f76fa158ecd91cfb6f9bb6b42`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _xtoa
   
   Library: Visual Studio 2003 Debug */

void __cdecl xtoa(uint param_1,char *param_2,uint param_3,int param_4)

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  char *local_c;
  char *local_8;
  
  local_8 = param_2;
  if (param_4 != 0) {
    *param_2 = '-';
    local_8 = param_2 + 1;
    param_1 = -param_1;
  }
  local_c = local_8;
  do {
    pcVar2 = local_8;
    uVar3 = param_1 % param_3;
    param_1 = param_1 / param_3;
    cVar1 = (char)uVar3;
    if (uVar3 < 10) {
      *local_8 = cVar1 + '0';
    }
    else {
      *local_8 = cVar1 + 'W';
    }
    local_8 = local_8 + 1;
  } while (param_1 != 0);
  *local_8 = '\0';
  local_8 = pcVar2;
  do {
    cVar1 = *local_8;
    *local_8 = *local_c;
    *local_c = cVar1;
    local_8 = local_8 + -1;
    local_c = local_c + 1;
  } while (local_c < local_8);
  return;
}
```

---

## __ltoa — 0x483a60

- Classification : internal
- Corps : `0x483a60–0x483a9e`
- État : pseudocode obtenu
- Evidence : `ev_57d44634547e0592ffdbdf8e27b6bb6de991d96f3cfb1301573845b6c6d67c64`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x483990` — `xtoa`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __ltoa
   
   Library: Visual Studio 2003 Debug */

char * __cdecl __ltoa(long _Value,char *_Dest,int _Radix)

{
  undefined4 local_8;
  
  if ((_Radix == 10) && (_Value < 0)) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  xtoa(_Value,_Dest,_Radix,local_8);
  return _Dest;
}
```

---

## __ultoa — 0x483aa0

- Classification : internal
- Corps : `0x483aa0–0x483abd`
- État : pseudocode obtenu
- Evidence : `ev_35314666c5dee3f5526c1ebfb0fe0f0ca3ce95b87b801e91fde50a5eeee9e255`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x483990` — `xtoa`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __ultoa
   
   Library: Visual Studio 2003 Debug */

char * __cdecl __ultoa(ulong _Value,char *_Dest,int _Radix)

{
  xtoa(_Value,_Dest,_Radix,0);
  return _Dest;
}
```

---

## __i64toa — 0x483ac0

- Classification : internal
- Corps : `0x483ac0–0x483b07`
- État : pseudocode obtenu
- Evidence : `ev_67e7b249a37edeb5df51174f105c34160d0e19329a189dc9711e62980b3ebe9f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x483b10` — `FUN_00483b10`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __i64toa
   
   Library: Visual Studio 2003 Debug */

char * __cdecl __i64toa(longlong _Val,char *_DstBuf,int _Radix)

{
  undefined4 local_8;
  
  if (((_Radix == 10) && (_Val < 0x100000000)) && (_Val < 0)) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  FUN_00483b10(_Val,_DstBuf,_Radix,local_8);
  return _DstBuf;
}
```

---

## FUN_00483b10 — 0x483b10

- Classification : internal
- Corps : `0x483b10–0x483bee`
- État : pseudocode obtenu
- Evidence : `ev_2e7a4b41914d52c653325b6a46504d66b5a54e21fcfe05905e00b49ee78b9270`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x483850` — `__aulldiv`
- `0x4838c0` — `__aullrem`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00483b10(undefined4 param_1,undefined4 param_2,char *param_3,undefined4 param_4,int param_5
                 )

{
  char cVar1;
  char *pcVar2;
  uint uVar3;
  longlong lVar4;
  char *local_c;
  char *local_8;
  
  lVar4 = CONCAT44(param_2,param_1);
  local_8 = param_3;
  if (param_5 != 0) {
    *param_3 = '-';
    local_8 = param_3 + 1;
  }
  local_c = local_8;
  do {
    pcVar2 = local_8;
    uVar3 = __aullrem(lVar4,param_4,0);
    lVar4 = __aulldiv(lVar4,param_4,0);
    if (uVar3 < 10) {
      *local_8 = (char)uVar3 + '0';
    }
    else {
      *local_8 = (char)uVar3 + 'W';
    }
    local_8 = local_8 + 1;
  } while (lVar4 != 0);
  *local_8 = '\0';
  local_8 = pcVar2;
  do {
    cVar1 = *local_8;
    *local_8 = *local_c;
    *local_c = cVar1;
    local_8 = local_8 + -1;
    local_c = local_c + 1;
  } while (local_c < local_8);
  return;
}
```

---

## __ui64toa — 0x483bf0

- Classification : internal
- Corps : `0x483bf0–0x483c0e`
- État : pseudocode obtenu
- Evidence : `ev_445c2b38d94d98d9fff18ea4bacb2785170470bae64d03a7f36fb19f0658aafc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x483b10` — `FUN_00483b10`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __ui64toa
   
   Library: Visual Studio 2003 Debug */

char * __cdecl __ui64toa(ulonglong _Val,char *_DstBuf,int _Radix)

{
  FUN_00483b10(_Val,_DstBuf,_Radix,0);
  return _DstBuf;
}
```

---

## FUN_00483c10 — 0x483c10

- Classification : internal
- Corps : `0x483c10–0x483d08`
- État : pseudocode obtenu
- Evidence : `ev_14e7681ca4756bcbf004e32e727f216ce822f856a102396dd7d67eb8b2e31c62`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x483c48 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x483c72 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x478ef0` — `FUN_00478ef0`
- `0x479170` — `FUN_00479170`
- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x495197` — "`format != NULL"
- `0x4951a8` — "sprintf.c"
- `0x4951a8` — "sprintf.c"
- `0x4951b4` — "string != NULL"

### Pseudocode Ghidra

```c
undefined4 FUN_00483c10(undefined1 *param_1,int param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  if ((param_1 == (undefined1 *)0x0) &&
     (iVar2 = FUN_0047a120(2,"sprintf.c",0x5d,0,"string != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_3 == 0) && (iVar2 = FUN_0047a120(2,"sprintf.c",0x5e,0,"format != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  local_18 = 0x42;
  local_1c = param_1;
  local_24 = param_1;
  local_20 = param_2;
  uVar3 = FUN_00479170(&local_24,param_3,&stack0x00000010);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    FUN_00478ef0(0,&local_24);
  }
  else {
    *local_24 = 0;
  }
  return uVar3;
}
```

---

## FUN_00483d10 — 0x483d10

- Classification : internal
- Corps : `0x483d10–0x483e02`
- État : pseudocode obtenu
- Evidence : `ev_743dd97095abc6efe430001673ff2647cbcc10a7e8359c5bce0b5f1daf64f548`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x483d42 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x483d6c with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x478ef0` — `FUN_00478ef0`
- `0x479170` — `FUN_00479170`
- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x495197` — "`format != NULL"
- `0x4951b4` — "string != NULL"
- `0x496208` — "vsprintf.c"
- `0x496208` — "vsprintf.c"

### Pseudocode Ghidra

```c
undefined4 FUN_00483d10(undefined1 *param_1,int param_2,int param_3,undefined4 param_4)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  if ((param_1 == (undefined1 *)0x0) &&
     (iVar2 = FUN_0047a120(2,"vsprintf.c",0x5a,0,"string != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_3 == 0) && (iVar2 = FUN_0047a120(2,"vsprintf.c",0x5b,0,"format != NULL"), iVar2 == 1))
  {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  local_18 = 0x42;
  local_1c = param_1;
  local_24 = param_1;
  local_20 = param_2;
  uVar3 = FUN_00479170(&local_24,param_3,param_4);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    FUN_00478ef0(0,&local_24);
  }
  else {
    *local_24 = 0;
  }
  return uVar3;
}
```

---

## FUN_00483e10 — 0x483e10

- Classification : internal
- Corps : `0x483e10–0x483f79`
- État : pseudocode obtenu
- Evidence : `ev_7f043b6e53afe7b7067bacae2a59de42fa157659a849dad5d2af636f1cccd84f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `EXTERNAL:0x17` — `KERNEL32.DLL::SetConsoleCtrlHandler`
- `0x4841e0` — `siglookup`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00483e10(int param_1,int param_2)

{
  int iVar1;
  BOOL BVar2;
  int local_c;
  undefined4 *local_8;
  
  if ((param_2 != 4) && (param_2 != 3)) {
    if ((param_1 == 2) || (((param_1 == 0x15 || (param_1 == 0x16)) || (param_1 == 0xf)))) {
      if (((param_1 == 2) || (param_1 == 0x15)) && (DAT_006328ac == 0)) {
        BVar2 = SetConsoleCtrlHandler(ctrlevent_capture,1);
        if (BVar2 != 1) {
          DAT_00632520 = GetLastError();
          _DAT_0063251c = 0x16;
          return -1;
        }
        DAT_006328ac = 1;
      }
      switch(param_1) {
      case 2:
        local_c = DAT_0063289c;
        DAT_0063289c = param_2;
        break;
      case 0xf:
        local_c = DAT_006328a8;
        DAT_006328a8 = param_2;
        break;
      case 0x15:
        local_c = DAT_006328a0;
        DAT_006328a0 = param_2;
        break;
      case 0x16:
        local_c = DAT_006328a4;
        DAT_006328a4 = param_2;
      }
      return local_c;
    }
    if ((((param_1 == 8) || (param_1 == 4)) || (param_1 == 0xb)) &&
       (local_8 = (undefined4 *)siglookup(param_1), local_8 != (undefined4 *)0x0)) {
      iVar1 = local_8[2];
      do {
        if (local_8[1] != param_1) {
          return iVar1;
        }
        local_8[2] = param_2;
        local_8 = local_8 + 3;
      } while (local_8 < &DAT_004a88b0 + DAT_004a8930 * 3);
      return iVar1;
    }
  }
  _DAT_0063251c = 0x16;
  return -1;
}
```

---

## ctrlevent_capture — 0x483fb0

- Classification : internal
- Corps : `0x483fb0–0x484017`
- État : pseudocode obtenu
- Evidence : `ev_04bda82b82959ada53f592d39441d46c041deef965926a74de98438e7261b92d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _ctrlevent_capture@4
   
   Library: Visual Studio 2003 Debug
   __stdcall ctrlevent_capture,4 */

undefined4 ctrlevent_capture(int param_1)

{
  undefined4 uVar1;
  code *local_10;
  undefined4 *local_c;
  undefined4 local_8;
  
  if (param_1 == 0) {
    local_c = &DAT_0063289c;
    local_10 = DAT_0063289c;
    local_8 = 2;
  }
  else {
    local_c = &DAT_006328a0;
    local_10 = DAT_006328a0;
    local_8 = 0x15;
  }
  if (local_10 == (code *)0x0) {
    uVar1 = 0;
  }
  else {
    if (local_10 != (code *)0x1) {
      *local_c = 0;
      (*local_10)(local_8);
    }
    uVar1 = 1;
  }
  return uVar1;
}
```

---

## FUN_00484020 — 0x484020

- Classification : internal
- Corps : `0x484020–0x4840ce`, `0x4840d2–0x4841a6`
- État : pseudocode obtenu
- Evidence : `ev_4f35535f8e253fbb1cc8fb592625b1fad64d6a95ff371ddc26285d941762a850`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x4840ca to 0x476ec0 __exit (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `0x476ec0` — `__exit`
- `0x4841e0` — `siglookup`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00484020(int param_1)

{
  int iVar1;
  code *local_18;
  undefined4 *local_14;
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  
  switch(param_1) {
  case 2:
    local_14 = &DAT_0063289c;
    local_18 = DAT_0063289c;
    break;
  default:
    return 0xffffffff;
  case 4:
  case 8:
  case 0xb:
    iVar1 = siglookup(param_1);
    local_14 = (undefined4 *)(iVar1 + 8);
    local_18 = (code *)*local_14;
    break;
  case 0xf:
    local_14 = &DAT_006328a8;
    local_18 = DAT_006328a8;
    break;
  case 0x15:
    local_14 = &DAT_006328a0;
    local_18 = DAT_006328a0;
    break;
  case 0x16:
    local_14 = &DAT_006328a4;
    local_18 = DAT_006328a4;
  }
  if (local_18 != (code *)0x1) {
    if (local_18 == (code *)0x0) {
                    /* WARNING: Subroutine does not return */
      __exit(3);
    }
    if (((param_1 == 8) || (param_1 == 0xb)) || (param_1 == 4)) {
      local_10 = DAT_0063262c;
      DAT_0063262c = 0;
      if (param_1 == 8) {
        local_8 = DAT_004a8934;
        DAT_004a8934 = 0x8c;
      }
    }
    if (param_1 == 8) {
      for (local_c = DAT_004a8928; local_c < DAT_004a8928 + _DAT_004a892c; local_c = local_c + 1) {
        *(undefined4 *)(local_c * 0xc + 0x4a88b8) = 0;
      }
    }
    else {
      *local_14 = 0;
    }
    if (param_1 == 8) {
      (*local_18)(8,DAT_004a8934);
    }
    else {
      (*local_18)(param_1);
      if ((param_1 != 0xb) && (param_1 != 4)) {
        return 0;
      }
    }
    if (param_1 == 8) {
      DAT_004a8934 = local_8;
    }
    DAT_0063262c = local_10;
    return 0;
  }
  return 0;
}
```

---

## siglookup — 0x4841e0

- Classification : internal
- Corps : `0x4841e0–0x48423c`
- État : pseudocode obtenu
- Evidence : `ev_b48ba62b42518d8de674d5baa52d34aeb031be6f45894806c47e72190ead5037`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _siglookup
   
   Library: Visual Studio 2003 Debug */

undefined4 * __cdecl siglookup(int param_1)

{
  undefined4 *local_8;
  
  local_8 = &DAT_004a88b0;
  do {
    if (local_8[1] == param_1) break;
    local_8 = local_8 + 3;
  } while (local_8 < &DAT_004a88b0 + DAT_004a8930 * 3);
  if ((&DAT_004a88b0 + DAT_004a8930 * 3 <= local_8) || (local_8[1] != param_1)) {
    local_8 = (undefined4 *)0x0;
  }
  return local_8;
}
```

---

## FUN_00484240 — 0x484240

- Classification : internal
- Corps : `0x484240–0x4842fa`
- État : pseudocode obtenu
- Evidence : `ev_39af1990af721e6e35b119694693ff8ee56787fe58a0923d197abc21d64e76fc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x47` — `KERNEL32.DLL::LoadLibraryA`
- `EXTERNAL:0x4b` — `KERNEL32.DLL::GetProcAddress`

### Chaînes référencées

- `0x495bdc` — "user32.dll"
- `0x496214` — "GetLastActivePopup"
- `0x496228` — "GetActiveWindow"
- `0x496238` — "MessageBoxA"

### Pseudocode Ghidra

```c
int FUN_00484240(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  HMODULE hModule;
  int iVar1;
  int local_8;
  
  local_8 = 0;
  if (DAT_006328b0 == (FARPROC)0x0) {
    hModule = LoadLibraryA("user32.dll");
    if (hModule != (HMODULE)0x0) {
      DAT_006328b0 = GetProcAddress(hModule,"MessageBoxA");
      if (DAT_006328b0 != (FARPROC)0x0) {
        DAT_006328b4 = GetProcAddress(hModule,"GetActiveWindow");
        DAT_006328b8 = GetProcAddress(hModule,"GetLastActivePopup");
        goto LAB_004842b3;
      }
    }
    iVar1 = 0;
  }
  else {
LAB_004842b3:
    if (DAT_006328b4 != (FARPROC)0x0) {
      local_8 = (*DAT_006328b4)();
    }
    if ((local_8 != 0) && (DAT_006328b8 != (FARPROC)0x0)) {
      local_8 = (*DAT_006328b8)(local_8);
    }
    iVar1 = (*DAT_006328b0)(local_8,param_1,param_2,param_3);
  }
  return iVar1;
}
```

---

## FUN_00484300 — 0x484300

- Classification : internal
- Corps : `0x484300–0x48445b`
- État : pseudocode obtenu
- Evidence : `ev_58553ba434576159cfe738cb5f1d180ada271fbb2b8af2889730fa6b9c2fa236`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x484335 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `EXTERNAL:0x5` — `KERNEL32.DLL::MultiByteToWideChar`
- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x496244` — "mbtowc.c"
- `0x496250` — "MB_CUR_MAX == 1 || MB_CUR_MAX == 2"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_00484300(LPWSTR param_1,byte *param_2,uint param_3)

{
  code *pcVar1;
  int iVar2;
  uint uVar3;
  
  if (((DAT_004a87f4 != 1) && (DAT_004a87f4 != 2)) &&
     (iVar2 = FUN_0047a120(2,"mbtowc.c",0x4f,0,"MB_CUR_MAX == 1 || MB_CUR_MAX == 2"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == (byte *)0x0) || (param_3 == 0)) {
    uVar3 = 0;
  }
  else if (*param_2 == 0) {
    if (param_1 != (LPWSTR)0x0) {
      *param_1 = L'\0';
    }
    uVar3 = 0;
  }
  else if (DAT_006325e8 == 0) {
    if (param_1 != (LPWSTR)0x0) {
      *param_1 = (ushort)*param_2;
    }
    uVar3 = 1;
  }
  else if ((*(ushort *)(PTR_DAT_004a85e8 + (uint)*param_2 * 2) & 0x8000) == 0) {
    iVar2 = MultiByteToWideChar(DAT_006325f8,9,(LPCSTR)param_2,1,param_1,
                                (uint)(param_1 != (LPWSTR)0x0));
    if (iVar2 == 0) {
      _DAT_0063251c = 0x2a;
      uVar3 = 0xffffffff;
    }
    else {
      uVar3 = 1;
    }
  }
  else if (((((int)DAT_004a87f4 < 2) || ((int)param_3 < (int)DAT_004a87f4)) ||
           (iVar2 = MultiByteToWideChar(DAT_006325f8,9,(LPCSTR)param_2,DAT_004a87f4,param_1,
                                        (uint)(param_1 != (LPWSTR)0x0)), uVar3 = DAT_004a87f4,
           iVar2 == 0)) && ((param_3 < DAT_004a87f4 || (uVar3 = DAT_004a87f4, param_2[1] == 0)))) {
    _DAT_0063251c = 0x2a;
    uVar3 = 0xffffffff;
  }
  return uVar3;
}
```

---

## FUN_00484460 — 0x484460

- Classification : internal
- Corps : `0x484460–0x4844a0`
- État : pseudocode obtenu
- Evidence : `ev_717bd07ee174811bb680459ec14452eda8690d1dc74a30cfb6e1166dc65e2f23`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00484460(int param_1)

{
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 0x103;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,0x103);
  }
  return local_8;
}
```

---

## FUN_004844b0 — 0x4844b0

- Classification : internal
- Corps : `0x4844b0–0x4844eb`
- État : pseudocode obtenu
- Evidence : `ev_83c98531942d843983526c39b9c26a57034666e87b468b525cbc0a07f9378610`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_004844b0(int param_1)

{
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 1;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,1);
  }
  return local_8;
}
```

---

## FUN_004844f0 — 0x4844f0

- Classification : internal
- Corps : `0x4844f0–0x48452b`
- État : pseudocode obtenu
- Evidence : `ev_ee3164ac8dc7f11ff1199a3a0bedb288faba628246d394b95677ab9aee0564d3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_004844f0(int param_1)

{
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 2;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,2);
  }
  return local_8;
}
```

---

## FUN_00484530 — 0x484530

- Classification : internal
- Corps : `0x484530–0x48456b`
- État : pseudocode obtenu
- Evidence : `ev_dce485486776733b358f0e430d24dbf384d86f1e4de473286aec670892f382de`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00484530(int param_1)

{
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 4;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,4);
  }
  return local_8;
}
```

---

## FUN_00484570 — 0x484570

- Classification : internal
- Corps : `0x484570–0x4845b0`
- État : pseudocode obtenu
- Evidence : `ev_07ca19b1707840b5a1d6f71b2475b15a3ccca593d8778e860ccfbf34517034be`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00484570(int param_1)

{
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 0x80;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,0x80);
  }
  return local_8;
}
```

---

## FUN_004845c0 — 0x4845c0

- Classification : internal
- Corps : `0x4845c0–0x4845fb`
- État : pseudocode obtenu
- Evidence : `ev_b879375b345dd5d077b28b90091dfccd7dcdfadc968fac4d1e8fa2bc3149ec81`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_004845c0(int param_1)

{
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 8;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,8);
  }
  return local_8;
}
```

---

## FUN_00484600 — 0x484600

- Classification : internal
- Corps : `0x484600–0x48463b`
- État : pseudocode obtenu
- Evidence : `ev_516f9a6f7d06bf7e79660b7be255c5975ed3bd7683d12f396e872d28f266cce0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00484600(int param_1)

{
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 0x10;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,0x10);
  }
  return local_8;
}
```

---

## FUN_00484640 — 0x484640

- Classification : internal
- Corps : `0x484640–0x484680`
- État : pseudocode obtenu
- Evidence : `ev_81862dda6ec6993fca8737dc17cbdb5d940889989147a4c111adb9f87c4b9cad`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00484640(int param_1)

{
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 0x107;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,0x107);
  }
  return local_8;
}
```

---


# 0022_batch_0018 — détails (1/3)

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

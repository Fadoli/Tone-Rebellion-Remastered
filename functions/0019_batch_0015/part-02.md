# 0019_batch_0015 — détails (2/6)

## FUN_004745f0 — 0x4745f0

- Classification : internal
- Corps : `0x4745f0–0x474891`
- État : pseudocode obtenu
- Evidence : `ev_9f825c3a00a73d8ce1efd68db6af1c0415d1aeb29489bca92f965ec7bac87c3f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `EXTERNAL:0x3b` — `KERNEL32.DLL::WriteFile`
- `0x4739b0` — `FUN_004739b0`
- `0x47cac0` — `__dosmaperr`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_004745f0(uint param_1,char *param_2,uint param_3)

{
  char cVar1;
  BOOL BVar2;
  int iVar3;
  int local_424;
  DWORD local_41c;
  char local_418 [1028];
  DWORD local_14;
  ulong local_10;
  char *local_c;
  char *local_8;
  
  if ((param_1 < DAT_00633e5c) &&
     (iVar3 = (int)param_1 >> 5,
     (*(byte *)((&DAT_00633d20)[iVar3] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    local_14 = 0;
    local_424 = 0;
    if (param_3 == 0) {
      local_424 = 0;
    }
    else {
      if ((*(byte *)((&DAT_00633d20)[iVar3] + 4 + (param_1 & 0x1f) * 8) & 0x20) != 0) {
        FUN_004739b0(param_1,0,2);
      }
      if (((int)*(char *)((&DAT_00633d20)[iVar3] + 4 + (param_1 & 0x1f) * 8) & 0x80U) == 0) {
        BVar2 = WriteFile(*(HANDLE *)((&DAT_00633d20)[iVar3] + (param_1 & 0x1f) * 8),param_2,param_3
                          ,&local_41c,(LPOVERLAPPED)0x0);
        if (BVar2 == 0) {
          local_10 = GetLastError();
        }
        else {
          local_10 = 0;
          local_14 = local_41c;
        }
      }
      else {
        local_8 = param_2;
        local_10 = 0;
        do {
          if (param_3 <= (uint)((int)local_8 - (int)param_2)) break;
          local_c = local_418;
          while (((int)local_c - (int)local_418 < 0x400 &&
                 ((uint)((int)local_8 - (int)param_2) < param_3))) {
            cVar1 = *local_8;
            local_8 = local_8 + 1;
            if (cVar1 == '\n') {
              local_424 = local_424 + 1;
              *local_c = '\r';
              local_c = local_c + 1;
            }
            *local_c = cVar1;
            local_c = local_c + 1;
          }
          BVar2 = WriteFile(*(HANDLE *)((&DAT_00633d20)[iVar3] + (param_1 & 0x1f) * 8),local_418,
                            (int)local_c - (int)local_418,&local_41c,(LPOVERLAPPED)0x0);
          if (BVar2 == 0) {
            local_10 = GetLastError();
            break;
          }
          local_14 = local_14 + local_41c;
        } while ((int)local_c - (int)local_418 <= (int)local_41c);
      }
      if (local_14 == 0) {
        if (local_10 == 0) {
          if (((*(byte *)((&DAT_00633d20)[iVar3] + 4 + (param_1 & 0x1f) * 8) & 0x40) == 0) ||
             (*param_2 != '\x1a')) {
            _DAT_0063251c = 0x1c;
            DAT_00632520 = 0;
            local_424 = -1;
          }
          else {
            local_424 = 0;
          }
        }
        else {
          if (local_10 == 5) {
            _DAT_0063251c = 9;
            DAT_00632520 = local_10;
          }
          else {
            __dosmaperr(local_10);
          }
          local_424 = -1;
        }
      }
      else {
        local_424 = local_14 - local_424;
      }
    }
  }
  else {
    _DAT_0063251c = 9;
    DAT_00632520 = 0;
    local_424 = -1;
  }
  return local_424;
}
```

---

## FUN_004748a0 — 0x4748a0

- Classification : internal
- Corps : `0x4748a0–0x47497c`
- État : pseudocode obtenu
- Evidence : `ev_de2d45a08359d5af86e1e964af4a973c24c3788f6c4c0f9cd7efda6b1339c7ac`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x4748f8 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x473fe0` — `FUN_00473fe0`
- `0x475780` — `FUN_00475780`
- `0x47a120` — `FUN_0047a120`
- `0x47d520` — `FUN_0047d520`
- `0x47d620` — `FUN_0047d620`

### Chaînes référencées

- `0x4951d0` — "fclose.c"
- `0x4951dc` — "str != NULL"

### Pseudocode Ghidra

```c
undefined4 FUN_004748a0(int param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  if ((*(uint *)(param_1 + 0xc) & 0x40) == 0) {
    if ((param_1 == 0) && (iVar2 = FUN_0047a120(2,"fclose.c",0x77,0,"str != NULL"), iVar2 == 1)) {
      pcVar1 = (code *)swi(3);
      uVar3 = (*pcVar1)();
      return uVar3;
    }
    if ((*(uint *)(param_1 + 0xc) & 0x83) != 0) {
      local_8 = FUN_0047d620(param_1);
      FUN_0047d520(param_1);
      iVar2 = FUN_00473fe0(*(undefined4 *)(param_1 + 0x10));
      if (iVar2 < 0) {
        local_8 = 0xffffffff;
      }
      else if (*(int *)(param_1 + 0x1c) != 0) {
        FUN_00475780(*(undefined4 *)(param_1 + 0x1c),2);
        *(undefined4 *)(param_1 + 0x1c) = 0;
      }
    }
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  else {
    *(undefined4 *)(param_1 + 0xc) = 0;
    local_8 = 0xffffffff;
  }
  return local_8;
}
```

---

## FUN_00474980 — 0x474980

- Classification : internal
- Corps : `0x474980–0x474a03`
- État : pseudocode obtenu
- Evidence : `ev_4d2b0c9cb45120509e6020ed763d38d4bfcfe11120859f6082452e78a903e10c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x4749b2 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x4749dc with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x47a120` — `FUN_0047a120`
- `0x47a7c0` — `FUN_0047a7c0`

### Chaînes référencées

- `0x495197` — "`format != NULL"
- `0x4951e8` — "fscanf.c"
- `0x4951e8` — "fscanf.c"
- `0x4951f4` — "stream != NULL"

### Pseudocode Ghidra

```c
undefined4 FUN_00474980(int param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((param_1 == 0) && (iVar2 = FUN_0047a120(2,"fscanf.c",0x36,0,"stream != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == 0) && (iVar2 = FUN_0047a120(2,"fscanf.c",0x37,0,"format != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  uVar3 = FUN_0047a7c0(param_1,param_2,&stack0x0000000c);
  return uVar3;
}
```

---

## FUN_00474a10 — 0x474a10

- Classification : internal
- Corps : `0x474a10–0x474aff`
- État : pseudocode obtenu
- Evidence : `ev_b8b21761698b76f9431ae6de57381ea47f3051338484808c2452c1d95cf8daba`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x474a3c with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x474a6a with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x474a94 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x474ac2 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x47a120` — `FUN_0047a120`
- `0x47d7d0` — `FUN_0047d7d0`
- `0x47db60` — `FUN_0047db60`

### Chaînes référencées

- `0x495204` — "*mode != _T('\\0')"
- `0x495218` — "mode != NULL"
- `0x495228` — "*file != _T('\\0')"
- `0x49523c` — "fopen.c"
- `0x49523c` — "fopen.c"
- `0x49523c` — "fopen.c"
- `0x49523c` — "fopen.c"
- `0x495244` — "file != NULL"

### Pseudocode Ghidra

```c
undefined4 FUN_00474a10(char *param_1,char *param_2,undefined4 param_3)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((param_1 == (char *)0x0) &&
     (iVar2 = FUN_0047a120(2,"fopen.c",0x35,0,"file != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((*param_1 == '\0') &&
     (iVar2 = FUN_0047a120(2,"fopen.c",0x36,0,"*file != _T(\'\\0\')"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == (char *)0x0) &&
     (iVar2 = FUN_0047a120(2,"fopen.c",0x37,0,"mode != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((*param_2 == '\0') &&
     (iVar2 = FUN_0047a120(2,"fopen.c",0x38,0,"*mode != _T(\'\\0\')"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  iVar2 = FUN_0047db60();
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_0047d7d0(param_1,param_2,param_3,iVar2);
  }
  return uVar3;
}
```

---

## FUN_00474b00 — 0x474b00

- Classification : internal
- Corps : `0x474b00–0x474b16`
- État : pseudocode obtenu
- Evidence : `ev_dbed377a96c46e7249eb471314289a7bc5e14e413dae2d53c986f75f10265626`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474a10` — `FUN_00474a10`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00474b00(undefined4 param_1,undefined4 param_2)

{
  FUN_00474a10(param_1,param_2,0x40);
  return;
}
```

---

## _memset — 0x474b20

- Classification : internal
- Corps : `0x474b20–0x474b77`
- État : pseudocode obtenu
- Evidence : `ev_3a058a373a8e9775f325d786dfce0aead8bee6871283fca00642eb454bb25827`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _memset
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

void * __cdecl _memset(void *_Dst,int _Val,size_t _Size)

{
  uint uVar1;
  uint uVar2;
  size_t sVar3;
  uint *puVar4;
  
  if (_Size == 0) {
    return _Dst;
  }
  uVar1 = _Val & 0xff;
  puVar4 = _Dst;
  if (3 < _Size) {
    uVar2 = -(int)_Dst & 3;
    sVar3 = _Size;
    if (uVar2 != 0) {
      sVar3 = _Size - uVar2;
      do {
        *(undefined1 *)puVar4 = (undefined1)_Val;
        puVar4 = (uint *)((int)puVar4 + 1);
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    uVar1 = uVar1 * 0x1010101;
    _Size = sVar3 & 3;
    uVar2 = sVar3 >> 2;
    if (uVar2 != 0) {
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar4 = uVar1;
        puVar4 = puVar4 + 1;
      }
      if (_Size == 0) {
        return _Dst;
      }
    }
  }
  do {
    *(char *)puVar4 = (char)uVar1;
    puVar4 = (uint *)((int)puVar4 + 1);
    _Size = _Size - 1;
  } while (_Size != 0);
  return _Dst;
}
```

---

## FUN_00474b80 — 0x474b80

- Classification : internal
- Corps : `0x474b80–0x474b8c`
- État : pseudocode obtenu
- Evidence : `ev_606c13907fc93b4fba7af9a488387145b1b6b4a61157b1e34c47057e3c69ad0c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00474b80(undefined4 param_1)

{
  DAT_004a6340 = param_1;
  return;
}
```

---

## FUN_00474b90 — 0x474b90

- Classification : internal
- Corps : `0x474b90–0x474bb6`
- État : pseudocode obtenu
- Evidence : `ev_653ca5e8f592888c1e9b40b1f751bfd3a4cb40580a0b0e14767c401fb7154e44`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00474b90(void)

{
  DAT_004a6340 = DAT_004a6340 * 0x343fd + 0x269ec3;
  return DAT_004a6340 >> 0x10 & 0x7fff;
}
```

---

## FUN_00474bc0 — 0x474bc0

- Classification : internal
- Corps : `0x474bc0–0x474c68`
- État : pseudocode obtenu
- Evidence : `ev_5e46814f50f82175351cc50babadffda5c52173895753081f3f97b8aec11787c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x474bf2 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x474c1c with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x479170` — `FUN_00479170`
- `0x47a120` — `FUN_0047a120`
- `0x47dc50` — `FUN_0047dc50`
- `0x47dd80` — `FUN_0047dd80`

### Chaînes référencées

- `0x495197` — "`format != NULL"
- `0x4951dc` — "str != NULL"
- `0x495254` — "fprintf.c"
- `0x495254` — "fprintf.c"

### Pseudocode Ghidra

```c
undefined4 FUN_00474bc0(int param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if ((param_1 == 0) && (iVar2 = FUN_0047a120(2,"fprintf.c",0x38,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == 0) && (iVar2 = FUN_0047a120(2,"fprintf.c",0x39,0,"format != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  uVar3 = FUN_0047dc50(param_1);
  uVar4 = FUN_00479170(param_1,param_2,&stack0x0000000c);
  FUN_0047dd80(uVar3,param_1);
  return uVar4;
}
```

---

## FUN_00474c70 — 0x474c70

- Classification : internal
- Corps : `0x474c70–0x474d12`
- État : pseudocode obtenu
- Evidence : `ev_00c5d19d97342d9278ad3927c5346e6be2327839d6bbeb39aecd4e8d992c6eea`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x474c9c with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x474cc6 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x479170` — `FUN_00479170`
- `0x47a120` — `FUN_0047a120`
- `0x47dc50` — `FUN_0047dc50`
- `0x47dd80` — `FUN_0047dd80`

### Chaînes référencées

- `0x495197` — "`format != NULL"
- `0x4951dc` — "str != NULL"
- `0x495260` — "vfprintf.c"
- `0x495260` — "vfprintf.c"

### Pseudocode Ghidra

```c
undefined4 FUN_00474c70(int param_1,int param_2,undefined4 param_3)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if ((param_1 == 0) && (iVar2 = FUN_0047a120(2,"vfprintf.c",0x35,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == 0) && (iVar2 = FUN_0047a120(2,"vfprintf.c",0x36,0,"format != NULL"), iVar2 == 1))
  {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  uVar3 = FUN_0047dc50(param_1);
  uVar4 = FUN_00479170(param_1,param_2,param_3);
  FUN_0047dd80(uVar3,param_1);
  return uVar4;
}
```

---

## FUN_00474d20 — 0x474d20

- Classification : internal
- Corps : `0x474d20–0x474d3c`
- État : pseudocode obtenu
- Evidence : `ev_9000fe42461594198e1e9eae9173aa4e12d9996ef363124c5689a135dc09758e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474d90` — `__nh_malloc_dbg`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00474d20(undefined4 param_1)

{
  __nh_malloc_dbg(param_1,DAT_006325b0,1,0,0);
  return;
}
```

---

## FUN_00474d40 — 0x474d40

- Classification : internal
- Corps : `0x474d40–0x474d62`
- État : pseudocode obtenu
- Evidence : `ev_387b01eef08df80c4eb07c1a0fe60d8b92c3d1df3c1c383486d104b9399940f8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474d90` — `__nh_malloc_dbg`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00474d40(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  __nh_malloc_dbg(param_1,DAT_006325b0,param_2,param_3,param_4);
  return;
}
```

---

## __nh_malloc — 0x474d70

- Classification : internal
- Corps : `0x474d70–0x474d8a`
- État : pseudocode obtenu
- Evidence : `ev_7c2a2d4b959ebcb053a4140fc844c7523baebcdad7d75bb63daf0c6294711c64`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474d90` — `__nh_malloc_dbg`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __nh_malloc
   
   Library: Visual Studio 2003 Debug */

void * __cdecl __nh_malloc(size_t _Size,int _NhFlag)

{
  void *pvVar1;
  
  pvVar1 = (void *)__nh_malloc_dbg(_Size,_NhFlag,1,0,0);
  return pvVar1;
}
```

---

## __nh_malloc_dbg — 0x474d90

- Classification : internal
- Corps : `0x474d90–0x474dd9`
- État : pseudocode obtenu
- Evidence : `ev_1172a89a7c0a16abb9fc6021062dff8cabc3bd9bb66c8861bd27964b344785cb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474e00` — `FUN_00474e00`
- `0x47de70` — `__callnewh`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __nh_malloc_dbg
   
   Library: Visual Studio 2003 Debug */

int __nh_malloc_dbg(size_t param_1,int param_2,undefined4 param_3,undefined4 param_4,
                   undefined4 param_5)

{
  int iVar1;
  
  while( true ) {
    iVar1 = FUN_00474e00(param_1,param_3,param_4,param_5);
    if (iVar1 != 0) {
      return iVar1;
    }
    if (param_2 == 0) break;
    iVar1 = __callnewh(param_1);
    if (iVar1 == 0) {
      return 0;
    }
  }
  return 0;
}
```

---

## FUN_00474de0 — 0x474de0

- Classification : internal
- Corps : `0x474de0–0x474df6`
- État : pseudocode obtenu
- Evidence : `ev_ce78abd133f6460a13ebea7bec3fe2edcc85123e12c4a03615fa2b67edf17b01`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474e00` — `FUN_00474e00`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00474de0(undefined4 param_1)

{
  FUN_00474e00(param_1,1,0,0);
  return;
}
```

---

## FUN_00474e00 — 0x474e00

- Classification : internal
- Corps : `0x474e00–0x475112`
- État : pseudocode obtenu
- Evidence : `ev_bbafab70723330b8b718046a23263d12053c0e1b21e17ba6f34b975ca5596aa7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x474e45 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x474e60 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x474eae with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x474ed6 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x474f35 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x474f89 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x474b20` — `_memset`
- `0x475e40` — `FUN_00475e40`
- `0x47a120` — `FUN_0047a120`
- `0x47df40` — `FUN_0047df40`
- `0x47df90` — `FUN_0047df90`

### Chaînes référencées

- `0x495290` — "Error: memory allocation: bad memory block type.\n"
- `0x4952c4` — "Invalid allocation size: %u bytes.\n"
- `0x4952ec` — "Client hook allocation failure.\n"
- `0x495310` — "Client hook allocation failure at file %hs line %d.\n"
- `0x495348` — "dbgheap.c"
- `0x495354` — "_CrtCheckMemory()"

### Pseudocode Ghidra

```c
undefined4 * FUN_00474e00(uint param_1,uint param_2,int param_3,undefined4 param_4)

{
  code *pcVar1;
  bool bVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  
  bVar2 = false;
  if ((((DAT_004a6348 & 4) != 0) && (iVar4 = FUN_00475e40(), iVar4 == 0)) &&
     (iVar4 = FUN_0047a120(2,"dbgheap.c",0x141,0,"_CrtCheckMemory()"), iVar4 == 1)) {
    pcVar1 = (code *)swi(3);
    puVar5 = (undefined4 *)(*pcVar1)();
    return puVar5;
  }
  iVar4 = DAT_004a634c;
  if (DAT_004a634c == DAT_004a6350) {
    pcVar1 = (code *)swi(3);
    puVar5 = (undefined4 *)(*pcVar1)();
    return puVar5;
  }
  iVar6 = (*(code *)PTR_FUN_004a65b8)(1,0,param_1,param_2,DAT_004a634c,param_3,param_4);
  if (iVar6 == 0) {
    if (param_3 == 0) {
      iVar4 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"Client hook allocation failure.\n");
      if (iVar4 == 1) {
        pcVar1 = (code *)swi(3);
        puVar5 = (undefined4 *)(*pcVar1)();
        return puVar5;
      }
    }
    else {
      iVar4 = FUN_0047a120(0,0,0,0,"Client hook allocation failure at file %hs line %d.\n",param_3,
                           param_4);
      if (iVar4 == 1) {
        pcVar1 = (code *)swi(3);
        puVar5 = (undefined4 *)(*pcVar1)();
        return puVar5;
      }
    }
    puVar5 = (undefined4 *)0x0;
  }
  else {
    if (((param_2 & 0xffff) != 2) && ((DAT_004a6348 & 1) == 0)) {
      bVar2 = true;
    }
    if ((param_1 < 0xffffffe1) && (param_1 + 0x24 < 0xffffffe1)) {
      if (((((param_2 & 0xffff) != 4) && (param_2 != 1)) && ((param_2 & 0xffff) != 2)) &&
         ((param_2 != 3 &&
          (iVar6 = FUN_0047a120(1,0,0,0,&DAT_004952e8,
                                "Error: memory allocation: bad memory block type.\n"), iVar6 == 1)))
         ) {
        pcVar1 = (code *)swi(3);
        puVar5 = (undefined4 *)(*pcVar1)();
        return puVar5;
      }
      puVar5 = (undefined4 *)FUN_0047df40(param_1 + 0x24);
      if (puVar5 == (undefined4 *)0x0) {
        puVar5 = (undefined4 *)0x0;
      }
      else {
        DAT_004a634c = DAT_004a634c + 1;
        if (bVar2) {
          *puVar5 = 0;
          puVar5[1] = 0;
          puVar5[2] = 0;
          puVar5[3] = 0xfedcbabc;
          puVar5[4] = param_1;
          puVar5[5] = 3;
          puVar5[6] = 0;
        }
        else {
          DAT_0063250c = DAT_0063250c + param_1;
          DAT_00632514 = DAT_00632514 + param_1;
          if (DAT_00632518 < DAT_00632514) {
            DAT_00632518 = DAT_00632514;
          }
          puVar3 = puVar5;
          if (DAT_00632510 != (undefined4 *)0x0) {
            DAT_00632510[1] = puVar5;
            puVar3 = DAT_00632508;
          }
          DAT_00632508 = puVar3;
          *puVar5 = DAT_00632510;
          puVar5[1] = 0;
          puVar5[2] = param_3;
          puVar5[3] = param_4;
          puVar5[4] = param_1;
          puVar5[5] = param_2;
          puVar5[6] = iVar4;
          DAT_00632510 = puVar5;
        }
        _memset(puVar5 + 7,(uint)DAT_004a6354,4);
        _memset((void *)((int)puVar5 + param_1 + 0x20),(uint)DAT_004a6354,4);
        _memset(puVar5 + 8,(uint)DAT_004a635c,param_1);
        puVar5 = puVar5 + 8;
      }
    }
    else {
      iVar4 = FUN_0047a120(1,0,0,0,"Invalid allocation size: %u bytes.\n",param_1);
      if (iVar4 == 1) {
        pcVar1 = (code *)swi(3);
        puVar5 = (undefined4 *)(*pcVar1)();
        return puVar5;
      }
      puVar5 = (undefined4 *)0x0;
    }
  }
  return puVar5;
}
```

---

## FUN_00475120 — 0x475120

- Classification : internal
- Corps : `0x475120–0x47513a`
- État : pseudocode obtenu
- Evidence : `ev_3f88774f11ba9f6cde1d58e7e64db7ba6c230779ae617350bbdfa32e65855e91`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x475140` — `__calloc_dbg`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00475120(undefined4 param_1,undefined4 param_2)

{
  __calloc_dbg(param_1,param_2,1,0,0);
  return;
}
```

---

## __calloc_dbg — 0x475140

- Classification : internal
- Corps : `0x475140–0x47519f`
- État : pseudocode obtenu
- Evidence : `ev_9f1e61e93c253fd3bf3009044d8d91ae1f5a0889954153370c402ea800114942`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474d40` — `FUN_00474d40`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __calloc_dbg
   
   Library: Visual Studio 2003 Debug */

undefined1 *
__calloc_dbg(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  undefined1 *puVar1;
  undefined1 *local_10;
  
  puVar1 = (undefined1 *)FUN_00474d40(param_2 * param_1,param_3,param_4,param_5);
  if (puVar1 != (undefined1 *)0x0) {
    for (local_10 = puVar1; local_10 < puVar1 + param_2 * param_1; local_10 = local_10 + 1) {
      *local_10 = 0;
    }
  }
  return puVar1;
}
```

---

## FUN_004751a0 — 0x4751a0

- Classification : internal
- Corps : `0x4751a0–0x4751ba`
- État : pseudocode obtenu
- Evidence : `ev_bae3b4afe0b802621580a848dee4b0960f58346ed5035d9c25912ff1f2dd1a3c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4751c0` — `__realloc_dbg`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004751a0(undefined4 param_1,undefined4 param_2)

{
  __realloc_dbg(param_1,param_2,1,0,0);
  return;
}
```

---

## __realloc_dbg — 0x4751c0

- Classification : internal
- Corps : `0x4751c0–0x4751eb`
- État : pseudocode obtenu
- Evidence : `ev_3bc9d689a0ac25050db8504b9e2110fbb5b67b67653addf40da7b93862ca97ae`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4751f0` — `FUN_004751f0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __realloc_dbg
   
   Library: Visual Studio 2003 Debug */

undefined4
__realloc_dbg(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
             undefined4 param_5)

{
  undefined4 uVar1;
  
  uVar1 = FUN_004751f0(param_1,param_2,param_3,param_4,param_5,1);
  return uVar1;
}
```

---


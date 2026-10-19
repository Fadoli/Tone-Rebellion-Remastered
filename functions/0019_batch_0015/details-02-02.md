# 0019_batch_0015 — détails (2/2)

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

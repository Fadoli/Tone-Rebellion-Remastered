# 0019_batch_0015 — détails (2/3)

## FUN_00475780 — 0x475780

- Classification : internal
- Corps : `0x475780–0x475b6b`
- État : pseudocode obtenu
- Evidence : `ev_c2ce8abe163eefdb6779ec298ad65820028cb6a87ee20267b729f1d1f42335dc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x4757bc with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x47580c with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475848 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x4758aa with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475919 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x47597f with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x4759c4 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475a3c with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475aa7 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475afd with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x474b20` — `_memset`
- `0x475db0` — `FUN_00475db0`
- `0x475e40` — `FUN_00475e40`
- `0x476280` — `FUN_00476280`
- `0x47a120` — `FUN_0047a120`
- `0x47df90` — `FUN_0047df90`
- `0x47e220` — `FUN_0047e220`

### Chaînes référencées

- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495354` — "_CrtCheckMemory()"
- `0x495458` — "_CrtIsValidHeapPointer(pUserData)"
- `0x495508` — "_pFirstBlock == pHead"
- `0x495520` — "_pLastBlock == pHead"
- `0x495538` — "pHead->nBlockUse == nBlockUse"
- `0x495558` — "pHead->nLine == IGNORE_LINE && pHead->lRequest == IGNORE_REQ"
- `0x495598` — "DAMAGE: after %hs block (#%d) at 0x%08X.\n"
- `0x4955c4` — "DAMAGE: before %hs block (#%d) at 0x%08X.\n"
- `0x4955f0` — "_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)"
- `0x495618` — "Client hook free failure.\n"

### Pseudocode Ghidra

```c
void FUN_00475780(void *param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  int *_Dst;
  
  if ((((DAT_004a6348 & 4) != 0) && (iVar2 = FUN_00475e40(), iVar2 == 0)) &&
     (iVar2 = FUN_0047a120(2,"dbgheap.c",0x3e1,0,"_CrtCheckMemory()"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (param_1 != (void *)0x0) {
    iVar2 = (*(code *)PTR_FUN_004a65b8)(3,param_1,0,param_2,0,0,0);
    if (iVar2 == 0) {
      iVar2 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"Client hook free failure.\n");
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
    }
    else {
      iVar2 = FUN_00476280(param_1);
      if ((iVar2 == 0) &&
         (iVar2 = FUN_0047a120(2,"dbgheap.c",0x3f3,0,"_CrtIsValidHeapPointer(pUserData)"),
         iVar2 == 1)) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      _Dst = (int *)((int)param_1 + -0x20);
      if ((((*(uint *)((int)param_1 + -0xc) & 0xffff) != 4) && (*(int *)((int)param_1 + -0xc) != 1))
         && (((*(uint *)((int)param_1 + -0xc) & 0xffff) != 2 &&
             ((*(int *)((int)param_1 + -0xc) != 3 &&
              (iVar2 = FUN_0047a120(2,"dbgheap.c",0x3f9,0,"_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)"),
              iVar2 == 1)))))) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      if ((DAT_004a6348 & 4) == 0) {
        iVar2 = FUN_00475db0((int)param_1 + -4,DAT_004a6354,4);
        if ((iVar2 == 0) &&
           (iVar2 = FUN_0047a120(1,0,0,0,"DAMAGE: before %hs block (#%d) at 0x%08X.\n",
                                 (&PTR_DAT_004a6360)[*(uint *)((int)param_1 + -0xc) & 0xffff],
                                 *(undefined4 *)((int)param_1 + -8),param_1), iVar2 == 1)) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        iVar2 = FUN_00475db0((int)param_1 + *(int *)((int)param_1 + -0x10),DAT_004a6354,4);
        if ((iVar2 == 0) &&
           (iVar2 = FUN_0047a120(1,0,0,0,"DAMAGE: after %hs block (#%d) at 0x%08X.\n",
                                 (&PTR_DAT_004a6360)[*(uint *)((int)param_1 + -0xc) & 0xffff],
                                 *(undefined4 *)((int)param_1 + -8),param_1), iVar2 == 1)) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
      }
      if (*(int *)((int)param_1 + -0xc) == 3) {
        if (((*(int *)((int)param_1 + -0x14) != -0x1234544) || (*(int *)((int)param_1 + -8) != 0))
           && (iVar2 = FUN_0047a120(2,"dbgheap.c",0x40e,0,
                                    "pHead->nLine == IGNORE_LINE && pHead->lRequest == IGNORE_REQ"),
              iVar2 == 1)) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        _memset(_Dst,(uint)DAT_004a6358,*(int *)((int)param_1 + -0x10) + 0x24);
        FUN_0047e220(_Dst);
      }
      else {
        if ((*(int *)((int)param_1 + -0xc) == 2) && (param_2 == 1)) {
          param_2 = 2;
        }
        if ((*(int *)((int)param_1 + -0xc) != param_2) &&
           (iVar2 = FUN_0047a120(2,"dbgheap.c",0x41b,0,"pHead->nBlockUse == nBlockUse"), iVar2 == 1)
           ) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        DAT_00632514 = DAT_00632514 - *(int *)((int)param_1 + -0x10);
        if ((DAT_004a6348 & 2) == 0) {
          if (*_Dst == 0) {
            if ((DAT_00632508 != _Dst) &&
               (iVar2 = FUN_0047a120(2,"dbgheap.c",0x42a,0,"_pLastBlock == pHead"), iVar2 == 1)) {
              pcVar1 = (code *)swi(3);
              (*pcVar1)();
              return;
            }
            DAT_00632508 = *(int **)((int)param_1 + -0x1c);
          }
          else {
            *(undefined4 *)(*_Dst + 4) = *(undefined4 *)((int)param_1 + -0x1c);
          }
          if (*(int *)((int)param_1 + -0x1c) == 0) {
            if ((DAT_00632510 != _Dst) &&
               (iVar2 = FUN_0047a120(2,"dbgheap.c",0x434,0,"_pFirstBlock == pHead"), iVar2 == 1)) {
              pcVar1 = (code *)swi(3);
              (*pcVar1)();
              return;
            }
            DAT_00632510 = (int *)*_Dst;
          }
          else {
            **(int **)((int)param_1 + -0x1c) = *_Dst;
          }
          _memset(_Dst,(uint)DAT_004a6358,*(int *)((int)param_1 + -0x10) + 0x24);
          FUN_0047e220(_Dst);
        }
        else {
          *(undefined4 *)((int)param_1 + -0xc) = 0;
          _memset(param_1,(uint)DAT_004a6358,*(size_t *)((int)param_1 + -0x10));
        }
      }
    }
  }
  return;
}
```

---

---

## FUN_00475b70 — 0x475b70

- Classification : internal
- Corps : `0x475b70–0x475b82`
- État : pseudocode obtenu
- Evidence : `ev_3fae188edd75c67a47a1e5b8ee247c367b9d12075f8b1207a88c0a0910809e71`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x475b90` — `FUN_00475b90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00475b70(undefined4 param_1)

{
  FUN_00475b90(param_1,1);
  return;
}
```

---

---

## FUN_00475b90 — 0x475b90

- Classification : internal
- Corps : `0x475b90–0x475cd1`
- État : pseudocode obtenu
- Evidence : `ev_a4fccd3c0799fb71f52e0a4f7f98af7421da93f497892408034b50c04a15f330`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x475bce with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475c05 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475c67 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475cb8 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x475e40` — `FUN_00475e40`
- `0x476280` — `FUN_00476280`
- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495354` — "_CrtCheckMemory()"
- `0x495458` — "_CrtIsValidHeapPointer(pUserData)"
- `0x495538` — "pHead->nBlockUse == nBlockUse"
- `0x4955f0` — "_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)"

### Pseudocode Ghidra

```c
undefined4 FUN_00475b90(int param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((((DAT_004a6348 & 4) != 0) && (iVar2 = FUN_00475e40(), iVar2 == 0)) &&
     (iVar2 = FUN_0047a120(2,"dbgheap.c",0x47c,0,"_CrtCheckMemory()"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  iVar2 = FUN_00476280(param_1);
  if ((iVar2 == 0) &&
     (iVar2 = FUN_0047a120(2,"dbgheap.c",0x485,0,"_CrtIsValidHeapPointer(pUserData)"), iVar2 == 1))
  {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((((*(uint *)(param_1 + -0xc) & 0xffff) != 4) && (*(int *)(param_1 + -0xc) != 1)) &&
     (((*(uint *)(param_1 + -0xc) & 0xffff) != 2 &&
      ((*(int *)(param_1 + -0xc) != 3 &&
       (iVar2 = FUN_0047a120(2,"dbgheap.c",0x48b,0,"_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)"),
       iVar2 == 1)))))) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((*(int *)(param_1 + -0xc) == 2) && (param_2 == 1)) {
    param_2 = 2;
  }
  if (((*(int *)(param_1 + -0xc) != 3) && (*(int *)(param_1 + -0xc) != param_2)) &&
     (iVar2 = FUN_0047a120(2,"dbgheap.c",0x492,0,"pHead->nBlockUse == nBlockUse"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  return *(undefined4 *)(param_1 + -0x10);
}
```

---

---

## FUN_00475ce0 — 0x475ce0

- Classification : internal
- Corps : `0x475ce0–0x475cfb`
- État : pseudocode obtenu
- Evidence : `ev_f15ac9f3fc91ee71f0b644d5f5a53dfb2247a2bd53816a1b43162acdb3f7ab83`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00475ce0(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_004a6350;
  DAT_004a6350 = param_1;
  return uVar1;
}
```

---

---

## FUN_00475d00 — 0x475d00

- Classification : internal
- Corps : `0x475d00–0x475d88`
- État : pseudocode obtenu
- Evidence : `ev_cb1264ad1d67f9ade3384a8239289a19513b36a0d209c8af6d310bff2ab8c4c2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x475d72 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x476280` — `FUN_00476280`
- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x495348` — "dbgheap.c"
- `0x4955f0` — "_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)"

### Pseudocode Ghidra

```c
void FUN_00475d00(int param_1,undefined4 param_2)

{
  code *pcVar1;
  int iVar2;
  
  iVar2 = FUN_00476280(param_1);
  if (iVar2 != 0) {
    if (((((*(uint *)(param_1 + -0xc) & 0xffff) != 4) && (*(int *)(param_1 + -0xc) != 1)) &&
        ((*(uint *)(param_1 + -0xc) & 0xffff) != 2)) &&
       ((*(int *)(param_1 + -0xc) != 3 &&
        (iVar2 = FUN_0047a120(2,"dbgheap.c",0x4d3,0,"_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)"),
        iVar2 == 1)))) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    *(undefined4 *)(param_1 + -0xc) = param_2;
  }
  return;
}
```

---

---

## FUN_00475d90 — 0x475d90

- Classification : internal
- Corps : `0x475d90–0x475dab`
- État : pseudocode obtenu
- Evidence : `ev_aefa4e24d201b5fc54f7cbde3724b45cc9bda925df39323c710c89aad3c75637`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_00475d90(undefined *param_1)

{
  undefined *puVar1;
  
  puVar1 = PTR_FUN_004a65b8;
  PTR_FUN_004a65b8 = param_1;
  return puVar1;
}
```

---

---

## FUN_00475db0 — 0x475db0

- Classification : internal
- Corps : `0x475db0–0x475e37`
- État : pseudocode obtenu
- Evidence : `ev_30c0ff6efc110c359faa8c76c2f65acb9149dda1dfdd4dfb25bc5a87792d2a12`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x475e1e with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x495634` — "memory check error at 0x%08X = 0x%02X, should be 0x%02X.\n"

### Pseudocode Ghidra

```c
undefined4 FUN_00475db0(char *param_1,char param_2,int param_3)

{
  code *pcVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 local_8;
  
  local_8 = 1;
  pcVar2 = param_1;
  while( true ) {
    do {
      param_1 = pcVar2;
      iVar4 = param_3 + -1;
      if (param_3 == 0) {
        return local_8;
      }
      pcVar2 = param_1 + 1;
      param_3 = iVar4;
    } while (*param_1 == param_2);
    iVar4 = FUN_0047a120(0,0,0,0,"memory check error at 0x%08X = 0x%02X, should be 0x%02X.\n",
                         param_1,*param_1,param_2);
    if (iVar4 == 1) break;
    local_8 = 0;
  }
  pcVar1 = (code *)swi(3);
  uVar3 = (*pcVar1)();
  return uVar3;
}
```

---

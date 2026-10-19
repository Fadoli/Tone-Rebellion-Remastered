# 0019_batch_0015 — détails (3/6)

## FUN_004751f0 — 0x4751f0

- Classification : internal
- Corps : `0x4751f0–0x475700`
- État : pseudocode obtenu
- Evidence : `ev_798d5f37fdfa5f8acee45de2eb9498ddca4a26dbc12f2ef46f4f2df5e9b9bdc5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x47527b with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475296 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x4752e6 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x47530e with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475340 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x47538f with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x4753c6 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475421 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475487 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x4755f6 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475655 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x4756a9 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x474b20` — `_memset`
- `0x474d40` — `FUN_00474d40`
- `0x475780` — `FUN_00475780`
- `0x475e40` — `FUN_00475e40`
- `0x476280` — `FUN_00476280`
- `0x47a120` — `FUN_0047a120`
- `0x47df90` — `FUN_0047df90`
- `0x47dfa0` — `FUN_0047dfa0`
- `0x47e040` — `FUN_0047e040`

### Chaînes référencées

- `0x495290` — "Error: memory allocation: bad memory block type.\n"
- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495348` — "dbgheap.c"
- `0x495354` — "_CrtCheckMemory()"
- `0x495368` — "_pFirstBlock == pOldBlock"
- `0x495384` — "_pLastBlock == pOldBlock"
- `0x4953a0` — "fRealloc || (!fRealloc && pNewBlock == pOldBlock)"
- `0x4953d4` — "_BLOCK_TYPE(pOldBlock->nBlockUse)==_BLOCK_TYPE(nBlockUse)"
- `0x495410` — "pOldBlock->nLine == IGNORE_LINE && pOldBlock->lRequest == IGNORE_REQ"
- `0x495458` — "_CrtIsValidHeapPointer(pUserData)"
- `0x49547c` — "Allocation too large or negative: %u bytes.\n"
- `0x4954ac` — "Client hook re-allocation failure.\n"
- `0x4954d0` — "Client hook re-allocation failure at file %hs line %d.\n"

### Pseudocode Ghidra

```c
int * FUN_004751f0(int param_1,uint param_2,uint param_3,int param_4,int param_5,int param_6)

{
  code *pcVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  bool bVar6;
  int *local_10;
  
  if (param_1 == 0) {
    piVar2 = (int *)FUN_00474d40(param_2,param_3,param_4,param_5);
  }
  else if ((param_6 == 0) || (param_2 != 0)) {
    if (((DAT_004a6348 & 4) != 0) &&
       ((iVar3 = FUN_00475e40(), iVar3 == 0 &&
        (iVar3 = FUN_0047a120(2,"dbgheap.c",0x239,0,"_CrtCheckMemory()"), iVar3 == 1)))) {
      pcVar1 = (code *)swi(3);
      piVar4 = (int *)(*pcVar1)();
      return piVar4;
    }
    iVar3 = DAT_004a634c;
    if (DAT_004a634c == DAT_004a6350) {
      pcVar1 = (code *)swi(3);
      piVar4 = (int *)(*pcVar1)();
      return piVar4;
    }
    iVar5 = (*(code *)PTR_FUN_004a65b8)(2,param_1,param_2,param_3,DAT_004a634c,param_4,param_5);
    if (iVar5 == 0) {
      if (param_4 == 0) {
        iVar3 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"Client hook re-allocation failure.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          piVar4 = (int *)(*pcVar1)();
          return piVar4;
        }
      }
      else {
        iVar3 = FUN_0047a120(0,0,0,0,"Client hook re-allocation failure at file %hs line %d.\n",
                             param_4,param_5);
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          piVar4 = (int *)(*pcVar1)();
          return piVar4;
        }
      }
      piVar2 = (int *)0x0;
    }
    else if (param_2 < 0xffffffdc) {
      if ((((param_3 != 1) && ((param_3 & 0xffff) != 4)) && ((param_3 & 0xffff) != 2)) &&
         (iVar5 = FUN_0047a120(1,0,0,0,&DAT_004952e8,
                               "Error: memory allocation: bad memory block type.\n"), iVar5 == 1)) {
        pcVar1 = (code *)swi(3);
        piVar4 = (int *)(*pcVar1)();
        return piVar4;
      }
      iVar5 = FUN_00476280(param_1);
      if ((iVar5 == 0) &&
         (iVar5 = FUN_0047a120(2,"dbgheap.c",0x261,0,"_CrtIsValidHeapPointer(pUserData)"),
         iVar5 == 1)) {
        pcVar1 = (code *)swi(3);
        piVar4 = (int *)(*pcVar1)();
        return piVar4;
      }
      piVar4 = (int *)(param_1 + -0x20);
      bVar6 = *(int *)(param_1 + -0xc) == 3;
      if (bVar6) {
        if (((*(int *)(param_1 + -0x14) != -0x1234544) || (*(int *)(param_1 + -8) != 0)) &&
           (iVar5 = FUN_0047a120(2,"dbgheap.c",0x26b,0,
                                 "pOldBlock->nLine == IGNORE_LINE && pOldBlock->lRequest == IGNORE_REQ"
                                ), iVar5 == 1)) {
          pcVar1 = (code *)swi(3);
          piVar4 = (int *)(*pcVar1)();
          return piVar4;
        }
      }
      else {
        if (((*(uint *)(param_1 + -0xc) & 0xffff) == 2) && ((param_3 & 0xffff) == 1)) {
          param_3 = 2;
        }
        if (((*(uint *)(param_1 + -0xc) & 0xffff) != (param_3 & 0xffff)) &&
           (iVar5 = FUN_0047a120(2,"dbgheap.c",0x272,0,
                                 "_BLOCK_TYPE(pOldBlock->nBlockUse)==_BLOCK_TYPE(nBlockUse)"),
           iVar5 == 1)) {
          pcVar1 = (code *)swi(3);
          piVar4 = (int *)(*pcVar1)();
          return piVar4;
        }
      }
      if (param_6 == 0) {
        local_10 = (int *)FUN_0047dfa0(piVar4,param_2 + 0x24);
        if (local_10 == (int *)0x0) {
          return (int *)0x0;
        }
      }
      else {
        local_10 = (int *)FUN_0047e040(piVar4,param_2 + 0x24);
        if (local_10 == (int *)0x0) {
          return (int *)0x0;
        }
      }
      DAT_004a634c = DAT_004a634c + 1;
      if (!bVar6) {
        DAT_0063250c = (DAT_0063250c - local_10[4]) + param_2;
        DAT_00632514 = (DAT_00632514 - local_10[4]) + param_2;
        if (DAT_00632518 < DAT_00632514) {
          DAT_00632518 = DAT_00632514;
        }
      }
      piVar2 = local_10 + 8;
      if ((uint)local_10[4] < param_2) {
        _memset((void *)((int)piVar2 + local_10[4]),(uint)DAT_004a635c,param_2 - local_10[4]);
      }
      _memset((void *)((int)piVar2 + param_2),(uint)DAT_004a6354,4);
      if (!bVar6) {
        local_10[2] = param_4;
        local_10[3] = param_5;
        local_10[6] = iVar3;
      }
      local_10[4] = param_2;
      if (((param_6 == 0) && (local_10 != piVar4)) &&
         (iVar3 = FUN_0047a120(2,"dbgheap.c",0x2a8,0,
                               "fRealloc || (!fRealloc && pNewBlock == pOldBlock)"), iVar3 == 1)) {
        pcVar1 = (code *)swi(3);
        piVar4 = (int *)(*pcVar1)();
        return piVar4;
      }
      if ((local_10 != piVar4) && (!bVar6)) {
        if (*local_10 == 0) {
          if ((DAT_00632508 != piVar4) &&
             (iVar3 = FUN_0047a120(2,"dbgheap.c",0x2b7,0,"_pLastBlock == pOldBlock"), iVar3 == 1)) {
            pcVar1 = (code *)swi(3);
            piVar4 = (int *)(*pcVar1)();
            return piVar4;
          }
          DAT_00632508 = (int *)local_10[1];
        }
        else {
          *(int *)(*local_10 + 4) = local_10[1];
        }
        if (local_10[1] == 0) {
          if ((DAT_00632510 != piVar4) &&
             (iVar3 = FUN_0047a120(2,"dbgheap.c",0x2c2,0,"_pFirstBlock == pOldBlock"), iVar3 == 1))
          {
            pcVar1 = (code *)swi(3);
            piVar4 = (int *)(*pcVar1)();
            return piVar4;
          }
          DAT_00632510 = (int *)*local_10;
        }
        else {
          *(int *)local_10[1] = *local_10;
        }
        if (DAT_00632510 == (int *)0x0) {
          DAT_00632508 = local_10;
        }
        else {
          DAT_00632510[1] = (int)local_10;
        }
        *local_10 = (int)DAT_00632510;
        local_10[1] = 0;
        DAT_00632510 = local_10;
      }
    }
    else {
      iVar3 = FUN_0047a120(1,0,0,0,"Allocation too large or negative: %u bytes.\n",param_2);
      if (iVar3 == 1) {
        pcVar1 = (code *)swi(3);
        piVar4 = (int *)(*pcVar1)();
        return piVar4;
      }
      piVar2 = (int *)0x0;
    }
  }
  else {
    FUN_00475780(param_1,param_3);
    piVar2 = (int *)0x0;
  }
  return piVar2;
}
```

---

## FUN_00475710 — 0x475710

- Classification : internal
- Corps : `0x475710–0x47572a`
- État : pseudocode obtenu
- Evidence : `ev_255a8989910c57698e4d7c1209f72da92880b3fbe8793a72b7169c7367d7bfc9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x475730` — `__expand_dbg`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00475710(undefined4 param_1,undefined4 param_2)

{
  __expand_dbg(param_1,param_2,1,0,0);
  return;
}
```

---

## __expand_dbg — 0x475730

- Classification : internal
- Corps : `0x475730–0x47575b`
- État : pseudocode obtenu
- Evidence : `ev_856ebd66484a55b3be607642aa12b843c0defca3eac7d4dfb0f58d4b883eb5c8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4751f0` — `FUN_004751f0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __expand_dbg
   
   Library: Visual Studio 2003 Debug */

undefined4
__expand_dbg(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 uVar1;
  
  uVar1 = FUN_004751f0(param_1,param_2,param_3,param_4,param_5,0);
  return uVar1;
}
```

---

## FUN_00475760 — 0x475760

- Classification : internal
- Corps : `0x475760–0x475772`
- État : pseudocode obtenu
- Evidence : `ev_b2cbc266a05f37134befb6fda594c52a5e8a326242016c1d6efb1888e411d758`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x475780` — `FUN_00475780`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00475760(undefined4 param_1)

{
  FUN_00475780(param_1,1);
  return;
}
```

---

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

## FUN_00475e40 — 0x475e40

- Classification : internal
- Corps : `0x475e40–0x476180`
- État : pseudocode obtenu
- Evidence : `ev_83038c24f1674e0ab7ebdb72116a2f215267b86e031cb0f6caf0e118160c574a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x475ec4 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475eef with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475f17 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475f3f with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475f67 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x476032 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x47608f with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x4760e8 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x476131 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x476164 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x475db0` — `FUN_00475db0`
- `0x47a120` — `FUN_0047a120`
- `0x47e280` — `FUN_0047e280`

### Chaînes référencées

- `0x495598` — "DAMAGE: after %hs block (#%d) at 0x%08X.\n"
- `0x4955c4` — "DAMAGE: before %hs block (#%d) at 0x%08X.\n"
- `0x495670` — "%hs located at 0x%08X is %u bytes long.\n"
- `0x49569c` — "%hs allocated at file %hs(%d).\n"
- `0x4956bc` — "DAMAGE: on top of Free block at 0x%08X.\n"
- `0x4956e8` — "DAMAGED"
- `0x4956f0` — "_heapchk fails with unknown return value!\n"
- `0x49571c` — "_heapchk fails with _HEAPBADPTR.\n"
- `0x495740` — "_heapchk fails with _HEAPBADEND.\n"
- `0x495764` — "_heapchk fails with _HEAPBADNODE.\n"
- `0x495788` — "_heapchk fails with _HEAPBADBEGIN.\n"

### Pseudocode Ghidra

```c
undefined4 FUN_00475e40(void)

{
  code *pcVar1;
  bool bVar2;
  int iVar3;
  undefined4 uVar4;
  char *local_18;
  undefined4 *local_c;
  undefined4 local_8;
  
  local_8 = 1;
  if ((DAT_004a6348 & 1) == 0) {
    local_8 = 1;
  }
  else {
    iVar3 = FUN_0047e280();
    if ((iVar3 == -1) || (iVar3 == -2)) {
      for (local_c = DAT_00632510; local_c != (undefined4 *)0x0; local_c = (undefined4 *)*local_c) {
        bVar2 = true;
        if (((((local_c[5] & 0xffff) == 4) || (local_c[5] == 1)) || ((local_c[5] & 0xffff) == 2)) ||
           (local_c[5] == 3)) {
          local_18 = (&PTR_DAT_004a6360)[local_c[5] & 0xffff];
        }
        else {
          local_18 = "DAMAGED";
        }
        iVar3 = FUN_00475db0(local_c + 7,DAT_004a6354,4);
        if (iVar3 == 0) {
          iVar3 = FUN_0047a120(0,0,0,0,"DAMAGE: before %hs block (#%d) at 0x%08X.\n",local_18,
                               local_c[6],local_c + 8);
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          bVar2 = false;
        }
        iVar3 = FUN_00475db0((int)local_c + local_c[4] + 0x20,DAT_004a6354,4);
        if (iVar3 == 0) {
          iVar3 = FUN_0047a120(0,0,0,0,"DAMAGE: after %hs block (#%d) at 0x%08X.\n",local_18,
                               local_c[6],local_c + 8);
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          bVar2 = false;
        }
        if ((local_c[5] == 0) &&
           (iVar3 = FUN_00475db0(local_c + 8,DAT_004a6358,local_c[4]), iVar3 == 0)) {
          iVar3 = FUN_0047a120(0,0,0,0,"DAMAGE: on top of Free block at 0x%08X.\n",local_c + 8);
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          bVar2 = false;
        }
        if (!bVar2) {
          if ((local_c[2] != 0) &&
             (iVar3 = FUN_0047a120(0,0,0,0,"%hs allocated at file %hs(%d).\n",local_18,local_c[2],
                                   local_c[3]), iVar3 == 1)) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          iVar3 = FUN_0047a120(0,0,0,0,"%hs located at 0x%08X is %u bytes long.\n",local_18,
                               local_c + 8,local_c[4]);
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          local_8 = 0;
        }
      }
    }
    else {
      switch(iVar3) {
      case -6:
        iVar3 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"_heapchk fails with _HEAPBADPTR.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      case -5:
        iVar3 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"_heapchk fails with _HEAPBADEND.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      case -4:
        iVar3 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"_heapchk fails with _HEAPBADNODE.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      case -3:
        iVar3 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"_heapchk fails with _HEAPBADBEGIN.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      default:
        iVar3 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"_heapchk fails with unknown return value!\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
      }
      local_8 = 0;
    }
  }
  return local_8;
}
```

---

## FUN_004761a0 — 0x4761a0

- Classification : internal
- Corps : `0x4761a0–0x4761c1`
- État : pseudocode obtenu
- Evidence : `ev_07597156be0a44ccb5d3d3f89d71ddfc20471393821ec3b2636f7443833dbd83`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004761a0(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_004a6348;
  if (param_1 != -1) {
    DAT_004a6348 = param_1;
  }
  return iVar1;
}
```

---

## FUN_004761d0 — 0x4761d0

- Classification : internal
- Corps : `0x4761d0–0x476222`
- État : pseudocode obtenu
- Evidence : `ev_23cd0f2afa963256366b3f11ac58a1feda6595f5d1f9e20c484220b6b7572858`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004761d0(code *param_1,undefined4 param_2)

{
  undefined4 *local_8;
  
  if ((DAT_004a6348 & 1) != 0) {
    for (local_8 = DAT_00632510; local_8 != (undefined4 *)0x0; local_8 = (undefined4 *)*local_8) {
      if ((local_8[5] & 0xffff) == 4) {
        (*param_1)(local_8 + 8,param_2);
      }
    }
  }
  return;
}
```

---

## FID_conflict:AtlIsValidAddress — 0x476230

- Classification : internal
- Corps : `0x476230–0x47627a`
- État : pseudocode obtenu
- Evidence : `ev_1cbe4d2e851ecd2e1066348c2958b11d567296a60d918df70941f2bc1073c6d4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xe` — `KERNEL32.DLL::IsBadReadPtr`
- `EXTERNAL:0x3c` — `KERNEL32.DLL::IsBadWritePtr`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Multiple Matches With Different Base Names
    int __cdecl ATL::AtlIsValidAddress(void const *,unsigned int,int)
    __CrtIsValidPointer
   
   Library: Visual Studio 2003 Debug */

undefined4 FID_conflict_AtlIsValidAddress(void *param_1,UINT_PTR param_2,int param_3)

{
  BOOL BVar1;
  
  if (((param_1 != (void *)0x0) && (BVar1 = IsBadReadPtr(param_1,param_2), BVar1 == 0)) &&
     ((param_3 == 0 || (BVar1 = IsBadWritePtr(param_1,param_2), BVar1 == 0)))) {
    return 1;
  }
  return 0;
}
```

---

## FUN_00476280 — 0x476280

- Classification : internal
- Corps : `0x476280–0x47630f`
- État : pseudocode obtenu
- Evidence : `ev_90a34d2f2cee8cf98e048a12e7f9b89ea9320643c5baa10b5ed017025fda5a3d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xf` — `KERNEL32.DLL::HeapValidate`
- `0x476230` — `FID_conflict:AtlIsValidAddress`
- `0x47e790` — `FUN_0047e790`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
BOOL FUN_00476280(int param_1)

{
  BOOL BVar1;
  int iVar2;
  undefined1 local_10 [4];
  char *local_c;
  undefined1 local_8 [4];
  
  if (param_1 == 0) {
    BVar1 = 0;
  }
  else {
    iVar2 = FID_conflict_AtlIsValidAddress(param_1 + -0x20,0x20,1);
    if (iVar2 == 0) {
      BVar1 = 0;
    }
    else {
      local_c = (char *)FUN_0047e790(param_1 + -0x20,local_10,local_8);
      if (local_c == (char *)0x0) {
        if ((DAT_00632528 & 0x8000) == 0) {
          BVar1 = HeapValidate(DAT_00633d04,0,(LPCVOID)(param_1 + -0x20));
        }
        else {
          BVar1 = 1;
        }
      }
      else if (*local_c == '\0') {
        BVar1 = 0;
      }
      else {
        BVar1 = 1;
      }
    }
  }
  return BVar1;
}
```

---


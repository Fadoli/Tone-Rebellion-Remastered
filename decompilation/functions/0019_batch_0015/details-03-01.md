# 0019_batch_0015 — détails (1/3)

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

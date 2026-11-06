# 0020_batch_0016 — détails (1/2)

## FUN_0047c230 — 0x47c230

- Classification : internal
- Corps : `0x47c230–0x47c2c8`, `0x47c2e0–0x47c326`
- État : pseudocode obtenu
- Evidence : `ev_1d2d7f98c0246e7e3263fdb9ddd71f76c0c7093c2eabc9ff6c44f5c68a15d004`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47c930` — `__CallSettingFrame@12`
- `0x47ca30` — `FUN_0047ca30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047c230(int param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined4 *unaff_FS_OFFSET;
  int local_20;
  undefined4 local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_00495d50;
  puStack_10 = &LAB_00480ac8;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  for (local_20 = *(int *)(param_1 + 8); local_8 = 0xffffffff, local_20 != param_4;
      local_20 = *(int *)(*(int *)(param_3 + 8) + local_20 * 8)) {
    if ((local_20 < 0) || (*(int *)(param_3 + 4) <= local_20)) {
      FUN_0047ca30();
    }
    local_8 = 0;
    if (*(int *)(*(int *)(param_3 + 8) + 4 + local_20 * 8) != 0) {
      __CallSettingFrame_12(*(undefined4 *)(*(int *)(param_3 + 8) + 4 + local_20 * 8),param_1,0x103)
      ;
    }
  }
  if (local_20 != param_4) {
    FUN_0047ca30();
  }
  *(int *)(param_1 + 8) = local_20;
  *unaff_FS_OFFSET = local_14;
  return;
}
```

---

## ArrayUnwindFilter — 0x47c330

- Classification : internal
- Corps : `0x47c330–0x47c35b`
- État : pseudocode obtenu
- Evidence : `ev_639f0762c7171f8593468405303e3e57c4b4da363478692453f951318bfa3166`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47c980` — `FUN_0047c980`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    int __cdecl ArrayUnwindFilter(struct _EXCEPTION_POINTERS *)
   
   Library: Visual Studio */

int __cdecl ArrayUnwindFilter(_EXCEPTION_POINTERS *param_1)

{
  if (param_1->ExceptionRecord->ExceptionCode == 0xe06d7363) {
    FUN_0047c980();
  }
  return 0;
}
```

---

## CatchIt — 0x47c360

- Classification : internal
- Corps : `0x47c360–0x47c416`
- État : pseudocode obtenu
- Evidence : `ev_98cd911a6976a764abeac19081afe8531ae8af5a6824ba7ecddcde8aab90e41f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472fd0` — `FUN_00472fd0`
- `0x473040` — `FUN_00473040`
- `0x47c230` — `FUN_0047c230`
- `0x47c420` — `FUN_0047c420`
- `0x47c5c0` — `FUN_0047c5c0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    void __cdecl CatchIt(struct EHExceptionRecord *,struct EHRegistrationNode *,struct _CONTEXT
   *,void *,struct _s_FuncInfo const *,struct _s_HandlerType const *,struct _s_CatchableType const
   *,struct _s_TryBlockMapEntry const *,int,struct EHRegistrationNode *,unsigned char)
   
   Library: Visual Studio */

void __cdecl
CatchIt(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,void *param_4,
       _s_FuncInfo *param_5,_s_HandlerType *param_6,_s_CatchableType *param_7,
       _s_TryBlockMapEntry *param_8,int param_9,EHRegistrationNode *param_10,uchar param_11)

{
  int iVar1;
  
  if (param_7 != (_s_CatchableType *)0x0) {
    FUN_0047c5c0(param_1,param_2,param_6,param_7);
  }
  if (param_10 == (EHRegistrationNode *)0x0) {
    FUN_00473040(param_2,param_1);
  }
  else {
    FUN_00473040(param_10,param_1);
  }
  FUN_0047c230(param_2,param_4,param_5,*(undefined4 *)param_8);
  *(int *)(param_2 + 8) = *(int *)(param_8 + 4) + 1;
  iVar1 = FUN_0047c420(param_1,param_2,param_3,param_5,*(undefined4 *)(param_6 + 0xc),param_9,0x100)
  ;
  if (iVar1 != 0) {
    FUN_00472fd0(iVar1,param_2);
  }
  return;
}
```

---

---

## FUN_0047c420 — 0x47c420

- Classification : internal
- Corps : `0x47c420–0x47c4b3`, `0x47c4e5–0x47c4f2`
- État : pseudocode obtenu
- Evidence : `ev_e97c4d9f1670a16cce2a081432431f851d5b5f78acc1693c9f5599fe370a10ff`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x47c4f1 to 0x47c54d FUN_0047c54d (external=false, thunk=false, hasNoReturn=false); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.

### Appels directs

- `0x473110` — `FUN_00473110`
- `0x47c4f3` — `FUN_0047c4f3`
- `0x47c54d` — `FUN_0047c54d`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047c420(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_00495d60;
  puStack_10 = &LAB_00480ac8;
  uStack_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_14;
  DAT_00632590 = param_1;
  DAT_00632594 = param_3;
  local_8 = 1;
  FUN_00473110(param_2,param_4,param_5,param_6,param_7);
  local_8 = 0xffffffff;
  FUN_0047c4f3();
  FUN_0047c54d();
  return;
}
```

---

---

## FUN_0047c4f3 — 0x47c4f3

- Classification : internal
- Corps : `0x47c4f3–0x47c54c`
- État : pseudocode obtenu
- Evidence : `ev_e6376be9f005d2e9f6e55af47410bc883d9680df956e346a13092935183a36f0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47345a` — `__abnormal_termination`
- `0x47c850` — `___DestructExceptionObject`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047c4f3(void)

{
  int iVar1;
  int unaff_EBP;
  
  *(undefined4 *)(*(int *)(unaff_EBP + 0xc) + -4) = *(undefined4 *)(unaff_EBP + -0x28);
  DAT_00632590 = *(undefined4 *)(unaff_EBP + -0x1c);
  DAT_00632594 = *(undefined4 *)(unaff_EBP + -0x20);
  if ((((**(int **)(unaff_EBP + 8) == -0x1f928c9d) &&
       (*(int *)(*(int *)(unaff_EBP + 8) + 0x10) == 3)) &&
      (*(int *)(*(int *)(unaff_EBP + 8) + 0x14) == 0x19930520)) &&
     ((*(int *)(unaff_EBP + -0x24) == 0 && (*(int *)(unaff_EBP + -0x2c) != 0)))) {
    iVar1 = __abnormal_termination();
    ___DestructExceptionObject(*(undefined4 *)(unaff_EBP + 8),iVar1);
  }
  return;
}
```

---

---

## FUN_0047c54d — 0x47c54d

- Classification : internal
- Corps : `0x47c54d–0x47c560`
- État : pseudocode obtenu
- Evidence : `ev_6609a2d41de523ff9a9a6afe69f526f58d2e0fa3f28cbb0f9135501fc927679b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047c54d(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET;
  
  uVar1 = *(undefined4 *)(unaff_EBP + -0x2c);
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return uVar1;
}
```

---

---

## FUN_0047c570 — 0x47c570

- Classification : internal
- Corps : `0x47c570–0x47c5b1`
- État : pseudocode obtenu
- Evidence : `ev_038c129238c27b78d60094d468c56331425aa7020acdf3b1448e948426aad3e9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047c570(int *param_1)

{
  undefined4 uVar1;
  
  param_1 = (int *)*param_1;
  if ((((*param_1 == -0x1f928c9d) && (param_1[4] == 3)) && (param_1[5] == 0x19930520)) &&
     (param_1[7] == 0)) {
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

## FUN_0047c5c0 — 0x47c5c0

- Classification : internal
- Corps : `0x47c5c0–0x47c81b`, `0x47c831–0x47c841`
- État : pseudocode obtenu
- Evidence : `ev_f5dccaa679a1c60612c04dd9aa5aede94c628b04458d779d0a04d5a5c2e5158e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x473020` — `FUN_00473020`
- `0x473030` — `FUN_00473030`
- `0x47c8e0` — `FID_conflict:___AdjustPointer`
- `0x47ca30` — `FUN_0047ca30`
- `0x483210` — `FUN_00483210`
- `0x484c40` — `FUN_00484c40`
- `0x484c70` — `FUN_00484c70`
- `0x484ca0` — `_ValidateExecute`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047c5c0(int param_1,int param_2,uint *param_3,uint *param_4)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_00495d78;
  puStack_10 = &LAB_00480ac8;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  if (((param_3[1] != 0) && (*(char *)(param_3[1] + 8) != '\0')) && (param_3[2] != 0)) {
    piVar1 = (int *)(param_2 + 0xc + param_3[2]);
    local_8 = 0;
    if ((*param_3 & 8) == 0) {
      if ((*param_4 & 1) == 0) {
        if (param_4[6] == 0) {
          iVar2 = FUN_00484c40(*(undefined4 *)(param_1 + 0x18),1);
          if ((iVar2 == 0) || (iVar2 = FUN_00484c70(piVar1,1), iVar2 == 0)) {
            FUN_0047ca30();
          }
          else {
            uVar3 = FID_conflict____AdjustPointer
                              (*(undefined4 *)(param_1 + 0x18),param_4 + 2,param_4[5]);
            FUN_00483210(piVar1,uVar3);
          }
        }
        else {
          iVar2 = FUN_00484c40(*(undefined4 *)(param_1 + 0x18),1);
          if (((iVar2 == 0) || (iVar2 = FUN_00484c70(piVar1,1), iVar2 == 0)) ||
             (iVar2 = _ValidateExecute((_func_int *)param_4[6]), iVar2 == 0)) {
            FUN_0047ca30();
          }
          else if ((*param_4 & 4) == 0) {
            uVar3 = FID_conflict____AdjustPointer(*(undefined4 *)(param_1 + 0x18),param_4 + 2);
            FUN_00473020(piVar1,param_4[6],uVar3);
          }
          else {
            uVar3 = FID_conflict____AdjustPointer(*(undefined4 *)(param_1 + 0x18),param_4 + 2,1);
            FUN_00473030(piVar1,param_4[6],uVar3);
          }
        }
      }
      else {
        iVar2 = FUN_00484c40(*(undefined4 *)(param_1 + 0x18),1);
        if ((iVar2 == 0) || (iVar2 = FUN_00484c70(piVar1,1), iVar2 == 0)) {
          FUN_0047ca30();
        }
        else {
          FUN_00483210(piVar1,*(undefined4 *)(param_1 + 0x18),param_4[5]);
          if ((param_4[5] == 4) && (*piVar1 != 0)) {
            iVar2 = FID_conflict____AdjustPointer(*piVar1,param_4 + 2);
            *piVar1 = iVar2;
          }
        }
      }
    }
    else {
      iVar2 = FUN_00484c40(*(undefined4 *)(param_1 + 0x18),1);
      if ((iVar2 == 0) || (iVar2 = FUN_00484c70(piVar1,1), iVar2 == 0)) {
        FUN_0047ca30();
      }
      else {
        *piVar1 = *(int *)(param_1 + 0x18);
        iVar2 = FID_conflict____AdjustPointer(*piVar1,param_4 + 2);
        *piVar1 = iVar2;
      }
    }
  }
  *unaff_FS_OFFSET = local_14;
  return;
}
```

---

## ___DestructExceptionObject — 0x47c850

- Classification : internal
- Corps : `0x47c850–0x47c8ad`, `0x47c8cc–0x47c8dc`
- État : pseudocode obtenu
- Evidence : `ev_a4e42fcc3449b2c541ca3d70a50572032622656df7a5b2629e8516e2fc9fb0b4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x473010` — `_CallMemberFunction0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    ___DestructExceptionObject
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

void ___DestructExceptionObject(int param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_00495d88;
  puStack_10 = &LAB_00480ac8;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  if ((param_1 != 0) && (*(int *)(*(int *)(param_1 + 0x1c) + 4) != 0)) {
    local_8 = 0;
    _CallMemberFunction0(*(void **)(param_1 + 0x18),*(void **)(*(int *)(param_1 + 0x1c) + 4));
  }
  *unaff_FS_OFFSET = local_14;
  return;
}
```

---

## FID_conflict:___AdjustPointer — 0x47c8e0

- Classification : internal
- Corps : `0x47c8e0–0x47c925`
- État : pseudocode obtenu
- Evidence : `ev_b540e6449331018f2d0cdb3e7eba812afa85c3dba278d17c4fc5bc9975e1ad31`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Multiple Matches With Different Base Names
    void * __cdecl AdjustPointer(void *,struct PMD const &)
    ___AdjustPointer
   
   Library: Visual Studio */

int FID_conflict____AdjustPointer(int param_1,int *param_2)

{
  int local_8;
  
  local_8 = param_1 + *param_2;
  if (-1 < param_2[1]) {
    local_8 = local_8 + *(int *)(*(int *)(param_1 + param_2[1]) + param_2[2]) + param_2[1];
  }
  return local_8;
}
```

---

## __CallSettingFrame@12 — 0x47c930

- Classification : internal
- Corps : `0x47c930–0x47c97b`
- État : pseudocode obtenu
- Evidence : `ev_e55398e47f33e83b10563f23cf5a4d0023f27dd55a8d94a92f2fc4ae1e46c2df`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47347d` — `__NLG_Notify1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Restarted to delay deadcode elimination for space: stack */
/* Library Function - Single Match
    __CallSettingFrame@12
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
   Studio 2019 Release */

void __CallSettingFrame_12(undefined4 param_1,undefined4 param_2,int param_3)

{
  code *pcVar1;
  
  pcVar1 = (code *)__NLG_Notify1(param_3);
  (*pcVar1)();
  if (param_3 == 0x100) {
    param_3 = 2;
  }
  __NLG_Notify1(param_3);
  return;
}
```

---

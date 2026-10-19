# 0020_batch_0016 — détails (2/2)

## FUN_0047bbb0 — 0x47bbb0

- Classification : internal
- Corps : `0x47bbb0–0x47bc07`
- État : pseudocode obtenu
- Evidence : `ev_84fa6a847bb87b9aa416afc857d704fc68d48df685cea1d2162e991eb85e3060`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_0047bbb0(uint param_1)

{
  uint local_c;
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 4;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,4);
  }
  if (local_8 == 0) {
    local_c = (param_1 & 0xffffffdf) - 7;
  }
  else {
    local_c = param_1;
  }
  return local_c;
}
```

---

## __inc — 0x47bc10

- Classification : internal
- Corps : `0x47bc10–0x47bc60`
- État : pseudocode obtenu
- Evidence : `ev_ac8547c91590ccbcfb4c099bcd58b976557080fbb6ecdd14995ca7d751958014`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x484870` — `FUN_00484870`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __inc
   
   Library: Visual Studio 2003 Debug */

uint __inc(int *param_1)

{
  uint local_8;
  
  param_1[1] = param_1[1] + -1;
  if (param_1[1] < 0) {
    local_8 = FUN_00484870(param_1);
  }
  else {
    local_8 = (uint)*(byte *)*param_1;
    *param_1 = *param_1 + 1;
  }
  return local_8;
}
```

---

---

## FUN_0047bc70 — 0x47bc70

- Classification : internal
- Corps : `0x47bc70–0x47bc8a`
- État : pseudocode obtenu
- Evidence : `ev_eb62891608362fb0b6f9fa292afb26a00d0bd10de9c2290c3d0007038ad09e4c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x484a50` — `FUN_00484a50`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047bc70(int param_1,undefined4 param_2)

{
  if (param_1 != -1) {
    FUN_00484a50(param_1,param_2);
  }
  return;
}
```

---

## __whiteout — 0x47bc90

- Classification : internal
- Corps : `0x47bc90–0x47bcc8`
- État : pseudocode obtenu
- Evidence : `ev_c8bee5f429efd0b58d8810e9ce16708d3321168b7d993ab264ec1029482ca01b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47bc10` — `__inc`
- `0x4845c0` — `FUN_004845c0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __whiteout
   
   Library: Visual Studio 2003 Debug */

undefined4 __whiteout(int *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  do {
    *param_1 = *param_1 + 1;
    uVar1 = __inc(param_2);
    iVar2 = FUN_004845c0(uVar1);
  } while (iVar2 != 0);
  return uVar1;
}
```

---

---

## FUN_0047bcd0 — 0x47bcd0

- Classification : internal
- Corps : `0x47bcd0–0x47bdb8`
- État : pseudocode obtenu
- Evidence : `ev_ca7a4d4b182e3043133fdccbac5c92b1cf70a8ea085f9a47660d1f76a480ee90`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47bdc0` — `FUN_0047bdc0`
- `0x47c230` — `FUN_0047c230`
- `0x47ca30` — `FUN_0047ca30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4
FUN_0047bcd0(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int *param_5,
            int param_6,undefined4 param_7,uint param_8)

{
  undefined4 uVar1;
  
  if (*param_5 == 0x19930520) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_0047ca30();
  }
  if ((param_1[1] & 0x66U) == 0) {
    if (param_5[3] != 0) {
      if (((*param_1 == -0x1f928c9d) && (0x19930520 < (uint)param_1[5])) &&
         (*(code **)(param_1[7] + 8) != (code *)0x0)) {
        uVar1 = (**(code **)(param_1[7] + 8))
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
        return uVar1;
      }
      FUN_0047bdc0(param_1,param_2,param_3,param_4,param_5,param_8 & 0xff,param_6,param_7,uVar1);
    }
  }
  else if ((param_5[1] != 0) && (param_6 == 0)) {
    FUN_0047c230(param_2,param_4,param_5,0xffffffff);
  }
  return 1;
}
```

---

---

## FUN_0047bdc0 — 0x47bdc0

- Classification : internal
- Corps : `0x47bdc0–0x47c047`
- État : pseudocode obtenu
- Evidence : `ev_73092d072a5a346f49a7a34462c4c61ef79e94b1cbc701789872b0d7ae35d071`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x473320` — `FUN_00473320`
- `0x47c050` — `FUN_0047c050`
- `0x47c170` — `FUN_0047c170`
- `0x47c360` — `CatchIt`
- `0x47c850` — `___DestructExceptionObject`
- `0x47c980` — `FUN_0047c980`
- `0x47ca30` — `FUN_0047ca30`
- `0x484c40` — `FUN_00484c40`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047bdc0(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,
                 void *param_4,_s_FuncInfo *param_5,char param_6,int param_7,
                 EHRegistrationNode *param_8)

{
  EHExceptionRecord *pEVar1;
  int iVar2;
  undefined4 in_stack_ffffffd0;
  int local_24;
  int local_20;
  _s_HandlerType *local_1c;
  undefined4 *local_18;
  uint local_14;
  _s_TryBlockMapEntry *local_10;
  uint local_c;
  int local_8;
  
  local_8 = *(int *)(param_2 + 8);
  if ((local_8 < -1) || (*(int *)(param_5 + 4) <= local_8)) {
    FUN_0047ca30();
  }
  pEVar1 = DAT_00632590;
  if ((((*(int *)param_1 == -0x1f928c9d) && (*(int *)(param_1 + 0x10) == 3)) &&
      (*(int *)(param_1 + 0x14) == 0x19930520)) && (*(int *)(param_1 + 0x1c) == 0)) {
    if (DAT_00632590 == (EHExceptionRecord *)0x0) {
      return;
    }
    param_1 = DAT_00632590;
    param_3 = DAT_00632594;
    iVar2 = FUN_00484c40(DAT_00632590,1);
    if (iVar2 == 0) {
      FUN_0047ca30();
    }
    if (((*(int *)pEVar1 == -0x1f928c9d) && (*(int *)(pEVar1 + 0x10) == 3)) &&
       ((*(int *)(pEVar1 + 0x14) == 0x19930520 && (*(int *)(pEVar1 + 0x1c) == 0)))) {
      in_stack_ffffffd0 = FUN_0047ca30();
    }
    else {
      in_stack_ffffffd0 = 0;
    }
  }
  if (((*(int *)param_1 == -0x1f928c9d) && (*(int *)(param_1 + 0x10) == 3)) &&
     (*(int *)(param_1 + 0x14) == 0x19930520)) {
    local_10 = (_s_TryBlockMapEntry *)FUN_00473320(param_5,param_7,local_8,&local_14,&local_c);
    for (; local_14 < local_c; local_14 = local_14 + 1) {
      if ((*(int *)local_10 <= local_8) && (local_8 <= *(int *)(local_10 + 4))) {
        local_1c = *(_s_HandlerType **)(local_10 + 0x10);
        for (local_24 = *(int *)(local_10 + 0xc); 0 < local_24; local_24 = local_24 + -1) {
          local_18 = *(undefined4 **)(*(int *)(param_1 + 0x1c) + 0xc);
          for (local_20 = **(int **)(*(int *)(param_1 + 0x1c) + 0xc); local_18 = local_18 + 1,
              0 < local_20; local_20 = local_20 + -1) {
            iVar2 = FUN_0047c170(local_1c,*local_18,*(undefined4 *)(param_1 + 0x1c));
            if (iVar2 != 0) {
              CatchIt(param_1,param_2,param_3,param_4,param_5,local_1c,(_s_CatchableType *)*local_18
                      ,local_10,param_7,param_8,(uchar)in_stack_ffffffd0);
              goto LAB_0047beef;
            }
          }
          local_1c = local_1c + 0x10;
        }
      }
LAB_0047beef:
      local_10 = local_10 + 0x14;
    }
    if (param_6 != '\0') {
      ___DestructExceptionObject(param_1,1);
    }
  }
  else if (param_6 == '\0') {
    FUN_0047c050(param_1,param_2,param_3,param_4,param_5,local_8,param_7,param_8);
  }
  else {
    FUN_0047c980();
  }
  return;
}
```

---

---

## FUN_0047c050 — 0x47c050

- Classification : internal
- Corps : `0x47c050–0x47c160`
- État : pseudocode obtenu
- Evidence : `ev_ace47b0f9fe86a5153ab1df72fc8d38a1d04674c856377dae8446818601d1603`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4731c0` — `FUN_004731c0`
- `0x473320` — `FUN_00473320`
- `0x47c360` — `CatchIt`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047c050(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,
                 void *param_4,_s_FuncInfo *param_5,int param_6,int param_7,
                 EHRegistrationNode *param_8)

{
  int iVar1;
  uint in_stack_fffffff0;
  _s_TryBlockMapEntry *local_c;
  uint local_8;
  
  if ((DAT_00632598 == 0) ||
     (iVar1 = FUN_004731c0(param_1,param_2,param_3,param_4,param_5,param_7,param_8), iVar1 == 0)) {
    local_c = (_s_TryBlockMapEntry *)FUN_00473320(param_5,param_7,param_6,&stack0xfffffff0,&local_8)
    ;
    for (; in_stack_fffffff0 < local_8; in_stack_fffffff0 = in_stack_fffffff0 + 1) {
      if (((*(int *)local_c <= param_6) && (param_6 <= *(int *)(local_c + 4))) &&
         ((*(int *)(*(int *)(local_c + 0x10) + 4 + (*(int *)(local_c + 0xc) + -1) * 0x10) == 0 ||
          (*(char *)(*(int *)(*(int *)(local_c + 0x10) + 4 + (*(int *)(local_c + 0xc) + -1) * 0x10)
                    + 8) == '\0')))) {
        CatchIt(param_1,param_2,param_3,param_4,param_5,
                (_s_HandlerType *)(*(int *)(local_c + 0x10) + (*(int *)(local_c + 0xc) + -1) * 0x10)
                ,(_s_CatchableType *)0x0,local_c,param_7,param_8,(uchar)in_stack_fffffff0);
      }
      local_c = local_c + 0x14;
    }
  }
  return;
}
```

---

---

## FUN_0047c170 — 0x47c170

- Classification : internal
- Corps : `0x47c170–0x47c225`
- État : pseudocode obtenu
- Evidence : `ev_cfa04a3b6dce81102485ef47d51e63c250adc405795640fa6b5e348fba1f1254`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4774f0` — `_strcmp`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047c170(uint *param_1,uint *param_2,uint *param_3)

{
  int iVar1;
  undefined4 local_8;
  
  if ((param_1[1] == 0) || (*(char *)(param_1[1] + 8) == '\0')) {
    local_8 = 1;
  }
  else if ((param_1[1] == param_2[1]) ||
          (iVar1 = _strcmp((char *)(param_1[1] + 8),(char *)(param_2[1] + 8)), iVar1 == 0)) {
    if (((((*param_2 & 2) == 0) || ((*param_1 & 8) != 0)) &&
        (((*param_3 & 1) == 0 || ((*param_1 & 1) != 0)))) &&
       (((*param_3 & 2) == 0 || ((*param_1 & 2) != 0)))) {
      local_8 = 1;
    }
    else {
      local_8 = 0;
    }
  }
  else {
    local_8 = 0;
  }
  return local_8;
}
```

---

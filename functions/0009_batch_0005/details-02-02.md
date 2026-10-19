# 0009_batch_0005 — détails (2/2)

## FUN_00414cff — 0x414cff

- Classification : internal
- Corps : `0x414cff–0x414d88`
- État : pseudocode obtenu
- Evidence : `ev_292c126f9d1e9cf39aec739a8bedd0a396b99fa4619478f64b291220f147b90d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00414cff(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int local_c;
  int local_8;
  
  local_8 = -1;
  if (DAT_004c0b18 == 0) {
    _memset(&DAT_004c0988,0,400);
    DAT_004c0b18 = 1;
  }
  local_c = 0;
  do {
    if (99 < local_c) {
LAB_00414d62:
      if (local_8 != -1) {
        *(undefined4 *)(&DAT_004c0988 + local_8 * 4) = param_3;
        *(undefined4 *)(&DAT_004c07f8 + local_8 * 4) = param_2;
      }
      return param_3;
    }
    if (*(int *)(&DAT_004c0988 + local_c * 4) == 0) {
      local_8 = local_c;
      goto LAB_00414d62;
    }
    local_c = local_c + 1;
  } while( true );
}
```

---

---

## FUN_00414d89 — 0x414d89

- Classification : internal
- Corps : `0x414d89–0x414de4`
- État : pseudocode obtenu
- Evidence : `ev_179eafca94eedad4e62b08a7b61dfcb9553f90dd32284f86b1144b85a3f479d0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414d89(undefined4 param_1,int param_2)

{
  int local_c;
  int local_8;
  
  local_8 = -1;
  if (param_2 != 0) {
    for (local_c = 0; local_c < 100; local_c = local_c + 1) {
      if (*(int *)(&DAT_004c0988 + local_c * 4) == param_2) {
        local_8 = local_c;
        break;
      }
    }
  }
  if (local_8 != -1) {
    *(undefined4 *)(&DAT_004c0988 + local_8 * 4) = 0;
  }
  return;
}
```

---

---

## FUN_00414de5 — 0x414de5

- Classification : internal
- Corps : `0x414de5–0x414e85`
- État : pseudocode obtenu
- Evidence : `ev_f7d1c93967d8386fe88f260a20c3c5e0a52399d9beeb535a3683fd77d5341454`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x49bcfc` — "HeapCheck:"
- `0x49bd08` — " No mallocs yet"
- `0x49bd18` — " %x,%d"
- `0x49bd20` — " Total: %d"

### Pseudocode Ghidra

```c
void FUN_00414de5(void)

{
  int local_c;
  int local_8;
  
  thunk_FUN_00414ad0(s_HeapCheck__0049bcfc);
  if (DAT_004c0b18 == 0) {
    thunk_FUN_00414ad0(s_No_mallocs_yet_0049bd08);
  }
  else {
    local_8 = 0;
    for (local_c = 0; local_c < 100; local_c = local_c + 1) {
      if (*(int *)(&DAT_004c0988 + local_c * 4) != 0) {
        thunk_FUN_00414ad0(s__x__d_0049bd18,*(undefined4 *)(&DAT_004c0988 + local_c * 4),
                           *(undefined4 *)(&DAT_004c07f8 + local_c * 4));
        local_8 = local_8 + *(int *)(&DAT_004c07f8 + local_c * 4);
      }
    }
    thunk_FUN_00414ad0(s_Total___d_0049bd20,local_8);
  }
  return;
}
```

---

---

## FUN_00414f80 — 0x414f80

- Classification : internal
- Corps : `0x414f80–0x414f8e`
- État : pseudocode obtenu
- Evidence : `ev_e5f145a5289960c69663909f0358e8244311fb4789da7e773555e1165702836c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x414f8f` — `FUN_00414f8f`
- `0x414f9e` — `FUN_00414f9e`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414f80(void)

{
  FUN_00414f8f();
  FUN_00414f9e();
  return;
}
```

---

---

## FUN_00414f8f — 0x414f8f

- Classification : internal
- Corps : `0x414f8f–0x414f9d`
- État : pseudocode obtenu
- Evidence : `ev_b33c4713b67c505085d3d127d7879a71497e0a3db73ee7db41e89e4b42cc68cc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401c17` — `thunk_FUN_004152ea`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414f8f(void)

{
  thunk_FUN_004152ea();
  return;
}
```

---

---

## FUN_00414f9e — 0x414f9e

- Classification : internal
- Corps : `0x414f9e–0x414faf`
- État : pseudocode obtenu
- Evidence : `ev_d222f2942c3e1068dd8b748d37f39029a8b8c2fdeeeeab9443a70d82ee79e3fc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476c60` — `FUN_00476c60`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414f9e(void)

{
  FUN_00476c60(FUN_00414fb0);
  return;
}
```

---

---

## FUN_00414fb0 — 0x414fb0

- Classification : internal
- Corps : `0x414fb0–0x414fbe`
- État : pseudocode obtenu
- Evidence : `ev_35e0ee6d85b2f77c9949aab6684fa2c3cc55c9b31885627255ba681998dda213`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b4` — `thunk_FUN_004152f8`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414fb0(void)

{
  thunk_FUN_004152f8();
  return;
}
```

---

---

## FUN_00414fbf — 0x414fbf

- Classification : internal
- Corps : `0x414fbf–0x415062`
- État : pseudocode obtenu
- Evidence : `ev_2225dcaac634d008b70b7c2c05ca964d8ad85415a230aca5f56f1143a85007f7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00414fbf(short *param_1,int *param_2,int *param_3)

{
  short sVar1;
  short sVar2;
  
  if ((param_1[8] & 2U) == 0) {
    sVar1 = param_1[1];
    if (param_2 != (int *)0x0) {
      *param_2 = (int)*(short *)(&DAT_006137c8 + sVar1 * 0x4c);
    }
    if (param_3 != (int *)0x0) {
      *param_3 = (int)*(short *)(&DAT_006137ca + sVar1 * 0x4c);
    }
  }
  else {
    sVar1 = *(short *)(&DAT_006137c6 + *param_1 * 0x4c);
    sVar2 = param_1[1];
    if (param_2 != (int *)0x0) {
      *param_2 = (int)*(short *)(&DAT_005ec640 + sVar2 * 0x60 + sVar1 * 0x29e8);
    }
    if (param_3 != (int *)0x0) {
      *param_3 = (int)*(short *)((int)(&DAT_005ec640 + sVar2 * 0x60 + sVar1 * 0x29e8) + 2);
    }
  }
  return;
}
```

---

---

## FUN_00415063 — 0x415063

- Classification : internal
- Corps : `0x415063–0x41511a`
- État : pseudocode obtenu
- Evidence : `ev_51b2bb858f6899cc3394bba5d8f9a9b78dfc787e365dfded36b405be94608b8f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00415063(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = DAT_00618e44 / 2;
  if (DAT_00618e44 % 2 != 0) {
    *(short *)(param_2 + 6) = *(short *)(param_2 + 6) + 1;
    if (*(short *)(param_1 + 0x1c + *(short *)(param_2 + 4) * 2) < *(short *)(param_2 + 6)) {
      *(ushort *)(param_2 + 0x10) = *(ushort *)(param_2 + 0x10) | 0x20;
    }
    if (*(short *)(param_2 + 6) < *(short *)(param_1 + 0x14 + *(short *)(param_2 + 4) * 2)) {
      *(undefined2 *)(param_2 + 6) = *(undefined2 *)(param_1 + 0x14 + *(short *)(param_2 + 4) * 2);
    }
    uVar1 = (uint)*(short *)(param_1 + 0x1c + *(short *)(param_2 + 4) * 2);
    if ((int)uVar1 < (int)*(short *)(param_2 + 6)) {
      *(undefined2 *)(param_2 + 6) = *(undefined2 *)(param_1 + 0x1c + *(short *)(param_2 + 4) * 2);
      uVar1 = param_2;
    }
  }
  return uVar1;
}
```

---

---

## FUN_0041511b — 0x41511b

- Classification : internal
- Corps : `0x41511b–0x415219`
- État : pseudocode obtenu
- Evidence : `ev_a15cac1c225306aedb8bc03c1e95425c2b687dbd7017886d1a12843486b61afd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40173a` — `thunk_FUN_004672a6`
- `0x40250e` — `thunk_FUN_00414fbf`
- `0x472c6c` — `__ftol`
- `0x476ce4` — `FUN_00476ce4`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041511b(undefined4 param_1,int param_2,int param_3)

{
  short sVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  int local_18;
  float local_14;
  int local_10;
  float local_c;
  float local_8;
  
  local_c = (float)param_3;
  thunk_FUN_00414fbf(param_2,&local_10,&local_18);
  iVar2 = local_10 - *(short *)(param_2 + 10);
  local_14 = (float)iVar2;
  iVar3 = local_18 - *(short *)(param_2 + 0xc);
  fVar4 = (float10)FUN_00476ce4((double)((float)iVar3 * (float)iVar3 + local_14 * local_14));
  local_8 = (float)fVar4;
  if (local_c <= local_8) {
    sVar1 = __ftol(iVar3,iVar2,local_c / local_8);
    *(short *)(param_2 + 10) = *(short *)(param_2 + 10) + sVar1;
    sVar1 = __ftol();
    *(short *)(param_2 + 0xc) = *(short *)(param_2 + 0xc) + sVar1;
  }
  else {
    *(undefined2 *)(param_2 + 10) = (undefined2)local_10;
    *(undefined2 *)(param_2 + 0xc) = (undefined2)local_18;
  }
  thunk_FUN_004672a6((int)*(short *)(param_2 + 10),(int)*(short *)(param_2 + 0xc),local_10,local_18)
  ;
  return;
}
```

---

---

## FUN_0041521a — 0x41521a

- Classification : internal
- Corps : `0x41521a–0x4152bc`
- État : pseudocode obtenu
- Evidence : `ev_f8fbbf55cd3ba3901294ef07c0e87a274b1b40db63b5a23d15637973bd160dc0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401fc3` — `thunk_FUN_0041511b`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041521a(int param_1,int param_2)

{
  if (DAT_00618e44 % 2 != 0) {
    *(short *)(param_2 + 6) = *(short *)(param_2 + 6) + 1;
    if (*(short *)(param_2 + 6) < *(short *)(param_1 + 0x14 + *(short *)(param_2 + 4) * 2)) {
      *(undefined2 *)(param_2 + 6) = *(undefined2 *)(param_1 + 0x14 + *(short *)(param_2 + 4) * 2);
    }
    else if (*(short *)(param_1 + 0x1c + *(short *)(param_2 + 4) * 2) < *(short *)(param_2 + 6)) {
      *(undefined2 *)(param_2 + 6) = *(undefined2 *)(param_1 + 0x14 + *(short *)(param_2 + 4) * 2);
    }
  }
  thunk_FUN_0041511b(param_1,param_2,(int)*(short *)(param_1 + 0x24));
  return;
}
```

---

---

## FUN_004152bd — 0x4152bd

- Classification : internal
- Corps : `0x4152bd–0x4152e9`
- État : pseudocode obtenu
- Evidence : `ev_8b69a2741fd93af7eabf0a30a269d6fdfa617dfbaf866f10da933049bb5ae590`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014bf` — `thunk_FUN_00467260`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004152bd(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  
  *(short *)(param_2 + 6) = *(short *)(param_2 + 6) + 1;
  uVar1 = thunk_FUN_00467260(0x8000);
  *(undefined2 *)(param_2 + 0xc) = uVar1;
  return;
}
```

---

---

## FUN_004152ea — 0x4152ea

- Classification : internal
- Corps : `0x4152ea–0x4152f7`
- État : pseudocode obtenu
- Evidence : `ev_f947e5cf3c6ebbf23adfdc796210d0aa297b9fcfabe0ef7e94d9d4289bb2d3da`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004152ea(void)

{
  undefined4 in_ECX;
  
  return in_ECX;
}
```

---

---

## FUN_004152f8 — 0x4152f8

- Classification : internal
- Corps : `0x4152f8–0x415371`
- État : pseudocode obtenu
- Evidence : `ev_9bf3fe992f62378de95ff0c4eefcf67df6199f5b1c75bfea4a496db2b027a332`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x49bde0` — "$$$$ SFX Changed: %s using sound \"%s\""

### Pseudocode Ghidra

```c
void FUN_004152f8(void)

{
  int in_ECX;
  int iVar1;
  int local_8;
  
  for (local_8 = 0; local_8 < *(short *)(in_ECX + 0x1200); local_8 = local_8 + 1) {
    iVar1 = in_ECX + local_8 * 0x30;
    if (((*(ushort *)(iVar1 + 0x2c) & 1) != 0) && (*(short *)(iVar1 + 0x28) != -1)) {
      thunk_FUN_00414ad0(s______SFX_Changed___s_using_sound_0049bde0,iVar1,
                         &DAT_005e8230 + *(short *)(iVar1 + 0x28) * 0x48);
    }
  }
  return;
}
```

---

---

## FUN_00415372 — 0x415372

- Classification : internal
- Corps : `0x415372–0x4153b7`
- État : pseudocode obtenu
- Evidence : `ev_b87ea303ffb71fef7ea466bedd7ae47caf0d81a2e8d06b4c0b7a645324d95047`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00415372(void)

{
  int in_ECX;
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 0x20; local_8 = local_8 + 1) {
    *(undefined2 *)(in_ECX + 0x1202 + local_8 * 0x14) = 0xffff;
  }
  *(undefined2 *)(in_ECX + 0x1482) = 0;
  return;
}
```

---

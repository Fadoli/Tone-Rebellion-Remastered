# 0018_batch_0014 — détails (1/1)

## FUN_00473110 — 0x473110

- Classification : internal
- Corps : `0x473110–0x473177`
- État : pseudocode obtenu
- Evidence : `ev_be4960ae5f74699adb65e2d4cc6d0e2b6af16a2062dd85f21365772e46aeb3b4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47c930` — `__CallSettingFrame@12`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4
FUN_00473110(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,undefined4 param_5
            )

{
  undefined4 uVar1;
  int *unaff_FS_OFFSET;
  int local_18;
  code *local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  local_14 = FUN_00473180;
  local_10 = param_2;
  local_c = param_1;
  local_8 = param_4 + 1;
  local_18 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (int)&local_18;
  uVar1 = __CallSettingFrame_12(param_3,param_1,param_5);
  *unaff_FS_OFFSET = local_18;
  return uVar1;
}
```

---

---

## FUN_00473180 — 0x473180

- Classification : internal
- Corps : `0x473180–0x4731b8`
- État : pseudocode obtenu
- Evidence : `ev_cef3d3e2146302fb2afee5b60be55c79c8673378453b677bf197abf5e71cdbb6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47bcd0` — `FUN_0047bcd0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00473180(undefined4 param_1,int param_2,undefined4 param_3)

{
  FUN_0047bcd0(param_1,*(undefined4 *)(param_2 + 0xc),param_3,0,*(undefined4 *)(param_2 + 8),
               *(undefined4 *)(param_2 + 0x10),param_2,0);
  return;
}
```

---

---

## FUN_004731c0 — 0x4731c0

- Classification : internal
- Corps : `0x4731c0–0x473289`
- État : pseudocode obtenu
- Evidence : `ev_14f190a55ff26429c9369c95241a597b35a5de30e2e0d166962027fddda9d742`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4
FUN_004731c0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  int *unaff_FS_OFFSET;
  undefined4 *local_34;
  undefined4 local_30;
  undefined4 *local_2c;
  code *local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined1 *local_10;
  undefined1 *local_c;
  int local_8;
  
  local_c = &stack0xfffffffc;
  local_10 = &stack0xffffffbc;
  local_28 = FUN_00473290;
  local_24 = param_5;
  local_20 = param_2;
  local_1c = param_6;
  local_18 = param_7;
  local_8 = 0;
  local_14 = 0x47325a;
  local_2c = (undefined4 *)*unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (int)&local_2c;
  local_34 = param_1;
  local_30 = param_3;
  (*DAT_00632598)(*param_1,&local_34);
  if (local_8 == 0) {
    *unaff_FS_OFFSET = (int)local_2c;
  }
  else {
    *local_2c = *(undefined4 *)*unaff_FS_OFFSET;
    *unaff_FS_OFFSET = (int)local_2c;
  }
  return 0;
}
```

---

---

## FUN_00473290 — 0x473290

- Classification : internal
- Corps : `0x473290–0x473306`, `0x47330c–0x473310`
- État : pseudocode obtenu
- Evidence : `ev_ac28110ec0084663a05f31639a31a41f45cdaa8d7e3aae10f6e62f5462bbd258`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x473040` — `FUN_00473040`
- `0x47bcd0` — `FUN_0047bcd0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00473290(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_1 + 4) & 0x66) != 0) {
    *(undefined4 *)(param_2 + 0x24) = 1;
    return 1;
  }
  FUN_0047bcd0(param_1,*(undefined4 *)(param_2 + 0xc),param_3,0,*(undefined4 *)(param_2 + 8),
               *(undefined4 *)(param_2 + 0x10),*(undefined4 *)(param_2 + 0x14),1);
  if (*(int *)(param_2 + 0x24) == 0) {
    FUN_00473040(param_2,param_1);
  }
                    /* WARNING: Could not recover jumptable at 0x00473304. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar1 = (**(code **)(param_2 + 0x18))();
  return uVar1;
}
```

---

---

## FUN_00473320 — 0x473320

- Classification : internal
- Corps : `0x473320–0x4733a3`
- État : pseudocode obtenu
- Evidence : `ev_e7049924d25e216a9d5612f29daa879fbd1396d580815b994a25c77e9d134a56`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47ca30` — `FUN_0047ca30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00473320(int param_1,int param_2,int param_3,uint *param_4,uint *param_5)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  iVar2 = *(int *)(param_1 + 0x10);
  uVar6 = *(uint *)(param_1 + 0xc);
  uVar5 = uVar6;
  uVar4 = uVar6;
  while (uVar3 = uVar5, -1 < param_2) {
    if (uVar6 == 0xffffffff) {
      FUN_0047ca30();
    }
    uVar6 = uVar6 - 1;
    iVar1 = iVar2 + uVar6 * 0x14;
    if (((*(int *)(iVar1 + 4) < param_3) && (param_3 <= *(int *)(iVar1 + 8))) ||
       (uVar5 = uVar3, uVar6 == 0xffffffff)) {
      param_2 = param_2 + -1;
      uVar5 = uVar6;
      uVar4 = uVar3;
    }
  }
  uVar6 = uVar6 + 1;
  *param_4 = uVar6;
  *param_5 = uVar4;
  if ((*(uint *)(param_1 + 0xc) < uVar4) || (uVar4 < uVar6)) {
    FUN_0047ca30();
  }
  return iVar2 + uVar6 * 0x14;
}
```

---

## __global_unwind2 — 0x4733b0

- Classification : internal
- Corps : `0x4733b0–0x4733cf`
- État : pseudocode obtenu
- Evidence : `ev_2ef1d2c7c8431b5868657a260a5dbe25ff6501b690fc471c6a3a39c486557129`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x48af90` — `KERNEL32.DLL::RtlUnwind`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __global_unwind2
   
   Library: Visual Studio */

void __global_unwind2(PVOID param_1)

{
  RtlUnwind(param_1,(PVOID)0x4733c8,(PEXCEPTION_RECORD)0x0,(PVOID)0x0);
  return;
}
```

---

## __local_unwind2 — 0x4733f2

- Classification : internal
- Corps : `0x4733f2–0x473459`
- État : pseudocode obtenu
- Evidence : `ev_35ffe692ba90ab95af3a35772fa4288fb7fdd04b659913c914805caa9286f411`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing shows a Borland/Delphi-style SEH frame registration at 0x473408 (push 0x4733d0 followed by fs-segment stack chaining); handler 0x4733d0 lies outside this procedure's body, so callees, strings, and cross-references may omit the handler region.

### Appels directs

- `0x473486` — `FUN_00473486`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __local_unwind2
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release, Visual Studio 2003 Debug, Visual
   Studio 2003 Release */

void __local_unwind2(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uStack_1c;
  undefined1 *puStack_18;
  undefined4 local_14;
  int iStack_10;
  
  iStack_10 = param_1;
  puStack_18 = &LAB_004733d0;
  uStack_1c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_1c;
  while( true ) {
    iVar1 = *(int *)(param_1 + 8);
    iVar2 = *(int *)(param_1 + 0xc);
    if ((iVar2 == -1) || (iVar2 == param_2)) break;
    local_14 = *(undefined4 *)(iVar1 + iVar2 * 0xc);
    *(undefined4 *)(param_1 + 0xc) = local_14;
    if (*(int *)(iVar1 + 4 + iVar2 * 0xc) == 0) {
      FUN_00473486(0x101);
      (**(code **)(iVar1 + 8 + iVar2 * 0xc))();
    }
  }
  *unaff_FS_OFFSET = uStack_1c;
  return;
}
```

---

## __abnormal_termination — 0x47345a

- Classification : internal
- Corps : `0x47345a–0x47347c`
- État : pseudocode obtenu
- Evidence : `ev_d5306b70c748431a48c01507fca09810687255138ea1b708760009a84d25ffdd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __abnormal_termination
   
   Library: Visual Studio */

int __cdecl __abnormal_termination(void)

{
  int iVar1;
  int iVar2;
  int *unaff_FS_OFFSET;
  
  iVar2 = 0;
  iVar1 = *unaff_FS_OFFSET;
  if ((*(undefined1 **)(iVar1 + 4) == &LAB_004733d0) &&
     (*(int *)(iVar1 + 8) == *(int *)(*(int *)(iVar1 + 0xc) + 0xc))) {
    iVar2 = 1;
  }
  return iVar2;
}
```

---

## __NLG_Notify1 — 0x47347d

- Classification : internal
- Corps : `0x47347d–0x473485`
- État : pseudocode obtenu
- Evidence : `ev_e8bda03415e63e895acca51853bd52ee5a2c710cd5a90047a2ed6a91f83587d1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __NLG_Notify1
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual
   Studio 2019 Release */

void __NLG_Notify1(void)

{
  undefined4 in_EAX;
  undefined4 in_ECX;
  undefined4 unaff_EBP;
  
  DAT_004a6338 = in_ECX;
  DAT_004a6334 = in_EAX;
  DAT_004a633c = unaff_EBP;
  return;
}
```

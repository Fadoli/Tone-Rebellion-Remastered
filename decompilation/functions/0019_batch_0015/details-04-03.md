# 0019_batch_0015 — détails (3/3)

## FUN_00476f20 — 0x476f20

- Classification : internal
- Corps : `0x476f20–0x476ff8`
- État : pseudocode obtenu
- Evidence : `ev_1b8ee176602d114820be74a790cb81817d321f15949c6804ec035c738b2f1054`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x476fef to EXTERNAL:0xd KERNEL32.DLL::ExitProcess (external=true, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `EXTERNAL:0xd` — `KERNEL32.DLL::ExitProcess`
- `EXTERNAL:0x2f` — `KERNEL32.DLL::TerminateProcess`
- `EXTERNAL:0x41` — `KERNEL32.DLL::GetCurrentProcess`
- `0x4761a0` — `FUN_004761a0`
- `0x476a60` — `FUN_00476a60`
- `0x477000` — `__initterm`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00476f20(UINT param_1,int param_2,int param_3)

{
  HANDLE hProcess;
  uint uVar1;
  UINT uExitCode;
  int *local_8;
  
  if (DAT_00632564 == 1) {
    uExitCode = param_1;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
  }
  _DAT_00632560 = 1;
  DAT_0063255c = (undefined1)param_3;
  if (param_2 == 0) {
    if (DAT_00633e88 != (int *)0x0) {
      local_8 = DAT_00633e78;
      while (local_8 = local_8 + -1, DAT_00633e88 <= local_8) {
        if (*local_8 != 0) {
          (*(code *)*local_8)();
        }
      }
    }
    __initterm(&DAT_00498768,&DAT_00498970);
  }
  __initterm(&DAT_00498a74,&DAT_00498c7c);
  if ((DAT_00632568 == 0) && (uVar1 = FUN_004761a0(0xffffffff), (uVar1 & 0x20) != 0)) {
    DAT_00632568 = 1;
    FUN_00476a60();
  }
  if (param_3 == 0) {
    DAT_00632564 = 1;
                    /* WARNING: Subroutine does not return */
    ExitProcess(param_1);
  }
  return;
}
```

---

## __initterm — 0x477000

- Classification : internal
- Corps : `0x477000–0x477024`
- État : pseudocode obtenu
- Evidence : `ev_a5b84bcbb634928e51ac7ef425d4f2368fdf928d392b191bd7b99f0a1f07d5a5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __initterm
   
   Library: Visual Studio 2003 Debug */

void __initterm(int *param_1,int *param_2)

{
  for (; param_1 < param_2; param_1 = param_1 + 1) {
    if (*param_1 != 0) {
      (*(code *)*param_1)();
    }
  }
  return;
}
```

---

---

## FUN_00477030 — 0x477030

- Classification : internal
- Corps : `0x477030–0x4770a1`
- État : pseudocode obtenu
- Evidence : `ev_57a584137e847c94289b97f6f0701a64beeaff44e9c71d6802d0fa6219cb0049`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472e90` — `_strlen`
- `0x47f2b0` — `FUN_0047f2b0`
- `0x47f730` — `FUN_0047f730`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_00477030(byte *param_1)

{
  size_t sVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint local_8;
  
  while( true ) {
    if (DAT_004a87f4 < 2) {
      local_8 = *(ushort *)(PTR_DAT_004a85e8 + (uint)*param_1 * 2) & 8;
    }
    else {
      local_8 = FUN_0047f2b0(*param_1,8);
    }
    if (local_8 == 0) break;
    param_1 = param_1 + 1;
  }
  uVar4 = 0;
  uVar3 = 0;
  sVar1 = _strlen((char *)param_1);
  iVar2 = FUN_0047f730(param_1,sVar1,uVar3,uVar4);
  return (float10)*(double *)(iVar2 + 0x10);
}
```

---

---

## FUN_004770b0 — 0x4770b0

- Classification : internal
- Corps : `0x4770b0–0x4771ae`
- État : pseudocode obtenu
- Evidence : `ev_b519a6417f2b7f4aec0b24c729aa198cccb209bf1653fe4bd3daf6f4bcfe43c2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004770b0(byte *param_1)

{
  byte *pbVar1;
  uint uVar2;
  uint local_18;
  uint local_14;
  int local_c;
  uint local_8;
  
  while( true ) {
    if (DAT_004a87f4 < 2) {
      local_14 = *(ushort *)(PTR_DAT_004a85e8 + (uint)*param_1 * 2) & 8;
    }
    else {
      local_14 = FUN_0047f2b0(*param_1,8);
    }
    if (local_14 == 0) break;
    param_1 = param_1 + 1;
  }
  uVar2 = (uint)*param_1;
  if ((uVar2 == 0x2d) || (pbVar1 = param_1 + 1, local_8 = uVar2, uVar2 == 0x2b)) {
    local_8 = (uint)param_1[1];
    pbVar1 = param_1 + 2;
  }
  param_1 = pbVar1;
  local_c = 0;
  while( true ) {
    if (DAT_004a87f4 < 2) {
      local_18 = *(ushort *)(PTR_DAT_004a85e8 + local_8 * 2) & 4;
    }
    else {
      local_18 = FUN_0047f2b0(local_8,4);
    }
    if (local_18 == 0) break;
    local_c = local_c * 10 + -0x30 + local_8;
    local_8 = (uint)*param_1;
    param_1 = param_1 + 1;
  }
  if (uVar2 == 0x2d) {
    local_c = -local_c;
  }
  return local_c;
}
```

---

---

## FUN_004771b0 — 0x4771b0

- Classification : internal
- Corps : `0x4771b0–0x4771c0`
- État : pseudocode obtenu
- Evidence : `ev_48af362f9a14af5fbba82aca1a9bc0886ae8dd10c828130d925be591673519d9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4770b0` — `FUN_004770b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004771b0(undefined4 param_1)

{
  FUN_004770b0(param_1);
  return;
}
```

---

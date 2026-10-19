# 0018_batch_0014 — détails (3/3)

## FUN_00473040 — 0x473040

- Classification : internal
- Corps : `0x473040–0x473095`
- État : pseudocode obtenu
- Evidence : `ev_9636f23c56eab9a4b005370d41bae49714bd3b06aaec11d5e6337a980b0506e9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x48af90` — `KERNEL32.DLL::RtlUnwind`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00473040(PVOID param_1,PEXCEPTION_RECORD param_2)

{
  undefined4 *puVar1;
  undefined4 *unaff_FS_OFFSET;
  
  puVar1 = (undefined4 *)*unaff_FS_OFFSET;
  RtlUnwind(param_1,(PVOID)0x47306c,param_2,(PVOID)0x0);
  param_2->ExceptionFlags = param_2->ExceptionFlags & 0xfffffffd;
  *puVar1 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = puVar1;
  return;
}
```

---

## FID_conflict:___CxxFrameHandler3 — 0x4730a0

- Classification : internal
- Corps : `0x4730a0–0x4730db`
- État : pseudocode obtenu
- Evidence : `ev_e1699fc98eddb9c2f3f1177273aa4695167fe9bcf6065191d2431d41d52cfcaf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47bcd0` — `FUN_0047bcd0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Multiple Matches With Different Base Names
    ___CxxFrameHandler
    ___CxxFrameHandler2
    ___CxxFrameHandler3
   
   Libraries: Visual Studio 2003, Visual Studio 2005, Visual Studio 2008, Visual Studio 2010 */

undefined4
FID_conflict____CxxFrameHandler3
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0047bcd0(param_1,param_2,param_3,param_4);
  return uVar1;
}
```

---

## ___CxxLongjmpUnwind@4 — 0x4730e0

- Classification : internal
- Corps : `0x4730e0–0x473105`
- État : pseudocode obtenu
- Evidence : `ev_0da5af41e7b5c179f7a4fb82e49ac5ff5e8afb8e26c2a10269a7a3ad8ff61ecd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47c230` — `FUN_0047c230`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    ___CxxLongjmpUnwind@4
   
   Libraries: Visual Studio 2003, Visual Studio 2005, Visual Studio 2008, Visual Studio 2010 */

void ___CxxLongjmpUnwind_4(int param_1)

{
  FUN_0047c230(*(undefined4 *)(param_1 + 0x18),0,*(undefined4 *)(param_1 + 0x28),
               *(undefined4 *)(param_1 + 0x1c));
  return;
}
```

---

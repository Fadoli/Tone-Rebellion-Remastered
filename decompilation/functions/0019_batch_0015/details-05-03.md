# 0019_batch_0015 — détails (3/3)

## FUN_00478090 — 0x478090

- Classification : internal
- Corps : `0x478090–0x4780ed`
- État : pseudocode obtenu
- Evidence : `ev_fffd3754939be29f397228491ee67e1a2f4e8970ebf9a9f9f71abba48b197f68`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `EXTERNAL:0x46` — `KERNEL32.DLL::GetFileAttributesA`
- `0x47cac0` — `__dosmaperr`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00478090(LPCSTR param_1,uint param_2)

{
  DWORD DVar1;
  undefined4 uVar2;
  
  DVar1 = GetFileAttributesA(param_1);
  if (DVar1 == 0xffffffff) {
    DVar1 = GetLastError();
    __dosmaperr(DVar1);
    uVar2 = 0xffffffff;
  }
  else if (((DVar1 & 1) == 0) || ((param_2 & 2) == 0)) {
    uVar2 = 0;
  }
  else {
    _DAT_0063251c = 0xd;
    DAT_00632520 = 5;
    uVar2 = 0xffffffff;
  }
  return uVar2;
}
```

---

## FID_conflict:__ctime64 — 0x4780f0

- Classification : internal
- Corps : `0x4780f0–0x47811c`
- État : pseudocode obtenu
- Evidence : `ev_a598862934c96887792e97149f001416c9b5d956da7f2eca7cae8d26816c3064`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480450` — `_asctime`
- `0x480610` — `FUN_00480610`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Multiple Matches With Different Base Names
    __ctime64
    _ctime
   
   Library: Visual Studio 2003 Debug */

char * __cdecl FID_conflict___ctime64(__time64_t *_Time)

{
  tm *_Tm;
  char *pcVar1;
  
  _Tm = (tm *)FUN_00480610(_Time);
  if (_Tm == (tm *)0x0) {
    pcVar1 = (char *)0x0;
  }
  else {
    pcVar1 = _asctime(_Tm);
  }
  return pcVar1;
}
```

---

---

## FUN_00478120 — 0x478120

- Classification : internal
- Corps : `0x478120–0x478133`
- État : pseudocode obtenu
- Evidence : `ev_278dc631c573d3f2b4d2861250d8deb37e3054b136b141cd1a3e181bed6c2619`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47813d` — `FUN_0047813d`
- `0x47f628` — `FUN_0047f628`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00478120(void)

{
  float10 in_ST0;
  
  FUN_0047f628((double)in_ST0);
  FUN_0047813d();
  return;
}
```

---

---

## FUN_00478134 — 0x478134

- Classification : internal
- Corps : `0x478134–0x47813c`
- État : pseudocode obtenu
- Evidence : `ev_05f1047ee6aeef611ddb20d155f9d273d09cf50461fbac05a86e3ef1d123b97e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x478138 to 0x47f5e5 __fload_withFB (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `0x47f5e5` — `__fload_withFB`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00478134(void)

{
                    /* WARNING: Subroutine does not return */
  __fload_withFB();
}
```

---

---

## FUN_0047813d — 0x47813d

- Classification : internal
- Corps : `0x47813d–0x4781eb`
- État : pseudocode obtenu
- Evidence : `ev_c7fb60099c23104e6a6c49a616c28dc179f5aa084ff2a7d44b1e7c34f6f27e0d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x478182 to 0x47f64b __math_exit (external=false, thunk=false, hasNoReturn=false); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.

### Appels directs

- `0x47f557` — `__startOneArgErrorHandling`
- `0x47f5cc` — `FUN_0047f5cc`
- `0x47f64b` — `__math_exit`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_0047813d(int param_1,uint param_2)

{
  uint in_EAX;
  uint uVar1;
  bool in_ZF;
  unkbyte10 in_ST0;
  
  if (!in_ZF) {
    if ((param_2 & 0x7ff00000) == 0) {
      if (((param_2 & 0xfffff) == 0) && (param_1 == 0)) {
        uVar1 = 2;
        goto LAB_004781cd;
      }
    }
    else if ((param_2 & 0x80000000) != 0) goto LAB_0047819c;
    log2(in_ST0);
LAB_0047816a:
    if (DAT_00632500 != 0) {
      return param_2;
    }
    uVar1 = __math_exit();
    return uVar1;
  }
  if (((in_EAX & 0xfffff) != 0) || (param_1 != 0)) {
    uVar1 = FUN_0047f5cc();
    goto LAB_004781cd;
  }
  param_2 = 0;
  if ((in_EAX & 0x80000000) == 0) goto LAB_0047816a;
LAB_0047819c:
  uVar1 = 1;
LAB_004781cd:
  if (DAT_00632500 != 0) {
    return uVar1;
  }
  uVar1 = __startOneArgErrorHandling();
  return uVar1;
}
```

---

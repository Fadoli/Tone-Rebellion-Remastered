# 0021_batch_0017 — détails (2/3)

## FUN_00480610 — 0x480610

- Classification : internal
- Corps : `0x480610–0x48086f`
- État : pseudocode obtenu
- Evidence : `ev_926e4e01883a7dcac5e191152c2de332e6a8c54a2e1a73936f6035b04a43fb19`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4875e0` — `FUN_004875e0`
- `0x487940` — `FUN_00487940`
- `0x487e40` — `_gmtime`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
tm * FUN_00480610(time_t *param_1)

{
  tm *ptVar1;
  int iVar2;
  int local_8;
  
  if ((int)*param_1 < 0) {
    ptVar1 = (tm *)0x0;
  }
  else {
    FUN_004875e0();
    if (((int)*param_1 < 0x3f481) || (0x7ffc0b7e < (int)*param_1)) {
      ptVar1 = _gmtime(param_1);
      iVar2 = FUN_00487940(ptVar1);
      if (iVar2 == 0) {
        local_8 = ptVar1->tm_sec - DAT_004a8ef8;
      }
      else {
        local_8 = ptVar1->tm_sec - (DAT_004a8ef8 + DAT_004a8f00);
      }
      ptVar1->tm_sec = local_8 % 0x3c;
      if (ptVar1->tm_sec < 0) {
        ptVar1->tm_sec = ptVar1->tm_sec + 0x3c;
        local_8 = local_8 + -0x3c;
      }
      local_8 = ptVar1->tm_min + local_8 / 0x3c;
      ptVar1->tm_min = local_8 % 0x3c;
      if (ptVar1->tm_min < 0) {
        ptVar1->tm_min = ptVar1->tm_min + 0x3c;
        local_8 = local_8 + -0x3c;
      }
      local_8 = ptVar1->tm_hour + local_8 / 0x3c;
      ptVar1->tm_hour = local_8 % 0x18;
      if (ptVar1->tm_hour < 0) {
        ptVar1->tm_hour = ptVar1->tm_hour + 0x18;
        local_8 = local_8 + -0x18;
      }
      local_8 = local_8 / 0x18;
      if (local_8 < 1) {
        if (local_8 < 0) {
          ptVar1->tm_wday = (ptVar1->tm_wday + 7 + local_8) % 7;
          ptVar1->tm_mday = ptVar1->tm_mday + local_8;
          if (ptVar1->tm_mday < 1) {
            ptVar1->tm_mday = ptVar1->tm_mday + 0x1f;
            ptVar1->tm_yday = 0x16c;
            ptVar1->tm_mon = 0xb;
            ptVar1->tm_year = ptVar1->tm_year + -1;
          }
          else {
            ptVar1->tm_yday = ptVar1->tm_yday + local_8;
          }
        }
      }
      else {
        ptVar1->tm_wday = (ptVar1->tm_wday + local_8) % 7;
        ptVar1->tm_mday = ptVar1->tm_mday + local_8;
        ptVar1->tm_yday = ptVar1->tm_yday + local_8;
      }
    }
    else {
      local_8 = (int)*param_1 - DAT_004a8ef8;
      ptVar1 = _gmtime((time_t *)&local_8);
      if ((DAT_004a8efc != 0) && (iVar2 = FUN_00487940(ptVar1), iVar2 != 0)) {
        local_8 = local_8 - DAT_004a8f00;
        ptVar1 = _gmtime((time_t *)&local_8);
        ptVar1->tm_isdst = 1;
      }
    }
  }
  return ptVar1;
}
```

---

## __cintrindisp2 — 0x480870

- Classification : internal
- Corps : `0x480870–0x4808ad`
- État : pseudocode obtenu
- Evidence : `ev_b8abb7f7091e97c95bdef1e3903cb2db430276f3898fbdb30223e14691625475`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f3d7` — `__trandisp2`
- `0x480925` — `FUN_00480925`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __cintrindisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __cintrindisp2(void)

{
  __trandisp2();
  DAT_00632628 = 1;
  FUN_00480925();
  return;
}
```

---

## __cintrindisp1 — 0x4808ae

- Classification : internal
- Corps : `0x4808ae–0x4808e3`
- État : pseudocode obtenu
- Evidence : `ev_0312abacadffb8db2b33c86f00009195d05710608f190f3977bffb3d2c86efd5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f370` — `__trandisp1`
- `0x480925` — `FUN_00480925`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __cintrindisp1
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __cintrindisp1(void)

{
  __trandisp1();
  DAT_00632628 = 1;
  FUN_00480925();
  return;
}
```

---

## __ctrandisp2 — 0x4808e4

- Classification : internal
- Corps : `0x4808e4–0x48091d`
- État : pseudocode obtenu
- Evidence : `ev_4219f0b72a0436a80344486f1af96b1b85e3a38b2f22257e359b6cab0d6848c3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f3d7` — `__trandisp2`
- `0x48091e` — `FUN_0048091e`
- `0x480a81` — `__fload`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __ctrandisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __ctrandisp2(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  __fload(param_1,param_2);
  __fload(param_3,param_4);
  __trandisp2();
  FUN_0048091e();
  return;
}
```

---

---

## FUN_0048091e — 0x48091e

- Classification : internal
- Corps : `0x48091e–0x480924`
- État : pseudocode obtenu
- Evidence : `ev_eeca05c606d8d34fe9ecaf8aa1d2b04dd415b846e4c7ebb1d4af0e3d908a6016`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0048091e(void)

{
  char cVar1;
  int unaff_EBP;
  ushort in_FPUStatusWord;
  float10 in_ST0;
  
  DAT_00632628 = '\0';
  if (DAT_00632500 != 0) {
    DAT_00632628 = 0;
    return;
  }
  _DAT_00632620 = (double)in_ST0;
  cVar1 = *(char *)(unaff_EBP + -0x90);
  if (cVar1 != '\0') {
    if ((cVar1 != -1) && (cVar1 != -2)) {
      if (cVar1 == '\0') {
        DAT_00632628 = 0;
        return;
      }
      *(int *)(unaff_EBP + -0x8e) = (int)cVar1;
      goto LAB_004809f3;
    }
    if (((ulonglong)_DAT_00632620 & 0x7ff0000000000000) == 0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 4;
      in_ST0 = (float10)fscale(in_ST0,(float10)1536.0);
      if (ABS(in_ST0) < (float10)2.2250738585072014e-308) {
        in_ST0 = in_ST0 * (float10)0.0;
      }
      goto LAB_004809f3;
    }
    if ((DAT_00632626 & 0x7ff0) == 0x7ff0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 3;
      in_ST0 = (float10)fscale(in_ST0,(float10)-1536.0);
      if ((float10)1.7976931348623157e+308 < ABS(in_ST0)) {
        in_ST0 = in_ST0 * (float10)INFINITY;
      }
      goto LAB_004809f3;
    }
  }
  if ((*(ushort *)(unaff_EBP + -0xa4) & 0x20) != 0) {
    DAT_00632628 = 0;
    return;
  }
  if ((in_FPUStatusWord & 0x20) == 0) {
    DAT_00632628 = 0;
    return;
  }
  *(undefined4 *)(unaff_EBP + -0x8e) = 8;
LAB_004809f3:
  *(int *)(unaff_EBP + -0x8a) = *(int *)(unaff_EBP + -0x94) + 1;
  if (DAT_00632628 == '\0') {
    *(undefined4 *)(unaff_EBP + -0x86) = *(undefined4 *)(unaff_EBP + 8);
    *(undefined4 *)(unaff_EBP + -0x82) = *(undefined4 *)(unaff_EBP + 0xc);
    if (*(char *)(*(int *)(unaff_EBP + -0x94) + 0xd) != '\x01') {
      *(undefined4 *)(unaff_EBP + -0x7e) = *(undefined4 *)(unaff_EBP + 0x10);
      *(undefined4 *)(unaff_EBP + -0x7a) = *(undefined4 *)(unaff_EBP + 0x14);
    }
  }
  *(double *)(unaff_EBP + -0x76) = (double)in_ST0;
  FUN_00485220((int)*(char *)(*(int *)(unaff_EBP + -0x94) + 0xe),unaff_EBP + -0x8e,unaff_EBP + -0xa4
              );
  return;
}
```

---

---

## FUN_00480925 — 0x480925

- Classification : internal
- Corps : `0x480925–0x480a54`
- État : pseudocode obtenu
- Evidence : `ev_872cdf0ac487938237b112c5803917f83ca59e65138fec49f59ec4a598bc6d92`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x485220` — `FUN_00485220`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00480925(void)

{
  char cVar1;
  int unaff_EBP;
  ushort in_FPUStatusWord;
  float10 in_ST0;
  
  if (DAT_00632500 != 0) {
    return;
  }
  _DAT_00632620 = (double)in_ST0;
  cVar1 = *(char *)(unaff_EBP + -0x90);
  if (cVar1 != '\0') {
    if ((cVar1 != -1) && (cVar1 != -2)) {
      if (cVar1 == '\0') {
        return;
      }
      *(int *)(unaff_EBP + -0x8e) = (int)cVar1;
      goto LAB_004809f3;
    }
    if (((ulonglong)_DAT_00632620 & 0x7ff0000000000000) == 0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 4;
      in_ST0 = (float10)fscale(in_ST0,(float10)1536.0);
      if (ABS(in_ST0) < (float10)2.2250738585072014e-308) {
        in_ST0 = in_ST0 * (float10)0.0;
      }
      goto LAB_004809f3;
    }
    if ((DAT_00632626 & 0x7ff0) == 0x7ff0) {
      *(undefined4 *)(unaff_EBP + -0x8e) = 3;
      in_ST0 = (float10)fscale(in_ST0,(float10)-1536.0);
      if ((float10)1.7976931348623157e+308 < ABS(in_ST0)) {
        in_ST0 = in_ST0 * (float10)INFINITY;
      }
      goto LAB_004809f3;
    }
  }
  if ((*(ushort *)(unaff_EBP + -0xa4) & 0x20) != 0) {
    return;
  }
  if ((in_FPUStatusWord & 0x20) == 0) {
    return;
  }
  *(undefined4 *)(unaff_EBP + -0x8e) = 8;
LAB_004809f3:
  *(int *)(unaff_EBP + -0x8a) = *(int *)(unaff_EBP + -0x94) + 1;
  if (DAT_00632628 == '\0') {
    *(undefined4 *)(unaff_EBP + -0x86) = *(undefined4 *)(unaff_EBP + 8);
    *(undefined4 *)(unaff_EBP + -0x82) = *(undefined4 *)(unaff_EBP + 0xc);
    if (*(char *)(*(int *)(unaff_EBP + -0x94) + 0xd) != '\x01') {
      *(undefined4 *)(unaff_EBP + -0x7e) = *(undefined4 *)(unaff_EBP + 0x10);
      *(undefined4 *)(unaff_EBP + -0x7a) = *(undefined4 *)(unaff_EBP + 0x14);
    }
  }
  *(double *)(unaff_EBP + -0x76) = (double)in_ST0;
  FUN_00485220((int)*(char *)(*(int *)(unaff_EBP + -0x94) + 0xe),unaff_EBP + -0x8e,unaff_EBP + -0xa4
              );
  return;
}
```

---

## __ctrandisp1 — 0x480a55

- Classification : internal
- Corps : `0x480a55–0x480a80`
- État : pseudocode obtenu
- Evidence : `ev_f780d7e9cd6e56148b3ea1a6fdba676b8b4f8fbbf171bf7db569c466102ca370`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f370` — `__trandisp1`
- `0x48091e` — `FUN_0048091e`
- `0x480a81` — `__fload`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __ctrandisp1
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __ctrandisp1(undefined4 param_1,undefined4 param_2)

{
  __fload(param_1,param_2);
  __trandisp1();
  FUN_0048091e();
  return;
}
```

---

## __fload — 0x480a81

- Classification : internal
- Corps : `0x480a81–0x480abc`
- État : pseudocode obtenu
- Evidence : `ev_d7796b0c3977bc52d81535e1acb09551399964e3f72d3fecdb656f17cd60d4c9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __fload
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

float10 __fload(uint param_1,int param_2)

{
  float10 fVar1;
  
  if ((param_2._2_2_ & 0x7ff0) == 0x7ff0) {
    fVar1 = (float10)CONCAT28(param_2._2_2_ | 0x7fff,
                              CONCAT44(param_2 << 0xb | param_1 >> 0x15,param_1));
  }
  else {
    fVar1 = (float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
  }
  return fVar1;
}
```

---

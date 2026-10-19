# 0022_batch_0018 — détails (1/2)

## FUN_00484690 — 0x484690

- Classification : internal
- Corps : `0x484690–0x4846d0`
- État : pseudocode obtenu
- Evidence : `ev_c37c564002da54a66d8ebb8d951cf0b2f84d093c738c00fcec9367462242f1c0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00484690(int param_1)

{
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 0x157;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,0x157);
  }
  return local_8;
}
```

---

---

## FUN_004846e0 — 0x4846e0

- Classification : internal
- Corps : `0x4846e0–0x484720`
- État : pseudocode obtenu
- Evidence : `ev_4c351854153b50b916b3612e07ea94a34a4068978e8ed495285aa430f3cfca5c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_004846e0(int param_1)

{
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 0x117;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,0x117);
  }
  return local_8;
}
```

---

---

## FUN_00484730 — 0x484730

- Classification : internal
- Corps : `0x484730–0x48476b`
- État : pseudocode obtenu
- Evidence : `ev_3516fcf7d737870b015dcb9dad96e3c0654df5a1b08512ab5ba4a820b76eecc5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00484730(int param_1)

{
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 0x20;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,0x20);
  }
  return local_8;
}
```

---

---

## FUN_00484770 — 0x484770

- Classification : internal
- Corps : `0x484770–0x48477f`
- État : pseudocode obtenu
- Evidence : `ev_9734ec74de884cdd34198fdaf70987b6e33d749d76eb7bce7697db6340583ce5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_00484770(uint param_1)

{
  return param_1 < 0x80;
}
```

---

---

## FUN_00484780 — 0x484780

- Classification : internal
- Corps : `0x484780–0x48478a`
- État : pseudocode obtenu
- Evidence : `ev_72b425491fd4f44ee705e138ca9ca1c89dc424ccfc257ef4e3ba99ab86db0bf8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00484780(uint param_1)

{
  return param_1 & 0x7f;
}
```

---

---

## FUN_00484790 — 0x484790

- Classification : internal
- Corps : `0x484790–0x4847ee`
- État : pseudocode obtenu
- Evidence : `ev_f53e04355bdc827993f1303f21fad0ab0d5f555fcc72c5c4191c3517af965d10`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00484790(int param_1)

{
  undefined4 local_c;
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 0x103;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,0x103);
  }
  if ((local_8 == 0) && (param_1 != 0x5f)) {
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}
```

---

---

## FUN_004847f0 — 0x4847f0

- Classification : internal
- Corps : `0x4847f0–0x48484e`
- État : pseudocode obtenu
- Evidence : `ev_11f7bf950be777bb46bff5481e302888ae28c1cdfa1c976f2e1c299faae50aa6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004847f0(int param_1)

{
  undefined4 local_c;
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 0x107;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,0x107);
  }
  if ((local_8 == 0) && (param_1 != 0x5f)) {
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}
```

---

## __allshl — 0x484850

- Classification : internal
- Corps : `0x484850–0x48486e`
- État : pseudocode obtenu
- Evidence : `ev_29ec272f15da0d1347539acf3ff2d8651447f2ca90dc16868bde63dfeb70c4e2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __allshl
   
   Library: Visual Studio */

longlong __allshl(void)

{
  uint in_EAX;
  byte in_CL;
  int in_EDX;
  
  if (0x3f < in_CL) {
    return 0;
  }
  if (in_CL < 0x20) {
    return CONCAT44(in_EDX << (in_CL & 0x1f) | in_EAX >> 0x20 - (in_CL & 0x1f),
                    in_EAX << (in_CL & 0x1f));
  }
  return (ulonglong)(in_EAX << (in_CL & 0x1f)) << 0x20;
}
```

---

---

## FUN_00484870 — 0x484870

- Classification : internal
- Corps : `0x484870–0x484a4f`
- État : pseudocode obtenu
- Evidence : `ev_5327cd9a778d2ab6f4f8d404b0bf940b2bcc60fa6b61abf7f3d30daa0893c291`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x48489c with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x474190` — `FUN_00474190`
- `0x47a120` — `FUN_0047a120`
- `0x483560` — `FUN_00483560`

### Chaînes référencées

- `0x4951dc` — "str != NULL"
- `0x496274` — "_filbuf.c"

### Pseudocode Ghidra

```c
uint FUN_00484870(int *param_1)

{
  code *pcVar1;
  int iVar2;
  uint uVar3;
  undefined *local_c;
  
  if ((param_1 == (int *)0x0) &&
     (iVar2 = FUN_0047a120(2,"_filbuf.c",0x69,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if (((param_1[3] & 0x83U) == 0) || ((param_1[3] & 0x40U) != 0)) {
    uVar3 = 0xffffffff;
  }
  else if ((param_1[3] & 2U) == 0) {
    param_1[3] = param_1[3] | 1;
    if ((param_1[3] & 0x10cU) == 0) {
      FUN_00483560(param_1);
    }
    else {
      *param_1 = param_1[2];
    }
    iVar2 = FUN_00474190(param_1[4],param_1[2],param_1[6]);
    param_1[1] = iVar2;
    if ((param_1[1] == 0) || (param_1[1] == -1)) {
      param_1[3] = param_1[3] | (-(uint)(param_1[1] != 0) & 0x10) + 0x10;
      param_1[1] = 0;
      uVar3 = 0xffffffff;
    }
    else {
      if ((param_1[3] & 0x82U) == 0) {
        if (param_1[4] == -1) {
          local_c = &DAT_004a65b0;
        }
        else {
          local_c = (undefined *)((&DAT_00633d20)[param_1[4] >> 5] + (param_1[4] & 0x1fU) * 8);
        }
        if (((int)(char)local_c[4] & 0x82U) == 0x82) {
          param_1[3] = param_1[3] | 0x2000;
        }
      }
      if (((param_1[6] == 0x200) && ((param_1[3] & 8U) != 0)) && ((param_1[3] & 0x400U) == 0)) {
        param_1[6] = 0x1000;
      }
      param_1[1] = param_1[1] + -1;
      uVar3 = (uint)*(byte *)*param_1;
      *param_1 = *param_1 + 1;
    }
  }
  else {
    param_1[3] = param_1[3] | 0x20;
    uVar3 = 0xffffffff;
  }
  return uVar3;
}
```

---

---

## FUN_00484a50 — 0x484a50

- Classification : internal
- Corps : `0x484a50–0x484b8d`
- État : pseudocode obtenu
- Evidence : `ev_8073903cd4197bb5d8974c9686688f031b73705e97559c96e70083ac935636a6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x484a7a with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x47a120` — `FUN_0047a120`
- `0x483560` — `FUN_00483560`

### Chaînes référencées

- `0x4951dc` — "str != NULL"
- `0x496280` — "ungetc.c"

### Pseudocode Ghidra

```c
uint FUN_00484a50(uint param_1,int *param_2)

{
  code *pcVar1;
  int iVar2;
  uint uVar3;
  
  if ((param_2 == (int *)0x0) &&
     (iVar2 = FUN_0047a120(2,"ungetc.c",0x60,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_1 == 0xffffffff) ||
     (((param_2[3] & 1U) == 0 && (((param_2[3] & 0x80U) == 0 || ((param_2[3] & 2U) != 0)))))) {
    param_1 = 0xffffffff;
  }
  else {
    if (param_2[2] == 0) {
      FUN_00483560(param_2);
    }
    if (*param_2 == param_2[2]) {
      if (param_2[1] != 0) {
        return 0xffffffff;
      }
      *param_2 = *param_2 + 1;
    }
    if ((param_2[3] & 0x40U) == 0) {
      *param_2 = *param_2 + -1;
      *(char *)*param_2 = (char)param_1;
    }
    else {
      *param_2 = *param_2 + -1;
      if (*(char *)*param_2 != (char)param_1) {
        *param_2 = *param_2 + 1;
        return 0xffffffff;
      }
    }
    param_2[1] = param_2[1] + 1;
    param_2[3] = param_2[3] & 0xffffffef;
    param_2[3] = param_2[3] | 1;
    param_1 = param_1 & 0xff;
  }
  return param_1;
}
```

---

---

## FUN_00484b90 — 0x484b90

- Classification : internal
- Corps : `0x484b90–0x484bf1`
- État : pseudocode obtenu
- Evidence : `ev_136ebe8ba75bc8b5d3d02e4d9327f41c92e969b8ad1d42bd42ce44502d06a786`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47c980` — `FUN_0047c980`
- `0x484ca0` — `_ValidateExecute`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00484b90(int *param_1)

{
  int iVar1;
  
  if (((*(int *)*param_1 == -0x1f928c9d) && (*(int *)(*param_1 + 0x10) == 3)) &&
     (*(int *)(*param_1 + 0x14) == 0x19930520)) {
    FUN_0047c980();
    iVar1 = 1;
  }
  else {
    if ((DAT_006328bc != (_func_int *)0x0) && (iVar1 = _ValidateExecute(DAT_006328bc), iVar1 != 0))
    {
      iVar1 = (*DAT_006328bc)(param_1);
      return iVar1;
    }
    iVar1 = 0;
  }
  return iVar1;
}
```

---

---

## FUN_00484c00 — 0x484c00

- Classification : internal
- Corps : `0x484c00–0x484c14`
- État : pseudocode obtenu
- Evidence : `ev_dbdcb579c846cfda74f943d688670ddb8f5ef11258364f9db39398dc75f033fc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x16` — `KERNEL32.DLL::SetUnhandledExceptionFilter`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00484c00(void)

{
  DAT_006328bc = SetUnhandledExceptionFilter(FUN_00484b90);
  return;
}
```

---

---

## FUN_00484c20 — 0x484c20

- Classification : internal
- Corps : `0x484c20–0x484c30`
- État : pseudocode obtenu
- Evidence : `ev_27a053532f0a25e176ecaa2800dfe58720bc204d605c934578ca1903e5507c96`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x16` — `KERNEL32.DLL::SetUnhandledExceptionFilter`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00484c20(void)

{
  SetUnhandledExceptionFilter(DAT_006328bc);
  return;
}
```

---

---

## FUN_00484c40 — 0x484c40

- Classification : internal
- Corps : `0x484c40–0x484c6a`
- État : pseudocode obtenu
- Evidence : `ev_f2d3d44c6ca6f0f24fb614868ab2ff8e4f43068c07451e099cb2000a1c5ef241`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xe` — `KERNEL32.DLL::IsBadReadPtr`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_00484c40(void *param_1,UINT_PTR param_2)

{
  BOOL BVar1;
  
  BVar1 = IsBadReadPtr(param_1,param_2);
  return BVar1 == 0;
}
```

---

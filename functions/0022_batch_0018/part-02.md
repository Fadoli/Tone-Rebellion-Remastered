# 0022_batch_0018 — détails (2/5)

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

## FUN_00484c70 — 0x484c70

- Classification : internal
- Corps : `0x484c70–0x484c9a`
- État : pseudocode obtenu
- Evidence : `ev_5b706d160e0cd00d5d2b0e964bedab2abe5c2c19f5c73693ac793268f5c37149`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x3c` — `KERNEL32.DLL::IsBadWritePtr`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_00484c70(LPVOID param_1,UINT_PTR param_2)

{
  BOOL BVar1;
  
  BVar1 = IsBadWritePtr(param_1,param_2);
  return BVar1 == 0;
}
```

---

## _ValidateExecute — 0x484ca0

- Classification : internal
- Corps : `0x484ca0–0x484cc6`
- État : pseudocode obtenu
- Evidence : `ev_34f9105bb3919ba7648b6ce4b5231ac280cbee8e36ca4587756fe1186c8cee01`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x15` — `KERNEL32.DLL::IsBadCodePtr`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    int __cdecl _ValidateExecute(int (__stdcall*)(void))
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

int __cdecl _ValidateExecute(_func_int *param_1)

{
  BOOL BVar1;
  uint local_8;
  
  BVar1 = IsBadCodePtr((FARPROC)param_1);
  local_8 = (uint)(BVar1 == 0);
  return local_8;
}
```

---

## FUN_00484cd0 — 0x484cd0

- Classification : internal
- Corps : `0x484cd0–0x484ced`
- État : pseudocode obtenu
- Evidence : `ev_615575ade5a730df3e395dd65b8220b5f933f9bab5699ab8931a2279c075c858`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x484ce9 to 0x476ec0 __exit (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `0x476ec0` — `__exit`
- `0x481f20` — `FUN_00481f20`
- `0x484020` — `FUN_00484020`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00484cd0(void)

{
  FUN_00481f20(10);
  FUN_00484020(0x16);
                    /* WARNING: Subroutine does not return */
  __exit(3);
}
```

---

## FUN_00484d00 — 0x484d00

- Classification : internal
- Corps : `0x484d00–0x484dfb`
- État : pseudocode obtenu
- Evidence : `ev_df15d0d2ce58744570321403da4c71576074a714655bf14837fcb3eb025d5e16`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00484d00(uint param_1,int param_2)

{
  char cVar1;
  int iVar2;
  
  if ((param_1 < DAT_00633e5c) &&
     (iVar2 = (int)param_1 >> 5,
     (*(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    cVar1 = *(char *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8);
    if (param_2 == 0x8000) {
      *(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) =
           *(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) & 0x7f;
    }
    else {
      if (param_2 != 0x4000) {
        _DAT_0063251c = 0x16;
        return -1;
      }
      *(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) =
           *(byte *)((&DAT_00633d20)[iVar2] + 4 + (param_1 & 0x1f) * 8) | 0x80;
    }
    iVar2 = (-(uint)(((int)cVar1 & 0x80U) != 0) & 0xffffc000) + 0x8000;
  }
  else {
    _DAT_0063251c = 9;
    iVar2 = -1;
  }
  return iVar2;
}
```

---

## FUN_00484e00 — 0x484e00

- Classification : internal
- Corps : `0x484e00–0x484ead`
- État : pseudocode obtenu
- Evidence : `ev_b8cefb4b644a7aea521aaa7452c8e08f957f465d56605f21662c506564b07a54`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `EXTERNAL:0x14` — `KERNEL32.DLL::FlushFileBuffers`
- `0x47ce00` — `FUN_0047ce00`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00484e00(uint param_1)

{
  HANDLE hFile;
  BOOL BVar1;
  DWORD local_8;
  
  if (((param_1 < DAT_00633e5c) &&
      ((*(byte *)((&DAT_00633d20)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) &&
     ((*(byte *)((&DAT_00633d20)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    hFile = (HANDLE)FUN_0047ce00(param_1);
    BVar1 = FlushFileBuffers(hFile);
    if (BVar1 == 0) {
      local_8 = GetLastError();
    }
    else {
      local_8 = 0;
    }
    if (local_8 == 0) {
      return 0;
    }
    DAT_00632520 = local_8;
  }
  _DAT_0063251c = 9;
  return 0xffffffff;
}
```

---

## FUN_00484eb0 — 0x484eb0

- Classification : internal
- Corps : `0x484eb0–0x4850bf`
- État : pseudocode obtenu
- Evidence : `ev_0a26d786947151327736b57fd6b8690f002aaddf32ab933e6455ca5f820dce45`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x7` — `KERNEL32.DLL::WideCharToMultiByte`
- `EXTERNAL:0x12` — `KERNEL32.DLL::GetStringTypeW`
- `EXTERNAL:0x13` — `KERNEL32.DLL::GetStringTypeA`
- `0x474d40` — `FUN_00474d40`
- `0x475140` — `__calloc_dbg`
- `0x475780` — `FUN_00475780`
- `0x483210` — `FUN_00483210`

### Chaînes référencées

- `0x49628c` — "aw_str.c"
- `0x49628c` — "aw_str.c"

### Pseudocode Ghidra

```c
void FUN_00484eb0(DWORD param_1,LPCWSTR param_2,int param_3,LPWORD param_4,UINT param_5,LCID param_6
                 )

{
  BOOL BVar1;
  int cbMultiByte;
  LPCSTR lpMultiByteStr;
  int iVar2;
  LPWORD local_10;
  WORD local_8 [2];
  
  if (DAT_006328c4 == 0) {
    BVar1 = GetStringTypeW(1,L"",1,local_8);
    if (BVar1 == 0) {
      BVar1 = GetStringTypeA(0,1,"",1,local_8);
      if (BVar1 == 0) {
        return;
      }
      DAT_006328c4 = 2;
    }
    else {
      DAT_006328c4 = 1;
    }
  }
  if (DAT_006328c4 == 1) {
    GetStringTypeW(param_1,param_2,param_3,param_4);
  }
  else if (DAT_006328c4 == 2) {
    local_10 = (LPWORD)0x0;
    if (param_5 == 0) {
      param_5 = DAT_006325f8;
    }
    cbMultiByte = WideCharToMultiByte(param_5,0x220,param_2,param_3,(LPSTR)0x0,0,(LPCSTR)0x0,
                                      (LPBOOL)0x0);
    if ((cbMultiByte != 0) &&
       (lpMultiByteStr = (LPCSTR)__calloc_dbg(1,cbMultiByte,2,"aw_str.c",0x76),
       lpMultiByteStr != (LPCSTR)0x0)) {
      iVar2 = WideCharToMultiByte(param_5,0x220,param_2,param_3,lpMultiByteStr,cbMultiByte,
                                  (LPCSTR)0x0,(LPBOOL)0x0);
      if ((iVar2 != 0) &&
         (local_10 = (LPWORD)FUN_00474d40(cbMultiByte * 2 + 2,2,"aw_str.c",0x80),
         local_10 != (LPWORD)0x0)) {
        if (param_6 == 0) {
          param_6 = DAT_006325e8;
        }
        local_10[param_3] = 0xffff;
        local_10[param_3 + -1] = 0xffff;
        GetStringTypeA(param_6,param_1,lpMultiByteStr,cbMultiByte,local_10);
        if ((local_10[param_3 + -1] != 0xffff) && (local_10[param_3] == 0xffff)) {
          FUN_00483210(param_4,local_10,param_3 << 1);
        }
      }
      FUN_00475780(lpMultiByteStr,2);
      FUN_00475780(local_10,2);
    }
  }
  return;
}
```

---

## FUN_004850c0 — 0x4850c0

- Classification : internal
- Corps : `0x4850c0–0x48521b`
- État : pseudocode obtenu
- Evidence : `ev_b95f713fa79721279575534538b8a46f64596a48d524dd2dc6105d207f0170c7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x5` — `KERNEL32.DLL::MultiByteToWideChar`
- `EXTERNAL:0x12` — `KERNEL32.DLL::GetStringTypeW`
- `EXTERNAL:0x13` — `KERNEL32.DLL::GetStringTypeA`
- `0x475140` — `__calloc_dbg`
- `0x475780` — `FUN_00475780`

### Chaînes référencées

- `0x49628c` — "aw_str.c"

### Pseudocode Ghidra

```c
void FUN_004850c0(DWORD param_1,LPCSTR param_2,int param_3,LPWORD param_4,UINT param_5,LCID param_6)

{
  BOOL BVar1;
  int iVar2;
  LPCWSTR local_14;
  WORD local_8 [2];
  
  if (DAT_006328c8 == 0) {
    BVar1 = GetStringTypeA(0,1,"",1,local_8);
    if (BVar1 == 0) {
      BVar1 = GetStringTypeW(1,L"",1,local_8);
      if (BVar1 == 0) {
        return;
      }
      DAT_006328c8 = 1;
    }
    else {
      DAT_006328c8 = 2;
    }
  }
  if (DAT_006328c8 == 2) {
    if (param_6 == 0) {
      param_6 = DAT_006325e8;
    }
    GetStringTypeA(param_6,param_1,param_2,param_3,param_4);
  }
  else if (DAT_006328c8 == 1) {
    local_14 = (LPCWSTR)0x0;
    if (param_5 == 0) {
      param_5 = DAT_006325f8;
    }
    iVar2 = MultiByteToWideChar(param_5,9,param_2,param_3,(LPWSTR)0x0,0);
    if (((iVar2 != 0) &&
        (local_14 = (LPCWSTR)__calloc_dbg(2,iVar2,2,"aw_str.c",0x104), local_14 != (LPCWSTR)0x0)) &&
       (iVar2 = MultiByteToWideChar(param_5,1,param_2,param_3,local_14,iVar2), iVar2 != 0)) {
      GetStringTypeW(param_1,local_14,iVar2,param_4);
    }
    FUN_00475780(local_14,2);
  }
  return;
}
```

---

## FUN_00485220 — 0x485220

- Classification : internal
- Corps : `0x485220–0x48537b`
- État : pseudocode obtenu
- Evidence : `ev_200bb88bc3d99a8c2327f346fb223df56609ec951e06998cf2679d4d82ac8d89`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x488b70` — `FUN_00488b70`
- `0x489040` — `FUN_00489040`
- `0x489460` — `__set_errno`
- `0x489560` — `__matherr`
- `0x4895b0` — `FUN_004895b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void FUN_00485220(int param_1,_exception *param_2,ushort *param_3)

{
  int iVar1;
  undefined1 local_6c [40];
  undefined4 local_44;
  undefined4 local_40;
  uint local_34;
  uint local_14;
  uint *local_10;
  int local_c;
  int local_8;
  
  local_14 = (uint)*param_3;
  local_10 = &local_14;
  switch(param_2->type) {
  case 1:
  case 5:
    local_8 = 8;
    break;
  case 2:
    local_8 = 4;
    break;
  case 3:
    local_8 = 0x11;
    break;
  case 4:
    local_8 = 0x12;
    break;
  case 7:
    param_2->type = 1;
  default:
    local_8 = 0;
    break;
  case 8:
    local_8 = 0x10;
  }
  if ((local_8 != 0) && (iVar1 = FUN_00489040(local_8,&param_2->retval,local_14), iVar1 == 0)) {
    if ((param_1 == 0x10) || ((param_1 == 0x16 || (param_1 == 0x1d)))) {
      local_34 = local_34 & 0xffffffe1 | 3;
      local_44 = *(undefined4 *)&param_2->arg2;
      local_40 = *(undefined4 *)((int)&param_2->arg2 + 4);
    }
    else {
      local_34 = local_34 & 0xfffffffe;
    }
    FUN_00488b70(local_6c,local_10,local_8,param_1,&param_2->arg1,&param_2->retval);
  }
  FUN_004895b0(*local_10,0xffff);
  local_c = 0;
  if ((param_2->type != 8) && (DAT_004a90f8 == 0)) {
    local_c = __matherr(param_2);
  }
  if (local_c == 0) {
    __set_errno(param_2->type);
  }
  return;
}
```

---


# 0012_batch_0008 — détails (1/3)

## FUN_0042d811 — 0x42d811

- Classification : internal
- Corps : `0x42d811–0x42d87b`
- État : pseudocode obtenu
- Evidence : `ev_90a200d6d3f031a17062cc565aebe9525bc877dd4dc65182bfd7fd5ab6d23d99`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_0042d811(void)

{
  int local_c;
  int local_8;
  
  if (DAT_005c3108 != DAT_005c30a4 + 1) {
    DAT_005c3108 = DAT_005c30a4 + 1;
    local_8 = 0;
    for (local_c = 0; local_c < 0x1e0; local_c = local_c + 1) {
      *(int *)(&DAT_005c28c8 + local_c * 4) = local_8;
      local_8 = local_8 + DAT_005c3108;
    }
  }
  return &DAT_005c28c8;
}
```

---

---

## FUN_0042d87c — 0x42d87c

- Classification : internal
- Corps : `0x42d87c–0x42d9cc`
- État : pseudocode obtenu
- Evidence : `ev_b0ca2ad0e393bc2c24ce878b4900a1f74dbfe3628d4ebb29f608adca3e09bcc3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49e554` — "C:\\float\\src\\graphsys.cpp"
- `0x49e570` — "GSNumInvalidRects >= 0 && GSNumInvalidRects < MAX_INVALID_RECTS"
- `0x49e5b0` — "C:\\float\\src\\graphsys.cpp"

### Pseudocode Ghidra

```c
void FUN_0042d87c(int *param_1,byte param_2)

{
  int iVar1;
  int *piVar2;
  int local_1c [6];
  
  if ((param_2 & DAT_005c3098) == 0) {
    if (param_1 == (int *)0x0) {
      thunk_FUN_00414b64(s_C__float_src_graphsys_cpp_0049e554,0x4de,&DAT_0049e54c);
    }
    if ((DAT_005c3118 < 0) || (0x3f < DAT_005c3118)) {
      thunk_FUN_00414b64(s_C__float_src_graphsys_cpp_0049e5b0,0x4df,
                         s_GSNumInvalidRects_>__0____GSNumI_0049e570);
    }
    piVar2 = local_1c;
    for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar2 = *param_1;
      param_1 = param_1 + 1;
      piVar2 = piVar2 + 1;
    }
    if ((((local_1c[1] < 0x280) && (-1 < local_1c[3])) && (local_1c[2] < 0x1e0)) &&
       (-1 < local_1c[4])) {
      if (local_1c[1] < 0) {
        local_1c[1] = 0;
      }
      if (0x27f < local_1c[3]) {
        local_1c[3] = 0x27f;
      }
      if (local_1c[2] < 0) {
        local_1c[2] = 0;
      }
      if (0x1df < local_1c[4]) {
        local_1c[4] = 0x1df;
      }
      iVar1 = DAT_005c3118 * 0x10;
      *(int *)(&DAT_005c1ca0 + iVar1) = local_1c[1];
      *(int *)(&DAT_005c1ca4 + iVar1) = local_1c[2];
      *(int *)(&DAT_005c1ca8 + iVar1) = local_1c[3] + 1;
      *(int *)(&DAT_005c1cac + iVar1) = local_1c[4] + 1;
      (&DAT_005c2888)[DAT_005c3118] = (&DAT_005c2888)[DAT_005c3118] | param_2;
      DAT_005c3118 = DAT_005c3118 + 1;
    }
  }
  return;
}
```

---

---

## FUN_0042d9cd — 0x42d9cd

- Classification : internal
- Corps : `0x42d9cd–0x42d9de`
- État : pseudocode obtenu
- Evidence : `ev_a2f408b3753c32bbd61a68fc331dd3d7a837b8e81493578f26ffc107c90f634c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042d9cd(byte param_1)

{
  DAT_005c3098 = DAT_005c3098 | param_1;
  return;
}
```

---

---

## FUN_0042d9df — 0x42d9df

- Classification : internal
- Corps : `0x42d9df–0x42d9ed`
- État : pseudocode obtenu
- Evidence : `ev_7af489f645dfea953292f104983118d5a4a9fc69e9ebad340401ce34d89d5a91`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042d9df(void)

{
  DAT_005c30d4 = 1;
  return;
}
```

---

---

## FUN_0042d9ee — 0x42d9ee

- Classification : internal
- Corps : `0x42d9ee–0x42d9fc`
- État : pseudocode obtenu
- Evidence : `ev_f3043019c243dacd84d836920d791d75f70834263ad3b70babcd1681c9fa07e4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042d9ee(void)

{
  DAT_005c30d4 = 0;
  return;
}
```

---

---

## FUN_0042d9fd — 0x42d9fd

- Classification : internal
- Corps : `0x42d9fd–0x42da68`
- État : pseudocode obtenu
- Evidence : `ev_fe7c587d7c480323c9aba1e4d7c4938754621886e2cbba7528b2dec264bcf199`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472c6c` — `__ftol`
- `0x477599` — `FUN_00477599`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0042d9fd(int param_1)

{
  float10 fVar1;
  undefined4 local_8;
  
  fVar1 = (float10)FUN_00477599((double)param_1 / 63.0,(double)(1.0 / _DAT_0049e13c));
  local_8 = __ftol((double)(fVar1 * (float10)255.0));
  if (local_8 < 0) {
    local_8 = 0;
  }
  if (0xff < local_8) {
    local_8 = 0xff;
  }
  return local_8;
}
```

---

---

## FUN_0042da69 — 0x42da69

- Classification : internal
- Corps : `0x42da69–0x42dc4d`
- État : pseudocode obtenu
- Evidence : `ev_0276c86990e0a6ade64e78b16571697e9ab600f09c53b04522c26050cf550258`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x6d` — `GDI32.DLL::SetDIBColorTable`
- `0x40144c` — `thunk_FUN_0042cc24`
- `0x40162c` — `thunk_FUN_0042d9fd`
- `0x40182f` — `thunk_FUN_0042bfa9`
- `0x4022de` — `thunk_FUN_0042d9cd`
- `0x402491` — `thunk_FUN_0042dd0f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0042da69(UINT param_1,UINT param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  RGBQUAD local_414 [256];
  int local_14;
  UINT local_10;
  int local_c;
  undefined1 *local_8;
  
  if ((((DAT_005c30cc != 0) && (-1 < (int)param_1)) && (0 < (int)param_2)) &&
     ((int)(param_1 + param_2) < 0x101)) {
    if (param_3 != (undefined1 *)0x0) {
      local_8 = param_3;
      for (local_c = 0; local_c < (int)param_2; local_c = local_c + 1) {
        uVar1 = thunk_FUN_0042d9fd(*local_8);
        (&DAT_005c18a0)[local_c * 4] = uVar1;
        uVar1 = thunk_FUN_0042d9fd(local_8[1]);
        (&DAT_005c18a1)[local_c * 4] = uVar1;
        uVar1 = thunk_FUN_0042d9fd(local_8[2]);
        (&DAT_005c18a2)[local_c * 4] = uVar1;
        (&DAT_005c18a3)[local_c * 4] = 0;
        local_8 = local_8 + 3;
      }
    }
    if (param_1 + param_2 == 0x100) {
      (&DAT_005c189e)[param_2 * 4] = 0xff;
      (&DAT_005c189d)[param_2 * 4] = 0xff;
      (&DAT_005c189c)[param_2 * 4] = 0xff;
    }
    if (DAT_0049e138 == 4) {
      for (local_14 = 0; local_14 < (int)param_2; local_14 = local_14 + 1) {
        local_414[local_14].rgbRed = (&DAT_005c18a0)[local_14 * 4];
        local_414[local_14].rgbGreen = (&DAT_005c18a1)[local_14 * 4];
        local_414[local_14].rgbBlue = (&DAT_005c18a2)[local_14 * 4];
        local_414[local_14].rgbReserved = '\0';
      }
      local_10 = SetDIBColorTable(DAT_005c3110,param_1,param_2,local_414);
    }
    else {
      (**(code **)(*DAT_005c30f8 + 0x18))(DAT_005c30f8,0,param_1,param_2,&DAT_005c18a0);
    }
    thunk_FUN_0042bfa9();
    _DAT_005c2878 = thunk_FUN_0042dd0f(6);
    _DAT_005c2878 = _DAT_005c2878 & 0xff;
    DAT_005c30c0 = _DAT_005c2878;
    if (DAT_0049e138 == 4) {
      thunk_FUN_0042d9cd(3);
      thunk_FUN_0042cc24();
    }
  }
  return;
}
```

---

---

## FUN_0042dc4e — 0x42dc4e

- Classification : internal
- Corps : `0x42dc4e–0x42dd0e`
- État : pseudocode obtenu
- Evidence : `ev_08f530104cafeaf1efbb126740bb862941943f30992168faa3d0f5b7fa5f48df`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042dc4e(int param_1,int param_2,undefined1 *param_3)

{
  int local_c;
  undefined1 *local_8;
  
  if ((((DAT_005c30cc != 0) && (param_3 != (undefined1 *)0x0)) && (-1 < param_1)) &&
     ((0 < param_2 && (param_1 + param_2 < 0x101)))) {
    local_8 = param_3;
    for (local_c = 0; local_c < param_2; local_c = local_c + 1) {
      *local_8 = (char)(((uint)(byte)(&DAT_005c18a0)[local_c * 4] * 0x3f) / 0xff);
      local_8[1] = (char)((ulonglong)((uint)(byte)(&DAT_005c18a1)[local_c * 4] * 0x3f) / 0xff);
      local_8[2] = (char)((ulonglong)((uint)(byte)(&DAT_005c18a2)[local_c * 4] * 0x3f) / 0xff);
      local_8 = local_8 + 3;
    }
  }
  return;
}
```

---

---

## FUN_0042dd0f — 0x42dd0f

- Classification : internal
- Corps : `0x42dd0f–0x42dd3c`
- État : pseudocode obtenu
- Evidence : `ev_37f12ca8c7f85d7a880e861bdcf39c41e4b1840adbc82d312ecf84457b9852e1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined1 FUN_0042dd0f(byte param_1)

{
  undefined1 uVar1;
  
  uVar1 = 0xff;
  if (param_1 < 7) {
    uVar1 = (&DAT_0049e140)[param_1];
  }
  return uVar1;
}
```

---

---

## FUN_0042dd3d — 0x42dd3d

- Classification : internal
- Corps : `0x42dd3d–0x42dd46`
- État : pseudocode obtenu
- Evidence : `ev_aa3e39e3f5030e22479b4c52848d23762c517ca8c740bb134fb6b9ad38711a2c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042dd3d(void)

{
  return DAT_005c30e0;
}
```

---

---

## FUN_0042dd47 — 0x42dd47

- Classification : internal
- Corps : `0x42dd47–0x42dd94`
- État : pseudocode obtenu
- Evidence : `ev_f390428e4e2b22a6ce9a9f425844123e7a120340e823e19cc9c45619ebb90e9a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x6a` — `USER32.DLL::SetCursor`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042dd47(int param_1)

{
  DAT_005c30dc = DAT_004c2b10;
  if (((-1 < param_1) && (param_1 < 0x11)) && ((&DAT_004c2b10)[param_1] != (HCURSOR)0x0)) {
    DAT_005c30e0 = param_1;
    DAT_005c30dc = (&DAT_004c2b10)[param_1];
  }
  SetCursor(DAT_005c30dc);
  return;
}
```

---

---

## FUN_0042dd95 — 0x42dd95

- Classification : internal
- Corps : `0x42dd95–0x42de02`
- État : pseudocode obtenu
- Evidence : `ev_92212c7d6ef01e332d4a3c3eb4eece0ed03d678c6ae550cababefb52c7c97778`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401294` — `thunk_FUN_004289ec`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042dd95(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = (uint)(DAT_005c30a0 != 0);
  if (local_8 == 0) {
    thunk_FUN_0042d28f();
  }
  local_1c = &DAT_005c30a0;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0x27f;
  local_c = 0x1df;
  thunk_FUN_004289ec(&local_1c,param_1,param_2,param_3,10);
  if (local_8 == 0) {
    thunk_FUN_0042d38a();
  }
  return;
}
```

---

---

## FUN_0042de03 — 0x42de03

- Classification : internal
- Corps : `0x42de03–0x42de0c`
- État : pseudocode obtenu
- Evidence : `ev_7e06adb78033f09f466423ead091cf7d1a101335eb38ccc2614875ae781e8936`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0042de03(void)

{
  return &DAT_005c2870;
}
```

---

---

## FUN_0042de0d — 0x42de0d

- Classification : internal
- Corps : `0x42de0d–0x42de16`
- État : pseudocode obtenu
- Evidence : `ev_0eb93bbc7dfc413b79a8628d1502cc675fbacf2a3f32fc7cfa9a6f1eb175c54d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0042de0d(void)

{
  return &DAT_005c30b8;
}
```

---

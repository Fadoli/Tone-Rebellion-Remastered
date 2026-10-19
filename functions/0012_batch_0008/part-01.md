# 0012_batch_0008 — détails (1/8)

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

## FUN_0042de17 — 0x42de17

- Classification : internal
- Corps : `0x42de17–0x42de7a`
- État : pseudocode obtenu
- Evidence : `ev_7d9b0252749415e1d97d244fd8c6e7b034606954b0b3c18675f3113e52abdb85`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4017df` — `thunk_FUN_0041be72`
- `0x401c35` — `thunk_FUN_0042c07d`
- `0x4737e0` — `_strncpy`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042de17(char *param_1,short param_2)

{
  int iVar1;
  
  if (DAT_005c3120 == 0x14) {
    thunk_FUN_0042c07d(0);
  }
  _strncpy(&DAT_005c20a0 + DAT_005c3120 * 100,param_1,100);
  iVar1 = thunk_FUN_0041be72();
  *(int *)(&DAT_005c3048 + DAT_005c3120 * 4) = iVar1 + param_2 * DAT_004c2b54;
  DAT_005c3120 = DAT_005c3120 + 1;
  return;
}
```

---

## FUN_0042de7b — 0x42de7b

- Classification : internal
- Corps : `0x42de7b–0x42de89`
- État : pseudocode obtenu
- Evidence : `ev_5c26fee23a03585f828a330299a51fc0d6899839f73b6ead8b63ce84273bc770`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042de7b(void)

{
  DAT_005c3120 = 0;
  return;
}
```

---

## FUN_0042e690 — 0x42e690

- Classification : internal
- Corps : `0x42e690–0x42e772`
- État : pseudocode obtenu
- Evidence : `ev_5962d75a6e9f4a3c2a1514b8406770c953989b9e276934a899cf3ab5c69a970d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- `0x494250` — "0123456789ABCDEF"
- `0x494250` — "0123456789ABCDEF"

### Pseudocode Ghidra

```c
undefined4 FUN_0042e690(int param_1,wchar_t *param_2)

{
  uint local_c;
  
  *param_2 = 0x7b;
  param_2 = param_2 + 1;
  for (local_c = 0; local_c < 0x14; local_c = local_c + 1) {
    if ((&DAT_00494238)[local_c] == '-') {
      *param_2 = L'-';
      param_2 = param_2 + 1;
    }
    else {
      *param_2 = L"0123456789ABCDEF"
                 [(int)(*(byte *)(param_1 + (uint)(byte)(&DAT_00494238)[local_c]) & 0xf0) >> 4];
      param_2[1] = L"0123456789ABCDEF"
                   [*(byte *)(param_1 + (uint)(byte)(&DAT_00494238)[local_c]) & 0xf];
      param_2 = param_2 + 2;
    }
  }
  *param_2 = L'}';
  param_2[1] = L'\0';
  return 0x26;
}
```

---

## FID_conflict:_AfxIsEqualGUID — 0x42e773

- Classification : internal
- Corps : `0x42e773–0x42e7c3`
- État : pseudocode obtenu
- Evidence : `ev_7cf97b14edd8e4be78ad8871239b1091e5367431f013a1db0ec0ac87d62aa140`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Multiple Matches With Different Base Names
    int __cdecl ATL::InlineIsEqualGUID(struct _GUID const &,struct _GUID const &)
    int __cdecl _AfxIsEqualGUID(struct _GUID const &,struct _GUID const &)
    _InlineIsEqualGUID
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual
   Studio 2010 Debug */

undefined4 FID_conflict__AfxIsEqualGUID(int *param_1,int *param_2)

{
  undefined4 local_8;
  
  if ((((*param_1 == *param_2) && (param_1[1] == param_2[1])) && (param_1[2] == param_2[2])) &&
     (param_1[3] == param_2[3])) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  return local_8;
}
```

---

## FUN_0042e7c4 — 0x42e7c4

- Classification : internal
- Corps : `0x42e7c4–0x42e826`
- État : pseudocode obtenu
- Evidence : `ev_6ca21e112d54a1f0ec895ef85e8cf3834024c05386f626ed8e1f038624af07fd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0042e7c4(char *param_1)

{
  char cVar1;
  int iVar2;
  
  cVar1 = *param_1;
  if ((cVar1 < '0') || ('9' < cVar1)) {
    if ((cVar1 < 'a') || ('f' < cVar1)) {
      if ((cVar1 < 'A') || ('F' < cVar1)) {
        iVar2 = 0;
      }
      else {
        iVar2 = cVar1 + -0x37;
      }
    }
    else {
      iVar2 = cVar1 + -0x57;
    }
  }
  else {
    iVar2 = cVar1 + -0x30;
  }
  return iVar2;
}
```

---

## FUN_0042e827 — 0x42e827

- Classification : internal
- Corps : `0x42e827–0x42e8e6`
- État : pseudocode obtenu
- Evidence : `ev_10e93ebbd04c7c0f07d09bda544cba00346c5c6498c4bd52d55e15850be050e6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401eb5` — `thunk_FUN_0042e7c4`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042e827(int param_1,int *param_2,int param_3,int param_4)

{
  char cVar1;
  char cVar2;
  int local_8;
  
  for (local_8 = 0; local_8 < param_3; local_8 = local_8 + 1) {
    if (*(char *)*param_2 == '-') {
      *param_2 = *param_2 + 1;
    }
    if (param_4 == 1) {
      cVar1 = thunk_FUN_0042e7c4(*param_2);
      cVar2 = thunk_FUN_0042e7c4(*param_2 + 1);
      *(char *)((param_1 + param_3) - (local_8 + 1)) = cVar1 * '\x10' + cVar2;
    }
    else {
      cVar1 = thunk_FUN_0042e7c4(*param_2);
      cVar2 = thunk_FUN_0042e7c4(*param_2 + 1);
      *(char *)(param_1 + local_8) = cVar1 * '\x10' + cVar2;
    }
    *param_2 = *param_2 + 2;
  }
  return;
}
```

---

## FUN_0042e8e7 — 0x42e8e7

- Classification : internal
- Corps : `0x42e8e7–0x42e9e8`
- État : pseudocode obtenu
- Evidence : `ev_e51c873857901aad660a340adef8ef39161ec42b4829e61a1f3e315d0837e299`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011e5` — `thunk_FUN_0042e9e9`
- `0x402365` — `thunk_FUN_0042e827`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042e8e7(undefined4 param_1,void *param_2)

{
  undefined4 uVar1;
  char *local_48;
  char local_44 [64];
  
  local_48 = local_44;
  thunk_FUN_0042e9e9(local_48,param_1,0x40);
  if (*local_48 == '{') {
    local_48 = local_48 + 1;
    thunk_FUN_0042e827(param_2,&local_48,4,1);
    thunk_FUN_0042e827((int)param_2 + 4,&local_48,2,1);
    thunk_FUN_0042e827((int)param_2 + 6,&local_48,2,1);
    thunk_FUN_0042e827((int)param_2 + 8,&local_48,8,0);
    if (*local_48 == '}') {
      uVar1 = 0;
    }
    else {
      _memset(param_2,0,0x10);
      uVar1 = 0x80004005;
    }
  }
  else {
    uVar1 = 0x80004005;
  }
  return uVar1;
}
```

---

## FUN_0042e9e9 — 0x42e9e9

- Classification : internal
- Corps : `0x42e9e9–0x42ea19`
- État : pseudocode obtenu
- Evidence : `ev_71c4c8c2de0099a27f270462166d38d44385e3aa400283b2cd58fb18f509f49d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x7` — `KERNEL32.DLL::WideCharToMultiByte`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0042e9e9(LPSTR param_1,LPCWSTR param_2,int param_3)

{
  int iVar1;
  BOOL local_c [2];
  
  iVar1 = WideCharToMultiByte(0,0,param_2,-1,param_1,param_3,&DAT_0049e6b4,local_c);
  return iVar1;
}
```

---

## FUN_0042ea1a — 0x42ea1a

- Classification : internal
- Corps : `0x42ea1a–0x42ea3f`
- État : pseudocode obtenu
- Evidence : `ev_e3fbd90a20f6c6a058c3938299f89c868fcaf57e0ad0ffa3b149d58a23d442af`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x5` — `KERNEL32.DLL::MultiByteToWideChar`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0042ea1a(LPWSTR param_1,LPCSTR param_2,int param_3)

{
  int iVar1;
  
  iVar1 = MultiByteToWideChar(0,0,param_2,-1,param_1,param_3);
  return iVar1;
}
```

---

## FUN_0042ea40 — 0x42ea40

- Classification : internal
- Corps : `0x42ea40–0x42ea64`
- État : pseudocode obtenu
- Evidence : `ev_16a9f931ed37bfb22210d2b1ef99cced7e802d73fdbbc298350b02693ee0fd35`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b90` — `FUN_00474b90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0042ea40(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_00474b90();
  return iVar1 % (param_2 - param_1) + param_1;
}
```

---

## FUN_0042ea65 — 0x42ea65

- Classification : internal
- Corps : `0x42ea65–0x42ea91`
- État : pseudocode obtenu
- Evidence : `ev_a4ecfbd0788002b0eb8cdca128dd3a48a0f409e4cc4f1c4d82d584980ce8aed2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b90` — `FUN_00474b90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_0042ea65(double param_1,double param_2)

{
  int iVar1;
  
  iVar1 = FUN_00474b90();
  return ((float10)iVar1 * (float10)(param_2 - param_1)) / (float10)32767.0 + (float10)param_1;
}
```

---

## FUN_0042eba0 — 0x42eba0

- Classification : internal
- Corps : `0x42eba0–0x42ee33`
- État : pseudocode obtenu
- Evidence : `ev_4539fa61c9afdfc26f53f63f89c1eeee1db31de6684e55bec209ac2cf5d040ee`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49e6b8` — "ISNumEvents < MAX_INPUT_EVENTS"
- `0x49e6d8` — "C:\\float\\src\\input.cpp"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0042eba0(uint param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int local_c;
  
  if (DAT_005c36b8 == 8) {
    for (local_c = 0; local_c < 8; local_c = local_c + 1) {
      iVar3 = local_c + 1;
      (&DAT_005c3618)[local_c * 4] = (&DAT_005c3618)[iVar3 * 4];
      (&DAT_005c361c)[local_c * 4] = (&DAT_005c361c)[iVar3 * 4];
      (&DAT_005c3620)[local_c * 4] = (&DAT_005c3620)[iVar3 * 4];
      (&DAT_005c3624)[local_c * 4] = (&DAT_005c3624)[iVar3 * 4];
    }
    DAT_005c36b8 = DAT_005c36b8 + -1;
  }
  if (7 < DAT_005c36b8) {
    thunk_FUN_00414b64(s_C__float_src_input_cpp_0049e6d8,0x3f,
                       s_ISNumEvents_<_MAX_INPUT_EVENTS_0049e6b8);
  }
  iVar3 = DAT_005c36b8;
  iVar1 = DAT_005c36b8 * 0x10;
  puVar2 = &DAT_005c3618 + DAT_005c36b8 * 4;
  if (param_1 < 0x201) {
    if (param_1 == 0x200) {
      *puVar2 = 1;
      _DAT_005c36bc = param_3 & 0xffff;
      _DAT_005c36c0 = (int)param_3 >> 0x10;
    }
    else if (param_1 == 0x100) {
      *puVar2 = 6;
      *(undefined2 *)(&DAT_005c3620 + iVar3 * 4) = (undefined2)param_2;
      *(ushort *)((int)&DAT_005c3620 + iVar1 + 2) =
           (ushort)param_3 & 0xff | -(ushort)(DAT_005c36c8 != 0) & 0x100 |
           -(ushort)(DAT_005c36cc != 0) & 0x200;
      *(uint *)(&DAT_005c3698 + DAT_005c36b8 * 4) = param_3;
      DAT_005c36c4 = (undefined2)param_2;
      if (param_2 == 0x10) {
        DAT_005c36c8 = 1;
      }
      else if (param_2 == 0x11) {
        DAT_005c36cc = 1;
      }
    }
    else if (param_1 == 0x101) {
      *puVar2 = 7;
      *(undefined2 *)(&DAT_005c3620 + iVar3 * 4) = (undefined2)param_2;
      *(ushort *)((int)&DAT_005c3620 + iVar1 + 2) =
           -(ushort)(DAT_005c36c8 != 0) & 0x100 | -(ushort)(DAT_005c36cc != 0) & 0x200;
      if (param_2 == 0x10) {
        DAT_005c36c8 = 0;
      }
      else if (param_2 == 0x11) {
        DAT_005c36cc = 0;
      }
    }
  }
  else {
    switch(param_1) {
    case 0x201:
      *puVar2 = 2;
      *(undefined2 *)(&DAT_005c3620 + iVar3 * 4) = (undefined2)param_2;
      break;
    case 0x202:
      *puVar2 = 3;
      *(undefined2 *)(&DAT_005c3620 + iVar3 * 4) = (undefined2)param_2;
      break;
    case 0x204:
      *puVar2 = 4;
      *(undefined2 *)(&DAT_005c3620 + iVar3 * 4) = (undefined2)param_2;
      break;
    case 0x205:
      *puVar2 = 5;
      *(undefined2 *)(&DAT_005c3620 + iVar3 * 4) = (undefined2)param_2;
    }
  }
  *(undefined2 *)(&DAT_005c361c + iVar3 * 4) = DAT_005c36bc;
  *(undefined2 *)((int)&DAT_005c361c + iVar1 + 2) = DAT_005c36c0;
  DAT_005c36b8 = DAT_005c36b8 + 1;
  return;
}
```

---

## FUN_0042ee48 — 0x42ee48

- Classification : internal
- Corps : `0x42ee48–0x42ef16`
- État : pseudocode obtenu
- Evidence : `ev_b1eef3a6b252c5fa1733dbfcf82a66aff0128de7f09b851e71e222f58035aff9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042ee48(undefined4 *param_1)

{
  int iVar1;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  local_18 = 0;
  if (0 < DAT_005c36b8) {
    local_18 = DAT_005c3618;
    local_14 = DAT_005c361c;
    local_10 = DAT_005c3620;
    local_c = DAT_005c3624;
    for (local_1c = 0; local_1c < DAT_005c36b8; local_1c = local_1c + 1) {
      iVar1 = local_1c + 1;
      (&DAT_005c3618)[local_1c * 4] = (&DAT_005c3618)[iVar1 * 4];
      (&DAT_005c361c)[local_1c * 4] = (&DAT_005c361c)[iVar1 * 4];
      (&DAT_005c3620)[local_1c * 4] = (&DAT_005c3620)[iVar1 * 4];
      (&DAT_005c3624)[local_1c * 4] = (&DAT_005c3624)[iVar1 * 4];
    }
    DAT_005c36b8 = DAT_005c36b8 + -1;
    local_8 = 1;
  }
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = local_18;
    param_1[1] = local_14;
    param_1[2] = local_10;
    param_1[3] = local_c;
  }
  return local_8;
}
```

---

## FUN_0042ef17 — 0x42ef17

- Classification : internal
- Corps : `0x42ef17–0x42f018`
- État : pseudocode obtenu
- Evidence : `ev_84932651de367bf515bdf073e6673f51992e52b524f7c4d9a416ce8b8a101e83`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4019c9` — `thunk_FUN_0042eba0`
- `0x402289` — `thunk_FUN_0041be0f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042ef17(void)

{
  int local_2c;
  undefined1 local_28 [4];
  uint local_24;
  undefined4 local_20;
  int local_1c;
  int local_c;
  undefined4 local_8;
  
  local_8 = 1;
  local_c = 1;
  DAT_005c36c4 = 0;
LAB_0042ef34:
  if (local_c == 0) {
    return local_8;
  }
  local_c = thunk_FUN_0041be0f(local_28);
  if (local_24 == 0x12) {
    local_8 = 0;
  }
  if (0x202 < local_24) goto LAB_0042ef93;
  if (local_24 < 0x200) {
    if (0xff < local_24) {
      if (local_24 < 0x102) goto LAB_0042efa7;
      if (local_24 == 0x102) {
        for (local_2c = 0; local_2c < DAT_005c36b8; local_2c = local_2c + 1) {
          if (((&DAT_005c3618)[local_2c * 4] == 6) &&
             (local_1c == *(int *)(&DAT_005c3698 + local_2c * 4))) {
            *(undefined2 *)(&DAT_005c3624 + local_2c * 4) = (undefined2)local_20;
            break;
          }
        }
      }
    }
    goto LAB_0042ef34;
  }
LAB_0042efa7:
  thunk_FUN_0042eba0(local_24,local_20,local_1c);
  goto LAB_0042ef34;
LAB_0042ef93:
  if ((local_24 < 0x204) || (0x205 < local_24)) goto LAB_0042ef34;
  goto LAB_0042efa7;
}
```

---

## FUN_0042f019 — 0x42f019

- Classification : internal
- Corps : `0x42f019–0x42f023`
- État : pseudocode obtenu
- Evidence : `ev_69754a18f0c9c1bf835c7c068b943169ebe12c4d44060fd7d10cf7c15a6462d8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined2 FUN_0042f019(void)

{
  return DAT_005c36c4;
}
```

---


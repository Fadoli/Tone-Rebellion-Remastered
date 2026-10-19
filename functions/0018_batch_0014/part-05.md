# 0018_batch_0014 — détails (5/6)

## FUN_00471a6a — 0x471a6a

- Classification : internal
- Corps : `0x471a6a–0x471a9a`
- État : pseudocode obtenu
- Evidence : `ev_90006a42c1ac6beda50cbfe6ef65d5773af7a37b81ca251f1827bffc2039abf7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x4a617c` — "WorldWindow draw_hilited got called.\n"
- `0x4a61a4` — "FALSE"
- `0x4a61ac` — "C:\\float\\src\\worldwin.cpp"

### Pseudocode Ghidra

```c
void FUN_00471a6a(void)

{
  thunk_FUN_00414ad0(s_WorldWindow_draw_hilited_got_cal_004a617c);
  thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a61ac,0x31d,s_FALSE_004a61a4);
  return;
}
```

---

## FUN_00471a9b — 0x471a9b

- Classification : internal
- Corps : `0x471a9b–0x471aa7`
- État : pseudocode obtenu
- Evidence : `ev_ea5efa3135e615f7766babcfc4d4a9a023979f2045ff313c6b749421595f731f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00471a9b(void)

{
  return;
}
```

---

## FUN_00471aa8 — 0x471aa8

- Classification : internal
- Corps : `0x471aa8–0x471abd`
- État : pseudocode obtenu
- Evidence : `ev_4a89e973f49cf54fbb61ed93c9bd4e0115bce88d569df83bdaa240da7bed5418`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a50` — `thunk_FUN_00471ad6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00471aa8(void)

{
  undefined4 in_ECX;
  
  thunk_FUN_00471ad6();
  return in_ECX;
}
```

---

## FUN_00471abe — 0x471abe

- Classification : internal
- Corps : `0x471abe–0x471ad5`
- État : pseudocode obtenu
- Evidence : `ev_116ec362453299b6f4bf182ad71af634c8a14b7407a0204eaf650e8338d213c9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00471abe(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x100) = 0;
  return;
}
```

---

## FUN_00471ad6 — 0x471ad6

- Classification : internal
- Corps : `0x471ad6–0x471aed`
- État : pseudocode obtenu
- Evidence : `ev_206214b9a5c14c04522e135440cdd7c92fcec5d70ed6ec084efb6b2cd7ac899a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00471ad6(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x100) = 0;
  return;
}
```

---

## FUN_00471aee — 0x471aee

- Classification : internal
- Corps : `0x471aee–0x471b33`
- État : pseudocode obtenu
- Evidence : `ev_c271e1d4ac89077732bfdfee6006b0c6423d68102c9ee01dd526c4d3e0dfff00`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00471aee(int param_1)

{
  int in_ECX;
  
  if ((*(int *)(in_ECX + 0x100) < 0x40) && (param_1 != 0)) {
    *(int *)(in_ECX + *(int *)(in_ECX + 0x100) * 4) = param_1;
    *(int *)(in_ECX + 0x100) = *(int *)(in_ECX + 0x100) + 1;
  }
  return;
}
```

---

## FUN_00471b34 — 0x471b34

- Classification : internal
- Corps : `0x471b34–0x471b5b`
- État : pseudocode obtenu
- Evidence : `ev_d6eb49b69458020edd78dc3aed4ee9e28f481980829c1f42c0b6bcc5518b7a2f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4777a0` — `FUN_004777a0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00471b34(void)

{
  FUN_004777a0();
  return;
}
```

---

## FUN_00471b5c — 0x471b5c

- Classification : internal
- Corps : `0x471b5c–0x471b73`
- État : pseudocode obtenu
- Evidence : `ev_4455975ef5ede8ede9f2b5b5d85e11ab153e85fc4b59ff3f2d1b70b6c294abae`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00471b5c(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x100) = 0;
  return;
}
```

---

## FUN_00471b74 — 0x471b74

- Classification : internal
- Corps : `0x471b74–0x471e65`
- État : pseudocode obtenu
- Evidence : `ev_f25f1346aedb6be441cfd3d05ab0482959e14cef6da1817e51b6442e691bae49`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a28` — `thunk_FUN_0041081b`
- `0x401f4b` — `thunk_FUN_0042d811`
- `0x472c6c` — `__ftol`
- `0x474b90` — `FUN_00474b90`
- `0x476ce4` — `FUN_00476ce4`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00471b74(undefined4 *param_1,int param_2)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined1 uVar6;
  ushort uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int local_5c;
  int local_4c;
  int local_48;
  int local_44;
  int local_28;
  
  if (DAT_004a5e8c != 0) {
    local_48 = 5;
    local_44 = 0x2d;
    for (local_4c = 0; local_4c < 8; local_4c = local_4c + 1) {
      uVar6 = thunk_FUN_0041081b(&DAT_00630730,(double)local_48,(double)local_48,(double)local_44);
      (&DAT_006324a0)[local_4c] = uVar6;
      local_48 = local_48 + 7;
      local_44 = local_44 + 2;
    }
    DAT_004a5e8c = 0;
  }
  fVar2 = (float)(int)*(short *)(param_2 + 8);
  fVar3 = (float)(int)*(short *)(param_2 + 10);
  fVar4 = (float)(int)*(short *)(param_2 + 0xc);
  fVar5 = (float)(int)*(short *)(param_2 + 0xe);
  if ((((((float)(int)param_1[1] <= fVar2) && (fVar2 <= (float)(int)param_1[3])) &&
       ((float)(int)param_1[2] <= fVar3)) &&
      ((fVar3 <= (float)(int)param_1[4] && ((float)(int)param_1[1] <= fVar4)))) &&
     ((fVar4 <= (float)(int)param_1[3] &&
      (((float)(int)param_1[2] <= fVar5 && (fVar5 <= (float)(int)param_1[4])))))) {
    FUN_00476ce4((double)((fVar5 - fVar3) * (fVar5 - fVar3) + (fVar4 - fVar2) * (fVar4 - fVar2)));
    iVar8 = thunk_FUN_0042d811();
    iVar1 = *(int *)*param_1;
    for (local_28 = 0; iVar9 = __ftol(), local_28 < iVar9; local_28 = local_28 + 1) {
      iVar9 = __ftol();
      iVar10 = __ftol();
      iVar11 = __ftol();
      iVar11 = (local_28 * 0x14) / iVar11;
      FUN_00474b90();
      iVar12 = __ftol();
      uVar6 = (&DAT_006324a0)[iVar12];
      for (local_5c = 0; local_5c < 10; local_5c = local_5c + 1) {
        uVar7 = FUN_00474b90();
        *(undefined1 *)
         (iVar1 + *(int *)(iVar8 + (iVar10 + ((iVar11 + 1) / 2 -
                                             (int)((longlong)
                                                   (ulonglong)(uint)((int)(uint)uVar7 >> 8) %
                                                  (longlong)(iVar11 + 1)))) * 4) +
         iVar9 + ((iVar11 + 1) / 2 - (int)((longlong)(ulonglong)uVar7 % (longlong)(iVar11 + 1)))) =
             uVar6;
      }
    }
  }
  return;
}
```

---

## FUN_00471e66 — 0x471e66

- Classification : internal
- Corps : `0x471e66–0x472012`
- État : pseudocode obtenu
- Evidence : `ev_6e36780f41a531e2dfc3f54e7397ffdf4c784b39baff3f6e88954fe4f89de3a8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011bd` — `thunk_FUN_0047117d`
- `0x401276` — `thunk_FUN_0042dd95`
- `0x4019ec` — `thunk_FUN_00405265`
- `0x401a9b` — `thunk_FUN_00471b74`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x472c6c` — `__ftol`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x4a61c8` — "shape"
- `0x4a61d0` — "C:\\float\\src\\worldwin.cpp"

### Pseudocode Ghidra

```c
void FUN_00471e66(int param_1)

{
  int iVar1;
  undefined4 *in_ECX;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_34 [12];
  int local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  short *local_18;
  int local_14;
  int local_10;
  undefined4 *local_c;
  undefined4 local_8;
  
  local_8 = 0;
  local_c = in_ECX;
  local_14 = thunk_FUN_0040e864(*(undefined2 *)(param_1 + 0x74));
  if (local_14 == 0) {
    uVar3 = thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a61d0,0x3aa,s_shape_004a61c8);
  }
  else {
    uVar3 = 0;
  }
  for (local_10 = 0; local_10 < (int)in_ECX[0x40]; local_10 = local_10 + 1) {
    local_18 = (short *)*local_c;
    local_1c = __ftol();
    local_1c = local_1c + -3000;
    iVar2 = *(int *)(local_18 + 2);
    if (iVar2 == 0) {
      local_20 = (int)*local_18;
      local_28 = 0xf;
      iVar1 = thunk_FUN_0047117d(*local_18);
      if ((iVar1 != 0) && (local_28 = 0, *(short *)(param_1 + 0x76) == local_20)) {
        local_28 = 0x1e;
      }
      local_24 = *(undefined4 *)(param_1 + 0x70);
      if (local_20 < 4) {
        local_24 = 0x10000;
      }
      thunk_FUN_00405265(param_1 + 8,local_14,(short)(&DAT_005eebf8)[local_20 * 0x14f4] + local_28,
                         (int)local_18[4],(int)local_18[5],&DAT_004b28f0,0,local_24,local_24,0,iVar2
                         ,uVar3);
      if (DAT_006324a8 != 0) {
        FUN_00472ca0(local_34,&DAT_004a61ec,local_20);
        thunk_FUN_0042dd95((int)local_18[4],(int)local_18[5],local_34);
      }
    }
    else if (iVar2 == 1) {
      thunk_FUN_00471b74(param_1 + 8,local_18);
    }
    local_c = local_c + 1;
  }
  return;
}
```

---

## FUN_00472013 — 0x472013

- Classification : internal
- Corps : `0x472013–0x472161`
- État : pseudocode obtenu
- Evidence : `ev_48660388f9661c8b08cc63052702ca5f112c74be7eeba4446be409c17bd4422a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a61f0` — "item_ptr != NULL"
- `0x4a6204` — "C:\\float\\src\\worldwin.cpp"
- `0x4a6220` — "islenum<MAX_ISLANDS"
- `0x4a6234` — "C:\\float\\src\\worldwin.cpp"

### Pseudocode Ghidra

```c
short * FUN_00472013(int param_1,int param_2)

{
  short *psVar1;
  int in_ECX;
  int iVar2;
  short local_14;
  undefined4 *local_10;
  short local_c;
  
  iVar2 = *(int *)(in_ECX + 0x100) + -1;
  local_10 = (undefined4 *)(in_ECX + iVar2 * 4);
  local_c = (short)iVar2;
  local_14 = local_c;
  do {
    if (local_14 < 0) {
      return (short *)0x0;
    }
    if (local_10 == (undefined4 *)0x0) {
      thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a6204,0x3fc,s_item_ptr____NULL_004a61f0);
    }
    psVar1 = (short *)*local_10;
    if (*(int *)(psVar1 + 2) == 0) {
      iVar2 = (int)*psVar1;
      if (0xe < iVar2) {
        thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a6234,0x403,s_islenum<MAX_ISLANDS_004a6220
                          );
      }
      if ((((*(int *)(&DAT_006323b0 + iVar2 * 0x10) + (int)psVar1[4] < param_1) &&
           (param_1 < *(int *)(&DAT_006323b8 + iVar2 * 0x10) + (int)psVar1[4])) &&
          (*(int *)(&DAT_006323b4 + iVar2 * 0x10) + (int)psVar1[5] < param_2)) &&
         (param_2 < *(int *)(&DAT_006323bc + iVar2 * 0x10) + (int)psVar1[5])) {
        return psVar1;
      }
    }
    local_14 = local_14 + -1;
    local_10 = local_10 + -1;
  } while( true );
}
```

---

## FUN_00472a10 — 0x472a10

- Classification : internal
- Corps : `0x472a10–0x472a3d`
- État : pseudocode obtenu
- Evidence : `ev_ba9370242fa8eadc39032c1fac98ff2e43f1accadeb6f51e71747ab889aa5908`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401078` — `COleResizeBar::~COleResizeBar`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
COleResizeBar * FUN_00472a10(uint param_1)

{
  COleResizeBar *in_ECX;
  
  COleResizeBar::~COleResizeBar(in_ECX);
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_00472bc0 — 0x472bc0

- Classification : internal
- Corps : `0x472bc0–0x472be0`
- État : pseudocode obtenu
- Evidence : `ev_5b1e5682866d1e464ae5cc544e80e98194389798baa45878a8849c2c83597281`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472c00` — `FUN_00472c00`
- `0x4786c0` — `__setdefaultprecision`
- `0x478740` — `__ms_p5_mp_test_fdiv`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00472bc0(void)

{
  FUN_00472c00();
  DAT_00632504 = __ms_p5_mp_test_fdiv();
  __setdefaultprecision();
  return;
}
```

---

## FUN_00472bf0 — 0x472bf0

- Classification : internal
- Corps : `0x472bf0–0x472bf4`
- État : pseudocode obtenu
- Evidence : `ev_901b0d37219753d82801f3a8523fe1b2c8fbd04f24c4d708805d1264dd7324ec`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00472bf0(void)

{
  return;
}
```

---

## FUN_00472c00 — 0x472c00

- Classification : internal
- Corps : `0x472c00–0x472c40`
- État : pseudocode obtenu
- Evidence : `ev_ceb54230c92ccddd61f6294165b0e7cd59fd8cfc85d7e518017e037061c16f7a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00472c00(void)

{
  PTR___fptrap_004a63d8 = __cfltcvt;
  PTR___fptrap_004a63dc = __cropzeros;
  PTR___fptrap_004a63e0 = __fassign;
  PTR___fptrap_004a63e4 = FUN_00478790;
  PTR___fptrap_004a63e8 = __positive;
  PTR___fptrap_004a63ec = __cfltcvt;
  return;
}
```

---

## FUN_00472c50 — 0x472c50

- Classification : internal
- Corps : `0x472c50–0x472c6b`
- État : pseudocode obtenu
- Evidence : `ev_cae1c33193953b883d8d02de43c77f596204b9e3a4edfb103b10f8a664916b8f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00472c50(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_00632500;
  DAT_00632500 = param_1;
  return uVar1;
}
```

---

## __ftol — 0x472c6c

- Classification : internal
- Corps : `0x472c6c–0x472c92`
- État : pseudocode obtenu
- Evidence : `ev_a0793f5d9552f14a7accb48cbf992564af87d834ce8fe8c91da7a4cfbdd76ad1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __ftol
   
   Library: Visual Studio */

longlong __ftol(void)

{
  float10 in_ST0;
  
  return (longlong)ROUND(in_ST0);
}
```

---

## FUN_00472ca0 — 0x472ca0

- Classification : internal
- Corps : `0x472ca0–0x472d99`
- État : pseudocode obtenu
- Evidence : `ev_b9a2edbaa37fdaf91eaf3a9974b929c7ca0d844bf067a202e822c6132ea711a6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x472cd8 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x472d02 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x478ef0` — `FUN_00478ef0`
- `0x479170` — `FUN_00479170`
- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x495197` — "`format != NULL"
- `0x4951a8` — "sprintf.c"
- `0x4951a8` — "sprintf.c"
- `0x4951b4` — "string != NULL"

### Pseudocode Ghidra

```c
undefined4 FUN_00472ca0(undefined1 *param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  if ((param_1 == (undefined1 *)0x0) &&
     (iVar2 = FUN_0047a120(2,"sprintf.c",0x5d,0,"string != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == 0) && (iVar2 = FUN_0047a120(2,"sprintf.c",0x5e,0,"format != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  local_18 = 0x42;
  local_1c = param_1;
  local_24 = param_1;
  local_20 = 0x7fffffff;
  uVar3 = FUN_00479170(&local_24,param_2,&stack0x0000000c);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    FUN_00478ef0(0,&local_24);
  }
  else {
    *local_24 = 0;
  }
  return uVar3;
}
```

---

## FUN_00472da0 — 0x472da0

- Classification : internal
- Corps : `0x472da0–0x472da6`
- État : pseudocode obtenu
- Evidence : `ev_2570964e2781fa14b34f024cdacdec88d18dfea602f7fc25c899f9a6c4a1c735`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint * FUN_00472da0(uint *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  
  puVar4 = param_1;
  while (((uint)param_2 & 3) != 0) {
    bVar1 = (byte)*param_2;
    uVar3 = (uint)bVar1;
    param_2 = (uint *)((int)param_2 + 1);
    if (bVar1 == 0) goto LAB_00472e88;
    *(byte *)puVar4 = bVar1;
    puVar4 = (uint *)((int)puVar4 + 1);
  }
  do {
    uVar2 = *param_2;
    uVar3 = *param_2;
    param_2 = param_2 + 1;
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar3 == '\0') {
LAB_00472e88:
        *(byte *)puVar4 = (byte)uVar3;
        return param_1;
      }
      if ((char)(uVar3 >> 8) == '\0') {
        *(short *)puVar4 = (short)uVar3;
        return param_1;
      }
      if ((uVar3 & 0xff0000) == 0) {
        *(short *)puVar4 = (short)uVar3;
        *(byte *)((int)puVar4 + 2) = 0;
        return param_1;
      }
      if ((uVar3 & 0xff000000) == 0) {
        *puVar4 = uVar3;
        return param_1;
      }
    }
    *puVar4 = uVar3;
    puVar4 = puVar4 + 1;
  } while( true );
}
```

---

## FUN_00472db0 — 0x472db0

- Classification : internal
- Corps : `0x472db0–0x472e8f`
- État : pseudocode obtenu
- Evidence : `ev_61e9baf158f6bd654333f1caa98d91b51d950194ca7e94bcf37929bf17723cfe`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint * FUN_00472db0(uint *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  
  puVar3 = param_1;
  do {
    if (((uint)puVar3 & 3) == 0) goto LAB_00472dcc;
    uVar4 = *puVar3;
    puVar3 = (uint *)((int)puVar3 + 1);
  } while ((byte)uVar4 != 0);
  goto LAB_00472dff;
  while( true ) {
    if ((uVar4 & 0xff0000) == 0) {
      puVar5 = (uint *)((int)puVar5 + 2);
      goto joined_r0x00472e1b;
    }
    if ((uVar4 & 0xff000000) == 0) break;
LAB_00472dcc:
    do {
      puVar5 = puVar3;
      puVar3 = puVar5 + 1;
    } while (((*puVar5 ^ 0xffffffff ^ *puVar5 + 0x7efefeff) & 0x81010100) == 0);
    uVar4 = *puVar5;
    if ((char)uVar4 == '\0') goto joined_r0x00472e1b;
    if ((char)(uVar4 >> 8) == '\0') {
      puVar5 = (uint *)((int)puVar5 + 1);
      goto joined_r0x00472e1b;
    }
  }
LAB_00472dff:
  puVar5 = (uint *)((int)puVar3 + -1);
joined_r0x00472e1b:
  do {
    if (((uint)param_2 & 3) == 0) {
      do {
        uVar2 = *param_2;
        uVar4 = *param_2;
        param_2 = param_2 + 1;
        if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
          if ((char)uVar4 == '\0') {
LAB_00472e88:
            *(byte *)puVar5 = (byte)uVar4;
            return param_1;
          }
          if ((char)(uVar4 >> 8) == '\0') {
            *(short *)puVar5 = (short)uVar4;
            return param_1;
          }
          if ((uVar4 & 0xff0000) == 0) {
            *(short *)puVar5 = (short)uVar4;
            *(byte *)((int)puVar5 + 2) = 0;
            return param_1;
          }
          if ((uVar4 & 0xff000000) == 0) {
            *puVar5 = uVar4;
            return param_1;
          }
        }
        *puVar5 = uVar4;
        puVar5 = puVar5 + 1;
      } while( true );
    }
    bVar1 = (byte)*param_2;
    uVar4 = (uint)bVar1;
    param_2 = (uint *)((int)param_2 + 1);
    if (bVar1 == 0) goto LAB_00472e88;
    *(byte *)puVar5 = bVar1;
    puVar5 = (uint *)((int)puVar5 + 1);
  } while( true );
}
```

---

## _strlen — 0x472e90

- Classification : internal
- Corps : `0x472e90–0x472f0a`
- État : pseudocode obtenu
- Evidence : `ev_cd7e36152c2104f087fd37f2a9255d5daf482eac00cdf922e936dc1ebbc1f93f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _strlen
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

size_t __cdecl _strlen(char *_Str)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar2 = (uint *)_Str;
  do {
    if (((uint)puVar2 & 3) == 0) goto LAB_00472eb0;
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
LAB_00472ee3:
  return (size_t)((int)puVar2 + (-1 - (int)_Str));
LAB_00472eb0:
  do {
    do {
      puVar3 = puVar2;
      puVar2 = puVar3 + 1;
    } while (((*puVar3 ^ 0xffffffff ^ *puVar3 + 0x7efefeff) & 0x81010100) == 0);
    uVar1 = *puVar3;
    if ((char)uVar1 == '\0') {
      return (int)puVar3 - (int)_Str;
    }
    if ((char)(uVar1 >> 8) == '\0') {
      return (size_t)((int)puVar3 + (1 - (int)_Str));
    }
    if ((uVar1 & 0xff0000) == 0) {
      return (size_t)((int)puVar3 + (2 - (int)_Str));
    }
  } while ((uVar1 & 0xff000000) != 0);
  goto LAB_00472ee3;
}
```

---

## FUN_00472f10 — 0x472f10

- Classification : internal
- Corps : `0x472f10–0x472fc6`
- État : pseudocode obtenu
- Evidence : `ev_cea34855829536b2d246faa4145c946c44fc96e7b9141e1dd3329f62f8a64eb0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x472f48 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x472f72 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x472e90` — `_strlen`
- `0x47a120` — `FUN_0047a120`
- `0x47a7c0` — `FUN_0047a7c0`

### Chaînes référencées

- `0x495197` — "`format != NULL"
- `0x4951b4` — "string != NULL"
- `0x4951c4` — "sscanf.c"
- `0x4951c4` — "sscanf.c"

### Pseudocode Ghidra

```c
undefined4 FUN_00472f10(char *param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  char *local_24;
  size_t local_20;
  char *local_1c;
  undefined4 local_18;
  
  if ((param_1 == (char *)0x0) &&
     (iVar2 = FUN_0047a120(2,"sscanf.c",0x42,0,"string != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == 0) && (iVar2 = FUN_0047a120(2,"sscanf.c",0x43,0,"format != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  local_18 = 0x49;
  local_1c = param_1;
  local_24 = param_1;
  local_20 = _strlen(param_1);
  uVar3 = FUN_0047a7c0(&local_24,param_2,&stack0x0000000c);
  return uVar3;
}
```

---

## FUN_00472fd0 — 0x472fd0

- Classification : internal
- Corps : `0x472fd0–0x472ffc`
- État : pseudocode obtenu
- Evidence : `ev_b8cce2b1057429b660467629de7dba42a66246bfd5a4f404c8fbfb79b3acce0d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00472fd0(code *UNRECOVERED_JUMPTABLE)

{
  undefined4 *unaff_FS_OFFSET;
  
  *unaff_FS_OFFSET = *(undefined4 *)*unaff_FS_OFFSET;
                    /* WARNING: Could not recover jumptable at 0x00472ffb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}
```

---

## _CallMemberFunction0 — 0x473010

- Classification : internal
- Corps : `0x473010–0x473016`
- État : pseudocode obtenu
- Evidence : `ev_191e2460bfa8559f4165147b835b99082405885f728d865261bcd815e58658d1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    void __stdcall _CallMemberFunction0(void *,void *)
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

void _CallMemberFunction0(void *param_1,void *param_2)

{
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x00473015. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*param_2)();
  return;
}
```

---

## FUN_00473020 — 0x473020

- Classification : internal
- Corps : `0x473020–0x473026`
- État : pseudocode obtenu
- Evidence : `ev_cff058bdba1d1bb62efe7ef85f35eb8d401b5c9319a20473eabbece225b94f02`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00473020(undefined4 param_1,code *UNRECOVERED_JUMPTABLE)

{
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x00473025. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}
```

---

## FUN_00473030 — 0x473030

- Classification : internal
- Corps : `0x473030–0x473036`
- État : pseudocode obtenu
- Evidence : `ev_31bf063a2cab62d51e68c0545ef629898ca8698356071567dd242e8d68a37058`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00473030(undefined4 param_1,code *UNRECOVERED_JUMPTABLE)

{
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x00473035. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}
```

---

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


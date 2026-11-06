# 0008_batch_0004 — détails (2/3)

## FUN_0041137c — 0x41137c

- Classification : internal
- Corps : `0x41137c–0x411477`
- État : pseudocode obtenu
- Evidence : `ev_926cf15c7d86f0f126efbc3fc22c447d1b66e29a13df68466493cfebdf0820b0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f14` — `thunk_FUN_00404770`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x40229d` — `thunk_FUN_00405e11`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041137c(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5,
                 int param_6,int param_7)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int local_34;
  int local_30;
  uint local_28;
  int local_20;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  thunk_FUN_00405e11(param_2,param_3,0,0,0,&local_14);
  iVar1 = local_c - local_14;
  if (param_7 != 0) {
    local_14 = -local_c;
  }
  local_30 = param_4 + local_14;
  local_28 = 0;
  uVar2 = thunk_FUN_0040ec89(&DAT_0049b554,1);
  for (local_20 = 0xc; local_20 < iVar1 + 1; local_20 = local_20 + 0x18) {
    for (local_34 = 0xc; local_34 < (local_8 - local_10) + 1; local_34 = local_34 + 0x18) {
      iVar3 = (int)(param_6 + -8 + (local_28 & 7)) / 2;
      if ((-1 < iVar3) && (iVar3 < 0xb)) {
        thunk_FUN_00404770(param_1,uVar2,iVar3,local_30 + local_20,param_5 + local_10 + local_34);
      }
      local_28 = local_28 + 5;
    }
  }
  return;
}
```

---

---

## FUN_00411478 — 0x411478

- Classification : internal
- Corps : `0x411478–0x41169e`
- État : pseudocode obtenu
- Evidence : `ev_fcca86b0878721fe3473a3fd2528e70affea05767e0d764a8ab1731e63b41523`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014ce` — `thunk_FUN_004108fa`
- `0x401f4b` — `thunk_FUN_0042d811`
- `0x402491` — `thunk_FUN_0042dd0f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00411478(undefined4 *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint local_1c;
  int local_18;
  int local_14;
  undefined1 local_8 [4];
  
  local_8[0] = thunk_FUN_004108fa(0,0x403e0000,0,0x403e0000,0,0x403e0000);
  local_8[1] = thunk_FUN_004108fa(0,0x40470000,0,0x40470000,0,0x40470000);
  local_8[2] = thunk_FUN_0042dd0f(1);
  iVar2 = thunk_FUN_0042d811();
  iVar1 = *(int *)*param_1;
  local_1c = 0xdefeca35;
  if (param_2 < param_1[1] + 1) {
    param_2 = param_1[1] + 1;
  }
  if (param_1[3] + -1 < param_4) {
    param_4 = param_1[3] + -1;
  }
  if (param_3 < param_1[2] + 1) {
    param_3 = param_1[2] + 1;
  }
  if (param_1[4] + -1 < param_5) {
    param_5 = param_1[4] + -1;
  }
  for (local_18 = param_3; local_14 = param_2, local_18 <= param_5; local_18 = local_18 + 2) {
    for (; local_14 <= param_4; local_14 = local_14 + 2) {
      uVar3 = ((((local_1c + param_6 + local_14) - param_2) + local_18) - param_3) % 0x77;
      local_1c = local_1c >> 1;
      if (local_1c < 0x40) {
        local_1c = local_1c + 0xdefeca35;
      }
      if ((uVar3 < 7) &&
         (*(undefined1 *)(iVar1 + *(int *)(iVar2 + local_18 * 4) + local_14) =
               local_8[(char)(&DAT_0049b468)[uVar3]], (&DAT_0049b470)[uVar3] != '\x04')) {
        *(undefined1 *)(iVar1 + *(int *)(iVar2 + local_18 * 4) + 1 + local_14) =
             local_8[(char)(&DAT_0049b470)[uVar3]];
        *(undefined1 *)(iVar1 + *(int *)(iVar2 + 4 + local_18 * 4) + local_14) =
             *(undefined1 *)(iVar1 + *(int *)(iVar2 + local_18 * 4) + 1 + local_14);
        *(undefined1 *)(iVar1 + *(int *)(iVar2 + local_18 * 4) + -1 + local_14) =
             *(undefined1 *)(iVar1 + *(int *)(iVar2 + 4 + local_18 * 4) + local_14);
        *(undefined1 *)(iVar1 + *(int *)(iVar2 + -4 + local_18 * 4) + local_14) =
             *(undefined1 *)(iVar1 + *(int *)(iVar2 + local_18 * 4) + -1 + local_14);
      }
    }
  }
  return;
}
```

---

---

## FUN_0041169f — 0x41169f

- Classification : internal
- Corps : `0x41169f–0x41179d`
- État : pseudocode obtenu
- Evidence : `ev_28da3bfea9d1018c50c839b35640e6131b22b87041cb621d14b84b2f7670bb1c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011a9` — `thunk_FUN_00403c35`
- `0x402022` — `thunk_FUN_00406604`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041169f(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,int param_8)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int local_18 [4];
  int local_8;
  
  thunk_FUN_00403c35(param_1,param_2,param_3,param_4,param_3,0,param_6);
  thunk_FUN_00403c35(param_1,param_2,param_5,param_4,param_5,0,param_6);
  thunk_FUN_00403c35(param_1,param_2,param_3,param_2,param_5,0,param_6);
  thunk_FUN_00403c35(param_1,param_4,param_3,param_4,param_5,0,param_6);
  if (param_7 != 0) {
    if (param_8 == -1) {
      param_8 = param_6;
    }
    piVar2 = param_1;
    piVar3 = local_18;
    for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar3 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar3 = piVar3 + 1;
    }
    local_18[1] = local_18[1] + 1 + param_2;
    local_18[3] = param_1[1] + -1 + param_4;
    local_18[2] = local_18[2] + 1 + param_3;
    local_8 = param_1[2] + -1 + param_5;
    thunk_FUN_00406604(local_18,param_8);
  }
  return;
}
```

---

---

## FUN_0041179e — 0x41179e

- Classification : internal
- Corps : `0x41179e–0x4118de`
- État : pseudocode obtenu
- Evidence : `ev_1d6d5b99ff20127dbfa10eec32eff74ce46ab47d948d0ac1fb089d16bea1747f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401442` — `thunk_FUN_0041169f`
- `0x402022` — `thunk_FUN_00406604`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472c6c` — `__ftol`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041179e(int *param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6,
                 undefined4 param_7,undefined4 param_8,int param_9,int param_10)

{
  undefined1 uVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int local_18 [4];
  int local_8;
  
  piVar3 = param_1;
  piVar4 = local_18;
  for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar4 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar4 = piVar4 + 1;
  }
  local_18[1] = local_18[1] + param_2;
  local_18[2] = local_18[2] + param_3;
  local_18[3] = local_18[1] + param_4;
  local_8 = local_18[2] + param_5;
  if (param_9 == 0) {
    local_18[3] = __ftol();
    local_18[3] = local_18[1] + local_18[3];
  }
  else {
    iVar2 = __ftol();
    local_18[2] = local_8 - iVar2;
  }
  if (param_10 == 0) {
    uVar1 = thunk_FUN_0042dd0f(1,0,0xffffffff);
    thunk_FUN_0041169f(param_1,param_2,param_3,param_2 + param_4,param_3 + param_5,uVar1);
  }
  else {
    uVar1 = thunk_FUN_0042dd0f(1,0,0xffffffff);
    thunk_FUN_0041169f(param_1,local_18[1] - param_1[1],local_18[2] - param_1[2],
                       local_18[3] - param_1[1],local_8 - param_1[2],uVar1);
  }
  local_18[1] = local_18[1] + 1;
  local_18[3] = local_18[3] + -1;
  local_18[2] = local_18[2] + 1;
  local_8 = local_8 + -1;
  thunk_FUN_00406604(local_18,param_6);
  return;
}
```

---

---

## FUN_004118df — 0x4118df

- Classification : internal
- Corps : `0x4118df–0x4119b9`
- État : pseudocode obtenu
- Evidence : `ev_1e9e2b997d11c89a045e32925f3af8bee4aefadf27400aad1545da2b7eb86f8f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f14` — `thunk_FUN_00404770`
- `0x402022` — `thunk_FUN_00406604`
- `0x472c6c` — `__ftol`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004118df(int *param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5,
                 int param_6,int param_7,int param_8,undefined4 param_9,double param_10,int param_11
                 )

{
  int iVar1;
  int *piVar2;
  int local_18 [4];
  int local_8;
  
  thunk_FUN_00404770(param_1,param_2,param_3,param_4,param_5);
  piVar2 = local_18;
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar2 = *param_1;
    param_1 = param_1 + 1;
    piVar2 = piVar2 + 1;
  }
  local_18[1] = local_18[1] + param_4 + param_8;
  local_18[2] = local_18[2] + param_5 + param_8;
  local_18[3] = local_18[1] + param_6 + param_8 * -2;
  local_8 = local_18[2] + param_7 + param_8 * -2;
  if (param_10 < 1.0) {
    iVar1 = __ftol();
    if (param_11 == 0) {
      local_18[1] = local_18[1] + iVar1;
    }
    else {
      local_8 = local_8 - iVar1;
    }
    thunk_FUN_00406604(local_18,param_9);
  }
  return;
}
```

---

---

## FUN_004119ba — 0x4119ba

- Classification : internal
- Corps : `0x4119ba–0x411ab1`
- État : pseudocode obtenu
- Evidence : `ev_393ddd67e73634646c721faf8d924123cca267f4086a6f25c7175d044c47f343`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x40229d` — `thunk_FUN_00405e11`

### Chaînes référencées

- `0x49b55c` — "C:\\float\\src\\color.cpp"
- `0x49b574` — "shape"
- `0x49b57c` — "C:\\float\\src\\color.cpp"

### Pseudocode Ghidra

```c
void FUN_004119ba(int param_1,int param_2,undefined4 param_3,int *param_4,int *param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  if (param_1 == 0) {
    uVar2 = thunk_FUN_00414b64(s_C__float_src_color_cpp_0049b55c,0x31c,&DAT_0049b558);
  }
  else {
    uVar2 = 0;
  }
  if (param_2 == 0) {
    uVar1 = thunk_FUN_00414b64(s_C__float_src_color_cpp_0049b57c,0x31d,s_shape_0049b574);
  }
  else {
    uVar1 = 0;
  }
  thunk_FUN_00405e11(param_2,param_3,0,0,0,&local_1c,uVar1,uVar2);
  *param_4 = (*(int *)(param_1 + 0xc) - *(int *)(param_1 + 4)) - (local_14 - local_1c);
  if (*param_4 != 0) {
    *param_4 = *param_4 / 2;
  }
  *param_5 = (*(int *)(param_1 + 0x10) - *(int *)(param_1 + 8)) - (local_10 - local_18);
  if (*param_5 != 0) {
    *param_5 = *param_5 / 2;
  }
  *param_4 = *param_4 - local_1c;
  *param_5 = *param_5 - local_18;
  return;
}
```

---

---

## FUN_00412020 — 0x412020

- Classification : internal
- Corps : `0x412020–0x412029`
- État : pseudocode obtenu
- Evidence : `ev_7ade3d560a12b5c1fd620e550b4423c99fc295d394d47263e8565ac7ca3f5644`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x41202a` — `FUN_0041202a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00412020(void)

{
  FUN_0041202a();
  return;
}
```

---

---

## FUN_0041202a — 0x41202a

- Classification : internal
- Corps : `0x41202a–0x412038`
- État : pseudocode obtenu
- Evidence : `ev_f1089f4feea5ed921d1a40968efb4111aea923ab442c937ce8556a400efae4d1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4017ad` — `thunk_FUN_004120e0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041202a(void)

{
  thunk_FUN_004120e0();
  return;
}
```

---

---

## FUN_00412039 — 0x412039

- Classification : internal
- Corps : `0x412039–0x412042`
- État : pseudocode obtenu
- Evidence : `ev_a990fc46f2dc9e4d0450e5e54b11b318c3399655e22d9069d5ca3c8bf1005e6c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x412043` — `FUN_00412043`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00412039(void)

{
  FUN_00412043();
  return;
}
```

---

---

## FUN_00412043 — 0x412043

- Classification : internal
- Corps : `0x412043–0x412051`
- État : pseudocode obtenu
- Evidence : `ev_e5548c7a9c5a120f6c414d17571acf0247465719086f61b7f3844b6382238fa5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4024a5` — `thunk_FUN_00413d86`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00412043(void)

{
  thunk_FUN_00413d86();
  return;
}
```

---

---

## FUN_00412052 — 0x412052

- Classification : internal
- Corps : `0x412052–0x4120ca`
- État : pseudocode obtenu
- Evidence : `ev_6efd87be85450ef2b6b8da06758e92d22ab3767029d687497c8a22b50c333213`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401d8e` — `thunk_FUN_004140dd`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49b600` — "FALSE"
- `0x49b608` — "C:\\float\\src\\command.cpp"

### Pseudocode Ghidra

```c
void FUN_00412052(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 local_8;
  
  switch(param_1) {
  case 1:
    local_8 = 1;
    break;
  case 2:
    local_8 = 2;
    break;
  case 3:
    local_8 = 3;
    break;
  case 4:
    local_8 = 4;
    break;
  default:
    thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b608,0x5c,s_FALSE_0049b600);
  }
  thunk_FUN_004140dd(local_8,param_2,param_3,5);
  return;
}
```

---

---

## FUN_004120db — 0x4120db

- Classification : internal
- Corps : `0x4120db–0x4120df`
- État : pseudocode obtenu
- Evidence : `ev_824cceb7f464dbde453d601d62b207fb93919b8f591d023f309af548e0f3e087`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004120db(void)

{
  return;
}
```

---

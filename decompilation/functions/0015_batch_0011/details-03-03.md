# 0015_batch_0011 — détails (3/3)

## FUN_004500c4 — 0x4500c4

- Classification : internal
- Corps : `0x4500c4–0x450196`
- État : pseudocode obtenu
- Evidence : `ev_ab12ac3e0e159b3c3218e0a63f6eaf2b9eb96a1ed5111b03132644c0b4b8c3f5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004500c4(void)

{
  int in_ECX;
  
  _memset((void *)(in_ECX + 0x3a),0,0x10);
  *(undefined4 *)(in_ECX + 0x50) = 0;
  *(undefined4 *)(in_ECX + 0x54) = 0;
  *(undefined4 *)(in_ECX + 0x1c) = 0;
  *(undefined2 *)(in_ECX + 0x32) = 0;
  *(undefined2 *)(in_ECX + 0x30) = 0;
  *(undefined2 *)(in_ECX + 0x2e) = 0;
  *(undefined2 *)(in_ECX + 0x2c) = 0;
  *(undefined2 *)(in_ECX + 0x2a) = 0;
  *(undefined2 *)(in_ECX + 0x28) = 0;
  *(undefined4 *)(in_ECX + 0x24) = 0;
  *(undefined1 *)(in_ECX + 0x22) = 0;
  *(undefined4 *)(in_ECX + 0x14) = 0xffffffff;
  *(undefined2 *)(in_ECX + 0x18) = 0xffff;
  *(undefined2 *)(in_ECX + 0x58) = 0;
  if (*(int *)(in_ECX + 4) != 3) {
    *(undefined4 *)(in_ECX + 0x10) = 0;
  }
  if (*(int *)(in_ECX + 0x10) != 3) {
    *(undefined2 *)(in_ECX + 0x4a) = 0;
  }
  if (*(int *)(in_ECX + 4) != 2) {
    *(undefined2 *)(in_ECX + 0x36) = 0xffff;
  }
  return;
}
```

---

---

## FUN_00450197 — 0x450197

- Classification : internal
- Corps : `0x450197–0x4502db`
- État : pseudocode obtenu
- Evidence : `ev_2051246410a63d4b65ce11be1e28fceb301af46227914716355c6e0125d2722c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401154` — `thunk_FUN_00414b91`
- `0x40125d` — `thunk_FUN_00456c13`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4021ad` — `thunk_FUN_004641de`
- `0x402248` — `thunk_FUN_00456b8d`
- `0x4024c3` — `thunk_FUN_00456bd0`

### Chaînes référencées

- `0x4a2978` — "x && y && anim < ANM_NumTypes"
- `0x4a2998` — "C:\\float\\src\\pad.cpp"
- `0x4a29b0` — "Bad Anim Type"
- `0x4a29c0` — "FALSE"
- `0x4a29c8` — "C:\\float\\src\\pad.cpp"

### Pseudocode Ghidra

```c
void FUN_00450197(int *param_1,int *param_2,int param_3)

{
  short sVar1;
  int iVar2;
  int in_ECX;
  undefined2 extraout_var;
  undefined4 uVar3;
  
  if (((param_1 == (int *)0x0) || (param_2 == (int *)0x0)) || (7 < param_3)) {
    uVar3 = thunk_FUN_00414b64(s_C__float_src_pad_cpp_004a2998,0x9a,
                               s_x____y____anim_<_ANM_NumTypes_004a2978);
  }
  else {
    uVar3 = 0;
  }
  *param_2 = 0;
  *param_1 = 0;
  iVar2 = thunk_FUN_004641de(*(undefined4 *)(in_ECX + 0x14),*(undefined4 *)(in_ECX + 0x10));
  sVar1 = *(short *)(iVar2 + 0x16);
  if (param_3 == 4) {
    iVar2 = thunk_FUN_00456b8d(CONCAT22(extraout_var,sVar1));
    if (iVar2 != 0) {
      *param_1 = (int)*(short *)(iVar2 + 4);
      *param_2 = (int)*(short *)(iVar2 + 6);
    }
  }
  else if (param_3 == 5) {
    iVar2 = thunk_FUN_00456bd0((int)sVar1);
    if (iVar2 != 0) {
      *param_1 = (int)*(short *)(iVar2 + 6);
      *param_2 = (int)*(short *)(iVar2 + 8);
    }
  }
  else if (param_3 == 6) {
    iVar2 = thunk_FUN_00456c13(sVar1);
    if (iVar2 != 0) {
      *param_1 = (int)*(short *)(iVar2 + 2);
      *param_2 = (int)*(short *)(iVar2 + 4);
    }
  }
  else {
    thunk_FUN_00414b91(s_C__float_src_pad_cpp_004a29c8,199,s_FALSE_004a29c0,s_Bad_Anim_Type_004a29b0
                       ,param_3,uVar3);
  }
  return;
}
```

---

---

## FUN_004502dc — 0x4502dc

- Classification : internal
- Corps : `0x4502dc–0x450304`
- État : pseudocode obtenu
- Evidence : `ev_8d591588cea4abce308dbbd5f69e34b5c6431010d387034afe228dee1b3385a8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004502dc(void)

{
  int in_ECX;
  undefined4 local_8;
  
  local_8 = 0;
  if (*(int *)(in_ECX + 0x10) == 1) {
    local_8 = *(undefined4 *)(in_ECX + 0x24);
  }
  return local_8;
}
```

---

---

## FUN_00450305 — 0x450305

- Classification : internal
- Corps : `0x450305–0x450359`
- État : pseudocode obtenu
- Evidence : `ev_83275ff82da670ce74e3ad4a2dfd317b20b7b0f0fd6513a33a0d43be184c89d9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00450305(int param_1)

{
  int in_ECX;
  undefined4 local_8;
  
  local_8 = 0;
  if (param_1 == 1) {
    local_8 = (int)*(short *)(in_ECX + 0x28);
  }
  else if (param_1 == 2) {
    local_8 = (int)*(short *)(in_ECX + 0x28);
  }
  else if (param_1 == 3) {
    local_8 = (int)*(short *)(in_ECX + 0x28);
  }
  return local_8;
}
```

---

---

## FUN_0045035a — 0x45035a

- Classification : internal
- Corps : `0x45035a–0x450384`
- État : pseudocode obtenu
- Evidence : `ev_0750d5f8426f4454fa1a2c800d15b998b3764a08743446b9fae29e7309906ecf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0045035a(void)

{
  int in_ECX;
  
  return (in_ECX - (int)(&DAT_005ec640 + *(short *)(in_ECX + 8) * 0x29e8)) / 0x60;
}
```

---

---

## FUN_00450385 — 0x450385

- Classification : internal
- Corps : `0x450385–0x4503bc`
- État : pseudocode obtenu
- Evidence : `ev_b003c4e2130a4f653012f553ad5cdf8222b961d4c5b48c785fd40fdd3404ada2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_00450385(void)

{
  undefined *puVar1;
  int in_ECX;
  
  if (*(short *)(in_ECX + 0x18) == -1) {
    puVar1 = (undefined *)0x0;
  }
  else {
    puVar1 = &DAT_006192b0 + *(short *)(in_ECX + 0x18) * 100 + *(int *)(in_ECX + 0x14) * 0x14a0;
  }
  return puVar1;
}
```

---

---

## FUN_004503bd — 0x4503bd

- Classification : internal
- Corps : `0x4503bd–0x4507c9`
- État : pseudocode obtenu
- Evidence : `ev_4021833f01ea8cc7d3246c1f20291de57002d6bcb3a77b46a31138e8159b824c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40102d` — `thunk_FUN_0045e6d3`
- `0x40119a` — `thunk_FUN_0045ff6d`
- `0x4014e7` — `thunk_FUN_0045035a`
- `0x40181b` — `thunk_FUN_00450978`
- `0x4018b1` — `thunk_FUN_0045f075`
- `0x4018b6` — `thunk_FUN_0045ff3f`
- `0x401adc` — `thunk_FUN_00416a9a`
- `0x401e6a` — `thunk_FUN_0045ffe2`
- `0x401e7e` — `thunk_FUN_0045ff9b`
- `0x402473` — `thunk_FUN_0045fcbe`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004503bd(int param_1,int param_2,int param_3)

{
  undefined *puVar1;
  short sVar2;
  short sVar3;
  undefined4 uVar4;
  int iVar5;
  int in_ECX;
  int iVar6;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined4 uVar7;
  undefined4 local_8;
  
  local_8 = 0;
  iVar6 = (int)*(short *)(in_ECX + 8);
  if (param_1 == 1) {
    uVar4 = thunk_FUN_0045035a();
    iVar5 = thunk_FUN_0045ff3f(CONCAT22(extraout_var_00,*(undefined2 *)(in_ECX + 8)),uVar4);
    if ((iVar5 != 0) && (param_2 == 1)) {
      *(short *)(in_ECX + 0x34) = *(short *)(in_ECX + 0x34) + 1;
      sVar2 = *(short *)(in_ECX + 0x34);
      sVar3 = thunk_FUN_00450978();
      if (sVar3 <= sVar2) {
        uVar4 = thunk_FUN_0045035a();
        thunk_FUN_0045ff9b(*(undefined2 *)(in_ECX + 8),uVar4);
      }
      return 1;
    }
    if (*(int *)(in_ECX + 0x10) == 0x28) {
      uVar4 = thunk_FUN_0045035a();
      iVar5 = thunk_FUN_0045ff6d(*(undefined2 *)(in_ECX + 8),uVar4);
      if ((iVar5 != 0) && (param_2 == 1)) {
        uVar7 = 1;
        uVar4 = thunk_FUN_0045035a(1);
        iVar6 = thunk_FUN_0045fcbe(CONCAT22(extraout_var_01,*(undefined2 *)(in_ECX + 8)),uVar4,uVar7
                                  );
        *(short *)(iVar6 + 8) = *(short *)(iVar6 + 8) + 1;
        if (*(short *)(iVar6 + 8) == 10) {
          *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 0x800 << ((byte)param_3 & 0x1f);
          uVar4 = thunk_FUN_0045035a();
          thunk_FUN_0045ffe2(CONCAT22(extraout_var,*(undefined2 *)(in_ECX + 8)),uVar4);
          thunk_FUN_0045e6d3((int)*(short *)(in_ECX + 8));
        }
        return 1;
      }
    }
    *(short *)(in_ECX + 0x28) = *(short *)(in_ECX + 0x28) + (short)param_2;
    local_8 = 1;
  }
  else if (param_1 == 2) {
    *(short *)(in_ECX + 0x2a) = *(short *)(in_ECX + 0x2a) + (short)param_2;
    local_8 = 1;
  }
  else if (param_1 == 3) {
    *(short *)(in_ECX + 0x2c) = *(short *)(in_ECX + 0x2c) + (short)param_2;
    local_8 = 1;
  }
  switch(*(undefined4 *)(in_ECX + 0x10)) {
  case 0:
    if (*(int *)(in_ECX + 4) == 0) {
      if (param_1 == 1) {
        *(undefined4 *)(in_ECX + 0x10) = 1;
        *(undefined4 *)(in_ECX + 0x24) = 1;
        if (*(int *)(in_ECX + 0x14) == -1) {
          *(int *)(in_ECX + 0x14) = param_3;
        }
        local_8 = 1;
      }
      else if ((4 < param_1) && (param_1 < 0x22)) {
        *(undefined4 *)(in_ECX + 0x10) = 1;
        *(int *)(in_ECX + 0x24) = param_1;
        local_8 = 1;
      }
    }
    break;
  case 1:
    if ((param_1 == 1) && (*(int *)(in_ECX + 0x24) == 1)) {
      local_8 = 1;
    }
    break;
  case 2:
    if ((param_1 == 5) && ((*(uint *)(in_ECX + 0x1c) & 4) == 0)) {
      *(undefined2 *)(in_ECX + 0x2c) = (undefined2)param_3;
      *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 4;
      *(undefined2 *)(in_ECX + 0x40) = 0;
      local_8 = 1;
    }
    else {
      thunk_FUN_0045f075(param_1,1);
    }
    break;
  case 3:
    param_1 = param_1 - ((short)(&DAT_005eebf8)[*(short *)(in_ECX + 8) * 0x14f4] * 2 + 6);
    if (param_1 == *(short *)(in_ECX + 0x4a)) {
      *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 1;
      puVar1 = &DAT_005ec640 + (short)(&DAT_005eebe8)[iVar6 * 0x14f4] * 0x60 + iVar6 * 0x29e8;
      *(ushort *)(puVar1 + 0x4a) =
           *(ushort *)(puVar1 + 0x4a) | (ushort)(1 << ((byte)param_1 & 0x1f));
      if ((*(ushort *)(puVar1 + 0x4a) & 3) == 3) {
        *(uint *)(puVar1 + 0x1c) = *(uint *)(puVar1 + 0x1c) | 1;
        (&DAT_005eebe4)[iVar6 * 0xa7a] = 1;
        *(ushort *)(&DAT_00619242 + param_3 * 0x14a0) =
             *(ushort *)(&DAT_00619242 + param_3 * 0x14a0) |
             (ushort)(1 << ((byte)*(undefined2 *)(in_ECX + 8) & 0x1f));
        thunk_FUN_00416a9a(4,puVar1);
      }
      local_8 = 1;
    }
    break;
  case 0x2a:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
  case 0x30:
    if ((4 < param_1) && (param_1 < 0x22)) {
      thunk_FUN_0045f075(param_1,1);
      local_8 = 1;
    }
  }
  return local_8;
}
```

---

---

## FUN_00450817 — 0x450817

- Classification : internal
- Corps : `0x450817–0x450846`
- État : pseudocode obtenu
- Evidence : `ev_9a6d23d093a5837771804321af0acca030bfce44366c3a09b7fe882e8732b296`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40115e` — `thunk_FUN_00450847`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00450817(undefined2 param_1)

{
  undefined4 uVar1;
  int in_ECX;
  
  if ((*(int *)(in_ECX + 0x10) < 0x17) || (0x24 < *(int *)(in_ECX + 0x10))) {
    uVar1 = thunk_FUN_00450847(param_1);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
```

---

# 0017_batch_0013 — détails (2/6)

## FUN_0045f5c5 — 0x45f5c5

- Classification : internal
- Corps : `0x45f5c5–0x45f754`
- État : pseudocode obtenu
- Evidence : `ev_b8ac2fd034c03491f78284865a603e7dda1ce800bc85e544b13add76dde36154`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40135c` — `thunk_FUN_00452e2b`
- `0x4014e7` — `thunk_FUN_0045035a`
- `0x401537` — `thunk_FUN_0045343b`
- `0x4017bc` — `thunk_FUN_0045f807`
- `0x4019b5` — `thunk_FUN_0046562b`
- `0x401c94` — `thunk_FUN_0045f2a1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045f5c5(undefined *param_1)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int iVar3;
  int in_ECX;
  short local_20 [2];
  short local_1c [2];
  short local_18 [2];
  int local_14;
  undefined4 *local_10;
  int local_c;
  undefined *local_8;
  
  if (*(int *)(in_ECX + 0x13c0) == 0) {
    uVar2 = 0;
  }
  else {
    local_8 = &DAT_005ec640 +
              *(short *)(in_ECX + 0x13bc) * 0x60 + *(short *)(in_ECX + 0x13ba) * 0x29e8;
    iVar3 = thunk_FUN_0045343b(local_8);
    if (iVar3 == 0) {
      uVar2 = 0;
    }
    else {
      if (*(int *)(param_1 + 0x10) == 0x2a) {
        *(undefined2 *)(in_ECX + 0x13c8) = *(undefined2 *)(param_1 + 8);
        uVar1 = thunk_FUN_0045035a();
        *(undefined2 *)(in_ECX + 0x13ca) = uVar1;
        if (local_8 != param_1) {
          local_c = (in_ECX + -0x6191b8) / 0x14a0;
          iVar3 = thunk_FUN_0046562b(local_c,8);
          if (iVar3 != 0) {
            iVar3 = DAT_00618fb4 * 0x4c;
            local_10 = &DAT_006137b8 + DAT_00618fb4 * 0x13;
            *(undefined2 *)(&DAT_006137f8 + iVar3) = *(undefined2 *)(in_ECX + 0x13c8);
            *(undefined4 *)(&DAT_006137f4 + iVar3) = 9;
            thunk_FUN_0045f807();
            uVar1 = thunk_FUN_00452e2b();
            *(undefined2 *)((int)local_10 + 0x42) = uVar1;
            *(undefined2 *)((int)local_10 + 0x46) = 0;
            local_10[0xb] = 0;
          }
        }
      }
      if (local_8 == param_1) {
        local_14 = thunk_FUN_0045f807();
        if (local_14 != 0) {
          thunk_FUN_0045f2a1(local_8,0,local_20,local_1c,local_18);
          *(short *)(local_14 + 0x28) = *(short *)(local_14 + 0x28) + local_20[0];
          *(short *)(local_14 + 0x2a) = *(short *)(local_14 + 0x2a) + local_1c[0];
          *(short *)(local_14 + 0x2c) = *(short *)(local_14 + 0x2c) + local_18[0];
        }
      }
      *(undefined4 *)(in_ECX + 0x13c0) = 0;
      uVar2 = 1;
    }
  }
  return uVar2;
}
```

---

## FUN_0045f755 — 0x45f755

- Classification : internal
- Corps : `0x45f755–0x45f806`
- État : pseudocode obtenu
- Evidence : `ev_496949b47dee3d4727400b7477adbe928fd66cfad4a0581f206561682a8fd971`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a4640` — "resource >= 0 && resource <= 2"
- `0x4a4660` — "C:\\float\\src\\tribe.cpp"
- `0x4a4678` — "mode >= -1 && mode <= 2"
- `0x4a4690` — "C:\\float\\src\\tribe.cpp"

### Pseudocode Ghidra

```c
void FUN_0045f755(short param_1,short param_2)

{
  int in_ECX;
  
  if ((param_1 < 0) || (2 < param_1)) {
    thunk_FUN_00414b64(s_C__float_src_tribe_cpp_004a4660,0x267,
                       s_resource_>__0____resource_<__2_004a4640);
  }
  if ((param_2 < -1) || (2 < param_2)) {
    thunk_FUN_00414b64(s_C__float_src_tribe_cpp_004a4690,0x268,s_mode_>___1____mode_<__2_004a4678);
  }
  if (param_2 == -1) {
    param_2 = (short)((*(short *)(in_ECX + 0x13d0 + param_1 * 2) + 1) % 3);
  }
  *(short *)(in_ECX + 0x13d0 + param_1 * 2) = param_2;
  return;
}
```

---

## FUN_0045f807 — 0x45f807

- Classification : internal
- Corps : `0x45f807–0x45f848`
- État : pseudocode obtenu
- Evidence : `ev_593f8a710f1ed28f08907d6644367309eb942d46a247531b989779fa3525c71f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_0045f807(void)

{
  undefined *puVar1;
  int in_ECX;
  
  if (*(short *)(in_ECX + 0x13c8) == -1) {
    puVar1 = (undefined *)0x0;
  }
  else {
    puVar1 = &DAT_005ec640 +
             *(short *)(in_ECX + 0x13ca) * 0x60 + *(short *)(in_ECX + 0x13c8) * 0x29e8;
  }
  return puVar1;
}
```

---

## FUN_0045f849 — 0x45f849

- Classification : internal
- Corps : `0x45f849–0x45fb6e`
- État : pseudocode obtenu
- Evidence : `ev_616dd7a915a8b60eba529fd43190c36b33a93b10a6fad251eaba99fe25fec3c9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4019b5` — `thunk_FUN_0046562b`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402153` — `thunk_FUN_0045f0cd`

### Chaînes référencées

- `0x4a46a8` — "totalscore&&badge&&islescore&&diffscore&&glyphscore&& tribe_pop_score&&phys_score&&snat_score&&ethr_score&&natr_score&&tribe_loss_deduct"
- `0x4a4734` — "C:\\float\\src\\tribe.cpp"

### Pseudocode Ghidra

```c
void FUN_0045f849(int *param_1,int *param_2,int *param_3,int *param_4,int *param_5,int *param_6,
                 int *param_7,int *param_8,int *param_9,int *param_10,int *param_11,int *param_12)

{
  int iVar1;
  int in_ECX;
  undefined4 uVar2;
  int local_48;
  int local_40;
  int local_3c [4];
  short local_2c [6];
  int local_20;
  int local_1c;
  int local_18;
  int local_14 [4];
  
  if ((((((param_1 == (int *)0x0) || (param_2 == (int *)0x0)) || (param_3 == (int *)0x0)) ||
       ((param_4 == (int *)0x0 || (param_5 == (int *)0x0)))) ||
      ((param_7 == (int *)0x0 || ((param_9 == (int *)0x0 || (param_10 == (int *)0x0)))))) ||
     ((param_11 == (int *)0x0 || ((param_12 == (int *)0x0 || (param_8 == (int *)0x0)))))) {
    uVar2 = thunk_FUN_00414b64(s_C__float_src_tribe_cpp_004a4734,0x2aa,
                               s_totalscore__badge__islescore__di_004a46a8);
  }
  else {
    uVar2 = 0;
  }
  local_48 = DAT_004bf11c;
  if (DAT_004bf11c < 0) {
    local_48 = 0;
  }
  if (4 < local_48) {
    local_48 = 4;
  }
  *param_4 = (int)(local_48 * 200 + (local_48 * 200 >> 0x1f & 3U)) >> 2;
  local_1c = 0;
  for (local_40 = 0; local_40 < (int)(uint)DAT_006136b0; local_40 = local_40 + 1) {
    if (*(int *)(&DAT_005eebc4 + ((in_ECX + -0x6191b8) / 0x14a0) * 4 + local_40 * 0x29e8) != 0) {
      local_1c = local_1c + 1;
    }
  }
  *param_6 = local_1c + -1;
  *param_3 = (local_1c * 100) / 0xe;
  local_1c = thunk_FUN_0045f0cd(uVar2);
  *param_5 = (local_1c * 200) / 0xe;
  iVar1 = thunk_FUN_0046562b((in_ECX + -0x6191b8) / 0x14a0,0xffffffff);
  if (iVar1 < 0x65) {
    *param_7 = (iVar1 * 100) / 100;
  }
  else {
    *param_7 = 100;
  }
  local_14[0] = 0x1a4;
  local_14[1] = 300;
  local_14[2] = 0x1e0;
  local_14[3] = 600;
  local_20 = (in_ECX + -0x6191b8) / 0x14a0;
  for (local_40 = 0; local_40 < 4; local_40 = local_40 + 1) {
    local_3c[local_20] = local_14[local_40];
    local_20 = local_20 + 1;
    if (3 < local_20) {
      local_20 = 0;
    }
  }
  for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1) {
    local_2c[local_18] =
         *(short *)(in_ECX + 0x1480 + local_18 * 4) + *(short *)(in_ECX + 0x1482 + local_18 * 4);
  }
  *param_9 = (local_2c[0] * local_3c[0]) / 200;
  *param_10 = (local_2c[1] * local_3c[1]) / 200;
  *param_11 = (local_2c[2] * local_3c[2]) / 200;
  *param_12 = (local_2c[3] * local_3c[3]) / 200;
  *param_8 = (*(short *)(in_ECX + 0x1498) * 500) / 0x118;
  *param_1 = (*param_4 + *param_3 + *param_5 + *param_7 + *param_9 + *param_10 + *param_11 +
             *param_12) - *param_8;
  if (*param_1 < 0) {
    *param_1 = 0;
  }
  *param_2 = (*param_1 * 10) / 0x4b0;
  if (*param_2 < 0) {
    *param_2 = 0;
  }
  if (9 < *param_2) {
    *param_2 = 9;
  }
  return;
}
```

---

## FUN_0045fb6f — 0x45fb6f

- Classification : internal
- Corps : `0x45fb6f–0x45fcbd`
- État : pseudocode obtenu
- Evidence : `ev_773b697a9733f2af54299261e5decab66b31c9e02a7c738831cb7827c01b06d6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045fb6f(short param_1)

{
  int in_ECX;
  int local_10;
  int local_c;
  int local_8;
  
  for (local_8 = 0; local_8 < 3; local_8 = local_8 + 1) {
    if (*(short *)(in_ECX + 0x13d6 + local_8 * 2) == param_1) {
      *(undefined2 *)(in_ECX + 0x13d6 + local_8 * 2) = 0xffff;
      *(undefined2 *)(in_ECX + 0x13d0 + local_8 * 2) = 1;
      return;
    }
  }
  local_c = in_ECX + 0x13dc;
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    if (*(short *)(local_c + 6) == param_1) {
      *(undefined2 *)(local_c + 6) = 0xffff;
      return;
    }
    local_c = local_c + 10;
  }
  local_10 = in_ECX + 0xf8;
  local_8 = 0;
  do {
    if (0x2f < local_8) {
      return;
    }
    if (*(short *)(local_10 + 2) != -1) {
      if (*(short *)(local_10 + 0x4e) == param_1) {
        *(undefined2 *)(local_10 + 0x4e) = 0xffff;
        return;
      }
      if (*(short *)(local_10 + 0x52) == param_1) {
        *(undefined2 *)(local_10 + 0x52) = 0xffff;
        *(undefined4 *)(local_10 + 0x58) = 0;
        return;
      }
      if (*(short *)(local_10 + 0x54) == param_1) {
        *(undefined2 *)(local_10 + 0x54) = 0xffff;
        *(undefined4 *)(local_10 + 0x5c) = 0;
        return;
      }
    }
    local_8 = local_8 + 1;
    local_10 = local_10 + 100;
  } while( true );
}
```

---

## FUN_0045fcbe — 0x45fcbe

- Classification : internal
- Corps : `0x45fcbe–0x45fd42`
- État : pseudocode obtenu
- Evidence : `ev_afaae087c995960b95bac49d0b81ecd2a64a16900956fcd5ecccd0de8c452fb8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
short * FUN_0045fcbe(short param_1,short param_2,short param_3)

{
  int in_ECX;
  short *local_c;
  int local_8;
  
  local_c = (short *)(in_ECX + 0x13dc);
  local_8 = 0;
  do {
    if (0xf < local_8) {
      return (short *)0x0;
    }
    if (((local_c[3] != -1) && (param_1 == *local_c)) && (param_2 == local_c[1])) {
      if (param_3 == -1) {
        return local_c;
      }
      if (param_3 == local_c[2]) {
        return local_c;
      }
    }
    local_8 = local_8 + 1;
    local_c = local_c + 5;
  } while( true );
}
```

---

## FUN_0045fd43 — 0x45fd43

- Classification : internal
- Corps : `0x45fd43–0x45fd90`
- État : pseudocode obtenu
- Evidence : `ev_4de9351dbfc6f12d3dcb476a9f88b030204f9d20cb73188b20e7072c516765e5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0045fd43(void)

{
  int in_ECX;
  int local_c;
  int local_8;
  
  local_c = in_ECX + 0x13dc;
  local_8 = 0;
  while( true ) {
    if (0xf < local_8) {
      return 0;
    }
    if (*(short *)(local_c + 6) == -1) break;
    local_8 = local_8 + 1;
    local_c = local_c + 10;
  }
  return local_c;
}
```

---

## FUN_0045fd91 — 0x45fd91

- Classification : internal
- Corps : `0x45fd91–0x45fe61`
- État : pseudocode obtenu
- Evidence : `ev_fb62ac94437aa75616a4b251164628e38b8afc98f5d1c80b95f5eec853a4372c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401686` — `thunk_FUN_004666c9`
- `0x4018b6` — `thunk_FUN_0045ff3f`
- `0x401b36` — `thunk_FUN_0045fd43`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a4750` — "C:\\float\\src\\tribe.cpp"

### Pseudocode Ghidra

```c
void FUN_0045fd91(short param_1,short param_2)

{
  short sVar1;
  int iVar2;
  short *psVar3;
  int in_ECX;
  
  iVar2 = thunk_FUN_0045ff3f(CONCAT22((short)((uint)(&DAT_005ec640 +
                                                    param_2 * 0x60 + param_1 * 0x29e8) >> 0x10),
                                      param_1),
                             CONCAT22((short)((uint)(param_2 * 0x60) >> 0x10),param_2));
  if (iVar2 == 0) {
    psVar3 = (short *)thunk_FUN_0045fd43();
    if (psVar3 == (short *)0x0) {
      thunk_FUN_00414b64(s_C__float_src_tribe_cpp_004a4750,0x3dd,&DAT_004a474c);
    }
    *psVar3 = param_1;
    psVar3[1] = param_2;
    psVar3[2] = 0;
    sVar1 = thunk_FUN_004666c9(&DAT_005ec640 + param_2 * 0x60 + param_1 * 0x29e8,1,
                               (in_ECX + -0x6191b8) / 0x14a0);
    psVar3[3] = sVar1;
  }
  return;
}
```

---

## FUN_0045fe62 — 0x45fe62

- Classification : internal
- Corps : `0x45fe62–0x45ff3e`
- État : pseudocode obtenu
- Evidence : `ev_c338e3603cb1f16d6aebc12bfd91c30ca71ad40542e27bd6a47b17fc4a943702`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119a` — `thunk_FUN_0045ff6d`
- `0x401361` — `thunk_FUN_00452bc5`
- `0x401686` — `thunk_FUN_004666c9`
- `0x401b36` — `thunk_FUN_0045fd43`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a476c` — "C:\\float\\src\\tribe.cpp"

### Pseudocode Ghidra

```c
void FUN_0045fe62(short param_1,short param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  int in_ECX;
  undefined2 extraout_var;
  
  iVar2 = (in_ECX + -0x6191b8) / 0x14a0;
  iVar3 = thunk_FUN_00452bc5(iVar2);
  if ((iVar3 != 0) &&
     (iVar3 = thunk_FUN_0045ff6d(CONCAT22(extraout_var,param_1),param_2), iVar3 == 0)) {
    psVar4 = (short *)thunk_FUN_0045fd43();
    if (psVar4 == (short *)0x0) {
      thunk_FUN_00414b64(s_C__float_src_tribe_cpp_004a476c,0x3f2,&DAT_004a4768);
    }
    *psVar4 = param_1;
    psVar4[1] = param_2;
    psVar4[2] = 1;
    sVar1 = thunk_FUN_004666c9(&DAT_005ec640 + param_2 * 0x60 + param_1 * 0x29e8,1,iVar2);
    psVar4[3] = sVar1;
    psVar4[4] = 0;
  }
  return;
}
```

---

## FUN_0045ff3f — 0x45ff3f

- Classification : internal
- Corps : `0x45ff3f–0x45ff6c`
- État : pseudocode obtenu
- Evidence : `ev_3564f6a3ff410c8b9827ae53e16e94f18109166c4431f61e8f7a9daa07b8a95e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402473` — `thunk_FUN_0045fcbe`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_0045ff3f(undefined2 param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = thunk_FUN_0045fcbe(param_1,param_2,0);
  return iVar1 != 0;
}
```

---

## FUN_0045ff6d — 0x45ff6d

- Classification : internal
- Corps : `0x45ff6d–0x45ff9a`
- État : pseudocode obtenu
- Evidence : `ev_526357e2478af97646bf23f3df2a0f8d7ce122477c3dd96420a06c777a322653`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402473` — `thunk_FUN_0045fcbe`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_0045ff6d(undefined2 param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = thunk_FUN_0045fcbe(param_1,param_2,1);
  return iVar1 != 0;
}
```

---

## FUN_0045ff9b — 0x45ff9b

- Classification : internal
- Corps : `0x45ff9b–0x45ffe1`
- État : pseudocode obtenu
- Evidence : `ev_4b9248525d606beed73c93adae0abde6ddea331c828e880cbdfebfc67903bbab`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4020b3` — `thunk_FUN_00466533`
- `0x402473` — `thunk_FUN_0045fcbe`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045ff9b(undefined2 param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = thunk_FUN_0045fcbe(param_1,param_2,0);
  if (iVar1 != 0) {
    thunk_FUN_00466533((int)*(short *)(iVar1 + 6));
    *(undefined2 *)(iVar1 + 6) = 0xffff;
  }
  return;
}
```

---

## FUN_0045ffe2 — 0x45ffe2

- Classification : internal
- Corps : `0x45ffe2–0x460028`
- État : pseudocode obtenu
- Evidence : `ev_7d2571f143ee8ad7299121d3d6dd5c1e2a8284793e44c8ebaa2e8de2e3d44779`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4020b3` — `thunk_FUN_00466533`
- `0x402473` — `thunk_FUN_0045fcbe`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045ffe2(undefined2 param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = thunk_FUN_0045fcbe(param_1,param_2,1);
  if (iVar1 != 0) {
    thunk_FUN_00466533((int)*(short *)(iVar1 + 6));
    *(undefined2 *)(iVar1 + 6) = 0xffff;
  }
  return;
}
```

---

## FUN_00460029 — 0x460029

- Classification : internal
- Corps : `0x460029–0x460071`
- État : pseudocode obtenu
- Evidence : `ev_eadb172927cba3906ffa9c456a1a4d0bc60a645fe530336147da8f8026ff2d26`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4020b3` — `thunk_FUN_00466533`
- `0x402473` — `thunk_FUN_0045fcbe`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00460029(undefined2 param_1,undefined2 param_2)

{
  int iVar1;
  
  while( true ) {
    iVar1 = thunk_FUN_0045fcbe(param_1,param_2,0xffffffff);
    if (iVar1 == 0) break;
    thunk_FUN_00466533((int)*(short *)(iVar1 + 6));
    *(undefined2 *)(iVar1 + 6) = 0xffff;
  }
  return;
}
```

---

## FUN_00460072 — 0x460072

- Classification : internal
- Corps : `0x460072–0x460333`
- État : pseudocode obtenu
- Evidence : `ev_1d0bd9feec2d7550ea50129522ad783374e97af92bb6dd9bebd24510c185aedf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014bf` — `thunk_FUN_00467260`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a4784` — "featloc->mItem == PIT_IslandFeature"
- `0x4a47a8` — "C:\\float\\src\\tribe.cpp"

### Pseudocode Ghidra

```c
void FUN_00460072(void)

{
  bool bVar1;
  undefined1 *puVar2;
  int in_ECX;
  int iVar3;
  uint local_2c;
  int local_20 [2];
  undefined1 *local_18;
  int local_14;
  undefined1 *local_10;
  int local_c;
  int local_8;
  
  for (local_8 = 0; local_8 < 0xe; local_8 = local_8 + 1) {
    if (((int)*(short *)(in_ECX + 0x8a) & 1 << ((byte)local_8 & 0x1f)) != 0) {
      local_18 = &DAT_005ec218;
      for (local_14 = 0; puVar2 = local_18, local_14 < (int)(uint)DAT_006136b0;
          local_14 = local_14 + 1) {
        if (*(short *)(local_18 + 0x29e0) == local_8) {
          *(undefined4 *)(local_18 + 0x29cc) = 0;
          iVar3 = *(short *)(local_18 + 0x29d0) * 0x60;
          if (*(int *)(local_18 + iVar3 + 0x438) != 4) {
            thunk_FUN_00414b64(s_C__float_src_tribe_cpp_004a47a8,0x453,
                               s_featloc_>mItem____PIT_IslandFeat_004a4784);
          }
          *(undefined2 *)(puVar2 + iVar3 + 0x472) = 0;
          *(uint *)(puVar2 + iVar3 + 0x444) = *(uint *)(puVar2 + iVar3 + 0x444) & 0xfffffffe;
          local_20[0] = 0;
          local_20[1] = 0;
          while ((local_20[0] == 0 || (local_20[1] == 0))) {
            iVar3 = thunk_FUN_00467260((int)*(short *)(local_18 + 0x29a8));
            iVar3 = iVar3 * 0x60;
            if (((*(int *)(local_18 + iVar3 + 0x42c) == 0) &&
                ((*(int *)(local_18 + iVar3 + 0x44c) == 0 &&
                 (*(int *)(local_18 + iVar3 + 0x43c) == -1)))) ||
               (*(int *)(local_18 + iVar3 + 0x43c) == 4)) {
              local_2c = (uint)(local_20[0] != 0);
              *(uint *)(local_18 + iVar3 + 0x44c) = local_2c + 6 + local_8 * 2;
              if (*(int *)(local_18 + iVar3 + 0x438) == 0) {
                *(undefined4 *)(local_18 + iVar3 + 0x438) = 1;
              }
              local_20[local_2c] = 1;
            }
          }
        }
        local_18 = local_18 + 0x29e8;
      }
      *(ushort *)(in_ECX + 0x8a) =
           *(ushort *)(in_ECX + 0x8a) & ~(ushort)(1 << ((byte)local_8 & 0x1f));
    }
  }
  local_10 = &DAT_005ec218 + ((in_ECX + -0x6191b8) / 0x14a0) * 0x29e8;
  for (local_c = 5; local_c < 0x22; local_c = local_c + 1) {
    while (*(short *)(in_ECX + 0x44 + local_c * 2) != 0) {
      bVar1 = false;
      while (!bVar1) {
        iVar3 = thunk_FUN_00467260((int)*(short *)(local_10 + 0x29a8));
        iVar3 = iVar3 * 0x60;
        if ((((*(int *)(local_10 + iVar3 + 0x42c) == 0) && (*(int *)(local_10 + iVar3 + 0x44c) == 0)
             ) && (*(int *)(local_10 + iVar3 + 0x43c) == -1)) ||
           (*(int *)(local_10 + iVar3 + 0x43c) == 4)) {
          *(int *)(local_10 + iVar3 + 0x44c) = local_c;
          if (*(int *)(local_10 + iVar3 + 0x438) == 0) {
            *(undefined4 *)(local_10 + iVar3 + 0x438) = 1;
          }
          bVar1 = true;
        }
      }
      *(short *)(in_ECX + 0x44 + local_c * 2) = *(short *)(in_ECX + 0x44 + local_c * 2) + -1;
    }
  }
  return;
}
```

---

## FUN_00460334 — 0x460334

- Classification : internal
- Corps : `0x460334–0x4603e9`
- État : pseudocode obtenu
- Evidence : `ev_3801e674478efa33932d2ff7589215bbb82a0b7afd627721ab0bef88b456a7f7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401771` — `thunk_FUN_0045e660`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401cee` — `thunk_FUN_0040fd80`
- `0x4022d4` — `thunk_FUN_0045e6b1`
- `0x478410` — `FUN_00478410`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00460334(undefined4 param_1,int param_2)

{
  undefined4 *extraout_ECX;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_14b0 [1315];
  undefined4 uStack_24;
  undefined4 *puStack_20;
  undefined4 uStack_1c;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491bfc;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  FUN_00478410();
  uStack_1c = 0x460369;
  thunk_FUN_0045e660();
  local_8 = 0;
  if (param_2 == 0) {
    puVar2 = extraout_ECX;
    puVar3 = local_14b0;
    for (iVar1 = 0x528; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    uStack_1c = 0x14a0;
    puStack_20 = local_14b0;
    uStack_24 = 0x4603c6;
    thunk_FUN_0040fd80();
  }
  else {
    uStack_1c = 0x14a0;
    puStack_20 = local_14b0;
    uStack_24 = 0x46038a;
    thunk_FUN_0040fc15();
    puVar2 = local_14b0;
    puVar3 = extraout_ECX;
    for (iVar1 = 0x528; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  local_8 = 0xffffffff;
  uStack_1c = 0x4603d8;
  thunk_FUN_0045e6b1();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

## FUN_004603ea — 0x4603ea

- Classification : internal
- Corps : `0x4603ea–0x46044c`
- État : pseudocode obtenu
- Evidence : `ev_3d067f239a0c4360d132239edf0cb2b0d9080004e4fe8a8f080716927ecbdb77`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401771` — `thunk_FUN_0045e660`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004603ea(void)

{
  int in_ECX;
  undefined4 local_8;
  
  thunk_FUN_0045e660();
  *(undefined4 *)(in_ECX + 0x3c) = 0;
  *(undefined4 *)(in_ECX + 0x40) = 0;
  *(undefined4 *)(in_ECX + 0x14a0) = 1;
  for (local_8 = 0; local_8 < 0xf; local_8 = local_8 + 1) {
    *(undefined2 *)(in_ECX + 0x15f6 + local_8 * 2) = 0;
  }
  return in_ECX;
}
```

---

## FUN_0046044d — 0x46044d

- Classification : internal
- Corps : `0x46044d–0x46045f`
- État : pseudocode obtenu
- Evidence : `ev_c8b37da8f46285907c11986d613161dd207376da391b3f2730efa85023ae6950`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4022d4` — `thunk_FUN_0045e6b1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046044d(void)

{
  thunk_FUN_0045e6b1();
  return;
}
```

---

## FUN_00460460 — 0x460460

- Classification : internal
- Corps : `0x460460–0x460988`
- État : pseudocode obtenu
- Evidence : `ev_67e9f6f06b6bb555f4b8a61a0b1d4b1d8fd8ae6c5a090b47499f0c439d80e029`
- Note de portée : cette fonction scanne les enregistrements d'emplacements d'une île (stride `0x60`) et leurs champs propriétaire/type. Elle maintient des compteurs insulaires de type 4, compte les floaters Leviathan autres que le sous-type 9, puis écrit l'intervalle `+0x45a` dans les enregistrements de sites sélectionnés. `+0x45a` appartient ici à l'enregistrement d'emplacement, pas au floater. Elle est appelée après des changements Leviathan et par un recalcul global ; le lecteur du temporisateur et le processus complet de production ne sont pas établis. Evidence de la relecture `ev_f6fad36a24d0df23600189218f8f97cf25c8ae1078856cf1f0526c0fd092aedd`.
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401131` — `thunk_FUN_00412cac`
- `0x40186b` — `thunk_FUN_004656d6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00460460(int param_1)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int in_ECX;
  short local_4c;
  short local_44;
  undefined2 local_40;
  int local_3c;
  undefined1 *local_38;
  short local_34;
  int local_2c;
  short asStack_28 [6];
  int local_1c;
  short local_18;
  int local_14;
  undefined1 *local_10;
  int local_c;
  uint local_8;
  
  local_14 = param_1;
  local_8 = param_1 + 1;
  if (param_1 == -1) {
    local_14 = 0;
    local_8 = (uint)DAT_006136b0;
  }
  local_10 = &DAT_005ec218 + local_14 * 0x29e8;
  local_c = local_14;
  do {
    if ((int)local_8 <= local_c) {
      return;
    }
    local_4c = 0;
    local_34 = 0;
    *(undefined2 *)(in_ECX + 0x15d8 + local_c * 2) = 0;
    local_2c = 1;
    bVar2 = false;
    local_38 = local_10 + 0x428;
    for (local_3c = 0; local_3c < *(short *)(local_10 + 0x29a8); local_3c = local_3c + 1) {
      if ((*(int *)(local_38 + 4) == 1) && (local_4c < 6)) {
        local_4c = local_4c + 1;
        if (*(int *)(local_38 + 0x14) == 4) {
          asStack_28[*(short *)(in_ECX + 0x15d8 + local_c * 2)] = (short)local_3c;
          *(short *)(in_ECX + 0x15d8 + local_c * 2) = *(short *)(in_ECX + 0x15d8 + local_c * 2) + 1;
        }
      }
      else if ((*(int *)(local_38 + 4) == 0) && (*(int *)(local_38 + 0x14) == 4)) {
        local_34 = local_34 + 1;
      }
      else if ((*(int *)(local_38 + 0x14) == -1) ||
              (((*(int *)(local_38 + 0x10) != 0x2a ||
                (iVar3 = thunk_FUN_00412cac(*(undefined4 *)(local_38 + 0x14)), iVar3 == -1)) &&
               ((*(int *)(local_38 + 0x10) < 0x2c || (0x2e < *(int *)(local_38 + 0x10))))))) {
        if ((((*(int *)(local_38 + 0x14) != -1) && (0x24 < *(int *)(local_38 + 0x10))) &&
            (*(int *)(local_38 + 0x10) < 0x36)) &&
           (iVar3 = thunk_FUN_00412cac(*(undefined4 *)(local_38 + 0x14)), iVar3 != -1)) {
          local_2c = 0;
        }
      }
      else {
        local_2c = 0;
        bVar2 = true;
      }
      local_38 = local_38 + 0x60;
    }
    if ((DAT_006191b4 == 0) && (local_c == DAT_006136b0 - 1)) {
      bVar1 = false;
      for (local_3c = 0; local_3c < *(short *)(local_10 + 0x29a8); local_3c = local_3c + 1) {
        if ((0x16 < *(int *)(local_10 + local_3c * 0x60 + 0x438)) &&
           (*(int *)(local_10 + local_3c * 0x60 + 0x438) < 0x25)) {
          bVar1 = true;
          break;
        }
      }
      if (!bVar1) {
        DAT_006191b4 = 2;
      }
    }
    if ((*(int *)(in_ECX + 0x14e8 + local_c * 4) != 0) && (local_2c == 0)) {
      *(undefined4 *)(in_ECX + 0x1524 + local_c * 4) = 0xffffffff;
    }
    *(int *)(in_ECX + 0x14e8 + local_c * 4) = local_2c;
    if (*(short *)(in_ECX + 0x15d8 + local_c * 2) != 0) {
      *(short *)(in_ECX + 0x159c + local_c * 2) =
           local_4c - *(short *)(in_ECX + 0x15d8 + local_c * 2);
      local_44 = (short)((int)(local_c + (local_c >> 0x1f & 3U)) >> 2);
      if (DAT_00618e48 < local_44) {
        local_44 = (short)DAT_00618e48;
      }
      *(short *)(in_ECX + 0x157e + local_c * 2) =
           *(short *)(in_ECX + 0x15d8 + local_c * 2) * (local_44 * 2 + 4) - local_34;
      if (*(short *)(in_ECX + 0x157e + local_c * 2) < 0) {
        *(undefined2 *)(in_ECX + 0x157e + local_c * 2) = 0;
      }
      *(undefined2 *)(in_ECX + 0x15ba + local_c * 2) = 0;
      local_1c = thunk_FUN_004656d6(local_c,0xfffffffe);
      for (local_3c = 0; local_3c < local_1c; local_3c = local_3c + 1) {
        if (((&DAT_006137b8)[(short)(&DAT_00618fb4)[local_3c] * 0x13] == 4) &&
           (*(int *)(&DAT_006137bc + (short)(&DAT_00618fb4)[local_3c] * 0x4c) != 9)) {
          *(short *)(in_ECX + 0x15ba + local_c * 2) = *(short *)(in_ECX + 0x15ba + local_c * 2) + 1;
        }
      }
      iVar3 = *(short *)(in_ECX + 0x15d8 + local_c * 2) + -1;
      if (*(int *)(in_ECX + 0x14e8 + local_c * 4) == 0) {
        if (bVar2) {
          local_18 = *(short *)(&DAT_004a4508 + iVar3 * 2 + DAT_00618e48 * 0xc);
        }
        else {
          local_18 = *(short *)(&DAT_004a44c8 + iVar3 * 2 + DAT_00618e48 * 0xc);
        }
      }
      else {
        local_18 = *(short *)(&DAT_004a4488 + iVar3 * 2 + DAT_00618e48 * 0xc);
      }
      *(short *)(in_ECX + 0x1560 + local_c * 2) =
           local_18 - *(short *)(in_ECX + 0x15ba + local_c * 2);
      local_40 = (undefined2)
                 (((local_44 + DAT_00618e48) * 2 + 10) /
                 (int)*(short *)(in_ECX + 0x15d8 + local_c * 2));
      if (((*(short *)(in_ECX + 0x159c + local_c * 2) == 0) &&
          (*(short *)(in_ECX + 0x157e + local_c * 2) == 0)) &&
         (*(short *)(in_ECX + 0x1560 + local_c * 2) == 0)) {
        local_40 = 0;
      }
      for (local_3c = 0; local_3c < *(short *)(in_ECX + 0x15d8 + local_c * 2);
          local_3c = local_3c + 1) {
        iVar3 = asStack_28[local_3c] * 0x60;
        if (*(int *)(local_10 + iVar3 + 0x438) == 5) {
          *(undefined2 *)(local_10 + iVar3 + 0x45a) = 1;
        }
        else {
          *(undefined2 *)(local_10 + iVar3 + 0x45a) = local_40;
        }
      }
    }
    local_c = local_c + 1;
    local_10 = local_10 + 0x29e8;
  } while( true );
}
```

---


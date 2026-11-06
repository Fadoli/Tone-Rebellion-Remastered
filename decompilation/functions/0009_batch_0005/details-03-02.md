# 0009_batch_0005 — détails (2/2)

## FUN_00415fc6 — 0x415fc6

- Classification : internal
- Corps : `0x415fc6–0x416341`
- État : pseudocode obtenu
- Evidence : `ev_909ac3a901faf4fa2fa52c792b4976d5a40c27cfff4b84cb19ad6d2d2fe61fe8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010d7` — `thunk_FUN_0042003c`
- `0x40130c` — `thunk_FUN_0045575c`
- `0x4013e8` — `thunk_FUN_00415f1e`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x4018cf` — `thunk_FUN_0041ff2e`
- `0x401933` — `thunk_FUN_00464242`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4024be` — `thunk_FUN_004207c2`

### Chaînes référencées

- `0x49c160` — "i<MAX_EFFECTINST"
- `0x49c174` — "C:\\float\\src\\effects.cpp"

### Pseudocode Ghidra

```c
uint FUN_00415fc6(undefined4 *param_1,int param_2,int param_3)

{
  short sVar1;
  int iVar2;
  int in_ECX;
  undefined2 extraout_var;
  short local_28;
  undefined4 local_1c;
  int local_14;
  uint local_10;
  short *local_8;
  
  if (*(short *)(in_ECX + 0x1482) == 0x20) {
    local_10 = 0xffff;
  }
  else {
    local_10 = 0;
    for (local_8 = (short *)(in_ECX + 0x1202); ((int)local_10 < 0x20 && (*local_8 != -1));
        local_8 = local_8 + 10) {
      local_10 = local_10 + 1;
    }
    if (0x1f < (int)local_10) {
      thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c174,0x15f,s_i<MAX_EFFECTINST_0049c160);
    }
    local_8[9] = 0;
    local_14 = 0;
    if (param_2 == 0) {
      iVar2 = thunk_FUN_00464242(*param_1,param_1[1]);
      local_14 = thunk_FUN_0045575c(CONCAT22(extraout_var,*(undefined2 *)(iVar2 + 4)));
      local_8[7] = *(short *)(local_14 + 0x48);
    }
    else {
      local_1c = param_1[1];
      iVar2 = thunk_FUN_004207c2();
      if (iVar2 != 0) {
        local_1c = 0;
      }
      sVar1 = thunk_FUN_0042003c(local_1c);
      sVar1 = thunk_FUN_00415f1e((&PTR_s_phyimp_0049bd58)[sVar1]);
      local_8[7] = sVar1;
    }
    if (local_8[7] == -1) {
      local_10 = 0xffffffff;
    }
    else {
      iVar2 = in_ECX + local_8[7] * 0x30;
      *local_8 = (short)((int)(param_1 + -0x184dee) / 0x4c);
      local_8[1] = *(short *)((int)param_1 + 0x32);
      local_8[4] = *(short *)((int)param_1 + 0xe);
      if (param_2 == 0) {
        local_8[5] = *(short *)(param_1 + 4);
        local_8[6] = *(short *)((int)param_1 + 0x12);
      }
      else {
        sVar1 = thunk_FUN_00467260(0xf);
        local_8[5] = sVar1 + -7;
        sVar1 = thunk_FUN_00467260(0xf);
        local_8[6] = sVar1 + -7;
      }
      local_8[8] = 0;
      local_8[8] = local_8[8] | (ushort)((param_1[7] & 2) != 0);
      local_8[8] = local_8[8] | (param_1[0xb] != 7) - 1 & 2;
      if ((*(int *)(iVar2 + 0xc) == 1) && (local_14 != 0)) {
        if ((local_8[8] & 1U) == 0) {
          local_28 = *(short *)(local_14 + 0x4e);
        }
        else {
          local_28 = -*(short *)(local_14 + 0x4e);
        }
        local_8[5] = local_8[5] + local_28;
        local_8[6] = local_8[6] + *(short *)(local_14 + 0x50);
      }
      if (*(int *)(iVar2 + 0xc) == 2) {
        sVar1 = thunk_FUN_00467260(0x8000);
        local_8[5] = sVar1;
        sVar1 = thunk_FUN_00467260(0x8000);
        local_8[6] = sVar1;
        local_8[2] = 0;
        local_8[3] = 0;
      }
      else {
        if (param_2 == 0) {
          sVar1 = thunk_FUN_0041ff2e();
          local_8[2] = sVar1;
        }
        else {
          local_8[2] = (short)(param_3 / 2);
        }
        if (local_8[2] < 0) {
          local_8[2] = 0;
        }
        if (*(short *)(iVar2 + 0x12) + -1 < (int)local_8[2]) {
          local_8[2] = *(short *)(iVar2 + 0x12) + -1;
        }
        local_8[3] = *(short *)(iVar2 + 0x14 + local_8[2] * 2);
      }
      if ((param_2 == 0) && (local_8[8] = local_8[8] | 8, *(int *)(iVar2 + 0xc) != 4)) {
        local_8[8] = local_8[8] | 0x10;
      }
      *(short *)(in_ECX + 0x1482) = *(short *)(in_ECX + 0x1482) + 1;
      local_10 = local_10 & 0xffff;
    }
  }
  return local_10;
}
```

---

---

## FUN_00416342 — 0x416342

- Classification : internal
- Corps : `0x416342–0x41660a`
- État : pseudocode obtenu
- Evidence : `ev_55e283bb5090275e6ae7b91d806c4588b2fd6009cc466eda1755abd8f34145fa`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013e8` — `thunk_FUN_00415f1e`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x4014e7` — `thunk_FUN_0045035a`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4021ad` — `thunk_FUN_004641de`
- `0x4024c3` — `thunk_FUN_00456bd0`

### Chaînes référencées

- `0x49c190` — "i<MAX_EFFECTINST"
- `0x49c1a4` — "C:\\float\\src\\effects.cpp"

### Pseudocode Ghidra

```c
uint FUN_00416342(short *param_1,int param_2,int param_3)

{
  short sVar1;
  int iVar2;
  int in_ECX;
  undefined4 uVar3;
  uint local_14;
  short *local_c;
  int local_8;
  
  if (*(short *)(in_ECX + 0x1482) == 0x20) {
    local_14 = 0xffff;
  }
  else {
    local_14 = 0;
    for (local_c = (short *)(in_ECX + 0x1202); ((int)local_14 < 0x20 && (*local_c != -1));
        local_c = local_c + 10) {
      local_14 = local_14 + 1;
    }
    if ((int)local_14 < 0x20) {
      uVar3 = 0;
    }
    else {
      uVar3 = thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c1a4,0x1c2,
                                 s_i<MAX_EFFECTINST_0049c190);
    }
    local_c[9] = 0;
    local_8 = 0;
    if (param_2 == 0) {
      iVar2 = thunk_FUN_004641de(*(undefined4 *)(param_1 + 10),*(undefined4 *)(param_1 + 8),uVar3);
      local_8 = thunk_FUN_00456bd0(*(undefined2 *)(iVar2 + 0x16));
      if (local_8 == 0) {
        local_c[7] = -1;
      }
      else {
        local_c[7] = *(short *)(local_8 + 0xe);
      }
    }
    else {
      sVar1 = thunk_FUN_00415f1e((&PTR_s_phyimp_0049bd58)
                                 [(short)((ushort)*(undefined4 *)(param_1 + 8) & 3)]);
      local_c[7] = sVar1;
    }
    if (local_c[7] == -1) {
      local_14 = 0xffffffff;
    }
    else {
      iVar2 = in_ECX + local_c[7] * 0x30;
      sVar1 = thunk_FUN_0045035a();
      *local_c = sVar1;
      local_c[1] = param_1[0x1b];
      local_c[4] = param_1[4];
      local_c[8] = 0;
      local_c[8] = local_c[8] | 4;
      if (param_2 == 0) {
        local_c[5] = *param_1;
        local_c[6] = param_1[1];
        if (local_8 != 0) {
          local_c[5] = local_c[5] + *(short *)(local_8 + 6);
          local_c[6] = local_c[6] + *(short *)(local_8 + 8);
        }
        local_c[2] = 0;
      }
      else {
        sVar1 = thunk_FUN_00467260(0xf);
        local_c[5] = sVar1 + -7;
        sVar1 = thunk_FUN_00467260(0xf);
        local_c[6] = sVar1 + -7;
        local_c[2] = (short)(param_3 / 2);
        if (local_c[2] < 0) {
          local_c[2] = 0;
        }
        if (*(short *)(iVar2 + 0x12) + -1 < (int)local_c[2]) {
          local_c[2] = *(short *)(iVar2 + 0x12) + -1;
        }
      }
      local_c[3] = *(short *)(iVar2 + 0x14 + local_c[2] * 2);
      if ((param_2 == 0) && (local_c[8] = local_c[8] | 8, *(int *)(iVar2 + 0xc) != 4)) {
        local_c[8] = local_c[8] | 0x10;
      }
      *(short *)(in_ECX + 0x1482) = *(short *)(in_ECX + 0x1482) + 1;
      local_14 = local_14 & 0xffff;
    }
  }
  return local_14;
}
```

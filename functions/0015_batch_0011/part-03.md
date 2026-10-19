# 0015_batch_0011 — détails (3/6)

## FUN_0044e77f — 0x44e77f

- Classification : internal
- Corps : `0x44e77f–0x44e9c6`
- État : pseudocode obtenu
- Evidence : `ev_5daea5a48e2013c7f961c54ebc7f59f3634fefaee46c6040bea3c9a16d225acd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472da0` — `FUN_00472da0`
- `0x472db0` — `FUN_00472db0`
- `0x472e90` — `_strlen`
- `0x476e20` — `_strncmp`

### Chaînes référencées

- `0x4a25bc` — "mpTextData"
- `0x4a25c8` — "C:\\float\\src\\newgame.cpp"
- `0x4a25e4` — "newgame.txt"
- `0x4a25f0` — "Couldn't load newgame.txt"
- `0x4a260c` — "FALSE"
- `0x4a2614` — "C:\\float\\src\\newgame.cpp"
- `0x4a2630` — "ENDTEXT"
- `0x4a2640` — "count<8"
- `0x4a2648` — "C:\\float\\src\\newgame.cpp"
- `0x4a2664` — "total_len<4096"
- `0x4a2674` — "C:\\float\\src\\newgame.cpp"

### Pseudocode Ghidra

```c
void FUN_0044e77f(undefined4 param_1)

{
  int iVar1;
  size_t sVar2;
  int in_ECX;
  char local_484 [512];
  int local_284;
  char local_274 [100];
  int local_210;
  int local_20c;
  int local_208;
  char local_204 [512];
  
  *(undefined4 *)(in_ECX + 0x78) = param_1;
  if (*(int *)(in_ECX + 0x78) == 0) {
    thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a25c8,0xbe,s_mpTextData_004a25bc);
  }
  iVar1 = thunk_FUN_0040f419(s_newgame_txt_004a25e4,&DAT_004b28f0,20000);
  if (iVar1 != 0) {
    thunk_FUN_00414ad0(s_Couldn_t_load_newgame_txt_004a25f0);
    thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a2614,0xc4,s_FALSE_004a260c);
  }
  local_20c = 0;
  local_208 = 0;
  while( true ) {
    thunk_FUN_0040f5b3(local_274,1);
    iVar1 = _strncmp(local_274,s_ENDTEXT_004a2630,7);
    if (iVar1 == 0) break;
    local_210 = 0;
    local_484[0] = '\0';
    while (local_210 == 0) {
      thunk_FUN_0040f5b3(local_204,1);
      iVar1 = _strncmp(local_204,&DAT_004a2638,3);
      if (iVar1 == 0) {
        local_210 = 1;
      }
      else {
        FUN_00472db0(local_484,local_204);
        FUN_00472db0(local_484,&DAT_004a263c);
      }
    }
    FUN_00472da0(*(int *)(in_ECX + 0x78) + local_20c,local_484);
    if (7 < local_208) {
      thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a2648,0xe5,s_count<8_004a2640);
    }
    *(undefined2 *)(in_ECX + 0x7c + local_208 * 2) = (undefined2)local_20c;
    local_208 = local_208 + 1;
    sVar2 = _strlen(local_484);
    local_284 = sVar2 + 1;
    local_20c = local_20c + local_284;
    if (0xfff < local_20c) {
      thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a2674,0xea,s_total_len<4096_004a2664);
    }
  }
  return;
}
```

---

## FUN_0044e9c7 — 0x44e9c7

- Classification : internal
- Corps : `0x44e9c7–0x44ebb6`
- État : pseudocode obtenu
- Evidence : `ev_90336bf93e608443b174f85bc4aceb53bdf75a61c92435e761292a6714e3c5fc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401235` — `thunk_FUN_0044ebea`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x4018d9` — `thunk_FUN_0044e77f`
- `0x401c44` — `thunk_FUN_0044e440`
- `0x402491` — `thunk_FUN_0042dd0f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0044e9c7(short param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 uVar3;
  
  switch((int)param_1) {
  case 1:
    *(undefined4 *)(in_ECX + 0x74) = 0xbf;
    *(undefined4 *)(in_ECX + 0x70) = 1;
    DAT_0049f538 = 0xffffffff;
    thunk_FUN_0044e77f(&DAT_005e3c30);
    uVar3 = extraout_var;
    if (DAT_005e4c50 == 0) {
      thunk_FUN_0044e440();
      DAT_005e4c50 = 1;
      uVar3 = extraout_var_00;
    }
    uVar2 = thunk_FUN_004293c6(CONCAT22(uVar3,param_1),param_2,param_3);
    break;
  default:
    uVar2 = thunk_FUN_004293c6(CONCAT22((short)((uint)(param_1 + -1) >> 0x10),param_1),param_2,
                               param_3);
    break;
  case 5:
    switch(param_2) {
    case 0x24:
      if (DAT_004c2b74 != 0) {
        uVar1 = thunk_FUN_0042dd0f(1);
        *(uint *)(in_ECX + 0x74) = uVar1 & 0xff;
      }
      break;
    case 0x25:
      if (DAT_004c2b74 != 0) {
        *(int *)(in_ECX + 0x74) = *(int *)(in_ECX + 0x74) + -1;
        if (*(int *)(in_ECX + 0x74) < 0) {
          *(undefined4 *)(in_ECX + 0x74) = 0;
        }
        if (0xfe < *(int *)(in_ECX + 0x74)) {
          *(undefined4 *)(in_ECX + 0x74) = 0xfe;
        }
      }
      break;
    case 0x26:
      if (DAT_004c2b74 != 0) {
        *(undefined4 *)(in_ECX + 0x74) = 0;
      }
      break;
    case 0x27:
      if (DAT_004c2b74 != 0) {
        *(int *)(in_ECX + 0x74) = *(int *)(in_ECX + 0x74) + 1;
        if (*(int *)(in_ECX + 0x74) < 0) {
          *(undefined4 *)(in_ECX + 0x74) = 0;
        }
        if (0xfe < *(int *)(in_ECX + 0x74)) {
          *(undefined4 *)(in_ECX + 0x74) = 0xfe;
        }
      }
      break;
    case 0x28:
      if (DAT_004c2b74 != 0) {
        *(undefined4 *)(in_ECX + 0x74) = 0xfe;
      }
    }
    *(undefined4 *)(in_ECX + 0x70) = 1;
    uVar2 = 0;
    break;
  case 6:
    uVar2 = thunk_FUN_0044ebea(param_2,param_3);
    break;
  case 0xb:
    *(undefined4 *)(in_ECX + 0x70) = 1;
    uVar2 = thunk_FUN_004293c6(param_1,param_2,param_3);
  }
  return uVar2;
}
```

---

## FUN_0044ebea — 0x44ebea

- Classification : internal
- Corps : `0x44ebea–0x44ec5c`
- État : pseudocode obtenu
- Evidence : `ev_1c56b29ef4733e1eb0bb465727e460ffd1ca105a01dfbc019e26ae0d3e355a8f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401bf4` — `thunk_FUN_0042970c`
- `0x401c53` — `thunk_FUN_0044e4f8`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0044ebea(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = thunk_FUN_0044e4f8(param_1,param_2);
  if (iVar1 == -1) {
    uVar2 = 0;
  }
  else {
    if (iVar1 < 4) {
      thunk_FUN_0042970c(0x3c,iVar1,0);
    }
    else if (iVar1 == 4) {
      thunk_FUN_0042970c(0x37,0,0);
    }
    else if (iVar1 == 5) {
      thunk_FUN_0042970c(0x35,0,0);
    }
    uVar2 = 1;
  }
  return uVar2;
}
```

---

## FUN_0044ec5d — 0x44ec5d

- Classification : internal
- Corps : `0x44ec5d–0x44fa93`
- État : pseudocode obtenu
- Evidence : `ev_4970330fd49b41ee0b1f53394c1d5cf3c12c584a9b208e76d0628c525c1b6566`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401389` — `thunk_FUN_00403a84`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x401677` — `thunk_FUN_0044e48f`
- `0x401712` — `thunk_FUN_004289a7`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401c53` — `thunk_FUN_0044e4f8`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x402234` — `thunk_FUN_0042892d`
- `0x4022fc` — `thunk_FUN_00428baa`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472c6c` — `__ftol`
- `0x474b90` — `FUN_00474b90`
- `0x476ce4` — `FUN_00476ce4`
- `0x477314` — `FUN_00477314`
- `0x477ab4` — `FUN_00477ab4`

### Chaînes référencées

- `0x4a2690` — "EXITNEWGAME"
- `0x4a269c` — "WORLDSIZE"
- `0x4a26a8` — "TRIBE0"
- `0x4a26b0` — "TRIBE1"
- `0x4a26b8` — "TRIBE2"
- `0x4a26c0` — "TRIBE3"
- `0x4a26c8` — "DIFFICULTY"
- `0x4a26d4` — "BEGINGAME"
- `0x4a26e0` — "newback"
- `0x4a26e8` — "newback"
- `0x4a26f0` — "glyphs"
- `0x4a26f8` — "shape"
- `0x4a2700` — "C:\\float\\src\\newgame.cpp"
- `0x4a271c` — "levidiff"
- `0x4a2728` — "shape"
- `0x4a2730` — "C:\\float\\src\\newgame.cpp"
- `0x4a2754` — "C:\\float\\src\\newgame.cpp"
- `0x4a2770` — "newback"
- `0x4a2778` — "ngrealms"
- `0x4a2784` — "shape"
- `0x4a278c` — "C:\\float\\src\\newgame.cpp"
- `0x4a27a8` — "bigfloat"
- `0x4a27b4` — "shape"
- `0x4a27bc` — "C:\\float\\src\\newgame.cpp"

### Pseudocode Ghidra

```c
void FUN_0044ec5d(void)

{
  undefined1 uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int in_ECX;
  int iVar6;
  uint uVar7;
  int *piVar8;
  int *piVar9;
  float10 fVar10;
  undefined4 uVar11;
  undefined8 uVar12;
  int local_7c [5];
  int local_68;
  int local_64;
  int local_60;
  float local_5c;
  int local_58;
  undefined4 local_54;
  int local_50;
  int local_4c;
  int local_48 [7];
  int local_2c;
  int local_28;
  int local_24 [6];
  double local_c;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    DAT_005e4c54 = DAT_005e4c54 + 1;
    if (DAT_005e4c54 % 3 == 0) {
      DAT_005e4c58 = DAT_005e4c58 + 1;
    }
    DAT_0049f538 = -1;
    for (local_48[5] = 0; local_48[5] < 4; local_48[5] = local_48[5] + 1) {
      if ((*(uint *)(&DAT_005e1730 + DAT_004befec * 4) & 1 << ((byte)local_48[5] & 0x1f)) != 0) {
        DAT_0049f538 = local_48[5];
        break;
      }
    }
    local_4c = 0;
    uVar2 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar2;
    uVar12 = 0;
    uVar11 = 0;
    uVar2 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
    thunk_FUN_00404770(in_ECX + 8,uVar2,uVar11,uVar12);
    thunk_FUN_0046c3bc(s_EXITNEWGAME_004a2690,0xb,0,0);
    thunk_FUN_0046c3bc(s_WORLDSIZE_004a269c,0xb,0,0);
    thunk_FUN_0046c3bc(s_TRIBE0_004a26a8,0xb,0,0);
    thunk_FUN_0046c3bc(s_TRIBE1_004a26b0,0xb,0,0);
    thunk_FUN_0046c3bc(s_TRIBE2_004a26b8,0xb,0,0);
    thunk_FUN_0046c3bc(s_TRIBE3_004a26c0,0xb,0,0);
    thunk_FUN_0046c3bc(s_DIFFICULTY_004a26c8,0xb,0,0);
    thunk_FUN_0046c3bc(s_BEGINGAME_004a26d4,0xb,0,0);
    piVar8 = (int *)(in_ECX + 8);
    piVar9 = local_24;
    for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
      *piVar9 = *piVar8;
      piVar8 = piVar8 + 1;
      piVar9 = piVar9 + 1;
    }
    local_4c = thunk_FUN_0040ec89(s_newback_004a26e0,1);
    local_24[1] = 0xd2;
    local_24[2] = 0x82;
    local_24[3] = 0x1ae;
    local_24[4] = 0x15e;
    thunk_FUN_00404770(local_24,local_4c,0,0xffffff2e,0xffffff7e);
    if (DAT_005e4c5c == 0) {
      for (local_50 = 0; local_50 < 3; local_50 = local_50 + 1) {
        if (local_50 == 0) {
          local_54 = 0xffffffce;
        }
        else if (local_50 == 1) {
          local_54 = 0xffffffe2;
        }
        else {
          local_54 = 0xffffffba;
        }
        for (local_58 = 0; local_58 < 0x12; local_58 = local_58 + 1) {
          local_5c = (float)(local_58 * 5) * 0.017453292;
          FUN_00477314((double)local_5c);
          uVar2 = __ftol();
          *(undefined4 *)(&DAT_005e36b8 + local_58 * 4 + local_50 * 0x48) = uVar2;
          FUN_00477ab4();
          uVar2 = __ftol();
          *(undefined4 *)(&DAT_005e3798 + local_58 * 4 + local_50 * 0x48) = uVar2;
        }
      }
      DAT_005e4c5c = 1;
    }
    for (local_24[5] = 0; local_24[5] < 3; local_24[5] = local_24[5] + 1) {
      for (local_60 = 2; local_60 < 0x10; local_60 = local_60 + 1) {
        local_2c = *(int *)(&DAT_005e36b8 + local_60 * 4 + local_24[5] * 0x48);
        local_48[6] = *(int *)(&DAT_005e3798 + local_60 * 4 + local_24[5] * 0x48);
        local_24[1] = local_2c + 0x13b;
        local_24[3] = local_2c + 0x145;
        local_24[2] = local_48[6] + 0xec;
        local_24[4] = local_48[6] + 0xf4;
        thunk_FUN_0042dd0f();
        thunk_FUN_00406604(local_24);
        local_24[1] = 0x13b - local_2c;
        local_24[3] = 0x145 - local_2c;
        local_24[2] = local_48[6] + 0xec;
        local_24[4] = local_48[6] + 0xf4;
        thunk_FUN_0042dd0f();
        thunk_FUN_00406604(local_24);
        local_24[1] = 0x13b - local_2c;
        local_24[3] = 0x145 - local_2c;
        local_24[2] = 0xec - local_48[6];
        local_24[4] = 0xf4 - local_48[6];
        thunk_FUN_0042dd0f();
        thunk_FUN_00406604(local_24);
        local_24[1] = local_2c + 0x13b;
        local_24[3] = local_2c + 0x145;
        local_24[2] = 0xec - local_48[6];
        local_24[4] = 0xf4 - local_48[6];
        thunk_FUN_0042dd0f();
        thunk_FUN_00406604();
        if (local_24[5] <= DAT_004bf118) {
          for (local_64 = 0; local_64 < 10; local_64 = local_64 + 1) {
            FUN_00474b90();
            iVar6 = FUN_00474b90();
            uVar3 = FUN_00474b90(local_48[6] + (0xf4 - iVar6 % 6));
            uVar7 = (int)uVar3 >> 0x1f;
            thunk_FUN_00403a84(in_ECX + 8,
                               local_2c + (0x145 - (((uVar3 ^ uVar7) - uVar7 & 7 ^ uVar7) - uVar7)))
            ;
            FUN_00474b90();
            iVar6 = local_48[6];
            iVar4 = FUN_00474b90();
            uVar3 = FUN_00474b90((0xf4 - iVar4 % 6) - iVar6);
            uVar7 = (int)uVar3 >> 0x1f;
            thunk_FUN_00403a84(in_ECX + 8,
                               local_2c + (0x145 - (((uVar3 ^ uVar7) - uVar7 & 7 ^ uVar7) - uVar7)))
            ;
            FUN_00474b90();
            iVar6 = local_48[6];
            iVar5 = FUN_00474b90();
            iVar4 = local_2c;
            uVar3 = FUN_00474b90((0xf4 - iVar5 % 6) - iVar6);
            uVar7 = (int)uVar3 >> 0x1f;
            thunk_FUN_00403a84(in_ECX + 8,
                               (0x145 - (((uVar3 ^ uVar7) - uVar7 & 7 ^ uVar7) - uVar7)) - iVar4);
            FUN_00474b90();
            FUN_00474b90();
            iVar6 = local_2c;
            uVar3 = FUN_00474b90();
            uVar7 = (int)uVar3 >> 0x1f;
            thunk_FUN_00403a84(in_ECX + 8,
                               (0x145 - (((uVar3 ^ uVar7) - uVar7 & 7 ^ uVar7) - uVar7)) - iVar6);
          }
        }
      }
    }
    local_4c = thunk_FUN_0040ec89(s_newback_004a26e8,1);
    for (local_48[5] = 0; local_48[5] < 4; local_48[5] = local_48[5] + 1) {
      local_2c = *(int *)(&DAT_004a24c8 + local_48[5] * 4) -
                 (int)*(short *)(&DAT_004a2568 + local_48[5] * 2);
      local_48[6] = *(int *)(&DAT_004a24d8 + local_48[5] * 4) + -0x2d;
      local_24[3] = local_2c + *(short *)(&DAT_004a2568 + local_48[5] * 2) * 2;
      local_24[4] = *(int *)(&DAT_004a24d8 + local_48[5] * 4) + 0x2d;
      local_24[1] = local_2c;
      local_24[2] = local_48[6];
      thunk_FUN_00404770(local_24,local_4c,0);
    }
    local_4c = thunk_FUN_0040ec89(s_glyphs_004a26f0,1);
    if (local_4c == 0) {
      thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a2700,0x1df,s_shape_004a26f8);
    }
    if (0x13 < DAT_005e4c58) {
      DAT_005e4c58 = 0;
    }
    for (local_48[5] = 0; local_48[5] < 4; local_48[5] = local_48[5] + 1) {
      thunk_FUN_00404770(in_ECX + 8,local_4c,local_48[5] * 0x14 + DAT_005e4c58);
    }
    local_4c = thunk_FUN_0040ec89(s_levidiff_004a271c,1);
    if (local_4c == 0) {
      thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a2730,0x1e9,s_shape_004a2728);
    }
    thunk_FUN_00404770(in_ECX + 8,local_4c,DAT_004bf11c,0x140,0xf0);
    local_28 = thunk_FUN_0042de03();
    if (local_28 == 0) {
      thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a2754,0x1ed,&DAT_004a274c);
    }
    if (DAT_004befe0 != 0) {
      uVar3 = thunk_FUN_0042dd0f();
      *(uint *)(local_28 + 8) = uVar3 & 0xff;
      for (local_48[5] = 0; local_48[5] < 4; local_48[5] = local_48[5] + 1) {
        for (local_68 = 0; local_68 < DAT_004befe4; local_68 = local_68 + 1) {
          if ((*(uint *)(&DAT_005e1730 + local_68 * 4) & 1 << ((byte)local_48[5] & 0x1f)) != 0) {
            local_7c[0] = 0x114;
            local_7c[1] = 0x7c;
            local_7c[2] = 0x114;
            local_7c[3] = 0x158;
            iVar6 = thunk_FUN_0042892d(&DAT_004beff0 + local_68 * 0x40,0xffffffff,0xffffffff);
            local_7c[4] = *(int *)(&DAT_004a24c8 + local_48[5] * 4) - iVar6 / 2;
            thunk_FUN_004289c0(in_ECX + 8,local_7c[4],local_7c[local_48[5]],
                               &DAT_004beff0 + local_68 * 0x40);
          }
        }
      }
    }
    local_4c = thunk_FUN_0040ec89(s_newback_004a2770,1);
    local_24[1] = 0;
    local_24[2] = 5;
    local_24[3] = 0xbc;
    local_24[4] = 0x5a;
    thunk_FUN_00404770(local_24,local_4c,0,0,0xfffffffb);
    local_24[1] = 0x1e0;
    local_24[2] = 5;
    local_24[3] = 0x24e;
    local_24[4] = 0x5a;
    thunk_FUN_00404770(local_24,local_4c,0,0xfffffe20,0xfffffffb);
    if (DAT_0049f538 != -1) {
      local_4c = thunk_FUN_0040ec89(s_ngrealms_004a2778,1);
      if (local_4c == 0) {
        thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a278c,0x20c,s_shape_004a2784);
      }
      thunk_FUN_00404770(in_ECX + 8,local_4c,DAT_0049f538,0x3c,0x28);
      uVar3 = (int)(DAT_0049f538 + 1U) >> 0x1f;
      thunk_FUN_00404770(in_ECX + 8,local_4c,
                         ((DAT_0049f538 + 1U ^ uVar3) - uVar3 & 3 ^ uVar3) - uVar3,0x8c,0x28);
    }
    local_c = 0.0;
    if (DAT_0049f538 != -1) {
      if ((DAT_004c2b64 % 2 != 0) && (DAT_004a2570 = DAT_004a2570 + 1, 0x10 < DAT_004a2570)) {
        DAT_004a2570 = 1;
      }
      uVar3 = (DAT_004c2b64 >> 1) % 0x18;
      if (uVar3 < 6) {
        fVar10 = (float10)FUN_00476ce4((double)(uVar3 << 1));
        local_c = (double)fVar10;
      }
      else if (uVar3 < 0xc) {
        fVar10 = (float10)FUN_00476ce4((double)(int)((0xc - uVar3) * 2));
        local_c = (double)fVar10;
      }
      else if (uVar3 < 0x12) {
        fVar10 = (float10)FUN_00476ce4((double)(int)(uVar3 * 2 + -0x18));
        local_c = (double)-fVar10;
      }
      else {
        fVar10 = (float10)FUN_00476ce4((double)(int)((0x18 - uVar3) * 2));
        local_c = (double)-fVar10;
      }
      if (DAT_0049f538 == 3) {
        local_c = local_c - 5.0;
      }
      local_4c = thunk_FUN_0040ec89(s_bigfloat_004a27a8,1);
      if (local_4c == 0) {
        thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a27bc,0x22c,s_shape_004a27b4);
      }
      iVar6 = __ftol();
      thunk_FUN_00404770(in_ECX + 8,local_4c,DAT_0049f538 * 0x11,0x212,iVar6 + 0x26);
      iVar6 = __ftol();
      thunk_FUN_00404770(in_ECX + 8,local_4c,DAT_0049f538 * 0x11 + DAT_004a2570,0x212,iVar6 + 0x26);
    }
    if ((*(int *)(in_ECX + 0x70) != 0) && (DAT_0049f538 != -1)) {
      *(undefined4 *)(local_28 + 8) = *(undefined4 *)(in_ECX + 0x74);
      uVar12 = 0x40199c00000001;
      iVar6 = *(int *)(in_ECX + 0x78) + (int)*(short *)(in_ECX + 0x7c + DAT_0049f538 * 4);
      iVar4 = thunk_FUN_004289a7(iVar6,1,&LAB_0040199c);
      thunk_FUN_00428baa(in_ECX + 8,0x14,DAT_004a24dc - iVar4,iVar6,uVar12);
      uVar12 = 0x40199c00000001;
      iVar4 = *(int *)(in_ECX + 0x78) + (int)*(short *)(in_ECX + 0x7e + DAT_0049f538 * 4);
      iVar6 = thunk_FUN_004289a7(iVar4,1,&LAB_0040199c);
      thunk_FUN_00428baa(in_ECX + 8,0x26c,DAT_004a24dc - iVar6,iVar4,uVar12);
      *(undefined4 *)(in_ECX + 0x70) = 0;
    }
    piVar8 = (int *)(in_ECX + 8);
    piVar9 = local_48;
    for (iVar6 = 5; iVar6 != 0; iVar6 = iVar6 + -1) {
      *piVar9 = *piVar8;
      piVar8 = piVar8 + 1;
      piVar9 = piVar9 + 1;
    }
    local_48[1] = 0xf5;
    local_48[3] = 0x18b;
    local_48[2] = 0x1ad;
    local_48[4] = 0x1bb;
    uVar1 = thunk_FUN_0042dd0f();
    thunk_FUN_00406604(local_48,uVar1);
    DAT_005e3790 = thunk_FUN_0044e4f8((int)DAT_00630a3c,(int)DAT_00630a3e);
    if (DAT_005e3790 == -1) {
      DAT_005e3790 = thunk_FUN_0044e48f();
    }
    if ((DAT_005e3790 != -1) && (*(int *)(&DAT_005e4c30 + DAT_005e3790 * 4) != 0)) {
      uVar3 = thunk_FUN_0042dd0f();
      *(uint *)(local_28 + 8) = uVar3 & 0xff;
      iVar6 = *(int *)(in_ECX + 0x14);
      iVar4 = *(int *)(in_ECX + 0xc);
      iVar5 = thunk_FUN_0042892d(*(undefined4 *)(&DAT_005e4c30 + DAT_005e3790 * 4),0xffffffff,
                                 0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,((iVar6 - iVar4) - iVar5) / 2,0x1ae,
                         *(undefined4 *)(&DAT_005e4c30 + DAT_005e3790 * 4));
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,1);
  }
  return;
}
```

---

## FUN_00450030 — 0x450030

- Classification : internal
- Corps : `0x450030–0x45005d`
- État : pseudocode obtenu
- Evidence : `ev_8d3f9bdc873d9514324898b0120c8f4d4d549812d1b1e6bfdd4498a9102aab7c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401014` — `thunk_FUN_0044e758`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00450030(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0044e758();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_00450070 — 0x450070

- Classification : internal
- Corps : `0x450070–0x4500b5`
- État : pseudocode obtenu
- Evidence : `ev_98b9f201b89c4860c1e95155aef815fffd0fedf61374018a528ddd61c616a97d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00450070(int param_1,int param_2)

{
  int iVar1;
  int local_8;
  
  local_8 = 0;
  if ((((0x14 < param_2) && (param_2 < 0x1d)) && (iVar1 = *(int *)(param_1 + 0x14), -1 < iVar1)) &&
     (iVar1 < 4)) {
    local_8 = (int)(char)(&DAT_004a2863)[iVar1 * 8 + param_2];
  }
  return local_8;
}
```

---

## FUN_004500b6 — 0x4500b6

- Classification : internal
- Corps : `0x4500b6–0x4500c3`
- État : pseudocode obtenu
- Evidence : `ev_53210d0c008c77fca6e68ed33585293189972e281e97f4df996f9e855552a877`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004500b6(void)

{
  undefined4 in_ECX;
  
  return in_ECX;
}
```

---

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


# 0015_batch_0011 — détails (2/3)

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

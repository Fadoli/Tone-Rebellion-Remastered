# 0011_batch_0007 — détails (2/6)

## FUN_0042704b — 0x42704b

- Classification : internal
- Corps : `0x42704b–0x428190`
- État : pseudocode obtenu
- Evidence : `ev_d21d92e7afdc377fecc4fce5fecca40c344273a5e036a4c507b40f99ab2e04b1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40105f` — `thunk_FUN_0040ab05`
- `0x401082` — `thunk_FUN_00410bd2`
- `0x4010d7` — `thunk_FUN_0042003c`
- `0x4011a9` — `thunk_FUN_00403c35`
- `0x401276` — `thunk_FUN_0042dd95`
- `0x4012da` — `thunk_FUN_0040adb5`
- `0x40130c` — `thunk_FUN_0045575c`
- `0x40163b` — `thunk_FUN_00404c3b`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x4018cf` — `thunk_FUN_0041ff2e`
- `0x401933` — `thunk_FUN_00464242`
- `0x4019ec` — `thunk_FUN_00405265`
- `0x401a78` — `thunk_FUN_004251a2`
- `0x401ab4` — `thunk_FUN_00425296`
- `0x401b0e` — `thunk_FUN_0040ad94`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401dac` — `thunk_FUN_004207f2`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402040` — `thunk_FUN_00411478`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x402144` — `thunk_FUN_00420f28`
- `0x40215d` — `thunk_FUN_0040aaeb`
- `0x402270` — `thunk_FUN_0041137c`
- `0x40229d` — `thunk_FUN_00405e11`
- `0x402306` — `thunk_FUN_004106dd`
- `0x4023bf` — `thunk_FUN_0045c3bb`
- `0x4023dd` — `thunk_FUN_0041ff56`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472c6c` — `__ftol`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49d048` — "Worker"
- `0x49d424` — "C:\\float\\src\\fltdraw.cpp"
- `0x49d440` — "type>(int)FT_None && type<(int)FT_NumTypes"
- `0x49d46c` — "C:\\float\\src\\fltdraw.cpp"
- `0x49d490` — "C:\\float\\src\\fltdraw.cpp"
- `0x49d4b4` — "spl11"
- `0x49d4bc` — "fltinfo"
- `0x49d4c4` — "rshape"
- `0x49d4cc` — "C:\\float\\src\\fltdraw.cpp"
- `0x49d4e8` — "realm>=0 && realm < 4"
- `0x49d500` — "C:\\float\\src\\fltdraw.cpp"

### Pseudocode Ghidra

```c
void FUN_0042704b(undefined4 param_1,int *param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,int param_8)

{
  undefined1 uVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 uVar6;
  bool bVar7;
  undefined1 *puVar8;
  int iVar9;
  int local_148;
  int local_130;
  int local_12c;
  int local_128;
  int local_124;
  int local_120;
  int local_114;
  int local_f4;
  int local_d8;
  int local_d4;
  int local_b4;
  int local_b0;
  int local_ac;
  uint local_a4;
  int local_a0;
  int local_9c;
  int local_98;
  int local_94;
  uint local_90;
  undefined4 local_8c;
  uint local_88;
  undefined1 local_84 [12];
  uint local_78;
  int local_74;
  int local_70;
  undefined4 local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  undefined4 local_50;
  uint local_4c;
  short *local_48;
  int local_44;
  int local_40;
  uint local_3c;
  undefined4 local_38;
  int local_34;
  undefined4 local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (param_2 == (int *)0x0) {
    thunk_FUN_00414b64(s_C__float_src_fltdraw_cpp_0049d424,0x58,&DAT_0049d420);
  }
  local_2c = *param_2;
  if ((local_2c < 0) || (4 < local_2c)) {
    thunk_FUN_00414b64(s_C__float_src_fltdraw_cpp_0049d46c,0x5a,
                       s_type>_int_FT_None____type<(int)F_0049d440);
  }
  local_24 = thunk_FUN_00464242(*param_2,param_2[1]);
  local_48 = (short *)thunk_FUN_0045575c(CONCAT22(extraout_var,*(undefined2 *)(local_24 + 4)));
  local_c = 0;
  uVar6 = extraout_var_00;
  if (*local_48 != -1) {
    local_c = thunk_FUN_0040e864(*local_48);
    uVar6 = extraout_var_01;
  }
  local_20 = thunk_FUN_0040e864(CONCAT22(uVar6,local_48[1]));
  if (local_20 == 0) {
    thunk_FUN_00414b64(s_C__float_src_fltdraw_cpp_0049d490,100,&DAT_0049d488);
  }
  local_3c = (uint)*(byte *)(param_2 + 5);
  if ((param_5 != 0) && ((param_2[7] & 8U) == 0)) {
    local_3c = local_3c + DAT_00618e44;
  }
  local_34 = (int)local_48[0x25];
  local_28 = (int)local_48[0x26];
  if (((param_5 == 0) || (param_2[0xb] != 0x11)) || ((short)param_2[0xd] < 1)) {
    if ((param_2[7] & 2U) != 0) {
      local_34 = -local_34;
      param_7 = -param_7;
    }
  }
  else {
    local_68 = (int)(short)param_2[0xd];
    if (0x78 < local_68) {
      local_68 = 0x78;
    }
    if (0x3c < local_68) {
      local_68 = local_68 + -0x3c;
    }
    param_4 = param_4 - (local_68 * local_68) / 0x14;
    param_6 = 8 - ((int)(local_68 + (local_68 >> 0x1f & 7U)) >> 3);
    DAT_005dc668 = 0;
  }
  local_38 = 0;
  if ((param_2[0xe] == (int)DAT_005e16ec) || (param_8 == 1)) {
    uVar3 = thunk_FUN_004106dd(1,1);
    thunk_FUN_00404c3b(uVar3);
    local_38 = 1;
  }
  local_30 = 0;
  if (param_2[6] != 0) {
    local_70 = param_3 + local_34;
    local_74 = param_4 + local_28;
    local_6c = 0;
    local_50 = 0;
    thunk_FUN_0040adb5(param_2[6],&local_78,&local_40);
    sVar2 = thunk_FUN_0040ad94(param_2[6]);
    local_74 = local_74 + sVar2;
    if ((local_78 & 0xffff) == 0) {
      if ((4 < param_2[6]) && (param_2[6] < 0x22)) {
        FUN_00472ca0(local_84,&DAT_0049d4ac,param_2[6] + -5);
        puVar8 = local_84;
        uVar3 = param_1;
        iVar5 = local_70;
        iVar4 = local_74;
        thunk_FUN_0042de03(param_1,local_70,local_74,puVar8);
        thunk_FUN_004289c0(uVar3,iVar5,iVar4,puVar8);
      }
    }
    else {
      local_50 = thunk_FUN_0040e864(CONCAT22(sVar2 >> 0xf,(undefined2)local_78));
      if (param_6 < 8) {
        thunk_FUN_00410bd2(param_1,local_50,local_40,local_70,local_74,param_6);
      }
      else {
        thunk_FUN_00404770(param_1,local_50,local_40,local_70,local_74);
      }
    }
  }
  local_54 = 0;
  bVar7 = (param_2[7] & 8U) != 0;
  if (bVar7) {
    local_54 = param_2[9];
  }
  local_4c = (uint)bVar7;
  local_1c = 1000;
  local_18 = 1000;
  local_14 = 0;
  local_10 = 0;
  if (*local_48 != -1) {
    local_40 = (int)local_48[2];
    if (local_40 == -1) {
      thunk_FUN_0042dd95(param_3 + -0xf,param_4 + -0xc,s_Worker_0049d048 + param_2[1] * 0xc);
    }
    else {
      sVar2 = thunk_FUN_0041ff2e();
      local_40 = local_40 + sVar2;
      if (local_40 < local_48[2]) {
        local_40 = (int)local_48[2];
      }
      if (local_48[3] < local_40) {
        local_40 = (int)local_48[3];
      }
      if (local_54 < 0x14) {
        if (param_6 < 8) {
          thunk_FUN_00410bd2(param_1,local_c,local_40,param_3,param_4,param_6);
        }
        else {
          thunk_FUN_00405265(param_1,local_c,local_40,param_3,param_4,&DAT_004b28f0,0,param_7,
                             0x10000,local_38);
          if (DAT_005dc668 != 0) {
            local_88 = (uint)(param_7 != 0x10000);
            thunk_FUN_00405e11(local_c,local_40,param_3,param_4,local_88,&local_1c);
          }
        }
      }
      if (local_4c != 0) {
        thunk_FUN_0041137c(param_1,local_c,local_40,param_3,param_4,local_54,param_7 != 0x10000);
      }
    }
  }
  local_44 = local_40;
  if (((*param_2 == 1) && (param_2[1] == 4)) && (param_2[0xb] == 0x13)) {
    local_8c = 1;
  }
  if ((((param_2[0xb] == 6) || (param_2[0xb] == 7)) || (param_2[0xb] == 0x13)) &&
     ((0 < (short)param_2[0xd] &&
      (iVar5 = param_2[0xd], iVar4 = thunk_FUN_004251a2(param_2[0xb]), (short)iVar5 <= iVar4)))) {
    if (*(int *)(local_48 + 0x20) == 0) {
      local_40 = thunk_FUN_0040aaeb((int)local_48[0x1c],(int)local_48[0x1d],
                                    (int)(short)param_2[0xd] / (int)local_48[0x1e]);
    }
    else {
      local_40 = thunk_FUN_0040ab05((int)local_48[0x1c],(int)local_48[0x1d],
                                    (int)(short)param_2[0xd] / (int)local_48[0x1e]);
    }
  }
  else if (param_2[6] == 0) {
    local_40 = thunk_FUN_0040aaeb((int)local_48[4],(int)local_48[5],
                                  local_3c / (uint)(int)local_48[6]);
  }
  else {
    local_40 = thunk_FUN_0040aaeb((int)local_48[0x14],(int)local_48[0x15],
                                  local_3c / (uint)(int)local_48[0x16]);
  }
  if (local_40 == -1) {
    local_40 = 0;
  }
  if (local_54 < 0x14) {
    if (param_6 < 8) {
      thunk_FUN_00410bd2(param_1,local_20,local_40,param_3,param_4,param_6);
    }
    else {
      thunk_FUN_00405265(param_1,local_20,local_40,param_3,param_4,&DAT_004b28f0,0,param_7,0x10000,
                         local_38);
      if (DAT_005dc668 != 0) {
        local_90 = (uint)(param_7 != 0x10000);
        thunk_FUN_00405e11(local_20,0,param_3,param_4,local_90,&local_64);
      }
    }
  }
  if (local_4c != 0) {
    thunk_FUN_0041137c(param_1,local_20,local_40,param_3,param_4,local_54,param_7 != 0x10000);
  }
  local_8 = 0;
  if ((-1 < *(short *)((int)param_2 + 0xe)) && (*(short *)((int)param_2 + 0xe) < 0xf)) {
    local_8 = (int)*(short *)(&DAT_0061fa2e + *(short *)((int)param_2 + 0xe) * 2);
  }
  if ((((param_5 != 0) && (*param_2 == 4)) && (0 < local_8)) && (local_8 < 0x16)) {
    local_40 = (0x16 - local_8) / 2;
    if (local_40 < 0) {
      local_40 = 0;
    }
    if (10 < local_40) {
      local_40 = 10;
    }
    iVar5 = local_40;
    iVar4 = param_3;
    iVar9 = param_4;
    uVar3 = thunk_FUN_0040ec89(s_spl11_0049d4b4,1);
    thunk_FUN_00404770(param_1,uVar3,iVar5,iVar4,iVar9);
  }
  if ((((param_2[7] & 0x2000U) != 0) ||
      (((param_2[7] & 0x100U) != 0 && (iVar5 = thunk_FUN_00425296(0x2000), param_2[9] < iVar5)))) &&
     (param_5 != 0)) {
    thunk_FUN_00411478(param_1,param_3 + -0x12,param_4 + -0xc,param_3 + 0x12,param_4 + 0x18,
                       DAT_00618e44 >> 1);
  }
  if ((param_2[7] & 0x808U) == 0) {
    if ((local_c != 0) && (((DAT_005c37f4 != 0 || (DAT_005c37f8 != 0)) || (DAT_005c37fc != 0)))) {
      local_9c = thunk_FUN_0040ec89(s_fltinfo_0049d4bc,1);
      if (local_9c == 0) {
        thunk_FUN_00414b64(s_C__float_src_fltdraw_cpp_0049d4cc,0x12e,s_rshape_0049d4c4);
      }
      local_a4 = (uint)((param_2[7] & 2U) != 0);
      thunk_FUN_00405e11(local_c,local_44,param_3,param_4,local_a4,&local_b4);
      if (local_a4 == 0) {
        local_148 = local_b4 + -8;
      }
      else {
        local_148 = local_ac;
      }
      local_94 = local_148;
      local_98 = local_b0;
    }
    if (((DAT_005c37f4 != 0) && (param_5 != 0)) && (local_c != 0)) {
      sVar2 = thunk_FUN_0042003c(param_2[1]);
      iVar5 = (int)sVar2;
      if ((iVar5 < 0) || (3 < iVar5)) {
        thunk_FUN_00414b64(s_C__float_src_fltdraw_cpp_0049d500,0x13c,
                           s_realm>_0____realm_<_4_0049d4e8);
      }
      thunk_FUN_00404770(param_1,local_9c,iVar5 + 0x16,local_94,local_98);
    }
    if (((DAT_005c37f8 != 0) && (param_5 != 0)) && (local_c != 0)) {
      thunk_FUN_00420f28();
      local_d4 = __ftol();
      if (10 < local_d4) {
        local_d4 = 10;
      }
      local_d8 = 2;
      if ((param_2[1] != 0) && (param_2[1] != 8)) {
        local_d8 = (-(uint)(local_a4 != 0) & 0xfffffffb) + 5;
      }
      thunk_FUN_00404770(param_1,local_9c,0x15 - local_d4,local_94 + local_d8,local_98);
    }
    if ((((DAT_005c37fc != 0) && (param_5 != 0)) && (*param_2 != 4)) &&
       ((0 < param_2[1] && (local_c != 0)))) {
      thunk_FUN_00464242(*param_2,param_2[1]);
      local_f4 = __ftol();
      if (10 < local_f4) {
        local_f4 = 10;
      }
      thunk_FUN_00404770(param_1,local_9c,10 - local_f4,local_94 + (-(uint)(local_a4 != 0) & 5),
                         local_98);
    }
    sVar2 = thunk_FUN_0041ff56();
    local_a0 = (int)sVar2;
    if (((0 < local_a0) && (DAT_005c37fc != 0)) &&
       ((param_5 != 0 &&
        ((((*param_2 == 4 && (9 < param_2[1])) && (param_2[1] < 0x12)) && (local_c != 0)))))) {
      local_114 = __ftol();
      if (10 < local_114) {
        local_114 = 10;
      }
      thunk_FUN_00404770(param_1,local_9c,0x2a - local_114,local_94 + (-(uint)(local_a4 != 0) & 5),
                         local_98);
    }
    if (((DAT_005c37f8 != 0) && (param_5 != 0)) && ((local_c != 0 && (param_2 != (int *)0x0)))) {
      local_120 = 0;
      iVar5 = thunk_FUN_004207f2();
      if (iVar5 != 0) {
        local_120 = thunk_FUN_0045c3bb();
      }
      if ((*param_2 == 4) && (100 < local_8)) {
        thunk_FUN_00404770(param_1,local_9c,0x1e,local_94,local_98 + -10);
      }
      else if ((param_2[1] == 0) && ((param_2[7] & 0x100U) != 0)) {
        thunk_FUN_00404770(param_1,local_9c,0x1c,local_94,local_98 + -10);
      }
      else if ((param_2[1] == 0) && (0 < *(short *)(&DAT_00618f5a + *param_2 * 2))) {
        thunk_FUN_00404770(param_1,local_9c,0x1f,local_94,local_98 + -10);
      }
      else if ((local_120 == 0) || ((*(uint *)(local_120 + 0x1c) & 0x8000) == 0)) {
        sVar2 = *(short *)((int)param_2 + 0x22);
        iVar5 = thunk_FUN_00464242(*param_2,param_2[1]);
        if (*(short *)(iVar5 + 8) < sVar2) {
          thunk_FUN_00404770(param_1,local_9c,0x1d,local_94,local_98 + -10);
        }
        else {
          iVar5 = param_2[8];
          sVar2 = thunk_FUN_00420f28();
          if (sVar2 < (short)iVar5) {
            thunk_FUN_00404770(param_1,local_9c,0x1a,local_94,local_98 + -10);
          }
        }
      }
      else {
        thunk_FUN_00404770(param_1,local_9c,0x1b,local_94,local_98 + -10);
      }
    }
  }
  if (DAT_005dc668 != 0) {
    local_130 = local_1c + -2;
    local_12c = local_18 + -2;
    local_128 = local_14 + 2;
    local_124 = local_10 + 10;
    if (local_64 < local_130) {
      local_130 = local_64;
    }
    if (local_128 < local_5c) {
      local_128 = local_5c;
    }
    if (local_60 < local_12c) {
      local_12c = local_60;
    }
    if (local_124 < local_58) {
      local_124 = local_58;
    }
    uVar1 = thunk_FUN_0042dd0f(1);
    thunk_FUN_00403c35(param_1,local_130,local_12c,local_130 + 3,local_12c,0,uVar1);
    thunk_FUN_00403c35(param_1,local_130,local_12c,local_130,local_12c + 3,0,uVar1);
    thunk_FUN_00403c35(param_1,local_128,local_12c,local_128 + -3,local_12c,0,uVar1);
    thunk_FUN_00403c35(param_1,local_128,local_12c,local_128,local_12c + 3,0,uVar1);
    thunk_FUN_00403c35(param_1,local_128,local_124,local_128 + -3,local_124,0,uVar1);
    thunk_FUN_00403c35(param_1,local_128,local_124,local_128,local_124 + -3,0,uVar1);
    thunk_FUN_00403c35(param_1,local_130,local_124,local_130 + 3,local_124,0,uVar1);
    thunk_FUN_00403c35(param_1,local_130,local_124,local_130,local_124 + -3,0,uVar1);
  }
  return;
}
```

---

## FUN_00428191 — 0x428191

- Classification : internal
- Corps : `0x428191–0x42822a`
- État : pseudocode obtenu
- Evidence : `ev_9a0e092353507683f0102fe470bdc369d3f92a2f1bc02487e899e9063ddd8c2f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40116d` — `thunk_FUN_0041e4d9`
- `0x40156e` — `thunk_FUN_0041ff8b`
- `0x4017a3` — `thunk_FUN_0041e4c3`
- `0x401a87` — `thunk_FUN_0042704b`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00428191(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  undefined2 extraout_var;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_30;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004915e9;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0041e4c3();
  local_8 = 0;
  local_5c = param_2;
  local_58 = param_3;
  thunk_FUN_0041ff8b(CONCAT22(extraout_var,param_4));
  local_30 = 0;
  local_44 = 0;
  local_40 = 0;
  thunk_FUN_0042704b(param_1,&local_5c,param_5,param_6,0,param_7,0x10000,0);
  local_8 = 0xffffffff;
  thunk_FUN_0041e4d9();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

## FUN_0042822b — 0x42822b

- Classification : internal
- Corps : `0x42822b–0x4282be`
- État : pseudocode obtenu
- Evidence : `ev_b4229d42dd41f3c5fdd3e44835793cad041459a76c6cdcee1c5d7ee52f113714`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40110e` — `thunk_FUN_00426fd0`
- `0x401a87` — `thunk_FUN_0042704b`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49d520` — "C:\\float\\src\\fltdraw.cpp"

### Pseudocode Ghidra

```c
void FUN_0042822b(undefined4 param_1,int param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 == 0) {
    thunk_FUN_00414b64(s_C__float_src_fltdraw_cpp_0049d520,0x1ba,&DAT_0049d51c);
  }
  iVar3 = (int)*(short *)(param_2 + 0x10) - (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
  sVar1 = *(short *)(param_2 + 0x12);
  iVar2 = thunk_FUN_00426fd0(param_2);
  if (iVar3 < 700) {
    thunk_FUN_0042704b(param_1,param_2,iVar3,sVar1 + iVar2,1,8,0x10000,0);
  }
  return;
}
```

---

## FUN_004282bf — 0x4282bf

- Classification : internal
- Corps : `0x4282bf–0x4282f8`
- État : pseudocode obtenu
- Evidence : `ev_f5fcae142471f5b2e5662a1f63ab31397c726411a7999a9c16e680c40939692d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004282bf(void)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
    *(undefined1 **)(&DAT_004c2ca0 + local_8 * 4) = &LAB_00401627;
  }
  DAT_004c2cb4 = 1;
  return;
}
```

---

## FUN_004282f9 — 0x4282f9

- Classification : internal
- Corps : `0x4282f9–0x428322`
- État : pseudocode obtenu
- Evidence : `ev_7bee3b46f2a506574fd7a2eed72aa88f4ebd83f2e16fe2ef817307a538f16fe8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401abe` — `thunk_FUN_004282bf`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004282f9(undefined4 param_1,int *param_2)

{
  if (DAT_004c2cb4 == 0) {
    thunk_FUN_004282bf();
  }
  (**(code **)(&DAT_004c2ca0 + *param_2 * 4))(param_1,param_2);
  return;
}
```

---

## FUN_00428800 — 0x428800

- Classification : internal
- Corps : `0x428800–0x428883`
- État : pseudocode obtenu
- Evidence : `ev_e824abcf343d7768146af3913ccca58952807bea96ec700f01ab05366e006c9f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00428800(void)

{
  undefined4 *in_ECX;
  int local_8;
  
  if (DAT_004c2ec0 == 0) {
    DAT_004c2dbf = 0xff;
    for (local_8 = 0; local_8 < 0x100; local_8 = local_8 + 1) {
      (&DAT_004c2dc0)[local_8] = (undefined1)local_8;
    }
    DAT_004c2ec0 = 1;
  }
  *in_ECX = 0;
  in_ECX[1] = 0;
  in_ECX[2] = 0xffffffff;
  in_ECX[3] = 3;
  in_ECX[4] = 0;
  return in_ECX;
}
```

---

## FUN_00428884 — 0x428884

- Classification : internal
- Corps : `0x428884–0x42892c`
- État : pseudocode obtenu
- Evidence : `ev_62d8b921775b33793b4b8683fb72f17353b1cf54d782b26b0a8d3881d5e263d0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x401749` — `thunk_FUN_00414c97`
- `0x4017f3` — `thunk_FUN_0040fb84`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401eba` — `thunk_FUN_0040f752`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00428884(undefined4 param_1)

{
  int iVar1;
  int *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049160c;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (*in_ECX != 0) {
    thunk_FUN_00414c97(*in_ECX);
    *in_ECX = 0;
  }
  thunk_FUN_0040f6f7();
  local_8 = 0;
  thunk_FUN_0040f752(param_1,0x8000);
  iVar1 = thunk_FUN_0040fb84(0);
  *in_ECX = iVar1;
  local_8 = 0xffffffff;
  thunk_FUN_0040f73f();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

## FUN_0042892d — 0x42892d

- Classification : internal
- Corps : `0x42892d–0x4289a6`
- État : pseudocode obtenu
- Evidence : `ev_058e7cccfcc8f22bdbb7a363c4b82bc46a45a9cd6d91d8b0bdaa8133bacfbea0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401974` — `thunk_FUN_00408287`
- `0x472e90` — `_strlen`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0042892d(char *param_1,int param_2,int param_3)

{
  size_t sVar1;
  int iVar2;
  undefined4 *in_ECX;
  int local_c;
  int local_8;
  
  if (param_2 == -1) {
    param_2 = 0;
  }
  if (param_3 == -1) {
    sVar1 = _strlen(param_1);
    param_3 = sVar1 - 1;
  }
  local_8 = 0;
  for (local_c = param_2; local_c <= param_3; local_c = local_c + 1) {
    iVar2 = thunk_FUN_00408287(*in_ECX,param_1[local_c]);
    local_8 = local_8 + iVar2;
  }
  return local_8;
}
```

---

## FUN_004289a7 — 0x4289a7

- Classification : internal
- Corps : `0x4289a7–0x4289bf`
- État : pseudocode obtenu
- Evidence : `ev_1eb850d08499e460e387a0ce0794bd470f0fc6584b29fe8a329a33e0d2f8eb98`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401523` — `thunk_FUN_00408274`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004289a7(void)

{
  undefined4 *in_ECX;
  
  thunk_FUN_00408274(*in_ECX);
  return;
}
```

---

## FUN_004289c0 — 0x4289c0

- Classification : internal
- Corps : `0x4289c0–0x4289eb`
- État : pseudocode obtenu
- Evidence : `ev_b450008741a2d0bbef5d7ca9a9af52a90961e5ef685add7eaf6fb885b4c99290`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401294` — `thunk_FUN_004289ec`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004289c0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int in_ECX;
  
  thunk_FUN_004289ec(param_1,param_2,param_3,param_4,*(undefined4 *)(in_ECX + 0x10));
  return;
}
```

---

## FUN_004289ec — 0x4289ec

- Classification : internal
- Corps : `0x4289ec–0x428ba9`
- État : pseudocode obtenu
- Evidence : `ev_af4527d762caf118766ab1ee0e25ab1ab9e5c8accc75e7ff253c646edfb319fb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401280` — `thunk_FUN_0040843a`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x401523` — `thunk_FUN_00408274`
- `0x401974` — `thunk_FUN_00408287`
- `0x401e79` — `thunk_FUN_004082a7`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x402234` — `thunk_FUN_0042892d`
- `0x472e90` — `_strlen`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x49d574` — "mShape"
- `0x49d57c` — "C:\\float\\src\\font.cpp"

### Pseudocode Ghidra

```c
void FUN_004289ec(int *param_1,int param_2,int param_3,char *param_4,uint param_5)

{
  size_t sVar1;
  int *in_ECX;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int local_30;
  int local_24 [4];
  int local_14;
  int local_10;
  int local_c;
  undefined *local_8;
  
  if (*in_ECX == 0) {
    thunk_FUN_00414b64(s_C__float_src_font_cpp_0049d57c,0x60,s_mShape_0049d574);
  }
  local_8 = &DAT_004c2dc0;
  if (in_ECX[2] != -1) {
    local_8 = &DAT_004c2cc0;
    _memset(&DAT_004c2cc1,in_ECX[2],0xfe);
  }
  local_10 = thunk_FUN_00408274(*in_ECX);
  if ((param_5 & 1) == 0) {
    local_c = thunk_FUN_0042892d(param_4,0xffffffff,0xffffffff);
  }
  else {
    sVar1 = _strlen(param_4);
    local_c = thunk_FUN_00408287(*in_ECX,0x43);
    local_c = sVar1 * local_c;
  }
  piVar3 = param_1;
  piVar4 = local_24;
  for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar4 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar4 = piVar4 + 1;
  }
  local_24[1] = param_2;
  local_24[2] = param_3;
  local_24[3] = param_2 + local_c;
  local_14 = param_3 + local_10;
  if ((param_5 & 2) != 0) {
    thunk_FUN_00406604(local_24,in_ECX[1]);
  }
  if ((param_5 & 1) == 0) {
    if (*param_4 != '\0') {
      thunk_FUN_0040843a(param_1,param_2,param_3,*in_ECX,param_4,local_8);
    }
  }
  else {
    iVar2 = thunk_FUN_00408287(*in_ECX,0x43);
    local_30 = param_2;
    for (; *param_4 != '\0'; param_4 = param_4 + 1) {
      thunk_FUN_004082a7(param_1,local_30,param_3,*in_ECX,(int)*param_4,local_8);
      local_30 = local_30 + iVar2;
    }
  }
  if ((param_5 & 8) != 0) {
    thunk_FUN_0042d87c(local_24,(char)in_ECX[3]);
  }
  return;
}
```

---

## FUN_00428baa — 0x428baa

- Classification : internal
- Corps : `0x428baa–0x428fea`
- État : pseudocode obtenu
- Evidence : `ev_070bb8f7f12c4075d07ababe01d163146f4b42bd9713ada666333c335146cb96`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402234` — `thunk_FUN_0042892d`
- `0x472e90` — `_strlen`
- `0x4737e0` — `_strncpy`
- `0x4773b0` — `FUN_004773b0`

### Chaînes référencées

- `0x49d594` — "num_spaces<MAX_SPACES"
- `0x49d5ac` — "C:\\float\\src\\font.cpp"
- `0x49d5c4` — "num_spaces<MAX_SPACES"
- `0x49d5dc` — "C:\\float\\src\\font.cpp"
- `0x49d5f4` — "endspace>=0"
- `0x49d600` — "C:\\float\\src\\font.cpp"

### Pseudocode Ghidra

```c
void FUN_00428baa(int param_1,int param_2,undefined4 param_3,char *param_4,int param_5,code *param_6
                 )

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_548;
  int local_540;
  int local_53c;
  char *local_534;
  undefined1 local_528 [4];
  undefined4 local_524;
  char local_520 [256];
  int local_420;
  size_t local_41c;
  int local_418;
  int local_414;
  int local_410;
  int aiStack_40c [256];
  int local_c;
  int local_8;
  
  if (((param_6 == (code *)0x0) || (param_4 == (char *)0x0)) || (param_1 == 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if (bVar1) {
    local_410 = param_2;
    local_524 = param_3;
    local_41c = _strlen(param_4);
    local_8 = 0;
    for (local_418 = 0; local_418 < (int)local_41c; local_418 = local_418 + 1) {
      if (param_4[local_418] == ' ') {
        if (0xff < local_8) {
          thunk_FUN_00414b64(s_C__float_src_font_cpp_0049d5ac,0xa9,s_num_spaces<MAX_SPACES_0049d594)
          ;
        }
        aiStack_40c[local_8] = local_418;
        local_8 = local_8 + 1;
      }
    }
    if (0xff < local_8) {
      thunk_FUN_00414b64(s_C__float_src_font_cpp_0049d5dc,0xad,s_num_spaces<MAX_SPACES_0049d5c4);
    }
    aiStack_40c[local_8] = local_418;
    local_8 = local_8 + 1;
    local_c = 0;
    while (local_c < (int)local_41c) {
      (*param_6)(local_410,local_524,&local_410,&local_524,&local_414,local_528);
      iVar4 = local_414 - local_410;
      local_420 = local_8 + -1;
      while (iVar2 = thunk_FUN_0042892d(param_4,local_c,aiStack_40c[local_420] + -1), iVar4 < iVar2)
      {
        local_420 = local_420 + -1;
        if (local_420 < 0) {
          thunk_FUN_00414b64(s_C__float_src_font_cpp_0049d600,0xc0,s_endspace>_0_0049d5f4);
        }
      }
      _strncpy(local_520,param_4 + local_c,aiStack_40c[local_420] - local_c);
      local_520[aiStack_40c[local_420] - local_c] = '\0';
      if (param_5 == 0) {
        thunk_FUN_004289c0(param_1,local_410,local_524,local_520);
      }
      else {
        local_53c = 0;
        for (local_534 = local_520; *local_534 != '\0'; local_534 = local_534 + 1) {
          if (*local_534 == ' ') {
            local_53c = local_53c + 1;
          }
        }
        if (local_53c == 0) {
          local_53c = 1;
        }
        iVar2 = thunk_FUN_0042892d(local_520,0xffffffff,0xffffffff);
        iVar4 = iVar4 - iVar2;
        iVar2 = iVar4 / local_53c;
        local_548 = local_410;
        local_534 = (char *)FUN_004773b0(local_520,&DAT_0049d618);
        local_540 = iVar4 - iVar2 * local_53c;
        while (local_534 != (char *)0x0) {
          iVar4 = thunk_FUN_0042892d(local_534,0xffffffff,0xffffffff);
          iVar3 = thunk_FUN_0042892d(&DAT_0049d61c,0xffffffff,0xffffffff);
          thunk_FUN_004289c0(param_1,local_548,local_524,local_534);
          local_548 = local_548 + iVar4 + iVar3 + iVar2;
          if (local_540 != 0) {
            local_548 = local_548 + 1;
          }
          local_534 = (char *)FUN_004773b0(0,&DAT_0049d620);
          local_540 = local_540 + -1;
        }
      }
      local_c = aiStack_40c[local_420] + 1;
    }
  }
  return;
}
```

---

## FUN_004291f0 — 0x4291f0

- Classification : internal
- Corps : `0x4291f0–0x4291f9`
- État : pseudocode obtenu
- Evidence : `ev_3f3f365243a48c6fca5f88c191292e2bb970aaf4fe0a415d4c2355f54b03f72e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4291fa` — `FUN_004291fa`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004291f0(void)

{
  FUN_004291fa();
  return;
}
```

---

## FUN_004291fa — 0x4291fa

- Classification : internal
- Corps : `0x4291fa–0x429208`
- État : pseudocode obtenu
- Evidence : `ev_b0f3e5c9726e5319cafea1c2f3c7888fd1fa047d6fcc3b45e611d50797c568af`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4020cc` — `thunk_FUN_00428800`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004291fa(void)

{
  thunk_FUN_00428800();
  return;
}
```

---

## FUN_00429209 — 0x429209

- Classification : internal
- Corps : `0x429209–0x429242`
- État : pseudocode obtenu
- Evidence : `ev_60089f167d8a725ffff636d52f369f93cf4e5222f99edaaa5b4c4871d8488763`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00429209(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if ((((param_1 < *(int *)(param_3 + 4)) || (*(int *)(param_3 + 0xc) < param_1)) ||
      (param_2 < *(int *)(param_3 + 8))) || (*(int *)(param_3 + 0x10) < param_2)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}
```

---

## FUN_00429243 — 0x429243

- Classification : internal
- Corps : `0x429243–0x429261`
- État : pseudocode obtenu
- Evidence : `ev_e226c86e7af328ab359627b9ff5b4ad9d906efae112a9c39c6287863552c2e2d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010e1` — `thunk_FUN_00429276`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00429243(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494168;
  thunk_FUN_00429276();
  return in_ECX;
}
```

---

## FUN_00429262 — 0x429262

- Classification : internal
- Corps : `0x429262–0x429275`
- État : pseudocode obtenu
- Evidence : `ev_7bb6f62c0432fd9ea8756f86ba744c3ada95cdc07a65b17c33e2417cf0025f2a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429262(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494168;
  return;
}
```

---

## FUN_00429276 — 0x429276

- Classification : internal
- Corps : `0x429276–0x42930e`
- État : pseudocode obtenu
- Evidence : `ev_314c189323a147e2680822eb0f068dcf8af18d5582e6ec09118a2f285b932b5c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429276(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 4) = 0;
  *(undefined4 *)(in_ECX + 8) = 0;
  *(undefined2 *)(in_ECX + 0x1c) = 0xffff;
  *(undefined2 *)(in_ECX + 0x1e) = 0xffff;
  *(undefined1 *)(in_ECX + 0x20) = 0;
  *(undefined4 *)(in_ECX + 0x38) = 0;
  *(undefined4 *)(in_ECX + 0x3c) = 0;
  *(undefined4 *)(in_ECX + 0x44) = 0;
  *(undefined2 *)(in_ECX + 0x60) = 0;
  *(undefined4 *)(in_ECX + 100) = 0;
  *(undefined4 *)(in_ECX + 0x68) = 0;
  *(undefined2 *)(in_ECX + 0x6c) = 0;
  *(undefined2 *)(in_ECX + 0x6e) = 0;
  *(undefined4 *)(in_ECX + 0x40) = 0;
  *(undefined4 *)(in_ECX + 0x34) = 0;
  return;
}
```

---

## FUN_0042930f — 0x42930f

- Classification : internal
- Corps : `0x42930f–0x42932d`
- État : pseudocode obtenu
- Evidence : `ev_70863ade22444382a63117a55fd68b519aaefc1e9000de9099b7252692795c21`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021f3` — `thunk_FUN_0046c7df`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042930f(void)

{
  undefined4 uVar1;
  int in_ECX;
  
  uVar1 = thunk_FUN_0046c7df(in_ECX);
  *(undefined4 *)(in_ECX + 4) = uVar1;
  return;
}
```

---


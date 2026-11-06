# 0011_batch_0007 — détails (1/3)

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

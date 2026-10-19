# 0013_batch_0009 — détails (1/2)

## FUN_00440567 — 0x440567

- Classification : internal
- Corps : `0x440567–0x441aad`
- État : pseudocode obtenu
- Evidence : `ev_cb0962ae9a0187897045bd9eabf82039d7325297fa191f029a6c7d4a5a3e33ed`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x40110e` — `thunk_FUN_00426fd0`
- `0x40116d` — `thunk_FUN_0041e4d9`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x401636` — `thunk_FUN_0045d9c1`
- `0x4016ea` — `thunk_FUN_004118df`
- `0x4017a3` — `thunk_FUN_0041e4c3`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x40181b` — `thunk_FUN_00450978`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x4019b5` — `thunk_FUN_0046562b`
- `0x401a87` — `thunk_FUN_0042704b`
- `0x401ac8` — `thunk_FUN_00441b36`
- `0x401b31` — `thunk_FUN_0041179e`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401bbd` — `thunk_FUN_00441aae`
- `0x401cad` — `thunk_FUN_0043fb30`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401eab` — `thunk_FUN_0040bf98`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x402103` — `thunk_FUN_0044034e`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x40248c` — `thunk_FUN_0045cd27`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472c6c` — `__ftol`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x4a0590` — "bldgage"
- `0x4a059c` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a05b4` — "bildicon"
- `0x4a05c0` — "shape"
- `0x4a05c8` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a05e0` — "tonecrys"
- `0x4a05ec` — "shape"
- `0x4a05f4` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a060c` — "taskicon"
- `0x4a0618` — "shape"
- `0x4a0620` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0638` — "magctone"
- `0x4a0644` — "shape"
- `0x4a064c` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0664` — "taskicon"
- `0x4a0670` — "shape"
- `0x4a0678` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0690` — "bildtone"
- `0x4a069c` — "shape"
- `0x4a06a4` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a06c0` — "tonecrys"
- `0x4a06cc` — "shape"
- `0x4a06d4` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a06f0` — "magctone"
- `0x4a06fc` — "shape"
- `0x4a0704` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0720` — "SURPFLOW"
- `0x4a072c` — "%s %d"
- `0x4a0734` — "POPSTR"
- `0x4a073c` — "%s %d"
- `0x4a0744` — "WORKSTR"
- `0x4a074c` — "%s %d (%d%%)"
- `0x4a075c` — "ACTICON"
- `0x4a0764` — "BC_OnOff"
- `0x4a0770` — "BC_HallStkB"
- `0x4a077c` — "BC_HallStkC"
- `0x4a0788` — "BC_HallStkM"
- `0x4a0794` — "BC_TrnStkC"
- `0x4a07a0` — "BC_TrnStkM"
- `0x4a07ac` — "BC_Upgrade"
- `0x4a07b8` — "BC_UpgSpread"
- `0x4a07c8` — "BC_Repair"
- `0x4a07d4` — "IWMove"
- `0x4a07dc` — "IWHallMove"

### Pseudocode Ghidra

```c
void FUN_00440567(void)

{
  double dVar1;
  undefined1 uVar2;
  short sVar3;
  short sVar4;
  undefined4 uVar5;
  int in_ECX;
  int iVar6;
  undefined2 extraout_var;
  uint uVar7;
  int *piVar8;
  int *piVar9;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined *local_22c;
  undefined *local_228;
  undefined2 local_1d0 [4];
  int local_1c8;
  undefined2 local_1c4 [4];
  int local_1bc;
  undefined2 local_1b8 [4];
  int local_1b0;
  undefined4 local_1ac;
  int local_1a8;
  int local_1a4;
  undefined1 local_1a0 [20];
  undefined1 local_18c [64];
  undefined4 local_14c;
  undefined4 local_148;
  undefined4 local_144;
  int local_140;
  undefined4 local_13c;
  undefined4 local_138;
  undefined4 local_134;
  undefined4 local_ec;
  int local_e8;
  int local_e4;
  undefined4 local_e0;
  int local_dc;
  int local_d8 [7];
  uint local_bc;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  undefined4 local_78;
  int *local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  uint local_58;
  undefined8 local_54;
  uint local_4c;
  undefined *local_48;
  undefined *local_44;
  undefined4 local_40;
  int local_3c;
  int local_38;
  undefined8 local_34;
  int local_2c;
  ushort local_28;
  undefined4 local_24;
  short local_20;
  short local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049184e;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if ((*(int *)(in_ECX + 0x3c) != 0) && (*(int *)(in_ECX + 0x70) != 0)) {
    local_24 = thunk_FUN_0042de0d();
    uVar5 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar5;
    if (DAT_004c2bac == 0) {
      thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
    }
    else {
      uVar11 = 0;
      uVar10 = 0;
      iVar6 = (int)*(short *)(in_ECX + 0x1e);
      uVar5 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar5,iVar6,uVar10,uVar11);
    }
    if (*(int *)(*(int *)(in_ECX + 0x70) + 4) == 0) {
      if ((*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0) ||
         (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 1)) {
        thunk_FUN_00441aae(0);
        thunk_FUN_0042d38a();
        thunk_FUN_0042d87c(in_ECX + 8,1);
      }
      else {
        local_14 = (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 2;
        if (((0x2b < *(int *)(*(int *)(in_ECX + 0x70) + 0x10)) &&
            (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) < 0x2f)) ||
           (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2f)) {
          if (*(short *)(*(int *)(in_ECX + 0x70) + 0x4a) == 0) {
            local_14 = local_14 + 0x1e;
          }
          if (*(short *)(*(int *)(in_ECX + 0x70) + 0x4a) == 1) {
            if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2f) {
              local_14 = local_14 + 0x1e;
            }
            else {
              local_14 = local_14 + 0x14;
            }
          }
          if ((*(short *)(*(int *)(in_ECX + 0x70) + 0x4a) == 2) &&
             (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2f)) {
            local_14 = local_14 + 10;
          }
        }
        thunk_FUN_0040bf98(in_ECX + 8,*(undefined4 *)(in_ECX + 0x70),local_14,0x5a,1,0x10000,0);
        if ((*(int *)(*(int *)(in_ECX + 0x70) + 0x10) != 0x2a) &&
           (*(int *)(*(int *)(in_ECX + 0x70) + 0x14) != 4)) {
          sVar3 = thunk_FUN_00450978();
          local_38 = (int)sVar3;
          local_2c = (int)*(short *)(*(int *)(in_ECX + 0x70) + 0x34);
          local_34 = (double)local_2c / (double)local_38;
          local_3c = thunk_FUN_0040ec89(s_bldgage_004a0590,1);
          if (local_3c == 0) {
            thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a059c,0x1cc,&DAT_004a0598);
          }
          uVar2 = thunk_FUN_0042dd0f(0,(undefined4)local_34,local_34._4_4_,0);
          thunk_FUN_004118df(in_ECX + 8,local_3c,0,local_14 + -0x12,0,0x24,8,2,uVar2);
        }
        if (*(short *)(*(int *)(in_ECX + 0x70) + 0x18) == -1) {
          if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2a) {
            local_1a4 = thunk_FUN_0040ec89(s_bildtone_004a0690,1);
            if (local_1a4 == 0) {
              thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a06a4,0x25b,s_shape_004a069c);
            }
            thunk_FUN_00404770(in_ECX + 8,local_1a4,0x18,0x29,0x28);
            FUN_00472ca0(local_1a0,&DAT_004a06bc,(int)*(short *)(*(int *)(in_ECX + 0x70) + 0x28));
            thunk_FUN_004289c0(in_ECX + 8,0x35,0x22,local_1a0);
            local_1a4 = thunk_FUN_0040ec89(s_tonecrys_004a06c0,1);
            if (local_1a4 == 0) {
              thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a06d4,0x261,s_shape_004a06cc);
            }
            thunk_FUN_00404770(in_ECX + 8,local_1a4,4,0x29,0x46);
            FUN_00472ca0(local_1a0,&DAT_004a06ec,(int)*(short *)(*(int *)(in_ECX + 0x70) + 0x2a));
            thunk_FUN_004289c0(in_ECX + 8,0x35,0x3f,local_1a0);
            local_1a4 = thunk_FUN_0040ec89(s_magctone_004a06f0,1);
            if (local_1a4 == 0) {
              thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0704,0x267,s_shape_004a06fc);
            }
            thunk_FUN_00404770(in_ECX + 8,local_1a4,4,0x29,0x61);
            FUN_00472ca0(local_1a0,&DAT_004a071c,(int)*(short *)(*(int *)(in_ECX + 0x70) + 0x2c));
            thunk_FUN_004289c0(in_ECX + 8,0x35,0x5a,local_1a0);
            local_e0 = thunk_FUN_00429ebe(s_SURPFLOW_004a0720,0);
            FUN_00472ca0(local_18c,s__s__d_004a072c,local_e0,
                         *(undefined4 *)
                          (&DAT_006191f8 + *(int *)(*(int *)(in_ECX + 0x70) + 0x14) * 0x14a0));
            thunk_FUN_004289c0(in_ECX + 8,5,4,local_18c);
            local_13c = thunk_FUN_0046562b(*(undefined4 *)(*(int *)(in_ECX + 0x70) + 0x14),
                                           0xffffffff);
            local_14c = thunk_FUN_0046562b(*(undefined4 *)(*(int *)(in_ECX + 0x70) + 0x14),0);
            local_ec = __ftol();
            thunk_FUN_0041e4c3();
            local_8 = 1;
            local_134 = 0;
            local_138 = *(undefined4 *)(*(int *)(in_ECX + 0x70) + 0x14);
            local_e8 = thunk_FUN_00426fd0(&local_138);
            if (DAT_0049f538 == 3) {
              local_e8 = local_e8 + -3;
            }
            local_148 = DAT_005c37f4;
            DAT_005c37fc = 0;
            DAT_005c37f8 = 0;
            DAT_005c37f4 = 0;
            thunk_FUN_0042704b(in_ECX + 8,&local_138,200,local_e8 + 0x11,1,8,0x10000,0);
            DAT_005c37fc = local_148;
            DAT_005c37f8 = local_148;
            DAT_005c37f4 = local_148;
            local_144 = thunk_FUN_00429ebe(s_POPSTR_004a0734,0);
            FUN_00472ca0(local_1a0,s__s__d_004a073c,local_144,local_13c);
            thunk_FUN_004289c0(in_ECX + 8,0xb6,0x29,local_1a0);
            local_1ac = thunk_FUN_00429ebe(s_WORKSTR_004a0744,0);
            FUN_00472ca0(local_1a0,s__s__d___d____004a074c,local_1ac,local_14c,local_ec);
            thunk_FUN_004289c0(in_ECX + 8,0xb6,0x33,local_1a0);
            local_dc = 0xdc;
            local_e4 = 1;
            local_1a8 = thunk_FUN_0040ec89(s_ACTICON_004a075c,1);
            for (local_140 = 0; local_140 < (int)(uint)DAT_006136b0; local_140 = local_140 + 1) {
              if ((((int)*(short *)(&DAT_00619242 +
                                   *(int *)(*(int *)(in_ECX + 0x70) + 0x14) * 0x14a0) &
                   1 << ((byte)local_140 & 0x1f)) != 0) && (local_1a8 != 0)) {
                thunk_FUN_00404770(in_ECX + 8,local_1a8,local_140,local_dc,local_e4);
              }
              local_dc = local_dc + 10;
              if ((((local_140 == 2) || (local_140 == 5)) || (local_140 == 8)) || (local_140 == 0xb)
                 ) {
                local_dc = 0xdc;
                local_e4 = local_e4 + 10;
                if (local_140 == 0xb) {
                  local_dc = 0xe1;
                }
              }
            }
            local_8 = 0xffffffff;
            thunk_FUN_0041e4d9();
          }
        }
        else {
          local_70 = thunk_FUN_00450385();
          local_80 = (int)*(short *)(local_70 + 0x60);
          local_5c = (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 2 + -0x28;
          local_68 = 5;
          local_7c = thunk_FUN_0040ec89(s_bildicon_004a05b4,1);
          if (local_7c == 0) {
            thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a05c8,0x1dd,s_shape_004a05c0);
          }
          local_64 = *(int *)(*(int *)(in_ECX + 0x70) + 0x14) + 4;
          if (local_64 < 4) {
            local_64 = 4;
          }
          if (7 < local_64) {
            local_64 = 7;
          }
          for (local_6c = 0; local_6c < local_80; local_6c = local_6c + 1) {
            thunk_FUN_00404770(in_ECX + 8,local_7c,local_64,local_5c,local_68);
            local_5c = local_5c + 8;
            if (local_6c == 4) {
              local_68 = local_68 + 8;
              local_5c = (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 2 + -0x28;
            }
          }
          local_5c = 8;
          local_68 = 0x14;
          local_40 = 6;
          local_78 = 0x37;
          local_4c = thunk_FUN_0042dd0f(4);
          local_4c = local_4c & 0xff;
          sVar3 = *(short *)(*(int *)(in_ECX + 0x70) + 0x2a);
          sVar4 = thunk_FUN_0045cd27();
          local_54 = (double)(int)sVar3 / (double)(int)sVar4;
          if (local_54 < 0.0) {
            local_54 = 0.0;
          }
          if (1.0 < local_54) {
            local_54 = 1.0;
          }
          local_7c = thunk_FUN_0040ec89(s_tonecrys_004a05e0,1);
          if (local_7c == 0) {
            thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a05f4,0x1f8,s_shape_004a05ec);
          }
          thunk_FUN_00404770(in_ECX + 8,local_7c,4,local_5c + 3,local_68 + -3);
          local_7c = thunk_FUN_0040ec89(s_taskicon_004a060c,1);
          if (local_7c == 0) {
            thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0620,0x1fc,s_shape_004a0618);
          }
          uVar2 = thunk_FUN_0042dd0f(0,(undefined4)local_54,local_54._4_4_,1);
          thunk_FUN_004118df(in_ECX + 8,local_7c,8,local_5c,local_68,local_40,local_78,2,uVar2);
          if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2f) {
            local_5c = 0x23;
            sVar3 = *(short *)(*(int *)(in_ECX + 0x70) + 0x2c);
            sVar4 = thunk_FUN_0045cd27();
            local_54 = (double)(int)sVar3 / (double)(int)sVar4;
            if (local_54 < 0.0) {
              local_54 = 0.0;
            }
            if (1.0 < local_54) {
              local_54 = 1.0;
            }
            local_7c = thunk_FUN_0040ec89(s_magctone_004a0638,1);
            if (local_7c == 0) {
              thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a064c,0x207,s_shape_004a0644);
            }
            thunk_FUN_00404770(in_ECX + 8,local_7c,4,local_5c + 3,local_68 + -3);
            local_7c = thunk_FUN_0040ec89(s_taskicon_004a0664,1);
            if (local_7c == 0) {
              thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0678,0x20b,s_shape_004a0670);
            }
            uVar2 = thunk_FUN_0042dd0f(0,(undefined4)local_54,local_54._4_4_,1);
            thunk_FUN_004118df(in_ECX + 8,local_7c,8,local_5c,local_68,local_40,local_78,2,uVar2);
            if (-1 < *(short *)(in_ECX + 0x74)) {
              local_88 = (int)*(short *)(&DAT_006188e4 + *(short *)(in_ECX + 0x74) * 0x2c);
              if (*(short *)(*(int *)(in_ECX + 0x70) + 0x2a) < local_88) {
                local_4c = thunk_FUN_0042dd0f(2);
                local_4c = local_4c & 0xff;
              }
              dVar1 = (double)local_88;
              sVar3 = thunk_FUN_0045cd27();
              local_54 = dVar1 / (double)(int)sVar3;
              if (local_54 < 0.0) {
                local_54 = 0.0;
              }
              if (1.0 < local_54) {
                local_54 = 1.0;
              }
              thunk_FUN_0041179e(in_ECX + 8,0xf,0x14,3,local_78,local_4c,(undefined4)local_54,
                                 local_54._4_4_,1,1);
              local_4c = thunk_FUN_0042dd0f(4);
              local_4c = local_4c & 0xff;
              local_8c = thunk_FUN_00450385();
              if (local_8c == 0) {
                local_84 = (int)*(short *)(&DAT_006188e2 + *(short *)(in_ECX + 0x74) * 0x2c);
              }
              else {
                local_84 = thunk_FUN_0045d9c1(CONCAT22(extraout_var,*(undefined2 *)(in_ECX + 0x74)))
                ;
              }
              if (*(short *)(*(int *)(in_ECX + 0x70) + 0x2c) < local_84) {
                local_4c = thunk_FUN_0042dd0f(2);
                local_4c = local_4c & 0xff;
              }
              dVar1 = (double)local_84;
              sVar3 = thunk_FUN_0045cd27();
              local_54 = dVar1 / (double)(int)sVar3;
              if (local_54 < 0.0) {
                local_54 = 0.0;
              }
              if (1.0 < local_54) {
                local_54 = 1.0;
              }
              thunk_FUN_0041179e(in_ECX + 8,0x2a,0x14,3,local_78,local_4c,(undefined4)local_54,
                                 local_54._4_4_,1,1);
            }
          }
          thunk_FUN_0044034e();
          if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2f) {
            local_228 = &DAT_004a04b8;
          }
          else {
            local_228 = &DAT_004a0498;
          }
          local_44 = local_228;
          if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2f) {
            local_22c = &DAT_004a04c8;
          }
          else {
            local_22c = &DAT_004a04a8;
          }
          local_48 = local_22c;
          for (local_60 = 0; local_60 < 6; local_60 = local_60 + 1) {
            if (*(short *)(in_ECX + 0x78 + local_60 * 2) != -1) {
              local_74 = &DAT_006137b8 + *(short *)(in_ECX + 0x78 + local_60 * 2) * 0x13;
              if (*local_74 != -1) {
                piVar8 = local_74;
                piVar9 = local_d8;
                for (iVar6 = 0x13; iVar6 != 0; iVar6 = iVar6 + -1) {
                  *piVar9 = *piVar8;
                  piVar8 = piVar8 + 1;
                  piVar9 = piVar9 + 1;
                }
                local_8 = 0;
                local_bc = local_bc | 2;
                local_14 = (int)*(short *)(local_44 + local_60 * 2);
                local_18 = (int)*(short *)(local_48 + local_60 * 2);
                local_58 = (uint)(*(int **)(DAT_005dc64c + 0x170) == local_74);
                thunk_FUN_0042704b(in_ECX + 8,local_d8,local_14,local_18,1,8,0x10000,local_58);
                local_8 = 0xffffffff;
                thunk_FUN_0041e4d9();
              }
            }
          }
        }
        local_1c = 0xb2;
        local_20 = 1;
        local_28 = *(ushort *)(&DAT_00619242 + *(int *)(*(int *)(in_ECX + 0x70) + 0x14) * 0x14a0);
        if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2c) {
          local_1b8[0] = 0;
          local_1b8[1] = 1;
          local_1b8[2] = 3;
          for (local_1b0 = 0; local_1b0 < 3; local_1b0 = local_1b0 + 1) {
            uVar7 = (int)(short)local_28 & 1 << ((byte)local_1b8[local_1b0] & 0x1f);
            if (uVar7 != 0) {
              thunk_FUN_0043fb30(in_ECX + 8,(int)local_1c,(int)local_20,
                                 CONCAT22((short)(uVar7 >> 0x10),local_1b8[local_1b0]));
              local_1c = local_1c + 10;
            }
          }
          if (((*(uint *)(*(int *)(in_ECX + 0x70) + 0x14) & 1) != 0) && ((local_28 & 4) != 0)) {
            thunk_FUN_0043fb30(in_ECX + 8,(int)local_1c,(int)local_20,2);
          }
          if ((local_28 & 0x1000) != 0) {
            thunk_FUN_0043fb30(in_ECX + 8,0x10,0x15,0xc);
          }
        }
        else if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2d) {
          local_1c4[0] = 6;
          local_1c4[1] = 7;
          local_1c4[2] = 5;
          for (local_1bc = 0; local_1bc < 3; local_1bc = local_1bc + 1) {
            uVar7 = (int)(short)local_28 & 1 << ((byte)local_1c4[local_1bc] & 0x1f);
            if (uVar7 != 0) {
              thunk_FUN_0043fb30(in_ECX + 8,(int)local_1c,(int)local_20,
                                 CONCAT22((short)(uVar7 >> 0x10),local_1c4[local_1bc]));
              local_1c = local_1c + 10;
            }
          }
          if (((*(uint *)(*(int *)(in_ECX + 0x70) + 0x14) & 1) == 0) && ((local_28 & 4) != 0)) {
            thunk_FUN_0043fb30(in_ECX + 8,(int)local_1c,(int)local_20,2);
          }
          if ((local_28 & 0x1000) != 0) {
            thunk_FUN_0043fb30(in_ECX + 8,0x10,0x15,0xc);
          }
        }
        else if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2e) {
          local_1d0[0] = 10;
          local_1d0[1] = 0xb;
          local_1d0[2] = 9;
          for (local_1c8 = 0; local_1c8 < 3; local_1c8 = local_1c8 + 1) {
            uVar7 = (int)(short)local_28 & 1 << ((byte)local_1d0[local_1c8] & 0x1f);
            if (uVar7 != 0) {
              thunk_FUN_0043fb30(in_ECX + 8,(int)local_1c,(int)local_20,
                                 CONCAT22((short)(uVar7 >> 0x10),local_1d0[local_1c8]));
              local_1c = local_1c + 10;
            }
          }
          if (((*(uint *)(*(int *)(in_ECX + 0x70) + 0x14) & 1) == 0) && ((local_28 & 4) != 0)) {
            thunk_FUN_0043fb30(in_ECX + 8,(int)local_1c,(int)local_20,2);
          }
          if ((local_28 & 0x1000) != 0) {
            thunk_FUN_0043fb30(in_ECX + 8,0x10,0x15,0xc);
          }
        }
        else if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2f) {
          if ((local_28 & 0x100) != 0) {
            thunk_FUN_0043fb30(in_ECX + 8,0x2b,0x15,8);
          }
        }
        else if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2a) {
          if ((local_28 & 0x2000) != 0) {
            thunk_FUN_0043fb30(in_ECX + 8,0x3f,0xe,0xd);
          }
          if ((local_28 & 0x10) != 0) {
            thunk_FUN_0043fb30(in_ECX + 8,0xad,0x10,4);
          }
        }
        thunk_FUN_0046c3bc(s_BC_OnOff_004a0764,0xb,0,0);
        thunk_FUN_0046c3bc(s_BC_HallStkB_004a0770,0xb,0,0);
        thunk_FUN_0046c3bc(s_BC_HallStkC_004a077c,0xb,0,0);
        thunk_FUN_0046c3bc(s_BC_HallStkM_004a0788,0xb,0,0);
        thunk_FUN_0046c3bc(s_BC_TrnStkC_004a0794,0xb,0,0);
        thunk_FUN_0046c3bc(s_BC_TrnStkM_004a07a0,0xb,0,0);
        thunk_FUN_0046c3bc(s_BC_Upgrade_004a07ac,0xb,0,0);
        thunk_FUN_0046c3bc(s_BC_UpgSpread_004a07b8,0xb,0,0);
        thunk_FUN_0046c3bc(s_BC_Repair_004a07c8,0xb,0,0);
        thunk_FUN_0046c3bc(s_IWMove_004a07d4,0xb,0,0);
        thunk_FUN_0046c3bc(s_IWHallMove_004a07dc,0xb,0,0);
        thunk_FUN_0042d38a();
        thunk_FUN_0042d87c(in_ECX + 8,1);
      }
    }
    else {
      thunk_FUN_00441b36(0);
      thunk_FUN_0042d38a();
      thunk_FUN_0042d87c(in_ECX + 8,1);
    }
  }
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

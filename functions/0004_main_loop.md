# FUN_0041c46f — 0x41c46f

- Classification : `internal`
- Corps : `0x41c46f–0x41cf85`
- État : pseudocode obtenu
- Evidence : `ev_a3a1136454b116409a3a18908d27e23488bf809cdcb8d28b4d4d0805f05688e3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

## Observations Ghidra

Appels directs observés :
- `0x40119f` — `thunk_FUN_0046c371` (thunk)
- `0x401267` — `thunk_FUN_0045a306` (thunk)
- `0x401276` — `thunk_FUN_0042dd95` (thunk)
- `0x401294` — `thunk_FUN_004289ec` (thunk)
- `0x40144c` — `thunk_FUN_0042cc24` (thunk)
- `0x401465` — `thunk_FUN_0046cbe0` (thunk)
- `0x4014a6` — `thunk_FUN_0040f6f7` (thunk)
- `0x4014ba` — `thunk_FUN_0042dd47` (thunk)
- `0x401591` — `thunk_FUN_0046bdee` (thunk)
- `0x40172b` — `thunk_FUN_0045a3f1` (thunk)
- `0x401749` — `thunk_FUN_00414c97` (thunk)
- `0x4017a8` — `thunk_FUN_00413e71` (thunk)
- `0x4017df` — `thunk_FUN_0041be72` (thunk)
- `0x4017f3` — `thunk_FUN_0040fb84` (thunk)
- `0x401825` — `thunk_FUN_0040f73f` (thunk)
- `0x401875` — `thunk_FUN_0040fc15` (thunk)
- `0x4018bb` — `thunk_FUN_0045aba9` (thunk)
- `0x401947` — `thunk_FUN_00454d1f` (thunk)
- `0x4019ce` — `thunk_FUN_0046cd22` (thunk)
- `0x4019e2` — `thunk_FUN_0046c1b4` (thunk)
- `0x401af5` — `thunk_FUN_004153b8` (thunk)
- `0x401c30` — `thunk_FUN_0042de03` (thunk)
- `0x401d25` — `thunk_FUN_0040f966` (thunk)
- `0x401d43` — `thunk_FUN_00413e8a` (thunk)
- `0x401ded` — `thunk_FUN_0042d38a` (thunk)
- `0x401e01` — `thunk_FUN_0042ef17` (thunk)
- `0x401e83` — `thunk_FUN_0046be81` (thunk)
- `0x401e8d` — `thunk_FUN_0041d0da` (thunk)
- `0x401eba` — `thunk_FUN_0040f752` (thunk)
- `0x401ee7` — `thunk_FUN_00408a25` (thunk)
- `0x401ef6` — `thunk_FUN_0041beac` (thunk)
- `0x401f64` — `thunk_FUN_00414b64` (thunk)
- `0x401f82` — `thunk_FUN_0046c640` (thunk)
- `0x402013` — `thunk_FUN_0045aafd` (thunk)
- `0x4020a4` — `thunk_FUN_0042c4cf` (thunk)
- `0x40213a` — `thunk_FUN_00455833` (thunk)
- `0x40218a` — `thunk_FUN_00410765` (thunk)
- `0x4021b7` — `thunk_FUN_0046ae19` (thunk)
- `0x402298` — `thunk_FUN_00414ad0` (thunk)
- `0x4022b6` — `thunk_FUN_00469f56` (thunk)
- `0x4022bb` — `thunk_FUN_0042d3fb` (thunk)
- `0x4022de` — `thunk_FUN_0042d9cd` (thunk)
- `0x402324` — `thunk_FUN_0041be90` (thunk)
- `0x402329` — `thunk_FUN_0042d28f` (thunk)
- `0x402360` — `thunk_FUN_00469dfc` (thunk)
- `0x4023fb` — `thunk_FUN_00466ce2` (thunk)
- `0x402491` — `thunk_FUN_0042dd0f` (thunk)
- `0x4024dc` — `thunk_FUN_0041cfdf` (thunk)
- `0x4024f0` — `thunk_FUN_004642a3` (thunk)
- `0x472c6c` — `__ftol` (interne)
- `0x472ca0` — `FUN_00472ca0` (interne)
- `0x474b90` — `FUN_00474b90` (interne)

Chaînes référencées observées :
- `0x49caa8` — `data\logo.gif`
- `0x49cab8` — `data\logo.pal`
- `0x49cac8` — `windows.txt`
- `0x49cad4` — `effects.txt`
- `0x49cae0` — `result==TRUE`
- `0x49caf0` — `C:\float\src\float.cpp`
- `0x49cb08` — `fltinf.txt`
- `0x49cb14` — `bldinf.txt`
- `0x49cb20` — `result==TRUE`
- `0x49cb30` — `C:\float\src\float.cpp`
- `0x49cb48` — `xyzzy`
- `0x49cb50` — `Init time: %.2f`
- `0x49cb60` — `start`
- `0x49cb70` — `%3.1f (%d ms; %.1f ms) (L %d %.1f;F %d %.1f;A %d)`
- `0x49cba4` — `Cache total:  %dK`
- `0x49cbb8` — `Cache buffer: %dK`
- `0x49cbcc` — `(%d,%d)`
- `0x49cbd4` — `goodrefresh`
- `0x49cbe0` — `C:\float\src\float.cpp`

## Interprétation

Cette procédure fait partie de l’initialisation ou de la boucle principale d’après les API, appels et chaînes visibles ; les noms de fonctions/données restent ceux fournis ou reconstruits par Ghidra.

## Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0041c46f(void)

{
  int iVar1;
  uint *puVar2;
  uint *puVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined4 local_2b0;
  undefined4 local_2ac;
  undefined4 local_2a8;
  undefined4 local_2a4;
  undefined4 local_2a0;
  uint local_29c [5];
  int local_288;
  undefined4 local_284;
  undefined1 local_280 [52];
  undefined4 local_24c;
  undefined1 local_248 [52];
  double local_214;
  undefined8 local_20c;
  uint local_204;
  undefined4 local_200;
  undefined8 local_1fc;
  undefined8 local_1f4;
  undefined4 local_1ec;
  undefined4 local_1e8;
  undefined4 local_1e4;
  undefined4 local_1e0;
  undefined4 local_1dc;
  undefined4 local_1d8;
  int local_1d4;
  uint local_1d0;
  int local_1cc;
  int local_1c8;
  uint local_1c4;
  uint local_1c0;
  uint local_1bc;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  float local_94;
  uint local_90;
  undefined1 local_8c [80];
  int local_3c;
  undefined8 local_38;
  int local_30;
  uint local_2c;
  undefined *local_28;
  uint local_24;
  uint local_20;
  undefined4 local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491552;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_1c = thunk_FUN_0041be72();
  if (DAT_004c2b98 != 0) {
    thunk_FUN_0040f6f7();
    local_8 = 0;
    thunk_FUN_0040f752(s_data_logo_gif_0049caa8,0x8000);
    local_ac = thunk_FUN_0040fb84();
    thunk_FUN_0040f966();
    thunk_FUN_0040f752(s_data_logo_pal_0049cab8,0x8000);
    thunk_FUN_0040fc15(&DAT_00630730,0x300);
    thunk_FUN_0040f966();
    thunk_FUN_00410765(&DAT_00630730,0,0x100);
    local_a4 = 0;
    local_a0 = 0;
    local_9c = 0x27f;
    local_98 = 0x1df;
    local_a8 = thunk_FUN_0042d28f();
    thunk_FUN_00408a25(&local_a8,local_ac,&DAT_004b28f0);
    thunk_FUN_0042d38a();
    thunk_FUN_0042d9cd();
    thunk_FUN_0042cc24();
    for (local_30 = 0; local_30 < 0x101; local_30 = local_30 + 4) {
      thunk_FUN_00410765(&DAT_00630730,0);
    }
    thunk_FUN_00414c97();
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
  }
  thunk_FUN_0046cd22();
  thunk_FUN_0046cbe0(0,&LAB_00401474);
  thunk_FUN_0046cbe0(1,&LAB_00401528);
  thunk_FUN_0046cbe0(2,&LAB_00401ea6);
  thunk_FUN_0046cbe0(3,thunk_FUN_0042fa0f);
  thunk_FUN_0046cbe0(7,&LAB_0040111d);
  thunk_FUN_0046cbe0(8,&LAB_00401091);
  local_18 = thunk_FUN_004153b8();
  if (local_18 != 1) {
    thunk_FUN_00414b64(s_C__float_src_float_cpp_0049caf0,0x223,s_result__TRUE_0049cae0);
  }
  thunk_FUN_00454d1f();
  local_18 = thunk_FUN_00455833();
  if (local_18 != 1) {
    thunk_FUN_00414b64(s_C__float_src_float_cpp_0049cb30,0x228,s_result__TRUE_0049cb20);
  }
  thunk_FUN_004642a3();
  thunk_FUN_0041cfdf();
  if (DAT_004c2b98 != 0) {
    for (local_30 = 0; local_30 < 0x101; local_30 = local_30 + 4) {
      thunk_FUN_00410765(&DAT_00630730,0);
    }
  }
  thunk_FUN_00413e71();
  if (DAT_004befe4 == 1) {
    thunk_FUN_0046c640(0,1);
  }
  else {
    thunk_FUN_0046c640(8,1);
  }
  local_14 = 0;
  local_24 = 0;
  local_8c[0] = 0;
  local_2c = 0;
  local_3c = 0;
  local_20 = thunk_FUN_0041be90();
  local_94 = (float)local_20 / (float)(int)DAT_004c2b54;
  thunk_FUN_00414ad0(s_Init_time____2f_0049cb50,(double)local_94);
  thunk_FUN_0045aba9(s_start_0049cb60,0,0);
  local_90 = FUN_00474b90();
  local_90 = local_90 & 1;
  local_28 = &DAT_0049cb68;
  DAT_0049cb6c = (char)local_90 + '1';
  thunk_FUN_0045aafd(&DAT_0049cb68,0,1,1);
  for (local_30 = 0; local_30 < 10; local_30 = local_30 + 1) {
    thunk_FUN_0045a3f1();
  }
  while (iVar1 = thunk_FUN_0042ef17(), iVar1 == 1) {
    if ((DAT_004c2b6c == 0) || (DAT_004c2bb8 != 0)) {
      if (DAT_004c2b70 != 0) {
        thunk_FUN_0046c1b4(4,1,0);
        if (DAT_00630a8c == 0) {
          thunk_FUN_0042dd47();
        }
        else {
          thunk_FUN_0042dd47();
        }
        thunk_FUN_0046c371(DAT_0062c6bc,8,0,0);
        DAT_0062c6bc = 0xffffffff;
        thunk_FUN_0046be81();
        DAT_004c2b70 = 0;
      }
      local_1cc = thunk_FUN_00469f56();
      if (local_1cc == 0) break;
      local_1c0 = 0;
      local_1bc = 0;
      local_1d0 = 0;
      local_1d4 = 0;
      for (local_1c8 = 0; local_1c8 < DAT_004bf110 + _DAT_004bf114; local_1c8 = local_1c8 + 1) {
        thunk_FUN_00413e8a();
        if ((DAT_004bf120 != 0) && (DAT_004bf124 == 0)) {
          local_1d8 = thunk_FUN_0041be72();
          thunk_FUN_00466ce2();
          thunk_FUN_0046bdee();
          iVar1 = thunk_FUN_0041be90();
          local_1c0 = local_1c0 + iVar1;
          local_1d0 = local_1d0 + _DAT_004c2bc4;
          local_1bc = local_1bc + _DAT_004c2bc0;
          local_1d4 = local_1d4 + 1;
        }
        if ((DAT_004c2b80 != 0) && (DAT_004c2b6c == 0)) {
          thunk_FUN_0045a3f1();
        }
      }
      if (DAT_005e1758 == 0) {
        if ((DAT_004c2b6c == 0) || ((DAT_004c2bb8 != 0 && (DAT_004c2b84 != 0)))) {
          thunk_FUN_0046ae19();
        }
        if (DAT_004c2b78 != 0) {
          if (local_24 % 10 == 0) {
            local_204 = thunk_FUN_0041be90();
            if (local_204 == 0) {
              local_38 = 1000000.0;
            }
            else {
              local_38 = ((double)DAT_004c2b54 * 10.0) / (double)local_204;
            }
            local_14 = local_14 + local_204;
            local_200 = __ftol();
            local_1f4 = 0.0;
            local_20c = 0.0;
            local_1fc = 0.0;
            if (local_1d4 != 0) {
              local_214 = (1000.0 / (double)local_1d4) / (double)DAT_004c2b54;
              local_1f4 = (double)local_1c0 * local_214;
              local_20c = (double)local_1d0 * local_214;
              local_1fc = (double)local_1bc * local_214;
            }
            FUN_00472ca0(local_8c,s__3_1f___d_ms____1f_ms___L__d___1_0049cb70,(undefined4)local_38,
                         local_38._4_4_,local_200,(undefined4)local_1f4,local_1f4._4_4_,DAT_004c2bbc
                         ,(undefined4)local_1fc,local_1fc._4_4_,DAT_006183b8,(undefined4)local_20c,
                         local_20c._4_4_);
          }
          local_1e8 = 0;
          local_1e4 = 0;
          local_1e0 = 0x27f;
          local_1dc = 0x1df;
          local_1ec = thunk_FUN_0042d28f();
          uVar7 = CONCAT44(0xb,local_8c);
          uVar6 = 0x1cc;
          uVar5 = 0;
          puVar4 = &local_1ec;
          thunk_FUN_0042de03(puVar4,0,0x1cc,local_8c);
          thunk_FUN_004289ec(puVar4,uVar5,uVar6,uVar7);
          thunk_FUN_0042d38a();
        }
        if (DAT_004c2b7c != 0) {
          local_24c = thunk_FUN_0041beac();
          FUN_00472ca0(local_248,s_Cache_total___dK_0049cba4);
          thunk_FUN_0042dd95(0x140,0x1bd);
          local_24c = DAT_00630728;
          FUN_00472ca0(local_248,s_Cache_buffer___dK_0049cbb8);
          thunk_FUN_0042dd95(0x140,0x1cc);
        }
        if (DAT_004c2b8c != 0) {
          local_288 = (int)DAT_00630a3e;
          local_284 = 0x1cc;
          if (0xf0 < local_288) {
            local_284 = 0;
          }
          FUN_00472ca0(local_280,s___d__d__0049cbcc,(int)DAT_00630a3c);
          thunk_FUN_0042dd95(500,local_284);
        }
        if (DAT_004c2bd0 != '\0') {
          puVar2 = (uint *)thunk_FUN_0042de03();
          puVar3 = local_29c;
          for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar3 = *puVar2;
            puVar2 = puVar2 + 1;
            puVar3 = puVar3 + 1;
          }
          local_29c[1] = thunk_FUN_0042dd0f();
          local_29c[1] = local_29c[1] & 0xff;
          local_29c[3] = 1;
          local_2ac = 0;
          local_2a8 = 0;
          local_2a4 = 0x27f;
          local_2a0 = 0x1df;
          local_2b0 = thunk_FUN_0042d28f();
          thunk_FUN_004289ec(&local_2b0,0,0x1cc,&DAT_004c2bd0,10);
          thunk_FUN_0042d38a();
        }
        local_1c4 = 0;
        if (DAT_004c2b60 != 0) {
          local_1c4 = DAT_004c2b54 / DAT_004c2b60;
        }
        do {
          local_2c = thunk_FUN_0041be90();
        } while (local_2c < local_1c4);
        local_3c = local_3c + local_2c;
        if (((DAT_004c2b6c == 0) || ((DAT_004c2bb8 != 0 && (DAT_004c2b84 != 0)))) &&
           (iVar1 = thunk_FUN_0042cc24(), iVar1 == 0)) {
          thunk_FUN_00414b64(s_C__float_src_float_cpp_0049cbe0);
        }
        local_24 = local_24 + 1;
        DAT_004c2b64 = DAT_004c2b64 + 1;
      }
    }
  }
  thunk_FUN_0041d0da();
  thunk_FUN_0045a306();
  thunk_FUN_00469dfc();
  thunk_FUN_0042dd0f();
  thunk_FUN_0042d3fb();
  thunk_FUN_0042c4cf();
  *unaff_FS_OFFSET = local_10;
  return 0;
}
```

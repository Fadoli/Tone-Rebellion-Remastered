# 0016_batch_0012 — détails (3/4)

## FUN_00455833 — 0x455833

- Classification : internal
- Corps : `0x455833–0x456a12`
- État : pseudocode obtenu
- Evidence : `ev_5d60033e6cc433f212a51343e2761e910c21c813cc1727a5c0375a566c73d999`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401154` — `thunk_FUN_00414b91`
- `0x4013e8` — `thunk_FUN_00415f1e`
- `0x401acd` — `thunk_FUN_0040ebde`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472f10` — `FUN_00472f10`
- `0x474b20` — `_memset`
- `0x477b60` — `FUN_00477b60`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x4a2e1c` — "%s %s"
- `0x4a2e24` — "numargs==2"
- `0x4a2e30` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2e4c` — "SHAPE"
- `0x4a2e54` — "%s %s"
- `0x4a2e5c` — "numargs==2"
- `0x4a2e68` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2e8c` — "%s %d %d %d"
- `0x4a2e98` — "numargs>=3"
- `0x4a2ea4` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2ec8` — "%s %d %d %d %c"
- `0x4a2ed8` — "numargs==5"
- `0x4a2ee4` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2f08` — "%s %d %d"
- `0x4a2f14` — "numargs==3"
- `0x4a2f20` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2f44` — "%s %d %d %d %c %d"
- `0x4a2f58` — "numargs==6"
- `0x4a2f64` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2f88` — "%s %d %d %d %c %d %d,%d"
- `0x4a2fa0` — "numargs==8"
- `0x4a2fac` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2fd0` — "%s %d %d %d %c %d %d %d,%d %s"
- `0x4a2ff0` — "numargs>=9"
- `0x4a2ffc` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a3020` — "%s %d %d %d,%d"
- `0x4a3030` — "numargs>=2"
- `0x4a303c` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a3060` — "%s %d %d"
- `0x4a306c` — "numargs==3"
- `0x4a3078` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a3098` — "mNumItems <= MAX_BLDSHP_ITEMS"
- `0x4a30b8` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a30d4` — "mNumBarg<=MAX_BARG_ANM"
- `0x4a30ec` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a3108` — "mNumBase<=MAX_BASE_ANM"
- `0x4a3120` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a313c` — "mNumChug<=MAX_CHUG_ANM"
- `0x4a3154` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a3170` — "mNumCons<=MAX_CONS_ANM"
- `0x4a3188` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a31a4` — "mNumGlyp<=MAX_GLYP_ANM"
- `0x4a31bc` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a31d8` — "mNumInci<=MAX_INCI_ANM"
- `0x4a31f0` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a320c` — "mNumOccu<=MAX_OCCU_ANM"
- `0x4a3224` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a3240` — "mNumProd<=MAX_PROD_ANM"
- `0x4a3258` — "C:\\float\\src\\shapeinf.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_00455833(undefined4 param_1)

{
  char *pcVar1;
  byte *pbVar2;
  undefined2 uVar3;
  int iVar4;
  undefined4 uVar5;
  void *in_ECX;
  short local_dc;
  int local_c0;
  undefined2 local_bc [2];
  int local_b8;
  undefined2 local_b4 [2];
  undefined2 local_b0 [2];
  undefined1 local_ac [4];
  undefined1 local_a8 [16];
  int local_98;
  undefined1 local_94 [16];
  char local_84 [4];
  int local_80;
  char local_7c [16];
  undefined1 local_6c [100];
  undefined2 local_8 [2];
  
  iVar4 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,20000);
  if (iVar4 == 0) {
    *(undefined2 *)((int)in_ECX + 0xa20) = 0;
    _memset(in_ECX,0,0x360);
    *(undefined2 *)((int)in_ECX + 0xb42) = 0;
    *(undefined2 *)((int)in_ECX + 0xc64) = 0;
    *(undefined2 *)((int)in_ECX + 0xd66) = 0;
    *(undefined2 *)((int)in_ECX + 0xe68) = 0;
    *(undefined2 *)((int)in_ECX + 0xefa) = 0;
    *(undefined2 *)((int)in_ECX + 0x10fc) = 0;
    *(undefined2 *)((int)in_ECX + 0x11be) = 0;
    *(undefined2 *)((int)in_ECX + 0x11e0) = 0;
    for (local_98 = 0; local_98 < 0x60; local_98 = local_98 + 1) {
      for (local_c0 = 0; local_c0 < 8; local_c0 = local_c0 + 1) {
        *(undefined2 *)((int)in_ECX + local_c0 * 2 + local_98 * 0x10 + 0x420) = 0xffff;
      }
    }
    do {
      while( true ) {
        while( true ) {
          while( true ) {
            while( true ) {
              while( true ) {
                while( true ) {
                  while( true ) {
                    while( true ) {
                      while( true ) {
                        iVar4 = thunk_FUN_0040f5b3(local_6c,0);
                        if (iVar4 != 0) goto LAB_004567f5;
                        FUN_00472f10(local_6c,&DAT_004a2e10,local_7c);
                        iVar4 = __strcmpi(local_7c,&DAT_004a2e14);
                        if (iVar4 == 0) {
                          local_80 = FUN_00472f10(local_6c,s__s__s_004a2e1c,local_7c,
                                                  (void *)((int)in_ECX +
                                                          *(short *)((int)in_ECX + 0xa20) * 9));
                          if (local_80 != 2) {
                            thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2e30,0x122,
                                               s_numargs__2_004a2e24,local_6c);
                          }
                          *(undefined1 *)((int)in_ECX + *(short *)((int)in_ECX + 0xa20) * 9 + 8) = 0
                          ;
                          uVar3 = thunk_FUN_0040ebde((void *)((int)in_ECX +
                                                             *(short *)((int)in_ECX + 0xa20) * 9));
                          *(undefined2 *)((int)in_ECX + *(short *)((int)in_ECX + 0xa20) * 2 + 0x360)
                               = uVar3;
                          *(short *)((int)in_ECX + 0xa20) = *(short *)((int)in_ECX + 0xa20) + 1;
                        }
                        iVar4 = __strcmpi(local_7c,s_SHAPE_004a2e4c);
                        if (iVar4 != 0) break;
                        local_80 = FUN_00472f10(local_6c,s__s__s_004a2e54,local_7c,local_94);
                        if (local_80 != 2) {
                          thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2e68,299,
                                             s_numargs__2_004a2e5c,local_6c);
                        }
                        uVar3 = thunk_FUN_0040ebde(local_94);
                        *(undefined2 *)((int)in_ECX + *(short *)((int)in_ECX + 0xa20) * 2 + 0x35e) =
                             uVar3;
                      }
                      iVar4 = __strcmpi(local_7c,&DAT_004a2e84);
                      if (iVar4 != 0) break;
                      local_80 = FUN_00472f10(local_6c,s__s__d__d__d_004a2e8c,local_7c,local_a8,
                                              local_ac,local_b0);
                      if (local_80 < 3) {
                        thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2ea4,0x131,
                                           s_numargs>_3_004a2e98,local_6c);
                      }
                      pcVar1 = (char *)((int)in_ECX + *(short *)((int)in_ECX + 0xb42) * 3 + 0xa22);
                      *pcVar1 = (char)local_a8._0_4_ + -1;
                      pcVar1[1] = local_ac[0] + -1;
                      pcVar1[2] = '\0';
                      if (3 < local_80) {
                        pcVar1[2] = (byte)local_b0[0];
                      }
                      *(undefined2 *)
                       ((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x420) =
                           *(undefined2 *)((int)in_ECX + 0xb42);
                      *(short *)((int)in_ECX + 0xb42) = *(short *)((int)in_ECX + 0xb42) + 1;
                    }
                    iVar4 = __strcmpi(local_7c,&DAT_004a2ec0);
                    if (iVar4 != 0) break;
                    local_80 = FUN_00472f10(local_6c,s__s__d__d__d__c_004a2ec8,local_7c,local_a8,
                                            local_ac,local_b0,local_84);
                    if (local_80 != 5) {
                      thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2ee4,0x140,
                                         s_numargs__5_004a2ed8,local_6c);
                    }
                    pbVar2 = (byte *)((int)in_ECX + *(short *)((int)in_ECX + 0xc64) * 6 + 0xb44);
                    *pbVar2 = (char)local_a8._0_4_ - 1;
                    pbVar2[1] = local_ac[0] - 1;
                    pbVar2[2] = (byte)local_b0[0];
                    iVar4 = FUN_00477b60((int)local_84[0]);
                    pbVar2[3] = iVar4 == 0x50;
                    if (pbVar2[3] == 0) {
                      *(ushort *)(pbVar2 + 4) = ((ushort)pbVar2[1] - (ushort)*pbVar2) + 1;
                    }
                    else {
                      *(ushort *)(pbVar2 + 4) = ((ushort)pbVar2[1] - (ushort)*pbVar2) * 2;
                    }
                    *(ushort *)(pbVar2 + 4) = *(short *)(pbVar2 + 4) * (ushort)pbVar2[2];
                    *(undefined2 *)
                     ((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x422) =
                         *(undefined2 *)((int)in_ECX + 0xc64);
                    *(short *)((int)in_ECX + 0xc64) = *(short *)((int)in_ECX + 0xc64) + 1;
                  }
                  iVar4 = __strcmpi(local_7c,&DAT_004a2f00);
                  if (iVar4 != 0) break;
                  local_80 = FUN_00472f10(local_6c,s__s__d__d_004a2f08,local_7c,local_a8,local_ac);
                  if (local_80 != 3) {
                    thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2f20,0x155,
                                       s_numargs__3_004a2f14,local_6c);
                  }
                  pbVar2 = (byte *)((int)in_ECX + *(short *)((int)in_ECX + 0xd66) * 4 + 0xc66);
                  *pbVar2 = (char)local_a8._0_4_ - 1;
                  pbVar2[1] = local_ac[0] - 1;
                  *(ushort *)(pbVar2 + 2) = ((ushort)pbVar2[1] - (ushort)*pbVar2) * 4 + 4;
                  *(undefined2 *)
                   ((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x424) =
                       *(undefined2 *)((int)in_ECX + 0xd66);
                  *(short *)((int)in_ECX + 0xd66) = *(short *)((int)in_ECX + 0xd66) + 1;
                }
                iVar4 = __strcmpi(local_7c,&DAT_004a2f3c);
                if (iVar4 != 0) break;
                local_80 = FUN_00472f10(local_6c,s__s__d__d__d__c__d_004a2f44,local_7c,local_a8,
                                        local_ac,local_b0,local_84,local_b4);
                if (local_80 != 6) {
                  thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2f64,0x164,
                                     s_numargs__6_004a2f58,local_6c);
                }
                pbVar2 = (byte *)((int)in_ECX + *(short *)((int)in_ECX + 0xe68) * 8 + 0xd68);
                *pbVar2 = (char)local_a8._0_4_ - 1;
                pbVar2[1] = local_ac[0] - 1;
                pbVar2[2] = (byte)local_b0[0];
                iVar4 = FUN_00477b60((int)local_84[0]);
                pbVar2[3] = iVar4 == 0x50;
                pbVar2[4] = (byte)local_b4[0];
                if (pbVar2[3] == 0) {
                  *(ushort *)(pbVar2 + 6) = ((ushort)pbVar2[1] - (ushort)*pbVar2) + 1;
                }
                else {
                  *(ushort *)(pbVar2 + 6) = ((ushort)pbVar2[1] - (ushort)*pbVar2) * 2;
                }
                *(ushort *)(pbVar2 + 6) = *(short *)(pbVar2 + 6) * (ushort)pbVar2[2];
                *(undefined2 *)((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x426)
                     = *(undefined2 *)((int)in_ECX + 0xe68);
                *(short *)((int)in_ECX + 0xe68) = *(short *)((int)in_ECX + 0xe68) + 1;
              }
              iVar4 = __strcmpi(local_7c,&DAT_004a2f80);
              if (iVar4 != 0) break;
              local_80 = FUN_00472f10(local_6c,s__s__d__d__d__c__d__d__d_004a2f88,local_7c,local_a8,
                                      local_ac,local_b0,local_84,local_b4,&local_b8,local_bc);
              if (local_80 != 8) {
                thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2fac,0x17b,s_numargs__8_004a2fa0,
                                   local_6c);
              }
              pbVar2 = (byte *)((int)in_ECX + *(short *)((int)in_ECX + 0xefa) * 0xc + 0xe6a);
              *pbVar2 = (char)local_a8._0_4_ - 1;
              pbVar2[1] = local_ac[0] - 1;
              pbVar2[2] = (byte)local_b0[0];
              iVar4 = FUN_00477b60((int)local_84[0]);
              pbVar2[3] = iVar4 == 0x50;
              *(short *)(pbVar2 + 8) = local_b4[0] + -1;
              *(undefined2 *)(pbVar2 + 4) = (undefined2)local_b8;
              *(undefined2 *)(pbVar2 + 6) = local_bc[0];
              if (pbVar2[3] == 0) {
                *(ushort *)(pbVar2 + 10) = ((ushort)pbVar2[1] - (ushort)*pbVar2) + 1;
              }
              else {
                *(ushort *)(pbVar2 + 10) = ((ushort)pbVar2[1] - (ushort)*pbVar2) * 2;
              }
              *(ushort *)(pbVar2 + 10) = *(short *)(pbVar2 + 10) * (ushort)pbVar2[2];
              *(undefined2 *)((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x428) =
                   *(undefined2 *)((int)in_ECX + 0xefa);
              *(short *)((int)in_ECX + 0xefa) = *(short *)((int)in_ECX + 0xefa) + 1;
            }
            iVar4 = __strcmpi(local_7c,&DAT_004a2fc8);
            if (iVar4 != 0) break;
            local_80 = FUN_00472f10(local_6c,s__s__d__d__d__c__d__d__d__d__s_004a2fd0,local_7c,
                                    local_a8,local_ac,local_b0,local_84,local_b4,&local_b8,local_bc,
                                    local_8,local_94);
            if (local_80 < 9) {
              thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2ffc,0x194,s_numargs>_9_004a2ff0,
                                 local_6c);
            }
            pbVar2 = (byte *)((int)in_ECX + *(short *)((int)in_ECX + 0x10fc) * 0x10 + 0xefc);
            *pbVar2 = (char)local_a8._0_4_ - 1;
            pbVar2[1] = local_ac[0] - 1;
            pbVar2[2] = (byte)local_b0[0];
            iVar4 = FUN_00477b60((int)local_84[0]);
            pbVar2[3] = iVar4 == 0x50;
            *(short *)(pbVar2 + 10) = local_b4[0] + -1;
            iVar4 = local_b8 + -1;
            *(undefined2 *)(pbVar2 + 6) = local_bc[0];
            *(undefined2 *)(pbVar2 + 8) = local_8[0];
            pbVar2[0xe] = 0xff;
            pbVar2[0xf] = 0xff;
            if (9 < local_80) {
              uVar3 = thunk_FUN_00415f1e(local_94);
              *(undefined2 *)(pbVar2 + 0xe) = uVar3;
            }
            pbVar2[4] = 0xff;
            pbVar2[5] = 0xff;
            if (iVar4 != -1) {
              *(ushort *)(pbVar2 + 4) = ((short)iVar4 - (ushort)*pbVar2) * (ushort)pbVar2[2];
            }
            if (pbVar2[3] == 0) {
              local_dc = ((ushort)pbVar2[1] - (ushort)*pbVar2) + 1;
            }
            else {
              local_dc = ((ushort)pbVar2[1] - (ushort)*pbVar2) * 2;
            }
            local_dc = local_dc * (ushort)pbVar2[2];
            *(short *)(pbVar2 + 0xc) = local_dc;
            *(undefined2 *)((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x42a) =
                 *(undefined2 *)((int)in_ECX + 0x10fc);
            *(short *)((int)in_ECX + 0x10fc) = *(short *)((int)in_ECX + 0x10fc) + 1;
          }
          iVar4 = __strcmpi(local_7c,&DAT_004a3018);
          if (iVar4 != 0) break;
          local_80 = FUN_00472f10(local_6c,s__s__d__d__d__d_004a3020,local_7c,local_a8,local_ac,
                                  local_b0,local_b4);
          if (local_80 < 2) {
            thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a303c,0x1b9,s_numargs>_2_004a3030,
                               local_6c);
          }
          pcVar1 = (char *)((int)in_ECX + *(short *)((int)in_ECX + 0x11be) * 6 + 0x10fe);
          *pcVar1 = (char)local_a8._0_4_ + -1;
          if (4 < local_80) {
            *(undefined2 *)(pcVar1 + 2) = local_b0[0];
            *(undefined2 *)(pcVar1 + 4) = local_b4[0];
          }
          *(undefined2 *)((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x42c) =
               *(undefined2 *)((int)in_ECX + 0x11be);
          *(short *)((int)in_ECX + 0x11be) = *(short *)((int)in_ECX + 0x11be) + 1;
        }
        iVar4 = __strcmpi(local_7c,&DAT_004a3058);
        if (iVar4 != 0) break;
        local_80 = FUN_00472f10(local_6c,s__s__d__d_004a3060,local_7c,local_a8,local_ac);
        if (local_80 != 3) {
          thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a3078,0x1ca,s_numargs__3_004a306c,
                             local_6c);
        }
        *(char *)((int)in_ECX + *(short *)((int)in_ECX + 0x11e0) * 2 + 0x11c0) =
             (char)local_a8._0_4_ + -1;
        *(char *)((int)in_ECX + *(short *)((int)in_ECX + 0x11e0) * 2 + 0x11c1) = local_ac[0] + -1;
        *(undefined2 *)((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x42e) =
             *(undefined2 *)((int)in_ECX + 0x11e0);
        *(short *)((int)in_ECX + 0x11e0) = *(short *)((int)in_ECX + 0x11e0) + 1;
      }
      iVar4 = __strcmpi(local_7c,&DAT_004a3094);
    } while (iVar4 != 0);
LAB_004567f5:
    if (0x60 < *(short *)((int)in_ECX + 0xa20)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a30b8,0x1d6,
                         s_mNumItems_<__MAX_BLDSHP_ITEMS_004a3098);
    }
    if (0x10 < *(short *)((int)in_ECX + 0x11e0)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a30ec,0x1d7,
                         s_mNumBarg<_MAX_BARG_ANM_004a30d4);
    }
    if (0x60 < *(short *)((int)in_ECX + 0xb42)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a3120,0x1d8,
                         s_mNumBase<_MAX_BASE_ANM_004a3108);
    }
    if (0x30 < *(short *)((int)in_ECX + 0xc64)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a3154,0x1d9,
                         s_mNumChug<_MAX_CHUG_ANM_004a313c);
    }
    if (0xc < *(short *)((int)in_ECX + 0xefa)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a3188,0x1da,
                         s_mNumCons<_MAX_CONS_ANM_004a3170);
    }
    if (0x40 < *(short *)((int)in_ECX + 0xd66)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a31bc,0x1db,
                         s_mNumGlyp<_MAX_GLYP_ANM_004a31a4);
    }
    if (0x20 < *(short *)((int)in_ECX + 0xe68)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a31f0,0x1dc,
                         s_mNumInci<_MAX_INCI_ANM_004a31d8);
    }
    if (0x20 < *(short *)((int)in_ECX + 0x11be)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a3224,0x1dd,
                         s_mNumOccu<_MAX_OCCU_ANM_004a320c);
    }
    if (0x20 < *(short *)((int)in_ECX + 0x10fc)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a3258,0x1de,
                         s_mNumProd<_MAX_PROD_ANM_004a3240);
    }
    uVar5 = 1;
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}
```

---

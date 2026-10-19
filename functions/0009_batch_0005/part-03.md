# 0009_batch_0005 — détails (3/3)

## FUN_004153b8 — 0x4153b8

- Classification : internal
- Corps : `0x4153b8–0x415f1d`
- État : pseudocode obtenu
- Evidence : `ev_a2f6dd8fe47f403c98165ec901d7fc9dac3fe46367845bddaa51759bdfbdbec6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401154` — `thunk_FUN_00414b91`
- `0x4013e8` — `thunk_FUN_00415f1e`
- `0x401acd` — `thunk_FUN_0040ebde`
- `0x401c76` — `thunk_FUN_0045b34c`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472da0` — `FUN_00472da0`
- `0x472f10` — `FUN_00472f10`
- `0x474b20` — `_memset`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x49be08` — "%s %s"
- `0x49be10` — "EFFECT"
- `0x49be18` — "mNumEffectData < MAX_EFFECTDATA"
- `0x49be38` — "C:\\float\\src\\effects.cpp"
- `0x49be54` — "%s %s"
- `0x49be5c` — "numargs==2"
- `0x49be68` — "C:\\float\\src\\effects.cpp"
- `0x49be8c` — "%s %s"
- `0x49be94` — "numargs==2"
- `0x49bea0` — "C:\\float\\src\\effects.cpp"
- `0x49bebc` — "ONESHOT"
- `0x49bec4` — "BULLET"
- `0x49becc` — "LIGHTNING"
- `0x49bed8` — "IMPACT"
- `0x49bee8` — "SPECIAL"
- `0x49bef0` — "SOUNDONLY"
- `0x49befc` — "FALSE"
- `0x49bf04` — "C:\\float\\src\\effects.cpp"
- `0x49bf20` — "REALM"
- `0x49bf28` — "%s %s"
- `0x49bf30` — "numargs==2"
- `0x49bf3c` — "C:\\float\\src\\effects.cpp"
- `0x49bf68` — "FALSE"
- `0x49bf70` — "C:\\float\\src\\effects.cpp"
- `0x49bf8c` — "SHAPE"
- `0x49bf94` — "%s %s"
- `0x49bf9c` — "numargs==2"
- `0x49bfa8` — "C:\\float\\src\\effects.cpp"
- `0x49bfc4` — "Shape not found: %s"
- `0x49bfd8` — "FALSE"
- `0x49bfe0` — "C:\\float\\src\\effects.cpp"
- `0x49bffc` — "SPEED"
- `0x49c004` — "%s %d"
- `0x49c00c` — "numargs==2"
- `0x49c018` — "C:\\float\\src\\effects.cpp"
- `0x49c034` — "SOUND"
- `0x49c03c` — "%s %s"
- `0x49c044` — "numargs==2"
- `0x49c050` — "C:\\float\\src\\effects.cpp"
- `0x49c06c` — "Sound not found: %s"
- `0x49c080` — "FALSE"
- `0x49c088` — "C:\\float\\src\\effects.cpp"
- `0x49c0a4` — "LEVELFRAMES"
- `0x49c0b0` — "%s %d %d,%d %d,%d %d,%d %d,%d"
- `0x49c0d0` — "numargs>=4"
- `0x49c0dc` — "C:\\float\\src\\effects.cpp"
- `0x49c0f8` — "val1 <= MAX_FRAMESEGMENTS"
- `0x49c114` — "C:\\float\\src\\effects.cpp"
- `0x49c130` — "CHAIN"
- `0x49c13c` — "FALSE"
- `0x49c144` — "C:\\float\\src\\effects.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_004153b8(undefined4 param_1)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  void *in_ECX;
  undefined4 local_440;
  undefined1 local_43c [4];
  undefined1 local_438 [4];
  undefined1 local_434 [4];
  undefined4 local_430;
  undefined1 local_42c [4];
  undefined1 local_428 [4];
  undefined1 local_424 [4];
  int local_420 [4];
  int local_410;
  char acStack_40c [864];
  char local_ac [32];
  int local_8c;
  char local_88 [32];
  undefined1 local_68 [100];
  
  iVar3 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,20000);
  if (iVar3 == 0) {
    *(undefined2 *)((int)in_ECX + 0x1200) = 0;
    *(undefined2 *)((int)in_ECX + 0x1482) = 0;
    _memset(in_ECX,0,0x1200);
    for (local_410 = 0; local_410 < 0x60; local_410 = local_410 + 1) {
      acStack_40c[local_410 * 9] = '\0';
    }
    for (local_410 = 0; local_410 < 0x20; local_410 = local_410 + 1) {
      *(undefined2 *)((int)in_ECX + local_410 * 0x14 + 0x1202) = 0xffff;
    }
    while (iVar3 = thunk_FUN_0040f5b3(local_68,0), iVar3 == 0) {
      FUN_00472f10(local_68,s__s__s_0049be08,local_88,local_ac);
      iVar3 = __strcmpi(local_88,s_EFFECT_0049be10);
      if (iVar3 == 0) {
        if (0x5f < *(short *)((int)in_ECX + 0x1200)) {
          thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049be38,0xba,
                             s_mNumEffectData_<_MAX_EFFECTDATA_0049be18);
        }
        local_8c = FUN_00472f10(local_68,s__s__s_0049be54,local_88,
                                (void *)((int)in_ECX + *(short *)((int)in_ECX + 0x1200) * 0x30));
        if (local_8c != 2) {
          thunk_FUN_00414b91(s_C__float_src_effects_cpp_0049be68,0xbe,s_numargs__2_0049be5c,local_68
                            );
        }
        *(undefined1 *)((int)in_ECX + *(short *)((int)in_ECX + 0x1200) * 0x30 + 0xb) = 0;
        *(undefined2 *)((int)in_ECX + *(short *)((int)in_ECX + 0x1200) * 0x30 + 0x24) = 5;
        *(undefined2 *)((int)in_ECX + *(short *)((int)in_ECX + 0x1200) * 0x30 + 0x28) = 0xffff;
        *(short *)((int)in_ECX + 0x1200) = *(short *)((int)in_ECX + 0x1200) + 1;
      }
      else {
        iVar3 = __strcmpi(local_88,&DAT_0049be84);
        if (iVar3 == 0) {
          local_8c = FUN_00472f10(local_68,s__s__s_0049be8c,local_88,local_ac);
          if (local_8c != 2) {
            thunk_FUN_00414b91(s_C__float_src_effects_cpp_0049bea0,200,s_numargs__2_0049be94,
                               local_68);
          }
          iVar3 = __strcmpi(local_ac,s_ONESHOT_0049bebc);
          if (iVar3 == 0) {
            *(undefined4 *)((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0xc) = 0;
          }
          else {
            iVar3 = __strcmpi(local_ac,s_BULLET_0049bec4);
            if (iVar3 == 0) {
              *(undefined4 *)((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0xc) =
                   1;
            }
            else {
              iVar3 = __strcmpi(local_ac,s_LIGHTNING_0049becc);
              if (iVar3 == 0) {
                *(undefined4 *)((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0xc)
                     = 2;
              }
              else {
                iVar3 = __strcmpi(local_ac,s_IMPACT_0049bed8);
                if (iVar3 == 0) {
                  *(undefined4 *)
                   ((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0xc) = 3;
                }
                else {
                  iVar3 = __strcmpi(local_ac,&DAT_0049bee0);
                  if (iVar3 == 0) {
                    *(undefined4 *)
                     ((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0xc) = 4;
                  }
                  else {
                    iVar3 = __strcmpi(local_ac,s_SPECIAL_0049bee8);
                    if (iVar3 == 0) {
                      *(undefined4 *)
                       ((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0xc) = 5;
                    }
                    else {
                      iVar3 = __strcmpi(local_ac,s_SOUNDONLY_0049bef0);
                      if (iVar3 == 0) {
                        *(undefined4 *)
                         ((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0xc) = 6;
                      }
                      else {
                        thunk_FUN_00414b91(s_C__float_src_effects_cpp_0049bf04,0xd9,s_FALSE_0049befc
                                           ,local_68);
                      }
                    }
                  }
                }
              }
            }
          }
        }
        else {
          iVar3 = __strcmpi(local_88,s_REALM_0049bf20);
          if (iVar3 == 0) {
            local_8c = FUN_00472f10(local_68,s__s__s_0049bf28,local_88,local_ac);
            if (local_8c != 2) {
              thunk_FUN_00414b91(s_C__float_src_effects_cpp_0049bf3c,0xdf,s_numargs__2_0049bf30,
                                 local_68);
            }
            iVar3 = __strcmpi(local_ac,&DAT_0049bf58);
            if (iVar3 == 0) {
              *(undefined2 *)((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0x10) =
                   0;
            }
            else {
              iVar3 = __strcmpi(local_ac,&DAT_0049bf5c);
              if (iVar3 == 0) {
                *(undefined2 *)((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0x10)
                     = 1;
              }
              else {
                iVar3 = __strcmpi(local_ac,&DAT_0049bf60);
                if (iVar3 == 0) {
                  *(undefined2 *)
                   ((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0x10) = 2;
                }
                else {
                  iVar3 = __strcmpi(local_ac,&DAT_0049bf64);
                  if (iVar3 == 0) {
                    *(undefined2 *)
                     ((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0x10) = 3;
                  }
                  else {
                    thunk_FUN_00414b91(s_C__float_src_effects_cpp_0049bf70,0xea,s_FALSE_0049bf68,
                                       local_68);
                  }
                }
              }
            }
          }
          else {
            iVar3 = __strcmpi(local_88,s_SHAPE_0049bf8c);
            if (iVar3 == 0) {
              local_8c = FUN_00472f10(local_68,s__s__s_0049bf94,local_88,local_ac);
              if (local_8c != 2) {
                thunk_FUN_00414b91(s_C__float_src_effects_cpp_0049bfa8,0xf0,s_numargs__2_0049bf9c,
                                   local_68);
              }
              sVar1 = thunk_FUN_0040ebde(local_ac);
              if (sVar1 == -1) {
                thunk_FUN_00414ad0(s_Shape_not_found___s_0049bfc4,local_ac);
                thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049bfe0,0xf6,s_FALSE_0049bfd8);
              }
              *(short *)((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0x26) =
                   sVar1;
            }
            else {
              iVar3 = __strcmpi(local_88,s_SPEED_0049bffc);
              if (iVar3 == 0) {
                local_8c = FUN_00472f10(local_68,s__s__d_0049c004,local_88,local_420);
                if (local_8c != 2) {
                  thunk_FUN_00414b91(s_C__float_src_effects_cpp_0049c018,0xfe,s_numargs__2_0049c00c,
                                     local_68);
                }
                *(undefined2 *)((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0x24)
                     = (undefined2)local_420[0];
              }
              else {
                iVar3 = __strcmpi(local_88,s_SOUND_0049c034);
                if (iVar3 == 0) {
                  local_8c = FUN_00472f10(local_68,s__s__s_0049c03c,local_88,local_ac);
                  if (local_8c != 2) {
                    thunk_FUN_00414b91(s_C__float_src_effects_cpp_0049c050,0x106,
                                       s_numargs__2_0049c044,local_68);
                  }
                  if (DAT_004c2b80 != 0) {
                    sVar1 = thunk_FUN_0045b34c(local_ac);
                    if (sVar1 == -1) {
                      thunk_FUN_00414ad0(s_Sound_not_found___s_0049c06c,local_ac);
                      thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c088,0x10e,s_FALSE_0049c080)
                      ;
                    }
                    *(short *)((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0x28)
                         = sVar1;
                  }
                }
                else {
                  iVar3 = __strcmpi(local_88,s_LEVELFRAMES_0049c0a4);
                  if (iVar3 == 0) {
                    local_8c = FUN_00472f10(local_68,s__s__d__d__d__d__d__d__d__d__d_0049c0b0,
                                            local_88,local_420,&local_430,&local_440,local_42c,
                                            local_43c,local_428,local_438,local_424,local_434);
                    if (local_8c < 4) {
                      thunk_FUN_00414b91(s_C__float_src_effects_cpp_0049c0dc,0x118,
                                         s_numargs>_4_0049c0d0,local_68);
                    }
                    *(undefined2 *)
                     ((int)in_ECX + (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0x12) =
                         (undefined2)local_420[0];
                    if (4 < local_420[0]) {
                      thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c114,0x11b,
                                         s_val1_<__MAX_FRAMESEGMENTS_0049c0f8);
                    }
                    for (local_410 = 0; local_410 < local_420[0]; local_410 = local_410 + 1) {
                      *(short *)((int)in_ECX +
                                local_410 * 2 +
                                (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0x14) =
                           (short)*(undefined4 *)(local_42c + local_410 * 4 + -4) + -1;
                      *(short *)((int)in_ECX +
                                local_410 * 2 +
                                (*(short *)((int)in_ECX + 0x1200) + -1) * 0x30 + 0x1c) =
                           (short)*(undefined4 *)(local_43c + local_410 * 4 + -4) + -1;
                    }
                  }
                  else {
                    iVar3 = __strcmpi(local_88,s_CHAIN_0049c130);
                    if (iVar3 == 0) {
                      FUN_00472da0(acStack_40c + (*(short *)((int)in_ECX + 0x1200) + -1) * 9,
                                   local_ac);
                    }
                    else {
                      iVar3 = __strcmpi(local_88,&DAT_0049c138);
                      if (iVar3 == 0) break;
                      thunk_FUN_00414b91(s_C__float_src_effects_cpp_0049c144,0x12a,s_FALSE_0049c13c,
                                         local_68);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    for (local_410 = 0; local_410 < *(short *)((int)in_ECX + 0x1200); local_410 = local_410 + 1) {
      if (acStack_40c[local_410 * 9] == '\0') {
        *(undefined2 *)((int)in_ECX + local_410 * 0x30 + 0x2a) = 0xffff;
      }
      else {
        uVar2 = thunk_FUN_00415f1e(acStack_40c + local_410 * 9);
        *(undefined2 *)((int)in_ECX + local_410 * 0x30 + 0x2a) = uVar2;
      }
    }
    uVar4 = 1;
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}
```

---

## FUN_00415f1e — 0x415f1e

- Classification : internal
- Corps : `0x415f1e–0x415f6c`
- État : pseudocode obtenu
- Evidence : `ev_828b94a4009418370abcdae585e5c3ccd003b876b17ba22f81162ded4304ea4a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x48b100` — `__strcmpi`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00415f1e(char *param_1)

{
  int iVar1;
  int in_ECX;
  uint local_8;
  
  local_8 = 0;
  while( true ) {
    if (0x5f < (int)local_8) {
      return 0xffff;
    }
    iVar1 = __strcmpi(param_1,(char *)(in_ECX + local_8 * 0x30));
    if (iVar1 == 0) break;
    local_8 = local_8 + 1;
  }
  return local_8 & 0xffff;
}
```

---

## FUN_00415f6d — 0x415f6d

- Classification : internal
- Corps : `0x415f6d–0x415fc5`
- État : pseudocode obtenu
- Evidence : `ev_8b35fe2aa3036a409894d98a435a4b61d341be0005e4db65a406bdd1e047a1ce`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a41` — `thunk_FUN_00416ff8`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00415f6d(void)

{
  int in_ECX;
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 0x20; local_8 = local_8 + 1) {
    if (*(short *)(in_ECX + 0x1202 + local_8 * 0x14) != -1) {
      thunk_FUN_00416ff8(CONCAT22((short)((uint)(local_8 * 0x14) >> 0x10),(undefined2)local_8));
    }
  }
  DAT_004c204c = DAT_004c204c + 1;
  return;
}
```

---

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

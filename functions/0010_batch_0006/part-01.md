# 0010_batch_0006 — détails (1/8)

## FUN_0041660b — 0x41660b

- Classification : internal
- Corps : `0x41660b–0x416a4a`
- État : pseudocode obtenu
- Evidence : `ev_09987715f457d6a8829d941c1b81ca3eaf3a415076ed78ee2f1c24db2eb87d9f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013e8` — `thunk_FUN_00415f1e`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49c1c0` — "i<MAX_EFFECTINST"
- `0x49c1d4` — "C:\\float\\src\\effects.cpp"
- `0x49c1f0` — "destsupp"
- `0x49c1f0` — "destsupp"
- `0x49c1fc` — "ascend"
- `0x49c1fc` — "ascend"
- `0x49c204` — "fltarmor"
- `0x49c204` — "fltarmor"
- `0x49c210` — "killbeas"
- `0x49c21c` — "fastprod"
- `0x49c21c` — "fastprod"
- `0x49c228` — "fltarmor"
- `0x49c228` — "fltarmor"
- `0x49c234` — "sacrif"
- `0x49c234` — "sacrif"

### Pseudocode Ghidra

```c
uint FUN_0041660b(int *param_1)

{
  bool bVar1;
  short sVar2;
  int in_ECX;
  char *local_28;
  char *local_1c;
  uint local_14;
  int local_10;
  short *local_c;
  
  if (*(short *)(in_ECX + 0x1482) == 0x20) {
    local_14 = 0xffff;
  }
  else {
    local_14 = 0;
    for (local_c = (short *)(in_ECX + 0x1202); ((int)local_14 < 0x20 && (*local_c != -1));
        local_c = local_c + 10) {
      local_14 = local_14 + 1;
    }
    if (0x1f < (int)local_14) {
      thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c1d4,0x213,s_i<MAX_EFFECTINST_0049c1c0);
    }
    local_c[9] = 0;
    if (param_1[0xb] == 0x13) {
      local_10 = (int)(short)param_1[0xc];
      if (local_10 < 0) {
        local_10 = 0;
      }
      if (0x16 < local_10) {
        local_10 = 0x16;
      }
      bVar1 = true;
      switch(local_10) {
      case 0:
      case 1:
      case 3:
      case 4:
      case 5:
      case 6:
      case 8:
      case 9:
      case 0xb:
      case 0xc:
      case 0xd:
      case 0xf:
      case 0x10:
      case 0x13:
      case 0x16:
        local_1c = (&PTR_s_pspell_0049bd68)[*param_1];
        if (local_10 == 0x10) {
          local_1c = s_destsupp_0049c1f0;
        }
        else if (local_10 == 0x16) {
          local_1c = s_ascend_0049c1fc;
        }
        else if (local_10 == 1) {
          local_1c = s_fltarmor_0049c204;
        }
        sVar2 = thunk_FUN_00415f1e(local_1c);
        local_c[7] = sVar2;
        *local_c = (short)((int)(param_1 + -0x184dee) / 0x4c);
        if (local_10 == 8) {
          local_c[1] = 0;
        }
        else {
          local_c[1] = *(short *)((int)param_1 + 0x32);
        }
        local_c[4] = *(short *)((int)param_1 + 0xe);
        local_c[5] = (short)param_1[4];
        local_c[6] = *(short *)((int)param_1 + 0x12);
        local_c[8] = 0;
        local_c[8] = local_c[8] | (ushort)((param_1[7] & 2U) != 0);
        if (local_10 != 8) {
          local_c[8] = local_c[8] | 2;
        }
        local_c[8] = local_c[8] | 0x100;
        local_c[2] = 0;
        local_c[3] = *(short *)(in_ECX + local_c[7] * 0x30 + 0x14 + local_c[2] * 2);
        break;
      case 2:
      case 7:
      case 0xe:
      case 0x11:
      case 0x12:
      case 0x14:
      case 0x15:
        local_28 = (&PTR_s_pspell_0049bd68)[*param_1];
        if (((local_10 == 2) || (local_10 == 0xe)) || (local_10 == 0x15)) {
          local_28 = s_fastprod_0049c21c;
        }
        else if (local_10 == 0x11) {
          local_28 = s_fltarmor_0049c228;
        }
        else if ((local_10 == 7) || (local_10 == 0x12)) {
          local_28 = s_sacrif_0049c234;
        }
        sVar2 = thunk_FUN_00415f1e(local_28);
        local_c[7] = sVar2;
        *local_c = (short)((int)(param_1 + -0x184dee) / 0x4c);
        local_c[1] = 0;
        local_c[4] = *(short *)((int)param_1 + 0xe);
        local_c[5] = (short)param_1[4];
        local_c[6] = *(short *)((int)param_1 + 0x12);
        local_c[8] = 0;
        local_c[8] = local_c[8] | (ushort)((param_1[7] & 2U) != 0);
        local_c[8] = local_c[8] | 0x100;
        local_c[2] = 0;
        local_c[3] = *(short *)(in_ECX + local_c[7] * 0x30 + 0x14 + local_c[2] * 2);
        break;
      case 10:
        sVar2 = thunk_FUN_00415f1e(s_killbeas_0049c210);
        local_c[7] = sVar2;
        *local_c = (short)((int)(param_1 + -0x184dee) / 0x4c);
        local_c[1] = *(short *)((int)param_1 + 0x32);
        local_c[4] = *(short *)((int)param_1 + 0xe);
        local_c[5] = (short)param_1[4];
        local_c[6] = *(short *)((int)param_1 + 0x12);
        local_c[8] = 0;
        local_c[8] = local_c[8] | (ushort)((param_1[7] & 2U) != 0);
        local_c[8] = local_c[8] | 0x100;
        local_c[2] = 0;
        local_c[3] = *(short *)(in_ECX + local_c[7] * 0x30 + 0x14 + local_c[2] * 2);
        break;
      default:
        bVar1 = false;
      }
      if (bVar1) {
        *(short *)(in_ECX + 0x1482) = *(short *)(in_ECX + 0x1482) + 1;
      }
      else {
        local_14 = 0xffffffff;
      }
      local_14 = local_14 & 0xffff;
    }
    else {
      local_14 = 0xffff;
    }
  }
  return local_14;
}
```

---

## FUN_00416a9a — 0x416a9a

- Classification : internal
- Corps : `0x416a9a–0x416e54`
- État : pseudocode obtenu
- Evidence : `ev_93447689ffdfefd313618e98d43e4c84371b3b13f0e21cf82989be9d7beb280a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013e8` — `thunk_FUN_00415f1e`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49c23c` — "worldevent>=0 && worldevent<WE_NumEvents"
- `0x49c268` — "C:\\float\\src\\effects.cpp"
- `0x49c284` — "i<MAX_EFFECTINST"
- `0x49c298` — "C:\\float\\src\\effects.cpp"
- `0x49c2b4` — "join6"
- `0x49c2b4` — "join6"
- `0x49c2bc` — "levbirth"
- `0x49c2bc` — "levbirth"
- `0x49c2c8` — "fltbirth"
- `0x49c2d4` — "levdeath"
- `0x49c2d4` — "levdeath"
- `0x49c2e0` — "fltdeath"
- `0x49c2ec` — "levbuild"
- `0x49c2ec` — "levbuild"
- `0x49c2f8` — "fltbuild"
- `0x49c304` — "crumble"
- `0x49c304` — "crumble"
- `0x49c30c` — "bridge"
- `0x49c30c` — "bridge"
- `0x49c314` — "FEAT%02d"

### Pseudocode Ghidra

```c
uint FUN_00416a9a(int param_1,int *param_2)

{
  short sVar1;
  int in_ECX;
  undefined4 uVar2;
  undefined4 uVar3;
  char local_20 [16];
  uint local_10;
  char *local_c;
  short *local_8;
  
  if ((param_1 < 0) || (0xc < param_1)) {
    uVar3 = thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c268,0x2a1,
                               s_worldevent>_0____worldevent<WE_N_0049c23c);
  }
  else {
    uVar3 = 0;
  }
  if (*(short *)(in_ECX + 0x1482) != 0x20) {
    local_10 = 0;
    for (local_8 = (short *)(in_ECX + 0x1202); ((int)local_10 < 0x20 && (*local_8 != -1));
        local_8 = local_8 + 10) {
      local_10 = local_10 + 1;
    }
    if ((int)local_10 < 0x20) {
      uVar2 = 0;
    }
    else {
      uVar2 = thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c298,0x2ab,
                                 s_i<MAX_EFFECTINST_0049c284);
    }
    local_8[8] = 0;
    local_8[9] = 0;
    local_c = (char *)0x0;
    switch(param_1) {
    case 0:
      if (param_2[5] == 4) {
        local_c = s_levbirth_0049c2bc;
      }
      else {
        local_c = s_fltbirth_0049c2c8;
      }
      local_8[4] = (short)param_2[2];
      local_8[5] = (short)*param_2;
      local_8[6] = *(short *)((int)param_2 + 2);
      break;
    case 1:
      if (*param_2 == 4) {
        local_c = s_levdeath_0049c2d4;
      }
      else {
        local_c = s_fltdeath_0049c2e0;
      }
      local_8[4] = *(short *)((int)param_2 + 0xe);
      local_8[5] = (short)param_2[4];
      local_8[6] = *(short *)((int)param_2 + 0x12);
      break;
    case 2:
      if (param_2[5] == 4) {
        local_c = s_levbuild_0049c2ec;
      }
      else {
        local_c = s_fltbuild_0049c2f8;
      }
      local_8[4] = (short)param_2[2];
      local_8[5] = (short)*param_2;
      local_8[6] = *(short *)((int)param_2 + 2);
      break;
    case 3:
      local_c = s_bridge_0049c30c;
      local_8[4] = (short)param_2[2];
      local_8[5] = (short)*param_2;
      local_8[6] = *(short *)((int)param_2 + 2);
      break;
    case 4:
      FUN_00472ca0(local_20,s_FEAT_02d_0049c314,
                   (int)(short)(&DAT_005eebf8)[(short)param_2[2] * 0x14f4],param_1,uVar2,uVar3);
      local_c = local_20;
      local_8[4] = (short)param_2[2];
      local_8[5] = (short)*param_2;
      local_8[6] = *(short *)((int)param_2 + 2);
      break;
    case 5:
      local_c = s_join6_0049c2b4;
      local_8[4] = *(short *)((int)param_2 + 0xe);
      local_8[5] = (short)param_2[4];
      local_8[6] = *(short *)((int)param_2 + 0x12);
      break;
    case 7:
      local_c = s_crumble_0049c304;
      local_8[4] = (short)param_2[2];
      local_8[5] = (short)*param_2;
      local_8[6] = *(short *)((int)param_2 + 2);
      break;
    case 9:
      local_c = (char *)(in_ECX + (int)param_2 * 0x30);
      local_8[4] = DAT_0049f53c;
      local_8[5] = *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) + 0x140;
      local_8[6] = 0x78;
      local_8[8] = local_8[8] | 0x80;
      local_8[2] = 0;
    }
    if (local_c != (char *)0x0) {
      sVar1 = thunk_FUN_00415f1e(local_c);
      local_8[7] = sVar1;
      if (local_8[7] != -1) {
        *local_8 = 9999;
        local_8[2] = 0;
        local_8[3] = *(short *)(in_ECX + local_8[7] * 0x30 + 0x14);
        *(short *)(in_ECX + 0x1482) = *(short *)(in_ECX + 0x1482) + 1;
        return local_10 & 0xffff;
      }
    }
  }
  return 0xffff;
}
```

---

## FUN_00416e7d — 0x416e7d

- Classification : internal
- Corps : `0x416e7d–0x416ece`
- État : pseudocode obtenu
- Evidence : `ev_ba8439b830fc15360774814aa1ebebd6f5c32740a12496cd43cc30867239486c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00416e7d(short param_1)

{
  int in_ECX;
  
  if (*(short *)(in_ECX + 0x1202 + param_1 * 0x14) != -1) {
    *(undefined2 *)(in_ECX + 0x1202 + param_1 * 0x14) = 0xffff;
    *(short *)(in_ECX + 0x1482) = *(short *)(in_ECX + 0x1482) + -1;
  }
  return;
}
```

---

## FUN_00416ecf — 0x416ecf

- Classification : internal
- Corps : `0x416ecf–0x416fe3`
- État : pseudocode obtenu
- Evidence : `ev_c3977caadef4915cd2ffe69273a26a310dbc9e4cf5ca36606049b7729bf0f7f2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40173a` — `thunk_FUN_004672a6`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x40250e` — `thunk_FUN_00414fbf`

### Chaînes référencées

- `0x49c320` — "Bad effect Type %d"
- `0x49c334` — "FALSE"
- `0x49c33c` — "C:\\float\\src\\effects.cpp"

### Pseudocode Ghidra

```c
uint FUN_00416ecf(short param_1)

{
  int iVar1;
  int in_ECX;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  if (*(short *)(in_ECX + 0x1202 + param_1 * 0x14) == -1) {
    local_8 = 1;
  }
  else {
    local_c = in_ECX + 0x1202 + param_1 * 0x14;
    local_10 = in_ECX + *(short *)(local_c + 0xe) * 0x30;
    local_8 = 0;
    switch(*(undefined4 *)(local_10 + 0xc)) {
    case 0:
    case 3:
    case 4:
      local_8 = (uint)((*(ushort *)(local_c + 0x10) & 0x20) != 0);
      break;
    case 1:
      thunk_FUN_00414fbf(local_c,&local_14,&local_18);
      iVar1 = thunk_FUN_004672a6((int)*(short *)(local_c + 10),(int)*(short *)(local_c + 0xc),
                                 local_14,local_18);
      if (iVar1 < 6) {
        local_8 = 1;
      }
      break;
    case 2:
      local_8 = (uint)(0x13 < *(short *)(local_c + 6));
      break;
    default:
      thunk_FUN_00414ad0(s_Bad_effect_Type__d_0049c320,*(undefined4 *)(local_10 + 0xc));
      thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c33c,0x35c,s_FALSE_0049c334);
    }
  }
  return local_8;
}
```

---

## FUN_00416ff8 — 0x416ff8

- Classification : internal
- Corps : `0x416ff8–0x4175f6`
- État : pseudocode obtenu
- Evidence : `ev_4bf3fa40e5e13170f21ec7216f3350d79ccb383de71014ab322ee52b3ebec592`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012a8` — `thunk_FUN_0041521a`
- `0x4012ad` — `thunk_FUN_0045339b`
- `0x40130c` — `thunk_FUN_0045575c`
- `0x4013e8` — `thunk_FUN_00415f1e`
- `0x40140b` — `thunk_FUN_00416e7d`
- `0x401433` — `thunk_FUN_00416ecf`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x4015aa` — `thunk_FUN_004533a8`
- `0x4015af` — `thunk_FUN_004152bd`
- `0x4018cf` — `thunk_FUN_0041ff2e`
- `0x401933` — `thunk_FUN_00464242`
- `0x401951` — `thunk_FUN_00415063`
- `0x401dca` — `thunk_FUN_0041760b`
- `0x401e4c` — `thunk_FUN_004200d2`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fa5` — `thunk_FUN_004181a6`
- `0x401faf` — `thunk_FUN_004206fc`
- `0x401fd2` — `thunk_FUN_00417f44`
- `0x4020d1` — `thunk_FUN_00420188`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x40250e` — `thunk_FUN_00414fbf`

### Chaînes référencées

- `0x49c358` — "mEffectInst[effectinst].src != -1"
- `0x49c37c` — "C:\\float\\src\\effects.cpp"
- `0x49c398` — "Bad Effect Type %d"
- `0x49c3ac` — "FALSE"
- `0x49c3b4` — "C:\\float\\src\\effects.cpp"

### Pseudocode Ghidra

```c
void FUN_00416ff8(short param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int in_ECX;
  undefined2 uVar4;
  undefined2 extraout_var;
  short local_34;
  short local_20 [2];
  short local_1c [2];
  int local_18;
  int local_14;
  int local_10;
  short *local_c;
  undefined1 *local_8;
  
  if (*(short *)(in_ECX + 0x1202 + param_1 * 0x14) == -1) {
    thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c37c,0x36f,
                       s_mEffectInst_effectinst__src______0049c358);
  }
  local_c = (short *)(in_ECX + 0x1202 + param_1 * 0x14);
  local_10 = in_ECX + local_c[7] * 0x30;
  uVar4 = (undefined2)((uint)local_10 >> 0x10);
  if ((local_c[8] & 0x80U) == 0) {
    if (((*(short *)(local_10 + 0x28) == -1) && (*(int *)(local_10 + 0xc) != 6)) ||
       (thunk_FUN_004181a6(CONCAT22(uVar4,param_1)), *(int *)(local_10 + 0xc) != 6)) {
      if (*(int *)(local_10 + 0xc) == 5) {
        thunk_FUN_0041760b(param_1);
      }
      else {
        local_14 = 0;
        local_8 = &DAT_005ec218 + local_c[4] * 0x29e8;
        iVar3 = thunk_FUN_00416ecf(param_1);
        if (iVar3 != 0) {
          if ((local_c[8] & 8U) == 0) {
            local_14 = 2;
          }
          else if ((local_c[8] & 0x10U) == 0) {
            if (*(short *)(local_10 + 0x2a) == -1) {
              local_14 = 2;
            }
            else {
              local_c[7] = *(short *)(local_10 + 0x2a);
              local_10 = in_ECX + local_c[7] * 0x30;
              if (*(int *)(local_10 + 0xc) == 2) {
                local_c[2] = 0;
                sVar1 = thunk_FUN_00467260(0x8000);
                local_c[5] = sVar1;
                sVar1 = thunk_FUN_00467260(0x8000);
                local_c[6] = sVar1;
              }
              else if ((local_c[8] & 4U) == 0) {
                sVar1 = *local_c;
                sVar2 = thunk_FUN_0041ff2e();
                local_c[2] = sVar2;
                if (local_c[2] < 0) {
                  local_c[2] = 0;
                }
                if (*(short *)(local_10 + 0x12) + -1 < (int)local_c[2]) {
                  local_c[2] = *(short *)(local_10 + 0x12) + -1;
                }
                if (*(int *)(local_10 + 0xc) == 1) {
                  iVar3 = thunk_FUN_00464242((&DAT_006137b8)[sVar1 * 0x13],
                                             *(undefined4 *)(&DAT_006137bc + sVar1 * 0x4c));
                  iVar3 = thunk_FUN_0045575c(CONCAT22(extraout_var,*(undefined2 *)(iVar3 + 4)));
                  if ((local_c[8] & 1U) == 0) {
                    local_34 = *(short *)(iVar3 + 0x4e);
                  }
                  else {
                    local_34 = -*(short *)(iVar3 + 0x4e);
                  }
                  local_c[5] = local_c[5] + local_34;
                  local_c[6] = local_c[6] + *(short *)(iVar3 + 0x50);
                }
              }
              local_c[3] = *(short *)(local_10 + 0x14 + local_c[2] * 2);
              if (*(int *)(local_10 + 0xc) != 4) {
                local_c[8] = local_c[8] | 0x10;
              }
              local_c[9] = 0;
              local_14 = 1;
            }
          }
          else {
            local_18 = 0;
            if ((local_c[8] & 2U) == 0) {
              if ((local_c[8] & 4U) == 0) {
                local_18 = thunk_FUN_004200d2(&DAT_006137b8 + local_c[1] * 0x13);
              }
              else {
                local_18 = thunk_FUN_004533a8(&DAT_006137b8 + local_c[1] * 0x13);
              }
            }
            else {
              local_18 = thunk_FUN_00420188(local_8 + local_c[1] * 0x60 + 0x428);
            }
            if (local_18 == 0) {
              local_14 = 2;
            }
            else {
              if (*(int *)(local_10 + 0xc) == 1) {
                thunk_FUN_00414fbf(local_c,local_20,local_1c);
                local_c[5] = local_20[0] - local_c[5];
                local_c[6] = local_1c[0] - local_c[6];
              }
              else {
                sVar1 = thunk_FUN_00467260(0xf);
                local_c[5] = sVar1 + -7;
                sVar1 = thunk_FUN_00467260(0xf);
                local_c[6] = sVar1 + -7;
              }
              sVar1 = thunk_FUN_00415f1e((&PTR_s_phyimp_0049bd58)[*(short *)(local_10 + 0x10)]);
              local_c[7] = sVar1;
              local_10 = in_ECX + local_c[7] * 0x30;
              local_c[2] = (short)(local_18 / 2);
              if (local_c[2] < 0) {
                local_c[2] = 0;
              }
              if (*(short *)(local_10 + 0x12) + -1 < (int)local_c[2]) {
                local_c[2] = *(short *)(local_10 + 0x12) + -1;
              }
              local_c[3] = *(short *)(local_10 + 0x14 + local_c[2] * 2);
              local_c[8] = local_c[8] & 0xffd7;
              local_c[9] = 0;
              local_14 = 1;
            }
          }
        }
        if (local_14 == 0) {
          switch(*(undefined4 *)(local_10 + 0xc)) {
          case 0:
          case 3:
          case 4:
            thunk_FUN_00415063(local_10,local_c);
            break;
          case 1:
            thunk_FUN_0041521a(local_10,local_c);
            if (200 < local_c[9]) {
              local_14 = 2;
            }
            break;
          case 2:
            thunk_FUN_004152bd(local_10,local_c);
            break;
          default:
            thunk_FUN_00414ad0(s_Bad_Effect_Type__d_0049c398,
                               *(undefined4 *)
                                (in_ECX + 0xc + *(short *)(in_ECX + 0x1210 + param_1 * 0x14) * 0x30)
                              );
            thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c3b4,0x406,s_FALSE_0049c3ac);
          }
          local_c[9] = local_c[9] + 1;
        }
        if (local_14 == 2) {
          if (((local_c[8] & 4U) == 0) || (99 < *local_c)) {
            if (*local_c < 0x100) {
              thunk_FUN_004206fc(param_1);
            }
          }
          else {
            thunk_FUN_0045339b(param_1);
          }
          thunk_FUN_00416e7d(param_1);
        }
      }
    }
  }
  else {
    thunk_FUN_00417f44(CONCAT22(uVar4,param_1));
  }
  return;
}
```

---

## FUN_0041760b — 0x41760b

- Classification : internal
- Corps : `0x41760b–0x417ee7`
- État : pseudocode obtenu
- Evidence : `ev_141765fef58a58c98b642e7d5a175b9e00d9fe52237a02f7d44ea6fc875699c7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012a8` — `thunk_FUN_0041521a`
- `0x4013e8` — `thunk_FUN_00415f1e`
- `0x40140b` — `thunk_FUN_00416e7d`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x4017ee` — `thunk_FUN_004239e9`
- `0x401951` — `thunk_FUN_00415063`
- `0x40250e` — `thunk_FUN_00414fbf`

### Chaînes référencées

- `0x49c3d0` — "upgrade"
- `0x49c3d0` — "upgrade"
- `0x49c3d8` — "freezelb"
- `0x49c3d8` — "freezelb"
- `0x49c3e4` — "locprot"
- `0x49c3e4` — "locprot"
- `0x49c3ec` — "buildton"
- `0x49c3ec` — "buildton"
- `0x49c3f8` — "hyperheal"
- `0x49c3f8` — "hyperheal"
- `0x49c404` — "hyperheal"
- `0x49c404` — "hyperheal"
- `0x49c410` — "fltarmor"
- `0x49c410` — "fltarmor"
- `0x49c41c` — "repair"
- `0x49c41c` — "repair"
- `0x49c424` — "revplot"
- `0x49c424` — "revplot"
- `0x49c42c` — "fastflt"
- `0x49c42c` — "fastflt"
- `0x49c434` — "freezesc"
- `0x49c434` — "freezesc"
- `0x49c440` — "freezesc"
- `0x49c440` — "freezesc"
- `0x49c44c` — "blastwb"
- `0x49c44c` — "blastwb"
- `0x49c454` — "stockup"
- `0x49c454` — "stockup"
- `0x49c45c` — "bldarmor"
- `0x49c45c` — "bldarmor"
- `0x49c468` — "locprot"
- `0x49c468` — "locprot"
- `0x49c470` — "buildton"
- `0x49c470` — "buildton"
- `0x49c47c` — "hyperheal"
- `0x49c47c` — "hyperheal"
- `0x49c488` — "farobt"
- `0x49c490` — "blastwb"
- `0x49c498` — "killbeas"

### Pseudocode Ghidra

```c
void FUN_0041760b(short param_1)

{
  bool bVar1;
  short sVar2;
  int in_ECX;
  int iVar3;
  undefined2 local_30 [2];
  undefined2 local_2c [2];
  int local_28;
  undefined4 *local_24;
  char *local_20;
  int local_1c;
  char *local_18;
  undefined4 *local_14;
  int local_10;
  uint local_c;
  short *local_8;
  
  local_8 = (short *)(in_ECX + 0x1202 + param_1 * 0x14);
  local_10 = in_ECX + local_8[7] * 0x30;
  local_c = 0;
  iVar3 = *local_8 * 0x4c;
  local_14 = &DAT_006137b8 + *local_8 * 0x13;
  switch(*(undefined2 *)(&DAT_006137e8 + iVar3)) {
  case 0:
  case 1:
  case 3:
  case 4:
  case 5:
  case 6:
  case 9:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xf:
  case 0x13:
    if ((local_8[8] & 0x100U) == 0) {
      if ((local_8[8] & 0x200U) == 0) {
        if (((local_8[8] & 0x400U) != 0) && (DAT_00618e44 % 2 != 0)) {
          if (*(short *)(&DAT_006137e8 + iVar3) == 0x13) {
            local_8[3] = local_8[3] + -1;
            bVar1 = local_8[3] < *(short *)(local_10 + 0x14);
            if (bVar1) {
              thunk_FUN_004239e9();
            }
            local_c = (uint)bVar1;
          }
          else {
            if (((*(short *)(&DAT_006137e8 + iVar3) == 5) ||
                (*(short *)(&DAT_006137e8 + iVar3) == 6)) ||
               (*(short *)(&DAT_006137e8 + iVar3) == 9)) {
              sVar2 = *(short *)(local_10 + 0x1e);
            }
            else {
              sVar2 = *(short *)(local_10 + 0x1c);
            }
            local_28 = (int)sVar2;
            local_8[3] = local_8[3] + 1;
            if (local_28 < local_8[3]) {
              if (*(short *)(&DAT_006137e8 + iVar3) == 1) {
                thunk_FUN_00414fbf(local_8,local_2c,local_30);
                *(undefined2 *)(local_14 + 10) = local_2c[0];
                *(undefined2 *)((int)local_14 + 0x2a) = local_30[0];
              }
              thunk_FUN_004239e9();
              local_c = 1;
            }
          }
        }
      }
      else {
        local_1c = thunk_FUN_0041521a(local_10,local_8);
        if (local_1c < 6) {
          local_20 = s_hyperheal_0049c404;
          iVar3 = *local_8 * 0x4c;
          local_24 = &DAT_006137b8 + *local_8 * 0x13;
          if (*(short *)(&DAT_006137e8 + iVar3) == 1) {
            local_20 = s_fltarmor_0049c410;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 0) {
            local_20 = s_repair_0049c41c;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 0xb) {
            local_20 = s_revplot_0049c424;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 0xc) {
            local_20 = s_fastflt_0049c42c;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 0xd) {
            local_20 = s_freezesc_0049c434;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 0x13) {
            local_20 = s_freezesc_0049c440;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 0xf) {
            local_20 = s_blastwb_0049c44c;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 3) {
            local_20 = s_stockup_0049c454;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 4) {
            local_20 = s_bldarmor_0049c45c;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 5) {
            local_20 = s_locprot_0049c468;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 6) {
            local_20 = s_buildton_0049c470;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 9) {
            local_20 = s_hyperheal_0049c47c;
          }
          sVar2 = thunk_FUN_00415f1e(local_20);
          local_8[7] = sVar2;
          local_10 = in_ECX + local_8[7] * 0x30;
          local_8[8] = 0;
          local_8[8] = local_8[8] | 2;
          local_8[8] = local_8[8] | 0x400;
          if (*(short *)(local_24 + 0xc) == 0x13) {
            local_8[3] = *(short *)(local_10 + 0x1c);
          }
          else {
            local_8[3] = *(short *)(local_10 + 0x14);
          }
          if (((*(short *)(local_24 + 0xc) == 5) || (*(short *)(local_24 + 0xc) == 6)) ||
             (*(short *)(local_24 + 0xc) == 9)) {
            local_8[2] = 1;
            local_8[3] = *(short *)(local_10 + 0x16);
          }
          else {
            local_8[2] = 0;
          }
        }
      }
    }
    else {
      thunk_FUN_00415063(local_10,local_8);
      if ((local_8[8] & 0x20U) != 0) {
        local_18 = s_upgrade_0049c3d0;
        if (*(short *)(local_14 + 0xc) == 1) {
          local_18 = s_freezelb_0049c3d8;
        }
        else if (*(short *)(local_14 + 0xc) == 5) {
          local_18 = s_locprot_0049c3e4;
        }
        else if (*(short *)(local_14 + 0xc) == 6) {
          local_18 = s_buildton_0049c3ec;
        }
        else if (*(short *)(local_14 + 0xc) == 9) {
          local_18 = s_hyperheal_0049c3f8;
        }
        sVar2 = thunk_FUN_00415f1e(local_18);
        local_8[7] = sVar2;
        local_10 = in_ECX + local_8[7] * 0x30;
        local_8[8] = 0;
        local_8[8] = local_8[8] | 2;
        local_8[8] = local_8[8] | 0x200;
        local_8[2] = 0;
        local_8[3] = *(short *)(local_10 + 0x14);
      }
    }
    break;
  case 2:
  case 0xe:
  case 0x11:
  case 0x14:
  case 0x15:
  case 0x16:
    thunk_FUN_00415063(local_10,local_8);
    if ((local_8[8] & 0x20U) != 0) {
      thunk_FUN_004239e9();
      local_c = 1;
    }
    break;
  case 7:
  case 0x12:
    if ((local_8[8] & 0x100U) == 0) {
      if (((local_8[8] & 0x200U) != 0) &&
         (thunk_FUN_00415063(local_10,local_8), (local_8[8] & 0x20U) != 0)) {
        thunk_FUN_004239e9();
        local_c = 1;
      }
    }
    else {
      thunk_FUN_00415063(local_10,local_8);
      if ((local_8[8] & 0x20U) != 0) {
        sVar2 = thunk_FUN_00415f1e(s_blastwb_0049c490);
        local_8[7] = sVar2;
        local_10 = in_ECX + local_8[7] * 0x30;
        local_8[8] = 0;
        local_8[8] = local_8[8] | 2;
        local_8[8] = local_8[8] | 0x200;
        local_8[2] = 0;
        local_8[3] = *(short *)(local_10 + 0x14);
      }
    }
    break;
  case 8:
    if ((local_8[8] & 0x100U) == 0) {
      local_8[5] = local_8[5] + 1;
      if (local_8[5] == 0x44) {
        local_8[2] = *(short *)(&DAT_005ec664 + local_8[1] * 0x60 + local_8[4] * 0x29e8);
        thunk_FUN_004239e9();
      }
      else if (local_8[5] == 0x7a) {
        local_c = 1;
      }
    }
    else {
      thunk_FUN_00415063(local_10,local_8);
      if ((local_8[8] & 0x20U) != 0) {
        sVar2 = thunk_FUN_00415f1e(s_farobt_0049c488);
        local_8[7] = sVar2;
        local_10 = in_ECX + local_8[7] * 0x30;
        local_8[4] = (short)(char)((ushort)*(undefined2 *)((int)local_14 + 0x32) >> 8);
        local_8[1] = *(ushort *)((int)local_14 + 0x32) & 0xff;
        local_8[5] = 0;
        local_8[6] = *(short *)((int)local_14 + 0x12);
        local_8[8] = 0;
        local_8[8] = local_8[8] | 2;
        local_8[2] = -1;
        local_8[3] = *(short *)(local_10 + 0x14);
      }
    }
    break;
  case 10:
    if ((local_8[8] & 0x100U) == 0) {
      local_8[5] = local_8[5] + 1;
      local_8[6] = local_8[6] + 1;
      local_8[3] = local_8[3] + 1;
      if (((0x4b < local_8[5]) && (0x4b < local_8[6])) && (0x4b < local_8[3])) {
        thunk_FUN_004239e9();
        local_c = 1;
      }
    }
    else {
      sVar2 = thunk_FUN_00415f1e(s_killbeas_0049c498);
      local_8[7] = sVar2;
      local_10 = in_ECX + local_8[7] * 0x30;
      sVar2 = thunk_FUN_00467260(0x1e);
      local_8[5] = -sVar2;
      sVar2 = thunk_FUN_00467260(0x1e);
      local_8[6] = -sVar2;
      local_8[8] = 0;
      sVar2 = thunk_FUN_00467260(8);
      local_8[2] = sVar2;
      sVar2 = thunk_FUN_00467260(0x1e);
      local_8[3] = -sVar2;
    }
    break;
  case 0x10:
    if ((*(short *)(local_10 + 0x1c) < local_8[3]) || (DAT_00618e44 % 2 == 0)) {
      if (*(short *)(local_10 + 0x1e) < local_8[3]) {
        if (DAT_00618e44 % 2 != 0) {
          local_8[3] = local_8[3] + 1;
        }
        if (*(short *)(local_10 + 0x20) < local_8[3]) {
          thunk_FUN_004239e9();
          local_c = 1;
        }
      }
      else {
        local_8[2] = 1;
        iVar3 = thunk_FUN_0041521a(local_10,local_8);
        if (iVar3 < 6) {
          local_8[3] = *(short *)(local_10 + 0x18);
        }
      }
    }
    else {
      local_8[3] = local_8[3] + 1;
    }
  }
  local_8[9] = local_8[9] + 1;
  if (local_c != 0) {
    thunk_FUN_00416e7d(param_1);
  }
  return;
}
```

---

## FUN_00417f44 — 0x417f44

- Classification : internal
- Corps : `0x417f44–0x418104`
- État : pseudocode obtenu
- Evidence : `ev_a03c22965475c38a6b6f8b1b595d77f8a389724770e7b7ade71f3ce794092cf7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40140b` — `thunk_FUN_00416e7d`
- `0x40184d` — `thunk_FUN_0045b24d`
- `0x401aaf` — `thunk_FUN_0045afb9`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00417f44(short param_1)

{
  int in_ECX;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_8 = in_ECX + 0x1202 + param_1 * 0x14;
  local_c = in_ECX + *(short *)(local_8 + 0xe) * 0x30;
  if ((*(short *)(local_8 + 0x12) == 0) && (*(short *)(local_c + 0x28) != -1)) {
    thunk_FUN_0045b24d((int)*(short *)(local_8 + 10),
                       *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) + 0x140,&local_14,&local_10);
    thunk_FUN_0045afb9(*(undefined2 *)(local_c + 0x28),local_14,local_10);
  }
  if (*(int *)(local_c + 0xc) == 1) {
    *(short *)(local_8 + 10) = *(short *)(local_8 + 10) + 3;
  }
  if (DAT_00618e44 % 2 != 0) {
    *(short *)(local_8 + 6) = *(short *)(local_8 + 6) + 1;
  }
  if (*(short *)(local_c + 0x1c + *(short *)(local_8 + 4) * 2) < *(short *)(local_8 + 6)) {
    if ((*(int *)(local_c + 0xc) == 1) && (*(short *)(local_8 + 10) < 0x1b9)) {
      *(undefined2 *)(local_8 + 6) = *(undefined2 *)(local_c + 0x14 + *(short *)(local_8 + 4) * 2);
    }
    else if ((int)*(short *)(local_8 + 4) < *(short *)(local_c + 0x12) + -1) {
      *(short *)(local_8 + 4) = *(short *)(local_8 + 4) + 1;
      *(undefined2 *)(local_8 + 6) = *(undefined2 *)(local_c + 0x14 + *(short *)(local_8 + 4) * 2);
      *(undefined2 *)(local_8 + 0x12) = 0;
      *(short *)(local_8 + 10) = *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) + 0x140;
    }
    else {
      *(ushort *)(local_8 + 0x10) = *(ushort *)(local_8 + 0x10) & 0xff7f;
      thunk_FUN_00416e7d(param_1);
    }
  }
  *(short *)(local_8 + 0x12) = *(short *)(local_8 + 0x12) + 1;
  return;
}
```

---

## FUN_00418105 — 0x418105

- Classification : internal
- Corps : `0x418105–0x4181a5`
- État : pseudocode obtenu
- Evidence : `ev_2c71645aaa9320eb731679d674b705320b6394eca7fe88af0cd6dcb7f1a82403`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49c4a4` — "shape"
- `0x49c4ac` — "C:\\float\\src\\effects.cpp"

### Pseudocode Ghidra

```c
void FUN_00418105(undefined4 param_1,int param_2)

{
  int in_ECX;
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = in_ECX + *(short *)(param_2 + 0xe) * 0x30;
  if (*(int *)(iVar1 + 0xc) != 6) {
    iVar1 = thunk_FUN_0040e864(CONCAT22((short)((uint)iVar1 >> 0x10),*(undefined2 *)(iVar1 + 0x26)))
    ;
    if (iVar1 == 0) {
      uVar2 = thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c4ac,0x584,s_shape_0049c4a4);
    }
    else {
      uVar2 = 0;
    }
    thunk_FUN_00404770(param_1,iVar1,(int)*(short *)(param_2 + 6),
                       (int)*(short *)(param_2 + 10) -
                       (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2),
                       (int)*(short *)(param_2 + 0xc),uVar2);
  }
  return;
}
```

---

## FUN_004181a6 — 0x4181a6

- Classification : internal
- Corps : `0x4181a6–0x4182c7`
- État : pseudocode obtenu
- Evidence : `ev_debaf503b8067df8b015020cce042fb513deb1333fbefcc4677ace9723cb5e9e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40140b` — `thunk_FUN_00416e7d`
- `0x40184d` — `thunk_FUN_0045b24d`
- `0x401aaf` — `thunk_FUN_0045afb9`
- `0x40250e` — `thunk_FUN_00414fbf`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004181a6(short param_1)

{
  int in_ECX;
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_8 = in_ECX + 0x1202 + param_1 * 0x14;
  local_c = in_ECX + *(short *)(local_8 + 0xe) * 0x30;
  if (*(short *)(local_8 + 0x12) == 0) {
    if (((*(short *)(local_c + 0x28) != -1) && (*(short *)(local_8 + 8) == DAT_0049f53c)) &&
       (DAT_0062d172 == 3)) {
      local_18 = *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) + 0x140;
      local_1c = (int)*(short *)(local_8 + 10);
      if ((*(int *)(local_c + 0xc) == 2) || (*(int *)(local_c + 0xc) == 3)) {
        thunk_FUN_00414fbf(local_8,&local_1c,0);
      }
      if (*(int *)(local_c + 0xc) == 3) {
        local_1c = local_1c + *(short *)(local_8 + 10);
      }
      thunk_FUN_0045b24d(local_1c,local_18,&local_14,&local_10);
      thunk_FUN_0045afb9(*(undefined2 *)(local_c + 0x28),local_14,local_10);
    }
    if (*(int *)(local_c + 0xc) == 6) {
      thunk_FUN_00416e7d(param_1);
    }
  }
  return;
}
```

---


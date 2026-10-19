# 0010_batch_0006 — détails (1/3)

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

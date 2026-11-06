# 0016_batch_0012 — détails (2/3)

## FUN_0045981d — 0x45981d

- Classification : internal
- Corps : `0x45981d–0x459e48`
- État : pseudocode obtenu
- Evidence : `ev_fff9e50ce789180778b33aec20433a25680da9da33751cc524d839482c18a0a2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401483` — `thunk_FUN_00459e49`
- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401d57` — `thunk_FUN_004593ff`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472ca0` — `FUN_00472ca0`
- `0x472da0` — `FUN_00472da0`
- `0x472f10` — `FUN_00472f10`
- `0x474b20` — `_memset`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x4a3684` — "data\\"
- `0x4a368c` — "%s\\thing2\\"
- `0x4a369c` — "%d %d"
- `0x4a36a4` — "%s %s %s"
- `0x4a36c0` — "Sound missing: %s"
- `0x4a36d4` — "FALSE"
- `0x4a36dc` — "C:\\float\\src\\soundsys.cpp"
- `0x4a36f8` — "success==TRUE"
- `0x4a3708` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3724` — "mNumSoundItems<=MAX_SOUNDITEMS"
- `0x4a3744` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3768` — "%s%s%s"
- `0x4a3770` — "Missing Sound File: %s"
- `0x4a3788` — "success==0"
- `0x4a3794` — "C:\\float\\src\\soundsys.cpp"
- `0x4a37b0` — "success==TRUE"
- `0x4a37c0` — "C:\\float\\src\\soundsys.cpp"
- `0x4a37dc` — "mNumSoundItems<=MAX_SOUNDITEMS"
- `0x4a37fc` — "C:\\float\\src\\soundsys.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0045981d(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined4 *unaff_FS_OFFSET;
  short local_37c;
  undefined1 local_378 [80];
  undefined1 local_328 [280];
  short local_210;
  undefined4 local_100;
  int local_fc;
  int local_f8;
  undefined1 local_f4 [32];
  undefined1 local_d4 [32];
  int local_b4;
  undefined1 local_b0 [128];
  char local_30 [32];
  undefined4 local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491b7a;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (DAT_004c2ba4 == 0) {
    FUN_00472ca0(local_378,s__s_thing2__004a368c,&DAT_004c2aa8);
    thunk_FUN_00459e49(local_378,1);
  }
  else {
    thunk_FUN_00459e49(s_data__004a3684,0);
  }
  thunk_FUN_0040f6f7();
  local_8 = 0;
  iVar1 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,20000);
  if (iVar1 == 0) {
    iVar1 = thunk_FUN_0040f5b3(local_b0,0);
    if (iVar1 == -1) {
      local_8 = 0xffffffff;
      thunk_FUN_0040f73f();
      uVar2 = 0;
    }
    else {
      FUN_00472f10(local_b0,&DAT_004a3698,&local_b4);
      DAT_005ea4b8 = 0;
      for (local_210 = 0; local_210 < local_b4; local_210 = local_210 + 1) {
        iVar1 = thunk_FUN_0040f5b3(local_b0,0);
        if (iVar1 == -1) {
          local_8 = 0xffffffff;
          thunk_FUN_0040f73f();
          uVar2 = 0;
          goto LAB_00459e39;
        }
        FUN_00472f10(local_b0,s__d__d_004a369c,&local_fc,&local_100);
        for (local_37c = 0; local_37c < local_fc; local_37c = local_37c + 1) {
          (&DAT_005ea3a4)[DAT_005ea4b8 * 3] = local_100;
          DAT_005ea4b8 = DAT_005ea4b8 + 1;
        }
      }
      thunk_FUN_0040f6f7();
      local_8 = CONCAT31(local_8._1_3_,1);
      *(undefined4 *)(in_ECX + 0x1f80) = 0;
      local_f8 = in_ECX;
LAB_00459a5a:
      iVar1 = thunk_FUN_0040f5b3(local_b0,0);
      if (iVar1 != -1) {
        FUN_00472f10(local_b0,s__s__s__s_004a36a4,local_30,local_d4,local_f4);
        FUN_00472da0(local_f8,local_d4);
        iVar1 = __strcmpi(local_30,&DAT_004a36b0);
        if (iVar1 == 0) goto code_r0x00459ac8;
        FUN_00472da0(local_f8 + 0xc,local_f4);
        goto LAB_00459b19;
      }
      if (DAT_004c2ba8 != 0) {
        FUN_00472da0(local_f8,&DAT_004c2ab8);
        FUN_00472ca0(local_f8 + 0xc,s__s_s_s_004a3768,in_ECX + 0x20a4,&DAT_004c2ab8,&DAT_004a3760);
        iVar1 = thunk_FUN_0040f752(local_f8 + 0xc,0x8000);
        if (iVar1 != 0) {
          thunk_FUN_00414ad0(s_Missing_Sound_File___s_004a3770,local_f8 + 0xc);
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3794,0x143,s_success__0_004a3788);
        }
        _memset((void *)(local_f8 + 0x34),0,0x14);
        *(undefined2 *)(local_f8 + 0x44) = 0x14;
        iVar1 = thunk_FUN_004593ff(local_328,local_f8 + 0x34,local_f8 + 0x2c,local_f8 + 0x30);
        if (iVar1 != 1) {
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a37c0,0x149,s_success__TRUE_004a37b0);
        }
        *(int *)(in_ECX + 0x1f80) = *(int *)(in_ECX + 0x1f80) + 1;
        local_f8 = local_f8 + 0x48;
        if (0x70 < *(int *)(in_ECX + 0x1f80)) {
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a37fc,0x14e,
                             s_mNumSoundItems<_MAX_SOUNDITEMS_004a37dc);
        }
      }
      local_8 = local_8 & 0xffffff00;
      thunk_FUN_0040f73f();
      local_8 = 0xffffffff;
      thunk_FUN_0040f73f();
      uVar2 = 1;
    }
  }
  else {
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
    uVar2 = 0;
  }
LAB_00459e39:
  *unaff_FS_OFFSET = local_10;
  return uVar2;
code_r0x00459ac8:
  if (DAT_004c2ba8 == 0) {
    FUN_00472ca0(local_f8 + 0xc,&DAT_004a36b8,in_ECX + 0x20a4,local_f4);
LAB_00459b19:
    iVar1 = thunk_FUN_0040f752(local_f8 + 0xc,0x8000);
    if (iVar1 != 0) {
      thunk_FUN_00414ad0(s_Sound_missing___s_004a36c0,local_f8 + 0xc);
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a36dc,0x12e,s_FALSE_004a36d4);
    }
    _memset((void *)(local_f8 + 0x34),0,0x14);
    *(undefined2 *)(local_f8 + 0x44) = 0x14;
    iVar1 = thunk_FUN_004593ff(local_328,local_f8 + 0x34,local_f8 + 0x2c,local_f8 + 0x30);
    if (iVar1 != 1) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3708,0x135,s_success__TRUE_004a36f8);
    }
    *(int *)(in_ECX + 0x1f80) = *(int *)(in_ECX + 0x1f80) + 1;
    local_f8 = local_f8 + 0x48;
    if (0x70 < *(int *)(in_ECX + 0x1f80)) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3744,0x13a,
                         s_mNumSoundItems<_MAX_SOUNDITEMS_004a3724);
    }
  }
  goto LAB_00459a5a;
}
```

---

---

## FUN_00459e49 — 0x459e49

- Classification : internal
- Corps : `0x459e49–0x459e83`
- État : pseudocode obtenu
- Evidence : `ev_fa2ce81ff4c1212e690d177a3dacfb8b79e527f46af621f483d6794523c301a9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4737e0` — `_strncpy`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00459e49(char *param_1,undefined4 param_2)

{
  int in_ECX;
  
  _strncpy((char *)(in_ECX + 0x20a4),param_1,0x4f);
  *(undefined1 *)(in_ECX + 0x20f3) = 0;
  *(undefined4 *)(in_ECX + 0x20f4) = param_2;
  return;
}
```

---

---

## FUN_00459e84 — 0x459e84

- Classification : internal
- Corps : `0x459e84–0x45a305`
- État : pseudocode obtenu
- Evidence : `ev_4eb126acfd04cac99fa7bbdbfba18989cbf15cc31ae7955fa0f48b23073449bb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401244` — `thunk_FUN_0045981d`
- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x401d57` — `thunk_FUN_004593ff`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x472a4a` — `DSOUND.DLL::DirectSoundCreate`

### Chaînes référencées

- `0x4a3818` — "SoundSystem: FAILED DirectSoundCreate.\n"
- `0x4a3840` — "SoundSystem: FAILED SetCooperativeLevel.\n"
- `0x4a386c` — "r==DS_OK"
- `0x4a3878` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3894` — "data\\format.wav"
- `0x4a38a4` — "status==0"
- `0x4a38b0` — "C:\\float\\src\\soundsys.cpp"
- `0x4a38cc` — "success==TRUE"
- `0x4a38dc` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3900` — "Stereo"
- `0x4a3900` — "Stereo"
- `0x4a3900` — "Stereo"
- `0x4a3908` — "Music Format: %d-bit %s.\n"
- `0x4a3924` — "SoundSystem: CreateSoundBuffer (tune) failed.\n"
- `0x4a3954` — "r==DS_OK"
- `0x4a3960` — "C:\\float\\src\\soundsys.cpp"
- `0x4a397c` — "data\\fxformat.wav"
- `0x4a3990` — "status==0"
- `0x4a399c` — "C:\\float\\src\\soundsys.cpp"
- `0x4a39b8` — "success==TRUE"
- `0x4a39c8` — "C:\\float\\src\\soundsys.cpp"
- `0x4a39e4` — "Effects Format: %d-bit %s.\n"
- `0x4a3a00` — "SoundSystem: CreateSoundBuffer SFX%d failed.\n"
- `0x4a3a30` — "r==DS_OK"
- `0x4a3a3c` — "C:\\float\\src\\soundsys.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_00459e84(undefined4 param_1)

{
  undefined4 uVar1;
  int in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_154;
  undefined1 local_150;
  undefined4 local_14f;
  undefined1 local_14b;
  char local_14a [4];
  char local_146 [2];
  char local_144;
  undefined2 local_143;
  undefined1 local_141;
  int local_140;
  int local_13c;
  short local_138;
  undefined1 local_134 [268];
  int local_28;
  undefined4 local_24;
  uint local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined *local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491b90;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_28 = DirectSoundCreate(0,&DAT_005ea39c,0);
  if (local_28 == 0) {
    local_28 = (**(code **)(*DAT_005ea39c + 0x18))(DAT_005ea39c,DAT_004c2b58,3);
    if (local_28 != 0) {
      thunk_FUN_00414ad0(s_SoundSystem__FAILED_SetCooperati_004a3840);
    }
    if (local_28 != 0) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3878,0x179,s_r__DS_OK_004a386c);
    }
    thunk_FUN_0045981d(param_1);
    thunk_FUN_0040f6f7();
    local_8 = 0;
    local_13c = thunk_FUN_0040f752(s_data_format_wav_004a3894,0x8000);
    if (local_13c != 0) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a38b0,0x185,s_status__0_004a38a4);
    }
    local_140 = thunk_FUN_004593ff(local_134,&DAT_005ea460,in_ECX + 0x2094,in_ECX + 0x2098);
    if (local_140 != 1) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a38dc,0x188,s_success__TRUE_004a38cc);
    }
    local_154 = DAT_004a38f8;
    local_150 = DAT_004a38fc;
    local_14f = 0;
    local_14b = 0;
    local_14a[0] = s_Stereo_004a3900[0];
    local_14a[1] = s_Stereo_004a3900[1];
    local_14a[2] = s_Stereo_004a3900[2];
    local_14a[3] = s_Stereo_004a3900[3];
    local_146[0] = s_Stereo_004a3900[4];
    local_146[1] = s_Stereo_004a3900[5];
    local_144 = s_Stereo_004a3900[6];
    local_143 = 0;
    local_141 = 0;
    thunk_FUN_00414ad0(s_Music_Format___d_bit__s__004a3908,DAT_005ea46e,
                       (int)&local_154 + (DAT_005ea462 - 1) * 10);
    local_24 = 0x14;
    local_20 = 0xe0;
    local_18 = 0;
    local_14 = &DAT_005ea460;
    local_1c = 0xc800;
    local_28 = (**(code **)(*DAT_005ea39c + 0xc))(DAT_005ea39c,&local_24,&DAT_005e8228,0);
    if (local_28 != 0) {
      thunk_FUN_00414ad0(s_SoundSystem__CreateSoundBuffer___004a3924);
    }
    if (local_28 != 0) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3960,0x1a7,s_r__DS_OK_004a3954);
    }
    local_20 = local_20 | 2;
    thunk_FUN_0040f966();
    local_13c = thunk_FUN_0040f752(s_data_fxformat_wav_004a397c,0x8000);
    if (local_13c != 0) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a399c,0x1b0,s_status__0_004a3990);
    }
    local_140 = thunk_FUN_004593ff(local_134,&DAT_005ea460,in_ECX + 0x2094,in_ECX + 0x2098);
    if (local_140 != 1) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a39c8,0x1b4,s_success__TRUE_004a39b8);
    }
    local_14 = &DAT_005ea460;
    thunk_FUN_00414ad0(s_Effects_Format___d_bit__s__004a39e4,DAT_005ea46e,
                       (int)&local_154 + (DAT_005ea462 - 1) * 10);
    for (local_138 = 0; local_138 < DAT_005ea4b8; local_138 = local_138 + 1) {
      local_1c = (&DAT_005ea3a4)[local_138 * 3];
      local_28 = (**(code **)(*DAT_005ea39c + 0xc))
                           (DAT_005ea39c,&local_24,&DAT_005ea478 + local_138,0);
      if (local_28 != 0) {
        thunk_FUN_00414ad0(s_SoundSystem__CreateSoundBuffer_S_004a3a00,(int)local_138);
      }
      if (local_28 != 0) {
        thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3a3c,0x1c4,s_r__DS_OK_004a3a30);
      }
    }
    *(undefined4 *)(in_ECX + 0x2168) = 0;
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
    uVar1 = 1;
  }
  else {
    thunk_FUN_00414ad0(s_SoundSystem__FAILED_DirectSoundC_004a3818);
    uVar1 = 0;
  }
  *unaff_FS_OFFSET = local_10;
  return uVar1;
}
```

---

---

## FUN_0045a306 — 0x45a306

- Classification : internal
- Corps : `0x45a306–0x45a3f0`
- État : pseudocode obtenu
- Evidence : `ev_76f6ee4570ab719fc7889a5996ec4af3f4c89e012a4685a2b57a5ec6b354c0ec`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401d25` — `thunk_FUN_0040f966`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045a306(void)

{
  short local_8;
  
  thunk_FUN_0040f966();
  if (DAT_005e8228 != (int *)0x0) {
    (**(code **)(*DAT_005e8228 + 0x48))(DAT_005e8228);
    (**(code **)(*DAT_005e8228 + 8))(DAT_005e8228);
    DAT_005e8228 = (int *)0x0;
  }
  for (local_8 = 0; local_8 < DAT_005ea4b8; local_8 = local_8 + 1) {
    if ((&DAT_005ea478)[local_8] != 0) {
      (**(code **)(*(int *)(&DAT_005ea478)[local_8] + 0x48))((&DAT_005ea478)[local_8]);
      (**(code **)(*(int *)(&DAT_005ea478)[local_8] + 8))((&DAT_005ea478)[local_8]);
      (&DAT_005ea478)[local_8] = 0;
    }
  }
  if (DAT_005ea39c != (int *)0x0) {
    (**(code **)(*DAT_005ea39c + 8))(DAT_005ea39c);
    DAT_005ea39c = (int *)0x0;
  }
  return;
}
```

---

---

## FUN_0045a3f1 — 0x45a3f1

- Classification : internal
- Corps : `0x45a3f1–0x45a4f9`
- État : pseudocode obtenu
- Evidence : `ev_494ea6bf205433872bf270c5cbed99038ff7ecac37ff86deb02a36d65f093383`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010f5` — `thunk_FUN_0045af9c`
- `0x4018bb` — `thunk_FUN_0045aba9`
- `0x401a91` — `thunk_FUN_0045a645`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x4021f8` — `thunk_FUN_004595cc`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045a3f1(void)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  
  if (*(int *)(in_ECX + 0x2160) == 1) {
    *(int *)(in_ECX + 0x2164) = *(int *)(in_ECX + 0x2164) + 1;
    iVar1 = thunk_FUN_0045af9c();
    iVar1 = iVar1 + *(int *)(in_ECX + 0x2164) * -4;
    if (iVar1 < 10) {
      if (*(char *)(in_ECX + 0x2108) == '\0') {
        thunk_FUN_0040f966();
      }
      else {
        thunk_FUN_0045aba9(in_ECX + 0x2108,*(undefined4 *)(in_ECX + 0x2158),
                           *(undefined4 *)(in_ECX + 0x215c));
        *(undefined1 *)(in_ECX + 0x2108) = 0;
      }
      *(undefined4 *)(in_ECX + 0x2160) = 0;
    }
    else {
      uVar2 = thunk_FUN_004595cc(iVar1);
      if (DAT_005e8228 != (int *)0x0) {
        (**(code **)(*DAT_005e8228 + 0x3c))(DAT_005e8228,uVar2);
      }
    }
  }
  *(int *)(in_ECX + 0x2168) = *(int *)(in_ECX + 0x2168) + 1;
  iVar1 = thunk_FUN_0045af9c();
  if (iVar1 != 0) {
    thunk_FUN_0045a645();
  }
  return;
}
```

---

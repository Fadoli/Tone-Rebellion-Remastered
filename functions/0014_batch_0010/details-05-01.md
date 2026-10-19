# 0014_batch_0010 — détails (1/3)

## FUN_00448e5a — 0x448e5a

- Classification : internal
- Corps : `0x448e5a–0x449482`
- État : pseudocode obtenu
- Evidence : `ev_fa8596b87038266d342d91e5cd7c43fef4e4131faaa00bbfc162313b562bb864`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401154` — `thunk_FUN_00414b91`
- `0x40119f` — `thunk_FUN_0046c371`
- `0x4012ee` — `thunk_FUN_0046c458`
- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x4017df` — `thunk_FUN_0041be72`
- `0x4017f3` — `thunk_FUN_0040fb84`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x4018bb` — `thunk_FUN_0045aba9`
- `0x401a3c` — `thunk_FUN_00410510`
- `0x401bea` — `thunk_FUN_004334ce`
- `0x401c53` — `thunk_FUN_0044e4f8`
- `0x401d02` — `thunk_FUN_0046cce7`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x401d8e` — `thunk_FUN_004140dd`
- `0x401e51` — `thunk_FUN_0044964f`
- `0x401e65` — `thunk_FUN_0046c4a5`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x40227f` — `thunk_FUN_0046c25d`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x4a1528` — "begingame"
- `0x4a1534` — "NGMBeginButton"
- `0x4a1544` — "C:\\float\\src\\master.cpp"
- `0x4a155c` — "data\\newgame.pal"
- `0x4a155c` — "data\\newgame.pal"
- `0x4a155c` — "data\\newgame.pal"
- `0x4a1570` — "status==0"
- `0x4a157c` — "C:\\float\\src\\master.cpp"
- `0x4a1594` — "data\\newgame.hzt"
- `0x4a15a8` — "ambient1"
- `0x4a15b4` — "NEWGAMWND"
- `0x4a24e8` — "TRIBE0"

### Pseudocode Ghidra

```c
void FUN_00448e5a(short param_1,int param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *unaff_FS_OFFSET;
  int local_460;
  int local_45c;
  undefined4 local_458;
  int local_454;
  int local_450;
  undefined4 local_44c;
  int local_448;
  int local_444;
  char *local_440;
  int local_43c;
  uint local_438;
  int local_434;
  int local_430;
  int local_42c;
  int local_31c;
  undefined1 local_318 [768];
  int local_18;
  char *local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491a04;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  switch(param_1) {
  case 1:
    iVar1 = thunk_FUN_0046c4a5(s_begingame_004a1528,0);
    DAT_005e1744 = *(int *)(iVar1 + 4);
    if (DAT_005e1744 == 0) {
      thunk_FUN_00414b64(s_C__float_src_master_cpp_004a1544,0xee,s_NGMBeginButton_004a1534);
    }
    thunk_FUN_0046c25d(1,0,0,0);
    thunk_FUN_0046c371(DAT_005e1744,4,0,0);
    thunk_FUN_0040f6f7();
    local_8 = 0;
    local_14 = s_data_newgame_pal_004a155c;
    local_31c = thunk_FUN_0040f752(s_data_newgame_pal_004a155c,0x8000);
    if (local_31c == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = thunk_FUN_00414b91(s_C__float_src_master_cpp_004a157c,0xf8,s_status__0_004a1570,
                                 local_14);
    }
    thunk_FUN_0040fb84(local_318);
    thunk_FUN_0046cce7(local_318);
    thunk_FUN_0040f966(uVar2);
    thunk_FUN_00410510(s_data_newgame_hzt_004a1594,local_318);
    if (DAT_005e1740 == 0) {
      thunk_FUN_0045aba9(s_ambient1_004a15a8,0,1);
      DAT_005e1740 = 1;
    }
    for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1) {
      *(undefined4 *)(&DAT_005e1730 + local_18 * 4) = *(undefined4 *)(&DAT_004bf0f0 + local_18 * 4);
    }
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
    break;
  case 2:
    local_42c = 0;
    while ((local_42c < 4 &&
           ((*(uint *)(&DAT_004bf0f0 + DAT_004befec * 4) & 1 << ((byte)local_42c & 0x1f)) == 0))) {
      local_42c = local_42c + 1;
    }
    if (local_42c < 4) {
      thunk_FUN_0044964f(local_42c);
    }
    break;
  case 3:
    if (((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) || (DAT_004befe0 == 0)) {
      for (local_43c = 0;
          (local_43c < DAT_004befe4 && (*(int *)(&DAT_004bf0f0 + local_43c * 4) != 0));
          local_43c = local_43c + 1) {
      }
      local_438 = (uint)(local_43c == DAT_004befe4);
      if (local_438 != *(uint *)(*(int *)(&DAT_0062a784 + DAT_005e1744 * 0xc) + 0x38)) {
        thunk_FUN_0046c371(DAT_005e1744,4 - (uint)(local_438 != 0),0,0);
        thunk_FUN_0046c371(DAT_005e1744,0xb,0,0);
      }
    }
    local_430 = 0;
    for (local_434 = 0; local_434 < 4; local_434 = local_434 + 1) {
      if (*(int *)(&DAT_005e1730 + local_434 * 4) != *(int *)(&DAT_004bf0f0 + local_434 * 4)) {
        local_430 = 1;
        *(undefined4 *)(&DAT_005e1730 + local_434 * 4) =
             *(undefined4 *)(&DAT_004bf0f0 + local_434 * 4);
      }
    }
    if (local_430 != 0) {
      thunk_FUN_0046c25d(0xb,0,0,0);
    }
    break;
  case 4:
    if (param_4 != (undefined4 *)0x0) {
      local_440 = (char *)thunk_FUN_0046c458(CONCAT22((short)((uint)(param_1 + -1) >> 0x10),
                                                      (undefined2)DAT_0062c6bc));
      if (local_440 != (char *)0x0) {
        iVar1 = __strcmpi(local_440,s_NEWGAMWND_004a15b4);
        if ((iVar1 == 0) && (local_444 = thunk_FUN_0044e4f8(param_2,param_3), local_444 != -1)) {
          local_440 = s_TRIBE0_004a24e8 + local_444 * 0x10;
        }
        uVar2 = thunk_FUN_00429ebe(local_440,0);
        *param_4 = uVar2;
      }
      if (local_440 != DAT_005e174c) {
        DAT_005e174c = local_440;
        thunk_FUN_0046c25d(0xb,1,0,0);
      }
    }
    break;
  case 5:
    thunk_FUN_004334ce(param_2,param_3);
    break;
  case 0x34:
    if (((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) || (DAT_004befe0 == 0)) {
      for (local_448 = 0;
          (local_448 < DAT_004befe4 && (*(int *)(&DAT_004bf0f0 + local_448 * 4) != 0));
          local_448 = local_448 + 1) {
      }
      if (local_448 == DAT_004befe4) {
        local_44c = thunk_FUN_0041be72();
        thunk_FUN_004140dd(9,&local_44c,4,0);
      }
    }
    break;
  case 0x35:
    if (((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) || (DAT_004befe0 == 0)) {
      local_450 = DAT_004bf118 + 1;
      if (2 < local_450) {
        local_450 = 0;
      }
      thunk_FUN_004140dd(7,&local_450,4,0);
    }
    break;
  case 0x37:
    if (((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) || (DAT_004befe0 == 0)) {
      local_460 = DAT_004bf11c + 1;
      if (4 < local_460) {
        local_460 = 0;
      }
      thunk_FUN_004140dd(8,&local_460,4,0);
    }
    break;
  case 0x3c:
  case 0x3d:
  case 0x3e:
  case 0x3f:
    local_45c = param_2;
    if (param_2 == -1) {
      local_45c = param_1 + -0x3c;
    }
    local_458 = *(undefined4 *)(&DAT_004bf100 + DAT_004befec * 4);
    local_454 = local_45c;
    thunk_FUN_004140dd(6,&local_458,8,0);
  }
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

---

## FUN_0044954d — 0x44954d

- Classification : internal
- Corps : `0x44954d–0x44964e`
- État : pseudocode obtenu
- Evidence : `ev_11348f4eeacf0261fce30a797f3a8cadad4e60977bc054eb6e659517c1e625c6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x4017f3` — `thunk_FUN_0040fb84`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401d02` — `thunk_FUN_0046cce7`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x40227f` — `thunk_FUN_0046c25d`

### Chaînes référencées

- `0x4a15cc` — "data\\endgame.pal"
- `0x4a15e0` — "status==0"
- `0x4a15ec` — "C:\\float\\src\\master.cpp"

### Pseudocode Ghidra

```c
void FUN_0044954d(short param_1)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar2;
  undefined1 local_310 [768];
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491a1a;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (param_1 == 1) {
    thunk_FUN_0040f6f7();
    local_8 = 0;
    iVar1 = thunk_FUN_0040f752(s_data_endgame_pal_004a15cc,0x8000);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = thunk_FUN_00414b64(s_C__float_src_master_cpp_004a15ec,0x1dc,s_status__0_004a15e0);
    }
    thunk_FUN_0040fb84(local_310);
    thunk_FUN_0046cce7(local_310);
    thunk_FUN_0040f966(uVar2);
    thunk_FUN_0046c25d(1,0,0,0);
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
  }
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

---

## FUN_0044964f — 0x44964f

- Classification : internal
- Corps : `0x44964f–0x4497ce`
- État : pseudocode obtenu
- Evidence : `ev_14b79f9277cf2f06806d09bda4a4f9d9021f6d5305a11a434bb40ed7e7eff29c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401640` — `thunk_FUN_0040e817`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x4a1604` — "data\\TEMPHOL%d.SHP"
- `0x4a1618` — "TEMPHOLE"
- `0x4a1624` — "data\\ISLETMP%d.SHP"
- `0x4a1638` — "ISLETEMP"
- `0x4a1644` — "data\\MAINBUT%d.SHP"
- `0x4a1658` — "MAINBUTT"
- `0x4a1664` — "data\\SLIDWIN%d.SHP"
- `0x4a1678` — "SLIDEWIN"
- `0x4a1684` — "data\\LOADSAV%d.SHP"
- `0x4a1698` — "LOADSAVE"
- `0x4a16a4` — "data\\THALL%d.SHP"
- `0x4a16b8` — "THALL"
- `0x4a16c0` — "data\\SCARROW%d.SHP"
- `0x4a16d4` — "SCARROW"
- `0x4a16dc` — "data\\ENDTEM%d.SHP"
- `0x4a16f0` — "ENDTEMP"
- `0x4a16f8` — "data\\CLIP%d.SHP"

### Pseudocode Ghidra

```c
void FUN_0044964f(int param_1)

{
  undefined1 local_1c [24];
  
  if (param_1 == -1) {
    param_1 = DAT_0049f538;
  }
  FUN_00472ca0(local_1c,s_data_TEMPHOL_d_SHP_004a1604,param_1);
  thunk_FUN_0040e817(s_TEMPHOLE_004a1618,local_1c);
  FUN_00472ca0(local_1c,s_data_ISLETMP_d_SHP_004a1624,param_1);
  thunk_FUN_0040e817(s_ISLETEMP_004a1638,local_1c);
  FUN_00472ca0(local_1c,s_data_MAINBUT_d_SHP_004a1644,param_1);
  thunk_FUN_0040e817(s_MAINBUTT_004a1658,local_1c);
  FUN_00472ca0(local_1c,s_data_SLIDWIN_d_SHP_004a1664,param_1);
  thunk_FUN_0040e817(s_SLIDEWIN_004a1678,local_1c);
  FUN_00472ca0(local_1c,s_data_LOADSAV_d_SHP_004a1684,param_1);
  thunk_FUN_0040e817(s_LOADSAVE_004a1698,local_1c);
  FUN_00472ca0(local_1c,s_data_THALL_d_SHP_004a16a4,param_1);
  thunk_FUN_0040e817(s_THALL_004a16b8,local_1c);
  FUN_00472ca0(local_1c,s_data_SCARROW_d_SHP_004a16c0,param_1);
  thunk_FUN_0040e817(s_SCARROW_004a16d4,local_1c);
  FUN_00472ca0(local_1c,s_data_ENDTEM_d_SHP_004a16dc,param_1);
  thunk_FUN_0040e817(s_ENDTEMP_004a16f0,local_1c);
  FUN_00472ca0(local_1c,s_data_CLIP_d_SHP_004a16f8,param_1);
  thunk_FUN_0040e817(&DAT_004a1708,local_1c);
  return;
}
```

---

---

## FUN_00449b60 — 0x449b60

- Classification : internal
- Corps : `0x449b60–0x449b78`
- État : pseudocode obtenu
- Evidence : `ev_db80ce270afeaab65b558dad50a55b4f197dfc86204684fde2d1dc57d2b52625`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401bc7` — `thunk_FUN_004500b6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00449b60(void)

{
  undefined4 in_ECX;
  
  thunk_FUN_004500b6();
  return in_ECX;
}
```

---

---

## FUN_00449b80 — 0x449b80

- Classification : internal
- Corps : `0x449b80–0x449e3b`
- État : pseudocode obtenu
- Evidence : `ev_d7ebc38258ca0b1d8698436f91c6f0c57006da3220d4ba25f1782a31bafed9b6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x5` — `KERNEL32.DLL::MultiByteToWideChar`
- `EXTERNAL:0x65` — `USER32.DLL::ShowCursor`
- `EXTERNAL:0x7a` — `OLE32.DLL::CoInitialize`
- `EXTERNAL:0x7b` — `OLE32.DLL::CoCreateInstance`
- `0x4016ef` — `thunk_FUN_00449e3c`
- `0x40179e` — `thunk_FUN_0042d9df`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x4a1794` — "ERROR: CoInitialize: %x\n"
- `0x4a17b0` — "ERROR: CoCreateInstance: %x\n"
- `0x4a17d0` — "intro.avi"
- `0x4a17dc` — "ERROR: RenderFile: %x"
- `0x4a17f4` — "Video Renderer"
- `0x4a1804` — "DD bob: %x\n"
- `0x4a1810` — "Couldn't get DDV: %x\n"
- `0x4a1828` — "Couldn't get filter: %x\n"
- `0x4a1844` — "message drain failed: %x\n"
- `0x4a1860` — "full screen switch failed: %x\n"
- `0x4a1880` — "Full Screen Get: %x, %x\n"
- `0x4a189c` — "Couldn't get VW: %x\n"
- `0x4a18b4` — "ERROR creating IMediaControl: %x\n"

### Pseudocode Ghidra

```c
void FUN_00449b80(void)

{
  int iVar1;
  undefined4 local_5c;
  undefined4 local_58;
  int *local_54;
  int *local_50;
  WCHAR local_4c [30];
  int *local_10;
  int *local_c;
  HRESULT local_8;
  
  ShowCursor(0);
  thunk_FUN_0042d9df();
  if (DAT_005e175c == (int *)0x0) {
    local_8 = CoInitialize((LPVOID)0x0);
    if (local_8 != 0) {
      thunk_FUN_00414ad0(s_ERROR__CoInitialize___x_004a1794,local_8);
    }
    local_8 = CoCreateInstance((IID *)&DAT_00494b78,(LPUNKNOWN)0x0,1,(IID *)&DAT_00495118,
                               &DAT_005e175c);
    if (local_8 != 0) {
      thunk_FUN_00414ad0(s_ERROR__CoCreateInstance___x_004a17b0,local_8);
      return;
    }
  }
  MultiByteToWideChar(0,0,s_intro_avi_004a17d0,-1,local_4c,0x1e);
  local_8 = (**(code **)(*DAT_005e175c + 0x34))(DAT_005e175c,local_4c,0);
  if (local_8 == 0) {
    MultiByteToWideChar(0,0,s_Video_Renderer_004a17f4,-1,local_4c,0x1e);
    local_8 = (**(code **)(*DAT_005e175c + 0x18))(DAT_005e175c,local_4c,&local_c);
    if (local_8 == 0) {
      local_8 = (**(code **)*local_c)(local_c,&DAT_00494db8,&local_54);
      if (local_8 == 0) {
        local_58 = 0;
        local_8 = (**(code **)(*local_54 + 0x28))(local_54,&local_58);
        thunk_FUN_00414ad0(s_DD_bob___x_004a1804,local_58);
        (**(code **)(*local_54 + 8))(local_54);
      }
      else {
        thunk_FUN_00414ad0(s_Couldn_t_get_DDV___x_004a1810,local_8);
      }
      (**(code **)(*local_c + 8))(local_c);
    }
    else {
      thunk_FUN_00414ad0(s_Couldn_t_get_filter___x_004a1828,local_8);
    }
    local_50 = (int *)0x0;
    local_8 = (**(code **)*DAT_005e175c)(DAT_005e175c,&DAT_00494878,&local_50);
    if (local_8 == 0) {
      local_8 = (**(code **)(*local_50 + 0x7c))(local_50,DAT_004c2b58);
      if (local_8 != 0) {
        thunk_FUN_00414ad0(s_message_drain_failed___x_004a1844,local_8);
      }
      local_8 = (**(code **)(*local_50 + 0x90))(local_50,0xffffffff);
      if (local_8 != 0) {
        thunk_FUN_00414ad0(s_full_screen_switch_failed___x_004a1860,local_8);
      }
      local_8 = (**(code **)(*local_50 + 0x8c))(local_50,&local_5c);
      thunk_FUN_00414ad0(s_Full_Screen_Get___x___x_004a1880,local_8,local_5c);
      local_8 = (**(code **)(*local_50 + 8))(local_50);
      local_8 = (**(code **)*DAT_005e175c)(DAT_005e175c,&DAT_00494838,&local_10);
      if (local_8 != 0) {
        thunk_FUN_00414ad0(s_ERROR_creating_IMediaControl___x_004a18b4,local_8);
      }
      (**(code **)(*local_10 + 0x1c))(local_10);
      (**(code **)(*local_10 + 8))(local_10);
      DAT_005e1758 = 1;
      do {
        iVar1 = thunk_FUN_00449e3c();
      } while (iVar1 != 0);
    }
    else {
      thunk_FUN_00414ad0(s_Couldn_t_get_VW___x_004a189c,local_8);
    }
  }
  else {
    thunk_FUN_00414ad0(s_ERROR__RenderFile___x_004a17dc,local_8);
  }
  return;
}
```

---

# 0012_batch_0008 — détails (4/8)

## FUN_00432940 — 0x432940

- Classification : internal
- Corps : `0x432940–0x432996`
- État : pseudocode obtenu
- Evidence : `ev_4eb0998c4b2b58fe0da8699a9f4e721cbf9b6075b80d203ee00c6e796de04bc4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00432940(short *param_1,short *param_2)

{
  return (int)*(short *)(*(int *)(DAT_005dc64c + 0x9c) + *param_1 * 0x60 + 0x42a) -
         (int)*(short *)(*(int *)(DAT_005dc64c + 0x9c) + *param_2 * 0x60 + 0x42a);
}
```

---

## FUN_00432997 — 0x432997

- Classification : internal
- Corps : `0x432997–0x432b40`
- État : pseudocode obtenu
- Evidence : `ev_df4800f070ff40192a72fd999dc31628c81a99f9616958a4ca2fdf4f3d5bfd6c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x40150a` — `thunk_FUN_0040f9af`
- `0x401749` — `thunk_FUN_00414c97`
- `0x4017f3` — `thunk_FUN_0040fb84`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402176` — `thunk_FUN_00414bf7`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49f598` — "island"
- `0x49f598` — "island"
- `0x49f5a0` — "editor"
- `0x49f5a0` — "editor"
- `0x49f5a8` — "DATA\\%s%02d.SHP"
- `0x49f5b8` — "DATA\\islandxx.SHP"
- `0x49f5cc` — "Load island shape %s failed.\n"
- `0x49f5f0` — "C:\\float\\src\\islewin.cpp"
- `0x49f60c` — "bkgshape"
- `0x49f618` — "C:\\float\\src\\islewin.cpp"

### Pseudocode Ghidra

```c
void FUN_00432997(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *unaff_FS_OFFSET;
  char *local_54;
  undefined1 local_50 [64];
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004916ac;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0040f6f7();
  local_8 = 0;
  local_54 = s_island_0049f598;
  if ((DAT_005dc654 != 0) && (DAT_005dc670 != 0)) {
    local_54 = s_editor_0049f5a0;
  }
  FUN_00472ca0(local_50,s_DATA__s_02d_SHP_0049f5a8,local_54,
               (int)(short)(&DAT_005eebf8)[DAT_0049f53c * 0x14f4]);
  iVar1 = thunk_FUN_0040f752(local_50,0x8000);
  iVar2 = 0;
  if (iVar1 != 0) {
    iVar2 = thunk_FUN_0040f752(s_DATA_islandxx_SHP_0049f5b8,0x8000);
  }
  if (iVar2 != 0) {
    thunk_FUN_00414ad0(s_Load_island_shape__s_failed__0049f5cc,local_50);
    thunk_FUN_00414b64(s_C__float_src_islewin_cpp_0049f5f0,0xa9,&DAT_0049f5ec);
  }
  uVar3 = thunk_FUN_0040f9af();
  iVar1 = thunk_FUN_00414bf7(uVar3);
  if (iVar1 == 0) {
    uVar3 = thunk_FUN_00414b64(s_C__float_src_islewin_cpp_0049f618,0xad,s_bkgshape_0049f60c);
  }
  else {
    uVar3 = 0;
  }
  thunk_FUN_0040fb84(iVar1);
  thunk_FUN_00404770(DAT_005dc64c + 0x74,iVar1,0,0,0,uVar3);
  thunk_FUN_0040f966();
  thunk_FUN_00414c97(iVar1);
  local_8 = 0xffffffff;
  thunk_FUN_0040f73f(uVar3,iVar2,0);
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

## FUN_00432b41 — 0x432b41

- Classification : internal
- Corps : `0x432b41–0x432c37`
- État : pseudocode obtenu
- Evidence : `ev_9eb52613cfbeaa5ea4fe5fa0f5cc7d523e2d4d7949b00b026df883a011a33229`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40212b` — `thunk_FUN_0042de17`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49cfc8` — "xTark"
- `0x49cff8` — "xLeviathan"
- `0x49f634` — "Editor on. <Shift-H> for help."
- `0x49f634` — "Editor on. <Shift-H> for help."
- `0x49f654` — "Editor off."
- `0x49f654` — "Editor off."
- `0x49f660` — "Add mode started."
- `0x49f660` — "Add mode started."
- `0x49f674` — "Add mode stopped."
- `0x49f674` — "Add mode stopped."
- `0x49f688` — "<A>        Toggle add mode"
- `0x49f688` — "<A>        Toggle add mode"
- `0x49f6a4` — "Saved padmap%02d files."
- `0x49f6bc` — "Tone cheat on."
- `0x49f6bc` — "Tone cheat on."
- `0x49f6cc` — "Tone cheat off."
- `0x49f6cc` — "Tone cheat off."
- `0x49f6dc` — "Floater Select OFF."
- `0x49f6dc` — "Floater Select OFF."
- `0x49f6f0` — "Floater Select ON."
- `0x49f6f0` — "Floater Select ON."
- `0x49f704` — "Add Floater OFF."
- `0x49f704` — "Add Floater OFF."
- `0x49f718` — "Add Floater ON."
- `0x49f718` — "Add Floater ON."
- `0x49f728` — "Current type: %s"

### Pseudocode Ghidra

```c
void FUN_00432b41(undefined4 param_1)

{
  char local_3c [52];
  char *local_8;
  
  local_8 = (char *)0x0;
  switch(param_1) {
  case 0:
    local_8 = s_Editor_on__<Shift_H>_for_help__0049f634;
    break;
  case 1:
    local_8 = s_Editor_off__0049f654;
    break;
  case 2:
    local_8 = s_Add_mode_started__0049f660;
    break;
  case 3:
    local_8 = s_Add_mode_stopped__0049f674;
    break;
  case 4:
    local_8 = s_<A>_Toggle_add_mode_0049f688;
    break;
  case 5:
    FUN_00472ca0(local_3c,s_Saved_padmap_02d_files__0049f6a4,(int)DAT_0049f53c);
    local_8 = local_3c;
    break;
  case 7:
    local_8 = s_Tone_cheat_on__0049f6bc;
    break;
  case 8:
    local_8 = s_Tone_cheat_off__0049f6cc;
    break;
  case 10:
    local_8 = s_Floater_Select_OFF__0049f6dc;
    break;
  case 0xb:
    local_8 = s_Floater_Select_ON__0049f6f0;
    break;
  case 0xc:
    local_8 = s_Add_Floater_OFF__0049f704;
    break;
  case 0xd:
    local_8 = s_Add_Floater_ON__0049f718;
    break;
  case 0xe:
    FUN_00472ca0(local_3c,s_Current_type___s_0049f728,s_xTark_0049cfc8 + DAT_0049f540 * 0xc);
    local_8 = local_3c;
  }
  if (local_8 != (char *)0x0) {
    thunk_FUN_0042de17(local_8,2);
  }
  return;
}
```

---

## FUN_00432c74 — 0x432c74

- Classification : internal
- Corps : `0x432c74–0x432e78`
- État : pseudocode obtenu
- Evidence : `ev_812dce32d68fb816fb9ffd51d7e3aee37973510d3bd087c2570046b2ef07544d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401712` — `thunk_FUN_004289a7`
- `0x4017bc` — `thunk_FUN_0045f807`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x472ca0` — `FUN_00472ca0`
- `0x472da0` — `FUN_00472da0`
- `0x472db0` — `FUN_00472db0`

### Chaînes référencées

- `0x49cfc8` — "xTark"
- `0x49d0b8` — "FA_Nothing"
- `0x49f73c` — "Tone: %d; Unused: %d"
- `0x49f754` — " CL: %d CG: %d"
- `0x49f764` — "Hall: B:%d,C:%d,M:%d"
- `0x49f77c` — "Task List:"
- `0x49f788` — "%s (%d): %s, %d, %d; %d"

### Pseudocode Ghidra

```c
void FUN_00432c74(void)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int local_80;
  short local_7c;
  short local_78;
  short local_76;
  short local_72;
  short local_70;
  short local_6e;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  undefined4 *local_58;
  int local_54;
  undefined *local_50;
  undefined1 local_4c [3];
  undefined1 local_49;
  undefined1 local_38 [52];
  
  local_5c = DAT_005dc64c + 8;
  local_58 = &DAT_004c2f30;
  local_50 = &DAT_006191b8 + DAT_0049f538 * 0x14a0;
  thunk_FUN_0042de03();
  local_68 = thunk_FUN_004289a7();
  local_68 = local_68 + 2;
  local_64 = 0;
  FUN_00472ca0(local_38,s_Tone___d__Unused___d_0049f73c,*(undefined4 *)(local_50 + 0x3c),
               *(undefined4 *)(local_50 + 0x40));
  if (DAT_0049f53c == 0xe) {
    local_6c = (int)DAT_0061f8de;
    FUN_00472ca0(local_4c,s_CL___d_CG___d_0049f754,(int)*(short *)(&DAT_0061f8e0 + local_6c * 2),
                 (int)*(short *)(&DAT_0061f8fc + local_6c * 2));
    FUN_00472db0(local_38,local_4c);
  }
  thunk_FUN_004289c0(local_5c,0,local_64,local_38);
  local_64 = local_64 + local_68;
  local_54 = thunk_FUN_0045f807();
  if (local_54 != 0) {
    FUN_00472ca0(local_38,s_Hall__B__d_C__d_M__d_0049f764,(int)*(short *)(local_54 + 0x28),
                 (int)*(short *)(local_54 + 0x2a),(int)*(short *)(local_54 + 0x2c));
    thunk_FUN_004289c0(local_5c,0,local_64,local_38);
  }
  local_64 = local_64 + local_68;
  thunk_FUN_004289c0(local_5c,0,local_64,s_Task_List__0049f77c);
  local_64 = local_64 + local_68;
  for (local_60 = 0; local_60 < 0x40; local_60 = local_60 + 1) {
    piVar2 = &DAT_006183bc + local_60 * 5;
    piVar3 = &local_80;
    for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar3 = *piVar2;
      piVar2 = piVar2 + 1;
      piVar3 = piVar3 + 1;
    }
    if (local_80 != 0) {
      FUN_00472da0(local_4c,s_xTark_0049cfc8 + local_78 * 0xc);
      local_49 = 0;
      FUN_00472ca0(local_38,s__s___d____s___d___d___d_0049f788,local_4c,(int)local_76,
                   s_FA_Nothing_0049d0b8 + local_70 * 0x10 + 3,(int)local_72,(int)local_6e,
                   (int)local_7c);
      thunk_FUN_004289c0(local_5c,0,local_64,local_38);
      local_64 = local_64 + local_68;
    }
  }
  return;
}
```

---

## FUN_00432e79 — 0x432e79

- Classification : internal
- Corps : `0x432e79–0x432f1c`
- État : pseudocode obtenu
- Evidence : `ev_a0e3498f3ed8eb4104bd4b63541e89783f53f63203d538d435ff69c00c824209`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4015a0` — `thunk_FUN_00432997`
- `0x401f14` — `thunk_FUN_00404770`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020e0` — `thunk_FUN_0040ec89`

### Chaînes référencées

- `0x49f7a0` — "padmap"

### Pseudocode Ghidra

```c
void FUN_00432e79(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int local_8;
  
  if (DAT_005dc680 == 0) {
    thunk_FUN_00406604(DAT_005dc64c + 0x74,0);
  }
  else {
    thunk_FUN_00432997();
  }
  for (local_8 = 0; local_8 < DAT_005dc674; local_8 = local_8 + 1) {
    uVar4 = (&DAT_005dbf04)[local_8 * 3];
    uVar3 = (&DAT_005dbf00)[local_8 * 3];
    uVar2 = (&DAT_005dbf08)[local_8 * 3];
    uVar1 = thunk_FUN_0040ec89(s_padmap_0049f7a0,1);
    thunk_FUN_00404770(DAT_005dc64c + 0x74,uVar1,uVar2,uVar3,uVar4);
  }
  *(undefined4 *)(DAT_005dc64c + 0x168) = 1;
  return;
}
```

---

## FUN_00432f1d — 0x432f1d

- Classification : internal
- Corps : `0x432f1d–0x432f4e`
- État : pseudocode obtenu
- Evidence : `ev_3aa380ef5cc664858543d200985846e4c69a1444d49835ee61359a04a6ef8652`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401456` — `thunk_FUN_00432b41`
- `0x4021da` — `thunk_FUN_00432e79`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00432f1d(void)

{
  thunk_FUN_00432e79();
  DAT_005dc674 = 0;
  DAT_0049f544 = 0xffffffff;
  DAT_005dc678 = 0;
  thunk_FUN_00432b41(0);
  return;
}
```

---

## FUN_00432f4f — 0x432f4f

- Classification : internal
- Corps : `0x432f4f–0x432f71`
- État : pseudocode obtenu
- Evidence : `ev_cac37d904f1669771327b6a81e50bb10c883053d2024cbd06f812d816696b3b0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401456` — `thunk_FUN_00432b41`
- `0x4015a0` — `thunk_FUN_00432997`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00432f4f(void)

{
  thunk_FUN_00432997();
  *(undefined4 *)(DAT_005dc64c + 0x168) = 1;
  thunk_FUN_00432b41(1);
  return;
}
```

---

## FUN_00432f72 — 0x432f72

- Classification : internal
- Corps : `0x432f72–0x433167`
- État : pseudocode obtenu
- Evidence : `ev_5f11b3af15a6fbf53480c1c54c9d1b64d6efcfb24c616e61fadd15ca4371235d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401456` — `thunk_FUN_00432b41`
- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x401744` — `thunk_FUN_00448436`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401cee` — `thunk_FUN_0040fd80`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401f5f` — `thunk_FUN_0042dc4e`
- `0x472ca0` — `FUN_00472ca0`
- `0x472e90` — `_strlen`

### Chaînes référencées

- `0x49f7a8` — "padmap%02d.gif"
- `0x49f7b8` — "padmap%02d.txt"
- `0x49f7c8` — "NUM_LOCATIONS %d\n\n\n"
- `0x49f7dc` — ";Number    X     Y   Type     Special_value\n\n"
- `0x49f80c` — "%2d%10d%6d   %s  %d\n"

### Pseudocode Ghidra

```c
void FUN_00432f72(void)

{
  size_t sVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_498 [1036];
  int local_8c;
  char local_88 [100];
  undefined1 local_24 [20];
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004916c2;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  FUN_00472ca0(local_24,s_padmap_02d_gif_0049f7a8,(int)DAT_0049f53c);
  thunk_FUN_0042dc4e(0,0x100,local_498);
  thunk_FUN_00448436(local_24,**(undefined4 **)(DAT_005dc64c + 0x74),local_498,0xa00,0x140);
  thunk_FUN_0040f6f7();
  local_8 = 0;
  FUN_00472ca0(local_24,s_padmap_02d_txt_0049f7b8,(int)DAT_0049f53c);
  thunk_FUN_0040f752(local_24,0x4301);
  FUN_00472ca0(local_88,s_NUM_LOCATIONS__d_0049f7c8,DAT_005dc674);
  sVar1 = _strlen(local_88);
  thunk_FUN_0040fd80(local_88,sVar1);
  FUN_00472ca0(local_88,s__Number_X_Y_Type_Special_value_0049f7dc);
  sVar1 = _strlen(local_88);
  thunk_FUN_0040fd80(local_88,sVar1);
  for (local_8c = 0; local_8c < DAT_005dc674; local_8c = local_8c + 1) {
    FUN_00472ca0(local_88,s__2d_10d_6d__s__d_0049f80c,local_8c,(&DAT_005dbf00)[local_8c * 3],
                 (&DAT_005dbf04)[local_8c * 3],
                 (&PTR_s_smpad_0049f548)[(&DAT_005dbf08)[local_8c * 3]],0);
    sVar1 = _strlen(local_88);
    thunk_FUN_0040fd80(local_88,sVar1);
  }
  thunk_FUN_00432b41(5);
  local_8 = 0xffffffff;
  thunk_FUN_0040f73f();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

## FUN_00433168 — 0x433168

- Classification : internal
- Corps : `0x433168–0x433270`
- État : pseudocode obtenu
- Evidence : `ev_8b0d0f14d0a0faa0a1a3295bb245790391fa5cb973848cd8d3bd12075e0c8522`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021da` — `thunk_FUN_00432e79`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00433168(void)

{
  short *local_c;
  int local_8;
  
  DAT_005dc674 = (int)*(short *)(*(int *)(DAT_005dc64c + 0x9c) + 0x29a8);
  local_c = (short *)(*(int *)(DAT_005dc64c + 0x9c) + 0x428);
  for (local_8 = 0; local_8 < *(short *)(*(int *)(DAT_005dc64c + 0x9c) + 0x29a8);
      local_8 = local_8 + 1) {
    if (*(int *)(local_c + 2) == 0) {
      (&DAT_005dbf08)[local_8 * 3] = *(undefined4 *)(local_c + 6);
    }
    else if (*(int *)(local_c + 2) == 1) {
      (&DAT_005dbf08)[local_8 * 3] = 3;
    }
    else if (*(int *)(local_c + 2) == 2) {
      (&DAT_005dbf08)[local_8 * 3] = 4;
    }
    else {
      (&DAT_005dbf08)[local_8 * 3] = 5;
    }
    (&DAT_005dbf00)[local_8 * 3] = (int)*local_c;
    (&DAT_005dbf04)[local_8 * 3] = (int)local_c[1];
    local_c = local_c + 0x30;
  }
  DAT_0049f544 = 0xffffffff;
  thunk_FUN_00432e79();
  return;
}
```

---

## FUN_00433271 — 0x433271

- Classification : internal
- Corps : `0x433271–0x433389`
- État : pseudocode obtenu
- Evidence : `ev_41d5cca8a5b0aae08c940b97c1a45ae38823a8a3c9b5c4f8d4b359f1a86e8c67`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021da` — `thunk_FUN_00432e79`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00433271(int param_1,int param_2)

{
  int local_1c;
  int local_18;
  int local_10;
  int local_c;
  int local_8;
  
  if ((DAT_005dc67c == 0) || (DAT_0049f544 == -1)) {
    local_c = 100;
    local_8 = -1;
    for (local_10 = 0; local_10 < DAT_005dc674; local_10 = local_10 + 1) {
      if ((&DAT_005dbf00)[local_10 * 3] - param_1 < 0) {
        local_18 = -((&DAT_005dbf00)[local_10 * 3] - param_1);
      }
      else {
        local_18 = (&DAT_005dbf00)[local_10 * 3] - param_1;
      }
      if ((&DAT_005dbf04)[local_10 * 3] - param_2 < 0) {
        local_1c = -((&DAT_005dbf04)[local_10 * 3] - param_2);
      }
      else {
        local_1c = (&DAT_005dbf04)[local_10 * 3] - param_2;
      }
      if (local_18 + local_1c < local_c) {
        local_8 = local_10;
        local_c = local_18 + local_1c;
      }
    }
    DAT_0049f544 = local_8;
  }
  else {
    (&DAT_005dbf00)[DAT_0049f544 * 3] = param_1;
    (&DAT_005dbf04)[DAT_0049f544 * 3] = param_2;
    thunk_FUN_00432e79();
  }
  return;
}
```

---

## FUN_0043338a — 0x43338a

- Classification : internal
- Corps : `0x43338a–0x4333ef`
- État : pseudocode obtenu
- Evidence : `ev_fc8050eb5b0665150d5435b6e14c3d99ecca06d5c8ad3da488ff121583d7f7aa`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021da` — `thunk_FUN_00432e79`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043338a(undefined4 param_1,undefined4 param_2)

{
  if (DAT_005dc674 < 100) {
    (&DAT_005dbf00)[DAT_005dc674 * 3] = param_1;
    (&DAT_005dbf04)[DAT_005dc674 * 3] = param_2;
    (&DAT_005dbf08)[DAT_005dc674 * 3] = DAT_005dc688;
    DAT_0049f544 = DAT_005dc674;
    DAT_005dc674 = DAT_005dc674 + 1;
    thunk_FUN_00432e79();
  }
  return;
}
```

---

## FUN_004333f0 — 0x4333f0

- Classification : internal
- Corps : `0x4333f0–0x433448`
- État : pseudocode obtenu
- Evidence : `ev_be76f6a05e25447abae7a61a8b2005441197b2e86f9966220d11910f7a1fc6f2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021da` — `thunk_FUN_00432e79`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004333f0(void)

{
  int local_8;
  
  if (DAT_0049f544 != -1) {
    if ((&DAT_005dbf08)[DAT_0049f544 * 3] == 5) {
      local_8 = 0;
    }
    else {
      local_8 = (&DAT_005dbf08)[DAT_0049f544 * 3] + 1;
    }
    (&DAT_005dbf08)[DAT_0049f544 * 3] = local_8;
    DAT_005dc688 = local_8;
    thunk_FUN_00432e79();
  }
  return;
}
```

---

## FUN_00433449 — 0x433449

- Classification : internal
- Corps : `0x433449–0x4334cd`
- État : pseudocode obtenu
- Evidence : `ev_0fbaac245261461d7bd9cba8f4dbb614f84a44388a8f83af4dc82ccb428aff5c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021da` — `thunk_FUN_00432e79`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00433449(void)

{
  int iVar1;
  int local_8;
  
  if ((DAT_0049f544 != -1) && (0 < DAT_005dc674)) {
    for (local_8 = DAT_0049f544; local_8 < DAT_005dc674 + -1; local_8 = local_8 + 1) {
      iVar1 = local_8 + 1;
      (&DAT_005dbf00)[local_8 * 3] = (&DAT_005dbf00)[iVar1 * 3];
      (&DAT_005dbf04)[local_8 * 3] = (&DAT_005dbf04)[iVar1 * 3];
      (&DAT_005dbf08)[local_8 * 3] = (&DAT_005dbf08)[iVar1 * 3];
    }
    DAT_005dc674 = DAT_005dc674 + -1;
    DAT_0049f544 = -1;
    thunk_FUN_00432e79();
  }
  return;
}
```

---

## FUN_004334ce — 0x4334ce

- Classification : internal
- Corps : `0x4334ce–0x4336b6`
- État : pseudocode obtenu
- Evidence : `ev_9d4effbf419b2608ab97220e863f96019bd578d5b9de60b9e93dab16fcf3231b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401285` — `thunk_FUN_00436e06`
- `0x4012cb` — `thunk_FUN_0045b8d1`
- `0x40150f` — `thunk_FUN_0046ff6f`
- `0x402013` — `thunk_FUN_0045aafd`
- `0x472ca0` — `FUN_00472ca0`
- `0x472da0` — `FUN_00472da0`
- `0x474b90` — `FUN_00474b90`

### Chaînes référencées

- `0x49f824` — "FLTADV"
- `0x49f834` — "LEVIBRK"
- `0x49f844` — "%s%s."
- `0x49f864` — "winend"
- `0x49f864` — "winend"
- `0x49f86c` — "loosend"
- `0x49f86c` — "loosend"

### Pseudocode Ghidra

```c
void FUN_004334ce(int param_1,uint param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  char *local_74;
  char local_54 [80];
  
  local_54[0] = '\0';
  if ((param_1 == 6) && (param_2 == DAT_0049f538)) {
    uVar1 = thunk_FUN_00429ebe(s_FLTADV_0049f824,0);
    thunk_FUN_00436e06(uVar1,1);
  }
  else if (param_1 == 10) {
    if (param_2 == 0xffffffff) {
      DAT_0049f831 = (char)DAT_0049f538 + '0';
      uVar1 = thunk_FUN_00429ebe(&DAT_0049f82c,0);
      FUN_00472da0(local_54,uVar1);
    }
    else if ((int)param_2 < 8) {
      uVar1 = thunk_FUN_00429ebe(s_LEVIBRK_0049f834,0);
      DAT_0049f840 = (char)param_2 + '0';
      uVar2 = thunk_FUN_00429ebe(&DAT_0049f83c,0);
      FUN_00472ca0(local_54,s__s_s__0049f844,uVar1,uVar2);
    }
    if (local_54[0] != '\0') {
      thunk_FUN_00436e06(local_54,1);
    }
  }
  else if (param_1 == 0xc) {
    if ((int)param_2 < 4) {
      DAT_0049f84f = (char)param_2 + '1';
      iVar3 = thunk_FUN_0045b8d1(&DAT_0049f84c);
      if (iVar3 == 0) {
        thunk_FUN_0045aafd(&DAT_0049f84c,0,0,0);
      }
    }
    else if (param_2 == 0xe) {
      iVar3 = thunk_FUN_0045b8d1(&DAT_0049f854);
      if (iVar3 == 0) {
        thunk_FUN_0045aafd(&DAT_0049f85c,0,0,0);
      }
    }
    else {
      uVar4 = FUN_00474b90();
      if ((uVar4 & 1) != 0) {
        thunk_FUN_0046ff6f(0);
      }
    }
  }
  else if (param_1 == 0xb) {
    local_74 = (char *)0x0;
    if (param_2 == 0) {
      local_74 = s_winend_0049f864;
    }
    else if (((param_2 & 0xff) == 3) && ((int)param_2 >> 0x10 == DAT_0049f538)) {
      local_74 = s_loosend_0049f86c;
    }
    if (local_74 != (char *)0x0) {
      thunk_FUN_0045aafd(local_74,0,0,0);
    }
  }
  return;
}
```

---

## FUN_004336b7 — 0x4336b7

- Classification : internal
- Corps : `0x4336b7–0x43370a`
- État : pseudocode obtenu
- Evidence : `ev_4224048dd8a599bbfc881065f1426a94413c38138b1dd2d9f7d54d6495bf82e8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a96` — `thunk_FUN_00433727`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_004336b7(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004916d5;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004942a8;
  thunk_FUN_00433727();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_0043370b — 0x43370b

- Classification : internal
- Corps : `0x43370b–0x433726`
- État : pseudocode obtenu
- Evidence : `ev_880cc97ab771a6993274c7a7958aeacfaf429c8b6f5203b04358591e899cc762`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043370b(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004942a8;
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_00433727 — 0x433727

- Classification : internal
- Corps : `0x433727–0x4337b9`
- État : pseudocode obtenu
- Evidence : `ev_46d138384ac2c3f8a53ac2872057b35f9e69ea2ecc9cb93a90d04234cfdecf09`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00433727(void)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x70) = 0xffff;
  *(undefined2 *)(in_ECX + 0x72) = 0;
  *(undefined4 *)(in_ECX + 0x88) = 0;
  *(int *)(in_ECX + 0x74) = in_ECX + 0x88;
  *(undefined4 *)(in_ECX + 0x9c) = 0;
  _memset(&DAT_005dbee0,0,0x1e);
  *(undefined4 *)(in_ECX + 0x174) = 0;
  *(undefined2 *)(in_ECX + 0x178) = 0;
  *(undefined2 *)(in_ECX + 0x17a) = 0xffff;
  *(undefined2 *)(in_ECX + 0x17c) = 0xffff;
  *(undefined2 *)(in_ECX + 0x17e) = 0;
  return;
}
```

---

## FUN_004337ba — 0x4337ba

- Classification : internal
- Corps : `0x4337ba–0x4337d8`
- État : pseudocode obtenu
- Evidence : `ev_91aa7266f35a7bbe8a16dc5d70eb83be4dc0fd5e8e41927db667e91c2d6efce7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021f3` — `thunk_FUN_0046c7df`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004337ba(void)

{
  undefined4 uVar1;
  int in_ECX;
  
  uVar1 = thunk_FUN_0046c7df(in_ECX);
  *(undefined4 *)(in_ECX + 4) = uVar1;
  return;
}
```

---


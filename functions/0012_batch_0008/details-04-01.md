# 0012_batch_0008 — détails (1/2)

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

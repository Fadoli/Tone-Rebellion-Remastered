# 0012_batch_0008 — détails (2/8)

## FUN_0042f150 — 0x42f150

- Classification : internal
- Corps : `0x42f150–0x42f302`
- État : pseudocode obtenu
- Evidence : `ev_fd6888838d129751b7b836f120b2f943abe1617bc91b1afc0b81c8323578cacf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401e65` — `thunk_FUN_0046c4a5`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49e700` — "BC_OnOff"
- `0x49ea30` — "Not in WINDOWS.TXT: %s"
- `0x49ea48` — "IWLocControl"
- `0x49ea58` — "locwnd"
- `0x49ea60` — "C:\\float\\src\\islemast.cpp"
- `0x49ea84` — "%s string not found (gamey.txt)"
- `0x49eaa4` — "FALSE"
- `0x49eaac` — "C:\\float\\src\\islemast.cpp"

### Pseudocode Ghidra

```c
void FUN_0042f150(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int local_20;
  undefined1 local_18 [8];
  char *local_10;
  int local_c;
  short local_8;
  
  local_c = 0;
  local_8 = 0;
  if (DAT_0049e9bc == 1) {
    for (local_20 = 0; local_20 < 0x1d; local_20 = local_20 + 1) {
      local_10 = s_BC_OnOff_0049e700 + local_20 * 0x14;
      iVar1 = thunk_FUN_0046c4a5(local_10,0);
      if (iVar1 == 0) {
        *(undefined4 *)(&DAT_005c3770 + local_20 * 4) = 0;
        thunk_FUN_00414ad0(s_Not_in_WINDOWS_TXT___s_0049ea30,local_10);
      }
      else {
        local_8 = local_8 + 1;
        *(undefined4 *)(&DAT_005c3770 + local_20 * 4) = *(undefined4 *)(iVar1 + 4);
        if (local_c == 0) {
          local_c = *(int *)(iVar1 + 4);
        }
        *(undefined4 *)(iVar1 + 0x38) = 0;
        *(undefined4 *)(iVar1 + 0x3c) = 0;
        *(int *)(iVar1 + 100) = local_20;
      }
    }
    DAT_0049e9bc = 0;
    iVar1 = thunk_FUN_0046c4a5(s_IWLocControl_0049ea48,0);
    if (iVar1 == 0) {
      uVar3 = thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049ea60,0xeb,s_locwnd_0049ea58);
    }
    else {
      uVar3 = 0;
    }
    if (local_c != 0) {
      *(int *)(iVar1 + 0x70) = local_c;
      *(short *)(iVar1 + 0x74) = local_8;
    }
    for (local_20 = 0; local_20 < 0x15; local_20 = local_20 + 1) {
      FUN_00472ca0(local_18,&DAT_0049ea7c,local_20,uVar3);
      uVar2 = thunk_FUN_00429ebe(local_18,0);
      *(undefined4 *)(&DAT_0049e948 + local_20 * 4) = uVar2;
      if (*(int *)(&DAT_0049e948 + local_20 * 4) == 0) {
        thunk_FUN_00414ad0(s__s_string_not_found__gamey_txt__0049ea84,local_18);
        thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049eaac,0xfb,s_FALSE_0049eaa4);
      }
    }
  }
  return;
}
```

---

## FUN_0042f303 — 0x42f303

- Classification : internal
- Corps : `0x42f303–0x42f730`
- État : pseudocode obtenu
- Evidence : `ev_90d7ff8d12f0e53364c8b54762c45c8dcbaec5ad67998ad1ccfe6672424ed00a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010e6` — `thunk_FUN_0042f755`
- `0x4014fb` — `thunk_FUN_0042f9c5`
- `0x4018e3` — `thunk_FUN_0046c3bc`

### Chaînes référencées

- `0x49eac8` — "IWConstruct"
- `0x49ead4` — "IWConstructInfo"
- `0x49eae4` — "IWTasks"
- `0x49eaec` — "IWTaskOptions"
- `0x49eafc` — "IWTrade"
- `0x49eb04` — "IWDiplomacy"
- `0x49eb10` — "IWLocInfo"
- `0x49eb1c` — "IWLocControl"
- `0x49eb2c` — "IWGlyphs"
- `0x49eb38` — "IWInventory"
- `0x49eb44` — "IWTextInfo"
- `0x49eb50` — "IWTextInfo2"
- `0x49eb5c` — "IWTaskInfo"
- `0x49eb68` — "IWFltInfo"
- `0x49eb74` — "IWEffList"
- `0x49eb80` — "IWSFXList"
- `0x49eb8c` — "IWLocInfo"
- `0x49eb98` — "IWLocControl"
- `0x49eba8` — "IWTextInfo"
- `0x49ebb4` — "IWConstruct"
- `0x49ebc0` — "IWConstructInfo"
- `0x49ebd0` — "IWTasks"
- `0x49ebd8` — "IWTaskOptions"
- `0x49ebe8` — "IWTaskInfo"
- `0x49ebf4` — "IWLocInfo"
- `0x49ec00` — "IWLocControl"
- `0x49ec10` — "IWTextInfo"
- `0x49ec1c` — "IWTextInfo"
- `0x49ec28` — "IWLocControl"
- `0x49ec38` — "IWInventory"
- `0x49ec44` — "IWTextInfo"
- `0x49ec50` — "IWLocControl"
- `0x49ec60` — "IWGlyphs"
- `0x49ec6c` — "IWTextInfo"
- `0x49ec78` — "IWLocControl"
- `0x49ec88` — "IWTrade"
- `0x49ec90` — "IWTextInfo"
- `0x49ec9c` — "IWLocControl"
- `0x49ecac` — "IWDiplomacy"
- `0x49ecb8` — "IWEffList"
- `0x49ecc4` — "IWSFXList"

### Pseudocode Ghidra

```c
void FUN_0042f303(undefined4 param_1)

{
  short sVar1;
  short sVar2;
  
  DAT_005c37f0 = 0;
  thunk_FUN_0046c3bc(s_IWConstruct_0049eac8,2,0,0);
  thunk_FUN_0046c3bc(s_IWConstructInfo_0049ead4,2,0,0);
  thunk_FUN_0046c3bc(s_IWTasks_0049eae4,2,0,0);
  thunk_FUN_0046c3bc(s_IWTaskOptions_0049eaec,2,0,0);
  thunk_FUN_0046c3bc(s_IWTrade_0049eafc,2,0,0);
  thunk_FUN_0046c3bc(s_IWDiplomacy_0049eb04,2,0,0);
  thunk_FUN_0046c3bc(s_IWLocInfo_0049eb10,2,0,0);
  thunk_FUN_0046c3bc(s_IWLocControl_0049eb1c,2,0,0);
  thunk_FUN_0046c3bc(s_IWGlyphs_0049eb2c,2,0,0);
  thunk_FUN_0046c3bc(s_IWInventory_0049eb38,2,0,0);
  thunk_FUN_0046c3bc(s_IWTextInfo_0049eb44,2,0,0);
  thunk_FUN_0046c3bc(s_IWTextInfo2_0049eb50,2,0,0);
  thunk_FUN_0046c3bc(s_IWTaskInfo_0049eb5c,2,0,0);
  thunk_FUN_0046c3bc(s_IWFltInfo_0049eb68,2,0,0);
  thunk_FUN_0046c3bc(s_IWEffList_0049eb74,2,0,0);
  thunk_FUN_0046c3bc(s_IWSFXList_0049eb80,2,0,0);
  DAT_0049e9cc = param_1;
  switch(param_1) {
  case 0:
    thunk_FUN_0042f9c5();
    thunk_FUN_0046c3bc(s_IWLocInfo_0049eb8c,1,0,0);
    thunk_FUN_0046c3bc(s_IWLocControl_0049eb98,1,0,0);
    thunk_FUN_0046c3bc(s_IWTextInfo_0049eba8,1,0,0);
    sVar1 = *(short *)(&DAT_0061a580 + DAT_0049f538 * 0x14a0);
    sVar2 = *(short *)(DAT_0049f538 * 0x14a0 + 0x61a582);
    *(undefined **)(DAT_005c37e4 + 0x16c) = &DAT_005ec640 + sVar2 * 0x60 + sVar1 * 0x29e8;
    thunk_FUN_0042f755(&DAT_005ec640 + sVar2 * 0x60 + sVar1 * 0x29e8,0);
    break;
  case 1:
    thunk_FUN_0042f9c5();
    thunk_FUN_0046c3bc(s_IWConstruct_0049ebb4,1,0,0);
    thunk_FUN_0046c3bc(s_IWConstructInfo_0049ebc0,1,0,0);
    break;
  case 2:
    thunk_FUN_0042f9c5();
    DAT_005c37f0 = 1;
    thunk_FUN_0046c3bc(s_IWTasks_0049ebd0,1,0,0);
    thunk_FUN_0046c3bc(s_IWTaskOptions_0049ebd8,1,0,0);
    thunk_FUN_0046c3bc(s_IWTaskInfo_0049ebe8,1,0,0);
    break;
  case 3:
    thunk_FUN_0042f9c5();
    thunk_FUN_0046c3bc(s_IWLocInfo_0049ebf4,1,0,0);
    thunk_FUN_0046c3bc(s_IWLocControl_0049ec00,1,0,0);
    thunk_FUN_0046c3bc(s_IWTextInfo_0049ec10,1,0,0);
    break;
  case 4:
    thunk_FUN_0046c3bc(s_IWTextInfo_0049ec1c,1,0,0);
    thunk_FUN_0046c3bc(s_IWLocControl_0049ec28,1,0,0);
    thunk_FUN_0046c3bc(s_IWInventory_0049ec38,1,0,0);
    break;
  case 5:
    thunk_FUN_0046c3bc(s_IWTextInfo_0049ec44,1,0,0);
    thunk_FUN_0046c3bc(s_IWLocControl_0049ec50,1,0,0);
    thunk_FUN_0046c3bc(s_IWGlyphs_0049ec60,1,0,0);
    break;
  case 6:
    thunk_FUN_0046c3bc(s_IWTextInfo_0049ec90,1,0,0);
    thunk_FUN_0046c3bc(s_IWLocControl_0049ec9c,1,0,0);
    thunk_FUN_0046c3bc(s_IWDiplomacy_0049ecac,1,0,0);
    break;
  case 7:
    thunk_FUN_0046c3bc(s_IWTextInfo_0049ec6c,1,0,0);
    thunk_FUN_0046c3bc(s_IWLocControl_0049ec78,1,0,0);
    thunk_FUN_0046c3bc(s_IWTrade_0049ec88,1,0,0);
    break;
  case 8:
    thunk_FUN_0042f9c5();
    thunk_FUN_0046c3bc(s_IWEffList_0049ecb8,1,0,0);
    thunk_FUN_0046c3bc(s_IWSFXList_0049ecc4,1,0,0);
  }
  return;
}
```

---

## FUN_0042f755 — 0x42f755

- Classification : internal
- Corps : `0x42f755–0x42f8f6`
- État : pseudocode obtenu
- Evidence : `ev_d476b7f99e42cedc0ad151604c90402e91be6b30ad028bfe4d3cda2f00b98bb0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x401721` — `thunk_FUN_0045302a`
- `0x401762` — `thunk_FUN_0042f303`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402009` — `thunk_FUN_00438120`
- `0x40224d` — `thunk_FUN_00450070`

### Chaînes référencées

- `0x49ecd4` — "C:\\float\\src\\islemast.cpp"
- `0x49ecf0` — "IWLocInfo"
- `0x49ecfc` — "IWLocControl"
- `0x49ed0c` — "IWTextInfo"

### Pseudocode Ghidra

```c
void FUN_0042f755(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_8;
  
  if (param_1 == 0) {
    uVar2 = thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049ecd4,0x186,&DAT_0049ecd0);
  }
  else {
    uVar2 = 0;
  }
  if (param_2 != 0) {
    thunk_FUN_0042f303(3,uVar2);
  }
  thunk_FUN_0046c3bc(s_IWLocInfo_0049ecf0,0x350b,param_1,0);
  thunk_FUN_0046c3bc(s_IWLocControl_0049ecfc,0x350b,param_1,0);
  thunk_FUN_0046c3bc(s_IWTextInfo_0049ed0c,0x3039,0,param_1);
  DAT_005c3800 = 0;
  thunk_FUN_0045302a(DAT_0049f538,&DAT_005c36f8,&DAT_005c3800);
  for (local_8 = 0; local_8 < DAT_005c3800; local_8 = local_8 + 1) {
    if (*(int *)(&DAT_005c3770 + *(int *)(&DAT_005c36f8 + local_8 * 4) * 4) != 0) {
      if ((0x14 < *(int *)(&DAT_005c36f8 + local_8 * 4)) &&
         (*(int *)(&DAT_005c36f8 + local_8 * 4) < 0x1d)) {
        iVar1 = thunk_FUN_00450070(param_1,*(undefined4 *)(&DAT_005c36f8 + local_8 * 4));
        thunk_FUN_0046c371(*(undefined4 *)
                            (&DAT_005c3770 + *(int *)(&DAT_005c36f8 + local_8 * 4) * 4),0xc,
                           iVar1 << 1,0);
      }
      thunk_FUN_0046c371(*(undefined4 *)(&DAT_005c3770 + *(int *)(&DAT_005c36f8 + local_8 * 4) * 4),
                         1,0,0);
    }
  }
  iVar1 = thunk_FUN_00450385();
  if ((iVar1 != 0) && (*(int *)(param_1 + 0x14) == DAT_0049f538)) {
    DAT_0049e9c8 = *(undefined2 *)(param_1 + 0x18);
    thunk_FUN_00438120(iVar1);
  }
  return;
}
```

---

## FUN_0042f8f7 — 0x42f8f7

- Classification : internal
- Corps : `0x42f8f7–0x42f9c4`
- État : pseudocode obtenu
- Evidence : `ev_8763470bf48503ef3e6fb2162d49472b4a764cb5b3af9902847999123f19a22a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010e6` — `thunk_FUN_0042f755`
- `0x401762` — `thunk_FUN_0042f303`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401dac` — `thunk_FUN_004207f2`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- `0x49ed18` — "IWTextInfo"
- `0x49ed24` — "IWFltInfo"
- `0x49ed30` — "IWFltInfo"

### Pseudocode Ghidra

```c
void FUN_0042f8f7(void)

{
  int iVar1;
  
  iVar1 = thunk_FUN_004207f2();
  if (iVar1 == 0) {
    if ((*(int *)(DAT_005c37e4 + 0x16c) == 0) ||
       (*(short *)(*(int *)(DAT_005c37e4 + 0x16c) + 0x18) == -1)) {
      thunk_FUN_0042f303(0);
    }
  }
  else {
    iVar1 = thunk_FUN_0045c3bb();
    if (iVar1 != 0) {
      *(int *)(DAT_005c37e4 + 0x16c) = iVar1;
      thunk_FUN_0042f755(iVar1,1);
    }
  }
  thunk_FUN_0046c3bc(s_IWTextInfo_0049ed18,2,0,0);
  thunk_FUN_0046c3bc(s_IWFltInfo_0049ed24,1,0,0);
  thunk_FUN_0046c3bc(s_IWFltInfo_0049ed30,0x350b,*(undefined4 *)(DAT_005c37e4 + 0x170),0);
  return;
}
```

---

## FUN_0042f9c5 — 0x42f9c5

- Classification : internal
- Corps : `0x42f9c5–0x42fa0e`
- État : pseudocode obtenu
- Evidence : `ev_089b3feeaa4e2d38fde8460adf0dacbe8856c17d80f170efcb78f4f720aa256c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042f9c5(void)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 0x1d; local_8 = local_8 + 1) {
    if (*(int *)(&DAT_005c3770 + local_8 * 4) != 0) {
      thunk_FUN_0046c371(*(undefined4 *)(&DAT_005c3770 + local_8 * 4),2,0,0);
    }
  }
  return;
}
```

---


# 0010_batch_0006 — détails (3/3)

## FUN_0041a8df — 0x41a8df

- Classification : internal
- Corps : `0x41a8df–0x41afba`
- État : pseudocode obtenu
- Evidence : `ev_ea10958170235dede7e42dfdd9e76d05696e96e3e798b34bbda94abd45a23d83`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401131` — `thunk_FUN_00412cac`
- `0x401217` — `thunk_FUN_0045f849`
- `0x401429` — `thunk_FUN_00428191`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x4019b5` — `thunk_FUN_0046562b`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402153` — `thunk_FUN_0045f0cd`
- `0x4022de` — `thunk_FUN_0042d9cd`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49c7c4` — "shape"
- `0x49c7cc` — "C:\\float\\src\\endgame.cpp"
- `0x49c7e8` — "POINTS"
- `0x49c7f8` — "C:\\float\\src\\endgame.cpp"
- `0x49c814` — "%s: %s"
- `0x49c824` — "%d %s: %s"
- `0x49c830` — "GLYPHS"
- `0x49c838` — "%d %s"
- `0x49c840` — "SHADSTR"
- `0x49c848` — "%d %s"
- `0x49c850` — "FLOTTRIB"
- `0x49c86c` — "FLOTLOSS"
- `0x49cfc8` — "xTark"
- `0x49cfc8` — "xTark"
- `0x49cfec` — "xDyla"
- `0x49cfec` — "xDyla"
- `0x49d008` — "xTarks"
- `0x49d008` — "xTarks"
- `0x49d008` — "xTarks"
- `0x49d02c` — "xDyla"
- `0x49d02c` — "xDyla"
- `0x49d02c` — "xDyla"

### Pseudocode Ghidra

```c
void FUN_0041a8df(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int in_ECX;
  undefined2 extraout_var;
  undefined1 local_e8 [4];
  int local_e4;
  undefined1 local_e0 [4];
  undefined1 local_dc [4];
  undefined1 local_d8 [4];
  int local_d4;
  int local_d0;
  undefined4 local_cc;
  undefined4 auStack_c8 [10];
  undefined1 local_a0 [72];
  undefined4 local_58;
  int local_54;
  undefined1 local_50 [4];
  int local_4c;
  int local_48;
  int local_44;
  undefined4 local_40;
  undefined *local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 local_1c;
  undefined *local_18;
  undefined1 local_14 [4];
  int local_10;
  undefined *local_c;
  undefined1 local_8 [4];
  
  iVar1 = thunk_FUN_00412cac((int)*(short *)(in_ECX + 0x70));
  if ((((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) && (DAT_004befe0 != 0)) &&
     (iVar1 != -1)) {
    uVar2 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar2;
    local_d0 = thunk_FUN_0040e864(CONCAT22(extraout_var,DAT_0049c684));
    if (local_d0 == 0) {
      thunk_FUN_00414b64(s_C__float_src_endgame_cpp_0049c7cc,0x1ae,s_shape_0049c7c4);
    }
    local_58 = thunk_FUN_00429ebe(s_POINTS_0049c7e8,0);
    local_e4 = (int)*(short *)(in_ECX + 0x70);
    if (local_e4 < 0) {
      local_e4 = 0;
    }
    if (3 < local_e4) {
      local_e4 = 3;
    }
    local_c = &DAT_006191b8 + local_e4 * 0x14a0;
    local_44 = thunk_FUN_0042de0d();
    if (local_44 == 0) {
      thunk_FUN_00414b64(s_C__float_src_endgame_cpp_0049c7f8,0x1bc,&DAT_0049c7f0);
    }
    uVar3 = thunk_FUN_0042dd0f(6);
    *(uint *)(local_44 + 8) = uVar3 & 0xff;
    thunk_FUN_0045f849(&local_cc,&local_54,local_e0,local_14,local_8,local_2c,local_28,local_dc,
                       local_d8,local_50,local_e8,local_24);
    local_4c = local_54 + 9;
    if (local_4c < 9) {
      local_4c = 9;
    }
    if (0x12 < local_4c) {
      local_4c = 0x12;
    }
    thunk_FUN_00404770(in_ECX + 8,local_d0,local_4c,0xfffffff0,0xffffffed);
    if (local_e4 == 1) {
      *(undefined4 *)(local_44 + 8) = 0xda;
    }
    else if (local_e4 == 2) {
      *(undefined4 *)(local_44 + 8) = 100;
    }
    else if (local_e4 == 3) {
      *(undefined4 *)(local_44 + 8) = 0xa7;
    }
    else {
      *(undefined4 *)(local_44 + 8) = 0xcf;
    }
    local_18 = &DAT_004beff0 + iVar1 * 0x40;
    FUN_00472ca0(local_a0,s__s___s_0049c814,local_18,s_xTarks_0049d008 + local_e4 * 0xc);
    thunk_FUN_004289c0(in_ECX + 8,10,2,local_a0);
    thunk_FUN_00428191(in_ECX + 8,local_e4,0,0,0xa2,0x18,8);
    *(undefined4 *)(local_44 + 8) = 0xdd;
    local_3c = &DAT_0049c81c;
    for (local_10 = 0; local_10 < 10; local_10 = local_10 + 1) {
      local_3c[4] = (char)local_10 + '0';
      uVar2 = thunk_FUN_00429ebe(local_3c,0);
      auStack_c8[local_10] = uVar2;
    }
    FUN_00472ca0(local_a0,s__d__s___s_0049c824,local_cc,local_58,auStack_c8[local_54]);
    thunk_FUN_004289c0(in_ECX + 8,10,0xc,local_a0);
    *(undefined4 *)(local_44 + 8) = 0x9c;
    local_30 = thunk_FUN_0045f0cd();
    local_20 = thunk_FUN_00429ebe(s_GLYPHS_0049c830,0);
    FUN_00472ca0(local_a0,s__d__s_0049c838,local_30,local_20);
    thunk_FUN_004289c0(in_ECX + 8,10,0x7a,local_a0);
    *(undefined4 *)(local_44 + 8) = 0xa0;
    local_d4 = 0;
    for (local_48 = 0; local_48 < 4; local_48 = local_48 + 1) {
      local_d4 = local_d4 + *(short *)(local_c + local_48 * 2 + 0x147e);
    }
    local_40 = thunk_FUN_00429ebe(s_SHADSTR_0049c840,0);
    FUN_00472ca0(local_a0,s__d__s_0049c848,local_d4,local_40);
    thunk_FUN_004289c0(in_ECX + 8,0x46,0x7a,local_a0);
    if (local_e4 == 1) {
      *(undefined4 *)(local_44 + 8) = 0xda;
    }
    else if (local_e4 == 2) {
      *(undefined4 *)(local_44 + 8) = 100;
    }
    else if (local_e4 == 3) {
      *(undefined4 *)(local_44 + 8) = 0xa7;
    }
    else {
      *(undefined4 *)(local_44 + 8) = 0xcf;
    }
    local_34 = thunk_FUN_00429ebe(s_FLOTTRIB_0049c850,0);
    local_38 = thunk_FUN_0046562b((int)(local_c + -0x6191b8) / 0x14a0,0xffffffff);
    FUN_00472ca0(local_a0,&DAT_0049c85c,local_38);
    thunk_FUN_004289c0(in_ECX + 8,0x8c,0x34,local_a0);
    if (local_38 == 1) {
      FUN_00472ca0(local_a0,&DAT_0049c860,s_xTark_0049cfc8 + local_e4 * 0xc);
    }
    else {
      FUN_00472ca0(local_a0,&DAT_0049c864,s_xTarks_0049d008 + local_e4 * 0xc);
    }
    thunk_FUN_004289c0(in_ECX + 8,0x8c,0x3e,local_a0);
    FUN_00472ca0(local_a0,&DAT_0049c868,local_34);
    thunk_FUN_004289c0(in_ECX + 8,0x8c,0x48,local_a0);
    local_1c = thunk_FUN_00429ebe(s_FLOTLOSS_0049c86c,0);
    FUN_00472ca0(local_a0,&DAT_0049c878,(int)*(short *)(local_c + 0x1498));
    thunk_FUN_004289c0(in_ECX + 8,0x8c,0x55,local_a0);
    if (*(short *)(&DAT_0061a650 + DAT_0049f538 * 0x14a0) == 1) {
      FUN_00472ca0(local_a0,&DAT_0049c87c,s_xTark_0049cfc8 + local_e4 * 0xc);
    }
    else {
      FUN_00472ca0(local_a0,&DAT_0049c880,s_xTarks_0049d008 + local_e4 * 0xc);
    }
    thunk_FUN_004289c0(in_ECX + 8,0x8c,0x5f,local_a0);
    FUN_00472ca0(local_a0,&DAT_0049c884,local_1c);
    thunk_FUN_004289c0(in_ECX + 8,0x8c,0x69,local_a0);
    thunk_FUN_0042d38a();
    thunk_FUN_0042d9cd(1);
  }
  return;
}
```

---

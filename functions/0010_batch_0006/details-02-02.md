# 0010_batch_0006 — détails (2/3)

## FUN_00419a6b — 0x419a6b

- Classification : internal
- Corps : `0x419a6b–0x41a7d5`
- État : pseudocode obtenu
- Evidence : `ev_01944b4c13c24ee61a5bcef30360dd50fe0d74a2c68507526092f64aa0c0c3ea`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
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
- `0x402234` — `thunk_FUN_0042892d`
- `0x4022de` — `thunk_FUN_0042d9cd`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49c688` — "POINTS"
- `0x49c690` — "shape"
- `0x49c698` — "C:\\float\\src\\endgame.cpp"
- `0x49c6bc` — "C:\\float\\src\\endgame.cpp"
- `0x49c6d8` — "IVISIT"
- `0x49c6e0` — "%d %s:"
- `0x49c6e8` — "%d %s"
- `0x49c6fc` — "%d %s"
- `0x49c704` — "GLYPHS"
- `0x49c70c` — "%d %s:"
- `0x49c714` — "%d %s"
- `0x49c71c` — "SHADSTR"
- `0x49c724` — "%d %s"
- `0x49c740` — "FLOTTRIB"
- `0x49c74c` — "%d %s %s:"
- `0x49c758` — "%d %s %s:"
- `0x49c764` — "%d %s"
- `0x49c76c` — "FLOTLOSS"
- `0x49c778` — "%d %s %s:"
- `0x49c784` — "%d %s %s:"
- `0x49c790` — "%d %s"
- `0x49c7a0` — "TROFTHE"
- `0x49c7b0` — "%d %s: %s"
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
void FUN_00419a6b(void)

{
  undefined2 extraout_var;
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int in_ECX;
  undefined *puVar4;
  undefined1 *puVar5;
  undefined4 auStack_120 [10];
  undefined *local_f8;
  undefined4 local_f4;
  int local_f0;
  undefined4 local_ec;
  int local_e8;
  undefined4 local_e4;
  int local_e0;
  int local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  int local_cc;
  undefined4 local_c8;
  int local_c4;
  int local_c0;
  undefined4 local_bc;
  int local_b8;
  undefined4 local_b4;
  int local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  int local_a4;
  undefined1 local_a0 [80];
  undefined4 local_50;
  int local_4c;
  undefined4 local_48;
  int local_44;
  int local_40;
  int local_3c;
  undefined4 auStack_38 [5];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined *local_18;
  undefined4 local_14;
  undefined *local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    local_b8 = DAT_0049f538;
    if (DAT_0049f538 < 0) {
      local_b8 = 0;
    }
    if (3 < local_b8) {
      local_b8 = 3;
    }
    local_50 = thunk_FUN_00429ebe(s_POINTS_0049c688,0);
    thunk_FUN_0045f849(&local_a8,&local_4c,&local_b4,&local_c,&local_8,&local_24,&local_20,&local_b0
                       ,&local_ac,&local_48,&local_bc,&local_1c);
    local_a4 = thunk_FUN_0040e864(CONCAT22(extraout_var,DAT_0049c684));
    if (local_a4 == 0) {
      thunk_FUN_00414b64(s_C__float_src_endgame_cpp_0049c698,0x71,s_shape_0049c690);
    }
    uVar1 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar1;
    if (0xfa < DAT_004c2994) {
      local_c0 = DAT_004bf118 + 5;
      if (7 < local_c0) {
        local_c0 = 7;
      }
      thunk_FUN_00404770(in_ECX + 8,local_a4,local_c0,0x1f,0x14);
    }
    if (300 < DAT_004c2994) {
      local_44 = DAT_004bf11c;
      if (DAT_004bf11c < 0) {
        local_44 = 0;
      }
      if (4 < local_44) {
        local_44 = 4;
      }
      thunk_FUN_00404770(in_ECX + 8,local_a4,local_44,0x1e3,0x13);
    }
    if (0x15e < DAT_004c2994) {
      local_44 = local_b8 + 0x23;
      thunk_FUN_00404770(in_ECX + 8,local_a4,local_44,0x16,0xbb);
      for (local_c4 = 0; local_c4 < 0xe; local_c4 = local_c4 + 1) {
        if (((int)*(short *)(&DAT_00619242 + local_b8 * 0x14a0) & 1 << ((byte)local_c4 & 0x1f)) != 0
           ) {
          thunk_FUN_00404770(in_ECX + 8,local_a4,local_c4 + 0x13,0x16,0xbb);
        }
      }
    }
    if (400 < DAT_004c2994) {
      thunk_FUN_00404770(in_ECX + 8,local_a4,8,0x1b7,0xbc);
    }
    if (500 < DAT_004c2994) {
      local_44 = local_4c + 9;
      if (local_44 < 9) {
        local_44 = 9;
      }
      if (0x12 < local_44) {
        local_44 = 0x12;
      }
      thunk_FUN_00404770(in_ECX + 8,local_a4,local_44,0xef,0x8d);
    }
    if (500 < DAT_004c2994) {
      thunk_FUN_00428191(in_ECX + 8,local_b8,0,0,0x19a,0xaf,8);
    }
    local_3c = thunk_FUN_0042de0d();
    if (local_3c == 0) {
      thunk_FUN_00414b64(s_C__float_src_endgame_cpp_0049c6bc,0xa6,&DAT_0049c6b4);
    }
    uVar2 = thunk_FUN_0042dd0f(6);
    *(uint *)(local_3c + 8) = uVar2 & 0xff;
    if (0xfa < DAT_004c2994) {
      *(undefined4 *)(local_3c + 8) = 0x9b;
      local_c8 = thunk_FUN_00429ebe(s_IVISIT_0049c6d8,0);
      FUN_00472ca0(local_a0,s__d__s__0049c6e0,local_24,local_c8);
      puVar5 = local_a0;
      uVar1 = 0x83;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,(0xcc - iVar3) / 2,uVar1,puVar5);
      *(undefined4 *)(local_3c + 8) = 0xdd;
      FUN_00472ca0(local_a0,s__d__s_0049c6e8,local_b4,local_50);
      puVar5 = local_a0;
      uVar1 = 0x8d;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,(0xcc - iVar3) / 2,uVar1,puVar5);
    }
    *(undefined4 *)(local_3c + 8) = 0xa0;
    local_18 = &DAT_0049c6f0;
    for (local_40 = 0; local_40 < 5; local_40 = local_40 + 1) {
      local_18[6] = (char)local_40 + '1';
      uVar1 = thunk_FUN_00429ebe(local_18,0);
      auStack_38[local_40] = uVar1;
    }
    if (300 < DAT_004c2994) {
      local_cc = DAT_004bf11c;
      FUN_00472ca0(local_a0,&DAT_0049c6f8,auStack_38[DAT_004bf11c]);
      puVar5 = local_a0;
      uVar1 = 0x83;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,(0x42f - iVar3) / 2,uVar1,puVar5);
      *(undefined4 *)(local_3c + 8) = 0xdd;
      FUN_00472ca0(local_a0,s__d__s_0049c6fc,local_c,local_50);
      puVar5 = local_a0;
      uVar1 = 0x8d;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,(0x42f - iVar3) / 2,uVar1,puVar5);
    }
    if (0x15e < DAT_004c2994) {
      *(undefined4 *)(local_3c + 8) = 0x9c;
      local_d4 = thunk_FUN_0045f0cd();
      local_d0 = thunk_FUN_00429ebe(s_GLYPHS_0049c704,0);
      FUN_00472ca0(local_a0,s__d__s__0049c70c,local_d4,local_d0);
      puVar5 = local_a0;
      uVar1 = 0x10a;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,(0xcc - iVar3) / 2,uVar1,puVar5);
      *(undefined4 *)(local_3c + 8) = 0xdd;
      FUN_00472ca0(local_a0,s__d__s_0049c714,local_8,local_50);
      puVar5 = local_a0;
      uVar1 = 0x114;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,(0xcc - iVar3) / 2,uVar1,puVar5);
    }
    if (400 < DAT_004c2994) {
      *(undefined4 *)(local_3c + 8) = 0xa0;
      local_e0 = 0;
      for (local_dc = 1; local_dc < 9; local_dc = local_dc + 1) {
        local_e0 = local_e0 + *(short *)(DAT_0049f538 * 0x14a0 + 0x61a636 + local_dc * 2);
      }
      local_d8 = thunk_FUN_00429ebe(s_SHADSTR_0049c71c,0);
      FUN_00472ca0(local_a0,s__d__s_0049c724,local_e0,local_d8);
      thunk_FUN_004289c0(in_ECX + 8,0x1c6,0xa7,local_a0);
      *(undefined4 *)(local_3c + 8) = 0xdd;
      FUN_00472ca0(local_a0,&DAT_0049c72c,local_50);
      thunk_FUN_004289c0(in_ECX + 8,0x1c6,0xb1,local_a0);
      FUN_00472ca0(local_a0,&DAT_0049c730,local_ac);
      thunk_FUN_004289c0(in_ECX + 8,0x1ca,0xec,local_a0);
      FUN_00472ca0(local_a0,&DAT_0049c734,local_48);
      thunk_FUN_004289c0(in_ECX + 8,0x1fa,0xec,local_a0);
      FUN_00472ca0(local_a0,&DAT_0049c738,local_bc);
      thunk_FUN_004289c0(in_ECX + 8,0x227,0xec,local_a0);
      FUN_00472ca0(local_a0,&DAT_0049c73c,local_1c);
      thunk_FUN_004289c0(in_ECX + 8,0x251,0xec,local_a0);
    }
    thunk_FUN_0042dd0f(6);
    if (local_b8 == 1) {
      local_14 = 0xda;
    }
    else if (local_b8 == 2) {
      local_14 = 100;
    }
    else if (local_b8 == 3) {
      local_14 = 0xa7;
    }
    else {
      local_14 = 0xcf;
    }
    if (0x1a9 < DAT_004c2994) {
      local_e4 = thunk_FUN_00429ebe(s_FLOTTRIB_0049c740,0);
      local_e8 = thunk_FUN_0046562b((DAT_0049f538 * 0x14a0) / 0x14a0,0xffffffff);
      *(undefined4 *)(local_3c + 8) = local_14;
      if (local_e8 == 1) {
        FUN_00472ca0(local_a0,s__d__s__s__0049c74c,1,s_xTark_0049cfc8 + local_b8 * 0xc,local_e4);
      }
      else {
        FUN_00472ca0(local_a0,s__d__s__s__0049c758,local_e8,s_xTarks_0049d008 + local_b8 * 0xc,
                     local_e4);
      }
      thunk_FUN_004289c0(in_ECX + 8,0x1c6,0x102,local_a0);
      *(undefined4 *)(local_3c + 8) = 0xdd;
      FUN_00472ca0(local_a0,s__d__s_0049c764,local_20,local_50);
      thunk_FUN_004289c0(in_ECX + 8,0x1ca,0x10c,local_a0);
    }
    if (0x1c2 < DAT_004c2994) {
      local_ec = thunk_FUN_00429ebe(s_FLOTLOSS_0049c76c,0);
      *(undefined4 *)(local_3c + 8) = local_14;
      if (*(short *)(&DAT_0061a650 + DAT_0049f538 * 0x14a0) == 1) {
        FUN_00472ca0(local_a0,s__d__s__s__0049c778,
                     (int)*(short *)(&DAT_0061a650 + DAT_0049f538 * 0x14a0),
                     s_xTark_0049cfc8 + local_b8 * 0xc,local_ec);
      }
      else {
        FUN_00472ca0(local_a0,s__d__s__s__0049c784,
                     (int)*(short *)(&DAT_0061a650 + DAT_0049f538 * 0x14a0),
                     s_xTarks_0049d008 + local_b8 * 0xc,local_ec);
      }
      thunk_FUN_004289c0(in_ECX + 8,0x1c6,0x11b,local_a0);
      *(undefined4 *)(local_3c + 8) = 0xdd;
      FUN_00472ca0(local_a0,s__d__s_0049c790,-local_b0,local_50);
      thunk_FUN_004289c0(in_ECX + 8,0x1ca,0x125,local_a0);
    }
    if (500 < DAT_004c2994) {
      *(undefined4 *)(local_3c + 8) = local_14;
      if (DAT_004befe0 != 0) {
        puVar4 = &DAT_004beff0 + DAT_004befec * 0x40;
        uVar1 = 0x9e;
        local_10 = puVar4;
        iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
        thunk_FUN_004289c0(in_ECX + 8,0x140 - iVar3 / 2,uVar1,puVar4);
      }
      local_f8 = &DAT_0049c798;
      for (local_f0 = 0; local_f0 < 10; local_f0 = local_f0 + 1) {
        local_f8[4] = (char)local_f0 + '0';
        uVar1 = thunk_FUN_00429ebe(local_f8,0);
        auStack_120[local_f0] = uVar1;
      }
      local_f4 = thunk_FUN_00429ebe(s_TROFTHE_0049c7a0,0);
      FUN_00472ca0(local_a0,&DAT_0049c7a8,local_f4,s_xTarks_0049d008 + local_b8 * 0xc);
      puVar5 = local_a0;
      uVar1 = 0xac;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,0x140 - iVar3 / 2,uVar1,puVar5);
      *(undefined4 *)(local_3c + 8) = 0xdd;
      FUN_00472ca0(local_a0,s__d__s___s_0049c7b0,local_a8,local_50,auStack_120[local_4c]);
      puVar5 = local_a0;
      uVar1 = 0x120;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,0x140 - iVar3 / 2,uVar1,puVar5);
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d9cd(1);
    DAT_004c2994 = DAT_004c2994 + 1;
    if (6000 < DAT_004c2994) {
      DAT_004c2994 = 0x1f5;
    }
  }
  return;
}
```

---

---

## FUN_0041a7d6 — 0x41a7d6

- Classification : internal
- Corps : `0x41a7d6–0x41a863`
- État : pseudocode obtenu
- Evidence : `ev_c1848c21aa9e848e44ecd1467a8f6bb368d8c6951753adb08457c68d0c662b17`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x401acd` — `thunk_FUN_0040ebde`

### Chaînes référencées

- `0x49c7bc` — "endgame"

### Pseudocode Ghidra

```c
undefined4 FUN_0041a7d6(short param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if (param_1 == 1) {
    DAT_0049c684 = thunk_FUN_0040ebde(s_endgame_0049c7bc);
    DAT_004c2994 = 0;
    uVar1 = thunk_FUN_004293c6(1,param_2,param_3);
  }
  else if ((param_1 < 6) || (7 < param_1)) {
    uVar1 = thunk_FUN_004293c6((int)param_1,param_2,param_3);
  }
  else {
    thunk_FUN_0046c1b4(1,0,0);
    uVar1 = 1;
  }
  return uVar1;
}
```

---

---

## FUN_0041a864 — 0x41a864

- Classification : internal
- Corps : `0x41a864–0x41a8b7`
- État : pseudocode obtenu
- Evidence : `ev_4a1d353919d567e3ec89acc023878f6dae1b9176a2aba8d1d844080d64779da1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401582` — `thunk_FUN_0041a8d4`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0041a864(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004914fc;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494098;
  thunk_FUN_0041a8d4();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0041a8b8 — 0x41a8b8

- Classification : internal
- Corps : `0x41a8b8–0x41a8d3`
- État : pseudocode obtenu
- Evidence : `ev_ba97d6dde0288991ab62121398c0adff8c433571dcc582ba1479d9e735f9920b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041a8b8(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494098;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_0041a8d4 — 0x41a8d4

- Classification : internal
- Corps : `0x41a8d4–0x41a8de`
- État : pseudocode obtenu
- Evidence : `ev_b545879e0edf81b7eadd018e5b0829116ac71e07f6e6e89557094d4fa6783ede`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041a8d4(void)

{
  return;
}
```

---

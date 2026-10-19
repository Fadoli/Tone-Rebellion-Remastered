# 0016_batch_0012 — détails (3/3)

## FUN_0045858a — 0x45858a

- Classification : internal
- Corps : `0x45858a–0x458cbe`
- État : pseudocode obtenu
- Evidence : `ev_2b0b260834ee2dcfa5ffa1a0a3e357b311405542d814c98e768eeb340b6a0742`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x40116d` — `thunk_FUN_0041e4d9`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x4017a3` — `thunk_FUN_0041e4c3`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401a87` — `thunk_FUN_0042704b`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401eab` — `thunk_FUN_0040bf98`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x4022de` — `thunk_FUN_0042d9cd`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x472c6c` — `__ftol`
- `0x472ca0` — `FUN_00472ca0`
- `0x472da0` — `FUN_00472da0`
- `0x4780f0` — `FID_conflict:__ctime64`

### Chaînes référencées

- `0x4a34ec` — "C:\\float\\src\\slidewin.cpp"
- `0x4a3508` — "ENDGAME"
- `0x4a3510` — "shape"
- `0x4a3518` — "C:\\float\\src\\slidewin.cpp"
- `0x4a3534` — "bildtone"
- `0x4a3540` — "shape"
- `0x4a3548` — "C:\\float\\src\\slidewin.cpp"
- `0x4a3568` — "tonecrys"
- `0x4a3574` — "shape"
- `0x4a357c` — "C:\\float\\src\\slidewin.cpp"
- `0x4a359c` — "magctone"
- `0x4a35a8` — "shape"
- `0x4a35b0` — "C:\\float\\src\\slidewin.cpp"
- `0x4a35d0` — "SURPFLOW"
- `0x4a35dc` — "%s %d"
- `0x4a35e4` — "POPSTR"
- `0x4a35ec` — "%s %d"
- `0x4a35f4` — "WORKSTR"
- `0x4a35fc` — "%s %d (%d%%)"
- `0x4a360c` — "LSTITLE"

### Pseudocode Ghidra

```c
void FUN_0045858a(void)

{
  undefined4 uVar1;
  char *pcVar2;
  int in_ECX;
  int iVar3;
  int *piVar4;
  int *piVar5;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar6;
  undefined4 uVar7;
  int local_134;
  undefined1 local_128 [20];
  int local_114;
  int local_110;
  undefined1 local_10c [64];
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_70;
  int local_6c;
  undefined4 local_68;
  undefined1 local_64 [52];
  int local_30 [6];
  int local_18;
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491af7;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  uVar1 = thunk_FUN_0042d28f();
  *(undefined4 *)(in_ECX + 8) = uVar1;
  piVar4 = (int *)(in_ECX + 8);
  piVar5 = local_30;
  for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar5 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  }
  local_30[1] = 0xd;
  local_30[3] = 0x138;
  local_30[2] = 0x24;
  local_30[4] = 0x86;
  local_14 = thunk_FUN_0042de0d();
  if (local_14 == 0) {
    thunk_FUN_00414b64(s_C__float_src_slidewin_cpp_004a34ec,0x28a,&DAT_004a34e4);
  }
  for (local_18 = 0; local_18 < 8; local_18 = local_18 + 1) {
    uVar7 = 0;
    uVar6 = 0;
    iVar3 = *(short *)(in_ECX + 0x1e) + local_18;
    uVar1 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
    thunk_FUN_00404770(local_30,uVar1,iVar3,uVar6,uVar7);
    if ((*(int *)(in_ECX + 0x70 + local_18 * 4) != 0) &&
       (*(int *)(in_ECX + 0x10c + local_18 * 0x80) != 0)) {
      iVar3 = thunk_FUN_0040ec89(s_ENDGAME_004a3508,1);
      if (iVar3 == 0) {
        thunk_FUN_00414b64(s_C__float_src_slidewin_cpp_004a3518,0x293,s_shape_004a3510);
      }
      local_114 = *(int *)(in_ECX + 0x108 + local_18 * 0x80);
      if (local_114 < 0) {
        local_114 = 0;
      }
      if (4 < local_114) {
        local_114 = 4;
      }
      thunk_FUN_00404770(local_30,iVar3,local_114,0xfffffffa,0xfffffffa);
      pcVar2 = FID_conflict___ctime64((__time64_t *)(in_ECX + 0x70 + local_18 * 4));
      FUN_00472da0(local_64,pcVar2);
      thunk_FUN_004289c0(local_30,2,2,local_64);
      local_110 = in_ECX + 0x98 + local_18 * 0x80;
      thunk_FUN_0040bf98(local_30,local_110,0xd2,0x5a,1,0x10000,0xffffffff);
      iVar3 = thunk_FUN_0040ec89(s_bildtone_004a3534,1);
      if (iVar3 == 0) {
        thunk_FUN_00414b64(s_C__float_src_slidewin_cpp_004a3548,0x2a3,s_shape_004a3540);
      }
      thunk_FUN_00404770(local_30,iVar3,0x18,0x8d,0x28);
      FUN_00472ca0(local_128,&DAT_004a3564,(int)*(short *)(local_110 + 0x28));
      thunk_FUN_004289c0(local_30,0x99,0x22,local_128);
      iVar3 = thunk_FUN_0040ec89(s_tonecrys_004a3568,1);
      if (iVar3 == 0) {
        thunk_FUN_00414b64(s_C__float_src_slidewin_cpp_004a357c,0x2a9,s_shape_004a3574);
      }
      thunk_FUN_00404770(local_30,iVar3,4,0x8d,0x46);
      FUN_00472ca0(local_128,&DAT_004a3598,(int)*(short *)(local_110 + 0x2a));
      thunk_FUN_004289c0(local_30,0x99,0x3f,local_128);
      iVar3 = thunk_FUN_0040ec89(s_magctone_004a359c,1);
      if (iVar3 == 0) {
        thunk_FUN_00414b64(s_C__float_src_slidewin_cpp_004a35b0,0x2af,s_shape_004a35a8);
      }
      thunk_FUN_00404770(local_30,iVar3,4,0x8d,0x61);
      FUN_00472ca0(local_128,&DAT_004a35cc,(int)*(short *)(local_110 + 0x2c));
      thunk_FUN_004289c0(local_30,0x99,0x5a,local_128);
      local_68 = thunk_FUN_00429ebe(s_SURPFLOW_004a35d0,0);
      FUN_00472ca0(local_10c,s__s__d_004a35dc,local_68,
                   *(undefined4 *)(in_ECX + 0xf8 + local_18 * 0x80));
      thunk_FUN_004289c0(local_30,0x69,0xe,local_10c);
      local_c0 = *(undefined4 *)(in_ECX + 0xfc + local_18 * 0x80);
      local_cc = *(undefined4 *)(in_ECX + 0x100 + local_18 * 0x80);
      local_70 = __ftol();
      thunk_FUN_0041e4c3();
      local_8 = 0;
      local_b8 = 0;
      local_bc = *(undefined4 *)(local_110 + 0x14);
      local_6c = 0;
      if (DAT_0049f538 == 3) {
        local_6c = -3;
      }
      local_c8 = DAT_005c37f4;
      DAT_005c37fc = 0;
      DAT_005c37f8 = 0;
      DAT_005c37f4 = 0;
      thunk_FUN_0042704b(local_30,&local_bc,0xfa,local_6c + 0x11,1,8,0x10000,0);
      DAT_005c37fc = local_c8;
      DAT_005c37f8 = local_c8;
      DAT_005c37f4 = local_c8;
      local_c4 = thunk_FUN_00429ebe(s_POPSTR_004a35e4,0);
      FUN_00472ca0(local_128,s__s__d_004a35ec,local_c4,local_c0);
      thunk_FUN_004289c0(local_30,0xe8,0x28,local_128);
      uVar1 = thunk_FUN_00429ebe(s_WORKSTR_004a35f4,0);
      FUN_00472ca0(local_128,s__s__d___d____004a35fc,uVar1,local_cc,local_70);
      thunk_FUN_004289c0(local_30,0xe8,0x32,local_128);
      local_8 = 0xffffffff;
      thunk_FUN_0041e4d9();
    }
    if (local_18 == 3) {
      local_30[2] = 0x24;
      local_30[4] = 0x86;
      local_30[1] = 0x146;
      local_30[3] = 0x271;
    }
    else {
      local_30[2] = local_30[2] + 0x6f;
      local_30[4] = local_30[4] + 0x6f;
    }
  }
  local_30[5] = thunk_FUN_0040ec89(s_LSTITLE_004a360c,1);
  if (local_30[5] != 0) {
    local_134 = DAT_0049f538;
    if (DAT_0049f538 < 0) {
      local_134 = 0;
    }
    if (DAT_0062d172 == 4) {
      local_134 = local_134 + 4;
    }
    if (local_134 < 0) {
      local_134 = 0;
    }
    if (7 < local_134) {
      local_134 = 7;
    }
    local_30[2] = 0;
    local_30[1] = 0;
    local_30[3] = 0x27f;
    local_30[4] = 0x1df;
    thunk_FUN_00404770(local_30,local_30[5],local_134,0x13d,0);
  }
  thunk_FUN_0042d38a();
  thunk_FUN_0042d9cd(1);
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

---

## FUN_004592d0 — 0x4592d0

- Classification : internal
- Corps : `0x4592d0–0x4592fd`
- État : pseudocode obtenu
- Evidence : `ev_1ad0327a3b1441996de96e949751e2ffad3b4f7318ca1dd81691ae20ba43bcd8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401ba4` — `thunk_FUN_00459310`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004592d0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00459310();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

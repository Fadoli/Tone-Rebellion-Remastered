# 0013_batch_0009 — détails (3/3)

## FUN_0043e5aa — 0x43e5aa

- Classification : internal
- Corps : `0x43e5aa–0x43ea27`
- État : pseudocode obtenu
- Evidence : `ev_bf0c6364cbdd6d347934dbdf3ecc156f6f17460cd80f9a1b49567d39fdcfcfb2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401429` — `thunk_FUN_00428191`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- `0x4a02e0` — "DIPLOMA"
- `0x4a02e8` — "shape"
- `0x4a02f0` — "C:\\float\\src\\iwhall.cpp"
- `0x4a0308` — "smfont&&bgfont"
- `0x4a0318` — "C:\\float\\src\\iwhall.cpp"
- `0x4a0330` — "TRDIPHI"
- `0x4a0338` — "TRCOMHI"

### Pseudocode Ghidra

```c
void FUN_0043e5aa(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int in_ECX;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int local_68;
  int local_64;
  int local_60;
  int local_48;
  int local_38 [12];
  int local_8;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    uVar1 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar1;
    if (DAT_004c2bac == 0) {
      thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
    }
    else {
      uVar6 = 0;
      uVar5 = 0;
      iVar4 = (int)*(short *)(in_ECX + 0x1e);
      uVar1 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar1,iVar4,uVar5,uVar6);
    }
    iVar4 = thunk_FUN_0040ec89(s_DIPLOMA_004a02e0,1);
    if (iVar4 == 0) {
      thunk_FUN_00414b64(s_C__float_src_iwhall_cpp_004a02f0,0x2ca,s_shape_004a02e8);
    }
    iVar2 = thunk_FUN_0042de0d();
    iVar3 = thunk_FUN_0042de03();
    if ((iVar2 == 0) || (iVar3 == 0)) {
      thunk_FUN_00414b64(s_C__float_src_iwhall_cpp_004a0318,0x2d0,s_smfont__bgfont_004a0308);
    }
    local_38[7] = 0x108;
    local_38[8] = 0x12d;
    local_38[9] = 0x145;
    local_38[3] = 0x17a;
    local_38[4] = 0x182;
    local_38[5] = 0x17b;
    local_38[0] = 0xdc;
    local_38[1] = 300;
    local_38[2] = 0x17c;
    DAT_005e16e8 = DAT_005e16e8 + 1;
    if (DAT_005e16e8 % 3 == 0) {
      *(short *)(in_ECX + 0x70) = *(short *)(in_ECX + 0x70) + 1;
    }
    if (4 < *(short *)(in_ECX + 0x70)) {
      *(undefined2 *)(in_ECX + 0x70) = 0;
    }
    local_38[0xb] = DAT_0049f538;
    thunk_FUN_00428191(in_ECX + 8,DAT_0049f538,0,0,
                       (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 2,10,8);
    local_38[10] = 0;
    for (local_38[6] = 0; local_38[6] < 4; local_38[6] = local_38[6] + 1) {
      if (local_38[6] != DAT_0049f538) {
        iVar2 = *(int *)(&DAT_00619290 + local_38[6] * 4 + DAT_0049f538 * 0x14a0);
        local_48 = local_38[10] * 7;
        if (*(int *)(&DAT_006192a0 + local_38[6] * 4 + DAT_0049f538 * 0x14a0) != 0) {
          local_48 = local_48 + 1 + (int)*(short *)(in_ECX + 0x70);
        }
        thunk_FUN_00404770(in_ECX + 8,iVar4,local_48,
                           local_38[local_38[10] + 7] - *(int *)(in_ECX + 0xc),
                           local_38[local_38[10] + 3] - *(int *)(in_ECX + 0x10));
        if (*(short *)(in_ECX + 0x72) == local_38[10]) {
          thunk_FUN_00404770(in_ECX + 8,iVar4,(local_38[10] + 1) * 7 + -1,
                             local_38[local_38[10] + 7] - *(int *)(in_ECX + 0xc),
                             local_38[local_38[10] + 3] - *(int *)(in_ECX + 0x10));
        }
        if (*(short *)(in_ECX + 0x74) == local_38[10]) {
          if (local_38[10] == 1) {
            local_60 = (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + -0x14;
          }
          else {
            local_60 = (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + -0x1e;
          }
          thunk_FUN_00404770(in_ECX + 8,iVar4,0x17,local_38[local_38[10]] - *(int *)(in_ECX + 0xc),
                             local_60 + -0xf);
        }
        local_38[0xb] = local_38[6];
        if (local_38[10] == 1) {
          local_64 = (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + -0x14;
        }
        else {
          local_64 = (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + -0x1e;
        }
        thunk_FUN_00428191(in_ECX + 8,local_38[6],0,0,
                           (local_38[local_38[10]] - *(int *)(in_ECX + 0xc)) + 0x12,local_64,8);
        local_48 = 0x16;
        if (iVar2 != 0) {
          local_48 = 0x15;
        }
        if (local_38[10] == 1) {
          local_68 = (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + -0x14;
        }
        else {
          local_68 = (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + -0x1e;
        }
        thunk_FUN_00404770(in_ECX + 8,iVar4,local_48,local_38[local_38[10]] - *(int *)(in_ECX + 0xc)
                           ,local_68 + -0xf);
        local_38[10] = local_38[10] + 1;
      }
    }
    local_8 = 0;
    if (*(short *)(in_ECX + 0x74) == -1) {
      if (*(short *)(in_ECX + 0x72) != -1) {
        local_8 = thunk_FUN_00429ebe(s_TRCOMHI_004a0338,0);
      }
    }
    else {
      local_8 = thunk_FUN_00429ebe(s_TRDIPHI_004a0330,0);
    }
    if (local_8 != 0) {
      thunk_FUN_004289c0(in_ECX + 8,(*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 2 + 0xf,7,
                         local_8);
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,1);
  }
  return;
}
```

---

---

## FUN_0043ea28 — 0x43ea28

- Classification : internal
- Corps : `0x43ea28–0x43ea7b`
- État : pseudocode obtenu
- Evidence : `ev_5eb42013f1f5b76e547883ee18f9e60580de7de9afd6ce37b3b4bde0a9b59015`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`
- `0x4021a3` — `thunk_FUN_0043ea98`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0043ea28(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004917f2;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494428;
  thunk_FUN_0043ea98();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0043ea7c — 0x43ea7c

- Classification : internal
- Corps : `0x43ea7c–0x43ea97`
- État : pseudocode obtenu
- Evidence : `ev_b6405061ce0965e29d135fdc31592c42d6d41c85051280ffb9d64a03a4fc317b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043ea7c(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494428;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_0043ea98 — 0x43ea98

- Classification : internal
- Corps : `0x43ea98–0x43eab4`
- État : pseudocode obtenu
- Evidence : `ev_604c52d146d9518ee7fbeb7e937c4056149c352528b692177a6ab7f078d93562`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043ea98(void)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x70) = 0;
  *(undefined2 *)(in_ECX + 0x72) = 0;
  return;
}
```

---

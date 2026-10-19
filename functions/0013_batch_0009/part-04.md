# 0013_batch_0009 — détails (4/5)

## FUN_0043eab5 — 0x43eab5

- Classification : internal
- Corps : `0x43eab5–0x43ec5b`
- État : pseudocode obtenu
- Evidence : `ev_ea3ad70447386ab4b8c197d46ebcfa383adefee3572540b95bbf6eaee09341b7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401569` — `thunk_FUN_0046c558`
- `0x401587` — `thunk_FUN_0043ec78`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a0340` — "TradeZERO"
- `0x4a034c` — "TradeDOIT"
- `0x4a0358` — "mhZero&&mhDoit"
- `0x4a0368` — "C:\\float\\src\\iwhall.cpp"
- `0x4a0380` — "IWTextInfo"

### Pseudocode Ghidra

```c
void FUN_0043eab5(short param_1,int param_2,int param_3)

{
  int in_ECX;
  
  switch(param_1) {
  case 1:
    if ((*(short *)(in_ECX + 0x70) == 0) && (*(short *)(in_ECX + 0x72) == 0)) {
      thunk_FUN_0046c558(s_TradeZERO_004a0340,3,in_ECX + 0x70);
      thunk_FUN_0046c558(s_TradeDOIT_004a034c,3,in_ECX + 0x72);
      if ((*(short *)(in_ECX + 0x70) == 0) || (*(short *)(in_ECX + 0x72) == 0)) {
        thunk_FUN_00414b64(s_C__float_src_iwhall_cpp_004a0368,0x340,s_mhZero__mhDoit_004a0358);
      }
    }
    thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x70),1,0,0);
    thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x72),1,0,0);
    _memset((void *)(in_ECX + 0x74),0,0x12);
    thunk_FUN_0046c3bc(s_IWTextInfo_004a0380,0x3039,9,0);
    break;
  case 2:
    if ((*(short *)(in_ECX + 0x70) != 0) && (*(short *)(in_ECX + 0x72) != 0)) {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x70),2,0,0);
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x72),2,0,0);
    }
    break;
  case 6:
  case 7:
    if (DAT_0062c6bc == *(int *)(in_ECX + 4)) {
      thunk_FUN_0043ec78(param_2 - *(int *)(in_ECX + 0xc),param_3 - *(int *)(in_ECX + 0x10),
                         param_1 == 6);
      return;
    }
  }
  thunk_FUN_004293c6(param_1,param_2,param_3);
  return;
}
```

---

## FUN_0043ec78 — 0x43ec78

- Classification : internal
- Corps : `0x43ec78–0x43edab`
- État : pseudocode obtenu
- Evidence : `ev_3b5f4720935dc2a46a88ff1fbfea436d9ef271c9dc1729588ff092dad9112b44`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043ec78(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int in_ECX;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((param_2 < 0x25) || (0x6d < param_2)) {
    uVar1 = 0;
  }
  else if ((param_1 < 0x28) || (0x9a < param_1)) {
    uVar1 = 0;
  }
  else {
    local_8 = (param_1 + -0x28) / 0x21;
    local_c = (param_2 + -0x25) / 0x13;
    if (local_8 < 0) {
      local_8 = 0;
    }
    if (2 < local_8) {
      local_8 = 2;
    }
    if (local_c < 0) {
      local_c = 0;
    }
    if (2 < local_c) {
      local_c = 2;
    }
    *(ushort *)(in_ECX + 0x74 + local_c * 6 + local_8 * 2) =
         *(short *)(in_ECX + 0x74 + local_c * 6 + local_8 * 2) +
         ((-(ushort)(param_3 != 0) & 2) - 1) * 10;
    if (*(short *)(in_ECX + 0x74 + local_c * 6 + local_8 * 2) < 0) {
      *(undefined2 *)(in_ECX + 0x74 + local_c * 6 + local_8 * 2) = 0;
    }
    if (1000 < *(short *)(in_ECX + 0x74 + local_c * 6 + local_8 * 2)) {
      *(undefined2 *)(in_ECX + 0x74 + local_c * 6 + local_8 * 2) = 1000;
    }
    uVar1 = 1;
  }
  return uVar1;
}
```

---

## FUN_0043edac — 0x43edac

- Classification : internal
- Corps : `0x43edac–0x43f221`
- État : pseudocode obtenu
- Evidence : `ev_ce422c3de4f4cbea0f4a05e91a4bceeed3f8bd5614b6c565a9389730931e5f1c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x40119f` — `thunk_FUN_0046c371`
- `0x401429` — `thunk_FUN_00428191`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x40174e` — `thunk_FUN_004109a6`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x402234` — `thunk_FUN_0042892d`
- `0x402306` — `thunk_FUN_004106dd`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x472ca0` — `FUN_00472ca0`
- `0x472da0` — `FUN_00472da0`

### Chaînes référencées

- `0x4a038c` — "smfont&&bgfont"
- `0x4a039c` — "C:\\float\\src\\iwhall.cpp"
- `0x4a03b4` — "bildtone"
- `0x4a03b4` — "bildtone"
- `0x4a03b4` — "bildtone"
- `0x4a03c0` — "tonecrys"
- `0x4a03c0` — "tonecrys"
- `0x4a03c0` — "tonecrys"
- `0x4a03cc` — "magctone"
- `0x4a03cc` — "magctone"
- `0x4a03cc` — "magctone"
- `0x4a03d8` — "shape"
- `0x4a03e0` — "C:\\float\\src\\iwhall.cpp"
- `0x4a0400` — "TRZERO"
- `0x4a0408` — "TRDOIT"

### Pseudocode Ghidra

```c
void FUN_0043edac(void)

{
  undefined4 uVar1;
  int in_ECX;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int local_60;
  undefined1 local_5c [8];
  int local_54;
  int local_50;
  int local_4c;
  int local_48 [4];
  int local_38;
  int local_34;
  undefined4 local_30;
  char local_2c [4];
  char local_28 [4];
  char local_24;
  undefined2 local_23;
  undefined1 local_21;
  char local_20 [4];
  char local_1c [4];
  char local_18;
  undefined2 local_17;
  undefined1 local_15;
  char local_14 [4];
  char local_10 [4];
  char local_c;
  undefined2 local_b;
  undefined1 local_9;
  int local_8;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    uVar1 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar1;
    if (DAT_004c2bac == 0) {
      thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
    }
    else {
      uVar8 = 0;
      uVar7 = 0;
      iVar2 = (int)*(short *)(in_ECX + 0x1e);
      uVar1 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar1,iVar2,uVar7,uVar8);
    }
    local_50 = thunk_FUN_0042de0d();
    local_4c = thunk_FUN_0042de03();
    if ((local_50 == 0) || (local_4c == 0)) {
      thunk_FUN_00414b64(s_C__float_src_iwhall_cpp_004a039c,0x393,s_smfont__bgfont_004a038c);
    }
    local_30 = thunk_FUN_004106dd(1,0);
    piVar5 = (int *)(in_ECX + 8);
    piVar6 = local_48;
    for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar6 = *piVar5;
      piVar5 = piVar5 + 1;
      piVar6 = piVar6 + 1;
    }
    local_38 = local_48[2] + 0x66;
    local_48[2] = local_48[2] + 0x16;
    for (local_34 = 0; local_34 < 3; local_34 = local_34 + 1) {
      local_48[1] = *(int *)(in_ECX + 0xc) + 0x28 + local_34 * 0x26;
      local_48[3] = local_48[1] + 0x1c;
      if (local_34 < DAT_0049f538) {
        local_54 = local_34;
      }
      else {
        local_54 = local_34 + 1;
      }
      thunk_FUN_00428191(in_ECX + 8,local_54,0,0,local_34 * 0x26 + 0x37,0xc,8);
      iVar4 = *(int *)(in_ECX + 0x10) - local_48[2];
      iVar3 = *(int *)(in_ECX + 0xc) - local_48[1];
      iVar2 = (int)*(short *)(in_ECX + 0x1e);
      uVar1 = local_30;
      uVar7 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_004109a6(local_48,uVar7,iVar2,iVar3,iVar4,uVar1);
    }
    local_48[1] = *(int *)(in_ECX + 0xc) + 0x28;
    local_48[3] = *(int *)(in_ECX + 0xc) + 0xbe;
    local_2c[0] = s_bildtone_004a03b4[0];
    local_2c[1] = s_bildtone_004a03b4[1];
    local_2c[2] = s_bildtone_004a03b4[2];
    local_2c[3] = s_bildtone_004a03b4[3];
    local_28[0] = s_bildtone_004a03b4[4];
    local_28[1] = s_bildtone_004a03b4[5];
    local_28[2] = s_bildtone_004a03b4[6];
    local_28[3] = s_bildtone_004a03b4[7];
    local_24 = s_bildtone_004a03b4[8];
    local_23 = 0;
    local_21 = 0;
    local_20[0] = s_tonecrys_004a03c0[0];
    local_20[1] = s_tonecrys_004a03c0[1];
    local_20[2] = s_tonecrys_004a03c0[2];
    local_20[3] = s_tonecrys_004a03c0[3];
    local_1c[0] = s_tonecrys_004a03c0[4];
    local_1c[1] = s_tonecrys_004a03c0[5];
    local_1c[2] = s_tonecrys_004a03c0[6];
    local_1c[3] = s_tonecrys_004a03c0[7];
    local_18 = s_tonecrys_004a03c0[8];
    local_17 = 0;
    local_15 = 0;
    local_14[0] = s_magctone_004a03cc[0];
    local_14[1] = s_magctone_004a03cc[1];
    local_14[2] = s_magctone_004a03cc[2];
    local_14[3] = s_magctone_004a03cc[3];
    local_10[0] = s_magctone_004a03cc[4];
    local_10[1] = s_magctone_004a03cc[5];
    local_10[2] = s_magctone_004a03cc[6];
    local_10[3] = s_magctone_004a03cc[7];
    local_c = s_magctone_004a03cc[8];
    local_b = 0;
    local_9 = 0;
    for (local_34 = 0; local_34 < 3; local_34 = local_34 + 1) {
      iVar2 = thunk_FUN_0040ec89(local_2c + local_34 * 0xc,1);
      if (iVar2 == 0) {
        thunk_FUN_00414b64(s_C__float_src_iwhall_cpp_004a03e0,0x3b2,s_shape_004a03d8);
      }
      thunk_FUN_00404770(in_ECX + 8,iVar2,4,0x1e,local_34 * 0x18 + 0x34);
      local_48[2] = *(int *)(in_ECX + 0x10) + 0x25 + local_34 * 0x18;
      local_38 = local_48[2] + 0xe;
      iVar4 = *(int *)(in_ECX + 0x10) - local_48[2];
      iVar3 = *(int *)(in_ECX + 0xc) - local_48[1];
      iVar2 = (int)*(short *)(in_ECX + 0x1e);
      uVar1 = local_30;
      uVar7 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_004109a6(local_48,uVar7,iVar2,iVar3,iVar4,uVar1);
      for (local_60 = 0; local_60 < 3; local_60 = local_60 + 1) {
        iVar2 = (int)*(short *)(in_ECX + 0x74 + local_34 * 6 + local_60 * 2);
        if (iVar2 == 0) {
          FUN_00472da0(local_5c,&DAT_004a03fc);
        }
        else {
          FUN_00472ca0(local_5c,&DAT_004a03f8,iVar2);
        }
        iVar2 = thunk_FUN_0042892d(local_5c,0xffffffff,0xffffffff);
        thunk_FUN_004289c0(in_ECX + 8,local_60 * 0x26 + 0x28 + (0x1c - iVar2) / 2,
                           local_34 * 0x18 + 0x2c,local_5c);
      }
    }
    local_8 = 0;
    if (DAT_0062c6bc == *(short *)(in_ECX + 0x70)) {
      local_8 = thunk_FUN_00429ebe(s_TRZERO_004a0400,0);
    }
    else if (DAT_0062c6bc == *(short *)(in_ECX + 0x72)) {
      local_8 = thunk_FUN_00429ebe(s_TRDOIT_004a0408,0);
    }
    if (local_8 != 0) {
      thunk_FUN_004289c0(in_ECX + 8,0x9c,0x32,local_8);
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,3);
    thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x70),0xb,0,0);
    thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x72),0xb,0,0);
  }
  return;
}
```

---

## FUN_0043fa30 — 0x43fa30

- Classification : internal
- Corps : `0x43fa30–0x43fa5d`
- État : pseudocode obtenu
- Evidence : `ev_116b3f789881bcbb01dcdf6d5d1dc2eb5fed27dc34f06ab53a801d5ea73ba9d9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40244b` — `thunk_FUN_0043d254`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043fa30(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0043d254();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0043fa70 — 0x43fa70

- Classification : internal
- Corps : `0x43fa70–0x43fa9d`
- État : pseudocode obtenu
- Evidence : `ev_3cceedd4884b580af75ed8cb7cb0bb75745a1722df57f5c9907f34933273e1ae`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40138e` — `thunk_FUN_0043dc7d`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043fa70(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0043dc7d();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0043fab0 — 0x43fab0

- Classification : internal
- Corps : `0x43fab0–0x43fadd`
- État : pseudocode obtenu
- Evidence : `ev_af9bde8f644e4fbec3bee3943c8077f30277588f1018cf05708d870d3b1965ad`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401230` — `thunk_FUN_0043e26f`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043fab0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0043e26f();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0043faf0 — 0x43faf0

- Classification : internal
- Corps : `0x43faf0–0x43fb1d`
- État : pseudocode obtenu
- Evidence : `ev_ec8812ee8ae89da36abf51a8d225b28f071787928f3e13684731c39ff4f5390f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40137a` — `thunk_FUN_0043ea7c`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043faf0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0043ea7c();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0043fb30 — 0x43fb30

- Classification : internal
- Corps : `0x43fb30–0x43fb7f`
- État : pseudocode obtenu
- Evidence : `ev_b6cb1676cac1820fad168a182382157b38b2b8d51f0a2a4ea75646e80f070e25`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f14` — `thunk_FUN_00404770`
- `0x4020e0` — `thunk_FUN_0040ec89`

### Chaînes référencées

- `0x4a04d4` — "ACTICON"

### Pseudocode Ghidra

```c
void FUN_0043fb30(undefined4 param_1,undefined4 param_2,undefined4 param_3,short param_4)

{
  int iVar1;
  
  iVar1 = thunk_FUN_0040ec89(s_ACTICON_004a04d4,1);
  if (((iVar1 != 0) && (-1 < param_4)) && (param_4 < 0xe)) {
    thunk_FUN_00404770(param_1,iVar1,(int)param_4,param_2,param_3);
  }
  return;
}
```

---

## FUN_0043fb80 — 0x43fb80

- Classification : internal
- Corps : `0x43fb80–0x43fbd3`
- État : pseudocode obtenu
- Evidence : `ev_ad5c1f8877876f94472f101da7bf2ff8973161811800e76c4fd0ba9f654e1c7a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4019ab` — `thunk_FUN_0043fbf0`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0043fb80(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491819;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494440;
  thunk_FUN_0043fbf0();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_0043fbd4 — 0x43fbd4

- Classification : internal
- Corps : `0x43fbd4–0x43fbef`
- État : pseudocode obtenu
- Evidence : `ev_4a906a54efedd66d588a952155902fde54840f02ee6ce49d989f6482587c50ea`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043fbd4(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494440;
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_0043fbf0 — 0x43fbf0

- Classification : internal
- Corps : `0x43fbf0–0x43fc0d`
- État : pseudocode obtenu
- Evidence : `ev_8125634827316c044100df1a4d97f624e908e9936c95d422f75964ee41ac7741`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043fbf0(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x70) = 0xffffffff;
  *(undefined2 *)(in_ECX + 0x74) = 0;
  return;
}
```

---

## FUN_0043fc0e — 0x43fc0e

- Classification : internal
- Corps : `0x43fc0e–0x43fcec`
- État : pseudocode obtenu
- Evidence : `ev_d329e6290ce3e15bc75484e75d02d89b9fa2b5290f5c6d7240eb739e70f59192`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`
- `0x4023d3` — `thunk_FUN_0046b928`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043fc0e(short param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int in_ECX;
  
  if (param_1 < 0x350c) {
    if (param_1 == 0x350b) {
      *(undefined4 *)(in_ECX + 0x78) = param_2;
      *(undefined4 *)(in_ECX + 0x34) = 1;
      return 1;
    }
    if (param_1 == 1) {
      *(undefined2 *)(in_ECX + 0x76) = 0xffff;
      thunk_FUN_0046b928(*(undefined4 *)(in_ECX + 4),0x350c,0,0,0);
    }
    else if (param_1 == 2) {
      DAT_0049e9c8 = 0xfffe;
    }
  }
  else if (param_1 == 0x350c) {
    if ((DAT_0062c6bc != *(short *)(in_ECX + 0x76)) && (*(int *)(in_ECX + 0x3c) != 0)) {
      *(undefined2 *)(in_ECX + 0x76) = (undefined2)DAT_0062c6bc;
      *(undefined4 *)(in_ECX + 0x34) = 1;
    }
    return 1;
  }
  uVar1 = thunk_FUN_004293c6(param_1,param_2,param_3);
  return uVar1;
}
```

---

## FUN_0043fced — 0x43fced

- Classification : internal
- Corps : `0x43fced–0x43ffc1`
- État : pseudocode obtenu
- Evidence : `ev_d4a8523612cbf3c89e1811ec062b9abc58733c8871442ca22403ffa2c55121d9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x401636` — `thunk_FUN_0045d9c1`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x40224d` — `thunk_FUN_00450070`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- `0x4a04dc` — "magctone"
- `0x4a04e8` — "shape"
- `0x4a04f0` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0508` — "tonecrys"
- `0x4a0514` — "shape"
- `0x4a051c` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
void FUN_0043fced(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int in_ECX;
  int iVar4;
  undefined2 extraout_var;
  undefined4 uVar5;
  undefined4 uVar6;
  int local_18;
  undefined2 local_14;
  int local_c;
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
    local_8 = -1;
    if (*(int *)(in_ECX + 0x70) != -1) {
      for (local_c = 0; local_c < *(short *)(in_ECX + 0x74); local_c = local_c + 1) {
        thunk_FUN_0046c371(*(int *)(in_ECX + 0x70) + local_c,0xb,0,0);
        if (*(int *)(in_ECX + 0x70) + local_c == DAT_0062c6bc) {
          local_8 = local_c;
        }
      }
    }
    if ((((local_8 != -1) &&
         (iVar4 = *(int *)(&DAT_0062a784 + DAT_0062c6bc * 0xc),
         0x2e < *(int *)(*(int *)(in_ECX + 0x78) + 0x10))) &&
        (*(int *)(*(int *)(in_ECX + 0x78) + 0x10) < 0x31)) &&
       ((0x14 < *(int *)(iVar4 + 100) && (*(int *)(iVar4 + 100) < 0x1d)))) {
      iVar4 = thunk_FUN_00450070(*(undefined4 *)(in_ECX + 0x78),*(undefined4 *)(iVar4 + 100));
      iVar2 = thunk_FUN_0040ec89(s_magctone_004a04dc,1);
      if (iVar2 == 0) {
        thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a04f0,0xb0,s_shape_004a04e8);
      }
      iVar3 = thunk_FUN_00450385();
      if (iVar3 == 0) {
        local_18 = (int)*(short *)(&DAT_006188e2 + iVar4 * 0x2c);
      }
      else {
        local_14 = (undefined2)iVar4;
        local_18 = thunk_FUN_0045d9c1(CONCAT22(extraout_var,local_14));
      }
      local_18 = local_18 + -1;
      if (local_18 < 0) {
        local_18 = 0;
      }
      if (0x31 < local_18) {
        local_18 = 0x31;
      }
      iVar3 = *(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc);
      thunk_FUN_00404770(in_ECX + 8,iVar2,local_18,((int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2) + -5,
                         0x1a);
      iVar2 = thunk_FUN_0040ec89(s_tonecrys_004a0508,1);
      if (iVar2 == 0) {
        uVar1 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a051c,0xbf,s_shape_004a0514);
      }
      else {
        uVar1 = 0;
      }
      local_18 = *(short *)(&DAT_006188e4 + iVar4 * 0x2c) + -1;
      if (local_18 < 0) {
        local_18 = 0;
      }
      if (0x31 < local_18) {
        local_18 = 0x31;
      }
      iVar4 = *(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc);
      thunk_FUN_00404770(in_ECX + 8,iVar2,local_18,((int)(iVar4 + (iVar4 >> 0x1f & 3U)) >> 2) + -5,
                         0x37,uVar1);
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,3);
    *(undefined4 *)(in_ECX + 0x34) = 0;
  }
  return;
}
```

---

## FUN_0043ffc2 — 0x43ffc2

- Classification : internal
- Corps : `0x43ffc2–0x440015`
- État : pseudocode obtenu
- Evidence : `ev_83d18a84dbed485487456ee880bac7982a004e87d4e06cfef12421ab57f1f33e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401492` — `thunk_FUN_00440032`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0043ffc2(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049182c;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494458;
  thunk_FUN_00440032();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_00440016 — 0x440016

- Classification : internal
- Corps : `0x440016–0x440031`
- État : pseudocode obtenu
- Evidence : `ev_c4d77d59d28c41174ded6080eda34637e30decd6ef2915c062a112b773f81f3f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00440016(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494458;
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_00440032 — 0x440032

- Classification : internal
- Corps : `0x440032–0x44003c`
- État : pseudocode obtenu
- Evidence : `ev_792fd1e46663ebafd0e5d29824971abeaec0da90ef49abbf59605a181e457616`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00440032(void)

{
  return;
}
```

---

## FUN_0044003d — 0x44003d

- Classification : internal
- Corps : `0x44003d–0x440325`
- État : pseudocode obtenu
- Evidence : `ev_9f854760de65b70cdb336d193609191bbf2d8bbde63868ca8f8757721ebda9ca`
- Note de flux : le clic sans slot envoie `0x32` si `+0x18 != -1`; une route vers `FUN_0042fa0f` n'est démontrée que sous les gardes dispatcher mode 0 et callback actif slot 3. Ces états ne sont pas reliés au clic. Evidence `ev_dfa9260d630c5590f535d54281a0b8f2c2767e3ca99d4a00ffdd596b3104b7eb`.
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401bf4` — `thunk_FUN_0042970c`
- `0x402504` — `thunk_FUN_00440451`
- `0x472c6c` — `__ftol`

### Chaînes référencées

- `0x4a0534` — "IWMove"
- `0x4a053c` — "IWHallMove"
- `0x4a0548` — "IWMove"
- `0x4a0550` — "IWHallMove"
- `0x4a055c` — "IWHallMove"
- `0x4a0568` — "IWMove"

### Pseudocode Ghidra

```c
undefined4 FUN_0044003d(short param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined2 extraout_var;
  undefined4 uVar2;
  int in_ECX;
  undefined4 uVar3;
  undefined *local_10;
  
  iVar1 = (int)param_1;
  if (iVar1 < 0x350c) {
    if (iVar1 == 0x350b) {
      thunk_FUN_0046c3bc(s_IWMove_004a0548,2,0,0);
      thunk_FUN_0046c3bc(s_IWHallMove_004a0550,2,0,0);
      *(undefined4 *)(in_ECX + 0x70) = param_2;
      local_10 = *(undefined **)(in_ECX + 0x70);
      if (*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) != 0) {
        local_10 = &DAT_005ec640 +
                   *(short *)(DAT_0049f538 * 0x14a0 + 0x61a574) * 0x60 +
                   *(short *)(DAT_0049f538 * 0x14a0 + 0x61a572) * 0x29e8;
      }
      if ((((local_10 != (undefined *)0x0) && (*(int *)(local_10 + 0x14) == DAT_0049f538)) &&
          (*(int *)(local_10 + 0x10) != 0)) && (*(int *)(local_10 + 0x10) != 1)) {
        if (*(int *)(local_10 + 0x10) == 0x2a) {
          thunk_FUN_0046c3bc(s_IWHallMove_004a055c,1,0,0);
        }
        else if (*(int *)(local_10 + 0x10) != 0x28) {
          thunk_FUN_0046c3bc(s_IWMove_004a0568,1,0,0);
        }
      }
      *(undefined2 *)(in_ECX + 0x76) = 0xffff;
      return 1;
    }
    switch(iVar1) {
    case 1:
      *(undefined2 *)(in_ECX + 0x74) = 0xffff;
      break;
    case 2:
      thunk_FUN_0046c3bc(s_IWMove_004a0534,2,0,0);
      thunk_FUN_0046c3bc(s_IWHallMove_004a053c,2,0,0);
      uVar2 = thunk_FUN_004293c6(CONCAT22(extraout_var,param_1),param_2,param_3);
      return uVar2;
    case 6:
      iVar1 = thunk_FUN_00429f3a();
      if ((iVar1 != 0) && (*(int *)(in_ECX + 0x70) != 0)) {
        thunk_FUN_00440451(param_2,param_3);
        if (*(short *)(in_ECX + 0x76) == -1) {
          if (*(short *)(*(int *)(in_ECX + 0x70) + 0x18) != -1) {
            *(undefined4 *)(DAT_005dc64c + 0x170) = 0;
            thunk_FUN_0042970c(0x32,0,0);
          }
        }
        else {
          thunk_FUN_0042970c(0x3f,(int)*(short *)(in_ECX + 0x78 + *(short *)(in_ECX + 0x76) * 2),0);
        }
      }
      break;
    case 7:
      iVar1 = thunk_FUN_00429f3a();
      if ((iVar1 != 0) && (*(int *)(in_ECX + 0x70) != 0)) {
        if (*(short *)(*(int *)(in_ECX + 0x70) + 8) != DAT_0049f53c) {
          thunk_FUN_0042970c(0x4d,(int)*(short *)(*(int *)(in_ECX + 0x70) + 8),0);
        }
        uVar3 = 1;
        uVar2 = __ftol(1);
        thunk_FUN_0042970c(0x3d,uVar2,uVar3);
      }
      break;
    case 10:
      thunk_FUN_00440451(param_2,param_3);
    }
  }
  else if (iVar1 == 0x350d) {
    *(undefined2 *)(in_ECX + 0x74) = (undefined2)param_2;
    return 1;
  }
  uVar2 = thunk_FUN_004293c6(param_1,param_2,param_3);
  return uVar2;
}
```

---

## FUN_0044034e — 0x44034e

- Classification : internal
- Corps : `0x44034e–0x440450`
- État : pseudocode obtenu
- Evidence : `ev_9ef02eb58bdf8a0866dbfbc4fddb24eb95a3c0322ffbf1e75b23988cc0c84e8d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4019a1` — `thunk_FUN_00450385`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x40208b` — `thunk_FUN_0045d7e8`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a0570` — "slot<6"
- `0x4a0578` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
void FUN_0044034e(void)

{
  int iVar1;
  int in_ECX;
  int local_14;
  int local_c;
  int local_8;
  
  _memset((void *)(in_ECX + 0x78),-1,0xc);
  if (((*(int *)(in_ECX + 0x70) != 0) && (*(int *)(*(int *)(in_ECX + 0x70) + 4) == 0)) &&
     (iVar1 = thunk_FUN_00450385(), iVar1 != 0)) {
    for (local_8 = 0; local_8 < 3; local_8 = local_8 + 1) {
      local_14 = 0;
      if (local_8 == 1) {
        local_14 = 3;
      }
      else if (local_8 == 2) {
        local_14 = 5;
      }
      local_c = -1;
      while (local_c = thunk_FUN_0045d7e8(local_c,local_8), local_c != -1) {
        if (5 < local_14) {
          thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0578,0x162,s_slot<6_004a0570);
        }
        *(undefined2 *)(in_ECX + 0x78 + local_14 * 2) = *(undefined2 *)(iVar1 + 4 + local_c * 2);
        local_14 = local_14 + 1;
      }
    }
  }
  return;
}
```

---

## FUN_00440451 — 0x440451

- Classification : internal
- Corps : `0x440451–0x440566`
- État : pseudocode obtenu
- Evidence : `ev_9e5f61cf79edd2a0425ee2f8b0f8c237a37b466f2219e936bdc3427204f308c2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00440451(int param_1,int param_2)

{
  int in_ECX;
  undefined *local_2c;
  undefined *local_28;
  int local_20;
  int local_18;
  int local_10;
  
  if ((*(int *)(in_ECX + 0x70) != 0) && (*(short *)(*(int *)(in_ECX + 0x70) + 0x18) != -1)) {
    *(undefined2 *)(in_ECX + 0x76) = 0xffff;
    if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2f) {
      local_28 = &DAT_004a04b8;
    }
    else {
      local_28 = &DAT_004a0498;
    }
    if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 0x2f) {
      local_2c = &DAT_004a04c8;
    }
    else {
      local_2c = &DAT_004a04a8;
    }
    for (local_10 = 0; local_10 < 6; local_10 = local_10 + 1) {
      if (*(short *)(in_ECX + 0x78 + local_10 * 2) != -1) {
        local_18 = (param_1 - *(int *)(in_ECX + 0xc)) - (int)*(short *)(local_28 + local_10 * 2);
        if (local_18 < 0) {
          local_18 = -local_18;
        }
        local_20 = (param_2 - *(int *)(in_ECX + 0x10)) - (int)*(short *)(local_2c + local_10 * 2);
        if (local_20 < 0) {
          local_20 = -local_20;
        }
        if ((local_18 < 0xf) && (local_20 < 0xf)) {
          *(undefined2 *)(in_ECX + 0x76) = (undefined2)local_10;
          return;
        }
      }
    }
  }
  return;
}
```

---


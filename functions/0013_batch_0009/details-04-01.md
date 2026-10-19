# 0013_batch_0009 — détails (1/3)

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

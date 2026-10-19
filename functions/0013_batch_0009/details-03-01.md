# 0013_batch_0009 — détails (1/3)

## FUN_0043d45c — 0x43d45c

- Classification : internal
- Corps : `0x43d45c–0x43d59a`
- État : pseudocode obtenu
- Evidence : `ev_9fc07a22727b951aa803d665ceb9d49be1f2cf511265359011b5b1a9c21be232`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018e3` — `thunk_FUN_0046c3bc`

### Chaînes référencées

- `0x4a0190` — "IWTextInfo"

### Pseudocode Ghidra

```c
undefined4 FUN_0043d45c(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  int in_ECX;
  int iVar3;
  
  sVar1 = *(short *)(in_ECX + 0x70);
  *(undefined2 *)(in_ECX + 0x70) = 0xffff;
  if ((((*(int *)(in_ECX + 0xc) <= param_1) && (param_1 <= *(int *)(in_ECX + 0x14))) &&
      (*(int *)(in_ECX + 0x10) + 0x18 <= param_2)) && (param_2 <= *(int *)(in_ECX + 0x18))) {
    iVar2 = (param_1 - *(int *)(in_ECX + 0xc)) /
            ((*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 5) +
            ((param_2 - (*(int *)(in_ECX + 0x10) + 0x18)) /
            (((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + -0x18) / 2)) * 5;
    iVar3 = *(short *)(in_ECX + 0xec) * 10;
    if (iVar3 + iVar2 < (int)*(short *)(in_ECX + 0xee)) {
      *(undefined2 *)(in_ECX + 0x70) = *(undefined2 *)(in_ECX + 0xf0 + (iVar3 + iVar2) * 2);
    }
  }
  if (*(short *)(in_ECX + 0x70) != sVar1) {
    *(undefined4 *)(in_ECX + 0x34) = 1;
    thunk_FUN_0046c3bc(s_IWTextInfo_004a0190,0x3039,2,(int)*(short *)(in_ECX + 0x70));
  }
  return 1;
}
```

---

---

## FUN_0043d59b — 0x43d59b

- Classification : internal
- Corps : `0x43d59b–0x43d6a2`
- État : pseudocode obtenu
- Evidence : `ev_44c84c02349f96e801edd8d158e98219890eac2e7f94382728cb39bb6a58e816`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018e3` — `thunk_FUN_0046c3bc`

### Chaînes référencées

- `0x4a019c` — "InvCycle"
- `0x4a01a8` — "InvCycle"

### Pseudocode Ghidra

```c
void FUN_0043d59b(void)

{
  short sVar1;
  int in_ECX;
  int local_c;
  int local_8;
  
  local_8 = 0;
  for (local_c = 0; local_c < 0x1d; local_c = local_c + 1) {
    sVar1 = (short)local_c + 5;
    if (0 < *(short *)(&DAT_006191fc + sVar1 * 2 + DAT_0049f538 * 0x14a0)) {
      *(short *)(in_ECX + 0xf0 + local_8 * 2) = sVar1;
      local_8 = local_8 + 1;
    }
  }
  if (local_8 != *(short *)(in_ECX + 0xee)) {
    if (local_8 < 0xb) {
      if (10 < *(short *)(in_ECX + 0xee)) {
        thunk_FUN_0046c3bc(s_InvCycle_004a01a8,2,0,0);
      }
    }
    else if (*(short *)(in_ECX + 0xee) < 0xb) {
      thunk_FUN_0046c3bc(s_InvCycle_004a019c,1,0,0);
    }
    *(undefined2 *)(in_ECX + 0xee) = (undefined2)local_8;
    *(undefined4 *)(in_ECX + 0x34) = 1;
  }
  if (DAT_0049e9c4 != -1) {
    *(undefined4 *)(in_ECX + 0x34) = 1;
  }
  return;
}
```

---

---

## FUN_0043d6a3 — 0x43d6a3

- Classification : internal
- Corps : `0x43d6a3–0x43dc28`
- État : pseudocode obtenu
- Evidence : `ev_b6f830a22cb40d4fddda3ad559c0a6aaecf6caae982f1a6027434aa2a0f0d62e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401442` — `thunk_FUN_0041169f`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x402234` — `thunk_FUN_0042892d`
- `0x40229d` — `thunk_FUN_00405e11`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x4a01b4` — "TRIGGERS"
- `0x4a01c0` — "shape"
- `0x4a01c8` — "C:\\float\\src\\iwhall.cpp"
- `0x4a01e0` — "TRIGGERS"
- `0x4a01ec` — "shape"
- `0x4a01f4` — "C:\\float\\src\\iwhall.cpp"
- `0x4a0214` — "InvCycle"
- `0x4a0224` — "C:\\float\\src\\iwhall.cpp"
- `0x4a023c` — "NOART"

### Pseudocode Ghidra

```c
void FUN_0043d6a3(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int in_ECX;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined1 local_74 [8];
  undefined4 local_6c;
  int local_68;
  int local_64;
  uint local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    uVar2 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar2;
    if (DAT_004c2bac == 0) {
      thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
    }
    else {
      uVar7 = 0;
      uVar6 = 0;
      iVar5 = (int)*(short *)(in_ECX + 0x1e);
      uVar2 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar2,iVar5,uVar6,uVar7);
    }
    if (*(int *)(in_ECX + 0x74) == 0) {
      local_28 = thunk_FUN_0040ec89(s_TRIGGERS_004a01b4,1);
      if (local_28 == 0) {
        thunk_FUN_00414b64(s_C__float_src_iwhall_cpp_004a01c8,0x106,s_shape_004a01c0);
      }
      for (local_24 = 0; (local_24 < 0x1d && (local_4c = local_24 + 5, local_4c < 0x22));
          local_24 = local_24 + 1) {
        thunk_FUN_00405e11(local_28,local_24,0,0,0,&local_38);
        local_40 = (local_30 - local_38) + 1;
        local_44 = (local_2c - local_34) + 1;
        local_3c = (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 5 - local_40;
        if (local_3c != 0) {
          local_3c = local_3c / 2;
        }
        local_48 = ((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + -0x18) / 2 - local_44;
        if (local_48 != 0) {
          local_48 = local_48 / 2;
        }
        *(short *)(in_ECX + 0x78 + local_24 * 2) = (short)local_3c - (short)local_38;
        *(short *)(in_ECX + 0xb2 + local_24 * 2) = (short)local_48 - (short)local_34;
      }
      *(undefined4 *)(in_ECX + 0x74) = 1;
    }
    local_20 = thunk_FUN_0040ec89(s_TRIGGERS_004a01e0,1);
    if (local_20 == 0) {
      thunk_FUN_00414b64(s_C__float_src_iwhall_cpp_004a01f4,0x122,s_shape_004a01ec);
    }
    local_c = 0;
    local_1c = *(short *)(in_ECX + 0xec) * 10;
    local_8 = local_1c + 10;
    local_14 = local_1c;
    if (*(short *)(in_ECX + 0xee) < local_8) {
      local_8 = (int)*(short *)(in_ECX + 0xee);
    }
    for (; local_14 < local_8; local_14 = local_14 + 1) {
      local_5c = (int)*(short *)(in_ECX + 0xf0 + local_14 * 2);
      local_58 = local_c / 5;
      local_54 = local_c % 5;
      if (1 < local_58) break;
      local_50 = local_5c + -5;
      if (local_50 < 0) {
        local_50 = 0;
      }
      if (0x1c < local_50) {
        local_50 = 0x1c;
      }
      local_10 = ((*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 5) * local_54 +
                 (int)*(short *)(in_ECX + 0x78 + local_50 * 2);
      local_18 = (((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + -0x18) / 2) * local_58 +
                 0x18 + (int)*(short *)(in_ECX + 0xb2 + local_50 * 2);
      if ((local_5c == *(short *)(in_ECX + 0x70)) || (local_5c == DAT_0049e9c4)) {
        local_64 = ((*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 5) * local_54 + 1;
        local_68 = (((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + -0x18) / 2) * local_58 +
                   0x19;
        local_60 = thunk_FUN_0042dd0f(1);
        local_60 = local_60 & 0xff;
        if (local_5c == DAT_0049e9c4) {
          local_60 = thunk_FUN_0042dd0f(4);
          local_60 = local_60 & 0xff;
        }
        thunk_FUN_0041169f(in_ECX + 8,local_64,local_68,
                           local_64 + -2 + (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 5,
                           local_68 + -2 +
                           ((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + -0x18) / 2,
                           local_60,0,0xffffffff);
      }
      thunk_FUN_00404770(in_ECX + 8,local_20,local_50,local_10,local_18);
      if (1 < *(short *)(&DAT_006191fc + local_5c * 2 + DAT_0049f538 * 0x14a0)) {
        FUN_00472ca0(local_74,&DAT_004a020c,
                     (int)*(short *)(&DAT_006191fc + local_5c * 2 + DAT_0049f538 * 0x14a0));
        local_6c = thunk_FUN_0042de0d();
        thunk_FUN_004289c0(in_ECX + 8,local_10 + 7,local_18 + -0x15,local_74);
      }
      local_c = local_c + 1;
    }
    thunk_FUN_0046c3bc(s_InvCycle_004a0214,0xb,0,0);
    if (*(short *)(in_ECX + 0xee) == 0) {
      iVar5 = thunk_FUN_0042de03();
      if (iVar5 == 0) {
        thunk_FUN_00414b64(s_C__float_src_iwhall_cpp_004a0224,0x16d,&DAT_004a0220);
      }
      uVar3 = thunk_FUN_0042dd0f(6);
      *(uint *)(iVar5 + 8) = uVar3 & 0xff;
      uVar2 = thunk_FUN_00429ebe(s_NOART_004a023c,0);
      iVar5 = *(int *)(in_ECX + 0x14);
      iVar1 = *(int *)(in_ECX + 0xc);
      iVar4 = thunk_FUN_0042892d(uVar2,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,((iVar5 - iVar1) - iVar4) / 2,
                         (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) / 2 + -6,uVar2);
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,3);
    *(undefined4 *)(in_ECX + 0x34) = 0;
  }
  return;
}
```

---

---

## FUN_0043dc29 — 0x43dc29

- Classification : internal
- Corps : `0x43dc29–0x43dc7c`
- État : pseudocode obtenu
- Evidence : `ev_1b835b9337286e93e596abd889f6f491f847e9e371b172c9209220dbc3c0e6d8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401500` — `thunk_FUN_0043dc99`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0043dc29(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004917cc;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004943f8;
  thunk_FUN_0043dc99();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0043dc7d — 0x43dc7d

- Classification : internal
- Corps : `0x43dc7d–0x43dc98`
- État : pseudocode obtenu
- Evidence : `ev_e1d05a888dcbdc726bd074da334c706c9a512ca4e3617025729eda7511a956ce`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043dc7d(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004943f8;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_0043dc99 — 0x43dc99

- Classification : internal
- Corps : `0x43dc99–0x43dcad`
- État : pseudocode obtenu
- Evidence : `ev_d24343bf8d3cfdb96711174b646c9038702a36772dae4957649161614458a1ee`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043dc99(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x74) = 0;
  return;
}
```

---

---

## FUN_0043dcae — 0x43dcae

- Classification : internal
- Corps : `0x43dcae–0x43dd9c`
- État : pseudocode obtenu
- Evidence : `ev_8ca64092de3b786050ffad150abf2dd04b82ef777d65f1cab09f8f07936c5419`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401a0a` — `thunk_FUN_0043ddcf`
- `0x401d93` — `thunk_FUN_0043dd9d`

### Chaînes référencées

- `0x4a0244` — "IWTextInfo"

### Pseudocode Ghidra

```c
void FUN_0043dcae(short param_1,int param_2,int param_3)

{
  int in_ECX;
  
  if (param_1 == 1) {
    *(undefined2 *)(in_ECX + 0x70) = 0xffff;
    thunk_FUN_0046c3bc(s_IWTextInfo_004a0244,0x3039,7,0);
  }
  else if (param_1 == 6) {
    if ((((*(int *)(in_ECX + 0xc) <= param_2) && (param_2 <= *(int *)(in_ECX + 0x14))) &&
        (*(int *)(in_ECX + 0x10) <= param_3)) &&
       ((param_3 <= *(int *)(in_ECX + 0x18) && (*(int *)(in_ECX + 0x38) != 0)))) {
      thunk_FUN_0043dd9d(param_2,param_3);
      return;
    }
  }
  else if (((param_1 == 10) && (*(int *)(in_ECX + 0xc) <= param_2)) &&
          ((param_2 <= *(int *)(in_ECX + 0x14) &&
           ((*(int *)(in_ECX + 0x10) <= param_3 && (param_3 <= *(int *)(in_ECX + 0x18))))))) {
    thunk_FUN_0043ddcf(param_2,param_3);
    return;
  }
  thunk_FUN_004293c6(param_1,param_2,param_3);
  return;
}
```

---

---

## FUN_0043dd9d — 0x43dd9d

- Classification : internal
- Corps : `0x43dd9d–0x43ddce`
- État : pseudocode obtenu
- Evidence : `ev_9ade0d4a821e96275d4606dbe0f0f834320b5d03d449ed2acff6dd12d44ca35e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401bf4` — `thunk_FUN_0042970c`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043dd9d(void)

{
  int in_ECX;
  
  if (*(short *)(in_ECX + 0x70) != -1) {
    thunk_FUN_0042970c(0x43,(int)*(short *)(in_ECX + 0x70),0);
  }
  return 1;
}
```

---

---

## FUN_0043ddcf — 0x43ddcf

- Classification : internal
- Corps : `0x43ddcf–0x43dee2`
- État : pseudocode obtenu
- Evidence : `ev_fea974fb0609629046e6c9a5a873d881f3d39e7301256f729b2272ac1267feb7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018e3` — `thunk_FUN_0046c3bc`

### Chaînes référencées

- `0x4a0250` — "IWTextInfo"

### Pseudocode Ghidra

```c
undefined4 FUN_0043ddcf(int param_1,int param_2)

{
  short sVar1;
  int in_ECX;
  int iVar2;
  int iVar3;
  int local_10;
  
  sVar1 = *(short *)(in_ECX + 0x70);
  *(undefined2 *)(in_ECX + 0x70) = 0xffff;
  local_10 = 0;
  do {
    if (0xd < local_10) {
LAB_0043dea1:
      if (sVar1 != *(short *)(in_ECX + 0x70)) {
        *(undefined4 *)(in_ECX + 0x34) = 1;
        thunk_FUN_0046c3bc(s_IWTextInfo_004a0250,0x3039,1,(int)*(short *)(in_ECX + 0x70));
      }
      return 1;
    }
    if (((int)*(short *)(&DAT_00619242 + DAT_0049f538 * 0x14a0) & 1 << ((byte)local_10 & 0x1f)) != 0
       ) {
      iVar2 = (param_1 - *(int *)(in_ECX + 0xc)) - (int)*(short *)(in_ECX + 0x78 + local_10 * 2);
      iVar3 = (param_2 - *(int *)(in_ECX + 0x10)) - (int)*(short *)(in_ECX + 0x94 + local_10 * 2);
      if ((((-0x10 < iVar2) && (iVar2 < 0x10)) && (-0x10 < iVar3)) && (iVar3 < 0xf)) {
        *(undefined2 *)(in_ECX + 0x70) = (undefined2)local_10;
        goto LAB_0043dea1;
      }
    }
    local_10 = local_10 + 1;
  } while( true );
}
```

---

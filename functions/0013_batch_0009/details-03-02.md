# 0013_batch_0009 — détails (2/3)

## FUN_0043dee3 — 0x43dee3

- Classification : internal
- Corps : `0x43dee3–0x43e21a`
- État : pseudocode obtenu
- Evidence : `ev_0a4e7c27eddcdffbfcf633f2dc2732e619dd7a529952f01462d8b76f7953d16f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x402234` — `thunk_FUN_0042892d`
- `0x40229d` — `thunk_FUN_00405e11`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`

### Chaînes référencées

- `0x4a025c` — "GLINV"
- `0x4a0264` — "shape"
- `0x4a026c` — "C:\\float\\src\\iwhall.cpp"
- `0x4a0284` — "TEMPHOLE"
- `0x4a0290` — "shape"
- `0x4a0298` — "C:\\float\\src\\iwhall.cpp"
- `0x4a02b4` — "C:\\float\\src\\iwhall.cpp"
- `0x4a02cc` — "NOKNOW"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0043dee3(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int in_ECX;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  short local_10;
  int local_c;
  int local_8;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    uVar2 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar2;
    local_14 = thunk_FUN_0040ec89(s_GLINV_004a025c,1);
    if (local_14 == 0) {
      thunk_FUN_00414b64(s_C__float_src_iwhall_cpp_004a026c,0x1e7,s_shape_004a0264);
    }
    if (*(int *)(in_ECX + 0x74) == 0) {
      for (local_18 = 0; local_18 < 0xe; local_18 = local_18 + 1) {
        thunk_FUN_00405e11(local_14,local_18 + 1,*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc),
                           *(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10),0,&local_28);
        *(short *)(in_ECX + 0x78 + local_18 * 2) =
             (short)local_28 + (short)(((local_20 - local_28) + 1) / 2);
        *(short *)(in_ECX + 0x94 + local_18 * 2) =
             (short)local_24 + (short)(((local_1c - local_24) + 1) / 2);
      }
      *(undefined4 *)(in_ECX + 0x74) = 1;
    }
    local_10 = *(short *)(&DAT_00619242 + DAT_0049f538 * 0x14a0);
    if (local_10 != 0) {
      thunk_FUN_00404770(in_ECX + 8,local_14,0,*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc),
                         *(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10));
    }
    for (local_8 = 0; local_8 < 0xe; local_8 = local_8 + 1) {
      if (((int)local_10 & 1 << ((byte)local_8 & 0x1f)) != 0) {
        local_c = local_8 + 1;
        _DAT_004c2f38 = thunk_FUN_0042dd0f(2);
        _DAT_004c2f38 = _DAT_004c2f38 & 0xff;
        if (local_8 == *(short *)(in_ECX + 0x70)) {
          local_c = local_c + 0xe;
        }
        thunk_FUN_00404770(in_ECX + 8,local_14,local_c,
                           *(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc),
                           *(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10));
      }
    }
    if (local_10 == 0) {
      local_14 = thunk_FUN_0040ec89(s_TEMPHOLE_004a0284,1);
      if (local_14 == 0) {
        thunk_FUN_00414b64(s_C__float_src_iwhall_cpp_004a0298,0x211,s_shape_004a0290);
      }
      thunk_FUN_00404770(in_ECX + 8,local_14,1,0,0);
      iVar3 = thunk_FUN_0042de03();
      if (iVar3 == 0) {
        thunk_FUN_00414b64(s_C__float_src_iwhall_cpp_004a02b4,0x214,&DAT_004a02b0);
      }
      uVar4 = thunk_FUN_0042dd0f(6);
      *(uint *)(iVar3 + 8) = uVar4 & 0xff;
      uVar2 = thunk_FUN_00429ebe(s_NOKNOW_004a02cc,0);
      iVar3 = *(int *)(in_ECX + 0x14);
      iVar1 = *(int *)(in_ECX + 0xc);
      iVar5 = thunk_FUN_0042892d(uVar2,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,((iVar3 - iVar1) - iVar5) / 2,
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

## FUN_0043e21b — 0x43e21b

- Classification : internal
- Corps : `0x43e21b–0x43e26e`
- État : pseudocode obtenu
- Evidence : `ev_23e7c6b324936f8e655c8bf4c95fe9cf93e3b2a8ebd6b1ae767e72784162123d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`
- `0x402126` — `thunk_FUN_0043e28b`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0043e21b(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004917df;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494410;
  thunk_FUN_0043e28b();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0043e26f — 0x43e26f

- Classification : internal
- Corps : `0x43e26f–0x43e28a`
- État : pseudocode obtenu
- Evidence : `ev_94291e279ab96aeb193f5af7f7d1c0a3e844d446e62691ad07ca6c595a275297`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043e26f(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494410;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_0043e28b — 0x43e28b

- Classification : internal
- Corps : `0x43e28b–0x43e295`
- État : pseudocode obtenu
- Evidence : `ev_d03d06264f536030a1288eae877083b8631207340689fadfccb981dfa19084d3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043e28b(void)

{
  return;
}
```

---

---

## FUN_0043e296 — 0x43e296

- Classification : internal
- Corps : `0x43e296–0x43e37a`
- État : pseudocode obtenu
- Evidence : `ev_ef8b6c65bd1c92a38f8252f3cdb0e41caa962af5bf35f9469e99625d7a226e9d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401087` — `thunk_FUN_0043e4f0`
- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x402333` — `thunk_FUN_0043e399`

### Chaînes référencées

- `0x4a02d4` — "IWTextInfo"

### Pseudocode Ghidra

```c
undefined4 FUN_0043e296(short param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  
  switch(param_1) {
  case 1:
    *(undefined2 *)(in_ECX + 0x70) = 0;
    *(undefined2 *)(in_ECX + 0x72) = 0xffff;
    *(undefined2 *)(in_ECX + 0x74) = 0xffff;
    thunk_FUN_0046c3bc(s_IWTextInfo_004a02d4,0x3039,8,0);
    break;
  case 6:
  case 7:
    iVar1 = thunk_FUN_00429f3a();
    if (iVar1 != 0) {
      thunk_FUN_0043e4f0(param_2 - *(int *)(in_ECX + 0xc),param_3 - *(int *)(in_ECX + 0x10),
                         param_1 == 6);
      return 1;
    }
    break;
  case 8:
    thunk_FUN_0043e399(0xffffffff,0xffffffff);
    return 0;
  case 10:
    thunk_FUN_0043e399(param_2,param_3);
    return 0;
  }
  uVar2 = thunk_FUN_004293c6(param_1,param_2,param_3);
  return uVar2;
}
```

---

---

## FUN_0043e399 — 0x43e399

- Classification : internal
- Corps : `0x43e399–0x43e4ef`
- État : pseudocode obtenu
- Evidence : `ev_83310289d91202d60603bd9f80ef78479a48b64c570e61ce5afd111af27eccb0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401bd1` — `thunk_FUN_00429209`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043e399(int param_1,int param_2)

{
  int iVar1;
  int in_ECX;
  undefined2 local_1c;
  undefined1 local_18 [4];
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  *(undefined2 *)(in_ECX + 0x72) = 0xffff;
  *(undefined2 *)(in_ECX + 0x74) = 0xffff;
  if (param_2 < 0x1b1) {
    local_14 = 0x10a;
    local_10 = 399;
    local_c = 0x127;
    local_8 = 0x1ac;
    iVar1 = thunk_FUN_00429209(param_1,param_2,local_18);
    if (iVar1 == 0) {
      local_14 = 0x139;
      local_10 = 399;
      local_c = 0x149;
      local_8 = 0x1b1;
      iVar1 = thunk_FUN_00429209(param_1,param_2,local_18);
      if (iVar1 == 0) {
        local_14 = 0x15b;
        local_10 = 399;
        local_c = 0x178;
        local_8 = 0x1ac;
        iVar1 = thunk_FUN_00429209(param_1,param_2,local_18);
        if (iVar1 != 0) {
          *(undefined2 *)(in_ECX + 0x72) = 2;
        }
      }
      else {
        *(undefined2 *)(in_ECX + 0x72) = 1;
      }
    }
    else {
      *(undefined2 *)(in_ECX + 0x72) = 0;
    }
  }
  else {
    param_1 = param_1 - *(int *)(in_ECX + 0xc);
    local_1c = 0;
    if (((*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) * 2) / 3 < param_1) {
      local_1c = 2;
    }
    else if ((*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 3 < param_1) {
      local_1c = 1;
    }
    *(undefined2 *)(in_ECX + 0x74) = local_1c;
  }
  return;
}
```

---

---

## FUN_0043e4f0 — 0x43e4f0

- Classification : internal
- Corps : `0x43e4f0–0x43e5a9`
- État : pseudocode obtenu
- Evidence : `ev_b31952fff609b555e9e8c59eecea0d388c46aab20464cc9ff7bd87c3ea7e0b5f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40228e` — `thunk_FUN_00414081`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043e4f0(void)

{
  int in_ECX;
  undefined2 local_1c;
  undefined2 local_1a;
  undefined2 local_18;
  undefined2 local_10;
  undefined2 local_e;
  undefined4 local_c;
  int local_8;
  
  local_8 = -1;
  if (*(short *)(in_ECX + 0x72) == -1) {
    if (*(short *)(in_ECX + 0x74) != -1) {
      local_8 = (int)*(short *)(in_ECX + 0x74);
      local_c = 0;
    }
  }
  else {
    local_8 = (int)*(short *)(in_ECX + 0x72);
    local_c = 1;
  }
  if (local_8 != -1) {
    if (DAT_0049f538 <= local_8) {
      local_8 = local_8 + 1;
    }
    _memset(&local_1c,0,0x10);
    local_1c = 3;
    local_18 = 10;
    local_1a = (undefined2)DAT_0049f538;
    local_10 = (undefined2)local_8;
    local_e = (undefined2)local_c;
    thunk_FUN_00414081(1,&local_1c,0x10);
  }
  return 1;
}
```

---

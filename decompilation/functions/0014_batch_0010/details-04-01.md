# 0014_batch_0010 — détails (1/3)

## FUN_004469d6 — 0x4469d6

- Classification : internal
- Corps : `0x4469d6–0x447204`
- État : pseudocode obtenu
- Evidence : `ev_af646caa747aeb02c1e96bdd6b32f50f4f6ca5d96ccacac948648818fb9f8bc4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401410` — `thunk_FUN_0040d3e1`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401c7b` — `thunk_FUN_004119ba`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401eab` — `thunk_FUN_0040bf98`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x40222a` — `thunk_FUN_00429e69`
- `0x402234` — `thunk_FUN_0042892d`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x4a11e0` — "smfont&&bgfont"
- `0x4a11f0` — "C:\\float\\src\\iwtask.cpp"
- `0x4a1208` — "NOTASKS"
- `0x4a1210` — "TNORM"
- `0x4a1218` — "THIGH"
- `0x4a1220` — "TEXCL"
- `0x4a1228` — "BLDNAME"
- `0x4a1238` — "C:\\float\\src\\iwtask.cpp"
- `0x4a1258` — "C:\\float\\src\\iwtask.cpp"
- `0x4a1270` — "BLDCONST"
- `0x4a127c` — "DELIVER"
- `0x4a1284` — "RETRIEVE"
- `0x4a1290` — "bildtone"
- `0x4a129c` — "STONE"
- `0x4a12a4` — "tonecrys"
- `0x4a12b0` — "CTONE"
- `0x4a12b8` — "magctone"
- `0x4a12c4` — "MTONE"
- `0x4a12cc` — "ARTIFACT"
- `0x4a12d8` — "TRIGGERS"
- `0x4a12e8` — "C:\\float\\src\\iwtask.cpp"
- `0x4a1300` — "bildicon"

### Pseudocode Ghidra

```c
void FUN_004469d6(void)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int in_ECX;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 local_e0;
  int local_c4;
  int local_c0;
  int local_bc;
  int local_b8;
  int local_b0;
  int local_ac;
  undefined1 local_9c [80];
  int local_4c;
  undefined *local_48;
  undefined4 local_44;
  int local_40;
  undefined4 local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  if (*(int *)(in_ECX + 0x34) == 0) {
    return;
  }
  if (*(int *)(in_ECX + 0x3c) == 0) {
    return;
  }
  uVar2 = thunk_FUN_0042d28f();
  *(undefined4 *)(in_ECX + 8) = uVar2;
  if (DAT_004c2bac == 0) {
    thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
  }
  else {
    uVar6 = 0;
    uVar5 = 0;
    iVar4 = (int)*(short *)(in_ECX + 0x1e);
    uVar2 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
    thunk_FUN_00404770(in_ECX + 8,uVar2,iVar4,uVar5,uVar6);
  }
  local_c = thunk_FUN_0042de0d();
  local_8 = thunk_FUN_0042de03();
  if ((local_c == 0) || (local_8 == 0)) {
    thunk_FUN_00414b64(s_C__float_src_iwtask_cpp_004a11f0,0x2d8,s_smfont__bgfont_004a11e0);
  }
  if ((*(int *)(in_ECX + 0x70) == 0) || (**(int **)(in_ECX + 0x70) == 0)) {
    local_10 = thunk_FUN_00429ebe(s_NOTASKS_004a1208,0);
    local_14 = thunk_FUN_0042892d(local_10,0xffffffff,0xffffffff);
    local_18 = ((*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) - local_14) / 2;
    thunk_FUN_004289c0(in_ECX + 8,local_18,0x32,local_10);
    goto LAB_004471e6;
  }
  local_1c = thunk_FUN_00429ebe(s_TNORM_004a1210,0);
  if (*(short *)(*(int *)(in_ECX + 0x70) + 6) == 2) {
    local_1c = thunk_FUN_00429ebe(s_THIGH_004a1218,0);
  }
  else if (*(short *)(*(int *)(in_ECX + 0x70) + 6) == 3) {
    local_1c = thunk_FUN_00429ebe(s_TEXCL_004a1220,0);
  }
  thunk_FUN_004289c0(in_ECX + 8,10,0x2b,local_1c);
  sVar1 = *(short *)(*(int *)(in_ECX + 0x70) + 0x10);
  if (sVar1 != 4) {
    if (sVar1 == 5) {
      local_30 = thunk_FUN_00429ebe(s_BLDNAME_004a1228,&local_2c);
      if (local_30 == 0) {
        thunk_FUN_00414b64(s_C__float_src_iwtask_cpp_004a1238,0x2f3,&DAT_004a1230);
      }
      local_34 = *(short *)(*(int *)(in_ECX + 0x70) + 0x12) + -0x25;
      local_30 = thunk_FUN_00429e69(local_2c + local_34 + DAT_0049f538 * 0x10,1);
      if (local_30 == 0) {
        thunk_FUN_00414b64(s_C__float_src_iwtask_cpp_004a1258,0x2f6,&DAT_004a1250);
      }
      local_24 = thunk_FUN_00429ebe(s_BLDCONST_004a1270,0);
      local_20 = thunk_FUN_0042892d(local_24,0xffffffff,0xffffffff);
      local_28 = ((*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) - local_20) / 2;
      thunk_FUN_0040d3e1(in_ECX + 8,DAT_0049f538,(int)*(short *)(*(int *)(in_ECX + 0x70) + 0x12),
                         (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) + -0x1e,
                         (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + -10,0x8000);
      thunk_FUN_004289c0(in_ECX + 8,local_28,5,local_24);
      thunk_FUN_004289c0(in_ECX + 8,10,0x1e,local_30);
      goto LAB_004471e6;
    }
    if (sVar1 != 0xd) goto LAB_004471e6;
  }
  uVar2 = thunk_FUN_00429ebe(s_DELIVER_004a127c,0);
  local_e0 = thunk_FUN_00429ebe(s_RETRIEVE_004a1284,0);
  if (*(short *)(*(int *)(in_ECX + 0x70) + 0x10) == 4) {
    local_e0 = uVar2;
  }
  local_44 = local_e0;
  local_40 = thunk_FUN_0042892d(local_e0,0xffffffff,0xffffffff);
  iVar4 = (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) - local_40;
  local_b0 = 0;
  local_ac = 0;
  local_4c = 4;
  sVar1 = *(short *)(*(int *)(in_ECX + 0x70) + 0x12);
  if (sVar1 == 1) {
    local_b0 = thunk_FUN_0040ec89(s_bildtone_004a1290,1);
    local_ac = thunk_FUN_00429ebe(s_STONE_004a129c,0);
  }
  else if (sVar1 == 2) {
    local_b0 = thunk_FUN_0040ec89(s_tonecrys_004a12a4,1);
    local_ac = thunk_FUN_00429ebe(s_CTONE_004a12b0,0);
  }
  else if (sVar1 == 3) {
    local_b0 = thunk_FUN_0040ec89(s_magctone_004a12b8,1);
    local_ac = thunk_FUN_00429ebe(s_MTONE_004a12c4,0);
  }
  if ((4 < *(short *)(*(int *)(in_ECX + 0x70) + 0x12)) &&
     (*(short *)(*(int *)(in_ECX + 0x70) + 0x12) < 0x22)) {
    local_ac = thunk_FUN_00429ebe(s_ARTIFACT_004a12cc,0);
    local_b0 = thunk_FUN_0040ec89(s_TRIGGERS_004a12d8,1);
    local_4c = *(short *)(*(int *)(in_ECX + 0x70) + 0x12) + -5;
  }
  thunk_FUN_004119ba(in_ECX + 8,local_b0,local_4c,&local_38,&local_3c);
  if ((*(short *)(*(int *)(in_ECX + 0x70) + 0x12) < 5) ||
     (0x21 < *(short *)(*(int *)(in_ECX + 0x70) + 0x12))) {
    local_38 = local_38 + 10;
  }
  local_48 = &DAT_005ec640 +
             *(short *)(*(int *)(in_ECX + 0x70) + 0xe) * 0x60 +
             *(short *)(*(int *)(in_ECX + 0x70) + 10) * 0x29e8;
  if (local_48 == (undefined *)0x0) {
    uVar2 = thunk_FUN_00414b64(s_C__float_src_iwtask_cpp_004a12e8,0x333,&DAT_004a12e4);
  }
  else {
    uVar2 = 0;
  }
  if (*(int *)(local_48 + 4) == 0) {
    thunk_FUN_0040bf98(in_ECX + 8,local_48,
                       (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) + -0x1e,
                       (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + -10,1,0x8000,0xffffffff
                       ,uVar2);
    iVar3 = thunk_FUN_00450385();
    if (iVar3 != 0) {
      local_b8 = (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) + -0x2d;
      local_c4 = 0x10;
      local_c0 = *(int *)(local_48 + 0x14);
      if (local_c0 < 0) {
        local_c0 = 0;
      }
      if (3 < local_c0) {
        local_c0 = 3;
      }
      uVar2 = thunk_FUN_0040ec89(s_bildicon_004a1300,1);
      for (local_bc = 0; local_bc < *(short *)(iVar3 + 0x60); local_bc = local_bc + 1) {
        thunk_FUN_00404770(in_ECX + 8,uVar2,local_c0,local_b8,local_c4);
        if (local_bc == 4) {
          local_b8 = (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) + -0x37;
          local_c4 = local_c4 + 5;
        }
        local_b8 = local_b8 + 5;
      }
    }
  }
  if (local_ac != 0) {
    FUN_00472ca0(local_9c,&DAT_004a130c,local_ac);
    thunk_FUN_004289c0(in_ECX + 8,10,0x1e,local_9c);
  }
  if (local_b0 != 0) {
    thunk_FUN_00404770(in_ECX + 8,local_b0,local_4c,local_38,local_3c);
  }
  thunk_FUN_004289c0(in_ECX + 8,iVar4 / 2,5,local_44);
LAB_004471e6:
  thunk_FUN_0042d38a();
  thunk_FUN_0042d87c(in_ECX + 8,1);
  return;
}
```

---

---

## FUN_00447205 — 0x447205

- Classification : internal
- Corps : `0x447205–0x447258`
- État : pseudocode obtenu
- Evidence : `ev_33df8d773512daf3b44f4dd61afb18475f1536fea0dac788daf547e0a713bbb1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401447` — `thunk_FUN_00447275`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00447205(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004919a2;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004945b8;
  thunk_FUN_00447275();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_00447259 — 0x447259

- Classification : internal
- Corps : `0x447259–0x447274`
- État : pseudocode obtenu
- Evidence : `ev_90a42be5b3c32c0f4f18c66d9b70215b0ec1d000c232369ebf946aa99fa60691`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00447259(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004945b8;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_00447275 — 0x447275

- Classification : internal
- Corps : `0x447275–0x447289`
- État : pseudocode obtenu
- Evidence : `ev_d2e585d8707217a159c7cfa996d4bd21acf05840ddc9c228d5bcd75eec1b335b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00447275(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x70) = 0;
  return;
}
```

---

---

## FUN_0044728a — 0x44728a

- Classification : internal
- Corps : `0x44728a–0x447422`
- État : pseudocode obtenu
- Evidence : `ev_836ec03804aee18d11a519b5dbeafaa89e911b7b36a1776513ee4d2605e1e304`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401569` — `thunk_FUN_0046c558`
- `0x401bf4` — `thunk_FUN_0042970c`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a1310` — "IWTasks"
- `0x4a1318` — "mpTaskList"
- `0x4a1324` — "C:\\float\\src\\iwtask.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0044728a(undefined2 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  int local_8;
  
  switch(param_1) {
  case 1:
    if (*(int *)(in_ECX + 0x70) == 0) {
      uVar2 = thunk_FUN_0046c558(s_IWTasks_004a1310,3,0);
      *(undefined4 *)(in_ECX + 0x70) = uVar2;
    }
    if (*(int *)(in_ECX + 0x70) == 0) {
      thunk_FUN_00414b64(s_C__float_src_iwtask_cpp_004a1324,0x382,s_mpTaskList_004a1318);
    }
    *(undefined2 *)(in_ECX + 0x74) = 0xffff;
  default:
    uVar2 = thunk_FUN_004293c6(param_1,param_2,param_3);
    break;
  case 6:
  case 7:
    iVar1 = thunk_FUN_00429f3a();
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      if ((*(int *)(in_ECX + 0x70) != 0) && (*(int *)(*(int *)(in_ECX + 0x70) + 0xf4) != 0)) {
        local_8 = -1;
        if (*(short *)(in_ECX + 0x74) == 0) {
          local_8 = 1;
        }
        else if (*(short *)(in_ECX + 0x74) == 1) {
          local_8 = 2;
        }
        else if (*(short *)(in_ECX + 0x74) == 2) {
          local_8 = 3;
        }
        if (-1 < local_8) {
          thunk_FUN_0042970c(*(undefined2 *)(in_ECX + 0x60),local_8,0);
        }
      }
      uVar2 = 1;
    }
    break;
  case 10:
    *(short *)(in_ECX + 0x74) =
         (short)((param_2 - *(int *)(in_ECX + 0xc)) /
                ((*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 3));
    if (*(short *)(in_ECX + 0x74) < 0) {
      *(undefined2 *)(in_ECX + 0x74) = 0;
    }
    if (3 < *(short *)(in_ECX + 0x74)) {
      *(undefined2 *)(in_ECX + 0x74) = 3;
    }
    uVar2 = 1;
  }
  return uVar2;
}
```

---

---

## FUN_00447e60 — 0x447e60

- Classification : internal
- Corps : `0x447e60–0x447e8d`
- État : pseudocode obtenu
- Evidence : `ev_f2a74df83dfa3ee697903f27959f8fb6e980de2dae0488815cf010e096691977`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4020f4` — `thunk_FUN_004450e4`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00447e60(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_004450e4();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_00447ea0 — 0x447ea0

- Classification : internal
- Corps : `0x447ea0–0x447ecd`
- État : pseudocode obtenu
- Evidence : `ev_8f782941ef3bff22f4f7a51e66f8dc2b8178b55d45a1959c479689ac1009c03f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013f2` — `thunk_FUN_004464e7`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00447ea0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_004464e7();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_00447ee0 — 0x447ee0

- Classification : internal
- Corps : `0x447ee0–0x447f0d`
- État : pseudocode obtenu
- Evidence : `ev_cee42edda90862f8d258f6fd6431f323b56eb051d17966e6ed74cc1e08d08e32`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f7d` — `thunk_FUN_0044695c`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00447ee0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0044695c();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_00447f20 — 0x447f20

- Classification : internal
- Corps : `0x447f20–0x447f4d`
- État : pseudocode obtenu
- Evidence : `ev_9de622eb23074459348362ef513f7936b0a922fc9e781dc077f9cbd99319fba8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4015c3` — `thunk_FUN_00447259`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00447f20(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00447259();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

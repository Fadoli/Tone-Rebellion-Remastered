# 0009_batch_0005 — détails (1/3)

## FUN_004120f6 — 0x4120f6

- Classification : internal
- Corps : `0x4120f6–0x4121b6`
- État : pseudocode obtenu
- Evidence : `ev_bd9d3c72685f34212092ba9063fe6498873dc22e95ebe358bcee4b0d29b46865`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004120f6(void)

{
  undefined4 *in_ECX;
  
  in_ECX[1] = 0;
  in_ECX[2] = 0xffffffff;
  in_ECX[3] = 0;
  in_ECX[0x4c] = 1;
  in_ECX[0x4d] = 0;
  in_ECX[0x4e] = 0;
  in_ECX[0x4f] = 0;
  in_ECX[0x50] = 0;
  in_ECX[0x51] = 0;
  *in_ECX = 0;
  _memset(in_ECX + 4,0,0x100);
  _memset(in_ECX + 0x48,0,0x10);
  _memset(in_ECX + 0x44,0,0x10);
  return;
}
```

---

## FUN_004121b7 — 0x4121b7

- Classification : internal
- Corps : `0x4121b7–0x412bec`
- État : pseudocode obtenu
- Evidence : `ev_436ec675045ff47701ee7511eba972fb3eac9f707eccb9322fefc66d4be20300`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401285` — `thunk_FUN_00436e06`
- `0x4013d4` — `thunk_FUN_004637fc`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x4016d6` — `thunk_FUN_00462f1d`
- `0x40173f` — `thunk_FUN_00412c1d`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x401d75` — `thunk_FUN_00414106`
- `0x401d9d` — `thunk_FUN_00460072`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472ca0` — `FUN_00472ca0`
- `0x472da0` — `FUN_00472da0`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x49b624` — "Duplicate Add Ignored: %s (%x)"
- `0x49b644` — "i<mNumPlayers"
- `0x49b654` — "C:\\float\\src\\command.cpp"
- `0x49b670` — "LEFTGAM"
- `0x49b678` — "%s %s"
- `0x49b680` — "REVSING"
- `0x49b688` — "player<mNumPlayers"
- `0x49b69c` — "C:\\float\\src\\command.cpp"
- `0x49b6b8` — "player<mNumPlayers"
- `0x49b6cc` — "C:\\float\\src\\command.cpp"
- `0x49b6e8` — "mbGameStarted==FALSE"
- `0x49b700` — "C:\\float\\src\\command.cpp"
- `0x49b71c` — "WORLDVIEW"
- `0x49b728` — "FALSE"
- `0x49b730` — "C:\\float\\src\\command.cpp"

### Pseudocode Ghidra

```c
void FUN_004121b7(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  byte bVar5;
  int in_ECX;
  undefined4 extraout_EDX;
  int local_b4;
  undefined4 local_b0;
  int local_ac;
  int local_a4;
  int local_9c;
  int local_94;
  int local_8c;
  int local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined1 local_7c [80];
  undefined4 local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 *local_10;
  int *local_c;
  int local_8;
  
  local_14 = *param_1;
  local_c = param_1 + 1;
  switch(local_14) {
  case 1:
    local_8 = *local_c;
    local_10 = param_1 + 2;
    local_18 = 0;
    for (local_1c = 0; local_1c < *(int *)(in_ECX + 4); local_1c = local_1c + 1) {
      if (*(int *)(in_ECX + 0x120 + local_1c * 4) == local_8) {
        local_18 = 1;
      }
    }
    local_c = local_10;
    if (local_18 == 0) {
      *(int *)(in_ECX + 0x120 + *(int *)(in_ECX + 4) * 4) = local_8;
      FUN_00472da0(in_ECX + 0x10 + *(int *)(in_ECX + 4) * 0x40,local_10);
      *(undefined4 *)(in_ECX + 0x110 + *(int *)(in_ECX + 4) * 4) = 0;
      *(int *)(in_ECX + 4) = *(int *)(in_ECX + 4) + 1;
      iVar2 = DAT_004c03ec;
    }
    else {
      thunk_FUN_00414ad0(s_Duplicate_Add_Ignored___s___x__0049b624,local_10,local_8);
      iVar2 = DAT_004c03ec;
    }
    break;
  case 2:
    local_8 = *local_c;
    for (local_24 = 0;
        (local_24 < *(int *)(in_ECX + 4) && (*(int *)(in_ECX + 0x120 + local_24 * 4) != local_8));
        local_24 = local_24 + 1) {
    }
    if (*(int *)(in_ECX + 4) <= local_24) {
      thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b654,0xd4,s_i<mNumPlayers_0049b644);
    }
    for (local_20 = 0;
        (local_20 < 4 && (*(int *)(in_ECX + 0x110 + local_24 * 4) != 1 << ((byte)local_20 & 0x1f)));
        local_20 = local_20 + 1) {
    }
    if (local_20 < 4) {
      thunk_FUN_00460072();
    }
    *(int *)(in_ECX + 4) = *(int *)(in_ECX + 4) + -1;
    local_2c = thunk_FUN_00429ebe(s_LEFTGAM_0049b670,0);
    FUN_00472ca0(local_7c,s__s__s_0049b678,&DAT_004beff0 + local_24 * 0x40,local_2c);
    uVar4 = thunk_FUN_0042dd0f(2);
    thunk_FUN_00436e06(local_7c,uVar4);
    for (local_28 = local_24; local_28 < *(int *)(in_ECX + 4); local_28 = local_28 + 1) {
      *(undefined4 *)(in_ECX + 0x120 + local_28 * 4) =
           *(undefined4 *)(in_ECX + 0x124 + local_28 * 4);
      FUN_00472da0(in_ECX + 0x10 + local_28 * 0x40,in_ECX + 0x10 + (local_28 + 1) * 0x40);
      *(undefined4 *)(in_ECX + 0x110 + local_28 * 4) =
           *(undefined4 *)(in_ECX + 0x114 + local_28 * 4);
    }
    *(undefined4 *)(in_ECX + 0x120 + local_28 * 4) = 0;
    *(undefined1 *)(in_ECX + 0x10 + local_28 * 0x40) = 0;
    *(undefined4 *)(in_ECX + 0x110 + local_28 * 4) = 0;
    if (*(int *)(in_ECX + 8) == local_24) {
      *(undefined4 *)(in_ECX + 8) = 0xffffffff;
      DAT_004befe4 = 1;
    }
    else if (local_24 < *(int *)(in_ECX + 8)) {
      *(int *)(in_ECX + 8) = *(int *)(in_ECX + 8) + -1;
    }
    if (local_24 < *(int *)(in_ECX + 0xc)) {
      *(int *)(in_ECX + 0xc) = *(int *)(in_ECX + 0xc) + -1;
    }
    iVar2 = DAT_004c03ec;
    if (DAT_004befe4 == 1) {
      DAT_004befe0 = 0;
      local_84 = 1;
      thunk_FUN_00414106(1,&local_84,4);
      local_80 = thunk_FUN_00429ebe(s_REVSING_0049b680,0);
      uVar4 = thunk_FUN_0042dd0f(2);
      thunk_FUN_00436e06(local_80,CONCAT31((int3)((uint)extraout_EDX >> 8),uVar4) & 0xffff00ff);
      iVar2 = DAT_004c03ec;
    }
    break;
  case 3:
    local_8 = *local_c;
    for (local_8c = 0;
        (local_8c < *(int *)(in_ECX + 4) && (*(int *)(in_ECX + 0x120 + local_8c * 4) != local_8));
        local_8c = local_8c + 1) {
    }
    iVar2 = local_8;
    if (local_8c != *(int *)(in_ECX + 4)) {
      thunk_FUN_00412c1d(local_8c);
      iVar2 = DAT_004c03ec;
    }
    break;
  case 4:
    iVar1 = *local_c;
    *(undefined4 *)(in_ECX + 0xc) = 0;
    for (local_88 = 0; iVar2 = DAT_004c03ec, local_88 < *(int *)(in_ECX + 4);
        local_88 = local_88 + 1) {
      if (*(int *)(in_ECX + 0x120 + local_88 * 4) == iVar1) {
        *(int *)(in_ECX + 0xc) = local_88;
        return;
      }
    }
    break;
  case 5:
    iVar2 = *local_c;
    local_c = param_1 + 2;
    uVar3 = *local_c;
    for (local_94 = 0;
        (local_94 < *(int *)(in_ECX + 4) && (*(int *)(in_ECX + 0x120 + local_94 * 4) != iVar2));
        local_94 = local_94 + 1) {
    }
    if (*(int *)(in_ECX + 4) <= local_94) {
      thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b69c,0x13f,s_player<mNumPlayers_0049b688);
    }
    local_9c = 0;
    while ((local_9c < *(int *)(in_ECX + 4) &&
           ((*(uint *)(in_ECX + 0x110 + local_9c * 4) & 1 << ((byte)uVar3 & 0x1f)) == 0))) {
      local_9c = local_9c + 1;
    }
    if ((local_9c == *(int *)(in_ECX + 4)) || (iVar2 = DAT_004c03ec, local_9c == local_94)) {
      *(uint *)(in_ECX + 0x110 + local_94 * 4) =
           *(uint *)(in_ECX + 0x110 + local_94 * 4) ^ 1 << ((byte)uVar3 & 0x1f);
      iVar2 = DAT_004c03ec;
    }
    break;
  case 6:
    iVar2 = DAT_004c03ec;
    if (*(int *)(in_ECX + 0x140) == 0) {
      iVar2 = *local_c;
      local_c = param_1 + 2;
      uVar3 = *local_c;
      for (local_a4 = 0;
          (local_a4 < *(int *)(in_ECX + 4) && (*(int *)(in_ECX + 0x120 + local_a4 * 4) != iVar2));
          local_a4 = local_a4 + 1) {
      }
      if (*(int *)(in_ECX + 4) <= local_a4) {
        thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b6cc,0x15d,s_player<mNumPlayers_0049b6b8);
      }
      local_ac = 0;
      while ((bVar5 = (byte)uVar3, local_ac < *(int *)(in_ECX + 4) &&
             ((*(uint *)(in_ECX + 0x110 + local_ac * 4) & 1 << (bVar5 & 0x1f)) == 0))) {
        local_ac = local_ac + 1;
      }
      if ((local_ac == *(int *)(in_ECX + 4)) || (iVar2 = DAT_004c03ec, local_ac == local_a4)) {
        *(uint *)(in_ECX + 0x110 + local_a4 * 4) =
             *(uint *)(in_ECX + 0x110 + local_a4 * 4) ^ 1 << (bVar5 & 0x1f);
        *(uint *)(in_ECX + 0x110 + local_a4 * 4) =
             *(uint *)(in_ECX + 0x110 + local_a4 * 4) & 1 << (bVar5 & 0x1f);
        iVar2 = DAT_004c03ec;
      }
    }
    break;
  case 7:
    *(int *)(in_ECX + 0x138) = *local_c;
    iVar2 = DAT_004c03ec;
    break;
  case 8:
    *(int *)(in_ECX + 0x13c) = *local_c;
    iVar2 = DAT_004c03ec;
    break;
  case 9:
    if (*(int *)(in_ECX + 0x140) != 0) {
      thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b700,0x195,s_mbGameStarted__FALSE_0049b6e8);
    }
    *(undefined4 *)(in_ECX + 0x140) = 1;
    DAT_004a4b78 = *local_c;
    local_b0 = 0;
    local_b4 = DAT_0049c9b0;
    if ((DAT_004c2b9c != 0) && (local_b0 = 1, DAT_0049c9b0 < 0)) {
      local_b4 = thunk_FUN_00467260(2);
      local_b4 = local_b4 << 1;
    }
    *(undefined4 *)(in_ECX + 0x130) = 1;
    if (DAT_004befe0 != 0) {
      *(undefined4 *)(in_ECX + 0x130) = 2;
    }
    thunk_FUN_004637fc(*(undefined4 *)(in_ECX + 0x138),*(undefined4 *)(in_ECX + 0x13c),local_b0,
                       local_b4);
    thunk_FUN_0046c3bc(s_WORLDVIEW_0049b71c,0x131,0,0);
    thunk_FUN_0046c1b4(1,2,0);
    iVar2 = DAT_004c03ec;
    break;
  case 10:
    *(uint *)(in_ECX + 0x144) = (uint)(*(int *)(in_ECX + 0x144) == 0);
    iVar2 = DAT_004c03ec;
    break;
  case 0xb:
    *(int *)(in_ECX + 0x130) = *local_c;
    iVar2 = DAT_004c03ec;
    break;
  case 0xc:
    *(undefined4 *)(in_ECX + 0x134) = 0;
    *(undefined4 *)(in_ECX + 0x138) = 0;
    *(undefined4 *)(in_ECX + 0x13c) = 0;
    *(undefined4 *)(in_ECX + 0x140) = 0;
    *(undefined4 *)(in_ECX + 0x144) = 0;
    *(undefined4 *)(in_ECX + 0x130) = 1;
    if (DAT_004befe0 != 0) {
      *(undefined4 *)(in_ECX + 0x130) = 2;
    }
    _memset((void *)(in_ECX + 0x110),0,0x10);
    thunk_FUN_00462f1d();
    thunk_FUN_0046c1b4(1,1,0);
    iVar2 = DAT_004c03ec;
    break;
  default:
    thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b730,0x1b7,s_FALSE_0049b728);
    iVar2 = DAT_004c03ec;
  }
  DAT_004c03ec = iVar2;
  return;
}
```

---

## FUN_00412c1d — 0x412c1d

- Classification : internal
- Corps : `0x412c1d–0x412cab`
- État : pseudocode obtenu
- Evidence : `ev_307296089f23e311584656d57c3aa44efd48fcb8ef6495d4f28533dfdc1e1654`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401d75` — `thunk_FUN_00414106`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49b74c` — "i>=0 && i<mNumPlayers"
- `0x49b764` — "C:\\float\\src\\command.cpp"

### Pseudocode Ghidra

```c
void FUN_00412c1d(int param_1)

{
  int in_ECX;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((param_1 < 0) || (*(int *)(in_ECX + 4) <= param_1)) {
    thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b764,0x1bf,s_i>_0____i<mNumPlayers_0049b74c);
  }
  *(int *)(in_ECX + 8) = param_1;
  if ((DAT_004befe0 != 0) && (DAT_004befec != DAT_004befe8)) {
    local_c = *(undefined4 *)(in_ECX + 0x120 + *(int *)(in_ECX + 0xc) * 4);
    local_8 = 1;
    thunk_FUN_00414106(3,&local_c,8);
  }
  return;
}
```

---

## FUN_00412cac — 0x412cac

- Classification : internal
- Corps : `0x412cac–0x412d09`
- État : pseudocode obtenu
- Evidence : `ev_8b8bd182d1dd288f562e632db8d2bbea798a89ac7a1d2498e5e63d98054ba18b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00412cac(int param_1)

{
  int in_ECX;
  int local_8;
  
  if (param_1 < 4) {
    for (local_8 = 0; local_8 < *(int *)(in_ECX + 4); local_8 = local_8 + 1) {
      if ((*(uint *)(in_ECX + 0x110 + local_8 * 4) & 1 << ((byte)param_1 & 0x1f)) != 0) {
        return local_8;
      }
    }
  }
  return -1;
}
```

---

## FUN_00412d0a — 0x412d0a

- Classification : internal
- Corps : `0x412d0a–0x412d6f`
- État : pseudocode obtenu
- Evidence : `ev_95f888b94b166ea841a654475fb0019ba6be42c9937e175b0ecfccfc544ccd2e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4017ad` — `thunk_FUN_004120e0`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401cee` — `thunk_FUN_0040fd80`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00412d0a(undefined4 param_1,int param_2)

{
  undefined4 in_ECX;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_14c [82];
  
  if (param_2 == 0) {
    thunk_FUN_0040fd80(in_ECX,0x148);
  }
  else {
    thunk_FUN_004120e0();
    thunk_FUN_0040fc15(local_14c,0x148);
    puVar2 = local_14c;
    puVar3 = &DAT_004befe0;
    for (iVar1 = 0x52; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  return;
}
```

---

## FUN_00412d70 — 0x412d70

- Classification : internal
- Corps : `0x412d70–0x412eab`
- État : pseudocode obtenu
- Evidence : `ev_08ab9f13d91a819fcc71f4ce3b4cbfdae6afb724cae76affc79a07b6cac6b226`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a8c` — `thunk_FUN_0044b3b7`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4734a0` — `FUN_004734a0`

### Chaînes référencées

- `0x49b780` — "size < (SEND_BUF_SIZE-3*sizeof(Dword))"
- `0x49b7a8` — "C:\\float\\src\\command.cpp"
- `0x49b7c4` — "success"
- `0x49b7cc` — "C:\\float\\src\\command.cpp"

### Pseudocode Ghidra

```c
void FUN_00412d70(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,uint param_5)

{
  int iVar1;
  int in_ECX;
  undefined4 local_c;
  
  if (0x53 < param_5) {
    thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b7a8,0x201,
                       s_size_<_(SEND_BUF_SIZE_3*sizeof(D_0049b780);
  }
  *(undefined4 *)(in_ECX + 0xc14) = param_1;
  *(undefined4 *)(in_ECX + 0xc18) = param_2;
  *(int *)(in_ECX + 0xc1c) = param_3;
  FUN_004734a0(in_ECX + 0xc20,param_4,param_5);
  if (-1 < DAT_004befe8) {
    local_c = 0xffffffff;
    if ((DAT_004befe0 != 0) && (DAT_004befec != DAT_004befe8)) {
      local_c = *(undefined4 *)(&DAT_004bf100 + DAT_004befe8 * 4);
    }
    iVar1 = thunk_FUN_0044b3b7(in_ECX + 0xc14,param_5 + 0xc,local_c);
    if (iVar1 == 0) {
      thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b7cc,0x218,s_success_0049b7c4);
    }
    if ((((param_3 != 3) && (param_3 != 5)) && (param_3 != 2)) && (param_3 != 6)) {
      *(int *)(in_ECX + 0x1280) = *(int *)(in_ECX + 0x1280) + 1;
    }
  }
  return;
}
```

---

## FUN_00412eac — 0x412eac

- Classification : internal
- Corps : `0x412eac–0x413087`
- État : pseudocode obtenu
- Evidence : `ev_eb34738a65ae7a5464539f5bda206e2a134ef34500d71e4f8c93b2c8c9b03cd2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401050` — `thunk_FUN_00413c60`
- `0x4010be` — `thunk_FUN_004133f2`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x402351` — `thunk_FUN_0044b532`

### Chaînes référencées

- `0x49b7e8` — "[PER %d] Command Received: Time %d  Period %d"
- `0x49b818` — "Buffered Periods Overflow...Exiting."
- `0x49b840` — "FALSE"
- `0x49b848` — "C:\\float\\src\\command.cpp"

### Pseudocode Ghidra

```c
int FUN_00412eac(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int in_ECX;
  uint local_20;
  uint local_1c;
  int local_10;
  int local_c;
  int *local_8;
  
  local_8 = (int *)0x0;
  local_8 = (int *)thunk_FUN_0044b532(&local_c);
  local_10 = 0;
  if (local_8 != (int *)0x0) {
    local_10 = *local_8;
    uVar2 = local_8[1];
    iVar3 = local_8[2];
    local_8 = local_8 + 3;
    local_20 = 0;
    if ((DAT_004befe0 != 0) && (DAT_004befec != DAT_004befe8)) {
      local_20 = 2;
    }
    local_1c = uVar2;
    if (((local_10 == 4) &&
        ((((iVar3 == 2 || (iVar3 == 5)) || (iVar3 == 3)) || ((iVar3 == 4 || (iVar3 == 6)))))) &&
       (((local_1c = *(uint *)(in_ECX + 0x1274), iVar3 == 5 || ((iVar3 == 3 || (iVar3 == 4)))) ||
        (iVar3 == 6)))) {
      local_20 = local_20 | 1;
    }
    thunk_FUN_004133f2(local_10,iVar3,local_8,local_c + -0xc,local_20,local_1c);
    if ((local_20 & 2) != 0) {
      uVar4 = uVar2 / *(uint *)(in_ECX + 0x1278);
      if ((*(uint *)(in_ECX + 0x127c) <= uVar4) && (0x40 < uVar4 - *(int *)(in_ECX + 0x127c))) {
        thunk_FUN_00414ad0(s__PER__d__Command_Received__Time___0049b7e8,
                           *(undefined4 *)(in_ECX + 0x127c),uVar2,uVar4);
        thunk_FUN_00414ad0(s_Buffered_Periods_Overflow___Exit_0049b818);
        thunk_FUN_00413c60();
        thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b848,0x270,s_FALSE_0049b840);
      }
      iVar1 = in_ECX + 0xc74 + (uVar4 % 0x40) * 0x18;
      if ((((iVar3 != 3) && (iVar3 != 5)) && (iVar3 != 2)) && (iVar3 != 6)) {
        *(int *)(iVar1 + 0xc) = *(int *)(iVar1 + 0xc) + 1;
      }
    }
  }
  return local_10;
}
```

---

## FUN_00413088 — 0x413088

- Classification : internal
- Corps : `0x413088–0x4132fe`
- État : pseudocode obtenu
- Evidence : `ev_20e8a8954d8f8520c6b9b69b9566850e380b49224fb67dbcee8e8f1469129bc6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010be` — `thunk_FUN_004133f2`
- `0x401258` — `thunk_FUN_00467ff6`
- `0x401d75` — `thunk_FUN_00414106`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00413088(void)

{
  int in_ECX;
  undefined4 local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int *local_20;
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  if ((DAT_004befe0 == 0) || (DAT_004befec != DAT_004befe8)) {
    local_1c = 0;
    local_20 = (int *)(in_ECX + 0xc74 + ((*(int *)(in_ECX + 0x127c) + 1U) % 0x40) * 0x18);
    if ((*local_20 == 1) && (local_20[3] == local_20[2])) {
      *local_20 = 0;
      local_20[3] = 0;
      local_8 = 1;
      DAT_0049b5ec = 1;
      DAT_0049b5e8 = 1;
      DAT_0049b5e4 = 1;
      DAT_0049b5e0 = 1;
      DAT_0049b5dc = 1;
      DAT_0049b5d8 = (uint)(local_20[4] == local_20[5]);
      if (DAT_0049b5d8 == 0) {
        local_28 = *(undefined4 *)(&DAT_004bf100 + DAT_004befec * 4);
        local_24 = *(undefined4 *)(in_ECX + 0x1274);
        thunk_FUN_00414106(4,&local_28,8);
      }
    }
  }
  else {
    local_18 = *(int *)(in_ECX + 0x127c) + 1;
    local_14 = *(undefined4 *)(in_ECX + 0x1280);
    local_10 = thunk_FUN_00467ff6();
    if (DAT_004c03d0 != 0) {
      local_8 = 1;
    }
    for (local_c = 0; local_c < DAT_004befe4; local_c = local_c + 1) {
      if ((local_c != DAT_004befec) && (0x1f < *(int *)(&DAT_004c03d8 + local_c * 4))) {
        local_8 = 0;
        break;
      }
    }
    if (local_8 != 0) {
      thunk_FUN_004133f2(4,2,&local_18,0xc,8,0);
      *(undefined4 *)(in_ECX + 0x1280) = 0;
    }
  }
  if (local_8 == 1) {
    *(undefined4 *)(in_ECX + 0x1284) = 0;
    *(int *)(in_ECX + 0x127c) = *(int *)(in_ECX + 0x127c) + 1;
    if (((DAT_004befe0 != 0) && (DAT_004befec != DAT_004befe8)) &&
       (*(uint *)(in_ECX + 0x127c) % 5 == 0)) {
      local_30 = *(undefined4 *)(&DAT_004bf100 + DAT_004befec * 4);
      local_2c = DAT_004c03e8 - *(int *)(in_ECX + 0x127c);
      if (local_2c < 0) {
        local_2c = 0;
      }
      thunk_FUN_00414106(6,&local_30,8);
    }
  }
  return local_8;
}
```

---

## FUN_004132ff — 0x4132ff

- Classification : internal
- Corps : `0x4132ff–0x413343`
- État : pseudocode obtenu
- Evidence : `ev_f8265925962c39ec0d1fdce355daec328e243f550ddc28604b2f32c85ef523a4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int * FUN_004132ff(void)

{
  int *in_ECX;
  int local_c;
  int *local_8;
  
  local_c = 0;
  local_8 = in_ECX;
  while( true ) {
    if (0x1f < local_c) {
      return (int *)0x0;
    }
    if (*local_8 == 0) break;
    local_c = local_c + 1;
    local_8 = local_8 + 0x18;
  }
  return local_8;
}
```

---

## FUN_00413344 — 0x413344

- Classification : internal
- Corps : `0x413344–0x4133f1`
- État : pseudocode obtenu
- Evidence : `ev_bbd327ad0d8fd20edaeb416bb271463696f49ca30bf0ccbec56244d490d60c0d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int * FUN_00413344(int param_1,int param_2)

{
  int *in_ECX;
  int local_10;
  int *local_c;
  
  if (in_ECX[param_1 + 0x300] != 0) {
    local_c = in_ECX;
    for (local_10 = 0; local_10 < 0x20; local_10 = local_10 + 1) {
      if (((*local_c == 1) && (local_c[1] == param_1)) &&
         (((uint)local_c[2] <= (uint)in_ECX[0x49d] || (param_2 == 0)))) {
        *local_c = 0;
        in_ECX[param_1 + 0x300] = in_ECX[param_1 + 0x300] + -1;
        return local_c;
      }
      local_c = local_c + 0x18;
    }
  }
  return (int *)0x0;
}
```

---

## FUN_004133f2 — 0x4133f2

- Classification : internal
- Corps : `0x4133f2–0x413674`
- État : pseudocode obtenu
- Evidence : `ev_34b7642d56fd0dae574f85396d8f78d7ba9c9e9804b2c5fbd60fb705b6d38df2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401050` — `thunk_FUN_00413c60`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401f96` — `thunk_FUN_00412d70`
- `0x40206d` — `thunk_FUN_004132ff`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x4734a0` — `FUN_004734a0`

### Chaînes référencées

- `0x49b864` — "mNextAvailCmdTime<mLatencyPeriod"
- `0x49b888` — "C:\\float\\src\\command.cpp"
- `0x49b8a4` — "availtime > cmdtime"
- `0x49b8b8` — "C:\\float\\src\\command.cpp"
- `0x49b8d4` — "No free buffers...Exiting"
- `0x49b8f4` — "C:\\float\\src\\command.cpp"

### Pseudocode Ghidra

```c
/* WARNING: Removing unreachable block (ram,0x004135db) */

void FUN_004133f2(int param_1,undefined4 param_2,undefined4 param_3,int param_4,uint param_5,
                 int param_6)

{
  int iVar1;
  undefined4 *puVar2;
  int in_ECX;
  int local_8;
  
  iVar1 = *(int *)(in_ECX + 0x1274);
  if ((param_5 & 2) == 0) {
    local_8 = iVar1;
    if (((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) || (DAT_004befe0 == 0)) {
      if ((param_5 & 8) == 0) {
        if ((param_5 & 1) == 0) {
          if (DAT_004befe0 == 0) {
            local_8 = iVar1 + *(int *)(in_ECX + 0x1278);
          }
          else {
            if (*(uint *)(in_ECX + 0x1278) <= *(uint *)(in_ECX + 0x1284)) {
              thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b888,0x399,
                                 s_mNextAvailCmdTime<mLatencyPeriod_0049b864);
            }
            local_8 = ((iVar1 + (*(uint *)(in_ECX + 0x1278) >> 1)) / *(uint *)(in_ECX + 0x1278) + 1)
                      * *(int *)(in_ECX + 0x1278) + *(int *)(in_ECX + 0x1284);
            *(int *)(in_ECX + 0x1284) = *(int *)(in_ECX + 0x1284) + 1;
            if (local_8 <= iVar1) {
              thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b8b8,0x3a0,
                                 s_availtime_>_cmdtime_0049b8a4);
            }
          }
        }
      }
      else {
        local_8 = iVar1 + (*(int *)(in_ECX + 0x1278) - (*(uint *)(in_ECX + 0x1278) >> 1));
      }
    }
  }
  else {
    local_8 = param_6;
  }
  if ((DAT_004befe0 != 0) && ((param_5 & 6) == 0)) {
    thunk_FUN_00412d70(param_1,local_8,param_2,param_3,param_4);
  }
  if (((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) ||
     ((DAT_004befe0 == 0 || ((param_5 & 6) != 0)))) {
    puVar2 = (undefined4 *)thunk_FUN_004132ff();
    if (puVar2 == (undefined4 *)0x0) {
      thunk_FUN_00414ad0(s_No_free_buffers___Exiting_0049b8d4);
      thunk_FUN_00413c60();
      thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b8f4,0x3bd,&DAT_0049b8f0);
    }
    *puVar2 = 1;
    puVar2[1] = param_1;
    puVar2[2] = local_8;
    puVar2[3] = param_4 + 4;
    FUN_004734a0(puVar2 + 4,&param_2,4);
    FUN_004734a0(puVar2 + 5,param_3,param_4);
    *(int *)(in_ECX + 0xc00 + param_1 * 4) = *(int *)(in_ECX + 0xc00 + param_1 * 4) + 1;
  }
  return;
}
```

---

## FUN_00413675 — 0x413675

- Classification : internal
- Corps : `0x413675–0x413b4f`
- État : pseudocode obtenu
- Evidence : `ev_a6354f3ad27e4f14eb1e4747d41de83ff4437d9276c0f7007fd0f488ceefdf2c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401050` — `thunk_FUN_00413c60`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x401ece` — `thunk_FUN_00413344`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x49b910` — "Attempt to overwrite PSD in use...Exiting"
- `0x49b93c` — "psd->flags==0"
- `0x49b94c` — "C:\\float\\src\\command.cpp"
- `0x49b968` — "i<GAMEENV.mNumPlayers"
- `0x49b980` — "C:\\float\\src\\command.cpp"
- `0x49b99c` — "i<GAMEENV.mNumPlayers"
- `0x49b9b4` — "C:\\float\\src\\command.cpp"
- `0x49b9d0` — "i<GAMEENV.mNumPlayers"
- `0x49b9e8` — "C:\\float\\src\\command.cpp"
- `0x49ba04` — "%d %%%%%%%%%% Received %s Arrival"
- `0x49ba28` — "i<GAMEENV.mNumPlayers"
- `0x49ba40` — "C:\\float\\src\\command.cpp"
- `0x49ba5c` — "%d %%%%%%%%%% Received %s Ack %d"
- `0x49ba80` — "FALSE"
- `0x49ba88` — "C:\\float\\src\\command.cpp"

### Pseudocode Ghidra

```c
void FUN_00413675(void)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  bool bVar5;
  int iVar6;
  uint *puVar7;
  int in_ECX;
  uint uVar8;
  undefined4 uVar9;
  int local_4c;
  int local_3c;
  int local_34;
  int local_28;
  
  while (iVar6 = thunk_FUN_00413344(4,1), iVar6 != 0) {
    puVar7 = (uint *)(iVar6 + 0x14);
    switch(*(undefined4 *)(iVar6 + 0x10)) {
    case 1:
      *(uint *)(in_ECX + 0x1278) = *puVar7;
      break;
    case 2:
      if ((DAT_004befe0 != 0) && (DAT_004befec != DAT_004befe8)) {
        uVar2 = *puVar7;
        iVar3 = *(int *)(iVar6 + 0x18);
        iVar6 = *(int *)(iVar6 + 0x1c);
        if ((int)DAT_004c03e8 < (int)uVar2) {
          DAT_004c03e8 = uVar2;
        }
        uVar8 = (int)uVar2 >> 0x1f;
        piVar1 = (int *)(in_ECX + 0xc74 + (((uVar2 ^ uVar8) - uVar8 & 0x3f ^ uVar8) - uVar8) * 0x18)
        ;
        if (*piVar1 != 0) {
          thunk_FUN_00414ad0(s_Attempt_to_overwrite_PSD_in_use__0049b910);
          thunk_FUN_00413c60();
          if (*piVar1 != 0) {
            thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b94c,0x404,s_psd_>flags__0_0049b93c);
          }
        }
        *piVar1 = 1;
        piVar1[1] = uVar2;
        piVar1[2] = iVar3;
        piVar1[4] = iVar6;
        DAT_004c03b8 = DAT_004c03b8 + 1;
      }
      break;
    case 3:
      if ((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) {
        for (local_3c = 0;
            (local_3c < DAT_004befe4 && (*(uint *)(&DAT_004bf100 + local_3c * 4) != *puVar7));
            local_3c = local_3c + 1) {
        }
        if (DAT_004befe4 <= local_3c) {
          thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b9e8,0x46c,
                             s_i<GAMEENV_mNumPlayers_0049b9d0);
        }
        *(undefined4 *)(&DAT_004c03c0 + local_3c * 4) = 1;
        thunk_FUN_00414ad0(s__d____________Received__s_Arriva_0049ba04,
                           *(undefined4 *)(in_ECX + 0x1274),&DAT_004beff0 + local_3c * 0x40);
        bVar5 = true;
        for (local_3c = 0; local_3c < DAT_004befe4; local_3c = local_3c + 1) {
          if ((DAT_004befec != local_3c) && (*(int *)(&DAT_004c03c0 + local_3c * 4) == 0)) {
            bVar5 = false;
          }
        }
        if ((bVar5) && (DAT_004c03d0 == 0)) {
          DAT_004c03d0 = 1;
          thunk_FUN_0046c1b4(5,0,0);
        }
      }
      break;
    case 4:
      if ((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) {
        for (local_28 = 0;
            (local_28 < DAT_004befe4 && (*(uint *)(&DAT_004bf100 + local_28 * 4) != *puVar7));
            local_28 = local_28 + 1) {
        }
        if (DAT_004befe4 <= local_28) {
          thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b980,0x43d,
                             s_i<GAMEENV_mNumPlayers_0049b968);
        }
      }
      break;
    case 5:
      if ((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) {
        uVar4 = *(undefined4 *)(iVar6 + 0x18);
        for (local_4c = 0;
            (local_4c < DAT_004befe4 && (*(uint *)(&DAT_004bf100 + local_4c * 4) != *puVar7));
            local_4c = local_4c + 1) {
        }
        if (local_4c < DAT_004befe4) {
          uVar9 = 0;
        }
        else {
          uVar9 = thunk_FUN_00414b64(s_C__float_src_command_cpp_0049ba40,0x494,
                                     s_i<GAMEENV_mNumPlayers_0049ba28);
        }
        *(undefined4 *)(&DAT_0049b5f0 + local_4c * 4) = uVar4;
        thunk_FUN_00414ad0(s__d____________Received__s_Ack__d_0049ba5c,
                           *(undefined4 *)(in_ECX + 0x1274),&DAT_004beff0 + local_4c * 0x40,uVar4,
                           uVar9);
      }
      break;
    case 6:
      if ((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) {
        uVar4 = *(undefined4 *)(iVar6 + 0x18);
        for (local_34 = 0;
            (local_34 < DAT_004befe4 && (*(uint *)(&DAT_004bf100 + local_34 * 4) != *puVar7));
            local_34 = local_34 + 1) {
        }
        if (DAT_004befe4 <= local_34) {
          thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b9b4,0x454,
                             s_i<GAMEENV_mNumPlayers_0049b99c);
        }
        *(undefined4 *)(&DAT_004c03d8 + local_34 * 4) = uVar4;
      }
      break;
    default:
      thunk_FUN_00414b64(s_C__float_src_command_cpp_0049ba88,0x49c,s_FALSE_0049ba80);
    }
  }
  return;
}
```

---

## FUN_00413b68 — 0x413b68

- Classification : internal
- Corps : `0x413b68–0x413c5f`
- État : pseudocode obtenu
- Evidence : `ev_f0de043d2aa2f8e66f7ede13c134f2b30e329dcf5f0a5a6fdbbc9ffb5d5d57d4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00413b68(void)

{
  int *in_ECX;
  int local_14;
  uint local_c;
  int *local_8;
  
  if (((DAT_004befe0 == 0) || (DAT_004befec != DAT_004befe8)) && (DAT_004befe0 != 0)) {
    local_c = 0;
    local_8 = in_ECX;
    for (local_14 = 0; local_14 < 0x20; local_14 = local_14 + 1) {
      if (((*local_8 == 1) && ((uint)in_ECX[0x49d] < (uint)local_8[2])) &&
         (local_c < (uint)(local_8[2] - in_ECX[0x49d]))) {
        local_c = local_8[2] - in_ECX[0x49d];
      }
      local_8 = local_8 + 0x18;
    }
    if ((DAT_004c03bc == 0) && ((uint)(in_ECX[0x49e] << 2) < local_c)) {
      _DAT_004bf114 = local_c >> 2;
      DAT_004c03bc = 1;
    }
    else if ((DAT_004c03bc != 0) && (local_c < (uint)(in_ECX[0x49e] << 1))) {
      _DAT_004bf114 = 0;
      DAT_004c03bc = 0;
    }
  }
  return;
}
```

---

## FUN_00413c60 — 0x413c60

- Classification : internal
- Corps : `0x413c60–0x413d85`
- État : pseudocode obtenu
- Evidence : `ev_4472f953f46f209135cb7f1cb60b52ed138e0bb9110b961ab459113a0ee4b154`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x49baa4` — "\n[Current] Tick %04d  Period %04d\n"
- `0x49bac8` — "%c Tick %04d  Class %04d  Size %04d [%d]"
- `0x49baf4` — "P%03d S%03d R%03d HCS %x CCS %x"

### Pseudocode Ghidra

```c
void FUN_00413c60(void)

{
  int *in_ECX;
  undefined1 local_10;
  int local_c;
  int *local_8;
  
  thunk_FUN_00414ad0(s__Current__Tick__04d_Period__04d_0049baa4,in_ECX[0x49d],in_ECX[0x49f]);
  local_8 = in_ECX;
  for (local_c = 0; local_c < 0x20; local_c = local_c + 1) {
    local_10 = 0x20;
    if (*local_8 != 0) {
      local_10 = 0x2a;
    }
    thunk_FUN_00414ad0(s__c_Tick__04d_Class__04d_Size__04_0049bac8,local_10,local_8[2],local_8[1],
                       local_8[3],local_8[4]);
    local_8 = local_8 + 0x18;
  }
  for (local_c = 0; local_c < 0x40; local_c = local_c + 1) {
    thunk_FUN_00414ad0(s_P_03d_S_03d_R_03d_HCS__x_CCS__x_0049baf4,in_ECX[local_c * 6 + 0x31e],
                       in_ECX[local_c * 6 + 799],in_ECX[local_c * 6 + 800],
                       in_ECX[local_c * 6 + 0x321],in_ECX[local_c * 6 + 0x322]);
  }
  thunk_FUN_00414ad0(&DAT_0049bb14);
  return;
}
```

---

## FUN_00413d86 — 0x413d86

- Classification : internal
- Corps : `0x413d86–0x413d9b`
- État : pseudocode obtenu
- Evidence : `ev_51ac6b66ad3a0f49caec3ad83fe26529427dd49255075682db91a2098a560966`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b4f` — `thunk_FUN_00413d9c`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00413d86(void)

{
  undefined4 in_ECX;
  
  thunk_FUN_00413d9c();
  return in_ECX;
}
```

---

## FUN_00413d9c — 0x413d9c

- Classification : internal
- Corps : `0x413d9c–0x413e70`
- État : pseudocode obtenu
- Evidence : `ev_c237cbb77808c2413fb7939337954826b54d17c5a8739afa716b3996dc8f6bb5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40152d` — `thunk_FUN_0044aa69`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00413d9c(void)

{
  void *in_ECX;
  int local_8;
  
  _memset(in_ECX,0,0xc00);
  _memset((void *)((int)in_ECX + 0xc00),0,0x14);
  for (local_8 = 0; local_8 < 0x40; local_8 = local_8 + 1) {
    *(undefined4 *)((int)in_ECX + local_8 * 0x18 + 0xc74) = 0;
    *(undefined4 *)((int)in_ECX + local_8 * 0x18 + 0xc80) = 0;
  }
  *(undefined4 *)((int)in_ECX + 0x1274) = 0;
  *(undefined4 *)((int)in_ECX + 0x127c) = 0;
  *(undefined4 *)((int)in_ECX + 0x1278) = 10;
  *(undefined4 *)((int)in_ECX + 0x1284) = 0;
  *(undefined4 *)((int)in_ECX + 0x1280) = 0;
  *(undefined4 *)((int)in_ECX + 0x1288) = 0;
  thunk_FUN_0044aa69(&LAB_0040133e);
  return;
}
```

---


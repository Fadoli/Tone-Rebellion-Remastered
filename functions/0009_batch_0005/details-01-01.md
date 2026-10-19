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

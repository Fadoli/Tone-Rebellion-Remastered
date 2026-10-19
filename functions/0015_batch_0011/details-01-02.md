# 0015_batch_0011 — détails (2/3)

## FUN_0044b1c5 — 0x44b1c5

- Classification : internal
- Corps : `0x44b1c5–0x44b1f5`
- État : pseudocode obtenu
- Evidence : `ev_8dc657701c4c328e0dc1707d4b1f515c4023a652e4b7aec1c8640a2eb9c503e5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0044b1c5(void)

{
  int *in_ECX;
  undefined4 local_c;
  
  if ((*in_ECX == 0) || (in_ECX[1] == 0)) {
    local_c = 0;
  }
  else {
    local_c = 1;
  }
  return local_c;
}
```

---

---

## FUN_0044b1f6 — 0x44b1f6

- Classification : internal
- Corps : `0x44b1f6–0x44b26d`
- État : pseudocode obtenu
- Evidence : `ev_4f65ceebf71771b23b2ccff00ad1c323fb00ec3006dfbd9b80f8a0953284ce0a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401203` — `thunk_FUN_0044b1c5`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a1d10` — "FALSE"
- `0x4a1d18` — "C:\\float\\src\\network.cpp"

### Pseudocode Ghidra

```c
int FUN_0044b1f6(void)

{
  int iVar1;
  int in_ECX;
  
  iVar1 = thunk_FUN_0044b1c5();
  if (iVar1 == 0) {
    iVar1 = -1;
  }
  else {
    DAT_005e1768 = 0;
    iVar1 = (**(code **)(*DAT_005e1770 + 0x30))(DAT_005e1770,0,&LAB_00401366,0,0);
    if (iVar1 < 0) {
      thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1d18,0x327,s_FALSE_004a1d10);
    }
    *(short *)(in_ECX + 0x16) = DAT_005e1768;
    iVar1 = (int)DAT_005e1768;
  }
  return iVar1;
}
```

---

---

## FUN_0044b26e — 0x44b26e

- Classification : internal
- Corps : `0x44b26e–0x44b3b6`
- État : pseudocode obtenu
- Evidence : `ev_8134dd6e57d128e0fed4c59e2d063c45a09918d81c83c9386fd21a304f4fb235`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a8c` — `thunk_FUN_0044b3b7`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x472e90` — `_strlen`
- `0x4737e0` — `_strncpy`

### Chaînes référencées

- `0x4a1d38` — "C:\\float\\src\\network.cpp"
- `0x4a1d54` — "num>=0 && num<NETNumPlayers"
- `0x4a1d70` — "C:\\float\\src\\network.cpp"
- `0x4a1d8c` — "success"
- `0x4a1d94` — "C:\\float\\src\\network.cpp"

### Pseudocode Ghidra

```c
void FUN_0044b26e(int param_1,char *param_2)

{
  size_t sVar1;
  int iVar2;
  int in_ECX;
  undefined4 local_8c;
  int local_88;
  char acStack_84 [119];
  undefined1 local_d;
  int local_c;
  char *local_8;
  
  if (param_2 == (char *)0x0) {
    thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1d38,0x33b,&DAT_004a1d34);
  }
  if ((param_1 < 0) || (DAT_005e1768 <= param_1)) {
    thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1d70,0x33c,
                       s_num>_0____num<NETNumPlayers_004a1d54);
  }
  local_8c = 0x70169;
  local_88 = (int)*(short *)(in_ECX + 8);
  local_8 = acStack_84;
  _strncpy(local_8,param_2,0x78);
  local_d = 0;
  sVar1 = _strlen(param_2);
  local_c = sVar1 + 9;
  if (local_c < 0) {
    local_c = 0;
  }
  if (0x80 < local_c) {
    local_c = 0x80;
  }
  iVar2 = thunk_FUN_0044b3b7(&local_8c,local_c,param_1);
  if (iVar2 == 0) {
    thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1d94,0x34a,s_success_004a1d8c);
  }
  return;
}
```

---

---

## FUN_0044b3b7 — 0x44b3b7

- Classification : internal
- Corps : `0x44b3b7–0x44b490`
- État : pseudocode obtenu
- Evidence : `ev_4311eafeb08c4e2f67f79eee519c4259c0fb6f3027e8053c2047f9dd050db518`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x4a1db8` — "INVALIDOBJECT"
- `0x4a1db8` — "INVALIDOBJECT"
- `0x4a1dc8` — "INVALIDPLAYER"
- `0x4a1dc8` — "INVALIDPLAYER"
- `0x4a1dd8` — "SENDTOOBIG"
- `0x4a1dd8` — "SENDTOOBIG"
- `0x4a1de4` — "UNKNOWN"
- `0x4a1de4` — "UNKNOWN"
- `0x4a1dec` — "NETWORK: Error sending message: %s.\n"

### Pseudocode Ghidra

```c
undefined4 FUN_0044b3b7(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int *in_ECX;
  char *local_10;
  int local_8;
  
  local_8 = param_3;
  if (param_3 == -1) {
    local_8 = 0;
  }
  if ((*in_ECX == 0) || (in_ECX[1] == 0)) {
    uVar1 = 0;
  }
  else {
    iVar2 = (**(code **)(*DAT_005e1770 + 0x68))(DAT_005e1770,DAT_005e1e94,local_8,1,param_1,param_2)
    ;
    if (iVar2 == 0) {
      uVar1 = 1;
    }
    else {
      switch(iVar2) {
      case -0x7788ff7e:
        local_10 = s_INVALIDOBJECT_004a1db8;
        break;
      default:
        local_10 = s_UNKNOWN_004a1de4;
        break;
      case -0x7788ff6a:
        local_10 = s_INVALIDPLAYER_004a1dc8;
        break;
      case -0x7788ff1a:
        local_10 = s_SENDTOOBIG_004a1dd8;
        break;
      case -0x7788fef2:
        local_10 = &DAT_004a1db0;
      }
      thunk_FUN_00414ad0(s_NETWORK__Error_sending_message____004a1dec,local_10);
      uVar1 = 0;
    }
  }
  return uVar1;
}
```

---

---

## FUN_0044b532 — 0x44b532

- Classification : internal
- Corps : `0x44b532–0x44b616`
- État : pseudocode obtenu
- Evidence : `ev_f412be75395a9410faa71bea88db2586740f8f8c4cdbe4d4d24ffd8086ba1f10`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cda` — `thunk_FUN_0044a55e`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x4a1e14` — "::getData ERR: %x  (size %d, avail %d)\n"

### Pseudocode Ghidra

```c
undefined4 * FUN_0044b532(undefined4 *param_1)

{
  undefined4 *puVar1;
  int *in_ECX;
  int local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  if ((*in_ECX == 0) || (in_ECX[1] == 0)) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    do {
      local_c = 1;
      local_8 = 0x408;
      local_10 = (**(code **)(*DAT_005e1770 + 100))
                           (DAT_005e1770,&local_14,&DAT_005e1e94,2,&DAT_005e2420,&local_8);
      if ((local_10 == 0) &&
         (((local_14 == 0 || (DAT_005e2420 == 0x60970)) || (DAT_005e2420 == 0x112694)))) {
        thunk_FUN_0044a55e(&DAT_005e2420,local_8);
        local_c = 0;
      }
    } while (local_c == 0);
    if ((local_10 != 0) && (local_10 != -0x7788ff42)) {
      thunk_FUN_00414ad0(s___getData_ERR___x__size__d__avai_004a1e14,local_10,local_8,0x408);
    }
    if (local_10 == 0) {
      if (param_1 != (undefined4 *)0x0) {
        *param_1 = local_8;
      }
      puVar1 = &DAT_005e2420;
    }
    else {
      puVar1 = (undefined4 *)0x0;
    }
  }
  return puVar1;
}
```

---

---

## FUN_0044b617 — 0x44b617

- Classification : internal
- Corps : `0x44b617–0x44b742`
- État : pseudocode obtenu
- Evidence : `ev_f5374da444616e5a8130fddb93aac02c3abfe11d1cbb23f90b441bd7c8e62f32`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a8c` — `thunk_FUN_0044b3b7`
- `0x401bd6` — `thunk_FUN_0044a3c8`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4734a0` — `FUN_004734a0`

### Chaînes référencées

- `0x4a1e3c` — "size + 3*sizeof(Dword) < MAX_COMMAND_SIZE"
- `0x4a1e68` — "C:\\float\\src\\network.cpp"

### Pseudocode Ghidra

```c
int FUN_0044b617(undefined4 param_1,undefined4 param_2,int param_3)

{
  int in_ECX;
  undefined4 uVar1;
  undefined4 local_8c;
  undefined4 local_88;
  int local_84;
  undefined1 auStack_80 [116];
  undefined1 *local_c;
  int local_8;
  
  if (*(int *)(in_ECX + 4) == 0) {
    local_8 = 0;
  }
  else {
    local_8 = 0;
    if (*(int *)(in_ECX + 0x10) == 1) {
      local_8 = thunk_FUN_0044a3c8(param_1,param_2,param_3,DAT_005e1e94,1);
    }
    else {
      local_8c = DAT_005e1e94;
      local_88 = param_1;
      local_84 = param_3;
      local_c = auStack_80;
      if (param_3 + 0xcU < 0x80) {
        uVar1 = 0;
      }
      else {
        uVar1 = thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1e68,0x414,
                                   s_size___3_sizeof_Dword__<_MAX_COM_004a1e3c);
      }
      FUN_004734a0(local_c,param_2,param_3,uVar1);
      if (DAT_005e1ef8 != 0) {
        local_8 = thunk_FUN_0044b3b7(&local_8c,param_3 + 0xc,DAT_005e1ef8);
      }
    }
    if (local_8 != 0) {
      *(undefined4 *)(in_ECX + 0x38) = 1;
    }
  }
  return local_8;
}
```

---

---

## FUN_0044b743 — 0x44b743

- Classification : internal
- Corps : `0x44b743–0x44b779`
- État : pseudocode obtenu
- Evidence : `ev_a4a316c4b4350b205bddeaf1ab2f2d98706443da479ee453762bd5b8e2d412fc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401659` — `thunk_FUN_0044b617`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044b743(void)

{
  int in_ECX;
  
  if (*(int *)(in_ECX + 4) != 0) {
    if (*(int *)(in_ECX + 0x38) == 0) {
      thunk_FUN_0044b617(0,0,0);
    }
    *(undefined4 *)(in_ECX + 0x38) = 0;
  }
  return;
}
```

---

---

## FUN_0044b77a — 0x44b77a

- Classification : internal
- Corps : `0x44b77a–0x44b9e6`
- État : pseudocode obtenu
- Evidence : `ev_e7f3f8ad66ce04a120258f2ccd5068a3e7b0c2eeff6a51bd938c4ab0d97bce4a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a8c` — `thunk_FUN_0044b3b7`
- `0x401bd6` — `thunk_FUN_0044a3c8`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402351` — `thunk_FUN_0044b532`
- `0x4734a0` — `FUN_004734a0`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a1e84` — "NETNumCommands==0"
- `0x4a1e98` — "C:\\float\\src\\network.cpp"
- `0x4a1eb4` — "stuffed==TRUE"
- `0x4a1ec4` — "C:\\float\\src\\network.cpp"
- `0x4a1ee0` — "count==mGameDescription.CurrentPlayers"
- `0x4a1f08` — "C:\\float\\src\\network.cpp"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0044b77a(void)

{
  undefined4 *puVar1;
  int iVar2;
  int in_ECX;
  int local_48;
  int local_44;
  short local_40;
  short local_34;
  undefined1 local_30 [32];
  int *local_10;
  undefined4 *local_c;
  undefined4 local_8;
  
  if ((*(int *)(in_ECX + 4) != 0) && (*(int *)(in_ECX + 0x10) != 0)) {
    if (DAT_005e19f8 != 0) {
      thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1e98,0x43b,s_NETNumCommands__0_004a1e84);
    }
    FUN_004734a0(&DAT_005e2020,&DAT_005e1f58,0x80);
    _DAT_005e30f8 = 1;
    DAT_005e19f8 = 1;
    local_48 = 0;
    _memset(local_30,0,0x20);
    do {
      puVar1 = (undefined4 *)thunk_FUN_0044b532(0);
      if (puVar1 == (undefined4 *)0x0) {
        local_c = (undefined4 *)0x0;
      }
      else {
        local_8 = puVar1[2];
        local_c = puVar1 + 3;
        local_48 = local_48 + 1;
        iVar2 = thunk_FUN_0044a3c8(puVar1[1],local_c,local_8,*puVar1,0);
        if (iVar2 != 1) {
          thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1ec4,0x469,s_stuffed__TRUE_004a1eb4);
        }
      }
    } while (local_48 < *(short *)(in_ECX + 0x16) + -1);
    if (local_48 != 0) {
      DAT_005e2420 = DAT_005e1e94;
      DAT_005e2424 = local_48 + 1;
      local_c = (undefined4 *)&DAT_005e2428;
      local_34 = 0;
      local_44 = 8;
      for (local_40 = 0; local_40 < 8; local_40 = local_40 + 1) {
        if (*(int *)(&DAT_005e30f8 + local_40 * 4) != 0) {
          local_10 = (int *)(&DAT_005e2028 + local_40 * 0x80);
          FUN_004734a0(local_c,&DAT_005e2020 + local_40 * 0x80,*local_10 + 0xc);
          local_44 = local_44 + 0xc + *local_10;
          local_c = (undefined4 *)(local_44 + 0x5e2420);
          local_34 = local_34 + 1;
        }
      }
      if (local_34 != *(short *)(in_ECX + 0x16)) {
        thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1f08,0x48d,
                           s_count__mGameDescription_CurrentP_004a1ee0);
      }
      thunk_FUN_0044b3b7(&DAT_005e2420,local_44,0xffffffff);
    }
  }
  return;
}
```

---

---

## FUN_0044b9e7 — 0x44b9e7

- Classification : internal
- Corps : `0x44b9e7–0x44bbdf`
- État : pseudocode obtenu
- Evidence : `ev_5ce25a29fb5b015de80ce1dcf3f8229027639e486bb7a9461e3bbb3ef4e2c274`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401bd6` — `thunk_FUN_0044a3c8`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402351` — `thunk_FUN_0044b532`

### Chaînes référencées

- `0x4a1f24` — "mGameDescription.CurrentPlayers>1"
- `0x4a1f48` — "C:\\float\\src\\network.cpp"
- `0x4a1f64` — "NETNumCommands==0"
- `0x4a1f78` — "C:\\float\\src\\network.cpp"
- `0x4a1f94` — "(uDword)fromplayer==NETHostID"
- `0x4a1fb4` — "C:\\float\\src\\network.cpp"
- `0x4a1fd0` — "num_messages==mGameDescription.CurrentPlayers"
- `0x4a2000` — "C:\\float\\src\\network.cpp"
- `0x4a201c` — "stuffed==TRUE"
- `0x4a202c` — "C:\\float\\src\\network.cpp"

### Pseudocode Ghidra

```c
void FUN_0044b9e7(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int in_ECX;
  short local_1c;
  int *local_c;
  
  if ((*(int *)(in_ECX + 4) != 0) && (*(int *)(in_ECX + 0x10) == 0)) {
    if (DAT_005e1ef8 == 0) {
      thunk_FUN_0044b532(0);
    }
    else {
      if (*(short *)(in_ECX + 0x16) < 2) {
        thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1f48,0x4a4,
                           s_mGameDescription_CurrentPlayers>_004a1f24);
      }
      if (DAT_005e19f8 != 0) {
        thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1f78,0x4a7,s_NETNumCommands__0_004a1f64);
      }
      do {
        piVar3 = (int *)thunk_FUN_0044b532(0);
        if (*(int *)(in_ECX + 0x10) != 0) {
          return;
        }
      } while (piVar3 == (int *)0x0);
      iVar1 = piVar3[1];
      local_c = piVar3 + 2;
      if (*piVar3 != DAT_005e1ef8) {
        thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1fb4,0x4b8,
                           s__uDword_fromplayer__NETHostID_004a1f94);
      }
      if (iVar1 != *(short *)(in_ECX + 0x16)) {
        thunk_FUN_00414b64(s_C__float_src_network_cpp_004a2000,0x4b9,
                           s_num_messages__mGameDescription_C_004a1fd0);
      }
      for (local_1c = 0; local_1c < iVar1; local_1c = local_1c + 1) {
        iVar2 = local_c[2];
        iVar4 = thunk_FUN_0044a3c8(local_c[1],local_c + 3,iVar2,*local_c,0);
        if (iVar4 != 1) {
          thunk_FUN_00414b64(s_C__float_src_network_cpp_004a202c,0x4c6,s_stuffed__TRUE_004a201c);
        }
        local_c = (int *)((int)(local_c + 3) + iVar2);
      }
    }
  }
  return;
}
```

---

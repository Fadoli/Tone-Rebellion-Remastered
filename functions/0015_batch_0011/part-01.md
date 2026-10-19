# 0015_batch_0011 — détails (1/6)

## FUN_0044a9ce — 0x44a9ce

- Classification : internal
- Corps : `0x44a9ce–0x44aa55`
- État : pseudocode obtenu
- Evidence : `ev_9249d43a95d4e2f940b23e9798b1767c962cb54b79a8b7df058c2e570fb395a9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0044a9ce(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = 0;
  in_ECX[1] = 0;
  in_ECX[3] = 0;
  in_ECX[0xe] = 0;
  DAT_005e1ef0 = 0;
  DAT_005e1770 = 0;
  DAT_005e1768 = 0;
  DAT_005e1ef8 = 0;
  DAT_005e19f8 = 0;
  DAT_005e30a0 = 0;
  DAT_005e176c = 0;
  _memset(&DAT_005e30f8,0,0x20);
  return in_ECX;
}
```

---

## FUN_0044aa56 — 0x44aa56

- Classification : internal
- Corps : `0x44aa56–0x44aa68`
- État : pseudocode obtenu
- Evidence : `ev_e710df6b90993d980a9328bc590d963c784e8565c8404aa2c84e28386d548313`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018d4` — `thunk_FUN_0044ac6a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044aa56(void)

{
  thunk_FUN_0044ac6a();
  return;
}
```

---

## FUN_0044aa69 — 0x44aa69

- Classification : internal
- Corps : `0x44aa69–0x44aa7d`
- État : pseudocode obtenu
- Evidence : `ev_1fe58eead7f04543d50523af3e7f109ffe7579886b288a1b77a10c8d56a9af51`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044aa69(undefined4 param_1)

{
  DAT_005e3170 = param_1;
  return;
}
```

---

## FUN_0044aa7e — 0x44aa7e

- Classification : internal
- Corps : `0x44aa7e–0x44ab4b`
- État : pseudocode obtenu
- Evidence : `ev_626128d7beef07bce123c5d2225d3285dcef8c5cc72dbfe21d5738831ca54913`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x472a56` — `DPLAYX.DLL::DirectPlayEnumerateA`
- `0x4737e0` — `_strncpy`

### Chaînes référencées

- `0x4a1b0c` — "\nDirectPlayEnumerate returned non DP_OK\n\n."
- `0x4a1b38` — "FALSE"
- `0x4a1b40` — "C:\\float\\src\\network.cpp"

### Pseudocode Ghidra

```c
int FUN_0044aa7e(int param_1,short param_2)

{
  int iVar1;
  short local_c;
  
  DAT_005e1f50 = 0;
  iVar1 = DirectPlayEnumerateA(&LAB_004022e8,0);
  if (iVar1 == 0) {
    if ((param_1 != 0) && (0 < param_2)) {
      for (local_c = 0; (local_c < param_2 && (local_c < DAT_005e1f50)); local_c = local_c + 1) {
        _strncpy((char *)(param_1 + local_c * 0x20),&DAT_005e2d78 + local_c * 0x68,0x20);
        *(undefined1 *)(param_1 + 0x1f + local_c * 0x20) = 0;
      }
    }
    iVar1 = (int)DAT_005e1f50;
  }
  else {
    thunk_FUN_00414ad0(s_DirectPlayEnumerate_returned_non_004a1b0c);
    thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1b40,0x1f7,s_FALSE_004a1b38);
    iVar1 = 0;
  }
  return iVar1;
}
```

---

## FUN_0044ab4c — 0x44ab4c

- Classification : internal
- Corps : `0x44ab4c–0x44ab79`
- État : pseudocode obtenu
- Evidence : `ev_4efaff10b21d5e4e237b06818a6409626a19734b1ae878adc824f04292206534`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476e20` — `_strncmp`

### Chaînes référencées

- `0x4a1b5c` — "IPX Connect"

### Pseudocode Ghidra

```c
bool FUN_0044ab4c(short param_1)

{
  int iVar1;
  
  iVar1 = _strncmp(&DAT_005e2d78 + param_1 * 0x68,s_IPX_Connect_004a1b5c,0xb);
  return iVar1 == 0;
}
```

---

## FUN_0044ab7a — 0x44ab7a

- Classification : internal
- Corps : `0x44ab7a–0x44ac69`
- État : pseudocode obtenu
- Evidence : `ev_cedb6d9d1e7d924b24d1354bcd6ad3c795e181eeccc0307e797367234e54545d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x472a5c` — `DPLAYX.DLL::DirectPlayCreate`

### Chaînes référencées

- `0x4a1b68` — "\nDirectPlay Object Created with %s.\n\n"
- `0x4a1b90` — "\nCreate failed with %s (%x)\n\n"
- `0x4a1bb0` — "\nQueryInterface for DP2 failed.\n"
- `0x4a1bd4` — "NETlpDplayObject!=NULL"
- `0x4a1bec` — "C:\\float\\src\\network.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0044ab7a(short param_1)

{
  undefined4 uVar1;
  int iVar2;
  int *in_ECX;
  
  if (*in_ECX == 0) {
    iVar2 = DirectPlayCreate(&DAT_005e2d60 + param_1 * 0x68,&DAT_005e1ef0,0);
    if (iVar2 == 0) {
      thunk_FUN_00414ad0(s_DirectPlay_Object_Created_with___004a1b68,&DAT_005e2d78 + param_1 * 0x68)
      ;
      iVar2 = (**(code **)*DAT_005e1ef0)(DAT_005e1ef0,&DAT_004945f8,&DAT_005e1770);
      if (iVar2 == 0) {
        if (DAT_005e1770 == 0) {
          thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1bec,0x24c,
                             s_NETlpDplayObject__NULL_004a1bd4);
        }
        *in_ECX = 1;
        uVar1 = 1;
      }
      else {
        thunk_FUN_00414ad0(s_QueryInterface_for_DP2_failed__004a1bb0);
        uVar1 = 0;
      }
    }
    else {
      thunk_FUN_00414ad0(s_Create_failed_with__s___x__004a1b90,&DAT_005e2d78 + param_1 * 0x68,iVar2)
      ;
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
```

---

## FUN_0044ac6a — 0x44ac6a

- Classification : internal
- Corps : `0x44ac6a–0x44acd7`
- État : pseudocode obtenu
- Evidence : `ev_08fd46e63e9e3b021c9acdb1a9c32a2384411b486415cdfa14c0eb22cbf2229e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401938` — `thunk_FUN_0044b172`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044ac6a(void)

{
  int *in_ECX;
  
  if (*in_ECX != 0) {
    if (in_ECX[1] != 0) {
      thunk_FUN_0044b172();
    }
    (**(code **)(*DAT_005e1ef0 + 8))(DAT_005e1ef0);
    (**(code **)(*DAT_005e1770 + 8))(DAT_005e1770);
    DAT_005e1770 = (int *)0x0;
    *in_ECX = 0;
    DAT_005e1768 = 0;
    DAT_005e1ef8 = 0;
  }
  return;
}
```

---

## FUN_0044acd8 — 0x44acd8

- Classification : internal
- Corps : `0x44acd8–0x44aed7`
- État : pseudocode obtenu
- Evidence : `ev_2906f5aef3536577f9bde30454b3f61718ae3515e2c8217d234c7151a764ee11`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x4023c9` — `thunk_FUN_0044c0ec`
- `0x4024af` — `thunk_FUN_0044bded`
- `0x472da0` — `FUN_00472da0`
- `0x4737e0` — `_strncpy`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a1c08` — "max_players <= NET_MAXPLAYERS"
- `0x4a1c28` — "C:\\float\\src\\network.cpp"
- `0x4a1c44` — "NETWORK: createGame Failed.\n"
- `0x4a1c64` — "CreatePlayer in ::createGame failed.\n"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0044acd8(char *param_1,short param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  int *in_ECX;
  undefined4 local_18 [2];
  undefined *local_10;
  undefined *local_c;
  undefined4 local_8;
  
  if ((*in_ECX == 0) || (in_ECX[1] == 1)) {
    uVar1 = 0;
  }
  else {
    if (param_2 < 9) {
      uVar1 = 0;
    }
    else {
      uVar1 = thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1c28,0x273,
                                 s_max_players_<__NET_MAXPLAYERS_004a1c08);
    }
    _memset(&DAT_005e1a00,0,0x50);
    _DAT_005e1a00 = 0x50;
    _DAT_005e1a04 = 0x44;
    _DAT_005e1a18 = 0xf8cbd700;
    _DAT_005e1a1c = 0x11cf9ea3;
    _DAT_005e1a20 = 0xa000a98b;
    _DAT_005e1a24 = 0x30521724;
    _DAT_005e1a28 = (int)param_2;
    FUN_00472da0(&DAT_005e1f00,param_1,uVar1);
    _DAT_005e1a30 = &DAT_005e1f00;
    iVar2 = (**(code **)(*DAT_005e1770 + 0x60))(DAT_005e1770,&DAT_005e1a00,2);
    if (iVar2 == 0) {
      FUN_00472da0(&DAT_005e3120,param_3);
      local_18[0] = 0x10;
      local_10 = &DAT_005e3120;
      local_c = &DAT_005e3120;
      local_8 = 0;
      iVar2 = (**(code **)(*DAT_005e1770 + 0x18))(DAT_005e1770,&DAT_005e1e94,local_18,0,0,0,0);
      if (iVar2 == 0) {
        *(short *)(in_ECX + 5) = param_2;
        *(undefined2 *)((int)in_ECX + 0x16) = 1;
        _strncpy((char *)(in_ECX + 6),param_1,0x20);
        in_ECX[4] = 1;
        in_ECX[1] = 1;
        DAT_005e1ef8 = DAT_005e1e94;
        _DAT_005e2880 = DAT_005e1e94;
        FUN_00472da0(&DAT_005e2830,&DAT_005e3120);
        thunk_FUN_0044bded(0);
        in_ECX[3] = 0;
        uVar1 = 1;
      }
      else {
        thunk_FUN_00414ad0(s_CreatePlayer_in___createGame_fai_004a1c64);
        thunk_FUN_0044c0ec(0x14);
        uVar1 = 0;
      }
    }
    else {
      thunk_FUN_00414ad0(s_NETWORK__createGame_Failed__004a1c44);
      thunk_FUN_0044c0ec(0x16);
      uVar1 = 0;
    }
  }
  return uVar1;
}
```

---

## FUN_0044aed8 — 0x44aed8

- Classification : internal
- Corps : `0x44aed8–0x44afcb`
- État : pseudocode obtenu
- Evidence : `ev_f0969ff3d7f0979beb7048a7b454b6d3391a5d77ab254d5b8c750931dcc91ac8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402298` — `thunk_FUN_00414ad0`
- `0x4737e0` — `_strncpy`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a1c8c` — "dplay->EnumSessions failed in ::findGamesToJoin\n"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

short FUN_0044aed8(int param_1,short param_2)

{
  short sVar1;
  int iVar2;
  int *in_ECX;
  short local_c;
  
  if (*in_ECX == 0) {
    sVar1 = 0;
  }
  else {
    _memset(&DAT_005e1a00,0,0x50);
    _DAT_005e1a00 = 0x50;
    DAT_005e3118 = 0;
    iVar2 = (**(code **)(*DAT_005e1770 + 0x34))(DAT_005e1770,&DAT_005e1a00,0,&LAB_004013b1,0,1);
    if ((iVar2 == 0) || (iVar2 == -0x7788ff24)) {
      sVar1 = DAT_005e3118;
      if ((param_1 != 0) && (0 < param_2)) {
        for (local_c = 0; (sVar1 = DAT_005e3118, local_c < param_2 && (local_c < DAT_005e3118));
            local_c = local_c + 1) {
          _strncpy((char *)(param_1 + 4 + local_c * 0x24),*(char **)(&DAT_005e17a8 + local_c * 0x50)
                   ,0x20);
        }
      }
    }
    else {
      thunk_FUN_00414ad0(s_dplay_>EnumSessions_failed_in____004a1c8c);
      sVar1 = 0;
    }
  }
  return sVar1;
}
```

---

## FUN_0044afcc — 0x44afcc

- Classification : internal
- Corps : `0x44afcc–0x44b171`
- État : pseudocode obtenu
- Evidence : `ev_853a8f9712db522a617ca498cc15606a6218663b158140ac793b6afd61554b8c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402298` — `thunk_FUN_00414ad0`
- `0x4023c9` — `thunk_FUN_0044c0ec`
- `0x472da0` — `FUN_00472da0`
- `0x4737e0` — `_strncpy`

### Chaînes référencées

- `0x4a1cc0` — "dplay->Open failed in joinGame.\n"
- `0x4a1ce4` — "dplay->CreatePlayer in ::joinGame failed.\n"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0044afcc(short param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  int *in_ECX;
  undefined4 local_18 [2];
  undefined *local_10;
  undefined *local_c;
  undefined4 local_8;
  
  if ((*in_ECX == 0) || (in_ECX[1] == 1)) {
    uVar1 = 0;
  }
  else {
    _DAT_005e1a00 = 0x50;
    _DAT_005e1a18 = 0xf8cbd700;
    _DAT_005e1a1c = 0x11cf9ea3;
    _DAT_005e1a20 = 0xa000a98b;
    _DAT_005e1a24 = 0x30521724;
    iVar2 = param_1 * 0x50;
    _DAT_005e1a08 = *(undefined4 *)(&DAT_005e1780 + iVar2);
    _DAT_005e1a0c = *(undefined4 *)(&DAT_005e1784 + iVar2);
    _DAT_005e1a10 = *(undefined4 *)(&DAT_005e1788 + iVar2);
    _DAT_005e1a14 = *(undefined4 *)(&DAT_005e178c + iVar2);
    iVar2 = (**(code **)(*DAT_005e1770 + 0x60))(DAT_005e1770,&DAT_005e1a00,1);
    if (iVar2 == 0) {
      FUN_00472da0(&DAT_005e3120,param_2);
      local_18[0] = 0x10;
      local_10 = &DAT_005e3120;
      local_c = &DAT_005e3120;
      local_8 = 0;
      iVar2 = (**(code **)(*DAT_005e1770 + 0x18))(DAT_005e1770,&DAT_005e1e94,local_18,0,0,0,0);
      if (iVar2 == 0) {
        *(undefined2 *)(in_ECX + 5) = *(undefined2 *)(&DAT_005e17a0 + param_1 * 0x50);
        *(short *)((int)in_ECX + 0x16) = (short)*(undefined4 *)(&DAT_005e17a4 + param_1 * 0x50) + 1;
        _strncpy((char *)(in_ECX + 6),*(char **)(&DAT_005e17a8 + param_1 * 0x50),0x20);
        in_ECX[1] = 1;
        in_ECX[3] = 0;
        uVar1 = 1;
      }
      else {
        thunk_FUN_00414ad0(s_dplay_>CreatePlayer_in___joinGam_004a1ce4);
        thunk_FUN_0044c0ec(0x14);
        uVar1 = 0;
      }
    }
    else {
      thunk_FUN_00414ad0(s_dplay_>Open_failed_in_joinGame__004a1cc0);
      thunk_FUN_0044c0ec(0x15);
      uVar1 = 0;
    }
  }
  return uVar1;
}
```

---

## FUN_0044b172 — 0x44b172

- Classification : internal
- Corps : `0x44b172–0x44b1c4`
- État : pseudocode obtenu
- Evidence : `ev_2ea60b7415695c6b1f6922057160bbc78956d9c89a3d84b825c32bca996d5d2c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044b172(void)

{
  int in_ECX;
  
  if (*(int *)(in_ECX + 4) != 0) {
    (**(code **)(*DAT_005e1770 + 0x24))(DAT_005e1770,DAT_005e1e94);
    (**(code **)(*DAT_005e1770 + 0x10))(DAT_005e1770);
    *(undefined4 *)(in_ECX + 4) = 0;
    *(undefined4 *)(in_ECX + 0xc) = 0;
  }
  return;
}
```

---

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

## FUN_0044bbe0 — 0x44bbe0

- Classification : internal
- Corps : `0x44bbe0–0x44bc81`
- État : pseudocode obtenu
- Evidence : `ev_36d3c7d01449d9a1e262db3a58b7034101b06b1e8caa99b2b055f06220688b3d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a2048` — "NETNumCommands >= 0"
- `0x4a205c` — "C:\\float\\src\\network.cpp"

### Pseudocode Ghidra

```c
undefined * FUN_0044bbe0(void)

{
  short local_c;
  
  local_c = 0;
  while( true ) {
    if (7 < local_c) {
      return (undefined *)0x0;
    }
    if (*(int *)(&DAT_005e30f8 + local_c * 4) != 0) break;
    local_c = local_c + 1;
  }
  *(undefined4 *)(&DAT_005e30f8 + local_c * 4) = 0;
  DAT_005e19f8 = DAT_005e19f8 + -1;
  if (-1 < DAT_005e19f8) {
    return &DAT_005e2020 + local_c * 0x80;
  }
  thunk_FUN_00414b64(s_C__float_src_network_cpp_004a205c,0x4e2,s_NETNumCommands_>__0_004a2048);
  return &DAT_005e2020 + local_c * 0x80;
}
```

---

## FUN_0044bc82 — 0x44bc82

- Classification : internal
- Corps : `0x44bc82–0x44bce4`
- État : pseudocode obtenu
- Evidence : `ev_9dee919368a81ff1b0ca77d445a2eb94970e0a6fb8dabc96b973030e4641ac10`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_0044bc82(void)

{
  ushort uVar1;
  undefined *local_8;
  
  local_8 = (undefined *)0x0;
  if (0 < DAT_005e176c) {
    local_8 = &DAT_005e1a90 + DAT_005e30a0 * 0x80;
    DAT_005e176c = DAT_005e176c + -1;
    uVar1 = (ushort)(DAT_005e30a0 + 1 >> 0x1f);
    DAT_005e30a0 = (((ushort)(DAT_005e30a0 + 1) ^ uVar1) - uVar1 & 7 ^ uVar1) - uVar1;
  }
  return local_8;
}
```

---

## FUN_0044bce5 — 0x44bce5

- Classification : internal
- Corps : `0x44bce5–0x44bd11`
- État : pseudocode obtenu
- Evidence : `ev_c5da577026982c4dc599d3b5b16e56b860abad043effbd15cef9a4d9067e6497`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0044bce5(void)

{
  undefined4 uVar1;
  int *in_ECX;
  
  if (in_ECX[1] == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = DAT_005e1e94;
    if (*in_ECX == 0) {
      uVar1 = 1;
    }
  }
  return uVar1;
}
```

---

## FUN_0044bd12 — 0x44bd12

- Classification : internal
- Corps : `0x44bd12–0x44bd4e`
- État : pseudocode obtenu
- Evidence : `ev_284f74334de9d4acae842f071f094054cf58f258cb7a0b4c863793f892ceaae1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_0044bd12(int param_1)

{
  undefined *puVar1;
  int *in_ECX;
  
  if ((in_ECX[1] == 0) || (*in_ECX == 0)) {
    puVar1 = (undefined *)0x0;
  }
  else if (param_1 < DAT_005e1768) {
    puVar1 = &DAT_005e2830 + param_1 * 0x54;
  }
  else {
    puVar1 = (undefined *)0x0;
  }
  return puVar1;
}
```

---


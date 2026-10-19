# 0015_batch_0011 — détails (1/3)

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

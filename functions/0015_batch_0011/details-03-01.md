# 0015_batch_0011 — détails (1/3)

## FUN_0044e77f — 0x44e77f

- Classification : internal
- Corps : `0x44e77f–0x44e9c6`
- État : pseudocode obtenu
- Evidence : `ev_5daea5a48e2013c7f961c54ebc7f59f3634fefaee46c6040bea3c9a16d225acd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472da0` — `FUN_00472da0`
- `0x472db0` — `FUN_00472db0`
- `0x472e90` — `_strlen`
- `0x476e20` — `_strncmp`

### Chaînes référencées

- `0x4a25bc` — "mpTextData"
- `0x4a25c8` — "C:\\float\\src\\newgame.cpp"
- `0x4a25e4` — "newgame.txt"
- `0x4a25f0` — "Couldn't load newgame.txt"
- `0x4a260c` — "FALSE"
- `0x4a2614` — "C:\\float\\src\\newgame.cpp"
- `0x4a2630` — "ENDTEXT"
- `0x4a2640` — "count<8"
- `0x4a2648` — "C:\\float\\src\\newgame.cpp"
- `0x4a2664` — "total_len<4096"
- `0x4a2674` — "C:\\float\\src\\newgame.cpp"

### Pseudocode Ghidra

```c
void FUN_0044e77f(undefined4 param_1)

{
  int iVar1;
  size_t sVar2;
  int in_ECX;
  char local_484 [512];
  int local_284;
  char local_274 [100];
  int local_210;
  int local_20c;
  int local_208;
  char local_204 [512];
  
  *(undefined4 *)(in_ECX + 0x78) = param_1;
  if (*(int *)(in_ECX + 0x78) == 0) {
    thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a25c8,0xbe,s_mpTextData_004a25bc);
  }
  iVar1 = thunk_FUN_0040f419(s_newgame_txt_004a25e4,&DAT_004b28f0,20000);
  if (iVar1 != 0) {
    thunk_FUN_00414ad0(s_Couldn_t_load_newgame_txt_004a25f0);
    thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a2614,0xc4,s_FALSE_004a260c);
  }
  local_20c = 0;
  local_208 = 0;
  while( true ) {
    thunk_FUN_0040f5b3(local_274,1);
    iVar1 = _strncmp(local_274,s_ENDTEXT_004a2630,7);
    if (iVar1 == 0) break;
    local_210 = 0;
    local_484[0] = '\0';
    while (local_210 == 0) {
      thunk_FUN_0040f5b3(local_204,1);
      iVar1 = _strncmp(local_204,&DAT_004a2638,3);
      if (iVar1 == 0) {
        local_210 = 1;
      }
      else {
        FUN_00472db0(local_484,local_204);
        FUN_00472db0(local_484,&DAT_004a263c);
      }
    }
    FUN_00472da0(*(int *)(in_ECX + 0x78) + local_20c,local_484);
    if (7 < local_208) {
      thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a2648,0xe5,s_count<8_004a2640);
    }
    *(undefined2 *)(in_ECX + 0x7c + local_208 * 2) = (undefined2)local_20c;
    local_208 = local_208 + 1;
    sVar2 = _strlen(local_484);
    local_284 = sVar2 + 1;
    local_20c = local_20c + local_284;
    if (0xfff < local_20c) {
      thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a2674,0xea,s_total_len<4096_004a2664);
    }
  }
  return;
}
```

---

---

## FUN_0044e9c7 — 0x44e9c7

- Classification : internal
- Corps : `0x44e9c7–0x44ebb6`
- État : pseudocode obtenu
- Evidence : `ev_90336bf93e608443b174f85bc4aceb53bdf75a61c92435e761292a6714e3c5fc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401235` — `thunk_FUN_0044ebea`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x4018d9` — `thunk_FUN_0044e77f`
- `0x401c44` — `thunk_FUN_0044e440`
- `0x402491` — `thunk_FUN_0042dd0f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0044e9c7(short param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 uVar3;
  
  switch((int)param_1) {
  case 1:
    *(undefined4 *)(in_ECX + 0x74) = 0xbf;
    *(undefined4 *)(in_ECX + 0x70) = 1;
    DAT_0049f538 = 0xffffffff;
    thunk_FUN_0044e77f(&DAT_005e3c30);
    uVar3 = extraout_var;
    if (DAT_005e4c50 == 0) {
      thunk_FUN_0044e440();
      DAT_005e4c50 = 1;
      uVar3 = extraout_var_00;
    }
    uVar2 = thunk_FUN_004293c6(CONCAT22(uVar3,param_1),param_2,param_3);
    break;
  default:
    uVar2 = thunk_FUN_004293c6(CONCAT22((short)((uint)(param_1 + -1) >> 0x10),param_1),param_2,
                               param_3);
    break;
  case 5:
    switch(param_2) {
    case 0x24:
      if (DAT_004c2b74 != 0) {
        uVar1 = thunk_FUN_0042dd0f(1);
        *(uint *)(in_ECX + 0x74) = uVar1 & 0xff;
      }
      break;
    case 0x25:
      if (DAT_004c2b74 != 0) {
        *(int *)(in_ECX + 0x74) = *(int *)(in_ECX + 0x74) + -1;
        if (*(int *)(in_ECX + 0x74) < 0) {
          *(undefined4 *)(in_ECX + 0x74) = 0;
        }
        if (0xfe < *(int *)(in_ECX + 0x74)) {
          *(undefined4 *)(in_ECX + 0x74) = 0xfe;
        }
      }
      break;
    case 0x26:
      if (DAT_004c2b74 != 0) {
        *(undefined4 *)(in_ECX + 0x74) = 0;
      }
      break;
    case 0x27:
      if (DAT_004c2b74 != 0) {
        *(int *)(in_ECX + 0x74) = *(int *)(in_ECX + 0x74) + 1;
        if (*(int *)(in_ECX + 0x74) < 0) {
          *(undefined4 *)(in_ECX + 0x74) = 0;
        }
        if (0xfe < *(int *)(in_ECX + 0x74)) {
          *(undefined4 *)(in_ECX + 0x74) = 0xfe;
        }
      }
      break;
    case 0x28:
      if (DAT_004c2b74 != 0) {
        *(undefined4 *)(in_ECX + 0x74) = 0xfe;
      }
    }
    *(undefined4 *)(in_ECX + 0x70) = 1;
    uVar2 = 0;
    break;
  case 6:
    uVar2 = thunk_FUN_0044ebea(param_2,param_3);
    break;
  case 0xb:
    *(undefined4 *)(in_ECX + 0x70) = 1;
    uVar2 = thunk_FUN_004293c6(param_1,param_2,param_3);
  }
  return uVar2;
}
```

---

---

## FUN_0044ebea — 0x44ebea

- Classification : internal
- Corps : `0x44ebea–0x44ec5c`
- État : pseudocode obtenu
- Evidence : `ev_1c56b29ef4733e1eb0bb465727e460ffd1ca105a01dfbc019e26ae0d3e355a8f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401bf4` — `thunk_FUN_0042970c`
- `0x401c53` — `thunk_FUN_0044e4f8`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0044ebea(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = thunk_FUN_0044e4f8(param_1,param_2);
  if (iVar1 == -1) {
    uVar2 = 0;
  }
  else {
    if (iVar1 < 4) {
      thunk_FUN_0042970c(0x3c,iVar1,0);
    }
    else if (iVar1 == 4) {
      thunk_FUN_0042970c(0x37,0,0);
    }
    else if (iVar1 == 5) {
      thunk_FUN_0042970c(0x35,0,0);
    }
    uVar2 = 1;
  }
  return uVar2;
}
```

---

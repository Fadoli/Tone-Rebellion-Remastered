# 0011_batch_0007 — détails (3/6)

## FUN_0042932e — 0x42932e

- Classification : internal
- Corps : `0x42932e–0x429370`
- État : pseudocode obtenu
- Evidence : `ev_c0574bd39964ad940abbaf5b280c342994d1a18f59b8df6da2c7043dcc07c24e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4016e5` — `thunk_FUN_00429371`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042932e(short param_1,short param_2)

{
  int in_ECX;
  
  thunk_FUN_00429371(param_1 - *(short *)(in_ECX + 0xc),
                     (int)param_2 - (int)*(short *)(in_ECX + 0x10));
  return;
}
```

---

## FUN_00429371 — 0x429371

- Classification : internal
- Corps : `0x429371–0x4293c5`
- État : pseudocode obtenu
- Evidence : `ev_51b634fe06c786d0da12aa5e5e381ee1d3d21c36a0d651e14f6ccbbf4756c206`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429371(short param_1,short param_2)

{
  int in_ECX;
  
  *(int *)(in_ECX + 0xc) = *(int *)(in_ECX + 0xc) + (int)param_1;
  *(int *)(in_ECX + 0x14) = *(int *)(in_ECX + 0x14) + (int)param_1;
  *(int *)(in_ECX + 0x10) = *(int *)(in_ECX + 0x10) + (int)param_2;
  *(int *)(in_ECX + 0x18) = *(int *)(in_ECX + 0x18) + (int)param_2;
  return;
}
```

---

## FUN_004293c6 — 0x4293c6

- Classification : internal
- Corps : `0x4293c6–0x4296db`
- État : pseudocode obtenu
- Evidence : `ev_bbd0349559f2561b262f1718ee7be05b291e7901ed6823ee2a56b1199ceec572`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014b5` — `thunk_FUN_0045b20c`
- `0x401bd1` — `thunk_FUN_00429209`
- `0x401bf4` — `thunk_FUN_0042970c`
- `0x4020b8` — `thunk_FUN_0046bc7e`
- `0x4021c6` — `thunk_FUN_0046ba3b`

### Chaînes référencées

- `0x49de30` — "button"

### Pseudocode Ghidra

```c
undefined4 FUN_004293c6(short param_1,int param_2,int param_3)

{
  int iVar1;
  int in_ECX;
  undefined2 uVar2;
  undefined2 extraout_var;
  short local_14;
  int local_10;
  int local_c;
  
  switch(param_1) {
  case 1:
    *(undefined4 *)(in_ECX + 0x3c) = 1;
    *(undefined4 *)(in_ECX + 0x38) = 1;
    *(undefined4 *)(in_ECX + 0x34) = 1;
    break;
  case 2:
    *(undefined4 *)(in_ECX + 0x3c) = 0;
    *(undefined4 *)(in_ECX + 0x38) = 0;
    thunk_FUN_0046bc7e(*(undefined4 *)(in_ECX + 4),0xffffffff);
    thunk_FUN_0046ba3b(*(undefined4 *)(in_ECX + 4),0xffffffff);
    break;
  case 3:
    *(undefined4 *)(in_ECX + 0x38) = 1;
    *(undefined4 *)(in_ECX + 0x3c) = 1;
    break;
  case 4:
    *(undefined4 *)(in_ECX + 0x38) = 0;
    break;
  case 6:
  case 7:
    if (*(int *)(in_ECX + 4) == DAT_0062c6bc) {
      local_14 = *(short *)(in_ECX + 0x60);
      local_c = *(int *)(in_ECX + 100);
      iVar1 = (int)local_14;
      if (iVar1 == 999) {
        local_14 = param_1;
      }
      if (local_c == 999) {
        local_c = (int)param_1;
      }
      local_10 = *(int *)(in_ECX + 0x68);
      if (*(int *)(in_ECX + 0x68) == 999) {
        iVar1 = (int)param_1;
        local_10 = iVar1;
      }
      uVar2 = (undefined2)((uint)iVar1 >> 0x10);
      if (DAT_0049c994 != 0) {
        thunk_FUN_0045b20c(s_button_0049de30,100,0);
        uVar2 = extraout_var;
      }
      thunk_FUN_0042970c(CONCAT22(uVar2,local_14),local_c,local_10);
      return 1;
    }
    break;
  case 8:
    if (((*(int *)(in_ECX + 0x3c) != 0) && (*(int *)(in_ECX + 0x38) != 0)) &&
       (*(int *)(in_ECX + 0x44) != 0)) {
      *(undefined4 *)(in_ECX + 0x34) = 3;
    }
    return 1;
  case 9:
    if (((*(int *)(in_ECX + 0x3c) != 0) && (*(int *)(in_ECX + 0x38) != 0)) &&
       (*(int *)(in_ECX + 0x44) != 0)) {
      *(undefined4 *)(in_ECX + 0x34) = 2;
    }
    return 1;
  case 0xb:
    if (*(int *)(in_ECX + 0x3c) != 0) {
      if ((param_2 == 1) || (param_3 == 0)) {
        *(undefined4 *)(in_ECX + 0x34) = 1;
      }
      else {
        iVar1 = thunk_FUN_00429209(*(undefined4 *)(in_ECX + 0xc),*(undefined4 *)(in_ECX + 0x10),
                                   param_3);
        if ((((iVar1 != 0) ||
             (iVar1 = thunk_FUN_00429209(*(undefined4 *)(in_ECX + 0xc),
                                         *(undefined4 *)(in_ECX + 0x18),param_3), iVar1 != 0)) ||
            (iVar1 = thunk_FUN_00429209(*(undefined4 *)(in_ECX + 0x14),
                                        *(undefined4 *)(in_ECX + 0x10),param_3), iVar1 != 0)) ||
           (((iVar1 = thunk_FUN_00429209(*(undefined4 *)(in_ECX + 0x14),
                                         *(undefined4 *)(in_ECX + 0x18),param_3), iVar1 != 0 ||
             (iVar1 = thunk_FUN_00429209(*(undefined4 *)(param_3 + 4),*(undefined4 *)(param_3 + 8),
                                         in_ECX + 8), iVar1 != 0)) ||
            ((iVar1 = thunk_FUN_00429209(*(undefined4 *)(param_3 + 0xc),*(undefined4 *)(param_3 + 8)
                                         ,in_ECX + 8), iVar1 != 0 ||
             ((iVar1 = thunk_FUN_00429209(*(undefined4 *)(param_3 + 4),
                                          *(undefined4 *)(param_3 + 0x10),in_ECX + 8), iVar1 != 0 ||
              (iVar1 = thunk_FUN_00429209(*(undefined4 *)(param_3 + 0xc),
                                          *(undefined4 *)(param_3 + 0x10),in_ECX + 8), iVar1 != 0)))
             ))))) {
          *(undefined4 *)(in_ECX + 0x34) = 1;
        }
      }
    }
    break;
  case 0xc:
    *(undefined2 *)(in_ECX + 0x1e) = (undefined2)param_2;
    return 1;
  }
  return 0;
}
```

---

## FUN_0042970c — 0x42970c

- Classification : internal
- Corps : `0x42970c–0x429787`
- État : pseudocode obtenu
- Evidence : `ev_2e243e6a44367a7224df1caee9e1f5b99329e761a4a81153c14c96085d459ce7`
- Note de routage : le champ `+0x48` choisit entre callback actif (mode 0), dispatch secondaire (mode 1) et file locale (mode 2). Le callback est indexé par le slot actif; le branchement indirect ne prouve pas sa cible sans l'état runtime. Evidence `ev_196d5ce18818030f061f610add4e421b67b51a08a81cfe4b30f91fd722d4a4dc`.
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013f7` — `thunk_FUN_0046c402`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x4019e2` — `thunk_FUN_0046c1b4`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042970c(undefined2 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int in_ECX;
  
  iVar1 = *(int *)(in_ECX + 0x48);
  if (iVar1 == 0) {
    thunk_FUN_0046c402(param_1,param_2,param_3);
  }
  else if (iVar1 == 1) {
    thunk_FUN_0046c1b4(param_1,param_2,param_3);
  }
  else if (iVar1 == 2) {
    thunk_FUN_0046c3bc(in_ECX + 0x4c,param_1,param_2,param_3);
  }
  return;
}
```

---

## FUN_00429788 — 0x429788

- Classification : internal
- Corps : `0x429788–0x4299be`
- État : pseudocode obtenu
- Evidence : `ev_56e83c017f6fd2569849a58abd5e20c96572a556bb2fbeb9d76f6ce5b6d04f51`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011a9` — `thunk_FUN_00403c35`
- `0x401276` — `thunk_FUN_0042dd95`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x40247d` — `thunk_FUN_00404637`
- `0x402491` — `thunk_FUN_0042dd0f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429788(undefined4 param_1)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int *in_ECX;
  
  if ((in_ECX[0xd] != 0) && (in_ECX[0xf] != 0)) {
    if (((in_ECX[1] == DAT_0062c6bc) || (in_ECX[0xd] == 2)) &&
       ((in_ECX[0x11] != 0 && (in_ECX[0xd] != 3)))) {
      (**(code **)(*in_ECX + 0xc))(param_1);
    }
    else if (*(short *)((int)in_ECX + 0x1e) == -1) {
      uVar1 = thunk_FUN_0042dd0f(2);
      iVar2 = thunk_FUN_0042d28f();
      in_ECX[2] = iVar2;
      thunk_FUN_00404637(in_ECX + 2,0,0,in_ECX[5] - in_ECX[3],in_ECX[6] - in_ECX[4],uVar1);
      thunk_FUN_00403c35(in_ECX + 2,0,0,in_ECX[5] - in_ECX[3],0,0,uVar1);
      thunk_FUN_00403c35(in_ECX + 2,0,0,0,in_ECX[6] - in_ECX[4],0,uVar1);
      thunk_FUN_00403c35(in_ECX + 2,in_ECX[5] - in_ECX[3],in_ECX[6] - in_ECX[4],
                         in_ECX[5] - in_ECX[3],0,0,uVar1);
      thunk_FUN_00403c35(in_ECX + 2,in_ECX[5] - in_ECX[3],in_ECX[6] - in_ECX[4],0,
                         in_ECX[6] - in_ECX[4],0,uVar1);
      thunk_FUN_0042d38a();
      thunk_FUN_0042dd95(in_ECX[3],in_ECX[4],in_ECX + 8);
    }
    else {
      iVar2 = (in_ECX[5] - in_ECX[3]) / 2;
      iVar3 = (in_ECX[6] - in_ECX[4]) / 2;
      iVar4 = thunk_FUN_0042d28f();
      in_ECX[2] = iVar4;
      iVar4 = (int)*(short *)((int)in_ECX + 0x1e);
      uVar5 = thunk_FUN_0040e864((short)in_ECX[7]);
      thunk_FUN_00404770(in_ECX + 2,uVar5,iVar4,iVar2,iVar3);
      thunk_FUN_0042d38a();
    }
    thunk_FUN_0042d87c(in_ECX + 2,3);
    in_ECX[0xd] = 0;
  }
  return;
}
```

---

## FUN_004299bf — 0x4299bf

- Classification : internal
- Corps : `0x4299bf–0x429c45`
- État : pseudocode obtenu
- Evidence : `ev_1e36d8610cb51eb0473880cb1ecbd4fed515de4f7e74104939c7d3d8e8342019`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011a9` — `thunk_FUN_00403c35`
- `0x401276` — `thunk_FUN_0042dd95`
- `0x40163b` — `thunk_FUN_00404c3b`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x402086` — `thunk_FUN_00404c5a`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x40247d` — `thunk_FUN_00404637`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004299bf(void)

{
  undefined1 uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int in_ECX;
  int iVar5;
  size_t _Size;
  int iVar6;
  undefined1 local_10c [256];
  int local_c;
  int local_8;
  
  if (*(short *)(in_ECX + 0x1e) == -1) {
    uVar1 = thunk_FUN_0042dd0f(3);
    uVar3 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar3;
    thunk_FUN_00404637(in_ECX + 8,0,0,*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc),
                       *(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10),uVar1);
    thunk_FUN_00403c35(in_ECX + 8,0,0,*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc),0,0,uVar1);
    thunk_FUN_00403c35(in_ECX + 8,0,0,0,*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10),0,uVar1);
    thunk_FUN_00403c35(in_ECX + 8,*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc),
                       *(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10),
                       *(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc),0,0,uVar1);
    thunk_FUN_00403c35(in_ECX + 8,*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc),
                       *(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10),0,
                       *(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10),0,uVar1);
    thunk_FUN_0042d38a();
    thunk_FUN_0042dd95(*(undefined4 *)(in_ECX + 0xc),*(undefined4 *)(in_ECX + 0x10),in_ECX + 0x20);
  }
  else {
    _Size = 0x100;
    uVar2 = thunk_FUN_0042dd0f(1);
    _memset(local_10c,uVar2 & 0xff,_Size);
    thunk_FUN_00404c3b(local_10c);
    local_8 = (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 2;
    local_c = (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) / 2;
    uVar3 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar3;
    iVar4 = (int)*(short *)(in_ECX + 0x1e);
    iVar5 = local_8;
    iVar6 = local_c;
    uVar3 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
    thunk_FUN_00404c5a(in_ECX + 8,uVar3,iVar4,iVar5,iVar6);
    thunk_FUN_0042d38a();
  }
  return;
}
```

---

## FUN_00429c46 — 0x429c46

- Classification : internal
- Corps : `0x429c46–0x429c4a`
- État : pseudocode obtenu
- Evidence : `ev_378c8a42f264b6b0cdf5571fe06650068f9e3979225c34c291c96646f45b24ca`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429c46(void)

{
  return;
}
```

---

## FUN_00429c4b — 0x429c4b

- Classification : internal
- Corps : `0x429c4b–0x429d5b`
- État : pseudocode obtenu
- Evidence : `ev_b04b7d1efd83a3e7d49ab7ce32bdae2bdc89bee29051ec02d0a1f76ab342b224`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401fa0` — `thunk_FUN_00429d5c`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472db0` — `FUN_00472db0`
- `0x476e20` — `_strncmp`

### Chaînes référencées

- `0x49de38` — "ENDTEXT"

### Pseudocode Ghidra

```c
undefined4 FUN_00429c4b(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_678 [780];
  char local_36c [100];
  int local_308;
  char local_304 [768];
  
  iVar1 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,39000);
  if (iVar1 == 0) {
    while( true ) {
      thunk_FUN_0040f5b3(local_36c,1);
      iVar1 = _strncmp(local_36c,s_ENDTEXT_0049de38,7);
      if (iVar1 == 0) break;
      local_308 = 0;
      local_678[0] = 0;
      while (local_308 == 0) {
        thunk_FUN_0040f5b3(local_304,1);
        iVar1 = _strncmp(local_304,&DAT_0049de40,3);
        if (iVar1 == 0) {
          local_308 = 1;
        }
        else {
          FUN_00472db0(local_678,local_304);
          FUN_00472db0(local_678,&DAT_0049de44);
        }
      }
      thunk_FUN_00429d5c(local_678,local_36c);
    }
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}
```

---

## FUN_00429d5c — 0x429d5c

- Classification : internal
- Corps : `0x429d5c–0x429e68`
- État : pseudocode obtenu
- Evidence : `ev_fe2d04de71105903ee26e44b7d85f686a4b05bf73a5a407f1e66a1fe0450cfef`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`

### Chaînes référencées

- `0x49de48` — "buffer != NULL"
- `0x49de58` — "C:\\float\\src\\gamewin.cpp"
- `0x49de74` — "sSharedTextLen + len < MAX_SHARED_TEXT"
- `0x49de9c` — "C:\\float\\src\\gamewin.cpp"
- `0x49deb8` — "FALSE"
- `0x49dec0` — "C:\\float\\src\\gamewin.cpp"

### Pseudocode Ghidra

```c
int FUN_00429d5c(char *param_1,int param_2)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (param_1 == (char *)0x0) {
    uVar4 = thunk_FUN_00414b64(s_C__float_src_gamewin_cpp_0049de58,0x1f8,s_buffer____NULL_0049de48);
  }
  else {
    uVar4 = 0;
  }
  sVar2 = _strlen(param_1);
  if ((int)(DAT_00597180 + sVar2) < 0x9800) {
    uVar3 = 0;
  }
  else {
    uVar3 = thunk_FUN_00414b64(s_C__float_src_gamewin_cpp_0049de9c,0x1fb,
                               s_sSharedTextLen___len_<_MAX_SHARE_0049de74);
  }
  FUN_00472da0(&DAT_0058d0b8 + DAT_00597180,param_1,uVar3,uVar4);
  iVar1 = DAT_00597180;
  DAT_00597180 = DAT_00597180 + 1 + sVar2;
  if (param_2 != 0) {
    if (DAT_00597184 < 0x200) {
      FUN_00472da0(&DAT_0058af48 + DAT_00597184 * 0x10,param_2,uVar3,uVar4);
      *(int *)(&DAT_005968b8 + DAT_00597184 * 4) = iVar1;
      DAT_00597184 = DAT_00597184 + 1;
    }
    else {
      thunk_FUN_00414b64(s_C__float_src_gamewin_cpp_0049dec0,0x20b,s_FALSE_0049deb8);
    }
  }
  return iVar1;
}
```

---

## FUN_00429e69 — 0x429e69

- Classification : internal
- Corps : `0x429e69–0x429ebd`
- État : pseudocode obtenu
- Evidence : `ev_8146606c6e3594474d1b0f6440df010441518d781cf58cfff88dab31f59f98d8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49dedc` — "index < sSharedTextLen"
- `0x49def4` — "C:\\float\\src\\gamewin.cpp"

### Pseudocode Ghidra

```c
undefined * FUN_00429e69(int param_1,int param_2)

{
  if (DAT_00597180 <= param_1) {
    thunk_FUN_00414b64(s_C__float_src_gamewin_cpp_0049def4,0x214,s_index_<_sSharedTextLen_0049dedc);
  }
  if (param_2 != 0) {
    param_1 = *(int *)(&DAT_005968b8 + param_1 * 4);
  }
  return &DAT_0058d0b8 + param_1;
}
```

---

## FUN_00429ebe — 0x429ebe

- Classification : internal
- Corps : `0x429ebe–0x429f39`
- État : pseudocode obtenu
- Evidence : `ev_8ff87772c7fe4f09c5d401d4704e629c1d1561f140695ffc53d21ec6a34fa1ef`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4774f0` — `_strcmp`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_00429ebe(char *param_1,int *param_2)

{
  int iVar1;
  int local_c;
  undefined *local_8;
  
  local_8 = (undefined *)0x0;
  local_c = 0;
  while ((local_c < DAT_00597184 &&
         (iVar1 = _strcmp(&DAT_0058af48 + local_c * 0x10,param_1), iVar1 != 0))) {
    local_c = local_c + 1;
  }
  if ((local_c < DAT_00597184) &&
     (local_8 = &DAT_0058d0b8 + *(int *)(&DAT_005968b8 + local_c * 4), param_2 != (int *)0x0)) {
    *param_2 = local_c;
  }
  return local_8;
}
```

---

## FUN_00429f3a — 0x429f3a

- Classification : internal
- Corps : `0x429f3a–0x429f57`
- État : pseudocode obtenu
- Evidence : `ev_109d1714fe261313365105194259bd329e5f517be169638fad23bf26a82067d8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_00429f3a(void)

{
  int in_ECX;
  
  return DAT_0062c6bc == *(int *)(in_ECX + 4);
}
```

---

## FUN_00429f58 — 0x429f58

- Classification : internal
- Corps : `0x429f58–0x429f64`
- État : pseudocode obtenu
- Evidence : `ev_b56f975fdc4def993467ceeaadf85c3fc89392cf4d621b55e84bd597bf27fa10`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429f58(void)

{
  return;
}
```

---

## FUN_00429f65 — 0x429f65

- Classification : internal
- Corps : `0x429f65–0x429fb8`
- État : pseudocode obtenu
- Evidence : `ev_a41c20a03d02c7e9dd51d60c5b5f4a792c8e9e20aa6ce4ffd579da42051e6590`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`
- `0x401d98` — `thunk_FUN_00429fd5`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00429f65(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491629;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494180;
  thunk_FUN_00429fd5();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_00429fb9 — 0x429fb9

- Classification : internal
- Corps : `0x429fb9–0x429fd4`
- État : pseudocode obtenu
- Evidence : `ev_a383139cb3aef2b0b9daab97e6ed8b8c60fb77d55fdf154f1eae094bdb4026d4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429fb9(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494180;
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_00429fd5 — 0x429fd5

- Classification : internal
- Corps : `0x429fd5–0x429fdf`
- État : pseudocode obtenu
- Evidence : `ev_a134a8e95b7713218f450212a00b7f91c59bb27522e2b612dfcb24d2b5c15074`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429fd5(void)

{
  return;
}
```

---

## FUN_00429fe0 — 0x429fe0

- Classification : internal
- Corps : `0x429fe0–0x42a00a`
- État : pseudocode obtenu
- Evidence : `ev_d06d8820a3e570b1124a0d71f15b9ddb3bc0f8e6f62b7bc631f4fabb826e283a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429fe0(short param_1,undefined4 param_2,undefined4 param_3)

{
  thunk_FUN_004293c6((int)param_1,param_2,param_3);
  return;
}
```

---

## FUN_0042a00b — 0x42a00b

- Classification : internal
- Corps : `0x42a00b–0x42a13a`
- État : pseudocode obtenu
- Evidence : `ev_d0001b947b137bf2112acf98a96c935796a52ba30e2a92940c6909af2484e647`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40146f` — `thunk_FUN_0042d87c`
- `0x40163b` — `thunk_FUN_00404c3b`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x402086` — `thunk_FUN_00404c5a`
- `0x402306` — `thunk_FUN_004106dd`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a00b(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int *in_ECX;
  int iVar3;
  int iVar4;
  
  if ((in_ECX[0xd] != 0) && (in_ECX[0xf] != 0)) {
    if (((in_ECX[1] == DAT_0062c6bc) || (in_ECX[0xd] == 2)) &&
       ((in_ECX[0x11] != 0 && (in_ECX[0xd] != 3)))) {
      (**(code **)(*in_ECX + 0xc))(param_1);
    }
    else if (*(short *)((int)in_ECX + 0x1e) != -1) {
      iVar1 = thunk_FUN_0042d28f();
      in_ECX[2] = iVar1;
      if (in_ECX[0xe] == 0) {
        uVar2 = thunk_FUN_004106dd(0,3);
        thunk_FUN_00404c3b(uVar2);
        iVar3 = (int)*(short *)((int)in_ECX + 0x6e);
        iVar1 = (int)(short)in_ECX[0x1b];
        iVar4 = (int)*(short *)((int)in_ECX + 0x1e);
        uVar2 = thunk_FUN_0040e864((short)in_ECX[7]);
        thunk_FUN_00404c5a(in_ECX + 2,uVar2,iVar4,iVar1,iVar3);
      }
      else {
        iVar3 = (int)*(short *)((int)in_ECX + 0x6e);
        iVar1 = (int)(short)in_ECX[0x1b];
        iVar4 = (int)*(short *)((int)in_ECX + 0x1e);
        uVar2 = thunk_FUN_0040e864((short)in_ECX[7]);
        thunk_FUN_00404770(in_ECX + 2,uVar2,iVar4,iVar1,iVar3);
      }
      thunk_FUN_0042d38a();
    }
    thunk_FUN_0042d87c(in_ECX + 2,3);
    in_ECX[0xd] = 0;
  }
  return;
}
```

---

## FUN_0042a13b — 0x42a13b

- Classification : internal
- Corps : `0x42a13b–0x42a1a0`
- État : pseudocode obtenu
- Evidence : `ev_ed62c20b500b2abbb8d262491e938b41baf89a207df8564c91cb21733513f68a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a13b(void)

{
  undefined4 uVar1;
  int iVar2;
  int in_ECX;
  int iVar3;
  int iVar4;
  
  if (*(short *)(in_ECX + 0x1e) != -1) {
    uVar1 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar1;
    iVar3 = (int)*(short *)(in_ECX + 0x6e);
    iVar2 = (int)*(short *)(in_ECX + 0x6c);
    iVar4 = *(short *)(in_ECX + 0x1e) + 1;
    uVar1 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
    thunk_FUN_00404770(in_ECX + 8,uVar1,iVar4,iVar2,iVar3);
    thunk_FUN_0042d38a();
  }
  return;
}
```

---

## FUN_0042a1a1 — 0x42a1a1

- Classification : internal
- Corps : `0x42a1a1–0x42a1f4`
- État : pseudocode obtenu
- Evidence : `ev_7d1ef468937acc07adb9a95965bb07699be717cc96b792380f6e572e957b1925`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40126c` — `thunk_FUN_0042a211`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0042a1a1(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049163c;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494198;
  thunk_FUN_0042a211();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_0042a1f5 — 0x42a1f5

- Classification : internal
- Corps : `0x42a1f5–0x42a210`
- État : pseudocode obtenu
- Evidence : `ev_c35c1b962906ad1fc18ce9ff11f25430db2317d9f7a73b61ad0486a04801745b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a1f5(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494198;
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_0042a211 — 0x42a211

- Classification : internal
- Corps : `0x42a211–0x42a22f`
- État : pseudocode obtenu
- Evidence : `ev_8e3814d4892ec761f27ac65ae2d6b2c5b92541003b733cbee2d89e7f5720b60e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a211(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x70) = 0;
  *(undefined4 *)(in_ECX + 0x74) = 0;
  return;
}
```

---

## FUN_0042a230 — 0x42a230

- Classification : internal
- Corps : `0x42a230–0x42a25a`
- État : pseudocode obtenu
- Evidence : `ev_d1a3a753121e33c2d45d6be3d8089a2db4cc4adf1954e66669ea637261d8e442`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a230(short param_1,undefined4 param_2,undefined4 param_3)

{
  thunk_FUN_004293c6((int)param_1,param_2,param_3);
  return;
}
```

---

## FUN_0042a25b — 0x42a25b

- Classification : internal
- Corps : `0x42a25b–0x42a27e`
- État : pseudocode obtenu
- Evidence : `ev_eaa3835e7259b33e3cb189b5d145ef68729480f0efad3c76576ae842451a6e6b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042a25b(void)

{
  int in_ECX;
  
  if (*(int *)(in_ECX + 0x70) != 0) {
    *(undefined4 *)(in_ECX + 0x74) = 0;
  }
  return *(undefined4 *)(in_ECX + 0x74);
}
```

---

## FUN_0042a27f — 0x42a27f

- Classification : internal
- Corps : `0x42a27f–0x42a3ca`
- État : pseudocode obtenu
- Evidence : `ev_c9510672eb7a91443b69d00f23f1deada8d18411a7fde9c3469905273dd228e8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40146f` — `thunk_FUN_0042d87c`
- `0x40163b` — `thunk_FUN_00404c3b`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x402086` — `thunk_FUN_00404c5a`
- `0x402306` — `thunk_FUN_004106dd`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a27f(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int *in_ECX;
  int iVar3;
  int local_8;
  
  if ((in_ECX[0xd] != 0) && (in_ECX[0xf] != 0)) {
    if (((in_ECX[1] == DAT_0062c6bc) || (in_ECX[0xd] == 2)) &&
       ((in_ECX[0x11] != 0 && (in_ECX[0xd] != 3)))) {
      (**(code **)(*in_ECX + 0xc))(param_1);
    }
    else if (*(short *)((int)in_ECX + 0x1e) != -1) {
      iVar1 = thunk_FUN_0042d28f();
      in_ECX[2] = iVar1;
      local_8 = (int)*(short *)((int)in_ECX + 0x1e);
      iVar1 = (**(code **)(*in_ECX + 0x14))();
      if (iVar1 != 0) {
        local_8 = local_8 + 2;
      }
      if (in_ECX[0xe] == 0) {
        uVar2 = thunk_FUN_004106dd(0,3);
        thunk_FUN_00404c3b(uVar2);
        iVar3 = (int)*(short *)((int)in_ECX + 0x6e);
        iVar1 = (int)(short)in_ECX[0x1b];
        uVar2 = thunk_FUN_0040e864(CONCAT22((short)in_ECX[0x1b] >> 0xf,(short)in_ECX[7]));
        thunk_FUN_00404c5a(in_ECX + 2,uVar2,local_8,iVar1,iVar3);
      }
      else {
        iVar1 = (int)*(short *)((int)in_ECX + 0x6e);
        iVar3 = (int)(short)in_ECX[0x1b];
        uVar2 = thunk_FUN_0040e864(CONCAT22((short)in_ECX[0x1b] >> 0xf,(short)in_ECX[7]));
        thunk_FUN_00404770(in_ECX + 2,uVar2,local_8,iVar3,iVar1);
      }
      thunk_FUN_0042d38a();
    }
    thunk_FUN_0042d87c(in_ECX + 2,3);
    in_ECX[0xd] = 0;
  }
  return;
}
```

---

## FUN_0042a3cb — 0x42a3cb

- Classification : internal
- Corps : `0x42a3cb–0x42a450`
- État : pseudocode obtenu
- Evidence : `ev_1583bc979d902b0ad2d4ff3484855b2d9432e1812f3779e7d0cb9bb42535c62a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a3cb(void)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  int *in_ECX;
  int iVar4;
  int local_8;
  
  if (*(short *)((int)in_ECX + 0x1e) != -1) {
    sVar1 = *(short *)((int)in_ECX + 0x1e);
    local_8 = sVar1 + 1;
    iVar2 = (**(code **)(*in_ECX + 0x14))();
    if (iVar2 != 0) {
      local_8 = sVar1 + 3;
    }
    iVar2 = thunk_FUN_0042d28f();
    in_ECX[2] = iVar2;
    iVar2 = (int)*(short *)((int)in_ECX + 0x6e);
    iVar4 = (int)(short)in_ECX[0x1b];
    uVar3 = thunk_FUN_0040e864(CONCAT22((short)in_ECX[0x1b] >> 0xf,(short)in_ECX[7]));
    thunk_FUN_00404770(in_ECX + 2,uVar3,local_8,iVar4,iVar2);
    thunk_FUN_0042d38a();
  }
  return;
}
```

---


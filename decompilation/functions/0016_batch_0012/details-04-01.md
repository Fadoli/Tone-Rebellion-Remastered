# 0016_batch_0012 — détails (1/3)

## FUN_0045a645 — 0x45a645

- Classification : internal
- Corps : `0x45a645–0x45aafc`
- État : pseudocode obtenu
- Evidence : `ev_572101b2259c5421e042ff5002804b43e2fc401410afff626a17946449ee8945`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401875` — `thunk_FUN_0040fc15`
- `0x401b9f` — `thunk_FUN_0040fa7f`
- `0x401f00` — `thunk_FUN_0045ab46`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fc8` — `thunk_FUN_0045c290`
- `0x40205e` — `thunk_FUN_0040fac8`

### Chaînes référencées

- `0x4a3a88` — "r==DS_OK"
- `0x4a3a94` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3ab0` — "r==DS_OK"
- `0x4a3abc` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3ad8` — "status==read_size"
- `0x4a3aec` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3b08` — "status==mMusicDataOffset"
- `0x4a3b24` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3b40` — "status==(int)(AudioBytes1-bytes_already)"
- `0x4a3b6c` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3b88` — "status==read_size"
- `0x4a3b9c` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3bb8` — "status==mMusicDataOffset"
- `0x4a3bd4` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3bf0` — "status==(int)(AudioBytes2-bytes_already)"
- `0x4a3c1c` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3c38` — "r==DS_OK"
- `0x4a3c44` — "C:\\float\\src\\soundsys.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0045a645(void)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  uint local_30;
  undefined1 local_28 [4];
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar1 = thunk_FUN_0045c290();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    local_c = (**(code **)(*DAT_005e8228 + 0x10))(DAT_005e8228,&local_18,local_28);
    if (local_c != 0) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3a94,0x274,s_r__DS_OK_004a3a88);
    }
    if (*(int *)(in_ECX + 0x2090) < local_18) {
      local_30 = (local_18 - *(int *)(in_ECX + 0x2090)) - 1;
    }
    else {
      local_30 = (0xc7ff - *(int *)(in_ECX + 0x2090)) + local_18;
    }
    if (0x1400 < (int)local_30) {
      local_30 = 0x1400;
    }
    if ((int)local_30 < 0x800) {
      uVar2 = 0;
    }
    else {
      local_c = (**(code **)(*DAT_005e8228 + 0x2c))
                          (DAT_005e8228,*(undefined4 *)(in_ECX + 0x2090),local_30 & 0xfffffffe,
                           &local_10,&local_1c,&local_8,&local_14,0);
      if (local_c != 0) {
        thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3abc,0x295,s_r__DS_OK_004a3ab0);
      }
      local_20 = local_1c;
      iVar1 = thunk_FUN_0040fa7f();
      if (*(int *)(in_ECX + 0x2094) + *(int *)(in_ECX + 0x2098) < iVar1 + local_1c) {
        local_20 = (*(int *)(in_ECX + 0x2094) + *(int *)(in_ECX + 0x2098)) - iVar1;
      }
      local_24 = thunk_FUN_0040fc15(local_10,local_20);
      if (local_24 != local_20) {
        thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3aec,0x2a7,s_status__read_size_004a3ad8);
      }
      iVar1 = local_24;
      *(int *)(in_ECX + 0x2090) = *(int *)(in_ECX + 0x2090) + local_24;
      if (local_20 < local_1c) {
        local_24 = thunk_FUN_0040fac8(*(undefined4 *)(in_ECX + 0x2094));
        if (local_24 != *(int *)(in_ECX + 0x2094)) {
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3b24,0x2b0,
                             s_status__mMusicDataOffset_004a3b08);
        }
        if (*(int *)(in_ECX + 0x20f8) == 0) {
          thunk_FUN_0045ab46();
        }
        else {
          local_24 = thunk_FUN_0040fc15(local_10 + iVar1,local_1c - iVar1);
          if (local_24 != local_1c - iVar1) {
            thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3b6c,699,
                               s_status___int__AudioBytes1_bytes__004a3b40);
          }
          *(int *)(in_ECX + 0x2090) = *(int *)(in_ECX + 0x2090) + local_24;
        }
      }
      if ((local_14 != 0) && (*(int *)(in_ECX + 0x2100) == 0)) {
        local_20 = local_14;
        iVar1 = thunk_FUN_0040fa7f();
        if (*(int *)(in_ECX + 0x2094) + *(int *)(in_ECX + 0x2098) < iVar1 + local_14) {
          local_20 = (*(int *)(in_ECX + 0x2094) + *(int *)(in_ECX + 0x2098)) - iVar1;
        }
        local_24 = thunk_FUN_0040fc15(local_8,local_20);
        if (local_24 != local_20) {
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3b9c,0x2ca,s_status__read_size_004a3b88
                            );
        }
        iVar1 = local_20;
        *(int *)(in_ECX + 0x2090) = *(int *)(in_ECX + 0x2090) + local_24;
        if (local_20 < local_14) {
          local_24 = thunk_FUN_0040fac8(*(undefined4 *)(in_ECX + 0x2094));
          if (local_24 != *(int *)(in_ECX + 0x2094)) {
            thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3bd4,0x2d3,
                               s_status__mMusicDataOffset_004a3bb8);
          }
          if (*(int *)(in_ECX + 0x20f8) == 0) {
            thunk_FUN_0045ab46();
          }
          else {
            local_24 = thunk_FUN_0040fc15(local_8 + iVar1,local_14 - iVar1);
            if (local_24 != local_14 - iVar1) {
              thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3c1c,0x2de,
                                 s_status___int__AudioBytes2_bytes__004a3bf0);
            }
            *(int *)(in_ECX + 0x2090) = *(int *)(in_ECX + 0x2090) + local_24;
          }
        }
      }
      if (0xc7ff < *(int *)(in_ECX + 0x2090)) {
        *(int *)(in_ECX + 0x2090) = *(int *)(in_ECX + 0x2090) + -0xc800;
      }
      local_c = (**(code **)(*DAT_005e8228 + 0x4c))(DAT_005e8228,local_10,local_1c,local_8,local_14)
      ;
      if (local_c != 0) {
        thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3c44,0x2ea,s_r__DS_OK_004a3c38);
      }
      uVar2 = 1;
    }
  }
  return uVar2;
}
```

---

---

## FUN_0045aafd — 0x45aafd

- Classification : internal
- Corps : `0x45aafd–0x45ab45`
- État : pseudocode obtenu
- Evidence : `ev_595ab9eab1441664900d5f6aff127ef24f4f721457e188f9c901095ea277aa46`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40245a` — `thunk_FUN_0045b8ac`
- `0x472da0` — `FUN_00472da0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045aafd(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int in_ECX;
  
  FUN_00472da0(in_ECX + 0x2108,param_1);
  *(undefined4 *)(in_ECX + 0x2158) = param_2;
  *(undefined4 *)(in_ECX + 0x215c) = param_3;
  if (param_4 == 0) {
    thunk_FUN_0045b8ac();
  }
  return;
}
```

---

---

## FUN_0045ab46 — 0x45ab46

- Classification : internal
- Corps : `0x45ab46–0x45aba8`
- État : pseudocode obtenu
- Evidence : `ev_e97630faf08f87aa055819b1826ce5ab7ff380c7ab26cdfe8c5b80fb3ee77a0e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40150f` — `thunk_FUN_0046ff6f`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x40245a` — `thunk_FUN_0045b8ac`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045ab46(void)

{
  int in_ECX;
  
  if (*(char *)(in_ECX + 0x2108) == '\0') {
    thunk_FUN_0046ff6f(1);
  }
  if (*(char *)(in_ECX + 0x2108) == '\0') {
    if (DAT_005e8228 != (int *)0x0) {
      (**(code **)(*DAT_005e8228 + 0x48))(DAT_005e8228);
    }
    thunk_FUN_0040f966();
  }
  else {
    thunk_FUN_0045b8ac();
  }
  return;
}
```

---

---

## FUN_0045aba9 — 0x45aba9

- Classification : internal
- Corps : `0x45aba9–0x45ae6c`
- État : pseudocode obtenu
- Evidence : `ev_d0d4e6a0547fbb383acba83a99791569aa95465a242d2b8b2e224bbf3eb01af8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a91` — `thunk_FUN_0045a645`
- `0x401aff` — `thunk_FUN_0045aeba`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fc8` — `thunk_FUN_0045c290`
- `0x40205e` — `thunk_FUN_0040fac8`
- `0x472ca0` — `FUN_00472ca0`
- `0x472da0` — `FUN_00472da0`
- `0x4734a0` — `FUN_004734a0`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x4a3c68` — "status==0"
- `0x4a3c74` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3c90` — "r==DS_OK"
- `0x4a3c9c` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3cb8` — "r==DS_OK"
- `0x4a3cc4` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3ce0` — "r==DS_OK"
- `0x4a3cec` — "C:\\float\\src\\soundsys.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0045aba9(char *param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  int in_ECX;
  short local_68;
  char local_5c [80];
  int local_c;
  undefined4 local_8;
  
  if ((DAT_005ea39c == 0) || (DAT_005e8228 == (int *)0x0)) {
    uVar1 = 0;
  }
  else {
    local_5c[0] = '\0';
    thunk_FUN_0045aeba(*(undefined4 *)(in_ECX + 0x209c));
    if (DAT_004c2ba8 != 0) {
      iVar2 = thunk_FUN_0045c290();
      if (iVar2 != 0) {
        return 1;
      }
      param_1 = &DAT_004c2ab8;
      param_2 = 0;
      param_3 = 1;
    }
    if (param_2 == 0) {
      local_68 = 0;
      while (((int)local_68 < *(int *)(in_ECX + 0x1f80) &&
             (iVar2 = __strcmpi(param_1,(char *)(in_ECX + local_68 * 0x48)), iVar2 != 0))) {
        local_68 = local_68 + 1;
      }
      if ((int)local_68 < *(int *)(in_ECX + 0x1f80)) {
        FUN_00472da0(local_5c,in_ECX + 0xc + local_68 * 0x48);
        *(short *)(in_ECX + 0x20fc) = local_68;
      }
    }
    else {
      FUN_00472ca0(local_5c,&DAT_004a3c60,in_ECX + 0x20a4,param_1);
    }
    if (local_5c[0] == '\0') {
      uVar1 = 0;
    }
    else {
      thunk_FUN_0040f966();
      iVar2 = thunk_FUN_0040f752(local_5c,0x8000);
      if (iVar2 != 0) {
        thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3c74,0x34e,s_status__0_004a3c68);
      }
      iVar2 = in_ECX + *(short *)(in_ECX + 0x20fc) * 0x48;
      FUN_004734a0(&DAT_005ea460,iVar2 + 0x34,0x12);
      *(undefined4 *)(in_ECX + 0x2094) = *(undefined4 *)(iVar2 + 0x2c);
      *(undefined4 *)(in_ECX + 0x2098) = *(undefined4 *)(iVar2 + 0x30);
      local_c = (**(code **)(*DAT_005e8228 + 0x48))(DAT_005e8228);
      if (local_c != 0) {
        thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3c9c,0x35a,s_r__DS_OK_004a3c90);
      }
      (**(code **)(*DAT_005e8228 + 0x34))(DAT_005e8228,0);
      if (local_c != 0) {
        thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3cc4,0x35c,s_r__DS_OK_004a3cb8);
      }
      *(undefined4 *)(in_ECX + 0x2090) = 0;
      thunk_FUN_0040fac8(*(undefined4 *)(in_ECX + 0x2094));
      thunk_FUN_0045a645();
      local_8 = 0;
      *(undefined4 *)(in_ECX + 0x20f8) = param_3;
      local_c = (**(code **)(*DAT_005e8228 + 0x30))(DAT_005e8228,0,0,1);
      if (local_c != 0) {
        thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3cec,0x36b,s_r__DS_OK_004a3ce0);
      }
      uVar1 = 1;
    }
  }
  return uVar1;
}
```

---

---

## FUN_0045ae6d — 0x45ae6d

- Classification : internal
- Corps : `0x45ae6d–0x45aeb9`
- État : pseudocode obtenu
- Evidence : `ev_4c2a0675d9b5eb9fa96328b918a7fb1ecf97050eebfbdbbc6584725bf3054198`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a3d08` — "volume<=0 && volume >= -10000"
- `0x4a3d28` — "C:\\float\\src\\soundsys.cpp"

### Pseudocode Ghidra

```c
void FUN_0045ae6d(int param_1)

{
  int in_ECX;
  
  if ((0 < param_1) || (param_1 < -10000)) {
    thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3d28,0x374,
                       s_volume<_0_&&_volume_>___10000_004a3d08);
  }
  *(int *)(in_ECX + 0x20a0) = param_1;
  return;
}
```

---

---

## FUN_0045aeba — 0x45aeba

- Classification : internal
- Corps : `0x45aeba–0x45af2a`
- État : pseudocode obtenu
- Evidence : `ev_79acfef7fd2073edd23b322478455cd609f278361b632fba1df1d39e595543a0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a3d44` — "volume<=0 && volume >= -10000"
- `0x4a3d64` — "C:\\float\\src\\soundsys.cpp"

### Pseudocode Ghidra

```c
void FUN_0045aeba(int param_1)

{
  int in_ECX;
  undefined4 uVar1;
  
  if ((param_1 < 1) && (-0x2711 < param_1)) {
    uVar1 = 0;
  }
  else {
    uVar1 = thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3d64,0x37c,
                               s_volume<_0_&&_volume_>___10000_004a3d44);
  }
  *(int *)(in_ECX + 0x209c) = param_1;
  if (DAT_005e8228 != (int *)0x0) {
    (**(code **)(*DAT_005e8228 + 0x3c))(DAT_005e8228,*(undefined4 *)(in_ECX + 0x209c),uVar1);
  }
  return;
}
```

---

---

## FUN_0045af2b — 0x45af2b

- Classification : internal
- Corps : `0x45af2b–0x45af54`
- État : pseudocode obtenu
- Evidence : `ev_414062535917300e62c3352eb2c18a2072a1f084e3fb13d6fce9fd7d89fa960d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021f8` — `thunk_FUN_004595cc`
- `0x4023b5` — `thunk_FUN_0045ae6d`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045af2b(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = thunk_FUN_004595cc(param_1);
  thunk_FUN_0045ae6d(uVar1);
  return;
}
```

---

---

## FUN_0045af55 — 0x45af55

- Classification : internal
- Corps : `0x45af55–0x45af7e`
- État : pseudocode obtenu
- Evidence : `ev_aeca0bf48682b416e7b4bbf92187f003c195332cd8212c5807aa6a1950543cac`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401aff` — `thunk_FUN_0045aeba`
- `0x4021f8` — `thunk_FUN_004595cc`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045af55(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = thunk_FUN_004595cc(param_1);
  thunk_FUN_0045aeba(uVar1);
  return;
}
```

---

---

## FUN_0045af7f — 0x45af7f

- Classification : internal
- Corps : `0x45af7f–0x45af9b`
- État : pseudocode obtenu
- Evidence : `ev_c8d81f66fc1b703109333ad7f0d0191ba466bd59fa5c66fa7e7b7dec3eac8c9d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4022f2` — `thunk_FUN_00459653`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045af7f(void)

{
  int in_ECX;
  
  thunk_FUN_00459653(*(undefined4 *)(in_ECX + 0x20a0));
  return;
}
```

---

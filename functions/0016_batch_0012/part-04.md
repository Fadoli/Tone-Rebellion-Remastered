# 0016_batch_0012 — détails (4/6)

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

## FUN_0045af9c — 0x45af9c

- Classification : internal
- Corps : `0x45af9c–0x45afb8`
- État : pseudocode obtenu
- Evidence : `ev_71dc5f1d59fbccfff477b60c4aeb664de36fb7170091b837ab15cb60ce2a1200`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4022f2` — `thunk_FUN_00459653`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045af9c(void)

{
  int in_ECX;
  
  thunk_FUN_00459653(*(undefined4 *)(in_ECX + 0x209c));
  return;
}
```

---

## FUN_0045afb9 — 0x45afb9

- Classification : internal
- Corps : `0x45afb9–0x45b20b`
- État : pseudocode obtenu
- Evidence : `ev_cacde6bdfaea3706f5ef075e8eeae74485d3e0fe485155a7c4caa8187b06f79a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x4021f8` — `thunk_FUN_004595cc`
- `0x402225` — `thunk_FUN_0045b3a7`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x4022f2` — `thunk_FUN_00459653`
- `0x472c6c` — `__ftol`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x4a3d80` — "Failed loadEffect for %s."
- `0x4a3d9c` — "levdeath"
- `0x4a3da8` — "fltdeath"
- `0x4a3db4` — "result==DS_OK"
- `0x4a3dc4` — "C:\\float\\src\\soundsys.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0045afb9(short param_1,int param_2,int param_3)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int in_ECX;
  uint local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if ((DAT_005ea39c == 0) || (DAT_005ea478 == 0)) {
    uVar2 = 0;
  }
  else {
    sVar1 = thunk_FUN_0045b3a7(param_1);
    local_c = (int)sVar1;
    if (local_c < 0) {
      thunk_FUN_00414ad0(s_Failed_loadEffect_for__s__004a3d80,in_ECX + param_1 * 0x48);
      uVar2 = 0;
    }
    else {
      if (((DAT_004c2bc8 != 0) &&
          (iVar3 = __strcmpi((char *)(in_ECX + param_1 * 0x48),s_levdeath_004a3d9c), iVar3 != 0)) &&
         (iVar3 = __strcmpi((char *)(in_ECX + param_1 * 0x48),s_fltdeath_004a3da8), iVar3 != 0)) {
        local_10 = (**(code **)(*(int *)(&DAT_005ea478)[local_c] + 0x24))
                             ((&DAT_005ea478)[local_c],&local_14);
        if (local_10 != 0) {
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3dc4,0x3bb,s_result__DS_OK_004a3db4);
        }
        if ((local_14 & 1) != 0) {
          return 1;
        }
      }
      local_8 = *(undefined4 *)(in_ECX + 0x20a0);
      if (param_2 != 100) {
        thunk_FUN_00459653(*(undefined4 *)(in_ECX + 0x20a0));
        local_8 = __ftol();
        if (local_8 < 0) {
          local_8 = 0;
        }
        if (100 < local_8) {
          local_8 = 100;
        }
        local_8 = thunk_FUN_004595cc(local_8);
      }
      if (param_3 < -10000) {
        param_3 = -10000;
      }
      if (10000 < param_3) {
        param_3 = 10000;
      }
      (**(code **)(*(int *)(&DAT_005ea478)[local_c] + 0x48))((&DAT_005ea478)[local_c]);
      (**(code **)(*(int *)(&DAT_005ea478)[local_c] + 0x34))((&DAT_005ea478)[local_c],0);
      (**(code **)(*(int *)(&DAT_005ea478)[local_c] + 0x40))((&DAT_005ea478)[local_c],param_3);
      (**(code **)(*(int *)(&DAT_005ea478)[local_c] + 0x3c))((&DAT_005ea478)[local_c],local_8);
      (**(code **)(*(int *)(&DAT_005ea478)[local_c] + 0x30))((&DAT_005ea478)[local_c],0,0,0);
      *(undefined4 *)(&DAT_005ea3a8 + local_c * 0xc) = *(undefined4 *)(in_ECX + 0x2168);
      uVar2 = 1;
    }
  }
  return uVar2;
}
```

---

## FUN_0045b20c — 0x45b20c

- Classification : internal
- Corps : `0x45b20c–0x45b24c`
- État : pseudocode obtenu
- Evidence : `ev_4a07b6b9bbfd2053b7611e6f03801b1aae3277b058e5b4e908de4913c4acdedd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401aaf` — `thunk_FUN_0045afb9`
- `0x401c76` — `thunk_FUN_0045b34c`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045b20c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  short sVar1;
  undefined4 uVar2;
  
  sVar1 = thunk_FUN_0045b34c(param_1);
  if (sVar1 == -1) {
    uVar2 = 0;
  }
  else {
    uVar2 = thunk_FUN_0045afb9((int)sVar1,param_2,param_3);
  }
  return uVar2;
}
```

---

## FUN_0045b24d — 0x45b24d

- Classification : internal
- Corps : `0x45b24d–0x45b34b`
- État : pseudocode obtenu
- Evidence : `ev_5331ef854ee3d9d6695246fa1a740200a69ada40159809488867e4e049e1a00f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021f8` — `thunk_FUN_004595cc`
- `0x472c6c` — `__ftol`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045b24d(int param_1,int param_2,undefined4 *param_3,int *param_4)

{
  undefined4 uVar1;
  int local_14;
  
  uVar1 = __ftol();
  local_14 = thunk_FUN_004595cc(uVar1);
  if (param_2 - param_1 < 0) {
    local_14 = -local_14;
  }
  if (param_4 != (int *)0x0) {
    *param_4 = local_14;
  }
  if (param_3 != (undefined4 *)0x0) {
    uVar1 = __ftol();
    *param_3 = uVar1;
  }
  return 1;
}
```

---

## FUN_0045b34c — 0x45b34c

- Classification : internal
- Corps : `0x45b34c–0x45b3a6`
- État : pseudocode obtenu
- Evidence : `ev_75f45f3af3e34b397268d635ba31b0420a58078beef979215b6e69040004a4e0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x48b100` — `__strcmpi`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
short FUN_0045b34c(char *param_1)

{
  int iVar1;
  int in_ECX;
  short local_8;
  
  local_8 = 0;
  while( true ) {
    if (*(int *)(in_ECX + 0x1f80) <= (int)local_8) {
      return -1;
    }
    iVar1 = __strcmpi(param_1,(char *)(in_ECX + local_8 * 0x48));
    if (iVar1 == 0) break;
    local_8 = local_8 + 1;
  }
  return local_8;
}
```

---

## FUN_0045b3a7 — 0x45b3a7

- Classification : internal
- Corps : `0x45b3a7–0x45b8ab`
- État : pseudocode obtenu
- Evidence : `ev_ea0d4fab064f8d499c6218aa34eb68b189f30177901eab66c733584fbb3393e4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x40205e` — `thunk_FUN_0040fac8`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a3de0` — "result==DS_OK"
- `0x4a3df0` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3e0c` — "!(status&DSBSTATUS_BUFFERLOST)"
- `0x4a3e2c` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3e48` — "success==0"
- `0x4a3e54` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3e70` — "result==DS_OK"
- `0x4a3e80` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3e9c` — "(Dword)bytes1>pitem->dataLen"
- `0x4a3ebc` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3ed8` — "bytes2==0"
- `0x4a3ee4` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3f00` — "audio1"
- `0x4a3f08` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3f24` — "bytesread==pitem->dataLen"
- `0x4a3f40` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3f5c` — "result==DS_OK"
- `0x4a3f6c` — "C:\\float\\src\\soundsys.cpp"

### Pseudocode Ghidra

```c
uint FUN_0045b3a7(short param_1)

{
  uint uVar1;
  int iVar2;
  int in_ECX;
  undefined4 *unaff_FS_OFFSET;
  int local_150;
  int local_148;
  uint local_144;
  int local_140;
  int local_13c;
  uint local_2c;
  undefined4 local_28;
  uint local_24;
  uint local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491ba6;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_20 = 0xffffffff;
  local_150 = 99999;
  if (param_1 < 0) {
    local_2c = 0xffff;
  }
  else {
    local_13c = in_ECX + param_1 * 0x48;
    for (local_2c = 0;
        ((int)local_2c < DAT_005ea4b8 && (*(int *)(&DAT_005ea3a0 + local_2c * 0xc) != (int)param_1))
        ; local_2c = local_2c + 1) {
      if ((*(int *)(&DAT_005ea3a0 + local_2c * 0xc) == -1) &&
         ((*(int *)(local_13c + 0x30) <= (int)(&DAT_005ea3a4)[local_2c * 3] &&
          ((int)(&DAT_005ea3a4)[local_2c * 3] < local_150)))) {
        local_20 = local_2c;
        local_150 = (&DAT_005ea3a4)[local_2c * 3];
      }
    }
    if ((int)local_2c < DAT_005ea4b8) {
      local_2c = local_2c & 0xffff;
    }
    else {
      if (local_20 == 0xffffffff) {
        for (local_2c = 0; (int)local_2c < DAT_005ea4b8; local_2c = local_2c + 1) {
          if (*(int *)(local_13c + 0x30) <= (int)(&DAT_005ea3a4)[local_2c * 3]) {
            local_18 = (**(code **)(*(int *)(&DAT_005ea478)[local_2c] + 0x24))
                                 ((&DAT_005ea478)[local_2c],&local_144);
            if (local_18 != 0) {
              thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3df0,0x453,s_result__DS_OK_004a3de0
                                );
            }
            if ((local_144 & 2) != 0) {
              thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3e2c,0x454,
                                 s___status_DSBSTATUS_BUFFERLOST__004a3e0c);
            }
            if (local_144 == 0) {
              if ((int)(&DAT_005ea3a4)[local_2c * 3] < local_150) {
                local_20 = local_2c;
                local_150 = (&DAT_005ea3a4)[local_2c * 3];
                local_24 = *(uint *)(&DAT_005ea3a8 + local_2c * 0xc);
              }
              else if (((&DAT_005ea3a4)[local_2c * 3] == local_150) &&
                      (*(uint *)(&DAT_005ea3a8 + local_2c * 0xc) < local_24)) {
                local_20 = local_2c;
                local_24 = *(uint *)(&DAT_005ea3a8 + local_2c * 0xc);
              }
            }
          }
        }
      }
      if (local_20 == 0xffffffff) {
        local_2c = 0xffff;
      }
      else {
        thunk_FUN_0040f6f7();
        local_8 = 0;
        iVar2 = thunk_FUN_0040f752(local_13c + 0xc,0x8000);
        if (iVar2 != 0) {
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3e54,0x475,s_success__0_004a3e48);
        }
        thunk_FUN_0040fac8(*(undefined4 *)(local_13c + 0x2c));
        local_18 = (**(code **)(*(int *)(&DAT_005ea478)[local_20] + 0x2c))
                             ((&DAT_005ea478)[local_20],0,(&DAT_005ea3a4)[local_20 * 3],&local_140,
                              &local_148,&local_28,&local_1c,0);
        if (local_18 != 0) {
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3e80,0x47d,s_result__DS_OK_004a3e70);
        }
        if (local_148 <= *(int *)(local_13c + 0x30)) {
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3ebc,0x47e,
                             s__Dword_bytes1>pitem_>dataLen_004a3e9c);
        }
        if (local_1c != 0) {
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3ee4,0x47f,s_bytes2__0_004a3ed8);
        }
        if (local_140 == 0) {
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3f08,0x480,s_audio1_004a3f00);
        }
        local_14 = thunk_FUN_0040fc15(local_140,*(undefined4 *)(local_13c + 0x30));
        if (local_14 != *(int *)(local_13c + 0x30)) {
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3f40,0x484,
                             s_bytesread__pitem_>dataLen_004a3f24);
        }
        _memset((void *)(local_140 + *(int *)(local_13c + 0x30)),0x80,
                local_148 - *(int *)(local_13c + 0x30));
        local_18 = (**(code **)(*(int *)(&DAT_005ea478)[local_20] + 0x4c))
                             ((&DAT_005ea478)[local_20],local_140,local_148,local_28,0);
        if (local_18 != 0) {
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3f6c,0x489,s_result__DS_OK_004a3f5c);
        }
        uVar1 = local_20;
        *(int *)(&DAT_005ea3a0 + local_20 * 0xc) = (int)param_1;
        local_8 = 0xffffffff;
        thunk_FUN_0040f73f();
        local_2c = uVar1 & 0xffff;
      }
    }
  }
  *unaff_FS_OFFSET = local_10;
  return local_2c;
}
```

---

## FUN_0045b8ac — 0x45b8ac

- Classification : internal
- Corps : `0x45b8ac–0x45b8d0`
- État : pseudocode obtenu
- Evidence : `ev_11a57ee769f0ef36bfcb4aaa07ff86baf51d5fd4fa4ca9c8295e87fdab06a77c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045b8ac(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x2164) = 0;
  *(undefined4 *)(in_ECX + 0x2160) = 1;
  return;
}
```

---

## FUN_0045b8d1 — 0x45b8d1

- Classification : internal
- Corps : `0x45b8d1–0x45b92a`
- État : pseudocode obtenu
- Evidence : `ev_8b91a9064fd30621891ef79fa91a2ec10802f31500143e92571c0dd11eedb1a6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x48b100` — `__strcmpi`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_0045b8d1(char *param_1)

{
  int in_ECX;
  int iVar1;
  bool bVar2;
  
  iVar1 = (int)*(short *)(in_ECX + 0x20fc);
  bVar2 = false;
  if ((-1 < iVar1) && (iVar1 < *(int *)(in_ECX + 0x1f80))) {
    iVar1 = __strcmpi(param_1,(char *)(in_ECX + iVar1 * 0x48));
    bVar2 = iVar1 == 0;
  }
  return bVar2;
}
```

---

## FUN_0045c290 — 0x45c290

- Classification : internal
- Corps : `0x45c290–0x45c2a7`
- État : pseudocode obtenu
- Evidence : `ev_e52e39df1204587fd54025850d1cb66744a508ddf8a898e420cf61b1a7f92d04`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_0045c290(void)

{
  int *in_ECX;
  
  return *in_ECX != -1;
}
```

---

## FUN_0045c2b0 — 0x45c2b0

- Classification : internal
- Corps : `0x45c2b0–0x45c2c5`
- État : pseudocode obtenu
- Evidence : `ev_5bfd043957029c932ae1e0f070a072311854a39f81b5280532c9ea6de854e2cf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40164a` — `thunk_FUN_0045c2d1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045c2b0(void)

{
  undefined4 in_ECX;
  
  thunk_FUN_0045c2d1();
  return in_ECX;
}
```

---

## FUN_0045c2c6 — 0x45c2c6

- Classification : internal
- Corps : `0x45c2c6–0x45c2d0`
- État : pseudocode obtenu
- Evidence : `ev_f4d0afcc43d8b4b2141ce634e7d513a6b615243d6821fdf0c80dc567b92332a2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045c2c6(void)

{
  return;
}
```

---

## FUN_0045c2d1 — 0x45c2d1

- Classification : internal
- Corps : `0x45c2d1–0x45c324`
- État : pseudocode obtenu
- Evidence : `ev_533c5b6707e514ad4be641dfbdc950a75ba7774eddea733cae6b8006e2845412`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045c2d1(void)

{
  undefined2 *in_ECX;
  short local_8;
  
  *in_ECX = 0xffff;
  in_ECX[1] = 0xffff;
  for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
    in_ECX[local_8 + 2] = 0xffff;
  }
  in_ECX[0x12] = 0;
  return;
}
```

---

## FUN_0045c325 — 0x45c325

- Classification : internal
- Corps : `0x45c325–0x45c3ba`
- État : pseudocode obtenu
- Evidence : `ev_266125dff766e2414135d1bcf74f13d513d1765005373355b2190e74ae733d16`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a42e3` — "\ntribe>=int(FT_Protector) && tribe<=int(FT_Lifegiver)"
- `0x4a431c` — "C:\\float\\src\\staffbld.cpp"

### Pseudocode Ghidra

```c
int FUN_0045c325(void)

{
  int iVar1;
  short *in_ECX;
  
  if ((*in_ECX == -1) || (in_ECX[1] == -1)) {
    iVar1 = 0xffff;
  }
  else {
    iVar1 = *(int *)(&DAT_005ec654 + in_ECX[1] * 0x60 + *in_ECX * 0x29e8);
    if ((iVar1 < 0) || (3 < iVar1)) {
      thunk_FUN_00414b64(s_C__float_src_staffbld_cpp_004a431c,0x9b,
                         s_tribe>_int_FT_Protector_____trib_004a42e3 + 1);
    }
    iVar1 = ((int)in_ECX - (int)(&DAT_006192b0 + iVar1 * 0x14a0)) / 100;
  }
  return iVar1;
}
```

---

## FUN_0045c3bb — 0x45c3bb

- Classification : internal
- Corps : `0x45c3bb–0x45c3fd`
- État : pseudocode obtenu
- Evidence : `ev_0f1bf5caca4a6c5c244c4a2b8bee6e591fc8367f9b451a0694329a19e3378011`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_0045c3bb(void)

{
  undefined *puVar1;
  short *in_ECX;
  
  if ((*in_ECX == -1) || (in_ECX[1] == -1)) {
    puVar1 = (undefined *)0x0;
  }
  else {
    puVar1 = &DAT_005ec640 + in_ECX[1] * 0x60 + *in_ECX * 0x29e8;
  }
  return puVar1;
}
```

---


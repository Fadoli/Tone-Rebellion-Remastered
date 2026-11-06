# 0017_batch_0013 — détails (2/3)

## FUN_004633a7 — 0x4633a7

- Classification : internal
- Corps : `0x4633a7–0x463562`
- État : pseudocode obtenu
- Evidence : `ev_44c306a9b382d851e58738b7b6eb24f80860af4d1dc3dfb2fe923b92a03de1e0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40149c` — `thunk_FUN_00414bc2`
- `0x401730` — `thunk_FUN_004557bc`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472f10` — `FUN_00472f10`

### Chaînes référencées

- `0x4a4e44` — "status == 0"
- `0x4a4e50` — "C:\\float\\src\\tworld.cpp"
- `0x4a4e68` — "%s %d %d %d %d %d %d"
- `0x4a4e80` — "vals == 7"
- `0x4a4e8c` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
void FUN_004633a7(undefined4 param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 local_a8 [2];
  undefined2 local_a4 [8];
  undefined2 local_94 [2];
  int local_90;
  undefined2 local_8c [2];
  undefined2 local_88 [2];
  undefined2 local_84 [2];
  undefined1 local_80 [24];
  undefined1 local_68 [100];
  
  iVar2 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,20000);
  if (iVar2 != 0) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4e50,0x35d,s_status____0_004a4e44);
  }
  for (local_90 = 0; local_90 < 0x2d; local_90 = local_90 + 1) {
    thunk_FUN_0040f5b3(local_68,0);
    iVar2 = FUN_00472f10(local_68,s__s__d__d__d__d__d__d_004a4e68,local_80,local_84,local_88,
                         local_8c,local_94,local_a4,local_a8);
    if (iVar2 != 7) {
      thunk_FUN_00414bc2(s_C__float_src_tworld_cpp_004a4e8c,0x368,s_vals____7_004a4e80,local_90);
    }
    uVar1 = thunk_FUN_004557bc(local_80);
    *(undefined2 *)(&DAT_005ebfa4 + local_90 * 0xe) = uVar1;
    *(undefined2 *)(&DAT_005ebfa0 + local_90 * 0xe) = local_84[0];
    *(undefined2 *)(&DAT_005ebfa2 + local_90 * 0xe) = local_88[0];
    *(undefined2 *)(&DAT_005ebfa6 + local_90 * 0xe) = local_8c[0];
    *(undefined2 *)(&DAT_005ebfa8 + local_90 * 0xe) = local_94[0];
    *(undefined2 *)(&DAT_005ebfaa + local_90 * 0xe) = local_a4[0];
    *(undefined2 *)(&DAT_005ebfac + local_90 * 0xe) = local_a8[0];
  }
  return;
}
```

---

---

## FUN_00463563 — 0x463563

- Classification : internal
- Corps : `0x463563–0x4637fb`
- État : pseudocode obtenu
- Evidence : `ev_7c01d6e5f54ad42240e42ed6a3a4ab2d68c251467f985d2cc74da384dcbe4f7b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401fa0` — `thunk_FUN_00429d5c`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472db0` — `FUN_00472db0`
- `0x472f10` — `FUN_00472f10`
- `0x4737e0` — `_strncpy`
- `0x476e20` — `_strncmp`

### Chaînes référencées

- `0x4a4ea4` — "%s %d"
- `0x4a4eac` — "%s %d"
- `0x4a4eb4` — "%s %d"

### Pseudocode Ghidra

```c
void FUN_00463563(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined1 local_238 [32];
  undefined1 local_218 [268];
  int local_10c;
  char local_108 [256];
  undefined2 local_8 [2];
  
  iVar1 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,20000);
  if (iVar1 == 0) {
    *(undefined2 *)(in_ECX + 0x2cc28) = 0;
    while ((*(short *)(in_ECX + 0x2cc28) < 0x20 &&
           (iVar1 = thunk_FUN_0040f5b3(local_108,1), iVar1 != -1))) {
      _strncpy((char *)(in_ECX + 0x2c6a8 + *(short *)(in_ECX + 0x2cc28) * 0x2c),local_108,0x20);
      *(undefined1 *)(in_ECX + 0x2c6c7 + *(short *)(in_ECX + 0x2cc28) * 0x2c) = 0;
      thunk_FUN_0040f5b3(local_108,1);
      FUN_00472f10(local_108,s__s__d_004a4ea4,local_238,local_8);
      *(short *)(in_ECX + 0x2c6c8 + *(short *)(in_ECX + 0x2cc28) * 0x2c) = local_8[0] + -1;
      thunk_FUN_0040f5b3(local_108,1);
      FUN_00472f10(local_108,s__s__d_004a4eac,local_238,local_8);
      *(undefined2 *)(in_ECX + 0x2c6ca + *(short *)(in_ECX + 0x2cc28) * 0x2c) = local_8[0];
      thunk_FUN_0040f5b3(local_108,1);
      FUN_00472f10(local_108,s__s__d_004a4eb4,local_238,local_8);
      *(undefined2 *)(in_ECX + 0x2c6cc + *(short *)(in_ECX + 0x2cc28) * 0x2c) = local_8[0];
      local_10c = 0;
      local_218[0] = 0;
      while (local_10c == 0) {
        thunk_FUN_0040f5b3(local_108,1);
        iVar1 = _strncmp(local_108,&DAT_004a4ebc,3);
        if (iVar1 == 0) {
          local_10c = 1;
        }
        else {
          FUN_00472db0(local_218,local_108);
          FUN_00472db0(local_218,&DAT_004a4ec0);
        }
      }
      uVar2 = thunk_FUN_00429d5c(local_218,0);
      *(undefined4 *)(in_ECX + 0x2c6d0 + *(short *)(in_ECX + 0x2cc28) * 0x2c) = uVar2;
      *(short *)(in_ECX + 0x2cc28) = *(short *)(in_ECX + 0x2cc28) + 1;
    }
  }
  return;
}
```

---

---

## FUN_004637fc — 0x4637fc

- Classification : internal
- Corps : `0x4637fc–0x4641dd`
- État : pseudocode obtenu
- Evidence : `ev_96a46390b086f06a56b3c395f6e1a9de7ba2c2a1c30396c7ca72c63944a1039e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010dc` — `thunk_FUN_00461b3b`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x401b2c` — `thunk_FUN_00464b9e`
- `0x401cd0` — `thunk_FUN_00461859`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402261` — `thunk_FUN_00415372`
- `0x4022ca` — `thunk_FUN_0046466f`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a4ec4` — "size>=0 && size<MAX_WORLDSIZE"
- `0x4a4ee4` — "C:\\float\\src\\tworld.cpp"
- `0x4a4efc` — "difficulty>=0"
- `0x4a4f0c` — "C:\\float\\src\\tworld.cpp"
- `0x4a4f24` — "mWorldSize<TW_NumWorlds"
- `0x4a4f3c` — "C:\\float\\src\\tworld.cpp"
- `0x4a4f54` — "emptycount > 0"
- `0x4a4f64` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
void FUN_004637fc(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int in_ECX;
  int local_d4;
  int local_d0;
  int local_c8;
  int local_c0;
  short local_bc;
  int local_b8;
  short local_b4;
  short local_b0;
  int local_a8;
  int local_a0;
  int local_98;
  int local_90;
  int local_88;
  int aiStack_84 [32];
  
  if ((param_1 < 0) || (3 < param_1)) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4ee4,0x3b6,
                       s_size>_0____size<MAX_WORLDSIZE_004a4ec4);
  }
  if (param_2 < 0) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4f0c,0x3b7,s_difficulty>_0_004a4efc);
  }
  *(undefined2 *)(in_ECX + 0x2749a) = (undefined2)param_1;
  if (DAT_005ebd70 <= *(short *)(in_ECX + 0x2749a)) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4f3c,0x3bb,s_mWorldSize<TW_NumWorlds_004a4f24);
  }
  *(int *)(in_ECX + 0x2cc30) = param_2;
  *(undefined2 *)(in_ECX + 0x2cf9c) = 0;
  *(undefined2 *)(in_ECX + 0x2cf9e) = 0;
  *(undefined4 *)(in_ECX + 0x2cc34) = 5000;
  *(undefined4 *)(in_ECX + 0x2cc38) = 4000;
  iVar2 = thunk_FUN_00467260(2);
  *(ushort *)(in_ECX + 0x2cc3c) = (-(ushort)(iVar2 != 0) & 2) - 1;
  iVar2 = thunk_FUN_00467260(2);
  *(ushort *)(in_ECX + 0x2cc3e) = (-(ushort)(iVar2 != 0) & 2) - 1;
  *(undefined2 *)(in_ECX + 0x27498) =
       *(undefined2 *)(&DAT_005ebf98 + *(short *)(in_ECX + 0x2749a) * 2);
  *(undefined2 *)(in_ECX + 0x2759c) =
       *(undefined2 *)(&DAT_005ebd68 + *(short *)(in_ECX + 0x2749a) * 2);
  for (local_88 = 0; local_88 < (int)(uint)*(ushort *)(in_ECX + 0x2759c); local_88 = local_88 + 1) {
    *(undefined2 *)(in_ECX + 0x274a0 + local_88 * 8) =
         *(undefined2 *)(&DAT_0061fa54 + local_88 * 8 + *(short *)(in_ECX + 0x2749a) * 0x100);
    *(undefined2 *)(in_ECX + 0x274a2 + local_88 * 8) =
         *(undefined2 *)(&DAT_0061fa56 + local_88 * 8 + *(short *)(in_ECX + 0x2749a) * 0x100);
    *(undefined4 *)(in_ECX + 0x2749c + local_88 * 8) = 0;
  }
  for (local_88 = 0; local_88 < (int)(uint)*(ushort *)(in_ECX + 0x27498); local_88 = local_88 + 1) {
    thunk_FUN_00461b3b(local_88);
    thunk_FUN_00461859();
  }
  *(undefined2 *)(in_ECX + 0x2c6a4) = 0;
  for (local_88 = 0; local_88 < 0x40; local_88 = local_88 + 1) {
    *(undefined4 *)(in_ECX + 0x2c1a4 + local_88 * 0x14) = 0;
  }
  for (local_88 = 0; local_88 < 0x100; local_88 = local_88 + 1) {
    *(undefined4 *)(in_ECX + 0x275a0 + local_88 * 0x4c) = 0xffffffff;
  }
  _memset((void *)(in_ECX + 0x2cd42),0,0x1e);
  _memset((void *)(in_ECX + 0x2cd60),0,0x1e);
  _memset((void *)(in_ECX + 0x2cd7e),0,0x1e);
  thunk_FUN_0046466f(param_3,param_4);
  thunk_FUN_00464b9e(param_3,param_4);
  for (local_88 = 0; local_88 < (int)(uint)*(ushort *)(in_ECX + 0x27498); local_88 = local_88 + 1) {
    local_98 = in_ECX + 0x428 + local_88 * 0x29e8;
    for (local_a0 = 0; local_a0 < *(short *)(in_ECX + local_88 * 0x29e8 + 0x29a8);
        local_a0 = local_a0 + 1) {
      if (*(int *)(local_98 + 4) == 2) {
        *(undefined4 *)(local_98 + 0x10) = 2;
      }
      local_98 = local_98 + 0x60;
    }
  }
  local_88 = 0;
  do {
    if ((int)(uint)*(ushort *)(in_ECX + 0x2759c) <= local_88) {
      for (local_88 = 0; local_88 < (int)(*(ushort *)(in_ECX + 0x27498) - 1);
          local_88 = local_88 + 1) {
        iVar2 = (int)*(short *)(in_ECX + 0x29e0 + local_88 * 0x29e8);
        aiStack_84[local_88 * 2] = iVar2 << 1;
        aiStack_84[local_88 * 2 + 1] = iVar2 * 2 + 1;
      }
      local_90 = 0;
      do {
        do {
          if ((int)((uint)*(ushort *)(in_ECX + 0x27498) * 2 + -2) <= local_90) {
            for (local_88 = 0; local_88 < 9; local_88 = local_88 + 1) {
              *(undefined4 *)(&DAT_005e16b0 + local_88 * 4) = 0;
            }
            DAT_005e16a8 = 0;
            thunk_FUN_00415372();
            *(undefined4 *)(in_ECX + 0x2cc2c) = 0;
            return;
          }
          local_d0 = local_90 / 2;
          if (DAT_0049c99c != 0) {
            local_d0 = thunk_FUN_00467260(*(ushort *)(in_ECX + 0x27498) - 1);
          }
          iVar2 = in_ECX + local_d0 * 0x29e8;
          local_c0 = 0;
          local_d4 = iVar2 + 0x428;
          for (local_88 = 0; local_88 < *(short *)(iVar2 + 0x29a8); local_88 = local_88 + 1) {
            if (((*(int *)(local_d4 + 4) == 0) && (*(int *)(local_d4 + 0x14) == -1)) &&
               (*(int *)(local_d4 + 0x10) == 0)) {
              local_c0 = local_c0 + 1;
            }
            local_d4 = local_d4 + 0x60;
          }
        } while (local_c0 == 0);
        iVar3 = thunk_FUN_00467260(local_c0);
        local_c8 = 0;
        local_d4 = iVar2 + 0x428;
        for (local_88 = 0; local_88 < *(short *)(iVar2 + 0x29a8); local_88 = local_88 + 1) {
          if (((*(int *)(local_d4 + 4) == 0) && (*(int *)(local_d4 + 0x14) == -1)) &&
             (*(int *)(local_d4 + 0x10) == 0)) {
            if (local_c8 == iVar3) {
              *(undefined4 *)(local_d4 + 0x10) = 1;
              *(int *)(local_d4 + 0x24) = aiStack_84[local_90] + 6;
              local_90 = local_90 + 1;
              break;
            }
            local_c8 = local_c8 + 1;
          }
          local_d4 = local_d4 + 0x60;
        }
      } while( true );
    }
    for (local_bc = (short)local_88; (int)(*(ushort *)(in_ECX + 0x27498) - 1) <= (int)local_bc;
        local_bc = (local_bc - (*(short *)(in_ECX + 0x27498) + -1)) + 4) {
    }
    iVar2 = in_ECX + local_bc * 0x29e8;
    local_b4 = 0;
    local_a8 = iVar2 + 0x428;
    for (local_b8 = 0; local_b8 < *(short *)(iVar2 + 0x29a8); local_b8 = local_b8 + 1) {
      if (((*(int *)(local_a8 + 4) == 0) && (*(int *)(local_a8 + 0x10) == 0)) &&
         (*(int *)(local_a8 + 0x14) == -1)) {
        local_b4 = local_b4 + 1;
      }
      local_a8 = local_a8 + 0x60;
    }
    if (local_b4 < 1) {
      thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4f64,0x40a,s_emptycount_>_0_004a4f54);
    }
    sVar1 = thunk_FUN_00467260((int)local_b4);
    local_b0 = 0;
    local_a8 = iVar2 + 0x428;
    for (local_b8 = 0; local_b8 < *(short *)(iVar2 + 0x29a8); local_b8 = local_b8 + 1) {
      if (((*(int *)(local_a8 + 4) == 0) && (*(int *)(local_a8 + 0x10) == 0)) &&
         (*(int *)(local_a8 + 0x14) == -1)) {
        if (local_b0 == sVar1) {
          *(undefined4 *)(local_a8 + 0x10) = 1;
          *(undefined4 *)(local_a8 + 0x24) = 5;
          break;
        }
        local_b0 = local_b0 + 1;
      }
      local_a8 = local_a8 + 0x60;
    }
    local_88 = local_88 + 1;
  } while( true );
}
```

---

---

## FUN_004641de — 0x4641de

- Classification : internal
- Corps : `0x4641de–0x464241`
- État : pseudocode obtenu
- Evidence : `ev_f92b05e1bac76d2be3a91b76e6eb420474e1d04db600d49cc8d4a55edf30587d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a4f7c` — "val >= 0 && val < NUMPADITEMINFOS"
- `0x4a4fa0` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
undefined * FUN_004641de(int param_1,int param_2)

{
  int local_8;
  
  local_8 = param_2;
  if ((-1 < param_1) && (param_1 < 4)) {
    local_8 = param_2 + param_1 * 0x10;
  }
  if ((local_8 < 0) || (100 < local_8)) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4fa0,0x46b,
                       s_val_>__0____val_<_NUMPADITEMINFO_004a4f7c);
  }
  return &DAT_005eac08 + local_8 * 0x2c;
}
```

---

---

## FUN_00464242 — 0x464242

- Classification : internal
- Corps : `0x464242–0x4642a2`
- État : pseudocode obtenu
- Evidence : `ev_055bd9354dfe4717f5f4c2749565d4303a049541ad9fbd7afe7d37d0536bc244`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a4fb8` — "val >= 0 && val < NUMFLOATERINFOS"
- `0x4a4fdc` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
undefined * FUN_00464242(int param_1,int param_2)

{
  int local_8;
  
  if (param_1 == 4) {
    local_8 = param_2 + 0x1b;
  }
  else {
    local_8 = param_1 * 9 + param_2;
  }
  if ((local_8 < 0) || (0x2c < local_8)) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4fdc,0x478,
                       s_val_>__0____val_<_NUMFLOATERINFO_004a4fb8);
  }
  return &DAT_005ebfa0 + local_8 * 0xe;
}
```

---

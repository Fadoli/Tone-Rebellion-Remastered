# 0017_batch_0013 — détails (2/3)

## FUN_00461b3b — 0x461b3b

- Classification : internal
- Corps : `0x461b3b–0x462093`
- État : pseudocode obtenu
- Evidence : `ev_3b7162466a7231d687838b72eb5276518cedf5f25744ad18bf65773722a5e009`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401154` — `thunk_FUN_00414b91`
- `0x40149c` — `thunk_FUN_00414bc2`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472ca0` — `FUN_00472ca0`
- `0x472f10` — `FUN_00472f10`
- `0x4774f0` — `_strcmp`

### Chaînes référencées

- `0x4a4bb0` — "data\\ISLAND%02d.TXT"
- `0x4a4bc4` — "%s %d"
- `0x4a4bcc` — "numlocs <= MAX_ISLAND_LOCS"
- `0x4a4be8` — "C:\\float\\src\\tworld.cpp"
- `0x4a4c00` — "%d %d %d %s %d"
- `0x4a4c14` — "smpad"
- `0x4a4c1c` — "mdpad"
- `0x4a4c24` — "lgpad"
- `0x4a4c34` — "bridge"
- `0x4a4c3c` — "special"
- `0x4a4c44` — "levhub"
- `0x4a4c4c` — "levshld"
- `0x4a4c54` — "feature"
- `0x4a4c5c` — "feattrig"
- `0x4a4c68` — "FALSE"
- `0x4a4c70` — "C:\\float\\src\\tworld.cpp"
- `0x4a4c88` — "mNumLocs < MAX_ISLAND_LOCS"
- `0x4a4ca4` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_00461b3b(undefined2 param_1)

{
  undefined2 *puVar1;
  int iVar2;
  undefined4 uVar3;
  int in_ECX;
  uint local_e8;
  undefined4 local_e0;
  undefined2 local_dc [2];
  undefined2 local_d8 [2];
  undefined1 local_d4 [4];
  int local_d0 [4];
  short local_c0;
  char local_bc [24];
  int local_a4;
  undefined4 local_a0;
  undefined1 local_9c [100];
  undefined1 local_38 [52];
  
  *(undefined2 *)(in_ECX + 0x29e0) =
       *(undefined2 *)(&DAT_005eaba8 + ((in_ECX + -0x5ec218) / 0x29e8) * 2 + DAT_006136b2 * 0x1e);
  FUN_00472ca0(local_38,s_data_ISLAND_02d_TXT_004a4bb0,(int)*(short *)(in_ECX + 0x29e0));
  iVar2 = thunk_FUN_0040f419(local_38,&DAT_004b28f0,20000);
  if (iVar2 == 0) {
    *(undefined2 *)(in_ECX + 0x29a8) = 0;
    thunk_FUN_0040f5b3(local_9c,0);
    FUN_00472f10(local_9c,s__s__d_004a4bc4,local_38,&local_a4);
    if (100 < local_a4) {
      thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4be8,0xf1,
                         s_numlocs_<__MAX_ISLAND_LOCS_004a4bcc);
    }
    for (local_c0 = 0; local_c0 < local_a4; local_c0 = local_c0 + 1) {
      thunk_FUN_0040f5b3(local_9c,0);
      iVar2 = FUN_00472f10(local_9c,s__d__d__d__s__d_004a4c00,local_d4,local_d8,local_dc,local_bc,
                           local_d0);
      if (iVar2 != 5) {
        return 0;
      }
      local_e8 = 0;
      local_e0 = 0;
      iVar2 = _strcmp(local_bc,&DAT_004a4c10);
      if (iVar2 == 0) {
        local_a0 = 0;
        local_e8 = (uint)(local_d0[0] == 1);
      }
      else {
        iVar2 = _strcmp(local_bc,s_smpad_004a4c14);
        if (iVar2 == 0) {
          local_a0 = 0;
          local_e8 = (uint)(local_d0[0] == 1);
        }
        else {
          iVar2 = _strcmp(local_bc,s_mdpad_004a4c1c);
          if (iVar2 == 0) {
            local_a0 = 0;
            local_e0 = 1;
            local_e8 = (uint)(local_d0[0] == 1);
          }
          else {
            iVar2 = _strcmp(local_bc,s_lgpad_004a4c24);
            if (iVar2 == 0) {
              local_a0 = 0;
              local_e0 = 2;
              local_e8 = (uint)(local_d0[0] == 1);
            }
            else {
              iVar2 = _strcmp(local_bc,&DAT_004a4c2c);
              if (iVar2 == 0) {
                local_a0 = 1;
              }
              else {
                iVar2 = _strcmp(local_bc,s_bridge_004a4c34);
                if (iVar2 == 0) {
                  local_a0 = 2;
                }
                else {
                  iVar2 = _strcmp(local_bc,s_special_004a4c3c);
                  if (iVar2 == 0) {
                    local_a0 = 3;
                  }
                  else {
                    iVar2 = _strcmp(local_bc,s_levhub_004a4c44);
                    if (iVar2 == 0) {
                      local_a0 = 3;
                      local_e8 = 0x16;
                    }
                    else {
                      iVar2 = _strcmp(local_bc,s_levshld_004a4c4c);
                      if (iVar2 == 0) {
                        local_a0 = 0;
                      }
                      else {
                        iVar2 = _strcmp(local_bc,s_feature_004a4c54);
                        if (iVar2 == 0) {
                          local_a0 = 3;
                          local_e8 = 4;
                        }
                        else {
                          iVar2 = _strcmp(local_bc,s_feattrig_004a4c5c);
                          if (iVar2 != 0) {
                            thunk_FUN_00414b91(s_C__float_src_tworld_cpp_004a4c70,0x13d,
                                               s_FALSE_004a4c68,local_bc);
                            return 0;
                          }
                          local_a0 = 3;
                          local_e8 = 3;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (99 < *(short *)(in_ECX + 0x29a8)) {
        thunk_FUN_00414bc2(s_C__float_src_tworld_cpp_004a4ca4,0x141,
                           s_mNumLocs_<_MAX_ISLAND_LOCS_004a4c88,(int)*(short *)(in_ECX + 0x29e0));
      }
      puVar1 = (undefined2 *)(in_ECX + 0x428 + *(short *)(in_ECX + 0x29a8) * 0x60);
      *(short *)(in_ECX + 0x29a8) = *(short *)(in_ECX + 0x29a8) + 1;
      *(undefined4 *)(puVar1 + 2) = local_a0;
      *puVar1 = local_d8[0];
      puVar1[1] = local_dc[0];
      puVar1[4] = param_1;
      *(uint *)(puVar1 + 8) = local_e8;
      *(undefined4 *)(puVar1 + 6) = local_e0;
      switch(local_a0) {
      case 0:
        break;
      case 1:
        puVar1[0x10] = 0x14;
        break;
      case 2:
        puVar1[0x1b] = (undefined2)local_d0[0];
        break;
      case 3:
        if (*(int *)(puVar1 + 8) == 3) {
          puVar1[0x25] = (undefined2)local_d0[0];
        }
        else if (*(int *)(puVar1 + 8) == 4) {
          *(short *)(in_ECX + 0x29d0) = local_c0;
        }
      }
    }
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}
```

---

---

## FUN_004620a4 — 0x4620a4

- Classification : internal
- Corps : `0x4620a4–0x46210f`
- État : pseudocode obtenu
- Evidence : `ev_ab8c3b536bfc7f9d9c2578cc3e5fd6fdb1a0674eff1670eda940aff59a36de3c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004620a4(int param_1,int param_2)

{
  int in_ECX;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (*(short *)(in_ECX + param_1 * 2) <= local_8) {
      return 0;
    }
    if ((*(int *)(in_ECX + 8 + param_1 * 0x100 + local_8 * 8) <= param_2) &&
       (param_2 <= *(int *)(in_ECX + param_1 * 0x100 + 0xc + local_8 * 8))) break;
    local_8 = local_8 + 1;
  }
  return 1;
}
```

---

---

## FUN_00462110 — 0x462110

- Classification : internal
- Corps : `0x462110–0x46226b`
- État : pseudocode obtenu
- Evidence : `ev_bb7bfd638dab1623b8d3eb908028998e40ef60175b2b6fea8a8f73134068fccf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a4cbc` — "numspans < MAX_TONE_SPANS"
- `0x4a4cd8` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
void FUN_00462110(int param_1,int param_2,int param_3)

{
  int in_ECX;
  int iVar1;
  int *local_10;
  int local_8;
  
  iVar1 = (int)*(short *)(in_ECX + param_1 * 2);
  if (0x1f < iVar1) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4cd8,0x178,s_numspans_<_MAX_TONE_SPANS_004a4cbc
                      );
  }
  if (param_2 < 0) {
    param_2 = 0;
  }
  if (0x9ff < param_3) {
    param_3 = 0x9ff;
  }
  local_8 = iVar1;
  if (0 < iVar1) {
    local_10 = (int *)(in_ECX + 8 + param_1 * 0x100);
    for (local_8 = 0; local_8 < iVar1; local_8 = local_8 + 1) {
      if ((param_2 < *local_10) && (*local_10 <= param_3)) {
        *local_10 = param_2;
        if (local_10[1] < param_3) {
          local_10[1] = param_3;
        }
        break;
      }
      if ((local_10[1] < param_3) && (param_2 <= local_10[1])) {
        local_10[1] = param_3;
        if (param_2 < *local_10) {
          *local_10 = param_2;
        }
        break;
      }
      local_10 = local_10 + 2;
    }
  }
  if (local_8 == iVar1) {
    *(int *)(in_ECX + 8 + param_1 * 0x100 + iVar1 * 8) = param_2;
    *(int *)(in_ECX + param_1 * 0x100 + 0xc + iVar1 * 8) = param_3;
    *(short *)(in_ECX + param_1 * 2) = *(short *)(in_ECX + param_1 * 2) + 1;
  }
  return;
}
```

---

---

## FUN_0046226c — 0x46226c

- Classification : internal
- Corps : `0x46226c–0x462284`
- État : pseudocode obtenu
- Evidence : `ev_3905b02543f0b0144a753b7cb0c664db2865ddb18518f6f3986f90ac7a4b59d9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046226c(int param_1)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + param_1 * 2) = 0;
  return;
}
```

---

---

## FUN_00462285 — 0x462285

- Classification : internal
- Corps : `0x462285–0x4626f7`
- État : pseudocode obtenu
- Evidence : `ev_d21db672f076fafb487f3df6b6c2223688f295be4f07b4dfb7d9645fa381068c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014f6` — `thunk_FUN_00462110`
- `0x401992` — `thunk_FUN_004539e9`
- `0x401aa0` — `thunk_FUN_004620a4`
- `0x401bef` — `thunk_FUN_00453cf5`
- `0x401c71` — `thunk_FUN_0046226c`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401ff0` — `thunk_FUN_00453958`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a4cf0` — "tribe > FT_None && tribe < FT_NumTypes"
- `0x4a4d18` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
int FUN_00462285(int param_1)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int in_ECX;
  uint uVar4;
  int local_88;
  int local_84;
  short *local_80;
  byte local_78;
  byte local_74 [100];
  int local_10;
  int local_c;
  int local_8;
  
  if ((param_1 < 0) || (4 < param_1)) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4d18,0x1a7,
                       s_tribe_>_FT_None____tribe_<_FT_Nu_004a4cf0);
  }
  local_88 = 0;
  local_10 = param_1;
  uVar4 = 1 << ((byte)param_1 & 0x1f);
  _memset(local_74,0,100);
  thunk_FUN_0046226c(local_10);
  bVar2 = true;
  while (local_78 = (byte)uVar4, bVar2) {
    bVar2 = false;
    local_80 = (short *)(in_ECX + 0x428);
    for (local_84 = 0; local_84 < *(short *)(in_ECX + 0x29a8); local_84 = local_84 + 1) {
      if (*(int *)(local_80 + 10) != 4) {
        if (*(int *)(&DAT_0061a654 + local_10 * 0x14a0) == 0) {
          if (local_74[local_84] == 0) {
            if (*(int *)(local_80 + 2) == 1) {
              if ((((int)(char)local_80[0x11] & uVar4) != 0) ||
                 (iVar3 = thunk_FUN_004620a4(local_10,(int)*local_80), iVar3 != 0)) {
                local_74[local_84] = local_78;
                thunk_FUN_00462110(local_10,*local_80 + -0x96,*local_80 + 0x96);
                local_88 = local_88 + 1;
              }
            }
            else if (*(int *)(local_80 + 2) == 2) {
              if ((*(uint *)(local_80 + 0xe) & 1) != 0) {
                local_74[local_84] = local_78;
                thunk_FUN_00462110(local_10,*local_80 + -100,*local_80 + 100);
              }
            }
            else if (((*(int *)(local_80 + 2) == 0) &&
                     (iVar3 = thunk_FUN_00453cf5(param_1), iVar3 != 0)) &&
                    ((*(int *)(local_80 + 8) == 0x28 &&
                     ((iVar3 = thunk_FUN_00453958(), iVar3 != 0 &&
                      (iVar3 = thunk_FUN_004620a4(local_10,(int)*local_80), iVar3 != 0)))))) {
              local_74[local_84] = local_78;
              thunk_FUN_00462110(local_10,*local_80 + -300,*local_80 + 300);
            }
            if (local_74[local_84] != 0) {
              bVar2 = true;
            }
          }
        }
        else {
          local_74[local_84] = local_78;
        }
      }
      local_80 = local_80 + 0x30;
    }
  }
  local_80 = (short *)(in_ECX + 0x428);
  for (local_84 = 0; local_84 < *(short *)(in_ECX + 0x29a8); local_84 = local_84 + 1) {
    if ((((local_74[local_84] == 0) && (*(int *)(local_80 + 2) == 0)) &&
        (*(int *)(local_80 + 10) != 4)) &&
       (iVar3 = thunk_FUN_004620a4(local_10,(int)*local_80), iVar3 != 0)) {
      local_74[local_84] = local_78;
    }
    local_80 = local_80 + 0x30;
  }
  if (*(int *)(&DAT_0061a654 + local_10 * 0x14a0) != 0) {
    thunk_FUN_00462110(local_10,0,0xa00);
    local_88 = 10;
  }
  local_80 = (short *)(in_ECX + 0x428);
  for (local_84 = 0; local_84 < *(short *)(in_ECX + 0x29a8); local_84 = local_84 + 1) {
    *(byte *)((int)local_80 + 0x22) = *(byte *)((int)local_80 + 0x22) & ~local_78;
    *(byte *)((int)local_80 + 0x22) = *(byte *)((int)local_80 + 0x22) | local_74[local_84];
    thunk_FUN_004539e9();
    local_80 = (short *)((int)local_80 + 0x60);
  }
  local_c = *(int *)(in_ECX + 0x408 + local_10 * 8);
  local_8 = *(int *)(in_ECX + 0x40c + local_10 * 8);
  for (local_84 = 0; local_84 < *(short *)(in_ECX + local_10 * 2); local_84 = local_84 + 1) {
    iVar3 = in_ECX + 8 + local_10 * 0x100;
    iVar1 = *(int *)(iVar3 + local_84 * 8);
    iVar3 = *(int *)(iVar3 + 4 + local_84 * 8);
    if (iVar1 + -100 < local_c) {
      local_c = iVar1 + -100;
    }
    if (local_8 < iVar3 + 100) {
      local_8 = iVar3 + 100;
    }
  }
  if (local_c < 0) {
    local_c = 0;
  }
  if (0x9ff < local_8) {
    local_8 = 0x9ff;
  }
  *(int *)(in_ECX + 0x408 + local_10 * 8) = local_c;
  *(int *)(in_ECX + 0x40c + local_10 * 8) = local_8;
  return local_88;
}
```

---

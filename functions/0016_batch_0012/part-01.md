# 0016_batch_0012 — détails (1/6)

## FUN_00453d36 — 0x453d36

- Classification : internal
- Corps : `0x453d36–0x453d8e`
- État : pseudocode obtenu
- Evidence : `ev_c4a96d9bf9951cb69aea782bbd170ccad76dc0935469c6d27ef5a7f4e14fe08b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401875` — `thunk_FUN_0040fc15`
- `0x401bc7` — `thunk_FUN_004500b6`
- `0x401cee` — `thunk_FUN_0040fd80`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00453d36(undefined4 param_1,int param_2)

{
  undefined4 *in_ECX;
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_64 [24];
  
  thunk_FUN_004500b6();
  if (param_2 == 0) {
    puVar2 = local_64;
    for (iVar1 = 0x18; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *in_ECX;
      in_ECX = in_ECX + 1;
      puVar2 = puVar2 + 1;
    }
    thunk_FUN_0040fd80(local_64,0x60);
  }
  else {
    thunk_FUN_0040fc15(local_64,0x60);
    puVar2 = local_64;
    for (iVar1 = 0x18; iVar1 != 0; iVar1 = iVar1 + -1) {
      *in_ECX = *puVar2;
      puVar2 = puVar2 + 1;
      in_ECX = in_ECX + 1;
    }
  }
  return;
}
```

---

## FUN_00454ce0 — 0x454ce0

- Classification : internal
- Corps : `0x454ce0–0x454ce9`
- État : pseudocode obtenu
- Evidence : `ev_dd454350423206db9c497b965dc45628f54b060b8e097bc8b303968236b4c10a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x454cea` — `FUN_00454cea`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00454ce0(void)

{
  FUN_00454cea();
  return;
}
```

---

## FUN_00454cea — 0x454cea

- Classification : internal
- Corps : `0x454cea–0x454cf8`
- État : pseudocode obtenu
- Evidence : `ev_71c23bd09ba8361ec26ee2cf2e8dda8bc8e7d51d93e978ab7c6c0d5e4396ab2a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401c8f` — `thunk_FUN_00455825`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00454cea(void)

{
  thunk_FUN_00455825();
  return;
}
```

---

## FUN_00454cf9 — 0x454cf9

- Classification : internal
- Corps : `0x454cf9–0x454d1e`
- État : pseudocode obtenu
- Evidence : `ev_606f80cf8581ee600486079bf518fb284ea44b7b85a0a516b6e4b1531f9c8348`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00454cf9(int param_1,int param_2,int param_3,int param_4)

{
  if (param_4 == 0) {
    param_3 = ((param_2 - param_1) + 1) * param_3;
  }
  else {
    param_3 = (param_2 - param_1) * param_3 * 2;
  }
  return param_3;
}
```

---

## FUN_00454d1f — 0x454d1f

- Classification : internal
- Corps : `0x454d1f–0x45575b`
- État : pseudocode obtenu
- Evidence : `ev_6ccf11adf4100a01f329d47d35c0c8bd1d7e5c6fcff4d70ee2a0c846e156a876`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013e8` — `thunk_FUN_00415f1e`
- `0x40149c` — `thunk_FUN_00414bc2`
- `0x401acd` — `thunk_FUN_0040ebde`
- `0x401dde` — `thunk_FUN_00454cf9`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472f10` — `FUN_00472f10`
- `0x4737e0` — `_strncpy`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x4a2b04` — "status == 0"
- `0x4a2b10` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2b3c` — "currnum < MAX_FLOATER_SHAPE_ITEMS"
- `0x4a2b60` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2b7c` — "%s %s"
- `0x4a2b84` — "t == 2"
- `0x4a2b8c` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2bb0` — "%s %s"
- `0x4a2bb8` — "t == 2"
- `0x4a2bc0` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2be4` — "%s %s"
- `0x4a2bec` — "t == 2"
- `0x4a2bf4` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2c18` — "%s %d %d"
- `0x4a2c24` — "t >= 2"
- `0x4a2c2c` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2c48` — "hover"
- `0x4a2c50` — "%s %d %d %d"
- `0x4a2c5c` — "t >= 2"
- `0x4a2c64` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2c80` — "pickup"
- `0x4a2c88` — "%s %d %d %d"
- `0x4a2c94` — "t >= 2"
- `0x4a2c9c` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2cb8` — "carry"
- `0x4a2cc0` — "%s %d %d"
- `0x4a2ccc` — "t >= 2"
- `0x4a2cd4` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2cf0` — "attack"
- `0x4a2cf8` — "%s %d %d %d %c %d"
- `0x4a2d0c` — "t >= 2"
- `0x4a2d14` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2d30` — "atteff"
- `0x4a2d38` — "%s %s"
- `0x4a2d40` — "t == 2"
- `0x4a2d48` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2d64` — "graspxy"
- `0x4a2d6c` — "%s %d %d"
- `0x4a2d78` — "t == 3"
- `0x4a2d80` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2d9c` — "attxy"
- `0x4a2da4` — "%s %d %d"
- `0x4a2db0` — "t == 3"
- `0x4a2db8` — "C:\\float\\src\\shapeinf.cpp"

### Pseudocode Ghidra

```c
void FUN_00454d1f(undefined4 param_1)

{
  undefined2 uVar1;
  int iVar2;
  int in_ECX;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  char local_b4 [20];
  char local_a0 [4];
  char local_9c [20];
  undefined4 local_88;
  int local_84;
  int local_80;
  undefined2 *local_70;
  undefined4 local_6c;
  undefined1 local_68 [100];
  
  local_80 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,20000);
  if (local_80 != 0) {
    thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a2b10,0x29,s_status____0_004a2b04);
  }
  *(undefined2 *)(in_ECX + 0x1740) = 0;
  local_84 = -1;
  local_88 = 0;
  local_6c = 0;
  local_70 = (undefined2 *)0x0;
  while (iVar2 = thunk_FUN_0040f5b3(local_68,0), iVar2 == 0) {
    FUN_00472f10(local_68,&DAT_004a2b2c,local_9c);
    iVar2 = __strcmpi(local_9c,&DAT_004a2b30);
    if (iVar2 == 0) break;
    iVar2 = __strcmpi(local_9c,&DAT_004a2b34);
    if (iVar2 == 0) {
      local_84 = local_84 + 1;
      if (0x3f < local_84) {
        thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a2b60,0x40,
                           s_currnum_<_MAX_FLOATER_SHAPE_ITEM_004a2b3c);
      }
      iVar2 = FUN_00472f10(local_68,s__s__s_004a2b7c,local_9c,local_b4);
      if (iVar2 != 2) {
        thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a2b8c,0x43,s_t____2_004a2b84);
      }
      local_70 = (undefined2 *)(in_ECX + local_84 * 0x54);
      _strncpy((char *)(in_ECX + 0x1500 + local_84 * 9),local_b4,8);
      *(undefined1 *)(in_ECX + 0x1508 + local_84 * 9) = 0;
      local_70[1] = 0xffff;
      *local_70 = 0xffff;
      local_70[0x24] = 0xffff;
      local_70[0x28] = 0;
      local_70[0x27] = 0;
      local_70[0x26] = 0;
      local_70[0x25] = 0;
    }
    else {
      iVar2 = __strcmpi(local_9c,&DAT_004a2ba8);
      if (iVar2 == 0) {
        iVar2 = FUN_00472f10(local_68,s__s__s_004a2bb0,local_9c,local_b4);
        if (iVar2 != 2) {
          thunk_FUN_00414bc2(s_C__float_src_shapeinf_cpp_004a2bc0,0x56,s_t____2_004a2bb8,local_84);
        }
        uVar1 = thunk_FUN_0040ebde(local_b4);
        *local_70 = uVar1;
      }
      else {
        iVar2 = __strcmpi(local_9c,&DAT_004a2bdc);
        if (iVar2 == 0) {
          iVar2 = FUN_00472f10(local_68,s__s__s_004a2be4,local_9c,local_b4);
          if (iVar2 != 2) {
            thunk_FUN_00414bc2(s_C__float_src_shapeinf_cpp_004a2bf4,0x5e,s_t____2_004a2bec,local_84)
            ;
          }
          uVar1 = thunk_FUN_0040ebde(local_b4);
          local_70[1] = uVar1;
        }
        else {
          iVar2 = __strcmpi(local_9c,&DAT_004a2c10);
          if (iVar2 == 0) {
            iVar2 = FUN_00472f10(local_68,s__s__d__d_004a2c18,local_9c,&local_b8,&local_bc);
            if (iVar2 < 2) {
              thunk_FUN_00414bc2(s_C__float_src_shapeinf_cpp_004a2c2c,0x66,s_t_>__2_004a2c24,
                                 local_84);
            }
            if (iVar2 < 3) {
              local_bc = local_b8;
            }
            local_70[2] = (undefined2)local_b8;
            local_70[3] = (undefined2)local_bc;
          }
          else {
            iVar2 = __strcmpi(local_9c,s_hover_004a2c48);
            if (iVar2 == 0) {
              iVar2 = FUN_00472f10(local_68,s__s__d__d__d_004a2c50,local_9c,&local_b8,&local_bc,
                                   &local_c0);
              if (iVar2 < 2) {
                thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a2c64,0x72,s_t_>__2_004a2c5c);
              }
              if (iVar2 < 3) {
                local_bc = local_b8;
              }
              if (iVar2 < 4) {
                local_c0 = 2;
              }
              local_70[4] = (undefined2)local_b8;
              local_70[5] = (undefined2)local_bc;
              local_70[6] = (undefined2)local_c0;
              local_70[7] = (undefined2)local_b8;
              *(undefined4 *)(local_70 + 8) = 0;
              uVar1 = thunk_FUN_00454cf9(local_b8,local_bc,local_c0,0);
              local_70[10] = uVar1;
            }
            else {
              iVar2 = __strcmpi(local_9c,s_pickup_004a2c80);
              if (iVar2 == 0) {
                iVar2 = FUN_00472f10(local_68,s__s__d__d__d_004a2c88,local_9c,&local_b8,&local_bc,
                                     &local_c0);
                if (iVar2 < 2) {
                  thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a2c9c,0x85,s_t_>__2_004a2c94);
                }
                if (iVar2 < 3) {
                  local_bc = local_b8;
                }
                if (iVar2 < 4) {
                  local_c0 = 2;
                }
                local_70[0xc] = (undefined2)local_b8;
                local_70[0xd] = (undefined2)local_bc;
                local_70[0xe] = (undefined2)local_c0;
                local_70[0xf] = (undefined2)local_bc;
                *(undefined4 *)(local_70 + 0x10) = 0;
                uVar1 = thunk_FUN_00454cf9(local_b8,local_bc,local_c0,0);
                local_70[10] = uVar1;
              }
              else {
                iVar2 = __strcmpi(local_9c,s_carry_004a2cb8);
                if (iVar2 == 0) {
                  iVar2 = FUN_00472f10(local_68,s__s__d__d_004a2cc0,local_9c,&local_b8,&local_bc,
                                       &local_c0);
                  if (iVar2 < 2) {
                    thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a2cd4,0x98,s_t_>__2_004a2ccc);
                  }
                  if (iVar2 < 3) {
                    local_bc = local_b8;
                  }
                  if (iVar2 < 4) {
                    local_c0 = 2;
                  }
                  local_70[0x14] = (undefined2)local_b8;
                  local_70[0x15] = (undefined2)local_bc;
                  local_70[0x16] = (undefined2)local_c0;
                  local_70[0x17] = (undefined2)local_bc;
                  *(undefined4 *)(local_70 + 0x18) = 0;
                  uVar1 = thunk_FUN_00454cf9(local_b8,local_bc,local_c0,0);
                  local_70[0x1a] = uVar1;
                }
                else {
                  iVar2 = __strcmpi(local_9c,s_attack_004a2cf0);
                  if (iVar2 == 0) {
                    iVar2 = FUN_00472f10(local_68,s__s__d__d__d__c__d_004a2cf8,local_9c,&local_b8,
                                         &local_bc,&local_c0,local_a0,&local_c4);
                    if (iVar2 < 2) {
                      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a2d14,0xab,s_t_>__2_004a2d0c
                                        );
                    }
                    if (iVar2 < 3) {
                      local_bc = local_b8;
                    }
                    if (iVar2 < 4) {
                      local_c0 = 2;
                    }
                    if (iVar2 < 5) {
                      local_a0[0] = 'L';
                    }
                    if (iVar2 < 6) {
                      local_c4 = local_bc;
                    }
                    local_70[0x1c] = (undefined2)local_b8;
                    local_70[0x1d] = (undefined2)local_bc;
                    local_70[0x1e] = (undefined2)local_c0;
                    local_70[0x1f] = (undefined2)local_c4;
                    *(uint *)(local_70 + 0x20) = (uint)(local_a0[0] == 'P');
                    uVar1 = thunk_FUN_00454cf9(local_b8,local_bc,local_c0,local_a0[0] == 'P');
                    local_70[0x22] = uVar1;
                  }
                  else {
                    iVar2 = __strcmpi(local_9c,s_atteff_004a2d30);
                    if (iVar2 == 0) {
                      iVar2 = FUN_00472f10(local_68,s__s__s_004a2d38,local_9c,local_b4);
                      if (iVar2 != 2) {
                        thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a2d48,0xc4,
                                           s_t____2_004a2d40);
                      }
                      uVar1 = thunk_FUN_00415f1e(local_b4);
                      local_70[0x24] = uVar1;
                    }
                    else {
                      iVar2 = __strcmpi(local_9c,s_graspxy_004a2d64);
                      if (iVar2 == 0) {
                        iVar2 = FUN_00472f10(local_68,s__s__d__d_004a2d6c,local_9c,&local_b8,
                                             &local_bc);
                        if (iVar2 != 3) {
                          thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a2d80,0xcc,
                                             s_t____3_004a2d78);
                        }
                        local_70[0x25] = (undefined2)local_b8;
                        local_70[0x26] = (undefined2)local_bc;
                      }
                      else {
                        iVar2 = __strcmpi(local_9c,s_attxy_004a2d9c);
                        if (iVar2 == 0) {
                          iVar2 = FUN_00472f10(local_68,s__s__d__d_004a2da4,local_9c,&local_b8,
                                               &local_bc);
                          if (iVar2 != 3) {
                            thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a2db8,0xd5,
                                               s_t____3_004a2db0);
                          }
                          local_70[0x27] = (undefined2)local_b8;
                          local_70[0x28] = (undefined2)local_bc;
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
    }
  }
  *(short *)(in_ECX + 0x1740) = (short)local_84 + 1;
  return;
}
```

---

## FUN_0045575c — 0x45575c

- Classification : internal
- Corps : `0x45575c–0x4557bb`
- État : pseudocode obtenu
- Evidence : `ev_c438a4e4609aef64254866213d7ddf71da639696fee66b111418aaf962898d12`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40149c` — `thunk_FUN_00414bc2`

### Chaînes référencées

- `0x4a2dd4` — "item != -1 && item < mNumItems"
- `0x4a2df4` — "C:\\float\\src\\shapeinf.cpp"

### Pseudocode Ghidra

```c
int FUN_0045575c(short param_1)

{
  int in_ECX;
  
  if ((param_1 == -1) || ((int)(uint)*(ushort *)(in_ECX + 0x1740) <= (int)param_1)) {
    thunk_FUN_00414bc2(s_C__float_src_shapeinf_cpp_004a2df4,0xe3,
                       s_item_____1____item_<_mNumItems_004a2dd4,(int)param_1);
  }
  return in_ECX + param_1 * 0x54;
}
```

---

## FUN_004557bc — 0x4557bc

- Classification : internal
- Corps : `0x4557bc–0x455824`
- État : pseudocode obtenu
- Evidence : `ev_7060c372bf104f242ef237949c5b00597b5bd6a4e25337c298ccc2674e7f672c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x48b100` — `__strcmpi`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined2 FUN_004557bc(char *param_1)

{
  int iVar1;
  int in_ECX;
  int local_c;
  
  local_c = 0;
  while( true ) {
    if ((int)(uint)*(ushort *)(in_ECX + 0x1740) <= local_c) {
      return 0xffff;
    }
    iVar1 = __strcmpi((char *)(in_ECX + 0x1500 + local_c * 9),param_1);
    if (iVar1 == 0) break;
    local_c = local_c + 1;
  }
  return (undefined2)local_c;
}
```

---

## FUN_00455825 — 0x455825

- Classification : internal
- Corps : `0x455825–0x455832`
- État : pseudocode obtenu
- Evidence : `ev_ad859f781daa935be0ac28f19ae469a0bd081bfd7b19aacc4cf8d516e3139d02`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00455825(void)

{
  undefined4 in_ECX;
  
  return in_ECX;
}
```

---

## FUN_00455833 — 0x455833

- Classification : internal
- Corps : `0x455833–0x456a12`
- État : pseudocode obtenu
- Evidence : `ev_5d60033e6cc433f212a51343e2761e910c21c813cc1727a5c0375a566c73d999`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401154` — `thunk_FUN_00414b91`
- `0x4013e8` — `thunk_FUN_00415f1e`
- `0x401acd` — `thunk_FUN_0040ebde`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472f10` — `FUN_00472f10`
- `0x474b20` — `_memset`
- `0x477b60` — `FUN_00477b60`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x4a2e1c` — "%s %s"
- `0x4a2e24` — "numargs==2"
- `0x4a2e30` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2e4c` — "SHAPE"
- `0x4a2e54` — "%s %s"
- `0x4a2e5c` — "numargs==2"
- `0x4a2e68` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2e8c` — "%s %d %d %d"
- `0x4a2e98` — "numargs>=3"
- `0x4a2ea4` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2ec8` — "%s %d %d %d %c"
- `0x4a2ed8` — "numargs==5"
- `0x4a2ee4` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2f08` — "%s %d %d"
- `0x4a2f14` — "numargs==3"
- `0x4a2f20` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2f44` — "%s %d %d %d %c %d"
- `0x4a2f58` — "numargs==6"
- `0x4a2f64` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2f88` — "%s %d %d %d %c %d %d,%d"
- `0x4a2fa0` — "numargs==8"
- `0x4a2fac` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a2fd0` — "%s %d %d %d %c %d %d %d,%d %s"
- `0x4a2ff0` — "numargs>=9"
- `0x4a2ffc` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a3020` — "%s %d %d %d,%d"
- `0x4a3030` — "numargs>=2"
- `0x4a303c` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a3060` — "%s %d %d"
- `0x4a306c` — "numargs==3"
- `0x4a3078` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a3098` — "mNumItems <= MAX_BLDSHP_ITEMS"
- `0x4a30b8` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a30d4` — "mNumBarg<=MAX_BARG_ANM"
- `0x4a30ec` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a3108` — "mNumBase<=MAX_BASE_ANM"
- `0x4a3120` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a313c` — "mNumChug<=MAX_CHUG_ANM"
- `0x4a3154` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a3170` — "mNumCons<=MAX_CONS_ANM"
- `0x4a3188` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a31a4` — "mNumGlyp<=MAX_GLYP_ANM"
- `0x4a31bc` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a31d8` — "mNumInci<=MAX_INCI_ANM"
- `0x4a31f0` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a320c` — "mNumOccu<=MAX_OCCU_ANM"
- `0x4a3224` — "C:\\float\\src\\shapeinf.cpp"
- `0x4a3240` — "mNumProd<=MAX_PROD_ANM"
- `0x4a3258` — "C:\\float\\src\\shapeinf.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_00455833(undefined4 param_1)

{
  char *pcVar1;
  byte *pbVar2;
  undefined2 uVar3;
  int iVar4;
  undefined4 uVar5;
  void *in_ECX;
  short local_dc;
  int local_c0;
  undefined2 local_bc [2];
  int local_b8;
  undefined2 local_b4 [2];
  undefined2 local_b0 [2];
  undefined1 local_ac [4];
  undefined1 local_a8 [16];
  int local_98;
  undefined1 local_94 [16];
  char local_84 [4];
  int local_80;
  char local_7c [16];
  undefined1 local_6c [100];
  undefined2 local_8 [2];
  
  iVar4 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,20000);
  if (iVar4 == 0) {
    *(undefined2 *)((int)in_ECX + 0xa20) = 0;
    _memset(in_ECX,0,0x360);
    *(undefined2 *)((int)in_ECX + 0xb42) = 0;
    *(undefined2 *)((int)in_ECX + 0xc64) = 0;
    *(undefined2 *)((int)in_ECX + 0xd66) = 0;
    *(undefined2 *)((int)in_ECX + 0xe68) = 0;
    *(undefined2 *)((int)in_ECX + 0xefa) = 0;
    *(undefined2 *)((int)in_ECX + 0x10fc) = 0;
    *(undefined2 *)((int)in_ECX + 0x11be) = 0;
    *(undefined2 *)((int)in_ECX + 0x11e0) = 0;
    for (local_98 = 0; local_98 < 0x60; local_98 = local_98 + 1) {
      for (local_c0 = 0; local_c0 < 8; local_c0 = local_c0 + 1) {
        *(undefined2 *)((int)in_ECX + local_c0 * 2 + local_98 * 0x10 + 0x420) = 0xffff;
      }
    }
    do {
      while( true ) {
        while( true ) {
          while( true ) {
            while( true ) {
              while( true ) {
                while( true ) {
                  while( true ) {
                    while( true ) {
                      while( true ) {
                        iVar4 = thunk_FUN_0040f5b3(local_6c,0);
                        if (iVar4 != 0) goto LAB_004567f5;
                        FUN_00472f10(local_6c,&DAT_004a2e10,local_7c);
                        iVar4 = __strcmpi(local_7c,&DAT_004a2e14);
                        if (iVar4 == 0) {
                          local_80 = FUN_00472f10(local_6c,s__s__s_004a2e1c,local_7c,
                                                  (void *)((int)in_ECX +
                                                          *(short *)((int)in_ECX + 0xa20) * 9));
                          if (local_80 != 2) {
                            thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2e30,0x122,
                                               s_numargs__2_004a2e24,local_6c);
                          }
                          *(undefined1 *)((int)in_ECX + *(short *)((int)in_ECX + 0xa20) * 9 + 8) = 0
                          ;
                          uVar3 = thunk_FUN_0040ebde((void *)((int)in_ECX +
                                                             *(short *)((int)in_ECX + 0xa20) * 9));
                          *(undefined2 *)((int)in_ECX + *(short *)((int)in_ECX + 0xa20) * 2 + 0x360)
                               = uVar3;
                          *(short *)((int)in_ECX + 0xa20) = *(short *)((int)in_ECX + 0xa20) + 1;
                        }
                        iVar4 = __strcmpi(local_7c,s_SHAPE_004a2e4c);
                        if (iVar4 != 0) break;
                        local_80 = FUN_00472f10(local_6c,s__s__s_004a2e54,local_7c,local_94);
                        if (local_80 != 2) {
                          thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2e68,299,
                                             s_numargs__2_004a2e5c,local_6c);
                        }
                        uVar3 = thunk_FUN_0040ebde(local_94);
                        *(undefined2 *)((int)in_ECX + *(short *)((int)in_ECX + 0xa20) * 2 + 0x35e) =
                             uVar3;
                      }
                      iVar4 = __strcmpi(local_7c,&DAT_004a2e84);
                      if (iVar4 != 0) break;
                      local_80 = FUN_00472f10(local_6c,s__s__d__d__d_004a2e8c,local_7c,local_a8,
                                              local_ac,local_b0);
                      if (local_80 < 3) {
                        thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2ea4,0x131,
                                           s_numargs>_3_004a2e98,local_6c);
                      }
                      pcVar1 = (char *)((int)in_ECX + *(short *)((int)in_ECX + 0xb42) * 3 + 0xa22);
                      *pcVar1 = (char)local_a8._0_4_ + -1;
                      pcVar1[1] = local_ac[0] + -1;
                      pcVar1[2] = '\0';
                      if (3 < local_80) {
                        pcVar1[2] = (byte)local_b0[0];
                      }
                      *(undefined2 *)
                       ((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x420) =
                           *(undefined2 *)((int)in_ECX + 0xb42);
                      *(short *)((int)in_ECX + 0xb42) = *(short *)((int)in_ECX + 0xb42) + 1;
                    }
                    iVar4 = __strcmpi(local_7c,&DAT_004a2ec0);
                    if (iVar4 != 0) break;
                    local_80 = FUN_00472f10(local_6c,s__s__d__d__d__c_004a2ec8,local_7c,local_a8,
                                            local_ac,local_b0,local_84);
                    if (local_80 != 5) {
                      thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2ee4,0x140,
                                         s_numargs__5_004a2ed8,local_6c);
                    }
                    pbVar2 = (byte *)((int)in_ECX + *(short *)((int)in_ECX + 0xc64) * 6 + 0xb44);
                    *pbVar2 = (char)local_a8._0_4_ - 1;
                    pbVar2[1] = local_ac[0] - 1;
                    pbVar2[2] = (byte)local_b0[0];
                    iVar4 = FUN_00477b60((int)local_84[0]);
                    pbVar2[3] = iVar4 == 0x50;
                    if (pbVar2[3] == 0) {
                      *(ushort *)(pbVar2 + 4) = ((ushort)pbVar2[1] - (ushort)*pbVar2) + 1;
                    }
                    else {
                      *(ushort *)(pbVar2 + 4) = ((ushort)pbVar2[1] - (ushort)*pbVar2) * 2;
                    }
                    *(ushort *)(pbVar2 + 4) = *(short *)(pbVar2 + 4) * (ushort)pbVar2[2];
                    *(undefined2 *)
                     ((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x422) =
                         *(undefined2 *)((int)in_ECX + 0xc64);
                    *(short *)((int)in_ECX + 0xc64) = *(short *)((int)in_ECX + 0xc64) + 1;
                  }
                  iVar4 = __strcmpi(local_7c,&DAT_004a2f00);
                  if (iVar4 != 0) break;
                  local_80 = FUN_00472f10(local_6c,s__s__d__d_004a2f08,local_7c,local_a8,local_ac);
                  if (local_80 != 3) {
                    thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2f20,0x155,
                                       s_numargs__3_004a2f14,local_6c);
                  }
                  pbVar2 = (byte *)((int)in_ECX + *(short *)((int)in_ECX + 0xd66) * 4 + 0xc66);
                  *pbVar2 = (char)local_a8._0_4_ - 1;
                  pbVar2[1] = local_ac[0] - 1;
                  *(ushort *)(pbVar2 + 2) = ((ushort)pbVar2[1] - (ushort)*pbVar2) * 4 + 4;
                  *(undefined2 *)
                   ((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x424) =
                       *(undefined2 *)((int)in_ECX + 0xd66);
                  *(short *)((int)in_ECX + 0xd66) = *(short *)((int)in_ECX + 0xd66) + 1;
                }
                iVar4 = __strcmpi(local_7c,&DAT_004a2f3c);
                if (iVar4 != 0) break;
                local_80 = FUN_00472f10(local_6c,s__s__d__d__d__c__d_004a2f44,local_7c,local_a8,
                                        local_ac,local_b0,local_84,local_b4);
                if (local_80 != 6) {
                  thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2f64,0x164,
                                     s_numargs__6_004a2f58,local_6c);
                }
                pbVar2 = (byte *)((int)in_ECX + *(short *)((int)in_ECX + 0xe68) * 8 + 0xd68);
                *pbVar2 = (char)local_a8._0_4_ - 1;
                pbVar2[1] = local_ac[0] - 1;
                pbVar2[2] = (byte)local_b0[0];
                iVar4 = FUN_00477b60((int)local_84[0]);
                pbVar2[3] = iVar4 == 0x50;
                pbVar2[4] = (byte)local_b4[0];
                if (pbVar2[3] == 0) {
                  *(ushort *)(pbVar2 + 6) = ((ushort)pbVar2[1] - (ushort)*pbVar2) + 1;
                }
                else {
                  *(ushort *)(pbVar2 + 6) = ((ushort)pbVar2[1] - (ushort)*pbVar2) * 2;
                }
                *(ushort *)(pbVar2 + 6) = *(short *)(pbVar2 + 6) * (ushort)pbVar2[2];
                *(undefined2 *)((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x426)
                     = *(undefined2 *)((int)in_ECX + 0xe68);
                *(short *)((int)in_ECX + 0xe68) = *(short *)((int)in_ECX + 0xe68) + 1;
              }
              iVar4 = __strcmpi(local_7c,&DAT_004a2f80);
              if (iVar4 != 0) break;
              local_80 = FUN_00472f10(local_6c,s__s__d__d__d__c__d__d__d_004a2f88,local_7c,local_a8,
                                      local_ac,local_b0,local_84,local_b4,&local_b8,local_bc);
              if (local_80 != 8) {
                thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2fac,0x17b,s_numargs__8_004a2fa0,
                                   local_6c);
              }
              pbVar2 = (byte *)((int)in_ECX + *(short *)((int)in_ECX + 0xefa) * 0xc + 0xe6a);
              *pbVar2 = (char)local_a8._0_4_ - 1;
              pbVar2[1] = local_ac[0] - 1;
              pbVar2[2] = (byte)local_b0[0];
              iVar4 = FUN_00477b60((int)local_84[0]);
              pbVar2[3] = iVar4 == 0x50;
              *(short *)(pbVar2 + 8) = local_b4[0] + -1;
              *(undefined2 *)(pbVar2 + 4) = (undefined2)local_b8;
              *(undefined2 *)(pbVar2 + 6) = local_bc[0];
              if (pbVar2[3] == 0) {
                *(ushort *)(pbVar2 + 10) = ((ushort)pbVar2[1] - (ushort)*pbVar2) + 1;
              }
              else {
                *(ushort *)(pbVar2 + 10) = ((ushort)pbVar2[1] - (ushort)*pbVar2) * 2;
              }
              *(ushort *)(pbVar2 + 10) = *(short *)(pbVar2 + 10) * (ushort)pbVar2[2];
              *(undefined2 *)((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x428) =
                   *(undefined2 *)((int)in_ECX + 0xefa);
              *(short *)((int)in_ECX + 0xefa) = *(short *)((int)in_ECX + 0xefa) + 1;
            }
            iVar4 = __strcmpi(local_7c,&DAT_004a2fc8);
            if (iVar4 != 0) break;
            local_80 = FUN_00472f10(local_6c,s__s__d__d__d__c__d__d__d__d__s_004a2fd0,local_7c,
                                    local_a8,local_ac,local_b0,local_84,local_b4,&local_b8,local_bc,
                                    local_8,local_94);
            if (local_80 < 9) {
              thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a2ffc,0x194,s_numargs>_9_004a2ff0,
                                 local_6c);
            }
            pbVar2 = (byte *)((int)in_ECX + *(short *)((int)in_ECX + 0x10fc) * 0x10 + 0xefc);
            *pbVar2 = (char)local_a8._0_4_ - 1;
            pbVar2[1] = local_ac[0] - 1;
            pbVar2[2] = (byte)local_b0[0];
            iVar4 = FUN_00477b60((int)local_84[0]);
            pbVar2[3] = iVar4 == 0x50;
            *(short *)(pbVar2 + 10) = local_b4[0] + -1;
            iVar4 = local_b8 + -1;
            *(undefined2 *)(pbVar2 + 6) = local_bc[0];
            *(undefined2 *)(pbVar2 + 8) = local_8[0];
            pbVar2[0xe] = 0xff;
            pbVar2[0xf] = 0xff;
            if (9 < local_80) {
              uVar3 = thunk_FUN_00415f1e(local_94);
              *(undefined2 *)(pbVar2 + 0xe) = uVar3;
            }
            pbVar2[4] = 0xff;
            pbVar2[5] = 0xff;
            if (iVar4 != -1) {
              *(ushort *)(pbVar2 + 4) = ((short)iVar4 - (ushort)*pbVar2) * (ushort)pbVar2[2];
            }
            if (pbVar2[3] == 0) {
              local_dc = ((ushort)pbVar2[1] - (ushort)*pbVar2) + 1;
            }
            else {
              local_dc = ((ushort)pbVar2[1] - (ushort)*pbVar2) * 2;
            }
            local_dc = local_dc * (ushort)pbVar2[2];
            *(short *)(pbVar2 + 0xc) = local_dc;
            *(undefined2 *)((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x42a) =
                 *(undefined2 *)((int)in_ECX + 0x10fc);
            *(short *)((int)in_ECX + 0x10fc) = *(short *)((int)in_ECX + 0x10fc) + 1;
          }
          iVar4 = __strcmpi(local_7c,&DAT_004a3018);
          if (iVar4 != 0) break;
          local_80 = FUN_00472f10(local_6c,s__s__d__d__d__d_004a3020,local_7c,local_a8,local_ac,
                                  local_b0,local_b4);
          if (local_80 < 2) {
            thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a303c,0x1b9,s_numargs>_2_004a3030,
                               local_6c);
          }
          pcVar1 = (char *)((int)in_ECX + *(short *)((int)in_ECX + 0x11be) * 6 + 0x10fe);
          *pcVar1 = (char)local_a8._0_4_ + -1;
          if (4 < local_80) {
            *(undefined2 *)(pcVar1 + 2) = local_b0[0];
            *(undefined2 *)(pcVar1 + 4) = local_b4[0];
          }
          *(undefined2 *)((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x42c) =
               *(undefined2 *)((int)in_ECX + 0x11be);
          *(short *)((int)in_ECX + 0x11be) = *(short *)((int)in_ECX + 0x11be) + 1;
        }
        iVar4 = __strcmpi(local_7c,&DAT_004a3058);
        if (iVar4 != 0) break;
        local_80 = FUN_00472f10(local_6c,s__s__d__d_004a3060,local_7c,local_a8,local_ac);
        if (local_80 != 3) {
          thunk_FUN_00414b91(s_C__float_src_shapeinf_cpp_004a3078,0x1ca,s_numargs__3_004a306c,
                             local_6c);
        }
        *(char *)((int)in_ECX + *(short *)((int)in_ECX + 0x11e0) * 2 + 0x11c0) =
             (char)local_a8._0_4_ + -1;
        *(char *)((int)in_ECX + *(short *)((int)in_ECX + 0x11e0) * 2 + 0x11c1) = local_ac[0] + -1;
        *(undefined2 *)((int)in_ECX + (*(short *)((int)in_ECX + 0xa20) + -1) * 0x10 + 0x42e) =
             *(undefined2 *)((int)in_ECX + 0x11e0);
        *(short *)((int)in_ECX + 0x11e0) = *(short *)((int)in_ECX + 0x11e0) + 1;
      }
      iVar4 = __strcmpi(local_7c,&DAT_004a3094);
    } while (iVar4 != 0);
LAB_004567f5:
    if (0x60 < *(short *)((int)in_ECX + 0xa20)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a30b8,0x1d6,
                         s_mNumItems_<__MAX_BLDSHP_ITEMS_004a3098);
    }
    if (0x10 < *(short *)((int)in_ECX + 0x11e0)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a30ec,0x1d7,
                         s_mNumBarg<_MAX_BARG_ANM_004a30d4);
    }
    if (0x60 < *(short *)((int)in_ECX + 0xb42)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a3120,0x1d8,
                         s_mNumBase<_MAX_BASE_ANM_004a3108);
    }
    if (0x30 < *(short *)((int)in_ECX + 0xc64)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a3154,0x1d9,
                         s_mNumChug<_MAX_CHUG_ANM_004a313c);
    }
    if (0xc < *(short *)((int)in_ECX + 0xefa)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a3188,0x1da,
                         s_mNumCons<_MAX_CONS_ANM_004a3170);
    }
    if (0x40 < *(short *)((int)in_ECX + 0xd66)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a31bc,0x1db,
                         s_mNumGlyp<_MAX_GLYP_ANM_004a31a4);
    }
    if (0x20 < *(short *)((int)in_ECX + 0xe68)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a31f0,0x1dc,
                         s_mNumInci<_MAX_INCI_ANM_004a31d8);
    }
    if (0x20 < *(short *)((int)in_ECX + 0x11be)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a3224,0x1dd,
                         s_mNumOccu<_MAX_OCCU_ANM_004a320c);
    }
    if (0x20 < *(short *)((int)in_ECX + 0x10fc)) {
      thunk_FUN_00414b64(s_C__float_src_shapeinf_cpp_004a3258,0x1de,
                         s_mNumProd<_MAX_PROD_ANM_004a3240);
    }
    uVar5 = 1;
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}
```

---

## FUN_00456a13 — 0x456a13

- Classification : internal
- Corps : `0x456a13–0x456a6a`
- État : pseudocode obtenu
- Evidence : `ev_fb6d0c4daa51eaf949b8f18e16e038d10f01fe5b1afd5097a071f38cef255a2a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x48b100` — `__strcmpi`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00456a13(char *param_1)

{
  int iVar1;
  int in_ECX;
  uint local_8;
  
  local_8 = 0;
  while( true ) {
    if ((int)*(short *)(in_ECX + 0xa20) <= (int)local_8) {
      return 0xffff;
    }
    iVar1 = __strcmpi(param_1,(char *)(in_ECX + local_8 * 9));
    if (iVar1 == 0) break;
    local_8 = local_8 + 1;
  }
  return local_8 & 0xffff;
}
```

---


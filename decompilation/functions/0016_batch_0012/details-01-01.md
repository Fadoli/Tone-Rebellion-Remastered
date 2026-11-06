# 0016_batch_0012 — détails (1/4)

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

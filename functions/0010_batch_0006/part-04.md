# 0010_batch_0006 — détails (4/8)

## FUN_0041d19d — 0x41d19d

- Classification : internal
- Corps : `0x41d19d–0x41d64d`
- État : pseudocode obtenu
- Evidence : `ev_a4d00f397b10ddd5f9e8450e88d33825e40a624c6b54a2e49736d00567ca318c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x402027` — `thunk_FUN_0042cbda`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472da0` — `FUN_00472da0`
- `0x472f10` — `FUN_00472f10`
- `0x477030` — `FUN_00477030`
- `0x4771b0` — `FUN_004771b0`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x49cc30` — "float.cfg"
- `0x49cc30` — "float.cfg"
- `0x49cc3c` — "%s %s"
- `0x49cc44` — "draw_method"
- `0x49cc50` — "nevada"
- `0x49cc58` — "frame_limit"
- `0x49cc64` — "sound_on"
- `0x49cc70` — "net_name"
- `0x49cc7c` — "quiet_click"
- `0x49cc88` — "no_template"
- `0x49cc94` — "network"
- `0x49cc9c` — "alloc_test"
- `0x49cca8` — "gamma"
- `0x49ccb8` — "partners"
- `0x49ccc4` — "easyplot"
- `0x49ccd0` — "easyunlock"
- `0x49ccdc` — "hdmusic"
- `0x49cce4` — "temphole"
- `0x49ccf0` — "holecolor"
- `0x49ccfc` — "simplesound"
- `0x49cd08` — "blomster"
- `0x49cd14` — "multispeed"
- `0x49cd20` — "island"
- `0x49cd28` — "medley"
- `0x49cd30` — "runback"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0041d19d(char *param_1)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  char local_d8 [20];
  undefined1 local_c4 [80];
  undefined1 local_74 [112];
  
  if ((param_1 == (char *)0x0) || (*param_1 == '\0')) {
    param_1 = s_float_cfg_0049cc30;
  }
  iVar1 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,20000);
  if (iVar1 == 0) {
    while (iVar1 = thunk_FUN_0040f5b3(local_74,0), iVar1 == 0) {
      iVar1 = FUN_00472f10(local_74,s__s__s_0049cc3c,local_d8,local_c4);
      iVar2 = __strcmpi(local_d8,s_draw_method_0049cc44);
      if ((iVar2 == 0) && (iVar1 == 2)) {
        iVar1 = FUN_004771b0(local_c4);
        DAT_004c2b84 = (uint)(iVar1 == 5);
        DAT_0049c9b4 = FUN_004771b0(local_c4);
      }
      else {
        iVar2 = __strcmpi(local_d8,s_nevada_0049cc50);
        if (iVar2 == 0) {
          DAT_004c2b74 = 1;
        }
        else {
          iVar2 = __strcmpi(local_d8,s_frame_limit_0049cc58);
          if ((iVar2 == 0) && (iVar1 == 2)) {
            DAT_004c2b60 = FUN_004771b0(local_c4);
          }
          else {
            iVar2 = __strcmpi(local_d8,s_sound_on_0049cc64);
            if (iVar2 == 0) {
              DAT_004c2b80 = 1;
            }
            else {
              iVar2 = __strcmpi(local_d8,s_net_name_0049cc70);
              if ((iVar2 == 0) && (iVar1 == 2)) {
                FUN_00472da0(&DAT_0049c9b8,local_c4);
              }
              else {
                iVar2 = __strcmpi(local_d8,s_quiet_click_0049cc7c);
                if (iVar2 == 0) {
                  DAT_0049c994 = 0;
                }
                else {
                  iVar2 = __strcmpi(local_d8,s_no_template_0049cc88);
                  if (iVar2 == 0) {
                    _DAT_0049c998 = 0;
                  }
                  else {
                    iVar2 = __strcmpi(local_d8,s_network_0049cc94);
                    if (iVar2 == 0) {
                      DAT_004c2b88 = 1;
                    }
                    else {
                      iVar2 = __strcmpi(local_d8,s_alloc_test_0049cc9c);
                      if (iVar2 == 0) {
                        DAT_004c2b90 = 1;
                      }
                      else {
                        iVar2 = __strcmpi(local_d8,s_gamma_0049cca8);
                        if ((iVar2 == 0) && (iVar1 == 2)) {
                          fVar3 = (float10)FUN_00477030(local_c4);
                          thunk_FUN_0042cbda((float)fVar3,(float)fVar3);
                        }
                        else {
                          iVar2 = __strcmpi(local_d8,&DAT_0049ccb0);
                          if (iVar2 == 0) {
                            DAT_004c2b98 = 1;
                          }
                          else {
                            iVar2 = __strcmpi(local_d8,s_partners_0049ccb8);
                            if (iVar2 == 0) {
                              DAT_004c2b9c = 1;
                            }
                            else {
                              iVar2 = __strcmpi(local_d8,s_easyplot_0049ccc4);
                              if (iVar2 == 0) {
                                DAT_0049c99c = 0;
                              }
                              else {
                                iVar2 = __strcmpi(local_d8,s_easyunlock_0049ccd0);
                                if (iVar2 == 0) {
                                  DAT_004c2ba0 = 1;
                                }
                                else {
                                  iVar2 = __strcmpi(local_d8,s_hdmusic_0049ccdc);
                                  if (iVar2 == 0) {
                                    DAT_004c2ba4 = 1;
                                  }
                                  else {
                                    iVar2 = __strcmpi(local_d8,s_temphole_0049cce4);
                                    if (iVar2 == 0) {
                                      DAT_004c2bac = 1;
                                    }
                                    else {
                                      iVar2 = __strcmpi(local_d8,s_holecolor_0049ccf0);
                                      if ((iVar2 == 0) && (iVar1 == 2)) {
                                        DAT_004c2b08 = FUN_004771b0(local_c4);
                                      }
                                      else {
                                        iVar2 = __strcmpi(local_d8,s_simplesound_0049ccfc);
                                        if (iVar2 == 0) {
                                          DAT_004c2bc8 = 1;
                                        }
                                        else {
                                          iVar2 = __strcmpi(local_d8,s_blomster_0049cd08);
                                          if (iVar2 == 0) {
                                            DAT_004c2bb0 = 1;
                                          }
                                          else {
                                            iVar2 = __strcmpi(local_d8,s_multispeed_0049cd14);
                                            if (iVar2 == 0) {
                                              DAT_004c2bb4 = 1;
                                            }
                                            else {
                                              iVar2 = __strcmpi(local_d8,s_island_0049cd20);
                                              if ((iVar2 == 0) && (iVar1 == 2)) {
                                                DAT_0049c9b0 = FUN_004771b0(local_c4);
                                              }
                                              else {
                                                iVar2 = __strcmpi(local_d8,s_medley_0049cd28);
                                                if ((iVar2 == 0) && (iVar1 == 2)) {
                                                  DAT_004c2ba8 = 1;
                                                  FUN_00472da0(&DAT_004c2ab8,local_c4);
                                                }
                                                else {
                                                  iVar1 = __strcmpi(local_d8,s_runback_0049cd30);
                                                  if (iVar1 == 0) {
                                                    DAT_004c2bb8 = 1;
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
  }
  return;
}
```

---

## FUN_0041d64e — 0x41d64e

- Classification : internal
- Corps : `0x41d64e–0x41d70c`
- État : pseudocode obtenu
- Evidence : `ev_187d22e0d18c68faf0861e12bda0956428befb83a667937aa0ced1976eed0ea5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x78` — `ADVAPI32.DLL::RegOpenKeyExA`
- `EXTERNAL:0x79` — `ADVAPI32.DLL::RegQueryValueExA`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49cd3c` — "Software\\The Logic Factory\\Tone Rebellion"
- `0x49cd68` — "%s\\%s"
- `0x49cd70` — "DEBUG: Registry info not found."
- `0x49cd90` — "cdrom"
- `0x49cd98` — "ERROR: CDROM info missing in registry"

### Pseudocode Ghidra

```c
void FUN_0041d64e(void)

{
  CHAR local_64 [80];
  LSTATUS local_14;
  HKEY local_10;
  DWORD local_c [2];
  
  FUN_00472ca0(local_64,s__s__s_0049cd68,s_Software_The_Logic_Factory_Tone_R_0049cd3c,&DAT_0049cd38)
  ;
  local_14 = RegOpenKeyExA((HKEY)0x80000002,local_64,0,0xf003f,&local_10);
  if (local_14 == 0) {
    local_c[0] = 1;
    local_c[1] = 10;
    local_14 = RegQueryValueExA(local_10,s_cdrom_0049cd90,(LPDWORD)0x0,local_c,&DAT_004c2aa8,
                                local_c + 1);
    if ((local_14 != 0) &&
       (thunk_FUN_00414ad0(s_ERROR__CDROM_info_missing_in_reg_0049cd98), DAT_004c2ba4 == 0)) {
      DAT_004c2b80 = 0;
    }
  }
  else {
    thunk_FUN_00414ad0(s_DEBUG__Registry_info_not_found__0049cd70);
    if (DAT_004c2ba4 == 0) {
      DAT_004c2b80 = 0;
    }
  }
  return;
}
```

---

## FUN_0041d70d — 0x41d70d

- Classification : internal
- Corps : `0x41d70d–0x41d8e0`
- État : pseudocode obtenu
- Evidence : `ev_b765d704b9b04a47f1cc07ea19409dcd140e8aadd2232363e5685731bec68576`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x4737e0` — `_strncpy`

### Chaînes référencées

- `0x49cdc0` — "FALSE"
- `0x49cdc8` — "C:\\float\\src\\float.cpp"
- `0x49cfc8` — "xTark"
- `0x49d008` — "xTarks"
- `0x4a4870` — "xTarzus"
- `0x4a4a50` — "xSpores"

### Pseudocode Ghidra

```c
void FUN_0041d70d(undefined4 param_1)

{
  int iVar1;
  int local_88;
  char local_84 [128];
  
  iVar1 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,39000);
  if (iVar1 != 0) {
    thunk_FUN_00414b64(s_C__float_src_float_cpp_0049cdc8,0x3f4,s_FALSE_0049cdc0);
  }
  for (local_88 = 0; local_88 < 5; local_88 = local_88 + 1) {
    thunk_FUN_0040f5b3(local_84,1);
    _strncpy(s_xTark_0049cfc8 + local_88 * 0xc,local_84,0xb);
    (&DAT_0049cfd3)[local_88 * 0xc] = 0;
  }
  for (local_88 = 0; local_88 < 5; local_88 = local_88 + 1) {
    thunk_FUN_0040f5b3(local_84,1);
    _strncpy(s_xTarks_0049d008 + local_88 * 0xc,local_84,0xb);
    (&DAT_0049d013)[local_88 * 0xc] = 0;
  }
  for (local_88 = 0; local_88 < 0xf; local_88 = local_88 + 1) {
    thunk_FUN_0040f5b3(local_84,1);
    _strncpy(s_xTarzus_004a4870 + local_88 * 0x20,local_84,0x1f);
    (&DAT_004a488f)[local_88 * 0x20] = 0;
  }
  for (local_88 = 0; local_88 < 0x12; local_88 = local_88 + 1) {
    thunk_FUN_0040f5b3(local_84,1);
    _strncpy(s_xSpores_004a4a50 + local_88 * 0x10,local_84,0xf);
    (&DAT_004a4a5f)[local_88 * 0x10] = 0;
  }
  return;
}
```

---

## FUN_0041e270 — 0x41e270

- Classification : internal
- Corps : `0x41e270–0x41e28d`
- État : pseudocode obtenu
- Evidence : `ev_748d2f16e9b9f5e7574367a5663a43d469c77c31b02a6763c6da6318f05c4dcc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0041e270(int *param_1)

{
  undefined4 uVar1;
  
  if ((*param_1 < 0) || (4 < *param_1)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}
```

---

## FUN_0041e28e — 0x41e28e

- Classification : internal
- Corps : `0x41e28e–0x41e3ea`
- État : pseudocode obtenu
- Evidence : `ev_667d311b6cd4f6b516c22975cd0e46ce337aa32ce5fe70c0d2ddd040239feb55`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014bf` — `thunk_FUN_00467260`
- `0x472c6c` — `__ftol`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0041e28e(int param_1,short param_2)

{
  undefined4 uVar1;
  int iVar2;
  double adStack_94 [10];
  double local_44;
  int local_3c [11];
  int local_10;
  int local_c;
  undefined2 local_8;
  
  if (param_2 < 1) {
    uVar1 = CONCAT22(param_2 >> 0xf,0xffff);
  }
  else {
    local_8 = 0xffff;
    local_10 = 0;
    local_44 = 0.0;
    for (local_3c[0] = 0; local_3c[0] < param_2; local_3c[0] = local_3c[0] + 1) {
      local_10 = local_10 + *(int *)(param_1 + local_3c[0] * 4);
    }
    for (local_3c[0] = 0; local_3c[0] < param_2; local_3c[0] = local_3c[0] + 1) {
      adStack_94[local_3c[0]] = (double)local_10 / (double)*(int *)(param_1 + local_3c[0] * 4);
      local_44 = local_44 + adStack_94[local_3c[0]];
    }
    local_10 = 0;
    for (local_3c[0] = 0; local_3c[0] < param_2; local_3c[0] = local_3c[0] + 1) {
      adStack_94[local_3c[0]] = (1000.0 / local_44) * adStack_94[local_3c[0]];
      local_10 = __ftol();
      local_3c[local_3c[0] + 1] = local_10;
    }
    local_3c[param_2] = 1000;
    local_c = thunk_FUN_00467260(1000);
    local_3c[0] = 0;
    while( true ) {
      iVar2 = (int)param_2;
      if (iVar2 <= local_3c[0]) break;
      if (local_c < local_3c[local_3c[0] + 1]) {
        iVar2 = CONCAT22(param_2 >> 0xf,(undefined2)local_3c[0]);
        local_8 = (undefined2)local_3c[0];
        break;
      }
      local_3c[0] = local_3c[0] + 1;
    }
    uVar1 = CONCAT22((short)((uint)iVar2 >> 0x10),local_8);
  }
  return uVar1;
}
```

---

## FUN_0041e3eb — 0x41e3eb

- Classification : internal
- Corps : `0x41e3eb–0x41e426`
- État : pseudocode obtenu
- Evidence : `ev_8929e443d2038384b5639346ca48bfaf74400aae3dcaeea6a8d9a774c872a388`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0041e3eb(short param_1,short param_2)

{
  int iVar1;
  
  iVar1 = (param_2 + 5) / 10;
  return CONCAT22((short)((uint)iVar1 >> 0x10),(ushort)((param_1 + 5) / 10 << 8) | (ushort)iVar1);
}
```

---

## FUN_0041e427 — 0x41e427

- Classification : internal
- Corps : `0x41e427–0x41e453`
- État : pseudocode obtenu
- Evidence : `ev_73084086e66c1221b083ee7fab1bd83e50fe565c7e7792780b346e397b17cd42`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041e427(ushort param_1,short *param_2,short *param_3)

{
  *param_2 = (param_1 >> 8) * 10;
  *param_3 = (param_1 & 0xff) * 10;
  return;
}
```

---

## FUN_0041e454 — 0x41e454

- Classification : internal
- Corps : `0x41e454–0x41e4c2`
- État : pseudocode obtenu
- Evidence : `ev_516df530870cffc769dce043e9a8c1b1b8c1f94b19f0c02801576769f23972ae`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0041e454(int param_1)

{
  undefined4 local_8;
  
  if ((((*(short *)(param_1 + 0x10) == 6) || (*(short *)(param_1 + 0x10) == 0xd)) ||
      ((*(short *)(param_1 + 0x10) == 4 &&
       ((4 < *(short *)(param_1 + 0x12) && (*(short *)(param_1 + 0x12) < 0x22)))))) ||
     ((*(short *)(param_1 + 0x10) == 0xb || (*(short *)(param_1 + 0x10) == 0x11)))) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  return local_8;
}
```

---

## FUN_0041e4c3 — 0x41e4c3

- Classification : internal
- Corps : `0x41e4c3–0x41e4d8`
- État : pseudocode obtenu
- Evidence : `ev_909c86d7e5beeb6c56e239a696f6674e0d0a06e79b0b871c7d32ff8eede7db65`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012c1` — `thunk_FUN_0041e4e4`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0041e4c3(void)

{
  undefined4 in_ECX;
  
  thunk_FUN_0041e4e4();
  return in_ECX;
}
```

---

## FUN_0041e4d9 — 0x41e4d9

- Classification : internal
- Corps : `0x41e4d9–0x41e4e3`
- État : pseudocode obtenu
- Evidence : `ev_ba02dc42419fe4d9b404370bb4ce877d13fe06c60f8e545e14a97b80b68fc08a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041e4d9(void)

{
  return;
}
```

---

## FUN_0041e4e4 — 0x41e4e4

- Classification : internal
- Corps : `0x41e4e4–0x41e568`
- État : pseudocode obtenu
- Evidence : `ev_a5f6ff6cbb1d9a1b23aa8807337444803e3415de869ec691acf503f150bb3523`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041e4e4(void)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x12) = 0;
  *(undefined2 *)(in_ECX + 0x10) = 0;
  *(undefined2 *)(in_ECX + 0x2a) = 0;
  *(undefined2 *)(in_ECX + 0x28) = 0;
  *(undefined2 *)(in_ECX + 8) = 0;
  *(undefined4 *)(in_ECX + 0x18) = 0;
  *(undefined4 *)(in_ECX + 0x1c) = 0;
  *(undefined2 *)(in_ECX + 0xc) = 0xffff;
  *(undefined4 *)(in_ECX + 0x3c) = 0;
  *(undefined4 *)(in_ECX + 0x38) = 0xffffffff;
  *(undefined2 *)(in_ECX + 0x40) = 0xffff;
  *(undefined4 *)(in_ECX + 0x2c) = 0;
  *(undefined2 *)(in_ECX + 0x48) = 0xffff;
  return;
}
```

---


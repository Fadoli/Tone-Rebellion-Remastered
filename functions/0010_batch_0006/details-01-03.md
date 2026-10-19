# 0010_batch_0006 — détails (3/3)

## FUN_0041760b — 0x41760b

- Classification : internal
- Corps : `0x41760b–0x417ee7`
- État : pseudocode obtenu
- Evidence : `ev_141765fef58a58c98b642e7d5a175b9e00d9fe52237a02f7d44ea6fc875699c7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012a8` — `thunk_FUN_0041521a`
- `0x4013e8` — `thunk_FUN_00415f1e`
- `0x40140b` — `thunk_FUN_00416e7d`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x4017ee` — `thunk_FUN_004239e9`
- `0x401951` — `thunk_FUN_00415063`
- `0x40250e` — `thunk_FUN_00414fbf`

### Chaînes référencées

- `0x49c3d0` — "upgrade"
- `0x49c3d0` — "upgrade"
- `0x49c3d8` — "freezelb"
- `0x49c3d8` — "freezelb"
- `0x49c3e4` — "locprot"
- `0x49c3e4` — "locprot"
- `0x49c3ec` — "buildton"
- `0x49c3ec` — "buildton"
- `0x49c3f8` — "hyperheal"
- `0x49c3f8` — "hyperheal"
- `0x49c404` — "hyperheal"
- `0x49c404` — "hyperheal"
- `0x49c410` — "fltarmor"
- `0x49c410` — "fltarmor"
- `0x49c41c` — "repair"
- `0x49c41c` — "repair"
- `0x49c424` — "revplot"
- `0x49c424` — "revplot"
- `0x49c42c` — "fastflt"
- `0x49c42c` — "fastflt"
- `0x49c434` — "freezesc"
- `0x49c434` — "freezesc"
- `0x49c440` — "freezesc"
- `0x49c440` — "freezesc"
- `0x49c44c` — "blastwb"
- `0x49c44c` — "blastwb"
- `0x49c454` — "stockup"
- `0x49c454` — "stockup"
- `0x49c45c` — "bldarmor"
- `0x49c45c` — "bldarmor"
- `0x49c468` — "locprot"
- `0x49c468` — "locprot"
- `0x49c470` — "buildton"
- `0x49c470` — "buildton"
- `0x49c47c` — "hyperheal"
- `0x49c47c` — "hyperheal"
- `0x49c488` — "farobt"
- `0x49c490` — "blastwb"
- `0x49c498` — "killbeas"

### Pseudocode Ghidra

```c
void FUN_0041760b(short param_1)

{
  bool bVar1;
  short sVar2;
  int in_ECX;
  int iVar3;
  undefined2 local_30 [2];
  undefined2 local_2c [2];
  int local_28;
  undefined4 *local_24;
  char *local_20;
  int local_1c;
  char *local_18;
  undefined4 *local_14;
  int local_10;
  uint local_c;
  short *local_8;
  
  local_8 = (short *)(in_ECX + 0x1202 + param_1 * 0x14);
  local_10 = in_ECX + local_8[7] * 0x30;
  local_c = 0;
  iVar3 = *local_8 * 0x4c;
  local_14 = &DAT_006137b8 + *local_8 * 0x13;
  switch(*(undefined2 *)(&DAT_006137e8 + iVar3)) {
  case 0:
  case 1:
  case 3:
  case 4:
  case 5:
  case 6:
  case 9:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xf:
  case 0x13:
    if ((local_8[8] & 0x100U) == 0) {
      if ((local_8[8] & 0x200U) == 0) {
        if (((local_8[8] & 0x400U) != 0) && (DAT_00618e44 % 2 != 0)) {
          if (*(short *)(&DAT_006137e8 + iVar3) == 0x13) {
            local_8[3] = local_8[3] + -1;
            bVar1 = local_8[3] < *(short *)(local_10 + 0x14);
            if (bVar1) {
              thunk_FUN_004239e9();
            }
            local_c = (uint)bVar1;
          }
          else {
            if (((*(short *)(&DAT_006137e8 + iVar3) == 5) ||
                (*(short *)(&DAT_006137e8 + iVar3) == 6)) ||
               (*(short *)(&DAT_006137e8 + iVar3) == 9)) {
              sVar2 = *(short *)(local_10 + 0x1e);
            }
            else {
              sVar2 = *(short *)(local_10 + 0x1c);
            }
            local_28 = (int)sVar2;
            local_8[3] = local_8[3] + 1;
            if (local_28 < local_8[3]) {
              if (*(short *)(&DAT_006137e8 + iVar3) == 1) {
                thunk_FUN_00414fbf(local_8,local_2c,local_30);
                *(undefined2 *)(local_14 + 10) = local_2c[0];
                *(undefined2 *)((int)local_14 + 0x2a) = local_30[0];
              }
              thunk_FUN_004239e9();
              local_c = 1;
            }
          }
        }
      }
      else {
        local_1c = thunk_FUN_0041521a(local_10,local_8);
        if (local_1c < 6) {
          local_20 = s_hyperheal_0049c404;
          iVar3 = *local_8 * 0x4c;
          local_24 = &DAT_006137b8 + *local_8 * 0x13;
          if (*(short *)(&DAT_006137e8 + iVar3) == 1) {
            local_20 = s_fltarmor_0049c410;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 0) {
            local_20 = s_repair_0049c41c;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 0xb) {
            local_20 = s_revplot_0049c424;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 0xc) {
            local_20 = s_fastflt_0049c42c;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 0xd) {
            local_20 = s_freezesc_0049c434;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 0x13) {
            local_20 = s_freezesc_0049c440;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 0xf) {
            local_20 = s_blastwb_0049c44c;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 3) {
            local_20 = s_stockup_0049c454;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 4) {
            local_20 = s_bldarmor_0049c45c;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 5) {
            local_20 = s_locprot_0049c468;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 6) {
            local_20 = s_buildton_0049c470;
          }
          else if (*(short *)(&DAT_006137e8 + iVar3) == 9) {
            local_20 = s_hyperheal_0049c47c;
          }
          sVar2 = thunk_FUN_00415f1e(local_20);
          local_8[7] = sVar2;
          local_10 = in_ECX + local_8[7] * 0x30;
          local_8[8] = 0;
          local_8[8] = local_8[8] | 2;
          local_8[8] = local_8[8] | 0x400;
          if (*(short *)(local_24 + 0xc) == 0x13) {
            local_8[3] = *(short *)(local_10 + 0x1c);
          }
          else {
            local_8[3] = *(short *)(local_10 + 0x14);
          }
          if (((*(short *)(local_24 + 0xc) == 5) || (*(short *)(local_24 + 0xc) == 6)) ||
             (*(short *)(local_24 + 0xc) == 9)) {
            local_8[2] = 1;
            local_8[3] = *(short *)(local_10 + 0x16);
          }
          else {
            local_8[2] = 0;
          }
        }
      }
    }
    else {
      thunk_FUN_00415063(local_10,local_8);
      if ((local_8[8] & 0x20U) != 0) {
        local_18 = s_upgrade_0049c3d0;
        if (*(short *)(local_14 + 0xc) == 1) {
          local_18 = s_freezelb_0049c3d8;
        }
        else if (*(short *)(local_14 + 0xc) == 5) {
          local_18 = s_locprot_0049c3e4;
        }
        else if (*(short *)(local_14 + 0xc) == 6) {
          local_18 = s_buildton_0049c3ec;
        }
        else if (*(short *)(local_14 + 0xc) == 9) {
          local_18 = s_hyperheal_0049c3f8;
        }
        sVar2 = thunk_FUN_00415f1e(local_18);
        local_8[7] = sVar2;
        local_10 = in_ECX + local_8[7] * 0x30;
        local_8[8] = 0;
        local_8[8] = local_8[8] | 2;
        local_8[8] = local_8[8] | 0x200;
        local_8[2] = 0;
        local_8[3] = *(short *)(local_10 + 0x14);
      }
    }
    break;
  case 2:
  case 0xe:
  case 0x11:
  case 0x14:
  case 0x15:
  case 0x16:
    thunk_FUN_00415063(local_10,local_8);
    if ((local_8[8] & 0x20U) != 0) {
      thunk_FUN_004239e9();
      local_c = 1;
    }
    break;
  case 7:
  case 0x12:
    if ((local_8[8] & 0x100U) == 0) {
      if (((local_8[8] & 0x200U) != 0) &&
         (thunk_FUN_00415063(local_10,local_8), (local_8[8] & 0x20U) != 0)) {
        thunk_FUN_004239e9();
        local_c = 1;
      }
    }
    else {
      thunk_FUN_00415063(local_10,local_8);
      if ((local_8[8] & 0x20U) != 0) {
        sVar2 = thunk_FUN_00415f1e(s_blastwb_0049c490);
        local_8[7] = sVar2;
        local_10 = in_ECX + local_8[7] * 0x30;
        local_8[8] = 0;
        local_8[8] = local_8[8] | 2;
        local_8[8] = local_8[8] | 0x200;
        local_8[2] = 0;
        local_8[3] = *(short *)(local_10 + 0x14);
      }
    }
    break;
  case 8:
    if ((local_8[8] & 0x100U) == 0) {
      local_8[5] = local_8[5] + 1;
      if (local_8[5] == 0x44) {
        local_8[2] = *(short *)(&DAT_005ec664 + local_8[1] * 0x60 + local_8[4] * 0x29e8);
        thunk_FUN_004239e9();
      }
      else if (local_8[5] == 0x7a) {
        local_c = 1;
      }
    }
    else {
      thunk_FUN_00415063(local_10,local_8);
      if ((local_8[8] & 0x20U) != 0) {
        sVar2 = thunk_FUN_00415f1e(s_farobt_0049c488);
        local_8[7] = sVar2;
        local_10 = in_ECX + local_8[7] * 0x30;
        local_8[4] = (short)(char)((ushort)*(undefined2 *)((int)local_14 + 0x32) >> 8);
        local_8[1] = *(ushort *)((int)local_14 + 0x32) & 0xff;
        local_8[5] = 0;
        local_8[6] = *(short *)((int)local_14 + 0x12);
        local_8[8] = 0;
        local_8[8] = local_8[8] | 2;
        local_8[2] = -1;
        local_8[3] = *(short *)(local_10 + 0x14);
      }
    }
    break;
  case 10:
    if ((local_8[8] & 0x100U) == 0) {
      local_8[5] = local_8[5] + 1;
      local_8[6] = local_8[6] + 1;
      local_8[3] = local_8[3] + 1;
      if (((0x4b < local_8[5]) && (0x4b < local_8[6])) && (0x4b < local_8[3])) {
        thunk_FUN_004239e9();
        local_c = 1;
      }
    }
    else {
      sVar2 = thunk_FUN_00415f1e(s_killbeas_0049c498);
      local_8[7] = sVar2;
      local_10 = in_ECX + local_8[7] * 0x30;
      sVar2 = thunk_FUN_00467260(0x1e);
      local_8[5] = -sVar2;
      sVar2 = thunk_FUN_00467260(0x1e);
      local_8[6] = -sVar2;
      local_8[8] = 0;
      sVar2 = thunk_FUN_00467260(8);
      local_8[2] = sVar2;
      sVar2 = thunk_FUN_00467260(0x1e);
      local_8[3] = -sVar2;
    }
    break;
  case 0x10:
    if ((*(short *)(local_10 + 0x1c) < local_8[3]) || (DAT_00618e44 % 2 == 0)) {
      if (*(short *)(local_10 + 0x1e) < local_8[3]) {
        if (DAT_00618e44 % 2 != 0) {
          local_8[3] = local_8[3] + 1;
        }
        if (*(short *)(local_10 + 0x20) < local_8[3]) {
          thunk_FUN_004239e9();
          local_c = 1;
        }
      }
      else {
        local_8[2] = 1;
        iVar3 = thunk_FUN_0041521a(local_10,local_8);
        if (iVar3 < 6) {
          local_8[3] = *(short *)(local_10 + 0x18);
        }
      }
    }
    else {
      local_8[3] = local_8[3] + 1;
    }
  }
  local_8[9] = local_8[9] + 1;
  if (local_c != 0) {
    thunk_FUN_00416e7d(param_1);
  }
  return;
}
```

---

---

## FUN_00417f44 — 0x417f44

- Classification : internal
- Corps : `0x417f44–0x418104`
- État : pseudocode obtenu
- Evidence : `ev_a03c22965475c38a6b6f8b1b595d77f8a389724770e7b7ade71f3ce794092cf7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40140b` — `thunk_FUN_00416e7d`
- `0x40184d` — `thunk_FUN_0045b24d`
- `0x401aaf` — `thunk_FUN_0045afb9`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00417f44(short param_1)

{
  int in_ECX;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_8 = in_ECX + 0x1202 + param_1 * 0x14;
  local_c = in_ECX + *(short *)(local_8 + 0xe) * 0x30;
  if ((*(short *)(local_8 + 0x12) == 0) && (*(short *)(local_c + 0x28) != -1)) {
    thunk_FUN_0045b24d((int)*(short *)(local_8 + 10),
                       *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) + 0x140,&local_14,&local_10);
    thunk_FUN_0045afb9(*(undefined2 *)(local_c + 0x28),local_14,local_10);
  }
  if (*(int *)(local_c + 0xc) == 1) {
    *(short *)(local_8 + 10) = *(short *)(local_8 + 10) + 3;
  }
  if (DAT_00618e44 % 2 != 0) {
    *(short *)(local_8 + 6) = *(short *)(local_8 + 6) + 1;
  }
  if (*(short *)(local_c + 0x1c + *(short *)(local_8 + 4) * 2) < *(short *)(local_8 + 6)) {
    if ((*(int *)(local_c + 0xc) == 1) && (*(short *)(local_8 + 10) < 0x1b9)) {
      *(undefined2 *)(local_8 + 6) = *(undefined2 *)(local_c + 0x14 + *(short *)(local_8 + 4) * 2);
    }
    else if ((int)*(short *)(local_8 + 4) < *(short *)(local_c + 0x12) + -1) {
      *(short *)(local_8 + 4) = *(short *)(local_8 + 4) + 1;
      *(undefined2 *)(local_8 + 6) = *(undefined2 *)(local_c + 0x14 + *(short *)(local_8 + 4) * 2);
      *(undefined2 *)(local_8 + 0x12) = 0;
      *(short *)(local_8 + 10) = *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) + 0x140;
    }
    else {
      *(ushort *)(local_8 + 0x10) = *(ushort *)(local_8 + 0x10) & 0xff7f;
      thunk_FUN_00416e7d(param_1);
    }
  }
  *(short *)(local_8 + 0x12) = *(short *)(local_8 + 0x12) + 1;
  return;
}
```

---

---

## FUN_00418105 — 0x418105

- Classification : internal
- Corps : `0x418105–0x4181a5`
- État : pseudocode obtenu
- Evidence : `ev_2c71645aaa9320eb731679d674b705320b6394eca7fe88af0cd6dcb7f1a82403`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49c4a4` — "shape"
- `0x49c4ac` — "C:\\float\\src\\effects.cpp"

### Pseudocode Ghidra

```c
void FUN_00418105(undefined4 param_1,int param_2)

{
  int in_ECX;
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = in_ECX + *(short *)(param_2 + 0xe) * 0x30;
  if (*(int *)(iVar1 + 0xc) != 6) {
    iVar1 = thunk_FUN_0040e864(CONCAT22((short)((uint)iVar1 >> 0x10),*(undefined2 *)(iVar1 + 0x26)))
    ;
    if (iVar1 == 0) {
      uVar2 = thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c4ac,0x584,s_shape_0049c4a4);
    }
    else {
      uVar2 = 0;
    }
    thunk_FUN_00404770(param_1,iVar1,(int)*(short *)(param_2 + 6),
                       (int)*(short *)(param_2 + 10) -
                       (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2),
                       (int)*(short *)(param_2 + 0xc),uVar2);
  }
  return;
}
```

---

---

## FUN_004181a6 — 0x4181a6

- Classification : internal
- Corps : `0x4181a6–0x4182c7`
- État : pseudocode obtenu
- Evidence : `ev_debaf503b8067df8b015020cce042fb513deb1333fbefcc4677ace9723cb5e9e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40140b` — `thunk_FUN_00416e7d`
- `0x40184d` — `thunk_FUN_0045b24d`
- `0x401aaf` — `thunk_FUN_0045afb9`
- `0x40250e` — `thunk_FUN_00414fbf`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004181a6(short param_1)

{
  int in_ECX;
  int local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_8 = in_ECX + 0x1202 + param_1 * 0x14;
  local_c = in_ECX + *(short *)(local_8 + 0xe) * 0x30;
  if (*(short *)(local_8 + 0x12) == 0) {
    if (((*(short *)(local_c + 0x28) != -1) && (*(short *)(local_8 + 8) == DAT_0049f53c)) &&
       (DAT_0062d172 == 3)) {
      local_18 = *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) + 0x140;
      local_1c = (int)*(short *)(local_8 + 10);
      if ((*(int *)(local_c + 0xc) == 2) || (*(int *)(local_c + 0xc) == 3)) {
        thunk_FUN_00414fbf(local_8,&local_1c,0);
      }
      if (*(int *)(local_c + 0xc) == 3) {
        local_1c = local_1c + *(short *)(local_8 + 10);
      }
      thunk_FUN_0045b24d(local_1c,local_18,&local_14,&local_10);
      thunk_FUN_0045afb9(*(undefined2 *)(local_c + 0x28),local_14,local_10);
    }
    if (*(int *)(local_c + 0xc) == 6) {
      thunk_FUN_00416e7d(param_1);
    }
  }
  return;
}
```

---

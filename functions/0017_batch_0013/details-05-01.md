# 0017_batch_0013 — détails (1/3)

## FUN_0046466f — 0x46466f

- Classification : internal
- Corps : `0x46466f–0x464b9d`
- État : pseudocode obtenu
- Evidence : `ev_ac313cb8cc73f9c102676395cd14cb97b5b1f9355d074df1e6656ce028d2d36f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40102d` — `thunk_FUN_0045e6d3`
- `0x40173a` — `thunk_FUN_004672a6`
- `0x4018a7` — `thunk_FUN_00462a87`
- `0x401924` — `thunk_FUN_00453a5f`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4022e3` — `thunk_FUN_00452859`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a5134` — "j<island->mNumLocs"
- `0x4a5148` — "C:\\float\\src\\tworld.cpp"
- `0x4a5160` — "jhall!=NULL"
- `0x4a516c` — "C:\\float\\src\\tworld.cpp"
- `0x4a5184` — "floater"
- `0x4a518c` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
void FUN_0046466f(uint param_1,int param_2)

{
  int iVar1;
  int in_ECX;
  int iVar2;
  uint local_44;
  int local_40;
  int local_3c;
  short *local_34;
  short *local_30;
  int local_2c;
  int local_28;
  short *local_1c;
  int local_18;
  int local_14;
  int local_10;
  uint local_8;
  
  *(undefined2 *)(in_ECX + 0x2c1a0) = 0;
  local_8 = 0;
  do {
    if (3 < (int)local_8) {
      return;
    }
    *(undefined4 *)(in_ECX + 0x2e360 + local_8 * 0x14a0) = 0;
    _memset((void *)(in_ECX + 0x2cfe4 + local_8 * 0x14a0),0,0x48);
    *(undefined4 *)(in_ECX + 0x2d02c + local_8 * 0x14a0) = 0;
    *(undefined4 *)(in_ECX + 0x2d030 + local_8 * 0x14a0) = 0;
    *(undefined2 *)(in_ECX + 0x2e370 + local_8 * 0x14a0) = 0;
    *(undefined2 *)(in_ECX + 0x2e372 + local_8 * 0x14a0) = 0;
    *(undefined2 *)(in_ECX + 0x2e374 + local_8 * 0x14a0) = 0;
    for (local_40 = 0; local_40 < 0x10; local_40 = local_40 + 1) {
      *(undefined2 *)(in_ECX + local_8 * 0x14a0 + 0x2e382 + local_40 * 10) = 0xffff;
    }
    _memset((void *)(in_ECX + 0x2e41e + local_8 * 0x14a0),0,0x12);
    _memset((void *)(in_ECX + 0x2e430 + local_8 * 0x14a0),0,8);
    *(undefined2 *)(in_ECX + 0x2e438 + local_8 * 0x14a0) = 0;
    local_44 = local_8;
    if ((param_1 & 1) != 0) {
      local_44 = param_2 + (local_8 & 1);
    }
    *(uint *)(in_ECX + 0x2e364 + local_8 * 0x14a0) = local_44;
    *(undefined2 *)(in_ECX + 0x2e368 + local_8 * 0x14a0) = (undefined2)local_44;
    iVar2 = in_ECX + local_44 * 0x29e8;
    *(undefined4 *)(iVar2 + 0x29ac + local_8 * 4) = 1;
    *(undefined4 *)(in_ECX + 0x2e43c + local_8 * 0x14a0) = 0;
    for (local_28 = 0; local_28 < 4; local_28 = local_28 + 1) {
      *(undefined4 *)(in_ECX + local_8 * 0x14a0 + 0x2d078 + local_28 * 4) = 1;
      *(undefined4 *)(in_ECX + local_8 * 0x14a0 + 0x2d088 + local_28 * 4) = 1;
    }
    local_34 = (short *)(iVar2 + 0x428);
    local_2c = 0;
    for (local_3c = 0; local_3c < *(short *)(iVar2 + 0x29a8); local_3c = local_3c + 1) {
      if (*(int *)(local_34 + 2) == 1) {
        if ((param_1 & 1) == 0) {
          if (((local_2c == 0) && ((local_8 & 1) == 0)) || ((local_2c == 3 && ((local_8 & 1) != 0)))
             ) {
            *(byte *)(local_34 + 0x11) =
                 *(byte *)(local_34 + 0x11) | (byte)(1 << ((byte)local_8 & 0x1f));
            break;
          }
        }
        else if (local_2c == ((int)local_8 >> 1) + 1) {
          *(byte *)(local_34 + 0x11) =
               *(byte *)(local_34 + 0x11) | (byte)(1 << ((byte)local_8 & 0x1f));
          break;
        }
        local_2c = local_2c + 1;
      }
      local_34 = local_34 + 0x30;
    }
    if (*(short *)(iVar2 + 0x29a8) <= local_3c) {
      thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a5148,0x520,s_j<island_>mNumLocs_004a5134);
    }
    thunk_FUN_0045e6d3(0xffffffff);
    local_30 = (short *)0x0;
    local_1c = (short *)(iVar2 + 0x428);
    local_10 = 9999;
    for (local_3c = 0; local_3c < *(short *)(iVar2 + 0x29a8); local_3c = local_3c + 1) {
      if (((*(int *)(local_1c + 2) == 0) && (*(int *)(local_1c + 8) == 0)) &&
         (iVar1 = thunk_FUN_004672a6((int)*local_1c,(int)local_1c[1],(int)*local_34,(int)local_34[1]
                                    ), iVar1 < local_10)) {
        local_30 = local_1c;
        *(undefined2 *)(in_ECX + 0x2e36a + local_8 * 0x14a0) = (undefined2)local_3c;
        local_10 = iVar1;
      }
      local_1c = local_1c + 0x30;
    }
    if (local_30 == (short *)0x0) {
      thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a516c,0x53b,s_jhall__NULL_004a5160);
    }
    thunk_FUN_00452859(0x2a,local_8);
    *(uint *)(local_30 + 0xe) = *(uint *)(local_30 + 0xe) & 0xffffffef;
    thunk_FUN_00453a5f();
    local_30[0x14] = 0x32;
    local_18 = *local_30 + -0x140;
    if (local_18 < 0) {
      local_18 = 0;
    }
    if (0x780 < local_18) {
      local_18 = 0x780;
    }
    *(int *)(iVar2 + 0x408 + local_8 * 8) = local_18;
    *(int *)(iVar2 + 0x40c + local_8 * 8) = local_18 + 0x27f;
    for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
      iVar2 = thunk_FUN_00462a87(local_8,0,(int)*local_34,(int)local_34[1]);
      if (iVar2 == 0) {
        thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a518c,0x54b,s_floater_004a5184);
      }
    }
    local_8 = local_8 + 1;
  } while( true );
}
```

---

---

## FUN_00464b9e — 0x464b9e

- Classification : internal
- Corps : `0x464b9e–0x464e4c`
- État : pseudocode obtenu
- Evidence : `ev_af395cb5dc0ed1efd405d0c4880d5843648c434a49f9d811e53dccc4b1268377`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011b8` — `thunk_FUN_004535e4`
- `0x401226` — `thunk_FUN_00460460`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x4022e3` — `thunk_FUN_00452859`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00464b9e(uint param_1)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  int local_44;
  short local_40;
  short local_3c;
  int local_38;
  int local_34;
  short local_30 [6];
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  undefined *local_14;
  uint local_10;
  uint local_c;
  int local_8;
  
  for (local_c = 0; (int)local_c < (int)(DAT_006136b0 - 1); local_c = local_c + 1) {
    local_18 = (int)(short)(&DAT_005eebf8)[local_c * 0x14f4];
    local_14 = &DAT_005e9830 + (uint)DAT_006136b0 * 0x29e8;
    local_1c = 0;
    while (local_1c == 0) {
      local_20 = thunk_FUN_00467260((int)*(short *)(local_14 + 0x29a8));
      if ((*(int *)(local_14 + local_20 * 0x60 + 0x42c) == 0) &&
         (*(int *)(local_14 + local_20 * 0x60 + 0x434) == 0)) {
        local_1c = 1;
        *(undefined4 *)(local_14 + local_20 * 0x60 + 0x43c) = 4;
        *(uint *)(local_14 + local_20 * 0x60 + 0x438) = local_c + 0x17;
        *(undefined2 *)(local_14 + local_20 * 0x60 + 0x45c) = 30000;
      }
    }
  }
  local_10 = param_1 & 1;
  local_c = 0;
  local_8 = in_ECX;
  do {
    if ((int)(uint)*(ushort *)(in_ECX + 0x27498) <= (int)local_c) {
      thunk_FUN_00460460(0xffffffff);
      return;
    }
    local_44 = 0;
    local_34 = local_8 + 0x428;
    local_24 = 0;
    for (local_38 = 0; local_38 < *(short *)(local_8 + 0x29a8); local_38 = local_38 + 1) {
      if (*(int *)(local_34 + 4) == 1) {
        local_30[local_44] = (short)local_38;
        local_44 = local_44 + 1;
        if (local_44 == 5) break;
      }
      local_34 = local_34 + 0x60;
    }
    if (local_44 != 0) {
      local_40 = -1;
      if ((int)local_c < 4) {
        if ((local_c & 1) == 0) {
          local_3c = local_30[local_44 + -1];
          if ((local_10 != 0) && (1 < local_44)) {
            local_40 = local_30[0];
          }
        }
        else {
          local_3c = local_30[0];
          if ((local_10 != 0) && (1 < local_44)) {
            local_40 = local_30[local_44 + -1];
          }
        }
      }
      else {
        iVar1 = thunk_FUN_00467260(local_44);
        local_3c = local_30[iVar1];
      }
      if (local_3c != -1) {
        uVar2 = thunk_FUN_004535e4();
        thunk_FUN_00452859(uVar2,4);
      }
      if (local_40 != -1) {
        uVar2 = thunk_FUN_004535e4();
        thunk_FUN_00452859(uVar2,4);
      }
    }
    local_c = local_c + 1;
    local_8 = local_8 + 0x29e8;
  } while( true );
}
```

---

---

## FUN_00464e4d — 0x464e4d

- Classification : internal
- Corps : `0x464e4d–0x46559d`
- État : pseudocode obtenu
- Evidence : `ev_263219709d3aac1377c16dbbced6520275c4a294771ed8573e37950887830f45`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013c0` — `thunk_FUN_004655b2`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x40156e` — `thunk_FUN_0041ff8b`
- `0x40186b` — `thunk_FUN_004656d6`
- `0x4018a7` — `thunk_FUN_00462a87`
- `0x4018cf` — `thunk_FUN_0041ff2e`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x401d16` — `thunk_FUN_004204bc`
- `0x401d8e` — `thunk_FUN_004140dd`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x40218a` — `thunk_FUN_00410765`
- `0x40225c` — `thunk_FUN_00421ec1`

### Chaînes référencées

- `0x4a51a8` — "C:\\float\\src\\tworld.cpp"
- `0x4a51c4` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
void FUN_00464e4d(void)

{
  short sVar1;
  int iVar2;
  int in_ECX;
  undefined4 uVar3;
  int local_50;
  int *local_4c;
  undefined4 local_48;
  undefined4 local_44;
  int local_40;
  int local_3c;
  int *local_38;
  short *local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  undefined4 local_10;
  int local_c;
  short local_8;
  
  if ((*(short *)(in_ECX + 0x2cf9c) != 0) && (*(short *)(in_ECX + 0x2cf9c) != 6)) {
    local_c = *(int *)(DAT_0049f538 * 0x14a0 + 0x619248);
    if (DAT_004a4b7c != 0) {
      local_10 = 1;
      thunk_FUN_004140dd(0xb,&local_10,4,0);
      DAT_004a4b7c = 0;
    }
    local_8 = *(short *)(in_ECX + 0x2cf9c);
    switch(*(undefined2 *)(in_ECX + 0x2cf9c)) {
    case 1:
      if (*(short *)(in_ECX + 0x2cf9e) == 100) {
        *(undefined2 *)(in_ECX + 0x2cf9c) = 3;
      }
      break;
    case 2:
      if (*(short *)(in_ECX + 0x2cf9e) == 0) {
        local_1c = 0xb;
        local_18 = 0;
        thunk_FUN_004655b2(&local_1c);
        local_14 = in_ECX + -0x29e8 + (uint)*(ushort *)(in_ECX + 0x27498) * 0x29e8;
        local_20 = 0;
        for (local_24 = local_14 + 0x428;
            ((local_20 < *(short *)(local_14 + 0x29a8) && (*(int *)(local_24 + 0x10) != 4)) &&
            (*(int *)(local_24 + 0x10) != 0x16)); local_24 = local_24 + 0x60) {
          local_20 = local_20 + 1;
        }
        if (local_24 == 0) {
          thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a51a8,0x60d,&DAT_004a51a4);
        }
        *(uint *)(local_24 + 0x1c) = *(uint *)(local_24 + 0x1c) | 1;
        local_28 = thunk_FUN_004656d6(*(ushort *)(in_ECX + 0x27498) - 1,4);
        for (local_20 = 0; local_20 < local_28; local_20 = local_20 + 1) {
          thunk_FUN_004204bc(*(undefined2 *)
                              (in_ECX + 0x275c0 + *(short *)(in_ECX + 0x2cd9c + local_20 * 2) * 0x4c
                              ),0xffffffff);
        }
      }
      else if (*(short *)(in_ECX + 0x2cf9e) == 0x28) {
        local_2c = in_ECX + -0x29e8 + (uint)*(ushort *)(in_ECX + 0x27498) * 0x29e8;
        local_30 = 0;
        for (local_34 = (short *)(local_2c + 0x428);
            ((local_30 < *(short *)(local_2c + 0x29a8) && (*(int *)(local_34 + 8) != 4)) &&
            (*(int *)(local_34 + 8) != 0x16)); local_34 = local_34 + 0x30) {
          local_30 = local_30 + 1;
        }
        if (local_34 == (short *)0x0) {
          uVar3 = thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a51c4,0x61c,&DAT_004a51c0);
        }
        else {
          uVar3 = 0;
        }
        local_38 = (int *)(in_ECX + 0x275a0);
        for (local_30 = 0; local_30 < 0x100; local_30 = local_30 + 1) {
          if (((-1 < *local_38) && (*local_38 < 4)) &&
             (((int)*(short *)((int)local_38 + 0xe) == *(ushort *)(in_ECX + 0x27498) - 1 &&
              (local_38[1] != 8)))) {
            local_3c = thunk_FUN_00467260(8);
            local_3c = local_3c + 10;
            local_40 = thunk_FUN_00462a87(4,local_3c,(int)*local_34,(int)local_34[1]);
            if (local_40 != 0) {
              sVar1 = thunk_FUN_0041ff2e(uVar3);
              if (sVar1 < 1) {
                thunk_FUN_0041ff8b(0);
              }
              else {
                thunk_FUN_0041ff8b(1);
              }
              thunk_FUN_00421ec1(0xffffffff);
              *(undefined4 *)(local_40 + 0x3c) = 0x14;
              *(undefined2 *)(local_40 + 0x40) = *(undefined2 *)(local_40 + 0xe);
              *(short *)(local_40 + 0x42) = (short)((int)(local_38 + -0x184dee) / 0x4c);
              *(undefined2 *)(local_40 + 0x46) = 0;
              thunk_FUN_00421ec1(0xffffffff);
              local_38[0xf] = 0x14;
              *(undefined2 *)(local_38 + 0x10) = *(undefined2 *)((int)local_38 + 0xe);
              *(short *)((int)local_38 + 0x42) = (short)((local_40 + -0x6137b8) / 0x4c);
              *(undefined2 *)((int)local_38 + 0x46) = 0;
            }
          }
          local_38 = local_38 + 0x13;
        }
      }
      else if (((*(short *)(in_ECX + 0x2cf9e) < 0x65) || (999 < *(short *)(in_ECX + 0x2cf9e))) &&
              (*(short *)(in_ECX + 0x2cf9e) == 1000)) {
        *(undefined2 *)(in_ECX + 0x2cf9c) = 3;
      }
      break;
    case 3:
      if (*(short *)(in_ECX + 0x2cf9e) < 100) {
        thunk_FUN_00410765(&DAT_00630730,0,((int)*(short *)(in_ECX + 0x2cf9e) << 8) / 99);
      }
      else if (*(short *)(in_ECX + 0x2cf9e) == 100) {
        thunk_FUN_0046c1b4(1,2,0);
        local_48 = 0xb;
        local_44 = 1;
        if (local_c != 0) {
          local_44 = 2;
        }
        thunk_FUN_004655b2(&local_48);
      }
      else if (*(short *)(in_ECX + 0x2cf9e) < 0x96) {
        thunk_FUN_00410765(&DAT_00630730,0,((0x95 - *(short *)(in_ECX + 0x2cf9e)) * 0x100) / 0x31);
      }
      else if (((*(short *)(in_ECX + 0x2cf9e) < 0x259) || (799 < *(short *)(in_ECX + 0x2cf9e))) ||
              (local_c == 0)) {
        if (local_c == 0) {
          if (599 < *(short *)(in_ECX + 0x2cf9e)) {
            *(undefined2 *)(in_ECX + 0x2cf9c) = 4;
          }
        }
        else if (0x513 < *(short *)(in_ECX + 0x2cf9e)) {
          *(undefined2 *)(in_ECX + 0x2cf9c) = 5;
        }
      }
      else {
        local_4c = &DAT_006136b4;
        for (local_50 = 0; local_50 < (int)(uint)DAT_006137b4; local_50 = local_50 + 1) {
          if ((*local_4c != 0) &&
             (iVar2 = thunk_FUN_00467260(800 - *(short *)(in_ECX + 0x2cf9e)), iVar2 < 3)) {
            *local_4c = 0;
          }
          local_4c = local_4c + 2;
        }
      }
      break;
    case 4:
      if (*(short *)(in_ECX + 0x2cf9e) == 0x15e) {
        *(undefined2 *)(in_ECX + 0x2cf9c) = 5;
      }
      break;
    case 5:
      if (*(short *)(in_ECX + 0x2cf9e) < 100) {
        thunk_FUN_00410765(&DAT_00630730,0,((int)*(short *)(in_ECX + 0x2cf9e) << 8) / 99);
      }
      else if (local_c == 0) {
        if (*(short *)(in_ECX + 0x2cf9e) == 100) {
          thunk_FUN_0046c1b4(1,7,0);
          DAT_004bf120 = 0;
        }
        else if (*(short *)(in_ECX + 0x2cf9e) < 200) {
          thunk_FUN_00410765(&DAT_00630730,0,((199 - *(short *)(in_ECX + 0x2cf9e)) * 0x100) / 99);
        }
        else {
          *(undefined2 *)(in_ECX + 0x2cf9c) = 6;
        }
      }
      else if (*(short *)(in_ECX + 0x2cf9e) == 0xa0) {
        thunk_FUN_0046c1b4(1,0,0);
        *(undefined2 *)(in_ECX + 0x2cf9c) = 6;
      }
    }
    if (local_8 == *(short *)(in_ECX + 0x2cf9c)) {
      *(short *)(in_ECX + 0x2cf9e) = *(short *)(in_ECX + 0x2cf9e) + 1;
    }
    else {
      *(undefined2 *)(in_ECX + 0x2cf9e) = 0;
    }
  }
  return;
}
```

---

---

## FUN_004655b2 — 0x4655b2

- Classification : internal
- Corps : `0x4655b2–0x465613`
- État : pseudocode obtenu
- Evidence : `ev_84e65309a12c404dece26608da24b9aa1f6be96f98341f8e72f412de20e47b3d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_004655b2(undefined4 *param_1)

{
  short sVar1;
  undefined4 uVar2;
  bool bVar3;
  int in_ECX;
  
  bVar3 = *(short *)(in_ECX + 0x2cd40) < 0x20;
  if (bVar3) {
    uVar2 = param_1[1];
    sVar1 = *(short *)(in_ECX + 0x2cd40);
    *(undefined4 *)(in_ECX + 0x2cc40 + sVar1 * 8) = *param_1;
    *(undefined4 *)(in_ECX + 0x2cc44 + sVar1 * 8) = uVar2;
    *(short *)(in_ECX + 0x2cd40) = *(short *)(in_ECX + 0x2cd40) + 1;
  }
  return bVar3;
}
```

---

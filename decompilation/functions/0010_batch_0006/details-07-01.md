# 0010_batch_0006 — détails (1/3)

## FUN_004211bb — 0x4211bb

- Classification : internal
- Corps : `0x4211bb–0x421d21`
- État : pseudocode obtenu
- Evidence : `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Lecture comportementale ajoutée

Le champ d’action à `+0x3c` est un ID d’ordre `FA_*`, pas l’état runtime à `+0x2c`. Les noms affichés sont indexés depuis `FA_Nothing` avec un pas de 0x10, confirmé par `FUN_0044338b` et `FUN_00435f4d`. La routine exécute l’ordre existant et fait avancer ses étapes/états ; elle ne choisit pas la politique de réévaluation. Relecture pseudocode Evidence `ev_0e9d3fbfa8df7eb8f372d0b17bc92593ddd6fc2eb7cebe7c043ca611798b4abd`, correspondance des noms dans [l’analyse enemy AI](../../behavior/enemy-ai.md#action-ids-and-the-leviathan-decision-branch).

### Appels directs

- `0x40100f` — `thunk_FUN_00420d97`
- `0x40131b` — `thunk_FUN_00423068`
- `0x40145b` — `thunk_FUN_00425084`
- `0x401546` — `thunk_FUN_00420e94`
- `0x401870` — `thunk_FUN_00420dbd`
- `0x401a1e` — `thunk_FUN_004526de`
- `0x401bae` — `thunk_FUN_00420829`
- `0x40202c` — `thunk_FUN_004210a9`
- `0x4020b3` — `thunk_FUN_00466533`
- `0x402199` — `thunk_FUN_004208eb`
- `0x402243` — `thunk_FUN_00452794`
- `0x40225c` — `thunk_FUN_00421ec1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004211bb(void)

{
  short sVar1;
  int iVar2;
  int *in_ECX;
  int local_5c;
  short local_50 [2];
  undefined2 local_4c [2];
  int local_48;
  short local_44;
  short local_40;
  short local_3c;
  int local_38;
  undefined2 local_34 [2];
  short local_30 [2];
  short local_2c;
  short local_28;
  int local_24;
  short local_20 [2];
  undefined2 local_1c [2];
  int local_18;
  undefined *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  *(undefined2 *)(in_ECX + 0xd) = 0;
  local_10 = 0;
  local_8 = 0;
  if ((((in_ECX[0xf] == 5) || (in_ECX[0xf] == 4)) || (in_ECX[0xf] == 0xd)) || (in_ECX[0xf] == 0x12))
  {
    local_5c = 0;
  }
  else {
    local_5c = 1;
  }
  local_c = local_5c;
  if (*(short *)((int)in_ECX + 0x46) == -1) {
    local_10 = 1;
    if ((in_ECX[0xf] != 4) || ((4 < (short)in_ECX[0x11] && ((short)in_ECX[0x11] < 0x22)))) {
      local_8 = 1;
    }
  }
  else if (((local_5c == 0) || ((short)in_ECX[0x10] == *(short *)((int)in_ECX + 0xe))) ||
          ((short)in_ECX[0x10] == -1)) {
    switch(in_ECX[0xf] + -1) {
    case 0:
      in_ECX[0xb] = 1;
      *(undefined2 *)((int)in_ECX + 0x32) = *(undefined2 *)((int)in_ECX + 0x42);
      *(undefined2 *)((int)in_ECX + 0x46) = 0xffff;
      break;
    case 1:
    case 0x10:
      in_ECX[0xb] = 2;
      *(undefined2 *)((int)in_ECX + 0x32) = *(undefined2 *)((int)in_ECX + 0x42);
      *(short *)(in_ECX + 0xc) = (short)in_ECX[0x11];
      *(undefined2 *)((int)in_ECX + 0x46) = 0xffff;
      break;
    case 3:
      local_24 = 1;
      if (*(short *)((int)in_ECX + 0x46) == 2) {
        if (((short)in_ECX[0x11] < 5) || (0x21 < (short)in_ECX[0x11])) {
          thunk_FUN_00421ec1(0xffffffff);
        }
        else {
          local_28 = thunk_FUN_00420e94(2,(short)*in_ECX);
          if (local_28 == -1) {
            local_24 = thunk_FUN_004210a9((int)*(short *)(&DAT_0061a580 + *in_ECX * 0x14a0));
          }
          else {
            in_ECX[0xb] = 4;
            *(short *)((int)in_ECX + 0x32) = local_28;
            *(undefined2 *)((int)in_ECX + 0x46) = 0xffff;
          }
        }
      }
      else if (*(short *)((int)in_ECX + 0x46) == 1) {
        if (in_ECX[6] == 0) {
          if (((short)in_ECX[0x11] < 5) || (0x21 < (short)in_ECX[0x11])) {
            *(undefined2 *)((int)in_ECX + 0x46) = 0;
          }
          else {
            *(undefined2 *)((int)in_ECX + 0x46) = 0xffff;
          }
        }
        else {
          *(undefined2 *)((int)in_ECX + 0x46) = 2;
        }
      }
      else if (in_ECX[6] == (int)(short)in_ECX[0x11]) {
        if (*(short *)((int)in_ECX + 0xe) == (short)in_ECX[0x10]) {
          in_ECX[0xb] = 4;
          *(undefined2 *)((int)in_ECX + 0x32) = *(undefined2 *)((int)in_ECX + 0x42);
          *(short *)(in_ECX + 0xc) = (short)in_ECX[0x11];
          *(undefined2 *)((int)in_ECX + 0x46) = 1;
        }
        else {
          local_24 = thunk_FUN_004210a9((int)(short)in_ECX[0x10]);
        }
      }
      else if (((short)in_ECX[0x11] < 5) || (0x21 < (short)in_ECX[0x11])) {
        thunk_FUN_00420dbd((int)(short)in_ECX[0x11],local_30,local_34);
        if (local_30[0] == -1) {
          thunk_FUN_00421ec1(0xffffffff);
        }
        else if (*(short *)((int)in_ECX + 0xe) == local_30[0]) {
          in_ECX[0xb] = 3;
          *(undefined2 *)((int)in_ECX + 0x32) = local_34[0];
          *(short *)(in_ECX + 0xc) = (short)in_ECX[0x11];
          *(undefined2 *)(in_ECX + 0xd) = 0;
        }
        else {
          local_24 = thunk_FUN_004210a9((int)local_30[0]);
        }
      }
      else {
        local_2c = thunk_FUN_00420e94(3,(short)in_ECX[0x11]);
        if (local_2c == -1) {
          local_24 = thunk_FUN_004210a9((int)*(short *)(&DAT_0061a580 + *in_ECX * 0x14a0));
        }
        else {
          in_ECX[0xb] = 3;
          *(short *)((int)in_ECX + 0x32) = local_2c;
          *(short *)(in_ECX + 0xc) = (short)in_ECX[0x11];
          *(undefined2 *)(in_ECX + 0xd) = 0;
        }
      }
      if (local_24 == 0) {
        thunk_FUN_00421ec1(0xffffffff);
      }
      break;
    case 4:
      local_14 = &DAT_005ec640 +
                 *(short *)((int)in_ECX + 0x42) * 0x60 + (short)in_ECX[0x10] * 0x29e8;
      iVar2 = thunk_FUN_004526de((int)(short)in_ECX[0x11],*in_ECX);
      if (iVar2 == 0) {
        local_10 = 1;
        local_8 = 1;
      }
      else {
        local_18 = 1;
        if ((*(int *)(local_14 + 4) == 0) &&
           (iVar2 = thunk_FUN_00452794((int)(short)in_ECX[0x11],*in_ECX), iVar2 != 0)) {
          if (*(short *)((int)in_ECX + 0xe) == (short)in_ECX[0x10]) {
            in_ECX[0xb] = 5;
            *(undefined2 *)((int)in_ECX + 0x32) = *(undefined2 *)((int)in_ECX + 0x42);
            *(short *)(in_ECX + 0xc) = (short)in_ECX[0x11];
            *(undefined2 *)((int)in_ECX + 0x46) = 0xffff;
          }
          else {
            local_18 = thunk_FUN_004210a9((int)(short)in_ECX[0x10]);
          }
        }
        else if (in_ECX[6] == 1) {
          if (*(short *)((int)in_ECX + 0xe) == (short)in_ECX[0x10]) {
            in_ECX[0xb] = 4;
            *(undefined2 *)((int)in_ECX + 0x32) = *(undefined2 *)((int)in_ECX + 0x42);
            *(undefined2 *)(in_ECX + 0xc) = 1;
          }
          else {
            local_18 = thunk_FUN_004210a9((int)(short)in_ECX[0x10]);
          }
        }
        else {
          thunk_FUN_00420dbd(1,local_20,local_1c);
          if (local_20[0] == -1) {
            thunk_FUN_00421ec1(0xffffffff);
          }
          else if (local_20[0] == *(short *)((int)in_ECX + 0xe)) {
            in_ECX[0xb] = 3;
            *(undefined2 *)((int)in_ECX + 0x32) = local_1c[0];
            *(undefined2 *)(in_ECX + 0xc) = 1;
            *(undefined2 *)(in_ECX + 0xd) = 0;
          }
          else {
            local_18 = thunk_FUN_004210a9((int)local_20[0]);
          }
        }
        if (local_18 == 0) {
          thunk_FUN_00421ec1(0xffffffff);
        }
      }
      break;
    case 5:
      if (*(short *)((int)in_ECX + 0x46) == 0) {
        if (*(short *)((int)in_ECX + 0x42) == -1) {
          thunk_FUN_00421ec1(0xffffffff);
        }
        else {
          thunk_FUN_00425084();
          in_ECX[0xb] = 0xf;
          *(undefined2 *)((int)in_ECX + 0x32) = *(undefined2 *)((int)in_ECX + 0x42);
          *(undefined2 *)(in_ECX + 0xc) = 0;
          in_ECX[7] = in_ECX[7] | 4;
          *(undefined2 *)((int)in_ECX + 0x46) = 1;
        }
      }
      else if (*(short *)((int)in_ECX + 0x46) == 1) {
        in_ECX[0xb] = 6;
        *(undefined2 *)((int)in_ECX + 0x46) = 0xffff;
      }
      break;
    case 6:
      if (*(short *)((int)in_ECX + 0x46) == 0) {
        thunk_FUN_00425084();
        in_ECX[0xb] = 0x10;
        *(undefined2 *)((int)in_ECX + 0x32) = *(undefined2 *)((int)in_ECX + 0x42);
        *(undefined2 *)(in_ECX + 0xc) = 0;
        *(undefined2 *)((int)in_ECX + 0x46) = 1;
      }
      else if (*(short *)((int)in_ECX + 0x46) == 1) {
        in_ECX[0xb] = 7;
        *(undefined2 *)((int)in_ECX + 0x46) = 0xffff;
      }
      break;
    case 7:
      sVar1 = *(short *)((int)in_ECX + 0x46);
      if (sVar1 == 0) {
        in_ECX[0xb] = 8;
        *(undefined2 *)((int)in_ECX + 0x32) = *(undefined2 *)((int)in_ECX + 0x42);
        in_ECX[7] = in_ECX[7] & 0xfffffffb;
        *(undefined2 *)((int)in_ECX + 0x46) = 1;
      }
      else if (sVar1 == 1) {
        local_44 = thunk_FUN_004208eb(CONCAT22((short)((uint)(in_ECX[0xf] + -1) >> 0x10),
                                               *(undefined2 *)((int)in_ECX + 0x42)));
        if (local_44 == -1) {
          *(undefined2 *)((int)in_ECX + 0x46) = 0;
        }
        else {
          in_ECX[0xb] = 0xf;
          *(short *)((int)in_ECX + 0x32) = local_44;
          in_ECX[7] = in_ECX[7] | 4;
          *(undefined2 *)((int)in_ECX + 0x46) = 2;
        }
      }
      else if (sVar1 == 2) {
        in_ECX[0xb] = 6;
        *(undefined2 *)((int)in_ECX + 0x46) = 1;
      }
      break;
    case 8:
      switch(*(undefined2 *)((int)in_ECX + 0x46)) {
      case 0:
        in_ECX[0xb] = 9;
        *(undefined2 *)((int)in_ECX + 0x32) = *(undefined2 *)((int)in_ECX + 0x42);
        in_ECX[7] = in_ECX[7] & 0xfffffffb;
        *(undefined2 *)((int)in_ECX + 0x46) = 1;
        break;
      case 1:
        local_40 = thunk_FUN_00420829(*(undefined2 *)((int)in_ECX + 0x42));
        if (local_40 == -1) {
          local_40 = thunk_FUN_00420d97(4,CONCAT22(0xffff,*(undefined2 *)((int)in_ECX + 0x42)));
          if (local_40 == -1) {
            *(undefined2 *)((int)in_ECX + 0x46) = 0;
          }
          else {
            in_ECX[0xb] = 0x10;
            *(short *)((int)in_ECX + 0x32) = local_40;
            *(undefined2 *)((int)in_ECX + 0x46) = 3;
          }
        }
        else {
          in_ECX[0xb] = 0xf;
          *(short *)((int)in_ECX + 0x32) = local_40;
          in_ECX[7] = in_ECX[7] | 4;
          *(undefined2 *)((int)in_ECX + 0x46) = 2;
        }
        break;
      case 2:
        in_ECX[0xb] = 6;
        *(undefined2 *)((int)in_ECX + 0x46) = 1;
        break;
      case 3:
        in_ECX[0xb] = 7;
        *(undefined2 *)((int)in_ECX + 0x46) = 1;
      }
      break;
    case 10:
    case 0xb:
      thunk_FUN_00425084();
      in_ECX[0xb] = in_ECX[0xf];
      *(undefined2 *)((int)in_ECX + 0x32) = *(undefined2 *)((int)in_ECX + 0x42);
      *(short *)(in_ECX + 0xc) = (short)in_ECX[0x11];
      *(undefined2 *)(in_ECX + 0xd) = 0;
      *(undefined2 *)((int)in_ECX + 0x46) = 0xffff;
      break;
    case 0xc:
      local_38 = 1;
      if (in_ECX[6] == (int)(short)in_ECX[0x11]) {
        local_3c = thunk_FUN_00420e94(2,(short)*in_ECX);
        if (local_3c == -1) {
          local_38 = thunk_FUN_004210a9((int)*(short *)(&DAT_0061a580 + *in_ECX * 0x14a0));
        }
        else {
          in_ECX[0xb] = 4;
          *(short *)((int)in_ECX + 0x32) = local_3c;
          *(short *)(in_ECX + 0xc) = (short)in_ECX[6];
          *(undefined2 *)((int)in_ECX + 0x46) = 0xffff;
        }
      }
      else {
        thunk_FUN_00425084();
        if (*(short *)((int)in_ECX + 0xe) == (short)in_ECX[0x10]) {
          in_ECX[0xb] = in_ECX[0xf];
          *(undefined2 *)((int)in_ECX + 0x32) = *(undefined2 *)((int)in_ECX + 0x42);
          *(short *)(in_ECX + 0xc) = (short)in_ECX[0x11];
          *(undefined2 *)((int)in_ECX + 0x46) = 1;
        }
        else {
          local_38 = thunk_FUN_004210a9((int)(short)in_ECX[0x10]);
        }
      }
      if (local_38 == 0) {
        thunk_FUN_00421ec1(0xffffffff);
      }
      break;
    case 0xd:
      in_ECX[0xb] = 0xe;
      *(undefined2 *)(in_ECX + 0xd) = 0x3c;
      *(undefined2 *)((int)in_ECX + 0x46) = 0xffff;
      break;
    case 0x11:
      local_48 = 1;
      if (in_ECX[6] == 1) {
        if (*(short *)((int)in_ECX + 0xe) == (short)in_ECX[0x10]) {
          in_ECX[0xb] = 4;
          *(undefined2 *)((int)in_ECX + 0x32) = *(undefined2 *)((int)in_ECX + 0x42);
          *(short *)(in_ECX + 0xc) = (short)in_ECX[6];
        }
        else {
          local_48 = thunk_FUN_004210a9((int)(short)in_ECX[0x10]);
        }
      }
      else {
        thunk_FUN_00420dbd(1,local_50,local_4c);
        if (local_50[0] == -1) {
          thunk_FUN_00421ec1(0xffffffff);
        }
        else if (local_50[0] == *(short *)((int)in_ECX + 0xe)) {
          in_ECX[0xb] = 3;
          *(undefined2 *)((int)in_ECX + 0x32) = local_4c[0];
          *(undefined2 *)(in_ECX + 0xc) = 1;
          *(undefined2 *)(in_ECX + 0xd) = 0;
        }
        else {
          local_48 = thunk_FUN_004210a9((int)local_50[0]);
        }
      }
      if (local_48 == 0) {
        thunk_FUN_00421ec1(0xffffffff);
      }
      break;
    case 0x12:
      in_ECX[0xb] = in_ECX[0xf];
      *(undefined2 *)((int)in_ECX + 0x32) = *(undefined2 *)((int)in_ECX + 0x42);
      *(short *)(in_ECX + 0xc) = (short)in_ECX[0x11];
      in_ECX[7] = in_ECX[7] & 0xfffffdff;
      *(undefined2 *)((int)in_ECX + 0x46) = 0xffff;
      break;
    case 0x13:
      if (*(short *)((int)in_ECX + 0x46) == 0) {
        in_ECX[0xb] = 0xf;
        *(undefined2 *)((int)in_ECX + 0x32) = *(undefined2 *)((int)in_ECX + 0x42);
        *(undefined2 *)(in_ECX + 0xc) = 0;
        *(undefined2 *)((int)in_ECX + 0x46) = 1;
      }
      else if (in_ECX[1] == 8) {
        in_ECX[0xb] = 0xe;
      }
      else {
        in_ECX[0xb] = 0x15;
      }
    }
  }
  else {
    iVar2 = thunk_FUN_004210a9((int)(short)in_ECX[0x10]);
    if (iVar2 == 0) {
      thunk_FUN_00421ec1(0xffffffff);
    }
  }
  if (local_10 != 0) {
    iVar2 = in_ECX[0xe];
    thunk_FUN_00421ec1(0xffffffff);
    if (local_8 != 0) {
      thunk_FUN_00466533(iVar2);
    }
  }
  if ((in_ECX[0xb] != 0) && (iVar2 = thunk_FUN_00423068(), iVar2 == 0)) {
    thunk_FUN_00421ec1(0xffffffff);
  }
  return;
}
```

---

---

## FUN_00421d82 — 0x421d82

- Classification : internal
- Corps : `0x421d82–0x421ec0`
- État : pseudocode obtenu
- Evidence : `ev_3a04c2a1778a07a8b0d8f20e43aa3103d41776253b982dade9d85e885853e856`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40186b` — `thunk_FUN_004656d6`
- `0x40225c` — `thunk_FUN_00421ec1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00421d82(void)

{
  int iVar1;
  int in_ECX;
  int local_8;
  
  if ((((((*(uint *)(in_ECX + 0x1c) & 0x10) != 0) && (*(int *)(in_ECX + 0x2c) != 6)) &&
       (*(int *)(in_ECX + 0x2c) != 7)) &&
      ((*(int *)(in_ECX + 4) != 0 && (*(int *)(in_ECX + 4) != 9)))) &&
     ((*(int *)(in_ECX + 4) != 4 || (*(int *)(in_ECX + 0x3c) != 0x13)))) {
    iVar1 = thunk_FUN_004656d6((int)*(short *)(in_ECX + 0xe),0xfffffffe);
    for (local_8 = 0; local_8 < iVar1; local_8 = local_8 + 1) {
      if (((int)*(short *)(&DAT_006137ea + (short)(&DAT_00618fb4)[local_8] * 0x4c) ==
           (in_ECX + -0x6137b8) / 0x4c) &&
         ((*(uint *)(&DAT_006137d4 + (short)(&DAT_00618fb4)[local_8] * 0x4c) & 0x40) != 0)) {
        if ((*(int *)(in_ECX + 0x3c) == 6) &&
           (*(short *)(in_ECX + 0x42) == (&DAT_00618fb4)[local_8])) {
          return;
        }
        thunk_FUN_00421ec1(0xffffffff);
        *(undefined4 *)(in_ECX + 0x3c) = 6;
        *(undefined2 *)(in_ECX + 0x40) = *(undefined2 *)(in_ECX + 0xe);
        *(undefined2 *)(in_ECX + 0x42) = (&DAT_00618fb4)[local_8];
        *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 4;
        *(undefined2 *)(in_ECX + 0x46) = 0;
        return;
      }
    }
  }
  return;
}
```

---

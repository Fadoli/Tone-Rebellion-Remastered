# 0010_batch_0006 — détails (7/8)

## FUN_004211bb — 0x4211bb

- Classification : internal
- Corps : `0x4211bb–0x421d21`
- État : pseudocode obtenu
- Evidence : `ev_96f90fdc7951d5fe26fcf0b495de08970ec0e6984d64572c67ff099abac40957`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Lecture comportementale ajoutée

Le champ d’action à `+0x3c` est un ID d’ordre `FA_*`, pas l’état runtime à `+0x2c`. Les noms affichés sont indexés depuis `FA_Nothing` avec un pas de 0x10, confirmé par `FUN_0044338b` et `FUN_00435f4d`. La routine exécute l’ordre existant et fait avancer ses étapes/états ; elle ne choisit pas la politique de réévaluation. Relecture pseudocode Evidence `ev_0e9d3fbfa8df7eb8f372d0b17bc92593ddd6fc2eb7cebe7c043ca611798b4abd`, correspondance des noms dans [l’analyse enemy AI](../behavior/enemy-ai.md#action-ids-and-the-leviathan-decision-branch).

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

## FUN_00421ec1 — 0x421ec1

- Classification : internal
- Corps : `0x421ec1–0x422030`
- État : pseudocode obtenu
- Evidence : `ev_c2d3e74dd2e94c30ca9de18f1387bb8d44d32daf432cd179e9d1b8dfc693b4dc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40140b` — `thunk_FUN_00416e7d`
- `0x4020b3` — `thunk_FUN_00466533`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00421ec1(int param_1)

{
  int in_ECX;
  int iVar1;
  int local_8;
  
  if (*(int *)(in_ECX + 0x38) != -1) {
    iVar1 = *(int *)(in_ECX + 0x38) * 0x14;
    *(short *)(&DAT_006183c0 + iVar1) = *(short *)(&DAT_006183c0 + iVar1) + -1;
  }
  local_8 = -1;
  if ((((4 < *(int *)(in_ECX + 0x18)) && (*(int *)(in_ECX + 0x18) < 0x22)) &&
      (*(int *)(in_ECX + 0x38) != -1)) &&
     ((*(int *)(in_ECX + 0x38) != param_1 &&
      ((*(int *)(in_ECX + 0x3c) == 0xd || (*(int *)(in_ECX + 0x3c) == 4)))))) {
    local_8 = *(int *)(in_ECX + 0x38);
  }
  if (param_1 == -1) {
    *(undefined4 *)(in_ECX + 0x38) = 0xffffffff;
    *(undefined4 *)(in_ECX + 0x3c) = 0;
    *(undefined2 *)(in_ECX + 0x40) = 0xffff;
    *(undefined4 *)(in_ECX + 0x2c) = 0;
  }
  else {
    iVar1 = param_1 * 0x14;
    *(short *)(&DAT_006183c0 + iVar1) = *(short *)(&DAT_006183c0 + iVar1) + 1;
    *(int *)(in_ECX + 0x38) = param_1;
    *(int *)(in_ECX + 0x3c) = (int)(short)(&DAT_006183cc)[param_1 * 10];
    *(undefined2 *)(in_ECX + 0x40) = (&DAT_006183c6)[param_1 * 10];
    *(undefined2 *)(in_ECX + 0x42) = (&DAT_006183ca)[param_1 * 10];
    *(undefined2 *)(in_ECX + 0x44) = *(undefined2 *)(&DAT_006183ce + iVar1);
    *(undefined2 *)(in_ECX + 0x46) = 0;
    *(undefined4 *)(in_ECX + 0x2c) = 0;
  }
  if (*(short *)(in_ECX + 0x48) != -1) {
    thunk_FUN_00416e7d(*(undefined2 *)(in_ECX + 0x48));
    *(undefined2 *)(in_ECX + 0x48) = 0xffff;
  }
  *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) & 0xffffff9a;
  if (local_8 != -1) {
    thunk_FUN_00466533(local_8);
  }
  return;
}
```

---

## FUN_00422031 — 0x422031

- Classification : internal
- Corps : `0x422031–0x42217a`
- État : pseudocode obtenu
- Evidence : `ev_9d5d129cd6bb5e1095f8136fbde959c47360ad898c94d3104c63add6dcda3bc7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401870` — `thunk_FUN_00420dbd`
- `0x401a1e` — `thunk_FUN_004526de`
- `0x402243` — `thunk_FUN_00452794`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00422031(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *in_ECX;
  undefined1 local_20 [4];
  short local_1c [2];
  int local_18;
  undefined *local_14;
  int local_10;
  undefined4 *local_c;
  int local_8;
  
  if (param_1 == -1) {
    uVar1 = 0;
  }
  else {
    local_c = &DAT_006183bc + param_1 * 5;
    local_8 = 0;
    switch((&DAT_006183cc)[param_1 * 10]) {
    case 4:
      local_18 = (int)*(short *)(&DAT_006183ce + param_1 * 0x14);
      if ((in_ECX[6] != local_18) && ((local_18 < 5 || (0x21 < local_18)))) {
        local_8 = local_18;
      }
      break;
    case 5:
      local_14 = &DAT_005ec640 +
                 (short)(&DAT_006183ca)[param_1 * 10] * 0x60 +
                 (short)(&DAT_006183c6)[param_1 * 10] * 0x29e8;
      local_10 = (int)*(short *)(&DAT_006183ce + param_1 * 0x14);
      iVar2 = thunk_FUN_004526de(local_10,*in_ECX);
      if (iVar2 == 0) {
        return 0;
      }
      if ((in_ECX[6] != 1) && (iVar2 = thunk_FUN_00452794(local_10,*in_ECX), iVar2 == 0)) {
        local_8 = 1;
      }
      break;
    case 0xb:
      if (in_ECX[1] != 0) {
        return 0;
      }
      break;
    case 0x12:
      if (in_ECX[6] != 1) {
        local_8 = 1;
      }
    }
    if ((local_8 == 0) || (thunk_FUN_00420dbd(local_8,local_1c,local_20), local_1c[0] != -1)) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}
```

---

## FUN_0042219e — 0x42219e

- Classification : internal
- Corps : `0x42219e–0x422d26`
- État : pseudocode obtenu
- Evidence : `ev_787dc785055d52728b1408fa372d280fa57be569a05f32883f94a4022cbce846`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Lecture comportementale ajoutée

Cette routine réévalue les ordres de chaque floater. Elle ignore les états runtime 6/7 et le garde global `DAT_006191b4`. Catégorie Leviathan 4 / sous-type 9 (`vspore`) possède une branche dédiée : sélection mode 2, ordre `FA_Move` (1), puis dommage périodique si aucune cible n’est retenue. Les sous-types 10–17 partagent une branche qui, depuis `FA_Wander` ou `FA_Nothing`, peut écrire `FA_AttackFlt` (6) ou `FA_AttackLoc` (7) selon un scan local, un score/threshold et un tirage aléatoire ; le flag `0x10` délègue à `FUN_00421d82`. Les floaters réguliers ont des branches distinctes pour engagement, tâche, entraînement, recharge et errance. Les identités métier des champs candidats et priorités restent partiellement inconnues. Evidence pseudocode actualisé `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`; table d’action et détails dans [l’analyse enemy AI](../behavior/enemy-ai.md).

### Appels directs

- `0x40100f` — `thunk_FUN_00420d97`
- `0x4010cd` — `thunk_FUN_00422031`
- `0x40141f` — `thunk_FUN_0045dd3c`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x40180c` — `thunk_FUN_00420600`
- `0x40186b` — `thunk_FUN_004656d6`
- `0x4018ca` — `thunk_FUN_0041e454`
- `0x401933` — `thunk_FUN_00464242`
- `0x401ccb` — `thunk_FUN_00421d82`
- `0x401d16` — `thunk_FUN_004204bc`
- `0x401d39` — `thunk_FUN_00420991`
- `0x401dac` — `thunk_FUN_004207f2`
- `0x40201d` — `thunk_FUN_0045de20`
- `0x402144` — `thunk_FUN_00420f28`
- `0x40225c` — `thunk_FUN_00421ec1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042219e(void)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  int iVar6;
  int *in_ECX;
  bool bVar7;
  int local_8c;
  int local_84;
  int local_7c;
  int local_58;
  int local_54;
  int local_50;
  int *local_48;
  int local_38;
  int local_34;
  int local_30;
  int local_28;
  int local_1c;
  
  if (in_ECX[0xb] == 6) {
    return;
  }
  if (in_ECX[0xb] == 7) {
    return;
  }
  if (DAT_006191b4 != 0) {
    return;
  }
  if ((*in_ECX == 4) && (in_ECX[1] == 9)) {
    if ((in_ECX[0xf] == 1) &&
       (*(int *)(&DAT_005ec654 +
                *(short *)((int)in_ECX + 0xe) * 0x29e8 + *(short *)((int)in_ECX + 0x32) * 0x60) ==
        -1)) {
      return;
    }
    sVar1 = thunk_FUN_00420d97(2,1);
    sVar2 = thunk_FUN_00420d97(2,0);
    if (((sVar1 != -1) && (0 < *(short *)(&DAT_0061f9d4 + *(short *)((int)in_ECX + 0xe) * 2))) &&
       ((*(short *)(&DAT_0061f9b6 + *(short *)((int)in_ECX + 0xe) * 2) == 0 ||
        ((iVar3 = thunk_FUN_00467260(4), iVar3 == 0 || (sVar2 == -1)))))) {
      sVar2 = sVar1;
    }
    thunk_FUN_00421ec1(0xffffffff);
    if (sVar2 == -1) {
      if ((DAT_00618e44 & 0x7f) == 0) {
        thunk_FUN_004204bc(1,0xffffffff);
      }
    }
    else {
      in_ECX[0xf] = 1;
      *(undefined2 *)(in_ECX + 0x10) = *(undefined2 *)((int)in_ECX + 0xe);
      *(short *)((int)in_ECX + 0x42) = sVar2;
      *(undefined2 *)((int)in_ECX + 0x46) = 0;
    }
  }
  else if ((*in_ECX == 4) && (in_ECX[1] != 9)) {
    if ((in_ECX[7] & 0x10U) == 0) {
      if ((in_ECX[0xf] == 0xe) || (in_ECX[0xf] == 0)) {
        local_1c = 0x96;
        if ((in_ECX[7] & 0x80U) != 0) {
          local_1c = 3000;
        }
        iVar3 = thunk_FUN_004656d6((int)*(short *)((int)in_ECX + 0xe),0xfffffffe);
        sVar2 = -1;
        for (local_28 = 0; local_28 < iVar3; local_28 = local_28 + 1) {
          sVar1 = (&DAT_00618fb4)[local_28];
          iVar4 = thunk_FUN_00420991(&DAT_006137b8 + sVar1 * 0x13);
          if ((iVar4 != 0) &&
             (iVar4 = thunk_FUN_00420600(&DAT_006137b8 + sVar1 * 0x13), iVar4 < local_1c)) {
            sVar2 = (&DAT_00618fb4)[local_28];
            break;
          }
        }
        sVar1 = thunk_FUN_00420d97(3,local_1c);
        if ((sVar2 != -1) && (iVar3 = thunk_FUN_00467260(3), iVar3 == 0)) {
          sVar1 = -1;
        }
        if (sVar1 == -1) {
          if (sVar2 != -1) {
            thunk_FUN_00421ec1(0xffffffff);
            in_ECX[0xf] = 6;
            *(undefined2 *)(in_ECX + 0x10) = *(undefined2 *)((int)in_ECX + 0xe);
            *(short *)((int)in_ECX + 0x42) = sVar2;
            *(undefined2 *)((int)in_ECX + 0x46) = 0;
          }
        }
        else {
          thunk_FUN_00421ec1(0xffffffff);
          in_ECX[0xf] = 7;
          *(undefined2 *)(in_ECX + 0x10) = *(undefined2 *)((int)in_ECX + 0xe);
          *(short *)((int)in_ECX + 0x42) = sVar1;
          *(undefined2 *)((int)in_ECX + 0x46) = 0;
        }
      }
    }
    else {
      thunk_FUN_00421d82();
    }
  }
  else if (((*in_ECX == 4) || ((short)in_ECX[3] != -1)) || (in_ECX[1] == 8)) {
    if ((*in_ECX != 4) && ((short)in_ECX[3] != -1)) {
      puVar5 = (undefined2 *)thunk_FUN_004207f2();
      bVar7 = (in_ECX[7] & 0x10U) != 0;
      if (bVar7) {
        thunk_FUN_00421d82();
      }
      else if ((short)((int)(in_ECX + -0x184dee) / 0x4c) == puVar5[0x26]) {
        if ((in_ECX[0xf] != 0xc) && ((in_ECX[7] & 0x20U) == 0)) {
          thunk_FUN_00421ec1(0xffffffff);
          in_ECX[0xf] = 0xc;
          *(undefined2 *)(in_ECX + 0x10) = *puVar5;
          *(undefined2 *)((int)in_ECX + 0x42) = puVar5[1];
          *(undefined2 *)((int)in_ECX + 0x46) = 0;
        }
        bVar7 = true;
      }
      if (((!bVar7) && (in_ECX[0xf] == 2)) && ((in_ECX[7] & 1U) != 0)) {
        bVar7 = true;
      }
      if (!bVar7) {
        sVar2 = thunk_FUN_00420f28();
        iVar4 = (int)sVar2;
        iVar3 = thunk_FUN_00464242(*in_ECX,in_ECX[1]);
        iVar3 = (int)*(short *)(iVar3 + 8);
        if ((((in_ECX[0xf] == 6) || (in_ECX[0xf] == 7)) ||
            ((in_ECX[0xf] == 9 && (*(short *)((int)in_ECX + 0x46) != 0)))) ||
           ((in_ECX[0xf] == 8 && (*(short *)((int)in_ECX + 0x46) != 0)))) {
          local_8c = 1;
          local_7c = iVar4 / 3;
        }
        else {
          iVar6 = thunk_FUN_0045de20();
          local_8c = iVar3;
          local_7c = iVar4;
          if (iVar6 == 0) {
            local_8c = iVar3 / 3;
            local_7c = iVar4 / 3;
          }
        }
        iVar6 = thunk_FUN_0045dd3c();
        local_84 = -1;
        if (((short)in_ECX[8] < local_7c) && (iVar4 <= (short)in_ECX[8] + iVar6)) {
          local_84 = 0;
        }
        else if ((*(short *)((int)in_ECX + 0x22) < local_8c) &&
                (iVar3 <= *(short *)((int)in_ECX + 0x22) + iVar6)) {
          local_84 = 1;
        }
        if (local_84 != -1) {
          if (in_ECX[0xf] != 2) {
            thunk_FUN_00421ec1(0xffffffff);
            in_ECX[0xf] = 2;
            *(undefined2 *)(in_ECX + 0x10) = *puVar5;
            *(undefined2 *)((int)in_ECX + 0x42) = puVar5[1];
            *(undefined2 *)(in_ECX + 0x11) = (undefined2)local_84;
            *(undefined2 *)((int)in_ECX + 0x46) = 0;
          }
          bVar7 = true;
        }
      }
      if (((!bVar7) && (in_ECX[0xf] != 0x13)) &&
         ((in_ECX[0xf] != *(int *)(puVar5 + 0x16) ||
          ((((short)in_ECX[0x10] != puVar5[0x14] || (*(short *)((int)in_ECX + 0x42) != puVar5[0x18])
            ) || ((short)in_ECX[0x11] != puVar5[0x19])))))) {
        thunk_FUN_00421ec1(0xffffffff);
        in_ECX[0xf] = *(int *)(puVar5 + 0x16);
        *(undefined2 *)(in_ECX + 0x10) = puVar5[0x14];
        *(undefined2 *)((int)in_ECX + 0x42) = puVar5[0x18];
        *(undefined2 *)(in_ECX + 0x11) = puVar5[0x19];
        *(undefined2 *)((int)in_ECX + 0x46) = 0;
      }
    }
  }
  else {
    if (*(int *)(&DAT_005eebd4 + *in_ECX * 4 + *(short *)((int)in_ECX + 0xe) * 0x29e8) != 0) {
      if (in_ECX[0xf] == 6) {
        return;
      }
      iVar3 = thunk_FUN_004656d6((int)*(short *)((int)in_ECX + 0xe),0xfffffffe);
      local_54 = -1;
      for (local_58 = 0; local_58 < iVar3; local_58 = local_58 + 1) {
        sVar2 = (&DAT_00618fb4)[local_58];
        iVar4 = thunk_FUN_00420991(&DAT_006137b8 + sVar2 * 0x13);
        if ((iVar4 != 0) &&
           ((iVar4 = thunk_FUN_00420600(&DAT_006137b8 + sVar2 * 0x13), local_54 == -1 ||
            (iVar4 < local_50)))) {
          local_54 = local_58;
          local_50 = iVar4;
        }
      }
      if (local_54 == -1) {
        return;
      }
      thunk_FUN_00421ec1(0xffffffff);
      in_ECX[0xf] = 6;
      *(undefined2 *)(in_ECX + 0x10) = *(undefined2 *)((int)in_ECX + 0xe);
      *(undefined2 *)((int)in_ECX + 0x42) = (&DAT_00618fb4)[local_54];
      *(undefined2 *)((int)in_ECX + 0x46) = 0;
      return;
    }
    if (in_ECX[0xf] == 6) {
      thunk_FUN_00421ec1(0xffffffff);
    }
    if (in_ECX[0xb] == 4) {
      return;
    }
    local_34 = 1000;
    sVar2 = 1;
    local_30 = -1;
    if (in_ECX[0xe] != -1) {
      iVar3 = in_ECX[0xe];
      iVar4 = thunk_FUN_0041e454(&DAT_006183bc + iVar3 * 5);
      if (iVar4 != 0) {
        return;
      }
      local_34 = (int)*(short *)(&DAT_006183c0 + iVar3 * 0x14);
      sVar2 = (&DAT_006183c2)[iVar3 * 10];
    }
    bVar7 = false;
    local_48 = &DAT_006183bc;
    for (local_38 = 0; local_38 < 0x40; local_38 = local_38 + 1) {
      if (((*local_48 != 0) && ((int)(short)local_48[2] == *in_ECX)) &&
         (*(short *)((int)local_48 + 6) == 3)) {
        bVar7 = true;
        break;
      }
      local_48 = local_48 + 5;
    }
    local_48 = &DAT_006183bc;
    local_38 = 0;
    while ((local_38 < 0x40 && (local_30 == -1))) {
      if ((((*local_48 != 0) && ((local_38 != in_ECX[0xe] && ((int)(short)local_48[2] == *in_ECX))))
          && ((iVar3 = thunk_FUN_0041e454(local_48), !bVar7 ||
              ((*(short *)((int)local_48 + 6) == 3 || (iVar3 != 0)))))) &&
         (iVar4 = thunk_FUN_00422031(local_38), iVar4 != 0)) {
        if (iVar3 == 0) {
          if ((*(short *)((int)local_48 + 6) == 3) && (sVar2 != 3)) {
            local_30 = local_38;
          }
          else if (*(short *)((int)local_48 + 6) == sVar2) {
            if ((int)(short)local_48[1] < local_34 + -1) {
              local_30 = local_38;
            }
          }
          else if ((*(short *)((int)local_48 + 6) == 2) && (sVar2 == 1)) {
            if ((int)(short)local_48[1] < local_34 * 2 + -2) {
              local_30 = local_38;
            }
          }
          else if ((*(short *)((int)local_48 + 6) == 1) &&
                  ((sVar2 == 2 && ((short)local_48[1] * 2 < local_34 + -1)))) {
            local_30 = local_38;
          }
        }
        else if ((short)local_48[1] < 1) {
          local_30 = local_38;
        }
      }
      local_38 = local_38 + 1;
      local_48 = local_48 + 5;
    }
    sVar2 = *(short *)(&DAT_0061a580 + *in_ECX * 0x14a0);
    if (local_30 == -1) {
      if (((in_ECX[0xe] == -1) && (*(short *)((int)in_ECX + 0xe) != sVar2)) &&
         ((short)in_ECX[0x10] != sVar2)) {
        thunk_FUN_00421ec1(0xffffffff);
        in_ECX[0xf] = 0xe;
        *(short *)(in_ECX + 0x10) = sVar2;
        *(undefined2 *)((int)in_ECX + 0x46) = 0;
      }
    }
    else {
      thunk_FUN_00421ec1(local_30);
    }
  }
  if (in_ECX[0xf] == 0) {
    thunk_FUN_00421ec1(0xffffffff);
    in_ECX[0xf] = 0xe;
    *(undefined2 *)(in_ECX + 0x10) = *(undefined2 *)((int)in_ECX + 0xe);
    *(undefined2 *)((int)in_ECX + 0x46) = 0;
  }
  return;
}
```

---

## FUN_00422d27 — 0x422d27

- Classification : internal
- Corps : `0x422d27–0x423067`
- État : pseudocode obtenu
- Evidence : `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401401` — `thunk_FUN_0041e427`
- `0x40173a` — `thunk_FUN_004672a6`
- `0x40180c` — `thunk_FUN_00420600`
- `0x401933` — `thunk_FUN_00464242`
- `0x401dac` — `thunk_FUN_004207f2`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00422d27(void)

{
  ushort uVar1;
  int iVar2;
  int *in_ECX;
  undefined4 local_44;
  short local_30 [2];
  short local_2c [2];
  undefined4 *local_28;
  int local_24;
  uint local_20;
  int local_1c;
  ushort local_18;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = (int)(short)in_ECX[10];
  local_10 = (int)*(short *)((int)in_ECX + 0x2a);
  local_20 = 0;
  if (in_ECX[0xb] == 8) {
    iVar2 = *(short *)((int)in_ECX + 0x32) * 0x4c;
    local_28 = &DAT_006137b8 + *(short *)((int)in_ECX + 0x32) * 0x13;
    local_c = local_c + *(short *)(&DAT_006137c8 + iVar2);
    local_10 = local_10 + *(short *)(&DAT_006137ca + iVar2);
    if (local_c < 0) {
      local_c = 0;
    }
    if (0x9ff < local_c) {
      local_c = 0x9ff;
    }
    if (local_10 < 0x28) {
      local_10 = 0x28;
    }
    if (0x122 < local_10) {
      local_10 = 0x122;
    }
    iVar2 = thunk_FUN_00420600(local_28);
    local_20 = (uint)(iVar2 < 100);
    if (local_c < (short)in_ECX[4]) {
      in_ECX[7] = in_ECX[7] | 2;
    }
    else {
      in_ECX[7] = in_ECX[7] & 0xfffffffd;
    }
  }
  else if (in_ECX[0xb] == 9) {
    thunk_FUN_0041e427(CONCAT22((short)((uint)local_30 >> 0x10),*(undefined2 *)((int)in_ECX + 0x32))
                       ,local_2c,local_30);
    iVar2 = thunk_FUN_004672a6((int)(short)in_ECX[4],(int)*(short *)((int)in_ECX + 0x12),
                               (int)local_2c[0],(int)local_30[0]);
    local_20 = (uint)(iVar2 < 100);
  }
  else if (in_ECX[0xb] == 0xe) {
    local_20 = 1;
  }
  if (local_20 == 0) {
    iVar2 = thunk_FUN_00464242(*in_ECX,in_ECX[1]);
    local_18 = *(ushort *)(iVar2 + 0xc);
  }
  else {
    local_18 = 1;
  }
  if ((in_ECX[1] == 0) && (0 < *(short *)(&DAT_00618f5a + *in_ECX * 2))) {
    local_18 = local_18 << 1;
  }
  local_8 = thunk_FUN_004207f2();
  if (local_8 != 0) {
    iVar2 = thunk_FUN_0045c3bb();
    uVar1 = *(ushort *)(&DAT_00619242 + *in_ECX * 0x14a0);
    if (((uVar1 & 8) == 0) || (*(int *)(iVar2 + 0x10) != 0x2c)) {
      if (((uVar1 & 0x20) == 0) || (*(int *)(iVar2 + 0x10) != 0x2d)) {
        if (((uVar1 & 0x200) != 0) && (*(int *)(iVar2 + 0x10) == 0x2e)) {
          local_18 = local_18 + 1;
        }
      }
      else {
        local_18 = local_18 + 1;
      }
    }
    else {
      local_18 = local_18 + 1;
    }
  }
  iVar2 = thunk_FUN_004672a6((int)(short)in_ECX[4],(int)*(short *)((int)in_ECX + 0x12),local_c,
                             local_10);
  if ((iVar2 < (short)local_18 * 4) &&
     (local_18 = (ushort)((int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2), (short)local_18 < 1)) {
    local_18 = (ushort)DAT_00618e44 & 1;
  }
  local_1c = local_c - (short)in_ECX[4];
  local_24 = local_10 - *(short *)((int)in_ECX + 0x12);
  if (local_1c < -(int)(short)local_18) {
    local_1c = -(int)(short)local_18;
  }
  if ((short)local_18 < local_1c) {
    local_1c = (int)(short)local_18;
  }
  *(short *)(in_ECX + 4) = (short)in_ECX[4] + (short)local_1c;
  if (local_24 < -(int)(short)local_18) {
    local_24 = -(int)(short)local_18;
  }
  if ((short)local_18 < local_24) {
    local_24 = (int)(short)local_18;
  }
  *(short *)((int)in_ECX + 0x12) = *(short *)((int)in_ECX + 0x12) + (short)local_24;
  if (((short)in_ECX[4] == local_c) && (*(short *)((int)in_ECX + 0x12) == local_10)) {
    local_44 = 1;
  }
  else {
    local_44 = 0;
  }
  return local_44;
}
```

---


# 0010_batch_0006 — détails (2/3)

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

---

## FUN_0042219e — 0x42219e

- Classification : internal
- Corps : `0x42219e–0x422d26`
- État : pseudocode obtenu
- Evidence : `ev_787dc785055d52728b1408fa372d280fa57be569a05f32883f94a4022cbce846`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Lecture comportementale ajoutée

Cette routine réévalue les ordres de chaque floater. Elle ignore les états runtime 6/7 et le garde global `DAT_006191b4`. Catégorie Leviathan 4 / sous-type 9 (`vspore`) possède une branche dédiée : sélection mode 2, ordre `FA_Move` (1), puis dommage périodique si aucune cible n’est retenue. Les sous-types 10–17 partagent une branche qui, depuis `FA_Wander` ou `FA_Nothing`, peut écrire `FA_AttackFlt` (6) ou `FA_AttackLoc` (7) selon un scan local, un score/threshold et un tirage aléatoire ; le flag `0x10` délègue à `FUN_00421d82`. Les floaters réguliers ont des branches distinctes pour engagement, tâche, entraînement, recharge et errance. Les identités métier des champs candidats et priorités restent partiellement inconnues. Evidence pseudocode actualisé `ev_4c7ea2d2c94eba918c2e82e0709966a1d9d2c60e1d2c705361285aceb05e5dea`; table d’action et détails dans [l’analyse enemy AI](../../behavior/enemy-ai.md).

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

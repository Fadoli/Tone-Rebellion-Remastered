# 0006_batch_0002 — détails (2/3)

## FUN_00406a7f — 0x406a7f

- Classification : internal
- Corps : `0x406a7f–0x406c7b`
- État : pseudocode obtenu
- Evidence : `ev_c44a8535f17b551eac9d4c053c8aafe61f3171aaf5f1331a7f21ef87b203f2de`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x406604` — `FUN_00406604`
- `0x4066e3` — `FUN_004066e3`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00406a7f(int **param_1,uint param_2,uint param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  int local_48;
  undefined4 **local_30;
  int *local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  iVar1 = ((int)param_1[3] + 1) - (int)param_1[1];
  if (iVar1 != 0 && (int)param_1[1] <= (int)param_1[3] + 1) {
    iVar3 = ((int)param_1[4] + 1) - (int)param_1[2];
    if (iVar3 != 0 && (int)param_1[2] <= (int)param_1[4] + 1) {
      iVar2 = -iVar1;
      iVar4 = -iVar3;
      uVar6 = SUB42(param_1,0);
      if (param_4 == 1) {
        if (param_5 == 0) {
          return iVar1 * iVar3;
        }
        local_30 = &local_2c;
        local_18 = param_5;
        local_2c = &local_18;
        local_28 = 0;
        local_24 = 0;
        local_20 = iVar1 + -1;
        local_1c = iVar3 + -1;
        local_14 = local_20;
        local_10 = local_1c;
        FUN_004066e3(param_1,0,0,(short)local_30,0,0,0xffffffff);
        param_2 = (int)param_2 % iVar1;
        param_3 = (int)param_3 % iVar3;
        local_48 = -1;
      }
      else {
        if ((iVar1 <= (int)((param_2 ^ (int)param_2 >> 0x1f) - ((int)param_2 >> 0x1f))) ||
           (iVar3 <= (int)((param_3 ^ (int)param_3 >> 0x1f) - ((int)param_3 >> 0x1f)))) {
          iVar1 = FUN_00406604(uVar6,(ushort)param_5 & 0xff);
          return iVar1;
        }
        local_30 = param_1;
        local_48 = param_5;
      }
      if (param_2 != 0 || param_3 != 0) {
        uVar7 = (undefined2)param_3;
        uVar5 = (undefined2)param_2;
        FUN_004066e3(local_30,0,0,uVar6,uVar5,uVar7,0xffffffff);
        FUN_004066e3(local_30,iVar1,iVar3,uVar6,uVar5,uVar7,local_48);
        FUN_004066e3(local_30,iVar1,0,uVar6,uVar5,uVar7,local_48);
        FUN_004066e3(local_30,iVar1,iVar4,uVar6,uVar5,uVar7,local_48);
        FUN_004066e3(local_30,0,iVar3,uVar6,uVar5,uVar7,local_48);
        FUN_004066e3(local_30,0,iVar4,uVar6,uVar5,uVar7,local_48);
        FUN_004066e3(local_30,iVar2,iVar3,uVar6,uVar5,uVar7,local_48);
        FUN_004066e3(local_30,iVar2,0,uVar6,uVar5,uVar7,local_48);
        FUN_004066e3(local_30,iVar2,iVar4,uVar6,uVar5,uVar7,local_48);
      }
      return 0;
    }
  }
  return -2;
}
```

---

---

## FUN_00406c7c — 0x406c7c

- Classification : internal
- Corps : `0x406c7c–0x406fbc`
- État : pseudocode obtenu
- Evidence : `ev_ee6d3e457b578bc52d6625d7cf42a3472c15947904d6933fee8a5ced3de23561`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x403c35` — `FUN_00403c35`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00406c7c(int *param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined1 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int local_30;
  int local_2c;
  int local_28;
  int local_14;
  int local_10;
  
  if ((param_4 == 0) || (param_5 == 0)) {
    iVar6 = FUN_00403c35(param_1,param_2 - param_4,param_3 - param_5,param_2 + param_4,
                         param_3 + param_5,0,param_6);
  }
  else {
    piVar1 = (int *)*param_1;
    iVar6 = piVar1[1];
    iVar7 = iVar6 + 1;
    if ((iVar7 == 0 || iVar6 < -1) || (iVar2 = piVar1[2], iVar2 < 0)) {
      return -1;
    }
    iVar3 = param_1[1];
    iVar8 = iVar3;
    if (iVar3 < 1) {
      iVar8 = 0;
    }
    iVar12 = param_1[2];
    iVar9 = iVar12;
    if (iVar12 < 1) {
      iVar9 = 0;
    }
    iVar10 = param_1[3];
    if (iVar6 <= param_1[3]) {
      iVar10 = iVar6;
    }
    iVar11 = param_1[4];
    if (iVar2 <= param_1[4]) {
      iVar11 = iVar2;
    }
    if ((iVar10 < iVar8) || (iVar11 < iVar9)) {
      return -2;
    }
    iVar2 = *piVar1;
    uVar5 = (undefined1)param_6;
    param_2 = param_2 + iVar3;
    param_3 = param_3 + iVar12;
    local_10 = 0;
    local_14 = param_5;
    iVar3 = param_5 * param_5;
    uVar4 = param_4 * param_4;
    local_28 = 0;
    local_2c = uVar4 * 2 * param_5;
    local_30 = ((uVar4 >> 2) + iVar3) - uVar4 * param_5;
    while (local_28 - local_2c < 0) {
      iVar12 = param_2 + local_10;
      iVar6 = param_3 + local_14;
      if ((((iVar8 <= iVar12) && (iVar12 <= iVar10)) && (iVar9 <= iVar6)) && (iVar6 <= iVar11)) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      iVar12 = param_2 + local_10;
      iVar6 = param_3 - local_14;
      if (((iVar8 <= iVar12) && (iVar12 <= iVar10)) && ((iVar9 <= iVar6 && (iVar6 <= iVar11)))) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      iVar12 = param_2 - local_10;
      iVar6 = param_3 + local_14;
      if (((iVar8 <= iVar12) && (iVar12 <= iVar10)) && ((iVar9 <= iVar6 && (iVar6 <= iVar11)))) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      iVar12 = param_2 - local_10;
      iVar6 = param_3 - local_14;
      if ((((iVar8 <= iVar12) && (iVar12 <= iVar10)) && (iVar9 <= iVar6)) && (iVar6 <= iVar11)) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      if (-1 < local_30) {
        local_14 = local_14 + -1;
        param_5 = param_5 + -1;
        local_2c = local_2c + uVar4 * -2;
        local_30 = local_30 - local_2c;
      }
      local_10 = local_10 + 1;
      local_28 = local_28 + iVar3 * 2;
      local_30 = local_30 + local_28 + iVar3;
    }
    local_30 = local_30 +
               ((int)(((((int)(uVar4 - iVar3) >> 1) + (uVar4 - iVar3)) - local_28) - local_2c) >> 1)
    ;
    do {
      iVar12 = param_2 + local_10;
      iVar6 = param_3 + local_14;
      if (((iVar8 <= iVar12) && (iVar12 <= iVar10)) && ((iVar9 <= iVar6 && (iVar6 <= iVar11)))) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      iVar12 = param_2 + local_10;
      iVar6 = param_3 - local_14;
      if (((iVar8 <= iVar12) && (iVar12 <= iVar10)) && ((iVar9 <= iVar6 && (iVar6 <= iVar11)))) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      iVar12 = param_2 - local_10;
      iVar6 = param_3 + local_14;
      if ((((iVar8 <= iVar12) && (iVar12 <= iVar10)) && (iVar9 <= iVar6)) && (iVar6 <= iVar11)) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      iVar12 = param_2 - local_10;
      iVar6 = param_3 - local_14;
      if (((iVar8 <= iVar12) && (iVar12 <= iVar10)) && ((iVar9 <= iVar6 && (iVar6 <= iVar11)))) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      if (local_30 < 0) {
        local_10 = local_10 + 1;
        local_28 = local_28 + iVar3 * 2;
        local_30 = local_30 + local_28;
      }
      local_14 = local_14 + -1;
      local_2c = local_2c + uVar4 * -2;
      iVar6 = local_2c - uVar4;
      local_30 = local_30 - iVar6;
      param_5 = param_5 + -1;
    } while (-1 < param_5);
  }
  return iVar6;
}
```

---

---

## FUN_00406fbd — 0x406fbd

- Classification : internal
- Corps : `0x406fbd–0x4072ba`
- État : pseudocode obtenu
- Evidence : `ev_8e76078d2d53f88249b0b34835a0b275b13863d70a847b6cf357f577efc82f59`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x403c35` — `FUN_00403c35`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00406fbd(int *param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined1 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  undefined4 *puVar16;
  int local_30;
  int local_2c;
  int local_28;
  int local_14;
  int local_10;
  
  if ((param_4 == 0) || (param_5 == 0)) {
    iVar6 = FUN_00403c35(param_1,param_2 - param_4,param_3 - param_5,param_2 + param_4,
                         param_3 + param_5,0,param_6);
  }
  else {
    piVar1 = (int *)*param_1;
    iVar6 = piVar1[1];
    iVar7 = iVar6 + 1;
    if ((iVar7 == 0 || iVar6 < -1) || (iVar2 = piVar1[2], iVar2 < 0)) {
      return -1;
    }
    iVar3 = param_1[1];
    iVar8 = iVar3;
    if (iVar3 < 1) {
      iVar8 = 0;
    }
    iVar15 = param_1[2];
    iVar9 = iVar15;
    if (iVar15 < 1) {
      iVar9 = 0;
    }
    iVar10 = param_1[3];
    if (iVar6 <= param_1[3]) {
      iVar10 = iVar6;
    }
    iVar11 = param_1[4];
    if (iVar2 <= param_1[4]) {
      iVar11 = iVar2;
    }
    if ((iVar10 < iVar8) || (iVar11 < iVar9)) {
      return -2;
    }
    iVar2 = *piVar1;
    uVar5 = (undefined1)param_6;
    param_6 = CONCAT22(CONCAT11(uVar5,uVar5),CONCAT11(uVar5,uVar5));
    param_2 = param_2 + iVar3;
    param_3 = param_3 + iVar15;
    local_10 = 0;
    local_14 = param_5;
    iVar3 = param_5 * param_5;
    uVar4 = param_4 * param_4;
    local_28 = 0;
    local_2c = uVar4 * 2 * param_5;
    local_30 = ((uVar4 >> 2) + iVar3) - uVar4 * param_5;
    while (local_28 - local_2c < 0) {
      iVar6 = param_2 + local_10;
      if (iVar8 <= iVar6) {
        if (iVar10 <= iVar6) {
          iVar6 = iVar10;
        }
        iVar15 = param_2 - local_10;
        if (iVar15 <= iVar10) {
          if (iVar15 <= iVar8) {
            iVar15 = iVar8;
          }
          iVar13 = param_3 + local_14;
          if (iVar9 <= iVar13) {
            if (iVar13 <= iVar11) {
              uVar12 = (iVar6 - iVar15) + 1;
              uVar14 = uVar12 & 3;
              puVar16 = (undefined4 *)(iVar13 * iVar7 + iVar2 + iVar15);
              for (uVar12 = uVar12 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                *puVar16 = param_6;
                puVar16 = puVar16 + 1;
              }
              for (; uVar14 != 0; uVar14 = uVar14 - 1) {
                *(undefined1 *)puVar16 = uVar5;
                puVar16 = (undefined4 *)((int)puVar16 + 1);
              }
            }
            iVar13 = param_3 - local_14;
            if ((iVar9 <= iVar13) && (iVar13 <= iVar11)) {
              uVar12 = (iVar6 - iVar15) + 1;
              uVar14 = uVar12 & 3;
              puVar16 = (undefined4 *)(iVar13 * iVar7 + iVar2 + iVar15);
              for (uVar12 = uVar12 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                *puVar16 = param_6;
                puVar16 = puVar16 + 1;
              }
              for (; uVar14 != 0; uVar14 = uVar14 - 1) {
                *(undefined1 *)puVar16 = uVar5;
                puVar16 = (undefined4 *)((int)puVar16 + 1);
              }
            }
          }
        }
      }
      if (-1 < local_30) {
        local_14 = local_14 + -1;
        param_5 = param_5 + -1;
        local_2c = local_2c + uVar4 * -2;
        local_30 = local_30 - local_2c;
      }
      local_10 = local_10 + 1;
      local_28 = local_28 + iVar3 * 2;
      local_30 = local_30 + local_28 + iVar3;
    }
    local_30 = local_30 +
               ((int)(((((int)(uVar4 - iVar3) >> 1) + (uVar4 - iVar3)) - local_28) - local_2c) >> 1)
    ;
    do {
      iVar6 = param_2 + local_10;
      if (iVar8 <= iVar6) {
        if (iVar10 <= iVar6) {
          iVar6 = iVar10;
        }
        iVar15 = param_2 - local_10;
        if (iVar15 <= iVar10) {
          if (iVar15 <= iVar8) {
            iVar15 = iVar8;
          }
          iVar13 = param_3 + local_14;
          if (iVar9 <= iVar13) {
            if (iVar13 <= iVar11) {
              uVar12 = (iVar6 - iVar15) + 1;
              uVar14 = uVar12 & 3;
              puVar16 = (undefined4 *)(iVar13 * iVar7 + iVar2 + iVar15);
              for (uVar12 = uVar12 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                *puVar16 = param_6;
                puVar16 = puVar16 + 1;
              }
              for (; uVar14 != 0; uVar14 = uVar14 - 1) {
                *(undefined1 *)puVar16 = uVar5;
                puVar16 = (undefined4 *)((int)puVar16 + 1);
              }
            }
            iVar13 = param_3 - local_14;
            if ((iVar9 <= iVar13) && (iVar13 <= iVar11)) {
              uVar12 = (iVar6 - iVar15) + 1;
              uVar14 = uVar12 & 3;
              puVar16 = (undefined4 *)(iVar13 * iVar7 + iVar2 + iVar15);
              for (uVar12 = uVar12 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                *puVar16 = param_6;
                puVar16 = puVar16 + 1;
              }
              for (; uVar14 != 0; uVar14 = uVar14 - 1) {
                *(undefined1 *)puVar16 = uVar5;
                puVar16 = (undefined4 *)((int)puVar16 + 1);
              }
            }
          }
        }
      }
      if (local_30 < 0) {
        local_10 = local_10 + 1;
        local_28 = local_28 + iVar3 * 2;
        local_30 = local_30 + local_28;
      }
      local_14 = local_14 + -1;
      local_2c = local_2c + uVar4 * -2;
      iVar6 = local_2c - uVar4;
      local_30 = local_30 - iVar6;
      param_5 = param_5 + -1;
    } while (-1 < param_5);
  }
  return iVar6;
}
```

---

---

## FUN_004080cf — 0x4080cf

- Classification : internal
- Corps : `0x4080cf–0x408186`
- État : pseudocode obtenu
- Evidence : `ev_444eaf89f729befe5df5270500396414e5a6aae903ad69ce54432ab18802d7f0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004080cf(uint param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  
  for (; (int)param_1 < 0; param_1 = param_1 + 0xe10) {
  }
  for (; 0xe10 < (int)param_1; param_1 = param_1 - 0xe10) {
  }
  if (param_1 < 0x709) {
    if (param_1 < 0x385) {
      iVar1 = *(int *)(&DAT_004072bb + param_1 * 4);
      iVar2 = *(int *)(&DAT_004080cb + param_1 * -4);
    }
    else {
      iVar1 = -*(int *)(&DAT_004072bb + (0x708 - param_1) * 4);
      iVar2 = *(int *)(&DAT_004080cb + (0x708 - param_1) * -4);
    }
  }
  else {
    param_1 = 0xe10 - param_1;
    if (param_1 < 0x385) {
      iVar1 = *(int *)(&DAT_004072bb + param_1 * 4);
      iVar2 = -*(int *)(&DAT_004080cb + param_1 * -4);
    }
    else {
      iVar1 = -*(int *)(&DAT_004072bb + (0x708 - param_1) * 4);
      iVar2 = -*(int *)(&DAT_004080cb + (0x708 - param_1) * -4);
    }
  }
  *param_2 = iVar1;
  *param_3 = iVar2;
  return;
}
```

---

---

## FUN_00408187 — 0x408187

- Classification : internal
- Corps : `0x408187–0x4081ac`
- État : pseudocode obtenu
- Evidence : `ev_1a5849bd620515f97ff1a9d2e00579a802ce436bb3e08e81797581f012189805`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00408187(int param_1,int param_2,uint *param_3)

{
  uint uVar1;
  ushort uVar2;
  
  uVar1 = (uint)((longlong)param_1 * (longlong)param_2);
  uVar2 = (ushort)(uVar1 + 0x8000 >> 0x10);
  *param_3 = (uint)uVar2 |
             CONCAT22(uVar2,(short)((ulonglong)((longlong)param_1 * (longlong)param_2) >> 0x20) +
                            (ushort)(0xffff7fff < uVar1)) << 0x10;
  return;
}
```

---

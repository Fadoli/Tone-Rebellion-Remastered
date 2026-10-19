# 0006_batch_0002 — détails (3/3)

## FUN_00405e11 — 0x405e11

- Classification : internal
- Corps : `0x405e11–0x405f88`
- État : pseudocode obtenu
- Evidence : `ev_1a39016a7cfe3f4a8de6b337982beb889bf730c45d8f364c200f54a23460ef03`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00405e11(int param_1,int param_2,int param_3,int param_4,uint param_5,int *param_6)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  byte *pbVar8;
  int iVar9;
  bool bVar10;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  
  local_1c = 0;
  local_20 = 0;
  local_24 = 0;
  local_28 = 0;
  param_1 = *(int *)(param_2 * 8 + 8 + param_1) + param_1;
  iVar3 = *(int *)(param_1 + 8) + param_3;
  iVar9 = *(int *)(param_1 + 0xc);
  iVar4 = iVar9 + param_4;
  iVar5 = *(int *)(param_1 + 0x14) + 1;
  iVar6 = iVar5 - iVar9;
  if (iVar6 != 0 && iVar9 <= iVar5) {
    pbVar7 = (byte *)(param_1 + 0x18);
    local_1c = 0x7fffffff;
    local_20 = 0x7fffffff;
    local_24 = -0x80000000;
    local_28 = -0x80000000;
    do {
      bVar2 = *pbVar7;
      pbVar7 = pbVar7 + 1;
      bVar10 = (bool)(bVar2 & 1);
      bVar2 = bVar2 >> 1;
      iVar9 = iVar3;
      if (!bVar10 && bVar2 != 0) goto LAB_00405ec9;
      if (bVar2 != 0) goto LAB_00405efc;
joined_r0x00405eb2:
      if (bVar10) {
        do {
          while( true ) {
            pbVar8 = pbVar7 + 1;
            iVar9 = iVar9 + (uint)*pbVar7;
            pbVar7 = pbVar7 + 2;
            bVar10 = (bool)(*pbVar8 & 1);
            bVar2 = *pbVar8 >> 1;
            if (!bVar10 && bVar2 != 0) goto LAB_00405ec9;
            if (bVar2 == 0) break;
LAB_00405efc:
            do {
              while( true ) {
                if (iVar9 <= local_1c) {
                  local_1c = iVar9;
                }
                iVar9 = iVar9 + (uint)bVar2;
                if (local_24 <= iVar9) {
                  local_24 = iVar9;
                }
                if (iVar4 <= local_20) {
                  local_20 = iVar4;
                }
                if (local_28 <= iVar4) {
                  local_28 = iVar4;
                }
                bVar1 = pbVar7[bVar2];
                pbVar7 = pbVar7 + bVar2 + 1;
                bVar10 = (bool)(bVar1 & 1);
                bVar2 = bVar1 >> 1;
                if (!bVar10 && bVar2 != 0) break;
                if (bVar2 == 0) goto joined_r0x00405eb2;
              }
LAB_00405ec9:
              do {
                pbVar8 = pbVar7 + 1;
                if (iVar9 <= local_1c) {
                  local_1c = iVar9;
                }
                iVar9 = iVar9 + (uint)bVar2;
                if (local_24 <= iVar9) {
                  local_24 = iVar9;
                }
                if (iVar4 <= local_20) {
                  local_20 = iVar4;
                }
                if (local_28 <= iVar4) {
                  local_28 = iVar4;
                }
                pbVar7 = pbVar7 + 2;
                bVar10 = (bool)(*pbVar8 & 1);
                bVar2 = *pbVar8 >> 1;
              } while (!bVar10 && bVar2 != 0);
              if (!bVar10) goto LAB_00405f2e;
            } while (bVar2 != 0);
          }
        } while (bVar10);
      }
LAB_00405f2e:
      iVar4 = iVar4 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  if ((param_5 & 1) != 0) {
    iVar9 = param_3 * 2 - local_1c;
    local_1c = param_3 * 2 - local_24;
    local_24 = iVar9;
  }
  if ((param_5 & 2) != 0) {
    iVar9 = param_4 * 2 - local_20;
    local_20 = param_4 * 2 - local_28;
    local_28 = iVar9;
  }
  *param_6 = local_1c;
  param_6[1] = local_20;
  param_6[2] = local_24;
  param_6[3] = local_28;
  return 0;
}
```

---

---

## FUN_00405f89 — 0x405f89

- Classification : internal
- Corps : `0x405f89–0x40620b`
- État : pseudocode obtenu
- Evidence : `ev_216b27c2ab5226eceb6146b0d7677ccc857bd80b6bbaead907ef130e0d5517ba`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40629e` — `FUN_0040629e`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00405f89(int *param_1,undefined4 param_2,int param_3,int param_4,undefined4 *param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  char *pcVar13;
  bool bVar14;
  int local_14;
  
  piVar1 = (int *)*param_1;
  iVar11 = piVar1[1];
  iVar6 = iVar11 + 1;
  if ((iVar6 == 0 || iVar11 < -1) || (iVar2 = piVar1[2], iVar2 < 0)) {
    return -1;
  }
  iVar3 = param_1[1];
  iVar7 = iVar3;
  if (iVar3 < 1) {
    iVar7 = 0;
  }
  iVar4 = param_1[2];
  local_14 = iVar4;
  if (iVar4 < 1) {
    local_14 = 0;
  }
  iVar8 = param_1[3];
  if (iVar11 <= param_1[3]) {
    iVar8 = iVar11;
  }
  iVar11 = param_1[4];
  if (iVar2 <= param_1[4]) {
    iVar11 = iVar2;
  }
  if ((iVar8 < iVar7) || (iVar11 < local_14)) {
    return -2;
  }
  iVar2 = *piVar1;
  DAT_00498dc1 = param_5;
  if (param_5 != (undefined4 *)0x0) {
    *param_5 = CONCAT22((short)param_1[3] - (short)param_1[1],(short)param_1[4] - (short)param_1[2])
    ;
    param_5[1] = CONCAT22((short)param_3,(undefined2)param_4);
    param_5[2] = 0;
    param_5[3] = 0;
    param_5[4] = 0xffffffff;
    param_5[5] = 0xffffffff;
  }
  iVar9 = (iVar8 + 1) - iVar7;
  DAT_00498de9 = 0x7fffffff;
  DAT_00498ded = 0x7fffffff;
  DAT_00498df1 = -0x7fffffff;
  DAT_00498df5 = -0x7fffffff;
  DAT_00498dc9 = (char *)(local_14 * iVar6 + iVar2 + iVar7);
  do {
    bVar14 = local_14 == iVar11;
    if (iVar11 < local_14) {
      if (param_5 != (undefined4 *)0x0) {
        param_5[2] = DAT_00498de9 - (param_3 + iVar3);
        param_5[3] = DAT_00498ded - (param_4 + iVar4);
        param_5[4] = DAT_00498df1 - (param_3 + iVar3);
        param_5[5] = DAT_00498df5 - (param_4 + iVar4);
      }
      DAT_00498dd1 = param_5 + 6;
      iVar11 = (DAT_00498df1 + 1) - DAT_00498de9;
      DAT_00498dc9 = (char *)(DAT_00498ded * iVar6 + iVar2 + DAT_00498de9);
      for (local_14 = DAT_00498ded; local_14 <= DAT_00498df5; local_14 = local_14 + 1) {
        FUN_0040629e(iVar11,param_2,iVar7);
        DAT_00498dc9 = (char *)((int)DAT_00498dc9 + iVar6);
      }
      return (int)DAT_00498dd1 - (int)param_5;
    }
    DAT_00498dcd = DAT_00498dc9;
    iVar12 = iVar9;
    pcVar13 = DAT_00498dc9;
    do {
      if (iVar12 == 0) break;
      iVar12 = iVar12 + -1;
      bVar14 = (char)param_2 == *pcVar13;
      pcVar13 = pcVar13 + 1;
    } while (bVar14);
    iVar5 = DAT_00498df1;
    if (!bVar14) {
      if (local_14 <= DAT_00498ded) {
        DAT_00498ded = local_14;
      }
      if (DAT_00498df5 <= local_14) {
        DAT_00498df5 = local_14;
      }
      iVar10 = iVar8 - iVar12;
      if (DAT_00498de9 <= iVar8 - iVar12) {
        iVar10 = DAT_00498de9;
      }
      DAT_00498dcd = DAT_00498dc9 + iVar9 + -1;
      bVar14 = DAT_00498dcd == (char *)0x0;
      iVar12 = iVar9;
      pcVar13 = DAT_00498dcd;
      do {
        if (iVar12 == 0) break;
        iVar12 = iVar12 + -1;
        bVar14 = (char)param_2 == *pcVar13;
        pcVar13 = pcVar13 + -1;
      } while (bVar14);
      DAT_00498de9 = iVar10;
      if ((!bVar14) && (iVar5 = iVar7 + iVar12, iVar7 + iVar12 <= DAT_00498df1)) {
        iVar5 = DAT_00498df1;
      }
    }
    DAT_00498df1 = iVar5;
    DAT_00498dc9 = DAT_00498dc9 + iVar6;
    local_14 = local_14 + 1;
  } while( true );
}
```

---

---

## FUN_0040620c — 0x40620c

- Classification : internal
- Corps : `0x40620c–0x40629d`
- État : pseudocode obtenu
- Evidence : `ev_6d3bafed853088acaf852f675dfe038f8c83a75ad7a8f2824bbffac489eaba5c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0040620c(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  byte *pbVar6;
  bool bVar7;
  
  param_1 = *(int *)(param_2 * 8 + 8 + param_1) + param_1;
  iVar2 = *(int *)(param_1 + 0x14) + 1;
  iVar3 = iVar2 - *(int *)(param_1 + 0xc);
  if (iVar3 != 0 && *(int *)(param_1 + 0xc) <= iVar2) {
    pbVar5 = (byte *)(param_1 + 0x18);
    do {
      bVar1 = *pbVar5;
      pbVar5 = pbVar5 + 1;
      bVar7 = (bool)(bVar1 & 1);
      bVar1 = bVar1 >> 1;
      uVar4 = (uint)bVar1;
      if (!bVar7 && bVar1 != 0) goto LAB_00406255;
      if (bVar1 != 0) goto LAB_0040627b;
joined_r0x00406240:
      if (bVar7) {
        do {
          while( true ) {
            pbVar6 = pbVar5 + 1;
            pbVar5 = pbVar5 + 2;
            bVar7 = (bool)(*pbVar6 & 1);
            bVar1 = *pbVar6 >> 1;
            uVar4 = (uint)bVar1;
            if (!bVar7 && bVar1 != 0) goto LAB_00406255;
            if (bVar1 == 0) break;
LAB_0040627b:
            do {
              while( true ) {
                do {
                  pbVar6 = pbVar5;
                  *pbVar6 = *(byte *)((int)&DAT_0049a610 + (uint)*pbVar6);
                  uVar4 = uVar4 - 1;
                  pbVar5 = pbVar6 + 1;
                } while (uVar4 != 0);
                bVar1 = pbVar6[1];
                pbVar5 = pbVar6 + 2;
                bVar7 = (bool)(bVar1 & 1);
                bVar1 = bVar1 >> 1;
                uVar4 = (uint)bVar1;
                if (!bVar7 && bVar1 != 0) break;
                if (bVar1 == 0) goto joined_r0x00406240;
              }
LAB_00406255:
              do {
                *pbVar5 = *(byte *)((int)&DAT_0049a610 + (uint)*pbVar5);
                pbVar6 = pbVar5 + 1;
                pbVar5 = pbVar5 + 2;
                bVar7 = (bool)(*pbVar6 & 1);
                bVar1 = *pbVar6 >> 1;
                uVar4 = (uint)bVar1;
              } while (!bVar7 && bVar1 != 0);
              if (!bVar7) goto LAB_00406293;
            } while (bVar1 != 0);
          }
        } while (bVar7);
      }
LAB_00406293:
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return 0;
}
```

---

# 0005_batch_0001 — détails (2/2)

## FUN_00404c5a — 0x404c5a

- Classification : internal (Ghidra FunctionManager)
- Corps : `0x404c5a–0x4050b5`, `0x4050c1–0x405131`
- État : pseudocode obtenu
- Evidence : `ev_1eb440f6f52737f4d7546d4e51ccda1ed6f23e5fb292436f4de53cf7c5c3b283`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs observés

- `0x405132` — `FUN_00405132`

### Chaînes référencées observées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00404c5a(int *param_1,int param_2,int param_3,int param_4,int param_5)

{
  undefined1 uVar1;
  int *piVar2;
  undefined3 uVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined1 *puVar13;
  uint uVar14;
  uint uVar15;
  byte bVar16;
  byte bVar18;
  uint uVar17;
  byte *pbVar19;
  byte *pbVar20;
  undefined4 *puVar21;
  bool bVar22;
  bool bVar23;
  undefined1 *local_30;
  undefined1 *local_2c;
  undefined4 *local_28;
  int local_24;
  
  piVar2 = (int *)*param_1;
  iVar9 = piVar2[1];
  iVar5 = iVar9 + 1;
  if ((iVar5 == 0 || iVar9 < -1) || (iVar10 = piVar2[2], iVar10 < 0)) {
    return 0xffffffff;
  }
  iVar11 = param_1[1];
  iVar6 = iVar11;
  if (iVar11 < 1) {
    iVar6 = 0;
  }
  iVar12 = param_1[2];
  iVar7 = iVar12;
  if (iVar12 < 1) {
    iVar7 = 0;
  }
  iVar8 = param_1[3];
  if (iVar9 <= param_1[3]) {
    iVar8 = iVar9;
  }
  iVar9 = param_1[4];
  if (iVar10 <= param_1[4]) {
    iVar9 = iVar10;
  }
  if ((iVar8 < iVar6) || (iVar9 < iVar7)) {
    return 0xfffffffe;
  }
  param_4 = param_4 + iVar11;
  param_5 = param_5 + iVar12;
  param_2 = *(int *)(param_3 * 8 + 8 + param_2) + param_2;
  iVar10 = *(int *)(param_2 + 8) + param_4;
  local_24 = *(int *)(param_2 + 0xc) + param_5;
  iVar11 = *(int *)(param_2 + 0x10) + param_4;
  iVar12 = *(int *)(param_2 + 0x14) + param_5;
  pbVar19 = (byte *)(param_2 + 0x18);
  if ((iVar11 < iVar10) || (iVar12 < local_24)) {
    return 0xfffffffc;
  }
  bVar16 = (((iVar10 - iVar6 < 0) * '\x02' + (iVar8 - iVar10 < 0)) * '\x02' + (local_24 - iVar7 < 0)
           ) * '\x02' + (iVar9 - local_24 < 0);
  bVar18 = (((iVar11 - iVar6 < 0) * '\x02' + (iVar8 - iVar11 < 0)) * '\x02' + (iVar12 - iVar7 < 0))
           * '\x02' + (iVar9 - iVar12 < 0);
  if ((bVar18 & bVar16) != 0) {
    return 0xfffffffd;
  }
  if (bVar16 == 0 && bVar18 == 0) {
    FUN_00405132(param_1,param_2,param_4 - param_1[1],param_5 - param_1[2],iVar5);
    return 0;
  }
  local_28 = (undefined4 *)(local_24 * iVar5 + *piVar2 + iVar10);
LAB_00404e06:
  if (local_24 < iVar7) {
    do {
      bVar4 = *pbVar19;
      pbVar19 = pbVar19 + 1;
      bVar22 = (bool)(bVar4 & 1);
      bVar4 = bVar4 >> 1;
      if (bVar22 || bVar4 == 0) {
        if (bVar4 != 0) {
          pbVar19 = pbVar19 + (bVar4 - 1);
        }
        else if (!bVar22) goto code_r0x00404e02;
      }
      pbVar19 = pbVar19 + 1;
    } while( true );
  }
  local_2c = (undefined1 *)((int)local_28 + (iVar6 - iVar10));
  local_30 = (undefined1 *)((int)local_28 + (iVar8 - iVar10));
LAB_00405108:
  if (iVar12 < local_24) {
    return 0;
  }
  if (iVar9 < local_24) {
    return 0;
  }
  puVar21 = local_28;
  if ((bVar16 & 8) == 0) {
    if ((bVar18 & 4) == 0) {
      bVar4 = *pbVar19;
      pbVar19 = pbVar19 + 1;
      bVar22 = (bool)(bVar4 & 1);
      bVar4 = bVar4 >> 1;
      uVar14 = (uint)bVar4;
      if (!bVar22 && bVar4 != 0) goto LAB_00404e7d;
      if (bVar4 != 0) goto LAB_00404eae;
joined_r0x00404e5e:
      if (bVar22) {
LAB_00404e64:
        do {
          pbVar20 = pbVar19 + 1;
          puVar21 = (undefined4 *)((int)puVar21 + (uint)*pbVar19);
          pbVar19 = pbVar19 + 2;
          bVar22 = (bool)(*pbVar20 & 1);
          bVar4 = *pbVar20 >> 1;
          uVar14 = (uint)bVar4;
          if (!bVar22 && bVar4 != 0) goto LAB_00404e7d;
          if (bVar4 != 0) {
LAB_00404eae:
            uVar14 = uVar14 & 0xff;
joined_r0x00404eb5:
            for (; uVar14 != 0; uVar14 = uVar14 - 4) {
              if ((int)uVar14 < 4) goto LAB_00404efa;
              *(undefined1 *)puVar21 = *(undefined1 *)((int)&DAT_0049a610 + (uint)*pbVar19);
              *(undefined1 *)((int)puVar21 + 1) =
                   *(undefined1 *)((int)&DAT_0049a610 + (uint)pbVar19[1]);
              *(undefined1 *)((int)puVar21 + 2) =
                   *(undefined1 *)((int)&DAT_0049a610 + (uint)pbVar19[2]);
              *(undefined1 *)((int)puVar21 + 3) =
                   *(undefined1 *)((int)&DAT_0049a610 + (uint)pbVar19[3]);
              pbVar19 = pbVar19 + 4;
              puVar21 = puVar21 + 1;
            }
            goto LAB_00404f09;
          }
        } while (bVar22);
      }
    }
    else {
      bVar4 = *pbVar19;
      pbVar19 = pbVar19 + 1;
      bVar22 = (bool)(bVar4 & 1);
      bVar4 = bVar4 >> 1;
      if (!bVar22 && bVar4 != 0) goto LAB_00404fd7;
      if (bVar4 != 0) goto LAB_00405026;
joined_r0x00404fb8:
      if (bVar22) {
LAB_00404fbe:
        do {
          pbVar20 = pbVar19 + 1;
          puVar21 = (undefined4 *)((int)puVar21 + (uint)*pbVar19);
          pbVar19 = pbVar19 + 2;
          bVar22 = (bool)(*pbVar20 & 1);
          bVar4 = *pbVar20 >> 1;
          if (!bVar22 && bVar4 != 0) goto LAB_00404fd7;
          if (bVar4 != 0) {
LAB_00405026:
            uVar14 = (uint)bVar4;
LAB_00405029:
            if ((int)local_30 < (int)puVar21) goto LAB_004050ea;
            puVar13 = (undefined1 *)((int)puVar21 + ((uVar14 - 1) - (int)local_30));
            uVar15 = ~((int)puVar13 >> 0x1f) & (uint)puVar13;
            for (iVar10 = uVar14 - uVar15; iVar10 != 0; iVar10 = iVar10 + -4) {
              if (iVar10 < 4) goto LAB_0040508a;
              *(undefined1 *)puVar21 = *(undefined1 *)((int)&DAT_0049a610 + (uint)*pbVar19);
              *(undefined1 *)((int)puVar21 + 1) =
                   *(undefined1 *)((int)&DAT_0049a610 + (uint)pbVar19[1]);
              *(undefined1 *)((int)puVar21 + 2) =
                   *(undefined1 *)((int)&DAT_0049a610 + (uint)pbVar19[2]);
              *(undefined1 *)((int)puVar21 + 3) =
                   *(undefined1 *)((int)&DAT_0049a610 + (uint)pbVar19[3]);
              pbVar19 = pbVar19 + 4;
              puVar21 = puVar21 + 1;
            }
            goto LAB_00405099;
          }
        } while (bVar22);
      }
    }
  }
  else {
    bVar4 = *pbVar19;
    pbVar19 = pbVar19 + 1;
    bVar22 = (bool)(bVar4 & 1);
    bVar4 = bVar4 >> 1;
    if (!bVar22 && bVar4 != 0) goto LAB_00404f41;
    if (bVar4 != 0) goto LAB_00404f72;
joined_r0x00404f2a:
    if (bVar22) {
      do {
        while( true ) {
          pbVar20 = pbVar19 + 1;
          puVar21 = (undefined4 *)((int)puVar21 + (uint)*pbVar19);
          pbVar19 = pbVar19 + 2;
          bVar22 = (bool)(*pbVar20 & 1);
          bVar4 = *pbVar20 >> 1;
          if (!bVar22 && bVar4 != 0) goto LAB_00404f41;
          if (bVar4 == 0) break;
LAB_00404f72:
          do {
            while( true ) {
              uVar14 = (uint)bVar4;
              iVar10 = (int)local_2c - (int)puVar21;
              if (iVar10 < (int)uVar14) {
                if (-1 < iVar10) {
                  puVar21 = (undefined4 *)((int)puVar21 + iVar10);
                  uVar14 = uVar14 - iVar10;
                  pbVar19 = pbVar19 + iVar10;
                }
                if ((bVar18 & 4) == 0) goto joined_r0x00404eb5;
                goto LAB_00405029;
              }
              puVar21 = (undefined4 *)((int)puVar21 + uVar14);
              bVar4 = pbVar19[uVar14];
              pbVar19 = pbVar19 + uVar14 + 1;
              bVar22 = (bool)(bVar4 & 1);
              bVar4 = bVar4 >> 1;
              if (!bVar22 && bVar4 != 0) break;
              if (bVar4 == 0) goto joined_r0x00404f2a;
            }
LAB_00404f41:
            do {
              uVar14 = (uint)bVar4;
              iVar10 = (int)local_2c - (int)puVar21;
              if (iVar10 < (int)uVar14) {
                if (-1 < iVar10) {
                  puVar21 = (undefined4 *)((int)puVar21 + iVar10);
                  uVar14 = uVar14 - iVar10;
                }
                if ((bVar18 & 4) == 0) goto LAB_00404e80;
                goto LAB_00404fda;
              }
              puVar21 = (undefined4 *)((int)puVar21 + uVar14);
              pbVar20 = pbVar19 + 1;
              pbVar19 = pbVar19 + 2;
              bVar22 = (bool)(*pbVar20 & 1);
              bVar4 = *pbVar20 >> 1;
            } while (!bVar22 && bVar4 != 0);
            if (!bVar22) goto LAB_004050f9;
          } while (bVar4 != 0);
        }
      } while (bVar22);
    }
  }
  goto LAB_004050f9;
code_r0x00404e02:
  local_28 = (undefined4 *)((int)local_28 + iVar5);
  local_24 = local_24 + 1;
  goto LAB_00404e06;
LAB_0040508a:
  do {
    *(undefined1 *)puVar21 = *(undefined1 *)((int)&DAT_0049a610 + (uint)*pbVar19);
    pbVar19 = pbVar19 + 1;
    puVar21 = (undefined4 *)((int)puVar21 + 1);
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
LAB_00405099:
  puVar21 = (undefined4 *)((int)puVar21 + uVar15);
  bVar4 = pbVar19[uVar15];
  pbVar19 = pbVar19 + uVar15 + 1;
  bVar22 = (bool)(bVar4 & 1);
  bVar4 = bVar4 >> 1;
  if (bVar22 || bVar4 == 0) {
    if (bVar4 == 0) goto joined_r0x00404fb8;
    goto LAB_00405026;
  }
LAB_00404fd7:
  do {
    uVar14 = (uint)bVar4;
LAB_00404fda:
    if ((int)local_30 < (int)puVar21) goto LAB_004050d9;
    puVar13 = (undefined1 *)((int)puVar21 + ((uVar14 - 1) - (int)local_30));
    uVar17 = ~((int)puVar13 >> 0x1f) & (uint)puVar13;
    uVar14 = uVar14 - uVar17;
    pbVar20 = pbVar19 + 1;
    uVar1 = *(undefined1 *)((int)&DAT_0049a610 + (uint)*pbVar19);
    for (uVar15 = uVar14 & 3; uVar15 != 0; uVar15 = uVar15 - 1) {
      *(undefined1 *)puVar21 = uVar1;
      puVar21 = (undefined4 *)((int)puVar21 + 1);
    }
    for (uVar14 = uVar14 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
      *puVar21 = CONCAT31(CONCAT21(CONCAT11(uVar1,uVar1),uVar1),uVar1);
      puVar21 = puVar21 + 1;
    }
    puVar21 = (undefined4 *)((int)puVar21 + uVar17);
    pbVar19 = pbVar19 + 2;
    bVar22 = (bool)(*pbVar20 & 1);
    bVar4 = *pbVar20 >> 1;
  } while (!bVar22 && bVar4 != 0);
  if (!bVar22) goto LAB_004050f9;
  if (bVar4 == 0) goto LAB_00404fbe;
  goto LAB_00405026;
LAB_004050d9:
  do {
    pbVar20 = pbVar19 + 1;
    pbVar19 = pbVar19 + 2;
    bVar22 = (bool)(*pbVar20 & 1);
    bVar4 = *pbVar20 >> 1;
  } while (!bVar22 && bVar4 != 0);
  if (bVar22) {
    if (bVar4 == 0) goto LAB_004050c1;
    while( true ) {
      uVar14 = (uint)bVar4;
LAB_004050ea:
      bVar4 = pbVar19[uVar14];
      pbVar19 = pbVar19 + uVar14 + 1;
      bVar22 = (bool)(bVar4 & 1);
      bVar4 = bVar4 >> 1;
      bVar23 = bVar4 != 0;
      if (!bVar22 && bVar23) break;
      while (!bVar23) {
        if (!bVar22) goto LAB_004050f9;
LAB_004050c1:
        pbVar20 = pbVar19 + 1;
        pbVar19 = pbVar19 + 2;
        bVar22 = (bool)(*pbVar20 & 1);
        bVar4 = *pbVar20 >> 1;
        bVar23 = bVar4 != 0;
        if (!bVar22 && bVar23) goto LAB_004050d9;
      }
    }
    goto LAB_004050d9;
  }
LAB_004050f9:
  local_28 = (undefined4 *)((int)local_28 + iVar5);
  local_2c = local_2c + iVar5;
  local_30 = local_30 + iVar5;
  local_24 = local_24 + 1;
  goto LAB_00405108;
LAB_00404efa:
  do {
    *(undefined1 *)puVar21 = *(undefined1 *)((int)&DAT_0049a610 + (uint)*pbVar19);
    pbVar19 = pbVar19 + 1;
    puVar21 = (undefined4 *)((int)puVar21 + 1);
    uVar14 = uVar14 - 1;
  } while (uVar14 != 0);
LAB_00404f09:
  bVar4 = *pbVar19;
  pbVar19 = pbVar19 + 1;
  bVar22 = (bool)(bVar4 & 1);
  bVar4 = bVar4 >> 1;
  uVar14 = (uint)bVar4;
  if (bVar22 || bVar4 == 0) {
    if (bVar4 == 0) goto joined_r0x00404e5e;
    goto LAB_00404eae;
  }
LAB_00404e7d:
  do {
    uVar14 = uVar14 & 0xff;
LAB_00404e80:
    pbVar20 = pbVar19 + 1;
    uVar1 = *(undefined1 *)((int)&DAT_0049a610 + (uint)*pbVar19);
    for (uVar15 = uVar14 & 3; uVar15 != 0; uVar15 = uVar15 - 1) {
      *(undefined1 *)puVar21 = uVar1;
      puVar21 = (undefined4 *)((int)puVar21 + 1);
    }
    uVar3 = CONCAT21(CONCAT11(uVar1,uVar1),uVar1);
    for (uVar14 = uVar14 >> 2; uVar14 != 0; uVar14 = uVar14 - 1) {
      *puVar21 = CONCAT31(uVar3,uVar1);
      puVar21 = puVar21 + 1;
    }
    pbVar19 = pbVar19 + 2;
    bVar22 = (bool)(*pbVar20 & 1);
    bVar4 = *pbVar20 >> 1;
    uVar14 = CONCAT31(uVar3,bVar4);
  } while (!bVar22 && bVar4 != 0);
  if (!bVar22) goto LAB_004050f9;
  if (bVar4 == 0) goto LAB_00404e64;
  goto LAB_00404eae;
}
```

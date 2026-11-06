# 0005_batch_0001 — détails (1/2)

## FUN_00404770 — 0x404770

- Classification : internal (Ghidra FunctionManager)
- Corps : `0x404770–0x404af7`, `0x404b03–0x404b73`
- État : pseudocode obtenu
- Evidence : `ev_58324df5aba97aff23abdbdaf7976e4b13966d30e2c803ee17dffad589b3f9c6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs observés

- `0x404b74` — `FUN_00404b74`

### Chaînes référencées observées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00404770(int *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int *piVar1;
  undefined3 uVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  byte bVar14;
  byte bVar16;
  uint uVar15;
  byte *pbVar17;
  byte *pbVar18;
  byte *pbVar19;
  bool bVar20;
  bool bVar21;
  byte *local_30;
  byte *local_2c;
  byte *local_28;
  int local_24;
  
  piVar1 = (int *)*param_1;
  iVar8 = piVar1[1];
  iVar4 = iVar8 + 1;
  if ((iVar4 == 0 || iVar8 < -1) || (iVar9 = piVar1[2], iVar9 < 0)) {
    return 0xffffffff;
  }
  iVar10 = param_1[1];
  iVar5 = iVar10;
  if (iVar10 < 1) {
    iVar5 = 0;
  }
  iVar11 = param_1[2];
  iVar6 = iVar11;
  if (iVar11 < 1) {
    iVar6 = 0;
  }
  iVar7 = param_1[3];
  if (iVar8 <= param_1[3]) {
    iVar7 = iVar8;
  }
  iVar8 = param_1[4];
  if (iVar9 <= param_1[4]) {
    iVar8 = iVar9;
  }
  if ((iVar7 < iVar5) || (iVar8 < iVar6)) {
    return 0xfffffffe;
  }
  param_4 = param_4 + iVar10;
  param_5 = param_5 + iVar11;
  param_2 = *(int *)(param_3 * 8 + 8 + param_2) + param_2;
  iVar9 = *(int *)(param_2 + 8) + param_4;
  local_24 = *(int *)(param_2 + 0xc) + param_5;
  iVar10 = *(int *)(param_2 + 0x10) + param_4;
  iVar11 = *(int *)(param_2 + 0x14) + param_5;
  pbVar17 = (byte *)(param_2 + 0x18);
  if ((iVar10 < iVar9) || (iVar11 < local_24)) {
    return 0xfffffffc;
  }
  bVar14 = (((iVar9 - iVar5 < 0) * '\x02' + (iVar7 - iVar9 < 0)) * '\x02' + (local_24 - iVar6 < 0))
           * '\x02' + (iVar8 - local_24 < 0);
  bVar16 = (((iVar10 - iVar5 < 0) * '\x02' + (iVar7 - iVar10 < 0)) * '\x02' + (iVar11 - iVar6 < 0))
           * '\x02' + (iVar8 - iVar11 < 0);
  if ((bVar16 & bVar14) != 0) {
    return 0xfffffffd;
  }
  if (bVar14 == 0 && bVar16 == 0) {
    FUN_00404b74(param_1,param_2,param_4 - param_1[1],param_5 - param_1[2],iVar4);
    return 0;
  }
  local_28 = (byte *)(local_24 * iVar4 + *piVar1 + iVar9);
LAB_0040491c:
  if (local_24 < iVar6) {
    do {
      bVar3 = *pbVar17;
      pbVar17 = pbVar17 + 1;
      bVar20 = (bool)(bVar3 & 1);
      bVar3 = bVar3 >> 1;
      if (bVar20 || bVar3 == 0) {
        if (bVar3 != 0) {
          pbVar17 = pbVar17 + (bVar3 - 1);
        }
        else if (!bVar20) goto code_r0x00404918;
      }
      pbVar17 = pbVar17 + 1;
    } while( true );
  }
  local_2c = local_28 + (iVar5 - iVar9);
  local_30 = local_28 + (iVar7 - iVar9);
LAB_00404b4a:
  if (iVar11 < local_24) {
    return 0;
  }
  if (iVar8 < local_24) {
    return 0;
  }
  pbVar19 = local_28;
  if ((bVar14 & 8) == 0) {
    if ((bVar16 & 4) == 0) {
      bVar3 = *pbVar17;
      pbVar17 = pbVar17 + 1;
      bVar20 = (bool)(bVar3 & 1);
      bVar3 = bVar3 >> 1;
      uVar12 = (uint)bVar3;
      if (!bVar20 && bVar3 != 0) goto LAB_00404987;
      if (bVar3 != 0) goto LAB_004049b0;
joined_r0x00404970:
      if (bVar20) {
        do {
          while( true ) {
            pbVar18 = pbVar17 + 1;
            pbVar19 = pbVar19 + *pbVar17;
            pbVar17 = pbVar17 + 2;
            bVar20 = (bool)(*pbVar18 & 1);
            bVar3 = *pbVar18 >> 1;
            uVar12 = (uint)bVar3;
            if (!bVar20 && bVar3 != 0) goto LAB_00404987;
            if (bVar3 == 0) break;
LAB_004049b0:
            do {
              while( true ) {
                uVar12 = uVar12 & 0xff;
LAB_004049b3:
                for (uVar13 = uVar12 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
                  *pbVar19 = *pbVar17;
                  pbVar17 = pbVar17 + 1;
                  pbVar19 = pbVar19 + 1;
                }
                pbVar18 = pbVar17;
                for (uVar12 = uVar12 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                  *(undefined4 *)pbVar19 = *(undefined4 *)pbVar18;
                  pbVar18 = pbVar18 + 4;
                  pbVar19 = pbVar19 + 4;
                }
                pbVar17 = pbVar18 + 1;
                bVar20 = (bool)(*pbVar18 & 1);
                bVar3 = *pbVar18 >> 1;
                uVar12 = (uint)bVar3;
                if (!bVar20 && bVar3 != 0) break;
                if (bVar3 == 0) goto joined_r0x00404970;
              }
LAB_00404987:
              do {
                uVar12 = uVar12 & 0xff;
LAB_0040498a:
                bVar3 = *pbVar17;
                pbVar18 = pbVar17 + 1;
                for (uVar13 = uVar12 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
                  *pbVar19 = bVar3;
                  pbVar19 = pbVar19 + 1;
                }
                uVar2 = CONCAT21(CONCAT11(bVar3,bVar3),bVar3);
                for (uVar12 = uVar12 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                  *(uint *)pbVar19 = CONCAT31(uVar2,bVar3);
                  pbVar19 = pbVar19 + 4;
                }
                pbVar17 = pbVar17 + 2;
                bVar20 = (bool)(*pbVar18 & 1);
                bVar3 = *pbVar18 >> 1;
                uVar12 = CONCAT31(uVar2,bVar3);
              } while (!bVar20 && bVar3 != 0);
              if (!bVar20) goto LAB_00404b3b;
            } while (bVar3 != 0);
          }
        } while (bVar20);
      }
    }
    else {
      bVar3 = *pbVar17;
      pbVar17 = pbVar17 + 1;
      bVar20 = (bool)(bVar3 & 1);
      bVar3 = bVar3 >> 1;
      if (!bVar20 && bVar3 != 0) goto LAB_00404a7d;
      if (bVar3 != 0) goto LAB_00404ac0;
joined_r0x00404a62:
      if (bVar20) {
        do {
          while( true ) {
            pbVar18 = pbVar17 + 1;
            pbVar19 = pbVar19 + *pbVar17;
            pbVar17 = pbVar17 + 2;
            bVar20 = (bool)(*pbVar18 & 1);
            bVar3 = *pbVar18 >> 1;
            if (!bVar20 && bVar3 != 0) goto LAB_00404a7d;
            if (bVar3 == 0) break;
LAB_00404ac0:
            do {
              while( true ) {
                uVar12 = (uint)bVar3;
LAB_00404ac3:
                if ((int)local_30 < (int)pbVar19) goto LAB_00404b2c;
                uVar15 = ~((int)(pbVar19 + ((uVar12 - 1) - (int)local_30)) >> 0x1f) &
                         (uint)(pbVar19 + ((uVar12 - 1) - (int)local_30));
                for (uVar13 = uVar12 - uVar15 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
                  *pbVar19 = *pbVar17;
                  pbVar17 = pbVar17 + 1;
                  pbVar19 = pbVar19 + 1;
                }
                for (uVar12 = uVar12 - uVar15 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                  *(undefined4 *)pbVar19 = *(undefined4 *)pbVar17;
                  pbVar17 = pbVar17 + 4;
                  pbVar19 = pbVar19 + 4;
                }
                pbVar19 = pbVar19 + uVar15;
                bVar3 = pbVar17[uVar15];
                pbVar17 = pbVar17 + uVar15 + 1;
                bVar20 = (bool)(bVar3 & 1);
                bVar3 = bVar3 >> 1;
                if (!bVar20 && bVar3 != 0) break;
                if (bVar3 == 0) goto joined_r0x00404a62;
              }
LAB_00404a7d:
              do {
                uVar12 = (uint)bVar3;
LAB_00404a80:
                if ((int)local_30 < (int)pbVar19) goto LAB_00404b1b;
                uVar15 = ~((int)(pbVar19 + ((uVar12 - 1) - (int)local_30)) >> 0x1f) &
                         (uint)(pbVar19 + ((uVar12 - 1) - (int)local_30));
                uVar12 = uVar12 - uVar15;
                bVar3 = *pbVar17;
                pbVar18 = pbVar17 + 1;
                for (uVar13 = uVar12 & 3; uVar13 != 0; uVar13 = uVar13 - 1) {
                  *pbVar19 = bVar3;
                  pbVar19 = pbVar19 + 1;
                }
                for (uVar12 = uVar12 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                  *(uint *)pbVar19 = CONCAT31(CONCAT21(CONCAT11(bVar3,bVar3),bVar3),bVar3);
                  pbVar19 = pbVar19 + 4;
                }
                pbVar19 = pbVar19 + uVar15;
                pbVar17 = pbVar17 + 2;
                bVar20 = (bool)(*pbVar18 & 1);
                bVar3 = *pbVar18 >> 1;
              } while (!bVar20 && bVar3 != 0);
              if (!bVar20) goto LAB_00404b3b;
            } while (bVar3 != 0);
          }
        } while (bVar20);
      }
    }
  }
  else {
    bVar3 = *pbVar17;
    pbVar17 = pbVar17 + 1;
    bVar20 = (bool)(bVar3 & 1);
    bVar3 = bVar3 >> 1;
    if (!bVar20 && bVar3 != 0) goto LAB_004049ef;
    if (bVar3 != 0) goto LAB_00404a20;
joined_r0x004049d8:
    if (bVar20) {
      do {
        while( true ) {
          pbVar18 = pbVar17 + 1;
          pbVar19 = pbVar19 + *pbVar17;
          pbVar17 = pbVar17 + 2;
          bVar20 = (bool)(*pbVar18 & 1);
          bVar3 = *pbVar18 >> 1;
          if (!bVar20 && bVar3 != 0) goto LAB_004049ef;
          if (bVar3 == 0) break;
LAB_00404a20:
          do {
            while( true ) {
              uVar12 = (uint)bVar3;
              iVar9 = (int)local_2c - (int)pbVar19;
              if (iVar9 < (int)uVar12) {
                if (-1 < iVar9) {
                  pbVar19 = pbVar19 + iVar9;
                  uVar12 = uVar12 - iVar9;
                  pbVar17 = pbVar17 + iVar9;
                }
                if ((bVar16 & 4) == 0) goto LAB_004049b3;
                goto LAB_00404ac3;
              }
              pbVar19 = pbVar19 + uVar12;
              bVar3 = pbVar17[uVar12];
              pbVar17 = pbVar17 + uVar12 + 1;
              bVar20 = (bool)(bVar3 & 1);
              bVar3 = bVar3 >> 1;
              if (!bVar20 && bVar3 != 0) break;
              if (bVar3 == 0) goto joined_r0x004049d8;
            }
LAB_004049ef:
            do {
              uVar12 = (uint)bVar3;
              iVar9 = (int)local_2c - (int)pbVar19;
              if (iVar9 < (int)uVar12) {
                if (-1 < iVar9) {
                  pbVar19 = pbVar19 + iVar9;
                  uVar12 = uVar12 - iVar9;
                }
                if ((bVar16 & 4) == 0) goto LAB_0040498a;
                goto LAB_00404a80;
              }
              pbVar19 = pbVar19 + uVar12;
              pbVar18 = pbVar17 + 1;
              pbVar17 = pbVar17 + 2;
              bVar20 = (bool)(*pbVar18 & 1);
              bVar3 = *pbVar18 >> 1;
            } while (!bVar20 && bVar3 != 0);
            if (!bVar20) goto LAB_00404b3b;
          } while (bVar3 != 0);
        }
      } while (bVar20);
    }
  }
  goto LAB_00404b3b;
code_r0x00404918:
  local_28 = local_28 + iVar4;
  local_24 = local_24 + 1;
  goto LAB_0040491c;
LAB_00404b1b:
  do {
    pbVar19 = pbVar17 + 1;
    pbVar17 = pbVar17 + 2;
    bVar20 = (bool)(*pbVar19 & 1);
    bVar3 = *pbVar19 >> 1;
  } while (!bVar20 && bVar3 != 0);
  if (bVar20) {
    if (bVar3 == 0) goto LAB_00404b03;
    while( true ) {
      uVar12 = (uint)bVar3;
LAB_00404b2c:
      bVar3 = pbVar17[uVar12];
      pbVar17 = pbVar17 + uVar12 + 1;
      bVar20 = (bool)(bVar3 & 1);
      bVar3 = bVar3 >> 1;
      bVar21 = bVar3 != 0;
      if (!bVar20 && bVar21) break;
      while (!bVar21) {
        if (!bVar20) goto LAB_00404b3b;
LAB_00404b03:
        pbVar19 = pbVar17 + 1;
        pbVar17 = pbVar17 + 2;
        bVar20 = (bool)(*pbVar19 & 1);
        bVar3 = *pbVar19 >> 1;
        bVar21 = bVar3 != 0;
        if (!bVar20 && bVar21) goto LAB_00404b1b;
      }
    }
    goto LAB_00404b1b;
  }
LAB_00404b3b:
  local_28 = local_28 + iVar4;
  local_2c = local_2c + iVar4;
  local_30 = local_30 + iVar4;
  local_24 = local_24 + 1;
  goto LAB_00404b4a;
}
```

---

---

## FUN_00404b74 — 0x404b74

- Classification : internal (Ghidra FunctionManager)
- Corps : `0x404b74–0x404c3a`
- État : pseudocode obtenu
- Evidence : `ev_cd7a5869adddd6938a8888e4a1d3fc461b90bfab9881087a5c7d3eecce544160`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs observés

- aucun relevé

### Chaînes référencées observées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00404b74(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined3 uVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  byte *pbVar9;
  byte *pbVar10;
  byte *pbVar11;
  byte *pbVar12;
  bool bVar13;
  
  iVar1 = ((int *)*param_1)[1];
  iVar4 = iVar1 + 1;
  if (iVar4 != 0 && -2 < iVar1) {
    iVar1 = *(int *)(param_2 + 0xc);
    pbVar11 = (byte *)(*(int *)*param_1 + *(int *)(param_2 + 8) + param_3 + param_1[1] +
                      (iVar1 + param_4 + param_1[2]) * iVar4);
    iVar5 = *(int *)(param_2 + 0x14) + 1;
    iVar6 = iVar5 - iVar1;
    if (iVar6 != 0 && iVar1 <= iVar5) {
      pbVar9 = (byte *)(param_2 + 0x18);
      do {
        bVar3 = *pbVar9;
        pbVar9 = pbVar9 + 1;
        bVar13 = (bool)(bVar3 & 1);
        bVar3 = bVar3 >> 1;
        uVar8 = (uint)bVar3;
        pbVar12 = pbVar11;
        if (!bVar13 && bVar3 != 0) goto LAB_00404be8;
        if (bVar3 != 0) goto LAB_00404c11;
joined_r0x00404bd1:
        if (bVar13) {
          do {
            while( true ) {
              pbVar10 = pbVar9 + 1;
              pbVar12 = pbVar12 + *pbVar9;
              pbVar9 = pbVar9 + 2;
              bVar13 = (bool)(*pbVar10 & 1);
              bVar3 = *pbVar10 >> 1;
              uVar8 = (uint)bVar3;
              if (!bVar13 && bVar3 != 0) goto LAB_00404be8;
              if (bVar3 == 0) break;
LAB_00404c11:
              do {
                while( true ) {
                  for (uVar7 = uVar8 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                    *pbVar12 = *pbVar9;
                    pbVar9 = pbVar9 + 1;
                    pbVar12 = pbVar12 + 1;
                  }
                  pbVar10 = pbVar9;
                  for (uVar8 = (uVar8 & 0xff) >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
                    *(undefined4 *)pbVar12 = *(undefined4 *)pbVar10;
                    pbVar10 = pbVar10 + 4;
                    pbVar12 = pbVar12 + 4;
                  }
                  pbVar9 = pbVar10 + 1;
                  bVar13 = (bool)(*pbVar10 & 1);
                  bVar3 = *pbVar10 >> 1;
                  uVar8 = (uint)bVar3;
                  if (!bVar13 && bVar3 != 0) break;
                  if (bVar3 == 0) goto joined_r0x00404bd1;
                }
LAB_00404be8:
                do {
                  bVar3 = *pbVar9;
                  pbVar10 = pbVar9 + 1;
                  for (uVar7 = uVar8 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                    *pbVar12 = bVar3;
                    pbVar12 = pbVar12 + 1;
                  }
                  uVar2 = CONCAT21(CONCAT11(bVar3,bVar3),bVar3);
                  for (uVar8 = (uVar8 & 0xff) >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
                    *(uint *)pbVar12 = CONCAT31(uVar2,bVar3);
                    pbVar12 = pbVar12 + 4;
                  }
                  pbVar9 = pbVar9 + 2;
                  bVar13 = (bool)(*pbVar10 & 1);
                  bVar3 = *pbVar10 >> 1;
                  uVar8 = CONCAT31(uVar2,bVar3);
                } while (!bVar13 && bVar3 != 0);
                if (!bVar13) goto LAB_00404c2b;
              } while (bVar3 != 0);
            }
          } while (bVar13);
        }
LAB_00404c2b:
        pbVar11 = pbVar11 + iVar4;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
  }
  return 0;
}
```

---

---

## FUN_00404c3b — 0x404c3b

- Classification : internal (Ghidra FunctionManager)
- Corps : `0x404c3b–0x404c59`
- État : pseudocode obtenu
- Evidence : `ev_19fe24686195522a31eed120a3f69795d2bcc57f2f013dcbed384fecd464891c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs observés

- aucun relevé

### Chaînes référencées observées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00404c3b(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_0049a610;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}
```

---

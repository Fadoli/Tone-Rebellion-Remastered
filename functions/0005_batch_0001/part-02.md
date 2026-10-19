# 0005_batch_0001 — détails (2/2)

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

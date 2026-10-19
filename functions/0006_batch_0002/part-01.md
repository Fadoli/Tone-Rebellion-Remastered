# 0006_batch_0002 — détails (1/3)

## FUN_00405132 — 0x405132

- Classification : internal
- Corps : `0x405132–0x405264`
- État : pseudocode obtenu
- Evidence : `ev_454fff2e2e3511aca13c0c13327ffc2dbf5b5e0def37a8c9e9c022917f0fd9dd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00405132(int *param_1,int param_2,int param_3,int param_4)

{
  undefined1 uVar1;
  int iVar2;
  undefined3 uVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  byte *pbVar10;
  byte *pbVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  bool bVar14;
  
  iVar2 = ((int *)*param_1)[1];
  iVar5 = iVar2 + 1;
  if (iVar5 != 0 && -2 < iVar2) {
    iVar2 = *(int *)(param_2 + 0xc);
    puVar12 = (undefined4 *)
              (*(int *)*param_1 + *(int *)(param_2 + 8) + param_3 + param_1[1] +
              (iVar2 + param_4 + param_1[2]) * iVar5);
    iVar6 = *(int *)(param_2 + 0x14) + 1;
    iVar7 = iVar6 - iVar2;
    if (iVar7 != 0 && iVar2 <= iVar6) {
      pbVar10 = (byte *)(param_2 + 0x18);
      do {
        bVar4 = *pbVar10;
        pbVar10 = pbVar10 + 1;
        bVar14 = (bool)(bVar4 & 1);
        bVar4 = bVar4 >> 1;
        uVar9 = (uint)bVar4;
        puVar13 = puVar12;
        if (!bVar14 && bVar4 != 0) goto LAB_004051b2;
        if (bVar4 != 0) goto LAB_004051e3;
joined_r0x00405193:
        if (bVar14) {
          do {
            while( true ) {
              pbVar11 = pbVar10 + 1;
              puVar13 = (undefined4 *)((int)puVar13 + (uint)*pbVar10);
              pbVar10 = pbVar10 + 2;
              bVar14 = (bool)(*pbVar11 & 1);
              bVar4 = *pbVar11 >> 1;
              uVar9 = (uint)bVar4;
              if (!bVar14 && bVar4 != 0) goto LAB_004051b2;
              if (bVar4 == 0) break;
LAB_004051e3:
              do {
                uVar9 = uVar9 & 0xff;
                if (uVar9 != 0) {
                  if (3 < uVar9) {
                    do {
                      *(undefined1 *)puVar13 = *(undefined1 *)((int)&DAT_0049a610 + (uint)*pbVar10);
                      *(undefined1 *)((int)puVar13 + 1) =
                           *(undefined1 *)((int)&DAT_0049a610 + (uint)pbVar10[1]);
                      *(undefined1 *)((int)puVar13 + 2) =
                           *(undefined1 *)((int)&DAT_0049a610 + (uint)pbVar10[2]);
                      *(undefined1 *)((int)puVar13 + 3) =
                           *(undefined1 *)((int)&DAT_0049a610 + (uint)pbVar10[3]);
                      pbVar10 = pbVar10 + 4;
                      puVar13 = puVar13 + 1;
                      uVar9 = uVar9 - 4;
                      if (uVar9 == 0) goto LAB_0040523e;
                    } while (3 < (int)uVar9);
                  }
                  do {
                    *(undefined1 *)puVar13 = *(undefined1 *)((int)&DAT_0049a610 + (uint)*pbVar10);
                    pbVar10 = pbVar10 + 1;
                    puVar13 = (undefined4 *)((int)puVar13 + 1);
                    uVar9 = uVar9 - 1;
                  } while (uVar9 != 0);
                }
LAB_0040523e:
                bVar4 = *pbVar10;
                pbVar10 = pbVar10 + 1;
                bVar14 = (bool)(bVar4 & 1);
                bVar4 = bVar4 >> 1;
                uVar9 = (uint)bVar4;
                if (bVar14 || bVar4 == 0) {
                  if (bVar4 == 0) goto joined_r0x00405193;
                  goto LAB_004051e3;
                }
LAB_004051b2:
                do {
                  pbVar11 = pbVar10 + 1;
                  uVar1 = *(undefined1 *)((int)&DAT_0049a610 + (uint)*pbVar10);
                  for (uVar8 = uVar9 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
                    *(undefined1 *)puVar13 = uVar1;
                    puVar13 = (undefined4 *)((int)puVar13 + 1);
                  }
                  uVar3 = CONCAT21(CONCAT11(uVar1,uVar1),uVar1);
                  for (uVar9 = (uVar9 & 0xff) >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
                    *puVar13 = CONCAT31(uVar3,uVar1);
                    puVar13 = puVar13 + 1;
                  }
                  pbVar10 = pbVar10 + 2;
                  bVar14 = (bool)(*pbVar11 & 1);
                  bVar4 = *pbVar11 >> 1;
                  uVar9 = CONCAT31(uVar3,bVar4);
                } while (!bVar14 && bVar4 != 0);
                if (!bVar14) goto LAB_00405251;
              } while (bVar4 != 0);
            }
          } while (bVar14);
        }
LAB_00405251:
        puVar12 = (undefined4 *)((int)puVar12 + iVar5);
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
  }
  return 0;
}
```

---

## FUN_00405265 — 0x405265

- Classification : internal
- Corps : `0x405265–0x405e10`
- État : pseudocode obtenu
- Evidence : `ev_82e26c10ce82ead5f7bc2bb0256f24cfca46da8be1048ceada8f0bd01d1aa9b3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x404770` — `FUN_00404770`
- `0x404c5a` — `FUN_00404c5a`
- `0x406604` — `FUN_00406604`
- `0x4081ad` — `FUN_004081ad`
- `0x408d1c` — `FUN_00408d1c`
- `0x408d50` — `FUN_00408d50`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

int * FUN_00405265(int *param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5,
                  int param_6,int param_7,int param_8,int param_9,uint param_10)

{
  char cVar1;
  int iVar2;
  int iVar3;
  ulonglong uVar4;
  longlong lVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  short sVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  int *piVar20;
  uint uVar21;
  int *piVar22;
  char *pcVar23;
  int *piVar24;
  char *pcVar25;
  uint local_d4;
  uint local_d0;
  uint local_cc;
  int local_c8;
  int local_c4;
  int local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  uint local_a8;
  uint local_a4;
  uint local_a0;
  uint local_9c;
  int *local_98;
  int *local_94;
  int *local_90;
  int local_8c;
  int local_88;
  int local_84;
  int *local_80;
  int *local_7c;
  int *local_70;
  int local_60;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int *local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  if (((param_8 == 0x10000) && (param_9 == 0x10000)) && (param_7 == 0)) {
    if ((param_10 & 1) == 0) {
      piVar24 = (int *)FUN_00404770(param_1,param_2,param_3,param_4,param_5);
      return piVar24;
    }
    local_94 = (int *)FUN_00404c5a(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    uVar6 = FUN_00408d1c(param_2,param_3);
    iVar7 = (uVar6 >> 0x10) - 1;
    iVar13 = (uVar6 & 0xffff) - 1;
    local_2c = &local_18;
    local_18 = param_6;
    local_28 = 0;
    DAT_0049a71c = 0;
    DAT_0049a758 = 0;
    local_24 = 0;
    DAT_0049a720 = 0;
    DAT_0049a734 = 0;
    DAT_0049a730 = iVar7;
    DAT_0049a744 = iVar7;
    DAT_0049a748 = iVar13;
    DAT_0049a75c = iVar13;
    local_20 = iVar7;
    local_1c = iVar13;
    local_14 = iVar7;
    local_10 = iVar13;
    iVar8 = FUN_00408d50(param_2,param_3);
    local_40 = -(int)(short)iVar8;
    local_44 = -(iVar8 >> 0x10);
    if ((param_10 & 2) == 0) {
      FUN_00406604(&local_2c,0xff);
      if ((param_10 & 1) == 0) {
        FUN_00404770(&local_2c,param_2,param_3,local_44,local_40);
      }
      else {
        FUN_00404c5a(&local_2c,param_2,param_3,local_44,local_40);
      }
    }
    piVar24 = (int *)*param_1;
    iVar8 = piVar24[1];
    iVar9 = iVar8 + 1;
    if ((iVar9 == 0 || iVar8 < -1) || (iVar2 = piVar24[2], iVar2 < 0)) {
      return (int *)0xffffffff;
    }
    iVar3 = param_1[1];
    iVar10 = iVar3;
    if (iVar3 < 1) {
      iVar10 = 0;
    }
    piVar20 = (int *)param_1[2];
    piVar11 = piVar20;
    if ((int)piVar20 < 1) {
      piVar11 = (int *)0x0;
    }
    iVar12 = param_1[3];
    if (iVar8 <= param_1[3]) {
      iVar12 = iVar8;
    }
    iVar8 = param_1[4];
    if (iVar2 <= param_1[4]) {
      iVar8 = iVar2;
    }
    if ((iVar12 < iVar10) || (iVar8 < (int)piVar11)) {
      return (int *)0xfffffffe;
    }
    local_60 = *piVar24;
    param_4 = param_4 - local_44;
    param_5 = param_5 - local_40;
    local_34 = 0;
    local_30 = 0;
    FUN_004081ad(&local_34,&local_3c,&local_44,param_7,param_8,param_9);
    DAT_0049a710 = local_3c + param_4;
    DAT_0049a714 = local_38 + param_5;
    local_30 = 0;
    local_34 = iVar7;
    FUN_004081ad(&local_34,&local_3c,&local_44,param_7,param_8,param_9);
    DAT_0049a710 = DAT_0049a710 + iVar3;
    DAT_0049a724 = local_3c + param_4 + iVar3;
    DAT_0049a714 = DAT_0049a714 + (int)piVar20;
    DAT_0049a728 = local_38 + param_5 + (int)piVar20;
    local_34 = iVar7;
    local_30 = iVar13;
    FUN_004081ad(&local_34,&local_3c,&local_44,param_7,param_8,param_9);
    DAT_0049a738 = local_3c + param_4;
    DAT_0049a73c = local_38 + param_5;
    local_34 = 0;
    local_30 = iVar13;
    FUN_004081ad(&local_34,&local_3c,&local_44,param_7,param_8,param_9);
    DAT_0049a738 = DAT_0049a738 + iVar3;
    DAT_0049a74c = local_3c + param_4 + iVar3;
    DAT_0049a73c = DAT_0049a73c + (int)piVar20;
    DAT_0049a750 = local_38 + param_5 + (int)piVar20;
    local_14 = local_14 + 1;
    piVar20 = &DAT_0049a710;
    local_90 = (int *)0x7fff;
    piVar24 = (int *)0xffff8000;
    uVar6 = 0xf;
    do {
      local_94 = (int *)piVar20[1];
      if ((int)local_94 <= (int)local_90) {
        local_90 = local_94;
        local_70 = piVar20;
      }
      if ((int)piVar24 <= (int)local_94) {
        piVar24 = local_94;
      }
      uVar6 = uVar6 & (((((uint)(*piVar20 - iVar10) >> 0x1f) << 1 |
                        (uint)(iVar12 - *piVar20) >> 0x1f) << 1 |
                       (uint)(piVar20[1] - (int)piVar11) >> 0x1f) << 1 |
                      (uint)(iVar8 - piVar20[1]) >> 0x1f);
      piVar20 = piVar20 + 5;
    } while (piVar20 != (int *)&DAT_0049a760);
    if (uVar6 == 0) {
      local_7c = local_70;
      local_80 = local_70;
      local_94 = local_70;
      piVar20 = local_7c;
      if (piVar24 != local_90) {
        do {
          local_7c = piVar20;
          piVar20 = local_7c + -5;
          if ((int)piVar20 < 0x49a710) {
            piVar20 = &DAT_0049a74c;
          }
        } while (((local_7c[1] < (int)piVar11) && (piVar20[1] <= (int)piVar11)) ||
                (local_84 = piVar20[1] - local_7c[1], local_84 == 0));
        local_ac = (int)((longlong)
                         ((ulonglong)(uint)((*piVar20 - *local_7c) * 0x10000 >> 0x10) << 0x20) /
                        (longlong)(local_84 * 0x10000));
        local_b4 = (int)((longlong)
                         ((ulonglong)(uint)((piVar20[3] - local_7c[3]) * 0x10000 >> 0x10) << 0x20) /
                        (longlong)(local_84 * 0x10000));
        local_bc = (int)((longlong)
                         ((ulonglong)(uint)((piVar20[4] - local_7c[4]) * 0x10000 >> 0x10) << 0x20) /
                        (longlong)(local_84 * 0x10000));
        local_94 = (int *)(*local_7c * 0x10000 + 0x8000);
        local_9c = local_7c[3] * 0x10000 + 0x8000;
        local_a4 = local_7c[4] * 0x10000 + 0x8000;
        piVar22 = local_80;
        do {
          local_80 = piVar22;
          piVar22 = local_80 + 5;
          if (0x49a75f < (int)piVar22) {
            piVar22 = &DAT_0049a710;
          }
        } while (((local_80[1] < (int)piVar11) && (piVar22[1] <= (int)piVar11)) ||
                (local_88 = piVar22[1] - local_80[1], local_88 == 0));
        local_b0 = (int)((longlong)
                         ((ulonglong)(uint)((*piVar22 - *local_80) * 0x10000 >> 0x10) << 0x20) /
                        (longlong)(local_88 * 0x10000));
        local_b8 = (int)((longlong)
                         ((ulonglong)(uint)((piVar22[3] - local_80[3]) * 0x10000 >> 0x10) << 0x20) /
                        (longlong)(local_88 * 0x10000));
        local_c0 = (int)((longlong)
                         ((ulonglong)(uint)((piVar22[4] - local_80[4]) * 0x10000 >> 0x10) << 0x20) /
                        (longlong)(local_88 * 0x10000));
        local_98 = (int *)(*local_80 * 0x10000 + 0x8000);
        local_a0 = local_80[3] * 0x10000 + 0x8000;
        local_a8 = local_80[4] * 0x10000 + 0x8000;
        local_8c = iVar8 - (int)local_90;
        if ((int)piVar24 - iVar8 == 0 || (int)piVar24 < iVar8) {
          local_8c = local_8c + ((int)piVar24 - iVar8);
        }
        if ((int)piVar11 - (int)local_90 != 0 && (int)local_90 <= (int)piVar11) {
          local_8c = local_8c - ((int)piVar11 - (int)local_90);
          local_84 = local_84 - ((int)piVar11 - local_7c[1]);
          iVar7 = ((int)piVar11 - local_7c[1]) * 0x10000;
          local_94 = (int *)((int)local_94 +
                            ((uint)((longlong)local_ac * (longlong)iVar7) >> 0x10 |
                            (int)((ulonglong)((longlong)local_ac * (longlong)iVar7) >> 0x20) << 0x10
                            ));
          local_9c = local_9c +
                     ((uint)((longlong)local_b4 * (longlong)iVar7) >> 0x10 |
                     (int)((ulonglong)((longlong)local_b4 * (longlong)iVar7) >> 0x20) << 0x10);
          local_a4 = local_a4 +
                     ((uint)((longlong)local_bc * (longlong)iVar7) >> 0x10 |
                     (int)((ulonglong)((longlong)local_bc * (longlong)iVar7) >> 0x20) << 0x10);
          local_88 = local_88 - ((int)piVar11 - local_80[1]);
          iVar7 = ((int)piVar11 - local_80[1]) * 0x10000;
          local_98 = (int *)((int)local_98 +
                            ((uint)((longlong)local_b0 * (longlong)iVar7) >> 0x10 |
                            (int)((ulonglong)((longlong)local_b0 * (longlong)iVar7) >> 0x20) << 0x10
                            ));
          local_a0 = local_a0 +
                     ((uint)((longlong)local_b8 * (longlong)iVar7) >> 0x10 |
                     (int)((ulonglong)((longlong)local_b8 * (longlong)iVar7) >> 0x20) << 0x10);
          local_a8 = local_a8 +
                     ((uint)((longlong)local_c0 * (longlong)iVar7) >> 0x10 |
                     (int)((ulonglong)((longlong)local_c0 * (longlong)iVar7) >> 0x20) << 0x10);
          local_90 = piVar11;
        }
        local_60 = (int)local_90 * iVar9 + local_60;
        local_80 = piVar22;
        local_7c = piVar20;
LAB_004058d8:
        piVar24 = local_94;
        local_d4 = local_9c;
        uVar16 = local_a0;
        piVar20 = local_98;
        uVar6 = local_a4;
        uVar21 = local_a8;
        if ((int)local_98 <= (int)local_94) {
          piVar24 = local_98;
          local_d4 = local_a0;
          uVar16 = local_9c;
          piVar20 = local_94;
          uVar6 = local_a8;
          uVar21 = local_a4;
        }
        local_c4 = (int)piVar24 >> 0x10;
        if ((local_c4 <= iVar12) && (local_c8 = (int)piVar20 >> 0x10, iVar10 <= local_c8)) {
          iVar7 = local_c8 - local_c4;
          if (iVar7 != 0) {
            uVar4 = CONCAT44((int)(uVar16 - local_d4) >> 0x10,(uVar16 - local_d4) * 0x10000) /
                    (longlong)(iVar7 * 0x10000);
            local_cc = (uint)uVar4;
            uVar16 = local_cc >> 0x10;
            iVar8 = 1;
            if ((uVar16 & 0x8000) != 0) {
              iVar8 = -1;
              uVar16 = ((uVar16 | 0xffff0000) + 1) - (uint)((uVar4 & 0xffff) == 0);
            }
            uVar4 = CONCAT44((int)(uVar21 - uVar6) >> 0x10,(uVar21 - uVar6) * 0x10000) /
                    (longlong)(iVar7 * 0x10000);
            local_d0 = (uint)uVar4;
            sVar15 = (short)(uVar4 >> 0x10);
            _DAT_0049a76c = local_14;
            if ((local_d0 >> 0x10 & 0x8000) != 0) {
              _DAT_0049a76c = -local_14;
              sVar15 = (sVar15 + 1) - (ushort)((uVar4 & 0xffff) == 0);
            }
            _DAT_0049a768 = (int)(short)((short)local_14 * sVar15);
            _DAT_0049a760 = uVar16 + _DAT_0049a768;
            _DAT_0049a764 = _DAT_0049a760 + _DAT_0049a76c;
            _DAT_0049a768 = iVar8 + uVar16 + _DAT_0049a768;
            _DAT_0049a76c = _DAT_0049a768 + _DAT_0049a76c;
            iVar7 = iVar10 - local_c4;
            if (iVar7 != 0 && local_c4 <= iVar10) {
              local_c4 = local_c4 + iVar7;
              lVar5 = (longlong)(int)local_cc * (longlong)(iVar7 * 0x10000);
              local_d4 = local_d4 + ((uint)lVar5 >> 0x10 | (int)((ulonglong)lVar5 >> 0x20) << 0x10);
              lVar5 = (longlong)(int)local_d0 * (longlong)(iVar7 * 0x10000);
              uVar6 = uVar6 + ((uint)lVar5 >> 0x10 | (int)((ulonglong)lVar5 >> 0x20) << 0x10);
            }
            if (local_c8 - iVar12 != 0 && iVar12 <= local_c8) {
              local_c8 = local_c8 - (local_c8 - iVar12);
            }
          }
          pcVar23 = (char *)((local_d4 >> 0x10) + (uVar6 >> 0x10) * local_14 + local_18);
          pcVar25 = (char *)(local_60 + local_c4);
          local_c8 = local_c8 - local_c4;
          uVar16 = local_cc;
          if ((int)local_cc < 0) {
            uVar16 = -local_cc;
            local_d4 = ~local_d4;
          }
          uVar16 = uVar16 * 0x10000;
          local_d4 = local_d4 << 0x10;
          uVar21 = local_d0;
          if ((int)local_d0 < 0) {
            uVar21 = -local_d0;
            uVar6 = ~uVar6;
          }
          uVar21 = uVar21 * 0x10000;
          uVar6 = uVar6 << 0x10;
          do {
            if (local_c8 < 5) {
              if (*pcVar23 != -1) {
                *pcVar25 = *pcVar23;
              }
              pcVar23 = pcVar23 + *(int *)(&DAT_0049a760 +
                                          ((uint)CARRY4(local_d4,uVar16) * 2 +
                                          (uint)CARRY4(uVar6,uVar21)) * 4);
              if (-1 < local_c8 + -1) {
                if (*pcVar23 != -1) {
                  pcVar25[1] = *pcVar23;
                }
                uVar17 = local_d4 + uVar16 + uVar16;
                uVar14 = uVar6 + uVar21 + uVar21;
                pcVar23 = pcVar23 + *(int *)(&DAT_0049a760 +
                                            ((uint)CARRY4(local_d4 + uVar16,uVar16) * 2 +
                                            (uint)CARRY4(uVar6 + uVar21,uVar21)) * 4);
                if (-1 < local_c8 + -2) {
                  if (*pcVar23 != -1) {
                    pcVar25[2] = *pcVar23;
                  }
                  iVar7 = *(int *)(&DAT_0049a760 +
                                  ((uint)CARRY4(uVar17,uVar16) * 2 + (uint)CARRY4(uVar14,uVar21)) *
                                  4);
                  if (-1 < local_c8 + -3) {
                    cVar1 = pcVar23[iVar7];
                    if (cVar1 != -1) {
                      pcVar25[3] = cVar1;
                    }
                    if ((-1 < local_c8 + -4) &&
                       (cVar1 = (pcVar23 + iVar7)
                                [*(int *)(&DAT_0049a760 +
                                         ((uint)CARRY4(uVar17 + uVar16,uVar16) * 2 +
                                         (uint)CARRY4(uVar14 + uVar21,uVar21)) * 4)], cVar1 != -1))
                    {
                      pcVar25[4] = cVar1;
                    }
                  }
                }
              }
              break;
            }
            if (*pcVar23 != -1) {
              *pcVar25 = *pcVar23;
            }
            pcVar23 = pcVar23 + *(int *)(&DAT_0049a760 +
                                        ((uint)CARRY4(local_d4,uVar16) * 2 +
                                        (uint)CARRY4(uVar6,uVar21)) * 4);
            if (*pcVar23 != -1) {
              pcVar25[1] = *pcVar23;
            }
            uVar17 = local_d4 + uVar16 + uVar16;
            uVar14 = uVar6 + uVar21 + uVar21;
            pcVar23 = pcVar23 + *(int *)(&DAT_0049a760 +
                                        ((uint)CARRY4(local_d4 + uVar16,uVar16) * 2 +
                                        (uint)CARRY4(uVar6 + uVar21,uVar21)) * 4);
            if (*pcVar23 != -1) {
              pcVar25[2] = *pcVar23;
            }
            uVar18 = uVar17 + uVar16;
            uVar6 = uVar14 + uVar21;
            pcVar23 = pcVar23 + *(int *)(&DAT_0049a760 +
                                        ((uint)CARRY4(uVar17,uVar16) * 2 +
                                        (uint)CARRY4(uVar14,uVar21)) * 4);
            if (*pcVar23 != -1) {
              pcVar25[3] = *pcVar23;
            }
            uVar17 = uVar18 + uVar16;
            uVar14 = uVar6 + uVar21;
            pcVar23 = pcVar23 + *(int *)(&DAT_0049a760 +
                                        ((uint)CARRY4(uVar18,uVar16) * 2 +
                                        (uint)CARRY4(uVar6,uVar21)) * 4);
            if (*pcVar23 != -1) {
              pcVar25[4] = *pcVar23;
            }
            uVar19 = uVar17 + uVar16;
            uVar18 = uVar14 + uVar21;
            iVar7 = *(int *)(&DAT_0049a760 +
                            ((uint)CARRY4(uVar17,uVar16) * 2 + (uint)CARRY4(uVar14,uVar21)) * 4);
            cVar1 = pcVar23[iVar7];
            if (cVar1 != -1) {
              pcVar25[5] = cVar1;
            }
            local_d4 = uVar19 + uVar16;
            uVar6 = uVar18 + uVar21;
            pcVar23 = pcVar23 + iVar7 +
                      *(int *)(&DAT_0049a760 +
                              ((uint)CARRY4(uVar19,uVar16) * 2 + (uint)CARRY4(uVar18,uVar21)) * 4);
            pcVar25 = pcVar25 + 6;
            local_c8 = local_c8 + -6;
          } while (-1 < local_c8);
        }
        local_60 = local_60 + iVar9;
        local_8c = local_8c + -1;
        if (-1 < local_8c) {
          if (local_8c == 0) {
            local_94 = (int *)((int)local_94 + local_ac);
            local_9c = local_9c + local_b4;
            local_a4 = local_a4 + local_bc;
            local_98 = (int *)((int)local_98 + local_b0);
            local_a0 = local_a0 + local_b8;
            local_a8 = local_a8 + local_c0;
          }
          else {
            local_84 = local_84 + -1;
            if (local_84 == 0) {
              piVar24 = local_7c + -5;
              if ((int)piVar24 < 0x49a710) {
                piVar24 = &DAT_0049a74c;
              }
              local_84 = (piVar24[1] - local_7c[1]) + (uint)(piVar24[1] - local_7c[1] == 0);
              local_ac = (int)((longlong)
                               ((ulonglong)(uint)((*piVar24 - *local_7c) * 0x10000 >> 0x10) << 0x20)
                              / (longlong)(local_84 * 0x10000));
              local_b4 = (int)((longlong)
                               ((ulonglong)(uint)((piVar24[3] - local_7c[3]) * 0x10000 >> 0x10) <<
                               0x20) / (longlong)(local_84 * 0x10000));
              local_bc = (int)((longlong)
                               ((ulonglong)(uint)((piVar24[4] - local_7c[4]) * 0x10000 >> 0x10) <<
                               0x20) / (longlong)(local_84 * 0x10000));
              local_94 = (int *)(*local_7c * 0x10000 + 0x8000);
              local_9c = local_7c[3] * 0x10000 + 0x8000;
              local_a4 = local_7c[4] * 0x10000 + 0x8000;
              local_7c = piVar24;
            }
            else {
              local_94 = (int *)((int)local_94 + local_ac);
              local_9c = local_9c + local_b4;
              local_a4 = local_a4 + local_bc;
            }
            local_88 = local_88 + -1;
            if (local_88 == 0) {
              piVar24 = local_80 + 5;
              if (0x49a75f < (int)piVar24) {
                piVar24 = &DAT_0049a710;
              }
              local_88 = (piVar24[1] - local_80[1]) + (uint)(piVar24[1] - local_80[1] == 0);
              local_b0 = (int)((longlong)
                               ((ulonglong)(uint)((*piVar24 - *local_80) * 0x10000 >> 0x10) << 0x20)
                              / (longlong)(local_88 * 0x10000));
              local_b8 = (int)((longlong)
                               ((ulonglong)(uint)((piVar24[3] - local_80[3]) * 0x10000 >> 0x10) <<
                               0x20) / (longlong)(local_88 * 0x10000));
              local_c0 = (int)((longlong)
                               ((ulonglong)(uint)((piVar24[4] - local_80[4]) * 0x10000 >> 0x10) <<
                               0x20) / (longlong)(local_88 * 0x10000));
              local_a0 = local_80[3] * 0x10000 + 0x8000;
              local_a8 = local_80[4] * 0x10000 + 0x8000;
              local_98 = (int *)(*local_80 * 0x10000 + 0x8000);
              local_80 = piVar24;
            }
            else {
              local_98 = (int *)((int)local_98 + local_b0);
              local_a0 = local_a0 + local_b8;
              local_a8 = local_a8 + local_c0;
            }
          }
          goto LAB_004058d8;
        }
      }
    }
  }
  return local_94;
}
```

---

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


# 0005_batch_0001 — détails (2/3)

## FUN_00403c35 — 0x403c35

- Classification : internal (Ghidra FunctionManager)
- Corps : `0x403c35–0x404636`
- État : pseudocode obtenu
- Evidence : `ev_21a8b4b52dde0d44999b7642a6ce8ae0c385409814ef8969a28bfc030fc283ff`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs observés

- aucun relevé

### Chaînes référencées observées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00403c35(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7)

{
  int *piVar1;
  ulonglong uVar2;
  longlong lVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  byte *pbVar15;
  int iVar16;
  byte bVar17;
  byte bVar21;
  uint uVar18;
  uint uVar19;
  undefined4 uVar20;
  uint uVar22;
  undefined1 *puVar23;
  undefined1 *puVar24;
  undefined1 *puVar25;
  undefined1 *puVar26;
  undefined1 *puVar27;
  int iVar28;
  bool bVar29;
  undefined1 auStack_6c [4];
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  
  puVar23 = &stack0xfffffffc;
  puVar24 = &stack0xfffffffc;
  puVar25 = &stack0xfffffffc;
  puVar27 = &stack0xfffffffc;
  puVar26 = &stack0xfffffffc;
  piVar1 = (int *)*param_1;
  iVar28 = piVar1[1];
  uVar5 = iVar28 + 1;
  if ((uVar5 == 0 || iVar28 < -1) || (iVar16 = piVar1[2], iVar16 < 0)) {
    return 0xffffffff;
  }
  local_30 = param_1[1];
  iVar6 = local_30;
  if (local_30 < 1) {
    iVar6 = 0;
  }
  local_34 = param_1[2];
  iVar7 = local_34;
  if (local_34 < 1) {
    iVar7 = 0;
  }
  iVar8 = param_1[3];
  if (iVar28 <= param_1[3]) {
    iVar8 = iVar28;
  }
  iVar28 = param_1[4];
  if (iVar16 <= param_1[4]) {
    iVar28 = iVar16;
  }
  if ((iVar8 < iVar6) || (iVar28 < iVar7)) {
    return 0xfffffffe;
  }
  param_2 = param_2 + local_30;
  local_30 = param_4 + local_30;
  param_3 = param_3 + local_34;
  local_34 = param_5 + local_34;
  uVar9 = local_30 - param_2;
  uVar18 = (int)uVar9 >> 0x1f;
  uVar10 = (uVar9 ^ uVar18) - uVar18;
  uVar11 = local_34 - param_3;
  uVar19 = (int)uVar11 >> 0x1f;
  uVar12 = (uVar11 ^ uVar19) - uVar19;
  bVar4 = (byte)param_7;
  local_28 = param_2;
  if (uVar9 == 0) {
    if ((param_2 < iVar6) || (iVar8 < param_2)) {
      return 2;
    }
    iVar16 = param_3;
    if (param_3 <= local_34) {
      iVar16 = local_34;
    }
    if (iVar16 < iVar7) {
      return 2;
    }
    iVar16 = param_3;
    if (local_34 <= param_3) {
      iVar16 = local_34;
    }
    if (iVar28 < iVar16) {
      return 2;
    }
    if (param_3 <= iVar7) {
      param_3 = iVar7;
    }
    local_2c = param_3;
    if (iVar28 <= param_3) {
      local_2c = iVar28;
    }
    if (local_34 <= iVar7) {
      local_34 = iVar7;
    }
    if (iVar28 <= local_34) {
      local_34 = iVar28;
    }
    uVar12 = (uVar5 ^ uVar19) - uVar19;
    uVar10 = local_34 - local_2c >> 0x1f;
    iVar28 = ((local_34 - local_2c ^ uVar10) - uVar10) + 1;
  }
  else {
    local_2c = param_3;
    if (uVar11 == 0) {
      if (param_3 < iVar7) {
        return 2;
      }
      if (iVar28 < param_3) {
        return 2;
      }
      iVar28 = param_2;
      if (param_2 <= local_30) {
        iVar28 = local_30;
      }
      if (iVar28 < iVar6) {
        return 2;
      }
      iVar28 = param_2;
      if (local_30 <= param_2) {
        iVar28 = local_30;
      }
      if (iVar8 < iVar28) {
        return 2;
      }
      if (param_2 <= iVar6) {
        param_2 = iVar6;
      }
      if (iVar8 <= param_2) {
        param_2 = iVar8;
      }
      if (local_30 <= iVar6) {
        local_30 = iVar6;
      }
      if (iVar8 <= local_30) {
        local_30 = iVar8;
      }
      uVar12 = uVar18 + 1 | uVar18;
      uVar10 = local_30 - param_2 >> 0x1f;
      iVar28 = ((local_30 - param_2 ^ uVar10) - uVar10) + 1;
      local_28 = param_2;
    }
    else {
      uVar13 = (int)(uVar9 ^ uVar11) >> 0x1f;
      uVar14 = 0xffffffff;
      if (uVar10 != uVar12) {
        uVar14 = uVar10;
        uVar22 = uVar12;
        if ((int)uVar12 <= (int)uVar10) {
          uVar14 = uVar12;
          uVar22 = uVar10;
        }
        uVar14 = (uint)(((ulonglong)uVar14 << 0x20) / (ulonglong)uVar22);
      }
      while( true ) {
        bVar17 = (((local_28 - iVar6 < 0) * '\x02' + (iVar8 - local_28 < 0)) * '\x02' +
                 (local_2c - iVar7 < 0)) * '\x02' + (iVar28 - local_2c < 0);
        bVar21 = (((local_30 - iVar6 < 0) * '\x02' + (iVar8 - local_30 < 0)) * '\x02' +
                 (local_34 - iVar7 < 0)) * '\x02' + (iVar28 - local_34 < 0);
        if (CONCAT11(bVar21,bVar17) == 0) break;
        if ((bVar21 & bVar17) != 0) {
          return 2;
        }
        if ((int)uVar10 < (int)uVar12) {
          if ((bVar17 & 8) == 0) {
            if ((bVar17 & 4) == 0) {
              if ((bVar17 & 2) == 0) {
                if ((bVar17 & 1) == 0) {
                  if ((bVar21 & 8) == 0) {
                    if ((bVar21 & 4) == 0) {
                      if ((bVar21 & 2) == 0) {
                        if ((bVar21 & 1) != 0) {
                          lVar3 = (ulonglong)(uint)(iVar28 - param_3) * (ulonglong)uVar14;
                          local_34 = iVar28;
                          local_30 = (((int)((ulonglong)lVar3 >> 0x20) +
                                       (uint)(0x7fffffff < (uint)lVar3) ^ uVar13) - uVar13) +
                                     param_2;
                        }
                      }
                      else {
                        lVar3 = (ulonglong)(uint)-(iVar7 - param_3) * (ulonglong)uVar14;
                        local_34 = iVar7;
                        local_30 = (((int)((ulonglong)lVar3 >> 0x20) +
                                     (uint)(0x7fffffff < (uint)lVar3) ^ ~uVar13) - ~uVar13) +
                                   param_2;
                      }
                    }
                    else {
                      uVar2 = (ulonglong)(uint)(iVar8 - param_2) << 0x20 | 0x80000000;
                      local_34 = (((int)(uVar2 / uVar14) -
                                   (uint)((int)(uVar2 % (ulonglong)uVar14) == 0) ^ uVar13) - uVar13)
                                 + param_3;
                      local_30 = iVar8;
                    }
                  }
                  else {
                    uVar2 = (ulonglong)(uint)-(iVar6 - param_2) << 0x20 | 0x80000000;
                    local_34 = (((int)(uVar2 / uVar14) -
                                 (uint)((int)(uVar2 % (ulonglong)uVar14) == 0) ^ ~uVar13) - ~uVar13)
                               + param_3;
                    local_30 = iVar6;
                  }
                }
                else {
                  lVar3 = (ulonglong)(uint)-(iVar28 - param_3) * (ulonglong)uVar14;
                  local_2c = iVar28;
                  local_28 = (((int)((ulonglong)lVar3 >> 0x20) + (uint)(0x7fffffff < (uint)lVar3) ^
                              ~uVar13) - ~uVar13) + param_2;
                }
              }
              else {
                lVar3 = (ulonglong)(uint)(iVar7 - param_3) * (ulonglong)uVar14;
                local_2c = iVar7;
                local_28 = (((int)((ulonglong)lVar3 >> 0x20) + (uint)(0x7fffffff < (uint)lVar3) ^
                            uVar13) - uVar13) + param_2;
              }
            }
            else {
              uVar2 = (ulonglong)(0xffffffff - (iVar8 - param_2)) << 0x20 | 0x80000000;
              local_2c = ((((int)(uVar2 / uVar14) + 1) -
                           (uint)((int)(uVar2 % (ulonglong)uVar14) == 0) ^ ~uVar13) - ~uVar13) +
                         param_3;
              local_28 = iVar8;
            }
          }
          else {
            uVar2 = (ulonglong)((iVar6 - param_2) - 1) << 0x20 | 0x80000000;
            local_2c = ((((int)(uVar2 / uVar14) + 1) - (uint)((int)(uVar2 % (ulonglong)uVar14) == 0)
                        ^ uVar13) - uVar13) + param_3;
            local_28 = iVar6;
          }
        }
        else if ((bVar17 & 8) == 0) {
          if ((bVar17 & 4) == 0) {
            if ((bVar17 & 2) == 0) {
              if ((bVar17 & 1) == 0) {
                if ((bVar21 & 8) == 0) {
                  if ((bVar21 & 4) == 0) {
                    if ((bVar21 & 2) == 0) {
                      if ((bVar21 & 1) != 0) {
                        uVar2 = (ulonglong)(uint)(iVar28 - param_3) << 0x20 | 0x80000000;
                        local_34 = iVar28;
                        local_30 = (((int)(uVar2 / uVar14) -
                                     (uint)((int)(uVar2 % (ulonglong)uVar14) == 0) ^ uVar13) -
                                   uVar13) + param_2;
                      }
                    }
                    else {
                      uVar2 = (ulonglong)(uint)-(iVar7 - param_3) << 0x20 | 0x80000000;
                      local_34 = iVar7;
                      local_30 = (((int)(uVar2 / uVar14) -
                                   (uint)((int)(uVar2 % (ulonglong)uVar14) == 0) ^ ~uVar13) -
                                 ~uVar13) + param_2;
                    }
                  }
                  else {
                    lVar3 = (ulonglong)(uint)(iVar8 - param_2) * (ulonglong)uVar14;
                    local_34 = (((int)((ulonglong)lVar3 >> 0x20) + (uint)(0x7fffffff < (uint)lVar3)
                                ^ uVar13) - uVar13) + param_3;
                    local_30 = iVar8;
                  }
                }
                else {
                  lVar3 = (ulonglong)(uint)-(iVar6 - param_2) * (ulonglong)uVar14;
                  local_34 = (((int)((ulonglong)lVar3 >> 0x20) + (uint)(0x7fffffff < (uint)lVar3) ^
                              ~uVar13) - ~uVar13) + param_3;
                  local_30 = iVar6;
                }
              }
              else {
                uVar2 = (ulonglong)(0xffffffff - (iVar28 - param_3)) << 0x20 | 0x80000000;
                local_2c = iVar28;
                local_28 = ((((int)(uVar2 / uVar14) + 1) -
                             (uint)((int)(uVar2 % (ulonglong)uVar14) == 0) ^ ~uVar13) - ~uVar13) +
                           param_2;
              }
            }
            else {
              uVar2 = (ulonglong)((iVar7 - param_3) - 1) << 0x20 | 0x80000000;
              local_2c = iVar7;
              local_28 = ((((int)(uVar2 / uVar14) + 1) -
                           (uint)((int)(uVar2 % (ulonglong)uVar14) == 0) ^ uVar13) - uVar13) +
                         param_2;
            }
          }
          else {
            lVar3 = (ulonglong)(uint)-(iVar8 - param_2) * (ulonglong)uVar14;
            local_2c = (((int)((ulonglong)lVar3 >> 0x20) + (uint)(0x7fffffff < (uint)lVar3) ^
                        ~uVar13) - ~uVar13) + param_3;
            local_28 = iVar8;
          }
        }
        else {
          lVar3 = (ulonglong)(uint)(iVar6 - param_2) * (ulonglong)uVar14;
          local_2c = (((int)((ulonglong)lVar3 >> 0x20) + (uint)(0x7fffffff < (uint)lVar3) ^ uVar13)
                     - uVar13) + param_3;
          local_28 = iVar6;
        }
      }
      pbVar15 = (byte *)(local_2c * uVar5 + *piVar1 + local_28);
      iVar28 = (uVar5 ^ uVar19) - uVar19;
      if (uVar10 != uVar12) {
        if ((int)uVar10 < (int)uVar12) {
          uVar5 = local_34 - local_2c >> 0x1f;
          iVar16 = ((local_34 - local_2c ^ uVar5) - uVar5) + 1;
          uVar5 = local_2c - param_3 >> 0x1f;
          uVar5 = ((local_2c - param_3 ^ uVar5) - uVar5) * uVar14 + 0x80000000;
          if ((int)uVar9 < 0) {
            if (param_6 == 1) {
              do {
                *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
                pbVar15 = pbVar15 + (iVar28 - (uint)CARRY4(uVar5,uVar14));
                puVar27 = &stack0xfffffffc;
                if (iVar16 == 1) break;
                *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
                uVar9 = uVar5 + uVar14 + uVar14;
                pbVar15 = pbVar15 + (iVar28 - (uint)CARRY4(uVar5 + uVar14,uVar14));
                puVar27 = &stack0xfffffffc;
                if (iVar16 == 2) break;
                *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
                uVar10 = uVar9 + uVar14;
                pbVar15 = pbVar15 + (iVar28 - (uint)CARRY4(uVar9,uVar14));
                puVar27 = &stack0xfffffffc;
                if (iVar16 == 3) break;
                *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
                uVar5 = uVar10 + uVar14;
                pbVar15 = pbVar15 + (iVar28 - (uint)CARRY4(uVar10,uVar14));
                iVar16 = iVar16 + -4;
                puVar27 = &stack0xfffffffc;
              } while (iVar16 != 0);
            }
            else if (param_6 < 2) {
              do {
                *pbVar15 = bVar4;
                pbVar15 = pbVar15 + (iVar28 - (uint)CARRY4(uVar5,uVar14));
                puVar27 = &stack0xfffffffc;
                if (iVar16 == 1) break;
                *pbVar15 = bVar4;
                uVar9 = uVar5 + uVar14 + uVar14;
                pbVar15 = pbVar15 + (iVar28 - (uint)CARRY4(uVar5 + uVar14,uVar14));
                puVar27 = &stack0xfffffffc;
                if (iVar16 == 2) break;
                *pbVar15 = bVar4;
                uVar10 = uVar9 + uVar14;
                puVar27 = &stack0xfffffffc;
                if (iVar16 == 3) break;
                pbVar15[iVar28 - (uint)CARRY4(uVar9,uVar14)] = bVar4;
                uVar5 = uVar10 + uVar14;
                pbVar15 = pbVar15 + (iVar28 - (uint)CARRY4(uVar9,uVar14)) +
                          (iVar28 - (uint)CARRY4(uVar10,uVar14));
                iVar16 = iVar16 + -4;
                puVar27 = &stack0xfffffffc;
              } while (iVar16 != 0);
            }
            else {
              local_28 = local_28 - param_1[1];
              local_2c = local_2c - param_1[2];
              do {
                (**(code **)(puVar24 + 0x20))(local_28,local_2c,puVar24,auStack_6c);
                bVar29 = CARRY4(uVar5,uVar14);
                uVar5 = uVar5 + uVar14;
                if (bVar29) {
                  local_28 = local_28 + -1;
                }
                local_2c = local_2c + uVar19 * 2 + 1;
                iVar16 = iVar16 + -1;
                puVar27 = puVar24;
              } while (iVar16 != 0);
            }
          }
          else if (param_6 == 1) {
            do {
              *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
              pbVar15 = pbVar15 + (uint)CARRY4(uVar5,uVar14) + iVar28;
              puVar27 = &stack0xfffffffc;
              if (iVar16 == 1) break;
              *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
              uVar9 = uVar5 + uVar14 + uVar14;
              pbVar15 = pbVar15 + (uint)CARRY4(uVar5 + uVar14,uVar14) + iVar28;
              puVar27 = &stack0xfffffffc;
              if (iVar16 == 2) break;
              *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
              uVar10 = uVar9 + uVar14;
              pbVar15 = pbVar15 + (uint)CARRY4(uVar9,uVar14) + iVar28;
              puVar27 = &stack0xfffffffc;
              if (iVar16 == 3) break;
              *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
              uVar5 = uVar10 + uVar14;
              pbVar15 = pbVar15 + (uint)CARRY4(uVar10,uVar14) + iVar28;
              iVar16 = iVar16 + -4;
              puVar27 = &stack0xfffffffc;
            } while (iVar16 != 0);
          }
          else if (param_6 < 2) {
            do {
              *pbVar15 = bVar4;
              pbVar15 = pbVar15 + (uint)CARRY4(uVar5,uVar14) + iVar28;
              puVar27 = &stack0xfffffffc;
              if (iVar16 == 1) break;
              *pbVar15 = bVar4;
              uVar9 = uVar5 + uVar14 + uVar14;
              pbVar15 = pbVar15 + (uint)CARRY4(uVar5 + uVar14,uVar14) + iVar28;
              puVar27 = &stack0xfffffffc;
              if (iVar16 == 2) break;
              *pbVar15 = bVar4;
              uVar10 = uVar9 + uVar14;
              puVar27 = &stack0xfffffffc;
              if (iVar16 == 3) break;
              pbVar15[(uint)CARRY4(uVar9,uVar14) + iVar28] = bVar4;
              uVar5 = uVar10 + uVar14;
              pbVar15 = pbVar15 + (uint)CARRY4(uVar9,uVar14) + iVar28 +
                        (uint)CARRY4(uVar10,uVar14) + iVar28;
              iVar16 = iVar16 + -4;
              puVar27 = &stack0xfffffffc;
            } while (iVar16 != 0);
          }
          else {
            local_28 = local_28 - param_1[1];
            local_2c = local_2c - param_1[2];
            do {
              (**(code **)(puVar23 + 0x20))(local_28,local_2c,puVar23,auStack_6c);
              bVar29 = CARRY4(uVar5,uVar14);
              uVar5 = uVar5 + uVar14;
              if (bVar29) {
                local_28 = local_28 + 1;
              }
              local_2c = local_2c + uVar19 * 2 + 1;
              iVar16 = iVar16 + -1;
              puVar27 = puVar23;
            } while (iVar16 != 0);
          }
        }
        else {
          uVar5 = local_30 - local_28 >> 0x1f;
          iVar16 = ((local_30 - local_28 ^ uVar5) - uVar5) + 1;
          uVar5 = local_28 - param_2 >> 0x1f;
          uVar5 = ((local_28 - param_2 ^ uVar5) - uVar5) * uVar14 + 0x80000000;
          if ((int)uVar9 < 0) {
            if (param_6 == 1) {
              do {
                *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
                pbVar15 = pbVar15 + -1;
                if (CARRY4(uVar5,uVar14)) {
                  pbVar15 = pbVar15 + iVar28;
                }
                puVar27 = &stack0xfffffffc;
                if (iVar16 == 1) break;
                *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
                pbVar15 = pbVar15 + -1;
                uVar9 = uVar5 + uVar14 + uVar14;
                if (CARRY4(uVar5 + uVar14,uVar14)) {
                  pbVar15 = pbVar15 + iVar28;
                }
                puVar27 = &stack0xfffffffc;
                if (iVar16 == 2) break;
                *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
                pbVar15 = pbVar15 + -1;
                uVar10 = uVar9 + uVar14;
                if (CARRY4(uVar9,uVar14)) {
                  pbVar15 = pbVar15 + iVar28;
                }
                puVar27 = &stack0xfffffffc;
                if (iVar16 == 3) break;
                *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
                pbVar15 = pbVar15 + -1;
                uVar5 = uVar10 + uVar14;
                if (CARRY4(uVar10,uVar14)) {
                  pbVar15 = pbVar15 + iVar28;
                }
                iVar16 = iVar16 + -4;
                puVar27 = &stack0xfffffffc;
              } while (iVar16 != 0);
            }
            else if (param_6 < 2) {
              do {
                *pbVar15 = bVar4;
                pbVar15 = pbVar15 + -1;
                if (CARRY4(uVar5,uVar14)) {
                  pbVar15 = pbVar15 + iVar28;
                }
                puVar27 = &stack0xfffffffc;
                if (iVar16 == 1) break;
                *pbVar15 = bVar4;
                pbVar15 = pbVar15 + -1;
                uVar9 = uVar5 + uVar14 + uVar14;
                if (CARRY4(uVar5 + uVar14,uVar14)) {
                  pbVar15 = pbVar15 + iVar28;
                }
                puVar27 = &stack0xfffffffc;
                if (iVar16 == 2) break;
                *pbVar15 = bVar4;
                pbVar15 = pbVar15 + -1;
                uVar10 = uVar9 + uVar14;
                if (CARRY4(uVar9,uVar14)) {
                  pbVar15 = pbVar15 + iVar28;
                }
                puVar27 = &stack0xfffffffc;
                if (iVar16 == 3) break;
                *pbVar15 = bVar4;
                pbVar15 = pbVar15 + -1;
                uVar5 = uVar10 + uVar14;
                if (CARRY4(uVar10,uVar14)) {
                  pbVar15 = pbVar15 + iVar28;
                }
                iVar16 = iVar16 + -4;
                puVar27 = &stack0xfffffffc;
              } while (iVar16 != 0);
            }
            else {
              local_28 = local_28 - param_1[1];
              local_2c = local_2c - param_1[2];
              do {
                (**(code **)(puVar27 + 0x20))(local_28,local_2c,puVar27,auStack_6c);
                bVar29 = CARRY4(uVar5,uVar14);
                uVar5 = uVar5 + uVar14;
                if (bVar29) {
                  local_2c = local_2c + -1;
                }
                local_28 = local_28 + uVar19 * 2 + 1;
                iVar16 = iVar16 + -1;
              } while (iVar16 != 0);
            }
          }
          else if (param_6 == 1) {
            do {
              *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
              pbVar15 = pbVar15 + 1;
              if (CARRY4(uVar5,uVar14)) {
                pbVar15 = pbVar15 + iVar28;
              }
              puVar27 = &stack0xfffffffc;
              if (iVar16 == 1) break;
              *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
              pbVar15 = pbVar15 + 1;
              uVar9 = uVar5 + uVar14 + uVar14;
              if (CARRY4(uVar5 + uVar14,uVar14)) {
                pbVar15 = pbVar15 + iVar28;
              }
              puVar27 = &stack0xfffffffc;
              if (iVar16 == 2) break;
              *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
              pbVar15 = pbVar15 + 1;
              uVar10 = uVar9 + uVar14;
              if (CARRY4(uVar9,uVar14)) {
                pbVar15 = pbVar15 + iVar28;
              }
              puVar27 = &stack0xfffffffc;
              if (iVar16 == 3) break;
              *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
              pbVar15 = pbVar15 + 1;
              uVar5 = uVar10 + uVar14;
              if (CARRY4(uVar10,uVar14)) {
                pbVar15 = pbVar15 + iVar28;
              }
              iVar16 = iVar16 + -4;
              puVar27 = &stack0xfffffffc;
            } while (iVar16 != 0);
          }
          else if (param_6 < 2) {
            do {
              *pbVar15 = bVar4;
              pbVar15 = pbVar15 + 1;
              if (CARRY4(uVar5,uVar14)) {
                pbVar15 = pbVar15 + iVar28;
              }
              puVar27 = &stack0xfffffffc;
              if (iVar16 == 1) break;
              *pbVar15 = bVar4;
              pbVar15 = pbVar15 + 1;
              uVar9 = uVar5 + uVar14 + uVar14;
              if (CARRY4(uVar5 + uVar14,uVar14)) {
                pbVar15 = pbVar15 + iVar28;
              }
              puVar27 = &stack0xfffffffc;
              if (iVar16 == 2) break;
              *pbVar15 = bVar4;
              pbVar15 = pbVar15 + 1;
              uVar10 = uVar9 + uVar14;
              if (CARRY4(uVar9,uVar14)) {
                pbVar15 = pbVar15 + iVar28;
              }
              puVar27 = &stack0xfffffffc;
              if (iVar16 == 3) break;
              *pbVar15 = bVar4;
              pbVar15 = pbVar15 + 1;
              uVar5 = uVar10 + uVar14;
              if (CARRY4(uVar10,uVar14)) {
                pbVar15 = pbVar15 + iVar28;
              }
              iVar16 = iVar16 + -4;
              puVar27 = &stack0xfffffffc;
            } while (iVar16 != 0);
          }
          else {
            local_28 = local_28 - param_1[1];
            local_2c = local_2c - param_1[2];
            do {
              (**(code **)(puVar25 + 0x20))(local_28,local_2c,puVar25,auStack_6c);
              bVar29 = CARRY4(uVar5,uVar14);
              uVar5 = uVar5 + uVar14;
              if (bVar29) {
                local_2c = local_2c + 1;
              }
              local_28 = local_28 + uVar19 * 2 + 1;
              iVar16 = iVar16 + -1;
              puVar27 = puVar25;
            } while (iVar16 != 0);
          }
        }
        goto LAB_0040461d;
      }
      uVar12 = ((uVar5 ^ uVar19) - uVar19) + (uVar18 + 1 | uVar18);
      uVar10 = local_30 - local_28 >> 0x1f;
      iVar28 = ((local_30 - local_28 ^ uVar10) - uVar10) + 1;
    }
  }
  uVar20 = (undefined4)((ulonglong)((longlong)local_2c * (longlong)(int)uVar5) >> 0x20);
  pbVar15 = (byte *)((int)((longlong)local_2c * (longlong)(int)uVar5) + *piVar1 + local_28);
  if (param_6 == 1) {
    do {
      *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
      pbVar15 = pbVar15 + uVar12;
      puVar27 = &stack0xfffffffc;
      if (iVar28 == 1) break;
      *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
      pbVar15 = pbVar15 + uVar12;
      puVar27 = &stack0xfffffffc;
      if (iVar28 == 2) break;
      *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
      pbVar15 = pbVar15 + uVar12;
      puVar27 = &stack0xfffffffc;
      if (iVar28 == 3) break;
      *pbVar15 = *(byte *)(param_7 + (uint)*pbVar15);
      pbVar15 = pbVar15 + uVar12;
      iVar28 = iVar28 + -4;
      puVar27 = &stack0xfffffffc;
    } while (iVar28 != 0);
  }
  else if (param_6 < 2) {
    do {
      *pbVar15 = bVar4;
      pbVar15 = pbVar15 + uVar12;
      puVar27 = &stack0xfffffffc;
      if (iVar28 == 1) break;
      *pbVar15 = bVar4;
      pbVar15 = pbVar15 + uVar12;
      puVar27 = &stack0xfffffffc;
      if (iVar28 == 2) break;
      *pbVar15 = bVar4;
      puVar27 = &stack0xfffffffc;
      if (iVar28 == 3) break;
      pbVar15[uVar12] = bVar4;
      pbVar15 = pbVar15 + uVar12 + uVar12;
      iVar28 = iVar28 + -4;
      puVar27 = &stack0xfffffffc;
    } while (iVar28 != 0);
  }
  else {
    local_28 = local_28 - param_1[1];
    local_2c = local_2c - param_1[2];
    uVar18 = uVar9 != 0 | uVar18;
    do {
      (**(code **)(puVar26 + 0x20))(local_28,local_2c,puVar26,auStack_6c,uVar18,uVar20);
      local_2c = local_2c + (uVar11 != 0 | uVar19);
      local_28 = local_28 + uVar18;
      iVar28 = iVar28 + -1;
      puVar27 = puVar26;
    } while (iVar28 != 0);
  }
LAB_0040461d:
  return (uint)(*(int *)(puVar27 + -0x34) != 0);
}
```

---

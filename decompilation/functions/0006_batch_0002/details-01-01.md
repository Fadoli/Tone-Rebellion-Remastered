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

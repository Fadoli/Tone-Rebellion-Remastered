# 0005_batch_0001 — détails (3/3)

## FUN_00404637 — 0x404637

- Classification : internal (Ghidra FunctionManager)
- Corps : `0x404637–0x404759`, `0x404765–0x40476f`
- État : pseudocode obtenu
- Evidence : `ev_9bf68baf436f01d574b3e7fb847adb11cacbc54549aa8becc7adb163a2a68085`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs observés

- aucun relevé

### Chaînes référencées observées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4
FUN_00404637(int *param_1,int param_2,int param_3,int param_4,int param_5,undefined1 param_6)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined1 *puVar10;
  int iVar11;
  uint uVar12;
  undefined1 *puVar13;
  
  piVar1 = (int *)*param_1;
  iVar9 = piVar1[1];
  iVar5 = iVar9 + 1;
  if ((iVar5 == 0 || iVar9 < -1) || (iVar11 = piVar1[2], iVar11 < 0)) {
    return 0xffffffff;
  }
  iVar2 = param_1[1];
  iVar6 = iVar2;
  if (iVar2 < 1) {
    iVar6 = 0;
  }
  iVar3 = param_1[2];
  iVar7 = iVar3;
  if (iVar3 < 1) {
    iVar7 = 0;
  }
  iVar8 = param_1[3];
  if (iVar9 <= param_1[3]) {
    iVar8 = iVar9;
  }
  iVar9 = param_1[4];
  if (iVar11 <= param_1[4]) {
    iVar9 = iVar11;
  }
  if ((iVar6 <= iVar8) && (iVar7 <= iVar9)) {
    param_2 = param_2 + iVar2;
    param_4 = param_4 + iVar2;
    param_3 = param_3 + iVar3;
    param_5 = param_5 + iVar3;
    if (param_2 <= iVar6) {
      param_2 = iVar6;
    }
    if (param_3 <= iVar7) {
      param_3 = iVar7;
    }
    if (iVar8 <= param_4) {
      param_4 = iVar8;
    }
    if (iVar9 <= param_5) {
      param_5 = iVar9;
    }
    if (param_2 <= param_4) {
      puVar10 = (undefined1 *)(param_3 * iVar5 + *piVar1 + param_2);
      uVar12 = param_5 - param_3;
      if (param_3 <= param_5) {
        while( true ) {
          iVar9 = (param_4 - param_2) + 1;
          puVar13 = puVar10;
          if ((uVar12 & 1) != 0) {
            iVar9 = param_4 - param_2;
            puVar13 = puVar10 + 1;
          }
          do {
            *puVar13 = param_6;
            iVar11 = iVar9 + -2;
            bVar4 = 1 < iVar9;
            iVar9 = iVar11;
            puVar13 = puVar13 + 2;
          } while (iVar11 != 0 && bVar4);
          uVar12 = uVar12 - 1;
          if ((int)uVar12 < 0) break;
          puVar10 = puVar10 + iVar5;
        }
        return 0;
      }
    }
    return 0xfffffffc;
  }
  return 0xfffffffe;
}
```

---

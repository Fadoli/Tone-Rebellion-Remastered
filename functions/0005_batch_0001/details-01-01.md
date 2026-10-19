# 0005_batch_0001 — détails (1/3)

## FUN_00403a3c — 0x403a3c

- Classification : internal (Ghidra FunctionManager)
- Corps : `0x403a3c–0x403a64`
- État : pseudocode obtenu
- Evidence : `ev_7a9b8bac8778a104fd86e30f689a09742ce2042a81459a4fd85cb119b8842a29`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs observés

- aucun relevé

### Chaînes référencées observées

- `0x498db5` — "CGA.DLL"

### Pseudocode Ghidra

```c
undefined1 * FUN_00403a3c(undefined4 *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar2 = (char *)(*(code *)*param_1)();
  pcVar3 = &DAT_00498db4;
  do {
    cVar1 = *pcVar2;
    *pcVar3 = cVar1;
    pcVar3 = pcVar3 + 1;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  return &DAT_00498db4;
}
```

---

---

## FUN_00403a65 — 0x403a65

- Classification : internal (Ghidra FunctionManager)
- Corps : `0x403a65–0x403a83`
- État : pseudocode obtenu
- Evidence : `ev_125dc2d0373002d6bfcbfe3ee11beace39e61b10fd339e7571742426296fecc0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs observés

- aucun relevé

### Chaînes référencées observées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00403a65(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_00498d80;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_1;
    param_1 = param_1 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}
```

---

---

## FUN_00403a84 — 0x403a84

- Classification : internal (Ghidra FunctionManager)
- Corps : `0x403a84–0x403b5e`
- État : pseudocode obtenu
- Evidence : `ev_2ca0e21e0cc917ff3674f4d5baa33bc3d4a49dc1bc6368a42d9b170e4f290209`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs observés

- aucun relevé

### Chaînes référencées observées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00403a84(int *param_1,int param_2,int param_3,byte param_4)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  
  piVar2 = (int *)*param_1;
  iVar3 = piVar2[1];
  if ((iVar3 + 1 == 0 || iVar3 < -1) || (iVar4 = piVar2[2], iVar4 < 0)) {
    return 0xffffffff;
  }
  iVar5 = param_1[1];
  iVar7 = iVar5;
  if (iVar5 < 1) {
    iVar7 = 0;
  }
  iVar6 = param_1[2];
  iVar8 = iVar6;
  if (iVar6 < 1) {
    iVar8 = 0;
  }
  iVar9 = param_1[3];
  if (iVar3 <= param_1[3]) {
    iVar9 = iVar3;
  }
  iVar10 = param_1[4];
  if (iVar4 <= param_1[4]) {
    iVar10 = iVar4;
  }
  if ((iVar7 <= iVar9) && (iVar8 <= iVar10)) {
    param_2 = param_2 + iVar5;
    param_3 = param_3 + iVar6;
    if ((((iVar7 <= param_2) && (param_2 <= iVar9)) && (iVar8 <= param_3)) && (param_3 <= iVar10)) {
      pbVar11 = (byte *)(param_3 * (iVar3 + 1) + *piVar2 + param_2);
      bVar1 = *pbVar11;
      *pbVar11 = param_4;
      return (uint)bVar1;
    }
    return 0xfffffffd;
  }
  return 0xfffffffe;
}
```

---

---

## FUN_00403b5f — 0x403b5f

- Classification : internal (Ghidra FunctionManager)
- Corps : `0x403b5f–0x403c34`
- État : pseudocode obtenu
- Evidence : `ev_0e252ecce86029a35f495364443865776b00a20ea13ae8497667111fbd57c24b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs observés

- aucun relevé

### Chaînes référencées observées

- aucune relevée

### Pseudocode Ghidra

```c
undefined8 FUN_00403b5f(int *param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 in_EDX;
  
  piVar1 = (int *)*param_1;
  iVar2 = piVar1[1];
  if ((iVar2 + 1 == 0 || iVar2 < -1) || (iVar3 = piVar1[2], iVar3 < 0)) {
    return CONCAT44(in_EDX,0xffffffff);
  }
  iVar4 = param_1[1];
  iVar7 = iVar4;
  if (iVar4 < 1) {
    iVar7 = 0;
  }
  iVar5 = param_1[2];
  iVar8 = iVar5;
  if (iVar5 < 1) {
    iVar8 = 0;
  }
  iVar9 = param_1[3];
  if (iVar2 <= param_1[3]) {
    iVar9 = iVar2;
  }
  iVar10 = param_1[4];
  if (iVar3 <= param_1[4]) {
    iVar10 = iVar3;
  }
  if ((iVar7 <= iVar9) && (iVar8 <= iVar10)) {
    param_2 = param_2 + iVar4;
    param_3 = param_3 + iVar5;
    if ((((iVar7 <= param_2) && (param_2 <= iVar9)) && (iVar8 <= param_3)) && (param_3 <= iVar10)) {
      lVar6 = (longlong)param_3 * (longlong)(iVar2 + 1);
      return CONCAT44((int)((ulonglong)lVar6 >> 0x20),
                      (uint)*(byte *)((int)lVar6 + *piVar1 + param_2));
    }
    return CONCAT44(iVar3,0xfffffffd);
  }
  return CONCAT44(iVar3,0xfffffffe);
}
```

---

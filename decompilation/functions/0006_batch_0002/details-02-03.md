# 0006_batch_0002 — détails (3/3)

## FUN_004081ad — 0x4081ad

- Classification : internal
- Corps : `0x4081ad–0x408273`
- État : pseudocode obtenu
- Evidence : `ev_705e8187ae170fe513c9171d68992a477f05d8d88a081c54f773e388cb10039f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4080cf` — `FUN_004080cf`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004081ad(int *param_1,int *param_2,int *param_3,undefined4 param_4,int param_5,int param_6)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  longlong lVar4;
  uint uVar5;
  ushort uVar9;
  uint uVar6;
  ushort uVar10;
  uint uVar7;
  ushort uVar11;
  uint uVar8;
  ushort uVar12;
  int iVar13;
  int local_c;
  int local_8;
  
  FUN_004080cf(param_4,&local_8,&local_c);
  lVar1 = (longlong)((*param_1 - *param_3) * 0x10000) * (longlong)param_5;
  iVar13 = (int)((ulonglong)lVar1 >> 0x20) + (uint)(0xffff7fff < (uint)lVar1);
  lVar1 = (longlong)iVar13 * (longlong)local_8;
  uVar5 = (uint)lVar1;
  uVar9 = (ushort)(uVar5 + 0x8000 >> 0x10);
  lVar2 = (longlong)iVar13 * (longlong)local_c;
  uVar6 = (uint)lVar2;
  uVar10 = (ushort)(uVar6 + 0x8000 >> 0x10);
  lVar3 = (longlong)((param_1[1] - param_3[1]) * 0x10000) * (longlong)param_6;
  iVar13 = (int)((ulonglong)lVar3 >> 0x20) + (uint)(0xffff7fff < (uint)lVar3);
  lVar3 = (longlong)iVar13 * (longlong)local_8;
  uVar7 = (uint)lVar3;
  uVar11 = (ushort)(uVar7 + 0x8000 >> 0x10);
  lVar4 = (longlong)iVar13 * (longlong)local_c;
  uVar8 = (uint)lVar4;
  uVar12 = (ushort)(uVar8 + 0x8000 >> 0x10);
  *param_2 = (((uint)uVar9 |
              CONCAT22(uVar9,(short)((ulonglong)lVar1 >> 0x20) + (ushort)(0xffff7fff < uVar5)) <<
              0x10) - ((uint)uVar12 |
                      CONCAT22(uVar12,(short)((ulonglong)lVar4 >> 0x20) +
                                      (ushort)(0xffff7fff < uVar8)) << 0x10)) + *param_3;
  param_2[1] = ((uint)uVar11 |
               CONCAT22(uVar11,(short)((ulonglong)lVar3 >> 0x20) + (ushort)(0xffff7fff < uVar7)) <<
               0x10) + ((uint)uVar10 |
                       CONCAT22(uVar10,(short)((ulonglong)lVar2 >> 0x20) +
                                       (ushort)(0xffff7fff < uVar6)) << 0x10) + param_3[1];
  return;
}
```

---

---

## FUN_00408274 — 0x408274

- Classification : internal
- Corps : `0x408274–0x408286`
- État : pseudocode obtenu
- Evidence : `ev_2e3ad3da1a7ba95ae90f12f47dfd6e4e2a34f76514a7b058b42bcb51531e2b88`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00408274(int param_1)

{
  return *(undefined4 *)(param_1 + 8);
}
```

---

---

## FUN_00408287 — 0x408287

- Classification : internal
- Corps : `0x408287–0x4082a6`
- État : pseudocode obtenu
- Evidence : `ev_cf04eb740ba4963a34f75df64cf9a5c36a6556d1409f35cf44e81cd3028342c3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00408287(int param_1,int param_2)

{
  return *(undefined4 *)(*(int *)(param_2 * 4 + param_1 + 0x10) + param_1);
}
```

---

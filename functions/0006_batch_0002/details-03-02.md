# 0006_batch_0002 — détails (2/2)

## FUN_004087e7 — 0x4087e7

- Classification : internal
- Corps : `0x4087e7–0x408868`
- État : pseudocode obtenu
- Evidence : `ev_605c1dce5ab3db1e73042ab5f54008bec9b61c2ab4f2803020a369fa5212a1af`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x408471` — `FUN_00408471`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004087e7(undefined4 param_1,int param_2)

{
  undefined1 *puVar1;
  undefined1 uVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  uint uVar8;
  int iVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  
  sVar3 = *(short *)(param_2 + 10);
  sVar4 = *(short *)(param_2 + 6);
  iVar9 = 0;
  uVar5 = *(ushort *)(param_2 + 0x42);
  puVar10 = (undefined1 *)(param_2 + 0x80);
  do {
    puVar11 = &DAT_004992f9;
    do {
      puVar1 = puVar10 + 1;
      uVar6 = CONCAT11(*puVar10,*puVar10) & 0xc0ff;
      uVar7 = uVar6 ^ 0xc000;
      if ((char)(uVar7 >> 8) == '\0') {
        puVar10 = puVar10 + 2;
        uVar2 = *puVar1;
        puVar12 = puVar11;
        for (uVar8 = uVar7 & 0x3f; uVar8 != 0; uVar8 = uVar8 - 1) {
          *puVar12 = uVar2;
          puVar12 = puVar12 + 1;
        }
      }
      else {
        puVar12 = puVar11 + 1;
        *puVar11 = (char)uVar6;
        puVar10 = puVar1;
      }
      puVar11 = puVar12;
    } while ((int)puVar12 < (int)(&DAT_004992f9 + uVar5));
    FUN_00408471(param_1,iVar9,&DAT_004992f9,(uint)uVar5);
    iVar9 = iVar9 + 1;
  } while (iVar9 <= (int)(uint)(ushort)(sVar3 - sVar4));
  return 0;
}
```

---

---

## FUN_00408869 — 0x408869

- Classification : internal
- Corps : `0x408869–0x408893`
- État : pseudocode obtenu
- Evidence : `ev_823742a0719138d045c46fcc5b0791112d6fd456243a2476e2db1caea847c23e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00408869(int param_1,int param_2,byte *param_3)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = 0x300;
  pbVar2 = (byte *)(param_1 + param_2 + -0x300);
  do {
    *param_3 = *pbVar2 >> 2;
    iVar1 = iVar1 + -1;
    pbVar2 = pbVar2 + 1;
    param_3 = param_3 + 1;
  } while (iVar1 != 0);
  return;
}
```

---

---

## FUN_00408894 — 0x408894

- Classification : internal
- Corps : `0x408894–0x4088ba`
- État : pseudocode obtenu
- Evidence : `ev_eb5d62f92b40ba496faeb9b2b2c573951987d08af9a5cd284f35e2962fe86e40`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00408894(int param_1)

{
  return CONCAT22((*(short *)(param_1 + 8) - *(short *)(param_1 + 4)) + 1,
                  (*(short *)(param_1 + 10) - *(short *)(param_1 + 6)) + 1);
}
```

---

---

## FUN_004088bb — 0x4088bb

- Classification : internal
- Corps : `0x4088bb–0x408902`
- État : pseudocode obtenu
- Evidence : `ev_b46029f6eb99768616c58abfbd145e1a35cbf4fdff0285549836f038d0a2c223`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004088bb(void)

{
  int in_ECX;
  int iVar1;
  int *unaff_EDI;
  
  *unaff_EDI = in_ECX + 2;
  unaff_EDI[1] = in_ECX << 1;
  for (iVar1 = 0; iVar1 < in_ECX; iVar1 = iVar1 + 1) {
    *(char *)(iVar1 + 0x102e + (int)unaff_EDI) = (char)iVar1;
    *(char *)(iVar1 + 0x202e + (int)unaff_EDI) = (char)iVar1;
    *(undefined2 *)((int)unaff_EDI + iVar1 * 2 + 0x302e) = 0xffff;
  }
  for (; iVar1 < 0x1000; iVar1 = iVar1 + 1) {
    *(undefined2 *)((int)unaff_EDI + iVar1 * 2 + 0x302e) = 0xfffe;
  }
  return;
}
```

---

---

## FUN_00408903 — 0x408903

- Classification : internal
- Corps : `0x408903–0x40891b`
- État : pseudocode obtenu
- Evidence : `ev_0cfdd9ab23356a20025980c718dbc5c5abf248bbdfae78c1054afb517e6b6c98`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
byte FUN_00408903(void)

{
  byte bVar1;
  byte *unaff_ESI;
  byte *pbVar2;
  int unaff_EDI;
  
  pbVar2 = unaff_ESI;
  if (*(int *)(unaff_EDI + 0x10) == 0) {
    pbVar2 = unaff_ESI + 1;
    *(uint *)(unaff_EDI + 0x10) = (uint)*unaff_ESI;
  }
  bVar1 = *pbVar2;
  *(int *)(unaff_EDI + 0x10) = *(int *)(unaff_EDI + 0x10) + -1;
  return bVar1;
}
```

---

---

## FUN_0040891c — 0x40891c

- Classification : internal
- Corps : `0x40891c–0x408961`
- État : pseudocode obtenu
- Evidence : `ev_ccbfc0eab3e20abc185bcf0e0d1fbe8d9b52aeabc9dcaefc3e790d3364a310d5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x408903` — `FUN_00408903`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_0040891c(void)

{
  byte bVar1;
  uint uVar2;
  int in_EDX;
  int unaff_EDI;
  undefined8 uVar3;
  
  if (*(int *)(unaff_EDI + 0x18) == 0) {
    uVar3 = FUN_00408903();
    in_EDX = (int)((ulonglong)uVar3 >> 0x20);
    *(int *)(unaff_EDI + 0x14) = (int)uVar3;
    *(undefined4 *)(unaff_EDI + 0x18) = 8;
  }
  if (*(int *)(unaff_EDI + 0x18) < in_EDX) {
    uVar3 = FUN_00408903();
    in_EDX = (int)((ulonglong)uVar3 >> 0x20);
    *(uint *)(unaff_EDI + 0x14) =
         *(uint *)(unaff_EDI + 0x14) |
         (int)uVar3 << ((byte)*(undefined4 *)(unaff_EDI + 0x18) & 0x1f);
    *(int *)(unaff_EDI + 0x18) = *(int *)(unaff_EDI + 0x18) + 8;
  }
  bVar1 = (&DAT_0049a5f9)[in_EDX];
  uVar2 = *(uint *)(unaff_EDI + 0x14);
  *(int *)(unaff_EDI + 0x18) = *(int *)(unaff_EDI + 0x18) - in_EDX;
  *(uint *)(unaff_EDI + 0x14) = *(uint *)(unaff_EDI + 0x14) >> ((byte)in_EDX & 0x1f);
  return uVar2 & bVar1;
}
```

# 0007_batch_0003 — détails (1/3)

## FUN_00408962 — 0x408962

- Classification : internal
- Corps : `0x408962–0x4089a7`
- État : pseudocode obtenu
- Evidence : `ev_ae50e28c8a4cc3ccce321b16684f76b3e009a79bdea703ca4ac7243272a3eb0f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00408962(void)

{
  int in_ECX;
  int unaff_EBX;
  int *unaff_EDI;
  
  *(short *)((int)unaff_EDI + *unaff_EDI * 2 + 0x302e) = (short)in_ECX;
  *(undefined1 *)(*unaff_EDI + 0x202e + (int)unaff_EDI) =
       *(undefined1 *)(unaff_EBX + 0x102e + (int)unaff_EDI);
  *(undefined1 *)(*unaff_EDI + 0x102e + (int)unaff_EDI) =
       *(undefined1 *)(in_ECX + 0x102e + (int)unaff_EDI);
  *unaff_EDI = *unaff_EDI + 1;
  if ((*unaff_EDI == unaff_EDI[1]) && (unaff_EDI[7] < 0xc)) {
    unaff_EDI[7] = unaff_EDI[7] + 1;
    unaff_EDI[1] = unaff_EDI[1] << 1;
  }
  return;
}
```

---

---

## FUN_004089a8 — 0x4089a8

- Classification : internal
- Corps : `0x4089a8–0x408a24`
- État : pseudocode obtenu
- Evidence : `ev_1277badfc42533adcae43d03b8e689868cf4388522d0922453354ad75993d9a1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x408471` — `FUN_00408471`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004089a8(void)

{
  undefined1 in_AL;
  int unaff_EDI;
  
  (&DAT_004992f9)[*(int *)(unaff_EDI + 8)] = in_AL;
  *(int *)(unaff_EDI + 8) = *(int *)(unaff_EDI + 8) + 1;
  *(int *)(unaff_EDI + 0x20) = *(int *)(unaff_EDI + 0x20) + -1;
  if (*(int *)(unaff_EDI + 0x20) == 0) {
    FUN_00408471(DAT_0049a60c,*(undefined4 *)(unaff_EDI + 0xc),&DAT_004992f9,
                 *(undefined4 *)(unaff_EDI + 0x24));
    *(undefined4 *)(unaff_EDI + 8) = 0;
    *(undefined4 *)(unaff_EDI + 0x20) = *(undefined4 *)(unaff_EDI + 0x24);
    if (*(char *)(unaff_EDI + 0x2c) == '\0') {
      *(int *)(unaff_EDI + 0xc) = *(int *)(unaff_EDI + 0xc) + 1;
      if (*(int *)(unaff_EDI + 0x28) <= *(int *)(unaff_EDI + 0xc)) {
        *(undefined4 *)(unaff_EDI + 0xc) = 0;
      }
    }
    else {
      *(int *)(unaff_EDI + 0xc) =
           *(int *)(unaff_EDI + 0xc) + (uint)(byte)(&DAT_0049a602)[*(byte *)(unaff_EDI + 0x2d)];
      if (*(int *)(unaff_EDI + 0x28) <= *(int *)(unaff_EDI + 0xc)) {
        *(char *)(unaff_EDI + 0x2d) = *(char *)(unaff_EDI + 0x2d) + '\x01';
        *(uint *)(unaff_EDI + 0xc) = (uint)*(byte *)(*(byte *)(unaff_EDI + 0x2d) + 0x49a607);
      }
    }
  }
  return;
}
```

---

---

## FUN_00408a25 — 0x408a25

- Classification : internal
- Corps : `0x408a25–0x408c3d`
- État : pseudocode obtenu
- Evidence : `ev_a577f147c1fceec3b4ea43ff12b67de50b680f6bd6e1d0387bbdc1fa29b6ad03`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4088bb` — `FUN_004088bb`
- `0x40891c` — `FUN_0040891c`
- `0x408962` — `FUN_00408962`
- `0x4089a8` — `FUN_004089a8`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Removing unreachable block (ram,0x00408bef) */
/* WARNING: Removing unreachable block (ram,0x00408c0e) */

undefined1 FUN_00408a25(undefined4 param_1,int param_2,undefined4 *param_3)

{
  undefined1 uVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  undefined1 *puVar8;
  byte *pbVar9;
  undefined4 *puVar10;
  int local_18;
  uint local_14;
  
  DAT_0049a60c = param_1;
  puVar10 = param_3;
  for (iVar5 = 2; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(undefined1 *)puVar10 = 0;
    puVar10 = (undefined4 *)((int)puVar10 + 1);
  }
  for (iVar5 = 0xb; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar10 = 0;
    puVar10 = puVar10 + 1;
  }
  uVar1 = *(undefined1 *)(param_2 + 0xb);
  iVar5 = param_2 + 0xd;
  if ((*(byte *)(param_2 + 10) & 0x80) != 0) {
    iVar5 = iVar5 + (1 << (*(byte *)(param_2 + 10) & 7) + 1) * 3;
  }
  param_3[9] = (uint)*(ushort *)(iVar5 + 5);
  param_3[10] = (uint)*(ushort *)(iVar5 + 7);
  bVar2 = *(byte *)(iVar5 + 9);
  *(byte *)(param_3 + 0xb) = bVar2;
  *(byte *)(param_3 + 0xb) = *(byte *)(param_3 + 0xb) & 0x40;
  pbVar7 = (byte *)(iVar5 + 10);
  if ((bVar2 & 0x80) != 0) {
    pbVar7 = pbVar7 + (1 << (bVar2 & 7) + 1) * 3;
  }
  param_3[4] = 0;
  pbVar9 = pbVar7 + 1;
  bVar2 = *pbVar7;
  uVar3 = 1 << (bVar2 & 0x1f);
  param_3[7] = bVar2 + 1;
  FUN_004088bb();
  local_14 = 0xffff;
  local_18 = 0;
  *(undefined1 *)((int)param_3 + 0x2d) = 0;
  param_3[8] = param_3[9];
  param_3[2] = 0;
  param_3[3] = 0;
  do {
    iVar5 = param_3[7];
    if (iVar5 < 9) {
      uVar4 = FUN_0040891c(iVar5);
    }
    else {
      uVar4 = FUN_0040891c(iVar5);
      iVar5 = FUN_0040891c(iVar5);
      uVar4 = iVar5 << 8 | uVar4;
    }
    if (uVar4 == uVar3) {
      FUN_004088bb();
      param_3[7] = bVar2 + 1;
      local_14 = 0xffff;
    }
    else {
      pbVar7 = pbVar9;
      if (uVar4 == uVar3 + 1) {
        do {
          while (param_3[4] != 0) {
            param_3[4] = param_3[4] + -1;
            pbVar7 = pbVar7 + 1;
          }
          pbVar9 = pbVar7 + 1;
          param_3[4] = (uint)*pbVar7;
          pbVar7 = pbVar9;
        } while (param_3[4] != 0);
        local_18 = 0xffff;
      }
      else {
        if (*(short *)((int)param_3 + uVar4 * 2 + 0x302e) == -2) {
          FUN_00408962();
        }
        else if (local_14 != 0xffff) {
          FUN_00408962();
        }
        iVar5 = 0;
        puVar8 = (undefined1 *)((int)param_3 + 0x2e);
        uVar6 = uVar4;
        do {
          *puVar8 = *(undefined1 *)(uVar6 + 0x202e + (int)param_3);
          puVar8 = puVar8 + 1;
          iVar5 = iVar5 + 1;
          uVar6 = (uint)*(ushort *)((int)param_3 + uVar6 * 2 + 0x302e);
        } while (uVar6 != 0xffff);
        do {
          FUN_004089a8();
          iVar5 = iVar5 + -1;
          local_14 = uVar4;
        } while (iVar5 != 0);
      }
    }
  } while (local_18 == 0);
  return uVar1;
}
```

---

---

## FUN_00408c3e — 0x408c3e

- Classification : internal
- Corps : `0x408c3e–0x408c9e`
- État : pseudocode obtenu
- Evidence : `ev_c9284a651bb46bd7351a2e0557bcf988f3f53ebd933cea01908744999b3d3c00`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00408c3e(int param_1,byte *param_2)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  
  pbVar2 = (byte *)(param_1 + 0xd);
  if ((*(byte *)(param_1 + 10) & 0x80) != 0) {
    iVar1 = (1 << (*(byte *)(param_1 + 10) & 7) + 1) * 3;
    pbVar3 = pbVar2;
    pbVar4 = param_2;
    do {
      pbVar2 = pbVar3 + 1;
      *pbVar4 = *pbVar3 >> 2;
      iVar1 = iVar1 + -1;
      pbVar3 = pbVar2;
      pbVar4 = pbVar4 + 1;
    } while (iVar1 != 0);
  }
  if ((pbVar2[9] & 0x80) != 0) {
    iVar1 = (1 << (pbVar2[9] & 7) + 1) * 3;
    pbVar2 = pbVar2 + 10;
    do {
      *param_2 = *pbVar2 >> 2;
      iVar1 = iVar1 + -1;
      pbVar2 = pbVar2 + 1;
      param_2 = param_2 + 1;
    } while (iVar1 != 0);
  }
  return;
}
```

---

---

## FUN_00408c9f — 0x408c9f

- Classification : internal
- Corps : `0x408c9f–0x408cd6`
- État : pseudocode obtenu
- Evidence : `ev_cfd30fc133452bd80012ede0ffa77a69245a912126a543f4f09fc8f5077f5eaa`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00408c9f(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 + 0xd;
  if ((*(byte *)(param_1 + 10) & 0x80) != 0) {
    iVar1 = iVar1 + (1 << (*(byte *)(param_1 + 10) & 7) + 1) * 3;
  }
  return CONCAT22(*(undefined2 *)(iVar1 + 5),*(undefined2 *)(iVar1 + 7));
}
```

---

---

## FUN_00408cd7 — 0x408cd7

- Classification : internal
- Corps : `0x408cd7–0x408cf8`
- État : pseudocode obtenu
- Evidence : `ev_0011c876e83c8585df6fb154d40b55e7013535cd9bb1eeccf441d2438937df98`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00408cd7(int param_1,int param_2)

{
  return *(undefined4 *)(*(int *)(param_1 + 8 + param_2 * 8) + param_1);
}
```

---

---

## FUN_00408cf9 — 0x408cf9

- Classification : internal
- Corps : `0x408cf9–0x408d1b`
- État : pseudocode obtenu
- Evidence : `ev_fbb6a6922072f4dd121014e305c60af42b3075020e74e2a5fbc42a03114f2312`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00408cf9(int param_1,int param_2)

{
  return *(undefined4 *)(*(int *)(param_1 + 8 + param_2 * 8) + param_1 + 4);
}
```

---

---

## FUN_00408d1c — 0x408d1c

- Classification : internal
- Corps : `0x408d1c–0x408d4f`
- État : pseudocode obtenu
- Evidence : `ev_ec6bbe6ef87384414b07d578ef68df1dc8b771451b276dbf035eacbf37396ea1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00408d1c(int param_1,int param_2)

{
  param_1 = *(int *)(param_1 + 8 + param_2 * 8) + param_1;
  return CONCAT22(((short)*(undefined4 *)(param_1 + 0x10) - (short)*(undefined4 *)(param_1 + 8)) + 1
                  ,((short)*(undefined4 *)(param_1 + 0x14) - (short)*(undefined4 *)(param_1 + 0xc))
                   + 1);
}
```

---

---

## FUN_00408d50 — 0x408d50

- Classification : internal
- Corps : `0x408d50–0x408d79`
- État : pseudocode obtenu
- Evidence : `ev_454fd93af120573e062df7f22e3cceb95936f3b1b5221fe8d1ec339ff859ad8f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00408d50(int param_1,int param_2)

{
  param_1 = *(int *)(param_1 + 8 + param_2 * 8) + param_1;
  return CONCAT22((short)*(undefined4 *)(param_1 + 8),*(undefined2 *)(param_1 + 0xc));
}
```

---

---

## FUN_00408d7a — 0x408d7a

- Classification : internal
- Corps : `0x408d7a–0x408dc4`
- État : pseudocode obtenu
- Evidence : `ev_b52f28a39adacbe9a9e4d02f1f96e3e908022fbc4d10086755569339295c839c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00408d7a(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  
  iVar2 = *(int *)(param_1 + param_2 * 8 + 0xc);
  if (iVar2 != 0) {
    pbVar3 = (byte *)(iVar2 + param_1);
    iVar2 = *(int *)pbVar3;
    do {
      iVar1 = (uint)pbVar3[4] * 3;
      *(byte *)(iVar1 + param_3) = pbVar3[5];
      *(undefined2 *)(iVar1 + 1 + param_3) = *(undefined2 *)(pbVar3 + 6);
      iVar2 = iVar2 + -1;
      pbVar3 = pbVar3 + 4;
    } while (iVar2 != 0);
  }
  return;
}
```

---

---

## FUN_00408dc5 — 0x408dc5

- Classification : internal
- Corps : `0x408dc5–0x408e0c`
- État : pseudocode obtenu
- Evidence : `ev_cec51238bc0802dbeba35e9f75c5d9753ce539cd7e8d1dfabbbe6945eaea73d4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00408dc5(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  iVar1 = *(int *)(param_1 + param_2 * 8 + 0xc);
  if (iVar1 == 0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    puVar5 = (undefined4 *)(iVar1 + param_1);
    puVar3 = (undefined4 *)*puVar5;
    puVar4 = puVar3;
    puVar2 = param_3;
    while (puVar2 != (undefined4 *)0x0) {
      puVar5 = puVar5 + 1;
      *param_3 = *puVar5;
      puVar4 = (undefined4 *)((int)puVar4 + -1);
      param_3 = param_3 + 1;
      puVar2 = puVar4;
    }
  }
  return puVar3;
}
```

---

---

## FUN_00408e0d — 0x408e0d

- Classification : internal
- Corps : `0x408e0d–0x408e56`
- État : pseudocode obtenu
- Evidence : `ev_b1c08169ec8bcb6e1de155c815152639cb73cfb56906b2a3c60036d5324d546a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00408e0d(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  iVar1 = *(int *)(param_1 + param_2 * 8 + 0xc);
  if (iVar1 == 0) {
    puVar3 = (undefined4 *)0x0;
  }
  else {
    puVar5 = (undefined4 *)(iVar1 + param_1);
    puVar3 = (undefined4 *)*puVar5;
    puVar4 = puVar3;
    puVar2 = param_3;
    while (puVar2 != (undefined4 *)0x0) {
      puVar5 = puVar5 + 1;
      *puVar5 = *param_3;
      puVar4 = (undefined4 *)((int)puVar4 + -1);
      param_3 = param_3 + 1;
      puVar2 = puVar4;
    }
  }
  return puVar3;
}
```

---

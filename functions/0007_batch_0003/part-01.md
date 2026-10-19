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

## FUN_00408e57 — 0x408e57

- Classification : internal
- Corps : `0x408e57–0x408e69`
- État : pseudocode obtenu
- Evidence : `ev_d524310e832a02ea89916756ed54bae80187eabacf227bd9cefa6f897e1acb9b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00408e57(int param_1)

{
  return *(undefined4 *)(param_1 + 4);
}
```

---

## FUN_00408e6a — 0x408e6a

- Classification : internal
- Corps : `0x408e6a–0x408ecb`
- État : pseudocode obtenu
- Evidence : `ev_57e671619ed1b5b49fc2415e191c3a6fcaf0082e297c414b14ead9683f7540db`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00408e6a(int param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  
  iVar1 = *(int *)(param_1 + 4);
  piVar3 = (int *)(param_1 + 8);
  iVar2 = 1;
  piVar4 = piVar3;
  if (param_2 != (uint *)0x0) {
    *param_2 = 0;
    param_2 = param_2 + 1;
  }
joined_r0x00408e9a:
  do {
    iVar1 = iVar1 + -1;
    if (iVar1 == 0) {
      return iVar2;
    }
    piVar4 = piVar4 + 2;
    piVar5 = piVar3;
    do {
      if (*piVar4 == *piVar5) goto joined_r0x00408e9a;
      piVar5 = piVar5 + 2;
    } while ((int)piVar5 < (int)piVar4);
    if (param_2 != (uint *)0x0) {
      *param_2 = (uint)((int)piVar4 - (int)piVar3) >> 3;
      param_2 = param_2 + 1;
    }
    iVar2 = iVar2 + 1;
  } while( true );
}
```

---

## FUN_00408ecc — 0x408ecc

- Classification : internal
- Corps : `0x408ecc–0x408f2d`
- État : pseudocode obtenu
- Evidence : `ev_6ae4f32e1d6e97a13bb0b8d398f0a7c8a7e959734c5cccc89bda6c4ad456f0a1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00408ecc(int param_1,uint *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  
  iVar1 = *(int *)(param_1 + 4);
  piVar3 = (int *)(param_1 + 0xc);
  iVar2 = 1;
  piVar4 = piVar3;
  if (param_2 != (uint *)0x0) {
    *param_2 = 0;
    param_2 = param_2 + 1;
  }
joined_r0x00408efc:
  do {
    iVar1 = iVar1 + -1;
    if (iVar1 == 0) {
      return iVar2;
    }
    piVar4 = piVar4 + 2;
    piVar5 = piVar3;
    do {
      if (*piVar4 == *piVar5) goto joined_r0x00408efc;
      piVar5 = piVar5 + 2;
    } while ((int)piVar5 < (int)piVar4);
    if (param_2 != (uint *)0x0) {
      *param_2 = (uint)((int)piVar4 - (int)piVar3) >> 3;
      param_2 = param_2 + 1;
    }
    iVar2 = iVar2 + 1;
  } while( true );
}
```

---

## FUN_00409221 — 0x409221

- Classification : internal
- Corps : `0x409221–0x4093a4`
- État : pseudocode obtenu
- Evidence : `ev_586c9bc74cbcf185a5f856de693007537cb8f6e210a97f72ce21c29598dddecc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00409221(undefined4 *param_1,int param_2,uint param_3)

{
  short sVar1;
  bool bVar2;
  byte bVar3;
  char cVar4;
  undefined1 uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  byte *pbVar9;
  uint uVar10;
  undefined4 *puVar11;
  byte *pbVar12;
  byte *pbVar13;
  undefined4 local_14;
  uint local_c;
  uint local_8;
  
  puVar11 = (undefined4 *)&DAT_00499ff9;
  for (iVar6 = 0x40; iVar6 != 0; iVar6 = iVar6 + -1) {
    *puVar11 = 0;
    puVar11 = puVar11 + 1;
  }
  iVar6 = (param_1[2] + 1) * (param_1[1] + 1);
  local_8 = 0xffffffff;
  pbVar9 = (byte *)*param_1;
  pbVar12 = &DAT_004995f9;
  do {
    bVar3 = *pbVar9;
    uVar7 = (uint)bVar3;
    pbVar13 = pbVar12;
    if ((&DAT_00499ff9)[uVar7] == '\0') {
      (&DAT_00499ff9)[uVar7] = (&DAT_00499ff9)[uVar7] | 1;
      pbVar13 = pbVar12 + 1;
      *pbVar12 = bVar3;
      local_8 = local_8 + 1;
      (*DAT_00498da0)(uVar7,&DAT_004992f9 + uVar7 * 3);
    }
    iVar6 = iVar6 + -1;
    pbVar9 = pbVar9 + 1;
    pbVar12 = pbVar13;
  } while (iVar6 != 0);
  local_c = 0;
  uVar7 = local_8;
  do {
    iVar6 = (uint)(byte)(&DAT_004995f9)[uVar7] * 3;
    iVar8 = 2;
    do {
      bVar3 = (&DAT_004992f9)[iVar6] - *(char *)(iVar6 + param_2);
      uVar5 = 0xff;
      if ((char)(&DAT_004992f9)[iVar6] < *(char *)(iVar6 + param_2)) {
        bVar3 = -bVar3;
        uVar5 = 1;
      }
      (&DAT_00499ff9)[iVar6] = uVar5;
      (&DAT_004996f9)[iVar6] = bVar3;
      if ((char)(byte)local_c < (char)bVar3) {
        local_c = (uint)bVar3;
      }
      iVar6 = iVar6 + 1;
      iVar8 = iVar8 + -1;
    } while (-1 < iVar8);
    uVar7 = uVar7 - 1;
  } while (-1 < (int)uVar7);
  bVar3 = (byte)local_c >> 1;
  pbVar9 = (byte *)&DAT_0049a2f9;
  for (uVar7 = local_8 >> 1; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(ushort *)pbVar9 = CONCAT11(bVar3,bVar3);
    pbVar9 = pbVar9 + 2;
  }
  for (uVar7 = (uint)((local_8 & 1) != 0); uVar7 != 0; uVar7 = uVar7 - 1) {
    *pbVar9 = bVar3;
    pbVar9 = pbVar9 + 1;
  }
  if (local_c != 0) {
    local_14 = 0x8000;
    uVar7 = local_8;
    uVar10 = local_c;
    do {
      do {
        iVar6 = (uint)(byte)(&DAT_004995f9)[uVar7] * 3;
        iVar8 = 2;
        do {
          cVar4 = *(char *)((int)&DAT_0049a2f9 + iVar6 + iVar8) + (&DAT_004996f9)[iVar6 + iVar8];
          if ((char)(byte)local_c <= cVar4) {
            cVar4 = cVar4 - (byte)local_c;
            (&DAT_004992f9)[iVar6 + iVar8] =
                 (&DAT_004992f9)[iVar6 + iVar8] + (&DAT_00499ff9)[iVar6 + iVar8];
          }
          *(char *)((int)&DAT_0049a2f9 + iVar6 + iVar8) = cVar4;
          iVar8 = iVar8 + -1;
        } while (-1 < iVar8);
        (*DAT_00498da4)((&DAT_004995f9)[uVar7],&DAT_004992f9 + iVar6);
        uVar7 = uVar7 - 1;
      } while (-1 < (int)uVar7);
      iVar6 = local_14 + (int)(CONCAT44(param_3 >> 0x10,param_3 << 0x10) / (ulonglong)local_c);
      local_14._2_2_ = (short)((uint)iVar6 >> 0x10);
      bVar2 = 0 < local_14._2_2_;
      local_14 = iVar6;
      if (bVar2) {
        do {
          (*DAT_00498d94)();
          sVar1 = local_14._2_2_ + -1;
          local_14 = CONCAT22(sVar1,(undefined2)local_14);
        } while (sVar1 != 0);
      }
      uVar10 = uVar10 - 1;
      uVar7 = local_8;
    } while (uVar10 != 0);
  }
  return;
}
```

---

## FUN_004093a5 — 0x4093a5

- Classification : internal
- Corps : `0x4093a5–0x409431`
- État : pseudocode obtenu
- Evidence : `ev_3a20f3b9b67dfefe1361fbf8ec45d6e0eb1aaf819cc0dbb6e24fc17f79a62a91`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined8 FUN_004093a5(int *param_1,uint *param_2)

{
  int iVar1;
  longlong lVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  uint *puVar10;
  int local_8;
  
  puVar9 = (undefined4 *)&DAT_00499ff9;
  for (iVar5 = 0x40; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar9 = 0;
    puVar9 = puVar9 + 1;
  }
  iVar5 = param_1[3];
  iVar1 = param_1[1];
  iVar7 = param_1[4] - param_1[2];
  iVar3 = *(int *)(*param_1 + 4) + 1;
  lVar2 = (longlong)param_1[2] * (longlong)iVar3;
  iVar8 = *(int *)*param_1 + (int)lVar2 + param_1[1];
  local_8 = -1;
  iVar6 = iVar5 - iVar1;
  do {
    do {
      uVar4 = (uint)*(byte *)(iVar6 + iVar8);
      puVar10 = param_2;
      if ((&DAT_00499ff9)[uVar4] == '\0') {
        (&DAT_00499ff9)[uVar4] = (&DAT_00499ff9)[uVar4] | 1;
        local_8 = local_8 + 1;
        if (param_2 != (uint *)0x0) {
          puVar10 = param_2 + 1;
          *param_2 = uVar4;
        }
      }
      iVar6 = iVar6 + -1;
      param_2 = puVar10;
    } while (-1 < iVar6);
    iVar8 = iVar8 + iVar3;
    iVar7 = iVar7 + -1;
    iVar6 = iVar5 - iVar1;
  } while (-1 < iVar7);
  return CONCAT44((int)((ulonglong)lVar2 >> 0x20),local_8 + 1);
}
```

---

## FUN_0040aab0 — 0x40aab0

- Classification : internal
- Corps : `0x40aab0–0x40aaea`
- État : pseudocode obtenu
- Evidence : `ev_7b903208b6a40953c48fdc689816be9eba55c9f6af8ea0029adb48d64f45b005`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472c6c` — `__ftol`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040aab0(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  iVar1 = __ftol(param_2 - param_1,((double)(param_2 - param_1) * (double)param_4) / (double)param_3
                );
  return iVar1 + param_1;
}
```

---

## FUN_0040aaeb — 0x40aaeb

- Classification : internal
- Corps : `0x40aaeb–0x40ab04`
- État : pseudocode obtenu
- Evidence : `ev_aef8ee24821e5bfdfaf659b2c42bc919c9af4371555431ac33609823828d5620`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040aaeb(int param_1,int param_2,uint param_3)

{
  return param_1 + param_3 % ((param_2 - param_1) + 1U);
}
```

---

## FUN_0040ab05 — 0x40ab05

- Classification : internal
- Corps : `0x40ab05–0x40ab41`
- État : pseudocode obtenu
- Evidence : `ev_6056eb40dfb1c2d9534d877f668c6067f854e40c9b77cb3c056aa48b4d653454`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0040ab05(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  undefined4 local_10;
  
  uVar1 = (param_2 - param_1) * 2;
  local_10 = param_3 % uVar1;
  if (param_2 - param_1 < (int)local_10) {
    local_10 = uVar1 - local_10;
  }
  return param_1 + local_10;
}
```

---

## FUN_0040ab42 — 0x40ab42

- Classification : internal
- Corps : `0x40ab42–0x40ad93`
- État : pseudocode obtenu
- Evidence : `ev_df297f81e526da8b4ae1f124854cd14e66efdb967f943694b94997a7d4ce88de`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40105f` — `thunk_FUN_0040ab05`
- `0x4013a7` — `thunk_FUN_00456a6b`
- `0x4014a1` — `thunk_FUN_00456aca`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401d11` — `thunk_FUN_00456a87`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x40215d` — `thunk_FUN_0040aaeb`

### Chaînes référencées

- `0x49ad20` — "shape"
- `0x49ad28` — "C:\\float\\src\\blddraw.cpp"
- `0x49ad4c` — "C:\\float\\src\\blddraw.cpp"
- `0x49ad70` — "C:\\float\\src\\blddraw.cpp"

### Pseudocode Ghidra

```c
void FUN_0040ab42(int param_1,short *param_2)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  byte *pbVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  uint local_14;
  
  sVar1 = DAT_004a4b74;
  if (((int)(char)param_2[0x11] & 1 << ((byte)DAT_0049f538 & 0x1f)) != 0) {
    iVar8 = (*(int *)(param_1 + 4) + (int)*param_2) -
            (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
    iVar9 = *(int *)(param_1 + 8) + (int)param_2[1];
    if (DAT_004a4b74 != -1) {
      uVar2 = thunk_FUN_00456a6b(DAT_004a4b74);
      iVar3 = thunk_FUN_0040e864(CONCAT22(extraout_var,uVar2));
      uVar2 = extraout_var_00;
      if (iVar3 == 0) {
        thunk_FUN_00414b64(s_C__float_src_blddraw_cpp_0049ad28,0x71,s_shape_0049ad20);
        uVar2 = extraout_var_01;
      }
      puVar4 = (undefined1 *)thunk_FUN_00456aca(CONCAT22(uVar2,sVar1));
      if (puVar4 == (undefined1 *)0x0) {
        thunk_FUN_00414b64(s_C__float_src_blddraw_cpp_0049ad4c,0x75,&DAT_0049ad44);
      }
      iVar5 = DAT_00618e44 / ((uint)(byte)puVar4[2] + *(int *)(param_2 + 6)) + (int)*param_2 % 0x17;
      if (((int)(char)param_2[0x11] & 1 << ((byte)DAT_0049f538 & 0x1f)) == 0) {
        pbVar6 = (byte *)thunk_FUN_00456a87(sVar1);
        if (pbVar6 == (byte *)0x0) {
          thunk_FUN_00414b64(s_C__float_src_blddraw_cpp_0049ad70,0x84,&DAT_0049ad68);
        }
        local_14 = (uint)*pbVar6;
      }
      else if (puVar4[3] == '\0') {
        local_14 = thunk_FUN_0040aaeb(*puVar4,puVar4[1],iVar5);
      }
      else {
        local_14 = thunk_FUN_0040ab05(*puVar4,puVar4[1],iVar5);
      }
      thunk_FUN_00404770(param_1,iVar3,*(int *)(param_2 + 6) * ((byte)puVar4[1] + 1) + local_14,
                         iVar8,iVar9);
      if (((*(uint *)(param_2 + 0xe) & 0x200) != 0) && (*(int *)(param_2 + 8) == 0)) {
        uVar7 = thunk_FUN_0040e864(DAT_0049acb8);
        thunk_FUN_00404770(param_1,uVar7,0x15,iVar8,iVar9);
      }
    }
  }
  return;
}
```

---

## FUN_0040ad94 — 0x40ad94

- Classification : internal
- Corps : `0x40ad94–0x40adb4`
- État : pseudocode obtenu
- Evidence : `ev_4586db16c58a3a23f362dc453333b4eb5755cdcdae4773f387b9a5f6b954977a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined2 FUN_0040ad94(int param_1)

{
  undefined2 uVar1;
  
  if ((param_1 < 5) || (0x21 < param_1)) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined2 *)(&DAT_0049acbe + param_1 * 2);
  }
  return uVar1;
}
```

---

## FUN_0040adb5 — 0x40adb5

- Classification : internal
- Corps : `0x40adb5–0x40ae4c`
- État : pseudocode obtenu
- Evidence : `ev_407e2460cd55410a56b04421eca788cdfcc32784fea228250b4da00e2fdbba23`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040adb5(int param_1,undefined2 *param_2,int *param_3)

{
  undefined2 local_c;
  undefined4 local_8;
  
  local_c = 0xffff;
  if (param_1 < 4) {
    if (param_1 == 1) {
      local_c = DAT_0049aca8;
    }
    else if (param_1 == 2) {
      local_c = DAT_0049acac;
    }
    else if (param_1 == 3) {
      local_c = DAT_0049acb0;
    }
    local_8 = 0;
  }
  else {
    local_c = DAT_0049acb4;
    local_8 = param_1 + -5;
  }
  *param_2 = local_c;
  *param_3 = local_8;
  return;
}
```

---

## FUN_0040ae4d — 0x40ae4d

- Classification : internal
- Corps : `0x40ae4d–0x40afd2`
- État : pseudocode obtenu
- Evidence : `ev_c0b728097c1a86101e3bd0f1682de03db6fc015407567ba16aab7a06b061e01c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012da` — `thunk_FUN_0040adb5`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401915` — `thunk_FUN_004502dc`
- `0x40198d` — `thunk_FUN_0040ab42`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401f14` — `thunk_FUN_00404770`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49ad8c` — "F%02d"

### Pseudocode Ghidra

```c
void FUN_0040ae4d(int param_1,short *param_2)

{
  int iVar1;
  undefined4 uVar2;
  short *extraout_EDX;
  short *psVar3;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  uint local_3c;
  int local_38;
  short *local_34;
  int local_30;
  undefined1 local_2c [40];
  
  thunk_FUN_0040ab42(param_1,param_2);
  local_30 = (*(int *)(param_1 + 4) + (int)*param_2) -
             (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
  local_38 = *(int *)(param_1 + 8) + (int)param_2[1];
  iVar1 = thunk_FUN_004502dc();
  thunk_FUN_0040adb5(iVar1,&local_3c,&local_34);
  if (iVar1 == 1) {
    local_34 = (short *)(param_2[0x14] + -1);
    psVar3 = extraout_EDX;
    if (0x31 < (int)local_34) {
      local_34 = (short *)0x31;
    }
  }
  else if (iVar1 == 2) {
    local_34 = (short *)(param_2[0x15] + -1);
    psVar3 = param_2;
    if (0x31 < (int)local_34) {
      local_34 = (short *)0x31;
    }
  }
  else {
    psVar3 = extraout_EDX;
    if ((iVar1 == 3) &&
       (psVar3 = (short *)(param_2[0x16] + -1), local_34 = psVar3, 0x31 < (int)psVar3)) {
      local_34 = (short *)0x31;
    }
  }
  uVar4 = (undefined2)((uint)psVar3 >> 0x10);
  if ((local_3c & 0xffff) == 0) {
    if ((5 < iVar1) && (iVar1 < 0x22)) {
      FUN_00472ca0(local_2c,s_F_02d_0049ad8c,iVar1 + -6);
      puVar7 = local_2c;
      iVar1 = param_1;
      iVar5 = local_30;
      iVar6 = local_38;
      thunk_FUN_0042de03(param_1,local_30,local_38,puVar7);
      thunk_FUN_004289c0(iVar1,iVar5,iVar6,puVar7);
      uVar4 = extraout_var;
    }
  }
  else {
    psVar3 = local_34;
    iVar1 = local_30;
    iVar5 = local_38;
    uVar2 = thunk_FUN_0040e864(local_3c & 0xffff);
    thunk_FUN_00404770(param_1,uVar2,psVar3,iVar1,iVar5);
    uVar4 = extraout_var_00;
  }
  if ((*(uint *)(param_2 + 0xe) & 0x200) != 0) {
    uVar2 = thunk_FUN_0040e864(CONCAT22(uVar4,DAT_0049acb8));
    thunk_FUN_00404770(param_1,uVar2,0x15,local_30,local_38);
  }
  return;
}
```

---


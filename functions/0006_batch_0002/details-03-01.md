# 0006_batch_0002 — détails (1/2)

## FUN_004082a7 — 0x4082a7

- Classification : internal
- Corps : `0x4082a7–0x408439`
- État : pseudocode obtenu
- Evidence : `ev_cc26e8ce8ba112cedb98cdb34d12e113b67a8f362a0ad4fedcb8e5f07af1a55c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004082a7(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  byte *pbVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint *puVar16;
  bool bVar17;
  uint local_c;
  uint local_8;
  
  piVar1 = (int *)*param_1;
  iVar10 = piVar1[1];
  iVar5 = iVar10 + 1;
  if ((iVar5 == 0 || iVar10 < -1) || (iVar9 = piVar1[2], iVar9 < 0)) {
    return -1;
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
  if (iVar10 <= param_1[3]) {
    iVar8 = iVar10;
  }
  iVar10 = param_1[4];
  if (iVar9 <= param_1[4]) {
    iVar10 = iVar9;
  }
  if ((iVar8 < iVar6) || (iVar10 < iVar7)) {
    return -2;
  }
  param_2 = param_2 + iVar2;
  param_3 = param_3 + iVar3;
  uVar15 = *(uint *)(param_4 + 8);
  puVar16 = (uint *)(*(int *)(param_5 * 4 + param_4 + 0x10) + param_4);
  local_c = 0;
  local_8 = *puVar16;
  if (local_8 != 0) {
    puVar16 = puVar16 + 1;
    iVar9 = ((iVar8 + 1) - local_8) - param_2;
    uVar12 = local_8;
    if ((-1 < iVar9) ||
       (uVar12 = local_8 + iVar9, uVar12 != 0 && SCARRY4(local_8,iVar9) == (int)uVar12 < 0)) {
      iVar6 = param_2 - iVar6;
      if (iVar6 < 0) {
        bVar17 = SCARRY4(uVar12,iVar6);
        uVar12 = uVar12 + iVar6;
        if (uVar12 == 0 || bVar17 != (int)uVar12 < 0) goto LAB_0040842e;
        puVar16 = (uint *)((int)puVar16 - iVar6);
        param_2 = param_2 - iVar6;
      }
      iVar10 = ((iVar10 + 1) - uVar15) - param_3;
      if ((-1 < iVar10) ||
         (bVar17 = SCARRY4(uVar15,iVar10), uVar15 = uVar15 + iVar10,
         uVar15 != 0 && bVar17 == (int)uVar15 < 0)) {
        iVar7 = param_3 - iVar7;
        if (iVar7 < 0) {
          bVar17 = SCARRY4(uVar15,iVar7);
          uVar15 = uVar15 + iVar7;
          if (uVar15 == 0 || bVar17 != (int)uVar15 < 0) goto LAB_0040842e;
          param_3 = param_3 - iVar7;
          puVar16 = (uint *)((int)puVar16 - iVar7 * local_8);
        }
        pbVar11 = (byte *)(param_3 * iVar5 + *piVar1 + param_2);
        local_8 = local_8 - uVar12;
        uVar13 = uVar12;
        if (param_6 == 0) {
          do {
            for (uVar13 = uVar12 >> 1; uVar13 != 0; uVar13 = uVar13 - 1) {
              *(short *)pbVar11 = (short)*puVar16;
              puVar16 = (uint *)((int)puVar16 + 2);
              pbVar11 = pbVar11 + 2;
            }
            for (uVar13 = (uint)((uVar12 & 1) != 0); uVar13 != 0; uVar13 = uVar13 - 1) {
              *pbVar11 = (byte)*puVar16;
              puVar16 = (uint *)((int)puVar16 + 1);
              pbVar11 = pbVar11 + 1;
            }
            puVar16 = (uint *)((int)puVar16 + local_8);
            pbVar11 = pbVar11 + (iVar5 - uVar12);
            uVar15 = uVar15 - 1;
          } while (uVar15 != 0);
          return local_8 + uVar12;
        }
        while (uVar14 = uVar12, local_c = uVar12, uVar13 != 0) {
          do {
            bVar4 = *(byte *)(param_6 + (uint)(byte)*puVar16);
            if (bVar4 != 0xff) {
              *pbVar11 = bVar4;
            }
            puVar16 = (uint *)((int)puVar16 + 1);
            pbVar11 = pbVar11 + 1;
            uVar14 = uVar14 - 1;
          } while (uVar14 != 0);
          puVar16 = (uint *)((int)puVar16 + local_8);
          pbVar11 = pbVar11 + (iVar5 - uVar12);
          uVar15 = uVar15 - 1;
          uVar13 = uVar15;
        }
      }
    }
  }
LAB_0040842e:
  return local_8 + local_c;
}
```

---

---

## FUN_0040843a — 0x40843a

- Classification : internal
- Corps : `0x40843a–0x408470`
- État : pseudocode obtenu
- Evidence : `ev_aa1b6995c397a10358ec44006578231100eb00daf1cf6678b2f81386204c8509`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4082a7` — `FUN_004082a7`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040843a(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,char *param_5
                 ,undefined4 param_6)

{
  int iVar1;
  
  do {
    iVar1 = FUN_004082a7(param_1,param_2,param_3,param_4,*param_5,param_6);
    param_2 = param_2 + iVar1;
    param_5 = param_5 + 1;
  } while (*param_5 != '\0');
  return;
}
```

---

---

## FUN_00408471 — 0x408471

- Classification : internal
- Corps : `0x408471–0x408573`
- État : pseudocode obtenu
- Evidence : `ev_da6beade665cf4384098a1f75ca8d6d47f699f95b1a3862f591f75c227bfd145`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Type propagation algorithm not settling */

undefined4 * FUN_00408471(int *param_1,int param_2,undefined4 *param_3,undefined1 *param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined4 *puVar11;
  bool bVar12;
  int local_8;
  
  piVar1 = (int *)*param_1;
  iVar2 = piVar1[1];
  if ((iVar2 + 1 == 0 || iVar2 < -1) || (iVar3 = piVar1[2], iVar3 < 0)) {
    return (undefined4 *)0xffffffff;
  }
  local_8 = param_1[1];
  iVar5 = local_8;
  if (local_8 < 1) {
    iVar5 = 0;
  }
  iVar4 = param_1[2];
  iVar6 = iVar4;
  if (iVar4 < 1) {
    iVar6 = 0;
  }
  iVar7 = param_1[3];
  if (iVar2 <= param_1[3]) {
    iVar7 = iVar2;
  }
  iVar8 = param_1[4];
  if (iVar3 <= param_1[4]) {
    iVar8 = iVar3;
  }
  if ((iVar5 <= iVar7) && (iVar6 <= iVar8)) {
    param_2 = param_2 + iVar4;
    puVar9 = (undefined4 *)(((iVar7 - local_8) + 1) - (int)param_4);
    if ((-1 < (int)puVar9) ||
       (bVar12 = SCARRY4((int)param_4,(int)puVar9), param_4 = param_4 + (int)puVar9,
       param_4 != (undefined1 *)0x0 && bVar12 == (int)param_4 < 0)) {
      puVar9 = (undefined4 *)(local_8 - iVar5);
      if ((int)puVar9 < 0) {
        bVar12 = SCARRY4((int)param_4,(int)puVar9);
        param_4 = param_4 + (int)puVar9;
        if (param_4 == (undefined1 *)0x0 || bVar12 != (int)param_4 < 0) {
          return puVar9;
        }
        param_3 = (undefined4 *)((int)param_3 - (int)puVar9);
        local_8 = local_8 - (int)puVar9;
      }
      puVar9 = (undefined4 *)(iVar8 - param_2);
      if ((-1 < (int)puVar9) && (puVar9 = (undefined4 *)(param_2 - iVar6), -1 < (int)puVar9)) {
        puVar9 = (undefined4 *)(param_2 * (iVar2 + 1) + *piVar1 + local_8);
        puVar11 = puVar9;
        for (uVar10 = (uint)param_4 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
          *(undefined1 *)puVar11 = *(undefined1 *)param_3;
          param_3 = (undefined4 *)((int)param_3 + 1);
          puVar11 = (undefined4 *)((int)puVar11 + 1);
        }
        for (uVar10 = (uint)param_4 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
          *puVar11 = *param_3;
          param_3 = param_3 + 1;
          puVar11 = puVar11 + 1;
        }
      }
    }
    return puVar9;
  }
  return (undefined4 *)0xfffffffe;
}
```

---

---

## FUN_00408580 — 0x408580

- Classification : internal
- Corps : `0x408580–0x4085c1`
- État : pseudocode obtenu
- Evidence : `ev_530128e17854c4082282398a1c9d40ab0be067501e35c630292c23c5b68e99bb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
short * FUN_00408580(short *param_1,int param_2)

{
  int iVar1;
  short *psVar2;
  short *psVar3;
  short *psVar4;
  bool bVar5;
  
  psVar2 = (short *)(param_2 + 0xc);
  do {
    for (; (char)*psVar2 == '\0'; psVar2 = (short *)((int)psVar2 + 1)) {
    }
    iVar1 = 2;
    bVar5 = false;
    psVar3 = psVar2;
    psVar4 = param_1;
    do {
      if (iVar1 == 0) break;
      iVar1 = iVar1 + -1;
      bVar5 = *psVar3 == *psVar4;
      psVar3 = psVar3 + 1;
      psVar4 = psVar4 + 1;
    } while (bVar5);
    if (bVar5) {
      return psVar2 + 4;
    }
    psVar2 = (short *)((int)psVar2 + CONCAT11((char)psVar2[3],(char)((ushort)psVar2[3] >> 8)) + 8);
  } while( true );
}
```

---

---

## FUN_004085c2 — 0x4085c2

- Classification : internal
- Corps : `0x4085c2–0x408788`
- État : pseudocode obtenu
- Evidence : `ev_6a85f5ec383ccc891e7e34ac8c71fff409822fde2f94617b6c859e2d8233a1db`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x408471` — `FUN_00408471`
- `0x408580` — `FUN_00408580`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_004085c2(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  ushort uVar3;
  ushort uVar4;
  undefined2 uVar5;
  char cVar11;
  uint uVar6;
  uint uVar7;
  ushort *puVar8;
  uint uVar9;
  int iVar10;
  byte bVar12;
  byte bVar13;
  int iVar14;
  int iVar15;
  byte *pbVar16;
  byte *pbVar17;
  undefined1 *puVar18;
  undefined1 *puVar19;
  uint local_3c;
  int local_2c;
  int local_1c;
  uint local_18;
  byte *local_14;
  uint local_c;
  
  uVar6 = (*(int *)(param_1 + 0xc) - *(int *)(param_1 + 4)) + 1;
  uVar7 = (*(int *)(param_1 + 0x10) - *(int *)(param_1 + 8)) + 1;
  local_2c = 0;
  iVar2 = *(int *)(param_2 + 8);
  puVar8 = (ushort *)FUN_00408580(&DAT_00408574,param_2);
  uVar1 = *puVar8;
  uVar3 = CONCAT11((char)uVar1,(char)(uVar1 >> 8));
  uVar9 = (uint)uVar3;
  local_c = (uint)CONCAT11((char)puVar8[1],(char)(puVar8[1] >> 8));
  if ((int)uVar7 <= (int)local_c) {
    local_c = uVar7;
  }
  if (*(char *)((int)puVar8 + 9) != '\x01') {
    uVar4 = puVar8[5];
    local_3c = (uint)*(byte *)((int)puVar8 + 0xd);
    uVar7 = ((uVar3 >> 3) + 1) - (uint)((uVar1 & 0x700) == 0);
    iVar14 = uVar7 + (uVar7 & 1);
    iVar10 = (uVar9 & 1) + uVar9;
    if ((int)uVar6 <= (int)uVar9) {
      uVar9 = uVar6;
    }
    local_14 = (byte *)FUN_00408580(&DAT_0040857c,param_2);
    do {
      if ((char)uVar4 == '\x01') {
        pbVar17 = &DAT_00499ff9;
        while (pbVar16 = local_14, pbVar17 < &DAT_00499ff9 + iVar10) {
          local_14 = pbVar16 + 1;
          uVar6 = (uint)*pbVar16;
          if (uVar6 != 0x80) {
            if (uVar6 < 0x81) {
              for (uVar7 = uVar6 + 1 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
                *pbVar17 = *local_14;
                local_14 = local_14 + 1;
                pbVar17 = pbVar17 + 1;
              }
              for (uVar6 = uVar6 + 1 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
                *(undefined4 *)pbVar17 = *(undefined4 *)local_14;
                local_14 = local_14 + 4;
                pbVar17 = pbVar17 + 4;
              }
            }
            else {
              bVar13 = *local_14;
              bVar12 = 1 - *pbVar16;
              for (uVar6 = bVar12 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
                *pbVar17 = bVar13;
                pbVar17 = pbVar17 + 1;
              }
              for (uVar6 = (uint)(bVar12 >> 2); local_14 = pbVar16 + 2, uVar6 != 0;
                  uVar6 = uVar6 - 1) {
                *(uint *)pbVar17 = CONCAT22(CONCAT11(bVar13,bVar13),CONCAT11(bVar13,bVar13));
                pbVar17 = pbVar17 + 4;
              }
            }
          }
        }
        pbVar17 = &DAT_00499ff9;
        local_14 = pbVar16;
      }
      else {
        pbVar17 = local_14;
        local_14 = local_14 + iVar10;
      }
      if (iVar2 == 0x4d424c49) {
        puVar18 = &DAT_004992f9;
        local_1c = iVar14;
        local_18 = uVar9;
        do {
          bVar13 = 0x80;
          puVar19 = puVar18;
          do {
            iVar15 = 0;
            uVar6 = 0x100;
            do {
              uVar5 = (undefined2)uVar6;
              if ((pbVar17[iVar15] & bVar13) != 0) {
                uVar5 = (undefined2)CONCAT31((int3)(uVar6 >> 8),(byte)uVar6 | (byte)(uVar6 >> 8));
              }
              iVar15 = iVar15 + iVar14;
              cVar11 = (char)((ushort)uVar5 >> 8) << 1;
              uVar6 = (uint)CONCAT11(cVar11,(char)uVar5);
            } while (cVar11 != '\0');
            puVar18 = puVar19 + 1;
            *puVar19 = (char)uVar5;
            local_18 = local_18 - 1;
            if (local_18 == 0) goto LAB_0040874a;
            bVar13 = bVar13 >> 1;
            puVar19 = puVar18;
          } while (bVar13 != 0);
          pbVar17 = pbVar17 + 1;
          local_1c = local_1c + -1;
        } while (local_1c != 0);
LAB_0040874a:
        FUN_00408471(param_1,local_2c,&DAT_004992f9,uVar9);
      }
      else {
        FUN_00408471(param_1,local_2c,pbVar17,uVar9);
      }
      local_2c = local_2c + 1;
      local_c = local_c - 1;
    } while (local_c != 0);
  }
  return local_3c;
}
```

---

---

## FUN_00408789 — 0x408789

- Classification : internal
- Corps : `0x408789–0x4087b9`
- État : pseudocode obtenu
- Evidence : `ev_36f14c10f9d88931ffd7ec0cf71276da09be4b2f76ad75594427262a23690ee1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x408580` — `FUN_00408580`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00408789(undefined4 param_1,byte *param_2)

{
  byte *pbVar1;
  int iVar2;
  
  pbVar1 = (byte *)FUN_00408580(&DAT_00408578,param_1);
  iVar2 = 0x300;
  do {
    *param_2 = *pbVar1 >> 2;
    iVar2 = iVar2 + -1;
    pbVar1 = pbVar1 + 1;
    param_2 = param_2 + 1;
  } while (iVar2 != 0);
  return;
}
```

---

---

## FUN_004087ba — 0x4087ba

- Classification : internal
- Corps : `0x4087ba–0x4087e6`
- État : pseudocode obtenu
- Evidence : `ev_27f1841915decefc83cac1a55d00a045e2aa0384fc1df6b47e7b76b4c58e54cb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x408580` — `FUN_00408580`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004087ba(undefined4 param_1)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)FUN_00408580(&DAT_00408574,param_1);
  return CONCAT31(CONCAT21(CONCAT11((char)*puVar1,(char)((ushort)*puVar1 >> 8)),(char)puVar1[1]),
                  (char)((ushort)puVar1[1] >> 8));
}
```

---

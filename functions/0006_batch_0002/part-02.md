# 0006_batch_0002 — détails (2/3)

## FUN_0040629e — 0x40629e

- Classification : internal
- Corps : `0x40629e–0x406426`
- État : pseudocode obtenu
- Evidence : `ev_0f97f4123ae400e79bc10792052a277ead29a910c2578cdddbcfc15ac632ac13`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x406427` — `FUN_00406427`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040629e(int param_1,char param_2,undefined4 param_3)

{
  char extraout_AH;
  char extraout_AH_00;
  char extraout_AH_01;
  char extraout_AH_02;
  char cVar1;
  char extraout_AH_03;
  char cVar2;
  char extraout_AH_04;
  int extraout_ECX;
  int iVar3;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  int extraout_ECX_04;
  char *pcVar4;
  char *pcVar5;
  bool bVar6;
  undefined4 local_8;
  
  pcVar4 = DAT_00498dc9;
  DAT_00498dcd = DAT_00498dc9;
  FUN_00406427(0,0,param_3);
  local_8 = 5;
  if (param_1 == 0) {
LAB_004063fc:
    DAT_00498dcd = pcVar4;
    FUN_00406427(local_8,0,param_3);
    FUN_00406427(4,0,param_3);
    return;
  }
  cVar2 = *pcVar4;
  pcVar4 = pcVar4 + 1;
  param_1 = param_1 + -1;
  do {
    if (cVar2 == param_2) goto LAB_004063cd;
    while( true ) {
      local_8 = 1;
      if (param_1 == 0) goto LAB_004063fc;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      param_1 = param_1 + -1;
      if (cVar1 == cVar2) break;
      if (cVar1 == param_2) {
        DAT_00498dcd = pcVar4;
        FUN_00406427(1,1,param_3);
        cVar2 = extraout_AH;
        param_1 = extraout_ECX;
      }
      else {
        while( true ) {
          pcVar5 = pcVar4;
          iVar3 = param_1;
          pcVar4 = pcVar5;
          if (iVar3 == 0) goto LAB_004063fc;
          cVar2 = *pcVar5;
          pcVar4 = pcVar5 + 1;
          if (cVar2 == param_2) break;
          bVar6 = cVar2 == cVar1;
          cVar1 = cVar2;
          param_1 = iVar3 + -1;
          if (bVar6) {
            if (iVar3 + -1 == 0) goto LAB_004063fc;
            cVar1 = *pcVar4;
            pcVar4 = pcVar5 + 2;
            DAT_00498dcd = pcVar4;
            if (cVar1 == param_2) {
              FUN_00406427(1,1,param_3);
              cVar2 = extraout_AH_01;
              param_1 = extraout_ECX_01;
              goto LAB_004063cd;
            }
            param_1 = iVar3 + -2;
            if (cVar1 == cVar2) {
              FUN_00406427(1,3,param_3);
              cVar1 = extraout_AH_02;
              param_1 = extraout_ECX_02;
              goto LAB_0040639a;
            }
          }
        }
        DAT_00498dcd = pcVar4;
        FUN_00406427(1,1,param_3);
        cVar2 = extraout_AH_00;
        param_1 = extraout_ECX_00;
      }
LAB_004063cd:
      do {
        local_8 = 3;
        if (param_1 == 0) goto LAB_004063fc;
        cVar1 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        param_1 = param_1 + -1;
      } while (cVar1 == cVar2);
      DAT_00498dcd = pcVar4;
      FUN_00406427(3,1,param_3);
      cVar2 = extraout_AH_04;
      param_1 = extraout_ECX_04;
    }
LAB_0040639a:
    do {
      local_8 = 2;
      if (param_1 == 0) goto LAB_004063fc;
      cVar2 = *pcVar4;
      pcVar4 = pcVar4 + 1;
      param_1 = param_1 + -1;
    } while (cVar2 == cVar1);
    DAT_00498dcd = pcVar4;
    FUN_00406427(2,1,param_3);
    cVar2 = extraout_AH_03;
    param_1 = extraout_ECX_03;
  } while( true );
}
```

---

## FUN_00406427 — 0x406427

- Classification : internal
- Corps : `0x406427–0x406603`
- État : pseudocode obtenu
- Evidence : `ev_8c6257b764fcbbfaeb574152f30562cb6563c3c78cb36fe89da34122d6bcefc3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00406427(int param_1,int param_2,int param_3)

{
  undefined4 in_EAX;
  char *pcVar1;
  char *pcVar2;
  char *pcVar3;
  
  if (param_1 == 2) {
    if (DAT_00498dc5 != (char *)0x0) {
      do {
        pcVar1 = DAT_00498dc5;
        if (0xfe < (int)DAT_00498dc5) {
          pcVar1 = (char *)0xff;
        }
        DAT_00498dc5 = DAT_00498dc5 + -(int)pcVar1;
        if (DAT_00498dc1 != 0) {
          *DAT_00498dd1 = '\x01';
          DAT_00498dd1[1] = (char)pcVar1;
        }
        DAT_00498dd1 = DAT_00498dd1 + 2;
        DAT_00498dd5 = DAT_00498dd5 + (int)pcVar1;
      } while (DAT_00498dc5 != (char *)0x0);
      DAT_00498dc5 = (char *)0x0;
    }
    pcVar3 = DAT_00498dcd + (-param_2 - (int)DAT_00498dd5);
    pcVar1 = DAT_00498dd5 + (param_3 - DAT_00498dc9);
    if ((int)pcVar1 < (int)DAT_00498de9) {
      DAT_00498de9 = pcVar1;
    }
    pcVar2 = pcVar1 + (int)pcVar3 + -1;
    if ((int)(pcVar1 + (int)pcVar3 + -1) <= (int)DAT_00498df1) goto LAB_004064f7;
    for (; DAT_00498df1 = pcVar2, pcVar3 != (char *)0x0; pcVar3 = pcVar3 + -(int)pcVar1) {
LAB_004064f7:
      pcVar1 = pcVar3;
      if (0x7e < (int)pcVar3) {
        pcVar1 = (char *)0x7f;
      }
      if (DAT_00498dc1 != 0) {
        *DAT_00498dd1 = (char)pcVar1 * '\x02';
        DAT_00498dd1[1] = *DAT_00498dd5;
      }
      DAT_00498dd1 = DAT_00498dd1 + 2;
      DAT_00498dd5 = DAT_00498dd5 + (int)pcVar1;
      pcVar2 = DAT_00498df1;
    }
  }
  else if (param_1 == 1) {
    if (DAT_00498dc5 != (char *)0x0) {
      do {
        pcVar1 = DAT_00498dc5;
        if (0xfe < (int)DAT_00498dc5) {
          pcVar1 = (char *)0xff;
        }
        DAT_00498dc5 = DAT_00498dc5 + -(int)pcVar1;
        if (DAT_00498dc1 != 0) {
          *DAT_00498dd1 = '\x01';
          DAT_00498dd1[1] = (char)pcVar1;
        }
        DAT_00498dd1 = DAT_00498dd1 + 2;
        DAT_00498dd5 = DAT_00498dd5 + (int)pcVar1;
      } while (DAT_00498dc5 != (char *)0x0);
      DAT_00498dc5 = (char *)0x0;
    }
    pcVar3 = DAT_00498dcd + (-param_2 - (int)DAT_00498dd5);
    pcVar1 = DAT_00498dd5 + (param_3 - DAT_00498dc9);
    if ((int)pcVar1 < (int)DAT_00498de9) {
      DAT_00498de9 = pcVar1;
    }
    pcVar2 = pcVar1 + (int)pcVar3 + -1;
    if ((int)(pcVar1 + (int)pcVar3 + -1) <= (int)DAT_00498df1) goto LAB_0040659e;
    for (; DAT_00498df1 = pcVar2, pcVar3 != (char *)0x0; pcVar3 = pcVar3 + -(int)pcVar1) {
LAB_0040659e:
      pcVar1 = pcVar3;
      if (0x7e < (int)pcVar3) {
        pcVar1 = (char *)0x7f;
      }
      if (DAT_00498dc1 == 0) {
        DAT_00498dd5 = DAT_00498dd5 + (int)pcVar1;
        DAT_00498dd1 = DAT_00498dd1 + (int)(pcVar1 + 1);
      }
      else {
        *DAT_00498dd1 = (char)pcVar1 * '\x02' + '\x01';
        for (pcVar2 = pcVar1; DAT_00498dd1 = DAT_00498dd1 + 1, pcVar2 != (char *)0x0;
            pcVar2 = pcVar2 + -1) {
          *DAT_00498dd1 = *DAT_00498dd5;
          DAT_00498dd5 = DAT_00498dd5 + 1;
        }
      }
      pcVar2 = DAT_00498df1;
    }
  }
  else if (param_1 == 3) {
    DAT_00498dc5 = DAT_00498dcd + (-param_2 - (int)DAT_00498dd5);
  }
  else if (param_1 == 4) {
    if (DAT_00498dc1 != 0) {
      *DAT_00498dd1 = '\0';
    }
    DAT_00498dd1 = DAT_00498dd1 + 1;
  }
  else if (param_1 == 0) {
    DAT_00498dc5 = (char *)0x0;
    DAT_00498dd5 = DAT_00498dcd;
  }
  return in_EAX;
}
```

---

## FUN_00406604 — 0x406604

- Classification : internal
- Corps : `0x406604–0x4066e2`
- État : pseudocode obtenu
- Evidence : `ev_8b38f05f1b91fb03de8e44226bb5a45050266a6e226a4a57752b095fd1916cd2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00406604(int *param_1,undefined1 param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  uint uVar9;
  uint uVar10;
  
  piVar1 = (int *)*param_1;
  iVar7 = piVar1[1];
  iVar3 = iVar7 + 1;
  if ((iVar3 == 0 || iVar7 < -1) || (iVar2 = piVar1[2], iVar2 < 0)) {
    return 0xffffffff;
  }
  iVar4 = param_1[1];
  if (iVar4 < 1) {
    iVar4 = 0;
  }
  iVar5 = param_1[2];
  if (iVar5 < 1) {
    iVar5 = 0;
  }
  iVar6 = param_1[3];
  if (iVar7 <= param_1[3]) {
    iVar6 = iVar7;
  }
  iVar7 = param_1[4];
  if (iVar2 <= param_1[4]) {
    iVar7 = iVar2;
  }
  if ((iVar4 <= iVar6) && (iVar5 <= iVar7)) {
    puVar8 = (undefined4 *)(iVar5 * iVar3 + *piVar1 + iVar4);
    uVar10 = (iVar6 + 1) - iVar4;
    for (; iVar5 <= iVar7; iVar5 = iVar5 + 1) {
      for (uVar9 = uVar10 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(undefined1 *)puVar8 = param_2;
        puVar8 = (undefined4 *)((int)puVar8 + 1);
      }
      for (uVar9 = uVar10 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
        *puVar8 = CONCAT22(CONCAT11(param_2,param_2),CONCAT11(param_2,param_2));
        puVar8 = puVar8 + 1;
      }
      puVar8 = (undefined4 *)((int)puVar8 + (iVar3 - uVar10));
    }
    return 0;
  }
  return 0xfffffffe;
}
```

---

## FUN_004066e3 — 0x4066e3

- Classification : internal
- Corps : `0x4066e3–0x406a7e`
- État : pseudocode obtenu
- Evidence : `ev_76c459dcab1381bbee6cfd4eda424e875be67fe8fdd611fc43451ef581334d75`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4
FUN_004066e3(int *param_1,int param_2,int param_3,int *param_4,int param_5,int param_6,uint param_7)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  undefined1 uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  uint uVar22;
  int iVar23;
  uint uVar24;
  undefined1 *puVar25;
  undefined4 *puVar26;
  undefined1 *puVar27;
  undefined4 *puVar28;
  int local_60;
  int local_54;
  int local_40;
  
  piVar1 = (int *)*param_1;
  iVar23 = piVar1[1];
  iVar9 = iVar23 + 1;
  if ((iVar9 == 0 || iVar23 < -1) || (iVar21 = piVar1[2], iVar21 < 0)) {
    return 0xffffffff;
  }
  iVar2 = param_1[1];
  iVar10 = iVar2;
  if (iVar2 < 1) {
    iVar10 = 0;
  }
  iVar3 = param_1[2];
  iVar11 = iVar3;
  if (iVar3 < 1) {
    iVar11 = 0;
  }
  iVar12 = param_1[3];
  if (iVar23 <= param_1[3]) {
    iVar12 = iVar23;
  }
  iVar23 = param_1[4];
  if (iVar21 <= param_1[4]) {
    iVar23 = iVar21;
  }
  if ((iVar12 < iVar10) || (iVar23 < iVar11)) {
    return 0xfffffffe;
  }
  iVar10 = iVar10 - iVar2;
  iVar12 = iVar12 - iVar2;
  iVar11 = iVar11 - iVar3;
  iVar23 = iVar23 - iVar3;
  piVar4 = (int *)*param_4;
  iVar21 = piVar4[1];
  iVar13 = iVar21 + 1;
  if ((iVar13 == 0 || iVar21 < -1) || (iVar16 = piVar4[2], iVar16 < 0)) {
    return 0xffffffff;
  }
  iVar5 = param_4[1];
  iVar14 = iVar5;
  if (iVar5 < 1) {
    iVar14 = 0;
  }
  iVar6 = param_4[2];
  iVar15 = iVar6;
  if (iVar6 < 1) {
    iVar15 = 0;
  }
  iVar20 = param_4[3];
  if (iVar21 <= param_4[3]) {
    iVar20 = iVar21;
  }
  iVar21 = param_4[4];
  if (iVar16 <= param_4[4]) {
    iVar21 = iVar16;
  }
  if ((iVar14 <= iVar20) && (iVar15 <= iVar21)) {
    iVar14 = iVar14 - iVar5;
    iVar20 = iVar20 - iVar5;
    iVar15 = iVar15 - iVar6;
    iVar21 = iVar21 - iVar6;
    param_2 = param_2 - param_5;
    param_3 = param_3 - param_6;
    iVar16 = iVar10;
    if (iVar10 <= iVar14 + param_2) {
      iVar16 = iVar14 + param_2;
    }
    iVar17 = iVar11;
    if (iVar11 <= iVar15 + param_3) {
      iVar17 = iVar15 + param_3;
    }
    iVar18 = iVar12;
    if (iVar20 + param_2 <= iVar12) {
      iVar18 = iVar20 + param_2;
    }
    iVar19 = iVar23;
    if (iVar21 + param_3 <= iVar23) {
      iVar19 = iVar21 + param_3;
    }
    if ((iVar16 <= iVar18) && (iVar17 <= iVar19)) {
      if (iVar14 <= iVar10 - param_2) {
        iVar14 = iVar10 - param_2;
      }
      if (iVar15 <= iVar11 - param_3) {
        iVar15 = iVar11 - param_3;
      }
      if (iVar12 - param_2 <= iVar20) {
        iVar20 = iVar12 - param_2;
      }
      if (iVar23 - param_3 <= iVar21) {
        iVar21 = iVar23 - param_3;
      }
      uVar22 = (iVar18 + 1) - iVar16;
      iVar23 = (iVar19 + 1) - iVar17;
      local_54 = iVar13;
      local_40 = iVar9;
      if (iVar17 <= iVar15) {
        local_54 = -iVar13;
        local_40 = -iVar9;
        iVar17 = iVar19;
        iVar15 = iVar21;
      }
      bVar7 = iVar16 <= iVar14;
      if (bVar7) {
        local_60 = 3;
        uVar24 = uVar22;
      }
      else {
        local_60 = 0;
        iVar18 = iVar16;
        iVar20 = iVar14;
        uVar24 = -uVar22;
      }
      local_40 = local_40 + uVar24;
      local_54 = local_54 + uVar24;
      puVar27 = (undefined1 *)(iVar6 * iVar13 + *piVar4 + iVar5 + iVar15 * iVar13 + iVar20);
      puVar25 = (undefined1 *)(iVar3 * iVar9 + *piVar1 + iVar2 + iVar17 * iVar9 + iVar18);
      if ((param_7 & 0xffffff00) == 0) {
        uVar8 = (undefined1)param_7;
        do {
          for (uVar24 = uVar22 & 3; uVar24 != 0; uVar24 = uVar24 - 1) {
            *puVar27 = uVar8;
            puVar27 = puVar27 + (uint)bVar7 * -2 + 1;
          }
          puVar26 = (undefined4 *)(puVar27 + -local_60);
          for (uVar24 = uVar22 >> 2; uVar24 != 0; uVar24 = uVar24 - 1) {
            *puVar26 = CONCAT22(CONCAT11(uVar8,uVar8),CONCAT11(uVar8,uVar8));
            puVar26 = puVar26 + (uint)bVar7 * -2 + 1;
          }
          puVar27 = (undefined1 *)((int)puVar26 + local_54 + local_60);
          iVar23 = iVar23 + -1;
        } while (iVar23 != 0);
      }
      else {
        do {
          for (uVar24 = uVar22 & 3; uVar24 != 0; uVar24 = uVar24 - 1) {
            *puVar27 = *puVar25;
            puVar25 = puVar25 + (uint)bVar7 * -2 + 1;
            puVar27 = puVar27 + (uint)bVar7 * -2 + 1;
          }
          puVar26 = (undefined4 *)(puVar25 + -local_60);
          puVar28 = (undefined4 *)(puVar27 + -local_60);
          for (uVar24 = uVar22 >> 2; uVar24 != 0; uVar24 = uVar24 - 1) {
            *puVar28 = *puVar26;
            puVar26 = puVar26 + (uint)bVar7 * -2 + 1;
            puVar28 = puVar28 + (uint)bVar7 * -2 + 1;
          }
          puVar25 = (undefined1 *)((int)puVar26 + local_40 + local_60);
          puVar27 = (undefined1 *)((int)puVar28 + local_54 + local_60);
          iVar23 = iVar23 + -1;
        } while (iVar23 != 0);
      }
      return 0;
    }
    return 0xfffffffd;
  }
  return 0xfffffffe;
}
```

---

## FUN_00406a7f — 0x406a7f

- Classification : internal
- Corps : `0x406a7f–0x406c7b`
- État : pseudocode obtenu
- Evidence : `ev_c44a8535f17b551eac9d4c053c8aafe61f3171aaf5f1331a7f21ef87b203f2de`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x406604` — `FUN_00406604`
- `0x4066e3` — `FUN_004066e3`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00406a7f(int **param_1,uint param_2,uint param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  int local_48;
  undefined4 **local_30;
  int *local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  iVar1 = ((int)param_1[3] + 1) - (int)param_1[1];
  if (iVar1 != 0 && (int)param_1[1] <= (int)param_1[3] + 1) {
    iVar3 = ((int)param_1[4] + 1) - (int)param_1[2];
    if (iVar3 != 0 && (int)param_1[2] <= (int)param_1[4] + 1) {
      iVar2 = -iVar1;
      iVar4 = -iVar3;
      uVar6 = SUB42(param_1,0);
      if (param_4 == 1) {
        if (param_5 == 0) {
          return iVar1 * iVar3;
        }
        local_30 = &local_2c;
        local_18 = param_5;
        local_2c = &local_18;
        local_28 = 0;
        local_24 = 0;
        local_20 = iVar1 + -1;
        local_1c = iVar3 + -1;
        local_14 = local_20;
        local_10 = local_1c;
        FUN_004066e3(param_1,0,0,(short)local_30,0,0,0xffffffff);
        param_2 = (int)param_2 % iVar1;
        param_3 = (int)param_3 % iVar3;
        local_48 = -1;
      }
      else {
        if ((iVar1 <= (int)((param_2 ^ (int)param_2 >> 0x1f) - ((int)param_2 >> 0x1f))) ||
           (iVar3 <= (int)((param_3 ^ (int)param_3 >> 0x1f) - ((int)param_3 >> 0x1f)))) {
          iVar1 = FUN_00406604(uVar6,(ushort)param_5 & 0xff);
          return iVar1;
        }
        local_30 = param_1;
        local_48 = param_5;
      }
      if (param_2 != 0 || param_3 != 0) {
        uVar7 = (undefined2)param_3;
        uVar5 = (undefined2)param_2;
        FUN_004066e3(local_30,0,0,uVar6,uVar5,uVar7,0xffffffff);
        FUN_004066e3(local_30,iVar1,iVar3,uVar6,uVar5,uVar7,local_48);
        FUN_004066e3(local_30,iVar1,0,uVar6,uVar5,uVar7,local_48);
        FUN_004066e3(local_30,iVar1,iVar4,uVar6,uVar5,uVar7,local_48);
        FUN_004066e3(local_30,0,iVar3,uVar6,uVar5,uVar7,local_48);
        FUN_004066e3(local_30,0,iVar4,uVar6,uVar5,uVar7,local_48);
        FUN_004066e3(local_30,iVar2,iVar3,uVar6,uVar5,uVar7,local_48);
        FUN_004066e3(local_30,iVar2,0,uVar6,uVar5,uVar7,local_48);
        FUN_004066e3(local_30,iVar2,iVar4,uVar6,uVar5,uVar7,local_48);
      }
      return 0;
    }
  }
  return -2;
}
```

---

## FUN_00406c7c — 0x406c7c

- Classification : internal
- Corps : `0x406c7c–0x406fbc`
- État : pseudocode obtenu
- Evidence : `ev_ee6d3e457b578bc52d6625d7cf42a3472c15947904d6933fee8a5ced3de23561`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x403c35` — `FUN_00403c35`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00406c7c(int *param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined1 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int local_30;
  int local_2c;
  int local_28;
  int local_14;
  int local_10;
  
  if ((param_4 == 0) || (param_5 == 0)) {
    iVar6 = FUN_00403c35(param_1,param_2 - param_4,param_3 - param_5,param_2 + param_4,
                         param_3 + param_5,0,param_6);
  }
  else {
    piVar1 = (int *)*param_1;
    iVar6 = piVar1[1];
    iVar7 = iVar6 + 1;
    if ((iVar7 == 0 || iVar6 < -1) || (iVar2 = piVar1[2], iVar2 < 0)) {
      return -1;
    }
    iVar3 = param_1[1];
    iVar8 = iVar3;
    if (iVar3 < 1) {
      iVar8 = 0;
    }
    iVar12 = param_1[2];
    iVar9 = iVar12;
    if (iVar12 < 1) {
      iVar9 = 0;
    }
    iVar10 = param_1[3];
    if (iVar6 <= param_1[3]) {
      iVar10 = iVar6;
    }
    iVar11 = param_1[4];
    if (iVar2 <= param_1[4]) {
      iVar11 = iVar2;
    }
    if ((iVar10 < iVar8) || (iVar11 < iVar9)) {
      return -2;
    }
    iVar2 = *piVar1;
    uVar5 = (undefined1)param_6;
    param_2 = param_2 + iVar3;
    param_3 = param_3 + iVar12;
    local_10 = 0;
    local_14 = param_5;
    iVar3 = param_5 * param_5;
    uVar4 = param_4 * param_4;
    local_28 = 0;
    local_2c = uVar4 * 2 * param_5;
    local_30 = ((uVar4 >> 2) + iVar3) - uVar4 * param_5;
    while (local_28 - local_2c < 0) {
      iVar12 = param_2 + local_10;
      iVar6 = param_3 + local_14;
      if ((((iVar8 <= iVar12) && (iVar12 <= iVar10)) && (iVar9 <= iVar6)) && (iVar6 <= iVar11)) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      iVar12 = param_2 + local_10;
      iVar6 = param_3 - local_14;
      if (((iVar8 <= iVar12) && (iVar12 <= iVar10)) && ((iVar9 <= iVar6 && (iVar6 <= iVar11)))) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      iVar12 = param_2 - local_10;
      iVar6 = param_3 + local_14;
      if (((iVar8 <= iVar12) && (iVar12 <= iVar10)) && ((iVar9 <= iVar6 && (iVar6 <= iVar11)))) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      iVar12 = param_2 - local_10;
      iVar6 = param_3 - local_14;
      if ((((iVar8 <= iVar12) && (iVar12 <= iVar10)) && (iVar9 <= iVar6)) && (iVar6 <= iVar11)) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      if (-1 < local_30) {
        local_14 = local_14 + -1;
        param_5 = param_5 + -1;
        local_2c = local_2c + uVar4 * -2;
        local_30 = local_30 - local_2c;
      }
      local_10 = local_10 + 1;
      local_28 = local_28 + iVar3 * 2;
      local_30 = local_30 + local_28 + iVar3;
    }
    local_30 = local_30 +
               ((int)(((((int)(uVar4 - iVar3) >> 1) + (uVar4 - iVar3)) - local_28) - local_2c) >> 1)
    ;
    do {
      iVar12 = param_2 + local_10;
      iVar6 = param_3 + local_14;
      if (((iVar8 <= iVar12) && (iVar12 <= iVar10)) && ((iVar9 <= iVar6 && (iVar6 <= iVar11)))) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      iVar12 = param_2 + local_10;
      iVar6 = param_3 - local_14;
      if (((iVar8 <= iVar12) && (iVar12 <= iVar10)) && ((iVar9 <= iVar6 && (iVar6 <= iVar11)))) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      iVar12 = param_2 - local_10;
      iVar6 = param_3 + local_14;
      if ((((iVar8 <= iVar12) && (iVar12 <= iVar10)) && (iVar9 <= iVar6)) && (iVar6 <= iVar11)) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      iVar12 = param_2 - local_10;
      iVar6 = param_3 - local_14;
      if (((iVar8 <= iVar12) && (iVar12 <= iVar10)) && ((iVar9 <= iVar6 && (iVar6 <= iVar11)))) {
        *(undefined1 *)(iVar6 * iVar7 + iVar2 + iVar12) = uVar5;
      }
      if (local_30 < 0) {
        local_10 = local_10 + 1;
        local_28 = local_28 + iVar3 * 2;
        local_30 = local_30 + local_28;
      }
      local_14 = local_14 + -1;
      local_2c = local_2c + uVar4 * -2;
      iVar6 = local_2c - uVar4;
      local_30 = local_30 - iVar6;
      param_5 = param_5 + -1;
    } while (-1 < param_5);
  }
  return iVar6;
}
```

---

## FUN_00406fbd — 0x406fbd

- Classification : internal
- Corps : `0x406fbd–0x4072ba`
- État : pseudocode obtenu
- Evidence : `ev_8e76078d2d53f88249b0b34835a0b275b13863d70a847b6cf357f577efc82f59`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x403c35` — `FUN_00403c35`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00406fbd(int *param_1,int param_2,int param_3,int param_4,int param_5,undefined4 param_6)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined1 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  undefined4 *puVar16;
  int local_30;
  int local_2c;
  int local_28;
  int local_14;
  int local_10;
  
  if ((param_4 == 0) || (param_5 == 0)) {
    iVar6 = FUN_00403c35(param_1,param_2 - param_4,param_3 - param_5,param_2 + param_4,
                         param_3 + param_5,0,param_6);
  }
  else {
    piVar1 = (int *)*param_1;
    iVar6 = piVar1[1];
    iVar7 = iVar6 + 1;
    if ((iVar7 == 0 || iVar6 < -1) || (iVar2 = piVar1[2], iVar2 < 0)) {
      return -1;
    }
    iVar3 = param_1[1];
    iVar8 = iVar3;
    if (iVar3 < 1) {
      iVar8 = 0;
    }
    iVar15 = param_1[2];
    iVar9 = iVar15;
    if (iVar15 < 1) {
      iVar9 = 0;
    }
    iVar10 = param_1[3];
    if (iVar6 <= param_1[3]) {
      iVar10 = iVar6;
    }
    iVar11 = param_1[4];
    if (iVar2 <= param_1[4]) {
      iVar11 = iVar2;
    }
    if ((iVar10 < iVar8) || (iVar11 < iVar9)) {
      return -2;
    }
    iVar2 = *piVar1;
    uVar5 = (undefined1)param_6;
    param_6 = CONCAT22(CONCAT11(uVar5,uVar5),CONCAT11(uVar5,uVar5));
    param_2 = param_2 + iVar3;
    param_3 = param_3 + iVar15;
    local_10 = 0;
    local_14 = param_5;
    iVar3 = param_5 * param_5;
    uVar4 = param_4 * param_4;
    local_28 = 0;
    local_2c = uVar4 * 2 * param_5;
    local_30 = ((uVar4 >> 2) + iVar3) - uVar4 * param_5;
    while (local_28 - local_2c < 0) {
      iVar6 = param_2 + local_10;
      if (iVar8 <= iVar6) {
        if (iVar10 <= iVar6) {
          iVar6 = iVar10;
        }
        iVar15 = param_2 - local_10;
        if (iVar15 <= iVar10) {
          if (iVar15 <= iVar8) {
            iVar15 = iVar8;
          }
          iVar13 = param_3 + local_14;
          if (iVar9 <= iVar13) {
            if (iVar13 <= iVar11) {
              uVar12 = (iVar6 - iVar15) + 1;
              uVar14 = uVar12 & 3;
              puVar16 = (undefined4 *)(iVar13 * iVar7 + iVar2 + iVar15);
              for (uVar12 = uVar12 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                *puVar16 = param_6;
                puVar16 = puVar16 + 1;
              }
              for (; uVar14 != 0; uVar14 = uVar14 - 1) {
                *(undefined1 *)puVar16 = uVar5;
                puVar16 = (undefined4 *)((int)puVar16 + 1);
              }
            }
            iVar13 = param_3 - local_14;
            if ((iVar9 <= iVar13) && (iVar13 <= iVar11)) {
              uVar12 = (iVar6 - iVar15) + 1;
              uVar14 = uVar12 & 3;
              puVar16 = (undefined4 *)(iVar13 * iVar7 + iVar2 + iVar15);
              for (uVar12 = uVar12 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                *puVar16 = param_6;
                puVar16 = puVar16 + 1;
              }
              for (; uVar14 != 0; uVar14 = uVar14 - 1) {
                *(undefined1 *)puVar16 = uVar5;
                puVar16 = (undefined4 *)((int)puVar16 + 1);
              }
            }
          }
        }
      }
      if (-1 < local_30) {
        local_14 = local_14 + -1;
        param_5 = param_5 + -1;
        local_2c = local_2c + uVar4 * -2;
        local_30 = local_30 - local_2c;
      }
      local_10 = local_10 + 1;
      local_28 = local_28 + iVar3 * 2;
      local_30 = local_30 + local_28 + iVar3;
    }
    local_30 = local_30 +
               ((int)(((((int)(uVar4 - iVar3) >> 1) + (uVar4 - iVar3)) - local_28) - local_2c) >> 1)
    ;
    do {
      iVar6 = param_2 + local_10;
      if (iVar8 <= iVar6) {
        if (iVar10 <= iVar6) {
          iVar6 = iVar10;
        }
        iVar15 = param_2 - local_10;
        if (iVar15 <= iVar10) {
          if (iVar15 <= iVar8) {
            iVar15 = iVar8;
          }
          iVar13 = param_3 + local_14;
          if (iVar9 <= iVar13) {
            if (iVar13 <= iVar11) {
              uVar12 = (iVar6 - iVar15) + 1;
              uVar14 = uVar12 & 3;
              puVar16 = (undefined4 *)(iVar13 * iVar7 + iVar2 + iVar15);
              for (uVar12 = uVar12 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                *puVar16 = param_6;
                puVar16 = puVar16 + 1;
              }
              for (; uVar14 != 0; uVar14 = uVar14 - 1) {
                *(undefined1 *)puVar16 = uVar5;
                puVar16 = (undefined4 *)((int)puVar16 + 1);
              }
            }
            iVar13 = param_3 - local_14;
            if ((iVar9 <= iVar13) && (iVar13 <= iVar11)) {
              uVar12 = (iVar6 - iVar15) + 1;
              uVar14 = uVar12 & 3;
              puVar16 = (undefined4 *)(iVar13 * iVar7 + iVar2 + iVar15);
              for (uVar12 = uVar12 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
                *puVar16 = param_6;
                puVar16 = puVar16 + 1;
              }
              for (; uVar14 != 0; uVar14 = uVar14 - 1) {
                *(undefined1 *)puVar16 = uVar5;
                puVar16 = (undefined4 *)((int)puVar16 + 1);
              }
            }
          }
        }
      }
      if (local_30 < 0) {
        local_10 = local_10 + 1;
        local_28 = local_28 + iVar3 * 2;
        local_30 = local_30 + local_28;
      }
      local_14 = local_14 + -1;
      local_2c = local_2c + uVar4 * -2;
      iVar6 = local_2c - uVar4;
      local_30 = local_30 - iVar6;
      param_5 = param_5 + -1;
    } while (-1 < param_5);
  }
  return iVar6;
}
```

---

## FUN_004080cf — 0x4080cf

- Classification : internal
- Corps : `0x4080cf–0x408186`
- État : pseudocode obtenu
- Evidence : `ev_444eaf89f729befe5df5270500396414e5a6aae903ad69ce54432ab18802d7f0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004080cf(uint param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  
  for (; (int)param_1 < 0; param_1 = param_1 + 0xe10) {
  }
  for (; 0xe10 < (int)param_1; param_1 = param_1 - 0xe10) {
  }
  if (param_1 < 0x709) {
    if (param_1 < 0x385) {
      iVar1 = *(int *)(&DAT_004072bb + param_1 * 4);
      iVar2 = *(int *)(&DAT_004080cb + param_1 * -4);
    }
    else {
      iVar1 = -*(int *)(&DAT_004072bb + (0x708 - param_1) * 4);
      iVar2 = *(int *)(&DAT_004080cb + (0x708 - param_1) * -4);
    }
  }
  else {
    param_1 = 0xe10 - param_1;
    if (param_1 < 0x385) {
      iVar1 = *(int *)(&DAT_004072bb + param_1 * 4);
      iVar2 = -*(int *)(&DAT_004080cb + param_1 * -4);
    }
    else {
      iVar1 = -*(int *)(&DAT_004072bb + (0x708 - param_1) * 4);
      iVar2 = -*(int *)(&DAT_004080cb + (0x708 - param_1) * -4);
    }
  }
  *param_2 = iVar1;
  *param_3 = iVar2;
  return;
}
```

---

## FUN_00408187 — 0x408187

- Classification : internal
- Corps : `0x408187–0x4081ac`
- État : pseudocode obtenu
- Evidence : `ev_1a5849bd620515f97ff1a9d2e00579a802ce436bb3e08e81797581f012189805`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00408187(int param_1,int param_2,uint *param_3)

{
  uint uVar1;
  ushort uVar2;
  
  uVar1 = (uint)((longlong)param_1 * (longlong)param_2);
  uVar2 = (ushort)(uVar1 + 0x8000 >> 0x10);
  *param_3 = (uint)uVar2 |
             CONCAT22(uVar2,(short)((ulonglong)((longlong)param_1 * (longlong)param_2) >> 0x20) +
                            (ushort)(0xffff7fff < uVar1)) << 0x10;
  return;
}
```

---

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


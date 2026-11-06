# 0006_batch_0002 — détails (1/3)

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

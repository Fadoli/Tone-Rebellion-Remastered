# 0007_batch_0003 — détails (2/3)

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

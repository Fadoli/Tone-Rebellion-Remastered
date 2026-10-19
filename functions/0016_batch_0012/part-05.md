# 0016_batch_0012 — détails (5/6)

## FUN_0045c3fe — 0x45c3fe

- Classification : internal
- Corps : `0x45c3fe–0x45c46f`
- État : pseudocode obtenu
- Evidence : `ev_9840c3c490311b0066fbdd4253d4b2869ddd0d71d6216ba3c133c6cf8c01d0bd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014e7` — `thunk_FUN_0045035a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045c3fe(int param_1)

{
  undefined2 uVar1;
  undefined2 *in_ECX;
  
  *in_ECX = *(undefined2 *)(param_1 + 8);
  uVar1 = thunk_FUN_0045035a();
  in_ECX[1] = uVar1;
  in_ECX[0x2a] = 0xffff;
  in_ECX[0x29] = 0xffff;
  in_ECX[0x28] = 0xffff;
  in_ECX[0x27] = 0xffff;
  in_ECX[0x26] = 0xffff;
  *(undefined4 *)(in_ECX + 0x2c) = 1;
  *(uint *)(in_ECX + 0x2e) = (uint)(*(int *)(param_1 + 0x10) == 0x2f);
  return;
}
```

---

## FUN_0045c470 — 0x45c470

- Classification : internal
- Corps : `0x45c470–0x45c51a`
- État : pseudocode obtenu
- Evidence : `ev_6f2d0cdcc95781d8db31227e8361cb64d04a9406408057cec473ac848439f601`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401906` — `thunk_FUN_0045c325`
- `0x4020c2` — `thunk_FUN_0045c797`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045c470(short param_1)

{
  undefined2 uVar1;
  int in_ECX;
  short local_8;
  
  if (*(short *)(in_ECX + 0x24) < 8) {
    for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
      if (*(short *)(in_ECX + 4 + local_8 * 2) == -1) {
        *(short *)(in_ECX + 4 + local_8 * 2) = param_1;
        *(short *)(in_ECX + 0x4c) = param_1;
        uVar1 = thunk_FUN_0045c325();
        *(undefined2 *)(&DAT_006137c4 + param_1 * 0x4c) = uVar1;
        *(short *)(in_ECX + 0x24) = *(short *)(in_ECX + 0x24) + 1;
        thunk_FUN_0045c797(param_1);
        return 1;
      }
    }
  }
  return 0;
}
```

---

## FUN_0045c51b — 0x45c51b

- Classification : internal
- Corps : `0x45c51b–0x45c5ac`
- État : pseudocode obtenu
- Evidence : `ev_e428ee76ec49704dfcc5748a0e4c9f729e00a254d0245818dab6cd79aa4c7dd7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401e15` — `thunk_FUN_0045c82f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045c51b(short param_1)

{
  int in_ECX;
  short local_8;
  
  local_8 = 0;
  while( true ) {
    if (7 < local_8) {
      return 0;
    }
    if (*(short *)(in_ECX + 4 + local_8 * 2) == param_1) break;
    local_8 = local_8 + 1;
  }
  *(undefined2 *)(in_ECX + 4 + local_8 * 2) = 0xffff;
  *(undefined2 *)(&DAT_006137c4 + param_1 * 0x4c) = 0xffff;
  *(short *)(in_ECX + 0x24) = *(short *)(in_ECX + 0x24) + -1;
  if (*(short *)(in_ECX + 0x4c) == param_1) {
    thunk_FUN_0045c82f();
  }
  return 1;
}
```

---

## FUN_0045c5ad — 0x45c5ad

- Classification : internal
- Corps : `0x45c5ad–0x45c5b7`
- État : pseudocode obtenu
- Evidence : `ev_e6dee393e03ab00f0994b309fdac108e18fb8057de802d523bfd0edb1180019a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045c5ad(void)

{
  return;
}
```

---

## FUN_0045c5b8 — 0x45c5b8

- Classification : internal
- Corps : `0x45c5b8–0x45c771`
- État : pseudocode obtenu
- Evidence : `ev_fc1315f4f77398c2c69554ced3f43d6e76dfcc9e7fe4eb0406200bdcbd11d0bf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40156e` — `thunk_FUN_0041ff8b`
- `0x40164a` — `thunk_FUN_0045c2d1`
- `0x401933` — `thunk_FUN_00464242`
- `0x401e15` — `thunk_FUN_0045c82f`
- `0x4020b3` — `thunk_FUN_00466533`
- `0x402144` — `thunk_FUN_00420f28`
- `0x40225c` — `thunk_FUN_00421ec1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045c5b8(void)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int in_ECX;
  short local_8;
  
  thunk_FUN_0045c82f();
  for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
    if (*(short *)(in_ECX + 4 + local_8 * 2) != -1) {
      *(undefined2 *)(&DAT_006137c4 + *(short *)(in_ECX + 4 + local_8 * 2) * 0x4c) = 0xffff;
      *(undefined4 *)(&DAT_006137bc + *(short *)(in_ECX + 4 + local_8 * 2) * 0x4c) = 0;
      thunk_FUN_0041ff8b(0);
      thunk_FUN_00421ec1(0xffffffff);
      sVar2 = thunk_FUN_00420f28();
      iVar3 = thunk_FUN_00464242((&DAT_006137b8)[*(short *)(in_ECX + 4 + local_8 * 2) * 0x13],0);
      sVar1 = *(short *)(iVar3 + 8);
      if (sVar2 < *(short *)(&DAT_006137d8 + *(short *)(in_ECX + 4 + local_8 * 2) * 0x4c)) {
        *(short *)(&DAT_006137d8 + *(short *)(in_ECX + 4 + local_8 * 2) * 0x4c) = sVar2;
      }
      if (sVar1 < *(short *)(&DAT_006137da + *(short *)(in_ECX + 4 + local_8 * 2) * 0x4c)) {
        *(short *)(&DAT_006137da + *(short *)(in_ECX + 4 + local_8 * 2) * 0x4c) = sVar1;
      }
    }
  }
  thunk_FUN_00466533((int)*(short *)(in_ECX + 0x4e));
  thunk_FUN_00466533((int)*(short *)(in_ECX + 0x52));
  thunk_FUN_00466533((int)*(short *)(in_ECX + 0x54));
  thunk_FUN_00466533((int)*(short *)(in_ECX + 0x50));
  thunk_FUN_0045c2d1();
  return;
}
```

---

## FUN_0045c772 — 0x45c772

- Classification : internal
- Corps : `0x45c772–0x45c796`
- État : pseudocode obtenu
- Evidence : `ev_ffd4a94702a3bf625c57517e22f35f4162c51590d8661ac7e7643c72286abeed`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_0045c772(void)

{
  int iVar1;
  
  iVar1 = thunk_FUN_0045c3bb();
  return 9 < *(short *)(iVar1 + 0x2a);
}
```

---

## FUN_0045c797 — 0x45c797

- Classification : internal
- Corps : `0x45c797–0x45c82e`
- État : pseudocode obtenu
- Evidence : `ev_a8242d95ff85a769bd494a1ed76f1d1e8daf1e73c73ebc05ce194694034caf68`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045c797(short param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = thunk_FUN_0045c3bb();
  if (*(short *)(iVar1 + 0x2a) < 10) {
    *(undefined2 *)(iVar1 + 0x2a) = 0;
  }
  else {
    *(short *)(iVar1 + 0x2a) = *(short *)(iVar1 + 0x2a) + -10;
  }
  iVar2 = param_1 * 0x4c;
  if (iVar2 != -0x6137b8) {
    *(uint *)(&DAT_006137d4 + iVar2) = *(uint *)(&DAT_006137d4 + iVar2) | 0x21;
    *(undefined2 *)(iVar1 + 0x30) = 0;
    if ((*(int *)(&DAT_006137bc + iVar2) == 0) && ((*(uint *)(&DAT_006137d4 + iVar2) & 0x100) != 0))
    {
      *(uint *)(&DAT_006137d4 + iVar2) = *(uint *)(&DAT_006137d4 + iVar2) & 0xfffffeff;
    }
  }
  return;
}
```

---

## FUN_0045c82f — 0x45c82f

- Classification : internal
- Corps : `0x45c82f–0x45c89a`
- État : pseudocode obtenu
- Evidence : `ev_eecb04c280f5c920a66f5c85ebbf4f8baa8d27cb0ce2d27cb6fd068d04d7ecd6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401672` — `thunk_FUN_0045c51b`
- `0x40225c` — `thunk_FUN_00421ec1`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045c82f(void)

{
  short sVar1;
  undefined2 uVar2;
  int in_ECX;
  undefined2 extraout_var;
  
  if (*(short *)(in_ECX + 0x4c) != -1) {
    thunk_FUN_0045c3bb();
    sVar1 = *(short *)(in_ECX + 0x4c);
    thunk_FUN_00421ec1(0xffffffff);
    uVar2 = *(undefined2 *)(in_ECX + 0x4c);
    *(undefined2 *)(in_ECX + 0x4c) = 0xffff;
    if (*(int *)(&DAT_006137bc + sVar1 * 0x4c) == 0) {
      thunk_FUN_0045c51b(CONCAT22(extraout_var,uVar2));
    }
  }
  return;
}
```

---

## FUN_0045c89b — 0x45c89b

- Classification : internal
- Corps : `0x45c89b–0x45c9b4`
- État : pseudocode obtenu
- Evidence : `ev_386424a9bb2879ea6ee21c72dc801a4115ff56c16cbba12cd135d94f0af0b2cc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_0045c89b(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int local_14;
  int local_10;
  
  bVar1 = false;
  iVar2 = thunk_FUN_0045c3bb();
  local_14 = 0;
  for (local_10 = 0; local_10 < (int)(uint)DAT_006136b0; local_10 = local_10 + 1) {
    if (*(int *)(&DAT_005eebc4 + *(int *)(iVar2 + 0x14) * 4 + local_10 * 0x29e8) != 0) {
      local_14 = local_14 + 1;
    }
  }
  iVar3 = *(short *)(iVar2 + 0x4a) + 1;
  iVar2 = *(int *)(iVar2 + 0x10) + -0x2c;
  if (((-1 < iVar2) && (iVar2 < 4)) && (iVar3 <= *(short *)(&DAT_004a415a + iVar2 * 2))) {
    if (DAT_006136b2 == 0) {
      bVar1 = (char)(&DAT_004a42b8)[iVar3 + iVar2 * 3] <= local_14;
    }
    else if (DAT_006136b2 == 1) {
      bVar1 = (char)(&DAT_004a42c8)[iVar3 + iVar2 * 3] <= local_14;
    }
    else {
      bVar1 = (char)(&DAT_004a42d8)[iVar3 + iVar2 * 3] <= local_14;
    }
  }
  return bVar1;
}
```

---

## FUN_0045c9b5 — 0x45c9b5

- Classification : internal
- Corps : `0x45c9b5–0x45c9fd`
- État : pseudocode obtenu
- Evidence : `ev_ace821a0fd1a4a7894b8b39ad26490cf63ebebe505634b68c42ed8ed659a90bd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401686` — `thunk_FUN_004666c9`
- `0x4018ac` — `thunk_FUN_0045c89b`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045c9b5(void)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int iVar3;
  int in_ECX;
  
  uVar2 = thunk_FUN_0045c3bb();
  if (*(short *)(in_ECX + 0x4e) == -1) {
    iVar3 = thunk_FUN_0045c89b();
    if (iVar3 != 0) {
      uVar1 = thunk_FUN_004666c9(uVar2,1,0xffffffff);
      *(undefined2 *)(in_ECX + 0x4e) = uVar1;
    }
  }
  return;
}
```

---

## FUN_0045c9fe — 0x45c9fe

- Classification : internal
- Corps : `0x45c9fe–0x45ca1d`
- État : pseudocode obtenu
- Evidence : `ev_5c14113625083d560327f4346a1c368f7c89d72179c33534f9aa7d0e2c0a49f2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_0045c9fe(void)

{
  int in_ECX;
  
  return *(short *)(in_ECX + 0x4e) != -1;
}
```

---

## FUN_0045ca1e — 0x45ca1e

- Classification : internal
- Corps : `0x45ca1e–0x45ca4f`
- État : pseudocode obtenu
- Evidence : `ev_c42b42f4a079b72f5b4d66ce3835adce2afc8b5edc82b68430d0afe305d069b5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4020b3` — `thunk_FUN_00466533`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045ca1e(void)

{
  int in_ECX;
  
  if (*(short *)(in_ECX + 0x4e) != -1) {
    thunk_FUN_00466533((int)*(short *)(in_ECX + 0x4e));
    *(undefined2 *)(in_ECX + 0x4e) = 0xffff;
  }
  return;
}
```

---

## FUN_0045ca50 — 0x45ca50

- Classification : internal
- Corps : `0x45ca50–0x45cb0a`
- État : pseudocode obtenu
- Evidence : `ev_3342eb6da51478f75b3ebc49638af037ce72104f070575c2d9b1bebc3b1a2068`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40181b` — `thunk_FUN_00450978`
- `0x4018ac` — `thunk_FUN_0045c89b`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4020b3` — `thunk_FUN_00466533`
- `0x4021c1` — `thunk_FUN_00453cba`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- `0x4a433c` — "C:\\float\\src\\staffbld.cpp"

### Pseudocode Ghidra

```c
void FUN_0045ca50(void)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int in_ECX;
  undefined4 uVar4;
  
  iVar3 = thunk_FUN_0045c89b();
  if (iVar3 != 0) {
    iVar3 = thunk_FUN_0045c3bb();
    if (iVar3 == 0) {
      uVar4 = thunk_FUN_00414b64(s_C__float_src_staffbld_cpp_004a433c,0x19f,&DAT_004a4338);
    }
    else {
      uVar4 = 0;
    }
    *(undefined2 *)(iVar3 + 0x28) = 0;
    sVar1 = thunk_FUN_00450978(uVar4);
    thunk_FUN_00453cba(*(short *)(iVar3 + 0x4a) + 1);
    sVar2 = thunk_FUN_00450978();
    *(short *)(iVar3 + 0x34) = *(short *)(iVar3 + 0x34) + (sVar2 - sVar1);
    thunk_FUN_00466533((int)*(short *)(in_ECX + 0x4e));
    *(undefined2 *)(in_ECX + 0x4e) = 0xffff;
  }
  return;
}
```

---

## FUN_0045cb0b — 0x45cb0b

- Classification : internal
- Corps : `0x45cb0b–0x45cba9`
- État : pseudocode obtenu
- Evidence : `ev_d2fe25472fee84d35e760f64f32b8177d930c51e4c9861443f33b53d9517f084`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401451` — `thunk_FUN_00466732`
- `0x401e15` — `thunk_FUN_0045c82f`
- `0x4020b3` — `thunk_FUN_00466533`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045cb0b(int param_1)

{
  undefined4 uVar1;
  int in_ECX;
  
  if (param_1 == 0) {
    if (*(short *)(in_ECX + 0x50) != -1) {
      thunk_FUN_00466533((int)*(short *)(in_ECX + 0x50));
      *(undefined2 *)(in_ECX + 0x50) = 0xffff;
    }
    thunk_FUN_0045c82f();
    uVar1 = thunk_FUN_0045c3bb();
    thunk_FUN_00466732(uVar1,1);
    *(undefined2 *)(in_ECX + 0x4e) = 0xffff;
    thunk_FUN_00466732(uVar1,2);
    *(undefined2 *)(in_ECX + 0x52) = 0xffff;
    thunk_FUN_00466732(uVar1,3);
    *(undefined2 *)(in_ECX + 0x54) = 0xffff;
  }
  return;
}
```

---

## FUN_0045cbaa — 0x45cbaa

- Classification : internal
- Corps : `0x45cbaa–0x45cc16`
- État : pseudocode obtenu
- Evidence : `ev_0789846ee60f8a4d83463a89fc6fe12dfc11f8b3d9c16275c87c17f11589f4ba`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401451` — `thunk_FUN_00466732`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045cbaa(int param_1)

{
  undefined4 uVar1;
  int in_ECX;
  
  if (param_1 == 0) {
    uVar1 = thunk_FUN_0045c3bb();
    thunk_FUN_00466732(uVar1,1);
    *(undefined2 *)(in_ECX + 0x4e) = 0xffff;
    thunk_FUN_00466732(uVar1,2);
    *(undefined2 *)(in_ECX + 0x52) = 0xffff;
    thunk_FUN_00466732(uVar1,3);
    *(undefined2 *)(in_ECX + 0x54) = 0xffff;
  }
  return;
}
```

---

## FUN_0045cc17 — 0x45cc17

- Classification : internal
- Corps : `0x45cc17–0x45ccb8`
- État : pseudocode obtenu
- Evidence : `ev_662549a7323954de913c38a89d56389b3a108f6dc29b0fc24f36af952a7d1164`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401451` — `thunk_FUN_00466732`
- `0x401686` — `thunk_FUN_004666c9`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045cc17(short param_1)

{
  short sVar1;
  int iVar2;
  int in_ECX;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_8;
  
  iVar2 = thunk_FUN_0045c3bb();
  if (param_1 == 0) {
    local_8 = (short *)(in_ECX + 0x52);
    local_10 = (short *)(iVar2 + 0x2a);
    local_14 = 2;
  }
  else {
    local_8 = (short *)(in_ECX + 0x54);
    local_10 = (short *)(iVar2 + 0x2c);
    local_14 = 3;
  }
  if (*local_8 == -1) {
    if (*local_10 < 100) {
      sVar1 = thunk_FUN_004666c9(iVar2,local_14,0xffffffff);
      *local_8 = sVar1;
    }
  }
  else {
    thunk_FUN_00466732(iVar2,local_14);
    *local_8 = -1;
  }
  return;
}
```

---

## FUN_0045ccb9 — 0x45ccb9

- Classification : internal
- Corps : `0x45ccb9–0x45cccd`
- État : pseudocode obtenu
- Evidence : `ev_88f2fca28c72eb24ef1569654f3e11f71cea3d8054f270c16741f468c14427a0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401910` — `thunk_FUN_0045cb0b`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045ccb9(void)

{
  thunk_FUN_0045cb0b(0);
  return;
}
```

---

## FUN_0045ccce — 0x45ccce

- Classification : internal
- Corps : `0x45ccce–0x45cd26`
- État : pseudocode obtenu
- Evidence : `ev_03ae670f8ce55005e51708a495030fb04df7fd648e2c8b32c3beb60b80a5343b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40135c` — `thunk_FUN_00452e2b`
- `0x4014e7` — `thunk_FUN_0045035a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045ccce(int param_1)

{
  undefined2 uVar1;
  undefined2 *in_ECX;
  
  *in_ECX = *(undefined2 *)(param_1 + 8);
  uVar1 = thunk_FUN_0045035a();
  in_ECX[1] = uVar1;
  in_ECX[0x14] = *(undefined2 *)(param_1 + 8);
  *(undefined4 *)(in_ECX + 0x16) = 9;
  uVar1 = thunk_FUN_00452e2b();
  in_ECX[0x18] = uVar1;
  in_ECX[0x19] = 0;
  return;
}
```

---

## FUN_0045cd27 — 0x45cd27

- Classification : internal
- Corps : `0x45cd27–0x45cd74`
- État : pseudocode obtenu
- Evidence : `ev_31afe6370f840800d5842722949f28b40233ecb74d7efdf5eb1880738a17db1e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- `0x4a435c` — "C:\\float\\src\\staffbld.cpp"

### Pseudocode Ghidra

```c
int FUN_0045cd27(void)

{
  int iVar1;
  
  iVar1 = thunk_FUN_0045c3bb();
  if (iVar1 == 0) {
    thunk_FUN_00414b64(s_C__float_src_staffbld_cpp_004a435c,0x21e,&DAT_004a4358);
  }
  return *(short *)(iVar1 + 0x4a) * 0x19 + 0x32;
}
```

---

## FUN_0045cd75 — 0x45cd75

- Classification : internal
- Corps : `0x45cd75–0x45d3bc`
- État : pseudocode obtenu
- Evidence : `ev_2968fcc7203f402ad28ae77013ff42e2116410c3752743ae3eb5ee0390f207ab`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40114a` — `thunk_FUN_0045cc17`
- `0x4013c0` — `thunk_FUN_004655b2`
- `0x40156e` — `thunk_FUN_0041ff8b`
- `0x4018cf` — `thunk_FUN_0041ff2e`
- `0x4018f7` — `thunk_FUN_0045ca50`
- `0x401933` — `thunk_FUN_00464242`
- `0x401b63` — `thunk_FUN_0045c772`
- `0x401d1b` — `thunk_FUN_004662b7`
- `0x401e15` — `thunk_FUN_0045c82f`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fd7` — `thunk_FUN_0045c5ad`
- `0x402063` — `thunk_FUN_0045d3bd`
- `0x4020b3` — `thunk_FUN_00466533`
- `0x402144` — `thunk_FUN_00420f28`
- `0x4023bf` — `thunk_FUN_0045c3bb`
- `0x40248c` — `thunk_FUN_0045cd27`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a4378` — "type>=(int)PIT_Recruiter1 && type <=(int)PIT_Spec2"
- `0x4a43ac` — "C:\\float\\src\\staffbld.cpp"

### Pseudocode Ghidra

```c
void FUN_0045cd75(void)

{
  short *psVar1;
  short sVar2;
  undefined2 uVar3;
  undefined2 *in_ECX;
  int iVar4;
  int local_80;
  undefined1 local_64 [2];
  undefined2 local_62;
  undefined2 local_60;
  undefined2 local_5a;
  undefined2 local_58;
  undefined2 local_56;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  undefined4 local_44;
  undefined4 local_40;
  int local_3c;
  undefined4 *local_38;
  undefined4 local_34;
  short local_30 [4];
  int local_28;
  short local_24;
  int local_20;
  int local_1c;
  int local_18;
  short local_14 [4];
  int local_c;
  int local_8;
  
  local_28 = thunk_FUN_0045c3bb();
  _memset(local_14,0,6);
  _memset(local_30,0,6);
  for (local_24 = 0; local_24 < 8; local_24 = local_24 + 1) {
    if (in_ECX[local_24 + 2] != -1) {
      local_34 = &DAT_006137b8 + (short)in_ECX[local_24 + 2] * 0x13;
      sVar2 = thunk_FUN_0041ff2e();
      local_14[sVar2] = local_14[sVar2] + 1;
    }
  }
  local_18 = *(int *)(local_28 + 0x10);
  if ((local_18 < 0x2c) || (0x32 < local_18)) {
    thunk_FUN_00414b64(s_C__float_src_staffbld_cpp_004a43ac,0x23e,
                       s_type>__int_PIT_Recruiter1____typ_004a4378);
  }
  local_18 = local_18 + -0x2b;
  for (local_24 = 0; local_24 < 3; local_24 = local_24 + 1) {
    local_30[local_24] =
         *(short *)(&DAT_004a4170 + local_24 * 2 + *(short *)(local_28 + 0x4a) * 8 + local_18 * 0x18
                   ) - local_14[local_24];
  }
  local_8 = thunk_FUN_0045c772();
  *(uint *)(local_28 + 0x1c) = *(uint *)(local_28 + 0x1c) & 0xfffffff7;
  local_c = 0;
  for (local_24 = 0; local_24 < 8; local_24 = local_24 + 1) {
    if (in_ECX[local_24 + 2] != -1) {
      iVar4 = (short)in_ECX[local_24 + 2] * 0x4c;
      local_38 = &DAT_006137b8 + (short)in_ECX[local_24 + 2] * 0x13;
      if ((*(uint *)(&DAT_006137d4 + iVar4) & 0x20) == 0) {
        sVar2 = thunk_FUN_0041ff2e();
        local_48 = (int)sVar2;
        local_50 = DAT_004bf11c;
        local_4c = 4 - DAT_004bf11c;
        iVar4 = local_4c * *(short *)(&DAT_004a424a + local_48 * 2 + local_38[1] * 6) +
                DAT_004bf11c * *(short *)(&DAT_004a4282 + local_48 * 2 + local_38[1] * 6);
        local_54 = (int)(iVar4 + (iVar4 >> 0x1f & 3U)) >> 2;
        if (((((in_ECX[0x26] == -1) && (local_48 < *(short *)(&DAT_004a4158 + local_38[1] * 2))) &&
             (local_48 < *(short *)(local_28 + 0x4a))) &&
            ((local_54 <= *(short *)(local_38 + 2) && (0 < local_54)))) &&
           ((local_30[local_48 + 1] != 0 && ((in_ECX[0x28] == -1 && (local_8 != 0)))))) {
          in_ECX[0x26] = in_ECX[local_24 + 2];
          local_c = 1;
        }
        if ((local_38[0xb] == 2) && ((local_38[7] & 1) != 0)) {
          *(uint *)(local_28 + 0x1c) = *(uint *)(local_28 + 0x1c) | 8;
        }
      }
      else {
        *(uint *)(local_28 + 0x1c) = *(uint *)(local_28 + 0x1c) | 8;
        *(short *)(local_28 + 0x30) = *(short *)(local_28 + 0x30) + *(short *)(local_28 + 0x32);
        if (*(short *)(local_28 + 0x30) < 0xfb) {
          *(double *)(local_28 + 0x50) = (double)(int)*(short *)(local_28 + 0x30) / 250.0;
        }
        else {
          if (*(int *)(&DAT_006137bc + iVar4) == 0) {
            *(int *)(&DAT_006137bc + iVar4) = local_18;
            thunk_FUN_0041ff8b(0);
          }
          else {
            sVar2 = thunk_FUN_0041ff2e();
            local_3c = (int)sVar2;
            thunk_FUN_0041ff8b(local_3c + 1);
            sVar2 = thunk_FUN_0041ff2e();
            psVar1 = (short *)((int)&local_34 + sVar2 * 2 + 2);
            *psVar1 = *psVar1 + 1;
            sVar2 = thunk_FUN_0041ff2e();
            local_30[sVar2] = local_30[sVar2] + -1;
            local_44 = 6;
            local_40 = *local_38;
            thunk_FUN_004655b2(&local_44);
          }
          iVar4 = thunk_FUN_00464242(*local_38,local_38[1]);
          *(undefined2 *)((int)local_38 + 0x22) = *(undefined2 *)(iVar4 + 8);
          uVar3 = thunk_FUN_00420f28();
          *(undefined2 *)(local_38 + 8) = uVar3;
          thunk_FUN_0045c82f();
          if (in_ECX[0x28] != -1) {
            thunk_FUN_00466533((int)(short)in_ECX[0x28]);
            in_ECX[0x28] = 0xffff;
          }
        }
      }
    }
  }
  if ((in_ECX[0x26] == -1) || ((*(uint *)(&DAT_006137d4 + (short)in_ECX[0x26] * 0x4c) & 0x20) == 0))
  {
    local_80 = 0;
  }
  else {
    local_80 = 1;
  }
  local_20 = local_80;
  if (((0.0 < *(double *)(local_28 + 0x50)) && (local_80 == 0)) &&
     (*(double *)(local_28 + 0x50) = *(double *)(local_28 + 0x50) - 0.25,
     *(double *)(local_28 + 0x50) < 0.0)) {
    *(undefined4 *)(local_28 + 0x50) = 0;
    *(undefined4 *)(local_28 + 0x54) = 0;
  }
  if (local_c != 0) {
    thunk_FUN_0045c5ad();
  }
  if (((local_30[0] == 0) || (in_ECX[0x26] != -1)) || ((in_ECX[0x28] != -1 || (local_8 == 0)))) {
    if (((local_8 == 0) && (in_ECX[0x28] != -1)) && (local_20 == 0)) {
      thunk_FUN_00466533((int)(short)in_ECX[0x28]);
      in_ECX[0x28] = 0xffff;
    }
  }
  else {
    _memset(local_64,0,0x10);
    local_62 = *(undefined2 *)(local_28 + 0x14);
    local_60 = 0xb;
    local_56 = 0;
    local_58 = in_ECX[1];
    local_5a = *in_ECX;
    uVar3 = thunk_FUN_004662b7(local_64);
    in_ECX[0x28] = uVar3;
  }
  if ((in_ECX[0x27] != -1) && (0x13 < *(short *)(local_28 + 0x28))) {
    thunk_FUN_0045ca50();
  }
  sVar2 = thunk_FUN_0045cd27();
  local_1c = (int)sVar2;
  if (*(int *)(in_ECX + 0x2c) == 0) {
    if (in_ECX[0x29] != -1) {
      thunk_FUN_0045cc17(0);
    }
  }
  else if (in_ECX[0x29] == -1) {
    if (*(short *)(local_28 + 0x2a) < local_1c) {
      thunk_FUN_0045cc17(0);
    }
  }
  else if (local_1c <= *(short *)(local_28 + 0x2a)) {
    thunk_FUN_0045cc17(0);
  }
  if (*(int *)(local_28 + 0x10) == 0x2f) {
    if (*(int *)(in_ECX + 0x2e) == 0) {
      if (in_ECX[0x2a] != -1) {
        thunk_FUN_0045cc17(1);
      }
    }
    else if (in_ECX[0x2a] == -1) {
      if (*(short *)(local_28 + 0x2c) < local_1c) {
        thunk_FUN_0045cc17(1);
      }
    }
    else if (local_1c <= *(short *)(local_28 + 0x2c)) {
      thunk_FUN_0045cc17(1);
    }
  }
  thunk_FUN_0045d3bd();
  return;
}
```

---

## FUN_0045d3bd — 0x45d3bd

- Classification : internal
- Corps : `0x45d3bd–0x45d53b`
- État : pseudocode obtenu
- Evidence : `ev_893c4b5ee60dd372f1b3e170309270433c807e778543ea6bb6eb7c4db1bbd25f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40123a` — `thunk_FUN_0041e3eb`
- `0x40135c` — `thunk_FUN_00452e2b`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045d3bd(void)

{
  int iVar1;
  short sVar2;
  short *psVar3;
  undefined2 uVar4;
  short *in_ECX;
  int iVar5;
  bool bVar6;
  int local_18;
  
  psVar3 = in_ECX + 0x14;
  bVar6 = false;
  if (*(int *)(in_ECX + 0x16) == 6) {
    bVar6 = (&DAT_006137b8)[in_ECX[0x18] * 0x13] == -1;
  }
  else if ((*(int *)(in_ECX + 0x16) == 7) &&
          ((iVar1 = in_ECX[0x18] * 0x60 + *psVar3 * 0x29e8,
           *(int *)(&DAT_005ec640 + iVar1 + 0x14) == -1 ||
           ((*(uint *)(&DAT_005ec640 + iVar1 + 0x1c) & 0x80) != 0)))) {
    bVar6 = true;
  }
  if (bVar6) {
    in_ECX[0x16] = 0;
    in_ECX[0x17] = 0;
    for (local_18 = 0; local_18 < 8; local_18 = local_18 + 1) {
      if (in_ECX[local_18 + 2] != -1) {
        sVar2 = in_ECX[local_18 + 2];
        iVar5 = sVar2 * 0x4c;
        iVar1 = *(int *)(&DAT_006137f4 + iVar5);
        if ((((iVar1 == 9) || (iVar1 == 8)) || (iVar1 == 7)) || (iVar1 == 6)) {
          in_ECX[0x16] = 9;
          in_ECX[0x17] = 0;
          *psVar3 = *(short *)(&DAT_006137c6 + iVar5);
          uVar4 = (undefined2)((uint)(&DAT_006137b8 + sVar2 * 0x13) >> 0x10);
          sVar2 = thunk_FUN_0041e3eb(CONCAT22(uVar4,*(undefined2 *)(&DAT_006137c8 + iVar5)),
                                     CONCAT22(uVar4,*(undefined2 *)(&DAT_006137ca + iVar5)));
          in_ECX[0x18] = sVar2;
        }
      }
    }
  }
  if (*(int *)(in_ECX + 0x16) == 0) {
    *psVar3 = *in_ECX;
    in_ECX[0x16] = 9;
    in_ECX[0x17] = 0;
    thunk_FUN_0045c3bb();
    sVar2 = thunk_FUN_00452e2b();
    in_ECX[0x18] = sVar2;
  }
  return;
}
```

---

## FUN_0045d53c — 0x45d53c

- Classification : internal
- Corps : `0x45d53c–0x45d5b9`
- État : pseudocode obtenu
- Evidence : `ev_785dd3a6093d5e2a2fdb69677f3152a4e0df8e2d38aa1e7475c393043ce9b143`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045d53c(void)

{
  int iVar1;
  int in_ECX;
  int local_8;
  
  for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
    if (((*(short *)(in_ECX + 4 + local_8 * 2) != -1) &&
        (iVar1 = *(short *)(in_ECX + 4 + local_8 * 2) * 0x4c, iVar1 != -0x6137b8)) &&
       ((*(uint *)(&DAT_006137d4 + iVar1) & 0x908) == 0)) {
      *(uint *)(&DAT_006137d4 + iVar1) = *(uint *)(&DAT_006137d4 + iVar1) | 0x2000;
      *(undefined4 *)(&DAT_006137dc + iVar1) = 0;
    }
  }
  return;
}
```

---

## FUN_0045d5ba — 0x45d5ba

- Classification : internal
- Corps : `0x45d5ba–0x45d773`
- État : pseudocode obtenu
- Evidence : `ev_03503d5f4f21c180313cc4e25f1af2c527b9a42b659ae9bcfabda4eea5422659`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- `0x4a43cc` — "C:\\float\\src\\staffbld.cpp"

### Pseudocode Ghidra

```c
void FUN_0045d5ba(int param_1,short *param_2)

{
  int iVar1;
  int local_14;
  
  iVar1 = thunk_FUN_0045c3bb();
  if (iVar1 == 0) {
    thunk_FUN_00414b64(s_C__float_src_staffbld_cpp_004a43cc,0x350,&DAT_004a43c8);
  }
  iVar1 = *(int *)(iVar1 + 0x10);
  *(undefined4 *)(param_1 + *param_2 * 4) = 5;
  *param_2 = *param_2 + 1;
  if ((0x2b < iVar1) && (iVar1 < 0x2f)) {
    *(undefined4 *)(param_1 + *param_2 * 4) = 0x10;
    *param_2 = *param_2 + 1;
    *(undefined4 *)(param_1 + *param_2 * 4) = 0x11;
    *param_2 = *param_2 + 1;
    *(undefined4 *)(param_1 + *param_2 * 4) = 0x12;
    *param_2 = *param_2 + 1;
    *(undefined4 *)(param_1 + *param_2 * 4) = 0x13;
    *param_2 = *param_2 + 1;
    *(undefined4 *)(param_1 + *param_2 * 4) = 0xf;
    *param_2 = *param_2 + 1;
  }
  if ((iVar1 == 0x2f) || (iVar1 == 0x30)) {
    *(undefined4 *)(param_1 + *param_2 * 4) = 6;
    *param_2 = *param_2 + 1;
    for (local_14 = 0; local_14 < 8; local_14 = local_14 + 1) {
      *(int *)(param_1 + *param_2 * 4) = local_14 + 0x15;
      *param_2 = *param_2 + 1;
    }
  }
  *(undefined4 *)(param_1 + *param_2 * 4) = 2;
  *param_2 = *param_2 + 1;
  return;
}
```

---

## FUN_0045d774 — 0x45d774

- Classification : internal
- Corps : `0x45d774–0x45d7e7`
- État : pseudocode obtenu
- Evidence : `ev_db8926026801790e01de6e61f2ff6ed838d6659a1deda65df9a6ca559d914928`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018cf` — `thunk_FUN_0041ff2e`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0045d774(int param_1)

{
  short sVar1;
  int in_ECX;
  int local_c;
  int local_8;
  
  local_8 = 0;
  for (local_c = 0; local_c < 8; local_c = local_c + 1) {
    if ((*(short *)(in_ECX + 4 + local_c * 2) != -1) &&
       (sVar1 = thunk_FUN_0041ff2e(), sVar1 == param_1)) {
      local_8 = local_8 + 1;
    }
  }
  return local_8;
}
```

---

## FUN_0045d7e8 — 0x45d7e8

- Classification : internal
- Corps : `0x45d7e8–0x45d866`
- État : pseudocode obtenu
- Evidence : `ev_fff50c897dddc692990ebb4ec2b95c2311565ddf1b32c8498bc8f607b2dcd273`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018cf` — `thunk_FUN_0041ff2e`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0045d7e8(int param_1,int param_2)

{
  short sVar1;
  int in_ECX;
  int local_8;
  
  param_1 = param_1 + 1;
  if (param_1 < 0) {
    param_1 = 0;
  }
  local_8 = param_1;
  while( true ) {
    if (7 < local_8) {
      return -1;
    }
    if ((*(short *)(in_ECX + 4 + local_8 * 2) != -1) &&
       (sVar1 = thunk_FUN_0041ff2e(), sVar1 == param_2)) break;
    local_8 = local_8 + 1;
  }
  return local_8;
}
```

---


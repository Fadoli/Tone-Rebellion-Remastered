# 0016_batch_0012 — détails (1/3)

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

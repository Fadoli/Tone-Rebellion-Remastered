# 0017_batch_0013 — détails (2/3)

## FUN_0045ff6d — 0x45ff6d

- Classification : internal
- Corps : `0x45ff6d–0x45ff9a`
- État : pseudocode obtenu
- Evidence : `ev_526357e2478af97646bf23f3df2a0f8d7ce122477c3dd96420a06c777a322653`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402473` — `thunk_FUN_0045fcbe`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_0045ff6d(undefined2 param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = thunk_FUN_0045fcbe(param_1,param_2,1);
  return iVar1 != 0;
}
```

---

---

## FUN_0045ff9b — 0x45ff9b

- Classification : internal
- Corps : `0x45ff9b–0x45ffe1`
- État : pseudocode obtenu
- Evidence : `ev_4b9248525d606beed73c93adae0abde6ddea331c828e880cbdfebfc67903bbab`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4020b3` — `thunk_FUN_00466533`
- `0x402473` — `thunk_FUN_0045fcbe`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045ff9b(undefined2 param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = thunk_FUN_0045fcbe(param_1,param_2,0);
  if (iVar1 != 0) {
    thunk_FUN_00466533((int)*(short *)(iVar1 + 6));
    *(undefined2 *)(iVar1 + 6) = 0xffff;
  }
  return;
}
```

---

---

## FUN_0045ffe2 — 0x45ffe2

- Classification : internal
- Corps : `0x45ffe2–0x460028`
- État : pseudocode obtenu
- Evidence : `ev_7d2571f143ee8ad7299121d3d6dd5c1e2a8284793e44c8ebaa2e8de2e3d44779`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4020b3` — `thunk_FUN_00466533`
- `0x402473` — `thunk_FUN_0045fcbe`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045ffe2(undefined2 param_1,undefined2 param_2)

{
  int iVar1;
  
  iVar1 = thunk_FUN_0045fcbe(param_1,param_2,1);
  if (iVar1 != 0) {
    thunk_FUN_00466533((int)*(short *)(iVar1 + 6));
    *(undefined2 *)(iVar1 + 6) = 0xffff;
  }
  return;
}
```

---

---

## FUN_00460029 — 0x460029

- Classification : internal
- Corps : `0x460029–0x460071`
- État : pseudocode obtenu
- Evidence : `ev_eadb172927cba3906ffa9c456a1a4d0bc60a645fe530336147da8f8026ff2d26`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4020b3` — `thunk_FUN_00466533`
- `0x402473` — `thunk_FUN_0045fcbe`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00460029(undefined2 param_1,undefined2 param_2)

{
  int iVar1;
  
  while( true ) {
    iVar1 = thunk_FUN_0045fcbe(param_1,param_2,0xffffffff);
    if (iVar1 == 0) break;
    thunk_FUN_00466533((int)*(short *)(iVar1 + 6));
    *(undefined2 *)(iVar1 + 6) = 0xffff;
  }
  return;
}
```

---

---

## FUN_00460072 — 0x460072

- Classification : internal
- Corps : `0x460072–0x460333`
- État : pseudocode obtenu
- Evidence : `ev_1d0bd9feec2d7550ea50129522ad783374e97af92bb6dd9bebd24510c185aedf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014bf` — `thunk_FUN_00467260`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a4784` — "featloc->mItem == PIT_IslandFeature"
- `0x4a47a8` — "C:\\float\\src\\tribe.cpp"

### Pseudocode Ghidra

```c
void FUN_00460072(void)

{
  bool bVar1;
  undefined1 *puVar2;
  int in_ECX;
  int iVar3;
  uint local_2c;
  int local_20 [2];
  undefined1 *local_18;
  int local_14;
  undefined1 *local_10;
  int local_c;
  int local_8;
  
  for (local_8 = 0; local_8 < 0xe; local_8 = local_8 + 1) {
    if (((int)*(short *)(in_ECX + 0x8a) & 1 << ((byte)local_8 & 0x1f)) != 0) {
      local_18 = &DAT_005ec218;
      for (local_14 = 0; puVar2 = local_18, local_14 < (int)(uint)DAT_006136b0;
          local_14 = local_14 + 1) {
        if (*(short *)(local_18 + 0x29e0) == local_8) {
          *(undefined4 *)(local_18 + 0x29cc) = 0;
          iVar3 = *(short *)(local_18 + 0x29d0) * 0x60;
          if (*(int *)(local_18 + iVar3 + 0x438) != 4) {
            thunk_FUN_00414b64(s_C__float_src_tribe_cpp_004a47a8,0x453,
                               s_featloc_>mItem____PIT_IslandFeat_004a4784);
          }
          *(undefined2 *)(puVar2 + iVar3 + 0x472) = 0;
          *(uint *)(puVar2 + iVar3 + 0x444) = *(uint *)(puVar2 + iVar3 + 0x444) & 0xfffffffe;
          local_20[0] = 0;
          local_20[1] = 0;
          while ((local_20[0] == 0 || (local_20[1] == 0))) {
            iVar3 = thunk_FUN_00467260((int)*(short *)(local_18 + 0x29a8));
            iVar3 = iVar3 * 0x60;
            if (((*(int *)(local_18 + iVar3 + 0x42c) == 0) &&
                ((*(int *)(local_18 + iVar3 + 0x44c) == 0 &&
                 (*(int *)(local_18 + iVar3 + 0x43c) == -1)))) ||
               (*(int *)(local_18 + iVar3 + 0x43c) == 4)) {
              local_2c = (uint)(local_20[0] != 0);
              *(uint *)(local_18 + iVar3 + 0x44c) = local_2c + 6 + local_8 * 2;
              if (*(int *)(local_18 + iVar3 + 0x438) == 0) {
                *(undefined4 *)(local_18 + iVar3 + 0x438) = 1;
              }
              local_20[local_2c] = 1;
            }
          }
        }
        local_18 = local_18 + 0x29e8;
      }
      *(ushort *)(in_ECX + 0x8a) =
           *(ushort *)(in_ECX + 0x8a) & ~(ushort)(1 << ((byte)local_8 & 0x1f));
    }
  }
  local_10 = &DAT_005ec218 + ((in_ECX + -0x6191b8) / 0x14a0) * 0x29e8;
  for (local_c = 5; local_c < 0x22; local_c = local_c + 1) {
    while (*(short *)(in_ECX + 0x44 + local_c * 2) != 0) {
      bVar1 = false;
      while (!bVar1) {
        iVar3 = thunk_FUN_00467260((int)*(short *)(local_10 + 0x29a8));
        iVar3 = iVar3 * 0x60;
        if ((((*(int *)(local_10 + iVar3 + 0x42c) == 0) && (*(int *)(local_10 + iVar3 + 0x44c) == 0)
             ) && (*(int *)(local_10 + iVar3 + 0x43c) == -1)) ||
           (*(int *)(local_10 + iVar3 + 0x43c) == 4)) {
          *(int *)(local_10 + iVar3 + 0x44c) = local_c;
          if (*(int *)(local_10 + iVar3 + 0x438) == 0) {
            *(undefined4 *)(local_10 + iVar3 + 0x438) = 1;
          }
          bVar1 = true;
        }
      }
      *(short *)(in_ECX + 0x44 + local_c * 2) = *(short *)(in_ECX + 0x44 + local_c * 2) + -1;
    }
  }
  return;
}
```

---

---

## FUN_00460334 — 0x460334

- Classification : internal
- Corps : `0x460334–0x4603e9`
- État : pseudocode obtenu
- Evidence : `ev_3801e674478efa33932d2ff7589215bbb82a0b7afd627721ab0bef88b456a7f7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401771` — `thunk_FUN_0045e660`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401cee` — `thunk_FUN_0040fd80`
- `0x4022d4` — `thunk_FUN_0045e6b1`
- `0x478410` — `FUN_00478410`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00460334(undefined4 param_1,int param_2)

{
  undefined4 *extraout_ECX;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_14b0 [1315];
  undefined4 uStack_24;
  undefined4 *puStack_20;
  undefined4 uStack_1c;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491bfc;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  FUN_00478410();
  uStack_1c = 0x460369;
  thunk_FUN_0045e660();
  local_8 = 0;
  if (param_2 == 0) {
    puVar2 = extraout_ECX;
    puVar3 = local_14b0;
    for (iVar1 = 0x528; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    uStack_1c = 0x14a0;
    puStack_20 = local_14b0;
    uStack_24 = 0x4603c6;
    thunk_FUN_0040fd80();
  }
  else {
    uStack_1c = 0x14a0;
    puStack_20 = local_14b0;
    uStack_24 = 0x46038a;
    thunk_FUN_0040fc15();
    puVar2 = local_14b0;
    puVar3 = extraout_ECX;
    for (iVar1 = 0x528; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
  }
  local_8 = 0xffffffff;
  uStack_1c = 0x4603d8;
  thunk_FUN_0045e6b1();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

---

## FUN_004603ea — 0x4603ea

- Classification : internal
- Corps : `0x4603ea–0x46044c`
- État : pseudocode obtenu
- Evidence : `ev_3d067f239a0c4360d132239edf0cb2b0d9080004e4fe8a8f080716927ecbdb77`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401771` — `thunk_FUN_0045e660`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004603ea(void)

{
  int in_ECX;
  undefined4 local_8;
  
  thunk_FUN_0045e660();
  *(undefined4 *)(in_ECX + 0x3c) = 0;
  *(undefined4 *)(in_ECX + 0x40) = 0;
  *(undefined4 *)(in_ECX + 0x14a0) = 1;
  for (local_8 = 0; local_8 < 0xf; local_8 = local_8 + 1) {
    *(undefined2 *)(in_ECX + 0x15f6 + local_8 * 2) = 0;
  }
  return in_ECX;
}
```

---

---

## FUN_0046044d — 0x46044d

- Classification : internal
- Corps : `0x46044d–0x46045f`
- État : pseudocode obtenu
- Evidence : `ev_c8b37da8f46285907c11986d613161dd207376da391b3f2730efa85023ae6950`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4022d4` — `thunk_FUN_0045e6b1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046044d(void)

{
  thunk_FUN_0045e6b1();
  return;
}
```

---

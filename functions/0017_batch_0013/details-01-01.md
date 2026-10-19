# 0017_batch_0013 — détails (1/3)

## FUN_0045d9c1 — 0x45d9c1

- Classification : internal
- Corps : `0x45d9c1–0x45da29`
- État : pseudocode obtenu
- Evidence : `ev_19648d1a4298a25e4233e9935d9a9e0a0a7fa9d024db82fcece593e65f45a8ee`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0045d9c1(short param_1)

{
  int iVar1;
  int local_8;
  
  iVar1 = thunk_FUN_0045c3bb();
  local_8 = (int)*(short *)(&DAT_006188e2 + param_1 * 0x2c);
  if ((*(ushort *)(&DAT_00619242 + *(int *)(iVar1 + 0x14) * 0x14a0) & 0x100) != 0) {
    local_8 = (local_8 << 1) / 3;
  }
  return local_8;
}
```

---

---

## FUN_0045da2a — 0x45da2a

- Classification : internal
- Corps : `0x45da2a–0x45da7f`
- État : pseudocode obtenu
- Evidence : `ev_9d597e786a377c398ee91b7ed8fb572d7088d0b6c9aba8813f1824d7895dfd9e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401636` — `thunk_FUN_0045d9c1`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045da2a(short param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined2 extraout_var;
  
  iVar2 = thunk_FUN_0045c3bb();
  sVar1 = *(short *)(iVar2 + 0x2c);
  iVar3 = thunk_FUN_0045d9c1(CONCAT22(extraout_var,param_1));
  if ((sVar1 < iVar3) || (*(short *)(iVar2 + 0x2a) < *(short *)(&DAT_006188e4 + param_1 * 0x2c))) {
    uVar4 = 0;
  }
  else {
    uVar4 = 1;
  }
  return uVar4;
}
```

---

---

## FUN_0045da80 — 0x45da80

- Classification : internal
- Corps : `0x45da80–0x45dcf3`
- État : pseudocode obtenu
- Evidence : `ev_0f9c0e1151dca8d181ee42ea559e71d3987676f2680c797f76c97d5b25bbba36`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401636` — `thunk_FUN_0045d9c1`
- `0x401690` — `thunk_FUN_0045da2a`
- `0x402004` — `thunk_FUN_0045d8f4`
- `0x40225c` — `thunk_FUN_00421ec1`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045da80(short param_1,short param_2,ushort param_3)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  short *in_ECX;
  uint uVar5;
  undefined *local_1c;
  undefined *local_18;
  undefined *local_14;
  
  iVar2 = thunk_FUN_0045c3bb();
  iVar3 = thunk_FUN_0045da2a(param_1);
  if (iVar3 == 0) {
    uVar4 = 0;
  }
  else {
    if ((((param_1 == 0xc) || (param_1 == 0xd)) || (param_1 == 0x13)) || (param_1 == 4)) {
      local_18 = (undefined *)(int)param_1;
      local_14 = (undefined *)0x0;
      if ((0 < (short)param_3) && ((short)param_3 < 0xf)) {
        local_18 = &DAT_005ec640 + (short)param_3 * 0x60 + *in_ECX * 0x29e8;
        local_14 = local_18;
      }
      if ((local_14 == (undefined *)0x0) || (0 < *(short *)(local_14 + 0x38))) {
        return 1;
      }
    }
    else if (param_1 == 5) {
      local_18 = (undefined *)0x0;
      if ((0 < (short)param_3) && ((short)param_3 < 0xf)) {
        local_18 = &DAT_005ec640 + (short)param_3 * 0x60 + *in_ECX * 0x29e8;
      }
      if (((local_18 == (undefined *)0x0) || (*(int *)(local_18 + 4) != 0)) ||
         (*(int *)(local_18 + 0x10) != 0)) {
        return 1;
      }
    }
    else {
      local_18 = (undefined *)(int)param_1;
      if (local_18 == (undefined *)0x6) {
        local_1c = (undefined *)0x0;
        if ((0 < (short)param_3) && ((short)param_3 < 0xf)) {
          local_18 = &DAT_005ec640 + (short)param_3 * 0x60 + *in_ECX * 0x29e8;
          local_1c = local_18;
        }
        if (((local_1c == (undefined *)0x0) || (*(int *)(local_1c + 4) != 1)) ||
           (*(int *)(local_1c + 0x10) != 0)) {
          return 1;
        }
      }
    }
    iVar3 = thunk_FUN_0045d8f4(CONCAT22((short)((uint)local_18 >> 0x10),param_1));
    if (iVar3 < 0) {
      uVar4 = 0;
    }
    else {
      iVar3 = in_ECX[iVar3 + 2] * 0x4c;
      thunk_FUN_00421ec1(0xffffffff);
      *(undefined4 *)(&DAT_006137f4 + iVar3) = 0x13;
      *(short *)(&DAT_006137f8 + iVar3) = param_2;
      *(ushort *)(&DAT_006137fa + iVar3) = param_3;
      *(short *)(&DAT_006137fc + iVar3) = param_1;
      *(undefined2 *)(&DAT_006137fe + iVar3) = 0;
      if (param_1 == 8) {
        *(undefined2 *)(&DAT_006137f8 + iVar3) = *(undefined2 *)(&DAT_006137c6 + iVar3);
        *(ushort *)(&DAT_006137fa + iVar3) = param_3 | param_2 << 8;
      }
      uVar5 = (uint)param_1;
      if ((uVar5 == 7) || (param_1 == 0x12)) {
        uVar5 = *(uint *)(&DAT_006137d4 + iVar3) | 0x100;
        *(uint *)(&DAT_006137d4 + iVar3) = uVar5;
        *(undefined4 *)(&DAT_006137dc + iVar3) = 0xfffff060;
      }
      sVar1 = thunk_FUN_0045d9c1(CONCAT22((short)(uVar5 >> 0x10),param_1));
      *(short *)(iVar2 + 0x2c) = *(short *)(iVar2 + 0x2c) - sVar1;
      *(short *)(iVar2 + 0x2a) =
           *(short *)(iVar2 + 0x2a) - *(short *)(&DAT_006188e4 + param_1 * 0x2c);
      uVar4 = 1;
    }
  }
  return uVar4;
}
```

---

---

## FUN_0045dcf4 — 0x45dcf4

- Classification : internal
- Corps : `0x45dcf4–0x45dd3b`
- État : pseudocode obtenu
- Evidence : `ev_fc6b52b072e8095c93f62d9e45ae254d04f83c96757ea63f35fcd1fd4b0fe166`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40135c` — `thunk_FUN_00452e2b`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045dcf4(void)

{
  undefined2 uVar1;
  int iVar2;
  int in_ECX;
  
  iVar2 = thunk_FUN_0045c3bb();
  *(undefined2 *)(in_ECX + 0x28) = *(undefined2 *)(iVar2 + 8);
  *(undefined4 *)(in_ECX + 0x2c) = 9;
  uVar1 = thunk_FUN_00452e2b();
  *(undefined2 *)(in_ECX + 0x30) = uVar1;
  *(undefined2 *)(in_ECX + 0x32) = 0;
  return;
}
```

---

---

## FUN_0045dd3c — 0x45dd3c

- Classification : internal
- Corps : `0x45dd3c–0x45ddb7`
- État : pseudocode obtenu
- Evidence : `ev_ee9345eeb1e013f0110fa40de57e731bede050d440d9d9b38e7c1e4aca0fdb18`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0045dd3c(void)

{
  int iVar1;
  int local_10;
  
  iVar1 = thunk_FUN_0045c3bb();
  local_10 = (int)*(short *)(iVar1 + 0x2a);
  if (((((*(ushort *)(&DAT_00619242 + *(int *)(iVar1 + 0x14) * 0x14a0) & 0x1000) != 0) &&
       (*(int *)(iVar1 + 0x10) == 0x2c)) && (*(int *)(iVar1 + 0x10) == 0x2d)) &&
     (*(int *)(iVar1 + 0x10) == 0x2e)) {
    local_10 = (local_10 << 2) / 3;
  }
  return local_10;
}
```

---

---

## FUN_0045ddb8 — 0x45ddb8

- Classification : internal
- Corps : `0x45ddb8–0x45de1f`
- État : pseudocode obtenu
- Evidence : `ev_0c06e5833d42d247636163ebd4dd8d5e5ec6b362123d017209719d0884498d6c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40141f` — `thunk_FUN_0045dd3c`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0045ddb8(int param_1)

{
  int iVar1;
  short local_c;
  int local_8;
  
  local_8 = thunk_FUN_0045dd3c();
  iVar1 = thunk_FUN_0045c3bb();
  local_c = *(short *)(iVar1 + 0x2a);
  if (param_1 <= local_8) {
    local_8 = param_1;
  }
  if (param_1 <= local_c) {
    local_c = (short)param_1;
  }
  *(short *)(iVar1 + 0x2a) = *(short *)(iVar1 + 0x2a) - local_c;
  return local_8;
}
```

---

---

## FUN_0045de20 — 0x45de20

- Classification : internal
- Corps : `0x45de20–0x45dea6`
- État : pseudocode obtenu
- Evidence : `ev_4aee340e1d5ec3256b2c9bafdf5e80664667ad27ec510cf86f5cfbbb7e7033ef`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401401` — `thunk_FUN_0041e427`
- `0x40173a` — `thunk_FUN_004672a6`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045de20(void)

{
  short *psVar1;
  int iVar2;
  short *in_ECX;
  undefined4 local_1c;
  short local_10 [4];
  short local_8 [2];
  
  psVar1 = (short *)thunk_FUN_0045c3bb();
  thunk_FUN_0041e427(CONCAT22((short)((uint)local_10 >> 0x10),in_ECX[0x18]),local_8,local_10);
  iVar2 = thunk_FUN_004672a6((int)*psVar1,(int)psVar1[1],(int)local_8[0],(int)local_10[0]);
  if (((*(int *)(in_ECX + 0x16) == 9) && (in_ECX[0x14] == *in_ECX)) && (iVar2 < 0x14)) {
    local_1c = 1;
  }
  else {
    local_1c = 0;
  }
  return local_1c;
}
```

---

---

## FUN_0045dea7 — 0x45dea7

- Classification : internal
- Corps : `0x45dea7–0x45df34`
- État : pseudocode obtenu
- Evidence : `ev_1e240befa60916cdd3d1fb38c37e8318961abbf3af473289d29b38c9080009bd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401875` — `thunk_FUN_0040fc15`
- `0x401cee` — `thunk_FUN_0040fd80`
- `0x4021cb` — `thunk_FUN_0045c2b0`
- `0x402428` — `thunk_FUN_0045c2c6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045dea7(undefined4 param_1,int param_2)

{
  undefined4 *in_ECX;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_74 [25];
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491bd9;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0045c2b0();
  local_8 = 0;
  if (param_2 == 0) {
    puVar2 = local_74;
    for (iVar1 = 0x19; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *in_ECX;
      in_ECX = in_ECX + 1;
      puVar2 = puVar2 + 1;
    }
    thunk_FUN_0040fd80(local_74,100);
  }
  else {
    thunk_FUN_0040fc15(local_74,100);
    puVar2 = local_74;
    for (iVar1 = 0x19; iVar1 != 0; iVar1 = iVar1 + -1) {
      *in_ECX = *puVar2;
      puVar2 = puVar2 + 1;
      in_ECX = in_ECX + 1;
    }
  }
  local_8 = 0xffffffff;
  thunk_FUN_0045c2c6();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

---

## FUN_0045e660 — 0x45e660

- Classification : internal
- Corps : `0x45e660–0x45e6b0`
- État : pseudocode obtenu
- Evidence : `ev_4f992879ddb59f1d994a25472ffa8e0d05df263c6928df70291b20953eb4d3e5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b20` — `_memset`
- `0x478210` — ``eh_vector_constructor_iterator'`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0045e660(void)

{
  int in_ECX;
  
  _eh_vector_constructor_iterator_
            ((void *)(in_ECX + 0xf8),100,0x30,thunk_FUN_0045c2b0,thunk_FUN_0045c2c6);
  *(undefined4 *)(in_ECX + 0x3c) = 0;
  *(undefined4 *)(in_ECX + 0x40) = 0;
  _memset((void *)(in_ECX + 0x44),0,0x48);
  return in_ECX;
}
```

---

---

## FUN_0045e6b1 — 0x45e6b1

- Classification : internal
- Corps : `0x45e6b1–0x45e6d2`
- État : pseudocode obtenu
- Evidence : `ev_d7c9820d6049e795d1d621d8814818ea3ef67eeb9fc56f59db892a1cc6222204`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4782b0` — `FUN_004782b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045e6b1(void)

{
  int in_ECX;
  
  FUN_004782b0(in_ECX + 0xf8,100,0x30,thunk_FUN_0045c2c6);
  return;
}
```

---

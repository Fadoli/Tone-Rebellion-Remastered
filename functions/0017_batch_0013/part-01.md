# 0017_batch_0013 — détails (1/6)

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

## FUN_0045e6d3 — 0x45e6d3

- Classification : internal
- Corps : `0x45e6d3–0x45eaa6`
- État : pseudocode obtenu
- Evidence : `ev_40029ca226cb3025b370307705f49a00c27de614f0bce2bbaee8d6771a69c66c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40101e` — `thunk_FUN_00462285`
- `0x40173a` — `thunk_FUN_004672a6`
- `0x4019b5` — `thunk_FUN_0046562b`
- `0x401bef` — `thunk_FUN_00453cf5`
- `0x4021ad` — `thunk_FUN_004641de`
- `0x472c6c` — `__ftol`
- `0x477599` — `FUN_00477599`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045e6d3(int param_1)

{
  short sVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int in_ECX;
  int local_38;
  int local_34;
  int local_30;
  undefined1 *local_20;
  short *local_1c;
  int local_18;
  int local_14;
  int local_10;
  uint local_8;
  
  iVar4 = (in_ECX + -0x6191b8) / 0x14a0;
  local_14 = 0;
  local_34 = param_1;
  local_8 = param_1 + 1;
  if (param_1 == -1) {
    local_34 = 0;
    local_8 = (uint)DAT_006136b0;
  }
  local_20 = &DAT_005ec218 + local_34 * 0x29e8;
  for (local_18 = local_34; local_18 < (int)local_8; local_18 = local_18 + 1) {
    uVar3 = thunk_FUN_00462285(iVar4);
    *(undefined2 *)(in_ECX + local_18 * 2) = uVar3;
    *(undefined2 *)(in_ECX + 0x1e + local_18 * 2) = 0;
    local_1c = (short *)(local_20 + 0x428);
    for (local_38 = 0; local_38 < *(short *)(local_20 + 0x29a8); local_38 = local_38 + 1) {
      if ((((*(int *)((int)local_1c + 4) == 0) && (iVar5 = thunk_FUN_00453cf5(iVar4), iVar5 != 0))
          && (*(int *)((int)local_1c + 0x10) != 0)) && ((*(uint *)((int)local_1c + 0x1c) & 1) != 0))
      {
        iVar5 = thunk_FUN_004641de(iVar4,*(undefined4 *)((int)local_1c + 0x10));
        *(short *)(in_ECX + 0x1e + local_18 * 2) =
             *(short *)(in_ECX + 0x1e + local_18 * 2) + *(short *)(iVar5 + 0xc);
      }
      local_1c = (short *)((int)local_1c + 0x60);
    }
    local_20 = local_20 + 0x29e8;
  }
  *(undefined4 *)(in_ECX + 0x3c) = 0;
  for (local_18 = 0; local_18 < (int)(uint)DAT_006136b0; local_18 = local_18 + 1) {
    *(int *)(in_ECX + 0x3c) = *(int *)(in_ECX + 0x3c) + (int)*(short *)(in_ECX + local_18 * 2);
    local_14 = local_14 + *(short *)(in_ECX + 0x1e + local_18 * 2);
  }
  FUN_00477599((double)*(int *)(in_ECX + 0x3c),0,0x3fe00000);
  uVar6 = __ftol();
  *(undefined4 *)(in_ECX + 0x3c) = uVar6;
  if ((*(ushort *)(in_ECX + 0x8a) & 0x2000) != 0) {
    local_14 = (local_14 * 0x11) / 0x14;
  }
  iVar5 = thunk_FUN_0046562b(iVar4,0xffffffff);
  local_14 = local_14 + iVar5;
  if (*(int *)(in_ECX + 0x3c) < local_14) {
    local_14 = *(int *)(in_ECX + 0x3c);
  }
  *(int *)(in_ECX + 0x40) = *(int *)(in_ECX + 0x3c) - local_14;
  *(undefined2 *)(in_ECX + 0x13cc) = *(undefined2 *)(in_ECX + 0x13c8);
  sVar1 = *(short *)(in_ECX + 0x13c8);
  iVar5 = sVar1 * 0x29e8;
  sVar2 = *(short *)(in_ECX + 0x13ca);
  local_1c = (short *)(&DAT_005ec640 + iVar5);
  local_10 = 0;
  local_30 = -1;
  for (local_18 = 0; local_18 < (short)(&DAT_005eebc0)[sVar1 * 0x14f4]; local_18 = local_18 + 1) {
    if (((*(int *)(local_1c + 2) == 1) &&
        ((iVar7 = thunk_FUN_004672a6((int)*local_1c,(int)local_1c[1],
                                     (int)*(short *)(&DAT_005ec640 + sVar2 * 0x60 + iVar5),
                                     (int)*(short *)((int)(&DAT_005ec640 + sVar2 * 0x60 + iVar5) + 2
                                                    )), local_30 == -1 || (iVar7 < local_10)))) &&
       (((int)(char)local_1c[0x11] & 1 << ((byte)iVar4 & 0x1f)) != 0)) {
      local_30 = local_18;
      local_10 = iVar7;
    }
    local_1c = local_1c + 0x30;
  }
  if (local_30 == -1) {
    *(undefined2 *)(in_ECX + 0x13cc) = *(undefined2 *)(in_ECX + 0x13c4);
    local_1c = (short *)(&DAT_005ec640 + *(int *)(in_ECX + 0x13c4) * 0x29e8);
    for (local_18 = 0; local_18 < (short)(&DAT_005eebc0)[*(int *)(in_ECX + 0x13c4) * 0x14f4];
        local_18 = local_18 + 1) {
      if ((*(int *)((int)local_1c + 4) == 1) &&
         (((int)*(char *)((int)local_1c + 0x22) & 1 << ((byte)iVar4 & 0x1f)) != 0)) {
        local_30 = local_18;
        break;
      }
      local_1c = (short *)((int)local_1c + 0x60);
    }
  }
  *(undefined2 *)(in_ECX + 0x13ce) = (undefined2)local_30;
  return;
}
```

---

## FUN_0045eaa7 — 0x45eaa7

- Classification : internal
- Corps : `0x45eaa7–0x45ee25`
- État : pseudocode obtenu
- Evidence : `ev_d0241191e19be6e3ec7ab4c4a16172c22e772b518c82aeef201ad3125475226d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013c0` — `thunk_FUN_004655b2`
- `0x4017bc` — `thunk_FUN_0045f807`
- `0x4019b5` — `thunk_FUN_0046562b`
- `0x401d1b` — `thunk_FUN_004662b7`
- `0x401d9d` — `thunk_FUN_00460072`
- `0x401f69` — `thunk_FUN_004532e2`
- `0x4020b3` — `thunk_FUN_00466533`
- `0x4021c1` — `thunk_FUN_00453cba`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045eaa7(void)

{
  undefined2 uVar1;
  int in_ECX;
  undefined1 local_44 [2];
  undefined2 local_42;
  undefined2 local_40;
  undefined2 local_3a;
  undefined2 local_38;
  short local_36;
  int local_34;
  int local_30;
  undefined4 local_2c;
  uint local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined1 *local_8;
  
  local_24 = (in_ECX + -0x6191b8) / 0x14a0;
  local_8 = &DAT_005ec218 + *(short *)(in_ECX + 0x13c8) * 0x29e8;
  local_20 = local_24;
  local_14 = thunk_FUN_0046562b(local_24,0xffffffff);
  if (((local_14 < 1) || (*(int *)(in_ECX + 0x3c) < 1)) && (*(int *)(in_ECX + 0x90) == 0)) {
    if (DAT_004befe0 == 0) {
      *(undefined4 *)(in_ECX + 0x90) = 1;
      local_2c = 0xb;
      local_28 = local_20 << 0x10 | 3;
      thunk_FUN_004655b2(&local_2c);
    }
    else {
      thunk_FUN_00460072();
    }
  }
  else if (*(int *)(in_ECX + 0x90) == 0) {
    local_30 = 0;
    for (local_1c = 0; local_1c < local_14; local_1c = local_1c + 1) {
      if (*(int *)(&DAT_006137bc + (short)(&DAT_00618fb4)[local_1c] * 0x4c) == 0) {
        local_30 = local_30 + 1;
      }
    }
    if (((4 < *(int *)(in_ECX + 0x40)) && (local_30 < *(int *)(in_ECX + 0x3c) / 2)) &&
       (*(short *)(in_ECX + 0x13ce) != -1)) {
      *(int *)(in_ECX + 0x8c) = *(int *)(in_ECX + 0x8c) + 1;
    }
    if ((300 < *(int *)(in_ECX + 0x8c)) && (*(short *)(in_ECX + 0x13ce) != -1)) {
      thunk_FUN_004532e2(local_24,0);
      *(undefined4 *)(in_ECX + 0x8c) = 0;
    }
  }
  local_18 = 0;
  for (local_1c = 0; local_1c < (int)(uint)DAT_006136b0; local_1c = local_1c + 1) {
    local_18 = local_18 + *(int *)(&DAT_005eebc4 + local_20 * 4 + local_1c * 0x29e8);
  }
  local_c = thunk_FUN_0045f807();
  if (local_18 < 6) {
    if (3 < local_18) {
      thunk_FUN_00453cba(1);
    }
  }
  else {
    thunk_FUN_00453cba(2);
  }
  local_10 = *(short *)(local_c + 0x4a) * 0x32 + 0x96;
  for (local_1c = 0; local_1c < 3; local_1c = local_1c + 1) {
    local_34 = (int)*(short *)(local_c + 0x2c);
    if (local_1c == 0) {
      local_34 = (int)*(short *)(local_c + 0x28);
    }
    else if (local_1c == 1) {
      local_34 = (int)*(short *)(local_c + 0x2a);
    }
    if ((((*(short *)(in_ECX + 0x13d6 + local_1c * 2) == -1) &&
         (*(short *)(in_ECX + 0x13d0 + local_1c * 2) == 2)) && (local_34 < local_10)) &&
       ((*(uint *)(local_c + 0x1c) & 1) != 0)) {
      _memset(local_44,0,0x10);
      local_42 = (undefined2)((in_ECX + -0x6191b8) / 0x14a0);
      local_40 = 4;
      local_38 = *(undefined2 *)(in_ECX + 0x13ca);
      local_3a = *(undefined2 *)(in_ECX + 0x13c8);
      local_36 = (short)local_1c + 1;
      uVar1 = thunk_FUN_004662b7(local_44);
      *(undefined2 *)(in_ECX + 0x13d6 + local_1c * 2) = uVar1;
    }
    else if ((*(short *)(in_ECX + 0x13d6 + local_1c * 2) != -1) &&
            (((*(short *)(in_ECX + 0x13d0 + local_1c * 2) != 2 || (local_10 <= local_34)) ||
             ((*(uint *)(local_c + 0x1c) & 1) == 0)))) {
      thunk_FUN_00466533((int)*(short *)(in_ECX + 0x13d6 + local_1c * 2));
      *(undefined2 *)(in_ECX + 0x13d6 + local_1c * 2) = 0xffff;
    }
  }
  return;
}
```

---

## FUN_0045ee26 — 0x45ee26

- Classification : internal
- Corps : `0x45ee26–0x45efd1`
- État : pseudocode obtenu
- Evidence : `ev_60aa716f59e3c4630381a13fefd3f471c0859d3647a755de7a8f9d51043e6bac`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401dcf` — `thunk_FUN_0045c3fe`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4023bf` — `thunk_FUN_0045c3bb`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a4544` — "(int)loc->mOwner == mytribe"
- `0x4a4560` — "C:\\float\\src\\tribe.cpp"
- `0x4a4578` — "(int)loc->mItem >= PIT_Recruiter1 && (int)loc->mItem <= PIT_Spec2"
- `0x4a45bc` — "C:\\float\\src\\tribe.cpp"
- `0x4a45d4` — "bld->mID>=0 && bld->mID<10"
- `0x4a45f0` — "C:\\float\\src\\tribe.cpp"

### Pseudocode Ghidra

```c
int FUN_0045ee26(int param_1)

{
  int iVar1;
  int in_ECX;
  int local_28;
  short local_24 [10];
  int local_10;
  short local_c;
  int local_8;
  
  local_10 = (in_ECX + -0x6191b8) / 0x14a0;
  if (*(int *)(param_1 + 0x14) != local_10) {
    thunk_FUN_00414b64(s_C__float_src_tribe_cpp_004a4560,0x122,
                       s__int_loc_>mOwner____mytribe_004a4544);
  }
  if ((*(int *)(param_1 + 0x10) < 0x2c) || (0x32 < *(int *)(param_1 + 0x10))) {
    thunk_FUN_00414b64(s_C__float_src_tribe_cpp_004a45bc,0x124,
                       s__int_loc_>mItem_>__PIT_Recruiter_004a4578);
  }
  local_8 = 0;
  local_28 = in_ECX + 0xf8;
  _memset(local_24,0,0x14);
  for (local_c = 0; local_c < 0x30; local_c = local_c + 1) {
    iVar1 = thunk_FUN_0045c3bb();
    if ((iVar1 != 0) &&
       (iVar1 = thunk_FUN_0045c3bb(), *(int *)(param_1 + 0x10) == *(int *)(iVar1 + 0x10))) {
      if ((*(short *)(local_28 + 0x60) < 0) || (9 < *(short *)(local_28 + 0x60))) {
        thunk_FUN_00414b64(s_C__float_src_tribe_cpp_004a45f0,0x12d,
                           s_bld_>mID>_0____bld_>mID<10_004a45d4);
      }
      local_24[*(short *)(local_28 + 0x60)] = 1;
    }
    if ((*(short *)(local_28 + 2) == -1) && (local_8 == 0)) {
      thunk_FUN_0045c3fe(param_1);
      local_8 = local_28;
    }
    local_28 = local_28 + 100;
  }
  if (local_8 != 0) {
    *(undefined2 *)(local_8 + 0x60) = 0;
    for (local_c = 0; local_c < 10; local_c = local_c + 1) {
      if (local_24[local_c] == 0) {
        *(short *)(local_8 + 0x60) = local_c;
        return local_8;
      }
    }
  }
  return local_8;
}
```

---

## FUN_0045efd2 — 0x45efd2

- Classification : internal
- Corps : `0x45efd2–0x45f074`
- État : pseudocode obtenu
- Evidence : `ev_cd7d302221a1831b9b4fb986ba8c0af04c4286fdc263ec3082d25dda498827fa`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4022d9` — `thunk_FUN_0045c5b8`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045efd2(int param_1)

{
  int in_ECX;
  short *local_18;
  short local_10;
  
  local_18 = (short *)(in_ECX + 0xf8);
  local_10 = 0;
  while( true ) {
    if (0x2f < local_10) {
      return 0;
    }
    if ((*local_18 == *(short *)(param_1 + 8)) &&
       ((int)local_18[1] ==
        (param_1 - (int)(&DAT_005ec640 + *(short *)(param_1 + 8) * 0x29e8)) / 0x60)) break;
    local_10 = local_10 + 1;
    local_18 = local_18 + 0x32;
  }
  thunk_FUN_0045c5b8();
  return 1;
}
```

---

## FUN_0045f075 — 0x45f075

- Classification : internal
- Corps : `0x45f075–0x45f0cc`
- État : pseudocode obtenu
- Evidence : `ev_a89c46b6515652feb153d509ef442bda08bac0b9ec9c29737611d97dddafa06d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a4608` — "obj >= 0 && obj < POT_NumTypes"
- `0x4a4628` — "C:\\float\\src\\tribe.cpp"

### Pseudocode Ghidra

```c
void FUN_0045f075(int param_1,short param_2)

{
  int in_ECX;
  
  if ((param_1 < 0) || (0x22 < param_1)) {
    thunk_FUN_00414b64(s_C__float_src_tribe_cpp_004a4628,0x15f,
                       s_obj_>__0____obj_<_POT_NumTypes_004a4608);
  }
  *(short *)(in_ECX + 0x44 + param_1 * 2) = *(short *)(in_ECX + 0x44 + param_1 * 2) + param_2;
  return;
}
```

---

## FUN_0045f0cd — 0x45f0cd

- Classification : internal
- Corps : `0x45f0cd–0x45f120`
- État : pseudocode obtenu
- Evidence : `ev_d1eb856703566f1ca289bb29b21d792fea8eb84294b19f75222b6f90a94357a3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0045f0cd(void)

{
  int in_ECX;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  for (local_c = 0; local_c < 0xe; local_c = local_c + 1) {
    if (((int)*(short *)(in_ECX + 0x8a) & 1 << ((byte)local_c & 0x1f)) != 0) {
      local_8 = local_8 + 1;
    }
  }
  return local_8;
}
```

---

## FUN_0045f121 — 0x45f121

- Classification : internal
- Corps : `0x45f121–0x45f2a0`
- État : pseudocode obtenu
- Evidence : `ev_790f83b443e86779c7c20c061fe4cce3e6966b77b46caeebce4542b0f55c7df1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021ad` — `thunk_FUN_004641de`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined2 FUN_0045f121(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int in_ECX;
  int local_1c;
  int local_10;
  int local_c;
  
  local_10 = 0;
  iVar2 = (in_ECX + -0x6191b8) / 0x14a0;
  for (local_c = 0; local_c < (int)(uint)DAT_006136b0; local_c = local_c + 1) {
    if (*(int *)(&DAT_005eebc4 + iVar2 * 4 + local_c * 0x29e8) != 0) {
      local_10 = local_10 + 1;
    }
  }
  *(undefined2 *)(in_ECX + 0xd4) = 0;
  local_c = 0;
  do {
    if (7 < local_c) {
      return *(undefined2 *)(in_ECX + 0xd4);
    }
    iVar1 = *(int *)(&DAT_004a4468 + local_c * 4);
    piVar3 = (int *)thunk_FUN_004641de(iVar2,iVar1);
    if ((*piVar3 <= *(int *)(param_1 + 0xc)) && ((short)piVar3[1] != -1)) {
      if ((0x2b < iVar1) && (iVar1 < 0x30)) {
        if (DAT_006136b2 == 0) {
          local_1c = (int)(char)(&DAT_004a42b8)[(iVar1 + -0x2c) * 3];
        }
        else if (DAT_006136b2 == 1) {
          local_1c = (int)(char)(&DAT_004a42c8)[(iVar1 + -0x2c) * 3];
        }
        else {
          local_1c = (int)(char)(&DAT_004a42d8)[(iVar1 + -0x2c) * 3];
        }
        if (local_10 < local_1c) goto LAB_0045f199;
      }
      *(int *)(in_ECX + 0x94 + (uint)*(ushort *)(in_ECX + 0xd4) * 4) = iVar1;
      *(short *)(in_ECX + 0xd4) = *(short *)(in_ECX + 0xd4) + 1;
    }
LAB_0045f199:
    local_c = local_c + 1;
  } while( true );
}
```

---

## FUN_0045f2a1 — 0x45f2a1

- Classification : internal
- Corps : `0x45f2a1–0x45f336`
- État : pseudocode obtenu
- Evidence : `ev_166ec7236cb49a5bd45dcbc859b69f029d1132243f92ee2e155015d72a50dedd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021ad` — `thunk_FUN_004641de`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045f2a1(int param_1,undefined4 param_2,int *param_3,int *param_4,int *param_5)

{
  int iVar1;
  
  *param_5 = 0xffff;
  *param_4 = 0xffff;
  *param_3 = 0xffff;
  if (param_1 != 0) {
    iVar1 = thunk_FUN_004641de(*(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x10));
    *param_3 = (int)*(short *)(iVar1 + 6) * (*(short *)(param_1 + 0x4a) + 1);
    *param_4 = (int)*(short *)(iVar1 + 10) * (*(short *)(param_1 + 0x4a) + 1);
    *param_5 = (int)*(short *)(iVar1 + 8) * (*(short *)(param_1 + 0x4a) + 1);
  }
  return;
}
```

---

## FUN_0045f337 — 0x45f337

- Classification : internal
- Corps : `0x45f337–0x45f4f4`
- État : pseudocode obtenu
- Evidence : `ev_d22a1eae81f90bf0a91044b05de09fc09d58c4b47dfc01072416258ddeaa8174`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014e7` — `thunk_FUN_0045035a`
- `0x4017bc` — `thunk_FUN_0045f807`
- `0x4018b6` — `thunk_FUN_0045ff3f`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x401c94` — `thunk_FUN_0045f2a1`
- `0x4020bd` — `thunk_FUN_0045c9fe`
- `0x4021ad` — `thunk_FUN_004641de`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045f337(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int in_ECX;
  undefined2 extraout_var;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (param_1 != 0) {
    uVar1 = thunk_FUN_0045035a();
    iVar2 = thunk_FUN_0045ff3f(CONCAT22(extraout_var,*(undefined2 *)(param_1 + 8)),uVar1);
    if (iVar2 == 0) {
      local_8 = thunk_FUN_00450385();
      if ((local_8 != 0) && (iVar2 = thunk_FUN_0045c9fe(), iVar2 != 0)) {
        return 0;
      }
      local_c = (in_ECX + -0x6191b8) / 0x14a0;
      if ((((param_2 == 0) ||
           ((((*(int *)(param_2 + 4) == 0 && (*(int *)(param_2 + 0x14) == -1)) &&
             (((int)*(char *)(param_2 + 0x22) & 1 << ((byte)local_c & 0x1f)) != 0)) &&
            (((*(int *)(param_2 + 0x10) != 1 || (*(int *)(param_2 + 0x24) < 5)) ||
             (0x21 < *(int *)(param_2 + 0x24))))))) &&
          (((*(int *)(param_1 + 0x14) == local_c && (0x24 < *(int *)(param_1 + 0x10))) &&
           ((*(int *)(param_1 + 0x10) < 0x35 &&
            (((*(int *)(param_1 + 0x10) != 0x28 && ((*(uint *)(param_1 + 0x1c) & 0x90) == 0)) &&
             (local_10 = thunk_FUN_0045f807(), local_10 != 0)))))))) &&
         ((thunk_FUN_0045f2a1(param_1,param_2,&local_1c,&local_18,&local_14),
          *(int *)(in_ECX + 0x13c0) != 0 ||
          (((local_1c <= *(short *)(local_10 + 0x28) && (local_18 <= *(short *)(local_10 + 0x2a)))
           && (local_14 <= *(short *)(local_10 + 0x2c))))))) {
        if (param_2 != 0) {
          piVar3 = (int *)thunk_FUN_004641de(local_c,*(undefined4 *)(param_1 + 0x10));
          local_20 = *piVar3;
          if (1 < *(short *)(param_1 + 0x4a)) {
            local_20 = local_20 + 1;
          }
          if (*(int *)(param_2 + 0xc) < local_20) {
            return 0;
          }
        }
        return 1;
      }
    }
  }
  return 0;
}
```

---

## FUN_0045f4f5 — 0x45f4f5

- Classification : internal
- Corps : `0x45f4f5–0x45f5c4`
- État : pseudocode obtenu
- Evidence : `ev_598cfe2b014b15e607c8b41ac943b5dd6af4e3db3c818406a1653591e00c406a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014e7` — `thunk_FUN_0045035a`
- `0x4017bc` — `thunk_FUN_0045f807`
- `0x401c94` — `thunk_FUN_0045f2a1`
- `0x401faa` — `thunk_FUN_0045f337`
- `0x402180` — `thunk_FUN_004533fb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045f4f5(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  int in_ECX;
  short local_14 [2];
  int local_10;
  short local_c [2];
  short local_8 [2];
  
  if (((*(int *)(in_ECX + 0x13c0) == 0) && (iVar2 = thunk_FUN_0045f337(param_1,0), iVar2 != 0)) &&
     (local_10 = thunk_FUN_0045f807(), local_10 != 0)) {
    thunk_FUN_0045f2a1(param_1,0,local_14,local_8,local_c);
    *(short *)(local_10 + 0x28) = *(short *)(local_10 + 0x28) - local_14[0];
    *(short *)(local_10 + 0x2a) = *(short *)(local_10 + 0x2a) - local_8[0];
    *(short *)(local_10 + 0x2c) = *(short *)(local_10 + 0x2c) - local_c[0];
    *(undefined2 *)(in_ECX + 0x13ba) = *(undefined2 *)(param_1 + 8);
    uVar1 = thunk_FUN_0045035a();
    *(undefined2 *)(in_ECX + 0x13bc) = uVar1;
    thunk_FUN_004533fb();
    *(undefined4 *)(in_ECX + 0x13c0) = 1;
  }
  return;
}
```

---


# 0012_batch_0008 — détails (1/2)

## FUN_00438379 — 0x438379

- Classification : internal
- Corps : `0x438379–0x43842b`
- État : pseudocode obtenu
- Evidence : `ev_2a9ff8882cdd23ea1b521c03fde5d04a51b9a21e4a323f2e11cf13dcc756584a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401bf4` — `thunk_FUN_0042970c`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00438379(short param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int in_ECX;
  int iVar3;
  undefined4 local_14;
  
  local_14 = param_2 - *(int *)(in_ECX + 0xc);
  iVar3 = (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) + 1;
  iVar1 = (int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2;
  iVar2 = iVar1 / 2;
  if (local_14 < iVar2) {
    local_14 = iVar2;
  }
  if (iVar3 - iVar2 < local_14) {
    local_14 = iVar3 - iVar2;
  }
  thunk_FUN_0042970c(0x3d,((local_14 - iVar2) * 1000) / (iVar3 - iVar1),param_1 == 6);
  return 1;
}
```

---

---

## FUN_0043842c — 0x43842c

- Classification : internal
- Corps : `0x43842c–0x4384e1`
- État : pseudocode obtenu
- Evidence : `ev_6e14e8267ba09d1cad538fe01273c8b56b076401cdf2fd0b5a6c46d5291a06ab`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402491` — `thunk_FUN_0042dd0f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043842c(undefined4 param_1,int param_2,int param_3,int param_4,int param_5)

{
  int local_10;
  int local_c;
  undefined1 local_8;
  
  local_8 = thunk_FUN_0042dd0f(2);
  switch(param_1) {
  case 0:
    local_8 = thunk_FUN_0042dd0f(1);
    break;
  case 1:
    local_8 = thunk_FUN_0042dd0f(0);
    break;
  case 2:
    local_8 = thunk_FUN_0042dd0f(4);
    break;
  case 3:
    local_8 = thunk_FUN_0042dd0f(5);
  }
  for (local_c = -1; local_c < 2; local_c = local_c + 1) {
    for (local_10 = -1; local_10 < 2; local_10 = local_10 + 1) {
      *(undefined1 *)(param_4 + *(int *)(param_5 + (param_3 + local_10) * 4) + param_2 + local_c) =
           local_8;
    }
  }
  return;
}
```

---

---

## FUN_00438a90 — 0x438a90

- Classification : internal
- Corps : `0x438a90–0x438a9c`
- État : pseudocode obtenu
- Evidence : `ev_b3ce1ae09d752ac6ba0a25d3654d598dd905a5cca45f7e9e4f4f7961aec85f49`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00438a90(void)

{
  return;
}
```

---

---

## FUN_00438a9d — 0x438a9d

- Classification : internal
- Corps : `0x438a9d–0x438abb`
- État : pseudocode obtenu
- Evidence : `ev_6a79993d433d61b1683eca23fed98f18922a28e41edca773c529827fdc4372ab`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00438a9d(void)

{
  undefined4 *in_ECX;
  
  thunk_FUN_00429243();
  *in_ECX = &PTR_LAB_00494308;
  return in_ECX;
}
```

---

---

## FUN_00438abc — 0x438abc

- Classification : internal
- Corps : `0x438abc–0x438ad7`
- État : pseudocode obtenu
- Evidence : `ev_c436aad466c85dd8c3402a994117a71941822f3a31e58580503c4386b632a2dd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00438abc(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494308;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_00438ad8 — 0x438ad8

- Classification : internal
- Corps : `0x438ad8–0x438ae2`
- État : pseudocode obtenu
- Evidence : `ev_ec5212a12fe63b8291967b5ee7ea57dbf84e72442931cf2901ab2998c66ad137`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00438ad8(void)

{
  return;
}
```

---

---

## FUN_00438ae3 — 0x438ae3

- Classification : internal
- Corps : `0x438ae3–0x438b04`
- État : pseudocode obtenu
- Evidence : `ev_717fc4c131acf838f7a66f0b9daf4d15e668b3e30ea9a31854a6a0156a97c8d7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00438ae3(undefined2 param_1,undefined4 param_2,undefined4 param_3)

{
  thunk_FUN_004293c6(param_1,param_2,param_3);
  return;
}
```

---

---

## FUN_00438b05 — 0x438b05

- Classification : internal
- Corps : `0x438b05–0x43907b`
- État : pseudocode obtenu
- Evidence : `ev_7b9ce74c6829ccd438744897ea397c08a2989df9595646ca928d2ced36381461`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40146f` — `thunk_FUN_0042d87c`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x402022` — `thunk_FUN_00406604`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472c6c` — `__ftol`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00438b05(void)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int in_ECX;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int local_b4;
  int local_b0;
  int local_9c;
  int local_94 [4];
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  undefined4 local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50 [5];
  int local_3c;
  int local_38;
  int local_34 [12];
  
  uVar2 = thunk_FUN_0042d28f();
  *(undefined4 *)(in_ECX + 8) = uVar2;
  local_34[0] = 0x3e;
  local_34[1] = 0x6d;
  local_34[2] = 0x3e;
  local_34[3] = 0xf;
  local_50[0] = 0x14f;
  local_50[1] = 0x17e;
  local_50[2] = 0x1ad;
  local_50[3] = 0x17e;
  local_34[8] = 0x4d;
  local_34[9] = 0x69;
  local_34[10] = 0x4d;
  local_34[0xb] = 0x33;
  local_34[4] = 0x174;
  local_34[5] = 0x18d;
  local_34[6] = 0x1aa;
  local_34[7] = 0x18d;
  local_78 = DAT_00618e4c / 0x594;
  if (6 < local_78) {
    local_78 = 6;
  }
  local_6c = 0x476;
  local_80 = DAT_00618e50 / 0x476;
  if (6 < local_80) {
    local_80 = 6;
  }
  local_50[4] = DAT_0049f538;
  piVar6 = (int *)(in_ECX + 8);
  piVar7 = local_94;
  for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar7 = *piVar6;
    piVar6 = piVar6 + 1;
    piVar7 = piVar7 + 1;
  }
  local_94[1] = local_34[8] + -3;
  local_94[3] = local_34[8] + 3;
  local_94[2] = local_34[4] + -5;
  local_84 = local_34[6] + 5;
  uVar1 = thunk_FUN_0042dd0f(0);
  thunk_FUN_00406604(local_94,uVar1);
  local_94[1] = local_34[0xb] + -5;
  local_94[3] = local_34[9] + 5;
  local_94[2] = local_34[7] + -3;
  local_84 = local_34[7] + 3;
  uVar1 = thunk_FUN_0042dd0f(0);
  thunk_FUN_00406604(local_94,uVar1);
  for (local_5c = 0; local_5c < 4; local_5c = local_5c + 1) {
    if ((local_50[4] & 1U) == 0) {
      local_7c = local_80;
      if ((local_50[4] & 2U) == 0) {
        local_7c = 6 - local_80;
      }
    }
    else {
      local_7c = local_78;
      if ((local_50[4] & 2U) == 0) {
        local_7c = 6 - local_78;
      }
    }
    local_7c = (local_50[4] & 3U) * 7 + local_7c;
    iVar3 = local_50[local_5c] - *(int *)(in_ECX + 0x10);
    iVar4 = local_34[local_5c] - *(int *)(in_ECX + 0xc);
    iVar5 = local_7c;
    uVar2 = thunk_FUN_0040e864(CONCAT22((short)((uint)iVar4 >> 0x10),*(undefined2 *)(in_ECX + 0x1c))
                              );
    thunk_FUN_00404770(in_ECX + 8,uVar2,iVar5,iVar4,iVar3);
    if ((local_50[4] & 3U) == 0) {
      local_9c = local_5c;
    }
    else if ((local_50[4] & 3U) == 1) {
      local_60 = local_5c;
    }
    local_50[4] = local_50[4] + 1;
  }
  local_68 = 0x29 - local_78;
  local_74 = 0x22 - local_80;
  local_58 = local_34[local_60 + 8];
  local_64 = local_34[(local_60 + 2U & 3) + 8];
  iVar5 = local_34[local_60 + 4];
  iVar3 = local_34[(local_60 + 2U & 3) + 4];
  if (((local_64 - local_58) + iVar3) - iVar5 < 0) {
    local_b0 = -(((local_64 - local_58) + iVar3) - iVar5);
  }
  else {
    local_b0 = ((local_64 - local_58) + iVar3) - iVar5;
  }
  local_70 = local_b0;
  local_54 = __ftol();
  if (iVar5 == iVar3) {
    local_38 = local_54;
    if (local_64 <= local_58) {
      local_38 = -local_54;
    }
    local_38 = local_58 + local_38;
    local_3c = iVar5;
  }
  else {
    local_38 = local_58;
    if (iVar5 < iVar3) {
      local_3c = iVar5 + local_54;
    }
    else {
      local_3c = iVar5 - local_54;
    }
  }
  iVar3 = local_3c - *(int *)(in_ECX + 0x10);
  iVar4 = local_38 - *(int *)(in_ECX + 0xc);
  iVar5 = local_68;
  uVar2 = thunk_FUN_0040e864(CONCAT22((short)((uint)iVar4 >> 0x10),*(undefined2 *)(in_ECX + 0x1c)));
  thunk_FUN_00404770(in_ECX + 8,uVar2,iVar5,iVar4,iVar3);
  local_58 = local_34[local_9c + 8];
  local_64 = local_34[(local_9c + 2U & 3) + 8];
  iVar5 = local_34[local_9c + 4];
  iVar3 = local_34[(local_9c + 2U & 3) + 4];
  if (((local_64 - local_58) + iVar3) - iVar5 < 0) {
    local_b4 = -(((local_64 - local_58) + iVar3) - iVar5);
  }
  else {
    local_b4 = ((local_64 - local_58) + iVar3) - iVar5;
  }
  local_70 = local_b4;
  local_54 = __ftol();
  if (iVar5 == iVar3) {
    local_38 = local_54;
    if (local_64 <= local_58) {
      local_38 = -local_54;
    }
    local_38 = local_58 + local_38;
    local_3c = iVar5;
  }
  else {
    local_38 = local_58;
    if (iVar5 < iVar3) {
      local_3c = iVar5 + local_54;
    }
    else {
      local_3c = iVar5 - local_54;
    }
  }
  iVar4 = local_3c - *(int *)(in_ECX + 0x10);
  iVar3 = local_38 - *(int *)(in_ECX + 0xc);
  iVar5 = local_74;
  uVar2 = thunk_FUN_0040e864(CONCAT22((short)((uint)iVar3 >> 0x10),*(undefined2 *)(in_ECX + 0x1c)));
  thunk_FUN_00404770(in_ECX + 8,uVar2,iVar5,iVar3,iVar4);
  thunk_FUN_0042d38a();
  thunk_FUN_0042d87c(in_ECX + 8,1);
  return;
}
```

---

---

## FUN_0043907c — 0x43907c

- Classification : internal
- Corps : `0x43907c–0x439088`
- État : pseudocode obtenu
- Evidence : `ev_b610f724e5897a0c112722486cb2959b0710c1ba1134f845394ee67541696c5e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043907c(void)

{
  return;
}
```

---

---

## FUN_00439089 — 0x439089

- Classification : internal
- Corps : `0x439089–0x4390b7`
- État : pseudocode obtenu
- Evidence : `ev_370d2fd11aa95636a8247827978f88e1aa44dd899be7e4cc5287e537dc487d24`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_00439089(void)

{
  int in_ECX;
  
  return *(char *)(in_ECX + 0x27) + -0x31 == (int)DAT_005e16a8;
}
```

---

---

## FUN_004390b8 — 0x4390b8

- Classification : internal
- Corps : `0x4390b8–0x43910b`
- État : pseudocode obtenu
- Evidence : `ev_0535cf2bd77b8d4d5e1adbbdf795e92c38985f06e19cbae5e72bd8fd4cbaceca`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b3b` — `thunk_FUN_00439128`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_004390b8(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491719;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494338;
  thunk_FUN_00439128();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0043910c — 0x43910c

- Classification : internal
- Corps : `0x43910c–0x439127`
- État : pseudocode obtenu
- Evidence : `ev_dfd6602d568bc43f13d1cefa6ee1785ecf5a8cec62ee190b98ba50a14dca4b77`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043910c(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494338;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_00439128 — 0x439128

- Classification : internal
- Corps : `0x439128–0x43913b`
- État : pseudocode obtenu
- Evidence : `ev_1f3060ec7833a88050a32d1d168316c5fd1a2ebb0b146339ec1bb4f6cc096dc6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00439128(void)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x70) = 0xffff;
  return;
}
```

---

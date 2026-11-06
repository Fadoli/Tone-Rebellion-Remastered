# 0011_batch_0007 — détails (1/3)

## FUN_0042a451 — 0x42a451

- Classification : internal
- Corps : `0x42a451–0x42a4a4`
- État : pseudocode obtenu
- Evidence : `ev_56783cc831f93572b5fae567ee2e2f124e1d722ec8c25406d6230405fd2e7d2a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`
- `0x401e92` — `thunk_FUN_0042a4c1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0042a451(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049164f;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004941b8;
  thunk_FUN_0042a4c1();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0042a4a5 — 0x42a4a5

- Classification : internal
- Corps : `0x42a4a5–0x42a4c0`
- État : pseudocode obtenu
- Evidence : `ev_588e21138948ac656e99b0c74b5557359d741209d633c97a0580139c65fda526`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a4a5(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004941b8;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_0042a4c1 — 0x42a4c1

- Classification : internal
- Corps : `0x42a4c1–0x42a4e6`
- État : pseudocode obtenu
- Evidence : `ev_99686a58f1eeff67977dea4941978558d372df100a9221e7affb64c7a6956eb4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a4c1(void)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x70) = 1;
  *(undefined2 *)(in_ECX + 0x72) = 0;
  *(undefined2 *)(in_ECX + 0x74) = 0xffff;
  return;
}
```

---

---

## FUN_0042a4e7 — 0x42a4e7

- Classification : internal
- Corps : `0x42a4e7–0x42a55c`
- État : pseudocode obtenu
- Evidence : `ev_06008e769215be00028ee1ef36c530a3b301c02c2ef2657a5eef2bbce081c447`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x40151e` — `thunk_FUN_004293c6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a4e7(short param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int in_ECX;
  
  if ((param_1 == 6) && (iVar1 = thunk_FUN_00429f3a(), iVar1 != 0)) {
    *(short *)(in_ECX + 0x72) = *(short *)(in_ECX + 0x72) + 1;
    if (*(short *)(in_ECX + 0x70) <= *(short *)(in_ECX + 0x72)) {
      *(undefined2 *)(in_ECX + 0x72) = 0;
    }
    *(undefined4 *)(in_ECX + 0x34) = 1;
  }
  thunk_FUN_004293c6(param_1,param_2,param_3);
  return;
}
```

---

---

## FUN_0042a55d — 0x42a55d

- Classification : internal
- Corps : `0x42a55d–0x42a648`
- État : pseudocode obtenu
- Evidence : `ev_4350628c428adfef5851303882cca4d122601a3fac28cd9f08a9464599d9f247`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a55d(void)

{
  undefined4 uVar1;
  int in_ECX;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    uVar1 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar1;
    iVar2 = (int)*(short *)(in_ECX + 0x1e) + (int)*(short *)(in_ECX + 0x72);
    iVar4 = (int)*(short *)(in_ECX + 0x6e);
    iVar3 = (int)*(short *)(in_ECX + 0x6c);
    uVar1 = thunk_FUN_0040e864(CONCAT22(*(short *)(in_ECX + 0x6c) >> 0xf,
                                        *(undefined2 *)(in_ECX + 0x1c)));
    thunk_FUN_00404770(in_ECX + 8,uVar1,iVar2,iVar3,iVar4);
    iVar2 = thunk_FUN_00429f3a();
    if ((iVar2 != 0) && (*(short *)(in_ECX + 0x74) != -1)) {
      iVar2 = (int)*(short *)(in_ECX + 0x6e);
      iVar4 = (int)*(short *)(in_ECX + 0x6c);
      iVar3 = (int)*(short *)(in_ECX + 0x74);
      uVar1 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar1,iVar3,iVar4,iVar2);
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,3);
    *(undefined4 *)(in_ECX + 0x34) = 0;
  }
  return;
}
```

---

---

## FUN_0042a649 — 0x42a649

- Classification : internal
- Corps : `0x42a649–0x42a6c8`
- État : pseudocode obtenu
- Evidence : `ev_8316437ed1c036f736c5f4c949728b2a3003dd344f7a4285b24c1b1a2885df50`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a649(int param_1)

{
  int local_8;
  
  DAT_00597188 = 0;
  DAT_0059718c = (short)(((*(int *)(param_1 + 0xc) - *(int *)(param_1 + 4)) *
                         (*(int *)(param_1 + 0x10) - *(int *)(param_1 + 8))) / 6000);
  if (0x32 < DAT_0059718c) {
    DAT_0059718c = 0x32;
  }
  for (local_8 = 0; local_8 < 0x32; local_8 = local_8 + 1) {
    *(undefined2 *)(&DAT_0058cf80 + local_8 * 2) = 0xffff;
  }
  DAT_0049d648 = 1;
  return;
}
```

---

---

## FUN_0042a6c9 — 0x42a6c9

- Classification : internal
- Corps : `0x42a6c9–0x42aa0e`
- État : pseudocode obtenu
- Evidence : `ev_4ac874f68af2eafb8a4202adab849692a143c2cf6f0c3e6a492d34d7a18a3d0a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401389` — `thunk_FUN_00403a84`
- `0x4013e3` — `thunk_FUN_00403b5f`
- `0x401a28` — `thunk_FUN_0041081b`
- `0x472c6c` — `__ftol`
- `0x474b90` — `FUN_00474b90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a6c9(int param_1)

{
  bool bVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  int iVar4;
  int local_40;
  int local_2c;
  int local_20;
  int local_1c;
  int local_18;
  int local_10;
  int local_8;
  
  if (DAT_0049d648 != 0) {
    local_18 = 0;
    for (local_1c = 0; local_1c < 8; local_1c = local_1c + 1) {
      uVar2 = thunk_FUN_0041081b(&DAT_00630730,(double)local_18);
      (&DAT_005970b8)[local_1c] = uVar2;
      local_18 = local_18 + 7;
    }
    DAT_0049d648 = 0;
  }
  local_8 = ((*(int *)(param_1 + 0xc) - *(int *)(param_1 + 4)) *
            (*(int *)(param_1 + 0x10) - *(int *)(param_1 + 8))) / 6000;
  if (0x32 < local_8) {
    local_8 = 0x32;
  }
  bVar1 = true;
  for (local_10 = 0; local_10 < local_8; local_10 = local_10 + 1) {
    if (*(short *)(&DAT_0058cf80 + local_10 * 2) == -1) {
      if (bVar1) {
        *(undefined2 *)(&DAT_0058cf80 + local_10 * 2) = 0;
        FUN_00474b90();
        uVar3 = __ftol();
        *(undefined2 *)(&DAT_0058d050 + local_10 * 2) = uVar3;
        FUN_00474b90();
        uVar3 = __ftol();
        *(undefined2 *)(&DAT_0058cfe8 + local_10 * 2) = uVar3;
        uVar2 = thunk_FUN_00403b5f();
        (&DAT_0058cf48)[local_10] = uVar2;
        for (local_20 = 0; local_20 < DAT_00597188; local_20 = local_20 + 1) {
          if ((((*(int *)(&DAT_005970c0 + local_20 * 0x10) <=
                 (int)*(short *)(&DAT_0058d050 + local_10 * 2)) &&
               ((int)*(short *)(&DAT_0058d050 + local_10 * 2) <=
                *(int *)(&DAT_005970c8 + local_20 * 0x10))) &&
              (*(int *)(&DAT_005970c4 + local_20 * 0x10) <=
               (int)*(short *)(&DAT_0058cfe8 + local_10 * 2))) &&
             ((int)*(short *)(&DAT_0058cfe8 + local_10 * 2) <=
              *(int *)(&DAT_005970cc + local_20 * 0x10))) {
            *(undefined2 *)(&DAT_0058cf80 + local_10 * 2) = 0xffff;
          }
        }
        bVar1 = false;
      }
    }
    else {
      *(short *)(&DAT_0058cf80 + local_10 * 2) = *(short *)(&DAT_0058cf80 + local_10 * 2) + 1;
      if (*(short *)(&DAT_0058cf80 + local_10 * 2) == 0x20) {
        *(undefined2 *)(&DAT_0058cf80 + local_10 * 2) = 0xffff;
      }
    }
  }
  for (local_10 = 0; local_10 < local_8; local_10 = local_10 + 1) {
    iVar4 = (int)*(short *)(&DAT_0058cf80 + local_10 * 2);
    if (iVar4 != -1) {
      local_40 = iVar4;
      if (0x10 < iVar4) {
        local_40 = 0x20 - iVar4;
      }
      local_40 = local_40 / 2;
      local_2c = local_40;
      if (local_40 < 0) {
        local_2c = 0;
      }
      if (7 < local_2c) {
        local_2c = 7;
      }
      if (iVar4 == 0x1f) {
        uVar2 = (&DAT_0058cf48)[local_10];
      }
      else {
        uVar2 = (&DAT_005970b8)[local_2c];
      }
      thunk_FUN_00403a84(param_1,(int)*(short *)(&DAT_0058d050 + local_10 * 2),
                         (int)*(short *)(&DAT_0058cfe8 + local_10 * 2),uVar2);
    }
  }
  return;
}
```

---

---

## FUN_0042aa0f — 0x42aa0f

- Classification : internal
- Corps : `0x42aa0f–0x42aa62`
- État : pseudocode obtenu
- Evidence : `ev_3e6e4b5a99ee2e341305b64acc7117c75b59f37dd45a880da11cf7b2f0e6febe`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`
- `0x4022a2` — `thunk_FUN_0042aa7f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0042aa0f(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491662;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004941d8;
  thunk_FUN_0042aa7f();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0042aa63 — 0x42aa63

- Classification : internal
- Corps : `0x42aa63–0x42aa7e`
- État : pseudocode obtenu
- Evidence : `ev_d00263ee3e7cc593ce740862370bebbda57ce95345fed24365889312a76ba495`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042aa63(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004941d8;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_0042aa7f — 0x42aa7f

- Classification : internal
- Corps : `0x42aa7f–0x42aa89`
- État : pseudocode obtenu
- Evidence : `ev_780d534dddfd0add2614dd4d19d37cb0da4faa0bbd3ba4d298971f8cc311e5c6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042aa7f(void)

{
  return;
}
```

---

---

## FUN_0042aa8a — 0x42aa8a

- Classification : internal
- Corps : `0x42aa8a–0x42aaf9`
- État : pseudocode obtenu
- Evidence : `ev_d055e1db9e1d79f2e2eea87b4daa5e935504adfacf76454a401c18686e560a79`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042aa8a(short param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int in_ECX;
  
  if (param_1 == 0xb) {
    if (*(int *)(in_ECX + 0x34) == 0) {
      if ((param_2 == 1) || (DAT_00630a94 != 0)) {
        *(undefined4 *)(in_ECX + 0x34) = 1;
      }
      else {
        *(undefined4 *)(in_ECX + 0x34) = 0x32;
        *(undefined4 *)(in_ECX + 0x70) = param_3;
      }
    }
    uVar1 = 0;
  }
  else {
    uVar1 = thunk_FUN_004293c6(param_1,param_2,param_3);
  }
  return uVar1;
}
```

---

---

## FUN_0042aafa — 0x42aafa

- Classification : internal
- Corps : `0x42aafa–0x42abf8`
- État : pseudocode obtenu
- Evidence : `ev_66082813f96b15552c09ed808e0b79ddd5162c757d7c5ecde7e860a9669f653e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40146f` — `thunk_FUN_0042d87c`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x49df10` — "BACKGRND"

### Pseudocode Ghidra

```c
void FUN_0042aafa(void)

{
  undefined4 uVar1;
  int in_ECX;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  undefined4 uVar7;
  int local_18 [5];
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    piVar5 = (int *)(in_ECX + 8);
    piVar6 = local_18;
    for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
      *piVar6 = *piVar5;
      piVar5 = piVar5 + 1;
      piVar6 = piVar6 + 1;
    }
    if (*(int *)(in_ECX + 0x34) == 0x32) {
      piVar5 = *(int **)(in_ECX + 0x70);
      piVar6 = local_18;
      for (iVar2 = 5; iVar2 != 0; iVar2 = iVar2 + -1) {
        *piVar6 = *piVar5;
        piVar5 = piVar5 + 1;
        piVar6 = piVar6 + 1;
      }
    }
    iVar3 = *(int *)(in_ECX + 0x10) - local_18[2];
    local_18[0] = thunk_FUN_0042d28f();
    uVar7 = 0;
    iVar4 = (int)*(short *)(in_ECX + 0x1e);
    iVar2 = iVar3;
    uVar1 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
    thunk_FUN_00404770(local_18,uVar1,iVar4,uVar7,iVar2);
    iVar2 = __strcmpi((char *)(in_ECX + 0x20),s_BACKGRND_0049df10);
    if (iVar2 == 0) {
      iVar3 = iVar3 + -0x28;
      uVar7 = 0;
      iVar2 = *(short *)(in_ECX + 0x1e) + 1;
      uVar1 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(local_18,uVar1,iVar2,uVar7,iVar3);
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,3);
    *(undefined4 *)(in_ECX + 0x34) = 0;
  }
  return;
}
```

---

# 0011_batch_0007 — détails (4/6)

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

## FUN_0042abf9 — 0x42abf9

- Classification : internal
- Corps : `0x42abf9–0x42ac4c`
- État : pseudocode obtenu
- Evidence : `ev_de5a8ba388ca800ed6769b904e363280711357514d3bc5f11b1c15a277fb55a6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401028` — `thunk_FUN_0042ac69`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0042abf9(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491675;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004941f0;
  thunk_FUN_0042ac69();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_0042ac4d — 0x42ac4d

- Classification : internal
- Corps : `0x42ac4d–0x42ac68`
- État : pseudocode obtenu
- Evidence : `ev_488c8c336869b67abfef6c65499fcbcb4896757dde08842dcf1ae80edb17945d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042ac4d(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004941f0;
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_0042ac69 — 0x42ac69

- Classification : internal
- Corps : `0x42ac69–0x42ad75`
- État : pseudocode obtenu
- Evidence : `ev_abcca1b3978e4fe3f0d7caba061e8457aeb292a334666d7134499e8edadb7dae`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x4737e0` — `_strncpy`
- `0x476e20` — `_strncmp`

### Chaînes référencées

- `0x49d650` — "Designed by"
- `0x49df1c` — "credits.txt"
- `0x49df28` — "FALSE"
- `0x49df30` — "C:\\float\\src\\gamewin.cpp"
- `0x49df4c` — "ENDCREDITS"

### Pseudocode Ghidra

```c
void FUN_0042ac69(void)

{
  int iVar1;
  int in_ECX;
  int local_894;
  undefined1 local_884 [2048];
  char local_84 [128];
  
  *(undefined2 *)(in_ECX + 0x78) = 0;
  *(undefined4 *)(in_ECX + 0x90) = 0;
  *(int *)(in_ECX + 0x7c) = in_ECX + 0x90;
  if (DAT_00597190 == 0) {
    iVar1 = thunk_FUN_0040f419(s_credits_txt_0049df1c,local_884,0x800);
    if (iVar1 != 0) {
      thunk_FUN_00414b64(s_C__float_src_gamewin_cpp_0049df30,0x45c,s_FALSE_0049df28);
    }
    local_894 = 0;
    while( true ) {
      thunk_FUN_0040f5b3(local_84,1);
      iVar1 = _strncmp(local_84,s_ENDCREDITS_0049df4c,9);
      if (iVar1 == 0) break;
      _strncpy(s_Designed_by_0049d650 + local_894 * 0x54,local_84,0x4f);
      (&DAT_0049d69f)[local_894 * 0x54] = 0;
      local_894 = local_894 + 1;
    }
    DAT_00597190 = 1;
  }
  return;
}
```

---

## FUN_0042ad76 — 0x42ad76

- Classification : internal
- Corps : `0x42ad76–0x42af01`
- État : pseudocode obtenu
- Evidence : `ev_8c450bbe8f8479e6933914c0e7acb06019a3182c2e585670abc0cd490f81c783`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401343` — `thunk_FUN_0042af02`
- `0x401406` — `thunk_FUN_0042a649`
- `0x40151e` — `thunk_FUN_004293c6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0042ad76(short param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int in_ECX;
  
  if (param_1 == 1) {
    thunk_FUN_004293c6(1,param_2,param_3);
    if (*(int *)(in_ECX + 0x90) == 0) {
      *(undefined **)(in_ECX + 0x90) = &DAT_004c2f48;
    }
    *(undefined4 *)(in_ECX + 0x94) = 0x27f;
    *(undefined4 *)(in_ECX + 0x98) = 0x1df;
    *(undefined4 *)(in_ECX + 0x9c) = 0;
    *(undefined4 *)(in_ECX + 0xa0) = 0;
    *(undefined4 *)(in_ECX + 0x80) = 0;
    *(undefined4 *)(in_ECX + 0x84) = 0;
    *(undefined4 *)(in_ECX + 0x88) = 0x27f;
    *(undefined4 *)(in_ECX + 0x8c) = 0x1df;
    thunk_FUN_0042a649(in_ECX + 8);
    if (DAT_0062d172 == 1) {
      _DAT_005970c0 = 0;
      _DAT_005970c4 = 0x50;
      _DAT_005970c8 = 0xbe;
      _DAT_005970cc = 0x1df;
      _DAT_005970d0 = 0x1c2;
      _DAT_005970d4 = 0x50;
      _DAT_005970d8 = 0x27f;
      _DAT_005970dc = 0x1df;
      DAT_00597188 = 2;
    }
    DAT_0049d64c = 0xfffffda8;
    thunk_FUN_0042af02();
    *(undefined4 *)(in_ECX + 0x70) = 1;
    *(undefined4 *)(in_ECX + 0x34) = 1;
  }
  else {
    if (param_1 != 0xb) {
      uVar1 = thunk_FUN_004293c6(param_1,param_2,param_3);
      return uVar1;
    }
    *(undefined4 *)(in_ECX + 0x34) = 1;
    *(undefined4 *)(in_ECX + 0x70) = 1;
  }
  return 0;
}
```

---

## FUN_0042af02 — 0x42af02

- Classification : internal
- Corps : `0x42af02–0x42af34`
- État : pseudocode obtenu
- Evidence : `ev_6a2bddf1f32d510d7e3d60bb85b615979d6c2b773ed0169d405c8c620bc45126`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401f14` — `thunk_FUN_00404770`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042af02(void)

{
  undefined4 uVar1;
  int in_ECX;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  uVar3 = 0;
  uVar2 = 0;
  uVar1 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
  thunk_FUN_00404770(in_ECX + 0x7c,uVar1,uVar2,uVar3,uVar4);
  return;
}
```

---

## FUN_0042af35 — 0x42af35

- Classification : internal
- Corps : `0x42af35–0x42b238`
- État : pseudocode obtenu
- Evidence : `ev_643258563fb1a0090b71b174061202df669b3f8e8f09822beb87aee19d99043d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401555` — `thunk_FUN_0042d647`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x40193d` — `thunk_FUN_0042d807`
- `0x401d7a` — `thunk_FUN_0042d598`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x402054` — `thunk_FUN_0042d697`
- `0x402081` — `thunk_FUN_004066e3`
- `0x402130` — `thunk_FUN_0042b239`
- `0x4022de` — `thunk_FUN_0042d9cd`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x40236a` — `thunk_FUN_0042a6c9`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x49df58` — "BACKGRND"

### Pseudocode Ghidra

```c
void FUN_0042af35(void)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined4 *puVar3;
  int *piVar4;
  undefined4 *puVar5;
  int *piVar6;
  int local_94;
  undefined1 local_8c [32];
  int local_6c;
  int local_68;
  undefined4 local_64 [5];
  undefined4 local_50 [5];
  int local_3c [4];
  int local_2c;
  int local_28;
  uint local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  uint local_c;
  int local_8;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    local_1c = 0;
    local_18 = 0;
    local_14 = 0x27f;
    local_10 = 0x1df;
    local_24 = 3;
    if (*(int *)(in_ECX + 0x74) != 0) {
      local_24 = 1;
    }
    if ((*(int *)(in_ECX + 0x74) != 0) || (*(int *)(in_ECX + 0x70) != 0)) {
      iVar1 = thunk_FUN_0042d807();
      if (iVar1 == 0) {
        puVar3 = (undefined4 *)(in_ECX + 0x7c);
        puVar5 = local_64;
        for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar5 = *puVar3;
          puVar3 = puVar3 + 1;
          puVar5 = puVar5 + 1;
        }
        local_20 = thunk_FUN_0042d28f();
        thunk_FUN_004066e3(local_64,0,0,&local_20,0,0,0xffffffff);
        *(undefined4 *)(in_ECX + 0x70) = 0;
        thunk_FUN_0042d38a();
      }
      else {
        if (*(int *)(in_ECX + 0x70) != 0) {
          puVar3 = (undefined4 *)(in_ECX + 0x7c);
          puVar5 = local_50;
          for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
            *puVar5 = *puVar3;
            puVar3 = puVar3 + 1;
            puVar5 = puVar5 + 1;
          }
          local_50[0] = thunk_FUN_0042d598();
          thunk_FUN_004066e3(in_ECX + 0x7c,0,0,local_50,0,0,0xffffffff);
          thunk_FUN_0042d647();
          *(undefined4 *)(in_ECX + 0x70) = 0;
        }
        thunk_FUN_0042d697(0,0,0x27f,0x1df);
      }
    }
    iVar1 = __strcmpi((char *)(in_ECX + 0x20),s_BACKGRND_0049df58);
    if ((iVar1 == 0) && (DAT_0062d172 != 8)) {
      local_94 = 1;
    }
    else {
      local_94 = 0;
    }
    local_8 = local_94;
    local_c = (uint)(DAT_0062d172 == 8);
    uVar2 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar2;
    piVar4 = (int *)(in_ECX + 8);
    piVar6 = local_3c;
    for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar6 = *piVar4;
      piVar4 = piVar4 + 1;
      piVar6 = piVar6 + 1;
    }
    if (local_8 != 0) {
      local_3c[1] = *(int *)(in_ECX + 0xc) + 0x14;
    }
    local_3c[2] = *(int *)(in_ECX + 0x10) + 0x14;
    local_3c[3] = *(int *)(in_ECX + 0x14) + -0x14;
    local_2c = *(int *)(in_ECX + 0x18) + -0x14;
    if (DAT_0062d172 != 7) {
      thunk_FUN_0042a6c9(local_3c);
    }
    if (local_8 != 0) {
      thunk_FUN_0042b239();
    }
    if (local_c != 0) {
      DAT_00597194 = DAT_00597194 + 1;
      if (600 < DAT_00597194) {
        DAT_00597194 = 0;
      }
      local_68 = DAT_00597194 / 0x14;
      if (0x1e < local_68) {
        local_68 = 0x1e;
      }
      for (local_6c = 0; local_6c < local_68; local_6c = local_6c + 1) {
        local_8c[local_6c] = 0x2a;
      }
      local_8c[local_6c] = 0;
      thunk_FUN_004289c0(in_ECX + 8,0x96,300,local_8c);
    }
    for (local_28 = 0; local_28 < *(short *)(in_ECX + 0x78); local_28 = local_28 + 1) {
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d9cd(local_24 & 0xff);
  }
  return;
}
```

---

## FUN_0042b239 — 0x42b239

- Classification : internal
- Corps : `0x42b239–0x42b44c`
- État : pseudocode obtenu
- Evidence : `ev_d1b532a63dab20983f1881ff6eedf46a99bb58c26c4dc9bee32225af143257aa`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401f14` — `thunk_FUN_00404770`
- `0x402234` — `thunk_FUN_0042892d`

### Chaînes référencées

- `0x49d650` — "Designed by"
- `0x49d650` — "Designed by"

### Pseudocode Ghidra

```c
/* WARNING: Removing unreachable block (ram,0x0042b30a) */

void FUN_0042b239(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int in_ECX;
  int iVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c [6];
  
  if (DAT_00597198 == 0) {
    local_24 = 0;
    for (local_20 = 0; local_20 < 0x18; local_20 = local_20 + 1) {
      local_24 = local_24 + *(int *)(&DAT_0049d6a0 + local_20 * 0x54);
      *(int *)(&DAT_0049d6a0 + local_20 * 0x54) = local_24;
    }
    DAT_0059719c = local_24 + 0xfa;
    DAT_00597198 = 1;
  }
  piVar5 = (int *)(in_ECX + 8);
  piVar7 = local_1c;
  for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar7 = *piVar5;
    piVar5 = piVar5 + 1;
    piVar7 = piVar7 + 1;
  }
  local_1c[5] = 0;
  local_1c[1] = 100;
  local_1c[2] = 0x14;
  local_1c[3] = 0x21c;
  local_1c[4] = 0x10e;
  if ((DAT_0049d64c < 300) || (DAT_0059719c + -0x118 < DAT_0049d64c)) {
    local_28 = -0x3c;
    if (0 < DAT_0049d64c) {
      if (DAT_0059719c + -0x118 < DAT_0049d64c) {
        local_28 = (DAT_0059719c - DAT_0049d64c) + -0x3c;
      }
      else {
        local_28 = -0x3c - DAT_0049d64c;
      }
    }
    uVar1 = 0xffffff9c;
    iVar4 = *(short *)(in_ECX + 0x1e) + 1;
    uVar2 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
    thunk_FUN_00404770(local_1c,uVar2,iVar4,uVar1,local_28);
  }
  if (0 < DAT_0049d64c) {
    for (local_2c = 0; local_2c < 0x18; local_2c = local_2c + 1) {
      iVar4 = *(int *)(&DAT_0049d6a0 + local_2c * 0x54) - DAT_0049d64c;
      if ((-10 < iVar4) && (iVar4 < 300)) {
        iVar6 = local_1c[3] - local_1c[1];
        iVar3 = thunk_FUN_0042892d(s_Designed_by_0049d650 + local_2c * 0x54,0xffffffff,0xffffffff);
        thunk_FUN_004289c0(local_1c,(iVar6 - iVar3) / 2,iVar4,
                           s_Designed_by_0049d650 + local_2c * 0x54);
      }
    }
  }
  DAT_0049d64c = DAT_0049d64c + 1;
  if (DAT_0059719c < DAT_0049d64c) {
    DAT_0049d64c = -600;
  }
  return;
}
```

---

## FUN_0042bcf0 — 0x42bcf0

- Classification : internal
- Corps : `0x42bcf0–0x42bd1d`
- État : pseudocode obtenu
- Evidence : `ev_43aff6f79edc099c361cef54e865baf82a22c1e09dcb015df4a68d11b92b8732`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042bcf0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00429262();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0042bd30 — 0x42bd30

- Classification : internal
- Corps : `0x42bd30–0x42bd5d`
- État : pseudocode obtenu
- Evidence : `ev_0cbf0b60b931254f49705f5546cf7908ef67316546757624fed6b1a7bd177eaf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4022f7` — `thunk_FUN_00429fb9`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042bd30(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00429fb9();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0042bd70 — 0x42bd70

- Classification : internal
- Corps : `0x42bd70–0x42bd9d`
- État : pseudocode obtenu
- Evidence : `ev_b926466161ca4e684b24627997c9d6b48d1bfa719dbfa07322caa35b075088fa`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40200e` — `thunk_FUN_0042a1f5`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042bd70(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0042a1f5();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0042bdb0 — 0x42bdb0

- Classification : internal
- Corps : `0x42bdb0–0x42bddd`
- État : pseudocode obtenu
- Evidence : `ev_0b0d52536aaec2a985ec769d3cf47c7a17ebea241a7e0a82af2998035c85ebce`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402450` — `thunk_FUN_0042a4a5`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042bdb0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0042a4a5();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0042bdf0 — 0x42bdf0

- Classification : internal
- Corps : `0x42bdf0–0x42be1d`
- État : pseudocode obtenu
- Evidence : `ev_2b135d3b77dac33e14d3a19b2054da8d9fcb32e3271d6fccba690eec31fddeaa`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402374` — `thunk_FUN_0042aa63`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042bdf0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0042aa63();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0042be30 — 0x42be30

- Classification : internal
- Corps : `0x42be30–0x42be5d`
- État : pseudocode obtenu
- Evidence : `ev_d3893502f52b58a275a09178cfb7e380dc52c140ac453ba310e0eb147355e364`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021a8` — `thunk_FUN_0042ac4d`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042be30(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0042ac4d();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0042be70 — 0x42be70

- Classification : internal
- Corps : `0x42be70–0x42be79`
- État : pseudocode obtenu
- Evidence : `ev_61f14dda8718254bd87af3cc2d80cb37380b9795746a3f82a367f5f98772cac8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x42be7a` — `FUN_0042be7a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042be70(void)

{
  FUN_0042be7a();
  return;
}
```

---


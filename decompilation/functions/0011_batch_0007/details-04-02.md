# 0011_batch_0007 — détails (2/3)

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

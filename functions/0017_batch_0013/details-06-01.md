# 0017_batch_0013 — détails (1/2)

## FUN_00466732 — 0x466732

- Classification : internal
- Corps : `0x466732–0x4667ea`
- État : pseudocode obtenu
- Evidence : `ev_0e3aaf211a469866259215ccd99855d4da0dc183c0021b7a3c1fbc5d25388065`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014e7` — `thunk_FUN_0045035a`
- `0x4020b3` — `thunk_FUN_00466533`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00466732(int param_1,int param_2)

{
  short sVar1;
  short sVar2;
  int in_ECX;
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 0x40; local_8 = local_8 + 1) {
    if (((*(int *)(in_ECX + 0x2c1a4 + local_8 * 0x14) != 0) &&
        (*(short *)(in_ECX + 0x2c1b4 + local_8 * 0x14) == 4)) &&
       (*(short *)(in_ECX + 0x2c1ae + local_8 * 0x14) == *(short *)(param_1 + 8))) {
      sVar1 = *(short *)(in_ECX + 0x2c1b2 + local_8 * 0x14);
      sVar2 = thunk_FUN_0045035a();
      if ((sVar1 == sVar2) && (*(short *)(in_ECX + 0x2c1b6 + local_8 * 0x14) == param_2)) {
        thunk_FUN_00466533(local_8);
      }
    }
  }
  return;
}
```

---

---

## FUN_004667eb — 0x4667eb

- Classification : internal
- Corps : `0x4667eb–0x4668d3`
- État : pseudocode obtenu
- Evidence : `ev_3c8a055e1af2b4f1b5b52849f14a0bd8d90f6162c37bbf836ea1eb10193d3626`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014e7` — `thunk_FUN_0045035a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004667eb(int param_1,int param_2,int param_3)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int in_ECX;
  int local_8;
  
  local_8 = 0;
  while ((local_8 < 0x40 &&
         ((((*(int *)(in_ECX + 0x2c1a4 + local_8 * 0x14) == 0 ||
            (*(short *)(in_ECX + 0x2c1b4 + local_8 * 0x14) != 0xd)) ||
           (*(short *)(in_ECX + 0x2c1b6 + local_8 * 0x14) != param_2)) ||
          (((*(short *)(in_ECX + 0x2c1ae + local_8 * 0x14) != *(short *)(param_1 + 8) ||
            (sVar1 = *(short *)(in_ECX + 0x2c1b2 + local_8 * 0x14), sVar2 = thunk_FUN_0045035a(),
            sVar1 != sVar2)) ||
           ((param_3 != -1 && (*(short *)(in_ECX + 0x2c1ac + local_8 * 0x14) != param_3))))))))) {
    local_8 = local_8 + 1;
  }
  if (local_8 < 0x40) {
    iVar3 = in_ECX + 0x2c1a4 + local_8 * 0x14;
  }
  else {
    iVar3 = 0;
  }
  return iVar3;
}
```

---

---

## FUN_004668d4 — 0x4668d4

- Classification : internal
- Corps : `0x4668d4–0x4669bc`
- État : pseudocode obtenu
- Evidence : `ev_21d6476027c41c04958628a25ab369a62ff2252cae60fbe6d78471d5e1cb8091`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014e7` — `thunk_FUN_0045035a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004668d4(int param_1,int param_2,int param_3)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int in_ECX;
  int local_8;
  
  local_8 = 0;
  while ((local_8 < 0x40 &&
         ((((*(int *)(in_ECX + 0x2c1a4 + local_8 * 0x14) == 0 ||
            (*(short *)(in_ECX + 0x2c1b4 + local_8 * 0x14) != 4)) ||
           (*(short *)(in_ECX + 0x2c1b6 + local_8 * 0x14) != param_2)) ||
          (((*(short *)(in_ECX + 0x2c1ae + local_8 * 0x14) != *(short *)(param_1 + 8) ||
            (sVar1 = *(short *)(in_ECX + 0x2c1b2 + local_8 * 0x14), sVar2 = thunk_FUN_0045035a(),
            sVar1 != sVar2)) ||
           ((param_3 != -1 && (*(short *)(in_ECX + 0x2c1ac + local_8 * 0x14) != param_3))))))))) {
    local_8 = local_8 + 1;
  }
  if (local_8 < 0x40) {
    iVar3 = in_ECX + 0x2c1a4 + local_8 * 0x14;
  }
  else {
    iVar3 = 0;
  }
  return iVar3;
}
```

---

---

## FUN_004669bd — 0x4669bd

- Classification : internal
- Corps : `0x4669bd–0x466b08`
- État : pseudocode obtenu
- Evidence : `ev_b30589ad8e8dc4fd8f9e7c50be1117bbafa5e3808f994368fd7124a2c0d4ddc4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4015f0` — `thunk_FUN_00466c8b`
- `0x401adc` — `thunk_FUN_00416a9a`
- `0x401d7f` — `thunk_FUN_00466b09`
- `0x401e9c` — `thunk_FUN_00466c08`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004669bd(int param_1)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int in_ECX;
  int iVar6;
  int local_14;
  
  if (*(int *)(param_1 + 4) == 2) {
    thunk_FUN_00416a9a(3,param_1);
    sVar1 = *(short *)(param_1 + 8);
    iVar4 = (int)sVar1;
    sVar2 = *(short *)(param_1 + 0x36);
    iVar6 = (int)sVar2;
    for (local_14 = 0; local_14 < (int)(uint)*(ushort *)(in_ECX + 0x2759c); local_14 = local_14 + 1)
    {
      if (((*(short *)(in_ECX + 0x274a0 + local_14 * 8) == iVar4) &&
          (*(short *)(in_ECX + 0x274a2 + local_14 * 8) == iVar6)) ||
         ((*(short *)(in_ECX + 0x274a2 + local_14 * 8) == iVar4 &&
          (*(short *)(in_ECX + 0x274a0 + local_14 * 8) == iVar6)))) {
        *(undefined4 *)(in_ECX + 0x2749c + local_14 * 8) = 1;
      }
    }
    uVar3 = *(uint *)(param_1 + 0x1c);
    *(uint *)(param_1 + 0x1c) = uVar3 | 1;
    iVar5 = thunk_FUN_00466c08(CONCAT22((short)(uVar3 >> 0x10),sVar1),sVar2);
    if ((iVar5 != 0) && (*(int *)(iVar5 + 4) == 2)) {
      *(uint *)(iVar5 + 0x1c) = *(uint *)(iVar5 + 0x1c) | 1;
    }
    if ((-1 < *(short *)(param_1 + 0x2c)) && (*(short *)(param_1 + 0x2c) < 4)) {
      thunk_FUN_00466b09((int)*(short *)(param_1 + 0x2c),sVar1,
                         CONCAT22(*(short *)(param_1 + 0x2c) >> 0xf,sVar2));
    }
    thunk_FUN_00466c8b(iVar4);
    thunk_FUN_00466c8b(iVar6);
  }
  return;
}
```

---

---

## FUN_00466b09 — 0x466b09

- Classification : internal
- Corps : `0x466b09–0x466c07`
- État : pseudocode obtenu
- Evidence : `ev_e35b13b50ae6690a857d3a97ec0f8e1a2cbb691b0aaab1141afac3f99b96d72f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40101e` — `thunk_FUN_00462285`
- `0x4013c0` — `thunk_FUN_004655b2`
- `0x401e9c` — `thunk_FUN_00466c08`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00466b09(int param_1,undefined2 param_2,short param_3)

{
  short *psVar1;
  int in_ECX;
  short local_20;
  undefined4 local_14;
  int local_10;
  uint local_c;
  int local_8;
  
  local_8 = in_ECX + param_3 * 0x29e8;
  local_c = (uint)(*(int *)(local_8 + 0x29ac + param_1 * 4) == 0);
  *(undefined4 *)(local_8 + 0x29ac + param_1 * 4) = 1;
  if (local_c != 0) {
    psVar1 = (short *)thunk_FUN_00466c08(param_2,param_3);
    if (psVar1 != (short *)0x0) {
      local_20 = *psVar1 + -0x140;
      if (local_20 < 0) {
        local_20 = 0;
      }
      if (0x780 < local_20) {
        local_20 = 0x780;
      }
      *(int *)(local_8 + 0x408 + param_1 * 8) = (int)local_20;
      *(int *)(local_8 + 0x40c + param_1 * 8) = (int)(short)(local_20 + 0x27f);
    }
    thunk_FUN_00462285(param_1);
    local_14 = 0xc;
    local_10 = (int)(short)(&DAT_005eebf8)[param_3 * 0x14f4];
    thunk_FUN_004655b2(&local_14);
  }
  return;
}
```

---

---

## FUN_00466c08 — 0x466c08

- Classification : internal
- Corps : `0x466c08–0x466c8a`
- État : pseudocode obtenu
- Evidence : `ev_c50cc6e829d1545a0ff5b6cadf8d1248dabad2086db613e1f1ba72423d27b6fb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00466c08(short param_1,short param_2)

{
  int in_ECX;
  int iVar1;
  int local_10;
  int local_c;
  
  iVar1 = in_ECX + param_2 * 0x29e8;
  local_10 = iVar1 + 0x428;
  local_c = 0;
  while( true ) {
    if (*(short *)(iVar1 + 0x29a8) <= local_c) {
      return 0;
    }
    if ((*(int *)(local_10 + 4) == 2) && (*(short *)(local_10 + 0x36) == param_1)) break;
    local_c = local_c + 1;
    local_10 = local_10 + 0x60;
  }
  return local_10;
}
```

---

---

## FUN_00466c8b — 0x466c8b

- Classification : internal
- Corps : `0x466c8b–0x466ce1`
- État : pseudocode obtenu
- Evidence : `ev_b28feac41f2a05efb584e2ba4e8f4ac889c721197d31a7f072f82c5556ddd7fa`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40102d` — `thunk_FUN_0045e6d3`
- `0x401226` — `thunk_FUN_00460460`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00466c8b(undefined4 param_1)

{
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
    thunk_FUN_0045e6d3(param_1);
  }
  thunk_FUN_00460460(param_1);
  return;
}
```

---

---

## FUN_00466ce2 — 0x466ce2

- Classification : internal
- Corps : `0x466ce2–0x466fe3`
- État : pseudocode obtenu
- Evidence : `ev_b51f2311ff9bd9ad209f0663ea00bfe330e7ff0eff117e8a273292d3112a4e0e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401122` — `thunk_FUN_0046290d`
- `0x401181` — `thunk_FUN_00466221`
- `0x401221` — `thunk_FUN_0041e569`
- `0x40166d` — `thunk_FUN_00460989`
- `0x4016bd` — `thunk_FUN_00415f6d`
- `0x4017df` — `thunk_FUN_0041be72`
- `0x401fbe` — `thunk_FUN_0045eaa7`
- `0x402072` — `thunk_FUN_00465614`
- `0x4020c7` — `thunk_FUN_00464e4d`
- `0x402324` — `thunk_FUN_0041be90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00466ce2(void)

{
  undefined4 uVar1;
  int in_ECX;
  int *local_14;
  short local_c;
  int local_8;
  
  thunk_FUN_00465614();
  if (*(short *)(in_ECX + 0x2cf9c) == 0) {
    if (*(int *)(in_ECX + 0x2d030 + DAT_0049f538 * 0x14a0) != 0) {
      *(undefined2 *)(in_ECX + 0x2cf9c) = 1;
    }
  }
  else {
    thunk_FUN_00464e4d();
  }
  thunk_FUN_00466221();
  thunk_FUN_00415f6d();
  DAT_004c2bbc = 0;
  uVar1 = thunk_FUN_0041be72();
  for (local_c = 0; (int)local_c < (int)(uint)*(ushort *)(in_ECX + 0x27498); local_c = local_c + 1)
  {
    thunk_FUN_0046290d();
  }
  _DAT_004c2bc0 = thunk_FUN_0041be90(uVar1);
  local_14 = (int *)(in_ECX + 0x275a0);
  local_8 = 0;
  local_c = 0;
  while ((local_c < 0x100 && (local_8 < (int)(uint)*(ushort *)(in_ECX + 0x2c1a0)))) {
    if (*local_14 != -1) {
      local_8 = local_8 + 1;
      thunk_FUN_0041e569();
    }
    local_c = local_c + 1;
    local_14 = local_14 + 0x13;
  }
  _DAT_004c2bc4 = thunk_FUN_0041be90(uVar1);
  _DAT_004c2bc4 = _DAT_004c2bc4 - _DAT_004c2bc0;
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    thunk_FUN_0045eaa7();
  }
  thunk_FUN_00460989();
  for (local_c = 0; local_c < 0xf; local_c = local_c + 1) {
    if (0 < *(short *)(in_ECX + 0x2cd42 + local_c * 2)) {
      *(short *)(in_ECX + 0x2cd42 + local_c * 2) = *(short *)(in_ECX + 0x2cd42 + local_c * 2) + -1;
    }
    if (0 < *(short *)(in_ECX + 0x2cd60 + local_c * 2)) {
      *(short *)(in_ECX + 0x2cd60 + local_c * 2) = *(short *)(in_ECX + 0x2cd60 + local_c * 2) + -1;
    }
    if (0 < *(short *)(in_ECX + 0x2cd7e + local_c * 2)) {
      *(short *)(in_ECX + 0x2cd7e + local_c * 2) = *(short *)(in_ECX + 0x2cd7e + local_c * 2) + -1;
    }
  }
  *(int *)(in_ECX + 0x2cc34) = *(int *)(in_ECX + 0x2cc34) + (int)*(short *)(in_ECX + 0x2cc3c);
  *(int *)(in_ECX + 0x2cc38) = *(int *)(in_ECX + 0x2cc38) + (int)*(short *)(in_ECX + 0x2cc3e);
  if ((*(int *)(in_ECX + 0x2cc34) == 0) || (*(int *)(in_ECX + 0x2cc34) == 9999)) {
    *(short *)(in_ECX + 0x2cc3c) = -*(short *)(in_ECX + 0x2cc3c);
  }
  if ((*(int *)(in_ECX + 0x2cc38) == 0) || (*(int *)(in_ECX + 0x2cc38) == 7999)) {
    *(short *)(in_ECX + 0x2cc3e) = -*(short *)(in_ECX + 0x2cc3e);
  }
  *(int *)(in_ECX + 0x2cc2c) = *(int *)(in_ECX + 0x2cc2c) + 1;
  return;
}
```

---

---

## FUN_00466fe4 — 0x466fe4

- Classification : internal
- Corps : `0x466fe4–0x467100`
- État : pseudocode obtenu
- Evidence : `ev_0ca802ac15043c61c073f6d68546619fc924a4ba10fd4d9f04e203668dc62ed7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012c1` — `thunk_FUN_0041e4e4`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x40156e` — `thunk_FUN_0041ff8b`
- `0x402144` — `thunk_FUN_00420f28`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int * FUN_00466fe4(int param_1,int param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int in_ECX;
  int *local_c;
  int local_8;
  
  if (*(ushort *)(in_ECX + 0x2c1a0) < 0x100) {
    local_c = (int *)(in_ECX + 0x275a0);
    if (param_1 == 4) {
      if (param_2 < 9) {
        param_2 = 9;
      }
      if (0x11 < param_2) {
        param_2 = 0x11;
      }
    }
    else {
      if (param_2 < 0) {
        param_2 = 0;
      }
      if (8 < param_2) {
        param_2 = 8;
      }
    }
    for (local_8 = 0; local_8 < 0x100; local_8 = local_8 + 1) {
      if (*local_c == -1) {
        thunk_FUN_0041e4e4();
        *local_c = param_1;
        local_c[1] = param_2;
        uVar1 = thunk_FUN_00467260(0x100);
        *(undefined1 *)(local_c + 5) = uVar1;
        *(undefined2 *)((int)local_c + 0x22) = 0;
        *(undefined2 *)(local_c + 2) = 0;
        thunk_FUN_0041ff8b(0);
        uVar2 = thunk_FUN_00420f28();
        *(undefined2 *)(local_c + 8) = uVar2;
        *(short *)(in_ECX + 0x2c1a0) = *(short *)(in_ECX + 0x2c1a0) + 1;
        return local_c;
      }
      local_c = local_c + 0x13;
    }
  }
  return (int *)0x0;
}
```

---

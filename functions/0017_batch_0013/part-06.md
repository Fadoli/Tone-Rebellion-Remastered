# 0017_batch_0013 — détails (6/6)

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

## FUN_00467101 — 0x467101

- Classification : internal
- Corps : `0x467101–0x46725f`
- État : pseudocode obtenu
- Evidence : `ev_5277d61e37d4f89f720cbbae1d0e4030b4f4298f0ec65cb4b0a012e47903bdd1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40145b` — `thunk_FUN_00425084`
- `0x401672` — `thunk_FUN_0045c51b`
- `0x401dac` — `thunk_FUN_004207f2`
- `0x401e5b` — `thunk_FUN_00418921`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x40225c` — `thunk_FUN_00421ec1`
- `0x4024d7` — `thunk_FUN_004206b2`

### Chaînes référencées

- `0x4a5230` — "num < MAX_FLOATERS"
- `0x4a5244` — "C:\\float\\src\\tworld.cpp"
- `0x4a525c` — "flt->mType!=FT_Leviathan"
- `0x4a5278` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
void FUN_00467101(ushort param_1)

{
  int *piVar1;
  int iVar2;
  int in_ECX;
  uint local_8;
  
  if (0xff < param_1) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a5244,0x9d1,s_num_<_MAX_FLOATERS_004a5230);
  }
  piVar1 = (int *)(in_ECX + 0x275a0 + (uint)param_1 * 0x4c);
  if (*piVar1 != -1) {
    iVar2 = thunk_FUN_004207f2();
    if (iVar2 != 0) {
      if (*piVar1 == 4) {
        thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a5278,0x9db,
                           s_flt_>mType__FT_Leviathan_004a525c);
      }
      thunk_FUN_0045c51b(param_1);
    }
    thunk_FUN_00421ec1(0xffffffff);
    thunk_FUN_00425084();
    for (local_8 = 0; (int)local_8 < 0x100; local_8 = local_8 + 1) {
      if ((local_8 != param_1) && (*(int *)(in_ECX + 0x275a0 + local_8 * 0x4c) != -1)) {
        thunk_FUN_004206b2(param_1);
      }
    }
    thunk_FUN_00418921(param_1);
    *(undefined4 *)(in_ECX + 0x275a0 + (uint)param_1 * 0x4c) = 0xffffffff;
    *(short *)(in_ECX + 0x2c1a0) = *(short *)(in_ECX + 0x2c1a0) + -1;
  }
  return;
}
```

---

## FUN_00467260 — 0x467260

- Classification : internal
- Corps : `0x467260–0x4672a5`
- État : pseudocode obtenu
- Evidence : `ev_258e54e159e72a542149c969658cf64c9aa031def3414bee317f234641f77de8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472c6c` — `__ftol`
- `0x474b80` — `FUN_00474b80`
- `0x474b90` — `FUN_00474b90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00467260(void)

{
  FUN_00474b80(DAT_004a4b78);
  DAT_004a4b78 = FUN_00474b90();
  __ftol();
  return;
}
```

---

## FUN_004672a6 — 0x4672a6

- Classification : internal
- Corps : `0x4672a6–0x4672ee`
- État : pseudocode obtenu
- Evidence : `ev_d6e45300f5ee5de4ed13ebfa3da2e5198981b6af36bc072d956c795033a50243`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004672a6(int param_1,int param_2,int param_3,int param_4)

{
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = param_1 - param_3;
  if (local_c < 0) {
    local_c = -local_c;
  }
  local_8 = param_2 - param_4;
  if (local_8 < 0) {
    local_8 = -local_8;
  }
  if (local_8 < local_c) {
    local_8 = local_c;
  }
  return local_8;
}
```

---

## FUN_004672ef — 0x4672ef

- Classification : internal
- Corps : `0x4672ef–0x467b8c`
- État : pseudocode obtenu
- Evidence : `ev_844f65b3a2326b16f50a1aab2e965997cf9d3bb05916f0847f5caf358678031b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40101e` — `thunk_FUN_00462285`
- `0x40102d` — `thunk_FUN_0045e6d3`
- `0x401113` — `thunk_FUN_004669bd`
- `0x401320` — `thunk_FUN_00452656`
- `0x401479` — `thunk_FUN_00452ae7`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x40156e` — `thunk_FUN_0041ff8b`
- `0x401573` — `thunk_FUN_00467101`
- `0x4018a7` — `thunk_FUN_00462a87`
- `0x4018b1` — `thunk_FUN_0045f075`
- `0x4018cf` — `thunk_FUN_0041ff2e`
- `0x401915` — `thunk_FUN_004502dc`
- `0x401965` — `thunk_FUN_00452a15`
- `0x4021c1` — `thunk_FUN_00453cba`
- `0x40225c` — `thunk_FUN_00421ec1`
- `0x4022e3` — `thunk_FUN_00452859`
- `0x402347` — `thunk_FUN_004503bd`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004672ef(undefined4 *param_1)

{
  int *piVar1;
  int iVar2;
  short sVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int in_ECX;
  uint uVar8;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_70;
  int local_6c;
  int local_64;
  int local_60;
  int local_58;
  int local_54;
  int local_4c;
  int local_48;
  int local_30;
  int local_2c;
  int local_c;
  
  switch(*param_1) {
  case 0:
    iVar7 = in_ECX + param_1[2] * 0x29e8;
    for (local_c = 0; local_c < 5; local_c = local_c + 1) {
      iVar6 = *(int *)(iVar7 + 0x408 + param_1[3] * 8);
      iVar2 = *(int *)(iVar7 + 0x40c + param_1[3] * 8);
      uVar4 = thunk_FUN_00467260(300);
      thunk_FUN_00462a87(param_1[3],0,(iVar6 + iVar2) / 2,uVar4);
    }
    break;
  case 1:
    if (*(int *)(in_ECX + param_1[2] * 0x29e8 + param_1[4] * 0x60 + 0x42c) == 0) {
      thunk_FUN_004503bd(1,0x32,param_1[3]);
      thunk_FUN_004503bd(2,0x32,param_1[3]);
      thunk_FUN_004503bd(3,0x32,param_1[3]);
    }
    break;
  case 2:
    sVar3 = thunk_FUN_0041ff2e();
    thunk_FUN_0041ff8b((sVar3 + 1) % 3);
    break;
  case 3:
    iVar7 = in_ECX + param_1[2] * 0x29e8 + 0x428 + param_1[3] * 0x60;
    if ((*(int *)(iVar7 + 4) == 0) &&
       ((*(int *)(iVar7 + 0x10) == 0x2a ||
        ((0x2b < *(int *)(iVar7 + 0x10) && (*(int *)(iVar7 + 0x10) < 0x31)))))) {
      uVar5 = (int)*(short *)(iVar7 + 0x4a) + 1;
      uVar8 = (int)uVar5 >> 0x1f;
      thunk_FUN_00453cba(((uVar5 ^ uVar8) - uVar8 & 3 ^ uVar8) - uVar8);
    }
    break;
  case 4:
    iVar7 = in_ECX + param_1[2] * 0x29e8;
    local_30 = iVar7 + 0x428;
    for (local_2c = 0; local_2c < *(short *)(iVar7 + 0x29a8); local_2c = local_2c + 1) {
      if (*(int *)(local_30 + 4) == 2) {
        thunk_FUN_004669bd(local_30);
      }
      local_30 = local_30 + 0x60;
    }
    break;
  case 5:
    iVar6 = in_ECX + param_1[3] * 0x29e8;
    iVar7 = param_1[2];
    *(undefined4 *)(iVar6 + 0x408 + iVar7 * 8) = 0;
    *(undefined4 *)(iVar6 + 0x40c + iVar7 * 8) = 0x9ff;
    break;
  case 6:
    thunk_FUN_00467101(CONCAT22((short)((uint)*param_1 >> 0x10),*(undefined2 *)(param_1 + 2)));
    break;
  case 7:
    thunk_FUN_00452ae7();
    break;
  case 8:
    *(short *)(in_ECX + 0x275a8 + param_1[2] * 0x4c) =
         *(short *)(in_ECX + 0x275a8 + param_1[2] * 0x4c) + 10;
    break;
  case 9:
    thunk_FUN_00421ec1(0xffffffff);
    break;
  case 10:
    iVar7 = in_ECX + param_1[3] * 0x29e8 + 0x428 + param_1[4] * 0x60;
    if ((*(int *)(iVar7 + 4) == 1) && (*(int *)(iVar7 + 0x14) == -1)) {
      *(byte *)(iVar7 + 0x22) = *(byte *)(iVar7 + 0x22) | (byte)(1 << ((byte)param_1[2] & 0x1f));
    }
    thunk_FUN_0045e6d3(param_1[3]);
    break;
  case 0xb:
    iVar7 = in_ECX + param_1[2] * 0x29e8 + 0x428 + param_1[3] * 0x60;
    local_54 = param_1[4];
    if ((local_54 == 4) || (local_54 == -1)) {
      local_54 = 4;
      if (*(int *)(iVar7 + 4) == 1) {
        local_58 = 6;
        local_48 = 9;
      }
      else {
        local_58 = 10;
        local_48 = 0x15;
      }
    }
    else {
      local_58 = 0x25;
      local_48 = 0x34;
    }
    local_4c = *(int *)(iVar7 + 0x10);
    if (local_4c < local_58) {
      local_4c = local_58;
    }
    do {
      local_4c = local_4c + 1;
      if (local_48 < local_4c) {
        local_4c = local_58;
      }
      iVar6 = thunk_FUN_00452656(local_4c,local_54);
      if (iVar6 != 0) {
        thunk_FUN_00452859(local_4c,local_54);
        return;
      }
    } while (local_4c != *(int *)(iVar7 + 0x10));
    break;
  case 0xc:
    iVar7 = in_ECX + param_1[2] * 0x29e8 + 0x428 + param_1[3] * 0x60;
    if (*(int *)(iVar7 + 4) == 2) {
      thunk_FUN_004669bd(iVar7);
    }
    break;
  case 0xd:
    *(uint *)(in_ECX + 0x336c0) = *(uint *)(in_ECX + 0x336c0) ^ 1;
    break;
  case 0xe:
    *(undefined4 *)(in_ECX + 0x2e43c + param_1[2] * 0x14a0) = 1;
    thunk_FUN_00462285(DAT_0049f538);
    break;
  case 0xf:
    local_60 = *(int *)(in_ECX + 0x275a0 + param_1[2] * 0x4c) + 1;
    if (4 < local_60) {
      local_60 = 0;
    }
    *(int *)(in_ECX + 0x275a0 + param_1[2] * 0x4c) = local_60;
    break;
  case 0x10:
    piVar1 = (int *)(in_ECX + 0x275a0 + param_1[2] * 0x4c);
    local_64 = piVar1[1] + 1;
    if ((*piVar1 == 4) && (0x11 < local_64)) {
      local_64 = 9;
    }
    else if ((*piVar1 != 4) && (8 < local_64)) {
      local_64 = 0;
    }
    piVar1[1] = local_64;
    break;
  case 0x11:
    *(ushort *)(in_ECX + 0x2d02a + param_1[2] * 0x14a0) =
         *(ushort *)(in_ECX + 0x2d02a + param_1[2] * 0x14a0) |
         (ushort)(1 << ((byte)param_1[3] & 0x1f));
    *(undefined4 *)(in_ECX + 0x29cc + param_1[3] * 0x29e8) = 1;
    local_70 = in_ECX + 0x428 + param_1[3] * 0x29e8;
    for (local_6c = 0; local_6c < *(short *)(in_ECX + 0x29a8 + param_1[3] * 0x29e8);
        local_6c = local_6c + 1) {
      if (*(int *)(local_70 + 0x10) == 4) {
        *(ushort *)(local_70 + 0x4a) = *(ushort *)(local_70 + 0x4a) | 3;
        *(uint *)(local_70 + 0x1c) = *(uint *)(local_70 + 0x1c) | 1;
      }
      local_70 = local_70 + 0x60;
    }
    break;
  case 0x12:
    iVar7 = thunk_FUN_004502dc();
    if ((4 < iVar7) && (iVar7 < 0x22)) {
      thunk_FUN_0045f075(iVar7,1);
      thunk_FUN_00452a15();
    }
    break;
  case 0x13:
    local_7c = in_ECX;
    for (local_80 = 0; local_80 < (int)(uint)*(ushort *)(in_ECX + 0x27498); local_80 = local_80 + 1)
    {
      local_84 = local_7c + 0x428;
      for (local_88 = 0; local_88 < *(short *)(local_7c + 0x29a8); local_88 = local_88 + 1) {
        iVar7 = thunk_FUN_004502dc();
        if (((*(int *)(local_84 + 4) == 0) && (4 < iVar7)) && (iVar7 < 0x22)) {
          thunk_FUN_0045f075(iVar7,1);
          thunk_FUN_00452a15();
        }
        local_84 = local_84 + 0x60;
      }
      local_7c = local_7c + 0x29e8;
    }
    break;
  case 0x14:
    thunk_FUN_00462a87(param_1[2],param_1[5],param_1[3],param_1[4]);
    break;
  case 0x15:
    DAT_006191b4 = 3;
    DAT_006191b6 = 0;
  }
  return;
}
```

---

## FUN_00467be5 — 0x467be5

- Classification : internal
- Corps : `0x467be5–0x467ff5`
- État : pseudocode obtenu
- Evidence : `ev_83ca625f94f4336ae3f690b6620c7ab998377f808715e93b09bd86f291de158e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40141a` — `thunk_FUN_00462c55`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401ac3` — `thunk_FUN_00460c83`
- `0x401b18` — `thunk_FUN_004252fa`
- `0x401cee` — `thunk_FUN_0040fd80`
- `0x401f2d` — `thunk_FUN_00460334`
- `0x401fff` — `thunk_FUN_0040fdab`
- `0x402455` — `thunk_FUN_004199c0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00467be5(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined4 local_8;
  
  if (param_2 == 0) {
    thunk_FUN_004199c0(*(undefined2 *)(in_ECX + 0x27498));
    thunk_FUN_004199c0(*(undefined2 *)(in_ECX + 0x2759c));
    thunk_FUN_004199c0(*(undefined2 *)(in_ECX + 0x2c1a0));
    thunk_FUN_004199c0(*(undefined2 *)(in_ECX + 0x2c6a4));
    thunk_FUN_004199c0(*(undefined4 *)(in_ECX + 0x2cc2c));
    thunk_FUN_004199c0(*(undefined4 *)(in_ECX + 0x2cc30));
    thunk_FUN_004199c0(*(undefined4 *)(in_ECX + 0x2cc34));
    thunk_FUN_004199c0(*(undefined4 *)(in_ECX + 0x2cc38));
    thunk_FUN_004199c0((int)*(short *)(in_ECX + 0x2cc3c));
    thunk_FUN_004199c0((int)*(short *)(in_ECX + 0x2cc3e));
    thunk_FUN_004199c0((int)*(short *)(in_ECX + 0x2749a));
    thunk_FUN_004199c0((int)*(short *)(in_ECX + 0x2cf9c));
    thunk_FUN_004199c0((int)*(short *)(in_ECX + 0x2cf9e));
    thunk_FUN_004199c0((int)*(short *)(in_ECX + 0x2cc28));
    thunk_FUN_004199c0((int)*(short *)(in_ECX + 0x2cd40));
    thunk_FUN_0040fd80(in_ECX + 0x2c1a4,0x500);
    thunk_FUN_0040fd80(in_ECX + 0x2749c,0x100);
    thunk_FUN_0040fd80(in_ECX + 0x2cc40,0x100);
    thunk_FUN_0040fd80(in_ECX + 0x2cd42,0x1e);
    thunk_FUN_0040fd80(in_ECX + 0x2cd60,0x1e);
    thunk_FUN_0040fd80(in_ECX + 0x2cd7e,0x1e);
  }
  else {
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x27498) = uVar1;
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x2759c) = uVar1;
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x2c1a0) = uVar1;
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x2c6a4) = uVar1;
    uVar2 = thunk_FUN_0040fdab();
    *(undefined4 *)(in_ECX + 0x2cc2c) = uVar2;
    uVar2 = thunk_FUN_0040fdab();
    *(undefined4 *)(in_ECX + 0x2cc30) = uVar2;
    uVar2 = thunk_FUN_0040fdab();
    *(undefined4 *)(in_ECX + 0x2cc34) = uVar2;
    uVar2 = thunk_FUN_0040fdab();
    *(undefined4 *)(in_ECX + 0x2cc38) = uVar2;
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x2cc3c) = uVar1;
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x2cc3e) = uVar1;
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x2749a) = uVar1;
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x2cf9c) = uVar1;
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x2cf9e) = uVar1;
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x2cc28) = uVar1;
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x2cd40) = uVar1;
    thunk_FUN_0040fc15(in_ECX + 0x2c1a4,0x500);
    thunk_FUN_0040fc15(in_ECX + 0x2749c,0x100);
    thunk_FUN_0040fc15(in_ECX + 0x2cc40,0x100);
    thunk_FUN_0040fc15(in_ECX + 0x2cd42,0x1e);
    thunk_FUN_0040fc15(in_ECX + 0x2cd60,0x1e);
    thunk_FUN_0040fc15(in_ECX + 0x2cd7e,0x1e);
  }
  for (local_8 = 0; local_8 < (int)(uint)*(ushort *)(in_ECX + 0x27498); local_8 = local_8 + 1) {
    thunk_FUN_00462c55(param_1,param_2);
  }
  for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
    thunk_FUN_00460334(param_1,param_2);
  }
  thunk_FUN_00460c83(param_1,param_2);
  for (local_8 = 0; local_8 < 0x100; local_8 = local_8 + 1) {
    thunk_FUN_004252fa(param_1,param_2);
  }
  return;
}
```

---

## FUN_00467ff6 — 0x467ff6

- Classification : internal
- Corps : `0x467ff6–0x468049`
- État : pseudocode obtenu
- Evidence : `ev_bac3027e2b6733da4d8524536db959e5944098f361b7299e286b339fef2a41e0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00467ff6(void)

{
  ushort *in_ECX;
  ushort *local_10;
  int local_8;
  
  local_8 = 0;
  for (local_10 = in_ECX; local_10 < in_ECX + 0x166ce; local_10 = local_10 + 1) {
    local_8 = local_8 + (uint)*local_10;
  }
  return local_8;
}
```

---

## FUN_0046804a — 0x46804a

- Classification : internal
- Corps : `0x46804a–0x4680a2`
- État : pseudocode obtenu
- Evidence : `ev_dd032e1c371972e30467ec87ff5ef241a0420f0b5b8050fa92cb6070a5e28f45`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0046804a(void)

{
  int in_ECX;
  ushort *local_10;
  int local_8;
  
  local_8 = 0;
  for (local_10 = (ushort *)(in_ECX + 0x275a0); local_10 < (ushort *)(in_ECX + 0x2c1a0);
      local_10 = local_10 + 1) {
    local_8 = local_8 + (uint)*local_10;
  }
  return local_8;
}
```

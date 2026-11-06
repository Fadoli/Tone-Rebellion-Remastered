# 0017_batch_0013 — détails (2/2)

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

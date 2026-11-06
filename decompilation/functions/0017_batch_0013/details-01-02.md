# 0017_batch_0013 — détails (2/3)

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

### Note de correction — calcul du Tone (`+0x3c`) et du surplus (`+0x40`)

Le pseudocode masque l'appel x87. Octets lus statiquement : `push 0x3fe00000; push 0; fild [+0x3c]; fstp [esp]; call FUN_00477599; fmul [0x494780]=20.0; call __ftol`. `FUN_00477599` est la fonction CRT `pow` ; l'appel calcule `pow(S, 0.5)`, donc `+0x3c = (int)(sqrt(S) * 20.0)`, `S` = somme des retours de `FUN_00462285`. Une lecture précédente (« constant 10 ») était erronée. Voir [la note budget Tone](../../behavior/player-tone-budget.md).

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

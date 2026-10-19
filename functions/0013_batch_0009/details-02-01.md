# 0013_batch_0009 — détails (1/3)

## FUN_0043b9af — 0x43b9af

- Classification : internal
- Corps : `0x43b9af–0x43bd2e`
- État : pseudocode obtenu
- Evidence : `ev_1d98e7256c690c3753e31e694f043773d6b7f90d711ae4932c8c7f73c5890a45`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x4011f4` — `thunk_FUN_0043bd2f`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401569` — `thunk_FUN_0046c558`
- `0x401adc` — `thunk_FUN_00416a9a`
- `0x40214e` — `thunk_FUN_0043bebe`

### Chaînes référencées

- `0x4a001c` — "escrollup"
- `0x4a0028` — "escrolldn"
- `0x4a0034` — "escrollup"
- `0x4a0040` — "escrolldn"

### Pseudocode Ghidra

```c
undefined4 FUN_0043b9af(short param_1,int param_2,int param_3)

{
  short sVar1;
  bool bVar2;
  undefined4 uVar3;
  int in_ECX;
  int iVar4;
  
  bVar2 = false;
  if (param_1 < 8) {
    if (param_1 < 6) {
      if (param_1 == 1) {
        *(undefined2 *)(in_ECX + 0x70) = DAT_004c1dc8;
        *(short *)(in_ECX + 0x74) =
             (short)((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) / 10);
        *(undefined2 *)(in_ECX + 0x76) = 0;
        if ((*(short *)(in_ECX + 0x78) == -1) || (*(short *)(in_ECX + 0x7a) == -1)) {
          thunk_FUN_0046c558(s_escrollup_004a001c,3,in_ECX + 0x78);
          thunk_FUN_0046c558(s_escrolldn_004a0028,3,in_ECX + 0x7a);
        }
        if ((*(short *)(in_ECX + 0x78) != -1) && (*(short *)(in_ECX + 0x7a) != -1)) {
          thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x78),1,0,0);
          thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x7a),1,0,0);
        }
      }
      else if (param_1 == 2) {
        if ((*(short *)(in_ECX + 0x78) != -1) || (*(short *)(in_ECX + 0x7a) == -1)) {
          thunk_FUN_0046c558(s_escrollup_004a0034,3,in_ECX + 0x78);
          thunk_FUN_0046c558(s_escrolldn_004a0040,3,in_ECX + 0x7a);
        }
        thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x78),2,0,0);
        thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x7a),2,0,0);
        *(undefined4 *)(in_ECX + 0x7c) = 0;
        *(undefined4 *)(in_ECX + 0x80) = 0;
      }
    }
    else if ((((*(int *)(in_ECX + 0xc) < param_2) && (param_2 < *(int *)(in_ECX + 0x14) + -0xd)) &&
             (*(int *)(in_ECX + 0x10) < param_3)) && (param_3 < *(int *)(in_ECX + 0x18))) {
      if ((DAT_0062c6bc == *(short *)(in_ECX + 0x78)) || (DAT_0062c6bc == *(short *)(in_ECX + 0x7a))
         ) {
        return 0;
      }
      thunk_FUN_0043bebe(param_2,param_3,param_1 == 7);
      bVar2 = true;
    }
  }
  else if (param_1 == 6000) {
    sVar1 = *(short *)(in_ECX + 0x76);
    *(short *)(in_ECX + 0x76) = *(short *)(in_ECX + 0x76) - *(short *)(in_ECX + 0x74);
    if (*(short *)(in_ECX + 0x76) < 0) {
      *(undefined2 *)(in_ECX + 0x76) = 0;
    }
    if (sVar1 != *(short *)(in_ECX + 0x76)) {
      thunk_FUN_0043bd2f();
    }
    bVar2 = true;
  }
  else if (param_1 == 0x1771) {
    sVar1 = *(short *)(in_ECX + 0x76);
    if (((int)*(short *)(in_ECX + 0x70) != (int)*(short *)(in_ECX + 0x74) &&
         -1 < (int)*(short *)(in_ECX + 0x70) - (int)*(short *)(in_ECX + 0x74)) &&
       (*(short *)(in_ECX + 0x76) = *(short *)(in_ECX + 0x76) + *(short *)(in_ECX + 0x74),
       (int)*(short *)(in_ECX + 0x70) - (int)*(short *)(in_ECX + 0x74) <
       (int)*(short *)(in_ECX + 0x76))) {
      *(short *)(in_ECX + 0x76) = *(short *)(in_ECX + 0x70) - *(short *)(in_ECX + 0x74);
    }
    if (sVar1 != *(short *)(in_ECX + 0x76)) {
      thunk_FUN_0043bd2f();
    }
    bVar2 = true;
  }
  else if (param_1 == 0x1c01) {
    iVar4 = *(short *)(in_ECX + 0x72) * 0x30;
    *(undefined2 *)(&DAT_004c0bf0 + iVar4) = (undefined2)param_2;
    *(ushort *)(&DAT_004c0bf4 + iVar4) = *(ushort *)(&DAT_004c0bf4 + iVar4) | 1;
    thunk_FUN_00416a9a(9,(int)*(short *)(in_ECX + 0x72));
  }
  if (bVar2) {
    uVar3 = 1;
  }
  else {
    uVar3 = thunk_FUN_004293c6(param_1,param_2,param_3);
  }
  return uVar3;
}
```

---

---

## FUN_0043bd2f — 0x43bd2f

- Classification : internal
- Corps : `0x43bd2f–0x43bebd`
- État : pseudocode obtenu
- Evidence : `ev_eef1fa1abb7656955a2a3504c5d2afcd23e310b6f5565d1ea919b02e720384b7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043bd2f(void)

{
  int in_ECX;
  
  if (*(short *)(in_ECX + 0x74) < *(short *)(in_ECX + 0x70)) {
    if ((*(short *)(in_ECX + 0x76) < 1) || (*(int *)(in_ECX + 0x7c) != 0)) {
      if ((*(int *)(in_ECX + 0x7c) != 0) && (*(short *)(in_ECX + 0x76) == 0)) {
        thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x78),2,0,0);
        *(undefined4 *)(in_ECX + 0x7c) = 0;
      }
    }
    else {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x78),1,0,0);
      *(undefined4 *)(in_ECX + 0x7c) = 1;
    }
    if (((int)*(short *)(in_ECX + 0x76) <
         (int)*(short *)(in_ECX + 0x70) - (int)*(short *)(in_ECX + 0x74)) &&
       (*(int *)(in_ECX + 0x80) == 0)) {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x7a),1,0,0);
      *(undefined4 *)(in_ECX + 0x80) = 1;
    }
    else if ((*(int *)(in_ECX + 0x80) != 0) &&
            ((int)*(short *)(in_ECX + 0x70) - (int)*(short *)(in_ECX + 0x74) <=
             (int)*(short *)(in_ECX + 0x76))) {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x7a),2,0,0);
      *(undefined4 *)(in_ECX + 0x80) = 0;
    }
  }
  else {
    *(undefined2 *)(in_ECX + 0x76) = 0;
    if (*(int *)(in_ECX + 0x7c) != 0) {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x78),2,0,0);
      *(undefined4 *)(in_ECX + 0x7c) = 0;
    }
    if (*(int *)(in_ECX + 0x80) != 0) {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x7a),2,0,0);
      *(undefined4 *)(in_ECX + 0x80) = 0;
    }
  }
  return;
}
```

---

---

## FUN_0043bebe — 0x43bebe

- Classification : internal
- Corps : `0x43bebe–0x43bf75`
- État : pseudocode obtenu
- Evidence : `ev_918fe51a3f5ba8afd18fb3cbe585943f68127052c128337f237cce832ac0cd92`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401adc` — `thunk_FUN_00416a9a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043bebe(undefined4 param_1,int param_2,int param_3)

{
  int in_ECX;
  int local_8;
  
  local_8 = ((param_2 - *(int *)(in_ECX + 0x10)) -
            ((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + *(short *)(in_ECX + 0x74) * -10)
            / 2) / 10 + (int)*(short *)(in_ECX + 0x76);
  if (local_8 < 0) {
    local_8 = 0;
  }
  if (local_8 < *(short *)(in_ECX + 0x70)) {
    *(undefined2 *)(in_ECX + 0x72) = (undefined2)local_8;
    if (param_3 == 0) {
      thunk_FUN_00416a9a(9,local_8);
    }
    else {
      *(undefined2 *)(&DAT_004c0bf0 + local_8 * 0x30) = 0xffff;
    }
  }
  return 1;
}
```

---

---

## FUN_0043bf76 — 0x43bf76

- Classification : internal
- Corps : `0x43bf76–0x43c2c5`
- État : pseudocode obtenu
- Evidence : `ev_48c948d2ba997839d41512d7131f1751f4e6a3abad099d2b2cc716e5b393e60d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x40174e` — `thunk_FUN_004109a6`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x402306` — `thunk_FUN_004106dd`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x4a0054` — "C:\\float\\src\\iwdebug.cpp"
- `0x4a0078` — "[%d] %s - %s"

### Pseudocode Ghidra

```c
void FUN_0043bf76(void)

{
  undefined4 uVar1;
  uint uVar2;
  int in_ECX;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int local_8c [4];
  int local_7c;
  undefined4 local_78;
  int local_74;
  undefined *local_70;
  undefined *local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  undefined1 local_54 [80];
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    uVar1 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar1;
    if (DAT_004c2bac == 0) {
      thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
    }
    else {
      uVar8 = 0;
      uVar7 = 0;
      iVar3 = (int)*(short *)(in_ECX + 0x1e);
      uVar1 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar1,iVar3,uVar7,uVar8);
    }
    local_60 = thunk_FUN_0042de0d();
    if (local_60 == 0) {
      thunk_FUN_00414b64(s_C__float_src_iwdebug_cpp_004a0054,0x111,&DAT_004a004c);
    }
    local_68 = ((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) +
               *(short *)(in_ECX + 0x74) * -10) / 2;
    local_5c = 0;
    local_58 = (int)*(short *)(in_ECX + 0x70);
    if ((int)*(short *)(in_ECX + 0x76) + (int)*(short *)(in_ECX + 0x74) < local_58) {
      local_58 = (int)*(short *)(in_ECX + 0x76) + (int)*(short *)(in_ECX + 0x74);
    }
    for (local_64 = (int)*(short *)(in_ECX + 0x76); local_64 < local_58; local_64 = local_64 + 1) {
      local_6c = &DAT_004c0bc8 + local_64 * 0x30;
      uVar2 = thunk_FUN_0042dd0f(6);
      *(uint *)(local_60 + 8) = uVar2 & 0xff;
      local_70 = &DAT_004a0070;
      if (*(short *)(local_6c + 0x28) != -1) {
        uVar2 = thunk_FUN_0042dd0f(3);
        *(uint *)(local_60 + 8) = uVar2 & 0xff;
        local_70 = &DAT_005e8230 + *(short *)(local_6c + 0x28) * 0x48;
      }
      if (*(short *)(in_ECX + 0x72) == local_64) {
        local_74 = local_5c * 10 + -3 +
                   ((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) +
                   *(short *)(in_ECX + 0x74) * -10) / 2;
        piVar5 = (int *)(in_ECX + 8);
        piVar6 = local_8c;
        for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
          *piVar6 = *piVar5;
          piVar5 = piVar5 + 1;
          piVar6 = piVar6 + 1;
        }
        local_8c[2] = *(int *)(in_ECX + 0x10) + local_74;
        local_7c = local_8c[2] + 10;
        local_8c[3] = local_8c[3] + -0xd;
        uVar1 = thunk_FUN_004106dd(1,1);
        iVar4 = *(int *)(in_ECX + 0x10) - local_8c[2];
        uVar8 = 0;
        iVar3 = (int)*(short *)(in_ECX + 0x1e);
        local_78 = uVar1;
        uVar7 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
        thunk_FUN_004109a6(local_8c,uVar7,iVar3,uVar8,iVar4,uVar1);
      }
      FUN_00472ca0(local_54,s___d___s____s_004a0078,local_64,local_6c,local_70);
      thunk_FUN_004289c0(in_ECX + 8,5,local_68,local_54);
      local_68 = local_68 + 10;
      local_5c = local_5c + 1;
    }
    uVar2 = thunk_FUN_0042dd0f(6);
    *(uint *)(local_60 + 8) = uVar2 & 0xff;
    thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x78),0xb,0,0);
    thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x7a),0xb,0,0);
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,1);
  }
  return;
}
```

---

---

## FUN_0043c2c6 — 0x43c2c6

- Classification : internal
- Corps : `0x43c2c6–0x43c2e9`
- État : pseudocode obtenu
- Evidence : `ev_6155d0f90c602fd8a9f93e1afcfdc80c4039b782554652ceae0b76359442d6db`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a0088` — "FALSE"
- `0x4a0090` — "C:\\float\\src\\iwdebug.cpp"

### Pseudocode Ghidra

```c
void FUN_0043c2c6(void)

{
  thunk_FUN_00414b64(s_C__float_src_iwdebug_cpp_004a0090,0x141,s_FALSE_004a0088);
  return;
}
```

---

---

## FUN_0043c2ea — 0x43c2ea

- Classification : internal
- Corps : `0x43c2ea–0x43c2f6`
- État : pseudocode obtenu
- Evidence : `ev_e763f4b0dae7049c899b1948179109fa276019fb4cd811e5da3cb1fbee45d6c2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043c2ea(void)

{
  return;
}
```

---

---

## FUN_0043c2f7 — 0x43c2f7

- Classification : internal
- Corps : `0x43c2f7–0x43c34a`
- État : pseudocode obtenu
- Evidence : `ev_4ecd858533e760c83cfafd676e88669f480ab627a89e9623378294976cbbbde9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401140` — `thunk_FUN_0043c367`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0043c2f7(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049179c;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004943c8;
  thunk_FUN_0043c367();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0043c34b — 0x43c34b

- Classification : internal
- Corps : `0x43c34b–0x43c366`
- État : pseudocode obtenu
- Evidence : `ev_87c6a7707f5b90c871c5a2670dd4621cacc7c224f8befdd0e5bad48b7baa7b54`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043c34b(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004943c8;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_0043c367 — 0x43c367

- Classification : internal
- Corps : `0x43c367–0x43c395`
- État : pseudocode obtenu
- Evidence : `ev_ea0d91f11eb7e13bf81e54c489162d90c2f8829e3aec37ef59c3654dc8f3ca0b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043c367(void)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x72) = 0;
  *(undefined2 *)(in_ECX + 0x70) = 0;
  *(undefined2 *)(in_ECX + 0x78) = 0xffff;
  *(undefined2 *)(in_ECX + 0x7a) = 0xffff;
  return;
}
```

---

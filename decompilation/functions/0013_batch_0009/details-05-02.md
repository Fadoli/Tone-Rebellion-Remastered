# 0013_batch_0009 — détails (2/2)

## FUN_00441aae — 0x441aae

- Classification : internal
- Corps : `0x441aae–0x441b35`
- État : pseudocode obtenu
- Evidence : `ev_0ecd4e7a20e361d304cf9829452a7c9830aac652d4d275c7a1ed60ff3416611e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401c7b` — `thunk_FUN_004119ba`
- `0x401f14` — `thunk_FUN_00404770`
- `0x4020e0` — `thunk_FUN_0040ec89`

### Chaînes référencées

- `0x4a07e8` — "triggers"

### Pseudocode Ghidra

```c
void FUN_00441aae(void)

{
  undefined4 uVar1;
  int iVar2;
  int in_ECX;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((4 < *(int *)(*(int *)(in_ECX + 0x70) + 0x24)) &&
     (*(int *)(*(int *)(in_ECX + 0x70) + 0x24) < 0x22)) {
    uVar1 = thunk_FUN_0040ec89(s_triggers_004a07e8,1);
    iVar2 = *(int *)(*(int *)(in_ECX + 0x70) + 0x24) + -5;
    thunk_FUN_004119ba(in_ECX + 8,uVar1,iVar2,&local_8,&local_c);
    thunk_FUN_00404770(in_ECX + 8,uVar1,iVar2,local_8,local_c);
  }
  return;
}
```

---

---

## FUN_00441b36 — 0x441b36

- Classification : internal
- Corps : `0x441b36–0x441cae`
- État : pseudocode obtenu
- Evidence : `ev_c186d32a485c268bd9e281abeccc5b5d69189b3d088c11c8fd07e7a7988d4d8d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402234` — `thunk_FUN_0042892d`

### Chaînes référencées

- `0x4a07fc` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0814` — "CBRIDGE"
- `0x4a081c` — "INFECT"
- `0x4a0824` — "BEASTI"
- `0x4a082c` — "PRIMED"
- `0x4a0834` — "UNPRIM"
- `0x4a083c` — "MYSTLOC"

### Pseudocode Ghidra

```c
void FUN_00441b36(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int in_ECX;
  int local_8;
  
  iVar2 = thunk_FUN_0042de03();
  if (iVar2 == 0) {
    thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a07fc,0x332,&DAT_004a07f4);
  }
  local_8 = 0;
  if (*(int *)(*(int *)(in_ECX + 0x70) + 4) == 2) {
    local_8 = thunk_FUN_00429ebe(s_CBRIDGE_004a0814,0);
  }
  else if (*(int *)(*(int *)(in_ECX + 0x70) + 4) == 1) {
    if (*(int *)(*(int *)(in_ECX + 0x70) + 0x14) == 4) {
      if (*(int *)(*(int *)(in_ECX + 0x70) + 0x10) == 5) {
        local_8 = thunk_FUN_00429ebe(s_INFECT_004a081c,0);
      }
      else {
        local_8 = thunk_FUN_00429ebe(s_BEASTI_004a0824,0);
      }
    }
    else if (((int)*(char *)(*(int *)(in_ECX + 0x70) + 0x22) & 1 << ((byte)DAT_0049f538 & 0x1f)) ==
             0) {
      local_8 = thunk_FUN_00429ebe(s_UNPRIM_004a0834,0);
    }
    else {
      local_8 = thunk_FUN_00429ebe(s_PRIMED_004a082c,0);
    }
  }
  else if (*(int *)(*(int *)(in_ECX + 0x70) + 4) == 3) {
    local_8 = thunk_FUN_00429ebe(s_MYSTLOC_004a083c,0);
  }
  if (local_8 != 0) {
    iVar2 = *(int *)(in_ECX + 0x14);
    iVar1 = *(int *)(in_ECX + 0xc);
    iVar3 = thunk_FUN_0042892d(local_8,0xffffffff,0xffffffff);
    thunk_FUN_004289c0(in_ECX + 8,((iVar2 - iVar1) - iVar3) / 2,
                       (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) / 2 + -10,local_8);
  }
  return;
}
```

---

---

## FUN_00441caf — 0x441caf

- Classification : internal
- Corps : `0x441caf–0x441d02`
- État : pseudocode obtenu
- Evidence : `ev_3df0be0154c9459b011590e3cac062ac07db8436185b3015c791fa82af22cdd0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401852` — `thunk_FUN_00441d1f`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00441caf(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491861;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004944a0;
  thunk_FUN_00441d1f();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_00441d03 — 0x441d03

- Classification : internal
- Corps : `0x441d03–0x441d1e`
- État : pseudocode obtenu
- Evidence : `ev_87909e4f90edcf24ecc4b5633b91952a9afe77f772cfd7dd9403c010dad62751`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00441d03(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004944a0;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_00441d1f — 0x441d1f

- Classification : internal
- Corps : `0x441d1f–0x441d3d`
- État : pseudocode obtenu
- Evidence : `ev_57152e5962a56a252b2cc411ea861156be1d67c19611bd56ee7b884e4346cac6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00441d1f(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x70) = 0;
  *(undefined4 *)(in_ECX + 0x74) = 0;
  return;
}
```

---

---

## FUN_00441d3e — 0x441d3e

- Classification : internal
- Corps : `0x441d3e–0x441e8a`
- État : pseudocode obtenu
- Evidence : `ev_721b02ae62d9e81fff934679f3d0f672a102544ced812b19041e4d27311fc4f1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401569` — `thunk_FUN_0046c558`
- `0x401bf4` — `thunk_FUN_0042970c`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401faa` — `thunk_FUN_0045f337`

### Chaînes référencées

- `0x4a0844` — "IWLocInfo"
- `0x4a0850` — "mpLocInfo"
- `0x4a085c` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_00441d3e(short param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  int in_EDX;
  int extraout_EDX;
  undefined2 uVar3;
  undefined2 extraout_var;
  
  uVar3 = (undefined2)((uint)in_EDX >> 0x10);
  if (param_1 < 7) {
    if (param_1 == 6) {
      iVar1 = thunk_FUN_00429f3a();
      uVar3 = extraout_var;
      if (iVar1 != 0) {
        if (*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) == 0) {
          iVar1 = thunk_FUN_0045f337(*(undefined4 *)(*(int *)(in_ECX + 0x70) + 0x70),0);
          if (iVar1 != 0) {
            thunk_FUN_0042970c(0x48,0,0);
          }
        }
        else {
          thunk_FUN_0042970c(0x4a,0,0);
        }
        return 1;
      }
    }
    else if (param_1 == 1) {
      if (*(int *)(in_ECX + 0x70) == 0) {
        uVar2 = thunk_FUN_0046c558(s_IWLocInfo_004a0844,3,0);
        *(undefined4 *)(in_ECX + 0x70) = uVar2;
        in_EDX = in_ECX;
        if (*(int *)(in_ECX + 0x70) == 0) {
          thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a085c,0x37b,s_mpLocInfo_004a0850);
          in_EDX = extraout_EDX;
        }
      }
      uVar3 = (undefined2)((uint)in_EDX >> 0x10);
      *(undefined4 *)(in_ECX + 0x74) = 0;
    }
  }
  else if (param_1 == 14000) {
    *(undefined4 *)(in_ECX + 0x74) = param_2;
    *(undefined4 *)(in_ECX + 0x34) = 1;
    return 1;
  }
  uVar2 = thunk_FUN_004293c6(CONCAT22(uVar3,param_1),param_2,param_3);
  return uVar2;
}
```

---

---

## FUN_00441e8b — 0x441e8b

- Classification : internal
- Corps : `0x441e8b–0x4420ea`
- État : pseudocode obtenu
- Evidence : `ev_85cda0bcd2ca4cf544e4fc6ae99c8785bdfda0d5c143bbefd4ef0f49e8560a08`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x40163b` — `thunk_FUN_00404c3b`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401faa` — `thunk_FUN_0045f337`
- `0x402086` — `thunk_FUN_00404c5a`
- `0x402306` — `thunk_FUN_004106dd`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- `0x4a0874` — "mpLocInfo"
- `0x4a0880` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
void FUN_00441e8b(void)

{
  int iVar1;
  int in_ECX;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    if (*(int *)(in_ECX + 0x70) == 0) {
      uVar5 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0880,0x3b3,s_mpLocInfo_004a0874);
    }
    else {
      uVar5 = 0;
    }
    iVar1 = thunk_FUN_0045f337(*(undefined4 *)(*(int *)(in_ECX + 0x70) + 0x70),0);
    if ((iVar1 == 0) && (*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) == 0)) {
      iVar1 = 0;
    }
    else {
      iVar1 = 1;
    }
    uVar5 = thunk_FUN_0042d28f(iVar1,uVar5);
    *(undefined4 *)(in_ECX + 8) = uVar5;
    if (iVar1 == 0) {
      uVar5 = thunk_FUN_004106dd(0,3);
      thunk_FUN_00404c3b(uVar5);
      uVar4 = 0;
      uVar3 = 0;
      iVar2 = (int)*(short *)(in_ECX + 0x1e);
      uVar5 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404c5a(in_ECX + 8,uVar5,iVar2,uVar3,uVar4);
    }
    else {
      uVar4 = 0;
      uVar3 = 0;
      iVar2 = (int)*(short *)(in_ECX + 0x1e);
      uVar5 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar5,iVar2,uVar3,uVar4);
    }
    iVar2 = thunk_FUN_00429f3a();
    if ((iVar2 != 0) && (iVar1 != 0)) {
      uVar4 = 0;
      uVar3 = 0;
      iVar1 = *(short *)(in_ECX + 0x1e) + 3;
      uVar5 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar5,iVar1,uVar3,uVar4);
    }
    if ((*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) != 0) &&
       ((DAT_00630a3e < 0x140 || (iVar1 = thunk_FUN_00429f3a(), iVar1 != 0)))) {
      if ((*(int *)(in_ECX + 0x74) == 0) ||
         (iVar1 = thunk_FUN_0045f337(*(undefined4 *)(*(int *)(in_ECX + 0x70) + 0x70),
                                     *(undefined4 *)(in_ECX + 0x74)), iVar1 == 0)) {
        uVar4 = 0;
        uVar3 = 0;
        iVar1 = *(short *)(in_ECX + 0x1e) + 1;
        uVar5 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
        thunk_FUN_00404770(in_ECX + 8,uVar5,iVar1,uVar3,uVar4);
      }
      else {
        uVar4 = 0;
        uVar3 = 0;
        iVar1 = *(short *)(in_ECX + 0x1e) + 2;
        uVar5 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
        thunk_FUN_00404770(in_ECX + 8,uVar5,iVar1,uVar3,uVar4);
      }
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,1);
  }
  return;
}
```

---

---

## FUN_004420eb — 0x4420eb

- Classification : internal
- Corps : `0x4420eb–0x44213e`
- État : pseudocode obtenu
- Evidence : `ev_203be26384938ba80f31f68c0ce23864480d6f1510f8035300118debf985ffae`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401325` — `thunk_FUN_0044215b`
- `0x4019ba` — `thunk_FUN_0042a451`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_004420eb(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491874;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0042a451();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004944b8;
  thunk_FUN_0044215b();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0044213f — 0x44213f

- Classification : internal
- Corps : `0x44213f–0x44215a`
- État : pseudocode obtenu
- Evidence : `ev_066625dfe14fd1bcb73a36e68d0164c335c5f653098fe4be52f7becb5de09a10`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402450` — `thunk_FUN_0042a4a5`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044213f(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004944b8;
  thunk_FUN_0042a4a5();
  return;
}
```

---

---

## FUN_0044215b — 0x44215b

- Classification : internal
- Corps : `0x44215b–0x44216f`
- État : pseudocode obtenu
- Evidence : `ev_d9b7799a2f1b41523b3fb8e2ff403e18787d1b4d7c4a8a56d1f6fe920f03f52a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044215b(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x78) = 0;
  return;
}
```

---

---

## FUN_00442170 — 0x442170

- Classification : internal
- Corps : `0x442170–0x4421f0`
- État : pseudocode obtenu
- Evidence : `ev_a7d97d384c6a20459d64eef4e4d9dd04c5768825ee7345a34f2d5344d6297dae`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`
- `0x401569` — `thunk_FUN_0046c558`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a0898` — "IWLocInfo"
- `0x4a08a4` — "mpLocInfo"
- `0x4a08b0` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
void FUN_00442170(short param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int in_ECX;
  
  if ((param_1 == 1) && (*(int *)(in_ECX + 0x78) == 0)) {
    uVar1 = thunk_FUN_0046c558(s_IWLocInfo_004a0898,3,0);
    *(undefined4 *)(in_ECX + 0x78) = uVar1;
    if (*(int *)(in_ECX + 0x78) == 0) {
      thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a08b0,0x401,s_mpLocInfo_004a08a4);
    }
  }
  thunk_FUN_004293c6(param_1,param_2,param_3);
  return;
}
```

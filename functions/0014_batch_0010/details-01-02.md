# 0014_batch_0010 — détails (2/3)

## FUN_004428b0 — 0x4428b0

- Classification : internal
- Corps : `0x4428b0–0x442903`
- État : pseudocode obtenu
- Evidence : `ev_48f75f7aefb09b23a7acb486761aa64fada114c3952a9e781cce1b116bcf0e4e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4019ba` — `thunk_FUN_0042a451`
- `0x401c85` — `thunk_FUN_00442920`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_004428b0(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004918ad;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0042a451();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494500;
  thunk_FUN_00442920();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_00442904 — 0x442904

- Classification : internal
- Corps : `0x442904–0x44291f`
- État : pseudocode obtenu
- Evidence : `ev_f915f12b8b575aefa09e2da5cffd0da8605fdf84b1816d5d54b32d9d44fe567c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402450` — `thunk_FUN_0042a4a5`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00442904(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494500;
  thunk_FUN_0042a4a5();
  return;
}
```

---

---

## FUN_00442920 — 0x442920

- Classification : internal
- Corps : `0x442920–0x442934`
- État : pseudocode obtenu
- Evidence : `ev_919dc9cf5769e6c974716cb25744be40803155a0ddf018afdbf49d8e0346b016`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00442920(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x78) = 0;
  return;
}
```

---

---

## FUN_00442935 — 0x442935

- Classification : internal
- Corps : `0x442935–0x442a7a`
- État : pseudocode obtenu
- Evidence : `ev_84c276fc02ea97bff2e784ce5c9b538c26a14edfce16f04100af061d85fcbeed`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x401361` — `thunk_FUN_00452bc5`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401569` — `thunk_FUN_0046c558`
- `0x401bf4` — `thunk_FUN_0042970c`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a0a84` — "IWLocInfo"
- `0x4a0a90` — "mpLocInfo"
- `0x4a0a9c` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0ab4` — "mpLocInfo"
- `0x4a0ac0` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0adc` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_00442935(short param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  int in_EDX;
  undefined2 uVar3;
  int extraout_EDX;
  
  uVar3 = (undefined2)((uint)in_EDX >> 0x10);
  if (param_1 == 1) {
    if (*(int *)(in_ECX + 0x78) == 0) {
      uVar2 = thunk_FUN_0046c558(s_IWLocInfo_004a0a84,3,0);
      *(undefined4 *)(in_ECX + 0x78) = uVar2;
      in_EDX = in_ECX;
      if (*(int *)(in_ECX + 0x78) == 0) {
        thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0a9c,0x515,s_mpLocInfo_004a0a90);
        in_EDX = extraout_EDX;
      }
    }
    uVar3 = (undefined2)((uint)in_EDX >> 0x10);
  }
  else if ((5 < param_1) && (param_1 < 8)) {
    iVar1 = thunk_FUN_00429f3a();
    if (iVar1 != 0) {
      if (*(int *)(in_ECX + 0x78) == 0) {
        thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0ac0,0x524,s_mpLocInfo_004a0ab4);
      }
      if (*(int *)(*(int *)(in_ECX + 0x78) + 0x70) == 0) {
        thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0adc,0x527,&DAT_004a0ad8);
      }
      iVar1 = thunk_FUN_00452bc5(DAT_0049f538);
      if (iVar1 != 0) {
        thunk_FUN_0042970c(*(undefined2 *)(in_ECX + 0x60),*(undefined4 *)(in_ECX + 100),
                           *(undefined4 *)(in_ECX + 0x68));
      }
      return 1;
    }
    return 0;
  }
  uVar2 = thunk_FUN_004293c6(CONCAT22(uVar3,param_1),param_2,param_3);
  return uVar2;
}
```

---

---

## FUN_00442a7b — 0x442a7b

- Classification : internal
- Corps : `0x442a7b–0x442b9b`
- État : pseudocode obtenu
- Evidence : `ev_6add30592d3f7a2edbaf5ea8352ea795b80c4c77b0457b6747bd9f57f068c5c6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40106e` — `thunk_FUN_0042a55d`
- `0x40119a` — `thunk_FUN_0045ff6d`
- `0x401361` — `thunk_FUN_00452bc5`
- `0x4014e7` — `thunk_FUN_0045035a`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a0af4` — "mpLocInfo"
- `0x4a0b00` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
void FUN_00442a7b(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int in_ECX;
  undefined2 extraout_var;
  undefined4 uVar3;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    if (*(int *)(in_ECX + 0x78) == 0) {
      uVar3 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0b00,0x53d,s_mpLocInfo_004a0af4);
    }
    else {
      uVar3 = 0;
    }
    iVar2 = *(int *)(*(int *)(in_ECX + 0x78) + 0x70);
    if (iVar2 == 0) {
      *(undefined4 *)(in_ECX + 0x38) = 0;
    }
    else {
      iVar1 = thunk_FUN_00452bc5(DAT_0049f538);
      if (iVar1 == 0) {
        *(undefined4 *)(in_ECX + 0x38) = 0;
      }
      else {
        *(undefined4 *)(in_ECX + 0x38) = 1;
        uVar3 = thunk_FUN_0045035a(uVar3);
        iVar2 = thunk_FUN_0045ff6d(CONCAT22(extraout_var,*(undefined2 *)(iVar2 + 8)),uVar3);
        if (iVar2 == 0) {
          *(undefined2 *)(in_ECX + 0x72) = 0;
        }
        else if ((DAT_004c2b64 % 2 != 0) &&
                (*(short *)(in_ECX + 0x72) = *(short *)(in_ECX + 0x72) + 1,
                *(short *)(in_ECX + 0x70) <= *(short *)(in_ECX + 0x72))) {
          *(undefined2 *)(in_ECX + 0x72) = 1;
        }
        thunk_FUN_0042a55d(param_1);
      }
    }
  }
  return;
}
```

---

---

## FUN_00442b9c — 0x442b9c

- Classification : internal
- Corps : `0x442b9c–0x442bef`
- État : pseudocode obtenu
- Evidence : `ev_01e89dcce3bcb15aa96d05c9a5a743a940cbe9b5c3756a00b9fe26860a61590d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401271` — `thunk_FUN_00442c0c`
- `0x4019ba` — `thunk_FUN_0042a451`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00442b9c(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004918c0;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0042a451();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494518;
  thunk_FUN_00442c0c();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_00442bf0 — 0x442bf0

- Classification : internal
- Corps : `0x442bf0–0x442c0b`
- État : pseudocode obtenu
- Evidence : `ev_6c5eb33ba8275e3d8fd86c969e5eaabb431735566b714a2d1dc48ea42964b175`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402450` — `thunk_FUN_0042a4a5`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00442bf0(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494518;
  thunk_FUN_0042a4a5();
  return;
}
```

---

---

## FUN_00442c0c — 0x442c0c

- Classification : internal
- Corps : `0x442c0c–0x442c20`
- État : pseudocode obtenu
- Evidence : `ev_14462cba2c3cf5dc05c8e99e04e30fea49282325dd291fac0d5bc88061f412fc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00442c0c(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x78) = 0;
  return;
}
```

---

---

## FUN_00442c21 — 0x442c21

- Classification : internal
- Corps : `0x442c21–0x442d5f`
- État : pseudocode obtenu
- Evidence : `ev_703ad5b5f4db571b2189374a9c8605eacba3f5c981927504174a2b583929560a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401569` — `thunk_FUN_0046c558`
- `0x401802` — `thunk_FUN_00452b67`
- `0x401bf4` — `thunk_FUN_0042970c`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a0b18` — "IWLocInfo"
- `0x4a0b24` — "mpLocInfo"
- `0x4a0b30` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0b48` — "mpLocInfo"
- `0x4a0b54` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0b70` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_00442c21(short param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined4 uVar3;
  
  if (param_1 == 1) {
    if (*(int *)(in_ECX + 0x78) == 0) {
      uVar2 = thunk_FUN_0046c558(s_IWLocInfo_004a0b18,3,0);
      *(undefined4 *)(in_ECX + 0x78) = uVar2;
      if (*(int *)(in_ECX + 0x78) == 0) {
        thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0b30,0x584,s_mpLocInfo_004a0b24);
      }
    }
  }
  else if ((5 < param_1) && (param_1 < 8)) {
    iVar1 = thunk_FUN_00429f3a();
    if (iVar1 != 0) {
      if (*(int *)(in_ECX + 0x78) == 0) {
        uVar2 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0b54,0x593,s_mpLocInfo_004a0b48);
      }
      else {
        uVar2 = 0;
      }
      if (*(int *)(*(int *)(in_ECX + 0x78) + 0x70) == 0) {
        uVar3 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0b70,0x596,&DAT_004a0b6c);
      }
      else {
        uVar3 = 0;
      }
      iVar1 = thunk_FUN_00452b67(uVar3,uVar2);
      if (iVar1 != 0) {
        thunk_FUN_0042970c(*(undefined2 *)(in_ECX + 0x60),*(undefined4 *)(in_ECX + 100),
                           *(undefined4 *)(in_ECX + 0x68));
      }
      return 1;
    }
    return 0;
  }
  uVar2 = thunk_FUN_004293c6(param_1,param_2,param_3);
  return uVar2;
}
```

---

---

## FUN_00442d60 — 0x442d60

- Classification : internal
- Corps : `0x442d60–0x442e8d`
- État : pseudocode obtenu
- Evidence : `ev_929784b34f22a7baf5a7f0892e53ed5eabb2a4364ac109a0d6f324e1b5475fd2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40106e` — `thunk_FUN_0042a55d`
- `0x4014e7` — `thunk_FUN_0045035a`
- `0x401802` — `thunk_FUN_00452b67`
- `0x4018b6` — `thunk_FUN_0045ff3f`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a0b88` — "mpLocInfo"
- `0x4a0b94` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0bb0` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
void FUN_00442d60(undefined4 param_1)

{
  int iVar1;
  int in_ECX;
  undefined2 extraout_var;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    if (*(int *)(in_ECX + 0x78) == 0) {
      uVar3 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0b94,0x5ac,s_mpLocInfo_004a0b88);
    }
    else {
      uVar3 = 0;
    }
    if (*(int *)(*(int *)(in_ECX + 0x78) + 0x70) == 0) {
      uVar2 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0bb0,0x5b4,&DAT_004a0bac);
    }
    else {
      uVar2 = 0;
    }
    iVar1 = thunk_FUN_00452b67(uVar2,uVar3);
    if (iVar1 == 0) {
      *(undefined4 *)(in_ECX + 0x38) = 0;
    }
    else {
      *(undefined4 *)(in_ECX + 0x38) = 1;
      uVar3 = thunk_FUN_0045035a();
      iVar1 = thunk_FUN_0045ff3f(CONCAT22(extraout_var,DAT_0049f53c),uVar3);
      if (iVar1 == 0) {
        *(undefined2 *)(in_ECX + 0x72) = 0;
      }
      else if ((DAT_004c2b64 % 2 != 0) &&
              (*(short *)(in_ECX + 0x72) = *(short *)(in_ECX + 0x72) + 1,
              *(short *)(in_ECX + 0x70) <= *(short *)(in_ECX + 0x72))) {
        *(undefined2 *)(in_ECX + 0x72) = 1;
      }
      thunk_FUN_0042a55d(param_1);
    }
  }
  return;
}
```

---

---

## FUN_00442e8e — 0x442e8e

- Classification : internal
- Corps : `0x442e8e–0x442ee1`
- État : pseudocode obtenu
- Evidence : `ev_f4b2764c2d8e7fa3aaca33cb25bdcccdfbe310e491d0a308f11112b6ea19f52a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`
- `0x401f5a` — `thunk_FUN_00442efe`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00442e8e(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004918d3;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494530;
  thunk_FUN_00442efe();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_00442ee2 — 0x442ee2

- Classification : internal
- Corps : `0x442ee2–0x442efd`
- État : pseudocode obtenu
- Evidence : `ev_c9f475c6a548bfbb6d90c1c15b179747a85a0e44b38015ad8b30cf940cb4b1f6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00442ee2(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494530;
  thunk_FUN_00429262();
  return;
}
```

---

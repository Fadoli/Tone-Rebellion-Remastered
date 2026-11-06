# 0014_batch_0010 — détails (1/3)

## FUN_004421f1 — 0x4421f1

- Classification : internal
- Corps : `0x4421f1–0x4423e5`
- État : pseudocode obtenu
- Evidence : `ev_5c9bc500c7692d38cdc0bf7295eab8cfa2962df6dc40171fc405f45049b8e1be`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40106e` — `thunk_FUN_0042a55d`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a08c8` — "mpLocInfo"
- `0x4a08d4` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a08f0` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0908` — "FALSE"
- `0x4a0910` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a092c` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0944` — "FALSE"
- `0x4a094c` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
void FUN_004421f1(undefined4 param_1)

{
  int iVar1;
  int in_ECX;
  undefined4 uVar2;
  uint local_c;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    if (*(int *)(in_ECX + 0x78) == 0) {
      thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a08d4,0x411,s_mpLocInfo_004a08c8);
    }
    iVar1 = *(int *)(*(int *)(in_ECX + 0x78) + 0x70);
    if (iVar1 == 0) {
      thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a08f0,0x417,&DAT_004a08ec);
    }
    local_c = 0xffffffff;
    if (*(int *)(iVar1 + 0x10) == 0x2a) {
      if (*(char *)(in_ECX + 0x2a) == 'B') {
        local_c = (*(short *)(&DAT_0061a588 + DAT_0049f538 * 0x14a0) + 1) % 3;
      }
      else if (*(char *)(in_ECX + 0x2a) == 'C') {
        local_c = (*(short *)(&DAT_0061a58a + DAT_0049f538 * 0x14a0) + 1) % 3;
      }
      else if (*(char *)(in_ECX + 0x2a) == 'M') {
        local_c = (*(short *)(&DAT_0061a58c + DAT_0049f538 * 0x14a0) + 1) % 3;
      }
      else {
        thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0910,0x426,s_FALSE_004a0908);
      }
    }
    else if (*(short *)(iVar1 + 0x18) != -1) {
      iVar1 = thunk_FUN_00450385();
      if (iVar1 == 0) {
        uVar2 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a092c,0x42b,&DAT_004a0928);
      }
      else {
        uVar2 = 0;
      }
      if (*(char *)(in_ECX + 0x29) == 'C') {
        local_c = (uint)(*(int *)(iVar1 + 0x58) != 0);
      }
      else if (*(char *)(in_ECX + 0x29) == 'M') {
        local_c = (uint)(*(int *)(iVar1 + 0x5c) != 0);
      }
      else {
        thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a094c,0x431,s_FALSE_004a0944,uVar2);
      }
    }
    if (local_c != 0xffffffff) {
      *(undefined2 *)(in_ECX + 0x72) = (undefined2)local_c;
    }
    thunk_FUN_0042a55d(param_1);
  }
  return;
}
```

---

---

## FUN_004423e6 — 0x4423e6

- Classification : internal
- Corps : `0x4423e6–0x442439`
- État : pseudocode obtenu
- Evidence : `ev_220eb635adc291b3be51f961290a60e4759b1cfb5983d43098ca13baff47f2fa`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4019ba` — `thunk_FUN_0042a451`
- `0x402068` — `thunk_FUN_00442456`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_004423e6(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491887;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0042a451();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004944d0;
  thunk_FUN_00442456();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0044243a — 0x44243a

- Classification : internal
- Corps : `0x44243a–0x442455`
- État : pseudocode obtenu
- Evidence : `ev_604b7fb3eab5901e9c42d5921481774d7c169081331eb674a674f6114bf5954e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402450` — `thunk_FUN_0042a4a5`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044243a(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004944d0;
  thunk_FUN_0042a4a5();
  return;
}
```

---

---

## FUN_00442456 — 0x442456

- Classification : internal
- Corps : `0x442456–0x44246a`
- État : pseudocode obtenu
- Evidence : `ev_c910dc3caa85bb6c58c392ed62d8155ef8fec6afe781e79679104d0684d062b9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00442456(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x78) = 0;
  return;
}
```

---

---

## FUN_0044246b — 0x44246b

- Classification : internal
- Corps : `0x44246b–0x4424eb`
- État : pseudocode obtenu
- Evidence : `ev_a6b12e2d967de861963d06f9468a6ee1e51f7c7c0b55c6d958322a269dd3e70b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`
- `0x401569` — `thunk_FUN_0046c558`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a0964` — "IWLocInfo"
- `0x4a0970` — "mpLocInfo"
- `0x4a097c` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
void FUN_0044246b(short param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int in_ECX;
  
  if ((param_1 == 1) && (*(int *)(in_ECX + 0x78) == 0)) {
    uVar1 = thunk_FUN_0046c558(s_IWLocInfo_004a0964,3,0);
    *(undefined4 *)(in_ECX + 0x78) = uVar1;
    if (*(int *)(in_ECX + 0x78) == 0) {
      thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a097c,0x45c,s_mpLocInfo_004a0970);
    }
  }
  thunk_FUN_004293c6(param_1,param_2,param_3);
  return;
}
```

---

---

## FUN_004424ec — 0x4424ec

- Classification : internal
- Corps : `0x4424ec–0x4425a0`
- État : pseudocode obtenu
- Evidence : `ev_5d636ac91c47f5d8ae3058c57a72459392ce898960650fc37808b74860bd2854`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40106e` — `thunk_FUN_0042a55d`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a0994` — "mpLocInfo"
- `0x4a09a0` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a09bc` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
void FUN_004424ec(undefined4 param_1)

{
  int iVar1;
  int in_ECX;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    if (*(int *)(in_ECX + 0x78) == 0) {
      thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a09a0,0x46c,s_mpLocInfo_004a0994);
    }
    iVar1 = *(int *)(*(int *)(in_ECX + 0x78) + 0x70);
    if (iVar1 == 0) {
      thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a09bc,0x472,&DAT_004a09b8);
    }
    *(undefined2 *)(in_ECX + 0x72) = 0;
    if ((*(uint *)(iVar1 + 0x1c) & 0x400) != 0) {
      *(undefined2 *)(in_ECX + 0x72) = 1;
    }
    thunk_FUN_0042a55d(param_1);
  }
  return;
}
```

---

---

## FUN_004425a1 — 0x4425a1

- Classification : internal
- Corps : `0x4425a1–0x4425f4`
- État : pseudocode obtenu
- Evidence : `ev_c6f686fc97f39d66b1a9b223346b44348da76f0326644c8a0424612b07fe9414`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018f2` — `thunk_FUN_00442611`
- `0x4019ba` — `thunk_FUN_0042a451`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_004425a1(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049189a;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0042a451();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004944e8;
  thunk_FUN_00442611();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_004425f5 — 0x4425f5

- Classification : internal
- Corps : `0x4425f5–0x442610`
- État : pseudocode obtenu
- Evidence : `ev_61b043e10c26b9c6b29cf5da59e91fc12adefee62e1efa6c7c5232241962ce8c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402450` — `thunk_FUN_0042a4a5`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004425f5(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004944e8;
  thunk_FUN_0042a4a5();
  return;
}
```

---

---

## FUN_00442611 — 0x442611

- Classification : internal
- Corps : `0x442611–0x442625`
- État : pseudocode obtenu
- Evidence : `ev_006ef2b48e41a9555733fc1fcc52d70796b96daa1588ff766bf27772873e73e4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00442611(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x78) = 0;
  return;
}
```

---

---

## FUN_00442626 — 0x442626

- Classification : internal
- Corps : `0x442626–0x442798`
- État : pseudocode obtenu
- Evidence : `ev_c4706e8b8d2484fb855c8b776dbfc6e008bd63abe093cd88fc5ecf9bf6ac8620`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401569` — `thunk_FUN_0046c558`
- `0x4018ac` — `thunk_FUN_0045c89b`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x401bf4` — `thunk_FUN_0042970c`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a09d4` — "IWLocInfo"
- `0x4a09e0` — "mpLocInfo"
- `0x4a09ec` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0a04` — "mpLocInfo"
- `0x4a0a10` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0a2c` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0a48` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_00442626(short param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (param_1 == 1) {
    if (*(int *)(in_ECX + 0x78) == 0) {
      uVar2 = thunk_FUN_0046c558(s_IWLocInfo_004a09d4,3,0);
      *(undefined4 *)(in_ECX + 0x78) = uVar2;
      if (*(int *)(in_ECX + 0x78) == 0) {
        thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a09ec,0x49d,s_mpLocInfo_004a09e0);
      }
    }
  }
  else if ((5 < param_1) && (param_1 < 8)) {
    iVar1 = thunk_FUN_00429f3a();
    if (iVar1 != 0) {
      if (*(int *)(in_ECX + 0x78) == 0) {
        uVar2 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0a10,0x4ac,s_mpLocInfo_004a0a04);
      }
      else {
        uVar2 = 0;
      }
      if (*(int *)(*(int *)(in_ECX + 0x78) + 0x70) == 0) {
        uVar4 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0a2c,0x4af,&DAT_004a0a28);
      }
      else {
        uVar4 = 0;
      }
      iVar1 = thunk_FUN_00450385();
      if (iVar1 == 0) {
        uVar3 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0a48,0x4b2,&DAT_004a0a44);
      }
      else {
        uVar3 = 0;
      }
      iVar1 = thunk_FUN_0045c89b(uVar3,uVar4,uVar2);
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

## FUN_00442799 — 0x442799

- Classification : internal
- Corps : `0x442799–0x4428af`
- État : pseudocode obtenu
- Evidence : `ev_78a83923a5fc89e419de6ca46026d63484c5de2c5ffc651ae55defddb7b4bf72`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40106e` — `thunk_FUN_0042a55d`
- `0x4018ac` — `thunk_FUN_0045c89b`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4020bd` — `thunk_FUN_0045c9fe`

### Chaînes référencées

- `0x4a0a60` — "mpLocInfo"
- `0x4a0a6c` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
void FUN_00442799(undefined4 param_1)

{
  int iVar1;
  int in_ECX;
  undefined4 uVar2;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    if (*(int *)(in_ECX + 0x78) == 0) {
      uVar2 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0a6c,0x4c8,s_mpLocInfo_004a0a60);
    }
    else {
      uVar2 = 0;
    }
    if (*(int *)(*(int *)(in_ECX + 0x78) + 0x70) == 0) {
      *(undefined4 *)(in_ECX + 0x38) = 0;
    }
    else {
      iVar1 = thunk_FUN_00450385(uVar2);
      if (iVar1 == 0) {
        *(undefined4 *)(in_ECX + 0x38) = 0;
      }
      else {
        iVar1 = thunk_FUN_0045c89b();
        if (iVar1 == 0) {
          *(undefined4 *)(in_ECX + 0x38) = 0;
        }
        else {
          *(undefined4 *)(in_ECX + 0x38) = 1;
          iVar1 = thunk_FUN_0045c9fe();
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
    }
  }
  return;
}
```

---

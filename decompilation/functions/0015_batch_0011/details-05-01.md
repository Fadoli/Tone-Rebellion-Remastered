# 0015_batch_0011 — détails (1/3)

## FUN_004526de — 0x4526de

- Classification : internal
- Corps : `0x4526de–0x452793`
- État : pseudocode obtenu
- Evidence : `ev_362f18c1c5d6399f0ca1abb08a88f3f9516320b6a45fd5724a68079716b6da56`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021ad` — `thunk_FUN_004641de`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004526de(undefined4 param_1,int param_2)

{
  int iVar1;
  int in_ECX;
  int local_10;
  
  local_10 = 0;
  if ((param_2 < 0) || (3 < param_2)) {
    if (param_2 == 4) {
      local_10 = DAT_0061e478;
    }
  }
  else {
    local_10 = *(int *)(&DAT_006191f8 + param_2 * 0x14a0);
  }
  if ((((*(int *)(in_ECX + 0x14) == -1) || (*(int *)(in_ECX + 0x14) == param_2)) &&
      ((*(int *)(in_ECX + 0x10) == 0 || (*(int *)(in_ECX + 0x10) == 1)))) &&
     ((((int)*(char *)(in_ECX + 0x22) & 1 << ((byte)param_2 & 0x1f)) != 0 &&
      (iVar1 = thunk_FUN_004641de(param_2,param_1), *(short *)(iVar1 + 0xc) <= local_10)))) {
    return 1;
  }
  return 0;
}
```

---

---

## FUN_00452794 — 0x452794

- Classification : internal
- Corps : `0x452794–0x4527ed`
- État : pseudocode obtenu
- Evidence : `ev_e884123140e558d8678b40fa79da6539532f8441ffe895daabdad5787c8afff7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a1e` — `thunk_FUN_004526de`
- `0x401ae6` — `thunk_FUN_00450305`
- `0x4021ad` — `thunk_FUN_004641de`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00452794(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = thunk_FUN_004526de(param_1,param_2);
  if (iVar1 != 0) {
    iVar1 = thunk_FUN_00450305(1);
    iVar2 = thunk_FUN_004641de(param_2,param_1);
    if (*(short *)(iVar2 + 4) <= iVar1) {
      return 1;
    }
  }
  return 0;
}
```

---

---

## FUN_004527ee — 0x4527ee

- Classification : internal
- Corps : `0x4527ee–0x452858`
- État : pseudocode obtenu
- Evidence : `ev_ff5099639bbdcb8c257ae4e8f690ea98f0ebdf4321753ff832e66ba4dc11d800`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401924` — `thunk_FUN_00453a5f`
- `0x401adc` — `thunk_FUN_00416a9a`
- `0x402243` — `thunk_FUN_00452794`
- `0x4024ff` — `thunk_FUN_004528ca`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_004527ee(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int in_ECX;
  
  iVar1 = thunk_FUN_00452794(param_1,param_2);
  if (iVar1 != 0) {
    thunk_FUN_004528ca(param_1,param_2);
    *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 0x10;
    thunk_FUN_00453a5f();
    thunk_FUN_00416a9a(2,in_ECX);
  }
  return iVar1 != 0;
}
```

---

---

## FUN_00452859 — 0x452859

- Classification : internal
- Corps : `0x452859–0x4528c9`
- État : pseudocode obtenu
- Evidence : `ev_a571ddb810f57eb82ddb7110d751957927677498282088ff2bc3d5256611b345`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401320` — `thunk_FUN_00452656`
- `0x401924` — `thunk_FUN_00453a5f`
- `0x401adc` — `thunk_FUN_00416a9a`
- `0x4024ff` — `thunk_FUN_004528ca`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00452859(int param_1,undefined4 param_2)

{
  int iVar1;
  int in_ECX;
  undefined4 local_8;
  
  local_8 = 0;
  iVar1 = thunk_FUN_00452656(param_1,param_2);
  if (iVar1 != 0) {
    thunk_FUN_004528ca(param_1,param_2);
    if (param_1 == 5) {
      *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) & 0xffffffef;
    }
    thunk_FUN_00453a5f();
    thunk_FUN_00416a9a(2,in_ECX);
    local_8 = 1;
  }
  return local_8;
}
```

---

---

## FUN_004528ca — 0x4528ca

- Classification : internal
- Corps : `0x4528ca–0x452a14`
- État : pseudocode obtenu
- Evidence : `ev_f43c86a4fb902537253e5af3631a3875fbaf57fbb356887e3d1e995894c6114b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4015f0` — `thunk_FUN_00466c8b`
- `0x40181b` — `thunk_FUN_00450978`
- `0x401906` — `thunk_FUN_0045c325`
- `0x401aeb` — `thunk_FUN_00452fcb`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4022cf` — `thunk_FUN_0045ee26`

### Chaînes référencées

- `0x4a2a54` — "mStaffBld!=-1"
- `0x4a2a64` — "C:\\float\\src\\pad.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_004528ca(int param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  int in_ECX;
  
  *(int *)(in_ECX + 0x10) = param_1;
  *(undefined2 *)(in_ECX + 0x30) = 0;
  *(undefined2 *)(in_ECX + 0x2c) = 0;
  *(undefined2 *)(in_ECX + 0x2a) = 0;
  *(undefined2 *)(in_ECX + 0x28) = 0;
  *(undefined2 *)(in_ECX + 0x4a) = 0;
  *(undefined2 *)(in_ECX + 0x32) = 1;
  *(int *)(in_ECX + 0x14) = param_2;
  uVar1 = thunk_FUN_00450978();
  *(undefined2 *)(in_ECX + 0x34) = uVar1;
  if (((param_2 != 4) || (*(int *)(in_ECX + 0x24) < 5)) || (0x21 < *(int *)(in_ECX + 0x24))) {
    *(undefined4 *)(in_ECX + 0x24) = 0;
  }
  *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) & 0xfffffffe;
  *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 0x410;
  if ((*(int *)(in_ECX + 4) == 0) && (param_2 == 4)) {
    *(undefined1 *)(in_ECX + 0x22) = 0;
  }
  thunk_FUN_00452fcb();
  if ((0x2b < param_1) && (param_1 < 0x33)) {
    iVar2 = thunk_FUN_0045ee26(in_ECX);
    if (iVar2 == 0) {
      return 0;
    }
    uVar1 = thunk_FUN_0045c325();
    *(undefined2 *)(in_ECX + 0x18) = uVar1;
    if (*(short *)(in_ECX + 0x18) == -1) {
      thunk_FUN_00414b64(s_C__float_src_pad_cpp_004a2a64,0x5ba,s_mStaffBld___1_004a2a54);
    }
  }
  thunk_FUN_00466c8b((int)*(short *)(in_ECX + 8));
  return 1;
}
```

---

---

## FUN_00452a15 — 0x452a15

- Classification : internal
- Corps : `0x452a15–0x452ae6`
- État : pseudocode obtenu
- Evidence : `ev_e2908a2ae8af51fad1abf37e192dc5cf25142c2b8ab72ef3ca34fe1019d57031`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014e7` — `thunk_FUN_0045035a`
- `0x4015f0` — `thunk_FUN_00466c8b`
- `0x401848` — `thunk_FUN_00460029`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00452a15(void)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined2 extraout_var;
  undefined4 local_c;
  
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    uVar2 = thunk_FUN_0045035a();
    thunk_FUN_00460029(CONCAT22(extraout_var,*(undefined2 *)(in_ECX + 8)),uVar2);
  }
  iVar1 = *(int *)(in_ECX + 0x14);
  *(undefined4 *)(in_ECX + 0x14) = 0xffffffff;
  if (((iVar1 == 4) && (4 < *(int *)(in_ECX + 0x24))) && (*(int *)(in_ECX + 0x24) < 0x22)) {
    *(undefined4 *)(in_ECX + 0x10) = 1;
  }
  else {
    *(undefined4 *)(in_ECX + 0x10) = 0;
    *(undefined4 *)(in_ECX + 0x24) = 0;
  }
  *(undefined2 *)(in_ECX + 0x18) = 0xffff;
  *(undefined2 *)(in_ECX + 0x2c) = 0;
  *(undefined2 *)(in_ECX + 0x2a) = 0;
  *(undefined2 *)(in_ECX + 0x28) = 0;
  thunk_FUN_00466c8b((int)*(short *)(in_ECX + 8));
  return 1;
}
```

---

---

## FUN_00452ae7 — 0x452ae7

- Classification : internal
- Corps : `0x452ae7–0x452b66`
- État : pseudocode obtenu
- Evidence : `ev_8054edfd10b785a40bad2e36221223e666d7d51486d0f35eee8627820370398b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013c0` — `thunk_FUN_004655b2`
- `0x401965` — `thunk_FUN_00452a15`
- `0x401ed8` — `thunk_FUN_0045efd2`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00452ae7(void)

{
  int in_ECX;
  undefined4 local_c;
  uint local_8;
  
  local_c = 8;
  local_8 = (int)*(short *)(in_ECX + 8) << 0x10 |
            (in_ECX - (int)(&DAT_005ec640 + *(short *)(in_ECX + 8) * 0x29e8)) / 0x60;
  thunk_FUN_004655b2(&local_c);
  if (*(int *)(in_ECX + 0x14) != -1) {
    thunk_FUN_0045efd2(in_ECX);
  }
  thunk_FUN_00452a15();
  return;
}
```

---

---

## FUN_00452b67 — 0x452b67

- Classification : internal
- Corps : `0x452b67–0x452bc4`
- État : pseudocode obtenu
- Evidence : `ev_6470cfabdc2556433f1dd93ac04237d1f61fd419a1b6c2030ce50919e70e5667`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40181b` — `thunk_FUN_00450978`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_00452b67(void)

{
  short sVar1;
  bool bVar2;
  short sVar3;
  int in_ECX;
  
  if ((((*(int *)(in_ECX + 0x14) < 0) || (3 < *(int *)(in_ECX + 0x14))) ||
      (*(int *)(in_ECX + 0x10) < 0x25)) || (0x34 < *(int *)(in_ECX + 0x10))) {
    bVar2 = false;
  }
  else {
    sVar1 = *(short *)(in_ECX + 0x34);
    sVar3 = thunk_FUN_00450978();
    bVar2 = sVar1 < sVar3;
  }
  return bVar2;
}
```

---

---

## FUN_00452bc5 — 0x452bc5

- Classification : internal
- Corps : `0x452bc5–0x452c30`
- État : pseudocode obtenu
- Evidence : `ev_a6d49220a7aa7891cd3a932e227e03cd30bb740eced76c3687379220c83aa0d3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00452bc5(byte param_1)

{
  int in_ECX;
  undefined4 local_8;
  
  local_8 = 0;
  if (((*(int *)(in_ECX + 0x14) < 0) || (3 < *(int *)(in_ECX + 0x14))) ||
     (*(int *)(in_ECX + 0x10) != 0x28)) {
    local_8 = 0;
  }
  else if ((((int)*(char *)(in_ECX + 0x22) & 1 << (param_1 & 0x1f)) != 0) &&
          ((*(uint *)(in_ECX + 0x1c) & 0x800 << (param_1 & 0x1f)) == 0)) {
    local_8 = 1;
  }
  return local_8;
}
```

---

---

## FUN_00452c31 — 0x452c31

- Classification : internal
- Corps : `0x452c31–0x452cea`
- État : pseudocode obtenu
- Evidence : `ev_5a0471841e28e1e0c4403918c700d2132239a49d2aa7fc4f4f06dd84f78fb7a0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_00452c31(int param_1)

{
  int in_ECX;
  bool bVar1;
  
  bVar1 = *(int *)(in_ECX + 0x24) == param_1;
  if ((*(int *)(in_ECX + 0x10) == 0x2a) &&
     ((((param_1 == 1 && (0 < *(short *)(in_ECX + 0x28))) ||
       ((param_1 == 2 && (0 < *(short *)(in_ECX + 0x2a))))) ||
      ((param_1 == 3 && (0 < *(short *)(in_ECX + 0x2c))))))) {
    bVar1 = true;
  }
  if (((*(int *)(in_ECX + 0x14) != -1) &&
      (((*(int *)(in_ECX + 0x10) == 0x2a || (*(short *)(in_ECX + 0x18) != -1)) && (4 < param_1))))
     && ((param_1 < 0x22 &&
         (0 < *(short *)(&DAT_006191fc + param_1 * 2 + *(int *)(in_ECX + 0x14) * 0x14a0))))) {
    bVar1 = true;
  }
  return bVar1;
}
```

---

---

## FUN_00452ceb — 0x452ceb

- Classification : internal
- Corps : `0x452ceb–0x452e2a`
- État : pseudocode obtenu
- Evidence : `ev_636f5bb2277cb3418b09d0152d37b9c7b176bb6da1310e3794613756a3979c67`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00452ceb(int param_1,int param_2)

{
  int in_ECX;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  if (param_1 == 1) {
    if ((*(int *)(in_ECX + 0x14) == param_2) &&
       (((*(int *)(in_ECX + 0x10) == 0x25 && ((*(uint *)(in_ECX + 0x1c) & 1) != 0)) ||
        ((*(int *)(in_ECX + 0x10) == 0x2a &&
         ((*(short *)(&DAT_0061a588 + param_2 * 0x14a0) == 0 && (0 < *(short *)(in_ECX + 0x28)))))))
       )) {
      local_c = 1;
      local_14 = local_c;
    }
    else {
      local_c = 0;
      local_14 = local_c;
    }
  }
  else if (param_1 == 2) {
    if ((*(int *)(in_ECX + 0x14) == param_2) &&
       (((*(int *)(in_ECX + 0x10) == 0x27 && ((*(uint *)(in_ECX + 0x1c) & 1) != 0)) ||
        ((*(int *)(in_ECX + 0x10) == 0x2a &&
         ((*(short *)(&DAT_0061a58a + param_2 * 0x14a0) == 0 && (0 < *(short *)(in_ECX + 0x2a)))))))
       )) {
      local_10 = 1;
      local_14 = local_10;
    }
    else {
      local_10 = 0;
      local_14 = local_10;
    }
  }
  else if (param_1 == 3) {
    if ((*(int *)(in_ECX + 0x14) == param_2) &&
       (((*(int *)(in_ECX + 0x10) == 0x26 && ((*(uint *)(in_ECX + 0x1c) & 1) != 0)) ||
        ((*(int *)(in_ECX + 0x10) == 0x2a &&
         ((*(short *)(&DAT_0061a58c + param_2 * 0x14a0) == 0 && (0 < *(short *)(in_ECX + 0x2c)))))))
       )) {
      local_14 = 1;
    }
    else {
      local_14 = 0;
    }
  }
  else {
    local_14 = 0;
  }
  return local_14;
}
```

---

---

## FUN_00452e2b — 0x452e2b

- Classification : internal
- Corps : `0x452e2b–0x452e4c`
- État : pseudocode obtenu
- Evidence : `ev_50b787cc3ab559f485e8b24562694aeeedfcc5940b0eab8001073461b3f42942`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40123a` — `thunk_FUN_0041e3eb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00452e2b(void)

{
  undefined2 *in_ECX;
  
  thunk_FUN_0041e3eb(*in_ECX,in_ECX[1]);
  return;
}
```

---

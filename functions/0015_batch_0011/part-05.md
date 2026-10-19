# 0015_batch_0011 — détails (5/6)

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

## FUN_00452e4d — 0x452e4d

- Classification : internal
- Corps : `0x452e4d–0x452eab`
- État : pseudocode obtenu
- Evidence : `ev_40379ff22d87a9658901c7307389da5f012fecd75baea490d2f78fab5095de26`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012c6` — `thunk_FUN_00452c31`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_00452e4d(undefined4 param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int in_ECX;
  
  if (*(short *)(in_ECX + 0x36) < param_2) {
    *(undefined2 *)(in_ECX + 0x2c) = 0;
    iVar2 = thunk_FUN_00452c31(param_1);
    if (iVar2 == 0) {
      *(undefined2 *)(in_ECX + 0x36) = (undefined2)param_2;
    }
    else {
      *(undefined2 *)(in_ECX + 0x36) = 0;
    }
    bVar1 = iVar2 != 0;
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}
```

---

## FUN_00452eac — 0x452eac

- Classification : internal
- Corps : `0x452eac–0x452fca`
- État : pseudocode obtenu
- Evidence : `ev_bf2ec011afe579c598c1f57feca9b80c83515881336566e4cee78b69ee690ca7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00452eac(int param_1)

{
  undefined4 uVar1;
  int in_ECX;
  
  if (*(int *)(in_ECX + 0x24) == param_1) {
    *(undefined4 *)(in_ECX + 0x24) = 0;
    return 1;
  }
  if (*(int *)(in_ECX + 0x10) == 0x2a) {
    if ((param_1 == 1) && (0 < *(short *)(in_ECX + 0x28))) {
      *(short *)(in_ECX + 0x28) = *(short *)(in_ECX + 0x28) + -1;
      return 1;
    }
    if ((param_1 == 2) && (0 < *(short *)(in_ECX + 0x2a))) {
      *(short *)(in_ECX + 0x2a) = *(short *)(in_ECX + 0x2a) + -1;
      return 1;
    }
    if ((param_1 == 3) && (0 < *(short *)(in_ECX + 0x2c))) {
      *(short *)(in_ECX + 0x2c) = *(short *)(in_ECX + 0x2c) + -1;
      return 1;
    }
  }
  if (((param_1 < 5) || (0x21 < param_1)) ||
     (*(short *)(&DAT_006191fc + param_1 * 2 + *(int *)(in_ECX + 0x14) * 0x14a0) == 0)) {
    uVar1 = 0;
  }
  else {
    *(short *)(&DAT_006191fc + param_1 * 2 + *(int *)(in_ECX + 0x14) * 0x14a0) =
         *(short *)(&DAT_006191fc + param_1 * 2 + *(int *)(in_ECX + 0x14) * 0x14a0) + -1;
    uVar1 = 1;
  }
  return uVar1;
}
```

---

## FUN_00452fcb — 0x452fcb

- Classification : internal
- Corps : `0x452fcb–0x453029`
- État : pseudocode obtenu
- Evidence : `ev_ad379046d150a47e33c909d078bc56001a74f2bfe896e5777d7a43c22183dfbf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00452fcb(void)

{
  undefined2 uVar1;
  int in_ECX;
  
  *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) & 0xfffffff1;
  uVar1 = *(undefined2 *)(in_ECX + 0x3a);
  _memset((void *)(in_ECX + 0x3a),0,0x10);
  if ((*(int *)(in_ECX + 4) == 1) && (*(int *)(in_ECX + 0x10) == 5)) {
    *(undefined2 *)(in_ECX + 0x3a) = uVar1;
  }
  *(undefined2 *)(in_ECX + 0x3e) = 0xffff;
  return;
}
```

---

## FUN_0045302a — 0x45302a

- Classification : internal
- Corps : `0x45302a–0x4532e1`
- État : pseudocode obtenu
- Evidence : `ev_0de0703ceefe3d0910cdf3530d16f5de02e41149093f5fb125dc3789a667012e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4019a1` — `thunk_FUN_00450385`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401f6e` — `thunk_FUN_0045d5ba`

### Chaînes référencées

- `0x4a2a80` — "C:\\float\\src\\pad.cpp"

### Pseudocode Ghidra

```c
void FUN_0045302a(int param_1,int param_2,short *param_3)

{
  int iVar1;
  int in_ECX;
  
  if (*(int *)(in_ECX + 4) == 0) {
    if (((*(int *)(in_ECX + 0x10) == 1) && (4 < *(int *)(in_ECX + 0x24))) &&
       (*(int *)(in_ECX + 0x24) < 0x22)) {
      *(undefined4 *)(param_2 + *param_3 * 4) = 4;
      *param_3 = *param_3 + 1;
    }
    else if (0x24 < *(int *)(in_ECX + 0x10)) {
      if (*(int *)(in_ECX + 0x10) != 0x2a) {
        *(undefined4 *)(param_2 + *param_3 * 4) = 3;
        *param_3 = *param_3 + 1;
      }
      if (((*(int *)(in_ECX + 0x10) == 0x28) && (*(int *)(in_ECX + 0x14) != param_1)) &&
         ((-1 < *(int *)(in_ECX + 0x14) &&
          ((*(int *)(in_ECX + 0x14) < 4 &&
           ((*(uint *)(in_ECX + 0x1c) & 0x1000 << ((byte)param_1 & 0x1f)) == 0)))))) {
        *(undefined4 *)(param_2 + *param_3 * 4) = 0x14;
        *param_3 = *param_3 + 1;
      }
      if (*(int *)(in_ECX + 0x14) == param_1) {
        if (((*(int *)(in_ECX + 0x10) == 0x25) || (*(int *)(in_ECX + 0x10) == 0x26)) ||
           (*(int *)(in_ECX + 0x10) == 0x27)) {
          *(undefined4 *)(param_2 + *param_3 * 4) = 0;
          *param_3 = *param_3 + 1;
        }
        if (*(int *)(in_ECX + 0x10) == 0x2a) {
          *(undefined4 *)(param_2 + *param_3 * 4) = 7;
          *param_3 = *param_3 + 1;
          *(undefined4 *)(param_2 + *param_3 * 4) = 8;
          *param_3 = *param_3 + 1;
          *(undefined4 *)(param_2 + *param_3 * 4) = 9;
          *param_3 = *param_3 + 1;
          *(undefined4 *)(param_2 + *param_3 * 4) = 10;
          *param_3 = *param_3 + 1;
          *(undefined4 *)(param_2 + *param_3 * 4) = 0xb;
          *param_3 = *param_3 + 1;
          *(undefined4 *)(param_2 + *param_3 * 4) = 0xc;
          *param_3 = *param_3 + 1;
          *(undefined4 *)(param_2 + *param_3 * 4) = 0xd;
          *param_3 = *param_3 + 1;
          *(undefined4 *)(param_2 + *param_3 * 4) = 0xe;
          *param_3 = *param_3 + 1;
        }
        if (*(short *)(in_ECX + 0x18) != -1) {
          iVar1 = thunk_FUN_00450385();
          if (iVar1 == 0) {
            thunk_FUN_00414b64(s_C__float_src_pad_cpp_004a2a80,0x6f4,&DAT_004a2a7c);
          }
          thunk_FUN_0045d5ba(param_2,param_3);
        }
      }
    }
  }
  return;
}
```

---

## FUN_004532e2 — 0x4532e2

- Classification : internal
- Corps : `0x4532e2–0x45339a`
- État : pseudocode obtenu
- Evidence : `ev_f568b5a3b8f15baa665610518ba92d8599e54715db51c26ef29d327af6893104`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018a7` — `thunk_FUN_00462a87`
- `0x401adc` — `thunk_FUN_00416a9a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004532e2(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  short *in_ECX;
  
  if (*(int *)(in_ECX + 2) == 1) {
    in_ECX[0x17] = -1;
    iVar1 = thunk_FUN_00462a87(param_1,param_2,(int)*in_ECX,(int)in_ECX[1]);
    if (iVar1 != 0) {
      thunk_FUN_00416a9a(0,in_ECX);
      in_ECX[0x17] = (short)((iVar1 + -0x6137b8) / 0x4c);
      *(uint *)(iVar1 + 0x1c) = *(uint *)(iVar1 + 0x1c) | 0x801;
      *(undefined4 *)(iVar1 + 0x24) = 0;
      *(uint *)(in_ECX + 0xe) = *(uint *)(in_ECX + 0xe) | 2;
      in_ECX[0x21] = 0;
    }
  }
  return;
}
```

---

## FUN_0045339b — 0x45339b

- Classification : internal
- Corps : `0x45339b–0x4533a7`
- État : pseudocode obtenu
- Evidence : `ev_585844a2303e844a378075cacfb2955c99f44fb748086ca8ee5f26b101d4e376`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045339b(void)

{
  return;
}
```

---

## FUN_004533a8 — 0x4533a8

- Classification : internal
- Corps : `0x4533a8–0x4533fa`
- État : pseudocode obtenu
- Evidence : `ev_ea1eb17ffcfb1d626add98beb898547e3300aa138ca4a53a347a98ddaa58cb5c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401109` — `thunk_FUN_0041fdd9`
- `0x40219e` — `thunk_FUN_00420217`
- `0x4021ad` — `thunk_FUN_004641de`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004533a8(void)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  
  iVar1 = thunk_FUN_004641de(*(undefined4 *)(in_ECX + 0x14),*(undefined4 *)(in_ECX + 0x10));
  uVar2 = thunk_FUN_00420217((int)*(short *)(iVar1 + 10),0xffffffff,*(undefined4 *)(in_ECX + 0x14));
  thunk_FUN_0041fdd9(in_ECX);
  return uVar2;
}
```

---

## FUN_004533fb — 0x4533fb

- Classification : internal
- Corps : `0x4533fb–0x45343a`
- État : pseudocode obtenu
- Evidence : `ev_b321716b0f48ef294b895f1c519ab63b5ddadb93137ccee1904185717663c855`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401924` — `thunk_FUN_00453a5f`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x402496` — `thunk_FUN_0045ccb9`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004533fb(void)

{
  int in_ECX;
  
  if (*(short *)(in_ECX + 0x18) != -1) {
    thunk_FUN_00450385();
    thunk_FUN_0045ccb9();
  }
  *(undefined2 *)(in_ECX + 0x58) = 1;
  *(undefined2 *)(in_ECX + 0x46) = 0;
  thunk_FUN_00453a5f();
  return;
}
```

---

## FUN_0045343b — 0x45343b

- Classification : internal
- Corps : `0x45343b–0x4535ae`
- État : pseudocode obtenu
- Evidence : `ev_99af8b603208cc07b8cceabca553c38e1fe4b63fa92ecb882f08fac06155109a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401320` — `thunk_FUN_00452656`
- `0x4014c4` — `thunk_FUN_004535af`
- `0x401924` — `thunk_FUN_00453a5f`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x4019d3` — `thunk_FUN_0045ccce`
- `0x4024ff` — `thunk_FUN_004528ca`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045343b(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int in_ECX;
  
  if (param_1 == in_ECX) {
    *(undefined2 *)(in_ECX + 0x58) = 2;
    if (*(short *)(in_ECX + 0x46) < 8) {
      *(short *)(in_ECX + 0x46) = 0x10 - *(short *)(in_ECX + 0x46);
    }
    uVar1 = 1;
  }
  else if ((*(int *)(in_ECX + 0x14) == -1) &&
          ((*(int *)(in_ECX + 0x10) == 0 || (*(int *)(in_ECX + 0x10) == 1)))) {
    iVar2 = thunk_FUN_00452656(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14));
    if (iVar2 == 0) {
      uVar1 = 0;
    }
    else {
      thunk_FUN_004528ca(*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(param_1 + 0x14));
      *(undefined2 *)(in_ECX + 0x58) = 2;
      *(undefined2 *)(in_ECX + 0x46) = 0;
      if (param_1 != in_ECX) {
        *(undefined2 *)(in_ECX + 0x18) = *(undefined2 *)(param_1 + 0x18);
        *(undefined2 *)(in_ECX + 0x4a) = *(undefined2 *)(param_1 + 0x4a);
        *(undefined2 *)(in_ECX + 0x34) = *(undefined2 *)(param_1 + 0x34);
        *(undefined2 *)(in_ECX + 0x28) = *(undefined2 *)(param_1 + 0x28);
        *(undefined2 *)(in_ECX + 0x2a) = *(undefined2 *)(param_1 + 0x2a);
        *(undefined2 *)(in_ECX + 0x2c) = *(undefined2 *)(param_1 + 0x2c);
        *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) & 0xfffffbef;
        *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | *(uint *)(param_1 + 0x1c) & 0x400;
        if (*(short *)(in_ECX + 0x18) != -1) {
          thunk_FUN_00450385(in_ECX);
          thunk_FUN_0045ccce(in_ECX);
        }
        thunk_FUN_004535af();
      }
      thunk_FUN_00453a5f();
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
```

---

## FUN_004535af — 0x4535af

- Classification : internal
- Corps : `0x4535af–0x4535e3`
- État : pseudocode obtenu
- Evidence : `ev_dd00986704099c371d205cdd90e3a60794490d6bd9fe6ae8536f80ffa11dcec1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004535af(void)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x58) = 3;
  if (7 < *(short *)(in_ECX + 0x46)) {
    *(short *)(in_ECX + 0x46) = 0x10 - *(short *)(in_ECX + 0x46);
  }
  return;
}
```

---

## FUN_004535e4 — 0x4535e4

- Classification : internal
- Corps : `0x4535e4–0x45388e`
- État : pseudocode obtenu
- Evidence : `ev_31221e7fe9a9d051962a8feae7b513cf35e0906fe9cb40f2fa8885a9c8bde283`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014bf` — `thunk_FUN_00467260`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004535e4(void)

{
  int in_ECX;
  int iVar1;
  short asStackY_1000c [32732];
  int local_4c;
  short local_40;
  short local_3c;
  short local_38 [10];
  undefined *local_24;
  int local_20;
  short local_1c;
  short local_18;
  undefined1 *local_14;
  int local_10;
  short asStack_c [4];
  
  iVar1 = (int)*(short *)(in_ECX + 8);
  local_14 = &DAT_005ec218 + iVar1 * 0x29e8;
  local_10 = (int)(short)(&DAT_005eebf8)[iVar1 * 0x14f4];
  if ((short)(&DAT_005eebf8)[iVar1 * 0x14f4] < 0) {
    local_10 = 0;
  }
  if (0xe < local_10) {
    local_10 = 0xe;
  }
  local_1c = DAT_006136b0 + -1;
  local_38[0] = 0;
  local_38[1] = 0;
  local_38[2] = 0;
  local_38[3] = 0;
  if (*(short *)(in_ECX + 8) == (short)(DAT_006136b0 + -1)) {
    local_38[3] = 1;
    local_38[2] = 1;
    local_38[1] = 1;
    local_38[0] = 1;
  }
  else {
    local_3c = *(short *)(&DAT_004a28c8 + local_10 * 2);
    local_40 = *(short *)(&DAT_004a28e8 + local_10 * 2);
    if (local_3c < -1) {
      local_3c = -1;
    }
    if (3 < local_3c) {
      local_3c = 3;
    }
    if (local_40 < -1) {
      local_40 = -1;
    }
    if (3 < local_40) {
      local_40 = 3;
    }
    if (-1 < local_3c) {
      local_38[local_3c] = 1;
    }
    if (-1 < local_40) {
      local_38[local_40] = 1;
    }
  }
  local_38[4] = 0;
  local_38[5] = 0;
  local_38[6] = 0;
  local_38[7] = 0;
  local_24 = &DAT_005ec640 + iVar1 * 0x29e8;
  for (local_20 = 0; local_20 < (short)(&DAT_005eebc0)[iVar1 * 0x14f4]; local_20 = local_20 + 1) {
    if ((5 < *(int *)(local_24 + 0x10)) && (*(int *)(local_24 + 0x10) < 10)) {
      local_4c = *(int *)(local_24 + 0x10) + -6;
      if (local_4c < 0) {
        local_4c = 0;
      }
      if (3 < local_4c) {
        local_4c = 3;
      }
      local_38[local_4c + 4] = local_38[local_4c + 4] + 1;
    }
    local_24 = local_24 + 0x60;
  }
  local_18 = 0;
  for (local_20 = 0; local_20 < 4; local_20 = local_20 + 1) {
    if (local_38[local_20 + 4] < local_38[local_20]) {
      asStack_c[local_18] = (short)local_20;
      local_18 = local_18 + 1;
    }
  }
  if (local_18 == 0) {
    for (local_20 = 0; local_20 < 4; local_20 = local_20 + 1) {
      if (local_38[local_20] != 0) {
        asStack_c[local_18] = (short)local_20;
        local_18 = local_18 + 1;
      }
    }
  }
  if (local_18 < 1) {
    local_18 = 1;
  }
  if (4 < local_18) {
    local_18 = 4;
  }
  iVar1 = thunk_FUN_00467260((int)local_18);
  return asStack_c[iVar1] + 6;
}
```

---

## FUN_0045388f — 0x45388f

- Classification : internal
- Corps : `0x45388f–0x453957`
- État : pseudocode obtenu
- Evidence : `ev_553814d3beb7ec3f9ebdb9102fc26090e4d3cf1dea35923c504e7f6240ac792f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014bf` — `thunk_FUN_00467260`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045388f(void)

{
  int iVar1;
  int in_ECX;
  int local_1c;
  int local_18;
  uint local_14;
  int local_c;
  
  local_14 = 0xc;
  if (DAT_00618e48 == 1) {
    local_14 = 10;
  }
  else if (DAT_00618e48 == 0) {
    local_14 = 6;
  }
  local_18 = (int)((DAT_006136b0 - 1) + ((int)(DAT_006136b0 - 1) >> 0x1f & 3U)) >> 2;
  local_1c = (int)((int)*(short *)(in_ECX + 8) + ((int)*(short *)(in_ECX + 8) >> 0x1f & 3U)) >> 2;
  if (local_18 == 0) {
    local_18 = 1;
    local_1c = 1;
  }
  local_c = local_14 / 2 + (int)((local_14 - local_14 / 2) * local_1c) / local_18;
  if (local_c < 1) {
    local_c = 1;
  }
  if (0xc < local_c) {
    local_c = 0xc;
  }
  iVar1 = thunk_FUN_00467260(local_c);
  return *(undefined4 *)(&DAT_004a2948 + iVar1 * 4);
}
```

---

## FUN_00453958 — 0x453958

- Classification : internal
- Corps : `0x453958–0x4539e8`
- État : pseudocode obtenu
- Evidence : `ev_4e9d9f16ef59e1813c25b8fc8c49e2f90f67f2d8723ae7bf25cacaf07607a717`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00453958(void)

{
  int in_ECX;
  undefined4 local_10;
  undefined4 local_8;
  
  if ((((*(uint *)(in_ECX + 0x1c) & 0x90) == 0) &&
      ((((*(uint *)(in_ECX + 0x1c) & 0x400) != 0 || (*(short *)(in_ECX + 0x18) != -1)) ||
       (*(int *)(in_ECX + 4) == 1)))) &&
     ((((*(uint *)(in_ECX + 0x1c) & 0x100) == 0 || (*(short *)(in_ECX + 0x44) < 0x14)) &&
      (*(short *)(in_ECX + 0x58) == 0)))) {
    local_10 = 1;
  }
  else {
    local_10 = 0;
  }
  local_8 = local_10;
  if (*(int *)(in_ECX + 0x10) < 2) {
    local_8 = 0;
  }
  return local_8;
}
```

---

## FUN_004539e9 — 0x4539e9

- Classification : internal
- Corps : `0x4539e9–0x453a5e`
- État : pseudocode obtenu
- Evidence : `ev_ebff1d31012dd2ee16d0e674aa0911fd1c2dfed438f43d535755fb935b15d227`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401ff0` — `thunk_FUN_00453958`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004539e9(void)

{
  int iVar1;
  int in_ECX;
  
  if ((((*(int *)(in_ECX + 4) != 2) && (*(int *)(in_ECX + 4) != 3)) &&
      (*(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) & 0xfffffffe,
      *(int *)(in_ECX + 0x14) != -1)) &&
     ((iVar1 = thunk_FUN_00453958(), iVar1 != 0 &&
      ((*(int *)(in_ECX + 0x14) == 4 ||
       (((int)*(char *)(in_ECX + 0x22) & 1 << ((byte)*(undefined4 *)(in_ECX + 0x14) & 0x1f)) != 0)))
      ))) {
    *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 1;
  }
  return;
}
```

---


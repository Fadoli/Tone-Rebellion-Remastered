# 0015_batch_0011 — détails (2/3)

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

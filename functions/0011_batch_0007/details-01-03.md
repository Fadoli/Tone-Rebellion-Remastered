# 0011_batch_0007 — détails (3/3)

## FUN_00425084 — 0x425084

- Classification : internal
- Corps : `0x425084–0x4251a1`
- État : pseudocode obtenu
- Evidence : `ev_c90fab99fa7691b34572e2c9eba925751fbdf77b63a570c51574e19c416b7e0b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4016e0` — `thunk_FUN_00420635`
- `0x402347` — `thunk_FUN_004503bd`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00425084(void)

{
  short sVar1;
  int iVar2;
  int *in_ECX;
  undefined *local_18;
  int local_14;
  int local_10;
  undefined *local_c;
  
  if ((4 < in_ECX[6]) && (in_ECX[6] < 0x22)) {
    sVar1 = *(short *)((int)in_ECX + 0xe);
    local_c = (undefined *)0x0;
    local_18 = &DAT_005ec640 + sVar1 * 0x29e8;
    for (local_14 = 0; local_14 < (short)(&DAT_005eebc0)[sVar1 * 0x14f4]; local_14 = local_14 + 1) {
      if (((*(int *)(local_18 + 4) == 0) && (*(int *)(local_18 + 0x14) == -1)) &&
         (*(int *)(local_18 + 0x10) == 0)) {
        iVar2 = thunk_FUN_00420635(local_18);
        if ((iVar2 < local_10) || (local_c == (undefined *)0x0)) {
          local_c = local_18;
          local_10 = iVar2;
        }
      }
      local_18 = local_18 + 0x60;
    }
    if (local_c == (undefined *)0x0) {
      *(short *)(&DAT_006191fc + in_ECX[6] * 2 + *in_ECX * 0x14a0) =
           *(short *)(&DAT_006191fc + in_ECX[6] * 2 + *in_ECX * 0x14a0) + 1;
    }
    else {
      thunk_FUN_004503bd(in_ECX[6],1,*in_ECX);
    }
  }
  in_ECX[6] = 0;
  return;
}
```

---

---

## FUN_004251a2 — 0x4251a2

- Classification : internal
- Corps : `0x4251a2–0x42520d`
- État : pseudocode obtenu
- Evidence : `ev_4a090340fdb5742a1da4d57fcee3e5dab4e12ef3e9bc84cc8a5f77d842551412`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40130c` — `thunk_FUN_0045575c`
- `0x401933` — `thunk_FUN_00464242`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004251a2(int param_1)

{
  int iVar1;
  undefined4 *in_ECX;
  int local_8;
  
  if ((param_1 < 6) || ((7 < param_1 && (param_1 != 0x13)))) {
    local_8 = 0x14;
  }
  else {
    iVar1 = thunk_FUN_00464242(*in_ECX,in_ECX[1]);
    iVar1 = thunk_FUN_0045575c(*(undefined2 *)(iVar1 + 4));
    local_8 = (int)*(short *)(iVar1 + 0x44);
  }
  return local_8;
}
```

---

---

## FUN_0042520e — 0x42520e

- Classification : internal
- Corps : `0x42520e–0x425295`
- État : pseudocode obtenu
- Evidence : `ev_d705e9b610a1d7163ee2704a995cd045b34d0c12c1e49dd3c356d174ce206641`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40130c` — `thunk_FUN_0045575c`
- `0x401933` — `thunk_FUN_00464242`
- `0x4024be` — `thunk_FUN_004207c2`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0042520e(int param_1)

{
  int iVar1;
  undefined4 *in_ECX;
  undefined4 local_c;
  int local_8;
  
  local_8 = 0;
  if ((param_1 == 6) || (param_1 == 7)) {
    local_c = in_ECX[1];
    iVar1 = thunk_FUN_004207c2();
    if (iVar1 != 0) {
      local_c = 0;
    }
    iVar1 = thunk_FUN_00464242(*in_ECX,local_c);
    iVar1 = thunk_FUN_0045575c(*(undefined2 *)(iVar1 + 4));
    local_8 = ((int)*(short *)(iVar1 + 0x3e) - (int)*(short *)(iVar1 + 0x38)) *
              (int)*(short *)(iVar1 + 0x3c);
  }
  return local_8;
}
```

---

---

## FUN_00425296 — 0x425296

- Classification : internal
- Corps : `0x425296–0x4252f9`
- État : pseudocode obtenu
- Evidence : `ev_d396d19e963f440badee51e257f40dbdc0fb6b31511f19947e1809f3216d7ec1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00425296(int param_1)

{
  if (param_1 < 0x101) {
    if (param_1 == 0x100) {
      return 2000;
    }
    if (param_1 == 8) {
      return 0x28;
    }
  }
  else {
    if (param_1 == 0x1000) {
      return 0xdac;
    }
    if (param_1 == 0x2000) {
      return 0x2d;
    }
  }
  return 0x14;
}
```

---

---

## FUN_004252fa — 0x4252fa

- Classification : internal
- Corps : `0x4252fa–0x425387`
- État : pseudocode obtenu
- Evidence : `ev_b167d3cb2eae7790d14c1b84d495ac967fb8c04ad34e0f4acd791c8d1ee725a2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40116d` — `thunk_FUN_0041e4d9`
- `0x4017a3` — `thunk_FUN_0041e4c3`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401cee` — `thunk_FUN_0040fd80`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004252fa(undefined4 param_1,int param_2)

{
  undefined4 *in_ECX;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_5c [19];
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004915c9;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0041e4c3();
  local_8 = 0;
  if (param_2 == 0) {
    puVar2 = local_5c;
    for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *in_ECX;
      in_ECX = in_ECX + 1;
      puVar2 = puVar2 + 1;
    }
    thunk_FUN_0040fd80(local_5c,0x4c);
  }
  else {
    thunk_FUN_0040fc15(local_5c,0x4c);
    puVar2 = local_5c;
    for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
      *in_ECX = *puVar2;
      puVar2 = puVar2 + 1;
      in_ECX = in_ECX + 1;
    }
  }
  local_8 = 0xffffffff;
  thunk_FUN_0041e4d9();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

---

## FUN_00426fd0 — 0x426fd0

- Classification : internal
- Corps : `0x426fd0–0x42704a`
- État : pseudocode obtenu
- Evidence : `ev_6e955bf9310cdc3f643bbbd16bf122ccffc5893b26f16bd2fa2692f9a12f56c8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472c6c` — `__ftol`
- `0x477314` — `FUN_00477314`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00426fd0(int param_1)

{
  if ((*(uint *)(param_1 + 0x1c) & 8) == 0) {
    FUN_00477314((double)((DAT_00618e44 + (uint)*(byte *)(param_1 + 0x14)) % 0x30) *
                 0.13089958333333332);
  }
  __ftol();
  return;
}
```

---

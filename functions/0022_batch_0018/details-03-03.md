# 0022_batch_0018 — détails (3/3)

## FUN_004874b0 — 0x4874b0

- Classification : internal
- Corps : `0x4874b0–0x4874f8`
- État : pseudocode obtenu
- Evidence : `ev_0fc4d25c9a40d9ea0fb14687d2ceb8a9546c22063e4c3e2ed57bd494b2327af8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004874b0(int param_1,uint param_2)

{
  undefined4 uVar1;
  
  if ((((param_2._2_2_ & 0x7ff8) == 0x7ff0) && (((param_2 & 0x7ffff) != 0 || (param_1 != 0)))) ||
     ((param_2._2_2_ & 0x7ff8) == 0x7ff8)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
```

---

---

## FUN_00487500 — 0x487500

- Classification : internal
- Corps : `0x487500–0x4875d2`
- État : pseudocode obtenu
- Evidence : `ev_8ad5e9aca3c8687a5db5898dfc4cfb844751f6f0488320cc5d8e05b9305c789b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x486db0` — `FUN_00486db0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00487500(int param_1,uint param_2)

{
  int iVar1;
  
  if ((param_2._2_2_ & 0x7ff0) == 0x7ff0) {
    iVar1 = FUN_00486db0(param_1,param_2);
    if (iVar1 == 1) {
      iVar1 = 0x200;
    }
    else if (iVar1 == 2) {
      iVar1 = 4;
    }
    else if (iVar1 == 3) {
      iVar1 = 2;
    }
    else {
      iVar1 = 1;
    }
  }
  else if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    iVar1 = (-(uint)((param_2 & 0x80000000) != 0) & 0xffffff90) + 0x80;
  }
  else if ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) == 0.0) {
    iVar1 = (-(uint)((param_2 & 0x80000000) != 0) & 0xffffffe0) + 0x40;
  }
  else {
    iVar1 = (-(uint)((param_2 & 0x80000000) != 0) & 0xffffff08) + 0x100;
  }
  return iVar1;
}
```

---

---

## FUN_004875e0 — 0x4875e0

- Classification : internal
- Corps : `0x4875e0–0x487608`
- État : pseudocode obtenu
- Evidence : `ev_2d63c3defa7fef834cb4471a59d0e757e04333b4c483a85f33d0289fb6d8cb74`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x487610` — `FUN_00487610`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004875e0(void)

{
  if (DAT_00632988 == 0) {
    FUN_00487610();
    DAT_00632988 = DAT_00632988 + 1;
  }
  return;
}
```

---

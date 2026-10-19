# 0015_batch_0011 — détails (1/3)

## FUN_00450847 — 0x450847

- Classification : internal
- Corps : `0x450847–0x450977`
- État : pseudocode obtenu
- Evidence : `ev_d67bb548977ec77c1f77c72e0564f2d76b8dbcfb43be993689a173be09ac058f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013c0` — `thunk_FUN_004655b2`
- `0x401479` — `thunk_FUN_00452ae7`
- `0x401924` — `thunk_FUN_00453a5f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00450847(short param_1)

{
  int iVar1;
  int in_ECX;
  undefined4 local_c;
  uint local_8;
  
  if ((((*(uint *)(in_ECX + 0x1c) & 0x290) == 0) && (*(int *)(in_ECX + 0x10) != 0)) &&
     ((*(int *)(in_ECX + 4) == 0 || (*(int *)(in_ECX + 4) == 1)))) {
    if (*(int *)(in_ECX + 0x10) == 1) {
      if (*(int *)(in_ECX + 0x24) == 1) {
        if (param_1 * 2 < (int)*(short *)(in_ECX + 0x28)) {
          *(short *)(in_ECX + 0x28) = *(short *)(in_ECX + 0x28) + param_1 * -2;
        }
        else {
          thunk_FUN_00452ae7();
        }
        iVar1 = 1;
      }
      else {
        iVar1 = 0;
      }
    }
    else {
      *(short *)(in_ECX + 0x34) = *(short *)(in_ECX + 0x34) - param_1;
      if (*(short *)(in_ECX + 0x34) < 1) {
        if (*(int *)(in_ECX + 0x10) == 5) {
          thunk_FUN_00452ae7();
        }
        else {
          *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 0x80;
          *(undefined2 *)(in_ECX + 0x48) = 0;
          thunk_FUN_00453a5f();
          local_8 = (int)*(short *)(in_ECX + 8) << 0x10 |
                    (in_ECX - (int)(&DAT_005ec640 + *(short *)(in_ECX + 8) * 0x29e8)) / 0x60;
          local_c = 7;
          thunk_FUN_004655b2(&local_c);
        }
      }
      iVar1 = (int)param_1;
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}
```

---

---

## FUN_00450978 — 0x450978

- Classification : internal
- Corps : `0x450978–0x4509d9`
- État : pseudocode obtenu
- Evidence : `ev_c050c8da1c727f3840e46ba700e9d2c54ff80d0a24c9a1e397b5340b16c95f7e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021ad` — `thunk_FUN_004641de`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
short FUN_00450978(void)

{
  int iVar1;
  short sVar2;
  int in_ECX;
  
  if (((*(int *)(in_ECX + 0x14) == -1) || (*(int *)(in_ECX + 0x10) == 0)) ||
     (*(int *)(in_ECX + 0x10) == 1)) {
    sVar2 = -1;
  }
  else {
    iVar1 = thunk_FUN_004641de(*(undefined4 *)(in_ECX + 0x14),*(undefined4 *)(in_ECX + 0x10));
    sVar2 = *(short *)(iVar1 + 0xe) + *(short *)(in_ECX + 0x4a) * 5;
  }
  return sVar2;
}
```

---

---

## FUN_004509da — 0x4509da

- Classification : internal
- Corps : `0x4509da–0x450a70`
- État : pseudocode obtenu
- Evidence : `ev_a6d38c9065018f623c1c101d4bf01ab49efe10cb16b87a4cf1b3fbf6bc215635`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40181b` — `thunk_FUN_00450978`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004509da(short param_1)

{
  short sVar1;
  short sVar2;
  undefined2 uVar3;
  int in_ECX;
  
  *(short *)(in_ECX + 0x28) = *(short *)(in_ECX + 0x28) + -1;
  *(short *)(in_ECX + 0x2a) = *(short *)(in_ECX + 0x2a) + -1;
  if (*(short *)(in_ECX + 0x28) < 0) {
    *(undefined2 *)(in_ECX + 0x28) = 0;
  }
  if (*(short *)(in_ECX + 0x2a) < 0) {
    *(undefined2 *)(in_ECX + 0x2a) = 0;
  }
  *(short *)(in_ECX + 0x34) = *(short *)(in_ECX + 0x34) + param_1;
  sVar1 = *(short *)(in_ECX + 0x34);
  sVar2 = thunk_FUN_00450978();
  if (sVar2 < sVar1) {
    uVar3 = thunk_FUN_00450978();
    *(undefined2 *)(in_ECX + 0x34) = uVar3;
  }
  return 1;
}
```

---

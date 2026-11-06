# 0017_batch_0013 — détails (3/3)

## FUN_00466533 — 0x466533

- Classification : internal
- Corps : `0x466533–0x466636`
- État : pseudocode obtenu
- Evidence : `ev_60c18846051d1c9de7f9c0bb3864f2011570ff4b4dc637ff583c252cc3261ec3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b09` — `thunk_FUN_00420669`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00466533(int param_1)

{
  int iVar1;
  int in_ECX;
  int local_8;
  
  if ((param_1 != -1) && (*(int *)(in_ECX + 0x2c1a4 + param_1 * 0x14) != 0)) {
    if ((*(short *)(in_ECX + 0x2c1b4 + param_1 * 0x14) == 5) &&
       ((iVar1 = *(short *)(in_ECX + 0x2c1b2 + param_1 * 0x14) * 0x60 +
                 *(short *)(in_ECX + 0x2c1ae + param_1 * 0x14) * 0x29e8,
        *(int *)(&DAT_005ec640 + iVar1 + 0x10) == 0 || (*(int *)(&DAT_005ec640 + iVar1 + 0x10) == 1)
        ))) {
      *(undefined4 *)(&DAT_005ec640 + iVar1 + 0x14) = 0xffffffff;
    }
    *(undefined4 *)(in_ECX + 0x2c1a4 + param_1 * 0x14) = 0;
    *(short *)(in_ECX + 0x2c6a4) = *(short *)(in_ECX + 0x2c6a4) + -1;
    for (local_8 = 0; local_8 < 0x100; local_8 = local_8 + 1) {
      if ((&DAT_006137b8)[local_8 * 0x13] != -1) {
        thunk_FUN_00420669(param_1);
      }
    }
  }
  return;
}
```

---

---

## FUN_00466637 — 0x466637

- Classification : internal
- Corps : `0x466637–0x4666c8`
- État : pseudocode obtenu
- Evidence : `ev_43d56085237b963ecb4506c80a4cd8233d02dd6378afd4125dd828eeb777f354`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4020b3` — `thunk_FUN_00466533`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00466637(int param_1,short param_2,short param_3)

{
  int in_ECX;
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (0x3f < local_8) {
      return;
    }
    if ((((*(int *)(in_ECX + 0x2c1a4 + local_8 * 0x14) != 0) &&
         (*(short *)(in_ECX + 0x2c1b4 + local_8 * 0x14) == param_1)) &&
        (*(short *)(in_ECX + 0x2c1ae + local_8 * 0x14) == param_2)) &&
       (*(short *)(in_ECX + 0x2c1b2 + local_8 * 0x14) == param_3)) break;
    local_8 = local_8 + 1;
  }
  thunk_FUN_00466533(local_8);
  return;
}
```

---

---

## FUN_004666c9 — 0x4666c9

- Classification : internal
- Corps : `0x4666c9–0x466731`
- État : pseudocode obtenu
- Evidence : `ev_0c8c51a59fdb2f988bd482e72771ee0b1647993976a20ba06c5acf50340f4752`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014e7` — `thunk_FUN_0045035a`
- `0x401d1b` — `thunk_FUN_004662b7`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004666c9(int param_1,undefined2 param_2,int param_3)

{
  undefined1 local_14 [2];
  undefined2 local_12;
  undefined2 local_10;
  undefined2 local_a;
  undefined2 local_8;
  undefined2 local_6;
  
  _memset(local_14,0,0x10);
  local_12 = *(undefined2 *)(param_1 + 0x14);
  if (param_3 != -1) {
    local_12 = (undefined2)param_3;
  }
  local_a = *(undefined2 *)(param_1 + 8);
  local_8 = thunk_FUN_0045035a();
  local_10 = 4;
  local_6 = param_2;
  thunk_FUN_004662b7(local_14);
  return;
}
```

---

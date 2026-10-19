# 0012_batch_0008 — détails (3/3)

## FUN_0042ee48 — 0x42ee48

- Classification : internal
- Corps : `0x42ee48–0x42ef16`
- État : pseudocode obtenu
- Evidence : `ev_b1eef3a6b252c5fa1733dbfcf82a66aff0128de7f09b851e71e222f58035aff9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042ee48(undefined4 *param_1)

{
  int iVar1;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 0;
  local_18 = 0;
  if (0 < DAT_005c36b8) {
    local_18 = DAT_005c3618;
    local_14 = DAT_005c361c;
    local_10 = DAT_005c3620;
    local_c = DAT_005c3624;
    for (local_1c = 0; local_1c < DAT_005c36b8; local_1c = local_1c + 1) {
      iVar1 = local_1c + 1;
      (&DAT_005c3618)[local_1c * 4] = (&DAT_005c3618)[iVar1 * 4];
      (&DAT_005c361c)[local_1c * 4] = (&DAT_005c361c)[iVar1 * 4];
      (&DAT_005c3620)[local_1c * 4] = (&DAT_005c3620)[iVar1 * 4];
      (&DAT_005c3624)[local_1c * 4] = (&DAT_005c3624)[iVar1 * 4];
    }
    DAT_005c36b8 = DAT_005c36b8 + -1;
    local_8 = 1;
  }
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = local_18;
    param_1[1] = local_14;
    param_1[2] = local_10;
    param_1[3] = local_c;
  }
  return local_8;
}
```

---

---

## FUN_0042ef17 — 0x42ef17

- Classification : internal
- Corps : `0x42ef17–0x42f018`
- État : pseudocode obtenu
- Evidence : `ev_84932651de367bf515bdf073e6673f51992e52b524f7c4d9a416ce8b8a101e83`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4019c9` — `thunk_FUN_0042eba0`
- `0x402289` — `thunk_FUN_0041be0f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042ef17(void)

{
  int local_2c;
  undefined1 local_28 [4];
  uint local_24;
  undefined4 local_20;
  int local_1c;
  int local_c;
  undefined4 local_8;
  
  local_8 = 1;
  local_c = 1;
  DAT_005c36c4 = 0;
LAB_0042ef34:
  if (local_c == 0) {
    return local_8;
  }
  local_c = thunk_FUN_0041be0f(local_28);
  if (local_24 == 0x12) {
    local_8 = 0;
  }
  if (0x202 < local_24) goto LAB_0042ef93;
  if (local_24 < 0x200) {
    if (0xff < local_24) {
      if (local_24 < 0x102) goto LAB_0042efa7;
      if (local_24 == 0x102) {
        for (local_2c = 0; local_2c < DAT_005c36b8; local_2c = local_2c + 1) {
          if (((&DAT_005c3618)[local_2c * 4] == 6) &&
             (local_1c == *(int *)(&DAT_005c3698 + local_2c * 4))) {
            *(undefined2 *)(&DAT_005c3624 + local_2c * 4) = (undefined2)local_20;
            break;
          }
        }
      }
    }
    goto LAB_0042ef34;
  }
LAB_0042efa7:
  thunk_FUN_0042eba0(local_24,local_20,local_1c);
  goto LAB_0042ef34;
LAB_0042ef93:
  if ((local_24 < 0x204) || (0x205 < local_24)) goto LAB_0042ef34;
  goto LAB_0042efa7;
}
```

---

---

## FUN_0042f019 — 0x42f019

- Classification : internal
- Corps : `0x42f019–0x42f023`
- État : pseudocode obtenu
- Evidence : `ev_69754a18f0c9c1bf835c7c068b943169ebe12c4d44060fd7d10cf7c15a6462d8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined2 FUN_0042f019(void)

{
  return DAT_005c36c4;
}
```

---

# 0011_batch_0007 — détails (6/6)

## FUN_0042d647 — 0x42d647

- Classification : internal
- Corps : `0x42d647–0x42d696`
- État : pseudocode obtenu
- Evidence : `ev_30a9ef35993461c86c2545e3de86abb7351dddbc9f48ac2517668c665bbb3c96`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042d647(void)

{
  if (((DAT_005c30cc != 0) && (DAT_005c30d0 != 0)) && (DAT_005c1888 != 0)) {
    (**(code **)(*DAT_005c30f0 + 0x80))(DAT_005c30f0,DAT_005c1888);
    DAT_005c1888 = 0;
  }
  return;
}
```

---

## FUN_0042d697 — 0x42d697

- Classification : internal
- Corps : `0x42d697–0x42d742`
- État : pseudocode obtenu
- Evidence : `ev_411bdc1fba800f3f7f129fac4547813adb3a2931b796a36d9d00fb4b0c6a5afe`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042d697(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  if ((DAT_005c30cc != 0) && (DAT_005c30d0 != 0)) {
    local_14 = param_1;
    local_10 = param_2;
    local_c = param_3 + 1;
    local_8 = param_4 + 1;
    if (DAT_0049e138 == 1) {
      (**(code **)(*DAT_005c30ec + 0x14))(DAT_005c30ec,&local_14,DAT_005c30f0,&local_14,0x1000000,0)
      ;
    }
    else if (DAT_0049e138 == 0) {
      (**(code **)(*DAT_005c30e8 + 0x14))(DAT_005c30e8,&local_14,DAT_005c30f0,&local_14,0x1000000,0)
      ;
    }
  }
  return;
}
```

---

## FUN_0042d743 — 0x42d743

- Classification : internal
- Corps : `0x42d743–0x42d806`
- État : pseudocode obtenu
- Evidence : `ev_4a474d2a387e359173ce90b076f7ca0f12468dba0e979f2e372cf817e027a57e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042d743(int param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  int local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  
  if ((DAT_005c30cc != 0) && (DAT_005c30d0 != 0)) {
    local_28 = param_1;
    local_24 = param_2;
    param_3 = param_3 + 1;
    local_1c = param_4 + 1;
    local_18 = param_1;
    local_14 = param_2;
    if (param_5 < 1) {
      local_28 = param_1 - param_5;
      local_10 = param_3 + param_5;
      local_20 = param_3;
    }
    else {
      local_18 = param_1 + param_5;
      local_20 = param_3 - param_5;
      local_10 = param_3;
    }
    if ((local_28 < local_20) && (local_18 < local_10)) {
      local_c = local_1c;
      (**(code **)(*DAT_005c30f0 + 0x14))(DAT_005c30f0,&local_18,DAT_005c30f0,&local_28,0x1000000,0)
      ;
    }
  }
  return;
}
```

---

## FUN_0042d807 — 0x42d807

- Classification : internal
- Corps : `0x42d807–0x42d810`
- État : pseudocode obtenu
- Evidence : `ev_42eaec8cd310340d0f4c28392b28ffd5dd8e6ab7ec454575d2da673d7469206a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042d807(void)

{
  return DAT_005c30d0;
}
```

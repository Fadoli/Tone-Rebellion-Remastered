# 0011_batch_0007 — détails (3/3)

## FUN_0042bdb0 — 0x42bdb0

- Classification : internal
- Corps : `0x42bdb0–0x42bddd`
- État : pseudocode obtenu
- Evidence : `ev_0b0d52536aaec2a985ec769d3cf47c7a17ebea241a7e0a82af2998035c85ebce`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402450` — `thunk_FUN_0042a4a5`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042bdb0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0042a4a5();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_0042bdf0 — 0x42bdf0

- Classification : internal
- Corps : `0x42bdf0–0x42be1d`
- État : pseudocode obtenu
- Evidence : `ev_2b135d3b77dac33e14d3a19b2054da8d9fcb32e3271d6fccba690eec31fddeaa`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402374` — `thunk_FUN_0042aa63`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042bdf0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0042aa63();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_0042be30 — 0x42be30

- Classification : internal
- Corps : `0x42be30–0x42be5d`
- État : pseudocode obtenu
- Evidence : `ev_d3893502f52b58a275a09178cfb7e380dc52c140ac453ba310e0eb147355e364`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021a8` — `thunk_FUN_0042ac4d`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042be30(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0042ac4d();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_0042be70 — 0x42be70

- Classification : internal
- Corps : `0x42be70–0x42be79`
- État : pseudocode obtenu
- Evidence : `ev_61f14dda8718254bd87af3cc2d80cb37380b9795746a3f82a367f5f98772cac8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x42be7a` — `FUN_0042be7a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042be70(void)

{
  FUN_0042be7a();
  return;
}
```

---

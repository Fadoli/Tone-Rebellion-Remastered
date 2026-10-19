# 0016_batch_0012 — détails (3/3)

## FUN_0045c2c6 — 0x45c2c6

- Classification : internal
- Corps : `0x45c2c6–0x45c2d0`
- État : pseudocode obtenu
- Evidence : `ev_f4d0afcc43d8b4b2141ce634e7d513a6b615243d6821fdf0c80dc567b92332a2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045c2c6(void)

{
  return;
}
```

---

---

## FUN_0045c2d1 — 0x45c2d1

- Classification : internal
- Corps : `0x45c2d1–0x45c324`
- État : pseudocode obtenu
- Evidence : `ev_533c5b6707e514ad4be641dfbdc950a75ba7774eddea733cae6b8006e2845412`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045c2d1(void)

{
  undefined2 *in_ECX;
  short local_8;
  
  *in_ECX = 0xffff;
  in_ECX[1] = 0xffff;
  for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
    in_ECX[local_8 + 2] = 0xffff;
  }
  in_ECX[0x12] = 0;
  return;
}
```

---

---

## FUN_0045c325 — 0x45c325

- Classification : internal
- Corps : `0x45c325–0x45c3ba`
- État : pseudocode obtenu
- Evidence : `ev_266125dff766e2414135d1bcf74f13d513d1765005373355b2190e74ae733d16`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a42e3` — "\ntribe>=int(FT_Protector) && tribe<=int(FT_Lifegiver)"
- `0x4a431c` — "C:\\float\\src\\staffbld.cpp"

### Pseudocode Ghidra

```c
int FUN_0045c325(void)

{
  int iVar1;
  short *in_ECX;
  
  if ((*in_ECX == -1) || (in_ECX[1] == -1)) {
    iVar1 = 0xffff;
  }
  else {
    iVar1 = *(int *)(&DAT_005ec654 + in_ECX[1] * 0x60 + *in_ECX * 0x29e8);
    if ((iVar1 < 0) || (3 < iVar1)) {
      thunk_FUN_00414b64(s_C__float_src_staffbld_cpp_004a431c,0x9b,
                         s_tribe>_int_FT_Protector_____trib_004a42e3 + 1);
    }
    iVar1 = ((int)in_ECX - (int)(&DAT_006192b0 + iVar1 * 0x14a0)) / 100;
  }
  return iVar1;
}
```

---

---

## FUN_0045c3bb — 0x45c3bb

- Classification : internal
- Corps : `0x45c3bb–0x45c3fd`
- État : pseudocode obtenu
- Evidence : `ev_0f1bf5caca4a6c5c244c4a2b8bee6e591fc8367f9b451a0694329a19e3378011`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_0045c3bb(void)

{
  undefined *puVar1;
  short *in_ECX;
  
  if ((*in_ECX == -1) || (in_ECX[1] == -1)) {
    puVar1 = (undefined *)0x0;
  }
  else {
    puVar1 = &DAT_005ec640 + in_ECX[1] * 0x60 + *in_ECX * 0x29e8;
  }
  return puVar1;
}
```

---

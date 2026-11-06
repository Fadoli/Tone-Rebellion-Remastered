# 0018_batch_0014 — détails (3/3)

## FUN_0046cbe0 — 0x46cbe0

- Classification : internal
- Corps : `0x46cbe0–0x46cc03`
- État : pseudocode obtenu
- Evidence : `ev_cf8066fbcce5f9c529a11371c145d5a641880a49ee0eab718b7332638457c736`
- Note d'inscription : stocke le callback à l'index fourni, dans la table de dispatch à pas `0x130`; l'inscription seule ne sélectionne pas ce slot comme actif. Evidence `ev_adba0f04ecf4c24995e49e0f36cf9efcfa8397a704bdfbe072742e0e43adab60`.
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046cbe0(short param_1,undefined4 param_2)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x206c + param_1 * 0x130) = param_2;
  return;
}
```

---

---

## FUN_0046cc04 — 0x46cc04

- Classification : internal
- Corps : `0x46cc04–0x46cce6`
- État : pseudocode obtenu
- Evidence : `ev_b75f3d0fac17447ea5378b444ccf473c5d539923ae95b6fa6c3a1424d6df7897`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a5900` — "hwnd < MAX_WINDOWS"
- `0x4a5914` — "C:\\float\\src\\winman.cpp"

### Pseudocode Ghidra

```c
void FUN_0046cc04(int param_1,int param_2)

{
  undefined4 *puVar1;
  int in_ECX;
  
  if (0x299 < param_1) {
    thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5914,0x741,s_hwnd_<_MAX_WINDOWS_004a5900);
  }
  if ((param_1 != 0) &&
     ((*(int *)(in_ECX + param_1 * 0xc) = *(int *)(in_ECX + param_1 * 0xc) + -1,
      *(int *)(in_ECX + param_1 * 0xc) == 0 || (param_2 != 0)))) {
    puVar1 = *(undefined4 **)(in_ECX + 4 + param_1 * 0xc);
    if (puVar1 != (undefined4 *)0x0) {
      (**(code **)*puVar1)(1);
    }
    *(undefined4 *)(in_ECX + 4 + param_1 * 0xc) = 0;
    *(undefined4 *)(in_ECX + param_1 * 0xc) = 0;
    *(short *)(in_ECX + 0x1f38) = *(short *)(in_ECX + 0x1f38) + -1;
  }
  return;
}
```

---

---

## FUN_0046cce7 — 0x46cce7

- Classification : internal
- Corps : `0x46cce7–0x46cd21`
- État : pseudocode obtenu
- Evidence : `ev_2f2a49af6b439dc8f4a3c415927137b41ef490600e0ae7a7f133a681eed1e2de`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4734a0` — `FUN_004734a0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046cce7(int param_1)

{
  int in_ECX;
  
  if (param_1 != 0) {
    FUN_004734a0(in_ECX + 0x5fb0,param_1,0x300);
  }
  *(undefined4 *)(in_ECX + 0x62b0) = 1;
  return;
}
```

---

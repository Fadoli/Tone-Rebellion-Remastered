# 0015_batch_0011 — détails (6/6)

## FUN_00453a5f — 0x453a5f

- Classification : internal
- Corps : `0x453a5f–0x453add`
- État : pseudocode obtenu
- Evidence : `ev_ed13893701a30da1a7dcca0f3b1e7ad88481ba168e841e628a874e0e0de09d11`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40102d` — `thunk_FUN_0045e6d3`
- `0x401226` — `thunk_FUN_00460460`
- `0x401992` — `thunk_FUN_004539e9`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00453a5f(void)

{
  uint uVar1;
  int in_ECX;
  
  if (((*(int *)(in_ECX + 4) != 2) && (*(int *)(in_ECX + 4) != 3)) &&
     (uVar1 = *(uint *)(in_ECX + 0x1c), thunk_FUN_004539e9(),
     (uVar1 & 1) != (*(uint *)(in_ECX + 0x1c) & 1))) {
    if (*(int *)(in_ECX + 0x14) == 4) {
      thunk_FUN_00460460((int)*(short *)(in_ECX + 8));
    }
    else {
      thunk_FUN_0045e6d3((int)*(short *)(in_ECX + 8));
    }
  }
  return;
}
```

---

## FUN_00453ade — 0x453ade

- Classification : internal
- Corps : `0x453ade–0x453b08`
- État : pseudocode obtenu
- Evidence : `ev_d1a0325c76de710ae581e686525313003033370c8a726008d3b895ce3a3456ca`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401924` — `thunk_FUN_00453a5f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00453ade(void)

{
  int in_ECX;
  
  *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 0x100;
  *(undefined2 *)(in_ECX + 0x44) = 0;
  thunk_FUN_00453a5f();
  return;
}
```

---

## FUN_00453b09 — 0x453b09

- Classification : internal
- Corps : `0x453b09–0x453b37`
- État : pseudocode obtenu
- Evidence : `ev_01c59648447d5a1db1eff5bd873a91797a94aa9b298b6472974175767f0fe9b7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00453b09(short param_1)

{
  int in_ECX;
  
  *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 0x200;
  *(short *)(in_ECX + 0x38) = (param_1 + 1) * 1000;
  return;
}
```

---

## FUN_00453b38 — 0x453b38

- Classification : internal
- Corps : `0x453b38–0x453b75`
- État : pseudocode obtenu
- Evidence : `ev_56947bad90e7e598e4740cfaaeddb15909bb47b1c8c3e67415a9dc93b17e8121`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00453b38(short param_1)

{
  int in_ECX;
  
  if (-1 < *(short *)(in_ECX + 0x18)) {
    *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 0x8000;
    *(short *)(in_ECX + 0x38) = param_1 * 500 + 1000;
  }
  return;
}
```

---

## FUN_00453b76 — 0x453b76

- Classification : internal
- Corps : `0x453b76–0x453bb5`
- État : pseudocode obtenu
- Evidence : `ev_07fb88cdf490d999cad92c2ae84a626fc14f2ff7ffa18a04f6e53b95b633f1ae`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00453b76(short param_1)

{
  int in_ECX;
  
  if (-1 < *(short *)(in_ECX + 0x18)) {
    *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 0x10000;
    *(short *)(in_ECX + 0x38) = param_1 * 500 + 1000;
  }
  return;
}
```

---

## FUN_00453bb6 — 0x453bb6

- Classification : internal
- Corps : `0x453bb6–0x453bf5`
- État : pseudocode obtenu
- Evidence : `ev_2409dbf8a8b6e776c7f2fc894fc550452390b67ea01028a65afc5e9fdd317b57`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00453bb6(short param_1)

{
  int in_ECX;
  
  if (-1 < *(short *)(in_ECX + 0x18)) {
    *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 0x20000;
    *(short *)(in_ECX + 0x38) = param_1 * 500 + 1000;
  }
  return;
}
```

---

## FUN_00453bf6 — 0x453bf6

- Classification : internal
- Corps : `0x453bf6–0x453cb9`
- État : pseudocode obtenu
- Evidence : `ev_ae39f7605eeb24b5fa6accafa3740bce5c8df5b07c06ec25b3411ce2df278b84`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401096` — `thunk_FUN_0045cbaa`
- `0x401924` — `thunk_FUN_00453a5f`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x4021ad` — `thunk_FUN_004641de`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00453bf6(int param_1)

{
  int iVar1;
  int in_ECX;
  uint local_c;
  
  if (param_1 == 0) {
    *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) & 0xfffffbff;
  }
  else if (((-1 < *(int *)(in_ECX + 0x14)) && (*(int *)(in_ECX + 0x14) < 4)) &&
          (iVar1 = thunk_FUN_004641de(*(undefined4 *)(in_ECX + 0x14),*(undefined4 *)(in_ECX + 0x10))
          , (int)*(short *)(iVar1 + 0xc) <=
            *(int *)(&DAT_006191f8 + *(int *)(in_ECX + 0x14) * 0x14a0))) {
    *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 0x400;
  }
  if (*(short *)(in_ECX + 0x18) != -1) {
    local_c = (uint)((*(uint *)(in_ECX + 0x1c) & 0x400) != 0);
    thunk_FUN_00450385(local_c);
    thunk_FUN_0045cbaa(local_c);
  }
  thunk_FUN_00453a5f();
  return;
}
```

---

## FUN_00453cba — 0x453cba

- Classification : internal
- Corps : `0x453cba–0x453cf4`
- État : pseudocode obtenu
- Evidence : `ev_a9d49dc588fa3426e801744813b36f0ed68489be0132e42bacf232403a108c58`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00453cba(int param_1)

{
  int in_ECX;
  
  if (*(short *)(in_ECX + 0x4a) < param_1) {
    *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 0x20;
    *(undefined2 *)(in_ECX + 0x48) = 0;
  }
  *(undefined2 *)(in_ECX + 0x4a) = (undefined2)param_1;
  return;
}
```

---

## FUN_00453cf5 — 0x453cf5

- Classification : internal
- Corps : `0x453cf5–0x453d35`
- État : pseudocode obtenu
- Evidence : `ev_f4403f998b0931ebb9a2bcbc99e137cda1466f6c23cee452e30e8c44793840d0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00453cf5(int param_1)

{
  int in_ECX;
  undefined4 local_8;
  
  local_8 = 0;
  if ((*(int *)(in_ECX + 0x14) == param_1) ||
     ((*(uint *)(in_ECX + 0x1c) & 0x800 << ((byte)param_1 & 0x1f)) != 0)) {
    local_8 = 1;
  }
  return local_8;
}
```

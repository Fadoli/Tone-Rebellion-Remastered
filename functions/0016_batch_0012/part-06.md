# 0016_batch_0012 — détails (6/6)

## FUN_0045d867 — 0x45d867

- Classification : internal
- Corps : `0x45d867–0x45d8b1`
- État : pseudocode obtenu
- Evidence : `ev_e379eeca2a8c0f32161b5132bc67bc6007dda9876820e623c8fc4a4dcbc810d3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045d867(int param_1,short param_2)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x28) = *(undefined2 *)(&DAT_006137c6 + param_2 * 0x4c);
  *(uint *)(in_ECX + 0x2c) = (-(uint)(param_1 != 0x12) & 0xfffffffe) + 8;
  *(short *)(in_ECX + 0x30) = param_2;
  *(undefined2 *)(in_ECX + 0x32) = 0;
  return;
}
```

---

## FUN_0045d8b2 — 0x45d8b2

- Classification : internal
- Corps : `0x45d8b2–0x45d8f3`
- État : pseudocode obtenu
- Evidence : `ev_b0d6dc330f48ea769d27f91e3813699594fed3422d909182391884696797306c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045d8b2(int param_1,undefined2 param_2,undefined2 param_3)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x28) = param_2;
  *(uint *)(in_ECX + 0x2c) = (-(uint)(param_1 != 0x13) & 0xfffffffe) + 9;
  *(undefined2 *)(in_ECX + 0x30) = param_3;
  *(undefined2 *)(in_ECX + 0x32) = 0;
  return;
}
```

---

## FUN_0045d8f4 — 0x45d8f4

- Classification : internal
- Corps : `0x45d8f4–0x45d9c0`
- État : pseudocode obtenu
- Evidence : `ev_44206137f644023c3f4fa7f6db5c106e4cbe0829f9805f291cc4d8208580fec1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018cf` — `thunk_FUN_0041ff2e`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0045d8f4(short param_1)

{
  short sVar1;
  int iVar2;
  int *piVar3;
  int in_ECX;
  int local_c;
  
  local_c = 0;
  do {
    if (7 < local_c) {
      return -1;
    }
    if (*(short *)(in_ECX + 4 + local_c * 2) != -1) {
      iVar2 = (int)*(short *)(in_ECX + 4 + local_c * 2);
      piVar3 = &DAT_006137b8 + iVar2 * 0x13;
      if (piVar3 != (int *)0x0) {
        if ((*piVar3 == 1) && (param_1 == 0xf)) {
          return local_c;
        }
        if ((*piVar3 == 2) && (param_1 == 0x11)) {
          return local_c;
        }
        sVar1 = thunk_FUN_0041ff2e();
        if ((*(short *)(&DAT_006188e0 + param_1 * 0x2c) <= sVar1) &&
           (*(int *)(&DAT_006137f4 + iVar2 * 0x4c) != 0x13)) {
          return local_c;
        }
      }
    }
    local_c = local_c + 1;
  } while( true );
}
```

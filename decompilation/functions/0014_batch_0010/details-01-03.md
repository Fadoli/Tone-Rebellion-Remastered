# 0014_batch_0010 — détails (3/3)

## FUN_00442efe — 0x442efe

- Classification : internal
- Corps : `0x442efe–0x442f12`
- État : pseudocode obtenu
- Evidence : `ev_483eceea84aae4de52d81b134dcedf5f3974b86937a787a685cec844760bc0af`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00442efe(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x70) = 0;
  return;
}
```

---

---

## FUN_00442f13 — 0x442f13

- Classification : internal
- Corps : `0x442f13–0x443077`
- État : pseudocode obtenu
- Evidence : `ev_2991011d076885033163ec70a8091037340c8fab36b90e80d0a705c9bceb9753`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401569` — `thunk_FUN_0046c558`
- `0x401bf4` — `thunk_FUN_0042970c`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402158` — `thunk_FUN_004667eb`

### Chaînes référencées

- `0x4a0bc8` — "IWLocInfo"
- `0x4a0bd4` — "mpLocInfo"
- `0x4a0be0` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0bf8` — "mpLocInfo"
- `0x4a0c04` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0c20` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_00442f13(short param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  
  if (param_1 == 1) {
    if (*(int *)(in_ECX + 0x70) == 0) {
      uVar2 = thunk_FUN_0046c558(s_IWLocInfo_004a0bc8,3,0);
      *(undefined4 *)(in_ECX + 0x70) = uVar2;
      if (*(int *)(in_ECX + 0x70) == 0) {
        thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0be0,0x5ef,s_mpLocInfo_004a0bd4);
      }
    }
  }
  else if ((5 < param_1) && (param_1 < 8)) {
    iVar1 = thunk_FUN_00429f3a();
    if (iVar1 != 0) {
      if (*(int *)(in_ECX + 0x70) == 0) {
        thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0c04,0x5fc,s_mpLocInfo_004a0bf8);
      }
      iVar1 = *(int *)(*(int *)(in_ECX + 0x70) + 0x70);
      if (iVar1 == 0) {
        thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0c20,0x5fe,&DAT_004a0c1c);
      }
      if (((4 < *(int *)(iVar1 + 0x24)) && (*(int *)(iVar1 + 0x24) < 0x22)) &&
         (iVar1 = thunk_FUN_004667eb(iVar1,*(undefined4 *)(iVar1 + 0x24),DAT_0049f538), iVar1 == 0))
      {
        thunk_FUN_0042970c(*(undefined2 *)(in_ECX + 0x60),*(undefined4 *)(in_ECX + 100),
                           *(undefined4 *)(in_ECX + 0x68));
      }
      return 1;
    }
    return 0;
  }
  uVar2 = thunk_FUN_004293c6(param_1,param_2,param_3);
  return uVar2;
}
```

---

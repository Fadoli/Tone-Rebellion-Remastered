# 0015_batch_0011 — détails (3/3)

## FUN_0044e613 — 0x44e613

- Classification : internal
- Corps : `0x44e613–0x44e703`
- État : pseudocode obtenu
- Evidence : `ev_717c6e0943cbfbac58e32e24e69adbb7c56f395b1e91e4215aac199ae4c6ba80`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401712` — `thunk_FUN_004289a7`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x472c6c` — `__ftol`
- `0x476ce4` — `FUN_00476ce4`

### Chaînes référencées

- `0x4a2580` — "ABS(lasty-240)<=NEWGAMERADIUS"
- `0x4a25a0` — "C:\\float\\src\\newgame.cpp"

### Pseudocode Ghidra

```c
void FUN_0044e613(int param_1,int param_2,int *param_3,int *param_4,int *param_5)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (param_2 + -0xf0 < 0) {
    iVar3 = -(param_2 + -0xf0);
  }
  else {
    iVar3 = param_2 + -0xf0;
  }
  if (iVar3 < 0xc9) {
    uVar4 = 0;
  }
  else {
    uVar4 = thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a25a0,0x82,
                               s_ABS_lasty_240_<_NEWGAMERADIUS_004a2580);
  }
  uVar1 = thunk_FUN_0042de03();
  iVar2 = thunk_FUN_004289a7();
  *param_4 = param_2 + 3 + iVar2;
  iVar2 = 40000 - (*param_4 + -0xf0) * (*param_4 + -0xf0);
  FUN_00476ce4((double)iVar2,iVar2,uVar4,iVar3,uVar1);
  iVar3 = __ftol();
  if (param_1 < 0x140) {
    *param_3 = 0x14;
    *param_5 = 0x13b - iVar3;
  }
  else {
    *param_3 = iVar3 + 0x145;
    *param_5 = 0x26c;
  }
  return;
}
```

---

---

## FUN_0044e704 — 0x44e704

- Classification : internal
- Corps : `0x44e704–0x44e757`
- État : pseudocode obtenu
- Evidence : `ev_fdda9e038b356415d9f32f827de41d2872a46b69b851484080e0ae1be2cea6cd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013d9` — `thunk_FUN_0044e774`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0044e704(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491a69;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004946e0;
  thunk_FUN_0044e774();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0044e758 — 0x44e758

- Classification : internal
- Corps : `0x44e758–0x44e773`
- État : pseudocode obtenu
- Evidence : `ev_9d8eb59a881ce141acfcc4417ac485c857ffaf263f33d811e8cb3f1d8a8cc8fc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044e758(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004946e0;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_0044e774 — 0x44e774

- Classification : internal
- Corps : `0x44e774–0x44e77e`
- État : pseudocode obtenu
- Evidence : `ev_3faadf50f45511fa1f7ede8c6cf611befa04014cc5a5315d4c17febdf3c2c87b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044e774(void)

{
  return;
}
```

---

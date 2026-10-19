# 0011_batch_0007 — détails (1/3)

## FUN_0042383d — 0x42383d

- Classification : internal
- Corps : `0x42383d–0x4239e8`
- État : pseudocode obtenu
- Evidence : `ev_d8079c55e74cb30411c811377e1cc01c47f9e97fb7085c47510ae2fd163f0bb9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401127` — `thunk_FUN_0041660b`
- `0x40173a` — `thunk_FUN_004672a6`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4022ed` — `thunk_FUN_0042361d`

### Chaînes référencées

- `0x49d31c` — "mActionObj >= 0 && mActionObj < SPELL_NumSpells"
- `0x49d34c` — "C:\\float\\src\\floater.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0042383d(void)

{
  bool bVar1;
  int iVar2;
  int in_ECX;
  undefined4 uVar3;
  
  if ((*(short *)(in_ECX + 0x30) < 0) || (0x16 < *(short *)(in_ECX + 0x30))) {
    uVar3 = thunk_FUN_00414b64(s_C__float_src_floater_cpp_0049d34c,0xcb4,
                               s_mActionObj_>__0____mActionObj_<_S_0049d31c);
  }
  else {
    uVar3 = 0;
  }
  if ((*(uint *)(in_ECX + 0x1c) & 0x200) == 0) {
    if ((*(int *)(&DAT_0049d230 + *(short *)(in_ECX + 0x30) * 4) == -1) ||
       (iVar2 = thunk_FUN_004672a6((int)*(short *)(in_ECX + 0x10),(int)*(short *)(in_ECX + 0x12),
                                   (int)*(short *)(in_ECX + 0x28),(int)*(short *)(in_ECX + 0x2a),
                                   uVar3),
       iVar2 <= *(int *)(&DAT_0049d230 + *(short *)(in_ECX + 0x30) * 4))) {
      *(undefined2 *)(in_ECX + 0x28) = *(undefined2 *)(in_ECX + 0x10);
      *(undefined2 *)(in_ECX + 0x2a) = *(undefined2 *)(in_ECX + 0x12);
      bVar1 = false;
      if ((*(short *)(in_ECX + 0x30) < 0) || (0x16 < *(short *)(in_ECX + 0x30))) {
        *(short *)(in_ECX + 0x34) = *(short *)(in_ECX + 0x34) + 1;
        if (*(short *)(in_ECX + 0x34) == 0x28) {
          bVar1 = true;
        }
      }
      else {
        *(short *)(in_ECX + 0x34) = *(short *)(in_ECX + 0x34) + 1;
        if (*(short *)(in_ECX + 0x34) == 10) {
          thunk_FUN_0041660b(in_ECX);
        }
        else if (399 < *(short *)(in_ECX + 0x34)) {
          bVar1 = true;
        }
      }
      if (bVar1) {
        *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 0x200;
      }
      uVar3 = 0;
    }
    else {
      if (((&DAT_0049d218)[*(short *)(in_ECX + 0x30)] & 2) != 0) {
        thunk_FUN_0042361d();
      }
      uVar3 = 0;
    }
  }
  else {
    *(short *)(in_ECX + 8) = *(short *)(in_ECX + 8) + 5;
    uVar3 = 1;
  }
  return uVar3;
}
```

---

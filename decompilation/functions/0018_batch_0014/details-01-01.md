# 0018_batch_0014 — détails (1/3)

## FUN_004680a3 — 0x4680a3

- Classification : internal
- Corps : `0x4680a3–0x4680fb`
- État : pseudocode obtenu
- Evidence : `ev_8da4c45b3dca6f556398f29e6b4a5da514738074179dd7117e600bf57efa899b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004680a3(void)

{
  int in_ECX;
  ushort *local_10;
  int local_8;
  
  local_8 = 0;
  for (local_10 = (ushort *)(in_ECX + 0x2c1a4); local_10 < (ushort *)(in_ECX + 0x2c6a4);
      local_10 = local_10 + 1) {
    local_8 = local_8 + (uint)*local_10;
  }
  return local_8;
}
```

---

---

## FUN_004680fc — 0x4680fc

- Classification : internal
- Corps : `0x4680fc–0x46814f`
- État : pseudocode obtenu
- Evidence : `ev_c6c5e10a022ed1fbd74d8c96fc011bb5ed8abd3f41a05782d9821552de2aa011`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004680fc(void)

{
  ushort *in_ECX;
  ushort *local_10;
  int local_8;
  
  local_8 = 0;
  for (local_10 = in_ECX; local_10 < in_ECX + 0x13a4c; local_10 = local_10 + 1) {
    local_8 = local_8 + (uint)*local_10;
  }
  return local_8;
}
```

---

---

## FUN_00469bf0 — 0x469bf0

- Classification : internal
- Corps : `0x469bf0–0x469bfe`
- État : pseudocode obtenu
- Evidence : `ev_183c5bd4301d509cabfa3ba3e0077df9930a4f5a78e57910a7516d70b3a2dd26`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x469bff` — `FUN_00469bff`
- `0x469c0e` — `FUN_00469c0e`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00469bf0(void)

{
  FUN_00469bff();
  FUN_00469c0e();
  return;
}
```

---

---

## FUN_00469bff — 0x469bff

- Classification : internal
- Corps : `0x469bff–0x469c0d`
- État : pseudocode obtenu
- Evidence : `ev_b57acbde8452cf42e1b981e908052fee0af21ead88dc6d7947549f0fc292d659`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401dd9` — `thunk_FUN_00469c2f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00469bff(void)

{
  thunk_FUN_00469c2f();
  return;
}
```

---

---

## FUN_00469c0e — 0x469c0e

- Classification : internal
- Corps : `0x469c0e–0x469c1f`
- État : pseudocode obtenu
- Evidence : `ev_aac0eee3d47cfdf7733a9c7009d20b5e05ee94b2cfbe6d1ab399d42ce4cdabed`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476c60` — `FUN_00476c60`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00469c0e(void)

{
  FUN_00476c60(FUN_00469c20);
  return;
}
```

---

---

## FUN_00469c20 — 0x469c20

- Classification : internal
- Corps : `0x469c20–0x469c2e`
- État : pseudocode obtenu
- Evidence : `ev_7ced01ad7aec263ea60514c05c90ff3729a4c7097492dbfd1f960459d13b6ec9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f23` — `thunk_FUN_00469c80`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00469c20(void)

{
  thunk_FUN_00469c80();
  return;
}
```

---

---

## FUN_00469c2f — 0x469c2f

- Classification : internal
- Corps : `0x469c2f–0x469c7f`
- État : pseudocode obtenu
- Evidence : `ev_e3f219f89f47c3acfdcd0eea8d16136e3b2bf0ac03bafaf07de0ca0a63affe79`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4015fa` — `thunk_FUN_00469cce`
- `0x401f55` — `thunk_FUN_0040e160`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00469c2f(void)

{
  undefined4 in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491d2f;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0040e160();
  local_8 = 0;
  thunk_FUN_00469cce();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_00469c80 — 0x469c80

- Classification : internal
- Corps : `0x469c80–0x469ccd`
- État : pseudocode obtenu
- Evidence : `ev_d64309c6ffe90ae496c1d56b7da718a8b671d6e77a3295b24a1e48e220466912`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40158c` — `thunk_FUN_0040e1ad`
- `0x402360` — `thunk_FUN_00469dfc`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00469c80(void)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00491d48;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_8 = 0;
  thunk_FUN_00469dfc();
  local_8 = 0xffffffff;
  thunk_FUN_0040e1ad();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

---

## FUN_00469cce — 0x469cce

- Classification : internal
- Corps : `0x469cce–0x469dfb`
- État : pseudocode obtenu
- Evidence : `ev_d58400ae0c35c006e36627c6ba6ce0c2542e52490b31798b57310ce1ee7e2602`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00469cce(void)

{
  void *in_ECX;
  
  *(undefined2 *)((int)in_ECX + 0x29f0) = 0;
  *(undefined2 *)((int)in_ECX + 0x1f38) = 0;
  *(undefined2 *)((int)in_ECX + 0x29f2) = 0xffff;
  *(undefined2 *)((int)in_ECX + 0x29f4) = 0xffff;
  *(undefined2 *)((int)in_ECX + 0x2cf8) = 0;
  *(undefined2 *)((int)in_ECX + 0x2e7c) = 0;
  *(undefined2 *)((int)in_ECX + 0x2fc0) = 0;
  *(undefined4 *)((int)in_ECX + 0x1f3c) = 0xffffffff;
  _memset((void *)((int)in_ECX + 8000),0,0xab0);
  _memset(in_ECX,0,0x1f38);
  _memset((void *)((int)in_ECX + 0x2cfc),0,0x180);
  _memset((void *)((int)in_ECX + 0x2e80),0,0x140);
  *(undefined4 *)((int)in_ECX + 0x62b8) = 0;
  *(undefined4 *)((int)in_ECX + 0x62b0) = 0;
  *(undefined4 *)((int)in_ECX + 0x62b4) = 0;
  *(undefined4 *)((int)in_ECX + 0x62c0) = 0;
  *(undefined1 *)((int)in_ECX + 0x62c4) = 0;
  *(undefined2 *)((int)in_ECX + 0x630a) = 0;
  *(undefined4 *)((int)in_ECX + 0x630c) = 0;
  *(undefined4 *)((int)in_ECX + 0x6310) = 0;
  return;
}
```

---

---

## FUN_00469dfc — 0x469dfc

- Classification : internal
- Corps : `0x469dfc–0x469f55`
- État : pseudocode obtenu
- Evidence : `ev_db75b549bdac1e43005c0697ebad801d41cf9c1e7b4d7532e6f4508c66e32e42`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40134d` — `thunk_FUN_0040e2a3`
- `0x401749` — `thunk_FUN_00414c97`
- `0x401d3e` — `thunk_FUN_00414d89`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x4a5498` — "***MOVE: %s  %d %d %d %d"
- `0x4a54b4` — "mWindows[i].window"

### Pseudocode Ghidra

```c
void FUN_00469dfc(void)

{
  undefined4 *puVar1;
  int in_ECX;
  short local_8;
  
  for (local_8 = 0; local_8 < 0x29a; local_8 = local_8 + 1) {
    if (*(int *)(in_ECX + 4 + local_8 * 0xc) != 0) {
      if ((*(uint *)(in_ECX + 8 + local_8 * 0xc) & 1) != 0) {
        thunk_FUN_00414ad0(s____MOVE___s__d__d__d__d_004a5498,
                           *(int *)(in_ECX + 4 + local_8 * 0xc) + 0x20,
                           *(undefined4 *)(*(int *)(in_ECX + 4 + local_8 * 0xc) + 0xc),
                           *(undefined4 *)(*(int *)(in_ECX + 4 + local_8 * 0xc) + 0x10),
                           *(undefined4 *)(*(int *)(in_ECX + 4 + local_8 * 0xc) + 0x14),
                           *(undefined4 *)(*(int *)(in_ECX + 4 + local_8 * 0xc) + 0x18));
      }
      thunk_FUN_00414d89(s_mWindows_i__window_004a54b4,*(undefined4 *)(in_ECX + 4 + local_8 * 0xc));
      puVar1 = *(undefined4 **)(in_ECX + 4 + local_8 * 0xc);
      if (puVar1 != (undefined4 *)0x0) {
        (**(code **)*puVar1)(1);
      }
      *(undefined4 *)(in_ECX + 4 + local_8 * 0xc) = 0;
    }
  }
  if (DAT_004c2f30 != 0) {
    thunk_FUN_00414c97(DAT_004c2f30);
    DAT_004c2f30 = 0;
  }
  thunk_FUN_0040e2a3();
  return;
}
```

---

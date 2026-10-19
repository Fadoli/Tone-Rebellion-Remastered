# 0020_batch_0016 — détails (6/6)

## FUN_0047e2f0 — 0x47e2f0

- Classification : internal
- Corps : `0x47e2f0–0x47e333`
- État : pseudocode obtenu
- Evidence : `ev_33ede9ba494efb2e810f47fc017279c05ddb0c8551059c95944654496d40d11c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x24` — `KERNEL32.DLL::HeapCreate`
- `EXTERNAL:0x25` — `KERNEL32.DLL::HeapDestroy`
- `0x47e3d0` — `FUN_0047e3d0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047e2f0(void)

{
  undefined4 uVar1;
  int iVar2;
  
  DAT_00633d04 = HeapCreate(1,0x1000,0);
  if (DAT_00633d04 == (HANDLE)0x0) {
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_0047e3d0();
    if (iVar2 == 0) {
      HeapDestroy(DAT_00633d04);
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}
```

---

## FUN_0047e340 — 0x47e340

- Classification : internal
- Corps : `0x47e340–0x47e389`
- État : pseudocode obtenu
- Evidence : `ev_5b52e3a8cf1ad71237b8f2f2ad575ca5c60365c5e92b071acc2792c783b26306`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x23` — `KERNEL32.DLL::VirtualFree`
- `EXTERNAL:0x25` — `KERNEL32.DLL::HeapDestroy`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047e340(void)

{
  undefined **local_8;
  
  local_8 = &PTR_LOOP_004a65c0;
  do {
    if (local_8[4] != (undefined *)0x0) {
      VirtualFree(local_8[4],0,0x8000);
    }
    local_8 = (undefined **)*local_8;
  } while (local_8 != &PTR_LOOP_004a65c0);
  HeapDestroy(DAT_00633d04);
  return;
}
```

---

## FUN_0047e390 — 0x47e390

- Classification : internal
- Corps : `0x47e390–0x47e399`
- État : pseudocode obtenu
- Evidence : `ev_12bf2cc92a7b2a3c3cc1d8375201d85b815eaba1155330eae12ab6d847fdf3ec`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047e390(void)

{
  return DAT_004a85e4;
}
```

---

## FUN_0047e3a0 — 0x47e3a0

- Classification : internal
- Corps : `0x47e3a0–0x47e3ca`
- État : pseudocode obtenu
- Evidence : `ev_adfa513a2d155ce96e3089d2890654d12766242f52965561773abfb06e44ac21`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_0047e3a0(int param_1)

{
  uint uVar1;
  
  uVar1 = param_1 + 0xfU & 0xfffffff0;
  if (uVar1 < 0x781) {
    DAT_004a85e4 = uVar1;
  }
  return uVar1 < 0x781;
}
```

---

## FUN_0047e3d0 — 0x47e3d0

- Classification : internal
- Corps : `0x47e3d0–0x47e5ad`
- État : pseudocode obtenu
- Evidence : `ev_9e87d1bacad855f61af779946fcc20efc2dcaa54f7ac8803722e6610dc372049`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x22` — `KERNEL32.DLL::VirtualAlloc`
- `EXTERNAL:0x23` — `KERNEL32.DLL::VirtualFree`
- `EXTERNAL:0x26` — `KERNEL32.DLL::HeapFree`
- `EXTERNAL:0x28` — `KERNEL32.DLL::HeapAlloc`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined ** FUN_0047e3d0(void)

{
  LPVOID pvVar1;
  undefined **local_10;
  int local_c;
  undefined4 *local_8;
  
  if (DAT_004a65d0 == -1) {
    local_10 = &PTR_LOOP_004a65c0;
  }
  else {
    local_10 = HeapAlloc(DAT_00633d04,0,0x2020);
    if (local_10 == (undefined **)0x0) {
      return (undefined **)0x0;
    }
  }
  local_8 = VirtualAlloc((LPVOID)0x0,0x400000,0x2000,4);
  if (local_8 != (undefined4 *)0x0) {
    pvVar1 = VirtualAlloc(local_8,0x10000,0x1000,4);
    if (pvVar1 != (LPVOID)0x0) {
      if (local_10 == &PTR_LOOP_004a65c0) {
        if (PTR_LOOP_004a65c0 == (undefined *)0x0) {
          PTR_LOOP_004a65c0 = (undefined *)&PTR_LOOP_004a65c0;
        }
        if (PTR_LOOP_004a65c4 == (undefined *)0x0) {
          PTR_LOOP_004a65c4 = (undefined *)&PTR_LOOP_004a65c0;
        }
      }
      else {
        *local_10 = (undefined *)&PTR_LOOP_004a65c0;
        local_10[1] = PTR_LOOP_004a65c4;
        PTR_LOOP_004a65c4 = (undefined *)local_10;
        *(undefined ***)local_10[1] = local_10;
      }
      local_10[4] = (undefined *)local_8;
      local_10[5] = (undefined *)(local_8 + 0x100000);
      local_10[2] = (undefined *)(local_10 + 6);
      local_10[3] = (undefined *)(local_10 + 0x26);
      for (local_c = 0; local_c < 0x400; local_c = local_c + 1) {
        if (local_c < 0x10) {
          local_10[local_c * 2 + 6] = (undefined *)0xf0;
        }
        else {
          local_10[local_c * 2 + 6] = (undefined *)0xffffffff;
        }
        local_10[local_c * 2 + 7] = (undefined *)0xf1;
      }
      _memset(local_8,0,0x10000);
      for (; local_8 < local_10[4] + 0x10000; local_8 = local_8 + 0x400) {
        *local_8 = local_8 + 2;
        local_8[1] = 0xf0;
        *(undefined1 *)(local_8 + 0x3e) = 0xff;
      }
      return local_10;
    }
    VirtualFree(local_8,0,0x8000);
  }
  if (local_10 != &PTR_LOOP_004a65c0) {
    HeapFree(DAT_00633d04,0,local_10);
  }
  return (undefined **)0x0;
}
```

---

## FUN_0047e5b0 — 0x47e5b0

- Classification : internal
- Corps : `0x47e5b0–0x47e622`
- État : pseudocode obtenu
- Evidence : `ev_106abf2f8e3c22a283f78f090a589ddc7dcfa94dfd7bbd8a24561b79893f67c4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x23` — `KERNEL32.DLL::VirtualFree`
- `EXTERNAL:0x26` — `KERNEL32.DLL::HeapFree`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047e5b0(undefined **param_1)

{
  VirtualFree(param_1[4],0,0x8000);
  if ((undefined **)PTR_LOOP_004a85e0 == param_1) {
    PTR_LOOP_004a85e0 = param_1[1];
  }
  if (param_1 == &PTR_LOOP_004a65c0) {
    DAT_004a65d0 = 0xffffffff;
  }
  else {
    *(undefined **)param_1[1] = *param_1;
    *(undefined **)(*param_1 + 4) = param_1[1];
    HeapFree(DAT_00633d04,0,param_1);
  }
  return;
}
```

---

## FUN_0047e630 — 0x47e630

- Classification : internal
- Corps : `0x47e630–0x47e786`
- État : pseudocode obtenu
- Evidence : `ev_5981e10c357def989d7edf8e2bfbac475eb9c62690f4d9fdb8ab57493db513d1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x23` — `KERNEL32.DLL::VirtualFree`
- `0x47e5b0` — `FUN_0047e5b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047e630(int param_1)

{
  undefined *puVar1;
  BOOL BVar2;
  undefined *local_18;
  int local_14;
  int local_10;
  int *local_8;
  
  local_18 = PTR_LOOP_004a65c4;
  do {
    puVar1 = local_18;
    if (*(int *)(local_18 + 0x10) != -1) {
      local_14 = 0;
      local_8 = (int *)(local_18 + 0x2010);
      for (local_10 = 0x3ff; -1 < local_10; local_10 = local_10 + -1) {
        if ((*local_8 == 0xf0) &&
           (BVar2 = VirtualFree((LPVOID)(*(int *)(local_18 + 0x10) + local_10 * 0x1000),0x1000,
                                0x4000), BVar2 != 0)) {
          *local_8 = -1;
          DAT_006325b8 = DAT_006325b8 + -1;
          if ((*(int *)(local_18 + 0xc) == 0) || (local_8 < *(int **)(local_18 + 0xc))) {
            *(int **)(local_18 + 0xc) = local_8;
          }
          local_14 = local_14 + 1;
          param_1 = param_1 + -1;
          if (param_1 == 0) break;
        }
        local_8 = local_8 + -2;
      }
      puVar1 = *(undefined **)(local_18 + 4);
      if ((local_14 != 0) && (*(int *)(local_18 + 0x18) == -1)) {
        local_10 = 1;
        for (local_8 = (int *)(local_18 + 0x20); (local_10 < 0x400 && (*local_8 == -1));
            local_8 = local_8 + 2) {
          local_10 = local_10 + 1;
        }
        if (local_10 == 0x400) {
          FUN_0047e5b0(local_18);
        }
      }
    }
    local_18 = puVar1;
    if ((local_18 == PTR_LOOP_004a65c4) || (param_1 < 1)) {
      return;
    }
  } while( true );
}
```

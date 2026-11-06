# 0011_batch_0007 — détails (3/3)

## FUN_0042d28f — 0x42d28f

- Classification : internal
- Corps : `0x42d28f–0x42d389`
- État : pseudocode obtenu
- Evidence : `ev_f0e8957f3ad59795107ad00e992806504e1a8fc8bde3544fc48db69ebc195a81`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401861` — `thunk_FUN_0042bea2`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x402338` — `thunk_FUN_0042bef7`

### Chaînes référencées

- `0x49e4b0` — " Lock failed: %x"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_0042d28f(void)

{
  undefined4 *puVar1;
  undefined4 local_78 [4];
  int local_68;
  int local_54;
  int *local_c;
  int local_8;
  
  if (DAT_005c30cc == 0) {
    puVar1 = (undefined4 *)0x0;
  }
  else if (DAT_005c30a0 == 0) {
    local_c = (int *)0x0;
    local_c = (int *)thunk_FUN_0042bea2();
    if ((DAT_0049e138 == 3) || (DAT_0049e138 == 2)) {
      DAT_005c30a0 = DAT_005c30fc;
      DAT_005c30a4 = DAT_005c3104 + -1;
    }
    else if (DAT_0049e138 == 4) {
      DAT_005c30a0 = DAT_005c3114;
      DAT_005c30a4 = 0x27f;
    }
    else {
      local_78[0] = 0x6c;
      while (local_8 = (**(code **)(*local_c + 100))(local_c,0,local_78,1,0), local_8 == -0x7789fe3e
            ) {
        thunk_FUN_0042bef7();
      }
      if (local_8 != 0) {
        thunk_FUN_00414ad0(s_Lock_failed___x_0049e4b0,local_8);
        return (undefined4 *)0x0;
      }
      DAT_005c30a0 = local_54;
      DAT_005c30a4 = local_68 + -1;
    }
    _DAT_005c30a8 = 0x1df;
    puVar1 = &DAT_005c30a0;
  }
  else {
    puVar1 = &DAT_005c30a0;
  }
  return puVar1;
}
```

---

---

## FUN_0042d38a — 0x42d38a

- Classification : internal
- Corps : `0x42d38a–0x42d3fa`
- État : pseudocode obtenu
- Evidence : `ev_fec237f415515a24d098aa09dca2357a2e41918dbd740f217e75583b5bfb4756`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401861` — `thunk_FUN_0042bea2`
- `0x402338` — `thunk_FUN_0042bef7`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042d38a(void)

{
  int *piVar1;
  int iVar2;
  
  if ((DAT_005c30cc != 0) && (DAT_005c30a0 != 0)) {
    piVar1 = (int *)thunk_FUN_0042bea2(0);
    if (((DAT_0049e138 == 0) || (DAT_0049e138 == 1)) &&
       (iVar2 = (**(code **)(*piVar1 + 0x80))(piVar1,DAT_005c30a0), iVar2 == -0x7789fe3e)) {
      thunk_FUN_0042bef7();
    }
    DAT_005c30a0 = 0;
  }
  return;
}
```

---

---

## FUN_0042d3fb — 0x42d3fb

- Classification : internal
- Corps : `0x42d3fb–0x42d44c`
- État : pseudocode obtenu
- Evidence : `ev_af38e8b04407f399258e363b86e85dc9d884463e8f1486995fd0cf1c77cb6006`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40144c` — `thunk_FUN_0042cc24`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x402022` — `thunk_FUN_00406604`
- `0x4022de` — `thunk_FUN_0042d9cd`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042d3fb(undefined4 param_1)

{
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_14 = 0;
  local_10 = 0;
  local_c = 0x27f;
  local_8 = 0x1df;
  local_18 = thunk_FUN_0042d28f();
  thunk_FUN_00406604(&local_18,param_1);
  thunk_FUN_0042d38a();
  thunk_FUN_0042d9cd(3);
  thunk_FUN_0042cc24();
  return;
}
```

---

---

## FUN_0042d44d — 0x42d44d

- Classification : internal
- Corps : `0x42d44d–0x42d597`
- État : pseudocode obtenu
- Evidence : `ev_0cad0e8c5d5dcd1b0515eed190938aa4e6dfac39ca5d33fe92f5aebf99cf192c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x402081` — `thunk_FUN_004066e3`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x402338` — `thunk_FUN_0042bef7`

### Chaînes référencées

- `0x49e4c4` — "pane && pane->window->buffer"
- `0x49e4e4` — "C:\\float\\src\\graphsys.cpp"
- `0x49e500` — "grabScreen() failed: unsupported for GSDM_Bitmap."
- `0x49e534` — " Lock: %x"

### Pseudocode Ghidra

```c
void FUN_0042d44d(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  int local_84;
  int local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74 [2];
  int local_6c;
  int local_64;
  undefined4 local_50;
  int local_8;
  
  if ((param_1 == (undefined4 *)0x0) || (*(int *)*param_1 == 0)) {
    uVar1 = thunk_FUN_00414b64(s_C__float_src_graphsys_cpp_0049e4e4,0x40d,
                               s_pane____pane_>window_>buffer_0049e4c4);
  }
  else {
    uVar1 = 0;
  }
  if (DAT_0049e138 == 4) {
    thunk_FUN_00414ad0(s_grabScreen___failed__unsupported_0049e500);
  }
  else {
    local_74[0] = 0x6c;
    while( true ) {
      local_8 = (**(code **)(*DAT_005c30e8 + 100))(DAT_005c30e8,0,local_74,1,0,uVar1);
      if (local_8 != -0x7789fe3e) break;
      thunk_FUN_0042bef7();
    }
    if (local_8 == 0) {
      local_88 = local_50;
      local_84 = local_64 + -1;
      local_80 = local_6c + -1;
      local_7c = 0;
      local_78 = 0;
      local_9c = &local_88;
      local_98 = 0;
      local_94 = 0;
      local_90 = 0x27f;
      local_8c = 0x1df;
      thunk_FUN_004066e3(&local_9c,0,0,param_1,0,0,0xffffffff);
      (**(code **)(*DAT_005c30e8 + 0x80))(DAT_005c30e8,local_88);
    }
    else {
      thunk_FUN_00414ad0(s_Lock___x_0049e534,local_8);
    }
  }
  return;
}
```

---

---

## FUN_0042d598 — 0x42d598

- Classification : internal
- Corps : `0x42d598–0x42d646`
- État : pseudocode obtenu
- Evidence : `ev_775cb18279b2429ed095c9c82061dcec90349c65dd123fd9d3380487b6801d53`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402298` — `thunk_FUN_00414ad0`
- `0x402338` — `thunk_FUN_0042bef7`

### Chaînes référencées

- `0x49e540` — " Lock: %x"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_0042d598(void)

{
  undefined4 *puVar1;
  undefined4 local_74 [2];
  int local_6c;
  int local_64;
  int local_50;
  int local_8;
  
  if (DAT_005c30cc == 0) {
    puVar1 = (undefined4 *)0x0;
  }
  else if (DAT_005c30d0 == 0) {
    puVar1 = (undefined4 *)0x0;
  }
  else if (DAT_005c1888 == 0) {
    local_74[0] = 0x6c;
    local_8 = (**(code **)(*DAT_005c30f0 + 100))(DAT_005c30f0,0,local_74,1,0);
    if (local_8 == -0x7789fe3e) {
      thunk_FUN_0042bef7();
    }
    else if (local_8 != 0) {
      thunk_FUN_00414ad0(s_Lock___x_0049e540,local_8);
      return (undefined4 *)0x0;
    }
    DAT_005c1888 = local_50;
    DAT_005c188c = local_64 + -1;
    _DAT_005c1890 = local_6c + -1;
    puVar1 = &DAT_005c1888;
  }
  else {
    puVar1 = &DAT_005c1888;
  }
  return puVar1;
}
```

---

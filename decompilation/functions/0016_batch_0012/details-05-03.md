# 0016_batch_0012 — détails (3/3)

## FUN_0045d53c — 0x45d53c

- Classification : internal
- Corps : `0x45d53c–0x45d5b9`
- État : pseudocode obtenu
- Evidence : `ev_785dd3a6093d5e2a2fdb69677f3152a4e0df8e2d38aa1e7475c393043ce9b143`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045d53c(void)

{
  int iVar1;
  int in_ECX;
  int local_8;
  
  for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
    if (((*(short *)(in_ECX + 4 + local_8 * 2) != -1) &&
        (iVar1 = *(short *)(in_ECX + 4 + local_8 * 2) * 0x4c, iVar1 != -0x6137b8)) &&
       ((*(uint *)(&DAT_006137d4 + iVar1) & 0x908) == 0)) {
      *(uint *)(&DAT_006137d4 + iVar1) = *(uint *)(&DAT_006137d4 + iVar1) | 0x2000;
      *(undefined4 *)(&DAT_006137dc + iVar1) = 0;
    }
  }
  return;
}
```

---

---

## FUN_0045d5ba — 0x45d5ba

- Classification : internal
- Corps : `0x45d5ba–0x45d773`
- État : pseudocode obtenu
- Evidence : `ev_03503d5f4f21c180313cc4e25f1af2c527b9a42b659ae9bcfabda4eea5422659`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- `0x4a43cc` — "C:\\float\\src\\staffbld.cpp"

### Pseudocode Ghidra

```c
void FUN_0045d5ba(int param_1,short *param_2)

{
  int iVar1;
  int local_14;
  
  iVar1 = thunk_FUN_0045c3bb();
  if (iVar1 == 0) {
    thunk_FUN_00414b64(s_C__float_src_staffbld_cpp_004a43cc,0x350,&DAT_004a43c8);
  }
  iVar1 = *(int *)(iVar1 + 0x10);
  *(undefined4 *)(param_1 + *param_2 * 4) = 5;
  *param_2 = *param_2 + 1;
  if ((0x2b < iVar1) && (iVar1 < 0x2f)) {
    *(undefined4 *)(param_1 + *param_2 * 4) = 0x10;
    *param_2 = *param_2 + 1;
    *(undefined4 *)(param_1 + *param_2 * 4) = 0x11;
    *param_2 = *param_2 + 1;
    *(undefined4 *)(param_1 + *param_2 * 4) = 0x12;
    *param_2 = *param_2 + 1;
    *(undefined4 *)(param_1 + *param_2 * 4) = 0x13;
    *param_2 = *param_2 + 1;
    *(undefined4 *)(param_1 + *param_2 * 4) = 0xf;
    *param_2 = *param_2 + 1;
  }
  if ((iVar1 == 0x2f) || (iVar1 == 0x30)) {
    *(undefined4 *)(param_1 + *param_2 * 4) = 6;
    *param_2 = *param_2 + 1;
    for (local_14 = 0; local_14 < 8; local_14 = local_14 + 1) {
      *(int *)(param_1 + *param_2 * 4) = local_14 + 0x15;
      *param_2 = *param_2 + 1;
    }
  }
  *(undefined4 *)(param_1 + *param_2 * 4) = 2;
  *param_2 = *param_2 + 1;
  return;
}
```

---

---

## FUN_0045d774 — 0x45d774

- Classification : internal
- Corps : `0x45d774–0x45d7e7`
- État : pseudocode obtenu
- Evidence : `ev_db8926026801790e01de6e61f2ff6ed838d6659a1deda65df9a6ca559d914928`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018cf` — `thunk_FUN_0041ff2e`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0045d774(int param_1)

{
  short sVar1;
  int in_ECX;
  int local_c;
  int local_8;
  
  local_8 = 0;
  for (local_c = 0; local_c < 8; local_c = local_c + 1) {
    if ((*(short *)(in_ECX + 4 + local_c * 2) != -1) &&
       (sVar1 = thunk_FUN_0041ff2e(), sVar1 == param_1)) {
      local_8 = local_8 + 1;
    }
  }
  return local_8;
}
```

---

---

## FUN_0045d7e8 — 0x45d7e8

- Classification : internal
- Corps : `0x45d7e8–0x45d866`
- État : pseudocode obtenu
- Evidence : `ev_fff50c897dddc692990ebb4ec2b95c2311565ddf1b32c8498bc8f607b2dcd273`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018cf` — `thunk_FUN_0041ff2e`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0045d7e8(int param_1,int param_2)

{
  short sVar1;
  int in_ECX;
  int local_8;
  
  param_1 = param_1 + 1;
  if (param_1 < 0) {
    param_1 = 0;
  }
  local_8 = param_1;
  while( true ) {
    if (7 < local_8) {
      return -1;
    }
    if ((*(short *)(in_ECX + 4 + local_8 * 2) != -1) &&
       (sVar1 = thunk_FUN_0041ff2e(), sVar1 == param_2)) break;
    local_8 = local_8 + 1;
  }
  return local_8;
}
```

---

# 0009_batch_0005 — détails (3/3)

## FUN_00413b68 — 0x413b68

- Classification : internal
- Corps : `0x413b68–0x413c5f`
- État : pseudocode obtenu
- Evidence : `ev_f0de043d2aa2f8e66f7ede13c134f2b30e329dcf5f0a5a6fdbbc9ffb5d5d57d4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00413b68(void)

{
  int *in_ECX;
  int local_14;
  uint local_c;
  int *local_8;
  
  if (((DAT_004befe0 == 0) || (DAT_004befec != DAT_004befe8)) && (DAT_004befe0 != 0)) {
    local_c = 0;
    local_8 = in_ECX;
    for (local_14 = 0; local_14 < 0x20; local_14 = local_14 + 1) {
      if (((*local_8 == 1) && ((uint)in_ECX[0x49d] < (uint)local_8[2])) &&
         (local_c < (uint)(local_8[2] - in_ECX[0x49d]))) {
        local_c = local_8[2] - in_ECX[0x49d];
      }
      local_8 = local_8 + 0x18;
    }
    if ((DAT_004c03bc == 0) && ((uint)(in_ECX[0x49e] << 2) < local_c)) {
      _DAT_004bf114 = local_c >> 2;
      DAT_004c03bc = 1;
    }
    else if ((DAT_004c03bc != 0) && (local_c < (uint)(in_ECX[0x49e] << 1))) {
      _DAT_004bf114 = 0;
      DAT_004c03bc = 0;
    }
  }
  return;
}
```

---

---

## FUN_00413c60 — 0x413c60

- Classification : internal
- Corps : `0x413c60–0x413d85`
- État : pseudocode obtenu
- Evidence : `ev_4472f953f46f209135cb7f1cb60b52ed138e0bb9110b961ab459113a0ee4b154`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x49baa4` — "\n[Current] Tick %04d  Period %04d\n"
- `0x49bac8` — "%c Tick %04d  Class %04d  Size %04d [%d]"
- `0x49baf4` — "P%03d S%03d R%03d HCS %x CCS %x"

### Pseudocode Ghidra

```c
void FUN_00413c60(void)

{
  int *in_ECX;
  undefined1 local_10;
  int local_c;
  int *local_8;
  
  thunk_FUN_00414ad0(s__Current__Tick__04d_Period__04d_0049baa4,in_ECX[0x49d],in_ECX[0x49f]);
  local_8 = in_ECX;
  for (local_c = 0; local_c < 0x20; local_c = local_c + 1) {
    local_10 = 0x20;
    if (*local_8 != 0) {
      local_10 = 0x2a;
    }
    thunk_FUN_00414ad0(s__c_Tick__04d_Class__04d_Size__04_0049bac8,local_10,local_8[2],local_8[1],
                       local_8[3],local_8[4]);
    local_8 = local_8 + 0x18;
  }
  for (local_c = 0; local_c < 0x40; local_c = local_c + 1) {
    thunk_FUN_00414ad0(s_P_03d_S_03d_R_03d_HCS__x_CCS__x_0049baf4,in_ECX[local_c * 6 + 0x31e],
                       in_ECX[local_c * 6 + 799],in_ECX[local_c * 6 + 800],
                       in_ECX[local_c * 6 + 0x321],in_ECX[local_c * 6 + 0x322]);
  }
  thunk_FUN_00414ad0(&DAT_0049bb14);
  return;
}
```

---

---

## FUN_00413d86 — 0x413d86

- Classification : internal
- Corps : `0x413d86–0x413d9b`
- État : pseudocode obtenu
- Evidence : `ev_51ac6b66ad3a0f49caec3ad83fe26529427dd49255075682db91a2098a560966`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b4f` — `thunk_FUN_00413d9c`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00413d86(void)

{
  undefined4 in_ECX;
  
  thunk_FUN_00413d9c();
  return in_ECX;
}
```

---

---

## FUN_00413d9c — 0x413d9c

- Classification : internal
- Corps : `0x413d9c–0x413e70`
- État : pseudocode obtenu
- Evidence : `ev_c237cbb77808c2413fb7939337954826b54d17c5a8739afa716b3996dc8f6bb5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40152d` — `thunk_FUN_0044aa69`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00413d9c(void)

{
  void *in_ECX;
  int local_8;
  
  _memset(in_ECX,0,0xc00);
  _memset((void *)((int)in_ECX + 0xc00),0,0x14);
  for (local_8 = 0; local_8 < 0x40; local_8 = local_8 + 1) {
    *(undefined4 *)((int)in_ECX + local_8 * 0x18 + 0xc74) = 0;
    *(undefined4 *)((int)in_ECX + local_8 * 0x18 + 0xc80) = 0;
  }
  *(undefined4 *)((int)in_ECX + 0x1274) = 0;
  *(undefined4 *)((int)in_ECX + 0x127c) = 0;
  *(undefined4 *)((int)in_ECX + 0x1278) = 10;
  *(undefined4 *)((int)in_ECX + 0x1284) = 0;
  *(undefined4 *)((int)in_ECX + 0x1280) = 0;
  *(undefined4 *)((int)in_ECX + 0x1288) = 0;
  thunk_FUN_0044aa69(&LAB_0040133e);
  return;
}
```

---

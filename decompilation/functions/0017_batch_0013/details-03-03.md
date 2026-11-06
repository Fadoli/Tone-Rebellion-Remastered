# 0017_batch_0013 — détails (3/3)

## FUN_004626f8 — 0x4626f8

- Classification : internal
- Corps : `0x4626f8–0x4628fc`
- État : pseudocode obtenu
- Evidence : `ev_ceec68ebd92188172b554b5516640e2fa7b5db846231f2264f38376bdc7d3acd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40173a` — `thunk_FUN_004672a6`
- `0x401a69` — `thunk_FUN_00452ceb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4
FUN_004626f8(undefined4 param_1,short param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  short *psVar1;
  int iVar2;
  int in_ECX;
  uint local_34;
  uint local_30;
  uint local_20;
  short *local_1c;
  int local_18;
  int local_14;
  short *local_10;
  int local_c;
  short local_8;
  
  local_8 = -1;
  local_14 = 0;
  if ((param_3 < 0) || (3 < param_3)) {
    local_10 = (short *)0x0;
    local_c = 0x9ff;
    psVar1 = (short *)(in_ECX + 0x428);
  }
  else {
    local_10 = *(short **)(in_ECX + 0x408 + param_3 * 8);
    local_c = *(int *)(in_ECX + 0x40c + param_3 * 8);
    psVar1 = local_10;
  }
  local_1c = (short *)(in_ECX + 0x428);
  for (local_18 = 0; local_18 < *(short *)(in_ECX + 0x29a8); local_18 = local_18 + 1) {
    if (((int)local_10 <= (int)*local_1c) && (*local_1c <= local_c)) {
      local_20 = 0;
      switch(param_1) {
      case 0:
        local_20 = (uint)(*(int *)(local_1c + 2) == (int)param_2);
        break;
      case 1:
        if ((*(int *)(local_1c + 2) == 0) && (*(int *)(local_1c + 8) == (int)param_2)) {
          local_30 = 1;
        }
        else {
          local_30 = 0;
        }
        local_20 = local_30;
        break;
      case 2:
        if (((*(int *)(local_1c + 2) == 0) && (*(int *)(local_1c + 10) == (int)param_2)) &&
           ((*(int *)(local_1c + 8) == 0x2a || (local_1c[0xc] != -1)))) {
          local_20 = 1;
        }
        break;
      case 3:
        if ((param_2 < 5) || (0x21 < param_2)) {
          local_20 = thunk_FUN_00452ceb((int)param_2,param_3);
        }
        else {
          if ((*(int *)(local_1c + 10) == param_3) &&
             (((*(int *)(local_1c + 8) == 0x2a || (local_1c[0xc] != -1)) &&
              (0 < *(short *)(&DAT_006191fc + param_2 * 2 + param_3 * 0x14a0))))) {
            local_34 = 1;
          }
          else {
            local_34 = 0;
          }
          local_20 = local_34;
        }
      }
      if ((local_20 != 0) &&
         ((iVar2 = thunk_FUN_004672a6((int)*local_1c,(int)local_1c[1],param_4,param_5),
          local_8 == -1 || (iVar2 < local_14)))) {
        local_8 = (short)local_18;
        local_14 = iVar2;
      }
    }
    psVar1 = local_1c + 0x30;
    local_1c = psVar1;
  }
  return CONCAT22((short)((uint)psVar1 >> 0x10),local_8);
}
```

---

---

## FUN_0046290d — 0x46290d

- Classification : internal
- Corps : `0x46290d–0x462a86`
- État : pseudocode obtenu
- Evidence : `ev_17007ffebe96d72cd52cb293a42776a6f5d9225353c509d624a7118731d03beb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f32` — `thunk_FUN_00450a71`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046290d(void)

{
  int in_ECX;
  undefined4 local_c;
  undefined4 local_8;
  
  for (local_c = 0; local_c < *(short *)(in_ECX + 0x29a8); local_c = local_c + 1) {
    thunk_FUN_00450a71();
  }
  while (6.28318 <= *(float *)(in_ECX + 0x29d4)) {
    *(float *)(in_ECX + 0x29d4) = *(float *)(in_ECX + 0x29d4) - 6.28318;
  }
  while (*(float *)(in_ECX + 0x29d4) < 0.0) {
    *(float *)(in_ECX + 0x29d4) = *(float *)(in_ECX + 0x29d4) + 6.28318;
  }
  local_8 = -1;
  if ((DAT_006191b4 == 3) && (99 < DAT_006191b6)) {
    local_8 = DAT_006191b6 + -100;
  }
  else if ((DAT_006191b4 == 4) && (DAT_006191b6 < 0x3c)) {
    local_8 = DAT_006191b6 + 200;
  }
  if (local_8 != -1) {
    if (*(int *)(DAT_0049f538 * 0x14a0 + 0x619248) == 0) {
      local_8 = -(local_8 / 0x46);
    }
    else {
      local_8 = (local_8 / 0x46) / 3;
    }
    if (local_8 < -0x14) {
      local_8 = -0x14;
    }
    if (0x14 < local_8) {
      local_8 = 0x14;
    }
    if (200 < *(int *)(in_ECX + 0x29d8)) {
      *(int *)(in_ECX + 0x29d8) = *(int *)(in_ECX + 0x29d8) + local_8;
    }
  }
  return;
}
```

---

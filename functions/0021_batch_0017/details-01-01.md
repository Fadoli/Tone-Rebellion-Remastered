# 0021_batch_0017 — détails (1/3)

## FUN_0047e790 — 0x47e790

- Classification : internal
- Corps : `0x47e790–0x47e81f`
- État : pseudocode obtenu
- Evidence : `ev_712bcd1cc46e6167f2f0a6b8dc9e8ceff66d6acddf14085e755eb6afe2a1a6eb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0047e790(undefined *param_1,undefined4 *param_2,uint *param_3)

{
  uint uVar1;
  undefined **local_c;
  
  local_c = &PTR_LOOP_004a65c0;
  while ((param_1 <= local_c[4] || (local_c[5] <= param_1))) {
    local_c = (undefined **)*local_c;
    if (local_c == &PTR_LOOP_004a65c0) {
      return 0;
    }
  }
  if ((((uint)param_1 & 0xf) == 0) && (0xff < ((uint)param_1 & 0xfff))) {
    *param_2 = local_c;
    uVar1 = (uint)param_1 & 0xfffff000;
    *param_3 = uVar1;
    return uVar1 + 8 + ((int)((int)param_1 - (uVar1 + 0x100)) >> 4);
  }
  return 0;
}
```

---

---

## FUN_0047e820 — 0x47e820

- Classification : internal
- Corps : `0x47e820–0x47e88b`
- État : pseudocode obtenu
- Evidence : `ev_03b6a41394b7215bb4ca18189eda5b59fd6567e0198bf1b65a65504fa94c2252`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47e630` — `FUN_0047e630`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047e820(int param_1,int param_2,byte *param_3)

{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + 0x18 + (param_2 - *(int *)(param_1 + 0x10) >> 0xc) * 8);
  *piVar1 = *piVar1 + (uint)*param_3;
  *param_3 = 0;
  piVar1[1] = 0xf1;
  if ((*piVar1 == 0xf0) && (DAT_006325b8 = DAT_006325b8 + 1, DAT_006325b8 == 0x20)) {
    FUN_0047e630(0x10);
  }
  return;
}
```

---

---

## FUN_0047e890 — 0x47e890

- Classification : internal
- Corps : `0x47e890–0x47ec47`
- État : pseudocode obtenu
- Evidence : `ev_6694fb9854f61d00287e8040f193832bc8cabd1598e434bc4dec7bca314aec49`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x22` — `KERNEL32.DLL::VirtualAlloc`
- `0x474b20` — `_memset`
- `0x47e3d0` — `FUN_0047e3d0`
- `0x47ec50` — `FUN_0047ec50`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int * FUN_0047e890(uint param_1)

{
  undefined **ppuVar1;
  int *piVar2;
  int *piVar3;
  undefined *puVar4;
  undefined **local_24;
  int *local_20;
  int local_1c;
  int local_18;
  undefined **local_14;
  int local_c;
  int *local_8;
  
  local_24 = (undefined **)PTR_LOOP_004a85e0;
  do {
    if (local_24[4] != (undefined *)0xffffffff) {
      local_8 = (int *)local_24[2];
      local_c = (int)local_24[4] + ((int)local_8 - (int)(local_24 + 6) >> 3) * 0x1000;
      for (; local_8 < local_24 + 0x806; local_8 = local_8 + 2) {
        if (((int)param_1 <= *local_8) && (param_1 < (uint)local_8[1])) {
          piVar2 = (int *)FUN_0047ec50(local_c,*local_8,param_1);
          if (piVar2 != (int *)0x0) {
            PTR_LOOP_004a85e0 = (undefined *)local_24;
            *local_8 = *local_8 - param_1;
            local_24[2] = (undefined *)local_8;
            return piVar2;
          }
          local_8[1] = param_1;
        }
        local_c = local_c + 0x1000;
      }
      piVar2 = (int *)local_24[2];
      local_c = (int)local_24[4];
      for (local_8 = (int *)(local_24 + 6); local_8 < piVar2; local_8 = local_8 + 2) {
        if (((int)param_1 <= *local_8) && (param_1 < (uint)local_8[1])) {
          piVar3 = (int *)FUN_0047ec50(local_c,*local_8,param_1);
          if (piVar3 != (int *)0x0) {
            PTR_LOOP_004a85e0 = (undefined *)local_24;
            *local_8 = *local_8 - param_1;
            local_24[2] = (undefined *)local_8;
            return piVar3;
          }
          local_8[1] = param_1;
        }
        local_c = local_c + 0x1000;
      }
    }
    local_24 = (undefined **)*local_24;
  } while (local_24 != (undefined **)PTR_LOOP_004a85e0);
  local_24 = &PTR_LOOP_004a65c0;
  while ((local_24[4] == (undefined *)0xffffffff || (local_24[3] == (undefined *)0x0))) {
    local_24 = (undefined **)*local_24;
    if (local_24 == &PTR_LOOP_004a65c0) {
      puVar4 = (undefined *)FUN_0047e3d0();
      if (puVar4 == (undefined *)0x0) {
        piVar2 = (int *)0x0;
      }
      else {
        piVar2 = *(int **)(puVar4 + 0x10);
        *(undefined1 *)(piVar2 + 2) = (undefined1)param_1;
        PTR_LOOP_004a85e0 = puVar4;
        *piVar2 = (int)piVar2 + param_1 + 8;
        piVar2[1] = 0xf0 - param_1;
        *(uint *)(puVar4 + 0x18) = *(int *)(puVar4 + 0x18) - (param_1 & 0xff);
        piVar2 = piVar2 + 0x40;
      }
      return piVar2;
    }
  }
  ppuVar1 = (undefined **)local_24[3];
  piVar2 = (int *)(local_24[4] + ((int)ppuVar1 - (int)(local_24 + 6) >> 3) * 0x1000);
  local_14 = ppuVar1;
  for (local_18 = 0; (*local_14 == (undefined *)0xffffffff && (local_18 < 0x10));
      local_18 = local_18 + 1) {
    local_14 = local_14 + 2;
  }
  piVar3 = VirtualAlloc(piVar2,local_18 << 0xc,0x1000,4);
  if (piVar3 == piVar2) {
    _memset(piVar2,local_18 << 0xc,0);
    local_20 = piVar2;
    local_14 = ppuVar1;
    for (local_1c = 0; local_1c < local_18; local_1c = local_1c + 1) {
      *local_20 = (int)(local_20 + 2);
      local_20[1] = 0xf0;
      *(undefined1 *)(local_20 + 0x3e) = 0xff;
      *local_14 = (undefined *)0xf0;
      local_14[1] = (undefined *)0xf1;
      local_20 = local_20 + 0x400;
      local_14 = local_14 + 2;
    }
    PTR_LOOP_004a85e0 = (undefined *)local_24;
    for (; (local_14 < local_24 + 0x806 && (*local_14 != (undefined *)0xffffffff));
        local_14 = local_14 + 2) {
    }
    local_24[3] = (undefined *)(-(uint)(local_14 < local_24 + 0x806) & (uint)local_14);
    *(undefined1 *)(piVar2 + 2) = (undefined1)param_1;
    local_24[2] = (undefined *)ppuVar1;
    *ppuVar1 = *ppuVar1 + -param_1;
    *piVar2 = (int)piVar2 + param_1 + 8;
    piVar2[1] = piVar2[1] - param_1;
    return piVar2 + 0x40;
  }
  return (int *)0x0;
}
```

---

---

## FUN_0047ec50 — 0x47ec50

- Classification : internal
- Corps : `0x47ec50–0x47eef8`
- État : pseudocode obtenu
- Evidence : `ev_0e7bfd6473e043985ec6c19f0f0690a96edb4c6e7accc729fbadcfe979551b8f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0047ec50(int *param_1,uint param_2,uint param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  uint local_14;
  byte *local_10;
  byte *local_c;
  
  pbVar1 = (byte *)*param_1;
  pbVar2 = (byte *)(param_1 + 0x3e);
  if ((uint)param_1[1] < param_3) {
    local_c = pbVar1;
    if (pbVar1[param_1[1]] != 0) {
      local_c = pbVar1 + param_1[1];
    }
    while (local_c + param_3 < pbVar2) {
      if (*local_c == 0) {
        local_14 = 1;
        local_10 = local_c;
        while (local_10 = local_10 + 1, *local_10 == 0) {
          local_14 = local_14 + 1;
        }
        if (param_3 <= local_14) {
          if (local_c + param_3 < pbVar2) {
            *param_1 = (int)(local_c + param_3);
            param_1[1] = local_14 - param_3;
          }
          else {
            *param_1 = (int)(param_1 + 2);
            param_1[1] = 0;
          }
          *local_c = (byte)param_3;
          return (int)param_1 * -0xf + (int)local_c * 0x10 + 0x80;
        }
        if (local_c == pbVar1) {
          param_1[1] = local_14;
        }
        else {
          param_2 = param_2 - local_14;
          if (param_2 < param_3) {
            return 0;
          }
        }
        local_c = local_10;
      }
      else {
        local_c = local_c + *local_c;
      }
    }
    local_c = (byte *)(param_1 + 2);
    while ((local_c < pbVar1 && (local_c + param_3 < pbVar2))) {
      if (*local_c == 0) {
        local_14 = 1;
        local_10 = local_c;
        while (local_10 = local_10 + 1, *local_10 == 0) {
          local_14 = local_14 + 1;
        }
        if (param_3 <= local_14) {
          if (local_c + param_3 < pbVar2) {
            *param_1 = (int)(local_c + param_3);
            param_1[1] = local_14 - param_3;
          }
          else {
            *param_1 = (int)(param_1 + 2);
            param_1[1] = 0;
          }
          *local_c = (byte)param_3;
          return (int)param_1 * -0xf + (int)local_c * 0x10 + 0x80;
        }
        param_2 = param_2 - local_14;
        if (param_2 < param_3) {
          return 0;
        }
        local_c = local_10;
      }
      else {
        local_c = local_c + *local_c;
      }
    }
    iVar3 = 0;
  }
  else {
    *pbVar1 = (byte)param_3;
    if (pbVar1 + param_3 < pbVar2) {
      *param_1 = *param_1 + param_3;
      param_1[1] = param_1[1] - param_3;
    }
    else {
      *param_1 = (int)(param_1 + 2);
      param_1[1] = 0;
    }
    iVar3 = (int)param_1 * -0xf + (int)pbVar1 * 0x10 + 0x80;
  }
  return iVar3;
}
```

---

---

## FUN_0047ef00 — 0x47ef00

- Classification : internal
- Corps : `0x47ef00–0x47f063`
- État : pseudocode obtenu
- Evidence : `ev_a15b7a2edccd06ccb25339c97b1c48122d56ab58ae8c70db1057606f1fd7fe9e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047ef00(int param_1,uint *param_2,byte *param_3,uint param_4)

{
  int *piVar1;
  uint uVar2;
  uint *local_1c;
  undefined4 local_18;
  uint *local_14;
  uint local_c;
  
  local_18 = 0;
  piVar1 = (int *)(param_1 + 0x18 + ((int)param_2 - *(int *)(param_1 + 0x10) >> 0xc) * 8);
  uVar2 = (uint)*param_3;
  if (param_4 < uVar2) {
    *param_3 = (byte)param_4;
    *piVar1 = *piVar1 + (uVar2 - param_4);
    piVar1[1] = 0xf1;
    local_18 = 1;
  }
  else if ((uVar2 < param_4) && (param_3 + param_4 <= param_2 + 0x3e)) {
    local_1c = (uint *)(param_3 + param_4);
    for (local_14 = (uint *)(param_3 + uVar2); (local_14 < local_1c && ((char)*local_14 == '\0'));
        local_14 = (uint *)((int)local_14 + 1)) {
    }
    if (local_14 == local_1c) {
      *param_3 = (byte)param_4;
      if ((param_3 <= (byte *)*param_2) && ((uint *)*param_2 < local_1c)) {
        if (local_1c < param_2 + 0x3e) {
          *param_2 = (uint)local_1c;
          local_c = 0;
          for (; (char)*local_1c == '\0'; local_1c = (uint *)((int)local_1c + 1)) {
            local_c = local_c + 1;
          }
          param_2[1] = local_c;
        }
        else {
          *param_2 = (uint)(param_2 + 2);
          param_2[1] = 0;
        }
      }
      *piVar1 = *piVar1 + (uVar2 - param_4);
      local_18 = 1;
    }
  }
  return local_18;
}
```

---

---

## FUN_0047f070 — 0x47f070

- Classification : internal
- Corps : `0x47f070–0x47f2a6`
- État : pseudocode obtenu
- Evidence : `ev_4c907e71949aa2dfa789fa7b2e6325392f6f1e8a5f34d043ce735ecd4427e1d3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047f070(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int local_2c;
  undefined *local_28;
  int local_24;
  undefined **local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int *local_8;
  
  local_c = 0;
  local_20 = &PTR_LOOP_004a65c0;
  do {
    if ((undefined **)PTR_LOOP_004a85e0 == local_20) {
      local_c = local_c + 1;
    }
    if (local_20[4] != (undefined *)0xffffffff) {
      local_10 = 0;
      local_2c = 0;
      local_8 = (int *)local_20[4];
      for (; local_10 < 0x400; local_10 = local_10 + 1) {
        if (local_20[local_10 * 2 + 6] == (undefined *)0xffffffff) {
          if ((local_2c == 0) && ((undefined **)local_20[3] != local_20 + local_10 * 2 + 6)) {
            return 0xffffffff;
          }
          local_2c = local_2c + 1;
        }
        else {
          if (local_8 + 0x3e <= (int *)*local_8) {
            return 0xfffffffe;
          }
          if ((char)local_8[0x3e] != -1) {
            return 0xfffffffd;
          }
          local_14 = 0;
          local_1c = 0;
          local_28 = (undefined *)0x0;
          local_24 = 0;
          while (local_14 < 0xf0) {
            if ((int)local_8 + local_14 + 8 == *local_8) {
              local_1c = local_1c + 1;
            }
            if (*(char *)((int)local_8 + local_14 + 8) == '\0') {
              local_28 = local_28 + 1;
              local_24 = local_24 + 1;
              local_14 = local_14 + 1;
            }
            else {
              if ((int)local_20[local_10 * 2 + 7] <= local_24) {
                return 0xfffffffc;
              }
              if (local_1c == 1) {
                if (local_24 < local_8[1]) {
                  return 0xfffffffb;
                }
                local_1c = 2;
              }
              local_24 = 0;
              iVar1 = local_14;
              while (local_18 = iVar1 + 1,
                    local_18 < (int)(local_14 + (uint)*(byte *)((int)local_8 + local_14 + 8))) {
                iVar2 = iVar1 + 9;
                iVar1 = local_18;
                if (*(char *)((int)local_8 + iVar2) != '\0') {
                  return 0xfffffffa;
                }
              }
              local_14 = local_18;
            }
          }
          if (local_28 != local_20[local_10 * 2 + 6]) {
            return 0xfffffff9;
          }
          if (local_1c == 0) {
            return 0xfffffff8;
          }
        }
        local_8 = local_8 + 0x400;
      }
    }
    local_20 = (undefined **)*local_20;
    if (local_20 == &PTR_LOOP_004a65c0) {
      if (local_c == 0) {
        uVar3 = 0xfffffff7;
      }
      else {
        uVar3 = 0;
      }
      return uVar3;
    }
  } while( true );
}
```

---

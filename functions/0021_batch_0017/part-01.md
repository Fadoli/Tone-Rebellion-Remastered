# 0021_batch_0017 — détails (1/5)

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

## FUN_0047f2b0 — 0x47f2b0

- Classification : internal
- Corps : `0x47f2b0–0x47f364`
- État : pseudocode obtenu
- Evidence : `ev_0275cffc0ee5ad6c6796b6c465d9d7166d56f76cf76033030c002c2428d76d86`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4850c0` — `FUN_004850c0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_0047f2b0(int param_1,uint param_2)

{
  int iVar1;
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined4 local_c;
  uint local_8;
  
  if (param_1 + 1U < 0x101) {
    param_2 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & param_2;
  }
  else {
    if ((*(ushort *)(PTR_DAT_004a85e8 + (param_1 >> 8 & 0xffU) * 2) & 0x8000) == 0) {
      local_10 = (undefined1)param_1;
      local_f = 0;
      local_c = 1;
    }
    else {
      local_10 = (undefined1)((uint)param_1 >> 8);
      local_f = (undefined1)param_1;
      local_e = 0;
      local_c = 2;
    }
    iVar1 = FUN_004850c0(1,&local_10,local_c,&local_8,0,0);
    if (iVar1 == 0) {
      param_2 = 0;
    }
    else {
      param_2 = local_8 & 0xffff & param_2;
    }
  }
  return param_2;
}
```

---

## __trandisp1 — 0x47f370

- Classification : internal
- Corps : `0x47f370–0x47f3d6`
- État : pseudocode obtenu
- Evidence : `ev_d981cf225f753d3dd391f97aec99be4b7ead2e066244d0c8dc119ad74d5f5f09`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __trandisp1
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __trandisp1(void)

{
  float10 fVar1;
  byte bVar2;
  int in_EDX;
  undefined2 uVar3;
  int unaff_EBP;
  float10 in_ST0;
  
  if (*(char *)(in_EDX + 0xe) == '\x05') {
    uVar3 = (undefined2)
            CONCAT31((uint3)((byte)((ushort)*(undefined2 *)(unaff_EBP + -0xa4) >> 8) & 0xfe | 2),
                     0x3f);
  }
  else {
    uVar3 = 0x133f;
  }
  *(undefined2 *)(unaff_EBP + -0xa2) = uVar3;
  fVar1 = (float10)0;
  *(int *)(unaff_EBP + -0x94) = in_EDX;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST0) << 8 | (ushort)(in_ST0 < fVar1) << 9 | (ushort)(in_ST0 != fVar1) << 10 |
       (ushort)(in_ST0 == fVar1) << 0xe;
  *(undefined1 *)(unaff_EBP + -0x90) = 0;
  bVar2 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
                    /* WARNING: Could not recover jumptable at 0x0047f3d5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(in_EDX + (char)(&DAT_004a881d)[(byte)((bVar2 & 7) << 1 | (char)bVar2 < '\0')] + 0x10)
  )();
  return;
}
```

---

## __trandisp2 — 0x47f3d7

- Classification : internal
- Corps : `0x47f3d7–0x47f462`
- État : pseudocode obtenu
- Evidence : `ev_c8b1010e215c8218ff3c61ac1c916ac61805557fed4a61774bd4a940ab093d86`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __trandisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __trandisp2(void)

{
  float10 fVar1;
  char cVar2;
  byte bVar3;
  int in_EDX;
  undefined2 uVar4;
  int unaff_EBP;
  float10 in_ST0;
  float10 in_ST1;
  
  if (*(char *)(in_EDX + 0xe) == '\x05') {
    uVar4 = (undefined2)
            CONCAT31((uint3)((byte)((ushort)*(undefined2 *)(unaff_EBP + -0xa4) >> 8) & 0xfe | 2),
                     0x3f);
  }
  else {
    uVar4 = 0x133f;
  }
  *(undefined2 *)(unaff_EBP + -0xa2) = uVar4;
  fVar1 = (float10)0;
  *(int *)(unaff_EBP + -0x94) = in_EDX;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST0) << 8 | (ushort)(in_ST0 < fVar1) << 9 | (ushort)(in_ST0 != fVar1) << 10 |
       (ushort)(in_ST0 == fVar1) << 0xe;
  *(undefined1 *)(unaff_EBP + -0x90) = 0;
  fVar1 = (float10)0;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST1) << 8 | (ushort)(in_ST1 < fVar1) << 9 | (ushort)(in_ST1 != fVar1) << 10 |
       (ushort)(in_ST1 == fVar1) << 0xe;
  bVar3 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
  cVar2 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
                    /* WARNING: Could not recover jumptable at 0x0047f461. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(in_EDX + (char)((&DAT_004a881d)[(byte)(cVar2 << 1 | cVar2 < '\0') & 0xf] |
                              (&DAT_004a881d)[(byte)((bVar3 & 7) << 1 | (char)bVar3 < '\0')] << 2) +
              0x10))();
  return;
}
```

---

## FUN_0047f468 — 0x47f468

- Classification : internal
- Corps : `0x47f468–0x47f46c`
- État : pseudocode obtenu
- Evidence : `ev_b14756e4f16a1fc2b844dc4a0dbe3b7d58f5db15a27d35c56b63d40d940b4f98`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047f468(void)

{
  return;
}
```

---

## FUN_0047f476 — 0x47f476

- Classification : internal
- Corps : `0x47f476–0x47f47a`
- État : pseudocode obtenu
- Evidence : `ev_fd22a6bd17ee99ae27bc19a45980fe73a963c8ec92b376d08b5343a65dd36762`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_0047f476(void)

{
  return (float10)0;
}
```

---

## FUN_0047f540 — 0x47f540

- Classification : internal
- Corps : `0x47f540–0x47f556`
- État : pseudocode obtenu
- Evidence : `ev_2c0b93748c29e71d16581d0dd8213d1e91d5d124362a3ff60e74155d2621d87e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_0047f540(void)

{
  float10 in_ST0;
  
  FUN_00485220();
  return (float10)(double)in_ST0;
}
```

---

## __startOneArgErrorHandling — 0x47f557

- Classification : internal
- Corps : `0x47f557–0x47f592`
- État : pseudocode obtenu
- Evidence : `ev_3c4f47b9d3000109f93374ad2cde4827ef87757eb1f9af372402dd8492ec5e41`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x485220` — `FUN_00485220`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __startOneArgErrorHandling
   
   Library: Visual Studio */

float10 __startOneArgErrorHandling(void)

{
  float10 in_ST0;
  
  FUN_00485220();
  return (float10)(double)in_ST0;
}
```

---

## FUN_0047f5b5 — 0x47f5b5

- Classification : internal
- Corps : `0x47f5b5–0x47f5cb`
- État : pseudocode obtenu
- Evidence : `ev_5fc009e3c960b69b536653d70c604f92eba91edc6b6792147769c35edeb1b4d1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047f5b5(void)

{
  return;
}
```

---

## FUN_0047f5cc — 0x47f5cc

- Classification : internal
- Corps : `0x47f5cc–0x47f5e4`
- État : pseudocode obtenu
- Evidence : `ev_05d06287b5ee79d918d29f40504f65d5e4cfdd3f2662fc6c363e9fe90806702b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047f5cc(void)

{
  uint in_EAX;
  
  if ((in_EAX & 0x80000) != 0) {
    return 7;
  }
  return 1;
}
```

---

## __fload_withFB — 0x47f5e5

- Classification : internal
- Corps : `0x47f5e5–0x47f627`
- État : pseudocode obtenu
- Evidence : `ev_36233ad168267309b0372e11a31ed472d6957ee821e49169ace706dabc9ba876`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __fload_withFB
   
   Library: Visual Studio */

uint __fload_withFB(void)

{
  uint uVar1;
  int in_EDX;
  
  uVar1 = *(uint *)(in_EDX + 4) & 0x7ff00000;
  if (uVar1 != 0x7ff00000) {
    return uVar1;
  }
  return *(uint *)(in_EDX + 4);
}
```

---

## FUN_0047f628 — 0x47f628

- Classification : internal
- Corps : `0x47f628–0x47f63d`
- État : pseudocode obtenu
- Evidence : `ev_e9cc48933a41045022af0e15aed31461d7028c8cbfc8596e21f39c47057f70f0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_0047f628(undefined4 param_1,uint param_2)

{
  if ((param_2 & 0x7ff00000) != 0x7ff00000) {
    return param_2 & 0x7ff00000;
  }
  return param_2;
}
```

---

## FUN_0047f63e — 0x47f63e

- Classification : internal
- Corps : `0x47f63e–0x47f64a`
- État : pseudocode obtenu
- Evidence : `ev_c4cb090131be91a557460ee8f7e2eb9d5eb553da81a01ec520dc7d4dce2732c0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047f63e(void)

{
  return;
}
```

---

## __math_exit — 0x47f64b

- Classification : internal
- Corps : `0x47f64b–0x47f674`
- État : pseudocode obtenu
- Evidence : `ev_d7c002d37ff22e842c7494e663721a71ee33051b82447f8fbde9bcda1e4da128`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f557` — `__startOneArgErrorHandling`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __math_exit
   
   Library: Visual Studio */

void __math_exit(void)

{
  ushort in_FPUStatusWord;
  ushort unaff_retaddr;
  
  if (((unaff_retaddr != 0x27f) && ((unaff_retaddr & 0x20) != 0)) &&
     ((in_FPUStatusWord & 0x20) != 0)) {
    __startOneArgErrorHandling();
    return;
  }
  return;
}
```

---

## FUN_0047f730 — 0x47f730

- Classification : internal
- Corps : `0x47f730–0x47f7f7`
- État : pseudocode obtenu
- Evidence : `ev_69be632faabd26278117e3e6b13875203fa08cb59a8a31187d6038ffbcb87113`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482d70` — `FUN_00482d70`
- `0x4853a0` — `FUN_004853a0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_0047f730(int param_1)

{
  undefined *puVar1;
  int iVar2;
  uint local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  undefined1 local_14 [12];
  uint local_8;
  
  local_24 = 0;
  local_8 = FUN_004853a0(local_14,&local_18,param_1,0,0,0,0);
  if ((local_8 & 4) == 0) {
    iVar2 = FUN_00482d70(local_14,&local_20);
    if (((local_8 & 2) != 0) || (iVar2 == 1)) {
      local_24 = 0x80;
    }
    if (((local_8 & 1) != 0) || (iVar2 == 2)) {
      local_24 = local_24 | 0x100;
    }
  }
  else {
    local_24 = 0x200;
    local_20 = 0;
    local_1c = 0;
  }
  *(uint *)PTR_DAT_004a8830 = local_24;
  *(int *)(PTR_DAT_004a8830 + 4) = local_18 - param_1;
  puVar1 = PTR_DAT_004a8830;
  *(undefined4 *)(PTR_DAT_004a8830 + 0x10) = local_20;
  *(undefined4 *)(puVar1 + 0x14) = local_1c;
  return PTR_DAT_004a8830;
}
```

---

## __allmul — 0x47f800

- Classification : internal
- Corps : `0x47f800–0x47f833`
- État : pseudocode obtenu
- Evidence : `ev_7cd3dfead16ccba0e6142589c95ba8c5a145cddc65e4827db37ea35df86eb060`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __allmul
   
   Library: Visual Studio */

longlong __allmul(uint param_1,int param_2,uint param_3,int param_4)

{
  if (param_4 == 0 && param_2 == 0) {
    return (ulonglong)param_1 * (ulonglong)param_3;
  }
  return CONCAT44((int)((ulonglong)param_1 * (ulonglong)param_3 >> 0x20) +
                  param_2 * param_3 + param_1 * param_4,
                  (int)((ulonglong)param_1 * (ulonglong)param_3));
}
```

---

## FUN_0047f99e — 0x47f99e

- Classification : internal
- Corps : `0x47f99e–0x47f9e0`
- État : pseudocode obtenu
- Evidence : `ev_ed4f620baefe87593388856e8a4dac3c46a2201640a2fa6bb755c69a4276dfcc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined5 FUN_0047f99e(void)

{
  undefined4 uVar1;
  undefined4 in_EAX;
  undefined1 extraout_DL;
  undefined1 in_DL;
  int unaff_EBP;
  float10 in_ST0;
  float10 fVar2;
  float10 fVar3;
  undefined4 unaff_retaddr;
  
  fVar2 = ABS(in_ST0);
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)(_DAT_004a885e < fVar2) << 8 | (ushort)(NAN(_DAT_004a885e) || NAN(fVar2)) << 10 |
       (ushort)(_DAT_004a885e == fVar2) << 0xe;
  if ((*(byte *)(unaff_EBP + -0x9f) & 0x41) == 0) {
    fVar3 = ROUND(in_ST0);
    fVar2 = (float10)0;
    *(ushort *)(unaff_EBP + -0xa0) =
         (ushort)(fVar3 < fVar2) << 8 | (ushort)(NAN(fVar3) || NAN(fVar2)) << 10 |
         (ushort)(fVar3 == fVar2) << 0xe;
    fVar3 = in_ST0 - fVar3;
    fVar2 = (float10)0;
    *(ushort *)(unaff_EBP + -0xa0) =
         (ushort)(fVar3 < fVar2) << 8 | (ushort)(NAN(fVar3) || NAN(fVar2)) << 10 |
         (ushort)(fVar3 == fVar2) << 0xe;
    f2xm1(ABS(fVar3));
    return CONCAT14(*(undefined1 *)(unaff_EBP + -0x9f),in_EAX);
  }
  fVar2 = (float10)0;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)(in_ST0 < fVar2) << 8 | (ushort)(NAN(in_ST0) || NAN(fVar2)) << 10 |
       (ushort)(in_ST0 == fVar2) << 0xe;
  if ((*(byte *)(unaff_EBP + -0x9f) & 1) == 0) {
    return CONCAT14(in_DL,unaff_retaddr);
  }
  *(undefined1 *)(unaff_EBP + -0x90) = 4;
  uVar1 = FUN_0047f476();
  return CONCAT14(extraout_DL,uVar1);
}
```

---

## FUN_0047fa50 — 0x47fa50

- Classification : internal
- Corps : `0x47fa50–0x47fcb3`
- État : pseudocode obtenu
- Evidence : `ev_ca7d300667088ba2257548d702f817c2b4709b2e8eda449bb03c362e1611e7f9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47fcc0` — `FUN_0047fcc0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047fa50(int param_1,int param_2,int param_3,int param_4,undefined4 *param_5)

{
  int iVar1;
  undefined4 local_2c;
  undefined4 local_28;
  undefined8 local_24;
  undefined8 local_1c;
  undefined4 local_10;
  
  local_10 = 0;
  if (0.0 <= (double)CONCAT44(param_2,param_1)) {
    local_1c = (double)CONCAT44(param_2,param_1);
  }
  else {
    local_1c = -(double)CONCAT44(param_2,param_1);
  }
  if ((param_4 == 0x7ff00000) && (param_3 == 0)) {
    if (local_1c <= 1.0) {
      if (1.0 <= local_1c) {
        *param_5 = DAT_004a8ed8;
        param_5[1] = DAT_004a8edc;
        local_10 = 1;
      }
      else {
        *param_5 = 0;
        param_5[1] = 0;
      }
    }
    else {
      *param_5 = DAT_004a8ed0;
      param_5[1] = DAT_004a8ed4;
    }
  }
  else if ((param_4 == -0x100000) && (param_3 == 0)) {
    if (local_1c <= 1.0) {
      if (1.0 <= local_1c) {
        *param_5 = DAT_004a8ed8;
        param_5[1] = DAT_004a8edc;
        local_10 = 1;
      }
      else {
        *param_5 = DAT_004a8ed0;
        param_5[1] = DAT_004a8ed4;
      }
    }
    else {
      *param_5 = 0;
      param_5[1] = 0;
    }
  }
  else if ((param_2 == 0x7ff00000) && (param_1 == 0)) {
    if ((double)CONCAT44(param_4,param_3) <= 0.0) {
      if (0.0 <= (double)CONCAT44(param_4,param_3)) {
        *param_5 = 0;
        param_5[1] = 0x3ff00000;
      }
      else {
        *param_5 = 0;
        param_5[1] = 0;
      }
    }
    else {
      *param_5 = DAT_004a8ed0;
      param_5[1] = DAT_004a8ed4;
    }
  }
  else if ((param_2 == -0x100000) && (param_1 == 0)) {
    iVar1 = FUN_0047fcc0(param_3,param_4);
    if ((double)CONCAT44(param_4,param_3) <= 0.0) {
      if (0.0 <= (double)CONCAT44(param_4,param_3)) {
        *param_5 = 0;
        param_5[1] = 0x3ff00000;
      }
      else {
        if (iVar1 == 1) {
          local_2c = DAT_004a8ef0;
          local_28 = DAT_004a8ef4;
        }
        else {
          local_2c = 0;
          local_28 = 0;
        }
        *param_5 = local_2c;
        param_5[1] = local_28;
      }
    }
    else {
      if (iVar1 == 1) {
        local_24 = -(double)CONCAT44(DAT_004a8ed4,DAT_004a8ed0);
      }
      else {
        local_24 = (double)CONCAT44(DAT_004a8ed4,DAT_004a8ed0);
      }
      *param_5 = (undefined4)local_24;
      param_5[1] = local_24._4_4_;
    }
  }
  return local_10;
}
```

---


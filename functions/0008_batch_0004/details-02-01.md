# 0008_batch_0004 — détails (1/3)

## FUN_00410765 — 0x410765

- Classification : internal
- Corps : `0x410765–0x41081a`
- État : pseudocode obtenu
- Evidence : `ev_1d2dad714b0835ce39e42cb889ad7b89d812cf10a60122b546edb56c8bab3bb9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x40232e` — `thunk_FUN_0042da69`

### Chaînes référencées

- `0x49b4fc` — "C:\\float\\src\\color.cpp"

### Pseudocode Ghidra

```c
void FUN_00410765(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_308 [768];
  int local_8;
  
  if (param_1 == 0) {
    uVar2 = thunk_FUN_00414b64(s_C__float_src_color_cpp_0049b4fc,99,&DAT_0049b4f4);
  }
  else {
    uVar2 = 0;
  }
  if (param_3 < 0) {
    param_3 = 0;
  }
  if (0x100 < param_3) {
    param_3 = 0x100;
  }
  for (local_8 = 0; local_8 < 0x300; local_8 = local_8 + 1) {
    iVar1 = (uint)*(byte *)(param_1 + local_8) * (0x100 - param_3);
    local_308[local_8] = (char)(iVar1 + (iVar1 >> 0x1f & 0xffU) >> 8);
  }
  thunk_FUN_0042da69(0,0x100,local_308,uVar2);
  return;
}
```

---

---

## FUN_0041081b — 0x41081b

- Classification : internal
- Corps : `0x41081b–0x4108f9`
- État : pseudocode obtenu
- Evidence : `ev_4b05090f701cb7e107f1140474b08ad4a3b0f7bc528554ce981b8fac356ef62c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0041081b(byte *param_1,double param_2,double param_3,double param_4)

{
  double dVar1;
  double dVar2;
  int local_28;
  int local_24;
  byte *local_8;
  
  dVar2 = -1.0;
  local_28 = 0;
  local_8 = param_1;
  local_24 = 0;
  while( true ) {
    if (0xfe < local_24) {
      return local_28;
    }
    dVar1 = (param_4 - (double)local_8[2]) * (param_4 - (double)local_8[2]) +
            (param_3 - (double)local_8[1]) * (param_3 - (double)local_8[1]) +
            (param_2 - (double)*local_8) * (param_2 - (double)*local_8);
    if ((dVar1 < dVar2) || (local_24 == 0)) {
      local_28 = local_24;
      dVar2 = dVar1;
    }
    if (dVar1 == 0.0) break;
    local_24 = local_24 + 1;
    local_8 = local_8 + 3;
  }
  return local_28;
}
```

---

---

## FUN_004108fa — 0x4108fa

- Classification : internal
- Corps : `0x4108fa–0x410943`
- État : pseudocode obtenu
- Evidence : `ev_6aad382544647788dcae162d4ffa3e387a8785b58c804f404d9712177d069821`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a28` — `thunk_FUN_0041081b`
- `0x401f5f` — `thunk_FUN_0042dc4e`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004108fa(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined1 local_304 [768];
  
  thunk_FUN_0042dc4e(0,0x100,local_304);
  thunk_FUN_0041081b(local_304,param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}
```

---

---

## FUN_00410944 — 0x410944

- Classification : internal
- Corps : `0x410944–0x4109a5`
- État : pseudocode obtenu
- Evidence : `ev_b2e144693b4104db779dfc8b5068bff5b11282805cd238f880cf3427c4a72b31`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b90` — `FUN_00474b90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00410944(undefined1 *param_1,undefined1 param_2,int param_3)

{
  uint uVar1;
  int local_c;
  undefined1 *local_8;
  
  local_8 = param_1;
  for (local_c = 0; local_c < 0x100; local_c = local_c + 1) {
    uVar1 = FUN_00474b90();
    if (param_3 < (int)(((int)(uVar1 & 0xffff) >> 7 & 0xffU) + 1)) {
      *local_8 = (undefined1)local_c;
    }
    else {
      *local_8 = param_2;
    }
    local_8 = local_8 + 1;
  }
  return;
}
```

---

---

## FUN_004109a6 — 0x4109a6

- Classification : internal
- Corps : `0x4109a6–0x410bd1`
- État : pseudocode obtenu
- Evidence : `ev_92b1f53b9bea0cdd105ea797aafe454686d75cb0ff17e10a6e793201a87751da`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004109a6(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  byte *pbVar5;
  byte *local_58;
  uint local_4c;
  byte *local_44;
  byte *local_40;
  byte *local_34;
  int local_28;
  int local_18;
  byte *local_14;
  byte *local_8;
  
  param_2 = param_2 + *(int *)(param_2 + 8 + param_3 * 8);
  local_18 = param_1[2] + param_5 + *(int *)(param_2 + 0xc);
  local_28 = local_18 + (*(int *)(param_2 + 0x14) - *(int *)(param_2 + 0xc));
  if (param_1[4] < local_28) {
    local_28 = param_1[4];
  }
  iVar3 = *(int *)(*param_1 + 4) + 1;
  iVar4 = *(int *)*param_1 + local_18 * iVar3;
  local_44 = (byte *)(iVar4 + param_1[1]);
  local_34 = (byte *)(iVar4 + param_1[3]);
  local_8 = (byte *)(iVar4 + param_1[1] + param_4 + *(int *)(param_2 + 8));
  local_14 = (byte *)(param_2 + 0x18);
  for (; local_40 = local_8, local_18 <= local_28; local_18 = local_18 + 1) {
    while( true ) {
      pbVar2 = local_40;
      bVar1 = *local_14;
      pbVar5 = local_14 + 1;
      if (bVar1 == 0) break;
      if (bVar1 == 1) {
        local_4c = (uint)*pbVar5;
        local_14 = local_14 + 2;
        local_40 = local_40 + local_4c;
      }
      else {
        iVar4 = (int)(uint)bVar1 >> 1;
        if ((bVar1 & 1) == 0) {
          local_14 = local_14 + 2;
        }
        else {
          local_14 = pbVar5 + iVar4;
        }
        if (param_1[2] <= local_18) {
          local_58 = local_40 + iVar4 + -1;
          if (local_40 < local_44) {
            local_40 = local_44;
          }
          if (local_34 < local_58) {
            local_58 = local_34;
          }
          for (; local_40 <= local_58; local_40 = local_40 + 1) {
            *local_40 = *(byte *)(param_6 + (uint)*local_40);
          }
          local_40 = pbVar2 + iVar4;
        }
      }
    }
    local_44 = local_44 + iVar3;
    local_34 = local_34 + iVar3;
    local_8 = local_8 + iVar3;
    local_14 = pbVar5;
  }
  return;
}
```

---

---

## FUN_00410bd2 — 0x410bd2

- Classification : internal
- Corps : `0x410bd2–0x411032`
- État : pseudocode obtenu
- Evidence : `ev_93125d3599f8e9901971b43e4237340137b0390c6a4897be8c00a556729a3495`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f14` — `thunk_FUN_00404770`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00410bd2(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  int iVar4;
  byte *pbVar5;
  uint uVar6;
  uint uVar7;
  byte bVar8;
  int iVar9;
  uint uVar10;
  bool bVar11;
  byte *local_8c;
  byte *local_88;
  byte *local_80;
  byte *local_7c;
  byte *local_74;
  byte local_68;
  byte *local_60;
  uint local_5c;
  byte *local_44;
  byte *local_40;
  byte *local_34;
  int local_28;
  uint local_18;
  byte *local_14;
  byte *local_8;
  
  if (0 < param_6) {
    if (param_6 < 8) {
      param_2 = param_2 + *(int *)(param_2 + 8 + param_3 * 8);
      local_18 = param_1[2] + param_5 + *(int *)(param_2 + 0xc);
      local_28 = local_18 + (*(int *)(param_2 + 0x14) - *(int *)(param_2 + 0xc));
      if (param_1[4] < local_28) {
        local_28 = param_1[4];
      }
      iVar9 = *(int *)(*param_1 + 4) + 1;
      iVar4 = *(int *)*param_1 + local_18 * iVar9;
      local_44 = (byte *)(iVar4 + param_1[1]);
      local_34 = (byte *)(iVar4 + param_1[3]);
      local_8 = (byte *)(iVar4 + param_1[1] + param_4 + *(int *)(param_2 + 8));
      local_14 = (byte *)(param_2 + 0x18);
      for (; (int)local_18 <= local_28; local_18 = local_18 + 1) {
        bVar1 = (&DAT_0049b444)[param_6 * 4 + (local_18 & 3)];
        uVar6 = (int)(char)bVar1 >> 4 & 0xf;
        bVar8 = bVar1 & 0xf;
        local_40 = local_8;
        while( true ) {
          pbVar3 = local_40;
          bVar2 = *local_14;
          pbVar5 = local_14 + 1;
          if (bVar2 == 0) break;
          if (bVar2 == 1) {
            local_5c = (uint)*pbVar5;
            local_14 = local_14 + 2;
            local_40 = local_40 + local_5c;
          }
          else {
            iVar4 = (int)(uint)bVar2 >> 1;
            local_68 = 0xff;
            bVar11 = (bVar2 & 1) == 0;
            if (bVar11) {
              local_68 = *pbVar5;
            }
            if ((param_1[2] <= (int)local_18) && (bVar8 != 0)) {
              local_74 = local_40 + iVar4 + -1;
              local_60 = pbVar5;
              if (local_40 < local_44) {
                local_60 = pbVar5 + ((int)local_44 - (int)local_40);
                local_40 = local_44;
              }
              if (local_34 < local_74) {
                local_74 = local_34;
              }
              if (bVar8 == 4) {
                if (bVar11) {
                  for (; local_40 <= local_74; local_40 = local_40 + 1) {
                    *local_40 = local_68;
                  }
                }
                else {
                  for (; local_40 <= local_74; local_40 = local_40 + 1) {
                    *local_40 = *local_60;
                    local_60 = local_60 + 1;
                  }
                }
              }
              else {
                uVar7 = (int)local_40 - (int)local_44 & 3;
                if ((bVar1 & 2) != 0) {
                  uVar10 = uVar6 - uVar7 & 1;
                  local_80 = local_40 + uVar10;
                  local_7c = local_60 + uVar10;
                  if (bVar11) {
                    for (; local_80 <= local_74; local_80 = local_80 + 2) {
                      *local_80 = local_68;
                    }
                  }
                  else {
                    for (; local_80 <= local_74; local_80 = local_80 + 2) {
                      *local_80 = *local_7c;
                      local_7c = local_7c + 2;
                    }
                  }
                }
                if ((bVar1 & 1) != 0) {
                  uVar7 = (uVar6 + (bVar8 == 3)) - uVar7 & 3;
                  local_8c = local_40 + uVar7;
                  local_88 = local_60 + uVar7;
                  if (bVar11) {
                    for (; local_8c <= local_74; local_8c = local_8c + 4) {
                      *local_8c = local_68;
                    }
                  }
                  else {
                    for (; local_8c <= local_74; local_8c = local_8c + 4) {
                      *local_8c = *local_88;
                      local_88 = local_88 + 4;
                    }
                  }
                }
              }
              local_40 = pbVar3 + iVar4;
            }
            if (bVar11) {
              local_14 = local_14 + 2;
            }
            else {
              local_14 = pbVar5 + iVar4;
            }
          }
        }
        local_44 = local_44 + iVar9;
        local_34 = local_34 + iVar9;
        local_8 = local_8 + iVar9;
        local_14 = pbVar5;
      }
    }
    else {
      thunk_FUN_00404770(param_1,param_2,param_3,param_4,param_5);
    }
  }
  return;
}
```

---

---

## FUN_00411033 — 0x411033

- Classification : internal
- Corps : `0x411033–0x41137b`
- État : pseudocode obtenu
- Evidence : `ev_4769e45c7554057d0b5cf7d248d13e8d6e38531c5790912e34fd805309e6d3d3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401154` — `thunk_FUN_00414b91`
- `0x402306` — `thunk_FUN_004106dd`
- `0x472e90` — `_strlen`

### Chaînes référencées

- `0x49b514` — "string_length <= MAX_HAZE_STRING_LEN"
- `0x49b53c` — "C:\\float\\src\\color.cpp"

### Pseudocode Ghidra

```c
void FUN_00411033(int *param_1,int param_2,char *param_3,int param_4,int param_5,undefined4 param_6,
                 undefined4 param_7)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  size_t sVar5;
  int iVar6;
  byte *local_1e0;
  char *local_1dc;
  byte *local_1d4;
  int local_1d0;
  byte *local_1c8;
  int local_1c4;
  byte *local_1b8;
  int aiStack_1b0 [100];
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  byte *local_8;
  
  local_18 = thunk_FUN_004106dd(0,param_7);
  iVar4 = thunk_FUN_004106dd(param_6,param_7);
  sVar5 = _strlen(param_3);
  if (100 < (int)sVar5) {
    thunk_FUN_00414b91(s_C__float_src_color_cpp_0049b53c,0x1eb,
                       s_string_length_<__MAX_HAZE_STRING_0049b514,param_3);
  }
  local_14 = param_2;
  iVar1 = *(int *)(param_2 + 8);
  for (local_1c4 = 0; local_1c4 < (int)sVar5; local_1c4 = local_1c4 + 1) {
    aiStack_1b0[local_1c4] =
         local_14 + *(int *)(local_14 + 0x10 + (uint)(byte)param_3[local_1c4] * 4);
  }
  iVar6 = *(int *)(*param_1 + 4) + 1;
  local_c = *(int *)*param_1 + param_5 * iVar6;
  local_1d4 = (byte *)(local_c + param_1[1]);
  local_1b8 = (byte *)(local_c + param_1[3]);
  local_1c8 = local_1d4 + param_4;
  local_8 = local_1c8;
  local_10 = param_1[2] + param_5;
  local_1c = param_1[2] + param_5 + -1 + iVar1;
  if (param_1[4] < local_1c) {
    local_1c = param_1[4];
  }
  local_1d0 = 0;
  for (; pbVar2 = local_1c8, local_10 <= local_1c; local_10 = local_10 + 1) {
    if (param_1[2] <= local_10) {
      for (local_1c4 = 0; pbVar3 = local_1c8, local_1c4 < (int)sVar5; local_1c4 = local_1c4 + 1) {
        local_20 = *(int *)aiStack_1b0[local_1c4];
        local_1dc = (char *)(aiStack_1b0[local_1c4] + 4 + local_1d0 * local_20);
        local_1e0 = local_1c8 + local_20 + -1;
        if (local_1c8 < local_1d4) {
          local_1dc = local_1dc + ((int)local_1d4 - (int)local_1c8);
          local_1c8 = local_1d4;
        }
        if (local_1b8 < local_1e0) {
          local_1e0 = local_1b8;
        }
        for (; local_1c8 <= local_1e0; local_1c8 = local_1c8 + 1) {
          if (*local_1dc != -1) {
            if (*local_1dc == '\0') {
              *local_1c8 = *(byte *)(local_18 + (uint)*local_1c8);
            }
            else {
              *local_1c8 = *(byte *)(iVar4 + (uint)*local_1c8);
            }
          }
          local_1dc = local_1dc + 1;
        }
        local_1c8 = pbVar3 + local_20;
      }
    }
    local_1d4 = local_1d4 + iVar6;
    local_1b8 = local_1b8 + iVar6;
    local_1c8 = pbVar2 + iVar6;
    local_8 = local_1c8;
    local_1d0 = local_1d0 + 1;
  }
  return;
}
```

---

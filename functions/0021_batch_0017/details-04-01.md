# 0021_batch_0017 — détails (1/2)

## FUN_00482280 — 0x482280

- Classification : internal
- Corps : `0x482280–0x4823f8`
- État : pseudocode obtenu
- Evidence : `ev_64c9ae2721f43977bd3b82820dbe24f6e8db417c900b663575f316de780f255b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00482280(uint param_1)

{
  uint uVar1;
  uint local_8;
  
  local_8 = 0;
  if ((param_1 & 1) != 0) {
    local_8 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    local_8 = local_8 | 8;
  }
  if ((param_1 & 8) != 0) {
    local_8 = local_8 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    local_8 = local_8 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    local_8 = local_8 | 1;
  }
  if ((param_1 & 2) != 0) {
    local_8 = local_8 | 0x80000;
  }
  uVar1 = param_1 & 0xc00;
  if (uVar1 < 0x401) {
    if (uVar1 == 0x400) {
      local_8 = local_8 | 0x100;
    }
  }
  else if (uVar1 == 0x800) {
    local_8 = local_8 | 0x200;
  }
  else if (uVar1 == 0xc00) {
    local_8 = local_8 | 0x300;
  }
  if ((param_1 & 0x300) == 0) {
    local_8 = local_8 | 0x20000;
  }
  else if ((param_1 & 0x300) == 0x200) {
    local_8 = local_8 | 0x10000;
  }
  if ((param_1 & 0x1000) != 0) {
    local_8 = local_8 | 0x40000;
  }
  return local_8;
}
```

---

---

## FUN_00482400 — 0x482400

- Classification : internal
- Corps : `0x482400–0x482559`
- État : pseudocode obtenu
- Evidence : `ev_e6d79d2b2245f097782afcdd962b20da9829e5ef0285efee76b7490d38bd0a76`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00482400(uint param_1)

{
  uint uVar1;
  ushort local_8;
  
  local_8 = (ushort)((param_1 & 0x10) != 0);
  if ((param_1 & 8) != 0) {
    local_8 = local_8 | 4;
  }
  if ((param_1 & 4) != 0) {
    local_8 = local_8 | 8;
  }
  if ((param_1 & 2) != 0) {
    local_8 = local_8 | 0x10;
  }
  if ((param_1 & 1) != 0) {
    local_8 = local_8 | 0x20;
  }
  if ((param_1 & 0x80000) != 0) {
    local_8 = local_8 | 2;
  }
  uVar1 = param_1 & 0x300;
  if (uVar1 < 0x101) {
    if (uVar1 == 0x100) {
      local_8 = local_8 | 0x400;
    }
  }
  else if (uVar1 == 0x200) {
    local_8 = local_8 | 0x800;
  }
  else if (uVar1 == 0x300) {
    local_8 = local_8 | 0xc00;
  }
  if ((param_1 & 0x30000) == 0) {
    local_8 = local_8 | 0x300;
  }
  else if ((param_1 & 0x30000) == 0x10000) {
    local_8 = local_8 | 0x200;
  }
  if ((param_1 & 0x40000) != 0) {
    local_8 = local_8 | 0x1000;
  }
  return CONCAT22((short)((param_1 & 0x40000) >> 0x10),local_8);
}
```

---

---

## FUN_00482560 — 0x482560

- Classification : internal
- Corps : `0x482560–0x482606`
- État : pseudocode obtenu
- Evidence : `ev_5ed516065c25e1820fc8e1eaa7941ae2d9524cad8b13f54df84e3c8d28fe9742`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00482560(uint param_1)

{
  undefined4 local_8;
  
  local_8 = 0;
  if ((param_1 & 1) != 0) {
    local_8 = 0x10;
  }
  if ((param_1 & 4) != 0) {
    local_8 = local_8 | 8;
  }
  if ((param_1 & 8) != 0) {
    local_8 = local_8 | 4;
  }
  if ((param_1 & 0x10) != 0) {
    local_8 = local_8 | 2;
  }
  if ((param_1 & 0x20) != 0) {
    local_8 = local_8 | 1;
  }
  if ((param_1 & 2) != 0) {
    local_8 = local_8 | 0x80000;
  }
  return local_8;
}
```

---

---

## FUN_00482610 — 0x482610

- Classification : internal
- Corps : `0x482610–0x48261a`
- État : pseudocode obtenu
- Evidence : `ev_238122b698d422be2471473e4dd4f3f40ca8a7bdc533d3a5cd4b3155e3533f04`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00482610(int param_1)

{
  return param_1 + 0x20;
}
```

---

---

## FUN_00482620 — 0x482620

- Classification : internal
- Corps : `0x482620–0x482748`
- État : pseudocode obtenu
- Evidence : `ev_2db989cd95d78bf631a6da107154f29bce99ed56db6244c81cbdb016a5b4c756`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`
- `0x480050` — `FUN_00480050`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00482620(uint param_1)

{
  int iVar1;
  uint local_14;
  uint local_10;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  undefined4 local_8;
  
  if (DAT_006325e8 == 0) {
    if ((0x40 < (int)param_1) && ((int)param_1 < 0x5b)) {
      param_1 = param_1 + 0x20;
    }
  }
  else {
    if ((int)param_1 < 0x100) {
      if (DAT_004a87f4 < 2) {
        local_14 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 1;
      }
      else {
        local_14 = FUN_0047f2b0(param_1,1);
      }
      if (local_14 == 0) {
        return param_1;
      }
    }
    if ((*(ushort *)(PTR_DAT_004a85e8 + ((int)param_1 >> 8 & 0xffU) * 2) & 0x8000) == 0) {
      local_c = (undefined1)param_1;
      local_b = 0;
      local_8 = 1;
    }
    else {
      local_c = (undefined1)(param_1 >> 8);
      local_b = (undefined1)param_1;
      local_a = 0;
      local_8 = 2;
    }
    iVar1 = FUN_00480050(DAT_006325e8,0x100,&local_c,local_8,&local_10,3,0);
    if (iVar1 != 0) {
      if (iVar1 == 1) {
        param_1 = local_10 & 0xff;
      }
      else {
        param_1 = local_10 & 0xff | (local_10 >> 8 & 0xff) << 8;
      }
    }
  }
  return param_1;
}
```

---

---

## FUN_00482750 — 0x482750

- Classification : internal
- Corps : `0x482750–0x4827d3`
- État : pseudocode obtenu
- Evidence : `ev_db828f2a24b922faa2d7c5d35b0e32000fce69b772793b9b39eb01eb4bb1a8a4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00482750(int param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  int local_10;
  
  local_10 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  bVar1 = (byte)(param_2 >> 0x1f);
  uVar2 = *(uint *)(param_1 + local_10 * 4) &
          ~(-1 << (0x1f - ((((byte)param_2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1) & 0x1f));
  while( true ) {
    if (uVar2 != 0) {
      return 0;
    }
    local_10 = local_10 + 1;
    if (2 < local_10) break;
    uVar2 = *(uint *)(param_1 + local_10 * 4);
  }
  return 1;
}
```

---

---

## FUN_004827e0 — 0x4827e0

- Classification : internal
- Corps : `0x4827e0–0x482887`
- État : pseudocode obtenu
- Evidence : `ev_7275e1717c807b5c5d106a86f0af29003aac6ee80e0b773a819574957ca6e1a8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x488040` — `___addl`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004827e0(int param_1,int param_2)

{
  byte bVar1;
  undefined4 local_14;
  undefined4 local_10;
  
  local_10 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  bVar1 = (byte)(param_2 >> 0x1f);
  local_14 = ___addl(*(undefined4 *)(param_1 + local_10 * 4),
                     1 << (0x1f - ((((byte)param_2 ^ bVar1) - bVar1 & 0x1f ^ bVar1) - bVar1) & 0x1f)
                     ,param_1 + local_10 * 4);
  while ((local_10 = local_10 + -1, -1 < local_10 && (local_14 != 0))) {
    local_14 = ___addl(*(undefined4 *)(param_1 + local_10 * 4),1,param_1 + local_10 * 4);
  }
  return local_14;
}
```

---

---

## FUN_00482890 — 0x482890

- Classification : internal
- Corps : `0x482890–0x482969`
- État : pseudocode obtenu
- Evidence : `ev_6252cf20f9b6945ce5cd4d4424afe3120f60070bae33a3701d2b07d5f83cfa55`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482750` — `FUN_00482750`
- `0x4827e0` — `FUN_004827e0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00482890(int param_1,int param_2)

{
  int iVar1;
  byte bVar2;
  undefined4 local_1c;
  undefined4 local_14;
  
  local_1c = 0;
  local_14 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  bVar2 = (byte)(param_2 >> 0x1f);
  bVar2 = 0x1f - ((((byte)param_2 ^ bVar2) - bVar2 & 0x1f ^ bVar2) - bVar2);
  if ((*(uint *)(param_1 + local_14 * 4) & 1 << (bVar2 & 0x1f)) != 0) {
    iVar1 = FUN_00482750(param_1,param_2 + 1);
    if (iVar1 == 0) {
      local_1c = FUN_004827e0(param_1,param_2 + -1);
    }
  }
  *(uint *)(param_1 + local_14 * 4) = *(uint *)(param_1 + local_14 * 4) & -1 << (bVar2 & 0x1f);
  while (local_14 = local_14 + 1, local_14 < 3) {
    *(undefined4 *)(param_1 + local_14 * 4) = 0;
  }
  return local_1c;
}
```

---

## __CopyMan — 0x482970

- Classification : internal
- Corps : `0x482970–0x4829bb`
- État : pseudocode obtenu
- Evidence : `ev_b16f737d771c0437e62a8f01855bb5018960fcd57ee56463f275844f7676ac1a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __CopyMan
   
   Library: Visual Studio */

void __CopyMan(undefined4 *param_1,undefined4 *param_2)

{
  int local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  local_8 = param_2;
  local_c = param_1;
  for (local_10 = 0; local_10 < 3; local_10 = local_10 + 1) {
    *local_c = *local_8;
    local_c = local_c + 1;
    local_8 = local_8 + 1;
  }
  return;
}
```

---

## __FillZeroMan — 0x4829c0

- Classification : internal
- Corps : `0x4829c0–0x4829ee`
- État : pseudocode obtenu
- Evidence : `ev_6a41fe05e0ad4a0593cfcfe3449942e5ddd1e4e6d130d22cf4cddddbb6fc35e2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __FillZeroMan
   
   Library: Visual Studio */

void __FillZeroMan(int param_1)

{
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 3; local_8 = local_8 + 1) {
    *(undefined4 *)(param_1 + local_8 * 4) = 0;
  }
  return;
}
```

---

## __IsZeroMan — 0x4829f0

- Classification : internal
- Corps : `0x4829f0–0x482a26`
- État : pseudocode obtenu
- Evidence : `ev_91c77170a5ecbfe3076f8770eac46578b9c46c7d4036692655e04684a70dc0a9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __IsZeroMan
   
   Library: Visual Studio */

undefined4 __IsZeroMan(int param_1)

{
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (2 < local_8) {
      return 1;
    }
    if (*(int *)(param_1 + local_8 * 4) != 0) break;
    local_8 = local_8 + 1;
  }
  return 0;
}
```

---

---

## FUN_00482a30 — 0x482a30

- Classification : internal
- Corps : `0x482a30–0x482b1b`
- État : pseudocode obtenu
- Evidence : `ev_847558cfb2a9c4b1c025a9bd46ef1472365c772e6992b576b19b4aadc694ef87`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00482a30(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  byte bVar3;
  undefined4 local_10;
  undefined4 local_c;
  
  iVar2 = (int)(param_2 + (param_2 >> 0x1f & 0x1fU)) >> 5;
  bVar3 = (byte)(param_2 >> 0x1f);
  bVar3 = (((byte)param_2 ^ bVar3) - bVar3 & 0x1f ^ bVar3) - bVar3;
  local_c = 0;
  for (local_10 = 0; local_10 < 3; local_10 = local_10 + 1) {
    uVar1 = *(uint *)(param_1 + local_10 * 4);
    *(uint *)(param_1 + local_10 * 4) = *(uint *)(param_1 + local_10 * 4) >> (bVar3 & 0x1f);
    *(uint *)(param_1 + local_10 * 4) = *(uint *)(param_1 + local_10 * 4) | local_c;
    local_c = (uVar1 & ~(-1 << (bVar3 & 0x1f))) << (0x20 - bVar3 & 0x1f);
  }
  for (local_10 = 2; -1 < local_10; local_10 = local_10 + -1) {
    if (local_10 < iVar2) {
      *(undefined4 *)(param_1 + local_10 * 4) = 0;
    }
    else {
      *(undefined4 *)(param_1 + local_10 * 4) = *(undefined4 *)(param_1 + (local_10 - iVar2) * 4);
    }
  }
  return;
}
```

---

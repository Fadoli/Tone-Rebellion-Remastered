# 0020_batch_0016 — détails (3/3)

## FUN_0047dfa0 — 0x47dfa0

- Classification : internal
- Corps : `0x47dfa0–0x47e03f`
- État : pseudocode obtenu
- Evidence : `ev_a547ab3666539239bd761c55bb7f75cae27c321383e5667564286ce180f11d28`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x27` — `KERNEL32.DLL::HeapReAlloc`
- `0x47e790` — `FUN_0047e790`
- `0x47ef00` — `FUN_0047ef00`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
LPVOID FUN_0047dfa0(LPVOID param_1,uint param_2)

{
  int iVar1;
  undefined4 local_14;
  int local_10;
  LPVOID local_c;
  undefined4 local_8;
  
  if (param_2 < 0xffffffe1) {
    if (param_2 == 0) {
      param_2 = 0x10;
    }
    else {
      param_2 = param_2 + 0xf & 0xfffffff0;
    }
    local_10 = FUN_0047e790(param_1,&local_14,&local_8);
    if (local_10 == 0) {
      local_c = HeapReAlloc(DAT_00633d04,0x10,param_1,param_2);
    }
    else {
      local_c = (LPVOID)0x0;
      if ((param_2 <= DAT_004a85e4) &&
         (iVar1 = FUN_0047ef00(local_14,local_8,local_10,param_2 >> 4), iVar1 != 0)) {
        local_c = param_1;
      }
    }
  }
  else {
    local_c = (LPVOID)0x0;
  }
  return local_c;
}
```

---

---

## FUN_0047e040 — 0x47e040

- Classification : internal
- Corps : `0x47e040–0x47e21a`
- État : pseudocode obtenu
- Evidence : `ev_621587b3ba5057b075ed33f819099c3c7f0f888beb6f01e038faeac7e58cc978`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x27` — `KERNEL32.DLL::HeapReAlloc`
- `EXTERNAL:0x28` — `KERNEL32.DLL::HeapAlloc`
- `0x4734a0` — `FUN_004734a0`
- `0x47de70` — `__callnewh`
- `0x47dea0` — `FUN_0047dea0`
- `0x47e220` — `FUN_0047e220`
- `0x47e790` — `FUN_0047e790`
- `0x47e820` — `FUN_0047e820`
- `0x47e890` — `FUN_0047e890`
- `0x47ef00` — `FUN_0047ef00`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
LPVOID FUN_0047e040(LPVOID param_1,uint param_2)

{
  LPVOID pvVar1;
  int iVar2;
  uint local_20;
  uint local_1c;
  undefined4 local_18;
  uint local_14;
  byte *local_10;
  LPVOID local_c;
  undefined4 local_8;
  
  if (param_1 == (LPVOID)0x0) {
    pvVar1 = (LPVOID)FUN_0047dea0(param_2);
  }
  else if (param_2 == 0) {
    FUN_0047e220(param_1);
    pvVar1 = (LPVOID)0x0;
  }
  else {
    if (param_2 < 0xffffffe1) {
      if (param_2 == 0) {
        param_2 = 0x10;
      }
      else {
        param_2 = param_2 + 0xf & 0xfffffff0;
      }
    }
    do {
      local_c = (LPVOID)0x0;
      if (param_2 < 0xffffffe1) {
        local_10 = (byte *)FUN_0047e790(param_1,&local_18,&local_8);
        if (local_10 == (byte *)0x0) {
          local_c = HeapReAlloc(DAT_00633d04,0,param_1,param_2);
        }
        else {
          if (param_2 < DAT_004a85e4) {
            iVar2 = FUN_0047ef00(local_18,local_8,local_10,param_2 >> 4);
            if (iVar2 == 0) {
              local_c = (LPVOID)FUN_0047e890(param_2 >> 4);
              if (local_c != (LPVOID)0x0) {
                local_14 = (uint)*local_10 << 4;
                local_1c = local_14;
                if (param_2 <= local_14) {
                  local_1c = param_2;
                }
                FUN_004734a0(local_c,param_1,local_1c);
                FUN_0047e820(local_18,local_8,local_10);
              }
            }
            else {
              local_c = param_1;
            }
          }
          if ((local_c == (LPVOID)0x0) &&
             (local_c = HeapAlloc(DAT_00633d04,0,param_2), local_c != (LPVOID)0x0)) {
            local_14 = (uint)*local_10 << 4;
            local_20 = local_14;
            if (param_2 <= local_14) {
              local_20 = param_2;
            }
            FUN_004734a0(local_c,param_1,local_20);
            FUN_0047e820(local_18,local_8,local_10);
          }
        }
      }
      if (local_c != (LPVOID)0x0) {
        return local_c;
      }
      if (DAT_006325b0 == 0) {
        return (LPVOID)0x0;
      }
      iVar2 = __callnewh(param_2);
    } while (iVar2 != 0);
    pvVar1 = (LPVOID)0x0;
  }
  return pvVar1;
}
```

---

---

## FUN_0047e220 — 0x47e220

- Classification : internal
- Corps : `0x47e220–0x47e277`
- État : pseudocode obtenu
- Evidence : `ev_fe82ae7785bfd95f434fa0ba0e107eaee58239e295656792efdfdd65a7386811`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x26` — `KERNEL32.DLL::HeapFree`
- `0x47e790` — `FUN_0047e790`
- `0x47e820` — `FUN_0047e820`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047e220(LPVOID param_1)

{
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  
  if (param_1 != (LPVOID)0x0) {
    local_c = FUN_0047e790(param_1,&local_10,&local_8);
    if (local_c == 0) {
      HeapFree(DAT_00633d04,0,param_1);
    }
    else {
      FUN_0047e820(local_10,local_8,local_c);
    }
  }
  return;
}
```

---

---

## FUN_0047e280 — 0x47e280

- Classification : internal
- Corps : `0x47e280–0x47e2dd`
- État : pseudocode obtenu
- Evidence : `ev_9f3a823930b40996363f792c56496ab76f089739ec6e6b5ff3011a62ccb9d52e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `EXTERNAL:0xf` — `KERNEL32.DLL::HeapValidate`
- `0x47f070` — `FUN_0047f070`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0047e280(void)

{
  int iVar1;
  BOOL BVar2;
  DWORD DVar3;
  undefined4 local_8;
  
  local_8 = 0xfffffffe;
  iVar1 = FUN_0047f070();
  if (iVar1 < 0) {
    local_8 = 0xfffffffc;
  }
  BVar2 = HeapValidate(DAT_00633d04,0,(LPCVOID)0x0);
  if (BVar2 == 0) {
    DVar3 = GetLastError();
    if (DVar3 == 0x78) {
      DAT_00632520 = 0x78;
      _DAT_0063251c = 0x28;
    }
    else {
      local_8 = 0xfffffffc;
    }
  }
  return local_8;
}
```

---

---

## FUN_0047e2e0 — 0x47e2e0

- Classification : internal
- Corps : `0x47e2e0–0x47e2e9`
- État : pseudocode obtenu
- Evidence : `ev_34c85996e6383f8e15a4d2eab92640d3db7a7e028a1acc6d7f7fd598e0adc5c9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47e280` — `FUN_0047e280`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047e2e0(void)

{
  FUN_0047e280();
  return;
}
```

---

# 0021_batch_0017 — détails (3/3)

## FUN_00482170 — 0x482170

- Classification : internal
- Corps : `0x482170–0x48218e`
- État : pseudocode obtenu
- Evidence : `ev_74e8d568f28cdc971932c1c44dee143004f7c8b6273135ca237f41a4d60280ae`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482560` — `FUN_00482560`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00482170(void)

{
  FUN_00482560();
  return;
}
```

---

---

## FUN_00482190 — 0x482190

- Classification : internal
- Corps : `0x482190–0x4821af`
- État : pseudocode obtenu
- Evidence : `ev_235de416c2dc2beb8180bbbff878e422ad8221ed97858b13087d0a554171426c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482560` — `FUN_00482560`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00482190(void)

{
  FUN_00482560();
  return;
}
```

---

---

## FUN_004821b0 — 0x4821b0

- Classification : internal
- Corps : `0x4821b0–0x4821fe`
- État : pseudocode obtenu
- Evidence : `ev_befc470f8d91a44045cba47140808d7f0e46e7a158a318486793cf2bf8d83512`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482280` — `FUN_00482280`
- `0x482400` — `FUN_00482400`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_004821b0(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = FUN_00482280();
  uVar1 = param_1 & param_2 | uVar1 & ~param_2;
  FUN_00482400(uVar1);
  return uVar1;
}
```

---

## __controlfp — 0x482200

- Classification : internal
- Corps : `0x482200–0x482219`
- État : pseudocode obtenu
- Evidence : `ev_fbae25ac6350f6bbd7f50f5c210b209fd36e0f0a645beb1eb04e1c35c8d46ab7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4821b0` — `FUN_004821b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __controlfp
   
   Library: Visual Studio 2003 Debug */

uint __cdecl __controlfp(uint _NewValue,uint _Mask)

{
  uint uVar1;
  
  uVar1 = FUN_004821b0(_NewValue,_Mask & 0xfff7ffff);
  return uVar1;
}
```

---

---

## FUN_00482220 — 0x482220

- Classification : internal
- Corps : `0x482220–0x482275`
- État : pseudocode obtenu
- Evidence : `ev_c133961885c50b991e211335309677e7c0f0d326d5b0c326987ff151127fdbe3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4786c0` — `__setdefaultprecision`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00482220(void)

{
  int iVar1;
  
  iVar1 = DAT_0063262c;
  __setdefaultprecision();
  if ((iVar1 != 0) && ((**(uint **)(iVar1 + 4) & 0x10008) != 0)) {
    iVar1 = *(int *)(iVar1 + 4);
    *(undefined4 *)(iVar1 + 0x20) = 0;
    *(undefined4 *)(iVar1 + 0x24) = 0xffff;
  }
  return;
}
```

---

# 0021_batch_0017 — détails (3/3)

## FUN_00480b85 — 0x480b85

- Classification : internal
- Corps : `0x480b85–0x480b9f`
- État : pseudocode obtenu
- Evidence : `ev_47fbd8d53e54f74147e56ea96af689e3b255ffab951693cc6b62a4bb3582da36`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4733f2` — `__local_unwind2`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480b85(int param_1)

{
  __local_unwind2(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x1c));
  return;
}
```

---

## __XcptFilter — 0x480ba0

- Classification : internal
- Corps : `0x480ba0–0x480d48`
- État : pseudocode obtenu
- Evidence : `ev_94ab6e588a8963c778ea8c0e1169e81bed1a791f70096a7ee390cff3f333da88`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x1f` — `KERNEL32.DLL::UnhandledExceptionFilter`
- `0x480d50` — `xcptlookup`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __XcptFilter
   
   Library: Visual Studio 2003 Debug */

int __cdecl __XcptFilter(ulong _ExceptionNum,_EXCEPTION_POINTERS *_ExceptionPtr)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  int local_14;
  
  piVar4 = (int *)xcptlookup(_ExceptionNum);
  uVar3 = DAT_0063262c;
  if ((piVar4 == (int *)0x0) || (piVar4[2] == 0)) {
    iVar5 = UnhandledExceptionFilter(_ExceptionPtr);
  }
  else if (piVar4[2] == 5) {
    piVar4[2] = 0;
    iVar5 = 1;
  }
  else if (piVar4[2] == 1) {
    iVar5 = -1;
    DAT_0063262c = (_EXCEPTION_POINTERS *)uVar3;
  }
  else {
    pcVar1 = (code *)piVar4[2];
    DAT_0063262c = _ExceptionPtr;
    if (piVar4[1] == 8) {
      for (local_14 = DAT_004a8928; uVar2 = DAT_004a8934, local_14 < DAT_004a8928 + _DAT_004a892c;
          local_14 = local_14 + 1) {
        *(undefined4 *)(local_14 * 0xc + 0x4a88b8) = 0;
      }
      if (*piVar4 == -0x3fffff72) {
        DAT_004a8934 = 0x83;
      }
      else if (*piVar4 == -0x3fffff70) {
        DAT_004a8934 = 0x81;
      }
      else if (*piVar4 == -0x3fffff6f) {
        DAT_004a8934 = 0x84;
      }
      else if (*piVar4 == -0x3fffff6d) {
        DAT_004a8934 = 0x85;
      }
      else if (*piVar4 == -0x3fffff73) {
        DAT_004a8934 = 0x82;
      }
      else if (*piVar4 == -0x3fffff71) {
        DAT_004a8934 = 0x86;
      }
      else if (*piVar4 == -0x3fffff6e) {
        DAT_004a8934 = 0x8a;
      }
      (*pcVar1)(8,DAT_004a8934);
      DAT_004a8934 = uVar2;
    }
    else {
      piVar4[2] = 0;
      (*pcVar1)(piVar4[1]);
    }
    iVar5 = -1;
    DAT_0063262c = (_EXCEPTION_POINTERS *)uVar3;
  }
  return iVar5;
}
```

---

## xcptlookup — 0x480d50

- Classification : internal
- Corps : `0x480d50–0x480daa`
- État : pseudocode obtenu
- Evidence : `ev_95e088a4bde575fc318b260e6e6cd6431cf1e03d27a35c1f69c1e374ddaf3778`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _xcptlookup
   
   Library: Visual Studio 2003 Debug */

int * __cdecl xcptlookup(int param_1)

{
  int *local_8;
  
  local_8 = &DAT_004a88b0;
  do {
    if (*local_8 == param_1) break;
    local_8 = local_8 + 3;
  } while (local_8 < &DAT_004a88b0 + DAT_004a8930 * 3);
  if ((&DAT_004a88b0 + DAT_004a8930 * 3 <= local_8) || (*local_8 != param_1)) {
    local_8 = (int *)0x0;
  }
  return local_8;
}
```

---

---

## FUN_00480db0 — 0x480db0

- Classification : internal
- Corps : `0x480db0–0x480dc4`
- État : pseudocode obtenu
- Evidence : `ev_b01febd9cf443bf7691751db24ac0af75916dd08c7e450738ec20f9fa4a574d4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480db0(undefined4 param_1)

{
  FUN_00480f30(param_1,0,1);
  return;
}
```

---

---

## FUN_00480dd0 — 0x480dd0

- Classification : internal
- Corps : `0x480dd0–0x480de4`
- État : pseudocode obtenu
- Evidence : `ev_08ae5d20c5bcbd20378ef83aef3fddf78d501a66add4dd792fabf6194f8c24d3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480dd0(undefined4 param_1)

{
  FUN_00480f30(param_1,0,3);
  return;
}
```

---

---

## FUN_00480df0 — 0x480df0

- Classification : internal
- Corps : `0x480df0–0x480e04`
- État : pseudocode obtenu
- Evidence : `ev_8d43fc2a33306e97db6791bcd6423c4241a7e5b4d1a046de6163a38d57bc219e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480df0(undefined4 param_1)

{
  FUN_00480f30(param_1,0,2);
  return;
}
```

---

---

## FUN_00480e10 — 0x480e10

- Classification : internal
- Corps : `0x480e10–0x480e27`
- État : pseudocode obtenu
- Evidence : `ev_fd3d58cfab0750613ca2560e22b0817592418192f48cb1aeace189cf926b4513`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480e10(undefined4 param_1)

{
  FUN_00480f30(param_1,0x107,1);
  return;
}
```

---

---

## FUN_00480e30 — 0x480e30

- Classification : internal
- Corps : `0x480e30–0x480e47`
- État : pseudocode obtenu
- Evidence : `ev_f90cc4695fd1ec76863ee94725ea916603faf78026ba51e4896b3b197c1c0998`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480e30(undefined4 param_1)

{
  FUN_00480f30(param_1,0x103,1);
  return;
}
```

---

---

## FUN_00480e50 — 0x480e50

- Classification : internal
- Corps : `0x480e50–0x480e67`
- État : pseudocode obtenu
- Evidence : `ev_0ef373180e7912e34a888102260dbf1e653fa2b9167b8430dfab1b8dc4ce161b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480e50(undefined4 param_1)

{
  FUN_00480f30(param_1,0x117,3);
  return;
}
```

---

---

## FUN_00480e70 — 0x480e70

- Classification : internal
- Corps : `0x480e70–0x480e87`
- État : pseudocode obtenu
- Evidence : `ev_cab2c0577594b53912b4af0a0772eaf7766063aaa9878ad2a430e55c1a4ed23f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480f30` — `FUN_00480f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00480e70(undefined4 param_1)

{
  FUN_00480f30(param_1,0x157,3);
  return;
}
```

---

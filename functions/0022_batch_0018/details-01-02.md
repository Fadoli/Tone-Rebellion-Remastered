# 0022_batch_0018 — détails (2/3)

## FUN_00483d10 — 0x483d10

- Classification : internal
- Corps : `0x483d10–0x483e02`
- État : pseudocode obtenu
- Evidence : `ev_743dd97095abc6efe430001673ff2647cbcc10a7e8359c5bce0b5f1daf64f548`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x483d42 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x483d6c with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x478ef0` — `FUN_00478ef0`
- `0x479170` — `FUN_00479170`
- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x495197` — "`format != NULL"
- `0x4951b4` — "string != NULL"
- `0x496208` — "vsprintf.c"
- `0x496208` — "vsprintf.c"

### Pseudocode Ghidra

```c
undefined4 FUN_00483d10(undefined1 *param_1,int param_2,int param_3,undefined4 param_4)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  if ((param_1 == (undefined1 *)0x0) &&
     (iVar2 = FUN_0047a120(2,"vsprintf.c",0x5a,0,"string != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_3 == 0) && (iVar2 = FUN_0047a120(2,"vsprintf.c",0x5b,0,"format != NULL"), iVar2 == 1))
  {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  local_18 = 0x42;
  local_1c = param_1;
  local_24 = param_1;
  local_20 = param_2;
  uVar3 = FUN_00479170(&local_24,param_3,param_4);
  local_20 = local_20 + -1;
  if (local_20 < 0) {
    FUN_00478ef0(0,&local_24);
  }
  else {
    *local_24 = 0;
  }
  return uVar3;
}
```

---

---

## FUN_00483e10 — 0x483e10

- Classification : internal
- Corps : `0x483e10–0x483f79`
- État : pseudocode obtenu
- Evidence : `ev_7f043b6e53afe7b7067bacae2a59de42fa157659a849dad5d2af636f1cccd84f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `EXTERNAL:0x17` — `KERNEL32.DLL::SetConsoleCtrlHandler`
- `0x4841e0` — `siglookup`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00483e10(int param_1,int param_2)

{
  int iVar1;
  BOOL BVar2;
  int local_c;
  undefined4 *local_8;
  
  if ((param_2 != 4) && (param_2 != 3)) {
    if ((param_1 == 2) || (((param_1 == 0x15 || (param_1 == 0x16)) || (param_1 == 0xf)))) {
      if (((param_1 == 2) || (param_1 == 0x15)) && (DAT_006328ac == 0)) {
        BVar2 = SetConsoleCtrlHandler(ctrlevent_capture,1);
        if (BVar2 != 1) {
          DAT_00632520 = GetLastError();
          _DAT_0063251c = 0x16;
          return -1;
        }
        DAT_006328ac = 1;
      }
      switch(param_1) {
      case 2:
        local_c = DAT_0063289c;
        DAT_0063289c = param_2;
        break;
      case 0xf:
        local_c = DAT_006328a8;
        DAT_006328a8 = param_2;
        break;
      case 0x15:
        local_c = DAT_006328a0;
        DAT_006328a0 = param_2;
        break;
      case 0x16:
        local_c = DAT_006328a4;
        DAT_006328a4 = param_2;
      }
      return local_c;
    }
    if ((((param_1 == 8) || (param_1 == 4)) || (param_1 == 0xb)) &&
       (local_8 = (undefined4 *)siglookup(param_1), local_8 != (undefined4 *)0x0)) {
      iVar1 = local_8[2];
      do {
        if (local_8[1] != param_1) {
          return iVar1;
        }
        local_8[2] = param_2;
        local_8 = local_8 + 3;
      } while (local_8 < &DAT_004a88b0 + DAT_004a8930 * 3);
      return iVar1;
    }
  }
  _DAT_0063251c = 0x16;
  return -1;
}
```

---

## ctrlevent_capture — 0x483fb0

- Classification : internal
- Corps : `0x483fb0–0x484017`
- État : pseudocode obtenu
- Evidence : `ev_04bda82b82959ada53f592d39441d46c041deef965926a74de98438e7261b92d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _ctrlevent_capture@4
   
   Library: Visual Studio 2003 Debug
   __stdcall ctrlevent_capture,4 */

undefined4 ctrlevent_capture(int param_1)

{
  undefined4 uVar1;
  code *local_10;
  undefined4 *local_c;
  undefined4 local_8;
  
  if (param_1 == 0) {
    local_c = &DAT_0063289c;
    local_10 = DAT_0063289c;
    local_8 = 2;
  }
  else {
    local_c = &DAT_006328a0;
    local_10 = DAT_006328a0;
    local_8 = 0x15;
  }
  if (local_10 == (code *)0x0) {
    uVar1 = 0;
  }
  else {
    if (local_10 != (code *)0x1) {
      *local_c = 0;
      (*local_10)(local_8);
    }
    uVar1 = 1;
  }
  return uVar1;
}
```

---

---

## FUN_00484020 — 0x484020

- Classification : internal
- Corps : `0x484020–0x4840ce`, `0x4840d2–0x4841a6`
- État : pseudocode obtenu
- Evidence : `ev_4f35535f8e253fbb1cc8fb592625b1fad64d6a95ff371ddc26285d941762a850`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x4840ca to 0x476ec0 __exit (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `0x476ec0` — `__exit`
- `0x4841e0` — `siglookup`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00484020(int param_1)

{
  int iVar1;
  code *local_18;
  undefined4 *local_14;
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  
  switch(param_1) {
  case 2:
    local_14 = &DAT_0063289c;
    local_18 = DAT_0063289c;
    break;
  default:
    return 0xffffffff;
  case 4:
  case 8:
  case 0xb:
    iVar1 = siglookup(param_1);
    local_14 = (undefined4 *)(iVar1 + 8);
    local_18 = (code *)*local_14;
    break;
  case 0xf:
    local_14 = &DAT_006328a8;
    local_18 = DAT_006328a8;
    break;
  case 0x15:
    local_14 = &DAT_006328a0;
    local_18 = DAT_006328a0;
    break;
  case 0x16:
    local_14 = &DAT_006328a4;
    local_18 = DAT_006328a4;
  }
  if (local_18 != (code *)0x1) {
    if (local_18 == (code *)0x0) {
                    /* WARNING: Subroutine does not return */
      __exit(3);
    }
    if (((param_1 == 8) || (param_1 == 0xb)) || (param_1 == 4)) {
      local_10 = DAT_0063262c;
      DAT_0063262c = 0;
      if (param_1 == 8) {
        local_8 = DAT_004a8934;
        DAT_004a8934 = 0x8c;
      }
    }
    if (param_1 == 8) {
      for (local_c = DAT_004a8928; local_c < DAT_004a8928 + _DAT_004a892c; local_c = local_c + 1) {
        *(undefined4 *)(local_c * 0xc + 0x4a88b8) = 0;
      }
    }
    else {
      *local_14 = 0;
    }
    if (param_1 == 8) {
      (*local_18)(8,DAT_004a8934);
    }
    else {
      (*local_18)(param_1);
      if ((param_1 != 0xb) && (param_1 != 4)) {
        return 0;
      }
    }
    if (param_1 == 8) {
      DAT_004a8934 = local_8;
    }
    DAT_0063262c = local_10;
    return 0;
  }
  return 0;
}
```

---

## siglookup — 0x4841e0

- Classification : internal
- Corps : `0x4841e0–0x48423c`
- État : pseudocode obtenu
- Evidence : `ev_b48ba62b42518d8de674d5baa52d34aeb031be6f45894806c47e72190ead5037`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _siglookup
   
   Library: Visual Studio 2003 Debug */

undefined4 * __cdecl siglookup(int param_1)

{
  undefined4 *local_8;
  
  local_8 = &DAT_004a88b0;
  do {
    if (local_8[1] == param_1) break;
    local_8 = local_8 + 3;
  } while (local_8 < &DAT_004a88b0 + DAT_004a8930 * 3);
  if ((&DAT_004a88b0 + DAT_004a8930 * 3 <= local_8) || (local_8[1] != param_1)) {
    local_8 = (undefined4 *)0x0;
  }
  return local_8;
}
```

---

---

## FUN_00484240 — 0x484240

- Classification : internal
- Corps : `0x484240–0x4842fa`
- État : pseudocode obtenu
- Evidence : `ev_39af1990af721e6e35b119694693ff8ee56787fe58a0923d197abc21d64e76fc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x47` — `KERNEL32.DLL::LoadLibraryA`
- `EXTERNAL:0x4b` — `KERNEL32.DLL::GetProcAddress`

### Chaînes référencées

- `0x495bdc` — "user32.dll"
- `0x496214` — "GetLastActivePopup"
- `0x496228` — "GetActiveWindow"
- `0x496238` — "MessageBoxA"

### Pseudocode Ghidra

```c
int FUN_00484240(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  HMODULE hModule;
  int iVar1;
  int local_8;
  
  local_8 = 0;
  if (DAT_006328b0 == (FARPROC)0x0) {
    hModule = LoadLibraryA("user32.dll");
    if (hModule != (HMODULE)0x0) {
      DAT_006328b0 = GetProcAddress(hModule,"MessageBoxA");
      if (DAT_006328b0 != (FARPROC)0x0) {
        DAT_006328b4 = GetProcAddress(hModule,"GetActiveWindow");
        DAT_006328b8 = GetProcAddress(hModule,"GetLastActivePopup");
        goto LAB_004842b3;
      }
    }
    iVar1 = 0;
  }
  else {
LAB_004842b3:
    if (DAT_006328b4 != (FARPROC)0x0) {
      local_8 = (*DAT_006328b4)();
    }
    if ((local_8 != 0) && (DAT_006328b8 != (FARPROC)0x0)) {
      local_8 = (*DAT_006328b8)(local_8);
    }
    iVar1 = (*DAT_006328b0)(local_8,param_1,param_2,param_3);
  }
  return iVar1;
}
```

---

---

## FUN_00484300 — 0x484300

- Classification : internal
- Corps : `0x484300–0x48445b`
- État : pseudocode obtenu
- Evidence : `ev_58553ba434576159cfe738cb5f1d180ada271fbb2b8af2889730fa6b9c2fa236`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x484335 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `EXTERNAL:0x5` — `KERNEL32.DLL::MultiByteToWideChar`
- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x496244` — "mbtowc.c"
- `0x496250` — "MB_CUR_MAX == 1 || MB_CUR_MAX == 2"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_00484300(LPWSTR param_1,byte *param_2,uint param_3)

{
  code *pcVar1;
  int iVar2;
  uint uVar3;
  
  if (((DAT_004a87f4 != 1) && (DAT_004a87f4 != 2)) &&
     (iVar2 = FUN_0047a120(2,"mbtowc.c",0x4f,0,"MB_CUR_MAX == 1 || MB_CUR_MAX == 2"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == (byte *)0x0) || (param_3 == 0)) {
    uVar3 = 0;
  }
  else if (*param_2 == 0) {
    if (param_1 != (LPWSTR)0x0) {
      *param_1 = L'\0';
    }
    uVar3 = 0;
  }
  else if (DAT_006325e8 == 0) {
    if (param_1 != (LPWSTR)0x0) {
      *param_1 = (ushort)*param_2;
    }
    uVar3 = 1;
  }
  else if ((*(ushort *)(PTR_DAT_004a85e8 + (uint)*param_2 * 2) & 0x8000) == 0) {
    iVar2 = MultiByteToWideChar(DAT_006325f8,9,(LPCSTR)param_2,1,param_1,
                                (uint)(param_1 != (LPWSTR)0x0));
    if (iVar2 == 0) {
      _DAT_0063251c = 0x2a;
      uVar3 = 0xffffffff;
    }
    else {
      uVar3 = 1;
    }
  }
  else if (((((int)DAT_004a87f4 < 2) || ((int)param_3 < (int)DAT_004a87f4)) ||
           (iVar2 = MultiByteToWideChar(DAT_006325f8,9,(LPCSTR)param_2,DAT_004a87f4,param_1,
                                        (uint)(param_1 != (LPWSTR)0x0)), uVar3 = DAT_004a87f4,
           iVar2 == 0)) && ((param_3 < DAT_004a87f4 || (uVar3 = DAT_004a87f4, param_2[1] == 0)))) {
    _DAT_0063251c = 0x2a;
    uVar3 = 0xffffffff;
  }
  return uVar3;
}
```

---

---

## FUN_00484460 — 0x484460

- Classification : internal
- Corps : `0x484460–0x4844a0`
- État : pseudocode obtenu
- Evidence : `ev_717bd07ee174811bb680459ec14452eda8690d1dc74a30cfb6e1166dc65e2f23`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00484460(int param_1)

{
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 0x103;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,0x103);
  }
  return local_8;
}
```

---

---

## FUN_004844b0 — 0x4844b0

- Classification : internal
- Corps : `0x4844b0–0x4844eb`
- État : pseudocode obtenu
- Evidence : `ev_83c98531942d843983526c39b9c26a57034666e87b468b525cbc0a07f9378610`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_004844b0(int param_1)

{
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 1;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,1);
  }
  return local_8;
}
```

---

---

## FUN_004844f0 — 0x4844f0

- Classification : internal
- Corps : `0x4844f0–0x48452b`
- État : pseudocode obtenu
- Evidence : `ev_ee3164ac8dc7f11ff1199a3a0bedb288faba628246d394b95677ab9aee0564d3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_004844f0(int param_1)

{
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 2;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,2);
  }
  return local_8;
}
```

---

# Lot 0019 — détails des procédures (2/4)



## FUN_0048a600 — 0x48a600

- Classification : internal
- Corps : `0x48a600–0x48a655`
- État : pseudocode obtenu
- Evidence : `ev_9fe587262b338f62a434ca0b8d8cd164f1f05917a148e54ca40e6b9791a7edc1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0048a600(short *param_1,int param_2)

{
  int local_c;
  short *local_8;
  
  local_c = param_2;
  for (local_8 = param_1; (local_c != 0 && (*local_8 != 0)); local_8 = local_8 + 1) {
    local_c = local_c + -1;
  }
  if (*local_8 == 0) {
    param_2 = (int)local_8 - (int)param_1 >> 1;
  }
  return param_2;
}
```

---

## FUN_0048a660 — 0x48a660

- Classification : internal
- Corps : `0x48a660–0x48aa19`
- État : pseudocode obtenu
- Evidence : `ev_8d521700d2261f8f8dec0c97d85482bed1330390a609e03a1d5fe60291e24169`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x48a7f9 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `EXTERNAL:0x5` — `KERNEL32.DLL::MultiByteToWideChar`
- `EXTERNAL:0x1a` — `KERNEL32.DLL::GetCPInfo`
- `EXTERNAL:0x32` — `KERNEL32.DLL::CompareStringW`
- `EXTERNAL:0x33` — `KERNEL32.DLL::CompareStringA`
- `0x474d40` — `FUN_00474d40`
- `0x475780` — `FUN_00475780`
- `0x47a120` — `FUN_0047a120`
- `0x48aa20` — `FUN_0048aa20`

### Chaînes référencées

- `0x496410` — "aw_cmp.c"
- `0x496410` — "aw_cmp.c"
- `0x496410` — "aw_cmp.c"
- `0x49641c` — "cchCount1==0 && cchCount2==1 || cchCount1==1 && cchCount2==0"

### Pseudocode Ghidra

```c
void FUN_0048a660(LCID param_1,DWORD param_2,byte *param_3,int param_4,byte *param_5,int param_6,
                 UINT param_7)

{
  code *pcVar1;
  int iVar2;
  BOOL BVar3;
  BYTE *local_30;
  _cpinfo local_2c;
  int local_18;
  LPWSTR local_14;
  LPWSTR local_10;
  int local_c;
  int local_8;
  
  if (DAT_006329b8 == 0) {
    iVar2 = CompareStringA(0,0,"",1,"",1);
    if (iVar2 == 0) {
      iVar2 = CompareStringW(0,0,L"",1,L"",1);
      if (iVar2 == 0) {
        return;
      }
      DAT_006329b8 = 1;
    }
    else {
      DAT_006329b8 = 2;
    }
  }
  if (0 < param_4) {
    param_4 = FUN_0048aa20(param_3,param_4);
  }
  if (0 < param_6) {
    param_6 = FUN_0048aa20(param_5,param_6);
  }
  if (DAT_006329b8 == 2) {
    CompareStringA(param_1,param_2,(PCNZCH)param_3,param_4,(PCNZCH)param_5,param_6);
  }
  else if (DAT_006329b8 == 1) {
    local_18 = 0;
    local_8 = 0;
    local_c = 0;
    local_10 = (LPWSTR)0x0;
    local_14 = (LPWSTR)0x0;
    if (param_7 == 0) {
      param_7 = DAT_006325f8;
    }
    if ((param_4 == 0) || (param_6 == 0)) {
      if (param_4 == param_6) {
        return;
      }
      if (1 < param_6) {
        return;
      }
      if (1 < param_4) {
        return;
      }
      BVar3 = GetCPInfo(param_7,&local_2c);
      if (BVar3 == 0) {
        return;
      }
      if ((((param_4 != 0) || (param_6 != 1)) && ((param_4 != 1 || (param_6 != 0)))) &&
         (iVar2 = FUN_0047a120(2,"aw_cmp.c",0x162,0,
                               "cchCount1==0 && cchCount2==1 || cchCount1==1 && cchCount2==0"),
         iVar2 == 1)) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      if (0 < param_4) {
        if (local_2c.MaxCharSize < 2) {
          return;
        }
        local_30 = local_2c.LeadByte;
        while( true ) {
          if (*local_30 == 0) {
            return;
          }
          if (local_30[1] == 0) break;
          if ((*local_30 <= *param_3) && (*param_3 <= local_30[1])) {
            return;
          }
          local_30 = local_30 + 2;
        }
        return;
      }
      if (0 < param_6) {
        if (local_2c.MaxCharSize < 2) {
          return;
        }
        local_30 = local_2c.LeadByte;
        while( true ) {
          if (*local_30 == 0) {
            return;
          }
          if (local_30[1] == 0) break;
          if ((*local_30 <= *param_5) && (*param_5 <= local_30[1])) {
            return;
          }
          local_30 = local_30 + 2;
        }
        return;
      }
    }
    local_8 = MultiByteToWideChar(param_7,9,(LPCSTR)param_3,param_4,(LPWSTR)0x0,0);
    if ((local_8 != 0) &&
       (local_10 = (LPWSTR)FUN_00474d40(local_8 << 1,2,"aw_cmp.c",0x18a), local_10 != (LPWSTR)0x0))
    {
      iVar2 = MultiByteToWideChar(param_7,1,(LPCSTR)param_3,param_4,local_10,local_8);
      if ((iVar2 != 0) &&
         (((local_c = MultiByteToWideChar(param_7,9,(LPCSTR)param_5,param_6,(LPWSTR)0x0,0),
           local_c != 0 &&
           (local_14 = (LPWSTR)FUN_00474d40(local_c << 1,2,"aw_cmp.c",0x199),
           local_14 != (LPWSTR)0x0)) &&
          (iVar2 = MultiByteToWideChar(param_7,1,(LPCSTR)param_5,param_6,local_14,local_c),
          iVar2 != 0)))) {
        local_18 = CompareStringW(param_1,param_2,local_10,local_8,local_14,local_c);
      }
      FUN_00475780(local_10,2);
      FUN_00475780(local_14,2);
    }
  }
  return;
}
```

---

## FUN_0048aa20 — 0x48aa20

- Classification : internal
- Corps : `0x48aa20–0x48aa6f`
- État : pseudocode obtenu
- Evidence : `ev_fccad85dc9b843c1bd3858b8ed8df7d6ad0aa770581509603e109131dbdae42d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0048aa20(char *param_1,int param_2)

{
  int local_c;
  char *local_8;
  
  local_c = param_2;
  for (local_8 = param_1; (local_c != 0 && (*local_8 != '\0')); local_8 = local_8 + 1) {
    local_c = local_c + -1;
  }
  if (*local_8 == '\0') {
    param_2 = (int)local_8 - (int)param_1;
  }
  return param_2;
}
```

---

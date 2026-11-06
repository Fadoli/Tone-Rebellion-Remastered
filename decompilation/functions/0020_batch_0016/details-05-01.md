# 0020_batch_0016 — détails (1/3)

## FUN_0047cf40 — 0x47cf40

- Classification : internal
- Corps : `0x47cf40–0x47d24a`
- État : pseudocode obtenu
- Evidence : `ev_a5112bfd30d387c6eb39436e2e1ffc0a1f75edc3379383e86fe65f0dd2e9a1d3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xa` — `KERNEL32.DLL::GetStdHandle`
- `EXTERNAL:0x2a` — `KERNEL32.DLL::SetHandleCount`
- `EXTERNAL:0x38` — `KERNEL32.DLL::GetFileType`
- `EXTERNAL:0x3f` — `KERNEL32.DLL::GetStartupInfoA`
- `0x474d40` — `FUN_00474d40`
- `0x478690` — `__amsg_exit`

### Chaînes référencées

- `0x495dd4` — "ioinit.c"
- `0x495dd4` — "ioinit.c"

### Pseudocode Ghidra

```c
void FUN_0047cf40(void)

{
  undefined4 *puVar1;
  int *piVar2;
  DWORD DVar3;
  HANDLE hFile;
  DWORD local_70;
  UINT local_6c;
  UINT local_68;
  byte *local_64;
  int local_60;
  uint local_5c;
  undefined4 *local_54;
  _STARTUPINFOA local_4c;
  byte *local_8;
  
  local_54 = (undefined4 *)FUN_00474d40(0x100,2,"ioinit.c",0x81);
  if (local_54 == (undefined4 *)0x0) {
    __amsg_exit(0x1b);
  }
  DAT_00633e5c = 0x20;
  DAT_00633d20 = local_54;
  for (; local_54 < DAT_00633d20 + 0x40; local_54 = local_54 + 2) {
    *(undefined1 *)(local_54 + 1) = 0;
    *local_54 = 0xffffffff;
    *(undefined1 *)((int)local_54 + 5) = 10;
  }
  GetStartupInfoA(&local_4c);
  if ((local_4c.cbReserved2 != 0) &&
     (CONCAT22(local_4c.lpReserved2._2_2_,local_4c.lpReserved2._0_2_) != 0)) {
    local_6c = *(UINT *)CONCAT22(local_4c.lpReserved2._2_2_,local_4c.lpReserved2._0_2_);
    local_8 = (byte *)(CONCAT22(local_4c.lpReserved2._2_2_,local_4c.lpReserved2._0_2_) + 4);
    local_64 = local_8 + local_6c;
    if (0x7ff < (int)local_6c) {
      local_6c = 0x800;
    }
    local_68 = local_6c;
    local_60 = 1;
    while ((int)DAT_00633e5c < (int)local_6c) {
      local_54 = (undefined4 *)FUN_00474d40(0x100,2,"ioinit.c",0xb6);
      if (local_54 == (undefined4 *)0x0) {
        local_68 = DAT_00633e5c;
        break;
      }
      (&DAT_00633d20)[local_60] = local_54;
      DAT_00633e5c = DAT_00633e5c + 0x20;
      for (; local_54 < (undefined4 *)((int)(&DAT_00633d20)[local_60] + 0x100);
          local_54 = local_54 + 2) {
        *(undefined1 *)(local_54 + 1) = 0;
        *local_54 = 0xffffffff;
        *(undefined1 *)((int)local_54 + 5) = 10;
      }
      local_60 = local_60 + 1;
    }
    for (local_5c = 0; (int)local_5c < (int)local_68; local_5c = local_5c + 1) {
      if (((*(int *)local_64 != -1) && ((*local_8 & 1) != 0)) &&
         (((*local_8 & 8) != 0 || (DVar3 = GetFileType(*(HANDLE *)local_64), DVar3 != 0)))) {
        puVar1 = (undefined4 *)((int)(&DAT_00633d20)[(int)local_5c >> 5] + (local_5c & 0x1f) * 8);
        *puVar1 = *(undefined4 *)local_64;
        *(byte *)(puVar1 + 1) = *local_8;
      }
      local_8 = local_8 + 1;
      local_64 = local_64 + 4;
    }
  }
  for (local_5c = 0; (int)local_5c < 3; local_5c = local_5c + 1) {
    piVar2 = DAT_00633d20 + local_5c * 2;
    if (*piVar2 == -1) {
      *(undefined1 *)(piVar2 + 1) = 0x81;
      if (local_5c == 0) {
        local_70 = 0xfffffff6;
      }
      else {
        local_70 = 0xfffffff5 - (local_5c != 1);
      }
      hFile = GetStdHandle(local_70);
      if ((hFile == (HANDLE)0xffffffff) || (DVar3 = GetFileType(hFile), DVar3 == 0)) {
        *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) | 0x40;
      }
      else {
        *piVar2 = (int)hFile;
        if ((DVar3 & 0xff) == 2) {
          *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) | 0x40;
        }
        else if ((DVar3 & 0xff) == 3) {
          *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) | 8;
        }
      }
    }
    else {
      *(byte *)(piVar2 + 1) = *(byte *)(piVar2 + 1) | 0x80;
    }
  }
  SetHandleCount(DAT_00633e5c);
  return;
}
```

---

## __ioterm — 0x47d250

- Classification : internal
- Corps : `0x47d250–0x47d2a1`
- État : pseudocode obtenu
- Evidence : `ev_06132c377167502ab67b4d1fa3bd8ad415f6cdab8eeaeed8465b4bd34723df95`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x475780` — `FUN_00475780`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __ioterm
   
   Library: Visual Studio 2003 Debug */

void __cdecl __ioterm(void)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 0x40; local_8 = local_8 + 1) {
    if ((&DAT_00633d20)[local_8] != 0) {
      FUN_00475780((&DAT_00633d20)[local_8],2);
      (&DAT_00633d20)[local_8] = 0;
    }
  }
  return;
}
```

---

---

## FUN_0047d2b0 — 0x47d2b0

- Classification : internal
- Corps : `0x47d2b0–0x47d514`
- État : pseudocode obtenu
- Evidence : `ev_e73ecb7359eb8e05b4d4c66ab62e493ba38812ed23ed3206a01cb116b2a0550c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x47d338 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `EXTERNAL:0x29` — `KERNEL32.DLL::SetEndOfFile`
- `0x4739b0` — `FUN_004739b0`
- `0x4745f0` — `FUN_004745f0`
- `0x474b20` — `_memset`
- `0x478410` — `FUN_00478410`
- `0x47a120` — `FUN_0047a120`
- `0x47ce00` — `FUN_0047ce00`
- `0x484d00` — `FUN_00484d00`

### Chaînes référencées

- `0x495de0` — "chsize.c"
- `0x495dec` — "size >= 0"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0047d2b0(uint param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  HANDLE hFile;
  BOOL BVar3;
  int local_1020;
  int local_101c;
  undefined1 local_1008 [4064];
  undefined4 uStackY_28;
  undefined4 uStackY_24;
  char *pcStackY_20;
  
  FUN_00478410();
  local_1020 = 0;
  if ((param_1 < DAT_00633e5c) &&
     ((*(byte *)((&DAT_00633d20)[(int)param_1 >> 5] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    if (param_2 < 0) {
      pcStackY_20 = "chsize.c";
      uStackY_24 = 2;
      uStackY_28 = 0x47d330;
      iVar2 = FUN_0047a120();
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        iVar2 = (*pcVar1)();
        return iVar2;
      }
    }
    pcStackY_20 = (char *)0x47d34c;
    iVar2 = FUN_004739b0();
    if (iVar2 != -1) {
      pcStackY_20 = (char *)0x47d36b;
      local_101c = FUN_004739b0();
      if (local_101c != -1) {
        local_101c = param_2 - local_101c;
        if (local_101c < 1) {
          if (local_101c < 0) {
            pcStackY_20 = (char *)0x47d4b2;
            FUN_004739b0();
            hFile = (HANDLE)FUN_0047ce00();
            BVar3 = SetEndOfFile(hFile);
            local_1020 = (BVar3 != 0) - 1;
            if (local_1020 == -1) {
              _DAT_0063251c = 0xd;
              DAT_00632520 = GetLastError();
            }
          }
        }
        else {
          pcStackY_20 = (char *)0x47d3b4;
          _memset(local_1008,0,0x1000);
          FUN_00484d00();
          do {
            pcStackY_20 = (char *)0x47d436;
            iVar2 = FUN_004745f0();
            if (iVar2 == -1) {
              if (DAT_00632520 == 5) {
                _DAT_0063251c = 0xd;
              }
              local_1020 = -1;
              break;
            }
            local_101c = local_101c - iVar2;
          } while (0 < local_101c);
          FUN_00484d00();
        }
        pcStackY_20 = (char *)0x47d505;
        FUN_004739b0();
        return local_1020;
      }
    }
  }
  else {
    _DAT_0063251c = 9;
  }
  return -1;
}
```

---

---

## FUN_0047d520 — 0x47d520

- Classification : internal
- Corps : `0x47d520–0x47d5b1`
- État : pseudocode obtenu
- Evidence : `ev_6616b1501dcdce33de4212a40284044d4dd743825b8268c2197ca95cf58225c2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x47d549 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x475780` — `FUN_00475780`
- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x4951f4` — "stream != NULL"
- `0x495df8` — "_freebuf.c"

### Pseudocode Ghidra

```c
void FUN_0047d520(undefined4 *param_1)

{
  code *pcVar1;
  int iVar2;
  
  if ((param_1 == (undefined4 *)0x0) &&
     (iVar2 = FUN_0047a120(2,"_freebuf.c",0x30,0,"stream != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (((param_1[3] & 0x83) != 0) && ((param_1[3] & 8) != 0)) {
    FUN_00475780(param_1[2],2);
    param_1[3] = param_1[3] & 0xfffffbf7;
    *param_1 = 0;
    param_1[2] = 0;
    param_1[1] = 0;
  }
  return;
}
```

---

---

## FUN_0047d5c0 — 0x47d5c0

- Classification : internal
- Corps : `0x47d5c0–0x47d612`
- État : pseudocode obtenu
- Evidence : `ev_e1a4e5c2f05b3f0998525c035173e93c004dc84fd27389b2eb92fc1e2eaed049`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47d620` — `FUN_0047d620`
- `0x47d6f0` — `FUN_0047d6f0`
- `0x484e00` — `FUN_00484e00`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0047d5c0(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    iVar1 = FUN_0047d6f0(0);
  }
  else {
    iVar1 = FUN_0047d620(param_1);
    if (iVar1 == 0) {
      if ((*(uint *)(param_1 + 0xc) & 0x4000) == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = FUN_00484e00(*(undefined4 *)(param_1 + 0x10));
        iVar1 = -(uint)(iVar1 != 0);
      }
    }
    else {
      iVar1 = -1;
    }
  }
  return iVar1;
}
```

---

---

## FUN_0047d620 — 0x47d620

- Classification : internal
- Corps : `0x47d620–0x47d6d6`
- État : pseudocode obtenu
- Evidence : `ev_98b007e9ea2980db482a31c9f1b40d65b5caf03b72db8bfd29a4dffad1ce936a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4745f0` — `FUN_004745f0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047d620(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 local_8;
  
  local_8 = 0;
  if ((((param_1[3] & 3U) == 2) && ((param_1[3] & 0x108U) != 0)) &&
     (iVar2 = *param_1 - param_1[2], 0 < iVar2)) {
    iVar1 = FUN_004745f0(param_1[4],param_1[2],iVar2);
    if (iVar1 == iVar2) {
      if ((param_1[3] & 0x80U) != 0) {
        param_1[3] = param_1[3] & 0xfffffffd;
      }
    }
    else {
      param_1[3] = param_1[3] | 0x20;
      local_8 = 0xffffffff;
    }
  }
  *param_1 = param_1[2];
  param_1[1] = 0;
  return local_8;
}
```

---

---

## FUN_0047d6e0 — 0x47d6e0

- Classification : internal
- Corps : `0x47d6e0–0x47d6ee`
- État : pseudocode obtenu
- Evidence : `ev_6a7eb401facb2b2892554d17a2bc2b21df97afdd1d32cbd72748805a8a1d9c68`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47d6f0` — `FUN_0047d6f0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047d6e0(void)

{
  FUN_0047d6f0(1);
  return;
}
```

---

---

## FUN_0047d6f0 — 0x47d6f0

- Classification : internal
- Corps : `0x47d6f0–0x47d7cd`
- État : pseudocode obtenu
- Evidence : `ev_c3c9c2e0183b5b397959f5ca5803ef7deb7ab562f807935e84681423571bf889`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47d5c0` — `FUN_0047d5c0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0047d6f0(int param_1)

{
  int iVar1;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  for (local_10 = 0; local_10 < DAT_00633d00; local_10 = local_10 + 1) {
    if ((*(int *)(DAT_006329bc + local_10 * 4) != 0) &&
       ((*(uint *)(*(int *)(DAT_006329bc + local_10 * 4) + 0xc) & 0x83) != 0)) {
      if (param_1 == 1) {
        iVar1 = FUN_0047d5c0(*(undefined4 *)(DAT_006329bc + local_10 * 4));
        if (iVar1 != -1) {
          local_8 = local_8 + 1;
        }
      }
      else if (((param_1 == 0) &&
               ((*(uint *)(*(int *)(DAT_006329bc + local_10 * 4) + 0xc) & 2) != 0)) &&
              (iVar1 = FUN_0047d5c0(*(undefined4 *)(DAT_006329bc + local_10 * 4)), iVar1 == -1)) {
        local_c = -1;
      }
    }
  }
  if (param_1 == 1) {
    local_c = local_8;
  }
  return local_c;
}
```

---

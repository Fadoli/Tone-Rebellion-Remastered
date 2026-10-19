# 0020_batch_0016 — détails (5/6)

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

## FUN_0047d7d0 — 0x47d7d0

- Classification : internal
- Corps : `0x47d7d0–0x47daec`
- État : pseudocode obtenu
- Evidence : `ev_36f54ffb291db4baf0b444e51efc7d83b5a487d70a97f8bdab8fbd4751cd0301`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x47d812 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x47d83c with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x47d866 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x473ae0` — `FUN_00473ae0`
- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x4951dc` — "str != NULL"
- `0x495218` — "mode != NULL"
- `0x495e04` — "_open.c"
- `0x495e04` — "_open.c"
- `0x495e04` — "_open.c"
- `0x495e0c` — "filename != NULL"

### Pseudocode Ghidra

```c
undefined4 * FUN_0047d7d0(int param_1,char *param_2,undefined4 param_3,undefined4 *param_4)

{
  char cVar1;
  code *pcVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  undefined4 *puVar7;
  uint local_20;
  uint local_18;
  
  local_20 = DAT_006328c0;
  bVar4 = false;
  bVar5 = false;
  if ((param_1 == 0) && (iVar6 = FUN_0047a120(2,"_open.c",0x47,0,"filename != NULL"), iVar6 == 1)) {
    pcVar2 = (code *)swi(3);
    puVar7 = (undefined4 *)(*pcVar2)();
    return puVar7;
  }
  if ((param_2 == (char *)0x0) &&
     (iVar6 = FUN_0047a120(2,"_open.c",0x48,0,"mode != NULL"), iVar6 == 1)) {
    pcVar2 = (code *)swi(3);
    puVar7 = (undefined4 *)(*pcVar2)();
    return puVar7;
  }
  if ((param_4 == (undefined4 *)0x0) &&
     (iVar6 = FUN_0047a120(2,"_open.c",0x49,0,"str != NULL"), iVar6 == 1)) {
    pcVar2 = (code *)swi(3);
    puVar7 = (undefined4 *)(*pcVar2)();
    return puVar7;
  }
  cVar1 = *param_2;
  if (cVar1 == 'a') {
    local_18 = 0x109;
    local_20 = local_20 | 2;
  }
  else if (cVar1 == 'r') {
    local_18 = 0;
    local_20 = local_20 | 1;
  }
  else {
    if (cVar1 != 'w') {
      return (undefined4 *)0x0;
    }
    local_18 = 0x301;
    local_20 = local_20 | 2;
  }
  bVar3 = true;
  while ((param_2 = param_2 + 1, *param_2 != '\0' && (bVar3))) {
    switch(*param_2) {
    case '+':
      if ((local_18 & 2) == 0) {
        local_18 = local_18 & 0xfffffffe | 2;
        local_20 = local_20 & 0xfffffffc | 0x80;
      }
      else {
        bVar3 = false;
      }
      break;
    default:
      bVar3 = false;
      break;
    case 'D':
      if ((local_18 & 0x40) == 0) {
        local_18 = local_18 | 0x40;
      }
      else {
        bVar3 = false;
      }
      break;
    case 'R':
      if (bVar5) {
        bVar3 = false;
      }
      else {
        bVar5 = true;
        local_18 = local_18 | 0x10;
      }
      break;
    case 'S':
      if (bVar5) {
        bVar3 = false;
      }
      else {
        bVar5 = true;
        local_18 = local_18 | 0x20;
      }
      break;
    case 'T':
      if ((local_18 & 0x1000) == 0) {
        local_18 = local_18 | 0x1000;
      }
      else {
        bVar3 = false;
      }
      break;
    case 'b':
      if ((local_18 & 0xc000) == 0) {
        local_18 = local_18 | 0x8000;
      }
      else {
        bVar3 = false;
      }
      break;
    case 'c':
      if (bVar4) {
        bVar3 = false;
      }
      else {
        bVar4 = true;
        local_20 = local_20 | 0x4000;
      }
      break;
    case 'n':
      if (bVar4) {
        bVar3 = false;
      }
      else {
        bVar4 = true;
        local_20 = local_20 & 0xffffbfff;
      }
      break;
    case 't':
      if ((local_18 & 0xc000) == 0) {
        local_18 = local_18 | 0x4000;
      }
      else {
        bVar3 = false;
      }
    }
  }
  iVar6 = FUN_00473ae0(param_1,local_18,param_3,0x1a4);
  if (iVar6 < 0) {
    param_4 = (undefined4 *)0x0;
  }
  else {
    DAT_00632898 = DAT_00632898 + 1;
    param_4[3] = local_20;
    param_4[1] = 0;
    *param_4 = 0;
    param_4[2] = 0;
    param_4[7] = 0;
    param_4[4] = iVar6;
  }
  return param_4;
}
```

---

## FUN_0047db60 — 0x47db60

- Classification : internal
- Corps : `0x47db60–0x47dc4d`
- État : pseudocode obtenu
- Evidence : `ev_5a5f1fd3acff5f5c6e3075f6e001b41a6c194a07a8ff3f39297b5da0356f91cf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474d40` — `FUN_00474d40`

### Chaînes référencées

- `0x495e20` — "stream.c"

### Pseudocode Ghidra

```c
undefined4 * FUN_0047db60(void)

{
  undefined4 uVar1;
  undefined4 *local_c;
  int local_8;
  
  local_c = (undefined4 *)0x0;
  local_8 = 0;
  do {
    if (DAT_00633d00 <= local_8) {
LAB_0047dc06:
      if (local_c != (undefined4 *)0x0) {
        local_c[1] = 0;
        local_c[3] = 0;
        local_c[2] = 0;
        *local_c = 0;
        local_c[7] = 0;
        local_c[4] = 0xffffffff;
      }
      return local_c;
    }
    if (*(int *)(DAT_006329bc + local_8 * 4) == 0) {
      uVar1 = FUN_00474d40(0x20,2,"stream.c",0x55);
      *(undefined4 *)(DAT_006329bc + local_8 * 4) = uVar1;
      if (*(int *)(DAT_006329bc + local_8 * 4) != 0) {
        local_c = *(undefined4 **)(DAT_006329bc + local_8 * 4);
      }
      goto LAB_0047dc06;
    }
    if ((*(uint *)(*(int *)(DAT_006329bc + local_8 * 4) + 0xc) & 0x83) == 0) {
      local_c = *(undefined4 **)(DAT_006329bc + local_8 * 4);
      goto LAB_0047dc06;
    }
    local_8 = local_8 + 1;
  } while( true );
}
```

---

## FUN_0047dc50 — 0x47dc50

- Classification : internal
- Corps : `0x47dc50–0x47dd7d`
- État : pseudocode obtenu
- Evidence : `ev_2a8cb43ef8e7dcb317660f754bba81aea4a3d2970972b79b13fcd7203ec4f361`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x47dc7c with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x474d40` — `FUN_00474d40`
- `0x47a120` — `FUN_0047a120`
- `0x483630` — `__isatty`

### Chaînes référencées

- `0x4951dc` — "str != NULL"
- `0x495e2c` — "_sftbuf.c"
- `0x495e2c` — "_sftbuf.c"

### Pseudocode Ghidra

```c
undefined4 FUN_0047dc50(undefined4 *param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  int local_c;
  
  if ((param_1 == (undefined4 *)0x0) &&
     (iVar2 = FUN_0047a120(2,"_sftbuf.c",0x41,0,"str != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  iVar2 = __isatty(param_1[4]);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    if (param_1 == (undefined4 *)&DAT_004a8b10) {
      local_c = 0;
    }
    else {
      if (param_1 != (undefined4 *)&DAT_004a8b30) {
        return 0;
      }
      local_c = 1;
    }
    DAT_00632898 = DAT_00632898 + 1;
    if ((param_1[3] & 0x10c) == 0) {
      if (*(int *)(&DAT_006325a8 + local_c * 4) == 0) {
        uVar3 = FUN_00474d40(0x1000,2,"_sftbuf.c",0x5e);
        *(undefined4 *)(&DAT_006325a8 + local_c * 4) = uVar3;
        if (*(int *)(&DAT_006325a8 + local_c * 4) == 0) {
          return 0;
        }
      }
      param_1[2] = *(undefined4 *)(&DAT_006325a8 + local_c * 4);
      *param_1 = param_1[2];
      param_1[6] = 0x1000;
      param_1[1] = 0x1000;
      param_1[3] = param_1[3] | 0x1102;
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
  }
  return uVar3;
}
```

---

## FUN_0047dd80 — 0x47dd80

- Classification : internal
- Corps : `0x47dd80–0x47de30`
- État : pseudocode obtenu
- Evidence : `ev_ffbd1a2c5bdd179befdc170058a1b25a76d4361f3d8ab4e1f0d58e5712c3610f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x47ddb3 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x47a120` — `FUN_0047a120`
- `0x47d620` — `FUN_0047d620`

### Chaînes référencées

- `0x495e2c` — "_sftbuf.c"
- `0x495e38` — "flag == 0 || flag == 1"

### Pseudocode Ghidra

```c
void FUN_0047dd80(int param_1,undefined4 *param_2)

{
  code *pcVar1;
  int iVar2;
  
  if (((param_1 != 0) && (param_1 != 1)) &&
     (iVar2 = FUN_0047a120(2,"_sftbuf.c",0x96,0,"flag == 0 || flag == 1"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (param_1 == 0) {
    if ((param_2[3] & 0x1000) != 0) {
      FUN_0047d620(param_2);
    }
  }
  else if ((param_2[3] & 0x1000) != 0) {
    FUN_0047d620(param_2);
    param_2[3] = param_2[3] & 0xffffeeff;
    param_2[6] = 0;
    *param_2 = 0;
    param_2[2] = 0;
  }
  return;
}
```

---

## FUN_0047de40 — 0x47de40

- Classification : internal
- Corps : `0x47de40–0x47de5b`
- État : pseudocode obtenu
- Evidence : `ev_77d440ec4f4370dfcafad5c72ebc9d0474f8cf40f48d46b287d99f95fbdd732d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047de40(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_006325b4;
  DAT_006325b4 = param_1;
  return uVar1;
}
```

---

## FUN_0047de60 — 0x47de60

- Classification : internal
- Corps : `0x47de60–0x47de69`
- État : pseudocode obtenu
- Evidence : `ev_31e8f1ff414fded13ba3cfabc4e30054528464e81d22c572afe39c20a3bd9465`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047de60(void)

{
  return DAT_006325b4;
}
```

---

## __callnewh — 0x47de70

- Classification : internal
- Corps : `0x47de70–0x47de9c`
- État : pseudocode obtenu
- Evidence : `ev_29ea3b43b0f2d944210c4af92d928ffe4ffb8aee5cd8bd6b20106bcc8443bdc5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __callnewh
   
   Library: Visual Studio 2003 Debug */

int __cdecl __callnewh(size_t _Size)

{
  int iVar1;
  
  if ((DAT_006325b4 != (code *)0x0) && (iVar1 = (*DAT_006325b4)(_Size), iVar1 != 0)) {
    return 1;
  }
  return 0;
}
```

---

## FUN_0047dea0 — 0x47dea0

- Classification : internal
- Corps : `0x47dea0–0x47deb6`
- État : pseudocode obtenu
- Evidence : `ev_cce649f0dc9bb0983a1365ffb31f4434561fec114c3e46f027ccd256c913526e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47dec0` — `FUN_0047dec0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047dea0(undefined4 param_1)

{
  FUN_0047dec0(param_1,DAT_006325b0);
  return;
}
```

---

## FUN_0047dec0 — 0x47dec0

- Classification : internal
- Corps : `0x47dec0–0x47df33`
- État : pseudocode obtenu
- Evidence : `ev_8a00b03a74ef2fabda0afcf953cf3b9cef229fb0cdaef36af36dde361be0992b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47de70` — `__callnewh`
- `0x47df40` — `FUN_0047df40`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0047dec0(uint param_1,int param_2)

{
  int iVar1;
  uint local_c;
  int local_8;
  
  if (param_1 < 0xffffffe1) {
    if (param_1 == 0) {
      local_c = 1;
    }
    else {
      local_c = param_1;
    }
    do {
      if (local_c < 0xffffffe1) {
        local_8 = FUN_0047df40(local_c);
      }
      else {
        local_8 = 0;
      }
      if (local_8 != 0) {
        return local_8;
      }
      if (param_2 == 0) {
        return 0;
      }
      iVar1 = __callnewh(local_c);
    } while (iVar1 != 0);
  }
  return 0;
}
```

---

## FUN_0047df40 — 0x47df40

- Classification : internal
- Corps : `0x47df40–0x47df8d`
- État : pseudocode obtenu
- Evidence : `ev_e05f380fed41247ce83371f9ed862a62b90afcf52bffc7a9b2fd2313cd48a9e5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x28` — `KERNEL32.DLL::HeapAlloc`
- `0x47e890` — `FUN_0047e890`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
LPVOID FUN_0047df40(int param_1)

{
  uint dwBytes;
  LPVOID pvVar1;
  
  dwBytes = param_1 + 0xfU & 0xfffffff0;
  if ((DAT_004a85e4 < dwBytes) ||
     (pvVar1 = (LPVOID)FUN_0047e890(param_1 + 0xfU >> 4), pvVar1 == (LPVOID)0x0)) {
    pvVar1 = HeapAlloc(DAT_00633d04,0,dwBytes);
  }
  return pvVar1;
}
```

---

## FUN_0047df90 — 0x47df90

- Classification : internal
- Corps : `0x47df90–0x47df99`
- État : pseudocode obtenu
- Evidence : `ev_51c998c624c5f9f137b062495ff1cc13a98fc565de8546f207bc580b0d3a2c63`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047df90(void)

{
  return 1;
}
```

---

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


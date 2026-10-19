# 0020_batch_0016 — détails (2/3)

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

# 0020_batch_0016 — détails (2/2)

## FUN_004789a0 — 0x4789a0

- Classification : internal
- Corps : `0x4789a0–0x478b5b`
- État : pseudocode obtenu
- Evidence : `ev_f138787037314b2bd06e229b07ba87f5f2e0930fdd992bad39e6358010781a3b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472da0` — `FUN_00472da0`
- `0x478ec0` — `__shift`
- `0x482f30` — `FUN_00482f30`
- `0x483020` — `FUN_00483020`

### Chaînes référencées

- `0x495a28` — "e+000"

### Pseudocode Ghidra

```c
undefined1 * FUN_004789a0(undefined4 *param_1,undefined1 *param_2,int param_3,int param_4)

{
  undefined1 *puVar1;
  int local_10;
  int *local_c;
  undefined1 *local_8;
  
  if (DAT_00632580 == '\0') {
    local_c = (int *)FUN_00483020(*param_1,param_1[1]);
    FUN_00482f30(param_2 + (uint)(0 < param_3) + (uint)(*local_c == 0x2d),param_3 + 1,local_c);
  }
  else {
    local_c = DAT_0063257c;
    __shift(param_2 + (*DAT_0063257c == 0x2d),0 < param_3);
  }
  local_8 = param_2;
  if (*local_c == 0x2d) {
    *param_2 = 0x2d;
    local_8 = param_2 + 1;
  }
  if (0 < param_3) {
    *local_8 = local_8[1];
    local_8 = local_8 + 1;
    *local_8 = DAT_004a87f8;
  }
  puVar1 = (undefined1 *)FUN_00472da0(local_8 + (uint)(DAT_00632580 == '\0') + param_3,"e+000");
  if (param_4 != 0) {
    *puVar1 = 0x45;
  }
  if (*(char *)local_c[3] != '0') {
    local_10 = local_c[1] + -1;
    if (local_10 < 0) {
      local_10 = -local_10;
      puVar1[1] = 0x2d;
    }
    if (99 < local_10) {
      puVar1[2] = puVar1[2] + (char)(local_10 / 100);
      local_10 = local_10 % 100;
    }
    if (9 < local_10) {
      puVar1[3] = puVar1[3] + (char)(local_10 / 10);
      local_10 = local_10 % 10;
    }
    puVar1[4] = puVar1[4] + (char)local_10;
  }
  return param_2;
}
```

---

---

## FUN_00478b60 — 0x478b60

- Classification : internal
- Corps : `0x478b60–0x478ce7`
- État : pseudocode obtenu
- Evidence : `ev_7ea1fe0ba2958011a0fe18926f1ab2a5dc45d7bb3949bdcf6fa2b52b55b70d08`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b20` — `_memset`
- `0x478ec0` — `__shift`
- `0x482f30` — `FUN_00482f30`
- `0x483020` — `FUN_00483020`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined1 * FUN_00478b60(undefined4 *param_1,undefined1 *param_2,size_t param_3)

{
  int iVar1;
  size_t local_18;
  int *local_c;
  undefined1 *local_8;
  
  if (DAT_00632580 == '\0') {
    local_c = (int *)FUN_00483020(*param_1,param_1[1]);
    FUN_00482f30(param_2 + (*local_c == 0x2d),param_3 + local_c[1],local_c);
  }
  else {
    local_c = DAT_0063257c;
    if (DAT_00632584 == param_3) {
      iVar1 = DAT_00632584 + (*DAT_0063257c == 0x2d);
      param_2[iVar1] = 0x30;
      (param_2 + iVar1)[1] = 0;
    }
  }
  local_8 = param_2;
  if (*local_c == 0x2d) {
    *param_2 = 0x2d;
    local_8 = param_2 + 1;
  }
  if (local_c[1] < 1) {
    __shift(local_8,1);
    *local_8 = 0x30;
    local_8 = local_8 + 1;
  }
  else {
    local_8 = local_8 + local_c[1];
  }
  if (0 < (int)param_3) {
    __shift(local_8,1);
    *local_8 = DAT_004a87f8;
    if (local_c[1] < 0) {
      if (DAT_00632580 == '\0') {
        if ((int)param_3 < -local_c[1]) {
          local_18 = param_3;
        }
        else {
          local_18 = -local_c[1];
        }
        param_3 = local_18;
      }
      else {
        param_3 = -local_c[1];
      }
      __shift(local_8 + 1,param_3);
      _memset(local_8 + 1,0x30,param_3);
    }
  }
  return param_2;
}
```

---

---

## FUN_00478cf0 — 0x478cf0

- Classification : internal
- Corps : `0x478cf0–0x478de3`
- État : pseudocode obtenu
- Evidence : `ev_42d78b5301a8a6f5f37bddac1be152a8a6757ef8e78fab6e1746e8f646907481`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x478df0` — `__cftoe_g`
- `0x478e30` — `__cftof_g`
- `0x482f30` — `FUN_00482f30`
- `0x483020` — `FUN_00483020`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00478cf0(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  char *pcVar1;
  char *local_8;
  
  DAT_0063257c = (int *)FUN_00483020(*param_1,param_1[1]);
  DAT_00632584 = DAT_0063257c[1] + -1;
  pcVar1 = (char *)(param_2 + (uint)(*DAT_0063257c == 0x2d));
  FUN_00482f30(pcVar1,param_3,DAT_0063257c);
  DAT_00632588 = DAT_00632584 < DAT_0063257c[1] + -1;
  DAT_00632584 = DAT_0063257c[1] + -1;
  if ((DAT_00632584 < -4) || (param_3 <= DAT_00632584)) {
    __cftoe_g(param_1,param_2,param_3,param_4);
  }
  else {
    if ((bool)DAT_00632588) {
      do {
        local_8 = pcVar1;
        pcVar1 = local_8 + 1;
      } while (*local_8 != '\0');
      local_8[-1] = '\0';
    }
    __cftof_g(param_1,param_2,param_3);
  }
  return;
}
```

---

## __cftoe_g — 0x478df0

- Classification : internal
- Corps : `0x478df0–0x478e23`
- État : pseudocode obtenu
- Evidence : `ev_3a2cd6c8f799ae088c327e44e1ec198fe0e46dad6610fc9fceb636d9797b71c5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4789a0` — `FUN_004789a0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __cftoe_g
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

undefined4 __cftoe_g(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  DAT_00632580 = 1;
  uVar1 = FUN_004789a0(param_1,param_2,param_3,param_4);
  DAT_00632580 = 0;
  return uVar1;
}
```

---

## __cftof_g — 0x478e30

- Classification : internal
- Corps : `0x478e30–0x478e5f`
- État : pseudocode obtenu
- Evidence : `ev_0e9430a336a14fcc540373685b447d40b47ec9878fa5047c4b87e859bef5eee9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x478b60` — `FUN_00478b60`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __cftof_g
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

undefined4 __cftof_g(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  DAT_00632580 = 1;
  uVar1 = FUN_00478b60(param_1,param_2,param_3);
  DAT_00632580 = 0;
  return uVar1;
}
```

---

## __cfltcvt — 0x478e60

- Classification : internal
- Corps : `0x478e60–0x478ebe`
- État : pseudocode obtenu
- Evidence : `ev_c7a5fda57141e682da58a26083b0ae413ca6f3a83c2e25b83ce5be99a607aedb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4789a0` — `FUN_004789a0`
- `0x478b60` — `FUN_00478b60`
- `0x478cf0` — `FUN_00478cf0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __cfltcvt
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

errno_t __cdecl
__cfltcvt(double *arg,char *buffer,size_t sizeInBytes,int format,int precision,int caps)

{
  errno_t eVar1;
  
  if ((sizeInBytes == 0x65) || (sizeInBytes == 0x45)) {
    eVar1 = FUN_004789a0(arg,buffer,format,precision);
  }
  else if (sizeInBytes == 0x66) {
    eVar1 = FUN_00478b60(arg,buffer,format);
  }
  else {
    eVar1 = FUN_00478cf0(arg,buffer,format,precision);
  }
  return eVar1;
}
```

---

## __shift — 0x478ec0

- Classification : internal
- Corps : `0x478ec0–0x478eed`
- État : pseudocode obtenu
- Evidence : `ev_6acd31d87c3db8309e3f0f0088f091072040a3299771f97298bdc77bbcb797eb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472e90` — `_strlen`
- `0x483210` — `FUN_00483210`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __shift
   
   Library: Visual Studio */

void __shift(char *param_1,int param_2)

{
  size_t sVar1;
  
  if (param_2 != 0) {
    sVar1 = _strlen(param_1);
    FUN_00483210(param_1 + param_2,param_1,sVar1 + 1);
  }
  return;
}
```

---

---

## FUN_00478ef0 — 0x478ef0

- Classification : internal
- Corps : `0x478ef0–0x479161`
- État : pseudocode obtenu
- Evidence : `ev_39ec45eb041bf84998f074377015e1f43aebe0fd2a8ebf7674ca561ff3134019`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x478f1c with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x479072 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x4739b0` — `FUN_004739b0`
- `0x4745f0` — `FUN_004745f0`
- `0x47a120` — `FUN_0047a120`
- `0x483560` — `FUN_00483560`
- `0x483630` — `__isatty`

### Chaînes référencées

- `0x4951dc` — "str != NULL"
- `0x495a30` — "(\"inconsistent IOB fields\", stream->_ptr - stream->_base >= 0)"
- `0x495a70` — "_flsbuf.c"
- `0x495a70` — "_flsbuf.c"

### Pseudocode Ghidra

```c
uint FUN_00478ef0(uint param_1,int *param_2)

{
  code *pcVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  undefined *local_18;
  int local_10;
  int local_8;
  
  if ((param_2 == (int *)0x0) &&
     (iVar3 = FUN_0047a120(2,"_flsbuf.c",0x69,0,"str != NULL"), iVar3 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar4 = (*pcVar1)();
    return uVar4;
  }
  piVar2 = param_2;
  uVar4 = param_2[4];
  if (((param_2[3] & 0x82U) == 0) || ((param_2[3] & 0x40U) != 0)) {
    param_2[3] = param_2[3] | 0x20;
    param_1 = 0xffffffff;
  }
  else {
    if ((param_2[3] & 1U) != 0) {
      param_2[1] = 0;
      if ((param_2[3] & 0x10U) == 0) {
        param_2[3] = param_2[3] | 0x20;
        return 0xffffffff;
      }
      *param_2 = param_2[2];
      param_2[3] = param_2[3] & 0xfffffffe;
    }
    param_2[3] = param_2[3] | 2;
    param_2[3] = param_2[3] & 0xffffffef;
    param_2[1] = 0;
    local_10 = 0;
    if (((param_2[3] & 0x10cU) == 0) &&
       (((param_2 != (int *)&DAT_004a8b10 && (param_2 != (int *)&DAT_004a8b30)) ||
        (iVar3 = __isatty(uVar4), iVar3 == 0)))) {
      FUN_00483560(piVar2);
    }
    if ((piVar2[3] & 0x108U) == 0) {
      local_8 = 1;
      local_10 = FUN_004745f0(uVar4,&param_1,1);
    }
    else {
      if ((*piVar2 - piVar2[2] < 0) &&
         (iVar3 = FUN_0047a120(2,"_flsbuf.c",0xa0,0,
                               "(\"inconsistent IOB fields\", stream->_ptr - stream->_base >= 0)"),
         iVar3 == 1)) {
        pcVar1 = (code *)swi(3);
        uVar4 = (*pcVar1)();
        return uVar4;
      }
      local_8 = *piVar2 - piVar2[2];
      *piVar2 = piVar2[2] + 1;
      piVar2[1] = piVar2[6] + -1;
      if (local_8 < 1) {
        if (uVar4 == 0xffffffff) {
          local_18 = &DAT_004a65b0;
        }
        else {
          local_18 = (undefined *)((&DAT_00633d20)[(int)uVar4 >> 5] + (uVar4 & 0x1f) * 8);
        }
        if ((local_18[4] & 0x20) != 0) {
          FUN_004739b0(uVar4,0,2);
        }
      }
      else {
        local_10 = FUN_004745f0(uVar4,piVar2[2],local_8);
      }
      *(undefined1 *)piVar2[2] = (undefined1)param_1;
    }
    if (local_10 == local_8) {
      param_1 = param_1 & 0xff;
    }
    else {
      piVar2[3] = piVar2[3] | 0x20;
      param_1 = 0xffffffff;
    }
  }
  return param_1;
}
```

---

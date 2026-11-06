# 0018_batch_0014 — détails (2/3)

## FUN_00472c00 — 0x472c00

- Classification : internal
- Corps : `0x472c00–0x472c40`
- État : pseudocode obtenu
- Evidence : `ev_ceb54230c92ccddd61f6294165b0e7cd59fd8cfc85d7e518017e037061c16f7a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00472c00(void)

{
  PTR___fptrap_004a63d8 = __cfltcvt;
  PTR___fptrap_004a63dc = __cropzeros;
  PTR___fptrap_004a63e0 = __fassign;
  PTR___fptrap_004a63e4 = FUN_00478790;
  PTR___fptrap_004a63e8 = __positive;
  PTR___fptrap_004a63ec = __cfltcvt;
  return;
}
```

---

---

## FUN_00472c50 — 0x472c50

- Classification : internal
- Corps : `0x472c50–0x472c6b`
- État : pseudocode obtenu
- Evidence : `ev_cae1c33193953b883d8d02de43c77f596204b9e3a4edfb103b10f8a664916b8f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00472c50(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_00632500;
  DAT_00632500 = param_1;
  return uVar1;
}
```

---

## __ftol — 0x472c6c

- Classification : internal
- Corps : `0x472c6c–0x472c92`
- État : pseudocode obtenu
- Evidence : `ev_a0793f5d9552f14a7accb48cbf992564af87d834ce8fe8c91da7a4cfbdd76ad1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __ftol
   
   Library: Visual Studio */

longlong __ftol(void)

{
  float10 in_ST0;
  
  return (longlong)ROUND(in_ST0);
}
```

---

---

## FUN_00472ca0 — 0x472ca0

- Classification : internal
- Corps : `0x472ca0–0x472d99`
- État : pseudocode obtenu
- Evidence : `ev_b9a2edbaa37fdaf91eaf3a9974b929c7ca0d844bf067a202e822c6132ea711a6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x472cd8 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x472d02 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x478ef0` — `FUN_00478ef0`
- `0x479170` — `FUN_00479170`
- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x495197` — "`format != NULL"
- `0x4951a8` — "sprintf.c"
- `0x4951a8` — "sprintf.c"
- `0x4951b4` — "string != NULL"

### Pseudocode Ghidra

```c
undefined4 FUN_00472ca0(undefined1 *param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *local_24;
  int local_20;
  undefined1 *local_1c;
  undefined4 local_18;
  
  if ((param_1 == (undefined1 *)0x0) &&
     (iVar2 = FUN_0047a120(2,"sprintf.c",0x5d,0,"string != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == 0) && (iVar2 = FUN_0047a120(2,"sprintf.c",0x5e,0,"format != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  local_18 = 0x42;
  local_1c = param_1;
  local_24 = param_1;
  local_20 = 0x7fffffff;
  uVar3 = FUN_00479170(&local_24,param_2,&stack0x0000000c);
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

## FUN_00472da0 — 0x472da0

- Classification : internal
- Corps : `0x472da0–0x472da6`
- État : pseudocode obtenu
- Evidence : `ev_2570964e2781fa14b34f024cdacdec88d18dfea602f7fc25c899f9a6c4a1c735`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint * FUN_00472da0(uint *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  
  puVar4 = param_1;
  while (((uint)param_2 & 3) != 0) {
    bVar1 = (byte)*param_2;
    uVar3 = (uint)bVar1;
    param_2 = (uint *)((int)param_2 + 1);
    if (bVar1 == 0) goto LAB_00472e88;
    *(byte *)puVar4 = bVar1;
    puVar4 = (uint *)((int)puVar4 + 1);
  }
  do {
    uVar2 = *param_2;
    uVar3 = *param_2;
    param_2 = param_2 + 1;
    if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
      if ((char)uVar3 == '\0') {
LAB_00472e88:
        *(byte *)puVar4 = (byte)uVar3;
        return param_1;
      }
      if ((char)(uVar3 >> 8) == '\0') {
        *(short *)puVar4 = (short)uVar3;
        return param_1;
      }
      if ((uVar3 & 0xff0000) == 0) {
        *(short *)puVar4 = (short)uVar3;
        *(byte *)((int)puVar4 + 2) = 0;
        return param_1;
      }
      if ((uVar3 & 0xff000000) == 0) {
        *puVar4 = uVar3;
        return param_1;
      }
    }
    *puVar4 = uVar3;
    puVar4 = puVar4 + 1;
  } while( true );
}
```

---

---

## FUN_00472db0 — 0x472db0

- Classification : internal
- Corps : `0x472db0–0x472e8f`
- État : pseudocode obtenu
- Evidence : `ev_61e9baf158f6bd654333f1caa98d91b51d950194ca7e94bcf37929bf17723cfe`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint * FUN_00472db0(uint *param_1,uint *param_2)

{
  byte bVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  
  puVar3 = param_1;
  do {
    if (((uint)puVar3 & 3) == 0) goto LAB_00472dcc;
    uVar4 = *puVar3;
    puVar3 = (uint *)((int)puVar3 + 1);
  } while ((byte)uVar4 != 0);
  goto LAB_00472dff;
  while( true ) {
    if ((uVar4 & 0xff0000) == 0) {
      puVar5 = (uint *)((int)puVar5 + 2);
      goto joined_r0x00472e1b;
    }
    if ((uVar4 & 0xff000000) == 0) break;
LAB_00472dcc:
    do {
      puVar5 = puVar3;
      puVar3 = puVar5 + 1;
    } while (((*puVar5 ^ 0xffffffff ^ *puVar5 + 0x7efefeff) & 0x81010100) == 0);
    uVar4 = *puVar5;
    if ((char)uVar4 == '\0') goto joined_r0x00472e1b;
    if ((char)(uVar4 >> 8) == '\0') {
      puVar5 = (uint *)((int)puVar5 + 1);
      goto joined_r0x00472e1b;
    }
  }
LAB_00472dff:
  puVar5 = (uint *)((int)puVar3 + -1);
joined_r0x00472e1b:
  do {
    if (((uint)param_2 & 3) == 0) {
      do {
        uVar2 = *param_2;
        uVar4 = *param_2;
        param_2 = param_2 + 1;
        if (((uVar2 ^ 0xffffffff ^ uVar2 + 0x7efefeff) & 0x81010100) != 0) {
          if ((char)uVar4 == '\0') {
LAB_00472e88:
            *(byte *)puVar5 = (byte)uVar4;
            return param_1;
          }
          if ((char)(uVar4 >> 8) == '\0') {
            *(short *)puVar5 = (short)uVar4;
            return param_1;
          }
          if ((uVar4 & 0xff0000) == 0) {
            *(short *)puVar5 = (short)uVar4;
            *(byte *)((int)puVar5 + 2) = 0;
            return param_1;
          }
          if ((uVar4 & 0xff000000) == 0) {
            *puVar5 = uVar4;
            return param_1;
          }
        }
        *puVar5 = uVar4;
        puVar5 = puVar5 + 1;
      } while( true );
    }
    bVar1 = (byte)*param_2;
    uVar4 = (uint)bVar1;
    param_2 = (uint *)((int)param_2 + 1);
    if (bVar1 == 0) goto LAB_00472e88;
    *(byte *)puVar5 = bVar1;
    puVar5 = (uint *)((int)puVar5 + 1);
  } while( true );
}
```

---

## _strlen — 0x472e90

- Classification : internal
- Corps : `0x472e90–0x472f0a`
- État : pseudocode obtenu
- Evidence : `ev_cd7e36152c2104f087fd37f2a9255d5daf482eac00cdf922e936dc1ebbc1f93f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _strlen
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

size_t __cdecl _strlen(char *_Str)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  
  puVar2 = (uint *)_Str;
  do {
    if (((uint)puVar2 & 3) == 0) goto LAB_00472eb0;
    uVar1 = *puVar2;
    puVar2 = (uint *)((int)puVar2 + 1);
  } while ((char)uVar1 != '\0');
LAB_00472ee3:
  return (size_t)((int)puVar2 + (-1 - (int)_Str));
LAB_00472eb0:
  do {
    do {
      puVar3 = puVar2;
      puVar2 = puVar3 + 1;
    } while (((*puVar3 ^ 0xffffffff ^ *puVar3 + 0x7efefeff) & 0x81010100) == 0);
    uVar1 = *puVar3;
    if ((char)uVar1 == '\0') {
      return (int)puVar3 - (int)_Str;
    }
    if ((char)(uVar1 >> 8) == '\0') {
      return (size_t)((int)puVar3 + (1 - (int)_Str));
    }
    if ((uVar1 & 0xff0000) == 0) {
      return (size_t)((int)puVar3 + (2 - (int)_Str));
    }
  } while ((uVar1 & 0xff000000) != 0);
  goto LAB_00472ee3;
}
```

---

---

## FUN_00472f10 — 0x472f10

- Classification : internal
- Corps : `0x472f10–0x472fc6`
- État : pseudocode obtenu
- Evidence : `ev_cea34855829536b2d246faa4145c946c44fc96e7b9141e1dd3329f62f8a64eb0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x472f48 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x472f72 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x472e90` — `_strlen`
- `0x47a120` — `FUN_0047a120`
- `0x47a7c0` — `FUN_0047a7c0`

### Chaînes référencées

- `0x495197` — "`format != NULL"
- `0x4951b4` — "string != NULL"
- `0x4951c4` — "sscanf.c"
- `0x4951c4` — "sscanf.c"

### Pseudocode Ghidra

```c
undefined4 FUN_00472f10(char *param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  char *local_24;
  size_t local_20;
  char *local_1c;
  undefined4 local_18;
  
  if ((param_1 == (char *)0x0) &&
     (iVar2 = FUN_0047a120(2,"sscanf.c",0x42,0,"string != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  if ((param_2 == 0) && (iVar2 = FUN_0047a120(2,"sscanf.c",0x43,0,"format != NULL"), iVar2 == 1)) {
    pcVar1 = (code *)swi(3);
    uVar3 = (*pcVar1)();
    return uVar3;
  }
  local_18 = 0x49;
  local_1c = param_1;
  local_24 = param_1;
  local_20 = _strlen(param_1);
  uVar3 = FUN_0047a7c0(&local_24,param_2,&stack0x0000000c);
  return uVar3;
}
```

---

---

## FUN_00472fd0 — 0x472fd0

- Classification : internal
- Corps : `0x472fd0–0x472ffc`
- État : pseudocode obtenu
- Evidence : `ev_b8cce2b1057429b660467629de7dba42a66246bfd5a4f404c8fbfb79b3acce0d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00472fd0(code *UNRECOVERED_JUMPTABLE)

{
  undefined4 *unaff_FS_OFFSET;
  
  *unaff_FS_OFFSET = *(undefined4 *)*unaff_FS_OFFSET;
                    /* WARNING: Could not recover jumptable at 0x00472ffb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}
```

---

## _CallMemberFunction0 — 0x473010

- Classification : internal
- Corps : `0x473010–0x473016`
- État : pseudocode obtenu
- Evidence : `ev_191e2460bfa8559f4165147b835b99082405885f728d865261bcd815e58658d1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    void __stdcall _CallMemberFunction0(void *,void *)
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

void _CallMemberFunction0(void *param_1,void *param_2)

{
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x00473015. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*param_2)();
  return;
}
```

---

---

## FUN_00473020 — 0x473020

- Classification : internal
- Corps : `0x473020–0x473026`
- État : pseudocode obtenu
- Evidence : `ev_cff058bdba1d1bb62efe7ef85f35eb8d401b5c9319a20473eabbece225b94f02`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00473020(undefined4 param_1,code *UNRECOVERED_JUMPTABLE)

{
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x00473025. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}
```

---

---

## FUN_00473030 — 0x473030

- Classification : internal
- Corps : `0x473030–0x473036`
- État : pseudocode obtenu
- Evidence : `ev_31bf063a2cab62d51e68c0545ef629898ca8698356071567dd242e8d68a37058`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00473030(undefined4 param_1,code *UNRECOVERED_JUMPTABLE)

{
  LOCK();
  UNLOCK();
                    /* WARNING: Could not recover jumptable at 0x00473035. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}
```

---

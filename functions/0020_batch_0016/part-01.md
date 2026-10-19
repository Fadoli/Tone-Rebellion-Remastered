# 0020_batch_0016 — détails (1/6)

## FUN_004782b0 — 0x4782b0

- Classification : internal
- Corps : `0x4782b0–0x478324`
- État : pseudocode obtenu
- Evidence : `ev_06cfea6f976a34b239a438a4f4f6be00af652ed6870af6c086d8798f40b9a00a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x478323 to 0x478341 FUN_00478341 (external=false, thunk=false, hasNoReturn=false); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.

### Appels directs

- `0x478325` — `FUN_00478325`
- `0x478341` — `FUN_00478341`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004782b0(undefined4 param_1,undefined4 param_2,int param_3,code *param_4)

{
  undefined4 unaff_EBX;
  undefined4 unaff_ESI;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar1;
  undefined4 uStack_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_004959c0;
  puStack_10 = &LAB_00480ac8;
  uStack_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_14;
  local_8 = 0;
  while( true ) {
    param_3 = param_3 + -1;
    if (param_3 < 0) break;
    (*param_4)();
  }
  uVar1 = 1;
  local_8 = 0xffffffff;
  FUN_00478325();
  FUN_00478341(unaff_ESI,unaff_EBX,uVar1);
  return;
}
```

---

## FUN_00478325 — 0x478325

- Classification : internal
- Corps : `0x478325–0x478340`
- État : pseudocode obtenu
- Evidence : `ev_b9e532010de014dee0decfe783c0ab60f189a798346dd2de7108a8b5b442d558`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x478360` — `FUN_00478360`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00478325(void)

{
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -0x1c) == 0) {
    FUN_00478360(*(undefined4 *)(unaff_EBP + 8),*(undefined4 *)(unaff_EBP + 0xc),
                 *(undefined4 *)(unaff_EBP + 0x10),*(undefined4 *)(unaff_EBP + 0x14));
  }
  return;
}
```

---

## FUN_00478341 — 0x478341

- Classification : internal
- Corps : `0x478341–0x478353`
- État : pseudocode obtenu
- Evidence : `ev_915cb5fe9d59b74077098fa881907b2fe291b950479c2cf975380526c75de34e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00478341(void)

{
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET;
  
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return;
}
```

---

## FUN_00478360 — 0x478360

- Classification : internal
- Corps : `0x478360–0x4783b5`, `0x4783cd–0x4783df`
- État : pseudocode obtenu
- Evidence : `ev_3c29517498e555b7d786e67ed5de09cbe7f7278f25aea8c6ea2e17d6d963f179`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00478360(undefined4 param_1,undefined4 param_2,int param_3,code *param_4)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_004959d0;
  puStack_10 = &LAB_00480ac8;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  local_8 = 0;
  while (param_3 = param_3 + -1, -1 < param_3) {
    (*param_4)();
  }
  *unaff_FS_OFFSET = local_14;
  return;
}
```

---

## ArrayUnwindFilter — 0x4783e0

- Classification : internal
- Corps : `0x4783e0–0x47840b`
- État : pseudocode obtenu
- Evidence : `ev_a3bc6560efeb64d8468277ceddc6020f874e74f5a850ed5c0dfb8adac139b35d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47c980` — `FUN_0047c980`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    int __cdecl ArrayUnwindFilter(struct _EXCEPTION_POINTERS *)
   
   Library: Visual Studio */

int __cdecl ArrayUnwindFilter(_EXCEPTION_POINTERS *param_1)

{
  if (param_1->ExceptionRecord->ExceptionCode == 0xe06d7363) {
    FUN_0047c980();
  }
  return 0;
}
```

---

## FUN_00478410 — 0x478410

- Classification : internal
- Corps : `0x478410–0x47843e`
- État : pseudocode obtenu
- Evidence : `ev_008612ff6977bf47b10cef788119a259393a1cac94b70e9fa103d2dcdf674a49`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Unable to track spacebase fully for stack */

void FUN_00478410(void)

{
  uint in_EAX;
  undefined1 *puVar1;
  undefined4 unaff_retaddr;
  
  puVar1 = &stack0x00000004;
  for (; 0xfff < in_EAX; in_EAX = in_EAX - 0x1000) {
    puVar1 = puVar1 + -0x1000;
  }
  *(undefined4 *)(puVar1 + (-4 - in_EAX)) = unaff_retaddr;
  return;
}
```

---

## FUN_00478440 — 0x478440

- Classification : internal
- Corps : `0x478440–0x478452`
- État : pseudocode obtenu
- Evidence : `ev_244c47e1e6dc44e11e2988347bcc049031b63d7fb1a4343191b3b2bd663c7f06`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474d70` — `__nh_malloc`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00478440(size_t param_1)

{
  __nh_malloc(param_1,1);
  return;
}
```

---

## __amsg_exit — 0x478690

- Classification : internal
- Corps : `0x478690–0x4786b7`
- État : pseudocode obtenu
- Evidence : `ev_b74fb1bfcb20625e672c6d0f69c4a95e70085d94abefa0b28b93bcd4dba98144`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x4786b2 to 0x476ec0 __exit (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `0x476ec0` — `__exit`
- `0x481ed0` — `__FF_MSGBANNER`
- `0x481f20` — `FUN_00481f20`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __amsg_exit
   
   Library: Visual Studio 2003 Debug */

void __cdecl __amsg_exit(int param_1)

{
  if (DAT_00632578 == 1) {
    __FF_MSGBANNER();
  }
  FUN_00481f20(param_1);
  (*(code *)PTR___exit_004a63d0)(0xff);
  return;
}
```

---

## __setdefaultprecision — 0x4786c0

- Classification : internal
- Corps : `0x4786c0–0x4786d6`
- État : pseudocode obtenu
- Evidence : `ev_3cca6436c6f2032fbb1322a56a8efc7020443e9c3088bfc1d354b57234c91400`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482200` — `__controlfp`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __setdefaultprecision
   
   Library: Visual Studio 2003 Debug */

void __setdefaultprecision(void)

{
  __controlfp(0x10000,0x30000);
  return;
}
```

---

## FUN_004786e0 — 0x4786e0

- Classification : internal
- Corps : `0x4786e0–0x47873d`
- État : pseudocode obtenu
- Evidence : `ev_e2a00234dda4c1e4c0a3b4a0f7d9218871019932b51a6f975755e442d64cbad1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Removing unreachable block (ram,0x00478724) */

undefined4 FUN_004786e0(void)

{
  return 0;
}
```

---

## __ms_p5_mp_test_fdiv — 0x478740

- Classification : internal
- Corps : `0x478740–0x478781`
- État : pseudocode obtenu
- Evidence : `ev_27334ed2c06803bdb3a4a217b59ae49b62eb8eb5947918b00ccff490e9be907c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x40` — `KERNEL32.DLL::GetModuleHandleA`
- `EXTERNAL:0x4b` — `KERNEL32.DLL::GetProcAddress`
- `0x4786e0` — `FUN_004786e0`

### Chaînes référencées

- `0x4959f7` — "?IsProcessorFeaturePresent"
- `0x495a14` — "KERNEL32"

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __ms_p5_mp_test_fdiv
   
   Libraries: Visual Studio 2003, Visual Studio 2005, Visual Studio 2008 */

void __ms_p5_mp_test_fdiv(void)

{
  HMODULE hModule;
  FARPROC pFVar1;
  
  hModule = GetModuleHandleA("KERNEL32");
  if ((hModule != (HMODULE)0x0) &&
     (pFVar1 = GetProcAddress(hModule,"IsProcessorFeaturePresent"), pFVar1 != (FARPROC)0x0)) {
    (*pFVar1)(0);
    return;
  }
  FUN_004786e0();
  return;
}
```

---

## FUN_00478790 — 0x478790

- Classification : internal
- Corps : `0x478790–0x478837`
- État : pseudocode obtenu
- Evidence : `ev_eb9b5a2bb0610e26c104d2222ba6b98323d716f0f2da667e769fd82547d0c305`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`
- `0x482620` — `FUN_00482620`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00478790(char *param_1)

{
  char cVar1;
  int iVar2;
  uint local_10;
  char local_c;
  
  iVar2 = FUN_00482620((int)*param_1);
  if (iVar2 != 0x65) {
    do {
      param_1 = param_1 + 1;
      if (DAT_004a87f4 < 2) {
        local_10 = *(ushort *)(PTR_DAT_004a85e8 + *param_1 * 2) & 4;
      }
      else {
        local_10 = FUN_0047f2b0((int)*param_1,4);
      }
    } while (local_10 != 0);
  }
  local_c = *param_1;
  *param_1 = DAT_004a87f8;
  do {
    param_1 = param_1 + 1;
    cVar1 = *param_1;
    *param_1 = local_c;
    local_c = cVar1;
  } while (*param_1 != '\0');
  return;
}
```

---

## __cropzeros — 0x478840

- Classification : internal
- Corps : `0x478840–0x478916`
- État : pseudocode obtenu
- Evidence : `ev_b9511f81bd58ec738f63a2054be5f0b4856b0d6b74385a25a810388b3366e60d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __cropzeros
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

void __cdecl __cropzeros(char *_Buf)

{
  char *pcVar1;
  char *local_8;
  
  for (; (*_Buf != '\0' && (*_Buf != DAT_004a87f8)); _Buf = _Buf + 1) {
  }
  if (*_Buf != '\0') {
    do {
      pcVar1 = _Buf;
      _Buf = pcVar1 + 1;
      if ((*_Buf == '\0') || (*_Buf == 'e')) break;
    } while (*_Buf != 'E');
    local_8 = _Buf;
    for (_Buf = pcVar1; *_Buf == '0'; _Buf = _Buf + -1) {
    }
    if (*_Buf == DAT_004a87f8) {
      _Buf = _Buf + -1;
    }
    do {
      _Buf = _Buf + 1;
      *_Buf = *local_8;
      local_8 = local_8 + 1;
    } while (*_Buf != '\0');
  }
  return;
}
```

---

## __positive — 0x478920

- Classification : internal
- Corps : `0x478920–0x47894c`
- État : pseudocode obtenu
- Evidence : `ev_6a9bad41ce0e7519f3435340d083a747df3fde072a2bebfe961454a82a60e19b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __positive
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

int __cdecl __positive(double *arg)

{
  uint local_8;
  
  local_8 = (uint)(0.0 <= *arg);
  return local_8;
}
```

---

## __fassign — 0x478950

- Classification : internal
- Corps : `0x478950–0x478997`
- État : pseudocode obtenu
- Evidence : `ev_97e72a8507ae07a13bf720805c02c02c92993906d0c4513ba6d7173a4b1c38b5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482e70` — `FUN_00482e70`
- `0x482ef0` — `FUN_00482ef0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __fassign
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

void __cdecl __fassign(int flag,char *argument,char *number)

{
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (flag == 0) {
    FUN_00482ef0(&local_10,number);
    *(undefined4 *)argument = local_10;
  }
  else {
    FUN_00482e70(&local_c,number);
    *(undefined4 *)argument = local_c;
    *(undefined4 *)(argument + 4) = local_8;
  }
  return;
}
```

---

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


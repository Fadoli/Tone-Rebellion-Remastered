# 0020_batch_0016 — détails (2/2)

## FUN_00479fb0 — 0x479fb0

- Classification : internal
- Corps : `0x479fb0–0x479fc9`
- État : pseudocode obtenu
- Evidence : `ev_9a9b6b23560c3a05e07f0e3b5ba501eca62c76762f07ec2088ce44c870d8a828`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00479fb0(int *param_1)

{
  *param_1 = *param_1 + 4;
  return *(undefined4 *)(*param_1 + -4);
}
```

---

---

## FUN_00479fd0 — 0x479fd0

- Classification : internal
- Corps : `0x479fd0–0x479fee`
- État : pseudocode obtenu
- Evidence : `ev_9548d47b7057b486d40e12572030ee81ab078a1fa5a95b0dd0f72b48ed0a4808`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined8 FUN_00479fd0(int *param_1)

{
  *param_1 = *param_1 + 8;
  return *(undefined8 *)(*param_1 + -8);
}
```

---

---

## FUN_00479ff0 — 0x479ff0

- Classification : internal
- Corps : `0x479ff0–0x47a00a`
- État : pseudocode obtenu
- Evidence : `ev_ccacfaed8480adf27b2a9c4b512ba749e41fabf616fe8c8d7961ea0bc7566dd4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined2 FUN_00479ff0(int *param_1)

{
  *param_1 = *param_1 + 4;
  return *(undefined2 *)(*param_1 + -4);
}
```

---

---

## FUN_0047a010 — 0x47a010

- Classification : internal
- Corps : `0x47a010–0x47a01a`
- État : pseudocode obtenu
- Evidence : `ev_c7b17768fbc008da001606feedba2545588265add1dffbea588c958e619c7079`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x4c` — `KERNEL32.DLL::DebugBreak`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047a010(void)

{
  DebugBreak();
  return;
}
```

---

---

## FUN_0047a020 — 0x47a020

- Classification : internal
- Corps : `0x47a020–0x47a076`
- État : pseudocode obtenu
- Evidence : `ev_335a03427318fe9eb6c177dfb445614390db7f60a3f7f7de5b4ad984c112698f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047a020(int param_1,uint param_2)

{
  undefined4 uVar1;
  
  if ((param_1 < 0) || (2 < param_1)) {
    uVar1 = 0xffffffff;
  }
  else if (param_2 == 0xffffffff) {
    uVar1 = *(undefined4 *)(&DAT_004a6400 + param_1 * 4);
  }
  else if ((param_2 & 0xfffffff8) == 0) {
    uVar1 = *(undefined4 *)(&DAT_004a6400 + param_1 * 4);
    *(uint *)(&DAT_004a6400 + param_1 * 4) = param_2;
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}
```

---

## __CrtSetReportFile — 0x47a080

- Classification : internal
- Corps : `0x47a080–0x47a0fd`
- État : pseudocode obtenu
- Evidence : `ev_1e6e63dc590a4e6ec7b8c203d4639d075365258bb584132bdb49ffa0a451662e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xa` — `KERNEL32.DLL::GetStdHandle`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __CrtSetReportFile
   
   Library: Visual Studio 2003 Debug */

undefined4 __CrtSetReportFile(int param_1,int param_2)

{
  undefined4 uVar1;
  HANDLE pvVar2;
  
  if ((param_1 < 0) || (2 < param_1)) {
    uVar1 = 0xfffffffe;
  }
  else if (param_2 == -6) {
    uVar1 = *(undefined4 *)(&DAT_004a6410 + param_1 * 4);
  }
  else {
    uVar1 = *(undefined4 *)(&DAT_004a6410 + param_1 * 4);
    if (param_2 == -4) {
      pvVar2 = GetStdHandle(0xfffffff5);
      *(HANDLE *)(&DAT_004a6410 + param_1 * 4) = pvVar2;
    }
    else if (param_2 == -5) {
      pvVar2 = GetStdHandle(0xfffffff4);
      *(HANDLE *)(&DAT_004a6410 + param_1 * 4) = pvVar2;
    }
    else {
      *(int *)(&DAT_004a6410 + param_1 * 4) = param_2;
    }
  }
  return uVar1;
}
```

---

---

## FUN_0047a100 — 0x47a100

- Classification : internal
- Corps : `0x47a100–0x47a11b`
- État : pseudocode obtenu
- Evidence : `ev_61199866d9cb3baef38bb9f84194085e3aa6e12e242fed4bb742b9c876f96523`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047a100(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_00633e60;
  DAT_00633e60 = param_1;
  return uVar1;
}
```

---

---

## FUN_0047a120 — 0x47a120

- Classification : internal
- Corps : `0x47a120–0x47a4af`
- État : pseudocode obtenu
- Evidence : `ev_ce89ffd481495a12038f69d71ca415522524a9a4e41283f39b4263d78b9c8ff5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x3b` — `KERNEL32.DLL::WriteFile`
- `EXTERNAL:0x47` — `KERNEL32.DLL::LoadLibraryA`
- `EXTERNAL:0x48` — `KERNEL32.DLL::InterlockedIncrement`
- `EXTERNAL:0x4b` — `KERNEL32.DLL::GetProcAddress`
- `EXTERNAL:0x4d` — `KERNEL32.DLL::InterlockedDecrement`
- `EXTERNAL:0x4e` — `KERNEL32.DLL::OutputDebugStringA`
- `0x472da0` — `FUN_00472da0`
- `0x472db0` — `FUN_00472db0`
- `0x472e90` — `_strlen`
- `0x478410` — `FUN_00478410`
- `0x47a010` — `FUN_0047a010`
- `0x47a4b0` — `FUN_0047a4b0`
- `0x483940` — `__itoa`
- `0x483c10` — `FUN_00483c10`
- `0x483d10` — `FUN_00483d10`

### Chaînes référencées

- `0x495b34` — "%s(%d) : %s"
- `0x495b48` — "Assertion failed!"
- `0x495b48` — "Assertion failed!"
- `0x495b5c` — "Assertion failed: "
- `0x495b5c` — "Assertion failed: "
- `0x495b70` — "_CrtDbgReport: String too long or IO Error"
- `0x495b70` — "_CrtDbgReport: String too long or IO Error"
- `0x495b9c` — "Second Chance Assertion Failed: File %s, Line %d\n"
- `0x495bd0` — "wsprintfA"
- `0x495bdc` — "user32.dll"

### Pseudocode Ghidra

```c
undefined4 FUN_0047a120(int param_1,int param_2,int param_3,undefined4 param_4,int param_5)

{
  LONG LVar1;
  size_t nNumberOfBytesToWrite;
  int iVar2;
  undefined4 *puVar3;
  char local_3028 [20];
  DWORD local_3014;
  HMODULE local_3010;
  undefined1 local_300c;
  undefined4 local_300b;
  CHAR local_200c;
  undefined4 local_200b;
  undefined4 local_100c;
  undefined1 *local_1008;
  undefined1 local_1004;
  undefined4 local_1003;
  undefined4 uStackY_24;
  CHAR *pCStackY_20;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  
  FUN_00478410();
  local_300c = 0;
  puVar3 = &local_300b;
  for (iVar2 = 0x3ff; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = 0;
  *(undefined1 *)((int)puVar3 + 2) = 0;
  local_200c = '\0';
  puVar3 = &local_200b;
  for (iVar2 = 0x3ff; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = 0;
  *(undefined1 *)((int)puVar3 + 2) = 0;
  local_1004 = 0;
  puVar3 = &local_1003;
  for (iVar2 = 0x3ff; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = 0;
  *(undefined1 *)((int)puVar3 + 2) = 0;
  local_1008 = &stack0x00000018;
  if ((param_1 < 0) || (2 < param_1)) {
    local_100c = 0xffffffff;
  }
  else if ((param_1 == 2) && (LVar1 = InterlockedIncrement((LONG *)&DAT_004a63f8), 0 < LVar1)) {
    if ((DAT_0063258c == (FARPROC)0x0) &&
       ((local_3010 = LoadLibraryA("user32.dll"), local_3010 == (HMODULE)0x0 ||
        (DAT_0063258c = GetProcAddress(local_3010,"wsprintfA"), DAT_0063258c == (FARPROC)0x0)))) {
      local_100c = 0xffffffff;
    }
    else {
      (*DAT_0063258c)();
      OutputDebugStringA(&local_200c);
      InterlockedDecrement((LONG *)&DAT_004a63f8);
      FUN_0047a010();
      local_100c = 0xffffffff;
    }
  }
  else {
    if ((param_5 != 0) && (iVar2 = FUN_00483d10(), iVar2 < 0)) {
      FUN_00472da0();
    }
    if (param_1 == 2) {
      FUN_00472da0();
    }
    FUN_00472db0();
    if (param_1 == 2) {
      if ((uRam004a6408 & 1) != 0) {
        FUN_00472db0();
      }
      FUN_00472db0();
    }
    if (param_2 == 0) {
      FUN_00472da0();
    }
    else {
      pCStackY_20 = &local_200c;
      uStackY_24 = 0x47a335;
      iVar2 = FUN_00483c10();
      if (iVar2 < 0) {
        FUN_00472da0();
      }
    }
    if ((DAT_00633e60 == (code *)0x0) || (iVar2 = (*DAT_00633e60)(), iVar2 == 0)) {
      if (((*(uint *)(&DAT_004a6400 + param_1 * 4) & 1) != 0) &&
         (*(int *)(&DAT_004a6410 + param_1 * 4) != -1)) {
        lpOverlapped = (LPOVERLAPPED)0x0;
        lpNumberOfBytesWritten = &local_3014;
        nNumberOfBytesToWrite = _strlen(&local_200c);
        pCStackY_20 = (CHAR *)0x47a3fb;
        WriteFile(*(HANDLE *)(&DAT_004a6410 + param_1 * 4),&local_200c,nNumberOfBytesToWrite,
                  lpNumberOfBytesWritten,lpOverlapped);
      }
      if ((*(uint *)(&DAT_004a6400 + param_1 * 4) & 2) != 0) {
        OutputDebugStringA(&local_200c);
      }
      if ((*(uint *)(&DAT_004a6400 + param_1 * 4) & 4) == 0) {
        if (param_1 == 2) {
          InterlockedDecrement((LONG *)&DAT_004a63f8);
        }
        local_100c = 0;
      }
      else {
        if (param_3 != 0) {
          __itoa(param_3,local_3028,10);
        }
        pCStackY_20 = (CHAR *)0x47a476;
        local_100c = FUN_0047a4b0();
        if (param_1 == 2) {
          InterlockedDecrement((LONG *)&DAT_004a63f8);
        }
      }
    }
    else if (param_1 == 2) {
      InterlockedDecrement((LONG *)&DAT_004a63f8);
    }
  }
  return local_100c;
}
```

---

---

## FUN_0047a4b0 — 0x47a4b0

- Classification : internal
- Corps : `0x47a4b0–0x47a7a5`, `0x47a7a9–0x47a7be`
- État : pseudocode obtenu
- Evidence : `ev_131d3a234b1f6b518352821c8f242a5506996099a922fe69f1d01a989f744340`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x47a7a1 to 0x476ec0 __exit (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `EXTERNAL:0x3d` — `KERNEL32.DLL::GetModuleFileNameA`
- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`
- `0x4737e0` — `_strncpy`
- `0x476ec0` — `__exit`
- `0x478410` — `FUN_00478410`
- `0x47a010` — `FUN_0047a010`
- `0x47a120` — `FUN_0047a120`
- `0x483c10` — `FUN_00483c10`
- `0x484020` — `FUN_00484020`
- `0x484240` — `FUN_00484240`

### Chaînes référencées

- `0x495b70` — "_CrtDbgReport: String too long or IO Error"
- `0x495be8` — "Microsoft Visual C++ Debug Library"
- `0x495c0c` — "Debug %s!\n\nProgram: %s%s%s%s%s%s%s%s%s%s%s\n\n(Press Retry to debug the application)"
- `0x495c60` — "\nModule: "
- `0x495c60` — "\nModule: "
- `0x495c6c` — "\nFile: "
- `0x495c6c` — "\nFile: "
- `0x495c74` — "\nLine: "
- `0x495c74` — "\nLine: "
- `0x495c80` — "Expression: "
- `0x495c80` — "Expression: "
- `0x495c94` — "\n\nFor information on how your program can cause an assertion\nfailure, see the Visual C++ documentation on asserts."
- `0x495c94` — "\n\nFor information on how your program can cause an assertion\nfailure, see the Visual C++ documentation on asserts."
- `0x495c94` — "\n\nFor information on how your program can cause an assertion\nfailure, see the Visual C++ documentation on asserts."
- `0x495d0c` — "<program name unknown>"
- `0x495d24` — "dbgrpt.c"
- `0x495d30` — "szUserMessage != NULL"

### Pseudocode Ghidra

```c
bool FUN_0047a4b0(int param_1,undefined *param_2,undefined *param_3,char *param_4,char *param_5)

{
  int iVar1;
  DWORD DVar2;
  size_t sVar3;
  char *local_113c;
  char *local_1138;
  char *local_1134;
  undefined *local_1130;
  char *local_112c;
  undefined *local_1128;
  undefined *local_1124;
  char *local_1118;
  char *local_1114;
  undefined1 local_1110 [4096];
  int local_110;
  CHAR local_10c [200];
  undefined4 uStackY_44;
  undefined1 *puStackY_40;
  undefined4 uStackY_3c;
  char *pcStackY_38;
  undefined *puStackY_34;
  char *pcStackY_30;
  char *pcStackY_2c;
  char *pcStackY_28;
  char *pcStackY_24;
  undefined *puStackY_20;
  char *pcStackY_1c;
  undefined *puStackY_18;
  char *pcStackY_14;
  char *_Str;
  
  FUN_00478410();
  if (param_5 == (char *)0x0) {
    pcStackY_14 = "dbgrpt.c";
    puStackY_18 = (undefined *)0x2;
    pcStackY_1c = (char *)0x47a4db;
    iVar1 = FUN_0047a120();
    if (iVar1 == 1) {
      FUN_0047a010();
    }
  }
  pcStackY_14 = (char *)0x47a502;
  DVar2 = GetModuleFileNameA((HMODULE)0x0,local_10c,0x104);
  if (DVar2 == 0) {
    FUN_00472da0();
  }
  _Str = local_10c;
  sVar3 = _strlen(_Str);
  if (0x40 < sVar3) {
    _strlen(_Str);
    pcStackY_14 = (char *)0x47a55a;
    _strncpy((char *)0x3,"...",3);
  }
  local_1114 = param_4;
  if ((param_4 != (char *)0x0) && (sVar3 = _strlen(param_4), 0x40 < sVar3)) {
    sVar3 = _strlen(param_4);
    local_1114 = param_4 + (sVar3 - 0x40);
    pcStackY_14 = (char *)0x47a5b5;
    _strncpy(local_1114,"...",3);
  }
  if (param_1 == 2) {
    local_1118 = 
    "\n\nFor information on how your program can cause an assertion\nfailure, see the Visual C++ documentation on asserts."
    ;
  }
  else {
    local_1118 = "";
  }
  if (*param_5 == '\0') {
    local_1124 = &DAT_00495c90;
  }
  else {
    local_1124 = &DAT_00495c7c;
  }
  if (param_3 == (undefined *)0x0) {
    local_1128 = &DAT_00495c90;
    local_112c = "";
    puStackY_18 = local_1128;
  }
  else {
    local_112c = "\nLine: ";
    puStackY_18 = param_3;
  }
  if (param_2 == (undefined *)0x0) {
    local_1130 = &DAT_00495c90;
    local_1134 = "";
    puStackY_20 = local_1130;
  }
  else {
    local_1134 = "\nFile: ";
    puStackY_20 = param_2;
  }
  if (local_1114 == (char *)0x0) {
    local_1138 = "";
    local_113c = "";
    pcStackY_28 = local_1138;
  }
  else {
    local_113c = "\nModule: ";
    pcStackY_28 = local_1114;
  }
  pcStackY_14 = local_1124;
  pcStackY_1c = local_112c;
  pcStackY_24 = local_1134;
  pcStackY_2c = local_113c;
  pcStackY_30 = local_1118;
  puStackY_34 = (&PTR_s_Warning_004a6420)[param_1];
  pcStackY_38 = 
  "Debug %s!\n\nProgram: %s%s%s%s%s%s%s%s%s%s%s\n\n(Press Retry to debug the application)";
  uStackY_3c = 0x1000;
  puStackY_40 = local_1110;
  uStackY_44 = 0x47a752;
  iVar1 = FUN_00483c10();
  if (iVar1 < 0) {
    FUN_00472da0();
  }
  pcStackY_14 = (char *)0x47a783;
  local_110 = FUN_00484240();
  if (local_110 == 3) {
    FUN_00484020();
                    /* WARNING: Subroutine does not return */
    __exit(3);
  }
  return local_110 == 4;
}
```

---

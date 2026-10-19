# 0010_batch_0006 — détails (2/2)

## FUN_0041be72 — 0x41be72

- Classification : internal
- Corps : `0x41be72–0x41be8f`
- État : pseudocode obtenu
- Evidence : `ev_d343d41f1244ee040e61f8a4d3da92910a859bc86639fdbd7f3d6faa89ab18da`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x30` — `KERNEL32.DLL::QueryPerformanceCounter`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
DWORD FUN_0041be72(void)

{
  LARGE_INTEGER local_c;
  
  local_c.s.LowPart = 0;
  QueryPerformanceCounter(&local_c);
  return local_c.s.LowPart;
}
```

---

---

## FUN_0041be90 — 0x41be90

- Classification : internal
- Corps : `0x41be90–0x41beab`
- État : pseudocode obtenu
- Evidence : `ev_973991c304a020034aa3b93c0d258dd953801631ebac3d3ab1943d8866bb6199`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4017df` — `thunk_FUN_0041be72`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0041be90(int param_1)

{
  int iVar1;
  
  iVar1 = thunk_FUN_0041be72();
  return iVar1 - param_1;
}
```

---

---

## FUN_0041beac — 0x41beac

- Classification : internal
- Corps : `0x41beac–0x41bfab`
- État : pseudocode obtenu
- Evidence : `ev_1f8345cce760875dcff07b55349c8f6bc6275554669564f82d497c3288b3639f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x40150a` — `thunk_FUN_0040f9af`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401eba` — `thunk_FUN_0040f752`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0041beac(void)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  int local_18;
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049153c;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (DAT_004c2c34 == 0) {
    local_14 = 0;
    for (local_18 = 0; local_18 < 0xfa; local_18 = local_18 + 1) {
      if ((&DAT_0062e108)[local_18 * 0x1e] != '\0') {
        thunk_FUN_0040f6f7();
        local_8 = 0;
        thunk_FUN_0040f752(&DAT_0062e108 + local_18 * 0x1e,0x8000);
        iVar1 = thunk_FUN_0040f9af();
        DAT_004c2c34 = DAT_004c2c34 + iVar1;
        local_14 = local_14 + 1;
        if (DAT_0063071e < local_14) {
          local_8 = 0xffffffff;
          thunk_FUN_0040f73f();
          break;
        }
        local_8 = 0xffffffff;
        thunk_FUN_0040f73f();
      }
    }
  }
  iVar1 = DAT_004c2c34;
  *unaff_FS_OFFSET = local_10;
  return iVar1;
}
```

---

---

## FUN_0041bfac — 0x41bfac

- Classification : internal
- Corps : `0x41bfac–0x41bfd6`
- État : pseudocode obtenu
- Evidence : `ev_d548ee5099d234d352e270bd34cd8e8a80702ddef31ca9235fa35615c0bf16f7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x2e` — `KERNEL32.DLL::WriteConsoleA`
- `0x472e90` — `_strlen`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041bfac(char *param_1)

{
  size_t nNumberOfCharsToWrite;
  DWORD *lpNumberOfCharsWritten;
  LPVOID lpReserved;
  DWORD local_8;
  
  lpReserved = (LPVOID)0x0;
  lpNumberOfCharsWritten = &local_8;
  nNumberOfCharsToWrite = _strlen(param_1);
  WriteConsoleA(DAT_004c2c3c,param_1,nNumberOfCharsToWrite,lpNumberOfCharsWritten,lpReserved);
  return;
}
```

---

---

## FUN_0041bfd7 — 0x41bfd7

- Classification : internal
- Corps : `0x41bfd7–0x41c038`
- État : pseudocode obtenu
- Evidence : `ev_309b439c7eabc5ef54537ff603b3cee1a10a02b2027984d8a3bcfa503562f416`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x2b` — `KERNEL32.DLL::GetNumberOfConsoleInputEvents`
- `EXTERNAL:0x2c` — `KERNEL32.DLL::ReadConsoleA`
- `EXTERNAL:0x2d` — `KERNEL32.DLL::FlushConsoleInputBuffer`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_0041bfd7(void)

{
  DWORD local_c;
  uint local_8;
  
  local_c = 0;
  local_8 = 0;
  GetNumberOfConsoleInputEvents(DAT_004c2c38,&local_c);
  if (local_c != 0) {
    ReadConsoleA(DAT_004c2c38,&local_8,1,&local_c,(PCONSOLE_READCONSOLE_CONTROL)0x0);
    FlushConsoleInputBuffer(DAT_004c2c38);
  }
  return local_8 & 0xff;
}
```

---

---

## FUN_0041c039 — 0x41c039

- Classification : internal
- Corps : `0x41c039–0x41c145`
- État : pseudocode obtenu
- Evidence : `ev_b7e737694a76c9ea1f4178ef4c8e2ecb7779d7a6da57da6f5469bd00e1551f7c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x9` — `KERNEL32.DLL::AllocConsole`
- `EXTERNAL:0xa` — `KERNEL32.DLL::GetStdHandle`
- `EXTERNAL:0xb` — `KERNEL32.DLL::SetConsoleMode`
- `EXTERNAL:0x35` — `KERNEL32.DLL::FreeConsole`
- `0x401bc2` — `thunk_FUN_0041bfd7`
- `0x401c58` — `thunk_FUN_0041bfac`
- `0x472ca0` — `FUN_00472ca0`
- `0x474b20` — `_memset`
- `0x474d20` — `FUN_00474d20`
- `0x475760` — `FUN_00475760`

### Chaînes référencées

- `0x49c9f8` — "Starting Mallocs.\n\n"
- `0x49ca0c` — "%d megs.\n"

### Pseudocode Ghidra

```c
void FUN_0041c039(void)

{
  void *_Dst;
  char local_24;
  undefined1 local_20 [20];
  int local_c;
  int local_8;
  
  AllocConsole();
  DAT_004c2c3c = GetStdHandle(0xfffffff5);
  DAT_004c2c38 = GetStdHandle(0xfffffff6);
  SetConsoleMode(DAT_004c2c38,0);
  thunk_FUN_0041bfac(s_Starting_Mallocs__0049c9f8);
  local_8 = 1;
  local_c = 0;
  while (local_c == 0) {
    FUN_00472ca0(local_20,s__d_megs__0049ca0c,local_8);
    _Dst = (void *)FUN_00474d20(local_8 << 0x14);
    local_24 = '\0';
    while (local_24 == '\0') {
      thunk_FUN_0041bfac(local_20);
      _memset(_Dst,0,local_8 << 0x14);
      local_24 = thunk_FUN_0041bfd7();
    }
    if ((local_24 < '1') || ('9' < local_24)) {
      local_8 = local_8 + 1;
    }
    else {
      local_8 = local_8 + -0x30 + (int)local_24;
    }
    if (local_24 == 'q') {
      local_c = 1;
    }
    FUN_00475760(_Dst);
  }
  FreeConsole();
  return;
}
```

---

---

## FUN_0041c146 — 0x41c146

- Classification : internal
- Corps : `0x41c146–0x41c180`
- État : pseudocode obtenu
- Evidence : `ev_8c65491e4dc6f8d86b543ba46cfe1e538cc16014bee4777d9000939de5fd1d11`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402298` — `thunk_FUN_00414ad0`
- `0x4737e0` — `_strncpy`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041c146(char *param_1)

{
  if (param_1 == (char *)0x0) {
    DAT_004c2bd0 = 0;
  }
  else {
    _strncpy(&DAT_004c2bd0,param_1,100);
    DAT_004c2c33 = 0;
    thunk_FUN_00414ad0(&DAT_004c2bd0);
  }
  return;
}
```

---

---

## FUN_0041c181 — 0x41c181

- Classification : internal
- Corps : `0x41c181–0x41c1d5`
- État : pseudocode obtenu
- Evidence : `ev_c726a273b363fd7769f6b98bb6a0fb90f454b1cc5c2da0d264a1175c0aaaca75`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x54` — `USER32.DLL::LoadCursorA`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041c181(HINSTANCE param_1)

{
  HCURSOR pHVar1;
  int local_8;
  
  _memset(&DAT_004c2b10,0,0x44);
  for (local_8 = 0; local_8 < 0x11; local_8 = local_8 + 1) {
    pHVar1 = LoadCursorA(param_1,(LPCSTR)(uint)*(ushort *)(&DAT_0049c950 + local_8 * 4));
    (&DAT_004c2b10)[local_8] = pHVar1;
  }
  return;
}
```

---

---

## FUN_0041c3e5 — 0x41c3e5

- Classification : internal
- Corps : `0x41c3e5–0x41c46e`
- État : pseudocode obtenu
- Evidence : `ev_8bfc9aac5229aa47014e3cc700d95c6bc6c642f69f280f307c7f232cbcf2a305`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40144c` — `thunk_FUN_0042cc24`
- `0x40172b` — `thunk_FUN_0045a3f1`
- `0x4021b7` — `thunk_FUN_0046ae19`
- `0x4022b6` — `thunk_FUN_00469f56`
- `0x402324` — `thunk_FUN_0041be90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041c3e5(void)

{
  if (DAT_004c2b80 != 0) {
    thunk_FUN_0045a3f1();
  }
  if (DAT_0062d172 == 8) {
    thunk_FUN_00469f56();
    thunk_FUN_0046ae19();
    if (DAT_004c2b60 != 0) {
      DAT_004c2c40 = DAT_004c2b54 / DAT_004c2b60;
    }
    do {
      DAT_004c2b0c = thunk_FUN_0041be90(DAT_004c2c44);
    } while (DAT_004c2b0c < DAT_004c2c40);
    DAT_004c2c44 = DAT_004c2c44 + DAT_004c2b0c;
    thunk_FUN_0042cc24();
  }
  return;
}
```

---

---

## FUN_0041cf86 — 0x41cf86

- Classification : internal
- Corps : `0x41cf86–0x41cfab`
- État : pseudocode obtenu
- Evidence : `ev_a96a976ad9c33472b4ef2263c63b0eb7fc71e68f3c288de3c2d861de035fa03b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x5a` — `USER32.DLL::PostQuitMessage`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x49cbf8` — "Posting Quit Message"

### Pseudocode Ghidra

```c
void FUN_0041cf86(int param_1)

{
  thunk_FUN_00414ad0(s_Posting_Quit_Message_0049cbf8);
  PostQuitMessage(param_1);
  DAT_004c2b68 = 0;
  return;
}
```

---

---

## FUN_0041cfac — 0x41cfac

- Classification : internal
- Corps : `0x41cfac–0x41cfde`
- État : pseudocode obtenu
- Evidence : `ev_336ef7e06e6882a1350d988742e9b15644e2b605a9fd8482f66140d0d9c8cef4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x6c` — `USER32.DLL::SendMessageA`
- `0x40168b` — `thunk_FUN_0045749a`
- `0x476ea0` — `FUN_00476ea0`

### Chaînes référencées

- `0x49cc10` — "09.sav"

### Pseudocode Ghidra

```c
void FUN_0041cfac(WPARAM param_1)

{
  thunk_FUN_0045749a(s_09_sav_0049cc10);
  SendMessageA(DAT_004c2b58,2,param_1,0);
  FUN_00476ea0(param_1);
  return;
}
```

---

---

## FUN_0041cfdf — 0x41cfdf

- Classification : internal
- Corps : `0x41cfdf–0x41d0d9`
- État : pseudocode obtenu
- Evidence : `ev_c80fd0b423985d31a213996463e056f78c55bc7c540fe4eec78a5ecc4a80c39e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40117c` — `thunk_FUN_0045af55`
- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x40196f` — `thunk_FUN_0045af2b`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401fff` — `thunk_FUN_0040fdab`

### Chaînes référencées

- `0x49cc18` — "float.prf"

### Pseudocode Ghidra

```c
void FUN_0041cfdf(void)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491568;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0040f6f7();
  local_8 = 0;
  iVar1 = thunk_FUN_0040f752(s_float_prf_0049cc18,0x8000);
  if (iVar1 == 0) {
    DAT_0049c9a0 = thunk_FUN_0040fdab();
    DAT_0049c9a4 = thunk_FUN_0040fdab();
    DAT_0049c9a8 = thunk_FUN_0040fdab();
    DAT_0049c9ac = thunk_FUN_0040fdab();
  }
  local_14 = 0;
  if (DAT_0049c9a8 != 0) {
    local_14 = DAT_0049c9a0;
  }
  thunk_FUN_0045af55(local_14);
  local_14 = 0;
  if (DAT_0049c9ac != 0) {
    local_14 = DAT_0049c9a4;
  }
  thunk_FUN_0045af2b(local_14);
  local_8 = 0xffffffff;
  thunk_FUN_0040f73f();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

---

## FUN_0041d0da — 0x41d0da

- Classification : internal
- Corps : `0x41d0da–0x41d19c`
- État : pseudocode obtenu
- Evidence : `ev_bf074e8f4d54fc5be269fbce0985060fe716c6fe3346c60c5f03364e97799b7f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010a5` — `thunk_FUN_0040f7a5`
- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x402455` — `thunk_FUN_004199c0`

### Chaînes référencées

- `0x49cc24` — "float.prf"

### Pseudocode Ghidra

```c
void FUN_0041d0da(void)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049157e;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0040f6f7();
  local_8 = 0;
  iVar1 = thunk_FUN_0040f7a5(s_float_prf_0049cc24);
  if (iVar1 == 0) {
    thunk_FUN_004199c0(DAT_0049c9a0);
    thunk_FUN_004199c0(DAT_0049c9a4);
    thunk_FUN_004199c0(DAT_0049c9a8);
    thunk_FUN_004199c0(DAT_0049c9ac);
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
  }
  else {
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
  }
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

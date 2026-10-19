# 0012_batch_0008 — détails (2/3)

## FUN_0042de17 — 0x42de17

- Classification : internal
- Corps : `0x42de17–0x42de7a`
- État : pseudocode obtenu
- Evidence : `ev_7d9b0252749415e1d97d244fd8c6e7b034606954b0b3c18675f3113e52abdb85`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4017df` — `thunk_FUN_0041be72`
- `0x401c35` — `thunk_FUN_0042c07d`
- `0x4737e0` — `_strncpy`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042de17(char *param_1,short param_2)

{
  int iVar1;
  
  if (DAT_005c3120 == 0x14) {
    thunk_FUN_0042c07d(0);
  }
  _strncpy(&DAT_005c20a0 + DAT_005c3120 * 100,param_1,100);
  iVar1 = thunk_FUN_0041be72();
  *(int *)(&DAT_005c3048 + DAT_005c3120 * 4) = iVar1 + param_2 * DAT_004c2b54;
  DAT_005c3120 = DAT_005c3120 + 1;
  return;
}
```

---

---

## FUN_0042de7b — 0x42de7b

- Classification : internal
- Corps : `0x42de7b–0x42de89`
- État : pseudocode obtenu
- Evidence : `ev_5c26fee23a03585f828a330299a51fc0d6899839f73b6ead8b63ce84273bc770`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042de7b(void)

{
  DAT_005c3120 = 0;
  return;
}
```

---

---

## FUN_0042e690 — 0x42e690

- Classification : internal
- Corps : `0x42e690–0x42e772`
- État : pseudocode obtenu
- Evidence : `ev_5962d75a6e9f4a3c2a1514b8406770c953989b9e276934a899cf3ab5c69a970d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- `0x494250` — "0123456789ABCDEF"
- `0x494250` — "0123456789ABCDEF"

### Pseudocode Ghidra

```c
undefined4 FUN_0042e690(int param_1,wchar_t *param_2)

{
  uint local_c;
  
  *param_2 = 0x7b;
  param_2 = param_2 + 1;
  for (local_c = 0; local_c < 0x14; local_c = local_c + 1) {
    if ((&DAT_00494238)[local_c] == '-') {
      *param_2 = L'-';
      param_2 = param_2 + 1;
    }
    else {
      *param_2 = L"0123456789ABCDEF"
                 [(int)(*(byte *)(param_1 + (uint)(byte)(&DAT_00494238)[local_c]) & 0xf0) >> 4];
      param_2[1] = L"0123456789ABCDEF"
                   [*(byte *)(param_1 + (uint)(byte)(&DAT_00494238)[local_c]) & 0xf];
      param_2 = param_2 + 2;
    }
  }
  *param_2 = L'}';
  param_2[1] = L'\0';
  return 0x26;
}
```

---

## FID_conflict:_AfxIsEqualGUID — 0x42e773

- Classification : internal
- Corps : `0x42e773–0x42e7c3`
- État : pseudocode obtenu
- Evidence : `ev_7cf97b14edd8e4be78ad8871239b1091e5367431f013a1db0ec0ac87d62aa140`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Multiple Matches With Different Base Names
    int __cdecl ATL::InlineIsEqualGUID(struct _GUID const &,struct _GUID const &)
    int __cdecl _AfxIsEqualGUID(struct _GUID const &,struct _GUID const &)
    _InlineIsEqualGUID
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual
   Studio 2010 Debug */

undefined4 FID_conflict__AfxIsEqualGUID(int *param_1,int *param_2)

{
  undefined4 local_8;
  
  if ((((*param_1 == *param_2) && (param_1[1] == param_2[1])) && (param_1[2] == param_2[2])) &&
     (param_1[3] == param_2[3])) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  return local_8;
}
```

---

---

## FUN_0042e7c4 — 0x42e7c4

- Classification : internal
- Corps : `0x42e7c4–0x42e826`
- État : pseudocode obtenu
- Evidence : `ev_6ca21e112d54a1f0ec895ef85e8cf3834024c05386f626ed8e1f038624af07fd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0042e7c4(char *param_1)

{
  char cVar1;
  int iVar2;
  
  cVar1 = *param_1;
  if ((cVar1 < '0') || ('9' < cVar1)) {
    if ((cVar1 < 'a') || ('f' < cVar1)) {
      if ((cVar1 < 'A') || ('F' < cVar1)) {
        iVar2 = 0;
      }
      else {
        iVar2 = cVar1 + -0x37;
      }
    }
    else {
      iVar2 = cVar1 + -0x57;
    }
  }
  else {
    iVar2 = cVar1 + -0x30;
  }
  return iVar2;
}
```

---

---

## FUN_0042e827 — 0x42e827

- Classification : internal
- Corps : `0x42e827–0x42e8e6`
- État : pseudocode obtenu
- Evidence : `ev_10e93ebbd04c7c0f07d09bda544cba00346c5c6498c4bd52d55e15850be050e6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401eb5` — `thunk_FUN_0042e7c4`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042e827(int param_1,int *param_2,int param_3,int param_4)

{
  char cVar1;
  char cVar2;
  int local_8;
  
  for (local_8 = 0; local_8 < param_3; local_8 = local_8 + 1) {
    if (*(char *)*param_2 == '-') {
      *param_2 = *param_2 + 1;
    }
    if (param_4 == 1) {
      cVar1 = thunk_FUN_0042e7c4(*param_2);
      cVar2 = thunk_FUN_0042e7c4(*param_2 + 1);
      *(char *)((param_1 + param_3) - (local_8 + 1)) = cVar1 * '\x10' + cVar2;
    }
    else {
      cVar1 = thunk_FUN_0042e7c4(*param_2);
      cVar2 = thunk_FUN_0042e7c4(*param_2 + 1);
      *(char *)(param_1 + local_8) = cVar1 * '\x10' + cVar2;
    }
    *param_2 = *param_2 + 2;
  }
  return;
}
```

---

---

## FUN_0042e8e7 — 0x42e8e7

- Classification : internal
- Corps : `0x42e8e7–0x42e9e8`
- État : pseudocode obtenu
- Evidence : `ev_e51c873857901aad660a340adef8ef39161ec42b4829e61a1f3e315d0837e299`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011e5` — `thunk_FUN_0042e9e9`
- `0x402365` — `thunk_FUN_0042e827`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042e8e7(undefined4 param_1,void *param_2)

{
  undefined4 uVar1;
  char *local_48;
  char local_44 [64];
  
  local_48 = local_44;
  thunk_FUN_0042e9e9(local_48,param_1,0x40);
  if (*local_48 == '{') {
    local_48 = local_48 + 1;
    thunk_FUN_0042e827(param_2,&local_48,4,1);
    thunk_FUN_0042e827((int)param_2 + 4,&local_48,2,1);
    thunk_FUN_0042e827((int)param_2 + 6,&local_48,2,1);
    thunk_FUN_0042e827((int)param_2 + 8,&local_48,8,0);
    if (*local_48 == '}') {
      uVar1 = 0;
    }
    else {
      _memset(param_2,0,0x10);
      uVar1 = 0x80004005;
    }
  }
  else {
    uVar1 = 0x80004005;
  }
  return uVar1;
}
```

---

---

## FUN_0042e9e9 — 0x42e9e9

- Classification : internal
- Corps : `0x42e9e9–0x42ea19`
- État : pseudocode obtenu
- Evidence : `ev_71c4c8c2de0099a27f270462166d38d44385e3aa400283b2cd58fb18f509f49d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x7` — `KERNEL32.DLL::WideCharToMultiByte`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0042e9e9(LPSTR param_1,LPCWSTR param_2,int param_3)

{
  int iVar1;
  BOOL local_c [2];
  
  iVar1 = WideCharToMultiByte(0,0,param_2,-1,param_1,param_3,&DAT_0049e6b4,local_c);
  return iVar1;
}
```

---

---

## FUN_0042ea1a — 0x42ea1a

- Classification : internal
- Corps : `0x42ea1a–0x42ea3f`
- État : pseudocode obtenu
- Evidence : `ev_e3fbd90a20f6c6a058c3938299f89c868fcaf57e0ad0ffa3b149d58a23d442af`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x5` — `KERNEL32.DLL::MultiByteToWideChar`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0042ea1a(LPWSTR param_1,LPCSTR param_2,int param_3)

{
  int iVar1;
  
  iVar1 = MultiByteToWideChar(0,0,param_2,-1,param_1,param_3);
  return iVar1;
}
```

---

---

## FUN_0042ea40 — 0x42ea40

- Classification : internal
- Corps : `0x42ea40–0x42ea64`
- État : pseudocode obtenu
- Evidence : `ev_16a9f931ed37bfb22210d2b1ef99cced7e802d73fdbbc298350b02693ee0fd35`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b90` — `FUN_00474b90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0042ea40(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_00474b90();
  return iVar1 % (param_2 - param_1) + param_1;
}
```

---

---

## FUN_0042ea65 — 0x42ea65

- Classification : internal
- Corps : `0x42ea65–0x42ea91`
- État : pseudocode obtenu
- Evidence : `ev_a4ecfbd0788002b0eb8cdca128dd3a48a0f409e4cc4f1c4d82d584980ce8aed2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b90` — `FUN_00474b90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_0042ea65(double param_1,double param_2)

{
  int iVar1;
  
  iVar1 = FUN_00474b90();
  return ((float10)iVar1 * (float10)(param_2 - param_1)) / (float10)32767.0 + (float10)param_1;
}
```

---

---

## FUN_0042eba0 — 0x42eba0

- Classification : internal
- Corps : `0x42eba0–0x42ee33`
- État : pseudocode obtenu
- Evidence : `ev_4539fa61c9afdfc26f53f63f89c1eeee1db31de6684e55bec209ac2cf5d040ee`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49e6b8` — "ISNumEvents < MAX_INPUT_EVENTS"
- `0x49e6d8` — "C:\\float\\src\\input.cpp"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0042eba0(uint param_1,int param_2,uint param_3)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int local_c;
  
  if (DAT_005c36b8 == 8) {
    for (local_c = 0; local_c < 8; local_c = local_c + 1) {
      iVar3 = local_c + 1;
      (&DAT_005c3618)[local_c * 4] = (&DAT_005c3618)[iVar3 * 4];
      (&DAT_005c361c)[local_c * 4] = (&DAT_005c361c)[iVar3 * 4];
      (&DAT_005c3620)[local_c * 4] = (&DAT_005c3620)[iVar3 * 4];
      (&DAT_005c3624)[local_c * 4] = (&DAT_005c3624)[iVar3 * 4];
    }
    DAT_005c36b8 = DAT_005c36b8 + -1;
  }
  if (7 < DAT_005c36b8) {
    thunk_FUN_00414b64(s_C__float_src_input_cpp_0049e6d8,0x3f,
                       s_ISNumEvents_<_MAX_INPUT_EVENTS_0049e6b8);
  }
  iVar3 = DAT_005c36b8;
  iVar1 = DAT_005c36b8 * 0x10;
  puVar2 = &DAT_005c3618 + DAT_005c36b8 * 4;
  if (param_1 < 0x201) {
    if (param_1 == 0x200) {
      *puVar2 = 1;
      _DAT_005c36bc = param_3 & 0xffff;
      _DAT_005c36c0 = (int)param_3 >> 0x10;
    }
    else if (param_1 == 0x100) {
      *puVar2 = 6;
      *(undefined2 *)(&DAT_005c3620 + iVar3 * 4) = (undefined2)param_2;
      *(ushort *)((int)&DAT_005c3620 + iVar1 + 2) =
           (ushort)param_3 & 0xff | -(ushort)(DAT_005c36c8 != 0) & 0x100 |
           -(ushort)(DAT_005c36cc != 0) & 0x200;
      *(uint *)(&DAT_005c3698 + DAT_005c36b8 * 4) = param_3;
      DAT_005c36c4 = (undefined2)param_2;
      if (param_2 == 0x10) {
        DAT_005c36c8 = 1;
      }
      else if (param_2 == 0x11) {
        DAT_005c36cc = 1;
      }
    }
    else if (param_1 == 0x101) {
      *puVar2 = 7;
      *(undefined2 *)(&DAT_005c3620 + iVar3 * 4) = (undefined2)param_2;
      *(ushort *)((int)&DAT_005c3620 + iVar1 + 2) =
           -(ushort)(DAT_005c36c8 != 0) & 0x100 | -(ushort)(DAT_005c36cc != 0) & 0x200;
      if (param_2 == 0x10) {
        DAT_005c36c8 = 0;
      }
      else if (param_2 == 0x11) {
        DAT_005c36cc = 0;
      }
    }
  }
  else {
    switch(param_1) {
    case 0x201:
      *puVar2 = 2;
      *(undefined2 *)(&DAT_005c3620 + iVar3 * 4) = (undefined2)param_2;
      break;
    case 0x202:
      *puVar2 = 3;
      *(undefined2 *)(&DAT_005c3620 + iVar3 * 4) = (undefined2)param_2;
      break;
    case 0x204:
      *puVar2 = 4;
      *(undefined2 *)(&DAT_005c3620 + iVar3 * 4) = (undefined2)param_2;
      break;
    case 0x205:
      *puVar2 = 5;
      *(undefined2 *)(&DAT_005c3620 + iVar3 * 4) = (undefined2)param_2;
    }
  }
  *(undefined2 *)(&DAT_005c361c + iVar3 * 4) = DAT_005c36bc;
  *(undefined2 *)((int)&DAT_005c361c + iVar1 + 2) = DAT_005c36c0;
  DAT_005c36b8 = DAT_005c36b8 + 1;
  return;
}
```

---

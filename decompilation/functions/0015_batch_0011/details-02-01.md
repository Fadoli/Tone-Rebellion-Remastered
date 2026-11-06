# 0015_batch_0011 — détails (1/3)

## FUN_0044bd4f — 0x44bd4f

- Classification : internal
- Corps : `0x44bd4f–0x44bd59`
- État : pseudocode obtenu
- Evidence : `ev_64ab6b0171c8b9c2f3a4d1ca98f1a772334406568f320019eded2c36b286b4b7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044bd4f(void)

{
  return;
}
```

---

---

## FUN_0044bd5a — 0x44bd5a

- Classification : internal
- Corps : `0x44bd5a–0x44bdec`
- État : pseudocode obtenu
- Evidence : `ev_97af14272e7479c32b93908ec09640bbad5d86e53077dd69bbec3ae63cc74a3d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a8c` — `thunk_FUN_0044b3b7`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a2078` — "NETHostID==NETPlayerId"
- `0x4a2090` — "C:\\float\\src\\network.cpp"
- `0x4a20b4` — "C:\\float\\src\\network.cpp"

### Pseudocode Ghidra

```c
void FUN_0044bd5a(void)

{
  int iVar1;
  int in_ECX;
  undefined4 local_c;
  int local_8;
  
  if (*(int *)(in_ECX + 0x10) == 1) {
    if (DAT_005e1ef8 != DAT_005e1e94) {
      thunk_FUN_00414b64(s_C__float_src_network_cpp_004a2090,0x522,s_NETHostID__NETPlayerId_004a2078
                        );
    }
    local_c = 0x60970;
    local_8 = DAT_005e1ef8;
    iVar1 = thunk_FUN_0044b3b7(&local_c,8,0xffffffff);
    if (iVar1 == 0) {
      thunk_FUN_00414b64(s_C__float_src_network_cpp_004a20b4,0x527,&DAT_004a20ac);
    }
  }
  return;
}
```

---

---

## FUN_0044bded — 0x44bded

- Classification : internal
- Corps : `0x44bded–0x44c09f`
- État : pseudocode obtenu
- Evidence : `ev_2252d5386ca5363d2e7597e40b0d632999e6a2c463b583b135eb8a568b86b023`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a8c` — `thunk_FUN_0044b3b7`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`

### Chaînes référencées

- `0x4a20d0` — "NETHostID==NETPlayerId"
- `0x4a20e8` — "C:\\float\\src\\network.cpp"
- `0x4a210c` — "C:\\float\\src\\network.cpp"
- `0x4a2130` — "C:\\float\\src\\network.cpp"
- `0x4a2154` — "C:\\float\\src\\network.cpp"

### Pseudocode Ghidra

```c
void FUN_0044bded(int param_1)

{
  size_t sVar1;
  int iVar2;
  int in_ECX;
  undefined4 uVar3;
  int local_9c;
  undefined4 local_98;
  int local_94;
  int local_90;
  undefined4 local_8c;
  undefined4 local_88;
  char local_84 [120];
  int local_c;
  char *local_8;
  
  if (*(int *)(in_ECX + 0x10) == 1) {
    local_8c = 0x112694;
    if (DAT_005e1ef8 != DAT_005e1e94) {
      thunk_FUN_00414b64(s_C__float_src_network_cpp_004a20e8,0x53a,s_NETHostID__NETPlayerId_004a20d0
                        );
    }
    if (*(int *)(&DAT_005e2880 + param_1 * 0x54) != DAT_005e1e94) {
      for (local_9c = 0; local_9c < DAT_005e1768; local_9c = local_9c + 1) {
        local_88 = *(undefined4 *)(&DAT_005e2880 + local_9c * 0x54);
        FUN_00472da0(local_84,&DAT_005e2830 + local_9c * 0x54);
        uVar3 = *(undefined4 *)(&DAT_005e2880 + param_1 * 0x54);
        sVar1 = _strlen(&DAT_005e2830 + local_9c * 0x54);
        iVar2 = thunk_FUN_0044b3b7(&local_8c,sVar1 + 9,uVar3);
        if (iVar2 == 0) {
          thunk_FUN_00414b64(s_C__float_src_network_cpp_004a210c,0x544,&DAT_004a2104);
        }
      }
      local_98 = 0x60970;
      local_94 = DAT_005e1ef8;
      iVar2 = thunk_FUN_0044b3b7(&local_98,8,*(undefined4 *)(&DAT_005e2880 + param_1 * 0x54));
      if (iVar2 == 0) {
        thunk_FUN_00414b64(s_C__float_src_network_cpp_004a2130,0x54a,&DAT_004a2128);
      }
    }
    local_88 = *(undefined4 *)(&DAT_005e2880 + param_1 * 0x54);
    local_8 = local_84;
    FUN_00472da0(local_8,&DAT_005e2830 + param_1 * 0x54);
    sVar1 = _strlen(local_8);
    local_c = sVar1 + 9;
    local_90 = thunk_FUN_0044b3b7(&local_8c,local_c,0xffffffff);
    if (local_90 == 0) {
      uVar3 = thunk_FUN_00414b64(s_C__float_src_network_cpp_004a2154,0x553,&DAT_004a214c);
    }
    else {
      uVar3 = 0;
    }
    if ((DAT_005e3170 != (code *)0x0) &&
       ((*DAT_005e3170)(1,&local_88,local_c + -4,uVar3),
       DAT_005e1e94 == *(int *)(&DAT_005e2880 + param_1 * 0x54))) {
      (*DAT_005e3170)(4,&local_88,4);
      (*DAT_005e3170)(3,&local_88,4);
    }
  }
  return;
}
```

---

---

## FUN_0044c0a0 — 0x44c0a0

- Classification : internal
- Corps : `0x44c0a0–0x44c0eb`
- État : pseudocode obtenu
- Evidence : `ev_14de8ee1e488b83cf5ff3ae9265533abd6d9ec66ed11ff1418b5f5695dccfac6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0044c0a0(void)

{
  int local_8;
  
  if (DAT_005e1ef8 != 0) {
    for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
      if (*(int *)(&DAT_005e2880 + local_8 * 0x54) == DAT_005e1ef8) {
        return local_8;
      }
    }
  }
  return -1;
}
```

---

---

## FUN_0044c0ec — 0x44c0ec

- Classification : internal
- Corps : `0x44c0ec–0x44c143`
- État : pseudocode obtenu
- Evidence : `ev_2ff00602fd3fba3a6418f5468784287c84bd55733052e8b747bc1377f4624fa6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x55` — `USER32.DLL::MessageBoxA`
- `EXTERNAL:0x64` — `USER32.DLL::LoadStringA`

### Chaînes référencées

- `0x639412` — "Tone Rebellion - Erreur"

### Pseudocode Ghidra

```c
undefined4 FUN_0044c0ec(UINT param_1)

{
  CHAR local_a4 [80];
  CHAR local_54 [80];
  
  LoadStringA(DAT_004c2b5c,param_1,local_54,0x50);
  LoadStringA(DAT_004c2b5c,0x1a,local_a4,0x50);
  MessageBoxA(DAT_004c2b58,local_54,local_a4,0);
  return 0;
}
```

---

---

## FUN_0044c144 — 0x44c144

- Classification : internal
- Corps : `0x44c144–0x44c21f`
- État : pseudocode obtenu
- Evidence : `ev_46e218aa5a1eb3bf566ee92011fbd2ca8870f3644ee546f6bfb25ee924b05398`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x6` — `KERNEL32.DLL::MulDiv`
- `EXTERNAL:0x71` — `GDI32.DLL::CreateFontIndirectA`
- `EXTERNAL:0x72` — `GDI32.DLL::GetDeviceCaps`
- `0x472da0` — `FUN_00472da0`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x63949a` — "Times"

### Pseudocode Ghidra

```c
void FUN_0044c144(HDC param_1)

{
  int iVar1;
  int iVar2;
  LOGFONTA local_90;
  CHAR local_54 [80];
  
  LoadStringA(DAT_004c2b5c,0x1d,local_54,0x50);
  _memset(&local_90,0,0x3c);
  iVar2 = 0x48;
  iVar1 = GetDeviceCaps(param_1,0x5a);
  local_90.lfHeight = MulDiv(0xb,iVar1,iVar2);
  local_90.lfHeight = -local_90.lfHeight;
  local_90.lfWeight = 500;
  local_90.lfItalic = '\x01';
  FUN_00472da0(local_90.lfFaceName,local_54);
  DAT_005e1ef4 = CreateFontIndirectA(&local_90);
  _memset(&local_90,0,0x3c);
  iVar2 = 0x48;
  iVar1 = GetDeviceCaps(param_1,0x5a);
  local_90.lfHeight = MulDiv(0xb,iVar1,iVar2);
  local_90.lfHeight = -local_90.lfHeight;
  local_90.lfWeight = 500;
  FUN_00472da0(local_90.lfFaceName,local_54);
  DAT_005e2d58 = CreateFontIndirectA(&local_90);
  return;
}
```

---

---

## FUN_0044c220 — 0x44c220

- Classification : internal
- Corps : `0x44c220–0x44c24f`
- État : pseudocode obtenu
- Evidence : `ev_064b5456ef4d814c8f2c3899047a21b6bd02a74328bfcd4d68baf508e9967a7e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x74` — `GDI32.DLL::DeleteObject`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044c220(void)

{
  if (DAT_005e1ef4 != (HGDIOBJ)0x0) {
    DeleteObject(DAT_005e1ef4);
  }
  if (DAT_005e2d58 != (HGDIOBJ)0x0) {
    DeleteObject(DAT_005e2d58);
  }
  return;
}
```

---

---

## FUN_0044c250 — 0x44c250

- Classification : internal
- Corps : `0x44c250–0x44c270`
- État : pseudocode obtenu
- Evidence : `ev_2b1529b9645d5334be2bcdd8cde55f157ba5bf97891ffd55d62f8237c798059b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x77` — `ADVAPI32.DLL::RegSetValueExA`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044c250(LPCSTR param_1,BYTE *param_2,DWORD param_3)

{
  RegSetValueExA(DAT_005e3174,param_1,0,1,param_2,param_3);
  return;
}
```

---

---

## FUN_0044c271 — 0x44c271

- Classification : internal
- Corps : `0x44c271–0x44c291`
- État : pseudocode obtenu
- Evidence : `ev_5fb54a903dd0ee62ca05cc08212a603239598cd371903e0d4e151df8a7cb7117`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x77` — `ADVAPI32.DLL::RegSetValueExA`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044c271(LPCSTR param_1,BYTE *param_2,DWORD param_3)

{
  RegSetValueExA(DAT_005e3174,param_1,0,1,param_2,param_3);
  return;
}
```

---

---

## FUN_0044c292 — 0x44c292

- Classification : internal
- Corps : `0x44c292–0x44c2b8`
- État : pseudocode obtenu
- Evidence : `ev_929a93e942a9f5a6b1286ad83a083c713b3a642dc2f2c7bb4d1801bd40246a41`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x79` — `ADVAPI32.DLL::RegQueryValueExA`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044c292(LPCSTR param_1,LPBYTE param_2,LPDWORD param_3)

{
  DWORD local_8;
  
  RegQueryValueExA(DAT_005e3174,param_1,(LPDWORD)0x0,&local_8,param_2,param_3);
  return;
}
```

---

---

## FUN_0044c2b9 — 0x44c2b9

- Classification : internal
- Corps : `0x44c2b9–0x44c608`
- État : pseudocode obtenu
- Evidence : `ev_920056457a8d9840efd759ec9ae007a97d31d024e7ebb523ce71180ad8511bc8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x6b` — `USER32.DLL::GetDC`
- `EXTERNAL:0x76` — `COMCTL32.DLL::PropertySheetA`
- `EXTERNAL:0x78` — `ADVAPI32.DLL::RegOpenKeyExA`
- `0x4011a4` — `thunk_FUN_0044c144`
- `0x401203` — `thunk_FUN_0044b1c5`
- `0x4024f5` — `thunk_FUN_0044c220`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x4a2174` — "Software\\The Logic Factory\\Tone Rebellion"
- `0x4a21a0` — "%s\\%s"
- `0x6394a6` — "Tone Rebellion - Modes de communication (1/4)"
- `0x639502` — "Tone Rebellion - Installation du jeu (2/4)"
- `0x639558` — "Tone Rebellion - Rejoindre une session (3/4)"
- `0x6395b2` — "Tone Rebellion - Héberger une session (3/4)"
- `0x63960a` — "Installation de Tone Rebellion"
- `0x639cba` — "Tone Rebellion - Commencer la partie(4/4)"

### Pseudocode Ghidra

```c
bool FUN_0044c2b9(void)

{
  HDC pHVar1;
  int iVar2;
  CHAR local_324 [80];
  undefined4 local_2d4;
  undefined4 local_2d0;
  HINSTANCE local_2cc;
  undefined4 local_2c8;
  undefined4 local_2c4;
  CHAR *local_2c0;
  undefined1 *local_2bc;
  undefined4 local_2b8;
  undefined4 local_2b4;
  undefined4 local_2ac;
  undefined4 local_2a8;
  HINSTANCE local_2a4;
  undefined4 local_2a0;
  undefined4 local_29c;
  CHAR *local_298;
  undefined1 *local_294;
  undefined4 local_290;
  undefined4 local_28c;
  undefined4 local_284;
  undefined4 local_280;
  HINSTANCE local_27c;
  undefined4 local_278;
  undefined4 local_274;
  CHAR *local_270;
  undefined1 *local_26c;
  undefined4 local_268;
  undefined4 local_264;
  undefined4 local_25c;
  undefined4 local_258;
  HINSTANCE local_254;
  undefined4 local_250;
  undefined4 local_24c;
  CHAR *local_248;
  undefined1 *local_244;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_234;
  undefined4 local_230;
  HINSTANCE local_22c;
  undefined4 local_228;
  undefined4 local_224;
  _union_1957 *local_220;
  undefined1 *local_21c;
  undefined4 local_218;
  undefined4 local_214;
  CHAR local_20c [80];
  CHAR local_1bc [80];
  PROPSHEETHEADERA_V2 local_16c [2];
  CHAR local_f4 [80];
  CHAR local_a4 [80];
  CHAR local_54 [80];
  
  LoadStringA(DAT_004c2b5c,0x1e,local_20c,0x50);
  LoadStringA(DAT_004c2b5c,0x1f,local_1bc,0x50);
  LoadStringA(DAT_004c2b5c,0x20,local_a4,0x50);
  LoadStringA(DAT_004c2b5c,0x21,local_54,0x50);
  LoadStringA(DAT_004c2b5c,0x3f,(LPSTR)&local_16c[0].u4,0x50);
  LoadStringA(DAT_004c2b5c,0x22,local_f4,0x50);
  local_2d4 = 0x28;
  local_2d0 = 0xc;
  local_2cc = DAT_004c2b5c;
  local_2c8 = 0x81;
  local_2c4 = 0;
  local_2bc = &LAB_00402446;
  local_2c0 = local_20c;
  local_2b8 = 0;
  local_2b4 = 0;
  local_2ac = 0x28;
  local_2a8 = 0xc;
  local_2a4 = DAT_004c2b5c;
  local_2a0 = 0x6c;
  local_29c = 0;
  local_294 = &LAB_00401799;
  local_298 = local_1bc;
  local_290 = 0;
  local_28c = 0;
  local_284 = 0x28;
  local_280 = 0xc;
  local_27c = DAT_004c2b5c;
  local_278 = 0x82;
  local_274 = 0;
  local_26c = &LAB_00402342;
  local_270 = local_a4;
  local_268 = 0;
  local_264 = 0;
  local_25c = 0x28;
  local_258 = 0xc;
  local_254 = DAT_004c2b5c;
  local_250 = 0x83;
  local_24c = 0;
  local_244 = &LAB_004010fa;
  local_248 = local_54;
  local_240 = 0;
  local_23c = 0;
  local_234 = 0x28;
  local_230 = 0xc;
  local_22c = DAT_004c2b5c;
  local_228 = 0x84;
  local_224 = 0;
  local_21c = &LAB_00401c67;
  local_220 = &local_16c[0].u4;
  local_218 = 0;
  local_214 = 0;
  local_16c[0].dwSize = 0x28;
  local_16c[0].dwFlags = 0x2c;
  local_16c[0].hwndParent = DAT_004c2b58;
  local_16c[0].hInstance = DAT_004c2b5c;
  local_16c[0].u.hIcon = (HICON)0x0;
  local_16c[0].pszCaption = local_f4;
  local_16c[0].nPages = 5;
  local_16c[0].u2.nStartPage = 0;
  local_16c[0].u3.ppsp = (LPCPROPSHEETPAGEA)&local_2d4;
  local_16c[0].pfnCallback = (PFNPROPSHEETCALLBACK)0x0;
  FUN_00472ca0(local_324,s__s__s_004a21a0,s_Software_The_Logic_Factory_Tone_R_004a2174,&DAT_004a2170
              );
  RegOpenKeyExA((HKEY)0x80000002,local_324,0,0xf003f,(PHKEY)&DAT_005e3174);
  pHVar1 = GetDC(DAT_004c2b58);
  thunk_FUN_0044c144(pHVar1);
  PropertySheetA(local_16c);
  thunk_FUN_0044c220();
  iVar2 = thunk_FUN_0044b1c5();
  return iVar2 != 0;
}
```

---

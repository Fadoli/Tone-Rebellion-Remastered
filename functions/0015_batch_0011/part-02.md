# 0015_batch_0011 — détails (2/6)

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

## FUN_0044c609 — 0x44c609

- Classification : internal
- Corps : `0x44c609–0x44c8e6`
- État : pseudocode obtenu
- Evidence : `ev_cc87568cd410ea8824952f032f34ef9aab72c5ba7073d4c2b1610f301154659d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x5f` — `USER32.DLL::GetParent`
- `EXTERNAL:0x60` — `USER32.DLL::PostMessageA`
- `EXTERNAL:0x61` — `USER32.DLL::SendDlgItemMessageA`
- `EXTERNAL:0x62` — `USER32.DLL::GetDlgItem`
- `EXTERNAL:0x63` — `USER32.DLL::SetFocus`
- `EXTERNAL:0x68` — `USER32.DLL::SetWindowLongA`
- `EXTERNAL:0x6c` — `USER32.DLL::SendMessageA`
- `0x401118` — `thunk_FUN_0044aa7e`
- `0x4011f9` — `thunk_FUN_0042ea1a`
- `0x40132a` — `FID_conflict:_AfxIsEqualGUID`
- `0x4018d4` — `thunk_FUN_0044ac6a`
- `0x4018de` — `thunk_FUN_0044ab7a`
- `0x402275` — `thunk_FUN_0044c292`
- `0x4023c9` — `thunk_FUN_0044c0ec`
- `0x402482` — `thunk_FUN_0042e8e7`

### Chaînes référencées

- `0x4a21a8` — "ServiceProvider"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0044c609(HWND param_1,int param_2,uint param_3,int param_4)

{
  HWND hWnd;
  int iVar1;
  undefined2 extraout_var;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  undefined4 local_84;
  WPARAM local_80;
  undefined1 local_7c [80];
  undefined1 local_2c [40];
  
  if (param_2 == 0x4e) {
    iVar1 = *(int *)(param_4 + 8);
    if (iVar1 == -0xd1) {
      thunk_FUN_0044ac6a();
      return 1;
    }
    if (iVar1 == -0xcf) {
      thunk_FUN_0044ac6a();
      if (_DAT_004a1958 != -1) {
        DAT_004a1954 = DAT_004a1958;
        iVar1 = thunk_FUN_0044ab7a(CONCAT22(extraout_var,DAT_004a1958));
        if (iVar1 != 0) {
          return 1;
        }
        thunk_FUN_0044c0ec(0x29);
      }
      SetWindowLongA(param_1,0,-1);
      return 1;
    }
    if (iVar1 == -200) {
      lParam = 2;
      wParam = 0;
      Msg = 0x470;
      hWnd = GetParent(param_1);
      PostMessageA(hWnd,Msg,wParam,lParam);
      return 1;
    }
  }
  else {
    if (param_2 == 0x110) {
      SendDlgItemMessageA(param_1,0x3eb,0x30,DAT_005e1ef4,1);
      DAT_005e2828 = GetDlgItem(param_1,0x3fd);
      if (DAT_005e2828 == (HWND)0x0) {
        return 1;
      }
      thunk_FUN_0044aa7e(0,0);
      for (local_80 = 0; (int)local_80 < (int)DAT_005e1f50; local_80 = local_80 + 1) {
        SendMessageA(DAT_005e2828,0x181,0xffffffff,(LPARAM)(&DAT_005e2d78 + local_80 * 0x68));
      }
      SetFocus(DAT_005e2828);
      _DAT_004a1958 = 0;
      local_84 = 0x27;
      if ((DAT_005e3174 != 0) &&
         (iVar1 = thunk_FUN_0044c292(s_ServiceProvider_004a21a8,local_2c,&local_84), iVar1 == 0)) {
        thunk_FUN_0042ea1a(local_7c,local_2c,0x27);
        thunk_FUN_0042e8e7(local_7c,&DAT_005e1ee0);
        for (local_80 = 0; (int)local_80 < (int)DAT_005e1f50; local_80 = local_80 + 1) {
          iVar1 = FID_conflict__AfxIsEqualGUID(&DAT_005e1ee0,&DAT_005e2d60 + local_80 * 0x68);
          if (iVar1 != 0) {
            _DAT_004a1958 = local_80;
            break;
          }
        }
      }
      SendMessageA(DAT_005e2828,0x186,_DAT_004a1958,0);
      _DAT_004a1958 = SendMessageA(DAT_005e2828,0x188,0,0);
      return 1;
    }
    if ((param_2 == 0x111) && (param_3 >> 0x10 == 1)) {
      _DAT_004a1958 = SendMessageA(DAT_005e2828,0x188,0,0);
      return 1;
    }
  }
  return 0;
}
```

---

## FUN_0044c8e7 — 0x44c8e7

- Classification : internal
- Corps : `0x44c8e7–0x44cac9`
- État : pseudocode obtenu
- Evidence : `ev_ad780708e3beb10cacc4e6d161688e6e22dfe58dcb30dddb6cef8e7dc96f34ed`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x5f` — `USER32.DLL::GetParent`
- `EXTERNAL:0x60` — `USER32.DLL::PostMessageA`
- `EXTERNAL:0x61` — `USER32.DLL::SendDlgItemMessageA`
- `EXTERNAL:0x68` — `USER32.DLL::SetWindowLongA`
- `0x4018d4` — `thunk_FUN_0044ac6a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0044c8e7(HWND param_1,int param_2,uint param_3,int param_4)

{
  int iVar1;
  HWND hWnd;
  LRESULT LVar2;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  
  if (param_2 == 0x4e) {
    iVar1 = *(int *)(param_4 + 8);
    if (iVar1 == -0xd1) {
      thunk_FUN_0044ac6a();
      return 1;
    }
    if (iVar1 == -0xcf) {
      if (DAT_005e1e90 != 0) {
        SetWindowLongA(param_1,0,0x83);
      }
      return 1;
    }
    if (iVar1 == -200) {
      lParam = 3;
      wParam = 0;
      Msg = 0x470;
      hWnd = GetParent(param_1);
      PostMessageA(hWnd,Msg,wParam,lParam);
      return 1;
    }
  }
  else {
    if (param_2 == 0x110) {
      SendDlgItemMessageA(param_1,0x3ec,0x30,DAT_005e1ef4,1);
      SendDlgItemMessageA(param_1,0x404,0x30,DAT_005e2d58,1);
      SendDlgItemMessageA(param_1,0x403,0x30,DAT_005e2d58,1);
      SendDlgItemMessageA(param_1,0x403,0xf1,1,0);
      SendDlgItemMessageA(param_1,0x404,0xf1,0,0);
      DAT_005e1e90 = 1;
      return 1;
    }
    if ((param_2 == 0x111) && (param_3 >> 0x10 == 0)) {
      if ((param_3 & 0xffff) == 0x403) {
        LVar2 = SendDlgItemMessageA(param_1,0x403,0xf0,1,0);
        if (LVar2 == 1) {
          DAT_005e1e90 = 1;
        }
        return 1;
      }
      if ((param_3 & 0xffff) == 0x404) {
        LVar2 = SendDlgItemMessageA(param_1,0x404,0xf0,1,0);
        if (LVar2 == 1) {
          DAT_005e1e90 = 0;
        }
        return 1;
      }
    }
  }
  return 0;
}
```

---

## FUN_0044caca — 0x44caca

- Classification : internal
- Corps : `0x44caca–0x44d01f`
- État : pseudocode obtenu
- Evidence : `ev_92b8e5b357c53452c7fad7bbbac576d5d8c70ceffa4b6fa44b851881706356a5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x5b` — `USER32.DLL::GetDlgItemTextA`
- `EXTERNAL:0x5c` — `USER32.DLL::KillTimer`
- `EXTERNAL:0x5d` — `USER32.DLL::SetDlgItemTextA`
- `EXTERNAL:0x5e` — `USER32.DLL::SetTimer`
- `EXTERNAL:0x5f` — `USER32.DLL::GetParent`
- `EXTERNAL:0x60` — `USER32.DLL::PostMessageA`
- `EXTERNAL:0x61` — `USER32.DLL::SendDlgItemMessageA`
- `EXTERNAL:0x62` — `USER32.DLL::GetDlgItem`
- `EXTERNAL:0x63` — `USER32.DLL::SetFocus`
- `EXTERNAL:0x68` — `USER32.DLL::SetWindowLongA`
- `EXTERNAL:0x6c` — `USER32.DLL::SendMessageA`
- `0x4011e5` — `thunk_FUN_0042e9e9`
- `0x4014e2` — `thunk_FUN_0044afcc`
- `0x4015dc` — `thunk_FUN_0044aed8`
- `0x4018d4` — `thunk_FUN_0044ac6a`
- `0x401e38` — `thunk_FUN_0042e690`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4020a9` — `thunk_FUN_0044ab4c`
- `0x40213f` — `thunk_FUN_0044c271`
- `0x402275` — `thunk_FUN_0044c292`
- `0x402441` — `thunk_FUN_0044c250`

### Chaînes référencées

- `0x4a21b8` — "ServiceProvider"
- `0x4a21c8` — "PlayerName"
- `0x4a21d4` — "iIndex!=LB_ERR && iIndex < NETNumSessions"
- `0x4a2200` — "C:\\float\\src\\network.cpp"
- `0x4a221c` — "success"
- `0x4a2224` — "C:\\float\\src\\network.cpp"
- `0x4a2240` — "PlayerName"
- `0x4a224c` — "CONNECT_TYPE!=-1"
- `0x4a2260` — "C:\\float\\src\\network.cpp"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0044caca(HWND param_1,undefined4 param_2,uint param_3,int param_4)

{
  int iVar1;
  UINT UVar2;
  HWND pHVar3;
  undefined4 uVar4;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 uVar5;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  WPARAM WVar6;
  LPARAM LVar7;
  int local_88;
  undefined1 local_80 [80];
  undefined1 local_30 [40];
  undefined4 local_8;
  
  switch(param_2) {
  case 0x4e:
    switch(*(undefined4 *)(param_4 + 8)) {
    case 0xffffff2f:
      KillTimer(param_1,0);
      thunk_FUN_0044ac6a();
      uVar4 = 1;
      break;
    default:
      goto switchD_0044cb09_caseD_4f;
    case 0xffffff31:
      KillTimer(param_1,0);
      if (DAT_005e3174 != 0) {
        thunk_FUN_0042e690(&DAT_005e1ee0,local_80);
        thunk_FUN_0042e9e9(local_30,local_80,0x4e);
        thunk_FUN_0044c271(s_ServiceProvider_004a21b8,local_30,0x27);
        thunk_FUN_0044c250(s_PlayerName_004a21c8,&DAT_005e1fd8,0x47);
      }
      _DAT_004a195c = SendMessageA(DAT_005e30f0,0x188,0,0);
      if ((_DAT_004a195c == 0xffffffff) ||
         (uVar5 = extraout_var, (int)DAT_005e3118 <= (int)_DAT_004a195c)) {
        thunk_FUN_00414b64(s_C__float_src_network_cpp_004a2200,0x755,
                           s_iIndex__LB_ERR____iIndex_<_NETNu_004a21d4);
        uVar5 = extraout_var_00;
      }
      iVar1 = thunk_FUN_0044afcc(CONCAT22(uVar5,DAT_004a195c),&DAT_005e1fd8);
      if (iVar1 == 0) {
        thunk_FUN_00414b64(s_C__float_src_network_cpp_004a2224,0x758,s_success_004a221c);
      }
      SetWindowLongA(param_1,0,0x84);
      uVar4 = 1;
      break;
    case 0xffffff32:
      KillTimer(param_1,0);
      uVar4 = 1;
      break;
    case 0xffffff38:
      UVar2 = GetDlgItemTextA(param_1,0x402,&DAT_005e1fd8,0x46);
      if ((UVar2 == 0) || (_DAT_004a195c == 0xffffffff)) {
        LVar7 = 1;
        WVar6 = 0;
        UVar2 = 0x470;
        pHVar3 = GetParent(param_1);
        PostMessageA(pHVar3,UVar2,WVar6,LVar7);
      }
      else {
        LVar7 = 3;
        WVar6 = 0;
        UVar2 = 0x470;
        pHVar3 = GetParent(param_1);
        PostMessageA(pHVar3,UVar2,WVar6,LVar7);
      }
      SetFocus(DAT_005e30f0);
      uVar4 = 1;
    }
    break;
  case 0x110:
    SendDlgItemMessageA(param_1,0x3f0,0x30,DAT_005e2d58,1);
    SendDlgItemMessageA(param_1,0x3f1,0x30,DAT_005e2d58,1);
    local_8 = 0x47;
    DAT_005e1fd8 = 0;
    if ((DAT_005e3174 != 0) &&
       (iVar1 = thunk_FUN_0044c292(s_PlayerName_004a2240,&DAT_005e1fd8,&local_8), iVar1 == 0)) {
      SetDlgItemTextA(param_1,0x402,&DAT_005e1fd8);
    }
    DAT_005e30f0 = GetDlgItem(param_1,0x400);
    uVar5 = extraout_var_01;
    if (DAT_004a1954 == -1) {
      thunk_FUN_00414b64(s_C__float_src_network_cpp_004a2260,0x774,s_CONNECT_TYPE___1_004a224c);
      uVar5 = extraout_var_02;
    }
    if ((DAT_005e30f0 != (HWND)0x0) &&
       (iVar1 = thunk_FUN_0044ab4c(CONCAT22(uVar5,DAT_004a1954)), iVar1 != 0)) {
      SetTimer(param_1,0,3000,(TIMERPROC)0x0);
    }
  case 0x113:
    if (DAT_005e30f0 == (HWND)0x0) {
      uVar4 = 1;
    }
    else {
      thunk_FUN_0044aed8(0,0);
      _DAT_004a195c = SendMessageA(DAT_005e30f0,0x188,0,0);
      SendMessageA(DAT_005e30f0,0x184,0,0);
      for (local_88 = 0; local_88 < DAT_005e3118; local_88 = local_88 + 1) {
        SendMessageA(DAT_005e30f0,0x181,0xffffffff,*(LPARAM *)(&DAT_005e17a8 + local_88 * 0x50));
      }
      if (_DAT_004a195c != 0xffffffff) {
        SendMessageA(DAT_005e30f0,0x186,_DAT_004a195c,0);
        _DAT_004a195c = SendMessageA(DAT_005e30f0,0x188,0,0);
      }
      uVar4 = 1;
    }
    break;
  case 0x111:
    if (param_3 >> 0x10 == 1) {
      _DAT_004a195c = SendMessageA(DAT_005e30f0,0x188,0,0);
      UVar2 = GetDlgItemTextA(param_1,0x402,&DAT_005e1fd8,0x46);
      if ((UVar2 == 0) || (_DAT_004a195c == -1)) {
        LVar7 = 1;
        WVar6 = 0;
        UVar2 = 0x470;
        pHVar3 = GetParent(param_1);
        PostMessageA(pHVar3,UVar2,WVar6,LVar7);
      }
      else {
        LVar7 = 3;
        WVar6 = 0;
        UVar2 = 0x470;
        pHVar3 = GetParent(param_1);
        PostMessageA(pHVar3,UVar2,WVar6,LVar7);
      }
      return 1;
    }
    if (((param_3 & 0xffff) == 0x402) && (param_3 >> 0x10 == 0x300)) {
      UVar2 = GetDlgItemTextA(param_1,0x402,&DAT_005e1fd8,0x46);
      if ((UVar2 == 0) || (_DAT_004a195c == 0xffffffff)) {
        LVar7 = 1;
        WVar6 = 0;
        UVar2 = 0x470;
        pHVar3 = GetParent(param_1);
        PostMessageA(pHVar3,UVar2,WVar6,LVar7);
      }
      else {
        LVar7 = 3;
        WVar6 = 0;
        UVar2 = 0x470;
        pHVar3 = GetParent(param_1);
        PostMessageA(pHVar3,UVar2,WVar6,LVar7);
      }
    }
  default:
switchD_0044cb09_caseD_4f:
    uVar4 = 0;
  }
  return uVar4;
}
```

---

## FUN_0044e440 — 0x44e440

- Classification : internal
- Corps : `0x44e440–0x44e48e`
- État : pseudocode obtenu
- Evidence : `ev_875dbfd40c7764617cbbeb079c9825b52298a38de981ecfc3711162a0a809792`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044e440(void)

{
  undefined4 uVar1;
  int local_c;
  
  for (local_c = 0; local_c < 8; local_c = local_c + 1) {
    DAT_004a257b = (char)local_c + '0';
    uVar1 = thunk_FUN_00429ebe(&DAT_004a2574,0);
    *(undefined4 *)(&DAT_005e4c30 + local_c * 4) = uVar1;
  }
  return;
}
```

---

## FUN_0044e48f — 0x44e48f

- Classification : internal
- Corps : `0x44e48f–0x44e4f7`
- État : pseudocode obtenu
- Evidence : `ev_603f454f2f767950881722a3298d4e33f61e1efb956b030356c5667b8e501bee`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012a3` — `thunk_FUN_0046c17b`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x4a24e8` — "TRIBE0"

### Pseudocode Ghidra

```c
int FUN_0044e48f(void)

{
  int iVar1;
  int iVar2;
  int local_10;
  
  iVar1 = thunk_FUN_0046c17b();
  if (iVar1 != 0) {
    for (local_10 = 0; local_10 < 8; local_10 = local_10 + 1) {
      iVar2 = __strcmpi((char *)(iVar1 + 0x20),s_TRIBE0_004a24e8 + local_10 * 0x10);
      if (iVar2 == 0) {
        return local_10;
      }
    }
  }
  return -1;
}
```

---

## FUN_0044e4f8 — 0x44e4f8

- Classification : internal
- Corps : `0x44e4f8–0x44e612`
- État : pseudocode obtenu
- Evidence : `ev_692b7d30a87f3044765a52264546a7ccade65e9667ae8532562f62f4b2813ef8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476ce4` — `FUN_00476ce4`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0044e4f8(int param_1,int param_2)

{
  float10 fVar1;
  int local_c;
  
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    fVar1 = (float10)FUN_00476ce4((double)((param_1 - *(int *)(&DAT_004a24c8 + local_c * 4)) *
                                           (param_1 - *(int *)(&DAT_004a24c8 + local_c * 4)) +
                                          (param_2 - *(int *)(&DAT_004a24d8 + local_c * 4)) *
                                          (param_2 - *(int *)(&DAT_004a24d8 + local_c * 4))));
    if ((float)fVar1 < 50.0) {
      return local_c;
    }
  }
  fVar1 = (float10)FUN_00476ce4((double)((param_1 + -0x140) * (param_1 + -0x140) +
                                        (param_2 + -0xf0) * (param_2 + -0xf0)));
  if (((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) || (DAT_004befe0 == 0)) {
    if ((float)fVar1 < 100.0) {
      return 4;
    }
    if ((float)fVar1 < 200.0) {
      return 5;
    }
  }
  return -1;
}
```

---

## FUN_0044e613 — 0x44e613

- Classification : internal
- Corps : `0x44e613–0x44e703`
- État : pseudocode obtenu
- Evidence : `ev_717c6e0943cbfbac58e32e24e69adbb7c56f395b1e91e4215aac199ae4c6ba80`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401712` — `thunk_FUN_004289a7`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x472c6c` — `__ftol`
- `0x476ce4` — `FUN_00476ce4`

### Chaînes référencées

- `0x4a2580` — "ABS(lasty-240)<=NEWGAMERADIUS"
- `0x4a25a0` — "C:\\float\\src\\newgame.cpp"

### Pseudocode Ghidra

```c
void FUN_0044e613(int param_1,int param_2,int *param_3,int *param_4,int *param_5)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (param_2 + -0xf0 < 0) {
    iVar3 = -(param_2 + -0xf0);
  }
  else {
    iVar3 = param_2 + -0xf0;
  }
  if (iVar3 < 0xc9) {
    uVar4 = 0;
  }
  else {
    uVar4 = thunk_FUN_00414b64(s_C__float_src_newgame_cpp_004a25a0,0x82,
                               s_ABS_lasty_240_<_NEWGAMERADIUS_004a2580);
  }
  uVar1 = thunk_FUN_0042de03();
  iVar2 = thunk_FUN_004289a7();
  *param_4 = param_2 + 3 + iVar2;
  iVar2 = 40000 - (*param_4 + -0xf0) * (*param_4 + -0xf0);
  FUN_00476ce4((double)iVar2,iVar2,uVar4,iVar3,uVar1);
  iVar3 = __ftol();
  if (param_1 < 0x140) {
    *param_3 = 0x14;
    *param_5 = 0x13b - iVar3;
  }
  else {
    *param_3 = iVar3 + 0x145;
    *param_5 = 0x26c;
  }
  return;
}
```

---

## FUN_0044e704 — 0x44e704

- Classification : internal
- Corps : `0x44e704–0x44e757`
- État : pseudocode obtenu
- Evidence : `ev_fdda9e038b356415d9f32f827de41d2872a46b69b851484080e0ae1be2cea6cd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013d9` — `thunk_FUN_0044e774`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0044e704(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491a69;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004946e0;
  thunk_FUN_0044e774();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_0044e758 — 0x44e758

- Classification : internal
- Corps : `0x44e758–0x44e773`
- État : pseudocode obtenu
- Evidence : `ev_9d8eb59a881ce141acfcc4417ac485c857ffaf263f33d811e8cb3f1d8a8cc8fc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044e758(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004946e0;
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_0044e774 — 0x44e774

- Classification : internal
- Corps : `0x44e774–0x44e77e`
- État : pseudocode obtenu
- Evidence : `ev_3faadf50f45511fa1f7ede8c6cf611befa04014cc5a5315d4c17febdf3c2c87b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044e774(void)

{
  return;
}
```

---


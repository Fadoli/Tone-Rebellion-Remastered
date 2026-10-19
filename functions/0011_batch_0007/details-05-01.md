# 0011_batch_0007 — détails (1/3)

## FUN_0042be7a — 0x42be7a

- Classification : internal
- Corps : `0x42be7a–0x42be88`
- État : pseudocode obtenu
- Evidence : `ev_3b3bc736f4dc00be75610c863c7693d7ef2b04bee108b54fcdff0b41e0d59bd9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4020cc` — `thunk_FUN_00428800`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042be7a(void)

{
  thunk_FUN_00428800();
  return;
}
```

---

---

## FUN_0042be89 — 0x42be89

- Classification : internal
- Corps : `0x42be89–0x42be92`
- État : pseudocode obtenu
- Evidence : `ev_ee18c6369819ba1235767fb35e680536b4f4017b699cc73b0cf92a46607d366b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x42be93` — `FUN_0042be93`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042be89(void)

{
  FUN_0042be93();
  return;
}
```

---

---

## FUN_0042be93 — 0x42be93

- Classification : internal
- Corps : `0x42be93–0x42bea1`
- État : pseudocode obtenu
- Evidence : `ev_d6b796a70949528cb3253f4c88d93b09fe1d7246b72ed9768d31e32108e9dcab`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4020cc` — `thunk_FUN_00428800`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042be93(void)

{
  thunk_FUN_00428800();
  return;
}
```

---

---

## FUN_0042bea2 — 0x42bea2

- Classification : internal
- Corps : `0x42bea2–0x42bef6`
- État : pseudocode obtenu
- Evidence : `ev_57e33531aa76713a27ead2869f92743db179033f3d32f2794382e049d0dde494`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042bea2(void)

{
  undefined4 local_8;
  
  local_8 = DAT_005c30e8;
  if (DAT_0049e138 == 0) {
  }
  else if (DAT_0049e138 == 1) {
    local_8 = DAT_005c30ec;
  }
  else if ((DAT_0049e138 == 3) || (DAT_0049e138 == 2)) {
    local_8 = DAT_005c30f4;
  }
  return local_8;
}
```

---

---

## FUN_0042bef7 — 0x42bef7

- Classification : internal
- Corps : `0x42bef7–0x42bfa8`
- État : pseudocode obtenu
- Evidence : `ev_8ac7a4d8d7e3b4a27e6884ceccb13b6c1b7636e701a37947bb07eec108ed074a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40149c` — `thunk_FUN_00414bc2`
- `0x4022de` — `thunk_FUN_0042d9cd`

### Chaînes référencées

- `0x49e160` — "r == DD_OK"
- `0x49e16c` — "C:\\float\\src\\graphsys.cpp"
- `0x49e188` — "r == DD_OK"
- `0x49e194` — "C:\\float\\src\\graphsys.cpp"

### Pseudocode Ghidra

```c
void FUN_0042bef7(void)

{
  int iVar1;
  
  if ((DAT_005c30e8 != (int *)0x0) &&
     (iVar1 = (**(code **)(*DAT_005c30e8 + 0x6c))(DAT_005c30e8), iVar1 != 0)) {
    thunk_FUN_00414bc2(s_C__float_src_graphsys_cpp_0049e16c,0x9f,s_r____DD_OK_0049e160,iVar1);
  }
  if ((DAT_005c30f0 != (int *)0x0) &&
     (iVar1 = (**(code **)(*DAT_005c30f0 + 0x6c))(DAT_005c30f0), iVar1 != 0)) {
    thunk_FUN_00414bc2(s_C__float_src_graphsys_cpp_0049e194,0xa5,s_r____DD_OK_0049e188,iVar1);
  }
  thunk_FUN_0042d9cd(3);
  DAT_005c311c = 1;
  return;
}
```

---

---

## FUN_0042bfa9 — 0x42bfa9

- Classification : internal
- Corps : `0x42bfa9–0x42c07c`
- État : pseudocode obtenu
- Evidence : `ev_fcb5b3b03e075931ad8c531eafaf5aae4c19d0954d66e44d0cc7b4cbfd9721a0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a28` — `thunk_FUN_0041081b`
- `0x401f5f` — `thunk_FUN_0042dc4e`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042bfa9(void)

{
  undefined1 uVar1;
  int local_308;
  undefined1 local_304 [768];
  
  thunk_FUN_0042dc4e();
  for (local_308 = 1; local_308 < 7; local_308 = local_308 + 1) {
    uVar1 = thunk_FUN_0041081b(local_304,(double)*(byte *)(local_308 * 3 + 0x49e148),
                               (double)*(byte *)(local_308 * 3 + 0x49e149),
                               (double)*(byte *)(local_308 * 3 + 0x49e14a));
    (&DAT_0049e140)[local_308] = uVar1;
  }
  return;
}
```

---

---

## FUN_0042c07d — 0x42c07d

- Classification : internal
- Corps : `0x42c07d–0x42c0f9`
- État : pseudocode obtenu
- Evidence : `ev_c6bf9fa5bc7603e89bbd0e32b15858e5f9cf615dfbb82a4b40447ec81edce1f0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4737e0` — `_strncpy`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042c07d(int param_1)

{
  int local_8;
  
  if (param_1 < DAT_005c3120) {
    for (local_8 = param_1; local_8 < DAT_005c3120 + -1; local_8 = local_8 + 1) {
      _strncpy(&DAT_005c20a0 + local_8 * 100,&DAT_005c20a0 + (local_8 + 1) * 100,100);
      *(undefined4 *)(&DAT_005c3048 + local_8 * 4) = *(undefined4 *)(&DAT_005c304c + local_8 * 4);
    }
    DAT_005c3120 = DAT_005c3120 + -1;
  }
  return;
}
```

---

---

## FUN_0042c0fa — 0x42c0fa

- Classification : internal
- Corps : `0x42c0fa–0x42c4ce`
- État : pseudocode obtenu
- Evidence : `ev_c7c31abc235ec681eacf6fb5287255a35eaad75dcc08d0672681b03e28502f08`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x50` — `USER32.DLL::ReleaseDC`
- `EXTERNAL:0x6b` — `USER32.DLL::GetDC`
- `EXTERNAL:0x6d` — `GDI32.DLL::SetDIBColorTable`
- `EXTERNAL:0x6e` — `GDI32.DLL::SelectObject`
- `EXTERNAL:0x6f` — `GDI32.DLL::GetSystemPaletteEntries`
- `EXTERNAL:0x70` — `GDI32.DLL::CreateCompatibleDC`
- `EXTERNAL:0x73` — `GDI32.DLL::CreateDIBSection`
- `0x401749` — `thunk_FUN_00414c97`
- `0x401b54` — `thunk_FUN_0042c608`
- `0x401c9e` — `thunk_FUN_00428884`
- `0x402176` — `thunk_FUN_00414bf7`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x472a50` — `DDRAW.DLL::DirectDrawCreate`

### Chaînes référencées

- `0x49e1b0` — "data\\bigfont.fnt"
- `0x49e1c4` — "data\\smfont.fnt"
- `0x49e1d4` — "CreateDIBSection() failed."
- `0x49e1f0` — "Bitmap DC creation failed."
- `0x49e20c` — "DirectDrawCreate failed: %x"
- `0x49e228` — "Not enough video memory: %d"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0042c0fa(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  RGBQUAD local_768 [256];
  undefined4 local_368 [91];
  HDC local_1fc;
  BITMAPINFO *local_1f8;
  undefined4 *local_1f4;
  int local_1f0;
  int local_1ec;
  BITMAPINFO *local_1e8;
  undefined4 local_1e4 [16];
  int local_1a4;
  int local_78;
  undefined4 local_74 [2];
  int local_6c;
  int local_64;
  UINT local_8;
  
  if (DAT_005c30cc == 0) {
    DAT_005c30dc = DAT_004c2b10;
    DAT_005c30a0 = 0;
    DAT_005c30a4 = 0;
    _DAT_005c30a8 = 0;
    _DAT_005c30ac = 0;
    _DAT_005c30b0 = 0;
    puVar2 = &DAT_005c30a0;
    puVar3 = &DAT_005c1888;
    for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    local_1fc = (HDC)0x0;
    thunk_FUN_00428884(s_data_bigfont_fnt_0049e1b0);
    thunk_FUN_00428884(s_data_smfont_fnt_0049e1c4);
    local_1f8 = (BITMAPINFO *)thunk_FUN_00414bf7(0x428);
    (local_1f8->bmiHeader).biSize = 0x28;
    (local_1f8->bmiHeader).biWidth = 0x280;
    (local_1f8->bmiHeader).biHeight = -0x1e0;
    (local_1f8->bmiHeader).biPlanes = 1;
    (local_1f8->bmiHeader).biBitCount = 8;
    (local_1f8->bmiHeader).biCompression = 0;
    (local_1f8->bmiHeader).biSizeImage = 0;
    (local_1f8->bmiHeader).biClrUsed = 0;
    (local_1f8->bmiHeader).biClrImportant = 0;
    for (local_1f0 = 0; local_1f0 < 0x100; local_1f0 = local_1f0 + 1) {
      local_1f8->bmiColors[local_1f0].rgbReserved = '\0';
    }
    local_1e8 = local_1f8;
    local_1fc = GetDC(DAT_004c2b58);
    DAT_005c310c = CreateDIBSection(local_1fc,local_1e8,0,(void **)&DAT_005c3114,(HANDLE)0x0,0);
    if (DAT_005c310c == (HBITMAP)0x0) {
      thunk_FUN_00414ad0(s_CreateDIBSection___failed__0049e1d4);
      iVar1 = 0;
    }
    else {
      DAT_005c3110 = CreateCompatibleDC(local_1fc);
      if (DAT_005c3110 == (HDC)0x0) {
        thunk_FUN_00414ad0(s_Bitmap_DC_creation_failed__0049e1f0);
        iVar1 = 0;
      }
      else {
        GetSystemPaletteEntries(local_1fc,0,0x100,(LPPALETTEENTRY)&DAT_005c18a0);
        ReleaseDC(DAT_004c2b58,local_1fc);
        thunk_FUN_00414c97(local_1e8);
        SelectObject(DAT_005c3110,DAT_005c310c);
        for (local_1f0 = 0; local_1f0 < 0x100; local_1f0 = local_1f0 + 1) {
          local_768[local_1f0].rgbRed = (&DAT_005c18a0)[local_1f0 * 4];
          local_768[local_1f0].rgbGreen = (&DAT_005c18a1)[local_1f0 * 4];
          local_768[local_1f0].rgbBlue = (&DAT_005c18a2)[local_1f0 * 4];
          local_768[local_1f0].rgbReserved = '\0';
        }
        local_8 = SetDIBColorTable(DAT_005c3110,0,0x100,local_768);
        local_1f4 = (undefined4 *)0x0;
        local_8 = DirectDrawCreate(0,&local_1f4,0);
        if (local_8 == 0) {
          local_8 = (**(code **)*local_1f4)(local_1f4,&DAT_00494208,&DAT_005c30e4);
          local_1e4[0] = 0x16c;
          local_368[0] = 0x16c;
          (**(code **)(*DAT_005c30e4 + 0x2c))(DAT_005c30e4,local_1e4,local_368);
          local_74[0] = 0x6c;
          (**(code **)(*DAT_005c30e4 + 0x30))(DAT_005c30e4,local_74);
          local_1ec = local_64 * local_6c;
          local_78 = local_1ec + local_1a4;
          if (local_78 < 0x100000) {
            thunk_FUN_00414ad0(s_Not_enough_video_memory___d_0049e228,local_78);
          }
          DAT_005c30cc = 1;
          iVar1 = thunk_FUN_0042c608(param_1);
          DAT_005c30cc = iVar1;
        }
        else {
          thunk_FUN_00414ad0(s_DirectDrawCreate_failed___x_0049e20c,local_8);
          iVar1 = 0;
        }
      }
    }
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}
```

---

---

## FUN_0042c4cf — 0x42c4cf

- Classification : internal
- Corps : `0x42c4cf–0x42c607`
- État : pseudocode obtenu
- Evidence : `ev_174379af86c2a90ada76f55cee901284b6755bb1812259ef5b142bf87afcd155`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401555` — `thunk_FUN_0042d647`
- `0x401749` — `thunk_FUN_00414c97`
- `0x401ded` — `thunk_FUN_0042d38a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042c4cf(void)

{
  thunk_FUN_0042d38a();
  thunk_FUN_0042d647();
  if (DAT_005c30f4 != (int *)0x0) {
    (**(code **)(*DAT_005c30f4 + 8))(DAT_005c30f4);
    DAT_005c30f4 = (int *)0x0;
  }
  if (DAT_005c30f0 != (int *)0x0) {
    (**(code **)(*DAT_005c30f0 + 8))(DAT_005c30f0);
    DAT_005c30f0 = (int *)0x0;
  }
  if (DAT_005c30ec != (int *)0x0) {
    (**(code **)(*DAT_005c30ec + 8))(DAT_005c30ec);
    DAT_005c30ec = (int *)0x0;
  }
  if (DAT_005c30e8 != (int *)0x0) {
    (**(code **)(*DAT_005c30e8 + 8))(DAT_005c30e8);
    DAT_005c30e8 = (int *)0x0;
  }
  if (DAT_005c30f8 != (int *)0x0) {
    (**(code **)(*DAT_005c30f8 + 8))(DAT_005c30f8);
    DAT_005c30f8 = (int *)0x0;
  }
  if (DAT_005c30e4 != (int *)0x0) {
    (**(code **)(*DAT_005c30e4 + 8))(DAT_005c30e4);
    DAT_005c30e4 = (int *)0x0;
  }
  if ((DAT_0049e138 == 4) && (DAT_005c1888 != 0)) {
    thunk_FUN_00414c97(DAT_005c1888);
    DAT_005c1888 = 0;
  }
  thunk_FUN_00414c97(DAT_005c2870);
  thunk_FUN_00414c97(DAT_005c30b8);
  DAT_005c30cc = 0;
  return;
}
```

---

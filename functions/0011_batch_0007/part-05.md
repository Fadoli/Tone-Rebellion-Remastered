# 0011_batch_0007 — détails (5/6)

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

## FUN_0042c608 — 0x42c608

- Classification : internal
- Corps : `0x42c608–0x42cbb5`
- État : pseudocode obtenu
- Evidence : `ev_0f9c69fb8878dfda9b45974ac4671e155f94d1d65c3c29e14bd351d54770764b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x57` — `USER32.DLL::GetSystemMetrics`
- `EXTERNAL:0x68` — `USER32.DLL::SetWindowLongA`
- `EXTERNAL:0x69` — `USER32.DLL::MoveWindow`
- `EXTERNAL:0x6a` — `USER32.DLL::SetCursor`
- `0x401555` — `thunk_FUN_0042d647`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x40232e` — `thunk_FUN_0042da69`

### Chaînes référencées

- `0x49e244` — "GSDM_VidFront"
- `0x49e254` — "GSDM_VidBack"
- `0x49e264` — "GSDM_SysToVidFront"
- `0x49e278` — "GSDM_SysToVidBack"
- `0x49e28c` — "GSDM_Bitmap"
- `0x49e28c` — "GSDM_Bitmap"
- `0x49e298` — "Start exclusive mode failed: %d"
- `0x49e2b8` — "Display changed to %dx%dx8."
- `0x49e2d4` — "Display change failed: %x"
- `0x49e2f0` — "Stop exclusive mode failed: %d"
- `0x49e310` — "Primary surface creation failed."
- `0x49e334` — "Back buffer setup failed: %x"
- `0x49e354` — "CreatePalette failed: %d"
- `0x49e370` — "DDRAW SetPalette failed: %x"
- `0x49e38c` — "Bkg CreateSurface failed: %x"
- `0x49e3ac` — "SysMemSurface creation failed: %d"
- `0x49e3d0` — "Primary surface restore failed: %d"
- `0x49e3f4` — "Bkg surface restore failed: %d"
- `0x49e414` — "Draw method set to %s"

### Pseudocode Ghidra

```c
undefined4 FUN_0042c608(int param_1)

{
  int iVar1;
  int iVar2;
  BOOL bRepaint;
  undefined4 local_90;
  undefined4 local_84;
  int local_80;
  int local_7c;
  undefined4 local_78;
  undefined4 local_74;
  int local_70;
  int local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_54;
  int local_24;
  undefined4 local_10;
  uint local_c;
  char *local_8;
  
  if ((DAT_005c30cc == 0) || (param_1 == DAT_0049e138)) {
    return 0;
  }
  local_78 = 0x6c;
  local_8 = &DAT_005c3124;
  local_80 = 0;
  local_7c = 0;
  switch(DAT_0049e138) {
  case 0:
    local_80 = 1;
    break;
  case 1:
    local_80 = 1;
    break;
  case 2:
    local_80 = 1;
    break;
  case 3:
    local_80 = 1;
  }
  switch(param_1) {
  case 0:
    local_7c = 1;
    local_8 = s_GSDM_VidFront_0049e244;
    break;
  case 1:
    local_7c = 1;
    local_8 = s_GSDM_VidBack_0049e254;
    break;
  case 2:
    local_7c = 1;
    local_8 = s_GSDM_SysToVidFront_0049e264;
    break;
  case 3:
    local_7c = 1;
    local_8 = s_GSDM_SysToVidBack_0049e278;
    break;
  case 4:
    local_8 = s_GSDM_Bitmap_0049e28c;
  }
  if ((local_80 == 0) && (local_7c == 1)) {
    SetWindowLongA(DAT_004c2b58,-0x10,-0x70000000);
    local_c = (**(code **)(*DAT_005c30e4 + 0x50))(DAT_005c30e4,DAT_004c2b58,0x13);
    if (local_c != 0) {
      thunk_FUN_00414ad0(s_Start_exclusive_mode_failed___d_0049e298,local_c & 0xffff);
      return 0;
    }
    (**(code **)(*DAT_005c30e4 + 0x30))(DAT_005c30e4,&local_78);
    if (((local_6c != 0x280) || (local_70 != 0x1e0)) || (local_24 != 8)) {
      local_c = (**(code **)(*DAT_005c30e4 + 0x54))(DAT_005c30e4,0x280,0x1e0,8,0,0);
      if (local_c != 0) {
        thunk_FUN_00414ad0(s_Display_change_failed___x_0049e2d4,local_c);
        return 0;
      }
      thunk_FUN_00414ad0(s_Display_changed_to__dx_dx8__0049e2b8,0x280,0x1e0);
    }
  }
  else if (local_7c == 0) {
    local_c = (**(code **)(*DAT_005c30e4 + 0x50))(DAT_005c30e4,DAT_004c2b58,8);
    if (local_c != 0) {
      thunk_FUN_00414ad0(s_Stop_exclusive_mode_failed___d_0049e2f0,local_c & 0xffff);
      return 0;
    }
    SetWindowLongA(DAT_004c2b58,-0x10,-0x6f360000);
    bRepaint = 1;
    iVar1 = GetSystemMetrics(8);
    iVar2 = GetSystemMetrics(0x1f);
    iVar1 = iVar2 + 0x1e0 + iVar1 * 2;
    iVar2 = GetSystemMetrics(7);
    MoveWindow(DAT_004c2b58,0,0,iVar2 * 2 + 0x280,iVar1,bRepaint);
  }
  if ((local_7c == 1) && (DAT_005c30d8 == 0)) {
    local_74 = 0x21;
    local_10 = 0x218;
    local_64 = 1;
    local_c = (**(code **)(*DAT_005c30e4 + 0x18))(DAT_005c30e4,&local_78,&DAT_005c30e8,0);
    if (local_c != 0) {
      thunk_FUN_00414ad0(s_Primary_surface_creation_failed__0049e310);
      return 0;
    }
    local_84 = 4;
    local_c = (**(code **)(*DAT_005c30e8 + 0x30))(DAT_005c30e8,&local_84,&DAT_005c30ec);
    if (local_c != 0) {
      thunk_FUN_00414ad0(s_Back_buffer_setup_failed___x_0049e334,local_c);
      return 0;
    }
    local_c = (**(code **)(*DAT_005c30e4 + 0x14))(DAT_005c30e4,0x4c,&DAT_005c18a0,&DAT_005c30f8,0);
    if (local_c != 0) {
      thunk_FUN_00414ad0(s_CreatePalette_failed___d_0049e354,local_c & 0xffff);
    }
    local_c = (**(code **)(*DAT_005c30e8 + 0x7c))(DAT_005c30e8,DAT_005c30f8);
    if (local_c != 0) {
      thunk_FUN_00414ad0(s_DDRAW_SetPalette_failed___x_0049e370,local_c);
      return 0;
    }
    local_74 = 7;
    local_10 = 0x4040;
    local_6c = 0x280;
    local_70 = 0x1e0;
    local_c = (**(code **)(*DAT_005c30e4 + 0x18))(DAT_005c30e4,&local_78,&DAT_005c30f0,0);
    if (local_c != 0) {
      thunk_FUN_00414ad0(s_Bkg_CreateSurface_failed___x_0049e38c,local_c);
      return 0;
    }
    local_74 = 7;
    local_10 = 0x840;
    local_6c = 0x280;
    local_70 = 0x1e0;
    local_c = (**(code **)(*DAT_005c30e4 + 0x18))(DAT_005c30e4,&local_78,&DAT_005c30f4,0);
    if (local_c != 0) {
      thunk_FUN_00414ad0(s_SysMemSurface_creation_failed____0049e3ac,local_c & 0xffff);
      return 0;
    }
    local_c = (**(code **)(*DAT_005c30f4 + 100))(DAT_005c30f4,0,&local_78,1,0);
    (**(code **)(*DAT_005c30f4 + 0x80))(DAT_005c30f4,local_54);
    DAT_005c30fc = local_54;
    DAT_005c3104 = local_68;
    DAT_005c30d8 = 1;
  }
  else if ((local_7c == 1) && (local_80 == 0)) {
    local_c = (**(code **)(*DAT_005c30e8 + 0x6c))(DAT_005c30e8);
    if (local_c != 0) {
      thunk_FUN_00414ad0(s_Primary_surface_restore_failed____0049e3d0,local_c & 0xffff);
      return 0;
    }
    local_c = (**(code **)(*DAT_005c30f0 + 0x6c))(DAT_005c30f0);
    if (local_c != 0) {
      thunk_FUN_00414ad0(s_Bkg_surface_restore_failed___d_0049e3f4,local_c & 0xffff);
      return 0;
    }
  }
  if (DAT_005c30a0 != 0) {
    thunk_FUN_0042d38a();
  }
  if (DAT_005c1888 != 0) {
    thunk_FUN_0042d647();
  }
  if ((param_1 == 1) || (param_1 == 0)) {
    local_90 = 1;
  }
  else {
    local_90 = 0;
  }
  DAT_005c30d0 = local_90;
  SetCursor(DAT_005c30dc);
  DAT_0049e138 = param_1;
  thunk_FUN_0042da69(0,0x100,0);
  thunk_FUN_00414ad0(s_Draw_method_set_to__s_0049e414,local_8);
  return 1;
}
```

---

## FUN_0042cbda — 0x42cbda

- Classification : internal
- Corps : `0x42cbda–0x42cc23`
- État : pseudocode obtenu
- Evidence : `ev_100a738c85dbd92b313f058971adecf1f6dd64a5d96e8c0360d1718fa9ebe889`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f5f` — `thunk_FUN_0042dc4e`
- `0x40232e` — `thunk_FUN_0042da69`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0042cbda(undefined4 param_1)

{
  undefined1 local_304 [768];
  
  _DAT_0049e13c = param_1;
  if (DAT_005c30cc != 0) {
    thunk_FUN_0042dc4e(0,0x100,local_304);
    thunk_FUN_0042da69(0,0x100,local_304);
  }
  return;
}
```

---

## FUN_0042cc24 — 0x42cc24

- Classification : internal
- Corps : `0x42cc24–0x42d27e`
- État : pseudocode obtenu
- Evidence : `ev_29e8acc9ef214546bdb7036b2cbf1e88ffe8105275d37ccc324960fffcdd8da8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x50` — `USER32.DLL::ReleaseDC`
- `EXTERNAL:0x66` — `USER32.DLL::GetCursorPos`
- `EXTERNAL:0x67` — `USER32.DLL::SetCursorPos`
- `EXTERNAL:0x6b` — `USER32.DLL::GetDC`
- `EXTERNAL:0x75` — `GDI32.DLL::BitBlt`
- `0x401276` — `thunk_FUN_0042dd95`
- `0x401712` — `thunk_FUN_004289a7`
- `0x4017df` — `thunk_FUN_0041be72`
- `0x401c35` — `thunk_FUN_0042c07d`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402338` — `thunk_FUN_0042bef7`

### Chaînes référencées

- `0x49e42c` — "GSNumInvalidRects < MAX_INVALID_RECTS"
- `0x49e454` — "C:\\float\\src\\graphsys.cpp"
- `0x49e470` — "Flip failed: %d"
- `0x49e480` — "Back to front blit failed: %d"
- `0x49e4a0` — "BitBlt failed."

### Pseudocode Ghidra

```c
undefined4 FUN_0042cc24(void)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  HDC hDC;
  BOOL BVar4;
  undefined *local_74;
  undefined4 *local_6c;
  int local_68;
  int local_64;
  undefined *local_60;
  undefined4 *local_5c;
  int local_58;
  int local_54;
  undefined *local_50;
  undefined4 *local_4c;
  int local_48;
  int local_44;
  undefined *local_40;
  undefined4 *local_3c;
  int local_38;
  int local_34;
  tagPOINT local_28;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  uint local_c;
  int local_8;
  
  DAT_005c311c = 0;
  if (DAT_005c30cc == 0) {
    uVar1 = 0;
  }
  else {
    if (DAT_005c3118 < 0x40) {
      uVar1 = 0;
    }
    else {
      uVar1 = thunk_FUN_00414b64(s_C__float_src_graphsys_cpp_0049e454,0x2b6,
                                 s_GSNumInvalidRects_<_MAX_INVALID__0049e42c);
    }
    if (DAT_005c30d4 == 0) {
      local_1c = 0;
      local_18 = 0;
      local_14 = 0x280;
      local_10 = 0x1e0;
      local_8 = 0;
      local_20 = 0;
      while (local_20 < DAT_005c3120) {
        uVar2 = thunk_FUN_0041be72();
        if (*(uint *)(&DAT_005c3048 + local_20 * 4) < uVar2) {
          thunk_FUN_0042c07d(local_20);
        }
        else {
          if (local_8 == 0) {
            thunk_FUN_0042d28f();
            local_8 = 1;
          }
          iVar3 = thunk_FUN_004289a7();
          thunk_FUN_0042dd95(0,iVar3 * local_20,&DAT_005c20a0 + local_20 * 100);
          local_20 = local_20 + 1;
        }
      }
      if (local_8 != 0) {
        thunk_FUN_0042d38a();
      }
      iVar3 = DAT_0049e138 + -1;
      switch(iVar3) {
      case 0:
        while (local_c = (**(code **)(*DAT_005c30e8 + 0x2c))(DAT_005c30e8,0,1,iVar3,uVar1),
              local_c == 0x887601c2) {
          thunk_FUN_0042bef7();
        }
        if (local_c != 0) {
          thunk_FUN_00414ad0(s_Flip_failed___d_0049e470,local_c & 0xffff);
          return 0;
        }
        local_34 = DAT_005c3118;
        local_3c = (undefined4 *)&DAT_005c1ca0;
        local_40 = &DAT_005c2888;
        if ((DAT_005c3098 & 2) != 0) {
          local_34 = 1;
          local_3c = &local_1c;
          local_40 = &DAT_005c3098;
        }
        local_c = 0;
        for (local_38 = 0; local_38 < local_34; local_38 = local_38 + 1) {
          if ((local_40[local_38] & 2) != 0) {
            while (local_c = (**(code **)(*DAT_005c30ec + 0x14))
                                       (DAT_005c30ec,local_3c + local_38 * 4,DAT_005c30e8,
                                        local_3c + local_38 * 4,0x1000000,0), local_c == 0x887601c2)
            {
              thunk_FUN_0042bef7();
            }
            if (local_c != 0) {
              thunk_FUN_00414ad0(s_Back_to_front_blit_failed___d_0049e480,local_c & 0xffff);
              return 0;
            }
          }
        }
        break;
      case 1:
        local_44 = DAT_005c3118;
        local_4c = (undefined4 *)&DAT_005c1ca0;
        local_50 = &DAT_005c2888;
        if ((DAT_005c3098 & 1) != 0) {
          local_44 = 1;
          local_4c = &local_1c;
          local_50 = &DAT_005c3098;
        }
        for (local_48 = 0; local_48 < local_44; local_48 = local_48 + 1) {
          if ((local_50[local_48] & 1) != 0) {
            while (local_c = (**(code **)(*DAT_005c30e8 + 0x14))
                                       (DAT_005c30e8,local_4c + local_48 * 4,DAT_005c30f4,
                                        local_4c + local_48 * 4,0x1000000,0), local_c != 0) {
              if (local_c == 0x887601c2) {
                thunk_FUN_0042bef7();
              }
              else if (local_c != 0x8876021c) {
                return 0;
              }
            }
          }
        }
        break;
      case 2:
        local_54 = DAT_005c3118;
        local_5c = (undefined4 *)&DAT_005c1ca0;
        local_60 = &DAT_005c2888;
        if ((DAT_005c3098 & 1) != 0) {
          local_54 = 1;
          local_5c = &local_1c;
          local_60 = &DAT_005c3098;
        }
        for (local_58 = 0; local_58 < local_54; local_58 = local_58 + 1) {
          if ((local_60[local_58] & 1) != 0) {
            while (local_c = (**(code **)(*DAT_005c30ec + 0x14))
                                       (DAT_005c30ec,local_5c + local_58 * 4,DAT_005c30f4,
                                        local_5c + local_58 * 4,0x1000000,0), local_c != 0) {
              if (local_c == 0x887601c2) {
                thunk_FUN_0042bef7();
              }
              else if (local_c != 0x8876021c) {
                return 0;
              }
            }
          }
        }
        while (local_c = (**(code **)(*DAT_005c30e8 + 0x2c))(DAT_005c30e8,0,1),
              local_c == 0x887601c2) {
          thunk_FUN_0042bef7();
        }
        if (local_c != 0) {
          return 0;
        }
        local_54 = DAT_005c3118;
        local_5c = (undefined4 *)&DAT_005c1ca0;
        local_60 = &DAT_005c2888;
        if ((DAT_005c3098 & 2) != 0) {
          local_54 = 1;
          local_5c = &local_1c;
          local_60 = &DAT_005c3098;
        }
        local_c = 0;
        for (local_58 = 0; local_58 < local_54; local_58 = local_58 + 1) {
          if ((local_60[local_58] & 2) != 0) {
            while (local_c = (**(code **)(*DAT_005c30ec + 0x14))
                                       (DAT_005c30ec,local_5c + local_58 * 4,DAT_005c30e8,
                                        local_5c + local_58 * 4,0x1000000,0), local_c == 0x887601c2)
            {
              thunk_FUN_0042bef7();
            }
            if (local_c != 0) {
              return 0;
            }
          }
        }
        break;
      case 3:
        local_64 = DAT_005c3118;
        local_6c = (undefined4 *)&DAT_005c1ca0;
        local_74 = &DAT_005c2888;
        if (1 < DAT_005c3118) {
          DAT_005c3098 = DAT_005c3098 | 1;
        }
        if ((DAT_005c3098 & 1) != 0) {
          local_64 = 1;
          local_6c = &local_1c;
          local_74 = &DAT_005c3098;
        }
        hDC = GetDC(DAT_004c2b58);
        for (local_68 = 0; local_68 < local_64; local_68 = local_68 + 1) {
          if (((local_74[local_68] & 1) != 0) &&
             (BVar4 = BitBlt(hDC,local_6c[local_68 * 4],local_6c[local_68 * 4 + 1],
                             local_6c[local_68 * 4 + 2],local_6c[local_68 * 4 + 3],DAT_005c3110,
                             local_6c[local_68 * 4],local_6c[local_68 * 4 + 1],0xcc0020), BVar4 == 0
             )) {
            thunk_FUN_00414ad0(s_BitBlt_failed__0049e4a0);
          }
        }
        ReleaseDC(DAT_004c2b58,hDC);
      }
      DAT_005c3118 = 0;
      if (DAT_005c311c == 0) {
        DAT_005c3098 = 0;
      }
      GetCursorPos(&local_28);
      SetCursorPos(local_28.x,local_28.y);
      uVar1 = 1;
    }
    else {
      DAT_005c3118 = 0;
      DAT_005c3098 = 0;
      uVar1 = 1;
    }
  }
  return uVar1;
}
```

---

## FUN_0042d28f — 0x42d28f

- Classification : internal
- Corps : `0x42d28f–0x42d389`
- État : pseudocode obtenu
- Evidence : `ev_f0e8957f3ad59795107ad00e992806504e1a8fc8bde3544fc48db69ebc195a81`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401861` — `thunk_FUN_0042bea2`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x402338` — `thunk_FUN_0042bef7`

### Chaînes référencées

- `0x49e4b0` — " Lock failed: %x"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_0042d28f(void)

{
  undefined4 *puVar1;
  undefined4 local_78 [4];
  int local_68;
  int local_54;
  int *local_c;
  int local_8;
  
  if (DAT_005c30cc == 0) {
    puVar1 = (undefined4 *)0x0;
  }
  else if (DAT_005c30a0 == 0) {
    local_c = (int *)0x0;
    local_c = (int *)thunk_FUN_0042bea2();
    if ((DAT_0049e138 == 3) || (DAT_0049e138 == 2)) {
      DAT_005c30a0 = DAT_005c30fc;
      DAT_005c30a4 = DAT_005c3104 + -1;
    }
    else if (DAT_0049e138 == 4) {
      DAT_005c30a0 = DAT_005c3114;
      DAT_005c30a4 = 0x27f;
    }
    else {
      local_78[0] = 0x6c;
      while (local_8 = (**(code **)(*local_c + 100))(local_c,0,local_78,1,0), local_8 == -0x7789fe3e
            ) {
        thunk_FUN_0042bef7();
      }
      if (local_8 != 0) {
        thunk_FUN_00414ad0(s_Lock_failed___x_0049e4b0,local_8);
        return (undefined4 *)0x0;
      }
      DAT_005c30a0 = local_54;
      DAT_005c30a4 = local_68 + -1;
    }
    _DAT_005c30a8 = 0x1df;
    puVar1 = &DAT_005c30a0;
  }
  else {
    puVar1 = &DAT_005c30a0;
  }
  return puVar1;
}
```

---

## FUN_0042d38a — 0x42d38a

- Classification : internal
- Corps : `0x42d38a–0x42d3fa`
- État : pseudocode obtenu
- Evidence : `ev_fec237f415515a24d098aa09dca2357a2e41918dbd740f217e75583b5bfb4756`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401861` — `thunk_FUN_0042bea2`
- `0x402338` — `thunk_FUN_0042bef7`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042d38a(void)

{
  int *piVar1;
  int iVar2;
  
  if ((DAT_005c30cc != 0) && (DAT_005c30a0 != 0)) {
    piVar1 = (int *)thunk_FUN_0042bea2(0);
    if (((DAT_0049e138 == 0) || (DAT_0049e138 == 1)) &&
       (iVar2 = (**(code **)(*piVar1 + 0x80))(piVar1,DAT_005c30a0), iVar2 == -0x7789fe3e)) {
      thunk_FUN_0042bef7();
    }
    DAT_005c30a0 = 0;
  }
  return;
}
```

---

## FUN_0042d3fb — 0x42d3fb

- Classification : internal
- Corps : `0x42d3fb–0x42d44c`
- État : pseudocode obtenu
- Evidence : `ev_af38e8b04407f399258e363b86e85dc9d884463e8f1486995fd0cf1c77cb6006`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40144c` — `thunk_FUN_0042cc24`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x402022` — `thunk_FUN_00406604`
- `0x4022de` — `thunk_FUN_0042d9cd`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042d3fb(undefined4 param_1)

{
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_14 = 0;
  local_10 = 0;
  local_c = 0x27f;
  local_8 = 0x1df;
  local_18 = thunk_FUN_0042d28f();
  thunk_FUN_00406604(&local_18,param_1);
  thunk_FUN_0042d38a();
  thunk_FUN_0042d9cd(3);
  thunk_FUN_0042cc24();
  return;
}
```

---

## FUN_0042d44d — 0x42d44d

- Classification : internal
- Corps : `0x42d44d–0x42d597`
- État : pseudocode obtenu
- Evidence : `ev_0cad0e8c5d5dcd1b0515eed190938aa4e6dfac39ca5d33fe92f5aebf99cf192c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x402081` — `thunk_FUN_004066e3`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x402338` — `thunk_FUN_0042bef7`

### Chaînes référencées

- `0x49e4c4` — "pane && pane->window->buffer"
- `0x49e4e4` — "C:\\float\\src\\graphsys.cpp"
- `0x49e500` — "grabScreen() failed: unsupported for GSDM_Bitmap."
- `0x49e534` — " Lock: %x"

### Pseudocode Ghidra

```c
void FUN_0042d44d(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 *local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  int local_84;
  int local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74 [2];
  int local_6c;
  int local_64;
  undefined4 local_50;
  int local_8;
  
  if ((param_1 == (undefined4 *)0x0) || (*(int *)*param_1 == 0)) {
    uVar1 = thunk_FUN_00414b64(s_C__float_src_graphsys_cpp_0049e4e4,0x40d,
                               s_pane____pane_>window_>buffer_0049e4c4);
  }
  else {
    uVar1 = 0;
  }
  if (DAT_0049e138 == 4) {
    thunk_FUN_00414ad0(s_grabScreen___failed__unsupported_0049e500);
  }
  else {
    local_74[0] = 0x6c;
    while( true ) {
      local_8 = (**(code **)(*DAT_005c30e8 + 100))(DAT_005c30e8,0,local_74,1,0,uVar1);
      if (local_8 != -0x7789fe3e) break;
      thunk_FUN_0042bef7();
    }
    if (local_8 == 0) {
      local_88 = local_50;
      local_84 = local_64 + -1;
      local_80 = local_6c + -1;
      local_7c = 0;
      local_78 = 0;
      local_9c = &local_88;
      local_98 = 0;
      local_94 = 0;
      local_90 = 0x27f;
      local_8c = 0x1df;
      thunk_FUN_004066e3(&local_9c,0,0,param_1,0,0,0xffffffff);
      (**(code **)(*DAT_005c30e8 + 0x80))(DAT_005c30e8,local_88);
    }
    else {
      thunk_FUN_00414ad0(s_Lock___x_0049e534,local_8);
    }
  }
  return;
}
```

---

## FUN_0042d598 — 0x42d598

- Classification : internal
- Corps : `0x42d598–0x42d646`
- État : pseudocode obtenu
- Evidence : `ev_775cb18279b2429ed095c9c82061dcec90349c65dd123fd9d3380487b6801d53`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402298` — `thunk_FUN_00414ad0`
- `0x402338` — `thunk_FUN_0042bef7`

### Chaînes référencées

- `0x49e540` — " Lock: %x"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_0042d598(void)

{
  undefined4 *puVar1;
  undefined4 local_74 [2];
  int local_6c;
  int local_64;
  int local_50;
  int local_8;
  
  if (DAT_005c30cc == 0) {
    puVar1 = (undefined4 *)0x0;
  }
  else if (DAT_005c30d0 == 0) {
    puVar1 = (undefined4 *)0x0;
  }
  else if (DAT_005c1888 == 0) {
    local_74[0] = 0x6c;
    local_8 = (**(code **)(*DAT_005c30f0 + 100))(DAT_005c30f0,0,local_74,1,0);
    if (local_8 == -0x7789fe3e) {
      thunk_FUN_0042bef7();
    }
    else if (local_8 != 0) {
      thunk_FUN_00414ad0(s_Lock___x_0049e540,local_8);
      return (undefined4 *)0x0;
    }
    DAT_005c1888 = local_50;
    DAT_005c188c = local_64 + -1;
    _DAT_005c1890 = local_6c + -1;
    puVar1 = &DAT_005c1888;
  }
  else {
    puVar1 = &DAT_005c1888;
  }
  return puVar1;
}
```

---


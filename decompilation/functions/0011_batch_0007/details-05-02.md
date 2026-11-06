# 0011_batch_0007 — détails (2/3)

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

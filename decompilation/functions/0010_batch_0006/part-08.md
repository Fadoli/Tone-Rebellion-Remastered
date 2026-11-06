# 0010_batch_0006 — détails (8/8)

## FUN_00423068 — 0x423068

- Classification : internal
- Corps : `0x423068–0x42361c`
- État : pseudocode obtenu
- Evidence : `ev_3dde3e48aa8d5db8b349dce765fef2704415afc59c5392eaecb900882a0f899f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40130c` — `thunk_FUN_0045575c`
- `0x401401` — `thunk_FUN_0041e427`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x401933` — `thunk_FUN_00464242`
- `0x401b0e` — `thunk_FUN_0040ad94`
- `0x401f28` — `thunk_FUN_00450197`
- `0x4021ad` — `thunk_FUN_004641de`
- `0x402248` — `thunk_FUN_00456b8d`
- `0x4022ed` — `thunk_FUN_0042361d`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00423068(void)

{
  bool bVar1;
  short sVar2;
  int *in_ECX;
  undefined2 extraout_var;
  int iVar3;
  undefined2 extraout_var_00;
  short local_5c [2];
  short local_58 [2];
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  undefined4 local_3c;
  short *local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  undefined1 *local_24;
  int local_20;
  int local_1c;
  undefined4 *local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (in_ECX[0xb] == 0x13) {
    local_8 = thunk_FUN_0042361d();
  }
  else {
    iVar3 = *(short *)((int)in_ECX + 0xe) * 0x29e8;
    local_24 = &DAT_005ec218 + iVar3;
    local_38 = (short *)0x0;
    local_18 = (undefined4 *)0x0;
    local_4c = 0;
    local_48 = 0;
    local_34 = 0;
    local_44 = 0x9ff;
    if (*in_ECX != 4) {
      local_54 = *(int *)(&DAT_005ec620 + *in_ECX * 8 + iVar3);
      local_50 = *(int *)(iVar3 + 0x5ec624 + *in_ECX * 8);
      if (0 < local_54) {
        local_34 = local_54;
      }
      if (local_50 < 0x9ff) {
        local_44 = local_50;
      }
    }
    if (((in_ECX[0xb] == 6) || (in_ECX[0xb] == 0xf)) || (in_ECX[0xb] == 8)) {
      iVar3 = *(short *)((int)in_ECX + 0x32) * 0x4c;
      local_18 = &DAT_006137b8 + *(short *)((int)in_ECX + 0x32) * 0x13;
      local_48 = (int)*(short *)(&DAT_006137c8 + iVar3);
      local_4c = (int)*(short *)(&DAT_006137ca + iVar3);
    }
    else if (((in_ECX[0xb] != 0xe) && (in_ECX[0xb] != 9)) && (in_ECX[0xb] != 0x15)) {
      local_38 = (short *)(&DAT_005ec640 + *(short *)((int)in_ECX + 0x32) * 0x60 + iVar3);
      local_48 = (int)*local_38;
      local_4c = (int)local_38[1];
    }
    if ((in_ECX[0xb] == 0xe) || (in_ECX[0xb] == 9)) {
      local_58[0] = (short)in_ECX[4];
      local_5c[0] = *(short *)((int)in_ECX + 0x12);
      if (in_ECX[0xb] == 9) {
        thunk_FUN_0041e427(CONCAT22((short)((uint)local_5c >> 0x10),
                                    *(undefined2 *)((int)in_ECX + 0x32)),local_58,local_5c);
      }
      if ((int)local_58[0] < local_34 + 100) {
        local_58[0] = (short)local_34 + 100;
      }
      if (local_44 + -100 < (int)local_58[0]) {
        local_58[0] = (short)local_44 + -100;
      }
      iVar3 = (int)local_58[0];
      local_20 = thunk_FUN_00467260(200);
      local_20 = iVar3 + -100 + local_20;
      iVar3 = (int)local_5c[0];
      local_2c = thunk_FUN_00467260(200);
      local_2c = iVar3 + -100 + local_2c;
      if (local_2c < 0x28) {
        local_2c = 0x28;
      }
      if (0x122 < local_2c) {
        local_2c = 0x122;
      }
    }
    else if (in_ECX[0xb] == 8) {
      local_20 = thunk_FUN_00467260(200);
      local_20 = local_20 + -100;
      local_2c = thunk_FUN_00467260(200);
      local_2c = local_2c + -100;
    }
    else if (in_ECX[0xb] == 0x15) {
      local_20 = (int)(short)in_ECX[4];
      local_2c = (int)*(short *)((int)in_ECX + 0x12);
    }
    else {
      local_20 = local_48;
      local_2c = local_4c;
    }
    local_1c = thunk_FUN_00464242(*in_ECX,in_ECX[1]);
    local_40 = thunk_FUN_0045575c(CONCAT22(extraout_var,*(undefined2 *)(local_1c + 4)));
    local_30 = (int)*(short *)(local_40 + 0x4a);
    local_28 = (int)*(short *)(local_40 + 0x4c);
    local_10 = 0x2b;
    local_3c = 0;
    if (local_20 < (short)in_ECX[4]) {
      in_ECX[7] = in_ECX[7] | 2;
      local_30 = -local_30;
      local_10 = -0x2b;
    }
    else if ((short)in_ECX[4] < local_20) {
      in_ECX[7] = in_ECX[7] & 0xfffffffd;
    }
    local_c = 0;
    local_14 = 0;
    if (local_38 == (short *)0x0) {
      if (((in_ECX[0xb] == 6) || (in_ECX[0xb] == 0xf)) && (in_ECX[0xf] != 0x14)) {
        local_20 = local_20 - local_10;
      }
    }
    else {
      if ((*(int *)(local_38 + 8) == 0x2a) || (local_38[0xc] != -1)) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      if (((in_ECX[0xb] != 4) || (*(int *)(local_38 + 2) != 0)) || (bVar1)) {
        if ((in_ECX[0xb] == 4) && (*(int *)(local_38 + 2) == 2)) {
          iVar3 = thunk_FUN_004641de(*(undefined4 *)(local_38 + 10),*(undefined4 *)(local_38 + 8));
          iVar3 = thunk_FUN_00456b8d(CONCAT22(extraout_var_00,*(undefined2 *)(iVar3 + 0x16)));
          if (iVar3 != 0) {
            local_c = (int)*(short *)(iVar3 + 4);
            local_14 = (int)*(short *)(iVar3 + 6);
          }
          local_c = local_c - local_30;
          local_14 = local_14 - local_28;
          sVar2 = thunk_FUN_0040ad94((int)(short)in_ECX[0xc]);
          local_14 = local_14 - sVar2;
        }
        else if ((in_ECX[0xb] != 3) || ((*(int *)(local_38 + 2) != 0 || (bVar1)))) {
          if ((in_ECX[0xb] == 7) || (in_ECX[0xb] == 0x10)) {
            local_c = -local_10;
            local_14 = 0;
          }
          else if (in_ECX[0xb] == 0xd) {
            local_c = -local_30;
            local_14 = -local_28;
            sVar2 = thunk_FUN_0040ad94((int)(short)in_ECX[0xc]);
            local_14 = local_14 - sVar2;
          }
          else if (in_ECX[0xb] == 0x11) {
            local_14 = -0x28;
          }
          else if (bVar1) {
            thunk_FUN_00450197(&local_c,&local_14,6);
          }
        }
        else if (((short)in_ECX[0xc] < 5) || (0x21 < (short)in_ECX[0xc])) {
          thunk_FUN_00450197(&local_c,&local_14,5);
          local_c = local_c - local_30;
          local_14 = local_14 - local_28;
        }
      }
      else if (*(int *)(local_38 + 8) == 0x2b) {
        thunk_FUN_00450197(&local_c,&local_14,4);
        local_c = local_c - local_30;
        local_14 = local_14 - local_28;
      }
      else if ((*(int *)(local_38 + 8) == 0) || (*(int *)(local_38 + 8) == 1)) {
        local_c = -local_30;
        local_14 = -local_28;
        sVar2 = thunk_FUN_0040ad94((int)(short)in_ECX[0xc]);
        local_14 = local_14 - sVar2;
      }
      local_20 = local_20 + local_c;
      local_2c = local_2c + local_14;
    }
    local_8 = 1;
    if ((local_20 < local_34) || (local_44 < local_20)) {
      local_8 = 0;
    }
    if (local_8 != 0) {
      *(undefined2 *)(in_ECX + 10) = (undefined2)local_20;
      *(undefined2 *)((int)in_ECX + 0x2a) = (undefined2)local_2c;
    }
  }
  return local_8;
}
```

---

## FUN_0042361d — 0x42361d

- Classification : internal
- Corps : `0x42361d–0x42383c`
- État : pseudocode obtenu
- Evidence : `ev_41f4dd45d8d838311bb4a2a6ec7147c053d632116535881470c2630ec795f60f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014bf` — `thunk_FUN_00467260`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49d2d0` — "mActionObj >= 0 && mActionObj < SPELL_NumSpells"
- `0x49d300` — "C:\\float\\src\\floater.cpp"

### Pseudocode Ghidra

```c
int FUN_0042361d(void)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int *in_ECX;
  int iVar5;
  int local_24;
  int local_10;
  int local_8;
  
  iVar5 = *(short *)((int)in_ECX + 0xe) * 0x29e8;
  local_24 = (int)(short)in_ECX[4];
  local_10 = (int)*(short *)((int)in_ECX + 0x12);
  if (((short)in_ECX[0xc] < 0) || (0x16 < (short)in_ECX[0xc])) {
    thunk_FUN_00414b64(s_C__float_src_floater_cpp_0049d300,0xc70,
                       s_mActionObj_>__0____mActionObj_<_S_0049d2d0);
  }
  bVar1 = (&DAT_0049d218)[(short)in_ECX[0xc]];
  if ((bVar1 & 2) == 0) {
    if ((bVar1 & 1) != 0) {
      local_24 = (int)*(short *)(&DAT_005ec640 + *(short *)((int)in_ECX + 0x32) * 0x60 + iVar5);
      local_10 = (int)*(short *)((int)(&DAT_005ec640 + *(short *)((int)in_ECX + 0x32) * 0x60 + iVar5
                                      ) + 2);
    }
  }
  else {
    iVar4 = *(short *)((int)in_ECX + 0x32) * 0x4c;
    local_24 = (int)*(short *)(&DAT_006137c8 + iVar4);
    local_10 = (int)*(short *)(&DAT_006137ca + iVar4);
  }
  iVar4 = local_24;
  if ((bVar1 & 4) != 0) {
    iVar3 = in_ECX[4];
    local_24 = thunk_FUN_00467260(200);
    local_24 = (short)iVar3 + -100 + local_24;
    sVar2 = *(short *)((int)in_ECX + 0x12);
    local_10 = thunk_FUN_00467260(200);
    local_10 = sVar2 + -100 + local_10;
    if (local_24 < 0x1e) {
      local_24 = 0x1e;
    }
    if (0x9e2 < local_24) {
      local_24 = 0x9e2;
    }
    if (local_10 < 0x28) {
      local_10 = 0x28;
    }
    if (0x122 < local_10) {
      local_10 = 0x122;
    }
  }
  if (iVar4 < (short)in_ECX[4]) {
    in_ECX[7] = in_ECX[7] | 2;
  }
  else {
    in_ECX[7] = in_ECX[7] & 0xfffffffd;
  }
  local_8 = 1;
  if (*in_ECX != 4) {
    iVar4 = *(int *)(iVar5 + 0x5ec624 + *in_ECX * 8);
    if (((0 < *(int *)(&DAT_005ec620 + *in_ECX * 8 + iVar5)) &&
        (local_24 < *(int *)(&DAT_005ec620 + *in_ECX * 8 + iVar5) + 0x28)) ||
       ((iVar4 < 0x9ff && (iVar4 + -0x28 < local_24)))) {
      local_8 = 0;
    }
  }
  if (local_8 != 0) {
    *(undefined2 *)(in_ECX + 10) = (undefined2)local_24;
    *(undefined2 *)((int)in_ECX + 0x2a) = (undefined2)local_10;
  }
  return local_8;
}
```

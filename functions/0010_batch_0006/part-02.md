# 0010_batch_0006 — détails (2/8)

## FUN_004182c8 — 0x4182c8

- Classification : internal
- Corps : `0x4182c8–0x418920`
- État : pseudocode obtenu
- Evidence : `ev_c9c2c66fe6b9ee3d45fc63a3e65944123025f5331829def323a022c54c0c8364`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401082` — `thunk_FUN_00410bd2`
- `0x4012da` — `thunk_FUN_0040adb5`
- `0x4019ec` — `thunk_FUN_00405265`
- `0x401a37` — `thunk_FUN_00418105`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x40250e` — `thunk_FUN_00414fbf`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x49c4c8` — "killbeas"
- `0x49c4d4` — "farobt"
- `0x49c4dc` — "shape"
- `0x49c4e4` — "C:\\float\\src\\effects.cpp"

### Pseudocode Ghidra

```c
void FUN_004182c8(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  undefined4 local_70;
  uint local_6c [2];
  short *local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  uint local_50;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  uint local_38;
  int local_34;
  uint local_30;
  int local_2c;
  ushort local_28;
  short local_24;
  int local_20;
  int local_1c;
  undefined4 local_18;
  char *local_14;
  int local_10;
  int local_c;
  short *local_8;
  
  local_8 = (short *)(in_ECX + 0x1202);
  local_c = 0;
  local_10 = 0;
  while ((local_10 < 0x20 && (local_c < *(short *)(in_ECX + 0x1482)))) {
    if ((local_8[8] & 0x80U) == 0) {
      if (*local_8 != -1) {
        local_c = local_c + 1;
        local_14 = (char *)(in_ECX + local_8[7] * 0x30);
        if ((local_8[4] == DAT_0049f53c) && (*(int *)(local_14 + 0xc) != 6)) {
          local_18 = thunk_FUN_0040e864(CONCAT22(DAT_0049f53c >> 0xf,
                                                 *(undefined2 *)(local_14 + 0x26)));
          if (*(int *)(local_14 + 0xc) == 2) {
            thunk_FUN_00414fbf(local_8,&local_2c,&local_1c);
            local_2c = local_2c - *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
            local_24 = local_8[5];
            local_28 = local_8[6];
            local_20 = 9;
            while ((-1 < local_20 && (-1 < local_1c))) {
              local_30 = ((int)local_24 & 7U) % 6;
              local_34 = (int)(char)(&DAT_0049bd78)[local_30];
              if ((local_28 & 1) != 0) {
                local_34 = local_34 + 1;
              }
              local_2c = local_2c + (char)(&DAT_0049bd80)[local_30];
              local_1c = local_1c + -0x28;
              if (local_20 <= local_8[3]) {
                thunk_FUN_00405265(param_1,local_18,local_34,local_2c,local_1c,&DAT_004b28f0,0,
                                   *(undefined4 *)(&DAT_0049bd88 + local_30 * 4),0x10000,0);
              }
              if (2 < (int)local_30) {
                local_2c = local_2c + -1;
              }
              local_24 = local_24 >> 3;
              local_28 = (short)local_28 >> 1;
              if (local_20 == 5) {
                local_24 = local_8[5];
              }
              local_20 = local_20 + -1;
            }
          }
          else {
            iVar1 = __strcmpi(local_14,s_killbeas_0049c4c8);
            if (iVar1 == 0) {
              local_3c = (int)*(short *)(&DAT_006137c8 + local_8[1] * 0x4c) -
                         (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
              local_40 = (int)*(short *)(&DAT_006137ca + local_8[1] * 0x4c);
              local_44 = local_3c + -5;
              for (local_48 = 0; local_48 < 3; local_48 = local_48 + 1) {
                if (local_48 == 0) {
                  local_38 = (uint)local_8[5];
                }
                else if (local_48 == 1) {
                  local_38 = (uint)local_8[6];
                }
                else {
                  local_38 = (uint)local_8[3];
                }
                if (((int)local_8[2] & 1 << ((byte)local_48 & 0x1f)) == 0) {
                  local_50 = local_38 % 0xd + 0xd;
                }
                else {
                  local_50 = local_38 % 0xd;
                }
                local_4c = local_40 + -0x140 + local_38 * 5;
                if (0x3f < (int)local_38) {
                  local_50 = local_38 - 0x26;
                  local_4c = local_40;
                }
                if ((-1 < (int)local_50) && ((int)local_50 < 0x24)) {
                  thunk_FUN_00404770(param_1,local_18,local_50,local_44,local_4c);
                }
                local_44 = local_44 + 5;
              }
            }
            else {
              iVar1 = __strcmpi(local_14,s_farobt_0049c4d4);
              if (iVar1 == 0) {
                local_64 = (short *)(&DAT_005ec640 + local_8[1] * 0x60 + local_8[4] * 0x29e8);
                local_58 = (int)*local_64 - (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
                iVar1 = (int)local_64[1];
                local_60 = iVar1 + -0x14;
                local_5c = 0;
                local_54 = 8;
                local_6c[1] = 0xffffffff;
                if (local_8[5] < 0x18) {
                  local_60 = iVar1 + -0x50;
                  local_5c = 0;
                  local_54 = (int)local_8[5] / 3;
                }
                else if (local_8[5] < 0x36) {
                  local_60 = local_60 - (0x3c - (local_8[5] * 2 + -0x30));
                  local_5c = 0;
                }
                else if (local_8[5] < 0x44) {
                  local_5c = (local_8[5] + -0x36) / 2 + 1;
                }
                else if (local_8[5] < 0x62) {
                  local_60 = local_60 - (local_8[5] * 2 + -0x88);
                  local_5c = 7;
                }
                else if (local_8[5] < 0x7a) {
                  local_60 = iVar1 + -0x50;
                  local_5c = 7;
                  local_54 = 8 - (local_8[5] + -0x62) / 3;
                }
                thunk_FUN_00410bd2(param_1,local_18,local_5c,local_58,local_60,local_54);
                if ((local_8[2] != -1) &&
                   (thunk_FUN_0040adb5((int)local_8[2],local_6c,&local_5c),
                   (local_6c[0] & 0xffff) != 0)) {
                  iVar3 = local_60 + 0x14;
                  iVar1 = local_5c;
                  iVar4 = local_58;
                  iVar5 = local_54;
                  uVar2 = thunk_FUN_0040e864(CONCAT22((short)((uint)iVar3 >> 0x10),
                                                      (undefined2)local_6c[0]));
                  thunk_FUN_00410bd2(param_1,uVar2,iVar1,iVar4,iVar3,iVar5);
                }
              }
              else {
                local_70 = 0x10000;
                if ((local_8[8] & 1U) != 0) {
                  local_70 = 0xffff0000;
                }
                local_74 = (int)local_8[5];
                local_78 = (int)local_8[6];
                if ((*(int *)(local_14 + 0xc) == 3) || ((local_8[8] & 0x40U) != 0)) {
                  thunk_FUN_00414fbf(local_8,&local_84,&local_80);
                  local_74 = local_74 + local_84;
                  local_78 = local_78 + local_80;
                }
                local_7c = thunk_FUN_0040e864(*(undefined2 *)(local_14 + 0x26));
                if (local_7c == 0) {
                  uVar2 = thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c4e4,0x661,
                                             s_shape_0049c4dc);
                }
                else {
                  uVar2 = 0;
                }
                thunk_FUN_00405265(param_1,local_7c,(int)local_8[3],
                                   local_74 - *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2),local_78,
                                   &DAT_004b28f0,0,local_70,0x10000,0,uVar2);
              }
            }
          }
        }
      }
    }
    else {
      thunk_FUN_00418105(param_1,local_8);
      local_c = local_c + 1;
    }
    local_10 = local_10 + 1;
    local_8 = local_8 + 10;
  }
  return;
}
```

---

## FUN_00418921 — 0x418921

- Classification : internal
- Corps : `0x418921–0x418a16`
- État : pseudocode obtenu
- Evidence : `ev_e29f50441d273d31daa91525891d92425e0c7618d3fc22db7ea82d38d5d2efae`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012ad` — `thunk_FUN_0045339b`
- `0x40140b` — `thunk_FUN_00416e7d`
- `0x401faf` — `thunk_FUN_004206fc`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00418921(short param_1)

{
  int in_ECX;
  undefined2 extraout_var;
  int local_c;
  short *local_8;
  
  local_8 = (short *)(in_ECX + 0x1202);
  for (local_c = 0; local_c < 0x20; local_c = local_c + 1) {
    if (*local_8 != -1) {
      if ((*local_8 == param_1) && ((local_8[8] & 4U) == 0)) {
        thunk_FUN_00416e7d(CONCAT22(param_1 >> 0xf,(undefined2)local_c));
      }
      else if ((local_8[1] == param_1) && ((local_8[8] & 2U) == 0)) {
        thunk_FUN_00416e7d(CONCAT22(param_1 >> 0xf,(undefined2)local_c));
        if ((local_8[8] & 4U) == 0) {
          thunk_FUN_004206fc(param_1);
        }
        else {
          thunk_FUN_0045339b(CONCAT22(extraout_var,param_1));
        }
      }
    }
    local_8 = local_8 + 10;
  }
  return;
}
```

---

## FUN_00418a17 — 0x418a17

- Classification : internal
- Corps : `0x418a17–0x418a7e`
- État : pseudocode obtenu
- Evidence : `ev_e5407372d8e5a6a6255dafe731c14e91ecd2f77eae4b2bcf2849ec4616b61d8d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401875` — `thunk_FUN_0040fc15`
- `0x401cee` — `thunk_FUN_0040fd80`
- `0x401fff` — `thunk_FUN_0040fdab`
- `0x402455` — `thunk_FUN_004199c0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00418a17(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  int in_ECX;
  
  if (param_2 == 0) {
    thunk_FUN_004199c0((int)*(short *)(in_ECX + 0x1482));
    thunk_FUN_0040fd80(in_ECX + 0x1202,0x280);
  }
  else {
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x1482) = uVar1;
    thunk_FUN_0040fc15(in_ECX + 0x1202,0x280);
  }
  return;
}
```

---

## FUN_00418a7f — 0x418a7f

- Classification : internal
- Corps : `0x418a7f–0x418adc`
- État : pseudocode obtenu
- Evidence : `ev_cc6a764ccc85a842be7cbf28dd92cc7631a0f8010ffc62cfdbadbabaea918ce3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00418a7f(void)

{
  int in_ECX;
  int local_14;
  ushort *local_c;
  int local_8;
  
  local_c = (ushort *)(in_ECX + 0x1202);
  local_8 = 0;
  for (local_14 = 0; local_14 < 0x140; local_14 = local_14 + 1) {
    local_8 = local_8 + (uint)*local_c;
    local_c = local_c + 1;
  }
  return local_8;
}
```

---

## FUN_004199c0 — 0x4199c0

- Classification : internal
- Corps : `0x4199c0–0x4199da`
- État : pseudocode obtenu
- Evidence : `ev_2e0c6a4faa6ad0ba735070912ceee5552423fa6898a121bd36b43e4daed33c3b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cee` — `thunk_FUN_0040fd80`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004199c0(void)

{
  thunk_FUN_0040fd80(&stack0x00000004,4);
  return;
}
```

---

## FUN_004199f0 — 0x4199f0

- Classification : internal
- Corps : `0x4199f0–0x419a43`
- État : pseudocode obtenu
- Evidence : `ev_3cda62e86170f17e44e22cd5874f875ef461050590dc390cc8cf9d47f77ef888`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012df` — `thunk_FUN_00419a60`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_004199f0(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004914e9;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494080;
  thunk_FUN_00419a60();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_00419a44 — 0x419a44

- Classification : internal
- Corps : `0x419a44–0x419a5f`
- État : pseudocode obtenu
- Evidence : `ev_52d1caf7266102844dfcc3fc047937764b37898b35151f77b5d6dc3e79b02c0b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00419a44(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494080;
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_00419a60 — 0x419a60

- Classification : internal
- Corps : `0x419a60–0x419a6a`
- État : pseudocode obtenu
- Evidence : `ev_33803c9325b5f94d0c8ee534852ce5c25773e263333d0bf7b36b8e7c60cc9112`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00419a60(void)

{
  return;
}
```

---

## FUN_00419a6b — 0x419a6b

- Classification : internal
- Corps : `0x419a6b–0x41a7d5`
- État : pseudocode obtenu
- Evidence : `ev_01944b4c13c24ee61a5bcef30360dd50fe0d74a2c68507526092f64aa0c0c3ea`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401217` — `thunk_FUN_0045f849`
- `0x401429` — `thunk_FUN_00428191`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x4019b5` — `thunk_FUN_0046562b`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402153` — `thunk_FUN_0045f0cd`
- `0x402234` — `thunk_FUN_0042892d`
- `0x4022de` — `thunk_FUN_0042d9cd`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49c688` — "POINTS"
- `0x49c690` — "shape"
- `0x49c698` — "C:\\float\\src\\endgame.cpp"
- `0x49c6bc` — "C:\\float\\src\\endgame.cpp"
- `0x49c6d8` — "IVISIT"
- `0x49c6e0` — "%d %s:"
- `0x49c6e8` — "%d %s"
- `0x49c6fc` — "%d %s"
- `0x49c704` — "GLYPHS"
- `0x49c70c` — "%d %s:"
- `0x49c714` — "%d %s"
- `0x49c71c` — "SHADSTR"
- `0x49c724` — "%d %s"
- `0x49c740` — "FLOTTRIB"
- `0x49c74c` — "%d %s %s:"
- `0x49c758` — "%d %s %s:"
- `0x49c764` — "%d %s"
- `0x49c76c` — "FLOTLOSS"
- `0x49c778` — "%d %s %s:"
- `0x49c784` — "%d %s %s:"
- `0x49c790` — "%d %s"
- `0x49c7a0` — "TROFTHE"
- `0x49c7b0` — "%d %s: %s"
- `0x49cfc8` — "xTark"
- `0x49cfc8` — "xTark"
- `0x49cfec` — "xDyla"
- `0x49cfec` — "xDyla"
- `0x49d008` — "xTarks"
- `0x49d008` — "xTarks"
- `0x49d008` — "xTarks"
- `0x49d02c` — "xDyla"
- `0x49d02c` — "xDyla"
- `0x49d02c` — "xDyla"

### Pseudocode Ghidra

```c
void FUN_00419a6b(void)

{
  undefined2 extraout_var;
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int in_ECX;
  undefined *puVar4;
  undefined1 *puVar5;
  undefined4 auStack_120 [10];
  undefined *local_f8;
  undefined4 local_f4;
  int local_f0;
  undefined4 local_ec;
  int local_e8;
  undefined4 local_e4;
  int local_e0;
  int local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  int local_cc;
  undefined4 local_c8;
  int local_c4;
  int local_c0;
  undefined4 local_bc;
  int local_b8;
  undefined4 local_b4;
  int local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  int local_a4;
  undefined1 local_a0 [80];
  undefined4 local_50;
  int local_4c;
  undefined4 local_48;
  int local_44;
  int local_40;
  int local_3c;
  undefined4 auStack_38 [5];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined *local_18;
  undefined4 local_14;
  undefined *local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    local_b8 = DAT_0049f538;
    if (DAT_0049f538 < 0) {
      local_b8 = 0;
    }
    if (3 < local_b8) {
      local_b8 = 3;
    }
    local_50 = thunk_FUN_00429ebe(s_POINTS_0049c688,0);
    thunk_FUN_0045f849(&local_a8,&local_4c,&local_b4,&local_c,&local_8,&local_24,&local_20,&local_b0
                       ,&local_ac,&local_48,&local_bc,&local_1c);
    local_a4 = thunk_FUN_0040e864(CONCAT22(extraout_var,DAT_0049c684));
    if (local_a4 == 0) {
      thunk_FUN_00414b64(s_C__float_src_endgame_cpp_0049c698,0x71,s_shape_0049c690);
    }
    uVar1 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar1;
    if (0xfa < DAT_004c2994) {
      local_c0 = DAT_004bf118 + 5;
      if (7 < local_c0) {
        local_c0 = 7;
      }
      thunk_FUN_00404770(in_ECX + 8,local_a4,local_c0,0x1f,0x14);
    }
    if (300 < DAT_004c2994) {
      local_44 = DAT_004bf11c;
      if (DAT_004bf11c < 0) {
        local_44 = 0;
      }
      if (4 < local_44) {
        local_44 = 4;
      }
      thunk_FUN_00404770(in_ECX + 8,local_a4,local_44,0x1e3,0x13);
    }
    if (0x15e < DAT_004c2994) {
      local_44 = local_b8 + 0x23;
      thunk_FUN_00404770(in_ECX + 8,local_a4,local_44,0x16,0xbb);
      for (local_c4 = 0; local_c4 < 0xe; local_c4 = local_c4 + 1) {
        if (((int)*(short *)(&DAT_00619242 + local_b8 * 0x14a0) & 1 << ((byte)local_c4 & 0x1f)) != 0
           ) {
          thunk_FUN_00404770(in_ECX + 8,local_a4,local_c4 + 0x13,0x16,0xbb);
        }
      }
    }
    if (400 < DAT_004c2994) {
      thunk_FUN_00404770(in_ECX + 8,local_a4,8,0x1b7,0xbc);
    }
    if (500 < DAT_004c2994) {
      local_44 = local_4c + 9;
      if (local_44 < 9) {
        local_44 = 9;
      }
      if (0x12 < local_44) {
        local_44 = 0x12;
      }
      thunk_FUN_00404770(in_ECX + 8,local_a4,local_44,0xef,0x8d);
    }
    if (500 < DAT_004c2994) {
      thunk_FUN_00428191(in_ECX + 8,local_b8,0,0,0x19a,0xaf,8);
    }
    local_3c = thunk_FUN_0042de0d();
    if (local_3c == 0) {
      thunk_FUN_00414b64(s_C__float_src_endgame_cpp_0049c6bc,0xa6,&DAT_0049c6b4);
    }
    uVar2 = thunk_FUN_0042dd0f(6);
    *(uint *)(local_3c + 8) = uVar2 & 0xff;
    if (0xfa < DAT_004c2994) {
      *(undefined4 *)(local_3c + 8) = 0x9b;
      local_c8 = thunk_FUN_00429ebe(s_IVISIT_0049c6d8,0);
      FUN_00472ca0(local_a0,s__d__s__0049c6e0,local_24,local_c8);
      puVar5 = local_a0;
      uVar1 = 0x83;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,(0xcc - iVar3) / 2,uVar1,puVar5);
      *(undefined4 *)(local_3c + 8) = 0xdd;
      FUN_00472ca0(local_a0,s__d__s_0049c6e8,local_b4,local_50);
      puVar5 = local_a0;
      uVar1 = 0x8d;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,(0xcc - iVar3) / 2,uVar1,puVar5);
    }
    *(undefined4 *)(local_3c + 8) = 0xa0;
    local_18 = &DAT_0049c6f0;
    for (local_40 = 0; local_40 < 5; local_40 = local_40 + 1) {
      local_18[6] = (char)local_40 + '1';
      uVar1 = thunk_FUN_00429ebe(local_18,0);
      auStack_38[local_40] = uVar1;
    }
    if (300 < DAT_004c2994) {
      local_cc = DAT_004bf11c;
      FUN_00472ca0(local_a0,&DAT_0049c6f8,auStack_38[DAT_004bf11c]);
      puVar5 = local_a0;
      uVar1 = 0x83;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,(0x42f - iVar3) / 2,uVar1,puVar5);
      *(undefined4 *)(local_3c + 8) = 0xdd;
      FUN_00472ca0(local_a0,s__d__s_0049c6fc,local_c,local_50);
      puVar5 = local_a0;
      uVar1 = 0x8d;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,(0x42f - iVar3) / 2,uVar1,puVar5);
    }
    if (0x15e < DAT_004c2994) {
      *(undefined4 *)(local_3c + 8) = 0x9c;
      local_d4 = thunk_FUN_0045f0cd();
      local_d0 = thunk_FUN_00429ebe(s_GLYPHS_0049c704,0);
      FUN_00472ca0(local_a0,s__d__s__0049c70c,local_d4,local_d0);
      puVar5 = local_a0;
      uVar1 = 0x10a;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,(0xcc - iVar3) / 2,uVar1,puVar5);
      *(undefined4 *)(local_3c + 8) = 0xdd;
      FUN_00472ca0(local_a0,s__d__s_0049c714,local_8,local_50);
      puVar5 = local_a0;
      uVar1 = 0x114;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,(0xcc - iVar3) / 2,uVar1,puVar5);
    }
    if (400 < DAT_004c2994) {
      *(undefined4 *)(local_3c + 8) = 0xa0;
      local_e0 = 0;
      for (local_dc = 1; local_dc < 9; local_dc = local_dc + 1) {
        local_e0 = local_e0 + *(short *)(DAT_0049f538 * 0x14a0 + 0x61a636 + local_dc * 2);
      }
      local_d8 = thunk_FUN_00429ebe(s_SHADSTR_0049c71c,0);
      FUN_00472ca0(local_a0,s__d__s_0049c724,local_e0,local_d8);
      thunk_FUN_004289c0(in_ECX + 8,0x1c6,0xa7,local_a0);
      *(undefined4 *)(local_3c + 8) = 0xdd;
      FUN_00472ca0(local_a0,&DAT_0049c72c,local_50);
      thunk_FUN_004289c0(in_ECX + 8,0x1c6,0xb1,local_a0);
      FUN_00472ca0(local_a0,&DAT_0049c730,local_ac);
      thunk_FUN_004289c0(in_ECX + 8,0x1ca,0xec,local_a0);
      FUN_00472ca0(local_a0,&DAT_0049c734,local_48);
      thunk_FUN_004289c0(in_ECX + 8,0x1fa,0xec,local_a0);
      FUN_00472ca0(local_a0,&DAT_0049c738,local_bc);
      thunk_FUN_004289c0(in_ECX + 8,0x227,0xec,local_a0);
      FUN_00472ca0(local_a0,&DAT_0049c73c,local_1c);
      thunk_FUN_004289c0(in_ECX + 8,0x251,0xec,local_a0);
    }
    thunk_FUN_0042dd0f(6);
    if (local_b8 == 1) {
      local_14 = 0xda;
    }
    else if (local_b8 == 2) {
      local_14 = 100;
    }
    else if (local_b8 == 3) {
      local_14 = 0xa7;
    }
    else {
      local_14 = 0xcf;
    }
    if (0x1a9 < DAT_004c2994) {
      local_e4 = thunk_FUN_00429ebe(s_FLOTTRIB_0049c740,0);
      local_e8 = thunk_FUN_0046562b((DAT_0049f538 * 0x14a0) / 0x14a0,0xffffffff);
      *(undefined4 *)(local_3c + 8) = local_14;
      if (local_e8 == 1) {
        FUN_00472ca0(local_a0,s__d__s__s__0049c74c,1,s_xTark_0049cfc8 + local_b8 * 0xc,local_e4);
      }
      else {
        FUN_00472ca0(local_a0,s__d__s__s__0049c758,local_e8,s_xTarks_0049d008 + local_b8 * 0xc,
                     local_e4);
      }
      thunk_FUN_004289c0(in_ECX + 8,0x1c6,0x102,local_a0);
      *(undefined4 *)(local_3c + 8) = 0xdd;
      FUN_00472ca0(local_a0,s__d__s_0049c764,local_20,local_50);
      thunk_FUN_004289c0(in_ECX + 8,0x1ca,0x10c,local_a0);
    }
    if (0x1c2 < DAT_004c2994) {
      local_ec = thunk_FUN_00429ebe(s_FLOTLOSS_0049c76c,0);
      *(undefined4 *)(local_3c + 8) = local_14;
      if (*(short *)(&DAT_0061a650 + DAT_0049f538 * 0x14a0) == 1) {
        FUN_00472ca0(local_a0,s__d__s__s__0049c778,
                     (int)*(short *)(&DAT_0061a650 + DAT_0049f538 * 0x14a0),
                     s_xTark_0049cfc8 + local_b8 * 0xc,local_ec);
      }
      else {
        FUN_00472ca0(local_a0,s__d__s__s__0049c784,
                     (int)*(short *)(&DAT_0061a650 + DAT_0049f538 * 0x14a0),
                     s_xTarks_0049d008 + local_b8 * 0xc,local_ec);
      }
      thunk_FUN_004289c0(in_ECX + 8,0x1c6,0x11b,local_a0);
      *(undefined4 *)(local_3c + 8) = 0xdd;
      FUN_00472ca0(local_a0,s__d__s_0049c790,-local_b0,local_50);
      thunk_FUN_004289c0(in_ECX + 8,0x1ca,0x125,local_a0);
    }
    if (500 < DAT_004c2994) {
      *(undefined4 *)(local_3c + 8) = local_14;
      if (DAT_004befe0 != 0) {
        puVar4 = &DAT_004beff0 + DAT_004befec * 0x40;
        uVar1 = 0x9e;
        local_10 = puVar4;
        iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
        thunk_FUN_004289c0(in_ECX + 8,0x140 - iVar3 / 2,uVar1,puVar4);
      }
      local_f8 = &DAT_0049c798;
      for (local_f0 = 0; local_f0 < 10; local_f0 = local_f0 + 1) {
        local_f8[4] = (char)local_f0 + '0';
        uVar1 = thunk_FUN_00429ebe(local_f8,0);
        auStack_120[local_f0] = uVar1;
      }
      local_f4 = thunk_FUN_00429ebe(s_TROFTHE_0049c7a0,0);
      FUN_00472ca0(local_a0,&DAT_0049c7a8,local_f4,s_xTarks_0049d008 + local_b8 * 0xc);
      puVar5 = local_a0;
      uVar1 = 0xac;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,0x140 - iVar3 / 2,uVar1,puVar5);
      *(undefined4 *)(local_3c + 8) = 0xdd;
      FUN_00472ca0(local_a0,s__d__s___s_0049c7b0,local_a8,local_50,auStack_120[local_4c]);
      puVar5 = local_a0;
      uVar1 = 0x120;
      iVar3 = thunk_FUN_0042892d(local_a0,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,0x140 - iVar3 / 2,uVar1,puVar5);
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d9cd(1);
    DAT_004c2994 = DAT_004c2994 + 1;
    if (6000 < DAT_004c2994) {
      DAT_004c2994 = 0x1f5;
    }
  }
  return;
}
```

---

## FUN_0041a7d6 — 0x41a7d6

- Classification : internal
- Corps : `0x41a7d6–0x41a863`
- État : pseudocode obtenu
- Evidence : `ev_c1848c21aa9e848e44ecd1467a8f6bb368d8c6951753adb08457c68d0c662b17`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x401acd` — `thunk_FUN_0040ebde`

### Chaînes référencées

- `0x49c7bc` — "endgame"

### Pseudocode Ghidra

```c
undefined4 FUN_0041a7d6(short param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  if (param_1 == 1) {
    DAT_0049c684 = thunk_FUN_0040ebde(s_endgame_0049c7bc);
    DAT_004c2994 = 0;
    uVar1 = thunk_FUN_004293c6(1,param_2,param_3);
  }
  else if ((param_1 < 6) || (7 < param_1)) {
    uVar1 = thunk_FUN_004293c6((int)param_1,param_2,param_3);
  }
  else {
    thunk_FUN_0046c1b4(1,0,0);
    uVar1 = 1;
  }
  return uVar1;
}
```

---

## FUN_0041a864 — 0x41a864

- Classification : internal
- Corps : `0x41a864–0x41a8b7`
- État : pseudocode obtenu
- Evidence : `ev_4a1d353919d567e3ec89acc023878f6dae1b9176a2aba8d1d844080d64779da1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401582` — `thunk_FUN_0041a8d4`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0041a864(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004914fc;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494098;
  thunk_FUN_0041a8d4();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_0041a8b8 — 0x41a8b8

- Classification : internal
- Corps : `0x41a8b8–0x41a8d3`
- État : pseudocode obtenu
- Evidence : `ev_ba97d6dde0288991ab62121398c0adff8c433571dcc582ba1479d9e735f9920b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041a8b8(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494098;
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_0041a8d4 — 0x41a8d4

- Classification : internal
- Corps : `0x41a8d4–0x41a8de`
- État : pseudocode obtenu
- Evidence : `ev_b545879e0edf81b7eadd018e5b0829116ac71e07f6e6e89557094d4fa6783ede`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041a8d4(void)

{
  return;
}
```

---

## FUN_0041a8df — 0x41a8df

- Classification : internal
- Corps : `0x41a8df–0x41afba`
- État : pseudocode obtenu
- Evidence : `ev_ea10958170235dede7e42dfdd9e76d05696e96e3e798b34bbda94abd45a23d83`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401131` — `thunk_FUN_00412cac`
- `0x401217` — `thunk_FUN_0045f849`
- `0x401429` — `thunk_FUN_00428191`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x4019b5` — `thunk_FUN_0046562b`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402153` — `thunk_FUN_0045f0cd`
- `0x4022de` — `thunk_FUN_0042d9cd`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49c7c4` — "shape"
- `0x49c7cc` — "C:\\float\\src\\endgame.cpp"
- `0x49c7e8` — "POINTS"
- `0x49c7f8` — "C:\\float\\src\\endgame.cpp"
- `0x49c814` — "%s: %s"
- `0x49c824` — "%d %s: %s"
- `0x49c830` — "GLYPHS"
- `0x49c838` — "%d %s"
- `0x49c840` — "SHADSTR"
- `0x49c848` — "%d %s"
- `0x49c850` — "FLOTTRIB"
- `0x49c86c` — "FLOTLOSS"
- `0x49cfc8` — "xTark"
- `0x49cfc8` — "xTark"
- `0x49cfec` — "xDyla"
- `0x49cfec` — "xDyla"
- `0x49d008` — "xTarks"
- `0x49d008` — "xTarks"
- `0x49d008` — "xTarks"
- `0x49d02c` — "xDyla"
- `0x49d02c` — "xDyla"
- `0x49d02c` — "xDyla"

### Pseudocode Ghidra

```c
void FUN_0041a8df(void)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int in_ECX;
  undefined2 extraout_var;
  undefined1 local_e8 [4];
  int local_e4;
  undefined1 local_e0 [4];
  undefined1 local_dc [4];
  undefined1 local_d8 [4];
  int local_d4;
  int local_d0;
  undefined4 local_cc;
  undefined4 auStack_c8 [10];
  undefined1 local_a0 [72];
  undefined4 local_58;
  int local_54;
  undefined1 local_50 [4];
  int local_4c;
  int local_48;
  int local_44;
  undefined4 local_40;
  undefined *local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined1 local_2c [4];
  undefined1 local_28 [4];
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 local_1c;
  undefined *local_18;
  undefined1 local_14 [4];
  int local_10;
  undefined *local_c;
  undefined1 local_8 [4];
  
  iVar1 = thunk_FUN_00412cac((int)*(short *)(in_ECX + 0x70));
  if ((((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) && (DAT_004befe0 != 0)) &&
     (iVar1 != -1)) {
    uVar2 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar2;
    local_d0 = thunk_FUN_0040e864(CONCAT22(extraout_var,DAT_0049c684));
    if (local_d0 == 0) {
      thunk_FUN_00414b64(s_C__float_src_endgame_cpp_0049c7cc,0x1ae,s_shape_0049c7c4);
    }
    local_58 = thunk_FUN_00429ebe(s_POINTS_0049c7e8,0);
    local_e4 = (int)*(short *)(in_ECX + 0x70);
    if (local_e4 < 0) {
      local_e4 = 0;
    }
    if (3 < local_e4) {
      local_e4 = 3;
    }
    local_c = &DAT_006191b8 + local_e4 * 0x14a0;
    local_44 = thunk_FUN_0042de0d();
    if (local_44 == 0) {
      thunk_FUN_00414b64(s_C__float_src_endgame_cpp_0049c7f8,0x1bc,&DAT_0049c7f0);
    }
    uVar3 = thunk_FUN_0042dd0f(6);
    *(uint *)(local_44 + 8) = uVar3 & 0xff;
    thunk_FUN_0045f849(&local_cc,&local_54,local_e0,local_14,local_8,local_2c,local_28,local_dc,
                       local_d8,local_50,local_e8,local_24);
    local_4c = local_54 + 9;
    if (local_4c < 9) {
      local_4c = 9;
    }
    if (0x12 < local_4c) {
      local_4c = 0x12;
    }
    thunk_FUN_00404770(in_ECX + 8,local_d0,local_4c,0xfffffff0,0xffffffed);
    if (local_e4 == 1) {
      *(undefined4 *)(local_44 + 8) = 0xda;
    }
    else if (local_e4 == 2) {
      *(undefined4 *)(local_44 + 8) = 100;
    }
    else if (local_e4 == 3) {
      *(undefined4 *)(local_44 + 8) = 0xa7;
    }
    else {
      *(undefined4 *)(local_44 + 8) = 0xcf;
    }
    local_18 = &DAT_004beff0 + iVar1 * 0x40;
    FUN_00472ca0(local_a0,s__s___s_0049c814,local_18,s_xTarks_0049d008 + local_e4 * 0xc);
    thunk_FUN_004289c0(in_ECX + 8,10,2,local_a0);
    thunk_FUN_00428191(in_ECX + 8,local_e4,0,0,0xa2,0x18,8);
    *(undefined4 *)(local_44 + 8) = 0xdd;
    local_3c = &DAT_0049c81c;
    for (local_10 = 0; local_10 < 10; local_10 = local_10 + 1) {
      local_3c[4] = (char)local_10 + '0';
      uVar2 = thunk_FUN_00429ebe(local_3c,0);
      auStack_c8[local_10] = uVar2;
    }
    FUN_00472ca0(local_a0,s__d__s___s_0049c824,local_cc,local_58,auStack_c8[local_54]);
    thunk_FUN_004289c0(in_ECX + 8,10,0xc,local_a0);
    *(undefined4 *)(local_44 + 8) = 0x9c;
    local_30 = thunk_FUN_0045f0cd();
    local_20 = thunk_FUN_00429ebe(s_GLYPHS_0049c830,0);
    FUN_00472ca0(local_a0,s__d__s_0049c838,local_30,local_20);
    thunk_FUN_004289c0(in_ECX + 8,10,0x7a,local_a0);
    *(undefined4 *)(local_44 + 8) = 0xa0;
    local_d4 = 0;
    for (local_48 = 0; local_48 < 4; local_48 = local_48 + 1) {
      local_d4 = local_d4 + *(short *)(local_c + local_48 * 2 + 0x147e);
    }
    local_40 = thunk_FUN_00429ebe(s_SHADSTR_0049c840,0);
    FUN_00472ca0(local_a0,s__d__s_0049c848,local_d4,local_40);
    thunk_FUN_004289c0(in_ECX + 8,0x46,0x7a,local_a0);
    if (local_e4 == 1) {
      *(undefined4 *)(local_44 + 8) = 0xda;
    }
    else if (local_e4 == 2) {
      *(undefined4 *)(local_44 + 8) = 100;
    }
    else if (local_e4 == 3) {
      *(undefined4 *)(local_44 + 8) = 0xa7;
    }
    else {
      *(undefined4 *)(local_44 + 8) = 0xcf;
    }
    local_34 = thunk_FUN_00429ebe(s_FLOTTRIB_0049c850,0);
    local_38 = thunk_FUN_0046562b((int)(local_c + -0x6191b8) / 0x14a0,0xffffffff);
    FUN_00472ca0(local_a0,&DAT_0049c85c,local_38);
    thunk_FUN_004289c0(in_ECX + 8,0x8c,0x34,local_a0);
    if (local_38 == 1) {
      FUN_00472ca0(local_a0,&DAT_0049c860,s_xTark_0049cfc8 + local_e4 * 0xc);
    }
    else {
      FUN_00472ca0(local_a0,&DAT_0049c864,s_xTarks_0049d008 + local_e4 * 0xc);
    }
    thunk_FUN_004289c0(in_ECX + 8,0x8c,0x3e,local_a0);
    FUN_00472ca0(local_a0,&DAT_0049c868,local_34);
    thunk_FUN_004289c0(in_ECX + 8,0x8c,0x48,local_a0);
    local_1c = thunk_FUN_00429ebe(s_FLOTLOSS_0049c86c,0);
    FUN_00472ca0(local_a0,&DAT_0049c878,(int)*(short *)(local_c + 0x1498));
    thunk_FUN_004289c0(in_ECX + 8,0x8c,0x55,local_a0);
    if (*(short *)(&DAT_0061a650 + DAT_0049f538 * 0x14a0) == 1) {
      FUN_00472ca0(local_a0,&DAT_0049c87c,s_xTark_0049cfc8 + local_e4 * 0xc);
    }
    else {
      FUN_00472ca0(local_a0,&DAT_0049c880,s_xTarks_0049d008 + local_e4 * 0xc);
    }
    thunk_FUN_004289c0(in_ECX + 8,0x8c,0x5f,local_a0);
    FUN_00472ca0(local_a0,&DAT_0049c884,local_1c);
    thunk_FUN_004289c0(in_ECX + 8,0x8c,0x69,local_a0);
    thunk_FUN_0042d38a();
    thunk_FUN_0042d9cd(1);
  }
  return;
}
```

---


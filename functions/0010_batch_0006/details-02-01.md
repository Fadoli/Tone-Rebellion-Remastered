# 0010_batch_0006 — détails (1/3)

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

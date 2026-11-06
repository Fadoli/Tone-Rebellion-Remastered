# 0014_batch_0010 — détails (2/3)

## FUN_00447f60 — 0x447f60

- Classification : internal
- Corps : `0x447f60–0x448010`
- État : pseudocode obtenu
- Evidence : `ev_983049828b0a34334f30ad5940fd19771f93a07190036e4729af2597d5a2eb10`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00447f60(uint param_1,uint param_2)

{
  ushort uVar1;
  uint uVar2;
  int *piVar3;
  int *local_14;
  
  uVar1 = *(ushort *)(DAT_005e1718 + (param_1 & 0xffff) * 2);
  if (uVar1 == 0xffff) {
    uVar2 = 0;
  }
  else {
    piVar3 = (int *)(uint)uVar1;
    local_14 = (int *)(DAT_005e1714 + (int)piVar3 * 4);
    while (local_14 < (int *)(DAT_005e1714 + (uint)DAT_005e16f4 * 4)) {
      if (*local_14 == (param_2 & 0xff) * 0x10000 + (param_1 & 0xffff)) {
        return ((int)local_14 - DAT_005e1714 >> 2 & 0xffffU) + 0x102;
      }
      piVar3 = local_14 + 1;
      local_14 = piVar3;
    }
    uVar2 = (uint)piVar3 & 0xffff0000;
  }
  return uVar2;
}
```

---

---

## FUN_00448011 — 0x448011

- Classification : internal
- Corps : `0x448011–0x44818e`
- État : pseudocode obtenu
- Evidence : `ev_7b4bc36fabd8821fecd0954d61918956c54964639b80191bded1c4c3630ec5c2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00448011(uint param_1)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  byte local_10;
  
  cVar1 = DAT_005e16fc;
  local_10 = (byte)((param_1 & 0xffff) << (DAT_005e1704 & 0x1f));
  *DAT_005e1710 = *DAT_005e1710 | local_10;
  DAT_005e1710 = DAT_005e1710 + 1;
  if ((short)((short)DAT_005e1710 - (short)DAT_005e16f8) == 0x100) {
    *DAT_005e16f8 = 0xff;
    DAT_005e16f8 = DAT_005e1710;
    DAT_005e1710 = DAT_005e1710 + 1;
  }
  iVar4 = (int)(param_1 & 0xffff) >> (8 - DAT_005e1704 & 0x1f);
  bVar3 = cVar1 - ('\b' - DAT_005e1704);
  DAT_005e1704 = 0;
  local_10 = (byte)iVar4;
  *DAT_005e1710 = local_10;
  bVar2 = bVar3;
  if (7 < bVar3) {
    DAT_005e1710 = DAT_005e1710 + 1;
    if ((short)((short)DAT_005e1710 - (short)DAT_005e16f8) == 0x100) {
      *DAT_005e16f8 = 0xff;
      DAT_005e16f8 = DAT_005e1710;
      DAT_005e1710 = DAT_005e1710 + 1;
    }
    bVar2 = DAT_005e1704;
    if (8 < bVar3) {
      DAT_005e1704 = bVar3 - 8;
      local_10 = (byte)((uint)iVar4 >> 8);
      *DAT_005e1710 = local_10;
      bVar2 = DAT_005e1704;
    }
  }
  DAT_005e1704 = bVar2;
  return;
}
```

---

---

## FUN_0044818f — 0x44818f

- Classification : internal
- Corps : `0x44818f–0x4482a5`
- État : pseudocode obtenu
- Evidence : `ev_821d1753a21510a39e07b15501c15eccd44ab639ceb2d7b45b7ce77070a16053`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012e4` — `thunk_FUN_00448011`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044818f(ushort param_1,byte param_2)

{
  ushort *puVar1;
  
  puVar1 = (ushort *)(DAT_005e1714 + (uint)DAT_005e16f4 * 4);
  *puVar1 = param_1;
  puVar1[1] = (ushort)param_2;
  if (*(short *)((int)DAT_005e1718 + (uint)param_1 * 2) == -1) {
    *(ushort *)((int)DAT_005e1718 + (uint)param_1 * 2) = DAT_005e16f4;
  }
  thunk_FUN_00448011(param_1);
  DAT_005e16f4 = DAT_005e16f4 + 1;
  if ((uint)DAT_005e1700 < DAT_005e16f4 + 0x102) {
    if (DAT_005e16f4 + 0x102 < 0x1001) {
      DAT_005e16fc = DAT_005e16fc + '\x01';
      DAT_005e1700 = DAT_005e1700 << 1;
    }
    else {
      thunk_FUN_00448011(0x100);
      DAT_005e16fc = '\t';
      DAT_005e1700 = 0x200;
      DAT_005e16f4 = 0;
      _memset(DAT_005e1718,0xff,0x2008);
    }
  }
  return;
}
```

---

---

## FUN_004482a6 — 0x4482a6

- Classification : internal
- Corps : `0x4482a6–0x448435`
- État : pseudocode obtenu
- Evidence : `ev_d408629253396291083efe704c6a7800506d007f68bbe8eb972969b3682ad606`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012e4` — `thunk_FUN_00448011`
- `0x401339` — `thunk_FUN_00447f60`
- `0x40223e` — `thunk_FUN_0044818f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004482a6(byte *param_1)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  short sVar4;
  ushort local_1c;
  int local_10;
  char local_c;
  
  DAT_005e16fc = 9;
  DAT_005e1700 = 0x200;
  DAT_005e1704 = '\0';
  *DAT_005e1710 = 8;
  DAT_005e16f8 = DAT_005e1710 + 1;
  DAT_005e1710 = DAT_005e1710 + 2;
  thunk_FUN_00448011(0x100);
  local_1c = (ushort)*param_1;
  iVar3 = _DAT_005e1708 * _DAT_005e16f0;
  for (local_10 = 1; local_10 < iVar3; local_10 = local_10 + 1) {
    bVar1 = param_1[local_10];
    uVar2 = thunk_FUN_00447f60(CONCAT22((short)((uint)(param_1 + local_10) >> 0x10),local_1c),
                               CONCAT31((int3)((uint)local_10 >> 8),bVar1));
    if (uVar2 == 0) {
      thunk_FUN_0044818f(local_1c,bVar1);
      uVar2 = (ushort)bVar1;
    }
    local_1c = uVar2;
  }
  thunk_FUN_00448011(local_1c);
  thunk_FUN_00448011(0x101);
  sVar4 = (short)DAT_005e1710 - (short)DAT_005e16f8;
  local_c = (char)sVar4;
  if (DAT_005e1704 == '\0') {
    if (sVar4 == 1) {
      *DAT_005e16f8 = '\0';
    }
    else {
      *DAT_005e16f8 = local_c + -1;
      *DAT_005e1710 = 0;
      DAT_005e1710 = DAT_005e1710 + 1;
    }
  }
  else {
    *DAT_005e16f8 = local_c;
    DAT_005e1710 = DAT_005e1710 + 1;
    *DAT_005e1710 = 0;
    DAT_005e1710 = DAT_005e1710 + 1;
  }
  return;
}
```

---

---

## FUN_00448436 — 0x448436

- Classification : internal
- Corps : `0x448436–0x4487a8`
- État : pseudocode obtenu
- Evidence : `ev_c58e1048724aca91ae06bfcabfa61a1ac27a24f95e8e01d26c55fe0852b389cf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401749` — `thunk_FUN_00414c97`
- `0x4017da` — `thunk_FUN_004482a6`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402176` — `thunk_FUN_00414bf7`
- `0x472ca0` — `FUN_00472ca0`
- `0x4734a0` — `FUN_004734a0`
- `0x473aa0` — `FID_conflict:__open`
- `0x473fe0` — `FUN_00473fe0`
- `0x4745f0` — `FUN_004745f0`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a140c` — "GIFOutput && GIFHash && GIFSpeedtbl"
- `0x4a1430` — "C:\\float\\src\\makegif.cpp"
- `0x4a144c` — "GIF87a"
- `0x4a1454` — "scr%03d.gif"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00448436(char *param_1,undefined4 param_2,int param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  undefined1 local_30;
  char local_28 [20];
  int local_14;
  int local_10;
  int local_c;
  char *local_8;
  
  _DAT_005e1708 = param_4;
  _DAT_005e16f0 = param_5;
  DAT_005e170c = (void *)thunk_FUN_00414bf7(param_4 * param_5);
  DAT_005e1714 = thunk_FUN_00414bf7(0x4000);
  DAT_005e1718 = (void *)thunk_FUN_00414bf7(0x2008);
  if (((DAT_005e170c == (void *)0x0) || (DAT_005e1714 == 0)) || (DAT_005e1718 == (void *)0x0)) {
    uVar1 = thunk_FUN_00414b64(s_C__float_src_makegif_cpp_004a1430,0x102,
                               s_GIFOutput____GIFHash____GIFSpeed_004a140c);
  }
  else {
    uVar1 = 0;
  }
  _memset(DAT_005e170c,0,param_4 * param_5);
  _memset(DAT_005e1718,0xff,0x2008);
  DAT_005e1710 = DAT_005e170c;
  DAT_005e16f4 = 0;
  FUN_004734a0(DAT_005e170c,s_GIF87a_004a144c,6,uVar1);
  DAT_005e1710 = (undefined2 *)((int)DAT_005e1710 + 6);
  *DAT_005e1710 = DAT_005e1708;
  DAT_005e1710 = DAT_005e1710 + 1;
  *DAT_005e1710 = DAT_005e16f0;
  DAT_005e1710 = DAT_005e1710 + 1;
  *(undefined1 *)DAT_005e1710 = 0x87;
  DAT_005e1710 = (undefined2 *)((int)DAT_005e1710 + 1);
  *(undefined1 *)DAT_005e1710 = 0xff;
  DAT_005e1710 = (undefined2 *)((int)DAT_005e1710 + 1);
  *(undefined1 *)DAT_005e1710 = 0;
  for (local_10 = 0; DAT_005e1710 = (undefined2 *)((int)DAT_005e1710 + 1), local_10 < 0x300;
      local_10 = local_10 + 1) {
    local_30 = (undefined1)(((uint)*(byte *)(param_3 + local_10) * 0xff) / 0x3f);
    *(undefined1 *)DAT_005e1710 = local_30;
  }
  *(undefined1 *)DAT_005e1710 = 0x2c;
  DAT_005e1710 = (undefined2 *)((int)DAT_005e1710 + 1);
  *DAT_005e1710 = 0;
  DAT_005e1710 = DAT_005e1710 + 1;
  *DAT_005e1710 = 0;
  DAT_005e1710 = DAT_005e1710 + 1;
  *DAT_005e1710 = DAT_005e1708;
  DAT_005e1710 = DAT_005e1710 + 1;
  *DAT_005e1710 = DAT_005e16f0;
  DAT_005e1710 = DAT_005e1710 + 1;
  *(undefined1 *)DAT_005e1710 = 7;
  DAT_005e1710 = (undefined2 *)((int)DAT_005e1710 + 1);
  thunk_FUN_004482a6(param_2);
  *(undefined1 *)DAT_005e1710 = 0x3b;
  DAT_005e1710 = (undefined2 *)((int)DAT_005e1710 + 1);
  local_c = (int)DAT_005e1710 - (int)DAT_005e170c;
  FUN_00472ca0(local_28,s_scr_03d_gif_004a1454,DAT_005e171c);
  local_8 = local_28;
  if (param_1 != (char *)0x0) {
    local_8 = param_1;
  }
  local_14 = FID_conflict___open(local_8,0x8302,0x180);
  FUN_004745f0(local_14,DAT_005e170c,local_c);
  FUN_00473fe0(local_14);
  DAT_005e171c = DAT_005e171c + 1;
  thunk_FUN_00414c97(DAT_005e170c);
  thunk_FUN_00414c97(DAT_005e1714);
  thunk_FUN_00414c97(DAT_005e1718);
  DAT_005e1710 = (undefined2 *)0x0;
  DAT_005e1718 = (void *)0x0;
  DAT_005e1714 = 0;
  DAT_005e170c = (void *)0x0;
  return;
}
```

---

---

## FUN_004489c0 — 0x4489c0

- Classification : internal
- Corps : `0x4489c0–0x448d21`
- État : pseudocode obtenu
- Evidence : `ev_9ca3320b7a81f1abe1b3e4185864503451aa25f54b75870cd8ea858d408d294e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401154` — `thunk_FUN_00414b91`
- `0x4012cb` — `thunk_FUN_0045b8d1`
- `0x4012ee` — `thunk_FUN_0046c458`
- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x4017f3` — `thunk_FUN_0040fb84`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x401b13` — `thunk_FUN_00457490`
- `0x401d02` — `thunk_FUN_0046cce7`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x402013` — `thunk_FUN_0045aafd`
- `0x402185` — `thunk_FUN_00449b60`
- `0x4021e9` — `thunk_FUN_004576c7`
- `0x40227f` — `thunk_FUN_0046c25d`

### Chaînes référencées

- `0x4a1474` — "data\\titscrn.pal"
- `0x4a1474` — "data\\titscrn.pal"
- `0x4a1474` — "data\\titscrn.pal"
- `0x4a1488` — "status==0"
- `0x4a1494` — "C:\\float\\src\\master.cpp"
- `0x4a14ac` — "ambi1"
- `0x4a14b4` — "ambi1"
- `0x4a14bc` — "resume.gam"
- `0x4a14c8` — "RESUME"
- `0x4a14d0` — "LOADGAME"
- `0x4a14dc` — "NEWGAME"
- `0x4a14e4` — "resume.gam"

### Pseudocode Ghidra

```c
void FUN_004489c0(short param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *unaff_FS_OFFSET;
  bool bVar3;
  undefined1 local_5c4 [124];
  int local_548;
  uint local_544;
  int local_328;
  undefined1 local_324 [768];
  int local_24;
  int local_20;
  char *local_1c;
  uint local_18;
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004919d8;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (param_1 < 0x7d2) {
    if (param_1 == 0x7d1) {
      if (DAT_004befe0 == 0) {
        thunk_FUN_004576c7(s_resume_gam_004a14e4);
        thunk_FUN_0046c1b4(3,0,0);
      }
      else {
        thunk_FUN_0046c1b4(1,2,0);
      }
    }
    else if (param_1 == 1) {
      thunk_FUN_0040f6f7();
      local_8 = 0;
      local_1c = s_data_titscrn_pal_004a1474;
      local_328 = thunk_FUN_0040f752(s_data_titscrn_pal_004a1474,0x8000);
      if (local_328 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = thunk_FUN_00414b91(s_C__float_src_master_cpp_004a1494,0x3f,s_status__0_004a1488,
                                   local_1c);
      }
      thunk_FUN_0040fb84(local_324);
      thunk_FUN_0046cce7(local_324);
      thunk_FUN_0040f966(uVar2);
      bVar3 = DAT_004a1470 != 0;
      if (bVar3) {
        DAT_004a1470 = 0;
      }
      local_18 = (uint)bVar3;
      iVar1 = thunk_FUN_0045b8d1(s_ambi1_004a14ac);
      if (iVar1 == 0) {
        thunk_FUN_0045aafd(s_ambi1_004a14b4,0,1,local_18);
      }
      DAT_005e1740 = 1;
      thunk_FUN_0046c25d(1,0,0,0);
      local_14 = 0;
      local_24 = 1;
      local_20 = 1;
      if (DAT_004befe0 == 0) {
        thunk_FUN_0040f6f7();
        local_8 = CONCAT31(local_8._1_3_,1);
        local_328 = thunk_FUN_0040f752(s_resume_gam_004a14bc,0x8000);
        if (local_328 == 0) {
          thunk_FUN_00449b60();
          thunk_FUN_0040fc15(local_5c4,0x80);
          iVar1 = thunk_FUN_00457490();
          local_544 = (uint)(local_548 == iVar1);
          if (local_544 != 0) {
            local_14 = 1;
          }
        }
        local_8 = local_8 & 0xffffff00;
        thunk_FUN_0040f73f();
      }
      else {
        local_24 = 0;
        local_14 = 0;
        if ((DAT_004befe0 != 0) && (DAT_004befec != DAT_004befe8)) {
          local_20 = 0;
        }
      }
      if (local_14 == 0) {
        thunk_FUN_0046c3bc(s_RESUME_004a14c8,2,0,0);
      }
      if (local_24 == 0) {
        thunk_FUN_0046c3bc(s_LOADGAME_004a14d0,2,0,0);
      }
      if (local_20 == 0) {
        thunk_FUN_0046c3bc(s_NEWGAME_004a14dc,2,0,0);
      }
      if (DAT_004befe0 == 0) {
        DAT_004bf120 = 0;
      }
      local_8 = 0xffffffff;
      thunk_FUN_0040f73f();
    }
    else if (param_1 == 3) {
      thunk_FUN_0046c25d(0xb,0,0,0);
    }
    else if (((param_1 == 4) && (param_4 != (undefined4 *)0x0)) &&
            (iVar1 = thunk_FUN_0046c458((undefined2)DAT_0062c6bc), iVar1 != 0)) {
      uVar2 = thunk_FUN_00429ebe(iVar1,0);
      *param_4 = uVar2;
    }
  }
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

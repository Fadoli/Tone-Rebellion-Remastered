# 0010_batch_0006 — détails (1/2)

## FUN_0041afbb — 0x41afbb

- Classification : internal
- Corps : `0x41afbb–0x41b05b`
- État : pseudocode obtenu
- Evidence : `ev_7c29df0ea0f8fcb6619089d5aa800d8d1c9c1daae37a929744e1066c6f3a2da6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`
- `0x4019e2` — `thunk_FUN_0046c1b4`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0041afbb(short param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int in_ECX;
  
  if (param_1 == 1) {
    *(short *)(in_ECX + 0x70) = *(char *)(in_ECX + 0x28) + -0x30;
    if (DAT_0049f538 <= *(short *)(in_ECX + 0x70)) {
      *(short *)(in_ECX + 0x70) = *(short *)(in_ECX + 0x70) + 1;
    }
    uVar1 = thunk_FUN_004293c6(1,param_2,param_3);
  }
  else if ((param_1 < 6) || (7 < param_1)) {
    uVar1 = thunk_FUN_004293c6(param_1,param_2,param_3);
  }
  else {
    thunk_FUN_0046c1b4(1,0,0);
    uVar1 = 1;
  }
  return uVar1;
}
```

---

---

## FUN_0041b05c — 0x41b05c

- Classification : internal
- Corps : `0x41b05c–0x41b0af`
- État : pseudocode obtenu
- Evidence : `ev_ba2d12f1077a50d008f3cbcffc574609aee89baa123d0f8395bec18d2c9366c9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`
- `0x402379` — `thunk_FUN_0041b0cc`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0041b05c(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049150f;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004940b0;
  thunk_FUN_0041b0cc();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0041b0b0 — 0x41b0b0

- Classification : internal
- Corps : `0x41b0b0–0x41b0cb`
- État : pseudocode obtenu
- Evidence : `ev_1a74048b51b446e58533c5c6c9e463f709749201b02e5bbf3b4d854329ae33c4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041b0b0(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004940b0;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_0041b0cc — 0x41b0cc

- Classification : internal
- Corps : `0x41b0cc–0x41b0d6`
- État : pseudocode obtenu
- Evidence : `ev_3920d22ec2b460b81b9399ee34f279e5c909b8ba4cc439483c0a0e8d0fa08c27`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041b0cc(void)

{
  return;
}
```

---

---

## FUN_0041b0d7 — 0x41b0d7

- Classification : internal
- Corps : `0x41b0d7–0x41b574`
- État : pseudocode obtenu
- Evidence : `ev_164303c0e173d69c8b5bde468bb555f073f3e5272695991d85545a212ead17ab`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401429` — `thunk_FUN_00428191`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x402234` — `thunk_FUN_0042892d`
- `0x4022de` — `thunk_FUN_0042d9cd`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x40236a` — `thunk_FUN_0042a6c9`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472ca0` — `FUN_00472ca0`
- `0x4737e0` — `_strncpy`
- `0x476e20` — `_strncmp`

### Chaînes référencées

- `0x49c888` — "endgame.txt"
- `0x49c894` — "FALSE"
- `0x49c89c` — "C:\\float\\src\\endgame.cpp"
- `0x49c8b8` — "ENDSTORY"
- `0x49c8cc` — "%s, %s"
- `0x4a4a50` — "xSpores"
- `0x4a4a50` — "xSpores"

### Pseudocode Ghidra

```c
void FUN_0041b0d7(void)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int in_ECX;
  int iVar6;
  int iVar7;
  undefined2 extraout_var;
  undefined1 *puVar8;
  int local_e84;
  int local_e80;
  int local_e74;
  int local_e70;
  undefined1 local_e60 [3072];
  char local_260 [512];
  int local_60;
  int local_5c;
  undefined4 local_58;
  undefined1 local_54 [80];
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    local_60 = thunk_FUN_0042de0d();
    uVar1 = thunk_FUN_0042dd0f(6);
    *(uint *)(local_60 + 8) = uVar1 & 0xff;
    local_5c = DAT_0049f538;
    if (DAT_0049f538 < 0) {
      local_5c = 0;
    }
    if (3 < local_5c) {
      local_5c = 3;
    }
    uVar2 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar2;
    local_58 = thunk_FUN_0040e864(CONCAT22(extraout_var,DAT_0049c684));
    thunk_FUN_00404770(in_ECX + 8,local_58,0,-*(int *)(in_ECX + 0xc),-*(int *)(in_ECX + 0x10));
    thunk_FUN_0042a6c9(in_ECX + 8);
    if (DAT_004c2998 == 0) {
      iVar3 = thunk_FUN_0040f419(s_endgame_txt_0049c888,local_e60,0xbff);
      if (iVar3 != 0) {
        thunk_FUN_00414b64(s_C__float_src_endgame_cpp_0049c89c,0x2ae,s_FALSE_0049c894);
      }
      DAT_004c2990 = 0;
      while( true ) {
        thunk_FUN_0040f5b3(local_260,1);
        iVar3 = _strncmp(local_260,s_ENDSTORY_0049c8b8,9);
        if (iVar3 == 0) break;
        _strncpy(&DAT_004c2470 + DAT_004c2990 * 0x29,local_260,0x28);
        (&DAT_004c2498)[DAT_004c2990 * 0x29] = 0;
        if ((&DAT_004c2470)[DAT_004c2990 * 0x29] == '*') {
          (&DAT_004c2470)[DAT_004c2990 * 0x29] = 0;
        }
        DAT_004c2990 = DAT_004c2990 + 1;
      }
      DAT_004c2998 = 1;
    }
    if ((5 < DAT_004c2994) && (DAT_004c2994 < 500)) {
      local_e70 = 0x96 - (DAT_004c2994 + -5);
      for (local_e74 = 0; local_e74 < DAT_004c2990; local_e74 = local_e74 + 1) {
        iVar3 = *(int *)(in_ECX + 0x14);
        iVar7 = *(int *)(in_ECX + 0xc);
        iVar4 = thunk_FUN_0042892d(&DAT_004c2470 + local_e74 * 0x29,0xffffffff,0xffffffff);
        thunk_FUN_004289c0(in_ECX + 8,((iVar3 - iVar7) - iVar4) / 2,local_e70,
                           &DAT_004c2470 + local_e74 * 0x29);
        local_e70 = local_e70 + 0x10;
      }
    }
    if (500 < DAT_004c2994) {
      iVar4 = DAT_004c2994 + -600;
      iVar6 = -iVar4 + 0x96;
      uVar2 = thunk_FUN_00429ebe(&DAT_0049c8c4,0);
      iVar3 = *(int *)(in_ECX + 0x14);
      iVar7 = *(int *)(in_ECX + 0xc);
      iVar5 = thunk_FUN_0042892d(uVar2,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,((iVar3 - iVar7) - iVar5) / 2,iVar6,uVar2);
      local_e80 = -iVar4 + 0xe6;
      for (local_e84 = 0; local_e84 < 8; local_e84 = local_e84 + 1) {
        thunk_FUN_00428191(in_ECX + 8,4,local_e84 + 10,0,0x3c,local_e80,8);
        FUN_00472ca0(local_54,s__s___s_0049c8cc,s_xSpores_004a4a50 + (local_e84 * 2 + 2) * 0x10,
                     s_xSpores_004a4a50 + (local_e84 * 2 + 3) * 0x10);
        puVar8 = local_54;
        iVar7 = local_e80 + 0x1e;
        iVar3 = thunk_FUN_0042892d(local_54,0xffffffff,0xffffffff);
        thunk_FUN_004289c0(in_ECX + 8,0x3c - iVar3 / 2,iVar7,puVar8);
        FUN_00472ca0(local_54,&DAT_0049c8d4,
                     (int)*(short *)(local_5c * 0x14a0 + 0x61a638 + local_e84 * 2));
        thunk_FUN_004289c0(in_ECX + 8,0x96,local_e80,local_54);
        local_e80 = local_e80 + 0x50;
      }
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d9cd(1);
  }
  return;
}
```

---

---

## FUN_0041b575 — 0x41b575

- Classification : internal
- Corps : `0x41b575–0x41b5d3`
- État : pseudocode obtenu
- Evidence : `ev_0e575a8b7b0bba0e2ebe3b3d6ea92c104695961c687ab5c2dac5833f4743d9b4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401406` — `thunk_FUN_0042a649`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x4019e2` — `thunk_FUN_0046c1b4`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0041b575(short param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int in_ECX;
  
  if ((param_1 < 6) || (7 < param_1)) {
    uVar1 = thunk_FUN_004293c6(param_1,param_2,param_3);
  }
  else {
    thunk_FUN_0046c1b4(1,0,0);
    thunk_FUN_0042a649(in_ECX + 8);
    uVar1 = 1;
  }
  return uVar1;
}
```

---

---

## FUN_0041bcd0 — 0x41bcd0

- Classification : internal
- Corps : `0x41bcd0–0x41bcfd`
- État : pseudocode obtenu
- Evidence : `ev_d7aba90c513d1d11b8186255429315ac934675109c5bdbfacf5507c2f9eb6886`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a00` — `thunk_FUN_00419a44`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0041bcd0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00419a44();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_0041bd10 — 0x41bd10

- Classification : internal
- Corps : `0x41bd10–0x41bd3d`
- État : pseudocode obtenu
- Evidence : `ev_4a533b6e6ce2a325bc2644d2eee67f65510b69378766394fc70e515576daf134`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401073` — `thunk_FUN_0041a8b8`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0041bd10(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0041a8b8();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_0041bd50 — 0x41bd50

- Classification : internal
- Corps : `0x41bd50–0x41bd7d`
- État : pseudocode obtenu
- Evidence : `ev_b64f07e2b329e4982e5a12a747b49849b0efb78fe78cef5df41687b1f775b17e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40238d` — `thunk_FUN_0041b0b0`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0041bd50(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0041b0b0();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_0041bd90 — 0x41bd90

- Classification : internal
- Corps : `0x41bd90–0x41bd99`
- État : pseudocode obtenu
- Evidence : `ev_97a5fb2dcb0733c1278de50b31104bfa4ff00f621d811a83a15e51b72c98d275`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x41bd9a` — `FUN_0041bd9a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041bd90(void)

{
  FUN_0041bd9a();
  return;
}
```

---

---

## FUN_0041bd9a — 0x41bd9a

- Classification : internal
- Corps : `0x41bd9a–0x41bdad`
- État : pseudocode obtenu
- Evidence : `ev_1c1d34ee73b13255e1c8460127e25550e2f4bae618662168625b6d50ececf091`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402491` — `thunk_FUN_0042dd0f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041bd9a(void)

{
  DAT_004c2b08 = thunk_FUN_0042dd0f(0);
  return;
}
```

---

---

## FUN_0041bdae — 0x41bdae

- Classification : internal
- Corps : `0x41bdae–0x41be0e`
- État : pseudocode obtenu
- Evidence : `ev_4c453f8245e9d1316205dd4285ed187d01ba61dc33a4d464394dc61400095283`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x4f` — `USER32.DLL::DefWindowProcA`
- `0x402216` — `thunk_FUN_0041cf86`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041bdae(HWND param_1,UINT param_2,WPARAM param_3,LPARAM param_4)

{
  if (param_2 == 2) {
    thunk_FUN_0041cf86(param_3);
  }
  else if ((param_2 == 0x1c) && (DAT_004c2b6c = (uint)(param_3 == 0), param_3 != 0)) {
    DAT_004c2b70 = 1;
  }
  DefWindowProcA(param_1,param_2,param_3,param_4);
  return;
}
```

---

---

## FUN_0041be0f — 0x41be0f

- Classification : internal
- Corps : `0x41be0f–0x41be71`
- État : pseudocode obtenu
- Evidence : `ev_29ad09d456ae628d3158564a8c1dab7a234851e959fde7b086429c419b386514`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x51` — `USER32.DLL::DispatchMessageA`
- `EXTERNAL:0x52` — `USER32.DLL::TranslateMessage`
- `EXTERNAL:0x53` — `USER32.DLL::PeekMessageA`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0041be0f(undefined4 *param_1)

{
  BOOL BVar1;
  int iVar2;
  tagMSG *ptVar3;
  tagMSG local_24;
  undefined4 local_8;
  
  local_24.message = 0;
  local_8 = 0;
  BVar1 = PeekMessageA(&local_24,(HWND)0x0,0,0,1);
  if (BVar1 != 0) {
    local_8 = 1;
    TranslateMessage(&local_24);
    DispatchMessageA(&local_24);
  }
  if (param_1 != (undefined4 *)0x0) {
    ptVar3 = &local_24;
    for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
      *param_1 = ptVar3->hwnd;
      ptVar3 = (tagMSG *)&ptVar3->message;
      param_1 = param_1 + 1;
    }
  }
  return local_8;
}
```

---

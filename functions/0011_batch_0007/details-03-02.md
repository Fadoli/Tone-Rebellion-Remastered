# 0011_batch_0007 — détails (2/3)

## FUN_00429d5c — 0x429d5c

- Classification : internal
- Corps : `0x429d5c–0x429e68`
- État : pseudocode obtenu
- Evidence : `ev_fe2d04de71105903ee26e44b7d85f686a4b05bf73a5a407f1e66a1fe0450cfef`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`

### Chaînes référencées

- `0x49de48` — "buffer != NULL"
- `0x49de58` — "C:\\float\\src\\gamewin.cpp"
- `0x49de74` — "sSharedTextLen + len < MAX_SHARED_TEXT"
- `0x49de9c` — "C:\\float\\src\\gamewin.cpp"
- `0x49deb8` — "FALSE"
- `0x49dec0` — "C:\\float\\src\\gamewin.cpp"

### Pseudocode Ghidra

```c
int FUN_00429d5c(char *param_1,int param_2)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  if (param_1 == (char *)0x0) {
    uVar4 = thunk_FUN_00414b64(s_C__float_src_gamewin_cpp_0049de58,0x1f8,s_buffer____NULL_0049de48);
  }
  else {
    uVar4 = 0;
  }
  sVar2 = _strlen(param_1);
  if ((int)(DAT_00597180 + sVar2) < 0x9800) {
    uVar3 = 0;
  }
  else {
    uVar3 = thunk_FUN_00414b64(s_C__float_src_gamewin_cpp_0049de9c,0x1fb,
                               s_sSharedTextLen___len_<_MAX_SHARE_0049de74);
  }
  FUN_00472da0(&DAT_0058d0b8 + DAT_00597180,param_1,uVar3,uVar4);
  iVar1 = DAT_00597180;
  DAT_00597180 = DAT_00597180 + 1 + sVar2;
  if (param_2 != 0) {
    if (DAT_00597184 < 0x200) {
      FUN_00472da0(&DAT_0058af48 + DAT_00597184 * 0x10,param_2,uVar3,uVar4);
      *(int *)(&DAT_005968b8 + DAT_00597184 * 4) = iVar1;
      DAT_00597184 = DAT_00597184 + 1;
    }
    else {
      thunk_FUN_00414b64(s_C__float_src_gamewin_cpp_0049dec0,0x20b,s_FALSE_0049deb8);
    }
  }
  return iVar1;
}
```

---

---

## FUN_00429e69 — 0x429e69

- Classification : internal
- Corps : `0x429e69–0x429ebd`
- État : pseudocode obtenu
- Evidence : `ev_8146606c6e3594474d1b0f6440df010441518d781cf58cfff88dab31f59f98d8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49dedc` — "index < sSharedTextLen"
- `0x49def4` — "C:\\float\\src\\gamewin.cpp"

### Pseudocode Ghidra

```c
undefined * FUN_00429e69(int param_1,int param_2)

{
  if (DAT_00597180 <= param_1) {
    thunk_FUN_00414b64(s_C__float_src_gamewin_cpp_0049def4,0x214,s_index_<_sSharedTextLen_0049dedc);
  }
  if (param_2 != 0) {
    param_1 = *(int *)(&DAT_005968b8 + param_1 * 4);
  }
  return &DAT_0058d0b8 + param_1;
}
```

---

---

## FUN_00429ebe — 0x429ebe

- Classification : internal
- Corps : `0x429ebe–0x429f39`
- État : pseudocode obtenu
- Evidence : `ev_8ff87772c7fe4f09c5d401d4704e629c1d1561f140695ffc53d21ec6a34fa1ef`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4774f0` — `_strcmp`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_00429ebe(char *param_1,int *param_2)

{
  int iVar1;
  int local_c;
  undefined *local_8;
  
  local_8 = (undefined *)0x0;
  local_c = 0;
  while ((local_c < DAT_00597184 &&
         (iVar1 = _strcmp(&DAT_0058af48 + local_c * 0x10,param_1), iVar1 != 0))) {
    local_c = local_c + 1;
  }
  if ((local_c < DAT_00597184) &&
     (local_8 = &DAT_0058d0b8 + *(int *)(&DAT_005968b8 + local_c * 4), param_2 != (int *)0x0)) {
    *param_2 = local_c;
  }
  return local_8;
}
```

---

---

## FUN_00429f3a — 0x429f3a

- Classification : internal
- Corps : `0x429f3a–0x429f57`
- État : pseudocode obtenu
- Evidence : `ev_109d1714fe261313365105194259bd329e5f517be169638fad23bf26a82067d8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_00429f3a(void)

{
  int in_ECX;
  
  return DAT_0062c6bc == *(int *)(in_ECX + 4);
}
```

---

---

## FUN_00429f58 — 0x429f58

- Classification : internal
- Corps : `0x429f58–0x429f64`
- État : pseudocode obtenu
- Evidence : `ev_b56f975fdc4def993467ceeaadf85c3fc89392cf4d621b55e84bd597bf27fa10`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429f58(void)

{
  return;
}
```

---

---

## FUN_00429f65 — 0x429f65

- Classification : internal
- Corps : `0x429f65–0x429fb8`
- État : pseudocode obtenu
- Evidence : `ev_a41c20a03d02c7e9dd51d60c5b5f4a792c8e9e20aa6ce4ffd579da42051e6590`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`
- `0x401d98` — `thunk_FUN_00429fd5`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00429f65(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491629;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494180;
  thunk_FUN_00429fd5();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_00429fb9 — 0x429fb9

- Classification : internal
- Corps : `0x429fb9–0x429fd4`
- État : pseudocode obtenu
- Evidence : `ev_a383139cb3aef2b0b9daab97e6ed8b8c60fb77d55fdf154f1eae094bdb4026d4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429fb9(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494180;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_00429fd5 — 0x429fd5

- Classification : internal
- Corps : `0x429fd5–0x429fdf`
- État : pseudocode obtenu
- Evidence : `ev_a134a8e95b7713218f450212a00b7f91c59bb27522e2b612dfcb24d2b5c15074`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429fd5(void)

{
  return;
}
```

---

---

## FUN_00429fe0 — 0x429fe0

- Classification : internal
- Corps : `0x429fe0–0x42a00a`
- État : pseudocode obtenu
- Evidence : `ev_d06d8820a3e570b1124a0d71f15b9ddb3bc0f8e6f62b7bc631f4fabb826e283a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00429fe0(short param_1,undefined4 param_2,undefined4 param_3)

{
  thunk_FUN_004293c6((int)param_1,param_2,param_3);
  return;
}
```

---

---

## FUN_0042a00b — 0x42a00b

- Classification : internal
- Corps : `0x42a00b–0x42a13a`
- État : pseudocode obtenu
- Evidence : `ev_d0001b947b137bf2112acf98a96c935796a52ba30e2a92940c6909af2484e647`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40146f` — `thunk_FUN_0042d87c`
- `0x40163b` — `thunk_FUN_00404c3b`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x402086` — `thunk_FUN_00404c5a`
- `0x402306` — `thunk_FUN_004106dd`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a00b(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int *in_ECX;
  int iVar3;
  int iVar4;
  
  if ((in_ECX[0xd] != 0) && (in_ECX[0xf] != 0)) {
    if (((in_ECX[1] == DAT_0062c6bc) || (in_ECX[0xd] == 2)) &&
       ((in_ECX[0x11] != 0 && (in_ECX[0xd] != 3)))) {
      (**(code **)(*in_ECX + 0xc))(param_1);
    }
    else if (*(short *)((int)in_ECX + 0x1e) != -1) {
      iVar1 = thunk_FUN_0042d28f();
      in_ECX[2] = iVar1;
      if (in_ECX[0xe] == 0) {
        uVar2 = thunk_FUN_004106dd(0,3);
        thunk_FUN_00404c3b(uVar2);
        iVar3 = (int)*(short *)((int)in_ECX + 0x6e);
        iVar1 = (int)(short)in_ECX[0x1b];
        iVar4 = (int)*(short *)((int)in_ECX + 0x1e);
        uVar2 = thunk_FUN_0040e864((short)in_ECX[7]);
        thunk_FUN_00404c5a(in_ECX + 2,uVar2,iVar4,iVar1,iVar3);
      }
      else {
        iVar3 = (int)*(short *)((int)in_ECX + 0x6e);
        iVar1 = (int)(short)in_ECX[0x1b];
        iVar4 = (int)*(short *)((int)in_ECX + 0x1e);
        uVar2 = thunk_FUN_0040e864((short)in_ECX[7]);
        thunk_FUN_00404770(in_ECX + 2,uVar2,iVar4,iVar1,iVar3);
      }
      thunk_FUN_0042d38a();
    }
    thunk_FUN_0042d87c(in_ECX + 2,3);
    in_ECX[0xd] = 0;
  }
  return;
}
```

---

---

## FUN_0042a13b — 0x42a13b

- Classification : internal
- Corps : `0x42a13b–0x42a1a0`
- État : pseudocode obtenu
- Evidence : `ev_ed62c20b500b2abbb8d262491e938b41baf89a207df8564c91cb21733513f68a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a13b(void)

{
  undefined4 uVar1;
  int iVar2;
  int in_ECX;
  int iVar3;
  int iVar4;
  
  if (*(short *)(in_ECX + 0x1e) != -1) {
    uVar1 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar1;
    iVar3 = (int)*(short *)(in_ECX + 0x6e);
    iVar2 = (int)*(short *)(in_ECX + 0x6c);
    iVar4 = *(short *)(in_ECX + 0x1e) + 1;
    uVar1 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
    thunk_FUN_00404770(in_ECX + 8,uVar1,iVar4,iVar2,iVar3);
    thunk_FUN_0042d38a();
  }
  return;
}
```

---

---

## FUN_0042a1a1 — 0x42a1a1

- Classification : internal
- Corps : `0x42a1a1–0x42a1f4`
- État : pseudocode obtenu
- Evidence : `ev_7d1ef468937acc07adb9a95965bb07699be717cc96b792380f6e572e957b1925`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40126c` — `thunk_FUN_0042a211`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0042a1a1(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049163c;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494198;
  thunk_FUN_0042a211();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0042a1f5 — 0x42a1f5

- Classification : internal
- Corps : `0x42a1f5–0x42a210`
- État : pseudocode obtenu
- Evidence : `ev_c35c1b962906ad1fc18ce9ff11f25430db2317d9f7a73b61ad0486a04801745b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a1f5(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494198;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_0042a211 — 0x42a211

- Classification : internal
- Corps : `0x42a211–0x42a22f`
- État : pseudocode obtenu
- Evidence : `ev_8e3814d4892ec761f27ac65ae2d6b2c5b92541003b733cbee2d89e7f5720b60e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a211(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x70) = 0;
  *(undefined4 *)(in_ECX + 0x74) = 0;
  return;
}
```

---

---

## FUN_0042a230 — 0x42a230

- Classification : internal
- Corps : `0x42a230–0x42a25a`
- État : pseudocode obtenu
- Evidence : `ev_d1a3a753121e33c2d45d6be3d8089a2db4cc4adf1954e66669ea637261d8e442`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a230(short param_1,undefined4 param_2,undefined4 param_3)

{
  thunk_FUN_004293c6((int)param_1,param_2,param_3);
  return;
}
```

---

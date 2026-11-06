# 0018_batch_0014 — détails (3/3)

## FUN_0047117d — 0x47117d

- Classification : internal
- Corps : `0x47117d–0x4711e1`
- État : pseudocode obtenu
- Evidence : `ev_6c02118291fa96e14fcc71511e9afb01b1e44cc85b53bdda2e204c08fdd086a5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047117d(short param_1)

{
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (3 < local_8) {
      return 0;
    }
    if (((*(uint *)(&DAT_004bf0f0 + DAT_004befec * 4) & 1 << ((byte)local_8 & 0x1f)) != 0) &&
       (*(int *)(&DAT_005eebc4 + local_8 * 4 + param_1 * 0x29e8) != 0)) break;
    local_8 = local_8 + 1;
  }
  return 1;
}
```

---

---

## FUN_004711e2 — 0x4711e2

- Classification : internal
- Corps : `0x4711e2–0x4714ad`
- État : pseudocode obtenu
- Evidence : `ev_e419f0590f1605f2f6c422dab09e4d4e72cfadd4a4dff7155135229a20dc1503`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011bd` — `thunk_FUN_0047117d`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x402234` — `thunk_FUN_0042892d`
- `0x4022de` — `thunk_FUN_0042d9cd`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402487` — `thunk_FUN_00471e66`

### Chaînes référencées

- `0x4a4870` — "xTarzus"
- `0x4a603c` — "paradise"
- `0x4a6048` — "shape"
- `0x4a6050` — "C:\\float\\src\\worldwin.cpp"
- `0x4a606c` — "paraglow"
- `0x4a6078` — "shape"
- `0x4a6080` — "C:\\float\\src\\worldwin.cpp"
- `0x4a60a4` — "C:\\float\\src\\worldwin.cpp"

### Pseudocode Ghidra

```c
void FUN_004711e2(void)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int in_ECX;
  int iVar4;
  int local_10;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    uVar2 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar2;
    if ((DAT_006191b4 < 4) ||
       (((DAT_006191b4 == 4 && (DAT_006191b6 < 0x3c)) ||
        (*(int *)(DAT_0049f538 * 0x14a0 + 0x619248) != 0)))) {
      thunk_FUN_00471e66(in_ECX);
    }
    if ((3 < DAT_006191b4) && (*(int *)(DAT_0049f538 * 0x14a0 + 0x619248) == 0)) {
      if ((DAT_006191b4 != 4) || (0x3b < DAT_006191b6)) {
        iVar3 = thunk_FUN_0040ec89(s_paradise_004a603c,1);
        if (iVar3 == 0) {
          thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a6050,0x268,s_shape_004a6048);
        }
        iVar4 = DAT_006324b8 % 0x15;
        DAT_006324b8 = DAT_006324b8 + 1;
        thunk_FUN_00404770(in_ECX + 8,iVar3,iVar4,(int)*(short *)(in_ECX + 0x784),
                           (int)*(short *)(in_ECX + 0x786));
      }
      if ((DAT_006191b6 < 0x50) && (DAT_006191b4 == 4)) {
        iVar3 = thunk_FUN_0040ec89(s_paraglow_004a606c,1);
        if (iVar3 == 0) {
          thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a6080,0x271,s_shape_004a6078);
        }
        local_10 = (int)DAT_006191b6;
        if (0x3d < local_10) {
          local_10 = 0x3d - (local_10 + -0x3d);
        }
        thunk_FUN_00404770(in_ECX + 8,iVar3,local_10,(int)*(short *)(in_ECX + 0x784),
                           (int)*(short *)(in_ECX + 0x786));
      }
    }
    if (((DAT_006191b4 == 0) && (-1 < *(short *)(in_ECX + 0x76))) &&
       (iVar3 = thunk_FUN_0047117d(*(undefined2 *)(in_ECX + 0x76)), iVar3 != 0)) {
      sVar1 = (&DAT_005eebf8)[*(short *)(in_ECX + 0x76) * 0x14f4];
      iVar3 = thunk_FUN_0042de03();
      if (iVar3 == 0) {
        thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a60a4,0x27d,&DAT_004a609c);
      }
      iVar3 = thunk_FUN_0042892d(s_xTarzus_004a4870 + sVar1 * 0x20,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,(0x280 - iVar3) / 2,0x3c,s_xTarzus_004a4870 + sVar1 * 0x20);
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d9cd(1);
    *(undefined4 *)(in_ECX + 0x34) = 0;
  }
  return;
}
```

---

---

## FUN_004714ae — 0x4714ae

- Classification : internal
- Corps : `0x4714ae–0x471535`
- État : pseudocode obtenu
- Evidence : `ev_54898e67522ee30189cd60335bad1cfe5fa3c55832ecc0ba40ee67e3ed7a0220`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004714ae(float param_1)

{
  int in_ECX;
  
  *(float *)(in_ECX + 0x78c) = param_1 * 0.017453277 + *(float *)(in_ECX + 0x78c);
  while (6.28318 <= *(float *)(in_ECX + 0x78c)) {
    *(float *)(in_ECX + 0x78c) = *(float *)(in_ECX + 0x78c) - 6.28318;
  }
  while (*(float *)(in_ECX + 0x78c) < 0.0) {
    *(float *)(in_ECX + 0x78c) = *(float *)(in_ECX + 0x78c) + 6.28318;
  }
  return;
}
```

---

---

## FUN_00471536 — 0x471536

- Classification : internal
- Corps : `0x471536–0x4718ea`
- État : pseudocode obtenu
- Evidence : `ev_232525675e1ef9f156606270bf3eebfa14a802cbecd1e151e6726403ee04b09a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401154` — `thunk_FUN_00414b91`
- `0x401979` — `thunk_FUN_00471b34`
- `0x401ae1` — `thunk_FUN_004718eb`
- `0x4023ab` — `thunk_FUN_00471b5c`
- `0x4023c4` — `thunk_FUN_00471aee`
- `0x472c6c` — `__ftol`
- `0x477314` — `FUN_00477314`
- `0x477ab4` — `FUN_00477ab4`

### Chaînes référencées

- `0x4a60c0` — "Bad DisplayItem Type"
- `0x4a60dc` — "C:\\float\\src\\worldwin.cpp"

### Pseudocode Ghidra

```c
void FUN_00471536(void)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  short sVar5;
  float fVar6;
  short sVar7;
  short sVar8;
  int in_ECX;
  float10 fVar9;
  float10 fVar10;
  short *local_18;
  int local_14;
  
  thunk_FUN_004718eb();
  local_18 = (short *)(in_ECX + 0x78);
  thunk_FUN_00471b5c();
  fVar6 = ((float)(DAT_00618e44 % 0x5a0) * 0.017453277) / 4.0 + *(float *)(in_ECX + 0x78c);
  for (local_14 = 0; local_14 < *(short *)(in_ECX + 0x678); local_14 = local_14 + 1) {
    if (*(int *)(local_18 + 2) == 0) {
      sVar5 = *local_18;
      fVar3 = *(float *)(&DAT_005eebec + sVar5 * 0x29e8);
      FUN_00477ab4((double)(fVar3 - fVar6));
      fVar9 = (float10)FUN_00477314((double)(fVar3 - fVar6));
      iVar1 = *(int *)(&DAT_005eebf0 + sVar5 * 0x29e8);
      fVar3 = *(float *)(in_ECX + 0x794);
      sVar5 = *(short *)(in_ECX + 0x784);
      sVar8 = __ftol();
      local_18[4] = sVar5 + sVar8;
      sVar5 = *(short *)(in_ECX + 0x786);
      sVar8 = __ftol();
      local_18[5] = sVar5 - sVar8;
      *(float *)(local_18 + 8) = (float)(fVar9 * (float10)iVar1 * (float10)fVar3) + 3000.0;
      local_18[10] = 1;
      local_18[0xb] = 0;
      thunk_FUN_00471aee();
    }
    else if (*(int *)(local_18 + 2) == 1) {
      sVar5 = *local_18;
      sVar8 = *(short *)(&DAT_006136b8 + sVar5 * 8);
      fVar3 = *(float *)(&DAT_005eebec + sVar8 * 0x29e8);
      FUN_00477ab4((double)(fVar3 - fVar6));
      fVar9 = (float10)FUN_00477314((double)(fVar3 - fVar6));
      iVar1 = *(int *)(&DAT_005eebf0 + sVar8 * 0x29e8);
      fVar3 = *(float *)(in_ECX + 0x794);
      sVar8 = *(short *)(in_ECX + 0x784);
      sVar7 = __ftol();
      local_18[4] = sVar8 + sVar7;
      sVar8 = *(short *)(in_ECX + 0x786);
      sVar7 = __ftol();
      local_18[5] = sVar8 - sVar7;
      sVar5 = *(short *)(&DAT_006136ba + sVar5 * 8);
      fVar4 = *(float *)(&DAT_005eebec + sVar5 * 0x29e8);
      FUN_00477ab4((double)(fVar4 - fVar6));
      fVar10 = (float10)FUN_00477314((double)(fVar4 - fVar6));
      iVar2 = *(int *)(&DAT_005eebf0 + sVar5 * 0x29e8);
      fVar4 = *(float *)(in_ECX + 0x794);
      sVar5 = *(short *)(in_ECX + 0x784);
      sVar8 = __ftol();
      local_18[6] = sVar5 + sVar8;
      sVar5 = *(short *)(in_ECX + 0x786);
      sVar8 = __ftol();
      local_18[7] = sVar5 - sVar8;
      *(float *)(local_18 + 8) =
           ((float)(fVar9 * (float10)iVar1 * (float10)fVar3) +
           (float)(fVar10 * (float10)iVar2 * (float10)fVar4)) / 2.0 + 3000.0;
      local_18[10] = 1;
      local_18[0xb] = 0;
      thunk_FUN_00471aee();
    }
    else {
      thunk_FUN_00414b91(s_C__float_src_worldwin_cpp_004a60dc,0x2eb,&DAT_004a60d8,
                         s_Bad_DisplayItem_Type_004a60c0);
    }
    local_18 = local_18 + 0xc;
  }
  thunk_FUN_00471b34();
  return;
}
```

---

---

## FUN_004718eb — 0x4718eb

- Classification : internal
- Corps : `0x4718eb–0x471a69`
- État : pseudocode obtenu
- Evidence : `ev_4a227d1765025385f80da169fa1849bf5c27b81f5750b2c7fde43521c12e4415`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a60f8` — "mNumDisplayItems < MAX_DISPLAY_ITEMS"
- `0x4a6120` — "C:\\float\\src\\worldwin.cpp"
- `0x4a613c` — "mNumDisplayItems<MAX_DISPLAY_ITEMS"
- `0x4a6160` — "C:\\float\\src\\worldwin.cpp"

### Pseudocode Ghidra

```c
void FUN_004718eb(void)

{
  int in_ECX;
  short local_c;
  
  *(undefined2 *)(in_ECX + 0x678) = 0;
  for (local_c = 0; (int)local_c < (int)(uint)DAT_006136b0; local_c = local_c + 1) {
    if (0x3f < *(short *)(in_ECX + 0x678)) {
      thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a6120,0x300,
                         s_mNumDisplayItems_<_MAX_DISPLAY_I_004a60f8);
    }
    *(short *)(in_ECX + 0x78 + *(short *)(in_ECX + 0x678) * 0x18) = local_c;
    *(undefined4 *)(in_ECX + 0x7c + *(short *)(in_ECX + 0x678) * 0x18) = 0;
    *(short *)(in_ECX + 0x678) = *(short *)(in_ECX + 0x678) + 1;
  }
  for (local_c = 0; (int)local_c < (int)(uint)DAT_006137b4; local_c = local_c + 1) {
    if ((&DAT_006136b4)[local_c * 2] != 0) {
      if (0x3f < *(short *)(in_ECX + 0x678)) {
        thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a6160,0x30f,
                           s_mNumDisplayItems<MAX_DISPLAY_ITE_004a613c);
      }
      *(short *)(in_ECX + 0x78 + *(short *)(in_ECX + 0x678) * 0x18) = local_c;
      *(undefined4 *)(in_ECX + 0x7c + *(short *)(in_ECX + 0x678) * 0x18) = 1;
      *(short *)(in_ECX + 0x678) = *(short *)(in_ECX + 0x678) + 1;
    }
  }
  return;
}
```

---

# 0016_batch_0012 — détails (2/3)

## FUN_0045cb0b — 0x45cb0b

- Classification : internal
- Corps : `0x45cb0b–0x45cba9`
- État : pseudocode obtenu
- Evidence : `ev_d2fe25472fee84d35e760f64f32b8177d930c51e4c9861443f33b53d9517f084`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401451` — `thunk_FUN_00466732`
- `0x401e15` — `thunk_FUN_0045c82f`
- `0x4020b3` — `thunk_FUN_00466533`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045cb0b(int param_1)

{
  undefined4 uVar1;
  int in_ECX;
  
  if (param_1 == 0) {
    if (*(short *)(in_ECX + 0x50) != -1) {
      thunk_FUN_00466533((int)*(short *)(in_ECX + 0x50));
      *(undefined2 *)(in_ECX + 0x50) = 0xffff;
    }
    thunk_FUN_0045c82f();
    uVar1 = thunk_FUN_0045c3bb();
    thunk_FUN_00466732(uVar1,1);
    *(undefined2 *)(in_ECX + 0x4e) = 0xffff;
    thunk_FUN_00466732(uVar1,2);
    *(undefined2 *)(in_ECX + 0x52) = 0xffff;
    thunk_FUN_00466732(uVar1,3);
    *(undefined2 *)(in_ECX + 0x54) = 0xffff;
  }
  return;
}
```

---

---

## FUN_0045cbaa — 0x45cbaa

- Classification : internal
- Corps : `0x45cbaa–0x45cc16`
- État : pseudocode obtenu
- Evidence : `ev_0789846ee60f8a4d83463a89fc6fe12dfc11f8b3d9c16275c87c17f11589f4ba`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401451` — `thunk_FUN_00466732`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045cbaa(int param_1)

{
  undefined4 uVar1;
  int in_ECX;
  
  if (param_1 == 0) {
    uVar1 = thunk_FUN_0045c3bb();
    thunk_FUN_00466732(uVar1,1);
    *(undefined2 *)(in_ECX + 0x4e) = 0xffff;
    thunk_FUN_00466732(uVar1,2);
    *(undefined2 *)(in_ECX + 0x52) = 0xffff;
    thunk_FUN_00466732(uVar1,3);
    *(undefined2 *)(in_ECX + 0x54) = 0xffff;
  }
  return;
}
```

---

---

## FUN_0045cc17 — 0x45cc17

- Classification : internal
- Corps : `0x45cc17–0x45ccb8`
- État : pseudocode obtenu
- Evidence : `ev_662549a7323954de913c38a89d56389b3a108f6dc29b0fc24f36af952a7d1164`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401451` — `thunk_FUN_00466732`
- `0x401686` — `thunk_FUN_004666c9`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045cc17(short param_1)

{
  short sVar1;
  int iVar2;
  int in_ECX;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_8;
  
  iVar2 = thunk_FUN_0045c3bb();
  if (param_1 == 0) {
    local_8 = (short *)(in_ECX + 0x52);
    local_10 = (short *)(iVar2 + 0x2a);
    local_14 = 2;
  }
  else {
    local_8 = (short *)(in_ECX + 0x54);
    local_10 = (short *)(iVar2 + 0x2c);
    local_14 = 3;
  }
  if (*local_8 == -1) {
    if (*local_10 < 100) {
      sVar1 = thunk_FUN_004666c9(iVar2,local_14,0xffffffff);
      *local_8 = sVar1;
    }
  }
  else {
    thunk_FUN_00466732(iVar2,local_14);
    *local_8 = -1;
  }
  return;
}
```

---

---

## FUN_0045ccb9 — 0x45ccb9

- Classification : internal
- Corps : `0x45ccb9–0x45cccd`
- État : pseudocode obtenu
- Evidence : `ev_88f2fca28c72eb24ef1569654f3e11f71cea3d8054f270c16741f468c14427a0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401910` — `thunk_FUN_0045cb0b`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045ccb9(void)

{
  thunk_FUN_0045cb0b(0);
  return;
}
```

---

---

## FUN_0045ccce — 0x45ccce

- Classification : internal
- Corps : `0x45ccce–0x45cd26`
- État : pseudocode obtenu
- Evidence : `ev_03ae670f8ce55005e51708a495030fb04df7fd648e2c8b32c3beb60b80a5343b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40135c` — `thunk_FUN_00452e2b`
- `0x4014e7` — `thunk_FUN_0045035a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045ccce(int param_1)

{
  undefined2 uVar1;
  undefined2 *in_ECX;
  
  *in_ECX = *(undefined2 *)(param_1 + 8);
  uVar1 = thunk_FUN_0045035a();
  in_ECX[1] = uVar1;
  in_ECX[0x14] = *(undefined2 *)(param_1 + 8);
  *(undefined4 *)(in_ECX + 0x16) = 9;
  uVar1 = thunk_FUN_00452e2b();
  in_ECX[0x18] = uVar1;
  in_ECX[0x19] = 0;
  return;
}
```

---

---

## FUN_0045cd27 — 0x45cd27

- Classification : internal
- Corps : `0x45cd27–0x45cd74`
- État : pseudocode obtenu
- Evidence : `ev_31afe6370f840800d5842722949f28b40233ecb74d7efdf5eb1880738a17db1e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- `0x4a435c` — "C:\\float\\src\\staffbld.cpp"

### Pseudocode Ghidra

```c
int FUN_0045cd27(void)

{
  int iVar1;
  
  iVar1 = thunk_FUN_0045c3bb();
  if (iVar1 == 0) {
    thunk_FUN_00414b64(s_C__float_src_staffbld_cpp_004a435c,0x21e,&DAT_004a4358);
  }
  return *(short *)(iVar1 + 0x4a) * 0x19 + 0x32;
}
```

---

---

## FUN_0045cd75 — 0x45cd75

- Classification : internal
- Corps : `0x45cd75–0x45d3bc`
- État : pseudocode obtenu
- Evidence : `ev_2968fcc7203f402ad28ae77013ff42e2116410c3752743ae3eb5ee0390f207ab`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40114a` — `thunk_FUN_0045cc17`
- `0x4013c0` — `thunk_FUN_004655b2`
- `0x40156e` — `thunk_FUN_0041ff8b`
- `0x4018cf` — `thunk_FUN_0041ff2e`
- `0x4018f7` — `thunk_FUN_0045ca50`
- `0x401933` — `thunk_FUN_00464242`
- `0x401b63` — `thunk_FUN_0045c772`
- `0x401d1b` — `thunk_FUN_004662b7`
- `0x401e15` — `thunk_FUN_0045c82f`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fd7` — `thunk_FUN_0045c5ad`
- `0x402063` — `thunk_FUN_0045d3bd`
- `0x4020b3` — `thunk_FUN_00466533`
- `0x402144` — `thunk_FUN_00420f28`
- `0x4023bf` — `thunk_FUN_0045c3bb`
- `0x40248c` — `thunk_FUN_0045cd27`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a4378` — "type>=(int)PIT_Recruiter1 && type <=(int)PIT_Spec2"
- `0x4a43ac` — "C:\\float\\src\\staffbld.cpp"

### Pseudocode Ghidra

```c
void FUN_0045cd75(void)

{
  short *psVar1;
  short sVar2;
  undefined2 uVar3;
  undefined2 *in_ECX;
  int iVar4;
  int local_80;
  undefined1 local_64 [2];
  undefined2 local_62;
  undefined2 local_60;
  undefined2 local_5a;
  undefined2 local_58;
  undefined2 local_56;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  undefined4 local_44;
  undefined4 local_40;
  int local_3c;
  undefined4 *local_38;
  undefined4 local_34;
  short local_30 [4];
  int local_28;
  short local_24;
  int local_20;
  int local_1c;
  int local_18;
  short local_14 [4];
  int local_c;
  int local_8;
  
  local_28 = thunk_FUN_0045c3bb();
  _memset(local_14,0,6);
  _memset(local_30,0,6);
  for (local_24 = 0; local_24 < 8; local_24 = local_24 + 1) {
    if (in_ECX[local_24 + 2] != -1) {
      local_34 = &DAT_006137b8 + (short)in_ECX[local_24 + 2] * 0x13;
      sVar2 = thunk_FUN_0041ff2e();
      local_14[sVar2] = local_14[sVar2] + 1;
    }
  }
  local_18 = *(int *)(local_28 + 0x10);
  if ((local_18 < 0x2c) || (0x32 < local_18)) {
    thunk_FUN_00414b64(s_C__float_src_staffbld_cpp_004a43ac,0x23e,
                       s_type>__int_PIT_Recruiter1____typ_004a4378);
  }
  local_18 = local_18 + -0x2b;
  for (local_24 = 0; local_24 < 3; local_24 = local_24 + 1) {
    local_30[local_24] =
         *(short *)(&DAT_004a4170 + local_24 * 2 + *(short *)(local_28 + 0x4a) * 8 + local_18 * 0x18
                   ) - local_14[local_24];
  }
  local_8 = thunk_FUN_0045c772();
  *(uint *)(local_28 + 0x1c) = *(uint *)(local_28 + 0x1c) & 0xfffffff7;
  local_c = 0;
  for (local_24 = 0; local_24 < 8; local_24 = local_24 + 1) {
    if (in_ECX[local_24 + 2] != -1) {
      iVar4 = (short)in_ECX[local_24 + 2] * 0x4c;
      local_38 = &DAT_006137b8 + (short)in_ECX[local_24 + 2] * 0x13;
      if ((*(uint *)(&DAT_006137d4 + iVar4) & 0x20) == 0) {
        sVar2 = thunk_FUN_0041ff2e();
        local_48 = (int)sVar2;
        local_50 = DAT_004bf11c;
        local_4c = 4 - DAT_004bf11c;
        iVar4 = local_4c * *(short *)(&DAT_004a424a + local_48 * 2 + local_38[1] * 6) +
                DAT_004bf11c * *(short *)(&DAT_004a4282 + local_48 * 2 + local_38[1] * 6);
        local_54 = (int)(iVar4 + (iVar4 >> 0x1f & 3U)) >> 2;
        if (((((in_ECX[0x26] == -1) && (local_48 < *(short *)(&DAT_004a4158 + local_38[1] * 2))) &&
             (local_48 < *(short *)(local_28 + 0x4a))) &&
            ((local_54 <= *(short *)(local_38 + 2) && (0 < local_54)))) &&
           ((local_30[local_48 + 1] != 0 && ((in_ECX[0x28] == -1 && (local_8 != 0)))))) {
          in_ECX[0x26] = in_ECX[local_24 + 2];
          local_c = 1;
        }
        if ((local_38[0xb] == 2) && ((local_38[7] & 1) != 0)) {
          *(uint *)(local_28 + 0x1c) = *(uint *)(local_28 + 0x1c) | 8;
        }
      }
      else {
        *(uint *)(local_28 + 0x1c) = *(uint *)(local_28 + 0x1c) | 8;
        *(short *)(local_28 + 0x30) = *(short *)(local_28 + 0x30) + *(short *)(local_28 + 0x32);
        if (*(short *)(local_28 + 0x30) < 0xfb) {
          *(double *)(local_28 + 0x50) = (double)(int)*(short *)(local_28 + 0x30) / 250.0;
        }
        else {
          if (*(int *)(&DAT_006137bc + iVar4) == 0) {
            *(int *)(&DAT_006137bc + iVar4) = local_18;
            thunk_FUN_0041ff8b(0);
          }
          else {
            sVar2 = thunk_FUN_0041ff2e();
            local_3c = (int)sVar2;
            thunk_FUN_0041ff8b(local_3c + 1);
            sVar2 = thunk_FUN_0041ff2e();
            psVar1 = (short *)((int)&local_34 + sVar2 * 2 + 2);
            *psVar1 = *psVar1 + 1;
            sVar2 = thunk_FUN_0041ff2e();
            local_30[sVar2] = local_30[sVar2] + -1;
            local_44 = 6;
            local_40 = *local_38;
            thunk_FUN_004655b2(&local_44);
          }
          iVar4 = thunk_FUN_00464242(*local_38,local_38[1]);
          *(undefined2 *)((int)local_38 + 0x22) = *(undefined2 *)(iVar4 + 8);
          uVar3 = thunk_FUN_00420f28();
          *(undefined2 *)(local_38 + 8) = uVar3;
          thunk_FUN_0045c82f();
          if (in_ECX[0x28] != -1) {
            thunk_FUN_00466533((int)(short)in_ECX[0x28]);
            in_ECX[0x28] = 0xffff;
          }
        }
      }
    }
  }
  if ((in_ECX[0x26] == -1) || ((*(uint *)(&DAT_006137d4 + (short)in_ECX[0x26] * 0x4c) & 0x20) == 0))
  {
    local_80 = 0;
  }
  else {
    local_80 = 1;
  }
  local_20 = local_80;
  if (((0.0 < *(double *)(local_28 + 0x50)) && (local_80 == 0)) &&
     (*(double *)(local_28 + 0x50) = *(double *)(local_28 + 0x50) - 0.25,
     *(double *)(local_28 + 0x50) < 0.0)) {
    *(undefined4 *)(local_28 + 0x50) = 0;
    *(undefined4 *)(local_28 + 0x54) = 0;
  }
  if (local_c != 0) {
    thunk_FUN_0045c5ad();
  }
  if (((local_30[0] == 0) || (in_ECX[0x26] != -1)) || ((in_ECX[0x28] != -1 || (local_8 == 0)))) {
    if (((local_8 == 0) && (in_ECX[0x28] != -1)) && (local_20 == 0)) {
      thunk_FUN_00466533((int)(short)in_ECX[0x28]);
      in_ECX[0x28] = 0xffff;
    }
  }
  else {
    _memset(local_64,0,0x10);
    local_62 = *(undefined2 *)(local_28 + 0x14);
    local_60 = 0xb;
    local_56 = 0;
    local_58 = in_ECX[1];
    local_5a = *in_ECX;
    uVar3 = thunk_FUN_004662b7(local_64);
    in_ECX[0x28] = uVar3;
  }
  if ((in_ECX[0x27] != -1) && (0x13 < *(short *)(local_28 + 0x28))) {
    thunk_FUN_0045ca50();
  }
  sVar2 = thunk_FUN_0045cd27();
  local_1c = (int)sVar2;
  if (*(int *)(in_ECX + 0x2c) == 0) {
    if (in_ECX[0x29] != -1) {
      thunk_FUN_0045cc17(0);
    }
  }
  else if (in_ECX[0x29] == -1) {
    if (*(short *)(local_28 + 0x2a) < local_1c) {
      thunk_FUN_0045cc17(0);
    }
  }
  else if (local_1c <= *(short *)(local_28 + 0x2a)) {
    thunk_FUN_0045cc17(0);
  }
  if (*(int *)(local_28 + 0x10) == 0x2f) {
    if (*(int *)(in_ECX + 0x2e) == 0) {
      if (in_ECX[0x2a] != -1) {
        thunk_FUN_0045cc17(1);
      }
    }
    else if (in_ECX[0x2a] == -1) {
      if (*(short *)(local_28 + 0x2c) < local_1c) {
        thunk_FUN_0045cc17(1);
      }
    }
    else if (local_1c <= *(short *)(local_28 + 0x2c)) {
      thunk_FUN_0045cc17(1);
    }
  }
  thunk_FUN_0045d3bd();
  return;
}
```

---

---

## FUN_0045d3bd — 0x45d3bd

- Classification : internal
- Corps : `0x45d3bd–0x45d53b`
- État : pseudocode obtenu
- Evidence : `ev_893c4b5ee60dd372f1b3e170309270433c807e778543ea6bb6eb7c4db1bbd25f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40123a` — `thunk_FUN_0041e3eb`
- `0x40135c` — `thunk_FUN_00452e2b`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045d3bd(void)

{
  int iVar1;
  short sVar2;
  short *psVar3;
  undefined2 uVar4;
  short *in_ECX;
  int iVar5;
  bool bVar6;
  int local_18;
  
  psVar3 = in_ECX + 0x14;
  bVar6 = false;
  if (*(int *)(in_ECX + 0x16) == 6) {
    bVar6 = (&DAT_006137b8)[in_ECX[0x18] * 0x13] == -1;
  }
  else if ((*(int *)(in_ECX + 0x16) == 7) &&
          ((iVar1 = in_ECX[0x18] * 0x60 + *psVar3 * 0x29e8,
           *(int *)(&DAT_005ec640 + iVar1 + 0x14) == -1 ||
           ((*(uint *)(&DAT_005ec640 + iVar1 + 0x1c) & 0x80) != 0)))) {
    bVar6 = true;
  }
  if (bVar6) {
    in_ECX[0x16] = 0;
    in_ECX[0x17] = 0;
    for (local_18 = 0; local_18 < 8; local_18 = local_18 + 1) {
      if (in_ECX[local_18 + 2] != -1) {
        sVar2 = in_ECX[local_18 + 2];
        iVar5 = sVar2 * 0x4c;
        iVar1 = *(int *)(&DAT_006137f4 + iVar5);
        if ((((iVar1 == 9) || (iVar1 == 8)) || (iVar1 == 7)) || (iVar1 == 6)) {
          in_ECX[0x16] = 9;
          in_ECX[0x17] = 0;
          *psVar3 = *(short *)(&DAT_006137c6 + iVar5);
          uVar4 = (undefined2)((uint)(&DAT_006137b8 + sVar2 * 0x13) >> 0x10);
          sVar2 = thunk_FUN_0041e3eb(CONCAT22(uVar4,*(undefined2 *)(&DAT_006137c8 + iVar5)),
                                     CONCAT22(uVar4,*(undefined2 *)(&DAT_006137ca + iVar5)));
          in_ECX[0x18] = sVar2;
        }
      }
    }
  }
  if (*(int *)(in_ECX + 0x16) == 0) {
    *psVar3 = *in_ECX;
    in_ECX[0x16] = 9;
    in_ECX[0x17] = 0;
    thunk_FUN_0045c3bb();
    sVar2 = thunk_FUN_00452e2b();
    in_ECX[0x18] = sVar2;
  }
  return;
}
```

---

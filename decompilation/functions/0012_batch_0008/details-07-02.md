# 0012_batch_0008 — détails (2/2)

## FUN_0043913c — 0x43913c

- Classification : internal
- Corps : `0x43913c–0x4391aa`
- État : pseudocode obtenu
- Evidence : `ev_082f8189d1b634d4d3b4c9aa5a845b0958026adc3177c02f8ef77b63cbca8eaa`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x402018` — `thunk_FUN_0043822b`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043913c(short param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  
  if (param_1 == 1) {
    *(short *)(in_ECX + 0x70) = *(char *)(in_ECX + 0x26) + -0x31;
  }
  else if ((param_1 == 7) && (iVar1 = thunk_FUN_00429f3a(), iVar1 != 0)) {
    thunk_FUN_0043822b((int)*(short *)(in_ECX + 0x70));
    return 1;
  }
  uVar2 = thunk_FUN_004293c6(param_1,param_2,param_3);
  return uVar2;
}
```

---

---

## FUN_004391ab — 0x4391ab

- Classification : internal
- Corps : `0x4391ab–0x4393aa`
- État : pseudocode obtenu
- Evidence : `ev_4bf5078bdf014da068c91380750b850555115573d41e5264004b461f7eacf337`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40146f` — `thunk_FUN_0042d87c`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401eab` — `thunk_FUN_0040bf98`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402018` — `thunk_FUN_0043822b`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x4021bc` — `thunk_FUN_004381e1`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- `0x49fc00` — "C:\\float\\src\\islewin2.cpp"
- `0x49fc1c` — "bildicon"
- `0x49fc28` — "shape"
- `0x49fc30` — "C:\\float\\src\\islewin2.cpp"

### Pseudocode Ghidra

```c
void FUN_004391ab(void)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int in_ECX;
  undefined4 uVar5;
  undefined4 uVar6;
  int local_28;
  int local_20;
  int local_1c;
  int local_18;
  int local_8;
  
  local_8 = thunk_FUN_004381e1((int)*(short *)(in_ECX + 0x70));
  if ((local_8 != 0) && (iVar2 = thunk_FUN_0045c3bb(), iVar2 == 0)) {
    thunk_FUN_0043822b((int)*(short *)(in_ECX + 0x70));
    local_8 = 0;
  }
  uVar3 = thunk_FUN_0042d28f();
  *(undefined4 *)(in_ECX + 8) = uVar3;
  if (DAT_004c2bac == 0) {
    thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
  }
  else {
    uVar6 = 0;
    uVar5 = 0;
    iVar2 = (int)*(short *)(in_ECX + 0x1e);
    uVar3 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
    thunk_FUN_00404770(in_ECX + 8,uVar3,iVar2,uVar5,uVar6);
  }
  if (local_8 != 0) {
    sVar1 = *(short *)(local_8 + 0x60);
    iVar2 = thunk_FUN_0045c3bb();
    if (iVar2 == 0) {
      thunk_FUN_00414b64(s_C__float_src_islewin2_cpp_0049fc00,0x28c,&DAT_0049fbfc);
    }
    if (*(int *)(iVar2 + 0x10) != 0) {
      thunk_FUN_0040bf98(in_ECX + 8,iVar2,0xc,0x1e,0,0x6000,0xffffffff);
      local_18 = 1;
      local_20 = 1;
      iVar4 = thunk_FUN_0040ec89(s_bildicon_0049fc1c,1);
      if (iVar4 == 0) {
        uVar3 = thunk_FUN_00414b64(s_C__float_src_islewin2_cpp_0049fc30,0x296,s_shape_0049fc28);
      }
      else {
        uVar3 = 0;
      }
      for (local_1c = 0; local_1c < sVar1; local_1c = local_1c + 1) {
        local_28 = *(int *)(iVar2 + 0x14);
        if (local_28 < 0) {
          local_28 = 0;
        }
        if (3 < local_28) {
          local_28 = 3;
        }
        thunk_FUN_00404770(in_ECX + 8,iVar4,local_28,local_18,local_20,uVar3);
        local_18 = local_18 + 5;
        if (local_1c == 4) {
          local_20 = local_20 + 5;
          local_18 = 1;
        }
      }
    }
  }
  thunk_FUN_0042d38a();
  thunk_FUN_0042d87c(in_ECX + 8,3);
  return;
}
```

---

---

## FUN_004393ab — 0x4393ab

- Classification : internal
- Corps : `0x4393ab–0x43954c`
- État : pseudocode obtenu
- Evidence : `ev_d0dd440fa2eff6227014d444c773d2784ce048ee725a1fd47d226568240c98f6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fff` — `thunk_FUN_0040fdab`
- `0x402455` — `thunk_FUN_004199c0`

### Chaînes référencées

- `0x49fc4c` — "slot<TOTALCLIPS"
- `0x49fc5c` — "C:\\float\\src\\islewin2.cpp"
- `0x49fc78` — "slot<TOTALCLIPS"
- `0x49fc88` — "C:\\float\\src\\islewin2.cpp"

### Pseudocode Ghidra

```c
void FUN_004393ab(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int in_ECX;
  int local_14;
  int local_c;
  int local_8;
  
  if (*(short *)(in_ECX + 0x70) == -1) {
    *(short *)(in_ECX + 0x70) = *(char *)(in_ECX + 0x26) + -0x31;
  }
  if (param_2 == 0) {
    for (local_14 = 0; local_14 < 3; local_14 = local_14 + 1) {
      iVar1 = local_14 * 3 + (int)*(short *)(in_ECX + 0x70);
      if (8 < iVar1) {
        thunk_FUN_00414b64(s_C__float_src_islewin2_cpp_0049fc88,0x2cc,s_slot<TOTALCLIPS_0049fc78);
      }
      local_8 = -1;
      if (*(int *)(&DAT_005e16b0 + iVar1 * 4) != 0) {
        local_8 = (*(int *)(&DAT_005e16b0 + iVar1 * 4) -
                  (int)(&DAT_006192b0 + DAT_0049f538 * 0x14a0)) / 100;
      }
      thunk_FUN_004199c0(local_8);
    }
    thunk_FUN_004199c0((int)DAT_005e16a8);
  }
  else {
    for (local_c = 0; local_c < 3; local_c = local_c + 1) {
      iVar1 = local_c * 3 + (int)*(short *)(in_ECX + 0x70);
      if (8 < iVar1) {
        thunk_FUN_00414b64(s_C__float_src_islewin2_cpp_0049fc5c,0x2bf,s_slot<TOTALCLIPS_0049fc4c);
      }
      *(undefined4 *)(&DAT_005e16b0 + iVar1 * 4) = 0;
      iVar2 = thunk_FUN_0040fdab();
      if (iVar2 != -1) {
        *(undefined **)(&DAT_005e16b0 + iVar1 * 4) =
             &DAT_006192b0 + iVar2 * 100 + DAT_0049f538 * 0x14a0;
      }
    }
    DAT_005e16a8 = thunk_FUN_0040fdab();
  }
  return;
}
```

---

---

## FUN_0043954d — 0x43954d

- Classification : internal
- Corps : `0x43954d–0x439582`
- État : pseudocode obtenu
- Evidence : `ev_0462b1ceb129a2813a40fb6a28915c0c9c76b969abb6e8bdcb9267529b9307f8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x401712` — `thunk_FUN_004289a7`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043954d(undefined4 param_1,int param_2,undefined4 *param_3,int *param_4,
                 undefined4 *param_5)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = thunk_FUN_0042de0d();
  iVar2 = thunk_FUN_004289a7(uVar1);
  *param_4 = param_2 + 1 + iVar2;
  *param_3 = 6;
  *param_5 = 0xad;
  return;
}
```

---

---

## FUN_00439583 — 0x439583

- Classification : internal
- Corps : `0x439583–0x4395d6`
- État : pseudocode obtenu
- Evidence : `ev_3e6e0f5322e9ae7b01d74cabdb29a3242cd703f42b03ce0dffba7de2cea5bc71`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`
- `0x40230b` — `thunk_FUN_004395f3`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00439583(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049172c;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494350;
  thunk_FUN_004395f3();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_004395d7 — 0x4395d7

- Classification : internal
- Corps : `0x4395d7–0x4395f2`
- État : pseudocode obtenu
- Evidence : `ev_a9febe32a35b0ee4077703b18106801af8148f6b75c2be90ebb826a213063afc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004395d7(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494350;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_004395f3 — 0x4395f3

- Classification : internal
- Corps : `0x4395f3–0x439607`
- État : pseudocode obtenu
- Evidence : `ev_d0336a2d554469591f35dc37025f7635b627b62a5bbd4be0117a94ccaf4f2df6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004395f3(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x70) = 0xffffffff;
  return;
}
```

---

---

## FUN_00439608 — 0x439608

- Classification : internal
- Corps : `0x439608–0x439672`
- État : pseudocode obtenu
- Evidence : `ev_28be9761760055f54744a72179aad9c4ccb9b59491de3497621063f64522718c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00439608(short param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int in_ECX;
  
  if (param_1 == 1) {
    *(undefined4 *)(in_ECX + 0x70) = 0xffffffff;
  }
  else if (param_1 == 0x3039) {
    *(undefined4 *)(in_ECX + 0x70) = param_2;
    *(undefined4 *)(in_ECX + 0x74) = param_3;
    *(undefined4 *)(in_ECX + 0x34) = 1;
    return 1;
  }
  uVar1 = thunk_FUN_004293c6((int)param_1,param_2,param_3);
  return uVar1;
}
```

---

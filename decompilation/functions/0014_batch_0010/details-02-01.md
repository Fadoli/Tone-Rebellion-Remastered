# 0014_batch_0010 — détails (1/3)

## FUN_00443078 — 0x443078

- Classification : internal
- Corps : `0x443078–0x443297`
- État : pseudocode obtenu
- Evidence : `ev_b872d320147a8da387abab84a4718d044f80384eeb68c8dd6deca921809761a5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40116d` — `thunk_FUN_0041e4d9`
- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4017a3` — `thunk_FUN_0041e4c3`
- `0x401a87` — `thunk_FUN_0042704b`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x402158` — `thunk_FUN_004667eb`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`

### Chaînes référencées

- `0x4a0c38` — "mpLocInfo"
- `0x4a0c44` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0c60` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0c78` — "diploma"

### Pseudocode Ghidra

```c
void FUN_00443078(void)

{
  undefined1 uVar1;
  int iVar2;
  int in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_4c;
  undefined4 local_18;
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004918e6;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    if (*(int *)(in_ECX + 0x70) == 0) {
      uVar4 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0c44,0x615,s_mpLocInfo_004a0c38);
    }
    else {
      uVar4 = 0;
    }
    local_14 = *(int *)(*(int *)(in_ECX + 0x70) + 0x70);
    if (local_14 == 0) {
      uVar3 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0c60,0x61c,&DAT_004a0c5c);
    }
    else {
      uVar3 = 0;
    }
    uVar4 = thunk_FUN_0042d28f(uVar3,uVar4);
    *(undefined4 *)(in_ECX + 8) = uVar4;
    uVar1 = thunk_FUN_0042dd0f(0);
    thunk_FUN_00406604(in_ECX + 8,uVar1);
    iVar2 = thunk_FUN_00429f3a();
    if (iVar2 != 0) {
      local_18 = thunk_FUN_0040ec89(s_diploma_004a0c78,1);
      thunk_FUN_00404770(in_ECX + 8,local_18,0x17,
                         (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 2 + -0x14,0);
    }
    if (((4 < *(int *)(local_14 + 0x24)) && (*(int *)(local_14 + 0x24) < 0x22)) &&
       (iVar2 = thunk_FUN_004667eb(local_14,*(undefined4 *)(local_14 + 0x24),DAT_0049f538),
       iVar2 == 0)) {
      thunk_FUN_0041e4c3();
      uVar4 = DAT_005c37f4;
      local_8 = 0;
      local_64 = DAT_0049f538;
      local_60 = 0;
      local_4c = *(undefined4 *)(local_14 + 0x24);
      DAT_005c37fc = 0;
      DAT_005c37f8 = 0;
      DAT_005c37f4 = 0;
      thunk_FUN_0042704b(in_ECX + 8,&local_64,(*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 2
                         ,0x14,1,8,0x10000,0);
      DAT_005c37fc = uVar4;
      DAT_005c37f8 = uVar4;
      local_8 = 0xffffffff;
      DAT_005c37f4 = uVar4;
      thunk_FUN_0041e4d9();
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,1);
  }
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

---

## FUN_00443298 — 0x443298

- Classification : internal
- Corps : `0x443298–0x4432eb`
- État : pseudocode obtenu
- Evidence : `ev_4feda02a1698432f71c8a1063d81f9e7931ad7a69a2f918028d847672829be4d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b77` — `thunk_FUN_00443308`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00443298(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004918f9;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494548;
  thunk_FUN_00443308();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_004432ec — 0x4432ec

- Classification : internal
- Corps : `0x4432ec–0x443307`
- État : pseudocode obtenu
- Evidence : `ev_e9aa39a47f834c20dae3bbfebab8187bae15f710ae00455caf807a71e7866f03`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004432ec(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494548;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_00443308 — 0x443308

- Classification : internal
- Corps : `0x443308–0x44331c`
- État : pseudocode obtenu
- Evidence : `ev_3d7b384a38e97dd79d7527c783feea56dad43e2a2e7797528865f5ffcbde252b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00443308(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x70) = 0;
  return;
}
```

---

---

## FUN_0044331d — 0x44331d

- Classification : internal
- Corps : `0x44331d–0x44338a`
- État : pseudocode obtenu
- Evidence : `ev_ef2d085fe5f3597a4a7ff8d2b5e0abf7b0eb70b92d580f2093b740db80eb6f43`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044331d(short param_1,int param_2,undefined4 param_3)

{
  int *in_ECX;
  
  if (param_1 == 0x350b) {
    in_ECX[0x1c] = param_2;
    if (in_ECX[0x1c] == 0) {
      (**(code **)(*in_ECX + 4))(2,0,0);
    }
    else {
      (**(code **)(*in_ECX + 4))(1,0,0);
    }
  }
  else {
    thunk_FUN_004293c6(param_1,param_2,param_3);
  }
  return;
}
```

---

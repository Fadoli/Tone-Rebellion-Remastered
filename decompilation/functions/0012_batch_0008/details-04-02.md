# 0012_batch_0008 — détails (2/2)

## FUN_00433168 — 0x433168

- Classification : internal
- Corps : `0x433168–0x433270`
- État : pseudocode obtenu
- Evidence : `ev_8b0d0f14d0a0faa0a1a3295bb245790391fa5cb973848cd8d3bd12075e0c8522`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021da` — `thunk_FUN_00432e79`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00433168(void)

{
  short *local_c;
  int local_8;
  
  DAT_005dc674 = (int)*(short *)(*(int *)(DAT_005dc64c + 0x9c) + 0x29a8);
  local_c = (short *)(*(int *)(DAT_005dc64c + 0x9c) + 0x428);
  for (local_8 = 0; local_8 < *(short *)(*(int *)(DAT_005dc64c + 0x9c) + 0x29a8);
      local_8 = local_8 + 1) {
    if (*(int *)(local_c + 2) == 0) {
      (&DAT_005dbf08)[local_8 * 3] = *(undefined4 *)(local_c + 6);
    }
    else if (*(int *)(local_c + 2) == 1) {
      (&DAT_005dbf08)[local_8 * 3] = 3;
    }
    else if (*(int *)(local_c + 2) == 2) {
      (&DAT_005dbf08)[local_8 * 3] = 4;
    }
    else {
      (&DAT_005dbf08)[local_8 * 3] = 5;
    }
    (&DAT_005dbf00)[local_8 * 3] = (int)*local_c;
    (&DAT_005dbf04)[local_8 * 3] = (int)local_c[1];
    local_c = local_c + 0x30;
  }
  DAT_0049f544 = 0xffffffff;
  thunk_FUN_00432e79();
  return;
}
```

---

---

## FUN_00433271 — 0x433271

- Classification : internal
- Corps : `0x433271–0x433389`
- État : pseudocode obtenu
- Evidence : `ev_41d5cca8a5b0aae08c940b97c1a45ae38823a8a3c9b5c4f8d4b359f1a86e8c67`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021da` — `thunk_FUN_00432e79`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00433271(int param_1,int param_2)

{
  int local_1c;
  int local_18;
  int local_10;
  int local_c;
  int local_8;
  
  if ((DAT_005dc67c == 0) || (DAT_0049f544 == -1)) {
    local_c = 100;
    local_8 = -1;
    for (local_10 = 0; local_10 < DAT_005dc674; local_10 = local_10 + 1) {
      if ((&DAT_005dbf00)[local_10 * 3] - param_1 < 0) {
        local_18 = -((&DAT_005dbf00)[local_10 * 3] - param_1);
      }
      else {
        local_18 = (&DAT_005dbf00)[local_10 * 3] - param_1;
      }
      if ((&DAT_005dbf04)[local_10 * 3] - param_2 < 0) {
        local_1c = -((&DAT_005dbf04)[local_10 * 3] - param_2);
      }
      else {
        local_1c = (&DAT_005dbf04)[local_10 * 3] - param_2;
      }
      if (local_18 + local_1c < local_c) {
        local_8 = local_10;
        local_c = local_18 + local_1c;
      }
    }
    DAT_0049f544 = local_8;
  }
  else {
    (&DAT_005dbf00)[DAT_0049f544 * 3] = param_1;
    (&DAT_005dbf04)[DAT_0049f544 * 3] = param_2;
    thunk_FUN_00432e79();
  }
  return;
}
```

---

---

## FUN_0043338a — 0x43338a

- Classification : internal
- Corps : `0x43338a–0x4333ef`
- État : pseudocode obtenu
- Evidence : `ev_fc8050eb5b0665150d5435b6e14c3d99ecca06d5c8ad3da488ff121583d7f7aa`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021da` — `thunk_FUN_00432e79`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043338a(undefined4 param_1,undefined4 param_2)

{
  if (DAT_005dc674 < 100) {
    (&DAT_005dbf00)[DAT_005dc674 * 3] = param_1;
    (&DAT_005dbf04)[DAT_005dc674 * 3] = param_2;
    (&DAT_005dbf08)[DAT_005dc674 * 3] = DAT_005dc688;
    DAT_0049f544 = DAT_005dc674;
    DAT_005dc674 = DAT_005dc674 + 1;
    thunk_FUN_00432e79();
  }
  return;
}
```

---

---

## FUN_004333f0 — 0x4333f0

- Classification : internal
- Corps : `0x4333f0–0x433448`
- État : pseudocode obtenu
- Evidence : `ev_be76f6a05e25447abae7a61a8b2005441197b2e86f9966220d11910f7a1fc6f2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021da` — `thunk_FUN_00432e79`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004333f0(void)

{
  int local_8;
  
  if (DAT_0049f544 != -1) {
    if ((&DAT_005dbf08)[DAT_0049f544 * 3] == 5) {
      local_8 = 0;
    }
    else {
      local_8 = (&DAT_005dbf08)[DAT_0049f544 * 3] + 1;
    }
    (&DAT_005dbf08)[DAT_0049f544 * 3] = local_8;
    DAT_005dc688 = local_8;
    thunk_FUN_00432e79();
  }
  return;
}
```

---

---

## FUN_00433449 — 0x433449

- Classification : internal
- Corps : `0x433449–0x4334cd`
- État : pseudocode obtenu
- Evidence : `ev_0fbaac245261461d7bd9cba8f4dbb614f84a44388a8f83af4dc82ccb428aff5c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021da` — `thunk_FUN_00432e79`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00433449(void)

{
  int iVar1;
  int local_8;
  
  if ((DAT_0049f544 != -1) && (0 < DAT_005dc674)) {
    for (local_8 = DAT_0049f544; local_8 < DAT_005dc674 + -1; local_8 = local_8 + 1) {
      iVar1 = local_8 + 1;
      (&DAT_005dbf00)[local_8 * 3] = (&DAT_005dbf00)[iVar1 * 3];
      (&DAT_005dbf04)[local_8 * 3] = (&DAT_005dbf04)[iVar1 * 3];
      (&DAT_005dbf08)[local_8 * 3] = (&DAT_005dbf08)[iVar1 * 3];
    }
    DAT_005dc674 = DAT_005dc674 + -1;
    DAT_0049f544 = -1;
    thunk_FUN_00432e79();
  }
  return;
}
```

---

---

## FUN_004334ce — 0x4334ce

- Classification : internal
- Corps : `0x4334ce–0x4336b6`
- État : pseudocode obtenu
- Evidence : `ev_9d4effbf419b2608ab97220e863f96019bd578d5b9de60b9e93dab16fcf3231b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401285` — `thunk_FUN_00436e06`
- `0x4012cb` — `thunk_FUN_0045b8d1`
- `0x40150f` — `thunk_FUN_0046ff6f`
- `0x402013` — `thunk_FUN_0045aafd`
- `0x472ca0` — `FUN_00472ca0`
- `0x472da0` — `FUN_00472da0`
- `0x474b90` — `FUN_00474b90`

### Chaînes référencées

- `0x49f824` — "FLTADV"
- `0x49f834` — "LEVIBRK"
- `0x49f844` — "%s%s."
- `0x49f864` — "winend"
- `0x49f864` — "winend"
- `0x49f86c` — "loosend"
- `0x49f86c` — "loosend"

### Pseudocode Ghidra

```c
void FUN_004334ce(int param_1,uint param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  char *local_74;
  char local_54 [80];
  
  local_54[0] = '\0';
  if ((param_1 == 6) && (param_2 == DAT_0049f538)) {
    uVar1 = thunk_FUN_00429ebe(s_FLTADV_0049f824,0);
    thunk_FUN_00436e06(uVar1,1);
  }
  else if (param_1 == 10) {
    if (param_2 == 0xffffffff) {
      DAT_0049f831 = (char)DAT_0049f538 + '0';
      uVar1 = thunk_FUN_00429ebe(&DAT_0049f82c,0);
      FUN_00472da0(local_54,uVar1);
    }
    else if ((int)param_2 < 8) {
      uVar1 = thunk_FUN_00429ebe(s_LEVIBRK_0049f834,0);
      DAT_0049f840 = (char)param_2 + '0';
      uVar2 = thunk_FUN_00429ebe(&DAT_0049f83c,0);
      FUN_00472ca0(local_54,s__s_s__0049f844,uVar1,uVar2);
    }
    if (local_54[0] != '\0') {
      thunk_FUN_00436e06(local_54,1);
    }
  }
  else if (param_1 == 0xc) {
    if ((int)param_2 < 4) {
      DAT_0049f84f = (char)param_2 + '1';
      iVar3 = thunk_FUN_0045b8d1(&DAT_0049f84c);
      if (iVar3 == 0) {
        thunk_FUN_0045aafd(&DAT_0049f84c,0,0,0);
      }
    }
    else if (param_2 == 0xe) {
      iVar3 = thunk_FUN_0045b8d1(&DAT_0049f854);
      if (iVar3 == 0) {
        thunk_FUN_0045aafd(&DAT_0049f85c,0,0,0);
      }
    }
    else {
      uVar4 = FUN_00474b90();
      if ((uVar4 & 1) != 0) {
        thunk_FUN_0046ff6f(0);
      }
    }
  }
  else if (param_1 == 0xb) {
    local_74 = (char *)0x0;
    if (param_2 == 0) {
      local_74 = s_winend_0049f864;
    }
    else if (((param_2 & 0xff) == 3) && ((int)param_2 >> 0x10 == DAT_0049f538)) {
      local_74 = s_loosend_0049f86c;
    }
    if (local_74 != (char *)0x0) {
      thunk_FUN_0045aafd(local_74,0,0,0);
    }
  }
  return;
}
```

---

---

## FUN_004336b7 — 0x4336b7

- Classification : internal
- Corps : `0x4336b7–0x43370a`
- État : pseudocode obtenu
- Evidence : `ev_4224048dd8a599bbfc881065f1426a94413c38138b1dd2d9f7d54d6495bf82e8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a96` — `thunk_FUN_00433727`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_004336b7(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004916d5;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004942a8;
  thunk_FUN_00433727();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0043370b — 0x43370b

- Classification : internal
- Corps : `0x43370b–0x433726`
- État : pseudocode obtenu
- Evidence : `ev_880cc97ab771a6993274c7a7958aeacfaf429c8b6f5203b04358591e899cc762`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043370b(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004942a8;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_00433727 — 0x433727

- Classification : internal
- Corps : `0x433727–0x4337b9`
- État : pseudocode obtenu
- Evidence : `ev_46d138384ac2c3f8a53ac2872057b35f9e69ea2ecc9cb93a90d04234cfdecf09`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00433727(void)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x70) = 0xffff;
  *(undefined2 *)(in_ECX + 0x72) = 0;
  *(undefined4 *)(in_ECX + 0x88) = 0;
  *(int *)(in_ECX + 0x74) = in_ECX + 0x88;
  *(undefined4 *)(in_ECX + 0x9c) = 0;
  _memset(&DAT_005dbee0,0,0x1e);
  *(undefined4 *)(in_ECX + 0x174) = 0;
  *(undefined2 *)(in_ECX + 0x178) = 0;
  *(undefined2 *)(in_ECX + 0x17a) = 0xffff;
  *(undefined2 *)(in_ECX + 0x17c) = 0xffff;
  *(undefined2 *)(in_ECX + 0x17e) = 0;
  return;
}
```

---

---

## FUN_004337ba — 0x4337ba

- Classification : internal
- Corps : `0x4337ba–0x4337d8`
- État : pseudocode obtenu
- Evidence : `ev_91aa7266f35a7bbe8a16dc5d70eb83be4dc0fd5e8e41927db667e91c2d6efce7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021f3` — `thunk_FUN_0046c7df`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004337ba(void)

{
  undefined4 uVar1;
  int in_ECX;
  
  uVar1 = thunk_FUN_0046c7df(in_ECX);
  *(undefined4 *)(in_ECX + 4) = uVar1;
  return;
}
```

---

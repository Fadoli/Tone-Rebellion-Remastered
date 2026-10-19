# 0013_batch_0009 — détails (2/3)

## FUN_0043c396 — 0x43c396

- Classification : internal
- Corps : `0x43c396–0x43c6c3`
- État : pseudocode obtenu
- Evidence : `ev_5ec6f68730855f7b0d35af54b1f5f437c5284d3c8442550b6627fc349a44cab7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x401398` — `thunk_FUN_0043c6c4`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401569` — `thunk_FUN_0046c558`
- `0x401cf8` — `thunk_FUN_0043c7bb`

### Chaînes référencées

- `0x4a00ac` — "scrollup"
- `0x4a00b8` — "scrolldn"
- `0x4a00c4` — "scrollup"
- `0x4a00d0` — "scrolldn"

### Pseudocode Ghidra

```c
undefined4 FUN_0043c396(short param_1,int param_2,int param_3)

{
  short sVar1;
  bool bVar2;
  undefined4 uVar3;
  int in_ECX;
  
  bVar2 = false;
  if (param_1 < 8) {
    if (param_1 < 6) {
      if (param_1 == 1) {
        *(undefined2 *)(in_ECX + 0x70) = DAT_005ea1b0;
        *(short *)(in_ECX + 0x74) =
             (short)((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) / 10);
        *(undefined2 *)(in_ECX + 0x76) = 0;
        if ((*(short *)(in_ECX + 0x78) == -1) || (*(short *)(in_ECX + 0x7a) == -1)) {
          thunk_FUN_0046c558(s_scrollup_004a00ac,3,in_ECX + 0x78);
          thunk_FUN_0046c558(s_scrolldn_004a00b8,3,in_ECX + 0x7a);
        }
        if ((*(short *)(in_ECX + 0x78) != -1) && (*(short *)(in_ECX + 0x7a) != -1)) {
          thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x78),1,0,0);
          thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x7a),1,0,0);
        }
      }
      else if (param_1 == 2) {
        if ((*(short *)(in_ECX + 0x78) != -1) || (*(short *)(in_ECX + 0x7a) == -1)) {
          thunk_FUN_0046c558(s_scrollup_004a00c4,3,in_ECX + 0x78);
          thunk_FUN_0046c558(s_scrolldn_004a00d0,3,in_ECX + 0x7a);
        }
        thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x78),2,0,0);
        thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x7a),2,0,0);
        *(undefined4 *)(in_ECX + 0x7c) = 0;
        *(undefined4 *)(in_ECX + 0x80) = 0;
      }
    }
    else if ((((*(int *)(in_ECX + 0xc) < param_2) && (param_2 < *(int *)(in_ECX + 0x14) + -0xd)) &&
             (*(int *)(in_ECX + 0x10) < param_3)) && (param_3 < *(int *)(in_ECX + 0x18))) {
      if ((DAT_0062c6bc == *(short *)(in_ECX + 0x78)) || (DAT_0062c6bc == *(short *)(in_ECX + 0x7a))
         ) {
        return 0;
      }
      thunk_FUN_0043c6c4(param_2,param_3,param_1 == 7);
      bVar2 = true;
    }
  }
  else if (param_1 == 6000) {
    sVar1 = *(short *)(in_ECX + 0x76);
    *(short *)(in_ECX + 0x76) = *(short *)(in_ECX + 0x76) - *(short *)(in_ECX + 0x74);
    if (*(short *)(in_ECX + 0x76) < 0) {
      *(undefined2 *)(in_ECX + 0x76) = 0;
    }
    if (sVar1 != *(short *)(in_ECX + 0x76)) {
      thunk_FUN_0043c7bb();
    }
    bVar2 = true;
  }
  else if (param_1 == 0x1771) {
    sVar1 = *(short *)(in_ECX + 0x76);
    if (((int)*(short *)(in_ECX + 0x70) != (int)*(short *)(in_ECX + 0x74) &&
         -1 < (int)*(short *)(in_ECX + 0x70) - (int)*(short *)(in_ECX + 0x74)) &&
       (*(short *)(in_ECX + 0x76) = *(short *)(in_ECX + 0x76) + *(short *)(in_ECX + 0x74),
       (int)*(short *)(in_ECX + 0x70) - (int)*(short *)(in_ECX + 0x74) <
       (int)*(short *)(in_ECX + 0x76))) {
      *(short *)(in_ECX + 0x76) = *(short *)(in_ECX + 0x70) - *(short *)(in_ECX + 0x74);
    }
    if (sVar1 != *(short *)(in_ECX + 0x76)) {
      thunk_FUN_0043c7bb();
    }
    bVar2 = true;
  }
  if (bVar2) {
    uVar3 = 1;
  }
  else {
    uVar3 = thunk_FUN_004293c6(param_1,param_2,param_3);
  }
  return uVar3;
}
```

---

---

## FUN_0043c6c4 — 0x43c6c4

- Classification : internal
- Corps : `0x43c6c4–0x43c7ba`
- État : pseudocode obtenu
- Evidence : `ev_9dcd8bc0d2126bd3a5fb9c284f1ef3c89ad89bafc9e89c5b967e3e174547d8c3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40184d` — `thunk_FUN_0045b24d`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401aaf` — `thunk_FUN_0045afb9`

### Chaînes référencées

- `0x4a00dc` — "IWEffList"

### Pseudocode Ghidra

```c
undefined4 FUN_0043c6c4(int param_1,int param_2,int param_3)

{
  int in_ECX;
  undefined2 extraout_var;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_10 = param_1 - *(int *)(in_ECX + 0xc);
  local_c = param_2 - *(int *)(in_ECX + 0x10);
  local_8 = (local_c -
            ((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + *(short *)(in_ECX + 0x74) * -10)
            / 2) / 10 + (int)*(short *)(in_ECX + 0x76);
  if (local_8 < 0) {
    local_8 = 0;
  }
  if (local_8 < *(short *)(in_ECX + 0x70)) {
    *(undefined2 *)(in_ECX + 0x72) = (undefined2)local_8;
    if (param_3 == 0) {
      thunk_FUN_0045b24d(*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) + 0x140,
                         *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) + 0x140,&local_18,&local_14);
      thunk_FUN_0045afb9(CONCAT22(extraout_var,(undefined2)local_8),local_18,local_14);
    }
    else {
      thunk_FUN_0046c3bc(s_IWEffList_004a00dc,0x1c01,(int)*(short *)(in_ECX + 0x72),0);
    }
  }
  return 1;
}
```

---

---

## FUN_0043c7bb — 0x43c7bb

- Classification : internal
- Corps : `0x43c7bb–0x43c949`
- État : pseudocode obtenu
- Evidence : `ev_2f1914840f251ab57dadcd88d1a6c7953970ed255671b1e523aebb9cd10142b8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043c7bb(void)

{
  int in_ECX;
  
  if (*(short *)(in_ECX + 0x74) < *(short *)(in_ECX + 0x70)) {
    if ((*(short *)(in_ECX + 0x76) < 1) || (*(int *)(in_ECX + 0x7c) != 0)) {
      if ((*(int *)(in_ECX + 0x7c) != 0) && (*(short *)(in_ECX + 0x76) == 0)) {
        thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x78),2,0,0);
        *(undefined4 *)(in_ECX + 0x7c) = 0;
      }
    }
    else {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x78),1,0,0);
      *(undefined4 *)(in_ECX + 0x7c) = 1;
    }
    if (((int)*(short *)(in_ECX + 0x76) <
         (int)*(short *)(in_ECX + 0x70) - (int)*(short *)(in_ECX + 0x74)) &&
       (*(int *)(in_ECX + 0x80) == 0)) {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x7a),1,0,0);
      *(undefined4 *)(in_ECX + 0x80) = 1;
    }
    else if ((*(int *)(in_ECX + 0x80) != 0) &&
            ((int)*(short *)(in_ECX + 0x70) - (int)*(short *)(in_ECX + 0x74) <=
             (int)*(short *)(in_ECX + 0x76))) {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x7a),2,0,0);
      *(undefined4 *)(in_ECX + 0x80) = 0;
    }
  }
  else {
    *(undefined2 *)(in_ECX + 0x76) = 0;
    if (*(int *)(in_ECX + 0x7c) != 0) {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x78),2,0,0);
      *(undefined4 *)(in_ECX + 0x7c) = 0;
    }
    if (*(int *)(in_ECX + 0x80) != 0) {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x7a),2,0,0);
      *(undefined4 *)(in_ECX + 0x80) = 0;
    }
  }
  return;
}
```

---

---

## FUN_0043c94a — 0x43c94a

- Classification : internal
- Corps : `0x43c94a–0x43cc62`
- État : pseudocode obtenu
- Evidence : `ev_c699d396c79efa6e626ce1e1684bd192bbfd20d295c4200fa091bf6dbaa25652`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x40174e` — `thunk_FUN_004109a6`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x402306` — `thunk_FUN_004106dd`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x4a00f0` — "C:\\float\\src\\iwdebug.cpp"
- `0x4a010c` — "[%d] %s (%d)"

### Pseudocode Ghidra

```c
void FUN_0043c94a(void)

{
  undefined4 uVar1;
  uint uVar2;
  int in_ECX;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int local_88 [4];
  int local_78;
  undefined4 local_74;
  int local_70;
  undefined *local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  undefined1 local_54 [80];
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    uVar1 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar1;
    if (DAT_004c2bac == 0) {
      thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
    }
    else {
      uVar8 = 0;
      uVar7 = 0;
      iVar3 = (int)*(short *)(in_ECX + 0x1e);
      uVar1 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar1,iVar3,uVar7,uVar8);
    }
    local_60 = thunk_FUN_0042de0d();
    if (local_60 == 0) {
      thunk_FUN_00414b64(s_C__float_src_iwdebug_cpp_004a00f0,0x220,&DAT_004a00e8);
    }
    local_68 = ((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) +
               *(short *)(in_ECX + 0x74) * -10) / 2;
    local_5c = 0;
    local_58 = (int)*(short *)(in_ECX + 0x70);
    if ((int)*(short *)(in_ECX + 0x76) + (int)*(short *)(in_ECX + 0x74) < local_58) {
      local_58 = (int)*(short *)(in_ECX + 0x76) + (int)*(short *)(in_ECX + 0x74);
    }
    for (local_64 = (int)*(short *)(in_ECX + 0x76); local_64 < local_58; local_64 = local_64 + 1) {
      local_6c = &DAT_005e8230 + local_64 * 0x48;
      uVar2 = thunk_FUN_0042dd0f(5);
      *(uint *)(local_60 + 8) = uVar2 & 0xff;
      if (*(short *)(in_ECX + 0x72) == local_64) {
        local_70 = local_5c * 10 + -3 +
                   ((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) +
                   *(short *)(in_ECX + 0x74) * -10) / 2;
        piVar5 = (int *)(in_ECX + 8);
        piVar6 = local_88;
        for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
          *piVar6 = *piVar5;
          piVar5 = piVar5 + 1;
          piVar6 = piVar6 + 1;
        }
        local_88[2] = *(int *)(in_ECX + 0x10) + local_70;
        local_78 = local_88[2] + 10;
        local_88[3] = local_88[3] + -0xd;
        uVar1 = thunk_FUN_004106dd(1,1);
        iVar4 = *(int *)(in_ECX + 0x10) - local_88[2];
        uVar8 = 0;
        iVar3 = (int)*(short *)(in_ECX + 0x1e);
        local_74 = uVar1;
        uVar7 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
        thunk_FUN_004109a6(local_88,uVar7,iVar3,uVar8,iVar4,uVar1);
      }
      FUN_00472ca0(local_54,s___d___s___d__004a010c,local_64,local_6c,
                   *(undefined4 *)(local_6c + 0x30));
      thunk_FUN_004289c0(in_ECX + 8,5,local_68,local_54);
      local_68 = local_68 + 10;
      local_5c = local_5c + 1;
    }
    uVar2 = thunk_FUN_0042dd0f(6);
    *(uint *)(local_60 + 8) = uVar2 & 0xff;
    thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x78),0xb,0,0);
    thunk_FUN_0046c371((int)*(short *)(in_ECX + 0x7a),0xb,0,0);
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,1);
  }
  return;
}
```

---

---

## FUN_0043cc63 — 0x43cc63

- Classification : internal
- Corps : `0x43cc63–0x43cc86`
- État : pseudocode obtenu
- Evidence : `ev_68d0ccefed2ccd0bffd02be09888e927d60f41af7f80cc6c21e4480f742663c3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a011c` — "FALSE"
- `0x4a0124` — "C:\\float\\src\\iwdebug.cpp"

### Pseudocode Ghidra

```c
void FUN_0043cc63(void)

{
  thunk_FUN_00414b64(s_C__float_src_iwdebug_cpp_004a0124,0x249,s_FALSE_004a011c);
  return;
}
```

---

---

## FUN_0043cc87 — 0x43cc87

- Classification : internal
- Corps : `0x43cc87–0x43cc93`
- État : pseudocode obtenu
- Evidence : `ev_28f4d400e1b05363ff7790bd0e3226c404d89a56d287a2aec2967092abbfe6b8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043cc87(void)

{
  return;
}
```

---

---

## FUN_0043d180 — 0x43d180

- Classification : internal
- Corps : `0x43d180–0x43d1ad`
- État : pseudocode obtenu
- Evidence : `ev_1a3849e42ec925288be0bb107fa25ff2db431b2b9e12d3fc42902fc823b74e36`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402419` — `thunk_FUN_0043b964`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043d180(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0043b964();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_0043d1c0 — 0x43d1c0

- Classification : internal
- Corps : `0x43d1c0–0x43d1ed`
- État : pseudocode obtenu
- Evidence : `ev_5f07c511e104aa007b91a01bb3b21afba26275ec9c779a1fc182dd3f0c7b49de`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4019f6` — `thunk_FUN_0043c34b`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043d1c0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0043c34b();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_0043d200 — 0x43d200

- Classification : internal
- Corps : `0x43d200–0x43d253`
- État : pseudocode obtenu
- Evidence : `ev_0515b957b9795cd10b8b7b21d9a6d4a49182397895bf82c224c0d75cb69f7b7a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4015e6` — `thunk_FUN_0043d270`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0043d200(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004917b9;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004943e0;
  thunk_FUN_0043d270();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

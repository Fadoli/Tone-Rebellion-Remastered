# 0013_batch_0009 — détails (2/3)

## FUN_0043fbd4 — 0x43fbd4

- Classification : internal
- Corps : `0x43fbd4–0x43fbef`
- État : pseudocode obtenu
- Evidence : `ev_4a906a54efedd66d588a952155902fde54840f02ee6ce49d989f6482587c50ea`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043fbd4(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494440;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_0043fbf0 — 0x43fbf0

- Classification : internal
- Corps : `0x43fbf0–0x43fc0d`
- État : pseudocode obtenu
- Evidence : `ev_8125634827316c044100df1a4d97f624e908e9936c95d422f75964ee41ac7741`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043fbf0(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x70) = 0xffffffff;
  *(undefined2 *)(in_ECX + 0x74) = 0;
  return;
}
```

---

---

## FUN_0043fc0e — 0x43fc0e

- Classification : internal
- Corps : `0x43fc0e–0x43fcec`
- État : pseudocode obtenu
- Evidence : `ev_d329e6290ce3e15bc75484e75d02d89b9fa2b5290f5c6d7240eb739e70f59192`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`
- `0x4023d3` — `thunk_FUN_0046b928`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043fc0e(short param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int in_ECX;
  
  if (param_1 < 0x350c) {
    if (param_1 == 0x350b) {
      *(undefined4 *)(in_ECX + 0x78) = param_2;
      *(undefined4 *)(in_ECX + 0x34) = 1;
      return 1;
    }
    if (param_1 == 1) {
      *(undefined2 *)(in_ECX + 0x76) = 0xffff;
      thunk_FUN_0046b928(*(undefined4 *)(in_ECX + 4),0x350c,0,0,0);
    }
    else if (param_1 == 2) {
      DAT_0049e9c8 = 0xfffe;
    }
  }
  else if (param_1 == 0x350c) {
    if ((DAT_0062c6bc != *(short *)(in_ECX + 0x76)) && (*(int *)(in_ECX + 0x3c) != 0)) {
      *(undefined2 *)(in_ECX + 0x76) = (undefined2)DAT_0062c6bc;
      *(undefined4 *)(in_ECX + 0x34) = 1;
    }
    return 1;
  }
  uVar1 = thunk_FUN_004293c6(param_1,param_2,param_3);
  return uVar1;
}
```

---

---

## FUN_0043fced — 0x43fced

- Classification : internal
- Corps : `0x43fced–0x43ffc1`
- État : pseudocode obtenu
- Evidence : `ev_d4a8523612cbf3c89e1811ec062b9abc58733c8871442ca22403ffa2c55121d9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x401636` — `thunk_FUN_0045d9c1`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x40224d` — `thunk_FUN_00450070`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- `0x4a04dc` — "magctone"
- `0x4a04e8` — "shape"
- `0x4a04f0` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0508` — "tonecrys"
- `0x4a0514` — "shape"
- `0x4a051c` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
void FUN_0043fced(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int in_ECX;
  int iVar4;
  undefined2 extraout_var;
  undefined4 uVar5;
  undefined4 uVar6;
  int local_18;
  undefined2 local_14;
  int local_c;
  int local_8;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    uVar1 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar1;
    if (DAT_004c2bac == 0) {
      thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
    }
    else {
      uVar6 = 0;
      uVar5 = 0;
      iVar4 = (int)*(short *)(in_ECX + 0x1e);
      uVar1 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar1,iVar4,uVar5,uVar6);
    }
    local_8 = -1;
    if (*(int *)(in_ECX + 0x70) != -1) {
      for (local_c = 0; local_c < *(short *)(in_ECX + 0x74); local_c = local_c + 1) {
        thunk_FUN_0046c371(*(int *)(in_ECX + 0x70) + local_c,0xb,0,0);
        if (*(int *)(in_ECX + 0x70) + local_c == DAT_0062c6bc) {
          local_8 = local_c;
        }
      }
    }
    if ((((local_8 != -1) &&
         (iVar4 = *(int *)(&DAT_0062a784 + DAT_0062c6bc * 0xc),
         0x2e < *(int *)(*(int *)(in_ECX + 0x78) + 0x10))) &&
        (*(int *)(*(int *)(in_ECX + 0x78) + 0x10) < 0x31)) &&
       ((0x14 < *(int *)(iVar4 + 100) && (*(int *)(iVar4 + 100) < 0x1d)))) {
      iVar4 = thunk_FUN_00450070(*(undefined4 *)(in_ECX + 0x78),*(undefined4 *)(iVar4 + 100));
      iVar2 = thunk_FUN_0040ec89(s_magctone_004a04dc,1);
      if (iVar2 == 0) {
        thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a04f0,0xb0,s_shape_004a04e8);
      }
      iVar3 = thunk_FUN_00450385();
      if (iVar3 == 0) {
        local_18 = (int)*(short *)(&DAT_006188e2 + iVar4 * 0x2c);
      }
      else {
        local_14 = (undefined2)iVar4;
        local_18 = thunk_FUN_0045d9c1(CONCAT22(extraout_var,local_14));
      }
      local_18 = local_18 + -1;
      if (local_18 < 0) {
        local_18 = 0;
      }
      if (0x31 < local_18) {
        local_18 = 0x31;
      }
      iVar3 = *(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc);
      thunk_FUN_00404770(in_ECX + 8,iVar2,local_18,((int)(iVar3 + (iVar3 >> 0x1f & 3U)) >> 2) + -5,
                         0x1a);
      iVar2 = thunk_FUN_0040ec89(s_tonecrys_004a0508,1);
      if (iVar2 == 0) {
        uVar1 = thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a051c,0xbf,s_shape_004a0514);
      }
      else {
        uVar1 = 0;
      }
      local_18 = *(short *)(&DAT_006188e4 + iVar4 * 0x2c) + -1;
      if (local_18 < 0) {
        local_18 = 0;
      }
      if (0x31 < local_18) {
        local_18 = 0x31;
      }
      iVar4 = *(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc);
      thunk_FUN_00404770(in_ECX + 8,iVar2,local_18,((int)(iVar4 + (iVar4 >> 0x1f & 3U)) >> 2) + -5,
                         0x37,uVar1);
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,3);
    *(undefined4 *)(in_ECX + 0x34) = 0;
  }
  return;
}
```

---

---

## FUN_0043ffc2 — 0x43ffc2

- Classification : internal
- Corps : `0x43ffc2–0x440015`
- État : pseudocode obtenu
- Evidence : `ev_83d18a84dbed485487456ee880bac7982a004e87d4e06cfef12421ab57f1f33e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401492` — `thunk_FUN_00440032`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0043ffc2(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049182c;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494458;
  thunk_FUN_00440032();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_00440016 — 0x440016

- Classification : internal
- Corps : `0x440016–0x440031`
- État : pseudocode obtenu
- Evidence : `ev_c4d77d59d28c41174ded6080eda34637e30decd6ef2915c062a112b773f81f3f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00440016(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494458;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_00440032 — 0x440032

- Classification : internal
- Corps : `0x440032–0x44003c`
- État : pseudocode obtenu
- Evidence : `ev_792fd1e46663ebafd0e5d29824971abeaec0da90ef49abbf59605a181e457616`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00440032(void)

{
  return;
}
```

---

---

## FUN_0044003d — 0x44003d

- Classification : internal
- Corps : `0x44003d–0x440325`
- État : pseudocode obtenu
- Evidence : `ev_9f854760de65b70cdb336d193609191bbf2d8bbde63868ca8f8757721ebda9ca`
- Note de flux : le clic sans slot envoie `0x32` si `+0x18 != -1`; une route vers `FUN_0042fa0f` n'est démontrée que sous les gardes dispatcher mode 0 et callback actif slot 3. Ces états ne sont pas reliés au clic. Evidence `ev_dfa9260d630c5590f535d54281a0b8f2c2767e3ca99d4a00ffdd596b3104b7eb`.
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401bf4` — `thunk_FUN_0042970c`
- `0x402504` — `thunk_FUN_00440451`
- `0x472c6c` — `__ftol`

### Chaînes référencées

- `0x4a0534` — "IWMove"
- `0x4a053c` — "IWHallMove"
- `0x4a0548` — "IWMove"
- `0x4a0550` — "IWHallMove"
- `0x4a055c` — "IWHallMove"
- `0x4a0568` — "IWMove"

### Pseudocode Ghidra

```c
undefined4 FUN_0044003d(short param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined2 extraout_var;
  undefined4 uVar2;
  int in_ECX;
  undefined4 uVar3;
  undefined *local_10;
  
  iVar1 = (int)param_1;
  if (iVar1 < 0x350c) {
    if (iVar1 == 0x350b) {
      thunk_FUN_0046c3bc(s_IWMove_004a0548,2,0,0);
      thunk_FUN_0046c3bc(s_IWHallMove_004a0550,2,0,0);
      *(undefined4 *)(in_ECX + 0x70) = param_2;
      local_10 = *(undefined **)(in_ECX + 0x70);
      if (*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) != 0) {
        local_10 = &DAT_005ec640 +
                   *(short *)(DAT_0049f538 * 0x14a0 + 0x61a574) * 0x60 +
                   *(short *)(DAT_0049f538 * 0x14a0 + 0x61a572) * 0x29e8;
      }
      if ((((local_10 != (undefined *)0x0) && (*(int *)(local_10 + 0x14) == DAT_0049f538)) &&
          (*(int *)(local_10 + 0x10) != 0)) && (*(int *)(local_10 + 0x10) != 1)) {
        if (*(int *)(local_10 + 0x10) == 0x2a) {
          thunk_FUN_0046c3bc(s_IWHallMove_004a055c,1,0,0);
        }
        else if (*(int *)(local_10 + 0x10) != 0x28) {
          thunk_FUN_0046c3bc(s_IWMove_004a0568,1,0,0);
        }
      }
      *(undefined2 *)(in_ECX + 0x76) = 0xffff;
      return 1;
    }
    switch(iVar1) {
    case 1:
      *(undefined2 *)(in_ECX + 0x74) = 0xffff;
      break;
    case 2:
      thunk_FUN_0046c3bc(s_IWMove_004a0534,2,0,0);
      thunk_FUN_0046c3bc(s_IWHallMove_004a053c,2,0,0);
      uVar2 = thunk_FUN_004293c6(CONCAT22(extraout_var,param_1),param_2,param_3);
      return uVar2;
    case 6:
      iVar1 = thunk_FUN_00429f3a();
      if ((iVar1 != 0) && (*(int *)(in_ECX + 0x70) != 0)) {
        thunk_FUN_00440451(param_2,param_3);
        if (*(short *)(in_ECX + 0x76) == -1) {
          if (*(short *)(*(int *)(in_ECX + 0x70) + 0x18) != -1) {
            *(undefined4 *)(DAT_005dc64c + 0x170) = 0;
            thunk_FUN_0042970c(0x32,0,0);
          }
        }
        else {
          thunk_FUN_0042970c(0x3f,(int)*(short *)(in_ECX + 0x78 + *(short *)(in_ECX + 0x76) * 2),0);
        }
      }
      break;
    case 7:
      iVar1 = thunk_FUN_00429f3a();
      if ((iVar1 != 0) && (*(int *)(in_ECX + 0x70) != 0)) {
        if (*(short *)(*(int *)(in_ECX + 0x70) + 8) != DAT_0049f53c) {
          thunk_FUN_0042970c(0x4d,(int)*(short *)(*(int *)(in_ECX + 0x70) + 8),0);
        }
        uVar3 = 1;
        uVar2 = __ftol(1);
        thunk_FUN_0042970c(0x3d,uVar2,uVar3);
      }
      break;
    case 10:
      thunk_FUN_00440451(param_2,param_3);
    }
  }
  else if (iVar1 == 0x350d) {
    *(undefined2 *)(in_ECX + 0x74) = (undefined2)param_2;
    return 1;
  }
  uVar2 = thunk_FUN_004293c6(param_1,param_2,param_3);
  return uVar2;
}
```

---

---

## FUN_0044034e — 0x44034e

- Classification : internal
- Corps : `0x44034e–0x440450`
- État : pseudocode obtenu
- Evidence : `ev_9ef02eb58bdf8a0866dbfbc4fddb24eb95a3c0322ffbf1e75b23988cc0c84e8d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4019a1` — `thunk_FUN_00450385`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x40208b` — `thunk_FUN_0045d7e8`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a0570` — "slot<6"
- `0x4a0578` — "C:\\float\\src\\Iwloc.cpp"

### Pseudocode Ghidra

```c
void FUN_0044034e(void)

{
  int iVar1;
  int in_ECX;
  int local_14;
  int local_c;
  int local_8;
  
  _memset((void *)(in_ECX + 0x78),-1,0xc);
  if (((*(int *)(in_ECX + 0x70) != 0) && (*(int *)(*(int *)(in_ECX + 0x70) + 4) == 0)) &&
     (iVar1 = thunk_FUN_00450385(), iVar1 != 0)) {
    for (local_8 = 0; local_8 < 3; local_8 = local_8 + 1) {
      local_14 = 0;
      if (local_8 == 1) {
        local_14 = 3;
      }
      else if (local_8 == 2) {
        local_14 = 5;
      }
      local_c = -1;
      while (local_c = thunk_FUN_0045d7e8(local_c,local_8), local_c != -1) {
        if (5 < local_14) {
          thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0578,0x162,s_slot<6_004a0570);
        }
        *(undefined2 *)(in_ECX + 0x78 + local_14 * 2) = *(undefined2 *)(iVar1 + 4 + local_c * 2);
        local_14 = local_14 + 1;
      }
    }
  }
  return;
}
```

---

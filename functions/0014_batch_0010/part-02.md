# 0014_batch_0010 — détails (2/6)

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

## FUN_0044338b — 0x44338b

- Classification : internal
- Corps : `0x44338b–0x443d71`
- État : pseudocode obtenu
- Evidence : `ev_995b04cc8ed7dc755e49489cf97d7e86bafd66996c26c5275f6e61b4af808b7f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x40116d` — `thunk_FUN_0041e4d9`
- `0x4011ea` — `thunk_FUN_0041fde6`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x4018cf` — `thunk_FUN_0041ff2e`
- `0x401933` — `thunk_FUN_00464242`
- `0x401a87` — `thunk_FUN_0042704b`
- `0x401ab4` — `thunk_FUN_00425296`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401bf4` — `thunk_FUN_0042970c`
- `0x401dac` — `thunk_FUN_004207f2`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x402144` — `thunk_FUN_00420f28`
- `0x40222a` — `thunk_FUN_00429e69`
- `0x402234` — `thunk_FUN_0042892d`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x4023bf` — `thunk_FUN_0045c3bb`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49cfc8` — "xTark"
- `0x49d0b8` — "FA_Nothing"
- `0x49d0b8` — "FA_Nothing"
- `0x4a0c80` — "BLDNAME"
- `0x4a0c90` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0cb0` — "C:\\float\\src\\Iwloc.cpp"
- `0x4a0cc8` — "LEVEL"
- `0x4a0cd0` — "%s %d"
- `0x4a0cdc` — "%s %d/%d"
- `0x4a0ce8` — "%s %d"
- `0x4a0cf0` — "%s %d"
- `0x4a0cf8` — "CHARGE"
- `0x4a0d00` — "%s %d/%d"
- `0x4a0d0c` — "WORKER"
- `0x4a0d14` — "AWAKE"
- `0x4a0d1c` — "%s %s"
- `0x4a0d28` — "LEVEL"
- `0x4a0d30` — "%s %d"
- `0x4a0d40` — "%s %d/%d"
- `0x4a0d4c` — "STRENGTH"
- `0x4a0d58` — "%s %d"
- `0x4a0d60` — "object=%d"
- `0x4a4a50` — "xSpores"

### Pseudocode Ghidra

```c
void FUN_0044338b(void)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int in_ECX;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 local_120;
  undefined1 local_110 [32];
  undefined4 local_f0;
  int local_ec;
  int local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  char *local_dc;
  undefined4 local_d8;
  int local_d4;
  int local_d0;
  int local_cc;
  int local_c8;
  int local_c4;
  int local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  int local_a4;
  undefined4 local_a0;
  undefined1 local_9c [32];
  int local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70 [7];
  uint local_54;
  int local_24;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049190c;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (((*(int *)(in_ECX + 0x3c) != 0) && (*(int *)(in_ECX + 0x70) != 0)) &&
     (**(int **)(in_ECX + 0x70) != -1)) {
    if (((*(uint *)(*(int *)(in_ECX + 0x70) + 0x1c) & 8) == 0) ||
       (iVar5 = *(int *)(in_ECX + 0x70), iVar2 = thunk_FUN_00425296(8),
       *(int *)(iVar5 + 0x24) < iVar2)) {
      local_74 = thunk_FUN_0042de0d();
      uVar3 = thunk_FUN_0042d28f();
      *(undefined4 *)(in_ECX + 8) = uVar3;
      if (DAT_004c2bac == 0) {
        thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
      }
      else {
        uVar9 = 0;
        uVar8 = 0;
        iVar5 = (int)*(short *)(in_ECX + 0x1e);
        uVar3 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
        thunk_FUN_00404770(in_ECX + 8,uVar3,iVar5,uVar8,uVar9);
      }
      puVar6 = *(undefined4 **)(in_ECX + 0x70);
      puVar7 = local_70;
      for (iVar5 = 0x13; iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar7 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar7 = puVar7 + 1;
      }
      local_8 = 0;
      local_54 = local_54 | 2;
      local_78 = DAT_005c37f4;
      DAT_005c37fc = 1;
      DAT_005c37f8 = 1;
      DAT_005c37f4 = 1;
      thunk_FUN_0042704b(in_ECX + 8,local_70,
                         (*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) + -0x32,
                         (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) / 2 + 5,1,8,0x10000,0);
      DAT_005c37fc = local_78;
      DAT_005c37f8 = local_78;
      DAT_005c37f4 = local_78;
      local_20 = 3;
      local_1c = 4;
      local_7c = thunk_FUN_004207f2();
      if (local_7c != 0) {
        local_b4 = thunk_FUN_0045c3bb();
        if (local_b4 != 0) {
          local_c4 = thunk_FUN_00429ebe(s_BLDNAME_004a0c80,&local_c0);
          if (local_c4 == 0) {
            thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0c90,0x69e,&DAT_004a0c88);
          }
          local_b8 = *(int *)(local_b4 + 0x10) + -0x25 + *(int *)(local_b4 + 0x14) * 0x10;
          local_24 = thunk_FUN_00429e69(local_c0 + local_b8,1);
          if (local_24 == 0) {
            thunk_FUN_00414b64(s_C__float_src_Iwloc_cpp_004a0cb0,0x6a1,&DAT_004a0ca8);
          }
          iVar5 = *(int *)(in_ECX + 0x14);
          iVar2 = *(int *)(in_ECX + 0xc);
          iVar4 = thunk_FUN_0042892d(local_24,0xffffffff,0xffffffff);
          local_bc = ((iVar5 - iVar2) - iVar4) / 2;
          thunk_FUN_004289c0(in_ECX + 8,local_bc,local_20,local_24);
        }
        local_20 = local_20 + 0xf;
        local_a8 = thunk_FUN_00429ebe(s_LEVEL_004a0cc8,0);
        sVar1 = thunk_FUN_0041ff2e();
        FUN_00472ca0(local_9c,s__s__d_004a0cd0,local_a8,sVar1 + 1);
        thunk_FUN_004289c0(in_ECX + 8,local_1c,local_20,local_9c);
        local_20 = local_20 + 10;
        sVar1 = thunk_FUN_0041ff2e();
        local_a4 = (int)sVar1;
        local_b0 = thunk_FUN_00429ebe(&DAT_004a0cd8,0);
        if (local_a4 < 2) {
          local_cc = DAT_004bf11c;
          local_c8 = 4 - DAT_004bf11c;
          iVar5 = local_c8 *
                  *(short *)(&DAT_004a424a +
                            local_a4 * 2 + *(int *)(*(int *)(in_ECX + 0x70) + 4) * 6) +
                  DAT_004bf11c *
                  *(short *)(&DAT_004a4282 +
                            local_a4 * 2 + *(int *)(*(int *)(in_ECX + 0x70) + 4) * 6);
          local_d0 = (int)(iVar5 + (iVar5 >> 0x1f & 3U)) >> 2;
          if (local_d0 < 1) {
            FUN_00472ca0(local_9c,s__s__d_004a0ce8,local_b0,
                         (int)*(short *)(*(int *)(in_ECX + 0x70) + 8));
          }
          else {
            FUN_00472ca0(local_9c,s__s__d__d_004a0cdc,local_b0,
                         (int)*(short *)(*(int *)(in_ECX + 0x70) + 8),local_d0);
          }
        }
        else {
          FUN_00472ca0(local_9c,s__s__d_004a0cf0,local_b0,
                       (int)*(short *)(*(int *)(in_ECX + 0x70) + 8));
        }
        thunk_FUN_004289c0(in_ECX + 8,local_1c,local_20,local_9c);
        local_20 = local_20 + 10;
        local_ac = thunk_FUN_00429ebe(s_CHARGE_004a0cf8,0);
        iVar5 = thunk_FUN_00464242(**(undefined4 **)(in_ECX + 0x70),
                                   *(undefined4 *)(*(int *)(in_ECX + 0x70) + 4));
        FUN_00472ca0(local_9c,s__s__d__d_004a0d00,local_ac,
                     (int)*(short *)(*(int *)(in_ECX + 0x70) + 0x22),(int)*(short *)(iVar5 + 8));
        thunk_FUN_004289c0(in_ECX + 8,local_1c,local_20,local_9c);
        local_20 = local_20 + 10;
      }
      if (local_7c == 0) {
        if (**(int **)(in_ECX + 0x70) == 4) {
          local_ec = *(int *)(*(int *)(in_ECX + 0x70) + 4) + -9;
          sVar1 = thunk_FUN_0041ff2e();
          local_e8 = (int)sVar1;
          FUN_00472ca0(local_9c,&DAT_004a0d24,s_xSpores_004a4a50 + (local_e8 + local_ec * 2) * 0x10)
          ;
        }
        else {
          local_dc = s_xTark_0049cfc8 + **(int **)(in_ECX + 0x70) * 0xc;
          local_e0 = thunk_FUN_00429ebe(s_WORKER_004a0d0c,0);
          local_d8 = thunk_FUN_00429ebe(s_AWAKE_004a0d14,0);
          local_120 = local_d8;
          if (*(int *)(*(int *)(in_ECX + 0x70) + 4) == 0) {
            local_120 = local_e0;
          }
          local_e4 = local_120;
          FUN_00472ca0(local_9c,s__s__s_004a0d1c,local_dc,local_120);
        }
        iVar5 = *(int *)(in_ECX + 0x14);
        iVar2 = *(int *)(in_ECX + 0xc);
        iVar4 = thunk_FUN_0042892d(local_9c,0xffffffff,0xffffffff);
        local_d4 = ((iVar5 - iVar2) - iVar4) / 2;
        thunk_FUN_004289c0(in_ECX + 8,local_d4,local_20,local_9c);
        local_20 = local_20 + 0x14;
      }
      if ((local_7c == 0) && (**(int **)(in_ECX + 0x70) == 4)) {
        local_f0 = thunk_FUN_00429ebe(s_LEVEL_004a0d28,0);
        sVar1 = thunk_FUN_0041ff2e();
        FUN_00472ca0(local_9c,s__s__d_004a0d30,local_f0,sVar1 + 1);
        thunk_FUN_004289c0(in_ECX + 8,local_1c,local_20,local_9c);
        local_20 = local_20 + 10;
      }
      local_14 = (int)*(short *)(*(int *)(in_ECX + 0x70) + 0x20);
      if (local_14 < 0) {
        local_14 = 0;
      }
      local_18 = thunk_FUN_00429ebe(&DAT_004a0d38,0);
      sVar1 = thunk_FUN_00420f28();
      FUN_00472ca0(local_9c,s__s__d__d_004a0d40,local_18,local_14,(int)sVar1);
      thunk_FUN_004289c0(in_ECX + 8,local_1c,local_20,local_9c);
      local_20 = local_20 + 10;
      local_a0 = thunk_FUN_00429ebe(s_STRENGTH_004a0d4c,0);
      uVar3 = thunk_FUN_0041fde6();
      FUN_00472ca0(local_9c,s__s__d_004a0d58,local_a0,uVar3);
      thunk_FUN_004289c0(in_ECX + 8,local_1c,local_20,local_9c);
      local_20 = local_20 + 10;
      if (DAT_004c2bb0 != 0) {
        thunk_FUN_004289c0(in_ECX + 8,(*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) + -0x50,
                           0x14,s_FA_Nothing_0049d0b8 +
                                *(int *)(*(int *)(in_ECX + 0x70) + 0x3c) * 0x10);
        thunk_FUN_004289c0(in_ECX + 8,(*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) + -0x50,
                           0x1e,s_FA_Nothing_0049d0b8 +
                                *(int *)(*(int *)(in_ECX + 0x70) + 0x2c) * 0x10);
        FUN_00472ca0(local_110,s_object__d_004a0d60,(int)*(short *)(*(int *)(in_ECX + 0x70) + 0x44))
        ;
        thunk_FUN_004289c0(in_ECX + 8,(*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) + -0x50,
                           0x28,local_110);
      }
      thunk_FUN_0042d38a();
      thunk_FUN_0042d87c(in_ECX + 8,1);
      local_8 = 0xffffffff;
      thunk_FUN_0041e4d9();
    }
    else {
      *(undefined4 *)(DAT_005dc64c + 0x170) = 0;
      if ((**(int **)(in_ECX + 0x70) == DAT_0049f538) &&
         (*(short *)(*(int *)(in_ECX + 0x70) + 0xc) != -1)) {
        thunk_FUN_0042970c(0x32,0,0);
      }
      else {
        thunk_FUN_0042970c(0x44,0,0);
      }
      *(undefined4 *)(in_ECX + 0x70) = 0;
    }
  }
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

## FUN_00444e10 — 0x444e10

- Classification : internal
- Corps : `0x444e10–0x444e3d`
- État : pseudocode obtenu
- Evidence : `ev_c4f6e939ed36ec38d04fb262f7e44b7a7e9e4fdcf119f3bdc572bf1d0ea270f0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40221b` — `thunk_FUN_0043fbd4`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00444e10(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0043fbd4();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_00444e50 — 0x444e50

- Classification : internal
- Corps : `0x444e50–0x444e7d`
- État : pseudocode obtenu
- Evidence : `ev_31deb6e6ed5acbb5ee4444f04d16755edd32a04d173891b2e6194d7db9b2d96e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401feb` — `thunk_FUN_00440016`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00444e50(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00440016();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_00444e90 — 0x444e90

- Classification : internal
- Corps : `0x444e90–0x444ebd`
- État : pseudocode obtenu
- Evidence : `ev_57b7979954a81a1e14dc0a7dc60c598e0db7db23164651493d4df29688832ef7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4016c2` — `thunk_FUN_00441d03`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00444e90(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00441d03();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_00444ed0 — 0x444ed0

- Classification : internal
- Corps : `0x444ed0–0x444efd`
- État : pseudocode obtenu
- Evidence : `ev_71445e65a42e7a2d32e40d941e0cbe137030140f9883892e74c5ebf7f00be290`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4015ff` — `thunk_FUN_0044213f`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00444ed0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0044213f();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_00444f10 — 0x444f10

- Classification : internal
- Corps : `0x444f10–0x444f3d`
- État : pseudocode obtenu
- Evidence : `ev_21a80478f577a7efc4389b3482e3d261710da82f630fb26b77f8e9533bad3ce5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401be5` — `thunk_FUN_0044243a`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00444f10(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0044243a();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_00444f50 — 0x444f50

- Classification : internal
- Corps : `0x444f50–0x444f7d`
- État : pseudocode obtenu
- Evidence : `ev_07a3b762b3af117c30d9bd2ee74b8871c91d91da5818e0576abed3610930c679`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4019f1` — `thunk_FUN_004425f5`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00444f50(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_004425f5();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_00444f90 — 0x444f90

- Classification : internal
- Corps : `0x444f90–0x444fbd`
- État : pseudocode obtenu
- Evidence : `ev_856887643b8c1e07fcadc7af8713deb43d60ef75d821a48b45e0ec3c4a5e362c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401e97` — `thunk_FUN_00442904`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00444f90(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00442904();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_00444fd0 — 0x444fd0

- Classification : internal
- Corps : `0x444fd0–0x444ffd`
- État : pseudocode obtenu
- Evidence : `ev_f9cf150784fdbe272fbcb939806ba99ba1e44a4e856a4b8ff98894bf6eb193d5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b5e` — `thunk_FUN_00442bf0`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00444fd0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00442bf0();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_00445010 — 0x445010

- Classification : internal
- Corps : `0x445010–0x44503d`
- État : pseudocode obtenu
- Evidence : `ev_bb4e980a70168ee049b39fe5161e1f193d5fe41682b8abc59ca3e61306e9f2cb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4015b9` — `thunk_FUN_00442ee2`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00445010(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00442ee2();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_00445050 — 0x445050

- Classification : internal
- Corps : `0x445050–0x44507d`
- État : pseudocode obtenu
- Evidence : `ev_7d6210ea729ebc017b416bc9ff1c422e5d7496764de23d42489d39ea015da5e3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40148d` — `thunk_FUN_004432ec`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00445050(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_004432ec();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_00445090 — 0x445090

- Classification : internal
- Corps : `0x445090–0x4450e3`
- État : pseudocode obtenu
- Evidence : `ev_5bb3f65ed53a7886004b4a015205097bdf7fc4313f52f894e2fb83442011467d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018a2` — `thunk_FUN_00445100`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00445090(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491969;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494560;
  thunk_FUN_00445100();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_004450e4 — 0x4450e4

- Classification : internal
- Corps : `0x4450e4–0x4450ff`
- État : pseudocode obtenu
- Evidence : `ev_9e80933d87d04d925be0728bef6e5d76167014c4d6eb8c6d837214512870147c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004450e4(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494560;
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_00445100 — 0x445100

- Classification : internal
- Corps : `0x445100–0x445144`
- État : pseudocode obtenu
- Evidence : `ev_ccfb02e7bf9118cdbd84051052a6968be58cf4f0f224e0614dea2832f5d450ea`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00445100(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0xf4) = 0;
  *(undefined2 *)(in_ECX + 0xf0) = 0;
  DAT_005e16ec = 9999;
  *(undefined2 *)(in_ECX + 0xfc) = 0xffff;
  *(undefined2 *)(in_ECX + 0xfe) = 0xffff;
  return;
}
```

---

## FUN_00445145 — 0x445145

- Classification : internal
- Corps : `0x445145–0x4455d0`
- État : pseudocode obtenu
- Evidence : `ev_7f2318bb02feca67ff2fdbff8c0b8670431c3b109d5eedbda03b58235ff29ab0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401569` — `thunk_FUN_0046c558`
- `0x40171c` — `thunk_FUN_004455d1`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401e2e` — `thunk_FUN_00445739`
- `0x40211c` — `thunk_FUN_0044590d`
- `0x4021c6` — `thunk_FUN_0046ba3b`
- `0x4023d3` — `thunk_FUN_0046b928`

### Chaînes référencées

- `0x4a0f30` — "scrollup"
- `0x4a0f3c` — "scrolldn"
- `0x4a0f48` — "scrollup"
- `0x4a0f54` — "scrolldn"
- `0x4a0f60` — "IWTaskOptions"
- `0x4a0f70` — "IWTaskInfo"

### Pseudocode Ghidra

```c
undefined4 FUN_00445145(short param_1,int param_2,int param_3)

{
  short sVar1;
  bool bVar2;
  undefined4 uVar3;
  int in_ECX;
  int local_c;
  
  bVar2 = false;
  if (param_1 < 7) {
    if (param_1 == 6) {
      if ((((*(int *)(in_ECX + 0xc) < param_2) && (param_2 < *(int *)(in_ECX + 0x14) + -0xd)) &&
          (*(int *)(in_ECX + 0x10) < param_3)) && (param_3 < *(int *)(in_ECX + 0x18))) {
        if ((DAT_0062c6bc == *(short *)(in_ECX + 0xfc)) ||
           (DAT_0062c6bc == *(short *)(in_ECX + 0xfe))) {
          return 0;
        }
        thunk_FUN_0044590d(param_2,param_3);
        bVar2 = true;
      }
    }
    else if (param_1 == 1) {
      thunk_FUN_0046b928(*(undefined4 *)(in_ECX + 4),5000,0,0,0);
      *(short *)(in_ECX + 0xf8) = (short)((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) / 0xd)
      ;
      *(undefined2 *)(in_ECX + 0xfa) = 0;
      if ((*(short *)(in_ECX + 0xfc) == -1) || (*(short *)(in_ECX + 0xfe) == -1)) {
        thunk_FUN_0046c558(s_scrollup_004a0f30,3,in_ECX + 0xfc);
        thunk_FUN_0046c558(s_scrolldn_004a0f3c,3,in_ECX + 0xfe);
      }
    }
    else if (param_1 == 2) {
      DAT_005e16ec = 9999;
      thunk_FUN_0046ba3b(*(undefined4 *)(in_ECX + 4),0xffffffff);
      if ((*(short *)(in_ECX + 0xfc) != -1) || (*(short *)(in_ECX + 0xfe) == -1)) {
        thunk_FUN_0046c558(s_scrollup_004a0f48,3,in_ECX + 0xfc);
        thunk_FUN_0046c558(s_scrolldn_004a0f54,3,in_ECX + 0xfe);
      }
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0xfc),2,0,0);
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0xfe),2,0,0);
      *(undefined4 *)(in_ECX + 0x100) = 0;
      *(undefined4 *)(in_ECX + 0x104) = 0;
    }
  }
  else if (param_1 < 0x1771) {
    if (param_1 == 6000) {
      sVar1 = *(short *)(in_ECX + 0xfa);
      *(short *)(in_ECX + 0xfa) = *(short *)(in_ECX + 0xfa) + -1;
      if (*(short *)(in_ECX + 0xfa) < 0) {
        *(undefined2 *)(in_ECX + 0xfa) = 0;
      }
      if (sVar1 != *(short *)(in_ECX + 0xfa)) {
        thunk_FUN_00445739();
      }
      bVar2 = true;
    }
    else if (param_1 == 4999) {
      if ((&DAT_006183bc)[param_2 * 5] != 0) {
        *(undefined4 **)(in_ECX + 0xf4) = &DAT_006183bc + param_2 * 5;
        thunk_FUN_0046c3bc(s_IWTaskOptions_004a0f60,0x13ba,*(undefined4 *)(in_ECX + 0xf4),0);
        thunk_FUN_0046c3bc(s_IWTaskInfo_004a0f70,0x13ba,*(undefined4 *)(in_ECX + 0xf4),0);
        if (*(short *)(in_ECX + 0xf8) < *(short *)(in_ECX + 0xf0)) {
          for (local_c = 0; local_c < *(short *)(in_ECX + 0xf0); local_c = local_c + 1) {
            if (*(int *)(in_ECX + 0x70 + local_c * 4) == *(int *)(in_ECX + 0xf4)) {
              if ((int)*(short *)(in_ECX + 0xf8) < local_c - *(short *)(in_ECX + 0xfa)) {
                *(undefined2 *)(in_ECX + 0xfa) = (undefined2)local_c;
                thunk_FUN_00445739();
              }
              break;
            }
          }
        }
      }
    }
    else if (param_1 == 5000) {
      thunk_FUN_004455d1();
      bVar2 = true;
    }
  }
  else if (param_1 == 0x1771) {
    sVar1 = *(short *)(in_ECX + 0xfa);
    if (((int)*(short *)(in_ECX + 0xf0) != (int)*(short *)(in_ECX + 0xf8) &&
         -1 < (int)*(short *)(in_ECX + 0xf0) - (int)*(short *)(in_ECX + 0xf8)) &&
       (*(short *)(in_ECX + 0xfa) = *(short *)(in_ECX + 0xfa) + 1,
       (int)*(short *)(in_ECX + 0xf0) - (int)*(short *)(in_ECX + 0xf8) <
       (int)*(short *)(in_ECX + 0xfa))) {
      *(short *)(in_ECX + 0xfa) = *(short *)(in_ECX + 0xf0) - *(short *)(in_ECX + 0xf8);
    }
    if (sVar1 != *(short *)(in_ECX + 0xfa)) {
      thunk_FUN_00445739();
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

## FUN_004455d1 — 0x4455d1

- Classification : internal
- Corps : `0x4455d1–0x445738`
- État : pseudocode obtenu
- Evidence : `ev_bc320115f0f140331cab5bd3c6af1bb19d2505748d9aa0d0e1ae63d7addc020b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401e2e` — `thunk_FUN_00445739`

### Chaînes référencées

- `0x4a0f7c` — "IWTaskOptions"
- `0x4a0f8c` — "IWTaskInfo"

### Pseudocode Ghidra

```c
void FUN_004455d1(void)

{
  int in_ECX;
  int local_8;
  
  *(undefined2 *)(in_ECX + 0xf0) = 0;
  for (local_8 = 0; local_8 < 0x40; local_8 = local_8 + 1) {
    if (((((short)(&DAT_006183c4)[local_8 * 10] == DAT_0049f538) &&
         ((&DAT_006183bc)[local_8 * 5] != 0)) && ((&DAT_006183cc)[local_8 * 10] != 0xb)) &&
       (*(short *)(in_ECX + 0xf0) < 0x20)) {
      *(undefined4 **)(in_ECX + 0x70 + *(short *)(in_ECX + 0xf0) * 4) = &DAT_006183bc + local_8 * 5;
      *(short *)(in_ECX + 0xf0) = *(short *)(in_ECX + 0xf0) + 1;
    }
  }
  if ((*(int *)(in_ECX + 0xf4) == 0) || (**(int **)(in_ECX + 0xf4) == 0)) {
    *(undefined4 *)(in_ECX + 0xf4) = 0;
    if (*(short *)(in_ECX + 0xf0) != 0) {
      *(undefined4 *)(in_ECX + 0xf4) = *(undefined4 *)(in_ECX + 0x70);
    }
    thunk_FUN_0046c3bc(s_IWTaskOptions_004a0f7c,0x13ba,*(undefined4 *)(in_ECX + 0xf4),0);
    thunk_FUN_0046c3bc(s_IWTaskInfo_004a0f8c,0x13ba,*(undefined4 *)(in_ECX + 0xf4),0);
  }
  thunk_FUN_00445739();
  if ((*(int *)(in_ECX + 0xf4) == 0) || (*(int *)(in_ECX + 0x3c) != 1)) {
    DAT_005e16ec = 9999;
  }
  else {
    DAT_005e16ec = (undefined2)((*(int *)(in_ECX + 0xf4) + -0x6183bc) / 0x14);
  }
  return;
}
```

---


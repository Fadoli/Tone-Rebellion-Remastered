# 0014_batch_0010 — détails (2/3)

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

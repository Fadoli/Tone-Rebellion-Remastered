# 0016_batch_0012 — détails (2/3)

## FUN_004578df — 0x4578df

- Classification : internal
- Corps : `0x4578df–0x457eaa`
- État : pseudocode obtenu
- Evidence : `ev_19858e9b6cb204cf31197808def027e78a942c8fcb764fbd77ec3e48b35dd6e5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40117c` — `thunk_FUN_0045af55`
- `0x4014ce` — `thunk_FUN_004108fa`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x40168b` — `thunk_FUN_0045749a`
- `0x401898` — `thunk_FUN_00410643`
- `0x40196f` — `thunk_FUN_0045af2b`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x401d8e` — `thunk_FUN_004140dd`
- `0x4021c6` — `thunk_FUN_0046ba3b`
- `0x4023d3` — `thunk_FUN_0046b928`

### Chaînes référencées

- `0x4a34a8` — "resume.gam"

### Pseudocode Ghidra

```c
undefined4 FUN_004578df(short param_1,int param_2,int param_3)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int in_ECX;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  bool bVar6;
  int local_10;
  uint local_c;
  int local_8;
  
  switch(param_1) {
  case 1:
    *(undefined4 *)(in_ECX + 0x3c) = 1;
    *(undefined4 *)(in_ECX + 0x38) = 1;
    *(undefined4 *)(in_ECX + 0x34) = 1;
    *(undefined2 *)(in_ECX + 0x70) = 0;
    *(undefined2 *)(in_ECX + 0x88) = 0;
    *(undefined4 *)(in_ECX + 0x18) = 0;
    *(undefined2 *)(in_ECX + 0x8a) = 0xffff;
    thunk_FUN_00410643();
    uVar1 = thunk_FUN_004108fa(0,0x40400000,0,0x40400000,0,0x40400000);
    *(undefined2 *)(in_ECX + 0xa0) = uVar1;
    break;
  case 2:
    *(undefined4 *)(in_ECX + 0x3c) = 0;
    *(undefined4 *)(in_ECX + 0x38) = 0;
    break;
  default:
    uVar2 = thunk_FUN_004293c6(CONCAT22((short)((uint)(param_1 + -1) >> 0x10),param_1),param_2,
                               param_3);
    return uVar2;
  case 6:
    if (*(short *)(in_ECX + 0x88) == 0) {
      if (*(int *)(in_ECX + 4) == DAT_0062c6bc) {
        *(undefined2 *)(in_ECX + 0x88) = 1;
        *(undefined2 *)(in_ECX + 0x70) = 0;
        *(undefined4 *)(in_ECX + 0x18) = 0x1df;
        thunk_FUN_0046b928(*(undefined4 *)(in_ECX + 4),0x32,0,0,0);
      }
    }
    else if (*(short *)(in_ECX + 0x88) == 2) {
      if ((param_3 == 0) || (0x61 < param_3)) {
        *(undefined2 *)(in_ECX + 0x88) = 3;
        thunk_FUN_0046b928(*(undefined4 *)(in_ECX + 4),0x32,0,0,0);
      }
      else if (*(short *)(in_ECX + 0x8a) != -1) {
        switch(*(undefined2 *)(in_ECX + 0x8a)) {
        case 0:
          if (DAT_004befe0 == 0) {
            thunk_FUN_0046c1b4(1,5,0);
          }
          break;
        case 1:
          if (DAT_004befe0 == 0) {
            thunk_FUN_0046c1b4(1,4,0);
          }
          break;
        case 2:
          local_c = (uint)(DAT_004bf124 == 0);
          thunk_FUN_004140dd(10,&local_c,4,0);
          break;
        case 3:
          if ((1 < DAT_0062d172) && (DAT_0062d174 = DAT_0062d172, DAT_004befe0 == 0)) {
            thunk_FUN_0045749a(s_resume_gam_004a34a8);
          }
          thunk_FUN_0046c1b4(1,0,0);
          break;
        case 4:
          bVar6 = DAT_0049c9a8 == 0;
          if (bVar6) {
            thunk_FUN_0045af55(DAT_0049c9a0);
          }
          else {
            thunk_FUN_0045af55(0);
          }
          DAT_0049c9a8 = (uint)bVar6;
          break;
        case 5:
          if (DAT_0049c9ac == 0) {
            thunk_FUN_0045af2b(DAT_0049c9a4);
            DAT_0049c9ac = 1;
          }
          else {
            thunk_FUN_0045af2b(0);
            DAT_0049c9ac = 0;
          }
        }
      }
      if ((0x1c1 < param_2) && (param_2 < 0x245)) {
        if ((10 < param_3) && ((param_3 < 0x20 && (DAT_0049c9a8 != 0)))) {
          DAT_0049c9a0 = param_2 + -0x1c8;
          if (DAT_0049c9a0 < 0) {
            DAT_0049c9a0 = 0;
          }
          if (100 < DAT_0049c9a0) {
            DAT_0049c9a0 = 100;
          }
          thunk_FUN_0045af55(DAT_0049c9a0);
        }
        if (((0x38 < param_3) && (param_3 < 0x4e)) && (DAT_0049c9ac != 0)) {
          DAT_0049c9a4 = param_2 + -0x1c8;
          if (DAT_0049c9a4 < 0) {
            DAT_0049c9a4 = 0;
          }
          if (100 < DAT_0049c9a4) {
            DAT_0049c9a4 = 100;
          }
          thunk_FUN_0045af2b(DAT_0049c9a4);
        }
      }
    }
    break;
  case 8:
    break;
  case 9:
    break;
  case 10:
    if (*(short *)(in_ECX + 0x88) == 2) {
      *(undefined2 *)(in_ECX + 0x8a) = 0xffff;
      for (local_8 = 0; local_8 < 6; local_8 = local_8 + 1) {
        if ((((*(int *)(&DAT_004a33f0 + local_8 * 0x10) <= param_2) &&
             (param_2 <= *(int *)(&DAT_004a33f8 + local_8 * 0x10))) &&
            (*(int *)(&DAT_004a33f4 + local_8 * 0x10) <= param_3)) &&
           (param_3 <= *(int *)(&DAT_004a33fc + local_8 * 0x10))) {
          *(undefined2 *)(in_ECX + 0x8a) = (undefined2)local_8;
          return 0;
        }
      }
    }
    break;
  case 0x32:
    if (*(short *)(in_ECX + 0x88) == 1) {
      local_10 = *(int *)(in_ECX + 0x84) - (int)*(short *)(in_ECX + 0x70);
      if (local_10 < 0x32) {
        local_10 = (local_10 * 0xf) / 0x32 + 1;
      }
      if (0xf < local_10) {
        local_10 = 0xf;
      }
      *(short *)(in_ECX + 0x70) = *(short *)(in_ECX + 0x70) + (short)local_10;
      if (*(int *)(in_ECX + 0x84) <= (int)*(short *)(in_ECX + 0x70)) {
        *(undefined2 *)(in_ECX + 0x70) = *(undefined2 *)(in_ECX + 0x84);
        *(undefined2 *)(in_ECX + 0x88) = 2;
        thunk_FUN_0046ba3b(*(undefined4 *)(in_ECX + 4),0xffffffff);
      }
    }
    else if (*(short *)(in_ECX + 0x88) == 3) {
      puVar4 = (undefined4 *)(in_ECX + 0x74);
      puVar5 = (undefined4 *)(in_ECX + 0x8c);
      for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      *(int *)(in_ECX + 0x9c) = (int)*(short *)(in_ECX + 0x70);
      *(short *)(in_ECX + 0x70) = *(short *)(in_ECX + 0x70) + -0xf;
      if (*(int *)(in_ECX + 0x7c) < (int)*(short *)(in_ECX + 0x70)) {
        *(int *)(in_ECX + 0x94) = *(short *)(in_ECX + 0x70) + 1;
      }
      else {
        *(undefined2 *)(in_ECX + 0x70) = *(undefined2 *)(in_ECX + 0x7c);
        *(undefined4 *)(in_ECX + 0x18) = 0;
        *(undefined4 *)(in_ECX + 0x94) = 0;
        *(undefined2 *)(in_ECX + 0x88) = 0;
        thunk_FUN_0046ba3b(*(undefined4 *)(in_ECX + 4),0xffffffff);
      }
      if (DAT_0062d172 != 3) {
        thunk_FUN_0046c1b4(4,0,in_ECX + 0x8c);
      }
    }
  }
  return 0;
}
```

---

---

## FUN_004580fc — 0x4580fc

- Classification : internal
- Corps : `0x4580fc–0x458161`
- État : pseudocode obtenu
- Evidence : `ev_388bca702f5e854db07ca2290ac0df17b32ac9a33bfe74ad5ed3919e5374e50f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`
- `0x402121` — `thunk_FUN_00459370`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_004580fc(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491ab5;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  thunk_FUN_00459370(in_ECX + 0x24,0x80,8,thunk_FUN_00449b60);
  *in_ECX = &PTR_LAB_00494710;
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_00458162 — 0x458162

- Classification : internal
- Corps : `0x458162–0x45834d`
- État : pseudocode obtenu
- Evidence : `ev_2c674ccd76aff90691182205460ba1311267fcfd771b802cf530891d810ccdc1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x40168b` — `thunk_FUN_0045749a`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401ebf` — `thunk_FUN_00458371`
- `0x40218a` — `thunk_FUN_00410765`
- `0x4021e9` — `thunk_FUN_004576c7`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x4a34b4` — "%02d.sav"
- `0x4a34c0` — "data\\game.pal"

### Pseudocode Ghidra

```c
undefined4 FUN_00458162(short param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined2 uVar3;
  undefined2 extraout_var;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_44 [52];
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491acb;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  uVar3 = (undefined2)((uint)(param_1 + -1) >> 0x10);
  switch(param_1) {
  case 1:
    thunk_FUN_0040f6f7();
    local_8 = 0;
    thunk_FUN_0040f752(s_data_game_pal_004a34c0,0x8000);
    thunk_FUN_0040fc15(&DAT_00630730,0x300);
    thunk_FUN_0040f966();
    thunk_FUN_00410765(&DAT_00630730,0,0);
    thunk_FUN_00458371();
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
    uVar3 = extraout_var;
  default:
    uVar2 = thunk_FUN_004293c6(CONCAT22(uVar3,param_1),param_2,param_3);
    goto LAB_0045833d;
  case 5:
    if (param_2 == 0x1b) {
      thunk_FUN_0046c1b4(3,0,0);
    }
    break;
  case 6:
    if (param_3 < 0x23) {
      thunk_FUN_0046c1b4(3,0,0);
      uVar2 = 1;
      goto LAB_0045833d;
    }
    iVar1 = (param_3 + -0x1c) / 0x70 + (param_2 / 0x140) * 4;
    FUN_00472ca0(local_44,s__02d_sav_004a34b4,iVar1);
    if (DAT_0062d172 == 4) {
      if (*(int *)(in_ECX + 0x10c + iVar1 * 0x80) != 0) {
        thunk_FUN_004576c7(local_44);
      }
    }
    else {
      thunk_FUN_0045749a(local_44);
    }
    thunk_FUN_0046c1b4(3,0,0);
    break;
  case 7:
    thunk_FUN_0046c1b4(3,0,0);
    break;
  case 0xb:
  }
  uVar2 = 0;
LAB_0045833d:
  *unaff_FS_OFFSET = local_10;
  return uVar2;
}
```

---

---

## FUN_00458371 — 0x458371

- Classification : internal
- Corps : `0x458371–0x458589`
- État : pseudocode obtenu
- Evidence : `ev_8ded5bd1b93d627e66f82fe4329ca5be65ab34eb54db58717c3bc1ee6267d1c2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401b13` — `thunk_FUN_00457490`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x472ca0` — `FUN_00472ca0`
- `0x473aa0` — `FID_conflict:__open`
- `0x473fe0` — `FUN_00473fe0`
- `0x474b20` — `_memset`
- `0x476e20` — `_strncmp`
- `0x477c90` — `FUN_00477c90`
- `0x478090` — `FUN_00478090`

### Chaînes référencées

- `0x4a34d0` — "%02d.sav"
- `0x4a34dc` — "1.16F"

### Pseudocode Ghidra

```c
void FUN_00458371(void)

{
  int iVar1;
  int in_ECX;
  int iVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_168 [28];
  undefined4 local_14c;
  uint local_144;
  char local_140 [32];
  int local_120;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491ae1;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  _memset((void *)(in_ECX + 0x70),0,0x20);
  _memset((void *)(in_ECX + 0x90),0,0x400);
  thunk_FUN_0040f6f7();
  local_8 = 0;
  local_120 = 0;
  do {
    if (7 < local_120) {
      local_8 = 0xffffffff;
      thunk_FUN_0040f73f();
      *unaff_FS_OFFSET = local_10;
      return;
    }
    *(undefined4 *)(in_ECX + 0x70 + local_120 * 4) = 0;
    FUN_00472ca0(local_140,s__02d_sav_004a34d0,local_120);
    iVar1 = FUN_00478090(local_140,0);
    if (iVar1 == 0) {
      iVar1 = FID_conflict___open(local_140,0x8000);
      if (iVar1 != -1) {
        FUN_00477c90(iVar1,local_168);
        *(undefined4 *)(in_ECX + 0x70 + local_120 * 4) = local_14c;
        FUN_00473fe0(iVar1);
      }
      thunk_FUN_0040f752(local_140,0x8000);
      thunk_FUN_0040fc15(in_ECX + 0x90 + local_120 * 0x80,0x80);
      thunk_FUN_0040f966();
      iVar2 = local_120 * 0x80;
      iVar1 = thunk_FUN_00457490();
      local_144 = (uint)(*(int *)(in_ECX + 0x10c + iVar2) == iVar1);
      if (local_144 != 0) {
        iVar1 = _strncmp((char *)(in_ECX + 0x90 + local_120 * 0x80),s_1_16F_004a34dc,4);
        if (iVar1 == 0) goto LAB_004583e6;
      }
      *(undefined4 *)(in_ECX + 0x10c + local_120 * 0x80) = 0;
    }
LAB_004583e6:
    local_120 = local_120 + 1;
  } while( true );
}
```

---

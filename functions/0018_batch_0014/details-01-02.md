# 0018_batch_0014 — détails (2/3)

## FUN_00469f56 — 0x469f56

- Classification : internal
- Corps : `0x469f56–0x46a4e3`
- État : pseudocode obtenu
- Evidence : `ev_3b7d1c7373d2274d945cf5579c6d5b74b907c2a1517b6587e6a2c23a92bec22e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x4014ba` — `thunk_FUN_0042dd47`
- `0x4016e5` — `thunk_FUN_00429371`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x401b9a` — `thunk_FUN_0046bacf`
- `0x401d84` — `thunk_FUN_0046a4fc`
- `0x401e10` — `thunk_FUN_0046a5b7`
- `0x401e83` — `thunk_FUN_0046be81`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401ffa` — `thunk_FUN_0041412d`
- `0x402194` — `thunk_FUN_0042ee48`
- `0x40227f` — `thunk_FUN_0046c25d`
- `0x4024c8` — `thunk_FUN_0046b752`

### Chaînes référencées

- `0x4a54c8` — "mhwndFocus!=-1"
- `0x4a54d8` — "C:\\float\\src\\winman.cpp"
- `0x4a54f0` — "mhwndFocus!=-1"
- `0x4a5500` — "C:\\float\\src\\winman.cpp"

### Pseudocode Ghidra

```c
bool FUN_00469f56(void)

{
  int iVar1;
  int in_ECX;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_2c [5];
  int local_18;
  undefined4 local_14;
  short local_10;
  short local_e;
  ushort local_c;
  ushort local_a;
  undefined2 local_8;
  
  if ((*(int *)(in_ECX + 0x1f3c) != -1) &&
     (*(int *)(*(int *)(in_ECX + 4 + *(int *)(in_ECX + 0x1f3c) * 0xc) + 0x38) == 0)) {
    *(undefined4 *)(in_ECX + 0x1f3c) = 0xffffffff;
  }
  while (iVar1 = thunk_FUN_0042ee48(&local_14), iVar1 == 1) {
    switch(local_14) {
    case 1:
      if (*(int *)(in_ECX + 0x6314) != 0) {
        if (*(int *)(in_ECX + 0x1f3c) == -1) {
          thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a54d8,0x107,s_mhwndFocus___1_004a54c8);
        }
        thunk_FUN_0046c1b4(4,0,*(int *)(in_ECX + 4 + *(int *)(in_ECX + 0x1f3c) * 0xc) + 8);
        thunk_FUN_00429371((int)local_10 - (int)*(short *)(in_ECX + 0x62bc),
                           (int)local_e - (int)*(short *)(in_ECX + 0x62be));
        *(uint *)(in_ECX + 8 + *(int *)(in_ECX + 0x1f3c) * 0xc) =
             *(uint *)(in_ECX + 8 + *(int *)(in_ECX + 0x1f3c) * 0xc) | 1;
      }
      *(short *)(in_ECX + 0x62bc) = local_10;
      *(short *)(in_ECX + 0x62be) = local_e;
      if ((((*(int *)(in_ECX + 0x6314) == 0) &&
           (thunk_FUN_0046be81(), *(int *)(in_ECX + 0x1f3c) != -1)) &&
          (thunk_FUN_0046c371(*(undefined4 *)(in_ECX + 0x1f3c),10,(int)local_10,(int)local_e),
          *(int *)(in_ECX + 0x630c) != 0)) &&
         (*(undefined4 *)(in_ECX + 0x6310) = 0,
         *(int *)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130) != 0)) {
        (**(code **)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130))
                  (4,(int)local_10,(int)local_e,in_ECX + 0x6310);
      }
      break;
    case 2:
      if (*(int *)(in_ECX + 0x630c) == 0) {
        if ((local_c & 6) == 0) {
          thunk_FUN_0046c25d(6,(int)local_10,(int)local_e,0);
        }
        else {
          *(undefined4 *)(in_ECX + 0x630c) = 1;
          thunk_FUN_0042dd47(2);
        }
      }
      else {
        *(undefined4 *)(in_ECX + 0x630c) = 0;
        thunk_FUN_0042dd47(0);
        thunk_FUN_0046c25d(0xb,1,0,0);
      }
      break;
    case 4:
      if (*(int *)(in_ECX + 0x630c) == 0) {
        if ((local_c & 5) == 0) {
          if (*(int *)(in_ECX + 0x6314) == 0) {
            thunk_FUN_0046c25d(7,(int)local_10,(int)local_e,0);
          }
          else {
            if (*(int *)(in_ECX + 0x1f3c) == -1) {
              thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5500,0x175,s_mhwndFocus___1_004a54f0)
              ;
            }
            puVar2 = (undefined4 *)(*(int *)(in_ECX + 4 + *(int *)(in_ECX + 0x1f3c) * 0xc) + 8);
            puVar3 = local_2c;
            for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
              *puVar3 = *puVar2;
              puVar2 = puVar2 + 1;
              puVar3 = puVar3 + 1;
            }
            thunk_FUN_0046c1b4(4,0,local_2c);
            puVar2 = (undefined4 *)(in_ECX + 0x6318);
            puVar3 = (undefined4 *)(*(int *)(in_ECX + 4 + *(int *)(in_ECX + 0x1f3c) * 0xc) + 8);
            for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
              *puVar3 = *puVar2;
              puVar2 = puVar2 + 1;
              puVar3 = puVar3 + 1;
            }
            *(uint *)(in_ECX + 8 + *(int *)(in_ECX + 0x1f3c) * 0xc) =
                 *(uint *)(in_ECX + 8 + *(int *)(in_ECX + 0x1f3c) * 0xc) & 0xfffffffe;
            *(undefined4 *)(in_ECX + 0x6314) = 0;
          }
        }
        else {
          *(undefined4 *)(in_ECX + 0x630c) = 1;
          thunk_FUN_0042dd47(2);
        }
      }
      else {
        *(undefined4 *)(in_ECX + 0x630c) = 0;
        thunk_FUN_0042dd47(0);
        thunk_FUN_0046c25d(0xb,1,0,0);
      }
      break;
    case 6:
      if ((local_a & 0xff) == 1) {
        local_18 = 1;
        if (((local_a & 0x200) != 0) || (local_c == 0x1b)) {
          local_18 = thunk_FUN_0046a5b7(local_c);
        }
        if (((local_c == 0xd) && (DAT_004befe0 != 0)) &&
           ((*(short *)(in_ECX + 0x29f2) == 0 ||
            ((*(short *)(in_ECX + 0x29f2) == 2 || (*(short *)(in_ECX + 0x29f2) == 3)))))) {
          if (*(int *)(in_ECX + 0x62c0) == 0) {
            *(undefined4 *)(in_ECX + 0x62c0) = 1;
            *(undefined1 *)(in_ECX + 0x62c4) = 0;
            *(undefined2 *)(in_ECX + 0x630a) = 0;
          }
          else {
            *(undefined4 *)(in_ECX + 0x62c0) = 0;
            if (0 < *(short *)(in_ECX + 0x630a)) {
              thunk_FUN_0041412d(in_ECX + 0x62c4,0xffff);
            }
          }
          local_18 = 0;
        }
        if (*(int *)(in_ECX + 0x62c0) != 0) {
          thunk_FUN_0046a4fc(local_8);
          local_18 = 0;
        }
        if (local_18 == 1) {
          thunk_FUN_0046c25d(5,(int)(short)local_c,(int)(short)local_a,0);
        }
      }
    }
  }
  if (*(short *)(in_ECX + 0x2e7c) != 0) {
    thunk_FUN_0046bacf();
  }
  while (0 < *(short *)(in_ECX + 0x2cf8)) {
    thunk_FUN_0046b752();
  }
  if ((-1 < *(short *)(in_ECX + 0x29f2)) &&
     (*(int *)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130) != 0)) {
    (**(code **)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130))(3,0,0,0);
  }
  return *(int *)(in_ECX + 0x62b8) == 0;
}
```

---

---

## FUN_0046a4fc — 0x46a4fc

- Classification : internal
- Corps : `0x46a4fc–0x46a5b6`
- État : pseudocode obtenu
- Evidence : `ev_d55629d5154955eee9995a3684f90b3d09f75094dc652d0f894530e5de308064`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046a4fc(short param_1)

{
  int in_ECX;
  
  if (param_1 == 8) {
    if (0 < *(short *)(in_ECX + 0x630a)) {
      *(short *)(in_ECX + 0x630a) = *(short *)(in_ECX + 0x630a) + -1;
    }
    *(undefined1 *)(in_ECX + 0x62c4 + (int)*(short *)(in_ECX + 0x630a)) = 0;
  }
  else if (((0x1f < param_1) && (param_1 < 0xe2)) && (*(short *)(in_ECX + 0x630a) < 0x45)) {
    *(undefined1 *)(in_ECX + 0x62c4 + (int)*(short *)(in_ECX + 0x630a)) = (undefined1)param_1;
    *(short *)(in_ECX + 0x630a) = *(short *)(in_ECX + 0x630a) + 1;
    *(undefined1 *)(in_ECX + 0x62c4 + (int)*(short *)(in_ECX + 0x630a)) = 0;
  }
  return;
}
```

---

---

## FUN_0046a5b7 — 0x46a5b7

- Classification : internal
- Corps : `0x46a5b7–0x46acc0`
- État : pseudocode obtenu
- Evidence : `ev_c658f75f34deec42ac063f4d2a1e83ba846ef040658718864d73fb6ccd2f2ec6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013fc` — `thunk_FUN_0042d44d`
- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x40150f` — `thunk_FUN_0046ff6f`
- `0x40168b` — `thunk_FUN_0045749a`
- `0x401744` — `thunk_FUN_00448436`
- `0x401749` — `thunk_FUN_00414c97`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x401af0` — `thunk_FUN_00467be5`
- `0x401b54` — `thunk_FUN_0042c608`
- `0x401d48` — `thunk_FUN_00462e66`
- `0x401d8e` — `thunk_FUN_004140dd`
- `0x401d9d` — `thunk_FUN_00460072`
- `0x401dd4` — `thunk_FUN_0041c146`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401f00` — `thunk_FUN_0045ab46`
- `0x401f5f` — `thunk_FUN_0042dc4e`
- `0x40205e` — `thunk_FUN_0040fac8`
- `0x402176` — `thunk_FUN_00414bf7`
- `0x4021e9` — `thunk_FUN_004576c7`
- `0x40228e` — `thunk_FUN_00414081`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x40231f` — `thunk_FUN_00462fa3`
- `0x474b20` — `_memset`
- `0x478410` — `FUN_00478410`

### Chaînes référencées

- `0x4a5518` — "Entering MakeGIF"
- `0x4a552c` — "quick.sav"
- `0x4a5538` — "quick.sav"
- `0x4a5544` — "resume.gam"
- `0x4a5550` — "06.sav"
- `0x4a5558` — "07.sav"

### Pseudocode Ghidra

```c
undefined4 FUN_0046a5b7(undefined2 param_1)

{
  void *_Dst;
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int extraout_ECX;
  undefined4 *unaff_FS_OFFSET;
  uint uStackY_33cbc;
  int local_364;
  int local_35c;
  undefined4 local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491d76;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  FUN_00478410();
  switch(param_1) {
  case 0x24:
    if (DAT_004c2b74 != 0) {
      thunk_FUN_0040f6f7();
      local_8 = 0;
      thunk_FUN_0040f6f7();
      local_8._0_1_ = 1;
      iVar1 = thunk_FUN_0040f752();
      iVar2 = thunk_FUN_0040f752();
      if (iVar1 + iVar2 == 0) {
        thunk_FUN_0040fac8();
        thunk_FUN_0040fac8();
        thunk_FUN_00462e66();
        local_8._0_1_ = 2;
        thunk_FUN_00467be5();
        thunk_FUN_00467be5();
        for (uStackY_33cbc = 0; uStackY_33cbc < 0x33838; uStackY_33cbc = uStackY_33cbc + 1) {
        }
        local_8._0_1_ = 1;
        thunk_FUN_00462fa3();
        local_8 = (uint)local_8._1_3_ << 8;
        thunk_FUN_0040f73f();
        local_8 = 0xffffffff;
        thunk_FUN_0040f73f();
      }
      else {
        local_8 = (uint)local_8._1_3_ << 8;
        thunk_FUN_0040f73f();
        local_8 = 0xffffffff;
        thunk_FUN_0040f73f();
      }
    }
    break;
  default:
    uVar3 = 1;
    goto LAB_0046acb1;
  case 0x31:
  case 0x32:
  case 0x33:
  case 0x34:
    thunk_FUN_0042c608();
    thunk_FUN_0046c1b4();
    break;
  case 0x38:
  case 0x6d:
    if (((DAT_004befe0 == 0) || (DAT_004c2bb4 != 0)) && (0 < DAT_004bf110 + -1)) {
      thunk_FUN_004140dd();
    }
    break;
  case 0x39:
  case 0x6b:
    if (((DAT_004befe0 == 0) || (DAT_004c2bb4 != 0)) && (DAT_004bf110 + 1 < 4)) {
      thunk_FUN_004140dd();
    }
    break;
  case 0x41:
    if (DAT_004c2b74 != 0) {
      DAT_00630ab0 = (uint)(DAT_00630ab0 == 0);
    }
    break;
  case 0x43:
    if (DAT_004c2b74 != 0) {
      DAT_004c2b7c = (uint)(DAT_004c2b7c == 0);
    }
    break;
  case 0x45:
    if (DAT_004c2b74 != 0) {
      thunk_FUN_0041c146();
    }
    break;
  case 0x46:
    if (DAT_004c2b74 != 0) {
      DAT_004c2b78 = (uint)(DAT_004c2b78 == 0);
    }
    break;
  case 0x47:
    _Dst = (void *)thunk_FUN_00414bf7();
    _memset(_Dst,0,0x4b000);
    thunk_FUN_0042d44d();
    thunk_FUN_0042dc4e();
    thunk_FUN_00414ad0();
    thunk_FUN_00448436();
    thunk_FUN_00414c97();
    break;
  case 0x48:
    if (DAT_004c2b74 != 0) {
      DAT_004c2bac = (uint)(DAT_004c2bac == 0);
      thunk_FUN_0046c1b4();
    }
    break;
  case 0x49:
    if (DAT_004c2b74 != 0) {
      thunk_FUN_0046c1b4();
    }
    break;
  case 0x4c:
    if (DAT_004c2b74 != 0) {
      thunk_FUN_00460072();
    }
    break;
  case 0x4d:
    if (DAT_004c2b74 != 0) {
      DAT_004c2b8c = (uint)(DAT_004c2b8c == 0);
    }
    break;
  case 0x51:
    if (DAT_004c2b74 != 0) {
      DAT_00630aac = (uint)(DAT_00630aac == 0);
    }
    break;
  case 0x52:
    if ((DAT_004befe0 == 0) && (DAT_004c2b74 != 0)) {
      thunk_FUN_004576c7();
      thunk_FUN_0046c1b4();
    }
    break;
  case 0x53:
    if ((DAT_004befe0 == 0) && (DAT_004c2b74 != 0)) {
      thunk_FUN_0045749a();
    }
    break;
  case 0x56:
    DAT_00630ab4 = (uint)(DAT_00630ab4 == 0);
    break;
  case 0x57:
    if (DAT_004c2b74 != 0) {
      if (DAT_004befe0 == 0) {
        thunk_FUN_0046c1b4();
      }
      else {
        thunk_FUN_00414081();
      }
    }
    break;
  case 0x58:
    if ((1 < *(short *)(extraout_ECX + 0x29f2)) && (DAT_004befe0 == 0)) {
      *(undefined2 *)(extraout_ECX + 0x29f4) = *(undefined2 *)(extraout_ECX + 0x29f2);
      thunk_FUN_0045749a();
    }
    *(undefined4 *)(extraout_ECX + 0x62b8) = 1;
    break;
  case 0x59:
    if (DAT_004c2b74 != 0) {
      for (local_35c = 0; local_35c < (int)(uint)DAT_006136b0; local_35c = local_35c + 1) {
        for (local_364 = 0; local_364 < (short)(&DAT_005eebc0)[local_35c * 0x14f4];
            local_364 = local_364 + 1) {
        }
      }
    }
    break;
  case 0x5a:
    if (DAT_004c2b74 != 0) {
      thunk_FUN_0046ff6f();
      thunk_FUN_0045ab46();
    }
    break;
  case 0xdb:
    if (DAT_004c2b74 != 0) {
      if (DAT_004c2b60 < 0xb) {
        DAT_004c2b60 = 5;
      }
      else {
        DAT_004c2b60 = DAT_004c2b60 - 5;
      }
    }
    break;
  case 0xdd:
    if (DAT_004c2b74 != 0) {
      DAT_004c2b60 = DAT_004c2b60 + 5;
    }
  }
  uVar3 = 0;
LAB_0046acb1:
  *unaff_FS_OFFSET = local_10;
  return uVar3;
}
```

---

---

## FUN_0046ade3 — 0x46ade3

- Classification : internal
- Corps : `0x46ade3–0x46ae18`
- État : pseudocode obtenu
- Evidence : `ev_248b66099002cd89daeaf7dd64aa1b25282ddc4e480de5f4c1a3d47a2dc17f61`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401712` — `thunk_FUN_004289a7`
- `0x401c30` — `thunk_FUN_0042de03`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046ade3(undefined4 param_1,int param_2,undefined4 *param_3,int *param_4,
                 undefined4 *param_5)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = thunk_FUN_0042de03();
  iVar2 = thunk_FUN_004289a7(uVar1);
  *param_4 = param_2 + 1 + iVar2;
  *param_3 = 10;
  *param_5 = 0x26c;
  return;
}
```

---

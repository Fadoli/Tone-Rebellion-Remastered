# 0012_batch_0008 — détails (1/3)

## FUN_00435826 — 0x435826

- Classification : internal
- Corps : `0x435826–0x435ea6`
- État : pseudocode obtenu
- Evidence : `ev_9fac3ab32e724258b184a4abd7ffd102c61b15164169cc041ae03f1859b5bb49`
- Evidence complémentaire (routes clic carte `0x65/0x11`, `/0x13`) : `ev_d63df45ffddaf36c3e3abb71731b4bad3d8b1e4fb492b3b2333e19d8cea5f0b9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40123a` — `thunk_FUN_0041e3eb`
- `0x4013f7` — `thunk_FUN_0046c402`
- `0x4014ba` — `thunk_FUN_0042dd47`
- `0x401bf4` — `thunk_FUN_0042970c`
- `0x401e9c` — `thunk_FUN_00466c08`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401faa` — `thunk_FUN_0045f337`
- `0x4021ee` — `thunk_FUN_00435581`
- `0x40228e` — `thunk_FUN_00414081`
- `0x472c6c` — `__ftol`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x49f960` — "farloc"
- `0x49f968` — "C:\\float\\src\\islewin.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_00435826(int param_1,uint param_2,int param_3)

{
  int iVar1;
  int in_ECX;
  undefined2 extraout_var;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  short local_42;
  undefined2 local_3e;
  short *local_38;
  double local_34;
  undefined *local_2c;
  int local_28;
  int local_24;
  int *local_20;
  short local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = 1;
  thunk_FUN_00435581(param_1,param_2,&local_c,&local_14);
  if (local_c != 1) {
    local_14 = -1;
  }
  local_c = 2;
  thunk_FUN_00435581(param_1,param_2,&local_c,&local_10);
  if (local_c != 2) {
    local_10 = -1;
  }
  local_8 = 1;
  if (((((local_10 == -1) && (*(int *)(in_ECX + 0x16c) != 0)) &&
       (*(short *)(*(int *)(in_ECX + 0x16c) + 0x18) != -1)) &&
      ((param_3 != 0 && (*(int *)(*(int *)(in_ECX + 0x16c) + 0x14) == DAT_0049f538)))) &&
     (((local_18 = 0, local_14 == -1 ||
       ((local_18 = *(int *)(in_ECX + 0x9c) + 0x428 + local_14 * 0x60, local_18 != 0 &&
        (*(int *)(local_18 + 0x14) == -1)))) ||
      ((local_18 != 0 &&
       ((*(int *)(local_18 + 0x14) != 4 &&
        (*(int *)(&DAT_00619290 + *(int *)(local_18 + 0x14) * 4 + DAT_0049f538 * 0x14a0) == 1)))))))
     ) {
    thunk_FUN_0042970c(0x65,0x13,0);
  }
  if ((*(ushort *)(in_ECX + 0x178) & 4) == 0) {
    if (((local_10 == -1) || (*(short *)(in_ECX + 0x178) == 1)) ||
       ((local_14 != -1 && (*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) != 0)))) {
      if (local_14 == -1) {
        thunk_FUN_0042970c(0x4b,0,0);
        if ((*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) == 0) &&
           ((*(int *)(in_ECX + 0x16c) != 0 || (*(int *)(in_ECX + 0x170) != 0)))) {
          *(undefined4 *)(in_ECX + 0x16c) = 0;
          *(undefined4 *)(in_ECX + 0x170) = 0;
          thunk_FUN_0042970c(0x33,0,0);
        }
      }
      else {
        local_24 = *(int *)(in_ECX + 0x9c) + 0x428 + local_14 * 0x60;
        if ((DAT_005dc650 == 0) || (*(int *)(local_24 + 4) != 0)) {
          if ((param_3 != 0) &&
             ((((*(short *)(in_ECX + 0x178) == 0 && (*(int *)(in_ECX + 0x16c) != 0)) &&
               (*(int *)(*(int *)(in_ECX + 0x16c) + 0x14) == DAT_0049f538)) &&
              (*(short *)(*(int *)(in_ECX + 0x16c) + 0x18) != -1)))) {
            if ((*(int *)(local_24 + 0x14) == 4) ||
               (*(int *)(&DAT_00619290 + *(int *)(local_24 + 0x14) * 4 + DAT_0049f538 * 0x14a0) == 0
               )) {
              thunk_FUN_0042970c(0x65,0x11,0);
            }
            else {
              thunk_FUN_0042970c(0x65,0x13,0);
            }
          }
          if ((*(ushort *)(in_ECX + 0x178) & 1) == 0) {
            *(undefined4 *)(in_ECX + 0x170) = 0;
            *(int *)(in_ECX + 0x16c) = local_24;
            thunk_FUN_0042970c(0x32,param_3,0);
          }
          else {
            local_28 = 1;
            if (*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) != 0) {
              local_28 = 0;
              local_8 = 0;
              local_2c = &DAT_005ec640 +
                         *(short *)(DAT_0049f538 * 0x14a0 + 0x61a574) * 0x60 +
                         *(short *)(DAT_0049f538 * 0x14a0 + 0x61a572) * 0x29e8;
              iVar1 = thunk_FUN_0045f337(local_2c,local_24);
              if (iVar1 == 0) {
                if ((*(int *)(local_24 + 4) == 2) && ((*(uint *)(local_24 + 0x1c) & 1) != 0)) {
                  if (DAT_004befe0 != 0) {
                    _memset(&local_48,0,0x10);
                    local_48 = 2;
                    local_46 = (undefined2)DAT_0049f538;
                    local_42 = DAT_0049f53c;
                    local_3e = *(undefined2 *)(local_24 + 0x36);
                    local_44 = 9;
                    thunk_FUN_00414081(1,&local_48,0x10);
                  }
                  thunk_FUN_0042970c(0x4d,(int)*(short *)(local_24 + 0x36),0);
                  local_38 = (short *)thunk_FUN_00466c08(*(undefined2 *)(local_24 + 8),
                                                         CONCAT22(extraout_var,
                                                                  *(undefined2 *)(local_24 + 0x36)))
                  ;
                  if (local_38 == (short *)0x0) {
                    uVar3 = thunk_FUN_00414b64(s_C__float_src_islewin_cpp_0049f968,0x72c,
                                               s_farloc_0049f960);
                  }
                  else {
                    uVar3 = 0;
                  }
                  local_34 = ((double)(*local_38 + -0x140) * 1000.0) / 1921.0;
                  uVar2 = 1;
                  uVar3 = __ftol(1,*local_38 + -0x140,uVar3);
                  thunk_FUN_0042970c(0x3d,uVar3,uVar2);
                }
              }
              else {
                *(int *)(in_ECX + 0x16c) = local_24;
                local_28 = 1;
                local_8 = 1;
              }
            }
            if (local_28 != 0) {
              thunk_FUN_0042970c(0x40,(int)DAT_0049f53c,local_14);
              *(undefined4 *)(in_ECX + 0x174) = 0;
              *(undefined2 *)(in_ECX + 0x178) = 0;
            }
          }
        }
        else {
          thunk_FUN_0042970c(0x38,1,local_14);
        }
      }
    }
    else {
      local_20 = &DAT_006137b8 + local_10 * 0x13;
      if (*(int *)(in_ECX + 0x170) != 0) {
        *(undefined4 *)(in_ECX + 0x170) = 0;
      }
      if (((*(int *)(in_ECX + 0x16c) != 0) &&
          (*(int *)(*(int *)(in_ECX + 0x16c) + 0x14) == DAT_0049f538)) &&
         (*(short *)(*(int *)(in_ECX + 0x16c) + 0x18) != -1)) {
        if ((param_3 != 0) && (*(short *)(in_ECX + 0x178) == 0)) {
          if ((*local_20 == 4) ||
             (*(int *)(&DAT_00619290 + *local_20 * 4 + DAT_0049f538 * 0x14a0) == 0)) {
            thunk_FUN_0046c402(0x65,0x10,0);
          }
          else {
            thunk_FUN_0046c402(0x65,0x12,0);
          }
        }
        if ((*(ushort *)(in_ECX + 0x178) & 2) != 0) {
          thunk_FUN_0042970c(0x41,local_10,0);
          *(undefined4 *)(in_ECX + 0x174) = 0;
          *(undefined2 *)(in_ECX + 0x178) = 0;
        }
      }
      thunk_FUN_0042970c(0x3f,local_10,0);
    }
  }
  else {
    local_1c = thunk_FUN_0041e3eb(param_1 + *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2),
                                  param_2 & 0xffff);
    thunk_FUN_0042970c(0x4c,(int)local_1c,0);
    *(undefined4 *)(in_ECX + 0x174) = 0;
    *(undefined2 *)(in_ECX + 0x178) = 0;
  }
  if (local_8 != 0) {
    *(undefined4 *)(in_ECX + 0x174) = 0;
    *(undefined2 *)(in_ECX + 0x178) = 0;
    *(undefined2 *)(in_ECX + 0x17e) = 0;
    thunk_FUN_0042dd47((int)*(short *)(in_ECX + 0x17e));
  }
  return 1;
}
```

---

---

## FUN_00435ea7 — 0x435ea7

- Classification : internal
- Corps : `0x435ea7–0x435f4c`
- État : pseudocode obtenu
- Evidence : `ev_8af73d35e8e208233c7a5f5ab7e9e508d0446c7e765185ccea58a2fe6874a08b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00435ea7(short param_1)

{
  int iVar1;
  int iVar2;
  int in_ECX;
  short local_10;
  short local_8;
  
  iVar2 = (int)DAT_0049f53c;
  local_8 = *(short *)(&DAT_005dbee0 + iVar2 * 2) + param_1;
  if (DAT_005dc670 == 0) {
    iVar2 = *(int *)(*(int *)(in_ECX + 0x9c) + 0x408 + DAT_0049f538 * 8);
    iVar1 = *(int *)(*(int *)(in_ECX + 0x9c) + 0x40c + DAT_0049f538 * 8);
    if (local_8 < iVar2) {
      local_10 = (short)iVar2;
      local_8 = local_10;
    }
    if (iVar1 + -0x27f < (int)local_8) {
      iVar2 = iVar1 + -0x27f;
      local_8 = (short)iVar2;
    }
  }
  if (local_8 < 0) {
    local_8 = 0;
  }
  if (0x781 < local_8) {
    local_8 = 0x781;
  }
  return CONCAT22((short)((uint)iVar2 >> 0x10),local_8);
}
```

---

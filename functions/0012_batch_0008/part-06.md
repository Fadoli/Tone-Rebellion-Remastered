# 0012_batch_0008 — détails (6/8)

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

## FUN_00435f4d — 0x435f4d

- Classification : internal
- Corps : `0x435f4d–0x436dc7`
- État : pseudocode obtenu
- Evidence : `ev_9466be6d877d3a7686cb6bcf7838301774c412a8e560a476b938307aac8b32ad`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x4011a9` — `thunk_FUN_00403c35`
- `0x4011fe` — `thunk_FUN_0042d743`
- `0x401285` — `thunk_FUN_00436e06`
- `0x401294` — `thunk_FUN_004289ec`
- `0x401442` — `thunk_FUN_0041169f`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x401555` — `thunk_FUN_0042d647`
- `0x401596` — `thunk_FUN_0040d5bf`
- `0x401631` — `thunk_FUN_004182c8`
- `0x401663` — `thunk_FUN_004282f9`
- `0x401767` — `thunk_FUN_00436ea8`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401816` — `thunk_FUN_00436f3f`
- `0x40193d` — `thunk_FUN_0042d807`
- `0x401a05` — `thunk_FUN_00432c74`
- `0x401d7a` — `thunk_FUN_0042d598`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402040` — `thunk_FUN_00411478`
- `0x402054` — `thunk_FUN_0042d697`
- `0x402081` — `thunk_FUN_004066e3`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x40240a` — `thunk_FUN_00411033`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472c6c` — `__ftol`
- `0x472ca0` — `FUN_00472ca0`
- `0x472da0` — `FUN_00472da0`
- `0x474b90` — `FUN_00474b90`
- `0x476ce4` — `FUN_00476ce4`

### Chaînes référencées

- `0x49d0b8` — "FA_Nothing"
- `0x49d0b8` — "FA_Nothing"
- `0x49f988` — "World Pos (%d,%d)"
- `0x49f99c` — "cryptic%d"
- `0x49f9a8` — "%s: %s"
- `0x49f9b0` — "No selected floater"
- `0x49f9c4` — "triggers"
- `0x49f9d8` — "C:\\float\\src\\islewin.cpp"

### Pseudocode Ghidra

```c
void FUN_00435f4d(void)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int in_ECX;
  undefined4 *puVar6;
  int *piVar7;
  undefined4 *puVar8;
  int *piVar9;
  int local_110;
  undefined1 local_10c [12];
  int local_100;
  int local_fc;
  int local_f8;
  int local_f4;
  int *local_f0;
  int local_ec;
  int local_e8;
  undefined1 local_e4 [8];
  short *local_dc;
  int local_d8;
  int *local_d4;
  int local_d0;
  int local_cc;
  int local_c8;
  uint local_c4;
  short *local_c0;
  int local_bc;
  short *local_b8;
  int local_b4;
  int local_b0;
  int local_ac [5];
  int local_98 [5];
  int local_84;
  int local_80;
  undefined4 local_7c [5];
  int local_68;
  int local_64;
  uint local_60;
  int local_5c;
  int local_58;
  undefined1 local_54 [60];
  undefined4 local_18;
  int local_14;
  undefined4 local_10;
  int local_c;
  undefined4 local_8;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    if (*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) == *(short *)(in_ECX + 0x70)) {
      *(undefined2 *)(in_ECX + 0x70) = 0xffff;
      *(undefined2 *)(in_ECX + 0x72) = 0;
    }
    local_60 = (uint)(*(short *)(in_ECX + 0x72) == 1000);
    if ((*(short *)(in_ECX + 0x70) != -1) && (local_60 == 0)) {
      local_68 = (int)*(short *)(in_ECX + 0x70) - (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
      local_64 = local_68;
      if (local_68 < 0) {
        local_64 = -local_68;
      }
      if (0x78 < local_64) {
        local_64 = 0x78;
      }
      FUN_00476ce4((double)local_64);
      uVar2 = __ftol();
      *(undefined2 *)(in_ECX + 0x72) = uVar2;
      if (local_64 < *(short *)(in_ECX + 0x72)) {
        *(undefined2 *)(in_ECX + 0x72) = (undefined2)local_64;
      }
      if (local_68 < 0) {
        *(short *)(in_ECX + 0x72) = -*(short *)(in_ECX + 0x72);
      }
    }
    if (local_60 == 0) {
      *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) =
           *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) + *(short *)(in_ECX + 0x72);
      if (*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) < 0) {
        *(undefined2 *)(&DAT_005dbee0 + DAT_0049f53c * 2) = 0;
      }
      if (0x781 < *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2)) {
        *(undefined2 *)(&DAT_005dbee0 + DAT_0049f53c * 2) = 0x781;
      }
    }
    else {
      *(short *)(in_ECX + 0x72) =
           *(short *)(in_ECX + 0x70) - *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
      *(undefined2 *)(&DAT_005dbee0 + DAT_0049f53c * 2) = *(undefined2 *)(in_ECX + 0x70);
    }
    local_14 = 0;
    local_10 = 0;
    local_c = 0x27f;
    local_8 = 0x13f;
    iVar3 = thunk_FUN_0042d807();
    if (iVar3 == 0) {
      piVar7 = (int *)(in_ECX + 0x74);
      piVar9 = local_ac;
      for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
        *piVar9 = *piVar7;
        piVar7 = piVar7 + 1;
        piVar9 = piVar9 + 1;
      }
      local_18 = thunk_FUN_0042d28f();
      local_ac[1] = (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
      local_ac[3] = *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) + 0x27f;
      thunk_FUN_004066e3(local_ac,0,0,&local_18,0,0,0xffffffff);
      thunk_FUN_0042d38a();
    }
    else {
      if (*(int *)(in_ECX + 0x168) == 0) {
        if (*(short *)(in_ECX + 0x72) != 0) {
          thunk_FUN_0042d743(0,0,0x27f,0x13f,-(int)*(short *)(in_ECX + 0x72));
          local_80 = (int)*(short *)(in_ECX + 0x72);
          if (local_80 < 0) {
            local_80 = -local_80;
          }
          if (*(short *)(in_ECX + 0x72) < 1) {
            local_84 = (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
            if (local_84 < 0) {
              local_84 = local_84 + 0xa00;
            }
          }
          else {
            local_84 = (*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) - local_80) + 0x280;
            if (0x9ff < local_84) {
              local_84 = (*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) - local_80) + -0x780;
            }
          }
          piVar7 = (int *)(in_ECX + 0x74);
          piVar9 = local_98;
          for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
            *piVar9 = *piVar7;
            piVar7 = piVar7 + 1;
            piVar9 = piVar9 + 1;
          }
          local_18 = thunk_FUN_0042d598();
          if (*(short *)(in_ECX + 0x72) < 1) {
            local_c = local_80 + -1;
          }
          else {
            local_14 = 0x27f - (local_80 + -1);
          }
          local_98[1] = local_84;
          local_98[3] = local_84 + -1 + local_80;
          thunk_FUN_004066e3(local_98,0,0,&local_18,0,0,0xffffffff);
          thunk_FUN_0042d647();
        }
      }
      else {
        puVar6 = (undefined4 *)(in_ECX + 0x74);
        puVar8 = local_7c;
        for (iVar3 = 5; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar8 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar8 = puVar8 + 1;
        }
        local_7c[0] = thunk_FUN_0042d598();
        thunk_FUN_004066e3(in_ECX + 0x74,(int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2),0,
                           local_7c,0,0,0xffffffff);
        thunk_FUN_0042d647();
        *(undefined4 *)(in_ECX + 0x168) = 0;
      }
      thunk_FUN_0042d697(0,0,0x27f,0x13f);
    }
    uVar4 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar4;
    if (*(short *)(in_ECX + 0x17a) != -1) {
      local_b8 = (short *)(*(int *)(in_ECX + 0x9c) + 0x428 + *(short *)(in_ECX + 0x17a) * 0x60);
      local_b0 = (int)*local_b8 - (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
      local_b4 = (int)local_b8[1];
      if ((*(int *)(local_b8 + 2) == 3) && (*(int *)(local_b8 + 8) == 3)) {
        thunk_FUN_00411478(in_ECX + 8,local_b0 + -0x17,local_b4 + -0x17,local_b0 + 0x17,
                           local_b4 + 0x17,DAT_00618e44 >> 1);
      }
    }
    if (DAT_005dc670 == 0) {
      for (local_58 = 0; local_58 < *(short *)(*(int *)(in_ECX + 0x9c) + 0x29a8);
          local_58 = local_58 + 1) {
        local_dc = (short *)(*(int *)(in_ECX + 0x9c) + 0x428 +
                            *(short *)(in_ECX + 0xa0 + local_58 * 2) * 0x60);
        local_d8 = (int)*local_dc - (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
        if (((*(int *)(local_dc + 2) == 3) ||
            ((*(int *)(in_ECX + 0xc) + -100 <= local_d8 &&
             (local_d8 <= *(int *)(in_ECX + 0x14) + 100)))) &&
           (thunk_FUN_0040d5bf(in_ECX + 8), DAT_005dc65c != 0)) {
          FUN_00472ca0(local_e4,&DAT_0049f984);
          local_e8 = thunk_FUN_0042de0d();
          if (*(short *)(in_ECX + 0x17a) == *(short *)(in_ECX + 0xa0 + local_58 * 2)) {
            uVar5 = thunk_FUN_0042dd0f();
            *(uint *)(local_e8 + 8) = uVar5 & 0xff;
          }
          thunk_FUN_004289c0(in_ECX + 8,
                             (*local_dc + 3) - (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2),
                             (int)local_dc[1],local_e4);
          uVar5 = thunk_FUN_0042dd0f();
          *(uint *)(local_e8 + 8) = uVar5 & 0xff;
        }
      }
      local_d4 = &DAT_006137b8;
      local_d0 = 0;
      local_58 = 0;
      while ((local_58 < 0x100 && (local_d0 < (int)(uint)DAT_006183b8))) {
        if (((*local_d4 != -1) &&
            (((local_d0 = local_d0 + 1, *(short *)((int)local_d4 + 0xe) == DAT_0049f53c &&
              ((local_d4[7] & 1U) == 0)) &&
             (local_ec = (int)(short)local_d4[4] - (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2)
             , *(int *)(in_ECX + 0xc) + -100 <= local_ec)))) &&
           (local_ec <= *(int *)(in_ECX + 0x14) + 100)) {
          if (local_d4 == *(int **)(in_ECX + 0x170)) {
            DAT_005dc668 = 1;
          }
          thunk_FUN_004282f9(in_ECX + 8);
          DAT_005dc668 = 0;
        }
        local_58 = local_58 + 1;
        local_d4 = local_d4 + 0x13;
      }
      thunk_FUN_004182c8();
      if (DAT_005dc658 != 0) {
        local_f0 = (int *)(*(int *)(in_ECX + 0x9c) + 8 + DAT_0049f538 * 0x100);
        for (local_58 = 0; local_58 < *(short *)(*(int *)(in_ECX + 0x9c) + DAT_0049f538 * 2);
            local_58 = local_58 + 1) {
          uVar1 = thunk_FUN_0042dd0f(1,0,0xffffffff);
          thunk_FUN_0041169f(in_ECX + 8,
                             *local_f0 - (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2),0x80,
                             local_f0[1] - (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2),0x13f,
                             uVar1);
          local_f0 = local_f0 + 2;
        }
      }
    }
    else {
      if (DAT_005dc658 != 0) {
        local_c0 = (short *)(*(int *)(in_ECX + 0x9c) + 0x428);
        for (local_bc = 0; local_bc < *(short *)(*(int *)(in_ECX + 0x9c) + 0x29a8);
            local_bc = local_bc + 1) {
          if ((*(int *)(local_c0 + 2) == 1) || (local_bc == DAT_0049f544)) {
            uVar1 = thunk_FUN_0042dd0f(1);
            thunk_FUN_0041169f(in_ECX + 8,
                               (*local_c0 + -0x96) -
                               (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2),0x80,
                               (*local_c0 + 0x96) -
                               (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2),0x13f,uVar1);
          }
          local_c0 = local_c0 + 0x30;
        }
      }
      if (DAT_0049f544 != -1) {
        local_c8 = (&DAT_005dbf00)[DAT_0049f544 * 3] -
                   (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
        local_cc = (&DAT_005dbf04)[DAT_0049f544 * 3];
        local_c4 = thunk_FUN_0042dd0f();
        local_c4 = local_c4 & 0xff;
        if (DAT_005dc67c != 0) {
          local_c4 = thunk_FUN_0042dd0f();
          local_c4 = local_c4 & 0xff;
        }
        thunk_FUN_00403c35(in_ECX + 8,local_c8 + -4,local_cc,local_c8 + 4,local_cc,0,local_c4);
        thunk_FUN_00403c35(in_ECX + 8,local_c8,local_cc + -4,local_c8,local_cc + 4,0,local_c4);
      }
    }
    if (DAT_005dc648 != 0) {
      local_f4 = ((int)DAT_00630a3c + (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2)) -
                 *(int *)(in_ECX + 0xc);
      local_f8 = (int)DAT_00630a3e - *(int *)(in_ECX + 0x10);
      FUN_00472ca0(local_54,s_World_Pos___d__d__0049f988,local_f4,local_f8);
      thunk_FUN_004289ec(in_ECX + 8,300,0,local_54,2);
    }
    DAT_005dc68c = DAT_005dc68c + 1;
    if (600 < DAT_005dc68c) {
      FUN_00474b90();
      iVar3 = __ftol();
      if (iVar3 == 0) {
        DAT_005dc68c = 0;
        FUN_00474b90();
        local_fc = __ftol();
        if (*(int *)(&DAT_005dc690 + local_fc * 4) == 0) {
          for (local_100 = 0; local_100 < 0x15; local_100 = local_100 + 1) {
            FUN_00472ca0(local_10c,s_cryptic_d_0049f99c,local_100);
            uVar4 = thunk_FUN_00429ebe();
            *(undefined4 *)(&DAT_005dc690 + local_100 * 4) = uVar4;
          }
        }
        else {
          thunk_FUN_00436e06(*(undefined4 *)(&DAT_005dc690 + local_fc * 4),1);
        }
      }
    }
    thunk_FUN_00436ea8();
    local_5c = thunk_FUN_00436f3f();
    if (local_5c != 0) {
      local_110 = 7;
      if (*(short *)(local_5c + 0x3e) < 0x32) {
        local_110 = (int)*(short *)(local_5c + 0x3e) / 2;
      }
      else if (*(short *)(local_5c + 0x40) + -0x32 < (int)*(short *)(local_5c + 0x3e)) {
        local_110 = ((int)*(short *)(local_5c + 0x40) - (int)*(short *)(local_5c + 0x3e)) / 2;
      }
      if (local_110 < 0) {
        local_110 = 0;
      }
      if (7 < local_110) {
        local_110 = 7;
      }
      thunk_FUN_00411033(in_ECX + 8,DAT_004c2f30,local_5c,0xf,0x127,(int)*(short *)(local_5c + 0x3c)
                         ,local_110);
    }
    if (DAT_005dc664 != 0) {
      thunk_FUN_00432c74();
    }
    if (DAT_005dc66c != 0) {
      if (*(int *)(in_ECX + 0x170) == 0) {
        FUN_00472da0(local_54,s_No_selected_floater_0049f9b0);
      }
      else {
        FUN_00472ca0(local_54,s__s___s_0049f9a8,
                     s_FA_Nothing_0049d0b8 + *(int *)(*(int *)(in_ECX + 0x170) + 0x3c) * 0x10,
                     s_FA_Nothing_0049d0b8 + *(int *)(*(int *)(in_ECX + 0x170) + 0x2c) * 0x10);
      }
      thunk_FUN_004289c0(in_ECX + 8,0x14,0x14,local_54);
    }
    if (DAT_0049e9c4 != -1) {
      iVar3 = thunk_FUN_0040ec89(s_triggers_0049f9c4,1);
      if (iVar3 == 0) {
        thunk_FUN_00414b64(s_C__float_src_islewin_cpp_0049f9d8,0x8a0,&DAT_0049f9d0);
      }
      thunk_FUN_00404770(in_ECX + 8,iVar3,DAT_0049e9c4 + -5,DAT_00630a3c + 10,(int)DAT_00630a3e);
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,1);
  }
  return;
}
```

---

## FUN_00436dc8 — 0x436dc8

- Classification : internal
- Corps : `0x436dc8–0x436df8`
- État : pseudocode obtenu
- Evidence : `ev_bb1302dce3359104d4cce542e03434e9ad015f849846a3293fb82177a475b2a2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x49f9f4` — "IsleWindow draw_hilited got called.\n"
- `0x49fa1c` — "FALSE"
- `0x49fa24` — "C:\\float\\src\\islewin.cpp"

### Pseudocode Ghidra

```c
void FUN_00436dc8(void)

{
  thunk_FUN_00414ad0(s_IsleWindow_draw_hilited_got_call_0049f9f4);
  thunk_FUN_00414b64(s_C__float_src_islewin_cpp_0049fa24,0x8b2,s_FALSE_0049fa1c);
  return;
}
```

---

## FUN_00436df9 — 0x436df9

- Classification : internal
- Corps : `0x436df9–0x436e05`
- État : pseudocode obtenu
- Evidence : `ev_85e3ae19ac5167b9ad8085e61ea16be962e8ee10f70cab70fd16bf3ae6519dec`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00436df9(void)

{
  return;
}
```

---

## FUN_00436e06 — 0x436e06

- Classification : internal
- Corps : `0x436e06–0x436ea7`
- État : pseudocode obtenu
- Evidence : `ev_ca91ee5621d213bb1283aea55835b7876dd881dcb7645fa8cb769fd436a8acf6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`
- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`

### Chaînes référencées

- `0x49fa40` — "len < 60"
- `0x49fa4c` — "C:\\float\\src\\islewin.cpp"

### Pseudocode Ghidra

```c
void FUN_00436e06(char *param_1,undefined2 param_2)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (DAT_005dc6e4 < 10) {
    sVar2 = _strlen(param_1);
    if ((int)sVar2 < 0x3c) {
      uVar4 = 0;
    }
    else {
      uVar4 = thunk_FUN_00414b64(s_C__float_src_islewin_cpp_0049fa4c,0x8c7,s_len_<_60_0049fa40);
    }
    iVar1 = DAT_005dc6e4;
    iVar3 = DAT_005dc6e4 * 0x42;
    FUN_00472da0(&DAT_005dc3b0 + iVar3,param_1,uVar4);
    *(undefined2 *)(&DAT_005dc3ec + iVar3) = param_2;
    (&DAT_005dc3ee)[iVar1 * 0x21] = 0;
    (&DAT_005dc3f0)[iVar1 * 0x21] = (short)sVar2 * 2 + 0x3c;
    DAT_005dc6e4 = DAT_005dc6e4 + 1;
  }
  return;
}
```

---

## FUN_00436ea8 — 0x436ea8

- Classification : internal
- Corps : `0x436ea8–0x436f3e`
- État : pseudocode obtenu
- Evidence : `ev_f68fa2c50e5d3cf6aca6b4c50d2780bc557f83fecc6bf824984a279c6ba5e81d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00436ea8(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int local_c;
  
  if ((DAT_005dc6e4 != 0) && (DAT_005dc3ee = DAT_005dc3ee + 1, DAT_005dc3f0 <= DAT_005dc3ee)) {
    for (local_c = 0; local_c < DAT_005dc6e4 + -1; local_c = local_c + 1) {
      puVar2 = (undefined4 *)(&DAT_005dc3b0 + (local_c + 1) * 0x42);
      puVar3 = (undefined4 *)(&DAT_005dc3b0 + local_c * 0x42);
      for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
        *puVar3 = *puVar2;
        puVar2 = puVar2 + 1;
        puVar3 = puVar3 + 1;
      }
      *(undefined2 *)puVar3 = *(undefined2 *)puVar2;
    }
    DAT_005dc6e4 = DAT_005dc6e4 + -1;
  }
  return;
}
```

---

## FUN_00436f3f — 0x436f3f

- Classification : internal
- Corps : `0x436f3f–0x436f55`
- État : pseudocode obtenu
- Evidence : `ev_a7c698c8cf67c2e5f2c314bf931b91913c7e2438e6eb05f154183f57ba8aec0f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_00436f3f(void)

{
  undefined *puVar1;
  
  if (DAT_005dc6e4 < 1) {
    puVar1 = (undefined *)0x0;
  }
  else {
    puVar1 = &DAT_005dc3b0;
  }
  return puVar1;
}
```

---

## FUN_004380e0 — 0x4380e0

- Classification : internal
- Corps : `0x4380e0–0x43810d`
- État : pseudocode obtenu
- Evidence : `ev_382d996567015af78a3031065e5f14582a0794e23b1bdd9037c2bfcf90e88b2e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40177b` — `thunk_FUN_0043370b`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004380e0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0043370b();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_00438120 — 0x438120

- Classification : internal
- Corps : `0x438120–0x4381a1`
- État : pseudocode obtenu
- Evidence : `ev_9db51b636f16705e20a38936c1e741f9f9048cf2d6f93d3bd0a1c771ec59a0a7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00438120(int param_1)

{
  int iVar1;
  int local_c;
  
  for (local_c = 0; local_c < 9; local_c = local_c + 1) {
    if (*(int *)(&DAT_005e16b0 + local_c * 4) == param_1) {
      return;
    }
  }
  local_c = DAT_005e16a8 * 3;
  iVar1 = local_c + 3;
  while( true ) {
    if (iVar1 <= local_c) {
      return;
    }
    if (*(int *)(&DAT_005e16b0 + local_c * 4) == 0) break;
    local_c = local_c + 1;
  }
  *(int *)(&DAT_005e16b0 + local_c * 4) = param_1;
  return;
}
```

---

## FUN_004381a2 — 0x4381a2

- Classification : internal
- Corps : `0x4381a2–0x4381e0`
- État : pseudocode obtenu
- Evidence : `ev_5364bbe379e3f0fdba385586dd726957d5a7a88e6cc2b73be9e126a8737fb484`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004381a2(int param_1)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 9; local_8 = local_8 + 1) {
    if (*(int *)(&DAT_005e16b0 + local_8 * 4) == param_1) {
      *(undefined4 *)(&DAT_005e16b0 + local_8 * 4) = 0;
    }
  }
  return;
}
```

---

## FUN_004381e1 — 0x4381e1

- Classification : internal
- Corps : `0x4381e1–0x43822a`
- État : pseudocode obtenu
- Evidence : `ev_c9282b52c73cceabf3ff26f5a286032393a232d3c3942c797ce7e6073aeaa4ff`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49fb70` — "slot<TOTALCLIPS"
- `0x49fb80` — "C:\\float\\src\\islewin2.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_004381e1(int param_1)

{
  param_1 = DAT_005e16a8 * 3 + param_1;
  if (8 < param_1) {
    thunk_FUN_00414b64(s_C__float_src_islewin2_cpp_0049fb80,0x75,s_slot<TOTALCLIPS_0049fb70);
  }
  return *(undefined4 *)(&DAT_005e16b0 + param_1 * 4);
}
```

---

## FUN_0043822b — 0x43822b

- Classification : internal
- Corps : `0x43822b–0x438278`
- État : pseudocode obtenu
- Evidence : `ev_980a1572db041f1717349e6c785ef1fccdbe524ac79403f0e26889b26942726f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x49fb9c` — "slot<TOTALCLIPS"
- `0x49fbac` — "C:\\float\\src\\islewin2.cpp"

### Pseudocode Ghidra

```c
void FUN_0043822b(int param_1)

{
  param_1 = DAT_005e16a8 * 3 + param_1;
  if (8 < param_1) {
    thunk_FUN_00414b64(s_C__float_src_islewin2_cpp_0049fbac,0x7d,s_slot<TOTALCLIPS_0049fb9c);
  }
  *(undefined4 *)(&DAT_005e16b0 + param_1 * 4) = 0;
  return;
}
```

---

## FUN_00438279 — 0x438279

- Classification : internal
- Corps : `0x438279–0x438297`
- État : pseudocode obtenu
- Evidence : `ev_4a42b2b5984917cc9078a6bb1c54c92b9671c66557171e14cfe09bb08c75053f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00438279(void)

{
  undefined4 *in_ECX;
  
  thunk_FUN_00429243();
  *in_ECX = &PTR_LAB_004942f0;
  return in_ECX;
}
```

---

## FUN_00438298 — 0x438298

- Classification : internal
- Corps : `0x438298–0x4382b3`
- État : pseudocode obtenu
- Evidence : `ev_98e3aa08090f8cd442c9915b4abaf13e191f26c1e92b05a4a3564dff51dccbcd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00438298(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004942f0;
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_004382b4 — 0x4382b4

- Classification : internal
- Corps : `0x4382b4–0x4382be`
- État : pseudocode obtenu
- Evidence : `ev_ec0b3b22726c1161d4b1119a381495c784add2b175f6c7b16da80eb5f1017987`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004382b4(void)

{
  return;
}
```

---

## FUN_004382bf — 0x4382bf

- Classification : internal
- Corps : `0x4382bf–0x438378`
- État : pseudocode obtenu
- Evidence : `ev_d76d5d142cd6742eda6053d7505f16a91fab0cc698a813d1ac03fba45044c5ac`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40146f` — `thunk_FUN_0042d87c`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401d34` — `thunk_FUN_00438379`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x402022` — `thunk_FUN_00406604`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004382bf(short param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 uVar1;
  undefined4 uVar2;
  int in_ECX;
  
  if (5 < param_1) {
    if (param_1 < 8) {
      if ((*(int *)(in_ECX + 4) == DAT_0062c6bc) && (*(int *)(in_ECX + 0x38) != 0)) {
        uVar2 = thunk_FUN_00438379(param_1,param_2,param_3);
        return uVar2;
      }
    }
    else if (param_1 == 0x33) {
      uVar2 = thunk_FUN_0042d28f();
      *(undefined4 *)(in_ECX + 8) = uVar2;
      uVar1 = thunk_FUN_0042dd0f(0);
      thunk_FUN_00406604(in_ECX + 8,uVar1);
      thunk_FUN_0042d38a();
      thunk_FUN_0042d87c(in_ECX + 8,1);
      return 1;
    }
  }
  uVar2 = thunk_FUN_004293c6(param_1,param_2,param_3);
  return uVar2;
}
```

---


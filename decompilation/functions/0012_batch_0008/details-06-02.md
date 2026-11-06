# 0012_batch_0008 — détails (2/3)

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

# 0012_batch_0008 — détails (8/8)

## FUN_00439673 — 0x439673

- Classification : internal
- Corps : `0x439673–0x439f07`
- État : pseudocode obtenu
- Evidence : `ev_45fa9501196d329d11ea55b4b6cd052663e870a194f980cb444488b0704663af`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x401294` — `thunk_FUN_004289ec`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x401712` — `thunk_FUN_004289a7`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402004` — `thunk_FUN_0045d8f4`
- `0x402022` — `thunk_FUN_00406604`
- `0x4021ad` — `thunk_FUN_004641de`
- `0x40222a` — `thunk_FUN_00429e69`
- `0x402234` — `thunk_FUN_0042892d`
- `0x4022fc` — `thunk_FUN_00428baa`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49fca4` — "SEAL%02d"
- `0x49fcb0` — "NEWGAME%d"
- `0x49fcbc` — "LEVNAME"
- `0x49fccc` — "C:\\float\\src\\islewin2.cpp"
- `0x49fce8` — "BRIDGE%02d"
- `0x49fcf4` — "PLOT%02d"
- `0x49fd00` — "BRIDGE"
- `0x49fd10` — "POOLINFECT"
- `0x49fd1c` — "SUPPLY%d"
- `0x49fd28` — "PRIMEPOOL"
- `0x49fd34` — "FEAT%02d"
- `0x49fd40` — "GLYPH%02d"
- `0x49fd4c` — "BRIDGE%02d"
- `0x49fd58` — "PLOT%02d"
- `0x49fd64` — "pIMIsleWindow"
- `0x49fd74` — "C:\\float\\src\\islewin2.cpp"
- `0x49fd90` — "LEVEL"
- `0x49fd98` — "(%s %d)"
- `0x49fda0` — "COLLART"
- `0x49fda8` — "GLYSTONE"
- `0x49fdb4` — "TRIDIP"
- `0x49fdbc` — "TRIASS"
- `0x49fdcc` — "C:\\float\\src\\islewin2.cpp"

### Pseudocode Ghidra

```c
void FUN_00439673(void)

{
  int iVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int in_ECX;
  int iVar6;
  undefined2 extraout_var;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined1 local_8c [16];
  int local_7c;
  int local_78;
  undefined4 local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  undefined1 local_58 [12];
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  undefined1 local_38 [32];
  int local_18;
  int local_14;
  int local_10;
  uint local_c;
  int local_8;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    uVar3 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar3;
    if (DAT_004c2bac == 0) {
      thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
    }
    else {
      uVar8 = 0;
      uVar7 = 0;
      iVar6 = (int)*(short *)(in_ECX + 0x1e);
      uVar3 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar3,iVar6,uVar7,uVar8);
    }
    local_14 = 0;
    uVar2 = thunk_FUN_0042dd0f(6);
    local_c = CONCAT31(local_c._1_3_,uVar2);
    local_18 = 10;
    local_3c = 6;
    local_44 = 1;
    local_40 = thunk_FUN_0042de0d();
    local_8 = thunk_FUN_0042de03();
    local_10 = local_40;
    switch(*(undefined4 *)(in_ECX + 0x70)) {
    case 0:
      local_48 = *(int *)(in_ECX + 0x74);
      if (local_48 != 0) {
        if (*(int *)(local_48 + 4) == 0) {
          if ((*(int *)(local_48 + 0x10) < 0x17) || (0x24 < *(int *)(local_48 + 0x10))) {
            if ((*(int *)(local_48 + 0x10) == 0) || (*(int *)(local_48 + 0x10) == 1)) {
              if (3 < *(int *)(local_48 + 0x24)) {
                local_68 = *(int *)(local_48 + 0x24);
                if (local_68 < 6) {
                  FUN_00472ca0(local_38,s_BRIDGE_02d_0049fce8,local_68 + -5);
                }
                else {
                  FUN_00472ca0(local_38,s_PLOT_02d_0049fcf4,local_68 + -6);
                }
                local_14 = thunk_FUN_00429ebe(local_38,0);
              }
            }
            else {
              iVar6 = thunk_FUN_004641de(*(undefined4 *)(local_48 + 0x14),
                                         *(undefined4 *)(local_48 + 0x10),0);
              local_14 = thunk_FUN_00429ebe(iVar6 + 0x18);
              if ((*(int *)(local_48 + 0x10) == 0x2a) && (*(int *)(local_48 + 0x14) != DAT_0049f538)
                 ) {
                FUN_00472ca0(local_58,s_NEWGAME_d_0049fcb0,*(undefined4 *)(local_48 + 0x14));
                local_14 = thunk_FUN_00429ebe(local_58,0);
                if (local_14 != 0) {
                  local_44 = 0;
                  iVar6 = *(int *)(in_ECX + 0x14);
                  iVar1 = *(int *)(in_ECX + 0xc);
                  iVar4 = thunk_FUN_0042892d(local_14,0xffffffff,0xffffffff);
                  local_18 = ((iVar6 - iVar1) - iVar4) / 2;
                  local_3c = (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) / 2 + -10;
                }
              }
              if ((local_14 == 0) && (*(int *)(local_48 + 0x14) == 4)) {
                local_64 = thunk_FUN_00429ebe(s_LEVNAME_0049fcbc,&local_60);
                if (local_64 == 0) {
                  thunk_FUN_00414b64(s_C__float_src_islewin2_cpp_0049fccc,0x36f,&DAT_0049fcc4);
                }
                local_5c = *(int *)(local_48 + 0x10) + -5;
                local_14 = thunk_FUN_00429e69(local_60 + local_5c,1);
                if (local_14 != 0) {
                  local_44 = 0;
                  iVar6 = *(int *)(in_ECX + 0x14);
                  iVar1 = *(int *)(in_ECX + 0xc);
                  iVar4 = thunk_FUN_0042892d(local_14,0xffffffff,0xffffffff);
                  local_18 = ((iVar6 - iVar1) - iVar4) / 2;
                  local_3c = (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) / 2 + -10;
                }
              }
            }
          }
          else {
            local_4c = *(int *)(local_48 + 0x10) + -0x17;
            FUN_00472ca0(local_38,s_SEAL_02d_0049fca4,local_4c);
            local_14 = thunk_FUN_00429ebe(local_38,0);
          }
        }
        else if (*(int *)(local_48 + 4) == 2) {
          local_14 = thunk_FUN_00429ebe(s_BRIDGE_0049fd00,0);
        }
        else if (*(int *)(local_48 + 4) == 1) {
          local_14 = thunk_FUN_00429ebe(&DAT_0049fd08,0);
          if (*(int *)(local_48 + 0x14) == 4) {
            if (*(int *)(local_48 + 0x10) == 5) {
              local_14 = thunk_FUN_00429ebe(s_POOLINFECT_0049fd10,0);
            }
            else {
              local_6c = *(int *)(local_48 + 0x10) + -6;
              FUN_00472ca0(local_38,s_SUPPLY_d_0049fd1c,local_6c);
              local_14 = thunk_FUN_00429ebe(local_38,0);
            }
          }
          else if (((int)*(char *)(local_48 + 0x22) & 1 << ((byte)DAT_0049f538 & 0x1f)) != 0) {
            local_14 = thunk_FUN_00429ebe(s_PRIMEPOOL_0049fd28,0);
          }
        }
        else if ((*(int *)(local_48 + 4) == 3) &&
                (local_70 = (int)(short)(&DAT_005eebf8)[*(short *)(local_48 + 8) * 0x14f4],
                local_70 < 0xe)) {
          FUN_00472ca0(local_38,s_FEAT_02d_0049fd34,local_70);
          local_14 = thunk_FUN_00429ebe(local_38,0);
        }
      }
      break;
    case 1:
      FUN_00472ca0(local_38,s_GLYPH_02d_0049fd40,*(undefined4 *)(in_ECX + 0x74));
      local_14 = thunk_FUN_00429ebe(local_38,0);
      break;
    case 2:
      if (*(int *)(in_ECX + 0x74) < 6) {
        FUN_00472ca0(local_38,s_BRIDGE_02d_0049fd4c,*(int *)(in_ECX + 0x74) + -5);
      }
      else {
        FUN_00472ca0(local_38,s_PLOT_02d_0049fd58,*(int *)(in_ECX + 0x74) + -6);
      }
      local_14 = thunk_FUN_00429ebe(local_38,0);
      break;
    case 3:
      if (-1 < *(int *)(in_ECX + 0x74)) {
        iVar6 = thunk_FUN_004641de(DAT_0049f538,*(undefined4 *)(in_ECX + 0x74),0);
        local_14 = thunk_FUN_00429ebe(iVar6 + 0x18);
      }
      break;
    case 4:
      local_18 = 10;
      local_3c = 2;
      thunk_FUN_004289ec(in_ECX + 8,10,2,&DAT_006188c0 + *(int *)(in_ECX + 0x74) * 0x2c,0);
      if (DAT_005c37e4 == 0) {
        thunk_FUN_00414b64(s_C__float_src_islewin2_cpp_0049fd74,0x3c3,s_pIMIsleWindow_0049fd64);
      }
      local_7c = *(int *)(DAT_005c37e4 + 0x16c);
      if (((local_7c != 0) && (iVar6 = thunk_FUN_00450385(), iVar6 != 0)) &&
         (iVar6 = thunk_FUN_0045d8f4(CONCAT22(extraout_var,*(undefined2 *)(in_ECX + 0x74))),
         iVar6 < 0)) {
        uVar5 = thunk_FUN_0042dd0f(2);
        *(uint *)(local_10 + 8) = uVar5 & 0xff;
      }
      local_74 = thunk_FUN_00429ebe(s_LEVEL_0049fd90,0);
      FUN_00472ca0(local_8c,s___s__d__0049fd98,local_74,
                   *(short *)(&DAT_006188e0 + *(int *)(in_ECX + 0x74) * 0x2c) + 1);
      local_18 = 10;
      local_3c = 0xb;
      thunk_FUN_004289ec(in_ECX + 8,10,0xb,local_8c,0);
      uVar5 = thunk_FUN_0042dd0f(6);
      *(uint *)(local_10 + 8) = uVar5 & 0xff;
      local_14 = 0;
      local_78 = *(int *)(&DAT_006188e8 + *(int *)(in_ECX + 0x74) * 0x2c);
      if (local_78 != 0) {
        local_14 = thunk_FUN_00429e69(local_78,0);
        local_18 = 10;
        iVar6 = thunk_FUN_004289a7();
        local_3c = local_3c + 2 + iVar6;
      }
      break;
    case 5:
      local_14 = *(int *)(&DAT_0049e948 + *(int *)(in_ECX + 0x74) * 4);
      local_3c = (*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) / 2 + -10;
      local_10 = local_8;
      if (local_14 != 0) {
        iVar6 = *(int *)(in_ECX + 0x14);
        iVar1 = *(int *)(in_ECX + 0xc);
        iVar4 = thunk_FUN_0042892d(local_14,0xffffffff,0xffffffff);
        local_18 = ((iVar6 - iVar1) - iVar4) / 2;
      }
      local_44 = 0;
      break;
    case 6:
      local_14 = thunk_FUN_00429ebe(s_COLLART_0049fda0,0);
      break;
    case 7:
      local_14 = thunk_FUN_00429ebe(s_GLYSTONE_0049fda8,0);
      break;
    case 8:
      local_14 = thunk_FUN_00429ebe(s_TRIDIP_0049fdb4,0);
      break;
    case 9:
      local_14 = thunk_FUN_00429ebe(s_TRIASS_0049fdbc,0);
    }
    if (local_14 != 0) {
      if (local_10 == 0) {
        thunk_FUN_00414b64(s_C__float_src_islewin2_cpp_0049fdcc,0x401,&DAT_0049fdc4);
      }
      *(uint *)(local_10 + 8) = local_c & 0xff;
      if (local_44 == 0) {
        thunk_FUN_004289c0(in_ECX + 8,local_18,local_3c,local_14);
      }
      else {
        thunk_FUN_00428baa(in_ECX + 8,local_18,local_3c,local_14,0,&LAB_0040132f);
      }
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,3);
    *(undefined4 *)(in_ECX + 0x34) = 0;
  }
  return;
}
```

---

## FUN_00439f30 — 0x439f30

- Classification : internal
- Corps : `0x439f30–0x439f83`
- État : pseudocode obtenu
- Evidence : `ev_b128fb9399c8f935f515883a337498283217ffb0781699c4be6a695db3d1bfe2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401415` — `thunk_FUN_00439fa0`
- `0x401cdf` — `thunk_FUN_00429f65`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00439f30(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049173f;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429f65();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494368;
  thunk_FUN_00439fa0();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_00439f84 — 0x439f84

- Classification : internal
- Corps : `0x439f84–0x439f9f`
- État : pseudocode obtenu
- Evidence : `ev_32e66b58c457859dd6267305ef3c77a63a2f989b2b491a7ab00d93a85c7b863b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4022f7` — `thunk_FUN_00429fb9`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00439f84(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494368;
  thunk_FUN_00429fb9();
  return;
}
```

---

## FUN_00439fa0 — 0x439fa0

- Classification : internal
- Corps : `0x439fa0–0x439fbc`
- État : pseudocode obtenu
- Evidence : `ev_e315e9c6e49a3552eaf8a0d527204dbd1fa7cdd51ec917b81f5f6b4faaeb2383`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00439fa0(void)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x70) = 8;
  *(undefined2 *)(in_ECX + 0x72) = 1;
  return;
}
```

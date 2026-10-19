# 0014_batch_0010 — détails (1/2)

## FUN_00445739 — 0x445739

- Classification : internal
- Corps : `0x445739–0x44590c`
- État : pseudocode obtenu
- Evidence : `ev_376d7136d35549ab086527f2d39caa01cf5a16bf4001b0c5e6d0a7288aec14a0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00445739(void)

{
  int in_ECX;
  
  if (*(short *)(in_ECX + 0xf8) < *(short *)(in_ECX + 0xf0)) {
    if ((*(short *)(in_ECX + 0xfa) < 1) || (*(int *)(in_ECX + 0x100) != 0)) {
      if ((*(int *)(in_ECX + 0x100) != 0) && (*(short *)(in_ECX + 0xfa) == 0)) {
        thunk_FUN_0046c371((int)*(short *)(in_ECX + 0xfc),2,0,0);
        *(undefined4 *)(in_ECX + 0x100) = 0;
      }
    }
    else {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0xfc),1,0,0);
      *(undefined4 *)(in_ECX + 0x100) = 1;
    }
    if (((int)*(short *)(in_ECX + 0xfa) <
         (int)*(short *)(in_ECX + 0xf0) - (int)*(short *)(in_ECX + 0xf8)) &&
       (*(int *)(in_ECX + 0x104) == 0)) {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0xfe),1,0,0);
      *(undefined4 *)(in_ECX + 0x104) = 1;
    }
    else if ((*(int *)(in_ECX + 0x104) != 0) &&
            ((int)*(short *)(in_ECX + 0xf0) - (int)*(short *)(in_ECX + 0xf8) <=
             (int)*(short *)(in_ECX + 0xfa))) {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0xfe),2,0,0);
      *(undefined4 *)(in_ECX + 0x104) = 0;
    }
  }
  else {
    *(undefined2 *)(in_ECX + 0xfa) = 0;
    if (*(int *)(in_ECX + 0x100) != 0) {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0xfc),2,0,0);
      *(undefined4 *)(in_ECX + 0x100) = 0;
    }
    if (*(int *)(in_ECX + 0x104) != 0) {
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0xfe),2,0,0);
      *(undefined4 *)(in_ECX + 0x104) = 0;
    }
  }
  return;
}
```

---

---

## FUN_0044590d — 0x44590d

- Classification : internal
- Corps : `0x44590d–0x4459e5`
- État : pseudocode obtenu
- Evidence : `ev_1ad82582cd763f0b2b6f4f4b140e7718bd31d5172c939858c64c7b69a2269ab3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018e3` — `thunk_FUN_0046c3bc`

### Chaînes référencées

- `0x4a0f98` — "IWTaskOptions"
- `0x4a0fa8` — "IWTaskInfo"

### Pseudocode Ghidra

```c
undefined4 FUN_0044590d(undefined4 param_1,int param_2)

{
  int in_ECX;
  int local_8;
  
  local_8 = ((param_2 - *(int *)(in_ECX + 0x10)) -
            ((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) + *(short *)(in_ECX + 0xf8) * -0xd)
            / 2) / 0xd + (int)*(short *)(in_ECX + 0xfa);
  if (local_8 < 0) {
    local_8 = 0;
  }
  if (local_8 < *(short *)(in_ECX + 0xf0)) {
    *(undefined4 *)(in_ECX + 0xf4) = *(undefined4 *)(in_ECX + 0x70 + local_8 * 4);
    thunk_FUN_0046c3bc(s_IWTaskOptions_004a0f98,0x13ba,*(undefined4 *)(in_ECX + 0xf4),0);
    thunk_FUN_0046c3bc(s_IWTaskInfo_004a0fa8,0x13ba,*(undefined4 *)(in_ECX + 0xf4),0);
  }
  return 1;
}
```

---

---

## FUN_004459e6 — 0x4459e6

- Classification : internal
- Corps : `0x4459e6–0x446461`
- État : pseudocode obtenu
- Evidence : `ev_fe6bd972740d099ab62aab1ef94df71e686f886cba296a0ba805cba982259d2f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x40119a` — `thunk_FUN_0045ff6d`
- `0x40119f` — `thunk_FUN_0046c371`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x4014e7` — `thunk_FUN_0045035a`
- `0x4016ea` — `thunk_FUN_004118df`
- `0x40174e` — `thunk_FUN_004109a6`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x40181b` — `thunk_FUN_00450978`
- `0x4018b6` — `thunk_FUN_0045ff3f`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020bd` — `thunk_FUN_0045c9fe`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x4021ad` — `thunk_FUN_004641de`
- `0x402306` — `thunk_FUN_004106dd`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402473` — `thunk_FUN_0045fcbe`
- `0x40248c` — `thunk_FUN_0045cd27`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49d0b8` — "FA_Nothing"
- `0x4a0fbc` — "C:\\float\\src\\iwtask.cpp"
- `0x4a0fd4` — "CONSTR"
- `0x4a0fdc` — "REPAIR"
- `0x4a0fe4` — "REPAIR"
- `0x4a0ff0` — "C:\\float\\src\\iwtask.cpp"
- `0x4a1008` — "UPGSPREAD"
- `0x4a1014` — "UPGRADE"
- `0x4a101c` — "bildtone"
- `0x4a1028` — "SUPPLY"
- `0x4a1030` — "tonecrys"
- `0x4a103c` — "magctone"
- `0x4a1048` — "STOCK"
- `0x4a1050` — "bildtone"
- `0x4a105c` — "tonecrys"
- `0x4a1068` — "magctone"
- `0x4a1074` — "DARTIFACT"
- `0x4a1080` — "OARTIFACT"
- `0x4a108c` — "taskicon"
- `0x4a1098` — "shape"
- `0x4a10a0` — "C:\\float\\src\\iwtask.cpp"

### Pseudocode Ghidra

```c
void FUN_004459e6(void)

{
  short sVar1;
  undefined1 uVar2;
  short sVar3;
  short sVar4;
  undefined4 uVar5;
  uint uVar6;
  int in_ECX;
  int iVar7;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  int iVar8;
  int *piVar9;
  int *piVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  short local_d2;
  undefined8 local_c4;
  int local_a8 [4];
  int local_98;
  undefined4 local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  char *local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  undefined4 local_5c;
  undefined1 local_58 [80];
  int local_8;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    uVar5 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar5;
    if (DAT_004c2bac == 0) {
      thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
    }
    else {
      uVar12 = 0;
      uVar11 = 0;
      iVar7 = (int)*(short *)(in_ECX + 0x1e);
      uVar5 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar5,iVar7,uVar11,uVar12);
    }
    local_7c = thunk_FUN_0042de0d();
    if (local_7c == 0) {
      thunk_FUN_00414b64(s_C__float_src_iwtask_cpp_004a0fbc,0x14e,&DAT_004a0fb4);
    }
    local_84 = ((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) +
               *(short *)(in_ECX + 0xf8) * -0xd) / 2;
    local_68 = 0;
    local_60 = (int)*(short *)(in_ECX + 0xf0);
    if ((int)*(short *)(in_ECX + 0xfa) + (int)*(short *)(in_ECX + 0xf8) < local_60) {
      local_60 = (int)*(short *)(in_ECX + 0xfa) + (int)*(short *)(in_ECX + 0xf8);
    }
    for (local_80 = (int)*(short *)(in_ECX + 0xfa); local_80 < local_60; local_80 = local_80 + 1) {
      local_88 = *(int *)(in_ECX + 0x70 + local_80 * 4);
      if (*(int *)(in_ECX + 0xf4) == local_88) {
        local_90 = local_68 * 0xd + -3 +
                   ((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) +
                   *(short *)(in_ECX + 0xf8) * -0xd) / 2;
        piVar9 = (int *)(in_ECX + 8);
        piVar10 = local_a8;
        for (iVar7 = 5; iVar7 != 0; iVar7 = iVar7 + -1) {
          *piVar10 = *piVar9;
          piVar9 = piVar9 + 1;
          piVar10 = piVar10 + 1;
        }
        local_a8[2] = *(int *)(in_ECX + 0x10) + local_90;
        local_98 = local_a8[2] + 0xd;
        local_a8[3] = local_a8[3] + -0xd;
        uVar5 = thunk_FUN_004106dd(1,1);
        iVar8 = *(int *)(in_ECX + 0x10) - local_a8[2];
        uVar12 = 0;
        iVar7 = (int)*(short *)(in_ECX + 0x1e);
        local_94 = uVar5;
        uVar11 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
        thunk_FUN_004109a6(local_a8,uVar11,iVar7,uVar12,iVar8,uVar5);
      }
      local_64 = -1;
      local_8 = -1;
      local_70 = -1;
      local_5c = 0xffffffff;
      local_6c = 0;
      local_78 = (char *)0x0;
      if (*(short *)(local_88 + 0x10) == 5) {
        iVar7 = thunk_FUN_004641de((int)*(short *)(local_88 + 8),(int)*(short *)(local_88 + 0x12));
        local_74 = (int)*(short *)(iVar7 + 4);
        local_64 = (int)*(short *)(&DAT_005ec668 +
                                  *(short *)(local_88 + 0xe) * 0x60 +
                                  *(short *)(local_88 + 10) * 0x29e8);
        local_8 = 0;
        local_78 = (char *)thunk_FUN_00429ebe(s_CONSTR_004a0fd4,0);
      }
      else if (*(short *)(local_88 + 0x10) == 0x12) {
        sVar4 = *(short *)(local_88 + 10);
        sVar1 = *(short *)(local_88 + 0xe);
        sVar3 = thunk_FUN_00450978();
        local_74 = (int)sVar3;
        local_64 = (int)*(short *)(sVar4 * 0x29e8 + sVar1 * 0x60 + 0x5ec674);
        local_8 = 1;
        local_78 = (char *)thunk_FUN_00429ebe(s_REPAIR_004a0fdc,0);
      }
      else if (*(short *)(local_88 + 0x10) == 4) {
        iVar7 = *(short *)(local_88 + 0xe) * 0x60 + *(short *)(local_88 + 10) * 0x29e8;
        if (*(short *)(local_88 + 0x12) == 1) {
          uVar5 = thunk_FUN_0045035a();
          iVar8 = thunk_FUN_0045ff3f(CONCAT22(extraout_var,
                                              *(undefined2 *)(&DAT_005ec640 + iVar7 + 8)),uVar5);
          if (iVar8 != 0) {
            sVar4 = *(short *)(local_88 + 10);
            sVar1 = *(short *)(local_88 + 0xe);
            sVar3 = thunk_FUN_00450978();
            local_74 = (int)sVar3;
            local_64 = (int)*(short *)(sVar4 * 0x29e8 + sVar1 * 0x60 + 0x5ec674);
            local_8 = 1;
            local_78 = (char *)thunk_FUN_00429ebe(s_REPAIR_004a0fe4,0);
            goto LAB_004461ea;
          }
        }
        if (*(short *)(local_88 + 0x12) == 1) {
          uVar5 = thunk_FUN_0045035a();
          iVar8 = thunk_FUN_0045ff6d(CONCAT22(extraout_var_00,
                                              *(undefined2 *)(&DAT_005ec640 + iVar7 + 8)),uVar5);
          if (iVar8 != 0) {
            uVar11 = 1;
            uVar5 = thunk_FUN_0045035a(1);
            iVar7 = thunk_FUN_0045fcbe(*(undefined2 *)(&DAT_005ec640 + iVar7 + 8),uVar5,uVar11);
            if (iVar7 == 0) {
              thunk_FUN_00414b64(s_C__float_src_iwtask_cpp_004a0ff0,0x19b,&DAT_004a0fec);
            }
            local_74 = 10;
            local_64 = (int)*(short *)(iVar7 + 8);
            local_8 = 2;
            local_78 = (char *)thunk_FUN_00429ebe(s_UPGSPREAD_004a1008,0);
            goto LAB_004461ea;
          }
        }
        iVar8 = thunk_FUN_00450385();
        if (iVar8 == 0) {
          if (*(int *)(&DAT_005ec640 + iVar7 + 0x10) == 0x2a) {
            local_74 = *(short *)(&DAT_005ec640 + iVar7 + 0x4a) * 0x32 + 0x96;
            local_8 = 3;
            local_78 = (char *)thunk_FUN_00429ebe(s_STOCK_004a1048,0);
            local_70 = 7;
            if (*(short *)(local_88 + 0x12) == 1) {
              local_64 = (int)*(short *)(&DAT_005ec640 + iVar7 + 0x28);
              local_6c = thunk_FUN_0040ec89(s_bildtone_004a1050,1);
            }
            else if (*(short *)(local_88 + 0x12) == 2) {
              local_64 = (int)*(short *)(&DAT_005ec640 + iVar7 + 0x2a);
              local_6c = thunk_FUN_0040ec89(s_tonecrys_004a105c,1);
            }
            else {
              local_64 = (int)*(short *)(&DAT_005ec640 + iVar7 + 0x2c);
              local_6c = thunk_FUN_0040ec89(s_magctone_004a1068,1);
            }
          }
          else if ((4 < *(short *)(local_88 + 0x12)) && (*(short *)(local_88 + 0x12) < 0x22)) {
            local_8 = 4;
            local_78 = (char *)thunk_FUN_00429ebe(s_DARTIFACT_004a1074,0);
          }
        }
        else {
          local_70 = (*(int *)(&DAT_005ec640 + iVar7 + 0x10) == 0x2f) + 5;
          iVar8 = thunk_FUN_0045c9fe();
          if ((iVar8 == 0) || (*(short *)(local_88 + 0x12) != 1)) {
            sVar4 = thunk_FUN_0045cd27();
            local_74 = (int)sVar4;
            if (*(short *)(local_88 + 0x12) == 2) {
              local_d2 = *(short *)(&DAT_005ec640 + iVar7 + 0x2a);
            }
            else {
              local_d2 = *(short *)(&DAT_005ec640 + iVar7 + 0x2c);
            }
            local_64 = (int)local_d2;
            local_8 = 3;
            local_78 = (char *)thunk_FUN_00429ebe(s_SUPPLY_004a1028,0);
            if (*(short *)(local_88 + 0x12) == 2) {
              local_64 = (int)*(short *)(&DAT_005ec640 + iVar7 + 0x2a);
              local_6c = thunk_FUN_0040ec89(s_tonecrys_004a1030,1);
            }
            else {
              local_64 = (int)*(short *)(&DAT_005ec640 + iVar7 + 0x2c);
              local_6c = thunk_FUN_0040ec89(s_magctone_004a103c,1);
            }
          }
          else {
            local_74 = 0x14;
            local_64 = (int)*(short *)(&DAT_005ec640 + iVar7 + 0x28);
            local_8 = 2;
            local_78 = (char *)thunk_FUN_00429ebe(s_UPGRADE_004a1014,0);
            local_6c = thunk_FUN_0040ec89(s_bildtone_004a101c,1);
          }
        }
      }
      else if (*(short *)(local_88 + 0x10) == 0xd) {
        local_8 = 4;
        local_78 = (char *)thunk_FUN_00429ebe(s_OARTIFACT_004a1080,0);
      }
      else {
        local_78 = s_FA_Nothing_0049d0b8 + *(short *)(local_88 + 0x10) * 0x10;
      }
LAB_004461ea:
      if (local_6c != 0) {
        thunk_FUN_00404770(in_ECX + 8,local_6c,0,0x87,local_84 + 7);
      }
      local_8c = thunk_FUN_0040ec89(s_taskicon_004a108c,1);
      if (local_8c == 0) {
        thunk_FUN_00414b64(s_C__float_src_iwtask_cpp_004a10a0,0x1f0,s_shape_004a1098);
      }
      if (local_8 != -1) {
        thunk_FUN_00404770(in_ECX + 8,local_8c,local_8,0x19,local_84);
      }
      if (local_70 != -1) {
        thunk_FUN_00404770(in_ECX + 8,local_8c,local_70,0x96,local_84);
      }
      if (local_64 != -1) {
        local_c4 = (double)local_64 / (double)local_74;
        if (1.0 < local_c4) {
          local_c4 = 1.0;
        }
        uVar2 = thunk_FUN_0042dd0f(0,(undefined4)local_c4,local_c4._4_4_,0);
        thunk_FUN_004118df(in_ECX + 8,local_8c,9,0xaa,local_84,0x46,7,2,uVar2);
      }
      if (*(short *)(local_88 + 6) == 2) {
        uVar6 = thunk_FUN_0042dd0f(5);
        *(uint *)(local_7c + 8) = uVar6 & 0xff;
      }
      else if (*(short *)(local_88 + 6) == 3) {
        uVar6 = thunk_FUN_0042dd0f(2);
        *(uint *)(local_7c + 8) = uVar6 & 0xff;
      }
      FUN_00472ca0(local_58,&DAT_004a10b8,(int)*(short *)(local_88 + 4));
      thunk_FUN_004289c0(in_ECX + 8,5,local_84,local_58);
      if (local_78 != (char *)0x0) {
        thunk_FUN_004289c0(in_ECX + 8,0x2d,local_84,local_78);
      }
      local_84 = local_84 + 0xd;
      local_68 = local_68 + 1;
      uVar6 = thunk_FUN_0042dd0f(6);
      *(uint *)(local_7c + 8) = uVar6 & 0xff;
    }
    thunk_FUN_0046c371((int)*(short *)(in_ECX + 0xfc),0xb,0,0);
    thunk_FUN_0046c371((int)*(short *)(in_ECX + 0xfe),0xb,0,0);
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,1);
  }
  return;
}
```

---

---

## FUN_00446462 — 0x446462

- Classification : internal
- Corps : `0x446462–0x446485`
- État : pseudocode obtenu
- Evidence : `ev_0155b4bd4f3c9069008d72ff81405b004a84dc3eba26db8c6ee4a93a77c53d87`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a10c0` — "FALSE"
- `0x4a10c8` — "C:\\float\\src\\iwtask.cpp"

### Pseudocode Ghidra

```c
void FUN_00446462(void)

{
  thunk_FUN_00414b64(s_C__float_src_iwtask_cpp_004a10c8,0x21e,s_FALSE_004a10c0);
  return;
}
```

---

---

## FUN_00446486 — 0x446486

- Classification : internal
- Corps : `0x446486–0x446492`
- État : pseudocode obtenu
- Evidence : `ev_a007324e36f43f62e03ad2b9253b6e930a028b3a5f26d2170a02f9bd5f7baa70`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00446486(void)

{
  return;
}
```

---

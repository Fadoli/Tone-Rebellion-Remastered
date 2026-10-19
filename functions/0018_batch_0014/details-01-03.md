# 0018_batch_0014 — détails (3/3)

## FUN_0046ae19 — 0x46ae19

- Classification : internal
- Corps : `0x46ae19–0x46b751`
- État : pseudocode obtenu
- Evidence : `ev_5f7ce4f254c4db6c64349b5391b74392190f664e9f8c4fa166b9a1248ee1c127`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401262` — `thunk_FUN_0045a4fa`
- `0x401424` — `thunk_FUN_0041072f`
- `0x401442` — `thunk_FUN_0041169f`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x40163b` — `thunk_FUN_00404c3b`
- `0x4017df` — `thunk_FUN_0041be72`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401f87` — `thunk_FUN_0041417a`
- `0x402086` — `thunk_FUN_00404c5a`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x40218a` — `thunk_FUN_00410765`
- `0x40229d` — `thunk_FUN_00405e11`
- `0x4022fc` — `thunk_FUN_00428baa`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472ca0` — `FUN_00472ca0`
- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a5560` — "wnd_index>=0"
- `0x4a5570` — "C:\\float\\src\\winman.cpp"
- `0x4a5588` — "mhwndFocus!=-1"
- `0x4a5598` — "C:\\float\\src\\winman.cpp"
- `0x4a55b8` — "tribe<MAX_TRIBES"
- `0x4a55cc` — "C:\\float\\src\\winman.cpp"
- `0x4a55e4` — "%s: %s"
- `0x4a55ec` — "Lost World Sync"
- `0x4a55fc` — "Lost Flt Sync"
- `0x4a560c` — "Lost Task Sync"
- `0x4a561c` — "Lost Island Sync"
- `0x4a5630` — "Lost WORLDRAND Sync"
- `0x4a5644` — "PAUSE"
- `0x4a564c` — "1.16F"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0046ae19(void)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  int in_ECX;
  undefined1 local_1f0 [32];
  undefined4 local_1d0;
  int local_1cc;
  int local_1c8;
  int local_1c4 [2];
  int local_1bc [2];
  int local_1b4;
  int local_1b0;
  size_t local_1ac;
  int local_1a8;
  int local_1a4;
  undefined1 local_1a0;
  undefined1 local_19c [256];
  int local_9c;
  undefined4 local_98;
  undefined4 local_94;
  int local_90;
  int *local_8c;
  short local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined1 local_70 [80];
  int local_20;
  int local_1c;
  int local_18;
  short local_14;
  undefined4 local_10;
  char *local_c;
  int local_8;
  
  if (-1 < *(short *)(in_ECX + 0x29f2)) {
    if ((*(int *)(in_ECX + 0x62b0) != 0) || (*(int *)(in_ECX + 0x62b4) < 0x100)) {
      thunk_FUN_00410765(in_ECX + 0x5fb0,0,0x100 - *(int *)(in_ECX + 0x62b4));
      *(int *)(in_ECX + 0x62b4) = *(int *)(in_ECX + 0x62b4) + 4;
      *(undefined4 *)(in_ECX + 0x62b0) = 0;
    }
    local_14 = *(short *)(in_ECX + 8000 + *(short *)(in_ECX + 0x29f2) * 0x130);
    local_10 = 0;
    for (local_88 = 0; local_88 < 0x4a; local_88 = local_88 + 1) {
      if (local_88 < 0) {
        thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5570,0x2ee,s_wnd_index>_0_004a5560);
      }
      local_8 = *(int *)(in_ECX + *(short *)(in_ECX + 0x29f2) * 0x130 + 0x1f44 + local_88 * 4);
      if (local_8 != 0) {
        local_14 = local_14 + -1;
        local_8c = *(int **)(in_ECX + 4 + local_8 * 0xc);
        if (local_8c[0xd] != 0) {
          (**(code **)(*local_8c + 8))(0);
        }
      }
      if (local_14 == 0) break;
    }
    local_80 = 0;
    local_7c = 0;
    local_78 = 0x27f;
    local_74 = 0x1df;
    local_84 = thunk_FUN_0042d28f();
    _DAT_004c2f38 = thunk_FUN_0042dd0f(6);
    _DAT_004c2f38 = _DAT_004c2f38 & 0xff;
    if (*(int *)(in_ECX + 0x6314) != 0) {
      if (*(int *)(in_ECX + 0x1f3c) == -1) {
        thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5598,0x306,s_mhwndFocus___1_004a5588);
      }
      local_90 = *(int *)(in_ECX + 4 + *(int *)(in_ECX + 0x1f3c) * 0xc);
      uVar1 = thunk_FUN_0042dd0f(1,0,0xffffffff);
      thunk_FUN_0041169f(&local_84,*(undefined4 *)(local_90 + 0xc),*(undefined4 *)(local_90 + 0x10),
                         *(undefined4 *)(local_90 + 0x14),*(undefined4 *)(local_90 + 0x18),uVar1);
    }
    if (*(int *)(in_ECX + 0x62c0) != 0) {
      FUN_00472ca0(local_70,&DAT_004a55b0,in_ECX + 0x62c4);
      thunk_FUN_004289c0(&local_84,1,300,local_70);
    }
    if (DAT_00630ab0 != 0) {
      _memset(local_19c,0,0xff);
      for (local_9c = 0x20; local_9c < 0xe2; local_9c = local_9c + 1) {
        *(undefined1 *)((int)local_1bc + local_9c) = (undefined1)local_9c;
      }
      local_98 = thunk_FUN_0042de03();
      local_94 = thunk_FUN_0042de0d();
      local_1a0 = local_19c[0x46];
      local_19c[0x46] = 0;
      thunk_FUN_004289c0(&local_84,5,0x14,local_19c);
      thunk_FUN_004289c0(&local_84,5,0x5a,local_19c);
      thunk_FUN_004289c0(&local_84,5,0xa0,local_19c);
      local_19c[0x46] = local_1a0;
      local_1a0 = local_19c[0x8c];
      local_19c[0x8c] = 0;
      thunk_FUN_004289c0(&local_84,5,0x28,local_19c + 0x46);
      thunk_FUN_004289c0(&local_84,5,0x6e,local_19c + 0x46);
      thunk_FUN_004289c0(&local_84,5,0xaf,local_19c + 0x46);
      local_19c[0x8c] = local_1a0;
      thunk_FUN_004289c0(&local_84,5,0x3c,local_19c + 0x8c);
      thunk_FUN_004289c0(&local_84,5,0x82,local_19c + 0x8c);
      thunk_FUN_004289c0(&local_84,5,0xbe,local_19c + 0x8c);
    }
    local_c = (char *)0x0;
LAB_0046b2a0:
    local_c = (char *)thunk_FUN_0041417a(&local_18);
    if (local_c != (char *)0x0) {
      local_1a4 = 0;
      while ((local_1a4 < 4 &&
             ((*(uint *)(&DAT_004bf0f0 + local_18 * 4) & 1 << ((byte)local_1a4 & 0x1f)) == 0))) {
        local_1a4 = local_1a4 + 1;
      }
      if (3 < local_1a4) {
        thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a55cc,0x342,s_tribe<MAX_TRIBES_004a55b8);
      }
      if (*(int *)(&DAT_006192a0 + DAT_0049f538 * 4 + local_1a4 * 0x14a0) != 0) {
        for (local_1a8 = 0; local_1a8 < 8; local_1a8 = local_1a8 + 1) {
          if ((&DAT_00630ab8)[local_1a8 * 0x80] == '\0') {
            local_1ac = _strlen(local_c);
            FUN_00472da0(&DAT_00630ab8 + local_1a8 * 0x80,local_c);
            *(int *)(&DAT_0062a740 + local_1a8 * 4) = local_18;
            iVar2 = thunk_FUN_0041be72();
            *(int *)(&DAT_0062a760 + local_1a8 * 4) =
                 iVar2 + DAT_004c2b54 * ((int)local_1ac / 10 + 5);
            break;
          }
        }
      }
      goto LAB_0046b2a0;
    }
    local_20 = 10;
    local_c = (char *)0x0;
    for (local_1c = 0; local_1c < 8; local_1c = local_1c + 1) {
      if ((&DAT_00630ab8)[local_1c * 0x80] != '\0') {
        uVar3 = thunk_FUN_0041be72();
        if (*(uint *)(&DAT_0062a760 + local_1c * 4) < uVar3) {
          (&DAT_00630ab8)[local_1c * 0x80] = 0;
        }
        else {
          FUN_00472ca0(local_70,s__s___s_004a55e4,
                       &DAT_004beff0 + *(int *)(&DAT_0062a740 + local_1c * 4) * 0x40,
                       &DAT_00630ab8 + local_1c * 0x80);
          thunk_FUN_004289c0(&local_84,10,local_20,local_70);
          local_20 = local_20 + 0xd;
        }
      }
    }
    if (DAT_00630aac != 0) {
      thunk_FUN_0045a4fa();
    }
    if (DAT_0049b5d8 == 0) {
      thunk_FUN_004289c0(&local_84,500,10,s_Lost_World_Sync_004a55ec);
      if (DAT_0049b5dc == 0) {
        thunk_FUN_004289c0(&local_84,500,0x16,s_Lost_Flt_Sync_004a55fc);
      }
      if (DAT_0049b5e0 == 0) {
        thunk_FUN_004289c0(&local_84,500,0x22,s_Lost_Task_Sync_004a560c);
      }
      if (DAT_0049b5e4 == 0) {
        thunk_FUN_004289c0(&local_84,500,0x2e,s_Lost_Island_Sync_004a561c);
      }
    }
    if (DAT_0049b5ec == 0) {
      thunk_FUN_004289c0(&local_84,100,10,s_Lost_WORLDRAND_Sync_004a5630);
    }
    if ((*(int *)(in_ECX + 0x630c) != 0) && (*(int *)(in_ECX + 0x6310) != 0)) {
      local_1b0 = local_20;
      if (*(short *)(DAT_005e8220 + 0x88) != 0) {
        local_1b0 = local_20 + 0x6e;
      }
      _DAT_004c2f38 = thunk_FUN_0042dd0f(5);
      _DAT_004c2f38 = _DAT_004c2f38 & 0xff;
      thunk_FUN_00428baa(&local_84,10,local_20,*(undefined4 *)(in_ECX + 0x6310),0,&LAB_0040235b);
    }
    if ((DAT_004bf124 != 0) && (local_1b4 = thunk_FUN_0040ec89(s_PAUSE_004a5644,1), local_1b4 != 0))
    {
      thunk_FUN_00405e11(local_1b4,0,0,0,0,local_1c4);
      local_1cc = (local_1bc[0] - local_1c4[0]) + 1;
      local_1c8 = (0x280 - local_1cc) / 2;
      if (local_1c8 < 0) {
        local_1c8 = 0;
      }
      if (0x27f < local_1c8) {
        local_1c8 = 0x27f;
      }
      if (DAT_0062d172 == 3) {
        thunk_FUN_00404770(&local_84,local_1b4,0,local_1c8,0x70);
      }
      else if (DAT_0062d172 == 2) {
        local_1d0 = thunk_FUN_0041072f();
        thunk_FUN_00404c3b(local_1d0);
        thunk_FUN_00404c5a(&local_84,local_1b4,0,local_1c8,0x70);
      }
    }
    if (DAT_00630ab4 != 0) {
      FUN_00472ca0(local_1f0,&DAT_004a5654,s_1_16F_004a564c);
      thunk_FUN_004289c0(&local_84,0x244,10,local_1f0);
    }
    thunk_FUN_0042d38a();
  }
  return;
}
```

---

---

## FUN_0046b752 — 0x46b752

- Classification : internal
- Corps : `0x46b752–0x46b90f`
- État : pseudocode obtenu
- Evidence : `ev_ace469c689a216dc474a889d452020df7bb5a196975334651249aea7b2412c34`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40146f` — `thunk_FUN_0042d87c`
- `0x401ad2` — `thunk_FUN_0046c7b5`
- `0x401d8e` — `thunk_FUN_004140dd`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401f82` — `thunk_FUN_0046c640`
- `0x402022` — `thunk_FUN_00406604`
- `0x40227f` — `thunk_FUN_0046c25d`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x4022bb` — `thunk_FUN_0042d3fb`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x4734a0` — `FUN_004734a0`

### Chaînes référencées

- `0x4a5658` — "SetState to %d (%d)"
- `0x4a566c` — "FALSE"
- `0x4a5674` — "C:\\float\\src\\winman.cpp"

### Pseudocode Ghidra

```c
void FUN_0046b752(void)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 uVar5;
  undefined4 uVar6;
  int in_ECX;
  short local_18;
  undefined2 local_8;
  
  FUN_004734a0(in_ECX + 0x2b78,in_ECX + 0x29f8,0x180);
  sVar1 = *(short *)(in_ECX + 0x2cf8);
  *(undefined2 *)(in_ECX + 0x2cf8) = 0;
  for (local_18 = 0; local_18 < sVar1; local_18 = local_18 + 1) {
    sVar2 = *(short *)(in_ECX + 0x2b78 + local_18 * 0xc);
    iVar3 = *(int *)(in_ECX + 0x2b7c + local_18 * 0xc);
    puVar4 = *(undefined4 **)(in_ECX + 0x2b80 + local_18 * 0xc);
    switch(sVar2) {
    case 0:
      break;
    case 1:
      local_8 = (undefined2)iVar3;
      thunk_FUN_0046c640(CONCAT22(sVar2 >> 0xf,local_8),puVar4 != (undefined4 *)0x0);
      thunk_FUN_00414ad0(s_SetState_to__d___d__004a5658,iVar3,puVar4);
      break;
    case 2:
      *(undefined4 *)(in_ECX + 0x62b8) = 1;
      break;
    case 3:
      thunk_FUN_0046c7b5();
      break;
    case 4:
      if (iVar3 == 1) {
        uVar5 = thunk_FUN_0042dd0f(0);
        thunk_FUN_0042d3fb(uVar5);
      }
      else {
        uVar6 = thunk_FUN_0042d28f();
        *puVar4 = uVar6;
        uVar5 = thunk_FUN_0042dd0f(0);
        thunk_FUN_00406604(puVar4,uVar5);
        thunk_FUN_0042d38a();
        thunk_FUN_0042d87c(puVar4,3);
      }
      thunk_FUN_0046c25d(0xb,iVar3,puVar4,0);
      break;
    case 5:
      thunk_FUN_004140dd(0xc,0,0,0);
      break;
    default:
      thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5674,0x400,s_FALSE_004a566c);
    }
  }
  return;
}
```

---

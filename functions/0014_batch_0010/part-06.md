# 0014_batch_0010 — détails (6/6)

## FUN_0044a55e — 0x44a55e

- Classification : internal
- Corps : `0x44a55e–0x44a9cd`
- État : pseudocode obtenu
- Evidence : `ev_919fc12623697bc49340a7fada44c313732f9ae075861b7340492da12f9ea2e5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010c3` — `thunk_FUN_0044bd5a`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x4024af` — `thunk_FUN_0044bded`
- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`

### Chaînes référencées

- `0x4a19dc` — "UNKNOWN"
- `0x4a19dc` — "UNKNOWN"
- `0x4a19e4` — "HOSTANNOUNCE"
- `0x4a19e4` — "HOSTANNOUNCE"
- `0x4a19f4` — "NEWPLAYERANNOUNCE"
- `0x4a19f4` — "NEWPLAYERANNOUNCE"
- `0x4a1a08` — "ADDPLAYERTOGROUP"
- `0x4a1a08` — "ADDPLAYERTOGROUP"
- `0x4a1a1c` — "CREATEGROUP"
- `0x4a1a1c` — "CREATEGROUP"
- `0x4a1a28` — "CREATEPLAYER"
- `0x4a1a28` — "CREATEPLAYER"
- `0x4a1a38` — "i<NET_MAXPLAYERS"
- `0x4a1a4c` — "C:\\float\\src\\network.cpp"
- `0x4a1a68` — "DELETEPLAYERFROMGROUP"
- `0x4a1a68` — "DELETEPLAYERFROMGROUP"
- `0x4a1a80` — "DELETEPLAYER"
- `0x4a1a80` — "DELETEPLAYER"
- `0x4a1a90` — "i<NET_MAXPLAYERS"
- `0x4a1aa4` — "C:\\float\\src\\network.cpp"
- `0x4a1ac0` — "NEWHOST"
- `0x4a1ac0` — "NEWHOST"
- `0x4a1ac8` — "SESSIONLOST"
- `0x4a1ac8` — "SESSIONLOST"
- `0x4a1ad4` — "SETDATA"
- `0x4a1ad4` — "SETDATA"
- `0x4a1adc` — "SETNAME"
- `0x4a1adc` — "SETNAME"
- `0x4a1ae4` — "UNKNOWN"
- `0x4a1ae4` — "UNKNOWN"
- `0x4a1aec` — "Network System Message: %s.\n"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0044a55e(uint *param_1)

{
  uint uVar1;
  size_t sVar2;
  undefined4 uVar3;
  uint local_b8;
  uint local_b4;
  uint *local_b0;
  int local_ac;
  uint *local_a8;
  int local_a4;
  char *local_a0;
  uint local_9c;
  char local_98 [124];
  uint local_1c;
  uint *local_18;
  uint local_14;
  uint *local_10;
  char *local_c;
  uint *local_8;
  
  local_8 = param_1;
  local_c = s_UNKNOWN_004a19dc;
  uVar1 = *param_1;
  if (uVar1 < 0x22) {
    if (uVar1 == 0x21) {
      local_c = s_DELETEPLAYERFROMGROUP_004a1a68;
      goto LAB_0044a9b9;
    }
    if (uVar1 == 3) {
      local_a8 = param_1;
      local_c = s_CREATEGROUP_004a1a1c;
      if (param_1[1] != 0) {
        local_c = s_CREATEPLAYER_004a1a28;
        DAT_005e1a66 = (short)param_1[3];
        for (local_a4 = 0; (local_a4 < 8 && (*(int *)(&DAT_005e2880 + local_a4 * 0x54) != 0));
            local_a4 = local_a4 + 1) {
        }
        if (7 < local_a4) {
          thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1a4c,0x164,s_i<NET_MAXPLAYERS_004a1a38);
        }
        *(uint *)(&DAT_005e2880 + local_a4 * 0x54) = local_a8[2];
        FUN_00472da0(&DAT_005e2830 + local_a4 * 0x54,local_a8[8]);
        thunk_FUN_0044bded(local_a4);
      }
      goto LAB_0044a9b9;
    }
    if (uVar1 == 5) {
      local_b0 = param_1;
      if (param_1[1] != 0) {
        local_c = s_DELETEPLAYER_004a1a80;
        DAT_005e1a66 = DAT_005e1a66 + -1;
        if ((DAT_005e1a60 == 0) && (DAT_005e1a66 == 1)) {
          DAT_005e1a60 = 1;
        }
        for (local_ac = 0;
            (local_ac < 8 && (*(uint *)(&DAT_005e2880 + local_ac * 0x54) != param_1[2]));
            local_ac = local_ac + 1) {
        }
        if (local_ac < 8) {
          uVar3 = 0;
        }
        else {
          uVar3 = thunk_FUN_00414b64(s_C__float_src_network_cpp_004a1aa4,0x185,
                                     s_i<NET_MAXPLAYERS_004a1a90);
        }
        *(undefined4 *)(&DAT_005e2880 + local_ac * 0x54) = 0;
        (&DAT_005e2830)[local_ac * 0x54] = 0;
        if (DAT_005e3170 != (code *)0x0) {
          local_b4 = local_b0[2];
          (*DAT_005e3170)(2,&local_b4,4,uVar3);
        }
      }
      goto LAB_0044a9b9;
    }
    if (uVar1 == 7) {
      local_c = s_ADDPLAYERTOGROUP_004a1a08;
      goto LAB_0044a9b9;
    }
  }
  else if (uVar1 < 0x102) {
    if (uVar1 == 0x101) {
      DAT_005e1a60 = 1;
      DAT_005e1ef8 = DAT_005e1e94;
      thunk_FUN_0044bd5a();
      if (DAT_005e3170 != (code *)0x0) {
        local_b8 = DAT_005e1ef8;
        (*DAT_005e3170)(3,&local_b8,4);
      }
      local_c = s_NEWHOST_004a1ac0;
      goto LAB_0044a9b9;
    }
    if (uVar1 == 0x31) {
      local_c = s_SESSIONLOST_004a1ac8;
      _DAT_005e1a54 = 0;
      goto LAB_0044a9b9;
    }
  }
  else if (uVar1 < 0x60971) {
    if (uVar1 == 0x60970) {
      local_10 = param_1;
      DAT_005e1ef8 = param_1[1];
      if (DAT_005e3170 != (code *)0x0) {
        local_14 = DAT_005e1ef8;
        (*DAT_005e3170)(3,&local_14,4);
      }
      local_c = s_HOSTANNOUNCE_004a19e4;
      goto LAB_0044a9b9;
    }
    if (uVar1 == 0x102) {
      local_c = s_SETDATA_004a1ad4;
      goto LAB_0044a9b9;
    }
    if (uVar1 == 0x103) {
      local_c = s_SETNAME_004a1adc;
      goto LAB_0044a9b9;
    }
  }
  else if (uVar1 == 0x112694) {
    local_1c = param_1[1];
    local_18 = param_1 + 2;
    if (DAT_005e3170 != (code *)0x0) {
      local_a0 = local_98;
      local_9c = local_1c;
      FUN_00472da0(local_a0,local_18);
      sVar2 = _strlen(local_a0);
      (*DAT_005e3170)(1,&local_9c,sVar2 + 5);
      if (DAT_005e1e94 == local_1c) {
        (*DAT_005e3170)(4,&local_9c,4);
      }
    }
    local_c = s_NEWPLAYERANNOUNCE_004a19f4;
    goto LAB_0044a9b9;
  }
  local_c = s_UNKNOWN_004a1ae4;
LAB_0044a9b9:
  thunk_FUN_00414ad0(s_Network_System_Message___s__004a1aec,local_c);
  return;
}
```

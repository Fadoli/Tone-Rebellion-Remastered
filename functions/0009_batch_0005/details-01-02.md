# 0009_batch_0005 — détails (2/3)

## FUN_00412eac — 0x412eac

- Classification : internal
- Corps : `0x412eac–0x413087`
- État : pseudocode obtenu
- Evidence : `ev_eb34738a65ae7a5464539f5bda206e2a134ef34500d71e4f8c93b2c8c9b03cd2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401050` — `thunk_FUN_00413c60`
- `0x4010be` — `thunk_FUN_004133f2`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x402351` — `thunk_FUN_0044b532`

### Chaînes référencées

- `0x49b7e8` — "[PER %d] Command Received: Time %d  Period %d"
- `0x49b818` — "Buffered Periods Overflow...Exiting."
- `0x49b840` — "FALSE"
- `0x49b848` — "C:\\float\\src\\command.cpp"

### Pseudocode Ghidra

```c
int FUN_00412eac(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int in_ECX;
  uint local_20;
  uint local_1c;
  int local_10;
  int local_c;
  int *local_8;
  
  local_8 = (int *)0x0;
  local_8 = (int *)thunk_FUN_0044b532(&local_c);
  local_10 = 0;
  if (local_8 != (int *)0x0) {
    local_10 = *local_8;
    uVar2 = local_8[1];
    iVar3 = local_8[2];
    local_8 = local_8 + 3;
    local_20 = 0;
    if ((DAT_004befe0 != 0) && (DAT_004befec != DAT_004befe8)) {
      local_20 = 2;
    }
    local_1c = uVar2;
    if (((local_10 == 4) &&
        ((((iVar3 == 2 || (iVar3 == 5)) || (iVar3 == 3)) || ((iVar3 == 4 || (iVar3 == 6)))))) &&
       (((local_1c = *(uint *)(in_ECX + 0x1274), iVar3 == 5 || ((iVar3 == 3 || (iVar3 == 4)))) ||
        (iVar3 == 6)))) {
      local_20 = local_20 | 1;
    }
    thunk_FUN_004133f2(local_10,iVar3,local_8,local_c + -0xc,local_20,local_1c);
    if ((local_20 & 2) != 0) {
      uVar4 = uVar2 / *(uint *)(in_ECX + 0x1278);
      if ((*(uint *)(in_ECX + 0x127c) <= uVar4) && (0x40 < uVar4 - *(int *)(in_ECX + 0x127c))) {
        thunk_FUN_00414ad0(s__PER__d__Command_Received__Time___0049b7e8,
                           *(undefined4 *)(in_ECX + 0x127c),uVar2,uVar4);
        thunk_FUN_00414ad0(s_Buffered_Periods_Overflow___Exit_0049b818);
        thunk_FUN_00413c60();
        thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b848,0x270,s_FALSE_0049b840);
      }
      iVar1 = in_ECX + 0xc74 + (uVar4 % 0x40) * 0x18;
      if ((((iVar3 != 3) && (iVar3 != 5)) && (iVar3 != 2)) && (iVar3 != 6)) {
        *(int *)(iVar1 + 0xc) = *(int *)(iVar1 + 0xc) + 1;
      }
    }
  }
  return local_10;
}
```

---

---

## FUN_00413088 — 0x413088

- Classification : internal
- Corps : `0x413088–0x4132fe`
- État : pseudocode obtenu
- Evidence : `ev_20e8a8954d8f8520c6b9b69b9566850e380b49224fb67dbcee8e8f1469129bc6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010be` — `thunk_FUN_004133f2`
- `0x401258` — `thunk_FUN_00467ff6`
- `0x401d75` — `thunk_FUN_00414106`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00413088(void)

{
  int in_ECX;
  undefined4 local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int *local_20;
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  if ((DAT_004befe0 == 0) || (DAT_004befec != DAT_004befe8)) {
    local_1c = 0;
    local_20 = (int *)(in_ECX + 0xc74 + ((*(int *)(in_ECX + 0x127c) + 1U) % 0x40) * 0x18);
    if ((*local_20 == 1) && (local_20[3] == local_20[2])) {
      *local_20 = 0;
      local_20[3] = 0;
      local_8 = 1;
      DAT_0049b5ec = 1;
      DAT_0049b5e8 = 1;
      DAT_0049b5e4 = 1;
      DAT_0049b5e0 = 1;
      DAT_0049b5dc = 1;
      DAT_0049b5d8 = (uint)(local_20[4] == local_20[5]);
      if (DAT_0049b5d8 == 0) {
        local_28 = *(undefined4 *)(&DAT_004bf100 + DAT_004befec * 4);
        local_24 = *(undefined4 *)(in_ECX + 0x1274);
        thunk_FUN_00414106(4,&local_28,8);
      }
    }
  }
  else {
    local_18 = *(int *)(in_ECX + 0x127c) + 1;
    local_14 = *(undefined4 *)(in_ECX + 0x1280);
    local_10 = thunk_FUN_00467ff6();
    if (DAT_004c03d0 != 0) {
      local_8 = 1;
    }
    for (local_c = 0; local_c < DAT_004befe4; local_c = local_c + 1) {
      if ((local_c != DAT_004befec) && (0x1f < *(int *)(&DAT_004c03d8 + local_c * 4))) {
        local_8 = 0;
        break;
      }
    }
    if (local_8 != 0) {
      thunk_FUN_004133f2(4,2,&local_18,0xc,8,0);
      *(undefined4 *)(in_ECX + 0x1280) = 0;
    }
  }
  if (local_8 == 1) {
    *(undefined4 *)(in_ECX + 0x1284) = 0;
    *(int *)(in_ECX + 0x127c) = *(int *)(in_ECX + 0x127c) + 1;
    if (((DAT_004befe0 != 0) && (DAT_004befec != DAT_004befe8)) &&
       (*(uint *)(in_ECX + 0x127c) % 5 == 0)) {
      local_30 = *(undefined4 *)(&DAT_004bf100 + DAT_004befec * 4);
      local_2c = DAT_004c03e8 - *(int *)(in_ECX + 0x127c);
      if (local_2c < 0) {
        local_2c = 0;
      }
      thunk_FUN_00414106(6,&local_30,8);
    }
  }
  return local_8;
}
```

---

---

## FUN_004132ff — 0x4132ff

- Classification : internal
- Corps : `0x4132ff–0x413343`
- État : pseudocode obtenu
- Evidence : `ev_f8265925962c39ec0d1fdce355daec328e243f550ddc28604b2f32c85ef523a4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int * FUN_004132ff(void)

{
  int *in_ECX;
  int local_c;
  int *local_8;
  
  local_c = 0;
  local_8 = in_ECX;
  while( true ) {
    if (0x1f < local_c) {
      return (int *)0x0;
    }
    if (*local_8 == 0) break;
    local_c = local_c + 1;
    local_8 = local_8 + 0x18;
  }
  return local_8;
}
```

---

---

## FUN_00413344 — 0x413344

- Classification : internal
- Corps : `0x413344–0x4133f1`
- État : pseudocode obtenu
- Evidence : `ev_bbd327ad0d8fd20edaeb416bb271463696f49ca30bf0ccbec56244d490d60c0d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int * FUN_00413344(int param_1,int param_2)

{
  int *in_ECX;
  int local_10;
  int *local_c;
  
  if (in_ECX[param_1 + 0x300] != 0) {
    local_c = in_ECX;
    for (local_10 = 0; local_10 < 0x20; local_10 = local_10 + 1) {
      if (((*local_c == 1) && (local_c[1] == param_1)) &&
         (((uint)local_c[2] <= (uint)in_ECX[0x49d] || (param_2 == 0)))) {
        *local_c = 0;
        in_ECX[param_1 + 0x300] = in_ECX[param_1 + 0x300] + -1;
        return local_c;
      }
      local_c = local_c + 0x18;
    }
  }
  return (int *)0x0;
}
```

---

---

## FUN_004133f2 — 0x4133f2

- Classification : internal
- Corps : `0x4133f2–0x413674`
- État : pseudocode obtenu
- Evidence : `ev_34b7642d56fd0dae574f85396d8f78d7ba9c9e9804b2c5fbd60fb705b6d38df2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401050` — `thunk_FUN_00413c60`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401f96` — `thunk_FUN_00412d70`
- `0x40206d` — `thunk_FUN_004132ff`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x4734a0` — `FUN_004734a0`

### Chaînes référencées

- `0x49b864` — "mNextAvailCmdTime<mLatencyPeriod"
- `0x49b888` — "C:\\float\\src\\command.cpp"
- `0x49b8a4` — "availtime > cmdtime"
- `0x49b8b8` — "C:\\float\\src\\command.cpp"
- `0x49b8d4` — "No free buffers...Exiting"
- `0x49b8f4` — "C:\\float\\src\\command.cpp"

### Pseudocode Ghidra

```c
/* WARNING: Removing unreachable block (ram,0x004135db) */

void FUN_004133f2(int param_1,undefined4 param_2,undefined4 param_3,int param_4,uint param_5,
                 int param_6)

{
  int iVar1;
  undefined4 *puVar2;
  int in_ECX;
  int local_8;
  
  iVar1 = *(int *)(in_ECX + 0x1274);
  if ((param_5 & 2) == 0) {
    local_8 = iVar1;
    if (((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) || (DAT_004befe0 == 0)) {
      if ((param_5 & 8) == 0) {
        if ((param_5 & 1) == 0) {
          if (DAT_004befe0 == 0) {
            local_8 = iVar1 + *(int *)(in_ECX + 0x1278);
          }
          else {
            if (*(uint *)(in_ECX + 0x1278) <= *(uint *)(in_ECX + 0x1284)) {
              thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b888,0x399,
                                 s_mNextAvailCmdTime<mLatencyPeriod_0049b864);
            }
            local_8 = ((iVar1 + (*(uint *)(in_ECX + 0x1278) >> 1)) / *(uint *)(in_ECX + 0x1278) + 1)
                      * *(int *)(in_ECX + 0x1278) + *(int *)(in_ECX + 0x1284);
            *(int *)(in_ECX + 0x1284) = *(int *)(in_ECX + 0x1284) + 1;
            if (local_8 <= iVar1) {
              thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b8b8,0x3a0,
                                 s_availtime_>_cmdtime_0049b8a4);
            }
          }
        }
      }
      else {
        local_8 = iVar1 + (*(int *)(in_ECX + 0x1278) - (*(uint *)(in_ECX + 0x1278) >> 1));
      }
    }
  }
  else {
    local_8 = param_6;
  }
  if ((DAT_004befe0 != 0) && ((param_5 & 6) == 0)) {
    thunk_FUN_00412d70(param_1,local_8,param_2,param_3,param_4);
  }
  if (((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) ||
     ((DAT_004befe0 == 0 || ((param_5 & 6) != 0)))) {
    puVar2 = (undefined4 *)thunk_FUN_004132ff();
    if (puVar2 == (undefined4 *)0x0) {
      thunk_FUN_00414ad0(s_No_free_buffers___Exiting_0049b8d4);
      thunk_FUN_00413c60();
      thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b8f4,0x3bd,&DAT_0049b8f0);
    }
    *puVar2 = 1;
    puVar2[1] = param_1;
    puVar2[2] = local_8;
    puVar2[3] = param_4 + 4;
    FUN_004734a0(puVar2 + 4,&param_2,4);
    FUN_004734a0(puVar2 + 5,param_3,param_4);
    *(int *)(in_ECX + 0xc00 + param_1 * 4) = *(int *)(in_ECX + 0xc00 + param_1 * 4) + 1;
  }
  return;
}
```

---

---

## FUN_00413675 — 0x413675

- Classification : internal
- Corps : `0x413675–0x413b4f`
- État : pseudocode obtenu
- Evidence : `ev_a6354f3ad27e4f14eb1e4747d41de83ff4437d9276c0f7007fd0f488ceefdf2c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401050` — `thunk_FUN_00413c60`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x401ece` — `thunk_FUN_00413344`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x49b910` — "Attempt to overwrite PSD in use...Exiting"
- `0x49b93c` — "psd->flags==0"
- `0x49b94c` — "C:\\float\\src\\command.cpp"
- `0x49b968` — "i<GAMEENV.mNumPlayers"
- `0x49b980` — "C:\\float\\src\\command.cpp"
- `0x49b99c` — "i<GAMEENV.mNumPlayers"
- `0x49b9b4` — "C:\\float\\src\\command.cpp"
- `0x49b9d0` — "i<GAMEENV.mNumPlayers"
- `0x49b9e8` — "C:\\float\\src\\command.cpp"
- `0x49ba04` — "%d %%%%%%%%%% Received %s Arrival"
- `0x49ba28` — "i<GAMEENV.mNumPlayers"
- `0x49ba40` — "C:\\float\\src\\command.cpp"
- `0x49ba5c` — "%d %%%%%%%%%% Received %s Ack %d"
- `0x49ba80` — "FALSE"
- `0x49ba88` — "C:\\float\\src\\command.cpp"

### Pseudocode Ghidra

```c
void FUN_00413675(void)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  bool bVar5;
  int iVar6;
  uint *puVar7;
  int in_ECX;
  uint uVar8;
  undefined4 uVar9;
  int local_4c;
  int local_3c;
  int local_34;
  int local_28;
  
  while (iVar6 = thunk_FUN_00413344(4,1), iVar6 != 0) {
    puVar7 = (uint *)(iVar6 + 0x14);
    switch(*(undefined4 *)(iVar6 + 0x10)) {
    case 1:
      *(uint *)(in_ECX + 0x1278) = *puVar7;
      break;
    case 2:
      if ((DAT_004befe0 != 0) && (DAT_004befec != DAT_004befe8)) {
        uVar2 = *puVar7;
        iVar3 = *(int *)(iVar6 + 0x18);
        iVar6 = *(int *)(iVar6 + 0x1c);
        if ((int)DAT_004c03e8 < (int)uVar2) {
          DAT_004c03e8 = uVar2;
        }
        uVar8 = (int)uVar2 >> 0x1f;
        piVar1 = (int *)(in_ECX + 0xc74 + (((uVar2 ^ uVar8) - uVar8 & 0x3f ^ uVar8) - uVar8) * 0x18)
        ;
        if (*piVar1 != 0) {
          thunk_FUN_00414ad0(s_Attempt_to_overwrite_PSD_in_use__0049b910);
          thunk_FUN_00413c60();
          if (*piVar1 != 0) {
            thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b94c,0x404,s_psd_>flags__0_0049b93c);
          }
        }
        *piVar1 = 1;
        piVar1[1] = uVar2;
        piVar1[2] = iVar3;
        piVar1[4] = iVar6;
        DAT_004c03b8 = DAT_004c03b8 + 1;
      }
      break;
    case 3:
      if ((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) {
        for (local_3c = 0;
            (local_3c < DAT_004befe4 && (*(uint *)(&DAT_004bf100 + local_3c * 4) != *puVar7));
            local_3c = local_3c + 1) {
        }
        if (DAT_004befe4 <= local_3c) {
          thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b9e8,0x46c,
                             s_i<GAMEENV_mNumPlayers_0049b9d0);
        }
        *(undefined4 *)(&DAT_004c03c0 + local_3c * 4) = 1;
        thunk_FUN_00414ad0(s__d____________Received__s_Arriva_0049ba04,
                           *(undefined4 *)(in_ECX + 0x1274),&DAT_004beff0 + local_3c * 0x40);
        bVar5 = true;
        for (local_3c = 0; local_3c < DAT_004befe4; local_3c = local_3c + 1) {
          if ((DAT_004befec != local_3c) && (*(int *)(&DAT_004c03c0 + local_3c * 4) == 0)) {
            bVar5 = false;
          }
        }
        if ((bVar5) && (DAT_004c03d0 == 0)) {
          DAT_004c03d0 = 1;
          thunk_FUN_0046c1b4(5,0,0);
        }
      }
      break;
    case 4:
      if ((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) {
        for (local_28 = 0;
            (local_28 < DAT_004befe4 && (*(uint *)(&DAT_004bf100 + local_28 * 4) != *puVar7));
            local_28 = local_28 + 1) {
        }
        if (DAT_004befe4 <= local_28) {
          thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b980,0x43d,
                             s_i<GAMEENV_mNumPlayers_0049b968);
        }
      }
      break;
    case 5:
      if ((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) {
        uVar4 = *(undefined4 *)(iVar6 + 0x18);
        for (local_4c = 0;
            (local_4c < DAT_004befe4 && (*(uint *)(&DAT_004bf100 + local_4c * 4) != *puVar7));
            local_4c = local_4c + 1) {
        }
        if (local_4c < DAT_004befe4) {
          uVar9 = 0;
        }
        else {
          uVar9 = thunk_FUN_00414b64(s_C__float_src_command_cpp_0049ba40,0x494,
                                     s_i<GAMEENV_mNumPlayers_0049ba28);
        }
        *(undefined4 *)(&DAT_0049b5f0 + local_4c * 4) = uVar4;
        thunk_FUN_00414ad0(s__d____________Received__s_Ack__d_0049ba5c,
                           *(undefined4 *)(in_ECX + 0x1274),&DAT_004beff0 + local_4c * 0x40,uVar4,
                           uVar9);
      }
      break;
    case 6:
      if ((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) {
        uVar4 = *(undefined4 *)(iVar6 + 0x18);
        for (local_34 = 0;
            (local_34 < DAT_004befe4 && (*(uint *)(&DAT_004bf100 + local_34 * 4) != *puVar7));
            local_34 = local_34 + 1) {
        }
        if (DAT_004befe4 <= local_34) {
          thunk_FUN_00414b64(s_C__float_src_command_cpp_0049b9b4,0x454,
                             s_i<GAMEENV_mNumPlayers_0049b99c);
        }
        *(undefined4 *)(&DAT_004c03d8 + local_34 * 4) = uVar4;
      }
      break;
    default:
      thunk_FUN_00414b64(s_C__float_src_command_cpp_0049ba88,0x49c,s_FALSE_0049ba80);
    }
  }
  return;
}
```

---

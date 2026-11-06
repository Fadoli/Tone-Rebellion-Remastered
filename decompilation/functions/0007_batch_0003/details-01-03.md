# 0007_batch_0003 — détails (3/3)

## FUN_0040adb5 — 0x40adb5

- Classification : internal
- Corps : `0x40adb5–0x40ae4c`
- État : pseudocode obtenu
- Evidence : `ev_407e2460cd55410a56b04421eca788cdfcc32784fea228250b4da00e2fdbba23`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040adb5(int param_1,undefined2 *param_2,int *param_3)

{
  undefined2 local_c;
  undefined4 local_8;
  
  local_c = 0xffff;
  if (param_1 < 4) {
    if (param_1 == 1) {
      local_c = DAT_0049aca8;
    }
    else if (param_1 == 2) {
      local_c = DAT_0049acac;
    }
    else if (param_1 == 3) {
      local_c = DAT_0049acb0;
    }
    local_8 = 0;
  }
  else {
    local_c = DAT_0049acb4;
    local_8 = param_1 + -5;
  }
  *param_2 = local_c;
  *param_3 = local_8;
  return;
}
```

---

---

## FUN_0040ae4d — 0x40ae4d

- Classification : internal
- Corps : `0x40ae4d–0x40afd2`
- État : pseudocode obtenu
- Evidence : `ev_c0b728097c1a86101e3bd0f1682de03db6fc015407567ba16aab7a06b061e01c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012da` — `thunk_FUN_0040adb5`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401915` — `thunk_FUN_004502dc`
- `0x40198d` — `thunk_FUN_0040ab42`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401f14` — `thunk_FUN_00404770`
- `0x472ca0` — `FUN_00472ca0`

### Chaînes référencées

- `0x49ad8c` — "F%02d"

### Pseudocode Ghidra

```c
void FUN_0040ae4d(int param_1,short *param_2)

{
  int iVar1;
  undefined4 uVar2;
  short *extraout_EDX;
  short *psVar3;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  uint local_3c;
  int local_38;
  short *local_34;
  int local_30;
  undefined1 local_2c [40];
  
  thunk_FUN_0040ab42(param_1,param_2);
  local_30 = (*(int *)(param_1 + 4) + (int)*param_2) -
             (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
  local_38 = *(int *)(param_1 + 8) + (int)param_2[1];
  iVar1 = thunk_FUN_004502dc();
  thunk_FUN_0040adb5(iVar1,&local_3c,&local_34);
  if (iVar1 == 1) {
    local_34 = (short *)(param_2[0x14] + -1);
    psVar3 = extraout_EDX;
    if (0x31 < (int)local_34) {
      local_34 = (short *)0x31;
    }
  }
  else if (iVar1 == 2) {
    local_34 = (short *)(param_2[0x15] + -1);
    psVar3 = param_2;
    if (0x31 < (int)local_34) {
      local_34 = (short *)0x31;
    }
  }
  else {
    psVar3 = extraout_EDX;
    if ((iVar1 == 3) &&
       (psVar3 = (short *)(param_2[0x16] + -1), local_34 = psVar3, 0x31 < (int)psVar3)) {
      local_34 = (short *)0x31;
    }
  }
  uVar4 = (undefined2)((uint)psVar3 >> 0x10);
  if ((local_3c & 0xffff) == 0) {
    if ((5 < iVar1) && (iVar1 < 0x22)) {
      FUN_00472ca0(local_2c,s_F_02d_0049ad8c,iVar1 + -6);
      puVar7 = local_2c;
      iVar1 = param_1;
      iVar5 = local_30;
      iVar6 = local_38;
      thunk_FUN_0042de03(param_1,local_30,local_38,puVar7);
      thunk_FUN_004289c0(iVar1,iVar5,iVar6,puVar7);
      uVar4 = extraout_var;
    }
  }
  else {
    psVar3 = local_34;
    iVar1 = local_30;
    iVar5 = local_38;
    uVar2 = thunk_FUN_0040e864(local_3c & 0xffff);
    thunk_FUN_00404770(param_1,uVar2,psVar3,iVar1,iVar5);
    uVar4 = extraout_var_00;
  }
  if ((*(uint *)(param_2 + 0xe) & 0x200) != 0) {
    uVar2 = thunk_FUN_0040e864(CONCAT22(uVar4,DAT_0049acb8));
    thunk_FUN_00404770(param_1,uVar2,0x15,local_30,local_38);
  }
  return;
}
```

---

# 0014_batch_0010 — détails (2/2)

## FUN_00446493 — 0x446493

- Classification : internal
- Corps : `0x446493–0x4464e6`
- État : pseudocode obtenu
- Evidence : `ev_65b695986103cd87424b6af142a81756921c90b69373c7606ccf217516a14b3e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4016a4` — `thunk_FUN_00446503`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00446493(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049197c;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494588;
  thunk_FUN_00446503();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_004464e7 — 0x4464e7

- Classification : internal
- Corps : `0x4464e7–0x446502`
- État : pseudocode obtenu
- Evidence : `ev_2ea3626afb56aea22e6e8e07b5e27f3e2d3f2232076eca26379f340e8b0957db`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004464e7(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494588;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_00446503 — 0x446503

- Classification : internal
- Corps : `0x446503–0x446517`
- État : pseudocode obtenu
- Evidence : `ev_634450edc3ea35fd0474e638b514c8897615eb2530b8caa1214f606ceffc8c09`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00446503(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x70) = 0;
  return;
}
```

---

---

## FUN_00446518 — 0x446518

- Classification : internal
- Corps : `0x446518–0x44661f`
- État : pseudocode obtenu
- Evidence : `ev_eb5f53197feafe930f54430f7af095f69b37ec2fe3cc36382ff56c8f58669b47`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`
- `0x4018e3` — `thunk_FUN_0046c3bc`

### Chaînes référencées

- `0x4a10e0` — "TaskNorm"
- `0x4a10ec` — "TaskHigh"
- `0x4a10f8` — "TaskExcl"
- `0x4a1104` — "TaskKill"
- `0x4a1110` — "TaskNorm"
- `0x4a111c` — "TaskHigh"
- `0x4a1128` — "TaskExcl"
- `0x4a1134` — "TaskKill"

### Pseudocode Ghidra

```c
void FUN_00446518(short param_1,undefined4 param_2,undefined4 param_3)

{
  int in_ECX;
  
  if (param_1 == 1) {
    thunk_FUN_0046c3bc(s_TaskNorm_004a10e0,1,0,0);
    thunk_FUN_0046c3bc(s_TaskHigh_004a10ec,1,0,0);
    thunk_FUN_0046c3bc(s_TaskExcl_004a10f8,1,0,0);
    thunk_FUN_0046c3bc(s_TaskKill_004a1104,1,0,0);
  }
  else if (param_1 == 2) {
    thunk_FUN_0046c3bc(s_TaskNorm_004a1110,2,0,0);
    thunk_FUN_0046c3bc(s_TaskHigh_004a111c,2,0,0);
    thunk_FUN_0046c3bc(s_TaskExcl_004a1128,2,0,0);
    thunk_FUN_0046c3bc(s_TaskKill_004a1134,2,0,0);
  }
  else if (param_1 == 0x13ba) {
    *(undefined4 *)(in_ECX + 0x70) = param_2;
    *(undefined4 *)(in_ECX + 0x34) = 1;
  }
  thunk_FUN_004293c6(param_1,param_2,param_3);
  return;
}
```

---

---

## FUN_00446620 — 0x446620

- Classification : internal
- Corps : `0x446620–0x4468ed`
- État : pseudocode obtenu
- Evidence : `ev_c1e936b5e37506afc3e5454c4b0df367ed16c28cc3f2facf920cf6200f47fa97`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x4012a3` — `thunk_FUN_0046c17b`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402022` — `thunk_FUN_00406604`
- `0x402234` — `thunk_FUN_0042892d`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x4a1140` — "bgfont"
- `0x4a1148` — "C:\\float\\src\\iwtask.cpp"
- `0x4a1160` — "TaskNorm"
- `0x4a1160` — "TaskNorm"
- `0x4a1160` — "TaskNorm"
- `0x4a116c` — "TaskHigh"
- `0x4a116c` — "TaskHigh"
- `0x4a116c` — "TaskHigh"
- `0x4a1178` — "TaskExcl"
- `0x4a1178` — "TaskExcl"
- `0x4a1178` — "TaskExcl"
- `0x4a1184` — "TaskKill"
- `0x4a1184` — "TaskKill"
- `0x4a1184` — "TaskKill"
- `0x4a1198` — "THIGH"
- `0x4a1198` — "THIGH"
- `0x4a11b0` — "TaskNorm"
- `0x4a11bc` — "TaskHigh"
- `0x4a11c8` — "TaskExcl"
- `0x4a11d4` — "TaskKill"

### Pseudocode Ghidra

```c
void FUN_00446620(void)

{
  undefined4 uVar1;
  int iVar2;
  int in_ECX;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int local_74;
  char local_68 [4];
  char local_64 [4];
  char local_60;
  undefined4 local_5f;
  undefined2 local_5b;
  undefined1 local_59;
  char local_58 [4];
  char local_54 [4];
  char local_50;
  undefined4 local_4f;
  undefined2 local_4b;
  undefined1 local_49;
  char local_48 [4];
  char local_44 [4];
  char local_40;
  undefined4 local_3f;
  undefined2 local_3b;
  undefined1 local_39;
  char local_38 [4];
  char local_34 [4];
  char local_30;
  undefined4 local_2f;
  undefined2 local_2b;
  undefined1 local_29;
  undefined4 local_28;
  undefined2 local_24;
  undefined2 local_22;
  char local_20 [4];
  char local_1c [2];
  undefined2 local_1a;
  undefined4 local_18;
  undefined2 local_14;
  undefined2 local_12;
  undefined4 local_10;
  undefined2 local_c;
  undefined2 local_a;
  int local_8;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    uVar1 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar1;
    if (DAT_004c2bac == 0) {
      thunk_FUN_00406604(in_ECX + 8,DAT_004c2b08);
    }
    else {
      uVar5 = 0;
      uVar4 = 0;
      iVar3 = (int)*(short *)(in_ECX + 0x1e);
      uVar1 = thunk_FUN_0040e864(*(undefined2 *)(in_ECX + 0x1c));
      thunk_FUN_00404770(in_ECX + 8,uVar1,iVar3,uVar4,uVar5);
    }
    iVar3 = thunk_FUN_0042de03();
    if (iVar3 == 0) {
      uVar1 = thunk_FUN_00414b64(s_C__float_src_iwtask_cpp_004a1148,0x26f,s_bgfont_004a1140);
    }
    else {
      uVar1 = 0;
    }
    local_8 = 0;
    local_68[0] = s_TaskNorm_004a1160[0];
    local_68[1] = s_TaskNorm_004a1160[1];
    local_68[2] = s_TaskNorm_004a1160[2];
    local_68[3] = s_TaskNorm_004a1160[3];
    local_64[0] = s_TaskNorm_004a1160[4];
    local_64[1] = s_TaskNorm_004a1160[5];
    local_64[2] = s_TaskNorm_004a1160[6];
    local_64[3] = s_TaskNorm_004a1160[7];
    local_60 = s_TaskNorm_004a1160[8];
    local_5f = 0;
    local_5b = 0;
    local_59 = 0;
    local_58[0] = s_TaskHigh_004a116c[0];
    local_58[1] = s_TaskHigh_004a116c[1];
    local_58[2] = s_TaskHigh_004a116c[2];
    local_58[3] = s_TaskHigh_004a116c[3];
    local_54[0] = s_TaskHigh_004a116c[4];
    local_54[1] = s_TaskHigh_004a116c[5];
    local_54[2] = s_TaskHigh_004a116c[6];
    local_54[3] = s_TaskHigh_004a116c[7];
    local_50 = s_TaskHigh_004a116c[8];
    local_4f = 0;
    local_4b = 0;
    local_49 = 0;
    local_48[0] = s_TaskExcl_004a1178[0];
    local_48[1] = s_TaskExcl_004a1178[1];
    local_48[2] = s_TaskExcl_004a1178[2];
    local_48[3] = s_TaskExcl_004a1178[3];
    local_44[0] = s_TaskExcl_004a1178[4];
    local_44[1] = s_TaskExcl_004a1178[5];
    local_44[2] = s_TaskExcl_004a1178[6];
    local_44[3] = s_TaskExcl_004a1178[7];
    local_40 = s_TaskExcl_004a1178[8];
    local_3f = 0;
    local_3b = 0;
    local_39 = 0;
    local_38[0] = s_TaskKill_004a1184[0];
    local_38[1] = s_TaskKill_004a1184[1];
    local_38[2] = s_TaskKill_004a1184[2];
    local_38[3] = s_TaskKill_004a1184[3];
    local_34[0] = s_TaskKill_004a1184[4];
    local_34[1] = s_TaskKill_004a1184[5];
    local_34[2] = s_TaskKill_004a1184[6];
    local_34[3] = s_TaskKill_004a1184[7];
    local_30 = s_TaskKill_004a1184[8];
    local_2f = 0;
    local_2b = 0;
    local_29 = 0;
    local_28 = DAT_004a1190;
    local_24 = DAT_004a1194;
    local_22 = 0;
    local_20[0] = s_THIGH_004a1198[0];
    local_20[1] = s_THIGH_004a1198[1];
    local_20[2] = s_THIGH_004a1198[2];
    local_20[3] = s_THIGH_004a1198[3];
    local_1c[0] = s_THIGH_004a1198[4];
    local_1c[1] = s_THIGH_004a1198[5];
    local_1a = 0;
    local_18 = DAT_004a11a0;
    local_14 = DAT_004a11a4;
    local_12 = 0;
    local_10 = DAT_004a11a8;
    local_c = DAT_004a11ac;
    local_a = 0;
    iVar3 = thunk_FUN_0046c17b(uVar1);
    if (iVar3 != 0) {
      for (local_74 = 0; local_74 < 4; local_74 = local_74 + 1) {
        iVar2 = __strcmpi(local_68 + local_74 * 0x10,(char *)(iVar3 + 0x20));
        if (iVar2 == 0) {
          local_8 = thunk_FUN_00429ebe(&local_28 + local_74 * 2,0);
          break;
        }
      }
    }
    if (local_8 != 0) {
      iVar3 = thunk_FUN_0042892d(local_8,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,((*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) - iVar3) / 2
                         ,0xf,local_8);
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,1);
    thunk_FUN_0046c3bc(s_TaskNorm_004a11b0,0xb,0,0);
    thunk_FUN_0046c3bc(s_TaskHigh_004a11bc,0xb,0,0);
    thunk_FUN_0046c3bc(s_TaskExcl_004a11c8,0xb,0,0);
    thunk_FUN_0046c3bc(s_TaskKill_004a11d4,0xb,0,0);
  }
  return;
}
```

---

---

## FUN_004468ee — 0x4468ee

- Classification : internal
- Corps : `0x4468ee–0x4468fa`
- État : pseudocode obtenu
- Evidence : `ev_62bc1b599d7cb17ea16f80cd0c4eecedc12ce610a72c6d895df867bbdae5e891`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004468ee(void)

{
  return;
}
```

---

---

## FUN_004468fb — 0x4468fb

- Classification : internal
- Corps : `0x4468fb–0x446907`
- État : pseudocode obtenu
- Evidence : `ev_bd9a8adeeba1dcbbd81ccbf5feae4c40f1397f1397f14bcbac5a50e83afd49fb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004468fb(void)

{
  return;
}
```

---

---

## FUN_00446908 — 0x446908

- Classification : internal
- Corps : `0x446908–0x44695b`
- État : pseudocode obtenu
- Evidence : `ev_4fe41a1a7e0ff222e217cbec15396a0ca8b8099e17f5070512c35731b6cf7b67`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401460` — `thunk_FUN_00446978`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00446908(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0049198f;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_004945a0;
  thunk_FUN_00446978();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_0044695c — 0x44695c

- Classification : internal
- Corps : `0x44695c–0x446977`
- État : pseudocode obtenu
- Evidence : `ev_dbd632ac2e31dc2eb8eadb3a90096f4e20de99398029bf6f429149f2051a9a08`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044695c(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004945a0;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_00446978 — 0x446978

- Classification : internal
- Corps : `0x446978–0x44698c`
- État : pseudocode obtenu
- Evidence : `ev_950fb61b927d652842747ffc4aff9331471788428b21e179145675184dfd15bc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00446978(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x70) = 0;
  return;
}
```

---

---

## FUN_0044698d — 0x44698d

- Classification : internal
- Corps : `0x44698d–0x4469d5`
- État : pseudocode obtenu
- Evidence : `ev_c6f5ce93f274fe3f4cdc398baeb42f44de643e0759dad6aa9691a0e954db9e37`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40151e` — `thunk_FUN_004293c6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044698d(short param_1,undefined4 param_2,undefined4 param_3)

{
  int in_ECX;
  
  if (param_1 == 0x13ba) {
    *(undefined4 *)(in_ECX + 0x70) = param_2;
    *(undefined4 *)(in_ECX + 0x34) = 1;
  }
  thunk_FUN_004293c6(param_1,param_2,param_3);
  return;
}
```

---

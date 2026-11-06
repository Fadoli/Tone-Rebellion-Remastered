# 0017_batch_0013 — détails (3/3)

## FUN_0045f2a1 — 0x45f2a1

- Classification : internal
- Corps : `0x45f2a1–0x45f336`
- État : pseudocode obtenu
- Evidence : `ev_166ec7236cb49a5bd45dcbc859b69f029d1132243f92ee2e155015d72a50dedd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4021ad` — `thunk_FUN_004641de`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045f2a1(int param_1,undefined4 param_2,int *param_3,int *param_4,int *param_5)

{
  int iVar1;
  
  *param_5 = 0xffff;
  *param_4 = 0xffff;
  *param_3 = 0xffff;
  if (param_1 != 0) {
    iVar1 = thunk_FUN_004641de(*(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x10));
    *param_3 = (int)*(short *)(iVar1 + 6) * (*(short *)(param_1 + 0x4a) + 1);
    *param_4 = (int)*(short *)(iVar1 + 10) * (*(short *)(param_1 + 0x4a) + 1);
    *param_5 = (int)*(short *)(iVar1 + 8) * (*(short *)(param_1 + 0x4a) + 1);
  }
  return;
}
```

---

---

## FUN_0045f337 — 0x45f337

- Classification : internal
- Corps : `0x45f337–0x45f4f4`
- État : pseudocode obtenu
- Evidence : `ev_d22a1eae81f90bf0a91044b05de09fc09d58c4b47dfc01072416258ddeaa8174`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014e7` — `thunk_FUN_0045035a`
- `0x4017bc` — `thunk_FUN_0045f807`
- `0x4018b6` — `thunk_FUN_0045ff3f`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x401c94` — `thunk_FUN_0045f2a1`
- `0x4020bd` — `thunk_FUN_0045c9fe`
- `0x4021ad` — `thunk_FUN_004641de`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0045f337(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int in_ECX;
  undefined2 extraout_var;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (param_1 != 0) {
    uVar1 = thunk_FUN_0045035a();
    iVar2 = thunk_FUN_0045ff3f(CONCAT22(extraout_var,*(undefined2 *)(param_1 + 8)),uVar1);
    if (iVar2 == 0) {
      local_8 = thunk_FUN_00450385();
      if ((local_8 != 0) && (iVar2 = thunk_FUN_0045c9fe(), iVar2 != 0)) {
        return 0;
      }
      local_c = (in_ECX + -0x6191b8) / 0x14a0;
      if ((((param_2 == 0) ||
           ((((*(int *)(param_2 + 4) == 0 && (*(int *)(param_2 + 0x14) == -1)) &&
             (((int)*(char *)(param_2 + 0x22) & 1 << ((byte)local_c & 0x1f)) != 0)) &&
            (((*(int *)(param_2 + 0x10) != 1 || (*(int *)(param_2 + 0x24) < 5)) ||
             (0x21 < *(int *)(param_2 + 0x24))))))) &&
          (((*(int *)(param_1 + 0x14) == local_c && (0x24 < *(int *)(param_1 + 0x10))) &&
           ((*(int *)(param_1 + 0x10) < 0x35 &&
            (((*(int *)(param_1 + 0x10) != 0x28 && ((*(uint *)(param_1 + 0x1c) & 0x90) == 0)) &&
             (local_10 = thunk_FUN_0045f807(), local_10 != 0)))))))) &&
         ((thunk_FUN_0045f2a1(param_1,param_2,&local_1c,&local_18,&local_14),
          *(int *)(in_ECX + 0x13c0) != 0 ||
          (((local_1c <= *(short *)(local_10 + 0x28) && (local_18 <= *(short *)(local_10 + 0x2a)))
           && (local_14 <= *(short *)(local_10 + 0x2c))))))) {
        if (param_2 != 0) {
          piVar3 = (int *)thunk_FUN_004641de(local_c,*(undefined4 *)(param_1 + 0x10));
          local_20 = *piVar3;
          if (1 < *(short *)(param_1 + 0x4a)) {
            local_20 = local_20 + 1;
          }
          if (*(int *)(param_2 + 0xc) < local_20) {
            return 0;
          }
        }
        return 1;
      }
    }
  }
  return 0;
}
```

---

---

## FUN_0045f4f5 — 0x45f4f5

- Classification : internal
- Corps : `0x45f4f5–0x45f5c4`
- État : pseudocode obtenu
- Evidence : `ev_598cfe2b014b15e607c8b41ac943b5dd6af4e3db3c818406a1653591e00c406a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014e7` — `thunk_FUN_0045035a`
- `0x4017bc` — `thunk_FUN_0045f807`
- `0x401c94` — `thunk_FUN_0045f2a1`
- `0x401faa` — `thunk_FUN_0045f337`
- `0x402180` — `thunk_FUN_004533fb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045f4f5(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  int in_ECX;
  short local_14 [2];
  int local_10;
  short local_c [2];
  short local_8 [2];
  
  if (((*(int *)(in_ECX + 0x13c0) == 0) && (iVar2 = thunk_FUN_0045f337(param_1,0), iVar2 != 0)) &&
     (local_10 = thunk_FUN_0045f807(), local_10 != 0)) {
    thunk_FUN_0045f2a1(param_1,0,local_14,local_8,local_c);
    *(short *)(local_10 + 0x28) = *(short *)(local_10 + 0x28) - local_14[0];
    *(short *)(local_10 + 0x2a) = *(short *)(local_10 + 0x2a) - local_8[0];
    *(short *)(local_10 + 0x2c) = *(short *)(local_10 + 0x2c) - local_c[0];
    *(undefined2 *)(in_ECX + 0x13ba) = *(undefined2 *)(param_1 + 8);
    uVar1 = thunk_FUN_0045035a();
    *(undefined2 *)(in_ECX + 0x13bc) = uVar1;
    thunk_FUN_004533fb();
    *(undefined4 *)(in_ECX + 0x13c0) = 1;
  }
  return;
}
```

---

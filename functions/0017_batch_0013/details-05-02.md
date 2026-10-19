# 0017_batch_0013 — détails (2/3)

## FUN_00465614 — 0x465614

- Classification : internal
- Corps : `0x465614–0x46562a`
- État : pseudocode obtenu
- Evidence : `ev_36bbbad5456621cd8eaea00837e4a0370a2c60f31933964c2ac69c069ae5af56`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00465614(void)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x2cd40) = 0;
  return;
}
```

---

---

## FUN_0046562b — 0x46562b

- Classification : internal
- Corps : `0x46562b–0x4656d5`
- État : pseudocode obtenu
- Evidence : `ev_fd7d84c3c921f63a87acb8c96ced7eaf23eb105f65c68340e3953e66ed314a18`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0046562b(int param_1,int param_2)

{
  int in_ECX;
  int *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  local_14 = (int *)(in_ECX + 0x275a0);
  local_10 = 0;
  while ((local_10 < 0x100 && (local_c < (int)(uint)*(ushort *)(in_ECX + 0x2c1a0)))) {
    if (((*local_14 != -1) && (local_c = local_c + 1, *local_14 == param_1)) &&
       ((param_2 == -1 || (local_14[1] == param_2)))) {
      *(undefined2 *)(in_ECX + 0x2cd9c + local_8 * 2) = (undefined2)local_10;
      local_8 = local_8 + 1;
    }
    local_10 = local_10 + 1;
    local_14 = local_14 + 0x13;
  }
  return local_8;
}
```

---

---

## FUN_004656d6 — 0x4656d6

- Classification : internal
- Corps : `0x4656d6–0x465792`
- État : pseudocode obtenu
- Evidence : `ev_3a2f8a74847e72c79376579000a41c68300e1cc411d3765726fd26e727bde038`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004656d6(int param_1,int param_2)

{
  int in_ECX;
  int *local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  local_14 = (int *)(in_ECX + 0x275a0);
  local_10 = 0;
  while ((local_10 < 0x100 && (local_c < (int)(uint)*(ushort *)(in_ECX + 0x2c1a0)))) {
    if (((*local_14 != -1) && (local_c = local_c + 1, *(short *)((int)local_14 + 0xe) == param_1))
       && ((param_2 == -2 || (((param_2 == -1 && (*local_14 != 4)) || (param_2 == *local_14)))))) {
      *(undefined2 *)(in_ECX + 0x2cd9c + local_8 * 2) = (undefined2)local_10;
      local_8 = local_8 + 1;
    }
    local_10 = local_10 + 1;
    local_14 = local_14 + 0x13;
  }
  return local_8;
}
```

---

---

## FUN_00465793 — 0x465793

- Classification : internal
- Corps : `0x465793–0x466220`
- État : pseudocode obtenu
- Evidence : `ev_90fc7b398e8cc430ee898f0371c196e285bf0f21c5cd78aa04fcdd060294d4ce`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401186` — `thunk_FUN_00453bf6`
- `0x40119a` — `thunk_FUN_0045ff6d`
- `0x4012f3` — `thunk_FUN_0045d867`
- `0x401334` — `thunk_FUN_0045f755`
- `0x40139d` — `thunk_FUN_0045fd91`
- `0x4013ac` — `thunk_FUN_0045f5c5`
- `0x40165e` — `thunk_FUN_00466637`
- `0x4016b3` — `thunk_FUN_0045ca1e`
- `0x4017bc` — `thunk_FUN_0045f807`
- `0x4018b6` — `thunk_FUN_0045ff3f`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x4019b5` — `thunk_FUN_0046562b`
- `0x401d1b` — `thunk_FUN_004662b7`
- `0x401d7f` — `thunk_FUN_00466b09`
- `0x401dbb` — `thunk_FUN_0045fe62`
- `0x401e6a` — `thunk_FUN_0045ffe2`
- `0x401e6f` — `thunk_FUN_0045da80`
- `0x401e7e` — `thunk_FUN_0045ff9b`
- `0x401f3c` — `thunk_FUN_0045f4f5`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402059` — `thunk_FUN_0045c9b5`
- `0x4020b3` — `thunk_FUN_00466533`
- `0x4020bd` — `thunk_FUN_0045c9fe`
- `0x4021e4` — `thunk_FUN_0045fb6f`
- `0x40224d` — `thunk_FUN_00450070`
- `0x40225c` — `thunk_FUN_00421ec1`
- `0x402347` — `thunk_FUN_004503bd`
- `0x4023bf` — `thunk_FUN_0045c3bb`
- `0x40249b` — `thunk_FUN_0045dcf4`
- `0x4024e1` — `thunk_FUN_0045d8b2`

### Chaînes référencées

- `0x4a51dc` — "FALSE"
- `0x4a51e4` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
void FUN_00465793(short *param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int in_ECX;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  uint uVar8;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  undefined2 extraout_var_03;
  undefined4 uVar9;
  
  if (*param_1 == 1) {
    iVar4 = (int)param_1[2];
    if (((iVar4 == 0x10) || (iVar4 == 0x12)) && (param_1[4] != -1)) {
      iVar5 = thunk_FUN_00450385();
      if (iVar5 != 0) {
        thunk_FUN_0045d867(iVar4,CONCAT22(extraout_var,param_1[6]));
      }
    }
    else if (((iVar4 == 0x11) || (iVar4 == 0x13)) && (param_1[4] != -1)) {
      iVar5 = in_ECX + param_1[3] * 0x29e8 + 0x428 + param_1[4] * 0x60;
      iVar6 = thunk_FUN_00450385();
      if ((*(short *)(iVar5 + 0x18) != -1) && (iVar6 != 0)) {
        thunk_FUN_0045d8b2(iVar4,param_1[5],CONCAT22((short)((uint)iVar5 >> 0x10),param_1[6]));
      }
    }
    else if (iVar4 == 0xf) {
      iVar4 = thunk_FUN_00450385();
      if (iVar4 != 0) {
        thunk_FUN_0045dcf4();
      }
    }
    else if (iVar4 == 2) {
      iVar4 = thunk_FUN_00450385();
      if (iVar4 != 0) {
        iVar4 = thunk_FUN_0045c9fe();
        if (iVar4 == 0) {
          thunk_FUN_0045c9b5();
        }
        else {
          thunk_FUN_0045ca1e();
        }
      }
    }
    else if (iVar4 == 3) {
      iVar4 = thunk_FUN_0045ff3f(param_1[3],param_1[4]);
      if (iVar4 == 0) {
        thunk_FUN_0045fd91(param_1[3],CONCAT22(extraout_var_02,param_1[4]));
      }
      else {
        thunk_FUN_0045ff9b(param_1[3],CONCAT22(extraout_var_00,param_1[4]));
      }
    }
    else if (iVar4 == 0) {
      thunk_FUN_00453bf6((*(uint *)(in_ECX + param_1[3] * 0x29e8 + param_1[4] * 0x60 + 0x444) &
                         0x400) == 0);
    }
    else if ((0x14 < iVar4) && (iVar4 < 0x1d)) {
      sVar1 = param_1[3];
      sVar2 = param_1[4];
      iVar5 = thunk_FUN_00450385();
      if (iVar5 != 0) {
        uVar9 = CONCAT22(extraout_var_03,param_1[6]);
        uVar8 = (uint)(ushort)param_1[5];
        uVar7 = thunk_FUN_00450070(in_ECX + sVar1 * 0x29e8 + 0x428 + sVar2 * 0x60,iVar4,uVar8,uVar9)
        ;
        thunk_FUN_0045da80(uVar7,uVar8,uVar9);
      }
    }
  }
  else if (*param_1 == 0) {
    thunk_FUN_004662b7(param_1);
  }
  else if (*param_1 == 3) {
    if (param_1[2] == 0) {
      *(uint *)(in_ECX + param_1[3] * 0x29e8 + 0x29bc + param_1[1] * 4) =
           *(uint *)(in_ECX + param_1[3] * 0x29e8 + 0x29bc + param_1[1] * 4) ^ 1;
    }
    else if (param_1[2] == 1) {
      thunk_FUN_00466637(5,param_1[5],param_1[6]);
    }
    else if (param_1[2] == 2) {
      if (param_1[6] == 0) {
        thunk_FUN_0045f755(param_1[7],0xffffffff);
      }
      else {
        iVar4 = in_ECX + param_1[1] * 0x14a0 + 0x2d098 + param_1[4] * 100;
        iVar5 = thunk_FUN_0045c3bb();
        if (iVar5 != 0) {
          if (param_1[7] == 0) {
            *(uint *)(iVar4 + 0x58) = (uint)(*(int *)(iVar4 + 0x58) == 0);
          }
          else {
            *(uint *)(iVar4 + 0x5c) = (uint)(*(int *)(iVar4 + 0x5c) == 0);
          }
        }
      }
    }
    else if (param_1[2] == 3) {
      iVar4 = thunk_FUN_0046562b((int)param_1[1],8);
      if (iVar4 != 0) {
        *(short *)(in_ECX + 0x2e41c + param_1[1] * 0x14a0) = param_1[7];
        iVar4 = in_ECX + 0x275a0 + *(short *)(in_ECX + 0x2cd9c) * 0x4c;
        thunk_FUN_00421ec1(0xffffffff);
        *(short *)(iVar4 + 0x40) = param_1[5];
        *(undefined4 *)(iVar4 + 0x3c) = 0x13;
        *(short *)(iVar4 + 0x42) = param_1[6];
        *(undefined2 *)(iVar4 + 0x44) = 0x16;
        *(undefined2 *)(iVar4 + 0x46) = 0;
      }
    }
    else if (param_1[2] == 4) {
      if ((0 < *(short *)(in_ECX + param_1[1] * 0x14a0 + 0x2cfe4 + param_1[7] * 2)) &&
         (iVar4 = thunk_FUN_004503bd((int)param_1[7],1,(int)param_1[1]), iVar4 != 0)) {
        *(short *)(in_ECX + param_1[1] * 0x14a0 + 0x2cfe4 + param_1[7] * 2) =
             *(short *)(in_ECX + param_1[1] * 0x14a0 + 0x2cfe4 + param_1[7] * 2) + -1;
      }
    }
    else if (param_1[2] == 5) {
      thunk_FUN_0045f4f5(in_ECX + param_1[5] * 0x29e8 + 0x428 + param_1[6] * 0x60);
    }
    else if (param_1[2] == 6) {
      thunk_FUN_0045f5c5(in_ECX + param_1[5] * 0x29e8 + 0x428 + param_1[6] * 0x60);
    }
    else if (param_1[2] == 10) {
      iVar5 = (int)param_1[6];
      iVar4 = in_ECX + 0x2cfa0 + param_1[1] * 0x14a0;
      if (param_1[7] == 0) {
        *(uint *)(iVar4 + 0xd8 + iVar5 * 4) = (uint)(*(int *)(iVar4 + 0xd8 + iVar5 * 4) == 0);
      }
      else {
        *(uint *)(iVar4 + 0xe8 + iVar5 * 4) = (uint)(*(int *)(iVar4 + 0xe8 + iVar5 * 4) == 0);
      }
    }
    else if (param_1[2] == 0xb) {
      sVar1 = param_1[3];
      sVar2 = param_1[4];
      sVar3 = param_1[5];
      iVar4 = thunk_FUN_0045f807();
      iVar5 = thunk_FUN_0045f807();
      if (iVar4 != 0) {
        if (sVar1 < 0) {
          sVar1 = 0;
        }
        if (*(short *)(iVar4 + 0x28) < sVar1) {
          sVar1 = *(short *)(iVar4 + 0x28);
        }
        if (sVar2 < 0) {
          sVar2 = 0;
        }
        if (*(short *)(iVar4 + 0x2a) < sVar2) {
          sVar2 = *(short *)(iVar4 + 0x2a);
        }
        if (sVar3 < 0) {
          sVar3 = 0;
        }
        if (*(short *)(iVar4 + 0x2c) < sVar3) {
          sVar3 = *(short *)(iVar4 + 0x2c);
        }
        if (iVar5 != 0) {
          *(short *)(iVar4 + 0x28) = *(short *)(iVar4 + 0x28) - sVar1;
          *(short *)(iVar4 + 0x2a) = *(short *)(iVar4 + 0x2a) - sVar2;
          *(short *)(iVar4 + 0x2c) = *(short *)(iVar4 + 0x2c) - sVar3;
          *(short *)(iVar5 + 0x28) = *(short *)(iVar5 + 0x28) + sVar1;
          *(short *)(iVar5 + 0x2a) = *(short *)(iVar5 + 0x2a) + sVar2;
          *(short *)(iVar5 + 0x2c) = *(short *)(iVar5 + 0x2c) + sVar3;
        }
      }
    }
    else if (param_1[2] == 0xc) {
      iVar4 = in_ECX + 0x2c1a4 + param_1[6] * 0x14;
      if (((*(short *)(iVar4 + 8) == param_1[1]) && (*(short *)(iVar4 + 10) == param_1[3])) &&
         ((*(short *)(iVar4 + 0x10) == param_1[4] && (*(short *)(iVar4 + 0x12) == param_1[5])))) {
        if ((-1 < *(short *)(iVar4 + 8)) && (*(short *)(iVar4 + 8) < 4)) {
          thunk_FUN_0045fb6f((iVar4 - (in_ECX + 0x2c1a4)) / 0x14);
        }
        thunk_FUN_00466533((iVar4 - (in_ECX + 0x2c1a4)) / 0x14);
      }
    }
    else if (((((param_1[2] == 0xd) || (param_1[2] == 0xe)) || (param_1[2] == 0xf)) &&
             ((iVar4 = in_ECX + 0x2c1a4 + param_1[6] * 0x14, *(short *)(iVar4 + 8) == param_1[1] &&
              (*(short *)(iVar4 + 10) == param_1[3])))) &&
            ((*(short *)(iVar4 + 0x10) == param_1[4] && (*(short *)(iVar4 + 0x12) == param_1[5]))))
    {
      *(short *)(iVar4 + 6) = param_1[2] + -0xc;
    }
  }
  else if (*param_1 == 2) {
    if (param_1[2] == 0x14) {
      iVar4 = thunk_FUN_0045ff6d(param_1[3],param_1[4]);
      if (iVar4 == 0) {
        thunk_FUN_0045fe62(param_1[3],CONCAT22(extraout_var_01,param_1[4]));
      }
      else {
        thunk_FUN_0045ffe2(param_1[3],param_1[4]);
      }
    }
    else if (param_1[2] == 9) {
      thunk_FUN_00466b09((int)param_1[1],param_1[3],param_1[5]);
    }
  }
  else {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a51e4,0x7f2,s_FALSE_004a51dc);
  }
  return;
}
```

---

---

## FUN_00466221 — 0x466221

- Classification : internal
- Corps : `0x466221–0x4662b6`
- État : pseudocode obtenu
- Evidence : `ev_63d9efb5bce1c51e26da896805829764236e9140de5f842cda6ad015f1c8ad1b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401307` — `thunk_FUN_00465793`
- `0x4016f9` — `thunk_FUN_004672ef`
- `0x401794` — `thunk_FUN_004140a8`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x4a51fc` — "Bad command %d.\n"
- `0x4a5210` — "FALSE"
- `0x4a5218` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
void FUN_00466221(void)

{
  int iVar1;
  int *piVar2;
  
  while (piVar2 = (int *)thunk_FUN_004140a8(), piVar2 != (int *)0x0) {
    iVar1 = *piVar2;
    if (iVar1 != 0) {
      if (iVar1 == 1) {
        thunk_FUN_00465793(piVar2 + 1);
      }
      else if (iVar1 == 2) {
        thunk_FUN_004672ef(piVar2 + 1);
      }
      else {
        thunk_FUN_00414ad0(s_Bad_command__d__004a51fc,iVar1);
        thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a5218,0x819,s_FALSE_004a5210);
      }
    }
  }
  return;
}
```

---

---

## FUN_004662b7 — 0x4662b7

- Classification : internal
- Corps : `0x4662b7–0x466532`
- État : pseudocode obtenu
- Evidence : `ev_db281f9a7a1fbb3e9bd29b7389912081c306195183d45c11b3bae8830ccff761`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004662b7(int param_1)

{
  short sVar1;
  int in_ECX;
  int local_c;
  int local_8;
  
  local_8 = -1;
  local_c = 0;
  do {
    if (0x3f < local_c) {
LAB_004663e9:
      if ((local_8 != -1) &&
         ((sVar1 = *(short *)(in_ECX + 0x2c1b4 + local_8 * 0x14), sVar1 == 5 || (sVar1 == 0xd)))) {
        for (local_c = 0; local_c < 0x40; local_c = local_c + 1) {
          if ((((local_c != local_8) && (*(int *)(in_ECX + 0x2c1a4 + local_c * 0x14) != 0)) &&
              (*(short *)(in_ECX + 0x2c1b4 + local_c * 0x14) == sVar1)) &&
             (((*(short *)(in_ECX + 0x2c1ac + local_c * 0x14) ==
                *(short *)(in_ECX + 0x2c1ac + local_8 * 0x14) &&
               (*(short *)(in_ECX + 0x2c1ae + local_c * 0x14) ==
                *(short *)(in_ECX + 0x2c1ae + local_8 * 0x14))) &&
              (*(short *)(in_ECX + 0x2c1b2 + local_c * 0x14) ==
               *(short *)(in_ECX + 0x2c1b2 + local_8 * 0x14))))) {
            *(undefined4 *)(in_ECX + 0x2c1a4 + local_8 * 0x14) = 0;
            *(short *)(in_ECX + 0x2c6a4) = *(short *)(in_ECX + 0x2c6a4) + -1;
            return -1;
          }
        }
      }
      return local_8;
    }
    if (*(int *)(in_ECX + 0x2c1a4 + local_c * 0x14) == 0) {
      *(undefined2 *)(in_ECX + 0x2c1ac + local_c * 0x14) = *(undefined2 *)(param_1 + 2);
      *(undefined2 *)(in_ECX + 0x2c1b4 + local_c * 0x14) = *(undefined2 *)(param_1 + 4);
      *(undefined2 *)(in_ECX + 0x2c1ae + local_c * 0x14) = *(undefined2 *)(param_1 + 10);
      *(undefined2 *)(in_ECX + 0x2c1b0 + local_c * 0x14) = *(undefined2 *)(param_1 + 8);
      *(undefined2 *)(in_ECX + 0x2c1b2 + local_c * 0x14) = *(undefined2 *)(param_1 + 0xc);
      *(undefined2 *)(in_ECX + 0x2c1b6 + local_c * 0x14) = *(undefined2 *)(param_1 + 0xe);
      *(undefined4 *)(in_ECX + 0x2c1a4 + local_c * 0x14) = 1;
      *(undefined2 *)(in_ECX + 0x2c1a8 + local_c * 0x14) = 0;
      *(undefined2 *)(in_ECX + 0x2c1aa + local_c * 0x14) = 1;
      local_8 = local_c;
      *(short *)(in_ECX + 0x2c6a4) = *(short *)(in_ECX + 0x2c6a4) + 1;
      goto LAB_004663e9;
    }
    local_c = local_c + 1;
  } while( true );
}
```

---

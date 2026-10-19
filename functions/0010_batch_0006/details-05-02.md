# 0010_batch_0006 — détails (2/2)

## FUN_0041fd57 — 0x41fd57

- Classification : internal
- Corps : `0x41fd57–0x41fdd8`
- État : pseudocode obtenu
- Evidence : `ev_ae71433afd41cc15eaf02e49fb748ef7e549de55fec4101782cdc94f26e03bb4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f78` — `thunk_FUN_00420721`
- `0x40225c` — `thunk_FUN_00421ec1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041fd57(int param_1)

{
  short sVar1;
  int *in_ECX;
  
  sVar1 = thunk_FUN_00420721();
  if (((0 < sVar1) && (*in_ECX == 4)) && ((in_ECX[0xf] == 0 || (in_ECX[0xf] == 0xe)))) {
    thunk_FUN_00421ec1(0xffffffff);
    in_ECX[0xf] = 6;
    *(undefined2 *)(in_ECX + 0x10) = *(undefined2 *)((int)in_ECX + 0xe);
    *(short *)((int)in_ECX + 0x42) = (short)((param_1 + -0x6137b8) / 0x4c);
    *(undefined2 *)((int)in_ECX + 0x46) = 0;
  }
  return;
}
```

---

---

## FUN_0041fdd9 — 0x41fdd9

- Classification : internal
- Corps : `0x41fdd9–0x41fde5`
- État : pseudocode obtenu
- Evidence : `ev_1b593505b657fc46ba3a2a93047d09838680f6f7017f071c48929458103f617c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041fdd9(void)

{
  return;
}
```

---

---

## FUN_0041fde6 — 0x41fde6

- Classification : internal
- Corps : `0x41fde6–0x41ff2d`
- État : pseudocode obtenu
- Evidence : `ev_d6c1c016e4cf058e9bd4ab7e903661d2d11e88cb65a71f512af85a2ca2c506b1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018cf` — `thunk_FUN_0041ff2e`
- `0x401933` — `thunk_FUN_00464242`
- `0x401dac` — `thunk_FUN_004207f2`
- `0x4023bf` — `thunk_FUN_0045c3bb`
- `0x4023dd` — `thunk_FUN_0041ff56`
- `0x4024be` — `thunk_FUN_004207c2`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0041fde6(void)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  int *in_ECX;
  int local_c;
  
  local_c = 0;
  iVar3 = thunk_FUN_004207c2();
  if (iVar3 == 0) {
    iVar3 = thunk_FUN_00464242(*in_ECX,in_ECX[1]);
    local_c = (int)*(short *)(iVar3 + 10);
  }
  iVar3 = thunk_FUN_004207f2();
  if (iVar3 != 0) {
    iVar3 = thunk_FUN_0045c3bb();
    if ((*(uint *)(iVar3 + 0x1c) & 0x8000) != 0) {
      local_c = local_c + 3;
    }
    uVar1 = *(ushort *)(&DAT_00619242 + *in_ECX * 0x14a0);
    if (((uVar1 & 1) == 0) || (*(int *)(iVar3 + 0x10) != 0x2c)) {
      if (((uVar1 & 0x40) == 0) || (*(int *)(iVar3 + 0x10) != 0x2d)) {
        if (((uVar1 & 0x400) != 0) && (*(int *)(iVar3 + 0x10) == 0x2e)) {
          local_c = local_c + 1;
        }
      }
      else {
        local_c = local_c + 1;
      }
    }
    else {
      local_c = local_c + 1;
    }
  }
  if (*in_ECX == 4) {
    sVar2 = thunk_FUN_0041ff2e();
    local_c = local_c + sVar2 * 3;
    sVar2 = thunk_FUN_0041ff56();
    local_c = local_c + (sVar2 * local_c) / 0x16;
  }
  else {
    sVar2 = thunk_FUN_0041ff2e();
    local_c = local_c + sVar2 * 2;
  }
  return local_c;
}
```

---

---

## FUN_0041ff2e — 0x41ff2e

- Classification : internal
- Corps : `0x41ff2e–0x41ff55`
- État : pseudocode obtenu
- Evidence : `ev_5657139eb84e6c0d378ad0241d5d105f78d2d014574f3ccfa0932e019a2cb8d3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_0041ff2e(void)

{
  int in_ECX;
  
  return CONCAT22((short)((uint)in_ECX >> 0x10),*(undefined2 *)(in_ECX + 10)) & 0xffff000f;
}
```

---

---

## FUN_0041ff56 — 0x41ff56

- Classification : internal
- Corps : `0x41ff56–0x41ff8a`
- État : pseudocode obtenu
- Evidence : `ev_1969d301e2bb55487d30e6894bb72a889d47852e7438ef91922c67decedb7bef`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
short FUN_0041ff56(void)

{
  int in_ECX;
  
  return (short)(*(ushort *)(in_ECX + 10) & 0xf0) >> 4;
}
```

---

---

## FUN_0041ff8b — 0x41ff8b

- Classification : internal
- Corps : `0x41ff8b–0x41ffc3`
- État : pseudocode obtenu
- Evidence : `ev_a61f4aee10f374e037ed6b871c881c4c0545b7ec3bf258bce0f2951311a26bbf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041ff8b(ushort param_1)

{
  int in_ECX;
  
  if (5 < (short)param_1) {
    param_1 = 5;
  }
  *(ushort *)(in_ECX + 10) = *(ushort *)(in_ECX + 10) & 0xf0 | param_1 & 0xf;
  return;
}
```

---

---

## FUN_0041ffc4 — 0x41ffc4

- Classification : internal
- Corps : `0x41ffc4–0x42000a`
- État : pseudocode obtenu
- Evidence : `ev_c1565505fc2c3ec0bf909b7021f22c7851352e7b262481c54fed5e83971d59f5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0041ffc4(ushort param_1)

{
  int in_ECX;
  
  if (0xb < (short)param_1) {
    param_1 = 0xb;
  }
  *(ushort *)(in_ECX + 10) = *(ushort *)(in_ECX + 10) & 0xf | (param_1 & 0xf) << 4;
  return;
}
```

---

---

## FUN_0042000b — 0x42000b

- Classification : internal
- Corps : `0x42000b–0x42003b`
- État : pseudocode obtenu
- Evidence : `ev_bd2cb1d9335b0dfff1570385a73e1fd7c0b7002ad4c3c38c09ed7296f6d993a2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a0f` — `thunk_FUN_0041ffc4`
- `0x4023dd` — `thunk_FUN_0041ff56`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042000b(void)

{
  undefined2 extraout_var;
  undefined2 local_8;
  
  local_8 = thunk_FUN_0041ff56();
  local_8 = local_8 + 1;
  thunk_FUN_0041ffc4(CONCAT22(extraout_var,local_8));
  return;
}
```

---

---

## FUN_0042003c — 0x42003c

- Classification : internal
- Corps : `0x42003c–0x4200d1`
- État : pseudocode obtenu
- Evidence : `ev_a6571c6863d26a9a1fc4acc6ce42bbe5cad9fb8d7298f7ccb5330b96e003f32f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401933` — `thunk_FUN_00464242`
- `0x401dac` — `thunk_FUN_004207f2`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_0042003c(undefined4 param_1)

{
  int iVar1;
  undefined4 *in_ECX;
  uint local_c;
  
  iVar1 = thunk_FUN_00464242(*in_ECX,param_1);
  local_c = (uint)*(short *)(iVar1 + 2);
  iVar1 = thunk_FUN_004207f2();
  if (iVar1 != 0) {
    iVar1 = thunk_FUN_0045c3bb();
    if ((*(uint *)(iVar1 + 0x1c) & 0x10000) == 0) {
      if (((*(uint *)(iVar1 + 0x1c) & 0x20000) != 0) && (local_c = local_c - 1, (int)local_c < 0)) {
        local_c = 3;
      }
    }
    else {
      local_c = local_c + 1;
      if (3 < (int)local_c) {
        local_c = 0;
      }
    }
  }
  return local_c & 0xffff;
}
```

---

---

## FUN_004200d2 — 0x4200d2

- Classification : internal
- Corps : `0x4200d2–0x420187`
- État : pseudocode obtenu
- Evidence : `ev_ad5590e5bdd229ea3ac351753a2221b9d2393fc5bb358b9f475119209abbe728`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010d7` — `thunk_FUN_0042003c`
- `0x4011ea` — `thunk_FUN_0041fde6`
- `0x401cc1` — `thunk_FUN_0041fd57`
- `0x40219e` — `thunk_FUN_00420217`
- `0x4024be` — `thunk_FUN_004207c2`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004200d2(void)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *in_ECX;
  undefined4 local_14;
  
  uVar2 = thunk_FUN_0041fde6();
  local_14 = in_ECX[1];
  iVar3 = thunk_FUN_004207c2();
  if (iVar3 != 0) {
    local_14 = 0;
  }
  sVar1 = thunk_FUN_0042003c(local_14);
  iVar3 = thunk_FUN_00420217(uVar2,(int)sVar1,*in_ECX);
  thunk_FUN_0041fd57(in_ECX);
  if (0 < iVar3) {
    *(short *)(in_ECX + 2) = *(short *)(in_ECX + 2) + 1;
  }
  if (0 < *(short *)((int)in_ECX + 0x22)) {
    *(short *)((int)in_ECX + 0x22) = *(short *)((int)in_ECX + 0x22) + -1;
  }
  return iVar3;
}
```

---

---

## FUN_00420188 — 0x420188

- Classification : internal
- Corps : `0x420188–0x420216`
- État : pseudocode obtenu
- Evidence : `ev_f961a5617f0ea77c8f7d5f211856963862326a35ce98f1af89be81e70cd5c196`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011ea` — `thunk_FUN_0041fde6`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x4024eb` — `thunk_FUN_00450817`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00420188(void)

{
  int iVar1;
  int in_ECX;
  undefined4 local_8;
  
  local_8 = thunk_FUN_0041fde6();
  if (local_8 < 1) {
    local_8 = 1;
  }
  local_8 = thunk_FUN_00467260(local_8);
  local_8 = local_8 + 1;
  if (6 < local_8) {
    local_8 = 6;
  }
  iVar1 = thunk_FUN_00450817(local_8);
  if (0 < iVar1) {
    *(short *)(in_ECX + 8) = *(short *)(in_ECX + 8) + 1;
  }
  if (0 < *(short *)(in_ECX + 0x22)) {
    *(short *)(in_ECX + 0x22) = *(short *)(in_ECX + 0x22) + -1;
  }
  return iVar1;
}
```

---

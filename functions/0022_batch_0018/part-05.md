# 0022_batch_0018 — détails (5/5)

## FUN_00489040 — 0x489040

- Classification : internal
- Corps : `0x489040–0x4893b1`
- État : pseudocode obtenu
- Evidence : `ev_cf93044a37e7350650c79a1d660fcb777261d2be598214c2ae30a8ae7e8cfcab`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x486e30` — `FUN_00486e30`
- `0x4895f0` — `FUN_004895f0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_00489040(uint param_1,double *param_2,uint param_3)

{
  double dVar1;
  ulonglong uVar2;
  uint uVar3;
  float10 fVar4;
  undefined8 local_44;
  undefined8 local_3c;
  undefined8 local_34;
  undefined8 local_2c;
  int local_1c;
  int local_18;
  undefined8 local_14;
  uint local_c;
  uint local_8;
  
  local_8 = param_1 & 0x1f;
  if (((param_1 & 8) == 0) || ((param_3 & 1) == 0)) {
    if (((param_1 & 4) == 0) || ((param_3 & 4) == 0)) {
      if (((param_1 & 1) == 0) || ((param_3 & 8) == 0)) {
        if (((param_1 & 2) != 0) && ((param_3 & 0x10) != 0)) {
          local_c = (uint)((param_1 & 0x10) != 0);
          if (*param_2 == 0.0) {
            local_c = 1;
          }
          else {
            fVar4 = (float10)FUN_00486e30(*(undefined4 *)param_2,*(undefined4 *)((int)param_2 + 4),
                                          &local_1c);
            dVar1 = (double)fVar4;
            local_18 = local_1c + -0x600;
            if (local_18 < -0x432) {
              local_14 = dVar1 * 0.0;
              local_c = 1;
            }
            else {
              local_14 = (double)((ulonglong)dVar1 & 0xfffffffffffff);
              local_14 = (double)((ulonglong)local_14 | 0x10000000000000);
              for (; local_18 < -0x3fd; local_18 = local_18 + 1) {
                if ((((ulonglong)local_14 & 1) != 0) && (local_c == 0)) {
                  local_c = 1;
                }
                uVar3 = (uint)local_14 >> 1;
                uVar2 = (ulonglong)local_14 & 0x100000000;
                local_14._0_4_ = uVar3;
                if (uVar2 != 0) {
                  local_14._0_4_ = uVar3 | 0x80000000;
                }
                local_14 = (double)CONCAT44(local_14._4_4_ >> 1,(uint)local_14);
              }
              if (dVar1 < 0.0) {
                local_14 = -local_14;
              }
            }
            *(uint *)param_2 = (uint)local_14;
            *(uint *)((int)param_2 + 4) = local_14._4_4_;
          }
          if (local_c != 0) {
            FUN_004895f0(0x10);
          }
          local_8 = local_8 & 0xfffffffd;
        }
      }
      else {
        FUN_004895f0(8);
        uVar3 = param_3 & 0xc00;
        if (uVar3 < 0x401) {
          if (uVar3 == 0x400) {
            if (*param_2 <= 0.0) {
              local_3c = -(double)CONCAT44(DAT_004a8ed4,DAT_004a8ed0);
            }
            else {
              local_3c = (double)CONCAT44(DAT_004a8ee4,DAT_004a8ee0);
            }
            *(undefined4 *)param_2 = (undefined4)local_3c;
            *(undefined4 *)((int)param_2 + 4) = local_3c._4_4_;
          }
          else if (uVar3 == 0) {
            if (*param_2 <= 0.0) {
              local_2c = -(double)CONCAT44(DAT_004a8ed4,DAT_004a8ed0);
            }
            else {
              local_2c = (double)CONCAT44(DAT_004a8ed4,DAT_004a8ed0);
            }
            *(undefined4 *)param_2 = (undefined4)local_2c;
            *(undefined4 *)((int)param_2 + 4) = local_2c._4_4_;
          }
        }
        else if (uVar3 == 0x800) {
          if (*param_2 <= 0.0) {
            local_34 = -(double)CONCAT44(DAT_004a8ee4,DAT_004a8ee0);
          }
          else {
            local_34 = (double)CONCAT44(DAT_004a8ed4,DAT_004a8ed0);
          }
          *(undefined4 *)param_2 = (undefined4)local_34;
          *(undefined4 *)((int)param_2 + 4) = local_34._4_4_;
        }
        else if (uVar3 == 0xc00) {
          if (*param_2 <= 0.0) {
            local_44 = -(double)CONCAT44(DAT_004a8ee4,DAT_004a8ee0);
          }
          else {
            local_44 = (double)CONCAT44(DAT_004a8ee4,DAT_004a8ee0);
          }
          *(undefined4 *)param_2 = (undefined4)local_44;
          *(undefined4 *)((int)param_2 + 4) = local_44._4_4_;
        }
        local_8 = local_8 & 0xfffffffe;
      }
    }
    else {
      FUN_004895f0(4);
      local_8 = local_8 & 0xfffffffb;
    }
  }
  else {
    FUN_004895f0(1);
    local_8 = local_8 & 0xfffffff7;
  }
  if (((param_1 & 0x10) != 0) && ((param_3 & 0x20) != 0)) {
    FUN_004895f0(0x20);
    local_8 = local_8 & 0xffffffef;
  }
  return local_8 == 0;
}
```

---

## __umatherr — 0x4893c0

- Classification : internal
- Corps : `0x4893c0–0x48945a`
- État : pseudocode obtenu
- Evidence : `ev_0feff384bd082ceca69cab90be6195e6887a06859d51a256c4668eea6526badf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x489460` — `__set_errno`
- `0x4894a0` — `__get_fname`
- `0x489560` — `__matherr`
- `0x4895b0` — `FUN_004895b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __umatherr
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

float10 __umatherr(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                  undefined4 param_9)

{
  double dVar1;
  int iVar2;
  _exception local_24;
  
  local_24.name = (char *)__get_fname(param_2);
  if (local_24.name == (char *)0x0) {
    FUN_004895b0(param_9,0xffff);
    __set_errno(param_1);
    dVar1 = (double)CONCAT44(param_8,param_7);
  }
  else {
    local_24.type = param_1;
    local_24.arg1._0_4_ = param_3;
    local_24.arg1._4_4_ = param_4;
    local_24.arg2._0_4_ = param_5;
    local_24.arg2._4_4_ = param_6;
    local_24.retval._0_4_ = param_7;
    local_24.retval._4_4_ = param_8;
    FUN_004895b0(param_9,0xffff);
    iVar2 = __matherr(&local_24);
    if (iVar2 == 0) {
      __set_errno(param_1);
    }
    dVar1 = (double)CONCAT44(local_24.retval._4_4_,local_24.retval._0_4_);
  }
  return (float10)dVar1;
}
```

---

## __set_errno — 0x489460

- Classification : internal
- Corps : `0x489460–0x489497`
- État : pseudocode obtenu
- Evidence : `ev_06990d540135198f50a435652eee56e9bb4f92bbad536c25fbcacdd19a143f0a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Library Function - Single Match
    __set_errno
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

errno_t __cdecl __set_errno(int _Value)

{
  if (_Value == 1) {
    _DAT_0063251c = 0x21;
  }
  else if ((1 < _Value) && (_Value < 4)) {
    _DAT_0063251c = 0x22;
  }
  return _Value;
}
```

---

## __get_fname — 0x4894a0

- Classification : internal
- Corps : `0x4894a0–0x4894de`
- État : pseudocode obtenu
- Evidence : `ev_6b288986c2cb8366f0fa26dae45c3fa3918b2ea5011371812e836b6b1e3cba7d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __get_fname
   
   Library: Visual Studio */

undefined * __get_fname(int param_1)

{
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (0x1a < local_8) {
      return (undefined *)0x0;
    }
    if (*(int *)(&DAT_004a9020 + local_8 * 8) == param_1) break;
    local_8 = local_8 + 1;
  }
  return (&PTR_DAT_004a9024)[local_8 * 2];
}
```

---

## FUN_004894e0 — 0x4894e0

- Classification : internal
- Corps : `0x4894e0–0x489550`
- État : pseudocode obtenu
- Evidence : `ev_9430a9bdefec185e3cbf99a95f9fabb60eb3054814d80a883e0e01f029221c71`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004894e0(uint param_1)

{
  undefined4 local_8;
  
  if ((param_1 & 0x20) == 0) {
    if ((param_1 & 8) == 0) {
      if ((param_1 & 4) == 0) {
        if ((param_1 & 1) == 0) {
          if ((param_1 & 2) == 0) {
            local_8 = 0;
          }
          else {
            local_8 = 4;
          }
        }
        else {
          local_8 = 3;
        }
      }
      else {
        local_8 = 2;
      }
    }
    else {
      local_8 = 1;
    }
  }
  else {
    local_8 = 5;
  }
  return local_8;
}
```

---

## __matherr — 0x489560

- Classification : internal
- Corps : `0x489560–0x489566`
- État : pseudocode obtenu
- Evidence : `ev_2b960d6048708ffc61171d36b3adc9217d905e1c9de62e31ae57315b53dd9438`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __matherr
   
   Library: Visual Studio */

int __cdecl __matherr(_exception *_Except)

{
  return 0;
}
```

---

## FUN_00489570 — 0x489570

- Classification : internal
- Corps : `0x489570–0x489585`
- État : pseudocode obtenu
- Evidence : `ev_6f96e43491ecc45f434a13701fe865536876129aa27b5751c3edc51d191cbc1e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00489570(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}
```

---

## FUN_00489590 — 0x489590

- Classification : internal
- Corps : `0x489590–0x4895a6`
- État : pseudocode obtenu
- Evidence : `ev_4e3e75ec023d8e7de76812b40e7b2db1d8638dbf884b90084c1da3676b53ffb8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00489590(void)

{
  short in_FPUStatusWord;
  
  return (int)in_FPUStatusWord;
}
```

---

## FUN_004895b0 — 0x4895b0

- Classification : internal
- Corps : `0x4895b0–0x4895e1`
- État : pseudocode obtenu
- Evidence : `ev_abc53389851ec385416eaad4b0793b05da8b79d3efd2257c73e0288c261a3454`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004895b0(void)

{
  short in_FPUControlWord;
  
  return (int)in_FPUControlWord;
}
```

---

## FUN_004895f0 — 0x4895f0

- Classification : internal
- Corps : `0x4895f0–0x489664`
- État : pseudocode obtenu
- Evidence : `ev_b4eac6b411ce8ea3a4574651b1d19b58d4ee2d67dd06b891d1f611096c263c9c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004895f0(void)

{
  return;
}
```

---

## FUN_00489670 — 0x489670

- Classification : internal
- Corps : `0x489670–0x489ab2`
- État : pseudocode obtenu
- Evidence : `ev_80f6289b68ccacdb08340c95b11ade7b982cef43424f5ce71ecacf1a30fa8bee`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x488040` — `___addl`
- `0x488130` — `___shl_12`
- `0x488190` — `___shr_12`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00489670(int *param_1,int *param_2)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int local_3c;
  ushort local_38;
  int local_30;
  int local_2c;
  int local_24;
  ushort local_1c;
  undefined2 uStack_1a;
  short local_18 [6];
  int local_c;
  int local_8;
  
  local_18[4] = 0;
  local_8 = 0;
  local_1c = 0;
  uStack_1a = 0;
  local_18[0] = 0;
  local_18[1] = 0;
  local_18[2] = 0;
  local_18[3] = 0;
  uVar1 = *(ushort *)((int)param_1 + 10);
  uVar2 = *(ushort *)((int)param_2 + 10);
  uVar3 = uVar1 ^ uVar2;
  local_38 = (uVar1 & 0x7fff) + (uVar2 & 0x7fff);
  if ((((uVar1 & 0x7fff) < 0x7fff) && ((uVar2 & 0x7fff) < 0x7fff)) && (local_38 < 0xbffe)) {
    if (local_38 < 0x3fc0) {
      param_1[2] = 0;
      param_1[1] = 0;
      *param_1 = 0;
    }
    else if ((((uVar1 & 0x7fff) == 0) && (local_38 = local_38 + 1, (param_1[2] & 0x7fffffffU) == 0))
            && ((param_1[1] == 0 && (*param_1 == 0)))) {
      *(undefined2 *)((int)param_1 + 10) = 0;
    }
    else if ((((uVar2 & 0x7fff) == 0) && (local_38 = local_38 + 1, (param_2[2] & 0x7fffffffU) == 0))
            && ((param_2[1] == 0 && (*param_2 == 0)))) {
      param_1[2] = 0;
      param_1[1] = 0;
      *param_1 = 0;
    }
    else {
      local_30 = 0;
      for (local_24 = 0; local_24 < 5; local_24 = local_24 + 1) {
        local_2c = local_24 << 1;
        local_c = 8;
        for (local_3c = 5 - local_24; 0 < local_3c; local_3c = local_3c + -1) {
          iVar4 = ___addl(*(undefined4 *)((int)&local_1c + local_30),
                          (uint)*(ushort *)((int)param_1 + local_2c) *
                          (uint)*(ushort *)((int)param_2 + local_c),
                          (undefined4 *)((int)&local_1c + local_30));
          if (iVar4 != 0) {
            *(short *)((int)local_18 + local_30) = *(short *)((int)local_18 + local_30) + 1;
          }
          local_2c = local_2c + 2;
          local_c = local_c + -2;
        }
        local_30 = local_30 + 2;
      }
      local_38 = local_38 + 0xc002;
      while ((0 < (short)local_38 && ((local_18[3] & 0x8000U) == 0))) {
        ___shl_12(&local_1c);
        local_38 = local_38 - 1;
      }
      if ((short)local_38 < 1) {
        for (local_38 = local_38 - 1; (short)local_38 < 0; local_38 = local_38 + 1) {
          if ((local_1c & 1) != 0) {
            local_8 = local_8 + 1;
          }
          ___shr_12(&local_1c);
        }
        if (local_8 != 0) {
          local_1c = local_1c | 1;
        }
      }
      iVar4 = CONCAT22(local_18[0],uStack_1a);
      if ((0x8000 < local_1c) ||
         (iVar5 = CONCAT22(local_18[2],local_18[1]),
         (CONCAT22(uStack_1a,local_1c) & 0x1ffff) == 0x18000)) {
        if (CONCAT22(local_18[0],uStack_1a) == -1) {
          iVar4 = 0;
          if (CONCAT22(local_18[2],local_18[1]) == -1) {
            iVar5 = 0;
            if (local_18[3] == 0xffff) {
              local_18[3] = 0x8000;
              local_38 = local_38 + 1;
            }
            else {
              local_18[3] = local_18[3] + 1;
            }
          }
          else {
            iVar5 = CONCAT22(local_18[2],local_18[1]) + 1;
          }
        }
        else {
          iVar4 = CONCAT22(local_18[0],uStack_1a) + 1;
          iVar5 = CONCAT22(local_18[2],local_18[1]);
        }
      }
      local_18[0] = (short)((uint)iVar4 >> 0x10);
      uStack_1a = (undefined2)iVar4;
      local_18[2] = (short)((uint)iVar5 >> 0x10);
      local_18[1] = (short)iVar5;
      if (local_38 < 0x7fff) {
        *(undefined2 *)param_1 = uStack_1a;
        *(uint *)((int)param_1 + 2) = CONCAT22(local_18[1],local_18[0]);
        *(uint *)((int)param_1 + 6) = CONCAT22(local_18[3],local_18[2]);
        *(ushort *)((int)param_1 + 10) = local_38 | uVar3 & 0x8000;
      }
      else {
        param_1[2] = (-(uint)((uVar3 & 0x8000) != 0) & 0x80000000) + 0x7fff8000;
        param_1[1] = 0;
        *param_1 = 0;
      }
    }
  }
  else {
    param_1[2] = (-(uint)((uVar3 & 0x8000) != 0) & 0x80000000) + 0x7fff8000;
    param_1[1] = 0;
    *param_1 = 0;
  }
  return;
}
```

---

## FUN_00489ac0 — 0x489ac0

- Classification : internal
- Corps : `0x489ac0–0x489b82`
- État : pseudocode obtenu
- Evidence : `ev_8d49f3e44e0daa7619ee8d7e38157dc24354e5c889e2d105c04f46cdaffee1b9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x489670` — `FUN_00489670`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00489ac0(undefined2 *param_1,uint param_2,int param_3)

{
  uint uVar1;
  ushort local_18;
  undefined4 uStack_16;
  undefined2 uStack_12;
  undefined4 local_10;
  ushort *local_c;
  undefined *local_8;
  
  local_8 = &DAT_004a90c0;
  if (param_2 != 0) {
    if ((int)param_2 < 0) {
      param_2 = -param_2;
      local_8 = &DAT_004a9220;
    }
    uStack_16 = CONCAT22(uStack_16._2_2_,(undefined2)uStack_16);
    if (param_3 == 0) {
      *param_1 = 0;
      uStack_16 = CONCAT22(uStack_16._2_2_,(undefined2)uStack_16);
    }
    while (param_2 != 0) {
      local_8 = local_8 + 0x54;
      uVar1 = param_2 & 7;
      param_2 = (int)param_2 >> 3;
      if (uVar1 != 0) {
        local_c = (ushort *)(local_8 + uVar1 * 0xc);
        if (0x7fff < *local_c) {
          local_18 = (ushort)*(undefined4 *)local_c;
          uStack_16._0_2_ = (undefined2)((uint)*(undefined4 *)local_c >> 0x10);
          uStack_16._2_2_ = (undefined2)*(undefined4 *)(local_c + 2);
          uStack_12 = (undefined2)((uint)*(undefined4 *)(local_c + 2) >> 0x10);
          local_10 = *(undefined4 *)(local_c + 4);
          uStack_16 = CONCAT22(uStack_16._2_2_,(undefined2)uStack_16) + -1;
          local_c = &local_18;
        }
        FUN_00489670(param_1,local_c);
      }
    }
  }
  return;
}
```

---

## FUN_00489b90 — 0x489b90

- Classification : internal
- Corps : `0x489b90–0x489e4b`
- État : pseudocode obtenu
- Evidence : `ev_313dca62299d9780e63c6a6a805003c34ba63c32862aecb1a89e4e86105fad76`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x486cc0` — `FUN_00486cc0`
- `0x486db0` — `FUN_00486db0`
- `0x486e30` — `FUN_00486e30`
- `0x486f90` — `__copysign`
- `0x488970` — `FUN_00488970`
- `0x488aa0` — `FUN_00488aa0`
- `0x4895b0` — `FUN_004895b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_00489b90(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  float10 fVar2;
  double dVar3;
  undefined4 uVar4;
  int local_38;
  int local_18;
  int local_14;
  undefined4 local_10;
  double local_c;
  
  local_10 = FUN_004895b0();
  if ((param_2._2_2_ & 0x7ff0) == 0x7ff0) {
    iVar1 = FUN_00486db0();
    if (0 < iVar1) {
      if (iVar1 < 3) {
        FUN_004895b0();
        return (float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
      }
      if (iVar1 == 3) {
        fVar2 = (float10)FUN_00488970(0x19,param_1,param_2,(double)param_3,local_10);
        return fVar2;
      }
    }
    fVar2 = (float10)FUN_00488aa0(8,0x19,param_1,param_2,(double)param_3,
                                  (double)CONCAT26(param_2._2_2_,
                                                   CONCAT24((undefined2)param_2,param_1)) + 1.0,
                                  local_10);
    return fVar2;
  }
  if ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) == 0.0) {
    FUN_004895b0();
    return (float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
  }
  fVar2 = (float10)FUN_00486e30(param_1,param_2,&local_14);
  dVar3 = (double)fVar2;
  if (param_3 < 0) {
    local_38 = -param_3;
  }
  else {
    local_38 = param_3;
  }
  if (local_38 <= 0x7fffffff) {
    local_18 = local_14 + param_3;
  }
  else {
    local_18 = param_3;
  }
  if (0xa00 < local_18) {
    uVar4 = local_10;
    dVar3 = __copysign((double)CONCAT44(DAT_004a8ed4,DAT_004a8ed0),dVar3);
    fVar2 = (float10)FUN_00488aa0(0x11,0x19,param_1,param_2,(double)param_3,dVar3,uVar4);
    return fVar2;
  }
  if (0x400 < local_18) {
    fVar2 = (float10)FUN_00486cc0(dVar3,local_18 + -0x600);
    local_c = (double)fVar2;
    fVar2 = (float10)FUN_00488aa0(0x11,0x19,param_1,param_2,(double)param_3,local_c,local_10);
    return fVar2;
  }
  if (local_18 < -0x9fd) {
    fVar2 = (float10)FUN_00488aa0(0x12,0x19,param_1,param_2,(double)param_3,dVar3 * 0.0,local_10);
    return fVar2;
  }
  if (local_18 < -0x3fd) {
    fVar2 = (float10)FUN_00486cc0(dVar3,local_18 + 0x600);
    local_c = (double)fVar2;
    fVar2 = (float10)FUN_00488aa0(0x12,0x19,param_1,param_2,(double)param_3,local_c,local_10);
    return fVar2;
  }
  fVar2 = (float10)FUN_00486cc0(dVar3,local_18);
  local_c = (double)fVar2;
  FUN_004895b0();
  return (float10)local_c;
}
```

---

## FUN_00489e50 — 0x489e50

- Classification : internal
- Corps : `0x489e50–0x48a12f`
- État : pseudocode obtenu
- Evidence : `ev_27f8175bcf7fe65c7852d0f82bf4b952f5ab7e4e6efba6a331bdb4b1dda77eec`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x489e9d with no resolved callee; its no-return basis is unknown.

### Appels directs

- `EXTERNAL:0x7` — `KERNEL32.DLL::WideCharToMultiByte`
- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `0x47a120` — `FUN_0047a120`
- `0x488010` — `FUN_00488010`
- `0x48a130` — `FUN_0048a130`

### Chaînes référencées

- `0x4963e8` — "wcstombs.c"
- `0x4963f4` — "pwcs != NULL"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_00489e50(LPSTR param_1,LPCWSTR param_2,uint param_3)

{
  WCHAR WVar1;
  code *pcVar2;
  int iVar3;
  uint uVar4;
  DWORD DVar5;
  BOOL local_18;
  int local_14;
  CHAR local_10 [4];
  int local_c;
  uint local_8;
  
  local_8 = 0;
  local_18 = 0;
  if ((param_1 == (LPSTR)0x0) || (param_3 != 0)) {
    if ((param_2 == (LPCWSTR)0x0) &&
       (iVar3 = FUN_0047a120(2,"wcstombs.c",0x7e,0,"pwcs != NULL"), iVar3 == 1)) {
      pcVar2 = (code *)swi(3);
      uVar4 = (*pcVar2)();
      return uVar4;
    }
    if (param_1 == (LPSTR)0x0) {
      if (DAT_006325e8 == 0) {
        local_8 = FUN_00488010(param_2);
      }
      else {
        iVar3 = WideCharToMultiByte(DAT_006325f8,0x220,param_2,-1,(LPSTR)0x0,0,(LPCSTR)0x0,&local_18
                                   );
        if ((iVar3 == 0) || (local_18 != 0)) {
          _DAT_0063251c = 0x2a;
          local_8 = 0xffffffff;
        }
        else {
          local_8 = iVar3 - 1;
        }
      }
    }
    else if (DAT_006325e8 == 0) {
      for (; local_8 < param_3; local_8 = local_8 + 1) {
        if (0xff < (ushort)*param_2) {
          _DAT_0063251c = 0x2a;
          return 0xffffffff;
        }
        param_1[local_8] = (CHAR)*param_2;
        WVar1 = *param_2;
        param_2 = param_2 + 1;
        if (WVar1 == L'\0') {
          return local_8;
        }
      }
    }
    else if (DAT_004a87f4 == 1) {
      if (param_3 != 0) {
        param_3 = FUN_0048a130(param_2,param_3);
      }
      local_8 = WideCharToMultiByte(DAT_006325f8,0x220,param_2,param_3,param_1,param_3,(LPCSTR)0x0,
                                    &local_18);
      if ((local_8 == 0) || (local_18 != 0)) {
        _DAT_0063251c = 0x2a;
        local_8 = 0xffffffff;
      }
      else if (param_1[local_8 - 1] == '\0') {
        local_8 = local_8 - 1;
      }
    }
    else {
      local_8 = WideCharToMultiByte(DAT_006325f8,0x220,param_2,-1,param_1,param_3,(LPCSTR)0x0,
                                    &local_18);
      if ((local_8 == 0) || (local_18 != 0)) {
        if ((local_18 == 0) && (DVar5 = GetLastError(), DVar5 == 0x7a)) {
          while (local_8 < param_3) {
            local_14 = WideCharToMultiByte(DAT_006325f8,0,param_2,1,local_10,DAT_004a87f4,
                                           (LPCSTR)0x0,&local_18);
            if ((local_14 == 0) || (local_18 != 0)) {
              _DAT_0063251c = 0x2a;
              return 0xffffffff;
            }
            if (param_3 < local_8 + local_14) {
              return local_8;
            }
            for (local_c = 0; local_c < local_14; local_c = local_c + 1) {
              param_1[local_8] = local_10[local_c];
              if (param_1[local_8] == '\0') {
                return local_8;
              }
              local_8 = local_8 + 1;
            }
            param_2 = param_2 + 1;
          }
        }
        else {
          _DAT_0063251c = 0x2a;
          local_8 = 0xffffffff;
        }
      }
      else {
        local_8 = local_8 - 1;
      }
    }
  }
  else {
    local_8 = 0;
  }
  return local_8;
}
```

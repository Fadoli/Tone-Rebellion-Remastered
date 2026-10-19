# 0022_batch_0018 — détails (2/2)

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

# 0020_batch_0016 — détails (2/6)

## FUN_00479170 — 0x479170

- Classification : internal
- Corps : `0x479170–0x479d8c`
- État : pseudocode obtenu
- Evidence : `ev_f3ba25d83ba3fbe9a6825047058555b299a82e125fba888a5de4a8e02dc65381`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x4792a6 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x472e90` — `_strlen`
- `0x479ea0` — `FUN_00479ea0`
- `0x479f20` — `FUN_00479f20`
- `0x479f60` — `FUN_00479f60`
- `0x479fb0` — `FUN_00479fb0`
- `0x479fd0` — `FUN_00479fd0`
- `0x479ff0` — `FUN_00479ff0`
- `0x47a120` — `FUN_0047a120`
- `0x483550` — `__fptrap`
- `0x4837b0` — `FUN_004837b0`
- `0x483850` — `__aulldiv`
- `0x4838c0` — `__aullrem`

### Chaînes référencées

- `0x495a30` — "(\"inconsistent IOB fields\", stream->_ptr - stream->_base >= 0)"
- `0x495ae0` — "ull)"
- `0x495af4` — "output.c"
- `0x495b00` — "ch != _T('\\0')"

### Pseudocode Ghidra

```c
/* WARNING: Type propagation algorithm not settling */

int FUN_00479170(undefined4 param_1,byte *param_2,undefined4 *param_3)

{
  byte bVar1;
  code *pcVar2;
  ulonglong uVar3;
  byte *pbVar4;
  short sVar5;
  byte *pbVar6;
  uint uVar7;
  size_t sVar8;
  int iVar9;
  undefined2 extraout_var;
  short *psVar10;
  bool bVar11;
  ulonglong uVar12;
  longlong lVar13;
  int local_2a8;
  uint local_294;
  undefined1 local_28c [4];
  size_t local_288;
  short *local_284;
  int local_280;
  undefined8 local_27c;
  int local_274;
  undefined8 local_270;
  undefined4 local_268;
  undefined4 local_264;
  int *local_260;
  int local_25c;
  short *local_258;
  short *local_254;
  short *local_250;
  undefined2 local_24c;
  int local_248;
  undefined1 local_244;
  char local_243;
  int local_240;
  int local_23c;
  int local_238;
  int local_234;
  int local_230;
  short local_22c [255];
  undefined2 uStack_2d;
  undefined3 uStack_2b;
  size_t local_28;
  short *local_24;
  int local_20;
  int local_1c;
  undefined2 local_18;
  int local_14;
  uint local_10;
  undefined4 local_c;
  uint local_8;
  
  local_28 = 0;
  local_230 = 0;
  local_1c = 0;
  pbVar6 = param_2;
  do {
    param_2 = pbVar6;
    bVar1 = *param_2;
    stack0xffffffd4 = CONCAT31(uStack_2b,bVar1);
    pbVar6 = param_2 + 1;
    if ((bVar1 == 0) || (local_230 < 0)) {
      return local_230;
    }
    if (((char)bVar1 < ' ') || ('x' < (char)bVar1)) {
      local_294 = 0;
    }
    else {
      local_294 = (int)"(\"inconsistent IOB fields\", stream->_ptr - stream->_base >= 0)"
                       [(char)bVar1 + 0x30] & 0xf;
    }
    local_10 = local_294;
    local_1c = (int)(char)(&DAT_00495a80)[local_294 * 8 + local_1c] >> 4;
    switch(local_1c) {
    case 0:
switchD_00479229_caseD_0:
      local_20 = 0;
      pbVar4 = pbVar6;
      if ((*(ushort *)(PTR_DAT_004a85e8 + (uint)bVar1 * 2) & 0x8000) != 0) {
        FUN_00479ea0((int)(char)bVar1,param_1,&local_230);
        stack0xffffffd4 = CONCAT31(uStack_2b,*pbVar6);
        pbVar4 = param_2 + 2;
        if (*pbVar6 == 0) {
          iVar9 = FUN_0047a120(2,"output.c",0x186,0,"ch != _T(\'\\0\')");
          if (iVar9 == 1) {
            pcVar2 = (code *)swi(3);
            iVar9 = (*pcVar2)();
            return iVar9;
          }
        }
      }
      param_2 = pbVar4;
      FUN_00479ea0((int)uStack_2d._1_1_,param_1,&local_230);
      pbVar6 = param_2;
      break;
    case 1:
      local_c = 0;
      local_240 = 0;
      local_248 = 0;
      local_14 = 0;
      local_8 = 0;
      local_238 = -1;
      local_20 = 0;
      break;
    case 2:
      switch(bVar1) {
      case 0x20:
        local_8 = local_8 | 2;
        break;
      case 0x23:
        local_8 = local_8 | 0x80;
        break;
      case 0x2b:
        local_8 = local_8 | 1;
        break;
      case 0x2d:
        local_8 = local_8 | 4;
        break;
      case 0x30:
        local_8 = local_8 | 8;
      }
      break;
    case 3:
      if (bVar1 == 0x2a) {
        local_248 = FUN_00479fb0(&param_3);
        if (local_248 < 0) {
          local_8 = local_8 | 4;
          local_248 = -local_248;
        }
      }
      else {
        local_248 = local_248 * 10 + -0x30 + (int)(char)bVar1;
      }
      break;
    case 4:
      local_238 = 0;
      break;
    case 5:
      if (bVar1 == 0x2a) {
        local_238 = FUN_00479fb0(&param_3);
        if (local_238 < 0) {
          local_238 = -1;
        }
      }
      else {
        local_238 = local_238 * 10 + -0x30 + (int)(char)bVar1;
      }
      break;
    case 6:
      switch(bVar1) {
      case 0x49:
        if ((*pbVar6 != 0x36) || (param_2[2] != 0x34)) {
          local_1c = 0;
          goto switchD_00479229_caseD_0;
        }
        local_8 = local_8 | 0x8000;
        pbVar6 = param_2 + 3;
        break;
      case 0x68:
        local_8 = local_8 | 0x20;
        break;
      case 0x6c:
        local_8 = local_8 | 0x10;
        break;
      case 0x77:
        local_8 = local_8 | 0x800;
      }
      param_2 = pbVar6;
      pbVar6 = param_2;
      break;
    case 7:
      psVar10 = local_24;
      switch(bVar1) {
      case 0x43:
        if ((local_8 & 0x830) == 0) {
          local_8 = local_8 | 0x800;
        }
      case 99:
        if ((local_8 & 0x810) == 0) {
          local_24c = FUN_00479fb0(&param_3);
          local_22c[0]._0_1_ = (undefined1)local_24c;
          local_28 = 1;
        }
        else {
          local_18 = FUN_00479ff0(&param_3);
          local_28 = FUN_004837b0(local_22c,CONCAT22(extraout_var,local_18));
          if ((int)local_28 < 0) {
            local_240 = 1;
          }
        }
        psVar10 = local_22c;
        break;
      case 0x45:
      case 0x47:
        local_c = 1;
        stack0xffffffd4 = CONCAT31(uStack_2b,bVar1 + 0x20);
      case 0x65:
      case 0x66:
      case 0x67:
        local_8 = local_8 | 0x40;
        local_24 = local_22c;
        if (local_238 < 0) {
          local_238 = 6;
        }
        else if ((local_238 == 0) && (uStack_2d._1_1_ == 'g')) {
          local_238 = 1;
        }
        local_268 = *param_3;
        local_264 = param_3[1];
        param_3 = param_3 + 2;
        (*(code *)PTR___fptrap_004a63d8)(&local_268,local_24,(int)uStack_2d._1_1_,local_238,local_c)
        ;
        if (((local_8 & 0x80) != 0) && (local_238 == 0)) {
          (*(code *)PTR___fptrap_004a63e4)(local_24);
        }
        if ((uStack_2d._1_1_ == 'g') && ((local_8 & 0x80) == 0)) {
          (*(code *)PTR___fptrap_004a63dc)(local_24);
        }
        if ((char)*local_24 == '-') {
          local_8 = local_8 | 0x100;
          local_24 = (short *)((int)local_24 + 1);
        }
        local_28 = _strlen((char *)local_24);
        psVar10 = local_24;
        break;
      case 0x53:
        if ((local_8 & 0x830) == 0) {
          local_8 = local_8 | 0x800;
        }
      case 0x73:
        if (local_238 == -1) {
          local_2a8 = 0x7fffffff;
        }
        else {
          local_2a8 = local_238;
        }
        local_25c = local_2a8;
        local_24 = (short *)FUN_00479fb0(&param_3);
        if ((local_8 & 0x810) == 0) {
          if (local_24 == (short *)0x0) {
            local_24 = (short *)PTR_DAT_004a63f0;
          }
          for (local_254 = local_24; (local_25c != 0 && ((char)*local_254 != '\0'));
              local_254 = (short *)((int)local_254 + 1)) {
            local_25c = local_25c + -1;
          }
          local_28 = (int)local_254 - (int)local_24;
          local_25c = local_25c + -1;
          psVar10 = local_24;
        }
        else {
          if (local_24 == (short *)0x0) {
            local_24 = (short *)PTR_DAT_004a63f4;
          }
          local_20 = 1;
          for (local_258 = local_24; (local_25c != 0 && (*local_258 != 0));
              local_258 = local_258 + 1) {
            local_25c = local_25c + -1;
          }
          local_28 = (int)local_258 - (int)local_24 >> 1;
          local_25c = local_25c + -1;
          psVar10 = local_24;
        }
        break;
      case 0x5a:
        local_250 = (short *)FUN_00479fb0(&param_3);
        if ((local_250 == (short *)0x0) || (*(int *)(local_250 + 2) == 0)) {
          local_24 = (short *)PTR_DAT_004a63f0;
          local_28 = _strlen(PTR_DAT_004a63f0);
          psVar10 = local_24;
        }
        else if ((local_8 & 0x800) == 0) {
          local_20 = 0;
          local_28 = (size_t)*local_250;
          psVar10 = *(short **)(local_250 + 2);
        }
        else {
          local_28 = (uint)(int)*local_250 >> 1;
          local_20 = 1;
          psVar10 = *(short **)(local_250 + 2);
        }
        break;
      case 100:
      case 0x69:
        local_8 = local_8 | 0x40;
        local_23c = 10;
        goto LAB_00479935;
      case 0x6e:
        local_260 = (int *)FUN_00479fb0(&param_3);
        if ((local_8 & 0x20) == 0) {
          *local_260 = local_230;
        }
        else {
          *(undefined2 *)local_260 = (undefined2)local_230;
        }
        local_240 = 1;
        psVar10 = local_24;
        break;
      case 0x6f:
        local_23c = 8;
        if ((local_8 & 0x80) != 0) {
          local_8 = local_8 | 0x200;
        }
        goto LAB_00479935;
      case 0x70:
        local_238 = 8;
      case 0x58:
        local_234 = 7;
        goto LAB_004798df;
      case 0x75:
        local_23c = 10;
        goto LAB_00479935;
      case 0x78:
        local_234 = 0x27;
LAB_004798df:
        local_23c = 0x10;
        if ((local_8 & 0x80) != 0) {
          local_244 = 0x30;
          local_243 = (char)local_234 + 'Q';
          local_14 = 2;
        }
LAB_00479935:
        if ((local_8 & 0x8000) == 0) {
          if ((local_8 & 0x20) == 0) {
            if ((local_8 & 0x40) == 0) {
              uVar7 = FUN_00479fb0(&param_3);
              uVar12 = (ulonglong)uVar7;
            }
            else {
              iVar9 = FUN_00479fb0(&param_3);
              uVar12 = (ulonglong)iVar9;
            }
          }
          else if ((local_8 & 0x40) == 0) {
            uVar7 = FUN_00479fb0(&param_3);
            uVar12 = (ulonglong)(uVar7 & 0xffff);
          }
          else {
            sVar5 = FUN_00479fb0(&param_3);
            uVar12 = (ulonglong)(int)sVar5;
          }
        }
        else {
          uVar12 = FUN_00479fd0(&param_3);
        }
        local_27c._4_4_ = (int)(uVar12 >> 0x20);
        local_27c._0_4_ = (int)uVar12;
        uVar3 = uVar12;
        if ((((local_8 & 0x40) != 0) && ((longlong)uVar12 < 0x100000000)) && ((longlong)uVar12 < 0))
        {
          local_8 = local_8 | 0x100;
          uVar3 = CONCAT44(-(local_27c._4_4_ + (uint)((int)local_27c != 0)),-(int)local_27c);
        }
        local_270._4_4_ = (int)(uVar3 >> 0x20);
        local_270._0_4_ = (int)uVar3;
        if ((local_8 & 0x8000) == 0) {
          local_270._4_4_ = 0;
        }
        lVar13 = CONCAT44(local_270._4_4_,(int)local_270);
        if (local_238 < 0) {
          local_238 = 1;
        }
        else {
          local_8 = local_8 & 0xfffffff7;
        }
        if ((int)local_270 == 0 && local_270._4_4_ == 0) {
          local_14 = 0;
        }
        local_24 = &uStack_2d;
        local_27c = uVar12;
        while ((iVar9 = local_238 + -1, 0 < local_238 || (lVar13 != 0))) {
          local_238 = iVar9;
          local_270 = lVar13;
          local_274 = __aullrem(lVar13,local_23c,local_23c >> 0x1f);
          local_274 = local_274 + 0x30;
          lVar13 = __aulldiv(local_270,local_23c,local_23c >> 0x1f);
          if (0x39 < local_274) {
            local_274 = local_274 + local_234;
          }
          *(char *)local_24 = (char)local_274;
          local_24 = (short *)((int)local_24 + -1);
        }
        local_28 = (int)&uStack_2d - (int)local_24;
        psVar10 = (short *)((int)local_24 + 1);
        local_270 = 0;
        local_238 = iVar9;
        if (((local_8 & 0x200) != 0) && ((*(char *)psVar10 != '0' || (local_28 == 0)))) {
          *(char *)local_24 = '0';
          local_28 = local_28 + 1;
          psVar10 = local_24;
        }
      }
      local_24 = psVar10;
      if (local_240 == 0) {
        if ((local_8 & 0x40) != 0) {
          if ((local_8 & 0x100) == 0) {
            if ((local_8 & 1) == 0) {
              if ((local_8 & 2) != 0) {
                local_244 = 0x20;
                local_14 = 1;
              }
            }
            else {
              local_244 = 0x2b;
              local_14 = 1;
            }
          }
          else {
            local_244 = 0x2d;
            local_14 = 1;
          }
        }
        local_280 = (local_248 - local_28) - local_14;
        if ((local_8 & 0xc) == 0) {
          FUN_00479f20(0x20,local_280,param_1,&local_230);
        }
        FUN_00479f60(&local_244,local_14,param_1,&local_230);
        if (((local_8 & 8) != 0) && ((local_8 & 4) == 0)) {
          FUN_00479f20(0x30,local_280,param_1,&local_230);
        }
        if ((local_20 == 0) || ((int)local_28 < 1)) {
          FUN_00479f60(local_24,local_28,param_1,&local_230);
        }
        else {
          local_284 = local_24;
          local_288 = local_28;
          while (sVar8 = local_288 - 1, bVar11 = local_288 != 0, local_288 = sVar8, bVar11) {
            sVar5 = *local_284;
            local_284 = local_284 + 1;
            iVar9 = FUN_004837b0(local_28c,CONCAT22((short)(sVar8 >> 0x10),sVar5));
            if (iVar9 < 1) break;
            FUN_00479f60(local_28c,iVar9,param_1,&local_230);
          }
        }
        if ((local_8 & 4) != 0) {
          FUN_00479f20(0x20,local_280,param_1,&local_230);
        }
      }
    }
  } while( true );
}
```

---

## FUN_00479ea0 — 0x479ea0

- Classification : internal
- Corps : `0x479ea0–0x479f16`
- État : pseudocode obtenu
- Evidence : `ev_c944ed7f0374b51b6531ca7c6c84c070d65051d4d4504266a398b5f8578c2473`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x478ef0` — `FUN_00478ef0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00479ea0(uint param_1,int *param_2,int *param_3)

{
  uint local_8;
  
  param_2[1] = param_2[1] + -1;
  if (param_2[1] < 0) {
    local_8 = FUN_00478ef0(param_1,param_2);
  }
  else {
    *(undefined1 *)*param_2 = (undefined1)param_1;
    local_8 = param_1 & 0xff;
    *param_2 = *param_2 + 1;
  }
  if (local_8 == 0xffffffff) {
    *param_3 = -1;
  }
  else {
    *param_3 = *param_3 + 1;
  }
  return;
}
```

---

## FUN_00479f20 — 0x479f20

- Classification : internal
- Corps : `0x479f20–0x479f54`
- État : pseudocode obtenu
- Evidence : `ev_32953d2a2699f6ec4d13eec237747829845c10e4046f3735e16af42c7bad9fd1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x479ea0` — `FUN_00479ea0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00479f20(undefined4 param_1,int param_2,undefined4 param_3,int *param_4)

{
  do {
    if (param_2 < 1) {
      return;
    }
    FUN_00479ea0(param_1,param_3,param_4);
    param_2 = param_2 + -1;
  } while (*param_4 != -1);
  return;
}
```

---

## FUN_00479f60 — 0x479f60

- Classification : internal
- Corps : `0x479f60–0x479fa9`
- État : pseudocode obtenu
- Evidence : `ev_5390617fff12a4eafa2f686af2c2794a7f9871efbcbf4e63014a2d15263b0006`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x479ea0` — `FUN_00479ea0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00479f60(char *param_1,int param_2,undefined4 param_3,int *param_4)

{
  char cVar1;
  
  do {
    if (param_2 < 1) {
      return;
    }
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    FUN_00479ea0((int)cVar1,param_3,param_4);
    param_2 = param_2 + -1;
  } while (*param_4 != -1);
  return;
}
```

---

## FUN_00479fb0 — 0x479fb0

- Classification : internal
- Corps : `0x479fb0–0x479fc9`
- État : pseudocode obtenu
- Evidence : `ev_9a9b6b23560c3a05e07f0e3b5ba501eca62c76762f07ec2088ce44c870d8a828`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00479fb0(int *param_1)

{
  *param_1 = *param_1 + 4;
  return *(undefined4 *)(*param_1 + -4);
}
```

---

## FUN_00479fd0 — 0x479fd0

- Classification : internal
- Corps : `0x479fd0–0x479fee`
- État : pseudocode obtenu
- Evidence : `ev_9548d47b7057b486d40e12572030ee81ab078a1fa5a95b0dd0f72b48ed0a4808`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined8 FUN_00479fd0(int *param_1)

{
  *param_1 = *param_1 + 8;
  return *(undefined8 *)(*param_1 + -8);
}
```

---

## FUN_00479ff0 — 0x479ff0

- Classification : internal
- Corps : `0x479ff0–0x47a00a`
- État : pseudocode obtenu
- Evidence : `ev_ccacfaed8480adf27b2a9c4b512ba749e41fabf616fe8c8d7961ea0bc7566dd4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined2 FUN_00479ff0(int *param_1)

{
  *param_1 = *param_1 + 4;
  return *(undefined2 *)(*param_1 + -4);
}
```

---

## FUN_0047a010 — 0x47a010

- Classification : internal
- Corps : `0x47a010–0x47a01a`
- État : pseudocode obtenu
- Evidence : `ev_c7b17768fbc008da001606feedba2545588265add1dffbea588c958e619c7079`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x4c` — `KERNEL32.DLL::DebugBreak`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047a010(void)

{
  DebugBreak();
  return;
}
```

---

## FUN_0047a020 — 0x47a020

- Classification : internal
- Corps : `0x47a020–0x47a076`
- État : pseudocode obtenu
- Evidence : `ev_335a03427318fe9eb6c177dfb445614390db7f60a3f7f7de5b4ad984c112698f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047a020(int param_1,uint param_2)

{
  undefined4 uVar1;
  
  if ((param_1 < 0) || (2 < param_1)) {
    uVar1 = 0xffffffff;
  }
  else if (param_2 == 0xffffffff) {
    uVar1 = *(undefined4 *)(&DAT_004a6400 + param_1 * 4);
  }
  else if ((param_2 & 0xfffffff8) == 0) {
    uVar1 = *(undefined4 *)(&DAT_004a6400 + param_1 * 4);
    *(uint *)(&DAT_004a6400 + param_1 * 4) = param_2;
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}
```

---

## __CrtSetReportFile — 0x47a080

- Classification : internal
- Corps : `0x47a080–0x47a0fd`
- État : pseudocode obtenu
- Evidence : `ev_1e6e63dc590a4e6ec7b8c203d4639d075365258bb584132bdb49ffa0a451662e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xa` — `KERNEL32.DLL::GetStdHandle`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __CrtSetReportFile
   
   Library: Visual Studio 2003 Debug */

undefined4 __CrtSetReportFile(int param_1,int param_2)

{
  undefined4 uVar1;
  HANDLE pvVar2;
  
  if ((param_1 < 0) || (2 < param_1)) {
    uVar1 = 0xfffffffe;
  }
  else if (param_2 == -6) {
    uVar1 = *(undefined4 *)(&DAT_004a6410 + param_1 * 4);
  }
  else {
    uVar1 = *(undefined4 *)(&DAT_004a6410 + param_1 * 4);
    if (param_2 == -4) {
      pvVar2 = GetStdHandle(0xfffffff5);
      *(HANDLE *)(&DAT_004a6410 + param_1 * 4) = pvVar2;
    }
    else if (param_2 == -5) {
      pvVar2 = GetStdHandle(0xfffffff4);
      *(HANDLE *)(&DAT_004a6410 + param_1 * 4) = pvVar2;
    }
    else {
      *(int *)(&DAT_004a6410 + param_1 * 4) = param_2;
    }
  }
  return uVar1;
}
```

---

## FUN_0047a100 — 0x47a100

- Classification : internal
- Corps : `0x47a100–0x47a11b`
- État : pseudocode obtenu
- Evidence : `ev_61199866d9cb3baef38bb9f84194085e3aa6e12e242fed4bb742b9c876f96523`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047a100(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_00633e60;
  DAT_00633e60 = param_1;
  return uVar1;
}
```

---

## FUN_0047a120 — 0x47a120

- Classification : internal
- Corps : `0x47a120–0x47a4af`
- État : pseudocode obtenu
- Evidence : `ev_ce89ffd481495a12038f69d71ca415522524a9a4e41283f39b4263d78b9c8ff5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x3b` — `KERNEL32.DLL::WriteFile`
- `EXTERNAL:0x47` — `KERNEL32.DLL::LoadLibraryA`
- `EXTERNAL:0x48` — `KERNEL32.DLL::InterlockedIncrement`
- `EXTERNAL:0x4b` — `KERNEL32.DLL::GetProcAddress`
- `EXTERNAL:0x4d` — `KERNEL32.DLL::InterlockedDecrement`
- `EXTERNAL:0x4e` — `KERNEL32.DLL::OutputDebugStringA`
- `0x472da0` — `FUN_00472da0`
- `0x472db0` — `FUN_00472db0`
- `0x472e90` — `_strlen`
- `0x478410` — `FUN_00478410`
- `0x47a010` — `FUN_0047a010`
- `0x47a4b0` — `FUN_0047a4b0`
- `0x483940` — `__itoa`
- `0x483c10` — `FUN_00483c10`
- `0x483d10` — `FUN_00483d10`

### Chaînes référencées

- `0x495b34` — "%s(%d) : %s"
- `0x495b48` — "Assertion failed!"
- `0x495b48` — "Assertion failed!"
- `0x495b5c` — "Assertion failed: "
- `0x495b5c` — "Assertion failed: "
- `0x495b70` — "_CrtDbgReport: String too long or IO Error"
- `0x495b70` — "_CrtDbgReport: String too long or IO Error"
- `0x495b9c` — "Second Chance Assertion Failed: File %s, Line %d\n"
- `0x495bd0` — "wsprintfA"
- `0x495bdc` — "user32.dll"

### Pseudocode Ghidra

```c
undefined4 FUN_0047a120(int param_1,int param_2,int param_3,undefined4 param_4,int param_5)

{
  LONG LVar1;
  size_t nNumberOfBytesToWrite;
  int iVar2;
  undefined4 *puVar3;
  char local_3028 [20];
  DWORD local_3014;
  HMODULE local_3010;
  undefined1 local_300c;
  undefined4 local_300b;
  CHAR local_200c;
  undefined4 local_200b;
  undefined4 local_100c;
  undefined1 *local_1008;
  undefined1 local_1004;
  undefined4 local_1003;
  undefined4 uStackY_24;
  CHAR *pCStackY_20;
  DWORD *lpNumberOfBytesWritten;
  LPOVERLAPPED lpOverlapped;
  
  FUN_00478410();
  local_300c = 0;
  puVar3 = &local_300b;
  for (iVar2 = 0x3ff; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = 0;
  *(undefined1 *)((int)puVar3 + 2) = 0;
  local_200c = '\0';
  puVar3 = &local_200b;
  for (iVar2 = 0x3ff; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = 0;
  *(undefined1 *)((int)puVar3 + 2) = 0;
  local_1004 = 0;
  puVar3 = &local_1003;
  for (iVar2 = 0x3ff; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = 0;
  *(undefined1 *)((int)puVar3 + 2) = 0;
  local_1008 = &stack0x00000018;
  if ((param_1 < 0) || (2 < param_1)) {
    local_100c = 0xffffffff;
  }
  else if ((param_1 == 2) && (LVar1 = InterlockedIncrement((LONG *)&DAT_004a63f8), 0 < LVar1)) {
    if ((DAT_0063258c == (FARPROC)0x0) &&
       ((local_3010 = LoadLibraryA("user32.dll"), local_3010 == (HMODULE)0x0 ||
        (DAT_0063258c = GetProcAddress(local_3010,"wsprintfA"), DAT_0063258c == (FARPROC)0x0)))) {
      local_100c = 0xffffffff;
    }
    else {
      (*DAT_0063258c)();
      OutputDebugStringA(&local_200c);
      InterlockedDecrement((LONG *)&DAT_004a63f8);
      FUN_0047a010();
      local_100c = 0xffffffff;
    }
  }
  else {
    if ((param_5 != 0) && (iVar2 = FUN_00483d10(), iVar2 < 0)) {
      FUN_00472da0();
    }
    if (param_1 == 2) {
      FUN_00472da0();
    }
    FUN_00472db0();
    if (param_1 == 2) {
      if ((uRam004a6408 & 1) != 0) {
        FUN_00472db0();
      }
      FUN_00472db0();
    }
    if (param_2 == 0) {
      FUN_00472da0();
    }
    else {
      pCStackY_20 = &local_200c;
      uStackY_24 = 0x47a335;
      iVar2 = FUN_00483c10();
      if (iVar2 < 0) {
        FUN_00472da0();
      }
    }
    if ((DAT_00633e60 == (code *)0x0) || (iVar2 = (*DAT_00633e60)(), iVar2 == 0)) {
      if (((*(uint *)(&DAT_004a6400 + param_1 * 4) & 1) != 0) &&
         (*(int *)(&DAT_004a6410 + param_1 * 4) != -1)) {
        lpOverlapped = (LPOVERLAPPED)0x0;
        lpNumberOfBytesWritten = &local_3014;
        nNumberOfBytesToWrite = _strlen(&local_200c);
        pCStackY_20 = (CHAR *)0x47a3fb;
        WriteFile(*(HANDLE *)(&DAT_004a6410 + param_1 * 4),&local_200c,nNumberOfBytesToWrite,
                  lpNumberOfBytesWritten,lpOverlapped);
      }
      if ((*(uint *)(&DAT_004a6400 + param_1 * 4) & 2) != 0) {
        OutputDebugStringA(&local_200c);
      }
      if ((*(uint *)(&DAT_004a6400 + param_1 * 4) & 4) == 0) {
        if (param_1 == 2) {
          InterlockedDecrement((LONG *)&DAT_004a63f8);
        }
        local_100c = 0;
      }
      else {
        if (param_3 != 0) {
          __itoa(param_3,local_3028,10);
        }
        pCStackY_20 = (CHAR *)0x47a476;
        local_100c = FUN_0047a4b0();
        if (param_1 == 2) {
          InterlockedDecrement((LONG *)&DAT_004a63f8);
        }
      }
    }
    else if (param_1 == 2) {
      InterlockedDecrement((LONG *)&DAT_004a63f8);
    }
  }
  return local_100c;
}
```

---

## FUN_0047a4b0 — 0x47a4b0

- Classification : internal
- Corps : `0x47a4b0–0x47a7a5`, `0x47a7a9–0x47a7be`
- État : pseudocode obtenu
- Evidence : `ev_131d3a234b1f6b518352821c8f242a5506996099a922fe69f1d01a989f744340`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x47a7a1 to 0x476ec0 __exit (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `EXTERNAL:0x3d` — `KERNEL32.DLL::GetModuleFileNameA`
- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`
- `0x4737e0` — `_strncpy`
- `0x476ec0` — `__exit`
- `0x478410` — `FUN_00478410`
- `0x47a010` — `FUN_0047a010`
- `0x47a120` — `FUN_0047a120`
- `0x483c10` — `FUN_00483c10`
- `0x484020` — `FUN_00484020`
- `0x484240` — `FUN_00484240`

### Chaînes référencées

- `0x495b70` — "_CrtDbgReport: String too long or IO Error"
- `0x495be8` — "Microsoft Visual C++ Debug Library"
- `0x495c0c` — "Debug %s!\n\nProgram: %s%s%s%s%s%s%s%s%s%s%s\n\n(Press Retry to debug the application)"
- `0x495c60` — "\nModule: "
- `0x495c60` — "\nModule: "
- `0x495c6c` — "\nFile: "
- `0x495c6c` — "\nFile: "
- `0x495c74` — "\nLine: "
- `0x495c74` — "\nLine: "
- `0x495c80` — "Expression: "
- `0x495c80` — "Expression: "
- `0x495c94` — "\n\nFor information on how your program can cause an assertion\nfailure, see the Visual C++ documentation on asserts."
- `0x495c94` — "\n\nFor information on how your program can cause an assertion\nfailure, see the Visual C++ documentation on asserts."
- `0x495c94` — "\n\nFor information on how your program can cause an assertion\nfailure, see the Visual C++ documentation on asserts."
- `0x495d0c` — "<program name unknown>"
- `0x495d24` — "dbgrpt.c"
- `0x495d30` — "szUserMessage != NULL"

### Pseudocode Ghidra

```c
bool FUN_0047a4b0(int param_1,undefined *param_2,undefined *param_3,char *param_4,char *param_5)

{
  int iVar1;
  DWORD DVar2;
  size_t sVar3;
  char *local_113c;
  char *local_1138;
  char *local_1134;
  undefined *local_1130;
  char *local_112c;
  undefined *local_1128;
  undefined *local_1124;
  char *local_1118;
  char *local_1114;
  undefined1 local_1110 [4096];
  int local_110;
  CHAR local_10c [200];
  undefined4 uStackY_44;
  undefined1 *puStackY_40;
  undefined4 uStackY_3c;
  char *pcStackY_38;
  undefined *puStackY_34;
  char *pcStackY_30;
  char *pcStackY_2c;
  char *pcStackY_28;
  char *pcStackY_24;
  undefined *puStackY_20;
  char *pcStackY_1c;
  undefined *puStackY_18;
  char *pcStackY_14;
  char *_Str;
  
  FUN_00478410();
  if (param_5 == (char *)0x0) {
    pcStackY_14 = "dbgrpt.c";
    puStackY_18 = (undefined *)0x2;
    pcStackY_1c = (char *)0x47a4db;
    iVar1 = FUN_0047a120();
    if (iVar1 == 1) {
      FUN_0047a010();
    }
  }
  pcStackY_14 = (char *)0x47a502;
  DVar2 = GetModuleFileNameA((HMODULE)0x0,local_10c,0x104);
  if (DVar2 == 0) {
    FUN_00472da0();
  }
  _Str = local_10c;
  sVar3 = _strlen(_Str);
  if (0x40 < sVar3) {
    _strlen(_Str);
    pcStackY_14 = (char *)0x47a55a;
    _strncpy((char *)0x3,"...",3);
  }
  local_1114 = param_4;
  if ((param_4 != (char *)0x0) && (sVar3 = _strlen(param_4), 0x40 < sVar3)) {
    sVar3 = _strlen(param_4);
    local_1114 = param_4 + (sVar3 - 0x40);
    pcStackY_14 = (char *)0x47a5b5;
    _strncpy(local_1114,"...",3);
  }
  if (param_1 == 2) {
    local_1118 = 
    "\n\nFor information on how your program can cause an assertion\nfailure, see the Visual C++ documentation on asserts."
    ;
  }
  else {
    local_1118 = "";
  }
  if (*param_5 == '\0') {
    local_1124 = &DAT_00495c90;
  }
  else {
    local_1124 = &DAT_00495c7c;
  }
  if (param_3 == (undefined *)0x0) {
    local_1128 = &DAT_00495c90;
    local_112c = "";
    puStackY_18 = local_1128;
  }
  else {
    local_112c = "\nLine: ";
    puStackY_18 = param_3;
  }
  if (param_2 == (undefined *)0x0) {
    local_1130 = &DAT_00495c90;
    local_1134 = "";
    puStackY_20 = local_1130;
  }
  else {
    local_1134 = "\nFile: ";
    puStackY_20 = param_2;
  }
  if (local_1114 == (char *)0x0) {
    local_1138 = "";
    local_113c = "";
    pcStackY_28 = local_1138;
  }
  else {
    local_113c = "\nModule: ";
    pcStackY_28 = local_1114;
  }
  pcStackY_14 = local_1124;
  pcStackY_1c = local_112c;
  pcStackY_24 = local_1134;
  pcStackY_2c = local_113c;
  pcStackY_30 = local_1118;
  puStackY_34 = (&PTR_s_Warning_004a6420)[param_1];
  pcStackY_38 = 
  "Debug %s!\n\nProgram: %s%s%s%s%s%s%s%s%s%s%s\n\n(Press Retry to debug the application)";
  uStackY_3c = 0x1000;
  puStackY_40 = local_1110;
  uStackY_44 = 0x47a752;
  iVar1 = FUN_00483c10();
  if (iVar1 < 0) {
    FUN_00472da0();
  }
  pcStackY_14 = (char *)0x47a783;
  local_110 = FUN_00484240();
  if (local_110 == 3) {
    FUN_00484020();
                    /* WARNING: Subroutine does not return */
    __exit(3);
  }
  return local_110 == 4;
}
```

---


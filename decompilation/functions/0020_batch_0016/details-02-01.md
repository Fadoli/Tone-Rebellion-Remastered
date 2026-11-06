# 0020_batch_0016 — détails (1/2)

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

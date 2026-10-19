# 0019_batch_0015 — détails (5/6)

## FUN_004771d0 — 0x4771d0

- Classification : internal
- Corps : `0x4771d0–0x4772f8`
- État : pseudocode obtenu
- Evidence : `ev_1902d92ef1dc3a7e2331f7bd28105daaa90997b861b7bd573302db9af6a1b795`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`
- `0x47f800` — `__allmul`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
longlong FUN_004771d0(byte *param_1)

{
  byte *pbVar1;
  uint uVar2;
  longlong lVar3;
  uint local_1c;
  uint local_18;
  int local_10;
  int local_c;
  uint local_8;
  
  while( true ) {
    if (DAT_004a87f4 < 2) {
      local_18 = *(ushort *)(PTR_DAT_004a85e8 + (uint)*param_1 * 2) & 8;
    }
    else {
      local_18 = FUN_0047f2b0(*param_1,8);
    }
    if (local_18 == 0) break;
    param_1 = param_1 + 1;
  }
  uVar2 = (uint)*param_1;
  if ((uVar2 == 0x2d) || (pbVar1 = param_1 + 1, local_8 = uVar2, uVar2 == 0x2b)) {
    local_8 = (uint)param_1[1];
    pbVar1 = param_1 + 2;
  }
  param_1 = pbVar1;
  lVar3 = 0;
  while( true ) {
    local_c = (int)((ulonglong)lVar3 >> 0x20);
    local_10 = (int)lVar3;
    if (DAT_004a87f4 < 2) {
      local_1c = *(ushort *)(PTR_DAT_004a85e8 + local_8 * 2) & 4;
    }
    else {
      local_1c = FUN_0047f2b0(local_8,4);
    }
    if (local_1c == 0) break;
    lVar3 = __allmul(lVar3,10,0);
    lVar3 = lVar3 + (int)(local_8 - 0x30);
    local_8 = (uint)*param_1;
    param_1 = param_1 + 1;
  }
  if (uVar2 == 0x2d) {
    lVar3 = CONCAT44(-(local_c + (uint)(local_10 != 0)),-local_10);
  }
  return lVar3;
}
```

---

## FUN_00477300 — 0x477300

- Classification : internal
- Corps : `0x477300–0x477313`
- État : pseudocode obtenu
- Evidence : `ev_eda78242e11571540d13466afec8e75fb4f75c8fd305646d84be629053a32c69`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47731d` — `FUN_0047731d`
- `0x47f628` — `FUN_0047f628`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00477300(void)

{
  float10 in_ST0;
  
  FUN_0047f628((double)in_ST0);
  FUN_0047731d();
  return;
}
```

---

## FUN_00477314 — 0x477314

- Classification : internal
- Corps : `0x477314–0x47731c`
- État : pseudocode obtenu
- Evidence : `ev_83195e44e6883b47aaee3ce5d7ff0d068c2f04ef0360f1a9a07da353ed47457e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x477318 to 0x47f5e5 __fload_withFB (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `0x47f5e5` — `__fload_withFB`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00477314(void)

{
                    /* WARNING: Subroutine does not return */
  __fload_withFB();
}
```

---

## FUN_0047731d — 0x47731d

- Classification : internal
- Corps : `0x47731d–0x4773ad`
- État : pseudocode obtenu
- Evidence : `ev_2e0bbe308567ead28deeb359f45a3a89be617e56ecd99b306790e11441f2e0cf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x477352 to 0x47f64b __math_exit (external=false, thunk=false, hasNoReturn=false); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.

### Appels directs

- `0x47f557` — `__startOneArgErrorHandling`
- `0x47f5cc` — `FUN_0047f5cc`
- `0x47f64b` — `__math_exit`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ushort FUN_0047731d(int param_1)

{
  ushort uVar1;
  uint in_EAX;
  bool in_ZF;
  ushort in_FPUStatusWord;
  unkbyte10 in_ST0;
  float10 fVar2;
  
  if (in_ZF) {
    if (((in_EAX & 0xfffff) == 0) && (param_1 == 0)) {
      in_FPUStatusWord = 1;
    }
    else {
      in_FPUStatusWord = FUN_0047f5cc();
    }
    if (DAT_00632500 == 0) {
      uVar1 = __startOneArgErrorHandling();
      return uVar1;
    }
  }
  else {
    fVar2 = (float10)fsin(in_ST0);
    if ((in_FPUStatusWord & 0x400) != 0) {
      do {
        fVar2 = fVar2 - ROUND(fVar2 / _DAT_00495e5a) * _DAT_00495e5a;
      } while ((in_FPUStatusWord & 0x400) != 0);
      fsin(fVar2);
    }
    if (DAT_00632500 == 0) {
      uVar1 = __math_exit();
      return uVar1;
    }
  }
  return in_FPUStatusWord;
}
```

---

## FUN_004773b0 — 0x4773b0

- Classification : internal
- Corps : `0x4773b0–0x4774e9`
- État : pseudocode obtenu
- Evidence : `ev_857b1ffd8ce074228de29be467b860c68884ba9db965c6abf37054ca99123b3a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
byte * FUN_004773b0(byte *param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  byte *local_30;
  byte abStack_2c [32];
  int local_c;
  byte *local_8;
  
  local_30 = param_2;
  for (local_c = 0; local_c < 0x20; local_c = local_c + 1) {
    abStack_2c[local_c] = 0;
  }
  do {
    abStack_2c[(int)(uint)*local_30 >> 3] =
         abStack_2c[(int)(uint)*local_30 >> 3] | (byte)(1 << (*local_30 & 7));
    bVar1 = *local_30;
    local_30 = local_30 + 1;
  } while (bVar1 != 0);
  if (param_1 == (byte *)0x0) {
    local_8 = DAT_0063256c;
  }
  else {
    local_8 = param_1;
  }
  for (; (pbVar2 = local_8, ((uint)abStack_2c[(int)(uint)*local_8 >> 3] & 1 << (*local_8 & 7)) != 0
         && (*local_8 != 0)); local_8 = local_8 + 1) {
  }
  do {
    if (*local_8 == 0) {
LAB_004774cf:
      DAT_0063256c = local_8;
      if (pbVar2 == local_8) {
        pbVar2 = (byte *)0x0;
      }
      return pbVar2;
    }
    if (((uint)abStack_2c[(int)(uint)*local_8 >> 3] & 1 << (*local_8 & 7)) != 0) {
      *local_8 = 0;
      local_8 = local_8 + 1;
      goto LAB_004774cf;
    }
    local_8 = local_8 + 1;
  } while( true );
}
```

---

## _strcmp — 0x4774f0

- Classification : internal
- Corps : `0x4774f0–0x477532`, `0x477534–0x477539`, `0x47753c–0x477573`
- État : pseudocode obtenu
- Evidence : `ev_eb78a378fbed9d48e7cfa79b2af160d595375af09ae0d3d053329721b60aed59`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _strcmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl _strcmp(char *_Str1,char *_Str2)

{
  undefined2 uVar1;
  undefined4 uVar2;
  byte bVar3;
  byte bVar4;
  bool bVar5;
  
  if (((uint)_Str1 & 3) != 0) {
    if (((uint)_Str1 & 1) != 0) {
      bVar4 = *_Str1;
      _Str1 = _Str1 + 1;
      bVar5 = bVar4 < (byte)*_Str2;
      if (bVar4 != *_Str2) goto LAB_00477534;
      _Str2 = _Str2 + 1;
      if (bVar4 == 0) {
        return 0;
      }
      if (((uint)_Str1 & 2) == 0) goto LAB_00477500;
    }
    uVar1 = *(undefined2 *)_Str1;
    _Str1 = _Str1 + 2;
    bVar4 = (byte)uVar1;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) goto LAB_00477534;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((ushort)uVar1 >> 8);
    bVar5 = bVar4 < (byte)_Str2[1];
    if (bVar4 != _Str2[1]) goto LAB_00477534;
    if (bVar4 == 0) {
      return 0;
    }
    _Str2 = _Str2 + 2;
  }
LAB_00477500:
  while( true ) {
    uVar2 = *(undefined4 *)_Str1;
    bVar4 = (byte)uVar2;
    bVar5 = bVar4 < (byte)*_Str2;
    if (bVar4 != *_Str2) break;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((uint)uVar2 >> 8);
    bVar5 = bVar4 < (byte)_Str2[1];
    if (bVar4 != _Str2[1]) break;
    if (bVar4 == 0) {
      return 0;
    }
    bVar4 = (byte)((uint)uVar2 >> 0x10);
    bVar5 = bVar4 < (byte)_Str2[2];
    if (bVar4 != _Str2[2]) break;
    bVar3 = (byte)((uint)uVar2 >> 0x18);
    if (bVar4 == 0) {
      return 0;
    }
    bVar5 = bVar3 < (byte)_Str2[3];
    if (bVar3 != _Str2[3]) break;
    _Str2 = _Str2 + 4;
    _Str1 = _Str1 + 4;
    if (bVar3 == 0) {
      return 0;
    }
  }
LAB_00477534:
  return (uint)bVar5 * -2 + 1;
}
```

---

## FUN_00477580 — 0x477580

- Classification : internal
- Corps : `0x477580–0x477598`
- État : pseudocode obtenu
- Evidence : `ev_30692b692c463c2db3fe759e5d632abaaf5a77e17d5ba2575db4e4d75915a7c5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4775a2` — `FUN_004775a2`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00477580(void)

{
  float10 in_ST0;
  float10 in_ST1;
  
  FUN_004775a2((double)in_ST1,(double)in_ST0);
  return;
}
```

---

## FUN_00477599 — 0x477599

- Classification : internal
- Corps : `0x477599–0x4775a1`
- État : pseudocode obtenu
- Evidence : `ev_53e17c6fb9e0e589570e41e96b9de8e17280abf0cfeface67efc6edb2712f840`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x47759d to 0x47f5e5 __fload_withFB (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `0x47f5e5` — `__fload_withFB`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00477599(void)

{
                    /* WARNING: Subroutine does not return */
  __fload_withFB();
}
```

---

## FUN_004775a2 — 0x4775a2

- Classification : internal
- Corps : `0x4775a2–0x4775d0`, `0x477639–0x477641`, `0x477669–0x47767e`
- État : pseudocode obtenu
- Evidence : `ev_1ef40e2605dd28845c303ee317460b4cb1c0a9a617b986ec3fd309ad51029f1a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x4775cc to 0x47f5e5 __fload_withFB (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return. Ghidra Listing reports a terminal call at 0x47763d to 0x47f5e5 __fload_withFB (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return. Ghidra Listing reports a terminal call at 0x47767a to 0x47f5e5 __fload_withFB (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `0x47f5b5` — `FUN_0047f5b5`
- `0x47f5e5` — `__fload_withFB`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004775a2(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint in_EAX;
  uint extraout_ECX;
  uint uVar1;
  short in_FPUControlWord;
  
  uVar1 = in_EAX;
  if (in_FPUControlWord != 0x27f) {
    in_EAX = FUN_0047f5b5();
    uVar1 = extraout_ECX;
  }
  if ((uVar1 & 0x7ff00000) != 0x7ff00000) {
                    /* WARNING: Subroutine does not return */
    __fload_withFB();
  }
  if ((in_EAX & 0xfffff) == 0 && param_3 == 0) {
                    /* WARNING: Subroutine does not return */
    __fload_withFB();
  }
                    /* WARNING: Subroutine does not return */
  __fload_withFB();
}
```

---

## FUN_004777a0 — 0x4777a0

- Classification : internal
- Corps : `0x4777a0–0x4779d3`
- État : pseudocode obtenu
- Evidence : `ev_67c26586715584be82c288d4929339e579595b59f0c086c56dd57bdbb9d996f5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4779e0` — `shortsort`
- `0x477a50` — `swap`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004777a0(uint param_1,uint param_2,uint param_3,code *param_4)

{
  int iVar1;
  uint local_110;
  uint auStack_10c [30];
  uint local_94;
  uint auStack_90 [30];
  uint local_18;
  int local_14;
  uint local_10;
  int local_c;
  uint local_8;
  
  if ((param_2 < 2) || (param_3 == 0)) {
    return;
  }
  local_14 = 0;
  local_10 = param_1;
  local_110 = param_1 + param_3 * (param_2 - 1);
LAB_004777de:
  local_8 = (local_110 - local_10) / param_3 + 1;
  if (8 < local_8) {
    local_c = local_10 + (local_8 >> 1) * param_3;
    swap(local_c,local_10,param_3);
    local_18 = local_10;
    local_94 = local_110 + param_3;
LAB_00477852:
    local_18 = local_18 + param_3;
    if (local_18 <= local_110) goto code_r0x00477866;
    goto LAB_00477878;
  }
  shortsort(local_10,local_110,param_3,param_4);
  goto LAB_0047799f;
code_r0x00477866:
  iVar1 = (*param_4)(local_18,local_10);
  if (iVar1 < 1) goto LAB_00477852;
LAB_00477878:
  do {
    local_94 = local_94 - param_3;
    if (local_94 <= local_10) break;
    iVar1 = (*param_4)(local_94,local_10);
  } while (-1 < iVar1);
  if (local_18 <= local_94) {
    swap(local_18,local_94,param_3);
    goto LAB_00477852;
  }
  swap(local_10,local_94,param_3);
  if ((int)((local_94 - 1) - local_10) < (int)(local_110 - local_18)) {
    if (local_18 < local_110) {
      auStack_90[local_14] = local_18;
      auStack_10c[local_14] = local_110;
      local_14 = local_14 + 1;
    }
    if (local_10 + param_3 < local_94) {
      local_110 = local_94 - param_3;
      goto LAB_004777de;
    }
  }
  else {
    if (local_10 + param_3 < local_94) {
      auStack_90[local_14] = local_10;
      auStack_10c[local_14] = local_94 - param_3;
      local_14 = local_14 + 1;
    }
    if (local_18 < local_110) {
      local_10 = local_18;
      goto LAB_004777de;
    }
  }
LAB_0047799f:
  local_14 = local_14 + -1;
  if (local_14 < 0) {
    return;
  }
  local_10 = auStack_90[local_14];
  local_110 = auStack_10c[local_14];
  goto LAB_004777de;
}
```

---

## shortsort — 0x4779e0

- Classification : internal
- Corps : `0x4779e0–0x477a4c`
- État : pseudocode obtenu
- Evidence : `ev_9369c3102b6e153561fb9884a18ee162d4b72e5c1299e0bee10f124ab3a131cc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x477a50` — `swap`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _shortsort
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual
   Studio 2010 Debug */

void __cdecl shortsort(uint param_1,uint param_2,int param_3,code *param_4)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  for (; param_1 < param_2; param_2 = param_2 - param_3) {
    local_c = param_1;
    local_8 = param_1;
    while (local_8 = local_8 + param_3, local_8 <= param_2) {
      iVar1 = (*param_4)(local_8,local_c);
      if (0 < iVar1) {
        local_c = local_8;
      }
    }
    swap(local_c,param_2,param_3);
  }
  return;
}
```

---

## swap — 0x477a50

- Classification : internal
- Corps : `0x477a50–0x477a9d`
- État : pseudocode obtenu
- Evidence : `ev_2950a95b58e8a552dd5aca3e6e2375def2920670446bc26d115446d5daa9c702`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _swap
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2005 Debug, Visual Studio 2008 Debug, Visual
   Studio 2010 Debug */

void __cdecl swap(undefined1 *param_1,undefined1 *param_2,int param_3)

{
  undefined1 uVar1;
  
  if (param_1 != param_2) {
    while (param_3 != 0) {
      uVar1 = *param_1;
      *param_1 = *param_2;
      param_1 = param_1 + 1;
      *param_2 = uVar1;
      param_2 = param_2 + 1;
      param_3 = param_3 + -1;
    }
  }
  return;
}
```

---

## FUN_00477aa0 — 0x477aa0

- Classification : internal
- Corps : `0x477aa0–0x477ab3`
- État : pseudocode obtenu
- Evidence : `ev_862df2ac266faef809a9d3d5198b04ba77d36391f94d0f25eff7961b9be40691`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x477abd` — `FUN_00477abd`
- `0x47f628` — `FUN_0047f628`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00477aa0(void)

{
  float10 in_ST0;
  
  FUN_0047f628((double)in_ST0);
  FUN_00477abd();
  return;
}
```

---

## FUN_00477ab4 — 0x477ab4

- Classification : internal
- Corps : `0x477ab4–0x477abc`
- État : pseudocode obtenu
- Evidence : `ev_00953bad2ddc5bda717ba63bea5321752793ad3cc53df37593084248ff91eb41`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x477ab8 to 0x47f5e5 __fload_withFB (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `0x47f5e5` — `__fload_withFB`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00477ab4(void)

{
                    /* WARNING: Subroutine does not return */
  __fload_withFB();
}
```

---

## FUN_00477abd — 0x477abd

- Classification : internal
- Corps : `0x477abd–0x477b4d`
- État : pseudocode obtenu
- Evidence : `ev_d9ee78f662f4d549a4460edbd8e684130a45d831555d9c6889384d7cc795f4b7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x477af2 to 0x47f64b __math_exit (external=false, thunk=false, hasNoReturn=false); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.

### Appels directs

- `0x47f557` — `__startOneArgErrorHandling`
- `0x47f5cc` — `FUN_0047f5cc`
- `0x47f64b` — `__math_exit`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ushort FUN_00477abd(int param_1)

{
  ushort uVar1;
  uint in_EAX;
  bool in_ZF;
  ushort in_FPUStatusWord;
  unkbyte10 in_ST0;
  float10 fVar2;
  
  if (in_ZF) {
    if (((in_EAX & 0xfffff) == 0) && (param_1 == 0)) {
      in_FPUStatusWord = 1;
    }
    else {
      in_FPUStatusWord = FUN_0047f5cc();
    }
    if (DAT_00632500 == 0) {
      uVar1 = __startOneArgErrorHandling();
      return uVar1;
    }
  }
  else {
    fVar2 = (float10)fcos(in_ST0);
    if ((in_FPUStatusWord & 0x400) != 0) {
      do {
        fVar2 = fVar2 - ROUND(fVar2 / _DAT_00495e5a) * _DAT_00495e5a;
      } while ((in_FPUStatusWord & 0x400) != 0);
      fcos(fVar2);
    }
    if (DAT_00632500 == 0) {
      uVar1 = __math_exit();
      return uVar1;
    }
  }
  return in_FPUStatusWord;
}
```

---

## FUN_00477b50 — 0x477b50

- Classification : internal
- Corps : `0x477b50–0x477b5a`
- État : pseudocode obtenu
- Evidence : `ev_c8a6533ea23e82a84c6d96e49b3c94bc1d0e0b5aeb17d67dee5f450b96949394`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00477b50(int param_1)

{
  return param_1 + -0x20;
}
```

---

## FUN_00477b60 — 0x477b60

- Classification : internal
- Corps : `0x477b60–0x477c88`
- État : pseudocode obtenu
- Evidence : `ev_7cd25b1f09406593647ce2d978a535763c1e0eccaf1beca1690a92f67f795dff`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`
- `0x480050` — `FUN_00480050`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00477b60(uint param_1)

{
  int iVar1;
  uint local_14;
  uint local_10;
  undefined1 local_c;
  undefined1 local_b;
  undefined1 local_a;
  undefined4 local_8;
  
  if (DAT_006325e8 == 0) {
    if ((0x60 < (int)param_1) && ((int)param_1 < 0x7b)) {
      param_1 = param_1 - 0x20;
    }
  }
  else {
    if ((int)param_1 < 0x100) {
      if (DAT_004a87f4 < 2) {
        local_14 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 2;
      }
      else {
        local_14 = FUN_0047f2b0(param_1,2);
      }
      if (local_14 == 0) {
        return param_1;
      }
    }
    if ((*(ushort *)(PTR_DAT_004a85e8 + ((int)param_1 >> 8 & 0xffU) * 2) & 0x8000) == 0) {
      local_c = (undefined1)param_1;
      local_b = 0;
      local_8 = 1;
    }
    else {
      local_c = (undefined1)(param_1 >> 8);
      local_b = (undefined1)param_1;
      local_a = 0;
      local_8 = 2;
    }
    iVar1 = FUN_00480050(DAT_006325e8,0x200,&local_c,local_8,&local_10,3,0);
    if (iVar1 != 0) {
      if (iVar1 == 1) {
        param_1 = local_10 & 0xff;
      }
      else {
        param_1 = local_10 & 0xff | (local_10 >> 8 & 0xff) << 8;
      }
    }
  }
  return param_1;
}
```

---

## FUN_00477c90 — 0x477c90

- Classification : internal
- Corps : `0x477c90–0x47808c`
- État : pseudocode obtenu
- Evidence : `ev_9bd18987248cf70c13e954ff5fdb2e7102f8c9a38bbb9b18d7cdbe7c80770f01`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `EXTERNAL:0x38` — `KERNEL32.DLL::GetFileType`
- `EXTERNAL:0x42` — `KERNEL32.DLL::FileTimeToSystemTime`
- `EXTERNAL:0x43` — `KERNEL32.DLL::FileTimeToLocalFileTime`
- `EXTERNAL:0x44` — `KERNEL32.DLL::GetFileInformationByHandle`
- `EXTERNAL:0x45` — `KERNEL32.DLL::PeekNamedPipe`
- `0x47cac0` — `__dosmaperr`
- `0x480360` — `FUN_00480360`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00477c90(uint param_1,uint *param_2)

{
  DWORD DVar1;
  BOOL BVar2;
  uint uVar3;
  int iVar4;
  uint local_60 [2];
  undefined4 local_58;
  _FILETIME local_54;
  uint local_4c;
  _BY_HANDLE_FILE_INFORMATION local_48;
  _SYSTEMTIME local_14;
  
  local_58 = 0;
  if ((param_1 < DAT_00633e5c) &&
     (iVar4 = (int)param_1 >> 5,
     (*(byte *)((&DAT_00633d20)[iVar4] + 4 + (param_1 & 0x1f) * 8) & 1) != 0)) {
    DVar1 = GetFileType(*(HANDLE *)((&DAT_00633d20)[iVar4] + (param_1 & 0x1f) * 8));
    local_4c = DVar1 & 0xffff7fff;
    if (local_4c == 1) {
      *(undefined2 *)((int)param_2 + 6) = 0;
      *(undefined2 *)(param_2 + 3) = 0;
      *(undefined2 *)((int)param_2 + 10) = 0;
      *(undefined2 *)(param_2 + 1) = 0;
      *(undefined2 *)(param_2 + 2) = 1;
      BVar2 = GetFileInformationByHandle
                        (*(HANDLE *)((&DAT_00633d20)[iVar4] + (param_1 & 0x1f) * 8),&local_48);
      if (BVar2 == 0) {
        DVar1 = GetLastError();
        __dosmaperr(DVar1);
        local_58 = 0xffffffff;
      }
      else {
        if ((local_48.dwFileAttributes & 1) == 0) {
          *(ushort *)((int)param_2 + 6) = *(ushort *)((int)param_2 + 6) | 0x1b6;
        }
        else {
          *(ushort *)((int)param_2 + 6) = *(ushort *)((int)param_2 + 6) | 0x124;
        }
        BVar2 = FileTimeToLocalFileTime(&local_48.ftLastWriteTime,&local_54);
        if ((BVar2 == 0) || (BVar2 = FileTimeToSystemTime(&local_54,&local_14), BVar2 == 0)) {
          local_58 = 0xffffffff;
        }
        else {
          uVar3 = FUN_00480360(local_14.wYear,local_14.wMonth,local_14.wDay,local_14.wHour,
                               local_14.wMinute,local_14.wSecond,0xffffffff);
          param_2[7] = uVar3;
          if ((local_48.ftLastAccessTime.dwLowDateTime == 0) &&
             (local_48.ftLastAccessTime.dwHighDateTime == 0)) {
            param_2[6] = param_2[7];
          }
          else {
            BVar2 = FileTimeToLocalFileTime(&local_48.ftLastAccessTime,&local_54);
            if ((BVar2 == 0) || (BVar2 = FileTimeToSystemTime(&local_54,&local_14), BVar2 == 0)) {
              return 0xffffffff;
            }
            uVar3 = FUN_00480360(local_14.wYear,local_14.wMonth,local_14.wDay,local_14.wHour,
                                 local_14.wMinute,local_14.wSecond,0xffffffff);
            param_2[6] = uVar3;
          }
          if ((local_48.ftCreationTime.dwLowDateTime == 0) &&
             (local_48.ftCreationTime.dwHighDateTime == 0)) {
            param_2[8] = param_2[7];
          }
          else {
            BVar2 = FileTimeToLocalFileTime(&local_48.ftCreationTime,&local_54);
            if ((BVar2 == 0) || (BVar2 = FileTimeToSystemTime(&local_54,&local_14), BVar2 == 0)) {
              return 0xffffffff;
            }
            uVar3 = FUN_00480360(local_14.wYear,local_14.wMonth,local_14.wDay,local_14.wHour,
                                 local_14.wMinute,local_14.wSecond,0xffffffff);
            param_2[8] = uVar3;
          }
          param_2[5] = local_48.nFileSizeLow;
          *(ushort *)((int)param_2 + 6) = *(ushort *)((int)param_2 + 6) | 0x8000;
          *param_2 = 0;
          param_2[4] = 0;
        }
      }
    }
    else if ((local_4c == 2) || (local_4c == 3)) {
      if (local_4c == 2) {
        *(undefined2 *)((int)param_2 + 6) = 0x2000;
      }
      else {
        *(undefined2 *)((int)param_2 + 6) = 0x1000;
      }
      *param_2 = param_1;
      param_2[4] = param_1;
      *(undefined2 *)(param_2 + 2) = 1;
      *(undefined2 *)(param_2 + 1) = 0;
      *(undefined2 *)(param_2 + 3) = 0;
      *(undefined2 *)((int)param_2 + 10) = 0;
      param_2[8] = 0;
      param_2[7] = 0;
      param_2[6] = 0;
      if (local_4c == 2) {
        param_2[5] = 0;
      }
      else {
        BVar2 = PeekNamedPipe(*(HANDLE *)((&DAT_00633d20)[iVar4] + (param_1 & 0x1f) * 8),(LPVOID)0x0
                              ,0,(LPDWORD)0x0,local_60,(LPDWORD)0x0);
        if (BVar2 == 0) {
          param_2[5] = 0;
        }
        else {
          param_2[5] = local_60[0];
        }
      }
    }
    else if (local_4c == 0) {
      _DAT_0063251c = 9;
      local_58 = 0xffffffff;
    }
    else {
      DVar1 = GetLastError();
      __dosmaperr(DVar1);
      local_58 = 0xffffffff;
    }
  }
  else {
    _DAT_0063251c = 9;
    local_58 = 0xffffffff;
  }
  return local_58;
}
```

---

## FUN_00478090 — 0x478090

- Classification : internal
- Corps : `0x478090–0x4780ed`
- État : pseudocode obtenu
- Evidence : `ev_fffd3754939be29f397228491ee67e1a2f4e8970ebf9a9f9f71abba48b197f68`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xc` — `KERNEL32.DLL::GetLastError`
- `EXTERNAL:0x46` — `KERNEL32.DLL::GetFileAttributesA`
- `0x47cac0` — `__dosmaperr`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00478090(LPCSTR param_1,uint param_2)

{
  DWORD DVar1;
  undefined4 uVar2;
  
  DVar1 = GetFileAttributesA(param_1);
  if (DVar1 == 0xffffffff) {
    DVar1 = GetLastError();
    __dosmaperr(DVar1);
    uVar2 = 0xffffffff;
  }
  else if (((DVar1 & 1) == 0) || ((param_2 & 2) == 0)) {
    uVar2 = 0;
  }
  else {
    _DAT_0063251c = 0xd;
    DAT_00632520 = 5;
    uVar2 = 0xffffffff;
  }
  return uVar2;
}
```

---

## FID_conflict:__ctime64 — 0x4780f0

- Classification : internal
- Corps : `0x4780f0–0x47811c`
- État : pseudocode obtenu
- Evidence : `ev_a598862934c96887792e97149f001416c9b5d956da7f2eca7cae8d26816c3064`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x480450` — `_asctime`
- `0x480610` — `FUN_00480610`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Multiple Matches With Different Base Names
    __ctime64
    _ctime
   
   Library: Visual Studio 2003 Debug */

char * __cdecl FID_conflict___ctime64(__time64_t *_Time)

{
  tm *_Tm;
  char *pcVar1;
  
  _Tm = (tm *)FUN_00480610(_Time);
  if (_Tm == (tm *)0x0) {
    pcVar1 = (char *)0x0;
  }
  else {
    pcVar1 = _asctime(_Tm);
  }
  return pcVar1;
}
```

---

## FUN_00478120 — 0x478120

- Classification : internal
- Corps : `0x478120–0x478133`
- État : pseudocode obtenu
- Evidence : `ev_278dc631c573d3f2b4d2861250d8deb37e3054b136b141cd1a3e181bed6c2619`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47813d` — `FUN_0047813d`
- `0x47f628` — `FUN_0047f628`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00478120(void)

{
  float10 in_ST0;
  
  FUN_0047f628((double)in_ST0);
  FUN_0047813d();
  return;
}
```

---

## FUN_00478134 — 0x478134

- Classification : internal
- Corps : `0x478134–0x47813c`
- État : pseudocode obtenu
- Evidence : `ev_05f1047ee6aeef611ddb20d155f9d273d09cf50461fbac05a86e3ef1d123b97e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x478138 to 0x47f5e5 __fload_withFB (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `0x47f5e5` — `__fload_withFB`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00478134(void)

{
                    /* WARNING: Subroutine does not return */
  __fload_withFB();
}
```

---

## FUN_0047813d — 0x47813d

- Classification : internal
- Corps : `0x47813d–0x4781eb`
- État : pseudocode obtenu
- Evidence : `ev_c7fb60099c23104e6a6c49a616c28dc179f5aa084ff2a7d44b1e7c34f6f27e0d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x478182 to 0x47f64b __math_exit (external=false, thunk=false, hasNoReturn=false); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.

### Appels directs

- `0x47f557` — `__startOneArgErrorHandling`
- `0x47f5cc` — `FUN_0047f5cc`
- `0x47f64b` — `__math_exit`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_0047813d(int param_1,uint param_2)

{
  uint in_EAX;
  uint uVar1;
  bool in_ZF;
  unkbyte10 in_ST0;
  
  if (!in_ZF) {
    if ((param_2 & 0x7ff00000) == 0) {
      if (((param_2 & 0xfffff) == 0) && (param_1 == 0)) {
        uVar1 = 2;
        goto LAB_004781cd;
      }
    }
    else if ((param_2 & 0x80000000) != 0) goto LAB_0047819c;
    log2(in_ST0);
LAB_0047816a:
    if (DAT_00632500 != 0) {
      return param_2;
    }
    uVar1 = __math_exit();
    return uVar1;
  }
  if (((in_EAX & 0xfffff) != 0) || (param_1 != 0)) {
    uVar1 = FUN_0047f5cc();
    goto LAB_004781cd;
  }
  param_2 = 0;
  if ((in_EAX & 0x80000000) == 0) goto LAB_0047816a;
LAB_0047819c:
  uVar1 = 1;
LAB_004781cd:
  if (DAT_00632500 != 0) {
    return uVar1;
  }
  uVar1 = __startOneArgErrorHandling();
  return uVar1;
}
```

---


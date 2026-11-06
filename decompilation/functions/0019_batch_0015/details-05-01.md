# 0019_batch_0015 — détails (1/3)

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

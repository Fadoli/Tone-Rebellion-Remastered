# 0019_batch_0015 — détails (2/3)

## FUN_00476bb0 — 0x476bb0

- Classification : internal
- Corps : `0x476bb0–0x476c53`
- État : pseudocode obtenu
- Evidence : `ev_2b3bb94985379bd926543cc0e4defa0fc00301f9b47540ff74cb955d3f6cc020`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4751c0` — `__realloc_dbg`
- `0x475b90` — `FUN_00475b90`

### Chaînes référencées

- `0x495998` — "onexit.c"

### Pseudocode Ghidra

```c
undefined4 FUN_00476bb0(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_00475b90(DAT_00633e88,2);
  if (uVar1 < (uint)((int)DAT_00633e78 + (4 - DAT_00633e88))) {
    iVar2 = FUN_00475b90(DAT_00633e88,2,2,"onexit.c",0x68);
    iVar2 = __realloc_dbg(DAT_00633e88,iVar2 + 0x10);
    if (iVar2 == 0) {
      return 0;
    }
    DAT_00633e78 = (undefined4 *)(iVar2 + ((int)DAT_00633e78 - DAT_00633e88 >> 2) * 4);
    DAT_00633e88 = iVar2;
  }
  *DAT_00633e78 = param_1;
  DAT_00633e78 = DAT_00633e78 + 1;
  return param_1;
}
```

---

---

## FUN_00476c60 — 0x476c60

- Classification : internal
- Corps : `0x476c60–0x476c77`
- État : pseudocode obtenu
- Evidence : `ev_ab0fade9573780c7ea9a5f40d3a3e9cdad259c65961765a32f1bf13764936b2e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476bb0` — `FUN_00476bb0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00476c60(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_00476bb0(param_1);
  return (iVar1 != 0) - 1;
}
```

---

---

## FUN_00476c80 — 0x476c80

- Classification : internal
- Corps : `0x476c80–0x476ccc`
- État : pseudocode obtenu
- Evidence : `ev_2965ee0378ec87b2558fc8d2dc0185930e0a0be25955fe7fd2358b2f6b49fbc9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474d40` — `FUN_00474d40`
- `0x478690` — `__amsg_exit`

### Chaînes référencées

- `0x495998` — "onexit.c"

### Pseudocode Ghidra

```c
void FUN_00476c80(void)

{
  DAT_00633e88 = (undefined4 *)FUN_00474d40(0x80,2,"onexit.c",0xb6);
  if (DAT_00633e88 == (undefined4 *)0x0) {
    __amsg_exit(0x18);
  }
  *DAT_00633e88 = 0;
  DAT_00633e78 = DAT_00633e88;
  return;
}
```

---

---

## FUN_00476cd0 — 0x476cd0

- Classification : internal
- Corps : `0x476cd0–0x476ce3`
- État : pseudocode obtenu
- Evidence : `ev_eebb3741db644ee03e7ce1e5b50f31750bcb2d92405c4d464064ace4f062228d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476ced` — `FUN_00476ced`
- `0x47f628` — `FUN_0047f628`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00476cd0(void)

{
  float10 in_ST0;
  
  FUN_0047f628((double)in_ST0);
  FUN_00476ced();
  return;
}
```

---

---

## FUN_00476ce4 — 0x476ce4

- Classification : internal
- Corps : `0x476ce4–0x476cec`
- État : pseudocode obtenu
- Evidence : `ev_218437eb322d345e47ffe427623f354a3f6294a854efdbe51e76cddddca5a36c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x476ce8 to 0x47f5e5 __fload_withFB (external=false, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `0x47f5e5` — `__fload_withFB`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00476ce4(void)

{
                    /* WARNING: Subroutine does not return */
  __fload_withFB();
}
```

---

---

## FUN_00476ced — 0x476ced

- Classification : internal
- Corps : `0x476ced–0x476d89`
- État : pseudocode obtenu
- Evidence : `ev_4eaf77e7897a66628ae432750a6925565f2b09f730ef38c15e080e60723e93cf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x476d26 to 0x47f64b __math_exit (external=false, thunk=false, hasNoReturn=false); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.

### Appels directs

- `0x47f557` — `__startOneArgErrorHandling`
- `0x47f5b5` — `FUN_0047f5b5`
- `0x47f5cc` — `FUN_0047f5cc`
- `0x47f64b` — `__math_exit`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00476ced(uint param_1,uint param_2)

{
  uint uVar1;
  bool in_ZF;
  short in_FPUControlWord;
  
  if (in_ZF) {
    if (((param_2 & 0xfffff) != 0) || (param_1 != 0)) {
      uVar1 = FUN_0047f5cc();
      goto LAB_00476d6b;
    }
    param_1 = param_2 & 0x80000000;
    param_2 = 0;
joined_r0x00476d5c:
    if (param_1 == 0) {
LAB_00476d0e:
      if (DAT_00632500 != 0) {
        return param_2;
      }
      uVar1 = __math_exit();
      return uVar1;
    }
  }
  else {
    if (in_FPUControlWord != 0x27f) {
      param_2 = FUN_0047f5b5();
    }
    if ((param_2 & 0x80000000) == 0) goto LAB_00476d0e;
    if (((param_2 & 0x7ff00000) == 0) && ((param_2 & 0xfffff) == 0)) goto joined_r0x00476d5c;
  }
  uVar1 = 1;
LAB_00476d6b:
  if (DAT_00632500 != 0) {
    return uVar1;
  }
  uVar1 = __startOneArgErrorHandling();
  return uVar1;
}
```

---

---

## FUN_00476d90 — 0x476d90

- Classification : internal
- Corps : `0x476d90–0x476e19`
- État : pseudocode obtenu
- Evidence : `ev_b301512b912e586c13b189dcb6ffa8869b3c4572b91672b85f9ed4b75aef680d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x476df9 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x475780` — `FUN_00475780`
- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x4955f0` — "_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)"
- `0x4959a4` — "dbgdel.cpp"

### Pseudocode Ghidra

```c
void FUN_00476d90(int param_1)

{
  code *pcVar1;
  int iVar2;
  
  if (param_1 != 0) {
    if (((((*(uint *)(param_1 + -0xc) & 0xffff) != 4) && (*(int *)(param_1 + -0xc) != 1)) &&
        ((*(uint *)(param_1 + -0xc) & 0xffff) != 2)) &&
       ((*(int *)(param_1 + -0xc) != 3 &&
        (iVar2 = FUN_0047a120(2,"dbgdel.cpp",0x2f,0,"_BLOCK_TYPE_IS_VALID(pHead->nBlockUse)"),
        iVar2 == 1)))) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    FUN_00475780(param_1,*(undefined4 *)(param_1 + -0xc));
  }
  return;
}
```

---

## _strncmp — 0x476e20

- Classification : internal
- Corps : `0x476e20–0x476e57`
- État : pseudocode obtenu
- Evidence : `ev_69246139307ea4bf51185ca11014c13fe29f446d7283005d05e233e8a43bab5a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    _strncmp
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl _strncmp(char *_Str1,char *_Str2,size_t _MaxCount)

{
  char cVar1;
  char cVar2;
  size_t sVar3;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  uVar5 = 0;
  sVar3 = _MaxCount;
  pcVar6 = _Str1;
  if (_MaxCount != 0) {
    do {
      if (sVar3 == 0) break;
      sVar3 = sVar3 - 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar1 != '\0');
    iVar4 = _MaxCount - sVar3;
    do {
      pcVar6 = _Str2;
      pcVar7 = _Str1;
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      pcVar7 = _Str1 + 1;
      pcVar6 = _Str2 + 1;
      cVar2 = *_Str1;
      cVar1 = *_Str2;
      _Str2 = pcVar6;
      _Str1 = pcVar7;
    } while (cVar1 == cVar2);
    uVar5 = 0;
    if ((byte)pcVar6[-1] <= (byte)pcVar7[-1]) {
      if (pcVar6[-1] == pcVar7[-1]) {
        return 0;
      }
      uVar5 = 0xfffffffe;
    }
    uVar5 = ~uVar5;
  }
  return uVar5;
}
```

---

---

## FUN_00476e60 — 0x476e60

- Classification : internal
- Corps : `0x476e60–0x476e97`
- État : pseudocode obtenu
- Evidence : `ev_490b5248d34e97cceecf8c5aacc478405c9a1374d12146626f1fc6aee050606f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472bc0` — `FUN_00472bc0`
- `0x477000` — `__initterm`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00476e60(void)

{
  if (PTR_FUN_004a6318 != (undefined *)0x0) {
    (*(code *)PTR_FUN_004a6318)();
  }
  __initterm(&DAT_00498350,&DAT_00498664);
  __initterm(&DAT_00498000,&DAT_0049824c);
  return;
}
```

---

---

## FUN_00476ea0 — 0x476ea0

- Classification : internal
- Corps : `0x476ea0–0x476eb4`
- État : pseudocode obtenu
- Evidence : `ev_ee0a646acb8876c506cfac57bfa75aea685a7b72022c0882968940b78cfa4d35`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476f20` — `FUN_00476f20`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00476ea0(undefined4 param_1)

{
  FUN_00476f20(param_1,0,0);
  return;
}
```

---

## __exit — 0x476ec0

- Classification : internal
- Corps : `0x476ec0–0x476ed4`
- État : pseudocode obtenu
- Evidence : `ev_2862c729d6544b557874b77f783e66470ea875ccb5f315de14dfa871ec365a4d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476f20` — `FUN_00476f20`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __exit
   
   Library: Visual Studio 2003 Debug */

void __cdecl __exit(int _Code)

{
  FUN_00476f20(_Code,1,0);
  return;
}
```

---

---

## FUN_00476ee0 — 0x476ee0

- Classification : internal
- Corps : `0x476ee0–0x476ef2`
- État : pseudocode obtenu
- Evidence : `ev_672b5bdc5eb480f4d3759b4e51129193c1e1de474371a4138b88d5c861b2797e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476f20` — `FUN_00476f20`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00476ee0(void)

{
  FUN_00476f20(0,0,1);
  return;
}
```

---

---

## FUN_00476f00 — 0x476f00

- Classification : internal
- Corps : `0x476f00–0x476f12`
- État : pseudocode obtenu
- Evidence : `ev_653b0bba04dc03df8375c409e99e0b0b5f39bef26ee310270b5ac33c7fff214c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476f20` — `FUN_00476f20`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00476f00(void)

{
  FUN_00476f20(0,1,1);
  return;
}
```

---

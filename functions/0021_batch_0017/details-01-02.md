# 0021_batch_0017 — détails (2/3)

## FUN_0047f2b0 — 0x47f2b0

- Classification : internal
- Corps : `0x47f2b0–0x47f364`
- État : pseudocode obtenu
- Evidence : `ev_0275cffc0ee5ad6c6796b6c465d9d7166d56f76cf76033030c002c2428d76d86`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4850c0` — `FUN_004850c0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_0047f2b0(int param_1,uint param_2)

{
  int iVar1;
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined4 local_c;
  uint local_8;
  
  if (param_1 + 1U < 0x101) {
    param_2 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & param_2;
  }
  else {
    if ((*(ushort *)(PTR_DAT_004a85e8 + (param_1 >> 8 & 0xffU) * 2) & 0x8000) == 0) {
      local_10 = (undefined1)param_1;
      local_f = 0;
      local_c = 1;
    }
    else {
      local_10 = (undefined1)((uint)param_1 >> 8);
      local_f = (undefined1)param_1;
      local_e = 0;
      local_c = 2;
    }
    iVar1 = FUN_004850c0(1,&local_10,local_c,&local_8,0,0);
    if (iVar1 == 0) {
      param_2 = 0;
    }
    else {
      param_2 = local_8 & 0xffff & param_2;
    }
  }
  return param_2;
}
```

---

## __trandisp1 — 0x47f370

- Classification : internal
- Corps : `0x47f370–0x47f3d6`
- État : pseudocode obtenu
- Evidence : `ev_d981cf225f753d3dd391f97aec99be4b7ead2e066244d0c8dc119ad74d5f5f09`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __trandisp1
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __trandisp1(void)

{
  float10 fVar1;
  byte bVar2;
  int in_EDX;
  undefined2 uVar3;
  int unaff_EBP;
  float10 in_ST0;
  
  if (*(char *)(in_EDX + 0xe) == '\x05') {
    uVar3 = (undefined2)
            CONCAT31((uint3)((byte)((ushort)*(undefined2 *)(unaff_EBP + -0xa4) >> 8) & 0xfe | 2),
                     0x3f);
  }
  else {
    uVar3 = 0x133f;
  }
  *(undefined2 *)(unaff_EBP + -0xa2) = uVar3;
  fVar1 = (float10)0;
  *(int *)(unaff_EBP + -0x94) = in_EDX;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST0) << 8 | (ushort)(in_ST0 < fVar1) << 9 | (ushort)(in_ST0 != fVar1) << 10 |
       (ushort)(in_ST0 == fVar1) << 0xe;
  *(undefined1 *)(unaff_EBP + -0x90) = 0;
  bVar2 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
                    /* WARNING: Could not recover jumptable at 0x0047f3d5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(in_EDX + (char)(&DAT_004a881d)[(byte)((bVar2 & 7) << 1 | (char)bVar2 < '\0')] + 0x10)
  )();
  return;
}
```

---

## __trandisp2 — 0x47f3d7

- Classification : internal
- Corps : `0x47f3d7–0x47f462`
- État : pseudocode obtenu
- Evidence : `ev_c8b1010e215c8218ff3c61ac1c916ac61805557fed4a61774bd4a940ab093d86`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __trandisp2
   
   Libraries: Visual Studio 1998, Visual Studio 2003, Visual Studio 2019 */

void __trandisp2(void)

{
  float10 fVar1;
  char cVar2;
  byte bVar3;
  int in_EDX;
  undefined2 uVar4;
  int unaff_EBP;
  float10 in_ST0;
  float10 in_ST1;
  
  if (*(char *)(in_EDX + 0xe) == '\x05') {
    uVar4 = (undefined2)
            CONCAT31((uint3)((byte)((ushort)*(undefined2 *)(unaff_EBP + -0xa4) >> 8) & 0xfe | 2),
                     0x3f);
  }
  else {
    uVar4 = 0x133f;
  }
  *(undefined2 *)(unaff_EBP + -0xa2) = uVar4;
  fVar1 = (float10)0;
  *(int *)(unaff_EBP + -0x94) = in_EDX;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST0) << 8 | (ushort)(in_ST0 < fVar1) << 9 | (ushort)(in_ST0 != fVar1) << 10 |
       (ushort)(in_ST0 == fVar1) << 0xe;
  *(undefined1 *)(unaff_EBP + -0x90) = 0;
  fVar1 = (float10)0;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)NAN(in_ST1) << 8 | (ushort)(in_ST1 < fVar1) << 9 | (ushort)(in_ST1 != fVar1) << 10 |
       (ushort)(in_ST1 == fVar1) << 0xe;
  bVar3 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
  cVar2 = (char)(*(char *)(unaff_EBP + -0x9f) << 1) >> 1;
                    /* WARNING: Could not recover jumptable at 0x0047f461. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(in_EDX + (char)((&DAT_004a881d)[(byte)(cVar2 << 1 | cVar2 < '\0') & 0xf] |
                              (&DAT_004a881d)[(byte)((bVar3 & 7) << 1 | (char)bVar3 < '\0')] << 2) +
              0x10))();
  return;
}
```

---

---

## FUN_0047f468 — 0x47f468

- Classification : internal
- Corps : `0x47f468–0x47f46c`
- État : pseudocode obtenu
- Evidence : `ev_b14756e4f16a1fc2b844dc4a0dbe3b7d58f5db15a27d35c56b63d40d940b4f98`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047f468(void)

{
  return;
}
```

---

---

## FUN_0047f476 — 0x47f476

- Classification : internal
- Corps : `0x47f476–0x47f47a`
- État : pseudocode obtenu
- Evidence : `ev_fd22a6bd17ee99ae27bc19a45980fe73a963c8ec92b376d08b5343a65dd36762`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_0047f476(void)

{
  return (float10)0;
}
```

---

---

## FUN_0047f540 — 0x47f540

- Classification : internal
- Corps : `0x47f540–0x47f556`
- État : pseudocode obtenu
- Evidence : `ev_2c0b93748c29e71d16581d0dd8213d1e91d5d124362a3ff60e74155d2621d87e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_0047f540(void)

{
  float10 in_ST0;
  
  FUN_00485220();
  return (float10)(double)in_ST0;
}
```

---

## __startOneArgErrorHandling — 0x47f557

- Classification : internal
- Corps : `0x47f557–0x47f592`
- État : pseudocode obtenu
- Evidence : `ev_3c4f47b9d3000109f93374ad2cde4827ef87757eb1f9af372402dd8492ec5e41`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x485220` — `FUN_00485220`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __startOneArgErrorHandling
   
   Library: Visual Studio */

float10 __startOneArgErrorHandling(void)

{
  float10 in_ST0;
  
  FUN_00485220();
  return (float10)(double)in_ST0;
}
```

---

---

## FUN_0047f5b5 — 0x47f5b5

- Classification : internal
- Corps : `0x47f5b5–0x47f5cb`
- État : pseudocode obtenu
- Evidence : `ev_5fc009e3c960b69b536653d70c604f92eba91edc6b6792147769c35edeb1b4d1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047f5b5(void)

{
  return;
}
```

---

---

## FUN_0047f5cc — 0x47f5cc

- Classification : internal
- Corps : `0x47f5cc–0x47f5e4`
- État : pseudocode obtenu
- Evidence : `ev_05d06287b5ee79d918d29f40504f65d5e4cfdd3f2662fc6c363e9fe90806702b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047f5cc(void)

{
  uint in_EAX;
  
  if ((in_EAX & 0x80000) != 0) {
    return 7;
  }
  return 1;
}
```

---

## __fload_withFB — 0x47f5e5

- Classification : internal
- Corps : `0x47f5e5–0x47f627`
- État : pseudocode obtenu
- Evidence : `ev_36233ad168267309b0372e11a31ed472d6957ee821e49169ace706dabc9ba876`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __fload_withFB
   
   Library: Visual Studio */

uint __fload_withFB(void)

{
  uint uVar1;
  int in_EDX;
  
  uVar1 = *(uint *)(in_EDX + 4) & 0x7ff00000;
  if (uVar1 != 0x7ff00000) {
    return uVar1;
  }
  return *(uint *)(in_EDX + 4);
}
```

---

---

## FUN_0047f628 — 0x47f628

- Classification : internal
- Corps : `0x47f628–0x47f63d`
- État : pseudocode obtenu
- Evidence : `ev_e9cc48933a41045022af0e15aed31461d7028c8cbfc8596e21f39c47057f70f0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_0047f628(undefined4 param_1,uint param_2)

{
  if ((param_2 & 0x7ff00000) != 0x7ff00000) {
    return param_2 & 0x7ff00000;
  }
  return param_2;
}
```

---

---

## FUN_0047f63e — 0x47f63e

- Classification : internal
- Corps : `0x47f63e–0x47f64a`
- État : pseudocode obtenu
- Evidence : `ev_c4cb090131be91a557460ee8f7e2eb9d5eb553da81a01ec520dc7d4dce2732c0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047f63e(void)

{
  return;
}
```

---

## __math_exit — 0x47f64b

- Classification : internal
- Corps : `0x47f64b–0x47f674`
- État : pseudocode obtenu
- Evidence : `ev_d7c002d37ff22e842c7494e663721a71ee33051b82447f8fbde9bcda1e4da128`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f557` — `__startOneArgErrorHandling`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __math_exit
   
   Library: Visual Studio */

void __math_exit(void)

{
  ushort in_FPUStatusWord;
  ushort unaff_retaddr;
  
  if (((unaff_retaddr != 0x27f) && ((unaff_retaddr & 0x20) != 0)) &&
     ((in_FPUStatusWord & 0x20) != 0)) {
    __startOneArgErrorHandling();
    return;
  }
  return;
}
```

---

---

## FUN_0047f730 — 0x47f730

- Classification : internal
- Corps : `0x47f730–0x47f7f7`
- État : pseudocode obtenu
- Evidence : `ev_69be632faabd26278117e3e6b13875203fa08cb59a8a31187d6038ffbcb87113`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482d70` — `FUN_00482d70`
- `0x4853a0` — `FUN_004853a0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined * FUN_0047f730(int param_1)

{
  undefined *puVar1;
  int iVar2;
  uint local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  undefined1 local_14 [12];
  uint local_8;
  
  local_24 = 0;
  local_8 = FUN_004853a0(local_14,&local_18,param_1,0,0,0,0);
  if ((local_8 & 4) == 0) {
    iVar2 = FUN_00482d70(local_14,&local_20);
    if (((local_8 & 2) != 0) || (iVar2 == 1)) {
      local_24 = 0x80;
    }
    if (((local_8 & 1) != 0) || (iVar2 == 2)) {
      local_24 = local_24 | 0x100;
    }
  }
  else {
    local_24 = 0x200;
    local_20 = 0;
    local_1c = 0;
  }
  *(uint *)PTR_DAT_004a8830 = local_24;
  *(int *)(PTR_DAT_004a8830 + 4) = local_18 - param_1;
  puVar1 = PTR_DAT_004a8830;
  *(undefined4 *)(PTR_DAT_004a8830 + 0x10) = local_20;
  *(undefined4 *)(puVar1 + 0x14) = local_1c;
  return PTR_DAT_004a8830;
}
```

---

## __allmul — 0x47f800

- Classification : internal
- Corps : `0x47f800–0x47f833`
- État : pseudocode obtenu
- Evidence : `ev_7cd3dfead16ccba0e6142589c95ba8c5a145cddc65e4827db37ea35df86eb060`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __allmul
   
   Library: Visual Studio */

longlong __allmul(uint param_1,int param_2,uint param_3,int param_4)

{
  if (param_4 == 0 && param_2 == 0) {
    return (ulonglong)param_1 * (ulonglong)param_3;
  }
  return CONCAT44((int)((ulonglong)param_1 * (ulonglong)param_3 >> 0x20) +
                  param_2 * param_3 + param_1 * param_4,
                  (int)((ulonglong)param_1 * (ulonglong)param_3));
}
```

---

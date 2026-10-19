# 0022_batch_0018 — détails (2/3)

## FUN_00486d30 — 0x486d30

- Classification : internal
- Corps : `0x486d30–0x486d62`
- État : pseudocode obtenu
- Evidence : `ev_81672f0bc3448033a26ee78fba0227deb35bc79f8495f4e323870201104ef8bd`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x486cc0` — `FUN_00486cc0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00486d30(undefined4 param_1,uint param_2,int param_3)

{
  FUN_00486cc0(param_1,param_2,(short)((int)(param_2 >> 0x10 & 0x7ff0) >> 4) + -0x3fe + param_3);
  return;
}
```

---

---

## FUN_00486d70 — 0x486d70

- Classification : internal
- Corps : `0x486d70–0x486da3`
- État : pseudocode obtenu
- Evidence : `ev_dbd7f4f240337098aa5f747fac0c17e2632bb466ba2671802259a055d2fb6a70`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_00486d70(undefined4 param_1,undefined4 param_2,short param_3)

{
  return (float10)(double)CONCAT26(param_2._2_2_ & 0x800f | param_3 << 4,
                                   CONCAT24((undefined2)param_2,param_1));
}
```

---

---

## FUN_00486db0 — 0x486db0

- Classification : internal
- Corps : `0x486db0–0x486e2b`
- État : pseudocode obtenu
- Evidence : `ev_75cd8da979fe29965043e20804df0c63e70f2236d3cb55ccd5180b3730fc5c1b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00486db0(int param_1,uint param_2)

{
  undefined4 uVar1;
  
  if ((param_2 == 0x7ff00000) && (param_1 == 0)) {
    uVar1 = 1;
  }
  else if ((param_2 == 0xfff00000) && (param_1 == 0)) {
    uVar1 = 2;
  }
  else if ((param_2._2_2_ & 0x7ff8) == 0x7ff8) {
    uVar1 = 3;
  }
  else if (((param_2._2_2_ & 0x7ff8) == 0x7ff0) && (((param_2 & 0x7ffff) != 0 || (param_1 != 0)))) {
    uVar1 = 4;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
```

---

---

## FUN_00486e30 — 0x486e30

- Classification : internal
- Corps : `0x486e30–0x486f68`
- État : pseudocode obtenu
- Evidence : `ev_381d98a7604ad3b8b39f73cca4d385b513f20d738beef2f95bd52254e9a39365`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x486cc0` — `FUN_00486cc0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_00486e30(uint param_1,uint param_2,int *param_3)

{
  double dVar1;
  int iVar2;
  float10 fVar3;
  double local_10;
  int local_8;
  
  if ((double)CONCAT26(param_2._2_2_,CONCAT24((ushort)param_2,param_1)) == 0.0) {
    local_10 = 0.0;
    local_8 = 0;
  }
  else if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    local_8 = -0x3fd;
    dVar1 = (double)CONCAT26(param_2._2_2_,CONCAT24((ushort)param_2,param_1));
    while ((param_2._2_2_ & 0x10) == 0) {
      iVar2 = CONCAT22(param_2._2_2_,(ushort)param_2) << 1;
      param_2._0_2_ = (ushort)iVar2;
      param_2._2_2_ = (ushort)((uint)iVar2 >> 0x10);
      if ((param_1 & 0x80000000) != 0) {
        param_2._0_2_ = (ushort)param_2 | 1;
      }
      param_1 = param_1 << 1;
      local_8 = local_8 + -1;
    }
    param_2._2_2_ = param_2._2_2_ & 0xffef;
    if (dVar1 < 0.0) {
      param_2._2_2_ = param_2._2_2_ | 0x8000;
    }
    fVar3 = (float10)FUN_00486cc0(param_1,CONCAT22(param_2._2_2_,(ushort)param_2),0);
    local_10 = (double)fVar3;
  }
  else {
    fVar3 = (float10)FUN_00486cc0(param_1,param_2,0);
    local_10 = (double)fVar3;
    local_8 = (short)((int)(param_2._2_2_ & 0x7ff0) >> 4) + -0x3fe;
  }
  *param_3 = local_8;
  return (float10)local_10;
}
```

---

---

## FUN_00486f70 — 0x486f70

- Classification : internal
- Corps : `0x486f70–0x486f8a`
- État : pseudocode obtenu
- Evidence : `ev_224eb09fa94b248bb8b12a85497f08500de1cbf57282643e5b0286397ac58373`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_00486f70(double param_1)

{
  return (float10)ROUND(param_1);
}
```

---

## __copysign — 0x486f90

- Classification : internal
- Corps : `0x486f90–0x486fb9`
- État : pseudocode obtenu
- Evidence : `ev_8b55f184f8ddaab9e1d6680985229c3b84898863abb58ed484dcbe83f2dfc828`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __copysign
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

double __cdecl __copysign(double _Number,double _Sign)

{
  return (double)CONCAT44(_Number._4_4_ & 0x7fffffff | _Sign._4_4_ & 0x80000000,_Number._0_4_);
}
```

---

## __chgsign — 0x486fc0

- Classification : internal
- Corps : `0x486fc0–0x486feb`
- État : pseudocode obtenu
- Evidence : `ev_3595cfe1ba2b9ddc8688397fff7a43f4c227667b687d52393e8c23448489eaa3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __chgsign
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

double __cdecl __chgsign(double _X)

{
  return (double)CONCAT44(_X._4_4_ & 0x7fffffff | ~_X._4_4_ & 0x80000000,_X._0_4_);
}
```

---

---

## FUN_00486ff0 — 0x486ff0

- Classification : internal
- Corps : `0x486ff0–0x487008`
- État : pseudocode obtenu
- Evidence : `ev_691073325fe17003a959d4da94d76ccb9828350c58ced30db0f8232772f82661`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x489b90` — `FUN_00489b90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00486ff0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_00489b90(param_1,param_2,param_3);
  return;
}
```

---

---

## FUN_00487010 — 0x487010

- Classification : internal
- Corps : `0x487010–0x48713b`
- État : pseudocode obtenu
- Evidence : `ev_02838f8a177eee589f996a8b9c5b0cfe8f188b4a0c92837be7c07327d1f32e3d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x486db0` — `FUN_00486db0`
- `0x486e30` — `FUN_00486e30`
- `0x488910` — `FUN_00488910`
- `0x4889e0` — `FUN_004889e0`
- `0x4895b0` — `FUN_004895b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 FUN_00487010(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  float10 fVar2;
  int local_c;
  undefined4 local_8;
  
  local_8 = FUN_004895b0();
  if ((param_2._2_2_ & 0x7ff0) != 0x7ff0) {
    if ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) == 0.0) {
      fVar2 = (float10)FUN_004889e0(4,0x25,param_1,param_2,-_DAT_004a8ed0,local_8);
      return fVar2;
    }
    FUN_00486e30(param_1,param_2,&local_c);
    FUN_004895b0();
    return (float10)(local_c + -1);
  }
  iVar1 = FUN_00486db0();
  if (0 < iVar1) {
    if (iVar1 < 3) {
      FUN_004895b0();
      return (float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
    }
    if (iVar1 == 3) {
      fVar2 = (float10)FUN_00488910(0x25,param_1,param_2,local_8);
      return fVar2;
    }
  }
  fVar2 = (float10)FUN_004889e0(8,0x25,param_1,param_2,
                                (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)
                                                ) + 1.0,local_8);
  return fVar2;
}
```

---

---

## FUN_00487140 — 0x487140

- Classification : internal
- Corps : `0x487140–0x487479`
- État : pseudocode obtenu
- Evidence : `ev_313686076575a8c4b68260efed9120494a9b253ca2c2319ee0146e9356b56d61`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x486cc0` — `FUN_00486cc0`
- `0x486e30` — `FUN_00486e30`
- `0x488970` — `FUN_00488970`
- `0x488aa0` — `FUN_00488aa0`
- `0x4895b0` — `FUN_004895b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_00487140(int param_1,uint param_2,int param_3,uint param_4)

{
  double dVar1;
  undefined4 unaff_EBP;
  float10 fVar2;
  int local_20;
  double local_1c;
  int local_14;
  undefined4 local_10;
  int local_c;
  undefined4 uStack_8;
  undefined2 uStack_4;
  undefined2 uStack_2;
  
  uStack_4 = (undefined2)unaff_EBP;
  uStack_2 = (undefined2)((uint)unaff_EBP >> 0x10);
  local_10 = FUN_004895b0();
  if (((param_2._2_2_ & 0x7ff0) == 0x7ff0) || ((param_4._2_2_ & 0x7ff0) == 0x7ff0)) {
    if ((((param_2._2_2_ & 0x7ff8) == 0x7ff0) && (((param_2 & 0x7ffff) != 0 || (param_1 != 0)))) ||
       (((param_4._2_2_ & 0x7ff8) == 0x7ff0 && (((param_4 & 0x7ffff) != 0 || (param_3 != 0)))))) {
      fVar2 = (float10)FUN_00488aa0(8,0x26,param_1,param_2,param_3,param_4,
                                    (double)CONCAT26(param_2._2_2_,
                                                     CONCAT24((undefined2)param_2,param_1)) +
                                    (double)CONCAT26(param_4._2_2_,
                                                     CONCAT24((undefined2)param_4,param_3)),local_10
                                   );
      return fVar2;
    }
    if (((param_2._2_2_ & 0x7ff8) == 0x7ff8) || ((param_4._2_2_ & 0x7ff8) == 0x7ff8)) {
      fVar2 = (float10)FUN_00488970(0x26,param_1,param_2,param_3,param_4,local_10);
      return fVar2;
    }
  }
  if ((double)CONCAT26(param_4._2_2_,CONCAT24((undefined2)param_4,param_3)) ==
      (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1))) {
    FUN_004895b0();
    fVar2 = (float10)(double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1));
  }
  else {
    if ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) == 0.0) {
      local_c = 1;
      if ((double)CONCAT26(param_4._2_2_,CONCAT24((undefined2)param_4,param_3)) <=
          (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1))) {
        uStack_8._0_2_ = 0;
        uStack_8._2_2_ = 0x8000;
      }
      else {
        uStack_8._0_2_ = 0;
        uStack_8._2_2_ = 0;
      }
    }
    if (((0.0 < (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1))) &&
        ((double)CONCAT26(param_4._2_2_,CONCAT24((undefined2)param_4,param_3)) <
         (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)))) ||
       (((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) < 0.0 &&
        ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) <
         (double)CONCAT26(param_4._2_2_,CONCAT24((undefined2)param_4,param_3)))))) {
      local_c = param_1 + -1;
      uStack_8 = param_2;
      if (param_1 == 0) {
        uStack_8 = param_2 - 1;
      }
    }
    else if ((((0.0 < (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1))) &&
              ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) <
               (double)CONCAT26(param_4._2_2_,CONCAT24((undefined2)param_4,param_3)))) ||
             ((uStack_8 = CONCAT22(uStack_8._2_2_,(undefined2)uStack_8),
              (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) < 0.0 &&
              (uStack_8 = CONCAT22(uStack_8._2_2_,(undefined2)uStack_8),
              (double)CONCAT26(param_4._2_2_,CONCAT24((undefined2)param_4,param_3)) <
              (double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)))))) &&
            (local_c = param_1 + 1, uStack_8 = param_2, local_c == 0)) {
      uStack_8 = param_2 + 1;
    }
    if (((uStack_8 & 0x7ff00000) == 0) && (((uStack_8 & 0xfffff) != 0 || (local_c != 0)))) {
      fVar2 = (float10)FUN_00486e30(local_c,uStack_8,&local_14);
      local_1c = (double)fVar2;
      fVar2 = (float10)FUN_00486cc0(local_1c,local_14 + 0x600);
      dVar1 = (double)fVar2;
      local_c = SUB84(dVar1,0);
      uStack_8._0_2_ = (undefined2)((ulonglong)dVar1 >> 0x20);
      uStack_8._2_2_ = (undefined2)((ulonglong)dVar1 >> 0x30);
      fVar2 = (float10)FUN_00488aa0(0x12,0x26,param_1,param_2,param_3,param_4,dVar1,local_10);
    }
    else if (((uStack_8 == 0x7ff00000) && (local_c == 0)) ||
            ((uStack_8 == 0xfff00000 && (local_c == 0)))) {
      fVar2 = (float10)FUN_00486e30(local_c,uStack_8,&local_20);
      fVar2 = (float10)FUN_00486cc0((double)fVar2,local_20 + -0x600);
      dVar1 = (double)fVar2;
      local_c = SUB84(dVar1,0);
      uStack_8._0_2_ = (undefined2)((ulonglong)dVar1 >> 0x20);
      uStack_8._2_2_ = (undefined2)((ulonglong)dVar1 >> 0x30);
      fVar2 = (float10)FUN_00488aa0(0x11,0x26,param_1,param_2,param_3,param_4,dVar1,local_10);
    }
    else {
      FUN_004895b0();
      fVar2 = (float10)(double)CONCAT26(uStack_8._2_2_,CONCAT24((undefined2)uStack_8,local_c));
    }
  }
  return fVar2;
}
```

---

---

## FUN_00487480 — 0x487480

- Classification : internal
- Corps : `0x487480–0x4874a1`
- État : pseudocode obtenu
- Evidence : `ev_1b26e1a8a6ea21b041e6510e38cbbfa0363db267b463e7f3b007dc4b8e655b6d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_00487480(undefined4 param_1,undefined8 param_2)

{
  return (param_2._2_4_ & 0x7ff0) != 0x7ff0;
}
```

---

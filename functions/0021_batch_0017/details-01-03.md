# 0021_batch_0017 — détails (3/3)

## FUN_0047f99e — 0x47f99e

- Classification : internal
- Corps : `0x47f99e–0x47f9e0`
- État : pseudocode obtenu
- Evidence : `ev_ed4f620baefe87593388856e8a4dac3c46a2201640a2fa6bb755c69a4276dfcc`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined5 FUN_0047f99e(void)

{
  undefined4 uVar1;
  undefined4 in_EAX;
  undefined1 extraout_DL;
  undefined1 in_DL;
  int unaff_EBP;
  float10 in_ST0;
  float10 fVar2;
  float10 fVar3;
  undefined4 unaff_retaddr;
  
  fVar2 = ABS(in_ST0);
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)(_DAT_004a885e < fVar2) << 8 | (ushort)(NAN(_DAT_004a885e) || NAN(fVar2)) << 10 |
       (ushort)(_DAT_004a885e == fVar2) << 0xe;
  if ((*(byte *)(unaff_EBP + -0x9f) & 0x41) == 0) {
    fVar3 = ROUND(in_ST0);
    fVar2 = (float10)0;
    *(ushort *)(unaff_EBP + -0xa0) =
         (ushort)(fVar3 < fVar2) << 8 | (ushort)(NAN(fVar3) || NAN(fVar2)) << 10 |
         (ushort)(fVar3 == fVar2) << 0xe;
    fVar3 = in_ST0 - fVar3;
    fVar2 = (float10)0;
    *(ushort *)(unaff_EBP + -0xa0) =
         (ushort)(fVar3 < fVar2) << 8 | (ushort)(NAN(fVar3) || NAN(fVar2)) << 10 |
         (ushort)(fVar3 == fVar2) << 0xe;
    f2xm1(ABS(fVar3));
    return CONCAT14(*(undefined1 *)(unaff_EBP + -0x9f),in_EAX);
  }
  fVar2 = (float10)0;
  *(ushort *)(unaff_EBP + -0xa0) =
       (ushort)(in_ST0 < fVar2) << 8 | (ushort)(NAN(in_ST0) || NAN(fVar2)) << 10 |
       (ushort)(in_ST0 == fVar2) << 0xe;
  if ((*(byte *)(unaff_EBP + -0x9f) & 1) == 0) {
    return CONCAT14(in_DL,unaff_retaddr);
  }
  *(undefined1 *)(unaff_EBP + -0x90) = 4;
  uVar1 = FUN_0047f476();
  return CONCAT14(extraout_DL,uVar1);
}
```

---

---

## FUN_0047fa50 — 0x47fa50

- Classification : internal
- Corps : `0x47fa50–0x47fcb3`
- État : pseudocode obtenu
- Evidence : `ev_ca7d300667088ba2257548d702f817c2b4709b2e8eda449bb03c362e1611e7f9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47fcc0` — `FUN_0047fcc0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047fa50(int param_1,int param_2,int param_3,int param_4,undefined4 *param_5)

{
  int iVar1;
  undefined4 local_2c;
  undefined4 local_28;
  undefined8 local_24;
  undefined8 local_1c;
  undefined4 local_10;
  
  local_10 = 0;
  if (0.0 <= (double)CONCAT44(param_2,param_1)) {
    local_1c = (double)CONCAT44(param_2,param_1);
  }
  else {
    local_1c = -(double)CONCAT44(param_2,param_1);
  }
  if ((param_4 == 0x7ff00000) && (param_3 == 0)) {
    if (local_1c <= 1.0) {
      if (1.0 <= local_1c) {
        *param_5 = DAT_004a8ed8;
        param_5[1] = DAT_004a8edc;
        local_10 = 1;
      }
      else {
        *param_5 = 0;
        param_5[1] = 0;
      }
    }
    else {
      *param_5 = DAT_004a8ed0;
      param_5[1] = DAT_004a8ed4;
    }
  }
  else if ((param_4 == -0x100000) && (param_3 == 0)) {
    if (local_1c <= 1.0) {
      if (1.0 <= local_1c) {
        *param_5 = DAT_004a8ed8;
        param_5[1] = DAT_004a8edc;
        local_10 = 1;
      }
      else {
        *param_5 = DAT_004a8ed0;
        param_5[1] = DAT_004a8ed4;
      }
    }
    else {
      *param_5 = 0;
      param_5[1] = 0;
    }
  }
  else if ((param_2 == 0x7ff00000) && (param_1 == 0)) {
    if ((double)CONCAT44(param_4,param_3) <= 0.0) {
      if (0.0 <= (double)CONCAT44(param_4,param_3)) {
        *param_5 = 0;
        param_5[1] = 0x3ff00000;
      }
      else {
        *param_5 = 0;
        param_5[1] = 0;
      }
    }
    else {
      *param_5 = DAT_004a8ed0;
      param_5[1] = DAT_004a8ed4;
    }
  }
  else if ((param_2 == -0x100000) && (param_1 == 0)) {
    iVar1 = FUN_0047fcc0(param_3,param_4);
    if ((double)CONCAT44(param_4,param_3) <= 0.0) {
      if (0.0 <= (double)CONCAT44(param_4,param_3)) {
        *param_5 = 0;
        param_5[1] = 0x3ff00000;
      }
      else {
        if (iVar1 == 1) {
          local_2c = DAT_004a8ef0;
          local_28 = DAT_004a8ef4;
        }
        else {
          local_2c = 0;
          local_28 = 0;
        }
        *param_5 = local_2c;
        param_5[1] = local_28;
      }
    }
    else {
      if (iVar1 == 1) {
        local_24 = -(double)CONCAT44(DAT_004a8ed4,DAT_004a8ed0);
      }
      else {
        local_24 = (double)CONCAT44(DAT_004a8ed4,DAT_004a8ed0);
      }
      *param_5 = (undefined4)local_24;
      param_5[1] = local_24._4_4_;
    }
  }
  return local_10;
}
```

---

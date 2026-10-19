# 0022_batch_0018 — détails (3/5)

## FUN_004853a0 — 0x4853a0

- Classification : internal
- Corps : `0x4853a0–0x485db9`
- État : pseudocode obtenu
- Evidence : `ev_82fb11513922ea3b00014ca07cc8a933e26fbb8cbda976b2256f446bd3f99225`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`
- `0x488200` — `FUN_00488200`
- `0x489ac0` — `FUN_00489ac0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_004853a0(undefined2 *param_1,undefined4 *param_2,byte *param_3,undefined4 param_4,
                 int param_5,int param_6,int param_7)

{
  byte bVar1;
  bool bVar2;
  byte *pbVar3;
  uint local_b4;
  uint local_b0;
  uint local_a4;
  uint local_9c;
  uint local_94;
  int local_80;
  int local_78;
  uint local_74;
  int local_70;
  char *local_6c;
  byte *local_68;
  undefined2 local_64;
  undefined4 local_62;
  undefined4 local_5e;
  ushort local_5a;
  int local_58;
  ushort local_54;
  int local_50;
  undefined2 local_4c;
  uint local_48;
  int local_44;
  uint local_40;
  char local_3c [23];
  char local_25;
  undefined4 local_20;
  int local_1c;
  int local_18;
  undefined4 local_14;
  int local_10;
  undefined4 local_c;
  byte *local_8;
  
  local_6c = local_3c;
  local_20 = local_20 & 0xffff0000;
  local_78 = 1;
  local_74 = 0;
  local_58 = 0;
  local_10 = 0;
  local_1c = 0;
  local_44 = 0;
  bVar2 = false;
  local_18 = 0;
  local_70 = 0;
  local_48 = 0;
  local_50 = 0;
  local_68 = param_3;
  for (local_8 = param_3;
      (((*local_8 == 0x20 || (*local_8 == 9)) || (*local_8 == 10)) || (*local_8 == 0xd));
      local_8 = local_8 + 1) {
  }
  do {
    if (local_50 == 10) {
      *param_2 = local_8;
      if ((local_58 != 0) && (local_44 == 0)) {
        if (0x18 < local_74) {
          if ('\x04' < local_25) {
            local_25 = local_25 + '\x01';
          }
          local_74 = 0x18;
          local_6c = local_6c + -1;
          local_70 = local_70 + 1;
        }
        if (local_74 == 0) {
          local_4c = 0;
          local_54 = 0;
          local_14 = 0;
          local_c = 0;
        }
        else {
          while (local_6c = local_6c + -1, *local_6c == '\0') {
            local_74 = local_74 - 1;
            local_70 = local_70 + 1;
          }
          FUN_00488200(local_3c,local_74,&local_64);
          if (local_78 < 0) {
            local_18 = -local_18;
          }
          local_18 = local_18 + local_70;
          if (local_1c == 0) {
            local_18 = local_18 + param_5;
          }
          if (local_10 == 0) {
            local_18 = local_18 - param_6;
          }
          if (local_18 < 0x1451) {
            if (local_18 < -0x1450) {
              bVar2 = true;
            }
            else {
              FUN_00489ac0(&local_64,local_18,param_4);
              local_4c = local_64;
              local_c = local_62;
              local_14 = local_5e;
              local_54 = local_5a;
            }
          }
          else {
            local_44 = 1;
          }
        }
      }
      if (local_58 == 0) {
        local_4c = 0;
        local_54 = 0;
        local_14 = 0;
        local_c = 0;
        local_48 = local_48 | 4;
      }
      else if (local_44 == 0) {
        if (bVar2) {
          local_4c = 0;
          local_54 = 0;
          local_14 = 0;
          local_c = 0;
          local_48 = local_48 | 1;
        }
      }
      else {
        local_54 = 0x7fff;
        local_14 = 0x80000000;
        local_c = 0;
        local_4c = 0;
        local_48 = local_48 | 2;
      }
      *param_1 = local_4c;
      *(undefined4 *)(param_1 + 1) = local_c;
      *(undefined4 *)(param_1 + 3) = local_14;
      param_1[5] = local_54 | (ushort)local_20;
      return local_48;
    }
    bVar1 = *local_8;
    local_40 = CONCAT31(local_40._1_3_,bVar1);
    pbVar3 = local_8 + 1;
    switch(local_50) {
    case 0:
      if (((char)bVar1 < '1') || ('9' < (char)bVar1)) {
        if (bVar1 == DAT_004a87f8) {
          local_50 = 5;
        }
        else if (bVar1 == 0x2b) {
          local_50 = 2;
          local_20 = (uint)local_20._2_2_ << 0x10;
        }
        else if (bVar1 == 0x2d) {
          local_50 = 2;
          local_20 = CONCAT22(local_20._2_2_,0x8000);
        }
        else if (bVar1 == 0x30) {
          local_50 = 1;
        }
        else {
          local_50 = 10;
          pbVar3 = local_8;
        }
      }
      else {
        local_50 = 3;
        pbVar3 = local_8;
      }
      break;
    case 1:
      local_58 = 1;
      if (((char)bVar1 < '1') || ('9' < (char)bVar1)) {
        if (bVar1 == DAT_004a87f8) {
          local_50 = 4;
        }
        else {
          switch(bVar1) {
          case 0x2b:
          case 0x2d:
            local_50 = 0xb;
            pbVar3 = local_8;
            break;
          default:
            local_50 = 10;
            pbVar3 = local_8;
            break;
          case 0x30:
            local_50 = 1;
            break;
          case 0x44:
          case 0x45:
          case 100:
          case 0x65:
            local_50 = 6;
          }
        }
      }
      else {
        local_50 = 3;
        pbVar3 = local_8;
      }
      break;
    case 2:
      if (((char)bVar1 < '1') || ('9' < (char)bVar1)) {
        if (bVar1 == DAT_004a87f8) {
          local_50 = 5;
        }
        else if (bVar1 == 0x30) {
          local_50 = 1;
        }
        else {
          local_50 = 10;
          local_8 = local_68;
          pbVar3 = local_8;
        }
      }
      else {
        local_50 = 3;
        pbVar3 = local_8;
      }
      break;
    case 3:
      local_58 = 1;
      local_8 = pbVar3;
      while( true ) {
        if (DAT_004a87f4 < 2) {
          local_94 = *(ushort *)(PTR_DAT_004a85e8 + (local_40 & 0xff) * 2) & 4;
        }
        else {
          local_94 = FUN_0047f2b0(local_40 & 0xff,4);
        }
        if (local_94 == 0) break;
        if (local_74 < 0x19) {
          local_74 = local_74 + 1;
          *local_6c = (char)local_40 + -0x30;
          local_6c = local_6c + 1;
        }
        else {
          local_70 = local_70 + 1;
        }
        local_40 = CONCAT31(local_40._1_3_,*local_8);
        local_8 = local_8 + 1;
      }
      pbVar3 = local_8;
      if ((char)local_40 == DAT_004a87f8) {
        local_50 = 4;
      }
      else {
        switch((char)local_40) {
        case '+':
        case '-':
          local_50 = 0xb;
          pbVar3 = local_8 + -1;
          break;
        default:
          local_50 = 10;
          pbVar3 = local_8 + -1;
          break;
        case 'D':
        case 'E':
        case 'd':
        case 'e':
          local_50 = 6;
        }
      }
      break;
    case 4:
      local_58 = 1;
      local_10 = 1;
      local_8 = pbVar3;
      if (local_74 == 0) {
        while ((char)local_40 == '0') {
          local_70 = local_70 + -1;
          local_40 = CONCAT31(local_40._1_3_,*local_8);
          local_8 = local_8 + 1;
        }
      }
      while( true ) {
        if (DAT_004a87f4 < 2) {
          local_9c = *(ushort *)(PTR_DAT_004a85e8 + (local_40 & 0xff) * 2) & 4;
        }
        else {
          local_9c = FUN_0047f2b0(local_40 & 0xff,4);
        }
        if (local_9c == 0) break;
        if (local_74 < 0x19) {
          local_74 = local_74 + 1;
          *local_6c = (char)local_40 + -0x30;
          local_6c = local_6c + 1;
          local_70 = local_70 + -1;
        }
        local_40 = CONCAT31(local_40._1_3_,*local_8);
        local_8 = local_8 + 1;
      }
      switch((char)local_40) {
      case '+':
      case '-':
        local_50 = 0xb;
        pbVar3 = local_8 + -1;
        break;
      default:
        local_50 = 10;
        pbVar3 = local_8 + -1;
        break;
      case 'D':
      case 'E':
      case 'd':
      case 'e':
        local_50 = 6;
        pbVar3 = local_8;
      }
      break;
    case 5:
      local_10 = 1;
      if (DAT_004a87f4 < 2) {
        local_a4 = *(ushort *)(PTR_DAT_004a85e8 + (uint)bVar1 * 2) & 4;
        local_8 = pbVar3;
      }
      else {
        local_8 = pbVar3;
        local_a4 = FUN_0047f2b0(bVar1,4);
      }
      if (local_a4 == 0) {
        local_50 = 10;
        local_8 = local_68;
        pbVar3 = local_8;
      }
      else {
        local_50 = 4;
        pbVar3 = local_8 + -1;
      }
      break;
    case 6:
      local_68 = local_8 + -1;
      if (((char)bVar1 < '1') || ('9' < (char)bVar1)) {
        if (bVar1 == 0x2b) {
          local_50 = 7;
        }
        else if (bVar1 == 0x2d) {
          local_50 = 7;
          local_78 = -1;
        }
        else if (bVar1 == 0x30) {
          local_50 = 8;
        }
        else {
          local_50 = 10;
          pbVar3 = local_68;
        }
      }
      else {
        local_50 = 9;
        pbVar3 = local_8;
      }
      break;
    case 7:
      if (((char)bVar1 < '1') || ('9' < (char)bVar1)) {
        if (bVar1 == 0x30) {
          local_50 = 8;
        }
        else {
          local_50 = 10;
          local_8 = local_68;
          pbVar3 = local_8;
        }
      }
      else {
        local_50 = 9;
        pbVar3 = local_8;
      }
      break;
    case 8:
      local_1c = 1;
      local_8 = pbVar3;
      while ((char)local_40 == '0') {
        bVar1 = *local_8;
        local_8 = local_8 + 1;
        local_40 = CONCAT31(local_40._1_3_,bVar1);
      }
      if (((char)local_40 < '1') || ('9' < (char)local_40)) {
        local_50 = 10;
      }
      else {
        local_50 = 9;
      }
      local_8 = local_8 + -1;
      pbVar3 = local_8;
      break;
    case 9:
      local_1c = 1;
      local_80 = 0;
      local_8 = pbVar3;
      while( true ) {
        if (DAT_004a87f4 < 2) {
          local_b0 = *(ushort *)(PTR_DAT_004a85e8 + (local_40 & 0xff) * 2) & 4;
        }
        else {
          local_b0 = FUN_0047f2b0(local_40 & 0xff,4);
        }
        if (local_b0 == 0) goto LAB_00485ac7;
        local_80 = local_80 * 10 + -0x30 + (int)(char)local_40;
        if (0x1450 < local_80) break;
        local_40 = CONCAT31(local_40._1_3_,*local_8);
        local_8 = local_8 + 1;
      }
      local_80 = 0x1451;
LAB_00485ac7:
      local_18 = local_80;
      while( true ) {
        if (DAT_004a87f4 < 2) {
          local_b4 = *(ushort *)(PTR_DAT_004a85e8 + (local_40 & 0xff) * 2) & 4;
        }
        else {
          local_b4 = FUN_0047f2b0(local_40 & 0xff,4);
        }
        if (local_b4 == 0) break;
        local_40 = CONCAT31(local_40._1_3_,*local_8);
        local_8 = local_8 + 1;
      }
      local_50 = 10;
      pbVar3 = local_8 + -1;
      break;
    case 0xb:
      if (param_7 == 0) {
        local_50 = 10;
        pbVar3 = local_8;
      }
      else {
        local_68 = local_8;
        if (bVar1 == 0x2b) {
          local_50 = 7;
        }
        else if (bVar1 == 0x2d) {
          local_50 = 7;
          local_78 = -1;
        }
        else {
          local_50 = 10;
          pbVar3 = local_8;
        }
      }
    }
    local_8 = pbVar3;
  } while( true );
}
```

---

## FUN_00485ee0 — 0x485ee0

- Classification : internal
- Corps : `0x485ee0–0x485f2e`
- État : pseudocode obtenu
- Evidence : `ev_c79702bafa15b3876eef5646d05476619727d51061603eb0c7884a3bb5e25128`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482db0` — `FUN_00482db0`
- `0x4853a0` — `FUN_004853a0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_00485ee0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint local_18;
  undefined1 local_10 [12];
  
  local_18 = FUN_004853a0(local_10,param_2,param_3,param_4,0,0,0);
  iVar1 = FUN_00482db0(local_10,param_1);
  if (iVar1 == 1) {
    local_18 = local_18 | 2;
  }
  return local_18;
}
```

---

## FUN_00485f30 — 0x485f30

- Classification : internal
- Corps : `0x485f30–0x486046`
- État : pseudocode obtenu
- Evidence : `ev_1209ff3ebe6686b718939232b3d6cfd23455342582eedeb0bbe4e639f2afdb2e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_00485f30(int param_1,uint param_2,ushort param_3,undefined4 param_4,uint param_5,
                 uint param_6)

{
  float10 fVar1;
  uint uVar2;
  float10 fVar3;
  
  fVar1 = (float10)CONCAT28(param_3,CONCAT44(param_2,param_1));
  while (!CARRY4(param_2,param_2)) {
    if (param_1 == 0 && param_2 == 0) {
      return 0;
    }
    if ((param_3 & 0x7fff) != 0) {
      return param_3 & 0x7fff;
    }
    uVar2 = param_6 & 0x7fff;
    if (uVar2 == 0) {
      if (CARRY4(param_5,param_5)) {
        return param_5 * 2;
      }
    }
    else if ((uVar2 == 0x7fff) || (uVar2 = param_5 * 2, !CARRY4(param_5,param_5))) {
      return uVar2;
    }
    fVar3 = fVar1 * (float10)_DAT_004a8d88;
    param_1 = SUB104(fVar3,0);
    param_3 = (ushort)((unkuint10)fVar3 >> 0x40);
    param_2 = (uint)((unkuint10)fVar3 >> 0x20);
  }
  uVar2 = param_2 * 2 ^ 0xe000000;
  if ((uVar2 & 0xe000000) != 0) {
    return uVar2;
  }
  uVar2 = (param_2 & 0x7fffffff) >> 0x1b;
  if ((&DAT_004a8d70)[uVar2] != '\0') {
    if (((param_3 & 0x7fff) != 0) && ((param_3 & 0x7fff) != 0x7fff)) {
      if ((param_6 & 0x7fff) != 1) {
        return param_6 & 0x7fff;
      }
      return 1;
    }
    return param_3 & 0x7fff;
  }
  return uVar2;
}
```

---

## FUN_00486721 — 0x486721

- Classification : internal
- Corps : `0x486721–0x486735`
- État : pseudocode obtenu
- Evidence : `ev_1660b34a66e1c7740e877eeaa36ff1a5870359870366f4b5a93a6310f32b4fbf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x485f30` — `FUN_00485f30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00486721(void)

{
  undefined4 in_EAX;
  
  FUN_00485f30();
  return in_EAX;
}
```

---

## FUN_00486cc0 — 0x486cc0

- Classification : internal
- Corps : `0x486cc0–0x486cfd`
- État : pseudocode obtenu
- Evidence : `ev_e59dd3c5fa6cd81a2ade30266bd3bbd0dcbbd571d831cd351461a09dc0346b4f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_00486cc0(undefined4 param_1,undefined4 param_2,short param_3)

{
  return (float10)(double)CONCAT26(param_2._2_2_ & 0x800f | (param_3 + 0x3fe) * 0x10,
                                   CONCAT24((undefined2)param_2,param_1));
}
```

---

## FUN_00486d00 — 0x486d00

- Classification : internal
- Corps : `0x486d00–0x486d2c`
- État : pseudocode obtenu
- Evidence : `ev_71d833bba2381453fad6380ac94c037d19e32ddfa5b17916b6a70d2962b88d49`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00486d00(undefined4 param_1,undefined8 param_2)

{
  short local_8;
  
  local_8 = (short)((int)(param_2._2_4_ & 0x7ff0) >> 4);
  return (int)(short)(local_8 + -0x3fe);
}
```

---

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

## FUN_004874b0 — 0x4874b0

- Classification : internal
- Corps : `0x4874b0–0x4874f8`
- État : pseudocode obtenu
- Evidence : `ev_0fc4d25c9a40d9ea0fb14687d2ceb8a9546c22063e4c3e2ed57bd494b2327af8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004874b0(int param_1,uint param_2)

{
  undefined4 uVar1;
  
  if ((((param_2._2_2_ & 0x7ff8) == 0x7ff0) && (((param_2 & 0x7ffff) != 0 || (param_1 != 0)))) ||
     ((param_2._2_2_ & 0x7ff8) == 0x7ff8)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}
```

---

## FUN_00487500 — 0x487500

- Classification : internal
- Corps : `0x487500–0x4875d2`
- État : pseudocode obtenu
- Evidence : `ev_8ad5e9aca3c8687a5db5898dfc4cfb844751f6f0488320cc5d8e05b9305c789b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x486db0` — `FUN_00486db0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00487500(int param_1,uint param_2)

{
  int iVar1;
  
  if ((param_2._2_2_ & 0x7ff0) == 0x7ff0) {
    iVar1 = FUN_00486db0(param_1,param_2);
    if (iVar1 == 1) {
      iVar1 = 0x200;
    }
    else if (iVar1 == 2) {
      iVar1 = 4;
    }
    else if (iVar1 == 3) {
      iVar1 = 2;
    }
    else {
      iVar1 = 1;
    }
  }
  else if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    iVar1 = (-(uint)((param_2 & 0x80000000) != 0) & 0xffffff90) + 0x80;
  }
  else if ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) == 0.0) {
    iVar1 = (-(uint)((param_2 & 0x80000000) != 0) & 0xffffffe0) + 0x40;
  }
  else {
    iVar1 = (-(uint)((param_2 & 0x80000000) != 0) & 0xffffff08) + 0x100;
  }
  return iVar1;
}
```

---

## FUN_004875e0 — 0x4875e0

- Classification : internal
- Corps : `0x4875e0–0x487608`
- État : pseudocode obtenu
- Evidence : `ev_2d63c3defa7fef834cb4471a59d0e757e04333b4c483a85f33d0289fb6d8cb74`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x487610` — `FUN_00487610`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004875e0(void)

{
  if (DAT_00632988 == 0) {
    FUN_00487610();
    DAT_00632988 = DAT_00632988 + 1;
  }
  return;
}
```

---


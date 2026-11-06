# 0007_batch_0003 — détails (1/2)

## FUN_0040afd3 — 0x40afd3

- Classification : internal
- Corps : `0x40afd3–0x40b099`
- État : pseudocode obtenu
- Evidence : `ev_a4155f95003acd7f3310865a482847771a7802846f8b38ae43838372ddb3ad5b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40105f` — `thunk_FUN_0040ab05`
- `0x40198d` — `thunk_FUN_0040ab42`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401f14` — `thunk_FUN_00404770`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040afd3(int param_1,short *param_2)

{
  short sVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  undefined2 extraout_var;
  undefined4 uVar6;
  undefined4 uVar7;
  
  sVar1 = *param_2;
  iVar4 = *(int *)(param_1 + 4);
  sVar2 = *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
  sVar3 = param_2[1];
  iVar5 = *(int *)(param_1 + 8);
  thunk_FUN_0040ab42(param_1,param_2);
  uVar6 = thunk_FUN_0040e864(CONCAT22(extraout_var,DAT_0049acbc));
  uVar7 = thunk_FUN_0040ab05((int)(char)(&DAT_0049ad04)[*(int *)(param_2 + 6)],
                             (int)(char)(&DAT_0049ad08)[*(int *)(param_2 + 6)],
                             (int)param_2[0x1d] / 3,uVar6);
  thunk_FUN_00404770(param_1,uVar6,uVar7,(iVar4 + sVar1) - (int)sVar2,iVar5 + sVar3);
  return;
}
```

---

---

## FUN_0040b09a — 0x40b09a

- Classification : internal
- Corps : `0x40b09a–0x40b2e5`
- État : pseudocode obtenu
- Evidence : `ev_c454d7fb5d524fdd5ec56d6a1fef42e234a6ed8e81d3e14ffb9b0592edacc8a7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40130c` — `thunk_FUN_0045575c`
- `0x40163b` — `thunk_FUN_00404c3b`
- `0x40174e` — `thunk_FUN_004109a6`
- `0x401933` — `thunk_FUN_00464242`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401eab` — `thunk_FUN_0040bf98`
- `0x402086` — `thunk_FUN_00404c5a`
- `0x402306` — `thunk_FUN_004106dd`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040b09a(int param_1,short *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 uVar9;
  int local_28;
  int local_20;
  
  iVar1 = (*(int *)(param_1 + 4) + (int)*param_2) -
          (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
  iVar2 = *(int *)(param_1 + 8) + (int)param_2[1];
  if ((*(int *)(param_2 + 8) < 6) || (9 < *(int *)(param_2 + 8))) {
    thunk_FUN_0040bf98(param_1,param_2,iVar1,iVar2,1,0x10000,0xffffffff);
    if ((*(uint *)(param_2 + 0xe) & 2) != 0) {
      local_20 = (int)param_2[0x21];
      iVar3 = thunk_FUN_00464242((&DAT_006137b8)[param_2[0x17] * 0x13],
                                 *(undefined4 *)(&DAT_006137bc + param_2[0x17] * 0x4c));
      psVar4 = (short *)thunk_FUN_0045575c(*(undefined2 *)(iVar3 + 4));
      if (local_20 < 0x11) {
        local_20 = local_20 / 2;
        if (local_20 < 0) {
          local_20 = 0;
        }
        if (7 < local_20) {
          local_20 = 7;
        }
        uVar5 = thunk_FUN_004106dd(1,local_20);
        if (*psVar4 != -1) {
          iVar8 = iVar2 + -0x28;
          uVar9 = 0;
          iVar3 = iVar1;
          uVar7 = uVar5;
          uVar6 = thunk_FUN_0040e864(CONCAT22((short)((uint)iVar8 >> 0x10),*psVar4));
          thunk_FUN_004109a6(param_1,uVar6,uVar9,iVar3,iVar8,uVar7);
        }
        iVar2 = iVar2 + -0x28;
        uVar6 = 0;
        uVar7 = thunk_FUN_0040e864(CONCAT22((short)((uint)iVar2 >> 0x10),psVar4[1]));
        thunk_FUN_004109a6(param_1,uVar7,uVar6,iVar1,iVar2,uVar5);
      }
      else {
        local_28 = (100 - local_20) / 2;
        if (local_28 < 0) {
          local_28 = 0;
        }
        if (7 < local_28) {
          local_28 = 7;
        }
        uVar5 = thunk_FUN_004106dd(1,local_28);
        thunk_FUN_00404c3b(uVar5);
        if (*psVar4 != -1) {
          iVar8 = iVar2 + -0x28;
          uVar7 = 0;
          iVar3 = iVar1;
          uVar5 = thunk_FUN_0040e864(CONCAT22((short)((uint)iVar8 >> 0x10),*psVar4));
          thunk_FUN_00404c5a(param_1,uVar5,uVar7,iVar3,iVar8);
        }
        iVar2 = iVar2 + -0x28;
        uVar7 = 0;
        uVar5 = thunk_FUN_0040e864(CONCAT22((short)((uint)iVar2 >> 0x10),psVar4[1]));
        thunk_FUN_00404c5a(param_1,uVar5,uVar7,iVar1,iVar2);
      }
    }
  }
  else {
    thunk_FUN_0040bf98(param_1,param_2,iVar1,iVar2,1,0x10000,0xffffffff);
  }
  return;
}
```

---

---

## FUN_0040b2e6 — 0x40b2e6

- Classification : internal
- Corps : `0x40b2e6–0x40b344`
- État : pseudocode obtenu
- Evidence : `ev_82799e3efe57367fce4257d4a4ccf5105a0255cb313103bd434ca6c3ad65d6a0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401eab` — `thunk_FUN_0040bf98`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040b2e6(int param_1,short *param_2)

{
  thunk_FUN_0040bf98(param_1,param_2,
                     (*(int *)(param_1 + 4) + (int)*param_2) -
                     (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2),
                     *(int *)(param_1 + 8) + (int)param_2[1],1,0x10000,0xffffffff);
  return;
}
```

---

---

## FUN_0040b345 — 0x40b345

- Classification : internal
- Corps : `0x40b345–0x40bf97`
- État : pseudocode obtenu
- Evidence : `ev_8dce4ad91260c55dc96a2edad2289a3f79b6c07ce8f9fa75e5529f6ca6418ab4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401082` — `thunk_FUN_00410bd2`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401f14` — `thunk_FUN_00404770`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Removing unreachable block (ram,0x0040bf78) */

void FUN_0040b345(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if ((*(int *)(param_2 + 0x10) == 4) || (*(int *)(param_2 + 0x10) == 0x16)) {
    iVar1 = *(int *)(param_1 + 4) - (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
    iVar2 = *(int *)(param_1 + 8);
    if ((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 0) {
      iVar1 = iVar1 + 0x6b3;
      iVar2 = iVar2 + 100;
      thunk_FUN_00404770(param_1,&DAT_005c3840,-((*(ushort *)(param_2 + 0x4a) & 1) != 0) & 2,iVar1,
                         iVar2);
      thunk_FUN_00404770(param_1,&DAT_005c3840,(-((*(ushort *)(param_2 + 0x4a) & 2) != 0) & 2U) + 1,
                         iVar1,iVar2);
      if ((*(uint *)(param_2 + 0x1c) & 1) != 0) {
        thunk_FUN_00410bd2(param_1,&DAT_005c3840,4,iVar1,iVar2,
                           (int)((int)*(short *)(param_2 + 0x30) +
                                ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
      }
    }
    else if ((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 1) {
      if ((*(ushort *)(param_2 + 0x4a) & 1) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,0,iVar1 + 0x11a,iVar2 + 0xe9);
      }
      if ((*(ushort *)(param_2 + 0x4a) & 2) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,1,iVar1 + 0x169,iVar2 + 0xf6);
      }
      if ((*(uint *)(param_2 + 0x1c) & 1) != 0) {
        thunk_FUN_00410bd2(param_1,&DAT_005c3840,2,iVar1 + 0x131,iVar2 + 0xae,
                           (int)((int)*(short *)(param_2 + 0x30) +
                                ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
      }
    }
    else if ((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 2) {
      if ((*(uint *)(param_2 + 0x1c) & 1) == 0) {
        if ((*(ushort *)(param_2 + 0x4a) & 1) != 0) {
          thunk_FUN_00404770(param_1,&DAT_005c3840,0,iVar1 + 0x4c,iVar2);
        }
        if ((*(ushort *)(param_2 + 0x4a) & 2) != 0) {
          thunk_FUN_00404770(param_1,&DAT_005c3840,1,iVar1 + 0x144,iVar2);
        }
      }
      else {
        thunk_FUN_00410bd2(param_1,&DAT_005c3840,2,iVar1 + 0x2d,iVar2,
                           (int)((int)*(short *)(param_2 + 0x30) +
                                ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
      }
    }
    else if ((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 3) {
      if ((*(uint *)(param_2 + 0x1c) & 1) == 0) {
        if ((*(ushort *)(param_2 + 0x4a) & 3) != 0) {
          thunk_FUN_00404770(param_1,&DAT_005c3840,0,iVar1 + 0x8f,iVar2 + 99);
        }
      }
      else {
        thunk_FUN_00410bd2(param_1,&DAT_005c3840,1,iVar1 + 0x3e,iVar2,
                           (int)((int)*(short *)(param_2 + 0x30) +
                                ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
      }
    }
    else if ((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 4) {
      if ((*(ushort *)(param_2 + 0x4a) & 1) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,0,iVar1 + 0x529,iVar2 + 0x8c);
      }
      if ((*(ushort *)(param_2 + 0x4a) & 2) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,1,iVar1 + 0x5c2,iVar2 + 0x90);
      }
      if ((*(uint *)(param_2 + 0x1c) & 1) != 0) {
        thunk_FUN_00410bd2(param_1,&DAT_005c3840,2,iVar1 + 0x4a5,iVar2,
                           (int)((int)*(short *)(param_2 + 0x30) +
                                ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
      }
    }
    else if ((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 5) {
      if ((*(ushort *)(param_2 + 0x4a) & 1) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,0,iVar1 + 0x2d4,iVar2 + 0xd5);
      }
      if ((*(ushort *)(param_2 + 0x4a) & 2) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,1,iVar1 + 0x33e,iVar2 + 0xd5);
      }
      if ((*(uint *)(param_2 + 0x1c) & 1) != 0) {
        thunk_FUN_00410bd2(param_1,&DAT_005c3840,2,iVar1 + 0x25e,iVar2 + 0x23,
                           (int)((int)*(short *)(param_2 + 0x30) +
                                ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
      }
    }
    else if ((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 6) {
      if ((*(ushort *)(param_2 + 0x4a) & 1) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,0,iVar1 + 0x40,iVar2 + 0x6c);
      }
      if ((*(ushort *)(param_2 + 0x4a) & 2) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,1,iVar1 + 0xa0,iVar2 + 0x69);
      }
      if ((*(uint *)(param_2 + 0x1c) & 1) != 0) {
        thunk_FUN_00410bd2(param_1,&DAT_005c3840,2,iVar1 + 0x26,iVar2 + 9,
                           (int)((int)*(short *)(param_2 + 0x30) +
                                ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
      }
    }
    else if ((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 7) {
      if ((*(uint *)(param_2 + 0x1c) & 1) == 0) {
        if ((*(ushort *)(param_2 + 0x4a) & 1) != 0) {
          thunk_FUN_00404770(param_1,&DAT_005c3840,0,iVar1 + 0x8f,iVar2 + 0xa2);
        }
        if ((*(ushort *)(param_2 + 0x4a) & 2) != 0) {
          thunk_FUN_00404770(param_1,&DAT_005c3840,1,iVar1 + 0xf5,iVar2 + 0xa5);
        }
      }
      else {
        thunk_FUN_00410bd2(param_1,&DAT_005c3840,2,iVar1 + 0x61,iVar2,
                           (int)((int)*(short *)(param_2 + 0x30) +
                                ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
      }
    }
    else if ((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 8) {
      if ((*(uint *)(param_2 + 0x1c) & 1) == 0) {
        if ((*(ushort *)(param_2 + 0x4a) & 1) != 0) {
          thunk_FUN_00404770(param_1,&DAT_005c3840,0,iVar1 + 0x4a1,iVar2 + 0x43);
        }
        if ((*(ushort *)(param_2 + 0x4a) & 2) != 0) {
          thunk_FUN_00404770(param_1,&DAT_005c3840,1,iVar1 + 0x51a,iVar2 + 0x9e);
        }
      }
      else {
        thunk_FUN_00410bd2(param_1,&DAT_005c3840,2,iVar1 + 0x47b,iVar2 + 0x33,
                           (int)((int)*(short *)(param_2 + 0x30) +
                                ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
      }
    }
    else if ((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 9) {
      if ((*(ushort *)(param_2 + 0x4a) & 1) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,0,iVar1 + 0x42a,iVar2 + 0x74);
      }
      if ((*(ushort *)(param_2 + 0x4a) & 2) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,1,iVar1 + 0x4d6,iVar2 + 0x7f);
      }
      if ((*(uint *)(param_2 + 0x1c) & 1) != 0) {
        thunk_FUN_00410bd2(param_1,&DAT_005c3840,2,iVar1 + 0x460,iVar2,
                           (int)((int)*(short *)(param_2 + 0x30) +
                                ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
      }
    }
    else if ((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 10) {
      if (((*(ushort *)(param_2 + 0x4a) & 1) != 0) && ((*(uint *)(param_2 + 0x1c) & 1) == 0)) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,0,iVar1 + 0x421,iVar2 + 0x87);
      }
      if ((*(ushort *)(param_2 + 0x4a) & 2) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,1,iVar1 + 0x43b,iVar2 + 0x18);
      }
      if ((*(uint *)(param_2 + 0x1c) & 1) != 0) {
        thunk_FUN_00410bd2(param_1,&DAT_005c3840,2,iVar1 + 0x3bc,iVar2 + 0x60,
                           (int)((int)*(short *)(param_2 + 0x30) +
                                ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
      }
    }
    else if ((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 0xb) {
      thunk_FUN_00404770(param_1,&DAT_005c3840,0,iVar1 + 0x57b,iVar2 + 0xf0);
      if ((*(ushort *)(param_2 + 0x4a) & 1) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,1,iVar1 + 0x57b,iVar2 + 0xf0);
      }
      if ((*(ushort *)(param_2 + 0x4a) & 2) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,2,iVar1 + 0x57b,iVar2 + 0xf0);
      }
      if ((*(uint *)(param_2 + 0x1c) & 1) != 0) {
        thunk_FUN_00410bd2(param_1,&DAT_005c3840,3,iVar1 + 0x58e,iVar2 + 0x75,
                           (int)((int)*(short *)(param_2 + 0x30) +
                                ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
      }
    }
    else if ((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 0xc) {
      if ((*(ushort *)(param_2 + 0x4a) & 1) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,0,iVar1 + 0x4e7,iVar2 + 0xa0);
      }
      if ((*(ushort *)(param_2 + 0x4a) & 2) != 0) {
        thunk_FUN_00404770(param_1,&DAT_005c3840,1,iVar1 + 0x4e7,iVar2 + 0xa0);
      }
      if ((*(uint *)(param_2 + 0x1c) & 1) != 0) {
        thunk_FUN_00410bd2(param_1,&DAT_005c3840,2,iVar1 + 0x4e7,iVar2 + 0xa0,
                           (int)((int)*(short *)(param_2 + 0x30) +
                                ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
      }
    }
    else if ((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 0xd) {
      if ((*(uint *)(param_2 + 0x1c) & 1) == 0) {
        if ((*(ushort *)(param_2 + 0x4a) & 1) != 0) {
          thunk_FUN_00404770(param_1,&DAT_005c3840,0,iVar1 + 0x463,iVar2 + 0x82);
        }
        if ((*(ushort *)(param_2 + 0x4a) & 2) != 0) {
          thunk_FUN_00404770(param_1,&DAT_005c3840,1,iVar1 + 0x463,iVar2 + 0x82);
        }
      }
      else {
        thunk_FUN_00410bd2(param_1,&DAT_005c3840,2,iVar1 + 0x463,iVar2 + 0x82,
                           (int)((int)*(short *)(param_2 + 0x30) +
                                ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
      }
    }
    else if (((&DAT_005eebf8)[DAT_0049f53c * 0x14f4] == 0xe) &&
            ((*(uint *)(param_2 + 0x1c) & 1) != 0)) {
      thunk_FUN_00410bd2(param_1,&DAT_005c3840,0,iVar1 + 0x45d,iVar2,
                         (int)((int)*(short *)(param_2 + 0x30) +
                              ((int)*(short *)(param_2 + 0x30) >> 0x1f & 3U)) >> 2);
    }
  }
  return;
}
```

---

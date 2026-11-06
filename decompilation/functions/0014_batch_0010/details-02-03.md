# 0014_batch_0010 — détails (3/3)

## FUN_00444fd0 — 0x444fd0

- Classification : internal
- Corps : `0x444fd0–0x444ffd`
- État : pseudocode obtenu
- Evidence : `ev_f9cf150784fdbe272fbcb939806ba99ba1e44a4e856a4b8ff98894bf6eb193d5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b5e` — `thunk_FUN_00442bf0`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00444fd0(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00442bf0();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_00445010 — 0x445010

- Classification : internal
- Corps : `0x445010–0x44503d`
- État : pseudocode obtenu
- Evidence : `ev_bb4e980a70168ee049b39fe5161e1f193d5fe41682b8abc59ca3e61306e9f2cb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4015b9` — `thunk_FUN_00442ee2`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00445010(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_00442ee2();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_00445050 — 0x445050

- Classification : internal
- Corps : `0x445050–0x44507d`
- État : pseudocode obtenu
- Evidence : `ev_7d6210ea729ebc017b416bc9ff1c422e5d7496764de23d42489d39ea015da5e3`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40148d` — `thunk_FUN_004432ec`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00445050(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_004432ec();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

---

## FUN_00445090 — 0x445090

- Classification : internal
- Corps : `0x445090–0x4450e3`
- État : pseudocode obtenu
- Evidence : `ev_5bb3f65ed53a7886004b4a015205097bdf7fc4313f52f894e2fb83442011467d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018a2` — `thunk_FUN_00445100`
- `0x401cbc` — `thunk_FUN_00429243`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00445090(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491969;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  *in_ECX = &PTR_LAB_00494560;
  thunk_FUN_00445100();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

---

## FUN_004450e4 — 0x4450e4

- Classification : internal
- Corps : `0x4450e4–0x4450ff`
- État : pseudocode obtenu
- Evidence : `ev_9e80933d87d04d925be0728bef6e5d76167014c4d6eb8c6d837214512870147c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004450e4(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_00494560;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_00445100 — 0x445100

- Classification : internal
- Corps : `0x445100–0x445144`
- État : pseudocode obtenu
- Evidence : `ev_ccfb02e7bf9118cdbd84051052a6968be58cf4f0f224e0614dea2832f5d450ea`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00445100(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0xf4) = 0;
  *(undefined2 *)(in_ECX + 0xf0) = 0;
  DAT_005e16ec = 9999;
  *(undefined2 *)(in_ECX + 0xfc) = 0xffff;
  *(undefined2 *)(in_ECX + 0xfe) = 0xffff;
  return;
}
```

---

---

## FUN_00445145 — 0x445145

- Classification : internal
- Corps : `0x445145–0x4455d0`
- État : pseudocode obtenu
- Evidence : `ev_7f2318bb02feca67ff2fdbff8c0b8670431c3b109d5eedbda03b58235ff29ab0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401569` — `thunk_FUN_0046c558`
- `0x40171c` — `thunk_FUN_004455d1`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401e2e` — `thunk_FUN_00445739`
- `0x40211c` — `thunk_FUN_0044590d`
- `0x4021c6` — `thunk_FUN_0046ba3b`
- `0x4023d3` — `thunk_FUN_0046b928`

### Chaînes référencées

- `0x4a0f30` — "scrollup"
- `0x4a0f3c` — "scrolldn"
- `0x4a0f48` — "scrollup"
- `0x4a0f54` — "scrolldn"
- `0x4a0f60` — "IWTaskOptions"
- `0x4a0f70` — "IWTaskInfo"

### Pseudocode Ghidra

```c
undefined4 FUN_00445145(short param_1,int param_2,int param_3)

{
  short sVar1;
  bool bVar2;
  undefined4 uVar3;
  int in_ECX;
  int local_c;
  
  bVar2 = false;
  if (param_1 < 7) {
    if (param_1 == 6) {
      if ((((*(int *)(in_ECX + 0xc) < param_2) && (param_2 < *(int *)(in_ECX + 0x14) + -0xd)) &&
          (*(int *)(in_ECX + 0x10) < param_3)) && (param_3 < *(int *)(in_ECX + 0x18))) {
        if ((DAT_0062c6bc == *(short *)(in_ECX + 0xfc)) ||
           (DAT_0062c6bc == *(short *)(in_ECX + 0xfe))) {
          return 0;
        }
        thunk_FUN_0044590d(param_2,param_3);
        bVar2 = true;
      }
    }
    else if (param_1 == 1) {
      thunk_FUN_0046b928(*(undefined4 *)(in_ECX + 4),5000,0,0,0);
      *(short *)(in_ECX + 0xf8) = (short)((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) / 0xd)
      ;
      *(undefined2 *)(in_ECX + 0xfa) = 0;
      if ((*(short *)(in_ECX + 0xfc) == -1) || (*(short *)(in_ECX + 0xfe) == -1)) {
        thunk_FUN_0046c558(s_scrollup_004a0f30,3,in_ECX + 0xfc);
        thunk_FUN_0046c558(s_scrolldn_004a0f3c,3,in_ECX + 0xfe);
      }
    }
    else if (param_1 == 2) {
      DAT_005e16ec = 9999;
      thunk_FUN_0046ba3b(*(undefined4 *)(in_ECX + 4),0xffffffff);
      if ((*(short *)(in_ECX + 0xfc) != -1) || (*(short *)(in_ECX + 0xfe) == -1)) {
        thunk_FUN_0046c558(s_scrollup_004a0f48,3,in_ECX + 0xfc);
        thunk_FUN_0046c558(s_scrolldn_004a0f54,3,in_ECX + 0xfe);
      }
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0xfc),2,0,0);
      thunk_FUN_0046c371((int)*(short *)(in_ECX + 0xfe),2,0,0);
      *(undefined4 *)(in_ECX + 0x100) = 0;
      *(undefined4 *)(in_ECX + 0x104) = 0;
    }
  }
  else if (param_1 < 0x1771) {
    if (param_1 == 6000) {
      sVar1 = *(short *)(in_ECX + 0xfa);
      *(short *)(in_ECX + 0xfa) = *(short *)(in_ECX + 0xfa) + -1;
      if (*(short *)(in_ECX + 0xfa) < 0) {
        *(undefined2 *)(in_ECX + 0xfa) = 0;
      }
      if (sVar1 != *(short *)(in_ECX + 0xfa)) {
        thunk_FUN_00445739();
      }
      bVar2 = true;
    }
    else if (param_1 == 4999) {
      if ((&DAT_006183bc)[param_2 * 5] != 0) {
        *(undefined4 **)(in_ECX + 0xf4) = &DAT_006183bc + param_2 * 5;
        thunk_FUN_0046c3bc(s_IWTaskOptions_004a0f60,0x13ba,*(undefined4 *)(in_ECX + 0xf4),0);
        thunk_FUN_0046c3bc(s_IWTaskInfo_004a0f70,0x13ba,*(undefined4 *)(in_ECX + 0xf4),0);
        if (*(short *)(in_ECX + 0xf8) < *(short *)(in_ECX + 0xf0)) {
          for (local_c = 0; local_c < *(short *)(in_ECX + 0xf0); local_c = local_c + 1) {
            if (*(int *)(in_ECX + 0x70 + local_c * 4) == *(int *)(in_ECX + 0xf4)) {
              if ((int)*(short *)(in_ECX + 0xf8) < local_c - *(short *)(in_ECX + 0xfa)) {
                *(undefined2 *)(in_ECX + 0xfa) = (undefined2)local_c;
                thunk_FUN_00445739();
              }
              break;
            }
          }
        }
      }
    }
    else if (param_1 == 5000) {
      thunk_FUN_004455d1();
      bVar2 = true;
    }
  }
  else if (param_1 == 0x1771) {
    sVar1 = *(short *)(in_ECX + 0xfa);
    if (((int)*(short *)(in_ECX + 0xf0) != (int)*(short *)(in_ECX + 0xf8) &&
         -1 < (int)*(short *)(in_ECX + 0xf0) - (int)*(short *)(in_ECX + 0xf8)) &&
       (*(short *)(in_ECX + 0xfa) = *(short *)(in_ECX + 0xfa) + 1,
       (int)*(short *)(in_ECX + 0xf0) - (int)*(short *)(in_ECX + 0xf8) <
       (int)*(short *)(in_ECX + 0xfa))) {
      *(short *)(in_ECX + 0xfa) = *(short *)(in_ECX + 0xf0) - *(short *)(in_ECX + 0xf8);
    }
    if (sVar1 != *(short *)(in_ECX + 0xfa)) {
      thunk_FUN_00445739();
    }
    bVar2 = true;
  }
  if (bVar2) {
    uVar3 = 1;
  }
  else {
    uVar3 = thunk_FUN_004293c6(param_1,param_2,param_3);
  }
  return uVar3;
}
```

---

---

## FUN_004455d1 — 0x4455d1

- Classification : internal
- Corps : `0x4455d1–0x445738`
- État : pseudocode obtenu
- Evidence : `ev_bc320115f0f140331cab5bd3c6af1bb19d2505748d9aa0d0e1ae63d7addc020b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401e2e` — `thunk_FUN_00445739`

### Chaînes référencées

- `0x4a0f7c` — "IWTaskOptions"
- `0x4a0f8c` — "IWTaskInfo"

### Pseudocode Ghidra

```c
void FUN_004455d1(void)

{
  int in_ECX;
  int local_8;
  
  *(undefined2 *)(in_ECX + 0xf0) = 0;
  for (local_8 = 0; local_8 < 0x40; local_8 = local_8 + 1) {
    if (((((short)(&DAT_006183c4)[local_8 * 10] == DAT_0049f538) &&
         ((&DAT_006183bc)[local_8 * 5] != 0)) && ((&DAT_006183cc)[local_8 * 10] != 0xb)) &&
       (*(short *)(in_ECX + 0xf0) < 0x20)) {
      *(undefined4 **)(in_ECX + 0x70 + *(short *)(in_ECX + 0xf0) * 4) = &DAT_006183bc + local_8 * 5;
      *(short *)(in_ECX + 0xf0) = *(short *)(in_ECX + 0xf0) + 1;
    }
  }
  if ((*(int *)(in_ECX + 0xf4) == 0) || (**(int **)(in_ECX + 0xf4) == 0)) {
    *(undefined4 *)(in_ECX + 0xf4) = 0;
    if (*(short *)(in_ECX + 0xf0) != 0) {
      *(undefined4 *)(in_ECX + 0xf4) = *(undefined4 *)(in_ECX + 0x70);
    }
    thunk_FUN_0046c3bc(s_IWTaskOptions_004a0f7c,0x13ba,*(undefined4 *)(in_ECX + 0xf4),0);
    thunk_FUN_0046c3bc(s_IWTaskInfo_004a0f8c,0x13ba,*(undefined4 *)(in_ECX + 0xf4),0);
  }
  thunk_FUN_00445739();
  if ((*(int *)(in_ECX + 0xf4) == 0) || (*(int *)(in_ECX + 0x3c) != 1)) {
    DAT_005e16ec = 9999;
  }
  else {
    DAT_005e16ec = (undefined2)((*(int *)(in_ECX + 0xf4) + -0x6183bc) / 0x14);
  }
  return;
}
```

---

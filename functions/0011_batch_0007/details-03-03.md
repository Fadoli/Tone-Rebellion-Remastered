# 0011_batch_0007 — détails (3/3)

## FUN_0042a25b — 0x42a25b

- Classification : internal
- Corps : `0x42a25b–0x42a27e`
- État : pseudocode obtenu
- Evidence : `ev_eaa3835e7259b33e3cb189b5d145ef68729480f0efad3c76576ae842451a6e6b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0042a25b(void)

{
  int in_ECX;
  
  if (*(int *)(in_ECX + 0x70) != 0) {
    *(undefined4 *)(in_ECX + 0x74) = 0;
  }
  return *(undefined4 *)(in_ECX + 0x74);
}
```

---

---

## FUN_0042a27f — 0x42a27f

- Classification : internal
- Corps : `0x42a27f–0x42a3ca`
- État : pseudocode obtenu
- Evidence : `ev_c9510672eb7a91443b69d00f23f1deada8d18411a7fde9c3469905273dd228e8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40146f` — `thunk_FUN_0042d87c`
- `0x40163b` — `thunk_FUN_00404c3b`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x402086` — `thunk_FUN_00404c5a`
- `0x402306` — `thunk_FUN_004106dd`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a27f(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int *in_ECX;
  int iVar3;
  int local_8;
  
  if ((in_ECX[0xd] != 0) && (in_ECX[0xf] != 0)) {
    if (((in_ECX[1] == DAT_0062c6bc) || (in_ECX[0xd] == 2)) &&
       ((in_ECX[0x11] != 0 && (in_ECX[0xd] != 3)))) {
      (**(code **)(*in_ECX + 0xc))(param_1);
    }
    else if (*(short *)((int)in_ECX + 0x1e) != -1) {
      iVar1 = thunk_FUN_0042d28f();
      in_ECX[2] = iVar1;
      local_8 = (int)*(short *)((int)in_ECX + 0x1e);
      iVar1 = (**(code **)(*in_ECX + 0x14))();
      if (iVar1 != 0) {
        local_8 = local_8 + 2;
      }
      if (in_ECX[0xe] == 0) {
        uVar2 = thunk_FUN_004106dd(0,3);
        thunk_FUN_00404c3b(uVar2);
        iVar3 = (int)*(short *)((int)in_ECX + 0x6e);
        iVar1 = (int)(short)in_ECX[0x1b];
        uVar2 = thunk_FUN_0040e864(CONCAT22((short)in_ECX[0x1b] >> 0xf,(short)in_ECX[7]));
        thunk_FUN_00404c5a(in_ECX + 2,uVar2,local_8,iVar1,iVar3);
      }
      else {
        iVar1 = (int)*(short *)((int)in_ECX + 0x6e);
        iVar3 = (int)(short)in_ECX[0x1b];
        uVar2 = thunk_FUN_0040e864(CONCAT22((short)in_ECX[0x1b] >> 0xf,(short)in_ECX[7]));
        thunk_FUN_00404770(in_ECX + 2,uVar2,local_8,iVar3,iVar1);
      }
      thunk_FUN_0042d38a();
    }
    thunk_FUN_0042d87c(in_ECX + 2,3);
    in_ECX[0xd] = 0;
  }
  return;
}
```

---

---

## FUN_0042a3cb — 0x42a3cb

- Classification : internal
- Corps : `0x42a3cb–0x42a450`
- État : pseudocode obtenu
- Evidence : `ev_1583bc979d902b0ad2d4ff3484855b2d9432e1812f3779e7d0cb9bb42535c62a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x402329` — `thunk_FUN_0042d28f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0042a3cb(void)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  int *in_ECX;
  int iVar4;
  int local_8;
  
  if (*(short *)((int)in_ECX + 0x1e) != -1) {
    sVar1 = *(short *)((int)in_ECX + 0x1e);
    local_8 = sVar1 + 1;
    iVar2 = (**(code **)(*in_ECX + 0x14))();
    if (iVar2 != 0) {
      local_8 = sVar1 + 3;
    }
    iVar2 = thunk_FUN_0042d28f();
    in_ECX[2] = iVar2;
    iVar2 = (int)*(short *)((int)in_ECX + 0x6e);
    iVar4 = (int)(short)in_ECX[0x1b];
    uVar3 = thunk_FUN_0040e864(CONCAT22((short)in_ECX[0x1b] >> 0xf,(short)in_ECX[7]));
    thunk_FUN_00404770(in_ECX + 2,uVar3,local_8,iVar4,iVar2);
    thunk_FUN_0042d38a();
  }
  return;
}
```

---

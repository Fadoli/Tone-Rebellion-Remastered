# 0013_batch_0009 — détails (3/3)

## FUN_0043d254 — 0x43d254

- Classification : internal
- Corps : `0x43d254–0x43d26f`
- État : pseudocode obtenu
- Evidence : `ev_6d84e9ecccd8eb7c6a5d3730e0db2b32d1e220c6cc3fb719c2e76d4ffec707f0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043d254(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004943e0;
  thunk_FUN_00429262();
  return;
}
```

---

---

## FUN_0043d270 — 0x43d270

- Classification : internal
- Corps : `0x43d270–0x43d284`
- État : pseudocode obtenu
- Evidence : `ev_d1905fe2ffeaa0be94b48c0ebf56c397de2f0ace7211b5a5dd886b7b72071415`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043d270(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x74) = 0;
  return;
}
```

---

---

## FUN_0043d285 — 0x43d285

- Classification : internal
- Corps : `0x43d285–0x43d419`
- État : pseudocode obtenu
- Evidence : `ev_1f4c9fb7164cf7098c41401790393896464ff57491fc99b2d87cefa2ada748d0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010d2` — `thunk_FUN_0043d45c`
- `0x401168` — `thunk_FUN_0043d41a`
- `0x4012d0` — `thunk_FUN_00429f3a`
- `0x4014f1` — `thunk_FUN_0043d59b`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x4021c6` — `thunk_FUN_0046ba3b`
- `0x4023d3` — `thunk_FUN_0046b928`

### Chaînes référencées

- `0x4a0178` — "IWTextInfo"
- `0x4a0184` — "InvCycle"

### Pseudocode Ghidra

```c
void FUN_0043d285(short param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int in_ECX;
  
  if (param_1 < 7) {
    if (param_1 == 6) {
      iVar1 = thunk_FUN_00429f3a();
      if (iVar1 != 0) {
        thunk_FUN_0043d41a(param_2,param_3);
        return;
      }
    }
    else if (param_1 == 1) {
      *(undefined2 *)(in_ECX + 0x70) = 0xffff;
      *(undefined2 *)(in_ECX + 0xee) = 0xffff;
      *(undefined2 *)(in_ECX + 0xec) = 0;
      thunk_FUN_0046b928(*(undefined4 *)(in_ECX + 4),0x16e2,0,0,0);
      thunk_FUN_0046c3bc(s_IWTextInfo_004a0178,0x3039,6,0);
    }
    else if (param_1 == 2) {
      thunk_FUN_0046ba3b(*(undefined4 *)(in_ECX + 4),0xffffffff);
      thunk_FUN_0046c3bc(s_InvCycle_004a0184,2,0,0);
      DAT_0049e9c4 = 0xffff;
    }
  }
  else {
    if (param_1 == 10) {
      thunk_FUN_0043d45c(param_2,param_3);
      return;
    }
    if (param_1 == 0x45) {
      if ((*(short *)(in_ECX + 0xec) + 1) * 10 < (int)*(short *)(in_ECX + 0xee)) {
        *(short *)(in_ECX + 0xec) = *(short *)(in_ECX + 0xec) + 1;
      }
      else {
        *(undefined2 *)(in_ECX + 0xec) = 0;
      }
      *(undefined4 *)(in_ECX + 0x34) = 1;
    }
    else if (param_1 == 0x16e2) {
      thunk_FUN_0043d59b();
    }
  }
  thunk_FUN_004293c6(param_1,param_2,param_3);
  return;
}
```

---

---

## FUN_0043d41a — 0x43d41a

- Classification : internal
- Corps : `0x43d41a–0x43d45b`
- État : pseudocode obtenu
- Evidence : `ev_4e1e27dddf6c34bbe05a21515af03d18a7ad0bf9694377f7dfea542b843b5a6d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010d2` — `thunk_FUN_0043d45c`
- `0x401bf4` — `thunk_FUN_0042970c`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0043d41a(undefined4 param_1,undefined4 param_2)

{
  int in_ECX;
  
  if (*(short *)(in_ECX + 0x70) != -1) {
    thunk_FUN_0042970c(0x42,(int)*(short *)(in_ECX + 0x70),0);
    thunk_FUN_0043d45c(param_1,param_2);
  }
  return 1;
}
```

---

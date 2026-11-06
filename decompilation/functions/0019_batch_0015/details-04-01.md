# 0019_batch_0015 — détails (1/3)

## FUN_00476310 — 0x476310

- Classification : internal
- Corps : `0x476310–0x4763d4`
- État : pseudocode obtenu
- Evidence : `ev_207550cca99273fa4fc4550fe73685faf2db93241c6d2c2f1c1ea3a5194577e2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476230` — `FID_conflict:AtlIsValidAddress`
- `0x476280` — `FUN_00476280`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4
FUN_00476310(int param_1,int param_2,undefined4 *param_3,undefined4 *param_4,undefined4 *param_5)

{
  int iVar1;
  
  iVar1 = FUN_00476280(param_1);
  if (((iVar1 != 0) &&
      (((((*(uint *)(param_1 + -0xc) & 0xffff) == 4 || (*(int *)(param_1 + -0xc) == 1)) ||
        ((*(uint *)(param_1 + -0xc) & 0xffff) == 2)) || (*(int *)(param_1 + -0xc) == 3)))) &&
     (((iVar1 = FID_conflict_AtlIsValidAddress(param_1,param_2,1), iVar1 != 0 &&
       (*(int *)(param_1 + -0x10) == param_2)) && (*(int *)(param_1 + -8) <= DAT_004a634c)))) {
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = *(undefined4 *)(param_1 + -8);
    }
    if (param_4 != (undefined4 *)0x0) {
      *param_4 = *(undefined4 *)(param_1 + -0x18);
    }
    if (param_5 != (undefined4 *)0x0) {
      *param_5 = *(undefined4 *)(param_1 + -0x14);
    }
    return 1;
  }
  return 0;
}
```

---

---

## FUN_004763e0 — 0x4763e0

- Classification : internal
- Corps : `0x4763e0–0x4763fb`
- État : pseudocode obtenu
- Evidence : `ev_d0faf7c39d085e29f0895313150c18ec786727f93570ecb86ab63629b9486073`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004763e0(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_00633e8c;
  DAT_00633e8c = param_1;
  return uVar1;
}
```

---

---

## FUN_00476400 — 0x476400

- Classification : internal
- Corps : `0x476400–0x476555`
- État : pseudocode obtenu
- Evidence : `ev_81255a7c36abbfb9c470ae424e9c5a63f595e25c14e20149baf0520885c2acb0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x47642e with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x47652b with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x4957ac` — "Bad memory block found at 0x%08X.\n"
- `0x4957d0` — "_CrtMemCheckPoint: NULL state pointer.\n"

### Pseudocode Ghidra

```c
void FUN_00476400(undefined4 *param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 *local_c;
  int local_8;
  
  if (param_1 == (undefined4 *)0x0) {
    iVar2 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"_CrtMemCheckPoint: NULL state pointer.\n");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  else {
    *param_1 = DAT_00632510;
    for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
      param_1[local_8 + 6] = 0;
      param_1[local_8 + 1] = 0;
    }
    for (local_c = DAT_00632510; local_c != (undefined4 *)0x0; local_c = (undefined4 *)*local_c) {
      if ((local_c[5] & 0xffff) < 5) {
        param_1[(local_c[5] & 0xffff) + 1] = param_1[(local_c[5] & 0xffff) + 1] + 1;
        param_1[(local_c[5] & 0xffff) + 6] = param_1[(local_c[5] & 0xffff) + 6] + local_c[4];
      }
      else {
        iVar2 = FUN_0047a120(0,0,0,0,"Bad memory block found at 0x%08X.\n",local_c);
        if (iVar2 == 1) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
      }
    }
    param_1[0xb] = DAT_00632518;
    param_1[0xc] = DAT_0063250c;
  }
  return;
}
```

---

---

## FUN_00476560 — 0x476560

- Classification : internal
- Corps : `0x476560–0x476682`
- État : pseudocode obtenu
- Evidence : `ev_93eee31f5a863d4a700155ce01db5039aea47b6b8de117a23f324e29d36ac05d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x4765a1 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x4957f8` — "_CrtMemDifference: NULL state pointer.\n"

### Pseudocode Ghidra

```c
undefined4 FUN_00476560(undefined4 *param_1,int param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_c;
  int local_8;
  
  local_c = 0;
  if (((param_1 == (undefined4 *)0x0) || (param_2 == 0)) || (param_3 == 0)) {
    iVar2 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"_CrtMemDifference: NULL state pointer.\n");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      uVar3 = (*pcVar1)();
      return uVar3;
    }
    local_c = 0;
  }
  else {
    for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
      param_1[local_8 + 6] =
           *(int *)(param_3 + 0x18 + local_8 * 4) - *(int *)(param_2 + 0x18 + local_8 * 4);
      param_1[local_8 + 1] =
           *(int *)(param_3 + 4 + local_8 * 4) - *(int *)(param_2 + 4 + local_8 * 4);
      if (((param_1[local_8 + 6] != 0) || (param_1[local_8 + 1] != 0)) &&
         ((local_8 != 0 && ((local_8 != 2 || ((DAT_004a6348 & 0x10) != 0)))))) {
        local_c = 1;
      }
    }
    param_1[0xb] = *(int *)(param_3 + 0x2c) - *(int *)(param_2 + 0x2c);
    param_1[0xc] = *(int *)(param_3 + 0x30) - *(int *)(param_2 + 0x30);
    *param_1 = 0;
  }
  return local_c;
}
```

---

---

## FUN_00476690 — 0x476690

- Classification : internal
- Corps : `0x476690–0x476934`
- État : pseudocode obtenu
- Evidence : `ev_5b74594c2099b6f4b07e5fe7b0fe6797e152dc3ef0a273806872974ace01d657`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x4766bf with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x476780 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x4767b1 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x4767d9 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x476828 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x476893 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x4768f0 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x476927 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x476230` — `FID_conflict:AtlIsValidAddress`
- `0x476940` — `FUN_00476940`
- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x495820` — "Object dump complete.\n"
- `0x495838` — "crt block at 0x%08X, subtype %x, %u bytes long.\n"
- `0x49586c` — "normal block at 0x%08X, %u bytes long.\n"
- `0x495894` — "client block at 0x%08X, subtype %x, %u bytes long.\n"
- `0x4958c8` — "{%ld} "
- `0x4958d0` — "%hs(%d) : "
- `0x4958dc` — "#File Error#(%d) : "
- `0x4958f0` — "Dumping objects ->\n"

### Pseudocode Ghidra

```c
void FUN_00476690(undefined4 *param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 *local_c;
  undefined4 *local_8;
  
  local_c = (undefined4 *)0x0;
  iVar2 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"Dumping objects ->\n");
  if (iVar2 == 1) {
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if (param_1 != (undefined4 *)0x0) {
    local_c = (undefined4 *)*param_1;
  }
  local_8 = DAT_00632510;
  do {
    if ((local_8 == (undefined4 *)0x0) || (local_8 == local_c)) {
      iVar2 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"Object dump complete.\n");
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      return;
    }
    if ((((local_8[5] & 0xffff) != 3) && ((local_8[5] & 0xffff) != 0)) &&
       (((local_8[5] & 0xffff) != 2 || ((DAT_004a6348 & 0x10) != 0)))) {
      if (local_8[2] != 0) {
        iVar2 = FID_conflict_AtlIsValidAddress(local_8[2],1,0);
        if (iVar2 == 0) {
          iVar2 = FUN_0047a120(0,0,0,0,"#File Error#(%d) : ",local_8[3]);
          if (iVar2 == 1) {
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
        }
        else {
          iVar2 = FUN_0047a120(0,0,0,0,"%hs(%d) : ",local_8[2],local_8[3]);
          if (iVar2 == 1) {
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
        }
      }
      iVar2 = FUN_0047a120(0,0,0,0,"{%ld} ",local_8[6]);
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      if ((local_8[5] & 0xffff) == 4) {
        iVar2 = FUN_0047a120(0,0,0,0,"client block at 0x%08X, subtype %x, %u bytes long.\n",
                             local_8 + 8,(int)local_8[5] >> 0x10 & 0xffff,local_8[4]);
        if (iVar2 == 1) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        if (DAT_00633e8c == (code *)0x0) {
          FUN_00476940(local_8);
        }
        else {
          (*DAT_00633e8c)(local_8 + 8,local_8[4]);
        }
      }
      else if (local_8[5] == 1) {
        iVar2 = FUN_0047a120(0,0,0,0,"normal block at 0x%08X, %u bytes long.\n",local_8 + 8,
                             local_8[4]);
        if (iVar2 == 1) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        FUN_00476940(local_8);
      }
      else if ((local_8[5] & 0xffff) == 2) {
        iVar2 = FUN_0047a120(0,0,0,0,"crt block at 0x%08X, subtype %x, %u bytes long.\n",local_8 + 8
                             ,(int)local_8[5] >> 0x10 & 0xffff,local_8[4]);
        if (iVar2 == 1) {
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        FUN_00476940(local_8);
      }
    }
    local_8 = (undefined4 *)*local_8;
  } while( true );
}
```

---

---

## FUN_00476940 — 0x476940

- Classification : internal
- Corps : `0x476940–0x476a53`
- État : pseudocode obtenu
- Evidence : `ev_521a483b3872c8bed5c830830208b6e937c73b5668d104f80c403e27e35ae5d9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x476a46 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x472ca0` — `FUN_00472ca0`
- `0x47a120` — `FUN_0047a120`
- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- `0x495904` — " Data: <%s> %s\n"
- `0x495914` — "%.2X "

### Pseudocode Ghidra

```c
void FUN_00476940(int param_1)

{
  byte bVar1;
  code *pcVar2;
  byte bVar3;
  int iVar4;
  uint local_5c;
  int local_58;
  int local_50;
  byte local_4c [20];
  undefined1 local_38 [52];
  
  local_50 = 0;
  while( true ) {
    if (*(int *)(param_1 + 0x10) < 0x10) {
      local_58 = *(int *)(param_1 + 0x10);
    }
    else {
      local_58 = 0x10;
    }
    if (local_58 <= local_50) break;
    bVar1 = *(byte *)(param_1 + local_50 + 0x20);
    if (DAT_004a87f4 < 2) {
      local_5c = *(ushort *)(PTR_DAT_004a85e8 + (uint)bVar1 * 2) & 0x157;
    }
    else {
      local_5c = FUN_0047f2b0(bVar1,0x157);
    }
    bVar3 = bVar1;
    if (local_5c == 0) {
      bVar3 = 0x20;
    }
    local_4c[local_50] = bVar3;
    FUN_00472ca0(local_38 + local_50 * 3,"%.2X ",bVar1);
    local_50 = local_50 + 1;
  }
  local_4c[local_50] = 0;
  iVar4 = FUN_0047a120(0,0,0,0," Data: <%s> %s\n",local_4c,local_38);
  if (iVar4 == 1) {
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  return;
}
```

---

---

## FUN_00476a60 — 0x476a60

- Classification : internal
- Corps : `0x476a60–0x476ad3`
- État : pseudocode obtenu
- Evidence : `ev_d237bb6821ee9fffd22286867e1c3094f0705e582d23f2240889ecddc561495b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x476ab3 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x476400` — `FUN_00476400`
- `0x476690` — `FUN_00476690`
- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x49591c` — "Detected memory leaks!\n"

### Pseudocode Ghidra

```c
undefined4 FUN_00476a60(void)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_38 [8];
  int local_30;
  int local_2c;
  int local_24;
  
  FUN_00476400(local_38);
  if (((local_24 == 0) && (local_30 == 0)) && (((DAT_004a6348 & 0x10) == 0 || (local_2c == 0)))) {
    uVar3 = 0;
  }
  else {
    iVar2 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"Detected memory leaks!\n");
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      uVar3 = (*pcVar1)();
      return uVar3;
    }
    FUN_00476690(0);
    uVar3 = 1;
  }
  return uVar3;
}
```

---

---

## FUN_00476ae0 — 0x476ae0

- Classification : internal
- Corps : `0x476ae0–0x476ba4`
- État : pseudocode obtenu
- Evidence : `ev_a035517afd6baf2937153ad9df7d8cbb54f8c7411c7ebc63954167ba540e5e61`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x476b45 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x476b6f with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x476b97 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x47a120` — `FUN_0047a120`

### Chaînes référencées

- `0x495934` — "Total allocations: %ld bytes.\n"
- `0x495954` — "Largest number used: %ld bytes.\n"
- `0x495978` — "%ld bytes in %ld %hs Blocks.\n"

### Pseudocode Ghidra

```c
void FUN_00476ae0(int param_1)

{
  code *pcVar1;
  int iVar2;
  int local_8;
  
  if (param_1 != 0) {
    for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
      iVar2 = FUN_0047a120(0,0,0,0,"%ld bytes in %ld %hs Blocks.\n",
                           *(undefined4 *)(param_1 + 0x18 + local_8 * 4),
                           *(undefined4 *)(param_1 + 4 + local_8 * 4),(&PTR_DAT_004a6360)[local_8]);
      if (iVar2 == 1) {
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
    }
    iVar2 = FUN_0047a120(0,0,0,0,"Largest number used: %ld bytes.\n",*(undefined4 *)(param_1 + 0x2c)
                        );
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    iVar2 = FUN_0047a120(0,0,0,0,"Total allocations: %ld bytes.\n",*(undefined4 *)(param_1 + 0x30));
    if (iVar2 == 1) {
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  return;
}
```

---

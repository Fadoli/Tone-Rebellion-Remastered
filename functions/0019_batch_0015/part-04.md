# 0019_batch_0015 — détails (4/6)

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

## FUN_00476f20 — 0x476f20

- Classification : internal
- Corps : `0x476f20–0x476ff8`
- État : pseudocode obtenu
- Evidence : `ev_1b8ee176602d114820be74a790cb81817d321f15949c6804ec035c738b2f1054`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x476fef to EXTERNAL:0xd KERNEL32.DLL::ExitProcess (external=true, thunk=false, hasNoReturn=true); fallthrough is excluded by Ghidra's flow model. This records Ghidra's FunctionManager flag, not an independent verification that the callee cannot return.

### Appels directs

- `EXTERNAL:0xd` — `KERNEL32.DLL::ExitProcess`
- `EXTERNAL:0x2f` — `KERNEL32.DLL::TerminateProcess`
- `EXTERNAL:0x41` — `KERNEL32.DLL::GetCurrentProcess`
- `0x4761a0` — `FUN_004761a0`
- `0x476a60` — `FUN_00476a60`
- `0x477000` — `__initterm`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00476f20(UINT param_1,int param_2,int param_3)

{
  HANDLE hProcess;
  uint uVar1;
  UINT uExitCode;
  int *local_8;
  
  if (DAT_00632564 == 1) {
    uExitCode = param_1;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
  }
  _DAT_00632560 = 1;
  DAT_0063255c = (undefined1)param_3;
  if (param_2 == 0) {
    if (DAT_00633e88 != (int *)0x0) {
      local_8 = DAT_00633e78;
      while (local_8 = local_8 + -1, DAT_00633e88 <= local_8) {
        if (*local_8 != 0) {
          (*(code *)*local_8)();
        }
      }
    }
    __initterm(&DAT_00498768,&DAT_00498970);
  }
  __initterm(&DAT_00498a74,&DAT_00498c7c);
  if ((DAT_00632568 == 0) && (uVar1 = FUN_004761a0(0xffffffff), (uVar1 & 0x20) != 0)) {
    DAT_00632568 = 1;
    FUN_00476a60();
  }
  if (param_3 == 0) {
    DAT_00632564 = 1;
                    /* WARNING: Subroutine does not return */
    ExitProcess(param_1);
  }
  return;
}
```

---

## __initterm — 0x477000

- Classification : internal
- Corps : `0x477000–0x477024`
- État : pseudocode obtenu
- Evidence : `ev_a5b84bcbb634928e51ac7ef425d4f2368fdf928d392b191bd7b99f0a1f07d5a5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __initterm
   
   Library: Visual Studio 2003 Debug */

void __initterm(int *param_1,int *param_2)

{
  for (; param_1 < param_2; param_1 = param_1 + 1) {
    if (*param_1 != 0) {
      (*(code *)*param_1)();
    }
  }
  return;
}
```

---

## FUN_00477030 — 0x477030

- Classification : internal
- Corps : `0x477030–0x4770a1`
- État : pseudocode obtenu
- Evidence : `ev_57a584137e847c94289b97f6f0701a64beeaff44e9c71d6802d0fa6219cb0049`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472e90` — `_strlen`
- `0x47f2b0` — `FUN_0047f2b0`
- `0x47f730` — `FUN_0047f730`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
float10 FUN_00477030(byte *param_1)

{
  size_t sVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint local_8;
  
  while( true ) {
    if (DAT_004a87f4 < 2) {
      local_8 = *(ushort *)(PTR_DAT_004a85e8 + (uint)*param_1 * 2) & 8;
    }
    else {
      local_8 = FUN_0047f2b0(*param_1,8);
    }
    if (local_8 == 0) break;
    param_1 = param_1 + 1;
  }
  uVar4 = 0;
  uVar3 = 0;
  sVar1 = _strlen((char *)param_1);
  iVar2 = FUN_0047f730(param_1,sVar1,uVar3,uVar4);
  return (float10)*(double *)(iVar2 + 0x10);
}
```

---

## FUN_004770b0 — 0x4770b0

- Classification : internal
- Corps : `0x4770b0–0x4771ae`
- État : pseudocode obtenu
- Evidence : `ev_b519a6417f2b7f4aec0b24c729aa198cccb209bf1653fe4bd3daf6f4bcfe43c2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004770b0(byte *param_1)

{
  byte *pbVar1;
  uint uVar2;
  uint local_18;
  uint local_14;
  int local_c;
  uint local_8;
  
  while( true ) {
    if (DAT_004a87f4 < 2) {
      local_14 = *(ushort *)(PTR_DAT_004a85e8 + (uint)*param_1 * 2) & 8;
    }
    else {
      local_14 = FUN_0047f2b0(*param_1,8);
    }
    if (local_14 == 0) break;
    param_1 = param_1 + 1;
  }
  uVar2 = (uint)*param_1;
  if ((uVar2 == 0x2d) || (pbVar1 = param_1 + 1, local_8 = uVar2, uVar2 == 0x2b)) {
    local_8 = (uint)param_1[1];
    pbVar1 = param_1 + 2;
  }
  param_1 = pbVar1;
  local_c = 0;
  while( true ) {
    if (DAT_004a87f4 < 2) {
      local_18 = *(ushort *)(PTR_DAT_004a85e8 + local_8 * 2) & 4;
    }
    else {
      local_18 = FUN_0047f2b0(local_8,4);
    }
    if (local_18 == 0) break;
    local_c = local_c * 10 + -0x30 + local_8;
    local_8 = (uint)*param_1;
    param_1 = param_1 + 1;
  }
  if (uVar2 == 0x2d) {
    local_c = -local_c;
  }
  return local_c;
}
```

---

## FUN_004771b0 — 0x4771b0

- Classification : internal
- Corps : `0x4771b0–0x4771c0`
- État : pseudocode obtenu
- Evidence : `ev_48af362f9a14af5fbba82aca1a9bc0886ae8dd10c828130d925be591673519d9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4770b0` — `FUN_004770b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004771b0(undefined4 param_1)

{
  FUN_004770b0(param_1);
  return;
}
```

---


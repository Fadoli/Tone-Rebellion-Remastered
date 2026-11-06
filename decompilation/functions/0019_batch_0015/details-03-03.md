# 0019_batch_0015 — détails (3/3)

## FUN_00475e40 — 0x475e40

- Classification : internal
- Corps : `0x475e40–0x476180`
- État : pseudocode obtenu
- Evidence : `ev_83038c24f1674e0ab7ebdb72116a2f215267b86e031cb0f6caf0e118160c574a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x475ec4 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475eef with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475f17 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475f3f with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x475f67 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x476032 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x47608f with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x4760e8 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x476131 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x476164 with no resolved callee; its no-return basis is unknown.

### Appels directs

- `0x475db0` — `FUN_00475db0`
- `0x47a120` — `FUN_0047a120`
- `0x47e280` — `FUN_0047e280`

### Chaînes référencées

- `0x495598` — "DAMAGE: after %hs block (#%d) at 0x%08X.\n"
- `0x4955c4` — "DAMAGE: before %hs block (#%d) at 0x%08X.\n"
- `0x495670` — "%hs located at 0x%08X is %u bytes long.\n"
- `0x49569c` — "%hs allocated at file %hs(%d).\n"
- `0x4956bc` — "DAMAGE: on top of Free block at 0x%08X.\n"
- `0x4956e8` — "DAMAGED"
- `0x4956f0` — "_heapchk fails with unknown return value!\n"
- `0x49571c` — "_heapchk fails with _HEAPBADPTR.\n"
- `0x495740` — "_heapchk fails with _HEAPBADEND.\n"
- `0x495764` — "_heapchk fails with _HEAPBADNODE.\n"
- `0x495788` — "_heapchk fails with _HEAPBADBEGIN.\n"

### Pseudocode Ghidra

```c
undefined4 FUN_00475e40(void)

{
  code *pcVar1;
  bool bVar2;
  int iVar3;
  undefined4 uVar4;
  char *local_18;
  undefined4 *local_c;
  undefined4 local_8;
  
  local_8 = 1;
  if ((DAT_004a6348 & 1) == 0) {
    local_8 = 1;
  }
  else {
    iVar3 = FUN_0047e280();
    if ((iVar3 == -1) || (iVar3 == -2)) {
      for (local_c = DAT_00632510; local_c != (undefined4 *)0x0; local_c = (undefined4 *)*local_c) {
        bVar2 = true;
        if (((((local_c[5] & 0xffff) == 4) || (local_c[5] == 1)) || ((local_c[5] & 0xffff) == 2)) ||
           (local_c[5] == 3)) {
          local_18 = (&PTR_DAT_004a6360)[local_c[5] & 0xffff];
        }
        else {
          local_18 = "DAMAGED";
        }
        iVar3 = FUN_00475db0(local_c + 7,DAT_004a6354,4);
        if (iVar3 == 0) {
          iVar3 = FUN_0047a120(0,0,0,0,"DAMAGE: before %hs block (#%d) at 0x%08X.\n",local_18,
                               local_c[6],local_c + 8);
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          bVar2 = false;
        }
        iVar3 = FUN_00475db0((int)local_c + local_c[4] + 0x20,DAT_004a6354,4);
        if (iVar3 == 0) {
          iVar3 = FUN_0047a120(0,0,0,0,"DAMAGE: after %hs block (#%d) at 0x%08X.\n",local_18,
                               local_c[6],local_c + 8);
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          bVar2 = false;
        }
        if ((local_c[5] == 0) &&
           (iVar3 = FUN_00475db0(local_c + 8,DAT_004a6358,local_c[4]), iVar3 == 0)) {
          iVar3 = FUN_0047a120(0,0,0,0,"DAMAGE: on top of Free block at 0x%08X.\n",local_c + 8);
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          bVar2 = false;
        }
        if (!bVar2) {
          if ((local_c[2] != 0) &&
             (iVar3 = FUN_0047a120(0,0,0,0,"%hs allocated at file %hs(%d).\n",local_18,local_c[2],
                                   local_c[3]), iVar3 == 1)) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          iVar3 = FUN_0047a120(0,0,0,0,"%hs located at 0x%08X is %u bytes long.\n",local_18,
                               local_c + 8,local_c[4]);
          if (iVar3 == 1) {
            pcVar1 = (code *)swi(3);
            uVar4 = (*pcVar1)();
            return uVar4;
          }
          local_8 = 0;
        }
      }
    }
    else {
      switch(iVar3) {
      case -6:
        iVar3 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"_heapchk fails with _HEAPBADPTR.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      case -5:
        iVar3 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"_heapchk fails with _HEAPBADEND.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      case -4:
        iVar3 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"_heapchk fails with _HEAPBADNODE.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      case -3:
        iVar3 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"_heapchk fails with _HEAPBADBEGIN.\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
        break;
      default:
        iVar3 = FUN_0047a120(0,0,0,0,&DAT_004952e8,"_heapchk fails with unknown return value!\n");
        if (iVar3 == 1) {
          pcVar1 = (code *)swi(3);
          uVar4 = (*pcVar1)();
          return uVar4;
        }
      }
      local_8 = 0;
    }
  }
  return local_8;
}
```

---

---

## FUN_004761a0 — 0x4761a0

- Classification : internal
- Corps : `0x4761a0–0x4761c1`
- État : pseudocode obtenu
- Evidence : `ev_07597156be0a44ccb5d3d3f89d71ddfc20471393821ec3b2636f7443833dbd83`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004761a0(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_004a6348;
  if (param_1 != -1) {
    DAT_004a6348 = param_1;
  }
  return iVar1;
}
```

---

---

## FUN_004761d0 — 0x4761d0

- Classification : internal
- Corps : `0x4761d0–0x476222`
- État : pseudocode obtenu
- Evidence : `ev_23cd0f2afa963256366b3f11ac58a1feda6595f5d1f9e20c484220b6b7572858`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004761d0(code *param_1,undefined4 param_2)

{
  undefined4 *local_8;
  
  if ((DAT_004a6348 & 1) != 0) {
    for (local_8 = DAT_00632510; local_8 != (undefined4 *)0x0; local_8 = (undefined4 *)*local_8) {
      if ((local_8[5] & 0xffff) == 4) {
        (*param_1)(local_8 + 8,param_2);
      }
    }
  }
  return;
}
```

---

## FID_conflict:AtlIsValidAddress — 0x476230

- Classification : internal
- Corps : `0x476230–0x47627a`
- État : pseudocode obtenu
- Evidence : `ev_1cbe4d2e851ecd2e1066348c2958b11d567296a60d918df70941f2bc1073c6d4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xe` — `KERNEL32.DLL::IsBadReadPtr`
- `EXTERNAL:0x3c` — `KERNEL32.DLL::IsBadWritePtr`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Multiple Matches With Different Base Names
    int __cdecl ATL::AtlIsValidAddress(void const *,unsigned int,int)
    __CrtIsValidPointer
   
   Library: Visual Studio 2003 Debug */

undefined4 FID_conflict_AtlIsValidAddress(void *param_1,UINT_PTR param_2,int param_3)

{
  BOOL BVar1;
  
  if (((param_1 != (void *)0x0) && (BVar1 = IsBadReadPtr(param_1,param_2), BVar1 == 0)) &&
     ((param_3 == 0 || (BVar1 = IsBadWritePtr(param_1,param_2), BVar1 == 0)))) {
    return 1;
  }
  return 0;
}
```

---

---

## FUN_00476280 — 0x476280

- Classification : internal
- Corps : `0x476280–0x47630f`
- État : pseudocode obtenu
- Evidence : `ev_90a34d2f2cee8cf98e048a12e7f9b89ea9320643c5baa10b5ed017025fda5a3d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0xf` — `KERNEL32.DLL::HeapValidate`
- `0x476230` — `FID_conflict:AtlIsValidAddress`
- `0x47e790` — `FUN_0047e790`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
BOOL FUN_00476280(int param_1)

{
  BOOL BVar1;
  int iVar2;
  undefined1 local_10 [4];
  char *local_c;
  undefined1 local_8 [4];
  
  if (param_1 == 0) {
    BVar1 = 0;
  }
  else {
    iVar2 = FID_conflict_AtlIsValidAddress(param_1 + -0x20,0x20,1);
    if (iVar2 == 0) {
      BVar1 = 0;
    }
    else {
      local_c = (char *)FUN_0047e790(param_1 + -0x20,local_10,local_8);
      if (local_c == (char *)0x0) {
        if ((DAT_00632528 & 0x8000) == 0) {
          BVar1 = HeapValidate(DAT_00633d04,0,(LPCVOID)(param_1 + -0x20));
        }
        else {
          BVar1 = 1;
        }
      }
      else if (*local_c == '\0') {
        BVar1 = 0;
      }
      else {
        BVar1 = 1;
      }
    }
  }
  return BVar1;
}
```

---

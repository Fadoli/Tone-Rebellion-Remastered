# 0019_batch_0015 — détails (6/6)

## FUN_004781f0 — 0x4781f0

- Classification : internal
- Corps : `0x4781f0–0x4781f9`
- État : pseudocode obtenu
- Evidence : `ev_ec58495b7804469bf604e00ad23c064b4c8880de5843d1f3bddb15aec01578ef`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x4781f5 to 0x480a55 __ctrandisp1 (external=false, thunk=false, hasNoReturn=false); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.

### Appels directs

- `0x480a55` — `__ctrandisp1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004781f0(void)

{
  __ctrandisp1();
  return;
}
```

---

## `eh_vector_constructor_iterator' — 0x478210

- Classification : internal
- Corps : `0x478210–0x478280`
- État : pseudocode obtenu
- Evidence : `ev_d8b32dc6d85d66789ba9af7394a26f52c220855345958f21b8071860a8b6ae9a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted. Ghidra Listing reports a terminal call at 0x47827f to 0x47829d FUN_0047829d (external=false, thunk=false, hasNoReturn=false); fallthrough is excluded by Ghidra's flow model. The reason for the terminal flow is not established by this observation.

### Appels directs

- `0x478281` — `FUN_00478281`
- `0x47829d` — `FUN_0047829d`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    void __stdcall `eh vector constructor iterator'(void *,unsigned int,int,void (__thiscall*)(void
   *),void (__thiscall*)(void *))
   
   Libraries: Visual Studio 2003 Debug, Visual Studio 2003 Release */

void _eh_vector_constructor_iterator_
               (void *param_1,uint param_2,int param_3,_func_void_void_ptr *param_4,
               _func_void_void_ptr *param_5)

{
  undefined4 unaff_EBX;
  undefined4 unaff_ESI;
  void *unaff_EDI;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar1;
  int iVar2;
  undefined4 uStack_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  puStack_c = &DAT_004959b0;
  puStack_10 = &LAB_00480ac8;
  uStack_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_14;
  local_8 = 0;
  for (iVar2 = 0; iVar2 < param_3; iVar2 = iVar2 + 1) {
    (*param_4)(unaff_EDI);
  }
  uVar1 = 1;
  local_8 = 0xffffffff;
  FUN_00478281();
  FUN_0047829d(unaff_ESI,unaff_EBX,uVar1,iVar2);
  return;
}
```

---

## FUN_00478281 — 0x478281

- Classification : internal
- Corps : `0x478281–0x47829c`
- État : pseudocode obtenu
- Evidence : `ev_155e78ef9aa6672838696097b2a54d2cff4d442a32ed2c68d5edfed30cf83a58`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x478360` — `FUN_00478360`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00478281(void)

{
  int unaff_EBP;
  
  if (*(int *)(unaff_EBP + -0x20) == 0) {
    FUN_00478360(*(undefined4 *)(unaff_EBP + 8),*(undefined4 *)(unaff_EBP + 0xc),
                 *(undefined4 *)(unaff_EBP + -0x1c),*(undefined4 *)(unaff_EBP + 0x18));
  }
  return;
}
```

---

## FUN_0047829d — 0x47829d

- Classification : internal
- Corps : `0x47829d–0x4782af`
- État : pseudocode obtenu
- Evidence : `ev_6c59bf92f87ca44893d59bdae6daeb9a8765418974fbb9c6da96c57870d54995`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047829d(void)

{
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET;
  
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0x10);
  return;
}
```

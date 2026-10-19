# 0018_batch_0014 — détails (1/3)

## FUN_0046ff6f — 0x46ff6f

- Classification : internal
- Corps : `0x46ff6f–0x470131`
- État : pseudocode obtenu
- Evidence : `ev_940528e0543fcfbd809a77f2700e26661dd502963e607f4873bc6666a4c1716d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402013` — `thunk_FUN_0045aafd`
- `0x474b90` — `FUN_00474b90`

### Chaînes référencées

- `0x4a5e90` — "tribex"
- `0x4a5e90` — "tribex"
- `0x4a5e90` — "tribex"
- `0x4a5e98` — "tribex"
- `0x4a5e98` — "tribex"
- `0x4a5e98` — "tribex"

### Pseudocode Ghidra

```c
int FUN_0046ff6f(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  int local_68;
  char local_64 [4];
  char local_60;
  char cStack_5f;
  char local_5e;
  undefined2 local_5d;
  undefined1 local_5b;
  char local_5a [4];
  char local_56;
  char cStack_55;
  char local_54;
  undefined2 local_53;
  undefined1 local_51;
  undefined3 local_50;
  char cStack_4d;
  undefined1 local_4c;
  undefined4 local_4b;
  undefined1 local_47;
  undefined4 local_46;
  undefined1 local_42;
  undefined4 local_41;
  undefined1 local_3d;
  undefined4 local_3c;
  undefined1 local_38;
  undefined4 local_37;
  undefined1 local_33;
  undefined4 local_32;
  undefined1 local_2e;
  undefined4 local_2d;
  undefined1 local_29;
  undefined4 local_28;
  undefined1 local_24;
  undefined4 local_23;
  undefined1 local_1f;
  undefined4 local_1e;
  undefined2 local_1a;
  undefined4 local_18;
  undefined4 local_14;
  undefined2 local_10;
  undefined4 local_e;
  int local_8;
  
  local_64 = (char  [4])s_tribex_004a5e90._0_4_;
  local_5e = s_tribex_004a5e90[6];
  local_5d = 0;
  local_5b = 0;
  local_5a = (char  [4])s_tribex_004a5e98._0_4_;
  local_54 = s_tribex_004a5e98[6];
  local_53 = 0;
  local_51 = 0;
  local_4c = DAT_004a5ea4;
  local_4b = 0;
  local_47 = 0;
  local_46 = DAT_004a5ea8;
  local_42 = DAT_004a5eac;
  local_41 = 0;
  local_3d = 0;
  local_3c = DAT_004a5eb0;
  local_38 = DAT_004a5eb4;
  local_37 = 0;
  local_33 = 0;
  local_32 = DAT_004a5eb8;
  local_2e = DAT_004a5ebc;
  local_2d = 0;
  local_29 = 0;
  local_28 = DAT_004a5ec0;
  local_24 = DAT_004a5ec4;
  local_23 = 0;
  local_1f = 0;
  local_1e = DAT_004a5ec8;
  local_1a = DAT_004a5ecc;
  local_18 = 0;
  local_14 = DAT_004a5ed0;
  local_10 = DAT_004a5ed4;
  local_e = 0;
  local_8 = DAT_0049f538;
  if (DAT_0049f538 < 0) {
    local_8 = 0;
  }
  if (3 < local_8) {
    local_8 = 3;
  }
  cVar1 = (char)local_8;
  _local_60 = CONCAT11(cVar1 + '0',(char)s_tribex_004a5e90._4_2_);
  _local_56 = CONCAT11(cVar1 + '0',(char)s_tribex_004a5e98._4_2_);
  _local_50 = CONCAT13(cVar1 + '1',(int3)DAT_004a5ea0);
  do {
    iVar2 = (int)DAT_006191b4;
    if (iVar2 == 0) {
      local_68 = FUN_00474b90();
      iVar2 = local_68 / 9;
      local_68 = local_68 % 9;
    }
    else if (*(int *)(DAT_0049f538 * 0x14a0 + 0x619248) == 0) {
      local_68 = 8;
    }
    else {
      local_68 = -99;
    }
  } while ((DAT_004a5e88 == local_68) && (iVar2 = (int)DAT_006191b4, iVar2 == 0));
  if (-1 < local_68) {
    iVar2 = thunk_FUN_0045aafd(local_64 + local_68 * 10,0,0,param_1);
  }
  DAT_004a5e88 = local_68;
  return iVar2;
}
```

---

---

## FUN_00470132 — 0x470132

- Classification : internal
- Corps : `0x470132–0x470197`
- État : pseudocode obtenu
- Evidence : `ev_c69448077a5f907ec97c36c319503cc68169b484a586d310251f9980438af447`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401cbc` — `thunk_FUN_00429243`
- `0x4022c0` — `thunk_FUN_00471aa8`
- `0x40236f` — `thunk_FUN_004701ef`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_00470132(void)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004920a8;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00429243();
  local_8 = 0;
  thunk_FUN_00471aa8();
  local_8 = CONCAT31(local_8._1_3_,1);
  *in_ECX = &PTR_LAB_004947c0;
  thunk_FUN_004701ef();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## COleResizeBar::~COleResizeBar — 0x470198

- Classification : internal
- Corps : `0x470198–0x4701ee`
- État : pseudocode obtenu
- Evidence : `ev_1b126dbb2534174da00c3ee338d64e9ee32c6c2cd830d3a91b452d2145fb2dee`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40178f` — `thunk_FUN_00471abe`
- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    public: virtual __thiscall COleResizeBar::~COleResizeBar(void)
   
   Library: Visual Studio 2003 Debug */

void __thiscall COleResizeBar::~COleResizeBar(COleResizeBar *this)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_004920bb;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  *(undefined ***)this = &PTR_LAB_004947c0;
  local_8 = 0;
  thunk_FUN_00471abe();
  local_8 = 0xffffffff;
  thunk_FUN_00429262();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

---

## FUN_004701ef — 0x4701ef

- Classification : internal
- Corps : `0x4701ef–0x470258`
- État : pseudocode obtenu
- Evidence : `ev_7c48970b926a88c050fc546badd96ec27c575ce1d456fecdf0a58d891af8d2e9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401acd` — `thunk_FUN_0040ebde`

### Chaînes référencées

- `0x4a5ed8` — "smisle"

### Pseudocode Ghidra

```c
void FUN_004701ef(void)

{
  undefined2 uVar1;
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x76) = 0xffff;
  *(undefined4 *)(in_ECX + 0x788) = 0;
  *(undefined2 *)(in_ECX + 0x678) = 0;
  *(undefined4 *)(in_ECX + 0x67c) = 0;
  *(undefined4 *)(in_ECX + 0x790) = 0x3e051eb8;
  *(undefined4 *)(in_ECX + 0x794) = 0x3d75c28f;
  uVar1 = thunk_FUN_0040ebde(s_smisle_004a5ed8);
  *(undefined2 *)(in_ECX + 0x74) = uVar1;
  return;
}
```

---

---

## FUN_00470259 — 0x470259

- Classification : internal
- Corps : `0x470259–0x4702b5`
- État : pseudocode obtenu
- Evidence : `ev_9c391dac376cfaba40258412828bb7967a76d60c13ccdf105f3406beabd1e24d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40233d` — `thunk_FUN_004702b6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00470259(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x70) = 0xc000;
  *(short *)(in_ECX + 0x784) = (short)((*(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0xc)) / 2);
  *(short *)(in_ECX + 0x786) =
       (short)((*(int *)(in_ECX + 0x18) - *(int *)(in_ECX + 0x10)) / 2) + 0xf;
  thunk_FUN_004702b6();
  return 1;
}
```

---

---

## FUN_004702b6 — 0x4702b6

- Classification : internal
- Corps : `0x4702b6–0x4702cd`
- État : pseudocode obtenu
- Evidence : `ev_1b042bb60854e5ce08cf72423ce9322d15dc3c4929c3054067da18f18f20fc82`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004702b6(void)

{
  int in_ECX;
  
  *(undefined4 *)(in_ECX + 0x78c) = 0;
  return;
}
```

---

---

## FUN_004702ce — 0x4702ce

- Classification : internal
- Corps : `0x4702ce–0x4702d8`
- État : pseudocode obtenu
- Evidence : `ev_9866ffd2a66cb964d620fbb633300cfb34d595497357a2da2e1e5de9dc473907`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004702ce(void)

{
  return;
}
```

---

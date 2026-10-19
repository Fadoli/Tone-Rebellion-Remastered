# 0018_batch_0014 — détails (4/6)

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

## FUN_004702d9 — 0x4702d9

- Classification : internal
- Corps : `0x4702d9–0x470ed8`
- État : pseudocode obtenu
- Evidence : `ev_aa3ab1b38d33c060b5a68075da723f864d3aab2e2801b905d45e64d5661e2962`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x401564` — `thunk_FUN_00470fe7`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401a23` — `thunk_FUN_0046bb7f`
- `0x401b4a` — `thunk_FUN_0040e864`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401e42` — `thunk_FUN_004714ae`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402013` — `thunk_FUN_0045aafd`
- `0x402022` — `thunk_FUN_00406604`
- `0x4020b8` — `thunk_FUN_0046bc7e`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x402117` — `thunk_FUN_00471536`
- `0x40218a` — `thunk_FUN_00410765`
- `0x40229d` — `thunk_FUN_00405e11`
- `0x4022c5` — `thunk_FUN_004702ce`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x4023ab` — `thunk_FUN_00471b5c`
- `0x4023d3` — `thunk_FUN_0046b928`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x4024b4` — `thunk_FUN_00470f67`

### Chaînes référencées

- `0x4a5ee0` — "mIsleHandle!=HCACHE_INVALID"
- `0x4a5efc` — "C:\\float\\src\\worldwin.cpp"
- `0x4a5f18` — "paradise"
- `0x4a5f24` — "paraglow"
- `0x4a5f30` — "data\\mainmap.pal"
- `0x4a5f44` — "shape"
- `0x4a5f4c` — "C:\\float\\src\\worldwin.cpp"
- `0x4a5f68` — "mVisible == TRUE"
- `0x4a5f7c` — "C:\\float\\src\\worldwin.cpp"
- `0x4a5fd8` — "start"
- `0x4a5fd8` — "start"
- `0x4a6008` — "winend"
- `0x4a6008` — "winend"
- `0x4a6008` — "winend"
- `0x4a6010` — "loosend"
- `0x4a6010` — "loosend"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004702d9(short param_1,int param_2,uint param_3)

{
  undefined1 uVar1;
  int iVar2;
  undefined4 uVar3;
  int *in_ECX;
  undefined2 extraout_var;
  undefined4 *unaff_FS_OFFSET;
  uint local_208;
  uint local_204;
  undefined4 local_200;
  undefined4 local_1e8;
  undefined2 local_1e4;
  undefined1 local_1e2;
  undefined2 local_1e1;
  undefined1 local_1df;
  undefined4 local_1de;
  undefined2 local_1da;
  undefined1 local_1d8;
  undefined2 local_1d7;
  undefined1 local_1d5;
  undefined4 local_1d4;
  undefined2 local_1d0;
  undefined1 local_1ce;
  undefined2 local_1cd;
  undefined1 local_1cb;
  undefined4 local_1ca;
  undefined2 local_1c6;
  undefined1 local_1c4;
  undefined2 local_1c3;
  undefined1 local_1c1;
  undefined4 local_1c0;
  undefined1 local_1bc;
  undefined4 local_1bb;
  undefined1 local_1b7;
  undefined4 local_1b6;
  undefined1 local_1b2;
  undefined4 local_1b1;
  undefined1 local_1ad;
  undefined4 local_1ac;
  undefined1 local_1a8;
  undefined4 local_1a7;
  undefined1 local_1a3;
  undefined4 local_1a2;
  undefined1 local_19e;
  undefined4 local_19d;
  undefined1 local_199;
  char local_198 [4];
  char local_194 [2];
  undefined4 local_192;
  undefined4 local_18e;
  undefined2 local_18a;
  undefined4 local_188;
  undefined4 local_184;
  undefined2 local_180;
  undefined4 local_17e;
  undefined4 local_17a;
  undefined2 local_176;
  undefined4 local_174;
  undefined4 local_170;
  undefined2 local_16c;
  undefined4 local_16a;
  undefined4 local_166;
  undefined1 local_162;
  undefined4 local_161;
  undefined1 local_15d;
  char local_15c [4];
  char local_158 [2];
  char local_156;
  undefined2 local_155;
  undefined1 local_153;
  char local_152 [4];
  char local_14e [4];
  undefined2 local_14a;
  int local_148;
  uint local_144;
  int local_140;
  int local_13c;
  uint local_138;
  uint local_134;
  int local_130;
  undefined4 local_12c;
  int local_128;
  int local_124;
  int local_120;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004920d1;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  iVar2 = (int)param_1;
  if (iVar2 < 0xb) {
    if (iVar2 == 10) {
      thunk_FUN_00470f67(param_2,param_3);
    }
    else {
      switch(iVar2) {
      case 1:
        in_ECX[0xf] = 1;
        in_ECX[0xe] = 1;
        if ((short)in_ECX[0x1d] == -1) {
          thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a5efc,0xdb,
                             s_mIsleHandle__HCACHE_INVALID_004a5ee0);
        }
        _DAT_006324ac = in_ECX + 2;
        if ((DAT_006191b4 == 3) && (*(int *)(DAT_0049f538 * 0x14a0 + 0x619248) == 0)) {
          thunk_FUN_0040ec89(s_paradise_004a5f18,1);
          thunk_FUN_0040ec89(s_paraglow_004a5f24,1);
        }
        thunk_FUN_0040f6f7();
        local_8 = 0;
        thunk_FUN_0040f752(s_data_mainmap_pal_004a5f30,0x8000);
        thunk_FUN_0040fc15(&DAT_00630730,0x300);
        thunk_FUN_0040f966();
        if (DAT_006191b4 == 0) {
          thunk_FUN_00410765(&DAT_00630730,0,0);
        }
        else {
          thunk_FUN_00410765(&DAT_00630730,0,0xff);
        }
        thunk_FUN_00471b5c();
        thunk_FUN_00471536();
        thunk_FUN_0046b928(in_ECX[1],0x12e,0,0,0);
        in_ECX[0xd] = 1;
        local_8 = 0xffffffff;
        thunk_FUN_0040f73f();
        break;
      case 2:
        thunk_FUN_004293c6((int)param_1,param_2,param_3);
        thunk_FUN_0046b928(in_ECX[1],0xffffffff,0,0,0);
        break;
      default:
        goto switchD_0047033f_caseD_3;
      case 5:
        local_204 = (uint)((param_3 & 0x100) != 0);
        local_134 = local_204;
        local_208 = (uint)((param_3 & 0x200) != 0);
        local_138 = local_208;
        switch(param_2) {
        case 0x20:
          if (DAT_004c2b74 != 0) {
            (**(code **)(*in_ECX + 4))(0x12f,0,0);
          }
          break;
        case 0x25:
          if (DAT_004c2b74 != 0) {
            (**(code **)(*in_ECX + 4))(300,0,0);
          }
          break;
        case 0x26:
          if ((DAT_004c2b74 != 0) && (in_ECX[0x1c] < 0x10000)) {
            in_ECX[0x1c] = in_ECX[0x1c] + 0x1000;
          }
          break;
        case 0x27:
          if (DAT_004c2b74 != 0) {
            (**(code **)(*in_ECX + 4))(0x12d,0,0);
          }
          break;
        case 0x28:
          if ((DAT_004c2b74 != 0) && (0x1fff < in_ECX[0x1c])) {
            in_ECX[0x1c] = in_ECX[0x1c] + -0x1000;
          }
          break;
        case 0x42:
          if (DAT_004c2b74 == 0) goto switchD_0047090e_caseD_49;
          DAT_004a5e84 = (uint)(DAT_004a5e84 == 0);
          for (local_13c = 0; local_13c < 8; local_13c = local_13c + 1) {
            *(undefined4 *)(&DAT_00613734 + local_13c * 8) = 0;
          }
          break;
        case 0x49:
switchD_0047090e_caseD_49:
          if (DAT_004c2b74 != 0) {
            for (local_140 = 0; local_140 < (int)(uint)DAT_006136b0; local_140 = local_140 + 1) {
              *(undefined4 *)(&DAT_005eebc4 + DAT_0049f538 * 4 + local_140 * 0x29e8) = 1;
            }
            in_ECX[0xd] = 1;
          }
          break;
        case 0x4e:
          if (DAT_004c2b74 != 0) {
            DAT_006324a8 = (uint)(DAT_006324a8 == 0);
            iVar2 = thunk_FUN_0042d28f();
            in_ECX[2] = iVar2;
            uVar1 = thunk_FUN_0042dd0f(0);
            thunk_FUN_00406604(in_ECX + 2,uVar1);
            thunk_FUN_0042d38a();
            in_ECX[0xd] = 1;
          }
          break;
        case 0x4f:
          if (DAT_004c2b74 != 0) {
            local_144 = (uint)(local_204 == 0);
            for (local_148 = 0; local_148 < (int)(uint)DAT_006137b4; local_148 = local_148 + 1) {
              (&DAT_006136b4)[local_148 * 2] = local_144;
            }
          }
          break;
        case 0x51:
          if (DAT_004c2b74 != 0) {
            local_1e8 = DAT_004a5f98;
            local_1e4 = DAT_004a5f9c;
            local_1e2 = DAT_004a5f9e;
            local_1e1 = 0;
            local_1df = 0;
            local_1de = DAT_004a5fa0;
            local_1da = DAT_004a5fa4;
            local_1d8 = DAT_004a5fa6;
            local_1d7 = 0;
            local_1d5 = 0;
            local_1d4 = DAT_004a5fa8;
            local_1d0 = DAT_004a5fac;
            local_1ce = DAT_004a5fae;
            local_1cd = 0;
            local_1cb = 0;
            local_1ca = DAT_004a5fb0;
            local_1c6 = DAT_004a5fb4;
            local_1c4 = DAT_004a5fb6;
            local_1c3 = 0;
            local_1c1 = 0;
            local_1c0 = DAT_004a5fb8;
            local_1bc = DAT_004a5fbc;
            local_1bb = 0;
            local_1b7 = 0;
            local_1b6 = DAT_004a5fc0;
            local_1b2 = DAT_004a5fc4;
            local_1b1 = 0;
            local_1ad = 0;
            local_1ac = DAT_004a5fc8;
            local_1a8 = DAT_004a5fcc;
            local_1a7 = 0;
            local_1a3 = 0;
            local_1a2 = DAT_004a5fd0;
            local_19e = DAT_004a5fd4;
            local_19d = 0;
            local_199 = 0;
            local_198[0] = s_start_004a5fd8[0];
            local_198[1] = s_start_004a5fd8[1];
            local_198[2] = s_start_004a5fd8[2];
            local_198[3] = s_start_004a5fd8[3];
            local_194[0] = s_start_004a5fd8[4];
            local_194[1] = s_start_004a5fd8[5];
            local_192 = 0;
            local_18e = DAT_004a5fe0;
            local_18a = DAT_004a5fe4;
            local_188 = 0;
            local_184 = DAT_004a5fe8;
            local_180 = DAT_004a5fec;
            local_17e = 0;
            local_17a = DAT_004a5ff0;
            local_176 = DAT_004a5ff4;
            local_174 = 0;
            local_170 = DAT_004a5ff8;
            local_16c = DAT_004a5ffc;
            local_16a = 0;
            local_166 = DAT_004a6000;
            local_162 = DAT_004a6004;
            local_161 = 0;
            local_15d = 0;
            local_15c[0] = s_winend_004a6008[0];
            local_15c[1] = s_winend_004a6008[1];
            local_15c[2] = s_winend_004a6008[2];
            local_15c[3] = s_winend_004a6008[3];
            local_158[0] = s_winend_004a6008[4];
            local_158[1] = s_winend_004a6008[5];
            local_156 = s_winend_004a6008[6];
            local_155 = 0;
            local_153 = 0;
            local_152[0] = s_loosend_004a6010[0];
            local_152[1] = s_loosend_004a6010[1];
            local_152[2] = s_loosend_004a6010[2];
            local_152[3] = s_loosend_004a6010[3];
            local_14e[0] = s_loosend_004a6010[4];
            local_14e[1] = s_loosend_004a6010[5];
            local_14e[2] = s_loosend_004a6010[6];
            local_14e[3] = s_loosend_004a6010[7];
            local_14a = 0;
            thunk_FUN_0045aafd((int)&local_1e8 + DAT_006324b4 * 10,0,0,0);
            DAT_006324b4 = DAT_006324b4 + 1;
            if (0xf < DAT_006324b4) {
              DAT_006324b4 = 0;
            }
          }
        }
        break;
      case 6:
        if (in_ECX[1] == DAT_0062c6bc) {
          iVar2 = thunk_FUN_00470fe7(param_2,param_3);
          if (iVar2 == 0) {
            uVar3 = thunk_FUN_004293c6(CONCAT22(extraout_var,param_1),param_2,param_3);
          }
          else {
            uVar3 = 1;
          }
          goto LAB_00470ec9;
        }
      }
    }
    goto LAB_00470ec7;
  }
  switch(iVar2 + -300) {
  case 0:
  case 1:
    if (in_ECX[0xf] != 1) {
      thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a5f7c,0x112,s_mVisible____TRUE_004a5f68);
    }
    local_12c = 0;
    local_130 = in_ECX[0x1e2];
    if (param_1 == 300) {
      if ((in_ECX[0x1e2] & 1U) == 0) {
        in_ECX[0x1e2] = in_ECX[0x1e2] | 1;
        in_ECX[0x1e2] = in_ECX[0x1e2] & 0xfffffffd;
      }
      else {
        in_ECX[0x1e2] = 0;
      }
      local_12c = 3;
    }
    if (param_1 == 0x12d) {
      if ((in_ECX[0x1e2] & 1U) == 0) {
        in_ECX[0x1e2] = in_ECX[0x1e2] | 1;
        in_ECX[0x1e2] = in_ECX[0x1e2] | 2;
      }
      else {
        in_ECX[0x1e2] = 0;
      }
      local_12c = 3;
    }
    if (param_2 == 6) {
      thunk_FUN_0046bb7f(in_ECX[1],1,0x12f,local_12c,0);
    }
    uVar3 = 1;
    break;
  case 2:
    if ((in_ECX[0x1e2] & 1U) != 0) {
      if ((in_ECX[0x1e2] & 2U) == 0) {
        local_200 = 0xc0c00000;
      }
      else {
        local_200 = 0x40c00000;
      }
      thunk_FUN_004714ae(local_200);
    }
    thunk_FUN_00471536();
    in_ECX[0xd] = 1;
    goto LAB_00470ec7;
  case 3:
    in_ECX[0x1e2] = 0;
    thunk_FUN_00471536();
    in_ECX[0xd] = 1;
    thunk_FUN_0046bc7e(in_ECX[1],0x12f);
    uVar3 = 1;
    break;
  case 4:
    thunk_FUN_004702ce();
    thunk_FUN_00471536();
    in_ECX[0xd] = 1;
    uVar3 = 1;
    break;
  case 5:
    local_124 = thunk_FUN_0040e864(CONCAT22((short)((uint)(iVar2 + -300) >> 0x10),
                                            (short)in_ECX[0x1d]));
    if (local_124 == 0) {
      thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a5f4c,0x104,s_shape_004a5f44);
    }
    for (local_120 = 0; local_120 < (int)(uint)DAT_006136b0; local_120 = local_120 + 1) {
      local_128 = (int)(short)(&DAT_005eebf8)[local_120 * 0x14f4];
      thunk_FUN_00405e11(local_124,local_128,0,0,0,&DAT_006323b0 + local_120 * 0x10);
    }
    for (local_120 = 0; local_120 < 0xf; local_120 = local_120 + 1) {
      *(undefined4 *)(&DAT_00632370 + local_120 * 4) = 1;
    }
LAB_00470ec7:
    uVar3 = 0;
    break;
  default:
switchD_0047033f_caseD_3:
    uVar3 = thunk_FUN_004293c6(param_1,param_2,param_3);
  }
LAB_00470ec9:
  *unaff_FS_OFFSET = local_10;
  return uVar3;
}
```

---

## FUN_00470f67 — 0x470f67

- Classification : internal
- Corps : `0x470f67–0x470fe6`
- État : pseudocode obtenu
- Evidence : `ev_5d7dcf83aeb690c87f9dcd523775665c66c3467d321d854e172222ee79b56d56`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401e0b` — `thunk_FUN_00472013`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00470f67(undefined4 param_1,undefined4 param_2)

{
  short sVar1;
  undefined2 *puVar2;
  int in_ECX;
  
  if (DAT_006191b4 == 0) {
    sVar1 = *(short *)(in_ECX + 0x76);
    puVar2 = (undefined2 *)thunk_FUN_00472013(param_1,param_2);
    if (puVar2 == (undefined2 *)0x0) {
      *(undefined2 *)(in_ECX + 0x76) = 0xffff;
    }
    else {
      *(undefined2 *)(in_ECX + 0x76) = *puVar2;
    }
    if (sVar1 != *(short *)(in_ECX + 0x76)) {
      *(undefined4 *)(in_ECX + 0x34) = 1;
    }
  }
  else {
    *(undefined2 *)(in_ECX + 0x76) = 0xffff;
  }
  return;
}
```

---

## FUN_00470fe7 — 0x470fe7

- Classification : internal
- Corps : `0x470fe7–0x47117c`
- État : pseudocode obtenu
- Evidence : `ev_c8c3fa40d02cbbb84756413780634e899191374ea15d52a888ba5ea5c044f084`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011bd` — `thunk_FUN_0047117d`
- `0x4012cb` — `thunk_FUN_0045b8d1`
- `0x40150f` — `thunk_FUN_0046ff6f`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x402013` — `thunk_FUN_0045aafd`
- `0x472ca0` — `FUN_00472ca0`
- `0x474b90` — `FUN_00474b90`

### Chaînes référencées

- `0x4a6028` — "tribe%1d"
- `0x4a6034` — "act%1d"

### Pseudocode Ghidra

```c
undefined4 FUN_00470fe7(void)

{
  int iVar1;
  uint uVar2;
  int in_ECX;
  undefined1 local_14 [12];
  int local_8;
  
  if (((*(short *)(in_ECX + 0x76) != -1) && (DAT_006191b4 == 0)) &&
     (iVar1 = thunk_FUN_0047117d(CONCAT22(*(short *)(in_ECX + 0x76) >> 0xf,
                                          *(undefined2 *)(in_ECX + 0x76))), iVar1 != 0)) {
    DAT_0049f53c = *(undefined2 *)(in_ECX + 0x76);
    thunk_FUN_0046c1b4(1,3,0);
    local_8 = (int)(short)(&DAT_005eebf8)[*(short *)(in_ECX + 0x76) * 0x14f4];
    if (*(int *)(&DAT_00632370 + (short)(&DAT_005eebf8)[*(short *)(in_ECX + 0x76) * 0x14f4] * 4) !=
        0) {
      if (local_8 == 0xe) {
        iVar1 = thunk_FUN_0045b8d1(&DAT_004a6018);
        if (iVar1 == 0) {
          thunk_FUN_0045aafd(&DAT_004a6020,0,0,0);
        }
      }
      else if (local_8 == DAT_0049f538) {
        FUN_00472ca0(local_14,s_tribe_1d_004a6028,DAT_0049f538);
        iVar1 = thunk_FUN_0045b8d1(local_14);
        if (iVar1 == 0) {
          thunk_FUN_0045aafd(local_14,0,0,0);
        }
      }
      else if (local_8 < 4) {
        FUN_00472ca0(local_14,s_act_1d_004a6034,local_8 + 1);
        iVar1 = thunk_FUN_0045b8d1(local_14);
        if (iVar1 == 0) {
          thunk_FUN_0045aafd(local_14,0,0,0);
        }
      }
      else {
        uVar2 = FUN_00474b90();
        if ((uVar2 & 1) != 0) {
          thunk_FUN_0046ff6f(0);
        }
      }
      *(undefined4 *)
       (&DAT_00632370 + (short)(&DAT_005eebf8)[*(short *)(in_ECX + 0x76) * 0x14f4] * 4) = 0;
    }
  }
  return 0;
}
```

---

## FUN_0047117d — 0x47117d

- Classification : internal
- Corps : `0x47117d–0x4711e1`
- État : pseudocode obtenu
- Evidence : `ev_6c02118291fa96e14fcc71511e9afb01b1e44cc85b53bdda2e204c08fdd086a5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047117d(short param_1)

{
  int local_8;
  
  local_8 = 0;
  while( true ) {
    if (3 < local_8) {
      return 0;
    }
    if (((*(uint *)(&DAT_004bf0f0 + DAT_004befec * 4) & 1 << ((byte)local_8 & 0x1f)) != 0) &&
       (*(int *)(&DAT_005eebc4 + local_8 * 4 + param_1 * 0x29e8) != 0)) break;
    local_8 = local_8 + 1;
  }
  return 1;
}
```

---

## FUN_004711e2 — 0x4711e2

- Classification : internal
- Corps : `0x4711e2–0x4714ad`
- État : pseudocode obtenu
- Evidence : `ev_e419f0590f1605f2f6c422dab09e4d4e72cfadd4a4dff7155135229a20dc1503`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4011bd` — `thunk_FUN_0047117d`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x402234` — `thunk_FUN_0042892d`
- `0x4022de` — `thunk_FUN_0042d9cd`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402487` — `thunk_FUN_00471e66`

### Chaînes référencées

- `0x4a4870` — "xTarzus"
- `0x4a603c` — "paradise"
- `0x4a6048` — "shape"
- `0x4a6050` — "C:\\float\\src\\worldwin.cpp"
- `0x4a606c` — "paraglow"
- `0x4a6078` — "shape"
- `0x4a6080` — "C:\\float\\src\\worldwin.cpp"
- `0x4a60a4` — "C:\\float\\src\\worldwin.cpp"

### Pseudocode Ghidra

```c
void FUN_004711e2(void)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int in_ECX;
  int iVar4;
  int local_10;
  
  if ((*(int *)(in_ECX + 0x34) != 0) && (*(int *)(in_ECX + 0x3c) != 0)) {
    uVar2 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar2;
    if ((DAT_006191b4 < 4) ||
       (((DAT_006191b4 == 4 && (DAT_006191b6 < 0x3c)) ||
        (*(int *)(DAT_0049f538 * 0x14a0 + 0x619248) != 0)))) {
      thunk_FUN_00471e66(in_ECX);
    }
    if ((3 < DAT_006191b4) && (*(int *)(DAT_0049f538 * 0x14a0 + 0x619248) == 0)) {
      if ((DAT_006191b4 != 4) || (0x3b < DAT_006191b6)) {
        iVar3 = thunk_FUN_0040ec89(s_paradise_004a603c,1);
        if (iVar3 == 0) {
          thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a6050,0x268,s_shape_004a6048);
        }
        iVar4 = DAT_006324b8 % 0x15;
        DAT_006324b8 = DAT_006324b8 + 1;
        thunk_FUN_00404770(in_ECX + 8,iVar3,iVar4,(int)*(short *)(in_ECX + 0x784),
                           (int)*(short *)(in_ECX + 0x786));
      }
      if ((DAT_006191b6 < 0x50) && (DAT_006191b4 == 4)) {
        iVar3 = thunk_FUN_0040ec89(s_paraglow_004a606c,1);
        if (iVar3 == 0) {
          thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a6080,0x271,s_shape_004a6078);
        }
        local_10 = (int)DAT_006191b6;
        if (0x3d < local_10) {
          local_10 = 0x3d - (local_10 + -0x3d);
        }
        thunk_FUN_00404770(in_ECX + 8,iVar3,local_10,(int)*(short *)(in_ECX + 0x784),
                           (int)*(short *)(in_ECX + 0x786));
      }
    }
    if (((DAT_006191b4 == 0) && (-1 < *(short *)(in_ECX + 0x76))) &&
       (iVar3 = thunk_FUN_0047117d(*(undefined2 *)(in_ECX + 0x76)), iVar3 != 0)) {
      sVar1 = (&DAT_005eebf8)[*(short *)(in_ECX + 0x76) * 0x14f4];
      iVar3 = thunk_FUN_0042de03();
      if (iVar3 == 0) {
        thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a60a4,0x27d,&DAT_004a609c);
      }
      iVar3 = thunk_FUN_0042892d(s_xTarzus_004a4870 + sVar1 * 0x20,0xffffffff,0xffffffff);
      thunk_FUN_004289c0(in_ECX + 8,(0x280 - iVar3) / 2,0x3c,s_xTarzus_004a4870 + sVar1 * 0x20);
    }
    thunk_FUN_0042d38a();
    thunk_FUN_0042d9cd(1);
    *(undefined4 *)(in_ECX + 0x34) = 0;
  }
  return;
}
```

---

## FUN_004714ae — 0x4714ae

- Classification : internal
- Corps : `0x4714ae–0x471535`
- État : pseudocode obtenu
- Evidence : `ev_54898e67522ee30189cd60335bad1cfe5fa3c55832ecc0ba40ee67e3ed7a0220`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004714ae(float param_1)

{
  int in_ECX;
  
  *(float *)(in_ECX + 0x78c) = param_1 * 0.017453277 + *(float *)(in_ECX + 0x78c);
  while (6.28318 <= *(float *)(in_ECX + 0x78c)) {
    *(float *)(in_ECX + 0x78c) = *(float *)(in_ECX + 0x78c) - 6.28318;
  }
  while (*(float *)(in_ECX + 0x78c) < 0.0) {
    *(float *)(in_ECX + 0x78c) = *(float *)(in_ECX + 0x78c) + 6.28318;
  }
  return;
}
```

---

## FUN_00471536 — 0x471536

- Classification : internal
- Corps : `0x471536–0x4718ea`
- État : pseudocode obtenu
- Evidence : `ev_232525675e1ef9f156606270bf3eebfa14a802cbecd1e151e6726403ee04b09a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401154` — `thunk_FUN_00414b91`
- `0x401979` — `thunk_FUN_00471b34`
- `0x401ae1` — `thunk_FUN_004718eb`
- `0x4023ab` — `thunk_FUN_00471b5c`
- `0x4023c4` — `thunk_FUN_00471aee`
- `0x472c6c` — `__ftol`
- `0x477314` — `FUN_00477314`
- `0x477ab4` — `FUN_00477ab4`

### Chaînes référencées

- `0x4a60c0` — "Bad DisplayItem Type"
- `0x4a60dc` — "C:\\float\\src\\worldwin.cpp"

### Pseudocode Ghidra

```c
void FUN_00471536(void)

{
  int iVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  short sVar5;
  float fVar6;
  short sVar7;
  short sVar8;
  int in_ECX;
  float10 fVar9;
  float10 fVar10;
  short *local_18;
  int local_14;
  
  thunk_FUN_004718eb();
  local_18 = (short *)(in_ECX + 0x78);
  thunk_FUN_00471b5c();
  fVar6 = ((float)(DAT_00618e44 % 0x5a0) * 0.017453277) / 4.0 + *(float *)(in_ECX + 0x78c);
  for (local_14 = 0; local_14 < *(short *)(in_ECX + 0x678); local_14 = local_14 + 1) {
    if (*(int *)(local_18 + 2) == 0) {
      sVar5 = *local_18;
      fVar3 = *(float *)(&DAT_005eebec + sVar5 * 0x29e8);
      FUN_00477ab4((double)(fVar3 - fVar6));
      fVar9 = (float10)FUN_00477314((double)(fVar3 - fVar6));
      iVar1 = *(int *)(&DAT_005eebf0 + sVar5 * 0x29e8);
      fVar3 = *(float *)(in_ECX + 0x794);
      sVar5 = *(short *)(in_ECX + 0x784);
      sVar8 = __ftol();
      local_18[4] = sVar5 + sVar8;
      sVar5 = *(short *)(in_ECX + 0x786);
      sVar8 = __ftol();
      local_18[5] = sVar5 - sVar8;
      *(float *)(local_18 + 8) = (float)(fVar9 * (float10)iVar1 * (float10)fVar3) + 3000.0;
      local_18[10] = 1;
      local_18[0xb] = 0;
      thunk_FUN_00471aee();
    }
    else if (*(int *)(local_18 + 2) == 1) {
      sVar5 = *local_18;
      sVar8 = *(short *)(&DAT_006136b8 + sVar5 * 8);
      fVar3 = *(float *)(&DAT_005eebec + sVar8 * 0x29e8);
      FUN_00477ab4((double)(fVar3 - fVar6));
      fVar9 = (float10)FUN_00477314((double)(fVar3 - fVar6));
      iVar1 = *(int *)(&DAT_005eebf0 + sVar8 * 0x29e8);
      fVar3 = *(float *)(in_ECX + 0x794);
      sVar8 = *(short *)(in_ECX + 0x784);
      sVar7 = __ftol();
      local_18[4] = sVar8 + sVar7;
      sVar8 = *(short *)(in_ECX + 0x786);
      sVar7 = __ftol();
      local_18[5] = sVar8 - sVar7;
      sVar5 = *(short *)(&DAT_006136ba + sVar5 * 8);
      fVar4 = *(float *)(&DAT_005eebec + sVar5 * 0x29e8);
      FUN_00477ab4((double)(fVar4 - fVar6));
      fVar10 = (float10)FUN_00477314((double)(fVar4 - fVar6));
      iVar2 = *(int *)(&DAT_005eebf0 + sVar5 * 0x29e8);
      fVar4 = *(float *)(in_ECX + 0x794);
      sVar5 = *(short *)(in_ECX + 0x784);
      sVar8 = __ftol();
      local_18[6] = sVar5 + sVar8;
      sVar5 = *(short *)(in_ECX + 0x786);
      sVar8 = __ftol();
      local_18[7] = sVar5 - sVar8;
      *(float *)(local_18 + 8) =
           ((float)(fVar9 * (float10)iVar1 * (float10)fVar3) +
           (float)(fVar10 * (float10)iVar2 * (float10)fVar4)) / 2.0 + 3000.0;
      local_18[10] = 1;
      local_18[0xb] = 0;
      thunk_FUN_00471aee();
    }
    else {
      thunk_FUN_00414b91(s_C__float_src_worldwin_cpp_004a60dc,0x2eb,&DAT_004a60d8,
                         s_Bad_DisplayItem_Type_004a60c0);
    }
    local_18 = local_18 + 0xc;
  }
  thunk_FUN_00471b34();
  return;
}
```

---

## FUN_004718eb — 0x4718eb

- Classification : internal
- Corps : `0x4718eb–0x471a69`
- État : pseudocode obtenu
- Evidence : `ev_4a227d1765025385f80da169fa1849bf5c27b81f5750b2c7fde43521c12e4415`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a60f8` — "mNumDisplayItems < MAX_DISPLAY_ITEMS"
- `0x4a6120` — "C:\\float\\src\\worldwin.cpp"
- `0x4a613c` — "mNumDisplayItems<MAX_DISPLAY_ITEMS"
- `0x4a6160` — "C:\\float\\src\\worldwin.cpp"

### Pseudocode Ghidra

```c
void FUN_004718eb(void)

{
  int in_ECX;
  short local_c;
  
  *(undefined2 *)(in_ECX + 0x678) = 0;
  for (local_c = 0; (int)local_c < (int)(uint)DAT_006136b0; local_c = local_c + 1) {
    if (0x3f < *(short *)(in_ECX + 0x678)) {
      thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a6120,0x300,
                         s_mNumDisplayItems_<_MAX_DISPLAY_I_004a60f8);
    }
    *(short *)(in_ECX + 0x78 + *(short *)(in_ECX + 0x678) * 0x18) = local_c;
    *(undefined4 *)(in_ECX + 0x7c + *(short *)(in_ECX + 0x678) * 0x18) = 0;
    *(short *)(in_ECX + 0x678) = *(short *)(in_ECX + 0x678) + 1;
  }
  for (local_c = 0; (int)local_c < (int)(uint)DAT_006137b4; local_c = local_c + 1) {
    if ((&DAT_006136b4)[local_c * 2] != 0) {
      if (0x3f < *(short *)(in_ECX + 0x678)) {
        thunk_FUN_00414b64(s_C__float_src_worldwin_cpp_004a6160,0x30f,
                           s_mNumDisplayItems<MAX_DISPLAY_ITE_004a613c);
      }
      *(short *)(in_ECX + 0x78 + *(short *)(in_ECX + 0x678) * 0x18) = local_c;
      *(undefined4 *)(in_ECX + 0x7c + *(short *)(in_ECX + 0x678) * 0x18) = 1;
      *(short *)(in_ECX + 0x678) = *(short *)(in_ECX + 0x678) + 1;
    }
  }
  return;
}
```

---


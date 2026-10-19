# 0017_batch_0013 — détails (4/6)

## FUN_00462a87 — 0x462a87

- Classification : internal
- Corps : `0x462a87–0x462c54`
- État : pseudocode obtenu
- Evidence : `ev_352feb8e600eceb96c53f7813bd012e104389976cd0dc42358a78b6a0fcddd24`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40102d` — `thunk_FUN_0045e6d3`
- `0x401226` — `thunk_FUN_00460460`
- `0x40135c` — `thunk_FUN_00452e2b`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x4017bc` — `thunk_FUN_0045f807`
- `0x4019b5` — `thunk_FUN_0046562b`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402153` — `thunk_FUN_0045f0cd`
- `0x4023ec` — `thunk_FUN_00466fe4`

### Chaînes référencées

- `0x4a4d30` — "type > FT_None && type <= FT_Leviathan"
- `0x4a4d58` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
undefined4 * FUN_00462a87(int param_1,undefined4 param_2,undefined2 param_3,undefined2 param_4)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int in_ECX;
  undefined4 uVar5;
  
  if ((param_1 < 0) || (4 < param_1)) {
    uVar5 = thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4d58,0x297,
                               s_type_>_FT_None____type_<__FT_Lev_004a4d30);
  }
  else {
    uVar5 = 0;
  }
  if ((param_1 == 4) || (*(int *)(&DAT_006191f8 + param_1 * 0x14a0) != 0)) {
    if ((param_1 == 4) && (iVar2 = thunk_FUN_0046562b(4,0xffffffff), 0x80 < iVar2)) {
      puVar3 = (undefined4 *)0x0;
    }
    else {
      puVar3 = (undefined4 *)thunk_FUN_00466fe4(param_1,param_2);
      if (puVar3 != (undefined4 *)0x0) {
        *(short *)((int)puVar3 + 0xe) = (short)((in_ECX + -0x5ec218) / 0x29e8);
        *(undefined2 *)(puVar3 + 10) = param_3;
        *(undefined2 *)(puVar3 + 4) = param_3;
        *(undefined2 *)((int)puVar3 + 0x2a) = param_4;
        *(undefined2 *)((int)puVar3 + 0x12) = param_4;
        if (param_1 == 4) {
          thunk_FUN_00460460((int)*(short *)((int)puVar3 + 0xe));
        }
        else {
          if (((*(short *)(&DAT_00619242 + param_1 * 0x14a0) != 0) &&
              (iVar2 = thunk_FUN_0046562b(*puVar3,8), iVar2 == 0)) &&
             ((iVar2 = thunk_FUN_0045f0cd(uVar5), DAT_004befe0 != 0 ||
              (iVar4 = thunk_FUN_00467260(DAT_006136b0 - 1), iVar4 + 1 <= iVar2)))) {
            puVar3[1] = 8;
            puVar3[0xf] = 9;
            thunk_FUN_0045f807();
            uVar1 = thunk_FUN_00452e2b();
            *(undefined2 *)((int)puVar3 + 0x42) = uVar1;
          }
          thunk_FUN_0045e6d3((int)*(short *)((int)puVar3 + 0xe));
        }
      }
    }
  }
  else {
    puVar3 = (undefined4 *)0x0;
  }
  return puVar3;
}
```

---

## FUN_00462c55 — 0x462c55

- Classification : internal
- Corps : `0x462c55–0x462e26`
- État : pseudocode obtenu
- Evidence : `ev_2c014a94b969b7d5863bbed0149110ed94e61446c2dcdd7544c864216a161b95`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401875` — `thunk_FUN_0040fc15`
- `0x401b86` — `thunk_FUN_00453d36`
- `0x401cee` — `thunk_FUN_0040fd80`
- `0x401fff` — `thunk_FUN_0040fdab`
- `0x402455` — `thunk_FUN_004199c0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00462c55(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined4 local_8;
  
  if (param_2 == 0) {
    thunk_FUN_004199c0((int)*(short *)(in_ECX + 0x29a8));
    thunk_FUN_004199c0(*(undefined4 *)(in_ECX + 0x29cc));
    thunk_FUN_004199c0((int)*(short *)(in_ECX + 0x29d0));
    thunk_FUN_004199c0((int)*(short *)(in_ECX + 0x29e0));
    thunk_FUN_0040fd80(in_ECX,8);
    thunk_FUN_0040fd80(in_ECX + 8,0x400);
    thunk_FUN_0040fd80(in_ECX + 0x408,0x20);
    thunk_FUN_0040fd80(in_ECX + 0x29ac,0x10);
    thunk_FUN_0040fd80(in_ECX + 0x29bc,0x10);
    thunk_FUN_0040fd80(in_ECX + 0x29d4,0xc);
  }
  else {
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x29a8) = uVar1;
    uVar2 = thunk_FUN_0040fdab();
    *(undefined4 *)(in_ECX + 0x29cc) = uVar2;
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x29d0) = uVar1;
    uVar1 = thunk_FUN_0040fdab();
    *(undefined2 *)(in_ECX + 0x29e0) = uVar1;
    thunk_FUN_0040fc15(in_ECX,8);
    thunk_FUN_0040fc15(in_ECX + 8,0x400);
    thunk_FUN_0040fc15(in_ECX + 0x408,0x20);
    thunk_FUN_0040fc15(in_ECX + 0x29ac,0x10);
    thunk_FUN_0040fc15(in_ECX + 0x29bc,0x10);
    thunk_FUN_0040fc15(in_ECX + 0x29d4,0xc);
  }
  for (local_8 = 0; local_8 < *(short *)(in_ECX + 0x29a8); local_8 = local_8 + 1) {
    thunk_FUN_00453d36(param_1,param_2);
  }
  return;
}
```

---

## FUN_00462e27 — 0x462e27

- Classification : internal
- Corps : `0x462e27–0x462e35`
- État : pseudocode obtenu
- Evidence : `ev_3a949cb5c0e20a3cade13cc94530d3c7b13e71928c76974badd1088db9500dee`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x462e36` — `FUN_00462e36`
- `0x462e45` — `FUN_00462e45`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00462e27(void)

{
  FUN_00462e36();
  FUN_00462e45();
  return;
}
```

---

## FUN_00462e36 — 0x462e36

- Classification : internal
- Corps : `0x462e36–0x462e44`
- État : pseudocode obtenu
- Evidence : `ev_4e59ed2df7a6b0be242090fbced66b804c5a845e3183dcaa0dd0e1fb2d6b872f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401d48` — `thunk_FUN_00462e66`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00462e36(void)

{
  thunk_FUN_00462e66();
  return;
}
```

---

## FUN_00462e45 — 0x462e45

- Classification : internal
- Corps : `0x462e45–0x462e56`
- État : pseudocode obtenu
- Evidence : `ev_935210142652e8b469dc5d1b2d8ec837a4c2fa6fbb228418a80ffceec4f301c2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476c60` — `FUN_00476c60`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00462e45(void)

{
  FUN_00476c60(FUN_00462e57);
  return;
}
```

---

## FUN_00462e57 — 0x462e57

- Classification : internal
- Corps : `0x462e57–0x462e65`
- État : pseudocode obtenu
- Evidence : `ev_c4ee7017aa32cba1446252d80163daf79964287a40d37a6a0e3030723da5f80b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40231f` — `thunk_FUN_00462fa3`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00462e57(void)

{
  thunk_FUN_00462fa3();
  return;
}
```

---

## FUN_00462e66 — 0x462e66

- Classification : internal
- Corps : `0x462e66–0x462f1c`
- État : pseudocode obtenu
- Evidence : `ev_2dea5a53c61f06484f9fd164ba755303c08b4f47351da84b80b8bfb2368e8dd4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4016d6` — `thunk_FUN_00462f1d`
- `0x401ad7` — `thunk_FUN_004603ea`
- `0x478210` — ``eh_vector_constructor_iterator'`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void * FUN_00462e66(void)

{
  void *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491c8b;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  _eh_vector_constructor_iterator_
            (in_ECX,0x29e8,0xf,(_func_void_void_ptr *)&LAB_004021b2,
             (_func_void_void_ptr *)&LAB_00401e06);
  local_8 = 0;
  _eh_vector_constructor_iterator_
            ((void *)((int)in_ECX + 0x275a0),0x4c,0x100,thunk_FUN_0041e4c3,thunk_FUN_0041e4d9);
  local_8._0_1_ = 1;
  _eh_vector_constructor_iterator_
            ((void *)((int)in_ECX + 0x2cfa0),0x14a0,4,thunk_FUN_0045e660,thunk_FUN_0045e6b1);
  local_8._0_1_ = 2;
  thunk_FUN_004603ea();
  local_8 = CONCAT31(local_8._1_3_,3);
  thunk_FUN_00462f1d();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_00462f1d — 0x462f1d

- Classification : internal
- Corps : `0x462f1d–0x462fa2`
- État : pseudocode obtenu
- Evidence : `ev_0c0269ab02c05481290abfcacd8d519b36ceda23d962cf18c4e24992f84df49b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00462f1d(void)

{
  int in_ECX;
  
  *(undefined2 *)(in_ECX + 0x2c1a0) = 0;
  _memset((void *)(in_ECX + 0x275a0),0,0x4c00);
  *(undefined2 *)(in_ECX + 0x27498) = 0;
  *(undefined2 *)(in_ECX + 0x2759c) = 0;
  _memset((void *)(in_ECX + 0x2c1a4),0,0x500);
  *(undefined2 *)(in_ECX + 0x2c6a4) = 0;
  *(undefined2 *)(in_ECX + 0x2cc28) = 0;
  *(undefined4 *)(in_ECX + 0x2cc2c) = 0;
  return;
}
```

---

## FUN_00462fa3 — 0x462fa3

- Classification : internal
- Corps : `0x462fa3–0x46303a`
- État : pseudocode obtenu
- Evidence : `ev_db7d531d44da0c3784adca1cea98f2d4823aa71ae9b4c969b568474f13ed2c13`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401c03` — `thunk_FUN_0046044d`
- `0x4782b0` — `FUN_004782b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00462fa3(void)

{
  int in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00491ce1;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_8 = 2;
  thunk_FUN_0046044d();
  local_8._0_1_ = 1;
  FUN_004782b0(in_ECX + 0x2cfa0,0x14a0,4,thunk_FUN_0045e6b1);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004782b0(in_ECX + 0x275a0,0x4c,0x100,thunk_FUN_0041e4d9);
  local_8 = 0xffffffff;
  FUN_004782b0(in_ECX,0x29e8,0xf,&LAB_00401e06);
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

## FUN_0046303b — 0x46303b

- Classification : internal
- Corps : `0x46303b–0x4633a6`
- État : pseudocode obtenu
- Evidence : `ev_c376abd7d000e38d788e4baf135389849cfd5bead8b071e126a93ae114385825`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40149c` — `thunk_FUN_00414bc2`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x402414` — `thunk_FUN_00456a13`
- `0x472da0` — `FUN_00472da0`
- `0x472f10` — `FUN_00472f10`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x4a4d70` — "status == 0"
- `0x4a4d7c` — "C:\\float\\src\\tworld.cpp"
- `0x4a4d94` — "%d %d %d,%d,%d %d %d %d %s %s %s"
- `0x4a4db8` — "vals >= 10"
- `0x4a4dc4` — "C:\\float\\src\\tworld.cpp"
- `0x4a4ddc` — "noshape"
- `0x4a4e14` — "FALSE"
- `0x4a4e1c` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
void FUN_0046303b(undefined4 param_1)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  int local_d4;
  undefined1 local_d0 [24];
  undefined4 local_b8;
  undefined2 local_b4 [2];
  undefined2 local_b0 [2];
  undefined2 local_ac [2];
  undefined2 local_a8 [2];
  undefined2 local_a4 [2];
  undefined2 local_a0 [2];
  undefined2 local_9c [2];
  char local_98 [24];
  char local_80 [24];
  undefined1 local_68 [100];
  
  iVar2 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,20000);
  if (iVar2 != 0) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4d7c,0x322,s_status____0_004a4d70);
  }
  for (local_d4 = 0; local_d4 < 0x65; local_d4 = local_d4 + 1) {
    iVar3 = local_d4 * 0x2c;
    thunk_FUN_0040f5b3(local_68,0);
    iVar2 = FUN_00472f10(local_68,s__d__d__d__d__d__d__d__d__s__s__s_004a4d94,&local_b8,local_b4,
                         local_b0,local_ac,local_a8,local_a4,local_a0,local_9c,local_80,local_98,
                         local_d0);
    if (iVar2 < 10) {
      thunk_FUN_00414bc2(s_C__float_src_tworld_cpp_004a4dc4,0x330,s_vals_>__10_004a4db8,local_d4);
    }
    *(undefined4 *)(&DAT_005eac08 + iVar3) = local_b8;
    *(undefined2 *)(&DAT_005eac0c + iVar3) = local_b4[0];
    *(undefined2 *)(&DAT_005eac0e + iVar3) = local_b0[0];
    *(undefined2 *)(&DAT_005eac12 + iVar3) = local_ac[0];
    *(undefined2 *)(&DAT_005eac10 + iVar3) = local_a8[0];
    *(undefined2 *)(&DAT_005eac14 + iVar3) = local_a4[0];
    *(undefined2 *)(&DAT_005eac16 + iVar3) = local_a0[0];
    *(undefined2 *)(&DAT_005eac18 + iVar3) = local_9c[0];
    *(undefined2 *)(&DAT_005eac1a + iVar3) = 0;
    *(undefined2 *)(&DAT_005eac1c + iVar3) = 0;
    *(undefined2 *)(&DAT_005eac1e + iVar3) = 0xffff;
    iVar2 = __strcmpi(local_98,s_noshape_004a4ddc);
    if (iVar2 != 0) {
      uVar1 = thunk_FUN_00456a13(local_98);
      *(undefined2 *)(&DAT_005eac1e + iVar3) = uVar1;
    }
    iVar2 = __strcmpi(local_80,&DAT_004a4de4);
    if (iVar2 == 0) {
      *(undefined4 *)(&DAT_005eac30 + iVar3) = 0;
    }
    else {
      iVar2 = __strcmpi(local_80,&DAT_004a4dec);
      if (iVar2 == 0) {
        *(undefined4 *)(&DAT_005eac30 + iVar3) = 2;
      }
      else {
        iVar2 = __strcmpi(local_80,&DAT_004a4df4);
        if (iVar2 == 0) {
          *(undefined4 *)(&DAT_005eac30 + iVar3) = 1;
        }
        else {
          iVar2 = __strcmpi(local_80,&DAT_004a4dfc);
          if (iVar2 == 0) {
            *(undefined4 *)(&DAT_005eac30 + iVar3) = 3;
          }
          else {
            iVar2 = __strcmpi(local_80,&DAT_004a4e04);
            if (iVar2 == 0) {
              *(undefined4 *)(&DAT_005eac30 + iVar3) = 4;
            }
            else {
              iVar2 = __strcmpi(local_80,&DAT_004a4e0c);
              if (iVar2 == 0) {
                *(undefined4 *)(&DAT_005eac30 + iVar3) = 0xffffffff;
              }
              else {
                thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4e1c,0x34d,s_FALSE_004a4e14);
              }
            }
          }
        }
      }
    }
    FUN_00472da0(iVar3 + 0x5eac20,local_d0);
  }
  DAT_004a4b70 = thunk_FUN_00456a13(&DAT_004a4e34);
  DAT_004a4b74 = thunk_FUN_00456a13(&DAT_004a4e3c);
  return;
}
```

---

## FUN_004633a7 — 0x4633a7

- Classification : internal
- Corps : `0x4633a7–0x463562`
- État : pseudocode obtenu
- Evidence : `ev_44c306a9b382d851e58738b7b6eb24f80860af4d1dc3dfb2fe923b92a03de1e0`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40149c` — `thunk_FUN_00414bc2`
- `0x401730` — `thunk_FUN_004557bc`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472f10` — `FUN_00472f10`

### Chaînes référencées

- `0x4a4e44` — "status == 0"
- `0x4a4e50` — "C:\\float\\src\\tworld.cpp"
- `0x4a4e68` — "%s %d %d %d %d %d %d"
- `0x4a4e80` — "vals == 7"
- `0x4a4e8c` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
void FUN_004633a7(undefined4 param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 local_a8 [2];
  undefined2 local_a4 [8];
  undefined2 local_94 [2];
  int local_90;
  undefined2 local_8c [2];
  undefined2 local_88 [2];
  undefined2 local_84 [2];
  undefined1 local_80 [24];
  undefined1 local_68 [100];
  
  iVar2 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,20000);
  if (iVar2 != 0) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4e50,0x35d,s_status____0_004a4e44);
  }
  for (local_90 = 0; local_90 < 0x2d; local_90 = local_90 + 1) {
    thunk_FUN_0040f5b3(local_68,0);
    iVar2 = FUN_00472f10(local_68,s__s__d__d__d__d__d__d_004a4e68,local_80,local_84,local_88,
                         local_8c,local_94,local_a4,local_a8);
    if (iVar2 != 7) {
      thunk_FUN_00414bc2(s_C__float_src_tworld_cpp_004a4e8c,0x368,s_vals____7_004a4e80,local_90);
    }
    uVar1 = thunk_FUN_004557bc(local_80);
    *(undefined2 *)(&DAT_005ebfa4 + local_90 * 0xe) = uVar1;
    *(undefined2 *)(&DAT_005ebfa0 + local_90 * 0xe) = local_84[0];
    *(undefined2 *)(&DAT_005ebfa2 + local_90 * 0xe) = local_88[0];
    *(undefined2 *)(&DAT_005ebfa6 + local_90 * 0xe) = local_8c[0];
    *(undefined2 *)(&DAT_005ebfa8 + local_90 * 0xe) = local_94[0];
    *(undefined2 *)(&DAT_005ebfaa + local_90 * 0xe) = local_a4[0];
    *(undefined2 *)(&DAT_005ebfac + local_90 * 0xe) = local_a8[0];
  }
  return;
}
```

---

## FUN_00463563 — 0x463563

- Classification : internal
- Corps : `0x463563–0x4637fb`
- État : pseudocode obtenu
- Evidence : `ev_7c01d6e5f54ad42240e42ed6a3a4ab2d68c251467f985d2cc74da384dcbe4f7b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401fa0` — `thunk_FUN_00429d5c`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472db0` — `FUN_00472db0`
- `0x472f10` — `FUN_00472f10`
- `0x4737e0` — `_strncpy`
- `0x476e20` — `_strncmp`

### Chaînes référencées

- `0x4a4ea4` — "%s %d"
- `0x4a4eac` — "%s %d"
- `0x4a4eb4` — "%s %d"

### Pseudocode Ghidra

```c
void FUN_00463563(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined1 local_238 [32];
  undefined1 local_218 [268];
  int local_10c;
  char local_108 [256];
  undefined2 local_8 [2];
  
  iVar1 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,20000);
  if (iVar1 == 0) {
    *(undefined2 *)(in_ECX + 0x2cc28) = 0;
    while ((*(short *)(in_ECX + 0x2cc28) < 0x20 &&
           (iVar1 = thunk_FUN_0040f5b3(local_108,1), iVar1 != -1))) {
      _strncpy((char *)(in_ECX + 0x2c6a8 + *(short *)(in_ECX + 0x2cc28) * 0x2c),local_108,0x20);
      *(undefined1 *)(in_ECX + 0x2c6c7 + *(short *)(in_ECX + 0x2cc28) * 0x2c) = 0;
      thunk_FUN_0040f5b3(local_108,1);
      FUN_00472f10(local_108,s__s__d_004a4ea4,local_238,local_8);
      *(short *)(in_ECX + 0x2c6c8 + *(short *)(in_ECX + 0x2cc28) * 0x2c) = local_8[0] + -1;
      thunk_FUN_0040f5b3(local_108,1);
      FUN_00472f10(local_108,s__s__d_004a4eac,local_238,local_8);
      *(undefined2 *)(in_ECX + 0x2c6ca + *(short *)(in_ECX + 0x2cc28) * 0x2c) = local_8[0];
      thunk_FUN_0040f5b3(local_108,1);
      FUN_00472f10(local_108,s__s__d_004a4eb4,local_238,local_8);
      *(undefined2 *)(in_ECX + 0x2c6cc + *(short *)(in_ECX + 0x2cc28) * 0x2c) = local_8[0];
      local_10c = 0;
      local_218[0] = 0;
      while (local_10c == 0) {
        thunk_FUN_0040f5b3(local_108,1);
        iVar1 = _strncmp(local_108,&DAT_004a4ebc,3);
        if (iVar1 == 0) {
          local_10c = 1;
        }
        else {
          FUN_00472db0(local_218,local_108);
          FUN_00472db0(local_218,&DAT_004a4ec0);
        }
      }
      uVar2 = thunk_FUN_00429d5c(local_218,0);
      *(undefined4 *)(in_ECX + 0x2c6d0 + *(short *)(in_ECX + 0x2cc28) * 0x2c) = uVar2;
      *(short *)(in_ECX + 0x2cc28) = *(short *)(in_ECX + 0x2cc28) + 1;
    }
  }
  return;
}
```

---

## FUN_004637fc — 0x4637fc

- Classification : internal
- Corps : `0x4637fc–0x4641dd`
- État : pseudocode obtenu
- Evidence : `ev_96a46390b086f06a56b3c395f6e1a9de7ba2c2a1c30396c7ca72c63944a1039e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010dc` — `thunk_FUN_00461b3b`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x401b2c` — `thunk_FUN_00464b9e`
- `0x401cd0` — `thunk_FUN_00461859`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402261` — `thunk_FUN_00415372`
- `0x4022ca` — `thunk_FUN_0046466f`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a4ec4` — "size>=0 && size<MAX_WORLDSIZE"
- `0x4a4ee4` — "C:\\float\\src\\tworld.cpp"
- `0x4a4efc` — "difficulty>=0"
- `0x4a4f0c` — "C:\\float\\src\\tworld.cpp"
- `0x4a4f24` — "mWorldSize<TW_NumWorlds"
- `0x4a4f3c` — "C:\\float\\src\\tworld.cpp"
- `0x4a4f54` — "emptycount > 0"
- `0x4a4f64` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
void FUN_004637fc(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int in_ECX;
  int local_d4;
  int local_d0;
  int local_c8;
  int local_c0;
  short local_bc;
  int local_b8;
  short local_b4;
  short local_b0;
  int local_a8;
  int local_a0;
  int local_98;
  int local_90;
  int local_88;
  int aiStack_84 [32];
  
  if ((param_1 < 0) || (3 < param_1)) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4ee4,0x3b6,
                       s_size>_0____size<MAX_WORLDSIZE_004a4ec4);
  }
  if (param_2 < 0) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4f0c,0x3b7,s_difficulty>_0_004a4efc);
  }
  *(undefined2 *)(in_ECX + 0x2749a) = (undefined2)param_1;
  if (DAT_005ebd70 <= *(short *)(in_ECX + 0x2749a)) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4f3c,0x3bb,s_mWorldSize<TW_NumWorlds_004a4f24);
  }
  *(int *)(in_ECX + 0x2cc30) = param_2;
  *(undefined2 *)(in_ECX + 0x2cf9c) = 0;
  *(undefined2 *)(in_ECX + 0x2cf9e) = 0;
  *(undefined4 *)(in_ECX + 0x2cc34) = 5000;
  *(undefined4 *)(in_ECX + 0x2cc38) = 4000;
  iVar2 = thunk_FUN_00467260(2);
  *(ushort *)(in_ECX + 0x2cc3c) = (-(ushort)(iVar2 != 0) & 2) - 1;
  iVar2 = thunk_FUN_00467260(2);
  *(ushort *)(in_ECX + 0x2cc3e) = (-(ushort)(iVar2 != 0) & 2) - 1;
  *(undefined2 *)(in_ECX + 0x27498) =
       *(undefined2 *)(&DAT_005ebf98 + *(short *)(in_ECX + 0x2749a) * 2);
  *(undefined2 *)(in_ECX + 0x2759c) =
       *(undefined2 *)(&DAT_005ebd68 + *(short *)(in_ECX + 0x2749a) * 2);
  for (local_88 = 0; local_88 < (int)(uint)*(ushort *)(in_ECX + 0x2759c); local_88 = local_88 + 1) {
    *(undefined2 *)(in_ECX + 0x274a0 + local_88 * 8) =
         *(undefined2 *)(&DAT_0061fa54 + local_88 * 8 + *(short *)(in_ECX + 0x2749a) * 0x100);
    *(undefined2 *)(in_ECX + 0x274a2 + local_88 * 8) =
         *(undefined2 *)(&DAT_0061fa56 + local_88 * 8 + *(short *)(in_ECX + 0x2749a) * 0x100);
    *(undefined4 *)(in_ECX + 0x2749c + local_88 * 8) = 0;
  }
  for (local_88 = 0; local_88 < (int)(uint)*(ushort *)(in_ECX + 0x27498); local_88 = local_88 + 1) {
    thunk_FUN_00461b3b(local_88);
    thunk_FUN_00461859();
  }
  *(undefined2 *)(in_ECX + 0x2c6a4) = 0;
  for (local_88 = 0; local_88 < 0x40; local_88 = local_88 + 1) {
    *(undefined4 *)(in_ECX + 0x2c1a4 + local_88 * 0x14) = 0;
  }
  for (local_88 = 0; local_88 < 0x100; local_88 = local_88 + 1) {
    *(undefined4 *)(in_ECX + 0x275a0 + local_88 * 0x4c) = 0xffffffff;
  }
  _memset((void *)(in_ECX + 0x2cd42),0,0x1e);
  _memset((void *)(in_ECX + 0x2cd60),0,0x1e);
  _memset((void *)(in_ECX + 0x2cd7e),0,0x1e);
  thunk_FUN_0046466f(param_3,param_4);
  thunk_FUN_00464b9e(param_3,param_4);
  for (local_88 = 0; local_88 < (int)(uint)*(ushort *)(in_ECX + 0x27498); local_88 = local_88 + 1) {
    local_98 = in_ECX + 0x428 + local_88 * 0x29e8;
    for (local_a0 = 0; local_a0 < *(short *)(in_ECX + local_88 * 0x29e8 + 0x29a8);
        local_a0 = local_a0 + 1) {
      if (*(int *)(local_98 + 4) == 2) {
        *(undefined4 *)(local_98 + 0x10) = 2;
      }
      local_98 = local_98 + 0x60;
    }
  }
  local_88 = 0;
  do {
    if ((int)(uint)*(ushort *)(in_ECX + 0x2759c) <= local_88) {
      for (local_88 = 0; local_88 < (int)(*(ushort *)(in_ECX + 0x27498) - 1);
          local_88 = local_88 + 1) {
        iVar2 = (int)*(short *)(in_ECX + 0x29e0 + local_88 * 0x29e8);
        aiStack_84[local_88 * 2] = iVar2 << 1;
        aiStack_84[local_88 * 2 + 1] = iVar2 * 2 + 1;
      }
      local_90 = 0;
      do {
        do {
          if ((int)((uint)*(ushort *)(in_ECX + 0x27498) * 2 + -2) <= local_90) {
            for (local_88 = 0; local_88 < 9; local_88 = local_88 + 1) {
              *(undefined4 *)(&DAT_005e16b0 + local_88 * 4) = 0;
            }
            DAT_005e16a8 = 0;
            thunk_FUN_00415372();
            *(undefined4 *)(in_ECX + 0x2cc2c) = 0;
            return;
          }
          local_d0 = local_90 / 2;
          if (DAT_0049c99c != 0) {
            local_d0 = thunk_FUN_00467260(*(ushort *)(in_ECX + 0x27498) - 1);
          }
          iVar2 = in_ECX + local_d0 * 0x29e8;
          local_c0 = 0;
          local_d4 = iVar2 + 0x428;
          for (local_88 = 0; local_88 < *(short *)(iVar2 + 0x29a8); local_88 = local_88 + 1) {
            if (((*(int *)(local_d4 + 4) == 0) && (*(int *)(local_d4 + 0x14) == -1)) &&
               (*(int *)(local_d4 + 0x10) == 0)) {
              local_c0 = local_c0 + 1;
            }
            local_d4 = local_d4 + 0x60;
          }
        } while (local_c0 == 0);
        iVar3 = thunk_FUN_00467260(local_c0);
        local_c8 = 0;
        local_d4 = iVar2 + 0x428;
        for (local_88 = 0; local_88 < *(short *)(iVar2 + 0x29a8); local_88 = local_88 + 1) {
          if (((*(int *)(local_d4 + 4) == 0) && (*(int *)(local_d4 + 0x14) == -1)) &&
             (*(int *)(local_d4 + 0x10) == 0)) {
            if (local_c8 == iVar3) {
              *(undefined4 *)(local_d4 + 0x10) = 1;
              *(int *)(local_d4 + 0x24) = aiStack_84[local_90] + 6;
              local_90 = local_90 + 1;
              break;
            }
            local_c8 = local_c8 + 1;
          }
          local_d4 = local_d4 + 0x60;
        }
      } while( true );
    }
    for (local_bc = (short)local_88; (int)(*(ushort *)(in_ECX + 0x27498) - 1) <= (int)local_bc;
        local_bc = (local_bc - (*(short *)(in_ECX + 0x27498) + -1)) + 4) {
    }
    iVar2 = in_ECX + local_bc * 0x29e8;
    local_b4 = 0;
    local_a8 = iVar2 + 0x428;
    for (local_b8 = 0; local_b8 < *(short *)(iVar2 + 0x29a8); local_b8 = local_b8 + 1) {
      if (((*(int *)(local_a8 + 4) == 0) && (*(int *)(local_a8 + 0x10) == 0)) &&
         (*(int *)(local_a8 + 0x14) == -1)) {
        local_b4 = local_b4 + 1;
      }
      local_a8 = local_a8 + 0x60;
    }
    if (local_b4 < 1) {
      thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4f64,0x40a,s_emptycount_>_0_004a4f54);
    }
    sVar1 = thunk_FUN_00467260((int)local_b4);
    local_b0 = 0;
    local_a8 = iVar2 + 0x428;
    for (local_b8 = 0; local_b8 < *(short *)(iVar2 + 0x29a8); local_b8 = local_b8 + 1) {
      if (((*(int *)(local_a8 + 4) == 0) && (*(int *)(local_a8 + 0x10) == 0)) &&
         (*(int *)(local_a8 + 0x14) == -1)) {
        if (local_b0 == sVar1) {
          *(undefined4 *)(local_a8 + 0x10) = 1;
          *(undefined4 *)(local_a8 + 0x24) = 5;
          break;
        }
        local_b0 = local_b0 + 1;
      }
      local_a8 = local_a8 + 0x60;
    }
    local_88 = local_88 + 1;
  } while( true );
}
```

---

## FUN_004641de — 0x4641de

- Classification : internal
- Corps : `0x4641de–0x464241`
- État : pseudocode obtenu
- Evidence : `ev_f92b05e1bac76d2be3a91b76e6eb420474e1d04db600d49cc8d4a55edf30587d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a4f7c` — "val >= 0 && val < NUMPADITEMINFOS"
- `0x4a4fa0` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
undefined * FUN_004641de(int param_1,int param_2)

{
  int local_8;
  
  local_8 = param_2;
  if ((-1 < param_1) && (param_1 < 4)) {
    local_8 = param_2 + param_1 * 0x10;
  }
  if ((local_8 < 0) || (100 < local_8)) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4fa0,0x46b,
                       s_val_>__0____val_<_NUMPADITEMINFO_004a4f7c);
  }
  return &DAT_005eac08 + local_8 * 0x2c;
}
```

---

## FUN_00464242 — 0x464242

- Classification : internal
- Corps : `0x464242–0x4642a2`
- État : pseudocode obtenu
- Evidence : `ev_055bd9354dfe4717f5f4c2749565d4303a049541ad9fbd7afe7d37d0536bc244`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a4fb8` — "val >= 0 && val < NUMFLOATERINFOS"
- `0x4a4fdc` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
undefined * FUN_00464242(int param_1,int param_2)

{
  int local_8;
  
  if (param_1 == 4) {
    local_8 = param_2 + 0x1b;
  }
  else {
    local_8 = param_1 * 9 + param_2;
  }
  if ((local_8 < 0) || (0x2c < local_8)) {
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a4fdc,0x478,
                       s_val_>__0____val_<_NUMFLOATERINFO_004a4fb8);
  }
  return &DAT_005ebfa0 + local_8 * 0xe;
}
```

---

## FUN_004642a3 — 0x4642a3

- Classification : internal
- Corps : `0x4642a3–0x46466e`
- État : pseudocode obtenu
- Evidence : `ev_561df3c3edee5a21c16764f7b95d5fa1e14e3a19d3ca83157c30bd51568c31c9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401046` — `thunk_FUN_0046303b`
- `0x4015cd` — `thunk_FUN_00463563`
- `0x401749` — `thunk_FUN_00414c97`
- `0x40187a` — `thunk_FUN_004633a7`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x402176` — `thunk_FUN_00414bf7`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472f10` — `FUN_00472f10`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a4ff4` — "pad.txt"
- `0x4a4ffc` — "floater.txt"
- `0x4a5008` — "spells.txt"
- `0x4a5014` — "data\\worldpos.txt"
- `0x4a5028` — "FALSE"
- `0x4a5030` — "C:\\float\\src\\tworld.cpp"
- `0x4a504c` — "TW_NumWorlds<=MAX_WORLD_DEFINITIONS"
- `0x4a5070` — "C:\\float\\src\\tworld.cpp"
- `0x4a508c` — "i0 <= MAX_ISLANDS"
- `0x4a50a0` — "C:\\float\\src\\tworld.cpp"
- `0x4a50b8` — "%d %d %d %d"
- `0x4a50c4` — "t == 4"
- `0x4a50cc` — "C:\\float\\src\\tworld.cpp"
- `0x4a50e4` — "%d %d"
- `0x4a50ec` — "i0 < TW_NumIslands[w] && i1 < TW_NumIslands[w]"
- `0x4a511c` — "C:\\float\\src\\tworld.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_004642a3(void)

{
  int iVar1;
  undefined4 uVar2;
  int local_94;
  undefined2 local_90 [2];
  undefined4 local_8c;
  undefined1 local_88 [100];
  int local_24;
  int local_20 [4];
  int local_10;
  int local_c;
  undefined4 local_8;
  
  thunk_FUN_0046303b(s_pad_txt_004a4ff4);
  thunk_FUN_004633a7(s_floater_txt_004a4ffc);
  thunk_FUN_00463563(s_spells_txt_004a5008);
  local_8 = thunk_FUN_00414bf7(10000);
  iVar1 = thunk_FUN_0040f419(s_data_worldpos_txt_004a5014,local_8,10000);
  if (iVar1 == 0) {
    _memset(&DAT_005ebd68,0,6);
    _memset(&DAT_005ebf98,0,6);
    thunk_FUN_0040f5b3(local_88,0);
    FUN_00472f10(local_88,&DAT_004a5048,&DAT_005ebd70);
    if (3 < DAT_005ebd70) {
      thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a5070,0x49a,
                         s_TW_NumWorlds<_MAX_WORLD_DEFINITI_004a504c);
    }
    for (local_10 = 0; local_10 < DAT_005ebd70; local_10 = local_10 + 1) {
      thunk_FUN_0040f5b3(local_88,0);
      FUN_00472f10(local_88,&DAT_004a5088,local_20);
      if (0xf < local_20[0]) {
        thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a50a0,0x4a0,s_i0_<__MAX_ISLANDS_004a508c);
      }
      *(undefined2 *)(&DAT_005ebf98 + local_10 * 2) = (undefined2)local_20[0];
      for (local_94 = 0; local_94 < *(short *)(&DAT_005ebf98 + local_10 * 2);
          local_94 = local_94 + 1) {
        thunk_FUN_0040f5b3(local_88,0);
        local_c = FUN_00472f10(local_88,s__d__d__d__d_004a50b8,local_20,&local_24,&local_8c,local_90
                              );
        if (local_c != 4) {
          thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a50cc,0x4a8,s_t____4_004a50c4);
        }
        *(float *)(&DAT_005ebd78 + local_94 * 0xc + local_10 * 0xb4) =
             (float)local_20[0] * 0.017453277;
        *(int *)(&DAT_005ebd7c + local_94 * 0xc + local_10 * 0xb4) = local_24;
        *(undefined4 *)(&DAT_005ebd80 + local_94 * 0xc + local_10 * 0xb4) = local_8c;
        *(undefined2 *)(&DAT_005eaba8 + local_94 * 2 + local_10 * 0x1e) = local_90[0];
      }
      do {
        thunk_FUN_0040f5b3(local_88,0);
        local_c = FUN_00472f10(local_88,s__d__d_004a50e4,local_20,&local_24);
        if (local_c == 2) {
          if ((*(short *)(&DAT_005ebf98 + local_10 * 2) <= local_20[0]) ||
             (*(short *)(&DAT_005ebf98 + local_10 * 2) <= local_24)) {
            thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a511c,0x4b7,
                               s_i0_<_TW_NumIslands[w]_&&_i1_<_TW_004a50ec);
          }
          *(undefined2 *)
           (&DAT_0061fa54 + *(short *)(&DAT_005ebd68 + local_10 * 2) * 8 + local_10 * 0x100) =
               (undefined2)local_20[0];
          *(undefined2 *)
           (&DAT_0061fa56 + *(short *)(&DAT_005ebd68 + local_10 * 2) * 8 + local_10 * 0x100) =
               (undefined2)local_24;
          *(undefined4 *)
           (&DAT_0061fa50 + *(short *)(&DAT_005ebd68 + local_10 * 2) * 8 + local_10 * 0x100) = 0;
          *(short *)(&DAT_005ebd68 + local_10 * 2) = *(short *)(&DAT_005ebd68 + local_10 * 2) + 1;
        }
      } while (local_c == 2);
    }
    thunk_FUN_00414c97(local_8);
    uVar2 = 1;
  }
  else {
    thunk_FUN_00414c97(local_8);
    thunk_FUN_00414b64(s_C__float_src_tworld_cpp_004a5030,0x490,s_FALSE_004a5028);
    uVar2 = 0;
  }
  return uVar2;
}
```

---


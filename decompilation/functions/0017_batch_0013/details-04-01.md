# 0017_batch_0013 — détails (1/3)

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

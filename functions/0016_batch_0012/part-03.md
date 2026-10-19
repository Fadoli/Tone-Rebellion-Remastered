# 0016_batch_0012 — détails (3/6)

## FUN_00459310 — 0x459310

- Classification : internal
- Corps : `0x459310–0x459322`
- État : pseudocode obtenu
- Evidence : `ev_1b7105a9fa83c932c3106804f6775b4936e15093c8ff885149a7c67b7ec6af9f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00459310(void)

{
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_00459330 — 0x459330

- Classification : internal
- Corps : `0x459330–0x45935d`
- État : pseudocode obtenu
- Evidence : `ev_ef20dc8480c4c55d70c918cfe9a3bf9c7d65ba9b2620391b30b40d82722ee274`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401a2d` — `thunk_FUN_004593a0`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00459330(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_004593a0();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_00459370 — 0x459370

- Classification : internal
- Corps : `0x459370–0x459396`
- État : pseudocode obtenu
- Evidence : `ev_ed9d8a99d5062e7d43e21973d670289e1dd73782b06144d9bc5885384056fe39`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00459370(undefined4 param_1,undefined4 param_2,int param_3,code *param_4)

{
  while (param_3 = param_3 + -1, -1 < param_3) {
    (*param_4)();
  }
  return;
}
```

---

## FUN_004593a0 — 0x4593a0

- Classification : internal
- Corps : `0x4593a0–0x4593b2`
- État : pseudocode obtenu
- Evidence : `ev_f9d5746429c2c9852fd108e21e9891acb6a270628993cb6010294ad073b72bb1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40194c` — `thunk_FUN_00429262`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004593a0(void)

{
  thunk_FUN_00429262();
  return;
}
```

---

## FUN_004593c0 — 0x4593c0

- Classification : internal
- Corps : `0x4593c0–0x4593ce`
- État : pseudocode obtenu
- Evidence : `ev_8df3df22d8ffeff2b2ff2795116584b0a993885459c8faf0b5b8bf76e6ac3413`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4593cf` — `FUN_004593cf`
- `0x4593de` — `FUN_004593de`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004593c0(void)

{
  FUN_004593cf();
  FUN_004593de();
  return;
}
```

---

## FUN_004593cf — 0x4593cf

- Classification : internal
- Corps : `0x4593cf–0x4593dd`
- État : pseudocode obtenu
- Evidence : `ev_1330ba6e05daf333bf14f66433ae168c237d5432f1d7e95ea95c131dae470c20`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401dfc` — `thunk_FUN_004596ca`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004593cf(void)

{
  thunk_FUN_004596ca();
  return;
}
```

---

## FUN_004593de — 0x4593de

- Classification : internal
- Corps : `0x4593de–0x4593ef`
- État : pseudocode obtenu
- Evidence : `ev_55277d1f912b45b0a6ff8947bd62e0c0aa2741f4aa41e6c396d5f6afc212ad6a`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476c60` — `FUN_00476c60`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004593de(void)

{
  FUN_00476c60(FUN_004593f0);
  return;
}
```

---

## FUN_004593f0 — 0x4593f0

- Classification : internal
- Corps : `0x4593f0–0x4593fe`
- État : pseudocode obtenu
- Evidence : `ev_ab1e372cd35162a5529395c6998a7fcc960837220ad976ba36967d7461ee6540`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401104` — `thunk_FUN_0045971b`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004593f0(void)

{
  thunk_FUN_0045971b();
  return;
}
```

---

## FUN_004593ff — 0x4593ff

- Classification : internal
- Corps : `0x4593ff–0x4595cb`
- État : pseudocode obtenu
- Evidence : `ev_6f41a8cd75fcd4dd9d373ff4d75b037e2229ec04e417a6658627b71ae83da252`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401875` — `thunk_FUN_0040fc15`
- `0x40205e` — `thunk_FUN_0040fac8`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004593ff(undefined4 param_1,int *param_2,int *param_3,int *param_4)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  int *piVar4;
  undefined4 local_ac;
  int local_90 [2];
  int local_88;
  int local_84 [30];
  int *local_c;
  
  thunk_FUN_0040fac8(0);
  thunk_FUN_0040fc15(local_90,0x80);
  if (local_90[0] == 0x46464952) {
    if (local_88 == 0x45564157) {
      bVar3 = false;
      bVar2 = false;
      local_c = local_84;
      while ((!bVar2 && ((int)local_c - (int)local_90 < 0x8c))) {
        iVar1 = local_c[1];
        piVar4 = local_c + 2;
        if (*local_c == 0x20746d66) {
          bVar3 = true;
          if (param_2 != (int *)0x0) {
            *param_2 = *piVar4;
            param_2[1] = local_c[3];
            param_2[2] = local_c[4];
            param_2[3] = local_c[5];
            *(short *)(param_2 + 4) = (short)local_c[6];
          }
          local_c = (int *)((int)piVar4 + iVar1);
        }
        else if (*local_c == 0x61746164) {
          bVar2 = true;
          if (param_4 != (int *)0x0) {
            *param_4 = iVar1;
          }
          local_c = piVar4;
          if (param_3 != (int *)0x0) {
            *param_3 = (int)piVar4 - (int)local_90;
          }
        }
        else {
          local_c = (int *)((int)piVar4 + iVar1);
        }
      }
      if ((bVar3) && (bVar2)) {
        local_ac = 1;
      }
      else {
        local_ac = 0;
      }
    }
    else {
      local_ac = 0;
    }
  }
  else {
    local_ac = 0;
  }
  return local_ac;
}
```

---

## FUN_004595cc — 0x4595cc

- Classification : internal
- Corps : `0x4595cc–0x459652`
- État : pseudocode obtenu
- Evidence : `ev_aad849610e531060d98436b3c400b1e5cee4f1e45ea7cb59f840981d9d0cf148`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472c6c` — `__ftol`
- `0x478134` — `FUN_00478134`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004595cc(int param_1)

{
  float10 fVar1;
  double dVar2;
  double dVar3;
  undefined4 local_8;
  
  if ((param_1 < 0) || (100 < param_1)) {
    local_8 = 0;
  }
  else if (param_1 == 0) {
    local_8 = -10000;
  }
  else {
    dVar3 = (double)param_1;
    fVar1 = (float10)FUN_00478134(dVar3 / 100.0);
    dVar2 = (double)fVar1;
    fVar1 = (float10)FUN_00478134(0,0x40000000,dVar2,dVar3);
    local_8 = __ftol(dVar2,(double)(((float10)dVar2 / fVar1) * (float10)1000.0));
    if (local_8 < -10000) {
      local_8 = -10000;
    }
    if (0 < local_8) {
      local_8 = 0;
    }
  }
  return local_8;
}
```

---

## FUN_00459653 — 0x459653

- Classification : internal
- Corps : `0x459653–0x4596c9`
- État : pseudocode obtenu
- Evidence : `ev_d9039744ed6a569770cf95afc0438a38142ad57aee8aa4f3d02b467f64f07ff7`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472c6c` — `__ftol`
- `0x478134` — `FUN_00478134`
- `0x4781f0` — `FUN_004781f0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_00459653(int param_1)

{
  float10 fVar1;
  double dVar2;
  undefined4 local_8;
  
  if ((param_1 < -10000) || (0 < param_1)) {
    local_8 = 0;
  }
  else {
    dVar2 = (double)param_1;
    fVar1 = (float10)FUN_00478134(0,0x40000000,dVar2);
    fVar1 = (float10)FUN_004781f0((double)((fVar1 * (float10)dVar2) / (float10)1000.0));
    local_8 = __ftol((double)(fVar1 * (float10)100.0));
    if (local_8 < 0) {
      local_8 = 0;
    }
    if (100 < local_8) {
      local_8 = 100;
    }
  }
  return local_8;
}
```

---

## FUN_004596ca — 0x4596ca

- Classification : internal
- Corps : `0x4596ca–0x45971a`
- État : pseudocode obtenu
- Evidence : `ev_7ce7f2c61a91c70b25625d98ca188eef3eafefaa56e1e88bd20291b69ee60aaa`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x40245f` — `thunk_FUN_00459769`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004596ca(void)

{
  undefined4 in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491b3f;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0040f6f7();
  local_8 = 0;
  thunk_FUN_00459769();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_0045971b — 0x45971b

- Classification : internal
- Corps : `0x45971b–0x459768`
- État : pseudocode obtenu
- Evidence : `ev_ada3ea8f23a5fcba3c39a786200b7f45c4e44fa92318b8096bff919b17892647`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401267` — `thunk_FUN_0045a306`
- `0x401825` — `thunk_FUN_0040f73f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045971b(void)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00491b58;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_8 = 0;
  thunk_FUN_0045a306();
  local_8 = 0xffffffff;
  thunk_FUN_0040f73f();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

## FUN_00459769 — 0x459769

- Classification : internal
- Corps : `0x459769–0x45981c`
- État : pseudocode obtenu
- Evidence : `ev_ff48d709d6ec86d4b8dee94154eb562dc78c1c404111300fa311527cbf69af18`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401aff` — `thunk_FUN_0045aeba`
- `0x4023b5` — `thunk_FUN_0045ae6d`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00459769(void)

{
  void *in_ECX;
  short local_8;
  
  DAT_005ea39c = 0;
  DAT_005e8228 = 0;
  _memset(in_ECX,0,0x1f80);
  *(undefined4 *)((int)in_ECX + 0x1f80) = 0;
  _memset(&DAT_005ea3a0,-1,0xc0);
  for (local_8 = 0; local_8 < DAT_005ea4b8; local_8 = local_8 + 1) {
    (&DAT_005ea478)[local_8] = 0;
  }
  *(undefined4 *)((int)in_ECX + 0x2100) = 0;
  *(undefined4 *)((int)in_ECX + 0x2160) = 0;
  thunk_FUN_0045ae6d(0);
  thunk_FUN_0045aeba(0);
  return;
}
```

---

## FUN_0045981d — 0x45981d

- Classification : internal
- Corps : `0x45981d–0x459e48`
- État : pseudocode obtenu
- Evidence : `ev_fff9e50ce789180778b33aec20433a25680da9da33751cc524d839482c18a0a2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401483` — `thunk_FUN_00459e49`
- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401d57` — `thunk_FUN_004593ff`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x472ca0` — `FUN_00472ca0`
- `0x472da0` — `FUN_00472da0`
- `0x472f10` — `FUN_00472f10`
- `0x474b20` — `_memset`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x4a3684` — "data\\"
- `0x4a368c` — "%s\\thing2\\"
- `0x4a369c` — "%d %d"
- `0x4a36a4` — "%s %s %s"
- `0x4a36c0` — "Sound missing: %s"
- `0x4a36d4` — "FALSE"
- `0x4a36dc` — "C:\\float\\src\\soundsys.cpp"
- `0x4a36f8` — "success==TRUE"
- `0x4a3708` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3724` — "mNumSoundItems<=MAX_SOUNDITEMS"
- `0x4a3744` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3768` — "%s%s%s"
- `0x4a3770` — "Missing Sound File: %s"
- `0x4a3788` — "success==0"
- `0x4a3794` — "C:\\float\\src\\soundsys.cpp"
- `0x4a37b0` — "success==TRUE"
- `0x4a37c0` — "C:\\float\\src\\soundsys.cpp"
- `0x4a37dc` — "mNumSoundItems<=MAX_SOUNDITEMS"
- `0x4a37fc` — "C:\\float\\src\\soundsys.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0045981d(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  undefined4 *unaff_FS_OFFSET;
  short local_37c;
  undefined1 local_378 [80];
  undefined1 local_328 [280];
  short local_210;
  undefined4 local_100;
  int local_fc;
  int local_f8;
  undefined1 local_f4 [32];
  undefined1 local_d4 [32];
  int local_b4;
  undefined1 local_b0 [128];
  char local_30 [32];
  undefined4 local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491b7a;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (DAT_004c2ba4 == 0) {
    FUN_00472ca0(local_378,s__s_thing2__004a368c,&DAT_004c2aa8);
    thunk_FUN_00459e49(local_378,1);
  }
  else {
    thunk_FUN_00459e49(s_data__004a3684,0);
  }
  thunk_FUN_0040f6f7();
  local_8 = 0;
  iVar1 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,20000);
  if (iVar1 == 0) {
    iVar1 = thunk_FUN_0040f5b3(local_b0,0);
    if (iVar1 == -1) {
      local_8 = 0xffffffff;
      thunk_FUN_0040f73f();
      uVar2 = 0;
    }
    else {
      FUN_00472f10(local_b0,&DAT_004a3698,&local_b4);
      DAT_005ea4b8 = 0;
      for (local_210 = 0; local_210 < local_b4; local_210 = local_210 + 1) {
        iVar1 = thunk_FUN_0040f5b3(local_b0,0);
        if (iVar1 == -1) {
          local_8 = 0xffffffff;
          thunk_FUN_0040f73f();
          uVar2 = 0;
          goto LAB_00459e39;
        }
        FUN_00472f10(local_b0,s__d__d_004a369c,&local_fc,&local_100);
        for (local_37c = 0; local_37c < local_fc; local_37c = local_37c + 1) {
          (&DAT_005ea3a4)[DAT_005ea4b8 * 3] = local_100;
          DAT_005ea4b8 = DAT_005ea4b8 + 1;
        }
      }
      thunk_FUN_0040f6f7();
      local_8 = CONCAT31(local_8._1_3_,1);
      *(undefined4 *)(in_ECX + 0x1f80) = 0;
      local_f8 = in_ECX;
LAB_00459a5a:
      iVar1 = thunk_FUN_0040f5b3(local_b0,0);
      if (iVar1 != -1) {
        FUN_00472f10(local_b0,s__s__s__s_004a36a4,local_30,local_d4,local_f4);
        FUN_00472da0(local_f8,local_d4);
        iVar1 = __strcmpi(local_30,&DAT_004a36b0);
        if (iVar1 == 0) goto code_r0x00459ac8;
        FUN_00472da0(local_f8 + 0xc,local_f4);
        goto LAB_00459b19;
      }
      if (DAT_004c2ba8 != 0) {
        FUN_00472da0(local_f8,&DAT_004c2ab8);
        FUN_00472ca0(local_f8 + 0xc,s__s_s_s_004a3768,in_ECX + 0x20a4,&DAT_004c2ab8,&DAT_004a3760);
        iVar1 = thunk_FUN_0040f752(local_f8 + 0xc,0x8000);
        if (iVar1 != 0) {
          thunk_FUN_00414ad0(s_Missing_Sound_File___s_004a3770,local_f8 + 0xc);
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3794,0x143,s_success__0_004a3788);
        }
        _memset((void *)(local_f8 + 0x34),0,0x14);
        *(undefined2 *)(local_f8 + 0x44) = 0x14;
        iVar1 = thunk_FUN_004593ff(local_328,local_f8 + 0x34,local_f8 + 0x2c,local_f8 + 0x30);
        if (iVar1 != 1) {
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a37c0,0x149,s_success__TRUE_004a37b0);
        }
        *(int *)(in_ECX + 0x1f80) = *(int *)(in_ECX + 0x1f80) + 1;
        local_f8 = local_f8 + 0x48;
        if (0x70 < *(int *)(in_ECX + 0x1f80)) {
          thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a37fc,0x14e,
                             s_mNumSoundItems<_MAX_SOUNDITEMS_004a37dc);
        }
      }
      local_8 = local_8 & 0xffffff00;
      thunk_FUN_0040f73f();
      local_8 = 0xffffffff;
      thunk_FUN_0040f73f();
      uVar2 = 1;
    }
  }
  else {
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
    uVar2 = 0;
  }
LAB_00459e39:
  *unaff_FS_OFFSET = local_10;
  return uVar2;
code_r0x00459ac8:
  if (DAT_004c2ba8 == 0) {
    FUN_00472ca0(local_f8 + 0xc,&DAT_004a36b8,in_ECX + 0x20a4,local_f4);
LAB_00459b19:
    iVar1 = thunk_FUN_0040f752(local_f8 + 0xc,0x8000);
    if (iVar1 != 0) {
      thunk_FUN_00414ad0(s_Sound_missing___s_004a36c0,local_f8 + 0xc);
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a36dc,0x12e,s_FALSE_004a36d4);
    }
    _memset((void *)(local_f8 + 0x34),0,0x14);
    *(undefined2 *)(local_f8 + 0x44) = 0x14;
    iVar1 = thunk_FUN_004593ff(local_328,local_f8 + 0x34,local_f8 + 0x2c,local_f8 + 0x30);
    if (iVar1 != 1) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3708,0x135,s_success__TRUE_004a36f8);
    }
    *(int *)(in_ECX + 0x1f80) = *(int *)(in_ECX + 0x1f80) + 1;
    local_f8 = local_f8 + 0x48;
    if (0x70 < *(int *)(in_ECX + 0x1f80)) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3744,0x13a,
                         s_mNumSoundItems<_MAX_SOUNDITEMS_004a3724);
    }
  }
  goto LAB_00459a5a;
}
```

---

## FUN_00459e49 — 0x459e49

- Classification : internal
- Corps : `0x459e49–0x459e83`
- État : pseudocode obtenu
- Evidence : `ev_fa2ce81ff4c1212e690d177a3dacfb8b79e527f46af621f483d6794523c301a9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4737e0` — `_strncpy`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00459e49(char *param_1,undefined4 param_2)

{
  int in_ECX;
  
  _strncpy((char *)(in_ECX + 0x20a4),param_1,0x4f);
  *(undefined1 *)(in_ECX + 0x20f3) = 0;
  *(undefined4 *)(in_ECX + 0x20f4) = param_2;
  return;
}
```

---

## FUN_00459e84 — 0x459e84

- Classification : internal
- Corps : `0x459e84–0x45a305`
- État : pseudocode obtenu
- Evidence : `ev_4eb126acfd04cac99fa7bbdbfba18989cbf15cc31ae7955fa0f48b23073449bb`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401244` — `thunk_FUN_0045981d`
- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x401d57` — `thunk_FUN_004593ff`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x472a4a` — `DSOUND.DLL::DirectSoundCreate`

### Chaînes référencées

- `0x4a3818` — "SoundSystem: FAILED DirectSoundCreate.\n"
- `0x4a3840` — "SoundSystem: FAILED SetCooperativeLevel.\n"
- `0x4a386c` — "r==DS_OK"
- `0x4a3878` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3894` — "data\\format.wav"
- `0x4a38a4` — "status==0"
- `0x4a38b0` — "C:\\float\\src\\soundsys.cpp"
- `0x4a38cc` — "success==TRUE"
- `0x4a38dc` — "C:\\float\\src\\soundsys.cpp"
- `0x4a3900` — "Stereo"
- `0x4a3900` — "Stereo"
- `0x4a3900` — "Stereo"
- `0x4a3908` — "Music Format: %d-bit %s.\n"
- `0x4a3924` — "SoundSystem: CreateSoundBuffer (tune) failed.\n"
- `0x4a3954` — "r==DS_OK"
- `0x4a3960` — "C:\\float\\src\\soundsys.cpp"
- `0x4a397c` — "data\\fxformat.wav"
- `0x4a3990` — "status==0"
- `0x4a399c` — "C:\\float\\src\\soundsys.cpp"
- `0x4a39b8` — "success==TRUE"
- `0x4a39c8` — "C:\\float\\src\\soundsys.cpp"
- `0x4a39e4` — "Effects Format: %d-bit %s.\n"
- `0x4a3a00` — "SoundSystem: CreateSoundBuffer SFX%d failed.\n"
- `0x4a3a30` — "r==DS_OK"
- `0x4a3a3c` — "C:\\float\\src\\soundsys.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_00459e84(undefined4 param_1)

{
  undefined4 uVar1;
  int in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_154;
  undefined1 local_150;
  undefined4 local_14f;
  undefined1 local_14b;
  char local_14a [4];
  char local_146 [2];
  char local_144;
  undefined2 local_143;
  undefined1 local_141;
  int local_140;
  int local_13c;
  short local_138;
  undefined1 local_134 [268];
  int local_28;
  undefined4 local_24;
  uint local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined *local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491b90;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_28 = DirectSoundCreate(0,&DAT_005ea39c,0);
  if (local_28 == 0) {
    local_28 = (**(code **)(*DAT_005ea39c + 0x18))(DAT_005ea39c,DAT_004c2b58,3);
    if (local_28 != 0) {
      thunk_FUN_00414ad0(s_SoundSystem__FAILED_SetCooperati_004a3840);
    }
    if (local_28 != 0) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3878,0x179,s_r__DS_OK_004a386c);
    }
    thunk_FUN_0045981d(param_1);
    thunk_FUN_0040f6f7();
    local_8 = 0;
    local_13c = thunk_FUN_0040f752(s_data_format_wav_004a3894,0x8000);
    if (local_13c != 0) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a38b0,0x185,s_status__0_004a38a4);
    }
    local_140 = thunk_FUN_004593ff(local_134,&DAT_005ea460,in_ECX + 0x2094,in_ECX + 0x2098);
    if (local_140 != 1) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a38dc,0x188,s_success__TRUE_004a38cc);
    }
    local_154 = DAT_004a38f8;
    local_150 = DAT_004a38fc;
    local_14f = 0;
    local_14b = 0;
    local_14a[0] = s_Stereo_004a3900[0];
    local_14a[1] = s_Stereo_004a3900[1];
    local_14a[2] = s_Stereo_004a3900[2];
    local_14a[3] = s_Stereo_004a3900[3];
    local_146[0] = s_Stereo_004a3900[4];
    local_146[1] = s_Stereo_004a3900[5];
    local_144 = s_Stereo_004a3900[6];
    local_143 = 0;
    local_141 = 0;
    thunk_FUN_00414ad0(s_Music_Format___d_bit__s__004a3908,DAT_005ea46e,
                       (int)&local_154 + (DAT_005ea462 - 1) * 10);
    local_24 = 0x14;
    local_20 = 0xe0;
    local_18 = 0;
    local_14 = &DAT_005ea460;
    local_1c = 0xc800;
    local_28 = (**(code **)(*DAT_005ea39c + 0xc))(DAT_005ea39c,&local_24,&DAT_005e8228,0);
    if (local_28 != 0) {
      thunk_FUN_00414ad0(s_SoundSystem__CreateSoundBuffer___004a3924);
    }
    if (local_28 != 0) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3960,0x1a7,s_r__DS_OK_004a3954);
    }
    local_20 = local_20 | 2;
    thunk_FUN_0040f966();
    local_13c = thunk_FUN_0040f752(s_data_fxformat_wav_004a397c,0x8000);
    if (local_13c != 0) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a399c,0x1b0,s_status__0_004a3990);
    }
    local_140 = thunk_FUN_004593ff(local_134,&DAT_005ea460,in_ECX + 0x2094,in_ECX + 0x2098);
    if (local_140 != 1) {
      thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a39c8,0x1b4,s_success__TRUE_004a39b8);
    }
    local_14 = &DAT_005ea460;
    thunk_FUN_00414ad0(s_Effects_Format___d_bit__s__004a39e4,DAT_005ea46e,
                       (int)&local_154 + (DAT_005ea462 - 1) * 10);
    for (local_138 = 0; local_138 < DAT_005ea4b8; local_138 = local_138 + 1) {
      local_1c = (&DAT_005ea3a4)[local_138 * 3];
      local_28 = (**(code **)(*DAT_005ea39c + 0xc))
                           (DAT_005ea39c,&local_24,&DAT_005ea478 + local_138,0);
      if (local_28 != 0) {
        thunk_FUN_00414ad0(s_SoundSystem__CreateSoundBuffer_S_004a3a00,(int)local_138);
      }
      if (local_28 != 0) {
        thunk_FUN_00414b64(s_C__float_src_soundsys_cpp_004a3a3c,0x1c4,s_r__DS_OK_004a3a30);
      }
    }
    *(undefined4 *)(in_ECX + 0x2168) = 0;
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
    uVar1 = 1;
  }
  else {
    thunk_FUN_00414ad0(s_SoundSystem__FAILED_DirectSoundC_004a3818);
    uVar1 = 0;
  }
  *unaff_FS_OFFSET = local_10;
  return uVar1;
}
```

---

## FUN_0045a306 — 0x45a306

- Classification : internal
- Corps : `0x45a306–0x45a3f0`
- État : pseudocode obtenu
- Evidence : `ev_76f6ee4570ab719fc7889a5996ec4af3f4c89e012a4685a2b57a5ec6b354c0ec`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401d25` — `thunk_FUN_0040f966`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045a306(void)

{
  short local_8;
  
  thunk_FUN_0040f966();
  if (DAT_005e8228 != (int *)0x0) {
    (**(code **)(*DAT_005e8228 + 0x48))(DAT_005e8228);
    (**(code **)(*DAT_005e8228 + 8))(DAT_005e8228);
    DAT_005e8228 = (int *)0x0;
  }
  for (local_8 = 0; local_8 < DAT_005ea4b8; local_8 = local_8 + 1) {
    if ((&DAT_005ea478)[local_8] != 0) {
      (**(code **)(*(int *)(&DAT_005ea478)[local_8] + 0x48))((&DAT_005ea478)[local_8]);
      (**(code **)(*(int *)(&DAT_005ea478)[local_8] + 8))((&DAT_005ea478)[local_8]);
      (&DAT_005ea478)[local_8] = 0;
    }
  }
  if (DAT_005ea39c != (int *)0x0) {
    (**(code **)(*DAT_005ea39c + 8))(DAT_005ea39c);
    DAT_005ea39c = (int *)0x0;
  }
  return;
}
```

---

## FUN_0045a3f1 — 0x45a3f1

- Classification : internal
- Corps : `0x45a3f1–0x45a4f9`
- État : pseudocode obtenu
- Evidence : `ev_494ea6bf205433872bf270c5cbed99038ff7ecac37ff86deb02a36d65f093383`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010f5` — `thunk_FUN_0045af9c`
- `0x4018bb` — `thunk_FUN_0045aba9`
- `0x401a91` — `thunk_FUN_0045a645`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x4021f8` — `thunk_FUN_004595cc`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0045a3f1(void)

{
  int iVar1;
  undefined4 uVar2;
  int in_ECX;
  
  if (*(int *)(in_ECX + 0x2160) == 1) {
    *(int *)(in_ECX + 0x2164) = *(int *)(in_ECX + 0x2164) + 1;
    iVar1 = thunk_FUN_0045af9c();
    iVar1 = iVar1 + *(int *)(in_ECX + 0x2164) * -4;
    if (iVar1 < 10) {
      if (*(char *)(in_ECX + 0x2108) == '\0') {
        thunk_FUN_0040f966();
      }
      else {
        thunk_FUN_0045aba9(in_ECX + 0x2108,*(undefined4 *)(in_ECX + 0x2158),
                           *(undefined4 *)(in_ECX + 0x215c));
        *(undefined1 *)(in_ECX + 0x2108) = 0;
      }
      *(undefined4 *)(in_ECX + 0x2160) = 0;
    }
    else {
      uVar2 = thunk_FUN_004595cc(iVar1);
      if (DAT_005e8228 != (int *)0x0) {
        (**(code **)(*DAT_005e8228 + 0x3c))(DAT_005e8228,uVar2);
      }
    }
  }
  *(int *)(in_ECX + 0x2168) = *(int *)(in_ECX + 0x2168) + 1;
  iVar1 = thunk_FUN_0045af9c();
  if (iVar1 != 0) {
    thunk_FUN_0045a645();
  }
  return;
}
```

---

## FUN_0045a4fa — 0x45a4fa

- Classification : internal
- Corps : `0x45a4fa–0x45a644`
- État : pseudocode obtenu
- Evidence : `ev_bd09d0fb31669adaca66c8eb417821f71b4cc7663d8859027fffa7ada292ceea`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401276` — `thunk_FUN_0042dd95`
- `0x401fc8` — `thunk_FUN_0045c290`
- `0x472ca0` — `FUN_00472ca0`
- `0x472da0` — `FUN_00472da0`

### Chaînes référencées

- `0x4a3a58` — "Empty"
- `0x4a3a64` — "[%s] (length %d,%d) (lastplayed %d)"

### Pseudocode Ghidra

```c
void FUN_0045a4fa(void)

{
  int iVar1;
  int in_ECX;
  undefined4 local_94;
  int local_90;
  undefined1 local_8c [64];
  undefined1 local_4c [64];
  int local_c;
  int local_8;
  
  local_c = 2;
  for (local_8 = 0; local_8 < 0x10; local_8 = local_8 + 1) {
    local_90 = 0;
    if (*(int *)(&DAT_005ea3a0 + local_8 * 0xc) == -1) {
      FUN_00472da0(local_8c,s_Empty_004a3a58);
    }
    else {
      local_90 = in_ECX + *(int *)(&DAT_005ea3a0 + local_8 * 0xc) * 0x48;
      FUN_00472ca0(local_8c,&DAT_004a3a60,local_90 + 0xc);
    }
    local_94 = 0;
    if (local_90 != 0) {
      local_94 = *(undefined4 *)(local_90 + 0x30);
    }
    FUN_00472ca0(local_4c,s___s___length__d__d___lastplayed___004a3a64,local_8c,
                 (&DAT_005ea3a4)[local_8 * 3],local_94,
                 *(undefined4 *)(&DAT_005ea3a8 + local_8 * 0xc));
    thunk_FUN_0042dd95(1,local_c,local_4c);
    local_c = local_c + 0xd;
  }
  iVar1 = thunk_FUN_0045c290();
  if (iVar1 != 0) {
    thunk_FUN_0042dd95(300,2,in_ECX + DAT_005ea32c * 0x48);
  }
  return;
}
```

---


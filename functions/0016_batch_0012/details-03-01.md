# 0016_batch_0012 — détails (1/3)

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

# 0018_batch_0014 — détails (1/6)

## FUN_004680a3 — 0x4680a3

- Classification : internal
- Corps : `0x4680a3–0x4680fb`
- État : pseudocode obtenu
- Evidence : `ev_8da4c45b3dca6f556398f29e6b4a5da514738074179dd7117e600bf57efa899b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004680a3(void)

{
  int in_ECX;
  ushort *local_10;
  int local_8;
  
  local_8 = 0;
  for (local_10 = (ushort *)(in_ECX + 0x2c1a4); local_10 < (ushort *)(in_ECX + 0x2c6a4);
      local_10 = local_10 + 1) {
    local_8 = local_8 + (uint)*local_10;
  }
  return local_8;
}
```

---

## FUN_004680fc — 0x4680fc

- Classification : internal
- Corps : `0x4680fc–0x46814f`
- État : pseudocode obtenu
- Evidence : `ev_c6c5e10a022ed1fbd74d8c96fc011bb5ed8abd3f41a05782d9821552de2aa011`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004680fc(void)

{
  ushort *in_ECX;
  ushort *local_10;
  int local_8;
  
  local_8 = 0;
  for (local_10 = in_ECX; local_10 < in_ECX + 0x13a4c; local_10 = local_10 + 1) {
    local_8 = local_8 + (uint)*local_10;
  }
  return local_8;
}
```

---

## FUN_00469bf0 — 0x469bf0

- Classification : internal
- Corps : `0x469bf0–0x469bfe`
- État : pseudocode obtenu
- Evidence : `ev_183c5bd4301d509cabfa3ba3e0077df9930a4f5a78e57910a7516d70b3a2dd26`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x469bff` — `FUN_00469bff`
- `0x469c0e` — `FUN_00469c0e`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00469bf0(void)

{
  FUN_00469bff();
  FUN_00469c0e();
  return;
}
```

---

## FUN_00469bff — 0x469bff

- Classification : internal
- Corps : `0x469bff–0x469c0d`
- État : pseudocode obtenu
- Evidence : `ev_b57acbde8452cf42e1b981e908052fee0af21ead88dc6d7947549f0fc292d659`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401dd9` — `thunk_FUN_00469c2f`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00469bff(void)

{
  thunk_FUN_00469c2f();
  return;
}
```

---

## FUN_00469c0e — 0x469c0e

- Classification : internal
- Corps : `0x469c0e–0x469c1f`
- État : pseudocode obtenu
- Evidence : `ev_aac0eee3d47cfdf7733a9c7009d20b5e05ee94b2cfbe6d1ab399d42ce4cdabed`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476c60` — `FUN_00476c60`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00469c0e(void)

{
  FUN_00476c60(FUN_00469c20);
  return;
}
```

---

## FUN_00469c20 — 0x469c20

- Classification : internal
- Corps : `0x469c20–0x469c2e`
- État : pseudocode obtenu
- Evidence : `ev_7ced01ad7aec263ea60514c05c90ff3729a4c7097492dbfd1f960459d13b6ec9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f23` — `thunk_FUN_00469c80`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00469c20(void)

{
  thunk_FUN_00469c80();
  return;
}
```

---

## FUN_00469c2f — 0x469c2f

- Classification : internal
- Corps : `0x469c2f–0x469c7f`
- État : pseudocode obtenu
- Evidence : `ev_e3f219f89f47c3acfdcd0eea8d16136e3b2bf0ac03bafaf07de0ca0a63affe79`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4015fa` — `thunk_FUN_00469cce`
- `0x401f55` — `thunk_FUN_0040e160`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00469c2f(void)

{
  undefined4 in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491d2f;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0040e160();
  local_8 = 0;
  thunk_FUN_00469cce();
  *unaff_FS_OFFSET = local_10;
  return in_ECX;
}
```

---

## FUN_00469c80 — 0x469c80

- Classification : internal
- Corps : `0x469c80–0x469ccd`
- État : pseudocode obtenu
- Evidence : `ev_d64309c6ffe90ae496c1d56b7da718a8b671d6e77a3295b24a1e48e220466912`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40158c` — `thunk_FUN_0040e1ad`
- `0x402360` — `thunk_FUN_00469dfc`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00469c80(void)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00491d48;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_8 = 0;
  thunk_FUN_00469dfc();
  local_8 = 0xffffffff;
  thunk_FUN_0040e1ad();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

## FUN_00469cce — 0x469cce

- Classification : internal
- Corps : `0x469cce–0x469dfb`
- État : pseudocode obtenu
- Evidence : `ev_d58400ae0c35c006e36627c6ba6ce0c2542e52490b31798b57310ce1ee7e2602`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00469cce(void)

{
  void *in_ECX;
  
  *(undefined2 *)((int)in_ECX + 0x29f0) = 0;
  *(undefined2 *)((int)in_ECX + 0x1f38) = 0;
  *(undefined2 *)((int)in_ECX + 0x29f2) = 0xffff;
  *(undefined2 *)((int)in_ECX + 0x29f4) = 0xffff;
  *(undefined2 *)((int)in_ECX + 0x2cf8) = 0;
  *(undefined2 *)((int)in_ECX + 0x2e7c) = 0;
  *(undefined2 *)((int)in_ECX + 0x2fc0) = 0;
  *(undefined4 *)((int)in_ECX + 0x1f3c) = 0xffffffff;
  _memset((void *)((int)in_ECX + 8000),0,0xab0);
  _memset(in_ECX,0,0x1f38);
  _memset((void *)((int)in_ECX + 0x2cfc),0,0x180);
  _memset((void *)((int)in_ECX + 0x2e80),0,0x140);
  *(undefined4 *)((int)in_ECX + 0x62b8) = 0;
  *(undefined4 *)((int)in_ECX + 0x62b0) = 0;
  *(undefined4 *)((int)in_ECX + 0x62b4) = 0;
  *(undefined4 *)((int)in_ECX + 0x62c0) = 0;
  *(undefined1 *)((int)in_ECX + 0x62c4) = 0;
  *(undefined2 *)((int)in_ECX + 0x630a) = 0;
  *(undefined4 *)((int)in_ECX + 0x630c) = 0;
  *(undefined4 *)((int)in_ECX + 0x6310) = 0;
  return;
}
```

---

## FUN_00469dfc — 0x469dfc

- Classification : internal
- Corps : `0x469dfc–0x469f55`
- État : pseudocode obtenu
- Evidence : `ev_db75b549bdac1e43005c0697ebad801d41cf9c1e7b4d7532e6f4508c66e32e42`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40134d` — `thunk_FUN_0040e2a3`
- `0x401749` — `thunk_FUN_00414c97`
- `0x401d3e` — `thunk_FUN_00414d89`
- `0x402298` — `thunk_FUN_00414ad0`

### Chaînes référencées

- `0x4a5498` — "***MOVE: %s  %d %d %d %d"
- `0x4a54b4` — "mWindows[i].window"

### Pseudocode Ghidra

```c
void FUN_00469dfc(void)

{
  undefined4 *puVar1;
  int in_ECX;
  short local_8;
  
  for (local_8 = 0; local_8 < 0x29a; local_8 = local_8 + 1) {
    if (*(int *)(in_ECX + 4 + local_8 * 0xc) != 0) {
      if ((*(uint *)(in_ECX + 8 + local_8 * 0xc) & 1) != 0) {
        thunk_FUN_00414ad0(s____MOVE___s__d__d__d__d_004a5498,
                           *(int *)(in_ECX + 4 + local_8 * 0xc) + 0x20,
                           *(undefined4 *)(*(int *)(in_ECX + 4 + local_8 * 0xc) + 0xc),
                           *(undefined4 *)(*(int *)(in_ECX + 4 + local_8 * 0xc) + 0x10),
                           *(undefined4 *)(*(int *)(in_ECX + 4 + local_8 * 0xc) + 0x14),
                           *(undefined4 *)(*(int *)(in_ECX + 4 + local_8 * 0xc) + 0x18));
      }
      thunk_FUN_00414d89(s_mWindows_i__window_004a54b4,*(undefined4 *)(in_ECX + 4 + local_8 * 0xc));
      puVar1 = *(undefined4 **)(in_ECX + 4 + local_8 * 0xc);
      if (puVar1 != (undefined4 *)0x0) {
        (**(code **)*puVar1)(1);
      }
      *(undefined4 *)(in_ECX + 4 + local_8 * 0xc) = 0;
    }
  }
  if (DAT_004c2f30 != 0) {
    thunk_FUN_00414c97(DAT_004c2f30);
    DAT_004c2f30 = 0;
  }
  thunk_FUN_0040e2a3();
  return;
}
```

---

## FUN_00469f56 — 0x469f56

- Classification : internal
- Corps : `0x469f56–0x46a4e3`
- État : pseudocode obtenu
- Evidence : `ev_3b7d1c7373d2274d945cf5579c6d5b74b907c2a1517b6587e6a2c23a92bec22e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x4014ba` — `thunk_FUN_0042dd47`
- `0x4016e5` — `thunk_FUN_00429371`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x401b9a` — `thunk_FUN_0046bacf`
- `0x401d84` — `thunk_FUN_0046a4fc`
- `0x401e10` — `thunk_FUN_0046a5b7`
- `0x401e83` — `thunk_FUN_0046be81`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401ffa` — `thunk_FUN_0041412d`
- `0x402194` — `thunk_FUN_0042ee48`
- `0x40227f` — `thunk_FUN_0046c25d`
- `0x4024c8` — `thunk_FUN_0046b752`

### Chaînes référencées

- `0x4a54c8` — "mhwndFocus!=-1"
- `0x4a54d8` — "C:\\float\\src\\winman.cpp"
- `0x4a54f0` — "mhwndFocus!=-1"
- `0x4a5500` — "C:\\float\\src\\winman.cpp"

### Pseudocode Ghidra

```c
bool FUN_00469f56(void)

{
  int iVar1;
  int in_ECX;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_2c [5];
  int local_18;
  undefined4 local_14;
  short local_10;
  short local_e;
  ushort local_c;
  ushort local_a;
  undefined2 local_8;
  
  if ((*(int *)(in_ECX + 0x1f3c) != -1) &&
     (*(int *)(*(int *)(in_ECX + 4 + *(int *)(in_ECX + 0x1f3c) * 0xc) + 0x38) == 0)) {
    *(undefined4 *)(in_ECX + 0x1f3c) = 0xffffffff;
  }
  while (iVar1 = thunk_FUN_0042ee48(&local_14), iVar1 == 1) {
    switch(local_14) {
    case 1:
      if (*(int *)(in_ECX + 0x6314) != 0) {
        if (*(int *)(in_ECX + 0x1f3c) == -1) {
          thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a54d8,0x107,s_mhwndFocus___1_004a54c8);
        }
        thunk_FUN_0046c1b4(4,0,*(int *)(in_ECX + 4 + *(int *)(in_ECX + 0x1f3c) * 0xc) + 8);
        thunk_FUN_00429371((int)local_10 - (int)*(short *)(in_ECX + 0x62bc),
                           (int)local_e - (int)*(short *)(in_ECX + 0x62be));
        *(uint *)(in_ECX + 8 + *(int *)(in_ECX + 0x1f3c) * 0xc) =
             *(uint *)(in_ECX + 8 + *(int *)(in_ECX + 0x1f3c) * 0xc) | 1;
      }
      *(short *)(in_ECX + 0x62bc) = local_10;
      *(short *)(in_ECX + 0x62be) = local_e;
      if ((((*(int *)(in_ECX + 0x6314) == 0) &&
           (thunk_FUN_0046be81(), *(int *)(in_ECX + 0x1f3c) != -1)) &&
          (thunk_FUN_0046c371(*(undefined4 *)(in_ECX + 0x1f3c),10,(int)local_10,(int)local_e),
          *(int *)(in_ECX + 0x630c) != 0)) &&
         (*(undefined4 *)(in_ECX + 0x6310) = 0,
         *(int *)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130) != 0)) {
        (**(code **)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130))
                  (4,(int)local_10,(int)local_e,in_ECX + 0x6310);
      }
      break;
    case 2:
      if (*(int *)(in_ECX + 0x630c) == 0) {
        if ((local_c & 6) == 0) {
          thunk_FUN_0046c25d(6,(int)local_10,(int)local_e,0);
        }
        else {
          *(undefined4 *)(in_ECX + 0x630c) = 1;
          thunk_FUN_0042dd47(2);
        }
      }
      else {
        *(undefined4 *)(in_ECX + 0x630c) = 0;
        thunk_FUN_0042dd47(0);
        thunk_FUN_0046c25d(0xb,1,0,0);
      }
      break;
    case 4:
      if (*(int *)(in_ECX + 0x630c) == 0) {
        if ((local_c & 5) == 0) {
          if (*(int *)(in_ECX + 0x6314) == 0) {
            thunk_FUN_0046c25d(7,(int)local_10,(int)local_e,0);
          }
          else {
            if (*(int *)(in_ECX + 0x1f3c) == -1) {
              thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5500,0x175,s_mhwndFocus___1_004a54f0)
              ;
            }
            puVar2 = (undefined4 *)(*(int *)(in_ECX + 4 + *(int *)(in_ECX + 0x1f3c) * 0xc) + 8);
            puVar3 = local_2c;
            for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
              *puVar3 = *puVar2;
              puVar2 = puVar2 + 1;
              puVar3 = puVar3 + 1;
            }
            thunk_FUN_0046c1b4(4,0,local_2c);
            puVar2 = (undefined4 *)(in_ECX + 0x6318);
            puVar3 = (undefined4 *)(*(int *)(in_ECX + 4 + *(int *)(in_ECX + 0x1f3c) * 0xc) + 8);
            for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
              *puVar3 = *puVar2;
              puVar2 = puVar2 + 1;
              puVar3 = puVar3 + 1;
            }
            *(uint *)(in_ECX + 8 + *(int *)(in_ECX + 0x1f3c) * 0xc) =
                 *(uint *)(in_ECX + 8 + *(int *)(in_ECX + 0x1f3c) * 0xc) & 0xfffffffe;
            *(undefined4 *)(in_ECX + 0x6314) = 0;
          }
        }
        else {
          *(undefined4 *)(in_ECX + 0x630c) = 1;
          thunk_FUN_0042dd47(2);
        }
      }
      else {
        *(undefined4 *)(in_ECX + 0x630c) = 0;
        thunk_FUN_0042dd47(0);
        thunk_FUN_0046c25d(0xb,1,0,0);
      }
      break;
    case 6:
      if ((local_a & 0xff) == 1) {
        local_18 = 1;
        if (((local_a & 0x200) != 0) || (local_c == 0x1b)) {
          local_18 = thunk_FUN_0046a5b7(local_c);
        }
        if (((local_c == 0xd) && (DAT_004befe0 != 0)) &&
           ((*(short *)(in_ECX + 0x29f2) == 0 ||
            ((*(short *)(in_ECX + 0x29f2) == 2 || (*(short *)(in_ECX + 0x29f2) == 3)))))) {
          if (*(int *)(in_ECX + 0x62c0) == 0) {
            *(undefined4 *)(in_ECX + 0x62c0) = 1;
            *(undefined1 *)(in_ECX + 0x62c4) = 0;
            *(undefined2 *)(in_ECX + 0x630a) = 0;
          }
          else {
            *(undefined4 *)(in_ECX + 0x62c0) = 0;
            if (0 < *(short *)(in_ECX + 0x630a)) {
              thunk_FUN_0041412d(in_ECX + 0x62c4,0xffff);
            }
          }
          local_18 = 0;
        }
        if (*(int *)(in_ECX + 0x62c0) != 0) {
          thunk_FUN_0046a4fc(local_8);
          local_18 = 0;
        }
        if (local_18 == 1) {
          thunk_FUN_0046c25d(5,(int)(short)local_c,(int)(short)local_a,0);
        }
      }
    }
  }
  if (*(short *)(in_ECX + 0x2e7c) != 0) {
    thunk_FUN_0046bacf();
  }
  while (0 < *(short *)(in_ECX + 0x2cf8)) {
    thunk_FUN_0046b752();
  }
  if ((-1 < *(short *)(in_ECX + 0x29f2)) &&
     (*(int *)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130) != 0)) {
    (**(code **)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130))(3,0,0,0);
  }
  return *(int *)(in_ECX + 0x62b8) == 0;
}
```

---

## FUN_0046a4fc — 0x46a4fc

- Classification : internal
- Corps : `0x46a4fc–0x46a5b6`
- État : pseudocode obtenu
- Evidence : `ev_d55629d5154955eee9995a3684f90b3d09f75094dc652d0f894530e5de308064`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046a4fc(short param_1)

{
  int in_ECX;
  
  if (param_1 == 8) {
    if (0 < *(short *)(in_ECX + 0x630a)) {
      *(short *)(in_ECX + 0x630a) = *(short *)(in_ECX + 0x630a) + -1;
    }
    *(undefined1 *)(in_ECX + 0x62c4 + (int)*(short *)(in_ECX + 0x630a)) = 0;
  }
  else if (((0x1f < param_1) && (param_1 < 0xe2)) && (*(short *)(in_ECX + 0x630a) < 0x45)) {
    *(undefined1 *)(in_ECX + 0x62c4 + (int)*(short *)(in_ECX + 0x630a)) = (undefined1)param_1;
    *(short *)(in_ECX + 0x630a) = *(short *)(in_ECX + 0x630a) + 1;
    *(undefined1 *)(in_ECX + 0x62c4 + (int)*(short *)(in_ECX + 0x630a)) = 0;
  }
  return;
}
```

---

## FUN_0046a5b7 — 0x46a5b7

- Classification : internal
- Corps : `0x46a5b7–0x46acc0`
- État : pseudocode obtenu
- Evidence : `ev_c658f75f34deec42ac063f4d2a1e83ba846ef040658718864d73fb6ccd2f2ec6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4013fc` — `thunk_FUN_0042d44d`
- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x40150f` — `thunk_FUN_0046ff6f`
- `0x40168b` — `thunk_FUN_0045749a`
- `0x401744` — `thunk_FUN_00448436`
- `0x401749` — `thunk_FUN_00414c97`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x401af0` — `thunk_FUN_00467be5`
- `0x401b54` — `thunk_FUN_0042c608`
- `0x401d48` — `thunk_FUN_00462e66`
- `0x401d8e` — `thunk_FUN_004140dd`
- `0x401d9d` — `thunk_FUN_00460072`
- `0x401dd4` — `thunk_FUN_0041c146`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401f00` — `thunk_FUN_0045ab46`
- `0x401f5f` — `thunk_FUN_0042dc4e`
- `0x40205e` — `thunk_FUN_0040fac8`
- `0x402176` — `thunk_FUN_00414bf7`
- `0x4021e9` — `thunk_FUN_004576c7`
- `0x40228e` — `thunk_FUN_00414081`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x40231f` — `thunk_FUN_00462fa3`
- `0x474b20` — `_memset`
- `0x478410` — `FUN_00478410`

### Chaînes référencées

- `0x4a5518` — "Entering MakeGIF"
- `0x4a552c` — "quick.sav"
- `0x4a5538` — "quick.sav"
- `0x4a5544` — "resume.gam"
- `0x4a5550` — "06.sav"
- `0x4a5558` — "07.sav"

### Pseudocode Ghidra

```c
undefined4 FUN_0046a5b7(undefined2 param_1)

{
  void *_Dst;
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int extraout_ECX;
  undefined4 *unaff_FS_OFFSET;
  uint uStackY_33cbc;
  int local_364;
  int local_35c;
  undefined4 local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491d76;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  FUN_00478410();
  switch(param_1) {
  case 0x24:
    if (DAT_004c2b74 != 0) {
      thunk_FUN_0040f6f7();
      local_8 = 0;
      thunk_FUN_0040f6f7();
      local_8._0_1_ = 1;
      iVar1 = thunk_FUN_0040f752();
      iVar2 = thunk_FUN_0040f752();
      if (iVar1 + iVar2 == 0) {
        thunk_FUN_0040fac8();
        thunk_FUN_0040fac8();
        thunk_FUN_00462e66();
        local_8._0_1_ = 2;
        thunk_FUN_00467be5();
        thunk_FUN_00467be5();
        for (uStackY_33cbc = 0; uStackY_33cbc < 0x33838; uStackY_33cbc = uStackY_33cbc + 1) {
        }
        local_8._0_1_ = 1;
        thunk_FUN_00462fa3();
        local_8 = (uint)local_8._1_3_ << 8;
        thunk_FUN_0040f73f();
        local_8 = 0xffffffff;
        thunk_FUN_0040f73f();
      }
      else {
        local_8 = (uint)local_8._1_3_ << 8;
        thunk_FUN_0040f73f();
        local_8 = 0xffffffff;
        thunk_FUN_0040f73f();
      }
    }
    break;
  default:
    uVar3 = 1;
    goto LAB_0046acb1;
  case 0x31:
  case 0x32:
  case 0x33:
  case 0x34:
    thunk_FUN_0042c608();
    thunk_FUN_0046c1b4();
    break;
  case 0x38:
  case 0x6d:
    if (((DAT_004befe0 == 0) || (DAT_004c2bb4 != 0)) && (0 < DAT_004bf110 + -1)) {
      thunk_FUN_004140dd();
    }
    break;
  case 0x39:
  case 0x6b:
    if (((DAT_004befe0 == 0) || (DAT_004c2bb4 != 0)) && (DAT_004bf110 + 1 < 4)) {
      thunk_FUN_004140dd();
    }
    break;
  case 0x41:
    if (DAT_004c2b74 != 0) {
      DAT_00630ab0 = (uint)(DAT_00630ab0 == 0);
    }
    break;
  case 0x43:
    if (DAT_004c2b74 != 0) {
      DAT_004c2b7c = (uint)(DAT_004c2b7c == 0);
    }
    break;
  case 0x45:
    if (DAT_004c2b74 != 0) {
      thunk_FUN_0041c146();
    }
    break;
  case 0x46:
    if (DAT_004c2b74 != 0) {
      DAT_004c2b78 = (uint)(DAT_004c2b78 == 0);
    }
    break;
  case 0x47:
    _Dst = (void *)thunk_FUN_00414bf7();
    _memset(_Dst,0,0x4b000);
    thunk_FUN_0042d44d();
    thunk_FUN_0042dc4e();
    thunk_FUN_00414ad0();
    thunk_FUN_00448436();
    thunk_FUN_00414c97();
    break;
  case 0x48:
    if (DAT_004c2b74 != 0) {
      DAT_004c2bac = (uint)(DAT_004c2bac == 0);
      thunk_FUN_0046c1b4();
    }
    break;
  case 0x49:
    if (DAT_004c2b74 != 0) {
      thunk_FUN_0046c1b4();
    }
    break;
  case 0x4c:
    if (DAT_004c2b74 != 0) {
      thunk_FUN_00460072();
    }
    break;
  case 0x4d:
    if (DAT_004c2b74 != 0) {
      DAT_004c2b8c = (uint)(DAT_004c2b8c == 0);
    }
    break;
  case 0x51:
    if (DAT_004c2b74 != 0) {
      DAT_00630aac = (uint)(DAT_00630aac == 0);
    }
    break;
  case 0x52:
    if ((DAT_004befe0 == 0) && (DAT_004c2b74 != 0)) {
      thunk_FUN_004576c7();
      thunk_FUN_0046c1b4();
    }
    break;
  case 0x53:
    if ((DAT_004befe0 == 0) && (DAT_004c2b74 != 0)) {
      thunk_FUN_0045749a();
    }
    break;
  case 0x56:
    DAT_00630ab4 = (uint)(DAT_00630ab4 == 0);
    break;
  case 0x57:
    if (DAT_004c2b74 != 0) {
      if (DAT_004befe0 == 0) {
        thunk_FUN_0046c1b4();
      }
      else {
        thunk_FUN_00414081();
      }
    }
    break;
  case 0x58:
    if ((1 < *(short *)(extraout_ECX + 0x29f2)) && (DAT_004befe0 == 0)) {
      *(undefined2 *)(extraout_ECX + 0x29f4) = *(undefined2 *)(extraout_ECX + 0x29f2);
      thunk_FUN_0045749a();
    }
    *(undefined4 *)(extraout_ECX + 0x62b8) = 1;
    break;
  case 0x59:
    if (DAT_004c2b74 != 0) {
      for (local_35c = 0; local_35c < (int)(uint)DAT_006136b0; local_35c = local_35c + 1) {
        for (local_364 = 0; local_364 < (short)(&DAT_005eebc0)[local_35c * 0x14f4];
            local_364 = local_364 + 1) {
        }
      }
    }
    break;
  case 0x5a:
    if (DAT_004c2b74 != 0) {
      thunk_FUN_0046ff6f();
      thunk_FUN_0045ab46();
    }
    break;
  case 0xdb:
    if (DAT_004c2b74 != 0) {
      if (DAT_004c2b60 < 0xb) {
        DAT_004c2b60 = 5;
      }
      else {
        DAT_004c2b60 = DAT_004c2b60 - 5;
      }
    }
    break;
  case 0xdd:
    if (DAT_004c2b74 != 0) {
      DAT_004c2b60 = DAT_004c2b60 + 5;
    }
  }
  uVar3 = 0;
LAB_0046acb1:
  *unaff_FS_OFFSET = local_10;
  return uVar3;
}
```

---

## FUN_0046ade3 — 0x46ade3

- Classification : internal
- Corps : `0x46ade3–0x46ae18`
- État : pseudocode obtenu
- Evidence : `ev_248b66099002cd89daeaf7dd64aa1b25282ddc4e480de5f4c1a3d47a2dc17f61`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401712` — `thunk_FUN_004289a7`
- `0x401c30` — `thunk_FUN_0042de03`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046ade3(undefined4 param_1,int param_2,undefined4 *param_3,int *param_4,
                 undefined4 *param_5)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = thunk_FUN_0042de03();
  iVar2 = thunk_FUN_004289a7(uVar1);
  *param_4 = param_2 + 1 + iVar2;
  *param_3 = 10;
  *param_5 = 0x26c;
  return;
}
```

---

## FUN_0046ae19 — 0x46ae19

- Classification : internal
- Corps : `0x46ae19–0x46b751`
- État : pseudocode obtenu
- Evidence : `ev_5f7ce4f254c4db6c64349b5391b74392190f664e9f8c4fa166b9a1248ee1c127`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401262` — `thunk_FUN_0045a4fa`
- `0x401424` — `thunk_FUN_0041072f`
- `0x401442` — `thunk_FUN_0041169f`
- `0x4014c9` — `thunk_FUN_0042de0d`
- `0x40163b` — `thunk_FUN_00404c3b`
- `0x4017df` — `thunk_FUN_0041be72`
- `0x4017e9` — `thunk_FUN_004289c0`
- `0x401c30` — `thunk_FUN_0042de03`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f14` — `thunk_FUN_00404770`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401f87` — `thunk_FUN_0041417a`
- `0x402086` — `thunk_FUN_00404c5a`
- `0x4020e0` — `thunk_FUN_0040ec89`
- `0x40218a` — `thunk_FUN_00410765`
- `0x40229d` — `thunk_FUN_00405e11`
- `0x4022fc` — `thunk_FUN_00428baa`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472ca0` — `FUN_00472ca0`
- `0x472da0` — `FUN_00472da0`
- `0x472e90` — `_strlen`
- `0x474b20` — `_memset`

### Chaînes référencées

- `0x4a5560` — "wnd_index>=0"
- `0x4a5570` — "C:\\float\\src\\winman.cpp"
- `0x4a5588` — "mhwndFocus!=-1"
- `0x4a5598` — "C:\\float\\src\\winman.cpp"
- `0x4a55b8` — "tribe<MAX_TRIBES"
- `0x4a55cc` — "C:\\float\\src\\winman.cpp"
- `0x4a55e4` — "%s: %s"
- `0x4a55ec` — "Lost World Sync"
- `0x4a55fc` — "Lost Flt Sync"
- `0x4a560c` — "Lost Task Sync"
- `0x4a561c` — "Lost Island Sync"
- `0x4a5630` — "Lost WORLDRAND Sync"
- `0x4a5644` — "PAUSE"
- `0x4a564c` — "1.16F"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0046ae19(void)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  int in_ECX;
  undefined1 local_1f0 [32];
  undefined4 local_1d0;
  int local_1cc;
  int local_1c8;
  int local_1c4 [2];
  int local_1bc [2];
  int local_1b4;
  int local_1b0;
  size_t local_1ac;
  int local_1a8;
  int local_1a4;
  undefined1 local_1a0;
  undefined1 local_19c [256];
  int local_9c;
  undefined4 local_98;
  undefined4 local_94;
  int local_90;
  int *local_8c;
  short local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined1 local_70 [80];
  int local_20;
  int local_1c;
  int local_18;
  short local_14;
  undefined4 local_10;
  char *local_c;
  int local_8;
  
  if (-1 < *(short *)(in_ECX + 0x29f2)) {
    if ((*(int *)(in_ECX + 0x62b0) != 0) || (*(int *)(in_ECX + 0x62b4) < 0x100)) {
      thunk_FUN_00410765(in_ECX + 0x5fb0,0,0x100 - *(int *)(in_ECX + 0x62b4));
      *(int *)(in_ECX + 0x62b4) = *(int *)(in_ECX + 0x62b4) + 4;
      *(undefined4 *)(in_ECX + 0x62b0) = 0;
    }
    local_14 = *(short *)(in_ECX + 8000 + *(short *)(in_ECX + 0x29f2) * 0x130);
    local_10 = 0;
    for (local_88 = 0; local_88 < 0x4a; local_88 = local_88 + 1) {
      if (local_88 < 0) {
        thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5570,0x2ee,s_wnd_index>_0_004a5560);
      }
      local_8 = *(int *)(in_ECX + *(short *)(in_ECX + 0x29f2) * 0x130 + 0x1f44 + local_88 * 4);
      if (local_8 != 0) {
        local_14 = local_14 + -1;
        local_8c = *(int **)(in_ECX + 4 + local_8 * 0xc);
        if (local_8c[0xd] != 0) {
          (**(code **)(*local_8c + 8))(0);
        }
      }
      if (local_14 == 0) break;
    }
    local_80 = 0;
    local_7c = 0;
    local_78 = 0x27f;
    local_74 = 0x1df;
    local_84 = thunk_FUN_0042d28f();
    _DAT_004c2f38 = thunk_FUN_0042dd0f(6);
    _DAT_004c2f38 = _DAT_004c2f38 & 0xff;
    if (*(int *)(in_ECX + 0x6314) != 0) {
      if (*(int *)(in_ECX + 0x1f3c) == -1) {
        thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5598,0x306,s_mhwndFocus___1_004a5588);
      }
      local_90 = *(int *)(in_ECX + 4 + *(int *)(in_ECX + 0x1f3c) * 0xc);
      uVar1 = thunk_FUN_0042dd0f(1,0,0xffffffff);
      thunk_FUN_0041169f(&local_84,*(undefined4 *)(local_90 + 0xc),*(undefined4 *)(local_90 + 0x10),
                         *(undefined4 *)(local_90 + 0x14),*(undefined4 *)(local_90 + 0x18),uVar1);
    }
    if (*(int *)(in_ECX + 0x62c0) != 0) {
      FUN_00472ca0(local_70,&DAT_004a55b0,in_ECX + 0x62c4);
      thunk_FUN_004289c0(&local_84,1,300,local_70);
    }
    if (DAT_00630ab0 != 0) {
      _memset(local_19c,0,0xff);
      for (local_9c = 0x20; local_9c < 0xe2; local_9c = local_9c + 1) {
        *(undefined1 *)((int)local_1bc + local_9c) = (undefined1)local_9c;
      }
      local_98 = thunk_FUN_0042de03();
      local_94 = thunk_FUN_0042de0d();
      local_1a0 = local_19c[0x46];
      local_19c[0x46] = 0;
      thunk_FUN_004289c0(&local_84,5,0x14,local_19c);
      thunk_FUN_004289c0(&local_84,5,0x5a,local_19c);
      thunk_FUN_004289c0(&local_84,5,0xa0,local_19c);
      local_19c[0x46] = local_1a0;
      local_1a0 = local_19c[0x8c];
      local_19c[0x8c] = 0;
      thunk_FUN_004289c0(&local_84,5,0x28,local_19c + 0x46);
      thunk_FUN_004289c0(&local_84,5,0x6e,local_19c + 0x46);
      thunk_FUN_004289c0(&local_84,5,0xaf,local_19c + 0x46);
      local_19c[0x8c] = local_1a0;
      thunk_FUN_004289c0(&local_84,5,0x3c,local_19c + 0x8c);
      thunk_FUN_004289c0(&local_84,5,0x82,local_19c + 0x8c);
      thunk_FUN_004289c0(&local_84,5,0xbe,local_19c + 0x8c);
    }
    local_c = (char *)0x0;
LAB_0046b2a0:
    local_c = (char *)thunk_FUN_0041417a(&local_18);
    if (local_c != (char *)0x0) {
      local_1a4 = 0;
      while ((local_1a4 < 4 &&
             ((*(uint *)(&DAT_004bf0f0 + local_18 * 4) & 1 << ((byte)local_1a4 & 0x1f)) == 0))) {
        local_1a4 = local_1a4 + 1;
      }
      if (3 < local_1a4) {
        thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a55cc,0x342,s_tribe<MAX_TRIBES_004a55b8);
      }
      if (*(int *)(&DAT_006192a0 + DAT_0049f538 * 4 + local_1a4 * 0x14a0) != 0) {
        for (local_1a8 = 0; local_1a8 < 8; local_1a8 = local_1a8 + 1) {
          if ((&DAT_00630ab8)[local_1a8 * 0x80] == '\0') {
            local_1ac = _strlen(local_c);
            FUN_00472da0(&DAT_00630ab8 + local_1a8 * 0x80,local_c);
            *(int *)(&DAT_0062a740 + local_1a8 * 4) = local_18;
            iVar2 = thunk_FUN_0041be72();
            *(int *)(&DAT_0062a760 + local_1a8 * 4) =
                 iVar2 + DAT_004c2b54 * ((int)local_1ac / 10 + 5);
            break;
          }
        }
      }
      goto LAB_0046b2a0;
    }
    local_20 = 10;
    local_c = (char *)0x0;
    for (local_1c = 0; local_1c < 8; local_1c = local_1c + 1) {
      if ((&DAT_00630ab8)[local_1c * 0x80] != '\0') {
        uVar3 = thunk_FUN_0041be72();
        if (*(uint *)(&DAT_0062a760 + local_1c * 4) < uVar3) {
          (&DAT_00630ab8)[local_1c * 0x80] = 0;
        }
        else {
          FUN_00472ca0(local_70,s__s___s_004a55e4,
                       &DAT_004beff0 + *(int *)(&DAT_0062a740 + local_1c * 4) * 0x40,
                       &DAT_00630ab8 + local_1c * 0x80);
          thunk_FUN_004289c0(&local_84,10,local_20,local_70);
          local_20 = local_20 + 0xd;
        }
      }
    }
    if (DAT_00630aac != 0) {
      thunk_FUN_0045a4fa();
    }
    if (DAT_0049b5d8 == 0) {
      thunk_FUN_004289c0(&local_84,500,10,s_Lost_World_Sync_004a55ec);
      if (DAT_0049b5dc == 0) {
        thunk_FUN_004289c0(&local_84,500,0x16,s_Lost_Flt_Sync_004a55fc);
      }
      if (DAT_0049b5e0 == 0) {
        thunk_FUN_004289c0(&local_84,500,0x22,s_Lost_Task_Sync_004a560c);
      }
      if (DAT_0049b5e4 == 0) {
        thunk_FUN_004289c0(&local_84,500,0x2e,s_Lost_Island_Sync_004a561c);
      }
    }
    if (DAT_0049b5ec == 0) {
      thunk_FUN_004289c0(&local_84,100,10,s_Lost_WORLDRAND_Sync_004a5630);
    }
    if ((*(int *)(in_ECX + 0x630c) != 0) && (*(int *)(in_ECX + 0x6310) != 0)) {
      local_1b0 = local_20;
      if (*(short *)(DAT_005e8220 + 0x88) != 0) {
        local_1b0 = local_20 + 0x6e;
      }
      _DAT_004c2f38 = thunk_FUN_0042dd0f(5);
      _DAT_004c2f38 = _DAT_004c2f38 & 0xff;
      thunk_FUN_00428baa(&local_84,10,local_20,*(undefined4 *)(in_ECX + 0x6310),0,&LAB_0040235b);
    }
    if ((DAT_004bf124 != 0) && (local_1b4 = thunk_FUN_0040ec89(s_PAUSE_004a5644,1), local_1b4 != 0))
    {
      thunk_FUN_00405e11(local_1b4,0,0,0,0,local_1c4);
      local_1cc = (local_1bc[0] - local_1c4[0]) + 1;
      local_1c8 = (0x280 - local_1cc) / 2;
      if (local_1c8 < 0) {
        local_1c8 = 0;
      }
      if (0x27f < local_1c8) {
        local_1c8 = 0x27f;
      }
      if (DAT_0062d172 == 3) {
        thunk_FUN_00404770(&local_84,local_1b4,0,local_1c8,0x70);
      }
      else if (DAT_0062d172 == 2) {
        local_1d0 = thunk_FUN_0041072f();
        thunk_FUN_00404c3b(local_1d0);
        thunk_FUN_00404c5a(&local_84,local_1b4,0,local_1c8,0x70);
      }
    }
    if (DAT_00630ab4 != 0) {
      FUN_00472ca0(local_1f0,&DAT_004a5654,s_1_16F_004a564c);
      thunk_FUN_004289c0(&local_84,0x244,10,local_1f0);
    }
    thunk_FUN_0042d38a();
  }
  return;
}
```

---

## FUN_0046b752 — 0x46b752

- Classification : internal
- Corps : `0x46b752–0x46b90f`
- État : pseudocode obtenu
- Evidence : `ev_ace469c689a216dc474a889d452020df7bb5a196975334651249aea7b2412c34`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40146f` — `thunk_FUN_0042d87c`
- `0x401ad2` — `thunk_FUN_0046c7b5`
- `0x401d8e` — `thunk_FUN_004140dd`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401f82` — `thunk_FUN_0046c640`
- `0x402022` — `thunk_FUN_00406604`
- `0x40227f` — `thunk_FUN_0046c25d`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x4022bb` — `thunk_FUN_0042d3fb`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x4734a0` — `FUN_004734a0`

### Chaînes référencées

- `0x4a5658` — "SetState to %d (%d)"
- `0x4a566c` — "FALSE"
- `0x4a5674` — "C:\\float\\src\\winman.cpp"

### Pseudocode Ghidra

```c
void FUN_0046b752(void)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined1 uVar5;
  undefined4 uVar6;
  int in_ECX;
  short local_18;
  undefined2 local_8;
  
  FUN_004734a0(in_ECX + 0x2b78,in_ECX + 0x29f8,0x180);
  sVar1 = *(short *)(in_ECX + 0x2cf8);
  *(undefined2 *)(in_ECX + 0x2cf8) = 0;
  for (local_18 = 0; local_18 < sVar1; local_18 = local_18 + 1) {
    sVar2 = *(short *)(in_ECX + 0x2b78 + local_18 * 0xc);
    iVar3 = *(int *)(in_ECX + 0x2b7c + local_18 * 0xc);
    puVar4 = *(undefined4 **)(in_ECX + 0x2b80 + local_18 * 0xc);
    switch(sVar2) {
    case 0:
      break;
    case 1:
      local_8 = (undefined2)iVar3;
      thunk_FUN_0046c640(CONCAT22(sVar2 >> 0xf,local_8),puVar4 != (undefined4 *)0x0);
      thunk_FUN_00414ad0(s_SetState_to__d___d__004a5658,iVar3,puVar4);
      break;
    case 2:
      *(undefined4 *)(in_ECX + 0x62b8) = 1;
      break;
    case 3:
      thunk_FUN_0046c7b5();
      break;
    case 4:
      if (iVar3 == 1) {
        uVar5 = thunk_FUN_0042dd0f(0);
        thunk_FUN_0042d3fb(uVar5);
      }
      else {
        uVar6 = thunk_FUN_0042d28f();
        *puVar4 = uVar6;
        uVar5 = thunk_FUN_0042dd0f(0);
        thunk_FUN_00406604(puVar4,uVar5);
        thunk_FUN_0042d38a();
        thunk_FUN_0042d87c(puVar4,3);
      }
      thunk_FUN_0046c25d(0xb,iVar3,puVar4,0);
      break;
    case 5:
      thunk_FUN_004140dd(0xc,0,0,0);
      break;
    default:
      thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5674,0x400,s_FALSE_004a566c);
    }
  }
  return;
}
```

---


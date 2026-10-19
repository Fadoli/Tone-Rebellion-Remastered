# 0018_batch_0014 — détails (2/3)

## FUN_0046c371 — 0x46c371

- Classification : internal
- Corps : `0x46c371–0x46c3bb`
- État : pseudocode obtenu
- Evidence : `ev_f8a09cad809f94f6483fa8f6623537024026f2d86fdd3f36b90ed39dbda0bd65`
- Note de dispatch : relaie le message au gestionnaire de l'entrée ciblée avec l'index d'état actif; l'appel est indirect. Evidence `ev_ed92b375145a0b030776f82d115ccc237230777746be74169b6aac305580d646`.
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0046c371(int param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int in_ECX;
  
  if (*(short *)(in_ECX + 0x29f2) < 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = (**(code **)(**(int **)(in_ECX + 4 + param_1 * 0xc) + 4))
                      (CONCAT22(*(short *)(in_ECX + 0x29f2) >> 0xf,param_2),param_3,param_4);
  }
  return uVar1;
}
```

---

---

## FUN_0046c3bc — 0x46c3bc

- Classification : internal
- Corps : `0x46c3bc–0x46c401`
- État : pseudocode obtenu
- Evidence : `ev_20f78af3bd6f098a74bb77593497f5a3ac4d89f2ad5db1bd6996b2a8132ae17e`
- Note de routage : trouve l'entrée puis délègue à `FUN_0046c371`, chemin file locale utilisé par le mode 2 de `FUN_0042970c`. Evidence `ev_9b2f8d28b701a828ee0fa8c8a2a7b9ed1ac5edc678f92d8c58589e8d2a034487`.
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x401e65` — `thunk_FUN_0046c4a5`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
bool FUN_0046c3bc(undefined4 param_1,undefined2 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined2 extraout_var;
  short local_8 [2];
  
  iVar1 = thunk_FUN_0046c4a5(param_1,local_8);
  if (iVar1 != 0) {
    thunk_FUN_0046c371((int)local_8[0],CONCAT22(extraout_var,param_2),param_3,param_4);
  }
  return iVar1 != 0;
}
```

---

---

## FUN_0046c402 — 0x46c402

- Classification : internal
- Corps : `0x46c402–0x46c457`
- État : pseudocode obtenu
- Evidence : `ev_22c10c003d5e67aa0a7ff7f87ab42ccd18271479b131778c6669c28fe2a70441`
- Note de dispatch : appelle par pointeur le callback du slot actif `+0x29f2` dans la table à pas `0x130`; la cible dépend donc de l'état courant. Evidence `ev_94eb91d39af9704767219d6df99b523c4408544d37cebde8472793c068780572`.
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046c402(undefined2 param_1,undefined4 param_2,undefined4 param_3)

{
  int in_ECX;
  
  if (*(int *)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130) != 0) {
    (**(code **)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130))(param_1,param_2,param_3,0);
  }
  return;
}
```

---

---

## FUN_0046c458 — 0x46c458

- Classification : internal
- Corps : `0x46c458–0x46c4a4`
- État : pseudocode obtenu
- Evidence : `ev_cdb7d6623c31f8f85d780b9ce25caa8e64c69d8ba0467ee8f39e7919f445b022`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0046c458(short param_1)

{
  int iVar1;
  int in_ECX;
  
  if (((param_1 < 1) || (*(short *)(in_ECX + 0x1f38) <= param_1)) ||
     (*(int *)(in_ECX + 4 + param_1 * 0xc) == 0)) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(in_ECX + 4 + param_1 * 0xc) + 0x20;
  }
  return iVar1;
}
```

---

---

## FUN_0046c4a5 — 0x46c4a5

- Classification : internal
- Corps : `0x46c4a5–0x46c557`
- État : pseudocode obtenu
- Evidence : `ev_8ca518262f6e9da0f51b7f516b986760a38b2cc4962b4ea5adf47c2f5b350e01`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x48b100` — `__strcmpi`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0046c4a5(char *param_1,short *param_2)

{
  int iVar1;
  int in_ECX;
  short local_10;
  short local_c;
  
  local_c = 0;
  local_10 = 0;
  while ((local_10 < 0x29a && (local_c <= *(short *)(in_ECX + 0x1f38)))) {
    if (*(int *)(in_ECX + 4 + local_10 * 0xc) != 0) {
      local_c = local_c + 1;
      iVar1 = __strcmpi(param_1,(char *)(*(int *)(in_ECX + 4 + local_10 * 0xc) + 0x20));
      if (iVar1 == 0) {
        if (param_2 != (short *)0x0) {
          *param_2 = local_10;
        }
        return *(undefined4 *)(in_ECX + 4 + local_10 * 0xc);
      }
    }
    local_10 = local_10 + 1;
  }
  return 0;
}
```

---

---

## FUN_0046c558 — 0x46c558

- Classification : internal
- Corps : `0x46c558–0x46c63f`
- État : pseudocode obtenu
- Evidence : `ev_3f74e51a066a3e957a7f5ced1f5626946553adb5e036fb426687a91a81e7f2db`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x48b100` — `__strcmpi`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0046c558(char *param_1,short param_2,undefined2 *param_3)

{
  int iVar1;
  int iVar2;
  int in_ECX;
  undefined2 local_14;
  short local_10;
  
  if (param_2 < *(short *)(in_ECX + 0x29f0)) {
    for (local_10 = 0; local_10 < *(short *)(in_ECX + 8000 + param_2 * 0x130);
        local_10 = local_10 + 1) {
      iVar1 = *(int *)(in_ECX + param_2 * 0x130 + 0x1f44 + local_10 * 4);
      if ((*(int *)(in_ECX + 4 + iVar1 * 0xc) != 0) &&
         (iVar2 = __strcmpi(param_1,(char *)(*(int *)(in_ECX + 4 + iVar1 * 0xc) + 0x20)), iVar2 == 0
         )) {
        if (param_3 != (undefined2 *)0x0) {
          local_14 = (undefined2)iVar1;
          *param_3 = local_14;
        }
        return *(undefined4 *)(in_ECX + 4 + iVar1 * 0xc);
      }
    }
  }
  return 0;
}
```

---

---

## FUN_0046c640 — 0x46c640

- Classification : internal
- Corps : `0x46c640–0x46c7b4`
- État : pseudocode obtenu
- Evidence : `ev_2399ce70bd485f8fca1018b94b277bcc7bed501a0e6846ae18403de594810554`
- Note d'état : écrit l'index actif `+0x29f2` à partir de son paramètre avant le dispatch; la file peut restaurer un état antérieur. Aucun lien ne fixe l'état actif à 3 au clic `0x32`. Evidence `ev_e485a0839f32ca445383d2eab74cff5f5c3744ea6dbfc9bfc1b3c00a0edaa26a`.
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40119f` — `thunk_FUN_0046c371`
- `0x401e83` — `thunk_FUN_0046be81`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x40227f` — `thunk_FUN_0046c25d`
- `0x4022bb` — `thunk_FUN_0042d3fb`
- `0x402491` — `thunk_FUN_0042dd0f`

### Chaînes référencées

- `0x4a57ac` — "state>=0 && state < MAX_GAME_STATES"
- `0x4a57d0` — "C:\\float\\src\\winman.cpp"

### Pseudocode Ghidra

```c
void FUN_0046c640(short param_1)

{
  undefined1 uVar1;
  int in_ECX;
  undefined4 uVar2;
  
  if (*(short *)(in_ECX + 0x29f2) != param_1) {
    if ((param_1 < 0) || (8 < param_1)) {
      uVar2 = thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a57d0,0x676,
                                 s_state>_0____state_<_MAX_GAME_STA_004a57ac);
    }
    else {
      uVar2 = 0;
    }
    if ((-1 < *(short *)(in_ECX + 0x29f2)) &&
       (*(int *)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130) != 0)) {
      (**(code **)(in_ECX + 0x206c + *(short *)(in_ECX + 0x29f2) * 0x130))(2,0,0,0,uVar2);
    }
    if (*(int *)(in_ECX + 0x1f3c) != -1) {
      thunk_FUN_0046c371(*(undefined4 *)(in_ECX + 0x1f3c),8,0,0);
    }
    thunk_FUN_0046c25d(2,0,0,0);
    *(undefined2 *)(in_ECX + 0x29f4) = *(undefined2 *)(in_ECX + 0x29f2);
    *(short *)(in_ECX + 0x29f2) = param_1;
    uVar1 = thunk_FUN_0042dd0f(0);
    thunk_FUN_0042d3fb(uVar1);
    if (*(int *)(in_ECX + 0x206c + param_1 * 0x130) == 0) {
      thunk_FUN_0046c25d(1,0,0,0);
    }
    else {
      (**(code **)(in_ECX + 0x206c + param_1 * 0x130))(1,9,9,9);
    }
    *(undefined4 *)(in_ECX + 0x1f3c) = 0xffffffff;
    thunk_FUN_0046be81();
  }
  return;
}
```

---

---

## FUN_0046c7b5 — 0x46c7b5

- Classification : internal
- Corps : `0x46c7b5–0x46c7de`
- État : pseudocode obtenu
- Evidence : `ev_e7876c37ea384bb3ce6d3bea8c382ed1468d2fc9bb8d17993a164cd109fdb4ab`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f82` — `thunk_FUN_0046c640`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined2 FUN_0046c7b5(void)

{
  int in_ECX;
  
  thunk_FUN_0046c640(*(undefined2 *)(in_ECX + 0x29f4),1);
  return *(undefined2 *)(in_ECX + 0x29f2);
}
```

---

---

## FUN_0046c7df — 0x46c7df

- Classification : internal
- Corps : `0x46c7df–0x46c896`
- État : pseudocode obtenu
- Evidence : `ev_23b18626e4cee1252969d692217a9faefe5e26a632c35ef49faace72896995e4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a57ec` — "C:\\float\\src\\winman.cpp"

### Pseudocode Ghidra

```c
int FUN_0046c7df(int param_1)

{
  int in_ECX;
  short local_8;
  
  if ((param_1 != 0) && (*(short *)(in_ECX + 0x1f38) != 0x299)) {
    for (local_8 = 1; local_8 < 0x29a; local_8 = local_8 + 1) {
      if (*(int *)(in_ECX + local_8 * 0xc) == 0) {
        *(undefined4 *)(in_ECX + local_8 * 0xc) = 1;
        *(int *)(in_ECX + 4 + local_8 * 0xc) = param_1;
        *(short *)(in_ECX + 0x1f38) = *(short *)(in_ECX + 0x1f38) + 1;
        return (int)local_8;
      }
    }
    thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a57ec,0x6c1,&DAT_004a57e8);
  }
  return 0;
}
```

---

---

## FUN_0046c897 — 0x46c897

- Classification : internal
- Corps : `0x46c897–0x46ca72`
- État : pseudocode obtenu
- Evidence : `ev_62edd40c85bd89a020159fba8772f22e1848df946626a64d236485f750fdf1d8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a5804` — "state>=0 && state<MAX_GAME_STATES"
- `0x4a5828` — "C:\\float\\src\\winman.cpp"
- `0x4a5840` — "hwnd < MAX_WINDOWS"
- `0x4a5854` — "C:\\float\\src\\winman.cpp"
- `0x4a586c` — "i<MAX_STATE_WINDOWS"
- `0x4a5880` — "C:\\float\\src\\winman.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0046c897(int param_1,short param_2)

{
  undefined4 uVar1;
  int in_ECX;
  short local_8;
  
  if ((param_2 < 0) || (8 < param_2)) {
    thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5828,0x6cc,
                       s_state>_0____state<MAX_GAME_STATE_004a5804);
  }
  if (0x299 < param_1) {
    thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5854,0x6cd,s_hwnd_<_MAX_WINDOWS_004a5840);
  }
  if ((param_1 == 0) || (*(short *)(in_ECX + 8000 + param_2 * 0x130) == 0x4a)) {
    uVar1 = 0;
  }
  else {
    local_8 = 0;
    if (*(short *)(in_ECX + 8000 + param_2 * 0x130) == 0) {
      *(short *)(in_ECX + 0x29f0) = *(short *)(in_ECX + 0x29f0) + 1;
      *(int *)(in_ECX + 0x1f44 + param_2 * 0x130) = param_1;
      *(undefined2 *)(in_ECX + 8000 + param_2 * 0x130) = 1;
    }
    else {
      for (local_8 = 0; local_8 < 0x4a; local_8 = local_8 + 1) {
        if (*(int *)(in_ECX + param_2 * 0x130 + 0x1f44 + local_8 * 4) == 0) {
          *(int *)(in_ECX + param_2 * 0x130 + 0x1f44 + local_8 * 4) = param_1;
          *(short *)(in_ECX + 8000 + param_2 * 0x130) =
               *(short *)(in_ECX + 8000 + param_2 * 0x130) + 1;
          break;
        }
      }
    }
    *(int *)(in_ECX + param_1 * 0xc) = *(int *)(in_ECX + param_1 * 0xc) + 1;
    if (0x49 < local_8) {
      thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5880,0x6ef,s_i<MAX_STATE_WINDOWS_004a586c);
    }
    uVar1 = 1;
  }
  return uVar1;
}
```

---

---

## FUN_0046ca73 — 0x46ca73

- Classification : internal
- Corps : `0x46ca73–0x46cbdf`
- État : pseudocode obtenu
- Evidence : `ev_fa69ef67ca1ef12f3cc15417d3ab69684ee21b559f099ae579637033e247da61`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4016b8` — `thunk_FUN_0046cc04`
- `0x401f64` — `thunk_FUN_00414b64`

### Chaînes référencées

- `0x4a5898` — "state>=0 && state<MAX_GAME_STATES"
- `0x4a58bc` — "C:\\float\\src\\winman.cpp"
- `0x4a58d4` — "hwnd < MAX_WINDOWS"
- `0x4a58e8` — "C:\\float\\src\\winman.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0046ca73(int param_1,short param_2,int param_3)

{
  undefined4 uVar1;
  int in_ECX;
  short local_8;
  
  if ((param_2 < 0) || (8 < param_2)) {
    thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a58bc,0x6ff,
                       s_state>_0____state<MAX_GAME_STATE_004a5898);
  }
  if (0x299 < param_1) {
    thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a58e8,0x700,s_hwnd_<_MAX_WINDOWS_004a58d4);
  }
  if ((param_1 == 0) || (*(short *)(in_ECX + 8000 + param_2 * 0x130) == 0)) {
    uVar1 = 0;
  }
  else {
    for (local_8 = 0; local_8 < 0x4a; local_8 = local_8 + 1) {
      if (*(int *)(in_ECX + param_2 * 0x130 + 0x1f44 + local_8 * 4) == param_1) {
        *(undefined4 *)(in_ECX + param_2 * 0x130 + 0x1f44 + local_8 * 4) = 0;
        *(short *)(in_ECX + 8000 + param_2 * 0x130) =
             *(short *)(in_ECX + 8000 + param_2 * 0x130) + -1;
        *(int *)(in_ECX + param_1 * 0xc) = *(int *)(in_ECX + param_1 * 0xc) + -1;
        if (param_3 != 0) {
          thunk_FUN_0046cc04(param_1,0);
        }
        break;
      }
    }
    if (local_8 < 0x4a) {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}
```

---

# 0017_batch_0013 — détails (3/3)

## FUN_00460460 — 0x460460

- Classification : internal
- Corps : `0x460460–0x460988`
- État : pseudocode obtenu
- Evidence : `ev_67e9f6f06b6bb555f4b8a61a0b1d4b1d8fd8ae6c5a090b47499f0c439d80e029`
- Note de portée : cette fonction scanne les enregistrements d'emplacements d'une île (stride `0x60`) et leurs champs propriétaire/type. Elle maintient des compteurs insulaires de type 4, compte les floaters Leviathan autres que le sous-type 9, puis écrit l'intervalle `+0x45a` dans les enregistrements de sites sélectionnés. `+0x45a` appartient ici à l'enregistrement d'emplacement, pas au floater. Elle est appelée après des changements Leviathan et par un recalcul global ; le lecteur du temporisateur et le processus complet de production ne sont pas établis. Evidence de la relecture `ev_f6fad36a24d0df23600189218f8f97cf25c8ae1078856cf1f0526c0fd092aedd`.
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401131` — `thunk_FUN_00412cac`
- `0x40186b` — `thunk_FUN_004656d6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00460460(int param_1)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int in_ECX;
  short local_4c;
  short local_44;
  undefined2 local_40;
  int local_3c;
  undefined1 *local_38;
  short local_34;
  int local_2c;
  short asStack_28 [6];
  int local_1c;
  short local_18;
  int local_14;
  undefined1 *local_10;
  int local_c;
  uint local_8;
  
  local_14 = param_1;
  local_8 = param_1 + 1;
  if (param_1 == -1) {
    local_14 = 0;
    local_8 = (uint)DAT_006136b0;
  }
  local_10 = &DAT_005ec218 + local_14 * 0x29e8;
  local_c = local_14;
  do {
    if ((int)local_8 <= local_c) {
      return;
    }
    local_4c = 0;
    local_34 = 0;
    *(undefined2 *)(in_ECX + 0x15d8 + local_c * 2) = 0;
    local_2c = 1;
    bVar2 = false;
    local_38 = local_10 + 0x428;
    for (local_3c = 0; local_3c < *(short *)(local_10 + 0x29a8); local_3c = local_3c + 1) {
      if ((*(int *)(local_38 + 4) == 1) && (local_4c < 6)) {
        local_4c = local_4c + 1;
        if (*(int *)(local_38 + 0x14) == 4) {
          asStack_28[*(short *)(in_ECX + 0x15d8 + local_c * 2)] = (short)local_3c;
          *(short *)(in_ECX + 0x15d8 + local_c * 2) = *(short *)(in_ECX + 0x15d8 + local_c * 2) + 1;
        }
      }
      else if ((*(int *)(local_38 + 4) == 0) && (*(int *)(local_38 + 0x14) == 4)) {
        local_34 = local_34 + 1;
      }
      else if ((*(int *)(local_38 + 0x14) == -1) ||
              (((*(int *)(local_38 + 0x10) != 0x2a ||
                (iVar3 = thunk_FUN_00412cac(*(undefined4 *)(local_38 + 0x14)), iVar3 == -1)) &&
               ((*(int *)(local_38 + 0x10) < 0x2c || (0x2e < *(int *)(local_38 + 0x10))))))) {
        if ((((*(int *)(local_38 + 0x14) != -1) && (0x24 < *(int *)(local_38 + 0x10))) &&
            (*(int *)(local_38 + 0x10) < 0x36)) &&
           (iVar3 = thunk_FUN_00412cac(*(undefined4 *)(local_38 + 0x14)), iVar3 != -1)) {
          local_2c = 0;
        }
      }
      else {
        local_2c = 0;
        bVar2 = true;
      }
      local_38 = local_38 + 0x60;
    }
    if ((DAT_006191b4 == 0) && (local_c == DAT_006136b0 - 1)) {
      bVar1 = false;
      for (local_3c = 0; local_3c < *(short *)(local_10 + 0x29a8); local_3c = local_3c + 1) {
        if ((0x16 < *(int *)(local_10 + local_3c * 0x60 + 0x438)) &&
           (*(int *)(local_10 + local_3c * 0x60 + 0x438) < 0x25)) {
          bVar1 = true;
          break;
        }
      }
      if (!bVar1) {
        DAT_006191b4 = 2;
      }
    }
    if ((*(int *)(in_ECX + 0x14e8 + local_c * 4) != 0) && (local_2c == 0)) {
      *(undefined4 *)(in_ECX + 0x1524 + local_c * 4) = 0xffffffff;
    }
    *(int *)(in_ECX + 0x14e8 + local_c * 4) = local_2c;
    if (*(short *)(in_ECX + 0x15d8 + local_c * 2) != 0) {
      *(short *)(in_ECX + 0x159c + local_c * 2) =
           local_4c - *(short *)(in_ECX + 0x15d8 + local_c * 2);
      local_44 = (short)((int)(local_c + (local_c >> 0x1f & 3U)) >> 2);
      if (DAT_00618e48 < local_44) {
        local_44 = (short)DAT_00618e48;
      }
      *(short *)(in_ECX + 0x157e + local_c * 2) =
           *(short *)(in_ECX + 0x15d8 + local_c * 2) * (local_44 * 2 + 4) - local_34;
      if (*(short *)(in_ECX + 0x157e + local_c * 2) < 0) {
        *(undefined2 *)(in_ECX + 0x157e + local_c * 2) = 0;
      }
      *(undefined2 *)(in_ECX + 0x15ba + local_c * 2) = 0;
      local_1c = thunk_FUN_004656d6(local_c,0xfffffffe);
      for (local_3c = 0; local_3c < local_1c; local_3c = local_3c + 1) {
        if (((&DAT_006137b8)[(short)(&DAT_00618fb4)[local_3c] * 0x13] == 4) &&
           (*(int *)(&DAT_006137bc + (short)(&DAT_00618fb4)[local_3c] * 0x4c) != 9)) {
          *(short *)(in_ECX + 0x15ba + local_c * 2) = *(short *)(in_ECX + 0x15ba + local_c * 2) + 1;
        }
      }
      iVar3 = *(short *)(in_ECX + 0x15d8 + local_c * 2) + -1;
      if (*(int *)(in_ECX + 0x14e8 + local_c * 4) == 0) {
        if (bVar2) {
          local_18 = *(short *)(&DAT_004a4508 + iVar3 * 2 + DAT_00618e48 * 0xc);
        }
        else {
          local_18 = *(short *)(&DAT_004a44c8 + iVar3 * 2 + DAT_00618e48 * 0xc);
        }
      }
      else {
        local_18 = *(short *)(&DAT_004a4488 + iVar3 * 2 + DAT_00618e48 * 0xc);
      }
      *(short *)(in_ECX + 0x1560 + local_c * 2) =
           local_18 - *(short *)(in_ECX + 0x15ba + local_c * 2);
      local_40 = (undefined2)
                 (((local_44 + DAT_00618e48) * 2 + 10) /
                 (int)*(short *)(in_ECX + 0x15d8 + local_c * 2));
      if (((*(short *)(in_ECX + 0x159c + local_c * 2) == 0) &&
          (*(short *)(in_ECX + 0x157e + local_c * 2) == 0)) &&
         (*(short *)(in_ECX + 0x1560 + local_c * 2) == 0)) {
        local_40 = 0;
      }
      for (local_3c = 0; local_3c < *(short *)(in_ECX + 0x15d8 + local_c * 2);
          local_3c = local_3c + 1) {
        iVar3 = asStack_28[local_3c] * 0x60;
        if (*(int *)(local_10 + iVar3 + 0x438) == 5) {
          *(undefined2 *)(local_10 + iVar3 + 0x45a) = 1;
        }
        else {
          *(undefined2 *)(local_10 + iVar3 + 0x45a) = local_40;
        }
      }
    }
    local_c = local_c + 1;
    local_10 = local_10 + 0x29e8;
  } while( true );
}
```

---

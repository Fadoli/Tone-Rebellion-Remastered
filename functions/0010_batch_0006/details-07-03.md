# 0010_batch_0006 — détails (3/3)

## FUN_00422d27 — 0x422d27

- Classification : internal
- Corps : `0x422d27–0x423067`
- État : pseudocode obtenu
- Evidence : `ev_810f7530a91d83a454c4d310d2142cafe948434cde2b0707fd5847693435b64f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401401` — `thunk_FUN_0041e427`
- `0x40173a` — `thunk_FUN_004672a6`
- `0x40180c` — `thunk_FUN_00420600`
- `0x401933` — `thunk_FUN_00464242`
- `0x401dac` — `thunk_FUN_004207f2`
- `0x4023bf` — `thunk_FUN_0045c3bb`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00422d27(void)

{
  ushort uVar1;
  int iVar2;
  int *in_ECX;
  undefined4 local_44;
  short local_30 [2];
  short local_2c [2];
  undefined4 *local_28;
  int local_24;
  uint local_20;
  int local_1c;
  ushort local_18;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = (int)(short)in_ECX[10];
  local_10 = (int)*(short *)((int)in_ECX + 0x2a);
  local_20 = 0;
  if (in_ECX[0xb] == 8) {
    iVar2 = *(short *)((int)in_ECX + 0x32) * 0x4c;
    local_28 = &DAT_006137b8 + *(short *)((int)in_ECX + 0x32) * 0x13;
    local_c = local_c + *(short *)(&DAT_006137c8 + iVar2);
    local_10 = local_10 + *(short *)(&DAT_006137ca + iVar2);
    if (local_c < 0) {
      local_c = 0;
    }
    if (0x9ff < local_c) {
      local_c = 0x9ff;
    }
    if (local_10 < 0x28) {
      local_10 = 0x28;
    }
    if (0x122 < local_10) {
      local_10 = 0x122;
    }
    iVar2 = thunk_FUN_00420600(local_28);
    local_20 = (uint)(iVar2 < 100);
    if (local_c < (short)in_ECX[4]) {
      in_ECX[7] = in_ECX[7] | 2;
    }
    else {
      in_ECX[7] = in_ECX[7] & 0xfffffffd;
    }
  }
  else if (in_ECX[0xb] == 9) {
    thunk_FUN_0041e427(CONCAT22((short)((uint)local_30 >> 0x10),*(undefined2 *)((int)in_ECX + 0x32))
                       ,local_2c,local_30);
    iVar2 = thunk_FUN_004672a6((int)(short)in_ECX[4],(int)*(short *)((int)in_ECX + 0x12),
                               (int)local_2c[0],(int)local_30[0]);
    local_20 = (uint)(iVar2 < 100);
  }
  else if (in_ECX[0xb] == 0xe) {
    local_20 = 1;
  }
  if (local_20 == 0) {
    iVar2 = thunk_FUN_00464242(*in_ECX,in_ECX[1]);
    local_18 = *(ushort *)(iVar2 + 0xc);
  }
  else {
    local_18 = 1;
  }
  if ((in_ECX[1] == 0) && (0 < *(short *)(&DAT_00618f5a + *in_ECX * 2))) {
    local_18 = local_18 << 1;
  }
  local_8 = thunk_FUN_004207f2();
  if (local_8 != 0) {
    iVar2 = thunk_FUN_0045c3bb();
    uVar1 = *(ushort *)(&DAT_00619242 + *in_ECX * 0x14a0);
    if (((uVar1 & 8) == 0) || (*(int *)(iVar2 + 0x10) != 0x2c)) {
      if (((uVar1 & 0x20) == 0) || (*(int *)(iVar2 + 0x10) != 0x2d)) {
        if (((uVar1 & 0x200) != 0) && (*(int *)(iVar2 + 0x10) == 0x2e)) {
          local_18 = local_18 + 1;
        }
      }
      else {
        local_18 = local_18 + 1;
      }
    }
    else {
      local_18 = local_18 + 1;
    }
  }
  iVar2 = thunk_FUN_004672a6((int)(short)in_ECX[4],(int)*(short *)((int)in_ECX + 0x12),local_c,
                             local_10);
  if ((iVar2 < (short)local_18 * 4) &&
     (local_18 = (ushort)((int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2), (short)local_18 < 1)) {
    local_18 = (ushort)DAT_00618e44 & 1;
  }
  local_1c = local_c - (short)in_ECX[4];
  local_24 = local_10 - *(short *)((int)in_ECX + 0x12);
  if (local_1c < -(int)(short)local_18) {
    local_1c = -(int)(short)local_18;
  }
  if ((short)local_18 < local_1c) {
    local_1c = (int)(short)local_18;
  }
  *(short *)(in_ECX + 4) = (short)in_ECX[4] + (short)local_1c;
  if (local_24 < -(int)(short)local_18) {
    local_24 = -(int)(short)local_18;
  }
  if ((short)local_18 < local_24) {
    local_24 = (int)(short)local_18;
  }
  *(short *)((int)in_ECX + 0x12) = *(short *)((int)in_ECX + 0x12) + (short)local_24;
  if (((short)in_ECX[4] == local_c) && (*(short *)((int)in_ECX + 0x12) == local_10)) {
    local_44 = 1;
  }
  else {
    local_44 = 0;
  }
  return local_44;
}
```

---

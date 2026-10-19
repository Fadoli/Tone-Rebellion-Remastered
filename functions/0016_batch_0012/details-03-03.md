# 0016_batch_0012 — détails (3/3)

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

# 0008_batch_0004 — détails (3/3)

## FUN_004120e0 — 0x4120e0

- Classification : internal
- Corps : `0x4120e0–0x4120f5`
- État : pseudocode obtenu
- Evidence : `ev_20707eacd8e7ae1bfb76c22d3713e36baa01e13901f80ef6ee36968239047c58`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401ea1` — `thunk_FUN_004120f6`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_004120e0(void)

{
  undefined4 in_ECX;
  
  thunk_FUN_004120f6();
  return in_ECX;
}
```

# entry — 0x478460

- Classification : `runtime`
- Corps : `0x478460–0x478643`, `0x478675–0x478685`
- État : pseudocode obtenu
- Evidence : `ev_4ea4348ef088ca577694ef3daa25d523ab017af07ee682c3223e064798ca5191`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

## Observations Ghidra

Appels directs observés :
- `EXTERNAL:0x3f` — `KERNEL32.DLL::GetStartupInfoA` (externe)
- `EXTERNAL:0x40` — `KERNEL32.DLL::GetModuleHandleA` (externe)
- `EXTERNAL:0x49` — `KERNEL32.DLL::GetCommandLineA` (externe)
- `EXTERNAL:0x4a` — `KERNEL32.DLL::GetVersion` (externe)
- `0x402149` — `thunk_FUN_0041d8e1` (thunk)
- `0x476e60` — `FUN_00476e60` (interne)
- `0x476ea0` — `FUN_00476ea0` (interne)
- `0x478690` — `__amsg_exit` (interne)
- `0x47cf40` — `FUN_0047cf40` (interne)
- `0x47e2f0` — `FUN_0047e2f0` (interne)
- `0x480eb0` — `FUN_00480eb0` (interne)
- `0x480fa0` — `FUN_00480fa0` (interne)
- `0x4810e0` — `FUN_004810e0` (interne)
- `0x481860` — `FUN_00481860` (interne)
- `0x481ec0` — `FUN_00481ec0` (interne)

Chaînes référencées observées :
- Aucune chaîne définie référencée observée.

## Interprétation

Cette fonction ressemble à l’amorçage du runtime C : elle prépare l’environnement de processus, récupère les informations de démarrage et appelle une thunk qui pointe sur `0x41d8e1`. Ce classement est une interprétation du pseudocode et des appels observés.

## Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  DWORD DVar1;
  int iVar2;
  HMODULE pHVar3;
  byte *pbVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar5;
  uint local_70;
  byte *local_68;
  _STARTUPINFOA local_60;
  undefined1 *local_1c;
  undefined4 local_14;
  undefined1 *puStack_10;
  undefined *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &DAT_004959e0;
  puStack_10 = &LAB_00480ac8;
  local_14 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_14;
  local_1c = &stack0xffffff84;
  DVar1 = GetVersion();
  _DAT_00632534 = DVar1 >> 8 & 0xff;
  DAT_00632530 = DVar1 & 0xff;
  _DAT_0063252c = DAT_00632530 * 0x100 + _DAT_00632534;
  DAT_00632528 = DVar1 >> 0x10;
  iVar2 = FUN_0047e2f0();
  if (iVar2 == 0) {
    __amsg_exit(0x1c);
  }
  local_8 = 0;
  FUN_0047cf40();
  FUN_00481ec0();
  DAT_00633e6c = (byte *)GetCommandLineA();
  DAT_00632570 = FUN_00481860();
  if ((DAT_00632570 == 0) || (DAT_00633e6c == (byte *)0x0)) {
    FUN_00476ea0(0xffffffff);
  }
  FUN_004810e0();
  FUN_00480fa0();
  FUN_00476e60();
  local_68 = DAT_00633e6c;
  pbVar4 = local_68;
  if (*DAT_00633e6c == 0x22) {
    while ((local_68 = pbVar4, pbVar4 = local_68 + 1, *pbVar4 != 0x22 && (*pbVar4 != 0))) {
      iVar2 = FUN_00480eb0(*pbVar4);
      if (iVar2 != 0) {
        pbVar4 = local_68 + 2;
      }
    }
    if (*pbVar4 == 0x22) {
      pbVar4 = local_68 + 2;
    }
  }
  else {
    for (; pbVar4 = local_68, 0x20 < *local_68; local_68 = local_68 + 1) {
    }
  }
  while ((local_68 = pbVar4, *local_68 != 0 && (*local_68 < 0x21))) {
    pbVar4 = local_68 + 1;
  }
  local_60.dwFlags = 0;
  GetStartupInfoA(&local_60);
  if ((local_60.dwFlags & 1) == 0) {
    local_70 = 10;
  }
  else {
    local_70 = local_60._48_4_ & 0xffff;
  }
  uVar5 = 0;
  pHVar3 = GetModuleHandleA((LPCSTR)0x0);
  uVar5 = thunk_FUN_0041d8e1(pHVar3,uVar5,local_68,local_70);
  FUN_00476ea0(uVar5);
  *unaff_FS_OFFSET = local_14;
  return;
}
```

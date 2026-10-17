# FUN_0041d8e1 — 0x41d8e1

- Classification : `internal`
- Corps : `0x41d8e1–0x41db0d`
- État : pseudocode obtenu
- Evidence : `ev_4447fdd9631929efaeb1d177248260afbbd55aec3775ce0996e1f9b427cb4e7f`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

## Observations Ghidra

Appels directs observés :
- `EXTERNAL:0x55` — `USER32.DLL::MessageBoxA` (externe)
- `EXTERNAL:0x6c` — `USER32.DLL::SendMessageA` (externe)
- `0x4010b9` — `thunk_FUN_00429ebe` (thunk)
- `0x401177` — `thunk_FUN_0041d64e` (thunk)
- `0x4011c2` — `thunk_FUN_0041c039` (thunk)
- `0x4013c5` — `thunk_FUN_0041c46f` (thunk)
- `0x4014a6` — `thunk_FUN_0040f6f7` (thunk)
- `0x40167c` — `thunk_FUN_0041d70d` (thunk)
- `0x401825` — `thunk_FUN_0040f73f` (thunk)
- `0x401942` — `thunk_FUN_00429c4b` (thunk)
- `0x401c4e` — `thunk_FUN_00414de5` (thunk)
- `0x401e29` — `thunk_FUN_0041c1d6` (thunk)
- `0x401eba` — `thunk_FUN_0040f752` (thunk)
- `0x402298` — `thunk_FUN_00414ad0` (thunk)
- `0x402356` — `thunk_FUN_0041d19d` (thunk)
- `0x472ca0` — `FUN_00472ca0` (interne)
- `0x472e90` — `_strlen` (interne)

Chaînes référencées observées :
- `0x49cde0` — `1.16F`
- `0x49cde8` — `Entering main: %s`
- `0x49cdfc` — `Command line (%d): %s`
- `0x49ce14` — `gamey.txt`
- `0x49ce20` — `newtext.txt`
- `0x49ce2c` — `bldtxt.txt`
- `0x49ce38` — `bldname.txt`
- `0x49ce44` — `plotobj.txt`
- `0x49ce50` — `tonehelp.txt`
- `0x49ce60` — `names.txt`
- `0x49ce6c` — `%s\thing1\float.exe`
- `0x49ce80` — `INSERTCD`
- `0x49ce8c` — `Tonus Rebellious`
- `0x49cea0` — `Exiting main: %x`

## Interprétation

Fonction de démarrage applicatif candidate : le pseudocode journalise `1.16F`, ouvre les fichiers listés et appelle les chemins d’initialisation fenêtre et boucle principale.

## Pseudocode Ghidra

```c
undefined4 FUN_0041d8e1(undefined4 param_1,undefined4 param_2,char *param_3,undefined4 param_4)

{
  size_t sVar1;
  int iVar2;
  LPCSTR lpText;
  undefined4 *unaff_FS_OFFSET;
  char *pcVar3;
  undefined1 local_144 [300];
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491594;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_00414ad0(s_Entering_main___s_0049cde8,s_1_16F_0049cde0);
  pcVar3 = param_3;
  sVar1 = _strlen(param_3);
  thunk_FUN_00414ad0(s_Command_line___d____s_0049cdfc,sVar1,pcVar3);
  thunk_FUN_00414de5();
  thunk_FUN_0041d19d(param_3);
  thunk_FUN_0041d64e();
  thunk_FUN_00429c4b(s_gamey_txt_0049ce14);
  thunk_FUN_00429c4b(s_newtext_txt_0049ce20);
  thunk_FUN_00429c4b(s_bldtxt_txt_0049ce2c);
  thunk_FUN_00429c4b(s_bldname_txt_0049ce38);
  thunk_FUN_00429c4b(s_plotobj_txt_0049ce44);
  thunk_FUN_00429c4b(s_tonehelp_txt_0049ce50);
  thunk_FUN_0041d70d(s_names_txt_0049ce60);
  if ((DAT_004c2b80 != 0) && (DAT_004c2ba4 == 0)) {
    local_18 = 0;
    do {
      FUN_00472ca0(local_144,s__s_thing1_float_exe_0049ce6c,&DAT_004c2aa8);
      thunk_FUN_0040f6f7();
      local_8 = 0;
      iVar2 = thunk_FUN_0040f752(local_144,0x8000);
      if (iVar2 == 0) {
        local_18 = 1;
      }
      else {
        lpText = (LPCSTR)thunk_FUN_00429ebe(s_INSERTCD_0049ce80,0);
        iVar2 = MessageBoxA((HWND)0x0,lpText,s_Tonus_Rebellious_0049ce8c,5);
        if (iVar2 == 2) {
          local_8 = 0xffffffff;
          thunk_FUN_0040f73f();
          local_14 = 0xffffffff;
          goto LAB_0041dafe;
        }
      }
      local_8 = 0xffffffff;
      thunk_FUN_0040f73f();
    } while (local_18 == 0);
  }
  if (DAT_004c2b90 != 0) {
    thunk_FUN_0041c039();
  }
  iVar2 = thunk_FUN_0041c1d6(param_1,param_3,param_4);
  if (iVar2 == 0) {
    local_14 = 0;
  }
  else {
    local_14 = thunk_FUN_0041c46f();
    if (DAT_004c2b68 != 0) {
      SendMessageA(DAT_004c2b58,2,0,0);
    }
    thunk_FUN_00414de5();
    thunk_FUN_00414ad0(s_Exiting_main___x_0049cea0,local_14);
  }
LAB_0041dafe:
  *unaff_FS_OFFSET = local_10;
  return local_14;
}
```

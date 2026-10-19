# 0018_batch_0014 — détails (3/6)

## FUN_0046cd22 — 0x46cd22

- Classification : internal
- Corps : `0x46cd22–0x46e9d6`
- État : pseudocode obtenu
- Evidence : `ev_fbdcb9f3b27de341d258e85d68d67d6f9dbe6fb0971f77f99f80d7c8484fa98c`
- Limites : Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again. Def-use links do not cross function boundaries and may omit memory aliasing, call side effects, or unresolved indirect flow. Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>. High p-code is decompiler-derived, not original source or runtime behavior. is_dead preserves the Java AST flag; decoded block members can retain that flag, so block_membership separately reports actual syntax-tree membership. Known omitted-edge counts cover links omitted from retained operations; omitted operations may contain additional uncounted links. Memory read/write effects include stack and temporary memory operations; they do not identify persistent state or business meaning. Operation, input, and def-use limits can truncate large functions; inspect truncation, omitted lower bounds, and known omitted counts before drawing conclusions. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Pseudocode is neither original source nor guaranteed to compile. References cover the complete Ghidra function-body AddressSet and exact entry. Dossier incoming edges omit sources owned by that function; procedure_references also retains those internal edges. Register variables, compiler-generated blocks, and pointer arithmetic remain decompiler artifacts. Resolved reference metadata identifies computed, indirect, external, call, jump, and data edges; unresolved targetless flows remain unknown, and function classifications distinguish thunks and externals. Synthetic Ghidra entry-point references without actionable memory sources are omitted. The Java bridge serializes one function request per Program and lets each decompilation run until it completes or the caller cancels. The Windows bridge uses authenticated IPv4 loopback because Node path-based IPC does not expose Java AF_UNIX sockets; the endpoint file contains no bearer token. The dossier combines Ghidra FunctionManager, Listing, ReferenceManager, BasicBlockModel, and decompiler observations; provider-specific pseudocode and assembly are not cross-provider text invariants. The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written. The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results. The target references PDB Float.pdb (GUID unknown, age (hex) 0, signature 3418386f, version NB10); Ghidra reports load state unknown. Original names and types may be missing; an empty name search does not prove a procedure is absent. Use list_procedures and address-based analysis to inspect recovered functions. REA does not admit a caller-selected PDB companion. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Types and calling conventions are Ghidra decompiler observations, not source declarations. Unresolved computed or indirect flows without target addresses are not represented as reference edges. Windows Ghidra P0 accepts native x86 and x86-64 PE applications and DLLs, and explicitly selected raw 6502 images; managed, hostile, sensitive, and mutable-path targets are unsupported. Windows sessions require the matching packaged Windows x64 native addon, local NTFS targets and runtimes, and Windows 10 or later. Native handles enforce path admission, private DACLs, and Job Object ownership automatically.

### Appels directs

- `0x401032` — `thunk_FUN_00443298`
- `0x4010af` — `thunk_FUN_0043ea28`
- `0x401163` — `thunk_FUN_0042aa0f`
- `0x401195` — `thunk_FUN_00442b9c`
- `0x401249` — `thunk_FUN_00446493`
- `0x401375` — `thunk_FUN_00470132`
- `0x401384` — `thunk_FUN_0040e764`
- `0x401438` — `thunk_FUN_0040e1c0`
- `0x401488` — `thunk_FUN_0043c2f7`
- `0x401681` — `thunk_FUN_0046c897`
- `0x401695` — `thunk_FUN_004580fc`
- `0x4016d1` — `thunk_FUN_00445090`
- `0x401735` — `thunk_FUN_0043dc29`
- `0x4017c6` — `thunk_FUN_00438279`
- `0x4017f8` — `thunk_FUN_0042abf9`
- `0x401807` — `thunk_FUN_004199f0`
- `0x401857` — `thunk_FUN_004423e6`
- `0x40185c` — `thunk_FUN_004420eb`
- `0x401929` — `thunk_FUN_0043aa50`
- `0x40192e` — `thunk_FUN_0041a864`
- `0x4019a6` — `thunk_FUN_00447205`
- `0x4019b0` — `thunk_FUN_0043d200`
- `0x4019ba` — `thunk_FUN_0042a451`
- `0x4019bf` — `thunk_FUN_00439f30`
- `0x4019c4` — `thunk_FUN_00439583`
- `0x401acd` — `thunk_FUN_0040ebde`
- `0x401afa` — `thunk_FUN_0042930f`
- `0x401bfe` — `thunk_FUN_00438a9d`
- `0x401c2b` — `thunk_FUN_00414cff`
- `0x401c9e` — `thunk_FUN_00428884`
- `0x401cbc` — `thunk_FUN_00429243`
- `0x401cdf` — `thunk_FUN_00429f65`
- `0x401d6b` — `thunk_FUN_0041b05c`
- `0x401d89` — `thunk_FUN_0043b24c`
- `0x401dc0` — `thunk_FUN_004390b8`
- `0x401de8` — `thunk_FUN_00441caf`
- `0x401e1f` — `thunk_FUN_00446908`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fe6` — `thunk_FUN_0040f5b3`
- `0x402077` — `thunk_FUN_00442e8e`
- `0x402095` — `thunk_FUN_004428b0`
- `0x4020db` — `thunk_FUN_0043fb80`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x4022ac` — `thunk_FUN_0043e21b`
- `0x40231a` — `thunk_FUN_0044e704`
- `0x402388` — `thunk_FUN_004336b7`
- `0x4023b0` — `thunk_FUN_004578b7`
- `0x4023ba` — `thunk_FUN_0044a040`
- `0x4023d8` — `thunk_FUN_0040f419`
- `0x4023f1` — `thunk_FUN_0043ffc2`
- `0x4024aa` — `thunk_FUN_0046fe40`
- `0x4024b9` — `thunk_FUN_004425a1`
- `0x4024d2` — `thunk_FUN_00470259`
- `0x4024fa` — `thunk_FUN_0043b910`
- `0x472da0` — `FUN_00472da0`
- `0x472f10` — `FUN_00472f10`
- `0x4737e0` — `_strncpy`
- `0x4774f0` — `_strcmp`
- `0x478440` — `FUN_00478440`

### Chaînes référencées

- `0x4a592c` — "%s %d"
- `0x4a5934` — "shapes.txt"
- `0x4a5940` — "data\\bgoutfnt.fnt"
- `0x4a5954` — "%s %d"
- `0x4a595c` — "GameWindow"
- `0x4a5968` — "BitmapButton"
- `0x4a5978` — "BkgndArtWindow"
- `0x4a5988` — "SceneWindow"
- `0x4a5994` — "NewGameWin"
- `0x4a59a0` — "IsleClipBd"
- `0x4a59ac` — "NStateButton"
- `0x4a59bc` — "IsleWindow"
- `0x4a59c8` — "WorldWindow"
- `0x4a59d4` — "MovieWindow"
- `0x4a59e0` — "SlideWindow"
- `0x4a59ec` — "LoadSaveWindow"
- `0x4a59fc` — "IWLilMap"
- `0x4a5a08` — "IWRealm"
- `0x4a5a10` — "IWConstruct"
- `0x4a5a1c` — "IWConstructInfo"
- `0x4a5a2c` — "IWTasks"
- `0x4a5a34` — "IWTaskOptions"
- `0x4a5a44` — "IWTrade"
- `0x4a5a4c` — "IWDiplomacy"
- `0x4a5a58` — "IWLocControl"
- `0x4a5a68` — "IWLocInfo"
- `0x4a5a74` — "IWInventory"
- `0x4a5a80` — "IWGlyphs"
- `0x4a5a8c` — "IWTextInfo"
- `0x4a5a98` — "IWTaskInfo"
- `0x4a5aa4` — "IWFloaterInfo"
- `0x4a5ab4` — "IWMove"
- `0x4a5abc` — "IWStock"
- `0x4a5ac4` — "EndGamePlayer"
- `0x4a5ad4` — "EndGameNonPlayer"
- `0x4a5ae8` — "EndGameText"
- `0x4a5af4` — "IWEffectList"
- `0x4a5b04` — "IWSFXList"
- `0x4a5b10` — "IWOnOff"
- `0x4a5b18` — "IWUpgrade"
- `0x4a5b24` — "IWRepair"
- `0x4a5b30` — "IWTaskPriority"
- `0x4a5b40` — "IWPanic"
- `0x4a5b48` — "IWGetArtifact"
- `0x4a5b58` — "IWUpgSpread"
- `0x4a5b64` — "ClipSelector"
- `0x4a5b74` — "%s %s"
- `0x4a5b7c` — "%s %d %d %d %d %d %d %d %d"
- `0x4a5b98` — "status"
- `0x4a5ba0` — "C:\\float\\src\\winman.cpp"
- `0x4a5bb8` — "%s %s"
- `0x4a5bc8` — "Shape missing: %s (last=%s)"
- `0x4a5be4` — "wnd->mShapeHandle!=HCACHE_INVALID"
- `0x4a5c08` — "C:\\float\\src\\winman.cpp"
- `0x4a5c20` — "%s %d"
- `0x4a5c28` — "%s %d"
- `0x4a5c30` — "%s %d %d %d %d %d %d"
- `0x4a5c48` — "%s %d %d %d"
- `0x4a5c54` — "%s %s"
- `0x4a5c5c` — "WINMGR"
- `0x4a5c64` — "MASTER"
- `0x4a5c6c` — "%s %s"
- `0x4a5c74` — "%s %d %d %d %d"
- `0x4a5c84` — "%s %d"
- `0x4a5c8c` — "%s %d"
- `0x4a5c94` — "%s %d"
- `0x4a5c9c` — "Bad Window Type in windows.txt"
- `0x4a5cbc` — "FALSE"
- `0x4a5cc4` — "C:\\float\\src\\winman.cpp"

### Pseudocode Ghidra

```c
void FUN_0046cd22(undefined4 param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar3;
  undefined4 local_35c;
  undefined4 local_358;
  undefined4 local_354;
  undefined4 local_350;
  undefined4 local_34c;
  undefined4 local_348;
  undefined4 local_344;
  undefined4 local_340;
  undefined4 local_33c;
  undefined4 local_338;
  undefined4 local_334;
  undefined4 local_330;
  undefined4 local_32c;
  undefined4 local_328;
  undefined4 local_324;
  undefined4 local_320;
  undefined4 local_31c;
  undefined4 local_318;
  undefined4 local_314;
  undefined4 local_310;
  undefined4 local_30c;
  undefined4 local_308;
  undefined4 local_304;
  undefined4 local_300;
  undefined4 local_2fc;
  undefined4 local_2f8;
  undefined4 local_2f4;
  undefined4 local_2f0;
  undefined4 local_2ec;
  undefined4 local_2e8;
  undefined4 local_2e4;
  undefined4 local_2e0;
  undefined4 local_2dc;
  undefined4 local_2d8;
  undefined4 local_2d4;
  undefined4 local_2d0;
  undefined4 local_2cc;
  undefined4 local_2c8;
  undefined4 local_2c4;
  undefined4 local_2c0;
  undefined4 local_2bc;
  undefined4 local_2b8;
  int local_158;
  int local_150;
  undefined1 local_14c [28];
  int local_130;
  undefined1 local_12c [4];
  undefined1 local_128 [4];
  undefined1 local_124 [4];
  undefined1 local_120 [4];
  undefined1 local_11c [4];
  undefined1 local_118 [4];
  undefined1 local_114 [4];
  int local_110;
  undefined2 local_10c [2];
  undefined2 local_108 [2];
  undefined4 local_104;
  undefined4 local_100;
  int local_fc;
  undefined1 local_f8 [52];
  undefined4 local_c4;
  int local_c0 [4];
  short local_b0;
  int local_ac;
  undefined1 local_a8 [100];
  char local_44 [52];
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00491fcc;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  iVar2 = thunk_FUN_0040f419(param_1,&DAT_004b28f0,30000);
  if (iVar2 == 0) {
    thunk_FUN_0040f5b3(local_a8,0);
    FUN_00472f10(local_a8,s__s__d_004a592c,local_f8,&local_ac);
    thunk_FUN_0040e1c0(local_ac);
    thunk_FUN_0040e764(s_shapes_txt_004a5934);
    thunk_FUN_00428884(s_data_bgoutfnt_fnt_004a5940);
    while( true ) {
      thunk_FUN_0040f5b3(local_a8,0);
      FUN_00472f10(local_a8,s__s__d_004a5954,local_f8,&local_ac);
      if (local_ac == -1) break;
      local_b0 = (short)local_ac;
      switch(local_ac) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      case 10:
      case 0xb:
      case 0xc:
      case 0xd:
      case 0xe:
      case 0xf:
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x15:
      case 0x16:
      case 0x17:
      case 0x18:
      case 0x1a:
      case 0x1b:
      case 0x1c:
      case 0x1d:
      case 0x1e:
      case 0x1f:
      case 0x20:
      case 0x21:
      case 0x22:
      case 0x23:
      case 0x24:
      case 0x25:
      case 0x26:
      case 0x27:
      case 0x28:
      case 0x29:
      case 0x2a:
      case 0x2b:
      case 0x2c:
      case 0x2d:
      case 0x2e:
      case 0x2f:
      case 0x30:
        if (local_ac == 0) {
          iVar2 = FUN_00478440(0x70);
          local_8 = 0;
          if (iVar2 == 0) {
            local_2b8 = 0;
          }
          else {
            local_2b8 = thunk_FUN_00429243();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_GameWindow_004a595c,0x70,local_2b8);
        }
        else if (local_ac == 1) {
          iVar2 = FUN_00478440(0x70);
          local_8 = 1;
          if (iVar2 == 0) {
            local_2bc = 0;
          }
          else {
            local_2bc = thunk_FUN_00429f65();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_BitmapButton_004a5968,0x70,local_2bc);
        }
        else if (local_ac == 2) {
          iVar2 = FUN_00478440(0x74);
          local_8 = 2;
          if (iVar2 == 0) {
            local_2c0 = 0;
          }
          else {
            local_2c0 = thunk_FUN_0042aa0f();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_BkgndArtWindow_004a5978,0x74,local_2c0);
        }
        else if (local_ac == 3) {
          iVar2 = FUN_00478440(0x124);
          local_8 = 3;
          if (iVar2 == 0) {
            local_2c4 = 0;
          }
          else {
            local_2c4 = thunk_FUN_0042abf9();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_SceneWindow_004a5988,0x124,local_2c4);
        }
        else if (local_ac == 4) {
          iVar2 = FUN_00478440(0x8c);
          local_8 = 4;
          if (iVar2 == 0) {
            local_2c8 = 0;
          }
          else {
            local_2c8 = thunk_FUN_0044e704();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_NewGameWin_004a5994,0x8c,local_2c8);
        }
        else if (local_ac == 5) {
          iVar2 = FUN_00478440(0x74);
          local_8 = 5;
          if (iVar2 == 0) {
            local_2cc = 0;
          }
          else {
            local_2cc = thunk_FUN_004390b8();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IsleClipBd_004a59a0,0x74,local_2cc);
        }
        else if (local_ac == 6) {
          iVar2 = FUN_00478440(0x78);
          local_8 = 6;
          if (iVar2 == 0) {
            local_2d0 = 0;
          }
          else {
            local_2d0 = thunk_FUN_0042a451();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_NStateButton_004a59ac,0x78,local_2d0);
        }
        else if (local_ac == 10) {
          iVar2 = FUN_00478440(0x180);
          local_8 = 7;
          if (iVar2 == 0) {
            local_2d4 = 0;
          }
          else {
            local_2d4 = thunk_FUN_004336b7();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IsleWindow_004a59bc,0x180,local_2d4);
        }
        else if (local_ac == 0xb) {
          iVar2 = FUN_00478440(0x798);
          local_8 = 8;
          if (iVar2 == 0) {
            local_2d8 = 0;
          }
          else {
            local_2d8 = thunk_FUN_00470132();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_WorldWindow_004a59c8,0x798,local_2d8);
        }
        else if (local_ac == 0xc) {
          iVar2 = FUN_00478440(0xa4);
          local_8 = 9;
          if (iVar2 == 0) {
            local_2dc = 0;
          }
          else {
            local_2dc = thunk_FUN_0044a040();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_MovieWindow_004a59d4,0xa4,local_2dc);
        }
        else if (local_ac == 0xd) {
          iVar2 = FUN_00478440(0xa4);
          local_8 = 10;
          if (iVar2 == 0) {
            local_2e0 = 0;
          }
          else {
            local_2e0 = thunk_FUN_004578b7();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_SlideWindow_004a59e0,0xa4,local_2e0);
        }
        else if (local_ac == 0xe) {
          iVar2 = FUN_00478440(0x490);
          local_8 = 0xb;
          if (iVar2 == 0) {
            local_2e4 = 0;
          }
          else {
            local_2e4 = thunk_FUN_004580fc();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_LoadSaveWindow_004a59ec,0x490,local_2e4);
        }
        else if (local_ac == 0x10) {
          iVar2 = FUN_00478440(0x70);
          local_8 = 0xc;
          if (iVar2 == 0) {
            local_2e8 = 0;
          }
          else {
            local_2e8 = thunk_FUN_00438279();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWLilMap_004a59fc,0x70,local_2e8);
        }
        else if (local_ac == 0x11) {
          iVar2 = FUN_00478440(0x70);
          local_8 = 0xd;
          if (iVar2 == 0) {
            local_2ec = 0;
          }
          else {
            local_2ec = thunk_FUN_00438a9d();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWRealm_004a5a08,0x70,local_2ec);
        }
        else if (local_ac == 0x12) {
          iVar2 = FUN_00478440(0x78);
          local_8 = 0xe;
          if (iVar2 == 0) {
            local_2f0 = 0;
          }
          else {
            local_2f0 = thunk_FUN_0043aa50();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWConstruct_004a5a10,0x78,local_2f0);
        }
        else if (local_ac == 0x1c) {
          iVar2 = FUN_00478440(0x74);
          local_8 = 0xf;
          if (iVar2 == 0) {
            local_2f4 = 0;
          }
          else {
            local_2f4 = thunk_FUN_0043b24c();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWConstructInfo_004a5a1c,0x74,local_2f4);
        }
        else if (local_ac == 0x15) {
          iVar2 = FUN_00478440(0x108);
          local_8 = 0x10;
          if (iVar2 == 0) {
            local_2f8 = 0;
          }
          else {
            local_2f8 = thunk_FUN_00445090();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWTasks_004a5a2c,0x108,local_2f8);
        }
        else if (local_ac == 0x16) {
          iVar2 = FUN_00478440(0x74);
          local_8 = 0x11;
          if (iVar2 == 0) {
            local_2fc = 0;
          }
          else {
            local_2fc = thunk_FUN_00446493();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWTaskOptions_004a5a34,0x74,local_2fc);
        }
        else if (local_ac == 0x17) {
          iVar2 = FUN_00478440(0x88);
          local_8 = 0x12;
          if (iVar2 == 0) {
            local_300 = 0;
          }
          else {
            local_300 = thunk_FUN_0043ea28();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWTrade_004a5a44,0x88,local_300);
        }
        else if (local_ac == 0x18) {
          iVar2 = FUN_00478440(0x78);
          local_8 = 0x13;
          if (iVar2 == 0) {
            local_304 = 0;
          }
          else {
            local_304 = thunk_FUN_0043e21b();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWDiplomacy_004a5a4c,0x78,local_304);
        }
        else if (local_ac == 0x1a) {
          iVar2 = FUN_00478440(0x7c);
          local_8 = 0x14;
          if (iVar2 == 0) {
            local_308 = 0;
          }
          else {
            local_308 = thunk_FUN_0043fb80();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWLocControl_004a5a58,0x7c,local_308);
        }
        else if (local_ac == 0x1b) {
          iVar2 = FUN_00478440(0x84);
          local_8 = 0x15;
          if (iVar2 == 0) {
            local_30c = 0;
          }
          else {
            local_30c = thunk_FUN_0043ffc2();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWLocInfo_004a5a68,0x84,local_30c);
        }
        else if (local_ac == 0x1d) {
          iVar2 = FUN_00478440(300);
          local_8 = 0x16;
          if (iVar2 == 0) {
            local_310 = 0;
          }
          else {
            local_310 = thunk_FUN_0043d200();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWInventory_004a5a74,300,local_310);
        }
        else if (local_ac == 0x1e) {
          iVar2 = FUN_00478440(0xb0);
          local_8 = 0x17;
          if (iVar2 == 0) {
            local_314 = 0;
          }
          else {
            local_314 = thunk_FUN_0043dc29();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWGlyphs_004a5a80,0xb0,local_314);
        }
        else if (local_ac == 0x1f) {
          iVar2 = FUN_00478440(0x78);
          local_8 = 0x18;
          if (iVar2 == 0) {
            local_318 = 0;
          }
          else {
            local_318 = thunk_FUN_00439583();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWTextInfo_004a5a8c,0x78,local_318);
        }
        else if (local_ac == 0x20) {
          iVar2 = FUN_00478440(0x74);
          local_8 = 0x19;
          if (iVar2 == 0) {
            local_31c = 0;
          }
          else {
            local_31c = thunk_FUN_00446908();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWTaskInfo_004a5a98,0x74,local_31c);
        }
        else if (local_ac == 0x21) {
          iVar2 = FUN_00478440(0x74);
          local_8 = 0x1a;
          if (iVar2 == 0) {
            local_320 = 0;
          }
          else {
            local_320 = thunk_FUN_00443298();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWFloaterInfo_004a5aa4,0x74,local_320);
        }
        else if (local_ac == 0x22) {
          iVar2 = FUN_00478440(0x78);
          local_8 = 0x1b;
          if (iVar2 == 0) {
            local_324 = 0;
          }
          else {
            local_324 = thunk_FUN_00441caf();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWMove_004a5ab4,0x78,local_324);
        }
        else if (local_ac == 0x23) {
          iVar2 = FUN_00478440(0x7c);
          local_8 = 0x1c;
          if (iVar2 == 0) {
            local_328 = 0;
          }
          else {
            local_328 = thunk_FUN_004420eb();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWStock_004a5abc,0x7c,local_328);
        }
        else if (local_ac == 0x24) {
          iVar2 = FUN_00478440(0x70);
          local_8 = 0x1d;
          if (iVar2 == 0) {
            local_32c = 0;
          }
          else {
            local_32c = thunk_FUN_004199f0();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_EndGamePlayer_004a5ac4,0x70,local_32c);
        }
        else if (local_ac == 0x25) {
          iVar2 = FUN_00478440(0x74);
          local_8 = 0x1e;
          if (iVar2 == 0) {
            local_330 = 0;
          }
          else {
            local_330 = thunk_FUN_0041a864();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_EndGameNonPlayer_004a5ad4,0x74,local_330);
        }
        else if (local_ac == 0x26) {
          iVar2 = FUN_00478440(0x70);
          local_8 = 0x1f;
          if (iVar2 == 0) {
            local_334 = 0;
          }
          else {
            local_334 = thunk_FUN_0041b05c();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_EndGameText_004a5ae8,0x70,local_334);
        }
        else if (local_ac == 0x27) {
          iVar2 = FUN_00478440(0x84);
          local_8 = 0x20;
          if (iVar2 == 0) {
            local_338 = 0;
          }
          else {
            local_338 = thunk_FUN_0043b910();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWEffectList_004a5af4,0x84,local_338);
        }
        else if (local_ac == 0x28) {
          iVar2 = FUN_00478440(0x84);
          local_8 = 0x21;
          if (iVar2 == 0) {
            local_33c = 0;
          }
          else {
            local_33c = thunk_FUN_0043c2f7();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWSFXList_004a5b04,0x84,local_33c);
        }
        else if (local_ac == 0x29) {
          iVar2 = FUN_00478440(0x7c);
          local_8 = 0x22;
          if (iVar2 == 0) {
            local_340 = 0;
          }
          else {
            local_340 = thunk_FUN_004423e6();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWOnOff_004a5b10,0x7c,local_340);
        }
        else if (local_ac == 0x2a) {
          iVar2 = FUN_00478440(0x7c);
          local_8 = 0x23;
          if (iVar2 == 0) {
            local_344 = 0;
          }
          else {
            local_344 = thunk_FUN_004425a1();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWUpgrade_004a5b18,0x7c,local_344);
        }
        else if (local_ac == 0x2b) {
          iVar2 = FUN_00478440(0x7c);
          local_8 = 0x24;
          if (iVar2 == 0) {
            local_348 = 0;
          }
          else {
            local_348 = thunk_FUN_00442b9c();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWRepair_004a5b24,0x7c,local_348);
        }
        else if (local_ac == 0x2c) {
          iVar2 = FUN_00478440(0x78);
          local_8 = 0x25;
          if (iVar2 == 0) {
            local_34c = 0;
          }
          else {
            local_34c = thunk_FUN_00447205();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWTaskPriority_004a5b30,0x78,local_34c);
        }
        else if (local_ac == 0x2d) {
          iVar2 = FUN_00478440(0x74);
          local_8 = 0x26;
          if (iVar2 == 0) {
            local_350 = 0;
          }
          else {
            local_350 = thunk_FUN_00439f30();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWPanic_004a5b40,0x74,local_350);
        }
        else if (local_ac == 0x2e) {
          iVar2 = FUN_00478440(0x74);
          local_8 = 0x27;
          if (iVar2 == 0) {
            local_354 = 0;
          }
          else {
            local_354 = thunk_FUN_00442e8e();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWGetArtifact_004a5b48,0x74,local_354);
        }
        else if (local_ac == 0x2f) {
          iVar2 = FUN_00478440(0x7c);
          local_8 = 0x28;
          if (iVar2 == 0) {
            local_358 = 0;
          }
          else {
            local_358 = thunk_FUN_004428b0();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_IWUpgSpread_004a5b58,0x7c,local_358);
        }
        else if (local_ac == 0x30) {
          iVar2 = FUN_00478440(0x78);
          local_8 = 0x29;
          if (iVar2 == 0) {
            local_35c = 0;
          }
          else {
            local_35c = thunk_FUN_0046fe40();
          }
          local_8 = 0xffffffff;
          local_158 = thunk_FUN_00414cff(s_ClipSelector_004a5b64,0x78,local_35c);
        }
        thunk_FUN_0042930f();
        thunk_FUN_0040f5b3(local_a8,0);
        FUN_00472f10(local_a8,s__s__s_004a5b74,local_f8,local_158 + 0x20);
        thunk_FUN_0040f5b3(local_a8,0);
        iVar2 = FUN_00472f10(local_a8,s__s__d__d__d__d__d__d__d__d_004a5b7c,local_f8,&local_130,
                             local_12c,local_128,local_124,local_120,local_11c,local_118,local_114);
        for (local_150 = 0; local_150 < iVar2 + -1; local_150 = local_150 + 1) {
          if ((&local_130)[local_150] != -1) {
            local_fc = thunk_FUN_0046c897(*(undefined4 *)(local_158 + 4),
                                          CONCAT22((short)((uint)local_150 >> 0x10),
                                                   (short)(&local_130)[local_150]));
            if (local_fc == 0) {
              thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5ba0,0x819,s_status_004a5b98);
            }
          }
        }
        thunk_FUN_0040f5b3(local_a8,0);
        FUN_00472f10(local_a8,s__s__s_004a5bb8,local_f8,local_44);
        iVar2 = _strcmp(local_44,&DAT_004a5bc0);
        if (iVar2 != 0) {
          uVar1 = thunk_FUN_0040ebde(local_44);
          *(undefined2 *)(local_158 + 0x1c) = uVar1;
          if (*(short *)(local_158 + 0x1c) == -1) {
            thunk_FUN_00414ad0(s_Shape_missing___s__last__s__004a5bc8,local_44,local_14c);
          }
          if (*(short *)(local_158 + 0x1c) == -1) {
            uVar3 = thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5c08,0x826,
                                       s_wnd_>mShapeHandle__HCACHE_INVALI_004a5be4);
          }
          else {
            uVar3 = 0;
          }
          FUN_00472da0(local_14c,local_44,uVar3);
        }
        thunk_FUN_0040f5b3(local_a8,0);
        FUN_00472f10(local_a8,s__s__d_004a5c20,local_f8,&local_ac);
        *(short *)(local_158 + 0x1e) = (short)local_ac;
        thunk_FUN_0040f5b3(local_a8,0);
        FUN_00472f10(local_a8,s__s__d_004a5c28,local_f8,&local_ac);
        if (local_ac != 0) {
          *(undefined4 *)(local_158 + 0x44) = 1;
        }
        *(undefined4 *)(local_158 + 0x40) = 1;
        thunk_FUN_0040f5b3(local_a8,0);
        local_110 = FUN_00472f10(local_a8,s__s__d__d__d__d__d__d_004a5c30,local_f8,local_c0,
                                 &local_c4,&local_100,&local_104,local_108,local_10c);
        *(int *)(local_158 + 0xc) = local_c0[0];
        *(undefined4 *)(local_158 + 0x10) = local_c4;
        *(undefined4 *)(local_158 + 0x14) = local_100;
        *(undefined4 *)(local_158 + 0x18) = local_104;
        if (local_110 == 7) {
          *(undefined2 *)(local_158 + 0x6c) = local_108[0];
          *(undefined2 *)(local_158 + 0x6e) = local_10c[0];
        }
        thunk_FUN_0040f5b3(local_a8,0);
        FUN_00472f10(local_a8,s__s__d__d__d_004a5c48,local_f8,local_158 + 0x60,local_158 + 100,
                     local_158 + 0x68);
        thunk_FUN_0040f5b3(local_a8,0);
        FUN_00472f10(local_a8,s__s__s_004a5c54,local_f8,local_44);
        iVar2 = _strcmp(local_44,s_WINMGR_004a5c5c);
        if (iVar2 == 0) {
          *(undefined4 *)(local_158 + 0x48) = 1;
        }
        else {
          iVar2 = _strcmp(local_44,s_MASTER_004a5c64);
          if (iVar2 == 0) {
            *(undefined4 *)(local_158 + 0x48) = 0;
          }
          else {
            *(undefined4 *)(local_158 + 0x48) = 2;
            _strncpy((char *)(local_158 + 0x4c),local_44,0x13);
            *(undefined1 *)(local_158 + 0x5f) = 0;
          }
        }
        if (local_b0 == 0xc) {
          thunk_FUN_0040f5b3(local_a8,0);
          FUN_00472f10(local_a8,s__s__s_004a5c6c,local_f8,local_44);
          FUN_00472da0(local_158 + 0x70,local_44);
        }
        if (local_b0 == 0xd) {
          thunk_FUN_0040f5b3(local_a8,0);
          FUN_00472f10(local_a8,s__s__d__d__d__d_004a5c74,local_f8,local_c0,&local_c4,&local_100,
                       &local_104);
          *(int *)(local_158 + 0x78) = local_c0[0];
          *(undefined4 *)(local_158 + 0x7c) = local_c4;
          *(undefined4 *)(local_158 + 0x80) = local_100;
          *(undefined4 *)(local_158 + 0x84) = local_104;
        }
        if (local_b0 == 3) {
          thunk_FUN_0040f5b3(local_a8,0);
          FUN_00472f10(local_a8,s__s__d_004a5c84,local_f8,local_c0);
          *(uint *)(local_158 + 0x74) = (uint)(local_c0[0] != 0);
        }
        if (local_b0 == 0xb) {
          thunk_FUN_00470259();
        }
        if ((((local_b0 == 6) || (local_b0 == 0x23)) || (local_b0 == 0x2b)) ||
           (((local_b0 == 0x2a || (local_b0 == 0x2f)) || (local_b0 == 0x29)))) {
          thunk_FUN_0040f5b3(local_a8,0);
          FUN_00472f10(local_a8,s__s__d_004a5c8c,local_f8,local_c0);
          *(undefined2 *)(local_158 + 0x70) = (undefined2)local_c0[0];
          thunk_FUN_0040f5b3(local_a8,0);
          FUN_00472f10(local_a8,s__s__d_004a5c94,local_f8,local_c0);
          *(undefined2 *)(local_158 + 0x74) = (undefined2)local_c0[0];
        }
        break;
      default:
        thunk_FUN_00414ad0(s_Bad_Window_Type_in_windows_txt_004a5c9c);
        thunk_FUN_00414b64(s_C__float_src_winman_cpp_004a5cc4,0x88a,s_FALSE_004a5cbc);
      }
    }
  }
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

## FUN_0046ea1c — 0x46ea1c

- Classification : internal
- Corps : `0x46ea1c–0x46ea96`
- État : pseudocode obtenu
- Evidence : `ev_d48f1b898bd1118c0aa954997cc4517887787d33e0a72d095caa0cb2a5bf601e`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046ea1c(undefined4 param_1,undefined4 param_2)

{
  int in_ECX;
  undefined2 local_8;
  
  for (local_8 = 1; local_8 < 0x29a; local_8 = local_8 + 1) {
    if ((*(int *)(in_ECX + local_8 * 0xc) != 0) && (*(int *)(in_ECX + 4 + local_8 * 0xc) != 0)) {
      (**(code **)(**(int **)(in_ECX + 4 + local_8 * 0xc) + 0x10))(param_1,param_2);
    }
  }
  return;
}
```

---

## FUN_0046fe40 — 0x46fe40

- Classification : internal
- Corps : `0x46fe40–0x46fe5e`
- État : pseudocode obtenu
- Evidence : `ev_9a1a3a438de61cc5b8f9e7fac8cd50093ff70d729cd3655cfe68f825bbe2e6f2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x402211` — `thunk_FUN_0042a1a1`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 * FUN_0046fe40(void)

{
  undefined4 *in_ECX;
  
  thunk_FUN_0042a1a1();
  *in_ECX = &PTR_LAB_004947a0;
  return in_ECX;
}
```

---

## FUN_0046fe70 — 0x46fe70

- Classification : internal
- Corps : `0x46fe70–0x46fe9d`
- État : pseudocode obtenu
- Evidence : `ev_7ca457e37be27cdf371c1b637a9b53e7035260717e76125345f0d769a6f18b22`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401fdc` — `thunk_FUN_0046feb0`
- `0x476d90` — `FUN_00476d90`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0046fe70(uint param_1)

{
  undefined4 in_ECX;
  
  thunk_FUN_0046feb0();
  if ((param_1 & 1) != 0) {
    FUN_00476d90(in_ECX);
  }
  return in_ECX;
}
```

---

## FUN_0046feb0 — 0x46feb0

- Classification : internal
- Corps : `0x46feb0–0x46fecb`
- État : pseudocode obtenu
- Evidence : `ev_a3e3a03b599004fa9de90a793e7ba8f693a2ddc2bd2e94b4160d180334586c32`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40200e` — `thunk_FUN_0042a1f5`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0046feb0(void)

{
  undefined4 *in_ECX;
  
  *in_ECX = &PTR_LAB_004947a0;
  thunk_FUN_0042a1f5();
  return;
}
```

---

## FUN_0046fee0 — 0x46fee0

- Classification : internal
- Corps : `0x46fee0–0x46ff6e`
- État : pseudocode obtenu
- Evidence : `ev_a33f146f8e48c8e669f38a10be45c43598481d1896ac8c3b3c41b222c949c3f4`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0046fee0(int *param_1,int *param_2)

{
  undefined4 local_8;
  
  local_8 = 0;
  if (*(int *)(*param_1 + 4) == *(int *)(*param_2 + 4)) {
    if (*(float *)(*param_1 + 0x10) <= *(float *)(*param_2 + 0x10)) {
      if (*(float *)(*param_1 + 0x10) < *(float *)(*param_2 + 0x10)) {
        local_8 = 1;
      }
    }
    else {
      local_8 = 0xffffffff;
    }
  }
  else if (*(int *)(*param_1 + 4) == 0) {
    local_8 = 1;
  }
  else {
    local_8 = 0xffffffff;
  }
  return local_8;
}
```

---


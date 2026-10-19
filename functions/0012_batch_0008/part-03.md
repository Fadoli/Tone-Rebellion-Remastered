# 0012_batch_0008 — détails (3/8)

## FUN_0042fa0f — 0x42fa0f

- Classification : internal
- Corps : `0x42fa0f–0x431d13`
- État : pseudocode obtenu
- Evidence : `ev_6ac7cc6650dc8a0e9b412c055606948d1c6dbbdd3e6c6df0a7fcc1551764419e`
- Evidence complémentaire (message `0x40`, branche glyphe) : `ev_a8230350584e54954217dfeda123b6cf8d9dc6ca7211fff2385661c22cdab6ba`
- Note de flux : `0x32` saute le `switch` des messages et rejoint le traitement commun de l'objet sélectionné. Le callback du slot 3 est inscrit au démarrage, mais mode et slot actifs à l'émission ne sont pas établis. Evidence `ev_a8230350584e54954217dfeda123b6cf8d9dc6ca7211fff2385661c22cdab6ba`.
- Limites : Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again. Def-use links do not cross function boundaries and may omit memory aliasing, call side effects, or unresolved indirect flow. Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>. High p-code is decompiler-derived, not original source or runtime behavior. is_dead preserves the Java AST flag; decoded block members can retain that flag, so block_membership separately reports actual syntax-tree membership. Known omitted-edge counts cover links omitted from retained operations; omitted operations may contain additional uncounted links. Memory read/write effects include stack and temporary memory operations; they do not identify persistent state or business meaning. Operation, input, and def-use limits can truncate large functions; inspect truncation, omitted lower bounds, and known omitted counts before drawing conclusions. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Pseudocode is neither original source nor guaranteed to compile. References cover the complete Ghidra function-body AddressSet and exact entry. Dossier incoming edges omit sources owned by that function; procedure_references also retains those internal edges. Register variables, compiler-generated blocks, and pointer arithmetic remain decompiler artifacts. Resolved reference metadata identifies computed, indirect, external, call, jump, and data edges; unresolved targetless flows remain unknown, and function classifications distinguish thunks and externals. Synthetic Ghidra entry-point references without actionable memory sources are omitted. The Java bridge serializes one function request per Program and lets each decompilation run until it completes or the caller cancels. The Windows bridge uses authenticated IPv4 loopback because Node path-based IPC does not expose Java AF_UNIX sockets; the endpoint file contains no bearer token. The dossier combines Ghidra FunctionManager, Listing, ReferenceManager, BasicBlockModel, and decompiler observations; provider-specific pseudocode and assembly are not cross-provider text invariants. The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written. The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results. The target references PDB Float.pdb (GUID unknown, age (hex) 0, signature 3418386f, version NB10); Ghidra reports load state unknown. Original names and types may be missing; an empty name search does not prove a procedure is absent. Use list_procedures and address-based analysis to inspect recovered functions. REA does not admit a caller-selected PDB companion. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Types and calling conventions are Ghidra decompiler observations, not source declarations. Unresolved computed or indirect flows without target addresses are not represented as reference edges. Windows Ghidra P0 accepts native x86 and x86-64 PE applications and DLLs, and explicitly selected raw 6502 images; managed, hostile, sensitive, and mutable-path targets are unsupported. Windows sessions require the matching packaged Windows x64 native addon, local NTFS targets and runtimes, and Windows 10 or later. Native handles enforce path admission, private DACLs, and Job Object ownership automatically.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`
- `0x4010e6` — `thunk_FUN_0042f755`
- `0x40119f` — `thunk_FUN_0046c371`
- `0x401208` — `thunk_FUN_0043530b`
- `0x4012ee` — `thunk_FUN_0046c458`
- `0x4013a2` — `thunk_FUN_004354a2`
- `0x4014ba` — `thunk_FUN_0042dd47`
- `0x4014e7` — `thunk_FUN_0045035a`
- `0x4014fb` — `thunk_FUN_0042f9c5`
- `0x401569` — `thunk_FUN_0046c558`
- `0x401762` — `thunk_FUN_0042f303`
- `0x4018e3` — `thunk_FUN_0046c3bc`
- `0x401906` — `thunk_FUN_0045c325`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x4019e2` — `thunk_FUN_0046c1b4`
- `0x401a32` — `thunk_FUN_0042f8f7`
- `0x401adc` — `thunk_FUN_00416a9a`
- `0x401b68` — `thunk_FUN_0042f150`
- `0x401b8b` — `thunk_FUN_0042fa0f`
- `0x401bea` — `thunk_FUN_004334ce`
- `0x401dac` — `thunk_FUN_004207f2`
- `0x401e65` — `thunk_FUN_0046c4a5`
- `0x401e9c` — `thunk_FUN_00466c08`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4021bc` — `thunk_FUN_004381e1`
- `0x40224d` — `thunk_FUN_00450070`
- `0x40228e` — `thunk_FUN_00414081`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x4023bf` — `thunk_FUN_0045c3bb`
- `0x472c6c` — `__ftol`
- `0x474b20` — `_memset`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x49ed3c` — "ISLEVIEW"
- `0x49ed48` — "ISLETMP"
- `0x49ed50` — "SHADE"
- `0x49ed58` — "IWLilMap"
- `0x49ed64` — "CLIPSEL1"
- `0x49ed70` — "CLIPSEL2"
- `0x49ed7c` — "CLIPSEL3"
- `0x49ed88` — "CLIPBD1"
- `0x49ed90` — "CLIPBD2"
- `0x49ed98` — "CLIPBD3"
- `0x49eda0` — "IWRealm"
- `0x49eda8` — "GOTOMAP"
- `0x49edb0` — "PANIC"
- `0x49edb8` — "TOGREALM"
- `0x49edc4` — "TASKLIST"
- `0x49edd0` — "ISLEVIEW"
- `0x49eddc` — "IWLilMap"
- `0x49ede8` — "IWConstructInfo"
- `0x49edf8` — "pIMIsleWindow->mpSelectedLoc"
- `0x49ee18` — "C:\\float\\src\\islemast.cpp"
- `0x49ee34` — "pIMIsleWindow->mpSelectedLoc"
- `0x49ee54` — "C:\\float\\src\\islemast.cpp"
- `0x49ee70` — "No staffbld.  mItem=%d,mOwner=%d"
- `0x49ee94` — "FALSE"
- `0x49ee9c` — "C:\\float\\src\\islemast.cpp"
- `0x49eeb8` — "BC_HallStkB"
- `0x49eec4` — "BC_HallStkC"
- `0x49eed0` — "BC_HallStkM"
- `0x49eedc` — "BC_HallStkB"
- `0x49eee8` — "BC_HallStkC"
- `0x49eef4` — "BC_HallStkM"
- `0x49ef00` — "BC_HallStkB"
- `0x49ef0c` — "BC_HallStkC"
- `0x49ef18` — "BC_HallStkM"
- `0x49ef24` — "BC_HallStkB"
- `0x49ef30` — "BC_HallStkC"
- `0x49ef3c` — "BC_HallStkM"
- `0x49ef48` — "ACTIVETRIBEPTR->mbHaveGrabbed==FALSE"
- `0x49ef70` — "C:\\float\\src\\islemast.cpp"
- `0x49ef8c` — "pIMIsleWindow"
- `0x49ef9c` — "C:\\float\\src\\islemast.cpp"
- `0x49efb8` — "ACTIVETRIBEPTR->mbHaveGrabbed==TRUE"
- `0x49efdc` — "C:\\float\\src\\islemast.cpp"
- `0x49eff8` — "pIMIsleWindow"
- `0x49f008` — "C:\\float\\src\\islemast.cpp"
- `0x49f024` — "IWLocInfo"
- `0x49f030` — "IWLocControl"
- `0x49f040` — "ACTIVETRIBEPTR->mbHaveGrabbed==TRUE"
- `0x49f064` — "C:\\float\\src\\islemast.cpp"
- `0x49f080` — "IWTasks"
- `0x49f088` — "farloc"
- `0x49f090` — "C:\\float\\src\\islemast.cpp"
- `0x49f0ac` — "IWLocInfo"
- `0x49f0b8` — "locinfo"
- `0x49f0c0` — "C:\\float\\src\\islemast.cpp"
- `0x49f0e0` — "C:\\float\\src\\islemast.cpp"
- `0x49f0fc` — "IWMove"
- `0x49f104` — "IWHallMove"
- `0x49f110` — "IWFltInfo"
- `0x49f11c` — "IWTextInfo"
- `0x49f128` — "IWTextInfo"
- `0x49f134` — "IWLocInfo"
- `0x49f144` — "C:\\float\\src\\islemast.cpp"
- `0x49f160` — "IWMove"
- `0x49f168` — "IWHallMove"
- `0x49f174` — "IWLocInfo"
- `0x49f180` — "IWTextInfo"
- `0x49f18c` — "IWHallMove"
- `0x49f198` — "IWMove"
- `0x49f1a0` — "CLIPBD1"
- `0x49f1a8` — "CLIPBD2"
- `0x49f1b0` — "CLIPBD3"
- `0x49f1b8` — "CLIPSEL1"
- `0x49f1c4` — "CLIPSEL2"
- `0x49f1d0` — "CLIPSEL3"
- `0x49f1dc` — "pIMIsleWindow"
- `0x49f1ec` — "C:\\float\\src\\islemast.cpp"
- `0x49f208` — "IWTasks"
- `0x49f210` — "iwtasks"
- `0x49f218` — "C:\\float\\src\\islemast.cpp"
- `0x49f234` — "IWTasks"
- `0x49f23c` — "iwtasks"
- `0x49f244` — "C:\\float\\src\\islemast.cpp"
- `0x49f260` — "IWTrade"
- `0x49f268` — "trader"
- `0x49f270` — "C:\\float\\src\\islemast.cpp"
- `0x49f28c` — "IWTrade"
- `0x49f294` — "trader"
- `0x49f29c` — "C:\\float\\src\\islemast.cpp"
- `0x49f2b8` — "IWEffList"
- `0x49f2c4` — "IWSFXList"
- `0x49f2d0` — "IWTasks"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0042fa0f(short param_1,int param_2,uint param_3,undefined4 *param_4)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  int local_1e8 [2];
  int local_1e0;
  int local_1dc;
  uint local_1d8;
  undefined2 local_1d0;
  undefined2 local_1ce;
  undefined2 local_1cc;
  undefined2 local_1ca;
  undefined2 local_1c8;
  undefined2 local_1c6;
  undefined2 local_1c4;
  int local_1c0;
  int local_1bc;
  int local_1b8;
  int local_1b4;
  undefined2 local_1b0;
  undefined2 local_1ae;
  undefined2 local_1ac;
  undefined2 local_1aa;
  undefined2 local_1a8;
  undefined2 local_1a6;
  undefined2 local_1a4;
  int local_1a0;
  int *local_19c;
  undefined2 local_198;
  undefined2 local_196;
  short local_194;
  undefined2 local_192;
  undefined2 local_190;
  undefined2 local_18e;
  undefined2 local_18c;
  int local_188;
  int *local_184;
  int local_180;
  int local_17c;
  int local_178;
  undefined2 local_174;
  undefined2 local_172;
  undefined2 local_170;
  short local_16e;
  short local_16a;
  undefined2 local_164;
  undefined2 local_162;
  undefined2 local_160;
  short local_15e;
  short local_15a;
  undefined2 local_158;
  short local_156;
  short local_154;
  undefined2 local_150;
  int local_14c;
  undefined4 local_148;
  undefined *local_144;
  int local_140;
  undefined4 local_13c;
  undefined4 local_138;
  int local_134;
  int local_130;
  int local_12c;
  int local_128;
  int local_124;
  int local_120;
  int local_11c;
  int local_118;
  uint local_114;
  uint local_110;
  undefined2 local_10c;
  undefined2 local_10a;
  undefined2 local_108;
  undefined2 local_106;
  undefined2 local_104;
  short local_102;
  short local_100;
  undefined *local_fc;
  undefined *local_f8;
  undefined2 local_f4;
  undefined2 local_f2;
  undefined2 local_f0;
  short local_ee;
  undefined2 local_ec;
  short local_ea;
  short local_e8;
  short local_e6;
  int local_e4;
  undefined *local_e0;
  int local_dc;
  undefined2 local_d8;
  undefined2 local_d6;
  undefined2 local_d4;
  short local_d2;
  undefined2 local_ce;
  short *local_c8;
  int local_c4;
  double local_c0;
  int local_b8;
  int *local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  undefined *local_a4;
  int local_a0;
  int local_9c;
  int local_98;
  int local_94;
  undefined *local_90;
  undefined2 local_8c;
  undefined2 local_8a;
  undefined2 local_88;
  undefined2 local_86;
  undefined2 local_84;
  undefined2 local_82;
  undefined2 local_80;
  int local_7c;
  undefined2 local_78;
  undefined2 local_76;
  undefined2 local_74;
  undefined2 local_72;
  undefined2 local_70;
  undefined2 local_6e;
  undefined2 local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  undefined2 local_58;
  undefined2 local_56;
  undefined2 local_54;
  undefined2 local_52;
  undefined2 local_50;
  undefined2 local_4e;
  undefined2 local_4c;
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  undefined2 local_42;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  int local_38;
  int local_34;
  uint local_30;
  undefined *local_2c;
  int local_28;
  uint local_24;
  undefined *local_20;
  int local_1c;
  int local_14;
  undefined2 local_10;
  int local_c;
  undefined *local_8;
  
  iVar3 = (int)param_1;
  if (iVar3 < 0x33) {
    if (iVar3 != 0x32) {
      switch(iVar3 + -1) {
      case 0:
        thunk_FUN_0046c3bc(s_ISLEVIEW_0049ed3c,1,0,0);
        thunk_FUN_0046c3bc(s_ISLETMP_0049ed48,1,0,0);
        thunk_FUN_0046c3bc(s_SHADE_0049ed50,1,0,0);
        thunk_FUN_0046c3bc(s_IWLilMap_0049ed58,1,0,0);
        thunk_FUN_0046c3bc(s_CLIPSEL1_0049ed64,1,0,0);
        thunk_FUN_0046c3bc(s_CLIPSEL2_0049ed70,1,0,0);
        thunk_FUN_0046c3bc(s_CLIPSEL3_0049ed7c,1,0,0);
        thunk_FUN_0046c3bc(s_CLIPBD1_0049ed88,1,0,0);
        thunk_FUN_0046c3bc(s_CLIPBD2_0049ed90,1,0,0);
        thunk_FUN_0046c3bc(s_CLIPBD3_0049ed98,1,0,0);
        thunk_FUN_0046c3bc(s_IWRealm_0049eda0,1,0,0);
        thunk_FUN_0046c3bc(s_GOTOMAP_0049eda8,1,0,0);
        thunk_FUN_0046c3bc(s_PANIC_0049edb0,1,0,0);
        thunk_FUN_0046c3bc(s_TOGREALM_0049edb8,1,0,0);
        thunk_FUN_0046c3bc(s_TASKLIST_0049edc4,1,0,0);
        thunk_FUN_0042f150();
        if (DAT_005c37e4 == (int *)0x0) {
          DAT_005c37e4 = (int *)thunk_FUN_0046c4a5(s_ISLEVIEW_0049edd0,0);
        }
        if (DAT_005c37ec == (int *)0x0) {
          DAT_005c37ec = (int *)thunk_FUN_0046c4a5(s_IWLilMap_0049eddc,0);
        }
        _DAT_005c37e8 = DAT_005c37e4[0x27];
        DAT_005c37e4[0x5a] = 1;
        DAT_0049e9c0 = 0xffff;
        DAT_0049e9c4 = 0xffff;
        if (*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) == 0) {
          thunk_FUN_0042f303(0);
          return;
        }
        local_8 = &DAT_005ec640 +
                  *(short *)(DAT_0049f538 * 0x14a0 + 0x61a574) * 0x60 +
                  *(short *)(DAT_0049f538 * 0x14a0 + 0x61a572) * 0x29e8;
        DAT_005c37e4[0x5b] = (int)local_8;
        thunk_FUN_0042f755(local_8,1);
        return;
      case 1:
        thunk_FUN_0042f9c5();
        _DAT_005c37e8 = 0;
        return;
      default:
        return;
      case 3:
        if (param_4 == (undefined4 *)0x0) {
          return;
        }
        local_10 = (undefined2)DAT_0062c6bc;
        local_14 = thunk_FUN_0046c458(CONCAT22((short)((uint)(iVar3 + -1) >> 0x10),
                                               (undefined2)DAT_0062c6bc));
        if (local_14 == 0) {
          return;
        }
        uVar4 = thunk_FUN_00429ebe(local_14,0);
        *param_4 = uVar4;
        return;
      case 4:
        goto switchD_0042fa5b_caseD_4;
      case 5:
        local_130 = DAT_005c37e4[0x5b];
        if (local_130 == 0) {
          return;
        }
        local_134 = param_2;
        if (param_2 == 0) {
          thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049f144,0x536,&DAT_0049f140);
        }
        local_12c = 0;
        iVar3 = __strcmpi((char *)(local_134 + 0x20),s_IWMove_0049f160);
        if ((iVar3 == 0) ||
           (iVar3 = __strcmpi((char *)(local_134 + 0x20),s_IWHallMove_0049f168), iVar3 == 0)) {
          local_12c = 1;
        }
        if ((*(short *)(local_134 + 0x60) != 0x65) && (local_12c == 0)) {
          return;
        }
        local_138 = 0;
        if (DAT_0049e9cc == 4) {
          local_138 = 6;
        }
        else if (DAT_0049e9cc == 5) {
          local_138 = 7;
        }
        else if (DAT_0049e9cc == 6) {
          local_138 = 8;
        }
        else if (DAT_0049e9cc == 7) {
          local_138 = 9;
        }
        thunk_FUN_0046c3bc(s_IWLocInfo_0049f174,0x350d,0xffffffff,0);
        thunk_FUN_0046c3bc(s_IWTextInfo_0049f180,0x3039,local_138,local_130);
        local_140 = DAT_005c37e4[0x5c];
        local_13c = thunk_FUN_00450385();
        if (local_140 == 0) {
          return;
        }
        iVar3 = thunk_FUN_004207f2();
        if (iVar3 != 0) {
          iVar3 = thunk_FUN_004207f2();
          iVar5 = thunk_FUN_00450385();
          if (iVar3 != iVar5) {
            return;
          }
        }
        thunk_FUN_0042f8f7();
        return;
      case 6:
        local_11c = DAT_005c37e4[0x5b];
        if (local_11c == 0) {
          return;
        }
        local_120 = param_2;
        if (param_2 == 0) {
          thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049f0e0,0x503,&DAT_0049f0dc);
        }
        local_118 = -1;
        local_124 = -1;
        iVar3 = __strcmpi((char *)(local_120 + 0x20),s_IWMove_0049f0fc);
        if ((iVar3 == 0) ||
           (iVar3 = __strcmpi((char *)(local_120 + 0x20),s_IWHallMove_0049f104), iVar3 == 0)) {
          local_118 = 5;
          local_124 = 1;
        }
        else if (*(short *)(local_120 + 0x60) == 0x65) {
          local_128 = *(int *)(local_120 + 100);
          if ((local_128 < 0x15) || (0x1c < local_128)) {
            local_118 = 5;
            local_124 = *(int *)(local_120 + 100);
          }
          else {
            local_118 = 4;
            local_124 = thunk_FUN_00450070(local_11c,local_128);
          }
        }
        if (local_118 == -1) {
          return;
        }
        if (local_124 == -1) {
          return;
        }
        thunk_FUN_0046c3bc(s_IWFltInfo_0049f110,2,0,0);
        thunk_FUN_0046c3bc(s_IWTextInfo_0049f11c,1,0,0);
        thunk_FUN_0046c3bc(s_IWTextInfo_0049f128,0x3039,local_118,local_124);
        if (local_118 != 4) {
          return;
        }
        thunk_FUN_0046c3bc(s_IWLocInfo_0049f134,0x350d,local_124,0);
        return;
      }
    }
    if (DAT_005c37e4[0x5b] == 0) {
      return;
    }
    local_a8 = DAT_005c37e4[0x5b];
    DAT_005c37e4[0x5d] = 0;
    *(undefined2 *)(DAT_005c37e4 + 0x5e) = 0;
    if (*(int *)(local_a8 + 4) != 0) {
      if (*(int *)(local_a8 + 4) != 2) {
        if ((*(int *)(local_a8 + 4) != 1) && (*(int *)(local_a8 + 4) != 3)) {
          return;
        }
        thunk_FUN_0042f755(local_a8,1);
        return;
      }
      if ((*(uint *)(local_a8 + 0x1c) & 1) == 0) {
        thunk_FUN_0042f755(local_a8,1);
        return;
      }
      if (DAT_004befe0 != 0) {
        _memset(&local_d8,0,0x10);
        local_d8 = 2;
        local_d6 = (undefined2)DAT_0049f538;
        local_d2 = DAT_0049f53c;
        local_ce = *(undefined2 *)(local_a8 + 0x36);
        local_d4 = 9;
        thunk_FUN_00414081(1,&local_d8,0x10);
      }
      thunk_FUN_0042fa0f(0x4d,(int)*(short *)(local_a8 + 0x36),0,0);
      local_c8 = (short *)thunk_FUN_00466c08(*(undefined2 *)(local_a8 + 8),
                                             CONCAT22(extraout_var,*(undefined2 *)(local_a8 + 0x36))
                                            );
      if (local_c8 == (short *)0x0) {
        thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049f090,0x431,s_farloc_0049f088);
      }
      local_c0 = ((double)(*local_c8 + -0x140) * 1000.0) / 1921.0;
      uVar4 = __ftol(1,0);
      thunk_FUN_0042fa0f(0x3d,uVar4);
      local_c4 = thunk_FUN_0046c558(s_IWLocInfo_0049f0ac,3,0);
      if (local_c4 == 0) {
        thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049f0c0,0x43c,s_locinfo_0049f0b8);
      }
      if (*(int *)(local_c4 + 0x70) == 0) {
        return;
      }
      DAT_005c37e4[0x5b] = *(int *)(local_c4 + 0x70);
      thunk_FUN_0042f755(*(undefined4 *)(local_c4 + 0x70),1);
      return;
    }
    if ((-1 < *(int *)(local_a8 + 0x10)) && (*(int *)(local_a8 + 0x10) < 2)) {
      if ((*(int *)(local_a8 + 0x24) < 5) || (0x21 < *(int *)(local_a8 + 0x24))) {
        if (((int)*(char *)(local_a8 + 0x22) & 1 << ((byte)DAT_0049f538 & 0x1f)) != 0) {
          local_b4 = &DAT_006183bc;
          local_b0 = 0;
          local_b8 = 0;
          local_ac = 0;
          while( true ) {
            if ((0x3f < local_ac) || ((int)(uint)DAT_006188bc <= local_b0)) goto LAB_004309ee;
            if ((*local_b4 != 0) &&
               ((((local_b0 = local_b0 + 1, *(short *)((int)local_b4 + 10) == DAT_0049f53c &&
                  (sVar1 = *(short *)((int)local_b4 + 0xe), sVar2 = thunk_FUN_0045035a(),
                  sVar1 == sVar2)) && ((short)local_b4[4] == 5)) &&
                ((short)local_b4[2] == DAT_0049f538)))) break;
            local_ac = local_ac + 1;
            local_b4 = local_b4 + 5;
          }
          thunk_FUN_0046c3bc(s_IWTasks_0049f080,4999,local_ac,0);
          thunk_FUN_0042f303(2);
          local_b8 = 1;
LAB_004309ee:
          if (local_b8 == 0) {
            thunk_FUN_0042f303(1);
          }
        }
      }
      else {
        thunk_FUN_0042f755(local_a8,1);
      }
    }
    if (*(int *)(local_a8 + 0x10) == 0) {
      return;
    }
    if (*(int *)(local_a8 + 0x10) == 1) {
      return;
    }
    thunk_FUN_0042f755(local_a8,1);
    return;
  }
  if (iVar3 < 0x66) {
    if (iVar3 == 0x65) {
      if (DAT_005c37e4[0x5b] == 0) {
        thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049ee18,0x2ac,
                           s_pIMIsleWindow_>mpSelectedLoc_0049edf8);
      }
      local_38 = DAT_005c37e4[0x5b];
      local_34 = param_2;
      switch(param_2) {
      case 0:
      case 2:
      case 3:
        _memset(&local_48,0,0x10);
        local_48 = 1;
        local_46 = (undefined2)DAT_0049f538;
        local_42 = *(undefined2 *)(local_38 + 8);
        local_44 = (undefined2)local_34;
        local_3e = local_42;
        local_40 = thunk_FUN_0045035a();
        local_3c = local_40;
        thunk_FUN_00414081(1,&local_48,0x10);
        break;
      case 4:
        thunk_FUN_0042fa0f(0x39,0,0,0);
        thunk_FUN_0042f303(0);
        break;
      case 5:
      case 6:
        if (DAT_005c37e4[0x5b] == 0) {
          thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049ee54,0x2eb,
                             s_pIMIsleWindow_>mpSelectedLoc_0049ee34);
        }
        local_5c = thunk_FUN_00450385();
        if (local_5c == 0) {
          thunk_FUN_00414ad0(s_No_staffbld__mItem__d_mOwner__d_0049ee70,
                             *(undefined4 *)(DAT_005c37e4[0x5b] + 0x10),
                             *(undefined4 *)(DAT_005c37e4[0x5b] + 0x14));
          thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049ee9c,0x2f8,s_FALSE_0049ee94);
        }
        else {
          sVar1 = thunk_FUN_0045c325();
          local_60 = (int)sVar1;
          thunk_FUN_004354a2(3,2,local_60,1,param_2 + -5,0xffffffff,0xffffffff);
        }
        break;
      case 7:
      case 8:
      case 9:
        thunk_FUN_004354a2(3,2,0,0,param_2 + -7,0xffffffff,0xffffffff);
        break;
      case 10:
        thunk_FUN_0042f755(DAT_005c37e4[0x5b],1);
        break;
      case 0xb:
        DAT_005c37e4[0x5c] = 0;
        thunk_FUN_0042f303(4);
        thunk_FUN_0046c3bc(s_BC_HallStkB_0049eeb8,2,0,0);
        thunk_FUN_0046c3bc(s_BC_HallStkC_0049eec4,2,0,0);
        thunk_FUN_0046c3bc(s_BC_HallStkM_0049eed0,2,0,0);
        break;
      case 0xc:
        DAT_005c37e4[0x5c] = 0;
        thunk_FUN_0042f303(5);
        thunk_FUN_0046c3bc(s_BC_HallStkB_0049eedc,2,0,0);
        thunk_FUN_0046c3bc(s_BC_HallStkC_0049eee8,2,0,0);
        thunk_FUN_0046c3bc(s_BC_HallStkM_0049eef4,2,0,0);
        break;
      case 0xd:
        DAT_005c37e4[0x5c] = 0;
        thunk_FUN_0042f303(7);
        thunk_FUN_0046c3bc(s_BC_HallStkB_0049ef00,2,0,0);
        thunk_FUN_0046c3bc(s_BC_HallStkC_0049ef0c,2,0,0);
        thunk_FUN_0046c3bc(s_BC_HallStkM_0049ef18,2,0,0);
        break;
      case 0xe:
        DAT_005c37e4[0x5c] = 0;
        thunk_FUN_0042f303(6);
        thunk_FUN_0046c3bc(s_BC_HallStkB_0049ef24,2,0,0);
        thunk_FUN_0046c3bc(s_BC_HallStkC_0049ef30,2,0,0);
        thunk_FUN_0046c3bc(s_BC_HallStkM_0049ef3c,2,0,0);
        break;
      case 0xf:
        local_7c = thunk_FUN_00450385();
        if (local_7c != 0) {
          _memset(&local_8c,0,0x10);
          local_8c = 1;
          local_88 = (undefined2)local_34;
          local_86 = *(undefined2 *)(local_38 + 8);
          local_82 = local_86;
          local_84 = thunk_FUN_0045035a();
          local_8a = (undefined2)DAT_0049f538;
          local_80 = local_84;
          thunk_FUN_00414081(1,&local_8c,0x10);
        }
        break;
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x13:
        _DAT_005c3804 = param_2;
        thunk_FUN_0043530b(param_2);
        break;
      case 0x14:
        _memset(&local_58,0,0x10);
        local_58 = 2;
        local_56 = (undefined2)DAT_0049f538;
        local_52 = *(undefined2 *)(local_38 + 8);
        local_54 = (undefined2)local_34;
        local_4e = local_52;
        local_50 = thunk_FUN_0045035a();
        local_4c = local_50;
        thunk_FUN_00414081(1,&local_58,0x10);
        break;
      case 0x15:
      case 0x16:
      case 0x17:
      case 0x18:
      case 0x19:
      case 0x1a:
      case 0x1b:
      case 0x1c:
        local_68 = thunk_FUN_00450070(local_38,param_2);
        local_64 = (int)(char)(&DAT_004a2898)[local_68];
        if (local_64 == 0) {
          _memset(&local_78,0,0x10);
          local_78 = 1;
          local_74 = (undefined2)local_34;
          local_72 = *(undefined2 *)(local_38 + 8);
          local_6e = local_72;
          local_70 = thunk_FUN_0045035a();
          local_76 = (undefined2)DAT_0049f538;
          local_6c = local_70;
          thunk_FUN_00414081(1,&local_78,0x10);
        }
        else {
          _DAT_005c3804 = local_34;
          thunk_FUN_0043530b(local_34);
        }
      }
      return;
    }
    switch(iVar3) {
    case 0x33:
      thunk_FUN_0042f303(0);
      DAT_0049e9c8 = 0xfffe;
      break;
    case 0x34:
    case 0x37:
    case 0x39:
    case 0x3a:
      local_14c = DAT_005c37e4[0x5b];
      if ((local_14c != 0) && (*(short *)(local_14c + 8) == DAT_0049f53c)) {
        local_150 = thunk_FUN_0045035a();
        _memset(&local_164,0,0x10);
        local_164 = 0;
        local_162 = (undefined2)DAT_0049f538;
        local_15a = DAT_0049f53c;
        local_15e = DAT_0049f53c;
        local_158 = local_150;
        local_148 = 5;
        local_154 = (short)param_2;
        if (param_1 == 0x39) {
          local_148 = 0xd;
          local_154 = *(short *)(local_14c + 0x24);
        }
        if ((param_1 == 0x3a) && (*(int *)(local_14c + 4) == 2)) {
          local_148 = 4;
          local_154 = 5;
        }
        local_160 = (undefined2)local_148;
        local_156 = local_154;
        thunk_FUN_00414081(1,&local_164,0x10);
      }
      break;
    case 0x35:
switchD_0042fa9a_caseD_35:
      thunk_FUN_0046c1b4(1,2,0);
      break;
    case 0x38:
      local_1e8[0] = param_2;
      local_1e0 = (int)DAT_0049f53c;
      local_1dc = DAT_0049f538;
      if (param_2 == 1) {
        local_1d8 = param_3;
      }
      thunk_FUN_00414081(2,local_1e8,0x18);
      break;
    case 0x3b:
switchD_0042fa9a_caseD_3b:
      _memset(&local_174,0,0x10);
      local_174 = 3;
      local_172 = (undefined2)DAT_0049f538;
      local_16a = DAT_0049f53c;
      local_16e = DAT_0049f53c;
      local_170 = 0;
      thunk_FUN_00414081(1,&local_174,0x10);
      break;
    case 0x3c:
      thunk_FUN_0046c3bc(s_IWConstructInfo_0049ede8,0x9a4,param_2,0);
      break;
    case 0x3d:
      thunk_FUN_0046c371(DAT_005c37e4[1],0x35,param_2,param_3);
      break;
    case 0x3f:
      DAT_005c37e4[0x5c] = (int)(&DAT_006137b8 + param_2 * 0x13);
      thunk_FUN_0042f8f7();
      break;
    case 0x40:
      if (((DAT_005c37e4[0x5b] != 0) || (DAT_0049e9c0 != -1)) || (DAT_0049e9c4 != -1)) {
        local_e4 = 0;
        local_e0 = &DAT_006191b8 + DAT_0049f538 * 0x14a0;
        if (*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) == 0) {
          _memset(&local_f4,0,0x10);
          local_f2 = (undefined2)DAT_0049f538;
          local_ea = (short)param_2;
          local_e8 = (short)param_3;
          local_dc = 1;
          if (DAT_0049e9c0 == -1) {
            if (DAT_0049e9c4 == -1) {
              local_f4 = 1;
              local_f0 = DAT_005c3804;
              local_ee = *(short *)(DAT_005c37e4[0x5b] + 8);
              local_ec = thunk_FUN_0045035a();
            }
            else {
              local_f4 = 0;
              local_f0 = 4;
              local_ee = DAT_0049f53c;
              local_e6 = DAT_0049e9c4;
              local_e4 = 1;
              local_f8 = &DAT_005ec640 + (short)param_3 * 0x60 + (short)param_2 * 0x29e8;
              if ((*(int *)(local_f8 + 4) == 0) &&
                 ((*(int *)(local_f8 + 0x10) != 0 || (*(int *)(local_f8 + 0x14) != -1)))) {
                local_dc = 0;
              }
              if ((DAT_004c2ba0 != 0) &&
                 ((DAT_0049e9c4 + -6) / 2 == (int)(short)(&DAT_005eebf8)[(short)param_2 * 0x14f4]))
              {
                local_fc = &DAT_005ec640 + (short)param_3 * 0x60 + (short)param_2 * 0x29e8;
                if (*(int *)(local_fc + 0x10) == 4) {
                  local_e8 = (short)param_3 + 1;
                  local_fc = local_fc + 0x60;
                }
                if ((*(int *)(local_fc + 4) == 3) &&
                   ((int)*(short *)(local_fc + 0x4a) != ((int)DAT_0049e9c4 - 6U & 1))) {
                  if (((int)DAT_0049e9c4 - 6U & 1) == 0) {
                    local_e8 = local_e8 + -1;
                  }
                  else {
                    local_e8 = local_e8 + 1;
                  }
                }
              }
            }
          }
          else {
            local_f4 = 3;
            local_f0 = 3;
            local_e6 = DAT_0049e9c0;
          }
          if (local_dc != 0) {
            thunk_FUN_00414081(1,&local_f4,0x10);
          }
          *(undefined2 *)((int)DAT_005c37e4 + 0x17e) = 0;
          thunk_FUN_0042dd47(0);
          DAT_0049e9c0 = -1;
          DAT_0049e9c4 = -1;
          if (local_e4 != 0) {
            thunk_FUN_0042fa0f(0x33,0,0,0);
          }
        }
        else {
          thunk_FUN_0042fa0f(0x49,0,0,0);
        }
      }
      break;
    case 0x41:
    case 0x4c:
      if (DAT_005c37e4[0x5b] != 0) {
        _memset(&local_10c,0,0x10);
        local_10c = 1;
        local_10a = (undefined2)DAT_0049f538;
        local_108 = DAT_005c3804;
        local_106 = *(undefined2 *)(DAT_005c37e4[0x5b] + 8);
        local_104 = thunk_FUN_0045035a();
        local_102 = DAT_0049f53c;
        local_100 = (short)param_2;
        thunk_FUN_00414081(1,&local_10c,0x10);
        *(undefined2 *)((int)DAT_005c37e4 + 0x17e) = 0;
        thunk_FUN_0042dd47(0);
      }
      break;
    case 0x42:
      DAT_0049e9c4 = (short)param_2;
      local_114 = -(uint)(param_2 != -1) & 0x11;
      thunk_FUN_0043530b(local_114);
      break;
    case 0x43:
      DAT_0049e9c0 = (short)param_2;
      local_110 = -(uint)(param_2 != -1) & 0x11;
      thunk_FUN_0043530b(local_110);
      break;
    case 0x44:
      if ((DAT_005c37e4[0x5b] == 0) || (param_2 != 0)) {
        thunk_FUN_0042f303(param_2);
      }
      else {
        thunk_FUN_0042f755(DAT_005c37e4[0x5b],1);
      }
      break;
    case 0x47:
      if (*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) != 0) {
        local_144 = (undefined *)0x0;
        if (param_2 != -1) {
          local_144 = &DAT_005ec640 + param_2 * 0x60 + DAT_0049f53c * 0x29e8;
        }
        thunk_FUN_0046c3bc(s_IWHallMove_0049f18c,14000,local_144,0);
        thunk_FUN_0046c3bc(s_IWMove_0049f198,14000,local_144,0);
      }
      break;
    case 0x48:
      if (*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) != 0) {
        thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049ef70,0x381,
                           s_ACTIVETRIBEPTR_>mbHaveGrabbed__F_0049ef48);
      }
      if (DAT_005c37e4 == (int *)0x0) {
        thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049ef9c,0x382,s_pIMIsleWindow_0049ef8c);
      }
      local_90 = &DAT_006191b8 + DAT_0049f538 * 0x14a0;
      iVar5 = (int)*(short *)(DAT_005c37e4[0x5b] + 8);
      uVar4 = 0xffffffff;
      iVar3 = iVar5;
      local_98 = iVar5;
      local_94 = iVar5;
      sVar1 = thunk_FUN_0045035a(0xffffffff,iVar5,iVar5);
      thunk_FUN_004354a2(3,5,0xffffffff,(int)sVar1,uVar4,iVar5,iVar3);
      thunk_FUN_0043530b(1);
      break;
    case 0x49:
      if (*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) != 1) {
        thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049efdc,0x394,
                           s_ACTIVETRIBEPTR_>mbHaveGrabbed__T_0049efb8);
      }
      if (DAT_005c37e4 == (int *)0x0) {
        thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049f008,0x395,s_pIMIsleWindow_0049eff8);
      }
      iVar5 = (int)*(short *)(DAT_005c37e4[0x5b] + 8);
      uVar4 = 0xffffffff;
      iVar3 = iVar5;
      local_a0 = iVar5;
      local_9c = iVar5;
      sVar1 = thunk_FUN_0045035a(0xffffffff,iVar5,iVar5);
      thunk_FUN_004354a2(3,6,0xffffffff,(int)sVar1,uVar4,iVar5,iVar3);
      thunk_FUN_0046c3bc(s_IWLocInfo_0049f024,0x350b,DAT_005c37e4[0x5b],0);
      thunk_FUN_0046c3bc(s_IWLocControl_0049f030,0x350b,DAT_005c37e4[0x5b],0);
      break;
    case 0x4a:
      if (*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) != 1) {
        thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049f064,0x3ae,
                           s_ACTIVETRIBEPTR_>mbHaveGrabbed__T_0049f040);
      }
      iVar3 = DAT_0049f538 * 0x14a0;
      local_a4 = &DAT_006191b8 + iVar3;
      thunk_FUN_004354a2(3,6,0xffffffff,(int)*(short *)(iVar3 + 0x61a574),0xffffffff,
                         (int)*(short *)(iVar3 + 0x61a572),(int)*(short *)(iVar3 + 0x61a572));
      DAT_005c37e4[0x5d] = 0;
      *(undefined2 *)(DAT_005c37e4 + 0x5e) = 0;
      *(undefined2 *)((int)DAT_005c37e4 + 0x17e) = 0;
      thunk_FUN_0042dd47(0);
      break;
    case 0x4b:
      if (*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) != 0) {
        thunk_FUN_0042fa0f(0x4a,0,0,0);
      }
      break;
    case 0x4d:
      DAT_0049f53c = (short)param_2;
      (**(code **)(*DAT_005c37ec + 4))(0x33,0,0);
      local_c = DAT_005c37e4[0x5b];
      (**(code **)(*DAT_005c37e4 + 4))(1,0,0);
      DAT_005c37e4[0x5b] = local_c;
      _DAT_005c37e8 = DAT_005c37e4[0x27];
    }
  }
  else {
    if (0xbbb < iVar3) {
      if (iVar3 < 0xfa4) {
        if (iVar3 == 0xfa3) {
          local_1a0 = thunk_FUN_0046c558(s_IWTasks_0049f234,3,0);
          if (local_1a0 == 0) {
            thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049f244,0x616,s_iwtasks_0049f23c);
          }
          local_19c = *(int **)(local_1a0 + 0xf4);
          if (local_19c == (int *)0x0) {
            return;
          }
          if (*local_19c == 0) {
            return;
          }
          _memset(&local_1b0,0,0x10);
          local_1b0 = 3;
          local_1ac = 0xc;
          local_1ae = (undefined2)local_19c[2];
          local_1a4 = (undefined2)((int)(local_19c + -0x1860ef) / 0x14);
          local_1aa = *(undefined2 *)((int)local_19c + 10);
          local_1a8 = (undefined2)local_19c[4];
          local_1a6 = *(undefined2 *)((int)local_19c + 0x12);
          thunk_FUN_00414081(1,&local_1b0,0x10);
          return;
        }
        if (iVar3 != 4000) {
          return;
        }
        local_188 = thunk_FUN_0046c558(s_IWTasks_0049f208,3,0);
        if (local_188 == 0) {
          thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049f218,0x5ff,s_iwtasks_0049f210);
        }
        local_184 = *(int **)(local_188 + 0xf4);
        if (local_184 == (int *)0x0) {
          return;
        }
        if (*local_184 == 0) {
          return;
        }
        _memset(&local_198,0,0x10);
        local_198 = 3;
        local_194 = (short)param_2 + 0xc;
        local_196 = (undefined2)local_184[2];
        local_18c = (undefined2)((int)(local_184 + -0x1860ef) / 0x14);
        local_192 = *(undefined2 *)((int)local_184 + 10);
        local_190 = (undefined2)local_184[4];
        local_18e = *(undefined2 *)((int)local_184 + 0x12);
        thunk_FUN_00414081(1,&local_198,0x10);
        return;
      }
      if (0x1773 < iVar3) {
        if (iVar3 < 0x1b59) {
          return;
        }
        if (0x1b5b < iVar3) {
          return;
        }
        DAT_005e16a8 = param_1 + -0x1b59;
        thunk_FUN_0046c3bc(s_CLIPBD1_0049f1a0,0xb,0,0);
        thunk_FUN_0046c3bc(s_CLIPBD2_0049f1a8,0xb,0,0);
        thunk_FUN_0046c3bc(s_CLIPBD3_0049f1b0,0xb,0,0);
        thunk_FUN_0046c3bc(s_CLIPSEL1_0049f1b8,0xb,0,0);
        thunk_FUN_0046c3bc(s_CLIPSEL2_0049f1c4,0xb,0,0);
        thunk_FUN_0046c3bc(s_CLIPSEL3_0049f1d0,0xb,0,0);
        return;
      }
      if (5999 < iVar3) {
        if (0x1771 < param_1) {
          thunk_FUN_0046c3bc(s_IWEffList_0049f2b8,param_1 + -2,param_2,param_3);
          return;
        }
        thunk_FUN_0046c3bc(s_IWSFXList_0049f2c4,(int)param_1,param_2,param_3);
        thunk_FUN_0046c3bc(s_IWTasks_0049f2d0,CONCAT22(extraout_var_00,param_1),param_2,param_3);
        return;
      }
      if (iVar3 != 0xfaa) {
        if (iVar3 != 0xfab) {
          return;
        }
        local_1bc = thunk_FUN_0046c558(s_IWTrade_0049f28c,3,0);
        if (local_1bc == 0) {
          thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049f29c,0x634,s_trader_0049f294);
        }
        for (local_1c0 = 0; local_1c0 < 3; local_1c0 = local_1c0 + 1) {
          local_1b8 = local_1c0;
          if (DAT_0049f538 <= local_1c0) {
            local_1b8 = local_1c0 + 1;
          }
          if (((*(short *)(local_1bc + 0x74 + local_1c0 * 2) != 0) ||
              (*(short *)(local_1bc + 0x7a + local_1c0 * 2) != 0)) ||
             (*(short *)(local_1bc + 0x80 + local_1c0 * 2) != 0)) {
            _memset(&local_1d0,0,0x10);
            local_1d0 = 3;
            local_1cc = 0xb;
            local_1ce = (undefined2)DAT_0049f538;
            local_1c4 = (undefined2)local_1b8;
            local_1ca = *(undefined2 *)(local_1bc + 0x74 + local_1c0 * 2);
            local_1c8 = *(undefined2 *)(local_1bc + 0x7a + local_1c0 * 2);
            local_1c6 = *(undefined2 *)(local_1bc + 0x80 + local_1c0 * 2);
            thunk_FUN_00414081(1,&local_1d0,0x10);
          }
        }
        _memset((void *)(local_1bc + 0x74),0,0x12);
        return;
      }
      local_1b4 = thunk_FUN_0046c558(s_IWTrade_0049f260,3,0);
      if (local_1b4 == 0) {
        thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049f270,0x62b,s_trader_0049f268);
      }
      _memset((void *)(local_1b4 + 0x74),0,0x12);
      return;
    }
    if (3000 < iVar3) {
      local_17c = param_1 + -0xbb9;
      local_178 = thunk_FUN_004381e1(local_17c);
      if (local_178 == 0) {
        return;
      }
      thunk_FUN_0042f303(0);
      local_180 = thunk_FUN_0045c3bb();
      if (DAT_005c37e4 == (int *)0x0) {
        thunk_FUN_00414b64(s_C__float_src_islemast_cpp_0049f1ec,0x5f4,s_pIMIsleWindow_0049f1dc);
      }
      DAT_005c37e4[0x5b] = local_180;
      thunk_FUN_0042f755(local_180,1);
      return;
    }
    switch(iVar3) {
    case 2000:
      goto switchD_0042fa9a_caseD_35;
    case 0x7d2:
      goto switchD_0042fa9a_caseD_3b;
    case 0x7d3:
      DAT_005c37f4 = (uint)(DAT_005c37f4 == 0);
      DAT_005c37f8 = (uint)(DAT_005c37f8 == 0);
      DAT_005c37fc = (uint)(DAT_005c37fc == 0);
      break;
    case 0x7d5:
      if (DAT_005c37f0 == 0) {
        thunk_FUN_0042f303(2);
      }
      else {
        thunk_FUN_0042f303(0);
      }
    }
  }
  return;
switchD_0042fa5b_caseD_4:
  thunk_FUN_004334ce(param_2,param_3);
  if (param_2 == 1) {
    if (&DAT_006137b8 + param_3 * 0x13 != (undefined4 *)DAT_005c37e4[0x5c]) {
      return;
    }
    DAT_005c37e4[0x5c] = 0;
    return;
  }
  local_28 = (int)param_3 >> 0x10;
  if (param_2 == 7) {
    local_30 = param_3 & 0xffff;
    local_2c = &DAT_005ec640 + local_30 * 0x60 + local_28 * 0x29e8;
    if (local_28 != DAT_0049f53c) {
      return;
    }
    thunk_FUN_00416a9a(7,local_2c);
    return;
  }
  if (param_2 != 8) {
    return;
  }
  local_24 = param_3 & 0xffff;
  local_20 = &DAT_005ec640 + local_24 * 0x60 + local_28 * 0x29e8;
  if (local_20 != (undefined *)DAT_005c37e4[0x5b]) {
    return;
  }
  local_1c = local_28;
  thunk_FUN_0042f303(0);
  return;
}
```

---


# 0012_batch_0008 — détails (5/8)

## FUN_004337d9 — 0x4337d9

- Classification : internal
- Corps : `0x4337d9–0x4351c9`
- État : pseudocode obtenu
- Evidence : `ev_0d862ab7ac54cca2b239537d84431bd5a758100fdc0d68f7cc958f8f31cdbdf6`
- Limites : Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again. Def-use links do not cross function boundaries and may omit memory aliasing, call side effects, or unresolved indirect flow. Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>. High p-code is decompiler-derived, not original source or runtime behavior. is_dead preserves the Java AST flag; decoded block members can retain that flag, so block_membership separately reports actual syntax-tree membership. Known omitted-edge counts cover links omitted from retained operations; omitted operations may contain additional uncounted links. Memory read/write effects include stack and temporary memory operations; they do not identify persistent state or business meaning. Operation, input, and def-use limits can truncate large functions; inspect truncation, omitted lower bounds, and known omitted counts before drawing conclusions. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Pseudocode is neither original source nor guaranteed to compile. References cover the complete Ghidra function-body AddressSet and exact entry. Dossier incoming edges omit sources owned by that function; procedure_references also retains those internal edges. Register variables, compiler-generated blocks, and pointer arithmetic remain decompiler artifacts. Resolved reference metadata identifies computed, indirect, external, call, jump, and data edges; unresolved targetless flows remain unknown, and function classifications distinguish thunks and externals. Synthetic Ghidra entry-point references without actionable memory sources are omitted. The Java bridge serializes one function request per Program and lets each decompilation run until it completes or the caller cancels. The Windows bridge uses authenticated IPv4 loopback because Node path-based IPC does not expose Java AF_UNIX sockets; the endpoint file contains no bearer token. The dossier combines Ghidra FunctionManager, Listing, ReferenceManager, BasicBlockModel, and decompiler observations; provider-specific pseudocode and assembly are not cross-provider text invariants. The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written. The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results. The target references PDB Float.pdb (GUID unknown, age (hex) 0, signature 3418386f, version NB10); Ghidra reports load state unknown. Original names and types may be missing; an empty name search does not prove a procedure is absent. Use list_procedures and address-based analysis to inspect recovered functions. REA does not admit a caller-selected PDB companion. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Types and calling conventions are Ghidra decompiler observations, not source declarations. Unresolved computed or indirect flows without target addresses are not represented as reference edges. Windows Ghidra P0 accepts native x86 and x86-64 PE applications and DLLs, and explicitly selected raw 6502 images; managed, hostile, sensitive, and mutable-path targets are unsupported. Windows sessions require the matching packaged Windows x64 native addon, local NTFS targets and runtimes, and Windows 10 or later. Native handles enforce path admission, private DACLs, and Job Object ownership automatically.

### Appels directs

- `0x401154` — `thunk_FUN_00414b91`
- `0x40115e` — `thunk_FUN_00450847`
- `0x40122b` — `thunk_FUN_00435538`
- `0x4012f8` — `thunk_FUN_00432f72`
- `0x401352` — `thunk_FUN_00432f4f`
- `0x401393` — `thunk_FUN_00433449`
- `0x4013a2` — `thunk_FUN_004354a2`
- `0x4013ca` — `thunk_FUN_0043338a`
- `0x40144c` — `thunk_FUN_0042cc24`
- `0x401456` — `thunk_FUN_00432b41`
- `0x40146f` — `thunk_FUN_0042d87c`
- `0x4014a6` — `thunk_FUN_0040f6f7`
- `0x4014ba` — `thunk_FUN_0042dd47`
- `0x4014e7` — `thunk_FUN_0045035a`
- `0x40150a` — `thunk_FUN_0040f9af`
- `0x40151e` — `thunk_FUN_004293c6`
- `0x4015a0` — `thunk_FUN_00432997`
- `0x4017f3` — `thunk_FUN_0040fb84`
- `0x401820` — `thunk_FUN_00433168`
- `0x401825` — `thunk_FUN_0040f73f`
- `0x401965` — `thunk_FUN_00452a15`
- `0x401a3c` — `thunk_FUN_00410510`
- `0x401b8b` — `thunk_FUN_0042fa0f`
- `0x401bf4` — `thunk_FUN_0042970c`
- `0x401c26` — `thunk_FUN_00432f1d`
- `0x401ce9` — `thunk_FUN_00433271`
- `0x401d02` — `thunk_FUN_0046cce7`
- `0x401d16` — `thunk_FUN_004204bc`
- `0x401d25` — `thunk_FUN_0040f966`
- `0x401d8e` — `thunk_FUN_004140dd`
- `0x401ded` — `thunk_FUN_0042d38a`
- `0x401eba` — `thunk_FUN_0040f752`
- `0x401ec4` — `thunk_FUN_004333f0`
- `0x401f46` — `thunk_FUN_0042dd3d`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401faa` — `thunk_FUN_0045f337`
- `0x402022` — `thunk_FUN_00406604`
- `0x40207c` — `thunk_FUN_00435ea7`
- `0x402144` — `thunk_FUN_00420f28`
- `0x4021da` — `thunk_FUN_00432e79`
- `0x4021ee` — `thunk_FUN_00435581`
- `0x402329` — `thunk_FUN_0042d28f`
- `0x40242d` — `thunk_FUN_00435826`
- `0x402491` — `thunk_FUN_0042dd0f`
- `0x472ca0` — `FUN_00472ca0`
- `0x4777a0` — `FUN_004777a0`

### Chaînes référencées

- `0x49f874` — "ACTIVEISLAND >= 0"
- `0x49f888` — "C:\\float\\src\\islewin.cpp"
- `0x49f8a4` — "data\\i%02d-feat.shp"
- `0x49f8b8` — "file.length() < ISLAND_FEATURE_SHAPE_SIZE"
- `0x49f8e4` — "C:\\float\\src\\islewin.cpp"
- `0x49f900` — "data\\island%02d.pal"
- `0x49f914` — "data\\game.pal"
- `0x49f924` — "status==0"
- `0x49f930` — "C:\\float\\src\\islewin.cpp"
- `0x49f94c` — "data\\island%02d.hzt"

### Pseudocode Ghidra

```c
undefined4 FUN_004337d9(short param_1,int param_2,uint param_3)

{
  undefined1 uVar1;
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  undefined4 uVar6;
  int in_ECX;
  uint uVar7;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar8;
  undefined4 uVar9;
  uint local_4f0;
  uint local_4ec;
  short local_4d4;
  int local_4d0;
  undefined2 *local_4cc;
  int local_4c8;
  uint local_4bc;
  undefined4 local_4b8;
  int local_4b4;
  int local_4b0;
  undefined4 local_4ac;
  uint local_4a8;
  uint local_4a4;
  undefined4 local_4a0;
  undefined *local_49c;
  undefined *local_498;
  int local_494;
  int local_490;
  int local_48c;
  int local_488;
  int local_484;
  int local_480;
  int local_47c;
  uint local_478;
  int local_368;
  undefined1 local_364 [768];
  undefined1 local_64 [48];
  int local_34;
  undefined1 local_30 [32];
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004916eb;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  switch(param_1) {
  case 1:
    *(undefined4 *)(in_ECX + 0x3c) = 1;
    *(undefined4 *)(in_ECX + 0x38) = 1;
    *(undefined4 *)(in_ECX + 0x34) = 1;
    if (DAT_0049f53c < 0) {
      thunk_FUN_00414b64(s_C__float_src_islewin_cpp_0049f888,0x2b3,s_ACTIVEISLAND_>__0_0049f874);
    }
    *(undefined1 **)(in_ECX + 0x9c) = &DAT_005ec218 + DAT_0049f53c * 0x29e8;
    DAT_005dc64c = in_ECX;
    if ((int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) <
        *(int *)(*(int *)(in_ECX + 0x9c) + 0x408 + DAT_0049f538 * 8)) {
      *(undefined2 *)(&DAT_005dbee0 + DAT_0049f53c * 2) =
           *(undefined2 *)(*(int *)(in_ECX + 0x9c) + 0x408 + DAT_0049f538 * 8);
    }
    if (*(int *)(*(int *)(in_ECX + 0x9c) + 0x40c + DAT_0049f538 * 8) + -0x27f <
        (int)*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2)) {
      *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) =
           (short)*(undefined4 *)(*(int *)(in_ECX + 0x9c) + 0x40c + DAT_0049f538 * 8) + -0x27f;
    }
    *(undefined2 *)(in_ECX + 0x70) = *(undefined2 *)(&DAT_005dbee0 + DAT_0049f53c * 2);
    *(undefined4 *)(in_ECX + 0x170) = 0;
    *(undefined4 *)(in_ECX + 0x16c) = 0;
    if (*(int *)(in_ECX + 0x88) == 0) {
      *(undefined **)(in_ECX + 0x88) = &DAT_004c2f48;
    }
    *(undefined4 *)(in_ECX + 0x8c) = 0x9ff;
    *(undefined4 *)(in_ECX + 0x90) = 0x13f;
    *(undefined4 *)(in_ECX + 0x94) = 0;
    *(undefined4 *)(in_ECX + 0x98) = 0;
    *(undefined4 *)(in_ECX + 0x78) = 0;
    *(undefined4 *)(in_ECX + 0x7c) = 0;
    *(undefined4 *)(in_ECX + 0x80) = 0x9ff;
    *(undefined4 *)(in_ECX + 0x84) = 0x13f;
    thunk_FUN_00432997();
    *(undefined4 *)(in_ECX + 0x168) = 1;
    thunk_FUN_0040f6f7();
    local_8 = 0;
    FUN_00472ca0(local_64,s_data_i_02d_feat_shp_0049f8a4,
                 (int)(short)(&DAT_005eebf8)[DAT_0049f53c * 0x14f4]);
    local_368 = thunk_FUN_0040f752(local_64,0x8000);
    if (local_368 == 0) {
      iVar5 = thunk_FUN_0040f9af();
      if (99999 < iVar5) {
        thunk_FUN_00414b64(s_C__float_src_islewin_cpp_0049f8e4,0x2dd,
                           s_file_length___<_ISLAND_FEATURE_S_0049f8b8);
      }
      thunk_FUN_0040fb84(&DAT_005c3840);
    }
    uVar6 = thunk_FUN_0042d28f();
    *(undefined4 *)(in_ECX + 8) = uVar6;
    uVar1 = thunk_FUN_0042dd0f(0);
    thunk_FUN_00406604(in_ECX + 8,uVar1);
    thunk_FUN_0042d38a();
    thunk_FUN_0042d87c(in_ECX + 8,1);
    thunk_FUN_0042cc24();
    FUN_00472ca0(local_30,s_data_island_02d_pal_0049f900,
                 (int)(short)(&DAT_005eebf8)[DAT_0049f53c * 0x14f4]);
    local_368 = thunk_FUN_0040f752(local_30,0x8000);
    if (local_368 != 0) {
      local_368 = thunk_FUN_0040f752(s_data_game_pal_0049f914,0x8000);
    }
    if (local_368 != 0) {
      thunk_FUN_00414b91(s_C__float_src_islewin_cpp_0049f930,0x2ef,s_status__0_0049f924,local_30);
    }
    thunk_FUN_0040fb84(local_364);
    thunk_FUN_0040f966();
    thunk_FUN_0046cce7(local_364);
    FUN_00472ca0(local_30,s_data_island_02d_hzt_0049f94c,
                 (int)(short)(&DAT_005eebf8)[DAT_0049f53c * 0x14f4]);
    thunk_FUN_00410510(local_30,local_364);
    for (local_34 = 0; local_34 < *(short *)(*(int *)(in_ECX + 0x9c) + 0x29a8);
        local_34 = local_34 + 1) {
      *(undefined2 *)(in_ECX + 0xa0 + local_34 * 2) = (undefined2)local_34;
    }
    FUN_004777a0(in_ECX + 0xa0,(int)*(short *)(*(int *)(in_ECX + 0x9c) + 0x29a8),2,&LAB_004019e7);
    local_8 = 0xffffffff;
    thunk_FUN_0040f73f();
    break;
  default:
    uVar6 = thunk_FUN_004293c6(CONCAT22((short)((uint)(param_1 + -1) >> 0x10),param_1),param_2,
                               param_3);
    goto LAB_004351b9;
  case 5:
    local_4ec = (uint)((param_3 & 0x100) != 0);
    local_4a4 = local_4ec;
    local_4f0 = (uint)((param_3 & 0x200) != 0);
    local_4a8 = local_4f0;
    switch(param_2) {
    case 0x20:
      if (((DAT_004c2b74 != 0) && (local_4f0 != 0)) && (*(int *)(in_ECX + 0x170) != 0)) {
        thunk_FUN_00435538(9,(*(int *)(in_ECX + 0x170) + -0x6137b8) / 0x4c,0,0,0);
      }
      break;
    case 0x25:
      if ((local_4ec == 0) || (DAT_004c2b74 == 0)) {
        if ((local_4f0 == 0) || (DAT_004c2b74 == 0)) {
          uVar2 = thunk_FUN_00435ea7(0xfffffe20);
          *(undefined2 *)(in_ECX + 0x70) = uVar2;
          *(undefined2 *)(in_ECX + 0x72) = 1000;
        }
        else if ((DAT_004befe0 == 0) && (*(int *)(in_ECX + 0x170) != 0)) {
          *(short *)(*(int *)(in_ECX + 0x170) + 0x10) =
               *(short *)(*(int *)(in_ECX + 0x170) + 0x10) + -10;
        }
      }
      else if ((DAT_004befe0 == 0) && (*(int *)(in_ECX + 0x170) != 0)) {
        *(uint *)(*(int *)(in_ECX + 0x170) + 0x1c) = *(uint *)(*(int *)(in_ECX + 0x170) + 0x1c) | 2;
      }
      break;
    case 0x26:
      if ((((DAT_004c2b74 != 0) && (DAT_004befe0 == 0)) && (local_4f0 != 0)) &&
         (*(int *)(in_ECX + 0x170) != 0)) {
        *(short *)(*(int *)(in_ECX + 0x170) + 0x12) =
             *(short *)(*(int *)(in_ECX + 0x170) + 0x12) + -10;
      }
      break;
    case 0x27:
      if ((local_4ec == 0) || (DAT_004c2b74 == 0)) {
        if ((local_4f0 == 0) || (DAT_004c2b74 == 0)) {
          uVar2 = thunk_FUN_00435ea7(0x1e0);
          *(undefined2 *)(in_ECX + 0x70) = uVar2;
          *(undefined2 *)(in_ECX + 0x72) = 1000;
        }
        else if ((DAT_004befe0 == 0) && (*(int *)(in_ECX + 0x170) != 0)) {
          *(short *)(*(int *)(in_ECX + 0x170) + 0x10) =
               *(short *)(*(int *)(in_ECX + 0x170) + 0x10) + 10;
        }
      }
      else if ((DAT_004befe0 == 0) && (*(int *)(in_ECX + 0x170) != 0)) {
        *(uint *)(*(int *)(in_ECX + 0x170) + 0x1c) =
             *(uint *)(*(int *)(in_ECX + 0x170) + 0x1c) & 0xfffffffd;
      }
      break;
    case 0x28:
      if (((DAT_004c2b74 != 0) && (DAT_004befe0 == 0)) &&
         ((local_4f0 != 0 && (*(int *)(in_ECX + 0x170) != 0)))) {
        *(short *)(*(int *)(in_ECX + 0x170) + 0x12) =
             *(short *)(*(int *)(in_ECX + 0x170) + 0x12) + 10;
      }
      break;
    case 0x31:
    case 0x32:
    case 0x33:
      local_4d4 = (short)param_2 + 0x1b28;
      thunk_FUN_0042fa0f(CONCAT22((short)((uint)(param_2 + -0x20) >> 0x10),local_4d4),0,0,0);
      break;
    case 0x41:
      if (DAT_004c2b74 != 0) {
        if (DAT_005dc670 == 0) {
          if (local_4ec == 0) {
            thunk_FUN_0042970c(0x3b,0,0);
          }
          else {
            thunk_FUN_00435538(0x11,DAT_0049f538,(int)DAT_0049f53c,0,0);
          }
        }
        else {
          DAT_005dc678 = (uint)(DAT_005dc678 == 0);
          local_4ac = 3;
          if (DAT_005dc678 != 0) {
            local_4ac = 2;
          }
          thunk_FUN_00432b41(local_4ac);
        }
      }
      break;
    case 0x42:
      if (DAT_004c2b74 != 0) {
        if (local_4ec == 0) {
          DAT_005dc680 = (uint)(DAT_005dc680 == 0);
          thunk_FUN_00432e79();
        }
        else {
          thunk_FUN_0042970c(0x38,0,0);
        }
      }
      break;
    case 0x43:
      if (DAT_004c2b74 != 0) {
        if (DAT_005dc670 == 0) {
          if (*(int *)(in_ECX + 0x170) == 0) {
            if (*(int *)(in_ECX + 0x16c) != 0) {
              if (local_4ec == 0) {
                uVar6 = 0;
                iVar5 = (int)DAT_0049f540;
                sVar3 = thunk_FUN_0045035a(iVar5,0);
                thunk_FUN_00435538(0xb,(int)*(short *)(*(int *)(in_ECX + 0x16c) + 8),(int)sVar3,
                                   iVar5,uVar6);
              }
              else {
                DAT_0049f540 = (short)((DAT_0049f540 + 1) % 5);
                thunk_FUN_00432b41(0xe);
              }
            }
          }
          else {
            local_4b0 = (*(int *)(in_ECX + 0x170) + -0x6137b8) / 0x4c;
            if (local_4ec == 0) {
              thunk_FUN_00435538(0x10,local_4b0,0,0,0);
            }
            else {
              thunk_FUN_00435538(0xf,local_4b0,0,0,0);
            }
          }
        }
        else {
          thunk_FUN_004333f0();
        }
      }
      break;
    case 0x44:
      if (DAT_004c2b74 != 0) {
        if (local_4ec == 0) {
          if (*(int *)(in_ECX + 0x170) == 0) {
            if (*(int *)(in_ECX + 0x16c) != 0) {
              thunk_FUN_00450847(5);
            }
          }
          else {
            thunk_FUN_004204bc(5,0xffffffff);
          }
        }
        else {
          DAT_005dc648 = (uint)(DAT_005dc648 == 0);
        }
      }
      break;
    case 0x45:
      if (DAT_004c2b74 != 0) {
        if (local_4ec == 0) {
          if (*(int *)(in_ECX + 0x170) == 0) {
            if (*(int *)(in_ECX + 0x16c) == 0) {
              if (DAT_005dc670 != 0) {
                DAT_005dc654 = DAT_005dc654 ^ 1;
                thunk_FUN_00432997();
                thunk_FUN_00432e79();
              }
            }
            else {
              uVar9 = 0;
              uVar6 = 0;
              sVar3 = thunk_FUN_0045035a(0,0);
              thunk_FUN_00435538(3,(int)*(short *)(*(int *)(in_ECX + 0x16c) + 8),(int)sVar3,uVar6,
                                 uVar9);
            }
          }
          else {
            local_4b4 = (*(int *)(in_ECX + 0x170) + -0x6137b8) / 0x4c;
            thunk_FUN_00435538(2,local_4b4,0,0,0);
          }
        }
        else {
          DAT_005dc670 = (uint)(DAT_005dc670 == 0);
          if (DAT_005dc670 == 0) {
            thunk_FUN_00432f4f();
          }
          else {
            thunk_FUN_00432f1d();
          }
        }
      }
      break;
    case 0x46:
      if (DAT_004c2b74 != 0) {
        if (local_4ec == 0) {
          if (*(int *)(in_ECX + 0x16c) != 0) {
            uVar8 = 0xffffffff;
            uVar9 = 0xffffffff;
            uVar6 = 0;
            sVar3 = thunk_FUN_0045035a(0,0xffffffff,0xffffffff);
            thunk_FUN_004354a2(0,0x12,0,(int)sVar3,uVar6,uVar9,uVar8);
          }
        }
        else {
          DAT_005dc66c = DAT_005dc66c ^ 1;
        }
      }
      break;
    case 0x47:
      if (((DAT_004c2b74 != 0) && (local_4ec != 0)) && (*(int *)(in_ECX + 0x16c) != 0)) {
        uVar6 = 0;
        sVar3 = thunk_FUN_0045035a(0);
        thunk_FUN_00435538(0x12,DAT_0049f538,(int)DAT_0049f53c,(int)sVar3,uVar6);
      }
      break;
    case 0x48:
      if (((DAT_004c2b74 != 0) && (DAT_005dc670 != 0)) && (local_4ec != 0)) {
        thunk_FUN_00432b41(4);
      }
      break;
    case 0x4a:
      if ((DAT_004c2b74 != 0) && (*(int *)(in_ECX + 0x16c) != 0)) {
        local_4b8 = 5;
        if (*(int *)(*(int *)(in_ECX + 0x16c) + 0x10) == 0) {
          local_4b8 = 6;
        }
        uVar8 = 0xffffffff;
        uVar9 = 0xffffffff;
        uVar6 = 0xffffffff;
        sVar3 = thunk_FUN_0045035a(0xffffffff,0xffffffff,0xffffffff);
        thunk_FUN_004354a2(3,local_4b8,0xffffffff,(int)sVar3,uVar6,uVar9,uVar8);
      }
      break;
    case 0x4b:
      if ((DAT_004c2b74 != 0) && (*(int *)(in_ECX + 0x16c) != 0)) {
        uVar8 = 0xffffffff;
        uVar9 = 0xffffffff;
        uVar6 = 0;
        sVar3 = thunk_FUN_0045035a(0,0xffffffff,0xffffffff);
        thunk_FUN_004354a2(3,1,0,(int)sVar3,uVar6,uVar9,uVar8);
      }
      break;
    case 0x4c:
      if (DAT_004c2b74 != 0) {
        if (local_4ec == 0) {
          DAT_005dc660 = (uint)(DAT_005dc660 == 0);
          thunk_FUN_00432b41(DAT_005dc660 + 0xc);
        }
        else if (DAT_005dc670 == 0) {
          DAT_005dc664 = DAT_005dc664 ^ 1;
        }
        else {
          thunk_FUN_00433168();
        }
      }
      break;
    case 0x4d:
      if (DAT_005dc670 == 0) {
        thunk_FUN_0042970c(0x35,0,0);
      }
      else {
        DAT_005dc67c = DAT_005dc67c ^ 1;
      }
      break;
    case 0x4e:
      if (DAT_004c2b74 != 0) {
        DAT_005dc65c = DAT_005dc65c ^ 1;
      }
      break;
    case 0x4f:
      if (DAT_004c2b74 != 0) {
        if (local_4ec == 0) {
          if (*(int *)(in_ECX + 0x16c) != 0) {
            uVar9 = 0;
            uVar6 = 0;
            sVar3 = thunk_FUN_0045035a(0,0);
            thunk_FUN_00435538(0xc,(int)DAT_0049f53c,(int)sVar3,uVar6,uVar9);
          }
        }
        else {
          thunk_FUN_00435538(4,(int)DAT_0049f53c,0,0,0);
        }
      }
      break;
    case 0x50:
      if (DAT_004c2b74 != 0) {
        if (local_4ec == 0) {
          if (*(int *)(in_ECX + 0x16c) != 0) {
            uVar6 = 0;
            sVar3 = thunk_FUN_0045035a(0);
            thunk_FUN_00435538(10,DAT_0049f538,(int)DAT_0049f53c,(int)sVar3,uVar6);
          }
        }
        else {
          local_4bc = (uint)(DAT_004bf124 == 0);
          thunk_FUN_004140dd(10,&local_4bc,4,0);
        }
      }
      break;
    case 0x51:
      if (DAT_004c2b74 != 0) {
        thunk_FUN_0042fa0f(0x44,8,0,*(undefined4 *)(in_ECX + 4));
      }
      break;
    case 0x52:
      if (DAT_004c2b74 != 0) {
        if (local_4ec == 0) {
          if (DAT_005dc670 == 0) {
            if (*(int *)(in_ECX + 0x170) == 0) {
              if (*(int *)(in_ECX + 0x16c) != 0) {
                uVar9 = 0;
                uVar6 = 0;
                sVar3 = thunk_FUN_0045035a(0,0);
                thunk_FUN_00435538(7,(int)DAT_0049f53c,(int)sVar3,uVar6,uVar9);
              }
            }
            else {
              thunk_FUN_00435538(6,(*(int *)(in_ECX + 0x170) + -0x6137b8) / 0x4c,0,0,0);
              *(undefined4 *)(in_ECX + 0x170) = 0;
            }
          }
          else {
            thunk_FUN_00433449();
          }
        }
        else {
          thunk_FUN_00435538(5,DAT_0049f538,(int)DAT_0049f53c,0,0);
        }
      }
      break;
    case 0x53:
      if (((DAT_004c2b74 != 0) && (DAT_005dc670 != 0)) && (local_4ec != 0)) {
        thunk_FUN_00432f72();
      }
      break;
    case 0x54:
      if (DAT_004c2b74 != 0) {
        if (local_4ec == 0) {
          if (local_4f0 == 0) {
            DAT_005dc650 = DAT_005dc650 ^ 1;
            if (DAT_005dc650 == 0) {
              thunk_FUN_00432b41(8);
            }
            else {
              thunk_FUN_00432b41(7);
            }
          }
          else {
            thunk_FUN_00435538(0xe,DAT_0049f538,0,0,0);
          }
        }
        else {
          DAT_005dc658 = DAT_005dc658 ^ 1;
        }
      }
      break;
    case 0x55:
      if ((DAT_004c2b74 != 0) && (*(int *)(in_ECX + 0x16c) != 0)) {
        sVar3 = thunk_FUN_0045035a();
        if (*(int *)(*(int *)(in_ECX + 0x16c) + 4) == 0) {
          thunk_FUN_004354a2(1,2,(int)sVar3,0xffffffff,0xffffffff,0xffffffff,0xffffffff);
        }
        else if (*(int *)(*(int *)(in_ECX + 0x16c) + 4) == 2) {
          thunk_FUN_004354a2(0,0x11,(int)sVar3,(int)sVar3,
                             (int)*(short *)(*(int *)(in_ECX + 0x16c) + 0x36),0xffffffff,0xffffffff)
          ;
        }
      }
      break;
    case 0x56:
      if (DAT_004c2b74 != 0) {
        if ((local_4ec == 0) || (local_4f0 != 0)) {
          if (local_4f0 != 0) {
            uVar7 = (uint)DAT_006136b0;
            local_4cc = &DAT_005e9c58 + uVar7 * 0x14f4;
            for (local_4c8 = 0; local_4c8 < (short)(&DAT_005ec1d8)[uVar7 * 0x14f4];
                local_4c8 = local_4c8 + 1) {
              if ((0x16 < *(int *)(local_4cc + 8)) && (*(int *)(local_4cc + 8) < 0x25)) {
                if (local_4a4 == 0) {
                  thunk_FUN_00450847(30000);
                }
                else {
                  thunk_FUN_00452a15();
                }
              }
              local_4cc = local_4cc + 0x30;
            }
          }
        }
        else {
          thunk_FUN_00435538(0xd,0,0,0,0);
        }
      }
      break;
    case 0x58:
      if ((DAT_004c2b74 != 0) && (*(int *)(in_ECX + 0x170) != 0)) {
        thunk_FUN_00435538(8,(*(int *)(in_ECX + 0x170) + -0x6137b8) / 0x4c,0,0,0);
      }
      break;
    case 0x59:
      if ((DAT_004c2b74 != 0) && (local_4ec != 0)) {
        thunk_FUN_00435538(0x13,DAT_0049f538,0,0,0);
      }
      break;
    case 0x5a:
      if ((DAT_004c2b74 != 0) && (local_4ec != 0)) {
        thunk_FUN_00435538(0x13,DAT_0049f538,0,0,0);
        for (local_4d0 = 0; local_4d0 < (int)(uint)DAT_006136b0; local_4d0 = local_4d0 + 1) {
          thunk_FUN_00435538(0x11,DAT_0049f538,local_4d0,0,0);
        }
      }
      break;
    case 0x6a:
      if (DAT_004c2b74 != 0) {
        DAT_005dc644 = DAT_005dc644 + 1;
        if (0x10 < DAT_005dc644) {
          DAT_005dc644 = 0;
        }
        thunk_FUN_0042dd47((int)DAT_005dc644);
      }
      break;
    case 0x6b:
      if (((DAT_004c2b74 != 0) && (DAT_004befe0 == 0)) &&
         ((*(int *)(in_ECX + 0x170) != 0 &&
          (sVar3 = *(short *)(*(int *)(in_ECX + 0x170) + 0x20), sVar4 = thunk_FUN_00420f28(),
          sVar3 < sVar4)))) {
        *(short *)(*(int *)(in_ECX + 0x170) + 0x20) =
             *(short *)(*(int *)(in_ECX + 0x170) + 0x20) + 1;
      }
      break;
    case 0x6d:
      if ((((DAT_004c2b74 != 0) && (DAT_004befe0 == 0)) && (*(int *)(in_ECX + 0x170) != 0)) &&
         (0 < *(short *)(*(int *)(in_ECX + 0x170) + 0x20))) {
        *(short *)(*(int *)(in_ECX + 0x170) + 0x20) =
             *(short *)(*(int *)(in_ECX + 0x170) + 0x20) + -1;
      }
      break;
    case 0x6f:
      if (DAT_004c2b74 != 0) {
        DAT_005dc644 = DAT_005dc644 + -1;
        if (DAT_005dc644 < 0) {
          DAT_005dc644 = 0x10;
        }
        thunk_FUN_0042dd47((int)DAT_005dc644);
      }
    }
    break;
  case 6:
  case 7:
    if (*(int *)(in_ECX + 4) == DAT_0062c6bc) {
      if (DAT_005dc670 == 0) {
        if (DAT_005dc660 == 0) {
          iVar5 = thunk_FUN_00435826(param_2,param_3,param_1 == 7);
          if (iVar5 == 0) {
            uVar6 = thunk_FUN_004293c6(param_1,param_2,param_3);
          }
          else {
            uVar6 = 1;
          }
          goto LAB_004351b9;
        }
        local_4a0 = 0;
        if (DAT_0049f540 == 4) {
          local_4a0 = 0xb;
        }
        thunk_FUN_00435538(0x14,(int)DAT_0049f540,
                           param_2 + *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2),param_3,local_4a0)
        ;
      }
      else if (DAT_005dc678 == 0) {
        thunk_FUN_00433271(*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) + param_2,param_3);
      }
      else {
        thunk_FUN_0043338a(*(short *)(&DAT_005dbee0 + DAT_0049f53c * 2) + param_2,param_3);
      }
    }
    break;
  case 8:
    local_478 = -(uint)(DAT_00630a8c != 0) & 2;
    thunk_FUN_0042dd47(local_478);
    break;
  case 9:
    thunk_FUN_0042dd47((int)*(short *)(in_ECX + 0x17e));
    break;
  case 10:
    if (param_2 == 0) {
      uVar2 = thunk_FUN_00435ea7(0xffffff88);
      *(undefined2 *)(in_ECX + 0x70) = uVar2;
    }
    else if (param_2 == 0x27f) {
      uVar2 = thunk_FUN_00435ea7(0x78);
      *(undefined2 *)(in_ECX + 0x70) = uVar2;
    }
    else {
      local_484 = (int)*(short *)(in_ECX + 0x17a);
      local_488 = (int)*(short *)(in_ECX + 0x17c);
      local_480 = 0;
      thunk_FUN_00435581(param_2,param_3,&local_480,&local_48c);
      *(undefined2 *)(in_ECX + 0x17a) = 0xffff;
      *(undefined2 *)(in_ECX + 0x17c) = 0xffff;
      if (DAT_00630a8c == 0) {
        local_490 = thunk_FUN_0042dd3d();
        local_494 = local_490;
        if (local_480 == 1) {
          local_498 = &DAT_005ec640 + local_48c * 0x60 + DAT_0049f53c * 0x29e8;
          if (*(short *)(in_ECX + 0x178) == 1) {
            if (*(int *)(DAT_0049f538 * 0x14a0 + 0x61a578) == 0) {
              local_494 = *(short *)(in_ECX + 0x17e) + 1;
            }
            else {
              local_49c = &DAT_005ec640 +
                          *(short *)(DAT_0049f538 * 0x14a0 + 0x61a574) * 0x60 +
                          *(short *)(DAT_0049f538 * 0x14a0 + 0x61a572) * 0x29e8;
              iVar5 = thunk_FUN_0045f337(local_49c,local_498);
              if (iVar5 != 0) {
                local_494 = *(short *)(in_ECX + 0x17e) + 1;
              }
            }
          }
          else if (*(short *)(in_ECX + 0x178) == 0) {
            local_494 = 1;
          }
          *(undefined2 *)(in_ECX + 0x17a) = (undefined2)local_48c;
        }
        else if (local_480 == 2) {
          if (*(short *)(in_ECX + 0x178) == 2) {
            local_494 = *(short *)(in_ECX + 0x17e) + 1;
          }
          else if (*(short *)(in_ECX + 0x178) == 0) {
            local_494 = 1;
          }
          *(undefined2 *)(in_ECX + 0x17c) = (undefined2)local_48c;
        }
        else if ((*(short *)(in_ECX + 0x17c) != local_488) ||
                (*(short *)(in_ECX + 0x17a) != local_484)) {
          if (*(int *)(in_ECX + 0x174) == 0) {
            *(undefined2 *)(in_ECX + 0x17e) = 0;
          }
          local_494 = (int)*(short *)(in_ECX + 0x17e);
        }
        if (local_494 != local_490) {
          thunk_FUN_0042dd47(local_494);
        }
      }
      if (*(short *)(in_ECX + 0x17a) != local_484) {
        thunk_FUN_0042970c(0x47,(int)*(short *)(in_ECX + 0x17a),0);
      }
    }
    break;
  case 0xb:
    *(undefined4 *)(in_ECX + 0x34) = 1;
    *(undefined4 *)(in_ECX + 0x168) = 1;
    break;
  case 0x32:
    *(undefined2 *)(in_ECX + 0x72) = 0xfffb;
    break;
  case 0x33:
    *(undefined2 *)(in_ECX + 0x72) = 5;
    break;
  case 0x34:
    *(undefined2 *)(in_ECX + 0x72) = 0;
    break;
  case 0x35:
    local_47c = (param_2 * 0x781) / 1000;
    uVar2 = thunk_FUN_00435ea7(local_47c - *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2));
    *(undefined2 *)(in_ECX + 0x70) = uVar2;
    if (param_3 == 1) {
      *(undefined2 *)(in_ECX + 0x72) = 1000;
    }
  }
  uVar6 = 0;
LAB_004351b9:
  *unaff_FS_OFFSET = local_10;
  return uVar6;
}
```

---

## FUN_0043530b — 0x43530b

- Classification : internal
- Corps : `0x43530b–0x4354a1`
- État : pseudocode obtenu
- Evidence : `ev_b65156eb13978511b7f06cdb3fee86e7c2c4a37bf3cac67ad0f0badb2f999a68`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40224d` — `thunk_FUN_00450070`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0043530b(int param_1)

{
  int iVar1;
  int in_ECX;
  
  *(int *)(in_ECX + 0x174) = param_1;
  *(undefined2 *)(in_ECX + 0x178) = 0;
  if (param_1 == 1) {
    *(undefined2 *)(in_ECX + 0x178) = 1;
    *(undefined2 *)(in_ECX + 0x17e) = 9;
  }
  if (param_1 == 0x11) {
    *(undefined2 *)(in_ECX + 0x178) = 1;
    *(undefined2 *)(in_ECX + 0x17e) = 0xd;
    if ((DAT_0049e9c0 != -1) || (DAT_0049e9c4 != -1)) {
      *(undefined2 *)(in_ECX + 0x17e) = 0xb;
    }
  }
  else if (param_1 == 0x13) {
    *(undefined2 *)(in_ECX + 0x178) = 4;
    *(undefined2 *)(in_ECX + 0x17e) = 0xf;
  }
  else if (param_1 == 0x10) {
    *(undefined2 *)(in_ECX + 0x178) = 2;
    *(undefined2 *)(in_ECX + 0x17e) = 3;
  }
  else if (param_1 == 0x12) {
    *(undefined2 *)(in_ECX + 0x178) = 2;
    *(undefined2 *)(in_ECX + 0x17e) = 5;
  }
  else if (((0x14 < param_1) && (param_1 < 0x1d)) && (*(int *)(in_ECX + 0x16c) != 0)) {
    iVar1 = thunk_FUN_00450070(*(undefined4 *)(in_ECX + 0x16c),param_1);
    *(short *)(in_ECX + 0x178) = (short)(char)(&DAT_004a2898)[iVar1];
    if ((*(short *)(in_ECX + 0x178) == 1) || (*(short *)(in_ECX + 0x178) == 4)) {
      *(undefined2 *)(in_ECX + 0x17e) = 0xb;
    }
    else if (*(short *)(in_ECX + 0x178) == 2) {
      *(undefined2 *)(in_ECX + 0x17e) = 7;
    }
  }
  return;
}
```

---

## FUN_004354a2 — 0x4354a2

- Classification : internal
- Corps : `0x4354a2–0x435537`
- État : pseudocode obtenu
- Evidence : `ev_b2285cf0e0e4766d4326255d4e7442bd644268872da28f1a18140867b9945798`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40228e` — `thunk_FUN_00414081`
- `0x474b20` — `_memset`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004354a2(undefined2 param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
                 undefined2 param_5,int param_6,int param_7)

{
  undefined2 local_14;
  undefined2 local_12;
  undefined2 local_10;
  undefined2 local_e;
  undefined2 local_c;
  undefined2 local_a;
  undefined2 local_8;
  undefined2 local_6;
  
  _memset(&local_14,0,0x10);
  local_14 = param_1;
  local_12 = (undefined2)DAT_0049f538;
  local_10 = param_2;
  local_e = (undefined2)param_6;
  if (param_6 == -1) {
    local_e = DAT_0049f53c;
  }
  local_a = (undefined2)param_7;
  if (param_7 == -1) {
    local_a = DAT_0049f53c;
  }
  local_c = param_3;
  local_8 = param_4;
  local_6 = param_5;
  thunk_FUN_00414081(1,&local_14,0x10);
  return;
}
```

---

## FUN_00435538 — 0x435538

- Classification : internal
- Corps : `0x435538–0x435580`
- État : pseudocode obtenu
- Evidence : `ev_804d4e9d826e6b0634ab0f56a1d5fbe497a086d78e2c2f128b0dfdb02987a467`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40228e` — `thunk_FUN_00414081`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00435538(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_1c = param_1;
  local_18 = (int)DAT_0049f53c;
  local_14 = param_2;
  local_10 = param_3;
  local_c = param_4;
  local_8 = param_5;
  thunk_FUN_00414081(2,&local_1c,0x18);
  return;
}
```

---

## FUN_00435581 — 0x435581

- Classification : internal
- Corps : `0x435581–0x435825`
- État : pseudocode obtenu
- Evidence : `ev_348f5497af7071783e238a442881827d9f24b812a0a6f4663070125e1d452240`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40173a` — `thunk_FUN_004672a6`
- `0x40186b` — `thunk_FUN_004656d6`
- `0x401d11` — `thunk_FUN_00456a87`
- `0x4021ad` — `thunk_FUN_004641de`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00435581(int param_1,int param_2,int *param_3,int *param_4)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int *piVar4;
  int in_ECX;
  int iVar5;
  undefined2 extraout_var;
  int local_44;
  int local_2c;
  int local_24;
  short *local_20;
  short local_1c;
  short local_14;
  
  param_1 = param_1 + *(short *)(&DAT_005dbee0 + DAT_0049f53c * 2);
  if ((*param_3 == 0) || (*param_3 == 2)) {
    iVar3 = thunk_FUN_004656d6((int)DAT_0049f53c,0xfffffffe);
    for (local_14 = 0; local_14 < iVar3; local_14 = local_14 + 1) {
      iVar5 = (short)(&DAT_00618fb4)[local_14] * 0x4c;
      if (((*(uint *)(&DAT_006137d4 + iVar5) & 1) == 0) &&
         (iVar5 = thunk_FUN_004672a6(param_1,param_2,(int)*(short *)(&DAT_006137c8 + iVar5),
                                     (int)*(short *)(&DAT_006137ca + iVar5)), iVar5 < 0x14)) {
        *param_3 = 2;
        *param_4 = (int)(short)(&DAT_00618fb4)[local_14];
        return;
      }
    }
  }
  if ((*param_3 == 0) || (*param_3 == 1)) {
    local_20 = (short *)(*(int *)(in_ECX + 0x9c) + 0x428);
    for (local_1c = 0; local_1c < *(short *)(*(int *)(in_ECX + 0x9c) + 0x29a8);
        local_1c = local_1c + 1) {
      if (param_1 - *local_20 < 0) {
        local_44 = -(param_1 - *local_20);
      }
      else {
        local_44 = param_1 - *local_20;
      }
      sVar1 = local_20[1];
      if ((local_44 < 0x65) &&
         (((*(int *)(local_20 + 2) != 0 ||
           (((int)(char)local_20[0x11] & 1 << ((byte)DAT_0049f538 & 0x1f)) != 0)) ||
          (*(int *)(local_20 + 8) != 0)))) {
        sVar2 = DAT_0049f564;
        if (*(int *)(local_20 + 2) == 0) {
          sVar2 = *(short *)(&DAT_0049f560 + *(int *)(local_20 + 6) * 2);
        }
        local_2c = (int)sVar2;
        local_24 = 0;
        if (*(int *)(local_20 + 8) != 0) {
          piVar4 = (int *)thunk_FUN_004641de(*(undefined4 *)(local_20 + 10),
                                             *(undefined4 *)(local_20 + 8));
          iVar3 = thunk_FUN_00456a87(CONCAT22(extraout_var,*(undefined2 *)((int)piVar4 + 0x16)));
          if (iVar3 != 0) {
            local_24 = -(uint)*(byte *)(iVar3 + 2);
          }
          if (*(int *)(local_20 + 2) == 0) {
            local_2c = (int)*(short *)(&DAT_0049f560 + *piVar4 * 2);
          }
        }
        iVar3 = local_2c / 2;
        if (-iVar3 < local_24) {
          local_24 = -iVar3;
        }
        if (((local_44 < local_2c) && (local_24 < param_2 - sVar1)) && (param_2 - sVar1 < iVar3)) {
          *param_3 = 1;
          *param_4 = (int)local_1c;
          return;
        }
      }
      local_20 = local_20 + 0x30;
    }
  }
  *param_3 = 0;
  return;
}
```

---


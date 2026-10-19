# 0015_batch_0011 — détails (2/3)

## FUN_00450a71 — 0x450a71

- Classification : internal
- Corps : `0x450a71–0x4525f2`
- État : pseudocode obtenu
- Evidence : `ev_2c01d69c5cc4626ed22aa4e310f991bfd5bbd1180eefe950c3ecf47a1b8658eb`
- Limites : Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again. Def-use links do not cross function boundaries and may omit memory aliasing, call side effects, or unresolved indirect flow. Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>. High p-code is decompiler-derived, not original source or runtime behavior. is_dead preserves the Java AST flag; decoded block members can retain that flag, so block_membership separately reports actual syntax-tree membership. Known omitted-edge counts cover links omitted from retained operations; omitted operations may contain additional uncounted links. Memory read/write effects include stack and temporary memory operations; they do not identify persistent state or business meaning. Operation, input, and def-use limits can truncate large functions; inspect truncation, omitted lower bounds, and known omitted counts before drawing conclusions. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Pseudocode is neither original source nor guaranteed to compile. References cover the complete Ghidra function-body AddressSet and exact entry. Dossier incoming edges omit sources owned by that function; procedure_references also retains those internal edges. Register variables, compiler-generated blocks, and pointer arithmetic remain decompiler artifacts. Resolved reference metadata identifies computed, indirect, external, call, jump, and data edges; unresolved targetless flows remain unknown, and function classifications distinguish thunks and externals. Synthetic Ghidra entry-point references without actionable memory sources are omitted. The Java bridge serializes one function request per Program and lets each decompilation run until it completes or the caller cancels. The Windows bridge uses authenticated IPv4 loopback because Node path-based IPC does not expose Java AF_UNIX sockets; the endpoint file contains no bearer token. The dossier combines Ghidra FunctionManager, Listing, ReferenceManager, BasicBlockModel, and decompiler observations; provider-specific pseudocode and assembly are not cross-provider text invariants. The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written. The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results. The target references PDB Float.pdb (GUID unknown, age (hex) 0, signature 3418386f, version NB10); Ghidra reports load state unknown. Original names and types may be missing; an empty name search does not prove a procedure is absent. Use list_procedures and address-based analysis to inspect recovered functions. REA does not admit a caller-selected PDB companion. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Types and calling conventions are Ghidra decompiler observations, not source declarations. Unresolved computed or indirect flows without target addresses are not represented as reference edges. Windows Ghidra P0 accepts native x86 and x86-64 PE applications and DLLs, and explicitly selected raw 6502 images; managed, hostile, sensitive, and mutable-path targets are unsupported. Windows sessions require the matching packaged Windows x64 native addon, local NTFS targets and runtimes, and Windows 10 or later. Native handles enforce path admission, private DACLs, and Job Object ownership automatically.

### Appels directs

- `0x4010d7` — `thunk_FUN_0042003c`
- `0x401113` — `thunk_FUN_004669bd`
- `0x4011b8` — `thunk_FUN_004535e4`
- `0x401370` — `thunk_FUN_00456b0d`
- `0x40143d` — `thunk_FUN_0045388f`
- `0x401479` — `thunk_FUN_00452ae7`
- `0x4014a1` — `thunk_FUN_00456aca`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x4014e7` — `thunk_FUN_0045035a`
- `0x40156e` — `thunk_FUN_0041ff8b`
- `0x4015aa` — `thunk_FUN_004533a8`
- `0x4016e0` — `thunk_FUN_00420635`
- `0x40186b` — `thunk_FUN_004656d6`
- `0x40188e` — `thunk_FUN_00416342`
- `0x401924` — `thunk_FUN_00453a5f`
- `0x401965` — `thunk_FUN_00452a15`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x4019b5` — `thunk_FUN_0046562b`
- `0x401aeb` — `thunk_FUN_00452fcb`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401f69` — `thunk_FUN_004532e2`
- `0x402144` — `thunk_FUN_00420f28`
- `0x4021ad` — `thunk_FUN_004641de`
- `0x40222f` — `thunk_FUN_0045cd75`
- `0x402248` — `thunk_FUN_00456b8d`
- `0x4022e3` — `thunk_FUN_00452859`
- `0x4024c3` — `thunk_FUN_00456bd0`
- `0x402509` — `thunk_FUN_00456b4d`

### Chaînes référencées

- `0x4a29e0` — "mStaffBld!=-1"
- `0x4a29f0` — "C:\\float\\src\\pad.cpp"
- `0x4a2a0c` — "C:\\float\\src\\pad.cpp"

### Pseudocode Ghidra

```c
/* WARNING: Restarted to delay deadcode elimination for space: stack */

int * FUN_00450a71(void)

{
  uint uVar1;
  bool bVar2;
  short sVar3;
  undefined2 uVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  int *in_ECX;
  int *piVar9;
  undefined4 local_140;
  int *local_12c;
  int local_118;
  int *local_114;
  short asStack_110 [6];
  int *local_104;
  uint local_100;
  int local_fc;
  int local_f8;
  int *local_f4;
  int *local_f0;
  int local_ec;
  int *local_e8;
  int *local_e4;
  undefined4 *local_dc;
  int local_d8;
  uint local_d4;
  int local_d0;
  int local_cc;
  int local_c8;
  int local_c4;
  int local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  int *local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  short local_9c;
  int local_98;
  short local_94 [4];
  uint local_8c;
  int local_88;
  short local_84 [6];
  int local_78;
  int local_74;
  int local_70;
  short local_6c;
  int local_68;
  short local_64;
  int local_60;
  uint local_5c;
  int local_58;
  undefined1 *local_54;
  int local_50;
  int local_4c;
  int local_48;
  undefined1 *local_44;
  int local_3c;
  short local_38;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  short local_1c;
  int local_18;
  undefined2 local_14;
  int local_10;
  int local_c;
  undefined1 *local_8;
  
  if (((in_ECX[1] != 0) || (((in_ECX[4] != 0 && (in_ECX[4] != 1)) || (in_ECX[5] != -1)))) ||
     (piVar6 = in_ECX, (in_ECX[7] & 0x200U) != 0)) {
    DAT_004c2bbc = DAT_004c2bbc + 1;
    local_8 = &DAT_005ec218 + (short)in_ECX[2] * 0x29e8;
    local_1c = thunk_FUN_0045035a();
    local_14 = 0xffff;
    if ((in_ECX[1] == 1) && ((in_ECX[4] == 0 || (in_ECX[4] == 5)))) {
      local_14 = DAT_004a4b70;
    }
    else {
      iVar5 = thunk_FUN_004641de(in_ECX[5],in_ECX[4]);
      local_14 = *(undefined2 *)(iVar5 + 0x16);
    }
    local_c = 0;
    local_18 = 0;
    if ((in_ECX[7] & 0x383b6U) != 0) {
      if (((in_ECX[7] & 0x10U) != 0) &&
         (*(short *)(in_ECX + 0x12) = (short)in_ECX[0x12] + 1, (short)in_ECX[0x12] == 100)) {
        thunk_FUN_00452fcb();
        in_ECX[7] = in_ECX[7] & 0xffffffef;
        thunk_FUN_00453a5f();
      }
      if (((in_ECX[7] & 0x20U) != 0) &&
         (*(short *)(in_ECX + 0x12) = (short)in_ECX[0x12] + 1, 0x17 < (short)in_ECX[0x12])) {
        in_ECX[7] = in_ECX[7] & 0xffffffdf;
      }
      if (((in_ECX[7] & 0x80U) != 0) &&
         (*(short *)(in_ECX + 0x12) = (short)in_ECX[0x12] + 1, 100 < (short)in_ECX[0x12])) {
        in_ECX[7] = in_ECX[7] & 0xffffff7f;
        thunk_FUN_00452ae7();
      }
      if ((in_ECX[7] & 0x100U) != 0) {
        *(short *)(in_ECX + 0x11) = (short)in_ECX[0x11] + 1;
        if (999 < (short)in_ECX[0x11]) {
          *(short *)(in_ECX + 0x11) = 0;
          in_ECX[7] = in_ECX[7] & 0xfffffeff;
        }
        thunk_FUN_00453a5f();
      }
      if ((in_ECX[7] & 0x200U) == 0) {
        if ((in_ECX[7] & 0x8000U) == 0) {
          if ((in_ECX[7] & 0x20000U) == 0) {
            if (((in_ECX[7] & 0x10000U) != 0) &&
               (*(short *)(in_ECX + 0xe) = (short)in_ECX[0xe] + -1, (short)in_ECX[0xe] < 1)) {
              in_ECX[7] = in_ECX[7] & 0xfffeffff;
            }
          }
          else {
            *(short *)(in_ECX + 0xe) = (short)in_ECX[0xe] + -1;
            if ((short)in_ECX[0xe] < 1) {
              in_ECX[7] = in_ECX[7] & 0xfffdffff;
            }
          }
        }
        else {
          *(short *)(in_ECX + 0xe) = (short)in_ECX[0xe] + -1;
          if ((short)in_ECX[0xe] < 1) {
            in_ECX[7] = in_ECX[7] & 0xffff7fff;
          }
        }
      }
      else {
        *(short *)(in_ECX + 0xe) = (short)in_ECX[0xe] + -1;
        if ((short)in_ECX[0xe] < 1) {
          in_ECX[7] = in_ECX[7] & 0xfffffdff;
        }
      }
      if ((in_ECX[7] & 2U) != 0) {
        *(short *)((int)in_ECX + 0x42) = *(short *)((int)in_ECX + 0x42) + 1;
        local_20 = 0;
        if ((in_ECX[1] == 1) && (in_ECX[5] != 4)) {
          local_20 = 100;
        }
        else {
          local_24 = thunk_FUN_00456bd0(local_14);
          if (local_24 == 0) {
            local_20 = 0x28;
          }
          else {
            local_20 = (int)*(short *)(local_24 + 0xc);
          }
        }
        if (local_20 <= *(short *)((int)in_ECX + 0x42)) {
          in_ECX[7] = in_ECX[7] & 0xfffffffd;
          local_c = 1;
        }
      }
      if ((in_ECX[7] & 4U) != 0) {
        *(short *)(in_ECX + 0x10) = (short)in_ECX[0x10] + 1;
        local_28 = thunk_FUN_00456b8d(local_14);
        if ((local_28 != 0) && (*(short *)(local_28 + 10) <= (short)in_ECX[0x10])) {
          in_ECX[7] = in_ECX[7] & 0xfffffffb;
          local_18 = 1;
        }
      }
    }
    if (in_ECX[1] == 1) {
      local_2c = thunk_FUN_00456aca(local_14);
      if (local_2c != 0) {
        if (in_ECX[4] == 5) {
          *(short *)((int)in_ECX + 0x3a) = *(short *)((int)in_ECX + 0x3a) + 1;
          if (0x7d < *(short *)((int)in_ECX + 0x3a)) {
            *(short *)((int)in_ECX + 0x3a) = 0x66;
          }
        }
        else if (in_ECX[4] == 0) {
          if (*(short *)((int)in_ECX + 0x3a) < 0x5a) {
            *(short *)((int)in_ECX + 0x3a) = *(short *)((int)in_ECX + 0x3a) + 1;
            if (0x59 < *(short *)((int)in_ECX + 0x3a)) {
              *(short *)((int)in_ECX + 0x3a) = 0;
            }
          }
          else {
            *(short *)((int)in_ECX + 0x3a) = *(short *)((int)in_ECX + 0x3a) + -1;
            if (*(short *)((int)in_ECX + 0x3a) < 0x5a) {
              *(short *)((int)in_ECX + 0x3a) = 0;
            }
          }
        }
        else {
          *(short *)((int)in_ECX + 0x3a) = *(short *)((int)in_ECX + 0x3a) + 1;
          if (*(short *)(local_2c + 4) <= *(short *)((int)in_ECX + 0x3a)) {
            *(short *)((int)in_ECX + 0x3a) = 0;
          }
        }
      }
    }
    else {
      if (((in_ECX[7] & 1U) != 0) && (local_30 = thunk_FUN_00456aca(local_14), local_30 != 0)) {
        if ((in_ECX[5] == 4) || (*(short *)((int)in_ECX + 0x32) < 2)) {
          *(short *)((int)in_ECX + 0x3a) = *(short *)((int)in_ECX + 0x3a) + 1;
        }
        else {
          *(ushort *)((int)in_ECX + 0x3a) =
               *(short *)((int)in_ECX + 0x3a) + (ushort)*(byte *)(local_30 + 2);
        }
        if (*(short *)(local_30 + 4) <= *(short *)((int)in_ECX + 0x3a)) {
          *(short *)((int)in_ECX + 0x3a) = 0;
        }
      }
      if (in_ECX[1] == 0) {
        local_34 = thunk_FUN_00456b0d(local_14);
        if (local_34 != 0) {
          local_38 = (short)in_ECX[0xf];
          if ((0 < local_38) || (((in_ECX[7] & 0x400U) != 0 && ((in_ECX[7] & 1U) != 0)))) {
            local_38 = local_38 + 1;
          }
          if (local_38 == 0x28) {
            local_38 = 0;
          }
          *(short *)(in_ECX + 0xf) = local_38;
        }
        if (0 < (short)in_ECX[0x16]) {
          *(short *)((int)in_ECX + 0x46) = *(short *)((int)in_ECX + 0x46) + 1;
          if (*(short *)((int)in_ECX + 0x46) < 0x10) {
            return in_ECX;
          }
          *(short *)((int)in_ECX + 0x46) = 0;
          if ((short)in_ECX[0x16] == 2) {
            *(short *)(in_ECX + 0x16) = 0;
            piVar6 = (int *)thunk_FUN_00453a5f();
            return piVar6;
          }
          if ((short)in_ECX[0x16] != 3) {
            return in_ECX;
          }
          *(short *)(in_ECX + 0x16) = 0;
          piVar6 = (int *)thunk_FUN_00452a15();
          return piVar6;
        }
      }
    }
    local_10 = thunk_FUN_00456b4d(local_14);
    piVar6 = (int *)0x0;
    if (local_10 != 0) {
      if ((*(short *)((int)in_ECX + 0x3e) == -1) && (*(byte *)(local_10 + 4) < 100)) {
        local_3c = (uint)*(byte *)(local_10 + 4) * (uint)*(byte *)(local_10 + 4) + 1;
        piVar6 = (int *)thunk_FUN_00467260(local_3c);
        if (piVar6 == (int *)0x0) {
          *(short *)((int)in_ECX + 0x3e) = 0;
        }
      }
      else {
        *(short *)((int)in_ECX + 0x3e) = *(short *)((int)in_ECX + 0x3e) + 1;
        piVar6 = (int *)(int)*(short *)((int)in_ECX + 0x3e);
        if ((int)*(short *)(local_10 + 6) <= (int)*(short *)((int)in_ECX + 0x3e)) {
          *(short *)((int)in_ECX + 0x3e) = -1;
          piVar6 = in_ECX;
        }
      }
    }
    uVar1 = in_ECX[4];
    if (uVar1 < 0x33) {
      piVar6 = (int *)(uint)(&switchD_00451317::switchdataD_00452623)[uVar1];
      switch(uVar1) {
      case 0:
      case 1:
        if (in_ECX[5] == 4) {
          piVar6 = (int *)thunk_FUN_00452859(5,4);
        }
        else {
          piVar6 = in_ECX;
          if ((in_ECX[1] == 1) && (local_c != 0)) {
            iVar5 = *(short *)((int)in_ECX + 0x2e) * 0x4c;
            piVar6 = &DAT_006137b8 + *(short *)((int)in_ECX + 0x2e) * 0x13;
            *(short *)(&DAT_006137c8 + iVar5) = (short)*in_ECX;
            *(short *)(&DAT_006137ca + iVar5) = *(short *)((int)in_ECX + 2) + -0x28;
            *(uint *)(&DAT_006137d4 + iVar5) = *(uint *)(&DAT_006137d4 + iVar5) & 0xfffff7fe;
          }
        }
        break;
      case 2:
        piVar6 = in_ECX;
        if ((in_ECX[7] & 1U) == 0) {
          if (local_18 == 0) {
            if (local_c != 0) {
              piVar6 = (int *)thunk_FUN_004669bd(in_ECX);
            }
          }
          else {
            uVar1 = in_ECX[7];
            in_ECX[7] = (int)(uVar1 | 2);
            *(short *)((int)in_ECX + 0x42) = 0;
            piVar6 = (int *)(uVar1 | 2);
          }
        }
        break;
      case 4:
      case 0x16:
        piVar6 = (int *)(in_ECX[7] & 1);
        if ((piVar6 != (int *)0x0) && ((short)in_ECX[0xc] < 0x20)) {
          *(short *)(in_ECX + 0xc) = (short)in_ECX[0xc] + 1;
          piVar6 = in_ECX;
        }
        break;
      case 5:
        *(short *)(in_ECX + 0xc) = (short)in_ECX[0xc] + *(short *)((int)in_ECX + 0x32);
        piVar6 = (int *)(int)(short)in_ECX[0xc];
        if (DAT_00618e48 * -100 + 0x4b0 <= (int)(short)in_ECX[0xc]) {
          if (in_ECX[1] == 1) {
            local_140 = thunk_FUN_004535e4();
          }
          else {
            local_140 = thunk_FUN_0045388f();
          }
          piVar6 = (int *)thunk_FUN_00452859(local_140,4);
        }
        break;
      case 6:
      case 7:
      case 8:
      case 9:
        if ((in_ECX[7] & 3U) == 1) {
          if (DAT_0061f8d8 != 0) {
            *(short *)(in_ECX + 0xc) = (short)in_ECX[0xc] + *(short *)((int)in_ECX + 0x32);
          }
          local_58 = DAT_004bf11c;
          if (DAT_004bf11c < 0) {
            local_58 = 0;
          }
          if (4 < local_58) {
            local_58 = 4;
          }
          local_4c = local_58 * -400 + 10000;
          if (1 < local_58) {
            if (DAT_00618e44 < 0x186a1) {
              local_5c = 0;
            }
            else {
              local_5c = (DAT_00618e44 - 100000) / 100;
              if (0x960 < local_5c) {
                local_5c = 0x960;
              }
            }
            local_4c = local_4c - local_5c;
          }
          iVar5 = (short)in_ECX[2] * 0x29e8;
          local_44 = &DAT_005ec218 + iVar5;
          local_54 = &DAT_005ec640 + iVar5;
          local_48 = 0;
          for (local_50 = 0; local_50 < (short)(&DAT_005eebc0)[(short)in_ECX[2] * 0x14f4];
              local_50 = local_50 + 1) {
            if (((local_54 != (undefined1 *)0x0) && (*(int *)(local_54 + 4) == 1)) &&
               (local_54[0x22] != '\0')) {
              local_48 = local_48 + 1;
            }
            local_54 = local_54 + 0x60;
          }
          if (1 < local_58) {
            if (local_48 < 0) {
              local_48 = 0;
            }
            if (5 < local_48) {
              local_48 = 5;
            }
            local_60 = (0xe - local_58) - local_48;
            if (local_60 < 5) {
              local_60 = 5;
            }
            if (10 < local_60) {
              local_60 = 10;
            }
            local_4c = (local_4c * local_60) / 10;
          }
          piVar6 = (int *)(int)(short)in_ECX[0xc];
          if (local_4c <= (short)in_ECX[0xc]) {
            in_ECX[7] = in_ECX[7] | 2;
            local_a0 = thunk_FUN_0046562b(4,0xffffffff);
            local_70 = (int)*(short *)(local_44 + 0x29e0);
            if (*(short *)(local_44 + 0x29e0) < 0) {
              local_70 = 0;
            }
            if (0xe < local_70) {
              local_70 = 0xe;
            }
            local_64 = *(short *)(&DAT_004a28c8 + local_70 * 2);
            local_6c = *(short *)(&DAT_004a28e8 + local_70 * 2);
            if (*(short *)(&DAT_004a28c8 + local_70 * 2) < -1) {
              local_64 = -1;
            }
            if (3 < local_64) {
              local_64 = 3;
            }
            if (*(short *)(&DAT_004a28e8 + local_70 * 2) < -1) {
              local_6c = -1;
            }
            if (3 < local_6c) {
              local_6c = 3;
            }
            local_84[4] = *(short *)(local_70 * 2 + 0x4a2908);
            local_9c = *(short *)(local_70 * 2 + 0x4a2928);
            local_98 = in_ECX[4] + -6;
            local_94[0] = 0;
            local_94[1] = 0;
            local_94[2] = 0;
            local_94[3] = 0;
            local_54 = local_44 + 0x428;
            for (local_88 = 0; local_88 < *(short *)(local_44 + 0x29a8); local_88 = local_88 + 1) {
              if ((5 < *(int *)(local_54 + 0x10)) && (*(int *)(local_54 + 0x10) < 10)) {
                local_ac = *(int *)(local_54 + 0x10) + -6;
                if (*(int *)(local_54 + 0x10) + -6 < 0) {
                  local_ac = 0;
                }
                if (3 < local_ac) {
                  local_ac = 3;
                }
                local_94[local_ac] = local_94[local_ac] + 1;
              }
              local_54 = local_54 + 0x60;
            }
            local_84[0] = 0;
            local_84[1] = 0;
            local_84[2] = 0;
            local_84[3] = 0;
            local_a4 = thunk_FUN_004656d6((int)(short)in_ECX[2],0xfffffffe);
            for (local_88 = 0; local_88 < local_a4; local_88 = local_88 + 1) {
              iVar5 = (short)(&DAT_00618fb4)[local_88] * 0x4c;
              local_b0 = &DAT_006137b8 + (short)(&DAT_00618fb4)[local_88] * 0x13;
              if ((((local_b0 != (int *)0x0) && (*local_b0 == 4)) &&
                  (9 < *(int *)(&DAT_006137bc + iVar5))) && (*(int *)(&DAT_006137bc + iVar5) < 0x12)
                 ) {
                sVar3 = thunk_FUN_0042003c(*(undefined4 *)(&DAT_006137bc + iVar5));
                local_b4 = (int)sVar3;
                if (sVar3 < 0) {
                  local_b4 = 0;
                }
                if (3 < local_b4) {
                  local_b4 = 3;
                }
                local_84[local_b4] = local_84[local_b4] + 1;
              }
            }
            local_68 = -1;
            local_74 = 50000;
            if (0 < local_94[0]) {
              local_68 = 0;
              local_74 = (local_84[0] * 100) / (int)local_94[0];
            }
            for (local_88 = 1; local_88 < 4; local_88 = local_88 + 1) {
              if (0 < local_94[local_88]) {
                local_b8 = (local_84[local_88] * 100) / (int)local_94[local_88];
                if (local_b8 < local_74) {
                  local_68 = local_88;
                  local_74 = local_b8;
                }
              }
            }
            local_8c = (uint)(local_98 == local_68);
            local_78 = 0;
            if (local_8c == 0) {
              local_78 = 1;
            }
            else {
              local_c4 = (int)*(short *)(&DAT_0061f9d4 + (short)in_ECX[2] * 2);
              local_c0 = (int)*(short *)(&DAT_0061fa10 + (short)in_ECX[2] * 2);
              local_c8 = (int)*(short *)(&DAT_0061f998 + (short)in_ECX[2] * 2);
              local_bc = (int)*(short *)(&DAT_0061f9f2 + (short)in_ECX[2] * 2);
              local_cc = (int)*(short *)(&DAT_0061f9b6 + (short)in_ECX[2] * 2);
              local_d0 = *(int *)(&DAT_0061f920 + (short)in_ECX[2] * 4);
              if ((local_c8 == 0) || (0x7b < local_a0)) {
                local_78 = 1;
              }
              else if ((local_c4 == 0) && (local_cc == 0)) {
                local_78 = 2;
              }
              else if (local_c0 == 1) {
                if (local_d0 == 0) {
                  if (local_bc < 2) {
                    local_78 = 2;
                  }
                  else if (local_c8 < 5) {
                    if (local_cc < 4) {
                      if ((local_cc == 0) && (2 < local_c8)) {
                        local_78 = 2;
                      }
                      else if (local_cc + 2 < local_c8) {
                        local_78 = 2;
                      }
                    }
                    else {
                      local_78 = 1;
                    }
                  }
                  else {
                    local_78 = 2;
                  }
                }
                else {
                  local_78 = 1;
                }
              }
              else if (local_cc == 0) {
                if (local_c4 < local_c8) {
                  local_78 = 2;
                }
                else if (local_c8 < local_c4) {
                  local_78 = 1;
                }
              }
              else if (local_c8 * 2 - local_cc == 0 || local_c8 * 2 < local_cc) {
                if (local_cc < local_c8 * 4) {
                  if (local_c4 < local_c8) {
                    local_78 = 2;
                  }
                  else if (local_c8 < local_c4) {
                    local_78 = 1;
                  }
                }
                else if (local_d0 != 0) {
                  local_78 = 1;
                }
              }
              else if (local_c8 * 2 - local_c4 == 0 || local_c8 * 2 < local_c4) {
                if (local_c8 * 2 < local_c4) {
                  local_78 = 1;
                }
              }
              else {
                local_78 = 2;
              }
              if (local_78 == 0) {
                iVar5 = thunk_FUN_00467260(2);
                local_78 = 2 - (uint)(iVar5 != 0);
              }
            }
            if (local_78 == 1) {
              local_a8 = 9;
            }
            else if (local_98 == local_6c) {
              local_a8 = local_98 * 2 + 0xb;
            }
            else if (local_98 == local_64) {
              local_a8 = local_98 * 2 + 10;
            }
            else {
              iVar5 = thunk_FUN_00467260(2);
              local_a8 = iVar5 + 10 + local_98 * 2;
            }
            thunk_FUN_004532e2(4,local_a8);
            if (*(short *)((int)in_ECX + 0x2e) != -1) {
              local_d4 = 0;
              if (local_98 == local_6c) {
                local_d4 = (uint)(0 < local_9c);
              }
              else if (local_98 == local_64) {
                local_d4 = (uint)(0 < local_84[4]);
              }
              else if (local_70 == 0xe) {
                local_d4 = 1;
              }
              if (local_d4 != 0) {
                local_d8 = (((int)(local_70 + (local_70 >> 0x1f & 3U)) >> 2) + -2 + DAT_00618e48) *
                           2;
                if (DAT_00618e48 < 2) {
                  local_d8 = local_d8 / 2;
                }
                iVar5 = thunk_FUN_00467260(9);
                if (iVar5 < local_d8) {
                  local_dc = &DAT_006137b8 + *(short *)((int)in_ECX + 0x2e) * 0x13;
                  thunk_FUN_0041ff8b(1);
                  uVar4 = thunk_FUN_00420f28();
                  *(undefined2 *)(local_dc + 8) = uVar4;
                }
              }
            }
            *(short *)(in_ECX + 0xc) = 0;
            piVar6 = in_ECX;
          }
        }
        if (local_c != 0) {
          local_e4 = &DAT_006137b8 + *(short *)((int)in_ECX + 0x2e) * 0x13;
          iVar5 = thunk_FUN_00456bd0(local_14);
          piVar6 = (int *)0x0;
          if (iVar5 != 0) {
            *(short *)(local_e4 + 4) = (short)*in_ECX + *(short *)(iVar5 + 6);
            *(short *)((int)local_e4 + 0x12) = *(short *)((int)in_ECX + 2) + *(short *)(iVar5 + 8);
            local_e4[7] = local_e4[7] & 0xfffff7fe;
            piVar6 = local_e4;
          }
        }
        break;
      case 10:
      case 0xb:
      case 0xc:
      case 0xd:
      case 0xe:
      case 0xf:
        if ((in_ECX[7] & 1U) != 0) {
          if ((in_ECX[7] & 2U) == 0) {
            piVar6 = (int *)((DAT_00618e44 - (int)local_1c) / 10);
            if ((DAT_00618e44 - (int)local_1c) % 10 == 0) {
              local_ec = 0;
              piVar6 = (int *)thunk_FUN_004656d6((int)(short)in_ECX[2],0xfffffffe);
              local_e8 = piVar6;
              for (local_f0 = (int *)0x0; (int)local_f0 < (int)local_e8;
                  local_f0 = (int *)((int)local_f0 + 1)) {
                local_f4 = &DAT_006137b8 + (short)(&DAT_00618fb4)[(int)local_f0] * 0x13;
                piVar6 = local_f0;
                if (((-1 < *local_f4) && (piVar6 = local_f4, *local_f4 < 4)) &&
                   (piVar6 = (int *)thunk_FUN_00420635(in_ECX), (int)piVar6 < 0x3c)) {
                  local_ec = 1;
                  break;
                }
              }
              if (local_ec != 0) {
                uVar1 = in_ECX[7];
                in_ECX[7] = (int)(uVar1 | 2);
                *(short *)((int)in_ECX + 0x42) = 0;
                piVar6 = (int *)(uVar1 | 2);
              }
            }
          }
          else {
            local_fc = 0x1e;
            local_100 = 1;
            local_f8 = thunk_FUN_00456bd0(local_14);
            if (local_f8 != 0) {
              local_fc = (int)*(short *)(local_f8 + 4);
              local_100 = (uint)(*(short *)(local_f8 + 0xe) == -1);
            }
            piVar6 = in_ECX;
            if (*(short *)((int)in_ECX + 0x42) == local_fc) {
              local_118 = 0;
              piVar6 = (int *)thunk_FUN_004656d6((int)(short)in_ECX[2],0xfffffffe);
              local_104 = piVar6;
              for (local_114 = (int *)0x0; (int)local_114 < (int)local_104;
                  local_114 = (int *)((int)local_114 + 1)) {
                piVar7 = &DAT_006137b8 + (short)(&DAT_00618fb4)[(int)local_114] * 0x13;
                piVar6 = local_114;
                if (((-1 < *piVar7) && (piVar6 = piVar7, *piVar7 < 4)) &&
                   (piVar6 = (int *)thunk_FUN_00420635(in_ECX), (int)piVar6 < 0x3c)) {
                  asStack_110[local_118] = (&DAT_00618fb4)[(int)local_114];
                  local_118 = local_118 + 1;
                  piVar6 = local_114;
                  if (4 < local_118) break;
                }
              }
              if (local_118 != 0) {
                iVar5 = thunk_FUN_00467260(local_118);
                *(short *)((int)in_ECX + 0x36) = asStack_110[iVar5];
                if (local_100 != 0) {
                  thunk_FUN_004533a8(&DAT_006137b8 + *(short *)((int)in_ECX + 0x36) * 0x13);
                }
                piVar6 = (int *)thunk_FUN_00416342(in_ECX,local_100,1);
              }
            }
          }
        }
        break;
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x14:
      case 0x15:
        if ((in_ECX[7] & 1U) == 0) {
          piVar6 = (int *)0x0;
        }
        else if (((in_ECX[7] & 2U) == 0) && (*(short *)((int)in_ECX + 0x36) == -1)) {
          piVar6 = (int *)((DAT_00618e44 - (int)local_1c) / 10);
          if ((DAT_00618e44 - (int)local_1c) % 10 == 0) {
            bVar2 = false;
            piVar7 = (int *)thunk_FUN_004656d6((int)(short)in_ECX[2],0xfffffffe);
            piVar6 = piVar7;
            for (local_12c = (int *)0x0; (int)local_12c < (int)piVar7;
                local_12c = (int *)((int)local_12c + 1)) {
              piVar9 = &DAT_006137b8 + (short)(&DAT_00618fb4)[(int)local_12c] * 0x13;
              piVar6 = local_12c;
              if ((-1 < *piVar9) && (piVar6 = piVar9, *piVar9 < 4)) {
                iVar5 = thunk_FUN_00420635(in_ECX);
                iVar8 = thunk_FUN_004641de(in_ECX[5],in_ECX[4]);
                piVar6 = (int *)(int)*(short *)(iVar8 + 6);
                if (iVar5 <= (int)piVar6) {
                  piVar6 = (int *)CONCAT22(*(short *)(iVar8 + 6) >> 0xf,
                                           (&DAT_00618fb4)[(int)local_12c]);
                  *(undefined2 *)((int)in_ECX + 0x36) = (&DAT_00618fb4)[(int)local_12c];
                  bVar2 = true;
                  break;
                }
              }
            }
            if (bVar2) {
              in_ECX[7] = in_ECX[7] | 2;
              *(short *)((int)in_ECX + 0x42) = 0;
              piVar6 = in_ECX;
            }
          }
        }
        else {
          piVar6 = (int *)(in_ECX[7] & 2);
          if ((piVar6 != (int *)0x0) && (*(short *)((int)in_ECX + 0x36) != -1)) {
            sVar3 = 0x1e;
            iVar5 = thunk_FUN_00456bd0(local_14);
            if (iVar5 != 0) {
              sVar3 = *(short *)(iVar5 + 4);
            }
            bVar2 = iVar5 == 0;
            piVar6 = in_ECX;
            if (*(short *)((int)in_ECX + 0x42) == sVar3) {
              if (bVar2) {
                thunk_FUN_004533a8(&DAT_006137b8 + *(short *)((int)in_ECX + 0x36) * 0x13);
              }
              thunk_FUN_00416342(in_ECX,bVar2,1);
              *(short *)((int)in_ECX + 0x36) = -1;
            }
          }
        }
        break;
      case 0x25:
      case 0x26:
      case 0x27:
        if (((in_ECX[7] & 1U) != 0) &&
           (*(short *)(in_ECX + 0xb) = (short)in_ECX[0xb] + 1, 10 < (short)in_ECX[0xb])) {
          *(short *)((int)in_ECX + 0x36) = 0;
          *(short *)(in_ECX + 0xb) = 0;
        }
        if ((((in_ECX[9] == 0) && ((in_ECX[7] & 1U) != 0)) && ((in_ECX[7] & 2U) == 0)) &&
           (*(short *)(in_ECX + 0xc) = (short)in_ECX[0xc] + *(short *)((int)in_ECX + 0x32),
           0x13 < (short)in_ECX[0xc])) {
          in_ECX[7] = in_ECX[7] | 2;
          *(short *)((int)in_ECX + 0x42) = 0;
          *(short *)(in_ECX + 0xc) = 0;
        }
        piVar6 = in_ECX;
        if (local_c != 0) {
          if (in_ECX[4] == 0x25) {
            in_ECX[9] = 1;
          }
          else if (in_ECX[4] == 0x27) {
            in_ECX[9] = 2;
          }
          else if (in_ECX[4] == 0x26) {
            in_ECX[9] = 3;
          }
        }
        break;
      case 0x2a:
        piVar6 = (int *)(DAT_00618e44 & 0xff);
        if ((piVar6 == (int *)0x0) && ((short)in_ECX[10] < 0x14)) {
          *(short *)(in_ECX + 10) = (short)in_ECX[10] + 1;
          piVar6 = in_ECX;
        }
        break;
      case 0x2c:
      case 0x2d:
      case 0x2e:
      case 0x2f:
      case 0x30:
      case 0x31:
      case 0x32:
        if ((in_ECX[7] & 0x90U) == 0) {
          if ((short)in_ECX[6] == -1) {
            thunk_FUN_00414b64(s_C__float_src_pad_cpp_004a29f0,0x525,s_mStaffBld___1_004a29e0);
          }
          iVar5 = thunk_FUN_00450385();
          if (iVar5 == 0) {
            thunk_FUN_00414b64(s_C__float_src_pad_cpp_004a2a0c,0x527,&DAT_004a2a08);
          }
          piVar6 = (int *)thunk_FUN_0045cd75();
        }
      }
    }
    if (((in_ECX[5] != 4) && (piVar6 = in_ECX, 1 < *(short *)((int)in_ECX + 0x32))) &&
       ((DAT_00618e44 & 0x3ff) == 0)) {
      *(short *)((int)in_ECX + 0x32) = 1;
    }
  }
  return piVar6;
}
```

---

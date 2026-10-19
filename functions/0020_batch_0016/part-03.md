# 0020_batch_0016 — détails (3/6)

## FUN_0047a7c0 — 0x47a7c0

- Classification : internal
- Corps : `0x47a7c0–0x47bae7`
- État : pseudocode obtenu
- Evidence : `ev_c337653463ee8c6cfd8d1c96e1f5ff733f7cb2d54228801312a9c893827bc0cb`
- Limites : Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again. Def-use links do not cross function boundaries and may omit memory aliasing, call side effects, or unresolved indirect flow. Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>. Ghidra Listing reports a terminal call at 0x47a7f2 with no resolved callee; its no-return basis is unknown. Ghidra Listing reports a terminal call at 0x47a81f with no resolved callee; its no-return basis is unknown. High p-code is decompiler-derived, not original source or runtime behavior. is_dead preserves the Java AST flag; decoded block members can retain that flag, so block_membership separately reports actual syntax-tree membership. Known omitted-edge counts cover links omitted from retained operations; omitted operations may contain additional uncounted links. Memory read/write effects include stack and temporary memory operations; they do not identify persistent state or business meaning. Operation, input, and def-use limits can truncate large functions; inspect truncation, omitted lower bounds, and known omitted counts before drawing conclusions. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Pseudocode is neither original source nor guaranteed to compile. References cover the complete Ghidra function-body AddressSet and exact entry. Dossier incoming edges omit sources owned by that function; procedure_references also retains those internal edges. Register variables, compiler-generated blocks, and pointer arithmetic remain decompiler artifacts. Resolved reference metadata identifies computed, indirect, external, call, jump, and data edges; unresolved targetless flows remain unknown, and function classifications distinguish thunks and externals. Synthetic Ghidra entry-point references without actionable memory sources are omitted. The Java bridge serializes one function request per Program and lets each decompilation run until it completes or the caller cancels. The Windows bridge uses authenticated IPv4 loopback because Node path-based IPC does not expose Java AF_UNIX sockets; the endpoint file contains no bearer token. The dossier combines Ghidra FunctionManager, Listing, ReferenceManager, BasicBlockModel, and decompiler observations; provider-specific pseudocode and assembly are not cross-provider text invariants. The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written. The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results. The target references PDB Float.pdb (GUID unknown, age (hex) 0, signature 3418386f, version NB10); Ghidra reports load state unknown. Original names and types may be missing; an empty name search does not prove a procedure is absent. Use list_procedures and address-based analysis to inspect recovered functions. REA does not admit a caller-selected PDB companion. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Types and calling conventions are Ghidra decompiler observations, not source declarations. Unresolved computed or indirect flows without target addresses are not represented as reference edges. Windows Ghidra P0 accepts native x86 and x86-64 PE applications and DLLs, and explicitly selected raw 6502 images; managed, hostile, sensitive, and mutable-path targets are unsupported. Windows sessions require the matching packaged Windows x64 native addon, local NTFS targets and runtimes, and Windows 10 or later. Native handles enforce path admission, private DACLs, and Job Object ownership automatically.

### Appels directs

- `0x474b20` — `_memset`
- `0x47a120` — `FUN_0047a120`
- `0x47bbb0` — `FUN_0047bbb0`
- `0x47bc10` — `__inc`
- `0x47bc70` — `FUN_0047bc70`
- `0x47bc90` — `__whiteout`
- `0x47f2b0` — `FUN_0047f2b0`
- `0x483550` — `__fptrap`
- `0x484300` — `FUN_00484300`
- `0x4845c0` — `FUN_004845c0`
- `0x484850` — `__allshl`

### Chaînes référencées

- `0x495197` — "`format != NULL"
- `0x4951f4` — "stream != NULL"
- `0x495d48` — "input.c"
- `0x495d48` — "input.c"
- `0x4a642c` — " \t-\r]"

### Pseudocode Ghidra

```c
int FUN_0047a7c0(int param_1,byte *param_2,undefined4 *param_3)

{
  byte bVar1;
  code *pcVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  byte *pbVar7;
  bool bVar8;
  longlong lVar9;
  uint local_228;
  uint local_224;
  uint local_220;
  uint local_21c;
  uint local_218;
  uint local_214;
  uint local_210;
  uint local_20c;
  uint local_200;
  uint local_1fc;
  byte local_1f4;
  undefined1 local_1f3;
  uint local_1f0;
  int local_1ec;
  uint *local_1e8;
  byte *local_1e4;
  int local_1e0;
  uint local_1dc;
  undefined4 *local_1d8;
  byte local_1d4;
  byte local_1d3 [351];
  char local_74;
  int local_70;
  char local_6c;
  char local_68;
  byte local_64 [11];
  undefined1 local_59;
  uint local_44;
  uint *local_40;
  char local_3c;
  uint local_38;
  undefined8 local_34;
  char local_2c;
  uint local_28;
  uint local_24;
  int local_20;
  char local_1c;
  char local_18;
  byte local_14;
  uint local_10;
  uint local_c;
  undefined2 local_8 [2];
  
  if ((param_2 == (byte *)0x0) &&
     (iVar4 = FUN_0047a120(2,"input.c",0x109,0,"format != NULL"), iVar4 == 1)) {
    pcVar2 = (code *)swi(3);
    iVar4 = (*pcVar2)();
    return iVar4;
  }
  if ((param_1 == 0) && (iVar4 = FUN_0047a120(2,"input.c",0x10c,0,"stream != NULL"), iVar4 == 1)) {
    pcVar2 = (code *)swi(3);
    iVar4 = (*pcVar2)();
    return iVar4;
  }
  local_2c = '\0';
  local_38 = 0;
  local_24 = local_38;
  do {
    if (*param_2 == 0) {
LAB_0047baaa:
      if ((local_1dc == 0xffffffff) && ((local_38 == 0 && (local_2c == '\0')))) {
        local_228 = 0xffffffff;
        local_38 = local_228;
      }
      return local_38;
    }
    if (DAT_004a87f4 < 2) {
      local_1fc = *(ushort *)(PTR_DAT_004a85e8 + (uint)*param_2 * 2) & 8;
    }
    else {
      local_1fc = FUN_0047f2b0(*param_2,8);
    }
    if (local_1fc != 0) {
      local_24 = local_24 - 1;
      uVar5 = __whiteout(&local_24,param_1,param_1);
      FUN_0047bc70(uVar5);
      do {
        param_2 = param_2 + 1;
        iVar4 = FUN_004845c0(*param_2);
      } while (iVar4 != 0);
    }
    if (*param_2 == 0x25) {
      local_44 = 0;
      local_c = local_c & 0xffffff00;
      local_70 = 0;
      local_1ec = 0;
      local_20 = 0;
      local_14 = 0;
      local_6c = '\0';
      local_74 = '\0';
      local_1c = '\0';
      local_68 = '\0';
      local_18 = '\0';
      local_3c = '\x01';
      local_1e0 = 0;
LAB_0047a935:
      if (local_1c == '\0') {
        pbVar7 = param_2 + 1;
        local_10 = (uint)*pbVar7;
        if (DAT_004a87f4 < 2) {
          local_200 = *(ushort *)(PTR_DAT_004a85e8 + local_10 * 2) & 4;
        }
        else {
          local_200 = FUN_0047f2b0(local_10,4);
        }
        if (local_200 == 0) {
          switch(local_10) {
          case 0x2a:
            local_74 = local_74 + '\x01';
            param_2 = pbVar7;
            break;
          case 0x46:
          case 0x4e:
            param_2 = pbVar7;
            break;
          case 0x49:
            if ((param_2[2] == 0x36) && (param_2[3] == 0x34)) {
              local_1e0 = local_1e0 + 1;
              local_34 = 0;
              param_2 = param_2 + 3;
              break;
            }
          default:
            local_1c = local_1c + '\x01';
            param_2 = pbVar7;
            break;
          case 0x4c:
            local_3c = local_3c + '\x01';
            param_2 = pbVar7;
            break;
          case 0x68:
            local_3c = local_3c + -1;
            local_18 = local_18 + -1;
            param_2 = pbVar7;
            break;
          case 0x6c:
            local_3c = local_3c + '\x01';
          case 0x77:
            local_18 = local_18 + '\x01';
            param_2 = pbVar7;
          }
        }
        else {
          local_1ec = local_1ec + 1;
          local_20 = (local_10 - 0x30) + local_20 * 10;
          param_2 = pbVar7;
        }
        goto LAB_0047a935;
      }
      if (local_74 == '\0') {
        local_1d8 = param_3;
        local_40 = (uint *)*param_3;
        param_3 = param_3 + 1;
      }
      local_1c = '\0';
      if (local_18 == '\0') {
        if ((*param_2 == 0x53) || (*param_2 == 0x43)) {
          local_18 = '\x01';
        }
        else {
          local_18 = -1;
        }
      }
      local_10 = *param_2 | 0x20;
      lVar9 = local_34;
      if (local_10 != 0x6e) {
        if ((local_10 == 99) || (local_10 == 0x7b)) {
          local_24 = local_24 + 1;
          local_1dc = __inc(param_1);
          lVar9 = local_34;
        }
        else {
          local_1dc = __whiteout(&local_24,param_1);
          lVar9 = local_34;
        }
      }
      local_34 = lVar9;
      if ((local_1ec != 0) && (local_20 == 0)) {
        local_24 = local_24 - 1;
        FUN_0047bc70(local_1dc,param_1);
        goto LAB_0047baaa;
      }
      pbVar7 = param_2;
      switch(local_10) {
      case 99:
        if (local_1ec == 0) {
          local_1ec = 1;
          local_20 = local_20 + 1;
        }
        if ('\0' < local_18) {
          local_68 = local_68 + '\x01';
        }
        local_1e4 = &DAT_004a6434;
        local_14 = local_14 - 1;
        goto LAB_0047ac40;
      case 100:
      case 0x6f:
      case 0x75:
        goto switchD_0047ab84_caseD_64;
      case 0x65:
      case 0x66:
      case 0x67:
        local_1e4 = &local_1d4;
        if (local_1dc == 0x2d) {
          local_1d4 = 0x2d;
          local_1e4 = local_1d3;
LAB_0047b56f:
          local_20 = local_20 + -1;
          local_24 = local_24 + 1;
          local_1dc = __inc(param_1);
          lVar9 = local_34;
        }
        else if (local_1dc == 0x2b) goto LAB_0047b56f;
        local_34 = lVar9;
        if ((local_1ec == 0) || (0x15d < local_20)) {
          local_20 = 0x15d;
        }
        while( true ) {
          if (DAT_004a87f4 < 2) {
            local_21c = *(ushort *)(PTR_DAT_004a85e8 + local_1dc * 2) & 4;
          }
          else {
            local_21c = FUN_0047f2b0(local_1dc,4);
          }
          if ((local_21c == 0) ||
             (iVar4 = local_20 + -1, bVar8 = local_20 == 0, local_20 = iVar4, bVar8)) break;
          local_70 = local_70 + 1;
          *local_1e4 = (byte)local_1dc;
          local_1e4 = local_1e4 + 1;
          local_24 = local_24 + 1;
          local_1dc = __inc(param_1);
        }
        if ((DAT_004a87f8 == (byte)local_1dc) &&
           (iVar4 = local_20 + -1, bVar8 = local_20 != 0, local_20 = iVar4, bVar8)) {
          local_24 = local_24 + 1;
          local_1dc = __inc(param_1);
          *local_1e4 = DAT_004a87f8;
          local_1e4 = local_1e4 + 1;
          while( true ) {
            if (DAT_004a87f4 < 2) {
              local_220 = *(ushort *)(PTR_DAT_004a85e8 + local_1dc * 2) & 4;
            }
            else {
              local_220 = FUN_0047f2b0(local_1dc,4);
            }
            if ((local_220 == 0) ||
               (iVar4 = local_20 + -1, bVar8 = local_20 == 0, local_20 = iVar4, bVar8)) break;
            local_70 = local_70 + 1;
            *local_1e4 = (byte)local_1dc;
            local_1e4 = local_1e4 + 1;
            local_24 = local_24 + 1;
            local_1dc = __inc(param_1);
          }
        }
        if ((local_70 != 0) &&
           (((local_1dc == 0x65 || (local_1dc == 0x45)) &&
            (iVar4 = local_20 + -1, bVar8 = local_20 != 0, local_20 = iVar4, bVar8)))) {
          *local_1e4 = 0x65;
          local_1e4 = local_1e4 + 1;
          local_24 = local_24 + 1;
          local_1dc = __inc(param_1);
          if (local_1dc == 0x2d) {
            *local_1e4 = 0x2d;
            local_1e4 = local_1e4 + 1;
LAB_0047b7d7:
            if (local_20 != 0) {
              local_24 = local_24 + 1;
              local_20 = local_20 + -1;
              local_1dc = __inc(param_1);
            }
          }
          else if (local_1dc == 0x2b) goto LAB_0047b7d7;
          while( true ) {
            if (DAT_004a87f4 < 2) {
              local_224 = *(ushort *)(PTR_DAT_004a85e8 + local_1dc * 2) & 4;
            }
            else {
              local_224 = FUN_0047f2b0(local_1dc,4);
            }
            if ((local_224 == 0) ||
               (iVar4 = local_20 + -1, bVar8 = local_20 == 0, local_20 = iVar4, bVar8)) break;
            local_70 = local_70 + 1;
            *local_1e4 = (byte)local_1dc;
            local_1e4 = local_1e4 + 1;
            local_24 = local_24 + 1;
            local_1dc = __inc(param_1);
          }
        }
        local_24 = local_24 - 1;
        FUN_0047bc70(local_1dc,param_1);
        if (local_70 == 0) goto LAB_0047baaa;
        lVar9 = local_34;
        if (local_74 == '\0') {
          local_38 = local_38 + 1;
          *local_1e4 = 0;
          (*(code *)PTR___fptrap_004a63e0)(local_3c + -1,local_40,&local_1d4);
          lVar9 = local_34;
        }
        break;
      default:
        if (*param_2 != local_1dc) {
          local_24 = local_24 - 1;
          FUN_0047bc70(local_1dc,param_1);
          goto LAB_0047baaa;
        }
        local_2c = local_2c + -1;
        if (local_74 == '\0') {
          param_3 = local_1d8;
        }
        break;
      case 0x69:
        local_10 = 100;
      case 0x78:
        if (local_1dc == 0x2d) {
          local_6c = local_6c + '\x01';
LAB_0047afdf:
          local_20 = local_20 + -1;
          if ((local_20 == 0) && (local_1ec != 0)) {
            local_1c = local_1c + '\x01';
          }
          else {
            local_24 = local_24 + 1;
            local_1dc = __inc(param_1);
            lVar9 = local_34;
          }
        }
        else if (local_1dc == 0x2b) goto LAB_0047afdf;
        local_34 = lVar9;
        if (local_1dc == 0x30) {
          local_24 = local_24 + 1;
          local_1dc = __inc(param_1);
          if (((byte)local_1dc == 'x') || ((byte)local_1dc == 'X')) {
            local_24 = local_24 + 1;
            local_1dc = __inc(param_1);
            local_10 = 0x78;
          }
          else {
            local_70 = local_70 + 1;
            if (local_10 == 0x78) {
              local_24 = local_24 - 1;
              FUN_0047bc70(local_1dc,param_1);
              local_1dc = 0x30;
            }
            else {
              local_10 = 0x6f;
            }
          }
        }
        goto LAB_0047b11e;
      case 0x6e:
        local_44 = local_24;
        if (local_74 != '\0') break;
        goto LAB_0047b4e1;
      case 0x70:
        local_3c = '\x01';
switchD_0047ab84_caseD_64:
        if (local_1dc == 0x2d) {
          local_6c = local_6c + '\x01';
LAB_0047b0e1:
          local_20 = local_20 + -1;
          if ((local_20 == 0) && (local_1ec != 0)) {
            local_1c = local_1c + '\x01';
          }
          else {
            local_24 = local_24 + 1;
            local_1dc = __inc(param_1);
          }
        }
        else if (local_1dc == 0x2b) goto LAB_0047b0e1;
LAB_0047b11e:
        lVar9 = local_34;
        if (local_1e0 == 0) {
          while (local_1c == '\0') {
            local_34 = lVar9;
            if ((local_10 == 0x78) || (local_10 == 0x70)) {
              if (DAT_004a87f4 < 2) {
                local_214 = *(ushort *)(PTR_DAT_004a85e8 + local_1dc * 2) & 0x80;
              }
              else {
                local_214 = FUN_0047f2b0(local_1dc,0x80);
                lVar9 = local_34;
              }
              if (local_214 == 0) {
                local_1c = local_1c + '\x01';
              }
              else {
                local_44 = local_44 << 4;
                local_34 = lVar9;
                local_1dc = FUN_0047bbb0(local_1dc);
                lVar9 = local_34;
              }
            }
            else {
              if (DAT_004a87f4 < 2) {
                local_218 = *(ushort *)(PTR_DAT_004a85e8 + local_1dc * 2) & 4;
              }
              else {
                local_218 = FUN_0047f2b0(local_1dc,4);
                lVar9 = local_34;
              }
              if (local_218 == 0) {
                local_1c = local_1c + '\x01';
              }
              else if (local_10 == 0x6f) {
                if ((int)local_1dc < 0x38) {
                  local_44 = local_44 << 3;
                }
                else {
                  local_1c = local_1c + '\x01';
                }
              }
              else {
                local_44 = local_44 * 10;
              }
            }
            local_34 = lVar9;
            if (local_1c == '\0') {
              local_70 = local_70 + 1;
              local_44 = (local_44 - 0x30) + local_1dc;
              if ((local_1ec == 0) || (local_20 = local_20 + -1, local_20 != 0)) {
                local_24 = local_24 + 1;
                local_1dc = __inc(param_1);
                lVar9 = local_34;
              }
              else {
                local_1c = '\x01';
              }
            }
            else {
              local_24 = local_24 - 1;
              FUN_0047bc70(local_1dc,param_1);
              lVar9 = local_34;
            }
          }
          if (local_6c != '\0') {
            local_44 = -local_44;
          }
        }
        else {
          while( true ) {
            local_34._4_4_ = (int)((ulonglong)lVar9 >> 0x20);
            local_34._0_4_ = (int)lVar9;
            if (local_1c != '\0') break;
            local_34 = lVar9;
            if (local_10 == 0x78) {
              if (DAT_004a87f4 < 2) {
                local_20c = *(ushort *)(PTR_DAT_004a85e8 + local_1dc * 2) & 0x80;
              }
              else {
                local_20c = FUN_0047f2b0(local_1dc,0x80);
              }
              if (local_20c == 0) {
                local_1c = local_1c + '\x01';
              }
              else {
                lVar9 = __allshl();
                local_34 = lVar9;
                local_1dc = FUN_0047bbb0(local_1dc);
              }
            }
            else {
              if (DAT_004a87f4 < 2) {
                local_210 = *(ushort *)(PTR_DAT_004a85e8 + local_1dc * 2) & 4;
              }
              else {
                local_210 = FUN_0047f2b0(local_1dc,4);
              }
              if (local_210 == 0) {
                local_1c = local_1c + '\x01';
              }
              else if (local_10 == 0x6f) {
                if ((int)local_1dc < 0x38) {
                  lVar9 = __allshl();
                  local_34 = lVar9;
                }
                else {
                  local_1c = local_1c + '\x01';
                }
              }
              else {
                __allshl();
                lVar9 = __allshl();
                local_34 = lVar9;
              }
            }
            if (local_1c == '\0') {
              local_70 = local_70 + 1;
              if ((local_1ec == 0) || (local_20 = local_20 + -1, local_20 != 0)) {
                local_24 = local_24 + 1;
                local_34 = local_34 + (int)(local_1dc - 0x30);
                local_1dc = __inc(param_1);
                lVar9 = local_34;
              }
              else {
                local_1c = '\x01';
                lVar9 = local_34 + (int)(local_1dc - 0x30);
              }
            }
            else {
              local_24 = local_24 - 1;
              FUN_0047bc70(local_1dc,param_1);
              lVar9 = local_34;
            }
          }
          if (local_6c != '\0') {
            lVar9 = CONCAT44(-(local_34._4_4_ + (uint)((int)local_34 != 0)),-(int)local_34);
          }
        }
        if (local_10 == 0x46) {
          local_70 = 0;
        }
        if (local_70 == 0) goto LAB_0047baaa;
        if (local_74 == '\0') {
          local_38 = local_38 + 1;
LAB_0047b4e1:
          if (local_1e0 == 0) {
            if (local_3c == '\0') {
              *(undefined2 *)local_40 = (undefined2)local_44;
            }
            else {
              *local_40 = local_44;
            }
          }
          else {
            *(longlong *)local_40 = lVar9;
          }
        }
        break;
      case 0x73:
        if ('\0' < local_18) {
          local_68 = local_68 + '\x01';
        }
        local_1e4 = (byte *)s_____004a642c;
        local_14 = local_14 - 1;
        goto LAB_0047ac40;
      case 0x7b:
        if ('\0' < local_18) {
          local_68 = local_68 + '\x01';
        }
        pbVar7 = param_2 + 1;
        local_1e4 = pbVar7;
        if (*pbVar7 == 0x5e) {
          local_1e4 = param_2 + 2;
          local_14 = local_14 - 1;
        }
LAB_0047ac40:
        param_2 = pbVar7;
        _memset(local_64,0,0x20);
        if ((local_10 == 0x7b) && (*local_1e4 == 0x5d)) {
          local_c = CONCAT31(local_c._1_3_,0x5d);
          local_59 = 0x20;
          local_1e4 = local_1e4 + 1;
        }
        while (*local_1e4 != 0x5d) {
          bVar1 = *local_1e4;
          local_1f0 = CONCAT31(local_1f0._1_3_,bVar1);
          pbVar7 = local_1e4 + 1;
          if (((bVar1 == 0x2d) && ((local_c & 0xff) != 0)) && (*pbVar7 != 0x5d)) {
            bVar1 = *pbVar7;
            local_1e4 = local_1e4 + 2;
            if ((uint)bVar1 <= (local_c & 0xff)) {
              bVar3 = (byte)local_c;
              local_c = CONCAT31(local_c._1_3_,bVar1);
              bVar1 = bVar3;
            }
            local_28 = CONCAT31(local_28._1_3_,bVar1);
            for (local_1f0 = CONCAT31(local_1f0._1_3_,(byte)local_c);
                (local_1f0 & 0xff) <= (local_28 & 0xff);
                local_1f0 = CONCAT31(local_1f0._1_3_,(byte)local_1f0 + 1)) {
              local_64[(int)(local_1f0 & 0xff) >> 3] =
                   local_64[(int)(local_1f0 & 0xff) >> 3] | (byte)(1 << ((byte)local_1f0 & 7));
            }
            local_c = local_c & 0xffffff00;
          }
          else {
            local_c = CONCAT31(local_c._1_3_,bVar1);
            local_64[(int)(uint)bVar1 >> 3] =
                 local_64[(int)(uint)bVar1 >> 3] | (byte)(1 << (bVar1 & 7));
            local_1e4 = pbVar7;
          }
        }
        if (*local_1e4 == 0) goto LAB_0047baaa;
        if (local_10 == 0x7b) {
          param_2 = local_1e4;
        }
        local_1e8 = local_40;
        local_24 = local_24 - 1;
        FUN_0047bc70(local_1dc,param_1);
        while( true ) {
          if ((local_1ec != 0) &&
             (iVar4 = local_20 + -1, bVar8 = local_20 == 0, local_20 = iVar4, lVar9 = local_34,
             bVar8)) goto LAB_0047af75;
          local_24 = local_24 + 1;
          local_1dc = __inc(param_1);
          if ((local_1dc == 0xffffffff) ||
             (bVar1 = (byte)local_1dc,
             ((int)(char)(local_64[(int)local_1dc >> 3] ^ local_14) & 1 << (bVar1 & 7)) == 0))
          break;
          if (local_74 == '\0') {
            if (local_68 == '\0') {
              *(byte *)local_40 = bVar1;
              local_40 = (uint *)((int)local_40 + 1);
            }
            else {
              local_1f4 = bVar1;
              if ((*(ushort *)(PTR_DAT_004a85e8 + (local_1dc & 0xff) * 2) & 0x8000) != 0) {
                local_24 = local_24 + 1;
                local_1f3 = __inc(param_1);
              }
              FUN_00484300(local_8,&local_1f4,DAT_004a87f4);
              *(undefined2 *)local_40 = local_8[0];
              local_40 = (uint *)((int)local_40 + 2);
            }
          }
          else {
            local_1e8 = (uint *)((int)local_1e8 + 1);
          }
        }
        local_24 = local_24 - 1;
        FUN_0047bc70(local_1dc,param_1);
        lVar9 = local_34;
LAB_0047af75:
        if (local_1e8 == local_40) goto LAB_0047baaa;
        if ((local_74 == '\0') && (local_38 = local_38 + 1, local_10 != 99)) {
          if (local_68 == '\0') {
            *(byte *)local_40 = 0;
          }
          else {
            *(undefined2 *)local_40 = 0;
          }
        }
      }
      local_2c = local_2c + '\x01';
      pbVar7 = param_2 + 1;
      local_34 = lVar9;
    }
    else {
      local_24 = local_24 + 1;
      bVar1 = *param_2;
      local_1dc = __inc(param_1);
      if (bVar1 != local_1dc) {
        local_24 = local_24 - 1;
        FUN_0047bc70(local_1dc,param_1);
        goto LAB_0047baaa;
      }
      pbVar7 = param_2 + 1;
      if ((*(ushort *)(PTR_DAT_004a85e8 + (local_1dc & 0xff) * 2) & 0x8000) != 0) {
        local_24 = local_24 + 1;
        bVar1 = param_2[1];
        uVar6 = __inc(param_1);
        if (bVar1 == uVar6) {
          local_24 = local_24 - 1;
          pbVar7 = param_2 + 2;
          goto LAB_0047ba81;
        }
        local_24 = local_24 - 1;
        FUN_0047bc70(uVar6,param_1);
        local_24 = local_24 - 1;
        FUN_0047bc70(local_1dc,param_1);
        goto LAB_0047baaa;
      }
    }
LAB_0047ba81:
    param_2 = pbVar7;
    if ((local_1dc == 0xffffffff) && ((*param_2 != 0x25 || (param_2[1] != 0x6e))))
    goto LAB_0047baaa;
  } while( true );
}
```

---

## FUN_0047bbb0 — 0x47bbb0

- Classification : internal
- Corps : `0x47bbb0–0x47bc07`
- État : pseudocode obtenu
- Evidence : `ev_84fa6a847bb87b9aa416afc857d704fc68d48df685cea1d2162e991eb85e3060`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47f2b0` — `FUN_0047f2b0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
uint FUN_0047bbb0(uint param_1)

{
  uint local_c;
  uint local_8;
  
  if (DAT_004a87f4 < 2) {
    local_8 = *(ushort *)(PTR_DAT_004a85e8 + param_1 * 2) & 4;
  }
  else {
    local_8 = FUN_0047f2b0(param_1,4);
  }
  if (local_8 == 0) {
    local_c = (param_1 & 0xffffffdf) - 7;
  }
  else {
    local_c = param_1;
  }
  return local_c;
}
```

---

## __inc — 0x47bc10

- Classification : internal
- Corps : `0x47bc10–0x47bc60`
- État : pseudocode obtenu
- Evidence : `ev_ac8547c91590ccbcfb4c099bcd58b976557080fbb6ecdd14995ca7d751958014`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x484870` — `FUN_00484870`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __inc
   
   Library: Visual Studio 2003 Debug */

uint __inc(int *param_1)

{
  uint local_8;
  
  param_1[1] = param_1[1] + -1;
  if (param_1[1] < 0) {
    local_8 = FUN_00484870(param_1);
  }
  else {
    local_8 = (uint)*(byte *)*param_1;
    *param_1 = *param_1 + 1;
  }
  return local_8;
}
```

---

## FUN_0047bc70 — 0x47bc70

- Classification : internal
- Corps : `0x47bc70–0x47bc8a`
- État : pseudocode obtenu
- Evidence : `ev_eb62891608362fb0b6f9fa292afb26a00d0bd10de9c2290c3d0007038ad09e4c`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x484a50` — `FUN_00484a50`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047bc70(int param_1,undefined4 param_2)

{
  if (param_1 != -1) {
    FUN_00484a50(param_1,param_2);
  }
  return;
}
```

---

## __whiteout — 0x47bc90

- Classification : internal
- Corps : `0x47bc90–0x47bcc8`
- État : pseudocode obtenu
- Evidence : `ev_c8bee5f429efd0b58d8810e9ce16708d3321168b7d993ab264ec1029482ca01b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47bc10` — `__inc`
- `0x4845c0` — `FUN_004845c0`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __whiteout
   
   Library: Visual Studio 2003 Debug */

undefined4 __whiteout(int *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  do {
    *param_1 = *param_1 + 1;
    uVar1 = __inc(param_2);
    iVar2 = FUN_004845c0(uVar1);
  } while (iVar2 != 0);
  return uVar1;
}
```

---

## FUN_0047bcd0 — 0x47bcd0

- Classification : internal
- Corps : `0x47bcd0–0x47bdb8`
- État : pseudocode obtenu
- Evidence : `ev_ca7a4d4b182e3043133fdccbac5c92b1cf70a8ea085f9a47660d1f76a480ee90`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x47bdc0` — `FUN_0047bdc0`
- `0x47c230` — `FUN_0047c230`
- `0x47ca30` — `FUN_0047ca30`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4
FUN_0047bcd0(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int *param_5,
            int param_6,undefined4 param_7,uint param_8)

{
  undefined4 uVar1;
  
  if (*param_5 == 0x19930520) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_0047ca30();
  }
  if ((param_1[1] & 0x66U) == 0) {
    if (param_5[3] != 0) {
      if (((*param_1 == -0x1f928c9d) && (0x19930520 < (uint)param_1[5])) &&
         (*(code **)(param_1[7] + 8) != (code *)0x0)) {
        uVar1 = (**(code **)(param_1[7] + 8))
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
        return uVar1;
      }
      FUN_0047bdc0(param_1,param_2,param_3,param_4,param_5,param_8 & 0xff,param_6,param_7,uVar1);
    }
  }
  else if ((param_5[1] != 0) && (param_6 == 0)) {
    FUN_0047c230(param_2,param_4,param_5,0xffffffff);
  }
  return 1;
}
```

---

## FUN_0047bdc0 — 0x47bdc0

- Classification : internal
- Corps : `0x47bdc0–0x47c047`
- État : pseudocode obtenu
- Evidence : `ev_73092d072a5a346f49a7a34462c4c61ef79e94b1cbc701789872b0d7ae35d071`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x473320` — `FUN_00473320`
- `0x47c050` — `FUN_0047c050`
- `0x47c170` — `FUN_0047c170`
- `0x47c360` — `CatchIt`
- `0x47c850` — `___DestructExceptionObject`
- `0x47c980` — `FUN_0047c980`
- `0x47ca30` — `FUN_0047ca30`
- `0x484c40` — `FUN_00484c40`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047bdc0(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,
                 void *param_4,_s_FuncInfo *param_5,char param_6,int param_7,
                 EHRegistrationNode *param_8)

{
  EHExceptionRecord *pEVar1;
  int iVar2;
  undefined4 in_stack_ffffffd0;
  int local_24;
  int local_20;
  _s_HandlerType *local_1c;
  undefined4 *local_18;
  uint local_14;
  _s_TryBlockMapEntry *local_10;
  uint local_c;
  int local_8;
  
  local_8 = *(int *)(param_2 + 8);
  if ((local_8 < -1) || (*(int *)(param_5 + 4) <= local_8)) {
    FUN_0047ca30();
  }
  pEVar1 = DAT_00632590;
  if ((((*(int *)param_1 == -0x1f928c9d) && (*(int *)(param_1 + 0x10) == 3)) &&
      (*(int *)(param_1 + 0x14) == 0x19930520)) && (*(int *)(param_1 + 0x1c) == 0)) {
    if (DAT_00632590 == (EHExceptionRecord *)0x0) {
      return;
    }
    param_1 = DAT_00632590;
    param_3 = DAT_00632594;
    iVar2 = FUN_00484c40(DAT_00632590,1);
    if (iVar2 == 0) {
      FUN_0047ca30();
    }
    if (((*(int *)pEVar1 == -0x1f928c9d) && (*(int *)(pEVar1 + 0x10) == 3)) &&
       ((*(int *)(pEVar1 + 0x14) == 0x19930520 && (*(int *)(pEVar1 + 0x1c) == 0)))) {
      in_stack_ffffffd0 = FUN_0047ca30();
    }
    else {
      in_stack_ffffffd0 = 0;
    }
  }
  if (((*(int *)param_1 == -0x1f928c9d) && (*(int *)(param_1 + 0x10) == 3)) &&
     (*(int *)(param_1 + 0x14) == 0x19930520)) {
    local_10 = (_s_TryBlockMapEntry *)FUN_00473320(param_5,param_7,local_8,&local_14,&local_c);
    for (; local_14 < local_c; local_14 = local_14 + 1) {
      if ((*(int *)local_10 <= local_8) && (local_8 <= *(int *)(local_10 + 4))) {
        local_1c = *(_s_HandlerType **)(local_10 + 0x10);
        for (local_24 = *(int *)(local_10 + 0xc); 0 < local_24; local_24 = local_24 + -1) {
          local_18 = *(undefined4 **)(*(int *)(param_1 + 0x1c) + 0xc);
          for (local_20 = **(int **)(*(int *)(param_1 + 0x1c) + 0xc); local_18 = local_18 + 1,
              0 < local_20; local_20 = local_20 + -1) {
            iVar2 = FUN_0047c170(local_1c,*local_18,*(undefined4 *)(param_1 + 0x1c));
            if (iVar2 != 0) {
              CatchIt(param_1,param_2,param_3,param_4,param_5,local_1c,(_s_CatchableType *)*local_18
                      ,local_10,param_7,param_8,(uchar)in_stack_ffffffd0);
              goto LAB_0047beef;
            }
          }
          local_1c = local_1c + 0x10;
        }
      }
LAB_0047beef:
      local_10 = local_10 + 0x14;
    }
    if (param_6 != '\0') {
      ___DestructExceptionObject(param_1,1);
    }
  }
  else if (param_6 == '\0') {
    FUN_0047c050(param_1,param_2,param_3,param_4,param_5,local_8,param_7,param_8);
  }
  else {
    FUN_0047c980();
  }
  return;
}
```

---

## FUN_0047c050 — 0x47c050

- Classification : internal
- Corps : `0x47c050–0x47c160`
- État : pseudocode obtenu
- Evidence : `ev_ace47b0f9fe86a5153ab1df72fc8d38a1d04674c856377dae8446818601d1603`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4731c0` — `FUN_004731c0`
- `0x473320` — `FUN_00473320`
- `0x47c360` — `CatchIt`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0047c050(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,
                 void *param_4,_s_FuncInfo *param_5,int param_6,int param_7,
                 EHRegistrationNode *param_8)

{
  int iVar1;
  uint in_stack_fffffff0;
  _s_TryBlockMapEntry *local_c;
  uint local_8;
  
  if ((DAT_00632598 == 0) ||
     (iVar1 = FUN_004731c0(param_1,param_2,param_3,param_4,param_5,param_7,param_8), iVar1 == 0)) {
    local_c = (_s_TryBlockMapEntry *)FUN_00473320(param_5,param_7,param_6,&stack0xfffffff0,&local_8)
    ;
    for (; in_stack_fffffff0 < local_8; in_stack_fffffff0 = in_stack_fffffff0 + 1) {
      if (((*(int *)local_c <= param_6) && (param_6 <= *(int *)(local_c + 4))) &&
         ((*(int *)(*(int *)(local_c + 0x10) + 4 + (*(int *)(local_c + 0xc) + -1) * 0x10) == 0 ||
          (*(char *)(*(int *)(*(int *)(local_c + 0x10) + 4 + (*(int *)(local_c + 0xc) + -1) * 0x10)
                    + 8) == '\0')))) {
        CatchIt(param_1,param_2,param_3,param_4,param_5,
                (_s_HandlerType *)(*(int *)(local_c + 0x10) + (*(int *)(local_c + 0xc) + -1) * 0x10)
                ,(_s_CatchableType *)0x0,local_c,param_7,param_8,(uchar)in_stack_fffffff0);
      }
      local_c = local_c + 0x14;
    }
  }
  return;
}
```

---

## FUN_0047c170 — 0x47c170

- Classification : internal
- Corps : `0x47c170–0x47c225`
- État : pseudocode obtenu
- Evidence : `ev_cfa04a3b6dce81102485ef47d51e63c250adc405795640fa6b5e348fba1f1254`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4774f0` — `_strcmp`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0047c170(uint *param_1,uint *param_2,uint *param_3)

{
  int iVar1;
  undefined4 local_8;
  
  if ((param_1[1] == 0) || (*(char *)(param_1[1] + 8) == '\0')) {
    local_8 = 1;
  }
  else if ((param_1[1] == param_2[1]) ||
          (iVar1 = _strcmp((char *)(param_1[1] + 8),(char *)(param_2[1] + 8)), iVar1 == 0)) {
    if (((((*param_2 & 2) == 0) || ((*param_1 & 8) != 0)) &&
        (((*param_3 & 1) == 0 || ((*param_1 & 1) != 0)))) &&
       (((*param_3 & 2) == 0 || ((*param_1 & 2) != 0)))) {
      local_8 = 1;
    }
    else {
      local_8 = 0;
    }
  }
  else {
    local_8 = 0;
  }
  return local_8;
}
```

---


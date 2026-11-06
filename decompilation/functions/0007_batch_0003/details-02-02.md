# 0007_batch_0003 — détails (2/2)

## FUN_0040bf98 — 0x40bf98

- Classification : internal
- Corps : `0x40bf98–0x40d3e0`
- État : pseudocode obtenu
- Evidence : `ev_5e71afc99fd4ab5273b4c07b5dc6e556212856d3462a715fb6a2569b19ce1407`
- Limites : Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again. Def-use links do not cross function boundaries and may omit memory aliasing, call side effects, or unresolved indirect flow. Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>. High p-code is decompiler-derived, not original source or runtime behavior. is_dead preserves the Java AST flag; decoded block members can retain that flag, so block_membership separately reports actual syntax-tree membership. Known omitted-edge counts cover links omitted from retained operations; omitted operations may contain additional uncounted links. Memory read/write effects include stack and temporary memory operations; they do not identify persistent state or business meaning. Operation, input, and def-use limits can truncate large functions; inspect truncation, omitted lower bounds, and known omitted counts before drawing conclusions. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Pseudocode is neither original source nor guaranteed to compile. References cover the complete Ghidra function-body AddressSet and exact entry. Dossier incoming edges omit sources owned by that function; procedure_references also retains those internal edges. Register variables, compiler-generated blocks, and pointer arithmetic remain decompiler artifacts. Resolved reference metadata identifies computed, indirect, external, call, jump, and data edges; unresolved targetless flows remain unknown, and function classifications distinguish thunks and externals. Synthetic Ghidra entry-point references without actionable memory sources are omitted. The Java bridge serializes one function request per Program and lets each decompilation run until it completes or the caller cancels. The Windows bridge uses authenticated IPv4 loopback because Node path-based IPC does not expose Java AF_UNIX sockets; the endpoint file contains no bearer token. The dossier combines Ghidra FunctionManager, Listing, ReferenceManager, BasicBlockModel, and decompiler observations; provider-specific pseudocode and assembly are not cross-provider text invariants. The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written. The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results. The target references PDB Float.pdb (GUID unknown, age (hex) 0, signature 3418386f, version NB10); Ghidra reports load state unknown. Original names and types may be missing; an empty name search does not prove a procedure is absent. Use list_procedures and address-based analysis to inspect recovered functions. REA does not admit a caller-selected PDB companion. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Types and calling conventions are Ghidra decompiler observations, not source declarations. Unresolved computed or indirect flows without target addresses are not represented as reference edges. Windows Ghidra P0 accepts native x86 and x86-64 PE applications and DLLs, and explicitly selected raw 6502 images; managed, hostile, sensitive, and mutable-path targets are unsupported. Windows sessions require the matching packaged Windows x64 native addon, local NTFS targets and runtimes, and Windows 10 or later. Native handles enforce path admission, private DACLs, and Job Object ownership automatically.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0040bf98(undefined4 *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7)

{
  bool bVar1;
  short sVar2;
  undefined2 uVar4;
  undefined4 uVar3;
  undefined2 extraout_var;
  int iVar5;
  undefined2 extraout_var_00;
  uint extraout_ECX;
  uint uVar6;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  undefined2 extraout_var_03;
  undefined2 extraout_var_04;
  undefined2 extraout_var_05;
  undefined2 extraout_var_06;
  undefined2 extraout_var_07;
  uint extraout_ECX_00;
  uint extraout_ECX_01;
  uint extraout_ECX_02;
  undefined2 extraout_var_08;
  undefined2 extraout_var_09;
  undefined2 extraout_var_10;
  undefined2 extraout_var_11;
  undefined2 extraout_var_12;
  undefined2 extraout_var_13;
  undefined2 extraout_var_14;
  undefined4 *puVar7;
  undefined4 *puVar8;
  bool bVar9;
  int iVar10;
  int local_f4;
  int local_f0;
  int local_e8;
  int local_e4;
  int local_e0;
  int local_dc;
  int local_d8;
  uint local_d4;
  int local_d0;
  int local_c4;
  int local_90;
  int local_8c;
  undefined2 local_84;
  int local_80;
  undefined4 local_74;
  byte *local_60;
  undefined4 local_5c [4];
  int local_4c;
  undefined4 local_48;
  byte *local_44;
  int *local_40;
  short local_3c;
  byte *local_38;
  int local_34;
  undefined2 local_30 [2];
  byte *local_2c;
  uint local_28;
  byte *local_24;
  int local_20;
  int local_1c;
  undefined1 *local_18;
  undefined1 *local_14;
  byte *local_10;
  int local_c;
  int local_8;
  
  puVar7 = param_1;
  puVar8 = local_5c;
  for (iVar5 = 5; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar8 = puVar8 + 1;
  }
  local_20 = param_4;
  if ((param_5 == 0) || (param_6 != 0x10000)) {
    local_f4 = 0;
  }
  else {
    local_f4 = 1;
  }
  local_c = local_f4;
  local_8 = 8;
  if (param_5 != 0) {
    if (*(short *)(param_2 + 0x58) == 1) {
      iVar5 = (int)*(short *)(param_2 + 0x46);
      if (iVar5 < 8) {
        local_8 = 8 - iVar5 / 2;
      }
      else {
        local_8 = (iVar5 + -8) / 2 + 4;
      }
    }
    else if (*(short *)(param_2 + 0x58) == 2) {
      local_8 = (int)*(short *)(param_2 + 0x46) / 2;
    }
    else if (*(short *)(param_2 + 0x58) == 3) {
      local_8 = 8 - (int)*(short *)(param_2 + 0x46) / 2;
    }
  }
  if ((((*(uint *)(param_2 + 0x1c) & 0x80) != 0) && (local_f4 != 0)) &&
     (0x1e < *(short *)(param_2 + 0x48))) {
    local_4c = param_4;
    iVar5 = *(short *)(param_2 + 0x48) + -0x1e;
    param_4 = param_4 + iVar5 + (iVar5 * iVar5) / 0x28;
  }
  local_1c = *(int *)(param_2 + 0x10);
  local_40 = (int *)thunk_FUN_004641de(*(undefined4 *)(param_2 + 0x14),local_1c);
  local_3c = *(short *)((int)local_40 + 0x16);
  if ((*(int *)(param_2 + 4) == 1) && ((local_1c == 0 || (local_1c == 5)))) {
    local_3c = DAT_004a4b70;
  }
  if (local_3c != -1) {
    local_30[0] = thunk_FUN_00456a6b(local_3c);
    local_48 = 0;
    bVar1 = false;
    local_80 = param_2;
    if (((*(uint *)(param_2 + 0x1c) & 0x10) != 0) && (local_c != 0)) {
      iVar5 = (int)*(short *)(param_2 + 0x48);
      bVar9 = *(int *)(param_2 + 0x14) != 4;
      bVar1 = true;
      local_74 = thunk_FUN_004106dd(bVar9,7);
      if (iVar5 < 0x10) {
        local_74 = thunk_FUN_004106dd(bVar9,iVar5 / 2);
      }
      else if (0x54 < iVar5) {
        local_74 = thunk_FUN_004106dd(bVar9,(100 - iVar5) / 2);
      }
      local_80 = thunk_FUN_00404c3b(local_74);
      if (iVar5 < 0x54) {
        local_84 = DAT_0049aca0;
        if (*(int *)(param_2 + 4) == 1) {
          local_84 = DAT_0049aca4;
        }
        local_48 = thunk_FUN_0040e864(local_84);
        if (*(int *)(param_2 + 4) == 1) {
          thunk_FUN_00404c5a(param_1,local_48,0,param_3,param_4);
          thunk_FUN_00404c5a(param_1,local_48,0x25,param_3,param_4);
        }
        else {
          thunk_FUN_004109a6(param_1,local_48,*(undefined4 *)(param_2 + 0xc),param_3,param_4,
                             local_74);
        }
        iVar5 = 0x54 - iVar5;
        if (iVar5 < 8) {
          local_80 = (int)(iVar5 * iVar5 + (iVar5 * iVar5 >> 0x1f & 7U)) >> 3;
        }
        else {
          local_80 = iVar5 * 2 + -8;
        }
        local_4c = param_4;
        local_80 = param_4 + local_80;
        param_4 = local_80;
      }
    }
    uVar4 = (undefined2)((uint)local_80 >> 0x10);
    if (((*(uint *)(param_2 + 0x1c) & 0x100) != 0) && (local_c != 0)) {
      local_8c = (int)*(short *)(param_2 + 0x44);
      if (local_8c < 0x14) {
        local_8c = local_8c / 5;
      }
      else if (1000 - local_8c < 0x14) {
        local_8c = (1000 - local_8c) / 5;
      }
      else {
        local_8c = 3;
      }
      uVar3 = thunk_FUN_004106dd(1,local_8c);
      thunk_FUN_00404c3b(uVar3);
      bVar1 = true;
      uVar4 = extraout_var;
    }
    local_48 = thunk_FUN_0040e864(CONCAT22(uVar4,local_30[0]));
    local_44 = (byte *)thunk_FUN_00456a87(CONCAT22(extraout_var_00,local_3c));
    if (local_44 != (byte *)0x0) {
      local_28 = (uint)*local_44 + (int)*(short *)(param_2 + 0x4a);
      if ((*(uint *)(param_2 + 0x1c) & 0x20) != 0) {
        local_28 = local_28 - 1;
      }
      if ((int)local_28 < (int)(uint)*local_44) {
        local_28 = (uint)*local_44;
      }
      if ((int)(uint)local_44[1] < (int)local_28) {
        local_28 = (uint)local_44[1];
      }
      if (local_8 < 8) {
        thunk_FUN_00410bd2(local_5c,local_48,local_28,param_3,param_4,local_8);
      }
      else if (bVar1) {
        thunk_FUN_00404c5a(local_5c,local_48,local_28,param_3,param_4);
      }
      else {
        thunk_FUN_00405265(local_5c,local_48,local_28,param_3,param_4,&DAT_004b28f0,0,param_6,
                           param_6,0);
        if ((((*(uint *)(param_2 + 0x1c) & 0x20) != 0) && (local_c != 0)) &&
           ((int)local_28 < (int)(uint)local_44[1])) {
          thunk_FUN_00410bd2(local_5c,local_48,local_28 + 1,param_3,param_4,
                             (int)*(short *)(param_2 + 0x48) / 3);
        }
      }
    }
    local_60 = (byte *)thunk_FUN_00456aca(local_3c);
    uVar6 = extraout_ECX;
    if ((*(int *)(param_2 + 4) == 2) && (uVar6 = *(uint *)(param_2 + 0x1c) & 1, uVar6 == 0)) {
      local_60 = (byte *)0x0;
    }
    uVar4 = (undefined2)(uVar6 >> 0x10);
    if (local_60 != (byte *)0x0) {
      if (param_5 == 0) {
        local_28 = (uint)*local_60;
      }
      else {
        local_90 = (int)*(short *)(param_2 + 0x3a);
        if (((*(int *)(param_2 + 4) == 1) && (*(int *)(param_2 + 0x14) == -1)) &&
           ((((int)*(char *)(param_2 + 0x22) & 1 << ((byte)DAT_0049f538 & 0x1f)) == 0 &&
            (local_90 < 0x5a)))) {
          local_90 = 0;
        }
        if (local_60[3] == 0) {
          local_28 = thunk_FUN_0040aaeb(*local_60,local_60[1],local_90 / (int)(uint)local_60[2]);
        }
        else {
          local_28 = thunk_FUN_0040ab05(*local_60,local_60[1],local_90 / (int)(uint)local_60[2]);
        }
      }
      if (local_8 < 8) {
        thunk_FUN_00410bd2(local_5c,local_48,local_28,param_3,param_4,local_8);
        uVar4 = extraout_var_01;
      }
      else if (bVar1) {
        thunk_FUN_00404c5a(local_5c,local_48,local_28,param_3,param_4);
        uVar4 = extraout_var_02;
      }
      else {
        thunk_FUN_00405265(local_5c,local_48,local_28,param_3,param_4,&DAT_004b28f0,0,param_6,
                           param_6,0);
        uVar4 = extraout_var_03;
      }
    }
    local_10 = (byte *)thunk_FUN_00456b0d(CONCAT22(uVar4,local_3c));
    uVar4 = extraout_var_11;
    if (local_10 != (byte *)0x0) {
      local_28 = (uint)*local_10;
      if (param_5 != 0) {
        uVar3 = thunk_FUN_0040ab05(0,0x14,(int)*(short *)(param_2 + 0x3c));
        local_28 = thunk_FUN_0040aab0(*local_10,local_10[1],0x14,uVar3);
      }
      if (local_8 < 8) {
        thunk_FUN_00410bd2(local_5c,local_48,local_28,param_3,param_4,local_8);
        uVar4 = extraout_var_12;
      }
      else if (bVar1) {
        thunk_FUN_00404c5a(local_5c,local_48,local_28,param_3,param_4);
        uVar4 = extraout_var_13;
      }
      else {
        thunk_FUN_00405265(local_5c,local_48,local_28,param_3,param_4,&DAT_004b28f0,0,param_6,
                           param_6,0);
        uVar4 = extraout_var_14;
      }
    }
    local_24 = (byte *)thunk_FUN_00456b4d(CONCAT22(uVar4,local_3c));
    uVar4 = extraout_var_04;
    if (local_24 != (byte *)0x0) {
      if ((param_5 == 0) || (*(short *)(param_2 + 0x3e) == -1)) {
        local_28 = (uint)*local_24;
      }
      else {
        iVar5 = (int)*(short *)(param_2 + 0x3e) / (int)(uint)local_24[2];
        if (local_24[3] == 0) {
          local_28 = thunk_FUN_0040aaeb(*local_24,local_24[1],iVar5);
        }
        else {
          local_28 = thunk_FUN_0040ab05(*local_24,local_24[1],iVar5);
        }
      }
      if (local_8 < 8) {
        thunk_FUN_00410bd2(local_5c,local_48,local_28,param_3,param_4,local_8);
        uVar4 = extraout_var_05;
      }
      else if (bVar1) {
        thunk_FUN_00404c5a(local_5c,local_48,local_28,param_3,param_4);
        uVar4 = extraout_var_06;
      }
      else {
        thunk_FUN_00405265(local_5c,local_48,local_28,param_3,param_4,&DAT_004b28f0,0,param_6,
                           param_6,0);
        uVar4 = extraout_var_07;
      }
    }
    local_18 = (undefined1 *)thunk_FUN_00456b8d(CONCAT22(uVar4,local_3c));
    uVar4 = (undefined2)(extraout_ECX_00 >> 0x10);
    if (local_18 != (undefined1 *)0x0) {
      local_28 = 0xffffffff;
      if (((*(uint *)(param_2 + 0x1c) & 4) == 0) || (param_5 == 0)) {
        uVar6 = extraout_ECX_00;
        if ((*(int *)(param_2 + 4) != 2) || (uVar6 = *(uint *)(param_2 + 0x1c) & 3, uVar6 != 0)) {
          local_28 = (uint)*(short *)(local_18 + 8);
        }
      }
      else {
        iVar5 = (int)*(short *)(param_2 + 0x40) / (int)(uint)(byte)local_18[2];
        if (local_18[3] == '\0') {
          local_28 = thunk_FUN_0040aaeb(*local_18,local_18[1],iVar5);
          uVar6 = extraout_ECX_02;
        }
        else {
          local_28 = thunk_FUN_0040ab05(*local_18,local_18[1],iVar5);
          uVar6 = extraout_ECX_01;
        }
      }
      uVar4 = (undefined2)(uVar6 >> 0x10);
      if (-1 < (int)local_28) {
        if (local_8 < 8) {
          thunk_FUN_00410bd2(local_5c,local_48,local_28,param_3,param_4,local_8);
          uVar4 = extraout_var_08;
        }
        else if (bVar1) {
          thunk_FUN_00404c5a(local_5c,local_48,local_28,param_3,param_4);
          uVar4 = extraout_var_09;
        }
        else {
          thunk_FUN_00405265(local_5c,local_48,local_28,param_3,param_4,&DAT_004b28f0,0,param_6,
                             param_6,0);
          uVar4 = extraout_var_10;
        }
      }
    }
    local_14 = (undefined1 *)thunk_FUN_00456bd0(CONCAT22(uVar4,local_3c));
    if (local_14 != (undefined1 *)0x0) {
      local_28 = 0xffffffff;
      bVar9 = false;
      if (local_c == 0) {
        local_28 = (uint)*(short *)(local_14 + 10);
      }
      else if ((*(uint *)(param_2 + 0x1c) & 2) == 0) {
        local_28 = (uint)*(short *)(local_14 + 10);
        bVar9 = *(int *)(param_2 + 0x24) != 0;
      }
      else {
        iVar5 = (int)*(short *)(param_2 + 0x42) / (int)(uint)(byte)local_14[2];
        if (local_14[3] == '\0') {
          local_28 = thunk_FUN_0040aaeb(*local_14,local_14[1],iVar5);
        }
        else {
          local_28 = thunk_FUN_0040ab05(*local_14,local_14[1],iVar5);
        }
        if (*(short *)(local_14 + 4) == -1) {
          bVar9 = false;
        }
        else {
          bVar9 = *(short *)(local_14 + 4) <= *(short *)(param_2 + 0x42);
        }
      }
      if (local_28 != 0xffffffff) {
        if (local_8 < 8) {
          thunk_FUN_00410bd2(local_5c,local_48,local_28,param_3,param_4,local_8);
        }
        else if (bVar1) {
          thunk_FUN_00404c5a(local_5c,local_48,local_28,param_3,param_4);
        }
        else {
          thunk_FUN_00405265(local_5c,local_48,local_28,param_3,param_4,&DAT_004b28f0,0,param_6,
                             param_6,0);
        }
      }
      if (bVar9) {
        iVar5 = *(int *)(param_2 + 0x10);
        sVar2 = DAT_0049aca8;
        if (((iVar5 != 0x25) && (sVar2 = DAT_0049acb0, iVar5 != 0x26)) &&
           (sVar2 = DAT_0049acac, iVar5 != 0x27)) {
          sVar2 = -1;
        }
        if (sVar2 != -1) {
          uVar3 = thunk_FUN_0040e864(sVar2);
          thunk_FUN_00410bd2(local_5c,uVar3,0,param_3 + *(short *)(local_14 + 6),
                             param_4 + *(short *)(local_14 + 8),local_8);
        }
      }
      if (((*(uint *)(param_2 + 0x1c) & 2) != 0) && (local_c != 0)) {
        if (*(int *)(param_2 + 0x10) == 6) {
          if (bVar9) {
            thunk_FUN_00428191(local_5c,4,
                               *(undefined4 *)(&DAT_006137bc + *(short *)(param_2 + 0x2e) * 0x4c),0,
                               param_3 + *(short *)(local_14 + 6),param_4 + *(short *)(local_14 + 8)
                               ,8);
          }
          if ((0x17 < (int)local_28) && ((int)local_28 < 0x27)) {
            thunk_FUN_00404770(local_5c,local_48,local_28 + 0x13,param_3,param_4);
          }
        }
        else if (*(int *)(param_2 + 0x10) == 8) {
          thunk_FUN_00428191(param_1,4,
                             *(undefined4 *)(&DAT_006137bc + *(short *)(param_2 + 0x2e) * 0x4c),0,
                             param_3 + *(short *)(local_14 + 6),param_4 + *(short *)(local_14 + 8),
                             ((int)*(short *)(param_2 + 0x42) << 3) /
                             (int)*(short *)(local_14 + 0xc));
        }
        else if (*(int *)(param_2 + 0x10) == 9) {
          if (bVar9) {
            thunk_FUN_00428191(param_1,4,
                               *(undefined4 *)(&DAT_006137bc + *(short *)(param_2 + 0x2e) * 0x4c),0,
                               param_3 + *(short *)(local_14 + 6),param_4 + *(short *)(local_14 + 8)
                               ,8);
          }
          local_c4 = (*(short *)(param_2 + 0x42) * 0xf) / (int)*(short *)(local_14 + 0xc) + 1;
          if ((0 < local_c4) && (local_c4 < 0x10)) {
            if (8 < local_c4) {
              local_c4 = 0x10 - local_c4;
            }
            uVar3 = thunk_FUN_0040ec89(s_v_nsupfx_0049ad94,1);
            thunk_FUN_00410bd2(param_1,uVar3,0,param_3 + 1,param_4 + -0x5a,local_c4);
          }
        }
      }
    }
    local_2c = (byte *)thunk_FUN_00456c13(local_3c);
    if (((local_2c != (byte *)0x0) && ((*(uint *)(param_2 + 0x1c) & 8) != 0)) && (param_5 != 0)) {
      local_28 = (uint)*local_2c;
      if (local_8 < 8) {
        thunk_FUN_00410bd2(local_5c,local_48,local_28,param_3,param_4,local_8);
      }
      else if (bVar1) {
        thunk_FUN_00404c5a(local_5c,local_48,local_28,param_3,param_4);
      }
      else {
        thunk_FUN_00405265(local_5c,local_48,local_28,param_3,param_4,&DAT_004b28f0,0,param_6,
                           param_6,0);
      }
    }
    local_38 = (byte *)thunk_FUN_00456c56(local_3c);
    if ((local_38 != (byte *)0x0) && (local_28 = __ftol(), 0 < (int)local_28)) {
      local_28 = (*local_38 - 1) + local_28;
      if ((int)(uint)local_38[1] < (int)local_28) {
        local_28 = (uint)local_38[1];
      }
      if (local_8 < 8) {
        thunk_FUN_00410bd2(local_5c,local_48,local_28,param_3,param_4,local_8);
      }
      else if (bVar1) {
        thunk_FUN_00404c5a(local_5c,local_48,local_28,param_3,param_4);
      }
      else {
        thunk_FUN_00405265(local_5c,local_48,local_28,param_3,param_4,&DAT_004b28f0,0,param_6,
                           param_6,0);
      }
    }
    if (((*(uint *)(param_2 + 0x1c) & 0x80) != 0) && (local_c != 0)) {
      local_d0 = (int)*(short *)(param_2 + 0x48);
      if (0x58 < *(short *)(param_2 + 0x48)) {
        local_d0 = 100 - *(short *)(param_2 + 0x48);
      }
      local_d0 = local_d0 / 3;
      if (*(int *)(param_2 + 4) == 1) {
        local_28 = DAT_0049ad1c;
      }
      else {
        local_28 = *(uint *)(&DAT_0049ad10 + *local_40 * 4);
      }
      if (local_d0 < 4) {
        local_28 = local_28 + local_d0;
      }
      else {
        local_28 = thunk_FUN_0040aaeb(local_28 + 4,local_28 + 8,local_d0 + -4);
      }
      uVar6 = local_28;
      iVar5 = param_3;
      iVar10 = local_20;
      uVar3 = thunk_FUN_0040e864(DAT_0049acc0);
      thunk_FUN_00404770(param_1,uVar3,uVar6,iVar5,iVar10);
    }
    if (((*(uint *)(param_2 + 0x1c) & 0x200) != 0) && (local_c != 0)) {
      if (*(int *)(param_2 + 4) == 1) {
        thunk_FUN_00411478(param_1,param_3 + -0x32,param_4 + -0x14,param_3 + 0x32,param_4 + 0x14,
                           DAT_00618e44 >> 1);
      }
      else {
        thunk_FUN_00411478(param_1,param_3 + -0x14,param_4 + -0x32,param_3 + 0x14,param_4,
                           DAT_00618e44 >> 1);
      }
    }
    if (((((*(int *)(param_2 + 0x14) == 4) && (param_5 != 0)) && (4 < *(int *)(param_2 + 0x24))) &&
        ((*(int *)(param_2 + 0x24) < 0x22 && (*(short *)(DAT_0049f53c * 2 + 0x618f78) != 0)))) &&
       (DAT_0049f538 == 2)) {
      local_d4 = (DAT_00618e44 >> 1 & 7) + 2;
      if (6 < local_d4) {
        local_d4 = 0xc - local_d4;
      }
      thunk_FUN_0040adb5(*(undefined4 *)(param_2 + 0x24),local_30,&local_28);
      uVar6 = local_28;
      iVar5 = param_3;
      iVar10 = param_4;
      uVar3 = thunk_FUN_0040e864(local_30[0]);
      thunk_FUN_00410bd2(param_1,uVar3,uVar6,iVar5,iVar10,local_d4);
    }
    if (((*(int *)(param_2 + 0x14) == DAT_0049f538) &&
        (local_34 = thunk_FUN_00450385(), local_34 != 0)) &&
       ((0 < param_7 || ((param_7 == -1 && (DAT_005c37f4 != 0)))))) {
      local_48 = thunk_FUN_0040ec89(s_bildicon_0049ada0,1);
      local_e4 = *(int *)(param_2 + 0x14) + 4;
      if (local_e4 < 4) {
        local_e4 = 4;
      }
      if (7 < local_e4) {
        local_e4 = 7;
      }
      local_d8 = param_3 + -0x14;
      local_dc = param_4 + -0x5a;
      for (local_e0 = 0; local_e0 < *(short *)(local_34 + 0x60); local_e0 = local_e0 + 1) {
        thunk_FUN_00404770(param_1,local_48,local_e4,local_d8,local_dc);
        local_d8 = local_d8 + 8;
        if (local_e0 == 4) {
          local_dc = local_dc + 8;
          local_d8 = param_3 + -0x14;
        }
      }
    }
    else if ((*(int *)(param_2 + 0x10) == 0x28) && ((*(uint *)(param_2 + 0x1c) & 0x7800) != 0)) {
      local_48 = thunk_FUN_0040ec89(s_bildicon_0049adac,1);
      if ((int)local_28 < 4) {
        local_28 = 4;
      }
      if (7 < (int)local_28) {
        local_28 = 7;
      }
      local_e8 = param_3 + -0xc;
      for (local_f0 = 0; local_f0 < 4; local_f0 = local_f0 + 1) {
        if ((*(uint *)(param_2 + 0x1c) & 0x800 << ((byte)local_f0 & 0x1f)) != 0) {
          thunk_FUN_00404770(param_1,local_48,local_f0 + 4,local_e8,param_4 + -0x43);
        }
        local_e8 = local_e8 + 8;
      }
    }
  }
  return;
}
```

---

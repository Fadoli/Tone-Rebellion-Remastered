# 0010_batch_0006 — détails (1/2)

## FUN_0041e569 — 0x41e569

- Classification : internal
- Corps : `0x41e569–0x41fd02`
- État : pseudocode obtenu
- Evidence : `ev_6c3ec9c58f2e2ec6ef837d8737ba3dfece6d35c11a918338523e688a6746c25a`
- Leviathan Spore note: in category 4 / subtype 9 runtime state 1, the update consumes the selected location record. For a qualifying owner/type pair it changes the location type at `+0x14` to 4, clears flag bit 1, calls `FUN_00453a5f`, then removes the Spore. If the target has flag `0x200`, it instead calls `FUN_004204bc` with the Spore's full current HP. User-provided gameplay context identifies Vspores as enemy constructors: converted sites can be basin slots that create a new enemy source or building slots for enemy construction; this meaning is not inferred from this function alone. This is the completion side of the mode-2 site search described in [enemy AI](../../behavior/enemy-ai.md#vspore-behavior-in-detail). Refreshed pseudocode Evidence `ev_ff0149927c5527e42ad97c0ccb0ecff046537edadb26eb9fecf60e1403b49d28`.
- Limites : Cancelling an active Ghidra request terminates its ephemeral database and discards session annotations. The selected target remains open; the next provider query imports the original artifact again. Def-use links do not cross function boundaries and may omit memory aliasing, call side effects, or unresolved indirect flow. Default-space addresses use lowercase 0x-prefixed hexadecimal; other address spaces use <percent-encoded-space>:0x<hex>. High p-code is decompiler-derived, not original source or runtime behavior. is_dead preserves the Java AST flag; decoded block members can retain that flag, so block_membership separately reports actual syntax-tree membership. Known omitted-edge counts cover links omitted from retained operations; omitted operations may contain additional uncounted links. Memory read/write effects include stack and temporary memory operations; they do not identify persistent state or business meaning. Operation, input, and def-use limits can truncate large functions; inspect truncation, omitted lower bounds, and known omitted counts before drawing conclusions. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Pseudocode is neither original source nor guaranteed to compile. References cover the complete Ghidra function-body AddressSet and exact entry. Dossier incoming edges omit sources owned by that function; procedure_references also retains those internal edges. Register variables, compiler-generated blocks, and pointer arithmetic remain decompiler artifacts. Resolved reference metadata identifies computed, indirect, external, call, jump, and data edges; unresolved targetless flows remain unknown, and function classifications distinguish thunks and externals. Synthetic Ghidra entry-point references without actionable memory sources are omitted. The Java bridge serializes one function request per Program and lets each decompilation run until it completes or the caller cancels. The Windows bridge uses authenticated IPv4 loopback because Node path-based IPC does not expose Java AF_UNIX sockets; the endpoint file contains no bearer token. The dossier combines Ghidra FunctionManager, Listing, ReferenceManager, BasicBlockModel, and decompiler observations; provider-specific pseudocode and assembly are not cross-provider text invariants. The imported Program and temporary project are ephemeral and deleted on close. Annotation operations edit session database metadata; original executable bytes are never written. The session serves operations only after Ghidra reports default auto-analysis complete; incomplete analysis does not expose partial results. The target references PDB Float.pdb (GUID unknown, age (hex) 0, signature 3418386f, version NB10); Ghidra reports load state unknown. Original names and types may be missing; an empty name search does not prove a procedure is absent. Use list_procedures and address-based analysis to inspect recovered functions. REA does not admit a caller-selected PDB companion. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Types and calling conventions are Ghidra decompiler observations, not source declarations. Unresolved computed or indirect flows without target addresses are not represented as reference edges. Windows Ghidra P0 accepts native x86 and x86-64 PE applications and DLLs, and explicitly selected raw 6502 images; managed, hostile, sensitive, and mutable-path targets are unsupported. Windows sessions require the matching packaged Windows x64 native addon, local NTFS targets and runtimes, and Windows 10 or later. Native handles enforce path admission, private DACLs, and Job Object ownership automatically.

### Appels directs

- `0x40100f` — `thunk_FUN_00420d97`
- `0x4012c6` — `thunk_FUN_00452c31`
- `0x40130c` — `thunk_FUN_0045575c`
- `0x40131b` — `thunk_FUN_00423068`
- `0x40135c` — `thunk_FUN_00452e2b`
- `0x4013de` — `thunk_FUN_0045c470`
- `0x401401` — `thunk_FUN_0041e427`
- `0x40145b` — `thunk_FUN_00425084`
- `0x401505` — `thunk_FUN_00422d27`
- `0x40156e` — `thunk_FUN_0041ff8b`
- `0x401573` — `thunk_FUN_00467101`
- `0x40160e` — `thunk_FUN_004211bb`
- `0x4016c7` — `thunk_FUN_00420ed9`
- `0x4016fe` — `thunk_FUN_00415fc6`
- `0x40173a` — `thunk_FUN_004672a6`
- `0x4017bc` — `thunk_FUN_0045f807`
- `0x4017c1` — `thunk_FUN_0042520e`
- `0x40186b` — `thunk_FUN_004656d6`
- `0x4018cf` — `thunk_FUN_0041ff2e`
- `0x401915` — `thunk_FUN_004502dc`
- `0x401924` — `thunk_FUN_00453a5f`
- `0x401933` — `thunk_FUN_00464242`
- `0x40195b` — `thunk_FUN_004527ee`
- `0x401965` — `thunk_FUN_00452a15`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x401a0f` — `thunk_FUN_0041ffc4`
- `0x401a69` — `thunk_FUN_00452ceb`
- `0x401a78` — `thunk_FUN_004251a2`
- `0x401ab4` — `thunk_FUN_00425296`
- `0x401adc` — `thunk_FUN_00416a9a`
- `0x401b63` — `thunk_FUN_0045c772`
- `0x401bae` — `thunk_FUN_00420829`
- `0x401bb8` — `thunk_FUN_00452e4d`
- `0x401d16` — `thunk_FUN_004204bc`
- `0x401d7f` — `thunk_FUN_00466b09`
- `0x401dac` — `thunk_FUN_004207f2`
- `0x401df2` — `thunk_FUN_0042000b`
- `0x401e4c` — `thunk_FUN_004200d2`
- `0x401e9c` — `thunk_FUN_00466c08`
- `0x401f0a` — `thunk_FUN_0042383d`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401f78` — `thunk_FUN_00420721`
- `0x401f91` — `thunk_FUN_00452eac`
- `0x4020c2` — `thunk_FUN_0045c797`
- `0x4020d1` — `thunk_FUN_00420188`
- `0x4020ea` — `thunk_FUN_004509da`
- `0x4020f9` — `thunk_FUN_0042219e`
- `0x402144` — `thunk_FUN_00420f28`
- `0x402199` — `thunk_FUN_004208eb`
- `0x402207` — `thunk_FUN_0045ddb8`
- `0x40225c` — `thunk_FUN_00421ec1`
- `0x402347` — `thunk_FUN_004503bd`
- `0x4023bf` — `thunk_FUN_0045c3bb`
- `0x4023dd` — `thunk_FUN_0041ff56`
- `0x4024be` — `thunk_FUN_004207c2`

### Chaînes référencées

- `0x49d28c` — "farloc"
- `0x49d294` — "C:\\float\\src\\floater.cpp"

### Pseudocode Ghidra

```c
void FUN_0041e569(void)

{
  bool bVar1;
  short sVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  undefined2 extraout_var;
  int *in_ECX;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  int iVar6;
  undefined2 extraout_var_03;
  int local_c0;
  short local_8c [2];
  int local_88;
  short local_84 [2];
  int local_80;
  short *local_7c;
  short *local_78;
  int local_74;
  undefined4 local_70;
  int local_6c;
  undefined4 local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  short local_54;
  int local_50;
  int local_4c;
  undefined4 local_48;
  int local_44;
  uint local_40;
  int local_3c;
  int local_38;
  undefined4 local_34;
  uint local_30;
  int local_2c;
  int local_28;
  int local_24;
  uint local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  undefined *local_10;
  undefined1 *local_c;
  int local_8;
  
  local_20 = (int)(in_ECX + -0x184dee) / 0x4c;
  if ((in_ECX[7] & 0x808U) != 0) {
    if ((in_ECX[7] & 0x800U) != 0) {
      iVar4 = in_ECX[9];
      in_ECX[9] = iVar4 + 1;
      if (in_ECX[9] < 0xc9) {
        return;
      }
      thunk_FUN_00467101(CONCAT22((short)((uint)(iVar4 + 1) >> 0x10),(undefined2)local_20));
      return;
    }
    if ((in_ECX[7] & 8U) != 0) {
      in_ECX[9] = in_ECX[9] + 1;
      iVar4 = thunk_FUN_00425296(8);
      if (in_ECX[9] <= iVar4) {
        return;
      }
      in_ECX[7] = in_ECX[7] & 0xfffffff7;
      thunk_FUN_00467101(local_20 & 0xffff);
      return;
    }
  }
  if ((in_ECX[0xb] == 0) || ((DAT_00618e44 + local_20) % 10 == 0)) {
    thunk_FUN_0042219e();
  }
  if (((*in_ECX == 4) && (9 < in_ECX[1])) && (in_ECX[1] < 0x12)) {
    local_2c = DAT_004bf11c;
    if (DAT_004bf11c < 0) {
      local_2c = 0;
    }
    if (4 < local_2c) {
      local_2c = 4;
    }
    if (1 < local_2c) {
      sVar2 = thunk_FUN_0041ff56();
      local_24 = (int)sVar2;
      local_28 = (0x1d4c / (local_2c + -1)) * local_24 * local_24;
      local_30 = local_28 + 15000;
      if ((DAT_00618e44 + local_20) % local_30 == 0) {
        local_34 = *(undefined4 *)(&DAT_0061f920 + *(short *)((int)in_ECX + 0xe) * 4);
        if ((local_24 == 0xb) && (sVar2 = thunk_FUN_0041ff2e(), sVar2 == 0)) {
          if (*(int *)(&DAT_0061f920 + *(short *)((int)in_ECX + 0xe) * 4) == 0) {
            thunk_FUN_0041ffc4(0);
            sVar2 = thunk_FUN_00420f28();
            local_38 = (int)sVar2 - (int)(short)in_ECX[8];
            if (local_38 < 0) {
              local_38 = 0;
            }
            thunk_FUN_0041ff8b(1);
            *(undefined2 *)(in_ECX + 2) = 0;
            sVar2 = thunk_FUN_00420f28();
            *(short *)(in_ECX + 8) = sVar2 - (short)(local_38 / 2);
          }
          else {
            thunk_FUN_004204bc((short)in_ECX[8],*in_ECX);
          }
        }
        else {
          thunk_FUN_0042000b();
        }
      }
    }
  }
  if ((in_ECX[0xb] == 0) && (in_ECX[0xf] != 0)) {
    thunk_FUN_004211bb();
  }
  local_14 = 0;
  if (((((in_ECX[0xb] != 0) && (in_ECX[0xb] != 6)) && (in_ECX[0xb] != 7)) &&
      ((in_ECX[0xb] != 0xf && (in_ECX[0xb] != 0x10)))) && ((in_ECX[7] & 0x411U) == 0)) {
    local_14 = thunk_FUN_00422d27();
  }
  iVar4 = *(short *)((int)in_ECX + 0xe) * 0x29e8;
  local_c = &DAT_005ec218 + iVar4;
  local_10 = &DAT_005ec640 + *(short *)((int)in_ECX + 0x32) * 0x60 + iVar4;
  local_8 = 0;
  local_1c = 0;
  local_18 = thunk_FUN_004251a2(in_ECX[0xb]);
  iVar4 = in_ECX[0xb] + -1;
  switch(iVar4) {
  case 0:
    if ((((local_14 != 0) && (local_8 = 1, *in_ECX == 4)) &&
        ((in_ECX[1] == 9 && ((*(int *)(local_10 + 4) == 1 || (*(int *)(local_10 + 4) == 0)))))) &&
       ((*(int *)(local_10 + 0x10) == 0 || (*(int *)(local_10 + 0x10) == 1)))) {
      if ((*(uint *)(local_10 + 0x1c) & 0x200) == 0) {
        *(undefined4 *)(local_10 + 0x14) = 4;
        *(uint *)(local_10 + 0x1c) = *(uint *)(local_10 + 0x1c) & 0xfffffffd;
        thunk_FUN_00453a5f();
        thunk_FUN_00467101(CONCAT22(extraout_var_00,(undefined2)local_20));
      }
      else {
        thunk_FUN_004204bc((short)in_ECX[8],0xffffffff);
      }
    }
    break;
  case 1:
    if ((short)in_ECX[0xd] == 0) {
      if (local_14 != 0) {
        in_ECX[7] = in_ECX[7] | 1;
        *(undefined2 *)(in_ECX + 0xd) = 1;
      }
    }
    else if ((short)in_ECX[0xd] < 10) {
      *(short *)(in_ECX + 0xd) = (short)in_ECX[0xd] + 1;
    }
    else {
      local_68 = thunk_FUN_004207f2();
      *(undefined2 *)(in_ECX + 0xd) = 1;
      sVar2 = thunk_FUN_00420f28();
      local_64 = (int)sVar2 - (int)(short)in_ECX[8];
      iVar4 = thunk_FUN_00464242(*in_ECX,in_ECX[1]);
      local_60 = (int)*(short *)(iVar4 + 8) - (int)*(short *)((int)in_ECX + 0x22);
      iVar4 = in_ECX[8];
      sVar2 = thunk_FUN_00420f28();
      if (sVar2 < (short)iVar4) {
        local_64 = 0;
      }
      sVar2 = *(short *)((int)in_ECX + 0x22);
      iVar4 = thunk_FUN_00464242(*in_ECX,in_ECX[1]);
      if (*(short *)(iVar4 + 8) < sVar2) {
        local_60 = 0;
      }
      if ((local_64 == 0) ||
         ((((short)in_ECX[0xc] != 0 && (local_60 != 0)) ||
          (iVar4 = thunk_FUN_0045ddb8(1), iVar4 == 0)))) {
        if (((local_60 == 0) || (((short)in_ECX[0xc] != 1 && (local_64 != 0)))) ||
           (iVar4 = thunk_FUN_0045ddb8(1), iVar4 == 0)) {
          in_ECX[7] = in_ECX[7] & 0xfffffffe;
          local_8 = 1;
        }
        else {
          *(short *)((int)in_ECX + 0x22) = *(short *)((int)in_ECX + 0x22) + 1;
        }
      }
      else {
        *(short *)(in_ECX + 8) = (short)in_ECX[8] + 1;
      }
    }
    break;
  case 2:
    if (((*(int *)(local_10 + 0x10) == 0x2a) || (*(short *)(local_10 + 0x18) != -1)) ||
       ((in_ECX[7] & 1U) != 0)) {
      if ((short)in_ECX[0xd] == 0) {
        thunk_FUN_00425084();
        if (local_14 != 0) {
          in_ECX[7] = in_ECX[7] | 1;
          *(undefined2 *)(in_ECX + 0xd) = 1;
        }
      }
      else if ((short)in_ECX[0xd] < 0x14) {
        *(short *)(in_ECX + 0xd) = (short)in_ECX[0xd] + 1;
      }
      else {
        local_58 = (int)(short)in_ECX[0xc];
        if ((*(int *)(local_10 + 4) == 0) && (iVar4 = thunk_FUN_00452c31(local_58), iVar4 != 0)) {
          in_ECX[6] = local_58;
          thunk_FUN_00452eac(local_58);
        }
        in_ECX[7] = in_ECX[7] & 0xfffffffe;
        local_8 = 1;
      }
    }
    else if (local_14 == 0) {
      thunk_FUN_00425084();
    }
    else {
      *(short *)(in_ECX + 0xd) = (short)in_ECX[0xd] + 1;
      local_5c = (int)(short)in_ECX[0xc];
      iVar4 = thunk_FUN_00452e4d(local_5c,(int)(short)in_ECX[0xd]);
      if (iVar4 == 0) {
        iVar4 = thunk_FUN_00452ceb(local_5c,*in_ECX);
        if (iVar4 == 0) {
          local_8 = 1;
        }
      }
      else {
        thunk_FUN_00425084();
        in_ECX[6] = local_5c;
        thunk_FUN_00452eac(local_5c);
        local_8 = 1;
      }
    }
    break;
  case 3:
    if (((*(int *)(local_10 + 0x10) == 0x2a) || (*(short *)(local_10 + 0x18) != -1)) ||
       ((in_ECX[7] & 1U) != 0)) {
      if ((short)in_ECX[0xd] == 0) {
        if (local_14 != 0) {
          in_ECX[7] = in_ECX[7] | 1;
          *(undefined2 *)(in_ECX + 0xd) = 1;
        }
      }
      else if ((short)in_ECX[0xd] < 0x14) {
        *(short *)(in_ECX + 0xd) = (short)in_ECX[0xd] + 1;
      }
      else {
        if ((*(int *)(local_10 + 4) == 0) && (in_ECX[6] != 0)) {
          iVar4 = thunk_FUN_004503bd(in_ECX[6],1,*in_ECX);
          if (iVar4 != 0) {
            in_ECX[6] = 0;
          }
        }
        else if ((((*(int *)(local_10 + 4) == 2) && ((4 < in_ECX[6] && (in_ECX[6] < 0x22)))) &&
                 ((*(uint *)(local_10 + 0x1c) & 1) == 0)) &&
                (iVar4 = thunk_FUN_004503bd(in_ECX[6],1,*in_ECX), iVar4 != 0)) {
          in_ECX[6] = 0;
        }
        in_ECX[7] = in_ECX[7] & 0xfffffffe;
        local_8 = 1;
      }
    }
    else if (((local_14 != 0) && (local_8 = 1, in_ECX[6] != 0)) &&
            (iVar4 = thunk_FUN_004503bd(in_ECX[6],1,*in_ECX), iVar4 != 0)) {
      in_ECX[6] = 0;
    }
    break;
  case 4:
    if (local_14 != 0) {
      local_8 = 1;
      if (*(int *)(local_10 + 4) == 0) {
        thunk_FUN_004527ee((int)(short)in_ECX[0xc],*in_ECX);
      }
    }
    break;
  case 5:
  case 6:
    local_3c = thunk_FUN_0042520e(in_ECX[0xb]);
    if ((short)in_ECX[0xd] == local_3c) {
      local_48 = 0;
      local_40 = 1;
      local_44 = 0;
      iVar4 = thunk_FUN_004207c2();
      if (iVar4 == 0) {
        iVar4 = thunk_FUN_00464242(*in_ECX,in_ECX[1]);
        iVar4 = thunk_FUN_0045575c(CONCAT22(extraout_var_01,*(undefined2 *)(iVar4 + 4)));
        if (*(short *)(iVar4 + 0x48) == -1) goto LAB_0041ec3e;
      }
      else {
LAB_0041ec3e:
        if (in_ECX[0xb] == 6) {
          local_44 = thunk_FUN_004200d2(&DAT_006137b8 + *(short *)((int)in_ECX + 0x32) * 0x13);
        }
        else {
          local_44 = thunk_FUN_00420188(local_10);
        }
        local_40 = (uint)(0 < local_44);
        local_48 = 1;
      }
      if (local_40 != 0) {
        uVar3 = thunk_FUN_00415fc6(in_ECX,local_48,local_44);
        *(undefined2 *)(in_ECX + 0x12) = uVar3;
      }
    }
    else if ((local_3c < (short)in_ECX[0xd]) && ((short)in_ECX[0x12] == -1)) {
      in_ECX[7] = in_ECX[7] & 0xffffffbf;
      local_8 = 1;
    }
    *(short *)(in_ECX + 0xd) = (short)in_ECX[0xd] + 1;
    break;
  case 7:
    sVar2 = thunk_FUN_004208eb(CONCAT22((short)((uint)iVar4 >> 0x10),
                                        *(undefined2 *)((int)in_ECX + 0x32)));
    local_6c = (int)sVar2;
    if ((local_6c != -1) || (local_14 != 0)) {
      local_8 = 1;
    }
    break;
  case 8:
    if (local_14 == 0) {
      if ((DAT_00618e44 + local_20 & 7) == 0) {
        sVar2 = thunk_FUN_00420829(CONCAT22((short)((uint)in_ECX[0xb] >> 0x10),
                                            *(undefined2 *)((int)in_ECX + 0x32)));
        local_4c = (int)sVar2;
        if (local_4c == -1) {
          sVar2 = thunk_FUN_00420d97(4,*(undefined2 *)((int)in_ECX + 0x32));
          local_4c = (int)sVar2;
        }
        if (local_4c != -1) {
          local_8 = 1;
        }
      }
    }
    else {
      local_8 = 1;
    }
    break;
  case 9:
    *(short *)(in_ECX + 0xd) = (short)in_ECX[0xd] + -1;
    if ((short)in_ECX[0xd] < 1) {
      local_8 = 1;
    }
    break;
  case 10:
    if ((short)in_ECX[0xd] == 0) {
      if (local_14 != 0) {
        iVar4 = thunk_FUN_00450385();
        if ((iVar4 == 0) || (iVar4 = thunk_FUN_0045c772(), iVar4 == 0)) {
          local_8 = 1;
        }
        else {
          thunk_FUN_00425084();
          thunk_FUN_0045c470(CONCAT22(extraout_var_03,(undefined2)local_20));
          *(undefined2 *)(in_ECX + 0xd) = 1;
        }
      }
    }
    else {
      *(short *)(in_ECX + 0xd) = (short)in_ECX[0xd] + 1;
    }
    break;
  case 0xb:
    if ((short)in_ECX[0xd] == 0) {
      if (local_14 != 0) {
        iVar4 = thunk_FUN_00450385();
        if ((iVar4 == 0) || (iVar4 = thunk_FUN_0045c772(), iVar4 == 0)) {
          local_8 = 1;
        }
        else {
          thunk_FUN_00425084();
          thunk_FUN_0045c797(CONCAT22(extraout_var,(undefined2)local_20));
          *(undefined2 *)(in_ECX + 0xd) = 1;
        }
      }
    }
    else {
      *(short *)(in_ECX + 0xd) = (short)in_ECX[0xd] + 1;
    }
    break;
  case 0xc:
    iVar4 = thunk_FUN_004502dc();
    if (iVar4 == 0) {
      thunk_FUN_00421ec1(0xffffffff);
    }
    else if (local_14 != 0) {
      thunk_FUN_00425084();
      if ((4 < iVar4) && (iVar4 < 0x22)) {
        in_ECX[6] = iVar4;
        thunk_FUN_00452a15();
      }
      local_8 = 1;
    }
    break;
  case 0xd:
    if ((local_14 != 0) &&
       (*(short *)(in_ECX + 0xd) = (short)in_ECX[0xd] + -1, (short)in_ECX[0xd] < 1)) {
      local_8 = 1;
    }
    break;
  case 0xe:
  case 0xf:
    local_50 = 0;
    local_54 = 0;
    if (in_ECX[0xf] != 0x14) {
      local_50 = 10;
      local_54 = thunk_FUN_00420721();
      if (local_54 != 0) {
        local_50 = (int)local_54;
      }
    }
    iVar4 = thunk_FUN_004672a6((int)(short)in_ECX[4],(int)*(short *)((int)in_ECX + 0x12),
                               (int)(short)in_ECX[10],(int)*(short *)((int)in_ECX + 0x2a));
    if (local_50 < iVar4) {
      iVar4 = thunk_FUN_00423068();
      if (iVar4 == 0) {
        thunk_FUN_00421ec1(0xffffffff);
      }
      else if ((in_ECX[7] & 0x411U) == 0) {
        thunk_FUN_00422d27();
      }
    }
    else {
      if (((local_54 == 0) && (in_ECX[0xb] == 0xf)) && (in_ECX[0xf] != 0x14)) {
        *(uint *)(&DAT_006137d4 + *(short *)((int)in_ECX + 0x32) * 0x4c) =
             *(uint *)(&DAT_006137d4 + *(short *)((int)in_ECX + 0x32) * 0x4c) | 0x10;
        in_ECX[7] = in_ECX[7] | 0x40;
      }
      local_8 = 1;
    }
    break;
  case 0x10:
    if ((short)in_ECX[0xd] < 1) {
      if (local_14 != 0) {
        if ((*(uint *)(local_10 + 0x1c) & 1) == 0) {
          local_8 = 1;
        }
        else {
          *(undefined2 *)(in_ECX + 0xd) = 1;
        }
      }
    }
    else if ((short)in_ECX[0xd] < 0x3c) {
      *(short *)(in_ECX + 0xd) = (short)in_ECX[0xd] + 1;
    }
    else if ((short)in_ECX[0xd] == 0x3c) {
      thunk_FUN_00466b09(*in_ECX,*(undefined2 *)((int)in_ECX + 0xe),(short)in_ECX[0xc]);
      local_74 = thunk_FUN_00466c08(*(undefined2 *)((int)in_ECX + 0xe),
                                    CONCAT22(extraout_var_02,(short)in_ECX[0xc]));
      if ((local_74 != 0) && ((*(uint *)(local_74 + 0x1c) & 1) == 0)) {
        local_74 = 0;
      }
      local_70 = 200;
      if (local_74 == 0) {
        local_70 = 500;
      }
      *(short *)(in_ECX + 0xd) = (short)local_70 + 0x78;
    }
    else if (0x3c < (short)in_ECX[0xd]) {
      if ((short)in_ECX[0xd] == 0x78) {
        local_78 = (short *)thunk_FUN_00466c08(*(undefined2 *)((int)in_ECX + 0xe),(short)in_ECX[0xc]
                                              );
        if ((local_78 != (short *)0x0) && ((*(uint *)(local_78 + 0xe) & 1) == 0)) {
          local_78 = (short *)0x0;
        }
        if (local_78 == (short *)0x0) {
          iVar4 = in_ECX[0xc];
          iVar6 = (short)iVar4 * 0x29e8;
          local_84[0] = 0x500;
          local_8c[0] = 0xa0;
          if ((in_ECX[0xf] == 6) || (in_ECX[0xf] == 8)) {
            iVar5 = *(short *)((int)in_ECX + 0x42) * 0x4c;
            local_84[0] = *(short *)(&DAT_006137c8 + iVar5);
            local_8c[0] = *(short *)(&DAT_006137ca + iVar5);
          }
          else if (in_ECX[0xf] == 9) {
            thunk_FUN_0041e427(CONCAT22((short)((uint)local_8c >> 0x10),
                                        *(undefined2 *)((int)in_ECX + 0x42)),local_84,local_8c);
          }
          else if (in_ECX[0xf] != 0xe) {
            local_84[0] = *(short *)(&DAT_005ec640 + *(short *)((int)in_ECX + 0x42) * 0x60 + iVar6);
            local_8c[0] = *(short *)((int)(&DAT_005ec640 +
                                          *(short *)((int)in_ECX + 0x42) * 0x60 + iVar6) + 2);
          }
          local_80 = 8000;
          local_7c = (short *)(&DAT_005ec640 + iVar6);
          for (local_88 = 0; local_88 < (short)(&DAT_005eebc0)[(short)iVar4 * 0x14f4];
              local_88 = local_88 + 1) {
            if ((((*(int *)(local_7c + 2) == 2) && ((*(uint *)(local_7c + 0xe) & 1) != 0)) &&
                (iVar6 = thunk_FUN_00420ed9(local_7c), iVar6 != 0)) &&
               (iVar6 = thunk_FUN_004672a6((int)*local_7c,(int)local_7c[1],(int)local_84[0],
                                           (int)local_8c[0]), iVar6 < local_80)) {
              local_78 = local_7c;
              local_80 = iVar6;
            }
            local_7c = local_7c + 0x30;
          }
          if (local_78 == (short *)0x0) {
            thunk_FUN_00414b64(s_C__float_src_floater_cpp_0049d294,0x2cd,s_farloc_0049d28c);
          }
        }
        *(short *)(in_ECX + 4) = *local_78;
        *(short *)(in_ECX + 10) = (short)in_ECX[4];
        *(short *)((int)in_ECX + 0x12) = local_78[1] + -0x1e;
        *(undefined2 *)((int)in_ECX + 0x2a) = *(undefined2 *)((int)in_ECX + 0x12);
        *(short *)((int)in_ECX + 0xe) = (short)in_ECX[0xc];
      }
      *(short *)(in_ECX + 0xd) = (short)in_ECX[0xd] + -1;
      if ((short)in_ECX[0xd] == 0x3c) {
        local_8 = 1;
      }
    }
    break;
  case 0x11:
    if ((local_14 != 0) &&
       (*(short *)(in_ECX + 0xd) = (short)in_ECX[0xd] + 1, 0x27 < (short)in_ECX[0xd])) {
      thunk_FUN_004509da(1);
      local_8 = 1;
    }
    break;
  case 0x12:
    local_8 = thunk_FUN_0042383d();
    break;
  case 0x14:
    *(short *)(in_ECX + 0xd) = (short)in_ECX[0xd] + 1;
    if ((short)in_ECX[0xd] == 1) {
      if (*in_ECX != 4) {
        thunk_FUN_00416a9a(5,in_ECX);
      }
    }
    else if ((short)in_ECX[0xd] == 0x19) {
      if (*in_ECX == 4) {
        thunk_FUN_00467101(local_20 & 0xffff);
      }
      else {
        in_ECX[1] = 8;
        thunk_FUN_0041ff8b(0);
        thunk_FUN_00425084();
      }
    }
    else if ((short)in_ECX[0xd] == 0x32) {
      local_8 = 1;
    }
  }
  if (local_8 != 0) {
    in_ECX[0xb] = 0;
    if (((in_ECX[1] == 8) && (in_ECX[0xf] != 0x13)) && (DAT_006191b4 == 0)) {
      in_ECX[0xf] = 9;
      *(undefined2 *)(in_ECX + 0x10) = *(undefined2 *)(&DAT_0061a580 + *in_ECX * 0x14a0);
      thunk_FUN_0045f807();
      uVar3 = thunk_FUN_00452e2b();
      *(undefined2 *)((int)in_ECX + 0x42) = uVar3;
      *(undefined2 *)((int)in_ECX + 0x46) = 0;
    }
    if ((in_ECX[1] == 4) && ((in_ECX[0xf] != 0x13 || ((in_ECX[7] & 0x200U) != 0)))) {
      in_ECX[7] = in_ECX[7] & 0xfffffdff;
      iVar4 = *in_ECX;
      iVar6 = in_ECX[3];
      if ((undefined2 *)(&DAT_006192b0 + (short)iVar6 * 100 + iVar4 * 0x14a0) != (undefined2 *)0x0)
      {
        thunk_FUN_0045c3bb();
        in_ECX[0xf] = 9;
        *(undefined2 *)(in_ECX + 0x10) =
             *(undefined2 *)(&DAT_006192b0 + (short)iVar6 * 100 + iVar4 * 0x14a0);
        *(undefined2 *)((int)in_ECX + 0x46) = 0;
        uVar3 = thunk_FUN_00452e2b();
        *(undefined2 *)((int)in_ECX + 0x42) = uVar3;
      }
    }
  }
  if ((in_ECX[7] & 0x2510U) != 0) {
    if ((in_ECX[7] & 0x100U) != 0) {
      if (((in_ECX[7] & 0x1000U) == 0) || (iVar4 = thunk_FUN_00425296(0x1000), in_ECX[9] <= iVar4))
      {
        iVar4 = thunk_FUN_00425296(0x100);
        if (iVar4 < in_ECX[9]) {
          in_ECX[7] = in_ECX[7] & 0xfffffeff;
        }
        else if (((in_ECX[9] < 0) && (in_ECX[0xb] != 0x13)) && (in_ECX[0xf] != 0x13)) {
          in_ECX[7] = in_ECX[7] & 0xfffffeff;
        }
        else {
          in_ECX[9] = in_ECX[9] + 1;
        }
      }
      else {
        in_ECX[7] = in_ECX[7] & 0xfffffeff;
        in_ECX[7] = in_ECX[7] & 0xffffefff;
      }
    }
    if ((in_ECX[7] & 0x2000U) != 0) {
      if (((in_ECX[7] & 0x2000U) == 0) || (iVar4 = thunk_FUN_00425296(0x2000), in_ECX[9] <= iVar4))
      {
        in_ECX[9] = in_ECX[9] + 1;
      }
      else {
        in_ECX[7] = in_ECX[7] & 0xffffdfff;
      }
    }
    if ((in_ECX[7] & 0x10U) != 0) {
      iVar4 = thunk_FUN_004656d6((int)*(short *)((int)in_ECX + 0xe),0xfffffffe);
      bVar1 = false;
      for (local_c0 = 0; local_c0 < iVar4; local_c0 = local_c0 + 1) {
        if (((int)*(short *)(&DAT_006137ea + (short)(&DAT_00618fb4)[local_c0] * 0x4c) == local_20)
           && ((*(uint *)(&DAT_006137d4 + (short)(&DAT_00618fb4)[local_c0] * 0x4c) & 0x40) != 0)) {
          bVar1 = true;
          break;
        }
      }
      if (!bVar1) {
        in_ECX[7] = in_ECX[7] & 0xffffffef;
      }
    }
    if (((in_ECX[7] & 0x400U) != 0) &&
       (*(short *)(&DAT_00618f96 + *(short *)((int)in_ECX + 0xe) * 2) == 0)) {
      in_ECX[7] = in_ECX[7] & 0xfffffbff;
    }
  }
  return;
}
```

---

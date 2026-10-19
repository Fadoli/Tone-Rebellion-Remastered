# 0011_batch_0007 — détails (1/6)

## FUN_0042383d — 0x42383d

- Classification : internal
- Corps : `0x42383d–0x4239e8`
- État : pseudocode obtenu
- Evidence : `ev_d8079c55e74cb30411c811377e1cc01c47f9e97fb7085c47510ae2fd163f0bb9`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x401127` — `thunk_FUN_0041660b`
- `0x40173a` — `thunk_FUN_004672a6`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4022ed` — `thunk_FUN_0042361d`

### Chaînes référencées

- `0x49d31c` — "mActionObj >= 0 && mActionObj < SPELL_NumSpells"
- `0x49d34c` — "C:\\float\\src\\floater.cpp"

### Pseudocode Ghidra

```c
undefined4 FUN_0042383d(void)

{
  bool bVar1;
  int iVar2;
  int in_ECX;
  undefined4 uVar3;
  
  if ((*(short *)(in_ECX + 0x30) < 0) || (0x16 < *(short *)(in_ECX + 0x30))) {
    uVar3 = thunk_FUN_00414b64(s_C__float_src_floater_cpp_0049d34c,0xcb4,
                               s_mActionObj_>__0____mActionObj_<_S_0049d31c);
  }
  else {
    uVar3 = 0;
  }
  if ((*(uint *)(in_ECX + 0x1c) & 0x200) == 0) {
    if ((*(int *)(&DAT_0049d230 + *(short *)(in_ECX + 0x30) * 4) == -1) ||
       (iVar2 = thunk_FUN_004672a6((int)*(short *)(in_ECX + 0x10),(int)*(short *)(in_ECX + 0x12),
                                   (int)*(short *)(in_ECX + 0x28),(int)*(short *)(in_ECX + 0x2a),
                                   uVar3),
       iVar2 <= *(int *)(&DAT_0049d230 + *(short *)(in_ECX + 0x30) * 4))) {
      *(undefined2 *)(in_ECX + 0x28) = *(undefined2 *)(in_ECX + 0x10);
      *(undefined2 *)(in_ECX + 0x2a) = *(undefined2 *)(in_ECX + 0x12);
      bVar1 = false;
      if ((*(short *)(in_ECX + 0x30) < 0) || (0x16 < *(short *)(in_ECX + 0x30))) {
        *(short *)(in_ECX + 0x34) = *(short *)(in_ECX + 0x34) + 1;
        if (*(short *)(in_ECX + 0x34) == 0x28) {
          bVar1 = true;
        }
      }
      else {
        *(short *)(in_ECX + 0x34) = *(short *)(in_ECX + 0x34) + 1;
        if (*(short *)(in_ECX + 0x34) == 10) {
          thunk_FUN_0041660b(in_ECX);
        }
        else if (399 < *(short *)(in_ECX + 0x34)) {
          bVar1 = true;
        }
      }
      if (bVar1) {
        *(uint *)(in_ECX + 0x1c) = *(uint *)(in_ECX + 0x1c) | 0x200;
      }
      uVar3 = 0;
    }
    else {
      if (((&DAT_0049d218)[*(short *)(in_ECX + 0x30)] & 2) != 0) {
        thunk_FUN_0042361d();
      }
      uVar3 = 0;
    }
  }
  else {
    *(short *)(in_ECX + 8) = *(short *)(in_ECX + 8) + 5;
    uVar3 = 1;
  }
  return uVar3;
}
```

---

## FUN_004239e9 — 0x4239e9

- Classification : internal
- Corps : `0x4239e9–0x425027`
- État : pseudocode obtenu
- Evidence : `ev_c455c0317556748b60ac119f64410c61eb6bcb16057896171345d3bd0be90b31`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40115e` — `thunk_FUN_00450847`
- `0x4016e0` — `thunk_FUN_00420635`
- `0x401726` — `thunk_FUN_00453b09`
- `0x40173a` — `thunk_FUN_004672a6`
- `0x4017cb` — `thunk_FUN_00453b76`
- `0x40180c` — `thunk_FUN_00420600`
- `0x40181b` — `thunk_FUN_00450978`
- `0x40186b` — `thunk_FUN_004656d6`
- `0x4018b1` — `thunk_FUN_0045f075`
- `0x4018cf` — `thunk_FUN_0041ff2e`
- `0x401915` — `thunk_FUN_004502dc`
- `0x401933` — `thunk_FUN_00464242`
- `0x401965` — `thunk_FUN_00452a15`
- `0x4019a1` — `thunk_FUN_00450385`
- `0x4019b5` — `thunk_FUN_0046562b`
- `0x401b59` — `thunk_FUN_00453b38`
- `0x401cd5` — `thunk_FUN_00453bb6`
- `0x401d16` — `thunk_FUN_004204bc`
- `0x401ee2` — `thunk_FUN_00453ade`
- `0x4020f9` — `thunk_FUN_0042219e`
- `0x402144` — `thunk_FUN_00420f28`
- `0x4022b1` — `thunk_FUN_0045d53c`
- `0x4023f6` — `thunk_FUN_00460c48`
- `0x4024eb` — `thunk_FUN_00450817`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004239e9(void)

{
  undefined *puVar1;
  short sVar2;
  short sVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  int *in_ECX;
  int *piVar7;
  uint uVar8;
  int iVar9;
  int local_148;
  int local_130;
  undefined *local_12c;
  int local_128;
  int local_11c;
  int local_10c;
  undefined *local_108;
  uint local_104;
  short *local_e8;
  int local_e4;
  undefined *local_d4;
  int local_d0;
  int local_b0;
  int local_ac;
  short local_9c;
  int local_98;
  int local_88;
  int local_74;
  int local_70;
  undefined2 local_54;
  int local_4c;
  undefined2 local_3c;
  int local_34;
  int local_24;
  int local_14;
  
  if ((in_ECX[0xb] == 0x13) && ((in_ECX[7] & 0x200U) == 0)) {
    switch((short)in_ECX[0xc]) {
    case 0:
      iVar5 = thunk_FUN_00450385();
      if (iVar5 != 0) {
        for (local_14 = 0; local_14 < 8; local_14 = local_14 + 1) {
          if ((*(short *)(iVar5 + 4 + local_14 * 2) != -1) &&
             (iVar6 = *(short *)(iVar5 + 4 + local_14 * 2) * 0x4c, iVar6 != -0x6137b8)) {
            sVar3 = thunk_FUN_00420f28();
            iVar9 = (int)sVar3;
            sVar3 = thunk_FUN_0041ff2e();
            if (*(short *)(&DAT_006137d8 + iVar6) < iVar9) {
              *(undefined2 *)((int)in_ECX + 0x32) = (&DAT_00618fb4)[local_14];
              local_24 = (int)*(short *)(&DAT_006137d8 + iVar6) + ((sVar3 + 2) * iVar9 >> 2);
              if (iVar9 < local_24) {
                local_24 = iVar9;
              }
              *(undefined2 *)(&DAT_006137d8 + iVar6) = (undefined2)local_24;
              if ((*(uint *)(&DAT_006137d4 + iVar6) & 0x908) == 0) {
                *(uint *)(&DAT_006137d4 + iVar6) = *(uint *)(&DAT_006137d4 + iVar6) | 0x2000;
                *(undefined4 *)(&DAT_006137dc + iVar6) = 0;
              }
            }
          }
        }
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 1:
      thunk_FUN_004656d6((int)*(short *)((int)in_ECX + 0xe),0xfffffffe);
      sVar2 = thunk_FUN_0041ff2e();
      sVar3 = *(short *)((int)in_ECX + 0xe);
      local_e8 = (short *)(&DAT_005ec640 + sVar3 * 0x29e8);
      for (local_e4 = 0; local_e4 < (short)(&DAT_005eebc0)[sVar3 * 0x14f4]; local_e4 = local_e4 + 1)
      {
        if (((local_e8 != (short *)0x0) && (9 < *(int *)(local_e8 + 8))) &&
           ((*(int *)(local_e8 + 8) < 0x16 &&
            (iVar5 = thunk_FUN_004672a6((int)(short)in_ECX[10],(int)*(short *)((int)in_ECX + 0x2a),
                                        (int)*local_e8,(int)local_e8[1]),
            iVar5 < sVar2 * 0x32 + 0xaf)))) {
          thunk_FUN_00453ade();
        }
        local_e8 = local_e8 + 0x30;
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 2:
      local_70 = 0;
      iVar5 = thunk_FUN_0046562b(*in_ECX,0xffffffff);
      for (local_74 = 0; local_74 < iVar5; local_74 = local_74 + 1) {
        iVar6 = (short)(&DAT_00618fb4)[local_74] * 0x4c;
        if (((&DAT_006137b8 + (short)(&DAT_00618fb4)[local_74] * 0x13 != (int *)0x0) &&
            ((&DAT_006137b8)[(short)(&DAT_00618fb4)[local_74] * 0x13] == *in_ECX)) &&
           (*(int *)(&DAT_006137bc + iVar6) == 0)) {
          sVar3 = thunk_FUN_0041ff2e();
          sVar2 = thunk_FUN_00420f28();
          if (*(short *)(&DAT_006137d8 + iVar6) < sVar2) {
            *(undefined2 *)((int)in_ECX + 0x32) = (&DAT_00618fb4)[local_74];
            *(short *)(&DAT_006137d8 + iVar6) = sVar2;
            if ((*(uint *)(&DAT_006137d4 + iVar6) & 0x908) == 0) {
              *(uint *)(&DAT_006137d4 + iVar6) = *(uint *)(&DAT_006137d4 + iVar6) | 0x2000;
              *(undefined4 *)(&DAT_006137dc + iVar6) = 0;
            }
            local_70 = local_70 + 1;
            if ((sVar3 + 1) * 5 <= local_70) break;
          }
        }
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 3:
      puVar1 = &DAT_005ec640 +
               *(short *)((int)in_ECX + 0x32) * 0x60 + *(short *)((int)in_ECX + 0xe) * 0x29e8;
      if (((puVar1 == (undefined *)0x0) || (*(int *)(puVar1 + 0x10) < 0x26)) ||
         (0x34 < *(int *)(puVar1 + 0x10))) {
        if ((puVar1 != (undefined *)0x0) && (*(int *)(puVar1 + 0x10) < 0x25)) {
          local_ac = 0;
          iVar5 = thunk_FUN_0046562b(*in_ECX,0xffffffff);
          for (local_b0 = 0; local_b0 < iVar5; local_b0 = local_b0 + 1) {
            iVar6 = (short)(&DAT_00618fb4)[local_b0] * 0x4c;
            if (((&DAT_006137b8)[(short)(&DAT_00618fb4)[local_b0] * 0x13] == *in_ECX) &&
               (*(int *)(&DAT_006137bc + iVar6) == 0)) {
              sVar3 = thunk_FUN_0041ff2e();
              sVar2 = thunk_FUN_00420f28();
              if (*(short *)(&DAT_006137d8 + iVar6) < sVar2) {
                *(undefined2 *)((int)in_ECX + 0x32) = (&DAT_00618fb4)[local_b0];
                *(short *)(&DAT_006137d8 + iVar6) = sVar2;
                local_ac = local_ac + 1;
                if (sVar3 * 2 + 2 <= local_ac) break;
              }
            }
          }
        }
      }
      else {
        uVar4 = thunk_FUN_00450978();
        *(undefined2 *)(puVar1 + 0x34) = uVar4;
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 4:
      sVar3 = thunk_FUN_0041ff2e();
      thunk_FUN_00453b09((int)sVar3);
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 5:
      sVar3 = thunk_FUN_0041ff2e();
      thunk_FUN_00453b09((int)sVar3);
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 6:
      sVar3 = thunk_FUN_0041ff2e();
      thunk_FUN_00453b09((int)sVar3);
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 7:
      in_ECX[7] = in_ECX[7] & 0xfffffeff;
      sVar3 = thunk_FUN_0041ff2e();
      iVar5 = thunk_FUN_004656d6((int)*(short *)((int)in_ECX + 0xe),0xfffffffe);
      iVar6 = sVar3 * 0x32 + 200;
      uVar8 = sVar3 * 5 + 0x11;
      for (local_10c = 0; local_10c < iVar5; local_10c = local_10c + 1) {
        piVar7 = &DAT_006137b8 + (short)(&DAT_00618fb4)[local_10c] * 0x13;
        if (((piVar7 != (int *)0x0) && (piVar7 != in_ECX)) &&
           (iVar9 = thunk_FUN_00420600(piVar7), iVar9 < iVar6)) {
          local_104 = uVar8;
          if (iVar6 >> 1 < iVar9) {
            local_104 = uVar8 - ((iVar9 * 2 - iVar6) * 7) / iVar6;
          }
          thunk_FUN_004204bc(local_104 & 0xffff,*in_ECX);
        }
      }
      sVar3 = *(short *)((int)in_ECX + 0xe);
      local_108 = &DAT_005ec640 + sVar3 * 0x29e8;
      for (local_10c = 0; local_10c < (short)(&DAT_005eebc0)[sVar3 * 0x14f4];
          local_10c = local_10c + 1) {
        thunk_FUN_00420635(local_108);
        if ((local_108 != (undefined *)0x0) &&
           (iVar5 = thunk_FUN_00420635(local_108), iVar5 < iVar6)) {
          local_104 = uVar8;
          if (iVar6 >> 1 < iVar5) {
            local_104 = uVar8 - ((iVar5 * 2 - iVar6) * 7) / iVar6;
          }
          thunk_FUN_00450817(local_104);
        }
        local_108 = local_108 + 0x60;
      }
      thunk_FUN_004204bc((short)in_ECX[8],*in_ECX);
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 8:
      iVar5 = thunk_FUN_004502dc();
      if ((4 < iVar5) && (iVar5 < 0x22)) {
        thunk_FUN_0045f075(iVar5,1);
        thunk_FUN_00452a15();
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 9:
      puVar1 = &DAT_005ec640 +
               *(short *)((int)in_ECX + 0x32) * 0x60 + *(short *)((int)in_ECX + 0xe) * 0x29e8;
      if (*(int *)(puVar1 + 4) == 0) {
        thunk_FUN_00450847(CONCAT22((short)((uint)puVar1 >> 0x10),*(undefined2 *)(puVar1 + 0x34)));
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 10:
      if ((&DAT_006137b8)[*(short *)((int)in_ECX + 0x32) * 0x13] == 4) {
        thunk_FUN_004204bc(*(undefined2 *)(&DAT_006137d8 + *(short *)((int)in_ECX + 0x32) * 0x4c),
                           *in_ECX);
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 0xb:
      iVar5 = thunk_FUN_00450385();
      if (iVar5 != 0) {
        for (local_4c = 0; local_4c < 8; local_4c = local_4c + 1) {
          if (*(short *)(iVar5 + 4 + local_4c * 2) != -1) {
            iVar6 = (int)*(short *)(iVar5 + 4 + local_4c * 2);
            iVar9 = iVar6 * 0x4c;
            piVar7 = &DAT_006137b8 + iVar6 * 0x13;
            if (((piVar7 != (int *)0x0) &&
                (*(undefined2 *)((int)in_ECX + 0x32) = (&DAT_00618fb4)[local_4c], -1 < *piVar7)) &&
               (*piVar7 < 4)) {
              sVar3 = thunk_FUN_00420f28();
              sVar2 = thunk_FUN_0041ff2e();
              *(short *)(&DAT_006137d8 + iVar9) = (sVar2 + 1) * *(short *)(&DAT_006137d8 + iVar9);
              if ((*(uint *)(&DAT_006137d4 + iVar9) & 0x908) == 0) {
                *(uint *)(&DAT_006137d4 + iVar9) = *(uint *)(&DAT_006137d4 + iVar9) | 0x2000;
                *(undefined4 *)(&DAT_006137dc + iVar9) = 0;
              }
              if ((int)sVar3 << 1 < (int)*(short *)(&DAT_006137d8 + iVar9)) {
                local_54 = (undefined2)((int)sVar3 << 1);
                *(undefined2 *)(&DAT_006137d8 + iVar9) = local_54;
              }
            }
          }
        }
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 0xc:
      iVar5 = thunk_FUN_00450385();
      if (iVar5 != 0) {
        sVar3 = thunk_FUN_0041ff2e();
        thunk_FUN_00453b38((int)sVar3);
        thunk_FUN_0045d53c();
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 0xd:
      iVar5 = thunk_FUN_00450385();
      if (iVar5 != 0) {
        sVar3 = thunk_FUN_0041ff2e();
        thunk_FUN_00453b76((int)sVar3);
        thunk_FUN_0045d53c();
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 0xe:
      iVar5 = thunk_FUN_0046562b(*in_ECX,0xffffffff);
      for (local_88 = 0; local_88 < iVar5; local_88 = local_88 + 1) {
        iVar6 = (short)(&DAT_00618fb4)[local_88] * 0x4c;
        if (((&DAT_006137b8 + (short)(&DAT_00618fb4)[local_88] * 0x13 != (int *)0x0) &&
            ((&DAT_006137b8)[(short)(&DAT_00618fb4)[local_88] * 0x13] == *in_ECX)) &&
           ((*(int *)(&DAT_006137bc + iVar6) == 0 &&
            ((*(uint *)(&DAT_006137d4 + iVar6) & 0x808) == 0)))) {
          sVar3 = thunk_FUN_0041ff2e();
          if (sVar3 < 2) {
            *(uint *)(&DAT_006137d4 + iVar6) = *(uint *)(&DAT_006137d4 + iVar6) | 0x100;
          }
          else if (sVar3 == 2) {
            *(uint *)(&DAT_006137d4 + iVar6) = *(uint *)(&DAT_006137d4 + iVar6) | 0x100;
            *(uint *)(&DAT_006137d4 + iVar6) = *(uint *)(&DAT_006137d4 + iVar6) | 0x1000;
          }
          *(undefined4 *)(&DAT_006137dc + iVar6) = 0;
        }
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 0xf:
      iVar5 = thunk_FUN_00450385();
      if (iVar5 != 0) {
        for (local_34 = 0; local_34 < 8; local_34 = local_34 + 1) {
          if (*(short *)(iVar5 + 4 + local_34 * 2) != -1) {
            iVar6 = (int)*(short *)(iVar5 + 4 + local_34 * 2);
            iVar9 = iVar6 * 0x4c;
            piVar7 = &DAT_006137b8 + iVar6 * 0x13;
            if (((piVar7 != (int *)0x0) &&
                (*(undefined2 *)((int)in_ECX + 0x32) = (&DAT_00618fb4)[local_34], -1 < *piVar7)) &&
               (*piVar7 < 4)) {
              iVar6 = thunk_FUN_00464242(*piVar7,*(undefined4 *)(&DAT_006137bc + iVar9));
              iVar6 = (int)*(short *)(iVar6 + 8) << 2;
              sVar3 = thunk_FUN_0041ff2e();
              *(short *)(&DAT_006137da + iVar9) = (sVar3 + 3) * *(short *)(&DAT_006137da + iVar9);
              if ((*(uint *)(&DAT_006137d4 + iVar9) & 0x908) == 0) {
                *(uint *)(&DAT_006137d4 + iVar9) = *(uint *)(&DAT_006137d4 + iVar9) | 0x2000;
                *(undefined4 *)(&DAT_006137dc + iVar9) = 0;
              }
              if (iVar6 < *(short *)(&DAT_006137da + iVar9)) {
                local_3c = (undefined2)iVar6;
                *(undefined2 *)(&DAT_006137da + iVar9) = local_3c;
              }
            }
          }
        }
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 0x10:
      puVar1 = &DAT_005ec640 +
               *(short *)((int)in_ECX + 0x32) * 0x60 + *(short *)((int)in_ECX + 0xe) * 0x29e8;
      if ((5 < *(int *)(puVar1 + 0x10)) && (*(int *)(puVar1 + 0x10) < 10)) {
        thunk_FUN_00450847(CONCAT22((short)((uint)puVar1 >> 0x10),*(undefined2 *)(puVar1 + 0x34)));
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 0x11:
      sVar3 = *(short *)((int)in_ECX + 0xe);
      local_d4 = &DAT_005ec640 + sVar3 * 0x29e8;
      for (local_d0 = 0; local_d0 < (short)(&DAT_005eebc0)[sVar3 * 0x14f4]; local_d0 = local_d0 + 1)
      {
        if ((5 < *(int *)(local_d4 + 0x10)) && (*(int *)(local_d4 + 0x10) < 10)) {
          thunk_FUN_00453ade();
        }
        local_d4 = local_d4 + 0x60;
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 0x12:
      iVar5 = thunk_FUN_004656d6((int)*(short *)((int)in_ECX + 0xe),0xfffffffe);
      local_11c = 0x11;
      for (local_130 = 0; local_130 < iVar5; local_130 = local_130 + 1) {
        piVar7 = &DAT_006137b8 + (short)(&DAT_00618fb4)[local_130] * 0x13;
        if (((piVar7 != (int *)0x0) && (piVar7 != in_ECX)) &&
           (iVar6 = thunk_FUN_00420600(piVar7), iVar6 < 0xfa)) {
          iVar9 = local_11c;
          if (0x7d < iVar6) {
            iVar9 = 0x11 - ((iVar6 * 2 + -0xfa) * 7) / 0xfa;
          }
          thunk_FUN_004204bc(iVar9,*in_ECX);
        }
      }
      sVar3 = *(short *)((int)in_ECX + 0xe);
      local_12c = &DAT_005ec640 + sVar3 * 0x29e8;
      for (local_130 = 0; local_130 < (short)(&DAT_005eebc0)[sVar3 * 0x14f4];
          local_130 = local_130 + 1) {
        thunk_FUN_00420635(local_12c);
        if ((local_12c != (undefined *)0x0) && (iVar5 = thunk_FUN_00420635(local_12c), iVar5 < 0xfa)
           ) {
          local_128 = 0x11;
          if (0x7d < iVar5) {
            local_128 = 0x11 - ((iVar5 * 2 + -0xfa) * 7) / 0xfa;
          }
          thunk_FUN_00450817(local_128);
        }
        local_12c = local_12c + 0x60;
      }
      in_ECX[7] = in_ECX[7] & 0xfffffeff;
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 0x13:
      iVar5 = thunk_FUN_00450385();
      if (iVar5 != 0) {
        sVar3 = thunk_FUN_0041ff2e();
        thunk_FUN_00453bb6((int)sVar3);
        thunk_FUN_0045d53c();
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 0x14:
      thunk_FUN_00460c48(CONCAT22((short)in_ECX[0xc] >> 0xf,*(undefined2 *)((int)in_ECX + 0xe)));
      iVar5 = thunk_FUN_004656d6((int)*(short *)((int)in_ECX + 0xe),0xfffffffe);
      for (local_148 = 0; local_148 < iVar5; local_148 = local_148 + 1) {
        if ((&DAT_006137b8)[(short)(&DAT_00618fb4)[local_148] * 0x13] == 4) {
          thunk_FUN_0042219e();
        }
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 0x15:
      sVar3 = thunk_FUN_0041ff2e();
      local_9c = sVar3 * 1000 + 1000;
      if (*in_ECX == 0) {
        _DAT_00618f5a = local_9c;
      }
      else if (*in_ECX == 1) {
        _DAT_00618f5c = local_9c;
      }
      else if (*in_ECX == 2) {
        _DAT_00618f5e = local_9c;
      }
      else if (*in_ECX == 3) {
        _DAT_00618f60 = local_9c;
      }
      iVar5 = thunk_FUN_0046562b(*in_ECX,0xffffffff);
      for (local_98 = 0; local_98 < iVar5; local_98 = local_98 + 1) {
        iVar6 = (short)(&DAT_00618fb4)[local_98] * 0x4c;
        if ((((&DAT_006137b8 + (short)(&DAT_00618fb4)[local_98] * 0x13 != (int *)0x0) &&
             ((&DAT_006137b8)[(short)(&DAT_00618fb4)[local_98] * 0x13] == *in_ECX)) &&
            (*(int *)(&DAT_006137bc + iVar6) == 0)) &&
           ((*(uint *)(&DAT_006137d4 + iVar6) & 0x908) == 0)) {
          *(uint *)(&DAT_006137d4 + iVar6) = *(uint *)(&DAT_006137d4 + iVar6) | 0x2000;
          *(undefined4 *)(&DAT_006137dc + iVar6) = 0;
        }
      }
      in_ECX[7] = in_ECX[7] | 0x200;
      break;
    case 0x16:
      if (*(int *)(&DAT_005ec650 +
                  *(short *)((int)in_ECX + 0xe) * 0x29e8 + *(short *)((int)in_ECX + 0x32) * 0x60) +
          -0x17 == (int)*(short *)(&DAT_0061a634 + *in_ECX * 0x14a0)) {
        thunk_FUN_00450847(30000);
      }
      in_ECX[7] = in_ECX[7] | 0x200;
    }
  }
  return;
}
```

---

## FUN_00425084 — 0x425084

- Classification : internal
- Corps : `0x425084–0x4251a1`
- État : pseudocode obtenu
- Evidence : `ev_c90fab99fa7691b34572e2c9eba925751fbdf77b63a570c51574e19c416b7e0b`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4016e0` — `thunk_FUN_00420635`
- `0x402347` — `thunk_FUN_004503bd`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00425084(void)

{
  short sVar1;
  int iVar2;
  int *in_ECX;
  undefined *local_18;
  int local_14;
  int local_10;
  undefined *local_c;
  
  if ((4 < in_ECX[6]) && (in_ECX[6] < 0x22)) {
    sVar1 = *(short *)((int)in_ECX + 0xe);
    local_c = (undefined *)0x0;
    local_18 = &DAT_005ec640 + sVar1 * 0x29e8;
    for (local_14 = 0; local_14 < (short)(&DAT_005eebc0)[sVar1 * 0x14f4]; local_14 = local_14 + 1) {
      if (((*(int *)(local_18 + 4) == 0) && (*(int *)(local_18 + 0x14) == -1)) &&
         (*(int *)(local_18 + 0x10) == 0)) {
        iVar2 = thunk_FUN_00420635(local_18);
        if ((iVar2 < local_10) || (local_c == (undefined *)0x0)) {
          local_c = local_18;
          local_10 = iVar2;
        }
      }
      local_18 = local_18 + 0x60;
    }
    if (local_c == (undefined *)0x0) {
      *(short *)(&DAT_006191fc + in_ECX[6] * 2 + *in_ECX * 0x14a0) =
           *(short *)(&DAT_006191fc + in_ECX[6] * 2 + *in_ECX * 0x14a0) + 1;
    }
    else {
      thunk_FUN_004503bd(in_ECX[6],1,*in_ECX);
    }
  }
  in_ECX[6] = 0;
  return;
}
```

---

## FUN_004251a2 — 0x4251a2

- Classification : internal
- Corps : `0x4251a2–0x42520d`
- État : pseudocode obtenu
- Evidence : `ev_4a090340fdb5742a1da4d57fcee3e5dab4e12ef3e9bc84cc8a5f77d842551412`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40130c` — `thunk_FUN_0045575c`
- `0x401933` — `thunk_FUN_00464242`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_004251a2(int param_1)

{
  int iVar1;
  undefined4 *in_ECX;
  int local_8;
  
  if ((param_1 < 6) || ((7 < param_1 && (param_1 != 0x13)))) {
    local_8 = 0x14;
  }
  else {
    iVar1 = thunk_FUN_00464242(*in_ECX,in_ECX[1]);
    iVar1 = thunk_FUN_0045575c(*(undefined2 *)(iVar1 + 4));
    local_8 = (int)*(short *)(iVar1 + 0x44);
  }
  return local_8;
}
```

---

## FUN_0042520e — 0x42520e

- Classification : internal
- Corps : `0x42520e–0x425295`
- État : pseudocode obtenu
- Evidence : `ev_d705e9b610a1d7163ee2704a995cd045b34d0c12c1e49dd3c356d174ce206641`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40130c` — `thunk_FUN_0045575c`
- `0x401933` — `thunk_FUN_00464242`
- `0x4024be` — `thunk_FUN_004207c2`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0042520e(int param_1)

{
  int iVar1;
  undefined4 *in_ECX;
  undefined4 local_c;
  int local_8;
  
  local_8 = 0;
  if ((param_1 == 6) || (param_1 == 7)) {
    local_c = in_ECX[1];
    iVar1 = thunk_FUN_004207c2();
    if (iVar1 != 0) {
      local_c = 0;
    }
    iVar1 = thunk_FUN_00464242(*in_ECX,local_c);
    iVar1 = thunk_FUN_0045575c(*(undefined2 *)(iVar1 + 4));
    local_8 = ((int)*(short *)(iVar1 + 0x3e) - (int)*(short *)(iVar1 + 0x38)) *
              (int)*(short *)(iVar1 + 0x3c);
  }
  return local_8;
}
```

---

## FUN_00425296 — 0x425296

- Classification : internal
- Corps : `0x425296–0x4252f9`
- État : pseudocode obtenu
- Evidence : `ev_d396d19e963f440badee51e257f40dbdc0fb6b31511f19947e1809f3216d7ec1`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- aucun relevé

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_00425296(int param_1)

{
  if (param_1 < 0x101) {
    if (param_1 == 0x100) {
      return 2000;
    }
    if (param_1 == 8) {
      return 0x28;
    }
  }
  else {
    if (param_1 == 0x1000) {
      return 0xdac;
    }
    if (param_1 == 0x2000) {
      return 0x2d;
    }
  }
  return 0x14;
}
```

---

## FUN_004252fa — 0x4252fa

- Classification : internal
- Corps : `0x4252fa–0x425387`
- État : pseudocode obtenu
- Evidence : `ev_b167d3cb2eae7790d14c1b84d495ac967fb8c04ad34e0f4acd791c8d1ee725a2`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x40116d` — `thunk_FUN_0041e4d9`
- `0x4017a3` — `thunk_FUN_0041e4c3`
- `0x401875` — `thunk_FUN_0040fc15`
- `0x401cee` — `thunk_FUN_0040fd80`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_004252fa(undefined4 param_1,int param_2)

{
  undefined4 *in_ECX;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_5c [19];
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_004915c9;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  thunk_FUN_0041e4c3();
  local_8 = 0;
  if (param_2 == 0) {
    puVar2 = local_5c;
    for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar2 = *in_ECX;
      in_ECX = in_ECX + 1;
      puVar2 = puVar2 + 1;
    }
    thunk_FUN_0040fd80(local_5c,0x4c);
  }
  else {
    thunk_FUN_0040fc15(local_5c,0x4c);
    puVar2 = local_5c;
    for (iVar1 = 0x13; iVar1 != 0; iVar1 = iVar1 + -1) {
      *in_ECX = *puVar2;
      puVar2 = puVar2 + 1;
      in_ECX = in_ECX + 1;
    }
  }
  local_8 = 0xffffffff;
  thunk_FUN_0041e4d9();
  *unaff_FS_OFFSET = local_10;
  return;
}
```

---

## FUN_00426fd0 — 0x426fd0

- Classification : internal
- Corps : `0x426fd0–0x42704a`
- État : pseudocode obtenu
- Evidence : `ev_6e955bf9310cdc3f643bbbd16bf122ccffc5893b26f16bd2fa2692f9a12f56c8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x472c6c` — `__ftol`
- `0x477314` — `FUN_00477314`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_00426fd0(int param_1)

{
  if ((*(uint *)(param_1 + 0x1c) & 8) == 0) {
    FUN_00477314((double)((DAT_00618e44 + (uint)*(byte *)(param_1 + 0x14)) % 0x30) *
                 0.13089958333333332);
  }
  __ftol();
  return;
}
```

---


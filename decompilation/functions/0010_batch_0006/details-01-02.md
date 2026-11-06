# 0010_batch_0006 — détails (2/3)

## FUN_00416ff8 — 0x416ff8

- Classification : internal
- Corps : `0x416ff8–0x4175f6`
- État : pseudocode obtenu
- Evidence : `ev_4bf3fa40e5e13170f21ec7216f3350d79ccb383de71014ab322ee52b3ebec592`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012a8` — `thunk_FUN_0041521a`
- `0x4012ad` — `thunk_FUN_0045339b`
- `0x40130c` — `thunk_FUN_0045575c`
- `0x4013e8` — `thunk_FUN_00415f1e`
- `0x40140b` — `thunk_FUN_00416e7d`
- `0x401433` — `thunk_FUN_00416ecf`
- `0x4014bf` — `thunk_FUN_00467260`
- `0x4015aa` — `thunk_FUN_004533a8`
- `0x4015af` — `thunk_FUN_004152bd`
- `0x4018cf` — `thunk_FUN_0041ff2e`
- `0x401933` — `thunk_FUN_00464242`
- `0x401951` — `thunk_FUN_00415063`
- `0x401dca` — `thunk_FUN_0041760b`
- `0x401e4c` — `thunk_FUN_004200d2`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x401fa5` — `thunk_FUN_004181a6`
- `0x401faf` — `thunk_FUN_004206fc`
- `0x401fd2` — `thunk_FUN_00417f44`
- `0x4020d1` — `thunk_FUN_00420188`
- `0x402298` — `thunk_FUN_00414ad0`
- `0x40250e` — `thunk_FUN_00414fbf`

### Chaînes référencées

- `0x49c358` — "mEffectInst[effectinst].src != -1"
- `0x49c37c` — "C:\\float\\src\\effects.cpp"
- `0x49c398` — "Bad Effect Type %d"
- `0x49c3ac` — "FALSE"
- `0x49c3b4` — "C:\\float\\src\\effects.cpp"

### Pseudocode Ghidra

```c
void FUN_00416ff8(short param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int in_ECX;
  undefined2 uVar4;
  undefined2 extraout_var;
  short local_34;
  short local_20 [2];
  short local_1c [2];
  int local_18;
  int local_14;
  int local_10;
  short *local_c;
  undefined1 *local_8;
  
  if (*(short *)(in_ECX + 0x1202 + param_1 * 0x14) == -1) {
    thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c37c,0x36f,
                       s_mEffectInst_effectinst__src______0049c358);
  }
  local_c = (short *)(in_ECX + 0x1202 + param_1 * 0x14);
  local_10 = in_ECX + local_c[7] * 0x30;
  uVar4 = (undefined2)((uint)local_10 >> 0x10);
  if ((local_c[8] & 0x80U) == 0) {
    if (((*(short *)(local_10 + 0x28) == -1) && (*(int *)(local_10 + 0xc) != 6)) ||
       (thunk_FUN_004181a6(CONCAT22(uVar4,param_1)), *(int *)(local_10 + 0xc) != 6)) {
      if (*(int *)(local_10 + 0xc) == 5) {
        thunk_FUN_0041760b(param_1);
      }
      else {
        local_14 = 0;
        local_8 = &DAT_005ec218 + local_c[4] * 0x29e8;
        iVar3 = thunk_FUN_00416ecf(param_1);
        if (iVar3 != 0) {
          if ((local_c[8] & 8U) == 0) {
            local_14 = 2;
          }
          else if ((local_c[8] & 0x10U) == 0) {
            if (*(short *)(local_10 + 0x2a) == -1) {
              local_14 = 2;
            }
            else {
              local_c[7] = *(short *)(local_10 + 0x2a);
              local_10 = in_ECX + local_c[7] * 0x30;
              if (*(int *)(local_10 + 0xc) == 2) {
                local_c[2] = 0;
                sVar1 = thunk_FUN_00467260(0x8000);
                local_c[5] = sVar1;
                sVar1 = thunk_FUN_00467260(0x8000);
                local_c[6] = sVar1;
              }
              else if ((local_c[8] & 4U) == 0) {
                sVar1 = *local_c;
                sVar2 = thunk_FUN_0041ff2e();
                local_c[2] = sVar2;
                if (local_c[2] < 0) {
                  local_c[2] = 0;
                }
                if (*(short *)(local_10 + 0x12) + -1 < (int)local_c[2]) {
                  local_c[2] = *(short *)(local_10 + 0x12) + -1;
                }
                if (*(int *)(local_10 + 0xc) == 1) {
                  iVar3 = thunk_FUN_00464242((&DAT_006137b8)[sVar1 * 0x13],
                                             *(undefined4 *)(&DAT_006137bc + sVar1 * 0x4c));
                  iVar3 = thunk_FUN_0045575c(CONCAT22(extraout_var,*(undefined2 *)(iVar3 + 4)));
                  if ((local_c[8] & 1U) == 0) {
                    local_34 = *(short *)(iVar3 + 0x4e);
                  }
                  else {
                    local_34 = -*(short *)(iVar3 + 0x4e);
                  }
                  local_c[5] = local_c[5] + local_34;
                  local_c[6] = local_c[6] + *(short *)(iVar3 + 0x50);
                }
              }
              local_c[3] = *(short *)(local_10 + 0x14 + local_c[2] * 2);
              if (*(int *)(local_10 + 0xc) != 4) {
                local_c[8] = local_c[8] | 0x10;
              }
              local_c[9] = 0;
              local_14 = 1;
            }
          }
          else {
            local_18 = 0;
            if ((local_c[8] & 2U) == 0) {
              if ((local_c[8] & 4U) == 0) {
                local_18 = thunk_FUN_004200d2(&DAT_006137b8 + local_c[1] * 0x13);
              }
              else {
                local_18 = thunk_FUN_004533a8(&DAT_006137b8 + local_c[1] * 0x13);
              }
            }
            else {
              local_18 = thunk_FUN_00420188(local_8 + local_c[1] * 0x60 + 0x428);
            }
            if (local_18 == 0) {
              local_14 = 2;
            }
            else {
              if (*(int *)(local_10 + 0xc) == 1) {
                thunk_FUN_00414fbf(local_c,local_20,local_1c);
                local_c[5] = local_20[0] - local_c[5];
                local_c[6] = local_1c[0] - local_c[6];
              }
              else {
                sVar1 = thunk_FUN_00467260(0xf);
                local_c[5] = sVar1 + -7;
                sVar1 = thunk_FUN_00467260(0xf);
                local_c[6] = sVar1 + -7;
              }
              sVar1 = thunk_FUN_00415f1e((&PTR_s_phyimp_0049bd58)[*(short *)(local_10 + 0x10)]);
              local_c[7] = sVar1;
              local_10 = in_ECX + local_c[7] * 0x30;
              local_c[2] = (short)(local_18 / 2);
              if (local_c[2] < 0) {
                local_c[2] = 0;
              }
              if (*(short *)(local_10 + 0x12) + -1 < (int)local_c[2]) {
                local_c[2] = *(short *)(local_10 + 0x12) + -1;
              }
              local_c[3] = *(short *)(local_10 + 0x14 + local_c[2] * 2);
              local_c[8] = local_c[8] & 0xffd7;
              local_c[9] = 0;
              local_14 = 1;
            }
          }
        }
        if (local_14 == 0) {
          switch(*(undefined4 *)(local_10 + 0xc)) {
          case 0:
          case 3:
          case 4:
            thunk_FUN_00415063(local_10,local_c);
            break;
          case 1:
            thunk_FUN_0041521a(local_10,local_c);
            if (200 < local_c[9]) {
              local_14 = 2;
            }
            break;
          case 2:
            thunk_FUN_004152bd(local_10,local_c);
            break;
          default:
            thunk_FUN_00414ad0(s_Bad_Effect_Type__d_0049c398,
                               *(undefined4 *)
                                (in_ECX + 0xc + *(short *)(in_ECX + 0x1210 + param_1 * 0x14) * 0x30)
                              );
            thunk_FUN_00414b64(s_C__float_src_effects_cpp_0049c3b4,0x406,s_FALSE_0049c3ac);
          }
          local_c[9] = local_c[9] + 1;
        }
        if (local_14 == 2) {
          if (((local_c[8] & 4U) == 0) || (99 < *local_c)) {
            if (*local_c < 0x100) {
              thunk_FUN_004206fc(param_1);
            }
          }
          else {
            thunk_FUN_0045339b(param_1);
          }
          thunk_FUN_00416e7d(param_1);
        }
      }
    }
  }
  else {
    thunk_FUN_00417f44(CONCAT22(uVar4,param_1));
  }
  return;
}
```

---

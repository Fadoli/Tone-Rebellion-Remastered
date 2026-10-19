# 0015_batch_0011 — détails (2/3)

## FUN_0044c609 — 0x44c609

- Classification : internal
- Corps : `0x44c609–0x44c8e6`
- État : pseudocode obtenu
- Evidence : `ev_cc87568cd410ea8824952f032f34ef9aab72c5ba7073d4c2b1610f301154659d`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x5f` — `USER32.DLL::GetParent`
- `EXTERNAL:0x60` — `USER32.DLL::PostMessageA`
- `EXTERNAL:0x61` — `USER32.DLL::SendDlgItemMessageA`
- `EXTERNAL:0x62` — `USER32.DLL::GetDlgItem`
- `EXTERNAL:0x63` — `USER32.DLL::SetFocus`
- `EXTERNAL:0x68` — `USER32.DLL::SetWindowLongA`
- `EXTERNAL:0x6c` — `USER32.DLL::SendMessageA`
- `0x401118` — `thunk_FUN_0044aa7e`
- `0x4011f9` — `thunk_FUN_0042ea1a`
- `0x40132a` — `FID_conflict:_AfxIsEqualGUID`
- `0x4018d4` — `thunk_FUN_0044ac6a`
- `0x4018de` — `thunk_FUN_0044ab7a`
- `0x402275` — `thunk_FUN_0044c292`
- `0x4023c9` — `thunk_FUN_0044c0ec`
- `0x402482` — `thunk_FUN_0042e8e7`

### Chaînes référencées

- `0x4a21a8` — "ServiceProvider"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0044c609(HWND param_1,int param_2,uint param_3,int param_4)

{
  HWND hWnd;
  int iVar1;
  undefined2 extraout_var;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  undefined4 local_84;
  WPARAM local_80;
  undefined1 local_7c [80];
  undefined1 local_2c [40];
  
  if (param_2 == 0x4e) {
    iVar1 = *(int *)(param_4 + 8);
    if (iVar1 == -0xd1) {
      thunk_FUN_0044ac6a();
      return 1;
    }
    if (iVar1 == -0xcf) {
      thunk_FUN_0044ac6a();
      if (_DAT_004a1958 != -1) {
        DAT_004a1954 = DAT_004a1958;
        iVar1 = thunk_FUN_0044ab7a(CONCAT22(extraout_var,DAT_004a1958));
        if (iVar1 != 0) {
          return 1;
        }
        thunk_FUN_0044c0ec(0x29);
      }
      SetWindowLongA(param_1,0,-1);
      return 1;
    }
    if (iVar1 == -200) {
      lParam = 2;
      wParam = 0;
      Msg = 0x470;
      hWnd = GetParent(param_1);
      PostMessageA(hWnd,Msg,wParam,lParam);
      return 1;
    }
  }
  else {
    if (param_2 == 0x110) {
      SendDlgItemMessageA(param_1,0x3eb,0x30,DAT_005e1ef4,1);
      DAT_005e2828 = GetDlgItem(param_1,0x3fd);
      if (DAT_005e2828 == (HWND)0x0) {
        return 1;
      }
      thunk_FUN_0044aa7e(0,0);
      for (local_80 = 0; (int)local_80 < (int)DAT_005e1f50; local_80 = local_80 + 1) {
        SendMessageA(DAT_005e2828,0x181,0xffffffff,(LPARAM)(&DAT_005e2d78 + local_80 * 0x68));
      }
      SetFocus(DAT_005e2828);
      _DAT_004a1958 = 0;
      local_84 = 0x27;
      if ((DAT_005e3174 != 0) &&
         (iVar1 = thunk_FUN_0044c292(s_ServiceProvider_004a21a8,local_2c,&local_84), iVar1 == 0)) {
        thunk_FUN_0042ea1a(local_7c,local_2c,0x27);
        thunk_FUN_0042e8e7(local_7c,&DAT_005e1ee0);
        for (local_80 = 0; (int)local_80 < (int)DAT_005e1f50; local_80 = local_80 + 1) {
          iVar1 = FID_conflict__AfxIsEqualGUID(&DAT_005e1ee0,&DAT_005e2d60 + local_80 * 0x68);
          if (iVar1 != 0) {
            _DAT_004a1958 = local_80;
            break;
          }
        }
      }
      SendMessageA(DAT_005e2828,0x186,_DAT_004a1958,0);
      _DAT_004a1958 = SendMessageA(DAT_005e2828,0x188,0,0);
      return 1;
    }
    if ((param_2 == 0x111) && (param_3 >> 0x10 == 1)) {
      _DAT_004a1958 = SendMessageA(DAT_005e2828,0x188,0,0);
      return 1;
    }
  }
  return 0;
}
```

---

---

## FUN_0044c8e7 — 0x44c8e7

- Classification : internal
- Corps : `0x44c8e7–0x44cac9`
- État : pseudocode obtenu
- Evidence : `ev_ad780708e3beb10cacc4e6d161688e6e22dfe58dcb30dddb6cef8e7dc96f34ed`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x5f` — `USER32.DLL::GetParent`
- `EXTERNAL:0x60` — `USER32.DLL::PostMessageA`
- `EXTERNAL:0x61` — `USER32.DLL::SendDlgItemMessageA`
- `EXTERNAL:0x68` — `USER32.DLL::SetWindowLongA`
- `0x4018d4` — `thunk_FUN_0044ac6a`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
undefined4 FUN_0044c8e7(HWND param_1,int param_2,uint param_3,int param_4)

{
  int iVar1;
  HWND hWnd;
  LRESULT LVar2;
  UINT Msg;
  WPARAM wParam;
  LPARAM lParam;
  
  if (param_2 == 0x4e) {
    iVar1 = *(int *)(param_4 + 8);
    if (iVar1 == -0xd1) {
      thunk_FUN_0044ac6a();
      return 1;
    }
    if (iVar1 == -0xcf) {
      if (DAT_005e1e90 != 0) {
        SetWindowLongA(param_1,0,0x83);
      }
      return 1;
    }
    if (iVar1 == -200) {
      lParam = 3;
      wParam = 0;
      Msg = 0x470;
      hWnd = GetParent(param_1);
      PostMessageA(hWnd,Msg,wParam,lParam);
      return 1;
    }
  }
  else {
    if (param_2 == 0x110) {
      SendDlgItemMessageA(param_1,0x3ec,0x30,DAT_005e1ef4,1);
      SendDlgItemMessageA(param_1,0x404,0x30,DAT_005e2d58,1);
      SendDlgItemMessageA(param_1,0x403,0x30,DAT_005e2d58,1);
      SendDlgItemMessageA(param_1,0x403,0xf1,1,0);
      SendDlgItemMessageA(param_1,0x404,0xf1,0,0);
      DAT_005e1e90 = 1;
      return 1;
    }
    if ((param_2 == 0x111) && (param_3 >> 0x10 == 0)) {
      if ((param_3 & 0xffff) == 0x403) {
        LVar2 = SendDlgItemMessageA(param_1,0x403,0xf0,1,0);
        if (LVar2 == 1) {
          DAT_005e1e90 = 1;
        }
        return 1;
      }
      if ((param_3 & 0xffff) == 0x404) {
        LVar2 = SendDlgItemMessageA(param_1,0x404,0xf0,1,0);
        if (LVar2 == 1) {
          DAT_005e1e90 = 0;
        }
        return 1;
      }
    }
  }
  return 0;
}
```

---

---

## FUN_0044caca — 0x44caca

- Classification : internal
- Corps : `0x44caca–0x44d01f`
- État : pseudocode obtenu
- Evidence : `ev_92b8e5b357c53452c7fad7bbbac576d5d8c70ceffa4b6fa44b851881706356a5`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `EXTERNAL:0x5b` — `USER32.DLL::GetDlgItemTextA`
- `EXTERNAL:0x5c` — `USER32.DLL::KillTimer`
- `EXTERNAL:0x5d` — `USER32.DLL::SetDlgItemTextA`
- `EXTERNAL:0x5e` — `USER32.DLL::SetTimer`
- `EXTERNAL:0x5f` — `USER32.DLL::GetParent`
- `EXTERNAL:0x60` — `USER32.DLL::PostMessageA`
- `EXTERNAL:0x61` — `USER32.DLL::SendDlgItemMessageA`
- `EXTERNAL:0x62` — `USER32.DLL::GetDlgItem`
- `EXTERNAL:0x63` — `USER32.DLL::SetFocus`
- `EXTERNAL:0x68` — `USER32.DLL::SetWindowLongA`
- `EXTERNAL:0x6c` — `USER32.DLL::SendMessageA`
- `0x4011e5` — `thunk_FUN_0042e9e9`
- `0x4014e2` — `thunk_FUN_0044afcc`
- `0x4015dc` — `thunk_FUN_0044aed8`
- `0x4018d4` — `thunk_FUN_0044ac6a`
- `0x401e38` — `thunk_FUN_0042e690`
- `0x401f64` — `thunk_FUN_00414b64`
- `0x4020a9` — `thunk_FUN_0044ab4c`
- `0x40213f` — `thunk_FUN_0044c271`
- `0x402275` — `thunk_FUN_0044c292`
- `0x402441` — `thunk_FUN_0044c250`

### Chaînes référencées

- `0x4a21b8` — "ServiceProvider"
- `0x4a21c8` — "PlayerName"
- `0x4a21d4` — "iIndex!=LB_ERR && iIndex < NETNumSessions"
- `0x4a2200` — "C:\\float\\src\\network.cpp"
- `0x4a221c` — "success"
- `0x4a2224` — "C:\\float\\src\\network.cpp"
- `0x4a2240` — "PlayerName"
- `0x4a224c` — "CONNECT_TYPE!=-1"
- `0x4a2260` — "C:\\float\\src\\network.cpp"

### Pseudocode Ghidra

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0044caca(HWND param_1,undefined4 param_2,uint param_3,int param_4)

{
  int iVar1;
  UINT UVar2;
  HWND pHVar3;
  undefined4 uVar4;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 uVar5;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  WPARAM WVar6;
  LPARAM LVar7;
  int local_88;
  undefined1 local_80 [80];
  undefined1 local_30 [40];
  undefined4 local_8;
  
  switch(param_2) {
  case 0x4e:
    switch(*(undefined4 *)(param_4 + 8)) {
    case 0xffffff2f:
      KillTimer(param_1,0);
      thunk_FUN_0044ac6a();
      uVar4 = 1;
      break;
    default:
      goto switchD_0044cb09_caseD_4f;
    case 0xffffff31:
      KillTimer(param_1,0);
      if (DAT_005e3174 != 0) {
        thunk_FUN_0042e690(&DAT_005e1ee0,local_80);
        thunk_FUN_0042e9e9(local_30,local_80,0x4e);
        thunk_FUN_0044c271(s_ServiceProvider_004a21b8,local_30,0x27);
        thunk_FUN_0044c250(s_PlayerName_004a21c8,&DAT_005e1fd8,0x47);
      }
      _DAT_004a195c = SendMessageA(DAT_005e30f0,0x188,0,0);
      if ((_DAT_004a195c == 0xffffffff) ||
         (uVar5 = extraout_var, (int)DAT_005e3118 <= (int)_DAT_004a195c)) {
        thunk_FUN_00414b64(s_C__float_src_network_cpp_004a2200,0x755,
                           s_iIndex__LB_ERR____iIndex_<_NETNu_004a21d4);
        uVar5 = extraout_var_00;
      }
      iVar1 = thunk_FUN_0044afcc(CONCAT22(uVar5,DAT_004a195c),&DAT_005e1fd8);
      if (iVar1 == 0) {
        thunk_FUN_00414b64(s_C__float_src_network_cpp_004a2224,0x758,s_success_004a221c);
      }
      SetWindowLongA(param_1,0,0x84);
      uVar4 = 1;
      break;
    case 0xffffff32:
      KillTimer(param_1,0);
      uVar4 = 1;
      break;
    case 0xffffff38:
      UVar2 = GetDlgItemTextA(param_1,0x402,&DAT_005e1fd8,0x46);
      if ((UVar2 == 0) || (_DAT_004a195c == 0xffffffff)) {
        LVar7 = 1;
        WVar6 = 0;
        UVar2 = 0x470;
        pHVar3 = GetParent(param_1);
        PostMessageA(pHVar3,UVar2,WVar6,LVar7);
      }
      else {
        LVar7 = 3;
        WVar6 = 0;
        UVar2 = 0x470;
        pHVar3 = GetParent(param_1);
        PostMessageA(pHVar3,UVar2,WVar6,LVar7);
      }
      SetFocus(DAT_005e30f0);
      uVar4 = 1;
    }
    break;
  case 0x110:
    SendDlgItemMessageA(param_1,0x3f0,0x30,DAT_005e2d58,1);
    SendDlgItemMessageA(param_1,0x3f1,0x30,DAT_005e2d58,1);
    local_8 = 0x47;
    DAT_005e1fd8 = 0;
    if ((DAT_005e3174 != 0) &&
       (iVar1 = thunk_FUN_0044c292(s_PlayerName_004a2240,&DAT_005e1fd8,&local_8), iVar1 == 0)) {
      SetDlgItemTextA(param_1,0x402,&DAT_005e1fd8);
    }
    DAT_005e30f0 = GetDlgItem(param_1,0x400);
    uVar5 = extraout_var_01;
    if (DAT_004a1954 == -1) {
      thunk_FUN_00414b64(s_C__float_src_network_cpp_004a2260,0x774,s_CONNECT_TYPE___1_004a224c);
      uVar5 = extraout_var_02;
    }
    if ((DAT_005e30f0 != (HWND)0x0) &&
       (iVar1 = thunk_FUN_0044ab4c(CONCAT22(uVar5,DAT_004a1954)), iVar1 != 0)) {
      SetTimer(param_1,0,3000,(TIMERPROC)0x0);
    }
  case 0x113:
    if (DAT_005e30f0 == (HWND)0x0) {
      uVar4 = 1;
    }
    else {
      thunk_FUN_0044aed8(0,0);
      _DAT_004a195c = SendMessageA(DAT_005e30f0,0x188,0,0);
      SendMessageA(DAT_005e30f0,0x184,0,0);
      for (local_88 = 0; local_88 < DAT_005e3118; local_88 = local_88 + 1) {
        SendMessageA(DAT_005e30f0,0x181,0xffffffff,*(LPARAM *)(&DAT_005e17a8 + local_88 * 0x50));
      }
      if (_DAT_004a195c != 0xffffffff) {
        SendMessageA(DAT_005e30f0,0x186,_DAT_004a195c,0);
        _DAT_004a195c = SendMessageA(DAT_005e30f0,0x188,0,0);
      }
      uVar4 = 1;
    }
    break;
  case 0x111:
    if (param_3 >> 0x10 == 1) {
      _DAT_004a195c = SendMessageA(DAT_005e30f0,0x188,0,0);
      UVar2 = GetDlgItemTextA(param_1,0x402,&DAT_005e1fd8,0x46);
      if ((UVar2 == 0) || (_DAT_004a195c == -1)) {
        LVar7 = 1;
        WVar6 = 0;
        UVar2 = 0x470;
        pHVar3 = GetParent(param_1);
        PostMessageA(pHVar3,UVar2,WVar6,LVar7);
      }
      else {
        LVar7 = 3;
        WVar6 = 0;
        UVar2 = 0x470;
        pHVar3 = GetParent(param_1);
        PostMessageA(pHVar3,UVar2,WVar6,LVar7);
      }
      return 1;
    }
    if (((param_3 & 0xffff) == 0x402) && (param_3 >> 0x10 == 0x300)) {
      UVar2 = GetDlgItemTextA(param_1,0x402,&DAT_005e1fd8,0x46);
      if ((UVar2 == 0) || (_DAT_004a195c == 0xffffffff)) {
        LVar7 = 1;
        WVar6 = 0;
        UVar2 = 0x470;
        pHVar3 = GetParent(param_1);
        PostMessageA(pHVar3,UVar2,WVar6,LVar7);
      }
      else {
        LVar7 = 3;
        WVar6 = 0;
        UVar2 = 0x470;
        pHVar3 = GetParent(param_1);
        PostMessageA(pHVar3,UVar2,WVar6,LVar7);
      }
    }
  default:
switchD_0044cb09_caseD_4f:
    uVar4 = 0;
  }
  return uVar4;
}
```

---

---

## FUN_0044e440 — 0x44e440

- Classification : internal
- Corps : `0x44e440–0x44e48e`
- État : pseudocode obtenu
- Evidence : `ev_875dbfd40c7764617cbbeb079c9825b52298a38de981ecfc3711162a0a809792`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4010b9` — `thunk_FUN_00429ebe`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
void FUN_0044e440(void)

{
  undefined4 uVar1;
  int local_c;
  
  for (local_c = 0; local_c < 8; local_c = local_c + 1) {
    DAT_004a257b = (char)local_c + '0';
    uVar1 = thunk_FUN_00429ebe(&DAT_004a2574,0);
    *(undefined4 *)(&DAT_005e4c30 + local_c * 4) = uVar1;
  }
  return;
}
```

---

---

## FUN_0044e48f — 0x44e48f

- Classification : internal
- Corps : `0x44e48f–0x44e4f7`
- État : pseudocode obtenu
- Evidence : `ev_603f454f2f767950881722a3298d4e33f61e1efb956b030356c5667b8e501bee`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4012a3` — `thunk_FUN_0046c17b`
- `0x48b100` — `__strcmpi`

### Chaînes référencées

- `0x4a24e8` — "TRIBE0"

### Pseudocode Ghidra

```c
int FUN_0044e48f(void)

{
  int iVar1;
  int iVar2;
  int local_10;
  
  iVar1 = thunk_FUN_0046c17b();
  if (iVar1 != 0) {
    for (local_10 = 0; local_10 < 8; local_10 = local_10 + 1) {
      iVar2 = __strcmpi((char *)(iVar1 + 0x20),s_TRIBE0_004a24e8 + local_10 * 0x10);
      if (iVar2 == 0) {
        return local_10;
      }
    }
  }
  return -1;
}
```

---

---

## FUN_0044e4f8 — 0x44e4f8

- Classification : internal
- Corps : `0x44e4f8–0x44e612`
- État : pseudocode obtenu
- Evidence : `ev_692b7d30a87f3044765a52264546a7ccade65e9667ae8532562f62f4b2813ef8`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x476ce4` — `FUN_00476ce4`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
int FUN_0044e4f8(int param_1,int param_2)

{
  float10 fVar1;
  int local_c;
  
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    fVar1 = (float10)FUN_00476ce4((double)((param_1 - *(int *)(&DAT_004a24c8 + local_c * 4)) *
                                           (param_1 - *(int *)(&DAT_004a24c8 + local_c * 4)) +
                                          (param_2 - *(int *)(&DAT_004a24d8 + local_c * 4)) *
                                          (param_2 - *(int *)(&DAT_004a24d8 + local_c * 4))));
    if ((float)fVar1 < 50.0) {
      return local_c;
    }
  }
  fVar1 = (float10)FUN_00476ce4((double)((param_1 + -0x140) * (param_1 + -0x140) +
                                        (param_2 + -0xf0) * (param_2 + -0xf0)));
  if (((DAT_004befe0 != 0) && (DAT_004befec == DAT_004befe8)) || (DAT_004befe0 == 0)) {
    if ((float)fVar1 < 100.0) {
      return 4;
    }
    if ((float)fVar1 < 200.0) {
      return 5;
    }
  }
  return -1;
}
```

---

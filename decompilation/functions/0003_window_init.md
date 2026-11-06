# FUN_0041c1d6 — 0x41c1d6

- Classification : `internal`
- Corps : `0x41c1d6–0x41c3e4`
- État : pseudocode obtenu
- Evidence : `ev_b6c592d2020a3b072f7d397ada43d048a75789229d848e76ffadec2a536491cf`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

## Observations Ghidra

Appels directs observés :
- `EXTERNAL:0x8` — `KERNEL32.DLL::QueryPerformanceFrequency` (externe)
- `EXTERNAL:0x55` — `USER32.DLL::MessageBoxA` (externe)
- `EXTERNAL:0x56` — `USER32.DLL::CreateWindowExA` (externe)
- `EXTERNAL:0x57` — `USER32.DLL::GetSystemMetrics` (externe)
- `EXTERNAL:0x58` — `USER32.DLL::RegisterClassA` (externe)
- `EXTERNAL:0x59` — `USER32.DLL::LoadIconA` (externe)
- `0x4010b9` — `thunk_FUN_00429ebe` (thunk)
- `0x40146a` — `thunk_FUN_0041c181` (thunk)
- `0x401532` — `thunk_FUN_0044c2b9` (thunk)
- `0x40176c` — `thunk_FUN_0042c0fa` (thunk)
- `0x4017df` — `thunk_FUN_0041be72` (thunk)
- `0x401d75` — `thunk_FUN_00414106` (thunk)
- `0x401e88` — `thunk_FUN_00459e84` (thunk)
- `0x401f64` — `thunk_FUN_00414b64` (thunk)
- `0x402298` — `thunk_FUN_00414ad0` (thunk)
- `0x474b80` — `FUN_00474b80` (interne)

Chaînes référencées observées :
- `0x49ca18` — `toneicon`
- `0x49ca24` — `Float Class`
- `0x49ca30` — `Tonus Rebellious`
- `0x49ca44` — `Float Class`
- `0x49ca54` — `C:\float\src\float.cpp`
- `0x49ca6c` — `Timer period: %d:%d`
- `0x49ca80` — `sound.txt`
- `0x49ca8c` — `DXSOUND`
- `0x49ca94` — `Tonus Rebellious`

## Interprétation

Cette procédure fait partie de l’initialisation ou de la boucle principale d’après les API, appels et chaînes visibles ; les noms de fonctions/données restent ceux fournis ou reconstruits par Ghidra.

## Pseudocode Ghidra

```c
undefined4 FUN_0041c1d6(HINSTANCE param_1)

{
  ATOM AVar1;
  undefined4 uVar2;
  int iVar3;
  int nWidth;
  LPCSTR lpText;
  HWND hWndParent;
  HMENU hMenu;
  HINSTANCE hInstance;
  LPVOID lpParam;
  undefined4 local_44;
  LARGE_INTEGER local_40;
  WNDCLASSA local_38;
  BOOL local_10;
  uint local_c;
  HWND local_8;
  
  thunk_FUN_0041c181(param_1);
  local_38.style = 3;
  local_38.lpfnWndProc = (WNDPROC)&LAB_004020d6;
  local_38.cbClsExtra = 0;
  local_38.cbWndExtra = 0;
  local_38.hInstance = param_1;
  local_38.hIcon = LoadIconA(param_1,s_toneicon_0049ca18);
  local_38.hCursor = (HCURSOR)0x0;
  local_38.hbrBackground = (HBRUSH)0x0;
  local_38.lpszMenuName = (LPCSTR)0x0;
  local_38.lpszClassName = s_Float_Class_0049ca24;
  AVar1 = RegisterClassA(&local_38);
  local_c = (uint)AVar1;
  if (local_c == 0) {
    uVar2 = 0;
  }
  else {
    lpParam = (LPVOID)0x0;
    hMenu = (HMENU)0x0;
    hWndParent = (HWND)0x0;
    hInstance = param_1;
    iVar3 = GetSystemMetrics(0x11);
    nWidth = GetSystemMetrics(0x10);
    local_8 = CreateWindowExA(0,s_Float_Class_0049ca44,s_Tonus_Rebellious_0049ca30,0x90000000,0,0,
                              nWidth,iVar3,hWndParent,hMenu,hInstance,lpParam);
    if (local_8 == (HWND)0x0) {
      uVar2 = 0;
    }
    else {
      DAT_004c2b5c = param_1;
      DAT_004c2b58 = local_8;
      local_10 = QueryPerformanceFrequency(&local_40);
      if (local_10 == 0) {
        uVar2 = thunk_FUN_00414b64(s_C__float_src_float_cpp_0049ca54,0x199,&DAT_0049ca50);
      }
      else {
        uVar2 = 0;
      }
      thunk_FUN_00414ad0(s_Timer_period___d__d_0049ca6c,local_40.s.HighPart,local_40.s.LowPart,uVar2
                        );
      DAT_004c2b54 = local_40.s.LowPart;
      if (DAT_004c2b88 == 1) {
        iVar3 = thunk_FUN_0044c2b9();
        if (iVar3 == 0) {
          return 0;
        }
        DAT_004befe0 = 1;
        DAT_004c2bb8 = 1;
      }
      else {
        DAT_004befe4 = 1;
        local_44 = 1;
        thunk_FUN_00414106(1,&local_44,4);
      }
      if ((DAT_004c2b80 != 0) && (iVar3 = thunk_FUN_00459e84(s_sound_txt_0049ca80), iVar3 == 0)) {
        lpText = (LPCSTR)thunk_FUN_00429ebe(s_DXSOUND_0049ca8c,0);
        iVar3 = MessageBoxA((HWND)0x0,lpText,s_Tonus_Rebellious_0049ca94,1);
        if (iVar3 == 2) {
          return 0;
        }
        DAT_004c2b80 = 0;
      }
      iVar3 = thunk_FUN_0042c0fa(DAT_0049c9b4);
      if (iVar3 == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = thunk_FUN_0041be72();
        FUN_00474b80(uVar2);
        DAT_004c2b68 = 1;
        uVar2 = 1;
      }
    }
  }
  return uVar2;
}
```

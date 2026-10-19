# Lot 0019 — détails des procédures (4/4)



## FUN_0048aec0 — 0x48aec0

- Classification : internal
- Corps : `0x48aec0–0x48af84`
- État : pseudocode obtenu
- Evidence : `ev_cd3d87fcd3a7aa8c6b0f37d5e967ffc25f77b4d40225ce23be71e589a9b45741`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x4738f0` — `_strchr`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
byte * FUN_0048aec0(byte *param_1,uint param_2)

{
  byte *pbVar1;
  uint local_8;
  
  if (DAT_00632844 == 0) {
    param_1 = (byte *)_strchr((char *)param_1,param_2);
  }
  else {
    while( true ) {
      local_8 = (uint)*param_1;
      if (local_8 == 0) break;
      if (((&DAT_00632741)[local_8] & 4) == 0) {
        pbVar1 = param_1;
        if (param_2 == local_8) break;
      }
      else {
        pbVar1 = param_1 + 1;
        if (*pbVar1 == 0) {
          return (byte *)0x0;
        }
        if (param_2 == CONCAT11(*param_1,*pbVar1)) {
          return param_1;
        }
      }
      param_1 = pbVar1;
      param_1 = param_1 + 1;
    }
    if (param_2 != local_8) {
      param_1 = (byte *)0x0;
    }
  }
  return param_1;
}
```

---

## __strcmpi — 0x48b100

- Classification : internal
- Corps : `0x48b100–0x48b18b`
- État : pseudocode obtenu
- Evidence : `ev_f3d181ed3ecebb344ae2932dbd18e5a8384e3bf037c237a7cd25ca9d0eeba0c6`
- Limites : Unresolved computed or indirect flows without target addresses are not represented as reference edges. Thunk and external classifications are Ghidra FunctionManager observations; they do not resolve targetless calls. Pseudocode and assembly are Ghidra-specific representations, not original source or Hopper-equivalent text. Synthetic Ghidra entry-point references without actionable memory sources are omitted.

### Appels directs

- `0x482620` — `FUN_00482620`

### Chaînes référencées

- aucune relevée

### Pseudocode Ghidra

```c
/* Library Function - Single Match
    __strcmpi
   
   Libraries: Visual Studio 1998 Debug, Visual Studio 1998 Release */

int __cdecl __strcmpi(char *_Str1,char *_Str2)

{
  char cVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  char cVar6;
  int iVar7;
  
  if (DAT_006325e8 == 0) {
    bVar5 = 0xff;
    do {
      do {
        cVar6 = '\0';
        if (bVar5 == 0) goto LAB_0048b14e;
        bVar5 = *_Str2;
        _Str2 = _Str2 + 1;
        bVar4 = *_Str1;
        _Str1 = _Str1 + 1;
      } while (bVar4 == bVar5);
      bVar3 = bVar5 + 0xbf + (-((byte)(bVar5 + 0xbf) < 0x1a) & 0x20U) + 0x41;
      bVar4 = bVar4 + 0xbf;
      bVar5 = bVar4 + (-(bVar4 < 0x1a) & 0x20U) + 0x41;
    } while (bVar5 == bVar3);
    cVar6 = (bVar5 < bVar3) * -2 + '\x01';
LAB_0048b14e:
    iVar7 = (int)cVar6;
  }
  else {
    iVar7 = 0xff;
    do {
      do {
        if ((char)iVar7 == '\0') {
          return iVar7;
        }
        cVar6 = *_Str2;
        iVar7 = CONCAT31((int3)((uint)iVar7 >> 8),cVar6);
        _Str2 = _Str2 + 1;
        cVar1 = *_Str1;
        _Str1 = _Str1 + 1;
      } while (cVar6 == cVar1);
      bVar5 = FUN_00482620(cVar1,iVar7);
      iVar7 = FUN_00482620();
    } while (bVar5 == (byte)iVar7);
    uVar2 = (uint)(bVar5 < (byte)iVar7);
    iVar7 = (1 - uVar2) - (uint)(uVar2 != 0);
  }
  return iVar7;
}
```

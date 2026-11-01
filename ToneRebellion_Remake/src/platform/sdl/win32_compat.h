/* The Win32 vocabulary the shared game code still speaks, for remake_sdl
   without <windows.h> (TODO_WEB.md steps 2-4). The game code handles its
   input as Win32 window messages; sdl_app.inc translates SDL events into
   them. Only types, constants and macros live here: the few functions the
   code calls are implemented on SDL in sdl_platform.inc. */
#ifndef TONE_WIN32_COMPAT_H
#define TONE_WIN32_COMPAT_H

#include <stdint.h>
#include <string.h>

typedef void *HWND;
typedef void *HMODULE;
typedef void *HCURSOR;
typedef void *HANDLE;
/* GDI handles still named in signatures the SDL shell passes NULL to. */
typedef void *HDC;
typedef void *HBITMAP;
typedef void *HGDIOBJ;
typedef void *HMENU;
typedef int BOOL;
typedef unsigned char BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint32_t COLORREF;
typedef unsigned int UINT;
typedef long LONG;
typedef uintptr_t WPARAM;
typedef intptr_t LPARAM;
typedef intptr_t LRESULT;
typedef intptr_t LONG_PTR;
typedef char *LPSTR;
typedef const char *LPCSTR;

/* SDL_main.h declares WINAPI and HINSTANCE on Windows. */
#ifndef WINAPI
#define WINAPI
#endif
#define CALLBACK
#define TRUE 1
#define FALSE 0
#define MAX_PATH 260

typedef struct RECT { LONG left, top, right, bottom; } RECT;
typedef struct POINT { LONG x, y; } POINT;

#define RGB(r, g, b) ((COLORREF)(((BYTE)(r)) | ((WORD)((BYTE)(g)) << 8) | \
                                 (((DWORD)(BYTE)(b)) << 16)))
#define GetRValue(c) ((BYTE)(c))
#define GetGValue(c) ((BYTE)(((WORD)(c)) >> 8))
#define GetBValue(c) ((BYTE)((c) >> 16))
#define LOWORD(l) ((WORD)(((uintptr_t)(l)) & 0xffff))
#define HIWORD(l) ((WORD)((((uintptr_t)(l)) >> 16) & 0xffff))
#define MAKELONG(a, b) ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define MAKELPARAM(l, h) ((LPARAM)(DWORD)MAKELONG(l, h))
#define MAKEWPARAM(l, h) ((WPARAM)(DWORD)MAKELONG(l, h))
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#define GET_WHEEL_DELTA_WPARAM(wp) ((short)HIWORD(wp))
#define WHEEL_DELTA 120
#define ZeroMemory(p, n) memset((p), 0, (n))
/* Microsoft C runtime names (SDL.h is included first). */
#define _stricmp SDL_strcasecmp
#define _strnicmp SDL_strncasecmp

/* PlaySound flags: the SDL shell plays in-memory effects on the mixer. */
#define SND_ASYNC 0x0001
#define SND_NODEFAULT 0x0002
#define SND_MEMORY 0x0004

/* Window messages the game code handles. */
#define WM_DESTROY 0x0002
#define WM_SIZE 0x0005
#define WM_PAINT 0x000F
#define WM_CLOSE 0x0010
#define WM_ERASEBKGND 0x0014
#define WM_SETCURSOR 0x0020
#define WM_GETMINMAXINFO 0x0024
#define WM_KEYDOWN 0x0100
#define WM_KEYUP 0x0101
#define WM_CHAR 0x0102
#define WM_SYSKEYDOWN 0x0104
#define WM_SYSCOMMAND 0x0112
#define WM_TIMER 0x0113
#define WM_MOUSEMOVE 0x0200
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202
#define WM_LBUTTONDBLCLK 0x0203
#define WM_RBUTTONDOWN 0x0204
#define WM_RBUTTONUP 0x0205
#define WM_MOUSEWHEEL 0x020A
#define WM_MOUSELEAVE 0x02A3
#define WM_USER 0x0400
#define WM_APP 0x8000
#define HTCLIENT 1

#define MK_LBUTTON 0x0001
#define MK_RBUTTON 0x0002
#define MK_SHIFT 0x0004
#define MK_CONTROL 0x0008

/* Virtual-key codes (sdl_virtual_key produces them). */
#define VK_BACK 0x08
#define VK_TAB 0x09
#define VK_RETURN 0x0D
#define VK_SHIFT 0x10
#define VK_CONTROL 0x11
#define VK_MENU 0x12
#define VK_PAUSE 0x13
#define VK_ESCAPE 0x1B
#define VK_SPACE 0x20
#define VK_PRIOR 0x21
#define VK_NEXT 0x22
#define VK_END 0x23
#define VK_HOME 0x24
#define VK_LEFT 0x25
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28
#define VK_INSERT 0x2D
#define VK_DELETE 0x2E
#define VK_NUMPAD0 0x60
#define VK_NUMPAD1 0x61
#define VK_NUMPAD9 0x69
#define VK_MULTIPLY 0x6A
#define VK_ADD 0x6B
#define VK_SUBTRACT 0x6D
#define VK_DIVIDE 0x6F
#define VK_F1 0x70
#define VK_F2 0x71
#define VK_F3 0x72
#define VK_F4 0x73
#define VK_F5 0x74
#define VK_F6 0x75
#define VK_F7 0x76
#define VK_F8 0x77
#define VK_F9 0x78
#define VK_F10 0x79
#define VK_F11 0x7A
#define VK_F12 0x7B
#define VK_OEM_PLUS 0xBB
#define VK_OEM_MINUS 0xBD

#endif

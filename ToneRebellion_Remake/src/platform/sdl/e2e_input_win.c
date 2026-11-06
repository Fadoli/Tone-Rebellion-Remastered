/* E2E test input on Windows (only with TONE_REBELLION_E2E_STATE). The test
   scripts drive the game with PostMessage: SDL turns posted keys into key
   events, but drops posted mouse buttons (it checks the real button state)
   and reads arrow keys without the extended bit as keypad keys. Under the
   test hook every mouse and key message goes straight to the game's message
   handler instead, as the former Win32 build received them. Separate file:
   it needs <windows.h>, which the game code replaces with win32_compat.h. */
#include <windows.h>
#include <SDL3/SDL.h>
#include <stdint.h>

/* menu_app.c: hands a message to menu_window_proc. */
void e2e_deliver_input(unsigned message, uintptr_t wparam, intptr_t lparam);

static bool SDLCALL e2e_message_hook(void *userdata, MSG *msg)
{
    (void)userdata;
    switch (msg->message) {
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MOUSEWHEEL:
    case WM_KEYDOWN:
    case WM_CHAR:
        e2e_deliver_input(msg->message, (uintptr_t)msg->wParam, (intptr_t)msg->lParam);
        return false;   /* SDL skips it */
    default:
        return true;
    }
}

void e2e_install_input_hook(void)
{
    SDL_SetWindowsMessageHook(e2e_message_hook, NULL);
}

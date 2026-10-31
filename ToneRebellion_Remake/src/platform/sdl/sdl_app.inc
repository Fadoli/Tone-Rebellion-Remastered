/* SDL3 shell (TODO_WEB.md step 3), built as remake_sdl. SDL owns the
   window, the event loop, the frame clock and the presentation of the
   640x480 RenderSurface through a streaming texture. The game code still
   reads Win32 window messages: SDL events are translated into the same
   menu_window_proc calls the Win32 shell receives, so both shells share
   every input path. Audio (waveOut, MCI), files and sockets stay on Win32
   for now (step 2 of TODO_WEB.md). */

static SDL_Window *g_sdl_window;
static SDL_Renderer *g_sdl_renderer;
static SDL_Texture *g_sdl_texture;
static uint32_t *g_sdl_pixels;
static WNDPROC g_sdl_window_proc;
static int g_sdl_dirty = 1;

static int sdl_ensure_back_buffer(void)
{
    if (g_sdl_pixels == NULL) {
        g_sdl_pixels = (uint32_t *)calloc((size_t)LOGICAL_WIDTH * LOGICAL_HEIGHT,
                                          sizeof(uint32_t));
        if (g_sdl_pixels == NULL) return 0;
    }
    if (g_back_surface.pixels != g_sdl_pixels)
        render_surface_init(&g_back_surface, g_sdl_pixels, LOGICAL_WIDTH,
                            LOGICAL_HEIGHT, LOGICAL_WIDTH);
    return 1;
}

/* Scales the back buffer into the window like present_back_buffer: black
   bars, nearest pixel unless the smooth mode is chosen. */
static void sdl_present(void)
{
    int width = 0;
    int height = 0;
    RECT viewport;
    SDL_FRect target;
    if (g_sdl_texture == NULL || g_sdl_pixels == NULL) return;
    (void)SDL_UpdateTexture(g_sdl_texture, NULL, g_sdl_pixels,
                            LOGICAL_WIDTH * (int)sizeof(uint32_t));
    (void)SDL_GetCurrentRenderOutputSize(g_sdl_renderer, &width, &height);
    (void)SDL_SetRenderDrawColor(g_sdl_renderer, 0, 0, 0, 255);
    (void)SDL_RenderClear(g_sdl_renderer);
    if (logical_viewport(width, height, &viewport)) {
        target.x = (float)viewport.left;
        target.y = (float)viewport.top;
        target.w = (float)(viewport.right - viewport.left);
        target.h = (float)(viewport.bottom - viewport.top);
        (void)SDL_SetTextureScaleMode(g_sdl_texture,
            g_scale_mode == SCALE_FIT_SMOOTH ? SDL_SCALEMODE_LINEAR
                                             : SDL_SCALEMODE_NEAREST);
        (void)SDL_RenderTexture(g_sdl_renderer, g_sdl_texture, NULL, &target);
    }
    (void)SDL_RenderPresent(g_sdl_renderer);
}

static void sdl_redraw(void)
{
    if (!sdl_ensure_back_buffer()) return;
    render_back_buffer(&g_back_surface);
    sdl_present();
    g_sdl_dirty = 0;
}

/* Win32 messages SDL's own window procedure would not pass on: InvalidateRect
   repaints, the original game's cursors, the scale entries of the system
   menu and the socket notifications. */
static LRESULT CALLBACK sdl_subclass_proc(HWND window, UINT message,
                                          WPARAM wparam, LPARAM lparam)
{
    switch (message) {
    case WM_PAINT:
        g_sdl_dirty = 1;
        break;
    case WM_SETCURSOR:
        if (LOWORD(lparam) == HTCLIENT) {
            update_interaction_cursor();
            return TRUE;
        }
        break;
    case WM_SYSCOMMAND:
        if ((wparam & 0xFFF0U) >= SYSCOMMAND_SCALE_FIRST &&
            (wparam & 0xFFF0U) < SYSCOMMAND_SCALE_FIRST + 0x10 * SCALE_MODE_COUNT)
            return menu_window_proc(window, message, wparam, lparam);
        break;
    case WM_NET_SOCKET:
        return menu_window_proc(window, message, wparam, lparam);
    default:
        break;
    }
    return CallWindowProcA(g_sdl_window_proc, window, message, wparam, lparam);
}

/* Creates the hidden SDL window and returns its Win32 handle, which the
   shared game code keeps using for titles, message boxes, mouse capture
   and socket notifications. */
static HWND sdl_create_window(void)
{
    HWND window;
    SDL_SetMainReady();
    if (!SDL_Init(SDL_INIT_VIDEO)) return NULL;
    g_sdl_window = SDL_CreateWindow("Tone Rebellion - New Game", 1024, 781,
                                    SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
    if (g_sdl_window == NULL) return NULL;
    g_sdl_renderer = SDL_CreateRenderer(g_sdl_window, NULL);
    if (g_sdl_renderer == NULL) return NULL;
    g_sdl_texture = SDL_CreateTexture(g_sdl_renderer, SDL_PIXELFORMAT_XRGB8888,
                                      SDL_TEXTUREACCESS_STREAMING,
                                      LOGICAL_WIDTH, LOGICAL_HEIGHT);
    if (g_sdl_texture == NULL) return NULL;
    window = (HWND)SDL_GetPointerProperty(SDL_GetWindowProperties(g_sdl_window),
                                          SDL_PROP_WINDOW_WIN32_HWND_POINTER,
                                          NULL);
    if (window == NULL) return NULL;
    g_sdl_window_proc = (WNDPROC)SetWindowLongPtrA(window, GWLP_WNDPROC,
                                                   (LONG_PTR)sdl_subclass_proc);
    if (!sdl_ensure_back_buffer()) return NULL;
    return window;
}

static void sdl_destroy_window(void)
{
    if (g_sdl_texture != NULL) SDL_DestroyTexture(g_sdl_texture);
    if (g_sdl_renderer != NULL) SDL_DestroyRenderer(g_sdl_renderer);
    if (g_sdl_window != NULL) SDL_DestroyWindow(g_sdl_window);
    g_sdl_texture = NULL;
    g_sdl_renderer = NULL;
    g_sdl_window = NULL;
    free(g_sdl_pixels);
    g_sdl_pixels = NULL;
    SDL_Quit();
}

/* The virtual-key codes the game tests (letters and digits are their
   upper-case ASCII codes, as on Win32). */
static WPARAM sdl_virtual_key(SDL_Keycode key)
{
    if (key >= 'a' && key <= 'z') return (WPARAM)(key - 'a' + 'A');
    if ((key >= '0' && key <= '9') || key == ' ') return (WPARAM)key;
    if (key >= SDLK_F1 && key <= SDLK_F12) return (WPARAM)(VK_F1 + (key - SDLK_F1));
    if (key >= SDLK_KP_1 && key <= SDLK_KP_9)
        return (WPARAM)(VK_NUMPAD1 + (key - SDLK_KP_1));
    switch (key) {
    case SDLK_KP_0: return VK_NUMPAD0;
    case SDLK_KP_PLUS: return VK_ADD;
    case SDLK_KP_MINUS: return VK_SUBTRACT;
    case SDLK_KP_ENTER:
    case SDLK_RETURN: return VK_RETURN;
    case SDLK_ESCAPE: return VK_ESCAPE;
    case SDLK_BACKSPACE: return VK_BACK;
    case SDLK_TAB: return VK_TAB;
    case SDLK_DELETE: return VK_DELETE;
    case SDLK_LEFT: return VK_LEFT;
    case SDLK_RIGHT: return VK_RIGHT;
    case SDLK_UP: return VK_UP;
    case SDLK_DOWN: return VK_DOWN;
    case SDLK_HOME: return VK_HOME;
    case SDLK_END: return VK_END;
    case SDLK_PAGEUP: return VK_PRIOR;
    case SDLK_PAGEDOWN: return VK_NEXT;
    case SDLK_LSHIFT:
    case SDLK_RSHIFT: return VK_SHIFT;
    case SDLK_LCTRL:
    case SDLK_RCTRL: return VK_CONTROL;
    default: return 0;
    }
}

/* SDL reports window coordinates; the game expects client pixels. */
static LPARAM sdl_client_point(float x, float y)
{
    int width = 1, height = 1, pixel_width = 1, pixel_height = 1;
    (void)SDL_GetWindowSize(g_sdl_window, &width, &height);
    (void)SDL_GetWindowSizeInPixels(g_sdl_window, &pixel_width, &pixel_height);
    if (width <= 0 || height <= 0) return 0;
    return MAKELPARAM((WORD)(short)((int)x * pixel_width / width),
                      (WORD)(short)((int)y * pixel_height / height));
}

static WPARAM sdl_mouse_buttons(void)
{
    SDL_MouseButtonFlags buttons = SDL_GetMouseState(NULL, NULL);
    WPARAM flags = 0;
    if (buttons & SDL_BUTTON_LMASK) flags |= MK_LBUTTON;
    if (buttons & SDL_BUTTON_RMASK) flags |= MK_RBUTTON;
    if (SDL_GetModState() & SDL_KMOD_SHIFT) flags |= MK_SHIFT;
    return flags;
}

/* Feeds one SDL event to the game as the Win32 message it stands for.
   Returns 0 once the window is closed. */
static int sdl_dispatch_event(HWND window, const SDL_Event *event)
{
    switch (event->type) {
    case SDL_EVENT_QUIT:
    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
        return 0;
    case SDL_EVENT_WINDOW_EXPOSED:
    case SDL_EVENT_WINDOW_RESIZED:
    case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
        g_sdl_dirty = 1;
        break;
    case SDL_EVENT_WINDOW_MOUSE_LEAVE:
        (void)menu_window_proc(window, WM_MOUSELEAVE, 0, 0);
        break;
    case SDL_EVENT_MOUSE_MOTION:
        (void)menu_window_proc(window, WM_MOUSEMOVE, sdl_mouse_buttons(),
                               sdl_client_point(event->motion.x, event->motion.y));
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP: {
        int down = event->type == SDL_EVENT_MOUSE_BUTTON_DOWN;
        UINT message;
        if (event->button.button == SDL_BUTTON_LEFT)
            message = down ? WM_LBUTTONDOWN : WM_LBUTTONUP;
        else if (event->button.button == SDL_BUTTON_RIGHT)
            message = down ? WM_RBUTTONDOWN : WM_RBUTTONUP;
        else
            break;
        (void)menu_window_proc(window, message, sdl_mouse_buttons(),
                               sdl_client_point(event->button.x, event->button.y));
        break;
    }
    case SDL_EVENT_MOUSE_WHEEL:
        if (event->wheel.y != 0.0f)
            (void)menu_window_proc(window, WM_MOUSEWHEEL,
                                   MAKEWPARAM(0, (WORD)(short)(event->wheel.y > 0.0f
                                                               ? WHEEL_DELTA
                                                               : -WHEEL_DELTA)),
                                   0);
        break;
    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP: {
        WPARAM key = sdl_virtual_key(event->key.key);
        int down = event->type == SDL_EVENT_KEY_DOWN;
        if (key == 0) break;
        (void)menu_window_proc(window, down ? WM_KEYDOWN : WM_KEYUP, key, 0);
        /* TranslateMessage also turns these keys into WM_CHAR; SDL text
           input carries only printable characters. */
        if (down && (key == VK_BACK || key == VK_RETURN || key == VK_ESCAPE ||
                     key == VK_TAB))
            (void)menu_window_proc(window, WM_CHAR,
                                   key == VK_RETURN ? '\r' : key, 0);
        break;
    }
    case SDL_EVENT_TEXT_INPUT: {
        const unsigned char *text = (const unsigned char *)event->text.text;
        for (; *text != '\0'; ++text)
            if (*text < 0x80U)
                (void)menu_window_proc(window, WM_CHAR, *text, 0);
        break;
    }
    default:
        break;
    }
    return 1;
}

/* Main loop: the 20 Hz frame clock of WM_TIMER 1, the one-second tune
   check of WM_TIMER 2, and a repaint whenever something changed. */
static void sdl_run(HWND window)
{
    Uint64 tune_check = SDL_GetTicks();
    int running = 1;
    SDL_ShowWindow(g_sdl_window);
    (void)SDL_StartTextInput(g_sdl_window);
    while (running) {
        SDL_Event event;
        unsigned due;
        if (SDL_WaitEventTimeout(&event, 10)) {
            do {
                if (!sdl_dispatch_event(window, &event)) running = 0;
            } while (running && SDL_PollEvent(&event));
        }
        if (!running) break;
        due = frame_clock_due();
        while (due-- != 0U) run_ui_frame(window, 1);
        if (SDL_GetTicks() - tune_check >= 1000U) {
            tune_check = SDL_GetTicks();
            run_ui_frame(window, 2);
        }
        /* The game asks for repaints with InvalidateRect, as on Win32. */
        if (GetUpdateRect(window, NULL, FALSE)) {
            ValidateRect(window, NULL);
            g_sdl_dirty = 1;
        }
        if (g_sdl_dirty) sdl_redraw();
    }
    (void)SDL_StopTextInput(g_sdl_window);
    /* WM_DESTROY: network shutdown, resume save, music stop. */
    (void)menu_window_proc(window, WM_DESTROY, 0, 0);
}

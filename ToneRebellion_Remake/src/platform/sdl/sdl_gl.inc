/* OpenGL presentation (remake): the 640x480 frame is scaled to the window
   on the GPU by libretro-style GLSL presets (shaders/, embedded by
   tools/embed_shaders.py into sdl_gl_shaders.h). Desktop: OpenGL 3.3 core;
   browser: OpenGL ES 3.0 (WebGL 2). Each preset is built on first use; one
   that fails to compile, link or get its framebuffers (ScaleFX needs float
   targets) is marked unsupported and its filter is offered no more. Without
   any OpenGL context the SDL renderer shows the frame (nearest or linear
   only).

   Runner conventions (RetroArch GLSL): attributes VertexCoord / TexCoord /
   COLOR; uniforms MVPMatrix, FrameCount, FrameDirection, InputSize,
   TextureSize, OutputSize; samplers Texture (also "decal") = this pass's
   input, OrigTexture = the game frame, PassPrevNTexture = the output of the
   pass N back (-1 = the game frame), LUT = the preset's lookup texture;
   PARAMETER_UNIFORM is defined and each "#pragma parameter" gets its
   default unless the preset sets it. Textures clamp to the edge. */

#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#define GLX(name) name
#else
/* Desktop: the few GL types, constants and entry points used here, loaded
   through SDL_GL_GetProcAddress (SDL_opengl.h would pull in <windows.h>,
   which clashes with win32_compat.h). */
typedef unsigned int GLenum;
typedef unsigned int GLuint;
typedef int GLint;
typedef int GLsizei;
typedef float GLfloat;
typedef unsigned char GLboolean;
typedef char GLchar;
typedef unsigned int GLbitfield;
typedef ptrdiff_t GLsizeiptr;
#if defined(_WIN32) && !defined(_WIN64)
#define GL_ENTRY __stdcall
#else
#define GL_ENTRY
#endif
#define GL_FALSE 0
#define GL_ONE 1
#define GL_TRIANGLE_STRIP 0x0005
#define GL_DEPTH_TEST 0x0B71
#define GL_BLEND 0x0BE2
#define GL_UNPACK_ALIGNMENT 0x0CF5
#define GL_TEXTURE_2D 0x0DE1
#define GL_UNSIGNED_BYTE 0x1401
#define GL_FLOAT 0x1406
#define GL_RED 0x1903
#define GL_BLUE 0x1905
#define GL_RGBA 0x1908
#define GL_NEAREST 0x2600
#define GL_LINEAR 0x2601
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_COLOR_BUFFER_BIT 0x4000
#define GL_RGBA8 0x8058
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE2 0x84C2
#define GL_TEXTURE3 0x84C3
#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_FRAMEBUFFER 0x8D40
#define GL_FUNCS(X) \
    X(void, glGenTextures, (GLsizei, GLuint *)) \
    X(void, glBindTexture, (GLenum, GLuint)) \
    X(void, glTexImage2D, (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *)) \
    X(void, glTexSubImage2D, (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *)) \
    X(void, glTexParameteri, (GLenum, GLenum, GLint)) \
    X(void, glDeleteTextures, (GLsizei, const GLuint *)) \
    X(void, glViewport, (GLint, GLint, GLsizei, GLsizei)) \
    X(void, glClearColor, (GLfloat, GLfloat, GLfloat, GLfloat)) \
    X(void, glClear, (GLbitfield)) \
    X(void, glDrawArrays, (GLenum, GLint, GLsizei)) \
    X(void, glPixelStorei, (GLenum, GLint)) \
    X(void, glDisable, (GLenum)) \
    X(void, glFinish, (void)) \
    X(void, glActiveTexture, (GLenum)) \
    X(void, glGenFramebuffers, (GLsizei, GLuint *)) \
    X(void, glBindFramebuffer, (GLenum, GLuint)) \
    X(void, glFramebufferTexture2D, (GLenum, GLenum, GLenum, GLuint, GLint)) \
    X(GLenum, glCheckFramebufferStatus, (GLenum)) \
    X(void, glDeleteFramebuffers, (GLsizei, const GLuint *)) \
    X(GLuint, glCreateShader, (GLenum)) \
    X(void, glShaderSource, (GLuint, GLsizei, const GLchar *const *, const GLint *)) \
    X(void, glCompileShader, (GLuint)) \
    X(void, glGetShaderiv, (GLuint, GLenum, GLint *)) \
    X(void, glGetShaderInfoLog, (GLuint, GLsizei, GLsizei *, GLchar *)) \
    X(void, glDeleteShader, (GLuint)) \
    X(GLuint, glCreateProgram, (void)) \
    X(void, glAttachShader, (GLuint, GLuint)) \
    X(void, glBindAttribLocation, (GLuint, GLuint, const GLchar *)) \
    X(void, glLinkProgram, (GLuint)) \
    X(void, glGetProgramiv, (GLuint, GLenum, GLint *)) \
    X(void, glGetProgramInfoLog, (GLuint, GLsizei, GLsizei *, GLchar *)) \
    X(void, glUseProgram, (GLuint)) \
    X(void, glDeleteProgram, (GLuint)) \
    X(GLint, glGetUniformLocation, (GLuint, const GLchar *)) \
    X(void, glUniform1i, (GLint, GLint)) \
    X(void, glUniform1f, (GLint, GLfloat)) \
    X(void, glUniform2f, (GLint, GLfloat, GLfloat)) \
    X(void, glUniformMatrix4fv, (GLint, GLsizei, GLboolean, const GLfloat *)) \
    X(void, glGenBuffers, (GLsizei, GLuint *)) \
    X(void, glBindBuffer, (GLenum, GLuint)) \
    X(void, glBufferData, (GLenum, GLsizeiptr, const void *, GLenum)) \
    X(void, glGenVertexArrays, (GLsizei, GLuint *)) \
    X(void, glBindVertexArray, (GLuint)) \
    X(void, glEnableVertexAttribArray, (GLuint)) \
    X(void, glVertexAttribPointer, (GLuint, GLint, GLenum, GLboolean, GLsizei, const void *))
#define GL_DECLARE_FUNC(ret, name, args) static ret (GL_ENTRY *p_##name) args;
GL_FUNCS(GL_DECLARE_FUNC)
#define GLX(name) p_##name
#endif

#include "sdl_gl_shaders.h"

#ifndef GL_TEXTURE_SWIZZLE_R
#define GL_TEXTURE_SWIZZLE_R 0x8E42
#define GL_TEXTURE_SWIZZLE_B 0x8E44
#define GL_TEXTURE_SWIZZLE_A 0x8E45
#endif
#ifndef GL_RGBA16F
#define GL_RGBA16F 0x881A
#endif
#ifndef GL_HALF_FLOAT
#define GL_HALF_FLOAT 0x140B
#endif

enum { GL_RUN_MAX_PASSES = GL_PRESET_MAX_PASSES + 1, GL_PRESET_PARAMS_MAX = 8 };

typedef struct GlPassRun {
    GLuint program;
    GLuint texture;          /* output (0 for the screen) */
    GLuint framebuffer;
    int width, height;       /* output size */
    int float_fb;
} GlPassRun;

typedef struct GlPresetRun {
    int state;               /* 0 not built, 1 ready, -1 unsupported */
    int pass_count;          /* with the final stretch when needed */
    GlPassDesc passes[GL_RUN_MAX_PASSES];
    GlPassRun runs[GL_RUN_MAX_PASSES];
    GLuint lut;
} GlPresetRun;

static SDL_GLContext g_gl_context;
static int g_gl_ready;
static GLuint g_gl_frame_texture;
#ifdef __EMSCRIPTEN__
/* WebGL 2 has no texture swizzle: the frame is uploaded as is and one
   pass writes it in R, G, B order into g_gl_frame_texture. */
static GLuint g_gl_raw_texture;
static GLuint g_gl_swap_framebuffer;
static GLuint g_gl_swap_program;
static const char g_gl_swap_shader[] =
    "#if defined(VERTEX)\n"
    "in vec4 VertexCoord; in vec4 TexCoord; out vec2 uv;\n"
    "uniform mat4 MVPMatrix;\n"
    "void main() { gl_Position = MVPMatrix * VertexCoord; uv = TexCoord.xy; }\n"
    "#else\n"
    "in vec2 uv; out vec4 FragColor; uniform sampler2D Texture;\n"
    "void main() { FragColor = vec4(texture(Texture, uv).bgr, 1.0); }\n"
    "#endif\n";
#endif
static GLuint g_gl_vertex_array;
static GLuint g_gl_vertex_buffer;
static unsigned g_gl_frame_count;
static GlPresetRun g_gl_runs[GL_PRESET_COUNT];

/* Before the window is created: the context this build asks for. */
static void gl_set_attributes(void)
{
#ifdef __EMSCRIPTEN__
    (void)SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    (void)SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    (void)SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#else
    (void)SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    (void)SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    (void)SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
#endif
    (void)SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

static void gl_set_input_filter(GLuint texture, int linear)
{
    GLX(glBindTexture)(GL_TEXTURE_2D, texture);
    GLX(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linear ? GL_LINEAR : GL_NEAREST);
    GLX(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linear ? GL_LINEAR : GL_NEAREST);
}

static GLuint gl_new_texture(int width, int height, int float_fb, const void *pixels)
{
    GLuint texture = 0;
    GLX(glGenTextures)(1, &texture);
    GLX(glBindTexture)(GL_TEXTURE_2D, texture);
    GLX(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GLX(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    GLX(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    GLX(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    if (float_fb)
        GLX(glTexImage2D)(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA,
                          GL_HALF_FLOAT, NULL);
    else
        GLX(glTexImage2D)(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA,
                          GL_UNSIGNED_BYTE, pixels);
    return texture;
}

/* Source text with its #version line removed, behind this build's
   header. */
static GLuint gl_compile(GLenum kind, const char *source)
{
#ifdef __EMSCRIPTEN__
    /* GLSL ES wants a float precision before the first declaration; the
       libretro shaders set theirs later. */
    const char *version = "#version 300 es\nprecision highp float;\nprecision highp int;\n";
#else
    const char *version = "#version 330 core\n";
#endif
    const char *stage = kind == GL_VERTEX_SHADER ? "#define VERTEX\n" : "#define FRAGMENT\n";
    const char *parts[4];
    GLint lengths[4];
    char *body;
    const char *line;
    size_t length = strlen(source);
    GLuint shader;
    GLint ok = 0;
    body = (char *)malloc(length + 1);
    if (body == NULL) return 0;
    memcpy(body, source, length + 1);
    /* Blank any "#version" line (it must come first; ours does). */
    for (line = body; line != NULL && *line != '\0';) {
        const char *at = line;
        while (*at == ' ' || *at == '\t') ++at;
        if (strncmp(at, "#version", 8) == 0) {
            char *cursor = (char *)line;
            while (*cursor != '\0' && *cursor != '\n') *cursor++ = ' ';
        }
        line = strchr(line, '\n');
        if (line != NULL) ++line;
    }
    parts[0] = version;
    parts[1] = stage;
    parts[2] = "#define PARAMETER_UNIFORM\n";
    parts[3] = body;
    lengths[0] = (GLint)strlen(parts[0]);
    lengths[1] = (GLint)strlen(parts[1]);
    lengths[2] = (GLint)strlen(parts[2]);
    lengths[3] = (GLint)length;
    shader = GLX(glCreateShader)(kind);
    GLX(glShaderSource)(shader, 4, parts, lengths);
    GLX(glCompileShader)(shader);
    free(body);
    GLX(glGetShaderiv)(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        GLX(glGetShaderInfoLog)(shader, sizeof(log), NULL, log);
        SDL_Log("shader compile failed: %s", log);
        GLX(glDeleteShader)(shader);
        return 0;
    }
    return shader;
}

static GLuint gl_link(const char *source)
{
    GLuint vertex = gl_compile(GL_VERTEX_SHADER, source);
    GLuint fragment = vertex != 0 ? gl_compile(GL_FRAGMENT_SHADER, source) : 0;
    GLuint program;
    GLint ok = 0;
    if (fragment == 0) {
        if (vertex != 0) GLX(glDeleteShader)(vertex);
        return 0;
    }
    program = GLX(glCreateProgram)();
    GLX(glAttachShader)(program, vertex);
    GLX(glAttachShader)(program, fragment);
    GLX(glBindAttribLocation)(program, 0, "VertexCoord");
    GLX(glBindAttribLocation)(program, 1, "TexCoord");
    GLX(glBindAttribLocation)(program, 2, "COLOR");
    GLX(glLinkProgram)(program);
    GLX(glDeleteShader)(vertex);
    GLX(glDeleteShader)(fragment);
    GLX(glGetProgramiv)(program, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        GLX(glGetProgramInfoLog)(program, sizeof(log), NULL, log);
        SDL_Log("shader link failed: %s", log);
        GLX(glDeleteProgram)(program);
        return 0;
    }
    return program;
}

/* "#pragma parameter NAME "label" default ..." lines: the defaults. */
static void gl_set_parameters(GLuint program, const char *source, const GlPresetDesc *preset)
{
    const char *line = source;
    while (line != NULL && *line != '\0') {
        char name[64];
        float value;
        if (sscanf(line, " #pragma parameter %63s \"%*[^\"]\" %f", name, &value) == 2) {
            GLint at = GLX(glGetUniformLocation)(program, name);
            int i;
            for (i = 0; i < preset->param_count; ++i)
                if (strcmp(preset->params[i].name, name) == 0) value = preset->params[i].value;
            if (at >= 0) GLX(glUniform1f)(at, value);
        }
        line = strchr(line, '\n');
        if (line != NULL) ++line;
    }
}

static GLuint gl_load_lut(int index, int linear)
{
    SDL_IOStream *stream = SDL_IOFromConstMem(g_gl_luts[index].png, g_gl_luts[index].size);
    SDL_Surface *image = stream != NULL ? SDL_LoadPNG_IO(stream, true) : NULL;
    SDL_Surface *rgba;
    GLuint texture;
    if (image == NULL) return 0;
    rgba = SDL_ConvertSurface(image, SDL_PIXELFORMAT_ABGR8888);  /* bytes R,G,B,A */
    SDL_DestroySurface(image);
    if (rgba == NULL) return 0;
    GLX(glPixelStorei)(GL_UNPACK_ALIGNMENT, 4);
    texture = gl_new_texture(rgba->w, rgba->h, 0, NULL);
    GLX(glTexSubImage2D)(GL_TEXTURE_2D, 0, 0, 0, rgba->w, rgba->h, GL_RGBA,
                         GL_UNSIGNED_BYTE, rgba->pixels);
    gl_set_input_filter(texture, linear);
    SDL_DestroySurface(rgba);
    return texture;
}

static void gl_free_run(GlPresetRun *run)
{
    int i;
    for (i = 0; i < run->pass_count; ++i) {
        if (run->runs[i].program != 0) GLX(glDeleteProgram)(run->runs[i].program);
        if (run->runs[i].texture != 0) GLX(glDeleteTextures)(1, &run->runs[i].texture);
        if (run->runs[i].framebuffer != 0)
            GLX(glDeleteFramebuffers)(1, &run->runs[i].framebuffer);
        run->runs[i].program = run->runs[i].texture = run->runs[i].framebuffer = 0;
        run->runs[i].width = run->runs[i].height = 0;
    }
    if (run->lut != 0) GLX(glDeleteTextures)(1, &run->lut);
    run->lut = 0;
}

/* Compiles the preset, plus a sharp-bilinear stretch to the window when its
   last pass has a fixed scale. Returns 1 when usable. */
static int gl_build_preset(int index)
{
    const GlPresetDesc *preset = &g_gl_presets[index];
    GlPresetRun *run = &g_gl_runs[index];
    int i;
    if (run->state != 0) return run->state > 0;
    run->pass_count = preset->pass_count;
    for (i = 0; i < preset->pass_count; ++i) run->passes[i] = preset->passes[i];
    if (preset->passes[preset->pass_count - 1].source_scale) {
        GlPassDesc stretch = {1, 1, 0, 1.0f, 0};   /* sharp-bilinear, see the generator */
        run->passes[run->pass_count++] = stretch;
    }
    for (i = 0; i < run->pass_count; ++i) {
        const char *source = g_gl_shader_sources[run->passes[i].shader];
        GLint at;
        run->runs[i].program = gl_link(source);
        if (run->runs[i].program == 0) {
            gl_free_run(run);
            run->state = -1;
            return 0;
        }
        run->runs[i].float_fb = run->passes[i].float_fb;
        GLX(glUseProgram)(run->runs[i].program);
        gl_set_parameters(run->runs[i].program, source, preset);
        if ((at = GLX(glGetUniformLocation)(run->runs[i].program, "Texture")) >= 0)
            GLX(glUniform1i)(at, 0);
        if ((at = GLX(glGetUniformLocation)(run->runs[i].program, "decal")) >= 0)
            GLX(glUniform1i)(at, 0);
        if ((at = GLX(glGetUniformLocation)(run->runs[i].program, "OrigTexture")) >= 0)
            GLX(glUniform1i)(at, 1);
        if ((at = GLX(glGetUniformLocation)(run->runs[i].program, "LUT")) >= 0)
            GLX(glUniform1i)(at, 2);
    }
    if (preset->lut >= 0) {
        run->lut = gl_load_lut(preset->lut, preset->lut_linear);
        if (run->lut == 0) {
            gl_free_run(run);
            run->state = -1;
            return 0;
        }
    }
    run->state = 1;
    return 1;
}

/* Output textures and framebuffers for the given input and window sizes.
   Returns 0 (and marks the preset unsupported) when a target is refused. */
static int gl_size_preset(GlPresetRun *run, int width, int height)
{
    int i;
    int in_w = LOGICAL_WIDTH, in_h = LOGICAL_HEIGHT;
    for (i = 0; i < run->pass_count; ++i) {
        GlPassRun *pass = &run->runs[i];
        int last = i == run->pass_count - 1;
        int out_w = last ? width : (int)(in_w * run->passes[i].scale + 0.5f);
        int out_h = last ? height : (int)(in_h * run->passes[i].scale + 0.5f);
        if (!last && (pass->width != out_w || pass->height != out_h)) {
            if (pass->texture != 0) GLX(glDeleteTextures)(1, &pass->texture);
            if (pass->framebuffer == 0) GLX(glGenFramebuffers)(1, &pass->framebuffer);
            pass->texture = gl_new_texture(out_w, out_h, pass->float_fb, NULL);
            GLX(glBindFramebuffer)(GL_FRAMEBUFFER, pass->framebuffer);
            GLX(glFramebufferTexture2D)(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                        GL_TEXTURE_2D, pass->texture, 0);
            if (GLX(glCheckFramebufferStatus)(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                GLX(glBindFramebuffer)(GL_FRAMEBUFFER, 0);
                gl_free_run(run);
                run->state = -1;
                return 0;
            }
        }
        pass->width = out_w;
        pass->height = out_h;
        in_w = out_w;
        in_h = out_h;
    }
    GLX(glBindFramebuffer)(GL_FRAMEBUFFER, 0);
    return 1;
}

static void gl_set_size_uniform(GLuint program, const char *name, int width, int height)
{
    GLint at = GLX(glGetUniformLocation)(program, name);
    if (at >= 0) GLX(glUniform2f)(at, (float)width, (float)height);
}

/* OpenGL context for the window; 0 leaves the SDL renderer in charge. */
static int gl_init(SDL_Window *window)
{
    static const float quad[4 * 12] = {
        /* VertexCoord x y z w, TexCoord u v 0 0, COLOR */
        0, 0, 0, 1,  0, 0, 0, 0,  1, 1, 1, 1,
        1, 0, 0, 1,  1, 0, 0, 0,  1, 1, 1, 1,
        0, 1, 0, 1,  0, 1, 0, 0,  1, 1, 1, 1,
        1, 1, 0, 1,  1, 1, 0, 0,  1, 1, 1, 1,
    };
    g_gl_context = SDL_GL_CreateContext(window);
    if (g_gl_context == NULL) return 0;
#ifndef __EMSCRIPTEN__
#define GL_LOAD_FUNC(ret, name, args) \
    p_##name = (ret (GL_ENTRY *) args)SDL_GL_GetProcAddress(#name); \
    if (p_##name == NULL) goto fail;
    GL_FUNCS(GL_LOAD_FUNC)
#undef GL_LOAD_FUNC
#endif
    /* Presentation is paced by the game's own clocks; vsync (setting)
       additionally waits for the monitor's refresh at each swap. */
    (void)SDL_GL_SetSwapInterval(g_vsync ? 1 : 0);
    GLX(glGenVertexArrays)(1, &g_gl_vertex_array);
    GLX(glBindVertexArray)(g_gl_vertex_array);
    GLX(glGenBuffers)(1, &g_gl_vertex_buffer);
    GLX(glBindBuffer)(GL_ARRAY_BUFFER, g_gl_vertex_buffer);
    GLX(glBufferData)(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    GLX(glEnableVertexAttribArray)(0);
    GLX(glVertexAttribPointer)(0, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float), (void *)0);
    GLX(glEnableVertexAttribArray)(1);
    GLX(glVertexAttribPointer)(1, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float),
                               (void *)(4 * sizeof(float)));
    GLX(glEnableVertexAttribArray)(2);
    GLX(glVertexAttribPointer)(2, 4, GL_FLOAT, GL_FALSE, 12 * sizeof(float),
                               (void *)(8 * sizeof(float)));
    GLX(glDisable)(GL_BLEND);
    GLX(glDisable)(GL_DEPTH_TEST);
    /* The frame's bytes are B, G, R, X: present them as R, G, B, 1. */
    g_gl_frame_texture = gl_new_texture(LOGICAL_WIDTH, LOGICAL_HEIGHT, 0, NULL);
#ifdef __EMSCRIPTEN__
    g_gl_raw_texture = gl_new_texture(LOGICAL_WIDTH, LOGICAL_HEIGHT, 0, NULL);
    g_gl_swap_program = gl_link(g_gl_swap_shader);
    if (g_gl_swap_program == 0) goto fail;
    GLX(glUseProgram)(g_gl_swap_program);
    {
        static const float flat_matrix[16] = {2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, -1, -1, 0, 1};
        GLX(glUniformMatrix4fv)(GLX(glGetUniformLocation)(g_gl_swap_program, "MVPMatrix"),
                                1, GL_FALSE, flat_matrix);
        GLX(glUniform1i)(GLX(glGetUniformLocation)(g_gl_swap_program, "Texture"), 0);
    }
    GLX(glGenFramebuffers)(1, &g_gl_swap_framebuffer);
    GLX(glBindFramebuffer)(GL_FRAMEBUFFER, g_gl_swap_framebuffer);
    GLX(glFramebufferTexture2D)(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                                g_gl_frame_texture, 0);
    if (GLX(glCheckFramebufferStatus)(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) goto fail;
    GLX(glBindFramebuffer)(GL_FRAMEBUFFER, 0);
#else
    GLX(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_BLUE);
    GLX(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
    GLX(glTexParameteri)(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ONE);
#endif
    g_gl_ready = 1;
    /* Nearest must work, or OpenGL is not used at all. */
    if (!gl_build_preset(0)) goto fail;
    return 1;
fail:
    g_gl_ready = 0;
    SDL_GL_DestroyContext(g_gl_context);
    g_gl_context = NULL;
    return 0;
}

/* Whether preset `index` can run (builds it on first ask). */
static int gl_preset_usable(int index)
{
    if (!g_gl_ready || index < 0 || index >= GL_PRESET_COUNT) return 0;
    return gl_build_preset(index);
}

/* Draws the frame into the viewport of a drawable of width x height. */
static int gl_present(int preset_index, const uint32_t *pixels, const RECT *viewport,
                      int drawable_w, int drawable_h)
{
    GlPresetRun *run;
    int width = viewport->right - viewport->left;
    int height = viewport->bottom - viewport->top;
    int i;
    static const float flat[16] = {2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0, -1, -1, 0, 1};
    /* The screen pass flips: frame row 0 (the top) sits at texture v = 0. */
    static const float flipped[16] = {2, 0, 0, 0, 0, -2, 0, 0, 0, 0, 1, 0, -1, 1, 0, 1};
    if (!gl_preset_usable(preset_index)) preset_index = 0;
    run = &g_gl_runs[preset_index];
    if (run->state <= 0) return 0;
    if (!gl_size_preset(run, width, height)) {
        run = &g_gl_runs[0];
        if (!gl_size_preset(run, width, height)) return 0;
    }
    GLX(glBindVertexArray)(g_gl_vertex_array);
    GLX(glActiveTexture)(GL_TEXTURE0);
#ifdef __EMSCRIPTEN__
    GLX(glBindTexture)(GL_TEXTURE_2D, g_gl_raw_texture);
#else
    GLX(glBindTexture)(GL_TEXTURE_2D, g_gl_frame_texture);
#endif
    GLX(glPixelStorei)(GL_UNPACK_ALIGNMENT, 4);
    GLX(glTexSubImage2D)(GL_TEXTURE_2D, 0, 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT, GL_RGBA,
                         GL_UNSIGNED_BYTE, pixels);
#ifdef __EMSCRIPTEN__
    GLX(glUseProgram)(g_gl_swap_program);
    GLX(glBindFramebuffer)(GL_FRAMEBUFFER, g_gl_swap_framebuffer);
    GLX(glViewport)(0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT);
    GLX(glDrawArrays)(GL_TRIANGLE_STRIP, 0, 4);
#endif
    GLX(glBindFramebuffer)(GL_FRAMEBUFFER, 0);
    GLX(glViewport)(0, 0, drawable_w, drawable_h);
    GLX(glClearColor)(0.0f, 0.0f, 0.0f, 1.0f);
    GLX(glClear)(GL_COLOR_BUFFER_BIT);
    GLX(glBindVertexArray)(g_gl_vertex_array);
    ++g_gl_frame_count;
    for (i = 0; i < run->pass_count; ++i) {
        GlPassRun *pass = &run->runs[i];
        int last = i == run->pass_count - 1;
        GLuint input = i == 0 ? g_gl_frame_texture : run->runs[i - 1].texture;
        int in_w = i == 0 ? LOGICAL_WIDTH : run->runs[i - 1].width;
        int in_h = i == 0 ? LOGICAL_HEIGHT : run->runs[i - 1].height;
        GLint at;
        int back;
        GLX(glUseProgram)(pass->program);
        GLX(glActiveTexture)(GL_TEXTURE1);
        gl_set_input_filter(g_gl_frame_texture, 0);
        GLX(glActiveTexture)(GL_TEXTURE2);
        GLX(glBindTexture)(GL_TEXTURE_2D, run->lut);
        /* PassPrevN: the output N passes back, -1 being the game frame. */
        for (back = 1; back <= i + 1 && back < 8; ++back) {
            char name[32];
            int from = i - back;
            GLuint texture = from < 0 ? g_gl_frame_texture : run->runs[from].texture;
            int w = from < 0 ? LOGICAL_WIDTH : run->runs[from].width;
            int h = from < 0 ? LOGICAL_HEIGHT : run->runs[from].height;
            (void)snprintf(name, sizeof(name), "PassPrev%dTexture", back);
            if ((at = GLX(glGetUniformLocation)(pass->program, name)) < 0) continue;
            GLX(glActiveTexture)(GL_TEXTURE3 + back);
            gl_set_input_filter(texture, 0);
            GLX(glUniform1i)(at, 3 + back);
            (void)snprintf(name, sizeof(name), "PassPrev%dTextureSize", back);
            gl_set_size_uniform(pass->program, name, w, h);
            (void)snprintf(name, sizeof(name), "PassPrev%dInputSize", back);
            gl_set_size_uniform(pass->program, name, w, h);
        }
        GLX(glActiveTexture)(GL_TEXTURE0);
        gl_set_input_filter(input, run->passes[i].linear);
        gl_set_size_uniform(pass->program, "InputSize", in_w, in_h);
        gl_set_size_uniform(pass->program, "TextureSize", in_w, in_h);
        gl_set_size_uniform(pass->program, "OutputSize", pass->width, pass->height);
        gl_set_size_uniform(pass->program, "OrigTextureSize", LOGICAL_WIDTH, LOGICAL_HEIGHT);
        gl_set_size_uniform(pass->program, "OrigInputSize", LOGICAL_WIDTH, LOGICAL_HEIGHT);
        if ((at = GLX(glGetUniformLocation)(pass->program, "FrameCount")) >= 0)
            GLX(glUniform1i)(at, (GLint)g_gl_frame_count);
        if ((at = GLX(glGetUniformLocation)(pass->program, "FrameDirection")) >= 0)
            GLX(glUniform1i)(at, 1);
        if ((at = GLX(glGetUniformLocation)(pass->program, "MVPMatrix")) >= 0)
            GLX(glUniformMatrix4fv)(at, 1, GL_FALSE, last ? flipped : flat);
        if (last) {
            GLX(glBindFramebuffer)(GL_FRAMEBUFFER, 0);
            GLX(glViewport)(viewport->left, drawable_h - viewport->bottom, width, height);
        } else {
            GLX(glBindFramebuffer)(GL_FRAMEBUFFER, pass->framebuffer);
            GLX(glViewport)(0, 0, pass->width, pass->height);
        }
        GLX(glDrawArrays)(GL_TRIANGLE_STRIP, 0, 4);
    }
    return 1;
}

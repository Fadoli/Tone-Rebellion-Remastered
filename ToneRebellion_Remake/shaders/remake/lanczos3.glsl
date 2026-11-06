/*
 * lanczos3 (Tone Rebellion remake, written for this project).
 * Separable Lanczos-3 resampling in one pass: 6x6 taps around the sample,
 * weights sinc(x) sinc(x / 3), normalised. Libretro GLSL conventions (the
 * runner in src/platform/sdl/sdl_gl.inc supplies the uniforms).
 */

#if defined(VERTEX)

#if __VERSION__ >= 130
#define COMPAT_VARYING out
#define COMPAT_ATTRIBUTE in
#else
#define COMPAT_VARYING varying
#define COMPAT_ATTRIBUTE attribute
#endif

COMPAT_ATTRIBUTE vec4 VertexCoord;
COMPAT_ATTRIBUTE vec4 TexCoord;
COMPAT_VARYING vec4 TEX0;
uniform mat4 MVPMatrix;

void main()
{
    gl_Position = MVPMatrix * VertexCoord;
    TEX0.xy = TexCoord.xy;
}

#elif defined(FRAGMENT)

#if __VERSION__ >= 130
#define COMPAT_VARYING in
#define COMPAT_TEXTURE texture
out vec4 FragColor;
#else
#define COMPAT_VARYING varying
#define FragColor gl_FragColor
#define COMPAT_TEXTURE texture2D
#endif

#ifdef GL_ES
precision highp float;
#endif

uniform vec2 TextureSize;
uniform sampler2D Texture;
COMPAT_VARYING vec4 TEX0;

const float PI = 3.14159265358979;

float lanczos(float x)
{
    x = abs(x);
    if (x < 1e-5) return 1.0;
    if (x >= 3.0) return 0.0;
    float px = PI * x;
    return 3.0 * sin(px) * sin(px / 3.0) / (px * px);
}

void main()
{
    vec2 texel = TEX0.xy * TextureSize - 0.5;
    vec2 base = floor(texel);
    vec2 f = texel - base;
    vec3 sum = vec3(0.0);
    float total = 0.0;
    for (int j = -2; j <= 3; ++j) {
        float wy = lanczos(float(j) - f.y);
        for (int i = -2; i <= 3; ++i) {
            float w = lanczos(float(i) - f.x) * wy;
            vec2 at = (base + vec2(float(i), float(j)) + 0.5) / TextureSize;
            sum += COMPAT_TEXTURE(Texture, at).rgb * w;
            total += w;
        }
    }
    FragColor = vec4(clamp(sum / total, 0.0, 1.0), 1.0);
}
#endif

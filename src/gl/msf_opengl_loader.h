//-----------------------------------------------------------------------------
// About imgui_impl_opengl3_loader.h:
//
// We embed our own OpenGL loader to not require user to provide their own or to have to use ours,
// which proved to be endless problems for users.
// Our loader is custom-generated, based on gl3w but automatically filtered to only include
// enums/functions that we use in our imgui_impl_opengl3.cpp source file in order to be small.
//
// YOU SHOULD NOT NEED TO INCLUDE/USE THIS DIRECTLY. THIS IS USED BY imgui_impl_opengl3.cpp ONLY.
// THE REST OF YOUR APP SHOULD USE A DIFFERENT GL LOADER: ANY GL LOADER OF YOUR CHOICE.
//
// Regenerate with:
//   python gl3w_gen.py --output ../imgui/backends/imgui_impl_opengl3_loader.h --ref ../imgui/backends/imgui_impl_opengl3.cpp ./extra_symbols.txt
//
// More info:
//   https://github.com/dearimgui/gl3w_stripped
//   https://github.com/ocornut/imgui/issues/4445
//-----------------------------------------------------------------------------

/*
 * This file was generated with gl3w_gen.py, part of msf_gl3w
 * (hosted at https://github.com/dearimgui/gl3w_stripped)
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __gl3w_h_
#define __gl3w_h_

// Adapted from KHR/khrplatform.h to avoid including entire file.
#ifndef __khrplatform_h_
typedef          float         khronos_float_t;
typedef signed   char          khronos_int8_t;
typedef unsigned char          khronos_uint8_t;
typedef signed   short int     khronos_int16_t;
typedef unsigned short int     khronos_uint16_t;
#ifdef _WIN64
typedef signed   long long int khronos_intptr_t;
typedef signed   long long int khronos_ssize_t;
#else
typedef signed   long  int     khronos_intptr_t;
typedef signed   long  int     khronos_ssize_t;
#endif

#if defined(_MSC_VER) && !defined(__clang__)
typedef signed   __int64       khronos_int64_t;
typedef unsigned __int64       khronos_uint64_t;
#elif (defined(__clang__) || defined(__GNUC__)) && (__cplusplus < 201100)
#include <stdint.h>
typedef          int64_t       khronos_int64_t;
typedef          uint64_t      khronos_uint64_t;
#else
typedef signed   long long     khronos_int64_t;
typedef unsigned long long     khronos_uint64_t;
#endif
#endif  // __khrplatform_h_

#ifndef __gl_glcorearb_h_
#define __gl_glcorearb_h_ 1
#ifdef __cplusplus
extern "C" {
#endif
/*
** Copyright 2013-2020 The Khronos Group Inc.
** SPDX-License-Identifier: MIT
**
** This header is generated from the Khronos OpenGL / OpenGL ES XML
** API Registry. The current version of the Registry, generator scripts
** used to make the header, and the header can be found at
**   https://github.com/KhronosGroup/OpenGL-Registry
*/
#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>
#endif
#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif
#ifndef GLAPI
#define GLAPI extern
#endif
/* glcorearb.h is for use with OpenGL core profile implementations.
** It should should be placed in the same directory as gl.h and
** included as <GL/glcorearb.h>.
**
** glcorearb.h includes only APIs in the latest OpenGL core profile
** implementation together with APIs in newer ARB extensions which 
** can be supported by the core profile. It does not, and never will
** include functionality removed from the core profile, such as
** fixed-function vertex and fragment processing.
**
** Do not #include both <GL/glcorearb.h> and either of <GL/gl.h> or
** <GL/glext.h> in the same source file.
*/
/* Generated C header for:
 * API: gl
 * Profile: core
 * Versions considered: .*
 * Versions emitted: .*
 * Default extensions included: glcore
 * Additional extensions included: _nomatch_^
 * Extensions removed: _nomatch_^
 */
#ifndef GL_VERSION_1_0
typedef void GLvoid;
typedef unsigned int GLenum;

typedef khronos_float_t GLfloat;
typedef int GLint;
typedef int GLsizei;
typedef unsigned int GLbitfield;
typedef double GLdouble;
typedef unsigned int GLuint;
typedef unsigned char GLboolean;
typedef khronos_uint8_t GLubyte;
#define GL_VENDOR                         0x1F00
typedef void (APIENTRYP PFNGLGETINTEGERVPROC) (GLenum pname, GLint *data);
typedef const GLubyte *(APIENTRYP PFNGLGETSTRINGPROC) (GLenum name);
#ifdef GL_GLEXT_PROTOTYPES
GLAPI void APIENTRY glGetIntegerv (GLenum pname, GLint *data);
GLAPI const GLubyte *APIENTRY glGetString (GLenum name);
#endif
#endif /* GL_VERSION_1_0 */
#ifndef GL_VERSION_1_1
typedef khronos_float_t GLclampf;
typedef double GLclampd;
#endif /* GL_VERSION_1_1 */
#ifndef GL_VERSION_1_5
typedef khronos_ssize_t GLsizeiptr;
typedef khronos_intptr_t GLintptr;
#endif /* GL_VERSION_1_5 */
#ifndef GL_VERSION_2_0
typedef char GLchar;
typedef khronos_int16_t GLshort;
typedef khronos_int8_t GLbyte;
typedef khronos_uint16_t GLushort;
#endif /* GL_VERSION_2_0 */
#ifndef GL_VERSION_3_0
typedef khronos_uint16_t GLhalf;
#define GL_MAJOR_VERSION                  0x821B
#define GL_MINOR_VERSION                  0x821C
typedef void (APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum target, GLuint index, GLboolean *data);
typedef void (APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum target, GLuint index, GLint *data);
#endif /* GL_VERSION_3_0 */
#ifndef GL_VERSION_3_2
typedef struct __GLsync *GLsync;
typedef khronos_uint64_t GLuint64;
typedef khronos_int64_t GLint64;
typedef void (APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum target, GLuint index, GLint64 *data);
#endif /* GL_VERSION_3_2 */
#ifndef GL_VERSION_4_1
typedef void (APIENTRYP PFNGLGETFLOATI_VPROC) (GLenum target, GLuint index, GLfloat *data);
typedef void (APIENTRYP PFNGLGETDOUBLEI_VPROC) (GLenum target, GLuint index, GLdouble *data);
#endif /* GL_VERSION_4_1 */
#ifndef GL_VERSION_4_3
typedef void (APIENTRY  *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
#endif /* GL_VERSION_4_3 */
#ifndef GL_VERSION_4_5
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI_VPROC) (GLuint xfb, GLenum pname, GLuint index, GLint *param);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI64_VPROC) (GLuint xfb, GLenum pname, GLuint index, GLint64 *param);
#endif /* GL_VERSION_4_5 */
#ifndef GL_ARB_bindless_texture
typedef khronos_uint64_t GLuint64EXT;
#endif /* GL_ARB_bindless_texture */
#ifndef GL_ARB_cl_event
struct _cl_context;
struct _cl_event;
#endif /* GL_ARB_cl_event */
#ifndef GL_ARB_debug_output
typedef void (APIENTRY  *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
#endif /* GL_ARB_debug_output */
#ifndef GL_EXT_EGL_image_storage
typedef void *GLeglImageOES;
#endif /* GL_EXT_EGL_image_storage */
#ifndef GL_EXT_direct_state_access
typedef void (APIENTRYP PFNGLGETFLOATI_VEXTPROC) (GLenum pname, GLuint index, GLfloat *params);
typedef void (APIENTRYP PFNGLGETDOUBLEI_VEXTPROC) (GLenum pname, GLuint index, GLdouble *params);
typedef void (APIENTRYP PFNGLGETPOINTERI_VEXTPROC) (GLenum pname, GLuint index, void **params);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINTEGERI_VEXTPROC) (GLuint vaobj, GLuint index, GLenum pname, GLint *param);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYPOINTERI_VEXTPROC) (GLuint vaobj, GLuint index, GLenum pname, void **param);
#endif /* GL_EXT_direct_state_access */
#ifndef GL_NV_draw_vulkan_image
typedef void (APIENTRY  *GLVULKANPROCNV)(void);
#endif /* GL_NV_draw_vulkan_image */
#ifndef GL_NV_gpu_shader5
typedef khronos_int64_t GLint64EXT;
#endif /* GL_NV_gpu_shader5 */
#ifndef GL_NV_vertex_buffer_unified_memory
typedef void (APIENTRYP PFNGLGETINTEGERUI64I_VNVPROC) (GLenum value, GLuint index, GLuint64EXT *result);
#endif /* GL_NV_vertex_buffer_unified_memory */
#ifdef __cplusplus
}
#endif
#endif

#ifndef GL3W_API
#define GL3W_API
#endif

#ifndef __gl_h_
#define __gl_h_
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define GL3W_OK 0
#define GL3W_ERROR_INIT -1
#define GL3W_ERROR_LIBRARY_OPEN -2
#define GL3W_ERROR_OPENGL_VERSION -3

typedef void (*GL3WglProc)(void);
typedef GL3WglProc (*GL3WGetProcAddressProc)(const char *proc);

/* gl3w api */
GL3W_API int msf_gl3wInit(void);
GL3W_API int msf_gl3wInit2(GL3WGetProcAddressProc proc);
GL3W_API int msf_gl3wIsSupported(int major, int minor);
GL3W_API GL3WglProc msf_gl3wGetProcAddress(const char *proc);

/* gl3w internal state */
union GL3WProcs {
    GL3WglProc ptr[2];
    struct {
        PFNGLGETINTEGERVPROC GetIntegerv;
        PFNGLGETSTRINGPROC   GetString;
    } gl;
};

GL3W_API extern union GL3WProcs msf_gl3wProcs;

/* OpenGL functions */
#define glGetIntegerv        msf_gl3wProcs.gl.GetIntegerv
#define glGetString          msf_gl3wProcs.gl.GetString

#ifdef __cplusplus
}
#endif

#endif

#ifdef MSF_GL3W_IMPL
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#define ARRAY_SIZE(x)  (sizeof(x) / sizeof((x)[0]))

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#include <windows.h>

static HMODULE libgl;
typedef PROC(__stdcall* GL3WglGetProcAddr)(LPCSTR);
static GL3WglGetProcAddr wgl_get_proc_address;

static int open_libgl(void)
{
    libgl = LoadLibraryA("opengl32.dll");
    if (!libgl)
        return GL3W_ERROR_LIBRARY_OPEN;
    wgl_get_proc_address = (GL3WglGetProcAddr)GetProcAddress(libgl, "wglGetProcAddress");
    return GL3W_OK;
}

static void close_libgl(void) { FreeLibrary(libgl); }
static GL3WglProc get_proc(const char *proc)
{
    GL3WglProc res;
    res = (GL3WglProc)wgl_get_proc_address(proc);
    if (!res)
        res = (GL3WglProc)GetProcAddress(libgl, proc);
    return res;
}
#elif defined(__APPLE__)
#include <dlfcn.h>

static void *libgl;
static int open_libgl(void)
{
    libgl = dlopen("/System/Library/Frameworks/OpenGL.framework/OpenGL", RTLD_LAZY | RTLD_LOCAL);
    if (!libgl)
        return GL3W_ERROR_LIBRARY_OPEN;
    return GL3W_OK;
}

static void close_libgl(void) { dlclose(libgl); }

static GL3WglProc get_proc(const char *proc)
{
    GL3WglProc res;
    *(void **)(&res) = dlsym(libgl, proc);
    return res;
}
#else
#include <dlfcn.h>

static void *libgl;
static GL3WglProc (*glx_get_proc_address)(const GLubyte *);

static int open_libgl(void)
{
    libgl = dlopen("libGL.so.1", RTLD_LAZY | RTLD_LOCAL);
    if (!libgl)
        return GL3W_ERROR_LIBRARY_OPEN;
    *(void **)(&glx_get_proc_address) = dlsym(libgl, "glXGetProcAddressARB");
    return GL3W_OK;
}

static void close_libgl(void) { dlclose(libgl); }

static GL3WglProc get_proc(const char *proc)
{
    GL3WglProc res;
    res = glx_get_proc_address((const GLubyte *)proc);
    if (!res)
        *(void **)(&res) = dlsym(libgl, proc);
    return res;
}
#endif

static struct { int major, minor; } version;

static int parse_version(void)
{
    if (!glGetIntegerv)
        return GL3W_ERROR_INIT;
    glGetIntegerv(GL_MAJOR_VERSION, &version.major);
    glGetIntegerv(GL_MINOR_VERSION, &version.minor);
    if (version.major < 3)
        return GL3W_ERROR_OPENGL_VERSION;
    return GL3W_OK;
}

static void load_procs(GL3WGetProcAddressProc proc);

int msf_gl3wInit(void)
{
    int res = open_libgl();
    if (res)
        return res;
    atexit(close_libgl);
    return msf_gl3wInit2(get_proc);
}

int msf_gl3wInit2(GL3WGetProcAddressProc proc)
{
    load_procs(proc);
    return parse_version();
}

int msf_gl3wIsSupported(int major, int minor)
{
    if (major < 3)
        return 0;
    if (version.major == major)
        return version.minor >= minor;
    return version.major >= major;
}

GL3WglProc msf_gl3wGetProcAddress(const char *proc) { return get_proc(proc); }

static const char *proc_names[] = {
    "glGetIntegerv",
    "glGetString",
};

GL3W_API union GL3WProcs msf_gl3wProcs;

static void load_procs(GL3WGetProcAddressProc proc)
{
    size_t i;
    for (i = 0; i < ARRAY_SIZE(proc_names); i++)
        msf_gl3wProcs.ptr[i] = proc(proc_names[i]);
}

#ifdef __cplusplus
}
#endif
#endif

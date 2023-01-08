#pragma once

#include "define.h"
#include "glad/glad.h"
BEGIN_OGS_GFX_NAMESPACE

using OGL_HANDLE = unsigned int;

#if OGS_DEBUG > 0 
        #define GL_CHECK(x)                                          \
        do {                                                         \
            x;                                                       \
            GLenum err = glGetError();                               \
            if (err != GL_NO_ERROR) {                                \
                ASSERT(false,"%s returned GL error: 0x%x", #x, err); \
            }                                                        \
        } while (0)
#else
	#define GL_CHECK(x) x
#endif

END_OGS_GFX_NAMESPACE
#pragma once

#define USE_GLEW
//#define USE_GL3W
//#define USE_GLAD

#if defined(USE_GLEW)
#include <GL/glew.h>
#elif defined(USE_GL3W)
#include <GL/gl3w.h>
#elif defined(USE_GLAD)
#include <glad/gl.h>
#endif

bool InitGL();

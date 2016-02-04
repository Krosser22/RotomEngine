/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#ifdef _MSC_VER
#undef APIENTRY
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3native.h>
#endif

#include "drawable.h"

namespace ROTOM {
  namespace GRAPHICS {
    void setShader(ShaderData *shaderData, const char *vertexShaderSource, const char *fragmentShaderSource);

    void useMaterial(ShaderData *shaderData, Drawable *drawable, float *projectionMatrix);
  }
}

#endif //__GRAPHICS_H__
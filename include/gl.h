/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

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
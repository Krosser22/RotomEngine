/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
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

#include "node/geometry.h"
#include "node/light.h"
#include "commandDrawObject.h"
#include "node/camera.h"
#include "node/material.h"

namespace ROTOM {
  namespace GRAPHICS {
    float getTime();

    void setShader(ShaderData *shaderData, const char *vertexShaderSource, const char *fragmentShaderSource);

    void setTexture(unsigned int *texture, unsigned char *image, int *textureWidth, int *textureHeight);

    void renderTexture();

    void setRenderTexture(Camera *camera, Material *material);

    void releaseMaterial(unsigned int shaderProgram);

    void drawMaterial(CommandDrawObjectData *commandDrawObjectData, std::vector<std::shared_ptr<Light>> *lights, float *projectionMatrix, float *viewMatrix);

    void clearScreen();

    void loadGeometry(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO, int numberOfElementsPerVertex, unsigned int vertexCount, float *vertex, int *index);

    void releaseGeometry(unsigned int VAO, unsigned int VBO, unsigned int EBO);
  }
}

#endif //__GRAPHICS_H__
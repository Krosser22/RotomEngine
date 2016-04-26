/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "node/light.h"
#include "commandDrawObject.h"
#include "node/material.h"

namespace ROTOM {
  namespace GRAPHICS {
    float getTime();

    void windowInit(unsigned int width, unsigned int height);

    void windowDestroy();

    bool windowShouldClose();

    void clearScreen();

    void clear();

    int screenWidth();

    void swapBuffers();

    int screenHeight();

    void setShader(ShaderData *shaderData, const char *vertexShaderSource, const char *fragmentShaderSource);

    unsigned int setTexture(unsigned int *texture, unsigned char *image, int *textureWidth, int *textureHeight);

    void releaseTexture(unsigned int *texture);

    void releaseMaterial(unsigned int *shaderProgram);

    void drawObject(CommandDrawObjectData *commandDrawObjectData, std::vector<std::shared_ptr<Light>> *lights, float *projectionMatrix, float *viewMatrix);

    void loadGeometry(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO, int numberOfElementsPerVertex, unsigned int vertexCount, float *vertex, int *index);

    void releaseGeometry(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO);

    void genRenderBuffer(unsigned int *textureColorbuffer, unsigned int *textureDepthbuffer, unsigned int *framebuffer, unsigned int width, unsigned int height);

    void beginFramebuffer(unsigned int framebuffer);

    void endFramebuffer();
  }
}

#endif //__GRAPHICS_H__
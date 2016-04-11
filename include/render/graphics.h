/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

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

    void setRenderTexture(Material *material, unsigned int *textureColorbuffer, unsigned int *framebuffer);

    void releaseMaterial(unsigned int shaderProgram);

    void drawMaterial(CommandDrawObjectData *commandDrawObjectData, std::vector<std::shared_ptr<Light>> *lights, float *projectionMatrix, float *viewMatrix);

    void clearScreen();

    void loadGeometry(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO, int numberOfElementsPerVertex, unsigned int vertexCount, float *vertex, int *index);

    void releaseGeometry(unsigned int VAO, unsigned int VBO, unsigned int EBO);

    void beginFramebuffer(unsigned int framebuffer);

    void endFramebuffer();
  }
}

#endif //__GRAPHICS_H__
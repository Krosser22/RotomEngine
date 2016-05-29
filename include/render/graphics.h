/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "node/directionalLight.h"
#include "node/spotLight.h"
#include "commandDrawObject.h"
#include "node/material.h"

namespace ROTOM {
  namespace GRAPHICS {
    //Time
    float getTime();

    //Windows
    void windowInit(unsigned int width, unsigned int height);
    void windowDestroy();
    bool windowShouldClose();
    void clearScreen();
    void clear();
    void swapBuffers();
    int screenWidth();
    int screenHeight();

    //Shader
    void setShader(ShaderData *shaderData, const char *vertexShaderSource, const char *fragmentShaderSource);

    //Texture
    void setTexture(unsigned int *texture, unsigned char *image, int *textureWidth, int *textureHeight);
    void releaseTexture(unsigned int *texture);

    //Material
    void releaseMaterial(unsigned int *shaderProgram);

    //Draw
    void drawObject(CommandDrawObjectData *commandDrawObjectData, std::vector<std::shared_ptr<DirectionalLight>> *directionalLights, std::vector<std::shared_ptr<SpotLight>> *spotLights, float *projectionMatrix, float *viewMatrix, float *viewPosition);
    void drawObject(CommandDrawObjectData *commandDrawObjectData);

    //Geometry
    void loadGeometry(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO, int numberOfElementsPerVertex, unsigned int vertexCount, float *vertex, int *index);
    void releaseGeometry(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO);

    //Framebuffer
    void genRenderBuffer(unsigned int *colorTexture, unsigned int *depthTexture, unsigned int *framebuffer, unsigned int width, unsigned int height);
    void beginFramebuffer(RenderTarget *renderTarget);
    void endFramebuffer();

    //Cubemap
    void loadCubemap(unsigned int *program, unsigned int *VAO, unsigned int *texture);
    void drawCubemap(unsigned int *program, unsigned int *VAO, unsigned int *texture, float *cameraProjection, float *cameraView);
  }
}

#endif //__GRAPHICS_H__
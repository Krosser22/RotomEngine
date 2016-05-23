/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "render/cubemap.h"
#include "render/graphics.h"
#include "node/material.h"
#include "general/files.h"

struct CubemapData {
  CubemapData() {
    VAO = 0;
    texture = 0;
  }
  unsigned int VAO;
  unsigned int texture;
  ROTOM::ShaderData shaderData;
} cubemapData;

ROTOM::Cubemap::Cubemap() {}

ROTOM::Cubemap::~Cubemap() {}

void ROTOM::Cubemap::init(char *path) {
  //TODO - The path of the cubemap is fixed
  printf("Fix the cubemap path");

  std::string vertexPath = kPath_shaderFiles;
  std::string fragmentPath = kPath_shaderFiles;

  vertexPath.append("cubemap.vertx");
  fragmentPath.append("cubemap.frag");

  std::string vertexShader = FILES::ReadFile(vertexPath.c_str());
  std::string fragmentShader = FILES::ReadFile(fragmentPath.c_str());

  GRAPHICS::setShader(&cubemapData.shaderData, vertexShader.c_str(), fragmentShader.c_str());
  GRAPHICS::loadCubemap(&cubemapData.shaderData.shaderProgram, &cubemapData.VAO, &cubemapData.texture);
}

void ROTOM::Cubemap::draw(float *projectionMatrix, float *viewMatrix) {
  GRAPHICS::drawCubemap(&cubemapData.shaderData.shaderProgram, &cubemapData.VAO, &cubemapData.texture, projectionMatrix, viewMatrix);
}
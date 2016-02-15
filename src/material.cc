/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "material.h"

#include "graphics.h"
#include "security.h"
#include "soil.h"

ROTOM::Material::Material(const char *texturePath) {
  SECURITY::addSecurityCount(SECURITY::MyClass::MyClass_Material);
  setTexture(texturePath);

  shininess_ = 500.0f;

  specularMaterial_[0] = 0.0f;
  specularMaterial_[1] = 0.0f;
  specularMaterial_[2] = 0.0f;
  specularMaterial_[3] = 0.0f;
}

ROTOM::Material::~Material() {
  SECURITY::removeSecurityCount(SECURITY::MyClass::MyClass_Material);
}

void ROTOM::Material::setShader(MaterialSettings *materialSettings, const char *vertexShaderSource, const char *fragmentShaderSource) {
  GRAPHICS::setShader(materialSettings, vertexShaderSource, fragmentShaderSource);
}

void ROTOM::Material::setTexture(const char *texturePath) {
  // Load and generate the texture
  // Load image, create texture and generate mipmaps
  //FILE *file = fopen(texturePath, "r");
  //if (file == NULL) printf("ERROR AL ABRIR %s\n", texturePath);
  //float *image = stbi_loadf_from_file(file, &textureWidth_, &textureHeight_, 0, 0);
  unsigned char *image = SOIL_load_image(texturePath, &textureWidth_, &textureHeight_, 0, SOIL_LOAD_RGB); //Line 1425 of SOIL.c
  if (image == NULL) printf("ERROR AL ABRIR: [%s]\n", texturePath);
  GRAPHICS::setTexture(&texture_, image, &textureWidth_, &textureHeight_);
  SOIL_free_image_data(image);
}

void ROTOM::Material::textureSize(int &width, int &height) {
  width = textureWidth_;
  height = textureHeight_;
}

const unsigned int ROTOM::Material::texture() {
  return texture_;
}
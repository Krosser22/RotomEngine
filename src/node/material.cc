/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** /////Email: lasernaco@esat-alumni.com  /////
*** /////            2015-2016             /////
*** ////////////////////////////////////////////
**/

#include "node/material.h"
#include "render/graphics.h"
#include "general/files.h"
#include <soil.h>

const static char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 normal;\n"
"layout(location = 2) in vec2 uv;\n"
"uniform mat4 u_model;\n"
"uniform mat4 u_view;\n"
"uniform mat4 u_projection;\n"
"out vec3 fragmentPosition;\n"
"out vec3 normalDirection;\n"
"out vec2 uvMaterial;\n"
"void main() {\n"
"  fragmentPosition = (u_model * vec4(position, 1.0f)).xyz;\n"
"  gl_Position = u_projection * u_view * u_model * vec4(position, 1.0f);\n"
"  normalDirection = transpose(inverse(mat3(u_model))) * normal;\n"
"  uvMaterial = uv;\n"
"};\0";

const static char* fragmentShaderSource = "#version 330 core\n"
"uniform struct Light {\n"
"  vec4 position;\n"
"  vec3 color;\n"
"  vec3 rotation;\n"
"} u_allLights[1];\n"
"uniform sampler2D u_texture;\n"
"uniform vec4 u_color;\n"
"uniform float u_ambientStrength;\n"
"uniform float u_shininess;\n"
"uniform vec3 u_specularIntensity;\n"
"uniform vec3 u_specularMaterial;\n"
"uniform vec3 u_viewPosition;\n"
"in vec3 fragmentPosition;\n"
"in vec3 normalDirection;\n"
"in vec2 uvMaterial;\n"
"out vec4 fragment;\n"
"void main() {\n"
"  vec4 materialColor = texture(u_texture, uvMaterial) * u_color;\n"
"  vec3 lightDirectionNormalized = normalize(u_allLights[0].position.xyz - fragmentPosition);\n"
"  vec3 normalDirectionNormalized = normalize(normalDirection);\n"
"  vec3 ambient = u_allLights[0].color * u_ambientStrength;\n"
"  vec3 diffuse = u_allLights[0].color * max(dot(lightDirectionNormalized, normalDirectionNormalized), 0.0f);\n"
"  vec3 viewDirectionNormalized = normalize(u_viewPosition - fragmentPosition);\n"
"  vec3 halfwayDir = normalize(lightDirectionNormalized + viewDirectionNormalized);\n"
"  float spec = pow(max(dot(normalDirectionNormalized, halfwayDir), 0.0f), u_shininess);\n"
"  vec3 specular = u_allLights[0].color * spec * u_specularIntensity * u_specularMaterial;\n"
"  fragment = materialColor * vec4((ambient + diffuse + specular), 1.0f);\n"
"  fragment = vec4(u_allLights[0].position.xyz, 1.0f);\n"
"};\0";

ROTOM::Material::Material(const char *texturePath) {
  materialData_.shininess = 64.0f;

  materialData_.specularMaterial[0] = 1.0f;
  materialData_.specularMaterial[1] = 1.0f;
  materialData_.specularMaterial[2] = 1.0f;

  materialData_.ambientStrength = 0.15f;
  
  setTextureFromPath(texturePath);
  setShader(vertexShaderSource, fragmentShaderSource);
}

ROTOM::Material::~Material() {
  GRAPHICS::releaseMaterial(&shaderData_.shaderProgram);
}

void ROTOM::Material::setShader(const char *vertexShaderSource, const char *fragmentShaderSource) {
  GRAPHICS::setShader(&shaderData_, vertexShaderSource, fragmentShaderSource);
}

void ROTOM::Material::setShaderFromPath(const char *vertexShaderPath, const char *fragmentShaderPath) {
  std::string vertexPath = kPath_shaderFiles;
  std::string fragmentPath = kPath_shaderFiles;

  vertexPath.append(vertexShaderPath);
  fragmentPath.append(fragmentShaderPath);

  std::string vertexShaderSource = FILES::ReadFile(vertexPath.data());
  std::string fragmentShaderSource = FILES::ReadFile(fragmentPath.data());

  setShader(vertexShaderSource.data(), fragmentShaderSource.data());
}

void ROTOM::Material::setTexture(unsigned char *texture) {
  GRAPHICS::setTexture(&texture_, texture, &textureWidth_, &textureHeight_);
}

void ROTOM::Material::setTexture(unsigned int *texture) {
  texture_ = *texture;
}

void ROTOM::Material::setTextureFromPath(const char *path) {
  //Load and generate the texture and the mipmaps
  unsigned char *image = SOIL_load_image(path, &textureWidth_, &textureHeight_, 0, SOIL_LOAD_RGBA);
  if (!image) {
    printf("ERROR AL ABRIR: [%s]\n", path);
    system("pause");
  }
  setTexture(image);
  SOIL_free_image_data(image);
}

void ROTOM::Material::textureSize(int &width, int &height) {
  width = textureWidth_;
  height = textureHeight_;
}

const unsigned int ROTOM::Material::texture() {
  return texture_;
}
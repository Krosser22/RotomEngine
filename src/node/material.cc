/**
*** ////////////////////////////////////////////
*** /////Autor: Juan Daniel Laserna Condado/////
*** ////////////////////////////////////////////
**/

#include "node/material.h"
#include "render/graphics.h"
#include "soil.h"

const static char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 normal;\n"
"layout(location = 2) in vec2 uv;\n"
"uniform mat4 u_model;\n"
"uniform mat4 u_view;\n"
"uniform mat4 u_projection;\n"
"uniform vec3 u_lightPosition;\n"
"out vec3 lightDirection;\n"
"out vec3 normalDirection;\n"
"out vec4 cameraPosition;\n"
"out vec4 materialPosition;\n"
"out vec2 uvMaterial;\n"
"void main() {\n"
"  mat4 mv_matrix = u_view * u_model;\n"
"  cameraPosition = u_view[3];\n"
"  //Light\n"
"  lightDirection = normalize(u_view * vec4(u_lightPosition, 1.0f) - mv_matrix * vec4(position, 1.0f)).xyz;\n"
"  normalDirection = normalize(mv_matrix * vec4(normal, 0.0f)).xyz;\n"
"  //Material\n"
"  uvMaterial = uv;\n"
"  gl_Position = u_projection * mv_matrix * vec4(position, 1.0);\n"
"};\0";

const static char* fragmentShaderSource = "#version 330 core\n"
"uniform vec4 u_color;\n"
"uniform sampler2D u_texture;\n"
"uniform vec3 u_lightColor;\n"
"uniform float u_shininess;\n"
"uniform vec3 u_specularIntensity;\n"
"uniform vec3 u_specularMaterial;\n"
"in vec3 lightDirection;\n"
"in vec3 normalDirection;\n"
"in vec4 cameraPosition;\n"
"in vec2 uvMaterial;\n"
"out vec4 fragment;\n"
"void main() {\n"
"  float cosAngleDifuse = max(0.0, dot(normalize(lightDirection), normalize(normalDirection)));\n"
"  vec4 difuseColor = vec4(texture(u_texture, uvMaterial).xyz * u_color.xyz * u_lightColor * cosAngleDifuse, 1.0);\n"
"  vec3 viewDirection = normalize(normalize(normalDirection) - cameraPosition.xyz);\n"
"  vec3 halfWay = normalize(normalize(lightDirection) + viewDirection);\n"
"  float cosAngleSpecular = max(0.0, dot(halfWay, normalize(normalDirection)));\n"
"  vec4 specularColor = vec4(pow(cosAngleSpecular, u_shininess) * u_specularIntensity * u_specularMaterial, 1.0);\n"
"  vec4 finalColor = difuseColor + specularColor;\n"
"  finalColor.w = min(1.0, finalColor.w);\n"
"  vec3 ambientLight = texture(u_texture, uvMaterial).xyz * 0.05;\n"
"  fragment = finalColor + vec4(ambientLight, 1.0);\n"
"};\0";

ROTOM::Material::Material(const char *texturePath) {
  materialData_.shininess = 500.0f;

  materialData_.specularMaterial[0] = 0.0f;
  materialData_.specularMaterial[1] = 0.0f;
  materialData_.specularMaterial[2] = 0.0f;
  materialData_.specularMaterial[3] = 0.0f;

  materialData_.ambientStrength = 0.05f;
  
  setTexture(texturePath);
  setShader(vertexShaderSource, fragmentShaderSource);
}

ROTOM::Material::~Material() {}

void ROTOM::Material::setShader(const char *vertexShaderSource, const char *fragmentShaderSource) {
  GRAPHICS::setShader(&shaderData_, vertexShaderSource, fragmentShaderSource);
}

void ROTOM::Material::setTexture(const char *path) {
  //Load and generate the texture and the mipmaps
  unsigned char *image = SOIL_load_image(path, &textureWidth_, &textureHeight_, 0, SOIL_LOAD_RGB); //Line 1425 of SOIL.c
  if (!image) {
    printf("ERROR AL ABRIR: [%s]\n", path);
  }
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